#include "C_Modbus.h"



/* 将int型数据转成BCD码  小数点前4位，小数点后两位  高位在前 */
void  uinttoBCD(unsigned int __ucint,unsigned char *ucbcd)
{
	//100
	ucbcd[0] = (unsigned char)(((__ucint/10000000)%10)<<4);
	ucbcd[0] = (ucbcd[0] | ((unsigned char)((__ucint/1000000)%10)));

	ucbcd[1] = (unsigned char)((__ucint/100000)%10)<<4;
	ucbcd[1] = (ucbcd[1] |((unsigned char)((__ucint/10000)%10)));

	ucbcd[2] = (unsigned char)(((__ucint/1000)%10)<<4);
	ucbcd[2] = (ucbcd[2] | ((unsigned char)((__ucint/100)%10)));

	ucbcd[3] = (unsigned char)((__ucint/10)%10)<<4;
	ucbcd[3] = (ucbcd[3] |((unsigned char)(__ucint%10)));

//	printf("power %d  bcd: 0x%x 0x%x 0x%x 0x%x  \n",
//			__ucint,
//			ucbcd[0],
//			ucbcd[1],
//			ucbcd[2],
//			ucbcd[3]);
}
void debug_printf_data(unsigned char * data_buff,unsigned char  deta_len)
{
    unsigned int i;
    for(i=0;i<deta_len;i++)
    {
        printf(" 0x%02x ",data_buff[i]);
    }
    printf("\r\n");
}
unsigned short int CRC16_Modbus(unsigned char *_pBuf, unsigned short int _usLen)
{
	unsigned char ucCRCHi = 0xFF; /* 高CRC字节初始化 */
	unsigned char ucCRCLo = 0xFF; /* 低CRC 字节初始化 */
	unsigned short int usIndex;  		/* CRC循环中的索引 */

    while (_usLen--)
    {
		usIndex = ucCRCHi ^ *_pBuf++; /* 计算CRC */
		ucCRCHi = ucCRCLo ^ s_CRCHi[usIndex];
		ucCRCLo = s_CRCLo[usIndex];
    }
    return ((unsigned short int)ucCRCHi << 8 | ucCRCLo);
}

signed char modbus_meter_reg_write(unsigned char module_addr,unsigned short int  write_addr,unsigned short int  write_data,unsigned char * data_buff,unsigned char  *deta_len)
{
	unsigned short int crc_data;
	unsigned short int dataLen;
	data_buff[0] = module_addr;

	
	data_buff[1] = DC_METER_WRITE_Register;

	data_buff[2] = (unsigned char)(write_addr>>8);
	data_buff[3] = (unsigned char)(write_addr);
	data_buff[4] = (unsigned char)(write_data>>8);
	data_buff[5] = (unsigned char)(write_data);
	dataLen = 6;
	crc_data = CRC16_Modbus(data_buff, dataLen);
    data_buff[6] = (unsigned char)(crc_data>>8);
    data_buff[7] = (unsigned char)(crc_data);

	*deta_len  = 8;

#ifdef  METER_MODBUS_DEBUG_EN
//	sysUsecTimeprintf();
	zlog_info(debug_out,"meter %d write data :" ,module_addr);
	// printf_data(data_buff,*deta_len);
#endif
	return 0;
}




signed char modbus_meter_reg_read(unsigned char module_addr,unsigned short int  read_addr,unsigned short int  read_len,unsigned char * data_buff,unsigned char  *deta_len)
{
	unsigned short int crc_data;
	unsigned short int dataLen;
	data_buff[0] = module_addr;


	data_buff[1] = DC_METER_READ_Register;

	data_buff[2] = (unsigned char)(read_addr>>8);
	data_buff[3] = (unsigned char)(read_addr);
	data_buff[4] = (unsigned char)(read_len>>8);
	data_buff[5] = (unsigned char)(read_len);
	dataLen = 6;
	crc_data = CRC16_Modbus(data_buff, dataLen);

	data_buff[6] = (unsigned char)(crc_data>>8);
	data_buff[7] = (unsigned char)(crc_data);
	*deta_len  = 8;
#ifdef  METER_MODBUS_DEBUG_EN
//	sysUsecTimeprintf();
	zlog_info(debug_out,"meter %d write data :", module_addr);
	// printf_data(data_buff,*deta_len);
#endif
	return 0;
}

//上面为具体modbus数据填充
//下面为具体电表的功能，如电压、电流


signed char read_rev_data_deal(unsigned char   * data_buff  ,unsigned char  data_len,unsigned short int read_addr,
							 	   MODBUS_METER_DATA * _meter_data,unsigned short int  read_date_len)
{
	Iee32_byte_int_flot  data_temp;
	unsigned char *pnew_data_buff = NULL;
	unsigned char new_data_len =0;
	int i;
#ifdef  METER_MODBUS_DEBUG_EN
//	sysUsecTimeprintf();
	zlog_info(debug_out,"meter %d read data %d: \r\n" ,_meter_data->Meter_addr,data_len);
	// printf_data(data_buff,data_len);
#endif

	for(i=0;i<data_len;i++){
		if(data_buff[i] == _meter_data->Meter_addr)
		{
			pnew_data_buff = &data_buff[i];
			new_data_len   = data_len-i;
			break;
		}
	}
	if(new_data_len < ((read_date_len*2)+5)){
		return -1;
	}
	

    if(CRC16_Modbus(pnew_data_buff,(read_date_len*2)+3 ) == ((pnew_data_buff[(read_date_len*2)+3 ]<<8 )|(pnew_data_buff[(read_date_len*2)+3+1])))
    {
        if((_meter_data->Meter_addr == pnew_data_buff[0])&&(DC_METER_READ_Register == pnew_data_buff[1])){

            if(read_addr == ADDR_READ_DC_VOLT){ /* 是读取电压 */
                if( pnew_data_buff[2] >= 4)
                {
                    pthread_mutex_lock(&(_meter_data->Meter_mutex));
                    _meter_data->dc_line_volt_10mv = 0;
                    _meter_data->dc_line_volt_10mv |= (pnew_data_buff[3]<<24);
                    _meter_data->dc_line_volt_10mv |= (pnew_data_buff[4]<<16);
                    _meter_data->dc_line_volt_10mv |= (pnew_data_buff[5]<<8);
                    _meter_data->dc_line_volt_10mv |= (pnew_data_buff[6]<<0);
                    pthread_mutex_unlock(&(_meter_data->Meter_mutex));
                    #ifdef  METER_MODBUS_DEBUG_EN
                        printf("module addr: %d volt:  %d/1000V  \r\n" ,_meter_data->Meter_addr,_meter_data->dc_line_volt_10mv);
                    #endif
                    return 0;
                }
            }
            if(read_addr == ADDR_READ_DC_CURR ){ /* 是读取功率 */
                if( pnew_data_buff[2] >= 4)
                {
                    pthread_mutex_lock(&(_meter_data->Meter_mutex));
                    _meter_data->dc_line_curr_ma = 0;
                    _meter_data->dc_line_curr_ma |= (pnew_data_buff[3]<<24);
                    _meter_data->dc_line_curr_ma |= (pnew_data_buff[4]<<16);
                    _meter_data->dc_line_curr_ma |= (pnew_data_buff[5]<<8);
                    _meter_data->dc_line_curr_ma |= (pnew_data_buff[6]<<0);
                    pthread_mutex_unlock(&(_meter_data->Meter_mutex));
                    #ifdef  METER_MODBUS_DEBUG_EN
                        printf("module addr: %d curr:  %d*ma \r\n" ,_meter_data->Meter_addr,_meter_data->dc_line_curr_ma);
                    #endif
                    return 0;
                }
            }
            if(read_addr == ADDR_READ_DC_POWER){ /* 是读取电流*/
                if( pnew_data_buff[2] >= 4)
                {
                    pthread_mutex_lock(&(_meter_data->Meter_mutex));
                    _meter_data->dc_line_power_10wh = 0;
                    _meter_data->dc_line_power_10wh |= (pnew_data_buff[3]<<24);
                    _meter_data->dc_line_power_10wh |= (pnew_data_buff[4]<<16);
                    _meter_data->dc_line_power_10wh |= (pnew_data_buff[5]<<8);
                    _meter_data->dc_line_power_10wh |= (pnew_data_buff[6]<<0);
                    uinttoBCD((unsigned int)(_meter_data->dc_line_power_10wh),_meter_data->ucbcd_dc_Total_Import_kWh);
                    pthread_mutex_unlock(&(_meter_data->Meter_mutex));
                    #ifdef  METER_MODBUS_DEBUG_EN
                        printf("module addr: %d power:  %u/100kwh \r\n" ,_meter_data->Meter_addr,_meter_data->dc_line_power_10wh );
                    #endif
                    return 0;
                }
            }
        }else{
            return -2;
        }
    }else{
        // zlog_info(debug_out,"module addr: %d meter crc check fail \r\n",_meter_data->Meter_addr);
        // printf_data(data_buff,data_len);
    }

}

