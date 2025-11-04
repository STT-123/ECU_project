#define _GNU_SOURCE
#include "Drv_SDCard.h"
#include "./GLB/G_GloabalVariable.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "log/log.h"
#include "./CP/BMS/bms/CANRcvFcn.h"
#include <time.h>

// 检查U盘是否可用
// 0正常 1不正常
static int CheckUsbStatus(void)
{
    static int lastUsbStatus = 0;
    int ret = 1; // 默认不存在

    // 直接打开
    FILE *fp = fopen("/proc/mounts", "r");
    if (!fp)
    {
        perror("fopen /proc/mounts failed");
        ret = 1; // 认为U盘不可用
    }
    else
    {
        char line[128];
        while (fgets(line, sizeof(line), fp))
        {
            if (strstr(line, USB_MOUNT_POINT))
            {
                ret = 0; // 找到了
                break;
            }
        }
        fclose(fp);
    }

    // 变化打印
    if (ret != lastUsbStatus)
    {
        LOG("[SD Card] SDCard Status From %d to %d(0:ok, 1:not exist). \n", lastUsbStatus, ret);
        lastUsbStatus = ret;
    }

    return ret;
}

// 获取当前时间
static int      GetNowTime(struct tm *nowTime)
{
    struct tm timeinfo = {0};
    static time_t last_update_time = 0;
    time_t current_time = time(NULL);
    // 检查时间
    if (BCU_TimeYear != 0) // bcu发来时间了
    {
        // 填充外部时间变量到 tm 结构体
        timeinfo.tm_year = BCU_TimeYear + 100;
        timeinfo.tm_mon = BCU_TimeMonth - 1;
        timeinfo.tm_mday = BCU_TimeDay;
        timeinfo.tm_hour = BCU_TimeHour;
        timeinfo.tm_min = BCU_TimeMinute;
        timeinfo.tm_sec = BCU_TimeSencond;
        timeinfo.tm_isdst = -1;
        if (mktime(&timeinfo) == (time_t)-1) {
            LOG("WARNING: mktime failed for BCU time\n");
            // 设置一个默认的星期几
            timeinfo.tm_wday = 0; // 星期日
        }
        //如果是第一次更新或者距离上次更新超过1分钟
        if (last_update_time == 0 || (current_time - last_update_time) >= 60) // 60秒 = 1分钟
        {
            // 执行实际的时间更新操作
            G_set_system_time_from_bcu();
            LOG("update time\r\n");
            // 更新最后更新时间
            last_update_time = current_time;
        }
        LOG("[SD Card] Time Source From Bcu");
    }
    else // bcu没发过来时间 用自己本地的时间
    {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        timeinfo = *tm_info;
        mktime(&timeinfo);
        LOG("[SD Card] Time Source From Local");
    }

    // 得到当前时间
    *nowTime = timeinfo;
    LOG("[SD Card] Now Time: %d-%d-%d %d:%d:%d. ", timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return 0;
}

// 使用一个时间创建一个文件路径（文件夹+文件名）
static int CreateAscFilePathWithTime(struct tm timeInfo, char *filePath)
{
    // 创建文件夹路径
    char folderPath[256];
    snprintf(folderPath, sizeof(folderPath), "%s/%04d%02d%02d",
             USB_MOUNT_POINT,         // 挂载点
             timeInfo.tm_year + 1900, // 年
             timeInfo.tm_mon + 1,     // 月
             timeInfo.tm_mday);       // 日

    // 创建目录（如果不存在）
    struct stat st = {0};
    if (stat(folderPath, &st) == -1)
    {
        if (mkdir(folderPath, 0777) == -1)
        {
            perror("mkdir failed");
            LOG("[SD Card] mkdir failed");
            return 1;
        }
    }

    // 生成完整文件路径（年月日时分秒）
    sprintf(filePath, "%s/%04d%02d%02d%02d%02d%02d.asc",
            folderPath,              // 文件夹路径
            timeInfo.tm_year + 1900, // 年
            timeInfo.tm_mon + 1,     // 月
            timeInfo.tm_mday,        // 日
            timeInfo.tm_hour,        // 时
            timeInfo.tm_min,         // 分
            timeInfo.tm_sec);        // 秒

    LOG("[SD Card] new asc file path is = %04d%02d%02d%02d%02d%02d. \n",
        timeInfo.tm_year + 1900,
        timeInfo.tm_mon + 1,
        timeInfo.tm_mday,
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec);

    return 0;
}

static int OpenNowWriteAscFile(const char *filePath, FILE **file) {
    static int failed_count = 0;
    
    if (!filePath || !file) {
        LOG("ERROR: Invalid parameters to OpenNowWriteAscFile\n");
        return 1;
    }
    
    //printf(">>> Attempting to open file: %s\n", filePath);
    
    *file = fopen(filePath, "ab");
    
    if (!*file) {
        int err = errno;
        LOG("ERROR: fopen failed for %s, errno=%d (%s)\n", filePath, err, strerror(err));
        failed_count++;
        
        if (failed_count >= 5) {
            LOG("[SD Card] OpenNowWriteAscFile %s failed %d times, errno=%d\n", filePath, failed_count, err);
            CP_set_emcu_fault(SD_FAULT, SET_ERROR);
        }
        return 1;
    }

    if (failed_count >= 5) {
        LOG("[SD Card] OpenNowWriteAscFile %s recovered after %d failures\n", filePath, failed_count);
        CP_set_emcu_fault(SD_FAULT, SET_RECOVER);
    }
    failed_count = 0;
    
    LOG("SUCCESS: File opened successfully: %p\n", (void*)*file);
    return 0;
}
// 打开当前需要写的Asc文件
// static int OpenNowWriteAscFile(char *filePath, FILE **file)
// {
//     static int failed_count = 0;

//     *file = fopen(filePath, "a");
//     if (!*file)
//     {
//         // 打开失败
//         failed_count++;
//         if (failed_count >= 5)
//         {
//             if (failed_count <= 5)
//             {
//                 LOG("[SD Card] OpenNowWriteAscFile  %s failed, count: %d\n", filePath, failed_count);
//             }
//             failed_count = 10;
//             CP_set_emcu_fault(SD_FAULT, SET_ERROR); // 标记modbus寄存器错误
//         }

//         return 1;
//     }
//     else
//     {
//         if (failed_count >= 5)
//         {
//             LOG("[SD Card] OpenNowWriteAscFile %s ok, count: %d\n", filePath, failed_count);
//         }
//         failed_count = 0;
//         CP_set_emcu_fault(SD_FAULT, SET_RECOVER);

//         return 0;
//     }

//     return 0;
// }
// ASC文件写一个时间头
static int AscFileWriteTimeHeader(FILE *file, struct tm *timeinfo)
{
    LOG("=== AscFileWriteTimeHeader START ===\n");
    
    if (file == NULL)
    {
        LOG("CRITICAL ERROR: File pointer is NULL in AscFileWriteTimeHeader\n");
        return -1;
    }
    
    if (timeinfo == NULL)
    {
        LOG("CRITICAL ERROR: timeinfo is NULL in AscFileWriteTimeHeader\n");
        return -1;
    }
    
    // 验证时间字段的合理性
    LOG("Time info: wday=%d, mon=%d, mday=%d, hour=%d, min=%d, sec=%d, year=%d\n",
           timeinfo->tm_wday, timeinfo->tm_mon, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
           timeinfo->tm_year);
    
    char header[512] = {0}; // 增大缓冲区确保安全
    const char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // 检查数组索引边界
    if (timeinfo->tm_wday < 0 || timeinfo->tm_wday > 6) {
        LOG("ERROR: Invalid tm_wday: %d\n", timeinfo->tm_wday);
        return -1;
    }
    if (timeinfo->tm_mon < 0 || timeinfo->tm_mon > 11) {
        LOG("ERROR: Invalid tm_mon: %d\n", timeinfo->tm_mon);
        return -1;
    }

    // 使用安全的 snprintf 一次性构建整个头部
    int total_len = snprintf(header, sizeof(header),
                            "date %s %s %02d %02d:%02d:%02d %s %04d\r\n"
                            "base hex timestamps absolute\r\n"
                            "// version 7.0.0\r\n",
                            weekDays[timeinfo->tm_wday],
                            months[timeinfo->tm_mon],
                            timeinfo->tm_mday,
                            (timeinfo->tm_hour > 12) ? (timeinfo->tm_hour - 12) : 
                             (timeinfo->tm_hour == 0) ? 12 : timeinfo->tm_hour, // 处理 0 点的情况
                            timeinfo->tm_min, 
                            timeinfo->tm_sec,
                            (timeinfo->tm_hour >= 12) ? "PM" : "AM",
                            timeinfo->tm_year + 1900);
    
    LOG("Header length: %d, buffer size: %zu\n", total_len, sizeof(header));
    
    if (total_len < 0) {
        LOG("ERROR: snprintf failed\n");
        return -1;
    }
    
    if ((size_t)total_len >= sizeof(header)) {
        LOG("ERROR: Header too long: %d >= %zu\n", total_len, sizeof(header));
        return -1;
    }
    
    LOG("Header content:\n%s", header);
    
    // 写入文件
    size_t written = fwrite(header, 1, total_len, file);
    LOG("Bytes written: %zu, expected: %d\n", written, total_len);
    
    if (written != (size_t)total_len)
    {
        LOG("WARNING: Header not fully written to file: %zu != %d\n", written, total_len);
        return -1;
    }
    
    fflush(file); // 确保数据写入磁盘
    LOG("=== AscFileWriteTimeHeader COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
// // ASC文件写一个时间头
// static int AscFileWriteTimeHeader(FILE *file, struct tm *timeinfo)
// {
//     if (file == NULL)
//     {
//         printf("Error: File pointer is NULL.\n");
//         return;
//     }
//     char header[256];
//     const char *weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//     const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
//                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

//     // 格式化头信息
//     sprintf(header, "date %s %s %02d %02d:%02d:%02d %s %04d\r\n",
//             weekDays[timeinfo->tm_wday],
//             months[timeinfo->tm_mon],
//             timeinfo->tm_mday,
//             (timeinfo->tm_hour > 12) ? (timeinfo->tm_hour - 12) : timeinfo->tm_hour,
//             timeinfo->tm_min, timeinfo->tm_sec,
//             (timeinfo->tm_hour >= 12) ? "PM" : "AM",
//             timeinfo->tm_year + 1900);
//     strcat(header, "base hex timestamps absolute\r\n");
//     strcat(header, "// version 7.0.0\r\n");

//     size_t written = fwrite(header, sizeof(char), strlen(header), file);
//     if (written < strlen(header))
//     {
//         // printf("Warning: Header not fully written to file.\n");
//     }
//     // printf("Header written to file :%d\n",strlen(header));
// }

DoubleRingBuffer canDoubleRingBuffer;

static bool newFileNeeded = true;

Rtc_Ip_TimedateType initialTime;
Rtc_Ip_TimedateType currentTime;
struct timespec start_tick;
#define CAN_ID_HISTORY_SIZE 6
uint32_t CAN_IDs[] = {
    0x180110E4,
    0x180210E4,
    0x180310E4,
    0x180410E4,
    0x1A0110E4,
    0x1B0110E4,
};
static CAN_MESSAGE can_msg_1A0110E4_cache[8]; // 单体电压，一包30个，一共240个，索引分8帧
static CAN_MESSAGE can_msg_1B0110E4_cache[2]; // 单体温度，一包60个，一共120个，索引分2帧
static CAN_MESSAGE can_msg_180410E4_cache[1]; // bmu电压，AFE温度，一包15个，一共15个，索引分1帧
CAN_MESSAGE can_msg_cache[CAN_ID_HISTORY_SIZE] = {0};

DoubleRingBuffer canDoubleRingBuffer;

// 初始化缓存
void Drv_init_can_id_history(void)
{
    int i = 0;
    for (i = 0; i < CAN_ID_HISTORY_SIZE; i++)
    {
        can_msg_cache[i].ID = CAN_IDs[i];
        can_msg_cache[i].Length = 64;
    }
    for (i = 0; i < 8; i++)
    {
        can_msg_1A0110E4_cache[i].ID = 0x1A0110E4;
        can_msg_1A0110E4_cache[i].Length = 64;
        can_msg_1A0110E4_cache[i].Data[0] = i + 1;
    }
    for (i = 0; i < 2; i++)
    {
        can_msg_1B0110E4_cache[i].ID = 0x1B0110E4;
        can_msg_1B0110E4_cache[i].Length = 64;
        can_msg_1B0110E4_cache[i].Data[0] = i + 1;
    }
    for (i = 0; i < 1; i++)
    {
        can_msg_180410E4_cache[i].ID = 0x180410E4;
        can_msg_180410E4_cache[i].Length = 64;
        can_msg_180410E4_cache[i].Data[0] = i + 1;
    }
}

// 删除老文件
void Drv_check_and_delete_old_files(const char *folderPath)
{
    DIR *dir;
    struct dirent *entry;
    char oldestFilePath[512] = {0};
    time_t oldestTime = LONG_MAX;
    int fileCount = 0;

    dir = opendir(folderPath);
    if (dir != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            { // 只处理普通文件
                fileCount++;
                struct tm tmFile = {0};
                char baseName[16] = {0};
                if (sscanf(entry->d_name, "%15[^.]", baseName) == 1 && strlen(baseName) == 14)
                {
                    if (sscanf(baseName, "%4d%2d%2d%2d%2d%2d",
                               &tmFile.tm_year, &tmFile.tm_mon, &tmFile.tm_mday,
                               &tmFile.tm_hour, &tmFile.tm_min, &tmFile.tm_sec) == 6)
                    {
                        tmFile.tm_year -= 1900;
                        tmFile.tm_mon -= 1;
                        time_t fileTime = mktime(&tmFile);

                        if (fileTime != (time_t)(-1) && fileTime < oldestTime)
                        {
                            oldestTime = fileTime;
                            snprintf(oldestFilePath, sizeof(oldestFilePath), "%s/%s", folderPath, entry->d_name);
                        }
                    }
                }
            }
        }
        closedir(dir);

        if (fileCount > MAX_FILES_IN_FOLDER && oldestFilePath[0])
        {
            remove(oldestFilePath);
        }
    }
}

void Drv_RTCGetTime(Rtc_Ip_TimedateType *rtcTime)
{
    // time_t now = time(NULL);
    // struct tm localTime;

    // localtime_r(&now, &localTime);
    // printf("%s\n", asctime(&localTime));

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    rtcTime->year = tm_info->tm_year + 1900;
    rtcTime->month = tm_info->tm_mon + 1;
    rtcTime->day = tm_info->tm_mday;
    rtcTime->hour = tm_info->tm_hour;
    rtcTime->minutes = tm_info->tm_min;
    rtcTime->seconds = tm_info->tm_sec;
}

bool Drv_CheckTimeChange(Rtc_Ip_TimedateType *currentTime)
{
    static Rtc_Ip_TimedateType previousTime;
    static int initialized = 0;

    if (!initialized)
    {
        Drv_RTCGetTime(&previousTime);
        // printf("previousTime_1: %04d-%02d-%02d %02d:%02d:%02d\n", previousTime.year, previousTime.month, previousTime.day,
        //        previousTime.hour, previousTime.minutes, previousTime.seconds);
        initialized = 1;
    }
    // printf("previousTime_2: %04d-%02d-%02d %02d:%02d:%02d\n", previousTime.year, previousTime.month, previousTime.day,
    //            previousTime.hour, previousTime.minutes, previousTime.seconds);
    if (currentTime->day != previousTime.day || currentTime->month != previousTime.month ||
        currentTime->year != previousTime.year)
    {
        previousTime = *currentTime;
        return true;
    }
    // printf("currentTime_1: %04d-%02d-%02d %02d:%02d:%02d\n", currentTime->year, currentTime->month, currentTime->day,
    //        currentTime->hour, currentTime->minutes, currentTime->seconds);
    if (currentTime->year == 1970 && currentTime->month == 1 && currentTime->day == 1)
    {
        return false;
    }

    return false;
}

void Drv_init_double_ring_buffer(DoubleRingBuffer *drb)
{
    for (int i = 0; i < 2; ++i)
    {
        drb->buffers[i].writeIndex = 0;
        drb->buffers[i].readIndex = 0;
        drb->buffers[i].count = 0;
        pthread_mutex_init(&drb->buffers[i].mutex, NULL);
    }
    drb->activeBuffer = 0;
    pthread_mutex_init(&drb->switchMutex, NULL);
}

// 查找指定CAN ID的历史消息，并与当前消息对比
int Drv_check_and_update_message(const CANFD_MESSAGE *msg)
{
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++)
    {
        // printf("msg->ID :%x\r\n",msg->ID);
        if (can_msg_cache[i].ID == msg->ID)
        {
            if (msg->ID == 0x1A0110E4)
            {
                if ((msg->Data[0] > 8) || (msg->Data[0] == 0))
                {
                    return 0;
                }
                if (memcmp(&can_msg_1A0110E4_cache[msg->Data[0] - 1].Data, msg->Data, 64) == 0)
                {
                    return 0; // 表示消息未修改
                }
                else
                {
                    memcpy(&can_msg_1A0110E4_cache[msg->Data[0] - 1].Data, msg->Data, 64);
                    return 1; // 表示消息已修改
                }
            }
            if (msg->ID == 0x1B0110E4)
            {
                if ((msg->Data[0] > 2) || (msg->Data[0] == 0))
                {
                    return 0;
                }
                if (memcmp(&can_msg_1B0110E4_cache[msg->Data[0] - 1].Data, msg->Data, 64) == 0)
                {
                    return 0; // 表示消息未修改
                }
                else
                {
                    memcpy(&can_msg_1B0110E4_cache[msg->Data[0] - 1].Data, msg->Data, 64);
                    return 1; // 表示消息已修改
                }
            }
            if (msg->ID == 0x180410E4)
            {
                if ((msg->Data[0] > 1) || (msg->Data[0] == 0))
                {
                    return 0;
                }
                if (memcmp(&can_msg_180410E4_cache[msg->Data[0] - 1].Data, msg->Data, 64) == 0)
                {
                    return 0; // 表示消息未修改
                }
                else
                {
                    memcpy(&can_msg_180410E4_cache[msg->Data[0] - 1].Data, msg->Data, 64);
                    return 1; // 表示消息已修改
                }
            }

            if (memcmp(&can_msg_cache[i].Data, msg->Data, 64) == 0)
            {
                return 0; // 表示消息未修改
            }
            else
            {
                // 如果消息不同，则更新历史消息
                memcpy(&can_msg_cache[i].Data, msg->Data, 64);
                return 1; // 表示消息已修改
            }
        }
    }
    return 0; // 如果未找到该 CAN ID
}

void Drv_write_to_active_buffer(const CANFD_MESSAGE *msg, uint8_t channel)
{
    DoubleRingBuffer *drb = &canDoubleRingBuffer;

    if (((msg->ID == 0x1cb0e410) && (msg->Data[0] == 0xC9)) ||
        (msg->ID == 0x1cb010e4) || (msg->ID == 0x1823E410) || (msg->ID == 0))
    {
        return;
    }
    // printf("ID: %x\n", msg->ID);

    if (Drv_check_and_update_message(msg) == 0)
    {
        return; // 临时取消
    }

    pthread_mutex_lock(&drb->switchMutex);
    RingBuffer *activeBuffer = &drb->buffers[drb->activeBuffer];
    pthread_mutex_lock(&activeBuffer->mutex);

    CAN_LOG_MESSAGE *logMsg = &activeBuffer->buffer[activeBuffer->writeIndex];
    logMsg->relativeTimestamp = GetTimeDifference_ms(start_tick);
    memcpy(&logMsg->msg, msg, sizeof(CANFD_MESSAGE));
    logMsg->channel = channel;

    activeBuffer->writeIndex = (activeBuffer->writeIndex + 1) % BUFFER_SIZE;

    if (activeBuffer->count == BUFFER_SIZE)
    {
        activeBuffer->readIndex = (activeBuffer->readIndex + 1) % BUFFER_SIZE;
    }
    else
    {
        activeBuffer->count++;
    }

    pthread_mutex_unlock(&activeBuffer->mutex);
    pthread_mutex_unlock(&drb->switchMutex);
}

void Drv_write_canmsg_cache_to_file(FILE *file, uint32_t timestamp_ms)
{
    if (file == NULL)
    {
        LOG("Error: File pointer is NULL.\n");
        return;
    }

    unsigned short index = 0;
    for (int i = 0; i < CAN_ID_HISTORY_SIZE; i++)
    {
        CAN_MESSAGE *logMsg = &can_msg_cache[i];
        if (CAN_IDs[i] == 0x1A0110E4)
        {
            logMsg = &can_msg_1A0110E4_cache[index++];
            if (index < 8)
            {
                i--;
            }
            else
            {
                index = 0;
            }
        }
        else if (CAN_IDs[i] == 0x1B0110E4)
        {
            logMsg = &can_msg_1B0110E4_cache[index++];
            if (index < 2)
            {
                i--;
            }
            else
            {
                index = 0;
            }
        }
        else if (CAN_IDs[i] == 0x180410E4)
        {
            logMsg = &can_msg_180410E4_cache[index++];
            if (index < 1)
            {
                i--;
            }
            else
            {
                index = 0;
            }
        }
        // 构造带时间戳的字符串
        char timeStampedMessage[BUFFERED_WRITE_SIZE] = {0};
        unsigned char offset = 0;

        // 时间戳
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage),
                           "%d.%03d 1 ", timestamp_ms / 1000, timestamp_ms % 1000);
        // ID + 长度
        offset += snprintf(timeStampedMessage + offset, sizeof(timeStampedMessage),
                           "%03Xx Rx d %d ", logMsg->ID, logMsg->Length);
        // 数据
        for (int j = 0; j < logMsg->Length; ++j)
        {
            offset += snprintf(timeStampedMessage + offset, 4,
                               "%02X ", logMsg->Data[j]);
        }
        // 换行
        offset += snprintf(timeStampedMessage + offset, 4, "\r\n");
        // 写入文件//阻塞
        size_t err = fseek(file, 0, SEEK_END);
        if (err != 0)
        {
            perror("fseek");
            LOG("Failed to seek to end of file\n");
            return;
        }

        err = fwrite(timeStampedMessage, 1, offset, file);
        if (err != offset)
        {
            LOG("Failed to write to file\n");
            return;
        }
    }
    fflush(file);
}

// 将缓冲区数据写到sd卡
void Drv_write_buffer_to_file(DoubleRingBuffer *drb)
{
    static char filePath[512] = {0}; // 当前使用的文件路径

    int ret = 0;

    // 根据当前时间创建一个文件路径
    struct tm nowTimeInfo = {0};
    // 获取当前时间
    GetNowTime(&nowTimeInfo);

    // 交换当前使用的缓冲区
    pthread_mutex_lock(&drb->switchMutex);
    drb->activeBuffer = 1 - drb->activeBuffer;
    pthread_mutex_unlock(&drb->switchMutex);

    // 获取需要写入的缓冲区
    int inactiveBufferIndex = 1 - drb->activeBuffer;
    RingBuffer *inactiveBuffer = &drb->buffers[inactiveBufferIndex];

    // 获取文件互斥锁
    ret = pthread_mutex_lock(&inactiveBuffer->mutex);
    if (ret != 0)
    {
        LOG("write_buffer_to_file end return. \n");
        return;
    }

    // 先检查存储器状态 不存在 标记错误 直接退出
    if (CheckUsbStatus() != 0)
    {
        CP_set_emcu_fault(SD_FAULT, SET_ERROR);
        goto QUIT_FLAG;
    }
    //printf("5. USB status OK\n");
    // 判断是否需要重新创建一个文件开始写
    if (newFileNeeded)
    {
        // 将时间转换为文件路径
        CreateAscFilePathWithTime(nowTimeInfo, filePath);
        filePath[sizeof(filePath) - 1] = '\0';
        //printf("6. New file path created: %s\n", filePath);
    }
    //printf("7. Before OpenNowWriteAscFile\n");
    // 打开目标文件
    FILE *file = NULL;
    
    if (OpenNowWriteAscFile(filePath, &file) != 0  || file == NULL)
    {
        LOG("ERROR: OpenNowWriteAscFile failed for: %s\n", filePath);
        goto QUIT_FLAG; // 打开失败 直接返回
    }

    //printf("8. File opened successfully: %p\n", (void*)file);
    // 如果是新创建的
    // 如果是新创建的文件
    if (newFileNeeded)
    {
        LOG("9. Writing headers for new file\n");
        // 先写入当前文件头
        if (AscFileWriteTimeHeader(file, &nowTimeInfo) != 0) {
            LOG("ERROR: Failed to write time header\n");
        } else {
            //printf("9.1 Time header written\n");
        }
        // 缓冲区数据写入
        Drv_write_canmsg_cache_to_file(file, 0) ;
       
        // 标记不需要重新创建了
        newFileNeeded = false;
        //printf("9.3 New file setup completed\n");
    }

    // 如果不是新创建的文件 从文件的末尾追加写入
    fseek(file, 0, SEEK_END);
    while (inactiveBuffer->count > 0)
    {
        //printf("write_buffer_to_file: %d\n", inactiveBuffer->count);
        CAN_LOG_MESSAGE *logMsg = &inactiveBuffer->buffer[inactiveBuffer->readIndex];

        char dataStr[3 * 64 + 1] = {0};
        int bytes = logMsg->msg.Length;
        if (bytes > 64) bytes = 64; // 双保险
        #if 1
        for (int i = 0; i < bytes; ++i) {
            // 每次写 3 个字符："%02X "，最多写入 3*64=192 字符，留了 +1 结尾
            // 这里用 sizeof(dataStr) - i*3 做保护，避免意外越界
            snprintf(&dataStr[i * 3], (size_t)(sizeof(dataStr) - i * 3), "%02X ", logMsg->msg.Data[i]);
        }
        // 2) 方向标记
        const char *dir = (logMsg->channel == 0) ? "Rx" : "Tx";
        // 3) 直接一次性写入最终字符串（避免中间缓冲 + memmove）
        char line[BUFFERED_WRITE_SIZE]; // 请把 BUFFERED_WRITE_SIZE 设为 >= 512
        int lineLen = snprintf(
            line, sizeof(line),
            "%d.%03d 1 %08lX %s d %d %s\r\n",
            logMsg->relativeTimestamp / 1000,
            logMsg->relativeTimestamp % 1000,
            (unsigned long)logMsg->msg.ID,
            dir,
            logMsg->msg.Length,
            dataStr
        );
        if (lineLen < 0 || (size_t)lineLen >= sizeof(line)) 
        {
            // 被截断或出错：可以选择丢弃，或写一条告警，再继续下一条
            // fprintf(stderr, "line truncated or error, drop this frame\n");
            // 安全起见我们直接丢弃这一帧，避免潜在越界
            inactiveBuffer->readIndex = (inactiveBuffer->readIndex + 1) % BUFFER_SIZE;
            inactiveBuffer->count--;
            continue;
        }

        size_t written = fwrite(line, 1, (size_t)lineLen, file);
        (void)written; // 如需可检查 written == (size_t)lineLen

        inactiveBuffer->readIndex = (inactiveBuffer->readIndex + 1) % BUFFER_SIZE;
        inactiveBuffer->count--;
        #endif

#if 0

        for (int i = 0; i < logMsg->msg.Length && i < 64; ++i)
        {
            snprintf(&dataStr[i * 3], 4, "%02X ", logMsg->msg.Data[i]);
        }
        char modifiedMessage[BUFFERED_WRITE_SIZE];
        if (logMsg->channel == 0)
        {
            snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Rx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
        }
        else if (logMsg->channel == 1)
        {
            snprintf(modifiedMessage, sizeof(modifiedMessage), "%03lX Tx d %d %s\r\n", logMsg->msg.ID, logMsg->msg.Length, dataStr);
        }

        memmove(&modifiedMessage[9], &modifiedMessage[8], strlen(&modifiedMessage[8]) + 1);
        modifiedMessage[8] = 'x';

        char timeStampedMessage[BUFFERED_WRITE_SIZE];
        int dataLen = snprintf(timeStampedMessage, sizeof(timeStampedMessage), "%d.%03d 1 %s", logMsg->relativeTimestamp / 1000, logMsg->relativeTimestamp % 1000, modifiedMessage);

        size_t res = fwrite(timeStampedMessage, sizeof(char), dataLen, file);

        inactiveBuffer->readIndex = (inactiveBuffer->readIndex + 1) % BUFFER_SIZE;
        inactiveBuffer->count--;
#endif
    }
    fflush(file);

    // 写完之后 计算文件大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    // 创建新文件的两个条件
    // 1. 当前写的文件大小超过10M
    // 2. 系统中不存在当前日志命名的文件夹（日期变化了）
    if ((fileSize > (10*1024*1024) )|| (judgeTimetoUpdate())) // 大于10M或者年月日发生变化
    {
        LOG("fileSize = %ld\r\n",fileSize);

        LOG("judgeTimetoUpdate = %d\r\n",judgeTimetoUpdate());
        newFileNeeded = true; // 下一轮就要创建新文件
    }
    // 关闭文件
    fclose(file);

QUIT_FLAG:
    pthread_mutex_unlock(&inactiveBuffer->mutex);

    return;
}

int SD_Initialize(void)
{
    int res;

    const char *device = "/dev/sda1";

#if 0
    const char *mount_point = "/media/usb0";
    res = system("umount /media/usb0");
#else
    const char *mount_point = "/mnt/sda";
    res = system("umount /mnt/sda");
#endif
    if (res != 0)
    {
        LOG("umount failed (maybe not mounted):%d\n", res);
    }
    else
    {
        LOG("umount success\n");
    }

    char cmd[256];
    // snprintf(cmd, sizeof(cmd), "mkfs.vfat -F 32 %s", device);
    // snprintf(cmd, sizeof(cmd), "/sbin/mkdosfs -F 32 %s", device);
    snprintf(cmd, sizeof(cmd), "mkfs.ntfs -F %s", device);
    // snprintf(cmd, sizeof(cmd), "mkfs.ext4 -F %s", device);
    // snprintf(cmd, sizeof(cmd), "mkfs.ext4 -F -m 0 %s", device);
    res = system(cmd);
    if (res != 0)
    {
        LOG("Format failed: %d\n", res);
        return res;
    }
    else
    {
        LOG("Format (FAT32) success\n");
    }

    snprintf(cmd, sizeof(cmd), "mount %s %s", device, mount_point);
    res = system(cmd);
    if (res != 0)
    {
        LOG("Mount failed: %d\n", res);
        return res;
    }
    else
    {
        LOG("Mount success\n");
    }

    usleep(100 * 1000); // 替代 g_Delay_Ms(10)
    newFileNeeded = true;

    return 0;
}
int judgeTimetoUpdate(void)
{
    int ret = 0;
    static int last_year = 0;
    static int last_month = 0;
    static int last_day = 0;
    
    LOG("Current time: %d-%d-%d, Last time: %d-%d-%d\n", 
        BCU_TimeYear, BCU_TimeMonth, BCU_TimeDay,
        last_year, last_month, last_day);

    // 检查时间数据是否有效
    if (BCU_TimeYear == 0 || BCU_TimeMonth == 0 || BCU_TimeDay == 0) {
        LOG("Time invalid, skip check\n");
        return 0;
    }

    // 变化检查
    if ((BCU_TimeYear != last_year) || 
        (BCU_TimeMonth != last_month) || 
        (BCU_TimeDay != last_day)) 
    {
        
        LOG("TIME CHANGE DETECTED: %d-%d-%d -> %d-%d-%d\n", 
            last_year, last_month, last_day,
            BCU_TimeYear, BCU_TimeMonth, BCU_TimeDay);

        last_year = BCU_TimeYear;
        last_month = BCU_TimeMonth;
        last_day = BCU_TimeDay;
        ret = 1;
    }
    
    return ret;
}