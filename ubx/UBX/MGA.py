from ubx.UBXMessage import UBXMessage, initMessageClass
from ubx.Types import U1, U2, U4, X2, X4, U, I2, I4, X, X1


@initMessageClass
class MGA:
    u"""Multiple GNSS Assistance Messages: i.e. Assistance data for various GNSS."""

    _class = 0x13

    class ACK_DATA0:
        u"""32.15.1.1 UBX-MGA-ACK-DATA0"""

        _id = 0x60

        class Fields:
            type = U1(1, allowed={
                0: "unused_by_receiver",
                1: "accepted_by_receiver"
            })
            version = U1(2, allowed={
                0: "this_version"
            })
            infoCode = U1(3, allowed={
                0: "accepted",
                1: "unknown_time",
                2: "unsupported_version",
                3: "wrong_message_size",
                4: "data_not_stored",
                5: "receiver_not_ready",
                6: "unknown_message_type"
            })
            msgId = U1(4)
            msgPayloadStart = U4(5)

    class FLASH_DATA:
        u"""32.15.5.1 UBX-MGA-FLASH-DATA"""

        _id = 0x21

        _hideParse = True  # workround for same id. Need parse FLASH_ACK

        class Fields:
            type = U1(1, allowed={
                1: "this_type"
            })
            version = U1(2, allowed={
                0: "this_version"
            })
            sequence = U2(3)
            size = U2(4)

            class Repeated:
                data = U1(1)

    class FLASH_STOP:
        u"""32.15.5.2 UBX-MGA-FLASH-STOP"""

        _id = 0x21

        _hideParse = True  # workround for same id. Need parse FLASH_ACK

        class Fields:
            type = U1(1, allowed={
                2: "this_type"
            })
            version = U1(2, allowed={
                0: "this_version"
            })

    class FLASH_ACK:
        u"""32.15.5.3 UBX-MGA-FLASH-ACK"""

        _id = 0x21

        class Fields:
            type = U1(1, allowed={
                3: "this_type"
            })
            version = U1(2, allowed={
                0: "this_version"
            })
            ack = U1(3, allowed={
                0: "ack",
                1: "nack",
                2: "nack2"
            })
            reserved1 = U1(4)
            sequence = U2(5)
