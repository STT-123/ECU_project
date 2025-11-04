#include "C_OTAAPPUpdate.h"
#include "../GLB/G_GloabalVariable.h"
#include "log/log.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "./GLB/G_AddressDefinition.h"
#include "C_OTADataMonitor.h"
#define APP_PATH  "/usr/xcharge"  

ECUStatus ecustatus;
void CP_ECU_OTA(OTAObject *pOTA)
{
	LOG("CP_ECU_OTA start!, pOTA->OTAStart:%d\r\n", pOTA->OTAStart);
    if (!pOTA->OTAStart) return;
    
    memset(&ecustatus, 0, sizeof(ECUStatus));
    LOG("pOTA->deviceType : %d \r\n", pOTA->deviceType);
    LOG("can id 0x%x device ota start!\r\n", pOTA->deviceID);
    CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);
    
    if(pOTA->deviceID == 0 && pOTA->deviceType == ECU)
    {
        char cmd[512];
        CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 10); // 0124
		// 步骤1: 检查OTA文件是否存在
		if(ecustatus.ErrorReg == 0)
		{
			char otafilenamestr1[OTAFILENAMEMAXLENGTH + 64] = {'\0'};
			snprintf(otafilenamestr1, sizeof(otafilenamestr1), "%s/%s", USB_MOUNT_POINT, pOTA->OTAFilename);
			LOG("OTA file path: %s\r\n", otafilenamestr1);

			// 检查文件是否存在
			if (access(otafilenamestr1, F_OK) != 0) {
				printf("OTA file does not exist: %s\n", otafilenamestr1);
				ecustatus.ErrorReg |= 1 << 2;
				return;
			}

			// 使用C语言FILE操作验证文件（不依赖shell的file命令）
			if (!verify_bin_file(otafilenamestr1)) {
				printf("File verification failed: %s\n", pOTA->OTAFilename);
				ecustatus.ErrorReg |= 1 << 4;
				return;
			}
			
			LOG("ECU bin file verified: %s\n", pOTA->OTAFilename);
		}

		CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 40); // 0124
		// 步骤2: 备份原有程序（可选但推荐）
		// 更安全的更新方式
		if(ecustatus.ErrorReg == 0)
		{
			memset(cmd, 0, sizeof(cmd));
			
			// 方法1: 原子替换
			snprintf(cmd, sizeof(cmd), "cp \"%s/%s\" \"%s/.bat_ecu.tmp\" && mv \"%s/.bat_ecu.tmp\" \"%s/bat_ecu\"", 
					USB_MOUNT_POINT, pOTA->OTAFilename, APP_PATH, APP_PATH, APP_PATH);	
			LOG("Copy command: %s\n", cmd);
			
			int ret = system(cmd);
			if (ret == 0) {
				LOG("Program update successful.\n");
			} else {
				LOG("Program update failed.\n");
				ecustatus.ErrorReg |= 1 << 2;
			}
		}
        // 步骤3: 复制新的可执行文件

		CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 60); // 0124
        if(ecustatus.ErrorReg == 0)
        {
            memset(cmd, 0, sizeof(cmd));
            // 将.bin文件复制为目标可执行文件（去掉.bin后缀）
            snprintf(cmd, sizeof(cmd), "cp \"%s/%s\" \"%s/bat_ecu\"", 
                     USB_MOUNT_POINT, pOTA->OTAFilename, APP_PATH);
            LOG("Copy command: %s\n", cmd);
            
            int ret = system(cmd);
            if (ret == 0) {
                LOG("Program copy successful.\n");
            } 
            else 
            {
                LOG("Program copy failed.\n");
                ecustatus.ErrorReg |= 1 << 2;
            }
        }

		// 步骤4: 验证复制后的文件 - 移除file命令依赖
		CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 80); // 0124
		if(ecustatus.ErrorReg == 0)
		{
			// 使用C语言方式验证，而不是system("file ...")
			if (!verify_bin_file("/usr/xcharge/bat_ecu")) {
				LOG("Copied file verification failed\n");
				ecustatus.ErrorReg |= 1 << 4;
			} else {
				LOG("Copied file verification successful\n");
			}
		}

        // 步骤5: 设置执行权限并重启
        if(ecustatus.ErrorReg == 0)
        {
            memset(cmd, 0, sizeof(cmd));
            snprintf(cmd, sizeof(cmd), "chmod 755 \"%s/bat_ecu\"", APP_PATH);
            int ret = system(cmd);
            if (ret == 0) {
                LOG("Permission settings successful.\n");
				CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 0); // 0124
                // 完成OTA清理工作
                FinshhECUOtaAndCleanup(pOTA);
                
                // 确保数据写入磁盘并重启
                LOG("Syncing filesystem and rebooting...\n");
                system("sync");

                sleep(5);//5s后重启
                system("reboot");
            } 
            else 
            {
                LOG("Permission setting failed.\n");
                ecustatus.ErrorReg |= 1 << 3;
            }
        }

        // 错误处理
        if(ecustatus.ErrorReg != 0)
        {
            printf("can id 0x%x device ota failed, error register val 0x%x!\r\n", 
                   pOTA->deviceID, ecustatus.ErrorReg);
            LOG("can id 0x%x device ota failed, error register val 0x%x!\r\n", 
                pOTA->deviceID, ecustatus.ErrorReg);
            CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
            
            // 恢复备份（可选）
            if(access("/usr/xcharge/bat_ecu.backup", F_OK) == 0) {
                printf("Attempting to restore backup...\n");
                snprintf(cmd, sizeof(cmd), "cp \"%s/bat_ecu.backup\" \"%s/bat_ecu\"", APP_PATH, APP_PATH);
                system(cmd);
            }
        }
        
        pOTA->OTAStart = 0;
    }
	else{
		LOG("pOTA->deviceID = 0x%x, pOTA->deviceType = %d\r\n",pOTA->deviceID, pOTA->deviceType);
		ecustatus.ErrorReg = 1;
		ecustatus.ErrorDeviceID = pOTA->deviceID;
	}
}


void FinshhECUOtaAndCleanup(OTAObject* pOTA)
{
    pOTA->deviceType = 0;//停止升级
    pOTA->OTAStart = 0;
	// delete_files_with_prefix(USB_MOUNT_POINT, "XC");//  这个要删除升级文件，判断ecustatus状态，成功或者失败删除
	// delete_files_with_prefix(USB_MOUNT_POINT, "md5");// 
	otactrl.UpDating = 0;//1130(升级结束)
	ecustatus.CANStartOTA = 0;
	// set_charger_cmd(BMS_POWER_DEFAULT);
    CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAIDLE);
}


// 简单的文件验证（不依赖file命令）
int verify_bin_file(const char *filepath)
{
    FILE *fp = fopen(filepath, "rb");
    if (!fp) {
        printf("Cannot open file for verification: %s\n", filepath);
        return 0;
    }
    
    // 检查文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    printf("File size: %ld bytes\n", file_size);
    
    // ECU程序通常有一定的大小范围
    if (file_size < 5 * 1024 || file_size > 10 * 1024 * 1024) {
        printf("File size %ld not in expected range\n", file_size);
        fclose(fp);
        return 0;
    }
    
    // 可选：检查ELF魔数
    unsigned char header[4];
    if (fread(header, 1, 4, fp) == 4) {
        // ELF文件头: 0x7F 'E' 'L' 'F'
        if (header[0] == 0x7F && header[1] == 'E' && 
            header[2] == 'L' && header[3] == 'F') {
            printf("File has valid ELF header\n");
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    
    // 即使不是标准ELF也继续（可能是去掉了头的二进制）
    printf("File may be a binary (not standard ELF), continuing...\n");
    return 1;
}