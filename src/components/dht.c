#include <pigpio.h>






#include "dht.h"



dht11_data_t read_dht11() {
    dht11_data_t result = {0, 0, 0};
    uint8_t data[5] = {0, 0, 0, 0, 0};
    uint8_t laststate = 1;
    uint8_t counter = 0;
    uint8_t j = 0, i;
    
    // Send start signal
    gpioSetMode(DHT_PIN, PI_OUTPUT);
    gpioWrite(DHT_PIN, 0);
    gpioDelay(18000);  // 18ms
    gpioWrite(DHT_PIN, 1);
    gpioDelay(40);
    gpioSetMode(DHT_PIN, PI_INPUT);
    
    // Read data
    for (i = 0; i < MAX_TIMINGS; i++)
    {
        counter = 0;
        while (gpioRead(DHT_PIN) == laststate)
        {
            counter++;
            gpioDelay(1);
            if (counter == 255) break;
        }
        laststate = gpioRead(DHT_PIN);
        
        if (counter == 255) break;
        
        if((i >= 4) && (i % 2 == 0))
        {
            data[j / 8] <<= 1;
            if(counter > 16)
            {
                data[j / 8] |= 1;
            }
            j++;
        }
    }
    
    // Verify checksum
    if((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        result.humidity = (float)data[0];
        result.temperature = (float)data[2];
        result.valid = 1;
    }
    
    return result;
}