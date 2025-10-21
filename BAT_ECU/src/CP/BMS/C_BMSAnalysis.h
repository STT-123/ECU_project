#ifndef __C_BMSANALYSIS_H__
#define __C_BMSANALYSIS_H__

#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "rtwtypes.h"
#include <string.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#include <linux/can.h>
#include <stdint.h>
#include "./GLB/G_GloabalVariable.h"
#include "./CP/BMS/bms/CANRcvFcn_types.h"
#define BMS_POWER_ON 0x01
#define BMS_POWER_OFF 0x02
#define BMS_POWER_URGENCY_OFF 0x04
#define BMS_POWER_UPDATING 0x05
#define BMS_POWER_DEFAULT 0x00

extern float Electric_Meter_BCU_V3;
extern float Electric_Meter_BCU_Curr2;
extern int32_t Electric_Meter_BCU_RealtimePower;
extern float Electric_Meter_BCU_EngryAccumulateChrg;
extern float Electric_Meter_BCU_EngryAccumulateDisChrg;

bool CP_BMSAnalysis(void);

void Set_BCU_Voltage(float voltage);

void Set_BCU_Current(float current);

void Set_BCU_Power(int32_t power_watt);

void Set_BCU_PositiveEnergy(float energy_wh);

void Set_BCU_NegativeEnergy(float energy_wh);

void CP_get_BCU_FaultInfoLv3H(uint32_T faultValue);

void CP_set_OTA_XCPConnect(real_T value);
real_T CP_get_OTA_XCPConnect(void);

void CP_set_TCU_ACMuteSet(real_T value);
real_T CP_get_TCU_ACMuteSet(void);

void CP_set_TCU_BCUEINSet(real_T value);
real_T CP_get_TCU_BCUEINSet(void);

void CP_set_TCU_ChargerWorkSts(real_T value);
real_T CP_get_TCU_ChargerWorkSts(void);

// void CP_set_TCU_ClearFault(real_T value);
// real_T CP_get_TCU_ClearFault(void);

void CP_set_TCU_ECOMode(real_T value);
real_T CP_get_TCU_ECOMode(void);

// void CP_set_TCU_GetTime(real_T value);
// real_T CP_get_TCU_GetTime(void);

void CP_set_TCU_LifeCounter(real_T value);
real_T CP_get_TCU_LifeCounter(void);

void CP_set_TCU_PowerUpCmd(real_T value);
real_T CP_get_TCU_PowerUpCmd(void);

void CP_set_TCU_TimeCalFlg(real_T value);
real_T CP_get_TCU_TimeCalFlg(void);

void CP_set_TCU_TimeDay(real_T value);
real_T CP_get_TCU_TimeDay(void);

void CP_set_TCU_TimeHour(real_T value);
real_T CP_get_TCU_TimeHour(void);

void CP_set_TCU_TimeMinute(real_T value);
real_T CP_get_TCU_TimeMinute(void);

void CP_set_TCU_TimeMonth(real_T value);
real_T CP_get_TCU_TimeMonth(void);

void CP_set_TCU_TimeSecond(real_T value);
real_T CP_get_TCU_TimeSecond(void);

void CP_set_TCU_TimeWeek(real_T value);
real_T CP_get_TCU_TimeWeek(void);

void CP_set_TCU_TimeYear(real_T value);
real_T CP_get_TCU_TimeYear(void);

void ConvertCANFDToBus(const struct canfd_frame *frame, CAN_FD_MESSAGE_BUS *msg);
void ConvertBusToCANFD(const CAN_FD_MESSAGE_BUS *msg, struct canfd_frame *frame);
void Convert_CAN_MESSAGE_to_can_frame(const CAN_MESSAGE *msg, struct can_frame *frame);
void Convert_canfd_frame_to_CAN_MESSAGE(const struct canfd_frame *frame, CAN_MESSAGE *msg);
void Convert_can_frame_to_CAN_MESSAGE(const struct can_frame *frame, CAN_MESSAGE *msg);
#endif