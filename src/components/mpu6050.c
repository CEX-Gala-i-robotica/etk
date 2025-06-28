#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <log_c/log.h>
#include <math.h>




#include "mpu6050.h"
#include "../gpio_utils.h"



bool is_dev_init;
int fd;


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

void MPU6050_Setup()
{
    if(isI2C_available())
    {
        fd = wiringPiI2CSetup(MPU6050_ADDR);
        if (fd == -1)
        {
            log_error("Failed to setup wiring Pi I2C!");
            is_dev_init = false;
        }
        else
        {
            fd = wiringPiI2CSetup(MPU6050_ADDR);
            if (fd == -1)
            {
                log_error("Failed to setup wiring Pi I2C!");
                is_dev_init = false;
            }
            else
            {
                log_info("MPU6050 successfully connected.\n");
                wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0);
                is_dev_init = true;
            }
        }
    }
    else
    {
        log_error("I2C Is Unavailable !!!");
        is_dev_init = false;
    }
}

MPU6050_fData ReadMPU6050()
{
    MPU6050_fData out;
    
    if(!is_dev_init)
    {
        log_error("MPU6050 Not initialized !!!");
    }
    else
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
        
        out.ax = Ax;
        out.ay = Ay;
        out.az = Az;
        out.gx = Gx;
        out.gy = Gy;
        out.gz = Gz;
        out.pitch = pitch;
        out.roll = roll;
        
        usleep(50000); // 50ms delay
    }

    return out;
}