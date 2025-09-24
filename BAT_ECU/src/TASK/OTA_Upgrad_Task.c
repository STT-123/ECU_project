#include "OTA_Upgrad_Task.h"
#include "./CP/OTA/C_OTAOtherUpdate.h"
#include "./CP/OTA/C_OTAXCPUpdate.h"
#include "./CP/OTA/C_OTAUDSUpdate.h"
#include "./GLB/G_GloabalVariable.h"
#include <pthread.h>
#include "C_OTAOtherUpdate.h"
#include"Drv_ZLog.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./CP/OTA/C_OTAAPPUpdate.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./CP/Xmodem/C_OTAStateMonitor.h"
#include "./GLB/G_AddressDefinition.h"
#include "main.h"
pthread_t OTAUpgrad_TASKHandle;
volatile unsigned int CurrentOTADeviceCanID = 0x1821FF10;
void *OTA_Upgrad_Task(void *arg);

void *OTA_Upgrad_Task(void *arg)
{
    OTAObject *pOTA = (OTAObject *)arg;
    CurrentOTADeviceCanID = ACPOTACANID;
    unsigned char ECUOtaFlag = 0;
    unsigned char ACPOtaFlag = 0;
    unsigned char DCDCOtaFlag = 0;
    unsigned char ACOtaFlag = 0;
    unsigned char BCUOtaFlag = 0;
    unsigned char BMUOtaFlag = 0;
    unsigned char ReOtaFlag = 0;
    //预留初始化部分
    if (pOTA == NULL) {
        printf("Warning: pOTA is NULL, using default settings.\r\n");

        pOTA = malloc(sizeof(OTAObject));
        if (pOTA == NULL) {
            printf("Error: Failed to allocate memory for default OTAObject.\r\n");
            zlog_info(debug_out, "Error: Failed to allocate memory for default OTAObject.\r\n");
            return NULL;
        }
    }
    while(1)
    {


        if(pOTA->deviceType == ECU)
        {
            printf("pOTA->deviceType == ECU : %u\r\n",pOTA->deviceType);
            CP_ECU_OTA(pOTA);
            if(ecustatus.ErrorReg !=0 && pOTA->OTAStart == 0)
            {

                ECUOtaFlag ++;
                if(ECUOtaFlag < 3)
                {

                    CurrentOTADeviceCanID = 0;
                    pOTA->deviceID = 0;
                    pOTA->OTAStart = 1;
                    ecustatus.ErrorReg = 0;
                    printf("ecu OTA failed, error ACPOtaFlag count:  %d\r\n", ECUOtaFlag);
                    zlog_info(debug_out, "ECU OTA failed, error ECUOtaFlag count:  %d\r\n", ECUOtaFlag);
                    continue;
                }
                else
                {
                    FinshhECUOtaAndCleanup(pOTA);
                    continue;
                }

            }
            else if(ecustatus.DeviceProgramOkFlag)
            {
                udsstatus.DeviceProgramOkFlag = 0;//需要添加
                printf("CAN ID 0x%x ECU OTA success!\r\n", pOTA->deviceID);
                zlog_info(debug_out, "CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                if(pOTA->deviceType == ECU)
                {
                    FinshhECUOtaAndCleanup(pOTA);
                }
    
            }


        }

          
        // printf("pOTA->deviceType == BCU : %u\r\n",pOTA->deviceType);
        else if(pOTA->deviceType == ACP || pOTA->deviceType == DCDC)
        {

            usleep(1000*1000);
            CP_ACPDCDC_OTA(pOTA);

            if(independentStatus.ErrorReg !=0 && pOTA->OTAStart == 0)
            {
                if(pOTA->deviceType == ACP)
                {
                    ACPOtaFlag ++;
                    if(ACPOtaFlag < 3)
                    {
    
                        CurrentOTADeviceCanID = ACPOTACANID;
                        pOTA->deviceID = ACPOTACANID;
                        pOTA->OTAStart = 1;
                        independentStatus.ErrorReg = 0;
                        printf("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACPOtaFlag);
                        zlog_info(debug_out, "ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACPOtaFlag);
                        continue;
                    }

                    else
                    {
                        FinishACPOtaAndCleanup(pOTA);
                        continue;
                    }
                }
                else if(pOTA->deviceType == DCDC)
                {
                    DCDCOtaFlag ++;
                    if(DCDCOtaFlag < 3)
                    {
    
                        CurrentOTADeviceCanID = DCDCOTACANID;
                        pOTA->deviceID = DCDCOTACANID;
                        pOTA->OTAStart = 1;
                        independentStatus.ErrorReg = 0;
                        printf("DCDC OTA failed, error ACPOtaFlag count:  %d\r\n", DCDCOtaFlag);
                        zlog_info(debug_out, "DCDC OTA failed, error ACPOtaFlag count:  %d\r\n", DCDCOtaFlag);
                        continue;
                    }

                    else
                    {
                        FinishDCDCOtaAndCleanup(pOTA);
                        continue;
                    }

                }

            }
            else if(independentStatus.DeviceProgramOkFlag)
            {
                independentStatus.DeviceProgramOkFlag = 0;//需要添加
                printf("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                zlog_info(debug_out, "CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                if(pOTA->deviceType == ACP)
                {
                    FinishACPOtaAndCleanup(pOTA);
                }
                else if(pOTA->deviceType == DCDC)
                {
                    FinishDCDCOtaAndCleanup(pOTA);
                }
    
            }
           

        }

////////////////////////////////////////////////
        if(pOTA->deviceType == AC)
        {
            // usleep(1000*1000);
            CP_UDS_OTA(pOTA);
            if(udsstatus.ErrorReg !=0 && pOTA->OTAStart == 0)
            {

                ACOtaFlag ++;
                if(ACOtaFlag < 3)
                {

                    CurrentOTADeviceCanID = ACOTACANID;
                    pOTA->deviceID = ACPOTACANID;
                    pOTA->OTAStart = 1;
                    udsstatus.ErrorReg = 0;
                    printf("ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACOtaFlag);
                    zlog_info(debug_out, "ACP OTA failed, error ACPOtaFlag count:  %d\r\n", ACOtaFlag);
                    continue;
                }
                else
                {
                    CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
                    FinishACOtaAndCleanup(pOTA);
                    continue;
                }

            }
            else if(udsstatus.DeviceProgramOkFlag)
            {
                udsstatus.DeviceProgramOkFlag = 0;//需要添加
                printf("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                zlog_info(debug_out, "CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                if(pOTA->deviceType == AC)
                {
                    FinishACOtaAndCleanup(pOTA);
                }
    
            }


        }
////////////////////////////////////////
        if(pOTA->deviceType == BCU || pOTA->deviceType == BMU)
        {
            printf("BCU or BMU OTA start!\r\n");
            printf("pOTA->deviceType == BCU : %u\r\n",pOTA->deviceType);
            if (pOTA->deviceType == BCU)
            {
                printf("BCU OTA start! pOTA_start\r\n",pOTA->OTAStart);
                for (int i = 0; i < 300; i++)
                {
                    CP_set_OTA_XCPConnect(255); 
                    CP_BMSAnalysis();        
                    usleep(2000);
                    printf("BCU OTA start! i : %d\r\n",i);
                }
                usleep(1000*1000);
                CP_XCP_OTA(pOTA);
                if(xcpstatus.ErrorReg !=0 && pOTA->OTAStart == 0)
                {
                    BCUOtaFlag ++;
                    if(BCUOtaFlag < 3)
                    {
    
                        CurrentOTADeviceCanID = BCUOTACANID;
                        pOTA->deviceID = BCUOTACANID;
                        pOTA->OTAStart = 1;
                        xcpstatus.ErrorReg = 0;
                        printf("ACP OTA failed, error BCUOtaFlag count:  %d\r\n", BCUOtaFlag);
                        zlog_info(debug_out, "ACP OTA failed, error BCUOtaFlag count:  %d\r\n", BCUOtaFlag);
                        continue;
                    }
                    else
                    {
                        FinshhBCUBMUOtaAndCleanup(pOTA);
                        continue;
                    }
                    
                }
                else if(xcpstatus.DeviceProgramOkFlag) //需要添加
                {
                    xcpstatus.DeviceProgramOkFlag = 0;//需要添加
                    printf("CAN ID 0x%x BCU OTA success!\r\n", pOTA->deviceID);
                    zlog_info(debug_out, "CAN ID 0x%x BCU OTA success!\r\n",pOTA->deviceID);
                    if(pOTA->deviceType == BCU)
                    {
                        FinshhBCUBMUOtaAndCleanup(pOTA);
                    }
                }
            }
            else if(pOTA->deviceType == BMU)
            {
                for(int i = 0; i < BMUMAXNUM; i++)
                {
                    printf("BMU OTA start! i : %d\r\n",i);
                   printf("ReOtaFlag :%d\r\n",ReOtaFlag);
                   ReOtaFlag = 0;
                    while (ReOtaFlag < 3) {
                        CurrentOTADeviceCanID = (0x1821D << 12) | ((i + 1) << 8) | 0x10;
                        pOTA->deviceID = CurrentOTADeviceCanID;
                        printf("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);
                        printf("pOTA->deviceID == BMU : %x\r\n",pOTA->deviceID);
                        pOTA->OTAStart = 1;
                        xcpstatus.ErrorReg = 0;
                
                        // printf("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);
                
                        CP_XCP_OTA(pOTA);
                        
                        // printf("xcpstatus.ErrorReg  %d, pOTA->OTAStart %d, xcpstatus.DeviceProgramOkFlag %d\r\n",xcpstatus.ErrorReg, pOTA->OTAStart,xcpstatus.DeviceProgramOkFlag);
                        if (xcpstatus.ErrorReg == 0 && pOTA->OTAStart == 0 && xcpstatus.DeviceProgramOkFlag) {
                            xcpstatus.DeviceProgramOkFlag = 0;
                            printf("CAN ID 0x%x BMU OTA success!\r\n", pOTA->deviceID);
                            zlog_info(debug_out, "CAN ID 0x%x BMU OTA success!\r\n",pOTA->deviceID);
                            break;
                        } else { 
                            // break;
                            ReOtaFlag++;
                            printf("CAN ID 0x%x BMU OTA failed, retry count: %d\r\n", pOTA->deviceID, ReOtaFlag);
                            zlog_info(debug_out, "CAN ID 0x%x BMU OTA failed, retry count: %d\r\n",pOTA->deviceID, ReOtaFlag);
                        }
                    }


                }
                FinshhBCUBMUOtaAndCleanup(pOTA);
                
            }
        }


        usleep(10*1000);
    }

}


void OTAUpgradTaskCreate(void)
{
    int ret;
    do {
        ret = pthread_create(&OTAUpgrad_TASKHandle, NULL,OTA_Upgrad_Task , &otactrl);
        if (ret != 0) {
            zlog_info(debug_out,"Failed to create SerialLedTask thread : %s",strerror(ret));
            sleep(1); 
        }
        else
        {
            zlog_info(debug_out,"SerialLedTask thread created successfully.\r\n");
        }
    } while (ret != 0);
}