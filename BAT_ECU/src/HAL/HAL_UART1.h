#ifndef __HAL_UART1_H__
#define __HAL_UART1_H__

#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <errno.h>
#include <stdint.h>
#include "stdbool.h"
#include <termios.h>
#include <sys/stat.h>


int HAL_open_port(int uart_num);

#endif