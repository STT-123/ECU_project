#include "C_OCPPAPPUpdate.h"
#include "./ocpp/updownfile.h"
#include "./GLB/G_GloabalVariable.h"
#include "./CP/OTA/C_OTAXCPUpdate.h"
#include "./GLB/G_AddressDefinition.h"
#include "./CP/OTA/C_OTAOtherUpdate.h"
#include "./CP/OTA/C_OTAUDSUpdate.h"
#include "./CP/Xmodem/C_OTAStateMonitor.h"
#include "./DRV/Drv_SDCard.h"
#include "main.h"
#define __DEBUG__SYSTEM


#define APP_ECU_UPGRADE_FILE "XC_ECU_V"
#define APP_BCU_UPGRADE_FILE "XC_BCU_V"
#define APP_BMU_UPGRADE_FILE "XC_BMU_V"
#define APP_ACP_UPGRADE_FILE "XC_ACP_V"
#define APP_DCDC_UPGRADE_FILE "XC_DCDC_V"
#define APP_AC_UPGRADE_FILE "XC_AC_V"

#define APP_UPGRADE_FILE_MD5 "batota.md5"

#define UPDATE_FILE_PATH "/mnt/sda/"

#define ANY_SCRIPT_FILE "script"
#define ANY_SCRIPT_FILE_MD5 "script.md5"


char matched_filename[256] = {0};
#define TCU_LOG_FILENAME       "/usr/xcharge/log/App_project.log"   /*LOG文件名*/

pthread_mutex_t 				Log_DebugOut_mutex_lock;


int get_check_ac_upgarde_file_type(const char *filename,const char *filetype,char *out_matched_filename,size_t max_len,appDataType *appData,flashDataType *flashData,int *app_index,int *sbl_index);



bool app_upgrade_flag = false;
void set_app_upgrade_flag(bool sta)
{
	app_upgrade_flag = sta;
}
bool get_app_upgrade_flag()
{
	return app_upgrade_flag;
}

bool file_any_script_flag = false;
void set_any_script_flag(bool sta)
{
	file_any_script_flag = sta;
}

void Log_DebugOut_Time(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}
void Log_DebugOut(const char *fmt, ...)
{
	struct timeval    tv;
	struct timezone tz;
	struct tm         *p;

    pthread_mutex_lock(&(Log_DebugOut_mutex_lock)); /* 加锁 */
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);
	if(strlen(fmt) > 10){
		Log_DebugOut_Time("\n[%04d-%02d-%02d--%02d:%02d:%02d:%03d] ", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, (tv.tv_usec/1000));
	}
#ifdef __DEBUG__SYSTEM
	struct stat filestate;
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
    if(stat(TCU_LOG_FILENAME,&filestate))
    {
    	filestate.st_size = 0;
    }
#endif
	pthread_mutex_unlock(&(Log_DebugOut_mutex_lock));/* 解锁 */
}

int upgarde_file_type(const char *filename,const char *filetype)
{
    if(strstr(filetype, APP_ECU_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        int ret =get_check_upgarde_file_type(filename, APP_ECU_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
        printf("ret:%d \r\n",ret);
        if(ret == 0)
        {
            //标志位
			sleep(1);
            // otactrl.UpDating = 1;
            otactrl.deviceType =ECU;
            printf("ECU_OTA_otadeviceType: %u\r\n",otactrl.deviceType);
            printf("otafilenamestr: %s\r\n",filetype);
            memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
            memcpy(otactrl.OTAFilename, filetype, strlen(filetype));
            printf("otactrl.OTAFilename : %s\r\n",otactrl.OTAFilename);
            otactrl.OTAStart = 1;
        }
        return ret;
    }
    else if(strstr(filetype, APP_BCU_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        int ret =get_check_upgarde_file_type(filename, APP_BCU_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
        if(ret == 0)
        {
            //标志位
			sleep(1);
            // otactrl.UpDating = 1;
            otactrl.deviceType = BCU;
            otactrl.deviceID = BCUOTACANID;
            memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
            memcpy(otactrl.OTAFilename,matched_filename , strlen(matched_filename));
            printf("otactrl.OTAFilename : %s\r\n",otactrl.OTAFilename);
            printf("BCU_OTA_otadeviceType: %u\r\n",otactrl.deviceType);
            printf("otafilenamestr: %s\r\n",filetype);
             otactrl.OTAStart = 1;

        }
        return ret;
    }
    else if(strstr(filetype, APP_BMU_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        int ret =get_check_upgarde_file_type(filename, APP_BMU_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
        if(ret == 0)
		{
			//标志位
			sleep(1);
            // otactrl.UpDating = 1;
            otactrl.deviceType = BMU;
            memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
            memcpy(otactrl.OTAFilename,matched_filename , strlen(matched_filename));
			printf("BCU_OTA_otafilenamestr: %s\r\n",matched_filename);
            printf("otactrl.OTAFilename : %s\r\n",otactrl.OTAFilename);
            printf("BCU_OTA_otadeviceType: %u\r\n",otactrl.deviceType);
            printf("otafilenamestr: %s\r\n",filetype);
            otactrl.deviceID = 0x1821FF10;
			otactrl.OTAStart = 1;
			
		}

		
		return ret;
    }
    else if(strstr(filetype, APP_ACP_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        int ret =get_check_upgarde_file_type(filename, APP_ACP_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
        if(ret ==0)
		{

			//标志位
            // otactrl.UpDating = 1;
			sleep(1);
            otactrl.deviceType = ACP;
            memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
            memcpy(otactrl.OTAFilename,matched_filename , strlen(matched_filename));
			printf("BCU_OTA_otafilenamestr: %s\r\n",matched_filename);
            printf("otactrl.OTAFilename : %s\r\n",otactrl.OTAFilename);
            printf("BCU_OTA_otadeviceType: %u\r\n",otactrl.deviceType);
            printf("otafilenamestr: %s\r\n",filetype);
            otactrl.deviceID = ACPOTACANID;
			otactrl.OTAStart = 1;

		}
		return ret;
    }
	else if(strstr(filetype, APP_DCDC_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        int ret =get_check_upgarde_file_type(filename, APP_DCDC_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
        if(ret == 0)
		{
			//标志位
            // otactrl.UpDating = 1;
			sleep(1);
            otactrl.deviceType = DCDC;
            memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
            memcpy(otactrl.OTAFilename,matched_filename , strlen(matched_filename));
			printf("BCU_OTA_otafilenamestr: %s\r\n",matched_filename);
            printf("otactrl.OTAFilename : %s\r\n",otactrl.OTAFilename);
            printf("BCU_OTA_otadeviceType: %u\r\n",otactrl.deviceType);
            printf("otafilenamestr: %s\r\n",filetype);
            otactrl.deviceID = DCDCOTACANID;
			otactrl.OTAStart = 1;
		}
		return ret;
    }
    else if(strstr(filetype, APP_AC_UPGRADE_FILE) != NULL) 
    {
		otactrl.UpDating = 1;
		sleep(1);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
        // int ret =get_check_upgarde_file_type(filename, APP_AC_UPGRADE_FILE,matched_filename,sizeof(matched_filename));
		int app_index = 0, sbl_index = 0;
		int ret = get_check_ac_upgarde_file_type(filename, APP_AC_UPGRADE_FILE, matched_filename,sizeof(matched_filename),&appData,&flashData,&app_index,&sbl_index);
		// printf("ret %d\r\n" ,ret);
		// printf("app_index:%d,sbl_index:%d\r\n"	,app_index,sbl_index);
		// printf("otactrl.OTAUdsSblFilename[0]:%s\n", otactrl.OTAUdsSblFilename[0]);
		// printf("flashData[0].writeAddr,flashData[0].writeLen,flashData[0].CRC :%x,%x,%x \r\n", flashData.writeAddr,flashData.writeLen,flashData.CRC);
		// printf("otactrl.OTAUdsFilename[0]:%s\n", otactrl.OTAUdsFilename[0]);
		// printf("appData[0].writeAddr,appData[0].writeLen,appData[0].CRC :%x,%x,%x \r\n", appData[0].writeAddr,appData[0].writeLen,appData[0].CRC);
		// printf("otactrl.OTAUdsFilename[1]:%s\n", otactrl.OTAUdsFilename[1]);
		// printf("appData[1].writeAddr,appData[1].writeLen,appData[1].CRC :%x,%x,%x \r\n", appData[1].writeAddr,appData[1].writeLen,appData[1].CRC);
		// printf("otactrl.OTAUdsFilename[2]:%s\n", otactrl.OTAUdsFilename[2]);
		// printf("appData[2].writeAddr,appData[2].writeLen,appData[2].CRC :%x,%x,%x \r\n", appData[2].writeAddr,appData[2].writeLen,appData[2].CRC);
		// printf("otactrl.OTAUdsFilename[3]:%s\n", otactrl.OTAUdsFilename[3]);
		// printf("appData[3].writeAddr,appData[3].writeLen,appData[3].CRC :%x,%x,%x \r\n", appData[3].writeAddr,appData[3].writeLen,appData[3].CRC);
		// printf("otactrl.OTAUdsFilename[4]:%s\n", otactrl.OTAUdsFilename[4]);
		// printf("appData[4].writeAddr,appData[4].writeLen,appData[4].CRC :%x,%x,%x \r\n", appData[4].writeAddr,appData[4].writeLen,appData[4].CRC);
		// printf("otactrl.OTAUdsFilename[5]:%s\n", otactrl.OTAUdsFilename[5]);
		// printf("appData[5].writeAddr,appData[5].writeLen,appData[5].CRC :%x,%x,%x \r\n", appData[5].writeAddr,appData[5].writeLen,appData[5].CRC);
		// printf("otactrl.OTAUdsFilename[6]:%s\n", otactrl.OTAUdsFilename[6]);
		// printf("appData[6].writeAddr,appData[6].writeLen,appData[6].CRC :%x,%x,%x \r\n", appData[6].writeAddr,appData[6].writeLen,appData[6].CRC);
		// printf("otactrl.OTAUdsFilename[7]:%s\n", otactrl.OTAUdsFilename[7]);
		// printf("appData[7].writeAddr,appData[7].writeLen,appData[7].CRC :%x,%x,%x \r\n", appData[7].writeAddr,appData[7].writeLen,appData[7].CRC);

       if(ret ==0)
	   {
			sleep(1);
			SBl_index = sbl_index;
			APP_index = app_index;

			printf(" SBl_index %d APP_index %d\n", SBl_index, APP_index);
			ret = CP_set_modbus_reg_val(AC_SBL_OTAFILENUMBER, 1);
			ret = CP_set_modbus_reg_val(AC_APP_OTAFILENUMBER, 8);

			ret = CP_get_modbus_reg_val(AC_SBL_OTAFILENUMBER, &sblfilenumber);
			ret = CP_get_modbus_reg_val(AC_APP_OTAFILENUMBER, &appfilenumber);
			printf(" sblfilenumber %d appfilenumber %d\n", sblfilenumber, appfilenumber);

			if((SBl_index != 0) && (SBl_index == sblfilenumber) && (APP_index != 0) && (APP_index == appfilenumber))
			{
				printf("SBl_index ...  %d \r\n",SBl_index);
				printf("APP_index ...  %d \r\n",APP_index);
				printf("sblfilenumber...%d\r\n",sblfilenumber);
				printf("appfilenumber...%d\r\n",appfilenumber);
				otactrl.deviceID = ACOTACANID;
				otactrl.deviceType = AC;
				otactrl.OTAStart = 1;

			}


	   }
	    return ret;
    }
	else
	{
		printf("Match failed:%s \r\n",filetype);
		return -1;

	}
}

int get_check_upgarde_file_type(const char *filename,const char *filetype,char *out_matched_filename, size_t max_len) // 传入压缩包路径加名字
{
	FILE *fp;
	// **here comes where I have the problem, reading the value**
	char str[1000] = {0};
	char *p = NULL;
	int result = 0;
	bool A_pfc_flag = false;
	bool B_dcdc_flag = false;
	bool app_upgrade_flag = false;
	bool c9360_upgrade_flag = false;
	bool any_script_flag = false;
	bool byd_bat_ota_flag = false;

	memset(str, 0, sizeof(str));
	sprintf(str, "tar tf %s ", filename);
    // sprintf(str, "unzip -l %s", filename); 
	fp = NULL;
	fp = popen(str, "r");
	Log_DebugOut("str:%s \r\n", str);
	if (fp == NULL)
	{
		Log_DebugOut("popen %s fail \r\n", str);
		result = -1;
		return result;
	}
	memset(str, 0, sizeof(str));
    printf("11111\r\n");
	while (fgets(str, sizeof(str), fp) != NULL)
	{
        printf("str:%s \r\n", str);
		Log_DebugOut("get %s %s  \r\n", filename, str);

		p = NULL;
		printf("filetype :%s\r\n",filetype);
		p = strstr((char *)str, filetype); //升级app 文件
        printf("p:%s \r\n",p);
		if (p)
		{
			app_upgrade_flag = true;
            printf("app_upgrade_flag:%d \r\n", app_upgrade_flag);
                // 清除换行符
            char *newline = strchr(str, '\n');
            if (newline) *newline = '\0';

            // 拷贝到输出参数
            strncpy(out_matched_filename, str, max_len - 1);
            out_matched_filename[max_len - 1] = '\0';  // 确保结尾
            printf("out_matched_filename Matched filename: %s\n", out_matched_filename);
        }

		p = NULL;
		p = strstr((char *)str, ANY_SCRIPT_FILE); //主机 执行脚本文件
		if (p)
		{
			any_script_flag = true;
            printf("any_script_flag:%d \r\n", any_script_flag);
		}

		
	}
    printf("22222\r\n");
	if (fp != NULL)
	{
		pclose(fp);
	}
    printf("33333\r\n");
	if(app_upgrade_flag == true) //解压压缩包 校验应用的MD5值
	{
        printf("44444\r\n");
		memset(str, 0, sizeof(str));
		sprintf(str, "cd %s \n tar xvf %s \n", UPDATE_FILE_PATH, filename);
		Log_DebugOut("%s \r\n", str);
		system(str);
		//校验MD5值
		memset(str, 0, sizeof(str));
		sprintf(str, "cd %s \n md5sum -c %s \n", UPDATE_FILE_PATH, APP_UPGRADE_FILE_MD5);
		Log_DebugOut("str:%s \r\n", str);
		fp = NULL;
		fp = popen(str, "r"); //进入文件
		if (fp == NULL)
		{
			Log_DebugOut("popen %s fail \r\n", str);
			result = -1;
			return result;
		}
		memset(str, 0, sizeof(str));
		app_upgrade_flag = false;
		while (fgets(str, sizeof(str), fp) != NULL)
		{
			Log_DebugOut("get %s  \r\n", str);
			p = NULL;
			p = strstr((char *)str, "OK");
			if (p)
			{
				app_upgrade_flag = true;
			}
			else
			{
				Log_DebugOut("%s md5 check fail \r\n", filetype);
				app_upgrade_flag = false;
			}
		}
		if (fp != NULL)
		{
			pclose(fp);
		}
	}
    printf("55555\r\n");
	if (app_upgrade_flag == true)
	{
		Log_DebugOut("%s ready upgrade  \r\n", filetype);
		set_app_upgrade_flag(app_upgrade_flag);
	}
	else
	{
		set_app_upgrade_flag(app_upgrade_flag);
	}

   printf("666666\r\n");

	if (any_script_flag == true) //解压压缩包 校验应用的MD5值
	{
		memset(str, 0, sizeof(str));
		sprintf(str, "cd %s \n tar xvf %s \n", UPDATE_FILE_PATH, filename);
		Log_DebugOut("%s \r\n", str);
		system(str);
		//校验MD5值
		memset(str, 0, sizeof(str));
		sprintf(str, "cd %s \n md5sum -c %s \n", UPDATE_FILE_PATH, ANY_SCRIPT_FILE_MD5);
		Log_DebugOut("%s \r\n", str);
		fp = NULL;
		fp = popen(str, "r"); //进入文件
		if (fp == NULL)
		{
			Log_DebugOut("popen %s fail \r\n", str);
			result = -1;
			return result;
		}
		memset(str, 0, sizeof(str));
		any_script_flag = false;
		while (fgets(str, sizeof(str), fp) != NULL)
		{
			Log_DebugOut("get %s  \r\n", str);
			p = NULL;
			p = strstr((char *)str, "OK");
			if (p)
			{
				any_script_flag = true;
			}
			else
			{
				Log_DebugOut("%s md5 check fail \r\n", ANY_SCRIPT_FILE);
				any_script_flag = false;
			}
		}
		if (fp != NULL)
		{
			pclose(fp);
		}
	}
    printf("77777\r\n");
	if (any_script_flag == true)
	{
		Log_DebugOut("%s ready upgrade  \r\n", ANY_SCRIPT_FILE);
		set_any_script_flag(any_script_flag);
	}
	else
	{
		set_any_script_flag(any_script_flag);
	}
	return result;
}






int get_check_ac_upgarde_file_type(const char *filename,
                                const char *filetype,
                                char *out_matched_filename,
                                size_t max_len,
                                appDataType *appData,
                                flashDataType *flashData,
                                int *app_index,
                                int *sbl_index)
{
    FILE *fp;
    char str[1000] = {0};
    char *p = NULL;
    int result = 0;
    bool app_upgrade_flag = false;
    bool any_script_flag = false;

    sprintf(str, "tar tf %s", filename);
    fp = popen(str, "r");
    Log_DebugOut("str:%s \r\n", str);
    if (fp == NULL)
    {
        Log_DebugOut("popen %s fail \r\n", str);
        return -1;
    }

    while (fgets(str, sizeof(str), fp) != NULL)
    {
        Log_DebugOut("get %s %s  \r\n", filename, str);

        char ota_filename[256] = {0};
        strncpy(ota_filename, str, sizeof(ota_filename) - 1);
        char *newline = strchr(ota_filename, '\n');
        if (newline) *newline = '\0';

        if (strstr(ota_filename, ".bin"))
        {
            if (strstr(ota_filename, "AC_SBL") != NULL && *sbl_index < SUP_MAX_BLOCK)
            {
                char *token;
                char *saveptr;
				memset(otactrl.OTAUdsSblFilename[*sbl_index],0 ,sizeof(otactrl.OTAUdsSblFilename[*sbl_index]));

				// strncpy(otactrl.OTAUdsSblFilename[*sbl_index], ota_filename, sizeof(otactrl.OTAUdsSblFilename[*sbl_index]) - 1);
				    
    			snprintf(otactrl.OTAUdsSblFilename[*sbl_index], sizeof(otactrl.OTAUdsSblFilename[*sbl_index]), "%s/%s", USB_MOUNT_POINT, ota_filename);
				// printf("AC_SBL_%d: %s\n", *sbl_index, otactrl.OTAUdsSblFilename[*sbl_index]);


                token = strtok_r(ota_filename, "_", &saveptr); // AC
                token = strtok_r(NULL, "_", &saveptr);         // SBL
                token = strtok_r(NULL, "_", &saveptr);         // addr
                flashData[*sbl_index].writeAddr = strtoul(token, NULL, 16);
                token = strtok_r(NULL, "_", &saveptr);         // len
                flashData[*sbl_index].writeLen = strtoul(token, NULL, 16);
                token = strtok_r(NULL, ".", &saveptr);         // crc
                flashData[*sbl_index].CRC = (uint16_t)strtoul(token, NULL, 16);
                printf("SBL[%d] addr: 0x%08X, len: 0x%08X, crc: 0x%04X\n",
                             *sbl_index,
                             flashData[*sbl_index].writeAddr,
                             flashData[*sbl_index].writeLen,
                             flashData[*sbl_index].CRC);
                (*sbl_index)++;
            }
            else if (strstr(ota_filename, "AC_APP") != NULL && *app_index < SUP_MAX_BLOCK)
            {
                strncpy(out_matched_filename, ota_filename, max_len - 1);
                out_matched_filename[max_len - 1] = '\0';
                app_upgrade_flag = true;
				memset(otactrl.OTAUdsFilename[*app_index],0 ,sizeof(otactrl.OTAUdsFilename[*app_index]));
				// strncpy(otactrl.OTAUdsFilename[*app_index], ota_filename, sizeof(otactrl.OTAUdsFilename[*app_index]) - 1);
				snprintf(otactrl.OTAUdsFilename[*app_index], sizeof(otactrl.OTAUdsFilename[*app_index]), "%s/%s", USB_MOUNT_POINT, ota_filename);
				// printf("app_index:%d, ota_filename:%s\n", *app_index, ota_filename);


                char *token;
                char *saveptr;
                token = strtok_r(ota_filename, "_", &saveptr); // AC
                token = strtok_r(NULL, "_", &saveptr);         // APP
                token = strtok_r(NULL, "_", &saveptr);         // addr
                appData[*app_index].writeAddr = strtoul(token, NULL, 16);
                token = strtok_r(NULL, "_", &saveptr);         // len
                appData[*app_index].writeLen = strtoul(token, NULL, 16);
                token = strtok_r(NULL, ".", &saveptr);         // crc
                appData[*app_index].CRC = (uint16_t)strtoul(token, NULL, 16);
                printf("APP[%d] addr: 0x%08X, len: 0x%08X, crc: 0x%04X\n",
                             *app_index,
                             appData[*app_index].writeAddr,
                             appData[*app_index].writeLen,
                             appData[*app_index].CRC);
                (*app_index)++;
            }
        }

        if (strstr(str, ANY_SCRIPT_FILE))
        {
            any_script_flag = true;
        }
    }

    if (fp)
        pclose(fp);

    // 解压并检查 APP 文件 MD5
    if (app_upgrade_flag)
    {
        snprintf(str, sizeof(str), "cd %s && tar xvf %s", UPDATE_FILE_PATH, filename);
        Log_DebugOut("%s \r\n", str);
        system(str);

        snprintf(str, sizeof(str), "cd %s && md5sum -c %s", UPDATE_FILE_PATH, APP_UPGRADE_FILE_MD5);
        Log_DebugOut("str:%s \r\n", str);
        fp = popen(str, "r");
        if (fp)
        {
            while (fgets(str, sizeof(str), fp) != NULL)
            {
                if (strstr(str, "OK"))
                    app_upgrade_flag = true;
                else
                    app_upgrade_flag = false;
            }
            pclose(fp);
        }
        else
        {
            Log_DebugOut("popen %s fail \r\n", str);
            result = -1;
        }
        set_app_upgrade_flag(app_upgrade_flag);
    }

    // 脚本文件也做 MD5 检查
    if (any_script_flag)
    {
        snprintf(str, sizeof(str), "cd %s && tar xvf %s", UPDATE_FILE_PATH, filename);
        system(str);

        snprintf(str, sizeof(str), "cd %s && md5sum -c %s", UPDATE_FILE_PATH, ANY_SCRIPT_FILE_MD5);
        fp = popen(str, "r");
        if (fp)
        {
            while (fgets(str, sizeof(str), fp) != NULL)
            {
                if (strstr(str, "OK"))
                    any_script_flag = true;
                else
                    any_script_flag = false;
            }
            pclose(fp);
        }
        else
        {
            Log_DebugOut("popen %s fail \r\n", str);
            result = -1;
        }
        set_any_script_flag(any_script_flag);
    }

    return result;
}
