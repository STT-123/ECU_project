#include "OTA_Upgrad_Task.h"
#include "./CP/OTA/C_OTAOtherUpdate.h"
#include "./CP/OTA/C_OTAXCPUpdate.h"
#include "./CP/OTA/C_OTAUDSUpdate.h"
#include "./GLB/G_GloabalVariable.h"
#include <pthread.h>
#include "C_OTAOtherUpdate.h"
#include "log/log.h"
#include "log/log.h"
#include "./CP/OTA/C_OTAAPPUpdate.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./CP/Xmodem/C_OTAStateMonitor.h"
#include "./GLB/G_AddressDefinition.h"
#include "main.h"
#include "./OCPP/C_OCPPAPPUpdate.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"

pthread_t OTAUpgrad_TASKHandle;
volatile unsigned int CurrentOTADeviceCanID = 0x1821FF10;

void *OTA_Upgrad_Task(void *arg)
{
    OTAObject *pOTA = (OTAObject *)arg;
    CurrentOTADeviceCanID = ACPOTACANID;
    unsigned char ECUOtaFlag = 0;
    unsigned char ACPOtaFlag = 0;
    unsigned char DCDCOtaFlag = 0;
    unsigned char ACOtaFlag = 0;
    unsigned char BCUOtaFlag = 0;
    unsigned char ReOtaFlag = 0;
    char matched_filename[256] = {0};
    // 预留初始化部分
    if (pOTA == NULL)
    {
        printf("Warning: pOTA is NULL, using default settings.\r\n");

        pOTA = malloc(sizeof(OTAObject));
        if (pOTA == NULL)
        {
            printf("Error: Failed to allocate memory for default OTAObject.\r\n");
            LOG("Error: Failed to allocate memory for default OTAObject.\r\n");
            return NULL;
        }
    }
#if 0
    sleep(20);
    static CAN_MESSAGE canmsg;
    int err;
    int xstatis = 0;
    strcpy(pOTA->OTAFilename, "XC_BCU_V525.bin");
    pOTA->deviceType = BCU;
    pOTA->deviceID = BCUOTACANID;
    pOTA->OTAStart = 1;
    printf("pOTA->OTAFilename : %s\r\n",pOTA->OTAFilename);
    printf("pOTA->deviceID: %u\r\n",pOTA->deviceID);
#endif
    while (1)
    {
        if(1 == pOTA->OTAStart)
        {
            CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);//0124.升级状态
            if (pOTA->deviceType == ECU)
            {
                printf("pOTA->deviceType == ECU : %u\r\n", pOTA->deviceType);
                CP_ECU_OTA(pOTA);
                if (ecustatus.ErrorReg != 0 && pOTA->OTAStart == 0)
                {

                    ECUOtaFlag++;
                    if (ECUOtaFlag < 3)
                    {

                        CurrentOTADeviceCanID = 0;
                        pOTA->deviceID = 0;
                        pOTA->OTAStart = 1;
                        ecustatus.ErrorReg = 0;
                        printf("ecu OTA failed, error ACPOtaFlag count:  %d\r\n", ECUOtaFlag);
                        LOG("ECU OTA failed, error ECUOtaFlag count:  %d\r\n", ECUOtaFlag);
                        continue;
                    }
                    else
                    {
                        FinshhECUOtaAndCleanup(pOTA);
                        continue;
                    }
                }
                else if (ecustatus.DeviceProgramOkFlag)
                {
                    udsstatus.DeviceProgramOkFlag = 0; // 需要添加
                    printf("CAN ID 0x%x ECU OTA success!\r\n", pOTA->deviceID);
                    LOG("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                    if (pOTA->deviceType == ECU)
                    {
                        FinshhECUOtaAndCleanup(pOTA);
                    }
                }
            }
            else if (pOTA->deviceType == ACP || pOTA->deviceType == DCDC)
            {

                usleep(1000 * 1000);
                CP_ACPDCDC_OTA(pOTA);

                if (independentStatus.ErrorReg != 0 && pOTA->OTAStart == 0)
                {
                    if (pOTA->deviceType == ACP)
                    {
                        ACPOtaFlag++;
                        if (ACPOtaFlag < 3)
                        {

                            CurrentOTADeviceCanID = ACPOTACANID;
                            pOTA->deviceID = ACPOTACANID;
                            pOTA->OTAStart = 1;
                            independentStatus.ErrorReg = 0;
                            printf("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACPOtaFlag);
                            LOG("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACPOtaFlag);
                            continue;
                        }

                        else
                        {
                            FinishACPOtaAndCleanup(pOTA);
                            continue;
                        }
                    }
                    else if (pOTA->deviceType == DCDC)
                    {
                        DCDCOtaFlag++;
                        if (DCDCOtaFlag < 3)
                        {

                            CurrentOTADeviceCanID = DCDCOTACANID;
                            pOTA->deviceID = DCDCOTACANID;
                            pOTA->OTAStart = 1;
                            independentStatus.ErrorReg = 0;
                            printf("DCDC OTA failed, error ACPOtaFlag count:  %d\r\n", DCDCOtaFlag);
                            LOG("DCDC OTA failed, error ACPOtaFlag count:  %d\r\n", DCDCOtaFlag);
                            continue;
                        }

                        else
                        {
                            FinishDCDCOtaAndCleanup(pOTA);
                            continue;
                        }
                    }
                }
                else if (independentStatus.DeviceProgramOkFlag)
                {
                    independentStatus.DeviceProgramOkFlag = 0; // 需要添加
                    printf("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                    LOG("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                    if (pOTA->deviceType == ACP)
                    {
                        FinishACPOtaAndCleanup(pOTA);
                    }
                    else if (pOTA->deviceType == DCDC)
                    {
                        FinishDCDCOtaAndCleanup(pOTA);
                    }
                }
            }
            else if (pOTA->deviceType == AC)
            {
                // usleep(1000*1000);
                CP_UDS_OTA(pOTA);
                if (udsstatus.ErrorReg != 0 && pOTA->OTAStart == 0)
                {

                    ACOtaFlag++;
                    if (ACOtaFlag < 3)
                    {

                        CurrentOTADeviceCanID = ACOTACANID;
                        pOTA->deviceID = ACPOTACANID;
                        pOTA->OTAStart = 1;
                        udsstatus.ErrorReg = 0;
                        printf("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACOtaFlag);
                        LOG("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACOtaFlag);
                        continue;
                    }
                    else
                    {
                        CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
                        FinishACOtaAndCleanup(pOTA);
                        continue;
                    }
                }
                else if (udsstatus.DeviceProgramOkFlag)
                {
                    udsstatus.DeviceProgramOkFlag = 0; // 需要添加
                    printf("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                    LOG("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                    if (pOTA->deviceType == AC)
                    {
                        FinishACOtaAndCleanup(pOTA);
                    }
                }
            }
            else if (pOTA->deviceType == BCU || pOTA->deviceType == BMU)
            {
                printf("BCU or BMU OTA start!\r\n");
                printf("pOTA->deviceType == BCU : %u\r\n", pOTA->deviceType);
                if (pOTA->deviceType == BCU)
                {
                    for (int i = 0; i < 10; i++){
                        CP_set_OTA_XCPConnect(255);//设置跳转到BOOT的条件,OTA_XCPConnect为0xFF才会跳转到BOOT
                        CP_BMSAnalysis();
                        usleep(2000);
                    }

                    // for (int i = 0; i < 100; i++){
                    //     xstatis = queue_pend(&Queue_Can0RevData, &canmsg,&err);
                    //     printf("xstatis = %d\r\n",xstatis);
                    // }
                    // sleep(3);
                    
                    usleep(1000 * 1000);
                    CP_XCP_OTA(pOTA);
                }
                else if (pOTA->deviceType == BMU)
                {
                    for (int i = 0; i < BMUMAXNUM; i++)
                    {
                        printf("BMU OTA start! i : %d\r\n", i);
                        printf("ReOtaFlag :%d\r\n", ReOtaFlag);
                        ReOtaFlag = 0;
                        while (ReOtaFlag < 3)
                        {
                            CurrentOTADeviceCanID = (0x1821D << 12) | ((i + 1) << 8) | 0x10;
                            pOTA->deviceID = CurrentOTADeviceCanID;
                            printf("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);
                            printf("pOTA->deviceID == BMU : %x\r\n", pOTA->deviceID);
                            pOTA->OTAStart = 1;
                            xcpstatus.ErrorReg = 0;

                            // printf("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);

                            CP_XCP_OTA(pOTA);

                            // printf("xcpstatus.ErrorReg  %d, pOTA->OTAStart %d, xcpstatus.DeviceProgramOkFlag %d\r\n",xcpstatus.ErrorReg, pOTA->OTAStart,xcpstatus.DeviceProgramOkFlag);
                            if (xcpstatus.ErrorReg == 0 && pOTA->OTAStart == 0 && xcpstatus.DeviceProgramOkFlag)
                            {
                                xcpstatus.DeviceProgramOkFlag = 0;
                                printf("CAN ID 0x%x BMU OTA success!\r\n", pOTA->deviceID);
                                LOG("CAN ID 0x%x BMU OTA success!\r\n", pOTA->deviceID);
                                break;
                            }
                            else
                            {
                                // break;
                                ReOtaFlag++;
                                printf("CAN ID 0x%x BMU OTA failed, retry count: %d\r\n", pOTA->deviceID, ReOtaFlag);
                                LOG("CAN ID 0x%x BMU OTA failed, retry count: %d\r\n", pOTA->deviceID, ReOtaFlag);
                            }
                        }
                    }

                }
                FinshhBCUBMUOtaAndCleanup(pOTA);
            }
        }
        usleep(10 * 1000);
    }
}

void OTAUpgradTaskCreate(void)
{
    int ret;
    do
    {
        ret = pthread_create(&OTAUpgrad_TASKHandle, NULL, OTA_Upgrad_Task, &otactrl);
        if (ret != 0)
        {
            LOG("Failed to create SerialLedTask thread : %s", strerror(ret));
            sleep(1);
        }
        else
        {
            LOG("SerialLedTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}