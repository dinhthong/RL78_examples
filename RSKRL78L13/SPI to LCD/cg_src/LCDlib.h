#ifndef __LCDLIB_H
#define __LCDLIB_H
#include "r_cg_macrodriver.h"

/*		Define Constant, Command Code
*/
#define LCD_WIDTH			128
#define LCD_HEIGHT		    8
#define DEPTH_SEGMENTS	    4
#define	SET_BIAS		    0xA3 			//0xA3 or 0xA2
#define DISPLAY_ON		    0xAF
#define DISPLAY_OFF		    0xAE
#define POWER_CONTROL	    0x2F
#define LCD_RESET			0xE2

#define DISPLAY_ALL_POINT_ON		0xA5
#define DISPLAY_ALL_POINT_OFF		0xA4

#define DISPLAY_REVERSE	            0xA7		//reverse all points of Display panel (black->white and vice versa)
#define DISPLAY_NORMAL	            0xA6		
#define ADC_NORMAL			        0xA0
#define ADC_REVERSE			        0xA1
#define VERTICAL_DIRECTION_NORMAL	0xC0
#define VERTICAL_DIRECTION_REVERSE	0xC8

#define REGULATION_RESISTOR_RATIO   0x24    // 0x24 or 0x20
#define ELECTRONIC_VOLUME_MODE		0x81

#define _CONTRAST_LEVEL_1			0x0A    //  0x0A or 0x18
#define _CONTRAST_LEVEL_2			0x1C
#define _CONTRAST_LEVEL_3			0x20
#define _CONTRAST_LEVEL_4			0x2D
#define _CONTRAST_LEVEL_5			0x30

/**************************************************************/
/*  Writing a data byte or a command to LCD  */

void LCD_write(uint8_t isData, uint8_t byte);

/*		Initializing LCD
*/
void LCD_init(void);
void LCD_Power_saver();
void LCD_Normal_Mode();

void LCD_contrast_set(uint8_t contrastLevel);



void LCD_gotoXY(uint8_t x, uint8_t y);
void LCD_clear(void);
void LCD_putc(uint8_t c);
void LCD_puts(uint8_t * str);

#endif