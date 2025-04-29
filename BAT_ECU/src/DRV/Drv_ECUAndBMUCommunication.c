#include "Drv_ECUAndBMUCommunication.h"
#include "./HAL/HAL_CAN2.h"

struct Myeventdata can2evendata;        //分机can epoll 事件
static pthread_mutex_t Mutex_Can2Send;

static int CAN2_Fd;  

queue_st	Queue_Can2RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
queue_st	Queue_Can2SendData;                   //用于发送消息存入

bool Drv_can2_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can2Send, NULL);
    queue_init(&Queue_Can2RevData);         //用于接收消息后存入
    queue_init(&Queue_Can2SendData);         //用于发送消息存入

    zlog_info(debug_out, "开始初始化 CAN2...\n");
    if (HAL_can2_ifconfig_up() == false)
    {
        zlog_error(debug_out, "HAL_can2_ifconfig_init 失败\n");
        return false;
    }
    zlog_info(debug_out, "CAN2 网络配置成功\n");

    while (HAL_can2_band(&CAN2_Fd) == false)
    {
        zlog_error(debug_out, "HAL_can2_band_init 失败\n");
        sleep(2);
    }
    zlog_info(debug_out, "CAN2 绑定成功，fd = %d\n", CAN2_Fd);


    can2evendata.fd = CAN2_Fd;
    can2evendata.fun_handle =(void*) can2_epoll_msg_transmit;   //回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *) &can2evendata;
    if(-1 == my_epoll_addtast(can2evendata.fd, &ev))
    {
        zlog_info(debug_out,"can2add epoll  fail\r\n");
        return RESULT_FAIL;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/********************************************************************************
 * 函数名称：static can2_msg_dealwith
 * 功能描述：来自分机can的消息接收，注意不可阻塞epoll处理中
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
static void can2_epoll_msg_transmit (void * arg)
{
    struct canfd_frame can_rev;
	struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	
    if(HAL_can2_read(CAN2_Fd, &can_rev, 1) != 0) //   后期改小这个参数
		{

            if(queue_post(&Queue_Can2RevData, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
            {
                printf("Queue_Can2RevData send err\r\n");
                queue_destroy(&Queue_Can2RevData);
                queue_init(&Queue_Can2RevData);
            }

		}
}

void can2_closeEx(int *fd)
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
 * lx
 ********************************************************************************/
int  reset_can_device_2(const char *can_name)
{
	int canState = 0;
    HAL_can2_get_state(can_name, &canState);
    if(canState != 0)
    {
        // LOGE("can0 status is %02X\r\n", canState);
        zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
        can2_closeEx(&CAN2_Fd);

        zlog_info(debug_out, "开始初始化 CAN2...\n");
        if (HAL_can2_ifconfig_up() == false)
        {
            zlog_error(debug_out, "HAL_can2_ifconfig_init 失败\n");
            return false;
        }
        zlog_info(debug_out, "CAN2 网络配置成功\n");
    
        while (HAL_can2_band(&CAN2_Fd) == false)
        {
            zlog_error(debug_out, "HAL_can2_band_init 失败\n");
            sleep(1);
        }
        zlog_info(debug_out, "CAN2 绑定成功，fd = %d\n", CAN2_Fd);
    }
    return 0;
}




/********************************************************************************
 * 函数名称： can2_send
 * 功能描述：can2 设备的发送
 * 输入参数：
 * 			sstruct canfd_frame *cansend_data
 * 输出参数： 0 表示发送成功，非0表示发送失败。
 * lx
 ********************************************************************************/
int can2_send(struct canfd_frame *cansend_data)
{
    if(queue_post(&Queue_Can2SendData, (unsigned char *)cansend_data, sizeof(struct canfd_frame)) != 0)
    {
        printf("Queue_Can2RevData send err\r\n");
        queue_destroy(&Queue_Can2RevData);
        queue_init(&Queue_Can2RevData);
        return 1;
    }
    else
    {
        return 0;
    }
}
