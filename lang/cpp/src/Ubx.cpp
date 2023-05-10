#include "Ubx.hpp"

using namespace ubx;

SerializeCommon::CkSum::CkSum() : ck_A(0), ck_B(0) {}

void SerializeCommon::CkSum::update(uint8_t byte)
{
    ck_A += byte;
    ck_B += ck_A;
}

bool SerializeCommon::CkSum::match(uint8_t _ck_A, uint8_t _ck_B) const
{
    return ((ck_A == _ck_A) && (ck_B == _ck_B));
}

void SerializeCommon::writeByte(uint8_t byte, uint8_t *data, uint16_t &index) const
{
    data[index] = byte;
    index++;
}

SerializeCommon::status_t SerializeCommon::serialize(uint8_t *buf, uint16_t bufLen) const
{
    status_t ret;

    if (bufLen < getDataSize() + UbxControlBytesSize)
    {
        ret = BufferLengthSmall;
    }
    else
    {
        CkSum ckSum;
        uint16_t index = 0;

        // serialize data
        writeByte(SerializeCommon::ubxHead0, buf, index);
        writeByte(SerializeCommon::ubxHead1, buf, index);
        writeByte(getClassId(), buf, index);
        ckSum.update(getClassId());
        writeByte(getMessageId(), buf, index);
        ckSum.update(getMessageId());
        writeByte(getDataSize() & 0x00ff, buf, index);
        ckSum.update(getDataSize() & 0x00ff);
        writeByte(getDataSize() >> 8, buf, index);
        ckSum.update(getDataSize() >> 8);
        for (uint16_t i = 0; i < getDataSize(); i++)
        {
            writeByte(getDataStartAddress()[i], buf, index);
            ckSum.update(getDataStartAddress()[i]);
        }
        writeByte(ckSum.ck_A, buf, index);
        writeByte(ckSum.ck_B, buf, index);
        ret = OK;
    }

    return ret;
};

SerializeCommon::status_t SerializeCommon::serialize(writeCb_t writeCb, void *userData) const
{
    status_t ret;
    const uint16_t bufLen = getDataSize() + UbxControlBytesSize;
    uint8_t buf[bufLen] = {0};

    ret = serialize(buf, bufLen);

    if (!ret)
    {
        if (!!writeCb(this, buf, bufLen, userData))
        {
            ret = WriteCbErr;
        }
    }

    return ret;
};
