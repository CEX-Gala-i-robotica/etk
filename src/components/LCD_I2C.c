#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <log_c/log.h>


#include "LCD_I2C.h"


int lcd_fd;

// Low level write to LCD
void lcd_toggle_enable(int bits)
{
    usleep(500);
    wiringPiI2CWrite(lcd_fd, (bits | ENABLE));
    usleep(500);
    wiringPiI2CWrite(lcd_fd, (bits & ~ENABLE));
    usleep(500);
}

void lcd_byte(int bits, int mode)
{
    int high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
    int low  = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;

    wiringPiI2CWrite(lcd_fd, high);
    lcd_toggle_enable(high);

    wiringPiI2CWrite(lcd_fd, low);
    lcd_toggle_enable(low);
}

void lcd_init()
{
    lcd_byte(0x33, LCD_CMD); // Initialize
    lcd_byte(0x32, LCD_CMD); // Set to 4-bit mode
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // Turn cursor off
    lcd_byte(0x28, LCD_CMD); // 2 line display
    lcd_byte(0x01, LCD_CMD); // Clear display
    usleep(5000);
}

void lcd_write_string(const char *str)
{
    while(*str)
    {
        lcd_byte(*str++, LCD_CHR);
    }
}

void lcd_set_cursor(int line)
{
    int addr[] = {0x80, 0xC0, 0x94, 0xD4}; // For 4-line displays
    lcd_byte(addr[line], LCD_CMD);
}

void RunLCD_I2C_Test()
{
    lcd_fd = wiringPiI2CSetup(LCD_ADDR);
    if (lcd_fd == -1)
    {
        log_error("Failed to setup wiring Pi I2C!");
    }
    lcd_init();

    lcd_set_cursor(0); // First line
    lcd_write_string("Hello, World!");

    lcd_set_cursor(1); // Second line
    lcd_write_string("LCD via I2C!");
}