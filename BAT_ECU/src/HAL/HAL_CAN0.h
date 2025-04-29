#ifndef __HAL_CAN0_H__
#define __HAL_CAN0_H__

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
#define PORT_CAN0_DEVICE_NAME            					    "can0"        						/*分机CAN设备名称*/
#define PORT_CAN0_CAN_BITRATE                  					250000       						/*分机通讯速率*/ //125kbps




 /* 函数名称：can_ifconfig_up
 * 功能描述：创建CAN网络,此函数需要移植IPROUTE2
 * 输入参数：device：物理设备名称，如"CAN0"
 *         bitrate:速率，如250000（250Kbps)
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_ifconfig_init(void);

/*
 * 函数名称：can_band
 * 功能描述：创绑定CAN设备
 * 输入参数：device：物理设备名称，如"CAN0"
 *         fd:SOCKET句柄
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_band_init(int *fd);

/*
 * 函数名称：can_write
 * 功能描述：CAN设备写数据
 * 输入参数：fd:SOCKET句柄
 *          pFrame：CAN帧数据指针
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_write(int fd,struct canfd_frame *pFrame);

/*
 * 函数名称：can_read
 * 功能描述：CAN设备读数据
 * 输入参数：fd:SOCKET句柄
 *          pFrame：CAN帧数据指针
 *          msTimeout：超时时间MS
 * 输出参数：0有效，其他失效
 */
bool HAL_can0_read(int fd, struct canfd_frame *pFrame,unsigned int msTimeout);


/*
 * 函数名称：can_close
 * 功能描述：CAN关闭
 * 输入参数：fd:SOCKET句柄
 * 输出参数：无
 */
void HAL_can0_closeEx(int *fd);

/*
 * 函数名称：int can_set_filter(int fd, struct can_filter *__can_filter , int  num);

 * 功能描述：can 设置过滤
 */
bool HAL_can0_set_filter(int fd, struct can_filter *__can_filter , int  num);

int HAL_can0_get_state(const char *name, int *state);
#endif


