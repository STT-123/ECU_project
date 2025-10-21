#include "Drv_ExternalCANCommunication.h"
#include "log/log.h"
#include "port/myepoll.h"

my_event_data_t can2evendata; // 分机can epoll 事件
static pthread_mutex_t Mutex_Can2Send;

static int CAN2_FD;

queue_t Queue_Can2RevData;

static void Drv_can2_epoll_msg_transmit(void *arg)
{
    struct canfd_frame can_rev;

    // printf("[Drv_can2_epoll_msg_transmit] epoll_wait\n");
    if (HAL_can_read(CAN2_FD, &can_rev, 1) != 0) //   后期改小这个参数
    {
        // printf("Received CAN frame with ID: %d, Length: %d\n", can_rev.can_id, can_rev.len);
        if (queue_post(&Queue_Can2RevData, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
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

bool Drv_can2_init(void)
{
    struct epoll_event ev;

    pthread_mutex_init(&Mutex_Can2Send, NULL);
    queue_init(&Queue_Can2RevData); // 用于接收消息后存入

    if (HAL_can_ifconfig_init(PORT_CAN2_DEVICE_NAME, PORT_CAN2_CAN_BITRATE) == false)
    {
        LOG("%s HAL_can_ifconfig_init 失败\n", PORT_CAN2_DEVICE_NAME);
        return false;
    }

    while (HAL_can_band_init(PORT_CAN2_DEVICE_NAME, &CAN2_FD) == false)
    {
        LOG("%s HAL_can_band_init 失败，重试中...\n", PORT_CAN2_DEVICE_NAME);
        sleep(1);
    }

    can2evendata.fd = CAN2_FD;
    can2evendata.fun_handle = (void *)Drv_can2_epoll_msg_transmit; // 回调函数
    ev.events = EPOLLIN;
    ev.data.ptr = (void *)&can2evendata;
    if (-1 == my_epoll_addtast(can2evendata.fd, &ev))
    {
        LOG("%s add epoll failed \n", PORT_CAN2_DEVICE_NAME);
        return false;
    }

    return true;
}

int Drv_can2_send(CAN_MESSAGE *pFrame)
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

int Drv_can2fd_send(CAN_FD_MESSAGE_BUS *pFrame)
{
    struct canfd_frame canfd_frame;
    int retryCount = 0;
    const int maxRetries = 3;
    ConvertBusToCANFD(pFrame, &canfd_frame);
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

// 消息转发CAN2
bool Drv_BMS_Forward_CAN2(const struct canfd_frame *Data)
{
    int cunt = 0;
    bool state = false;
    do
    {
        state = HAL_can_write(CAN2_FD, Data);
        if (state == false)
        {
            cunt++;
            LOG("CAN2 发送失败\n");
        }
        else
        {
        }

    } while ((state == false) && (cunt < 3));

    return state;
}
