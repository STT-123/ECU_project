#define _GNU_SOURCE
#include "C_OTAStateMonitor.h"
#include  "../BMS/bms/bms_cortol.h"
#include "../GLB/G_AddressDefinition.h"
#include "../GLB/G_GloabalVariable.h"
#include "C_OTAListenMonitor.h"
#include "./CP/Modbus/C_ModbusServer.h"
#include "./CP/Xmodem/C_OTADataMonitor.h"
#include "main.h"

struct timespec AC_OTA_lastCheckTick;

unsigned short sblfilenumber = 0xFFFF;//SBL文件数量大小
unsigned short appfilenumber = 0xFFFF;//app文件数量大小
int SBl_index = 0;
int APP_index = 0;

int otasock = -1;
int otasock1 = -1;

volatile unsigned long prvmsgtimer = 0;

static int otafileret = -1;  // 初始化为自定义值（-1 表示未初始化）

*pLwIPTCPDataTaskHandle = NULL;
*pLwIPTCPListenTaskHandle = NULL;




static unsigned char clientConnected;
static unsigned char XmodemSendCFlag;
static unsigned char XmodemServerReceiveSOH;
static unsigned char XmodemServerReceiveEOT;
static unsigned char XmodemServerReceiveFileEnd = 0;
static unsigned char XmodemServerEnd;



pthread_mutex_t task_mutex = PTHREAD_MUTEX_INITIALIZER;

FILE *OTAfil = NULL;

// unsigned int GetTimeDifference_ms(unsigned int lastTick) {
//     struct timespec now;
//     clock_gettime(CLOCK_MONOTONIC, &now);
//     unsigned int now_ms = (now.tv_sec * 1000 + now.tv_nsec / 1000000);
//     return now_ms - lastTick;
// }

unsigned int OsIf_GetMilliseconds(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec * 1000 + now.tv_nsec / 1000000);
}


void *TcpServerExample(void *arg) {
    unsigned int startTime = 0;
    unsigned short curotaCtrregval = 0xFFFF;
    unsigned short prvotaCtrregval = 0xFFFF;
    static unsigned char step = 0;
    static unsigned char times = 0;
    unsigned short times1 = 0;

    printf("TcpServerExample task!\n");

    step = 1;
    while(1) {
        if (otactrl.UpDating == 1) {  
            CP_set_modbus_reg_val(BMS_POWER_UPDATING, 1);
        }

        if (otactrl.OTAStart == 0 && (sblfilenumber != 0) && ((GetTimeDifference_ms(AC_OTA_lastCheckTick)) >= 30000)) {
            SBl_index = 0;
            APP_index = 0;
        }

        int ret = CP_get_modbus_reg_val(OTACTRLREGADDR, &curotaCtrregval);
        ret = CP_get_modbus_reg_val(AC_SBL_OTAFILENUMBER, &sblfilenumber);
        ret = CP_get_modbus_reg_val(AC_APP_OTAFILENUMBER, &appfilenumber);

        if (ret < 0) {
            printf("ret %d get modbus reg val error\n", ret);
        } else {
            if ((curotaCtrregval != prvotaCtrregval) && (otactrl.OTAStart == 0)) {
                printf("ota curotaCtrregval 0x%x prvotaCtrregval 0x%x\n", curotaCtrregval, prvotaCtrregval);

                if (curotaCtrregval == 0x0000) {
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                    // CloseXModemServer();
                    // XmodemServerEnd = 0;
                    step = 2;
                }

                if (curotaCtrregval == 0x0001) {
                    // 临界区保护：确保任务创建不会出现竞态条件
                    pthread_mutex_lock(&task_mutex);  // 锁住临界区

                    if (pLwIPTCPListenTaskHandle == NULL) {
                        pLwIPTCPListenTaskHandle = malloc(sizeof(pthread_t));
                        pLwIPTCPDataTaskHandle = malloc(sizeof(pthread_t));

                        if (pLwIPTCPListenTaskHandle == NULL || pLwIPTCPDataTaskHandle == NULL) {
                            printf("TcpServerExample task malloc failed!\n");
                            while(1) {
                                sleep(1);
                            }
                        }

                        *pLwIPTCPDataTaskHandle = NULL;
                        *pLwIPTCPListenTaskHandle = NULL;

                        // 创建监听任务
                        pthread_create(pLwIPTCPListenTaskHandle, NULL, Lwip_Listen_TASK, NULL);
                        printf("Lwip_Listen xTaskCreate!\n");

                        if (ret == 0) {
                            CP_set_modbus_reg_val(OTASTATUSREGADDR, 1);
                        }
                    }

                    pthread_mutex_unlock(&task_mutex);  // 解锁临界区
                    startTime = OsIf_GetMilliseconds();
                    while(1) {
                        unsigned int currentTime = OsIf_GetMilliseconds();
                        ret = CheckXModemClient();
                        unsigned int time = currentTime - startTime;

                        if (ret == 0) {
                            while(1) {
                                char c = 'C';
                                signed char ret = write(otasock1, &c, 1);
                                printf("write tcp message C to client ret %d!\n", ret);
                                printf("otasock1 %d!\n", otasock1);

                                if (ret == 1) {
                                    printf("write tcp message C to client!\n");
                                    XmodemSendCFlag = 1;
                                }

                                unsigned int RvTime = OsIf_GetMilliseconds();
                                while(1) {
                                    unsigned int RvPassTime = OsIf_GetMilliseconds() - RvTime;

                                    if (XmodemServerReceiveSOH) {
                                        printf("Received SOH!\n");
                                        break;
                                    }

                                    if (RvPassTime >= 2000) {
                                        times++;
                                        break;
                                    }

                                    usleep(100000);  // 100ms
                                }

                                if (XmodemServerReceiveSOH) {
                                    times = 0;
                                    break;
                                }

                                if (times >= 30) {
                                    times = 0;
                                    otactrl.UpDating = 0;
                                    printf("Write C 30 times over time!\n");
                                    break;
                                }
                            }

                            break;
                        } else {
                            if (time >= 60000) {
                                // CloseXModemServer();
                                XmodemServerEnd = 1;
                                CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                                CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                                printf("Without client connect over 60s, close xmodem tcp server!\n");
                                break;
                            }
                        }

                        usleep(100000);  // 100ms
                    }
                }

                if (prvotaCtrregval == 0x0001 && curotaCtrregval == 0x0008) {
                    // 暂未用到
                }

                if (prvotaCtrregval == 0x0008 && curotaCtrregval == 0x0080) {
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);
                    otactrl.OTAStart = 1;
                }

                // 0x0000 -> !0x0001
                if (prvotaCtrregval == 0 && step == 2 && curotaCtrregval != 0x0001) {
                    XmodemServerEnd = 1;
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                    printf("prvotaCtrregval == 0 && step == 2 && curotaCtrregval != 0x0001\n");
                }
            }

            if (XmodemServerEnd) {
                printf("XmodemServerEnd\n");
                // CloseXModemServer();
                XmodemServerEnd = 0;
            }

            prvotaCtrregval = curotaCtrregval;
        }

        if (curotaCtrregval == 0x0001) {
            if (prvmsgtimer == curmsgtimer) {
                times1++;
            } else {
                times1 = 0;
            }

            prvmsgtimer = curmsgtimer;

            if (times1 >= 400) {
                if (get_timeout_flag() == 1) {
                    otactrl.UpDating = 0;
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                }
                prvmsgtimer = curmsgtimer = 0;
                // CloseXModemServer();
                XmodemServerEnd = 0;
            }
        }

        usleep(10000);  // 10ms
    }
}




void CloseXModemServer(void)
{
    if(otasock1 > 0)
    {
        close(otasock1);
        close(otasock);
    }

    if(pLwIPTCPDataTaskHandle != NULL)
    {
        pthread_cancel(*pLwIPTCPDataTaskHandle);  // 
        free(pLwIPTCPDataTaskHandle);
        pLwIPTCPDataTaskHandle = NULL;
    }

    if(pLwIPTCPListenTaskHandle != NULL)
    {
        pthread_cancel(*pLwIPTCPListenTaskHandle);
        free(pLwIPTCPListenTaskHandle);
        pLwIPTCPListenTaskHandle = NULL;
    }

     if (OTAfil != NULL)
    {
        fclose(OTAfil);
        OTAfil = NULL;
    }

    prvmsgtimer = 0;
    curmsgtimer	= 0;
    clientConnected = 0;
    XmodemSendCFlag = 0;
    otasock1 = -1;
    otasock = -1;
    XmodemServerReceiveSOH = 0;
    otafileret = 30;
    XmodemServerEnd = 0;
}




signed char CheckXModemClient(void)
{
	if(clientConnected)
	{
		return 0;

	}
	else
	{
		return -1;
	}
}


unsigned char getClientConnected(void) {
    return clientConnected;
}

void setClientConnected(unsigned char value) {
    clientConnected = value;
}

unsigned char getXmodemSendCFlag(void) {
    return XmodemSendCFlag;
}

void setXmodemSendCFlag(unsigned char value) {
    XmodemSendCFlag = value;
}

unsigned char getXmodemServerReceiveSOH(void) {
    return XmodemServerReceiveSOH;
}

void setXmodemServerReceiveSOH(unsigned char value) {
    XmodemServerReceiveSOH = value;
}

unsigned char getXmodemServerReceiveEOT(void) {
    return XmodemServerReceiveEOT;
}

void setXmodemServerReceiveEOT(unsigned char value) {
    XmodemServerReceiveEOT = value;
}

unsigned char getXmodemServerReceiveFileEnd(void) {
    return XmodemServerReceiveFileEnd;
}

void setXmodemServerReceiveFileEnd(unsigned char value) {
    XmodemServerReceiveFileEnd = value;
}

unsigned char getXmodemServerEnd(void) {
    return XmodemServerEnd;
}

void setXmodemServerEnd(unsigned char value) {
    XmodemServerEnd = value;
}
