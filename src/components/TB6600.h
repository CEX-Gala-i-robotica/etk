#ifndef TB6600_H
#define TB6600_H





typedef struct 
{
    int en_a;
    int dir;
    int pul;
}TB6600_Stepper;

enum TB6600_Directions
{
    TB6600_FORWARD = 0,
    TB6600_BACKWARD
};


void TB6600_Setup(TB6600_Stepper s);
void TB6600_Step(TB6600_Stepper s, int steps, enum TB6600_Directions dr, int delay_speed);
void TB6600_Enable(TB6600_Stepper s);
void TB6600_Disable(TB6600_Stepper s);
void TB6600_StepNoEnable(TB6600_Stepper s, int steps, enum TB6600_Directions dr, int delay_speed);
void TB6600_CancelSteps();

#endif