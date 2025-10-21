#include "C_OTAUDSUpdate.h"
#include "../GLB/G_GloabalVariable.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"
#include "./GLB/G_AddressDefinition.h"
// #include "../CP/BMS/bms/bms_cortol.h"
#include "./Xmodem/C_OTADataMonitor.h"
#include "./Xmodem/C_OTAStateMonitor.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "log/log.h"
#include "main.h"
flashDataType flashData;
appDataType appData[SUP_MAX_BLOCK + 1];
// unsigned short sblfilenumber = 0xFFFF;//SBL文件数量大小
// unsigned short appfilenumber = 0xFFFF;//app文件数量大小
// int SBl_index = 0;
// int APP_index = 0;

UDSStatus udsstatus;
bool getSeedToKey(uint32_t seed, uint32_t *key)
{
    uint32_t MASK = 0x20204143;
    uint32_t wSeed = seed;

    if (wSeed != 0U)
    {
        for (int i = 0; i < 35; i++)
        {
            if (wSeed & 0x80000000)
            {
                wSeed = wSeed << 1;
                wSeed = wSeed ^ MASK;
            }
            else
            {
                wSeed = wSeed << 1;
            }
        }
        *key = wSeed;
        return true;
    }

    return false;
}

signed char udsServer3E(unsigned int id)
{
	int TStatus;
	CAN_MESSAGE CanMes;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 3;
	CanMes.ID = id;
	CanMes.Data[0] = 0x02;
	CanMes.Data[1] = 0x3e;
	CanMes.Data[2] = 0x80;

	TStatus = Drv_can0_send(&CanMes);
	 usleep(100*1000);
	 usleep(100*1000);
	if(TStatus ==0)
	{
		return 0;
	}
	else
	{
		return 1;//失败
	}
}


signed char udsServer10(unsigned int id, uint8_t session)
{
	unsigned int times = 0;
	int TStatus;
	int UStatus;
	int err;
	CAN_MESSAGE CanMes;
	CAN_MESSAGE canmsg;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 3;
	CanMes.ID = id;
	CanMes.Data[0] = 0x02;
	CanMes.Data[1] = 0x10;
	CanMes.Data[2] = session;

    udsstatus.udsServerID = 0x10;
    udsstatus.udsSession = session;

	TStatus = Drv_can0_send(&CanMes);	
	if(TStatus ==0)
	{	//接收CAN消息，秘钥，是否超时或者否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(80*1000);
		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus ==0)
		{
			printf("canmsg.Data[0] :%02x\r\n", canmsg.Data[0] );
			printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[1] );
			printf("canmsg.Data[2] :%02x\r\n", canmsg.Data[2] );
			printf("canmsg.Data[3] :%02x\r\n", canmsg.Data[3] );
			printf("canmsg.Data[4] :%02x\r\n", canmsg.Data[4] );
			printf("canmsg.Data[5] :%02x\r\n", canmsg.Data[5] );
			if (canmsg.Data[1] == 0x50) {
				printf("udsstatus.udsReturnSuccess = true");
				udsstatus.udsReturnSuccess = true;
				return 0;
			            }
			else
			{
				printf("udsServer10 Return false\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 1;
				return 1;
			}
		}
		else
		{
			printf("udsstatus.ErrorReg = 2\r\n");
			udsstatus.ErrorReg = 2;
			return 1;
		}



	}
	else
	{
		printf("udsstatus.ErrorReg = 3\r\n");
		udsstatus.ErrorReg = 3;
		return 1;
	}

}



signed char udsServer27(unsigned int id, uint8_t session)
{
	CAN_MESSAGE CanMes;
	CAN_MESSAGE CanMes_1;
	CAN_MESSAGE canmsg;
	unsigned int times = 0;
	int TStatus;
	int UStatus;
	int err;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 3;
	CanMes.ID = id;
	CanMes.Data[0] = 0x02;
	CanMes.Data[1] = 0x27;
	CanMes.Data[2] = session;
	if(session == 1)
	{
		CanMes.Data[0] = 0x02;
	    udsstatus.udsServerID = 0x10;
	    udsstatus.udsSession = session;


//		printf("CanMes.Data[0]: 0x%08X\n", CanMes.Data[0]);
//		printf("CanMes.Data[1]: 0x%08X\n", CanMes.Data[1]);
//		printf("CanMes.Data[2]: 0x%08X\n", CanMes.Data[2]);
//		printf("CanMes.Data[3]: 0x%08X\n", CanMes.Data[3]);
//		printf(" CanMes.Data[4]: 0x%08X\n",  CanMes.Data[4]);
//		printf(" CanMes.Data[5]: 0x%08X\n",  CanMes.Data[5]);
//		printf(" CanMes.Data[6]: 0x%08X\n",  CanMes.Data[6]);
//		printf(" CanMes.Data[7]: 0x%08X\n",  CanMes.Data[7]);

	    TStatus = Drv_can0_send(&CanMes);
		if(TStatus ==0)
		{	//接收CAN消息，秘钥，是否超时或者否定回复
			memset(&canmsg, 0, sizeof(CAN_MESSAGE));
			usleep(80*1000);
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
			if(UStatus ==0)
			{
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[0] );
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[1] );
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[2] );
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[3] );
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[4] );
				printf("canmsg.Data[1] :%02x\r\n", canmsg.Data[5] );
				if (canmsg.Data[1] == 0x67) {
					printf("0x67: = pdpass \r\n");
				        if (canmsg.Data[2] == 0x00) {
				            // 情况 1：不需要种子值，直接成功
				            udsstatus.seedValue = 0xFFFFFFFF;
				            printf("udsstatus.seedValue_000: 0x%08X\n", udsstatus.seedValue);
				            udsstatus.udsReturnSuccess = true;
				        }
				        else if (canmsg.Data[2] == 0x01) {
				            // 情况 2：返回种子值
				            udsstatus.seedValue = (canmsg.Data[3] << 24) | (canmsg.Data[4] << 16) | (canmsg.Data[5] << 8) | canmsg.Data[6];
				            printf("udsstatus.seedValue_111: 0x%08X\n", udsstatus.seedValue);
				            udsstatus.udsReturnSuccess = true;
				        }
				        else if (canmsg.Data[2] == 0x02) {
				            // 情况 3：秘钥验证成功
				            udsstatus.udsReturnSuccess = true;
				            printf("秘钥验证成功！\n");
				        }
						else
						{
							printf("udsServer27 Return_1 false\r\n");
							udsstatus.udsReturnSuccess = false;
							udsstatus.ErrorReg = 4;
							return 1;
						}
				    }
				else
				{
					printf("udsServer27 Return_1 false\r\n");
					udsstatus.udsReturnSuccess = false;
					udsstatus.ErrorReg = 4;
					return 1;

				}
			}


		}

		else
		{
			printf("udsstatus.ErrorReg = 5\r\n");
			udsstatus.ErrorReg = 5;
			return 1;
		}



        if(udsstatus.seedValue == 0xffffffff)
        {
        	printf("udsstatus.seedValue == 0xffffffff\r\n");

//			udsstatus.ErrorReg = 3;

            return 0 ;//安全模式下也认为是成功的//1225
        }

        usleep(100*1000);
        uint32_t seedKey = 0;
        getSeedToKey(udsstatus.seedValue,&seedKey);
        printf("SeedKey: 0x%08X\n", seedKey);

    	memset(&CanMes_1, 0 , sizeof(CAN_MESSAGE));
    	CanMes_1.Extended = 1;
    	CanMes_1.Length = 7;
    	CanMes_1.ID = id;
    	CanMes_1.Data[0] = 0x06;
    	CanMes_1.Data[1] = 0x27;
    	CanMes_1.Data[2] = 0x02;
    	CanMes_1.Data[3] = seedKey >> 24;
    	CanMes_1.Data[4] = seedKey >> 16;
    	CanMes_1.Data[5] = seedKey >> 8;
    	CanMes_1.Data[6] = seedKey >> 0;
		udsstatus.udsServerID = 0x27;
		udsstatus.udsSession = 0x02;
//		printf("CanMes_1.Data[0]: 0x%08X\n", CanMes_1.Data[0]);
//		printf("CanMes_1.Data[1]: 0x%08X\n", CanMes_1.Data[1]);
//		printf("CanMes_1.Data[2]: 0x%08X\n", CanMes_1.Data[2]);
//		printf("CanMes_1.Data[3]: 0x%08X\n", CanMes_1.Data[3]);
//		printf(" CanMes_1.Data[4]: 0x%08X\n",  CanMes_1.Data[4]);
//		printf(" CanMes_1.Data[5]: 0x%08X\n",  CanMes_1.Data[5]);
//		printf(" CanMes_1.Data[6]: 0x%08X\n",  CanMes_1.Data[6]);
//		printf(" CanMes_1.Data[7]: 0x%08X\n",  CanMes_1.Data[7]);

		TStatus = Drv_can0_send(&CanMes_1);
		if(TStatus ==0)
		{	//接收CAN消息，秘钥，是否超时或者否定回复
			memset(&canmsg, 0, sizeof(CAN_MESSAGE));
			usleep(80*1000);
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
			if(UStatus ==0)
			{
				printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1] );
				if (canmsg.Data[1] == 0x67) {
					printf("0x67: = pdpass \r\n");
				        if (canmsg.Data[2] == 0x00) {
				            // 情况 1：不需要种子值，直接成功
				            udsstatus.seedValue = 0xFFFFFFFF;
				            printf("udsstatus.seedValue_000: 0x%08X\n", udsstatus.seedValue);
				            udsstatus.udsReturnSuccess = true;
				        }
				        else if (canmsg.Data[2] == 0x01) {
				            // 情况 2：返回种子值
				            udsstatus.seedValue = (canmsg.Data[3] << 24) | (canmsg.Data[4] << 16) | (canmsg.Data[5] << 8) | canmsg.Data[6];
				            printf("udsstatus.seedValue_111: 0x%08X\n", udsstatus.seedValue);
				            udsstatus.udsReturnSuccess = true;

				        }
				        else if (canmsg.Data[2] == 0x02) {
				            // 情况 3：秘钥验证成功
				            udsstatus.udsReturnSuccess = true;
				            printf("The secret key was validated successfully！\n");
				            return 0;
				        }
						else
						{
							printf("udsServer27 Return_2 false\r\n");
							udsstatus.udsReturnSuccess = false;
							udsstatus.ErrorReg = 6;
							return 1;
						}
				    }
			}
			else
			{
				printf("udsstatus.ErrorReg = 7\r\n");
				udsstatus.ErrorReg = 7;
				return 1;
			}


		}

		else
		{
			printf("udsstatus.ErrorReg = 8\r\n");
			udsstatus.ErrorReg = 8;
			return 1;
		}


	}



}




signed char udsServer31(unsigned int id, uint32_t addr, uint32_t len)
{

	CAN_MESSAGE CanMes;
	CAN_MESSAGE CanMes_1;
	unsigned int times = 0;
	CAN_MESSAGE canmsg;
	int TStatus;
	int UStatus;
	int err;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 8;
	CanMes.ID = id;
	CanMes.Data[0] = 0x10;
	CanMes.Data[1] = 0x0d;
	CanMes.Data[2] = 0x31;
	CanMes.Data[3] = 0x01;
	CanMes.Data[4] = 0xff;
	CanMes.Data[5] = 0x00;
	CanMes.Data[6] = 0x44;

	CanMes.Data[7] = addr>>24;

	printf("send can0 CanMes:%x %x %x %x %x %x %x %x %x\n",CanMes.ID,CanMes.Data[0],CanMes.Data[1],CanMes.Data[2],CanMes.Data[3],CanMes.Data[4],CanMes.Data[5],CanMes.Data[6],CanMes.Data[7]);

    udsstatus.udsServerID = 0x31;
    udsstatus.udsSession = 0x00;
    // while((queue_pend(&Queue_Can0RevData, &canmsg,&err)));//过滤到其他消息
	queue_clear(&Queue_Can0RevData);
    TStatus = Drv_can0_send(&CanMes);
    if(TStatus ==0)
    {

		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(300*1000);
		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus ==0)
		{
			printf("canmsg.Data[0] :%d\r\n", canmsg.Data[0] );
			if (canmsg.Data[0] == 0x30) {

				udsstatus.udsReturnSuccess = true;
			}
			else
			{
				printf("udsServer31 Return_1 false\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 9;
				return 1;
			}
		}
		else
		{
			printf("udsstatus.ErrorReg = 10\r\n");
			udsstatus.ErrorReg = 10;
			return 1;
		}
    }
	else
	{
		printf("udsstatus.ErrorReg = 11\r\n");
		udsstatus.ErrorReg = 11;
		return 1;
	}

    usleep(50*1000);
	memset(&CanMes_1, 0 , sizeof(CAN_MESSAGE));
	CanMes_1.Extended = 1;
	CanMes_1.Length = 8;
	CanMes_1.ID = id;
	CanMes_1.Data[0] = 0x21;


	CanMes_1.Data[1] = addr>>16;
	CanMes_1.Data[2] = addr>>8;
	CanMes_1.Data[3] = addr>>0;
	CanMes_1.Data[4] = len>>24;
	CanMes_1.Data[5] = len>>16;
	CanMes_1.Data[6] = len>>8;
	CanMes_1.Data[7] = len>>0;
	printf("send can0 CanMes_1: %x %x %x %x %x %x %x %x\n",CanMes_1.ID,CanMes_1.Data[0],CanMes_1.Data[1],CanMes_1.Data[2],CanMes_1.Data[3],CanMes_1.Data[4],CanMes_1.Data[5],CanMes_1.Data[6]);


//     TStatus = Drv_can0_send(&CanMes_1);
//     if(TStatus ==0)
//     {
//     	//接收CAN消息，秘钥，是否超时或者否定回复
// 		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
// 		usleep(500*1000);
// 		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
// 		if(UStatus == 0)
// 		{
// //			usleep(100);
// 			printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1] );
// 			if (canmsg.Data[1] == 0x71) {

// 				udsstatus.udsReturnSuccess = true;
// 				return 0;
// 			}
// 			else
// 			{
// 				printf("udsServer31 Return_2 false\r\n");
// 				udsstatus.udsReturnSuccess = false;
// 				udsstatus.ErrorReg = 12;
// 				return 1;
// 			}


// 		}
// 		else
// 		{
// 			printf("udsstatus.ErrorReg = 13\r\n");
// 			udsstatus.ErrorReg = 13;
// 			printf("canrevmsg0.Data[0] :%d\r\n", canmsg.Data[0] );
// 			printf("canrevmsg1.Data[0] :%d\r\n", canmsg.Data[1] );
// 			printf("canrevmsg2.Data[0] :%d\r\n", canmsg.Data[2] );
// 			printf("canrevmsg3.Data[0] :%d\r\n", canmsg.Data[3] );
// 			printf("canrevmsg4.Data[0] :%d\r\n", canmsg.Data[4] );
// 			printf("canrevmsg5.Data[0] :%d\r\n", canmsg.Data[5] );
// 			printf("canrevmsg6.Data[0] :%d\r\n", canmsg.Data[6] );
// 			printf("canrevmsg7.Data[0] :%d\r\n", canmsg.Data[7] );
// 			return 1;
// 		}


//     }
// 	else
// 	{
// 		printf("udsstatus.ErrorReg = 14\r\n");
// 		udsstatus.ErrorReg = 14;
// 		return 1;
// 	}


	TStatus = Drv_can0_send(&CanMes_1);
	if (TStatus == 0)
	{
		// 接收CAN消息，秘钥，是否超时或者否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(50 * 1000);

		int retry_count = 0;
		do {
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg, &err);
			if (UStatus == 0)
			{
				printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1]);
				if (canmsg.Data[1] == 0x71)
				{
					udsstatus.udsReturnSuccess = true;
					return 0;
				}
				else
				{
					printf("udsServer31 Return_2 false\r\n");
					udsstatus.udsReturnSuccess = false;
					udsstatus.ErrorReg = 12;
					return 1;
				}
			}
			else
			{
				retry_count++;
				usleep(50 * 1000);  // 等待100ms
			}
		} while (UStatus != 0 && retry_count < 10);

		// 超过重试次数仍失败
		printf("udsstatus.ErrorReg = 13\r\n");
		udsstatus.ErrorReg = 13;
		printf("canrevmsg0.Data[0] :%d\r\n", canmsg.Data[0]);
		printf("canrevmsg1.Data[0] :%d\r\n", canmsg.Data[1]);
		printf("canrevmsg2.Data[0] :%d\r\n", canmsg.Data[2]);
		printf("canrevmsg3.Data[0] :%d\r\n", canmsg.Data[3]);
		printf("canrevmsg4.Data[0] :%d\r\n", canmsg.Data[4]);
		printf("canrevmsg5.Data[0] :%d\r\n", canmsg.Data[5]);
		printf("canrevmsg6.Data[0] :%d\r\n", canmsg.Data[6]);
		printf("canrevmsg7.Data[0] :%d\r\n", canmsg.Data[7]);
		return 1;
	}
	else
	{
		printf("udsstatus.ErrorReg = 14\r\n");
		udsstatus.ErrorReg = 14;
		return 1;
	}


}





signed char udsServer31_2(unsigned int id, uint32_t addr)
{

	CAN_MESSAGE CanMes;
	unsigned int times = 0;
	CAN_MESSAGE canmsg;
	int TStatus;
	int UStatus;
	int err;
	CAN_MESSAGE CanMes_1;

	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 8u;
	CanMes.ID = id;
	CanMes.Data[0] = 0x10;
	CanMes.Data[1] = 0x0d;
	CanMes.Data[2] = 0x31;
	CanMes.Data[3] = 0x01;
	CanMes.Data[4] = 0xff;
	CanMes.Data[5] = 0x02;
	CanMes.Data[6] = 0x44;
	CanMes.Data[7] = addr>>24;



    udsstatus.udsServerID = 0x31;
    udsstatus.udsSession = 0x00;

   TStatus = Drv_can0_send(&CanMes);
    if(TStatus ==0)
    {

		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(300*1000);
		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus ==0)
		{
			printf("canmsg.Data[0] :%d\r\n", canmsg.Data[0] );
			if (canmsg.Data[0] == 0x30) {

				udsstatus.udsReturnSuccess = true;
			}
			else
			{
				printf("udsServer32_2 Return_1 false\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 15;
				return 1;
			}
		}
		else
		{
			printf("udsstatus.ErrorReg = 16\r\n");
			udsstatus.ErrorReg = 16;
			return 1;
		}
    }
	else
	{
		printf("udsstatus.ErrorReg = 17\r\n");
		udsstatus.ErrorReg = 17;
		return 1;
	}

    usleep(50*1000);
	memset(&CanMes_1, 0 , sizeof(CAN_MESSAGE));
	CanMes_1.Extended = 1;
	CanMes_1.Length = 8U;
	CanMes_1.ID = id;
	CanMes_1.Data[0] = 0x21;
	CanMes_1.Data[1] = addr>>16;
	CanMes_1.Data[2] = addr>>8;
	CanMes_1.Data[3] = addr>>0;
	printf("CanMes_1.Data[0]: %x\n", CanMes_1.Data[0]);
	printf("CanMes_1.Data[1]: %x\n", CanMes_1.Data[1]);
	printf("CanMes_1.Data[2]: %x\n", CanMes_1.Data[2]);
	printf("CanMes_1.Data[3]: %x\n", CanMes_1.Data[3]);
	printf(" CanMes_1.Data[4]: %x\n",  CanMes_1.Data[4]);
	printf(" CanMes_1.Data[5]: %x\n",  CanMes_1.Data[5]);
	printf(" CanMes_1.Data[6]: %x\n",  CanMes_1.Data[6]);
	printf(" CanMes_1.Data[7]: %x\n",  CanMes_1.Data[7]);
// 	TStatus = Drv_can0_send(&CanMes_1);
// 	if(TStatus ==0)
// 	{
//    	//接收CAN消息，秘钥，是否超时或者否定回复
// 		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
// 		usleep(300*1000);
// 		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
// 		if(UStatus == 0)
// 		{
// 			printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1] );
// 			if (canmsg.Data[1] == 0x71) {

// 				udsstatus.udsReturnSuccess = true;
// 				return 0;
// 			}
// 			else
// 			{
// 				printf("udsServer31_2 Return_2 false\r\n");
// 				udsstatus.udsReturnSuccess = false;
// 				udsstatus.ErrorReg = 18;
// 				return 1;
// 			}


// 		}

// 		else
// 		{
// 			printf("udsstatus.ErrorReg = 19\r\n");
// //			udsstatus.ErrorReg = 19;
// //			printf("canrevmsg0.Data[0] :%d\r\n", canmsg.Data[0] );
// //			printf("canrevmsg1.Data[0] :%d\r\n", canmsg.Data[1] );
// //			printf("canrevmsg2.Data[0] :%d\r\n", canmsg.Data[2] );
// //			printf("canrevmsg3.Data[0] :%d\r\n", canmsg.Data[3] );
// //			printf("canrevmsg4.Data[0] :%d\r\n", canmsg.Data[4] );
// //			printf("canrevmsg5.Data[0] :%d\r\n", canmsg.Data[5] );
// //			printf("canrevmsg6.Data[0] :%d\r\n", canmsg.Data[6] );
// //			printf("canrevmsg7.Data[0] :%d\r\n", canmsg.Data[7] );
// //			return 1;
// 		}



//    }
// 	else
// 	{
// 		printf("udsstatus.ErrorReg = 20\r\n");
// 		udsstatus.ErrorReg = 20;
// 		return 1;
// 	}

	TStatus = Drv_can0_send(&CanMes_1);
	if (TStatus == 0)
	{
		// 接收CAN消息，秘钥，是否超时或者否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(300 * 1000);  // 初始等待 300ms

		int retry_count = 0;
		while (retry_count < 10)
		{
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg, &err);
			if (UStatus == 0)
			{
				printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1]);
				if (canmsg.Data[1] == 0x71)
				{
					udsstatus.udsReturnSuccess = true;
					return 0;
				}
				else
				{
					printf("udsServer31_2 Return_2 false\r\n");
					udsstatus.udsReturnSuccess = false;
					udsstatus.ErrorReg = 18;
					return 1;
				}
			}
			else
			{
				retry_count++;
				usleep(50 * 1000);  // 重试前等待100ms
			}
		}

		// 超过三次仍然接收失败
		// printf("queue_pend 失败超过3次，退出，udsstatus.ErrorReg = 19\r\n");
		udsstatus.udsReturnSuccess = false;
		// udsstatus.ErrorReg = 19;
		return 1;
	}
	else
	{
		printf("Drv_can0_send 发送失败，udsstatus.ErrorReg = 20\r\n");
		udsstatus.ErrorReg = 20;
		return 1;
	}


}



signed char udsServer34(unsigned int id, uint32_t addr,uint32_t len)
{
	CAN_MESSAGE CanMes_1;
	CAN_MESSAGE CanMes;
	unsigned int times = 0;
	CAN_MESSAGE canmsg;
	int TStatus;
	int UStatus;
	int err;

	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 8U;
	CanMes.ID = id;
	CanMes.Data[0] = 0x10;
	CanMes.Data[1] = 0x0b;
	CanMes.Data[2] = 0x34;
	CanMes.Data[3] = 0x00;
	CanMes.Data[4] = 0x44;
	CanMes.Data[5] = addr >> 24;
	CanMes.Data[6] = addr >> 16;
	CanMes.Data[7] = addr >> 8;


	printf(" CanMes.Data[0]:%02x\r\n",CanMes.Data[0]);
	printf(" CanMes.Data[1]:%02x\r\n",CanMes.Data[1]);
	printf(" CanMes.Data[2]:%02x\r\n",CanMes.Data[2]);
	printf(" CanMes.Data[3]:%02x\r\n",CanMes.Data[3]);
	printf(" CanMes.Data[4]:%02x\r\n",CanMes.Data[4]);
	printf(" CanMes.Data[5]:%02x\r\n",CanMes.Data[5]);
	printf(" CanMes.Data[6]:%02x\r\n",CanMes.Data[6]);
	printf(" CanMes.Data[7]:%02x\r\n",CanMes.Data[7]);


    udsstatus.udsServerID = 0x34;
    udsstatus.udsSession = 0x00;

   TStatus = Drv_can0_send(&CanMes);
	if(TStatus ==0)
	{
		//接收CAN消息，秘钥，是否超时或者否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(80*1000);
		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus ==0)
		{
			printf("canmsg.Data[0] :%d\r\n", canmsg.Data[0] );
			if (canmsg.Data[0] == 0x30) {

				udsstatus.udsReturnSuccess = true;
			}
			else
			{
				printf("udsServer34 Return_1 false\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 21;
				return 1;
			}
		}
		else
		{
			printf("udsstatus.ErrorReg = 22\r\n");
			udsstatus.ErrorReg = 22;
			return 1;
		}

	}
	else
	{
		printf("udsstatus.ErrorReg = 23\r\n");
		udsstatus.ErrorReg = 23;
		return 1;
	}

	usleep(100*1000);

	memset(&CanMes_1, 0 , sizeof(CAN_MESSAGE));
	CanMes_1.Extended = 1;
	CanMes_1.Length = 8U;
	CanMes_1.ID = id;

	CanMes_1.Data[0] = 0x21;
	CanMes_1.Data[1] = addr>>0;
	CanMes_1.Data[2] = len>>24;
	CanMes_1.Data[3] = len>>16;
	CanMes_1.Data[4] = len>>8;
	CanMes_1.Data[5] = len>>0;
	printf(" 1111CanMes.Data[0]:%02x\r\n",CanMes_1.Data[0]);
	printf(" 1111CanMes.Data[1]:%02x\r\n",CanMes_1.Data[1]);
	printf(" 1111CanMes.Data[2]:%02x\r\n",CanMes_1.Data[2]);
	printf(" 1111CanMes.Data[3]:%02x\r\n",CanMes_1.Data[3]);
	printf(" 1111CanMes.Data[4]:%02x\r\n",CanMes_1.Data[4]);
	printf(" 1111CanMes.Data[5]:%02x\r\n",CanMes_1.Data[5]);
	printf(" 1111CanMes.Data[6]:%02x\r\n",CanMes_1.Data[6]);
	printf(" 1111CanMes.Data[7]:%02x\r\n",CanMes_1.Data[7]);
    TStatus = Drv_can0_send(&CanMes_1);
	if(TStatus ==0)
	{
		//接收CAN消息，秘钥，是否超时或者否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));
		usleep(80*1000);
		UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus == 0)
		{
			printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1] );
			if (canmsg.Data[1] == 0x74) {

				udsstatus.udsReturnSuccess = true;
				return 0;
			}
			else
			{
				printf("udsServer34 Return_2 false\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 24;
				return 1;
			}


		}
		else
		{
			printf("udsstatus.ErrorReg = 25\r\n");
			udsstatus.ErrorReg = 25;
			return 1;
		}


	}
	else
	{
		printf("udsstatus.ErrorReg = 26\r\n");
		udsstatus.ErrorReg = 26;
		return 1;
	}


}



#define BLOCK_SIZE 1024
#define FRAME_SIZE 8
signed char  udsServer36(uint32_t id, const char *filename,FILE *rfile) {
    uint8_t sendBuf[BLOCK_SIZE + FRAME_SIZE]; // 存放每个分块的数据
    uint8_t fileBuffer[BLOCK_SIZE];          // 用于存放从文件中读取的原始数据
    uint32_t totalCount = 0;                 // 文件总长度
    uint32_t sendSuccessCount = 0;           // 已发送的字节数
    uint16_t blockCount = 0;                 // 块数量
    unsigned int bytesRead;


    CAN_MESSAGE canmsg;
    CAN_MESSAGE CanMes;
    CAN_MESSAGE CanMes_1;
	int TStatus;
	int UStatus;
	int err;
	printf("filename:%s\r\n",filename);
    // 打开文件
    rfile = fopen(filename, "rb");
    if (rfile == NULL) {
		printf("open file error\r\n");
        udsstatus.ErrorReg = 1;
        return 1;
    }
    // 获取文件大小
	fseek(rfile, 0, SEEK_END);
    totalCount = ftell(rfile);
    fseek(rfile, 0, SEEK_SET);
    printf("Bin OTA file size: %d\r\n", totalCount);
    blockCount = (totalCount + BLOCK_SIZE - 1) / BLOCK_SIZE;
    printf("blockCount : %d\r\n", blockCount);

    for (uint16_t count = 0; count < blockCount; count++) {
    	uint8_t byte = 1;
    	uint16_t blockSizeSet = 0;//当前数据帧的长度
    	uint32_t blockSize = 0;

        memset(fileBuffer, 0, BLOCK_SIZE);

        // 从文件中读取数据
     	bytesRead = fread(fileBuffer, 1, BLOCK_SIZE, rfile);
        if (bytesRead <= 0) {
            udsstatus.ErrorReg = 2;
            fclose(rfile);
            return 1;
        }

        printf("bytesRead : %d\r\n", bytesRead);

        blockSize = bytesRead -4;
        printf("blockSize : %d\r\n", blockSize);
        blockSizeSet = bytesRead +2;
        printf("blockSizeSet : %d\r\n", blockSizeSet);


        uint16_t zhengshu = blockSize / 7;
        printf("zhengshu : %d\r\n", zhengshu);


        uint16_t yushu = blockSize % 7;
        printf("yushu : %d\r\n", yushu);

        // 发送第一帧数据
        sendBuf[0] = (0x10 | ((blockSizeSet >> 8) & 0x0F));
        sendBuf[1] = (blockSizeSet & 0xFF);
        sendBuf[2] = 0x36;
        sendBuf[3] = count + 1;
        memcpy(&sendBuf[4], fileBuffer, 4);
        printf("sendBuf[0]: %02x\r\n", sendBuf[0]);
        printf("sendBuf[1]: %02x\r\n", sendBuf[1]);
        printf("sendBuf[2]: %02x\r\n", sendBuf[2]);



        memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
        CanMes.Extended = 1;
        CanMes.Length = 8U;
        CanMes.ID = id;
        memcpy(CanMes.Data, sendBuf, 8);

		printf(" CanMes.Data[0]:%02x\r\n",CanMes.Data[0]);
		printf(" CanMes.Data[1]:%02x\r\n",CanMes.Data[1]);
		printf(" CanMes.Data[2]:%02x\r\n",CanMes.Data[2]);
		printf(" CanMes.Data[3]:%02x\r\n",CanMes.Data[3]);
		printf(" CanMes.Data[4]:%02x\r\n",CanMes.Data[4]);
		printf(" CanMes.Data[5]:%02x\r\n",CanMes.Data[5]);
		printf(" CanMes.Data[6]:%02x\r\n",CanMes.Data[6]);
		printf(" CanMes.Data[7]:%02x\r\n",CanMes.Data[7]);

//        TStatus = xQueueSend(xQueue_forward_can_out2in,&CanMes,1000/portTICK_PERIOD_MS);
		int reva = Drv_can0_send(&CanMes);
		if(reva == 0)
		{
			//发送成功

			//接收CAN消息，秘钥，是否超时或者否定回复
			memset(&canmsg, 0, sizeof(CAN_MESSAGE));
			usleep(80*1000);
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
			if(UStatus == 0)
			{
				//usleep(50);
				printf("canrevmsg0.Data[0] :%d\r\n", canmsg.Data[0] );
				printf("canrevmsg1.Data[0] :%d\r\n", canmsg.Data[1] );
				printf("canrevmsg2.Data[0] :%d\r\n", canmsg.Data[2] );
				printf("canrevmsg3.Data[0] :%d\r\n", canmsg.Data[3] );
				printf("canrevmsg4.Data[0] :%d\r\n", canmsg.Data[4] );
				printf("canrevmsg5.Data[0] :%d\r\n", canmsg.Data[5] );
				printf("canrevmsg6.Data[0] :%d\r\n", canmsg.Data[6] );
				printf("canrevmsg7.Data[0] :%d\r\n", canmsg.Data[7] );

				if (canmsg.Data[0] == 0x30) {
					printf("canmsg00000000000.Data[0] :%d\r\n", canmsg.Data[0] );
					udsstatus.udsReturnSuccess = true;

				}
				else
				{
					printf("udsServer36 Return false ErrorReg = 27\r\n");
					udsstatus.udsReturnSuccess = false;
					udsstatus.ErrorReg = 27;
					fclose(rfile);
					return 1;//1223
				}


			}
			else
			{
				printf("udsstatus.ErrorReg = 28\r\n");
				udsstatus.ErrorReg = 28;
				fclose(rfile);
				return 1;
			}



		}
		else
		{
			usleep(10*1000);
			//发送失败
			printf("send failed, reva: %d\r\n",reva);
			for (int i = 0; i < 3; i++) {
				reva = Drv_can0_send(&CanMes);
				usleep(10*1000);
				if (reva == 0) {
					// 发送成功


					//接收CAN消息，秘钥，是否超时或者否定回复
					memset(&canmsg, 0, sizeof(CAN_MESSAGE));
					usleep(80*1000);
					UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
					if(UStatus == 0)
					{
						//usleep(50);
						printf("canrevmsg0.Data[0] :%d\r\n", canmsg.Data[0] );
						printf("canrevmsg1.Data[0] :%d\r\n", canmsg.Data[1] );
						printf("canrevmsg2.Data[0] :%d\r\n", canmsg.Data[2] );
						printf("canrevmsg3.Data[0] :%d\r\n", canmsg.Data[3] );
						printf("canrevmsg4.Data[0] :%d\r\n", canmsg.Data[4] );
						printf("canrevmsg5.Data[0] :%d\r\n", canmsg.Data[5] );
						printf("canrevmsg6.Data[0] :%d\r\n", canmsg.Data[6] );
						printf("canrevmsg7.Data[0] :%d\r\n", canmsg.Data[7] );

						if (canmsg.Data[0] == 0x30) {
							printf("canmsg00000000000.Data[0] :%d\r\n", canmsg.Data[0] );
							udsstatus.udsReturnSuccess = true;

						}
						else
						{
							printf("udsServer36 Return false ErrorReg = 27\r\n");
							udsstatus.udsReturnSuccess = false;
							udsstatus.ErrorReg = 27;
							fclose(rfile);
							return 1;//1223
						}


					}
					else
					{
						printf("udsstatus.ErrorReg = 28\r\n");
						udsstatus.ErrorReg = 28;
						fclose(rfile);
						return 1;
					}


					break;
				} else {
					// 发送失败
					printf("udsstatus.ErrorReg = 29\r\n");
					udsstatus.ErrorReg = 29;
					fclose(rfile);
					return 1;
					printf("send failed, reva: %d, retry: %d\r\n", reva, i + 1);
				}
			}
		}

        udsstatus.sendCount += 4;

        // 循环发送每7字节的数据帧
//        uint8_t frameBuf[FRAME_SIZE];
        for (uint16_t i = 0; i < zhengshu; i++) {
        	usleep(10*1000);

        	CanMes.Data[0] = (0x20 | (byte & 0x0F));
            memcpy(&CanMes.Data[1], &fileBuffer[4 + i * 7], 7);
//            memcpy(CanMes.Data, frameBuf, 8);
			int reva = Drv_can0_send(&CanMes);
			if(reva == 0)
			{
				//发送成功
			}
			else
			{
				usleep(10*1000);
				//发送失败
				printf("send failed, reva: %d\r\n",reva);
				for (int i = 0; i < 3; i++) {
					reva = Drv_can0_send(&CanMes);
					usleep(10*1000);
					if (reva == 0) {
						// 发送成功
						break;
					} else {
						// 发送失败
						 fclose(rfile);
						return 1;
						printf("send failed, reva: %d, retry: %d\r\n", reva, i + 1);
					}
				}
			}

//            TStatus = xQueueSend(xQueue_forward_can_out2in,&CanMes,1000/portTICK_PERIOD_MS);
//            if (TStatus != pdPASS) {
//                f_close(rfile);
//                return 1;
//            }
            udsstatus.sendCount += 7;
            byte++;
        }

        // 发送余下不足7字节的数据帧
        if (yushu > 0) {
            memset(&CanMes_1, 0 , sizeof(CAN_MESSAGE));
            CanMes_1.Extended = 1;
            CanMes_1.Length = yushu+1;
            CanMes_1.ID = id;

//            memset(frameBuf, 0, FRAME_SIZE);
            CanMes_1.Data[0] =(0x20 | (byte & 0x0F));
            memcpy(&CanMes_1.Data[1], &fileBuffer[4 + zhengshu * 7], (yushu));

//            memcpy(CanMes_1.Data, frameBuf, (yushu+1));
    		printf(" CanMes_1.Data[0]:%02x\r\n",CanMes_1.Data[0]);
    		printf(" CanMes_1.Data[1]:%02x\r\n",CanMes_1.Data[1]);
    		printf(" CanMes_1.Data[2]:%02x\r\n",CanMes_1.Data[2]);
    		printf(" CanMes_1.Data[3]:%02x\r\n",CanMes_1.Data[3]);
    		printf(" CanMes_1.Data[4]:%02x\r\n",CanMes_1.Data[4]);
    		printf(" CanMes_1.Data[5]:%02x\r\n",CanMes_1.Data[5]);
    		printf(" CanMes_1.Data[6]:%02x\r\n",CanMes_1.Data[6]);
    		printf(" CanMes_1.Data[7]:%02x\r\n",CanMes_1.Data[7]);
			int reva = Drv_can0_send(&CanMes_1);
			if(reva == 0)
			{
				//发送成功
			}
			else
			{
				usleep(2*1000);
				//发送失败
				printf("send failed, reva: %d\r\n",reva);
				for (int i = 0; i < 3; i++) {
					reva = Drv_can0_send(&CanMes_1);
					usleep(10*1000);
					if (reva == 0) {
						// 发送成功
						break;
					} else {
						// 发送失败
						 fclose(rfile);
						return 1;
						printf("send failed, reva: %d, retry: %d\r\n", reva, i + 1);
					}
				}
			}
            udsstatus.sendCount += yushu+1;
        }

        // 等待响应
		usleep(150*1000);
        UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
		if(UStatus == 0)
		{
			printf("canrev0.Data[0] :%x\r\n", canmsg.Data[0] );
			printf("canrev1.Data[0] :%x\r\n", canmsg.Data[1] );
			printf("canrev2.Data[0] :%x\r\n", canmsg.Data[2] );
			printf("canrev3.Data[0] :%x\r\n", canmsg.Data[3] );
			printf("canrev4.Data[0] :%x\r\n", canmsg.Data[4] );
			printf("canrev5.Data[0] :%x\r\n", canmsg.Data[5] );
			printf("canrev6.Data[0] :%x\r\n", canmsg.Data[6] );
			printf("canrev7.Data[0] :%x\r\n", canmsg.Data[7] );
			if (canmsg.Data[1] == 0x76) {

				udsstatus.udsReturnSuccess = true;

			}
			else
			{
				printf("udsServer36 Return false ErrorReg = 30\r\n");
				udsstatus.udsReturnSuccess = false;
				udsstatus.ErrorReg = 30;
				fclose(rfile);
				return 1;
			}
		}
		else
		{
			printf("udsstatus.ErrorReg = 31\r\n");
			udsstatus.ErrorReg = 31;
			fclose(rfile);
			return 1;
		}



		// int retry_count = 0;
		// while (retry_count < 10)
		// {
		// 	UStatus = queue_pend(&Queue_Can0RevData, &canmsg, &err);
		// 	if (UStatus == 0)
		// 	{
		// 		// 打印接收到的CAN数据
		// 		printf("canrev0.Data[0] :%x\r\n", canmsg.Data[0]);
		// 		printf("canrev1.Data[0] :%x\r\n", canmsg.Data[1]);
		// 		printf("canrev2.Data[0] :%x\r\n", canmsg.Data[2]);
		// 		printf("canrev3.Data[0] :%x\r\n", canmsg.Data[3]);
		// 		printf("canrev4.Data[0] :%x\r\n", canmsg.Data[4]);
		// 		printf("canrev5.Data[0] :%x\r\n", canmsg.Data[5]);
		// 		printf("canrev6.Data[0] :%x\r\n", canmsg.Data[6]);
		// 		printf("canrev7.Data[0] :%x\r\n", canmsg.Data[7]);

		// 		if (canmsg.Data[1] == 0x76)
		// 		{
		// 			udsstatus.udsReturnSuccess = true;
		// 			return 0;
		// 		}
		// 		else
		// 		{
		// 			printf("udsServer36 Return false ErrorReg = 30\r\n");
		// 			udsstatus.udsReturnSuccess = false;
		// 			udsstatus.ErrorReg = 30;
		// 			fclose(rfile);
		// 			return 1;
		// 		}
		// 	}

		// 	retry_count++;
		// 	usleep(50 * 1000);  // 每次失败后延时100ms
		// }

		// // 超过三次重试仍失败
		// printf("udsstatus.ErrorReg = 31\r\n");
		// udsstatus.ErrorReg = 31;
		// fclose(rfile);
		// return 1;


    }

    fclose(rfile);
    return 0;
}




signed char udsServer37(unsigned int id, uint16_t crc_value)
{
	CAN_MESSAGE CanMes;
	CAN_MESSAGE CanMes_1;
	CAN_MESSAGE canmsg;
	int TStatus;
	int UStatus;
	int err;
	memset(&CanMes, 0 , sizeof(CAN_MESSAGE));
	CanMes.Extended = 1;
	CanMes.Length = 8;
	CanMes.ID = id;
	CanMes.Data[0] = 0x03;
	CanMes.Data[1] = 0x37;
	CanMes.Data[2] = 0x9C;
	CanMes.Data[3] = 0x56;

	CanMes.Data[2] = crc_value>>8;
	CanMes.Data[3] = crc_value>>0;

    udsstatus.udsServerID = 0x37;
    udsstatus.udsSession = 0x00;
    udsstatus.userData = crc_value;
    printf(" crc_value:%02x\r\n",crc_value);
	printf(" 1111CanMes.Data[0]:%02x\r\n",CanMes.Data[0]);
	printf(" 1111CanMes.Data[1]:%02x\r\n",CanMes.Data[1]);
	printf(" 1111CanMes.Data[2]:%02x\r\n",CanMes.Data[2]);
	printf(" 1111CanMes.Data[3]:%02x\r\n",CanMes.Data[3]);
	printf(" 1111CanMes.Data[4]:%02x\r\n",CanMes.Data[4]);
	printf(" 1111CanMes.Data[5]:%02x\r\n",CanMes.Data[5]);
	printf(" 1111CanMes.Data[6]:%02x\r\n",CanMes.Data[6]);
	printf(" 1111CanMes.Data[7]:%02x\r\n",CanMes.Data[7]);

    // TStatus = Drv_can0_send(&CanMes);
    // if(TStatus == 0)
    // {
    // 	//接收CAN消息，秘钥，是否超时或者否定回复
	// 	memset(&canmsg, 0, sizeof(CAN_MESSAGE));
	// 	UStatus = queue_pend(&Queue_Can0RevData, &canmsg,&err);
	// 	printf("canmsg.Data[0]:%02x\r\n",canmsg.Data[0]);
	// 	printf(" canmsg.Data[1]:%02x\r\n",canmsg.Data[1]);
	// 	printf(" canmsg.Data[2]:%02x\r\n",canmsg.Data[2]);
	// 	printf(" canmsg.Data[3]:%02x\r\n",canmsg.Data[3]);
	// 	printf(" canmsg.Data[4]:%02x\r\n",canmsg.Data[4]);
	// 	printf(" canmsg.Data[5]:%02x\r\n",canmsg.Data[5]);
	// 	printf(" canmsg.Data[6]:%02x\r\n",canmsg.Data[6]);
	// 	printf(" canmsg.Data[7]:%02x\r\n",canmsg.Data[7]);
	// 	if(UStatus == 0)
	// 	{

	// 		printf("canmsg.Data[1] :%d\r\n", canmsg.Data[1] );
	// 		if (canmsg.Data[1] == 0x77) {
	// 			 uint16_t received_crc = (canmsg.Data[4] << 8) | canmsg.Data[5];
	// 			 printf(" received_crc:%02x\r\n",received_crc);
	// 			    if (received_crc == crc_value) {
	// 			        udsstatus.udsReturnSuccess = true;
	// 			        return 0;
	// 			    }
	// 			    else
	// 			    {
	// 					printf("udsServer37 Return false\r\n");
	// 					udsstatus.udsReturnSuccess = false;
	// 			    	udsstatus.ErrorReg = 32;
	// 			    	return 1;
	// 			    }
	// 		}
	// 		else
	// 		{
	// 			printf("udsServer37 Return false\r\n");
	// 			udsstatus.udsReturnSuccess = false;
	// 			udsstatus.ErrorReg = 32;
	// 			return 1;
	// 		}


	// 	}
	// 	else
	// 	{
	// 		printf("udsstatus.ErrorReg = 32\r\n");
	// 		udsstatus.ErrorReg = 33;
	// 		return 1;
	// 	}
    // }

	// else
	// {
	// 	printf("udsstatus.ErrorReg = 33\r\n");
	// 	udsstatus.ErrorReg = 34;
	// 	return 1;
	// }
	TStatus = Drv_can0_send(&CanMes);
	if (TStatus == 0)
	{
		// 接收CAN消息，验证秘钥，判断是否超时或否定回复
		memset(&canmsg, 0, sizeof(CAN_MESSAGE));

		int retry_count = 0;
		while (retry_count < 20)
		{
			UStatus = queue_pend(&Queue_Can0RevData, &canmsg, &err);

			// 打印接收数据内容
			printf("canmsg.Data[0]:%02x\r\n", canmsg.Data[0]);
			printf(" canmsg.Data[1]:%02x\r\n", canmsg.Data[1]);
			printf(" canmsg.Data[2]:%02x\r\n", canmsg.Data[2]);
			printf(" canmsg.Data[3]:%02x\r\n", canmsg.Data[3]);
			printf(" canmsg.Data[4]:%02x\r\n", canmsg.Data[4]);
			printf(" canmsg.Data[5]:%02x\r\n", canmsg.Data[5]);
			printf(" canmsg.Data[6]:%02x\r\n", canmsg.Data[6]);
			printf(" canmsg.Data[7]:%02x\r\n", canmsg.Data[7]);

			if (UStatus == 0)
			{
				printf("canmsg.Data[1] :%x\r\n", canmsg.Data[1]);
				if (canmsg.Data[1] == 0x77)
				{
					uint16_t received_crc = (canmsg.Data[4] << 8) | canmsg.Data[5];
					printf(" received_crc:%02x\r\n", received_crc);
					if (received_crc == crc_value)
					{
						udsstatus.udsReturnSuccess = true;
						return 0;
					}
					else
					{
						printf("udsServer37 CRC校验失败\r\n");
						udsstatus.udsReturnSuccess = false;
						udsstatus.ErrorReg = 32;
						printf("ErrorReg = %d\r\n", udsstatus.ErrorReg);
						return 1;
					}
				}
				else
				{
					printf("udsServer37 Data[1] != 0x77\r\n");
					udsstatus.udsReturnSuccess = false;
					udsstatus.ErrorReg = 32;
					printf("ErrorReg = %d\r\n", udsstatus.ErrorReg);
					return 1;
				}
			}
			else
			{
				retry_count++;
				usleep(50 * 1000); // 100ms 延时
			}
		}

		// 如果超过3次仍然失败
		printf("queue_pend 失败超过3次，退出\r\n");
		udsstatus.ErrorReg = 33;
		printf("ErrorReg = %d\r\n", udsstatus.ErrorReg);
		return 1;
	}
	else
	{
		printf("Drv_can0_send 发送失败\r\n");
		udsstatus.ErrorReg = 34;
		printf("ErrorReg = %d\r\n", udsstatus.ErrorReg);
		return 1;
	}

}





void CP_UDS_OTA(OTAObject* pOTA)
{
	printf("pOTA->OTAStart %d \r\n",pOTA->OTAStart);
    if (!pOTA->OTAStart) return;
	printf(" pOTA->OTAUdsFilename[0] :%s \r\n", pOTA->OTAUdsFilename[0]);
	printf(" pOTA->deviceID :%d\r\n", pOTA->deviceID);
	printf(" pOTA->OTAFileType :%d \r\n", pOTA->OTAFileType);
    if(pOTA->deviceID != 0 && pOTA->OTAUdsFilename[0] != 0 && pOTA->deviceType == AC && pOTA->OTAStart ==1 && (SBl_index != 0) && (SBl_index == sblfilenumber) && (APP_index != 0) && (APP_index == appfilenumber))
    {
		int count = 0;
		FILE *rfile =NULL;
        CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASTARTRUNNING);//0124.升级状态
        memset(&udsstatus, 0, sizeof(UDSStatus));
		printf("pOTA->OTAFilename : %s\r\n",pOTA->OTAFilename);
		// rfile = fopen(pOTA->OTAFilename, "rb"); // Open the file for reading in binary mode
        // if(rfile == NULL)
        // {
        //     printf("pvPortMalloc rfile space error\r\n");

        //     udsstatus.ErrorReg |= 1 << 0;
        //     udsstatus.ErrorDeviceID = pOTA->deviceID;
        // }
        if(udsstatus.ErrorReg == 0)
        {
            udsstatus.XCPCMDOuttimeTimes = 5000;
            udsstatus.XCPCMDOuttimeTime = UDSOVERTIME;
            udsstatus.XCPCMDRpeatTimes = 0;
            unsigned char tmp = 0;
            unsigned int times = 0;
            while(1)
            {
                signed char res = 1;
                if(pOTA->deviceType == AC)
                {
                    udsstatus.CANStartOTA = 1;
                    usleep(3000*1000);
                    printf("XCPOTAtask start_____\r\n");
                    queue_clear(&Queue_Can0RevData);
                    res = udsServer3E(0x600);//保持链接0x3E//0x600//0x1801E410
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer3E successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer3E failed\r\n");
					//								 break;
                    }
                    //延时
                 	usleep(100*1000);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 10);//0124,升级进度
                    res = udsServer10(ACOTACANID,3);//请求0x10
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer10 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer10 failed\r\n");
                         break;
                    }
                    //延时
					usleep(100*1000);
                    res = udsServer3E(0x600);//保持链接0x3E
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer3E successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer3E failed\r\n");
						//								 break;
                    }
                    //延时
					usleep(100*1000);
                    res = udsServer10(ACOTACANID,3);//请求0x10
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer10 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer10 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(100*1000);
                     CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 20);//0124,升级进度
                    res = udsServer27(ACOTACANID,1);//安全访问0x27
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer27 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer27 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(100*1000);
                    res = udsServer10(ACOTACANID,2);//请求0x10
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer10 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer10 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(100*1000);
                    res = udsServer27(ACOTACANID,1);//安全访问0x27
                    if(res == 0)
                    {
                        //成功
                         printf("udsServer27 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer27 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(100*1000);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 30);//0124,升级进度
                    res = udsServer3E(0x600);//保持链接0x3E

                    if(res == 0)
                    {
                        //成功
                         printf("udsServer3E successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer3E failed\r\n");
					//								 break;
                    }
                    //延时
                    usleep(100*1000);
                    res = udsServer3E(0x600);//保持链接0x3E

                    if(res == 0)
                    {
                        //成功
                         printf("udsServer3E successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("udsServer3E failed\r\n");
					//								 break;
                    }
                    //延时
					//开始FLASH数据发送
                    usleep(100*1000);
                    res = udsServer34(ACOTACANID,flashData.writeAddr,flashData.writeLen);//请求下载0x34
                    if(res == 0)
                    {
                        //成功
                         printf("FLASH_udsServer34 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("FLASH_udsServer34 failed\r\n");
                         break;
                    }
                    usleep(500*1000);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 40);//0124,升级进度
                    //延时
                    for(int i = 0; i < sblfilenumber;i++)
                    {
                        printf("sblfilenumber:%d\r\n",sblfilenumber);

                        char otafilenamestr1[OTAFILENAMEMAXLENGTH + 2] = {'\0'};
                        if(udsstatus.ErrorReg == 0)
                        {
                            // otafilenamestr1[0] = '0';
                            // otafilenamestr1[1] = ':';
                            memcpy(&otafilenamestr1, pOTA->OTAUdsSblFilename[i], strlen(pOTA->OTAUdsSblFilename[i]));
                            printf("otafilenamestr1: %s\r\n", otafilenamestr1);
                            printf("pOTA->OTAUdsSblFilename[i]: %s\r\n", pOTA->OTAUdsSblFilename[i]);

                        }
						// rfile = fopen(otafilenamestr1, "rb"); // Open the file for reading in binary mode
						// if(rfile == NULL)
						// {
						//     printf("pvPortMalloc rfile space error\r\n");

						//     udsstatus.ErrorReg |= 1 << 0;
						//     udsstatus.ErrorDeviceID = pOTA->deviceID;
						// }
                        int transferRes = udsServer36(ACOTACANID,otafilenamestr1,rfile);//首帧和连续帧
                        usleep(5*1000);

                        memset(otafilenamestr1, '\0', OTAFILENAMEMAXLENGTH + 2);
                        // otafilenamestr1[0] = '0';
                        // otafilenamestr1[1] = ':';
                        char *str = "w.bin";
                        memcpy(&otafilenamestr1, str, strlen(str));
                        //printf("otafilenamestr1 %s\r\n", otafilenamestr1);
						// if(rfile != NULL)
						// {
						// 	fclose(rfile);
						// 	rfile = NULL;
						// }

                        if (transferRes == 0)
                        {
                            printf("Block %d transferred successfully.\r\n", count + 1);
                        }
                        else
                        {
                            printf("Block %d transfer failed. Error code: %d\r\n", count + 1, transferRes);
                            break;

                        }

                    }
                    usleep(500*1000);
                    res = udsServer37(ACOTACANID ,flashData.CRC);//请求退出0x37
                    if(res == 0)
                    {
                        //成功
                         printf("FLASH_udsServer37 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("FLASH_udsServer37 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(500*1000);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR,50);//0124,升级进度
                    res = udsServer3E(0x600);//保持链接0x3E
                    if(res == 0)
                    {
                        //成功
                         printf("FLASH_udsServer3E successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("FLASH_udsServer3E failed\r\n");
					//								 break;
                    }
                    //延时
                    usleep(100*1000);
					//跳转到RAM程序进行运行
                    res = udsServer31_2(ACOTACANID,0X2108);//例行程序控制0x31,跳转至RAM程序
                    if(res == 0)
                    {
                        //成功
                         printf("APP_udsServer31_2 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("APP_udsServer31_2 failed\r\n");
					//								 break;
                    }
                    //延时
                    usleep(100*1000);
                    res = udsServer31(ACOTACANID,0xee00,0x100);//例行程序控制0x31
                    if(res == 0)
                    {
                        //成功
                         printf("APP_udsServer31 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("APP_udsServer31 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(200*1000);
                    res = udsServer34(ACOTACANID,0xee00,0x100);//请求下载0x34
                    if(res == 0)
                    {
                        //成功
                         printf("APP_udsServer34 successed\r\n");
                    }
                    else
                    {
                        //失败
                         printf("APP_udsServer34 failed\r\n");
                         break;
                    }
                    //延时
                    usleep(500*1000);

					//开始app数据发送

                    char ee00Flag = 0;
                    char ee00Number = 0;
                    for(int i=0;i<appfilenumber;i++)
                    {
                        CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, (50+i*3));//0124,升级进度
                        printf("appfilenumber:%d\r\n",appfilenumber);
                        if(appData[i].writeAddr == 0x0000EE00)
                        {
                            printf("appData[i].writeAddr :%02x\r\n",appData[i].writeAddr);
                            ee00Number = i;
                            ee00Flag = 1;
                            continue;
                        }


                        char otafilenamestr1[OTAFILENAMEMAXLENGTH + 2] = {'\0'};
                        if(udsstatus.ErrorReg == 0)
                        {
                            // otafilenamestr1[0] = '0';
                            // otafilenamestr1[1] = ':';
                            memcpy(&otafilenamestr1, pOTA->OTAUdsFilename[i], strlen(pOTA->OTAUdsFilename[i]));
                            printf("otafilenamestr1 %s\r\n", otafilenamestr1);

                        }

	
                        usleep(100*1000);
                        res = udsServer3E(0x600);//保持链接0x3E
                        if(res == 0)
                        {
                            //成功
                             printf("APP_udsServer3E successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("APP_udsServer3E failed\r\n");
                        }
                        //延时
                        usleep(150*1000);
                        printf("appData[%d].writeAddr = 0x%08X, appData[%d].writeLen = %u\r\n", i, appData[i].writeAddr, i, appData[i].writeLen);
                        res = udsServer31(ACOTACANID,appData[i].writeAddr,appData[i].writeLen);//例行程序控制0x31
                        if(res == 0)
                        {
                            //成功
                             printf("APP_udsServer31 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("APP_udsServer31 failed\r\n");
                             break;
                        }
                        //延时
                        usleep(150*1000);
                        res = udsServer34(ACOTACANID,appData[i].writeAddr,appData[i].writeLen);//请求下载0x34
                        if(res == 0)
                        {
                            //成功
                             printf("APP_udsServer34 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("APP_udsServer34 failed\r\n");
                             break;
                        }
                        //延时
                        usleep(150*1000);
                        res = udsServer3E(0x600);//保持链接0x3E
                        if(res == 0)
                        {
                            //成功
                             printf("APP_udsServer3E successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("APP_udsServer3E failed\r\n");
                        }
                        //延时
                        usleep(150*1000);
                        int transferRes = udsServer36(ACOTACANID,otafilenamestr1,rfile);//首帧和连续帧
                        usleep(100*1000);
                        memset(otafilenamestr1, '\0', OTAFILENAMEMAXLENGTH + 2);
                        // otafilenamestr1[0] = '0';
                        // otafilenamestr1[1] = ':';
                        char *str = "w.bin";
                        memcpy(&otafilenamestr1, str, strlen(str));
                        //printf("otafilenamestr1 %s\r\n", otafilenamestr1);
                        if (transferRes == 0)
                        {
                            printf("Block %d transferred successfully.\r\n", count + 1);
                        }
                        else
                        {
                            printf("Block %d transfer failed. Error code: %d\r\n", count + 1, transferRes);
                            break; // 传输失败
                        }
                        //延时
                        usleep(200*1000);
                        res = udsServer37(ACOTACANID ,appData[i].CRC);//请求退出0x37
                        if(res == 0)
                        {
                            //成功
                             printf("udsServer37 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("udsServer37 failed\r\n");
                             break;
                        }
                        //延时
                         usleep(500*1000);

                    }
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 80);//0124,升级进度


                    if(ee00Flag)
                    {
                        char otafilenamestr1[OTAFILENAMEMAXLENGTH + 2] = {'\0'};
                        if(udsstatus.ErrorReg == 0)
                            {
                                // otafilenamestr1[0] = '0';
                                // otafilenamestr1[1] = ':';
                                memcpy(&otafilenamestr1, pOTA->OTAUdsFilename[ee00Number], strlen(pOTA->OTAUdsFilename[ee00Number]));
                                printf("otafilenamestr1 %s\r\n", otafilenamestr1);
                            }
                        usleep(100*1000);
                        res = udsServer31(ACOTACANID,appData[ee00Number].writeAddr,appData[ee00Number].writeLen);//例行程序控制0x31
                        if(res == 0)
                        {
                            //成功
                             printf("ee00Flag_udsServer31 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("ee00Flag_udsServer31 failed\r\n");
                             break;
                        }
                        //延时
                        usleep(150*1000);
                        res = udsServer34(ACOTACANID,appData[ee00Number].writeAddr,appData[ee00Number].writeLen);//请求下载0x34
                        if(res == 0)
                        {
                            //成功
                             printf("ee00Flag_udsServer34 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("ee00Flag_udsServer34 failed\r\n");
                             break;
                        }
                        //延时
                        usleep(150*1000);
                        int transferRes = udsServer36(ACOTACANID,otafilenamestr1,rfile);//首帧和连续帧
                        usleep(100*1000);

                        memset(otafilenamestr1, '\0', OTAFILENAMEMAXLENGTH + 2);
                        // otafilenamestr1[0] = '0';
                        // otafilenamestr1[1] = ':';
                        char *str = "w.bin";
                        memcpy(&otafilenamestr1, str, strlen(str));
                        //printf("otafilenamestr1 %s\r\n", otafilenamestr1);
                        if (transferRes == 0)
                        {
                            printf("Block %d transferred successfully.\r\n", count + 1);
                        }
                        else
                        {
                            printf("Block %d transfer failed. Error code: %d\r\n", count + 1, transferRes);
                            break; // 传输失败
                        }

                        //延时
                        usleep(150*1000);
                        res = udsServer37(ACOTACANID ,appData[ee00Number].CRC);//请求退出0x37
                        if(res == 0)
                        {
                            //成功
                              printf("ee00Flag_udsServer37 successed\r\n");
                        }
                        else
                        {
                            //失败
                             printf("ee00Flag_udsServer37 failed\r\n");
                             break;
                        }
                        //延时
                    }
                    usleep(150*1000);
                    res = udsServer31_2(ACOTACANID,0XCBA5);//例行程序控制0x31
                    if(res == 0)
                    {
                        //成功
                          printf("ee00Flag_udsServer31_2 successed\r\n");
                    }
                    else
                    {
                        //失败
                        printf("ee00Flag_udsServer31_2 failed\r\n");
                        break;
                    }
                    //延时
                    usleep(150*1000);
                    CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 90);//0124,升级进度
                    break;

                }



            }

        }

        printf("1111\r\n");
        if(rfile != NULL)
        {
            printf("1100\r\n");
            if(udsstatus.ErrorReg >= 27 || udsstatus.ErrorReg == 0)
            {
                printf("2222\r\n");
                fclose(rfile);
                printf("3333\r\n");
            }
            rfile = NULL;
        }
        printf("4444\r\n");
        if(udsstatus.ErrorReg == 0)
        {
            printf("can id 0x%x device ota success!\r\n", pOTA->deviceID);
			LOG("can id 0x%x device ota success!\r\n", pOTA->deviceID);
            udsstatus.DeviceProgramOkFlag = 1;
            CP_set_modbus_reg_val(OTAPPROGRESSREGADDR, 100);//0124,升级进度
            CP_set_modbus_reg_val(OTASTATUSREGADDR, OTASUCCESS);
            otactrl.UpDating = 0;//1130(升级成功)
            udsstatus.CANStartOTA = 0;

        }
        else
        {
            printf("can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, udsstatus.ErrorReg);
			LOG("can id 0x%x device ota failed, error register val 0x%x!\r\n", pOTA->deviceID, udsstatus.ErrorReg);
            // CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAFAILED);
        }

        pOTA->OTAStart =0;

    }
}

void FinishACOtaAndCleanup(OTAObject* pOTA)
{
	CP_set_modbus_reg_val(AC_SBL_OTAFILENUMBER, 0);
	CP_set_modbus_reg_val(AC_APP_OTAFILENUMBER, 0);
	pOTA->deviceType = 0;//停止升级
	pOTA->OTAStart = 0;
	delete_files_with_prefix(USB_MOUNT_POINT, "AC");//  这个要删除升级文件，判断xcpstatus状态，成功或者失败删除
	delete_files_with_prefix(USB_MOUNT_POINT, "XC");//  这个要删除升级文件，判断xcpstatus状态，成功或者失败删除
	delete_files_with_prefix(USB_MOUNT_POINT, "md5"); // 删除升级文件
	otactrl.UpDating = 0;//1130(升级结束)
	udsstatus.CANStartOTA = 0;
	SBl_index = 0;
	APP_index = 0;
	CP_set_TCU_PowerUpCmd(BMS_POWER_DEFAULT);
	CP_set_modbus_reg_val(OTASTATUSREGADDR, OTAIDLE);
	Drv_BMS_Analysis();//BMS数据解析
}

