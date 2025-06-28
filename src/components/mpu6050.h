#ifndef MPU6050_H
#define MPU6050_H



#define MPU6050_ADDR 0x68

#define PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43


typedef struct
{
    float ax, ay, az, gx, gy, gz, pitch, roll;
}MPU6050_fData;

void MPU6050_Setup();
MPU6050_fData ReadMPU6050();
#endif