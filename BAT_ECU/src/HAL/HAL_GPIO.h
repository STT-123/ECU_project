#ifndef ___INC_HAL_GPIO_H__
#define ___INC_HAL_GPIO_H__


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include "fcntl.h"
#include <errno.h>


#define	IO_OUTPUT_L				0
#define	IO_OUTPUT_H				1

int HAL_GPIO_Export(int pin);
int HAL_GPIO_Unexport(int pin);
int HAL_GPIO_Direction(int pin, int dir);
int HAL_GPIO_Write(int pin, int value);
int HAL_GPIO_Read(int pin);
int HAL_gpio_set_edge(unsigned int gpio, char *edge);
int HAL_gpio_fd_open(unsigned int gpio);
int HAL_gpio_fd_close(int fd);
int HAL_GPIO_open_epoll(int pin);
int HAL_GPIO_read_epoll(int pin,int fd,int *read_value);
#endif