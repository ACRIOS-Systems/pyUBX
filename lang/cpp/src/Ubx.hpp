// define the _iterator

#ifndef __UBX_H__
#define __UBX_H__

#include <cstdint>
#include <string>

#define UBX_CHANGE_VAR_BIT(name, val, map, offset) (name = (name & ~map) | ((val << offset) & map))
#define UBX_GET_VAR_BIT(name, map, offset) ((name & map) >> offset)

namespace ubx
{
    class SerializeCommon
    {
    private:
        class CkSum
        {
        public:
            uint8_t ck_A, ck_B;

            CkSum();

            void update(uint8_t byte);

            bool match(uint8_t _ck_A, uint8_t _ck_B) const;
        };

        void writeByte(uint8_t byte, uint8_t *data, uint16_t &index) const;

    public:
        using writeCb_t = int32_t(const SerializeCommon *serializedClass, const uint8_t *data, uint16_t len, void *userData);

        using status_t = enum _status_t { OK = 0,
                                          BufferLengthSmall };

        static constexpr uint8_t ubxHead0 = 0xB5u;
        static constexpr uint8_t ubxHead1 = 0x62u;
        static constexpr uint8_t PayloadPlusSize = 8u;

        virtual uint8_t getClassId(void) const = 0;

        virtual uint8_t getMessageId(void) const = 0;

        virtual const std::string &getClassName(void) const = 0;

        virtual std::string getMessageName(void) const = 0;

        std::string getName(void) const { return getClassName() + std::string("::") + getMessageName() + std::string("(") + std::to_string(getClassId()) + std::string(":") + std::to_string(getMessageId()) + std::string(")"); }

        virtual std::string getDescription(void) const = 0;

        virtual uint8_t *getDataStartAddress(void) const = 0;

        virtual uint16_t getDataSize(void) const = 0;

        int32_t serialize(uint8_t *buf, uint16_t bufLen) const;

        int32_t serialize(writeCb_t writeCb, void *userData) const;
    };
}

#endif // #define __UBX_H__
