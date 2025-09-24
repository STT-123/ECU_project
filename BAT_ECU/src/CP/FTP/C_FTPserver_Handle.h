#ifndef __C_FTPSERVER_HANDLE_H__
#define __C_FTPSERVER_HANDLE_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
typedef struct {
	uint32_t last_activity;
    int control_sock;
    int data_sock;
    int logged_in;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    char path[255+8];
    char newpathname[128];
    FILE *file;
    uint8_t file_interrupt_flag;
} FTPState;

void send_response(int sock, const char *message);
void handle_user_command(FTPState *state, char *args);
void handle_pass_command(FTPState *state, char *args);
void handle_pasv_command(FTPState *state);
void handle_port_command(FTPState *state, char *args);
void handle_list_command(FTPState *state, char *args);
void set_ftp_read_file_flag(bool flag);
bool CP_get_ftp_read_file_flag();
void handle_retr_command(FTPState *state, char *filename);
void handle_stor_command(FTPState *state, char *filename);
void handle_mget_command(FTPState *state, char *args);
void handle_pwd_command(FTPState *state);
void handle_syst_command(FTPState *state);
void handle_cdup_command(FTPState *state);
void handle_cwd_command(FTPState *state, const char *args);
void handle_type_command(FTPState *state, char *args);
int handle_ftp_commands(FTPState *state);
#endif