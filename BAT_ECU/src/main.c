#include "message_queue.h"
#include "sqlite_storage.h"
#include "ocpp_messages.h"
#include "batdata.h"
#include "project.h"

#include "log/log.h"

#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "./GLB/G_GloabalVariable.h"
#include "./GLB/G_SystemConf.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"
#include "./DRV/Drv_ECUAndBMUCommunication.h"
#include "./DRV/Drv_ExternalCANCommunication.h"
#include "./DRV/Drv_SDCard.h"
#include "port/myepoll.h"
#include "log/log.h"
#include "./CP/BMS/bms/CANRcvFcn.h"

#include "./TASK/Net_Config_Task.h"
#include "./TASK/OTA_Upgrad_Task.h"

OTAObject otactrl;
void all_init(void);
void all_thread_init(void);
void update_bat_data(sqlite3 *db);

struct tm utc_timeinfo;

int main(int argc, char **argv)
{
    int counter = 60;
    sqlite3 *db;
    init_db(&db);

    /*硬件接口初始化部分*/
    all_init();

    /*任务线程初始化*/
    all_thread_init();

    while (1)
    {
        enqueue_message(build_heartbeat());

        sleep(1);
        update_bat_data(db); // 更新电池数据

        if (++counter >= 60)
        {
            counter = 0;
            int ids[REPORT_COUNT];
            int count = 0;

            // enqueue_message(compress_detail_data(db, ids, &count));
            struct json_object *json = compress_detail_data(db, ids, &count);
            if (json)
            {
                if (enqueue_message(json))
                {
                    delete_data_by_ids(db, ids, count);
                }
            }
        }
        usleep(1 * 1000);
    }
}

static void printf_version(void)
{
    char compile_date[12] = {0}, compile_time[20] = {0};
    sprintf(compile_date, "%s", __DATE__);
    sprintf(compile_time, "%s", __TIME__);
    LOG("========================================================= \n");
    LOG("[VERSION] BAT ECU_EU START RUN!!!. \n");
    LOG("[VERSION] Software compilation time %s--%s. \n", compile_date, compile_time);
    LOG("========================================================= \n");
}

void all_init(void)
{
    // 日志初始化
    log_init();
    printf_version();

    // can通信功能
    my_epoll_init(); // 初始化epoll环境
    Drv_can0_init(); // ecu 和 bcu通信can初始化（打开can口 绑定回调）
    Drv_can1_init(); // ecu 和 bmu通信can初始化（打开can口 绑定回调）
    Drv_can2_init(); // ecu 和 外部can初始化（打开can口 绑定回调）

    /* SD卡存储相关 */
    Drv_init_double_ring_buffer(&canDoubleRingBuffer); // 初始化往sd卡写数据用的双环形缓冲区
    Drv_init_can_id_history();                         // 初始化往SD卡写的can消息的缓存区

    // 判断本机IP 如果不存在 默认使用110
    G_settings_init();

    // 初始化急停IO
    gpio_all_init();

    // OCPP初始化
    enqueue_message(build_boot_notification());
}

void all_thread_init(void)
{
    CAN0RecvDelTaskCreate();

    CAN1RecvDelTaskCreate();

    FtpServiceThreadCreate();

    OTAUpgradTaskCreate();

    NETConfigTaskCreate();

    TcpServerExampleTaskCreate();

    SDCardDataSaveTaskCreate(); // SD卡写任务

    GPIODetectionTaskCreate(); // 异常监测任务

    SDCapacityChenkTaskCreate();

    OCPPCommunicationTaskCreate();
}

// ✅ 每秒更新一次数据（可由外部线程或主循环调用）
void update_bat_data(sqlite3 *db)
{
    tBatData data = {0};
    tBatData data_be = {0};
    uint16_t DAq_version1;
    uint16_t DAq_version2;
    uint16_t DAq_version3;
    uint16_t DAq_version4;
    uint16_t DAq_version5;
    uint16_t DAq_version6;
    uint16_t DAq_version7;
    uint16_t DAq_version8;
    uint16_t DAq_version9;
    uint16_t DAq_version10;
    uint16_t DAq_version11;
    uint16_t DAq_version12;
    uint16_t DAq_version13;
    uint16_t DAq_version14;
    uint16_t DAq_version15;

    CP_get_modbus_reg_val(0x5000, &DAq_version1);
    CP_get_modbus_reg_val(0x5001, &DAq_version2);
    CP_get_modbus_reg_val(0x5002, &DAq_version3);
    CP_get_modbus_reg_val(0x5003, &DAq_version4);
    CP_get_modbus_reg_val(0x5004, &DAq_version5);
    CP_get_modbus_reg_val(0x5005, &DAq_version6);
    CP_get_modbus_reg_val(0x5006, &DAq_version7);
    CP_get_modbus_reg_val(0x5007, &DAq_version8);
    CP_get_modbus_reg_val(0x5008, &DAq_version9);
    CP_get_modbus_reg_val(0x5009, &DAq_version10);
    CP_get_modbus_reg_val(0x500A, &DAq_version11);
    CP_get_modbus_reg_val(0x500B, &DAq_version12);
    CP_get_modbus_reg_val(0x500C, &DAq_version13);
    CP_get_modbus_reg_val(0x500D, &DAq_version14);
    CP_get_modbus_reg_val(0x500E, &DAq_version15);

    memcpy(data.usSingleBatVal, CANRcvFcn_DW.tmp, sizeof(data.usSingleBatVal));
    memcpy(data.usSingleBatTemp, CANRcvFcn_DW.tmp_a, sizeof(data.usSingleBatTemp));

    // 使用类似 DAq_version1 的逻辑补全其余字段
    if (DAq_version1 != 0)
    {
        data.uiBmuErrorNum[0] = CANRcvFcn_B.ux180110E16_o1;
        data.uiBmuExErrorNum[0] = CANRcvFcn_B.ux180110E16_o2;
    }
    else
    {
        data.uiBmuErrorNum[0] = 65535;
        data.uiBmuExErrorNum[0] = 65535;
    }

    if (DAq_version2 != 0)
    {
        data.uiBmuErrorNum[1] = CANRcvFcn_B.ux180110E17_o1;
        data.uiBmuExErrorNum[1] = CANRcvFcn_B.ux180110E17_o2;
    }
    else
    {
        data.uiBmuErrorNum[1] = 65535;
        data.uiBmuExErrorNum[1] = 65535;
        // printf("65535_CANRcvFcn_B.ux180110E17_o1 = %d\n", CANRcvFcn_B.ux180110E17_o1);
    }

    if (DAq_version3 != 0)
    {
        data.uiBmuErrorNum[2] = CANRcvFcn_B.ux180110E18_o1;
        data.uiBmuExErrorNum[2] = CANRcvFcn_B.ux180110E18_o2;
    }
    else
    {
        data.uiBmuErrorNum[2] = 65535;
        data.uiBmuExErrorNum[2] = 65535;
    }

    if (DAq_version4 != 0)
    {
        data.uiBmuErrorNum[3] = CANRcvFcn_B.ux180110E19_o1;
        data.uiBmuExErrorNum[3] = CANRcvFcn_B.ux180110E19_o2;
    }
    else
    {
        data.uiBmuErrorNum[3] = 65535;
        data.uiBmuExErrorNum[3] = 65535;
    }

    if (DAq_version5 != 0)
    {
        data.uiBmuErrorNum[4] = CANRcvFcn_B.ux180110E20_o1;
        data.uiBmuExErrorNum[4] = CANRcvFcn_B.ux180110E20_o2;
    }
    else
    {
        data.uiBmuErrorNum[4] = 65535;
        data.uiBmuExErrorNum[4] = 65535;
    }

    if (DAq_version6 != 0)
    {
        data.uiBmuErrorNum[5] = CANRcvFcn_B.ux180110E21_o1;
        data.uiBmuExErrorNum[5] = CANRcvFcn_B.ux180110E21_o2;
    }
    else
    {
        data.uiBmuErrorNum[5] = 65535;
        data.uiBmuExErrorNum[5] = 65535;
    }

    if (DAq_version7 != 0)
    {
        data.uiBmuErrorNum[6] = CANRcvFcn_B.ux180110E22_o1;
        data.uiBmuExErrorNum[6] = CANRcvFcn_B.ux180110E22_o2;
    }
    else
    {
        data.uiBmuErrorNum[6] = 65535;
        data.uiBmuExErrorNum[6] = 65535;
    }

    if (DAq_version8 != 0)
    {
        data.uiBmuErrorNum[7] = CANRcvFcn_B.ux180110E23_o1;
        data.uiBmuExErrorNum[7] = CANRcvFcn_B.ux180110E23_o2;
    }
    else
    {
        data.uiBmuErrorNum[7] = 65535;
        data.uiBmuExErrorNum[7] = 65535;
    }

    if (DAq_version9 != 0)
    {
        data.uiBmuErrorNum[8] = CANRcvFcn_B.ux180110E24_o1;
        data.uiBmuExErrorNum[8] = CANRcvFcn_B.ux180110E24_o2;
    }
    else
    {
        data.uiBmuErrorNum[8] = 65535;
        data.uiBmuExErrorNum[8] = 65535;
    }

    if (DAq_version10 != 0)
    {
        data.uiBmuErrorNum[9] = CANRcvFcn_B.ux180110E25_o1;
        data.uiBmuExErrorNum[9] = CANRcvFcn_B.ux180110E25_o2;
    }
    else
    {
        data.uiBmuErrorNum[9] = 65535;
        data.uiBmuExErrorNum[9] = 65535;
    }

    if (DAq_version11 != 0)
    {
        data.uiBmuErrorNum[10] = CANRcvFcn_B.ux180110E26_o1;
        data.uiBmuExErrorNum[10] = CANRcvFcn_B.ux180110E26_o2;
    }
    else
    {
        data.uiBmuErrorNum[10] = 65535;
        data.uiBmuExErrorNum[10] = 65535;
    }

    if (DAq_version12 != 0)
    {
        data.uiBmuErrorNum[11] = CANRcvFcn_B.ux180110E27_o1;
        data.uiBmuExErrorNum[11] = CANRcvFcn_B.ux180110E27_o2;
    }
    else
    {
        data.uiBmuErrorNum[11] = 65535;
        data.uiBmuExErrorNum[11] = 65535;
    }

    if (DAq_version13 != 0)
    {
        data.uiBmuErrorNum[12] = CANRcvFcn_B.ux180110E28_o1;
        data.uiBmuExErrorNum[12] = CANRcvFcn_B.ux180110E28_o2;
    }
    else
    {
        data.uiBmuErrorNum[12] = 65535;
        data.uiBmuExErrorNum[12] = 65535;
    }

    if (DAq_version14 != 0)
    {
        data.uiBmuErrorNum[13] = CANRcvFcn_B.ux180110E29_o1;
        data.uiBmuExErrorNum[13] = CANRcvFcn_B.ux180110E29_o2;
    }
    else
    {
        data.uiBmuErrorNum[13] = 65535;
        data.uiBmuExErrorNum[13] = 65535;
    }

    if (DAq_version15 != 0)
    {
        data.uiBmuErrorNum[14] = CANRcvFcn_B.ux180110E30_o1;
        data.uiBmuExErrorNum[14] = CANRcvFcn_B.ux180110E30_o2;
    }
    else
    {
        data.uiBmuErrorNum[14] = 65535;
        data.uiBmuExErrorNum[14] = 65535;
    }
    // printf(" data.uiBmuErrorNum[0]:%d\r\n", data.uiBmuErrorNum[0]);
    // printf(" data.uiBmuErrorNum[1]:%d\r\n", data.uiBmuErrorNum[1]);
    // printf(" data.uiBmuErrorNum[2]:%d\r\n", data.uiBmuErrorNum[2]);
    // printf(" data.uiBmuErrorNum[3]:%d\r\n", data.uiBmuErrorNum[3]);
    // printf(" data.uiBmuErrorNum[4]:%d\r\n", data.uiBmuErrorNum[4]);
    // printf(" data.uiBmuErrorNum[5]:%d\r\n", data.uiBmuErrorNum[5]);
    // printf(" data.uiBmuErrorNum[6]:%d\r\n", data.uiBmuErrorNum[6]);
    // printf(" data.uiBmuErrorNum[7]:%d\r\n", data.uiBmuErrorNum[7]);
    // printf(" data.uiBmuErrorNum[8]:%d\r\n", data.uiBmuErrorNum[8]);
    // printf(" data.uiBmuErrorNum[9]:%d\r\n", data.uiBmuErrorNum[9]);
    // printf(" data.uiBmuErrorNum[10]:%d\r\n", data.uiBmuErrorNum[10]);
    // printf(" data.uiBmuErrorNum[11]:%d\r\n", data.uiBmuErrorNum[11]);
    // printf(" data.uiBmuErrorNum[12]:%d\r\n", data.uiBmuErrorNum[12]);
    // printf(" data.uiBmuErrorNum[13]:%d\r\n", data.uiBmuErrorNum[13]);
    // printf(" data.uiBmuErrorNum[14]:%d\r\n", data.uiBmuErrorNum[14]);
    // printf(" data.uiBmuErrorNum[15]:%d\r\n", data.uiBmuErrorNum[15]);

    data.iDcPower = CANRcvFcn_B.CANFDUnpack3_o7;
    // data.iDcPower = 100;
    // printf("iDcPower = %d\n",data.iDcPower);
    data.ullPosEleQuantity = CANRcvFcn_B.CANFDUnpack3_o5;
    // printf("ullPosEleQuantity = %llu\n",data.ullPosEleQuantity);
    data.ullNegEleQuantity = CANRcvFcn_B.CANFDUnpack3_o2;
    // printf("ullNegEleQuantity = %llu\n",data.ullNegEleQuantity);

    data.usAirState = CANRcvFcn_B.CANFDUnpack3_o20;
    // printf("usAirState = %d\n",data.usAirState);
    data.usAirPumpState = CANRcvFcn_B.CANFDUnpack3_o24;
    // printf("usAirPumpState = %d\n",data.usAirPumpState);
    data.usAirCompressorSta = CANRcvFcn_B.CANFDUnpack3_o21;
    // printf("usAirCompressorSta = %d\n",data.usAirCompressorSta);

    // int faultCode = CANRcvFcn_B.CANFDUnpack3_o33;
    // data.uiAirErrorLv1 = 0;
    // data.uiAirErrorLv2 = 0;
    // data.uiAirErrorLv3 = 0;
    // if (faultCode == 1 || faultCode == 3 || faultCode == 28) {
    //     data.uiAirErrorLv1 = faultCode;
    //     printf("Air Error Lv1: %d\n", faultCode);
    // } else if ((faultCode >= 4 && faultCode <= 5) ||
    //         (faultCode >= 8 && faultCode <= 17) ||
    //         (faultCode >= 20 && faultCode <= 22) ||
    //         faultCode == 25 ||
    //         faultCode == 29 ||
    //         faultCode == 30 ||
    //         faultCode == 31) {
    //     data.uiAirErrorLv2 = faultCode;
    //     printf("Air Error Lv2: %d\n", faultCode);
    // } else if (faultCode == 18 || faultCode == 19 || faultCode == 23 ||
    //         faultCode == 24 || faultCode == 26 || faultCode == 27) {
    //     data.uiAirErrorLv3 = faultCode;
    //     printf("Air Error Lv3: %d\n", faultCode);
    // }
    int faultCode = CANRcvFcn_B.CANFDUnpack3_o33;
    data.uiAirErrorLv1 = 0;
    data.uiAirErrorLv2 = 0;
    data.uiAirErrorLv3 = 0;

    // Lv1 错误判断
    if (faultCode == 1)
    {
        data.uiAirErrorLv1 |= (1U << 1);
        // printf("Air Error Lv1: %d -> bit1\n", faultCode);
    }
    if (faultCode == 3)
    {
        data.uiAirErrorLv1 |= (1U << 3);
        // printf("Air Error Lv1: %d -> bit3\n", faultCode);
    }
    if (faultCode == 28)
    {
        data.uiAirErrorLv1 |= (1U << 28);
        // printf("Air Error Lv1: %d -> bit28\n", faultCode);
    }

    // Lv2 错误判断
    if (faultCode == 4 || faultCode == 5 ||
        (faultCode >= 8 && faultCode <= 17) ||
        (faultCode >= 20 && faultCode <= 22) ||
        faultCode == 25 || faultCode == 29 ||
        faultCode == 30 || faultCode == 31)
    {

        data.uiAirErrorLv2 |= (1U << faultCode);
        // printf("Air Error Lv2: %d -> bit%d\n", faultCode, faultCode);
    }

    // Lv3 错误判断
    if (faultCode == 18 || faultCode == 19 ||
        faultCode == 23 || faultCode == 24 ||
        faultCode == 26 || faultCode == 27)
    {

        data.uiAirErrorLv3 |= (1U << faultCode);
        // printf("Air Error Lv3: %d -> bit%d\n", faultCode, faultCode);
    }

    data.usTempInside = CANRcvFcn_B.CANFDUnpack3_o34;
    data.usTempOutside = CANRcvFcn_B.CANFDUnpack3_o36;
    data.usHumidityInside = 0;

    data.usBmuH2MaxConcentration = CANRcvFcn_B.CANFDUnpack_o34;
    // printf("data.usBmuH2MaxConcentration :%d\r\n",data.usBmuH2MaxConcentration);
    data.usBmuH2MinConcentration = 0;
    data.usBmuCOMaxConcentration = CANRcvFcn_B.CANFDUnpack_o32;
    // printf("data.usBmuCOMaxConcentration :%d\r\n",data.usBmuCOMaxConcentration);
    data.usBmuCOMinConcentration = 0;
    data.usBmuPressureMax = CANRcvFcn_B.CANFDUnpack_o38;
    // printf("data.usBmuPressureMax :%d\r\n",data.usBmuPressureMax);
    data.usBmuPressureMin = 0;
    data.usBmuLightMax = CANRcvFcn_B.CANFDUnpack_o36;
    data.usBmuLightMin = 0;
    data.usBmuH2MaxIndex = CANRcvFcn_B.CANFDUnpack_o33;
    data.usBmuCOMaxIndex = CANRcvFcn_B.CANFDUnpack_o31;
    data.usBmuCOMinIndex = 0;
    data.usBmuPressureMaxIndex = CANRcvFcn_B.CANFDUnpack_o37;
    data.usBmuPressureMinIndex = 0;
    data.usBmuLightMaxIndex = CANRcvFcn_B.CANFDUnpack_o35;
    data.usBmuLightMinIndex = 0;

    data.usAirEnergyMode = CANRcvFcn_B.CANFDUnpack3_o17;
    // data.usAirEnergyMode = 1;
    // printf("data.usAirEnergyMode :%d\r\n",data.usAirEnergyMode);
    data.usAirInletPressure = CANRcvFcn_B.CANFDUnpack3_o18;
    data.usAirCoolSetTemp = CANRcvFcn_B.CANFDUnpack3_o15 * 10;
    data.usAirHeatSetTemp = CANRcvFcn_B.CANFDUnpack3_o27 * 10;
    data.usAirOutWaterTemp = CANRcvFcn_B.CANFDUnpack3_o36 * 10;
    // printf("data.usAirOutWaterTemp :%d\r\n",data.usAirOutWaterTemp);
    data.usAirReturnWaterTemp = CANRcvFcn_B.CANFDUnpack3_o34 * 10;
    // printf("data.usAirReturnWaterTemp :%d\r\n",data.usAirReturnWaterTemp);

    data.usBatMaxVoltCellIndex = CANRcvFcn_B.CANFDUnpack2_o42;
    data.usBatMinVoltCellIndex = CANRcvFcn_B.CANFDUnpack2_o44;
    data.usBatMaxTempCellIndex = CANRcvFcn_B.CANFDUnpack2_o14;
    data.usBatMinTempCellIndex = CANRcvFcn_B.CANFDUnpack2_o21;
    data.usBatCellVoltMax = CANRcvFcn_B.CANFDUnpack2_o37;
    data.usBatCellVoltMin = CANRcvFcn_B.CANFDUnpack2_o41;
    // data.usBatMaxTempCellVolt =CANRcvFcn_B.CANFDUnpack2_o43;
    // data.usBatMinTempCellVolt =CANRcvFcn_B.CANFDUnpack2_o45;
    data.usBatMaxTempCellVolt = 0;
    data.usBatMinTempCellVolt = 0;
    data.usBatCellTempMax = CANRcvFcn_B.CANFDUnpack2_o19;
    data.usBatCellTempMin = CANRcvFcn_B.CANFDUnpack2_o24;
    data.usBatMaxVoltCellTemp = CANRcvFcn_B.CANFDUnpack2_o3;
    data.usBatMinVoltCellTemp = CANRcvFcn_B.CANFDUnpack2_o4;

    utc_timeinfo.tm_year = BCU_TimeYear + 100; // BCU年是如24，tm_year从1900起
    utc_timeinfo.tm_mon = BCU_TimeMonth - 1;   // BCU月是1~12，tm_mon是0~11
    utc_timeinfo.tm_mday = BCU_TimeDay;
    utc_timeinfo.tm_hour = BCU_TimeHour - 8;
    utc_timeinfo.tm_min = BCU_TimeMinute;
    utc_timeinfo.tm_sec = BCU_TimeSencond;
    utc_timeinfo.tm_isdst = -1;

    // utc_timeinfo.tm_hour -= 8;
    time_t t = mktime(&utc_timeinfo);
    data.uiTimeStamp = (unsigned int)t;
    // printf("utc_timeinfo.tm_year: %d\n",utc_timeinfo.tm_year);
    // printf("utc_timeinfo.tm_mon: %d\n",utc_timeinfo.tm_mon);
    // printf("utc_timeinfo.tm_mday: %d\n",utc_timeinfo.tm_mday);
    // printf("utc_timeinfo.tm_hour: %d\n",utc_timeinfo.tm_hour);
    // printf("utc_timeinfo.tm_min: %d\n",utc_timeinfo.tm_min);
    // printf("utc_timeinfo.tm_sec: %d\n",utc_timeinfo.tm_sec);
    // printf("timestamp: %u\n", data.uiTimeStamp);
    /////////////////////////////////////////////////////////

    convert_tBatData_to_big_endian(&data_be, &data);
    insert_data(db, &data_be);
}
