#ifndef __DRV_EXTERNAL_EMERGENCY_STOP_H__
#define __DRV_EXTERNAL_EMERGENCY_STOP_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

// #define EMERGENCY_STOP     496			
// #define PCSSTOP     32	

#define Emergencystop_output    32

       				

extern time_t last_can0_rx_time ;


void gpio_all_init(void);
void PHYlinktate();
void log_eror_csv(void);
void ECUfault_process();
void Drv_can0_rx_timeout_check(void);
void Set_Electric_Meter_Data(void);
#endif