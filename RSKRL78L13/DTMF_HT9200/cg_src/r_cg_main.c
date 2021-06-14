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
* Creation Date: 5/27/2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define _Stop_DTMF Get_DTMF(0xFF)
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */
#include "lcd_panel.h"
#include "switch.h"
#include "rskrl78l13def.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* Some of the code in this file is generated using "Application Leading Tool (Applilet)" */
/* Warnings exist in this module. */

/* Static variable declaration, used in static variable test */


/* Global variable declaration, used in static variable test */


/* Static functions used in this module */

/* End user code. Do not edit comment generated here */

void R_MAIN_UserInit(void);

void Get_DTMF(uint8_t digit);

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
    
    HT9200_EN = 0;
    XDP = 1;
    /* This function must not exit */

    R_TAU_MsDelay(500);

    Get_DTMF(0x01);        
    R_TAU_MsDelay(300);
    _Stop_DTMF;
    R_TAU_MsDelay(500);

    Get_DTMF(0x01);        
    R_TAU_MsDelay(300);
    _Stop_DTMF;
    R_TAU_MsDelay(500);

    Get_DTMF(0x09);        
	R_TAU_MsDelay(300);
    _Stop_DTMF;
    R_TAU_MsDelay(5000);



    while (1)
    {
        

        

/* 	HT9200_CLK = 1;
	HT9200_DATA = 1;
	R_TAU_MsDelay(1);

    HT9200_CLK = 0;
	HT9200_DATA = 0;
	R_TAU_MsDelay(1); */
  
        /* Do Nothing */
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
void Get_DTMF(uint8_t digit)
{
    uint8_t loop_t;

    for(loop_t = 0; loop_t < 5; loop_t++)
    {
        HT9200_CLK = 1;
        if((digit & (0x01 << loop_t)) == 0)
        HT9200_DATA = 0;
        else
        HT9200_DATA = 1;
        R_TAU_MsDelay(1);
        HT9200_CLK = 0;
        R_TAU_MsDelay(1);
    }

    HT9200_CLK = 1;

}
/***********************************************************************************************************************
* Function Name : static_test
* Description   : Displays an initialised string, then modifies it, a character at a time, displaying it at each stage.
*                 Finally RL78 is displayed. 
* Arguments     : None
* Return value  : None
***********************************************************************************************************************/
