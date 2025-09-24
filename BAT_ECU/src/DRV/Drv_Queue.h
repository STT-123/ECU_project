#ifndef __DRV_QUEUE_H__
#define __DRV_QUEUE_H__

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define CAN_THREAD_BUFFER_MAX 	 512

#define   QUEUE_DEEPTH     128   /*队列深度*/

typedef struct __QUEUE_ST
{
	pthread_mutex_t mutex_lock;
	pthread_cond_t  cond_not_empty;
	struct
	{
		unsigned char Buffer[CAN_THREAD_BUFFER_MAX];// __attribute__((aligned(8)));//每条消息内容的缓冲区大小
//		canfd_frame Buffer[CAN_THREAD_BUFFER_MAX];//每条消息内容的缓冲区大小
		unsigned int  Length;//每条消息的长度
	} Data[QUEUE_DEEPTH];
	int Count;//队列中消息条数
	int pHeader;//队列中首消息位置
} queue_st, *queue_pst;



// extern queue_st Queue_FissionMsgFiFo;


// extern queue_st	Queue_FisChargeCmd;		/* 分机发送的充电相关命令队列 */
// extern queue_st	Queue_FisInsulationCmd;		/* 分机发送的绝缘检测命令队列 */


// extern queue_st	Queue_PDUSendData;
// extern queue_st Queue_PDUInputInfo;
// extern queue_st Queue_PDUErrorInfo;
// extern queue_st Queue_PDURevData;
// extern queue_st Queue_PDUControlData;
// extern queue_st Queue_LogData;


// extern queue_st	Queue_FissionMultiSendData;

// extern queue_st	Queue_PMControlCmd;		/* 电源模块调控调测相关命令队列 */


/*
 * 函数名称：queue_destroy
 * 功能描述：初始化一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_init(queue_pst pQueue);

/*
 * 函数名称：queue_destroy
 * 功能描述：销毁一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_destroy(queue_pst pQueue);


/*
 * 函数名称：queue_clear
 * 功能描述：清除一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_clear(queue_pst pQueue);

/*
 * 函数名称：queue_getQueueNum
 * 功能描述：获取消息队列数量
 * 输入参数：pQueue：队列指针
 * 输出参数：0：		无数据
 * 		  其他   	有数据
 */
int queue_getQueueNum(queue_pst pQueue);


/*
 * 函数名称：udp_recv_queue_post
 * 功能描述：向队列中发送一则消息
 * 输入参数：pQueue：队列指针
 *                     pBuffer：缓冲区
 *                     Length：长度
 * 输出参数：0成功获取，其他失败
 */
int queue_post(queue_pst pQueue,unsigned char* pBuffer,int Length);

/*
 * 函数名称：queue_pend
 * 功能描述：从队列中获取一则消息
 * 输入参数：pQueue：队列指针
 *                     pBuffer：缓冲区
 *                     Length：长度
 * 输出参数：0成功获取，其他失败
 */
int queue_pend(queue_pst pQueue,unsigned char* pBuffer,int *Length);



#endif