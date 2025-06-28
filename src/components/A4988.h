#ifndef A4988_H
#define A4988_H

#include <stdbool.h>



/*
!!! INPORTANT PIN Configuration !!!

1: red
3: blue
4: green
6: black

Normal Stepper: 1, 3, 4, 6

Connections on a printer shield:
2B -> 6
2A -> 3
1A -> 4
1B -> 1
*/


typedef struct
{
    int step_pin;
    int dir_pin;
    int enable_pin;
}A4988_Stepper;

typedef struct
{
    int step_pin;
    int dir_pin;
    int enable_pin;
    int ms1;
    int ms2;
    int ms3;
    int sleep;
    int rst;
}A4988_FullStepper;

enum A4988_Directions
{
    FORWARD,
    BACKWARDS
};

void A4988_Setup(A4988_Stepper driver);
void A4988_Step(A4988_Stepper driver, int steps, int delay, enum A4988_Directions step_dirs);

// Support on full controll
void A4988Full_Setup(A4988_FullStepper driver);
void A4988_Enable(A4988_FullStepper driver, bool toggle);
void A4988Full_SetDirection(A4988_FullStepper driver, enum A4988_Directions step_dirs);
void A4988Full_Step(A4988_FullStepper driver, int steps, int delay, enum A4988_Directions step_dirs);
void A4988_Sleep(A4988_FullStepper driver, bool toggle);
void A4988_Reset(A4988_FullStepper driver, bool toggle);
#endif