"""Configuration Input Messages: Set Dynamic Model, Set DOP Mask, Set Baud Rate, etc."""

from UBXMessage import UBXMessage, initMessageClass, addGet
import struct
from Types import U1, U2


@initMessageClass
class CFG:
    """Message class CFG."""

    _class = 0x06

    @addGet
    class PMS:

        _id = 0x86

        class Fields:
            version = U1(1)
            powerSetupValue = U1(2)
            period = U2(3)
            onTime = U2(4)
            reserved = U2(5)

        class Set(UBXMessage):
            def __init__(self, powerSetupValue=1, period=0, onTime=0):
                payload = struct.pack(
                    '<BBhhBB', 0, powerSetupValue, period, onTime, 0, 0
                )
                UBXMessage.__init__(
                    self, CFG._class, CFG.PMS._id, payload
                )

    @addGet
    class GNSS:

        _id = 0x3E

        class Fields:
            pass
