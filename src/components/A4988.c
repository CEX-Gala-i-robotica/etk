#include <wiringPi.h>
#include <log_c/log.h>
#include <stdlib.h>


#include "A4988.h"
#include "../gpio_utils.h"




bool is_driver_enabled = false;
bool is_driver_in_sleep;
bool is_driver_reset;


void A4988_Setup(A4988_Stepper driver)
{
    if(wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring pi !!!");
    }
    else
    {
        pinMode(driver.dir_pin,    OUTPUT);
        pinMode(driver.step_pin,   OUTPUT);
        pinMode(driver.enable_pin, OUTPUT);
    }
}

void A4988_Step(A4988_Stepper driver, int steps, int delay, enum A4988_Directions step_dirs)
{
    if(delay <= 500)
    {
        log_warn("Low delay speed !!!! This can affect the stepper motor performance. Please set the speed delay higher or enable microstep levels.");
    }
    if(delay <= 400)
    {
        log_error("Delay speed is too low !!!");
        exit(1);
    }
    else
    {
        digitalWrite(driver.enable_pin, LOW); // Enable driver (LOW = enabled)
        if(step_dirs == A4988_FORWARD)
        {
            digitalWrite(driver.dir_pin, HIGH); // Set direction
            log_info("A4988: %d steps forward", steps);
        }
        else if(step_dirs == A4988_BACKWARDS)
        {
            digitalWrite(driver.dir_pin, LOW); // Set direction
            log_info("A4988: %d steps backwards", steps);
        }
        
        
        for(int i = 0; i < steps; i++)
        {
            digitalWrite(driver.step_pin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(driver.step_pin, LOW);
            delayMicroseconds(delay);
        }
        
        digitalWrite(driver.enable_pin, HIGH); // Disable driver (optional)
    }
}

void A4988Full_Setup(A4988_FullStepper driver)
{
    if(wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring pi !!!");
    }
    else
    {
        pinMode(driver.dir_pin,    OUTPUT);
        pinMode(driver.step_pin,   OUTPUT);
        pinMode(driver.enable_pin, OUTPUT);
        pinMode(driver.sleep,      OUTPUT);
        pinMode(driver.rst,        OUTPUT);
        pinMode(driver.ms1,        OUTPUT);
        pinMode(driver.ms2,        OUTPUT);
        pinMode(driver.ms3,        OUTPUT);
    }
}

void A4988_Enable(A4988_FullStepper driver, bool toggle)
{
    if(toggle)
    {
        digitalWrite(driver.enable_pin, LOW);
        is_driver_enabled = true;
    }
    else
    {
        digitalWrite(driver.enable_pin, HIGH);
        is_driver_enabled = false;
    }
}

void A4988_Sleep(A4988_FullStepper driver, bool toggle)
{
    if(toggle)
    {
        digitalWrite(driver.sleep, LOW);
        is_driver_in_sleep = true;
    }
    else
    {
        digitalWrite(driver.sleep, HIGH);
        is_driver_in_sleep = false;
    }
}

void A4988Full_SetDirection(A4988_FullStepper driver, enum A4988_Directions step_dirs)
{
    digitalWrite(driver.enable_pin, LOW);
    if(step_dirs == A4988_FORWARD)
    {
        digitalWrite(driver.dir_pin, HIGH);
        log_info("A4988: Direction changed: forward");
    }
    else if(step_dirs == A4988_BACKWARDS)
    {
        digitalWrite(driver.dir_pin, LOW);
        log_info("A4988: Direction changed: backwards");
    }
}

void A4988_Reset(A4988_FullStepper driver, bool toggle)
{
    if(toggle)
    {
        digitalWrite(driver.rst, LOW);
        is_driver_reset = true;
    }
    else
    {
        digitalWrite(driver.rst, HIGH);
        is_driver_reset = false;
    }
}

void A4988Full_Step(A4988_FullStepper driver, int steps, int delay, enum A4988_Directions step_dirs)
{
    if(!is_driver_enabled)
    {
        log_warn("A4988: Driver is not enabled !!!");
    }
    else if(is_driver_in_sleep)
    {
        log_warn("A4988: Driver is in sleep mode !!!");
    }
    else if(is_driver_reset)
    {
        log_warn("A4988: Driver is in reset !!!");
    }
    else
    {
        for(int i = 0; i < steps; i++)
        {
            digitalWrite(driver.step_pin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(driver.step_pin, LOW);
            delayMicroseconds(delay);
        }
    }
}