#ifndef GPIO_H_
#define GPIO_H_

typedef enum
{
    GPIO_L = 0,
    GPIO_H = 1,
} GPIO_VALUE;

// 正常使用
int gpio_open(int pin, int dir, GPIO_VALUE value);
int gpio_write(int pin, GPIO_VALUE value);
GPIO_VALUE gpio_read(int pin);
int gpio_close(int pin);
// 中断使用
int gpio_open_epoll(int pin);
int gpio_read_epoll(int pin, int fd, int *value);

#endif /* GPIO_H_ */
