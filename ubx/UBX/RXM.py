"""Receiver Manager Messages: i.e. Satellite Status, RTC Status."""

from ubx.UBXMessage import initMessageClass, addGet
from ubx.Types import CH, U, U1, U4, I4, X4

@initMessageClass
class RXM:
    """Message class RXM."""

    _class = 0x02

    class IMES:
        """Indoor Messaging System information"""

        _id = 0x61

        class Fields:
            numTx = U1(1)
            version = U1(2, allowed = {1 : "this_version"})
            reserved1 = U(3,2)
            class Repeated:
                reserved2 = U1(1)
                txId = U1(2)
                reserved3 = U(3,3)
                cno = U1(4)
                reserved4 = U(5,2)
                doppler = I4(6)
                position1_1 = X4(7, bitfield={
                    "pos1Floor": {"s": 0, "e": 7},
                    "pos1Lat": {"s": 8, "e": 30}})
                position1_2 = X4(8, bitfield={
                    "pos1Lon": {"s": 0, "e": 23},
                    "pos1Valid": 24})
                position2_1 = X4(9, bitfield={
                    "pos2Floor": {"s": 0, "e": 8},
                    "pos2Alt": {"s": 9, "e": 20},
                    "pos2Acc": {"s": 21, "e": 22},
                    "pos2Valid": 23})
                lat = I4(10)
                lon = I4(11)
                shortIdFrame = X4(12,bitfield={
                    "shortId": {"s": 0, "e": 11},
                    "shortValid": 12,
                    "shortBoundary": 13})
                mediumIdLSB = U4(13)
                mediumId_2 = X4(14, bitfield={
                    "mediumIdMSB": 0,
                    "mediumValid": 1,
                    "mediumboundary": 2})

    class MEASX:
        """TODO: MISSING IMPLEMENTATION"""
        _id = 0x14

        class Fields:
                pass

    class PMREQ:
        u"""Power management request"""

        _id = 0x41

        class Fields:
            duration = U4(1)
            flags = X4(2,bitfield={
                    "backup": 1})

    class PMREQ2:
        """Power management request"""

        _id = 0x41

        class Fields:
            version = U1(1, allowed = {0 : "this_version"})
            reserved1 = U(2, 3)
            duration = U4(3)
            flags = X4(4,bitfield={
                    "backup": 1,
                    "force": 2})
            wakeupSources = X4(5,bitfield={
                    "uartrx": 3,
                    "extint0": 5,
                    "extint1": 6,
                    "spics": 7})

    class RAWX:
        """TODO: MISSING IMPLEMENTATION"""

        _id = 0x15

        class Fields:
                pass

    class RLM:
        """TODO: MISSING IMPLEMENTATION"""
        _id = 0x59

        class Fields:
                pass

    class RTCM:
        """TODO: MISSING IMPLEMENTATION"""

        _id = 0x32

        class Fields:
                pass

    class SFRBX:
        """TODO: MISSING IMPLEMENTATION"""

        _id = 0x13

        class Fields:
                pass

    class SVSI:
        """TODO: MISSING IMPLEMENTATION"""

        _id = 0x20

        class Fields:
                pass
