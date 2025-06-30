#ifndef MPU6050_H
#define MPU6050_H





typedef struct
{
    float ax, ay, az, gx, gy, gz, pitch, roll;
}MPU6050_fData;

void MPU6050_Setup();
MPU6050_fData ReadMPU6050();
#endif