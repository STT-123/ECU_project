#include "Drv_ExternalCANCommunication.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./DRV/LOG/zlog.h"
struct Myeventdata can2evendata;        //分机can epoll 事件
static pthread_mutex_t Mutex_Can2Send;

static int CAN2_FD;  

queue_st	Queue_Can2RevData;                   
// queue_st	Queue_Can2SendData;                   
static void Drv_can2_epoll_msg_transmit (void * arg);
bool Drv_can2_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can2Send, NULL);
    queue_init(&Queue_Can2RevData);         //用于接收消息后存入
    // queue_init(&Queue_Can2SendData);         //用于发送消息存入
     printf("[Drv_can2_init] 开始初始化 CAN2_FD...\n");
    zlog_info(debug_out, "开始初始化 CAN2_FD...\n");
    if (HAL_can_ifconfig_init(PORT_CAN2_DEVICE_NAME,PORT_CAN2_CAN_BITRATE) == false)
    {
        printf("[Drv_can2_init] HAL_can_ifconfig_init 失败\n");
        zlog_error(debug_out, "HAL_can_ifconfig_init 失败\n");
        return false;
    }
    printf("[Drv_can2_init] CAN2_FD 网络配置成功\n");
    zlog_info(debug_out, "CAN2_FD 网络配置成功\n");

    while (HAL_can_band_init(PORT_CAN2_DEVICE_NAME,&CAN2_FD) == false)
    {
        printf("[Drv_can2_init] HAL_can_band_init 失败，重试中...\n");
        zlog_error(debug_out, "HAL_can_band_init 失败\n");
        sleep(1);
    }
    printf("[Drv_can2_init] CAN2_FD 绑定成功，fd = %d\n", CAN2_FD);
    zlog_info(debug_out, "CAN2_FD 绑定成功，fd = %d\n", CAN2_FD);


    can2evendata.fd = CAN2_FD;
    can2evendata.fun_handle =(void*) Drv_can2_epoll_msg_transmit;   //回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *) &can2evendata;
     printf("[Drv_can2_init] 添加到 epoll...\n");
    if(-1 == my_epoll_addtast(can2evendata.fd, &ev))
    {
         printf("[Drv_can2_init] my_epoll_addtast 失败\n");
        zlog_info(debug_out,"can2add epoll  fail\r\n");
        return RESULT_FAIL;
    }
    printf("[Drv_can2_init] 初始化完成\n");
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************
 * 函数名称：static can2_msg_dealwith
 * 功能描述：来自分机can的消息接收，注意不可阻塞epoll处理中
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * ZHX ！！！
 ********************************************************************************/
static void Drv_can2_epoll_msg_transmit (void * arg)
{
    struct canfd_frame can_rev;
	struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	// printf("[Drv_can2_epoll_msg_transmit] epoll_wait\n");
    if(HAL_can_read(CAN2_FD, &can_rev, 1) != 0) //   后期改小这个参数
    {
        // printf("Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
        if(queue_post(&Queue_Can2RevData, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
        {
            // printf("Queue_Can2RevData send err\r\n");
            queue_destroy(&Queue_Can2RevData);
            queue_init(&Queue_Can2RevData);
        }

    }
    else
    {
        printf("[Drv_can2_epoll_msg_transmit] Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
    }
}

void Drv_can2_closeEx(int *fd)
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
 * ZHX ！！！
 ********************************************************************************/
int  Drv_reset_can2_device(const char *can_name)
{
	int canState = 0;
    HAL_can_get_state(can_name, &canState);
    if(canState != 0)
    {
        // LOGE("can2 status is %02X\r\n", canState);
        zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
        Drv_can2_closeEx(&CAN2_FD);

        zlog_info(debug_out, "开始初始化 CAN2_FD...\n");
        if (HAL_can_ifconfig_init(PORT_CAN2_DEVICE_NAME,PORT_CAN2_CAN_BITRATE) == false)
        {
            zlog_error(debug_out, "HAL_can_ifconfig_init 失败\n");
            return false;
        }
        zlog_info(debug_out, "CAN2_FD 网络配置成功\n");
    
        while (HAL_can_band_init(PORT_CAN2_DEVICE_NAME,&CAN2_FD) == false)
        {
            zlog_error(debug_out, "HAL_can_band_init 失败\n");
            sleep(1);
        }
        zlog_info(debug_out, "CAN2_FD 绑定成功，fd = %d\n", CAN2_FD);
    }
    return 0;
}




/********************************************************************************
 * 函数名称： Drv_can2_send
 * 功能描述：can2 设备的发送
 * 输入参数：
 * 			sstruct canfd_frame *cansend_data
 * 输出参数： 0 表示发送成功，非0表示发送失败。
 * ZHX ！！！
 ********************************************************************************/
// int Drv_can2_send(struct canfd_frame *cansend_data)
// {
    // if(queue_post(&Queue_Can2SendData, (unsigned char *)cansend_data, sizeof(struct canfd_frame)) != 0)
    // {
    //     printf("Queue_Can2RevData send err\r\n");
    //     queue_destroy(&Queue_Can2RevData);
    //     queue_init(&Queue_Can2RevData);
    //     return 1;
    // }
    // else
    // {
    //     return 0;
    // }
// }
int Drv_can2_send( CAN_MESSAGE *pFrame)
{
    int retryCount = 0;
    const int maxRetries = 3;
    while (retryCount < maxRetries)
    {
        if (HAL_can_write(CAN2_FD, pFrame))
        {
            return 0;  
        }

        retryCount++;
        usleep(100);  
    }

    return -1;  
}

int Drv_can2fd_send( CAN_FD_MESSAGE_BUS *pFrame)
{
    struct canfd_frame canfd_frame;
    int retryCount = 0;
    const int maxRetries = 3;
    ConvertBusToCANFD(pFrame,&canfd_frame);
    while (retryCount < maxRetries)
    {
        if (HAL_can_write(CAN2_FD, &canfd_frame))
        {
            return 0;  
        }

        retryCount++;
        usleep(100);  
    }

    return -1;  
}


/////////////////////////////////////////////////////////////////////////////////////////////



//消息转发CAN2

bool Drv_BMS_Forward_CAN2(const struct canfd_frame *Data)
{
    int cunt = 0;
    bool state = false;
    do
    {
        state = HAL_can_write(CAN2_FD,Data);
        if(state == false)  
        {
            cunt++;
            zlog_error(debug_out, "CAN2 发送失败\n");
        }
        else
        {

        }
        
    } while ((state == false) && (cunt < 3));
    
  return state;
}


