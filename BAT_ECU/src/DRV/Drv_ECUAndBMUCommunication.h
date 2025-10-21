#ifndef __DRV_ECUANDBMUCOMMUNICATION_H__
#define __DRV_ECUANDBMUCOMMUNICATION_H__

#include "lib/queue/queue.h"
#include "port/can.h"
#include "port/myepoll.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../CP/BMS/C_BMSAnalysis.h"

#include "G_GloabalVariable.h"
#include <pthread.h>
#include "log/log.h"

extern queue_t Queue_Can1RevData; // 分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用

/*PORT difine*/
#define PORT_CAN1_DEVICE_NAME "can1"
#define PORT_CAN1_CAN_BITRATE 500000

bool Drv_can1_init(void);
int Drv_can1_send(CAN_MESSAGE *pFrame);
int Drv_can1fd_send(struct canfd_frame *cansend_data);

#endif