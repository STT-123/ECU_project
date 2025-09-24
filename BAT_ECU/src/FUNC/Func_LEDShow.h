#ifndef __FUNC_LED_SHOW_H__
#define __FUNC_LED_SHOW_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define SERIAL_ADDR 0x00	//设备地址
#define UART_SERIAL_LED_NUM      0x04
typedef enum
{
	soc_flashing_mode = 1,      //空闲状态蓝色常亮
	rainbow_discharging_mode,	//...
	working_state_green,        //工作状态绿色呼吸
	fixing_state_red,           //维修状态红色灯条常亮
	warning_level_1,            //一级警报  黄灯闪烁
	warning_level_2,            //二级警报  红灯闪烁
	warning_level_3,            //三级警报  红灯闪烁
	charging_state,             //充电状态
	discharging_state,          //放电状态


}LED_Mode;

void *Func_SerialLed(void* arg);
// bool Func_LEDShow(int uart_fd,LED_Mode *led_mode);
void Func_update_led_mode(LED_Mode *ledmode);
#endif