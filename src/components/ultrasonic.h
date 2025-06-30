#ifndef ULTRASONIC_H
#define ULTRASONIC_H


void Ultrasonic_Setup(int echo, int trig);
float Ultrasonic_GetDistance(int echo, int trig);
void RunUltrasonicSensorTest(int trig, int echo);
#endif