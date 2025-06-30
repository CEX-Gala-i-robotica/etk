#include <wiringPiI2C.h>
#include <log_c/log.h>
#include <unistd.h>



#include "PCA9685.h"


#define PCA9685_ADDR 0x40

// Register addresses
#define MODE1       0x00
#define MODE2       0x01
#define PRESCALE    0xFE
#define LED0_ON_L   0x06


void PCA9685_SetPWMFreq(int fd, float freq)
{
    float prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freq;
    prescaleval -= 1.0;
    int prescale = (int)(prescaleval + 0.5);

    int oldmode = wiringPiI2CReadReg8(fd, MODE1);
    int newmode = (oldmode & 0x7F) | 0x10; // sleep
    wiringPiI2CWriteReg8(fd, MODE1, newmode);
    wiringPiI2CWriteReg8(fd, PRESCALE, prescale);
    wiringPiI2CWriteReg8(fd, MODE1, oldmode);
    usleep(5000);
    wiringPiI2CWriteReg8(fd, MODE1, oldmode | 0x80);
}

int PCA9685_Setup()
{
    int fd = wiringPiI2CSetup(PCA9685_ADDR);
    if(fd < 0)
    {
        log_error("PCA9685: Failed to initialize I2C !!!");
    }
    else
    {
        //wiringPiI2CWriteReg8(*fd, MODE1, 0x00);
        PCA9685_SetPWMFreq(fd, 50);
        log_info("PCA9685: Init");
    }
    
    return fd;
}

void PCA9685_SetPWM(int fd, int channel, int on, int off)
{
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel, on & 0xFF);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 1, on >> 8);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 2, off & 0xFF);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 3, off >> 8);
}