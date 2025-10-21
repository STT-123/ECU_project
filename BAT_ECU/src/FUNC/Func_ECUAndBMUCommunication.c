#define _GNU_SOURCE
#include "Func_ECUAndBMUCommunication.h"
#include "../DRV/Drv_ECUAndBMUCommunication.h"
#include "log/log.h"
#include "Func_SDCard.h"
#include "main.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

void Func_print_can1fd_frame(const struct canfd_frame *frame)
{
    printf("CAN FD Frame:\n");
    printf("  CAN ID   : 0x%08X\n", frame->can_id & CAN_EFF_MASK);
    printf("  DLC      : %d\n", frame->len);
    printf("  Data     : ");
    for (int i = 0; i < frame->len; i++)
    {
        printf("%02X ", frame->data[i]);
    }
    printf("\n");
}

#include "./FUNC/Func_SDCard.h"
void *Func_thread_can1_dealwith(void *arg)
{
    // struct can_frame canrev_frame;
    CAN_MESSAGE canrev_frame;
    LOG("Func_thread_can1_dealwith is running\n");
    int err = 0;
    while (1)
    {
        if ((ota_flag == OTAIDLE || ota_flag == OTAFAILED || otactrl.deviceType == AC))
        {

            // 等待信号，有信号则有消息来，处理以后加进消息接收中
            if (queue_pend(&Queue_Can1RevData, (unsigned char *)&canrev_frame, &err) == 0)
            {
                // Func_print_can1fd_frame(&canrev_frame);
                // printf("queue_post can1 data success\r\n");
                // canrev_frame.can_id &= CAN_EFF_MASK;
                // printf("queue_post can1 data success\r\n");
                if ((ota_flag == OTAIDLE || ota_flag == OTAFAILED))
                {
                    memcpy(&CANRcvMsg, &canrev_frame, sizeof(CAN_MESSAGE));
                    // Convert_can_frame_to_CAN_MESSAGE(&canrev_frame,&bms_B.CAN_Daq_o2);
                    // Convert_canfd_frame_to_CAN_MESSAGE(&canrev_frame,&bms_B.CAN_Daq_o2);
                    Drv_BMS_Analysis(); // BMS数据解析 临时取消
                    memset(&canrev_frame, 0, sizeof(canrev_frame));
                }
            }
        }

        // printf("queue_pend return err = %d\r\n", err);
        usleep(10 * 1000);
    }
}


pthread_t CAN1RecvDel_TASKHandle;
void CAN1RecvDelTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&CAN1RecvDel_TASKHandle, NULL, Func_thread_can1_dealwith, NULL);
        if (ret != 0)
        {
            LOG("Failed to create Func_thread_can1_dealwith thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("Func_thread_can1_dealwith thread created successfully.\r\n");
        }
    } while (ret != 0);
}