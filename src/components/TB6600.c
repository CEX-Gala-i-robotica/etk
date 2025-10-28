#include <wiringPi.h>
#include <log_c/log.h>


#include "TB6600.h"


bool forced_stop = false;
bool is_init;
bool is_enabled;

void TB6600_Setup(TB6600_Stepper s)
{
    if(wiringPiSetup() == -1)
    {
        is_init = false;
        log_error("Failed to setup WiringPi");
        return;
    }
    
    pinMode(s.pul, OUTPUT);
    pinMode(s.dir, OUTPUT);
    pinMode(s.en_a, OUTPUT);
    is_init = true;
}

void TB6600_CancelSteps()
{
    forced_stop = true;
}

void TB6600_Step(TB6600_Stepper s, int steps, enum TB6600_Directions dr, int delay_speed)
{
    if(!is_init)
    {
        log_error("TB6600 not initialized !!!");
        return;
    }
    
    
    
    digitalWrite(s.en_a, LOW);
    log_trace("Direction: %d", dr);
    digitalWrite(s.dir, (int)dr);
    
    for(int i = 0; i < steps; i++)
    {
        //log_info("Stepping...");
        digitalWrite(s.pul, HIGH);
        delayMicroseconds(delay_speed);  // pulse width (min 5µs, TB6600 spec)
        digitalWrite(s.pul, LOW);
        delayMicroseconds(delay_speed);  // step interval
        if(forced_stop)
            break;
    }
    digitalWrite(s.en_a, HIGH);
}

void TB6600_Enable(TB6600_Stepper s)
{
    digitalWrite(s.en_a, LOW);
    is_enabled = true;
}

void TB6600_Disable(TB6600_Stepper s)
{
    digitalWrite(s.en_a, HIGH);
    is_enabled = false;
}

void TB6600_StepNoEnable(TB6600_Stepper s, int steps, enum TB6600_Directions dr, int delay_speed)
{
    if(!is_init)
    {
        log_error("TB6600 not initialized !!!");
        return;
    }
    
    if(!is_enabled)
    {
        log_warn("TB6600 Driver not enabled !!!");
        return;
    }
    
    digitalWrite(s.dir, dr);
    
    for(int i = 0; i < steps; i++)
    {
        digitalWrite(s.pul, HIGH);
        delayMicroseconds(delay_speed);  // pulse width (min 5µs, TB6600 spec)
        digitalWrite(s.pul, LOW);
        delayMicroseconds(delay_speed);  // step interval
        if(forced_stop)
            break;
    }
    
    if(is_enabled)
    {
        log_warn("Stepper motor is locked !!! Please disable the driver !!!");
        return;
    }
}