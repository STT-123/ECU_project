

#ifndef __BATDATA_H__
#define __BATDATA_H__


#pragma pack(push, 1)
typedef struct 
{
    /* data 命名修改按智充代码规范*/
    unsigned int            uiTimeStamp;           /*时间戳4 字节*/
    
    /*电池数据480+240+60+60*/
    unsigned short          usSingleBatVal[240];     /*单体电池电压单位0.001V*/
    unsigned short          usSingleBatTemp[120];    /*单体电池温度*/
    unsigned int            uiBmuErrorNum[15];       /*消防版故障*/
    unsigned int            uiBmuExErrorNum[15];     /*消防板子故障扩展*/
    /*电表数据20字节*/
    int                     iDcPower;               /*直流功率*/
    unsigned long long      ullPosEleQuantity;     /*正电能*/    
    unsigned long long      ullNegEleQuantity;     /*负电能*/
    /*空调和环境数据共24字节*/
    unsigned short          usAirState;            /*空调开状态*/
    unsigned short          usAirPumpState;        /*水泵状态*/
    unsigned short          usAirCompressorSta;    /*空调压缩机1状态*/
    unsigned int            uiAirErrorLv1;         /*空调1级故障*/
    unsigned int            uiAirErrorLv2;         /*空调2级故障*/
    unsigned int            uiAirErrorLv3;         /*空调3级故障*/
    unsigned short          usTempInside;          /*机箱内部温度*/
    unsigned short          usTempOutside;         /*机箱外部温度*/
    unsigned short          usHumidityInside;      /*机箱内部湿度*/
    /*消防板bmu数据共32字节*/
    /* 消防数据共32字节 */
    unsigned short usBmuH2MaxConcentration;        /* 消防H2最大浓度 (1ppm) */
    unsigned short usBmuH2MinConcentration;        /* 消防H2最小浓度 (1ppm) */
    unsigned short usBmuCOMaxConcentration;        /* 消防CO最大浓度 (1ppm) */
    unsigned short usBmuCOMinConcentration;        /* 消防CO最小浓度 (1ppm) */
    unsigned short usBmuPressureMax;               /* 消防最大气压 (1kPa) */
    unsigned short usBmuPressureMin;               /* 消防最小气压 (1kPa) */
    unsigned short usBmuLightMax;                  /* 消防最大光照强度 (1℃) */
    unsigned short usBmuLightMin;                  /* 消防最小光照强度 (1℃) */
    unsigned short usBmuH2MaxIndex;                /* H2最大浓度编号 */
    unsigned short usBmuH2MinIndex;                /* H2最小浓度编号 */
    unsigned short usBmuCOMaxIndex;                /* CO最大浓度编号 */
    unsigned short usBmuCOMinIndex;                /* CO最小浓度编号 */
    unsigned short usBmuPressureMaxIndex;          /* 最大气压编号 */
    unsigned short usBmuPressureMinIndex;          /* 最小气压编号 */
    unsigned short usBmuLightMaxIndex;             /* 最大光照强度编号 */
    unsigned short usBmuLightMinIndex;             /* 最小光照强度编号 */

    /* 空调扩展信息共12字节 */
    unsigned short usAirEnergyMode;                /* 空调节能模式：0正常、1节能 */
    unsigned short usAirInletPressure;             /* 空调水系统入口压力 (0.1bar) */
    unsigned short usAirCoolSetTemp;               /* 空调制冷设定温度 (0.1℃) */
    unsigned short usAirHeatSetTemp;               /* 空调加热设定温度 (0.1℃) */
    unsigned short usAirOutWaterTemp;              /* 空调出水温度 (0.1℃) */
    unsigned short usAirReturnWaterTemp;           /* 空调回水温度 (0.1℃) */

    /* 电池摘要信息共24字节 */
    unsigned short usBatMaxVoltCellIndex;         /* 最大电压电池号 */
    unsigned short usBatMinVoltCellIndex;         /* 最小电压电池号 */
    unsigned short usBatMaxTempCellIndex;         /* 最大温度电池号 */
    unsigned short usBatMinTempCellIndex;         /* 最小温度电池号 */
    unsigned short usBatCellVoltMax;              /* 单节电压最大值 (0.001V) */
    unsigned short usBatCellVoltMin;              /* 单节电压最小值 (0.001V) */
    unsigned short usBatMaxTempCellVolt;          /* 最大温度电池电压 (0.001V) */
    unsigned short usBatMinTempCellVolt;          /* 最小温度电池电压 (0.001V) */
    unsigned short usBatCellTempMax;              /* 单节温度最大值 (1℃) */
    unsigned short usBatCellTempMin;              /* 单节温度最小值 (1℃) */
    unsigned short usBatMaxVoltCellTemp;          /* 最大电压电池温度 (1℃) */
    unsigned short usBatMinVoltCellTemp;          /* 最小电压电池温度 (1℃) */


}tBatData;
#pragma pack(pop)

void convert_tBatData_to_big_endian(tBatData *dst, const tBatData *src);

#endif // !__BATDATA_H__
