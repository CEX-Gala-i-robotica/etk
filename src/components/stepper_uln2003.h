#ifndef STEPPER_ULN2003_H
#define STEPPER_ULN2003_H



typedef struct
{
    int in1;
    int in2;
    int in3;
    int in4;
}StepperULN2003;


void RunStepperULN2003Test(StepperULN2003 stepper);
#endif