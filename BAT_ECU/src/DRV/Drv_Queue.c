#include "Drv_Queue.h"
#include <pthread.h>
#include <semaphore.h>
#include "main.h"
#include "./FUNC/Func_ECUAndBCUCommunication.h"
/*
 * 函数名称：queue_destroy
 * 功能描述：初始化一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_init(queue_pst pQueue)
{
	pthread_mutex_init(&pQueue->mutex_lock, NULL);
	pthread_cond_init(&pQueue->cond_not_empty, NULL);
	pQueue->Count = 0;
	pQueue->pHeader = 0;
}

/*
 * 函数名称：queue_destroy
 * 功能描述：销毁一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_destroy(queue_pst pQueue)
{
	pthread_mutex_destroy(&pQueue->mutex_lock);
	pQueue->Count = 0;
	pQueue->pHeader = 0;
}


/*
 * 函数名称：queue_clear
 * 功能描述：清除一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_clear(queue_pst pQueue)
{
	pthread_mutex_lock(&pQueue->mutex_lock);
	pQueue->Count = 0;
	pQueue->pHeader = 0;
	pthread_mutex_unlock(&pQueue->mutex_lock);
}

/*
 * 函数名称：queue_getQueueNum
 * 功能描述：获取消息队列数量
 * 输入参数：pQueue：队列指针
 * 输出参数：0：		无数据
 * 		  其他   	有数据
 */
int queue_getQueueNum(queue_pst pQueue)
{
	int counter = -1;
	pthread_mutex_lock(&pQueue->mutex_lock);
	counter = pQueue->Count;
	pthread_mutex_unlock(&pQueue->mutex_lock);
	return counter;
}

/*
 * 函数名称：udp_recv_queue_post
 * 功能描述：向队列中发送一则消息
 * 输入参数：pQueue：队列指针
 *                     pBuffer：缓冲区
 *                     Length：长度
 * 输出参数：0成功获取，其他失败
 */
int queue_post(queue_pst pQueue,unsigned char* pBuffer,int Length)
{
	int ret = -1;
	int IndexAt = 0;
	pthread_mutex_lock(&pQueue->mutex_lock);
	if(pQueue->Count >= QUEUE_DEEPTH)
	{
		ret = -1;
		// printf("queue is full\n");
 
	}
	else
	{
		if(pQueue->pHeader + pQueue->Count >= QUEUE_DEEPTH)
			IndexAt = pQueue->pHeader + pQueue->Count - QUEUE_DEEPTH;
		else
			IndexAt = pQueue->pHeader + pQueue->Count ;
		pQueue->Data[IndexAt].Length = Length;
		memcpy(pQueue->Data[IndexAt].Buffer,pBuffer,pQueue->Data[IndexAt].Length);
		pQueue->Count++ ;
		ret = 0;
		pthread_cond_signal(&pQueue->cond_not_empty);
	}
	pthread_mutex_unlock(&pQueue->mutex_lock);
	return ret ;
}

/*
 * 函数名称：queue_pend
 * 功能描述：从队列中获取一则消息
 * 输入参数：pQueue：队列指针
 *                     pBuffer：缓冲区
 *                     Length：长度
 * 输出参数：0成功获取，其他失败
//  */
// int queue_pend(queue_pst pQueue,unsigned char* pBuffer,int *Length)
// {
// 	int ret = 0;
// 	*Length = 0;
// 	pthread_mutex_lock(&pQueue->mutex_lock);
// 	if(pQueue->Count <= 0)
// 	{
// 		pthread_cond_wait(&pQueue->cond_not_empty, &pQueue->mutex_lock);
// 		ret = -1;
// 		// printf("queue is empty\n");
// 	}
// 	else
// 	{
// 		memcpy(pBuffer,pQueue->Data[pQueue->pHeader].Buffer,pQueue->Data[pQueue->pHeader].Length);
// 		 *Length = pQueue->Data[pQueue->pHeader].Length;
// 		if(++pQueue->pHeader>=QUEUE_DEEPTH)
// 			pQueue->pHeader = 0;
// 		pQueue->Count-- ;
// 		ret = 0;
// 	}
// 	pthread_mutex_unlock(&pQueue->mutex_lock);
// 	// printf("queue_pend pQueue->Count: %d\n",pQueue->Count);
// 	return ret ;
// }


#include "errno.h"
int queue_pend(queue_pst pQueue, unsigned char* pBuffer, int *Length)
{
    int ret = 0;
    *Length = 0;

    pthread_mutex_lock(&pQueue->mutex_lock);
	// printf("[queue_pend] 当前Count = %d\n", pQueue->Count);
    while (pQueue->Count <= 0)
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 0.0015;  // 最多等待 1 秒钟

        int wait_ret = pthread_cond_timedwait(&pQueue->cond_not_empty, &pQueue->mutex_lock, &ts);
        if (wait_ret == ETIMEDOUT) {
            pthread_mutex_unlock(&pQueue->mutex_lock);
            return -2;  // 超时返回
        }
    }

    memcpy(pBuffer, pQueue->Data[pQueue->pHeader].Buffer, pQueue->Data[pQueue->pHeader].Length);
    *Length = pQueue->Data[pQueue->pHeader].Length;

    if (++pQueue->pHeader >= QUEUE_DEEPTH)
        pQueue->pHeader = 0;
    pQueue->Count--;

    pthread_mutex_unlock(&pQueue->mutex_lock);
    return ret;
}
