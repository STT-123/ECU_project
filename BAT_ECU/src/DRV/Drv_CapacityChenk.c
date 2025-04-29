#include "Drv_CapacityChenk.h"

char *my_strdup(const char *str) {
    if (!str) return NULL;
    char *dup = malloc(strlen(str) + 1);
    if (dup) strcpy(dup, str);
    return dup;
}

// int CompareFolderNames(const void *a, const void *b) {
//     return strcmp(*(const char **)a, *(const char **)b);
// }

// 递归删除目录及内容
int remove_directory(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char subPath[512];

    if (!dir) return -1;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(subPath, sizeof(subPath), "%s/%s", path, entry->d_name);

        struct stat statbuf;
        if (stat(subPath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                remove_directory(subPath);  // 递归删除
            } else {
                unlink(subPath);            // 删除文件
            }
        }
    }

    closedir(dir);
    return rmdir(path);  // 删除目录
}