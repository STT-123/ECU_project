#ifndef __C_OTASTATEMONITOR_H__
#define __C_OTASTATEMONITOR_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

extern int otasock;
extern int otasock1;



// extern unsigned char clientConnected;
// extern unsigned char XmodemSendCFlag;
// extern unsigned char XmodemServerReceiveSOH;
// extern unsigned char XmodemServerReceiveEOT;
// extern unsigned char XmodemServerReceiveFileEnd;
// extern unsigned char XmodemServerEnd;




extern unsigned short sblfilenumber ;
extern unsigned short appfilenumber ;

extern int SBl_index;
extern int APP_index;

extern struct timespec AC_OTA_lastCheckTick;

extern pthread_mutex_t task_mutex ;
extern pthread_t* pLwIPTCPDataTaskHandle;

extern FILE *OTAfil;
unsigned int OsIf_GetMilliseconds(void) ;
void *TcpServerExample(void *arg);

unsigned char getClientConnected(void);
void setClientConnected(unsigned char value);

unsigned char getXmodemSendCFlag(void);
void setXmodemSendCFlag(unsigned char value);

unsigned char getXmodemServerReceiveSOH(void);
void setXmodemServerReceiveSOH(unsigned char value);

unsigned char getXmodemServerReceiveEOT(void);
void setXmodemServerReceiveEOT(unsigned char value);

unsigned char getXmodemServerReceiveFileEnd(void);
void setXmodemServerReceiveFileEnd(unsigned char value);

unsigned char getXmodemServerEnd(void);
void setXmodemServerEnd(unsigned char value);
signed char CheckXModemClient(void);
#endif