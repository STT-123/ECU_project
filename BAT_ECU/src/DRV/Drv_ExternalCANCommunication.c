// #include "Drv_ExternalCANCommunication.h"
// #include "./HAL/HAL_CAN0.h"




// struct Myeventdata can0evendata;        //分机can epoll 事件
// static pthread_mutex_t Mutex_Can0Send;

// static int CAN0_Fd;  

// static queue_st	Queue_Can0RevData;                   //分机消息队列，用于epoll接收数据存入，防止处理不过来所以用队列，内部使用
// static queue_st	Queue_Can0SendData;  





// bool Drv_can0_init(void)
// {
//     struct epoll_event ev;

//     pthread_mutex_init(&Mutex_Can0Send, NULL);
//     queue_init(&Queue_Can0RevData);         //用于接收消息后存入
//     queue_init(&Queue_Can0SendData);         //用于发送消息存入

//     zlog_info(debug_out, "开始初始化 CAN0...\n");
//     if (HAL_can0_ifconfig_init() == false)
//     {
//         zlog_error(debug_out, "HAL_can0_ifconfig_init 失败\n");
//         return false;
//     }
//     zlog_info(debug_out, "CAN0 网络配置成功\n");

//     while (HAL_can0_band_init(&CAN0_Fd) == false)
//     {
//         zlog_error(debug_out, "HAL_can0_band_init 失败\n");
//         sleep(1);
//     }
//     zlog_info(debug_out, "CAN0 绑定成功，fd = %d\n", CAN0_Fd);


//     can0evendata.fd = CAN0_Fd;
//     can0evendata.fun_handle =(void*) can0_epoll_msg_transmit;   //回调函数
//     ev.events = EPOLLIN;
//     ev.data.ptr = (void *) &can0evendata;
//     if(-1 == my_epoll_addtast(can0evendata.fd, &ev))
//     {
//         zlog_info(debug_out,"can0add epoll  fail\r\n");
//         return RESULT_FAIL;
//     }

//     return true;
// }

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////


// /********************************************************************************
//  * 函数名称：static can0_msg_dealwith
//  * 功能描述：来自分机can的消息接收，注意不可阻塞epoll处理中
//  * 输入参数：
//  * 			struct    Myeventdata  *
//  * 输出参数：无
//  * lx
//  ********************************************************************************/
// static void can0_epoll_msg_transmit (void * arg)
// {
//     struct canfd_frame can_rev;
// 	struct Myeventdata evdata;
// 	evdata = *(struct Myeventdata *)arg;
	
//     if(can_read(CAN0_Fd, &can_rev, 1) != 0) //   后期改小这个参数
// 		{

//             if(queue_post(&Queue_Can0RevData, (unsigned char *)&can_rev, sizeof(can_rev)) != 0)
//             {
//                 printf("Queue_Can0RevData send err\r\n");
//                 queue_destroy(&Queue_Can0RevData);
//                 queue_init(&Queue_Can0RevData);
//             }

// 		}
// }


// /********************************************************************************
//  * 函数名称： reset_can_device
//  * 功能描述：can 设备的复位操作
//  * 输入参数：
//  * 			struct    Myeventdata  *
//  * 输出参数： 0 表示复位成功，1表示复位失败。
//  * lx
//  ********************************************************************************/
// int  reset_can_device(const char *can_name)
// {
// 	int canState = 0;
//     can_get_state(can_name, &canState);
//     if(canState != 0)
//     {
//         // LOGE("can0 status is %02X\r\n", canState);
//         zlog_info(debug_out,"%s status is %02X\r\n",can_name, canState);
//         can_closeEx(&CAN0_Fd);

//         zlog_info(debug_out, "开始初始化 CAN0...\n");
//         if (HAL_can0_ifconfig_init() == false)
//         {
//             zlog_error(debug_out, "HAL_can0_ifconfig_init 失败\n");
//             return false;
//         }
//         zlog_info(debug_out, "CAN0 网络配置成功\n");
    
//         while (HAL_can0_band_init(&CAN0_Fd) == false)
//         {
//             zlog_error(debug_out, "HAL_can0_band_init 失败\n");
//             sleep(1);
//         }
//         zlog_info(debug_out, "CAN0 绑定成功，fd = %d\n", CAN0_Fd);
//     }
//     return 0;
// }




// /********************************************************************************
//  * 函数名称： can0_send
//  * 功能描述：can0 设备的发送
//  * 输入参数：
//  * 			sstruct canfd_frame *cansend_data
//  * 输出参数： 0 表示发送成功，非0表示发送失败。
//  * lx
//  ********************************************************************************/
// int can0_send(struct canfd_frame *cansend_data)
// {
//     if(queue_post(&Queue_Can0SendData, (unsigned char *)cansend_data, sizeof(struct canfd_frame)) != 0)
//     {
//         printf("Queue_Can0RevData send err\r\n");
//         queue_destroy(&Queue_Can0RevData);
//         queue_init(&Queue_Can0RevData);
//         return 1;
//     }
//     else
//     {
//         return 0;
//     }
// }