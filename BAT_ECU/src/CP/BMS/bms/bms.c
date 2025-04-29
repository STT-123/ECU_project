/*
 * File: bms.c
 *
 * Code generated for Simulink model 'bms'.
 *
 * Model version                  : 1.413
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Feb  8 16:39:57 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include <stdio.h>
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bms.h"
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "bms_private.h"
#include "./GLB/G_GloabalVariable.h"
#include "./DRV/Drv_ECUAndBCUCommunication.h"
#include "./DRV/Drv_ECUAndBMUCommunication.h"
int err;
/* Block signals (default storage) */
B_bms_T bms_B;

/* Block states (default storage) */
DW_bms_T bms_DW;

/* Real-time model */
static RT_MODEL_bms_T bms_M_;
RT_MODEL_bms_T *const bms_M = &bms_M_;

/* Exported data definition */

/* Definition for custom storage class: Default */
uint32_T BCU_FaultInfoLv1H;            /* '<S2>/0x180E10E4' */
uint32_T BCU_FaultInfoLv1L;            /* '<S2>/0x180E10E4' */
uint32_T BCU_FaultInfoLv2H;            /* '<S2>/0x180F10E4' */
uint32_T BCU_FaultInfoLv2L;            /* '<S2>/0x180F10E4' */
uint32_T BCU_FaultInfoLv3H;            /* '<S2>/0x181010E4' */
uint32_T BCU_FaultInfoLv3L;            /* '<S2>/0x181010E4' */
uint32_T BCU_FaultInfoLv4H;            /* '<S2>/0x181110E4' */
uint32_T BCU_FaultInfoLv4L;            /* '<S2>/0x181110E4' */
uint16_T BCU_SOC;                      /* '<S2>/Data Type Conversion35' */
uint16_T BCU_SystemStatus;             /* '<S2>/Constant' */
uint16_T BCU_SystemWorkMode;           /* '<S2>/0x180110E4' */
uint8_T BCU_TimeDay;                   /* '<S2>/0x180110E2' */
uint8_T BCU_TimeHour;                  /* '<S2>/0x180110E2' */
uint8_T BCU_TimeMinute;                /* '<S2>/0x180110E2' */
uint8_T BCU_TimeMonth;                 /* '<S2>/0x180110E2' */
uint8_T BCU_TimeSencond;               /* '<S2>/0x180110E2' */
uint8_T BCU_TimeWeek;                  /* '<S2>/0x180110E2' */
uint8_T BCU_TimeYear;                  /* '<S2>/0x180110E2' */

/* Model step function */
void bms_step(void)
{
  real_T tmp_2;
  real_T tmp_3;
  int32_T i_0;
  int32_T rtb_Gain3;
  real32_T rtb_Gain31;
  real32_T tmp;
  real32_T tmp_0;
  real32_T tmp_1;
  real32_T tmp_4;
  real32_T tmp_5;
  real32_T tmp_6;
  real32_T tmp_7;
  real32_T tmp_8;
  real32_T tmp_9;
  real32_T tmp_a;
  real32_T tmp_b;
  real32_T u;
  real32_T u_0;
  real32_T v;
  uint32_T port_index;
  uint32_T port_len;
  uint32_T q0;
  uint32_T qY;
  uint32_T rtb_Gain15;
  uint16_T rtb_TmpSignalConversionAtSFun_h[582];
  uint16_T rtb_y_k[240];
  uint16_T rtb_y_g3[120];
  uint16_T rtb_y[15];
  uint16_T rtb_y_j[15];
  uint16_T rtb_TmpSignalConversionAtSFun_o[6];
  uint16_T rtb_TmpSignalConversionAtSFunct[5];
  uint16_T rtb_TmpSignalConversionAtSFun_k[3];
  uint16_T CFunction10_o1;
  uint16_T CFunction10_o2;
  uint16_T CFunction12_o1;
  uint16_T CFunction12_o2;
  uint16_T CFunction13;
  uint16_T CFunction3_o1;
  uint16_T CFunction3_o2;
  uint16_T CFunction4_o1;
  uint16_T CFunction4_o2;
  uint16_T CFunction5_o1;
  uint16_T CFunction5_o2;
  uint16_T CFunction6_o1;
  uint16_T CFunction6_o2;
  uint16_T CFunction7_o1;
  uint16_T CFunction7_o2;
  uint16_T CFunction8_o1;
  uint16_T CFunction8_o2;
  uint16_T CFunction9_o1;
  uint16_T CFunction9_o2;
  uint16_T rtb_DataTypeConversion11;
  uint16_T rtb_DataTypeConversion12;
  uint16_T rtb_DataTypeConversion13;
  uint16_T rtb_DataTypeConversion16;
  uint16_T rtb_DataTypeConversion2;
  uint16_T rtb_DataTypeConversion23;
  uint16_T rtb_DataTypeConversion24;
  uint16_T rtb_DataTypeConversion42;
  uint16_T rtb_DataTypeConversion44;
  uint16_T rtb_DataTypeConversion45;
  uint16_T rtb_DataTypeConversion47;
  uint16_T rtb_DataTypeConversion50;
  uint16_T rtb_DataTypeConversion56;
  uint16_T rtb_DataTypeConversion57;
  uint16_T rtb_DataTypeConversion58;
  uint16_T rtb_DataTypeConversion59;
  uint16_T rtb_DataTypeConversion60;
  uint16_T rtb_DataTypeConversion61;
  uint16_T rtb_DataTypeConversion62;
  uint16_T rtb_DataTypeConversion63;
  uint16_T rtb_DataTypeConversion66;
  uint16_T rtb_DataTypeConversion67;
  uint16_T rtb_DataTypeConversion68;
  uint16_T rtb_DataTypeConversion69;
  uint16_T rtb_DataTypeConversion8;
  uint16_T rtb_DataTypeConversion80;
  uint16_T rtb_Saturation1;
  uint16_T rtb_Saturation8;
  uint8_T b;
  uint8_T c;
  uint8_T i;
  uint8_T rtb_Saturation;

  /* CCaller: '<Root>/CANBuff1' incorporates:
   *  Constant: '<Root>/Constant4'
   */
  // CANReceiveMsg(1U, &bms_B.CANBuff1);
  queue_pend(&Queue_Can1RevData, &bms_B.CANBuff2,&err);
  /* S-Function (scanunpack): '<S2>/0x180110E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180110E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180110E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 48
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              BCU_SystemWorkMode = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180110E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180110E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 58
           *  length                  = 2
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[7]) & (uint8_T)(0xCU)) >> 2);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 56
           *  length                  = 2
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[7]) & (uint8_T)(0x3U));
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 60
           *  length                  = 2
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[7]) & (uint8_T)(0x30U)) >> 4);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E4_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 62
           *  length                  = 2
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[7]) & (uint8_T)(0xC0U)) >> 6);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              bms_B.ux180110E4_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180110E4_o8 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/0x1C0110E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x1C0110E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1C0110E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1C0110E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              bms_B.ux1C0110E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              bms_B.ux1C0110E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1C0110E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1C0110E4_o5 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion3' incorporates:
   *  Gain: '<S2>/Gain28'
   */
  tmp_b = fmodf(floorf(10.0F * bms_B.ux180110E4_o2), 65536.0F);

  /* DataTypeConversion: '<S2>/Data Type Conversion4' incorporates:
   *  Gain: '<S2>/Gain29'
   */
  tmp_a = fmodf(floorf(10.0F * bms_B.ux180110E4_o3), 65536.0F);

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  ArithShift: '<S2>/Shift Arithmetic'
   *  ArithShift: '<S2>/Shift Arithmetic1'
   *  Chart: '<Root>/Chart1'
   *  DataTypeConversion: '<S2>/Data Type Conversion5'
   *  DataTypeConversion: '<S2>/Data Type Conversion6'
   *  DataTypeConversion: '<S2>/Data Type Conversion7'
   *  S-Function (sfix_bitop): '<S2>/Bitwise AND'
   */
  rtb_TmpSignalConversionAtSFun_h[4] = (uint16_T)(bms_B.ux180110E4_o4 << 2 |
    bms_B.ux180110E4_o5 | bms_B.ux180110E4_o6 << 4);

  /* S-Function (scanunpack): '<S2>/0x1B0310E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x1B0310E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1B0310E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 56
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1B0310E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1B0310E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 32
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[4]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[3]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1B0310E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 48
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[6]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[5]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1B0310E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux1B0310E4_o5 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/0x180210E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180210E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180210E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 48
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[6]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[3]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180210E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180210E4_o2 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion18' incorporates:
   *  Gain: '<S2>/Gain17'
   */
  tmp_9 = fmodf(floorf(10.0F * bms_B.ux180210E4_o1), 4.2949673E+9F);
  rtb_Gain15 = tmp_9 < 0.0F ? (uint32_T)-(int32_T)(uint32_T)-tmp_9 : (uint32_T)
    tmp_9;

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  CFunction: '<S2>/C Function'
   *  Chart: '<Root>/Chart1'
   */
  rtb_TmpSignalConversionAtSFun_h[9] = (uint16_T)(rtb_Gain15 >> 16);
  rtb_TmpSignalConversionAtSFun_h[10] = (uint16_T)(rtb_Gain15 & 65535U);

  /* DataTypeConversion: '<S2>/Data Type Conversion19' incorporates:
   *  Gain: '<S2>/Gain16'
   */
  tmp_9 = fmodf(floorf(10.0F * bms_B.ux180210E4_o2), 65536.0F);

  /* S-Function (scanunpack): '<S2>/CAN Unpack5' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack5' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180310E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 40
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[3]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[2]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.CANUnpack5_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack5_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.CANUnpack5_o3 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion20' incorporates:
   *  Gain: '<S2>/Gain18'
   */
  tmp_8 = fmodf(floorf(10.0F * bms_B.CANUnpack5_o1), 4.2949673E+9F);
  rtb_Gain15 = tmp_8 < 0.0F ? (uint32_T)-(int32_T)(uint32_T)-tmp_8 : (uint32_T)
    tmp_8;

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  CFunction: '<S2>/C Function1'
   *  Chart: '<Root>/Chart1'
   */
  rtb_TmpSignalConversionAtSFun_h[12] = (uint16_T)(rtb_Gain15 >> 16);
  rtb_TmpSignalConversionAtSFun_h[13] = (uint16_T)(rtb_Gain15 & 65535U);

  /* DataTypeConversion: '<S2>/Data Type Conversion21' incorporates:
   *  Gain: '<S2>/Gain19'
   */
  tmp_8 = fmodf(floorf(10.0F * bms_B.CANUnpack5_o3), 65536.0F);

  /* Product: '<S2>/Product' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  DataTypeConversion: '<S2>/Data Type Conversion1'
   *  Sum: '<S2>/Add'
   */
  rtb_Saturation = (uint8_T)((uint8_T)((uint8_T)bms_B.ux1B0310E4_o5 - 1) * 3U);

  /* Saturate: '<S2>/Saturation' */
  if (rtb_Saturation <= 12) {
  } else {
    rtb_Saturation = 12U;
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* SignalConversion generated from: '<S5>/ SFunction ' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function1'
   */
  rtb_TmpSignalConversionAtSFun_k[0] = bms_B.ux1B0310E4_o2;
  rtb_TmpSignalConversionAtSFun_k[1] = bms_B.ux1B0310E4_o3;
  rtb_TmpSignalConversionAtSFun_k[2] = bms_B.ux1B0310E4_o4;

  /* MATLAB Function: '<S2>/MATLAB Function1' */
  b = (uint8_T)(rtb_Saturation + 1U);
  c = (uint8_T)(rtb_Saturation + 3U);
  for (i = b; i <= c; i++) {
    bms_DW.tmp_a[i - 1] = rtb_TmpSignalConversionAtSFun_k[(i - rtb_Saturation) -
      1];
  }

  for (i_0 = 0; i_0 < 15; i_0++) {
    rtb_y_j[i_0] = bms_DW.tmp_a[i_0];
  }

  /* S-Function (scanunpack): '<S2>/0x180410E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180410E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180410E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180410E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 48
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[6]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[3]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.ux180410E4_o2 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion31' incorporates:
   *  Gain: '<S2>/Gain20'
   */
  tmp_7 = fmodf(floorf(10.0F * bms_B.ux180410E4_o1), 65536.0F);

  /* DataTypeConversion: '<S2>/Data Type Conversion22' incorporates:
   *  Gain: '<S2>/Gain21'
   */
  tmp_6 = fmodf(floorf(10.0F * bms_B.ux180410E4_o2), 4.2949673E+9F);
  rtb_Gain15 = tmp_6 < 0.0F ? (uint32_T)-(int32_T)(uint32_T)-tmp_6 : (uint32_T)
    tmp_6;

  /* S-Function (scanunpack): '<S2>/CAN Unpack10' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack10' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181710E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack10_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack10_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack10_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack10_o4 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/CAN Unpack11' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack11' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181610E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack11_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack11_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack11_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack11_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack11_o5 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/0x180E10E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180E10E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180E10E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv1H = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv1L = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function3' */
  CFunction3_o1 = (uint16_T)(BCU_FaultInfoLv1H >> 16);

  /* CFunction: '<S2>/C Function3' */
  CFunction3_o2 = (uint16_T)(BCU_FaultInfoLv1H & 65535U);

  /* CFunction: '<S2>/C Function4' */
  CFunction4_o1 = (uint16_T)(BCU_FaultInfoLv1L >> 16);

  /* CFunction: '<S2>/C Function4' */
  CFunction4_o2 = (uint16_T)(BCU_FaultInfoLv1L & 65535U);

  /* S-Function (scanunpack): '<S2>/0x180F10E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180F10E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180F10E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv2H = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv2L = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function5' */
  CFunction5_o1 = (uint16_T)(BCU_FaultInfoLv2H >> 16);

  /* CFunction: '<S2>/C Function5' */
  CFunction5_o2 = (uint16_T)(BCU_FaultInfoLv2H & 65535U);

  /* CFunction: '<S2>/C Function6' */
  CFunction6_o1 = (uint16_T)(BCU_FaultInfoLv2L >> 16);

  /* CFunction: '<S2>/C Function6' */
  CFunction6_o2 = (uint16_T)(BCU_FaultInfoLv2L & 65535U);

  /* S-Function (scanunpack): '<S2>/0x181010E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x181010E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181010E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv3H = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv3L = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function7' */
  CFunction7_o1 = (uint16_T)(BCU_FaultInfoLv3H >> 16);

  /* CFunction: '<S2>/C Function7' */
  CFunction7_o2 = (uint16_T)(BCU_FaultInfoLv3H & 65535U);

  /* CFunction: '<S2>/C Function8' */
  CFunction8_o1 = (uint16_T)(BCU_FaultInfoLv3L >> 16);

  /* CFunction: '<S2>/C Function8' */
  CFunction8_o2 = (uint16_T)(BCU_FaultInfoLv3L & 65535U);

  /* S-Function (scanunpack): '<S2>/0x181110E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x181110E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181110E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv4H = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              BCU_FaultInfoLv4L = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function9' */
  CFunction9_o1 = (uint16_T)(BCU_FaultInfoLv4H >> 16);

  /* CFunction: '<S2>/C Function9' */
  CFunction9_o2 = (uint16_T)(BCU_FaultInfoLv4H & 65535U);

  /* CFunction: '<S2>/C Function10' */
  CFunction10_o1 = (uint16_T)(BCU_FaultInfoLv4L >> 16);

  /* CFunction: '<S2>/C Function10' */
  CFunction10_o2 = (uint16_T)(BCU_FaultInfoLv4L & 65535U);

  /* S-Function (scanunpack): '<S2>/0x180710E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180710E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180710E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180710E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180710E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180710E4_o3 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/SOX' */
  {
    /* S-Function (scanunpack): '<S2>/SOX' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180610E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.SOX_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.SOX_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.SOX_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.SOX_o4 = result;
            }
          }
        }
      }
    }
  }

  /* Gain: '<S2>/Gain22' */
  u = 0.00999999F * (real32_T)bms_B.SOX_o2;

  /* DataTypeConversion: '<S2>/Data Type Conversion35' */
  if (u >= 0.5F) {
    i_0 = (int32_T)floorf(u + 0.5F);
  } else {
    i_0 = 0;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion35' */
  BCU_SOC = (uint16_T)fmodf((real32_T)i_0, 65536.0F);

  /* Gain: '<S2>/Gain23' */
  u = 0.00999999F * (real32_T)bms_B.SOX_o4;

  /* S-Function (scanunpack): '<S2>/CAN Unpack19' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack19' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1CA010E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack19_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack19_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff1.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.CANUnpack19_o3 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/0x181310E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x181310E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181310E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181310E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux181310E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181310E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181310E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux181310E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181310E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion66' incorporates:
   *  Constant: '<S2>/Constant14'
   *  Gain: '<S2>/Gain24'
   *  Sum: '<S2>/Add7'
   *  Sum: '<S2>/Subtract4'
   */
  rtb_DataTypeConversion66 = (uint16_T)((((uint32_T)(uint16_T)
    (bms_B.ux181310E4_o1 - 1) << 15) + ((uint32_T)bms_B.ux181310E4_o3 << 11)) >>
    11);

  /* DataTypeConversion: '<S2>/Data Type Conversion2' */
  rtb_DataTypeConversion2 = (uint16_T)bms_B.ux181310E4_o2;

  /* DataTypeConversion: '<S2>/Data Type Conversion57' */
  rtb_DataTypeConversion57 = (uint16_T)bms_B.ux181310E4_o5;

  /* S-Function (scanunpack): '<S2>/0x180B10E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180B10E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180B10E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180B10E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180B10E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux180B10E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180B10E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180B10E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux180B10E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S2>/Saturation3' */
  if (bms_B.ux180B10E4_o1 > 16) {
    b = 16U;
  } else if (bms_B.ux180B10E4_o1 < 1) {
    b = 1U;
  } else {
    b = bms_B.ux180B10E4_o1;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion44' incorporates:
   *  Constant: '<S2>/Constant7'
   *  Gain: '<S2>/Gain11'
   *  Saturate: '<S2>/Saturation3'
   *  Sum: '<S2>/Add2'
   *  Sum: '<S2>/Subtract'
   */
  rtb_DataTypeConversion44 = (uint16_T)(((uint32_T)((b - 1) << 7) + ((uint32_T)
    bms_B.ux180B10E4_o2 << 3)) >> 3);

  /* DataTypeConversion: '<S2>/Data Type Conversion58' */
  rtb_DataTypeConversion58 = (uint16_T)bms_B.ux180B10E4_o3;

  /* Saturate: '<S2>/Saturation4' */
  if (bms_B.ux180B10E4_o4 > 16) {
    b = 16U;
  } else if (bms_B.ux180B10E4_o4 < 1) {
    b = 1U;
  } else {
    b = bms_B.ux180B10E4_o4;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion45' incorporates:
   *  Constant: '<S2>/Constant8'
   *  Gain: '<S2>/Gain12'
   *  Saturate: '<S2>/Saturation4'
   *  Sum: '<S2>/Add3'
   *  Sum: '<S2>/Subtract1'
   */
  rtb_DataTypeConversion45 = (uint16_T)(((uint32_T)((b - 1) << 7) + ((uint32_T)
    bms_B.ux180B10E4_o5 << 3)) >> 3);

  /* DataTypeConversion: '<S2>/Data Type Conversion59' */
  rtb_DataTypeConversion59 = (uint16_T)bms_B.ux180B10E4_o6;

  /* S-Function (scanunpack): '<S2>/0x180C10E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180C10E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180C10E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180C10E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180C10E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180C10E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux180C10E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180C10E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux180C10E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion60' */
  rtb_DataTypeConversion60 = (uint16_T)bms_B.ux180C10E4_o4;

  /* DataTypeConversion: '<S2>/Data Type Conversion61' */
  rtb_DataTypeConversion61 = (uint16_T)bms_B.ux180C10E4_o6;

  /* S-Function (scanunpack): '<S2>/0x181410E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x181410E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181410E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181410E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181410E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux181410E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181410E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181410E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux181410E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S2>/Saturation5' */
  if (bms_B.ux181410E4_o1 > 16) {
    b = 16U;
  } else if (bms_B.ux181410E4_o1 < 1) {
    b = 1U;
  } else {
    b = bms_B.ux181410E4_o1;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion67' incorporates:
   *  Constant: '<S2>/Constant15'
   *  Gain: '<S2>/Gain25'
   *  Saturate: '<S2>/Saturation5'
   *  Sum: '<S2>/Add8'
   *  Sum: '<S2>/Subtract5'
   */
  rtb_DataTypeConversion67 = (uint16_T)(((uint32_T)((b - 1) << 7) + ((uint32_T)
    bms_B.ux181410E4_o2 << 3)) >> 3);

  /* DataTypeConversion: '<S2>/Data Type Conversion62' */
  rtb_DataTypeConversion62 = (uint16_T)bms_B.ux181410E4_o3;

  /* Saturate: '<S2>/Saturation6' */
  if (bms_B.ux181410E4_o4 > 16) {
    b = 16U;
  } else if (bms_B.ux181410E4_o4 < 1) {
    b = 1U;
  } else {
    b = bms_B.ux181410E4_o4;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion68' incorporates:
   *  Constant: '<S2>/Constant16'
   *  Gain: '<S2>/Gain26'
   *  Saturate: '<S2>/Saturation6'
   *  Sum: '<S2>/Add9'
   *  Sum: '<S2>/Subtract6'
   */
  rtb_DataTypeConversion68 = (uint16_T)(((uint32_T)((b - 1) << 7) + ((uint32_T)
    bms_B.ux181410E4_o5 << 3)) >> 3);

  /* DataTypeConversion: '<S2>/Data Type Conversion63' */
  rtb_DataTypeConversion63 = (uint16_T)bms_B.ux181410E4_o6;

  /* S-Function (scanunpack): '<S2>/CAN Unpack27' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack27' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180510E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = -3200.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = (result * 0.1F) + -3200.0F;
              bms_B.CANUnpack27_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.CANUnpack27_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.CANUnpack27_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              bms_B.CANUnpack27_o4 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion46' incorporates:
   *  Gain: '<S2>/Gain14'
   */
  tmp_6 = fmodf(floorf(10.0F * bms_B.CANUnpack27_o1), 65536.0F);

  /* Gain: '<S2>/Gain6' */
  u_0 = 10.0F * bms_B.CANUnpack27_o2;

  /* DataTypeConversion: '<S2>/Data Type Conversion37' */
  v = fabsf(u_0);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u_0 = floorf(u_0 + 0.5F);
    } else {
      u_0 = 0.0F;
    }
  }

  tmp_5 = fmodf(u_0, 65536.0F);

  /* Gain: '<S2>/Gain7' */
  u_0 = 10.0F * bms_B.CANUnpack27_o3;

  /* DataTypeConversion: '<S2>/Data Type Conversion39' */
  v = fabsf(u_0);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u_0 = floorf(u_0 + 0.5F);
    } else {
      u_0 = 0.0F;
    }
  }

  tmp_4 = fmodf(u_0, 65536.0F);

  /* Gain: '<S2>/Gain8' */
  u_0 = 10.0F * bms_B.CANUnpack27_o4;

  /* DataTypeConversion: '<S2>/Data Type Conversion40' */
  v = fabsf(u_0);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u_0 = floorf(u_0 + 0.5F);
    } else {
      u_0 = 0.0F;
    }
  }

  v = fmodf(u_0, 65536.0F);

  /* S-Function (scanunpack): '<S2>/0x181210E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x181210E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181210E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181210E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181210E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181210E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181210E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux181210E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux181210E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S2>/Saturation7' */
  if (bms_B.ux181210E4_o1 > 16) {
    b = 16U;
  } else if (bms_B.ux181210E4_o1 < 1) {
    b = 1U;
  } else {
    b = bms_B.ux181210E4_o1;
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion69' incorporates:
   *  Constant: '<S2>/Constant17'
   *  Gain: '<S2>/Gain27'
   *  Saturate: '<S2>/Saturation7'
   *  Sum: '<S2>/Add10'
   *  Sum: '<S2>/Subtract7'
   */
  rtb_DataTypeConversion69 = (uint16_T)(((uint32_T)((b - 1) << 7) + ((uint32_T)
    bms_B.ux181210E4_o6 << 3)) >> 3);

  /* S-Function (scanunpack): '<S2>/0x180810E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180810E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180810E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180810E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180810E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180810E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180810E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 56
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180810E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180810E4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion42' incorporates:
   *  Constant: '<S2>/Constant13'
   *  Gain: '<S2>/Gain9'
   *  Sum: '<S2>/Add6'
   *  Sum: '<S2>/Subtract3'
   */
  rtb_DataTypeConversion42 = (uint16_T)(((uint32_T)((uint8_T)
    (bms_B.ux180810E4_o4 - 1) << 7) + ((uint32_T)bms_B.ux180810E4_o6 << 3)) >> 3);

  /* S-Function (scanunpack): '<S2>/0x180A10E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x180A10E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x180A10E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180A10E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180A10E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180A10E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 48
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[6]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[5]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180A10E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180A10E4_o5 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/CAN Unpack32' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack32' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181510E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack32_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack32_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack32_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 40
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack32_o4 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S2>/0x1B0110E4' */
  {
    /* S-Function (scanunpack): '<S2>/0x1B0110E4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1B0110E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 48
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.ux1B0110E4_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux1B0110E4_o7 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S2>/Saturation1' incorporates:
   *  Constant: '<S2>/Constant5'
   *  Constant: '<S2>/Constant6'
   *  Product: '<S2>/Product1'
   *  Sum: '<S2>/Add1'
   */
  i_0 = (uint8_T)((uint8_T)(bms_B.ux1B0110E4_o7 - 1) * 6U);
  if ((uint32_T)i_0 <= 114U) {
    rtb_Saturation1 = (uint16_T)i_0;
  } else {
    i_0 = 114;
    rtb_Saturation1 = 114U;
  }

  /* SignalConversion generated from: '<S4>/ SFunction ' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion15'
   *  DataTypeConversion: '<S2>/Data Type Conversion51'
   *  DataTypeConversion: '<S2>/Data Type Conversion52'
   *  DataTypeConversion: '<S2>/Data Type Conversion53'
   *  DataTypeConversion: '<S2>/Data Type Conversion54'
   *  DataTypeConversion: '<S2>/Data Type Conversion55'
   *  MATLAB Function: '<S2>/MATLAB Function'
   */
  rtb_TmpSignalConversionAtSFun_o[0] = (uint16_T)bms_B.ux1B0110E4_o1;
  rtb_TmpSignalConversionAtSFun_o[1] = (uint16_T)bms_B.ux1B0110E4_o2;
  rtb_TmpSignalConversionAtSFun_o[2] = (uint16_T)bms_B.ux1B0110E4_o3;
  rtb_TmpSignalConversionAtSFun_o[3] = (uint16_T)bms_B.ux1B0110E4_o4;
  rtb_TmpSignalConversionAtSFun_o[4] = (uint16_T)bms_B.ux1B0110E4_o5;
  rtb_TmpSignalConversionAtSFun_o[5] = (uint16_T)bms_B.ux1B0110E4_o6;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Saturate: '<S2>/Saturation1'
   */
  CFunction13 = (uint16_T)(rtb_Saturation1 + 1U);
  rtb_Saturation8 = (uint16_T)(rtb_Saturation1 + 6U);
  for (rtb_DataTypeConversion80 = CFunction13; rtb_DataTypeConversion80 <=
       rtb_Saturation8; rtb_DataTypeConversion80++) {
    bms_DW.tmp_ay[rtb_DataTypeConversion80 - 1] =
      rtb_TmpSignalConversionAtSFun_o[(rtb_DataTypeConversion80 - i_0) - 1];
  }

  memcpy(&rtb_y_g3[0], &bms_DW.tmp_ay[0], 120U * sizeof(uint16_T));

  /* S-Function (scanunpack): '<S2>/CAN Unpack29' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack29' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1A0110E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 16
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack29_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 32
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[4]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[3]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack29_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 48
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[6]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[5]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack29_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack29_o4 = result;
            }
          }
        }
      }
    }
  }

  /* Product: '<S2>/Product2' incorporates:
   *  Constant: '<S2>/Constant10'
   *  Constant: '<S2>/Constant11'
   *  Sum: '<S2>/Add4'
   */
  rtb_Saturation = (uint8_T)((uint8_T)(bms_B.CANUnpack29_o4 - 1) * 3U);

  /* Saturate: '<S2>/Saturation2' */
  if (rtb_Saturation <= 237) {
  } else {
    rtb_Saturation = 237U;
  }

  /* End of Saturate: '<S2>/Saturation2' */

  /* SignalConversion generated from: '<S6>/ SFunction ' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion43'
   *  DataTypeConversion: '<S2>/Data Type Conversion48'
   *  DataTypeConversion: '<S2>/Data Type Conversion49'
   *  Gain: '<S2>/Gain10'
   *  Gain: '<S2>/Gain13'
   *  Gain: '<S2>/Gain15'
   *  MATLAB Function: '<S2>/MATLAB Function2'
   */
  rtb_TmpSignalConversionAtSFun_k[0] = (uint16_T)((52429U * bms_B.CANUnpack29_o1)
    >> 19);
  rtb_TmpSignalConversionAtSFun_k[1] = (uint16_T)((52429U * bms_B.CANUnpack29_o2)
    >> 19);
  rtb_TmpSignalConversionAtSFun_k[2] = (uint16_T)((52429U * bms_B.CANUnpack29_o3)
    >> 19);

  /* MATLAB Function: '<S2>/MATLAB Function2' */
  b = (uint8_T)(rtb_Saturation + 1U);
  c = (uint8_T)(rtb_Saturation + 3U);
  for (i = b; i <= c; i++) {
    bms_DW.tmp_n[i - 1] = rtb_TmpSignalConversionAtSFun_k[(i - rtb_Saturation) -
      1];
  }

  memcpy(&rtb_y_k[0], &bms_DW.tmp_n[0], 240U * sizeof(uint16_T));

  /* Sum: '<S2>/Add5' incorporates:
   *  Constant: '<S2>/Constant12'
   *  Gain: '<S2>/Gain5'
   *  Sum: '<S2>/Subtract2'
   */
  rtb_Saturation1 = (uint16_T)((uint32_T)((uint8_T)(bms_B.ux180810E4_o1 - 1) <<
    7) + ((uint32_T)bms_B.ux180810E4_o3 << 3));

  /* S-Function (scanunpack): '<S2>/CAN Unpack1' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack1' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1B0410E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack1_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack1_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 48
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              bms_B.CANUnpack1_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack1_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack1_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack1_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack1_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack1_o8 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion8' */
  rtb_DataTypeConversion8 = (uint16_T)bms_B.CANUnpack1_o1;

  /* DataTypeConversion: '<S2>/Data Type Conversion11' */
  rtb_DataTypeConversion11 = (uint16_T)bms_B.CANUnpack1_o4;

  /* DataTypeConversion: '<S2>/Data Type Conversion16' */
  rtb_DataTypeConversion16 = (uint16_T)bms_B.CANUnpack1_o3;

  /* DataTypeConversion: '<S2>/Data Type Conversion12' incorporates:
   *  Gain: '<S2>/Gain'
   */
  rtb_DataTypeConversion12 = (uint16_T)((20480 * bms_B.CANUnpack1_o6) >> 11);

  /* DataTypeConversion: '<S2>/Data Type Conversion13' incorporates:
   *  Gain: '<S2>/Gain2'
   */
  rtb_DataTypeConversion13 = (uint16_T)((20480 * bms_B.CANUnpack1_o7) >> 11);

  /* Gain: '<S2>/Gain3' */
  rtb_Gain3 = 20480 * bms_B.CANUnpack1_o8;

  /* Gain: '<S2>/Gain1' */
  u_0 = 0.00999999F * (real32_T)bms_B.SOX_o1;

  /* S-Function (scanunpack): '<S2>/CAN Unpack2' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack2' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1B0510E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 41
           *  length                  = 1
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[5]) & (uint8_T)(0x2U)) >> 1);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              bms_B.CANUnpack2_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (real_T) (unpackedValue);
            }

            {
              real_T result = (real_T) outValue;
              result = result * 0.1;
              bms_B.CANUnpack2_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(bms_B.CANBuff1.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (bms_B.CANBuff1.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack2_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (real_T) (unpackedValue);
            }

            {
              real_T result = (real_T) outValue;
              result = result * 0.1;
              bms_B.CANUnpack2_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 40
           *  length                  = 1
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[5]) & (uint8_T)(0x1U));
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              bms_B.CANUnpack2_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 43
           *  length                  = 1
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[5]) & (uint8_T)(0x8U)) >> 3);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack2_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 42
           *  length                  = 1
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[5]) & (uint8_T)(0x4U)) >> 2);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack2_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 44
           *  length                  = 1
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[5]) & (uint8_T)(0x10U)) >> 4);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack2_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.CANUnpack2_o9 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion23' */
  rtb_DataTypeConversion23 = (uint16_T)bms_B.CANUnpack2_o1;

  /* DataTypeConversion: '<S2>/Data Type Conversion24' */
  rtb_DataTypeConversion24 = (uint16_T)bms_B.CANUnpack2_o5;

  /* Gain: '<S2>/Gain33' */
  tmp_3 = fmod(floor(10.0 * bms_B.CANUnpack2_o2), 65536.0);

  /* Gain: '<S2>/Gain32' */
  tmp_2 = fmod(floor(10.0 * bms_B.CANUnpack2_o4), 65536.0);

  /* CFunction: '<S2>/C Function11' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion32'
   */
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -2) |
    bms_ConstB.DataTypeConversion27);
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -3) |
    bms_ConstB.DataTypeConversion28 << 1);
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -5) |
    bms_ConstB.DataTypeConversion29 << 2);
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -9) |
    bms_ConstB.DataTypeConversion30 << 3);
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -17) |
    (bms_B.CANUnpack2_o6 != 0) << 4);
  bms_B.CFunction11 = (uint16_T)((bms_B.CFunction11 & -33) |
    bms_ConstB.DataTypeConversion38 << 5);

  /* S-Function (scanunpack): '<S2>/CAN Unpack3' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack3' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x181810E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack3_o6 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion47' */
  rtb_DataTypeConversion47 = (uint16_T)bms_B.CANUnpack3_o3;

  /* DataTypeConversion: '<S2>/Data Type Conversion50' */
  rtb_DataTypeConversion50 = (uint16_T)bms_B.CANUnpack3_o4;

  /* DataTypeConversion: '<S2>/Data Type Conversion56' */
  rtb_DataTypeConversion56 = (uint16_T)bms_B.CANUnpack3_o6;

  /* DataTypeConversion: '<S2>/Data Type Conversion64' incorporates:
   *  Gain: '<S2>/Gain4'
   */
  tmp_1 = fmodf(floorf(10.0F * bms_B.ux180110E4_o8), 65536.0F);

  /* DataTypeConversion: '<S2>/Data Type Conversion65' incorporates:
   *  Gain: '<S2>/Gain30'
   */
  tmp_0 = fmodf(floorf(10.0F * bms_B.ux1C0110E4_o2), 65536.0F);

  /* CFunction: '<S2>/C Function12' */
  CFunction12_o1 = (uint16_T)(bms_B.CANUnpack19_o3 >> 16);

  /* CFunction: '<S2>/C Function12' */
  CFunction12_o2 = (uint16_T)(bms_B.CANUnpack19_o3 & 65535U);

  /* DataTypeConversion: '<S2>/Data Type Conversion71' */
  tmp = fmodf(floorf(bms_B.ux180110E4_o7), 65536.0F);

  /* Gain: '<S2>/Gain31' */
  rtb_Gain31 = 10.0F * bms_B.ux1C0110E4_o3;

  /* S-Function (scanunpack): '<S2>/CAN Unpack4' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack4' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x1B0210E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack4_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack4_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack4_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -40.0
           * -----------------------------------------------------------------------*/
          {
            int16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              bms_B.CANUnpack4_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack4_o6 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S2>/Saturation8' incorporates:
   *  Constant: '<S2>/Constant22'
   *  Constant: '<S2>/Constant23'
   *  Product: '<S2>/Product3'
   *  Sum: '<S2>/Add11'
   */
  i_0 = (uint8_T)((uint8_T)(bms_B.CANUnpack4_o6 - 1) * 5U);
  if ((uint32_T)i_0 <= 10U) {
    rtb_Saturation8 = (uint16_T)i_0;
  } else {
    i_0 = 10;
    rtb_Saturation8 = 10U;
  }

  /* SignalConversion generated from: '<S7>/ SFunction ' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion74'
   *  DataTypeConversion: '<S2>/Data Type Conversion75'
   *  DataTypeConversion: '<S2>/Data Type Conversion76'
   *  DataTypeConversion: '<S2>/Data Type Conversion77'
   *  DataTypeConversion: '<S2>/Data Type Conversion78'
   *  MATLAB Function: '<S2>/MATLAB Function3'
   */
  rtb_TmpSignalConversionAtSFunct[0] = (uint16_T)bms_B.CANUnpack4_o1;
  rtb_TmpSignalConversionAtSFunct[1] = (uint16_T)bms_B.CANUnpack4_o2;
  rtb_TmpSignalConversionAtSFunct[2] = (uint16_T)bms_B.CANUnpack4_o3;
  rtb_TmpSignalConversionAtSFunct[3] = (uint16_T)bms_B.CANUnpack4_o4;
  rtb_TmpSignalConversionAtSFunct[4] = (uint16_T)bms_B.CANUnpack4_o5;

  /* MATLAB Function: '<S2>/MATLAB Function3' incorporates:
   *  Saturate: '<S2>/Saturation8'
   */
  CFunction13 = (uint16_T)(rtb_Saturation8 + 1U);
  rtb_Saturation8 = (uint16_T)(rtb_Saturation8 + 5U);
  for (rtb_DataTypeConversion80 = CFunction13; rtb_DataTypeConversion80 <=
       rtb_Saturation8; rtb_DataTypeConversion80++) {
    bms_DW.tmp[rtb_DataTypeConversion80 - 1] = rtb_TmpSignalConversionAtSFunct
      [(rtb_DataTypeConversion80 - i_0) - 1];
  }

  for (i_0 = 0; i_0 < 15; i_0++) {
    rtb_y[i_0] = bms_DW.tmp[i_0];
  }

  /* S-Function (scanunpack): '<S2>/CAN Unpack6' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack6' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x18FAE6E2 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack6_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack6_o2 = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function13' */
  CFunction13 = (uint16_T)(bms_B.CANUnpack6_o1 << 8 | bms_B.CANUnpack6_o2);
  /* S-Function (scanunpack): '<S2>/CAN Unpack7' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack7' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x18FA78F5 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack7_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack7_o2 = result;
            }
          }
        }
      }
    }
  }

  /* CFunction: '<S2>/C Function15' */
  rtb_Saturation8 = (uint16_T)(bms_B.CANUnpack7_o1 << 8 | bms_B.CANUnpack7_o2);
  /* S-Function (scanunpack): '<S2>/CAN Unpack8' */
  {
    /* S-Function (scanunpack): '<S2>/CAN Unpack8' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x18FFC13D == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 5
           *  desiredSignalByteLayout = LITTLEENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            int8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)
                    (bms_B.CANBuff1.Data[0]) & (uint8_T)(0x1FU));
                }

                unpackedValue = tempValue;
              }

              outValue = (int8_T) (unpackedValue);
            }

            {
              int8_T result = (int8_T) outValue;
              bms_B.CANUnpack8_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.CANUnpack8_o2 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S2>/Data Type Conversion80' */
  rtb_DataTypeConversion80 = bms_B.CANUnpack8_o2;

  /* CCaller: '<Root>/CANBuff2' incorporates:
   *  Constant: '<Root>/Constant3'
   */
  // CANReceiveMsg(2U, &bms_B.CANBuff2);
 
  queue_pend(&Queue_Can2RevData, &bms_B.CANBuff2,&err);
  /* S-Function (scanunpack): '<S3>/0x180110E4' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E4' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D1 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E4_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E4_o2_a = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E2' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E2' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D2 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E2_o1_o = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E2_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E1' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E1' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D3 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E1_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E1_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E5' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E5' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D4 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E5_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E5_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E3' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E3' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D5 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E3_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E3_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E7' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E7' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D6 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E7_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E7_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E6' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E6' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D7 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E6_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E6_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E9' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E9' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D8 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E9_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E9_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E8' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E8' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510D9 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E8_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E8_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E11' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E11' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DA == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E11_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E11_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E10' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E10' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DB == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E10_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E10_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E13' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E13' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DC == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E13_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E13_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E12' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E12' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DD == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E12_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E12_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E15' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E15' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DE == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E15_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E15_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E14' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E14' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180510DF == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E14_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff2.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              bms_B.ux180110E14_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E16' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E16' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D1 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E16_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E16_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E17' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E17' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D2 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E17_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E17_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E18' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E18' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D3 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E18_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E18_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E19' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E19' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D4 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E19_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E19_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E20' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E20' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D5 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E20_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E20_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E21' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E21' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D6 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E21_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E21_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E22' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E22' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D7 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E22_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E22_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E23' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E23' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D8 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E23_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E23_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E24' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E24' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410D9 == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E24_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E24_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E25' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E25' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DA == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E25_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E25_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E26' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E26' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DB == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E26_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E26_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E27' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E27' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DC == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E27_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E27_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E28' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E28' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DD == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E28_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E28_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E29' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E29' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DE == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E29_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E29_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E30' */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E30' */
    if ((8 == bms_B.CANBuff2.Length) && (bms_B.CANBuff2.ID != INVALID_CAN_ID) )
    {
      if ((0x180410DF == bms_B.CANBuff2.ID) && (1U == bms_B.CANBuff2.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 24
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[2]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[1]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[0]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E30_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 56
           *  length                  = 32
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(bms_B.CANBuff2.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[6]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[5]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (bms_B.CANBuff2.Data[4]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              bms_B.ux180110E30_o2 = result;
            }
          }
        }
      }
    }
  }

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  CFunction: '<S2>/C Function2'
   *  Chart: '<Root>/Chart1'
   *  DataTypeConversion: '<S2>/Data Type Conversion19'
   *  DataTypeConversion: '<S2>/Data Type Conversion21'
   *  DataTypeConversion: '<S2>/Data Type Conversion3'
   *  DataTypeConversion: '<S2>/Data Type Conversion31'
   *  DataTypeConversion: '<S2>/Data Type Conversion4'
   */
  rtb_TmpSignalConversionAtSFun_h[0] = BCU_SystemWorkMode;
  rtb_TmpSignalConversionAtSFun_h[1] = bms_B.ux1C0110E4_o1;
  rtb_TmpSignalConversionAtSFun_h[2] = (uint16_T)(tmp_b < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_b : (int32_T)(uint16_T)tmp_b);
  rtb_TmpSignalConversionAtSFun_h[3] = (uint16_T)(tmp_a < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_a : (int32_T)(uint16_T)tmp_a);
  rtb_TmpSignalConversionAtSFun_h[5] = BCU_SystemStatus;
  rtb_TmpSignalConversionAtSFun_h[6] = bms_B.ux1C0110E4_o4;
  rtb_TmpSignalConversionAtSFun_h[7] = bms_B.ux1C0110E4_o5;
  rtb_TmpSignalConversionAtSFun_h[8] = bms_B.ux1B0310E4_o1;
  rtb_TmpSignalConversionAtSFun_h[11] = (uint16_T)(tmp_9 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_9 : (int32_T)(uint16_T)tmp_9);
  rtb_TmpSignalConversionAtSFun_h[14] = (uint16_T)(tmp_8 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_8 : (int32_T)(uint16_T)tmp_8);
  for (i_0 = 0; i_0 < 15; i_0++) {
    rtb_TmpSignalConversionAtSFun_h[i_0 + 15] = rtb_y_j[i_0];
  }

  rtb_TmpSignalConversionAtSFun_h[30] = (uint16_T)(tmp_7 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_7 : (int32_T)(uint16_T)tmp_7);
  rtb_TmpSignalConversionAtSFun_h[31] = (uint16_T)(rtb_Gain15 & 65535U);
  rtb_TmpSignalConversionAtSFun_h[32] = (uint16_T)(rtb_Gain15 >> 16);
  rtb_TmpSignalConversionAtSFun_h[33] = bms_B.CANUnpack10_o1;
  rtb_TmpSignalConversionAtSFun_h[34] = bms_B.CANUnpack10_o2;
  rtb_TmpSignalConversionAtSFun_h[35] = bms_B.CANUnpack10_o3;
  rtb_TmpSignalConversionAtSFun_h[36] = bms_B.CANUnpack10_o4;
  rtb_TmpSignalConversionAtSFun_h[37] = bms_B.CANUnpack11_o1;
  rtb_TmpSignalConversionAtSFun_h[38] = bms_B.CANUnpack11_o2;
  rtb_TmpSignalConversionAtSFun_h[39] = bms_B.CANUnpack11_o4;
  rtb_TmpSignalConversionAtSFun_h[40] = bms_B.CANUnpack11_o5;
  rtb_TmpSignalConversionAtSFun_h[41] = CFunction3_o1;
  rtb_TmpSignalConversionAtSFun_h[42] = CFunction3_o2;
  rtb_TmpSignalConversionAtSFun_h[43] = CFunction4_o1;
  rtb_TmpSignalConversionAtSFun_h[44] = CFunction4_o2;
  rtb_TmpSignalConversionAtSFun_h[45] = CFunction5_o1;
  rtb_TmpSignalConversionAtSFun_h[46] = CFunction5_o2;
  rtb_TmpSignalConversionAtSFun_h[47] = CFunction6_o1;
  rtb_TmpSignalConversionAtSFun_h[48] = CFunction6_o2;
  rtb_TmpSignalConversionAtSFun_h[49] = CFunction7_o1;
  rtb_TmpSignalConversionAtSFun_h[50] = CFunction7_o2;
  rtb_TmpSignalConversionAtSFun_h[51] = CFunction8_o1;
  rtb_TmpSignalConversionAtSFun_h[52] = CFunction8_o2;
  rtb_TmpSignalConversionAtSFun_h[53] = CFunction9_o1;
  rtb_TmpSignalConversionAtSFun_h[54] = CFunction9_o2;
  rtb_TmpSignalConversionAtSFun_h[55] = CFunction10_o1;
  rtb_TmpSignalConversionAtSFun_h[56] = bms_B.ux180710E4_o1;
  rtb_TmpSignalConversionAtSFun_h[57] = bms_B.ux180710E4_o2;
  rtb_TmpSignalConversionAtSFun_h[58] = bms_B.ux180710E4_o3;
  rtb_TmpSignalConversionAtSFun_h[59] = BCU_SOC;

  /* DataTypeConversion: '<S2>/Data Type Conversion36' */
  if (u >= 0.5F) {
    i_0 = (int32_T)floorf(u + 0.5F);
  } else {
    i_0 = 0;
  }

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  Chart: '<Root>/Chart1'
   *  DataTypeConversion: '<S2>/Data Type Conversion14'
   *  DataTypeConversion: '<S2>/Data Type Conversion36'
   *  DataTypeConversion: '<S2>/Data Type Conversion37'
   *  DataTypeConversion: '<S2>/Data Type Conversion39'
   *  DataTypeConversion: '<S2>/Data Type Conversion40'
   *  DataTypeConversion: '<S2>/Data Type Conversion41'
   *  DataTypeConversion: '<S2>/Data Type Conversion46'
   *  Gain: '<S2>/Gain3'
   *  Sum: '<S2>/Add5'
   */
  rtb_TmpSignalConversionAtSFun_h[60] = (uint16_T)fmodf((real32_T)i_0, 65536.0F);
  rtb_TmpSignalConversionAtSFun_h[61] = bms_B.CANUnpack19_o1;
  rtb_TmpSignalConversionAtSFun_h[62] = bms_B.CANUnpack19_o2;
  rtb_TmpSignalConversionAtSFun_h[63] = rtb_DataTypeConversion66;
  rtb_TmpSignalConversionAtSFun_h[64] = rtb_DataTypeConversion2;
  rtb_TmpSignalConversionAtSFun_h[65] = bms_B.ux181310E4_o4;
  rtb_TmpSignalConversionAtSFun_h[66] = rtb_DataTypeConversion57;
  rtb_TmpSignalConversionAtSFun_h[67] = bms_B.ux181310E4_o6;
  rtb_TmpSignalConversionAtSFun_h[68] = rtb_DataTypeConversion44;
  rtb_TmpSignalConversionAtSFun_h[69] = rtb_DataTypeConversion58;
  rtb_TmpSignalConversionAtSFun_h[70] = rtb_DataTypeConversion45;
  rtb_TmpSignalConversionAtSFun_h[71] = rtb_DataTypeConversion59;
  rtb_TmpSignalConversionAtSFun_h[72] = bms_B.ux180C10E4_o1;
  rtb_TmpSignalConversionAtSFun_h[73] = bms_B.ux180C10E4_o2;
  rtb_TmpSignalConversionAtSFun_h[74] = bms_B.ux180C10E4_o3;
  rtb_TmpSignalConversionAtSFun_h[75] = rtb_DataTypeConversion60;
  rtb_TmpSignalConversionAtSFun_h[76] = bms_B.ux180C10E4_o5;
  rtb_TmpSignalConversionAtSFun_h[77] = rtb_DataTypeConversion61;
  rtb_TmpSignalConversionAtSFun_h[78] = rtb_DataTypeConversion67;
  rtb_TmpSignalConversionAtSFun_h[79] = rtb_DataTypeConversion62;
  rtb_TmpSignalConversionAtSFun_h[80] = rtb_DataTypeConversion68;
  rtb_TmpSignalConversionAtSFun_h[81] = rtb_DataTypeConversion63;
  rtb_TmpSignalConversionAtSFun_h[82] = (uint16_T)(tmp_6 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_6 : (int32_T)(uint16_T)tmp_6);
  rtb_TmpSignalConversionAtSFun_h[83] = (uint16_T)(tmp_5 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_5 : (int32_T)(uint16_T)tmp_5);
  rtb_TmpSignalConversionAtSFun_h[84] = (uint16_T)(tmp_4 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_4 : (int32_T)(uint16_T)tmp_4);
  rtb_TmpSignalConversionAtSFun_h[85] = (uint16_T)(v < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-v : (int32_T)(uint16_T)v);
  rtb_TmpSignalConversionAtSFun_h[86] = bms_B.ux181210E4_o2;
  rtb_TmpSignalConversionAtSFun_h[87] = bms_B.ux181210E4_o4;
  rtb_TmpSignalConversionAtSFun_h[88] = bms_B.ux181210E4_o3;
  rtb_TmpSignalConversionAtSFun_h[89] = bms_B.ux181210E4_o5;
  rtb_TmpSignalConversionAtSFun_h[90] = rtb_DataTypeConversion69;
  rtb_TmpSignalConversionAtSFun_h[91] = bms_B.ux180810E4_o2;
  rtb_TmpSignalConversionAtSFun_h[92] = bms_B.ux180810E4_o5;
  rtb_TmpSignalConversionAtSFun_h[93] = rtb_DataTypeConversion42;
  rtb_TmpSignalConversionAtSFun_h[94] = bms_B.ux180A10E4_o1;
  rtb_TmpSignalConversionAtSFun_h[95] = bms_B.ux180A10E4_o2;
  rtb_TmpSignalConversionAtSFun_h[96] = bms_B.ux180A10E4_o3;
  rtb_TmpSignalConversionAtSFun_h[97] = bms_B.ux180A10E4_o4;
  rtb_TmpSignalConversionAtSFun_h[98] = bms_B.ux180A10E4_o5;
  rtb_TmpSignalConversionAtSFun_h[99] = bms_B.CANUnpack32_o1;
  rtb_TmpSignalConversionAtSFun_h[100] = bms_B.CANUnpack32_o2;
  rtb_TmpSignalConversionAtSFun_h[101] = bms_B.CANUnpack32_o3;
  rtb_TmpSignalConversionAtSFun_h[102] = bms_B.CANUnpack32_o4;
  rtb_TmpSignalConversionAtSFun_h[103] = CFunction10_o2;
  memcpy(&rtb_TmpSignalConversionAtSFun_h[104], &rtb_y_g3[0], 120U * sizeof
         (uint16_T));
  memcpy(&rtb_TmpSignalConversionAtSFun_h[224], &rtb_y_k[0], 240U * sizeof
         (uint16_T));
  rtb_TmpSignalConversionAtSFun_h[464] = (uint16_T)((uint32_T)rtb_Saturation1 >>
    3);
  rtb_TmpSignalConversionAtSFun_h[465] = rtb_DataTypeConversion8;
  rtb_TmpSignalConversionAtSFun_h[466] = bms_B.CANUnpack1_o2;
  rtb_TmpSignalConversionAtSFun_h[467] = rtb_DataTypeConversion11;
  rtb_TmpSignalConversionAtSFun_h[468] = rtb_DataTypeConversion16;
  rtb_TmpSignalConversionAtSFun_h[469] = bms_B.CANUnpack1_o5;
  rtb_TmpSignalConversionAtSFun_h[470] = rtb_DataTypeConversion12;
  rtb_TmpSignalConversionAtSFun_h[471] = rtb_DataTypeConversion13;
  rtb_TmpSignalConversionAtSFun_h[472] = (uint16_T)(rtb_Gain3 >> 11);

  /* DataTypeConversion: '<S2>/Data Type Conversion17' */
  if (u_0 >= 0.5F) {
    i_0 = (int32_T)floorf(u_0 + 0.5F);
  } else {
    i_0 = 0;
  }

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  Chart: '<Root>/Chart1'
   *  DataTypeConversion: '<S2>/Data Type Conversion17'
   *  DataTypeConversion: '<S2>/Data Type Conversion64'
   *  DataTypeConversion: '<S2>/Data Type Conversion65'
   *  DataTypeConversion: '<S2>/Data Type Conversion71'
   *  Gain: '<S2>/Gain32'
   *  Gain: '<S2>/Gain33'
   */
  rtb_TmpSignalConversionAtSFun_h[473] = (uint16_T)fmodf((real32_T)i_0, 65536.0F);
  rtb_TmpSignalConversionAtSFun_h[474] = rtb_DataTypeConversion23;
  rtb_TmpSignalConversionAtSFun_h[475] = rtb_DataTypeConversion24;
  rtb_TmpSignalConversionAtSFun_h[476] = (uint16_T)(tmp_3 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_3 : (int32_T)(uint16_T)tmp_3);
  rtb_TmpSignalConversionAtSFun_h[477] = (uint16_T)(tmp_2 < 0.0 ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_2 : (int32_T)(uint16_T)tmp_2);
  rtb_TmpSignalConversionAtSFun_h[478] = bms_B.CFunction11;
  rtb_TmpSignalConversionAtSFun_h[479] = rtb_DataTypeConversion47;
  rtb_TmpSignalConversionAtSFun_h[480] = rtb_DataTypeConversion50;
  rtb_TmpSignalConversionAtSFun_h[481] = rtb_DataTypeConversion56;
  rtb_TmpSignalConversionAtSFun_h[482] = (uint16_T)(tmp_1 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_1 : (int32_T)(uint16_T)tmp_1);
  rtb_TmpSignalConversionAtSFun_h[483] = (uint16_T)(tmp_0 < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_0 : (int32_T)(uint16_T)tmp_0);
  rtb_TmpSignalConversionAtSFun_h[484] = bms_B.CANUnpack2_o3;
  rtb_TmpSignalConversionAtSFun_h[485] = CFunction12_o1;
  rtb_TmpSignalConversionAtSFun_h[486] = CFunction12_o2;
  rtb_TmpSignalConversionAtSFun_h[487] = (uint16_T)(tmp < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp : (int32_T)(uint16_T)tmp);

  /* DataTypeConversion: '<S2>/Data Type Conversion72' */
  tmp_b = fmodf(floorf(rtb_Gain31), 65536.0F);

  /* SignalConversion generated from: '<S1>/ SFunction ' incorporates:
   *  CFunction: '<S3>/C Function1'
   *  CFunction: '<S3>/C Function10'
   *  CFunction: '<S3>/C Function11'
   *  CFunction: '<S3>/C Function12'
   *  CFunction: '<S3>/C Function13'
   *  CFunction: '<S3>/C Function14'
   *  CFunction: '<S3>/C Function15'
   *  CFunction: '<S3>/C Function16'
   *  CFunction: '<S3>/C Function17'
   *  CFunction: '<S3>/C Function18'
   *  CFunction: '<S3>/C Function19'
   *  CFunction: '<S3>/C Function2'
   *  CFunction: '<S3>/C Function20'
   *  CFunction: '<S3>/C Function21'
   *  CFunction: '<S3>/C Function22'
   *  CFunction: '<S3>/C Function23'
   *  CFunction: '<S3>/C Function24'
   *  CFunction: '<S3>/C Function25'
   *  CFunction: '<S3>/C Function26'
   *  CFunction: '<S3>/C Function27'
   *  CFunction: '<S3>/C Function28'
   *  CFunction: '<S3>/C Function29'
   *  CFunction: '<S3>/C Function3'
   *  CFunction: '<S3>/C Function30'
   *  CFunction: '<S3>/C Function31'
   *  CFunction: '<S3>/C Function32'
   *  CFunction: '<S3>/C Function33'
   *  CFunction: '<S3>/C Function34'
   *  CFunction: '<S3>/C Function35'
   *  CFunction: '<S3>/C Function36'
   *  CFunction: '<S3>/C Function37'
   *  CFunction: '<S3>/C Function38'
   *  CFunction: '<S3>/C Function39'
   *  CFunction: '<S3>/C Function4'
   *  CFunction: '<S3>/C Function40'
   *  CFunction: '<S3>/C Function41'
   *  CFunction: '<S3>/C Function42'
   *  CFunction: '<S3>/C Function43'
   *  CFunction: '<S3>/C Function44'
   *  CFunction: '<S3>/C Function45'
   *  CFunction: '<S3>/C Function5'
   *  CFunction: '<S3>/C Function6'
   *  CFunction: '<S3>/C Function7'
   *  CFunction: '<S3>/C Function8'
   *  CFunction: '<S3>/C Function9'
   *  Chart: '<Root>/Chart1'
   *  DataTypeConversion: '<S2>/Data Type Conversion72'
   */
  rtb_TmpSignalConversionAtSFun_h[488] = (uint16_T)(tmp_b < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-tmp_b : (int32_T)(uint16_T)tmp_b);
  for (i_0 = 0; i_0 < 15; i_0++) {
    rtb_TmpSignalConversionAtSFun_h[i_0 + 489] = rtb_y[i_0];
  }

  rtb_TmpSignalConversionAtSFun_h[504] = CFunction13;
  rtb_TmpSignalConversionAtSFun_h[505] = rtb_Saturation8;
  rtb_TmpSignalConversionAtSFun_h[506] = rtb_DataTypeConversion80;
  rtb_TmpSignalConversionAtSFun_h[507] = (uint16_T)(bms_B.ux180110E4_o2_a << 8 |
    bms_B.ux180110E4_o1);
  rtb_TmpSignalConversionAtSFun_h[508] = (uint16_T)(bms_B.ux180110E2_o2 << 8 |
    bms_B.ux180110E2_o1_o);
  rtb_TmpSignalConversionAtSFun_h[509] = (uint16_T)(bms_B.ux180110E1_o2 << 8 |
    bms_B.ux180110E1_o1);
  rtb_TmpSignalConversionAtSFun_h[510] = (uint16_T)(bms_B.ux180110E5_o2 << 8 |
    bms_B.ux180110E5_o1);
  rtb_TmpSignalConversionAtSFun_h[511] = (uint16_T)(bms_B.ux180110E3_o2 << 8 |
    bms_B.ux180110E3_o1);
  rtb_TmpSignalConversionAtSFun_h[512] = (uint16_T)(bms_B.ux180110E7_o2 << 8 |
    bms_B.ux180110E7_o1);
  rtb_TmpSignalConversionAtSFun_h[513] = (uint16_T)(bms_B.ux180110E6_o2 << 8 |
    bms_B.ux180110E6_o1);
  rtb_TmpSignalConversionAtSFun_h[514] = (uint16_T)(bms_B.ux180110E9_o2 << 8 |
    bms_B.ux180110E9_o1);
  rtb_TmpSignalConversionAtSFun_h[515] = (uint16_T)(bms_B.ux180110E8_o2 << 8 |
    bms_B.ux180110E8_o1);
  rtb_TmpSignalConversionAtSFun_h[516] = (uint16_T)(bms_B.ux180110E11_o2 << 8 |
    bms_B.ux180110E11_o1);
  rtb_TmpSignalConversionAtSFun_h[517] = (uint16_T)(bms_B.ux180110E10_o2 << 8 |
    bms_B.ux180110E10_o1);
  rtb_TmpSignalConversionAtSFun_h[518] = (uint16_T)(bms_B.ux180110E13_o2 << 8 |
    bms_B.ux180110E13_o1);
  rtb_TmpSignalConversionAtSFun_h[519] = (uint16_T)(bms_B.ux180110E12_o2 << 8 |
    bms_B.ux180110E12_o1);
  rtb_TmpSignalConversionAtSFun_h[520] = (uint16_T)(bms_B.ux180110E15_o2 << 8 |
    bms_B.ux180110E15_o1);
  rtb_TmpSignalConversionAtSFun_h[521] = (uint16_T)(bms_B.ux180110E14_o2 << 8 |
    bms_B.ux180110E14_o1);
  rtb_TmpSignalConversionAtSFun_h[522] = (uint16_T)(bms_B.ux180110E16_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[523] = (uint16_T)(bms_B.ux180110E16_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[524] = (uint16_T)(bms_B.ux180110E16_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[525] = (uint16_T)(bms_B.ux180110E16_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[526] = (uint16_T)(bms_B.ux180110E17_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[527] = (uint16_T)(bms_B.ux180110E17_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[528] = (uint16_T)(bms_B.ux180110E17_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[529] = (uint16_T)(bms_B.ux180110E17_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[530] = (uint16_T)(bms_B.ux180110E18_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[531] = (uint16_T)(bms_B.ux180110E18_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[532] = (uint16_T)(bms_B.ux180110E18_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[533] = (uint16_T)(bms_B.ux180110E18_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[534] = (uint16_T)(bms_B.ux180110E19_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[535] = (uint16_T)(bms_B.ux180110E19_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[536] = (uint16_T)(bms_B.ux180110E19_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[537] = (uint16_T)(bms_B.ux180110E19_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[538] = (uint16_T)(bms_B.ux180110E20_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[539] = (uint16_T)(bms_B.ux180110E20_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[540] = (uint16_T)(bms_B.ux180110E20_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[541] = (uint16_T)(bms_B.ux180110E20_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[542] = (uint16_T)(bms_B.ux180110E21_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[543] = (uint16_T)(bms_B.ux180110E21_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[544] = (uint16_T)(bms_B.ux180110E21_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[545] = (uint16_T)(bms_B.ux180110E21_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[546] = (uint16_T)(bms_B.ux180110E22_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[547] = (uint16_T)(bms_B.ux180110E22_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[548] = (uint16_T)(bms_B.ux180110E22_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[549] = (uint16_T)(bms_B.ux180110E22_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[550] = (uint16_T)(bms_B.ux180110E23_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[551] = (uint16_T)(bms_B.ux180110E23_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[552] = (uint16_T)(bms_B.ux180110E23_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[553] = (uint16_T)(bms_B.ux180110E23_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[554] = (uint16_T)(bms_B.ux180110E24_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[555] = (uint16_T)(bms_B.ux180110E24_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[556] = (uint16_T)(bms_B.ux180110E24_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[557] = (uint16_T)(bms_B.ux180110E24_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[558] = (uint16_T)(bms_B.ux180110E25_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[559] = (uint16_T)(bms_B.ux180110E25_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[560] = (uint16_T)(bms_B.ux180110E25_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[561] = (uint16_T)(bms_B.ux180110E25_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[562] = (uint16_T)(bms_B.ux180110E26_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[563] = (uint16_T)(bms_B.ux180110E26_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[564] = (uint16_T)(bms_B.ux180110E26_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[565] = (uint16_T)(bms_B.ux180110E26_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[566] = (uint16_T)(bms_B.ux180110E27_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[567] = (uint16_T)(bms_B.ux180110E27_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[568] = (uint16_T)(bms_B.ux180110E27_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[569] = (uint16_T)(bms_B.ux180110E27_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[570] = (uint16_T)(bms_B.ux180110E28_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[571] = (uint16_T)(bms_B.ux180110E28_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[572] = (uint16_T)(bms_B.ux180110E28_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[573] = (uint16_T)(bms_B.ux180110E28_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[574] = (uint16_T)(bms_B.ux180110E29_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[575] = (uint16_T)(bms_B.ux180110E29_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[576] = (uint16_T)(bms_B.ux180110E29_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[577] = (uint16_T)(bms_B.ux180110E29_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[578] = (uint16_T)(bms_B.ux180110E30_o1 >> 16);
  rtb_TmpSignalConversionAtSFun_h[579] = (uint16_T)(bms_B.ux180110E30_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFun_h[580] = (uint16_T)(bms_B.ux180110E30_o2 >> 16);
  rtb_TmpSignalConversionAtSFun_h[581] = (uint16_T)(bms_B.ux180110E30_o2 &
    65535U);

  /* Chart: '<Root>/Chart1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Outport: '<Root>/modbusBuff'
   */
  rtb_Gain15 = 0U;
  port_index = 0U;
  port_len = sizeof(uint32_T);
  if (port_len == 0U) {
    port_len = MAX_uint32_T;

    /* Divide by zero handler */
  } else {
    port_len = sizeof(uint32_T [196]) / port_len;
  }

  while (port_index < port_len) {
    if (bms_ConstP.Constant2_Value[port_index] == 1U) {
      modbusBuff_C[bms_ConstP.Constant1_Value[port_index]] =
        rtb_TmpSignalConversionAtSFun_h[rtb_Gain15];
      qY = rtb_Gain15 + /*MW:OvSatOk*/ 1U;
      if (rtb_Gain15 + 1U < rtb_Gain15) {
        qY = MAX_uint32_T;
      }

      rtb_Gain15 = qY;
    } else {
      rtb_DataTypeConversion80 = 0U;
      while (rtb_DataTypeConversion80 < bms_ConstP.Constant2_Value[port_index])
      {
        q0 = bms_ConstP.Constant1_Value[port_index];
        qY = q0 + /*MW:OvSatOk*/ rtb_DataTypeConversion80;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        modbusBuff_C[qY] = rtb_TmpSignalConversionAtSFun_h[rtb_Gain15];
        qY = rtb_Gain15 + /*MW:OvSatOk*/ 1U;
        if (rtb_Gain15 + 1U < rtb_Gain15) {
          qY = MAX_uint32_T;
        }

        rtb_Gain15 = qY;
        i_0 = rtb_DataTypeConversion80 + 1;
        if (rtb_DataTypeConversion80 + 1 > 65535) {
          i_0 = 65535;
        }

        rtb_DataTypeConversion80 = (uint16_T)i_0;
      }
    }

    port_index++;
  }

  /* S-Function (scanunpack): '<S2>/0x180110E2' */
  {
    /* S-Function (scanunpack): '<S2>/0x180110E2' */
    if ((8 == bms_B.CANBuff1.Length) && (bms_B.CANBuff1.ID != INVALID_CAN_ID) )
    {
      if ((0x182310E4 == bms_B.CANBuff1.ID) && (1U == bms_B.CANBuff1.Extended) )
      {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 56
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint16_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              bms_B.ux180110E2_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 16
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeDay = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeHour = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 32
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeMinute = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 8
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeMonth = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 40
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeSencond = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 48
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeWeek = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 0
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            uint8_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(bms_B.CANBuff1.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              BCU_TimeYear = result;
            }
          }
        }
      }
    }
  }
}

/* Model initialize function */
void bms_initialize(void)
{
  /* Start for S-Function (scanunpack): '<S2>/0x180110E4' */

  /*-----------S-Function Block: <S2>/0x180110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x1C0110E4' */

  /*-----------S-Function Block: <S2>/0x1C0110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x1B0310E4' */

  /*-----------S-Function Block: <S2>/0x1B0310E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180210E4' */

  /*-----------S-Function Block: <S2>/0x180210E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack5' */

  /*-----------S-Function Block: <S2>/CAN Unpack5 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180410E4' */

  /*-----------S-Function Block: <S2>/0x180410E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack10' */

  /*-----------S-Function Block: <S2>/CAN Unpack10 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack11' */

  /*-----------S-Function Block: <S2>/CAN Unpack11 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180E10E4' */

  /*-----------S-Function Block: <S2>/0x180E10E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180F10E4' */

  /*-----------S-Function Block: <S2>/0x180F10E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x181010E4' */

  /*-----------S-Function Block: <S2>/0x181010E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x181110E4' */

  /*-----------S-Function Block: <S2>/0x181110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180710E4' */

  /*-----------S-Function Block: <S2>/0x180710E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/SOX' */

  /*-----------S-Function Block: <S2>/SOX -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack19' */

  /*-----------S-Function Block: <S2>/CAN Unpack19 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x181310E4' */

  /*-----------S-Function Block: <S2>/0x181310E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180B10E4' */

  /*-----------S-Function Block: <S2>/0x180B10E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180C10E4' */

  /*-----------S-Function Block: <S2>/0x180C10E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x181410E4' */

  /*-----------S-Function Block: <S2>/0x181410E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack27' */

  /*-----------S-Function Block: <S2>/CAN Unpack27 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x181210E4' */

  /*-----------S-Function Block: <S2>/0x181210E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180810E4' */

  /*-----------S-Function Block: <S2>/0x180810E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180A10E4' */

  /*-----------S-Function Block: <S2>/0x180A10E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack32' */

  /*-----------S-Function Block: <S2>/CAN Unpack32 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x1B0110E4' */

  /*-----------S-Function Block: <S2>/0x1B0110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack29' */

  /*-----------S-Function Block: <S2>/CAN Unpack29 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack1' */

  /*-----------S-Function Block: <S2>/CAN Unpack1 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack2' */

  /*-----------S-Function Block: <S2>/CAN Unpack2 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack3' */

  /*-----------S-Function Block: <S2>/CAN Unpack3 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack4' */

  /*-----------S-Function Block: <S2>/CAN Unpack4 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack6' */

  /*-----------S-Function Block: <S2>/CAN Unpack6 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack7' */

  /*-----------S-Function Block: <S2>/CAN Unpack7 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/CAN Unpack8' */

  /*-----------S-Function Block: <S2>/CAN Unpack8 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E4' */

  /*-----------S-Function Block: <S3>/0x180110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E2' */

  /*-----------S-Function Block: <S3>/0x180110E2 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E1' */

  /*-----------S-Function Block: <S3>/0x180110E1 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E5' */

  /*-----------S-Function Block: <S3>/0x180110E5 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E3' */

  /*-----------S-Function Block: <S3>/0x180110E3 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E7' */

  /*-----------S-Function Block: <S3>/0x180110E7 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E6' */

  /*-----------S-Function Block: <S3>/0x180110E6 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E9' */

  /*-----------S-Function Block: <S3>/0x180110E9 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E8' */

  /*-----------S-Function Block: <S3>/0x180110E8 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E11' */

  /*-----------S-Function Block: <S3>/0x180110E11 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E10' */

  /*-----------S-Function Block: <S3>/0x180110E10 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E13' */

  /*-----------S-Function Block: <S3>/0x180110E13 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E12' */

  /*-----------S-Function Block: <S3>/0x180110E12 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E15' */

  /*-----------S-Function Block: <S3>/0x180110E15 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E14' */

  /*-----------S-Function Block: <S3>/0x180110E14 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E16' */

  /*-----------S-Function Block: <S3>/0x180110E16 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E17' */

  /*-----------S-Function Block: <S3>/0x180110E17 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E18' */

  /*-----------S-Function Block: <S3>/0x180110E18 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E19' */

  /*-----------S-Function Block: <S3>/0x180110E19 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E20' */

  /*-----------S-Function Block: <S3>/0x180110E20 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E21' */

  /*-----------S-Function Block: <S3>/0x180110E21 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E22' */

  /*-----------S-Function Block: <S3>/0x180110E22 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E23' */

  /*-----------S-Function Block: <S3>/0x180110E23 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E24' */

  /*-----------S-Function Block: <S3>/0x180110E24 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E25' */

  /*-----------S-Function Block: <S3>/0x180110E25 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E26' */

  /*-----------S-Function Block: <S3>/0x180110E26 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E27' */

  /*-----------S-Function Block: <S3>/0x180110E27 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E28' */

  /*-----------S-Function Block: <S3>/0x180110E28 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E29' */

  /*-----------S-Function Block: <S3>/0x180110E29 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E30' */

  /*-----------S-Function Block: <S3>/0x180110E30 -----------------*/

  /* Start for S-Function (scanunpack): '<S2>/0x180110E2' */

  /*-----------S-Function Block: <S2>/0x180110E2 -----------------*/
}

/* Model terminate function */
void bms_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
