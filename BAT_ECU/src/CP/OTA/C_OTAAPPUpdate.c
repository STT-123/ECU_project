#include "C_OTAAPPUpdate.h"
#include "../GLB/G_GloabalVariable.h"
#include "./DRV/LOG/Drv_ZLog.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./GLB/G_AddressDefinition.h"
#include "C_OTADataMonitor.h"
#define APP_PATH  "/usr/xcharge"  

ECUStatus ecustatus;
void CP_ECU_OTA(OTAObject *pOTA)
{
	printf("CP_ECU_OTA start!,pOTA->OTAStart:%d\r\n",pOTA->OTAStart);
	if (!pOTA->OTAStart) return;
	memset(&ecustatus, 0, sizeof(ECUStatus));
	printf("pOTA->deviceType : %d \r\n", pOTA->deviceType);
	printf("can id 0x%d device ota start!\r\n", pOTA->deviceID);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);//0124.升级状态
	if(pOTA->deviceID == 0 && pOTA->deviceType == ECU )
	{
		char cmd[512];
		if(ecustatus.ErrorReg == 0)
		{
			memset(cmd, 0, sizeof(cmd));
			char otafilenamestr1[OTAFILENAMEMAXLENGTH + 64] = {'\0'};
			snprintf(otafilenamestr1, sizeof(otafilenamestr1), "%s/%s", USB_MOUNT_POINT, pOTA->OTAFilename);
            printf("otafilenamestr1 %s\r\n", otafilenamestr1);
			zlog_info(debug_out,"otafilenamestr1 %s\r\n", otafilenamestr1);


			if (access(otafilenamestr1, F_OK) != 0) {
			printf("OTA file does not exist: %s\n", otafilenamestr1);
			ecustatus.ErrorReg |= 1 << 2;
			return;
			}


			//解压

			// snprintf(cmd, sizeof(cmd), "cd %s && tar xvjf %s", USB_MOUNT_POINT, pOTA->OTAFilename);
			snprintf(cmd, sizeof(cmd), "cd %s && tar --no-same-owner --touch -xvjf %s", USB_MOUNT_POINT, pOTA->OTAFilename);
			// snprintf(cmd, sizeof(cmd), "cd %s && bunzip2 %s && tar xvf %s.tar", USB_MOUNT_POINT, pOTA->OTAFilename, basename(pOTA->OTAFilename));
			// snprintf(cmd, sizeof(cmd), "cd %s && unzip -o %s", USB_MOUNT_POINT, pOTA->OTAFilename);
			printf("cmd: %s\n", cmd);
			// snprintf(cmd, sizeof(cmd), "cd %s && bunzip2 %s", USB_MOUNT_POINT, pOTA->OTAFilename);
			int ret = system(cmd);
			if (ret == 0) {
				printf("Decompression successful.\n");
				zlog_info(debug_out,"Decompression successful.\n");
			}
			else 
			{
			printf("Decompression failed.\n");
			zlog_info(debug_out,"Decompression failed.\n");
			ecustatus.ErrorReg  |= 1<<1;			
			}


		}

		if(ecustatus.ErrorReg == 0)
		{
			memset(cmd, 0, sizeof(cmd));
			snprintf(cmd, sizeof(cmd), "cp \"%s/bat_ecu\" \"%s\"", USB_MOUNT_POINT, APP_PATH);
			int ret = system(cmd);
			if (ret == 0) {
				printf("Copy successful.\n");
				zlog_info(debug_out,"Copy successful.\n");
			} 
			else 
			{
				printf("Copy failed.\n");
				zlog_info(debug_out,"Copy failed.\n");
				ecustatus.ErrorReg  |= 1<<2;			
			}


		}

		if(ecustatus.ErrorReg == 0)
		{
			memset(cmd, 0, sizeof(cmd));
			snprintf(cmd, sizeof(cmd), "chmod 777 \"%s/bat_ecu\"", APP_PATH);
			int ret = system(cmd);
			if (ret == 0) {
				FinshhECUOtaAndCleanup(pOTA);
				printf("Permission settings have been successfully configured.\n");
				zlog_info(debug_out,"Permission settings have been successfully configured.\n");

				system("sync");
				system("reboot");
			} 
			else 
			{
				printf("Permission setting failed.\n");
				zlog_info(debug_out,"Permission setting failed.\n");
				ecustatus.ErrorReg  |= 1<<3;			
			}

		}



		if(ecustatus.ErrorReg != 0)
		{
			printf("can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, ecustatus.ErrorReg);
			zlog_info(debug_out,"can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, ecustatus.ErrorReg);
			CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
		}
		pOTA->OTAStart =0;
	}
}


void FinshhECUOtaAndCleanup(OTAObject* pOTA)
{
    pOTA->deviceType = 0;//停止升级
    pOTA->OTAStart = 0;
	delete_files_with_prefix(USB_MOUNT_POINT, "XC");//  这个要删除升级文件，判断ecustatus状态，成功或者失败删除
	delete_files_with_prefix(USB_MOUNT_POINT, "md5");// 
	otactrl.UpDating = 0;//1130(升级结束)
	ecustatus.CANStartOTA = 0;
	// set_charger_cmd(BMS_POWER_DEFAULT);
    CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAIDLE);
}