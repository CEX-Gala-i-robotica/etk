#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <log_c/log.h>



#include "universal_sensors.h"




int readADC(int channel)
{
    unsigned char buffer[3];
    buffer[0] = 1; // Start bit
    buffer[1] = (8 + channel) << 4; // Single-ended, channel
    buffer[2] = 0;

    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

    int value = ((buffer[1] & 3) << 8) | buffer[2];
    return value;
}

void UniversalSensorTest(enum SensorInput tm, int pin)
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
    }
    else
    {
        pinMode(pin, INPUT);
        
        if(tm == DIGITAL_INPUT)
        {

            while(1)
            {
                int value = digitalRead(pin);
    
                if (value == HIGH)
                {
                    printf("Sensor activated\n");
                }
                else
                {
                    printf("Sensor inactive!\n");
                }
    
                delay(500); // Wait 500ms
            }
        }
        else if(tm == ANALOGIC_INPUT)
        {
            // Not working on Raspberry pi 5
            if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
            {
                printf("SPI setup failed!\n");
            }
            else
            {
                while(1)
                {
                    int moisture = readADC(0); // Channel 0 for ME110 AOUT
                    printf("Moisture Value: %d\n", moisture); // 0 (dry) to 1023 (wet)
                    delay(1000); // 1 second
                }
            }
        }
    }
}