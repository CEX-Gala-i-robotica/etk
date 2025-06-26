
#include <wiringpi/wiringPi.h>
#include <wiringpi/softTone.h>
#include <softServo.h>
#include <softPwm.h>


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


#include "dev_test.h"
#include "gpio_utils.h"
#include "components/servo.h"
#include "components/stepper_uln2003.h"
#include "components/dht.h"
#include "components/ultrasonic.h"
#include "components/mpu6050.h"
#include "components/LCD_I2C.h"
#include "components/universal_sensors.h"

//#define SERVO_PIN GPIO_26
#define	PIN	28

//void cleanup(int sig) {
//    // Set your pins to input or low as needed
//    digitalWrite(LED_PIN, LOW);
//    pinMode(LED_PIN, INPUT);
//    printf("Cleaned up GPIO, exiting.\n");
//    _exit(0);
//}

int angleToSoftPWM(int angle) {
    // 0 deg = 5% (1ms), 180 deg = 10% (2ms)
    int min = 5;   // 1ms pulse
    int max = 25;  // 2ms pulse
    return min + (angle * (max - min)) / 180;
}

int angleToPWM(int angle) {
    // For 50Hz (20ms period), 1ms pulse = 5% duty, 2ms = 10% duty
    // WiringPi PWM range is 0-1024 by default
    // 1ms pulse: 1024 * 1ms / 20ms = 51
    // 2ms pulse: 1024 * 2ms / 20ms = 102
    int min = 51; // 1ms
    int max = 102; // 2ms
    return min + (angle * (max - min)) / 180;
}

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

/*
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
   */
   
   /*
   
   printf ("Raspberry Pi blink\n") ;
  
    wiringPiSetup () ;
    pinMode (GPIO_26, OUTPUT) ;
  
    for (;;)
    {
      digitalWrite (GPIO_26, HIGH) ;	// On
      delay(500) ;		// mS
      digitalWrite (GPIO_26, LOW) ;	// Off
      delay(500) ;
    }
    */
    
/*
    int bright ;
   
     printf ("Raspberry Pi wiringPi PWM test program\n") ;
   
     if (wiringPiSetup () == -1)
       exit (1) ;
   
     pinMode (GPIO_19, PWM_OUTPUT) ;
   
     for (;;)
     {
       for (bright = 0 ; bright < 1024 ; ++bright)
       {
         pwmWrite (GPIO_19, bright) ;
         delay (1) ;
       }
   
       for (bright = 1023 ; bright >= 0 ; --bright)
       {
         pwmWrite (GPIO_19, bright) ;
         delay (1) ;
       }
     }
    */
    
/*
    if (wiringPiSetup() == -1) {
        printf("Setup wiringPi failed!\n");
        exit(1);
    }

    if (softPwmCreate(GPIO_18, 0, 200) != 0) { // 200 steps = 20ms period
        printf("softPwmCreate failed!\n");
        exit(1);
    }

    int angle;
    while (1) {
        // Sweep from 0 to 180 degrees
        for (angle = 0; angle <= 180; angle += 5) {
            softPwmWrite(GPIO_18, angleToSoftPWM(angle));
            delay(50);
        }
        // Sweep back from 180 to 0 degrees
        for (angle = 180; angle >= 0; angle -= 5) {
            softPwmWrite(GPIO_18, angleToSoftPWM(angle));
            delay(50);
        }
    }
    */
    
/*
    if (wiringPiSetup() == -1) {
        printf("Setup wiringPi failed!");
        exit(1);
    }

    pinMode(GPIO_19, PWM_OUTPUT);

    // Set PWM mode to mark-space and range for 50Hz
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(1024); // 1024 steps
    pwmSetClock(375);  // 19.2MHz / 375 / 1024 = ~50Hz

    int angle;
    while (1) {
        // Sweep from 0 to 180 degrees
        for (angle = 0; angle <= 280; angle += 10) {
            pwmWrite(GPIO_19, angleToPWM(angle));
            delay(40);
        }
        // Sweep back from 180 to 0 degrees
        for (angle = 280; angle >= 0; angle -= 10) {
            pwmWrite(GPIO_19, angleToPWM(angle));
            delay(40);
        }
    }
*/
    //RunServoTest(DEFAULT, GPIO_19);

/*
    StepperULN2003 someStepper;
    someStepper.in1 = GPIO_12;
    someStepper.in2 = GPIO_16;
    someStepper.in3 = GPIO_20;
    someStepper.in4 = GPIO_21;
    
    RunStepperULN2003Test(someStepper);
*/

    //while(1)
    //{
    //    read_dht11(GPIO_2);
    //    delay(2000);
    //}
    
    //RunUltrasonicSensorTest(GPIO_16, GPIO_20);
    //ReadMPU6050();
    
    //if(isI2C_available())
    //{
    //    printf("Yes i2c\n");    
    //}
    
    //RunLCD_I2C_Test();
    //UniversalSensorTest(DIGITAL_INPUT, GPIO_14);
    UniversalSensorTest(ANALOGIC_INPUT, GPIO_14);
}