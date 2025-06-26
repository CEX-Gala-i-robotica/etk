#ifndef MH_INFRARED_H
#define MH_INFRARED_H






#define SPI_CHANNEL 0      // Use CE0
#define SPI_SPEED   1000000 // 1 MHz


enum SensorInput
{
    DIGITAL_INPUT,
    ANALOGIC_INPUT // Dosen't work on rpi 5
};

void UniversalSensorTest(enum SensorInput tm, int pin);
#endif