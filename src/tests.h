#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>


enum TestType
{
    Servo,
    Stepper,
    H_BridgeL298N,
    DHT,
    LCD_I2C,
    MPU6500,
    Ultrasonic,
    Keypad2x4,
    Keypad4x4,
    Keypad3x4,
    Infrared,
    LED_Matrix,
    WaterLevel,
    SoilMoisture,
    SpeedSensor,
    GasDetector,
    SmokeDetector,
    Microphone,
    PH_Meter,
    HallSensor,
    FlowMeter,
    Potentiometer,
    Photoresistor,
    StepperMotorULN2003,
    RFID_RC522,
    JoystickX2,
    IR_Remote,
    PCA9685,
    A4988_Stepper,
    RT_Clock_DS1302,
    RT_Clock_DS3231,
    RTClock_DS1307,
};

void RunAutomaticTest(enum TestType t, bool loop);
void GetRealtimeData();
void StopLoopTest();



#endif