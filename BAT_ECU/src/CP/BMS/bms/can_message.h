#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_

#ifndef INVALID_CAN_ID
#define INVALID_CAN_ID                 0xFFFFFFFFU
#endif
typedef enum {CAN_MESSAGE_STANDARD, CAN_MESSAGE_EXTENDED} CanFrameType;

typedef struct
{

    /* Is Extended frame */
    uint8_T Extended;
    /* Length */
    uint8_T Length;
    /* RTR */
    uint8_T Remote;
    /* Error */
    uint8_T Error;
    /* CAN ID */
    uint32_T ID;
    /* Timestamp */
    double Timestamp;
    /* Data field */
    uint8_T Data[8];

}  CAN_MESSAGE_BUS;
typedef CAN_MESSAGE_BUS CAN_DATATYPE;


#endif
