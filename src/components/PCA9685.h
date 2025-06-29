#ifndef PCA9685_H
#define PCA9685_H

#include <wiringPiI2C.h>




#define PCA9685_ADDR 0x40

// Register addresses
#define MODE1       0x00
#define MODE2       0x01
#define PRESCALE    0xFE
#define LED0_ON_L   0x06



int PCA9685_Setup();
//void PCA9685_SetMode(int fd, int mode);
void PCA9685_SetPWMFreq(int fd, float freq);
void PCA9685_SetPWM(int fd, int channel, int on, int off);
#endif