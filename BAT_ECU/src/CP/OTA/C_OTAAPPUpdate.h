#ifndef __C_OTAAPPUpdate_H
#define __C_OTAAPPUpdate_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#include "main.h"

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
 
 } ECUStatus;
 
extern ECUStatus ecustatus;
void CP_ECU_OTA(OTAObject *pOTA);
void FinshhECUOtaAndCleanup(OTAObject* pOTA);
int verify_bin_file(const char *filepath);
#endif