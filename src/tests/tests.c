#include <unistd.h>
#include "../gpio_utils.h"

#include "../components/servo.h"




#include "tests.h"





void idk()
{
    //lskdfjsdjkfhsdjkhfsdjkhfksjdhfjsh
    ServoInit(GPIO_25, SOFT_BASED);

    ServoSetAngle(GPIO_25, 0);
    usleep(1000);
    ServoSetAngle(GPIO_25, 90);
    usleep(1000);
}