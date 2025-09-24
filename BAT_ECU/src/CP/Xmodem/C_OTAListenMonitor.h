#ifndef __C_OTALISTENMONITOR_H__
#define __C_OTALISTENMONITOR_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>                   
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


void* Lwip_Listen_TASK(void* param);

#endif