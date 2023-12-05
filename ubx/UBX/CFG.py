"""Configuration Input Messages: Set Dynamic Model, Set DOP Mask, Set Baud Rate, etc."""

from ubx.UBXMessage import UBXMessage, initMessageClass, addGet
import struct
from ubx.Types import U1, U2, U4, X2, X4, U, I2, I4, X, X1


@initMessageClass
class CFG:
    U"""Message class CFG."""

    _class = 0x06

    @addGet
    class GNSS:
        u"""GNSS system configuration. §31.11.10."""

        _id = 0x3E

        class Fields:
            msgVer = U1(1)
            numTrkChHw = U1(2)
            numTrkChUse = U1(3)
            numConfigBlocks = U1(4)

            class Repeated:
                gnssId = U1(
                    1,
                    allowed={
                        0: 'GPS',
                        1: 'SBAS',
                        2: 'Galileo',
                        3: 'BeiDou',
                        4: 'IMES',
                        5: 'QZSS',
                        6: 'GLONASS',
                    })
                resTrkCh = U1(2)
                maxTrkCh = U1(3)
                reserved = U1(4)
                flags = X4(5, bitfield={
                    "enable": 0,
                    "sigCfgMask": {"s": 16, "e": 23}
                })

    @addGet
    class PM2:
        u"""§31.11.20 Extended Power Management configuration."""

        _id = 0x3B

        class Fields:
            version = U1(1, allowed={
                2: "this_version"
            })  # Message version (0x02 for this version)
            reserved1 = U1(2)  # Reserved
            # Maximum time to spend in Acquisition state. If 0: bound disabled (see maxStartupStateDur). (not supported in protocol versions less than 17), (not supported in protocol versions 23 to 23.01)
            maxStartupStateDur = U1(3, allowed={
                0: "bound disabled"
            })
            reserved2 = U1(4)  # Reserved
            flags = X4(5, bitfield={
                "optTarget": {"s": 1, "e": 3},
                "extintSel": 4,
                "extintWake": 5,
                "extintBackup": 6,
                "extintInactiv": 7,
                "limitPeakCurr": {"s": 8, "e": 9},
                "waitTimeFix": 10,
                "updateRTC": 11,
                "updateEPH": 12,
                "doNotEnterOff": 16,
                "mode": {"s": 17, "e": 18}
            })  # PSM configuration flags (see graphic below)
            # ms  Position update period. If set to 0, the receiver will never retry a fix and it will wait for external events
            updatePeriod = U4(6, allowed={
                0: "external event"
            })
            # ms  Acquisition retry period if previously failed. If set to 0, the receiver will never retry a startup (not supported in protocol versions 23 to 23.01)
            searchPeriod = U4(7, allowed={
                0: "never retry"
            })
            # ms  Grid offset relative to GPS start of week (not supported in protocol versions 23 to 23.01)
            gridOffset = U4(8)
            # s  Time to stay in Tracking state (not supported in protocol versions 23 to 23.01)
            onTime = U2(9)
            minAcqTime = U2(10)  # s  minimal search time
            reserved3 = U(11, 20) 	# Reserved
            # ms  inactivity time out on EXTINT pint if enabled
            extintInactivityMs = U4(12)

    class PRT:
        u"""§31.11.22.4 Port Configuration."""

        _id = 0x00

        class Fields:
            portID = U1(1, allowed={
                0: "i2c",
                1: "UART1",
                2: "UART2",
                3: "USB",
                4: "SPI"
            })
            reserved1 = U1(2)
            txReady = X2(3, bitfield={
                "en": 0,
                "pol": 1,
                "pin": {"s": 2, "e": 6},
                "thres": {"s": 7, "e": 15}
            }
            )
            mode = X4(4, bitfield={
                "charLen": {"s": 6, "e": 7},
                "parity": {"s": 9, "e": 11},
                "nStopBits": {"s": 12, "e": 13}
            }
            )
            baudRate = U4(5)
            inProtoMask = X2(6, bitfield={
                "inUbx": 0,
                "inNmea": 1,
                "inRtcm": 2,
                "inRtcm3": 5
            }
            )
            outProtoMask = X2(7, bitfield={
                "outUbx": 0,
                "outNmea": 1,
                "inRtcm3": 5
            }
            )
            flags = X2(8, bitfield={
                "extendedTxTimeout": 1
            }
            )
            reserved2 = U2(9)

    class PRT_GET:
        u"""§31.11.22.4 Port Configuration."""

        _id = 0x00

        class Fields:
            portID = U1(1)

    @addGet
    class RATE:
        u"""§31.11.24 Navigation/Measurement Rate Settings."""

        _id = 0x08

        class Fields:
            measRate = U2(1)
            navRate = U2(2)
            timeRef = U2(
                3,
                allowed={
                    0: "UTC time",
                    1: "GPS time",
                    2: "GLONASS time",
                    3: "BeiDou time",
                    4: "Galileo time",
                    5: "NavIC time"
                })

    class RST:
        u"""32.10.29.1 Reset receiver / Clear backup data structures

        Do not expect this message to be acknowledged by the receiver.
        • Newer FW version will not acknowledge this message at all.
        • Older FW version will acknowledge this message but the acknowledge may not
        be sent completely before the receiver is reset.
        Notes:
        • If Galileo is enabled, UBX-CFG-RST Controlled GNSS start must be followed by
        UBX-CFG-CFG to save current configuration to BBR and then by UBX-CFG-RST
        with resetMode set to Hardware reset.
        • If Galileo is enabled, use resetMode Hardware reset instead of Controlled
        software reset or Controlled software reset (GNSS only).
        """

        _id = 0x04

        class Fields:
            navBbrMask = X2(1, allowed={
                    0:"HOT_START",
                    1:"WARM_START",
                    0xFFFF: "COLD_START"
                })
            resetMode = U1(2, allowed={
                    0:"HW",
                    1:"SW",
                    2:"SW_GNSS_ONLY",
                    3: "HW_AFTER_SHUTDOWN",
                    8: "STOP",
                    9: "START",
                })
            reserved1 = U1(3)   # reserved


    @addGet
    class RXM:
        u"""§31.11.27 RXM configuration.

        For a detailed description see section 'Power Management'.
        """

        _id = 0x11

        class Fields:
            reserved1 = U1(1)   # reserved
            lpMode = U1(        # Low Power Mode
                2,
                allowed={
                    0: "Continuous mode",
                    1: "Power save mode",
                    4: "Continuous mode"    # for ver>=14 0 and 4 are the same
                })

    @addGet
    class TP5:
        u"""§31.11.32.3 Time Pulse Parameters."""

        _id = 0x31

        class Fields:
            # Time pulse selection (0 = TIMEPULSE, 1 = TIMEPULSE2)
            tpIdx = U1(1)
            version = U1(2)  # Message version (0x00 for this version)
            reserved2 = U2(3)
            antCableDelay = I2(4)  # Antenna cable delay
            rfGroupDelay = I2(5)  # RF group delay
            # Frequency or period time, depending on setting of bit 'isFreq'
            freqPeriod = U4(6)
            # Frequency or period time when locked to GPS time, only used if 'lockedOtherSet' is set
            freqPeriodLock = U4(7)
            # Pulse length or duty cycle, depending on 'isLength'
            pulseLenRatio = U4(8)
            # Pulse length or duty cycle when locked to GPS time, only used if 'lockedOtherSet' is set
            pulseLenRatioLock = U4(9)
            userConfigDelay = I4(10)  # User configurable time pulse delay
            flags = X4(11)  # Configuration flags

    class TP5_GET:
        u"""§31.11.32.2 Poll Time Pulse Parameters."""

        _id = 0x00

        class Fields:
            # Time pulse selection (0 = TIMEPULSE, 1 = TIMEPULSE2)
            tpIdx = U1(1)

    class CFG:
        u"""32.10.3.1 Clear, save and load configurations"""

        _id = 0x09

        class Fields:
            clearMask = X4(1, bitfield={
                "ioPort": 0,
                "msgConf": 1,
                "infMsg": 2,
                "navConf": 3,
                "rxmConf": 4,
                "senConf": 8,
                "rinvConf": 9,
                "antConf": 10,
                "logConf": 11,
                "ftsConf": 12,
            })
            saveMask = X4(2, bitfield={
                "ioPort": 0,
                "msgConf": 1,
                "infMsg": 2,
                "navConf": 3,
                "rxmConf": 4,
                "senConf": 8,
                "rinvConf": 9,
                "antConf": 10,
                "logConf": 11,
                "ftsConf": 12,
            })
            loadMask = X4(3, bitfield={
                "ioPort": 0,
                "msgConf": 1,
                "infMsg": 2,
                "navConf": 3,
                "rxmConf": 4,
                "senConf": 8,
                "rinvConf": 9,
                "antConf": 10,
                "logConf": 11,
                "ftsConf": 12,
            })
            deviceMask = X1(4, bitfield={
                "devBBR": 0,
                "devFlash": 1,
                "devEEPROM": 2,
                "devSpiFlash": 4
            })

    class INF:
        u"""GNSS system configuration. §32.10.15.2"""

        _id = 0x02

        class Fields:
            class Repeated:
                protocolID = U1(1, allowed={
                    0: "UBX protocol",
                    1: "NMEA protocol"
                })
                reserved1 = U(2, 3)
                infMsgMask = X1(3, bitfield={
                    "ERROR": 0,
                    "WARNING": 1,
                    "NOTICE": 2,
                    "TEST": 3,
                    "DEBUG": 4,
                })
                infMsgMaskUnused = X(4, 5)

    class LOGFILTER:
        u"""32.10.17.1 Data logger configuration"""

        _id = 0x47

        class Fields:
            version = U1(1)
            flags = X1(2, bitfield={
                "recordEnabled": 0,
                "psmOncePerWakupEnabled": 1,
                "applyAllFilterSettings": 2
            })
            minInterval = U2(3)
            timeThreshold = U2(4)
            speedThreshold = U2(5)
            positionThreshold = U4(6)

    class MSG:
        u"""32.10.18.2 Set message rate(s)"""

        _id = 0x01

        class Fields:
            msgClass = U1(1)
            msgID = U1(2)
            rate = U(3, 6)

    class NAVX5:
        u"""§32.10.20.2 Navigation engine expert settings."""

        _id = 0x23

        class Fields:
            version = U2(1)
            mask1 = X2(2, bitfield={
                "minMax": 2,
                "minCno": 3,
                "initial3dfix": 6,
                "wknRoll": 9,
                "ackAid": 10,
                "ppp": 13,
                "aop": 14
            })
            mask2 = X4(3, bitfield={
                "adr": 6
            })
            reserved1 = U2(4)
            minSVs = U1(5)
            maxSVs = U1(6)
            minCNO = U1(7)
            reserved2 = U1(8)
            iniFix3D = U1(9, allowed={
                1: "initial fix must be 3D"
            })
            reserved3 = U2(10)
            ackAiding = U1(11, allowed={
                1: "issue acknowledgements for assistance"
            })
            wknRollover = U2(12)
            sigAttenCompMode = U1(13)
            reserved4 = U(14, 5)
            usePPP = U1(15, allowed={
                1: "Precise Point Positioning"
            })
            aopCfg = U1(16, bitfield={
                "useAOP": 0
            })
            reserved5 = U2(17)
            aopOrbMaxErr = U2(18)
            reserved6 = U4(19)
            reserved7 = U(20, 3)
            useAdr = U1(21, allowed={
                0: "disable ADR sensor fusion",
                1: "enable ADR sensor fusion"
            })

    @addGet
    class PMS:
        u"""32.10.24.1 Power mode setup"""

        _id = 0x86

        class Fields:
            version = U1(1, allowed={
                0: "this_version"
            })
            powerSetupValue = U1(2, allowed={0x00: "Full power",
                                             0x01: "Balanced",
                                             0x02: "Interval",
                                             0x03: "Aggressive with 1 Hz",
                                             0x04: "Aggressive with 2 Hz",
                                             0x05: "Aggressive with 4 Hz",
                                             0xFF: "Invalid"
                                             })
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
