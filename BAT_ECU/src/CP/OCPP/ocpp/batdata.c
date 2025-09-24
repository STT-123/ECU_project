#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <zstd.h>
#include <json-c/json.h>
#include <unistd.h>
#include "batdata.h"
#include <arpa/inet.h>

void convert_tBatData_to_big_endian(tBatData *dst, const tBatData *src) {
    dst->uiTimeStamp = htonl(src->uiTimeStamp);

    for (int i = 0; i < 240; ++i)
        dst->usSingleBatVal[i] = htons(src->usSingleBatVal[i]);

    for (int i = 0; i < 120; ++i)
        dst->usSingleBatTemp[i] = htons(src->usSingleBatTemp[i]);

    for (int i = 0; i < 15; ++i) {
        dst->uiBmuErrorNum[i] = htonl(src->uiBmuErrorNum[i]);
        dst->uiBmuExErrorNum[i] = htonl(src->uiBmuExErrorNum[i]);
    }

    dst->iDcPower = htonl(src->iDcPower);

    // 手动拆分 64 位整数（unsigned long long）为大端存储
    dst->ullPosEleQuantity = ((uint64_t)htonl(src->ullPosEleQuantity >> 32)) |
                             ((uint64_t)htonl(src->ullPosEleQuantity & 0xFFFFFFFF) << 32);
    dst->ullNegEleQuantity = ((uint64_t)htonl(src->ullNegEleQuantity >> 32)) |
                             ((uint64_t)htonl(src->ullNegEleQuantity & 0xFFFFFFFF) << 32);

    dst->usAirState = htons(src->usAirState);
    dst->usAirPumpState = htons(src->usAirPumpState);
    dst->usAirCompressorSta = htons(src->usAirCompressorSta);
    dst->uiAirErrorLv1 = htonl(src->uiAirErrorLv1);
    dst->uiAirErrorLv2 = htonl(src->uiAirErrorLv2);
    dst->uiAirErrorLv3 = htonl(src->uiAirErrorLv3);
    dst->usTempInside = htons(src->usTempInside);
    dst->usTempOutside = htons(src->usTempOutside);
    dst->usHumidityInside = htons(src->usHumidityInside);

    dst->usBmuH2MaxConcentration = htons(src->usBmuH2MaxConcentration);
    dst->usBmuH2MinConcentration = htons(src->usBmuH2MinConcentration);
    dst->usBmuCOMaxConcentration = htons(src->usBmuCOMaxConcentration);
    dst->usBmuCOMinConcentration = htons(src->usBmuCOMinConcentration);
    dst->usBmuPressureMax = htons(src->usBmuPressureMax);
    dst->usBmuPressureMin = htons(src->usBmuPressureMin);
    dst->usBmuLightMax = htons(src->usBmuLightMax);
    dst->usBmuLightMin = htons(src->usBmuLightMin);
    dst->usBmuH2MaxIndex = htons(src->usBmuH2MaxIndex);
    dst->usBmuH2MinIndex = htons(src->usBmuH2MinIndex);
    dst->usBmuCOMaxIndex = htons(src->usBmuCOMaxIndex);
    dst->usBmuCOMinIndex = htons(src->usBmuCOMinIndex);
    dst->usBmuPressureMaxIndex = htons(src->usBmuPressureMaxIndex);
    dst->usBmuPressureMinIndex = htons(src->usBmuPressureMinIndex);
    dst->usBmuLightMaxIndex = htons(src->usBmuLightMaxIndex);
    dst->usBmuLightMinIndex = htons(src->usBmuLightMinIndex);

    dst->usAirEnergyMode = htons(src->usAirEnergyMode);
    dst->usAirInletPressure = htons(src->usAirInletPressure);
    dst->usAirCoolSetTemp = htons(src->usAirCoolSetTemp);
    dst->usAirHeatSetTemp = htons(src->usAirHeatSetTemp);
    dst->usAirOutWaterTemp = htons(src->usAirOutWaterTemp);
    dst->usAirReturnWaterTemp = htons(src->usAirReturnWaterTemp);

    dst->usBatMaxVoltCellIndex = htons(src->usBatMaxVoltCellIndex);
    dst->usBatMinVoltCellIndex = htons(src->usBatMinVoltCellIndex);
    dst->usBatMaxTempCellIndex = htons(src->usBatMaxTempCellIndex);
    dst->usBatMinTempCellIndex = htons(src->usBatMinTempCellIndex);
    dst->usBatCellVoltMax = htons(src->usBatCellVoltMax);
    dst->usBatCellVoltMin = htons(src->usBatCellVoltMin);
    dst->usBatMaxTempCellVolt = htons(src->usBatMaxTempCellVolt);
    dst->usBatMinTempCellVolt = htons(src->usBatMinTempCellVolt);
    dst->usBatCellTempMax = htons(src->usBatCellTempMax);
    dst->usBatCellTempMin = htons(src->usBatCellTempMin);
    dst->usBatMaxVoltCellTemp = htons(src->usBatMaxVoltCellTemp);
    dst->usBatMinVoltCellTemp = htons(src->usBatMinVoltCellTemp);
}


tBatData BatData;