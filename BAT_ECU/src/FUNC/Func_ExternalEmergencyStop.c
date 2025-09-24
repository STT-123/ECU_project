#include "Func_ExternalEmergencyStop.h"
#include "./DRV/Drv_ExternalEmergencyStop.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

void *GPIODetection(void* arg)
{

    while (1)
    {
        /* code */
        Drv_can0_rx_timeout_check();
        PHYlinktate();
        ECUfault_process();
        //printf("BCU_FaultInfoLv3H=%d \n",BCU_FaultInfoLv3H);
        CP_get_BCU_FaultInfoLv3H(BCU_FaultInfoLv3H);
        // Set_Electric_Meter_Data();
        usleep(20*1000);
    }

}