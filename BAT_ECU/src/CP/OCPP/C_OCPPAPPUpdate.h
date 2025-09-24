#ifndef __C_OTAOCPPAPPUpdate_H
#define __C_OTAOCPPAPPUpdate_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdarg.h>  

int get_check_upgarde_file_type(const char *filename,const char *filetype,char *out_matched_filename, size_t max_len) ;
int upgarde_file_type(const char *filename,const char *filetype);
#endif