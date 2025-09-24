#include "Can_MessageSend_Task.h"
#include "./FUNC/Func_ECUAndBCUCommunication.h"
#include "./FUNC/Func_ECUAndBMUCommunication.h"
#include "zlog.h"
#include"Drv_ZLog.h"
// pthread_t CAN0Send_TASKHandle;
// pthread_t CAN1Send_TASKHandle;
// pthread_t CAN2Send_TASKHandle;

// void CAN0SendTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&CAN0Send_TASKHandle, NULL,thread_can0_send , NULL);
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

/*void CAN1SendTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&CAN0Send_TASKHandle, NULL,Func_thread_can1_send , NULL);
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
*/
// void CAN2SendTaskCreate(void)
// {
//     int ret;
//     do {
//         ret = pthread_create(&CAN2Send_TASKHandle, NULL,Func_thread_can2_send , NULL);
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