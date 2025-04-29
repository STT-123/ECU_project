#define _GNU_SOURCE
#include "C_OTAXCPUpdate.h"
#include "../GLB/G_GloabalVariable.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"
#include "./DRV/Drv_ECUAndBMUCommunication.h"
#include "./GLB/G_AddressDefinition.h"
#include "../CP/BMS/bms/bms_cortol.h"
#include "./Xmodem/C_OTADataMonitor.h"
#include "main.h"
XCPStatus xcpstatus;
signed char XcpSendConnectCMD(unsigned int id, unsigned char xcpobjectid)
{
	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 1;
	CanMes.ID = id;
	CanMes.Data[0] = 0xFF;
	//CanMes.Data[1] = 0x00;
	if(xcpobjectid == 0)
	{

		//xQueueSend(xQueue_forward_can_out2in,&CanMes,100/portTICK_PERIOD_MS);
		return can2_send(&CanMes);	
	}
	else
	{
        can1_send(&CanMes);
		return 0;
		//return CANSendMsg(BCUXCPCANID, &CanMes);
	}

}



signed char XCPCANOTAMSGParse(CAN_MESSAGE *pCANMsg, XCPStatus *pXCPStatus)
{
	if(pCANMsg == NULL || pXCPStatus== NULL)
	{
		return -1;
	}

	if(pCANMsg->Length == 1)
	{
		if(pCANMsg->Data[0] == 0xFF)
		{
			//XXflag = 1;
			//XCPCMDResponseFlag = 1;
			pXCPStatus->XCPCMDResponseFlag = 1;
			//printf("xcpstatus.XCPCMDResponseFlag -> 1\r\n");
		}
	}
	else if(pCANMsg->Length == 6)
	{
		pXCPStatus->XCPQUERYCMDResponseFlag = 1;
		unsigned char cmpbuf[6] ={0xFF, 0x00, 0x10, 0x00, 0x00, 0x00};
		if(memcmp(cmpbuf, pCANMsg->Data, 6) == 0)
		{
			pXCPStatus->DeviceCanProgramFlag = 1;
			//printf("xcpstatus.DeviceCanProgramFlag -> 1\r\n");
		}

	}
	else if(pCANMsg->Length == 8)
	{
		if(pCANMsg->Data[0] == 0xFF && pCANMsg->Data[1] == 0x10)
		{
			//xxflag = 1;

			pXCPStatus->DeviceConnectedFlag = 1;
			//printf("xcpstatus.DeviceConnectedFlag -> 1\r\n");

		}
	}
	else
	{
		printf("Unsupported xcp responsed cmd!\r\n");
		return -2;
	}

	return 0;
}



signed char XcpSendQueryStatusCMD(unsigned int id, unsigned char xcpobjectid)
{
	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 1;
	CanMes.ID = id;
	CanMes.Data[0] = 0xFD;
	if(xcpobjectid == 0)
	{
		return can2_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		can1_send(&CanMes);
		return 0;
	}
}



signed char XcpSendProgramMaxCMD(unsigned int id, unsigned char *pbuf, unsigned char payloaddatalen, unsigned char xcpobjectid)
{
	if(pbuf == NULL)
	{
		return -10;
	}

	if(payloaddatalen > 7)
	{
		return -9;
	}
	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = payloaddatalen + 1;
	CanMes.ID = id;
	CanMes.Data[0] = 0xC9;
#if 0
	int i;


	for(i = 0; i < payloaddatalen; i++)
	{
		CanMes.Data[i+1] = pbuf[payloaddatalen-1-i];

	}

#else
	memcpy(&CanMes.Data[1], pbuf, payloaddatalen);
#endif
	if(xcpobjectid == 0)
	{
		return can2_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		can1_send(&CanMes);	
		return 0;
	}
}



signed char XCPCANOTAMSGParseMult(XCPStatus *xcpstatus)
{
    int xStatus;
    int err;
    struct timespec xStartTime;
    clock_gettime(CLOCK_MONOTONIC, &xStartTime);
	CAN_MESSAGE canmsg;
	memset(&canmsg, 0, sizeof(CAN_MESSAGE));
	while (1) {
		xStatus = queue_pend(&Queue_Can2RevData, &canmsg,&err);
	    if (xStatus == 0)
	    {
	    	signed char res = XCPCANOTAMSGParse(&canmsg, xcpstatus);
	        if ((res == 0) && (xcpstatus->XCPCMDResponseFlag == 1))
	        {
	        	return 0;
	        }
	    }
		if (GetTimeDifference_ms(xStartTime)>50 )
		{
			return 1;
		}
	}
}




signed char XcpSendProgramEndCMD(unsigned int id, unsigned char xcpobjectid)
{

	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 2;
	CanMes.ID = id;
	CanMes.Data[0] = 0xD0;
	CanMes.Data[1] = 0x00;

	if(xcpobjectid == 0)
	{
		return can2_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		
		return can1_send(&CanMes);	
	}
}



signed char XcpSendProgramResetCMD(unsigned int id, unsigned char xcpobjectid)
{

	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 1;
	CanMes.ID = id;
	CanMes.Data[0] = 0xCF;

	if(xcpobjectid == 0)
	{
		return can2_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		return can1_send(&CanMes);	
	}
}






int XcpTryConnectDevice(OTAObject *pOTA)
{
    int xStatus;
    int err;
	if (xcpstatus.ErrorReg != 0)
		return -1;

	xcpstatus.XCPCMDOuttimeTimes = 5000;
	xcpstatus.XCPCMDOuttimeTime = XCPOVERTIME;
	xcpstatus.XCPCMDRpeatTimes = 0;
	unsigned int times = 0;

	while (1)
	{
		signed char res = -1;

		if (pOTA->deviceType == BMU)
		{
			res = XcpSendConnectCMD(pOTA->deviceID, 0);
		}
		else
		{
			xcpstatus.CANStartOTA = 1; //1126
			printf("XcpSendConnectCMD_ing\r\n");
			res = XcpSendConnectCMD(pOTA->deviceID, 1);
		}

		printf("xQueueReceive_ing\r\n");

		CAN_MESSAGE canmsg;
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
        usleep(2*1000);
        if(pOTA->deviceType == BMU)
        {
            xStatus = queue_pend(&Queue_Can2RevData, &canmsg,&err);
        }
        else
        {
            xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
        }
		
		if (xStatus == 0)
		{
			signed char res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
			if (res == 0 && xcpstatus.DeviceConnectedFlag)
			{
				printf("Can ID 0x%x device connected!\r\n", pOTA->deviceID);
				return 0;
			}
		}

		times++;
		if (times >= xcpstatus.XCPCMDOuttimeTimes)
		{
			printf("Overtime %d times ,Can ID 0x%x device connect failed!\r\n", xcpstatus.XCPCMDOuttimeTimes, pOTA->deviceID);
			memset(&xcpstatus, 0, sizeof(XCPStatus));
			xcpstatus.ErrorReg |= 1 << 3;
			xcpstatus.ErrorDeviceID = pOTA->deviceID;
			return -1;
		}
	}
}




int XcpTryQueryStatusOnce(OTAObject *pOTA)
{
    int xStatus;
    int err;
    if (xcpstatus.ErrorReg != 0)
        return -1;

    xcpstatus.XCPCMDOuttimeTimes = 5;
    xcpstatus.XCPCMDOuttimeTime = XCPOVERTIME;
    xcpstatus.XCPCMDRpeatTimes = 0;

    signed char res = -1;
    if (pOTA->deviceType == BMU)
    {
        res = XcpSendQueryStatusCMD(pOTA->deviceID, 0);
    }
    else
    {
        printf("XcpSendQueryStatusCMD\r\n");
        xcpstatus.CANStartOTA = 1;
        res = XcpSendQueryStatusCMD(pOTA->deviceID, 1);
    }

    if (res < 0)
    {
        printf("XCP SendQueryStatusCMD error, Error code %d\r\n", res);
        xcpstatus.ErrorReg |= 1 << 4;
        xcpstatus.ErrorDeviceID = pOTA->deviceID;
        return -1;
    }

    usleep(20*1000);

    printf("xQueueReceive_ing\r\n");
    CAN_MESSAGE canmsg;
    memset(&canmsg, 0, sizeof(CAN_MESSAGE));

    if(pOTA->deviceType == BMU)
    {
        xStatus = queue_pend(&Queue_Can2RevData, &canmsg,&err);
    }
    else
    {
        xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
    }
    if (xStatus == 0)
    {
        signed char parseRes = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
        if (parseRes == 0 && xcpstatus.DeviceCanProgramFlag)
        {
            printf("Can ID 0x%x device can be programmed!\r\n", pOTA->deviceID);
            return 0;
        }
    }

    // 超时或解析失败
    printf("Device query response timeout or failed. ID: 0x%x\r\n", pOTA->deviceID);
    xcpstatus.ErrorReg |= 1 << 5;
    xcpstatus.ErrorDeviceID = pOTA->deviceID;
    return -1;
}






/// @brief 
/// @param rfile 
/// @param FileBuff 
/// @param FileCount 
/// @param totalpack 
/// @param i 
/// @return 
bool ReadFileData(FILE *rfile, unsigned char *FileBuff, unsigned char *FileCount, unsigned int totalpack, unsigned int i) {
    size_t rnum = 0;
    if (*FileCount == 0 || *FileCount >= 70) {
        int remaining_data = (totalpack - i) * 7;
        int bytes_to_read = (remaining_data < sizeof(FileBuff)) ? remaining_data : sizeof(FileBuff);
        rnum = fread(FileBuff, 1, bytes_to_read, rfile);

        if (rnum < 7) {
            printf("file read 7 byte data failed! rnum: %zu\n", rnum);
            return false;
        }
        *FileCount = 0;
    }
    return true;
}

void SendOTACommand(OTAObject *pOTA, unsigned char *buf, unsigned int len, XCPStatus *xcpstatus, unsigned int i, unsigned int totalpack, unsigned int percent_count) {
    xcpstatus->XCPCMDOuttimeTimes = 1;
    xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
    xcpstatus->XCPCMDRpeatTimes = 0;
    xcpstatus->XCPCMDResponseFlag = 0;
    signed char res;
    unsigned int times = 0;
    unsigned int per = i / percent_count;
    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, (10 + per)); // 0124, upgrade progress

    while (1) {

        
        if(pOTA->deviceType == BMU)
        {
            res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, len, 0);
        }
        else
        {
            res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, len,1);
        }

        if (res != 0) {
            printf("XCP XcpSendProgramMaxCMD error, Error code %d\r\n", res);
            xcpstatus->ErrorReg |= 1 << 7;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            break;
        }

        int result = XCPCANOTAMSGParseMult(xcpstatus);
        if (result == 0) {
            break;
        }

        times++;
        if (times >= xcpstatus->XCPCMDOuttimeTimes) {
            printf("Overtime %d times_6 ,Can ID 0x%x device XcpSendProgramMaxCMD response failed!\r\n", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
            xcpstatus->ErrorReg |= 1 << 8;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            break;
        }
    }
}

void SendLastPacket(FILE*rfile, OTAObject *pOTA, unsigned char lastpackdatanum, XCPStatus *xcpstatus) {
    signed char res;
     int xStatus;
     int err;
    unsigned char buf[7] = {0};
    size_t rnum = 0;
     rnum = fread(buf, 1, lastpackdatanum, rfile);

    if (rnum != lastpackdatanum) {
        printf("file read %d byte data failed!\r\n", lastpackdatanum);
        xcpstatus->ErrorReg |= 1 << 6;
        xcpstatus->ErrorDeviceID = pOTA->deviceID;
    } else {
        xcpstatus->XCPCMDOuttimeTimes = 1;
        xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
        xcpstatus->XCPCMDRpeatTimes = 0;

        unsigned int times = 0;
        while (1) {
            xcpstatus->XCPCMDResponseFlag = 0;
            if(pOTA->deviceType == BMU)
            {
                res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, lastpackdatanum, 0);
            }
            else
            {
                res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, lastpackdatanum,1);
            }
            if (res != 0) {
                printf("XCP XcpSendProgramCMD error, Error code %d\r\n", res);
                xcpstatus->ErrorReg |= 1 << 11;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;
                break;
            }

            CAN_MESSAGE canmsg;
            memset(&canmsg, 0, sizeof(CAN_MESSAGE));
            usleep(2*1000);
            if(pOTA->deviceType == BMU)
            {
               xStatus =  queue_pend(&Queue_Can2RevData, &canmsg,&err);
            }
            else
            {
                xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
            }

            if (xStatus == 0) {
                signed char res = XCPCANOTAMSGParse(&canmsg, xcpstatus);
                if (res == 0 && xcpstatus->XCPCMDResponseFlag) {
                    break;
                }
            }

            times++;
            if (times >= xcpstatus->XCPCMDOuttimeTimes) {
                printf("Overtime %d times_7 ,Can ID 0x%x device XcpSendProgramCMD response failed!\r\n", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                xcpstatus->ErrorReg |= 1 << 12;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;
                break;
            }
        }
    }
}


void ReadFileAndSendData(FILE *rfile, OTAObject *pOTA, XCPStatus *xcpstatus) {
   int fd = fileno(rfile); // 从 FILE* 获取文件描述符
    struct stat file_stat;
    if (fstat(fd, &file_stat) != 0) {
        perror("fstat failed");
        return;
    }
    unsigned int filesize = file_stat.st_size;
    printf("Bin ota file size %d\r\n", filesize);

    unsigned char lastpackdatanum = filesize % 7;
    unsigned int totalpack = (filesize - lastpackdatanum) / 7;
    unsigned int percent_count = totalpack / 80;
    lastpackdatanum = filesize - (totalpack * 7);

    unsigned char PrvProgramProgress = 0;
    unsigned char ProgramProgress = 0;
    
    fseek(rfile, 0, SEEK_SET);
    printf("totalpack %d, lastpackdatanum %d\r\n", totalpack, lastpackdatanum);

    unsigned char FileBuff[490] = {0};
    unsigned char FileCount = 0;

    if (lastpackdatanum != 0) {
        totalpack += 1;
        int i = 0;

        for (i = 0; i < totalpack - 1; i++) {
            unsigned char buf[7] = {0};
            if (ReadFileData(rfile, FileBuff, &FileCount, totalpack, i)) {
                memcpy(buf, &FileBuff[FileCount * 7], 7);
                SendOTACommand(pOTA, buf, 7, xcpstatus, i, totalpack, percent_count);
            }

            ProgramProgress = (int)((float)i / totalpack * 100);
            if (ProgramProgress != PrvProgramProgress) {
                // Handle progress change
            }
            PrvProgramProgress = ProgramProgress;
        }

        if (xcpstatus->ErrorReg == 0) {
            SendLastPacket(rfile, pOTA, lastpackdatanum, xcpstatus);
        }

    } else {
        printf("Total programmax pack %d\r\n", totalpack);
        for (int i = 0; i < totalpack; i++) {
            unsigned char buf[7] = {0};
            if (ReadFileData(rfile, FileBuff, &FileCount, totalpack, i)) {
                memcpy(buf, &FileBuff[FileCount * 7], 7);
                SendOTACommand(pOTA, buf, 7, xcpstatus, i, totalpack, percent_count);
            }

            ProgramProgress = (int)((float)i / totalpack * 100);
            if (ProgramProgress != PrvProgramProgress) {
                // Handle progress change
            }
            PrvProgramProgress = ProgramProgress;
        }
    }
}





// 封装XCP命令发送和响应接收处理逻辑
static int SendXcpProgramEndCommand(OTAObject *pOTA, XCPStatus *xcpstatus) {
    signed char res = -1;
    
    if (pOTA->deviceType == BMU) {
        res = XcpSendProgramEndCMD(pOTA->deviceID, 0);
    } else {
        xcpstatus->CANStartOTA = 1; // 1126
        res = XcpSendProgramEndCMD(pOTA->deviceID, 1);
    }

    if (res != 0) {
        printf(" XCP XcpSendProgramEndCMD error, Error code %d\r\n", res);
        memset(xcpstatus, 0, sizeof(XCPStatus));
        xcpstatus->ErrorReg |= 1 << 14;
        xcpstatus->ErrorDeviceID = pOTA->deviceID;
        return -1; // 返回错误代码
    }

    return 0; // 成功
}

// 封装响应超时和错误处理逻辑
static int HandleXcpResponseTimeout(XCPStatus *xcpstatus, OTAObject *pOTA) {
    CAN_MESSAGE canmsg;
    int xStatus;
    int err;
    unsigned int times = 0;
    memset(&canmsg, 0, sizeof(CAN_MESSAGE));

    if(pOTA->deviceType == BMU)
    {
        xStatus =  queue_pend(&Queue_Can2RevData, &canmsg,&err);
    }
    else
    {
        xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
    }    
    if (xStatus == 0) {
        signed char res = XCPCANOTAMSGParse(&canmsg, xcpstatus);
        if (res == 0 && xcpstatus->XCPCMDResponseFlag) {
            return 0; // 收到有效响应
        }
        else
        {
            times++;
            if(times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_11 ,Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(&xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= 1 << 15;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;

            return -1; // 收到有效响应
            }
        }
        
    }
    else
    {
        // 如果没有响应，增加尝试次数
        times++;
        if (times >= xcpstatus->XCPCMDOuttimeTimes) {
            printf("Overtime %d times, Can ID 0x%x device XcpSendProgramEndCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
            memset(xcpstatus, 0, sizeof(XCPStatus));
            xcpstatus->ErrorReg |= 1 << 15;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            return -1; // 收到有效响应
        }
    }

}

// 主函数封装，调用上述函数处理XCP
void HandleXcpCommunication(OTAObject *pOTA, XCPStatus *xcpstatus) {
    xcpstatus->XCPCMDOuttimeTimes = 1;
    xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
    xcpstatus->XCPCMDResponseFlag = 0;

    unsigned int times = 0;
    while (1) {
        // 发送XCP命令
        int sendResult = SendXcpProgramEndCommand(pOTA, xcpstatus);
        if (sendResult != 0) {
            break;
        }

        // 等待并处理响应
        int responseResult = HandleXcpResponseTimeout(xcpstatus, pOTA);
        if (responseResult == 0) {
            break; // 成功接收到响应
        }
        else
        {
            break;
        }

        usleep(2*1000);
    }
}




signed char XcpProgramResetHandler(OTAObject *pOTA,XCPStatus *xcpstatus)
{
    xcpstatus->XCPCMDOuttimeTimes = 5;
    xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
    xcpstatus->XCPCMDRpeatTimes = 0;
    xcpstatus->XCPCMDResponseFlag = 0;

    unsigned int times = 0;
    int xStatus;
    int err;
    while (1)
    {
        signed char res = -1;

        if (pOTA->deviceType == BMU)
        {
            res = XcpSendProgramResetCMD(pOTA->deviceID, 0);
        }
        else
        {
            xcpstatus->CANStartOTA = 1; // 1126
            res = XcpSendProgramResetCMD(pOTA->deviceID, 1);
        }

        if (res != 0)
        {
            printf("XCP XcpSendProgramResetCMD error, Error code %d\r\n", res);
            memset(&xcpstatus, 0, sizeof(XCPStatus));
            xcpstatus->ErrorReg |= (1 << 9);
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            return -1; // 发送失败
        }

        CAN_MESSAGE canmsg;
        memset(&canmsg, 0, sizeof(CAN_MESSAGE));

       usleep(2*1000);

        if(pOTA->deviceType == BMU)
        {
            xStatus =  queue_pend(&Queue_Can2RevData, &canmsg,&err);
        }
        else
        {
            xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
        }  
        if (xStatus == 0)
        {
            res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
            if (res == 0)
            {
                if (xcpstatus->XCPCMDResponseFlag)
                {
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 90); // 0124, 升级进度
                    return 0; // 成功完成
                }
            }
            else
            {
                times++;
                if (times >= xcpstatus->XCPCMDOuttimeTimes)
                {
                    printf("Overtime %d times_13, Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                    memset(&xcpstatus, 0, sizeof(XCPStatus));
                    xcpstatus->ErrorReg |= (1 << 10);
                    xcpstatus->ErrorDeviceID = pOTA->deviceID;
                    return -2; // 超时错误
                }
            }
        }
        else
        {
            times++;
            if (times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_14, Can ID 0x%x device XcpSendProgramResetCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(&xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= (1 << 10);
                xcpstatus->ErrorDeviceID = pOTA->deviceID;
                return -2; // 超时错误
            }
        }
    }
}


// OTAObject *pOTA = (OTAObject *)param;
void CP_XCP_OTA(OTAObject *pOTA)
{
    if (!pOTA->OTAStart) return;
    if(pOTA->deviceID != 0 && pOTA->OTAFilename[0] != 0 && pOTA->OTAFileType != ECU && (pOTA->deviceType == BCU || pOTA->deviceType == BMU))
    {
        CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);//0124.升级状态
        memset(&xcpstatus, 0, sizeof(XCPStatus));
        FILE *rfile = NULL;
        rfile = fopen(pOTA->OTAFilename, "rb"); // Open the file for reading in binary mode
        if(rfile == NULL)
        {
            printf("pvPortMalloc rfile space error\r\n");
    
            xcpstatus.ErrorReg |= 1 << 0;
            xcpstatus.ErrorDeviceID = pOTA->deviceID;
        }
        CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 10);//0124,升级进度
        if(xcpstatus.ErrorReg == 0)
        {
            char otafilenamestr1[OTAFILENAMEMAXLENGTH + 2] = {'\0'};
            otafilenamestr1[0] = '0';
            otafilenamestr1[1] = ':';
            memcpy(&otafilenamestr1[2], pOTA->OTAFilename, strlen(pOTA->OTAFilename));
            printf("otafilenamestr1 %s\r\n", otafilenamestr1);
            rfile = fopen(otafilenamestr1, "rb");  // "rb" = 只读，二进制
            if (rfile == NULL)
            {
                printf("%s open error, error code %d (%s)\n", otafilenamestr1, errno, strerror(errno));
                xcpstatus.ErrorReg |= 1 << 1;
                xcpstatus.ErrorDeviceID = pOTA->deviceID;
            }
            else
            {
                printf("xcpota %s open success\n", pOTA->OTAFilename);
            }

    int ret = XcpTryConnectDevice(pOTA);
    if(ret == 0)
    {
        
    }
    else
    {
        printf("XcpTryConnectDevice error, error code %d\r\n", ret);
        return 1;
    }

   ret =  XcpTryQueryStatusOnce(pOTA);
   if(ret == 0)
   {

   }
   else
   {
       printf("XcpTryQueryStatusOnce error, error code %d\r\n", ret);
      return 1;
   }

    ReadFileAndSendData(rfile,pOTA,&xcpstatus);
//    if(ret == 0)
//    {

//    }
//    else
//    {
//        printf("ReadFileAndSendData error, error code %d\r\n", ret);
//        break;
//    }

   HandleXcpCommunication(pOTA,&xcpstatus);
//    if(ret == 0)
//    {

//    }
//    else
//    {
//        printf("HandleXcpCommunication error, error code %d\r\n", ret);
//        break;
//    }

    XcpProgramResetHandler(pOTA,&xcpstatus);
    // if(ret == 0)
    // {

    // }
    // else
    // [
    //     printf("XcpSendCommandAndWait error, error code %d\r\n", ret);
    // ]

	if(xcpstatus.ErrorReg == 0)
	{
		printf("can id 0x%x device ota success!\r\n", pOTA->deviceID);
		xcpstatus.DeviceProgramOkFlag = 1;
		CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 100);//0124,升级进度
		CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASUCCESS);

	}
	else
	{
		printf("can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, xcpstatus.ErrorReg);
		CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
	}

	if(rfile != NULL)
	{
		fclose(rfile);
		rfile = NULL;
	}
	pOTA->OTAStart =0;

    }
}
}


void FinshhBCUBMUOtaAndCleanup(OTAObject* pOTA)
{
    pOTA->deviceType = 0;//停止升级
    pOTA->OTAStart = 0;
	delete_files_with_prefix("0:", "XC");//  这个要删除升级文件，判断xcpstatus状态，成功或者失败删除
	otactrl.UpDating = 0;//1130(升级结束)
	xcpstatus.CANStartOTA = 0;
	set_charger_cmd(BMS_POWER_DEFAULT);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAIDLE);
}


