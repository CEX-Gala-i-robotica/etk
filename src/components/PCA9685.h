#ifndef PCA9685_H
#define PCA9685_H

#include <wiringPiI2C.h>






int PCA9685_Setup();
//void PCA9685_SetMode(int fd, int mode);
void PCA9685_SetPWMFreq(int fd, float freq);
void PCA9685_SetPWM(int fd, int channel, int on, int off);
#endif