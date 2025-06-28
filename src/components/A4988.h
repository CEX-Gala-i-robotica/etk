#ifndef A4988_H
#define A4988_H




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

enum A4988_Directions
{
    FORWARD,
    BACKWARDS
};

void A4988_Setup(A4988_Stepper driver);
void A4988_Step(A4988_Stepper driver, int steps, int delay, enum A4988_Directions step_dirs);
void tempTest();
#endif