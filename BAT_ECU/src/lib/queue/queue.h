#ifndef QUEUE_H_
#define QUEUE_H_

#include <pthread.h>
#include "stdint.h"

#define CAN_THREAD_BUFFER_MAX 512 // 
#define QUEUE_DEEPTH 128					// 最大队列存储长度

typedef struct _queue
{
	pthread_mutex_t mutex_lock;
	struct
	{
		uint8_t Buffer[CAN_THREAD_BUFFER_MAX];
		unsigned int Length;
	} Data[QUEUE_DEEPTH];
	int Count;
	int pHeader;
} queue_t;
typedef queue_t *queue_ptr;

void queue_init(queue_ptr pQueue);
void queue_destroy(queue_ptr pQueue);
void queue_clear(queue_ptr pQueue);
int queue_get_len(queue_ptr pQueue);
int queue_post(queue_ptr pQueue, uint8_t *pBuffer, int Length);
int queue_pend(queue_ptr pQueue, uint8_t *pBuffer, int *Length);

#endif /* QUEUE_H_ */
