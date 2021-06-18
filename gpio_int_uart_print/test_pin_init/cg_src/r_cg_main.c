/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_main.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMG
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 6/10/2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"
#include "r_cg_adc.h"
#include "r_cg_sau.h"
#include "r_cg_iica.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
#include "keyboard.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
uint8_t tsd_debug;
/* End user code. Do not edit comment generated here */

void R_MAIN_UserInit(void);
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    
    tsd_debug = 0;
    {
	    //
	    /* tsd note */
	    //
	    // chuong trinh nay da config tat ca cac chan/chuc nang phu hop voi version moi cua dtap
	    // chuong trinh nay chi moi porting ham va bien cua 2 file "keyboard.c" va "keyboard.h"
	    // cac file khac chua duoc porting, duoc them vao de ho tro pass debug cho 2 file keyboard
	    // chuong trinh da duoc verify bang cach hien thi so len uart khi goi ham read_keyboard()
	    // Su dung uart2: baud 9600: Bam so nao se hien thi len uart so do
	    // 
	    /* end tsd note */
	    
	    uint8_t pre_kb_keyPressed;
            char smpl_banner[] = "Renesas RL78/L13 Async Serial \n\r";
	    
    	    /* test UART */
	    R_UART2_Start();
            R_UART2_Transmit((uint8_t *)smpl_banner, (uint16_t)strlen(smpl_banner));
	    
	    /* end test UART*/
	    R_INTC5_Start();
	    R_INTC0_Start();
	    R_INTC7_Start();
	    
    while (1U)
    {
	   
	    /* test keyboard 
	    Keyboard_Config();
	    
	    _XDP = 1;
	    _BATT_ST = 1;
	    LVD_Flag = 0;	    
	    Kb_keyPressed = 0;
	    Kb_mode = KEYBOARD_NORMAL_MODE;
	    
	    read_keyboard();
	    
	    
	    delay_ms(50);
	    if(Kb_keyPressed != pre_kb_keyPressed)
	    {
		   switch (Kb_keyPressed)
			{
			case 11:	R_UART2_Send("LichSu",6);	break;
			case 15:	R_UART2_Send("M4",2);	break;
			case 23:	R_UART2_Send("AmLuong",7);	break;
			case 24:	R_UART2_Send("Giu",3);	break;
			case 25:	R_UART2_Send("M5",2);	break;
			case 31:	R_UART2_Send("Nho",3);	break;
			case 32:	R_UART2_Send("M1",2);	break;
			case 33:	R_UART2_Send("M2",2);	break;
			case 34:	R_UART2_Send("M3",2);	break;
			case 35:	R_UART2_Send("M6",2);	break;
			case 41:	R_UART2_Send("Loa",3);	break;
			case 42:	R_UART2_Send("Dung",4);	break;
			case 43:	R_UART2_Send("Chuyen",6);	break;
			case 44:	R_UART2_Send("QuayLai",7);	break;
			case 45:	R_UART2_Send("M7",2);	break;
			case 51:	R_UART2_Send("Len",3);	break;
			case 52:	R_UART2_Send("Xuong",5);	break;
			case 53:	R_UART2_Send("Thoat",5);	break;
			case 54:	R_UART2_Send("Xoa",3);	break;
			case 55:	R_UART2_Send("M8",2);	break;
			case 61:	R_UART2_Send("1",1);	break;
			case 62:	R_UART2_Send("4",1);	break;
			case 63:	R_UART2_Send("7",1);	break;
			case 64:	R_UART2_Send("*",1);	break;
			case 65:	R_UART2_Send("M9",2);	break;
			case 71:	R_UART2_Send("2",1);	break;
			case 72:	R_UART2_Send("5",1);	break;
			case 73:	R_UART2_Send("8",1);	break;
			case 74:	R_UART2_Send("0",1);	break;
			case 75:	R_UART2_Send("M10",3);	break;
			case 81:	R_UART2_Send("3",1);	break;
			case 82:	R_UART2_Send("6",1);	break;
			case 83:	R_UART2_Send("9",1);	break;
			case 84:	R_UART2_Send("#",1);	break;
			case 85:	R_UART2_Send("M11",3);	break;
			//default:		R_UART2_Send("default",7);	break;
			} 
		pre_kb_keyPressed = Kb_keyPressed;
	    }
	     end test keyboard */
        ;
    }
    }
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
