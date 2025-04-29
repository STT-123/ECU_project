#ifndef __DRV_SDCARD_H__
#define __DRV_SDCARD_H__

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <./GLB/G_GloabalVariable.h>
#define MAX_FILES_IN_FOLDER 80
#define BUFFER_SIZE 200  // 每个环形缓冲区的容量
#define BUFFERED_WRITE_SIZE 100

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Rtc_Ip_TimedateType;

typedef struct {
	uint32_t relativeTimestamp; // 相对时间戳
//    char formattedMessage[50];  // 用于存储格式化后的CAN消息
	CAN_MESSAGE msg;
	unsigned char channel;
} CAN_LOG_MESSAGE;

typedef struct {
    CAN_LOG_MESSAGE buffer[BUFFER_SIZE];
    size_t writeIndex;
    size_t readIndex;
    size_t count;  // 当前缓冲区中的消息数量
    pthread_mutex_t mutex;  // 保护缓冲区访问的互斥量
} RingBuffer;
typedef struct {
    RingBuffer buffers[2];
    int activeBuffer;             // 当前活跃缓冲区索引
    pthread_mutex_t switchMutex; // 用于保护缓冲区切换
} DoubleRingBuffer;

DoubleRingBuffer canDoubleRingBuffer;

int check_and_update_message(const CAN_MESSAGE *msg);
void write_to_active_buffer(const CAN_MESSAGE *msg, uint8_t channel);
void swap_buffers(DoubleRingBuffer *drb) ;
void write_canmsg_cache_to_file(FILE *file, uint32_t timestamp_ms);
void CreateFilePath(char *filePath, struct tm *timeinfo);
void write_buffer_to_file(DoubleRingBuffer *drb) ;
#endif