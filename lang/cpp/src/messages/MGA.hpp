// File lang/cpp/src/messages/MGA.hpp
// Auto-generated by pyUBX generateCPP.py v0.2 on 2023-06-07T12:40:39.302912
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

#ifndef __MGA_H__
#define __MGA_H__
#include "Ubx.hpp"

/* Multiple GNSS Assistance Messages: i.e. Assistance data for various GNSS.
 */
namespace ubx
{
namespace MGA {

constexpr uint8_t classID = 19;

/* 32.15.1.1 UBX-MGA-ACK-DATA0
 */
struct __attribute__((packed)) ACK_DATA0 : public SerializeCommon
{
    virtual uint8_t getClassId(void) const override;
    virtual uint8_t getMessageId(void) const override;
    virtual const std::string &getClassName(void) const override;
    virtual std::string getMessageName(void) const override;
    virtual std::string getDescription(void) const override;
    virtual uint8_t* getDataStartAddress(void) const override;
    virtual uint16_t getDataSize(void) const override;

    static constexpr uint8_t messageID = 96;

    struct __attribute__((packed)) _data {
        uint8_t type;
        uint8_t version;
        uint8_t infoCode;
        uint8_t msgId;
        uint32_t msgPayloadStart;

        enum _type_allowed{
            allowed_type_unused_by_receiver=0,
            allowed_type_accepted_by_receiver=1,
        };
        enum _version_allowed{
            allowed_version_this_version=0,
        };
        enum _infoCode_allowed{
            allowed_infoCode_accepted=0,
            allowed_infoCode_unknown_time=1,
            allowed_infoCode_unsupported_version=2,
            allowed_infoCode_wrong_message_size=3,
            allowed_infoCode_data_not_stored=4,
            allowed_infoCode_receiver_not_ready=5,
            allowed_infoCode_unknown_message_type=6,
        };
    } data;
};

/* 32.15.5.3 UBX-MGA-FLASH-ACK
 */
struct __attribute__((packed)) FLASH_ACK : public SerializeCommon
{
    virtual uint8_t getClassId(void) const override;
    virtual uint8_t getMessageId(void) const override;
    virtual const std::string &getClassName(void) const override;
    virtual std::string getMessageName(void) const override;
    virtual std::string getDescription(void) const override;
    virtual uint8_t* getDataStartAddress(void) const override;
    virtual uint16_t getDataSize(void) const override;

    static constexpr uint8_t messageID = 33;

    struct __attribute__((packed)) _data {
        uint8_t type;
        uint8_t version;
        uint8_t ack;
        uint8_t reserved1;
        uint16_t sequence;

        enum _type_allowed{
            allowed_type_this_type=3,
        };
        enum _version_allowed{
            allowed_version_this_version=0,
        };
        enum _ack_allowed{
            allowed_ack_ack=0,
            allowed_ack_nack=1,
            allowed_ack_nack2=2,
        };
    } data;
};

/* 32.15.5.1 UBX-MGA-FLASH-DATA
 */
struct __attribute__((packed)) FLASH_DATA : public SerializeCommon
{
    uint16_t repeatedLen; /* Set N-count array dimension of repeated structure. Do not serialize this byte*/
    static const uint16_t repeatedSize;
    virtual uint8_t getClassId(void) const override;
    virtual uint8_t getMessageId(void) const override;
    virtual const std::string &getClassName(void) const override;
    virtual std::string getMessageName(void) const override;
    virtual std::string getDescription(void) const override;
    virtual uint8_t* getDataStartAddress(void) const override;
    virtual uint16_t getDataSize(void) const override;

    static constexpr uint8_t messageID = 33;

    struct __attribute__((packed)) _data {
        uint8_t type;
        uint8_t version;
        uint16_t sequence;
        uint16_t size;

        struct __attribute__((packed)) _repeated {
            uint8_t data;
        } repeated [0]; /* [0] -> to pass compilation. Length is set by repeatedLen. Do not forget alloc enough space*/

        enum _type_allowed{
            allowed_type_this_type=1,
        };
        enum _version_allowed{
            allowed_version_this_version=0,
        };
    } data;
};

/* 32.15.5.2 UBX-MGA-FLASH-STOP
 */
struct __attribute__((packed)) FLASH_STOP : public SerializeCommon
{
    virtual uint8_t getClassId(void) const override;
    virtual uint8_t getMessageId(void) const override;
    virtual const std::string &getClassName(void) const override;
    virtual std::string getMessageName(void) const override;
    virtual std::string getDescription(void) const override;
    virtual uint8_t* getDataStartAddress(void) const override;
    virtual uint16_t getDataSize(void) const override;

    static constexpr uint8_t messageID = 33;

    struct __attribute__((packed)) _data {
        uint8_t type;
        uint8_t version;

        enum _type_allowed{
            allowed_type_this_type=2,
        };
        enum _version_allowed{
            allowed_version_this_version=0,
        };
    } data;
};

} // namespace MGA
} // namespace ubx
#endif // ifndef __MGA_H__
