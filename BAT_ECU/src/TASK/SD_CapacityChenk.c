#include "SD_CapacityChenk.h"
#define ROOT_PATH "./dev/test_sdcard"  
#define CHECKSD_TRIGGERING_TIME 60000
#define GETFREE_TRIGGERING_TIME 1000
// 检查SD卡容量并删除旧文件夹的线程任务
void *CheckSDCardCapacityTask(void *arg) {
    while (1) {
        struct statvfs stat;
        if (statvfs(ROOT_PATH, &stat) != 0) {
            perror("statvfs");
            sleep(CHECKSD_TRIGGERING_TIME);
            continue;
        }

        unsigned long total = stat.f_blocks * stat.f_frsize;
        unsigned long free_space = stat.f_bfree * stat.f_frsize;
        float usage_percent = ((float)(total - free_space) / total) * 100;

        printf("SD Card Usage: %.2f%%\n", usage_percent);

        if (usage_percent >= 90) {
            DeleteOldestFolder();
        }

        sleep(CHECKSD_TRIGGERING_TIME);
    }
    return NULL;
}