#ifndef _PARSE_UBX_MESSAGE_BASE_H__
#define _PARSE_UBX_MESSAGE_BASE_H__

#include <memory>
#include "Ubx.hpp"

namespace ubx
{
    class ParseUbxMessageBase
    {

        int32_t findUbxMessageStartIdx(const uint8_t *buf, uint16_t len) const;

        int32_t findUbxMessageLen(const uint8_t *buf, uint16_t len, int32_t startIdx) const;

        static constexpr uint8_t minimalSize = 8u;

    protected:
        virtual std::shared_ptr<SerializeCommon> createUbx(const uint8_t *buf, uint16_t len, uint8_t classId, uint8_t messageID, bool isGet = true) const = 0;

    public:
        using indexes_t = enum _indexes_t {
            IDX_HEAD0 = 0,
            IDX_HEAD1 = 1,
            IDX_CLASS_ID = 2,
            IDX_MESSAGE_ID = 3,
            IDX_LEN_L = 4,
            IDX_LEN_H = 5,
            IDX_DATA_START = 6
        };

        ParseUbxMessageBase(){};

        using parameters_t = struct _parameters_t
        {
            int32_t startIdx;
            int32_t len;
        };

        std::shared_ptr<SerializeCommon> parseUbx(const uint8_t *buf, uint16_t len) const;
        std::shared_ptr<SerializeCommon> parseUbx(uint8_t classId, uint8_t messageId, const uint8_t *buf, uint16_t len) const;

        bool isUbxMessage(const uint8_t *buf, uint16_t len) const;

        parameters_t getUbxMessageParameters(const uint8_t *buf, uint16_t len) const;
    };

}

#endif /* _PARSE_UBX_MESSAGE_BASE_H__ */
