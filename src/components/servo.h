#ifndef SERVO_H
#define SERVO_H


enum PWM_Mode
{
    SOFT_BASED,
    DEFAULT
};


static int angleToSoftPWM(int angle);
static int angleToPWM(int angle);

void ServoInit(int pwm_pin, enum PWM_Mode pm);
void ServoSetAngle(int pin, int angle);
#endif