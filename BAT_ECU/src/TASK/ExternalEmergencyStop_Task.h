#ifndef __EXTERNALEMERGENCYSTOP_TASK_H__
#define __EXTERNALEMERGENCYSTOP_TASK_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "stdbool.h"
#include <termios.h>
#include <pthread.h>
void  GPIODetectionTaskCreate(void);
#endif