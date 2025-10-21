#ifndef __DRV_EXTERNALCANCOMMUNICATION_H__
#define __DRV_EXTERNALCANCOMMUNICATION_H__

#include "lib/queue/queue.h"
#include "port/can.h"
#include "port/myepoll.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"
#include "../GLB/G_GloabalVariable.h"
#include <pthread.h>

#define PORT_CAN2_DEVICE_NAME "can2" /*分机CAN设备名称*/
#define PORT_CAN2_CAN_BITRATE 500000

extern queue_t Queue_Can1RevData; // 分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用

bool Drv_can2_init(void);
int Drv_can2_send(CAN_MESSAGE *pFrame);
int Drv_can2fd_send(CAN_FD_MESSAGE_BUS *pFrame);

// 消息转发CAN2
bool Drv_BMS_Forward_CAN2(const struct canfd_frame *Data);

#endif