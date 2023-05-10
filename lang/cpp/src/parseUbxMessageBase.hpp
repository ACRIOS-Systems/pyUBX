#ifndef _PARSE_UBX_MESSAGE_BASE_H__
#define _PARSE_UBX_MESSAGE_BASE_H__

#include <memory>
#include "Ubx.hpp"

namespace ubx
{
    /**
     * @brief Class which is determined to parse byte array and return UBX object.
     */
    class ParseUbxMessageBase
    {
        /**
         * @brief Finding UBX header bytes in buffer
         *
         * @param buf Buffer with ubx data.
         * @param len Length of buffer.
         *
         * @return int32_t >=0 Start index.
         */
        int32_t findUbxMessageStartIdx(const uint8_t *buf, uint16_t len) const;

        /**
         * @brief Find and calculate ubx data length.
         *
         * @param buf Buffer with ubx data.
         * @param len Length of buffer.
         * @param startIdx Index with ubx header location.
         *
         * @return int32_t >=0 Length of ubx data.
         */
        int32_t findUbxMessageLen(const uint8_t *buf, uint16_t len, int32_t startIdx) const;

    protected:
        /**
         * @brief Return Ubx object parsed from given buffer and object details.
         *
         * @param buf buffer with data
         * @param len buffer length
         * @param classId Ubx class id
         * @param messageID Ubx message id
         * @param isGet Is get type.
         *
         * @return std::shared_ptr<SerializeCommon> Nullptr or shared_ptr of UBX object.
         */
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

        using parameters_t = struct _parameters_t
        {
            int32_t startIdx;
            int32_t len;
        };

        ParseUbxMessageBase(){};

        /**
         * @brief Parse buffer data and return UBX object.
         *
         * @param buf Buffer with ubx data.
         * @param len Buffer length.
         *
         * @return std::shared_ptr<SerializeCommon> Nullptr or UBX object
         */
        std::shared_ptr<SerializeCommon> parseUbx(const uint8_t *buf, uint16_t len) const;

        /**
         * @brief Parsing ubx buffer data without ubx control bytes and return UBX object.
         *
         * @param classId ubx class id.
         * @param messageId ubx message id
         * @param buf buffer data without ubx control data.
         * @param len buffer length
         *
         * @return std::shared_ptr<SerializeCommon> Nullptr or UBX object
         */
        std::shared_ptr<SerializeCommon> parseUbx(uint8_t classId, uint8_t messageId, const uint8_t *buf, uint16_t len) const;

        /**
         * @brief Check if buffer contains ubx header bytes.
         *
         * @param buf buffer data.
         * @param len buffer length.
         *
         * @return bool True if buffer contains ubx header bytes.
         */
        bool isUbxMessage(const uint8_t *buf, uint16_t len) const;

        /**
         * @brief Return start index and ubx message length with ubx control bytes included.
         *
         * @param buf buffer data.
         * @param len buffer length.
         *
         * @return parameters_t Start index and message length.
         */
        parameters_t getUbxMessageParameters(const uint8_t *buf, uint16_t len) const;
    };

}

#endif /* _PARSE_UBX_MESSAGE_BASE_H__ */
