#include "r_cg_macrodriver.h"
#include "Sys.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

uint8_t LVD_Flag=0;
uint8_t SET_PW_RING_F=0;
uint8_t enteringIDLE0mode_counter = 0, enteringIDLEmodeSign_flag = 0;  //
uint8_t exitSettingScreen_timer;			//

void delay_us(uint16_t time){
	uint16_t i;
	while(time>0)
	{
		time--;
		for (i==0;i<0x1;i++) {}
	}
}

void delay_ms(uint16_t time){
	uint16_t i;
	while(time>0)
	{
		time--;
		delay_us(1000);
	}
}

