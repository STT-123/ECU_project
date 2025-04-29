#ifndef __C_S19OPERATION_H__
#define __C_S19OPERATION_H__    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define LO (0)
#define HI (1)

#define SREC_NEWLINE    (0) // Start of line
#define SREC_RECORDTYPE (1) // Sn
#define SREC_BYTECOUNT  (2) // Byte Count
#define SREC_ADDRESS    (3) // Address
#define SREC_DATA       (4) // Data
#define SREC_CHKSUM     (5) // Checksum
#define SREC_ENDOFLINE  (6) // End of a Line

#endif