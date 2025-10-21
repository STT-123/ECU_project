#include "Func_CapacityChenk.h"
#include "./GLB/G_SystemConf.h"
#include "log/log.h"
// #define ROOT_PATH "./dev/test_sdcard"
// #define ROOT_PATH "/media/usb0"
#define ROOT_PATH "/mnt/sda"
#define CHECKSD_TRIGGERING_TIME 60000 * 1000

char *Drv_my_strdup(const char *str)
{
    if (!str)
        return NULL;
    char *dup = malloc(strlen(str) + 1);
    if (dup)
        strcpy(dup, str);
    return dup;
}

// 递归删除目录及内容
int Drv_remove_directory(const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    char subPath[512];

    if (!dir)
        return -1;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(subPath, sizeof(subPath), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(subPath, &statbuf) == 0)
        {
            if (S_ISDIR(statbuf.st_mode))
            {
                Drv_remove_directory(subPath); // 递归删除
            }
            else
            {
                unlink(subPath); // 删除文件
            }
        }
    }

    closedir(dir);
    return rmdir(path); // 删除目录
}

int CompareFolderNames(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

// 删除最旧的文件夹（假设文件夹名为日期字符串）
void Func_DeleteOldestFolder(void)
{
    DIR *dir = opendir(ROOT_PATH);
    struct dirent *entry;
    char *folders[100];
    int folderCount = 0;

    if (!dir)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0 &&
            strcmp(entry->d_name, "19700101") != 0)
        {

            // 用 stat 判断是不是目录
            char fullPath[512];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", ROOT_PATH, entry->d_name);

            struct stat st;
            if (stat(fullPath, &st) == 0 && S_ISDIR(st.st_mode))
            {
                folders[folderCount] = Drv_my_strdup(entry->d_name);
                if (!folders[folderCount])
                    break;
                folderCount++;
            }
        }
    }

    closedir(dir);

    if (folderCount > 0)
    {
        qsort(folders, folderCount, sizeof(char *), CompareFolderNames);

        char path[512];
        snprintf(path, sizeof(path), "%s/%s", ROOT_PATH, folders[0]);

        LOG("Deleting oldest folder: %s\n", path);
        Drv_remove_directory(path);

        for (int i = 0; i < folderCount; i++)
        {
            free(folders[i]);
        }
    }
}

// 检查SD卡容量并删除旧文件夹的线程任务
void *Func_CheckSDCardCapacityTask(void *arg)
{
    while (1)
    {
        struct statvfs stat;
        if (statvfs(ROOT_PATH, &stat) != 0)
        {
            perror("statvfs");
            LOG("Failed to get SD card capacity.\n");
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

        LOG("SD Card Usage:%.2f%%\n", usage_percent);

        if (usage_percent >= 90)
        {
            Func_DeleteOldestFolder();
        }

        G_set_system_time_from_bcu(); // 时间同步
        usleep(CHECKSD_TRIGGERING_TIME);
    }
    return NULL;
}

pthread_t SDCapacityChenk_TASKHandle;
void SDCapacityChenkTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&SDCapacityChenk_TASKHandle, NULL, Func_CheckSDCardCapacityTask, NULL);
        if (ret != 0)
        {
            LOG("Failed to create SDCapacityChenkTaskCreate thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("SDCapacityChenkTaskCreate thread created successfully.\r\n");
        }
    } while (ret != 0);
}