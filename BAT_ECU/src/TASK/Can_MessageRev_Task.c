#include "Can_MessageRev_Task.h"
#include "./FUNC/Func_ECUAndBCUCommunication.h"
#include"Drv_ZLog.h"
pthread_t CAN0RecvDel_TASKHandle;
pthread_t CAN1RecDel_TASKHandle;
pthread_t CAN2RecvDel_TASKHandle;

// void CAN0RecvDelTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&CAN0RecvDel_TASKHandle, NULL, thread_can0_send, NULL);
//         if (ret != 0) {
//             zlog_info(debug_out,"Failed to create SerialLedTask thread : %s",strerror(ret));
//             sleep(1); 
//         }
//         else
//         {
//             zlog_info(debug_out,"SerialLedTask thread created successfully.\r\n");
//         }
//     } while (ret != 0);
// }

void CAN1RecvDelTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&CAN1RecDel_TASKHandle, NULL, thread_can1_dealwith, NULL);
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

// void CAN2RecvDelTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&CAN2RecvDel_TASKHandle, NULL, , NULL);
//         if (ret != 0) {
//             zlog_info(debug_out,"Failed to create SerialLedTask thread : %s",strerror(ret));
//             sleep(1); 
//         }
//         else
//         {
//             zlog_info(debug_out,"SerialLedTask thread created successfully.\r\n");
//         }
//     } while (ret != 0);
// }