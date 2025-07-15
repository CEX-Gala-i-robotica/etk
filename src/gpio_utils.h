#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H



#include <stdbool.h>

//int current_gpio_pin;


#define I2C_DEV_SYSFS "/dev/i2c-1"
#define I2C_KMOD_SYSFS "/sys/class/i2c-adapter/"


// PLEASE DO NOT TOUCH THESE !!!
//todo: Find missing GPIO pins
#define GPIO_22 3
#define GPIO_23 4
#define GPIO_24 5
#define GPIO_25 6
#define GPIO_4  7
#define GPIO_2  8
#define GPIO_3  9
#define GPIO_8  10
#define GPIO_7  11
#define GPIO_10 12
#define GPIO_9  13
#define GPIO_11 14
#define GPIO_14 15
#define GPIO_15 16
#define GPIO_27 2
#define GPIO_18 1
#define GPIO_17 0
#define GPIO_26 25
#define GPIO_16 27
#define GPIO_12 26
#define GPIO_21 29
#define GPIO_19 24
#define GPIO_6  22
#define GPIO_20 28
//#define GPIO_13
//#define GPIO_5
// PLEASE DO NOT TOUCH THESE !!!

bool isI2C_available();
bool isPWM_available(int pin);
void gpioInit();
void gpio_cleanup(int pin);
void gpio_cleanup_all();
void on_exit_signal(int s);
#endif