#include <wiringPi.h>
#include <stdio.h>
#include <log_c/log.h>


#include "keypad.h"



int current_rows;
int current_cols;
bool is_keypad4x4_init;
bool is_keypad4x3_init;

void setupKeypad4x4(Keypad4x4 kp)
{
    if(wiringPiSetup() == -1)
    {
        is_keypad4x4_init = false;
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        int i;
        // Set row pins as OUTPUT, default HIGH
        for(i = 0; i < KEYPAD_4X4_MAX_ROWS; i++)
        {
            pinMode(kp.rowPins[i], OUTPUT);
            digitalWrite(kp.rowPins[i], HIGH);
        }
        // Set column pins as INPUT with pull-up
        for(i = 0; i < KEYPAD_4X4_MAX_ROWS; i++)
        {
            pinMode(kp.colPins[i], INPUT);
            pullUpDnControl(kp.colPins[i], PUD_UP);
        }
        is_keypad4x4_init = true;
    }
}

char KeypadScan4x4(Keypad4x4 kp, char kp_layout[KEYPAD_4X4_MAX_ROWS][KEYPAD_4X4_MAX_COLS])
{
    char pressed_key;
    int row, col;
    if(!is_keypad4x4_init)
    {
        log_error("Keypad 4x4: Not initialized !!!");
    }
    else
    {
        for(row = 0; row < KEYPAD_4X4_MAX_ROWS; row++)
        {
            // Set all rows HIGH
            for(int i = 0; i < KEYPAD_4X4_MAX_ROWS; i++)
                digitalWrite(kp.rowPins[i], HIGH);
            // Set current row LOW
            digitalWrite(kp.rowPins[row], LOW);
            
            // Scan columns
            for(col = 0; col < KEYPAD_4X4_MAX_COLS; col++)
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
    }
    return 0;
}

void setupKeypad4x3(Keypad4x3 kp)
{
    if(wiringPiSetup() == -1)
    {
        is_keypad4x3_init = false;
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        int i;
        // Set row pins as OUTPUT, default HIGH
        for(i = 0; i < KEYPAD_4X3_MAX_ROWS; i++)
        {
            pinMode(kp.rowPins[i], OUTPUT);
            digitalWrite(kp.rowPins[i], HIGH);
        }
        // Set column pins as INPUT with pull-up
        for(i = 0; i < KEYPAD_4X3_MAX_ROWS; i++)
        {
            pinMode(kp.colPins[i], INPUT);
            pullUpDnControl(kp.colPins[i], PUD_UP);
        }
        is_keypad4x3_init = true;
    }
}

char KeypadScan4x3(Keypad4x3 kp, char kp_layout[KEYPAD_4X3_MAX_ROWS][KEYPAD_4X3_MAX_COLS])
{
    char pressed_key;
    int row, col;
    if(!is_keypad4x3_init)
    {
        log_error("Keypad 4x3: Not initialized !!!");
    }
    else
    {
        for(row = 0; row < KEYPAD_4X3_MAX_ROWS; row++)
        {
            // Set all rows HIGH
            for(int i = 0; i < KEYPAD_4X3_MAX_ROWS; i++)
                digitalWrite(kp.rowPins[i], HIGH);
            // Set current row LOW
            digitalWrite(kp.rowPins[row], LOW);
            
            // Scan columns
            for(col = 0; col < KEYPAD_4X3_MAX_COLS; col++)
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
    }
    return 0;
}