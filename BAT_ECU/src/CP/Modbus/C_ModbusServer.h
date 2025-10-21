#ifndef __C_MODBUS_SERVER_H__
#define __C_MODBUS_SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./modbuslib/modbus.h"
#include "./modbuslib/modbus-tcp.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if.h>

extern uint16_t *modbusBuff;

#define NB_CONNECTION 3
extern const uint16_t REGISTERS_START_ADDRESS;
extern unsigned char modbus_ip[16];
void *CP_ModbusTCPServer(void *arg);

int get_timeout_flag();

#endif