#include "OCPP_Communication_Task.h"
#include "./CP/OCPP/ocpp/ws_client.h"
#include "./DRV/LOG/Drv_ZLog.h"

pthread_t ws_thread;

void OCPPCommunicationTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&ws_thread, NULL, websocket_client_thread, NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create websocket_client_thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"websocket_client_thread created successfully.\r\n");
        }
    } while (ret != 0);
}