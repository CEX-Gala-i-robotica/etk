#ifndef LCD_I2C_H
#define LCD_I2C_H






void LCD_I2C_Init();
void LCD_printf(const char * fmt, ...); // Todo: 
void LCD_write_string(const char *str);
void LCD_set_cursor(int line);
// void RunLCD_I2C_Test(); // Deprecated
#endif