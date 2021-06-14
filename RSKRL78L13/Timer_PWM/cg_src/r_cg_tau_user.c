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
* Creation Date: 12/09/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTTM00 r_tau0_channel0_interrupt
#pragma interrupt INTTM01 r_tau0_channel1_interrupt
#pragma interrupt INTTM02 r_tau0_channel2_interrupt
#pragma interrupt INTTM04 r_tau0_channel4_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
/* Start user code for include. Do not edit comment generated here */

/* Defines switch callback functions required by interrupt handlers */
#include "switch.h"

/* Platform related defines */
#include "rskrl78l13def.h"

/* LCD panel defines */
#include "lcd_panel.h"

/* Utility defines */
#include "utility.h"

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* interrupt flag for delay function */
static volatile uint8_t one_ms_delay_complete = FALSE;

/* Flag indicates whether we are varying the duty cycle or not */
static volatile uint8_t vary_duty_cycle = 0x1u;

/* Declare a variable for storing the count value */
static volatile uint16_t duty_update = LOWER_DUTY_CYCLE;

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
    one_ms_delay_complete = TRUE;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_tau0_channel4_interrupt
* Description  : This function INTTM04 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel4_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* Increment the duty cycle updater if required */
    if (1 == vary_duty_cycle)
    {
        /* Increment duty cycle updater */
        duty_update += DUTY_CYCLE_STEPS;
    }

    /* If the duty cycle exceeds UPPER_DUTY_CYCLE percentage,
       wrap around back to LOWER_DUTY_CYCLE percentage */
    if (duty_update > UPPER_DUTY_CYCLE)
    {
        duty_update = LOWER_DUTY_CYCLE;
    }

    /* Load the new duty */
    TDR05 = duty_update;

    /* Clear the interrupt flag */
    TMIF04 = 0;

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_TAU_MsDelay
* Description  : Uses TAU0 channel 2 to wait for a specified number of milliseconds
* Arguments    : uint16_t millisecs, number of milliseconds to wait
* Return Value : None
***********************************************************************************************************************/
void R_TAU_MsDelay (const uint16_t millisec)
{
    uint16_t ms_count = 0;

    do
    {
        R_TAU0_Channel2_Start();
        while (FALSE == one_ms_delay_complete)
        {
            /*Wait*/
        }
        R_TAU0_Channel2_Stop();
        one_ms_delay_complete = FALSE;
        ms_count++;
    } while (ms_count < millisec);


}
/***********************************************************************************************************************
End of function R_TAU_MsDelay
***********************************************************************************************************************/

/*******************************************************************************
* Function Name: PwmSwitchPressCallback
* Description  : Called from Switch ISRs when any switch press is detected.
*                Toggles the state of the vary_duty_cycle flag and displays
*                current duty cycle on the LCD if vary_duty_cycle is false,
*                otherwise reverts LCD display to "".
*                triggered, otherwise 0.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void PwmSwitchPressCallback (void)
{
    /* Depending on the new state of the flag, update the LCD display */
    if (0 == vary_duty_cycle)
    {
        Display_Panel_String(PANEL_LCD_LINE1, " J1-7");
        vary_duty_cycle = 1;
    }
    else
    {
        /* Local LCD buffer string */
        char        lcd_buffer[] = "   dc";
        uint32_t    calc_duty_percent = 0;

        /* Calculate the percentage */
        calc_duty_percent =
            (uint32_t)(((uint32_t)duty_update * 100u) / CYCLE_PERIOD);

        /* Convert the calculated percentage into a BCD character string */
        uint16_to_bcd_string(lcd_buffer, 1u, (uint16_t)calc_duty_percent);

        /* Display contents of lcd_buffer onto the LCD panel */
        Display_Panel_String(PANEL_LCD_LINE1, lcd_buffer);

        vary_duty_cycle = 0;
}

    /* Clear the switch press flags */
    g_switch_flag &= (uint8_t) ~SWITCHHOLD_ALL;


}
/*******************************************************************************
* End of function PwmSwitchPressCallback
*******************************************************************************/
/* End user code. Do not edit comment generated here */
