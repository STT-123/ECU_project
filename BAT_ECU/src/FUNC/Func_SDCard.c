#define _GNU_SOURCE
#include "Func_SDCard.h"
#include "./DRV/Drv_SDCard.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./GLB/G_AddressDefinition.h"
#include "./GLB/G_GloabalVariable.h"
#include "log/log.h"
#include "main.h"

unsigned short ota_flag = 0;
// 检查挂载点是否存在
static int ensure_mount_point(const char *path)
{
    struct stat st;
    if (stat(path, &st) == -1)
    {
        if (mkdir(path, 0777) == -1)
        {
            perror("创建挂载目录失败");
            LOG("请检查挂载点路径是否正确\n");
            return -1;
        }
        else
        {
            LOG("创建挂载目录成功\n");
        }
    }
    else
    {
        LOG("挂载点已存在\n");
    }
    return 0;
}

void *Func_file_write_task(void *arg)
{
    // const char *usb_device = "/dev/sda1";
    // const char *mount_point = "/media/usb0"; // 使用自动挂载的路径
    const char *mount_point = "/mnt/sda"; // 使用自动挂载的路径

    uint16_t SD_INIT_flag = 0;

    // 1. 检查挂载点
    if (ensure_mount_point(mount_point) != 0)
    {
        LOG("[SD Card] 请检查挂载点路径是否正确.\n");
        return NULL;
    }
    LOG("[SD Card] SD卡挂载 %s 成功. \n", mount_point);

    while (1)
    {
        usleep(3000 * 1000);

        // 获取 ota标识 和 sd卡初始化标识
        CP_get_modbus_reg_val(OTASTATUSREGADDR, &ota_flag);
        CP_get_modbus_reg_val(0x6721, &SD_INIT_flag);

        // 如果sd卡未初始化 则初始化sd卡
        if (SD_INIT_flag == 1)
        {
            int result = SD_Initialize();
            if (result == 0)
            {
                CP_set_modbus_reg_val(0x6721, 2); // 成功
                LOG("[SD Card] SD_Initialize succeeded.\n");
            }
            else
            {
                CP_set_modbus_reg_val(0x6721, 3); // 失败
                LOG("[SD Card] SD_Initialize error code: %d \n", result);
            }
        }

        // 没有ota中 并且 sd卡初始化过
        if ((ota_flag == OTAIDLE || ota_flag == OTAFAILED) && SD_INIT_flag != 1)
        {
            if (CP_get_ftp_read_file_flag() == 0)
            {
                Drv_write_buffer_to_file(&canDoubleRingBuffer); // 将缓冲区内容写入文件
            }
        }
        else
        {
            LOG("[SD Card] ----------------OTAing---------flag = 0x%X-----\r\n", ota_flag);
        }
    }
}

pthread_t SDCardDataSave_TASKHandle;
void SDCardDataSaveTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&SDCardDataSave_TASKHandle, NULL, Func_file_write_task, NULL);
        if (ret != 0)
        {
            LOG("[SD Card] Failed to create SDCardDataSaveTaskCreate thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("[SD Card] SDCardDataSaveTaskCreate thread created successfully.\r\n");
        }
    } while (ret != 0);
}