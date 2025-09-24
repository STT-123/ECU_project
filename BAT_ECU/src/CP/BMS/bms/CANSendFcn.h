/*
 * File: CANSendFcn.h
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

#ifndef CANSendFcn_h_
#define CANSendFcn_h_
#ifndef CANSendFcn_COMMON_INCLUDES_
#define CANSendFcn_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
// #include "can_fd_message.h"
#endif                                 /* CANSendFcn_COMMON_INCLUDES_ */

#include "CANSendFcn_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* user code (top of header file) */
#include "C_ModbusServer.h"

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int_T CANFDPack_ModeSignalID;        /* '<Root>/CAN FD Pack' */
} DW_CANSendFcn_T;

/* Real-time Model Data Structure */
struct tag_RTM_CANSendFcn_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_CANSendFcn_T CANSendFcn_DW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T OTA_XCPConnect;         /* '<Root>/OTA_XCPConnect' */
extern uint8_T TCU_ACMuteSet;          /* '<Root>/TCU_ACMuteSet' */
extern uint32_T TCU_BCUEINSet;         /* '<Root>/TCU_BCUEINSet' */
extern uint8_T TCU_ChargerWorkSts;     /* '<Root>/TCU_ChargerWorkSts' */
extern uint8_T TCU_ECOMode;            /* '<Root>/TCU_ECOMode' */
extern uint8_T TCU_FcnStopSet;         /* '<Root>/TCU_FcnStopSet' */
extern uint8_T TCU_HighVoltType;       /* '<Root>/TCU_HighVoltType' */
extern uint16_T TCU_HighVoltValue;     /* '<Root>/TCU_HighVoltValue' */
extern uint8_T TCU_LifeCounter;        /* '<Root>/TCU_LifeCounter' */
extern uint8_T TCU_PowerUpCmd;         /* '<Root>/TCU_PowerUpCmd' */
extern uint8_T TCU_TimeCalFlg;         /* '<Root>/TCU_TimeCalFlg' */
extern uint8_T TCU_TimeDay;            /* '<Root>/TCU_TimeDay' */
extern uint8_T TCU_TimeHour;           /* '<Root>/TCU_TimeHour' */
extern uint8_T TCU_TimeMinute;         /* '<Root>/TCU_TimeMinute' */
extern uint8_T TCU_TimeMonth;          /* '<Root>/TCU_TimeMonth' */
extern uint8_T TCU_TimeSecond;         /* '<Root>/TCU_TimeSecond' */
extern uint8_T TCU_TimeWeek;           /* '<Root>/TCU_TimeWeek' */
extern uint8_T TCU_TimeYear;           /* '<Root>/TCU_TimeYear' */
extern CAN_FD_MESSAGE_BUS CANSendMsg;  /* '<Root>/CANSendMsg' */

/* Model entry point functions */
extern void CANSendFcn_initialize(void);
extern void bms_CANSendFcn(void);
extern void CANSendFcn_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CANSendFcn_T *const CANSendFcn_M;

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
 * '<Root>' : 'CANSendFcn'
 */
#endif                                 /* CANSendFcn_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
