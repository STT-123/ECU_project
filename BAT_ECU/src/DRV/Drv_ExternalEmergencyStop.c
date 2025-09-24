#include "Drv_ExternalEmergencyStop.h"
#include "./DRV/Epoll/Drv_epoll.h"
#include "HAL/HAL_GPIO.h"
#include "./CP/BMS/C_BMSAnalysis.h"
#include "main.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./DRV/easylogger/inc/elog.h"
#include "./GLB/G_GloabalVariable.h"
#include "./CP/BMS/bms/CANRcvFcn.h"
#define RECOVER_REPORT_TIME 5000
#define FAULT_REPORT_TIME 3000
#define RECOVER_KM_DEFAULT_STATE 0 //恢复接触器默认状态
#define RECOVER_KM_ACTION_STATE 1 // 恢复接触器动作状态
struct timespec lastCheckTick ;
int PHY_RECOVER = 0;
int PHY_ERROR = 0;
uint8_t ECUState = 0;
int RECOVER = 0;
int ERROR = 0;
struct timespec  lasttimes;

time_t last_can0_rx_time = 0;
bool can0_fault_reported = false;

// 将gpio的状态存入Input结构体中
static void Input_set_state(int pin, unsigned char state);

// 所有gpio初始化
void gpio_all_init(void)
{

	HAL_GPIO_Export(Emergencystop_output);
	HAL_GPIO_Direction(Emergencystop_output, 1);
}




static uint8_t is_header_written = 0;
void log_eror_csv(void)
{
	unsigned char log_flag = 0;
	static unsigned int BCU_FaultInfoLv1H_LAST =0;
	static unsigned int BCU_FaultInfoLv1L_LAST =0;
	static unsigned int BCU_FaultInfoLv2H_LAST =0;
	static unsigned int BCU_FaultInfoLv2L_LAST =0;
	static unsigned int BCU_FaultInfoLv3H_LAST =0;
	static unsigned int BCU_FaultInfoLv3L_LAST =0;
	static unsigned int BCU_FaultInfoLv4H_LAST =0;
	static unsigned int BCU_FaultInfoLv4L_LAST =0;
	static unsigned short BCU_SystemWorkMode_LAST =0;

	if(ecu_fault_last.emcu_fault0 !=  ecu_fault.emcu_fault0)
		{
			printf("****  emcu_fault0  status last=%d,now=%d  \r\n",ecu_fault_last.emcu_fault0,ecu_fault.emcu_fault0);
			//log_i("****  emcu_fault0  status last=%d,now=%d  ",ecu_fault_last.emcu_fault0,ecu_fault.emcu_fault0);
			log_flag = 1;
			ecu_fault_last.emcu_fault0 = ecu_fault.emcu_fault0;
		}
		if(ecu_fault_last.emcu_fault1 !=  ecu_fault.emcu_fault1)
		{
			printf("****  emcu_fault1  status last=%d,now=%d  \r\n",ecu_fault_last.emcu_fault1,ecu_fault.emcu_fault1);
			//log_i("****  emcu_fault1  status last=%d,now=%d  ",ecu_fault_last.emcu_fault1,ecu_fault.emcu_fault1);
			log_flag = 1;
			ecu_fault_last.emcu_fault1 = ecu_fault.emcu_fault1;
		}
		if(ecu_fault_last.emcu_fault2 !=  ecu_fault.emcu_fault2)
		{
			printf("****  emcu_fault2  status last=%d,now=%d  \r\n",ecu_fault_last.emcu_fault2,ecu_fault.emcu_fault2);
			//log_i("****  emcu_fault2  status last=%d,now=%d  ",ecu_fault_last.emcu_fault2,ecu_fault.emcu_fault2);
			log_flag = 1;
			ecu_fault_last.emcu_fault2 = ecu_fault.emcu_fault2;
		}

		if(ecu_fault_last.emcu_fault_state !=  ecu_fault.emcu_fault_state)
		{
			printf("****  emcu_fault_state  status last=%d,now=%d  \r\n",ecu_fault_last.emcu_fault_state,ecu_fault.emcu_fault_state);
			//log_i("****  emcu_fault_state  status last=%d,now=%d  ",ecu_fault_last.emcu_fault_state,ecu_fault.emcu_fault_state);
			log_flag = 1;
			ecu_fault_last.emcu_fault_state = ecu_fault.emcu_fault_state;
		}
		if(BCU_SystemWorkMode_LAST != BCU_SystemWorkMode)
		{
			log_flag = 1;
			BCU_SystemWorkMode_LAST = BCU_SystemWorkMode;
		}

		if(BCU_FaultInfoLv1H_LAST != BCU_FaultInfoLv1H)
				{
					log_flag = 1;
					BCU_FaultInfoLv1H_LAST = BCU_FaultInfoLv1H;
				}
		if(BCU_FaultInfoLv1L_LAST != BCU_FaultInfoLv1L)
				{
					log_flag = 1;
					BCU_FaultInfoLv1L_LAST = BCU_FaultInfoLv1L;
				}
		if(BCU_FaultInfoLv2H_LAST != BCU_FaultInfoLv2H)
				{
					log_flag = 1;
					BCU_FaultInfoLv2H_LAST = BCU_FaultInfoLv2H;
				}
		if(BCU_FaultInfoLv2L_LAST != BCU_FaultInfoLv2L)
				{
					log_flag = 1;
					BCU_FaultInfoLv2L_LAST = BCU_FaultInfoLv2L;
				}
		if(BCU_FaultInfoLv3H_LAST != BCU_FaultInfoLv3H)
				{
					log_flag = 1;
					BCU_FaultInfoLv3H_LAST = BCU_FaultInfoLv3H;
				}
		if(BCU_FaultInfoLv3L_LAST != BCU_FaultInfoLv3L)
				{
					log_flag = 1;
					BCU_FaultInfoLv3L_LAST = BCU_FaultInfoLv3L;
				}
		if(BCU_FaultInfoLv4H_LAST != BCU_FaultInfoLv4H)
				{
					log_flag = 1;
					BCU_FaultInfoLv4H_LAST = BCU_FaultInfoLv4H;
				}
		if(BCU_FaultInfoLv4L_LAST != BCU_FaultInfoLv4L)
				{
					log_flag = 1;
					BCU_FaultInfoLv4L_LAST = BCU_FaultInfoLv4L;
				}
		//,ECU_VERSION>>8,ECU_VERSION&0x00FF,  ecu 版本号不打印
		// printf("log_flag :%d\r\n",log_flag);
		// log_flag = 1;
		if(log_flag == 1)
		{

			log_i("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
					ecu_fault.emcu_fault0,
					ecu_fault.emcu_fault1,
					ecu_fault.emcu_fault2,
					BCU_FaultInfoLv1H,
					BCU_FaultInfoLv1L,
					BCU_FaultInfoLv2H,
					BCU_FaultInfoLv2L,
					BCU_FaultInfoLv3H,
					BCU_FaultInfoLv3L,
					BCU_FaultInfoLv4H,
					BCU_FaultInfoLv4L,
					BCU_SOC,
					BCU_SystemStatus,
					BCU_SystemWorkMode


			);
		}
}


// //网线连接状态检测
// void CheckPHYStatus(const char* iface, int* recoverFlag, int* errorFlag, struct timespec* lastTick)
// {
//     char path[128];
//     char buf[2] = {0};  
//     int fd = -1;

//     snprintf(path, sizeof(path), "/sys/class/net/%s/carrier", iface);
//     fd = open(path, O_RDONLY);
//     if (fd >= 0)
//     {
//         if (read(fd, buf, 1) == 1)
//         {
//             if (buf[0] == '1')  
//             {
//                 if (*recoverFlag == 1)
//                 {
//                     if (GetTimeDifference_ms(*lastTick) >= RECOVER_REPORT_TIME)
//                     {
//                         CP_set_emcu_fault(PHY_LINK_FAULT, SET_RECOVER);
//                         *errorFlag = 0;
//                     }
//                 }
//                 else
//                 {
//                     clock_gettime(CLOCK_MONOTONIC, lastTick);
//                     *recoverFlag = 1;
//                     *errorFlag = 0;
//                 }
//             }
//             else  
//             {
//                 if (*errorFlag == 1)
//                 {
//                     if (GetTimeDifference_ms(*lastTick) >= FAULT_REPORT_TIME)
//                     {
//                         CP_set_emcu_fault(PHY_LINK_FAULT, SET_ERROR);
//                         *recoverFlag = 0;
//                     }
//                 }
//                 else
//                 {
//                     clock_gettime(CLOCK_MONOTONIC, lastTick);
//                     *errorFlag = 1;
//                     *recoverFlag = 0;
//                 }
//             }
//         }
//         else
//         {
//             // 读取失败
//             fprintf(stderr, "Failed to read carrier for %s: %s\n", iface, strerror(errno));
//         }
//         close(fd);
//     }
//     else
//     {
//         fprintf(stderr, "Failed to open carrier for %s: %s\n", iface, strerror(errno));
//     }
// }

// void PHYlinktate()
// {
//     static struct timespec lastCheckTick_eth0 = {0};
//     static struct timespec lastCheckTick_eth1 = {0};
//     static int PHY_RECOVER_eth0 = 0, PHY_ERROR_eth0 = 0;
//     static int PHY_RECOVER_eth1 = 0, PHY_ERROR_eth1 = 0;

//     CheckPHYStatus("eth0", &PHY_RECOVER_eth0, &PHY_ERROR_eth0, &lastCheckTick_eth0);
//     CheckPHYStatus("eth1", &PHY_RECOVER_eth1, &PHY_ERROR_eth1, &lastCheckTick_eth1);
// }

void PHYlinktate()
{
    static struct timespec lastCheckTick = {0};
    static int PHY_RECOVER_FLAG = 0;
    static int PHY_ERROR_FLAG = 0;

    int eth0_status = 0; // 1表示连接，0表示未连接
    int eth1_status = 0;

    // 检查eth0
    eth0_status = CheckSinglePHYStatus("eth0");
    // 检查eth1
    eth1_status = CheckSinglePHYStatus("eth1");

    if (eth0_status && eth1_status)  // 两个都连接
    {
        if (PHY_RECOVER_FLAG == 1)
        {
            if (GetTimeDifference_ms(lastCheckTick) >= RECOVER_REPORT_TIME)
            {
                CP_set_emcu_fault(PHY_LINK_FAULT, SET_RECOVER);
                PHY_ERROR_FLAG = 0;
            }
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC, &lastCheckTick);
            PHY_RECOVER_FLAG = 1;
            PHY_ERROR_FLAG = 0;
        }
    }
    else // 任意一个未连接就报故障
    {
        if (PHY_ERROR_FLAG == 1)
        {
            if (GetTimeDifference_ms(lastCheckTick) >= FAULT_REPORT_TIME)
            {
               // CP_set_emcu_fault(PHY_LINK_FAULT, SET_ERROR);
                PHY_RECOVER_FLAG = 0;
            }
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC, &lastCheckTick);
            PHY_ERROR_FLAG = 1;
            PHY_RECOVER_FLAG = 0;
        }
    }
}



int CheckSinglePHYStatus(const char* iface)
{
    char path[128];
    char buf[2] = {0};
    int fd = -1;

    snprintf(path, sizeof(path), "/sys/class/net/%s/carrier", iface);
    fd = open(path, O_RDONLY);
    if (fd >= 0)
    {
        if (read(fd, buf, 1) == 1)
        {
            close(fd);
            return buf[0] == '1' ? 1 : 0;
        }
        close(fd);
    }
    fprintf(stderr, "Failed to get carrier for %s: %s\n", iface, strerror(errno));
    return 0;
}


void ECUfault_process()
{

		if ( ( CP_get_emcu_fault(ALL_FAULT) !=0 ) && (otactrl.UpDating == 0))
		{
			CP_set_TCU_PowerUpCmd(BMS_POWER_OFF);
			HAL_GPIO_Write(Emergencystop_output,RECOVER_KM_DEFAULT_STATE);
			// printf("Emergencystop_output:0\r\n");
		}
		else   //恢复告警
		{
			HAL_GPIO_Write(Emergencystop_output,RECOVER_KM_ACTION_STATE);
			// printf("Emergencystop_output:1\r\n");
		}
    	CP_update_fault_tomodus();

}


void Drv_can0_rx_timeout_check(void)
{
    time_t current_time;
    time(&current_time);
    double diff = difftime(current_time, last_can0_rx_time);

    if (diff >= 5.0)
    {
        if (!can0_fault_reported)
        {
            CP_set_emcu_fault(BMS_COM_FAULT, SET_ERROR);
            can0_fault_reported = true;
            printf("CAN0 TimeoutCheck warning\n");
        }
    }
    else
    {
        if (can0_fault_reported)
        {
            CP_set_emcu_fault(BMS_COM_FAULT, SET_RECOVER);
            can0_fault_reported = false;
            printf("CAN0 TimeoutCheckv normal\n");
        }
    }
}


void Set_Electric_Meter_Data(void)
{
// 	printf("Electric_Meter_BCU_V3:%f\r\n",Electric_Meter_BCU_V3);
// 	printf("Electric_Meter_BCU_Curr2:%f\r\n",Electric_Meter_BCU_Curr2);
// 	printf("Electric_Meter_BCU_RealtimePower:%d\r\n",Electric_Meter_BCU_RealtimePower);
// 	printf("Electric_Meter_BCU_EngryAccumulateChrg:%d\r\n",Electric_Meter_BCU_EngryAccumulateChrg);
// 	printf("Electric_Meter_BCU_EngryAccumulateDisChrg:%d\r\n",Electric_Meter_BCU_EngryAccumulateDisChrg);
    Set_BCU_Voltage((float)102.3);
	
	// Set_BCU_Current(Electric_Meter_BCU_Curr2);

	// Set_BCU_Power(Electric_Meter_BCU_RealtimePower);
	
	// Set_BCU_PositiveEnergy(Electric_Meter_BCU_EngryAccumulateChrg);

	// Set_BCU_NegativeEnergy(Electric_Meter_BCU_EngryAccumulateDisChrg);
	
}
