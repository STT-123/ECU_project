#ifndef __MYEPOLL_H__
#define __MYEPOLL_H__

#include <sys/epoll.h>

typedef struct
{
    int fd;
    int pin;
    void (*fun_handle)(void *arg); // epoll的回调
    void (*call_back)(void *arg);  // 二级回调，用于epoll回调的函数处理一些清除epoll中断的操作，然后再调用这里的函数实现功能，在功能函数中不需要考虑清除中断的操作
} my_event_data_t;
typedef my_event_data_t *my_event_data_ptr;

int my_epoll_init(void);
int my_epoll_addtast(int fd, struct epoll_event *ev);
int my_epoll_deltast(int fd, struct epoll_event *ev);

#endif // DEBUG