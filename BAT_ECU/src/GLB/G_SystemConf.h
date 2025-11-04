#ifndef __G_SystemConf_H
#define __G_SystemConf_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "stdbool.h"
#include <time.h>
#include <sys/time.h>
#include <arpa/inet.h> // for inet_ntoa etc.
#include <netinet/in.h>
#include <sys/stat.h> // stat()
void G_settings_init();
void G_ip_set_deal(uint16_t address, uint16_t data);
void G_set_system_time_from_bcu(void);
#endif