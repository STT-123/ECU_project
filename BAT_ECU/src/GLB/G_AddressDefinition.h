#ifndef _G_AddressDefinition_H_
#define _G_AddressDefinition_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define MDBUS_ADDR_BECU_FAULT0 0x3440
#define MDBUS_ADDR_BECU_FAULT1 0x3441
#define MDBUS_ADDR_BECU_FAULT2 0x3442
#define MDBUS_ADDR_BECU_FAULT3 0x3443   //SD卡故障

#define MDBUS_ADDR_RTC_TIME 0x6705 // rtc 时间

#define OTASTATUSREGADDR 0x4010
#define OTAPPROGRESSREGADDR 0x4011
#define OTACTRLREGADDR 0x4012

#define AC_SBL_OTAFILENUMBER 0x4013
#define AC_APP_OTAFILENUMBER 0x4014

#define MDBUS_ADDR_DC_VOL 0x3460   // 直流电压
#define MDBUS_ADDR_DC_CUR 0x3462   // 直流电流
#define MDBUS_ADDR_DC_POW 0x3464   // 直流功率
#define MDBUS_ADDR_P_ENERGY 0x3466 // 正向能量
#define MDBUS_ADDR_N_ENERGY 0x3468 // 负向能量



#define MDBUS_ADDR_PRODUCTION 0x3416  // ems 厂家
#define MDBUS_ADDR_ECU_VERSION 0x3417 // ems 版本号


#endif