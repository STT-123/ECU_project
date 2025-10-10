/*
 * File: CANRcvFcn_data.c
 *
 * Code generated for Simulink model 'CANRcvFcn'.
 *
 * Model version                  : 5.4
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Sep 26 17:36:05 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CANRcvFcn.h"

/* Invariant block signals (default storage) */
const ConstB_CANRcvFcn_T CANRcvFcn_ConstB = {
  0U,                                  /* '<S6>/Gain30' */
  0U,                                  /* '<S6>/Gain31' */
  0U,                                  /* '<S6>/Gain25' */
  0U,                                  /* '<S6>/Add8' */
  0U,                                  /* '<S6>/Gain26' */
  0U,                                  /* '<S6>/Add9' */
  1U,                                  /* '<S6>/Saturation5' */
  0U,                                  /* '<S6>/Subtract5' */
  0U,                                  /* '<S6>/Data Type Conversion67' */
  1U,                                  /* '<S6>/Saturation6' */
  0U,                                  /* '<S6>/Subtract6' */
  0U,                                  /* '<S6>/Data Type Conversion68' */
  0U,                                  /* '<S6>/Data Type Conversion65' */
  0U,                                  /* '<S6>/Data Type Conversion72' */
  false,                               /* '<S12>/Data Type Conversion27' */
  false,                               /* '<S12>/Data Type Conversion28' */
  false,                               /* '<S12>/Data Type Conversion29' */
  false,                               /* '<S12>/Data Type Conversion30' */
  false                                /* '<S12>/Data Type Conversion38' */
};

/* Constant parameters (default storage) */
const ConstP_CANRcvFcn_T CANRcvFcn_ConstP = {
  /* Computed Parameter: index_Value
   * Referenced by: '<Root>/index'
   */
  { 12289U, 12324U, 12307U, 12308U, 12548U, 0U, 12325U, 12321U, 12323U, 12417U,
    12418U, 12416U, 12420U, 12421U, 12419U, 12326U, 12423U, 12425U, 12424U,
    12426U, 12427U, 12428U, 12429U, 12430U, 12431U, 12432U, 12433U, 12369U,
    12370U, 12371U, 12372U, 12365U, 12366U, 12367U, 12368U, 12361U, 12362U,
    12363U, 12364U, 12357U, 12358U, 12359U, 12436U, 12435U, 12434U, 12292U,
    12293U, 12288U, 0U, 12438U, 12439U, 0U, 12440U, 12437U, 12301U, 12302U,
    12304U, 12305U, 0U, 0U, 0U, 0U, 0U, 0U, 12310U, 12309U, 12312U, 12311U,
    12387U, 12384U, 12385U, 12290U, 12449U, 12450U, 12451U, 12447U, 12448U,
    12296U, 12299U, 12298U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 12360U, 13312U,
    12800U, 12295U, 0U, 0U, 0U, 6944U, 6976U, 6950U, 6948U, 6949U, 12319U, 6952U,
    6951U, 6958U, 6961U, 6965U, 12550U, 12549U, 12551U, 12388U, 12389U, 6963U,
    14114U, 14115U, 12552U, 0U, 12452U, 12547U, 12546U, 12545U, 0U, 0U, 0U,
    1120U, 1121U, 1129U, 1128U, 1127U, 1126U, 1122U, 1123U, 8192U, 8193U, 8194U,
    8195U, 8196U, 8197U, 8198U, 8199U, 8200U, 8201U, 8202U, 8203U, 8204U, 8205U,
    8206U, 7004U, 7005U, 7006U, 7007U, 7008U, 7009U, 7010U, 7011U, 7012U, 7013U,
    7014U, 7015U, 7016U, 7017U, 7018U, 7019U, 7020U, 7021U, 7022U, 7023U, 7024U,
    7025U, 7026U, 7027U, 7028U, 7029U, 7030U, 7031U, 7032U, 7033U, 7034U, 7035U,
    7036U, 7037U, 7038U, 7039U, 7040U, 7041U, 7042U, 7043U, 7044U, 7045U, 7046U,
    7047U, 7048U, 7049U, 7050U, 7051U, 7052U, 7053U, 7054U, 7055U, 7056U, 7057U,
    7058U, 7059U, 7060U, 7061U, 7062U, 7063U },

  /* Computed Parameter: portDimensions_Value
   * Referenced by: '<Root>/portDimensions'
   */
  { 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 15U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 120U, 240U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 15U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U,
    1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
