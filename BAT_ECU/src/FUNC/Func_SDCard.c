#include "Func_SDCard.h"
#include "./DRV/Drv_SDCard.h"
#include "./GLB/G_AddressDefinition.h"
#include "./GLB/G_GloabalVariable.h"
void *v_file_write_task(void *pvParameters) {
	unsigned short flag = 0;
    while (1) {
            usleep(3000*1000);
            //if(otactrl.OTAStart == 0)
            CP_get_modbus_reg_val(OTASTATUSREGADDR,&flag);
            if(flag == OTAIDLE)
            {
            	if(get_ftp_read_file_flag() == 0)
            	{
					swap_buffers(&canDoubleRingBuffer);  // 交换缓冲区，新日志存新缓存区，把旧缓冲区的写道文件里
					write_buffer_to_file(&canDoubleRingBuffer);  // 将缓冲区内容写入文件
            	}

            }
            else
            {
                printf("----------------OTAing---------%X-----\r\n",flag);
            }


    }
}
