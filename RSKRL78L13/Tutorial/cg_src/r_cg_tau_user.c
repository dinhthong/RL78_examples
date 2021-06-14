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
* File Name    : r_cg_tau_user.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for TAU module.
* Creation Date: 4/18/2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTTM00 r_tau0_channel0_interrupt
#pragma interrupt INTTM01 r_tau0_channel1_interrupt
#pragma interrupt INTTM02 r_tau0_channel2_interrupt
#pragma interrupt INTTM03 r_tau0_channel3_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_adc.h"
#include "lcd_panel.h"
#include "rskrl78l13def.h"
#include "r_cg_port.h"
#include "switch.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* interrupt flag for delay function */
static volatile uint8_t one_ms_delay_complete = FALSE;

/* Declare a variable for storing the ADC value */
volatile uint16_t g_timer_adc_period = 0u;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_tau0_channel0_interrupt
* Description  : This function INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    
    /* Stop this timer - we start it again in the debounce routines */
    R_TAU0_Channel0_Stop();
    
    /* Call the debounce callback routine */
    SwitchDebounceIsrCallback();    
    
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tau0_channel1_interrupt
* Description  : This function INTTM01 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    
    /* Stop this timer - we start it again in the debounce routines */
    R_TAU0_Channel1_Stop();
    
    /* Call the debounce callback routine */
    SwitchDebounceIsrCallback(); 
    
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tau0_channel2_interrupt
* Description  : This function INTTM02 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */

    /* Toggle the heart symbol */
    Toggle_Symbol();

    /* Toggle the LEDs */
    Toggle_LED();

    /* Ensure that the timer period is never set below the minimum period */
    if (g_timer_adc_period < MIN_TIMER_PERIOD)
    {
        /* Set the period to the minimum defined period */
        g_timer_adc_period = MIN_TIMER_PERIOD;
    }

    /* Update timer period with respect to a scaled adc value */
    TDR02 = g_timer_adc_period * TIMER_PERIOD_SCALER;

    /* Clear the interrupt flag */
    TMIF02 = 0;

    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tau0_channel3_interrupt
* Description  : This function INTTM03 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
	one_ms_delay_complete = TRUE;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name : Timer_ADC
* Description   : Uses the ADC to change the timer period, used to flash the heart symbol.
* Argument      : None
* Return value  : None
***********************************************************************************************************************/
void Timer_ADC (void)
{
    /* Start ADC operations */
    R_ADC_Start();

    /* Start timer TM02 operations */
    R_TAU0_Channel2_Start();
}
/***********************************************************************************************************************
End of function Timer_ADC
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name : Toggle_Symbol
* Description   : This function toggles the heart symbol.
* Arguments     : None
* Return Value  : None
***********************************************************************************************************************/
void Toggle_Symbol (void)
{
    /* Used to keep track of toggling all LCD segments on/off */
    static uint8_t heart_symbol_toggle = FALSE;

    /* Check if the variable is 0 */
    if (FALSE == heart_symbol_toggle)
    {
        /* Turn off all segments */
        Symbol_Map(LCD_HEART_ON);

        /* Set the variable to TRUE */
        heart_symbol_toggle = TRUE;
    }
    else
    {
        /* Turn on the heart segments */
        Symbol_Map(LCD_HEART_OFF);

        /* Set the variable to FALSE */
        heart_symbol_toggle = FALSE;
    }
}
/***********************************************************************************************************************
* End of function Toggle_Symbol
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_TAU_MsDelay
* Description  : Uses TAU0 channel 3 to wait for a specified number of milliseconds
* Arguments    : uint16_t millisecs, number of milliseconds to wait
* Return Value : None
***********************************************************************************************************************/
void R_TAU_MsDelay (const uint16_t millisec)
{
    uint16_t ms_count = 0;

    do
    {
        R_TAU0_Channel3_Start();
        while (FALSE == one_ms_delay_complete)
        {
            /*Wait*/
        }
        R_TAU0_Channel3_Stop();
        one_ms_delay_complete = FALSE;
        ms_count++;
    } while (ms_count < millisec);


}
/***********************************************************************************************************************
End of function R_TAU_MsDelay
***********************************************************************************************************************/
/* End user code. Do not edit comment generated here */
