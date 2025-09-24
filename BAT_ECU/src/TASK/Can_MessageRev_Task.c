#include "Can_MessageRev_Task.h"
#include "./FUNC/Func_ECUAndBCUCommunication.h"
#include "./FUNC/Func_ECUAndBMUCommunication.h"
#include"Drv_ZLog.h"
pthread_t CAN2RecvDel_TASKHandle;
pthread_t CAN0RecDel_TASKHandle;
pthread_t CAN1RecvDel_TASKHandle;

// void CAN2RecvDelTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&CAN2RecvDel_TASKHandle, NULL, thread_can2_send, NULL);
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

void CAN0RecvDelTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&CAN0RecDel_TASKHandle, NULL, Func_thread_can0_dealwith, NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create Func_thread_can0_dealwith thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"Func_thread_can0_dealwith thread created successfully.\r\n");
        }
    } while (ret != 0);
}

void CAN1RecvDelTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&CAN1RecvDel_TASKHandle, NULL, Func_thread_can1_dealwith, NULL);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create Func_thread_can1_dealwith thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"Func_thread_can1_dealwith thread created successfully.\r\n");
        }
    } while (ret != 0);
}