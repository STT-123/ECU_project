#include "Func_CapacityChenk.h"
#include "./GLB/G_SystemConf.h"
#include "./DRV/LOG/Drv_ZLog.h"
// #define ROOT_PATH "./dev/test_sdcard" 
// #define ROOT_PATH "/media/usb0" 
#define ROOT_PATH "/mnt/sda" 
#define CHECKSD_TRIGGERING_TIME 60000*1000
#define GETFREE_TRIGGERING_TIME 1000*1000

// 删除最旧的文件夹（假设文件夹名为日期字符串）

int CompareFolderNames(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
void Func_DeleteOldestFolder(void) {
    DIR *dir = opendir(ROOT_PATH);
    struct dirent *entry;
    char *folders[100];
    int folderCount = 0;

    if (!dir) {
        perror("opendir");
        return;
    }

while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 &&
        strcmp(entry->d_name, "..") != 0 &&
        strcmp(entry->d_name, "19700101") != 0) {
        
        // 用 stat 判断是不是目录
        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", ROOT_PATH, entry->d_name);

        struct stat st;
        if (stat(fullPath, &st) == 0 && S_ISDIR(st.st_mode)) {
            folders[folderCount] = Drv_my_strdup(entry->d_name);
            if (!folders[folderCount]) break;
            folderCount++;
        }
    }
}


    closedir(dir);

    if (folderCount > 0) {
        qsort(folders, folderCount, sizeof(char *), CompareFolderNames);

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", ROOT_PATH, folders[0]);
        printf("Deleting oldest folder: %s\n", path);
        zlog_info(debug_out,"Deleting oldest folder: %s\n", path);
        Drv_remove_directory(path);

        for (int i = 0; i < folderCount; i++) {
            free(folders[i]);
        }
    }
}

// 检查SD卡容量并删除旧文件夹的线程任务
void *Func_CheckSDCardCapacityTask(void *arg) {
    while (1) {


        struct statvfs stat;
        if (statvfs(ROOT_PATH, &stat) != 0) {
            perror("statvfs");
            printf("Failed to get SD card capacity.\n");
            zlog_info(debug_out,"Failed to get SD card capacity.\n");
            usleep(CHECKSD_TRIGGERING_TIME);
            continue;
        }

        // unsigned long total = stat.f_blocks * stat.f_frsize;
        // unsigned long free_space = stat.f_bfree * stat.f_frsize;
        // float usage_percent = ((float)(total - free_space) / total) * 100;
        uint64_t total = (uint64_t)stat.f_blocks * (uint64_t)stat.f_frsize;
        uint64_t free_space = (uint64_t)stat.f_bfree * (uint64_t)stat.f_frsize;
        uint64_t used = total - free_space;

        float usage_percent = ((float)used / (float)total) * 100.0f;

        
        // printf("SD Card Usage: %.2f%%\n", usage_percent);
        zlog_info(debug_out,"SD Card Usage:%.2f%%\n",usage_percent);

        if (usage_percent >= 90) {
            Func_DeleteOldestFolder();
        }

        G_set_system_time_from_bcu();//时间同步
        usleep(CHECKSD_TRIGGERING_TIME);

    }
    return NULL;
}


