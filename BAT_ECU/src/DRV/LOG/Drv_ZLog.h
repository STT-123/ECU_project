#ifndef _DRV_ZLOG_H_
#define _DRV_ZLOG_H_

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "zlog.h"
#include "stdint.h"
#include "stdbool.h"
extern zlog_category_t                 *debug_out ;
extern zlog_category_t                 *debug_printf ;
extern zlog_category_t                 *debug_file ;

#define ZLOG_CONF_PATH    	    "zlog.conf"   /*zlog 配置文件 */
bool debug_enabled;
#define LOG_INIT(b) {debug_enabled=b;}
int app_zlog_init();

#endif
