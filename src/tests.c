#include <log_c/log.h>






#include "components/A4988.h"

#include "tests.h"

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




void RunTest(enum ComponentTest tt, enum TestMode tm, bool loop)
{
    if(tt == CT_SERVO)
    {
        log_info("Running servo test");
    }
    else if(tt == CT_STEPPER)
    {
        log_info("Running stepper test");
    }
    else if(tt == CT_H_BRIDGE_L298N)
    {
        log_info("Running H-Bridge L298N test");
    }
    else if(tt == CT_DHT)
    {
        log_info("Running DHT test");
    }
    else if(tt == CT_LCD_I2C)
    {
        log_info("Running LCD_I2C test");
    }
    else if(tt == CT_LCD)
    {
        log_info("Running LCD test");
    }
    else if(tt == CT_OLED)
    {
        log_info("Running OLED test");
    }
    else if(tt == CT_TFT)
    {
        log_info("Running TFT test");
    }
    else if(tt == CT_SEVEN_SEG_DISPLAY)
    {
        log_info("Running seven segment display test");
    }
    else if(tt == CT_MPU6050)
    {
        log_info("Running MPU6050 test");
    }
    else if(tt == CT_ULTRASONIC_HC06)
    {
        log_info("Running ultrasonic HC06 test");
    }
    else if(tt == CT_KEYPAD_2X4)
    {
        log_info("Running keypad 2x4 test");
    }
    else if(tt == CT_KEYPAD_4X4)
    {
        log_info("Running keypad 4x4 test");
    }
    else if(tt == CT_KEYPAD_3X4)
    {
        log_info("Running keypad 3x4 test");
    }
    else if(tt == CT_INFRARED)
    {
        log_info("Running infrared test");
    }
    else if(tt == CT_LED_MATRIX)
    {
        log_info("Running LED matrix test");
    }
    else if(tt == CT_WATER_LEVEL)
    {
        log_info("Running water level test");
    }
    else if(tt == CT_SOIL_MOISTURE)
    {
        log_info("Running soil moisture test");
    }
    else if(tt == CT_SPEED_SENSOR)
    {
        log_info("Running speed sensor test");
    }
    else if(tt == CT_GAS_SENSOR)
    {
        log_info("Running gas sensor test");
    }
    else if(tt == CT_SMOKE_DETECTOR)
    {
        log_info("Running smoke detector test");
    }
    else if(tt == CT_MICROPHONE)
    {
        log_info("Running microphone test");
    }
    else if(tt == CT_PH_METER)
    {
        log_info("Running pH meter test");
    }
    else if(tt == CT_HALL_SENSOR)
    {
        log_info("Running hall sensor test");
    }
    else if(tt == CT_FLOW_METER)
    {
        log_info("Running flow meter test");
    }
    else if(tt == CT_POTENTIOMETER)
    {
        log_info("Running potentiometer test");
    }
    else if(tt == CT_PHOTORESISTOR)
    {
        log_info("Running photoresistor test");
    }
    else if(tt == CT_STEPPER_MOTOR_ULN2003)
    {
        log_info("Running stepper motor ULN2003 test");
    }
    else if(tt == CT_RFID_RC522)
    {
        log_info("Running RFID RC522 test");
    }
    else if(tt == CT_JOYSTICK_X2)
    {
        log_info("Running joystick X2 test");
    }
    else if(tt == CT_IR_REMOTE)
    {
        log_info("Running IR remote test");
    }
    else if(tt == CT_PCA9685)
    {
        log_info("Running PCA9685 test");
    }
    else if(tt == CT_A4988_DRIVER)
    {
        log_info("Running A4988 driver test");
    }
    else if(tt == CT_RT_CLOCK_DS1302)
    {
        log_info("Running RTC DS1302 test");
    }
    else if(tt == CT_RT_CLOCK_DS3231)
    {
        log_info("Running RTC DS3231 test");
    }
    else if(tt == CT_RT_CLOCK_DS1307)
    {
        log_info("Running RTC DS1307 test");
    }
    else if(tt == CT_ARDUINO_UNO)
    {
        log_info("Running Arduino Uno test");
    }
    else if(tt == CT_ARDUINO_MEGA)
    {
        log_info("Running Arduino Mega test");
    }
    else if(tt == CT_ARDUINO_NANO)
    {
        log_info("Running Arduino Nano test");
    }
    else if(tt == CT_ARDUINO_GIGA)
    {
        log_info("Running Arduino Giga test");
    }
}