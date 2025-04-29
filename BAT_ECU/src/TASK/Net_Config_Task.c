#include "Net_Config_Task.h"
#include "./CP/Modbus/C_ModbusServer.h"
#include"Drv_ZLog.h"
#include "./CP/Xmodem/C_OTAStateMonitor.h"

pthread_t NetConfig_TASKHandle;
pthread_t TcpServerExample_TASKHandle;

void NETConfigTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&NetConfig_TASKHandle, NULL,CP_ModbusTCPServer , NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create NETConfigTask thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"NETConfigTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}



void TcpServerExampleTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&TcpServerExample_TASKHandle, NULL,TcpServerExample , NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create TcpServerExampleTask thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"TcpServerExampleTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}