#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <log_c/log.h>






#include "dht.h"




bool is_dht11_init;


void dht11_Setup(int pin)
{
    if(wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring Pi!");
        is_dht11_init = false;
    }
    else
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        delay(18); // 18ms
        digitalWrite(pin, HIGH);
        delayMicroseconds(40);
        pinMode(pin, INPUT);
        is_dht11_init = true;
    }
}

dht11_data_t read_dht11(int pin)
{
    dht11_data_t result = {0, 0, 0};
    
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    int data[5] = {0, 0, 0, 0, 0};
   
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    
    if(!is_dht11_init)
    {
        log_error("DHT11: Sensor not initialised !!!");
    }
    else
    {
        
        // Read data
        for(i = 0; i < MAX_TIMINGS; i++)
        {
            counter = 0;
            while(digitalRead(pin) == laststate)
            {
                counter++;
                delayMicroseconds(1);
                if (counter == 255)
                    break;
            }
            laststate = digitalRead(pin);
    
            if(counter == 255)
                break;
    
            // Ignore first 3 transitions
            if((i >= 4) && (i % 2 == 0))
            {
                data[j / 8] <<= 1;
                if(counter > 16)
                    data[j / 8] |= 1;
                j++;
            }
        }
        
        // Check we read 40 bits (5 bytes)
        if((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
        {
            log_info("Humidity: %d.%d | Temperature: %d.%d *C\n", data[0], data[1], data[2], data[3]);
            result.humidity = data[0];
            result.temperature = data[2];
            result.valid = 1;
        }
        else
        {
            result.valid = 0;
            log_warn("No data ! Skipping...\n");
        }
    }
    
    return result;
}