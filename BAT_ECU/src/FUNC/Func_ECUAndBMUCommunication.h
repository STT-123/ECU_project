#ifndef __ECU_AND_BMU_COMMUNICATION_H__
#define __ECU_AND_BMU_COMMUNICATION_H__
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
#include <semaphore.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>

void CAN1RecvDelTaskCreate(void);

#endif