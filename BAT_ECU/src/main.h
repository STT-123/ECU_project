#ifndef __MAIN_H__
#define __MAIN_H__

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include "./GLB/G_GloabalVariable.h"
enum system_state
{
	SYS_INIT = 0x00,	 /*系统初始化中*/
	SYS_STOP = 0x01,	 /*系统停止中*/
	SYS_STARTING = 0x02, /*系统启动中*/
	SYS_RUNING = 0x03,	 /*系统运行中*/
	SYS_ERROR = 0x04	 /*系统故障中*/

};

extern OTAObject otactrl;
uint32_t GetTimeDifference_ms(struct timespec start_tick);
void set_charger_cmd(unsigned char chargecmd) ;  //设置充电桩发出的cmd命令
unsigned short get_system_state() ;   //获取充电桩状态
#endif