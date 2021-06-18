#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "Sys.h"

/*	Define Buttons*/
#define _B_1			61
#define _B_2			71
#define _B_3			81
#define _B_4			62
#define _B_5			72
#define _B_6			82
#define _B_7			63
#define _B_8			73
#define _B_9			83
#define _B_0			74
#define _B_x			64
#define _B_t			84
#define _B_UP			51
#define _B_DOWN			52
#define _B_MEM			31	
#define _B_DEL			54
#define _B_SET			43	//B_FLASH
#define _B_OUT			53
#define _B_PAUSE		42	//B_READIAL
#define _B_BACK			44	
#define _B_VOLUME		23
#define _B_HIS			11	
#define _B_HOLD			24		
#define _B_FLASH		43
#define _B_REDIAL		42
#define _B_M1			32
#define _B_M2			33
#define _B_M3			34
#define _B_M4			15
#define _B_M5			25
#define _B_M6			35
#define _B_M7			45
#define _B_M8			55
#define _B_M9			65
#define _B_M10			75
#define _B_M11			85
#define _B_MUTE			01
#define _B_HF			41	

extern unsigned char Kb_keyPressed;
extern unsigned char Kb_mode;

#define	MAX_CHARS_OF_STRING		19
#define KEYBOARD_NORMAL_MODE	0
#define KEYBOARD_TEXT_MODE		1
#define KEYBOARD_DIAL_MODE		2


extern char edtBuffer[MAX_CHARS_OF_STRING+1];
extern uint8_t edtCount, comKeyPressedTime;
extern uint8_t comKeyFlag;
extern uint8_t ShiftKeyFlag;

void IO_KEYBOARD_POWER_DOW (void);
void IO_KEYBOARD_POWER_UP (void);
void Timer_KeyBoard_Scanner_Config (void);


/*********************************************************************************
*Function name: Keyboard_Config()
*Description:
*Input:
*Return value:
*Date created:	11-10-18
**********************************************************************************/
void Keyboard_Config(void);
void Keyboard_Config_IDLE(void);
/*********************************************************************************
*Function name: check_keyboard()
*Description:
*Input:
*Return value:	1 - if any key is pressed
				0 -  No pressed key
*Date created:	11-10-18
**********************************************************************************/
uint8_t check_keyboard(void);

/*********************************************************************************
*Function name: scan_column(u8 col)
*Description:
*Input:
*Return value:	
*Date created:	11-10-18
**********************************************************************************/
void scan_column(uint8_t col);

/*********************************************************************************
*Function name: read_keyboard()
*Description:
*Input:
*Return value:	Save pressed key to "Kb_keyPressed" global Variable
*Date created:	11-10-18
**********************************************************************************/
void read_keyboard();

/*********************************************************************************
*Function name: is_DialingChar(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not Dialing Number
				1 - Pressed button is a Dialing Number
*Return value:	
*Date created:	29-10-18
**********************************************************************************/
uint8_t is_DialingChar(uint8_t pressedButton);

/*********************************************************************************
*Function name: is_Digit(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not Digit
				1 - Pressed button is a Digit
*Return value:	
*Date created:	19-11-18
**********************************************************************************/
uint8_t is_Digit(uint8_t pressedButton);

/*********************************************************************************
*Function name: is_SPDkey(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not a Speed Dial Key
				1 - Pressed button is a Speed Dial Key
*Return value:	
*Date created:	27-12-18	
**********************************************************************************/
uint8_t is_SPDkey(uint8_t pressedButton);

/*********************************************************************************
*Function name: parseU8(char* str)
*Description:
*Input:
*Return value:	convert a number in form of text to an unsiged int value
*Date created:	19-11-18
**********************************************************************************/
uint8_t parseU8(char* str);

/*********************************************************************************
*Function name: free_edtBuffer()
*Description:
*Input:
*Return value:
*Date created:	12-12-18			Last modified:	12-12-18
**********************************************************************************/
void free_edtBuffer();

/*********************************************************************************
*Function name: read_text()
*Description:	Read a String of 'MAX_CHARS_OF_STRING' chars. Remember to call 
				free_edtBuffer() when reading is completed
*Input:
*Return value:
*Date created:	12-12-18			Last modified:	12-12-18
**********************************************************************************/
void read_text();

/*********************************************************************************
*Function name: read_digitString()
*Description:	Read a String of 'MAX_CHARS_OF_STRING' digit chars. Remember to call
				free_edtBuffer() when reading is completed
*Input:
*Return value:
*Date created:	12-12-18			Last modified:	12-12-18
**********************************************************************************/
void read_digitString();

#endif //_KEYBOARD_H_

