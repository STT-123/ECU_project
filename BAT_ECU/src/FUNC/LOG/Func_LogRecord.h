#ifndef __FUNC_LOG_RECORD_H__
#define __FUNC_LOG_RECORD_H__

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
#include <syslog.h>
#include <stdio.h>
// bool debug_enabled;
// #define LOG_INIT(b) {debug_enabled=b;}
// #define LOG(...) {if(debug_enabled){printf(__VA_ARGS__);}}
// // #define LOG(...) {if(debug_enabled){syslog(LOG_INFO,__VA_ARGS__);}}


// #define ERROR(...) {syslog(LOG_ERR,__VA_ARGS__);}

// #define LOGI(fmt, args...)  printf(fmt, ##args)
// #define LOGD(fmt, args...) printf( fmt, ##args)
// #define LOGE(fmt, args...) printf( fmt, ##args)
void *Thread_Log(void *arg);

#endif