#include "C_BMSAnalysis.h"
#include "./bms/bms.h"
#include "./bms/bms_cortol.h"
#include "./bms/set_bms_cmd.h"
static unsigned char bms_cmd = BMS_POWER_DEFAULT;
bool CP_BMSAnalysis(void)
{
    bool state = false;
    bms_step();
    state = true;
    return state;
}

void CP_set_charger_cmd(unsigned char chargecmd)
{
    // bool state = false;
    // bms_set_charger_cmd(cmd);
    // state = true;
    // return state;
    bms_cmd = chargecmd;
}

unsigned char CP_get_charger_cmd(void)
{
    // bool state = false;
    // *cmd = bms_get_charger_cmd();
    // state = true;
    // return state;
    return bms_cmd;
}

bool CP_bms_set_bms_cmd(void)
{
    bool state = false;
    bms_set_bms_cmd();
    state = true;
    return state;
}
