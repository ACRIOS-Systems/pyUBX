#include "parseUbxMessageBase.hpp"
#include <cstring>

using namespace ubx;
using namespace std;

int32_t ParseUbxMessageBase::findUbxMessageStartIdx(const uint8_t *buf, uint16_t len) const
{
    int ret = -1;

    for (uint16_t i = 1; i < len; i++)
    {
        if ((buf[i - 1] == SerializeCommon::ubxHead0) && (buf[i] == SerializeCommon::ubxHead1))
        {
            ret = i - 1;
        }
    }

    return ret;
}

int32_t ParseUbxMessageBase::findUbxMessageLen(const uint8_t *buf, uint16_t len, int32_t startIdx) const
{
    int32_t ret = -1;

    if (startIdx > -1)
    {
        if ((startIdx + minimalSize) <= len)
        {
            ret = startIdx + minimalSize + buf[startIdx + IDX_LEN_L] + (buf[startIdx + IDX_LEN_H] << 8U);
            if ((startIdx + ret) > len)
            {
                ret = -2;
            }
        }
    }

    return ret;
}

shared_ptr<SerializeCommon> ParseUbxMessageBase::parseUbx(const uint8_t *buf, uint16_t len) const
{
    shared_ptr<SerializeCommon> ret = nullptr;
    parameters_t param = getUbxMessageParameters(buf, len);

    if (param.len > -1)
    {
        ret = createUbx(&buf[param.startIdx + IDX_DATA_START], param.len, buf[param.startIdx + IDX_CLASS_ID], buf[param.startIdx + IDX_MESSAGE_ID]);
    }

    return ret;
}

std::shared_ptr<SerializeCommon> ParseUbxMessageBase::parseUbx(uint8_t classId, uint8_t messageId, const uint8_t *buf, uint16_t len) const
{
    return createUbx(buf, len, classId, messageId);
}

bool ParseUbxMessageBase::isUbxMessage(const uint8_t *buf, uint16_t len) const
{
    return (findUbxMessageStartIdx(buf, len) > -1);
}

ParseUbxMessageBase::parameters_t ParseUbxMessageBase::getUbxMessageParameters(const uint8_t *buf, uint16_t len) const
{
    parameters_t ret = {-1, -1};

    ret.startIdx = findUbxMessageStartIdx(buf, len);
    if (ret.startIdx > -1)
    {
        ret.len = findUbxMessageLen(buf, len, ret.startIdx);
    }

    return ret;
}
