#ifndef __C_OTA_DATAMONITOR_H__
#define __C_OTA_DATAMONITOR_H__

 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h> 


#define SOH 0x01
#define STX 0x02
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define CAN 0x18
#define CTRLZ 0xFF



// #define ACOTACANID				0x61A
// #define ACPOTACANID				0x18FA78F5//ACP报文显示版本
// #define DCDCOTACANID			0x18FAE6E2//DCDC报文显示版本

void *lwip_data_TASK(void *param);

extern volatile unsigned long curmsgtimer ;

// unsigned int OsIf_GetMilliseconds(void) ;
unsigned short crcGet(unsigned char *ptr, int len);
signed char GetOTAFILEInfo(unsigned char *databuf, char *name, int *filesize, int *xmodempacknum);
signed char SaveOtaFile(char *name, unsigned char *buf, int totalpacknum, int curpackno, int datanum);
void delete_files_with_prefix(const char *path, const char *prefix) ;
#endif