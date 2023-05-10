from ubx.UBXMessage import UBXMessage, initMessageClass
from ubx.Types import U1, U2, U4, X2, X4, U, I2, I4, X, X1


@initMessageClass
class LOG:
    u"""Logging Messages: i.e. Log creation, deletion, info and retrieval"""

    _class = 0x21

    class CREATE:
        u"""32.14.2.1 Create log file"""

        _id = 0x07

        class Fields:
            version = U1(1)
            logCfg = X1(2, bitfield={
                "circular": 0
            })
            reserved1 = U1(3)
            logSize = U1(4, allowed={
                0: "maximum safe size",
                1: "minimum size",
                2: "user defined size"
            })
            userDefinedSize = U4(5)

    class ERASE:
        u"""32.14.3.1 Erase logged data"""

        _id = 0x03

        class Fields:
            pass

    class FINDTIME:
        u"""32.14.4.1 Find index of a log entry based on a given time"""

        _id = 0x0E

        class Fields:
            version = U1(1, allowed={
                0: "this_version"
            })
            type = U1(2, allowed={
                0: "request"
            })
            year = U2(3)
            month = U1(4)
            day = U1(5)
            hour = U1(6)
            minute = U1(7)
            second = U1(8)
            reserved1 = U1(9)

    class FINDTIME_GET:
        _id = 0x0E
        class Fields:
            version = U1(1)
            type = U1(2)
            reserved1 = U2(3)
            entryNumber = U4(4)

    class INFO:
        u"""32.14.5.1 Poll for log information"""

        _id = 0x08

        class Fields:
            pass

    class INFO_GET:
        u"""32.14.5.2 Log information"""

        _id = 0x08

        class Fields:
            version = U1(1)
            reserved1 = U(2, 3)
            filestoreCapacity = U4(3)
            reserved2 = U(4, 8)
            currentMaxLogSize = U4(5)
            currentLogSize = U4(6)
            entryCount = U4(7)
            oldestYear = U2(8)
            oldestMonth = U1(9)
            oldestDay = U1(10)
            oldestHour = U1(11)
            oldestMinute = U1(12)
            oldestSecond = U1(13)
            reserved3 = U1(14)
            newestYear = U2(15)
            newestMonth = U1(16)
            newestDay = U1(17)
            newestHour = U1(18)
            newestMinute = U1(19)
            newestSecond = U1(20)
            reserved4 = U1(21)
            status = X1(22, bitfield={
                "recording": 3,
                "inactive": 4,
                "circular": 5
            })
            reserved5 = U(23, 3)

    class RETRIEVE:
        u"""32.14.10.1 Request log data"""

        _id = 0x09

        class Fields:
            startNumber = U4(1)
            entryCount = U4(2)
            version = U1(3, allowed={
                0: "this_version"
            })
            reserved1 = U(4, 3)

    class RETRIEVEPOS:
        u"""32.14.7.1 Odometer log entry"""

        _id = 0x0b

        class Fields:
            entryIndex = U4(1)
            lon = I4(2)
            lat = I4(3)
            hMSL = I4(4)
            hAcc = U4(5)
            gSpeed = U4(6)
            heading = U4(7)
            version = U1(8)
            fixType = U1(9)
            year = U2(10)
            month = U1(11)
            day = U1(12)
            hour = U1(13)
            minute = U1(14)
            second = U1(15)
            reserved1 = U1(16)
            numSV = U1(17)
            reserved2 = U1(18)


    class RETRIEVEPOSEXTRA:
        u"""32.14.8.1 Position fix log entry"""

        _id = 0x0f

        class Fields:
            entryIndex = U4(1)
            version =U1(2,allowed={
                0: "this_version"
            })
            reserved1 =U1(3)
            year =U2(4)
            month =U1(5)
            day =U1(6)
            hour =U1(7)
            minute =U1(8)
            second =U1(9)
            reserved2 =U(10,3)
            distance =U4(11)
            reserved3 =U(12,12)
