#ifndef __C_OTAXCPUPDATE_H__
#define __C_OTAXCPUPDATE_H__

 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <time.h> // for timespec 
#include <sys/time.h> // for timeval 
#include <sys/stat.h>
#include <sys/time.h>
#include "./GLB/G_GloabalVariable.h"
#define XCPCANID			0
#define BMUXCPCANID			2
#define BCUXCPCANID			1

#define BCUOTACANID				0x1CB0E410

#define XCPOVERTIME				50
#define QUEUEDELAYTIME			1
#define WAITRESPONSETIME		2


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

} XCPStatus;


extern XCPStatus xcpstatus;
void CP_XCP_OTA(OTAObject* pOTA);
// void FinshhBCUBMUOtaAndCleanup(OTAObject* pOTA);
#endif