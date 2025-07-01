#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdbool.h>
#include <stdint.h>



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
    bool unicode;
}LCD_I2C;


void LCD_I2C_init(LCD_I2C settings);
void LCD_create_char(uint8_t location, uint8_t charmap[]);
void LCD_printf(bool text_scroll, const char * fmt, ...); // Todo: 
void LCD_write_string(const char *str);
void LCD_scroll_text(const char *msg, int row, int delay_ms);
void LCD_set_cursor(int line);
void LCD_clear();
#endif