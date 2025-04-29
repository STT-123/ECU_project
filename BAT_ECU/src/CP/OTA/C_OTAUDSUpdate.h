#ifndef __C_OTAUDSUpdate_H__
#define __C_OTAUDSUpdate_H__

 
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

#define UDSOVERTIME				1000

#define MAX_FILE_COUNT 20

#define ACOTACANID				0x61A

#define     SUP_MAX_BLOCK       10

// 定义appDataType结构体
typedef struct {
    uint32_t writeAddr; // 写入地址
    uint32_t writeLen;  // 写入长度
    uint16_t CRC;
} appDataType;

// 定义flasDataType结构体
typedef struct {
    uint32_t writeAddr; // 写入地址
    uint32_t writeLen;  // 写入长度
    uint16_t CRC;
} flashDataType;

extern flashDataType flashData;
extern appDataType appData[SUP_MAX_BLOCK + 1];
// extern unsigned short sblfilenumber ;//SBL文件数量大小
// extern unsigned short appfilenumber ;//app文件数量大小
// extern int SBl_index;
// extern int APP_index ;
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



	unsigned char DiagnosticSessionControl;
	unsigned char UDSSecurityAccess_1;
	unsigned char UDSSecurityAccess_2;
	unsigned char UDSSecurityAccess_3;
	unsigned char UDSRoutineControl;
	unsigned char RequestDownload;
	unsigned char TransferData;
	unsigned char RequestTransferExit;

    uint8_t udsServerID;    //uds的服务ID
    uint8_t udsSession;     //服务码
    uint32_t seedValue;     //获取的种子
    uint8_t udsReturnSuccess;//需要响应的数据已经成功响应，1接收到数据 0没有
    uint32_t userData;//用户数据，用来记录一些使用的数据
    uint32_t totalCount;//升级总的字节数
    uint32_t sendCount;//升级过程中已经下发的字节数

} UDSStatus;


extern UDSStatus udsstatus;
void CP_AC_OTA(OTAObject* pOTA);
void FinishACOtaAndCleanup(OTAObject* pOTA);
#endif