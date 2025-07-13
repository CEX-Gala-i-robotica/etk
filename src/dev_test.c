
#include <wiringpi/wiringPi.h>
#include <wiringpi/softTone.h>
#include <softServo.h>
#include <softPwm.h>


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <log_c/log.h>



#include "config_utils.h"


#include "dev_test.h"
#include "gpio_utils.h"
#include "components/servo.h"
#include "components/stepper_uln2003.h"
#include "components/dht.h"
#include "components/ultrasonic.h"
#include "components/mpu6050.h"
#include "components/LCD_I2C.h"
#include "components/universal_sensors.h"
#include "components/keypad.h"
#include "components/TTP229.h"
#include "components/A4988.h"
#include "components/PCA9685.h"

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



/*
#define PRESCALE 0xFE



void setPWMFreq(int fd, float freq) {
    float prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= freq;
    prescaleval -= 1.0;
    int prescale = (int)(prescaleval + 0.5);

    int oldmode = wiringPiI2CReadReg8(fd, MODE1);
    int newmode = (oldmode & 0x7F) | 0x10; // sleep
    wiringPiI2CWriteReg8(fd, MODE1, newmode);
    wiringPiI2CWriteReg8(fd, PRESCALE, prescale);
    wiringPiI2CWriteReg8(fd, MODE1, oldmode);
    usleep(5000);
    wiringPiI2CWriteReg8(fd, MODE1, oldmode | 0x80);
}

void setPWM(int fd, int channel, int on, int off) {
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel, on & 0xFF);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 1, on >> 8);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 2, off & 0xFF);
    wiringPiI2CWriteReg8(fd, LED0_ON_L + 4*channel + 3, off >> 8);
}
*/


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
    //UniversalSensorTest(ANALOGIC_INPUT, GPIO_14);
    /*
    Keypad basic_keypad4x4 =
    {
        .rowPins = {GPIO_20, GPIO_21, GPIO_16, GPIO_12},
        .colPins = {GPIO_7, GPIO_8, GPIO_25, GPIO_24}
    };
    setupKeypad(4, 4, basic_keypad4x4);
    
    while(1)
    {
        char key = KeypadScan(basic_keypad4x4, keypad4x4_layout);
        if (key)
        {
            printf("Key Pressed: %c\n", key);
        }
        delay(100); // Polling delay
    }
    */
    
    
/*
    // Already deprecated use
    Keypad basic_keypad4x3 =
    {
        .rowPins = {GPIO_20, GPIO_21, GPIO_16, GPIO_12},
        .colPins = {GPIO_7, GPIO_8, GPIO_25}
    };
    setupKeypad(4, 3, basic_keypad4x3);
    
    while(1)
    {
        char key = KeypadScan(basic_keypad4x3, keypad4x3_layout);
        if (key)
        {
            printf("Key Pressed: %c\n", key);
        }
        delay(100); // Polling delay
    }
*/

/*
    Setup_TTP229();
    
    while(1)
    {
            log_error("Pressed key: %d", TTP229_GetPressed());
        }
        
*/

/*
// Not good enough
int keyPins[8] = 
{
    GPIO_14,
    GPIO_15,
    GPIO_18,
    GPIO_23,
    GPIO_24,
    GPIO_25,
    GPIO_8,
    GPIO_7
};

if (wiringPiSetup() == -1)
{
    log_error("Failed to setup wiring pi !!!\n");
}
else
{
    for (int i=0; i<8; i++) pinMode(keyPins[i], INPUT);

    while (1) {
        for (int i=0; i<8; i++) {
            printf("K%d: %d ", i+1, digitalRead(keyPins[i]));
        }
        printf("\n");
        delay(100);
    }
}
*/

/*
if (wiringPiSetup() == -1) {
    printf("WiringPi setup failed!\n");
   
}

pinMode(GPIO_17, OUTPUT);
pinMode(GPIO_18, INPUT);

printf("TTP229 4x4 Touchpad test. Press Ctrl+C to exit.\n");

while (1) {
    unsigned short keyState = 0;
    // Read 16 bits (one for each key)
    for (int i = 0; i < 16; i++) {
        digitalWrite(GPIO_17, LOW);
        delayMicroseconds(2); // Short delay
        digitalWrite(GPIO_17, HIGH);
        delayMicroseconds(2); // Short delay

        int bit = digitalRead(GPIO_18);
        // TTP229: 0 = pressed, 1 = not pressed
        if (bit == 0) {
            keyState |= (1 << i);
        }
    }

    // Print pressed keys
    printf("Pressed keys: ");
    for (int i = 0; i < 16; i++) {
        if (keyState & (1 << i)) {
            printf("%d ", i+1); // Key numbers 1-16
        }
    }
    printf("\n");

    delay(100); // 100 ms
}

*/

/*
wiringPiSetup();
    
pinMode(GPIO_17, OUTPUT);
pinMode(GPIO_18, INPUT);

while (1) {
    digitalWrite(GPIO_17, LOW);
    delayMicroseconds(2);
    digitalWrite(GPIO_17, HIGH);
    delayMicroseconds(2);

    printf("SDO: %d\n", digitalRead(GPIO_18));
    delay(100);
}
*/

//tempTest();
/*
    A4988_Stepper stepper_test =
    {
        .dir_pin = GPIO_26,
        .step_pin = GPIO_21,
        .enable_pin = GPIO_16
    };
    
    A4988_Setup(stepper_test);
    
    while(1)
    {
        // prev speed delay: 850
        A4988_Step(stepper_test, 2000, 850, FORWARD);
        A4988_Step(stepper_test, 2000, 850, BACKWARDS);
    }
    
    //Todo: test the manual controll of A4988
    */
    

    /*
    int pca_fd;
    pca_fd = PCA9685_Setup();
    
    for(int i = 0; i < 16; i++)
    {
        PCA9685_SetPWM(pca_fd, i, 0, 307);
        //sleep(1);
        delay(1000);
        PCA9685_SetPWM(pca_fd, i, 0, 205);
        //sleep(1);
        delay(1000);
        PCA9685_SetPWM(pca_fd, i, 0, 510);
        //sleep(1);
        delay(1000);
    }
    */


/*
int fd = wiringPiI2CSetup(PCA9685_ADDR);
if (fd < 0) {
    printf("Failed to init I2C communication.\n");
}
setPWMFreq(fd, 50); // 50Hz for servos

// Typical servo pulse: 1ms (min), 1.5ms (center), 2ms (max)
// At 50Hz, period = 20ms, so 4096 steps = 20ms
// 1ms = 205, 1.5ms = 307, 2ms = 410 (approx)


for (int i = 0; i < 16; i++)
{
    setPWM(fd, i, 0, 307); // Center position
    
    printf("Sent center pulse to channel 0\n");
    sleep(1);
    
    setPWM(fd, i, 0, 205); // Min position
    printf("Sent min pulse to channel 0\n");
    sleep(1);
    
    setPWM(fd, i, 0, 510); // Max position
    printf("Sent max pulse to channel 0\n");
    sleep(1);
}
*/


/*
Setup_TTP229();

    printf("TTP229 16-key test. Press keys...\n");

    while (1) {
       
        
        
        wait_for_key_event(); // Wait for key press
                uint16_t keys = TTP229_GetPressed();
                print_keys(keys);
                wait_for_key_release(); // Wait for key release
                delay(100); // Debounce
            
    }
*/


/*
LCD_I2C lcd_i2c =
{
    .lcd_size  = LCD_16x2,
    .backlight = true,
    .unicode   = true,
    .pre_clear = true
};

LCD_I2C_init(lcd_i2c);
//LCD_set_cursor(0);
//LCD_write_string("John Doe fhdsjkfh");
while(1)
{
    delay(500);
    //LCD_clear();
    //LCD_scroll_text("Hello here some text scrolling lol", 0, 500);
    LCD_set_cursor(0);
    LCD_printf(false, "%s", "string test");
    
    LCD_set_cursor(1);
    //LCD_printf(true, "%s", "aBcDefghijklmnopwwehjfg");
    LCD_write_string("î");
    // Resulted: șȘîÎâÂîțșȘ
}
*/

configuration_setup();

}