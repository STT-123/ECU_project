#include "myepoll.h"
#include <sys/epoll.h> // epoll
#include <pthread.h>   // 线程
#include <unistd.h>    // usleep函数
#include <string.h>    // 主要声明 strerror()
#include <errno.h>     // 提供 errno 宏（可选，但通常一起使用）
#include "log.h"       // 日志接口

#define MYMAX_TASTNUM 100 // 最大的监听任务数量

// 记录一共有多少个epoll事件
static unsigned int epoll_count = 0;
struct epoll_event events[MYMAX_TASTNUM];

static int my_epollfd; // 用于监听所有能监听的事件
static void *epoll_thread_func(void *arg)
{
    int num;
    int i;
    my_event_data_t event;

    LOG("[EPOLL] epoll_thread_func running ");

    sleep(5); // 此时没有epoll事件

    for (;;)
    {
        num = epoll_wait(my_epollfd, events, epoll_count, -1);
#if 0
        printf("epoll events happen %d\n", num);
#endif
        if (num < 0)
        {
            perror("epoll error");
        }
        for (i = 0; i < num; i++)
        {
            if (events[i].events & EPOLLPRI)
            {
                event = *(my_event_data_ptr)events[i].data.ptr;
                event.fun_handle(events[i].data.ptr);
                lseek(event.fd, 0, SEEK_SET); // 清中断，epoll采用默认LT模式，如果不管会一直触发。
            }
            else if ((events[i].events & EPOLLIN))
            {
                event = *(my_event_data_ptr)events[i].data.ptr;
                event.fun_handle(events[i].data.ptr);
                lseek(event.fd, 0, SEEK_SET); // 清中断，epoll采用默认LT模式，如果不管会一直触发。
            }
            else
            {
                event = *(my_event_data_ptr)events[i].data.ptr;
                lseek(event.fd, 0, SEEK_SET); // 清中断，epoll采用默认LT模式，如果不管会一直触发。
            }
        }
    }

    return NULL;
}

// epoll 初始化
static pthread_t epoll_thread_id;
int my_epoll_init(void)
{
    LOG("[EPOLL] my_epoll_init ");

    int err = 0;
    my_epollfd = epoll_create(50); // 内核2.6.8+参数无意义，大于零即可
    if (my_epollfd < 0)
    {
        perror("[EPOLL] my epoll create error");
        return -1;
    }

    err = pthread_create(&epoll_thread_id, NULL, &epoll_thread_func, NULL);
    if (err != 0)
        LOG("[EPOLL] Create epoll_thread_func Failed, [%s]", strerror(err));

    usleep(50 * 1000);
    LOG(" ");

    return 0;
}

// 回调函数写入ev中
// int fd: 要监听的文件描述符
// struct epoll_event * ev: 监听的事件
int my_epoll_addtast(int fd, struct epoll_event *ev)
{
    if (epoll_ctl(my_epollfd, EPOLL_CTL_ADD, fd, ev) < 0)
    {
        perror("epoll_ctl error");
        return -1;
    }
    epoll_count++;

    return 0;
}

// 删除epoll监听事件和任务
// int fd: 要监听的文件描述符
// struct epoll_event * ev: 监听的事件
int my_epoll_deltast(int fd, struct epoll_event *ev)
{
    epoll_ctl(my_epollfd, EPOLL_CTL_DEL, fd, ev);
    epoll_count--;

    return 0;
}
