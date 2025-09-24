#include "message_queue.h"
#include <pthread.h>
#include <stdlib.h>
#include "ws_client.h"
/*
    功能描述： 此文件主要实现一个json对象指针的 环形缓冲消息队列，
        队列中只存json对象的指针。

        目的是 减少拷贝操作，ocpp消息全部为json数据，在数据创建和操作的
        过程中均使用了json对象的创建添加操作，最后得到的也为json对象。
        直接传递json对象，在出队后销毁json对象，减少中间的拷贝。

        内存操作：
            申请过程： 创建json对象的时候 json_object_new_object
                    内部调用malloc申请了内存
            释放过程: 出队后调用json_object_put() 释放
        
        
        选择json-c 而非CJSON 因为CJSON非线程安全，在多线程同时调用
                cJSON_Parse()、cJSON_Print() 等函数会
                导致程序崩溃，解析失败，数据混乱

*/










#define QUEUE_SIZE 128

static struct json_object *queue[QUEUE_SIZE];
static int head = 0;
static int tail = 0;
static int count = 0;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * 非阻塞入队
 * 返回 true 表示成功，false 表示队列已满
 */
bool enqueue_message(struct json_object *msg) {
    bool result = false;
    if(msg==NULL)
    {
        return result;
    }
    pthread_mutex_lock(&lock);

    if (count < QUEUE_SIZE) {
        queue[tail] = msg;  //json_object_get(msg);  
        tail = (tail + 1) % QUEUE_SIZE;
        count++;
        result = true;
    }

    pthread_mutex_unlock(&lock);
    websocket_request_write();
    return result;
}

/**
 * 非阻塞出队
 * 返回 NULL 表示队列为空
 */
struct json_object *dequeue_message() {
    struct json_object *msg = NULL;
    pthread_mutex_lock(&lock);

    if (count > 0) {
        msg = queue[head];
        head = (head + 1) % QUEUE_SIZE;
        count--;
    }

    pthread_mutex_unlock(&lock);
    return msg;
}
