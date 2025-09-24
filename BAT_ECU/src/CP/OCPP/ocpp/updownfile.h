#ifndef __UPDOWNFILE_H__
#define __UPDOWNFILE_H__


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <stdlib.h>

// 文件下载回调函数
// #define DOWNLOAD_FILENAME "/tmp/XC_ECU_DCBproject.bz2"  // 固定下载文件名
#define UPLOAD_FILE_PATH "/usr/xcharge/log/app_project.log.bz2"  // 固定上传的文件路径
#define LOG_FILE_PATH     "/usr/xcharge/log/app_project.log"
int ocpp_upload_file(const char *url);
int download_file(const char *url,const char *filetype);

#endif