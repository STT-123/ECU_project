#include "OTA_Upgrad_Task.h"
#include "C_OTAOtherUpdate.h"
#include "C_OTAUDSUpdate.h"
#include "C_OTAXCPUpdate.h"
#include "./GLB/G_GloabalVariable.h"
#include <pthread.h>
#include "C_OTAOtherUpdate.h"
#include"Drv_ZLog.h"
pthread_t OTAUpgrad_TASKHandle;
volatile unsigned int CurrentOTADeviceCanID = 0x1821FF10;
void *OTA_Upgrad_Task(void *arg);

void *OTA_Upgrad_Task(void *arg)
{
    OTAObject *pOTA = (OTAObject *)arg;
    CurrentOTADeviceCanID = ACPOTACANID;
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
            return NULL;
        }
    }
    while(1)
    {
          
        if(pOTA->deviceType == ACP || pOTA->deviceType == DCDC)
        {
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
                    continue;
                }
                else
                {
                    FinishACOtaAndCleanup(pOTA);
                    continue;
                }

            }
            else if(udsstatus.DeviceProgramOkFlag)
            {
                udsstatus.DeviceProgramOkFlag = 0;//需要添加
                printf("CAN ID 0x%x ACP OTA success!\r\n", pOTA->deviceID);
                if(pOTA->deviceType == AC)
                {
                    FinishACOtaAndCleanup(pOTA);
                }
    
            }


        }
////////////////////////////////////////
        if(pOTA->deviceType == BCU || pOTA->deviceType == BMU)
        {
            if (pOTA->deviceType == BCU)
            {
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
                   
                    while (ReOtaFlag < 3) {
                        CurrentOTADeviceCanID = (0x1821D << 12) | ((i + 1) << 8) | 0x10;
                        pOTA->deviceID = CurrentOTADeviceCanID;
                        pOTA->OTAStart = 1;
                        xcpstatus.ErrorReg = 0;
                
                        printf("Start OTA try %d, CAN ID 0x%x BMU %d\r\n", ReOtaFlag + 1, CurrentOTADeviceCanID, i);
                
                        CP_XCP_OTA(pOTA);
                
                        if (xcpstatus.ErrorReg == 0 && pOTA->OTAStart == 0 && xcpstatus.DeviceProgramOkFlag) {
                            xcpstatus.DeviceProgramOkFlag = 0;
                            printf("CAN ID 0x%x BMU OTA success!\r\n", pOTA->deviceID);
                            break;
                        } else {
                            ReOtaFlag++;
                            printf("CAN ID 0x%x BMU OTA failed, retry count: %d\r\n", pOTA->deviceID, ReOtaFlag);
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
        ret = pthread_create(&OTAUpgrad_TASKHandle, NULL,OTA_Upgrad_Task , NULL);
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