#ifndef __DRV_ECUANDBMUCOMMUNICATION_H__
#define __DRV_ECUANDBMUCOMMUNICATION_H__

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"
#include "./HAL/HAL_CAN.h"
#include "G_GloabalVariable.h"
#include "Drv_Queue.h"
#include "./Epoll/Drv_epoll.h"
#include <pthread.h>
#include "./DRV/LOG/Drv_ZLog.h"

extern queue_st	Queue_Can1RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
extern queue_st	Queue_Can1SendData;                   //用于发送消息存入

/*PORT difine*/
#define PORT_CAN1_DEVICE_NAME            					    "can1"        						/*分机CAN设备名称*/
#define PORT_CAN1_CAN_BITRATE                  					500000       						/*分机通讯速率*/ //125kbps

bool Drv_can1_init(void);
static void Drv_can1_epoll_msg_transmit (void * arg);
int  Drv_reset_can1_device(const char *can_name);
int Drv_can1_send( CAN_MESSAGE *pFrame);
int Drv_can1fd_send( struct canfd_frame *cansend_data);

#endif