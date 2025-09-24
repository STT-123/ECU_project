#ifndef __FUNC_EPOLL_DEALWITH_H__
#define __FUNC_EPOLL_DEALWITH_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
void *Thread_Myepoll(void *arg);
void my_epoll_dealwith(void);
#endif