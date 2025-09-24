#ifndef __FTP_SERVER_TASK_H__
#define __FTP_SERVER_TASK_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <pthread.h>



void FTPServerTaskCreate(void);
#endif