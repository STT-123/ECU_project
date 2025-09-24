#define _POSIX_C_SOURCE 199309L
#include "HAL_TIM1.h"
#include "DRV/Epoll/Drv_epoll.h"


void timer_dealwith_repeat (void * arg);
void timer_dealwith_once(void * arg);
/********************************************************************************
 * 函数名称：createTimer
 * 功能描述：创建一个定时器，这个定时器是重复的
 * 输入参数：
 * 			(int32_t uisec   设置间隔多少秒
 * 			int32_t uinsec         间隔多少us
 * 输出参数： 时间的文件句柄timefd
 * lx
 ********************************************************************************/
int create_timer(uint32_t uisec, uint32_t uinsec)
{
    int timefd;
    struct itimerspec timervalue;

    timefd = timerfd_create(CLOCK_MONOTONIC,0);
    if(timefd < 0 )
    {
        perror("timerfd create error");
    }

    //设置开启定时器
    /*
    Setting either field of new_value.it_value to a nonzero value arms the timer. 
    Setting both fields of new_value.it_value to zero disarms the timer.
    意思是如果不设置it_interval的值非零，那么即关闭定时器
    */
            timervalue.it_value.tv_sec = 1 ;
            timervalue.it_value.tv_nsec =0;//  ns          //第一次执行时间

            //设置定时器周期
            timervalue.it_interval.tv_sec = (time_t) uisec;            //
            timervalue.it_interval.tv_nsec =uinsec;

            int ret = timerfd_settime(timefd,0,&timervalue,NULL);
            if(ret < 0)
            {
                perror("timerfd_settime error");
                close (timefd);
                return -1;
            }
            return timefd;
}


/********************************************************************************
 * 函数名称：create_timer_once
 * 功能描述：创建一个定时器，这个定时器是一次性的
 * 输入参数：
 * 			(int32_t uisec   设置间隔多少秒
 * 			int32_t uinsec         间隔多少us
 * 输出参数： 时间的文件句柄timefd
 * lx
 ********************************************************************************/
int create_timer_once(uint32_t uisec, uint32_t uinsec)
{
    int timefd;
    struct itimerspec timervalue;

    timefd = timerfd_create(CLOCK_MONOTONIC,0);                       //CLOCK_MONOTONIC  为系统启动重启到现在的时间  CLOCK_REALTIME  为1970到现在的时间，修改系统时间有影响
    if(timefd < 0 )
    {
        perror("timerfd create error");
    }

    //设置开启定时器
    /*
    Setting either field of new_value.it_value to a nonzero value arms the timer. 
    Setting both fields of new_value.it_value to zero disarms the timer.
    意思是如果不设置it_interval的值非零，那么即关闭定时器
    */
            timervalue.it_value.tv_sec = (time_t) uisec; 
            timervalue.it_value.tv_nsec =uinsec;//  ns          //第一次执行时间

            //设置定时器周期
            timervalue.it_interval.tv_sec = 0;            //
            timervalue.it_interval.tv_nsec = 0;

            int ret = timerfd_settime(timefd,0,&timervalue,NULL);
            if(ret < 0)
            {
                perror("timerfd_settime error");
                close (timefd);
                return -1;
            }
            return timefd;
}


/********************************************************************************
 * 函数名称：timer_addepoll
 * 功能描述：为timer启用epoll监听，调用myepoll加入
 * 输入参数： 
 *                  uint32_t uisec         定时器的s数
 *                  uint32_t uinsec        定时器的ns数
 *                  void  (*callback)(void* arg)     定时器中断后执行的函数
 *                  unsigned char repeat)         定时器单次执行还是重复执行
 *      注意： ns数最大值999999999，如果超过这个值为1s使用s参数
 * 
 * 输出参数：无
 * lx
 ********************************************************************************/
//static struct Myeventdata timerevendata;  //使用 malloc 方便释放
void timer_addepoll(uint32_t uisec, uint32_t uinsec,void  (*callback)(void* arg),unsigned char repeat)
{
    int timerfd;
    int ret;
    struct epoll_event ev; 
    struct Myeventdata *timerevendata;

    timerevendata = (struct Myeventdata *)calloc(1,sizeof(struct Myeventdata));   


    if(repeat == 1)
        {
        timerfd = create_timer(uisec, uinsec);
        timerevendata->fun_handle = (void*)timer_dealwith_repeat;
        }
    else if(repeat == 0)
        {
        timerfd = create_timer_once(uisec, uinsec);
        timerevendata->fun_handle = (void*)timer_dealwith_once;
        }

    timerevendata->fd =timerfd;
    timerevendata->call_back =  (void*)callback;
    ev.events = EPOLLIN| EPOLLERR | EPOLLHUP;
    ev.data.ptr =  (void *)timerevendata;                                                   //单次最后要free
    ret = my_epoll_addtast(timerfd,&ev);
    if(ret < 0)
    {
        perror("timer add epoll error");
    }
    // printf("timer add epoll \n");
}

/********************************************************************************
 * 函数名称：timer_dealwith_repeat
 * 功能描述：定时器到时的消息处理,这个定时器是重复的，
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
void timer_dealwith_repeat (void * arg)
{
        struct Myeventdata evdata;
	evdata = *(struct Myeventdata *)arg;
	uint64_t timedata;
		// printf("timer fd = %d \r\n",evdata.fd);
    if(read(evdata.fd, &timedata, sizeof(timedata)) != 0)   //清中断
    {
    }
        /*************回调执行用户函数*******************/
    evdata.call_back(arg);
    /*************回调执行用户函数*******************/
}

// 结束重复事件
void del_timer_repeat()
{
    // 待完善
}



//单次事件，定时器到后 销毁，执行单次任务，（比如gpio中断的判断）单次和周期//以后再优化，参考时间轮🎡
/********************************************************************************
 * 
 * 
 * 
 * 函数名称：timer_dealwith_once
 * 功能描述：定时器到时的消息处理,这个定时器是重复的，
 * 输入参数：
 * 			struct    Myeventdata  *
 * 输出参数：无
 * lx
 ********************************************************************************/
void timer_dealwith_once (void * arg)
{
        struct Myeventdata evdata;
        struct epoll_event ev; 
	evdata = *(struct Myeventdata *)arg;
	uint64_t timedata;  //必须64位
		// printf("timer fd = %d \r\n",evdata.fd);
    if(read(evdata.fd, &timedata, sizeof(timedata)) != 0)   //清epoll中断
    {

    }
    
    /*************回调执行用户函数*******************/
    evdata.call_back(arg);
    /*************回调执行用户函数*******************/

        ev.events = EPOLLIN| EPOLLERR | EPOLLHUP;
        my_epoll_deltast(evdata.fd,&ev) ;            //删除epoll事件
    close(evdata.fd);           //关闭时间的文件描述符
    free(arg);          //释放内存
}



/***********以下为一个小demo  9999999执行重复任务1s，1s里增加100个定时任务，单次执行 5s 任务处理*****************************************/
//************初始化定时事件
//    timer_addepoll(0,9999999,timer_1s_deal,1);         //定时器重复



// void timer_5s_deal(void * arg)
// {
//     printf("***********************************************time 5 in \n ");
// }
// void timer_1s_deal(void * arg)
// {
//     int i =0;
//     printf("time 1 in \n ");
//     for( i = 0; i <100;i++)
//     {
//     timer_addepoll(0,999999,timer_5s_deal,0);        //用来测试单次的事件有没有造成内存泄漏等
//     }

// }


