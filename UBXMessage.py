#!/usr/bin/env python3
"""TODO."""

import struct
import inspect
from enum import Enum
import sys
import UBX


class MessageClass(Enum):
    """UBX Class IDs."""

    NAV = b'\x01'  # Navigation Results Messages: Position, Speed, Time, Acceleration, Heading, DOP, SVs used
    RXM = b'\x02'  # Receiver Manager Messages: Satellite Status, RTC Status
    INF = b'\x04'  # Information Messages: Printf-Style Messages, with IDs such as Error, Warning, Notice
    UPD = b'\x09'  # Firmware Update Messages: Memory/Flash erase/write, Reboot, Flash identification, etc.
    AID = b'\x0B'  # AssistNow Aiding Messages: Ephemeris, Almanac, other A-GPS data input
    TIM = b'\x0D'  # Timing Messages: Time Pulse Output, Time Mark Results
    ESF = b'\x10'  # External Sensor Fusion Messages: External Sensor Measurements and Status Information
    MGA = b'\x13'  # Multiple GNSS Assistance Messages: Assistance data for various GNSS
    LOG = b'\x21'  # Logging Messages: Log creation, deletion, info and retrieval
    SEC = b'\x27'  # Security Feature Messages
    HNR = b'\x28'  # High Rate Navigation Results Messages: High rate time, position, speed, heading


class UBXMessage(object):
    """Base class for UBX messages."""

    def __init__(self, msgClass, msgId, payload):
        """Instantiate UBXMessage from MessageClass, messageId and payload."""
        self.messageClass = bytes([msgClass])
        self.messageId = bytes([msgId])
        self.payload = payload

    def serialize(self):
        """Serialize the UBXMessage."""
        msg = struct.pack('cc', b'\xb5', b'\x62')
        msg += struct.pack('cc', self.messageClass, self.messageId)
        msg += struct.pack('<h', len(self.payload))
        msg += self.payload
        msg += struct.pack('>H', UBXMessage.Checksum(msg[2:]).get())
        return msg

    class Checksum:
        """Incrementally calculate UBX message checksums."""

        def __init__(self, msg=None):
            """Instantiate object.

            If msg is not None calculate the checksum of the message, otherwise
            instantiate the checksums to zero.
            """
            self.reset()
            if msg is not None:
                for i in msg:
                    self.update(bytes([i]))

        def reset(self):
            """Reset the checksums to zero."""
            self.a, self.b = 0x00, 0x00

        def update(self, byte):
            """Update checksums with byte."""
            i = ord(byte)
            self.a += i
            self.a &= 0xff
            self.b += self.a
            self.b &= 0xff

        def get(self):
            """Return the checksum (a 16-bit integer, ck_a is the MSB)."""
            return self.a * 256 + self.b


def _mkFieldStructPack(Fields):
    # The following is a list of (name, formatChar) tuples, such as
    # [(1, 'clsID', 'B'), (2, 'msgID', 'B')]
    once = [
        (v.ord, k, v.fmt)
        for k, v in Fields.__dict__.items()
        if not k.startswith('__') and k != 'Repeated'
    ]
    once.sort()
    repeated = Fields.__dict__.get('Repeated')
    repeated = [] if repeated is None else _mkFieldStructPack(repeated)
    return {
        'once': ("".join([v for (o, k, v) in once]),    # struct pack string
                 [k for (o, k, v) in once]),            # list of var names
        'repeat': repeated
        }


def _nameAndFmt(fieldStructPack, length):
    packFmt, varNames = fieldStructPack['once']
    repeat = fieldStructPack['repeat']
    if repeat:
        packFmtRepeat, varNamesRepeat = repeat['once']
        nOnce = struct.Struct(packFmt).size
        nRepeat = struct.Struct(packFmtRepeat).size
        N = (length - nOnce) // nRepeat
        if nOnce + N * nRepeat != length:
            errmsg = "message length {} does not match {}"\
                     .format(length, nOnce + N * nRepeat)
            raise Exception(errmsg)
        packFmt = packFmt + N * packFmtRepeat
        varNamesRepeat = _flatten(list(
            map(lambda i: list(map(lambda s: s+"_"+str(i),
                                   varNamesRepeat)
                              ),
                range(1, N+1))
            )
        )
        varNames = varNames + varNamesRepeat
    return varNames, packFmt


def _flatten(l):
    return [item for sublist in l for item in sublist]


def initMessageClass(cls):
    """Decorator for the python class representing a UBX message class.

    It adds a dict with name '_lookup' that maps UBX message ID to python
    subclass.
    """
    cls_name = cls.__name__
    subClasses = [c for c in cls.__dict__.values() if type(c) == type]

    lookup = dict([(getattr(subcls, '_id'), subcls) for subcls in subClasses])
    setattr(cls, "_lookup", lookup)

    for sc in subClasses:
        if sc.__dict__.get('Fields') is None:       # 'Fields' must be present
            raise Exception(
                "Class {}.{} has no Fields"
                .format(cls.__name__, sc.__name__)
            )
        # add __init__ to subclass if necessary
        if sc.__dict__.get('__init__') is None:
            def __init__(self, msg):
                fieldStructPack = _mkFieldStructPack(self.Fields)
                varNames, packFmt = _nameAndFmt(fieldStructPack, len(msg))
                if not varNames:
                    errmsg = 'No variables found in UBX.{}.{}.'\
                             .format(cls_name, sc.__name__)
                    errmsg += ' Is the \'Fields\' class empty?'
                    raise Exception(errmsg)
                try:
                    values = struct.unpack(packFmt, msg)
                except Exception as e:
                    errmsg = "{}, message length is {}".format(e, len(msg))
                    raise Exception(errmsg) from None
                if len(values) != len(varNames):
                    errmsg = "Mismatch: {} values, but {} variables!"\
                             .format(len(values), len(varNames))
                    raise Exception(errmsg)
                for (i, name) in enumerate(varNames):
                    setattr(self, name, values[i])
                setattr(self, '_len', len(msg))
            setattr(sc, "__init__", __init__)
        # add __str__ to subclass if necessary
        if sc.__dict__.get('__str__') is None:
            def __str__(self):
                fieldStructPack = _mkFieldStructPack(self.Fields)
                varNames, packFmt = _nameAndFmt(fieldStructPack, self._len)
                s = "{}-{}".format(cls_name, type(self).__name__)
                for name in varNames:
                    s += "\n  {}=0x{:02x}".format(name, getattr(self, name))
                return s
            setattr(sc, "__str__", __str__)
    return cls


def classFromMessageClass():
    """Look up the python class corresponding to a UBX message class.

    The result is something like
    [(5, UBX.ACK.ACK), (6, UBX.CFG.CFG), (10, UBX.MON.MON)]
    """
    return dict([
        (getattr(v, '_class'), v)
        for (k, v) in inspect.getmembers(sys.modules["UBX"], inspect.isclass)
        if v.__name__ not in [
            "UBXMessage", "U1", "I1", "X1", "U2", "I2", "X2",
            "U4", "I4", "X4", "R4", "R8", "CH"
            ]
    ])


def parseUBXMessage(msgClass, msgId, payload):
    """Parse a UBX message from message class, message ID and payload."""
    Cls = classFromMessageClass().get(msgClass)
    if Cls is None:
        raise Exception("Cannot parse message class {}".format(msgClass))
    Subcls = Cls._lookup.get(msgId)
    if Subcls is None:
        raise Exception("Cannot parse message ID {} of message class {}"
                        .format(msgId, msgClass.__name__))
    return Subcls(payload)


def formatByteString(s):
    """Return a readable string of hex numbers."""
    return " ".join('{:02x}'.format(x) for x in s)


def stringFromByteString(bs):
    """Extract a null-terminated string from bytestring."""
    i = bs.find(0)
    return "" if i < 0 else bs[0:i].decode('ascii')


def addGet(cls):
    """Add a Get function to the subclass."""
    class Get(UBXMessage):
        def __init__(self):
            # this only works because class and module have the same name!
            _class = eval(cls.__module__)._class
            UBXMessage.__init__(self, _class, cls._id, b'')
    setattr(cls, "Get", Get)
    return cls
