#define _GNU_SOURCE
#include "Drv_SDCard.h"
#include "./GLB/G_GloabalVariable.h"

#define CAN_ID_HISTORY_SIZE 32

uint32_t CAN_IDs[] = {
    0x180110E4, 0x180210E4, 0x180310E4, 0x180410E4, 0x180510E4,0x180610E4,
    0x180710E4, 0x180810E4, 0x180A10E4, 0x180B10E4, 0x180C10E4,0x180D10E4,
    0x180E10E4, 0x180F10E4, 0x181010E4, 0x181110E4, 0x181210E4,0x181310E4,
    0x181410E4, 0x181510E4, 0x181610E4, 0x181710E4, 0x181810E4,0x1A0110E4,
    0x1B0110E4, 0x1B0210E4, 0x1B0310E4, 0x1B0410E4, 0x1B0510E4,0x1C0110E4,
    0x1CA010E4, 0x1CA010E5
};
static CAN_MESSAGE can_msg_1A0110E4_cache[80]; //单体电压，一包三个，一共240个，索引分80帧
static CAN_MESSAGE can_msg_1B0110E4_cache[20]; //单体温度，一包六个，一共120个，索引分20帧
static CAN_MESSAGE can_msg_1B0210E4_cache[5];  //AFE温度，一包五个，一共15个，索引分5帧
static CAN_MESSAGE can_msg_1B0310E4_cache[5]; //bmu电压，一包三个，一共15个，索引分5帧

CAN_MESSAGE can_msg_cache[CAN_ID_HISTORY_SIZE] = {0};
struct timespec  start_tick ;

DoubleRingBuffer canDoubleRingBuffer;

// 初始化缓存
void init_can_id_history() {
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
        can_msg_cache[i].ID = CAN_IDs[i];
        can_msg_cache[i].Length = 8;
    }
}

// 消息比对并更新缓存
// int check_and_update_message(const CAN_MESSAGE *msg) {
//     for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
//         if (can_msg_cache[i].ID == msg->ID) {
//             if (memcmp(&can_msg_cache[i].Data, msg->Data, 8) != 0) {
//                 memcpy(&can_msg_cache[i].Data, msg->Data, 8);
//                 return 1;
//             } else {
//                 return 0;
//             }
//         }
//     }
//     return 0;
// }

// 写入缓冲

void CAN_Receive_Callback(CAN_MESSAGE *msg) {
    struct timespec now_tick;
    clock_gettime(CLOCK_MONOTONIC, &now_tick);

    RingBuffer *active = &canDoubleRingBuffer.buffers[canDoubleRingBuffer.activeBuffer];

    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_nsec += 10 * 1000 * 1000; // 10ms = 10,000,000 ns
    if (timeout.tv_nsec >= 1000000000) {
        timeout.tv_sec += timeout.tv_nsec / 1000000000;
        timeout.tv_nsec = timeout.tv_nsec % 1000000000;
    }

    if (pthread_mutex_timedlock(&active->mutex, &timeout) == 0) { // 成功拿到锁
        if (active->count < BUFFER_SIZE) {
            CAN_LOG_MESSAGE *log = &active->buffer[active->writeIndex];
            log->msg = *msg;

            // 计算相对时间戳（单位：毫秒，或者根据你的需求）
            uint32_t diff_ms = (now_tick.tv_sec - start_tick.tv_sec) * 1000 
                             + (now_tick.tv_nsec - start_tick.tv_nsec) / 1000000;
            log->relativeTimestamp = diff_ms;

            active->writeIndex = (active->writeIndex + 1) % BUFFER_SIZE;
            active->count++;
        }
        pthread_mutex_unlock(&active->mutex);
    }
}


void save_buffered_data_to_file(const char *basePath) {
    RingBuffer *active = &canDoubleRingBuffer.buffers[canDoubleRingBuffer.activeBuffer];
    RingBuffer *backup = &canDoubleRingBuffer.buffers[1 - canDoubleRingBuffer.activeBuffer];

    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_nsec += 10 * 1000 * 1000; // 10ms
    if (timeout.tv_nsec >= 1000000000) {
        timeout.tv_sec += timeout.tv_nsec / 1000000000;
        timeout.tv_nsec %= 1000000000;
    }

    if (pthread_mutex_timedlock(&canDoubleRingBuffer.switchMutex, &timeout) == 0) {
        canDoubleRingBuffer.activeBuffer = 1 - canDoubleRingBuffer.activeBuffer;
        pthread_mutex_unlock(&canDoubleRingBuffer.switchMutex);
    } else {
        // 拿不到锁就不切换，直接返回
        return;
    }

    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_nsec += 100 * 1000 * 1000; // 100ms
    if (timeout.tv_nsec >= 1000000000) {
        timeout.tv_sec += timeout.tv_nsec / 1000000000;
        timeout.tv_nsec %= 1000000000;
    }

    if (pthread_mutex_timedlock(&backup->mutex, &timeout) == 0) {
        if (backup->count > 0) {
            // 生成文件名
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char filename[256];
            snprintf(filename, sizeof(filename), "%s/%04d%02d%02d%02d%02d%02d.asc",
                     basePath, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                     t->tm_hour, t->tm_min, t->tm_sec);

            FILE *file = fopen(filename, "w");
            if (file) {
                for (size_t i = 0; i < backup->count; i++) {
                    CAN_LOG_MESSAGE *log = &backup->buffer[(backup->readIndex + i) % BUFFER_SIZE];
                    fprintf(file, "%08X [%u] ", log->msg.ID, log->msg.Length);
                    for (int j = 0; j < log->msg.Length; j++) {
                        fprintf(file, "%02X ", log->msg.Data[j]);
                    }
                    fprintf(file, "\r\n");
                }
                fclose(file);
            }
            // 清空备份缓冲区
            backup->count = 0;
            backup->writeIndex = backup->readIndex = 0;
        }
        pthread_mutex_unlock(&backup->mutex);
    }
}

// 删除老文件
void check_and_delete_old_files(const char *folderPath) {
    DIR *dir;
    struct dirent *entry;
    char oldestFilePath[512] = {0};
    time_t oldestTime = LONG_MAX;
    int fileCount = 0;

    dir = opendir(folderPath);
    if (dir != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // 只处理普通文件
                fileCount++;
                struct tm tmFile = {0};
                char baseName[16] = {0};
                if (sscanf(entry->d_name, "%15[^.]", baseName) == 1 && strlen(baseName) == 14) {
                    if (sscanf(baseName, "%4d%2d%2d%2d%2d%2d",
                               &tmFile.tm_year, &tmFile.tm_mon, &tmFile.tm_mday,
                               &tmFile.tm_hour, &tmFile.tm_min, &tmFile.tm_sec) == 6) {
                        tmFile.tm_year -= 1900;
                        tmFile.tm_mon -= 1;
                        time_t fileTime = mktime(&tmFile);

                        if (fileTime != (time_t)(-1) && fileTime < oldestTime) {
                            oldestTime = fileTime;
                            snprintf(oldestFilePath, sizeof(oldestFilePath), "%s/%s", folderPath, entry->d_name);
                        }
                    }
                }
            }
        }
        closedir(dir);

        if (fileCount > MAX_FILES_IN_FOLDER && oldestFilePath[0]) {
            remove(oldestFilePath);
        }
    }
}


void RTCGetTime(Rtc_Ip_TimedateType *rtcTime) {
    time_t now = time(NULL);
    struct tm localTime;

    localtime_r(&now, &localTime);

    rtcTime->year = localTime.tm_year + 1900;
    rtcTime->month = localTime.tm_mon + 1;
    rtcTime->day = localTime.tm_mday;
    rtcTime->hour = localTime.tm_hour;
    rtcTime->minute = localTime.tm_min;
    rtcTime->second = localTime.tm_sec;
}


bool CheckTimeChange(Rtc_Ip_TimedateType *currentTime) {
    static Rtc_Ip_TimedateType previousTime;
    static int initialized = 0;

    if (!initialized) {
        RTCGetTime(&previousTime);
        initialized = 1;
    }

    if (currentTime->year == 1970 && currentTime->month == 1 && currentTime->day == 1) {
        return false;
    }

    if (currentTime->day != previousTime.day || currentTime->month != previousTime.month ||
        currentTime->year != previousTime.year) {
        previousTime = *currentTime;
        return true;
    }

    return false;
}

// uint32_t GetTimeDifference_ms(struct timespec start_tick) {
//     struct timespec current_tick;
//     clock_gettime(CLOCK_MONOTONIC, &current_tick);

//     uint32_t diff_sec = current_tick.tv_sec - start_tick.tv_sec;
//     int32_t diff_nsec = current_tick.tv_nsec - start_tick.tv_nsec;

//     return diff_sec * 1000 + diff_nsec / 1000000;
// }





void init_double_ring_buffer(DoubleRingBuffer *drb) {
    for (int i = 0; i < 2; ++i) {
        drb->buffers[i].writeIndex = 0;
        drb->buffers[i].readIndex = 0;
        drb->buffers[i].count = 0;
        pthread_mutex_init(&drb->buffers[i].mutex, NULL);
    }
    drb->activeBuffer = 0;
    pthread_mutex_init(&drb->switchMutex, NULL);

    clock_gettime(CLOCK_MONOTONIC, &start_tick);
}



// 查找指定CAN ID的历史消息，并与当前消息对比
int check_and_update_message(const CAN_MESSAGE *msg) {
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
//		Debug_Printf("msg->ID :%x\r\n",msg->ID);
        if (can_msg_cache[i].ID == msg->ID) {
        	if(msg->ID == 0x1A0110E4)
        	{
        		if((msg->Data[0]>80)||(msg->Data[0]==0))
        		{
        			return 0;
        		}
				if (memcmp(&can_msg_1A0110E4_cache[msg->Data[0]-1].Data, msg->Data, 8) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1A0110E4_cache[msg->Data[0]-1].Data, msg->Data, 8);
					return 1; // 表示消息已修改
				}
        	}
        	if(msg->ID == 0x1B0110E4)
        	{
        		if((msg->Data[0]>20)||(msg->Data[0]==0))
				{
					return 0;
				}
        		if (memcmp(&can_msg_1B0110E4_cache[msg->Data[0]-1].Data, msg->Data, 8) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1B0110E4_cache[msg->Data[0]-1].Data, msg->Data, 8);
					return 1; // 表示消息已修改
				}
        	}
        	if(msg->ID == 0x1B0210E4)
			{
				if((msg->Data[0]>5)||(msg->Data[0]==0))
				{
					return 0;
				}
				if (memcmp(&can_msg_1B0210E4_cache[msg->Data[0]-1].Data, msg->Data, 8) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1B0210E4_cache[msg->Data[0]-1].Data, msg->Data, 8);
					return 1; // 表示消息已修改
				}
			}
        	if(msg->ID == 0x1B0310E4)
			{
				if((msg->Data[0]>5)||(msg->Data[0]==0))
				{
					return 0;
				}
				if (memcmp(&can_msg_1B0310E4_cache[msg->Data[0]-1].Data, msg->Data, 8) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1B0310E4_cache[msg->Data[0]-1].Data, msg->Data, 8);
					return 1; // 表示消息已修改
				}
			}

            if (memcmp(&can_msg_cache[i].Data, msg->Data, 8) == 0) {
                      return 0;  // 表示消息未修改
            } else {
                // 如果消息不同，则更新历史消息
                memcpy(&can_msg_cache[i].Data, msg->Data, 8);
               return 1;  // 表示消息已修改
            }
        }
    }
    return 0;  // 如果未找到该 CAN ID
}




void write_to_active_buffer(const CAN_MESSAGE *msg, uint8_t channel) {
    DoubleRingBuffer *drb = &canDoubleRingBuffer;

    if (((msg->ID == 0x1cb0e410) && (msg->Data[0] == 0xC9)) ||
        (msg->ID == 0x1cb010e4) || (msg->ID == 0x1823E410)) {
        return;
    }

    if (check_and_update_message(msg) == 0) return;

    pthread_mutex_lock(&drb->switchMutex);
    RingBuffer *activeBuffer = &drb->buffers[drb->activeBuffer];
    pthread_mutex_lock(&activeBuffer->mutex);

    CAN_LOG_MESSAGE *logMsg = &activeBuffer->buffer[activeBuffer->writeIndex];
    logMsg->relativeTimestamp = GetTimeDifference_ms(start_tick);
    memcpy(&logMsg->msg, msg, sizeof(CAN_MESSAGE));
    logMsg->channel = channel;

    activeBuffer->writeIndex = (activeBuffer->writeIndex + 1) % BUFFER_SIZE;

    if (activeBuffer->count == BUFFER_SIZE) {
        activeBuffer->readIndex = (activeBuffer->readIndex + 1) % BUFFER_SIZE;
    } else {
        activeBuffer->count++;
    }

    pthread_mutex_unlock(&activeBuffer->mutex);
    pthread_mutex_unlock(&drb->switchMutex);
}

void swap_buffers(DoubleRingBuffer *drb) {
    pthread_mutex_lock(&drb->switchMutex);
    drb->activeBuffer = 1 - drb->activeBuffer;
    pthread_mutex_unlock(&drb->switchMutex);
}




void write_canmsg_cache_to_file(FILE *file, uint32_t timestamp_ms) {
    if (!file) return;

    unsigned short index = 0;
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
        CAN_MESSAGE *logMsg = &can_msg_cache[i];
        if (CAN_IDs[i] == 0x1A0110E4) {
            logMsg = &can_msg_1A0110E4_cache[index++];
            if (index < 80) { i--; } else { index = 0; }
        } else if (CAN_IDs[i] == 0x1B0110E4) {
            logMsg = &can_msg_1B0110E4_cache[index++];
            if (index < 20) { i--; } else { index = 0; }
        } else if (CAN_IDs[i] == 0x1B0210E4) {
            logMsg = &can_msg_1B0210E4_cache[index++];
            if (index < 5) { i--; } else { index = 0; }
        } else if (CAN_IDs[i] == 0x1B0310E4) {
            logMsg = &can_msg_1B0310E4_cache[index++];
            if (index < 5) { i--; } else { index = 0; }
        }

        // 构造带时间戳的字符串
        char timeStampedMessage[BUFFERED_WRITE_SIZE];
        unsigned char offset = 0;

        // 时间戳
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage) - offset,
                           "%d.%03d 1 ", timestamp_ms / 1000, timestamp_ms % 1000);

        // ID + 长度
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage) - offset,
                           "%03lXx Rx d %d ", logMsg->ID, logMsg->Length);

        // 数据
        for (int j = 0; j < logMsg->Length; ++j) {
            offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage) - offset,
                               "%02X ", logMsg->Data[j]);
        }

        // 换行
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage) - offset, "\r\n");

        // 写入文件
        fseek(file, 0, SEEK_END);
        fwrite(timeStampedMessage, 1, offset, file);
    }

    // 建议写完后刷新缓冲
    fflush(file);
}






void CreateFilePath(char *filePath, struct tm *timeinfo) {
    // 创建一级目录（年月日）
    char firstLevelFolderPath[100];
    sprintf(firstLevelFolderPath, "./%04d%02d%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);

    // 创建目录（如果不存在）
    struct stat st = {0};
    if (stat(firstLevelFolderPath, &st) == -1) {
        mkdir(firstLevelFolderPath, 0777);
    }

    // 生成完整文件路径（年月日时分秒）
    sprintf(filePath, "%s/%04d%02d%02d%02d%02d%02d.asc",
            firstLevelFolderPath,
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void WriteFileHeader(FILE *file, struct tm *timeinfo) {
    char header[256];
    const char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // 格式化头信息
    sprintf(header, "date %s %s %02d %02d:%02d:%02d %s %04d\r\n",
            weekDays[timeinfo->tm_wday], months[timeinfo->tm_mon], timeinfo->tm_mday,
            (timeinfo->tm_hour > 12) ? (timeinfo->tm_hour - 12) : timeinfo->tm_hour,
            timeinfo->tm_min, timeinfo->tm_sec,
            (timeinfo->tm_hour >= 12) ? "PM" : "AM",
            timeinfo->tm_year + 1900);

    strcat(header, "base hex timestamps absolute\r\n");
    strcat(header, "// version 7.0.0\r\n");

    fwrite(header, sizeof(char), strlen(header), file);
}





void write_buffer_to_file(DoubleRingBuffer *drb) {
    static struct tm startTime;
    static bool newFileNeeded = true;
    static char filePath[256];
    static int SD_FAULT_count = 0;
    static int new_file_count = 0;

    FILE *file = NULL;
    int messagesToWrite = 0;

    int inactiveBufferIndex = 1 - drb->activeBuffer;
    RingBuffer *inactiveBuffer = &drb->buffers[inactiveBufferIndex];

    if (pthread_mutex_lock(&inactiveBuffer->mutex) == 0) {

        if (newFileNeeded) {
            time_t rawtime = time(NULL);
            struct tm *timeinfo = localtime(&rawtime);
            CreateFilePath(filePath, timeinfo);

            // 使用 fopen 替代 f_open
            file = fopen(filePath, "w");
            if (!file) {
                SD_FAULT_count++;
                if (SD_FAULT_count > 5) {
                    // 错误处理
                    SD_FAULT_count = 5;
                }
                pthread_mutex_unlock(&inactiveBuffer->mutex);
                return;
            }
            SD_FAULT_count = 0;

            WriteFileHeader(file, &startTime);
            // 缓冲区数据写入
            // write_canmsg_cache_to_file(&file, 0);  // 这里你可以根据实际需求来实现数据写入
            fclose(file);
            newFileNeeded = false;
        }

        file = fopen(filePath, "a");  // 使用 "a" 以追加模式打开文件
        if (!file) {
            SD_FAULT_count++;
            if (SD_FAULT_count > 5) {
                SD_FAULT_count = 5;
            }
            pthread_mutex_unlock(&inactiveBuffer->mutex);
            return;
        }
        SD_FAULT_count = 0;

        int messagesToWrite = 0;
        while (inactiveBuffer->count > 0) {
            CAN_LOG_MESSAGE *logMsg = &inactiveBuffer->buffer[inactiveBuffer->readIndex];

            char dataStr[3 * 8 + 1] = {0};
            for (int i = 0; i < logMsg->msg.Length; ++i) {
                snprintf(&dataStr[i * 3], 4, "%02X ", logMsg->msg.Data[i]);
            }

            char modifiedMessage[BUFFERED_WRITE_SIZE];
            if (logMsg->channel == 0) {
                snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Rx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
            } else if (logMsg->channel == 1) {
                snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Tx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
            }

            memmove(&modifiedMessage[9], &modifiedMessage[8], strlen(&modifiedMessage[8]) + 1);
            modifiedMessage[8] = 'x';

            char timeStampedMessage[BUFFERED_WRITE_SIZE];
            int dataLen = snprintf(timeStampedMessage, sizeof(timeStampedMessage), "%d.%03d 1 %s", 0, 0, modifiedMessage);

            fwrite(timeStampedMessage, sizeof(char), dataLen, file);

            inactiveBuffer->readIndex = (inactiveBuffer->readIndex + 1) % BUFFER_SIZE;
            inactiveBuffer->count--;
        }

        // 检查文件大小，如果文件超过10MB，则创建新的文件
        fseek(file, 0, SEEK_END);  // 文件指针移到文件末尾
        long fileSize = ftell(file);
        if (fileSize > (10 * 1024 * 1024)) {
            newFileNeeded = true;
            inactiveBuffer->count = 0;
        }

        fflush(file);  // 相当于 f_sync
        fclose(file);
        pthread_mutex_unlock(&inactiveBuffer->mutex);
    } else {
        return;
    }
}
