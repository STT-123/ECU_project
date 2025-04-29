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
#define MDBUS_ADDR_BECU_FAULT3 0x3443



#define MDBUS_ADDR_RTC_TIME 0x6705    //rtc 时间



#define OTASTATUSREGADDR					0x4010
#define OTAPPROGRESSREGADDR					0x4011
#define OTACTRLREGADDR						0x4012

#define AC_SBL_OTAFILENUMBER 					0x4013
#define AC_APP_OTAFILENUMBER 					0x4014


#endif