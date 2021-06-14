#include "r_cg_macrodriver.h"

void LCD_write_byte(uint8_t isData, uint8_t byte);
void LCD_gotoXY(uint8_t x, uint8_t y);
void LCD_clear(void);
void LCD_putc(uint8_t c);
void LCD_puts(uint8_t * str);