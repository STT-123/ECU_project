#ifdef INVALID_CAN_ID

#else
#include"can_message.h"

#include "rtwtypes.h"



//typedef uint8_T uint8;
typedef int8_T sint8;
typedef uint16_T uint16;
typedef uint8_T uint8;
typedef uint32_T uint32;
typedef int32_T sint32;

typedef CAN_MESSAGE_BUS CAN_SendBuffType;

typedef CAN_MESSAGE_BUS CAN_MsgBuffType;

typedef struct{
	uint16 BALTime[16];
	uint16 BALPWM[16];
} BALStruct;

uint8 CANInit(uint8 channelID,uint8 baudrate_ID);

void CANDeinit(uint8 channelID);

void CANSendMsg(uint8 channelID,const CAN_MESSAGE_BUS *data);

void CANReceiveMsg(uint8 channelID,CAN_MESSAGE_BUS *data);


sint8 DinGetChanState(uint8 ChannelIDIn);
//0：低电平       1：高电平       -1：通道号错误

sint8 DoutSetChanState(uint8 ChannelIDOut, uint8 State);
// 0：成功           -1：通道号错误           -2：State参数错误

sint8 OpenADC(void);
//0：表示成功        -1：表示状态错误         -2：表示超时  -3：表示ADC_ID错误

sint8 CloseADC(void);
//   0：表示成功         -1：表示状态错误         -2：表示超时
sint8 ADCGetChanResult(uint8 ChannelID,uint16 *ADCValue);

// 0：表示成功         -1：表示通道号错误       -2：表示ADCValue地址不合法



sint8 OpenAfe(uint8 NumOf33774, uint8 NumOf33772);

//0：表示成功        -1：表示初始化33665失败         -2：表示初始化33774失败      -3：表示初始化33772失败


sint8 CloseAfe(void);
// 0：表示成功        -1：表示关闭33665失败         -2：表示关闭33774失败    -3：表示关闭33772失败


sint8 AfeGet33774Voltage(uint8 PackAddr, uint32 *VoltageBuff, uint32 *BuffSize);
//PackAddr： 电池包地址（地址范围：0<PackAddr<= NumOf33774）
//VoltageBuff：电芯电压输出地址 单位：mV
//BuffSize：返回的电芯电压个数（默认为17 包括16节电芯电压+1个总电压）
//返回值：	0：表示成功        -1：表示AFE模块未开启         -2：表示Pack地址错误   -3：表示VoltageBuff地址不合法   -4：表示BuffSize不合法
sint8 AfeGet33774Temp(uint8 PackAddr, sint32 *TempBuff, uint32 *BuffSize);
//
//PackAddr： 电池包地址（地址范围：0<PackAddr<= NumOf33774）
//TempBuff：温度输出地址  单位：0.01℃
//BuffSize：返回的温度数量（默认为9 包括8节点电芯温度+1个环境温度）
//返回值：	0：表示成功        -1：表示AFE模块未开启         -2：表示Pack地址错误   -3：表示TempBuff地址不合法   -4：表示BuffSize不合法

sint8 AfeGet33774BALStatus(uint8 PackAddr, BALStruct *BALStatusBuff);
//PackAddr： 电池包地址（地址范围：0<PackAddr<= NumOf33774）
//BALStatusBuff：均衡状态输出地址
//返回值：	0：表示成功        -1：表示AFE模块未开启         -2：表示Pack地址错误   -3：表示BALStatusBuff地址不合法

sint8 AfeSet33774BALStatus(uint8 PackAddr, BALStruct *BALStatusBuff);
//设置均衡状态。
//输入量：
//PackAddr： （地址范围：0<PackAddr<= NumOf33774）
//BALStatusBuff：均衡状态参数地址
//返回值：0：表示成功  -1：表示AFE模块未开启   -2：表示Pack地址错误   -3：表示BALStatusBuff地址不合法


//BALTime：均衡的时长
// 0：不开启均衡
//N(1~3FFFH)：开启N*10 s时长的均衡
//BALPWM: 均衡的占空比
         // N(0~FFH):  占空比系数 N/255*100%


sint8 SystemBSWInit(void);
 //0：表示成功  
//-1：表示系统时钟初始化失败  
//-2：表示管脚初始化失败
//-3：表示中断初始化失败
//-4：表示AFE采集模块初始化失败
//-5：表示ADS系统采集模块初始化失败
//-40：表示1ms定时器中断开启失败


sint8 AfeGet33772Voltage(uint8 PackAddr, uint32 *VoltageBuff);   


// 获取总电压值，返回储能单元总电压值。
// 输入量：
// PackAddr： 33772地址（地址范围：0<PackAddr<= NumOf33772）
// VoltageBuff：电压输出地址 单位：mV
// 返回值：
// 0：成功        					-1：AFE模块未开启         
// -2：Pack地址错误                 -3：VoltageBuff地址不合法   



sint8 AfeGet33772Current(uint8 PackAddr, sint32 *CurrentBuff);  
// 获取电流值，返回储能单元电流值。
// 输入量：
// PackAddr： 33772地址（地址范围：0<PackAddr<= NumOf33772）
// CurrentBuff：电流输出地址 单位：mA  大于0为放电 小于0为充电
// 返回值：
// 0：成功        					-1：AFE模块未开启         
// -2：Pack地址错误                 -3：CurrentBuff地址不合法   

sint8 AfeGet33772Temp(uint8 PackAddr, sint32 *TempBuff, uint32 *BuffSize);
// 获取温度数据，返回储能单元温度值。
// 输入量：
// PackAddr： 33772地址（地址范围：0<PackAddr<= NumOf33772）
// TempBuff：温度输出地址 单位：0.01℃ 
// BuffSize：返回的温度数量（默认为4 包括3节点温度值+1个芯片温度值）
// 返回值：
// 0：成功        					-1：AFE模块未开启         
// -2：Pack地址错误                 -3：CurrentBuff地址不合法   
// -4：BuffSize地址不合法

 sint8 ADS101xGetV2(uint32 *V2Value);
//   读取高压V2的电压值
// 输入量：
// V2Value： 电压输出地址 单位：mV
// 返回值：
// 0：成功        					-1：ADS101x模块未开启         
//  -2：V2Value地址不合法


sint8 ADS101xGetV3(uint32 *V3Value);
//   读取高压V3的电压值
// 输入量：
// V3Value： 电压输出地址 单位：mV
// 返回值：
// 0：成功        					-1：ADS101x模块未开启         
//  -2：V3Value地址不合法

  sint8 ADS101xGetIMDVol(uint16 *IMDPosVol,uint16 *IMDNegVol);
//   读取绝缘检测采集正负极电压值
// 输入量：
// IMDPosVol： 正极电压输出地址 单位：mV
// IMDNegVol：负极电压输出地址 单位：mV
// 返回值：
// 0：成功        					-1：ADS101x模块未开启         
//  -2：IMDPosVol/ IMDNegVol地址不合法


void Debug_Printf(const char *format,sint32 data);
// 
// （3）绝缘检测控制正极设置接口函数：
 	sint8 IMDCtrlRdcPSet(uint8 State);
// 
//       	0：成功  -1：State参数错误（>1）
// （4）绝缘检测控制负极设置接口函数：
 	sint8 IMDCtrlRdcNSet(uint8 State);
// 输入量:
//      State: 设置状态，0为低电平，1为高电平
// 返回值：
//       	0：成功  -1：State参数错误（>1）
// （5）绝缘检测开关正极设置接口函数：
 	sint8 IMDSwRdcPSet(uint8 State);
// 输入量:
//      State: 设置状态，0为低电平，1为高电平
// 返回值：
//       	0：成功  -1：State参数错误（>1）
// （6）绝缘检测开关负极设置接口函数：
 	sint8 IMDSwRdcNSet(uint8 State);
// 输入量:
//      State: 设置状态，0为低电平，1为高电平
// 返回值：
//       	0：成功  -1：State参数错误（>1）
// （7）绝缘检测控制地设置接口函数：
 	sint8 IMDCtrlEarthSet(uint8 State);
// 输入量:
//      State: 设置状态，0为低电平，1为高电平
// 返回值：
//       	0：成功  -1：State参数错误（>1）
#endif

