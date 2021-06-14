#include "GLCD128x64.h"
#include "r_cg_macrodriver.h"
#include "rskrl78l13def.h"
#include "r_cg_sau.h"
#include "Fonts.h"



void LCD_write_byte(uint8_t isData, uint8_t byte)
{
    if (isData)
    LCD_A0 = 1;
    else
    LCD_A0 = 0;
 
    Sync_Send_Byte(byte);
}

void LCD_gotoXY(uint8_t x, uint8_t y)
{
    LCD_write_byte(0, 0xB0 | (y));
    LCD_write_byte(0, x & 0x0F);
    LCD_write_byte(0, 0x10 | ((x >> 4) & 0x0F));
}

void LCD_clear(void)
{
    uint8_t i, j;
    for (i = 0; i < 8; i++)
    {
        LCD_gotoXY(0, i);
        for (j = 0; j < 132; j++)
        {
            LCD_write_byte(1, 0);
        }
    }
    LCD_gotoXY(0,0);
}

void LCD_putc(uint8_t c)
{
    if ((c >= 0x20) && (c <= 0x7F))
    {
        c = c - 32U;
        LCD_A0 = 1;

        Sync_Send_Array(font6x8[c], 6);
    }
}

void LCD_puts(uint8_t * str)
{
    while (* str)
    LCD_putc(* str++);
}





