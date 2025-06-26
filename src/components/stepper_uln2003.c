#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <log_c/log.h>


#include "stepper_uln2003.h"



StepperULN2003 stepper;

int step_sequence[4][4] =
{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

void step(StepperULN2003 stepper, int step_num)
{
    digitalWrite(stepper.in1, step_sequence[step_num][0]);
    digitalWrite(stepper.in2, step_sequence[step_num][1]);
    digitalWrite(stepper.in3, step_sequence[step_num][2]);
    digitalWrite(stepper.in4, step_sequence[step_num][3]);
}

void RunStepperULN2003Test(StepperULN2003 stepper)
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        pinMode(stepper.in1, OUTPUT);
        pinMode(stepper.in2, OUTPUT);
        pinMode(stepper.in3, OUTPUT);
        pinMode(stepper.in4, OUTPUT);
        
        int steps = 1500; // One revolution for 28BYJ-48
        int i, j;
        
        while(1)
        {
            for(i = 0; i < steps; i++)
            {
                step(stepper, i % 4);
                delay(2); // 2ms per step, adjust for speed
            }
            
            delay(500);
            
            for(i = steps; i > 0; i--)
            {
                step(stepper, i % 4);
                delay(2); // 2ms per step, adjust for speed
            }
            
            delay(500);
        }
    }
}