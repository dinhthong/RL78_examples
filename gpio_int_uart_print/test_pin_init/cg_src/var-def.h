#ifndef _VAR_DEF_H_
#define _VAR_DEF_H_
//
//typedef     unsigned char   uchar, U8, u8;
//typedef     unsigned int    uint, U16, u16;
//typedef     unsigned long   ulong, U32, u32;
//typedef     signed   char   S8, s8;
//typedef     signed   int    S16, s16;
//typedef     signed   long   S32, s32;

//typedef struct tm{
//	uint8_t second;
//	uint8_t minute;
//	uint8_t hour;
//	uint8_t day;
//	uint8_t month;
//	uint8_t year;
//}time;

#define _XDP_ON  	_XDP=1
#define _XDP_OFF  	_XDP=0

#define _MUTE_ON	_MUTE=0
#define _UN_MUTE	_MUTE=1

#define HKS_INTERRUPT_ENABLE  _int0e = 1;_int0f = 0;
#define HKS_INTERRUPT_DISABLE _int0e = 0;_int0f = 0;
#define EMI_Interrupt_ENABLE  _emi = 1;
#define EMI_Interrupt_DISABLE _emi = 0;

#define SPI_INTERRUPT_ENABLE  _int1e = 1; _papu7 	= 0; // SPI no pullup
#define SPI_INTERRUPT_DISABLE _int1e = 0; _papu7 	= 1; // SPI pullup

#define RD_INTERRUPT_ENABLE  _int2e = 1;_int2f = 0; 
#define RD_INTERRUPT_DISABLE _int2e = 0;_int2f = 0; 



#define SW_PW_ON  _pt0on = 1
#define SW_PW_OFF _pt0on = 0

/* define interrupt Flags */
#define HOOK_SW_ON		1
#define HOOK_SW_OFF		0
#define HOOK_SW_NORMAL  2

//extern unsigned int couter_1;
//extern unsigned long couter_2;
//extern unsigned int ring_couter;
//extern char HKS_Change_Flag;
//extern char Ringing_Flag;
//extern U8 TIMER1S_Soft_Flag, sysTime_update_Flag; 

/*	Define Phone States*/
#define STATE_NORMAL						0
#define	STATE_SPEED_DIALING					20				
#define STATE_HANDON_DIALING				21
#define STATE_FREEHAND_DIALING				22
#define STATE_RINGING						30
#define STATE_ANALYZING_PHONENUMB			31
#define STATE_MISSED_CALL					32
#define STATE_HANDON_CONVERSATION			40
#define STATE_HANDON_CONVERSATION_HOLD		41
#define STATE_FREEHAND_CONVERSATION			50
#define STATE_FREEHAND_CONVERSATION_HOLD	51	
#define STATE_DISPLAY_CALLLOGS				7
#define STATE_DISPLAY_MENU					1
#define STATE_DATE_TIME_SETTING				11
#define	STATE_SCREEN_SETTING				12
#define	STATE_SCREEN_SETTING_BRIGHTNESS		121
#define	STATE_SCREEN_SETTING_CONTRAST		122
#define STATE_VOLUME_SETTING				13
#define STATE_RING_VOLUME_SETTING			131
#define STATE_SPEECH_VOLUME_SETTING			132
#define STATE_PHONEBOOK_SETTING				14
#define STATE_DISPLAY_PHONEBOOK				141
#define STATE_PHONEBOOK_ADD_ENTRY			142
#define STATE_PHONEBOOK_DELETE_ENTRY		143
#define STATE_PHONEBOOK_DELETE_ALL			144	
#define STATE_PHONEBOOK_MODIFY_ENTRY		145
#define STATE_PHONEBOOK_DISPLAY_DETAIL		146
#define STATE_DISPLAY_SPDKEYS_1				147
#define STATE_SPDKEY_1_MODIFY_ENTRY			148
#define STATE_SPDKEY_1_DELETE_ENTRY			149
#define STATE_DISPLAY_SPDKEYS_2				15
#define STATE_SPDKEY_2_MODIFY_ENTRY			151
#define STATE_SPDKEY_2_DELETE_ENTRY			152
#define STATE_RINGTONE_SETTING				16
#define STATE_FLASH_TIME_SETTING			161
#define STATE_DIAL_MODE_SETTING				162

/*	Define EEPROM Organization*/
#define	EEPROM_RING_VOLUME_LEVEL_ADDRESS			0 //callLogs_ENDING_ADDRESS + 1
#define	EEPROM_SPEECH_VOLUME_LEVEL_ADDRESS			EEPROM_RING_VOLUME_LEVEL_ADDRESS + 1
#define	EEPROM_RINGTONE_TYPE_ADDRESS				EEPROM_SPEECH_VOLUME_LEVEL_ADDRESS + 1
#define	EEPROM_SCREEN_BACKLIGHT_LEVEL_ADDRESS		EEPROM_RINGTONE_TYPE_ADDRESS + 1
#define	EEPROM_SCREEN_CONTRAST_LEVEL_ADDRESS		EEPROM_SCREEN_BACKLIGHT_LEVEL_ADDRESS + 1
#define	EEPROM_FLASH_TIME_ADDRESS					EEPROM_SCREEN_CONTRAST_LEVEL_ADDRESS + 1	
#define EEPROM_DIAL_MODE_ADDRESS					EEPROM_FLASH_TIME_ADDRESS + 1

/*	Define ID of call types*/
#define CALL_OUT					0
#define	CALL_INCOMING_FSK			1
#define	CALL_INCOMING_DTMF			2
#define	CALL_INCOMING_UNKNOWN		3

/* 	PhoneBook Linking Status - Variable: phoneBookLinking_Status*/ 
#define PHONEBOOK_LINKING_NOT_FOUND		0 
#define PHONEBOOK_LINKING_FOUND			1 
#define PHONEBOOK_LINKING_SEARCHING		2

/*	Define updating System parameters Operation Code*/
#define UPDATE_RING_VOLUME_LEVEL					0
#define UPDATE_SPEECH_VOLUME_LEVEL					1
#define UPDATE_RINGTONE_TYPE						2
#define UPDATE_SCREEN_BACKLIGHT_LEVEL				3
#define UPDATE_SCREEN_CONTRAST_LEVEL				4
#define UPDATE_FLASH_TIME							5
#define UPDATE_DIAL_MODE							6	

/*	Define Operation constant Parameters*/
//#define TIME_TO_IDLE_0_MODE					5	// unit: second (s)
#define TIME_TO_IDLE_1_MODE					12	// unit: second (s)
#define DIAL_WAITING_TIME					6	// unit: second (s)
#define PAUSING_TIME						140	// unit: 25 ms. Note: value < DIAL_WAITING_TIME
#define SPEED_DIALING_INTERVAL				12	// unit: 25 ms
#define PHONE_RINGING_INTERVAL				10	// unit: second (s). Ex: expected time + 1 (s)
#define SPEED_DIALING_INIT_TIME				200	// unit: 10 ms. Note: value > 120; if value>256, change counting variable data type to u16
#define RING_PEAK_CHECKING_QUANTITY			3
#define MAX_ANALYZING_SIGNAL_TIME			160	// unit: 25 ms.
#define ENABLING_SPI_INTERRUPT_TIME			420	// unit: 2.5 ms (PTM1)
#define GOING_INTO_SCREENSAVER_TIME			60	// unit: second (s)
#define ENALBE_ADD_POWER_SUPPLIER_TIME		1800// unit: second (s)

/*	Define Error Code*/
#define ERROR_I2C_WAITING_ACK_TIME_OUT		10	// unit: second (s)

#endif //_VAR_DEF_H_

