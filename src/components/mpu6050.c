#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <log_c/log.h>
#include <math.h>




#include "mpu6050.h"
#include "../gpio_utils.h"


// Read 16-bit value from two registers
int read_word_2c(int fd, int reg)
{
    int high = wiringPiI2CReadReg8(fd, reg);
    int low = wiringPiI2CReadReg8(fd, reg+1);
    int val = (high << 8) + low;
    if (val >= 0x8000)
        val = -((65535 - val) + 1);
    return val;
}

void ReadMPU6050()
{
    if(isI2C_available())
    {
        int fd = wiringPiI2CSetup(MPU6050_ADDR);
        if (fd == -1)
        {
            log_error("Failed to setup wiring Pi I2C!");
        }
        else
        {
            log_info("MPU6050 successfully connected.\n");
            
            wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0);
            
            while(1)
            {
                // Read raw accelerometer data
                int16_t acc_x = read_word_2c(fd, ACCEL_XOUT_H);
                int16_t acc_y = read_word_2c(fd, ACCEL_XOUT_H + 2);
                int16_t acc_z = read_word_2c(fd, ACCEL_XOUT_H + 4);
                
                // Read raw gyroscope data
                int16_t gyro_x = read_word_2c(fd, GYRO_XOUT_H);
                int16_t gyro_y = read_word_2c(fd, GYRO_XOUT_H + 2);
                int16_t gyro_z = read_word_2c(fd, GYRO_XOUT_H + 4);
                
                // Convert to 'g' and 'deg/s'
                float Ax = acc_x / 16384.0;
                float Ay = acc_y / 16384.0;
                float Az = acc_z / 16384.0;
                
                float Gx = gyro_x / 131.0;
                float Gy = gyro_y / 131.0;
                float Gz = gyro_z / 131.0;
                
                // Calculate pitch and roll (in degrees)
                float pitch = atan2(Ay, sqrt(Ax*Ax + Az*Az)) * 180 / M_PI;
                float roll  = atan2(-Ax, Az) * 180 / M_PI;
                
                printf("Accel: X=%.2f Y=%.2f Z=%.2f g | Gyro: X=%.2f Y=%.2f Z=%.2f deg/s | Pitch=%.2f Roll=%.2f\n", Ax, Ay, Az, Gx, Gy, Gz, pitch, roll);
                
                usleep(50000); // 50ms delay
            }
        }
    }
}