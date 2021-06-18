#ifndef _IO_CONFIG_
#define _IO_CONFIG_
//#include "Sys.h"

void EEPROM_IO_Config (void);
void SPEECH_IO_CONFIG (void);
void HKS_IO_EXT_CONFIG (void);
void SPI_IO_EXT_CONFIG (void);
void RD_IO_EXT_CONFIG (void);
void I2C_Config(void);

/* System Wakeup Function IO*/
#define SYS_WAKEUP			_pa1

/* EEPROM */
#define EEPROM_SDA
#define EEPROM_SCL
#define EEPROM_WP			_pe3
/**/
#define _ACRA _pa0

/* SPEECH BOARD IO */
#define	_HKS				_pa6
#define	_RD					_pa4
#define	_SPI				_pa7
#define	_XDP				P0.1
#define	_MUTE				_pf0
#define	_PT					_pf1
#define	_VOL2				_pj6
#define	_VOL1				_pj7
#define	_NEW				_pe0
#define	_DT					_pd4
#define _BATT_ST			P2.1

/* LCD's pins Definition*/
#define LCD_SDI				_pa3
#define	LCD_SCL				_pa5
#define LCD_A0				_pc4
#define LCD_CS				_pc6
#define LCD_RST				_pc5
#define LCD_ON				_pc3
#define LCD_BACKLIGHT		_st0on


/* KEYBOARD's pins Definition*/
#define CO01				P1.4
#define CO0				P1.0
#define CO1				P1.1
#define CO2				P1.2
#define CO3				P1.3
#define RO0				P7.0
#define RO1				P7.1
#define RO2				P7.2
#define RO3				P7.3
#define RO4				P7.4
#define RO5				P7.5
#define RO6				P7.6
#define RO7				P7.7
#define	_RMUTE				P13.7

/*	I2C pin definitions*/
#define		SDA		_pf2
#define		SCL		_pf3
#define		SDAC	_pfc2
#define		SCLC	_pfc3
#define		SDAPU	_pfpu2
#define		SCLPU	_pfpu3
/* Ringer --------------------------------------------------------------------------- */
#define Multifuncion2_IT_Enable  _mf2e = 1
#define Multifuncion2_IT_Disable _mf2e = 0

#define PWM_Ring_IT_Enable  	 _ptm2pe = 1
#define PWM_Ring_IT_Disable  	 _ptm2pe = 0
#define PWM_Ring_ON   			 _pt2on = 1
#define PWM_Ring_OFF  			 _pt2on = 0
#define _Ring_Test_Enable		Ringing_Status = 1; 	PWM_Ring_ON;	_MUTE=0;	Test_Flag=1;  Set_Ring_Tone_Volume_Level()
#define _Ring_Enable			Ringing_Status = 1; 	PWM_Ring_ON;	_MUTE=0;	Test_Flag=0;  Set_Ring_Tone_Volume_Level()
#define _Ring_Disable			Ringing_Status = 0;     PWM_Ring_OFF;	_MUTE=1;    Test_Flag=0

#define _Tone_1_H	_ptm2rpl = 0xe8;_ptm2rph = 0x03 // 500Hz
#define _Tone_1_L   _ptm2rpl = 0xa6;_ptm2rph = 0x04 // 420Hz

#define _Tone_2_H	_ptm2rpl = 0xee;_ptm2rph = 0x02 // 666Hz
#define _Tone_2_L	_ptm2rpl = 0xe8;_ptm2rph = 0x03 // 500Hz

#define _Tone_3_H	_ptm2rpl = 0xee;_ptm2rph = 0x02 // 666Hz
#define _Tone_3_L	_ptm2rpl = 0xa6;_ptm2rph = 0x04 // 420Hz

#define _Tone_4_H	_ptm2rpl = 0xa6;_ptm2rph = 0x04 // 420Hz
#define _Tone_4_L	_ptm2rpl = 0x82;_ptm2rph = 0x06 // 300Hz 

#define _Tone_5_H	_ptm2rpl = 0xe8;_ptm2rph = 0x03 // 500Hz
#define _Tone_5_L	_ptm2rpl = 0x82;_ptm2rph = 0x06 // 300Hz

#define _Tone_6_H	_ptm2rpl = 0x57;_ptm2rph = 0x04 // 450Hz
#define _Tone_6_L	_ptm2rpl = 0x95;_ptm2rph = 0x05 // 350Hz

#define _Tone_7_H	_ptm2rpl = 0xe8;_ptm2rph = 0x03 // 500Hz
#define _Tone_7_L	_ptm2rpl = 0xe2;_ptm2rph = 0x04 // 400Hz

#define _Tone_8_H	_ptm2rpl = 0xee;_ptm2rph = 0x02 // 666Hz
#define _Tone_8_L	_ptm2rpl = 0xe2;_ptm2rph = 0x04 // 400Hz

#define _Tone_9_H	_ptm2rpl = 0x8d;_ptm2rph = 0x03 // 550Hz
#define _Tone_9_L	_ptm2rpl = 0x57;_ptm2rph = 0x04 // 450Hz

#define _Tone_10_H	_ptm2rpl = 0x8d;_ptm2rph = 0x03 // 550Hz
#define _Tone_10_L	_ptm2rpl = 0x57;_ptm2rph = 0x04 // 450Hz

#define _BackLight_LV0	0
#define _BackLight_LV1	65
#define _BackLight_LV2	130
#define _BackLight_LV3	190
#define _BackLight_LV4	255
extern unsigned char Test_Flag, Test_Ring_type, Ringing_Status;
//void Config_PWM_Ring_Tone (void);
//void RingTone_Gen(void);
//void Set_PWM_Tone(void);
//
//void Set_Volume_Speaker (void);
//
//
//void Config_PWM_BackLight (void);
//void Set_LCD_BackLight_Level(U8 BackLight_Level);
//
//void Set_Ring_Tone_Volume_Level(void);


#endif //_IO_CONFIG_
