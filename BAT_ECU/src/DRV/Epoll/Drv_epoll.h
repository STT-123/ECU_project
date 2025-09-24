#ifndef __DRV_EPOLL_H__
#define __DRV_EPOLL_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/epoll.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>

#define  MYMAX_TASTNUM    100            //最大的监听任务数量
extern int my_epollfd ;
extern unsigned int epoll_count; //  记录一共有多少个epoll事件
struct Myeventdata
{
    int fd;
    int pin;
    void (*fun_handle)(void *arg);         //epoll的回调
    void (*call_back)(void *arg);           //二级回调，用于 epoll回调的函数处理一些清除epoll中断的操作，然后再调用这里的函数实现功能，在功能函数中不需要考虑清除中断的操作
};


// void *Thread_Myepoll(void *arg);

/********************************************************************************
 * 函数名称：my_epoll_init
 * 功能描述：epoll 初始化    
 *  *输出参数：成功0    失败-1
 * lx
 *******************************************************************************/
int my_epoll_init(void);


/********************************************************************************
 * 函数名称：my_epoll_addtast
 * 功能描述：添加epoll监听事件和任务    
 * 输入参数：
 * 			int fd   要监听的文件描述符
 * 			struct epoll_event * ev         监听的事件
 *          void (*func_handle)(void * arg)   事件的回调函数,   根据不同函数传入值，针对gpio可以为&gpiopin，
 *          int gpiopin                           回调函数需要的参数,主要是为gpio考虑，传入gpio的pin号，有事件可以返回到回调函数中。回调函数可以知道pin号
 * 输出参数：成功0    失败-1
 * lx
 ********************************************************************************/
// int my_epoll_addtast(int  fd, struct epoll_event * ev,void (*func_handle)(void * arg),int  gpiopin)  ;

int my_epoll_addtast(int  fd, struct epoll_event * ev) ;// 回调函数写入ev中   

/********************************************************************************
 * 函数名称：my_epoll_deltast
 * 功能描述：删除epoll监听事件和任务    
 * 输入参数：
 * 			int fd   要监听的文件描述符
 * 			struct epoll_event * ev         监听的事件
 * 输出参数：无
 * lx
 ********************************************************************************/
int my_epoll_deltast(int  fd, struct epoll_event * ev) ;



/********************************************************************************
 * 函数名称：my_epoll_dealwith
 * 功能描述：处理epoll事件，在一个pthread中运行epoll_wait会阻塞
 * 输入参数：
 * 			int fd   要监听的文件描述符
 * 			struct epoll_event * ev         监听的事件
 * 输出参数：无
 * lx
 ********************************************************************************/
void my_epoll_dealwith(void);












#endif // DEBUG