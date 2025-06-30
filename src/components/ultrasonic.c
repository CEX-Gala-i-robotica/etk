#include <wiringPi.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <log_c/log.h>



#include "ultrasonic.h"





bool is_ultrasonic_init;



long getMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void Ultrasonic_Setup(int echo, int trig)
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
        is_ultrasonic_init = false;
    }
    else
    {
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
       
        // Ensure TRIG is LOW
        digitalWrite(trig, LOW);
        delay(500);
        is_ultrasonic_init = true;
    }
}

float Ultrasonic_GetDistance(int echo, int trig)
{
    long startTime, travelTime;
    float distance;
    if (!is_ultrasonic_init)
    {
        log_error("Ultrasinic: Not initialized !!!");
    }
    else
    {
        // Send 10us pulse to TRIG
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
    
        // Wait for ECHO to go HIGH
        while (digitalRead(echo) == LOW);
    
        startTime = getMicroseconds();
    
        // Wait for ECHO to go LOW
        while (digitalRead(echo) == HIGH);
    
        travelTime = getMicroseconds() - startTime;
    
        // Calculate distance (speed of sound is 34300 cm/s)
        distance = travelTime / 58.0; // in cm
    
        printf("Distance: %.2f cm\n", distance);
        return distance;
    }
    return 0;
}