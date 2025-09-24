#include "FTP_Server_Task.h"
#include "C_FTPserver_Handle.h"
#include "./CP/FTP/C_FTPserver.h"
#include"Drv_ZLog.h"
int ftp_port = 21;

pthread_t FTPServer_TASKHandle;


void FTPServerTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&FTPServer_TASKHandle, NULL,ftp_service , &ftp_port);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create FTPServerTaskCreate thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"FTPServerTaskCreate thread created successfully.\r\n");
        }
    } while (ret != 0);
}