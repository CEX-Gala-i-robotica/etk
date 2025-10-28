#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <log_c/log.h>


#include "LCD_I2C.h"






/*
Todo: Remake the entire unicode  mapping and fix the unicode chars...
*/




#define LCD_I2C_ADDR           0x27
#define LCD_CHR                1          // Mode - Sending data
#define LCD_CMD                0          // Mode - Sending command
#define LCD_BACKLIGHT          0x08       // On
#define LCD_NO_BACKLIGHT       0x00       // Off
#define ENABLE                 0b00000100 // Enable bit
#define LCD_CMD_INIT           0x33
#define LCD_CMD_SET_4_BIT_MODE 0x32
#define LCD_MOVE_CURSOR_DIR    0x06
#define LCD_TUR_OFF_CURSOR     0x0C
#define LCD_SET_2_LINE_DISPLAY 0x28
#define LCD_CLEAR_DISPLAY      0x01
#define LCD_CGRAM              0x40
#define LCD_LINE_1             0x80
#define LCD_LINE_2             0xC0
#define LCD_LINE_3             0x94
#define LCD_LINE_4             0xD4









LCD_I2C defaults =
{
    .lcd_size  = LCD_16x2,
    .backlight = true,
    .unicode   = true,
    .pre_clear = true
};

int lcd_fd;
int current_line = -1;
bool is_lcd_init;
bool is_scroll_enabled;
bool is_backlight;
enum LCD_I2C_Size current_lcd_size;




// That's ugly af
int utf8_to_custom(const char *s)
{
    // ă (U+0103) in UTF-8: 0xC4 0x83
    if((unsigned char)s[0] == 0xC4 && (unsigned char)s[1] == 0x83) return 0;
    // Ă (U+0102) in UTF-8: 0xC4 0x82
    if((unsigned char)s[0] == 0xC4 && (unsigned char)s[1] == 0x82) return 1;

    // â (U+00E2) in UTF-8: 0xC3 0xA2
    if((unsigned char)s[0] == 0xC3 && (unsigned char)s[1] == 0xA2) return 2;
    // Â (U+00C2) in UTF-8: 0xC3 0x82
    if((unsigned char)s[0] == 0xC3 && (unsigned char)s[1] == 0x82) return 3;

    // î (U+00EE) in UTF-8: 0xC3 0xAE
    if((unsigned char)s[0] == 0xC3 && (unsigned char)s[1] == 0xAE) return 4;
    // Î (U+00CE) in UTF-8: 0xC3 0x8E
    if((unsigned char)s[0] == 0xC3 && (unsigned char)s[1] == 0x8E) return 5;

    // ș (U+0219) in UTF-8: 0xC8 0x99
    if((unsigned char)s[0] == 0xC8 && (unsigned char)s[1] == 0x99) return 6;
    // Ș (U+0218) in UTF-8: 0xC8 0x98
    if((unsigned char)s[0] == 0xC8 && (unsigned char)s[1] == 0x98) return 7;

    // ț (U+021B) in UTF-8: 0xC8 0x9B
    
    if((unsigned char)s[0] == 0xC8 && (unsigned char)s[1] == 0x9B) return 8;
    // Ț (U+021A) in UTF-8: 0xC8 0x9A
    
    if((unsigned char)s[0] == 0xC8 && (unsigned char)s[1] == 0x9A) return 9;
 
    return -1;
}



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
    int high;
    int low; 
    if(is_backlight)
    {
        high = mode | (bits & 0xF0) | LCD_BACKLIGHT;
        low  = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT;
    }
    else
    {
        high = mode | (bits & 0xF0) | LCD_NO_BACKLIGHT;
        low  = mode | ((bits << 4) & 0xF0) | LCD_NO_BACKLIGHT;
    }

    wiringPiI2CWrite(lcd_fd, high);
    lcd_toggle_enable(high);

    wiringPiI2CWrite(lcd_fd, low);
    lcd_toggle_enable(low);
}

void LCD_I2C_init(LCD_I2C settings)
{
    is_backlight = settings.backlight;
    int char_location = 0;
    lcd_fd = wiringPiI2CSetup(LCD_I2C_ADDR);
    if(lcd_fd == -1)
    {
        is_lcd_init = false;
        log_error("Failed to setup wiring Pi I2C!");
    }
    else
    {
        lcd_byte(LCD_CMD_INIT,           LCD_CMD);
        lcd_byte(LCD_CMD_SET_4_BIT_MODE, LCD_CMD);
        lcd_byte(LCD_MOVE_CURSOR_DIR,    LCD_CMD);
        lcd_byte(LCD_TUR_OFF_CURSOR,     LCD_CMD);
        lcd_byte(LCD_SET_2_LINE_DISPLAY, LCD_CMD);
        if(settings.pre_clear)
        {
            lcd_byte(LCD_CLEAR_DISPLAY, LCD_CMD);
        }
        
        if(settings.unicode)
        {
            /*
            Todo: Implement proper unicode handling
            */
            log_info("Todo...");
        }
        usleep(5000);
        is_lcd_init = true;
    }
}

void LCD_create_char(uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // Only 0-7 are valid
    lcd_byte(LCD_CGRAM | (location << 3), LCD_CMD); // Set CGRAM address
    
    for(int i = 0; i < 8; i++)
    {
        lcd_byte(charmap[i], LCD_CHR); // Write pattern row
    }
}

void LCD_write_string(const char *str)
{
    int msg_len = strlen(str);
    char buf[LCD_WIDTH_16 + 1];
    int unicode_chars;
    if(!is_lcd_init)
    {
        log_error("LCD I2C: Not initialized !!!");
    }
    else
    {
        if(current_line == -1)
        {
            log_warn("LCD I2C: No cursor line was set !!!");
        }
        while(*str)
        {
            unicode_chars = utf8_to_custom(str);
            if(unicode_chars >= 0)
            {
                lcd_byte(unicode_chars, LCD_CHR);
                str += 2;
            }
            else
            {
                if((unsigned char)*str >= 0x20 && (unsigned char)*str <= 0x7E)
                {
                    lcd_byte(*str, LCD_CHR);
                }
                else
                {
                    lcd_byte(' ', LCD_CHR); // Replace unknowns with space
                }
                str++;
            }
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
        current_line = line;
        int addr[] = {LCD_LINE_1, LCD_LINE_2, LCD_LINE_3, LCD_LINE_4}; // For 4-line displays
        lcd_byte(addr[line], LCD_CMD);
    }
}

void LCD_printf(bool text_scroll, const char * fmt, ...)
{
    va_list args;
    char buf[1500];
    
    if(!is_lcd_init)
    {
        log_error("LCD I2C: Not initialized !!!");
    }
    else
    {
        va_start(args, fmt);
        
        if(current_line == -1)
        {
            log_warn("LCD I2C: No cursor line was set !!!");
        }
        
        vsnprintf(buf, sizeof(buf), fmt, args);
        if(text_scroll)
        {
            //log_info("current line: %d", current_line);
            LCD_scroll_text(buf, current_line, 600);
        }
        else
        {
            LCD_write_string(buf);
        }
        
        va_end(args);
    }
    
}

void LCD_clear()
{
    lcd_byte(LCD_CLEAR_DISPLAY, LCD_CMD); // 0x01 is the clear display command
    delay(2);
}

/*
Todo: Add more advanced LCD testing (Testing each dot from the character blocks)
*/