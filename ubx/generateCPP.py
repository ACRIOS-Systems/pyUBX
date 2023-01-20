#!/usr/bin/env python3
"""Generate CPP code from the UBX message definitions in UBX/."""
import os
import sys
import re
import datetime
import inspect
from ubx.introspect import getClassesInModule, getClassName, getClassMembers, getMessageName
from ubx import UBX
from pathlib import Path


__version__ = "0.1"


def isFieldType(obj):
    """Test if object is a Type in a Field."""
    return obj.__class__.__module__ == 'Types'


def isFieldRepeated(obj):
    """Test if object is a Repeated 'type' in a Field."""
    if inspect.isclass(obj):
        return getClassName(obj).split(".")[-1] == "Repeated"
    else:
        return False


def makeComment(s):
    """Comment out a (multiline) string."""
    if s is None or s == "":
        return None
    l = s.split("\n")
    if len(s) == 1:
        l[0] = "/* " + l + " */"
    else:
        l[0] = "/* " + l[0]
        l[1:] = [" *" + ((" " + ss) if (ss != "") else ss) for ss in l[1:-1]]
        l.append(" */")
    return "\n".join(l)


def makeMemberDecl(typ, name):
    """Return a member declaration.

    In particular rearrange the pseudo .ctype such as char[10]."""
    m = re.match(r"(.*)(\[[-0-9]+\])", typ)
    if m is not None:
        typ, ary = m.groups()
        return "{} {}{};".format(typ, name, ary)
    else:
        return "{} {};".format(typ, name)


def getBitName(field,  bit):
    return field[0] + "_" + bit


def getBitNameUp(field, bit):
    return getBitName(field, bit).upper()


def generateEnumDefinitions(fields, file, repeated=False):
    if fields:
        if repeated:
            name = "repeated_"
        else:
            name = ""
        for field in fields:
            allowed = getattr(field[1], "allowed", {})
            if len(allowed.keys()) > 0:
                file.write(f"        enum _{name}{field[0]}_allowed{{\n")
                keys = {}
                for a in allowed:
                    key = allowed[a].replace(' ', '_').replace('-', '_')
                    if key not in keys:
                        keys[key] = 0
                    else:
                        keys[key] += 1
                        key += str(keys[key])
                    file.write(
                        f"            allowed_{name}{field[0]}_{key}={a},\n")
                file.write(f"        }};\n")


def generateMacroDefinitions(fields, file, name, repeated=False):
    if fields:
        if repeated:
            name += "_REPEATED"
        for field in fields:
            bitfield = getattr(field[1], "bitfield", {})
            if len(bitfield.keys()) > 0:
                file.write(f"\n")
                for bit in bitfield:
                    file.write(
                        f"#define {name}_{getBitNameUp(field, bit)}_OFFSET ({bitfield[bit]['s']})\n")
                    file.write(
                        f"#define {name}_{getBitNameUp(field, bit)}_MASK ({bitfield[bit]['mask']})\n")


def generateUsageOfMacroDefinitions(fields, file, name, repeated=False):
    if fields:
        if repeated:
            name += "_REPEATED"
            name2 = "repeated_"
            nDefCom = ", "
            nDef = "uint8_t n"
        else:
            name2 = ""
            nDefCom = ""
            nDef = ""
        for field in fields:
            bitfield = getattr(field[1], "bitfield", {})
            if len(bitfield.keys()) > 0:
                file.write(f"\n")
                for bit in bitfield:
                    file.write(
                        f"        void {name2}{getBitName(field, bit)}(uint8_t val{nDefCom}{nDef});\n")
                    file.write(
                        f"        uint8_t {name2}{getBitName(field, bit)}({nDef}) const;\n")


def generateUsageOfMacroDefinitionsBody(fields, file, className, name, repeated=False):
    if fields:
        if repeated:
            name += "_REPEATED"
            name2 = "repeated_"
            nDefCom = ", "
            nDef = "uint8_t n"
            repeatedName = "repeated[n]."
        else:
            name2 = ""
            nDefCom = ""
            nDef = ""
            repeatedName = ""
        for field in fields:
            bitfield = getattr(field[1], "bitfield", {})
            if len(bitfield.keys()) > 0:
                file.write(f"\n")
                for bit in bitfield:
                    file.write(
                        f"void ubx::{className}::_data::{name2}{getBitName(field, bit)}(uint8_t val{nDefCom}{nDef}){{ UBX_CHANGE_VAR_BIT({repeatedName}{field[0]}, val, {name}_{getBitNameUp(field, bit)}_MASK, {name}_{getBitNameUp(field, bit)}_OFFSET); }}\n")
                    file.write(
                        f"uint8_t ubx::{className}::_data::{name2}{getBitName(field, bit)}({nDef})const{{ return UBX_GET_VAR_BIT({repeatedName}{field[0]}, {name}_{getBitNameUp(field, bit)}_MASK, {name}_{getBitNameUp(field, bit)}_OFFSET); }}\n")


def makeMessageStruct(file, className, Message):
    messageName = getMessageName(
        Message, withUBX=False, withMessageClass=False)
    # fullClassName = "{}::{}".format(className, messageName)
    fullClassNameUnder = "{}_{}".format(className, messageName)
    fields = getClassMembers(Message.Fields)
    fieldsNotRepeated = list(
        filter(lambda f: not isFieldRepeated(f[1]), fields))
    fieldsNotRepeated = sorted(fieldsNotRepeated, key=lambda x: x[1].ord)
    repeated = list(filter(lambda f: isFieldRepeated(f[1]), fields))
    if repeated:
        repeated = repeated[0]
        fieldsRepeated = getClassMembers(repeated[1])
        fieldsRepeated = sorted(fieldsRepeated, key=lambda x: x[1].ord)
    else:
        fieldsRepeated = None
    generateMacroDefinitions(fieldsNotRepeated, file, fullClassNameUnder)
    generateMacroDefinitions(fieldsRepeated, file, fullClassNameUnder, True)
    if Message.__doc__ is not None:
        file.write(makeComment(Message.__doc__))
        file.write("\n")
    file.write(
        "struct __attribute__((packed)) {} : public SerializeCommon\n".format(messageName))
    file.write("{\n")
    if fieldsRepeated:
        file.write(
            "    uint16_t repeatedLen; /* Set N-count array dimension of repeated structure. Do not serialize this byte*/\n")
        file.write("    static const uint16_t repeatedSize;\n")
    file.write("    virtual uint8_t getClassId(void) const override;\n")
    file.write("    virtual uint8_t getMessageId(void) const override;\n")
    file.write(
        "    virtual const std::string &getClassName(void) const override;\n")
    file.write("    virtual std::string getMessageName(void) const override;\n")
    file.write("    virtual std::string getDescription(void) const override;\n")
    file.write("    virtual uint8_t* getDataStartAddress(void) const override;\n")
    file.write("    virtual uint16_t getDataSize(void) const override;\n\n")
    file.write(f"    static constexpr uint8_t messageID = {Message._id};\n")
    file.write("\n    struct __attribute__((packed)) _data {\n")
    for field in fieldsNotRepeated:
        file.write("        {}\n".format(
            makeMemberDecl(field[1].ctype, field[0])))
    if fieldsRepeated:
        file.write("\n        struct __attribute__((packed)) _repeated {\n")
        makeStructBodyRepeated(file, repeated[1])
        file.write(
            "        } repeated [0]; /* [0] -> to pass compilation. Length is set by repeatedLen. Do not forget alloc enough space*/\n")
    file.write("\n")
    generateEnumDefinitions(fieldsNotRepeated, file)
    generateEnumDefinitions(fieldsRepeated, file, True)
    generateUsageOfMacroDefinitions(
        fieldsNotRepeated, file, fullClassNameUnder)
    generateUsageOfMacroDefinitions(
        fieldsRepeated, file, fullClassNameUnder, True)
    file.write("    } data;\n")
    file.write("};\n\n")


def makeMessageStructBody(file, className, Message):
    def returnStrNumber(attribute, isRepeated=False):
        name = attribute[0]
        type = attribute[1].ctype
        ret = f"<< \", \\\"{name}"
        prefix = "data."
        if isRepeated:
            prefix += "repeated[i]."
            ret += "[\" << i << \"]"
        ret += "\\\":\" << "
        if "reserved" in name:
            return ret + "\"0\""
        if type != "":
            typeSplit = type.split("[")
            if len(typeSplit) == 2:
                nameSplitArray = typeSplit[1][:-1]
                nameSplitArray = int(nameSplitArray)
                ret += f"\"[\" << std::to_string({prefix}{name}[0])"
                for i in range(nameSplitArray-1):
                    ret += f"<< \",\" << std::to_string({prefix}{name}[{i+1}])"
                ret += "<< \"]\""
                return ret
        return ret + f"std::to_string({prefix}{name})"

    def returnFlags(attribute, isRepeated=False):
        name = attribute[0]
        ret = ""
        bitfield = getattr(attribute[1], "bitfield", {})
        prefix = "data."
        if isRepeated:
            index = "i"
            prefix += "repeated_"
        else:
            index = ""
        keys = list(bitfield.keys())
        if len(keys) > 0:
            ret += f" << \", \\\"_{name}\\\":{{"
            ret += f"\\\"{keys[0]}\\\":\" << std::to_string({prefix}{getBitName(attribute, keys[0])}({index}))"
            for bit in keys[1:]:
                ret += f" << \", \\\"{bit}\\\":\" << std::to_string({prefix}{getBitName(attribute, bit)}({index}))"
            ret += " << \"}\""
        return ret

    messageName = getMessageName(
        Message, withUBX=False, withMessageClass=False)
    fullClassName = "{}::{}".format(className, messageName)
    fullClassNameUnder = "{}_{}".format(className, messageName)
    fields = getClassMembers(Message.Fields)
    fieldsNotRepeated = list(
        filter(lambda f: not isFieldRepeated(f[1]), fields))
    fieldsNotRepeated = sorted(fieldsNotRepeated, key=lambda x: x[1].ord)
    repeated = list(filter(lambda f: isFieldRepeated(f[1]), fields))
    if repeated:
        repeated = repeated[0]
        fieldsRepeated = getClassMembers(repeated[1])
        fieldsRepeated = sorted(fieldsRepeated, key=lambda x: x[1].ord)
    else:
        fieldsRepeated = None
    file.write(
        f"uint8_t ubx::{fullClassName}::getClassId(void) const {{ return ubx::{className}::classID; }}\n")
    file.write(
        f"uint8_t ubx::{fullClassName}::getMessageId(void) const {{ return messageID; }}\n")
    file.write(
        f"const std::string &ubx::{fullClassName}::getClassName(void) const {{ return classIDName; }}\n")
    file.write(
        f"std::string ubx::{fullClassName}::getMessageName(void) const {{ return std::string(\"{messageName}\"); }};\n")
    file.write(
        f"std::string ubx::{fullClassName}::getDescription(void) const {{\n    std::stringstream ret;\n")
    file.write("    ret << \"{")
    file.write("\\\"classId\\\":\" << std::to_string(getClassId()) << \",")
    file.write("\\\"messageId\\\":\" << std::to_string(getMessageId()) << \",")
    file.write("\\\"classIdName\\\":\\\"\" << getClassName() << \"\\\",")
    file.write("\\\"messageIdName\\\":\\\"\" << getMessageName() << \"\\\"\";")
    if len(fieldsNotRepeated):
        file.write(
            f"\n    ret {returnStrNumber( fieldsNotRepeated[0])}{returnFlags(fieldsNotRepeated[0])}")
        for field in fieldsNotRepeated[1:]:
            file.write(f" {returnStrNumber(field)}{returnFlags(field)}")
        file.write(f";")
    if fieldsRepeated:
        file.write(
            f"\n    for (uint16_t i = 0; i < repeatedLen; i++) {{ ret {returnStrNumber(fieldsRepeated[0], True)}{returnFlags(fieldsRepeated[0], True)}")
        for field in fieldsRepeated[1:]:
            file.write(
                f" {returnStrNumber(field, True)}{returnFlags(field, True)}")
        file.write(";}")
    file.write("\n    ret << \"}\";\n")
    file.write("    return ret.str();\n}\n")
    file.write(
        f"uint8_t* ubx::{fullClassName}::getDataStartAddress(void) const {{ return (uint8_t*)&data; }}\n")
    file.write(
        f"uint16_t ubx::{fullClassName}::getDataSize(void) const {{ return ")
    if len(fieldsNotRepeated) == 0 and not (fieldsRepeated is not None and len(fieldsRepeated) > 0):
        file.write("0")
    else:
        file.write("sizeof(data)")
    if fieldsRepeated:
        file.write(" + (repeatedLen * repeatedSize)")
    file.write("; }\n")
    generateUsageOfMacroDefinitionsBody(
        fieldsNotRepeated, file, fullClassName, fullClassNameUnder)
    generateUsageOfMacroDefinitionsBody(
        fieldsRepeated, file, fullClassName, fullClassNameUnder, True)
    if fieldsRepeated:
        file.write(
            f"const uint16_t ubx::{fullClassName}::repeatedSize = sizeof(struct ubx::{fullClassName}::_data::_repeated);\n")


def makeStructBodyRepeated(file, Repeated):
    fields = getClassMembers(Repeated)
    fields = sorted(fields, key=lambda x: x[1].ord)
    for name, Type in fields:
        file.write("            {}\n".format(makeMemberDecl(Type.ctype, name)))


def generateCPP_main():
    def caseOutput(file, fields, className, messageName, indent=""):
        repeated = list(
            filter(lambda f: isFieldRepeated(f[1]), getClassMembers(fields)))
        print()
        print(className)
        print(messageName)
        print(getClassMembers(fields))
        print(repeated)
        repeatLen = ""
        if repeated:
            repeatLen= " + 2U"
        file.write(
            indent+f"uint8_t *heap = new uint8_t[sizeof(ubx::SerializeCommon) + len{repeatLen}];\n")
        file.write(
            indent+f"ret = shared_ptr<{className}::{messageName}>(new (heap) {className}::{messageName});\n")
        if repeated:
            file.write(
                indent+f"dynamic_cast<{className}::{messageName}*>(ret.get())->repeatedLen = (len - sizeof(struct {className}::{messageName}::_data)) / sizeof(struct {className}::{messageName}::_data::_repeated);\n")

    topdir = Path(__file__).parent.parent
    cppsrcdir = topdir.joinpath("lang", "cpp", "src")
    for Cls in getClassesInModule(UBX):
        className = getMessageName(Cls, withUBX=False, withMessageName=False)
        fileName = cppsrcdir.joinpath("messages", className+".hpp")
        shortName = fileName.relative_to(topdir)  # Starts with lang/cpp...
        file = open(fileName, 'w+')
        file.write("// File {}\n".format(shortName))
        file.write("// Auto-generated by pyUBX {} v{} on {}\n".format(
            os.path.basename(__file__),
            __version__,
            datetime.datetime.now().isoformat())
        )
        file.write("// See https://github.com/mayeranalytics/pyUBX\n")
        file.write("// DO NOT MODIFY THIS FILE!\n")
        ifndefName = "__"+className.upper()+"_H__"
        file.write("\n#ifndef {}\n".format(ifndefName))
        file.write("#define {}\n".format(ifndefName))
        file.write("#include \"Ubx.hpp\"\n\n")
        if Cls.__doc__ is not None:
            file.write(makeComment(Cls.__doc__) + "\n")
        file.write("namespace ubx\n{\n")
        file.write("namespace {} {{\n".format(className))

        for _, Message in getClassMembers(Cls, inspect.isclass):
            file.write(f"\nconstexpr uint8_t classID = {Message._class};\n\n")
            break
        for _, Message in getClassMembers(Cls, inspect.isclass):
            makeMessageStruct(file, className, Message)

        file.write("}} // namespace {}\n".format(className))
        file.write("} // namespace ubx\n")
        file.write("#endif // ifndef {}\n".format(ifndefName))
        file.close()
        sys.stderr.write("Wrote {}\n".format(shortName))

        fileNameCpp = cppsrcdir.joinpath("messages", className+".cpp")
        shortName = fileNameCpp.relative_to(topdir)  # Starts with lang/cpp...
        file = open(fileNameCpp, 'w+')
        file.write("// File {}\n".format(shortName))
        file.write("// Auto-generated by pyUBX {} v{} on {}\n".format(
            os.path.basename(__file__),
            __version__,
            datetime.datetime.now().isoformat())
        )
        file.write("// See https://github.com/mayeranalytics/pyUBX\n")
        file.write("// DO NOT MODIFY THIS FILE!\n")
        file.write(f"\n #include \"{className}.hpp\"\n")
        file.write("#include <sstream>\n\n")

        file.write(f"const std::string classIDName(\"{className}\");\n\n")
        for _, Message in getClassMembers(Cls, inspect.isclass):
            makeMessageStructBody(file, className, Message)
        file.close()

    # make parseUbxMessage.hpp
    fileName = cppsrcdir.joinpath("parseUbxMessage.hpp")
    shortName = fileName.relative_to(topdir)  # Starts with lang/cpp...
    file = open(fileName, 'w')
    file.write("// File {}\n".format(shortName))
    file.write("// Auto-generated by pyUBX {} v{} on {}\n".format(
        os.path.basename(__file__),
        __version__,
        datetime.datetime.now().isoformat())
    )
    file.write("// See https://github.com/mayeranalytics/pyUBX\n")
    file.write("// DO NOT MODIFY THIS FILE!\n")
    # ifndef
    ifndefName = "__PARSE_UBX_MESSAGE_H__"
    file.write("\n#ifndef {}\n".format(ifndefName))
    file.write("#define {}\n".format(ifndefName))
    file.write("\n")
    file.write("#include \"parseUbxMessageBase.hpp\"\n")
    # include all files
    for Cls in getClassesInModule(UBX):
        className = getMessageName(Cls, withUBX=False, withMessageName=False)
        file.write("#include \"messages/{}.hpp\"\n".format(className))
    file.write("\nnamespace ubx\n{\n")
    file.write(
        "    class ParseUbxMessage : public ParseUbxMessageBase\n    {\n")
    file.write("        public:\n")
    file.write("            ParseUbxMessage():ParseUbxMessageBase(){};\n")
    file.write("        protected:\n")
    file.write("            virtual std::shared_ptr<SerializeCommon> createUbx(const uint8_t *buf, uint16_t len, uint8_t classId, uint8_t messageID, bool isGet = true) const override;\n")
    file.write("    };\n")
    file.write("}\n")
    file.write("#endif // #define {}\n".format(ifndefName))
    file.close()
    sys.stderr.write("Wrote {}\n".format(shortName))

    # make parseUbxMessage.cpp
    fileName = cppsrcdir.joinpath("parseUbxMessage.cpp")
    shortName = fileName.relative_to(topdir)  # Starts with lang/cpp...
    file = open(fileName, 'w')
    file.write("// File {}\n".format(shortName))
    file.write("// Auto-generated by pyUBX {} v{} on {}\n".format(
        os.path.basename(__file__),
        __version__,
        datetime.datetime.now().isoformat())
    )
    file.write("// See https://github.com/mayeranalytics/pyUBX\n")
    file.write("// DO NOT MODIFY THIS FILE!\n")
    file.write("#include <cstring>\n")
    file.write("#include \"parseUbxMessage.hpp\"\n")
    file.write("\nusing namespace std;\n")
    file.write("using namespace ubx;\n\n")
    file.write(
        "std::shared_ptr<SerializeCommon> ParseUbxMessage::createUbx(const uint8_t *buf, uint16_t len, uint8_t classId, uint8_t messageID, bool isGet) const\n{\n")
    file.write("    shared_ptr<SerializeCommon> ret = nullptr;\n\n")
    file.write("    switch(classId)\n    {\n")
    for Cls in getClassesInModule(UBX):
        className = getMessageName(Cls, withUBX=False, withMessageName=False)
        file.write(
            "        case ::{}::classID: // Message class {}\n        {{\n".format(className, className))
        file.write("            switch(messageID)\n            {\n")
        messagesTypes = {}
        for messageName, Message in getClassMembers(Cls, inspect.isclass):
            messageName1 = messageName.split("_GET")[0]
            if messageName1 not in messagesTypes:
                if getattr(Message, "_hideParse", False):
                    continue
                messagesTypes[messageName1] = {"general": None, "get": None}
            if messageName1 == messageName:
                messagesTypes[messageName1]["general"] = Message.Fields
            else:
                messagesTypes[messageName1]["get"] = Message.Fields
        for messageNameKey in messagesTypes:
            if messagesTypes[messageNameKey]["general"] != None:
                messageName = messageNameKey
            else:
                messageName = messageNameKey+"_GET"
            file.write("                case {}::{}::messageID: // Message {}-{}\n                {{\n".format(
                className, messageName, className, messageName))
            indent = "                    "
            if messagesTypes[messageNameKey]["general"] != None and messagesTypes[messageNameKey]["get"] != None:
                indent += "    "
                file.write(
                    "                    if (isGet)\n                    {\n")
                caseOutput(
                    file,  messagesTypes[messageNameKey]["get"], className, messageNameKey+"_GET", indent)
                file.write(
                    "                    }\n                    else\n                    {\n")
                caseOutput(
                    file,  messagesTypes[messageNameKey]["general"], className, messageNameKey, indent)
                file.write("                    }\n")
            elif messagesTypes[messageNameKey]["general"]:
                caseOutput(
                    file,  messagesTypes[messageNameKey]["general"], className, messageNameKey, indent)
            else:
                caseOutput(
                    file,  messagesTypes[messageNameKey]["get"], className, messageNameKey+"_GET", indent)
            file.write("                    break;\n                }\n")
        file.write(
            "                default:\n                {\n                    break;\n                }\n")
        file.write("            }\n")
        file.write("            break;\n        }\n")
    file.write("        default:\n        {\n            break;\n        }\n")
    file.write("    }\n")
    file.write("    if (ret != nullptr)\n    {\n")
    file.write("        (void)memcpy(ret->getDataStartAddress(), buf, len);\n")
    file.write("    }\n\n")
    file.write("    return ret;\n")
    file.write("}\n")
    file.close()
    sys.stderr.write("Wrote {}\n".format(shortName))


if __name__ == '__main__':
    generateCPP_main()
