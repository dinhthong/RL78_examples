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
* End of function SetSwitchReleaseCallback
******************************************************************************/

    
/******************************************************************************
* Function Name : Switch1IsrCallback
* Description   : Switch 1 callback ISR function. The function disables switch
*                 interrupts, then uses the debounce timer to re-enable them
*                 after the debounce period finishes.
* Argument      : none
* Return value  : none
******************************************************************************/
void Switch1IsrCallback (void)
{       
    /* Disable switch 1 interrupts */
    R_INTC0_Stop();    
                       
    /* Check if interrupt was generated by falling edge */
    if (1 == R_INTC0_IsFallingEdge())
    {
        /* Start short debounce timer */
        R_TAU0_Channel0_Start();
        
        /* Set detection direction as rising edge */
        R_INTC0_SetFallingEdge(0);
        R_INTC0_SetRisingEdge(1);        
                
        /* Set global switch flag to indicate SW1 is held down */
        g_switch_flag |= SWITCHHOLD_1;
    }
    else
    {   
        /* Start long debounce timer */
        R_TAU0_Channel1_Start();
            
        /* Set detection direction to falling edge */
        R_INTC0_SetFallingEdge(1);
        R_INTC0_SetRisingEdge(0);        
        
        /* Clear SW1 held-down flag bit in switch flag */
        /* type cast required to remove warning for 
            Conversion may lose significant digits */ 
        g_switch_flag &= (uint8_t) ~SWITCHHOLD_1;
        
        /* Set global switch flag to indicate SW1 press complete */
        g_switch_flag |= SWITCHPRESS_1;
    
        /* Check if switch release callback function is not NULL */
        if (g_switch_release_callback_func)
        {
            /* Execute user callback function */
            g_switch_release_callback_func();
        }
    }
}
/******************************************************************************
* End of function Switch1IsrCallback
******************************************************************************/ 

/******************************************************************************
* Function Name : Switch3IsrCallback
* Description   : Switch 3 callback ISR function. The function disables switch
*                 interrupts, then uses the debounce timer to re-enable them
*                 after the debounce period finishes.
* Argument      : none
* Return value  : none
******************************************************************************/
void Switch3IsrCallback (void)
{       
    /* Disable switch 2 interrupts */
    R_INTC7_Stop();
                       
    /* Check if interrupt was generated by falling edge */
    if (1 == R_INTC7_IsFallingEdge())
    {
        /* Start short debounce timer */
        R_TAU0_Channel0_Start();
        
        /* Set detection direction as rising edge */
        R_INTC7_SetFallingEdge(0);
        R_INTC7_SetRisingEdge(1);
                
        /* Set global switch flag to indicate SW3 is held down */
        g_switch_flag |= SWITCHHOLD_3;
    }
    else
    {   
        /* Start long debounce timer */
        R_TAU0_Channel1_Start();
            
        /* Set detection direction to falling edge */
        R_INTC7_SetFallingEdge(1);
        R_INTC7_SetRisingEdge(0);
        
        /* Clear SW2 held-down flag bit in switch flag */
        /* type cast required to remove warning for 
            Conversion may lose significant digits */ 
        g_switch_flag &= (uint8_t) ~SWITCHHOLD_3;
        
        /* Set global switch flag to indicate SW3 press complete */
        g_switch_flag |= SWITCHPRESS_3;
    
        /* Check if switch release callback function is not NULL */
        if (g_switch_release_callback_func)
        {
            /* Execute user callback function */
            g_switch_release_callback_func();
        }
    }
}
/******************************************************************************
* End of function Switch3IsrCallback
******************************************************************************/ 



/******************************************************************************
* Function Name : SwitchDebounceIsrCallback
* Description   : Switch debounce timer callback function. Function is executed
*                 by the timer ISR used for debounce. Function re-enables all 
*                 switch interrupts; then verifies a correct switch press was
*                 detected, and calls the user switch press callback function.
* Argument      : none
* Return value  : none
******************************************************************************/
void SwitchDebounceIsrCallback (void)
{   
   /* Re-enable switch 1 interrupts */
    R_INTC0_Start();

    /* Re-enable switch 3 interrupts */
    R_INTC7_Start();

    /* Check if switch 1 hold flag is set */ 
    if ((g_switch_flag & 0x0F) & (SWITCHHOLD_1 | SWITCHHOLD_2 | SWITCHHOLD_3))
    {
       /* Check if switch press callback function is not NULL */
        if (g_switch_press_callback_func)
        {
            /* Execute user callback function */
            g_switch_press_callback_func();
        }
    }
  

}
/******************************************************************************
* End of function SwitchDebounceIsrCallback
******************************************************************************/

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


/******************************************************************************
* Function Name : Switch2_Poll
* Description   : Polls SW2 for the specified event returns TRUE if occurred.
* Argument      : uint8_t switch_flag: Flag indicating which types of SW2 event
*                                      to check, SWITCHPRESS_2 or SWITCHHOLD_2
* Return value  : TRUE if event occurred, FALSE if not.
******************************************************************************/
uint8_t Switch2_Poll (const uint8_t switch_flag)
{
    uint8_t event_occurred = FALSE;

    /* Check to see if SW is down */
    if (0 == SW2)
    {
        /* if we want a SWITCHPRESS_2 event we wait for release */
        if (SWITCHPRESS_2 == switch_flag)
        {
            while (0 == SW2)
            {
               /* Wait */
            }
            g_switch_flag = switch_flag;
            event_occurred = TRUE;
        }
        else if (SWITCHHOLD_2 == switch_flag)
        {
            g_switch_flag = switch_flag;
            event_occurred = TRUE;
        }
        else
        {
            /* Do nothing */
        }

        /* Delay for debounce */
        R_TAU_MsDelay(200);
   }
    return event_occurred;

}
/******************************************************************************
* End of function Switch2_Poll
******************************************************************************/


