#ifndef __G_VERSIONS_H__
#define __G_VERSIONS_H__

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ECU_VERSION  0x202  //  表示v1.01 格式xx。yy xx 高八位yy低八位

#define MDBUS_ADDR_PRODUCTION 0x3416    //ems 厂家
#define MDBUS_ADDR_ECU_VERSION 0x3417    //ems 版本号

#define FTP_VERSION "FTP Server 1.0.0"

#endif