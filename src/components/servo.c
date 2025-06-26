#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>
#include <stdio.h>
#include <log_c/log.h>



#include "servo.h"
#include "../gpio_utils.h"





int angleToSoftPWM(int angle)
{
    // 0 deg = 5% (1ms), 180 deg = 10% (2ms)
    int min = 5;   // 1ms pulse
    int max = 25;  // 2ms pulse
    return min + (angle * (max - min)) / 180;
}

int angleToPWM(int angle)
{
    // For 50Hz (20ms period), 1ms pulse = 5% duty, 2ms = 10% duty
    // WiringPi PWM range is 0-1024 by default
    // 1ms pulse: 1024 * 1ms / 20ms = 51
    // 2ms pulse: 1024 * 2ms / 20ms = 102
    int min = 51; // 1ms
    int max = 102; // 2ms
    return min + (angle * (max - min)) / 180;
}


void RunServoTest(enum PWM_Mode pm, int pin)
{
    int angle;
    
    if(pm == DEFAULT)
    {
        printf("Servo auto test: DEFAULT PWM Mode\n");
        if (wiringPiSetup() == -1)
        {
            log_error("Failed to setup wiring Pi!");
        }
        else
        {
            if(isPWM_available(pin))
            {
                pinMode(pin, PWM_OUTPUT);
                
                pwmSetMode(PWM_MODE_MS);
                pwmSetRange(1024);
                pwmSetClock(375);
                
                while(1)
                {
                    // Sweep from 0 to 180 degrees
                    for(angle = 0; angle <= 280; angle += 10)
                    {
                        pwmWrite(GPIO_19, angleToPWM(angle));
                        delay(40);
                    }
                    // Sweep back from 180 to 0 degrees
                    for(angle = 280; angle >= 0; angle -= 10)
                    {
                        pwmWrite(GPIO_19, angleToPWM(angle));
                        delay(40);
                    }
                }
            }
        }
    }
    else if(pm == SOFT_BASED)
    {
        printf("Servo auto test: SOFT_BASED PWM Mode\n");
        if (wiringPiSetup() == -1)
        {
            log_error("Failed to setup wiring Pi!");
        }
        else
        {
            if(isPWM_available(pin))
            {
                if(softPwmCreate(GPIO_18, 0, 200) != 0)
                {
                    log_error("softPwmCreate failed!\n");
                }
                else
                {
                    while(1)
                    {
                        // Sweep from 0 to 180 degrees
                        for(angle = 0; angle <= 180; angle += 5)
                        {
                            softPwmWrite(GPIO_18, angleToSoftPWM(angle));
                            delay(50);
                        }
                        // Sweep back from 180 to 0 degrees
                        for(angle = 180; angle >= 0; angle -= 5)
                        {
                            softPwmWrite(GPIO_18, angleToSoftPWM(angle));
                            delay(50);
                        }
                    }
                }
            }
        }
    }
}