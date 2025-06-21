#ifndef DHT_H
#define DHT_H





#define MAX_TIMINGS 85
#define DHT_PIN 4  // GPIO 4


typedef struct
{
    float temperature;
    float humidity;
    int valid;
} dht11_data_t;

dht11_data_t read_dht11();
#endif