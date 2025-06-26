#include <wiringPi.h>
#include <stdio.h>


#include "keypad.h"



int current_rows;
int current_cols;

void setupKeypad(int cols, int rows, Keypad kp)
{
    if(cols < MAX_ROWS || rows < MAX_COLS)
    {
        printf("The keypad layout cannot be larger than %d rows, %d columns !!!\n", MAX_ROWS, MAX_COLS);
    }
    else
    {
        current_rows = rows;
        current_cols = cols;
        if (wiringPiSetup() == -1)
        {
            printf("Failed to setup GPIO !!!\n");
        }
        else
        {
            int i;
            // Set row pins as OUTPUT, default HIGH
            for(i = 0; i < rows; i++)
            {
                pinMode(kp.rowPins[i], OUTPUT);
                digitalWrite(kp.rowPins[i], HIGH);
            }
            // Set column pins as INPUT with pull-up
            for(i = 0; i < rows; i++)
            {
                pinMode(kp.colPins[i], INPUT);
                pullUpDnControl(kp.colPins[i], PUD_UP);
            }
        }
    }
}

char KeypadScan(Keypad kp, char kp_layout[MAX_ROWS][MAX_COLS])
{
    char pressed_key;
    int row, col;
    for(row = 0; row < MAX_ROWS; row++)
    {
        // Set all rows HIGH
        for(int i = 0; i < MAX_ROWS; i++)
            digitalWrite(kp.rowPins[i], HIGH);
        // Set current row LOW
        digitalWrite(kp.rowPins[row], LOW);
    
        // Scan columns
        for(col = 0; col < MAX_COLS; col++)
        {
            if(digitalRead(kp.colPins[col]) == LOW)
            {
                // Debounce
                delay(50);
                if(digitalRead(kp.colPins[col]) == LOW)
                {
                    // Wait for key release
                    while (digitalRead(kp.colPins[col]) == LOW);
                    return kp_layout[row][col];
                }
            }
        }
    }
    return 0;
}