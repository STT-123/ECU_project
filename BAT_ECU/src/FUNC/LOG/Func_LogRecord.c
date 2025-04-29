#include "Func_LogRecord.h"
#include "G_GloabalVariable.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "./DRV/LOG/Drv_ZLog.h"
pthread_t ThreadID_Log;


void *Thread_Log(void *arg)
{
		unsigned short time_count =0;
		for(;;)
		{

		//log_transfer_dealwith();             //日志传输处理
		sleep(1);
		time_count++;
			if(time_count == 6000)     //100分钟 
			{
			time_count = 0;
			system("cd /usr/xcharge/log \n rm $(ls |grep -E 'lx.[0-9][0-9]|lx.[1-9]')");      //后期需要改成popen函数读取返回值

			}
		}
}


void log_init()
{
		int err = 0;
	LOG_INIT(1);   //1开启printf 0 关闭printf
	// queue_init(&Queue_LogData);           //初始化log队列

		err = pthread_create(&(ThreadID_Log), NULL, &Thread_Log, NULL);
	// if (err != 0)
		// LOGE("Can't create thread :[%s]", strerror(err));
	// else
		// LOGE("create thread log ok\r\n");
}