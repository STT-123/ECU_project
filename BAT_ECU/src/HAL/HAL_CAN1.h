#ifndef __HAL_CAN1_H__
#define __HAL_CAN1_H__


#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/types.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/fs.h>

#include <net/if.h>


#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>


#ifndef PF_CAN
#define PF_CAN 29
#endif
#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif


/*PORT difine*/
#define PORT_CAN1_DEVICE_NAME            					    "can1"        						/*分机CAN设备名称*/
#define PORT_CAN1_CAN_BITRATE                  					500000       						/*分机通讯速率*/ //125kbps


bool HAL_can1_init(int *fd);
bool HAL_can1_ifconfig_init(void);
bool HAL_can1_band_init(int *fd);
bool HAL_can1_write(int fd,struct canfd_frame *pFrame);
bool HAL_can1_read(int fd, struct canfd_frame *pFrame,unsigned int msTimeout);
void HAL_can1_closeEx(int *fd);
bool HAL_can1_set_filter(int fd, struct can_filter *__can_filter , int  num);
int HAL_can1_get_state(const char *name, int *state);
#endif
