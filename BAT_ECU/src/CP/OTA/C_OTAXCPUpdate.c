#define _GNU_SOURCE
#include "C_OTAXCPUpdate.h"
#include "../GLB/G_GloabalVariable.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"
#include "./DRV/Drv_ECUAndBMUCommunication.h"
#include "./GLB/G_AddressDefinition.h"
#include "./DRV/LOG/Drv_ZLog.h"
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
    // printf("XcpSendConnectCMD_%d\r\n",id);
	CanMes.Data[0] = 0xFF;
	//CanMes.Data[1] = 0x00;
	if(xcpobjectid == 0)
	{

		//xQueueSend(xQueue_forward_can_out2in,&CanMes,100/portTICK_PERIOD_MS);
		return Drv_can1_send(&CanMes);	
	}
	else
	{
        // int err = Drv_can1fd_send(&CanMes);
        // int err = Drv_can0_send(&CanMes);
        // CP_set_OTA_XCPConnect(255);
        // CP_BMSAnalysis();
        // printf("xcpobjectid %d err %d\n",xcpobjectid,err);
		return Drv_can0_send(&CanMes);
		//return CANSendMsg(BCUXCPCANID, &CanMes);
	}

}



signed char XCPCANOTAMSGParse(CAN_MESSAGE *pCANMsg, XCPStatus *pXCPStatus)
{
	if(pCANMsg == NULL || pXCPStatus== NULL)
	{
		return -1;
	}
    printf("pCANMsg->len: %d\n",pCANMsg->Length);
    printf("pCANMsg->Data[0]: %x\n",pCANMsg->Data[0]);
    printf("pCANMsg->Data[1]: %x\n",pCANMsg->Data[1]);
    // printf("pCANMsg->Data[2]: %x\n",pCANMsg->Data[2]);
    // printf("pCANMsg->Data[3]: %x\n",pCANMsg->Data[3]);
    // printf("pCANMsg->Data[4]: %x\n",pCANMsg->Data[4]);
    // printf("pCANMsg->Data[5]: %x\n",pCANMsg->Data[5]);
	if(pCANMsg->Length == 1)
	{
		if(pCANMsg->Data[0] == 0xFF)
		{
			//XXflag = 1;
			//XCPCMDResponseFlag = 1;
			pXCPStatus->XCPCMDResponseFlag = 1;
			printf("xcpstatus.XCPCMDResponseFlag -> 1\r\n");
            return 0;
		}
	}
	else if(pCANMsg->Length == 6)
	{
		pXCPStatus->XCPQUERYCMDResponseFlag = 1;
		unsigned char cmpbuf[6] ={0xFF, 0x00, 0x10, 0x00, 0x00, 0x00};
		if(memcmp(cmpbuf, pCANMsg->Data, 6) == 0)
		{
			pXCPStatus->DeviceCanProgramFlag = 1;
			printf("xcpstatus.DeviceCanProgramFlag -> 1\r\n");
            return 0;
		}

	}
	else if(pCANMsg->Length == 8)
	{
		if(pCANMsg->Data[0] == 0xFF && pCANMsg->Data[1] == 0x10)
		{
			//xxflag = 1;

			pXCPStatus->DeviceConnectedFlag = 1;
			printf("xcpstatus.DeviceConnectedFlag -> 1\r\n");
            return 0;

		}
	}
	else
	{
		printf("Unsupported xcp responsed cmd!\r\n");
		return -2;
	}

	
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
		return Drv_can1_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		
		return Drv_can0_send(&CanMes);
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
		return Drv_can1_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		
		return Drv_can0_send(&CanMes);	
	}
}



int XCPCANOTAMSGParseMult(OTAObject *pOTA,XCPStatus *xcpstatus)
{
    int xStatus;
    int err;
    struct timespec xStartTime;
    clock_gettime(CLOCK_MONOTONIC, &xStartTime);
	static CAN_MESSAGE canmsg;
	memset(&canmsg, 0, sizeof(CAN_MESSAGE));
    clock_gettime(CLOCK_MONOTONIC, &xStartTime); // 初始化起始时间戳
    // struct canfd_frame frame;
    // memset(&frame, 0, sizeof(frame));
	while (1) {

        if(pOTA->deviceType == BMU)
        {
            xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
        }
        else
        {
            xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
            // printf("frame->data[0] :%02X \r\n", canmsg.Data[0]);
            printf("queue_pend_XCPCANOTAMSGParseMult_ %d\r\n",xStatus);
        }
	    if (xStatus == 0)
	    {
	    	signed char res = XCPCANOTAMSGParse(&canmsg, xcpstatus);
            printf("xcpstatus->XCPCMDResponseFlag %d\r\n",xcpstatus->XCPCMDResponseFlag);
	        if ((res == 0) && (xcpstatus->XCPCMDResponseFlag == 1))
	        {
                printf("XCPCANOTAMSGParseMult_success\r\n");
	        	return 0;
	        }
	    }

		else if (GetTimeDifference_ms(xStartTime)>50 )//50->100
		{
            printf("XCPCANOTAMSGParseMult_timeout\r\n");
			return 1;
		}
        // usleep(10);
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
		return Drv_can1_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		
		return Drv_can0_send(&CanMes);	
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
		return Drv_can1_send(&CanMes);	
	}
	else
	{
		//return CANSendMsg(BCUXCPCANID, &CanMes);
		return Drv_can0_send(&CanMes);	
	}
}






int XcpTryConnectDevice(OTAObject *pOTA)
{
    if(xcpstatus.ErrorReg == 0)
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
                printf("pOTA->deviceID_11111111 == BMU : %x\r\n",pOTA->deviceID);
                res = XcpSendConnectCMD(pOTA->deviceID, 0);
                printf("XcpSendConnectCMD_res:%d\r\n",res);
            }
            else
            {
                // CP_set_OTA_XCPConnect(255);//发送FF至BMS进行跳转
                // CP_BMSAnalysis();
                // printf("XcpSendConnectCMD_ing\r\n");
                res = XcpSendConnectCMD(pOTA->deviceID, 1);
                // printf("XcpSendConnectCMD_end res:%d\r\n",res);
                // printf("pOTA->deviceID %d\r\n",pOTA->deviceID);
            }

            static CAN_MESSAGE canmsg;
            memset(&canmsg, 0, sizeof(CAN_MESSAGE));

            // struct canfd_frame frame;
            // memset(&frame, 0, sizeof(frame));
            usleep(2*1000);
            if(pOTA->deviceType == BMU)
            {
                xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
                printf("Xstatus %d\r\n",xStatus);
                // printf("canmsg.ID %x\r\n",canmsg.ID);
                // printf("canmsg.Data[0] %x\r\n",canmsg.Data[0]);
                // printf("canmsg.Data[1] %x\r\n",canmsg.Data[1]);
            }
            else
            {
                xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
                printf("Xstatus %d\r\n",xStatus);
            }
            
            if (xStatus == 0)
            {
                signed char res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
                if (res == 0 && xcpstatus.DeviceConnectedFlag)
                {
                    CP_set_OTA_XCPConnect(0);//跳转成功，恢复初始状态。
                    printf("Can ID 0x%x device connected!\r\n", pOTA->deviceID);
                    return 0;

                }
                else
                {
                    times++;
                    if(times >= xcpstatus.XCPCMDOuttimeTimes)
                    {
                        printf("Overtime %d times_1 ,Can ID 0x%x device connect failed!\r\n",  xcpstatus.XCPCMDOuttimeTimes, pOTA->deviceID);
                        memset(&xcpstatus, 0, sizeof(XCPStatus));
                        xcpstatus.ErrorReg |= 1 << 3;
                        xcpstatus.ErrorDeviceID = pOTA->deviceID;

                        return -1;
                    }
                }
            }

            else
            {
                times++;
                if(times >= xcpstatus.XCPCMDOuttimeTimes)
                {
                    printf("Overtime %d times_2 ,Can ID 0x%x device connect failed!\r\n", xcpstatus.XCPCMDOuttimeTimes, pOTA->deviceID);
                    memset(&xcpstatus, 0, sizeof(XCPStatus));
                    xcpstatus.ErrorReg |= 1 << 3;
                    xcpstatus.ErrorDeviceID = pOTA->deviceID;

                    return -2;
                }

            }
        }
    }
    
}




int XcpTryQueryStatusOnce(OTAObject *pOTA)
{
    if(xcpstatus.ErrorReg == 0)
    {
        int xStatus;
        int err;
        xcpstatus.XCPCMDOuttimeTimes = 5;
        xcpstatus.XCPCMDOuttimeTime = XCPOVERTIME;
        xcpstatus.XCPCMDRpeatTimes = 0;
        unsigned char tmp = 0;
        unsigned int times = 0;
        signed char res = -1;
        while(1)
        {
            if (pOTA->deviceType == BMU)
            {
                res = XcpSendQueryStatusCMD(pOTA->deviceID, 0);
            }
            else
            {
                printf("XcpSendQueryStatusCMD\r\n");
                xcpstatus.CANStartOTA = 1;
                res = XcpSendQueryStatusCMD(pOTA->deviceID, 1);
                printf("XcpSendQueryStatusCMD res :%d\r\n",res);
            }

            if (res < 0)
            {
                printf("XCP SendQueryStatusCMD error, Error code %d\r\n", res);
                xcpstatus.ErrorReg |= 1 << 4;
                xcpstatus.ErrorDeviceID = pOTA->deviceID;
                return -1;
            }


            usleep(2*1000);
            printf("xQueueReceive_ing\r\n");
            static CAN_MESSAGE canmsg;
            memset(&canmsg, 0, sizeof(CAN_MESSAGE));

            // struct canfd_frame frame;
            // memset(&frame, 0, sizeof(frame));

            if(pOTA->deviceType == BMU)
            {
                xStatus = queue_pend(&Queue_Can1RevData, &canmsg,&err);
            }
            else
            {
                xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
                // printf("canmsg->data[0] :%02X\r\n ", canmsg.Data[0]);
                // printf("canmsg->data[1] :%02X \r\n", canmsg.Data[1]);
                // printf("canmsg.data[2] :%02X\r\n ", canmsg.Data[2]);
                // printf("canmsg.data[3] :%02X \r\n", canmsg.Data[3]);
                // printf("canmsg.data[4] :%02X \r\n", canmsg.Data[4]);
                // printf("rame.data[5] :%02X \r\n", canmsg.Data[5]);
                // printf("rame.data[6] :%02X \r\n", canmsg.Data[6]);
                // printf("rame.data[7] :%02X\r\n ", canmsg.Data[7]);
                // printf("rame.data[8] :%02X \r\n", canmsg.Data[8]);

                printf("XcpTryQueryStatusOnce   recv xStatus: %d\r\n",xStatus);
            }
            if (xStatus == 0)
            {
                signed char parseRes = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
                if (parseRes == 0 && xcpstatus.DeviceCanProgramFlag)
                {
                    printf("Can ID 0x%x device can be programmed!\r\n", pOTA->deviceID);
                    return 0;
                }
                else
                {
                    times++;
                    if(times >= xcpstatus.XCPCMDOuttimeTimes)
                    {
                        printf("Overtime %d times_3 ,Can ID 0x%x device query response failed!", xcpstatus.XCPCMDOuttimeTimes, pOTA->deviceID);
                        memset(&xcpstatus, 0, sizeof(XCPStatus));
                        xcpstatus.ErrorReg |= 1 << 5;
                        xcpstatus.ErrorDeviceID = pOTA->deviceID;

                        break;
                    }
                }
            }
            else
            {
                times++;
                if(times >= xcpstatus.XCPCMDOuttimeTimes)
                {
                    printf("Overtime %d times_4 ,Can ID 0x%x device query response failed!", xcpstatus.XCPCMDOuttimeTimes, pOTA->deviceID);
                    memset(&xcpstatus, 0, sizeof(XCPStatus));
                    xcpstatus.ErrorReg |= 1 << 5;
                    xcpstatus.ErrorDeviceID = pOTA->deviceID;

                    break;
                }
            }

        }

    }
    



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

int  SendOTACommand(OTAObject *pOTA, unsigned char *buf, unsigned int len, XCPStatus *xcpstatus, unsigned int i, unsigned int totalpack, unsigned int percent_count) 
{
    if (pOTA == NULL || xcpstatus == NULL) {
            printf("Error: Null pointer passed to XCPCANOTAMSGParseMult.\n");
            return -1; 
        }

    xcpstatus->XCPCMDOuttimeTimes = 1;
    xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
    xcpstatus->XCPCMDRpeatTimes = 0;
    xcpstatus->XCPCMDResponseFlag = 0;
    signed char res;
    unsigned int times = 0;
    unsigned int per = i / percent_count;
    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, (10 + per)); // 0124, upgrade progress
    int retry_count = 0; // 用于控制最大重试次数
    while (1) 
    {
        signed char res = -1;
        if(pOTA->deviceType == BMU)
        {
            res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, len, 0);
        }
        else
        {
            res = XcpSendProgramMaxCMD(pOTA->deviceID, buf, len,1);
            printf("XcpTryProgramOnce   recv res: %d\r\n",res);
        }

        if (res != 0) {
            printf("XCP XcpSendProgramMaxCMD error, Error code %d\r\n", res);
            xcpstatus->ErrorReg |= 1 << 7;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            return 1;
        }
        // usleep(2*1000);

        int result = XCPCANOTAMSGParseMult(pOTA,xcpstatus);
        if (result == 0) {
            printf("XCP XCPCANOTAMSGParseMult   recv result: %d\r\n",result);
            // usleep(2*1000);
            return 0;
        }
        else if( (result == 1 ) && (retry_count<5))
        {
            retry_count ++;
            printf("XCP_1111111 XCPCANOTAMSGParseMult   recv result: %d, retry_count: %d\r\n",result,retry_count);
            if (retry_count < 5) {
                return 1;
            }
        }


        else
        {
            times++;
            if(times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_6 ,Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= 1 << 8;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;

                return 1;
            }

        }
    }
}



int SendLastPacket(FILE*rfile, OTAObject *pOTA, unsigned char lastpackdatanum, XCPStatus *xcpstatus) {
    signed char res;
     int xStatus;
     int err;
    unsigned char buf[7] = {0};
    size_t rnum = 0;

    // long cur_pos = ftell(rfile);
    // fseek(rfile, 0, SEEK_END);
    // long file_size = ftell(rfile);
    // fseek(rfile, cur_pos, SEEK_SET);

    // printf("file size: %ld, current pos: %ld\n", file_size, cur_pos);

     rnum = fread(buf, 1, lastpackdatanum, rfile);
    // printf("file read %d byte data success!\r\n", rnum);
    if (rnum != lastpackdatanum) {
        printf("file read %d byte data failed!\r\n", lastpackdatanum);
        xcpstatus->ErrorReg |= 1 << 6;
        xcpstatus->ErrorDeviceID = pOTA->deviceID;
    } else {
        printf("file read %d byte data success!\r\n", rnum);
    }

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
            printf("SendLastPacket XcpTryProgramOnce   recv res: %d\r\n",res);
        }
        if (res != 0) {
            printf("XCP XcpSendProgramCMD SendLastPacket error, Error code %d\r\n", res);
            xcpstatus->ErrorReg |= 1 << 11;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            return -1;
        }
        else
        {

        }

        int result = XCPCANOTAMSGParseMult(pOTA,xcpstatus);
        if (result == 0) {
            // printf("XCP XCPCANOTAMSGParseMult   recv result: %d\r\n",result);
            // usleep(2*1000);
            return 0;
        }

        // static CAN_MESSAGE canmsg;
        // memset(&canmsg, 0, sizeof(CAN_MESSAGE));

        // // struct canfd_frame frame;
        // // memset(&frame, 0, sizeof(frame));
        // usleep(1*1000);
        // if(pOTA->deviceType == BMU)
        // {
        //     xStatus =  queue_pend(&Queue_Can1RevData, &canmsg,&err);
        // }
        // else
        // {
        //     xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
        //     printf("XCP  SendLastPacket recv xStatus: %d\r\n",xStatus);
        // }

        // if (xStatus == 0) {
        //     signed char res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
        //     if(res == 0)
        //     {   printf("222222222222XCP  SendLastPacket recv res: %d\r\n",res);
        //         printf("xcpstatus->XCPCMDResponseFlag: %d\r\n",xcpstatus->XCPCMDResponseFlag);
        //         if(xcpstatus->XCPCMDResponseFlag)
        //         {
        //             printf("000000000000XCP  SendLastPacket recv res: %d\r\n",res);
        //             return 0;
        //         }
        //     }
        //     else
        //     {
        //         times++;
        //         if(times >= xcpstatus->XCPCMDOuttimeTimes)
        //         {
        //             printf("Overtime %d times_7 ,Can ID 0x%x device XcpSendProgramCMD response failed!\r\n", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
        //             memset(xcpstatus, 0, sizeof(XCPStatus));
        //             xcpstatus->ErrorReg |= 1 << 12;
        //             xcpstatus->ErrorDeviceID = pOTA->deviceID;

        //             return -2;
        //         }
        //      }
        // }
        else
        {
            times++;
            if(times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_8 ,Can ID 0x%x device XcpSendProgramCMD response failed!\r\n", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= 1 << 12;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;

               return -3;
            }

        }

    }



}

void print_timestamp_with_ms() {
    struct timeval tv;
    struct tm *tm_info;

    // 获取当前时间
    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);

    // 打印带毫秒的时间戳
    printf("%d-%02d-%02d %02d:%02d:%02d.%03ld\n",
           tm_info->tm_year + 1900,
           tm_info->tm_mon + 1,    
           tm_info->tm_mday,
           tm_info->tm_hour,
           tm_info->tm_min,
           tm_info->tm_sec,
           tv.tv_usec / 1000);      
}

int ReadFileAndSendData(FILE *rfile, OTAObject *pOTA, XCPStatus *xcpstatus) 
{
    if(xcpstatus->ErrorReg == 0 && pOTA->OTAFileType == 0)
    {
        unsigned char PrvProgramProgress = 0;
        unsigned char ProgramProgress = 0;
        int fd = fileno(rfile); 
        struct stat file_stat;
        if (fstat(fd, &file_stat) != 0) {
            perror("fstat failed");
            return 1;
        }
        unsigned int filesize = file_stat.st_size;
        printf("Bin ota file size %d\r\n", filesize);

        unsigned char lastpackdatanum = filesize % 7;
        printf("lastpackdatanum %d\r\n", lastpackdatanum);
        unsigned int totalpack = (filesize - lastpackdatanum) / 7;
        printf("totalpack %d\r\n", totalpack);
        unsigned int percent_count = totalpack / 80;
        printf("percent_count %d\r\n", percent_count);
        lastpackdatanum = filesize - (totalpack * 7);
        // usleep(2000*1000);
        printf("lastpackdatanum %d\r\n", lastpackdatanum);




        
        fseek(rfile, 0, SEEK_SET);
         
        // printf("totalpack %d, lastpackdatanum %d\r\n", totalpack, lastpackdatanum);
        
        unsigned char FileBuff[490] = {0};
        unsigned char FileCount = 0;

        if (lastpackdatanum != 0) {
            totalpack += 1;
            int i = 0;
           
            for (i = 0; i < totalpack - 1; i++) 
            {
                unsigned char buf[7] = {0};
                size_t rnum = 0;
               
                if (FileCount == 0 || FileCount >= 70) 
                {
                    int remaining_data = (totalpack - i) * 7;
                    int bytes_to_read = (remaining_data < sizeof(FileBuff)) ? remaining_data : sizeof(FileBuff);
                    rnum = fread(FileBuff, 1, bytes_to_read, rfile);
                   
                    if (rnum < 7) {
                        printf("file read 7 byte data failed! rnum: %zu\n", rnum);
                        xcpstatus->ErrorReg |= 1 << 6;
                        xcpstatus->ErrorDeviceID = pOTA->deviceID;
                       
                        return 2;
                    }
                   
                    FileCount = 0;
                }
                memcpy(buf, &FileBuff[FileCount * 7], 7);
                rnum = 7;
                FileCount++;
                int ret = SendOTACommand(pOTA, buf, 7, xcpstatus, i, totalpack, percent_count);
                printf("ret :%d\r\n",ret);
                if(xcpstatus->ErrorReg != 0)
                {
                    printf("if(xcpstatus.ErrorReg != 0)");
                    return;
                }
                ProgramProgress = (int)((float)i/totalpack*100);

                if(ProgramProgress != PrvProgramProgress)
                {
                    //RTOSDebugPrintf(".\r\n", ProgramProgress);
                }
                PrvProgramProgress = ProgramProgress;
            }
            // printf("totalpack %d, lastpackdatanum %d\r\n", totalpack, lastpackdatanum);
            if (xcpstatus->ErrorReg == 0) 
            {
                fseek(rfile, (totalpack-1)* 7, SEEK_SET);  // 设置到最后一包开头
                int ret = SendLastPacket(rfile, pOTA, lastpackdatanum, xcpstatus);
                // printf("111111111111SendLastPacket ret :%d\r\n",ret);
    

                ProgramProgress = (int)((float)i/totalpack*100);

                if(ProgramProgress != PrvProgramProgress)
                {
                    //RTOSDebugPrintf("program %d%!\r\n", ProgramProgress);
                }
                PrvProgramProgress = ProgramProgress;
            }

        } else {
            printf("Total programmax pack %d\r\n", totalpack);
            for (int i = 0; i < totalpack; i++) {
                unsigned char buf[7] = {0};
                size_t rnum = 0;
                // if (ReadFileData(rfile, FileBuff, &FileCount, totalpack, i)) {
                //     memcpy(buf, &FileBuff[FileCount * 7], 7);
                //     printf("SendOTACommand\r\n");
                //     SendOTACommand(pOTA, buf, 7, xcpstatus, i, totalpack, percent_count);
                // }
                if (FileCount == 0 || FileCount >= 70) 
                {
                    int remaining_data = (totalpack - i) * 7;
                    int bytes_to_read = (remaining_data < sizeof(FileBuff)) ? remaining_data : sizeof(FileBuff);
                    rnum = fread(FileBuff, 1, bytes_to_read, rfile);

                    if (rnum < 7) {
                        printf("file read 7 byte data failed! rnum: %zu\n", rnum);
                        xcpstatus->ErrorReg |= 1 << 6;
                        xcpstatus->ErrorDeviceID = pOTA->deviceID;
                        return 3;
                    }
                    FileCount = 0;
                }
                memcpy(buf, &FileBuff[FileCount * 7], 7);
                rnum = 7;
                FileCount++;

                SendOTACommand(pOTA, buf, 7, xcpstatus, i, totalpack, percent_count);
                ProgramProgress = (int)((float)i/totalpack*100);

                if(ProgramProgress != PrvProgramProgress)
                {

                    if(ProgramProgress == 100)
                    {
                        //printf("program 100!\r\n");
                    }
                    //printf("program %d%!\r\n", ProgramProgress);
                }
                PrvProgramProgress = ProgramProgress;
                //printf("program %d!\r\n", (int)((float)i/totalpack*100));
            }
        }
        return 0;

    }
    else
    {
        return 4;
    }
   
}





// 封装XCP命令发送和响应接收处理逻辑
static int SendXcpProgramEndCommand(OTAObject *pOTA, XCPStatus *xcpstatus) {
    signed char res = -1;
    xcpstatus->XCPCMDOuttimeTimes = 1;
    xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
    // xcpstatus->XCPCMDRpeatTimes = 0;
    xcpstatus->XCPCMDResponseFlag = 0;
     unsigned int times = 0;
    while (1)
    {
       
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
        
        int result = XCPCANOTAMSGParseMult(pOTA,xcpstatus);
        if (result == 0) {
            // printf("XCP XCPCANOTAMSGParseMult   recv result: %d\r\n",result);
            // usleep(2*1000);
            return 0;
        }
        else
        {
            times++;
            if(times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_11 ,Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= 1 << 15;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;

                return 1;
            }

        }
    }


}

// 封装响应超时和错误处理逻辑
static int HandleXcpResponseTimeout(XCPStatus *xcpstatus, OTAObject *pOTA) {
    static CAN_MESSAGE canmsg;
    int xStatus;
    int err;
    unsigned int times = 0;
    memset(&canmsg, 0, sizeof(CAN_MESSAGE));

    // struct canfd_frame frame;
    // memset(&frame, 0, sizeof(frame));

    if(pOTA->deviceType == BMU)
    {
        xStatus =  queue_pend(&Queue_Can1RevData, &canmsg,&err);
    }
    else
    {
        xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
    }    
    if (xStatus == 0) 
    {
        signed char res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
        if (res == 0 && xcpstatus->XCPCMDResponseFlag) {
            return 0; 
        }
        else
        {
            times++;
            if(times >= xcpstatus->XCPCMDOuttimeTimes)
            {
                printf("Overtime %d times_11 ,Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                memset(xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= 1 << 15;
                xcpstatus->ErrorDeviceID = pOTA->deviceID;

            return -1; 
            }
        }
        
    }
    else
    {
        
        times++;
        if (times >= xcpstatus->XCPCMDOuttimeTimes) {
            printf("Overtime %d times, Can ID 0x%x device XcpSendProgramEndCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
            memset(xcpstatus, 0, sizeof(XCPStatus));
            xcpstatus->ErrorReg |= 1 << 15;
            xcpstatus->ErrorDeviceID = pOTA->deviceID;
            return -1; 
        }
    }

}


int HandleXcpCommunication(OTAObject *pOTA, XCPStatus *xcpstatus) {
    if(xcpstatus->ErrorReg == 0)
    {
        xcpstatus->XCPCMDOuttimeTimes = 1;
        xcpstatus->XCPCMDOuttimeTime = XCPOVERTIME;
        xcpstatus->XCPCMDResponseFlag = 0;

        unsigned int times = 0;
        while (1) 
        {
            // 发送XCP命令
            int sendResult = SendXcpProgramEndCommand(pOTA, xcpstatus);
            // printf("sendResult %d\r\n", sendResult);
            if (sendResult != 0) {
                return -1;
            }
            else{
                return  0;
            }
            // usleep(2*1000);
            // // 等待并处理响应
            // int responseResult = HandleXcpResponseTimeout(xcpstatus, pOTA);
            // if (responseResult == 0) {
            //     return 0; // 成功接收到响应
            // }
            // else
            // {
            //     return -1;
            // }

           
        }

    }
    
}




signed char XcpProgramResetHandler(OTAObject *pOTA,XCPStatus *xcpstatus)
{	
    if(xcpstatus->ErrorReg == 0)
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
                memset(xcpstatus, 0, sizeof(XCPStatus));
                xcpstatus->ErrorReg |= (1 << 9);
                xcpstatus->ErrorDeviceID = pOTA->deviceID;
                return -1; // 发送失败
            }

            // static CAN_MESSAGE canmsg;
            // memset(&canmsg, 0, sizeof(CAN_MESSAGE));
            // // struct canfd_frame frame;
            // // memset(&frame, 0, sizeof(frame));
            // usleep(10*1000);

            // if(pOTA->deviceType == BMU)
            // {
            //     xStatus =  queue_pend(&Queue_Can1RevData, &canmsg,&err);
            // }
            // else
            // {
            //     xStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
            //     printf("XcpProgramResetHandler xStatus %d\r\n", xStatus);
            // }  
            // if (xStatus == 0)
            // {
            //     res = XCPCANOTAMSGParse(&canmsg, &xcpstatus);
            //     if (res == 0)
            //     {
            //         if (xcpstatus->XCPCMDResponseFlag)
            //         {
            //             CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 90); // 0124, 升级进度
            //             return 0; // 成功完成
            //         }
            //     }
            //     else
            //     {
            //         times++;
            //         if (times >= xcpstatus->XCPCMDOuttimeTimes)
            //         {
            //             printf("Overtime %d times_13, Can ID 0x%x device XcpSendProgramMaxCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
            //             memset(xcpstatus, 0, sizeof(XCPStatus));
            //             xcpstatus->ErrorReg |= (1 << 10);
            //             xcpstatus->ErrorDeviceID = pOTA->deviceID;
            //             return -2; // 超时错误
            //         }
            //     }
            // }
            int result = XCPCANOTAMSGParseMult(pOTA,xcpstatus);
            if (result == 0) {
                // printf("XCP XCPCANOTAMSGParseMult   recv result: %d\r\n",result);
                // usleep(2*1000);
                return 0;
            }
            else
            {
                times++;
                if (times >= xcpstatus->XCPCMDOuttimeTimes)
                {
                    printf("Overtime %d times_14, Can ID 0x%x device XcpSendProgramResetCMD response failed!", xcpstatus->XCPCMDOuttimeTimes, pOTA->deviceID);
                    memset(xcpstatus, 0, sizeof(XCPStatus));
                    xcpstatus->ErrorReg |= (1 << 10);
                    xcpstatus->ErrorDeviceID = pOTA->deviceID;
                    return -2; // 超时错误
                }
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
        // char filePath[256]; 
        // snprintf(filePath, sizeof(filePath), "%s/%s", USB_MOUNT_POINT, pOTA->OTAFilename);
        // printf("filePath:%s\n", filePath);
        // printf("OTAStart:%d,deviceID:%d,OTAFilename:%s,OTAFileType:%d,deviceType:%d\n", pOTA->OTAStart, pOTA->deviceID, pOTA->OTAFilename, pOTA->OTAFileType, pOTA->deviceType);
        // rfile = fopen(filePath, "rb");
        // if(rfile == NULL)
        // {
        //     printf("open %s error, error code %d (%s)\n", filePath, errno, strerror(errno));
        //     printf("open %s error, error code %d (%s)\n", pOTA->OTAFilename, errno, strerror(errno));
        //     xcpstatus.ErrorReg |= 1 << 0;
        //     xcpstatus.ErrorDeviceID = pOTA->deviceID;
        // }
        CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 10);//0124,升级进度
        if(xcpstatus.ErrorReg == 0)
        {
            char otafilenamestr1[OTAFILENAMEMAXLENGTH + 64] = {'\0'};
            // otafilenamestr1[0] = '0';
            // otafilenamestr1[1] = ':';
            snprintf(otafilenamestr1, sizeof(otafilenamestr1), "%s/%s", USB_MOUNT_POINT, pOTA->OTAFilename);
            printf("otafilenamestr1 %s\r\n", otafilenamestr1);
            printf("OTAStart:%d,deviceID:%d,OTAFilename:%s,OTAFileType:%d,deviceType:%d\n", pOTA->OTAStart, pOTA->deviceID, pOTA->OTAFilename, pOTA->OTAFileType, pOTA->deviceType);
            rfile = fopen(otafilenamestr1, "rb");  // "rb" = 只读，二进制
            if (rfile == NULL)
            {
                printf("%s open error, error code %d (%s)\n", otafilenamestr1, errno, strerror(errno));
                zlog_info(debug_out,"%s open error, error code %d %s\r\n",otafilenamestr1, errno, strerror(errno));
                xcpstatus.ErrorReg |= 1 << 1;
                xcpstatus.ErrorDeviceID = pOTA->deviceID;
            }
            else
            {
                printf("xcpota %s open success\n", pOTA->OTAFilename);
            }
        }
                
                int ret = XcpTryConnectDevice(pOTA);

                if(ret == 0)
                {
                    printf("1111111_XcpTryConnectDevice_111111\r\n");
                }
                else
                {
                    printf("1111111_XcpTryConnectDevice_111111 error, error code %d\r\n", ret);
                    zlog_info(debug_out,"1111111_XcpTryConnectDevice_111111 error, error code %d\r\n", ret);
                    // return 1;
                    return;
                }




                ret =  XcpTryQueryStatusOnce(pOTA);

                if(ret == 0)
                {
                      printf("2222222222_XcpTryQueryStatusOnce_222222222\r\n");
                }
                else
                {
                    printf("2222222222_XcpTryQueryStatusOnce_222222222 error, error code %d\r\n", ret);
                    zlog_info(debug_out,"2222222222_XcpTryQueryStatusOnce_222222222 error, error code %d\r\n", ret);
                     return;
                }



           ret =  ReadFileAndSendData(rfile,pOTA,&xcpstatus);


            if(ret == 0)
            {
                printf("333333333_ReadFileAndSendData_333333333\r\n");
            }
            else
            {
                printf("333333333_ReadFileAndSendData_333333333 error, error code %d\r\n", ret);
                zlog_info(debug_out,"333333333_ReadFileAndSendData_333333333 error, error code %d\r\n", ret);
                 return;
            }




           ret =  HandleXcpCommunication(pOTA,&xcpstatus);

            if(ret == 0)
            {
                printf("444444444_HandleXcpCommunication_44444444\r\n");
            }
            else
            {
                printf("4444444444_HandleXcpCommunication_44444444444 error, error code %d\r\n", ret);
                zlog_info(debug_out,"4444444444_HandleXcpCommunication_44444444444 error, error code %d\r\n", ret);
                 return;
            }


           ret =  XcpProgramResetHandler(pOTA,&xcpstatus);
            if(ret == 0)
            {
                printf("555555_ReadFileAndSendData_5555555\r\n");
            }
            else
            {
                printf("XcpProgramResetHandler error, error code %d\r\n", ret);
                zlog_info(debug_out,"XcpProgramResetHandler error, error code %d\r\n", ret);
                return;
            }

            if(xcpstatus.ErrorReg == 0)
            {
                printf("can id 0x%x device ota success!\r\n", pOTA->deviceID);
                zlog_info(debug_out,"can id 0x%x device ota success!\r\n", pOTA->deviceID);
                xcpstatus.DeviceProgramOkFlag = 1;
                CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 100);//0124,升级进度
                CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASUCCESS);

            }
            else
            {
                printf("can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, xcpstatus.ErrorReg);
                zlog_info(debug_out,"can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, xcpstatus.ErrorReg);
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



void FinshhBCUBMUOtaAndCleanup(OTAObject* pOTA)
{
    pOTA->deviceType = 0;//停止升级
    pOTA->OTAStart = 0;
	delete_files_with_prefix(USB_MOUNT_POINT, "XC");//  这个要删除升级文件，判断xcpstatus状态，成功或者失败删除
    delete_files_with_prefix(USB_MOUNT_POINT, "md5"); // 删除升级文件
	otactrl.UpDating = 0;//1130(升级结束)
	xcpstatus.CANStartOTA = 0;
	// set_charger_cmd(BMS_POWER_DEFAULT);
    CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAIDLE);
    Drv_BMS_Analysis();//BMS数据解析
}


