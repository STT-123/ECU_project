#ifndef __HAL_TIM1_H__
#define __HAL_TIM1_H__ 

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
void timer_addepoll(uint32_t uisec, uint32_t uinsec,void  (*callback)(void* arg),unsigned char repeat);
#endif