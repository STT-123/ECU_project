#ifndef __DRV_EXTERNALCANCOMMUNICATION_H__
#define __DRV_EXTERNALCANCOMMUNICATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"
#include "../HAL/HAL_CAN.h"
#include "../GLB/G_GloabalVariable.h"
#include "Drv_Queue.h"
#include "./Epoll/Drv_epoll.h"
#include <pthread.h>
// #include "./LOG/Drv_ZLog.h"
#define PORT_CAN2_DEVICE_NAME            					    "can2"        						/*分机CAN设备名称*/
#define PORT_CAN2_CAN_BITRATE                  					500000     


extern queue_st	Queue_Can1RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
// extern queue_st	Queue_Can1SendData;                   //用于发送消息存入
int  Drv_reset_can2_device(const char *can_name);
bool Drv_can2_init(void);
bool Drv_BMS_Forward_CAN2(const struct canfd_frame *Data);
// int Drv_can2_send(struct canfd_frame *cansend_data);
int Drv_can2_send(CAN_MESSAGE *pFrame);
int Drv_can2fd_send( CAN_FD_MESSAGE_BUS *pFrame);
#endif