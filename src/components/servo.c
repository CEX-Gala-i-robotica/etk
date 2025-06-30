#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>
#include <stdio.h>
#include <log_c/log.h>



#include "servo.h"
#include "../gpio_utils.h"





bool is_servo_init;
enum PWM_Mode current_pwm_mode;



void ServoInit(int pwm_pin, enum PWM_Mode pm)
{
    current_pwm_mode = pm;
    if(wiringPiSetup() == -1)
    {
        is_servo_init = false;
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        if(isPWM_available(pwm_pin))
        {
            if(pm == DEFAULT)
            {
                pinMode(pwm_pin, PWM_OUTPUT);
                
                pwmSetMode(PWM_MODE_MS);
                pwmSetRange(1024);
                pwmSetClock(375);
                is_servo_init = true;
            }
            else if(pm == SOFT_BASED)
            {
                if(softPwmCreate(pwm_pin, 0, 200) != 0)
                {
                    log_error("Servo: Failed to create software based PWM !!!");
                    is_servo_init = false;
                }
                else
                {
                    is_servo_init = true;
                }
            }
        }
        else
        {
            is_servo_init = false;
            log_error("Servo: pin %d does not support PWM !!!");
        }
    }
}


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


void ServoSetAngle(int pin, int angle)
{
    //int angle;
    
    if(current_pwm_mode == DEFAULT)
    {
        printf("Servo auto test: DEFAULT PWM Mode\n");
        if(!is_servo_init)
        {
            log_error("Servo: Not initialized !!!");
        }
        else
        {
            
            // Still incomplete...
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
    else if(current_pwm_mode == SOFT_BASED)
    {
        printf("Servo auto test: SOFT_BASED PWM Mode\n");
        
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