#include "LCDlib.h"
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#include "Fonts.h"
#include "IO_Config.h"
#include "Sys.h"
#include "r_cg_tau.h"


void LCD_write(uint8_t isData, uint8_t byte)
{
    if (isData)
    LCD_A0 = 1;
    else
    LCD_A0 = 0;
 
    Sync_Send_Byte(byte);
}

uint8_t LCD_ST = 2;
void LCD_init(void)
{
  LCD_RST = LOW;
  R_TAU_MsDelay(1);
  LCD_RST = HIGH;
  R_TAU_MsDelay(1);
  LCD_write(0, LCD_RESET);
  R_TAU_MsDelay(1);
  LCD_write(0, SET_BIAS);
  LCD_write(0, POWER_CONTROL);
  R_TAU_MsDelay(50);
  LCD_write(0, REGULATION_RESISTOR_RATIO);
  LCD_write(0, DISPLAY_ON);
  LCD_write(0, ADC_REVERSE);
  LCD_write(0, VERTICAL_DIRECTION_REVERSE);
  LCD_contrast_set(screen_Contrast);
  // Set_LCD_BackLight_Level(screen_BackLight);   tam thoi chua co backlight
  LCD_clear();
  LCD_ST = 1;

}

void LCD_Power_saver() {  // tanhhc:  chua test func nay
  if (LCD_ST != 0) {
    LCD_write(0, DISPLAY_OFF);
    LCD_write(0, DISPLAY_ALL_POINT_ON);

    LCD_CS = 0;
    LCD_A0 = 1;
//    LCD_SCL = 1;          tanhhc:  Luu y cho nay chuyen thanh disable bo SPI, vi qua Renesas minh dung SPI de giao tiep
//    LCD_SDI = 1;

    LCD_ST = 0;
  }
}

void LCD_Normal_Mode() {        // tanhhc: chua test func nay, tai sao lai khong reset LCD, set bias, resistor ratio nua, ... nhu ham LCD_init?
  if (LCD_ST != 1) {
    LCD_write(0, DISPLAY_ALL_POINT_OFF);
    LCD_write(0, DISPLAY_ON);
    LCD_write(0, POWER_CONTROL);
    LCD_write(0, ADC_REVERSE);
    LCD_write(0, VERTICAL_DIRECTION_REVERSE);
    LCD_contrast_set(screen_Contrast);
    //Set_LCD_BackLight_Level(screen_BackLight);    tam thoi chua co backlight
    LCD_clear();

    LCD_ST = 1;
  }
}  

void LCD_contrast_set(uint8_t contrastLevel) {
  LCD_write(0, ELECTRONIC_VOLUME_MODE);
  switch (contrastLevel) {
  case CONTRAST_LEVEL_1:
    LCD_write(0, _CONTRAST_LEVEL_1);
    break;
  case CONTRAST_LEVEL_2:
    LCD_write(0, _CONTRAST_LEVEL_2);
    break;
  case CONTRAST_LEVEL_3:
    LCD_write(0, _CONTRAST_LEVEL_3);
    break;
  case CONTRAST_LEVEL_4:
    LCD_write(0, _CONTRAST_LEVEL_4);
    break;
  case CONTRAST_LEVEL_5:
    LCD_write(0, _CONTRAST_LEVEL_5);
    break;
  default:
    LCD_write(0, _CONTRAST_LEVEL_2);
  }
}




void LCD_gotoXY(uint8_t x, uint8_t y)
{
    LCD_write(0, 0xB0 | (y));
    LCD_write(0, x & 0x0F);
    LCD_write(0, 0x10 | ((x >> 4) & 0x0F));
}

void LCD_clear(void)
{
    uint8_t i, j;
    for (i = 0; i < 8; i++)
    {
        LCD_gotoXY(0, i);
        for (j = 0; j < 132; j++)
        {
            LCD_write(1, 0);
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





