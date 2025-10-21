#ifndef LOG_H__
#define LOG_H__

#include "zlog.h"

/*
    ！！！！！！！！！！！！！！！！！！！！！！！！ 此文件 禁止格式化 ！！！！！！！！！！！！！！！！！！！！！！！！
*/

#define ZLOG_CONF_FILE_PATH "/usr/xcharge/zlog.conf"    // zlog 配置文件地址
#define ZLOG_DATA_FILE_PATH "/usr/xcharge/log"          // zlog 日志存放地址

zlog_category_t *log_printf;    // 终端
zlog_category_t *log_record;    // 通用日志
zlog_category_t *log_csv;       // csv文件

// 对外提供的宏定义
#define LOG(fmt, ...)       {zlog_info(log_record, fmt, ##__VA_ARGS__); zlog_info(log_printf, fmt, ##__VA_ARGS__);}
#define LOG_CSV(fmt, ...)   {zlog_info(log_csv, fmt, ##__VA_ARGS__); zlog_info(log_printf, fmt, ##__VA_ARGS__);}

int log_init(void);
void ascill_to_string(unsigned char *data, unsigned int data_len, char *string_ptr, int string_len);

#endif /* LOG_H__ */