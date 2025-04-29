/*
 * bms_cortol.h
 *
 *  Created on: 2024锟斤拷1锟斤拷22锟斤拷
 *      Author: 30822
 */

#ifndef BMS_BMS_CORTOL_H_
#define BMS_BMS_CORTOL_H_

#define BMS_POWER_ON 0x01
#define BMS_POWER_OFF 0x02
#define BMS_POWER_URGENCY_OFF 0x04
#define BMS_POWER_UPDATING 0x05
#define BMS_POWER_DEFAULT 0x00

void set_charger_cmd(unsigned char chargecmd);
unsigned char  get_charger_cmd(void);
#endif /* BMS_BMS_CORTOL_H_ */
