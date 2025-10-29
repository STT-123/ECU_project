#include "queue.h"
#include <string.h> // mem操作函数

/*
 * 函数名称：queue_destroy
 * 功能描述：初始化一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_init(queue_ptr pQueue)
{
	pthread_mutex_init(&pQueue->mutex_lock, NULL);
	pQueue->Count = 0;
	pQueue->pHeader = 0;

	memset(pQueue->Data, 0, sizeof(pQueue->Data));
}

/*
 * 函数名称：queue_destroy
 * 功能描述：销毁一队列
 * 输入参数：pQueue：队列指针
 * 输出参数：无
 */
void queue_destroy(queue_ptr pQueue)
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
void queue_clear(queue_ptr pQueue)
{
	pthread_mutex_lock(&pQueue->mutex_lock);
	pQueue->Count = 0;
	pQueue->pHeader = 0;
	pthread_mutex_unlock(&pQueue->mutex_lock);
}

/*
 * 函数名称：queue_get_len
 * 功能描述：获取消息队列数量
 * 输入参数：pQueue：队列指针
 * 输出参数：0： 无数据
 *          其他 有数据
 */
int queue_get_len(queue_ptr pQueue)
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
 *          pBuffer：缓冲区
 *          Length：长度
 * 输出参数：0成功获取，其他失败
 */
int queue_post(queue_ptr pQueue, uint8_t *pBuffer, int Length)
{
	int ret = -1;
	int IndexAt = 0;

	    // 参数验证
    if (pQueue == NULL || pBuffer == NULL || Length <= 0) {
        return -1;
    }

	pthread_mutex_lock(&pQueue->mutex_lock);
	if (pQueue->Count >= QUEUE_DEEPTH)
	{
		ret = -1;
	}
	else
	{
		if (pQueue->pHeader + pQueue->Count >= QUEUE_DEEPTH)
			IndexAt = pQueue->pHeader + pQueue->Count - QUEUE_DEEPTH;
		else
			IndexAt = pQueue->pHeader + pQueue->Count;
		pQueue->Data[IndexAt].Length = Length;
		memcpy(pQueue->Data[IndexAt].Buffer, pBuffer, pQueue->Data[IndexAt].Length);
		pQueue->Count++;
		ret = 0;
	}
	pthread_mutex_unlock(&pQueue->mutex_lock);
	return ret;
}

/*
 * 函数名称：queue_pend
 * 功能描述：从队列中获取一则消息
 * 输入参数：pQueue：队列指针
 *          pBuffer：缓冲区
 *          Length：长度
 * 输出参数：0成功获取，其他失败
 */
int queue_pend(queue_ptr pQueue, uint8_t *pBuffer, int *Length)
{
	int ret = 0;
	*Length = 0;
	pthread_mutex_lock(&pQueue->mutex_lock);
	if (pQueue->Count <= 0)
	{
		ret = -1;
	}
	else
	{
		memcpy(pBuffer, pQueue->Data[pQueue->pHeader].Buffer, pQueue->Data[pQueue->pHeader].Length);
		*Length = pQueue->Data[pQueue->pHeader].Length;
		if (++pQueue->pHeader >= QUEUE_DEEPTH)
			pQueue->pHeader = 0;
		pQueue->Count--;
		ret = 0;
	}
	pthread_mutex_unlock(&pQueue->mutex_lock);
	return ret;
}
