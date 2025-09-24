#include "Drv_SerialLed.h"
#include "./DRV/LOG/Drv_ZLog.h"




// 设置每一个像素点的颜色
static void Drv_SetPixelColor(unsigned char num, unsigned int color, unsigned char *buff)
{
    
	if (num <= MAX_LEN_NUM)
	{
		buff[SERIAL_LED_HEAD_LEN + (num * 3)] = (unsigned char)(color >> 8);	  // G
		buff[SERIAL_LED_HEAD_LEN + (num * 3 + 1)] = (unsigned char)(color >> 16); // R
		buff[SERIAL_LED_HEAD_LEN + (num * 3 + 2)] = (unsigned char)(color);		  // B
	}
}


void Drv_soc_flashing(unsigned char Soc, unsigned int led_num, unsigned int Color, unsigned char *RGBBuf)
{
	unsigned int i;
	unsigned int flags = led_num -(led_num * Soc) / 100;
	if(flags ==led_num)
		{
			flags =led_num -1 ; //最低soc时也要留一个灯亮
		}
	//for (i = 0; i < led_num; i++)
	for (i = START_USE_NUM; i < led_num; i++)
	{
		if (i >= flags)
		{
			Drv_SetPixelColor(i, Color, RGBBuf);
		}
		else
		{
			Drv_SetPixelColor(i, 0, RGBBuf);
		}
	}

}


void Drv_led_working_state_blue(unsigned char soc,unsigned int led_num,unsigned char *buff)
{
    unsigned int i;
	unsigned int flags = led_num -(led_num * soc) / 100 ;
	if(flags ==led_num)
	{
		flags =led_num -1 ; //最低soc时也要留一个灯亮
	}
	for (i = START_USE_NUM; i < led_num; i++)
	{
		if (i >= flags)
		{
			Drv_SetPixelColor(i, BLUE_COLOR, buff); // 绿色
		}
		else
		{
			Drv_SetPixelColor(i, 0, buff); // 灭灯
		}
	}
}


void Drv_led_green_breathing(unsigned char soc,unsigned int led_num,unsigned char *buff)
{
    unsigned int i;
	unsigned int flags = led_num -(led_num * soc) / 100;
	static unsigned char brifhtness=5,up_flag=1;
	if(flags ==led_num)
	{
		flags =led_num -1 ; //最低soc时也要留一个灯亮
	}
	if(brifhtness==255)
	{
		up_flag = 0;
	}
	else if(brifhtness ==5)
	{
		up_flag = 1;
	}
	if(up_flag)
	{
		brifhtness+= 25;
	}
	else
	{
		brifhtness -=25;
	}

		//for (i = 0; i < led_num; i++)
	for (i = START_USE_NUM; i < led_num; i++)
	{
		if (i >= flags)
		{
			Drv_SetPixelColor(i, brifhtness<<8, buff);
		}
		else
		{
			Drv_SetPixelColor(i, 0, buff);
		}
	}
}


void Drv_led_fixing_state_red(unsigned char soc,unsigned int led_num,unsigned char *buff)
{
    unsigned int i;
	unsigned int flags = led_num -(led_num * soc) / 100;
	if(flags ==led_num)
	{
		flags =led_num -1 ; //最低soc时也要留一个灯亮
	}
	for (i = START_USE_NUM; i < led_num; i++)
	{
		if (i >= flags)
		{
			Drv_SetPixelColor(i, RED_COLOR, buff); // 红色
		}
		else
		{
			Drv_SetPixelColor(i, 0, buff); // 灭灯
		}
	}
}


void Drv_led_warnning_level_1(unsigned char soc, unsigned char *buff)
{
    static uint8_t count=0;
	count++;
	if(count>10)
	{
		count =0;
	}
	if(count>5)  //500ms亮
	{
		Drv_soc_flashing(soc, MAX_USE_LEN_NUM, YELLOW_COLOR, buff);
	}
}

void Drv_led_warnning_level_2(unsigned char soc, unsigned char *buff)
{
    static uint8_t count=0;
	count++;
	if(count>10)
	{
        count =0;
	}
	if(count>5)  //500ms亮
	{
		Drv_soc_flashing(soc, MAX_USE_LEN_NUM, RED_COLOR, buff);
	}
}


void Drv_led_warnning_level_3(unsigned char soc, unsigned char *buff)
{
    static uint8_t count=0;
    count++;
    if(count>5)
    {
        count =0;
    }
    if(count>3)  //500ms亮
    {
        Drv_soc_flashing(soc, MAX_USE_LEN_NUM, RED_COLOR, buff);
    }
    else //500ms灭
    {
        Drv_soc_flashing(soc, MAX_USE_LEN_NUM, 0, buff);
    }
}


bool Drv_SerialASyncSend(int uart_fd,const uint8_t *TxBuff,uint16_t TxSize)
{
	/*HAl底层相关发送函数*/
	ssize_t bytes_written = write(uart_fd, TxBuff, TxSize);

    if (bytes_written >= 0 && (size_t)bytes_written == TxSize) {
        return true; 
    } else {
       
        return false; 
    }


}




