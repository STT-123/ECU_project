
#include "Func_EpollDealwith.h"
#include <stdio.h>
#include "../DRV/Epoll/Drv_epoll.h"
#include "sys/epoll.h"
#include <pthread.h>
// static int my_epollfd ;   //用于监听所有能监听的事件
// static pthread_t ThreadID_Myepoll;


//epoll_wait 事件的处理
// void *Thread_Myepoll(void *arg)
// {
//         printf("myepoll  pthread running \n");
//         my_epoll_dealwith();            //epoll_wait ，然后调用注册的函数
// }



struct epoll_event events[MYMAX_TASTNUM];
/********************************************************************************
 * 函数名称：my_epoll_dealwith
 * 功能描述：处理epoll事件，在一个pthread中运行      此函数会阻塞
 * 输入参数：
 * 			int fd   要监听的文件描述符
 * 			struct epoll_event * ev         监听的事件
 * 输出参数：无
 * lx
 ********************************************************************************/

void my_epoll_dealwith(void)
{
        int num ;
        int test_val;
        int i,j;
        char buf[64];
        struct Myeventdata  event;
	
        for(;;)
        {
            // printf("myepoll  pthread running ok\n");
            num = epoll_wait(my_epollfd,events,epoll_count,-1);   //此处还要改
            // printf("epoll events happen %d\n",num);
            #if MYEPOLL_DEBUG_EN
            printf("epoll events happen %d\n",num);
            #endif
            if(num <0)
            {
            perror("epoll error");
            // return ;
            }
            for( i = 0; i < num; i++)
            {
                // printf("events[i].events %d\n",events[i].events);
                
                if(events[i].events & EPOLLPRI)
                {
                    
                    // lseek(events[i].data.fd,0,SEEK_SET);
                    // myep_tast.task[j].func_handle(events[i].data.ptr);
                    
                   //( void *)events[i].data.ptr.fun_handle(events[i].data);
                    
                    event =*(struct Myeventdata*)events[i].data.ptr;
                    event.fun_handle(events[i].data.ptr);
                    lseek(event.fd,0,SEEK_SET);           //清中断，epoll采用默认LT模式，如果不管会一直触发。
                    // HAL_GPIO_read_epoll(myep_tast.task[j].gpiopin,events[i].data.fd,&test_val);
                //  lseek(events[i].data.fd,0,SEEK_SET);
                //     for( j = 0; j < myep_tast.task_num; j++)         //修改为利用epoll的void * ptr 传入自定义结构体。定义出是gpio事件还是can事件，还是485事件，
                //     {
                //         if(events[i].data.fd == myep_tast.task[j].fd)
                //         {
                //             myep_tast.task[j].func_handle(&myep_tast.task[j].gpiopin);
                //             HAL_GPIO_read_epoll(myep_tast.task[j].gpiopin,events[i].data.fd,&test_val);
                //             break;
                //         }
                //     }
                }
                else if((events[i].events & EPOLLIN)) //can来的数据
                {
                    event =*(struct Myeventdata*)events[i].data.ptr;
                    event.fun_handle(events[i].data.ptr);
                    lseek(event.fd,0,SEEK_SET);           //清中断，epoll采用默认LT模式，如果不管会一直触发。
                }
                else
                {
                    event =*(struct Myeventdata*)events[i].data.ptr;
	                lseek(event.fd,0,SEEK_SET);           //清中断，epoll采用默认LT模式，如果不管会一直触发。
                    
                }
                
            }
        }
}