#include "Log_Save_Task.h"
#include"Drv_ZLog.h"
#include "./FUNC/Func_SDCard.h"


pthread_t SDCardDataSave_TASKHandle;

void SDCardDataSaveTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&SDCardDataSave_TASKHandle, NULL,Func_file_write_task , NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create SDCardDataSaveTaskCreate thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"SDCardDataSaveTaskCreate thread created successfully.\r\n");
        }
    } while (ret != 0);
}
