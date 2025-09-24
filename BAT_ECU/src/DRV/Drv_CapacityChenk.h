#ifndef __DRV_CAPACITY_CHECK_H__
#define __DRV_CAPACITY_CHECK_H__
 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
char *Drv_my_strdup(const char *str);
int Drv_remove_directory(const char *path);

#endif