#include "C_ModbusServer_Handle.h"
#include "../GLB/G_GloabalVariable.h"
#include "C_ModbusServer.h"
ecu_fault_t ecu_fault;

void CP_update_fault_tomodus(void)
{

	CP_set_modbus_reg_val(MDBUS_ADDR_BECU_FAULT0, ecu_fault.emcu_fault0);
	CP_set_modbus_reg_val(MDBUS_ADDR_BECU_FAULT1, ecu_fault.emcu_fault1);
	CP_set_modbus_reg_val(MDBUS_ADDR_BECU_FAULT2, ecu_fault.emcu_fault2);
	CP_set_modbus_reg_val(MDBUS_ADDR_BECU_FAULT3, ecu_fault.emcu_fault3);

}


/********************************************************************************
*
* 输入参数：
*                      unsigned int parameter   参数 //詳見fault_intaface.h
*                      unsigned char status        分机的状态 1 0
* 			无
* 输出参数：无
********************************************************************************/
void CP_set_emcu_fault(unsigned char parameter, unsigned char status)
{
	unsigned char byte_num = (parameter & 0xf0) >> 4; //高4位字节号
	unsigned short bit_num = (parameter & 0x0F);       //  低4位bit位

	switch (byte_num)
	 {
		case 0:
	        if (status)
	        {
	        	ecu_fault.emcu_fault0 &= ~(1 << bit_num);
	        }
	        else
	        {
	        	ecu_fault.emcu_fault0 |= (1 << bit_num);
	        }
	        break;
		case 1:
	        if (status)
	        {
	        	ecu_fault.emcu_fault1 &= ~(1 << bit_num);
	        }
	        else
	        {
	        	ecu_fault.emcu_fault1 |= (1 << bit_num);
	        }
	        break;
		case 2:
	        if (status)
	        {
	        	ecu_fault.emcu_fault2 &= ~(1 << bit_num);
	        }
	        else
	        {
	        	ecu_fault.emcu_fault2 |= (1 << bit_num);
	        }
	        break;
		case 3:
			if (status)
			{
				ecu_fault.emcu_fault3 &= ~(1 << bit_num);
			}
			else
			{
				ecu_fault.emcu_fault3 |= (1 << bit_num);
			}
	        break;
		default:break;

	 }
	if(ecu_fault.emcu_fault0 + ecu_fault.emcu_fault1 + ecu_fault.emcu_fault2)
	{
		ecu_fault.emcu_fault_state = 1;
	}
	else
	{
		ecu_fault.emcu_fault_state = 0;
	}

}

/********************************************************************************
*
* 输入参数：
*                      unsigned int parameter   参数 //詳見fault_intaface.h
*                      unsigned char status        分机的状态 1 0
* 			无
* 输出参数：无
********************************************************************************/
unsigned short CP_get_emcu_fault(unsigned char parameter)
{
    unsigned char byte_num = (parameter & 0xf0) >> 4; //高4位字节号
    unsigned short bit_num = (parameter & 0x0F);       //  低4位bit位

    unsigned char status = 0;

    if(ALL_FAULT == parameter)
    {
    	return ecu_fault.emcu_fault_state;
    }
    switch (byte_num)
        {
    	case 0:

        status = (ecu_fault.emcu_fault0 >> bit_num) & (0x01);
        break;
        case 1:
            status = (ecu_fault.emcu_fault1 >> bit_num) & (0x01);
            break;

        case 2:
            status = (ecu_fault.emcu_fault2 >> bit_num) & (0x01);
            break;
        default:break;
        } //endof switch
        return status;
}



/********************************************************************************
 * 函数名称： get_modbus_reg_val
 * 功能描述：   获取modbus寄存器的值
 * 输入参数：
 * 输出参数： 0表示获取成功，非0表示获取失败
 ********************************************************************************/
int CP_get_modbus_reg_val(uint16_t addr, uint16_t * get_val)
{
	if(modbusBuff_C ==NULL)
	{
		return -1;
	}
	if ((addr >= REGISTERS_START_ADDRESS) && (addr < (REGISTERS_START_ADDRESS + REGISTERS_NB)))
	{
		*get_val = modbusBuff_C[addr -REGISTERS_START_ADDRESS ];
		return 0;
	}
	else
	{
		*get_val = 0;
		return -2;
	}
	return 0;
}
/********************************************************************************
 * 函数名称： CP_set_modbus_reg_val
 * 功能描述：   向modbus寄存器的值
 * 输入参数：
 * 输出参数： 0 表示写入成功，非0表示写入失败
 ********************************************************************************/
int CP_set_modbus_reg_val(uint16_t addr, uint16_t set_val)
{
	if(modbusBuff_C ==NULL)
	{
		return -1;
	}
	if ((addr >= REGISTERS_START_ADDRESS) && (addr < (REGISTERS_START_ADDRESS + REGISTERS_NB)))
	{
		modbusBuff_C[addr -REGISTERS_START_ADDRESS ] = set_val;
		return 0;
	}
	else
	{
		return -2;
	}
	return 0;
}

/********************************************************************************
 * 函数名称： RTC_ModBus_Deal
 * 功能描述： ModBus设置RTC指令
 * 输入参数：
 * 输出参数： 0 表示写入成功，1表示写入完成，-1表示失败。
 *sqw
 ********************************************************************************/
int CP_RTC_ModBus_Deal(uint16_t address,uint16_t data)
{
//	static uint16_t year=0,month=0,day=0,hour=0,min=0;
//	static uint8_t second=0;
	static Rtc_Ip_TimedateType TmData;
	CAN_MESSAGE bms_rtc_set;
	if(address==0x6705)  //年
	{
		TmData.year=data;
		return 0;  //成功
	}
	else if(address==0x6706)  //月
	{
		TmData.month=data;
		return 0;  //成功
	}
	else if(address==0x6707)  //日
	{
		TmData.day=data;
		return 0;  //成功
	}
	else if(address==0x6708)  //时
	{
		TmData.hour=data;
		return 0;  //成功
	}
	else if(address==0x6709)  //分
	{
		TmData.minutes=data;
		return 0;  //成功
	}
	else if(address==0x670A)  //秒
	{
		static uint8_t rtccount =0;
		TmData.seconds=(uint8_t)data;
//		RTCSetTime(TmData);    //设置RTC时间

		printf("RTC Set Success!  \r\n");

		bms_rtc_set.ID=0x1823E410;
		bms_rtc_set.Length=8;
		bms_rtc_set.Extended=1;
		bms_rtc_set.Remote=0;
		bms_rtc_set.Data[0]=(uint8_t)(TmData.year%100);
		bms_rtc_set.Data[1]=(uint8_t)(TmData.month);
		bms_rtc_set.Data[2]=(uint8_t)(TmData.day);
		bms_rtc_set.Data[3]=(uint8_t)(TmData.hour);
		bms_rtc_set.Data[4]=(uint8_t)(TmData.minutes);
		bms_rtc_set.Data[5]=TmData.seconds;
		bms_rtc_set.Data[6]=0;
		bms_rtc_set.Data[7]=1;    //RTC设置完毕标志位为1
        for (int i = 0; i < 3; i++)
        {
			can1_send(&bms_rtc_set);
        }
//		xQueueSend(xQueue_forward_can_out2in,&bms_rtc_set,100/portTICK_PERIOD_MS);
		bms_rtc_set.Data[7]=0;    //RTC设置完毕标志位为0
		can1_send(&bms_rtc_set);
		bms_rtc_set.Data[7]=0;    //RTC设置完毕标志位为0
		can1_send(&bms_rtc_set);
		return 1;  //完成
	}
	else
	{
		printf("RTC Set Error!  \r\n");
		return -1;    //失败
	}



}




/********************************************************************************
 * 函数名称： BatteryCalibration_ModBus_Deal
 * 功能描述： ModBus设置电池标定指令
 * 输入参数：
 * 输出参数： 0 表示写入成功，1表示写入完成，-1表示失败。
 *sqw
 ********************************************************************************/

 int CP_BatteryCalibration_ModBus_Deal(uint16_t address,uint16_t data)
 {
	 static uint8_t SOHCmd,SOCMaxCmd,SOCMinCmd =0;
	 CAN_MESSAGE bms_calibration_msg;
	 if(address == 0x6714)
	 {
		 SOHCmd =(data >> 8);
	 }
	 if(address == 0x6715)
	 {
		 SOCMaxCmd = ( data >> 8);
		 SOCMinCmd = (data & 0xff);
	 }
	 printf("SOHCmd :%d \r\n",SOHCmd);
	 printf("SOCMaxCmd :%d \r\n",SOCMaxCmd);
	 printf("SOCMinCmd :%d \r\n",SOCMinCmd);

	 memset(&bms_calibration_msg, 0 , sizeof(CAN_MESSAGE));
	 bms_calibration_msg.Extended = 1;
	 bms_calibration_msg.Length = 8U;
	 bms_calibration_msg.ID = 0x1822E410;
	 bms_calibration_msg.Data[0] = SOHCmd;
	 bms_calibration_msg.Data[1] = SOCMinCmd;
	 bms_calibration_msg.Data[2] = SOCMaxCmd;
	 printf("bms_calibration_msg.Data[0] :%d \r\n",bms_calibration_msg.Data[0]);
	 printf("bms_calibration_msg.Data[1] :%d \r\n",bms_calibration_msg.Data[1]);
	 printf("bms_calibration_msg.Data[2] :%d \r\n",bms_calibration_msg.Data[2]);
	 can1_send(&bms_calibration_msg);

 }
 

 void CP_set_ems_bms_reboot()
{
	CAN_MESSAGE bms_reboot_msg;
	bms_reboot_msg.ID=0x1CB0E410;
	bms_reboot_msg.Length=1;
	bms_reboot_msg.Extended=1;
	bms_reboot_msg.Remote=0;
	bms_reboot_msg.Data[0]=0xAA;    //设置bms 重启//FF修改为AA

	can1_send(&bms_reboot_msg);
	usleep(250*1000);

	printf("\r\n\r\n  ******* pcs cmd Reset  *******  r\n\r\n");

	system("reboot");//复位并准备跳转

}


