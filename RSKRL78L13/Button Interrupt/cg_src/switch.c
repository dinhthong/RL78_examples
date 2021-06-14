/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*******************************************************************************/
/* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.   */
/*******************************************************************************
* File Name     : switch.c
* Version       : 1.00
* Device(s)     : R5F10WMG
* Tool-Chain    : CA78K0R
* H/W Platform  : RSKRL78L13
* Description   : Defines interrupt service routine functions for the switch
*                 interrupts. De-bounces switch and sets a key press flag. 
*******************************************************************************/
/*******************************************************************************
* History       : 08/10/2013  Ver. 1.00 First Release
*******************************************************************************/

/*******************************************************************************
* User Includes (Project Level Includes)
*******************************************************************************/
/* Switch handler function definitions */
#include "switch.h"

/* INTP function definitions */
#include "r_cg_intp.h"

/* TAU function definitions */
#include "r_cg_tau.h"

/* General definitions */
#include "r_cg_userdefine.h"

/* General definitions */
#include "rskrl78l13def.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Switch flag global variable */
volatile uint8_t g_switch_flag = 0x00;

/* Detected switch faults counter variable */
volatile uint16_t g_switch_faults_detected = 0;

/* Switch press callback pointer declaration */
void (*g_switch_press_callback_func)(void) = 0;

/* Switch release callback pointer declaration */
void (*g_switch_release_callback_func)(void) = 0;

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/


/******************************************************************************
* Function Name : Switch_Init
* Description   : Takes a pointer to a function, and sets it as the callback
*                 function for the switch interrupts. The passed function is
*                 executed every time any switch is pressed down.
* Argument      : pointer to callback function (set to NULL to disable)
* Return value  : none
******************************************************************************/
void Switch_Init (void)
{
    /* Turn on the switch interrupts */
    ControlSwitchInterrupts(1);
}
/******************************************************************************
* End of function Switch_Init
******************************************************************************/

/******************************************************************************
* Function Name : SetSwitchPressCallback
* Description   : Takes a pointer to a function, and sets it as the callback
*                 function for the switch interrupts. The passed function is
*                 executed every time any switch is pressed down.
* Argument      : pointer to callback function (set to NULL to disable)
* Return value  : none
******************************************************************************/
void SetSwitchPressCallback (void( *const callback)(void))
{
    /* Store the callback function pointer into the global variable */
    g_switch_press_callback_func = callback;
}
/******************************************************************************
* End of function SetSwitchPressCallback
******************************************************************************/

/******************************************************************************
* Function Name : SetSwitchReleaseCallback
* Description   : Takes a pointer to a function, and sets it as the callback
*                 function for the switch interrupts. The passed function is
*                 executed every time any switch is released. Note that switch
*                 release functionality is not provided for SW3.
* Argument      : pointer to callback function (set to NULL to disable)
* Return value  : none
******************************************************************************/
void SetSwitchReleaseCallback (void( *const callback)(void))
{
    /* Store the callback function pointer into the global variable */
    g_switch_release_callback_func = callback;
}
    

/******************************************************************************
* Function Name : ControlSwitchInterrupts
* Description   : Enables or disables the switch IRQ interrupts, based on the
*                 input variable, control.
* Argument      : uint8_t - 0x1  : Enables switch interrupts.
*                           0x0  : Disables switch interrupts.
* Return value  : none
******************************************************************************/
void ControlSwitchInterrupts (const uint8_t control)
{    
    /* Check if control input is 0x1 */
    if (control)
    {
        /* Enable SW1 interrupt requests */
        R_INTC0_Start();
    
        /* Enable SW3 interrupt requests */
        R_INTC7_Start();
    }
    else
    {   
        /* Control input is 0x0 */
        /* Disable SW1 interrupts */
        R_INTC0_Stop();
        
        /* Disable SW3 interrupts */
        R_INTC7_Stop();
    } 
}   
/******************************************************************************
* End of function ControlSwitchInterrupts
******************************************************************************/ 


