#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>


enum TestType
{
    Servo,               // yes
    Stepper,             // ???
    H_BridgeL298N,       // yes
    DHT,                 // yes
    LCD_I2C,             // yes
    LCD,                 // yes
    OLED,                // yes
    TFT,                 // yes
    Seven_Seg_Display,   // yes
    MPU6500,             // yes (Giroscopic sensor)
    UltrasonicHC06,      // yes
    Keypad2x4,           // Not self contained
    Keypad4x4,           // Not self contained
    Keypad3x4,           // Not self contained
    Infrared,            // yes
    LED_Matrix,          // todo
    WaterLevel,          // yes (Analog)
    SoilMoisture,        // yes (Analogic)
    SpeedSensor,         // yes
    GasDetector,         // yes
    SmokeDetector,       // yes
    Microphone,          // yes
    PH_Meter,            // todo
    HallSensor,          // yes
    FlowMeter,           // yes
    Potentiometer,       // yes
    Photoresistor,       // yes
    StepperMotorULN2003, // yes
    RFID_RC522,          // todo
    JoystickX2,          // yes
    IR_Remote,           //
    PCA9685,             // yes
    A4988_Stepper,       // yes
    RT_Clock_DS1302,     // Not Self contained
    RT_Clock_DS3231,     // Not Self contained
    RT_Clock_DS1307,     // Not Self contained
};

void RunAutomaticTest(enum TestType t, bool loop);
void GetRealtimeData();
void StopLoopTest();



#endif