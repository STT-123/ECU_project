#ifndef __C_BMSANALYSIS_H__
#define __C_BMSANALYSIS_H__

#include <stdio.h>
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>




bool CP_BMSAnalysis(void);

void CP_set_charger_cmd(unsigned char chargecmd);

unsigned char CP_get_charger_cmd(void);

bool CP_bms_set_bms_cmd(void);

#endif