#ifndef __MAIN_H__
#define __MAIN_H__

// #ifndef _POSIX_C_SOURCE
// #define _POSIX_C_SOURCE 199309L
// #endif
#include <semaphore.h>
#include "./GLB/G_GloabalVariable.h"
// extern sem_t send_sem; //信号量
// enum system_state
// {
// 	SYS_INIT = 0x00,	 /*系统初始化中*/
// 	SYS_STOP = 0x01,	 /*系统停止中*/
// 	SYS_STARTING = 0x02, /*系统启动中*/
// 	SYS_RUNING = 0x03,	 /*系统运行中*/
// 	SYS_ERROR = 0x04	 /*系统故障中*/

// };
extern struct tm utc_timeinfo;
extern OTAObject otactrl;
uint32_t GetTimeDifference_ms(struct timespec start_tick);
#endif