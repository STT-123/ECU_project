#ifndef __SD_CAPACITY_CHECK_TASK_H__
#define __SD_CAPACITY_CHECK_TASK_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/statvfs.h>
#include <sys/stat.h>


void SDCapacityChenkTaskCreate(void);
#endif