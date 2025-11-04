#include "OTA_Upgrad_Task.h"
#include "./CP/OTA/C_OTAOtherUpdate.h"
#include "./CP/OTA/C_OTAXCPUpdate.h"
#include "./CP/OTA/C_OTAUDSUpdate.h"
#include "./GLB/G_GloabalVariable.h"
#include <pthread.h>
#include "C_OTAOtherUpdate.h"
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
    strcpy(pOTA->OTAFilename, "XC_BMU_V302.bin");
    pOTA->deviceType = BMU;
    // pOTA->deviceID = BCUOTACANID;
    pOTA->deviceID = 0x1821FF10;//BMU
    // pOTA->deviceID = 0;//ECU
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
                LOG("pOTA->deviceType == ECU : %u\r\n", pOTA->deviceType);
                CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0); // 0124


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
                        LOG("ECU OTA failed, error ECUOtaFlag count:  %d\r\n", ECUOtaFlag);
                        continue;
                    }
                    else
                    {
                        LOG(" ECUOtaFlag > 3 \r\n");
                    }
                }
                else if (ecustatus.DeviceProgramOkFlag)
                {
                    LOG("errot\r\n");
                }

                CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASUCCESS);
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
                    usleep(1000 * 1000);
                    CP_XCP_OTA(pOTA);
                }
                else if (pOTA->deviceType == BMU)
                {
                    unsigned int total_steps = BMUMAXNUM;  // 0到14共15次
                    unsigned int start_percent = 7;
                    unsigned int end_percent = 100;
                    //
                    for (int i = 0; i < BMUMAXNUM; i++)
                    {
                        LOG("BMU OTA start! i : ,ReOtaFlag = %d %d\r\n", i,ReOtaFlag);
                        ReOtaFlag = 0;
                        while (ReOtaFlag < 3)
                        {
                            CurrentOTADeviceCanID = (0x1821D << 12) | ((i + 1) << 8) | 0x10;
                            pOTA->deviceID = CurrentOTADeviceCanID;
                            LOG("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);
                            LOG("pOTA->deviceID == BMU : %x\r\n", pOTA->deviceID);
                            pOTA->OTAStart = 1;
                            xcpstatus.ErrorReg = 0;                           
                            LOG("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);

                            CP_XCP_OTA(pOTA);

                            // printf("xcpstatus.ErrorReg  %d, pOTA->OTAStart %d, xcpstatus.DeviceProgramOkFlag %d\r\n",xcpstatus.ErrorReg, pOTA->OTAStart,xcpstatus.DeviceProgramOkFlag);
                            if (xcpstatus.ErrorReg == 0 && pOTA->OTAStart == 0 && xcpstatus.DeviceProgramOkFlag)
                            {
                                xcpstatus.DeviceProgramOkFlag = 0;
                                LOG("CAN ID 0x%x BMU OTA success!\r\n", pOTA->deviceID);
                                break;
                            }
                            else
                            {
                                ReOtaFlag++;
                                LOG("CAN ID 0x%x BMU OTA failed, retry count: %d\r\n", pOTA->deviceID, ReOtaFlag);
                            }
                        }
                        sleep(2);
                        //这段代码是，一共15个BMU，每ota完一个增加7%的进度
                        unsigned int percentage = start_percent + (end_percent - start_percent) * i / (total_steps - 1);
                        CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, percentage); // 0124, upgrade progress,BCU直接写升级进度，BMU 由于有15个，不在这里写进度
                        if(percentage == 100){
                            CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASUCCESS);
                        }
                        LOG("STEP %2d: %3d%%\n", i, percentage);
                    }

                }         
            }
            FinshhBCUBMUOtaAndCleanup(pOTA);
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