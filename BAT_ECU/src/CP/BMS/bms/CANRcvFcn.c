/*
 * File: CANRcvFcn.c
 *
 * Code generated for Simulink model 'CANRcvFcn'.
 *
 * Model version                  : 3.284
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Aug 13 13:48:29 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CANRcvFcn.h"
#include <math.h>
#include <string.h>
#include "CANRcvFcn_types.h"
#include "rtwtypes.h"
#include "CANRcvFcn_private.h"

/* Exported block signals */
CAN_FD_MESSAGE_BUS CANFDRcvMsg;        /* '<Root>/CANFDRcvMsg' */
CAN_MESSAGE_BUS CANMsg;                /* '<Root>/CANMsg' */

/* Block signals (default storage) */
B_CANRcvFcn_T CANRcvFcn_B;

/* Block states (default storage) */
DW_CANRcvFcn_T CANRcvFcn_DW;

/* Real-time model */
static RT_MODEL_CANRcvFcn_T CANRcvFcn_M_;
RT_MODEL_CANRcvFcn_T *const CANRcvFcn_M = &CANRcvFcn_M_;

/* Exported data definition */

/* Definition for custom storage class: Default */
uint32_T BCU_FaultInfoLv1H;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv1L;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv2H;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv2L;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv3H;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv3L;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv4H;            /* '<S1>/CAN FD Unpack1' */
uint32_T BCU_FaultInfoLv4L;            /* '<S1>/CAN FD Unpack1' */
uint16_T BCU_SOC;                      /* '<S1>/Data Type Conversion35' */
uint16_T BCU_SystemStatus;             /* '<S6>/Constant' */
uint16_T BCU_SystemWorkMode;           /* '<S1>/CAN FD Unpack1' */
uint8_T BCU_TimeDay;                   /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeHour;                  /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeMinute;                /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeMonth;                 /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeSencond;               /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeWeek;                  /* '<S1>/CAN FD Unpack' */
uint8_T BCU_TimeYear;                  /* '<S1>/CAN FD Unpack' */

/* Model step function */
void bms_CANRcvFcn(void)
{
  int32_T tmp;
  int32_T y;
  real32_T u;
  real32_T v;
  uint32_T data_index;
  uint32_T port_index;
  uint32_T port_len;
  uint32_T q0;
  uint32_T qY;
  uint16_T rtb_TmpSignalConversionAtSFunct[593];
  uint16_T rtb_TmpSignalConversionAtSFun_a[60];
  uint16_T rtb_TmpSignalConversionAtSFu_kh[30];
  uint16_T CFunction1_o1;
  uint16_T CFunction1_o2;
  uint16_T CFunction_o1;
  uint16_T CFunction_o2;
  uint16_T c;
  uint16_T i;
  uint16_T rtb_DataTypeConversion27;
  uint16_T rtb_DataTypeConversion29;
  uint8_T b;
  uint8_T i_0;
  uint8_T rtb_Saturation2;

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack1' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack1' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((402723044 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[6]);
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
           *  startBit                = 120
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[15]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[14]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = (result * 0.1F) + -3200.0F;
              CANRcvFcn_B.CANFDUnpack1_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 136
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[17]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[16]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = (result * 0.1F) + -3200.0F;
              CANRcvFcn_B.CANFDUnpack1_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 248
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[31]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[30]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[29]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[28]) << 24);
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

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 216
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[27]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[26]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[25]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[24]) << 24);
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

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 312
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[39]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[38]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[37]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[36]) << 24);
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

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 280
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[35]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[34]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[33]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[32]) << 24);
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

          /* --------------- START Unpacking signal 9 ------------------
           *  startBit                = 376
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[47]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[46]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[45]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[44]) << 24);
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

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 344
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[43]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[42]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[41]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[40]) << 24);
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

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 440
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[55]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[54]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[53]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[52]) << 24);
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

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 408
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[51]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[50]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[49]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[48]) << 24);
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

          /* --------------- START Unpacking signal 13 ------------------
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
                    (CANFDRcvMsg.Data[7]) & (uint8_T)(0xCU)) >> 2);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
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
                  tempValue = tempValue | (uint8_T)((uint8_T)(CANFDRcvMsg.Data[7])
                    & (uint8_T)(0x3U));
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
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
                    (CANFDRcvMsg.Data[7]) & (uint8_T)(0x30U)) >> 4);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
           *  startBit                = 472
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[59]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[58]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
           *  startBit                = 488
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[61]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[60]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
           *  startBit                = 504
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[63]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[62]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
           *  startBit                = 456
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[57]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[56]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
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
                    (CANFDRcvMsg.Data[7]) & (uint8_T)(0xC0U)) >> 6);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              CANRcvFcn_B.CANFDUnpack1_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 184
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[23]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[22]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 168
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[21]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[20]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
           *  startBit                = 152
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[19]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[18]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack1_o25 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack3' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack3' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((402854116 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 312
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[39]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[38]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 408
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[51]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[50]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[49]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[48]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 376
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[47]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[46]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 264
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[33]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[32]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 360
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[45]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[44]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[43]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[42]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 328
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[41]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[40]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 296
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[37]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[36]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[35]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[34]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 168
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[21]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[20]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 184
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[23]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[22]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o9 = result;
            }
          }

          /* --------------- START Unpacking signal 9 ------------------
           *  startBit                = 200
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[25]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[24]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o10 = result;
            }
          }

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 208
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[26]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o11 = result;
            }
          }

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 232
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[29]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[28]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o12 = result;
            }
          }

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 248
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[31]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[30]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o13 = result;
            }
          }

          /* --------------- START Unpacking signal 13 ------------------
           *  startBit                = 152
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[19]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
           *  startBit                = 432
           *  length                  = 24
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -8.388608E+6
           * -----------------------------------------------------------------------*/
          {
            int32_T outValue = 0;

            {
              uint32_T unpackedValue = 0;

              {
                uint32_T tempValue = (uint32_T) (0);

                {
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[54]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[53]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[52]) << 16);
                }

                unpackedValue = tempValue;
              }

              outValue = (int32_T) (unpackedValue);
            }

            {
              int32_T result = (int32_T) outValue;
              result = result + -8388608;
              CANRcvFcn_B.CANFDUnpack3_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
           *  startBit                = 216
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
                  tempValue = tempValue | (uint8_T)((uint8_T)(CANFDRcvMsg.Data
                    [27]) & (uint8_T)(0x3U));
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
           *  startBit                = 220
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
                    (CANFDRcvMsg.Data[27]) & (uint8_T)(0x30U)) >> 4);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
           *  startBit                = 218
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
                    (CANFDRcvMsg.Data[27]) & (uint8_T)(0xCU)) >> 2);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack3_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
           *  startBit                = 110
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
                    (CANFDRcvMsg.Data[13]) & (uint8_T)(0x40U)) >> 6);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 88
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[11]);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 72
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[9]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[8]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
           *  startBit                = 96
           *  length                  = 8
           *  desiredSignalByteLayout = BIGENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real32_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[12]);
                }

                unpackedValue = tempValue;
              }

              outValue = (real32_T) (unpackedValue);
            }

            {
              real32_T result = (real32_T) outValue;
              result = result * 0.1F;
              CANRcvFcn_B.CANFDUnpack3_o25 = result;
            }
          }

          /* --------------- START Unpacking signal 25 ------------------
           *  startBit                = 120
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[15]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o26 = result;
            }
          }

          /* --------------- START Unpacking signal 26 ------------------
           *  startBit                = 128
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[16]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o27 = result;
            }
          }

          /* --------------- START Unpacking signal 27 ------------------
           *  startBit                = 109
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
                    (CANFDRcvMsg.Data[13]) & (uint8_T)(0x20U)) >> 5);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o28 = result;
            }
          }

          /* --------------- START Unpacking signal 28 ------------------
           *  startBit                = 111
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
                    (CANFDRcvMsg.Data[13]) & (uint8_T)(0x80U)) >> 7);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o29 = result;
            }
          }

          /* --------------- START Unpacking signal 29 ------------------
           *  startBit                = 108
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
                    (CANFDRcvMsg.Data[13]) & (uint8_T)(0x10U)) >> 4);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o30 = result;
            }
          }

          /* --------------- START Unpacking signal 30 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack3_o31 = result;
            }
          }

          /* --------------- START Unpacking signal 31 ------------------
           *  startBit                = 112
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[14]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o32 = result;
            }
          }

          /* --------------- START Unpacking signal 32 ------------------
           *  startBit                = 136
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[17]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o33 = result;
            }
          }

          /* --------------- START Unpacking signal 33 ------------------
           *  startBit                = 144
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[18]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o34 = result;
            }
          }

          /* --------------- START Unpacking signal 34 ------------------
           *  startBit                = 107
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
                    (CANFDRcvMsg.Data[13]) & (uint8_T)(0x8U)) >> 3);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o35 = result;
            }
          }

          /* --------------- START Unpacking signal 35 ------------------
           *  startBit                = 80
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[10]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o36 = result;
            }
          }

          /* --------------- START Unpacking signal 36 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack3_o37 = result;
            }
          }

          /* --------------- START Unpacking signal 37 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack3_o38 = result;
            }
          }

          /* --------------- START Unpacking signal 38 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack3_o39 = result;
            }
          }

          /* --------------- START Unpacking signal 39 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack3_o40 = result;
            }
          }
        }
      }
    }
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion18' incorporates:
   *  Gain: '<S1>/Gain17'
   */
  u = 1000.0F * CANRcvFcn_B.CANFDUnpack3_o2;
  if (u < 4.2949673E+9F) {
    if (u >= 0.0F) {
      data_index = (uint32_T)u;
    } else {
      data_index = 0U;
    }
  } else {
    data_index = MAX_uint32_T;
  }

  /* CFunction: '<S1>/C Function' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion18'
   */
  CFunction_o1 = (uint16_T)(data_index >> 16);

  /* CFunction: '<S1>/C Function' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion18'
   */
  CFunction_o2 = (uint16_T)(data_index & 65535U);

  /* DataTypeConversion: '<S1>/Data Type Conversion20' incorporates:
   *  Gain: '<S1>/Gain18'
   */
  u = 1000.0F * CANRcvFcn_B.CANFDUnpack3_o5;
  if (u < 4.2949673E+9F) {
    if (u >= 0.0F) {
      data_index = (uint32_T)u;
    } else {
      data_index = 0U;
    }
  } else {
    data_index = MAX_uint32_T;
  }

  /* CFunction: '<S1>/C Function1' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion20'
   */
  CFunction1_o1 = (uint16_T)(data_index >> 16);

  /* CFunction: '<S1>/C Function1' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion20'
   */
  CFunction1_o2 = (uint16_T)(data_index & 65535U);

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((402919652 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 240
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[30]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 248
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[31]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 256
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[32]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 264
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[33]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 272
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[34]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 280
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[35]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 288
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[36]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 296
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[37]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 304
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[38]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o9 = result;
            }
          }

          /* --------------- START Unpacking signal 9 ------------------
           *  startBit                = 312
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[39]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o10 = result;
            }
          }

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 320
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[40]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o11 = result;
            }
          }

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 328
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[41]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o12 = result;
            }
          }

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 336
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[42]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o13 = result;
            }
          }

          /* --------------- START Unpacking signal 13 ------------------
           *  startBit                = 344
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[43]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
           *  startBit                = 352
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[44]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[0]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[5]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[7]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[6]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
           *  startBit                = 72
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[9]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[8]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
           *  startBit                = 88
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[11]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[10]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 104
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[13]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[12]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 120
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[15]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[14]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
           *  startBit                = 136
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[17]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[16]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
           *  startBit                = 152
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[19]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[18]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o25 = result;
            }
          }

          /* --------------- START Unpacking signal 25 ------------------
           *  startBit                = 168
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[21]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[20]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o26 = result;
            }
          }

          /* --------------- START Unpacking signal 26 ------------------
           *  startBit                = 184
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[23]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[22]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o27 = result;
            }
          }

          /* --------------- START Unpacking signal 27 ------------------
           *  startBit                = 200
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[25]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[24]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o28 = result;
            }
          }

          /* --------------- START Unpacking signal 28 ------------------
           *  startBit                = 216
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[27]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[26]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o29 = result;
            }
          }

          /* --------------- START Unpacking signal 29 ------------------
           *  startBit                = 232
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[29]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[28]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o30 = result;
            }
          }

          /* --------------- START Unpacking signal 30 ------------------
           *  startBit                = 448
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[56]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o31 = result;
            }
          }

          /* --------------- START Unpacking signal 31 ------------------
           *  startBit                = 440
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[55]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[54]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o32 = result;
            }
          }

          /* --------------- START Unpacking signal 32 ------------------
           *  startBit                = 424
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[53]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o33 = result;
            }
          }

          /* --------------- START Unpacking signal 33 ------------------
           *  startBit                = 416
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[52]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[51]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o34 = result;
            }
          }

          /* --------------- START Unpacking signal 34 ------------------
           *  startBit                = 376
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[47]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o35 = result;
            }
          }

          /* --------------- START Unpacking signal 35 ------------------
           *  startBit                = 368
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[46]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[45]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o36 = result;
            }
          }

          /* --------------- START Unpacking signal 36 ------------------
           *  startBit                = 400
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[50]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o37 = result;
            }
          }

          /* --------------- START Unpacking signal 37 ------------------
           *  startBit                = 392
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[49]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[48]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack_o38 = result;
            }
          }

          /* --------------- START Unpacking signal 38 ------------------
           *  startBit                = 456
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[57]);
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

          /* --------------- START Unpacking signal 39 ------------------
           *  startBit                = 480
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[60]);
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

          /* --------------- START Unpacking signal 40 ------------------
           *  startBit                = 488
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[61]);
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

          /* --------------- START Unpacking signal 41 ------------------
           *  startBit                = 496
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[62]);
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

          /* --------------- START Unpacking signal 42 ------------------
           *  startBit                = 472
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[59]);
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

          /* --------------- START Unpacking signal 43 ------------------
           *  startBit                = 504
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[63]);
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

          /* --------------- START Unpacking signal 44 ------------------
           *  startBit                = 464
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[58]);
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

  /* DataTypeConversion: '<S1>/Data Type Conversion22' incorporates:
   *  Gain: '<S1>/Gain21'
   */
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o7), 4.2949673E+9F);
  data_index = u < 0.0F ? (uint32_T)-(int32_T)(uint32_T)-u : (uint32_T)u;

  /* Gain: '<S1>/Gain22' */
  u = 0.00999999F * (real32_T)CANRcvFcn_B.CANFDUnpack1_o18;

  /* DataTypeConversion: '<S1>/Data Type Conversion35' */
  if (u >= 0.5F) {
    tmp = (int32_T)floorf(u + 0.5F);
  } else {
    tmp = 0;
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion35' */
  BCU_SOC = (uint16_T)fmodf((real32_T)tmp, 65536.0F);

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack2' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack2' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((402788580 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 40
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
                  tempValue = tempValue | (uint32_T)(CANFDRcvMsg.Data[5]);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[4]) << 8);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[3]) << 16);
                  tempValue = tempValue | (uint32_T)((uint32_T)
                    (CANFDRcvMsg.Data[2]) << 24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 168
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[21]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 176
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[22]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 56
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 80
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[10]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 72
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[9]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 88
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[11]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o9 = result;
            }
          }

          /* --------------- START Unpacking signal 9 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o10 = result;
            }
          }

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 160
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[20]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o11 = result;
            }
          }

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 144
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[18]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o12 = result;
            }
          }

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 152
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[19]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o13 = result;
            }
          }

          /* --------------- START Unpacking signal 13 ------------------
           *  startBit                = 136
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[17]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
           *  startBit                = 128
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[16]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
           *  startBit                = 232
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[29]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
           *  startBit                = 224
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[28]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
           *  startBit                = 216
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[27]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
           *  startBit                = 200
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[25]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
           *  startBit                = 120
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[15]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
           *  startBit                = 112
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[14]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 104
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[13]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 208
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[26]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
           *  startBit                = 192
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[24]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
           *  startBit                = 96
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[12]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o25 = result;
            }
          }

          /* --------------- START Unpacking signal 25 ------------------
           *  startBit                = 184
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[23]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack2_o26 = result;
            }
          }

          /* --------------- START Unpacking signal 26 ------------------
           *  startBit                = 288
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[36]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o27 = result;
            }
          }

          /* --------------- START Unpacking signal 27 ------------------
           *  startBit                = 264
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[33]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[32]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o28 = result;
            }
          }

          /* --------------- START Unpacking signal 28 ------------------
           *  startBit                = 296
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[37]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o29 = result;
            }
          }

          /* --------------- START Unpacking signal 29 ------------------
           *  startBit                = 280
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[35]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o30 = result;
            }
          }

          /* --------------- START Unpacking signal 30 ------------------
           *  startBit                = 248
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[31]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[30]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o31 = result;
            }
          }

          /* --------------- START Unpacking signal 31 ------------------
           *  startBit                = 304
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[38]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o32 = result;
            }
          }

          /* --------------- START Unpacking signal 32 ------------------
           *  startBit                = 368
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[46]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o33 = result;
            }
          }

          /* --------------- START Unpacking signal 33 ------------------
           *  startBit                = 392
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[49]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[48]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o34 = result;
            }
          }

          /* --------------- START Unpacking signal 34 ------------------
           *  startBit                = 312
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[39]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o35 = result;
            }
          }

          /* --------------- START Unpacking signal 35 ------------------
           *  startBit                = 376
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[47]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o36 = result;
            }
          }

          /* --------------- START Unpacking signal 36 ------------------
           *  startBit                = 416
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[52]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[51]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o37 = result;
            }
          }

          /* --------------- START Unpacking signal 37 ------------------
           *  startBit                = 328
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[41]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[40]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o38 = result;
            }
          }

          /* --------------- START Unpacking signal 38 ------------------
           *  startBit                = 336
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[42]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o39 = result;
            }
          }

          /* --------------- START Unpacking signal 39 ------------------
           *  startBit                = 344
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[43]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o40 = result;
            }
          }

          /* --------------- START Unpacking signal 40 ------------------
           *  startBit                = 400
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[50]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o41 = result;
            }
          }

          /* --------------- START Unpacking signal 41 ------------------
           *  startBit                = 360
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[45]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[44]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o42 = result;
            }
          }

          /* --------------- START Unpacking signal 42 ------------------
           *  startBit                = 424
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[53]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o43 = result;
            }
          }

          /* --------------- START Unpacking signal 43 ------------------
           *  startBit                = 440
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[55]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[54]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o44 = result;
            }
          }

          /* --------------- START Unpacking signal 44 ------------------
           *  startBit                = 448
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[56]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o45 = result;
            }
          }

          /* --------------- START Unpacking signal 45 ------------------
           *  startBit                = 464
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[58]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[57]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack2_o46 = result;
            }
          }
        }
      }
    }
  }

  /* Gain: '<S1>/Gain8' */
  u = 10.0F * CANRcvFcn_B.CANFDUnpack1_o24;

  /* DataTypeConversion: '<S1>/Data Type Conversion29' */
  v = fabsf(u);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u = floorf(u + 0.5F);
    } else {
      u = 0.0F;
    }
  }

  u = fmodf(u, 65536.0F);
  rtb_DataTypeConversion29 = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u : (int32_T)(uint16_T)u);

  /* End of DataTypeConversion: '<S1>/Data Type Conversion29' */

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack4' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack4' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((453054692 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[2]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o2 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[3]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o3 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[4]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o4 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[5]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o5 = result;
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[6]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 56
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[7]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 64
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[8]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 72
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[9]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o9 = result;
            }
          }

          /* --------------- START Unpacking signal 9 ------------------
           *  startBit                = 80
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[10]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o10 = result;
            }
          }

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 88
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[11]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o11 = result;
            }
          }

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 96
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[12]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o12 = result;
            }
          }

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 104
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[13]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o13 = result;
            }
          }

          /* --------------- START Unpacking signal 13 ------------------
           *  startBit                = 112
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[14]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
           *  startBit                = 120
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[15]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
           *  startBit                = 128
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[16]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
           *  startBit                = 136
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[17]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
           *  startBit                = 144
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[18]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
           *  startBit                = 152
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[19]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
           *  startBit                = 160
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[20]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
           *  startBit                = 168
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[21]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 176
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[22]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 184
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[23]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
           *  startBit                = 192
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[24]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
           *  startBit                = 200
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[25]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o25 = result;
            }
          }

          /* --------------- START Unpacking signal 25 ------------------
           *  startBit                = 208
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[26]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o26 = result;
            }
          }

          /* --------------- START Unpacking signal 26 ------------------
           *  startBit                = 216
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[27]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o27 = result;
            }
          }

          /* --------------- START Unpacking signal 27 ------------------
           *  startBit                = 224
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[28]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o28 = result;
            }
          }

          /* --------------- START Unpacking signal 28 ------------------
           *  startBit                = 232
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[29]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o29 = result;
            }
          }

          /* --------------- START Unpacking signal 29 ------------------
           *  startBit                = 240
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[30]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o30 = result;
            }
          }

          /* --------------- START Unpacking signal 30 ------------------
           *  startBit                = 248
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[31]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o31 = result;
            }
          }

          /* --------------- START Unpacking signal 31 ------------------
           *  startBit                = 256
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[32]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o32 = result;
            }
          }

          /* --------------- START Unpacking signal 32 ------------------
           *  startBit                = 264
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[33]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o33 = result;
            }
          }

          /* --------------- START Unpacking signal 33 ------------------
           *  startBit                = 272
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[34]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o34 = result;
            }
          }

          /* --------------- START Unpacking signal 34 ------------------
           *  startBit                = 280
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[35]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o35 = result;
            }
          }

          /* --------------- START Unpacking signal 35 ------------------
           *  startBit                = 288
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[36]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o36 = result;
            }
          }

          /* --------------- START Unpacking signal 36 ------------------
           *  startBit                = 296
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[37]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o37 = result;
            }
          }

          /* --------------- START Unpacking signal 37 ------------------
           *  startBit                = 304
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[38]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o38 = result;
            }
          }

          /* --------------- START Unpacking signal 38 ------------------
           *  startBit                = 312
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[39]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o39 = result;
            }
          }

          /* --------------- START Unpacking signal 39 ------------------
           *  startBit                = 320
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[40]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o40 = result;
            }
          }

          /* --------------- START Unpacking signal 40 ------------------
           *  startBit                = 328
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[41]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o41 = result;
            }
          }

          /* --------------- START Unpacking signal 41 ------------------
           *  startBit                = 336
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[42]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o42 = result;
            }
          }

          /* --------------- START Unpacking signal 42 ------------------
           *  startBit                = 344
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[43]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o43 = result;
            }
          }

          /* --------------- START Unpacking signal 43 ------------------
           *  startBit                = 352
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[44]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o44 = result;
            }
          }

          /* --------------- START Unpacking signal 44 ------------------
           *  startBit                = 360
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[45]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o45 = result;
            }
          }

          /* --------------- START Unpacking signal 45 ------------------
           *  startBit                = 368
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[46]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o46 = result;
            }
          }

          /* --------------- START Unpacking signal 46 ------------------
           *  startBit                = 376
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[47]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o47 = result;
            }
          }

          /* --------------- START Unpacking signal 47 ------------------
           *  startBit                = 384
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[48]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o48 = result;
            }
          }

          /* --------------- START Unpacking signal 48 ------------------
           *  startBit                = 392
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[49]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o49 = result;
            }
          }

          /* --------------- START Unpacking signal 49 ------------------
           *  startBit                = 400
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[50]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o50 = result;
            }
          }

          /* --------------- START Unpacking signal 50 ------------------
           *  startBit                = 408
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[51]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o51 = result;
            }
          }

          /* --------------- START Unpacking signal 51 ------------------
           *  startBit                = 416
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[52]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o52 = result;
            }
          }

          /* --------------- START Unpacking signal 52 ------------------
           *  startBit                = 424
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[53]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o53 = result;
            }
          }

          /* --------------- START Unpacking signal 53 ------------------
           *  startBit                = 432
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[54]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o54 = result;
            }
          }

          /* --------------- START Unpacking signal 54 ------------------
           *  startBit                = 440
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[55]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o55 = result;
            }
          }

          /* --------------- START Unpacking signal 55 ------------------
           *  startBit                = 448
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[56]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o56 = result;
            }
          }

          /* --------------- START Unpacking signal 56 ------------------
           *  startBit                = 456
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[57]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o57 = result;
            }
          }

          /* --------------- START Unpacking signal 57 ------------------
           *  startBit                = 464
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[58]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o58 = result;
            }
          }

          /* --------------- START Unpacking signal 58 ------------------
           *  startBit                = 472
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[59]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o59 = result;
            }
          }

          /* --------------- START Unpacking signal 59 ------------------
           *  startBit                = 480
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[60]);
                }

                unpackedValue = tempValue;
              }

              outValue = (int16_T) (unpackedValue);
            }

            {
              int16_T result = (int16_T) outValue;
              result = result + -40;
              CANRcvFcn_B.CANFDUnpack4_o60 = result;
            }
          }

          /* --------------- START Unpacking signal 60 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack4_o61 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S4>/Saturation1' incorporates:
   *  Constant: '<S4>/Constant5'
   *  Sum: '<S4>/Add1'
   */
  if ((uint8_T)(CANRcvFcn_B.CANFDUnpack4_o61 - 1) <= 1) {
    y = (uint8_T)(CANRcvFcn_B.CANFDUnpack4_o61 - 1);
  } else {
    y = 1;
  }

  /* SignalConversion generated from: '<S31>/ SFunction ' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   *  DataTypeConversion: '<S1>/Data Type Conversion10'
   *  DataTypeConversion: '<S1>/Data Type Conversion100'
   *  DataTypeConversion: '<S1>/Data Type Conversion101'
   *  DataTypeConversion: '<S1>/Data Type Conversion102'
   *  DataTypeConversion: '<S1>/Data Type Conversion103'
   *  DataTypeConversion: '<S1>/Data Type Conversion104'
   *  DataTypeConversion: '<S1>/Data Type Conversion105'
   *  DataTypeConversion: '<S1>/Data Type Conversion106'
   *  DataTypeConversion: '<S1>/Data Type Conversion107'
   *  DataTypeConversion: '<S1>/Data Type Conversion108'
   *  DataTypeConversion: '<S1>/Data Type Conversion109'
   *  DataTypeConversion: '<S1>/Data Type Conversion110'
   *  DataTypeConversion: '<S1>/Data Type Conversion111'
   *  DataTypeConversion: '<S1>/Data Type Conversion112'
   *  DataTypeConversion: '<S1>/Data Type Conversion113'
   *  DataTypeConversion: '<S1>/Data Type Conversion114'
   *  DataTypeConversion: '<S1>/Data Type Conversion115'
   *  DataTypeConversion: '<S1>/Data Type Conversion116'
   *  DataTypeConversion: '<S1>/Data Type Conversion117'
   *  DataTypeConversion: '<S1>/Data Type Conversion118'
   *  DataTypeConversion: '<S1>/Data Type Conversion119'
   *  DataTypeConversion: '<S1>/Data Type Conversion120'
   *  DataTypeConversion: '<S1>/Data Type Conversion121'
   *  DataTypeConversion: '<S1>/Data Type Conversion122'
   *  DataTypeConversion: '<S1>/Data Type Conversion123'
   *  DataTypeConversion: '<S1>/Data Type Conversion124'
   *  DataTypeConversion: '<S1>/Data Type Conversion125'
   *  DataTypeConversion: '<S1>/Data Type Conversion126'
   *  DataTypeConversion: '<S1>/Data Type Conversion127'
   *  DataTypeConversion: '<S1>/Data Type Conversion128'
   *  DataTypeConversion: '<S1>/Data Type Conversion129'
   *  DataTypeConversion: '<S1>/Data Type Conversion130'
   *  DataTypeConversion: '<S1>/Data Type Conversion131'
   *  DataTypeConversion: '<S1>/Data Type Conversion15'
   *  DataTypeConversion: '<S1>/Data Type Conversion51'
   *  DataTypeConversion: '<S1>/Data Type Conversion52'
   *  DataTypeConversion: '<S1>/Data Type Conversion53'
   *  DataTypeConversion: '<S1>/Data Type Conversion54'
   *  DataTypeConversion: '<S1>/Data Type Conversion55'
   *  DataTypeConversion: '<S1>/Data Type Conversion66'
   *  DataTypeConversion: '<S1>/Data Type Conversion81'
   *  DataTypeConversion: '<S1>/Data Type Conversion82'
   *  DataTypeConversion: '<S1>/Data Type Conversion83'
   *  DataTypeConversion: '<S1>/Data Type Conversion84'
   *  DataTypeConversion: '<S1>/Data Type Conversion85'
   *  DataTypeConversion: '<S1>/Data Type Conversion86'
   *  DataTypeConversion: '<S1>/Data Type Conversion87'
   *  DataTypeConversion: '<S1>/Data Type Conversion88'
   *  DataTypeConversion: '<S1>/Data Type Conversion89'
   *  DataTypeConversion: '<S1>/Data Type Conversion90'
   *  DataTypeConversion: '<S1>/Data Type Conversion91'
   *  DataTypeConversion: '<S1>/Data Type Conversion92'
   *  DataTypeConversion: '<S1>/Data Type Conversion93'
   *  DataTypeConversion: '<S1>/Data Type Conversion94'
   *  DataTypeConversion: '<S1>/Data Type Conversion95'
   *  DataTypeConversion: '<S1>/Data Type Conversion96'
   *  DataTypeConversion: '<S1>/Data Type Conversion97'
   *  DataTypeConversion: '<S1>/Data Type Conversion98'
   *  DataTypeConversion: '<S1>/Data Type Conversion99'
   *  MATLAB Function: '<S4>/MATLAB Function'
   */
  rtb_TmpSignalConversionAtSFun_a[0] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o1;
  rtb_TmpSignalConversionAtSFun_a[1] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o2;
  rtb_TmpSignalConversionAtSFun_a[2] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o3;
  rtb_TmpSignalConversionAtSFun_a[3] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o4;
  rtb_TmpSignalConversionAtSFun_a[4] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o5;
  rtb_TmpSignalConversionAtSFun_a[5] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o6;
  rtb_TmpSignalConversionAtSFun_a[6] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o7;
  rtb_TmpSignalConversionAtSFun_a[7] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o8;
  rtb_TmpSignalConversionAtSFun_a[8] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o9;
  rtb_TmpSignalConversionAtSFun_a[9] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o10;
  rtb_TmpSignalConversionAtSFun_a[10] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o11;
  rtb_TmpSignalConversionAtSFun_a[11] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o12;
  rtb_TmpSignalConversionAtSFun_a[12] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o13;
  rtb_TmpSignalConversionAtSFun_a[13] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o14;
  rtb_TmpSignalConversionAtSFun_a[14] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o15;
  rtb_TmpSignalConversionAtSFun_a[15] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o16;
  rtb_TmpSignalConversionAtSFun_a[16] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o17;
  rtb_TmpSignalConversionAtSFun_a[17] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o18;
  rtb_TmpSignalConversionAtSFun_a[18] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o19;
  rtb_TmpSignalConversionAtSFun_a[19] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o20;
  rtb_TmpSignalConversionAtSFun_a[20] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o21;
  rtb_TmpSignalConversionAtSFun_a[21] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o22;
  rtb_TmpSignalConversionAtSFun_a[22] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o23;
  rtb_TmpSignalConversionAtSFun_a[23] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o24;
  rtb_TmpSignalConversionAtSFun_a[24] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o25;
  rtb_TmpSignalConversionAtSFun_a[25] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o26;
  rtb_TmpSignalConversionAtSFun_a[26] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o27;
  rtb_TmpSignalConversionAtSFun_a[27] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o28;
  rtb_TmpSignalConversionAtSFun_a[28] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o29;
  rtb_TmpSignalConversionAtSFun_a[29] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o30;
  rtb_TmpSignalConversionAtSFun_a[30] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o31;
  rtb_TmpSignalConversionAtSFun_a[31] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o32;
  rtb_TmpSignalConversionAtSFun_a[32] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o33;
  rtb_TmpSignalConversionAtSFun_a[33] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o34;
  rtb_TmpSignalConversionAtSFun_a[34] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o35;
  rtb_TmpSignalConversionAtSFun_a[35] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o36;
  rtb_TmpSignalConversionAtSFun_a[36] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o37;
  rtb_TmpSignalConversionAtSFun_a[37] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o38;
  rtb_TmpSignalConversionAtSFun_a[38] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o39;
  rtb_TmpSignalConversionAtSFun_a[39] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o40;
  rtb_TmpSignalConversionAtSFun_a[40] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o41;
  rtb_TmpSignalConversionAtSFun_a[41] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o42;
  rtb_TmpSignalConversionAtSFun_a[42] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o43;
  rtb_TmpSignalConversionAtSFun_a[43] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o44;
  rtb_TmpSignalConversionAtSFun_a[44] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o45;
  rtb_TmpSignalConversionAtSFun_a[45] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o46;
  rtb_TmpSignalConversionAtSFun_a[46] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o47;
  rtb_TmpSignalConversionAtSFun_a[47] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o48;
  rtb_TmpSignalConversionAtSFun_a[48] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o49;
  rtb_TmpSignalConversionAtSFun_a[49] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o50;
  rtb_TmpSignalConversionAtSFun_a[50] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o51;
  rtb_TmpSignalConversionAtSFun_a[51] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o52;
  rtb_TmpSignalConversionAtSFun_a[52] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o53;
  rtb_TmpSignalConversionAtSFun_a[53] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o54;
  rtb_TmpSignalConversionAtSFun_a[54] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o55;
  rtb_TmpSignalConversionAtSFun_a[55] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o56;
  rtb_TmpSignalConversionAtSFun_a[56] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o57;
  rtb_TmpSignalConversionAtSFun_a[57] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o58;
  rtb_TmpSignalConversionAtSFun_a[58] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o59;
  rtb_TmpSignalConversionAtSFun_a[59] = (uint16_T)CANRcvFcn_B.CANFDUnpack4_o60;

  /* Saturate: '<S4>/Saturation1' incorporates:
   *  Constant: '<S4>/Constant5'
   *  Sum: '<S4>/Add1'
   */
  if ((uint8_T)(CANRcvFcn_B.CANFDUnpack4_o61 - 1) <= 1) {
    tmp = (uint8_T)(CANRcvFcn_B.CANFDUnpack4_o61 - 1);
  } else {
    tmp = 1;
  }

  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  Saturate: '<S4>/Saturation1'
   */
  tmp = (int32_T)((uint32_T)tmp * 60U + 1U);
  port_index = (uint32_T)y * 60U;
  rtb_DataTypeConversion27 = (uint16_T)(port_index + 1U);
  c = (uint16_T)(port_index + 60U);
  for (i = rtb_DataTypeConversion27; i <= c; i++) {
    CANRcvFcn_DW.tmp_h[i - 1] = rtb_TmpSignalConversionAtSFun_a[i - tmp];
  }

  /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack5' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */
  {
    /* S-Function (scanfdunpack): '<S1>/CAN FD Unpack5' */
    if ((64 == CANFDRcvMsg.Length) && (CANFDRcvMsg.ID != INVALID_CAN_ID) ) {
      if ((436277476 == CANFDRcvMsg.ID) && (1U == CANFDRcvMsg.Extended) ) {
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[2]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[1]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o1 = result;
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[4]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[3]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o2 = result;
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[6]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[5]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o3 = result;
            }
          }

          /* --------------- START Unpacking signal 3 ------------------
           *  startBit                = 64
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[8]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[7]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o4 = result;
            }
          }

          /* --------------- START Unpacking signal 4 ------------------
           *  startBit                = 80
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[10]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[9]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o5 = result;
            }
          }

          /* --------------- START Unpacking signal 5 ------------------
           *  startBit                = 96
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[12]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[11]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o6 = result;
            }
          }

          /* --------------- START Unpacking signal 6 ------------------
           *  startBit                = 112
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[14]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[13]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o7 = result;
            }
          }

          /* --------------- START Unpacking signal 7 ------------------
           *  startBit                = 128
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[16]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[15]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o8 = result;
            }
          }

          /* --------------- START Unpacking signal 8 ------------------
           *  startBit                = 144
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[18]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[17]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o9 = result;
            }
          }

          /* --------------- START Unpacking signal 9 ------------------
           *  startBit                = 160
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[20]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[19]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o10 = result;
            }
          }

          /* --------------- START Unpacking signal 10 ------------------
           *  startBit                = 176
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[22]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[21]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o11 = result;
            }
          }

          /* --------------- START Unpacking signal 11 ------------------
           *  startBit                = 192
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[24]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[23]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o12 = result;
            }
          }

          /* --------------- START Unpacking signal 12 ------------------
           *  startBit                = 208
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[26]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[25]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o13 = result;
            }
          }

          /* --------------- START Unpacking signal 13 ------------------
           *  startBit                = 224
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[28]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[27]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o14 = result;
            }
          }

          /* --------------- START Unpacking signal 14 ------------------
           *  startBit                = 240
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[30]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[29]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o15 = result;
            }
          }

          /* --------------- START Unpacking signal 15 ------------------
           *  startBit                = 256
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[32]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[31]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o16 = result;
            }
          }

          /* --------------- START Unpacking signal 16 ------------------
           *  startBit                = 272
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[34]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[33]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o17 = result;
            }
          }

          /* --------------- START Unpacking signal 17 ------------------
           *  startBit                = 288
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[36]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[35]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o18 = result;
            }
          }

          /* --------------- START Unpacking signal 18 ------------------
           *  startBit                = 304
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[38]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[37]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o19 = result;
            }
          }

          /* --------------- START Unpacking signal 19 ------------------
           *  startBit                = 320
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[40]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[39]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o20 = result;
            }
          }

          /* --------------- START Unpacking signal 20 ------------------
           *  startBit                = 336
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[42]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[41]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o21 = result;
            }
          }

          /* --------------- START Unpacking signal 21 ------------------
           *  startBit                = 352
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[44]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[43]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o22 = result;
            }
          }

          /* --------------- START Unpacking signal 22 ------------------
           *  startBit                = 368
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[46]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[45]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o23 = result;
            }
          }

          /* --------------- START Unpacking signal 23 ------------------
           *  startBit                = 384
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[48]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[47]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o24 = result;
            }
          }

          /* --------------- START Unpacking signal 24 ------------------
           *  startBit                = 400
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[50]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[49]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o25 = result;
            }
          }

          /* --------------- START Unpacking signal 25 ------------------
           *  startBit                = 416
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[52]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[51]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o26 = result;
            }
          }

          /* --------------- START Unpacking signal 26 ------------------
           *  startBit                = 432
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[54]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[53]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o27 = result;
            }
          }

          /* --------------- START Unpacking signal 27 ------------------
           *  startBit                = 448
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[56]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[55]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o28 = result;
            }
          }

          /* --------------- START Unpacking signal 28 ------------------
           *  startBit                = 464
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[58]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[57]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o29 = result;
            }
          }

          /* --------------- START Unpacking signal 29 ------------------
           *  startBit                = 480
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
                  tempValue = tempValue | (uint16_T)(CANFDRcvMsg.Data[60]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (CANFDRcvMsg.Data[59]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint16_T) (unpackedValue);
            }

            {
              uint16_T result = (uint16_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o30 = result;
            }
          }

          /* --------------- START Unpacking signal 30 ------------------
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
                  tempValue = tempValue | (uint8_T)(CANFDRcvMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.CANFDUnpack5_o31 = result;
            }
          }
        }
      }
    }
  }

  /* Saturate: '<S5>/Saturation2' incorporates:
   *  Constant: '<S5>/Constant10'
   *  Sum: '<S5>/Add4'
   */
  if ((uint8_T)(CANRcvFcn_B.CANFDUnpack5_o31 - 1) <= 7) {
    rtb_Saturation2 = (uint8_T)(CANRcvFcn_B.CANFDUnpack5_o31 - 1);
  } else {
    rtb_Saturation2 = 7U;
  }

  /* End of Saturate: '<S5>/Saturation2' */

  /* SignalConversion generated from: '<S32>/ SFunction ' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion132'
   *  DataTypeConversion: '<S1>/Data Type Conversion133'
   *  DataTypeConversion: '<S1>/Data Type Conversion134'
   *  DataTypeConversion: '<S1>/Data Type Conversion135'
   *  DataTypeConversion: '<S1>/Data Type Conversion136'
   *  DataTypeConversion: '<S1>/Data Type Conversion137'
   *  DataTypeConversion: '<S1>/Data Type Conversion138'
   *  DataTypeConversion: '<S1>/Data Type Conversion139'
   *  DataTypeConversion: '<S1>/Data Type Conversion140'
   *  DataTypeConversion: '<S1>/Data Type Conversion141'
   *  DataTypeConversion: '<S1>/Data Type Conversion142'
   *  DataTypeConversion: '<S1>/Data Type Conversion143'
   *  DataTypeConversion: '<S1>/Data Type Conversion144'
   *  DataTypeConversion: '<S1>/Data Type Conversion145'
   *  DataTypeConversion: '<S1>/Data Type Conversion146'
   *  DataTypeConversion: '<S1>/Data Type Conversion147'
   *  DataTypeConversion: '<S1>/Data Type Conversion148'
   *  DataTypeConversion: '<S1>/Data Type Conversion149'
   *  DataTypeConversion: '<S1>/Data Type Conversion150'
   *  DataTypeConversion: '<S1>/Data Type Conversion151'
   *  DataTypeConversion: '<S1>/Data Type Conversion152'
   *  DataTypeConversion: '<S1>/Data Type Conversion153'
   *  DataTypeConversion: '<S1>/Data Type Conversion155'
   *  DataTypeConversion: '<S1>/Data Type Conversion156'
   *  DataTypeConversion: '<S1>/Data Type Conversion157'
   *  DataTypeConversion: '<S1>/Data Type Conversion158'
   *  DataTypeConversion: '<S1>/Data Type Conversion43'
   *  DataTypeConversion: '<S1>/Data Type Conversion48'
   *  DataTypeConversion: '<S1>/Data Type Conversion49'
   *  DataTypeConversion: '<S1>/Data Type Conversion9'
   *  Gain: '<S1>/Gain10'
   *  Gain: '<S1>/Gain13'
   *  Gain: '<S1>/Gain15'
   *  Gain: '<S1>/Gain24'
   *  Gain: '<S1>/Gain34'
   *  Gain: '<S1>/Gain35'
   *  Gain: '<S1>/Gain36'
   *  Gain: '<S1>/Gain37'
   *  Gain: '<S1>/Gain38'
   *  Gain: '<S1>/Gain39'
   *  Gain: '<S1>/Gain40'
   *  Gain: '<S1>/Gain41'
   *  Gain: '<S1>/Gain42'
   *  Gain: '<S1>/Gain43'
   *  Gain: '<S1>/Gain44'
   *  Gain: '<S1>/Gain45'
   *  Gain: '<S1>/Gain46'
   *  Gain: '<S1>/Gain47'
   *  Gain: '<S1>/Gain48'
   *  Gain: '<S1>/Gain49'
   *  Gain: '<S1>/Gain5'
   *  Gain: '<S1>/Gain50'
   *  Gain: '<S1>/Gain51'
   *  Gain: '<S1>/Gain52'
   *  Gain: '<S1>/Gain53'
   *  Gain: '<S1>/Gain55'
   *  Gain: '<S1>/Gain56'
   *  Gain: '<S1>/Gain57'
   *  Gain: '<S1>/Gain58'
   *  Gain: '<S1>/Gain59'
   *  MATLAB Function: '<S5>/MATLAB Function2'
   */
  rtb_TmpSignalConversionAtSFu_kh[0] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o1) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[1] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o2) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[2] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o3) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[3] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o4) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[4] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o5) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[5] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o6) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[6] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o7) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[7] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o8) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[8] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o9) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[9] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o10) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[10] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o11) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[11] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o12) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[12] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o13) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[13] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o14) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[14] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o15) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[15] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o16) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[16] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o17) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[17] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o18) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[18] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o19) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[19] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o20) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[20] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o21) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[21] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o22) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[22] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o23) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[23] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o24) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[24] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o25) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[25] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o26) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[26] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o27) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[27] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o28) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[28] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o29) >> 19);
  rtb_TmpSignalConversionAtSFu_kh[29] = (uint16_T)((52429U *
    CANRcvFcn_B.CANFDUnpack5_o30) >> 19);

  /* MATLAB Function: '<S5>/MATLAB Function2' */
  tmp = (int32_T)(rtb_Saturation2 * 30U + 1U);
  b = (uint8_T)((uint8_T)(rtb_Saturation2 * 30) + 1);
  rtb_Saturation2 = (uint8_T)((uint8_T)(rtb_Saturation2 * 30) + 30);
  for (i_0 = b; i_0 <= rtb_Saturation2; i_0++) {
    CANRcvFcn_DW.tmp[i_0 - 1] = rtb_TmpSignalConversionAtSFu_kh[i_0 - (uint8_T)
      tmp];
  }

  /* CFunction: '<S12>/C Function11' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion32'
   */
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967294U) | CANRcvFcn_ConstB.DataTypeConversion27);
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967293U) | CANRcvFcn_ConstB.DataTypeConversion28 << 1);
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967291U) | CANRcvFcn_ConstB.DataTypeConversion29 << 2);
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967287U) | CANRcvFcn_ConstB.DataTypeConversion30 << 3);
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967279U) | (CANRcvFcn_B.CANFDUnpack3_o29 != 0) << 4);
  CANRcvFcn_B.CFunction11 = (uint16_T)((int32_T)(CANRcvFcn_B.CFunction11 &
    4294967263U) | CANRcvFcn_ConstB.DataTypeConversion38 << 5);

  /* DataTypeConversion: '<S1>/Data Type Conversion27' incorporates:
   *  Gain: '<S1>/Gain9'
   */
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack1_o3), 65536.0F);
  rtb_DataTypeConversion27 = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-u : (int32_T)(uint16_T)u);

  /* CFunction: '<S1>/U32_to_F32' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion40'
   */
  CANRcvFcn_DW.U32_to_F32_float_value = rtb_DataTypeConversion29 /10.0f;// 整型转浮点

  // 方法1：使用 memcpy（避免指针别名问题，推荐）
  memcpy(&CANRcvFcn_DW.U32_to_F32_float_bits,
         &CANRcvFcn_DW.U32_to_F32_float_value, sizeof(float));

  // 方法2：直接指针转换（可能有严格别名问题，不推荐）
  // float_bits = *(uint32_t *)&float_value;

  // 提取字节（大端序 DCBA）
  CANRcvFcn_DW.U32_to_F32_byteD = (CANRcvFcn_DW.U32_to_F32_float_bits >> 24) &
    0xFF;                              // 最高有效字节
  CANRcvFcn_DW.U32_to_F32_byteC = (CANRcvFcn_DW.U32_to_F32_float_bits >> 16) &
    0xFF;
  CANRcvFcn_DW.U32_to_F32_byteB = (CANRcvFcn_DW.U32_to_F32_float_bits >> 8) &
    0xFF;
  CANRcvFcn_DW.U32_to_F32_byteA = CANRcvFcn_DW.U32_to_F32_float_bits & 0xFF;// 最低有效字节

  // 组合成两个 16 位寄存器
  CANRcvFcn_B.BCU_V4_L = (CANRcvFcn_DW.U32_to_F32_byteD << 8) |
    CANRcvFcn_DW.U32_to_F32_byteC;     // DC 寄存器
  CANRcvFcn_B.BCU_V4_H = (CANRcvFcn_DW.U32_to_F32_byteB << 8) |
    CANRcvFcn_DW.U32_to_F32_byteA;     // BA 寄存器

  /* CFunction: '<S1>/U32_to_F1' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion33'
   */
  CANRcvFcn_DW.U32_to_F1_float_value = rtb_DataTypeConversion27/10.0f;// 整型转浮点

  // 方法1：使用 memcpy（避免指针别名问题，推荐）
  memcpy(&CANRcvFcn_DW.U32_to_F1_float_bits, &CANRcvFcn_DW.U32_to_F1_float_value,
         sizeof(float));

  // 方法2：直接指针转换（可能有严格别名问题，不推荐）
  // float_bits = *(uint32_t *)&float_value;

  // 提取字节（大端序 DCBA）
  CANRcvFcn_DW.U32_to_F1_byteD = (CANRcvFcn_DW.U32_to_F1_float_bits >> 24) &
    0xFF;                              // 最高有效字节
  CANRcvFcn_DW.U32_to_F1_byteC = (CANRcvFcn_DW.U32_to_F1_float_bits >> 16) &
    0xFF;
  CANRcvFcn_DW.U32_to_F1_byteB = (CANRcvFcn_DW.U32_to_F1_float_bits >> 8) & 0xFF;
  CANRcvFcn_DW.U32_to_F1_byteA = CANRcvFcn_DW.U32_to_F1_float_bits & 0xFF;// 最低有效字节

  // 组合成两个 16 位寄存器
  CANRcvFcn_B.BCU_Curr2_L = (CANRcvFcn_DW.U32_to_F1_byteD << 8) |
    CANRcvFcn_DW.U32_to_F1_byteC;      // DC 寄存器
  CANRcvFcn_B.BCU_Curr2_H = (CANRcvFcn_DW.U32_to_F1_byteB << 8) |
    CANRcvFcn_DW.U32_to_F1_byteA;      // BA 寄存器

  /* S-Function (scanunpack): '<S3>/0x180110E4' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E4' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985169 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E4_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E4_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E2' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E2' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985170 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E2_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E2_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E1' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E1' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985171 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E1_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E1_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E5' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E5' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985172 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E5_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E5_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E3' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E3' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985173 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E3_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E3_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E7' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E7' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985174 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E7_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E7_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E6' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E6' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985175 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E6_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E6_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E9' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E9' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985176 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E9_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E9_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E8' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E8' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985177 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E8_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E8_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E11' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E11' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985178 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E11_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E11_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E10' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E10' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985179 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E10_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E10_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E13' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E13' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985180 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E13_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E13_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E12' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E12' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985181 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E12_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E12_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E15' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E15' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985182 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E15_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E15_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E14' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E14' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402985183 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[1]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E14_o1 = result;
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
                  tempValue = tempValue | (uint8_T)(CANMsg.Data[0]);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint8_T) (unpackedValue);
            }

            {
              uint8_T result = (uint8_T) outValue;
              CANRcvFcn_B.ux180110E14_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E16' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E16' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919633 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E16_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E16_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E17' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E17' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919634 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E17_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E17_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E18' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E18' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919635 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E18_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E18_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E19' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E19' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919636 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E19_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E19_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E20' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E20' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919637 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E20_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E20_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E21' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E21' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919638 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E21_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E21_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E22' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E22' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919639 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E22_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E22_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E23' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E23' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919640 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E23_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E23_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E24' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E24' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919641 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E24_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E24_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E25' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E25' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919642 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E25_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E25_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E26' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E26' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919643 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E26_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E26_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E27' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E27' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919644 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E27_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E27_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E28' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E28' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919645 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E28_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E28_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E29' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E29' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919646 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E29_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E29_o2 = result;
            }
          }
        }
      }
    }
  }

  /* S-Function (scanunpack): '<S3>/0x180110E30' incorporates:
   *  Inport: '<Root>/CANMsg'
   */
  {
    /* S-Function (scanunpack): '<S3>/0x180110E30' */
    if ((8 == CANMsg.Length) && (CANMsg.ID != INVALID_CAN_ID) ) {
      if ((402919647 == CANMsg.ID) && (1U == CANMsg.Extended) ) {
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[3]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[2]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[1]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[0]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E30_o1 = result;
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
                  tempValue = tempValue | (uint32_T)(CANMsg.Data[7]);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[6]) <<
                    8);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[5]) <<
                    16);
                  tempValue = tempValue | (uint32_T)((uint32_T)(CANMsg.Data[4]) <<
                    24);
                }

                unpackedValue = tempValue;
              }

              outValue = (uint32_T) (unpackedValue);
            }

            {
              uint32_T result = (uint32_T) outValue;
              CANRcvFcn_B.ux180110E30_o2 = result;
            }
          }
        }
      }
    }
  }

  /* SignalConversion generated from: '<S2>/ SFunction ' incorporates:
   *  ArithShift: '<S1>/Shift Arithmetic'
   *  ArithShift: '<S1>/Shift Arithmetic1'
   *  CFunction: '<S1>/C Function10'
   *  CFunction: '<S1>/C Function14'
   *  CFunction: '<S1>/C Function2'
   *  CFunction: '<S1>/C Function3'
   *  CFunction: '<S1>/C Function4'
   *  CFunction: '<S1>/C Function5'
   *  CFunction: '<S1>/C Function6'
   *  CFunction: '<S1>/C Function7'
   *  CFunction: '<S1>/C Function8'
   *  CFunction: '<S1>/C Function9'
   *  Chart: '<Root>/Chart1'
   *  Constant: '<S30>/Constant14'
   *  Constant: '<S6>/Constant24'
   *  Constant: '<S6>/Constant27'
   *  Constant: '<S6>/Constant28'
   *  Constant: '<S6>/Constant8'
   *  DataTypeConversion: '<S1>/Data Type Conversion19'
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   *  DataTypeConversion: '<S1>/Data Type Conversion21'
   *  DataTypeConversion: '<S1>/Data Type Conversion3'
   *  DataTypeConversion: '<S1>/Data Type Conversion31'
   *  DataTypeConversion: '<S1>/Data Type Conversion36'
   *  DataTypeConversion: '<S1>/Data Type Conversion4'
   *  DataTypeConversion: '<S1>/Data Type Conversion5'
   *  DataTypeConversion: '<S1>/Data Type Conversion57'
   *  DataTypeConversion: '<S1>/Data Type Conversion6'
   *  DataTypeConversion: '<S1>/Data Type Conversion7'
   *  DataTypeConversion: '<S30>/Data Type Conversion66'
   *  Gain: '<S1>/Gain16'
   *  Gain: '<S1>/Gain19'
   *  Gain: '<S1>/Gain20'
   *  Gain: '<S1>/Gain23'
   *  Gain: '<S1>/Gain28'
   *  Gain: '<S1>/Gain29'
   *  Gain: '<S30>/Gain24'
   *  S-Function (sfix_bitop): '<S1>/Bitwise AND'
   *  Sum: '<S30>/Add7'
   *  Sum: '<S30>/Subtract4'
   */
  rtb_TmpSignalConversionAtSFunct[0] = BCU_SystemWorkMode;
  rtb_TmpSignalConversionAtSFunct[1] = 0U;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack1_o4), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[2] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack1_o5), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[3] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[4] = (uint16_T)(CANRcvFcn_B.CANFDUnpack1_o14 <<
    2 | CANRcvFcn_B.CANFDUnpack1_o15 | CANRcvFcn_B.CANFDUnpack1_o16 << 4);
  rtb_TmpSignalConversionAtSFunct[5] = BCU_SystemStatus;
  rtb_TmpSignalConversionAtSFunct[6] = 0U;
  rtb_TmpSignalConversionAtSFunct[7] = 0U;
  rtb_TmpSignalConversionAtSFunct[8] = 0U;
  rtb_TmpSignalConversionAtSFunct[9] = CFunction_o1;
  rtb_TmpSignalConversionAtSFunct[10] = CFunction_o2;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o3), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[11] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[12] = CFunction1_o1;
  rtb_TmpSignalConversionAtSFunct[13] = CFunction1_o2;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o6), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[14] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[15] = CANRcvFcn_B.CANFDUnpack_o16;
  rtb_TmpSignalConversionAtSFunct[16] = CANRcvFcn_B.CANFDUnpack_o17;
  rtb_TmpSignalConversionAtSFunct[17] = CANRcvFcn_B.CANFDUnpack_o18;
  rtb_TmpSignalConversionAtSFunct[18] = CANRcvFcn_B.CANFDUnpack_o19;
  rtb_TmpSignalConversionAtSFunct[19] = CANRcvFcn_B.CANFDUnpack_o20;
  rtb_TmpSignalConversionAtSFunct[20] = CANRcvFcn_B.CANFDUnpack_o21;
  rtb_TmpSignalConversionAtSFunct[21] = CANRcvFcn_B.CANFDUnpack_o22;
  rtb_TmpSignalConversionAtSFunct[22] = CANRcvFcn_B.CANFDUnpack_o23;
  rtb_TmpSignalConversionAtSFunct[23] = CANRcvFcn_B.CANFDUnpack_o24;
  rtb_TmpSignalConversionAtSFunct[24] = CANRcvFcn_B.CANFDUnpack_o25;
  rtb_TmpSignalConversionAtSFunct[25] = CANRcvFcn_B.CANFDUnpack_o26;
  rtb_TmpSignalConversionAtSFunct[26] = CANRcvFcn_B.CANFDUnpack_o27;
  rtb_TmpSignalConversionAtSFunct[27] = CANRcvFcn_B.CANFDUnpack_o28;
  rtb_TmpSignalConversionAtSFunct[28] = CANRcvFcn_B.CANFDUnpack_o29;
  rtb_TmpSignalConversionAtSFunct[29] = CANRcvFcn_B.CANFDUnpack_o30;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o4), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[30] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[31] = (uint16_T)(data_index & 65535U);
  rtb_TmpSignalConversionAtSFunct[32] = (uint16_T)(data_index >> 16);
  rtb_TmpSignalConversionAtSFunct[33] = CANRcvFcn_B.CANFDUnpack_o31;
  rtb_TmpSignalConversionAtSFunct[34] = CANRcvFcn_B.CANFDUnpack_o32;
  rtb_TmpSignalConversionAtSFunct[35] = CANRcvFcn_B.CANFDUnpack_o33;
  rtb_TmpSignalConversionAtSFunct[36] = CANRcvFcn_B.CANFDUnpack_o34;
  rtb_TmpSignalConversionAtSFunct[37] = CANRcvFcn_B.CANFDUnpack_o35;
  rtb_TmpSignalConversionAtSFunct[38] = CANRcvFcn_B.CANFDUnpack_o36;
  rtb_TmpSignalConversionAtSFunct[39] = CANRcvFcn_B.CANFDUnpack_o37;
  rtb_TmpSignalConversionAtSFunct[40] = CANRcvFcn_B.CANFDUnpack_o38;
  rtb_TmpSignalConversionAtSFunct[41] = (uint16_T)(BCU_FaultInfoLv1H >> 16);
  rtb_TmpSignalConversionAtSFunct[42] = (uint16_T)(BCU_FaultInfoLv1H & 65535U);
  rtb_TmpSignalConversionAtSFunct[43] = (uint16_T)(BCU_FaultInfoLv1L >> 16);
  rtb_TmpSignalConversionAtSFunct[44] = (uint16_T)(BCU_FaultInfoLv1L & 65535U);
  rtb_TmpSignalConversionAtSFunct[45] = (uint16_T)(BCU_FaultInfoLv2H >> 16);
  rtb_TmpSignalConversionAtSFunct[46] = (uint16_T)(BCU_FaultInfoLv2H & 65535U);
  rtb_TmpSignalConversionAtSFunct[47] = (uint16_T)(BCU_FaultInfoLv2L >> 16);
  rtb_TmpSignalConversionAtSFunct[48] = (uint16_T)(BCU_FaultInfoLv2L & 65535U);
  rtb_TmpSignalConversionAtSFunct[49] = (uint16_T)(BCU_FaultInfoLv3H >> 16);
  rtb_TmpSignalConversionAtSFunct[50] = (uint16_T)(BCU_FaultInfoLv3H & 65535U);
  rtb_TmpSignalConversionAtSFunct[51] = (uint16_T)(BCU_FaultInfoLv3L >> 16);
  rtb_TmpSignalConversionAtSFunct[52] = (uint16_T)(BCU_FaultInfoLv3L & 65535U);
  rtb_TmpSignalConversionAtSFunct[53] = (uint16_T)(BCU_FaultInfoLv4H >> 16);
  rtb_TmpSignalConversionAtSFunct[54] = (uint16_T)(BCU_FaultInfoLv4H & 65535U);
  rtb_TmpSignalConversionAtSFunct[55] = (uint16_T)(BCU_FaultInfoLv4L >> 16);
  rtb_TmpSignalConversionAtSFunct[56] = CANRcvFcn_B.CANFDUnpack3_o10;
  rtb_TmpSignalConversionAtSFunct[57] = CANRcvFcn_B.CANFDUnpack3_o8;
  rtb_TmpSignalConversionAtSFunct[58] = CANRcvFcn_B.CANFDUnpack3_o9;
  rtb_TmpSignalConversionAtSFunct[59] = BCU_SOC;
  u = 0.00999999F * (real32_T)CANRcvFcn_B.CANFDUnpack1_o20;
  if (u >= 0.5F) {
    tmp = (int32_T)floorf(u + 0.5F);
  } else {
    tmp = 0;
  }

  rtb_TmpSignalConversionAtSFunct[60] = (uint16_T)fmodf((real32_T)tmp, 65536.0F);
  rtb_TmpSignalConversionAtSFunct[61] = (uint16_T)((CANRcvFcn_B.CANFDUnpack2_o1 <<
    8) + CANRcvFcn_B.CANFDUnpack2_o2);
  rtb_TmpSignalConversionAtSFunct[62] = 0U;
  rtb_TmpSignalConversionAtSFunct[63] = (uint16_T)((((uint32_T)(uint16_T)
    (CANRcvFcn_B.CANFDUnpack2_o7 - 1) << 15) + ((uint32_T)
    CANRcvFcn_B.CANFDUnpack2_o8 << 11)) >> 11);
  rtb_TmpSignalConversionAtSFunct[64] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o6;
  rtb_TmpSignalConversionAtSFunct[65] = CANRcvFcn_B.CANFDUnpack2_o9;
  rtb_TmpSignalConversionAtSFunct[66] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o10;
  rtb_TmpSignalConversionAtSFunct[67] = 0U;

  /* Saturate: '<S11>/Saturation3' */
  if (CANRcvFcn_B.CANFDUnpack2_o14 > 16) {
    b = 16U;
  } else if (CANRcvFcn_B.CANFDUnpack2_o14 < 1) {
    b = 1U;
  } else {
    b = CANRcvFcn_B.CANFDUnpack2_o14;
  }

  /* SignalConversion generated from: '<S2>/ SFunction ' incorporates:
   *  Chart: '<Root>/Chart1'
   *  Constant: '<S11>/Constant7'
   *  DataTypeConversion: '<S11>/Data Type Conversion44'
   *  DataTypeConversion: '<S1>/Data Type Conversion58'
   *  Gain: '<S11>/Gain11'
   *  Saturate: '<S11>/Saturation3'
   *  Sum: '<S11>/Add2'
   *  Sum: '<S11>/Subtract'
   */
  rtb_TmpSignalConversionAtSFunct[68] = (uint16_T)((int32_T)((uint32_T)((b - 1) <<
    7) + ((uint32_T)CANRcvFcn_B.CANFDUnpack2_o15 << 3)) >> 3);
  rtb_TmpSignalConversionAtSFunct[69] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o20;

  /* Saturate: '<S10>/Saturation4' */
  if (CANRcvFcn_B.CANFDUnpack2_o21 > 16) {
    b = 16U;
  } else if (CANRcvFcn_B.CANFDUnpack2_o21 < 1) {
    b = 1U;
  } else {
    b = CANRcvFcn_B.CANFDUnpack2_o21;
  }

  /* SignalConversion generated from: '<S2>/ SFunction ' incorporates:
   *  Chart: '<Root>/Chart1'
   *  Constant: '<S10>/Constant8'
   *  Constant: '<S6>/Constant3'
   *  Constant: '<S6>/Constant7'
   *  Constant: '<S6>/Constant9'
   *  DataTypeConversion: '<S10>/Data Type Conversion45'
   *  DataTypeConversion: '<S1>/Data Type Conversion37'
   *  DataTypeConversion: '<S1>/Data Type Conversion39'
   *  DataTypeConversion: '<S1>/Data Type Conversion46'
   *  DataTypeConversion: '<S1>/Data Type Conversion59'
   *  DataTypeConversion: '<S1>/Data Type Conversion60'
   *  DataTypeConversion: '<S1>/Data Type Conversion61'
   *  Gain: '<S10>/Gain12'
   *  Gain: '<S1>/Gain14'
   *  Gain: '<S1>/Gain6'
   *  Gain: '<S1>/Gain7'
   *  Saturate: '<S10>/Saturation4'
   *  Sum: '<S10>/Add3'
   *  Sum: '<S10>/Subtract1'
   */
  rtb_TmpSignalConversionAtSFunct[70] = (uint16_T)((int32_T)((uint32_T)((b - 1) <<
    7) + ((uint32_T)CANRcvFcn_B.CANFDUnpack2_o22 << 3)) >> 3);
  rtb_TmpSignalConversionAtSFunct[71] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o25;
  rtb_TmpSignalConversionAtSFunct[72] = CANRcvFcn_B.CANFDUnpack2_o16;
  rtb_TmpSignalConversionAtSFunct[73] = CANRcvFcn_B.CANFDUnpack2_o17;
  rtb_TmpSignalConversionAtSFunct[74] = CANRcvFcn_B.CANFDUnpack2_o18;
  rtb_TmpSignalConversionAtSFunct[75] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o19;
  rtb_TmpSignalConversionAtSFunct[76] = CANRcvFcn_B.CANFDUnpack2_o23;
  rtb_TmpSignalConversionAtSFunct[77] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o24;
  rtb_TmpSignalConversionAtSFunct[78] = CANRcvFcn_ConstB.DataTypeConversion67;
  rtb_TmpSignalConversionAtSFunct[79] = 0U;
  rtb_TmpSignalConversionAtSFunct[80] = CANRcvFcn_ConstB.DataTypeConversion68;
  rtb_TmpSignalConversionAtSFunct[81] = 0U;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack1_o2), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[82] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  u = 10.0F * CANRcvFcn_B.CANFDUnpack1_o22;
  v = fabsf(u);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u = floorf(u + 0.5F);
    } else {
      u = 0.0F;
    }
  }

  u = fmodf(u, 65536.0F);
  rtb_TmpSignalConversionAtSFunct[83] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  u = 10.0F * CANRcvFcn_B.CANFDUnpack1_o23;
  v = fabsf(u);
  if (v < 8.388608E+6F) {
    if (v >= 0.5F) {
      u = floorf(u + 0.5F);
    } else {
      u = 0.0F;
    }
  }

  u = fmodf(u, 65536.0F);
  rtb_TmpSignalConversionAtSFunct[84] = (uint16_T)(u < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[85] = rtb_DataTypeConversion29;
  rtb_TmpSignalConversionAtSFunct[86] = CANRcvFcn_B.CANFDUnpack2_o28;
  rtb_TmpSignalConversionAtSFunct[87] = CANRcvFcn_B.CANFDUnpack2_o31;
  rtb_TmpSignalConversionAtSFunct[88] = CANRcvFcn_B.CANFDUnpack2_o29;
  rtb_TmpSignalConversionAtSFunct[89] = 0U;

  /* Saturate: '<S9>/Saturation7' */
  if (CANRcvFcn_B.CANFDUnpack2_o27 > 16) {
    b = 16U;
  } else if (CANRcvFcn_B.CANFDUnpack2_o27 < 1) {
    b = 1U;
  } else {
    b = CANRcvFcn_B.CANFDUnpack2_o27;
  }

  /* SignalConversion generated from: '<S2>/ SFunction ' incorporates:
   *  Bias: '<S1>/Bias'
   *  CFunction: '<S1>/C Function10'
   *  CFunction: '<S1>/C Function11'
   *  CFunction: '<S1>/C Function12'
   *  CFunction: '<S1>/C Function13'
   *  CFunction: '<S1>/C Function15'
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
   *  Constant: '<S7>/Constant13'
   *  Constant: '<S8>/Constant12'
   *  Constant: '<S9>/Constant17'
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  DataTypeConversion: '<S1>/Data Type Conversion11'
   *  DataTypeConversion: '<S1>/Data Type Conversion16'
   *  DataTypeConversion: '<S1>/Data Type Conversion17'
   *  DataTypeConversion: '<S1>/Data Type Conversion23'
   *  DataTypeConversion: '<S1>/Data Type Conversion24'
   *  DataTypeConversion: '<S1>/Data Type Conversion28'
   *  DataTypeConversion: '<S1>/Data Type Conversion47'
   *  DataTypeConversion: '<S1>/Data Type Conversion50'
   *  DataTypeConversion: '<S1>/Data Type Conversion56'
   *  DataTypeConversion: '<S1>/Data Type Conversion64'
   *  DataTypeConversion: '<S1>/Data Type Conversion71'
   *  DataTypeConversion: '<S1>/Data Type Conversion8'
   *  DataTypeConversion: '<S1>/Data Type Conversion80'
   *  DataTypeConversion: '<S7>/Data Type Conversion42'
   *  DataTypeConversion: '<S8>/Data Type Conversion41'
   *  DataTypeConversion: '<S9>/Data Type Conversion69'
   *  Gain: '<S1>/Gain'
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Gain: '<S1>/Gain3'
   *  Gain: '<S1>/Gain32'
   *  Gain: '<S1>/Gain33'
   *  Gain: '<S1>/Gain4'
   *  Gain: '<S7>/Gain9'
   *  Gain: '<S8>/Gain5'
   *  Gain: '<S9>/Gain27'
   *  MATLAB Function: '<S4>/MATLAB Function'
   *  MATLAB Function: '<S5>/MATLAB Function2'
   *  Saturate: '<S9>/Saturation7'
   *  Sum: '<S7>/Add6'
   *  Sum: '<S7>/Subtract3'
   *  Sum: '<S8>/Add5'
   *  Sum: '<S8>/Subtract2'
   *  Sum: '<S9>/Add10'
   *  Sum: '<S9>/Subtract7'
   */
  rtb_TmpSignalConversionAtSFunct[90] = (uint16_T)((int32_T)((uint32_T)((b - 1) <<
    7) + ((uint32_T)CANRcvFcn_B.CANFDUnpack2_o30 << 3)) >> 3);
  rtb_TmpSignalConversionAtSFunct[91] = CANRcvFcn_B.CANFDUnpack2_o38;
  rtb_TmpSignalConversionAtSFunct[92] = CANRcvFcn_B.CANFDUnpack2_o42;
  rtb_TmpSignalConversionAtSFunct[93] = (uint16_T)((int32_T)((uint32_T)((uint8_T)
    (CANRcvFcn_B.CANFDUnpack2_o39 - 1) << 7) + ((uint32_T)
    CANRcvFcn_B.CANFDUnpack2_o40 << 3)) >> 3);
  rtb_TmpSignalConversionAtSFunct[94] = CANRcvFcn_B.CANFDUnpack2_o33;
  rtb_TmpSignalConversionAtSFunct[95] = CANRcvFcn_B.CANFDUnpack2_o34;
  rtb_TmpSignalConversionAtSFunct[96] = CANRcvFcn_B.CANFDUnpack2_o36;
  rtb_TmpSignalConversionAtSFunct[97] = CANRcvFcn_B.CANFDUnpack2_o37;
  rtb_TmpSignalConversionAtSFunct[98] = CANRcvFcn_B.CANFDUnpack2_o41;
  rtb_TmpSignalConversionAtSFunct[99] = CANRcvFcn_B.CANFDUnpack2_o43;
  rtb_TmpSignalConversionAtSFunct[100] = CANRcvFcn_B.CANFDUnpack2_o44;
  rtb_TmpSignalConversionAtSFunct[101] = CANRcvFcn_B.CANFDUnpack2_o45;
  rtb_TmpSignalConversionAtSFunct[102] = CANRcvFcn_B.CANFDUnpack2_o46;
  rtb_TmpSignalConversionAtSFunct[103] = (uint16_T)(BCU_FaultInfoLv4L & 65535U);
  memcpy(&rtb_TmpSignalConversionAtSFunct[104], &CANRcvFcn_DW.tmp_h[0], 120U *
         sizeof(uint16_T));
  memcpy(&rtb_TmpSignalConversionAtSFunct[224], &CANRcvFcn_DW.tmp[0], 240U *
         sizeof(uint16_T));
  rtb_TmpSignalConversionAtSFunct[464] = (uint16_T)((int32_T)((uint32_T)
    ((uint8_T)(CANRcvFcn_B.CANFDUnpack2_o32 - 1) << 7) + ((uint32_T)
    CANRcvFcn_B.CANFDUnpack2_o35 << 3)) >> 3);
  rtb_TmpSignalConversionAtSFunct[465] = (uint16_T)CANRcvFcn_B.CANFDUnpack3_o19;
  rtb_TmpSignalConversionAtSFunct[466] = CANRcvFcn_B.CANFDUnpack3_o20;
  rtb_TmpSignalConversionAtSFunct[467] = (uint16_T)CANRcvFcn_B.CANFDUnpack3_o31;
  rtb_TmpSignalConversionAtSFunct[468] = (uint16_T)CANRcvFcn_B.CANFDUnpack3_o24;
  rtb_TmpSignalConversionAtSFunct[469] = CANRcvFcn_B.CANFDUnpack3_o37;
  rtb_TmpSignalConversionAtSFunct[470] = (uint16_T)(10 *
    CANRcvFcn_B.CANFDUnpack3_o38);
  rtb_TmpSignalConversionAtSFunct[471] = (uint16_T)(10 *
    CANRcvFcn_B.CANFDUnpack3_o39);
  rtb_TmpSignalConversionAtSFunct[472] = (uint16_T)(10 *
    CANRcvFcn_B.CANFDUnpack3_o40);
  u = 0.00999999F * (real32_T)CANRcvFcn_B.CANFDUnpack1_o17;
  if (u >= 0.5F) {
    tmp = (int32_T)floorf(u + 0.5F);
  } else {
    tmp = 0;
  }

  rtb_TmpSignalConversionAtSFunct[473] = (uint16_T)fmodf((real32_T)tmp, 65536.0F);
  rtb_TmpSignalConversionAtSFunct[474] = (uint16_T)CANRcvFcn_B.CANFDUnpack3_o21;
  rtb_TmpSignalConversionAtSFunct[475] = (uint16_T)CANRcvFcn_B.CANFDUnpack3_o28;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o22), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[476] = (uint16_T)(u < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack3_o25), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[477] = (uint16_T)(u < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[478] = CANRcvFcn_B.CFunction11;
  rtb_TmpSignalConversionAtSFunct[479] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o12;
  rtb_TmpSignalConversionAtSFunct[480] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o13;
  rtb_TmpSignalConversionAtSFunct[481] = (uint16_T)CANRcvFcn_B.CANFDUnpack2_o11;
  u = fmodf(floorf(10.0F * CANRcvFcn_B.CANFDUnpack1_o25), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[482] = (uint16_T)(u < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[483] = CANRcvFcn_ConstB.DataTypeConversion65;
  rtb_TmpSignalConversionAtSFunct[484] = CANRcvFcn_B.CANFDUnpack3_o23;
  rtb_TmpSignalConversionAtSFunct[485] = (uint16_T)(CANRcvFcn_B.CANFDUnpack2_o3 >>
    16);
  rtb_TmpSignalConversionAtSFunct[486] = (uint16_T)(CANRcvFcn_B.CANFDUnpack2_o3
    & 65535U);
  u = fmodf(floorf(CANRcvFcn_B.CANFDUnpack1_o21), 65536.0F);
  rtb_TmpSignalConversionAtSFunct[487] = (uint16_T)(u < 0.0F ? (int32_T)
    (uint16_T)-(int16_T)(uint16_T)-u : (int32_T)(uint16_T)u);
  rtb_TmpSignalConversionAtSFunct[488] = CANRcvFcn_ConstB.DataTypeConversion72;
  rtb_TmpSignalConversionAtSFunct[489] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o1;
  rtb_TmpSignalConversionAtSFunct[490] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o2;
  rtb_TmpSignalConversionAtSFunct[491] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o3;
  rtb_TmpSignalConversionAtSFunct[492] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o4;
  rtb_TmpSignalConversionAtSFunct[493] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o5;
  rtb_TmpSignalConversionAtSFunct[494] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o6;
  rtb_TmpSignalConversionAtSFunct[495] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o7;
  rtb_TmpSignalConversionAtSFunct[496] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o8;
  rtb_TmpSignalConversionAtSFunct[497] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o9;
  rtb_TmpSignalConversionAtSFunct[498] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o10;
  rtb_TmpSignalConversionAtSFunct[499] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o11;
  rtb_TmpSignalConversionAtSFunct[500] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o12;
  rtb_TmpSignalConversionAtSFunct[501] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o13;
  rtb_TmpSignalConversionAtSFunct[502] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o14;
  rtb_TmpSignalConversionAtSFunct[503] = (uint16_T)CANRcvFcn_B.CANFDUnpack_o15;
  rtb_TmpSignalConversionAtSFunct[504] = (uint16_T)(CANRcvFcn_B.CANFDUnpack3_o26
    << 8 | CANRcvFcn_B.CANFDUnpack3_o27);
  rtb_TmpSignalConversionAtSFunct[505] = (uint16_T)(CANRcvFcn_B.CANFDUnpack3_o33
    << 8 | CANRcvFcn_B.CANFDUnpack3_o34);
  rtb_TmpSignalConversionAtSFunct[506] = CANRcvFcn_B.CANFDUnpack3_o32;
  rtb_TmpSignalConversionAtSFunct[507] = (uint16_T)((uint32_T)
    (CANRcvFcn_B.CANFDUnpack3_o15 - 8388608) >> 16);
  rtb_TmpSignalConversionAtSFunct[508] = (uint16_T)((uint32_T)
    (CANRcvFcn_B.CANFDUnpack3_o15 - 8388608) & 65535U);
  rtb_TmpSignalConversionAtSFunct[509] = rtb_DataTypeConversion27;
  rtb_TmpSignalConversionAtSFunct[510] = CANRcvFcn_B.BCU_V4_H;
  rtb_TmpSignalConversionAtSFunct[511] = CANRcvFcn_B.BCU_V4_L;
  rtb_TmpSignalConversionAtSFunct[512] = CFunction_o1;
  rtb_TmpSignalConversionAtSFunct[513] = CFunction_o2;
  rtb_TmpSignalConversionAtSFunct[514] = CFunction1_o1;
  rtb_TmpSignalConversionAtSFunct[515] = CFunction1_o2;
  rtb_TmpSignalConversionAtSFunct[516] = CANRcvFcn_B.BCU_Curr2_H;
  rtb_TmpSignalConversionAtSFunct[517] = CANRcvFcn_B.BCU_Curr2_L;
  rtb_TmpSignalConversionAtSFunct[518] = (uint16_T)(CANRcvFcn_B.ux180110E4_o2 <<
    8 | CANRcvFcn_B.ux180110E4_o1);
  rtb_TmpSignalConversionAtSFunct[519] = (uint16_T)(CANRcvFcn_B.ux180110E2_o2 <<
    8 | CANRcvFcn_B.ux180110E2_o1);
  rtb_TmpSignalConversionAtSFunct[520] = (uint16_T)(CANRcvFcn_B.ux180110E1_o2 <<
    8 | CANRcvFcn_B.ux180110E1_o1);
  rtb_TmpSignalConversionAtSFunct[521] = (uint16_T)(CANRcvFcn_B.ux180110E5_o2 <<
    8 | CANRcvFcn_B.ux180110E5_o1);
  rtb_TmpSignalConversionAtSFunct[522] = (uint16_T)(CANRcvFcn_B.ux180110E3_o2 <<
    8 | CANRcvFcn_B.ux180110E3_o1);
  rtb_TmpSignalConversionAtSFunct[523] = (uint16_T)(CANRcvFcn_B.ux180110E7_o2 <<
    8 | CANRcvFcn_B.ux180110E7_o1);
  rtb_TmpSignalConversionAtSFunct[524] = (uint16_T)(CANRcvFcn_B.ux180110E6_o2 <<
    8 | CANRcvFcn_B.ux180110E6_o1);
  rtb_TmpSignalConversionAtSFunct[525] = (uint16_T)(CANRcvFcn_B.ux180110E9_o2 <<
    8 | CANRcvFcn_B.ux180110E9_o1);
  rtb_TmpSignalConversionAtSFunct[526] = (uint16_T)(CANRcvFcn_B.ux180110E8_o2 <<
    8 | CANRcvFcn_B.ux180110E8_o1);
  rtb_TmpSignalConversionAtSFunct[527] = (uint16_T)(CANRcvFcn_B.ux180110E11_o2 <<
    8 | CANRcvFcn_B.ux180110E11_o1);
  rtb_TmpSignalConversionAtSFunct[528] = (uint16_T)(CANRcvFcn_B.ux180110E10_o2 <<
    8 | CANRcvFcn_B.ux180110E10_o1);
  rtb_TmpSignalConversionAtSFunct[529] = (uint16_T)(CANRcvFcn_B.ux180110E13_o2 <<
    8 | CANRcvFcn_B.ux180110E13_o1);
  rtb_TmpSignalConversionAtSFunct[530] = (uint16_T)(CANRcvFcn_B.ux180110E12_o2 <<
    8 | CANRcvFcn_B.ux180110E12_o1);
  rtb_TmpSignalConversionAtSFunct[531] = (uint16_T)(CANRcvFcn_B.ux180110E15_o2 <<
    8 | CANRcvFcn_B.ux180110E15_o1);
  rtb_TmpSignalConversionAtSFunct[532] = (uint16_T)(CANRcvFcn_B.ux180110E14_o2 <<
    8 | CANRcvFcn_B.ux180110E14_o1);
  rtb_TmpSignalConversionAtSFunct[533] = (uint16_T)(CANRcvFcn_B.ux180110E16_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[534] = (uint16_T)(CANRcvFcn_B.ux180110E16_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[535] = (uint16_T)(CANRcvFcn_B.ux180110E16_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[536] = (uint16_T)(CANRcvFcn_B.ux180110E16_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[537] = (uint16_T)(CANRcvFcn_B.ux180110E17_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[538] = (uint16_T)(CANRcvFcn_B.ux180110E17_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[539] = (uint16_T)(CANRcvFcn_B.ux180110E17_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[540] = (uint16_T)(CANRcvFcn_B.ux180110E17_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[541] = (uint16_T)(CANRcvFcn_B.ux180110E18_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[542] = (uint16_T)(CANRcvFcn_B.ux180110E18_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[543] = (uint16_T)(CANRcvFcn_B.ux180110E18_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[544] = (uint16_T)(CANRcvFcn_B.ux180110E18_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[545] = (uint16_T)(CANRcvFcn_B.ux180110E19_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[546] = (uint16_T)(CANRcvFcn_B.ux180110E19_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[547] = (uint16_T)(CANRcvFcn_B.ux180110E19_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[548] = (uint16_T)(CANRcvFcn_B.ux180110E19_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[549] = (uint16_T)(CANRcvFcn_B.ux180110E20_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[550] = (uint16_T)(CANRcvFcn_B.ux180110E20_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[551] = (uint16_T)(CANRcvFcn_B.ux180110E20_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[552] = (uint16_T)(CANRcvFcn_B.ux180110E20_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[553] = (uint16_T)(CANRcvFcn_B.ux180110E21_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[554] = (uint16_T)(CANRcvFcn_B.ux180110E21_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[555] = (uint16_T)(CANRcvFcn_B.ux180110E21_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[556] = (uint16_T)(CANRcvFcn_B.ux180110E21_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[557] = (uint16_T)(CANRcvFcn_B.ux180110E22_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[558] = (uint16_T)(CANRcvFcn_B.ux180110E22_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[559] = (uint16_T)(CANRcvFcn_B.ux180110E22_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[560] = (uint16_T)(CANRcvFcn_B.ux180110E22_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[561] = (uint16_T)(CANRcvFcn_B.ux180110E23_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[562] = (uint16_T)(CANRcvFcn_B.ux180110E23_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[563] = (uint16_T)(CANRcvFcn_B.ux180110E23_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[564] = (uint16_T)(CANRcvFcn_B.ux180110E23_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[565] = (uint16_T)(CANRcvFcn_B.ux180110E24_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[566] = (uint16_T)(CANRcvFcn_B.ux180110E24_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[567] = (uint16_T)(CANRcvFcn_B.ux180110E24_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[568] = (uint16_T)(CANRcvFcn_B.ux180110E24_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[569] = (uint16_T)(CANRcvFcn_B.ux180110E25_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[570] = (uint16_T)(CANRcvFcn_B.ux180110E25_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[571] = (uint16_T)(CANRcvFcn_B.ux180110E25_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[572] = (uint16_T)(CANRcvFcn_B.ux180110E25_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[573] = (uint16_T)(CANRcvFcn_B.ux180110E26_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[574] = (uint16_T)(CANRcvFcn_B.ux180110E26_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[575] = (uint16_T)(CANRcvFcn_B.ux180110E26_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[576] = (uint16_T)(CANRcvFcn_B.ux180110E26_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[577] = (uint16_T)(CANRcvFcn_B.ux180110E27_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[578] = (uint16_T)(CANRcvFcn_B.ux180110E27_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[579] = (uint16_T)(CANRcvFcn_B.ux180110E27_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[580] = (uint16_T)(CANRcvFcn_B.ux180110E27_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[581] = (uint16_T)(CANRcvFcn_B.ux180110E28_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[582] = (uint16_T)(CANRcvFcn_B.ux180110E28_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[583] = (uint16_T)(CANRcvFcn_B.ux180110E28_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[584] = (uint16_T)(CANRcvFcn_B.ux180110E28_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[585] = (uint16_T)(CANRcvFcn_B.ux180110E29_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[586] = (uint16_T)(CANRcvFcn_B.ux180110E29_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[587] = (uint16_T)(CANRcvFcn_B.ux180110E29_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[588] = (uint16_T)(CANRcvFcn_B.ux180110E29_o2 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[589] = (uint16_T)(CANRcvFcn_B.ux180110E30_o1 >>
    16);
  rtb_TmpSignalConversionAtSFunct[590] = (uint16_T)(CANRcvFcn_B.ux180110E30_o1 &
    65535U);
  rtb_TmpSignalConversionAtSFunct[591] = (uint16_T)(CANRcvFcn_B.ux180110E30_o2 >>
    16);
  rtb_TmpSignalConversionAtSFunct[592] = (uint16_T)(CANRcvFcn_B.ux180110E30_o2 &
    65535U);

  /* Chart: '<Root>/Chart1' incorporates:
   *  Constant: '<Root>/index'
   *  Constant: '<Root>/portDimensions'
   *  Outport: '<Root>/modbusBuff'
   */
  data_index = 0U;
  port_index = 0U;
  port_len = sizeof(uint32_T);
  if (port_len == 0U) {
    port_len = MAX_uint32_T;

    /* Divide by zero handler */
  } else {
    port_len = sizeof(uint32_T [207]) / port_len;
  }

  while (port_index < port_len) {
    if (CANRcvFcn_ConstP.portDimensions_Value[port_index] == 1U) {
      modbusBuff[CANRcvFcn_ConstP.index_Value[port_index]] =
        rtb_TmpSignalConversionAtSFunct[data_index];
      qY = data_index + /*MW:OvSatOk*/ 1U;
      if (data_index + 1U < data_index) {
        qY = MAX_uint32_T;
      }

      data_index = qY;
    } else {
      i = 0U;
      while (i < CANRcvFcn_ConstP.portDimensions_Value[port_index]) {
        q0 = CANRcvFcn_ConstP.index_Value[port_index];
        qY = q0 + /*MW:OvSatOk*/ i;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        modbusBuff[qY] = rtb_TmpSignalConversionAtSFunct[data_index];
        qY = data_index + /*MW:OvSatOk*/ 1U;
        if (data_index + 1U < data_index) {
          qY = MAX_uint32_T;
        }

        data_index = qY;
        tmp = i + 1;
        if (i + 1 > 65535) {
          tmp = 65535;
        }

        i = (uint16_T)tmp;
      }
    }

    port_index++;
  }
}

/* Model initialize function */
void CANRcvFcn_initialize(void)
{
  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack1' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack1 -----------------*/

  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack3' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack3 -----------------*/

  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack -----------------*/

  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack2' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack2 -----------------*/

  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack4' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack4 -----------------*/

  /* Start for S-Function (scanfdunpack): '<S1>/CAN FD Unpack5' incorporates:
   *  Inport: '<Root>/CANFDRcvMsg'
   */

  /*-----------S-Function Block: <S1>/CAN FD Unpack5 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E4' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E4 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E2' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E2 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E1' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E1 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E5' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E5 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E3' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E3 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E7' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E7 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E6' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E6 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E9' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E9 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E8' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E8 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E11' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E11 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E10' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E10 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E13' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E13 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E12' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E12 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E15' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E15 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E14' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E14 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E16' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E16 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E17' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E17 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E18' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E18 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E19' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E19 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E20' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E20 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E21' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E21 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E22' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E22 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E23' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E23 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E24' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E24 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E25' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E25 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E26' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E26 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E27' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E27 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E28' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E28 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E29' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E29 -----------------*/

  /* Start for S-Function (scanunpack): '<S3>/0x180110E30' incorporates:
   *  Inport: '<Root>/CANMsg'
   */

  /*-----------S-Function Block: <S3>/0x180110E30 -----------------*/
}

/* Model terminate function */
void CANRcvFcn_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
