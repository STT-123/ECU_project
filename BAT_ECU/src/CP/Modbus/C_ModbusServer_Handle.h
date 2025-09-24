#ifndef __C_MODBUS_UPDATE_H__
#define __C_MODBUS_UPDATE_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>





#define  REGISTERS_NB  0x4000            // 寄存器数量

#define MDBUS_ADDR_BECU_FAULT0 0x3440
#define MDBUS_ADDR_BECU_FAULT1 0x3441
#define MDBUS_ADDR_BECU_FAULT2 0x3442
#define MDBUS_ADDR_BECU_FAULT3 0x3443
typedef struct
{
	unsigned char emcu_fault_state;   //总故障标志
	unsigned short emcu_fault0;
	unsigned short emcu_fault1;
	unsigned short emcu_fault2;
	unsigned short emcu_fault3;  //告警不影响功能，比如sd卡
}ecu_fault_t;
// uint16_t *modbusBuff = NULL;
extern ecu_fault_t ecu_fault;
extern ecu_fault_t ecu_fault_last;

void CP_update_fault_tomodus(void);
void CP_set_emcu_fault(unsigned char parameter, unsigned char status);
unsigned short CP_get_emcu_fault(unsigned char parameter);
int CP_set_modbus_reg_val(uint16_t addr, uint16_t set_val);
int CP_get_modbus_reg_val(uint16_t addr, uint16_t * get_val);
int CP_RTC_ModBus_Deal(uint16_t address,uint16_t data);
int CP_BatteryCalibration_ModBus_Deal(uint16_t address,uint16_t data);
 void CP_set_ems_bms_reboot();
//  int update_system_time(const Rtc_Ip_TimedateType *timeData);
#endif