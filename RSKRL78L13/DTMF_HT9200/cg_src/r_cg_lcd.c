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
* File Name    : r_cg_lcd.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for LCD module.
* Creation Date: 4/18/2021
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
#include "r_cg_lcd.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_tau.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* Some of the code in this file is generated using "Application Leading Tool (Applilet)" */
/* Warnings exist in this module. */

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LCD_Create
* Description  : This function initializes the LCD module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Create(void)
{
    LCDON = 0U;    /* disable LCD clock operation */
    LCDMK0 = 1U;    /* disable INTLCD0 interrupt */
    LCDIF0 = 0U;    /* clear INTLCD0 interrupt flag */
    LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
    LCDM0 |= _80_LCD_VOLTAGE_MODE_CAPACITOR;
    /* Set CAPL and CAPH pins */
    ISCLCD &= (uint8_t)~_01_LCD_CAPLH_BUFFER_VALID;
    PU12 &= 0x3FU;
    P12 &= 0x3FU;
    PM12 |= 0xC0U;
    /* Set segment pins */
    PU1 &= 0xE0U;
    PU2 &= 0x03U;
    PU3 &= 0xC0U;
    PU4 &= 0x3FU;
    PU5 &= 0x00U;
    PU7 &= 0x00U;
    PU13 &= 0xFEU;
    POM3 &= 0xDFU;
    POM4 &= 0x3FU;
    POM5 &= 0x87U;
    POM13 &= 0xFEU;
    PIM3 &= 0xEFU;
    PIM4 &= 0x3FU;
    PIM5 &= 0xD7U;
    PFSEG0 |= 0xF0U;
    PFSEG1 |= 0xFFU;
    PFSEG2 |= 0xFFU;
    PFSEG3 |= 0xFBU;
    PFSEG4 |= 0xFFU;
    PFSEG5 |= 0x01U;
    PMC1 &= 0xF0U;
    P1 &= 0xE0U;
    PM1 &= 0xE0U;
    PMC2 &= 0x03U;
    P2 &= 0x03U;
    PM2 &= 0x03U;
    P3 &= 0xC0U;
    PM3 &= 0xC0U;
    P4 &= 0x3FU;
    PM4 &= 0x3FU;
    P5 &= 0x00U;
    PM5 &= 0x00U;
    P7 &= 0x00U;
    PM7 &= 0x00U;
    P13 &= 0xFEU;
    PM13 &= 0xFEU;
    LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
    LCDC0 = _1A_LCD_CLOCK_FMAIN_17;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Start
* Description  : This function enables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Start(void)
{
    LCDON = 1U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Stop
* Description  : This function disables the LCD display.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Stop(void)
{
    LCDON = 0U;
}
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_Off
* Description  : This function disables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_Off(void)
{
    SCOC = 0U;
    VLCON = 0U;
    LCDM0 &= (uint8_t)~_C0_LCD_VOLTAGE_MODE_INITIALVALUE;
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_LCD_Voltage_On
* Description  : This function enables voltage boost circuit or capacitor split circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LCD_Voltage_On (void)
{
    VLCON = 1U;

    /* 100ms capacitor split wait time */
    R_TAU_MsDelay(100);

    SCOC = 1U;
}
/***********************************************************************************************************************
* End of function R_LCD_Voltage_On
***********************************************************************************************************************/
/* End user code. Do not edit comment generated here */
