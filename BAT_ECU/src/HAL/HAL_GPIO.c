
#include "HAL_GPIO.h"
#include "./DRV/LOG/Drv_ZLog.h"
#define SYSFS_GPIO_DIR "/sys/class/gpio"
/*********************************************************************************************************
**  @FunctionName               GPIO_Export
**  @Description                GPIO export
**  @InputParam                 pin:     	IO端口号
**  @OutputParam                NONE
**  @ReturnValue                -1:        失败
**                               0:        成功
// *********************************************************************************************************/
int HAL_GPIO_Export(int pin)
{
	char buffer[64];
	int len = 0;
	int fd = -1;
	// zlog_info(debug_out,"gpio_export pin num is:%d\n", pin);
	memset(buffer, 0, sizeof(buffer));
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if(fd < 0)
	{
		zlog_info(debug_out,"Failed to open export for writing!\n");
		return(-1);
	}
	else
	{
		zlog_info(debug_out,"success Exporting GPIO %d\n", pin);
	}

	len = snprintf(buffer, sizeof(buffer), "%d", pin);
    // zlog_info(debug_out,"snprintf len is:%d\n", len);
	if(write(fd, buffer, len) < 0)
	{
		zlog_info(debug_out,"Failed to export gpio!");
		return -1;
	}

	close(fd);
	return 0;
}
// int HAL_GPIO_Export(int pin)
// {
//     char buffer[64];
//     char path[64];
//     int len = 0;
//     int fd = -1;

//     // 如果已导出则跳过
//     snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d", pin);
//     if (access(path, F_OK) == 0) {
//         zlog_info(debug_out, "GPIO %d already exported\n", pin);
//         return 0;
//     }

//     fd = open("/sys/class/gpio/export", O_WRONLY);
//     if (fd < 0)
//     {
//         zlog_info(debug_out, "Failed to open export for writing!\n");
//         return -1;
//     }

//     len = snprintf(buffer, sizeof(buffer), "%d", pin);
//     if (write(fd, buffer, len) < 0)
//     {
//         zlog_info(debug_out, "Failed to export gpio %d, errno = %d (%s)\n", pin, errno, strerror(errno));
//         close(fd);
//         return -1;
//     }

//     close(fd);
//     return 0;
// }


/*********************************************************************************************************
**  @FunctionName               GPIO_Unexport
**  @Description                GPIO Unexport
**  @InputParam                 pin:     	IO端口号
**  @OutputParam                NONE
**  @ReturnValue                -1:        失败
**                               0:        成功
*********************************************************************************************************/
int HAL_GPIO_Unexport(int pin)
{
	char buffer[64];
	int len = 0;
	int fd = -1;
	zlog_info(debug_out,"gpio_unexport pin num is:%d\n", pin);
	memset(buffer, 0, sizeof(buffer));
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if(fd < 0)
	{
		zlog_info(debug_out,"Failed to open unexport for writing!\n");
		return -1;
	}

	len = snprintf(buffer, sizeof(buffer), "%d", pin);
	zlog_info(debug_out,"snprintf len is:%d\n", len);
	if(write(fd, buffer, len) < 0)
	{
		zlog_info(debug_out,"Failed to unexport gpio!");
		return -1;
	}

	close(fd);
	return 0;
}

/*********************************************************************************************************
**  @FunctionName               GPIO_Direction
**  @Description                GPIO 设置io方向
**  @InputParam                 pin:     	IO端口号
**  							dir:		IO端口方向	0-->IN, 1-->OUT
**  @OutputParam                NONE
**  @ReturnValue                -1:        失败
**                               0:        成功
*********************************************************************************************************/
int HAL_GPIO_Direction(int pin, int dir)
{
	static const char dir_str[] = "in\0out";
	char path[64];
	int fd = -1;
	// zlog_info(debug_out,"gpio_direction pin num is:%d\n", pin);
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if(fd < 0)
	{
		zlog_info(debug_out,"Failed to open gpio direction for writing!\n");
		return -1;
	}

	if(write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0)
	{
		zlog_info(debug_out,"Failed to set direction!\n");
		return -1;
	}
	else
	{
		zlog_info(debug_out,"success setting GPIO %d to %s\n", pin, &dir_str[dir == 0 ? 0 : 3]);
	}

	close(fd);
	return 0;
}

/*********************************************************************************************************
**  @FunctionName               GPIO_Write
**  @Description                GPIO 设置输出
**  @InputParam                 pin:     	IO端口号
**  							value:		IO端口	0-->LOW, 1-->HIGH
**  @OutputParam                NONE
**  @ReturnValue                -1:        失败
**                               0:        成功
*********************************************************************************************************/
int HAL_GPIO_Write(int pin, int value)
{
	static const char values_str[] = "01";
	char path[64];
	int fd = -1;
//	zlog_info(debug_out,"gpio_write pin num is:%d state:%d\n", pin, value);
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if(fd < 0)
	{
		zlog_info(debug_out,"Failed to open gpio value for writing!\n");
		zlog_info(debug_out,"gpio_write pin num is:%d\n", pin);
		return -1;
	}

	if(write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0)
	{
		zlog_info(debug_out,"Failed to write value!\n");
		return -1;
	}

	close(fd);
	return 0;
}

/*********************************************************************************************************
**  @FunctionName               GPIO_Read
**  @Description                GPIO 读取输入值
**  @InputParam                 pin:     	IO端口号
**  @OutputParam                NONE
**  @ReturnValue                -1:        失败
**                              0/1:        输入值
*********************************************************************************************************/
int HAL_GPIO_Read(int pin)
{
	char path[64];
	char value_str[3] = { 0 };
	int fd = -1;

	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		zlog_info(debug_out, "Failed to open %s: errno=%d (%s)\n", path, errno, strerror(errno));
		zlog_info(debug_out,"Failed to open gpio value for reading!\n");
		zlog_info(debug_out,"gpio_read pin num is:%d\n", pin);
		// close(fd);
		return -1;
	}

	if(read(fd, value_str, 3) < 0)
	{
		zlog_info(debug_out,"Failed to read value!\n");
		close(fd);
		return -1;
	}

	close(fd);
	return (atoi(value_str));
}




/****************************************************************
 * gpio_set_edge
 ****************************************************************/

int HAL_gpio_set_edge(unsigned int gpio, char *edge)
{
	int fd, len;
	char buf[64];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-edge");
		return fd;
	}

	write(fd, edge, strlen(edge) + 1);
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/

int HAL_gpio_fd_open(unsigned int gpio)
{
	int fd, len;
	char buf[64];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int HAL_gpio_fd_close(int fd)
{
	return close(fd);
}





/*
 *  功能：打开gpio读取设备，并且配置为点评出发
 *  输入：pin:GPIO引脚,
 *       
 *  输出：打开成功的文件描述符
 */
int HAL_GPIO_open_epoll(int pin)
{
	char path[64];
	char value_str[3] = { 0 };
	int fd = -1;
	HAL_gpio_set_edge(pin, "both");
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open  /sys/class/gpio/gpio%d/value\n",pin);
		return -1;
	}
	return fd;
}

/*
 *  功能：读取GPIO引脚高低电平
 *  输入：pin:GPIO引脚,
 *       value:高低电平值变量指针
 *  输出：0成功，-1失败
 *  //不会关闭fb
 */
int HAL_GPIO_read_epoll(int pin,int fd,int *read_value)
{

	char value_str[3] = { 0 };
	int ret = -1;

	if (read(fd, value_str, 3) < 0)
	{
		printf("Failed to read  /sys/class/gpio/gpio%d/value\n",pin);
		return ret;
	}
	else
	{
		*read_value = atoi(value_str);
		//printf(" /sys/class/gpio/gpio%d/value%d\n",pin,*read_value);
		ret = 0;
	}
	return ret;
}




