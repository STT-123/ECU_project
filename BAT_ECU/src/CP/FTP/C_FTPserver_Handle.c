#include "C_FTPserver_Handle.h"

#define DATA_PORT 40900
#define BUFFER_SIZE 2920 // 2048 网络传输包mtu限制改为1460得倍数
#define TIMEOUT_SECONDS 300000

void send_response(int sock, const char *message)
{
    send(sock, message, strlen(message), 0);
}

// 更新最后活动时间
void update_last_activity(FTPState *state)
{
    state->last_activity = time(NULL);
}

// 检查是否超时
void check_timeouts(FTPState *state)
{
    time_t current_time = time(NULL);
    if ((current_time - state->last_activity) > TIMEOUT_SECONDS)
    {
        close(state->control_sock);
        close(state->data_sock);
        state->control_sock = -1;
        state->data_sock = -1;
        printf("Connection timed out.\n");
    }
}

// 处理 USER 命令
void handle_user_command(FTPState *state, char *args)
{
    update_last_activity(state);
    send_response(state->control_sock, "331 Username OK, need password.\r\n");
}

// 处理 PASS 命令
// void handle_pass_command(FTPState *state, char *args) {
//     update_last_activity(state);
//     state->logged_in = 1;
//     send_response(state->control_sock, "230 Login successful.\r\n");
// }
// 处理 PASS 命令
void handle_pass_command(FTPState *state, char *args)
{
    update_last_activity(state);
    state->logged_in = 1;

    // 切换到 U 盘挂载目录
    // if (chdir("/media/usb0") != 0) {
    if (chdir("/mnt/sda") != 0)
    {
        printf("Failed to change to USB directory: %s\n", strerror(errno));
        send_response(state->control_sock, "550 Failed to access USB directory.\r\n");
        return;
    }

    send_response(state->control_sock, "230 Login successful.\r\n");
}

void handle_pasv_command(FTPState *state)
{
    update_last_activity(state);

    struct timeval timeout;
    // int ip[4];
    // ip[0] = (setting.ip >> 24) & 0xFF;
    // ip[1] = (setting.ip >> 16) & 0xFF;
    // ip[2] = (setting.ip >> 8) & 0xFF;
    // ip[3] = setting.ip & 0xFF;
    int ip[4] = {192, 168, 1, 110};
    char response[BUFFER_SIZE] = {0};

    snprintf(response, sizeof(response),
             "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
             ip[0], ip[1], ip[2], ip[3], DATA_PORT / 256, DATA_PORT % 256);

    if (state->data_sock >= 0)
    {
        close(state->data_sock);
        state->data_sock = -1;
    }

    state->data_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (state->data_sock < 0)
    {
        perror("Failed to create data socket");
        return;
    }

    struct sockaddr_in data_addr;
    memset(&data_addr, 0, sizeof(data_addr));
    data_addr.sin_family = AF_INET;
    data_addr.sin_addr.s_addr = INADDR_ANY;
    data_addr.sin_port = htons(DATA_PORT);

    int opt = 1;
    if (setsockopt(state->data_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt SO_REUSEADDR");
    }

    if (bind(state->data_sock, (struct sockaddr *)&data_addr, sizeof(data_addr)) < 0)
    {
        perror("Failed to bind data socket");
        close(state->data_sock);
        state->data_sock = -1;
        return;
    }

    if (listen(state->data_sock, 2) < 0)
    {
        perror("Failed to listen on data socket");
        close(state->data_sock);
        state->data_sock = -1;
        return;
    }

    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    if (setsockopt(state->data_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
    {
        perror("Failed to set socket receive timeout");
        close(state->data_sock);
        state->data_sock = -1;
        return;
    }

    send_response(state->control_sock, response);
}

void handle_port_command(FTPState *state, char *args)
{
    update_last_activity(state);

    int ip[4];
    int port_high, port_low;

    if (sscanf(args, "%d,%d,%d,%d,%d,%d", &ip[0], &ip[1], &ip[2], &ip[3], &port_high, &port_low) != 6)
    {
        send_response(state->control_sock, "501 Syntax error in parameters or arguments.\r\n");
        return;
    }

    int port = (port_high << 8) | port_low;

    struct sockaddr_in data_addr;
    memset(&data_addr, 0, sizeof(data_addr));
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(port);

    char ip_str[INET_ADDRSTRLEN];
    snprintf(ip_str, sizeof(ip_str), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    if (inet_pton(AF_INET, ip_str, &data_addr.sin_addr) != 1)
    {
        fprintf(stderr, "Failed to convert IP address\n");
        send_response(state->control_sock, "501 Invalid IP address.\r\n");
        return;
    }

    // 关闭旧连接（如果有）
    if (state->data_sock >= 0)
    {
        close(state->data_sock);
        state->data_sock = -1;
    }

    // 创建 socket 并尝试连接客户端提供的数据端口
    state->data_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (state->data_sock < 0)
    {
        perror("Failed to create data socket");
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        return;
    }

    if (connect(state->data_sock, (struct sockaddr *)&data_addr, sizeof(data_addr)) < 0)
    {
        perror("Failed to connect to client data port");
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        close(state->data_sock);
        state->data_sock = -1;
        return;
    }

    send_response(state->control_sock, "200 PORT command successful.\r\n");
}

void handle_list_command(FTPState *state, char *args)
{
    update_last_activity(state);
    send_response(state->control_sock, "150 Here comes the directory listing.\r\n");
    printf("accept \r\n");

    int client_data_sock = accept(state->data_sock, (struct sockaddr *)&state->client_addr, &state->client_addr_len);
    printf("client_data_sock: %d\n", client_data_sock);

    if (client_data_sock < 0)
    {
        printf("Failed to accept data connection: errno=%d, %s\n", errno, strerror(errno));
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        close(state->data_sock);
        return;
    }

    DIR *dir;
    struct dirent *entry;
    char buffer[BUFFER_SIZE] = {0};
    char cwd[BUFFER_SIZE] = {0};

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Failed to get current working directory\n");
        send_response(state->control_sock, "550 Failed to get current directory.\r\n");
        close(client_data_sock);
        close(state->data_sock);
        return;
    }

    dir = opendir(cwd);
    if (!dir)
    {
        printf("Failed to open directory: %s\n", strerror(errno));
        send_response(state->control_sock, "550 Failed to open directory.\r\n");
        close(client_data_sock);
        close(state->data_sock);
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip hidden files unless "-a" is specified
        if ((!args || strcmp(args, "-a") != 0) && entry->d_name[0] == '.')
        {
            continue;
        }

        char fullpath[BUFFER_SIZE];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", cwd, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1)
        {
            printf("Failed to stat file %s\n", entry->d_name);
            continue;
        }

        if (S_ISDIR(st.st_mode))
        {
            snprintf(buffer, sizeof(buffer), "+/,\t%s\r\n", entry->d_name);
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "+r,s%ld,\t%s\r\n", st.st_size, entry->d_name);
        }

        if (send(client_data_sock, buffer, strlen(buffer), 0) < 0)
        {
            printf("Failed to send data: %s\n", strerror(errno));
            send_response(state->control_sock, "426 Connection closed; transfer aborted.\r\n");
            closedir(dir);
            close(client_data_sock);
            close(state->data_sock);
            return;
        }

        printf("sent to client_data_sock %d: %s", client_data_sock, buffer);
    }

    closedir(dir);
    close(client_data_sock);
    close(state->data_sock);
    state->data_sock = -1;

    send_response(state->control_sock, "226 Directory send OK.\r\n");
}

/*
 * ftp 开始的时候设置标志位，
 * 	然后里边调用各自的接口去实现文件的关闭
 * 	并且不允许再次去写文件。
 *
 */
static bool ftp_read_flag = false;
void set_ftp_read_file_flag(bool flag)
{
    static bool flag_last = false;
    if (flag_last == flag)
        return;

    ftp_read_flag = flag;
    flag_last = ftp_read_flag;

    // if(flag == true)
    // {
    // 	ftpread_elog_suspend();
    // }
    // else
    // {
    // 	ftpread_elog_resume();
    // }
}

bool CP_get_ftp_read_file_flag()
{
    return ftp_read_flag;
}

void handle_retr_command(FTPState *state, char *filename)
{
    send_response(state->control_sock, "150 Opening data connection.\r\n");

    int client_data_sock = accept(state->data_sock,
                                  (struct sockaddr *)&state->client_addr,
                                  &state->client_addr_len);
    if (client_data_sock < 0)
    {
        printf("Failed to accept data connection: %s\n", strerror(errno));
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        return;
    }

    printf("Accepted data connection, socket fd: %d\n", client_data_sock);
    set_ftp_read_file_flag(true); // 设置标志位阻止写文件

    printf("state->path: '%s'\n", state->path);
    printf("filename: '%s'\n", filename);

    char filebuff[512] = {0};
    snprintf(filebuff, sizeof(filebuff), "%s/%s", state->path, filename);
    printf("load file path: %s\n", filebuff);

    state->file = fopen(filebuff, "rb");
    if (!state->file)
    {
        printf("Failed to open file: %s\n", strerror(errno));
        send_response(state->control_sock, "550 File not found.\r\n");
        close(client_data_sock);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), state->file)) > 0)
    {
        update_last_activity(state);

        if (send(client_data_sock, buffer, bytes_read, 0) < 0)
        {
            printf("Failed to send data: %s\n", strerror(errno));
            break;
        }

        usleep(1000);
    }

    fclose(state->file);
    close(client_data_sock);
    close(state->data_sock);
    state->data_sock = -1;

    set_ftp_read_file_flag(false);

    send_response(state->control_sock, "226 Transfer complete.\r\n");
}

void handle_stor_command(FTPState *state, char *filename)
{
    send_response(state->control_sock, "150 Opening data connection.\r\n");

    int client_data_sock = accept(state->data_sock, (struct sockaddr *)&state->client_addr, &state->client_addr_len);
    if (client_data_sock < 0)
    {
        printf("Failed to accept data connection: %s\n", strerror(errno));
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        close(state->data_sock);
        return;
    }

    char filepath[512] = {0};
    snprintf(filepath, sizeof(filepath), "%s/%s", state->path, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file)
    {
        printf("Failed to create file: %s\n", strerror(errno));
        send_response(state->control_sock, "550 Failed to create file.\r\n");
        close(client_data_sock);
        close(state->data_sock);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_data_sock, buffer, sizeof(buffer), 0)) > 0)
    {
        update_last_activity(state);

        size_t bytes_written = fwrite(buffer, 1, bytes_received, file);
        if (bytes_written != bytes_received)
        {
            printf("Failed to write data to file: %s\n", strerror(errno));
            send_response(state->control_sock, "426 Connection closed; transfer aborted.\r\n");
            fclose(file);
            close(client_data_sock);
            close(state->data_sock);
            return;
        }
    }

    fclose(file);
    close(client_data_sock);
    close(state->data_sock);
    state->data_sock = -1;

    send_response(state->control_sock, "226 Transfer complete.\r\n");
}

void handle_mget_command(FTPState *state, char *args)
{
    send_response(state->control_sock, "150 Opening data connection.\r\n");

    int client_data_sock = accept(state->data_sock, (struct sockaddr *)&state->client_addr, &state->client_addr_len);
    if (client_data_sock < 0)
    {
        printf("Failed to accept data connection: %s\n", strerror(errno));
        send_response(state->control_sock, "425 Can't open data connection.\r\n");
        close(state->data_sock);
        return;
    }

    char filepath[512] = {0};
    snprintf(filepath, sizeof(filepath), "%s/%s", state->path, args);

    FILE *file = fopen(filepath, "rb"); // Open the file for reading
    if (!file)
    {
        printf("Failed to open file: %s\n", strerror(errno));
        send_response(state->control_sock, "550 File not found.\r\n");
        close(client_data_sock);
        close(state->data_sock);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        update_last_activity(state);
        if (send(client_data_sock, buffer, bytes_read, 0) < 0)
        {
            printf("Failed to send data: %s\n", strerror(errno));
            send_response(state->control_sock, "426 Connection closed; transfer aborted.\r\n");
            fclose(file);
            close(client_data_sock);
            close(state->data_sock);
            return;
        }
    }

    fclose(file);
    close(client_data_sock);
    close(state->data_sock);
    state->data_sock = -1;

    send_response(state->control_sock, "226 Transfer complete.\r\n");
}

void handle_pwd_command(FTPState *state)
{
    char cwd[BUFFER_SIZE];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "257 \"%s\" is the current directory.\r\n", cwd);
        send_response(state->control_sock, response);
    }
    else
    {
        send_response(state->control_sock, "550 Failed to get current directory.\r\n");
    }
}

void handle_syst_command(FTPState *state)
{
    update_last_activity(state);
    send_response(state->control_sock, "215 UNIX Type: L8\r\n");
}

void handle_cdup_command(FTPState *state)
{
    update_last_activity(state);

    // 获取当前目录
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Failed to get current directory\n");
        send_response(state->control_sock, "550 Failed to get current directory.\r\n");
        return;
    }

    // 改变目录到父级目录
    if (chdir("..") != 0)
    {
        printf("Failed to change to parent directory\n");
        send_response(state->control_sock, "550 Failed to change directory.\r\n");
    }
    else
    {
        send_response(state->control_sock, "200 Directory successfully changed.\r\n");
    }
}

void handle_cwd_command(FTPState *state, const char *args)
{
    update_last_activity(state);
    if (args == NULL)
    {
        send_response(state->control_sock, "501 Syntax error in parameters or arguments.\r\n");
        return;
    }
    // 拦截 CWD / 并重定向到 /media/usb0
    if (strcmp(args, "/") == 0)
    {
        // args = "/media/usb0";
        args = "/mnt/sda";
    }

    if (chdir(args) == 0)
    {
        send_response(state->control_sock, "250 Directory changed.\r\n");

        // 更新会话中的路径
        if (strlen(args) < sizeof(state->path))
        {
            strncpy(state->path, args, sizeof(state->path) - 1);
            state->path[sizeof(state->path) - 1] = '\0'; // 确保路径是null-terminated
        }
    }
    else
    {
        printf("Failed to change directory: %s\n", strerror(errno));
        send_response(state->control_sock, "550 Failed to change directory.\r\n");
    }
}

void handle_type_command(FTPState *state, char *args)
{
    if (args && strcmp(args, "A") == 0)
    {
        send_response(state->control_sock, "200 Type set to A.\r\n");
    }
    else if (args && strcmp(args, "I") == 0)
    {
        send_response(state->control_sock, "200 Switching to Binary mode.\r\n");
    }
    else
    {
        send_response(state->control_sock, "504 Command not implemented for that parameter.\r\n");
    }
}

int handle_ftp_commands(FTPState *state)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    update_last_activity(state);

    for (;;)
    {
        // 使用非阻塞的 recv 来避免阻塞
        while ((bytes_received = recv(state->control_sock, buffer, sizeof(buffer) - 1, 0)) > 0)
        {
            check_timeouts(state);         // 检查超时
            buffer[bytes_received] = '\0'; // 确保字符串以 \0 结束
            printf("Received command: %s\n", buffer);

            // 分割命令和参数
            char *command = strtok(buffer, " \r\n");
            char *args = strtok(NULL, "\r\n");

            // 处理 FTP 命令
            if (strcmp(command, "USER") == 0)
            {
                handle_user_command(state, args);
            }
            else if (strcmp(command, "PASS") == 0)
            {
                handle_pass_command(state, args);
            }
            else if (strcmp(command, "PASV") == 0)
            {
                handle_pasv_command(state);
            }
            else if (strcmp(command, "PORT") == 0)
            {
                handle_port_command(state, args);
            }
            else if (strcmp(command, "LIST") == 0)
            {
                if (state->logged_in)
                {
                    handle_list_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "RETR") == 0)
            {
                if (state->logged_in)
                {
                    handle_retr_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "STOR") == 0)
            {
                if (state->logged_in)
                {
                    handle_stor_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "MGET") == 0)
            {
                if (state->logged_in)
                {
                    handle_mget_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "PWD") == 0)
            {
                if (state->logged_in)
                {
                    handle_pwd_command(state);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "CWD") == 0)
            {
                if (state->logged_in)
                {
                    handle_cwd_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "TYPE") == 0)
            {
                handle_type_command(state, args);
            }
            else if (strcmp(command, "SYST") == 0)
            {
                handle_syst_command(state);
            }
            else if (strcmp(command, "NLST") == 0)
            {
                if (state->logged_in)
                {
                    handle_list_command(state, args);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else if (strcmp(command, "CDUP") == 0)
            {
                if (state->logged_in)
                {
                    handle_cdup_command(state);
                }
                else
                {
                    send_response(state->control_sock, "530 Please login with USER and PASS.\r\n");
                }
            }
            else
            {
                send_response(state->control_sock, "502 Command not implemented.\r\n");
            }
        }

        if (bytes_received == 0)
        {
            close(state->control_sock);
            close(state->data_sock);
            return 0; // 客户端断开连接
        }
        else if (bytes_received < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                close(state->control_sock);
                close(state->data_sock);
                return -1; // 非阻塞错误
            }
            else
            {
                close(state->control_sock);
                close(state->data_sock);
                return -2; // 其他错误
            }
        }
    }
}
