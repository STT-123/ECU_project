#define _GNU_SOURCE
#include "Func_ECUAndBMUCommunication.h"
#include "../DRV/Drv_ECUAndBMUCommunication.h"
#include "../DRV/LOG/Drv_ZLog.h"
#include "Func_SDCard.h"
#include "main.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

static int CAN1_FD;      

// sem_t send2_sem; //信号量
static pthread_mutex_t Mutex_Can1Send;
void Func_print_can1fd_frame(const struct canfd_frame *frame)
{
    printf("CAN FD Frame:\n");
    printf("  CAN ID   : 0x%08X\n", frame->can_id & CAN_EFF_MASK);
    printf("  DLC      : %d\n", frame->len);
    printf("  Data     : ");
    for (int i = 0; i < frame->len; i++) {
        printf("%02X ", frame->data[i]);
    }
    printf("\n");
}
/********************************************************************************
 * 函数名称： Func_thread_can1_dealwith
 * 功能描述：can1 的消息处理
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
#include "./FUNC/Func_SDCard.h"
void *Func_thread_can1_dealwith(void *arg)
{
    // struct can_frame canrev_frame;
    CAN_MESSAGE canrev_frame;
	zlog_info(debug_out,"can1 deal thread is running\r\n");
    printf("can1 deal thread is running\r\n");
    int err = 0;
    while(1)
    {
         if((flag == OTAIDLE  || flag == OTAFAILED || otactrl.deviceType == AC))
        {

                        //等待信号，有信号则有消息来，处理以后加进消息接收中
            if(queue_pend(&Queue_Can1RevData, (unsigned char *)&canrev_frame, &err) == 0)
            {
                // Func_print_can1fd_frame(&canrev_frame);
                // printf("queue_post can1 data success\r\n");
                // canrev_frame.can_id &= CAN_EFF_MASK;
                // printf("queue_post can1 data success\r\n");
                if((flag == OTAIDLE  || flag == OTAFAILED ))
                {
                memcpy(&CANMsg,&canrev_frame,sizeof(CAN_MESSAGE));
                // Convert_can_frame_to_CAN_MESSAGE(&canrev_frame,&bms_B.CAN_Daq_o2);
                // Convert_canfd_frame_to_CAN_MESSAGE(&canrev_frame,&bms_B.CAN_Daq_o2);
                Drv_BMS_Analysis();//BMS数据解析 临时取消
                memset(&canrev_frame, 0, sizeof(canrev_frame));
                }


            }

        }
    
        // printf("queue_pend return err = %d\r\n", err);
        usleep(10*1000);
    }
}




/********************************************************************************
 * 函数名称： Func_thread_can1_send
 * 功能描述：can1 的消息发送处理
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
/*void *Func_thread_can1_send(void *arg)
{
	int err = 0;
	unsigned int i = 0;

	int sendErrCounter = 0;
	struct canfd_frame send_msg;
    sem_init(&send2_sem, 0, 0); //初始化信号量

	//LOGE("thread bms send is running\r\n");
	while(1)
	{
        sem_wait(&send2_sem);
		if(queue_pend(&Queue_Can1SendData, (unsigned char *)&send_msg, &err) == 0)
		{
			pthread_mutex_lock(&Mutex_Can1Send);
            if(HAL_can_write(CAN1_FD, &send_msg) == RESULT_OK)//CAN0_PowerModule_Fd  CAN1_BMS_Fd
            {
        //    	LOGE("can1 send ok\r\n");
                //return 1;
            }
            else
            {
				sendErrCounter++;
				if(sendErrCounter >= 60)
				{
					if(Drv_reset_can1_device(PORT_CAN1_DEVICE_NAME))
                    {
                        sendErrCounter = 0;
                    }
                    else
                    {
                        sendErrCounter = 60;
                    }
				}
			}
			pthread_mutex_unlock(&Mutex_Can1Send);
        }
		usleep(20000);//0000
	}

}
*/