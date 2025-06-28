#include <wiringPi.h>
#include <log_c/log.h>



/*
Not good for any use

Maybe this could help: https://github.com/kiryanenko/TTP229/blob/master/TTP229.cpp
*/



#include "TTP229.h"
#include "../gpio_utils.h"


unsigned short keyState = 0;

void Setup_TTP229()
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        pinMode(GPIO_17, OUTPUT);
        pinMode(GPIO_18, INPUT);
    }
}

int TTP229_GetPressed()
{
    //char key;
    for(int i = 0; i < 16; i++)
    {
        digitalWrite(GPIO_17, LOW);
        delayMicroseconds(2); // Short delay
        digitalWrite(GPIO_17, HIGH);
        delayMicroseconds(2); // Short delay
        int bit = digitalRead(GPIO_18);
        // TTP229: 0 = pressed, 1 = not pressed
        if(bit == 0)
        {
            keyState |= (1 << i);
        }
    }
    
    // Print pressed keys
    //printf("Pressed keys: ");
    for(int i = 0; i < 16; i++)
    {
        if(keyState & (1 << i))
        {
            //printf("%d ", i+1); // Key numbers 1-16
            return i+1;
        }
    }
    delay(100); // 100 ms
    return 0;
}