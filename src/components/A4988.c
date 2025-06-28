#include <wiringPi.h>
#include <log_c/log.h>


#include "A4988.h"
#include "../gpio_utils.h"

//#define DIR_PIN GPIO_26   // WiringPi pin 1 (GPIO18)
//#define STEP_PIN GPIO_21  // WiringPi pin 0 (GPIO17)
//#define EN_PIN GPIO_16

/*
void tempTest()
{
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");

    }
// 6 1 4 3 (PIN ORDER !!!)
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW); // Enable driver (LOW = enabled)
    digitalWrite(DIR_PIN, HIGH); // Set direction

    for (int i = 0; i < 2000; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(850);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(850);
    }

    digitalWrite(EN_PIN, HIGH); // Disable driver (optional)
    printf("Done!\n");
}
*/

void A4988_Setup(A4988_Stepper driver)
{
    if (wiringPiSetup() == -1)
    {
        log_error("Failed to setup wiring pi !!!");
    }
    else
    {
        pinMode(driver.dir_pin, OUTPUT);
        pinMode(driver.step_pin, OUTPUT);
        pinMode(driver.enable_pin, OUTPUT);
    }
}

void A4988_Step(A4988_Stepper driver, int steps, int delay, enum A4988_Directions step_dirs)
{
    digitalWrite(driver.enable_pin, LOW); // Enable driver (LOW = enabled)
    if(step_dirs == FORWARD)
    {
        digitalWrite(driver.dir_pin, HIGH); // Set direction
        log_info("A4988: %d steps forward", steps);
    }
    else if(step_dirs == BACKWARDS)
    {
        digitalWrite(driver.dir_pin, LOW); // Set direction
        log_info("A4988: %d steps backwards", steps);
    }

    for(int i = 0; i < steps; i++)
    {
        digitalWrite(driver.step_pin, HIGH);
        delayMicroseconds(delay);
        digitalWrite(driver.step_pin, LOW);
        delayMicroseconds(delay);
    }

    digitalWrite(driver.enable_pin, HIGH); // Disable driver (optional)
}