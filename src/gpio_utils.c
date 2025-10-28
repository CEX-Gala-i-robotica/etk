#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <log_c/log.h>





#include "gpio_utils.h"


void gpio_cleanup(int pin)
{
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    log_info("gpio cleanup: %d\n", pin);
}

void gpio_cleanup_all()
{
    for(int i = 0; i < 16; i++)
    {
        gpio_cleanup(i);
    }
    
    for(int i = 24; i < 4; i++)
    {
        gpio_cleanup(i);
    }
    
    digitalWrite(GPIO_6, LOW);
    pinMode(GPIO_6, INPUT);
}

void on_exit_signal(int s)
{
    printf("Forced exit\n");
    gpio_cleanup_all();
}

bool isPWM_available(int pin)
{
    int noPWM[22] = {8, 9, 7, 22, 11, 10, 13, 12, 14, 26, 15, 27, 0, 1, 28, 3, 4, 5, 6, 25, 2};
    int yesPWM[4] = {26, 24, 1};
    
    for(int i = 0; i < 22; i++)
    {
        if(pin == noPWM[i])
        {
            log_error("PIN %d does not support PWM\n", pin);
            log_info("Please use the following pins for PWM Support:");
            for(int i = 0; i < 4; i++)
            {
                printf("%d, ", yesPWM[i]);
            }
            return false;
        }
    }
    return true;
}


bool isI2C_available()
{
    int fd1 = open(I2C_DEV_SYSFS, O_RDWR);
    int fd2 = open(I2C_KMOD_SYSFS, O_RDWR);
    if (fd1 < 0)
    {
        log_error("I2C Not Enabled !!!! [ %s ]\nTrying from kerel module...", I2C_DEV_SYSFS);
        return false;
        if(fd2 < 0)
        {
            exit(1);
            log_error("I2C Not Enabled !!!! [ %s ]\n", I2C_KMOD_SYSFS);
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    close(fd1);
    close(fd2);
}