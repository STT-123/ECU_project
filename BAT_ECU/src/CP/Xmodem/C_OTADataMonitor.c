#define _GNU_SOURCE
#include "C_OTADataMonitor.h"
#include "C_OTAStateMonitor.h"
#include "./GLB/G_GloabalVariable.h"
#include "./GLB/G_AddressDefinition.h"
#include "log/log.h"
#include "./CP/OTA/C_OTAUDSUpdate.h"
#include "./CP/OTA/C_OTAXCPUpdate.h"
#include "./CP/OTA/C_OTAOtherUpdate.h"
#include "C_OTAStateMonitor.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "C_OTAStateMonitor.h"
#include "main.h"


unsigned char tcp_server_recvbuf[2048];
unsigned char tcp_server_Txbuf[256];
volatile unsigned long curmsgtimer =0 ;

const unsigned int crc_table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};


// unsigned int OsIf_GetMilliseconds(void) {
//     struct timespec now;
//     clock_gettime(CLOCK_MONOTONIC, &now);
//     return (now.tv_sec * 1000 + now.tv_nsec / 1000000);
// }


void *lwip_data_TASK(void *param)
{
	printf("lwip_data_TASK %d\r\n", otasock1);
	printf("otasock1 %d\r\n", otasock1);
	char otafilenamestr[128] = {'\0'};
	int filesize = 0;
	int xmodempacknum = 0;
	int readdatanum = 128;
	int packno = 0;
	unsigned int errpacknum = 0;
	static unsigned char findfirstpack = 0;
	unsigned char prvpackno = 0;
	unsigned char curpackno = 0;
	unsigned int packidoverflownum = 0;
	char otafilenamestr1[130] = {'\0'};
	// otafilenamestr1[0] = '0';//替换取消
	// otafilenamestr1[1] = ':';//替换取消
	unsigned char otadeviceType;
	static int filenormalflag =0;
	int errorCount = 0;
	while (1)
	{

		if(otasock1 > 0)
		{

			memset(tcp_server_recvbuf, 0, 2048);
			int length = read(otasock1, tcp_server_recvbuf, 2048);
			curmsgtimer = OsIf_GetMilliseconds();
			// printf("length :%d\r\n",length);
			if(length == 133)
			{
				if((tcp_server_recvbuf[0] == SOH)  && (crcGet(tcp_server_recvbuf, 131) == (tcp_server_recvbuf[131] << 8 | tcp_server_recvbuf[132])))
				{

					errpacknum = 0;
					tcp_server_Txbuf[0] = ACK;
					write(otasock1, tcp_server_Txbuf, 1);
					if(tcp_server_recvbuf[1] == 0x00)
					{
						printf("Received first pack !\r\n");
						setXmodemServerReceiveSOH(1);
						// XmodemServerReceiveSOH = 1;
						if(GetOTAFILEInfo(&(tcp_server_recvbuf[3]),otafilenamestr, &filesize, &xmodempacknum) == 0)
						{
							printf("File name %s filesize %d packnum %d\r\n", otafilenamestr, filesize, xmodempacknum);
							findfirstpack = 1;
							curpackno = 0;
							prvpackno = 0;
							packidoverflownum = 0;  //lx
							// memcpy(&otafilenamestr1[2], otafilenamestr, 128);//替换取消
							snprintf(otafilenamestr1, sizeof(otafilenamestr1), "%s/%s", USB_MOUNT_POINT, otafilenamestr);
	
						}

					}
					else
					{
						if(findfirstpack)
						{

							curpackno = tcp_server_recvbuf[1];

							if(curpackno == 0x01 && prvpackno == 0xff)
							{
								packidoverflownum++;
							}
							packno = tcp_server_recvbuf[1] + packidoverflownum * 255;
							printf("recv packnum = %d \r\n",packno);
							if(packno != xmodempacknum)
							{
								readdatanum = 128;
								if(packno == 1)
								{
									printf("otafilenamestr : %s\r\n",otafilenamestr);
									if(strstr(otafilenamestr, "ECU") != NULL)									
									{
										printf("otafilenamestr : %s\r\n",otafilenamestr);
										otadeviceType = ECU;
										otactrl.UpDating = 1;//1130
									}
									else if(tcp_server_recvbuf[51]==0x42 && tcp_server_recvbuf[52]==0x43 && tcp_server_recvbuf[53]==0x55 && (strstr(otafilenamestr, "BCU") != NULL))
									{

										otadeviceType = BCU;
										otactrl.UpDating = 1;//1130
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[51]);
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[52]);
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[53]);
									}
									else if(tcp_server_recvbuf[51]==0x42 && tcp_server_recvbuf[52]==0x4d && tcp_server_recvbuf[53]==0x55 && (strstr(otafilenamestr, "BMU") != NULL))
									{

										otadeviceType = BMU;
										otactrl.UpDating = 1;//1130
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[51]);
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[52]);
										printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[53]);
									}
									else if( sblfilenumber == 1)
									{
										printf("AC_OTA_FILE_DATA..... \r\n");
										otactrl.UpDating = 1;//1130

									}
									else if(strstr(otafilenamestr, "ACP") != NULL)
									{
										printf("ACP_OTA_FILE_DATA..... \r\n");
										otactrl.UpDating = 1;//1220
									}
									else if(strstr(otafilenamestr, "DCDC") != NULL)
									{
										printf("ACP_OTA_FILE_DATA..... \r\n");
										otactrl.UpDating = 1;//1220
									}

									else
									{
										otactrl.UpDating = 0;//1130
										otadeviceType = 0;
										delete_files_with_prefix("USB_MOUNT_POINT", "XC");
										printf("Invalid upgrade file\r\n");
										LOG("Invalid upgrade file\r\n");
										setXmodemServerReceiveFileEnd(1);
										// XmodemServerReceiveFileEnd = 1;
										CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
										// CP_set_charger_cmd(BMS_POWER_DEFAULT);

									}
								}

								int err = SaveOtaFile(otafilenamestr1, &(tcp_server_recvbuf[3]), xmodempacknum, packno, readdatanum);
								if(err != 0)
								{
									filenormalflag =1;
									otactrl.UpDating = 0;//1130
									otadeviceType = 0;
									if (fclose(&OTAfil) != 0)
									{
										printf("Error file close failed err code!\r\n");
										LOG("Error file close failed err code!\r\n");
									}
									else
									{
										printf("file closed successfully!\r\n");
										LOG("file closed successfully!\r\n");
									}
									delete_files_with_prefix("0:", "XC");
									printf("Failed to write upgrade file\r\n");
									LOG("Failed to write upgrade file\r\n");
									// XmodemServerReceiveFileEnd = 1;
									setXmodemServerReceiveFileEnd(1);
//									set_emcu_fault(SD_FAULT,SET_ERROR);
									CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
									CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
								}
							}
							else
							{
								filesize%128?(readdatanum = filesize%128):(readdatanum = 128);
								printf("Receive the last pack , need read %d data from xmodem data area!\r\n", readdatanum);
								int err = SaveOtaFile(otafilenamestr1, &(tcp_server_recvbuf[3]), xmodempacknum, packno, readdatanum);
								if(err != 0)
								{
									filenormalflag =1;
									otactrl.UpDating = 0;//1130
									otadeviceType = 0;
									if (fclose(&OTAfil) != 0)
									{
										printf("Error file close failed err code!\r\n");
										LOG("Error file close failed err code!\r\n");
									}
									else
									{
										printf("file closed successfully!\r\n");
										LOG("file closed successfully!\r\n");
									}
									delete_files_with_prefix("0:", "XC");
									printf("Failed to write upgrade file\r\n");
									LOG("Failed to write upgrade file\r\n");
									// XmodemServerReceiveFileEnd = 1;
									setXmodemServerReceiveFileEnd(1);
//									set_emcu_fault(SD_FAULT,SET_ERROR);
									CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
									CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
								}

								// XmodemServerReceiveFileEnd = 1;
								setXmodemServerReceiveFileEnd(1);//考虑后移动
								printf("otafilenamestr1111111 : %s\r\n",otafilenamestr1);
								if((strstr(otafilenamestr, "bin") != NULL) || (strstr(otafilenamestr1, "bz2") != NULL))
								{
									CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);
									otactrl.OTAFileType = 0;
									if(strstr(otafilenamestr, "ECU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										printf("ECU_OTA_otadeviceType: %u\r\n");
										printf("otafilenamestr: %u\r\n",otafilenamestr);
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
										// snprintf(otactrl.OTAFilename, sizeof(otactrl.OTAFilename), "%s/%s", USB_MOUNT_POINT, otafilenamestr);
										// EMS_OTA_SD_ready_func(otactrl.OTAFilename);    //EMS的SD卡OTA升级功能
										otactrl.OTAStart = 1;

									}
									else if(strstr(otafilenamestr, "BCU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										otactrl.deviceID = BCUOTACANID;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));

										otactrl.OTAStart = 1;
									}
									else if(strstr(otafilenamestr, "BMU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
										otactrl.deviceID = 0x1821FF10;
										otactrl.OTAStart = 1;
									}
									else if(strstr(otafilenamestr, "ACP") != NULL)
									{
										otactrl.deviceType = ACP;//1126
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
										otactrl.deviceID = ACPOTACANID;
										otactrl.OTAStart = 1;

									}
									else if(strstr(otafilenamestr, "DCDC") != NULL)
									{
										otactrl.deviceType = DCDC;//1126
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
										otactrl.deviceID = DCDCOTACANID;
										otactrl.OTAStart = 1;
									}
									//------------------------------OTAACP----------------------------------------//
									else if(strstr(otafilenamestr, "AC") != NULL)
									{
									    char *token;
									    char *delimiter = "_";
										CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEDECRYPTIONNORMALTERMINATION);

										otactrl.OTAFileType = 0;
										if(strstr(otafilenamestr, "AC_SBL") != NULL)
										{
											clock_gettime(CLOCK_MONOTONIC, &AC_OTA_lastCheckTick);
											memset(otactrl.OTAUdsSblFilename[SBl_index],0 ,sizeof(otactrl.OTAUdsSblFilename[SBl_index]));
											//需要告诉我一共分成多少bin文件，然后达到数量后赋值otactrl.deviceType = ACP;，进入XcpOTATestTask
											printf("AC_SBL_OTA_FILE_NAME: %s\r\n", otafilenamestr);
											printf("AC_SBL_OTA_FILE_NAME: %s\r\n", otafilenamestr1);
											memcpy(otactrl.OTAUdsSblFilename[SBl_index], otafilenamestr1, strlen(otafilenamestr1));

										    token = strtok(otafilenamestr, delimiter); // AC
										    token = strtok(NULL, delimiter);          // SBL
											token = strtok(NULL, delimiter);
											flashData.writeAddr =(uint32_t)strtoul(token, NULL, 16);
											token = strtok(NULL, delimiter);
											flashData.writeLen =(uint32_t)strtoul(token, NULL, 16);
											token = strtok(NULL, delimiter);
											flashData.CRC =(uint16_t)strtoul(token, NULL, 16);
											printf("otactrl.OTAUdsSblFilename[SBl_index]: %s!\r\n", otactrl.OTAUdsSblFilename[SBl_index]);
											printf("flashData.writeAddr: 0x%08X\r\n", flashData.writeAddr);
											printf("flashData.writeLen: 0x%08X\r\n", flashData.writeLen);
											printf("flashData.CRC: 0x%04X\r\n", flashData.CRC);
											printf("SBl_index: %d\r\n", SBl_index);
											SBl_index++;

										}

										else if(strstr(otafilenamestr, "AC_APP") != NULL)
										{
												clock_gettime(CLOCK_MONOTONIC, &AC_OTA_lastCheckTick);
												memset(otactrl.OTAUdsFilename[APP_index],0 ,sizeof(otactrl.OTAUdsFilename[APP_index]));
												printf("AC_APP_OTA_FILE_NAME: %s\r\n", otafilenamestr);
												printf("AC_SBL_OTA_FILE_NAME: %s\r\n", otafilenamestr1);
												memcpy(otactrl.OTAUdsFilename[APP_index], otafilenamestr1, strlen(otafilenamestr1));

											    token = strtok(otafilenamestr, delimiter); // AC
											    token = strtok(NULL, delimiter);          // SBL
												token = strtok(NULL, delimiter);
												appData[APP_index].writeAddr =(uint32_t)strtoul(token, NULL, 16);
												token = strtok(NULL, delimiter);
												appData[APP_index].writeLen =(uint32_t)strtoul(token, NULL, 16);
												token = strtok(NULL, delimiter);
												appData[APP_index].CRC =(uint16_t)strtoul(token, NULL, 16);
												printf("otactrl.OTAUdsFilename[APP_index]: %s\r\n", otactrl.OTAUdsFilename[APP_index]);
												printf("appData.writeAddr[APP_index]: 0x%08X\r\n", appData[APP_index].writeAddr);
												printf("appData.writeLen[APP_index]: 0x%08X\r\n", appData[APP_index].writeLen);
												printf("appData.CRC[APP_index]: 0x%04X!\r\n", appData[APP_index].CRC);
												printf("APP_index: %d\r\n", APP_index);
												APP_index++;

										}

									}
										CP_get_modbus_reg_val(AC_SBL_OTAFILENUMBER, &sblfilenumber);
										CP_get_modbus_reg_val(AC_APP_OTAFILENUMBER, &appfilenumber);
										usleep(50*1000);
										printf("SBl_index ...  %d \r\n",SBl_index);
										printf("APP_index ...  %d \r\n",APP_index);
										printf("sblfilenumber...%d\r\n",sblfilenumber);
										printf("appfilenumber...%d\r\n",appfilenumber);


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
									//------------------------------OTAACP----------------------------------------//

									else
									{

									}
									printf("OTAStart:%d,deviceID:%d,OTAFilename:%s,OTAFileType:%d,deviceType:%d\n", otactrl.OTAStart, otactrl.deviceID, otactrl.OTAFilename, otactrl.OTAFileType, otactrl.deviceType);

								}
								else if(strstr(otafilenamestr, "srec") != NULL || strstr(otafilenamestr, "s19") != NULL)
								{
									CP_set_modbus_reg_val(OTASTATUSREGADDR, FILEISDECRYPTIIONING);
									otactrl.OTAFileType = 1;
									if(strstr(otafilenamestr, "ECU") != NULL)
									{
										otactrl.deviceType = ECU;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else if(strstr(otafilenamestr, "BCU") != NULL)
									{
										otactrl.deviceType = BCU;
										otactrl.deviceID = BCUOTACANID;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else if(strstr(otafilenamestr, "BMU") != NULL)
									{
										otactrl.deviceType = BMU;
										otactrl.deviceID = 0x1821FF10;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else
									{

									}
								}
	

							}
							prvpackno = curpackno;

						}
					}

				}
				else
				{
					errpacknum++;
					tcp_server_Txbuf[0] = NAK;
					write(otasock1, tcp_server_Txbuf, 1);
				}
			}
			else if(length == 1029)
			{
				if((tcp_server_recvbuf[0] == STX) && (crcGet(tcp_server_recvbuf, 1027) == (tcp_server_recvbuf[1025] << 8 | tcp_server_recvbuf[1026])))
				{

					errpacknum = 0;
					tcp_server_Txbuf[0] = ACK;
					write(otasock1, tcp_server_Txbuf, 1);
					// if(tcp_server_recvbuf[1] == 0x00)
					// {
					// 	printf("Received first pack !\r\n");

					// 	XmodemServerReceiveSOH = 1;
					// 	if(GetOTAFILEInfo(&(tcp_server_recvbuf[3]),1024,otafilenamestr, &filesize, &xmodempacknum) == 0)
					// 	{
					// 		printf("File name %s filesize %d packnum %d\r\n", otafilenamestr, filesize, xmodempacknum);
					// 		findfirstpack = 1;
					// 		curpackno = 0;
					// 		prvpackno = 0;
					// 		packidoverflownum = 0;  //lx
					// 		memcpy(&otafilenamestr1[2], otafilenamestr, 128);
					// 	}

					// }


					if(findfirstpack)
					{
						curpackno = tcp_server_recvbuf[1];

						if(curpackno == 0x01 && prvpackno == 0xff)
						{
							packidoverflownum++;
						}
						packno = tcp_server_recvbuf[1] + packidoverflownum * 255;
						if(packno != xmodempacknum - 1)
						{
							readdatanum = 1024;
							if(packno == 1)
							{
								if(strstr(otafilenamestr, "ECU") != NULL)									
								{
									otadeviceType = ECU;
									otactrl.UpDating = 1;//1130
								}
								else if(tcp_server_recvbuf[51]==0x42 && tcp_server_recvbuf[52]==0x43 && tcp_server_recvbuf[53]==0x55)
								{
									otadeviceType = BCU;
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[51]);
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[52]);
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[53]);
								}
								else if(tcp_server_recvbuf[51]==0x42 && tcp_server_recvbuf[52]==0x4d && tcp_server_recvbuf[53]==0x55)
								{
									otadeviceType = BMU;
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[51]);
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[52]);
									printf("As hexadecimal10: 0x%X\n", tcp_server_recvbuf[53]);
								}
								else
								{
									delete_files_with_prefix(USB_MOUNT_POINT, "XC");
									otadeviceType = 0;
									printf("Invalid upgrade file\r\n");
									setXmodemServerReceiveFileEnd(1);
									// XmodemServerReceiveFileEnd = 1;
								}
							}
							int err = SaveOtaFile(otafilenamestr, &(tcp_server_recvbuf[3]), xmodempacknum, packno, readdatanum);
							if(err != 0)
							{
								filenormalflag =1;
								otactrl.UpDating = 0;//1130
								otadeviceType = 0;
								if (fclose(&OTAfil) != 0)
								{
									printf("Error file close failed err code!\r\n");
									LOG("Error file close failed err code!\r\n");
								}
								else
								{
									printf("file closed successfully!\r\n");
									LOG("file closed successfully!\r\n");
								}
								delete_files_with_prefix("0:", "XC");
								printf("Failed to write upgrade file\r\n");
								LOG("Failed to write upgrade file\r\n");
								// XmodemServerReceiveFileEnd = 1;
								setXmodemServerReceiveFileEnd(1);
//									set_emcu_fault(SD_FAULT,SET_ERROR);
								CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
								CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
							}
						}
						else
						{

							filesize%1024?(readdatanum = filesize%1024):(readdatanum = 1024);
							printf("Receive the last pack , need read %d data from xmodem data area!\r\n", readdatanum);
							int err = SaveOtaFile(otafilenamestr, &(tcp_server_recvbuf[3]), xmodempacknum, packno, readdatanum);
							if(err != 0)
							{
								filenormalflag =1;
								otactrl.UpDating = 0;//1130
								otadeviceType = 0;
								if (fclose(&OTAfil) != 0)
								{
									printf("Error file close failed err code!\r\n");
									LOG("Error file close failed err code!\r\n");
								}
								else
								{
									printf("file closed successfully!\r\n");
									LOG("file closed successfully!\r\n");
								}
								delete_files_with_prefix("0:", "XC");
								printf("Failed to write upgrade file\r\n");
								LOG("Failed to write upgrade file\r\n");
								// XmodemServerReceiveFileEnd = 1;
								setXmodemServerReceiveFileEnd(1);
//									set_emcu_fault(SD_FAULT,SET_ERROR);
								CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
								CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
							}
							setXmodemServerReceiveFileEnd(1);
							// XmodemServerReceiveFileEnd = 1;

							if(strstr(otafilenamestr1, "bin") != NULL)
								{
									otactrl.OTAFileType = 0;
									if(strstr(otafilenamestr1, "ECU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));

									}
									else if(strstr(otafilenamestr1, "BCU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else if(strstr(otafilenamestr1, "BMU") != NULL)
									{
										otactrl.deviceType = otadeviceType;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else
									{

									}
								}
								else if(strstr(otafilenamestr1, "srec") != NULL)
								{
									otactrl.OTAFileType = 1;
									if(strstr(otafilenamestr1, "ECU") != NULL)
									{
										otactrl.deviceType = ECU;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));

									}
									else if(strstr(otafilenamestr1, "BCU") != NULL)
									{
										otactrl.deviceType = BCU;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else if(strstr(otafilenamestr1, "BMU") != NULL)
									{
										otactrl.deviceType = BMU;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));
									}
									else
									{

									}
								}
								else if(strstr(otafilenamestr1, "zip") != NULL)
								{
									otactrl.OTAFileType = 0;
									if(strstr(otafilenamestr1, "ECU") != NULL)
									{
										printf("ECU tar.bz2 file\r\n");
										LOG("ECU tar.bz2 file\r\n");
										otactrl.deviceType = otadeviceType;
										memset(otactrl.OTAFilename ,0 ,sizeof(otactrl.OTAFilename));
										memcpy(otactrl.OTAFilename, otafilenamestr, strlen(otafilenamestr));

									}
									else
									{

									}
								}

						}



					}
				}
				else
				{
					errpacknum++;
					tcp_server_Txbuf[0] = NAK;
					write(otasock1, tcp_server_Txbuf, 1);
				}

			}
			else if(length == 1)
			{
				printf("Rcv 1 byte data -> 0x%x\r\n", tcp_server_recvbuf[0]);
				if(tcp_server_recvbuf[0] == EOT)
				{
					setXmodemServerReceiveEOT(1);
					// XmodemServerReceiveEOT = 1;
				}

			}

			else if(length == -1 || length == 0)
			{
			    errorCount++;

			    if (errorCount >= 10)
			    {

					setXmodemServerReceiveFileEnd(1);
			        // XmodemServerReceiveFileEnd = 1;
			        otactrl.UpDating = 0;//1130

			    }
			}
			else
			{
			    errorCount = 0;
			}



		}

		if(errpacknum > 5)
		{
			printf("error pack over 5!\r\n");
			setXmodemServerEnd(1);
			// XmodemServerEnd = 1;

		}
		if(getXmodemServerReceiveFileEnd())
		{
			printf("receive file end!\r\n");
			uint32_t starttime = OsIf_GetMilliseconds();
			while(1)
			{
				uint32_t time = OsIf_GetMilliseconds()-starttime;

				{
					printf("wait XmodemServerReceiveEOT over !\r\n");
					// XmodemServerEnd = 1;
					// XmodemServerReceiveEOT = 0;
					// XmodemServerReceiveFileEnd = 0;
					setXmodemServerEnd(1);
					setXmodemServerReceiveEOT(0);
					setXmodemServerReceiveFileEnd(0);
					break;
				}
				if(time >= 10000)
				{
					tcp_server_Txbuf[0] = CAN;
					write(otasock1, tcp_server_Txbuf, 1);
					printf("wait XmodemServerReceiveEOT over 10s exit!\r\n");
					// XmodemServerEnd = 1;
					// XmodemServerReceiveEOT = 0;
					// XmodemServerReceiveFileEnd = 0;
					setXmodemServerEnd(1);
					setXmodemServerReceiveEOT(0);
					setXmodemServerReceiveFileEnd(0);
					break;

				}
				usleep(100*1000);

			}

		}

		usleep(100*1000);
	}


}








signed char GetOTAFILEInfo(unsigned char *databuf, char *name, int *filesize, int *xmodempacknum)

{
	char namebuf[128] = {'\0'};
	char filesizebuf[128] = {'\0'};
	char filepacknumbuf[128] = {'\0'};
	//unsigned char ctrflag = 0;
	int idx = 0;
	int idx1 = 0;
	unsigned short i = 0;
	if(databuf == NULL)
	{
		printf("databuf null\r\n");
		return -1;
	}

	for( i = 0; i < 128; i++)
	{

		if(databuf[i] == 0x00)
		{
			//printf("find 0x00\r\n");
			idx++;
		}
		else
		{

		}
		if(idx == 1)
		{
			//printf("Find file name end idx %d\r\n");
			idx1 = i;
			for(int j = 0; j < idx1 + 2; j++)
			{
				namebuf[j] = databuf[idx + j - 1];
			}
			//memPrint(namebuf, 16, 128);
			memcpy(name, namebuf, 128);
			//name = namebuf;
			//sprintf(name, "%s", namebuf);
			//for(i = 0)
			//printf("Find file name %s\r\n", namebuf);

		}
		else if(idx == 3)
		{

			for(int j = 0; j < i - idx1 - 2; j++)
			{
				filesizebuf[j] = databuf[idx1 + j + 2];
			}
			idx += 1;
			idx1 = i;
			//memPrint(filesizebuf, 16, 128);
			//printf("Find file size %s\r\n", filesizebuf);

		}

		else if(idx == 5)
		{
			for(int j = 0; j < i - idx1 - 1; j++)
			{
				filepacknumbuf[j] = databuf[idx1 + j + 1];
			}
			idx1 = i;
			//memPrint(filepacknumbuf, 16, 128);
			//printf("Find file pack num %s\r\n", filepacknumbuf);
			break;
		}

	}
	 if (sscanf(filesizebuf, "%d", filesize) == 1)
	 {
		 //printf(" filesize %s->%d success \r\n", filesize);
	 }
	 else
	{
		printf("filesize %s->%d error \r\n");
		return -2;
	}
	if (sscanf(filepacknumbuf, "%d", xmodempacknum) == 1)
	{
		//printf(" xmodempacknum %s->%d success \r\n", xmodempacknum);
	}
	else
	{
		printf("xmodempacknum %s->%d error \r\n");
		return -3;
	}

	return 0;

}



int switch_to_root_directory(void) {
    char current_path[PATH_MAX];


    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        perror("Failed to get current working directory");
        return errno;
    }


    if (strcmp(current_path, "/") != 0) {
        if (chdir("/") == 0) {
            printf("Changed to root directory.\n");
        } else {
            perror("Failed to change to root directory");
            return errno;
        }
    } else {
        // printf("Already in root directory.\n");
    }

    return 0; 
}


signed char SaveOtaFile(char *name, unsigned char *buf, int totalpacknum, int curpackno, int datanum)
{
    int writebytenum = 0;

    if(name == NULL || buf == NULL)
    {
        return -1;
    }
	switch_to_root_directory();
    // 如果文件还没打开，打开它（第一次包）
    if(OTAfil == NULL)
    {
        OTAfil = fopen(name, "wb+");
        if(OTAfil == NULL)
        {
            perror("Error creating OTA file");
            return -4;
        }
        else
        {
            printf("file create successfully!\n");
        }
    }

    writebytenum = fwrite(buf, 1, datanum, OTAfil);
    if(writebytenum != datanum)
    {
        printf("xmodem write file %s error! Expected %d bytes, wrote %d bytes\n", name, datanum, writebytenum);
        return -2;
    }

    if(fflush(OTAfil) != 0)
    {
        perror("File synchronization failure");
        return -3;
    }

    if(curpackno == totalpacknum)
    {
        printf("The last pack!\n");
        if(fclose(OTAfil) != 0)
        {
            perror("close ota file error");
            OTAfil = NULL;
            return -5;
        }
        OTAfil = NULL; // 记得清空指针
    }

    return 0;
}



unsigned short crcGet(unsigned char *ptr, int len)
{
    unsigned short crc = 0x0000;

    while(len--)
    {
        crc = (crc << 8) ^ crc_table[(crc >> 8 ^ *ptr++) & 0xff];
    }

    return(crc);
}



void delete_files_with_prefix(const char *path, const char *prefix) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filepath[512];

        // Skip directories
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(filepath, &st) == -1) {
            perror("stat failed");
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            continue;
        }

        // Check prefix match
        if (strncmp(prefix, entry->d_name, strlen(prefix)) == 0) {
            if (unlink(filepath) == 0) {
                printf("Deleted: %s\n", filepath);
            } else {
                perror("Failed to delete file");
                printf("Filename: %s\n", filepath);
            }
        }
    }

    closedir(dir);
}
