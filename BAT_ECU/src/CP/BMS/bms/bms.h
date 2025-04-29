/*
 * File: bms.h
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

#ifndef RTW_HEADER_bms_h_
#define RTW_HEADER_bms_h_
#ifndef bms_COMMON_INCLUDES_
#define bms_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "can_message.h"
#endif                                 /* bms_COMMON_INCLUDES_ */

#include "bms_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* user code (top of header file) */
#include "../../Modbus/C_ModbusServer.h"
#include "bms_cortol.h"

/* Block signals (default storage) */
typedef struct {
  CAN_MESSAGE_BUS CANBuff1;            /* '<Root>/CANBuff1' */
  CAN_MESSAGE_BUS CANBuff2;            /* '<Root>/CANBuff2' */
  real_T CANUnpack2_o2;                /* '<S2>/CAN Unpack2' */
  real_T CANUnpack2_o4;                /* '<S2>/CAN Unpack2' */
  uint32_T CANUnpack19_o3;             /* '<S2>/CAN Unpack19' */
  uint32_T ux180110E16_o1;             /* '<S3>/0x180110E16' */
  uint32_T ux180110E16_o2;             /* '<S3>/0x180110E16' */
  uint32_T ux180110E17_o1;             /* '<S3>/0x180110E17' */
  uint32_T ux180110E17_o2;             /* '<S3>/0x180110E17' */
  uint32_T ux180110E18_o1;             /* '<S3>/0x180110E18' */
  uint32_T ux180110E18_o2;             /* '<S3>/0x180110E18' */
  uint32_T ux180110E19_o1;             /* '<S3>/0x180110E19' */
  uint32_T ux180110E19_o2;             /* '<S3>/0x180110E19' */
  uint32_T ux180110E20_o1;             /* '<S3>/0x180110E20' */
  uint32_T ux180110E20_o2;             /* '<S3>/0x180110E20' */
  uint32_T ux180110E21_o1;             /* '<S3>/0x180110E21' */
  uint32_T ux180110E21_o2;             /* '<S3>/0x180110E21' */
  uint32_T ux180110E22_o1;             /* '<S3>/0x180110E22' */
  uint32_T ux180110E22_o2;             /* '<S3>/0x180110E22' */
  uint32_T ux180110E23_o1;             /* '<S3>/0x180110E23' */
  uint32_T ux180110E23_o2;             /* '<S3>/0x180110E23' */
  uint32_T ux180110E24_o1;             /* '<S3>/0x180110E24' */
  uint32_T ux180110E24_o2;             /* '<S3>/0x180110E24' */
  uint32_T ux180110E25_o1;             /* '<S3>/0x180110E25' */
  uint32_T ux180110E25_o2;             /* '<S3>/0x180110E25' */
  uint32_T ux180110E26_o1;             /* '<S3>/0x180110E26' */
  uint32_T ux180110E26_o2;             /* '<S3>/0x180110E26' */
  uint32_T ux180110E27_o1;             /* '<S3>/0x180110E27' */
  uint32_T ux180110E27_o2;             /* '<S3>/0x180110E27' */
  uint32_T ux180110E28_o1;             /* '<S3>/0x180110E28' */
  uint32_T ux180110E28_o2;             /* '<S3>/0x180110E28' */
  uint32_T ux180110E29_o1;             /* '<S3>/0x180110E29' */
  uint32_T ux180110E29_o2;             /* '<S3>/0x180110E29' */
  uint32_T ux180110E30_o1;             /* '<S3>/0x180110E30' */
  uint32_T ux180110E30_o2;             /* '<S3>/0x180110E30' */
  real32_T ux180110E4_o2;              /* '<S2>/0x180110E4' */
  real32_T ux180110E4_o3;              /* '<S2>/0x180110E4' */
  real32_T ux180110E4_o7;              /* '<S2>/0x180110E4' */
  real32_T ux180110E4_o8;              /* '<S2>/0x180110E4' */
  real32_T ux1C0110E4_o2;              /* '<S2>/0x1C0110E4' */
  real32_T ux1C0110E4_o3;              /* '<S2>/0x1C0110E4' */
  real32_T ux180210E4_o1;              /* '<S2>/0x180210E4' */
  real32_T ux180210E4_o2;              /* '<S2>/0x180210E4' */
  real32_T CANUnpack5_o1;              /* '<S2>/CAN Unpack5' */
  real32_T CANUnpack5_o3;              /* '<S2>/CAN Unpack5' */
  real32_T ux180410E4_o1;              /* '<S2>/0x180410E4' */
  real32_T ux180410E4_o2;              /* '<S2>/0x180410E4' */
  real32_T CANUnpack27_o1;             /* '<S2>/CAN Unpack27' */
  real32_T CANUnpack27_o2;             /* '<S2>/CAN Unpack27' */
  real32_T CANUnpack27_o3;             /* '<S2>/CAN Unpack27' */
  real32_T CANUnpack27_o4;             /* '<S2>/CAN Unpack27' */
  uint16_T ux1C0110E4_o1;              /* '<S2>/0x1C0110E4' */
  uint16_T ux1C0110E4_o4;              /* '<S2>/0x1C0110E4' */
  uint16_T ux1C0110E4_o5;              /* '<S2>/0x1C0110E4' */
  uint16_T ux1B0310E4_o1;              /* '<S2>/0x1B0310E4' */
  uint16_T ux1B0310E4_o2;              /* '<S2>/0x1B0310E4' */
  uint16_T ux1B0310E4_o3;              /* '<S2>/0x1B0310E4' */
  uint16_T ux1B0310E4_o4;              /* '<S2>/0x1B0310E4' */
  uint16_T ux1B0310E4_o5;              /* '<S2>/0x1B0310E4' */
  uint16_T CANUnpack5_o2;              /* '<S2>/CAN Unpack5' */
  uint16_T CANUnpack10_o1;             /* '<S2>/CAN Unpack10' */
  uint16_T CANUnpack10_o2;             /* '<S2>/CAN Unpack10' */
  uint16_T CANUnpack10_o3;             /* '<S2>/CAN Unpack10' */
  uint16_T CANUnpack10_o4;             /* '<S2>/CAN Unpack10' */
  uint16_T CANUnpack11_o1;             /* '<S2>/CAN Unpack11' */
  uint16_T CANUnpack11_o2;             /* '<S2>/CAN Unpack11' */
  uint16_T CANUnpack11_o3;             /* '<S2>/CAN Unpack11' */
  uint16_T CANUnpack11_o4;             /* '<S2>/CAN Unpack11' */
  uint16_T CANUnpack11_o5;             /* '<S2>/CAN Unpack11' */
  uint16_T ux180710E4_o1;              /* '<S2>/0x180710E4' */
  uint16_T ux180710E4_o2;              /* '<S2>/0x180710E4' */
  uint16_T ux180710E4_o3;              /* '<S2>/0x180710E4' */
  uint16_T SOX_o1;                     /* '<S2>/SOX' */
  uint16_T SOX_o2;                     /* '<S2>/SOX' */
  uint16_T SOX_o3;                     /* '<S2>/SOX' */
  uint16_T SOX_o4;                     /* '<S2>/SOX' */
  uint16_T CANUnpack19_o1;             /* '<S2>/CAN Unpack19' */
  uint16_T CANUnpack19_o2;             /* '<S2>/CAN Unpack19' */
  uint16_T ux181310E4_o1;              /* '<S2>/0x181310E4' */
  uint16_T ux181310E4_o3;              /* '<S2>/0x181310E4' */
  uint16_T ux181310E4_o4;              /* '<S2>/0x181310E4' */
  uint16_T ux181310E4_o6;              /* '<S2>/0x181310E4' */
  uint16_T ux180C10E4_o1;              /* '<S2>/0x180C10E4' */
  uint16_T ux180C10E4_o2;              /* '<S2>/0x180C10E4' */
  uint16_T ux180C10E4_o3;              /* '<S2>/0x180C10E4' */
  uint16_T ux180C10E4_o5;              /* '<S2>/0x180C10E4' */
  uint16_T ux181210E4_o2;              /* '<S2>/0x181210E4' */
  uint16_T ux181210E4_o3;              /* '<S2>/0x181210E4' */
  uint16_T ux181210E4_o4;              /* '<S2>/0x181210E4' */
  uint16_T ux181210E4_o5;              /* '<S2>/0x181210E4' */
  uint16_T ux180810E4_o2;              /* '<S2>/0x180810E4' */
  uint16_T ux180810E4_o5;              /* '<S2>/0x180810E4' */
  uint16_T ux180A10E4_o1;              /* '<S2>/0x180A10E4' */
  uint16_T ux180A10E4_o2;              /* '<S2>/0x180A10E4' */
  uint16_T ux180A10E4_o3;              /* '<S2>/0x180A10E4' */
  uint16_T ux180A10E4_o4;              /* '<S2>/0x180A10E4' */
  uint16_T ux180A10E4_o5;              /* '<S2>/0x180A10E4' */
  uint16_T CANUnpack32_o1;             /* '<S2>/CAN Unpack32' */
  uint16_T CANUnpack32_o2;             /* '<S2>/CAN Unpack32' */
  uint16_T CANUnpack32_o3;             /* '<S2>/CAN Unpack32' */
  uint16_T CANUnpack32_o4;             /* '<S2>/CAN Unpack32' */
  uint16_T CANUnpack29_o1;             /* '<S2>/CAN Unpack29' */
  uint16_T CANUnpack29_o2;             /* '<S2>/CAN Unpack29' */
  uint16_T CANUnpack29_o3;             /* '<S2>/CAN Unpack29' */
  uint16_T CANUnpack1_o2;              /* '<S2>/CAN Unpack1' */
  uint16_T CANUnpack1_o5;              /* '<S2>/CAN Unpack1' */
  uint16_T CANUnpack2_o3;              /* '<S2>/CAN Unpack2' */
  uint16_T CANUnpack2_o6;              /* '<S2>/CAN Unpack2' */
  uint16_T CANUnpack2_o7;              /* '<S2>/CAN Unpack2' */
  uint16_T CANUnpack2_o8;              /* '<S2>/CAN Unpack2' */
  uint16_T CANUnpack2_o9;              /* '<S2>/CAN Unpack2' */
  uint16_T CFunction11;                /* '<S2>/C Function11' */
  uint16_T ux180110E2_o1;              /* '<S2>/0x180110E2' */
  int16_T ux181310E4_o2;               /* '<S2>/0x181310E4' */
  int16_T ux181310E4_o5;               /* '<S2>/0x181310E4' */
  int16_T ux180B10E4_o3;               /* '<S2>/0x180B10E4' */
  int16_T ux180B10E4_o6;               /* '<S2>/0x180B10E4' */
  int16_T ux180C10E4_o4;               /* '<S2>/0x180C10E4' */
  int16_T ux180C10E4_o6;               /* '<S2>/0x180C10E4' */
  int16_T ux181410E4_o3;               /* '<S2>/0x181410E4' */
  int16_T ux181410E4_o6;               /* '<S2>/0x181410E4' */
  int16_T ux1B0110E4_o1;               /* '<S2>/0x1B0110E4' */
  int16_T ux1B0110E4_o2;               /* '<S2>/0x1B0110E4' */
  int16_T ux1B0110E4_o3;               /* '<S2>/0x1B0110E4' */
  int16_T ux1B0110E4_o4;               /* '<S2>/0x1B0110E4' */
  int16_T ux1B0110E4_o5;               /* '<S2>/0x1B0110E4' */
  int16_T ux1B0110E4_o6;               /* '<S2>/0x1B0110E4' */
  int16_T CANUnpack1_o1;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack1_o3;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack1_o4;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack1_o6;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack1_o7;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack1_o8;               /* '<S2>/CAN Unpack1' */
  int16_T CANUnpack2_o1;               /* '<S2>/CAN Unpack2' */
  int16_T CANUnpack2_o5;               /* '<S2>/CAN Unpack2' */
  int16_T CANUnpack3_o1;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack3_o2;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack3_o3;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack3_o4;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack3_o5;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack3_o6;               /* '<S2>/CAN Unpack3' */
  int16_T CANUnpack4_o1;               /* '<S2>/CAN Unpack4' */
  int16_T CANUnpack4_o2;               /* '<S2>/CAN Unpack4' */
  int16_T CANUnpack4_o3;               /* '<S2>/CAN Unpack4' */
  int16_T CANUnpack4_o4;               /* '<S2>/CAN Unpack4' */
  int16_T CANUnpack4_o5;               /* '<S2>/CAN Unpack4' */
  uint8_T ux180110E4_o4;               /* '<S2>/0x180110E4' */
  uint8_T ux180110E4_o5;               /* '<S2>/0x180110E4' */
  uint8_T ux180110E4_o6;               /* '<S2>/0x180110E4' */
  uint8_T ux180B10E4_o1;               /* '<S2>/0x180B10E4' */
  uint8_T ux180B10E4_o2;               /* '<S2>/0x180B10E4' */
  uint8_T ux180B10E4_o4;               /* '<S2>/0x180B10E4' */
  uint8_T ux180B10E4_o5;               /* '<S2>/0x180B10E4' */
  uint8_T ux181410E4_o1;               /* '<S2>/0x181410E4' */
  uint8_T ux181410E4_o2;               /* '<S2>/0x181410E4' */
  uint8_T ux181410E4_o4;               /* '<S2>/0x181410E4' */
  uint8_T ux181410E4_o5;               /* '<S2>/0x181410E4' */
  uint8_T ux181210E4_o1;               /* '<S2>/0x181210E4' */
  uint8_T ux181210E4_o6;               /* '<S2>/0x181210E4' */
  uint8_T ux180810E4_o1;               /* '<S2>/0x180810E4' */
  uint8_T ux180810E4_o3;               /* '<S2>/0x180810E4' */
  uint8_T ux180810E4_o4;               /* '<S2>/0x180810E4' */
  uint8_T ux180810E4_o6;               /* '<S2>/0x180810E4' */
  uint8_T ux1B0110E4_o7;               /* '<S2>/0x1B0110E4' */
  uint8_T CANUnpack29_o4;              /* '<S2>/CAN Unpack29' */
  uint8_T CANUnpack4_o6;               /* '<S2>/CAN Unpack4' */
  uint8_T CANUnpack6_o1;               /* '<S2>/CAN Unpack6' */
  uint8_T CANUnpack6_o2;               /* '<S2>/CAN Unpack6' */
  uint8_T CANUnpack7_o1;               /* '<S2>/CAN Unpack7' */
  uint8_T CANUnpack7_o2;               /* '<S2>/CAN Unpack7' */
  uint8_T CANUnpack8_o2;               /* '<S2>/CAN Unpack8' */
  uint8_T ux180110E4_o1;               /* '<S3>/0x180110E4' */
  uint8_T ux180110E4_o2_a;             /* '<S3>/0x180110E4' */
  uint8_T ux180110E2_o1_o;             /* '<S3>/0x180110E2' */
  uint8_T ux180110E2_o2;               /* '<S3>/0x180110E2' */
  uint8_T ux180110E1_o1;               /* '<S3>/0x180110E1' */
  uint8_T ux180110E1_o2;               /* '<S3>/0x180110E1' */
  uint8_T ux180110E5_o1;               /* '<S3>/0x180110E5' */
  uint8_T ux180110E5_o2;               /* '<S3>/0x180110E5' */
  uint8_T ux180110E3_o1;               /* '<S3>/0x180110E3' */
  uint8_T ux180110E3_o2;               /* '<S3>/0x180110E3' */
  uint8_T ux180110E7_o1;               /* '<S3>/0x180110E7' */
  uint8_T ux180110E7_o2;               /* '<S3>/0x180110E7' */
  uint8_T ux180110E6_o1;               /* '<S3>/0x180110E6' */
  uint8_T ux180110E6_o2;               /* '<S3>/0x180110E6' */
  uint8_T ux180110E9_o1;               /* '<S3>/0x180110E9' */
  uint8_T ux180110E9_o2;               /* '<S3>/0x180110E9' */
  uint8_T ux180110E8_o1;               /* '<S3>/0x180110E8' */
  uint8_T ux180110E8_o2;               /* '<S3>/0x180110E8' */
  uint8_T ux180110E11_o1;              /* '<S3>/0x180110E11' */
  uint8_T ux180110E11_o2;              /* '<S3>/0x180110E11' */
  uint8_T ux180110E10_o1;              /* '<S3>/0x180110E10' */
  uint8_T ux180110E10_o2;              /* '<S3>/0x180110E10' */
  uint8_T ux180110E13_o1;              /* '<S3>/0x180110E13' */
  uint8_T ux180110E13_o2;              /* '<S3>/0x180110E13' */
  uint8_T ux180110E12_o1;              /* '<S3>/0x180110E12' */
  uint8_T ux180110E12_o2;              /* '<S3>/0x180110E12' */
  uint8_T ux180110E15_o1;              /* '<S3>/0x180110E15' */
  uint8_T ux180110E15_o2;              /* '<S3>/0x180110E15' */
  uint8_T ux180110E14_o1;              /* '<S3>/0x180110E14' */
  uint8_T ux180110E14_o2;              /* '<S3>/0x180110E14' */
  int8_T CANUnpack8_o1;                /* '<S2>/CAN Unpack8' */
} B_bms_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int_T ux180110E4_ModeSignalID;       /* '<S2>/0x180110E4' */
  int_T ux180110E4_StatusPortID;       /* '<S2>/0x180110E4' */
  int_T ux1C0110E4_ModeSignalID;       /* '<S2>/0x1C0110E4' */
  int_T ux1C0110E4_StatusPortID;       /* '<S2>/0x1C0110E4' */
  int_T ux1B0310E4_ModeSignalID;       /* '<S2>/0x1B0310E4' */
  int_T ux1B0310E4_StatusPortID;       /* '<S2>/0x1B0310E4' */
  int_T ux180210E4_ModeSignalID;       /* '<S2>/0x180210E4' */
  int_T ux180210E4_StatusPortID;       /* '<S2>/0x180210E4' */
  int_T CANUnpack5_ModeSignalID;       /* '<S2>/CAN Unpack5' */
  int_T CANUnpack5_StatusPortID;       /* '<S2>/CAN Unpack5' */
  int_T ux180410E4_ModeSignalID;       /* '<S2>/0x180410E4' */
  int_T ux180410E4_StatusPortID;       /* '<S2>/0x180410E4' */
  int_T CANUnpack10_ModeSignalID;      /* '<S2>/CAN Unpack10' */
  int_T CANUnpack10_StatusPortID;      /* '<S2>/CAN Unpack10' */
  int_T CANUnpack11_ModeSignalID;      /* '<S2>/CAN Unpack11' */
  int_T CANUnpack11_StatusPortID;      /* '<S2>/CAN Unpack11' */
  int_T ux180E10E4_ModeSignalID;       /* '<S2>/0x180E10E4' */
  int_T ux180E10E4_StatusPortID;       /* '<S2>/0x180E10E4' */
  int_T ux180F10E4_ModeSignalID;       /* '<S2>/0x180F10E4' */
  int_T ux180F10E4_StatusPortID;       /* '<S2>/0x180F10E4' */
  int_T ux181010E4_ModeSignalID;       /* '<S2>/0x181010E4' */
  int_T ux181010E4_StatusPortID;       /* '<S2>/0x181010E4' */
  int_T ux181110E4_ModeSignalID;       /* '<S2>/0x181110E4' */
  int_T ux181110E4_StatusPortID;       /* '<S2>/0x181110E4' */
  int_T ux180710E4_ModeSignalID;       /* '<S2>/0x180710E4' */
  int_T ux180710E4_StatusPortID;       /* '<S2>/0x180710E4' */
  int_T SOX_ModeSignalID;              /* '<S2>/SOX' */
  int_T SOX_StatusPortID;              /* '<S2>/SOX' */
  int_T CANUnpack19_ModeSignalID;      /* '<S2>/CAN Unpack19' */
  int_T CANUnpack19_StatusPortID;      /* '<S2>/CAN Unpack19' */
  int_T ux181310E4_ModeSignalID;       /* '<S2>/0x181310E4' */
  int_T ux181310E4_StatusPortID;       /* '<S2>/0x181310E4' */
  int_T ux180B10E4_ModeSignalID;       /* '<S2>/0x180B10E4' */
  int_T ux180B10E4_StatusPortID;       /* '<S2>/0x180B10E4' */
  int_T ux180C10E4_ModeSignalID;       /* '<S2>/0x180C10E4' */
  int_T ux180C10E4_StatusPortID;       /* '<S2>/0x180C10E4' */
  int_T ux181410E4_ModeSignalID;       /* '<S2>/0x181410E4' */
  int_T ux181410E4_StatusPortID;       /* '<S2>/0x181410E4' */
  int_T CANUnpack27_ModeSignalID;      /* '<S2>/CAN Unpack27' */
  int_T CANUnpack27_StatusPortID;      /* '<S2>/CAN Unpack27' */
  int_T ux181210E4_ModeSignalID;       /* '<S2>/0x181210E4' */
  int_T ux181210E4_StatusPortID;       /* '<S2>/0x181210E4' */
  int_T ux180810E4_ModeSignalID;       /* '<S2>/0x180810E4' */
  int_T ux180810E4_StatusPortID;       /* '<S2>/0x180810E4' */
  int_T ux180A10E4_ModeSignalID;       /* '<S2>/0x180A10E4' */
  int_T ux180A10E4_StatusPortID;       /* '<S2>/0x180A10E4' */
  int_T CANUnpack32_ModeSignalID;      /* '<S2>/CAN Unpack32' */
  int_T CANUnpack32_StatusPortID;      /* '<S2>/CAN Unpack32' */
  int_T ux1B0110E4_ModeSignalID;       /* '<S2>/0x1B0110E4' */
  int_T ux1B0110E4_StatusPortID;       /* '<S2>/0x1B0110E4' */
  int_T CANUnpack29_ModeSignalID;      /* '<S2>/CAN Unpack29' */
  int_T CANUnpack29_StatusPortID;      /* '<S2>/CAN Unpack29' */
  int_T CANUnpack1_ModeSignalID;       /* '<S2>/CAN Unpack1' */
  int_T CANUnpack1_StatusPortID;       /* '<S2>/CAN Unpack1' */
  int_T CANUnpack2_ModeSignalID;       /* '<S2>/CAN Unpack2' */
  int_T CANUnpack2_StatusPortID;       /* '<S2>/CAN Unpack2' */
  int_T CANUnpack3_ModeSignalID;       /* '<S2>/CAN Unpack3' */
  int_T CANUnpack3_StatusPortID;       /* '<S2>/CAN Unpack3' */
  int_T CANUnpack4_ModeSignalID;       /* '<S2>/CAN Unpack4' */
  int_T CANUnpack4_StatusPortID;       /* '<S2>/CAN Unpack4' */
  int_T CANUnpack6_ModeSignalID;       /* '<S2>/CAN Unpack6' */
  int_T CANUnpack6_StatusPortID;       /* '<S2>/CAN Unpack6' */
  int_T CANUnpack7_ModeSignalID;       /* '<S2>/CAN Unpack7' */
  int_T CANUnpack7_StatusPortID;       /* '<S2>/CAN Unpack7' */
  int_T CANUnpack8_ModeSignalID;       /* '<S2>/CAN Unpack8' */
  int_T CANUnpack8_StatusPortID;       /* '<S2>/CAN Unpack8' */
  int_T ux180110E4_ModeSignalID_d;     /* '<S3>/0x180110E4' */
  int_T ux180110E4_StatusPortID_i;     /* '<S3>/0x180110E4' */
  int_T ux180110E2_ModeSignalID;       /* '<S3>/0x180110E2' */
  int_T ux180110E2_StatusPortID;       /* '<S3>/0x180110E2' */
  int_T ux180110E1_ModeSignalID;       /* '<S3>/0x180110E1' */
  int_T ux180110E1_StatusPortID;       /* '<S3>/0x180110E1' */
  int_T ux180110E5_ModeSignalID;       /* '<S3>/0x180110E5' */
  int_T ux180110E5_StatusPortID;       /* '<S3>/0x180110E5' */
  int_T ux180110E3_ModeSignalID;       /* '<S3>/0x180110E3' */
  int_T ux180110E3_StatusPortID;       /* '<S3>/0x180110E3' */
  int_T ux180110E7_ModeSignalID;       /* '<S3>/0x180110E7' */
  int_T ux180110E7_StatusPortID;       /* '<S3>/0x180110E7' */
  int_T ux180110E6_ModeSignalID;       /* '<S3>/0x180110E6' */
  int_T ux180110E6_StatusPortID;       /* '<S3>/0x180110E6' */
  int_T ux180110E9_ModeSignalID;       /* '<S3>/0x180110E9' */
  int_T ux180110E9_StatusPortID;       /* '<S3>/0x180110E9' */
  int_T ux180110E8_ModeSignalID;       /* '<S3>/0x180110E8' */
  int_T ux180110E8_StatusPortID;       /* '<S3>/0x180110E8' */
  int_T ux180110E11_ModeSignalID;      /* '<S3>/0x180110E11' */
  int_T ux180110E11_StatusPortID;      /* '<S3>/0x180110E11' */
  int_T ux180110E10_ModeSignalID;      /* '<S3>/0x180110E10' */
  int_T ux180110E10_StatusPortID;      /* '<S3>/0x180110E10' */
  int_T ux180110E13_ModeSignalID;      /* '<S3>/0x180110E13' */
  int_T ux180110E13_StatusPortID;      /* '<S3>/0x180110E13' */
  int_T ux180110E12_ModeSignalID;      /* '<S3>/0x180110E12' */
  int_T ux180110E12_StatusPortID;      /* '<S3>/0x180110E12' */
  int_T ux180110E15_ModeSignalID;      /* '<S3>/0x180110E15' */
  int_T ux180110E15_StatusPortID;      /* '<S3>/0x180110E15' */
  int_T ux180110E14_ModeSignalID;      /* '<S3>/0x180110E14' */
  int_T ux180110E14_StatusPortID;      /* '<S3>/0x180110E14' */
  int_T ux180110E16_ModeSignalID;      /* '<S3>/0x180110E16' */
  int_T ux180110E16_StatusPortID;      /* '<S3>/0x180110E16' */
  int_T ux180110E17_ModeSignalID;      /* '<S3>/0x180110E17' */
  int_T ux180110E17_StatusPortID;      /* '<S3>/0x180110E17' */
  int_T ux180110E18_ModeSignalID;      /* '<S3>/0x180110E18' */
  int_T ux180110E18_StatusPortID;      /* '<S3>/0x180110E18' */
  int_T ux180110E19_ModeSignalID;      /* '<S3>/0x180110E19' */
  int_T ux180110E19_StatusPortID;      /* '<S3>/0x180110E19' */
  int_T ux180110E20_ModeSignalID;      /* '<S3>/0x180110E20' */
  int_T ux180110E20_StatusPortID;      /* '<S3>/0x180110E20' */
  int_T ux180110E21_ModeSignalID;      /* '<S3>/0x180110E21' */
  int_T ux180110E21_StatusPortID;      /* '<S3>/0x180110E21' */
  int_T ux180110E22_ModeSignalID;      /* '<S3>/0x180110E22' */
  int_T ux180110E22_StatusPortID;      /* '<S3>/0x180110E22' */
  int_T ux180110E23_ModeSignalID;      /* '<S3>/0x180110E23' */
  int_T ux180110E23_StatusPortID;      /* '<S3>/0x180110E23' */
  int_T ux180110E24_ModeSignalID;      /* '<S3>/0x180110E24' */
  int_T ux180110E24_StatusPortID;      /* '<S3>/0x180110E24' */
  int_T ux180110E25_ModeSignalID;      /* '<S3>/0x180110E25' */
  int_T ux180110E25_StatusPortID;      /* '<S3>/0x180110E25' */
  int_T ux180110E26_ModeSignalID;      /* '<S3>/0x180110E26' */
  int_T ux180110E26_StatusPortID;      /* '<S3>/0x180110E26' */
  int_T ux180110E27_ModeSignalID;      /* '<S3>/0x180110E27' */
  int_T ux180110E27_StatusPortID;      /* '<S3>/0x180110E27' */
  int_T ux180110E28_ModeSignalID;      /* '<S3>/0x180110E28' */
  int_T ux180110E28_StatusPortID;      /* '<S3>/0x180110E28' */
  int_T ux180110E29_ModeSignalID;      /* '<S3>/0x180110E29' */
  int_T ux180110E29_StatusPortID;      /* '<S3>/0x180110E29' */
  int_T ux180110E30_ModeSignalID;      /* '<S3>/0x180110E30' */
  int_T ux180110E30_StatusPortID;      /* '<S3>/0x180110E30' */
  int_T ux180110E2_ModeSignalID_h;     /* '<S2>/0x180110E2' */
  int_T ux180110E2_StatusPortID_m;     /* '<S2>/0x180110E2' */
  uint16_T tmp[15];                    /* '<S2>/MATLAB Function3' */
  uint16_T tmp_n[240];                 /* '<S2>/MATLAB Function2' */
  uint16_T tmp_a[15];                  /* '<S2>/MATLAB Function1' */
  uint16_T tmp_ay[120];                /* '<S2>/MATLAB Function' */
} DW_bms_T;

/* Invariant block signals (default storage) */
typedef struct {
  const boolean_T DataTypeConversion27;/* '<S2>/Data Type Conversion27' */
  const boolean_T DataTypeConversion28;/* '<S2>/Data Type Conversion28' */
  const boolean_T DataTypeConversion29;/* '<S2>/Data Type Conversion29' */
  const boolean_T DataTypeConversion30;/* '<S2>/Data Type Conversion30' */
  const boolean_T DataTypeConversion38;/* '<S2>/Data Type Conversion38' */
} ConstB_bms_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Constant1_Value
   * Referenced by: '<Root>/Constant1'
   */
  uint32_T Constant1_Value[196];

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<Root>/Constant2'
   */
  uint32_T Constant2_Value[196];
} ConstP_bms_T;

/* Real-time Model Data Structure */
struct tag_RTM_bms_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_bms_T bms_B;

/* Block states (default storage) */
extern DW_bms_T bms_DW;
extern const ConstB_bms_T bms_ConstB;  /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_bms_T bms_ConstP;

/* Model entry point functions */
extern void bms_initialize(void);
extern void bms_step(void);
extern void bms_terminate(void);

/* Real-time Model object */
extern RT_MODEL_bms_T *const bms_M;

/* Exported data declaration */

/* Declaration for custom storage class: Default */
extern uint32_T BCU_FaultInfoLv1H;     /* '<S2>/0x180E10E4' */
extern uint32_T BCU_FaultInfoLv1L;     /* '<S2>/0x180E10E4' */
extern uint32_T BCU_FaultInfoLv2H;     /* '<S2>/0x180F10E4' */
extern uint32_T BCU_FaultInfoLv2L;     /* '<S2>/0x180F10E4' */
extern uint32_T BCU_FaultInfoLv3H;     /* '<S2>/0x181010E4' */
extern uint32_T BCU_FaultInfoLv3L;     /* '<S2>/0x181010E4' */
extern uint32_T BCU_FaultInfoLv4H;     /* '<S2>/0x181110E4' */
extern uint32_T BCU_FaultInfoLv4L;     /* '<S2>/0x181110E4' */
extern uint16_T BCU_SOC;               /* '<S2>/Data Type Conversion35' */
extern uint16_T BCU_SystemStatus;      /* '<S2>/Constant' */
extern uint16_T BCU_SystemWorkMode;    /* '<S2>/0x180110E4' */
extern uint8_T BCU_TimeDay;            /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeHour;           /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeMinute;         /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeMonth;          /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeSencond;        /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeWeek;           /* '<S2>/0x180110E2' */
extern uint8_T BCU_TimeYear;           /* '<S2>/0x180110E2' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<S2>/Data Type Conversion25' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion26' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion33' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion34' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion70' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion73' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion79' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion9' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'bms'
 * '<S1>'   : 'bms/Chart1'
 * '<S2>'   : 'bms/Subsystem'
 * '<S3>'   : 'bms/Subsystem1'
 * '<S4>'   : 'bms/Subsystem/MATLAB Function'
 * '<S5>'   : 'bms/Subsystem/MATLAB Function1'
 * '<S6>'   : 'bms/Subsystem/MATLAB Function2'
 * '<S7>'   : 'bms/Subsystem/MATLAB Function3'
 * '<S8>'   : 'bms/Subsystem/Write Measurement'
 * '<S9>'   : 'bms/Subsystem/Write Measurement1'
 * '<S10>'  : 'bms/Subsystem/Write Measurement10'
 * '<S11>'  : 'bms/Subsystem/Write Measurement11'
 * '<S12>'  : 'bms/Subsystem/Write Measurement12'
 * '<S13>'  : 'bms/Subsystem/Write Measurement13'
 * '<S14>'  : 'bms/Subsystem/Write Measurement14'
 * '<S15>'  : 'bms/Subsystem/Write Measurement15'
 * '<S16>'  : 'bms/Subsystem/Write Measurement16'
 * '<S17>'  : 'bms/Subsystem/Write Measurement17'
 * '<S18>'  : 'bms/Subsystem/Write Measurement2'
 * '<S19>'  : 'bms/Subsystem/Write Measurement3'
 * '<S20>'  : 'bms/Subsystem/Write Measurement4'
 * '<S21>'  : 'bms/Subsystem/Write Measurement5'
 * '<S22>'  : 'bms/Subsystem/Write Measurement6'
 * '<S23>'  : 'bms/Subsystem/Write Measurement7'
 * '<S24>'  : 'bms/Subsystem/Write Measurement8'
 * '<S25>'  : 'bms/Subsystem/Write Measurement9'
 */
#endif                                 /* RTW_HEADER_bms_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
