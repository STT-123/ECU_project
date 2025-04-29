/*
 * File: set_bms_cmd.c
 *
 * Code generated for Simulink model 'bms'.
 *
 * Model version                  : 1.224
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Mar  5 11:53:18 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bms.h"
#include "set_bms_cmd.h"
#include "rtwtypes.h"
#include "./CP/Modbus/C_ModbusServer_Handle.h"
#include "DRV/Drv_ECUAndBCUCommunication.h"
#include "../../CP/OTA/C_OTAOtherUpdate.h"
#include "../../CP/OTA/C_OTAUDSUpdate.h"
#include "../../CP/OTA/C_OTAXCPUpdate.h"
 signed char GetXCPOTAStatus(void);
/* Output and update for atomic system: '<Root>/set_bms_cmd' */
CAN_MESSAGE_BUS bmdcmd ;
uint8_T CCaller;                     /* '<S3>/C Caller' */
uint8_t ECOstate;
uint8_t Offgridstate;
void bms_set_bms_cmd(void)
{

  /* CCaller: '<S3>/C Caller' */
 CCaller = get_charger_cmd();

  /* S-Function (scanpack): '<S3>/0x1801E410' */
  /* S-Function (scanpack): '<S3>/0x1801E410' */
  bmdcmd.ID = 402777104U;
  bmdcmd.Length = 8U;
  bmdcmd.Extended = 1U;
  bmdcmd.Remote = 0;
//  bmdcmd.Data[0] = 0;
  bmdcmd.Data[1] = 0;
  bmdcmd.Data[2] = 0;
  bmdcmd.Data[3] = 0;
  bmdcmd.Data[4] = 0;
  bmdcmd.Data[5] = 0;
  bmdcmd.Data[6] = 0;
  bmdcmd.Data[7] = 0;

  {
	  bmdcmd.Data[0] = (bmdcmd.Data[0] +1) % 255;
//	  printf(" bmdcmd.Data[0]:%u\r\n",bmdcmd.Data[0]);
    /* --------------- START Packing signal 0 ------------------
     *  startBit                = 52
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 1 ------------------
     *  startBit                = 50
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 2 ------------------
     *  startBit                = 48
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 3 ------------------
     *  startBit                = 0
     *  length                  = 8
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 4 ------------------
     *  startBit                = 14
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
	  int ret = CP_get_modbus_reg_val(0x3418,&ECOstate);
	  CP_get_modbus_reg_val(0x6719,&Offgridstate);
	  {
      uint32_T packingValue = 0;

      uint8_T ECOmodeValue = 0;

      {
        uint32_T result = (uint32_T) (CCaller);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (uint8_T)(5)) {
          packedValue = (uint8_T) 5;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
        	  bmdcmd.Data[1] = packedValue;

        	  if(ECOstate == 1)
        	  {
        		  ECOmodeValue |= (1 << 2);
        	  }
        	  else
        	  {
        		  ECOmodeValue &= ~(1 << 2);
        	  }
        	  bmdcmd.Data[2] = ECOmodeValue;
        	  bmdcmd.Data[3] = Offgridstate;
          }
        }
      }
    }

    /* --------------- START Packing signal 5 ------------------
     *  startBit                = 16
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 6 ------------------
     *  startBit                = 34
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 7 ------------------
     *  startBit                = 36
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 8 ------------------
     *  startBit                = 38
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 9 ------------------
     *  startBit                = 40
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 10 ------------------
     *  startBit                = 42
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 11 ------------------
     *  startBit                = 44
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 12 ------------------
     *  startBit                = 18
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 13 ------------------
     *  startBit                = 20
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 14 ------------------
     *  startBit                = 22
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 15 ------------------
     *  startBit                = 24
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 16 ------------------
     *  startBit                = 26
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 17 ------------------
     *  startBit                = 28
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 18 ------------------
     *  startBit                = 30
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/

    /* --------------- START Packing signal 19 ------------------
     *  startBit                = 32
     *  length                  = 2
     *  desiredSignalByteLayout = BIGENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
  }

  /* CCaller: '<S3>/C Caller1' incorporates:
   *  Constant: '<S3>/Constant'
   */
  //CANSendMsg(1U, &bmdcmd);
  //bms_cmd_send(&bmdcmd);
  if((0!=GetXCPOTAStatus()))
  	{
      can1_send(&bmdcmd);
  	}
//  if((0!=GetXCPOTAStatus())&&(xQueue_forward_can_in2out!=NULL))//转发CMD
//  	{
//  		xQueueSend(xQueue_forward_can_in2out,&bmdcmd,100/portTICK_PERIOD_MS);
//  	}
  //xQueueSend(xQueue_forward_can_out2in, &bmdcmd,100/portTICK_PERIOD_MS);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
/*
 * 获取XCP OTA状态
 * 返回值 0 表示正在进行CAN XCP传输
 * 		 -1 表示未进行CAN XCP传输
 * */

 signed char GetXCPOTAStatus(void)
 {
	 if((xcpstatus.CANStartOTA == 1) || (udsstatus.CANStartOTA == 1) || (independentStatus.CANStartOTA == 1))
	 {
		 return 0;
	 }
	 else
	 {
		 return -1;
	 }


 }
