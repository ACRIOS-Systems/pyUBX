// File lang/cpp/src/messages/TIM.cpp
// Auto-generated by pyUBX generateCPP.py v0.1 on 2023-04-08T18:03:13.559857
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

 #include "TIM.hpp"
#include <sstream>

const std::string classIDName("TIM");

uint8_t ubx::TIM::SVIN::getClassId(void) const { return ubx::TIM::classID; }
uint8_t ubx::TIM::SVIN::getMessageId(void) const { return messageID; }
const std::string &ubx::TIM::SVIN::getClassName(void) const { return classIDName; }
std::string ubx::TIM::SVIN::getMessageName(void) const { return std::string("SVIN"); };
std::string ubx::TIM::SVIN::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"dur\":" << std::to_string(data.dur) << ", \"meanX\":" << std::to_string(data.meanX) << ", \"meanY\":" << std::to_string(data.meanY) << ", \"meanZ\":" << std::to_string(data.meanZ) << ", \"meanV\":" << std::to_string(data.meanV) << ", \"obs\":" << std::to_string(data.obs) << ", \"valid\":" << std::to_string(data.valid) << ", \"active\":" << std::to_string(data.active) << ", \"reserved\":" << "0";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::TIM::SVIN::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::TIM::SVIN::getDataSize(void) const { return sizeof(data); }