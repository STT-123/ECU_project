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
