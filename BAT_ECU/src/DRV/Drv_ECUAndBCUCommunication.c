#include "Drv_ECUAndBCUCommunication.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./DRV/LOG/zlog.h"
struct Myeventdata can1evendata;        //分机can epoll 事件
static pthread_mutex_t Mutex_Can1Send;

static int CAN1_FD;  

queue_st	Queue_Can1RevData;                   
queue_st	Queue_Can1SendData;                   
static void can1_epoll_msg_transmit (void * arg);
bool Drv_can1_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can1Send, NULL);
    queue_init(&Queue_Can1RevData);         //用于接收消息后存入
    queue_init(&Queue_Can1SendData);         //用于发送消息存入
     printf("[Drv_can1_init] 开始初始化 CAN1_FD...\n");
    zlog_info(debug_out, "开始初始化 CAN1_FD...\n");
    if (HAL_can1_ifconfig_init() == false)
    {
        printf("[Drv_can1_init] HAL_can1_ifconfig_init 失败\n");
        zlog_error(debug_out, "HAL_can1_ifconfig_init 失败\n");
        return false;
    }
    printf("[Drv_can1_init] CAN1_FD 网络配置成功\n");
    zlog_info(debug_out, "CAN1_FD 网络配置成功\n");

    while (HAL_can1_band_init(&CAN1_FD) == false)
    {
        printf("[Drv_can1_init] HAL_can1_band_init 失败，重试中...\n");
        zlog_error(debug_out, "HAL_can1_band_init 失败\n");
        sleep(1);
    }
    printf("[Drv_can1_init] CAN1_FD 绑定成功，fd = %d\n", CAN1_FD);
    zlog_info(debug_out, "CAN1_FD 绑定成功，fd = %d\n", CAN1_FD);


    can1evendata.fd = CAN1_FD;
    can1evendata.fun_handle =(void*) can1_epoll_msg_transmit;   //回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *) &can1evendata;
     printf("[Drv_can1_init] 添加到 epoll...\n");
    if(-1 == my_epoll_addtast(can1evendata.fd, &ev))
    {
         printf("[Drv_can1_init] my_epoll_addtast 失败\n");
        zlog_info(debug_out,"can1add epoll  fail\r\n");
        return RESULT_FAIL;
    }
    printf("[Drv_can1_init] 初始化完成\n");
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
static void can1_epoll_msg_transmit (void * arg)
{
    struct canfd_frame can_rev;
	struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	// printf("[can1_epoll_msg_transmit] epoll_wait\n");
    if(HAL_can1_read(CAN1_FD, &can_rev, 1) != 0) //   后期改小这个参数
    {
        // printf("Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
        if(queue_post(&Queue_Can1RevData, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
        {
            printf("Queue_Can1RevData send err\r\n");
            queue_destroy(&Queue_Can1RevData);
            queue_init(&Queue_Can1RevData);
        }

    }
    else
    {
        printf("[can1_epoll_msg_transmit] Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
    }
}

void can1_closeEx(int *fd)
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
int  reset_can_device_1(const char *can_name)
{
	int canState = 0;
    HAL_can1_get_state(can_name, &canState);
    if(canState != 0)
    {
        // LOGE("can0 status is %02X\r\n", canState);
        zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
        can1_closeEx(&CAN1_FD);

        zlog_info(debug_out, "开始初始化 CAN1_FD...\n");
        if (HAL_can1_ifconfig_init() == false)
        {
            zlog_error(debug_out, "HAL_can1_ifconfig_init 失败\n");
            return false;
        }
        zlog_info(debug_out, "CAN1_FD 网络配置成功\n");
    
        while (HAL_can1_band_init(&CAN1_FD) == false)
        {
            zlog_error(debug_out, "HAL_can1_band_init 失败\n");
            sleep(1);
        }
        zlog_info(debug_out, "CAN1_FD 绑定成功，fd = %d\n", CAN1_FD);
    }
    return 0;
}




/********************************************************************************
 * 函数名称： can1_send
 * 功能描述：can1 设备的发送
 * 输入参数：
 * 			sstruct canfd_frame *cansend_data
 * 输出参数： 0 表示发送成功，非0表示发送失败。
 * lx
 ********************************************************************************/
int can1_send(struct canfd_frame *cansend_data)
{
    if(queue_post(&Queue_Can1SendData, (unsigned char *)cansend_data, sizeof(struct canfd_frame)) != 0)
    {
        printf("Queue_Can1RevData send err\r\n");
        queue_destroy(&Queue_Can1RevData);
        queue_init(&Queue_Can1RevData);
        return 1;
    }
    else
    {
        return 0;
    }
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

bool Drv_BMS_Forward_CAN0(int fd,CAN_MESSAGE *Data)
{
    int cunt = 0;
    bool state = false;
    do
    {
        state = HAL_can1_write(fd,Data);
        if(state == false)  
        {
            cunt++;
            zlog_error(debug_out, "CAN0 发送失败\n");
        }
        else
        {

        }
        
    } while ((state == false) && (cunt < 3));
    
  return state;
}

//消息转发CAN1
bool Drv_BMS_Forward_CAN1(int fd,CAN_MESSAGE *Data)
{
    int cunt = 0;
    bool state = false;
    do
    {
        state = HAL_can1_write(fd,Data);
        if(state == false)  
        {
            cunt++;
            zlog_error(debug_out, "CAN1_FD 发送失败\n");
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