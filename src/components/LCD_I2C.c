#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <log_c/log.h>


#include "LCD_I2C.h"





#define LCD_I2C_ADDR 0x27

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LCD_BACKLIGHT   0x08  // On
//#define LCD_BACKLIGHT 0x00  // Off

#define ENABLE  0b00000100 // Enable bit




int lcd_fd;
bool is_lcd_init;
bool is_scroll_enabled;

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

void LCD_I2C_Init(bool text_scroll)
{
    lcd_fd = wiringPiI2CSetup(LCD_I2C_ADDR);
    is_scroll_enabled = text_scroll;
    if(lcd_fd == -1)
    {
        is_lcd_init = false;
        log_error("Failed to setup wiring Pi I2C!");
    }
    else
    {
        lcd_byte(0x33, LCD_CMD); // Initialize
        lcd_byte(0x32, LCD_CMD); // Set to 4-bit mode
        lcd_byte(0x06, LCD_CMD); // Cursor move direction
        lcd_byte(0x0C, LCD_CMD); // Turn cursor off
        lcd_byte(0x28, LCD_CMD); // 2 line display
        lcd_byte(0x01, LCD_CMD); // Clear display
        usleep(5000);
        is_lcd_init = true;
    }
}

void LCD_write_string(const char *str)
{
    int msg_len = strlen(str);
    char buf[LCD_WIDTH_16 + 1];
    if(!is_lcd_init)
    {
        log_error("LCD I2C: Not initialized !!!");
    }
    else
    {
        while(*str)
        {
            lcd_byte(*str++, LCD_CHR);
        }
    }
}

void LCD_scroll_text(const char *msg, int row, int delay_ms)
{
    int msg_len = strlen(msg);
    char buf[LCD_WIDTH_16 + 1];

    // If message is shorter than LCD width, just display it
    if(msg_len <= LCD_WIDTH_16)
    {
        LCD_set_cursor(row);
        LCD_write_string(msg);
        return;
    }

    // Scroll the message
    for(int i = 0; i <= msg_len - LCD_WIDTH_16; i++)
    {
        strncpy(buf, msg + i, LCD_WIDTH_16);
        buf[LCD_WIDTH_16] = '\0';

        LCD_set_cursor(row);
        LCD_write_string(buf);

        usleep(delay_ms * 1000); // delay in milliseconds
    }
}

void LCD_set_cursor(int line)
{
    if(!is_lcd_init)
    {
        log_error("LCD I2C: Not initialized !!!");
    }
    else
    {
        int addr[] = {0x80, 0xC0, 0x94, 0xD4}; // For 4-line displays
        lcd_byte(addr[line], LCD_CMD);
    }
}

void LCD_printf(const char * fmt, ...)
{
    va_list args;
    char buf[1500];
    va_start(args, fmt);
    
    vsnprintf(buf, sizeof(buf), fmt, args);
    LCD_write_string(buf);
    
    va_end(args);
    
}

void LCD_Clear()
{
    lcd_byte(0x01, LCD_CMD); // 0x01 is the clear display command
    delay(2);
}

//void RunLCD_I2C_Test()
//{
//    LCD_I2C_Init();
//
//    LCD_set_cursor(0); // First line
//    LCD_write_string("Hello, World!");
//
//    LCD_set_cursor(1); // Second line
//    LCD_write_string("LCD via I2C!");
//}

/*
Todo: Add more advanced LCD testing (Testing each dot from the character blocks)
*/