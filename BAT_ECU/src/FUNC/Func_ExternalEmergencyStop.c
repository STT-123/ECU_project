#include "Func_ExternalEmergencyStop.h"
#include "./DRV/Drv_ExternalEmergencyStop.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./CP/BMS/bms/CANRcvFcn.h"
#include <pthread.h>
#include "log/log.h"

void *GPIODetection(void *arg)
{
    while (1)
    {
        /* code */
        Drv_can0_rx_timeout_check();
        PHYlinktate();
        ECUfault_process();
        CP_get_BCU_FaultInfoLv3H(BCU_FaultInfoLv3H);
        // Set_Electric_Meter_Data();
        usleep(20 * 1000);
    }
}

pthread_t GPIODetectionTask_TASKHandle;
void GPIODetectionTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&GPIODetectionTask_TASKHandle, NULL, GPIODetection, NULL);
        if (ret != 0)
        {
            LOG("Failed to create GPIODetectionTask thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("GPIODetectionTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}