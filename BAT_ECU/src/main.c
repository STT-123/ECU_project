#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include "./GLB/G_GloabalVariable.h"
#include "main.h"

#include "./DRV/Drv_ECUAndBCUCommunication.h"	
#include "./TASK/Net_Config_Task.h"
#include "TASK/Can_MessageSend_Task.h"
#include "./FUNC/Epoll/Func_EpollDealwith.h"
OTAObject otactrl;
void all_init(void);
void all_Func_init(void);
void all_thread_init(void);
int main(int argc, char **argv)
{
	/*1硬件接口初始化部分*/
	all_init();

	/* 功能初始化部分 */
	// all_Func_init();
	

	/*队列初始化*/

	/*任务线程初始化*/
	all_thread_init();

	while (1)
	{

	}
	
}


void all_init(void)
{
	my_epoll_init();
	usleep(10*1000);
	Drv_can1_init();
	
}

void all_Func_init(void)
{

}

void all_thread_init(void)
{
	CAN1RecvDelTaskCreate();
	CAN1SendTaskCreate();

	OTAUpgradTaskCreate();

	NETConfigTaskCreate();
}

uint32_t GetTimeDifference_ms(struct timespec start_tick) {
    struct timespec current_tick;
    clock_gettime(CLOCK_MONOTONIC, &current_tick);
	// gettimeofday(&current_tick,NULL);
    uint32_t diff_sec = current_tick.tv_sec - start_tick.tv_sec;
    int32_t diff_nsec = current_tick.tv_nsec - start_tick.tv_nsec;

    return diff_sec * 1000 + diff_nsec / 1000000;
}


