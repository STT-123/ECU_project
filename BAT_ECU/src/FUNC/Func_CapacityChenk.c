#include "Func_CapacityChenk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <unistd.h>


#define ROOT_PATH "./test_sdcard" 
// 删除最旧的文件夹（假设文件夹名为日期字符串）

int CompareFolderNames(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
void DeleteOldestFolder(void) {
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
            folders[folderCount] = my_strdup(entry->d_name);
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
        remove_directory(path);

        for (int i = 0; i < folderCount; i++) {
            free(folders[i]);
        }
    }
}
