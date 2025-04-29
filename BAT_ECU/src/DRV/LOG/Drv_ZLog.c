#include"Drv_ZLog.h"
#include "stdlib.h"
#include "unistd.h"

zlog_category_t 				*debug_out = NULL;
zlog_category_t 				*debug_printf = NULL;
zlog_category_t 				*debug_file = NULL;


#define ZLOG_LOG_FOLDER  "/usr/xcharge/log" 

int output(zlog_msg_t *msg)
{
    unsigned char * pbuff=NULL;
    unsigned char buff_date[512+1];
//    printf("[mystd]:[%s][%s][%ld]\n", msg->path, msg->buf, (long)msg->len);

//[mystd]:
//[ mypath debug_out 2021-06-18 10:47:12]
//[2021-06-18 10:47:12 INFO [1254:User/main.c:83]  debug_out hello, zlog 123]
//[74]
    if(msg->len > 512)
    {
        pbuff =  malloc(msg->len+1);
        if(pbuff !=NULL)
        {
            memcpy(( void *)pbuff,(const void *)msg->buf,msg->len);
            pbuff[msg->len] =0x00;
            zlog_info(debug_printf, "%s",pbuff);
            zlog_info(debug_file, "%s",pbuff);
            free(pbuff);
        }
    }else{
        memcpy(( void *)buff_date,(const void *)msg->buf,msg->len);
        buff_date[msg->len] =0x00;
        zlog_info(debug_printf, "%s",buff_date);
        zlog_info(debug_file, "%s",buff_date);
    }


return 0;
}
int app_zlog_init()
{
	int rc;
	if(F_OK != access(ZLOG_LOG_FOLDER,0))
	{
		system("mkdir "ZLOG_LOG_FOLDER); //创建文件夹
	}
	rc = zlog_init(ZLOG_CONF_PATH);
	if (rc) {
		printf("zlog init failed %d\n",rc);
		return -1;
	}
	zlog_set_record("myoutput", output); //调用zlog_info(debug_out, "hello, zlog"); 会进入output回调
	debug_out = zlog_get_category("debug_out");
	if (!debug_out) {
		printf("zlog get debug_out fail\n");
		zlog_fini();
		return -2;
	}
	debug_printf = zlog_get_category("debug_printf");
	if (!debug_printf) {
		printf("zlog get debug_printf fail\n");
		zlog_fini();
		return -3;
	}
	debug_file = zlog_get_category("debug_file");
	if (!debug_file) {
		printf("zlog get debug_file fail\n");
		zlog_fini();
		return -3;
	}
//		zlog_trace(zc, "hello, zlog - trace");
//
//		zlog_debug(zc, "hello, zlog - debug");

//	zlog_info(zc2, "hello, zlog - info");
//	zlog_info(zc1, "hello, zlog - info");

//	zlog_fini();

	return 0;
}

