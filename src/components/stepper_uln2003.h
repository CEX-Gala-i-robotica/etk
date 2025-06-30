#ifndef STEPPER_ULN2003_H
#define STEPPER_ULN2003_H



typedef struct
{
    int in1;
    int in2;
    int in3;
    int in4;
}StepperULN2003;

enum StepperDirections
{
    ULN2003_FORWARD,
    ULN2003_BACKWARDS
};

void StepperULN2003_Setup(StepperULN2003 stepper);
void StepperULN2003_RunSteps(StepperULN2003 stepper, int steps, int delay_speed, enum StepperDirections step_dirs);
void RunStepperULN2003Test(StepperULN2003 stepper);
#endif