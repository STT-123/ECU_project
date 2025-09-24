#define _GNU_SOURCE
#include "Func_SDCard.h"
#include "./DRV/Drv_SDCard.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./GLB/G_AddressDefinition.h"
#include "./GLB/G_GloabalVariable.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include    "main.h"
unsigned short flag = 0;
// 检查挂载点是否存在
int ensure_mount_point(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0777) == -1) {
            perror("创建挂载目录失败");
            printf("请检查挂载点路径是否正确\n");
            return -1;
        }
        else
        {
            printf("创建挂载目录成功\n");
        }
    }
    else{
        printf("挂载点已存在\n");
    }
    return 0;
}

void *Func_file_write_task(void *arg) {
    // const char *usb_device = "/dev/sda1";
    // const char *mount_point = "/media/usb0"; // 使用自动挂载的路径
    const char *mount_point = "/mnt/sda"; // 使用自动挂载的路径
    unsigned short SD_INIT_flag = 0;
    // 1. 检查挂载点
    if (ensure_mount_point(mount_point) != 0) {
        // printf("请检查挂载点路径是否正确\r\n");
        zlog_info(debug_out,"请检查挂载点路径是否正确.\r\n");
        return NULL;
    }
    Drv_RTCGetTime(&initialTime);  // 获取系统启动的时间//1205
    clock_gettime(CLOCK_MONOTONIC, &start_tick);
    printf("start_tick : %ld\n",start_tick);
    while (1) {
            usleep(3000*1000);
            //if(otactrl.OTAStart == 0)
            CP_get_modbus_reg_val(OTASTATUSREGADDR,&flag);
            CP_get_modbus_reg_val(0x6721,&SD_INIT_flag);
            if(SD_INIT_flag == 1)
            {
            	int  result = SD_Initialize();
            	if (result == 0) {
            		CP_set_modbus_reg_val(0x6721,2);//成功
            		// printf("SD_Initialize succeeded.\n");
                    zlog_info(debug_out,"SD_Initialize succeeded.\n");
				} else {
					// printf("SD_Initialize error code: %d\n", result);
                    zlog_info(debug_out,"SD_Initialize error code: %d\n", result);
					CP_set_modbus_reg_val(0x6721,3);//失败
				}
            }
            if((flag == OTAIDLE  || flag == OTAFAILED ) && SD_INIT_flag != 1)
            {
                // printf("OTAIDLE\n");
            	if(CP_get_ftp_read_file_flag() == 0)
            	{
                    // printf("CP_get_ftp_read_file_flag() == 0\n");
					Drv_swap_buffers(&canDoubleRingBuffer);  // 交换缓冲区，新日志存新缓存区，把旧缓冲区的写道文件里
					Drv_write_buffer_to_file(&canDoubleRingBuffer);  // 将缓冲区内容写入文件
                    // printf("OVER\r\n");
            	}

            }
            else
            {
                printf("----------------OTAing---------%X-----\r\n",flag);
            }


    }
}
