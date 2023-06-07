// File lang/cpp/src/messages/MGA.cpp
// Auto-generated by pyUBX generateCPP.py v0.2 on 2023-06-07T13:38:14.194355
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

 #include "MGA.hpp"
#include <sstream>

const std::string classIDName("MGA");

uint8_t ubx::MGA::ACK_DATA0::getClassId(void) const { return ubx::MGA::classID; }
uint8_t ubx::MGA::ACK_DATA0::getMessageId(void) const { return messageID; }
const std::string &ubx::MGA::ACK_DATA0::getClassName(void) const { return classIDName; }
std::string ubx::MGA::ACK_DATA0::getMessageName(void) const { return std::string("ACK_DATA0"); };
std::string ubx::MGA::ACK_DATA0::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"type\":" << std::to_string(data.type) << ", \"version\":" << std::to_string(data.version) << ", \"infoCode\":" << std::to_string(data.infoCode) << ", \"msgId\":" << std::to_string(data.msgId) << ", \"msgPayloadStart\":" << std::to_string(data.msgPayloadStart);
    ret << "}";
    return ret.str();
}
uint8_t* ubx::MGA::ACK_DATA0::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::MGA::ACK_DATA0::getDataSize(void) const { return sizeof(data); }
uint8_t ubx::MGA::FLASH_ACK::getClassId(void) const { return ubx::MGA::classID; }
uint8_t ubx::MGA::FLASH_ACK::getMessageId(void) const { return messageID; }
const std::string &ubx::MGA::FLASH_ACK::getClassName(void) const { return classIDName; }
std::string ubx::MGA::FLASH_ACK::getMessageName(void) const { return std::string("FLASH_ACK"); };
std::string ubx::MGA::FLASH_ACK::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"type\":" << std::to_string(data.type) << ", \"version\":" << std::to_string(data.version) << ", \"ack\":" << std::to_string(data.ack) << ", \"reserved1\":" << "0" << ", \"sequence\":" << std::to_string(data.sequence);
    ret << "}";
    return ret.str();
}
uint8_t* ubx::MGA::FLASH_ACK::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::MGA::FLASH_ACK::getDataSize(void) const { return sizeof(data); }
uint8_t ubx::MGA::FLASH_DATA::getClassId(void) const { return ubx::MGA::classID; }
uint8_t ubx::MGA::FLASH_DATA::getMessageId(void) const { return messageID; }
const std::string &ubx::MGA::FLASH_DATA::getClassName(void) const { return classIDName; }
std::string ubx::MGA::FLASH_DATA::getMessageName(void) const { return std::string("FLASH_DATA"); };
std::string ubx::MGA::FLASH_DATA::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"type\":" << std::to_string(data.type) << ", \"version\":" << std::to_string(data.version) << ", \"sequence\":" << std::to_string(data.sequence) << ", \"size\":" << std::to_string(data.size);
    for (uint16_t i = 0; i < repeatedLen; i++) { ret << ", \"data[" << i << "]\":" << std::to_string(data.repeated[i].data);}
    ret << "}";
    return ret.str();
}
uint8_t* ubx::MGA::FLASH_DATA::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::MGA::FLASH_DATA::getDataSize(void) const { return sizeof(data) + (repeatedLen * repeatedSize); }
const uint16_t ubx::MGA::FLASH_DATA::repeatedSize = sizeof(struct ubx::MGA::FLASH_DATA::_data::_repeated);
uint8_t ubx::MGA::FLASH_STOP::getClassId(void) const { return ubx::MGA::classID; }
uint8_t ubx::MGA::FLASH_STOP::getMessageId(void) const { return messageID; }
const std::string &ubx::MGA::FLASH_STOP::getClassName(void) const { return classIDName; }
std::string ubx::MGA::FLASH_STOP::getMessageName(void) const { return std::string("FLASH_STOP"); };
std::string ubx::MGA::FLASH_STOP::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"type\":" << std::to_string(data.type) << ", \"version\":" << std::to_string(data.version);
    ret << "}";
    return ret.str();
}
uint8_t* ubx::MGA::FLASH_STOP::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::MGA::FLASH_STOP::getDataSize(void) const { return sizeof(data); }
