
#ifndef ACPDCOTA_OTA_H_
#define ACPDCOTA_OTA_H_
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "./GLB/G_GloabalVariable.h"

 #define INDOVERTIME				5000//100

 #define ACPOTACANID				0x18FA78F5//ACP报文显示版本
 #define DCDCOTACANID			0x18FAE6E2//DCDC报文显示版本
 
 typedef struct
 {
     unsigned int XCPCMDRpeatTimes;
     unsigned int xcpstatus;
     unsigned int XCPCMDOuttimeTime;
     unsigned int XCPCMDOuttimeTimes;
     unsigned char DeviceConnectedFlag;
     unsigned char XCPQUERYCMDResponseFlag;
     unsigned char DeviceCanProgramFlag;
     unsigned char XCPCMDResponseFlag;
     unsigned char DeviceProgramOkFlag;
     unsigned char CANStartOTA;
     unsigned int ErrorReg;
     unsigned int ErrorDeviceID;
 
 
 
 
     uint8_t IndReturnSuccess;//需要响应的数据已经成功响应，1接收到数据 0没有
     uint32_t userData;//用户数据，用来记录一些使用的数据
     uint32_t totalCount;//升级总的字节数
     uint32_t sendCount;//升级过程中已经下发的字节数
 
 } IndependentStatus;
 
 
 
 extern IndependentStatus independentStatus;
 
 signed char  AcpDcUpgradesend(const char *filename,FILE *rfile);
 
 
 void CP_ACPDCDC_OTA(OTAObject* pOTA);
 
 void FinishACPOtaAndCleanup(OTAObject* pOTA);
 void FinishDCDCOtaAndCleanup(OTAObject* pOTA);
 
 
 #endif /* ACPDCOTA_OTA_H_ */
 