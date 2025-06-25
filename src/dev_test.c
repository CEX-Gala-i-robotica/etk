
#include <wiringpi/wiringPi.h>
#include <wiringpi/softTone.h>
#include <softServo.h>
#include <softPwm.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#include "dev_test.h"
#include "gpio_utils.h"

#define SERVO_PIN GPIO_26
#define	PIN	28

int scale [8] = { 262, 294, 330, 349, 392, 440, 494, 525 } ;


void Dev_Test(int argc, char *argv[])
{
    /*
    int i ;
    
    wiringPiSetup();
    
    softToneCreate(GPIO_26);

    for(;;)
    {
        for(i = 0 ; i < 8 ; ++i)
        {
            printf("%3d\n", i) ;
            softToneWrite(GPIO_26, scale [i]);
            delay(500);
        }
    }
    */
    
/*
    int bright ;
   
     printf ("Raspberry Pi wiringPi PWM test program\n") ;
   
     if (wiringPiSetup () == -1)
       exit (1) ;
   
     pinMode (GPIO_26, PWM_OUTPUT) ;
   
     for (;;)
     {
       for (bright = 0 ; bright < 1024 ; ++bright)
       {
         pwmWrite (GPIO_26, bright) ;
         delay (1) ;
       }
   
       for (bright = 1023 ; bright >= 0 ; --bright)
       {
         pwmWrite (GPIO_26, bright) ;
         delay (1) ;
       }
     }
*/

wiringPiSetup();
 softServoSetup(25, -1, -1, -1, -1, -1, -1, -1); // Only using pin 25

 softServoWrite(25, 1000); // 1ms pulse (one end)
 delay(1000);
 softServoWrite(25, 1500); // 1.5ms pulse (center)
 delay(1000);
 softServoWrite(25, 2000); // 2ms pulse (other end)
 delay(1000);

 for (;;)
   delay(10);
}