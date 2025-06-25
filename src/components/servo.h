#ifndef SERVO_H
#define SERVO_H


enum PWM_Mode
{
    SOFT_BASED,
    DEFAULT
};


static int angleToSoftPWM(int angle);
static int angleToPWM(int angle);

void RunServoTest(enum PWM_Mode pm, int pin);
#endif