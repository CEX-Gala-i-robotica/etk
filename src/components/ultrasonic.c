#include <wiringPi.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>



#include "ultrasonic.h"



long getMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void RunUltrasonicSensorTest(int trig, int echo)
{
    long startTime, travelTime;
    float distance;
    if (wiringPiSetup() == -1)
    {
        printf("Failed to setup GPIO !!!\n");
    }
    else
    {
        pinMode(trig, OUTPUT);
        pinMode(echo, INPUT);
       
        // Ensure TRIG is LOW
        digitalWrite(trig, LOW);
        delay(500);
        
        while(1)
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
        }
    }
}