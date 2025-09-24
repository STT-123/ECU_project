#ifndef __LOG_SAVE_TASK_H__
#define __LOG_SAVE_TASK_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

void SDCardDataSaveTaskCreate(void);
#endif