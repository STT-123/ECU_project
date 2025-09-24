/*
 * File: CANSendFcn.c
 *
 * Code generated for Simulink model 'CANSendFcn'.
 *
 * Model version                  : 3.235
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Tue Aug 12 10:34:54 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CANSendFcn.h"
#include "rtwtypes.h"
#include "CANSendFcn_types.h"

/* Exported block signals */
uint8_T OTA_XCPConnect;                /* '<Root>/OTA_XCPConnect' */
uint8_T TCU_ACMuteSet;                 /* '<Root>/TCU_ACMuteSet' */
uint32_T TCU_BCUEINSet;                /* '<Root>/TCU_BCUEINSet' */
uint8_T TCU_ChargerWorkSts;            /* '<Root>/TCU_ChargerWorkSts' */
uint8_T TCU_ECOMode;                   /* '<Root>/TCU_ECOMode' */
uint8_T TCU_FcnStopSet;                /* '<Root>/TCU_FcnStopSet' */
uint8_T TCU_HighVoltType;              /* '<Root>/TCU_HighVoltType' */
uint16_T TCU_HighVoltValue;            /* '<Root>/TCU_HighVoltValue' */
uint8_T TCU_LifeCounter;               /* '<Root>/TCU_LifeCounter' */
uint8_T TCU_PowerUpCmd;                /* '<Root>/TCU_PowerUpCmd' */
uint8_T TCU_TimeCalFlg;                /* '<Root>/TCU_TimeCalFlg' */
uint8_T TCU_TimeDay;                   /* '<Root>/TCU_TimeDay' */
uint8_T TCU_TimeHour;                  /* '<Root>/TCU_TimeHour' */
uint8_T TCU_TimeMinute;                /* '<Root>/TCU_TimeMinute' */
uint8_T TCU_TimeMonth;                 /* '<Root>/TCU_TimeMonth' */
uint8_T TCU_TimeSecond;                /* '<Root>/TCU_TimeSecond' */
uint8_T TCU_TimeWeek;                  /* '<Root>/TCU_TimeWeek' */
uint8_T TCU_TimeYear;                  /* '<Root>/TCU_TimeYear' */
CAN_FD_MESSAGE_BUS CANSendMsg;         /* '<Root>/CANSendMsg' */

/* Block states (default storage) */
DW_CANSendFcn_T CANSendFcn_DW;

/* Real-time model */
static RT_MODEL_CANSendFcn_T CANSendFcn_M_;
RT_MODEL_CANSendFcn_T *const CANSendFcn_M = &CANSendFcn_M_;

/* Model step function */
void bms_CANSendFcn(void)
{
  /* S-Function (scanfdpack): '<Root>/CAN FD Pack' incorporates:
   *  Inport: '<Root>/OTA_XCPConnect'
   *  Inport: '<Root>/TCU_ACMuteSet'
   *  Inport: '<Root>/TCU_BCUEINSet'
   *  Inport: '<Root>/TCU_ChargerWorkSts'
   *  Inport: '<Root>/TCU_ECOMode'
   *  Inport: '<Root>/TCU_FcnStopSet'
   *  Inport: '<Root>/TCU_HighVoltType'
   *  Inport: '<Root>/TCU_HighVoltValue'
   *  Inport: '<Root>/TCU_LifeCounter'
   *  Inport: '<Root>/TCU_PowerUpCmd'
   *  Inport: '<Root>/TCU_TimeCalFlg'
   *  Inport: '<Root>/TCU_TimeDay'
   *  Inport: '<Root>/TCU_TimeHour'
   *  Inport: '<Root>/TCU_TimeMinute'
   *  Inport: '<Root>/TCU_TimeMonth'
   *  Inport: '<Root>/TCU_TimeSecond'
   *  Inport: '<Root>/TCU_TimeWeek'
   *  Inport: '<Root>/TCU_TimeYear'
   *  Outport: '<Root>/CANSendMsg'
   */
  /* S-Function (scanfdpack): '<Root>/CAN FD Pack' */
  CANSendMsg.ID = 402777104;
  CANSendMsg.Length = 64U;
  CANSendMsg.Extended = 1U;
  CANSendMsg.Remote = 0;
  CANSendMsg.BRS = 1;
  CANSendMsg.ProtocolMode = 1;
  CANSendMsg.DLC = 15U;
  CANSendMsg.Data[0] = 0;
  CANSendMsg.Data[1] = 0;
  CANSendMsg.Data[2] = 0;
  CANSendMsg.Data[3] = 0;
  CANSendMsg.Data[4] = 0;
  CANSendMsg.Data[5] = 0;
  CANSendMsg.Data[6] = 0;
  CANSendMsg.Data[7] = 0;
  CANSendMsg.Data[8] = 0;
  CANSendMsg.Data[9] = 0;
  CANSendMsg.Data[10] = 0;
  CANSendMsg.Data[11] = 0;
  CANSendMsg.Data[12] = 0;
  CANSendMsg.Data[13] = 0;
  CANSendMsg.Data[14] = 0;
  CANSendMsg.Data[15] = 0;
  CANSendMsg.Data[16] = 0;
  CANSendMsg.Data[17] = 0;
  CANSendMsg.Data[18] = 0;
  CANSendMsg.Data[19] = 0;
  CANSendMsg.Data[20] = 0;
  CANSendMsg.Data[21] = 0;
  CANSendMsg.Data[22] = 0;
  CANSendMsg.Data[23] = 0;
  CANSendMsg.Data[24] = 0;
  CANSendMsg.Data[25] = 0;
  CANSendMsg.Data[26] = 0;
  CANSendMsg.Data[27] = 0;
  CANSendMsg.Data[28] = 0;
  CANSendMsg.Data[29] = 0;
  CANSendMsg.Data[30] = 0;
  CANSendMsg.Data[31] = 0;
  CANSendMsg.Data[32] = 0;
  CANSendMsg.Data[33] = 0;
  CANSendMsg.Data[34] = 0;
  CANSendMsg.Data[35] = 0;
  CANSendMsg.Data[36] = 0;
  CANSendMsg.Data[37] = 0;
  CANSendMsg.Data[38] = 0;
  CANSendMsg.Data[39] = 0;
  CANSendMsg.Data[40] = 0;
  CANSendMsg.Data[41] = 0;
  CANSendMsg.Data[42] = 0;
  CANSendMsg.Data[43] = 0;
  CANSendMsg.Data[44] = 0;
  CANSendMsg.Data[45] = 0;
  CANSendMsg.Data[46] = 0;
  CANSendMsg.Data[47] = 0;
  CANSendMsg.Data[48] = 0;
  CANSendMsg.Data[49] = 0;
  CANSendMsg.Data[50] = 0;
  CANSendMsg.Data[51] = 0;
  CANSendMsg.Data[52] = 0;
  CANSendMsg.Data[53] = 0;
  CANSendMsg.Data[54] = 0;
  CANSendMsg.Data[55] = 0;
  CANSendMsg.Data[56] = 0;
  CANSendMsg.Data[57] = 0;
  CANSendMsg.Data[58] = 0;
  CANSendMsg.Data[59] = 0;
  CANSendMsg.Data[60] = 0;
  CANSendMsg.Data[61] = 0;
  CANSendMsg.Data[62] = 0;
  CANSendMsg.Data[63] = 0;

  {
    /* --------------- START Packing signal 0 ------------------
     *  startBit                = 40
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (OTA_XCPConnect);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[5] = CANSendMsg.Data[5] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 1 ------------------
     *  startBit                = 16
     *  length                  = 1
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_ACMuteSet);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (uint8_T)(1)) {
          packedValue = (uint8_T) 1;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            CANSendMsg.Data[2] = CANSendMsg.Data[2] | (uint8_T)((uint8_T)
              (packedValue & (uint8_T)0x1U));
          }
        }
      }
    }

    /* --------------- START Packing signal 2 ------------------
     *  startBit                = 72
     *  length                  = 32
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_BCUEINSet);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint32_T packedValue;
        packedValue = (uint32_T) (packingValue);

        {
          {
            CANSendMsg.Data[9] = CANSendMsg.Data[9] | (uint8_T)((uint32_T)
              (packedValue & (uint32_T)0xFFU));
            CANSendMsg.Data[8] = CANSendMsg.Data[8] | (uint8_T)((uint32_T)
              ((uint32_T)(packedValue & (uint32_T)0xFF00U) >> 8));
            CANSendMsg.Data[7] = CANSendMsg.Data[7] | (uint8_T)((uint32_T)
              ((uint32_T)(packedValue & (uint32_T)0xFF0000U) >> 16));
            CANSendMsg.Data[6] = CANSendMsg.Data[6] | (uint8_T)((uint32_T)
              ((uint32_T)(packedValue & (uint32_T)0xFF000000U) >> 24));
          }
        }
      }
    }

    /* --------------- START Packing signal 3 ------------------
     *  startBit                = 24
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_ChargerWorkSts);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[3] = CANSendMsg.Data[3] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 4 ------------------
     *  startBit                = 18
     *  length                  = 1
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_ECOMode);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (uint8_T)(1)) {
          packedValue = (uint8_T) 1;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            CANSendMsg.Data[2] = CANSendMsg.Data[2] | (uint8_T)((uint8_T)
              ((uint8_T)(packedValue & (uint8_T)0x1U) << 2));
          }
        }
      }
    }

    /* --------------- START Packing signal 5 ------------------
     *  startBit                = 32
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_FcnStopSet);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[4] = CANSendMsg.Data[4] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 6 ------------------
     *  startBit                = 19
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_HighVoltType);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (uint8_T)(3)) {
          packedValue = (uint8_T) 3;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            CANSendMsg.Data[2] = CANSendMsg.Data[2] | (uint8_T)((uint8_T)
              ((uint8_T)(packedValue & (uint8_T)0x3U) << 3));
          }
        }
      }
    }

    /* --------------- START Packing signal 7 ------------------
     *  startBit                = 152
     *  length                  = 16
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_HighVoltValue);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint16_T packedValue;
        packedValue = (uint16_T) (packingValue);

        {
          {
            CANSendMsg.Data[19] = CANSendMsg.Data[19] | (uint8_T)((uint16_T)
              (packedValue & (uint16_T)0xFFU));
            CANSendMsg.Data[18] = CANSendMsg.Data[18] | (uint8_T)((uint16_T)
              ((uint16_T)(packedValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    /* --------------- START Packing signal 8 ------------------
     *  startBit                = 0
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    // {
    //   uint32_T packingValue = 0;

    //   {
    //     uint32_T result = (uint32_T) (TCU_LifeCounter);

    //     /* no scaling required */
    //     packingValue = result;
    //   }

    //   {
    //     uint8_T packedValue;
    //     packedValue = (uint8_T) (packingValue);

    //     {
    //       {
    //         CANSendMsg.Data[0] = CANSendMsg.Data[0] | (uint8_T)(packedValue);
    //       }
    //     }
    //   }
    // }

    {
      static uint8_T lifeCounter = 0;  // 静态变量，自动递增
      real_T outValue = 0;

      // 模拟 TCU_LifeCounter 自增
      lifeCounter++;
      if (lifeCounter > 255) {
        lifeCounter = 0;
      }

      TCU_LifeCounter = (real_T)lifeCounter;

      // printf("TCU_LifeCounter = %.0f\n", TCU_LifeCounter);
      outValue = round(TCU_LifeCounter);

      uint8_T packedValue;
      if (outValue > 255.0) {
        packedValue = 255;
      } else if (outValue < 0.0) {
        packedValue = 0;
      } else {
        packedValue = (uint8_T)outValue;
      }
      CANSendMsg.Data[0] = CANSendMsg.Data[0] | (uint8_T)(packedValue);
    }

    /* --------------- START Packing signal 9 ------------------
     *  startBit                = 8
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_PowerUpCmd);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[1] = CANSendMsg.Data[1] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 10 ------------------
     *  startBit                = 136
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeCalFlg);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[17] = CANSendMsg.Data[17] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 11 ------------------
     *  startBit                = 80
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeDay);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[10] = CANSendMsg.Data[10] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 12 ------------------
     *  startBit                = 88
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeHour);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[11] = CANSendMsg.Data[11] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 13 ------------------
     *  startBit                = 96
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeMinute);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[12] = CANSendMsg.Data[12] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 14 ------------------
     *  startBit                = 104
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeMonth);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[13] = CANSendMsg.Data[13] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 15 ------------------
     *  startBit                = 112
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeSecond);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[14] = CANSendMsg.Data[14] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 16 ------------------
     *  startBit                = 120
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeWeek);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[15] = CANSendMsg.Data[15] | (uint8_T)(packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 17 ------------------
     *  startBit                = 128
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (TCU_TimeYear);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        packedValue = (uint8_T) (packingValue);

        {
          {
            CANSendMsg.Data[16] = CANSendMsg.Data[16] | (uint8_T)(packedValue);
          }
        }
      }
    }
  }


  CANSendMsg.Extended =1;
  CANSendMsg.Remote =0;
  CANSendMsg.Error =0;
  CANSendMsg.ESI  =0;
  CANSendMsg.BRS  =0;
  int ret = Drv_can0fd_send(&CANSendMsg);
}

/* Model initialize function */
void CANSendFcn_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void CANSendFcn_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
