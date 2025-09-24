#include "ExternalEmergencyStop_Task.h"
#include "./FUNC/Func_ExternalEmergencyStop.h"
#include "./DRV/LOG/Drv_ZLog.h"
pthread_t GPIODetectionTask_TASKHandle;
void  GPIODetectionTaskCreate(void)
{ 
    int ret;
    do {
    ret = pthread_create(&GPIODetectionTask_TASKHandle, NULL, GPIODetection, NULL);
    if (ret != 0) {
        zlog_info(debug_out,"Failed to create GPIODetectionTask thread : %s",strerror(ret));
        sleep(1); 
    }
    else
    {
        zlog_info(debug_out,"GPIODetectionTask thread created successfully.\r\n");
    }
    } while (ret != 0);
}