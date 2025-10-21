#include "Drv_ExternalEmergencyStop.h"

#include "port/gpio.h"
#include "log/log.h"

#include "./CP/BMS/C_BMSAnalysis.h"
#include "main.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./GLB/G_GloabalVariable.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

#define RECOVER_REPORT_TIME 5000
#define FAULT_REPORT_TIME 3000
#define RECOVER_KM_DEFAULT_STATE 0 // 恢复接触器默认状态
#define RECOVER_KM_ACTION_STATE 1  // 恢复接触器动作状态
struct timespec lastCheckTick;
int PHY_RECOVER = 0;
int PHY_ERROR = 0;
uint8_t ECUState = 0;
int RECOVER = 0;
int ERROR = 0;
struct timespec lasttimes;

time_t last_can0_rx_time = 0;
bool can0_fault_reported = false;

// 所有gpio初始化
void gpio_all_init(void)
{
	gpio_open(Emergencystop_output, 1, RECOVER_KM_ACTION_STATE);
}

void log_eror_csv(void)
{
	unsigned char log_flag = 0;
	static unsigned int BCU_FaultInfoLv1H_LAST = 0;
	static unsigned int BCU_FaultInfoLv1L_LAST = 0;
	static unsigned int BCU_FaultInfoLv2H_LAST = 0;
	static unsigned int BCU_FaultInfoLv2L_LAST = 0;
	static unsigned int BCU_FaultInfoLv3H_LAST = 0;
	static unsigned int BCU_FaultInfoLv3L_LAST = 0;
	static unsigned int BCU_FaultInfoLv4H_LAST = 0;
	static unsigned int BCU_FaultInfoLv4L_LAST = 0;
	static unsigned short BCU_SystemWorkMode_LAST = 0;

	if (ecu_fault_last.emcu_fault0 != ecu_fault.emcu_fault0)
	{
		printf("****  emcu_fault0  status last=%d,now=%d  \r\n", ecu_fault_last.emcu_fault0, ecu_fault.emcu_fault0);
		// log_i("****  emcu_fault0  status last=%d,now=%d  ",ecu_fault_last.emcu_fault0,ecu_fault.emcu_fault0);
		log_flag = 1;
		ecu_fault_last.emcu_fault0 = ecu_fault.emcu_fault0;
	}
	if (ecu_fault_last.emcu_fault1 != ecu_fault.emcu_fault1)
	{
		printf("****  emcu_fault1  status last=%d,now=%d  \r\n", ecu_fault_last.emcu_fault1, ecu_fault.emcu_fault1);
		// log_i("****  emcu_fault1  status last=%d,now=%d  ",ecu_fault_last.emcu_fault1,ecu_fault.emcu_fault1);
		log_flag = 1;
		ecu_fault_last.emcu_fault1 = ecu_fault.emcu_fault1;
	}
	if (ecu_fault_last.emcu_fault2 != ecu_fault.emcu_fault2)
	{
		printf("****  emcu_fault2  status last=%d,now=%d  \r\n", ecu_fault_last.emcu_fault2, ecu_fault.emcu_fault2);
		// log_i("****  emcu_fault2  status last=%d,now=%d  ",ecu_fault_last.emcu_fault2,ecu_fault.emcu_fault2);
		log_flag = 1;
		ecu_fault_last.emcu_fault2 = ecu_fault.emcu_fault2;
	}

	if (ecu_fault_last.emcu_fault_state != ecu_fault.emcu_fault_state)
	{
		printf("****  emcu_fault_state  status last=%d,now=%d  \r\n", ecu_fault_last.emcu_fault_state, ecu_fault.emcu_fault_state);
		// log_i("****  emcu_fault_state  status last=%d,now=%d  ",ecu_fault_last.emcu_fault_state,ecu_fault.emcu_fault_state);
		log_flag = 1;
		ecu_fault_last.emcu_fault_state = ecu_fault.emcu_fault_state;
	}
	if (BCU_SystemWorkMode_LAST != BCU_SystemWorkMode)
	{
		log_flag = 1;
		BCU_SystemWorkMode_LAST = BCU_SystemWorkMode;
	}

	if (BCU_FaultInfoLv1H_LAST != BCU_FaultInfoLv1H)
	{
		log_flag = 1;
		BCU_FaultInfoLv1H_LAST = BCU_FaultInfoLv1H;
	}
	if (BCU_FaultInfoLv1L_LAST != BCU_FaultInfoLv1L)
	{
		log_flag = 1;
		BCU_FaultInfoLv1L_LAST = BCU_FaultInfoLv1L;
	}
	if (BCU_FaultInfoLv2H_LAST != BCU_FaultInfoLv2H)
	{
		log_flag = 1;
		BCU_FaultInfoLv2H_LAST = BCU_FaultInfoLv2H;
	}
	if (BCU_FaultInfoLv2L_LAST != BCU_FaultInfoLv2L)
	{
		log_flag = 1;
		BCU_FaultInfoLv2L_LAST = BCU_FaultInfoLv2L;
	}
	if (BCU_FaultInfoLv3H_LAST != BCU_FaultInfoLv3H)
	{
		log_flag = 1;
		BCU_FaultInfoLv3H_LAST = BCU_FaultInfoLv3H;
	}
	if (BCU_FaultInfoLv3L_LAST != BCU_FaultInfoLv3L)
	{
		log_flag = 1;
		BCU_FaultInfoLv3L_LAST = BCU_FaultInfoLv3L;
	}
	if (BCU_FaultInfoLv4H_LAST != BCU_FaultInfoLv4H)
	{
		log_flag = 1;
		BCU_FaultInfoLv4H_LAST = BCU_FaultInfoLv4H;
	}
	if (BCU_FaultInfoLv4L_LAST != BCU_FaultInfoLv4L)
	{
		log_flag = 1;
		BCU_FaultInfoLv4L_LAST = BCU_FaultInfoLv4L;
	}

	//,ECU_VERSION>>8,ECU_VERSION&0x00FF,  ecu 版本号不打印
	// printf("log_flag :%d\r\n",log_flag);
	// log_flag = 1;
	if (log_flag == 1)
	{
		LOG_CSV("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
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
			BCU_SystemWorkMode);
	}
}

typedef struct
{
	unsigned long long rx_bytes;
	unsigned long long tx_bytes;
	unsigned long long rx_packets;
	unsigned long long tx_packets;
} net_stats_t;

int CheckSinglePHYStatus(const char *ifname)
{
	FILE *fp;
	char line[512];
	char devname[32];
	net_stats_t stats = {0};
	static net_stats_t last_stats[2] = {0}; // 简单缓存上次统计
	static int initialized = 0;

	fp = fopen("/proc/net/dev", "r");
	if (!fp)
	{
		perror("fopen /proc/net/dev failed");
		return 0; // 没有
	}

	// 跳过前两行标题
	fgets(line, sizeof(line), fp);
	fgets(line, sizeof(line), fp);

	while (fgets(line, sizeof(line), fp))
	{
		// 解析接口统计信息
		if (sscanf(line, "%31[^:]: %llu %llu %*u %*u %*u %*u %*u %*u %llu %llu",
				   devname, &stats.rx_bytes, &stats.rx_packets,
				   &stats.tx_bytes, &stats.tx_packets) >= 4)
		{

			// 去除接口名末尾的空格
			char *p = devname;
			while (*p == ' ')
				p++;

			if (strcmp(p, ifname) == 0)
			{
				fclose(fp);

				// 检查是否有数据活动
				int has_traffic = 0;

				if (initialized)
				{
					// 比较当前统计和上次统计
					net_stats_t *last = &last_stats[strcmp(ifname, "eth0") == 0 ? 0 : 1];
					if (stats.rx_bytes > last->rx_bytes ||
						stats.tx_bytes > last->tx_bytes ||
						stats.rx_packets > last->rx_packets ||
						stats.tx_packets > last->tx_packets)
					{
						has_traffic = 1;
					}
				}

				// 更新缓存
				net_stats_t *last = &last_stats[strcmp(ifname, "eth0") == 0 ? 0 : 1];
				*last = stats;
				initialized = 1;

				return has_traffic;
			}
		}
	}

	fclose(fp);
	return 0; // 接口未找到
}

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

	// LOG("TTTTTTTTTTTTTTTTT eth0_status = %d,  eth1_status=%d ", eth0_status, eth1_status);
	// eth0_status = 1;
	// eth1_status = 1;

	if (eth0_status && eth1_status) // 两个都连接
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
				CP_set_emcu_fault(PHY_LINK_FAULT, SET_ERROR);
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

void ECUfault_process()
{
	if ((CP_get_emcu_fault(ALL_FAULT) != 0) && (otactrl.UpDating == 0))
	{
		CP_set_TCU_PowerUpCmd(BMS_POWER_OFF);
		gpio_write(Emergencystop_output, RECOVER_KM_DEFAULT_STATE);
		// printf("Emergencystop_output:0\r\n");
	}
	else // 恢复告警
	{
		gpio_write(Emergencystop_output, RECOVER_KM_ACTION_STATE);
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
