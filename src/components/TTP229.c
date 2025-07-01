#include <wiringPi.h>
#include <log_c/log.h>



/*
Not good for any use

Maybe this could help: https://github.com/kiryanenko/TTP229/blob/master/TTP229.cpp
*/



#include "TTP229.h"
#include "../gpio_utils.h"


unsigned short keyState = 0;

void wait_for_key_event() {
    while (digitalRead(GPIO_27) == HIGH) {
        delay(1); // Wait 1 ms
    }
}

// Wait for SDO to go HIGH (ready for next event)
void wait_for_key_release() {
    while (digitalRead(GPIO_27) == LOW) {
        delay(1); // Wait 1 ms
    }
}

void Setup_TTP229()
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        pinMode(GPIO_17, OUTPUT);
        pinMode(GPIO_27, INPUT);
        digitalWrite(GPIO_17, LOW);
    }
}

uint16_t TTP229_GetPressed()
{
    uint16_t keys = 0;
        for (int i = 0; i < 16; i++) {
            digitalWrite(GPIO_17, HIGH);
            delayMicroseconds(100);
            if (digitalRead(GPIO_27) == LOW) {
                keys |= (1 << i); // Active low: 0 = pressed, so set bit if LOW
            }
            digitalWrite(GPIO_17, LOW);
            delayMicroseconds(100);
        }
        return keys;
}

void print_keys(uint16_t keys) {
    printf("Keys: ");
    for (int i = 0; i < 16; i++) {
        if (keys & (1 << i))
            printf("%2d ", i + 1);
    }
    printf("\n");
}