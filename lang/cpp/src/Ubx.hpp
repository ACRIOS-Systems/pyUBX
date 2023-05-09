// define the _iterator

#ifndef __UBX_H__
#define __UBX_H__

#include <cstdint>
#include <string>

#define UBX_CHANGE_VAR_BIT(name, val, map, offset) (name = (name & ~map) | ((val << offset) & map))
#define UBX_GET_VAR_BIT(name, map, offset) ((name & map) >> offset)

namespace ubx
{
    /**
     * @brief This is basic class for UBX object used for getting UBX object details and serializing context function.
     */
    class SerializeCommon
    {
    private:
        /**
         * @brief This class is used for counting checksum of serialized data.
         */
        class CkSum
        {
        public:
            uint8_t ck_A, ck_B;

            CkSum();

            /**
             * @brief Update checksum variables with given byte.
             *
             * @param byte Byte used for counting checksum.
             */
            void update(uint8_t byte);

            /**
             * @brief Compare given checksum bytes with counted one.
             *
             * @param _ck_A Low byte checksum value
             * @param _ck_B  High bute checksum value
             *
             * @return bool True if checksum matched otherwise false.
             */
            bool match(uint8_t _ck_A, uint8_t _ck_B) const;
        };

        /**
         * @brief Write given byte into buffer.
         *
         * @param byte Byte to write into buffer.
         * @param data Buffer where the data should be serialized
         * @param index Tracking index of bytes used in buffer.
         */
        void writeByte(uint8_t byte, uint8_t *data, uint16_t &index) const;

    public:
        static constexpr uint8_t ubxHead0 = 0xB5u;         /**> First ubx bytearray header byte value. */
        static constexpr uint8_t ubxHead1 = 0x62u;         /**> Second ubx bytearray header byte value. */
        static constexpr uint8_t UbxControlBytesSize = 8u; /**> Extra bytes serialized into buffer to identify message and validate its context. */

        using writeCb_t = int32_t(const SerializeCommon *serializedClass, const uint8_t *data, uint16_t len, void *userData);

        using status_t = enum _status_t { OK = 0,
                                          BufferLengthSmall };

        /**
         * @brief Get the UBX class id value
         *
         * @return uint8_t UBX class id value.
         */
        virtual uint8_t getClassId(void) const = 0;

        /**
         * @brief Get the UBX message id value
         *
         * @return uint8_t UBX message id value
         */
        virtual uint8_t getMessageId(void) const = 0;

        /**
         * @brief Get string representation of UBX class id.
         *
         * @return const std::string& String representation of UBX class id.
         */
        virtual const std::string &getClassName(void) const = 0;

        /**
         * @brief Get string representation of UBX message id.
         *
         * @return std::string String representation of UBX message id.
         */
        virtual std::string getMessageName(void) const = 0;

        /**
         * @brief Get string representation of UBX class name/id and message name/id.
         *
         * @return std::string String representation of UBX class name/id and message name/id.
         */
        std::string getName(void) const { return getClassName() + std::string("::") + getMessageName() + std::string("(") + std::to_string(getClassId()) + std::string(":") + std::to_string(getMessageId()) + std::string(")"); }

        /**
         * @brief Get the complete string representation of UBX object.
         *
         * @return std::string Complete string representation of UBX object.
         */
        virtual std::string getDescription(void) const = 0;

        /**
         * @brief Get UBX object data of interest start address
         *
         * @return uint8_t* UBX object data of interest start address
         */
        virtual uint8_t *getDataStartAddress(void) const = 0;

        /**
         * @brief Get size of data for current object.
         *
         * @return uint16_t Size of data for current object.
         */
        virtual uint16_t getDataSize(void) const = 0;

        /**
         * @brief Serialize object data into given buffer.
         *
         * @param buf Buffer where data are serialized.
         * @param bufLen Buffer data length.
         *
         * @return status_t Error code - OK when serialization passed.
         */
        status_t serialize(uint8_t *buf, uint16_t bufLen) const;

        /**
         * @brief Serialized object into buffer and call given callback function with serialized data.
         *
         * @param writeCb Callback function called once data are prepared.
         * @param userData User callback data.
         *
         * @return status_t Error code - OK when serialization passed.
         */
        status_t serialize(writeCb_t writeCb, void *userData) const;
    };
}

#endif // #define __UBX_H__
