#ifndef __DRV_ECUANDBMUCOMMUNICATION_H__
#define __DRV_ECUANDBMUCOMMUNICATION_H__

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"
#include "./HAL/HAL_CAN2.h"
#include "G_GloabalVariable.h"
#include "Drv_Queue.h"
#include "./Epoll/Drv_epoll.h"
#include <pthread.h>
#include "./DRV/LOG/Drv_ZLog.h"

extern queue_st	Queue_Can2RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
extern queue_st	Queue_Can2SendData;                   //用于发送消息存入

bool Drv_can2_init(void);
static void can2_epoll_msg_transmit (void * arg);
int  reset_can_device_2(const char *can_name);
int can2_send(struct canfd_frame *cansend_data);

#endif