#ifndef __DRV_ECUANDBCUCOMMUNICATION_H__
#define __DRV_ECUANDBCUCOMMUNICATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"
#include "../HAL/HAL_CAN1.h"
#include "../GLB/G_GloabalVariable.h"
#include "Drv_Queue.h"
#include "./Epoll/Drv_epoll.h"
#include <pthread.h>
// #include "./LOG/Drv_ZLog.h"



extern queue_st	Queue_Can1RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
extern queue_st	Queue_Can1SendData;                   //用于发送消息存入
int  reset_can_device_1(const char *can_name);
bool Drv_can1_init(void);
int Drv_ECUAndBCUCommunication_Init(void);
bool Drv_BMS_Analysis();
bool Drv_BMS_Forward_CAN0(int fd,CAN_MESSAGE *Data);
bool Drv_BMS_Forward_CAN1(int fd,CAN_MESSAGE *Data);
int can1_send(struct canfd_frame *cansend_data);
#endif