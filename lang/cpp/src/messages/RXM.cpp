// File lang/cpp/src/messages/RXM.cpp
// Auto-generated by pyUBX generateCPP.py v0.2 on 2023-06-06T19:57:04.622688
// See https://github.com/mayeranalytics/pyUBX
// DO NOT MODIFY THIS FILE!

 #include "RXM.hpp"
#include <sstream>

const std::string classIDName("RXM");

uint8_t ubx::RXM::IMES::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::IMES::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::IMES::getClassName(void) const { return classIDName; }
std::string ubx::RXM::IMES::getMessageName(void) const { return std::string("IMES"); };
std::string ubx::RXM::IMES::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::IMES::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::IMES::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::IMES_GET::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::IMES_GET::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::IMES_GET::getClassName(void) const { return classIDName; }
std::string ubx::RXM::IMES_GET::getMessageName(void) const { return std::string("IMES_GET"); };
std::string ubx::RXM::IMES_GET::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"numTx\":" << std::to_string(data.numTx) << ", \"version\":" << std::to_string(data.version) << ", \"reserved1\":" << "0";
    for (uint16_t i = 0; i < repeatedLen; i++) { ret << ", \"reserved2[" << i << "]\":" << "0" << ", \"txId[" << i << "]\":" << std::to_string(data.repeated[i].txId) << ", \"reserved3[" << i << "]\":" << "0" << ", \"cno[" << i << "]\":" << std::to_string(data.repeated[i].cno) << ", \"reserved4[" << i << "]\":" << "0" << ", \"doppler[" << i << "]\":" << std::to_string(data.repeated[i].doppler) << ", \"position1_1[" << i << "]\":" << std::to_string(data.repeated[i].position1_1) << ", \"_position1_1\":{\"pos1Floor\":" << std::to_string(data.repeated_position1_1_pos1Floor(i)) << ", \"pos1Lat\":" << std::to_string(data.repeated_position1_1_pos1Lat(i)) << "}" << ", \"position1_2[" << i << "]\":" << std::to_string(data.repeated[i].position1_2) << ", \"_position1_2\":{\"pos1Lon\":" << std::to_string(data.repeated_position1_2_pos1Lon(i)) << ", \"pos1Valid\":" << std::to_string(data.repeated_position1_2_pos1Valid(i)) << "}" << ", \"position2_1[" << i << "]\":" << std::to_string(data.repeated[i].position2_1) << ", \"_position2_1\":{\"pos2Floor\":" << std::to_string(data.repeated_position2_1_pos2Floor(i)) << ", \"pos2Alt\":" << std::to_string(data.repeated_position2_1_pos2Alt(i)) << ", \"pos2Acc\":" << std::to_string(data.repeated_position2_1_pos2Acc(i)) << ", \"pos2Valid\":" << std::to_string(data.repeated_position2_1_pos2Valid(i)) << "}" << ", \"lat[" << i << "]\":" << std::to_string(data.repeated[i].lat) << ", \"lon[" << i << "]\":" << std::to_string(data.repeated[i].lon) << ", \"shortIdFrame[" << i << "]\":" << std::to_string(data.repeated[i].shortIdFrame) << ", \"_shortIdFrame\":{\"shortId\":" << std::to_string(data.repeated_shortIdFrame_shortId(i)) << ", \"shortValid\":" << std::to_string(data.repeated_shortIdFrame_shortValid(i)) << ", \"shortBoundary\":" << std::to_string(data.repeated_shortIdFrame_shortBoundary(i)) << "}" << ", \"mediumIdLSB[" << i << "]\":" << std::to_string(data.repeated[i].mediumIdLSB) << ", \"mediumId2[" << i << "]\":" << std::to_string(data.repeated[i].mediumId2) << ", \"_mediumId2\":{\"mediumIdMSB\":" << std::to_string(data.repeated_mediumId2_mediumIdMSB(i)) << ", \"mediumValid\":" << std::to_string(data.repeated_mediumId2_mediumValid(i)) << ", \"mediumboundary\":" << std::to_string(data.repeated_mediumId2_mediumboundary(i)) << "}";}
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::IMES_GET::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::IMES_GET::getDataSize(void) const { return sizeof(data) + (repeatedLen * repeatedSize); }

void ubx::RXM::IMES_GET::_data::repeated_position1_1_pos1Floor(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position1_1, val, RXM_IMES_GET_REPEATED_POSITION1_1_POS1FLOOR_MASK, RXM_IMES_GET_REPEATED_POSITION1_1_POS1FLOOR_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position1_1_pos1Floor(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position1_1, RXM_IMES_GET_REPEATED_POSITION1_1_POS1FLOOR_MASK, RXM_IMES_GET_REPEATED_POSITION1_1_POS1FLOOR_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_position1_1_pos1Lat(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position1_1, val, RXM_IMES_GET_REPEATED_POSITION1_1_POS1LAT_MASK, RXM_IMES_GET_REPEATED_POSITION1_1_POS1LAT_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position1_1_pos1Lat(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position1_1, RXM_IMES_GET_REPEATED_POSITION1_1_POS1LAT_MASK, RXM_IMES_GET_REPEATED_POSITION1_1_POS1LAT_OFFSET); }

void ubx::RXM::IMES_GET::_data::repeated_position1_2_pos1Lon(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position1_2, val, RXM_IMES_GET_REPEATED_POSITION1_2_POS1LON_MASK, RXM_IMES_GET_REPEATED_POSITION1_2_POS1LON_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position1_2_pos1Lon(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position1_2, RXM_IMES_GET_REPEATED_POSITION1_2_POS1LON_MASK, RXM_IMES_GET_REPEATED_POSITION1_2_POS1LON_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_position1_2_pos1Valid(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position1_2, val, RXM_IMES_GET_REPEATED_POSITION1_2_POS1VALID_MASK, RXM_IMES_GET_REPEATED_POSITION1_2_POS1VALID_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position1_2_pos1Valid(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position1_2, RXM_IMES_GET_REPEATED_POSITION1_2_POS1VALID_MASK, RXM_IMES_GET_REPEATED_POSITION1_2_POS1VALID_OFFSET); }

void ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Floor(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position2_1, val, RXM_IMES_GET_REPEATED_POSITION2_1_POS2FLOOR_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2FLOOR_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Floor(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position2_1, RXM_IMES_GET_REPEATED_POSITION2_1_POS2FLOOR_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2FLOOR_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Alt(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position2_1, val, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ALT_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ALT_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Alt(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position2_1, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ALT_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ALT_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Acc(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position2_1, val, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ACC_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ACC_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Acc(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position2_1, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ACC_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2ACC_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Valid(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].position2_1, val, RXM_IMES_GET_REPEATED_POSITION2_1_POS2VALID_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2VALID_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_position2_1_pos2Valid(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].position2_1, RXM_IMES_GET_REPEATED_POSITION2_1_POS2VALID_MASK, RXM_IMES_GET_REPEATED_POSITION2_1_POS2VALID_OFFSET); }

void ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortId(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].shortIdFrame, val, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTID_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTID_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortId(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].shortIdFrame, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTID_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTID_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortValid(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].shortIdFrame, val, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTVALID_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTVALID_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortValid(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].shortIdFrame, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTVALID_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTVALID_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortBoundary(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].shortIdFrame, val, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTBOUNDARY_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTBOUNDARY_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_shortIdFrame_shortBoundary(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].shortIdFrame, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTBOUNDARY_MASK, RXM_IMES_GET_REPEATED_SHORTIDFRAME_SHORTBOUNDARY_OFFSET); }

void ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumIdMSB(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].mediumId2, val, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMIDMSB_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMIDMSB_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumIdMSB(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].mediumId2, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMIDMSB_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMIDMSB_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumValid(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].mediumId2, val, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMVALID_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMVALID_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumValid(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].mediumId2, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMVALID_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMVALID_OFFSET); }
void ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumboundary(uint8_t val, uint8_t n){ UBX_CHANGE_VAR_BIT(repeated[n].mediumId2, val, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMBOUNDARY_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMBOUNDARY_OFFSET); }
uint8_t ubx::RXM::IMES_GET::_data::repeated_mediumId2_mediumboundary(uint8_t n)const{ return UBX_GET_VAR_BIT(repeated[n].mediumId2, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMBOUNDARY_MASK, RXM_IMES_GET_REPEATED_MEDIUMID2_MEDIUMBOUNDARY_OFFSET); }
const uint16_t ubx::RXM::IMES_GET::repeatedSize = sizeof(struct ubx::RXM::IMES_GET::_data::_repeated);
uint8_t ubx::RXM::MEASX::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::MEASX::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::MEASX::getClassName(void) const { return classIDName; }
std::string ubx::RXM::MEASX::getMessageName(void) const { return std::string("MEASX"); };
std::string ubx::RXM::MEASX::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::MEASX::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::MEASX::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::PMREQ::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::PMREQ::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::PMREQ::getClassName(void) const { return classIDName; }
std::string ubx::RXM::PMREQ::getMessageName(void) const { return std::string("PMREQ"); };
std::string ubx::RXM::PMREQ::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"duration\":" << std::to_string(data.duration) << ", \"flags\":" << std::to_string(data.flags) << ", \"_flags\":{\"backup\":" << std::to_string(data.flags_backup()) << "}";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::PMREQ::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::PMREQ::getDataSize(void) const { return sizeof(data); }

void ubx::RXM::PMREQ::_data::flags_backup(uint8_t val){ UBX_CHANGE_VAR_BIT(flags, val, RXM_PMREQ_FLAGS_BACKUP_MASK, RXM_PMREQ_FLAGS_BACKUP_OFFSET); }
uint8_t ubx::RXM::PMREQ::_data::flags_backup()const{ return UBX_GET_VAR_BIT(flags, RXM_PMREQ_FLAGS_BACKUP_MASK, RXM_PMREQ_FLAGS_BACKUP_OFFSET); }
uint8_t ubx::RXM::PMREQ2::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::PMREQ2::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::PMREQ2::getClassName(void) const { return classIDName; }
std::string ubx::RXM::PMREQ2::getMessageName(void) const { return std::string("PMREQ2"); };
std::string ubx::RXM::PMREQ2::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << ", \"version\":" << std::to_string(data.version) << ", \"reserved1\":" << "0" << ", \"duration\":" << std::to_string(data.duration) << ", \"flags\":" << std::to_string(data.flags) << ", \"_flags\":{\"backup\":" << std::to_string(data.flags_backup()) << ", \"force\":" << std::to_string(data.flags_force()) << "}" << ", \"wakeupSources\":" << std::to_string(data.wakeupSources) << ", \"_wakeupSources\":{\"uartrx\":" << std::to_string(data.wakeupSources_uartrx()) << ", \"extint0\":" << std::to_string(data.wakeupSources_extint0()) << ", \"extint1\":" << std::to_string(data.wakeupSources_extint1()) << ", \"spics\":" << std::to_string(data.wakeupSources_spics()) << "}";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::PMREQ2::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::PMREQ2::getDataSize(void) const { return sizeof(data); }

void ubx::RXM::PMREQ2::_data::flags_backup(uint8_t val){ UBX_CHANGE_VAR_BIT(flags, val, RXM_PMREQ2_FLAGS_BACKUP_MASK, RXM_PMREQ2_FLAGS_BACKUP_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::flags_backup()const{ return UBX_GET_VAR_BIT(flags, RXM_PMREQ2_FLAGS_BACKUP_MASK, RXM_PMREQ2_FLAGS_BACKUP_OFFSET); }
void ubx::RXM::PMREQ2::_data::flags_force(uint8_t val){ UBX_CHANGE_VAR_BIT(flags, val, RXM_PMREQ2_FLAGS_FORCE_MASK, RXM_PMREQ2_FLAGS_FORCE_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::flags_force()const{ return UBX_GET_VAR_BIT(flags, RXM_PMREQ2_FLAGS_FORCE_MASK, RXM_PMREQ2_FLAGS_FORCE_OFFSET); }

void ubx::RXM::PMREQ2::_data::wakeupSources_uartrx(uint8_t val){ UBX_CHANGE_VAR_BIT(wakeupSources, val, RXM_PMREQ2_WAKEUPSOURCES_UARTRX_MASK, RXM_PMREQ2_WAKEUPSOURCES_UARTRX_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::wakeupSources_uartrx()const{ return UBX_GET_VAR_BIT(wakeupSources, RXM_PMREQ2_WAKEUPSOURCES_UARTRX_MASK, RXM_PMREQ2_WAKEUPSOURCES_UARTRX_OFFSET); }
void ubx::RXM::PMREQ2::_data::wakeupSources_extint0(uint8_t val){ UBX_CHANGE_VAR_BIT(wakeupSources, val, RXM_PMREQ2_WAKEUPSOURCES_EXTINT0_MASK, RXM_PMREQ2_WAKEUPSOURCES_EXTINT0_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::wakeupSources_extint0()const{ return UBX_GET_VAR_BIT(wakeupSources, RXM_PMREQ2_WAKEUPSOURCES_EXTINT0_MASK, RXM_PMREQ2_WAKEUPSOURCES_EXTINT0_OFFSET); }
void ubx::RXM::PMREQ2::_data::wakeupSources_extint1(uint8_t val){ UBX_CHANGE_VAR_BIT(wakeupSources, val, RXM_PMREQ2_WAKEUPSOURCES_EXTINT1_MASK, RXM_PMREQ2_WAKEUPSOURCES_EXTINT1_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::wakeupSources_extint1()const{ return UBX_GET_VAR_BIT(wakeupSources, RXM_PMREQ2_WAKEUPSOURCES_EXTINT1_MASK, RXM_PMREQ2_WAKEUPSOURCES_EXTINT1_OFFSET); }
void ubx::RXM::PMREQ2::_data::wakeupSources_spics(uint8_t val){ UBX_CHANGE_VAR_BIT(wakeupSources, val, RXM_PMREQ2_WAKEUPSOURCES_SPICS_MASK, RXM_PMREQ2_WAKEUPSOURCES_SPICS_OFFSET); }
uint8_t ubx::RXM::PMREQ2::_data::wakeupSources_spics()const{ return UBX_GET_VAR_BIT(wakeupSources, RXM_PMREQ2_WAKEUPSOURCES_SPICS_MASK, RXM_PMREQ2_WAKEUPSOURCES_SPICS_OFFSET); }
uint8_t ubx::RXM::RAWX::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::RAWX::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::RAWX::getClassName(void) const { return classIDName; }
std::string ubx::RXM::RAWX::getMessageName(void) const { return std::string("RAWX"); };
std::string ubx::RXM::RAWX::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::RAWX::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::RAWX::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::RLM::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::RLM::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::RLM::getClassName(void) const { return classIDName; }
std::string ubx::RXM::RLM::getMessageName(void) const { return std::string("RLM"); };
std::string ubx::RXM::RLM::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::RLM::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::RLM::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::RTCM::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::RTCM::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::RTCM::getClassName(void) const { return classIDName; }
std::string ubx::RXM::RTCM::getMessageName(void) const { return std::string("RTCM"); };
std::string ubx::RXM::RTCM::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::RTCM::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::RTCM::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::SFRBX::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::SFRBX::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::SFRBX::getClassName(void) const { return classIDName; }
std::string ubx::RXM::SFRBX::getMessageName(void) const { return std::string("SFRBX"); };
std::string ubx::RXM::SFRBX::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::SFRBX::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::SFRBX::getDataSize(void) const { return 0; }
uint8_t ubx::RXM::SVSI::getClassId(void) const { return ubx::RXM::classID; }
uint8_t ubx::RXM::SVSI::getMessageId(void) const { return messageID; }
const std::string &ubx::RXM::SVSI::getClassName(void) const { return classIDName; }
std::string ubx::RXM::SVSI::getMessageName(void) const { return std::string("SVSI"); };
std::string ubx::RXM::SVSI::getDescription(void) const {
    std::stringstream ret;
    ret << "{\"classId\":" << std::to_string(getClassId()) << ",\"messageId\":" << std::to_string(getMessageId()) << ",\"classIdName\":\"" << getClassName() << "\",\"messageIdName\":\"" << getMessageName() << "\"";
    ret << "}";
    return ret.str();
}
uint8_t* ubx::RXM::SVSI::getDataStartAddress(void) const { return (uint8_t*)&data; }
uint16_t ubx::RXM::SVSI::getDataSize(void) const { return 0; }
