#define _GNU_SOURCE
#include "C_OTAStateMonitor.h"
#include "../GLB/G_AddressDefinition.h"
#include "../GLB/G_GloabalVariable.h"
#include "C_OTAListenMonitor.h"
#include "./CP/Modbus/C_ModbusServer.h"
#include "./CP/Xmodem/C_OTADataMonitor.h"
#include "./BMS/C_BMSAnalysis.h"
#include "C_OTAListenMonitor.h"
#include "log/log.h"
#include "main.h"

struct timespec AC_OTA_lastCheckTick;

unsigned short sblfilenumber = 0xFFFF; // SBL文件数量大小
unsigned short appfilenumber = 0xFFFF; // app文件数量大小
int SBl_index = 0;
int APP_index = 0;

int otasock = -1;
int otasock1 = -1;

volatile unsigned long prvmsgtimer = 0;

static int otafileret = -1; // 初始化为自定义值（-1 表示未初始化）

// *pLwIPTCPDataTaskHandle = NULL;
// *pLwIPTCPListenTaskHandle = NULL;

pthread_t *pLwIPTCPDataTaskHandle = NULL;
pthread_t *pLwIPTCPListenTaskHandle = NULL;

unsigned char clientConnected;
unsigned char XmodemSendCFlag;
unsigned char XmodemServerReceiveSOH;
unsigned char XmodemServerReceiveEOT;
unsigned char XmodemServerReceiveFileEnd = 0;
unsigned char XmodemServerEnd;

pthread_mutex_t task_mutex = PTHREAD_MUTEX_INITIALIZER;

FILE *OTAfil = NULL;

unsigned int OsIf_GetMilliseconds(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec * 1000 + now.tv_nsec / 1000000);
}

void *TcpServerExample(void *arg)
{
    unsigned int startTime = 0;
    unsigned short curotaCtrregval = 0xFFFF;
    unsigned short prvotaCtrregval = 0xFFFF;
    static unsigned char step = 0;
    static unsigned char times = 0;
    unsigned short times1 = 0;

    printf("TcpServerExample task!\n");
    signal(SIGPIPE, SIG_IGN);
    step = 1;
    while (1)
    {
        if (otactrl.UpDating == 1)
        {
            CP_set_TCU_PowerUpCmd(BMS_POWER_UPDATING);
            // CP_BMSAnalysis();
            // printf(" BMS_POWER_UPDATING!\n");
        }
        if (otactrl.OTAStart == 0 && (sblfilenumber != 0) && ((GetTimeDifference_ms(AC_OTA_lastCheckTick)) >= 30000))
        {
            SBl_index = 0;
            APP_index = 0;
            printf("Check OTA!\n");
        }

        int ret = CP_get_modbus_reg_val(OTACTRLREGADDR, &curotaCtrregval);
        ret = CP_get_modbus_reg_val(AC_SBL_OTAFILENUMBER, &sblfilenumber);
        ret = CP_get_modbus_reg_val(AC_APP_OTAFILENUMBER, &appfilenumber);
        // printf("curotaCtrregval %d sblfilenumber %d appfilenumber %d\n", curotaCtrregval, sblfilenumber, appfilenumber);

        if (ret < 0)
        {
            printf("ret %d get modbus reg val error\n", ret);
        }
        else
        {
            if ((curotaCtrregval != prvotaCtrregval) && (otactrl.OTAStart == 0))
            {
                printf("ota curotaCtrregval 0x%x prvotaCtrregval 0x%x\n", curotaCtrregval, prvotaCtrregval);

                if (curotaCtrregval == 0x0000)
                {
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                    CloseXModemServer();
                    // XmodemServerEnd = 0;
                    setXmodemServerEnd(0);
                    step = 2;
                }

                if (curotaCtrregval == 0x0001)
                {
                    // 临界区保护：确保任务创建不会出现竞态条件
                    printf("TcpServerExample task malloc!\n");
                    pthread_mutex_lock(&task_mutex); // 锁住临界区

                    if (pLwIPTCPListenTaskHandle == NULL)
                    {
                        pLwIPTCPListenTaskHandle = malloc(sizeof(pthread_t));
                        pLwIPTCPDataTaskHandle = malloc(sizeof(pthread_t));

                        if (pLwIPTCPListenTaskHandle == NULL || pLwIPTCPDataTaskHandle == NULL)
                        {
                            printf("TcpServerExample task malloc failed!\n");
                            while (1)
                            {
                                usleep(1000 * 10000);
                            }
                        }
                        // memset(pLwIPTCPListenTaskHandle, 0, sizeof(pthread_t));
                        // memset(pLwIPTCPDataTaskHandle, 0, sizeof(pthread_t));

                        *pLwIPTCPDataTaskHandle = NULL;
                        *pLwIPTCPListenTaskHandle = NULL;

                        // 创建监听任务
                        int ret = pthread_create(pLwIPTCPListenTaskHandle, NULL, Lwip_Listen_TASK, NULL);
                        if (ret != 0)
                        {
                            LOG("Failed to create Lwip_Listen xTaskCreate! thread : %s", strerror(ret));
                            sleep(1);
                        }
                        else
                        {
                            // CP_set_TCU_PowerUpCmd(BMS_POWER_UPDATING);
                            // CP_BMSAnalysis();
                            // LOG("Lwip_Listen xTaskCreate! thread created successfully.\r\n");
                            printf("success to create Lwip_Listen xTaskCreate! thread");
                        }

                        if (ret == 0)
                        {
                            CP_set_modbus_reg_val(OTASTATUSREGADDR, 1);
                        }
                    }

                    pthread_mutex_unlock(&task_mutex); // 解锁临界区
                    startTime = OsIf_GetMilliseconds();
                    while (1)
                    {
                        unsigned int currentTime = OsIf_GetMilliseconds();
                        ret = CheckXModemClient();
                        unsigned int time = currentTime - startTime;

                        if (ret == 0)
                        {
                            while (1)
                            {
                                char c = 'C';
                                printf("write tcp message C to client! otasock1:  %d!\n", otasock1);
                                signed char ret = write(otasock1, &c, 1);
                                printf("write tcp message C to client ret %d!\n", ret);
                                printf("otasock1 %d!\n", otasock1);

                                if (ret == 1)
                                {
                                    printf("write tcp message C to client!\n");
                                    XmodemSendCFlag = 1;
                                }

                                unsigned int RvTime = OsIf_GetMilliseconds();
                                while (1)
                                {
                                    unsigned int RvPassTime = OsIf_GetMilliseconds() - RvTime;

                                    if (XmodemServerReceiveSOH)
                                    {
                                        printf("Received SOH!\n");
                                        break;
                                    }

                                    if (RvPassTime >= 2000)
                                    {
                                        printf("Received SOH timeout!\n");
                                        times++;
                                        printf("times %d!\n", times);
                                        break;
                                    }

                                    usleep(100000); // 100ms
                                }
                                printf("XmodemServerReceiveSOH %d!\n", XmodemServerReceiveSOH);
                                if (XmodemServerReceiveSOH)
                                {
                                    times = 0;
                                    printf("Received SOH!\n");
                                    break;
                                }

                                if (times >= 30)
                                {
                                    times = 0;
                                    otactrl.UpDating = 0;
                                    printf("Write C 30 times over time!\n");
                                    LOG("Write C 30 times over time!");
                                    break;
                                }
                            }

                            break;
                        }
                        else
                        {
                            if (time >= 60000)
                            {
                                // CloseXModemServer();
                                // XmodemServerEnd = 1;
                                setXmodemServerEnd(1);
                                CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                                CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                                printf("Without client connect over 60s, close xmodem tcp server!\n");
                                LOG("Without client connect over 60s, close xmodem tcp server!");
                                break;
                            }
                        }

                        usleep(100 * 1000); // 100ms
                    }
                }

                if (prvotaCtrregval == 0x0001 && curotaCtrregval == 0x0008)
                {
                    // 暂未用到
                }

                if (prvotaCtrregval == 0x0008 && curotaCtrregval == 0x0080)
                {
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);
                    otactrl.OTAStart = 1;
                }

                // 0x0000 -> !0x0001
                if (prvotaCtrregval == 0 && step == 2 && curotaCtrregval != 0x0001)
                {
                    // XmodemServerEnd = 1;
                    setXmodemServerEnd(1);
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0);
                    printf("prvotaCtrregval == 0 && step == 2 && curotaCtrregval != 0x0001\n");
                }
            }
            // printf("getXmodemServerEnd() %d\r\n",getXmodemServerEnd());
            if (getXmodemServerEnd() == 1)
            {
                printf("XmodemServerEnd\n");
                CloseXModemServer();
                // XmodemServerEnd = 0;
                setXmodemServerEnd(0);
            }

            prvotaCtrregval = curotaCtrregval;
        }

        if (curotaCtrregval == 0x0001)
        {
            if (prvmsgtimer == curmsgtimer)
            {
                times1++;
            }
            else
            {
                times1 = 0;
            }

            prvmsgtimer = curmsgtimer;

            if (times1 >= 400)
            {
                if (get_timeout_flag() == 1)
                {
                    otactrl.UpDating = 0;
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, 0);
                }
                prvmsgtimer = curmsgtimer = 0;
                CloseXModemServer();
                // XmodemServerEnd = 0;
                setXmodemServerEnd(0);
            }
        }

        usleep(10 * 1000); // 10ms
    }
}

void CloseXModemServer(void)
{
    shutdown(otasock1, SHUT_RDWR);

    if (otasock1 > 0)
    {
        close(otasock1);
        otasock1 = -1;
    }

    if (otasock > 0)
    {
        close(otasock);
        otasock = -1;
    }
    // printf("CloseXModemServer\n");
    // if(pLwIPTCPDataTaskHandle != NULL)
    // {
    //     pthread_cancel(*pLwIPTCPDataTaskHandle);  //
    //     free(pLwIPTCPDataTaskHandle);
    //     pLwIPTCPDataTaskHandle = NULL;
    // }
    if (pLwIPTCPDataTaskHandle != NULL)
    {
        // 添加调试输出
        // printf("Before pthread_cancel: pLwIPTCPDataTaskHandle=%p, *pLwIPTCPDataTaskHandle=%lu\n",
        //        (void*)pLwIPTCPDataTaskHandle, (unsigned long)*pLwIPTCPDataTaskHandle);

        pthread_cancel(*pLwIPTCPDataTaskHandle);
        // printf("After pthread_cancel\n");
        // printf("Before pthread_join: pLwIPTCPDataTaskHandle=%p, *pLwIPTCPDataTaskHandle=%lu\n",
        //        (void*)pLwIPTCPDataTaskHandle, (unsigned long)*pLwIPTCPDataTaskHandle);

        pthread_join(*pLwIPTCPDataTaskHandle, NULL); // 等待线程回收资源

        free(pLwIPTCPDataTaskHandle);
        pLwIPTCPDataTaskHandle = NULL;
    }

    // if(pLwIPTCPListenTaskHandle != NULL)
    // {
    //     pthread_cancel(*pLwIPTCPListenTaskHandle);
    //     free(pLwIPTCPListenTaskHandle);
    //     pLwIPTCPListenTaskHandle = NULL;
    // }
    if (pLwIPTCPListenTaskHandle != NULL)
    {
        pthread_cancel(*pLwIPTCPListenTaskHandle);
        pthread_join(*pLwIPTCPListenTaskHandle, NULL); // 等待线程回收资源
        free(pLwIPTCPListenTaskHandle);
        pLwIPTCPListenTaskHandle = NULL;
    }

    if (OTAfil != NULL)
    {
        fclose(OTAfil);
        OTAfil = NULL;
    }

    prvmsgtimer = 0;
    curmsgtimer = 0;
    clientConnected = 0;
    XmodemSendCFlag = 0;
    otasock1 = -1;
    otasock = -1;
    XmodemServerReceiveSOH = 0;
    otafileret = 30;
    // XmodemServerEnd = 0;
    setXmodemServerEnd(0);
}

signed char CheckXModemClient(void)
{
    if (clientConnected)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

unsigned char getClientConnected(void)
{
    return clientConnected;
}

void setClientConnected(unsigned char value)
{
    clientConnected = value;
}

unsigned char getXmodemSendCFlag(void)
{
    return XmodemSendCFlag;
}

void setXmodemSendCFlag(unsigned char value)
{
    XmodemSendCFlag = value;
}

unsigned char getXmodemServerReceiveSOH(void)
{
    return XmodemServerReceiveSOH;
}

void setXmodemServerReceiveSOH(unsigned char value)
{
    XmodemServerReceiveSOH = value;
}

unsigned char getXmodemServerReceiveEOT(void)
{
    return XmodemServerReceiveEOT;
}

void setXmodemServerReceiveEOT(unsigned char value)
{
    XmodemServerReceiveEOT = value;
}

unsigned char getXmodemServerReceiveFileEnd(void)
{
    return XmodemServerReceiveFileEnd;
}

void setXmodemServerReceiveFileEnd(unsigned char value)
{
    XmodemServerReceiveFileEnd = value;
}

unsigned char getXmodemServerEnd(void)
{
    return XmodemServerEnd;
}

void setXmodemServerEnd(unsigned char value)
{
    XmodemServerEnd = value;
}
