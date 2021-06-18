#ifndef SYS_H
#define SYS_H

#include "GUIlib.h"
#include "DTMF_GEN.h"
#include "IO_Config.h"

extern uint8_t LVD_Flag,SET_PW_RING_F;
extern uint8_t enteringIDLE0mode_counter, enteringIDLEmodeSign_flag;  //
extern uint8_t exitSettingScreen_timer;			//

void delay_us(uint16_t time);
void delay_ms(uint16_t time);


#endif
