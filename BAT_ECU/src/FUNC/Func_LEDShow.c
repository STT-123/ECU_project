// #include "Func_LEDShow.h"
// #include "Drv_SerialLed.h"




// bool Func_LEDShow(LED_Mode *led_mode)
// {
//     bool state = false;
//     uint8_t cnt = 0;
// 	int j = 0;
// 	unsigned char buff[(MAX_LEN_NUM * 3) + SERIAL_LED_HEAD_LEN] = {0};
// 	int len = (MAX_LEN_NUM * 3) + SERIAL_LED_HEAD_LEN;
//     memcpy(buff, Head, sizeof(Head));
//     buff[5] = SERIAL_ADDR;
//     buff[6] = 0x00;
//     buff[7] = (char)((MAX_LEN_NUM * 3) >> 8);
//     buff[8] = (char)((MAX_LEN_NUM * 3));

//     for (j = 0; j < MAX_LEN_NUM; j++)
//     {
//         buff[SERIAL_LED_HEAD_LEN + (j * 3)] = 0x00;		// r
//         buff[SERIAL_LED_HEAD_LEN + (j * 3 + 1)] = 0x00; // g
//         buff[SERIAL_LED_HEAD_LEN + (j * 3 + 2)] = 0x00; // b
//     }

//     Func_led_working_mode_select(100,led_mode,buff);
//     do{
//         cnt++;
//         state = Drv_SerialASyncSend(UART_SERIAL_LED_NUM, buff, len);
//         if(state == true)
//         {
            
    
//         }
// 		else
// 		{
			
			
// 		}

//     }while ((state == false) && (cnt < 3))
//     return state;

// }


// void Func_update_led_mode(LED_Mode *ledmode)
// {
// 	static LED_Mode led_last_mode = soc_flashing_mode;


// 	if(BCU_SystemWorkMode <3 )
// 	{
// 		*ledmode = soc_flashing_mode;  //空闲状态蓝灯常亮
// 	}
// 	else if(BCU_SystemWorkMode ==3 )
// 	{
// 		*ledmode = working_state_green;  //未充放时候灯绿色
// 	}

// 	if((BCU_FaultInfoLv1H!=0||(BCU_FaultInfoLv1L!=0)))
// 	{
// 		*ledmode = warning_level_1;
// 	}
// 	if(BCU_FaultInfoLv2H!=0||(BCU_FaultInfoLv2L!=0))
// 	{
// 		*ledmode = warning_level_2;
// 	}
// 	if((BCU_FaultInfoLv3H!=0||(BCU_FaultInfoLv3L!=0)))
// 	{
// 		*ledmode = warning_level_3;
// 	}
// 	if((1 == CP_get_emcu_fault(ALL_FAULT))||(BCU_FaultInfoLv4H!=0||(BCU_FaultInfoLv4L!=0)))//ecu的故障为维护故障
// 	{
// 		*ledmode = fixing_state_red;
// 	}


// 	if(led_last_mode != *ledmode)
// 	{
// 		 printf("ledmode  status last=%d,now=%d bcu_workmode=%d,bcu_state=%d,ecu=%d \r\n",led_last_mode,*ledmode,BCU_SystemWorkMode,BCU_SystemStatus,get_emcu_fault(ALL_FAULT));

// 		 if(*ledmode == warning_level_1)
// 		 {
//             printf("BCU_FaultInfoLv1H =0x%x,BCU_FaultInfoLv1L=0x%x \r\n",BCU_FaultInfoLv1H,BCU_FaultInfoLv1L);
// 		 }
// 		 if(*ledmode == warning_level_2)
// 		 {
//             printf("BCU_FaultInfoLv2H =0x%x,BCU_FaultInfoLv2L=0x%x \r\n",BCU_FaultInfoLv2H,BCU_FaultInfoLv2L);
// 		 }

// 		 if(*ledmode == warning_level_3)
// 		 {
// 		    printf("BCU_FaultInfoLv3H =0x%x,BCU_FaultInfoLv3L=0x%x \r\n",BCU_FaultInfoLv3H,BCU_FaultInfoLv3L);
// 		 }
// 		 if(*ledmode == fixing_state_red)
// 		 {
// 		    printf("BCU_FaultInfoLv4H =0x%x,BCU_FaultInfoLv4L=0x%x \r\n",BCU_FaultInfoLv4H,BCU_FaultInfoLv4L);
// 		 }
// 		 led_last_mode  = *ledmode;
// 	}



// }




// void Func_led_working_mode_select(unsigned char soc, LED_Mode led_mode, unsigned char *buff)
// {
//     if(led_mode == soc_flashing_mode)    //此处本质是空闲状态，蓝色灯条闪烁。
// 	{
// 		Drv_led_working_state_blue(soc,MAX_USE_LEN_NUM,buff);
// 	}
// 	else if(led_mode == working_state_green)    //工作状态绿色条常亮
// 	{
// 		Drv_led_green_breathing(soc,MAX_USE_LEN_NUM,buff);
// 	}
// 	else if(led_mode == fixing_state_red)    //此处是修理状态红色灯条常亮
// 	{
// 		Drv_led_fixing_state_red(soc,MAX_USE_LEN_NUM,buff);
// 	}
// 	else if(led_mode == warning_level_1)    //此处是一级警报黄灯闪烁
// 	{
// 		Drv_led_warnning_level_1(soc,buff);
// 	}
// 	else if(led_mode == warning_level_2)    //此处是二级警报红灯闪烁
// 	{
// 		Drv_led_warnning_level_2(soc,buff);
// 	}
// 	else if(led_mode == warning_level_3)    //此处是三级警报红灯闪烁
// 	{
// 		Drv_led_warnning_level_3(soc,buff);
// 	}
// }
