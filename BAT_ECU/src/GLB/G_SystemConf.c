#include "G_SystemConf.h"
#include "./GLB/G_GloabalVariable.h"
#include "log/log.h"
#include "./CP/BMS/bms/CANRcvFcn.h"
#define CONFIG_FILE_PATH "setting.conf"
Setting_t setting;

void save_setting_to_file(const char *filepath, Setting_t *setting)
{
    FILE *fp = fopen(filepath, "wb");
    if (fp)
    {
        fwrite(setting, sizeof(Setting_t), 1, fp);
        fclose(fp);
    }
    else
    {
        LOG("Failed to write setting\r\n");
    }
}

int load_setting_from_file(const char *filepath, Setting_t *setting)
{
    FILE *fp = fopen(filepath, "rb");
    if (fp)
    {
        fread(setting, sizeof(Setting_t), 1, fp);
        fclose(fp);
        return 0;
    }
    return -1;
}

void G_settings_init()
{
    memset(&setting, 0, sizeof(setting));

    struct stat st;
    int config_exist = (stat(CONFIG_FILE_PATH, &st) == 0);

    if (config_exist && load_setting_from_file(CONFIG_FILE_PATH, &setting) == 0 && setting.flag == 1)
    {
        struct in_addr addr;
        addr.s_addr = htonl(setting.ip);
        LOG("Read IP from config: %s\n", inet_ntoa(addr));
    }
    else
    {
        // 配置文件不存在或数据无效，写入默认值
        setting.flag = 1;
        setting.ip = (192 << 24) | (168 << 16) | (1 << 8) | 110;

        save_setting_to_file(CONFIG_FILE_PATH, &setting);

        struct in_addr addr;
        addr.s_addr = htonl(setting.ip);
        LOG("Default IP used and saved: %s\n", inet_ntoa(addr));
    }
}

void G_ip_set_deal(uint16_t address, uint16_t data)
{
    static uint32_t ip_addr = 0;
    if (address == 0x6711) // 高 16 位
    {
        ip_addr &= 0x0000ffff;
        ip_addr |= ((uint32_t)data) << 16;
        return;
    }
    else if (address == 0x6712) // 低 16 位
    {
        ip_addr &= 0xffff0000;
        ip_addr |= data & 0xFFFF;

        setting.ip = ip_addr;
        setting.flag = 1;

        // 显示 IP
        struct in_addr ip_struct;
        ip_struct.s_addr = htonl(ip_addr); // 转为网络字节序
        printf("Set IP to: %s\n", inet_ntoa(ip_struct));
        save_setting_to_file(CONFIG_FILE_PATH, &setting);
        usleep(500 * 1000);
        system("reboot");
    }
}

void G_set_system_time_from_bcu(void)
{
    struct tm tm;
    struct timeval tv;

    memset(&tm, 0, sizeof(struct tm));

    tm.tm_year = 2000 + BCU_TimeYear - 1900; // tm_year 是从1900年开始计数的
    tm.tm_mon = BCU_TimeMonth - 1;           // tm_mon 范围是 0-11
    tm.tm_mday = BCU_TimeDay;
    tm.tm_hour = BCU_TimeHour;
    tm.tm_min = BCU_TimeMinute;
    tm.tm_sec = BCU_TimeSencond;

    time_t t = mktime(&tm); // 转为 time_t 类型（时间戳）
    if (t == -1)
    {
        printf("Invalid time provided\n");
        return;
    }

    tv.tv_sec = t;
    tv.tv_usec = 0;

    if (settimeofday(&tv, NULL) != 0)
    {
        perror("settimeofday failed");
    }
    else
    {
        printf("System time updated to: %04d-%02d-%02d %02d:%02d:%02d\n",
               2000 + BCU_TimeYear,
               BCU_TimeMonth,
               BCU_TimeDay,
               BCU_TimeHour,
               BCU_TimeMinute,
               BCU_TimeSencond);
    }
}