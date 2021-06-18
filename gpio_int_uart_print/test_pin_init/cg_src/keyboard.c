#include "r_cg_macrodriver.h"
#include "keyboard.h"
#include "r_cg_port.h"


const char Com2[4] = {  'a',  'b',  'c',  '2'	};
const char Com3[4] = {  'd',  'e',  'f',  '3'	}; 
const char Com4[4] = {  'g',  'h',  'i',  '4'	};
const char Com5[4] = {  'j',  'k',  'l',  '5'	};
const char Com6[4] = {  'm',  'n',  'o',  '6'	};
const char Com7[5] = {  'p',  'q',  'r',  's',  '7'	};
const char Com8[4] = {  't',  'u',  'v',  '8'	};
const char Com9[5] = {  'w',  'x',  'y',  'z',  '9'	};
const char Com0[2] = {  ' ',  '0'	};

unsigned char Kb_columnPressed = 1;
unsigned char Kb_keyPressed = 0;
unsigned char Kb_mode = KEYBOARD_NORMAL_MODE;

char edtBuffer[MAX_CHARS_OF_STRING + 1] = "";
uint8_t edtCount = 0, pressedTimeCount = 0, comKeyPressedTime = 0;  
uint8_t ShiftKeyFlag = 0, comKeyFlag = 0;

void Keyboard_Config_IDLE(void) {  
  /* set R0 - R7: output and Set = 1 (P70-P77)-------------------- */
  // P70-P77 => P7: set output = 1; PM7: use as output mode
  P7 = _01_Pn0_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1 | _10_Pn4_OUTPUT_1 | 
         _20_Pn5_OUTPUT_1 | _40_Pn6_OUTPUT_1 | _80_Pn7_OUTPUT_1;
  PM7 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | 
          _00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;

  /* set C0 - C3, C01, MUTE: input pull up (P10-P14 and P13)(--------------------- */
  // P10-P14 => PU1: set pull-up; PMC1: enable digital input; PM1: use pin as input mode
  PU1 |= _01_PUn0_PULLUP_ON | _02_PUn1_PULLUP_ON | _04_PUn2_PULLUP_ON | _08_PUn3_PULLUP_ON | _10_PUn4_PULLUP_ON;
  PMC1 |= _00_PMCn0_DI_ON | _00_PMCn1_DI_ON | _00_PMCn2_DI_ON | _00_PMCn3_DI_ON | _F0_PMC1_DEFAULT;
  PM1 |= _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _04_PMn2_MODE_INPUT | _08_PMn3_MODE_INPUT | 
          _10_PMn4_MODE_INPUT;
  
  // P13: not config  

}

void Keyboard_Config(void) {
  /* set R0 - R7, MUTE: input pull up -------------------- */
    PU7 = _01_PUn0_PULLUP_ON | _02_PUn1_PULLUP_ON | _04_PUn2_PULLUP_ON | _08_PUn3_PULLUP_ON | _10_PUn4_PULLUP_ON | 
          _20_PUn5_PULLUP_ON | _40_PUn6_PULLUP_ON | _80_PUn7_PULLUP_ON;
    PM7 = _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _04_PMn2_MODE_INPUT | _08_PMn3_MODE_INPUT | 
          _10_PMn4_MODE_INPUT | _20_PMn5_MODE_INPUT | _40_PMn6_MODE_INPUT | _80_PMn7_MODE_INPUT;
  /* set C0 – C3, C01: output (C0-C3 = 1, C01 = 0) --------------------- */
    PMC1 |= _00_PMCn0_DI_ON | _00_PMCn1_DI_ON | _00_PMCn2_DI_ON | _00_PMCn3_DI_ON | _F0_PMC1_DEFAULT;
    PM1 |= _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | 
          _00_PMn4_MODE_OUTPUT;
    P1 |= _01_Pn0_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1;
    P1.4 = 0;
  
}

uint8_t check_keyboard(void) { 		// Neeus k bam phim nao thi return 0, co bam phim thi return 1
  CO0 = CO1 = CO2 = CO3 = CO01 = 0; 	
  if (!_RMUTE) return 1;  // neu nhan tat tieng thi return 1
  if (RO0 & RO1 & RO2 & RO3 & RO4 & RO5 & RO6 & RO7) return 0;
  else return 1; // keyboard is being pressed		
}

void scan_column(uint8_t col) {
  CO0 = CO1 = CO2 = CO3 = CO01 = 1;
  delay_us(100); //chong nhieu
  switch (col) {
  case 1:
    CO0 = 0;
    break;
  case 2:
    CO1 = 0;
    break;
  case 3:
    CO2 = 0;
    break;
  case 4:
    CO3 = 0;
    break;
  case 5:
    CO01 = 0;
    break;
  case 6:
  case 7:
  case 8:
    break;
  }
}

void scan_row(uint8_t col) {
  RO0 = RO1 = RO2 = RO3 = RO4 = RO5 = RO6 = RO7 = 1;
  delay_ms(10); //chong nhieu
  switch (col) {
  case 1:
    RO0 = 0;
    break;
  case 2:
    RO1 = 0;
    break;
  case 3:
    RO2 = 0;
    break;
  case 4:
    RO3 = 0;
    break;
  case 5:
    RO4 = 0;
    break;
  case 6:
    RO5 = 0;
    break;
  case 7:
    RO6 = 0;
    break;
  case 8:
    RO7 = 0;
    break;
  }
}


void read_keyboard() {
  uint8_t i;
  if ((_XDP == 1) || ((_BATT_ST == 1) && (LVD_Flag == 0))) { // khong cho quet phim khi khong lap pin hoac pin yeu
  // XDP dieu khien nhac may dap may
  // _BATT_ST : chan doc ADC pin
  
    if (Kb_keyPressed == 0 && check_keyboard()) {   // ban dau khoi dong len chua bam nut va k bam nut gi
      delay_ms(5);
      if (check_keyboard()) {
        if (!_RMUTE) {							// Neu bam mute thi cho gia tri Kb_keyPressed là mute 
          Kb_keyPressed = _B_MUTE;				
          return;
        }

        if (Kb_mode == KEYBOARD_NORMAL_MODE) {		// o che do NORMAL 
          for (i = 1; i < 6; i++) {			
            scan_column(i);								// quet cot thu i 
            delay_us(100); //anti noise
            switch (i) {					// Gan vao bien Kb_keyPressed voi phim duoc bam
            case 1:	
              if (!RO0) Kb_keyPressed = 11;
              else if (!RO1) Kb_keyPressed = 21;
              else if (!RO2) Kb_keyPressed = 31;
              else if (!RO3) Kb_keyPressed = 41;
              else if (!RO4) Kb_keyPressed = 51;
              else if (!RO5) Kb_keyPressed = 61;
              else if (!RO6) Kb_keyPressed = 71;
              else if (!RO7) Kb_keyPressed = 81;
              break;
            case 2:
              if (!RO0) Kb_keyPressed = 12;
              else if (!RO1) Kb_keyPressed = 22;
              else if (!RO2) Kb_keyPressed = 32;
              else if (!RO3) Kb_keyPressed = 42;
              else if (!RO4) Kb_keyPressed = 52;
              else if (!RO5) Kb_keyPressed = 62;
              else if (!RO6) Kb_keyPressed = 72;
              else if (!RO7) Kb_keyPressed = 82;
              break;
            case 3:
              if (!RO0) Kb_keyPressed = 13;
              else if (!RO1) Kb_keyPressed = 23;
              else if (!RO2) Kb_keyPressed = 33;
              else if (!RO3) Kb_keyPressed = 43;
              else if (!RO4) Kb_keyPressed = 53;
              else if (!RO5) Kb_keyPressed = 63;
              else if (!RO6) Kb_keyPressed = 73;
              else if (!RO7) Kb_keyPressed = 83;
              break;
            case 4:
              if (!RO0) Kb_keyPressed = 14;
              else if (!RO1) Kb_keyPressed = 24;
              else if (!RO2) Kb_keyPressed = 34;
              else if (!RO3) Kb_keyPressed = 44;
              else if (!RO4) Kb_keyPressed = 54;
              else if (!RO5) Kb_keyPressed = 64;
              else if (!RO6) Kb_keyPressed = 74;
              else if (!RO7) Kb_keyPressed = 84;
              break;
            case 5:
              if (!RO0) Kb_keyPressed = 15;
              else if (!RO1) Kb_keyPressed = 25;
              else if (!RO2) Kb_keyPressed = 35;
              else if (!RO3) Kb_keyPressed = 45;
              else if (!RO4) Kb_keyPressed = 55;
              else if (!RO5) Kb_keyPressed = 65;
              else if (!RO6) Kb_keyPressed = 75;
              else if (!RO7) Kb_keyPressed = 85;
              break;
            }
          }
          comKeyFlag = 0;
          //LCD_gotoxy(DEPTH_SEGMENTS+6, 4);
          //LCD_putNumber(Kb_keyPressed);
        } else { //Kb_mode==KEYBOARD_TEXT_MODE			// che do text mode 
          for (i = 1; i < 9; i++) {
            scan_column(i);
            delay_us(100); //anti noise
            switch (i) {
            case 1:
              if (!RO0) Kb_keyPressed = 11;
              else if (!RO1) Kb_keyPressed = 21;
              else if (!RO2) Kb_keyPressed = 31;
              else if (!RO3) Kb_keyPressed = 41;
              else if (!RO4) Kb_keyPressed = 51;
              else if (!RO5) Kb_keyPressed = 61;
              else if (!RO6) Kb_keyPressed = 71;
              else if (!RO7) Kb_keyPressed = 81;
              break;
            case 2:
              if (!RO0) Kb_keyPressed = 12;
              else if (!RO1) Kb_keyPressed = 22;
              else if (!RO2) Kb_keyPressed = 32;
              else if (!RO3) Kb_keyPressed = 42;
              else if (!RO4) Kb_keyPressed = 52;
              else if (!RO5) Kb_keyPressed = 62;
              else if (!RO6) Kb_keyPressed = 72;
              else if (!RO7) Kb_keyPressed = 82;
              break;
            case 3:
              if (!RO0) Kb_keyPressed = 13;
              else if (!RO1) Kb_keyPressed = 23;
              else if (!RO2) Kb_keyPressed = 33;
              else if (!RO3) Kb_keyPressed = 43;
              else if (!RO4) Kb_keyPressed = 53;
              else if (!RO5) Kb_keyPressed = 63;
              else if (!RO6) Kb_keyPressed = 73;
              else if (!RO7) Kb_keyPressed = 83;
              break;
            case 4:
              if (!RO0) Kb_keyPressed = 14;
              else if (!RO1) Kb_keyPressed = 24;
              else if (!RO2) Kb_keyPressed = 34;
              else if (!RO3) Kb_keyPressed = 44;
              else if (!RO4) Kb_keyPressed = 54;
              else if (!RO5) Kb_keyPressed = 64;
              else if (!RO6) Kb_keyPressed = 74;
              else if (!RO7) Kb_keyPressed = 84;
              break;
            case 5:
              if (!RO0) Kb_keyPressed = 15;
              else if (!RO1) Kb_keyPressed = 25;
              else if (!RO2) Kb_keyPressed = 35;
              else if (!RO3) Kb_keyPressed = 45;
              else if (!RO4) Kb_keyPressed = 55;
              else if (!RO5) Kb_keyPressed = 65;
              else if (!RO6) Kb_keyPressed = 75;
              else if (!RO7) Kb_keyPressed = 85;
              break;
            }
            if (Kb_keyPressed == _B_HOLD) {					// Neu bam phim giu thi chuyen trang thai ShiftKeyFlag 
              if (ShiftKeyFlag) ShiftKeyFlag = 0;				// va hien thi lai thanh status
              else ShiftKeyFlag = 1;
              statusBar();
              break;
            }
          }
        }
        enteringIDLE0mode_counter = enteringIDLEmodeSign_flag = exitSettingScreen_timer = 0;
      }

    }
  }
  CO0 = CO1 = CO2 = CO3 = CO01 = 1; // reset colum.		
}

/*********************************************************************************
*Function name: is_DialingChar(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not Dialing Number
				1 - Pressed button is a Dialing Number
*Return value:	 
*Date created:	29-10-18
**********************************************************************************/
uint8_t is_DialingChar(uint8_t pressedButton) {
  switch (pressedButton) {
  case _B_0:
  case _B_1:
  case _B_2:
  case _B_3:
  case _B_4:
  case _B_5:
  case _B_6:
  case _B_7:
  case _B_8:
  case _B_9:
  case _B_t:
  case _B_x:
    return 1;
  default:
    return 0;
  }
}

/*********************************************************************************
*Function name: is_Digit(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not Digit
				1 - Pressed button is a Digit
*Return value:	
*Date created:	19-11-18
**********************************************************************************/
uint8_t is_Digit(uint8_t pressedButton) {
  switch (pressedButton) {
  case _B_0:
  case _B_1:
  case _B_2:
  case _B_3:
  case _B_4:
  case _B_5:
  case _B_6:
  case _B_7:
  case _B_8:
  case _B_9:
    return 1;
  default:
    return 0;
  }
}

/*********************************************************************************
*Function name: is_SPDkey(u8 pressedButton)
*Description:	
*Input:			0 - Pressed button is not a Speed Dial Key
				1 - Pressed button is a Speed Dial Key
*Return value:	
*Date created:	27-12-18			Last modified:	27-12-18
**********************************************************************************/
uint8_t is_SPDkey(uint8_t pressedButton) {
  switch (pressedButton) {
  case _B_M1:
  case _B_M2:
  case _B_M3:
  case _B_M4:
  case _B_M5:
  case _B_M6:
  case _B_M7:
  case _B_M8:
  case _B_M9:
  case _B_M10:
  case _B_M11:
    return 1;
  default:
    return 0;
  }
}

/*********************************************************************************
 *Function name: parseU8(* str)
 *Description:
 *Input:
 *Return value:	convert a number in form of text to an unsiged int value
 *Date created:	19-11-18
 **********************************************************************************/
uint8_t parseU8(char * str) {
  uint8_t value = 0;
  while ( * str) {
    value = value * 10 + ( * str - 48);
    str++;
  }
  return value;
}

/*********************************************************************************
 *Function name: free_edtBuffer()
 *Description: 
 *Input:  
 *Return value:
 *Date created:	12-12-18			Last modified:	12-12-18
 **********************************************************************************/
void free_edtBuffer() {
  uint8_t i;
  for (i = 0; i <= MAX_CHARS_OF_STRING; i++) edtBuffer[i] = 0;
  edtCount = 0;
}

uint8_t isWordChar(uint8_t c) {
  if (c >= 0x61 && c <= 0x7A) return 1;
  else return 0;
}

/*********************************************************************************
*Function name: read_text()
*Description:	Read a String of 'MAX_CHARS_OF_STRING' chars. Remember to call 
				free_edtBuffer() when reading is completed
*Input:
*Return value:
*Date created:	12-12-18			Last modified:	13-12-18
**********************************************************************************/
void read_text() {
  static uint8_t prevKeyPressed;
  if ((edtCount < MAX_CHARS_OF_STRING || (comKeyFlag && edtCount <= MAX_CHARS_OF_STRING && Kb_keyPressed == prevKeyPressed)) &&
    is_DialingChar(Kb_keyPressed)) // neu chua du 20 ky tu hoac neu dang du 20 ky tu
    {
    	// dien luon neu nhan 1,*,# (tai phim nay k co chu)
    if (Kb_keyPressed == _B_1 || Kb_keyPressed == _B_x || Kb_keyPressed == _B_t) {
      edtBuffer[edtCount] = Print_Button();
      edtCount++;
    } else {
      char c = 0;
      // neu bam lai phim do thi xet xem co bam lien tuc khong, tang so lan bam de xem ky tu can nhap
      if (comKeyFlag && (Kb_keyPressed == prevKeyPressed)) {
        pressedTimeCount++;
        edtCount--;
      } else {
        pressedTimeCount = 0;
        comKeyFlag = 1;
      }
      comKeyPressedTime = 0;
      // Xac dinh ky tu can nhap gan vao bien c
      switch (Kb_keyPressed) {
      case _B_2:
        c = Com2[pressedTimeCount % 4];
        break;
      case _B_3:
        c = Com3[pressedTimeCount % 4];
        break;
      case _B_4:
        c = Com4[pressedTimeCount % 4];
        break;
      case _B_5:
        c = Com5[pressedTimeCount % 4];
        break;
      case _B_6:
        c = Com6[pressedTimeCount % 4];
        break;
      case _B_7:
        c = Com7[pressedTimeCount % 5];
        break;
      case _B_8:
        c = Com8[pressedTimeCount % 4];
        break;
      case _B_9:
        c = Com9[pressedTimeCount % 5];
        break;
      case _B_0:
        c = Com0[pressedTimeCount % 2];
        break;
      }
      // Neu bam shift thi viet hoa
      if (ShiftKeyFlag && isWordChar(c)) { //and isWordChar
        c -= 32;
      }
      edtBuffer[edtCount] = c;
      edtCount++;
      prevKeyPressed = Kb_keyPressed;
    }
  }
  // neu bam del thi xoa mang và set comKeyFlag = 0
  if (Kb_keyPressed == _B_DEL && edtCount > 0) {
    edtCount--;
    edtBuffer[edtCount] = 0;
    comKeyFlag = 0;
  }
}

/*********************************************************************************
*Function name: read_digitString()
*Description:	Read a String of 'MAX_CHARS_OF_STRING' digit chars. Remember to call
				free_edtBuffer() when reading is completed
*Input:
*Return value:
*Date created:	12-12-18			Last modified:	12-12-18
**********************************************************************************/
void read_digitString() {
  if ((edtCount < MAX_CHARS_OF_STRING || comKeyFlag) && is_DialingChar(Kb_keyPressed)) {
    edtBuffer[edtCount] = Print_Button();
    edtCount++;
  }
  if (Kb_keyPressed == _B_DEL && edtCount > 0) {
    edtCount--;
    edtBuffer[edtCount] = 0;
  }
}

//// end line
