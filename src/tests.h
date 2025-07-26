#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>


enum TestMode
{
    MANUAL,
    AUTOMATIC
};


enum ComponentTest
{
                              /* on the UI list | Component implemented |*/
    CT_SERVO = 1,             //      yes       |          yes          |
    CT_STEPPER,               //      ???       |                       |
    CT_H_BRIDGE_L298N,        //      yes       |                       |
    CT_DHT,                   //      yes       |          yes          |
    CT_LCD_I2C,               //      yes       |          yes          |
    CT_LCD,                   //      yes       |                       |
    CT_OLED,                  //      yes       |                       |
    CT_TFT,                   //      yes       |                       |
    CT_SEVEN_SEG_DISPLAY,     //      yes       |                       |
    CT_MPU6050,               //      yes       |          yes          |
    CT_ULTRASONIC_HC06,       //      yes       |          yes          |
    CT_KEYPAD_2X4,            //                |          yes          |
    CT_KEYPAD_4X4,            //                |          yes          |
    CT_KEYPAD_3X4,            //                |          yes          |
    CT_INFRARED,              //      yes       |                       |
    CT_LED_MATRIX,            //      yes       |                       |
    CT_WATER_LEVEL,           //      yes       |                       |
    CT_SOIL_MOISTURE,         //      yes       |                       |
    CT_SPEED_SENSOR,          //      yes       |                       |
    CT_GAS_SENSOR,            //      yes       |                       |
    CT_SMOKE_DETECTOR,        //      yes       |                       |
    CT_MICROPHONE,            //      yes       |                       |
    CT_PH_METER,              //                |                       |
    CT_HALL_SENSOR,           //      yes       |                       |
    CT_FLOW_METER,            //      yes       |                       |
    CT_POTENTIOMETER,         //      yes       |                       |
    CT_PHOTORESISTOR,         //      yes       |                       |
    CT_STEPPER_MOTOR_ULN2003, //      yes       |          yes          |
    CT_RFID_RC522,            //                |      in progress      |
    CT_JOYSTICK_X2,           //      yes       |                       |
    CT_IR_REMOTE,             //      yes       |                       |
    CT_PCA9685,               //      yes       |          yes          |
    CT_A4988_DRIVER,          //      yes       |          yes          |
    CT_RT_CLOCK_DS1302,       //                |                       |
    CT_RT_CLOCK_DS3231,       //                |                       |
    CT_RT_CLOCK_DS1307,       //                |                       |
    CT_TTP229,                //                |                       |
    CT_ARDUINO_UNO,           //      yes       |                       |
    CT_ARDUINO_MEGA,          //      yes       |                       |
    CT_ARDUINO_NANO,          //      yes       |                       |
    CT_ARDUINO_GIGA,          //      yes       |                       |
    CT_RESISTOR
};


void SetupTest(enum ComponentTest tt);
void RunTest(enum ComponentTest tt, enum TestMode tm);
void GetRealtimeData();
void StopLoopTest();



#endif