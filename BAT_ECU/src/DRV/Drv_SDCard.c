#define _GNU_SOURCE
#include "Drv_SDCard.h"
#include "./GLB/G_GloabalVariable.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include    "main.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

DoubleRingBuffer canDoubleRingBuffer;

struct tm timeinfo;
bool newFileNeeded_flag;

 Rtc_Ip_TimedateType initialTime;
 Rtc_Ip_TimedateType currentTime;
struct timespec start_tick;
#define CAN_ID_HISTORY_SIZE 6
static char filePath[256];
// uint32_t CAN_IDs[] = {
//     0x180110E4, 0x180210E4, 0x180310E4, 0x180410E4, 0x180510E4,0x180610E4,
//     0x180710E4, 0x180810E4, 0x180A10E4, 0x180B10E4, 0x180C10E4,0x180D10E4,
//     0x180E10E4, 0x180F10E4, 0x181010E4, 0x181110E4, 0x181210E4,0x181310E4,
//     0x181410E4, 0x181510E4, 0x181610E4, 0x181710E4, 0x181810E4,0x1A0110E4,
//     0x1B0110E4, 0x1B0210E4, 0x1B0310E4, 0x1B0410E4, 0x1B0510E4,0x1C0110E4,
//     0x1CA010E4, 0x1CA010E5
// };
uint32_t CAN_IDs[] = {
    0x180110E4, 
    0x180210E4, 
    0x180310E4, 
    0x180410E4,
    0x1A0110E4,
    0x1B0110E4, 
};
static CAN_MESSAGE can_msg_1A0110E4_cache[8]; //单体电压，一包30个，一共240个，索引分8帧
static CAN_MESSAGE can_msg_1B0110E4_cache[2]; //单体温度，一包60个，一共120个，索引分2帧
// static CAN_MESSAGE can_msg_1B0210E4_cache[1];  //AFE温度，一包五个，一共15个，索引分5帧
// static CAN_MESSAGE can_msg_1B0310E4_cache[5]; //bmu电压，一包三个，一共15个，索引分5帧
static CAN_MESSAGE can_msg_180410E4_cache[1]; //bmu电压，AFE温度，一包15个，一共15个，索引分1帧
CAN_MESSAGE can_msg_cache[CAN_ID_HISTORY_SIZE] = {0};


DoubleRingBuffer canDoubleRingBuffer;

// 初始化缓存
void Drv_init_can_id_history() {

	int i = 0;
    for (i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
        can_msg_cache[i].ID = CAN_IDs[i];
        can_msg_cache[i].Length  = 64;

    }
    for (i = 0; i < 8; i++)
    {
    	can_msg_1A0110E4_cache[i].ID =0x1A0110E4;
    	can_msg_1A0110E4_cache[i].Length = 64;
    	can_msg_1A0110E4_cache[i].Data[0] = i+1;
    }
    for (i = 0; i < 2; i++)
	{
    	can_msg_1B0110E4_cache[i].ID =0x1B0110E4;
    	can_msg_1B0110E4_cache[i].Length = 64;
    	can_msg_1B0110E4_cache[i].Data[0] = i+1;
	}
    for (i = 0; i < 1; i++)
	{
    	can_msg_180410E4_cache[i].ID =0x180410E4;
    	can_msg_180410E4_cache[i].Length = 64;
    	can_msg_180410E4_cache[i].Data[0] = i+1;
	}


}


// 写入缓冲

void Drv_CAN_Receive_Callback(CANFD_MESSAGE *msg) {
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
            log->msg = *msg;//修改0507

            // 计算相对时间戳（单位：毫秒，或者根据你的需求）
            uint32_t diff_ms = (now_tick.tv_sec - start_tick.tv_sec) * 1000 
                             + (now_tick.tv_nsec - start_tick.tv_nsec) / 1000000;
            log->relativeTimestamp = diff_ms;
            

            printf("log->relativeTimestamp: %d\n",log->relativeTimestamp);

            active->writeIndex = (active->writeIndex + 1) % BUFFER_SIZE;
            active->count++;
        }
        pthread_mutex_unlock(&active->mutex);
    }
}


void Drv_save_buffered_data_to_file(const char *basePath) {
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
void Drv_check_and_delete_old_files(const char *folderPath) {
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


void Drv_RTCGetTime(Rtc_Ip_TimedateType *rtcTime) {
    // time_t now = time(NULL);
    // struct tm localTime;

    // localtime_r(&now, &localTime);
    // printf("%s\n", asctime(&localTime));

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    rtcTime->year = tm_info->tm_year+1900;
    rtcTime->month = tm_info->tm_mon+1;
    rtcTime->day = tm_info->tm_mday;
    rtcTime->hour = tm_info->tm_hour;
    rtcTime->minutes = tm_info ->tm_min;
    rtcTime->seconds = tm_info ->tm_sec;
//     printf("Drv_RTCGetTime tm_info: %04d-%02d-%02d %02d:%02d:%02d\n",tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,tm_info->tm_hour,tm_info ->tm_min,
// tm_info ->tm_sec);
//     printf("Drv_RTCGetTime Current time: %04d-%02d-%02d %02d:%02d:%02d\n", rtcTime->year, rtcTime->month, rtcTime->day,
//                rtcTime->hour, rtcTime->minutes, rtcTime->seconds);
    
}


bool Drv_CheckTimeChange(Rtc_Ip_TimedateType *currentTime) {
    static Rtc_Ip_TimedateType previousTime;
    static int initialized = 0;

    if (!initialized) {
        Drv_RTCGetTime(&previousTime);
        // printf("previousTime_1: %04d-%02d-%02d %02d:%02d:%02d\n", previousTime.year, previousTime.month, previousTime.day,
        //        previousTime.hour, previousTime.minutes, previousTime.seconds);
        initialized = 1;
    }
    // printf("previousTime_2: %04d-%02d-%02d %02d:%02d:%02d\n", previousTime.year, previousTime.month, previousTime.day,
    //            previousTime.hour, previousTime.minutes, previousTime.seconds);
    if (currentTime->day != previousTime.day || currentTime->month != previousTime.month ||
        currentTime->year != previousTime.year) {
        previousTime = *currentTime;
        return true;
    }
    // printf("currentTime_1: %04d-%02d-%02d %02d:%02d:%02d\n", currentTime->year, currentTime->month, currentTime->day,
    //        currentTime->hour, currentTime->minutes, currentTime->seconds);
    if (currentTime->year == 1970 && currentTime->month == 1 && currentTime->day == 1) {
        return false;
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





void Drv_init_double_ring_buffer(DoubleRingBuffer *drb) {
    for (int i = 0; i < 2; ++i) {
        drb->buffers[i].writeIndex = 0;
        drb->buffers[i].readIndex = 0;
        drb->buffers[i].count = 0;
        pthread_mutex_init(&drb->buffers[i].mutex, NULL);
    }
    drb->activeBuffer = 0;
    pthread_mutex_init(&drb->switchMutex, NULL);

    // clock_gettime(CLOCK_MONOTONIC, &start_tick);
}



// 查找指定CAN ID的历史消息，并与当前消息对比
int Drv_check_and_update_message(const CANFD_MESSAGE *msg) {
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
		// printf("msg->ID :%x\r\n",msg->ID);
        if (can_msg_cache[i].ID == msg->ID) {
        	if(msg->ID == 0x1A0110E4)
        	{
        		if((msg->Data[0]>8)||(msg->Data[0]==0))
        		{
        			return 0;
        		}
				if (memcmp(&can_msg_1A0110E4_cache[msg->Data[0]-1].Data, msg->Data, 64) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1A0110E4_cache[msg->Data[0]-1].Data, msg->Data, 64);
					return 1; // 表示消息已修改
				}
        	}
        	if(msg->ID == 0x1B0110E4)
        	{
        		if((msg->Data[0]>2)||(msg->Data[0]==0))
				{
					return 0;
				}
        		if (memcmp(&can_msg_1B0110E4_cache[msg->Data[0]-1].Data, msg->Data, 64) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_1B0110E4_cache[msg->Data[0]-1].Data, msg->Data, 64);
					return 1; // 表示消息已修改
				}
        	}
        	if(msg->ID == 0x180410E4)
			{
				if((msg->Data[0]>1)||(msg->Data[0]==0))
				{
					return 0;
				}
				if (memcmp(&can_msg_180410E4_cache[msg->Data[0]-1].Data, msg->Data, 64) == 0)
				{
				   return 0;  // 表示消息未修改
				}
				else
				{
					memcpy(&can_msg_180410E4_cache[msg->Data[0]-1].Data, msg->Data, 64);
					return 1; // 表示消息已修改
				}
			}


            if (memcmp(&can_msg_cache[i].Data, msg->Data, 64) == 0) {
                      return 0;  // 表示消息未修改
            } else {
                // 如果消息不同，则更新历史消息
                memcpy(&can_msg_cache[i].Data, msg->Data, 64);
               return 1;  // 表示消息已修改
            }
        }
    }
    return 0;  // 如果未找到该 CAN ID
}




void Drv_write_to_active_buffer(const CANFD_MESSAGE *msg, uint8_t channel) {
    DoubleRingBuffer *drb = &canDoubleRingBuffer;

    if (((msg->ID == 0x1cb0e410) && (msg->Data[0] == 0xC9)) ||
        (msg->ID == 0x1cb010e4) || (msg->ID == 0x1823E410) || (msg->ID == 0)) {
        return;
    }
    // printf("ID: %x\n", msg->ID);

    if (Drv_check_and_update_message(msg) == 0) 
    {
        // printf("The message has not been modified.\n");
        return;//临时取消
    }
  

    pthread_mutex_lock(&drb->switchMutex);
    RingBuffer *activeBuffer = &drb->buffers[drb->activeBuffer];
    pthread_mutex_lock(&activeBuffer->mutex);

    CAN_LOG_MESSAGE *logMsg = &activeBuffer->buffer[activeBuffer->writeIndex];
    logMsg->relativeTimestamp = GetTimeDifference_ms(start_tick);
    // printf("logMsg->relativeTimestamp: %d\n", logMsg->relativeTimestamp);
    memcpy(&logMsg->msg, msg, sizeof(CANFD_MESSAGE));
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

void Drv_swap_buffers(DoubleRingBuffer *drb) {
    pthread_mutex_lock(&drb->switchMutex);
    drb->activeBuffer = 1 - drb->activeBuffer;
    // printf("Swapped buffers\n");
    pthread_mutex_unlock(&drb->switchMutex);
}




void Drv_write_canmsg_cache_to_file(FILE *file, uint32_t timestamp_ms) {
    if (file == NULL) {
    printf("Error: File pointer is NULL.\n");
    return;
    }
    // printf("Writing CAN message cache to file...\n");
    unsigned short index = 0;
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++) {
        CAN_MESSAGE *logMsg = &can_msg_cache[i];
        if (CAN_IDs[i] == 0x1A0110E4) {
            logMsg = &can_msg_1A0110E4_cache[index++];
            if (index < 8) { i--; } else { index = 0; }
        } 
        else if (CAN_IDs[i] == 0x1B0110E4) {
            logMsg = &can_msg_1B0110E4_cache[index++];
            if (index < 2) { i--; } else { index = 0; }
        } 
        else if (CAN_IDs[i] == 0x180410E4) {
            logMsg = &can_msg_180410E4_cache[index++];
            if (index < 1) { i--; } else { index = 0; }
        } 
        // 构造带时间戳的字符串
        char timeStampedMessage[BUFFERED_WRITE_SIZE];
        unsigned char offset = 0;

        // 时间戳
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage),
                           "%d.%03d 1 ", timestamp_ms / 1000, timestamp_ms % 1000);

        // ID + 长度
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage),
                           "%03lXx Rx d %d ", logMsg->ID, logMsg->Length);

        // printf("logMsg->msg.Length %d \r\n",logMsg->Length);
        // 数据
        for (int j = 0; j < logMsg->Length; ++j) {
            offset += snprintf(timeStampedMessage + offset, 4,
                               "%02X ", logMsg->Data[j]);
        }
        // 换行
        offset += snprintf(timeStampedMessage + offset, 4, "\r\n");
        // printf("%s\r\n",timeStampedMessage);
        // printf("file pointer address: %p\r\n", (void *)file);
        // printf("Wrote %zu bytes to file\r\n", offset);
        // 写入文件//阻塞
        size_t err = fseek(file, 0, SEEK_END);
        // printf("fseek error: %d\r\n", err);
        if (err != 0) {
            perror("fseek");
            printf("Failed to seek to end of file\n");
            return;
        }
        else
        {
            // printf("Success to seek to end of file\n");
        }

        err = fwrite(timeStampedMessage, 1, offset, file);
        if (err != offset) {
            printf("Failed to write to file\n");
            return;
        }
        else
        {
            // printf("Success to write to file\n");
        }
        // printf("Wrote %zu bytes to file\n", offset);
    }
    // printf("Flushing file\r\n");
    fflush(file);
}





void Drv_CreateFilePath(char *filePath, struct tm *timeinfo) {
    // 创建一级目录（年月日）
    char firstLevelFolderPath[100];
    // sprintf(firstLevelFolderPath, "./%04d%02d%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    snprintf(firstLevelFolderPath, sizeof(firstLevelFolderPath), "%s/%04d%02d%02d", USB_MOUNT_POINT, 
             timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
 

    // 创建目录（如果不存在）
    struct stat st = {0};
    // if (stat(firstLevelFolderPath, &st) == -1) {
    //     mkdir(firstLevelFolderPath, 0777);
    // }
    if (stat(firstLevelFolderPath, &st) == -1) {
    if (mkdir(firstLevelFolderPath, 0777) == -1) {
        perror("mkdir failed");
        return;
    }
}


    // 生成完整文件路径（年月日时分秒）
    sprintf(filePath, "%s/%04d%02d%02d%02d%02d%02d.asc",
            firstLevelFolderPath,
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("File path: %s\n", filePath);
    printf("%04d%02d%02d%02d%02d%02d\n",
           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void Drv_WriteFileHeader(FILE *file, struct tm *timeinfo) {
    if (file == NULL) {
    printf("Error: File pointer is NULL.\n");
    return;
    }
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

    size_t written = fwrite(header, sizeof(char), strlen(header), file);
    if (written < strlen(header)) {
    // printf("Warning: Header not fully written to file.\n");
    }
    // printf("Header written to file :%d\n",strlen(header));

}


int check_usb_removed(void) {
    FILE *fp = fopen("/proc/mounts", "r");
    if (!fp) {
        perror("fopen /proc/mounts failed");
        // printf("Error: Failed to open /proc/mounts.\n");
        return 1; // 认为U盘不可用
    }

    char line[512];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, USB_MOUNT_POINT)) {
            found = 1;
            // printf("USB device is still mounted.\n");
            break;
        }
    }
    fclose(fp);

    if (found) {
        // printf("USB device found: 1, returning 0 (U盘存在)\n");
        return 0; // U盘还在
    } else {
        // printf("USB device found: 0, returning 1 (U盘拔出)\n");
        return 1; // U盘被拔出
    }
}



void Drv_write_buffer_to_file(DoubleRingBuffer *drb) {
    static struct tm startTime;
    static bool newFileNeeded = true;
    static int SD_FAULT_count = 0;
    static int new_file_count = 0;

    FILE *file = NULL;
    int messagesToWrite = 0;

    int inactiveBufferIndex = 1 - drb->activeBuffer;
    RingBuffer *inactiveBuffer = &drb->buffers[inactiveBufferIndex];
    if (pthread_mutex_lock(&inactiveBuffer->mutex) == 0) {

    	if(newFileNeeded_flag == true)
    	{
    		newFileNeeded = true;
    		newFileNeeded_flag = false;
            printf("newFileNeeded\r\n");
    	}

        if (newFileNeeded) {
            // time_t rawtime = time(NULL);
            // struct tm *timeinfo = localtime(&rawtime);
            // Drv_CreateFilePath(filePath, timeinfo);

            if(BCU_TimeYear != 0)
            {
                // 填充外部时间变量到 tm 结构体
                timeinfo.tm_year = BCU_TimeYear + 100;    
                timeinfo.tm_mon  = BCU_TimeMonth - 1;  
                timeinfo.tm_mday = BCU_TimeDay;     
                timeinfo.tm_hour = BCU_TimeHour;
                timeinfo.tm_min  = BCU_TimeMinute;
                timeinfo.tm_sec  = BCU_TimeSencond;
                timeinfo.tm_isdst = -1;
                printf("BCU_Time:%d-%d-%d %d:%d:%d\r\n",BCU_TimeYear,BCU_TimeMonth,BCU_TimeDay,BCU_TimeHour,BCU_TimeMinute,BCU_TimeSencond);
                printf("timeinfo:%d-%d-%d %d:%d:%d\r\n",timeinfo.tm_year,timeinfo.tm_mon,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
            
                mktime(&timeinfo);
            }
            else
            {
                time_t now = time(NULL);
                struct tm *tm_info = localtime(&now);
                timeinfo = *tm_info;
                printf("timeinfo:%d-%d-%d %d:%d:%d\r\n",timeinfo.tm_year,timeinfo.tm_mon,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
            }


           
            int ret = check_usb_removed();
            if(ret != 0)
            {
                CP_set_emcu_fault(SD_FAULT,SET_ERROR);
                // printf("SD_FAULT_ret_1 : %d\r\n",ret);
                zlog_info(debug_out,"SD_FAULT_ret_1: %d\n", ret);
                pthread_mutex_unlock(&inactiveBuffer->mutex);
                return; 
            }
            Drv_CreateFilePath(filePath, &timeinfo);
            file = fopen(filePath, "a");
            if (!file) {
                SD_FAULT_count++;
                if (SD_FAULT_count > 5) {
                // 错误处理
                CP_set_emcu_fault(SD_FAULT,SET_ERROR);
                // printf("SD_FAULT_SD_FAULT_count \r\n",SD_FAULT_count);
                zlog_info(debug_out,"SD_FAULT_SD_FAULT_count: %d\n", SD_FAULT_count);
                SD_FAULT_count = 5;
                }
                pthread_mutex_unlock(&inactiveBuffer->mutex);
                return;
            }
            else
            {
                CP_set_emcu_fault(SD_FAULT,SET_RECOVER);
                printf("创建文件成功\n");
                zlog_info(debug_out,"创建文件成功\n");
            }
            SD_FAULT_count = 0;
            memcpy(&startTime,&timeinfo,sizeof(struct tm));
            Drv_WriteFileHeader(file, &startTime);
            // 缓冲区数据写入
            Drv_write_canmsg_cache_to_file(file, 0);  
            // printf("写入文件成功\n");
            size_t res = fclose(file);
            // printf("文件关闭结果：%d\n", res);
            newFileNeeded = false;
        }
        int ret = check_usb_removed();
        if(ret != 0)
        {
            CP_set_emcu_fault(SD_FAULT,SET_ERROR);
            // printf("SD_FAULT_ret : %d\r\n",ret);
            zlog_info(debug_out,"SD_FAULT_ret: %d\n", ret);
            pthread_mutex_unlock(&inactiveBuffer->mutex);
            return; 
        }

        file = fopen(filePath, "a");  // 使用 "a" 以追加模式打开文件
        if (!file) 
        {
            SD_FAULT_count++;
            if (SD_FAULT_count > 5) {
                CP_set_emcu_fault(SD_FAULT,SET_ERROR);
                // printf("SD_FAULT_SD_FAULT_count \r\n",SD_FAULT_count);
                zlog_info(debug_out,"SD_FAULT_SD_FAULT_count: %d\n", SD_FAULT_count);
                SD_FAULT_count = 5;
            }
            // printf("无法打开文件：%s\n", filePath);
            pthread_mutex_unlock(&inactiveBuffer->mutex);
            return;
        }
        else
        {
            CP_set_emcu_fault(SD_FAULT,SET_RECOVER);
        }
        // printf("使用以追加模式打开文件:file pointer address: %p\r\n", (void *)file);
        SD_FAULT_count = 0;

        int messagesToWrite = 0;
        fseek(file, 0, SEEK_END);

        // 获取文件大小
        long  fileSize = ftell(file);

        // printf("文件大小为: %ld 字节\n", fileSize);
        // printf("inactiveBuffer->count: %d\n",inactiveBuffer->count);//获取环形缓冲区中消息的个数
        while (inactiveBuffer->count > 0) 
        {
            CAN_LOG_MESSAGE *logMsg = &inactiveBuffer->buffer[inactiveBuffer->readIndex];

            char dataStr[3 * 64 + 1] = {0};
            for (int i = 0; i < logMsg->msg.Length && i<64; ++i) {
                snprintf(&dataStr[i * 3], 4, "%02X ", logMsg->msg.Data[i]);
            }
            // printf("CAN%d: %08X [%02X] %s %ld\n", logMsg->channel + 1, logMsg->msg.ID, logMsg->msg.Length,
            //        dataStr, logMsg->relativeTimestamp);
            char modifiedMessage[BUFFERED_WRITE_SIZE];
            if (logMsg->channel == 0) {
                snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Rx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
            } else if (logMsg->channel == 1) {
                snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Tx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
            }

            memmove(&modifiedMessage[9], &modifiedMessage[8], strlen(&modifiedMessage[8]) + 1);
            modifiedMessage[8] = 'x';
            // printf("modifiedMessage: %s\r\n",modifiedMessage);
            char timeStampedMessage[BUFFERED_WRITE_SIZE];
            // int dataLen = snprintf(timeStampedMessage, sizeof(timeStampedMessage), "%d.%03d 1 %s", 0, 0, modifiedMessage);
        	int dataLen = snprintf(timeStampedMessage, sizeof(timeStampedMessage), "%d.%03d 1 %s", logMsg->relativeTimestamp/1000,logMsg->relativeTimestamp%1000, modifiedMessage);

			// printf("timeStampedMessage: %s\r\n",timeStampedMessage);
			// printf("dataLen: %d\r\n",dataLen);
            size_t res = fwrite(timeStampedMessage, sizeof(char), dataLen, file);

            inactiveBuffer->readIndex = (inactiveBuffer->readIndex + 1) % BUFFER_SIZE;
            inactiveBuffer->count--;
        }

        // 检查文件大小，如果文件超过10MB，则创建新的文件
        fseek(file, 0, SEEK_END);  // 文件指针移到文件末尾
        fileSize = ftell(file);
        Drv_RTCGetTime(&currentTime);
        // printf("currentTime %d %d %d %d %d %d\r\n",currentTime.year,currentTime.month,currentTime.day,currentTime.hour,currentTime.minutes,currentTime.seconds);
        if (fileSize > (10 * 1024 * 1024) || Drv_CheckTimeChange(&currentTime)) {
        // if (fileSize > (10 * 1024 * 1024)) {

            // printf("文件大小超过10MB,创建新的文件\r\n");
            // Drv_write_canmsg_cache_to_file(&file,GetTimeDifference_ms(start_tick));//阻塞线程
            Drv_RTCGetTime(&initialTime);//1205
            clock_gettime(CLOCK_MONOTONIC, &start_tick);
            newFileNeeded = true;
            inactiveBuffer->count = 0;
           
            pthread_mutex_lock(&(drb->buffers[drb->activeBuffer].mutex));
            drb->buffers[drb->activeBuffer].count = 0;
			drb->buffers[drb->activeBuffer].writeIndex = 0;
			drb->buffers[drb->activeBuffer].readIndex = 0;
            pthread_mutex_unlock(&(drb->buffers[drb->activeBuffer].mutex));
        }
        fflush(file);  
        size_t err = fclose(file);
        pthread_mutex_unlock(&inactiveBuffer->mutex);
    } else {
        printf("write_buffer_to_file end return\n");
        return;
    }
    
}






int SD_Initialize(void) {
    int res;

    const char *device = "/dev/sda1";         
    // const char *mount_point = "/media/usb0";
    const char *mount_point = "/mnt/sda";

    // res = system("umount /media/usb0");
    res = system("umount /mnt/sda");
    if (res != 0) {
        // printf("umount failed (maybe not mounted): %d\n", res);
        zlog_info(debug_out,"umount failed (maybe not mounted):%d\n", res);
        
    } else {
        // printf("umount success\n");
        zlog_info(debug_out,"umount success\n");
    }

    char cmd[256];
    // snprintf(cmd, sizeof(cmd), "mkfs.vfat -F 32 %s", device);
    // snprintf(cmd, sizeof(cmd), "/sbin/mkdosfs -F 32 %s", device);
    snprintf(cmd, sizeof(cmd), "mkfs.ntfs -F %s", device);
    // snprintf(cmd, sizeof(cmd), "mkfs.ext4 -F %s", device);
    // snprintf(cmd, sizeof(cmd), "mkfs.ext4 -F -m 0 %s", device);


    res = system(cmd);
    if (res != 0) {
        printf("Format failed: %d\n", res);
        return res;
    } else {
        printf("Format (FAT32) success\n");
    }

    snprintf(cmd, sizeof(cmd), "mount %s %s", device, mount_point);
    res = system(cmd);
    if (res != 0) {
        printf("Mount failed: %d\n", res);
        return res;
    } else {
        printf("Mount success\n");
    }

    usleep(10*1000); // 替代 g_Delay_Ms(10)
    newFileNeeded_flag = true;

    // printf("USB drive formatted and mounted successfully\n");
    return 0;
}
