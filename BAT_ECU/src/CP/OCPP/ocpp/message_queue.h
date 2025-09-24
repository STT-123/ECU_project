#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H
#include <stdbool.h>
#include <json-c/json.h>


bool enqueue_message(struct json_object *msg);
struct json_object *dequeue_message();

#endif