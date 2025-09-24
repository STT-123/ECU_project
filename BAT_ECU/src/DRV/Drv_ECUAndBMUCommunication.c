#include "Drv_ECUAndBMUCommunication.h"
#include "./HAL/HAL_CAN.h"

struct Myeventdata can1evendata;        //分机can epoll 事件
static pthread_mutex_t Mutex_Can1Send;

static int CAN1_FD;  

queue_st	Queue_Can1RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
queue_st	Queue_Can1SendData;                   //用于发送消息存入

bool Drv_can1_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can1Send, NULL);
    queue_init(&Queue_Can1RevData);         //用于接收消息后存入
    queue_init(&Queue_Can1SendData);         //用于发送消息存入

    zlog_info(debug_out, "开始初始化 CAN1...\n");
    if (HAL_can1_ifconfig_init(PORT_CAN1_DEVICE_NAME,PORT_CAN1_CAN_BITRATE) == false)
    {
        zlog_error(debug_out, "HAL_can1_ifconfig_init 失败\n");
        return false;
    }
    zlog_info(debug_out, "CAN1 网络配置成功\n");

    while (HAL_can1_band_init(PORT_CAN1_DEVICE_NAME,&CAN1_FD) == false)
    {
        zlog_error(debug_out, "HAL_can1_band_init 失败\n");
        sleep(2);
    }
    zlog_info(debug_out, "CAN1 绑定成功，fd = %d\n", CAN1_FD);

    can1evendata.fd = CAN1_FD;
    can1evendata.fun_handle =(void*) Drv_can1_epoll_msg_transmit;   //回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *) &can1evendata;
    if(-1 == my_epoll_addtast(can1evendata.fd, &ev))
    {
        zlog_info(debug_out,"can1add epoll  fail\r\n");
        return RESULT_FAIL;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************
 * 函数名称：static can1_msg_dealwith
 * 功能描述：来自分机can的消息接收，注意不可阻塞epoll处理中
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
static void Drv_can1_epoll_msg_transmit (void * arg)
{
    struct can_frame can_rev;
    CAN_MESSAGE  can1_rev;
	struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	memset(&can_rev, 0, sizeof(struct can_frame));
    memset(&can1_rev, 0, sizeof(CAN_MESSAGE));
    if(HAL_can1_read(CAN1_FD, &can_rev, 1) > 0) //   后期改小这个参数
    {
        //   printf("can_rev.id = %x\r\n", can_rev.can_id);
        //   printf("can_rev.dlc = %d\r\n", can_rev.can_dlc);
        //   printf("can_rev.data = %x %x %x %x %x %x %x %x\r\n", can_rev.data[0], can_rev.data[1], can_rev.data[2], can_rev.data[3], can_rev.data[4], can_rev.data[5], can_rev.data[6], can_rev.data[7]);
          Convert_can_frame_to_CAN_MESSAGE(&can_rev, &can1_rev);
        //   printf("can1_rev.ID = %x\r\n", can1_rev.ID);
        //   printf("can1_rev.Length = %d\r\n", can1_rev.Length);
        //   printf("can1_rev.Data = %x %x %x %x %x %x %x %x\r\n", can1_rev.Data[0], can1_rev.Data[1], can1_rev.Data[2], can1_rev.Data[3], can1_rev.Data[4], can1_rev.Data[5], can1_rev.Data[6], can1_rev.Data[7]);
		{

            if(queue_post(&Queue_Can1RevData, (unsigned char *)&can1_rev, sizeof(CAN_MESSAGE)) != 0)
            {
                // printf("Queue_Can1RevData send err\r\n");
                queue_destroy(&Queue_Can1RevData);
                queue_init(&Queue_Can1RevData);
            }

		}
    }
}

void Drv_can1_closeEx(int *fd)
{
	if(*fd>=0)
	{
		close(*fd);
		*fd=-1;
	}
}
/********************************************************************************
 * 函数名称： Drv_reset_can1_device
 * 功能描述：can 设备的复位操作
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数： 0 表示复位成功，1表示复位失败。
 * lx
 ********************************************************************************/
int  Drv_reset_can1_device(const char *can_name)
{
	int canState = 0;
    HAL_can_get_state(can_name, &canState);
    if(canState != 0)
    {
        // LOGE("can0 status is %02X\r\n", canState);
        zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
        Drv_can1_closeEx(&CAN1_FD);

        zlog_info(debug_out, "开始初始化 CAN1...\n");
        if (HAL_can1_ifconfig_init(PORT_CAN1_DEVICE_NAME,PORT_CAN1_CAN_BITRATE) == false)
        {
            zlog_error(debug_out, "HAL_can1_ifconfig_init 失败\n");
            return false;
        }
        zlog_info(debug_out, "CAN1 网络配置成功\n");
    
        while (HAL_can_band_init(PORT_CAN1_DEVICE_NAME,&CAN1_FD) == false)
        {
            zlog_error(debug_out, "HAL_can1_band_init 失败\n");
            sleep(1);
        }
        zlog_info(debug_out, "CAN1 绑定成功，fd = %d\n", CAN1_FD);
    }
    return 0;
}




/********************************************************************************
 * 函数名称： Drv_can1_send
 * 功能描述：can1 设备的发送
 * 输入参数：
 * 			sstruct canfd_frame *cansend_data
 * 输出参数： 0 表示发送成功，非0表示发送失败。
 * lx
 ********************************************************************************/
int Drv_can1_send( CAN_MESSAGE *pFrame)
{
    struct can_frame can_frame;
    int retryCount = 0;
    const int maxRetries = 3;
     Convert_CAN_MESSAGE_to_can_frame(pFrame,&can_frame);
    while (retryCount < maxRetries)
    {
        if (HAL_can_1_write(CAN1_FD, &can_frame))
        {
            return 0;  
        }

        retryCount++;
    }

    return -1;  
}


int Drv_can1fd_send( struct canfd_frame *cansend_data)
{
    int retryCount = 0;
    const int maxRetries = 3;

    while (retryCount < maxRetries)
    {
        if (HAL_can_write(CAN1_FD, &cansend_data))
        {
            return 0;  
        }

        retryCount++;
        usleep(100);  
    }

    return -1;  
}
