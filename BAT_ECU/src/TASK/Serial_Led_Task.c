#include "Serial_Led_Task.h"
#include "../GLB/G_GloabalVariable.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "../FUNC/Func_LEDShow.h"

pthread_t SerialLed_TASKHandle;



void SerialLedTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&SerialLed_TASKHandle, NULL, Func_SerialLed, NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create SerialLedTask thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"SerialLedTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}
