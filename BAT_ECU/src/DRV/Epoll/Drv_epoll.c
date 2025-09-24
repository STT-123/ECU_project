#include "Drv_epoll.h"
#include "./GLB/G_GloabalVariable.h"
#include "./LOG/Drv_ZLog.h"
int my_epollfd ;   //用于监听所有能监听的事件
static pthread_t ThreadID_Myepoll;
// typedef struct __MYEPOLL_ST
// {
// 	int task_num;           
// 	struct
// 	{
// 		int fd;/* epoll监听文件句柄*/
// 		void (*func_handle)(void *arg);/*对应的处理回调函数*/
// 		int  gpiopin;/* 回调函数的参数*/
// 	} task[MYMAX_TASTNUM];
// }Myepoll_task;

void *Thread_Myepoll(void *arg);
typedef struct 
{
		int fd;/* epoll监听文件句柄*/
		void (*func_handle)(void *arg);/*对应的处理回调函数*/
		int  gpiopin;/* 回调函数的参数*/
	    //注意：此结构体不能大于64位 uint64_t;
}Myepoll_eventdata;
Myepoll_eventdata  myevdata[MYMAX_TASTNUM];

// typedef struct __MYEPOLL_ST
// {
// 	int task_num;           
//     Myepoll_eventdata  myevdata[MYMAX_TASTNUM];
// }Myepoll_task;


// static Myepoll_task  myep_tast;
/********************************************************************************
 * 函数名称：my_epoll_init
 * 功能描述：epoll 初始化    
 *  *输出参数：成功0    失败-1
 * lx
 *******************************************************************************/
int my_epoll_init(void)
{
        int err = 0;
        my_epollfd = epoll_create(50);  //内核2.6.8+参数无意义，大于零即可
        if(my_epollfd < 0)
        {
            perror("my epoll create error");
            return -1;
        }
                    
            err = pthread_create(&ThreadID_Myepoll, NULL, Thread_Myepoll, NULL);			//epoll事件监听回调线程
            if (err != 0)
                zlog_info(debug_out,"Can't create thread :[%s]", strerror(err));
            else
                zlog_info(debug_out,"create thread myepoll ok\r\n");

        // myep_tast.task_num = 0 ;
        return 0;
}
/********************************************************************************
 * 函数名称：Thread_Myepoll
 * 功能描述：epoll_wait   事件处理的线程
 *  *输出参数：成功0    失败-1
 * lx
 *******************************************************************************/
void *Thread_Myepoll(void *arg)
{
        printf("   myepoll  pthread running \n");
        sleep(1);           //此时没有epoll事件
        my_epoll_dealwith();            //epoll_wait ，然后调用注册的函数
}




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
// int my_epoll_addtast(int  fd, struct epoll_event * ev,void (*func_handle)(void * arg),int  gpiopin)   
// {       //初始化主动调用，暂不考虑加🔓
//         if(myep_tast.task_num > (MYMAX_TASTNUM -1)) {
//             return -1;
//         }
//         if(epoll_ctl( my_epollfd, EPOLL_CTL_ADD,fd, ev)<0) //添加到epoll事件集
//         {
//             perror("epoll_ctl error");
//             return -1;
//         }
//         myep_tast.task[myep_tast.task_num].fd = fd;
//         myep_tast.task[myep_tast.task_num].func_handle = func_handle;
//         myep_tast.task[myep_tast.task_num].gpiopin = gpiopin;
//         myep_tast.task_num ++;
//         return 0;
// }
unsigned int epoll_count =  0; //  记录一共有多少个epoll事件
int my_epoll_addtast(int  fd, struct epoll_event * ev) // 回调函数写入ev中   
{       //初始化主动调用，暂不考虑加🔓

        if(epoll_ctl( my_epollfd, EPOLL_CTL_ADD,fd, ev)<0) //添加到epoll事件集
        {
            perror("epoll_ctl error");
            return -1;
        }
        epoll_count++;
        printf("epoll_count = %d\n",epoll_count);
        return 0;
}




/********************************************************************************
 * 函数名称：my_epoll_deltast
 * 功能描述：删除epoll监听事件和任务    
 * 输入参数：
 * 			int fd   要监听的文件描述符
 * 			struct epoll_event * ev         监听的事件
 * 输出参数：无
 * lx
 ********************************************************************************/
int my_epoll_deltast(int  fd, struct epoll_event * ev) 
{

        epoll_ctl( my_epollfd, EPOLL_CTL_DEL,fd, ev); //删除epoll事件
        // myep_tast.task_num --;
        epoll_count --;
}
