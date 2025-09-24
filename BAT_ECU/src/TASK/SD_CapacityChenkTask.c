#include "SD_CapacityChenkTask.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./FUNC/Func_CapacityChenk.h"
pthread_t SDCapacityChenk_TASKHandle;

void SDCapacityChenkTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&SDCapacityChenk_TASKHandle, NULL,Func_CheckSDCardCapacityTask , NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create SDCapacityChenkTaskCreate thread : %s",strerror(ret));
            printf("Failed to create SDCapacityChenkTaskCreate thread : %s\r\n",ret);
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"SDCapacityChenkTaskCreate thread created successfully.\r\n");
            printf("success to create SDCapacityChenkTaskCreate thread : %s\r\n",ret);
        }
    } while (ret != 0);
}
