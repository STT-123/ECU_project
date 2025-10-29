#define _GNU_SOURCE
#include "C_ModbusServer.h"

#include "log/log.h"
#include "../GLB/G_AddressDefinition.h"

#include "../GLB/G_GloabalVariable.h"
#include "./GLB/G_SystemConf.h"
#include "C_BMSAnalysis.h"
#include "C_ModbusServer_Handle.h"

#include "main.h"

// modbus服务器信息
modbus_t *ctx = NULL;
modbus_mapping_t *mb_mapping;
unsigned char modbus_ip[16] = "192.168.1.110";
const uint16_t REGISTERS_START_ADDRESS = 0x3000; // 寄存器起始地址
extern unsigned short ota_flag;
uint16_t *modbusBuff = NULL;

// modbus连接超时标志
static int timeout_flag = 0;
int get_timeout_flag()
{
    return timeout_flag;
}

// modbus接收数据处理，只处理06的写入操作
static void CP_modbus_write_reg_deal(modbus_t *ctx, const uint8_t *query, int req_length)
{
    int header_length = 0;
    unsigned short data = 0;
    unsigned short address = 0;

    // 获取数据长度
    header_length = modbus_get_header_length(ctx);

    if (query[header_length] == 0x06) // 功能码
    {
        if (req_length < 12)
        {
            return; // 长度不够直接退出
        }

        // 获取目标地址和数据
        address = (query[header_length + 1] << 8) | query[header_length + 2];
        data = (query[header_length + 3] << 8) | query[header_length + 4];

        // 判断地址范围
        if ((address >= REGISTERS_START_ADDRESS) && (address < (REGISTERS_START_ADDRESS + REGISTERS_NB)))
        {
            // 开关机操作
            if ((address == 0x6700) && (otactrl.UpDating == 0)) // 过滤，自己需要判断是否在升级来进行自主上下电
            {
                if (data == 0)
                {
                    if(ota_flag != OTASTARTRUNNING)
                    {
                        CP_set_TCU_PowerUpCmd(BMS_POWER_ON);
                        printf("1CP_get_TCU_PowerUpCmd(BMS_POWER_ON) = %d\r\n",(int)CP_get_TCU_PowerUpCmd());
                    }
                    // if ((CP_get_emcu_fault(ALL_FAULT) == 0)) // 1130(增加升级不能开机命令)
                    // {
                    //     CP_set_TCU_PowerUpCmd(BMS_POWER_ON);
                    // }
                }
                else if (data == 1)
                {
                    CP_set_TCU_PowerUpCmd(BMS_POWER_OFF);
                    printf("2CP_get_TCU_PowerUpCmd(BMS_POWER_ON) = %d\r\n",(int)CP_get_TCU_PowerUpCmd());
                }
            }
            // RTC时间设置
            else if (address >= 0x6705 && address <= 0x670A)
            {
                CP_RTC_ModBus_Deal(address, data);
            }
            // 设置ip
            else if (address == 0x6711 || address == 0x6712)
            {
                G_ip_set_deal(address, data);
            }
            // 重启
            else if ((address == 0x6720) && (data == 1))
            {
                CP_set_ems_bms_reboot();
            }
            else if ((address == 0x6718))
            {
                if (data == 0)
                {
                    CP_set_modbus_reg_val(0x3418, 0);
                    CP_set_TCU_ECOMode(0);
                }
                else if (data == 1)
                {
                    CP_set_modbus_reg_val(0x3418, 1);
                    CP_set_TCU_ECOMode(1);
                }
            }
            else if ((address == 0x6719) || (address == 0x6734) || (address == 0x6735))
            {
                VoltageCalibration_ModBus_Deal(address, data);
            }
            else if (address == 0x6714)
            {
                CP_BatteryCalibration_ModBus_Deal(address, data);
            }
            else if (address == 0x6715)
            {
                CP_BatteryCalibration_ModBus_Deal(address, data);
            }
            else if (address == 0x6719)
            {
                CP_set_modbus_reg_val(address, data);
                CP_set_TCU_FcnStopSet(data);
            }
            else if (address == 0x6721)
            {
                CP_set_modbus_reg_val(address, data);
            }
        }
    }
}

static int set_ip_address(const char *if_name, const char *ip_addr)
{
    int fd;
    struct ifreq ifr;
    struct sockaddr_in sin;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ - 1);

    memset(&sin, 0, sizeof(struct sockaddr));
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr, &sin.sin_addr);
    memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));

    if (ioctl(fd, SIOCSIFADDR, &ifr) < 0)
    {
        perror("SIOCSIFADDR");
        close(fd);
        return -1;
    }

    // 设置网口状态为 up
    if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0)
    {
        perror("SIOCGIFFLAGS");
        close(fd);
        return -1;
    }

    ifr.ifr_flags |= IFF_UP | IFF_RUNNING;

    if (ioctl(fd, SIOCSIFFLAGS, &ifr) < 0)
    {
        perror("SIOCSIFFLAGS");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

void *CP_ModbusTCPServer(void *arg)
{
    int rc;
    fd_set refset;
    fd_set rdset;
    int fdmax;
    int server_socket;
    int master_socket;

    // 创建modbus服务端
    if (setting.flag == 1 && setting.ip != 0)
    {
        sprintf(modbus_ip, "%d.%d.%d.%d", (setting.ip >> 24) & 0xFF, (setting.ip >> 16) & 0xFF, (setting.ip >> 8) & 0xFF, setting.ip & 0xFF);
    }
    set_ip_address("eth1", modbus_ip);
    ctx = modbus_new_tcp(modbus_ip, 502);
    LOG("ctx =%d ,modbus ip =%s \r\n", ctx, modbus_ip);

    
    mb_mapping = modbus_mapping_new_start_address(0, 0, 0, 0, REGISTERS_START_ADDRESS, REGISTERS_NB, 0, 0);
    if (mb_mapping == NULL)
    {
        LOG("Failed to allocate the mapping: %s \r\n", modbus_strerror(errno));
        modbus_free(ctx);
        for (;;)
        {
            usleep(5000);
        }
    }

    // 全局 外部在用
    modbusBuff = mb_mapping->tab_registers;

    // 填充部分信息
    int i;
    for (i = 0; i < 2; i++)
    {
        mb_mapping->tab_registers[i] = 10;
    }
    mb_mapping->tab_registers[MDBUS_ADDR_PRODUCTION - REGISTERS_START_ADDRESS] = 0x9528;       // 智充
    mb_mapping->tab_registers[MDBUS_ADDR_ECU_VERSION - REGISTERS_START_ADDRESS] = ECU_VERSION; // 版本号

    // 开启监听
    server_socket = modbus_tcp_listen(ctx, NB_CONNECTION);
    FD_ZERO(&refset);
    FD_SET(server_socket, &refset);
    fdmax = server_socket;

    struct timeval timeout;
    for (;;)
    {
        // 获取modbus消息
        timeout.tv_sec = 10; // 超时时间 10 秒
        timeout.tv_usec = 0;
        rdset = refset;
        if (select(fdmax + 1, &rdset, NULL, NULL, &timeout) == 0)
        {
            timeout_flag = 1;
            for (master_socket = 0; master_socket <= fdmax; master_socket++)
            {
                if (FD_ISSET(master_socket, &refset) && master_socket != server_socket)
                {
                    printf("Closing connection on socket %d\n", master_socket);
                    close(master_socket); // 关闭服务器套接字
                    FD_CLR(master_socket, &refset);
                    if (master_socket == fdmax)
                    {
                        fdmax--;
                    }
                }
            }
        }
        else
        {
            timeout_flag = 0;
        }

        // 处理消息
        for (master_socket = 0; master_socket <= fdmax; master_socket++)
        {
            if (FD_ISSET(master_socket, &rdset))
            {
                if (master_socket == server_socket)
                {
                    /* A client is asking a new connection */
                    socklen_t addrlen;
                    struct sockaddr_in clientaddr;
                    int newfd;

                    /* Handle new connections */
                    addrlen = sizeof(clientaddr);
                    memset(&clientaddr, 0, sizeof(clientaddr));
                    newfd = accept(server_socket, (struct sockaddr *)&clientaddr, &addrlen);
                    if (newfd == -1)
                    {
                        printf("Server accept() error: %s\n", strerror(errno));
                        for (master_socket = 0; master_socket <= fdmax; master_socket++)
                        {
                            if (FD_ISSET(master_socket, &refset) && master_socket != server_socket)
                            {
                                printf("Closing connection on socket %d\n", master_socket);
                                close(master_socket); // 关闭服务器套接字
                                FD_CLR(master_socket, &refset);
                                if (master_socket == fdmax)
                                {
                                    fdmax--;
                                }
                            }
                        }
                        usleep(1000);
                    }
                    else
                    {
                        FD_SET(newfd, &refset);
                        if (newfd > fdmax)
                        {
                            /* Keep track of the maximum */
                            fdmax = newfd;
                        }
                        printf("New connection from %s:%d on socket %d \r\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port, newfd);
                    }
                }
                else
                {
                    /* An already connected master has sent a new query */
                    unsigned char query[MODBUS_TCP_MAX_ADU_LENGTH];

                    modbus_set_socket(ctx, master_socket);

                    rc = modbus_receive(ctx, query);
                    if (rc != -1)
                    {
                        CP_modbus_write_reg_deal(ctx, query, rc); // 写寄存器处理
                        modbus_reply(ctx, query, rc, mb_mapping); // 回复寄存器
                    }
                    else
                    {
                        printf("Connection closed or error on socket %d: %s\n", master_socket, modbus_strerror(errno));

                        // 关闭连接
                        close(master_socket);
                        FD_CLR(master_socket, &refset);

                        // 若该 socket 是当前最大值，更新 fdmax
                        if (master_socket == fdmax)
                        {
                            while (fdmax > 0 && !FD_ISSET(fdmax, &refset))
                            {
                                fdmax--;
                            }
                        }
                    }
                }
            }
        }
    }
    while (1)
    {

        usleep(5000);
    }
}
