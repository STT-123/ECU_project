#include "gpio.h"
#include "string.h"
#include "fcntl.h"	// 文件操作类型定义
#include <unistd.h> // 读写函数
#include <stdlib.h> // atoi函数
#include "log.h"	// 日志接口

#define SYSFS_GPIO_DIR "/sys/class/gpio"

static int gpio_export(int pin)
{
	int fd = -1;
	int len = 0;

	char buffer[64];
	memset(buffer, 0, sizeof(buffer));

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0)
	{
		printf("[GPIO] Failed to open export, pin=[%d]\n", pin);
		return -1;
	}

	len = snprintf(buffer, sizeof(buffer), "%d", pin);
	if (write(fd, buffer, len) < 0)
	{
		return -1;
	}

	close(fd);

	return 0;
}

// IO端口方向	0-->IN, 1-->OUT
static int gpio_direction(int pin, int dir)
{
	static const char dir_str[] = "in\0out";
	int fd = -1;

	char path[64];
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);

	fd = open(path, O_WRONLY);
	if (fd < 0)
	{
		printf("[GPIO] Failed to open direction, pin=[%d]\n", pin);
		return -1;
	}

	if (write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0)
	{
		printf("[GPIO] Failed to write direction, pin=[%d]\n", pin);
		return -1;
	}

	close(fd);
	return 0;
}

//
int gpio_open(int pin, int dir, GPIO_VALUE value)
{
	gpio_export(pin);
	gpio_direction(pin, dir);
	// 如果是输入，这就可以结束了
	if (dir == 0)
		return 0;
	// 如果是输出，设置一个默认电平
	gpio_write(pin, value);

	return 0;
}

int gpio_write(int pin, GPIO_VALUE value)
{
	static const char values_str[] = "01";

	int fd = -1;
	char path[64];
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);

	fd = open(path, O_WRONLY);
	if (fd < 0)
	{
		printf("[GPIO] Failed to open write, pin=[%d]\n", pin);
		return -1;
	}

	if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0)
	{
		printf("[GPIO] Failed to write write, pin=[%d]\n", pin);
		return -1;
	}

	close(fd);
	return 0;
}

GPIO_VALUE gpio_read(int pin)
{
	char path[64];
	char value_str[3] = {0};
	int fd = -1;

	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("[GPIO] Failed to open read, pin=[%d]\n", pin);
		return -1;
	}

	if (read(fd, value_str, 3) < 0)
	{
		printf("[GPIO] Failed to read read, pin=[%d]\n", pin);
		return -1;
	}

	close(fd);

	return (atoi(value_str));
}

static int gpio_unexport(int pin)
{
	int fd = -1;
	int len = 0;

	char buffer[64];
	memset(buffer, 0, sizeof(buffer));

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd < 0)
	{
		printf("[GPIO] Failed to open unexport, pin=[%d]\n", pin);
		return -1;
	}

	len = snprintf(buffer, sizeof(buffer), "%d", pin);
	if (write(fd, buffer, len) < 0)
	{
		printf("[GPIO] Failed to write unexport, pin=[%d]\n", pin);
		return -1;
	}

	close(fd);
	return 0;
}

int gpio_close(int pin)
{
	return gpio_unexport(pin);
}

static int gpio_set_edge(unsigned int gpio, char *edge)
{
	int fd;
	char buf[64];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0)
	{
		perror("gpio/set-edge");
		return fd;
	}

	write(fd, edge, strlen(edge) + 1);
	close(fd);
	return 0;
}

int gpio_open_epoll(int pin)
{
	int fd = -1;
	char path[64];

	// 设置边沿触发
	if (gpio_set_edge(pin, "both") < 0)
	{
		printf("[GPIO] Failed to set edge gpio pin=[%d] !\n", pin);
	}

	// 获取文件fd
	memset(path, 0, sizeof(path));
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open  /sys/class/gpio/gpio%d/value\n", pin);
		return -1;
	}
	return fd;
}

int gpio_read_epoll(int pin, int fd, int *value)
{
	int ret = -1;
	char value_str[3] = {0};

	if (read(fd, value_str, 3) < 0)
	{
		printf("Failed to read  /sys/class/gpio/gpio%d/value\n", pin);
		return ret;
	}
	else
	{
		*value = atoi(value_str);
		ret = 0;
	}
	return ret;
}
