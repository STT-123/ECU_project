#include "Drv_ECUAndBMUCommunication.h"
#include "port/myepoll.h"

my_event_data_t can1evendata; // 分机can epoll 事件
static pthread_mutex_t Mutex_Can1Send;

static int CAN1_FD;

queue_t Queue_Can1RevData; // 分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用

static void Drv_can1_epoll_msg_transmit(void *arg)
{
    struct can_frame can_rev;
    CAN_MESSAGE can1_rev;

    memset(&can_rev, 0, sizeof(struct can_frame));
    memset(&can1_rev, 0, sizeof(CAN_MESSAGE));
    if (HAL_can1_read(CAN1_FD, &can_rev, 1) > 0) //   后期改小这个参数
    {
        //   printf("can_rev.id = %x\r\n", can_rev.can_id);
        //   printf("can_rev.dlc = %d\r\n", can_rev.can_dlc);
        //   printf("can_rev.data = %x %x %x %x %x %x %x %x\r\n", can_rev.data[0], can_rev.data[1], can_rev.data[2], can_rev.data[3], can_rev.data[4], can_rev.data[5], can_rev.data[6], can_rev.data[7]);
        Convert_can_frame_to_CAN_MESSAGE(&can_rev, &can1_rev);
        //   printf("can1_rev.ID = %x\r\n", can1_rev.ID);
        //   printf("can1_rev.Length = %d\r\n", can1_rev.Length);
        //   printf("can1_rev.Data = %x %x %x %x %x %x %x %x\r\n", can1_rev.Data[0], can1_rev.Data[1], can1_rev.Data[2], can1_rev.Data[3], can1_rev.Data[4], can1_rev.Data[5], can1_rev.Data[6], can1_rev.Data[7]);
        if (queue_post(&Queue_Can1RevData, (unsigned char *)&can1_rev, sizeof(CAN_MESSAGE)) != 0)
        {
            queue_destroy(&Queue_Can1RevData);
            queue_init(&Queue_Can1RevData);
        }
    }
}

// 初始化
bool Drv_can1_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can1Send, NULL);
    queue_init(&Queue_Can1RevData); // 用于接收消息后存入

    if (HAL_can_ifconfig_init(PORT_CAN1_DEVICE_NAME, PORT_CAN1_CAN_BITRATE) == false)
    {
        LOG("%s HAL_can_ifconfig_init 失败\n", PORT_CAN1_DEVICE_NAME);
        return false;
    }

    while (HAL_can_band_init(PORT_CAN1_DEVICE_NAME, &CAN1_FD) == false)
    {
        LOG("%s HAL_can_band_init 失败，重试中...\n", PORT_CAN1_DEVICE_NAME);
        sleep(1);
    }

    can1evendata.fd = CAN1_FD;
    can1evendata.fun_handle = (void *)Drv_can1_epoll_msg_transmit;
    ev.events = EPOLLIN;
    ev.data.ptr = (void *)&can1evendata;
    if (-1 == my_epoll_addtast(can1evendata.fd, &ev))
    {
        LOG("%s add epoll failed \n", PORT_CAN1_DEVICE_NAME);
        return false;
    }

    return true;
}

// 发送can报文
int Drv_can1_send(CAN_MESSAGE *pFrame)
{
    struct can_frame can_frame;
    int retryCount = 0;
    const int maxRetries = 3;
    Convert_CAN_MESSAGE_to_can_frame(pFrame, &can_frame);
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

// 发送canfd报文
int Drv_can1fd_send(struct canfd_frame *cansend_data)
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
