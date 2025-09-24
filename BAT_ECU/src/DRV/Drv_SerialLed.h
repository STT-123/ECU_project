#ifndef ___DRV_SERIAL_LED_H__
#define ___DRV_SERIAL_LED_H__

 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "stdbool.h"
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0x00FF00
#define BLUE_COLOR 0x0000FF
#define YELLOW_COLOR 0xFFFF00

#define MAX_USE_LEN_NUM 90 
#define MAX_LEN_NUM 100   //灯条灯珠最大数量
#define SERIAL_LED_HEAD_LEN 9   //包头的长度
#define START_USE_NUM   0    //灯条实际起始位置


void Drv_soc_flashing(unsigned char Soc, unsigned int led_num, unsigned int Color, unsigned char *RGBBuf);
void Drv_led_working_state_blue(unsigned char soc,unsigned int led_num,unsigned char *buff);
void Drv_led_green_breathing(unsigned char soc,unsigned int led_num,unsigned char *buff);
void Drv_led_fixing_state_red(unsigned char soc,unsigned int led_num,unsigned char *buff);
void Drv_led_warnning_level_1(unsigned char soc, unsigned char *buff);
void Drv_led_warnning_level_2(unsigned char soc, unsigned char *buff);
void Drv_led_warnning_level_3(unsigned char soc, unsigned char *buff);
bool Drv_SerialASyncSend(int uart_fd,const uint8_t *TxBuff,uint16_t TxSize);
int open_port(int uart_num);
#endif