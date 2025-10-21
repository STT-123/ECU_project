#include "Net_Config_Task.h"
#include "./CP/Modbus/C_ModbusServer.h"
#include "log/log.h"
#include "./CP/Xmodem/C_OTAStateMonitor.h"

pthread_t NetConfig_TASKHandle;
pthread_t TcpServerExample_TASKHandle;

void NETConfigTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&NetConfig_TASKHandle, NULL, CP_ModbusTCPServer, NULL);
        if (ret != 0)
        {
            LOG("Failed to create NETConfigTask thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("NETConfigTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}

void TcpServerExampleTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&TcpServerExample_TASKHandle, NULL, TcpServerExample, NULL);
        if (ret != 0)
        {
            LOG("Failed to create TcpServerExampleTask thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("TcpServerExampleTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}