#ifndef __DRV_ECUANDBCUCOMMUNICATION_H__
#define __DRV_ECUANDBCUCOMMUNICATION_H__

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

#define PORT_CAN0_DEVICE_NAME "can0"
#define PORT_CAN0_CAN_BITRATE 500000

extern queue_t Queue_Can0RevData; // 分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
extern queue_t Queue_Can0RevData_FD;

bool Drv_can0_init(void);
int Drv_can0_send(CAN_MESSAGE *pFrame);
int Drv_can0fd_send(CAN_FD_MESSAGE_BUS *pFrame);

// 消息解析
bool Drv_BMS_Analysis();
// 消息转发CAN0
bool Drv_BMS_Forward_CAN0(int fd, CAN_MESSAGE *Data);

#endif