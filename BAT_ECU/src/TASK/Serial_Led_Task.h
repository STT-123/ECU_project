#ifndef __SERIAL_LED_TASK_H__
#define __SERIAL_LED_TASK_H__
#include <pthread.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void SerialLedTask_func(void* arg);
void SerialLedTaskCreate(void);

#endif