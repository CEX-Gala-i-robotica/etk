#ifndef LCD_I2C_H
#define LCD_I2C_H




#define LCD_ADDR 0x27

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LCD_BACKLIGHT   0x08  // On
//#define LCD_BACKLIGHT 0x00  // Off

#define ENABLE  0b00000100 // Enable bit

void RunLCD_I2C_Test();
#endif