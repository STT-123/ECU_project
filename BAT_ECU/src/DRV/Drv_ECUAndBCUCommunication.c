#include "Drv_ECUAndBCUCommunication.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./DRV/LOG/zlog.h"
#include "./DRV/Drv_ExternalEmergencyStop.h"

struct Myeventdata can0evendata;        //分机can epoll 事件
static pthread_mutex_t Mutex_Can0Send;

static int CAN0_FD;  

queue_st	Queue_Can0RevData;          
queue_st	Queue_Can0RevData_FD;                             
static void Drv_can0_epoll_msg_transmit (void * arg);
bool Drv_can0_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can0Send, NULL);
    queue_init(&Queue_Can0RevData);         //用于接收消息后存入
    queue_init(&Queue_Can0RevData_FD);         //用于接收消息后存入
    // queue_init(&Queue_Can0SendData);         //用于发送消息存入
     printf("[Drv_can0_init] 开始初始化 CAN0_FD...\n");
    zlog_info(debug_out, "开始初始化 CAN0_FD...\n");
    if (HAL_can_ifconfig_init(PORT_CAN0_DEVICE_NAME,PORT_CAN0_CAN_BITRATE) == false)
    {
        printf("[Drv_can0_init] HAL_can_ifconfig_init 失败\n");
        zlog_error(debug_out, "HAL_can_ifconfig_init 失败\n");
        return false;
    }
    printf("[Drv_can0_init] CAN0_FD 网络配置成功\n");
    zlog_info(debug_out, "CAN0_FD 网络配置成功\n");

    while (HAL_can_band_init(PORT_CAN0_DEVICE_NAME,&CAN0_FD) == false)
    {
        printf("[Drv_can0_init] HAL_can_band_init 失败，重试中...\n");
        zlog_error(debug_out, "HAL_can_band_init 失败\n");
        sleep(1);
    }
    printf("[Drv_can0_init] CAN0_FD 绑定成功,fd = %d\n", CAN0_FD);
    zlog_info(debug_out, "CAN0_FD 绑定成功,fd = %d\n", CAN0_FD);

    can0evendata.fd = CAN0_FD;
    can0evendata.fun_handle =(void*) Drv_can0_epoll_msg_transmit;   //回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *) &can0evendata;
     printf("[Drv_can0_init] 添加到 epoll...\n");
    if(-1 == my_epoll_addtast(can0evendata.fd, &ev))
    {
         printf("[Drv_can0_init] my_epoll_addtast 失败\n");
        zlog_info(debug_out,"can0add epoll  fail\r\n");
        return false;
    }
    printf("[Drv_can0_init] 初始化完成\n");
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define CAN_ID_STD_61B      0x61B
#define CAN_ID_EXT_1CB010E4 0x1CB010E4
#define CAN_ID_EXT_030C1600 0x030C1600



static void Drv_can0_epoll_msg_transmit (void * arg)
{
    struct canfd_frame can_rev;
    CAN_MESSAGE  can_send;
	struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	// printf("[Drv_can0_epoll_msg_transmit] epoll_wait\n");
    memset(&can_rev, 0, sizeof(struct canfd_frame));
    memset(&can_send, 0, sizeof(CAN_MESSAGE));
    int frame_type = HAL_can_read(CAN0_FD, &can_rev, 1);
    // printf("frame_type = %d\n",frame_type);
    time(&last_can0_rx_time); 
    if(frame_type == 1) 
    {
        Convert_canfd_frame_to_CAN_MESSAGE(&can_rev, &can_send);
        // if(can_send.ID == 0x30C1600)
        // {
            // printf("can_send->data[0] :%02X \r\n", can_send.Data[0]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[1]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[2]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[3]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[4]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[5]);
        // }
        // if(can_send.ID == 0x61B)
        // {
            // printf("can_send->data[0] :%02X \r\n", can_send.Data[0]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[1]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[2]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[3]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[4]);
            // printf("can_send->data[1] :%02X\r\n ", can_send.Data[5]);
        // }

        if( ((CP_get_TCU_PowerUpCmd()) == 5)&& (can_send.ID == 0x30C1600 || can_send.ID == 0x61B || can_send.ID ==0x1CB010E4))
        {
            if(queue_post(&Queue_Can0RevData, &can_send, sizeof(CAN_MESSAGE)) != 0)
            {
                printf("Queue_Can0RevData send err\r\n");
                queue_destroy(&Queue_Can0RevData);
                queue_init(&Queue_Can0RevData);
            }
            else
            {

                // printf("Queue_Can0RevData send\r\n");
                // printtf("can_send->ID :%08X \r\n",can_send.ID);
                // printf("can_send->data[0] :%02X \r\n", can_send.Data[0]);
                // printf("can_send->data[1] :%02X\r\n ", can_send.Data[1]);
                // printf("can_send.data[2] :%02X\r\n ", can_send.Data[2]);
                // printf("can_send.data[2] :%02X\r\n ", can_send.Data[2]);
            }
        }
        else if( (CP_get_TCU_PowerUpCmd()) != 5 && can_send.ID != 0x18FFC13A && can_send.ID != 0x18FFC13B && can_send.ID != 0x18FFC13C && can_send.ID != 0x18FAE6E1 && can_send.ID != 0x18FD7BE1 && can_send.ID != 0X18FA78F1 && can_send.ID !=0x18FFC13D && can_send.ID !=0x18FA78F5 && can_send.ID !=0x18FAE6E2)
        {
            if(queue_post(&Queue_Can0RevData, &can_send, sizeof(CAN_MESSAGE)) != 0)
            {
                printf("Queue_Can0RevData send err\r\n");
                queue_destroy(&Queue_Can0RevData);
                queue_init(&Queue_Can0RevData);
            }
            else
            {

                // printf("Queue_Can0RevData send\r\n");
                // printtf("can_send->ID :%08X \r\n",can_send.ID);
                // printf("can_send->data[0] :%02X \r\n", can_send.Data[0]);
                // printf("can_send->data[1] :%02X\r\n ", can_send.Data[1]);
                // printf("can_send.data[2] :%02X\r\n ", can_send.Data[2]);
                // printf("can_send.data[2] :%02X\r\n ", can_send.Data[2]);
            }

        }
        
    }
    else if(frame_type == 2)
    {

            if(queue_post(&Queue_Can0RevData_FD, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
            {
                // printf("Queue_Can0RevData_FD send err\r\n");
                queue_destroy(&Queue_Can0RevData_FD);
                queue_init(&Queue_Can0RevData_FD);
            }
            else
            {
                // printf("Queue_Can0RevData_FD send\r\n");
                // printf("can_rev->data[0] :%02X \r\n", can_rev.data[0]);
                // printf("can_rev->data[1] :%02X\r\n ", can_rev.data[1]);
                // printf("can_rev.data[2] :%02X\r\n ", can_rev.data[2]);

            }


    }

        

 
    else
    {
        printf("[Drv_can0_epoll_msg_transmit] Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
    }
}

void Drv_can0_closeEx(int *fd)
{
	if(*fd>=0)
	{
		close(*fd);
		*fd=-1;
	}
}

/********************************************************************************
 * 函数名称： reset_can_device
 * 功能描述：can 设备的复位操作
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数： 0 表示复位成功，1表示复位失败。
 * ZHX !!!
 ********************************************************************************/
int  Drv_reset_can0_device(const char *can_name)
{
	int canState = 0;
    HAL_can_get_state(can_name, &canState);
    if(canState != 0)
    {
        // LOGE("can0 status is %02X\r\n", canState);
        zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
        Drv_can0_closeEx(&CAN0_FD);

        //zlog_info(debug_out, "开始初始化 CAN0_FD...\n");
        if (HAL_can_ifconfig_init(PORT_CAN0_DEVICE_NAME,PORT_CAN0_CAN_BITRATE) == false)
        {
            zlog_error(debug_out, "HAL_can_ifconfig_init 失败\n");
            return false;
        }
        //zlog_info(debug_out, "CAN0_FD 网络配置成功\n");
    
        while (HAL_can_band_init(PORT_CAN0_DEVICE_NAME,&CAN0_FD) == false)
        {
          //  zlog_error(debug_out, "HAL_can_band_init 失败\n");
            sleep(1);
        }
        //zlog_info(debug_out, "CAN0_FD 绑定成功，fd = %d\n", CAN0_FD);
    }
    return 0;
}




/********************************************************************************
 * 函数名称： Drv_can0_send
 * 功能描述：can0 设备的发送
 * 输入参数：
 * 			sstruct canfd_frame *cansend_data
 * 输出参数： 0 表示发送成功，非0表示发送失败。
 * ZHX !!!
 ********************************************************************************/
// int Drv_can0_send(struct canfd_frame *cansend_data)
// {
    // if(queue_post(&Queue_Can0SendData, (unsigned char *)cansend_data, sizeof(struct canfd_frame)) != 0)
    // {
    //     printf("Queue_Can0RevData send err\r\n");
    //     queue_destroy(&Queue_Can0RevData);
    //     queue_init(&Queue_Can0RevData);
    //     return 1;
    // }
    // else
    // {
    //     return 0;
    // }
// }
int Drv_can0_send( CAN_MESSAGE *pFrame)
{
    struct can_frame can_frame;
    int retryCount = 0;
    const int maxRetries = 3;
    //  ConvertBusToCANFD(pFrame,&canfd_frame);
    Convert_CAN_MESSAGE_to_can_frame(pFrame,&can_frame);
    while (retryCount < maxRetries)
    {
        if (HAL_can_1_write(CAN0_FD, &can_frame))
        {
            return 0;  
        }

        retryCount++;
        // printf("Retrying CAN0 send... (Attempt %d)\n", retryCount); 
    }
    if(retryCount ==3)
    {
        Drv_reset_can0_device(PORT_CAN0_DEVICE_NAME);
    }

    return -1;  
}

int Drv_can0fd_send( CAN_FD_MESSAGE_BUS *pFrame)
{
    struct canfd_frame canfd_frame;
    int retryCount = 0;
    const int maxRetries = 3;
    Drv_write_to_active_buffer(&pFrame,0);//0709添加
    ConvertBusToCANFD(pFrame,&canfd_frame);
    while (retryCount < maxRetries)
    {
        if (HAL_can_write(CAN0_FD, &canfd_frame))
        {
            return 0;  
        }

        retryCount++;
        // usleep(100);  
    }

    return -1;  
}




/////////////////////////////////////////////////////////////////////////////////////////////


//消息解析
bool Drv_BMS_Analysis()
{
    bool state = false;
    state = CP_BMSAnalysis();
    return state;
}

//消息转发CAN0


//消息转发CAN0
bool Drv_BMS_Forward_CAN0(int fd,CAN_MESSAGE *Data)
{
    int cunt = 0;
    bool state = false;
    do
    {
        state = HAL_can_write(fd,Data);
        if(state == false)  
        {
            cunt++;
            zlog_error(debug_out, "CAN0_FD 发送失败\n");
        }
        else
        {

        }
        
    } while ((state == false) && (cunt < 3));
    
  return state;
}


//BCU通信故障

bool Drv_BCU_Communication_Fault()
{
    bool state = false;
    
}