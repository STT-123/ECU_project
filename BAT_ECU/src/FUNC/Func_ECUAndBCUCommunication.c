#define _GNU_SOURCE

#include "Func_ECUAndBCUCommunication.h"
#include "../DRV/Drv_ECUAndBCUCommunication.h"
#include "./DRV/Drv_ExternalCANCommunication.h"
#include "../DRV/LOG/Drv_ZLog.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./DRV/Drv_SDCard.h"
#include "Func_SDCard.h"
#include "main.h"
#include "./CP/BMS/bms/CANRcvFcn.h"
static int CAN0_FD;      


static pthread_mutex_t Mutex_Can0Send;
void Func_print_canfd_frame(const struct canfd_frame *frame)
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
 * ZHX !!!
 ********************************************************************************/
void *Func_thread_can0_dealwith(void *arg)
{
    struct canfd_frame canrev_frame;
    CANFD_MESSAGE can_msg_buf;
	zlog_info(debug_out,"can1 deal thread is running\r\n");
    printf("can1 deal thread is running\r\n");
    int err = 0;

    int bms_analysis_done = 0;
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);  // 记录线程开始时间
    while(1)
    {
        if((flag == OTAIDLE  || flag == OTAFAILED || otactrl.deviceType == AC ))
        {
            if(queue_pend(&Queue_Can0RevData_FD, (unsigned char *)&canrev_frame, &err) == 0)
            {
                // printf("canrev_frame->data[0] :%02X \r\n", canrev_frame.data[0]);
                // printf("canrev_frame->data[1] :%02X\r\n ", canrev_frame.data[1]);
                // printf("canrev_frame.data[2] :%02X\r\n ", canrev_frame.data[2]);
        
                if ((canrev_frame.len > 8))
                {
                    // Func_print_canfd_frame(&canrev_frame);
                    // printf("queue_post can1 data success\r\n");
                    canrev_frame.can_id &= CAN_EFF_MASK;
                    // printf("queue_post can1 data success\r\n");
                    ///////////////////////////////////////////////////////////////////////////////////////////////   
                    // Drv_BMS_Forward_CAN2(&canrev_frame);//转发给Can0//临时取消测试。
                    ///////////////////////////////////////////////////////////////////////////////////
                    // memcpy(&bms_B.CAN_BCU_o2,&canrev_frame,sizeof(struct canfd_frame));//转发给BMS
                    ConvertCANFDToBus(&canrev_frame,& CANFDRcvMsg); 
                    Drv_BMS_Analysis();//BMS数据解析 
                    ConvertCANFDToBus(&canrev_frame,&can_msg_buf);
                    Drv_write_to_active_buffer(&can_msg_buf,1);
                    // printf("Drv_BMS_Analysis camsg recv ok\r\n");
                }
    
                memset(&canrev_frame, 0, sizeof(canrev_frame));
            }
            else if(err != 0)
            {
                printf("queue_pend return err = %d\r\n", err);
            }
            else
            {
                // 仅在初始化后10秒执行一次
                if (!bms_analysis_done)
                {
                    struct timespec now;
                    clock_gettime(CLOCK_MONOTONIC, &now);
                    long elapsed_ms = (now.tv_sec - start_time.tv_sec) * 1000 +
                                    (now.tv_nsec - start_time.tv_nsec) / 1000000;

                    if (elapsed_ms >= 10000)  // 10秒后执行
                    {
                        Drv_BMS_Analysis();
                       
                        bms_analysis_done = 1;
                        zlog_info(debug_out, "Drv_BMS_Analysis executed after 10s delay\r\n");
                    }
                }
            }
        }
        // printf("queue_pend return err = %d\r\n", err);
        usleep(2*1000);//临时添加测试
    }
}




/********************************************************************************
 * 函数名称： Func_thread_can1_send
 * 功能描述：can1 的消息发送处理
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * ZHX !!!
 ********************************************************************************/
/*void *Func_thread_can1_send(void *arg)
{
	int err = 0;
	unsigned int i = 0;

	int sendErrCounter = 0;
	struct canfd_frame send_msg;



	//LOGE("thread bms send is running\r\n");
	while(1)
	{
        sem_wait(&send_sem);
        // printf("Func_thread_can1_send is running\r\n");
		if(queue_pend(&Queue_Can0SendData, (unsigned char *)&send_msg, &err) == 0)
		{
            // printf("queue_pend can1 send success\r\n");
			pthread_mutex_lock(&Mutex_Can0Send);
            if(HAL_can_write(CAN0_FD, &send_msg) == RESULT_OK)//CAN0_PowerModule_Fd  CAN0_BMS_Fd
            {
                printf("send_msg.can_id  : %08lX\r\n", send_msg.can_id );
                printf("send_msg.len  : %d\r\n", send_msg.len );
                // printf("send_msg.data  : %02X %02X %02X %02X %02X %02X %02X %02X\r\n", send_msg.data[0], send_msg.data[1], send_msg.data[2], send_msg.data[3], send_msg.data[4], send_msg.data[5], send_msg.data[6], send_msg.data[7] );
                char data_str[128]; 
                int offset = 0;
                for (int i = 0; i < send_msg.len; i++) {
                    offset += snprintf(data_str + offset, sizeof(data_str) - offset, "%02X ", send_msg.data[i]);
                }
                printf("send_msg.data  : %s\r\n", data_str);
           	    printf("can1 send ok\r\n");
                //return 1;
            }
            else
            {
				sendErrCounter++;
				if(sendErrCounter >= 60)
				{
					if(Drv_reset_can1_device(PORT_CAN0_DEVICE_NAME))
                    {
                        sendErrCounter = 0;
                    }
                    else
                    {
                        sendErrCounter = 60;
                    }
				}
			}
			pthread_mutex_unlock(&Mutex_Can0Send);
        }
		usleep(20000);//0000
	}

}
*/