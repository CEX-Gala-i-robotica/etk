#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdbool.h>



#define LCD_WIDTH_16 16

enum LCD_I2C_Size
{
    LCD_16x2,
    LCD_20x4
};

typedef struct
{
    enum LCD_I2C_Size lcd_size;
    bool pre_clear;
    bool backlight;
    bool unicode_support;
}LCD_I2C;


void LCD_I2C_Init(bool text_scroll);
void LCD_Enable_Scroll(int width);
void LCD_printf(const char * fmt, ...); // Todo: 
void LCD_write_string(const char *str);
void LCD_scroll_text(const char *msg, int row, int delay_ms);
void LCD_set_cursor(int line);
void LCD_Clear();
// void RunLCD_I2C_Test(); // Deprecated
#endif