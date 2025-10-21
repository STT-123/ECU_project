#ifndef __HAL_CAN_H__
#define __HAL_CAN_H__

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

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

bool HAL_can_ifconfig_init(const char *device, int bitrate);
bool HAL_can1_ifconfig_init(const char *device, int bitrate);
bool HAL_can_band_init(const char *device, int *fd);

bool HAL_can1_ifconfig_init(const char *device, int bitrate);
bool HAL_can1_band_init(const char *device, int *fd);

bool HAL_can_write(int fd, struct canfd_frame *pFrame);
bool HAL_can_1_write(int fd, struct can_frame *pFrame);

int HAL_can_read(int fd, struct canfd_frame *pFrame, unsigned int msTimeout);
int HAL_can1_read(int fd, struct can_frame *pFrame, unsigned int msTimeout);

void HAL_can_closeEx(int *fd);

int HAL_can_get_state(const char *name, int *state);

#endif
