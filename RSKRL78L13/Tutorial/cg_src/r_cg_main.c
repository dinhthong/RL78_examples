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
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_rtc.h"
#include "r_cg_adc.h"
#include "r_cg_lcd.h"
#include "r_cg_intp.h"
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
#define STRING_SIZE 6
const char g_const_str[STRING_SIZE] = " L13 ";

/* Global variable declaration, used in static variable test */
char g_replace_str[STRING_SIZE] = " RL78";

/* Static functions used in this module */
static void static_test(void);
static void flash_lcd(void);
static void toggle_lcd(void);
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
    
    /* Enable and configure LCD display. */
    Init_Display_Panel();
    
    /* Initialise the switch module */
    Switch_Init();

    /* Display the device family name on LCD.*/
    Display_Panel_String(PANEL_LCD_LINE1, " RL78");
    
    /* Flash all available LCD segments */
    flash_lcd();
    
    /* Start the RTC */
    R_RTC_Start();

    /* Wait at least 2*fRTC clock cycles */
    R_TAU_MsDelay(1);

    /* Set the RTC interrupt to 1 second */
    R_RTC_Set_ConstPeriodInterruptOn(ONESEC);

    /* Begins the ADC-varying flash sequence */
    Timer_ADC();

    /* Demonstration of initialised variables.*/
    static_test();

    /* This function must not exit */
    while (1)
    {
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

/***********************************************************************************************************************
* Function Name : static_test
* Description   : Displays an initialised string, then modifies it, a character at a time, displaying it at each stage.
*                 Finally RL78 is displayed. 
* Arguments     : None
* Return value  : None
***********************************************************************************************************************/
static void static_test (void)
{
    /* Declare loop count variable */
    uint8_t count = 0u;
    
    /* Turn off all LCD segments */
    LCD_DISPLAY_OFF();
    
    /* Delay */
    R_TAU_MsDelay(1000);
    
    /* Begin for loop which writes one letter of gConstStr to the LCD at a time 
       The nested while loops generate the delay between each letter change */
    for (count = 0u; count < STRING_SIZE; count++)
    {  
        /* Copy the bytes from gConstStr to gReplaceStr one byte at a time */
        g_replace_str[count] = g_const_str[count];
        
        /* Display the updated string on the LCD.
           Casting to ensure use of correct data type. */
        Display_Panel_String(PANEL_LCD_LINE1, g_replace_str);
        
        /* Delay */
        R_TAU_MsDelay(1000);
    }    
}
/***********************************************************************************************************************
End of function static_test
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name : toggle_lcd
* Description   : This function toggles the state of all available LCD segments
* Arguments     : None
* Return Value  : None
***********************************************************************************************************************/
static void toggle_lcd (void)
{
    /* Used to keep track of toggling all LCD segments on/off */
    static uint8_t lcd_toggle = FALSE;

    /* Check if the variable is TRUE */
    if (TRUE == lcd_toggle)
    {
        /* Turn off all segments */
        LCD_DISPLAY_OFF();

        /* Set the variable to FALSE */
        lcd_toggle = FALSE;
    }
    else
    {
        /* Turn on all segments */
        LCD_DISPLAY_ON();

        /* Set the variable to TRUE */
        lcd_toggle = TRUE;
    }
}
/***********************************************************************************************************************
* End of function toggle_lcd
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name : flash_lcd
* Description   : Calls the Toggle_LCD function to flash the LCD segments.
* Argument      : None
* Return value  : None
***********************************************************************************************************************/
static void flash_lcd (void)
{
    /* Declare loop count variables */
    volatile uint8_t  flash_count = 0u;

    /* Turn off all segments */
    LCD_DISPLAY_OFF();

    /* Flash the LCD segs for 200 times or until a user switch is pressed. */
    while ((0 == g_switch_flag) && (flash_count++ < 200))
    {
        uint16_t ms;

        /* Toggles the LCD segments */
        toggle_lcd();

        /* LCD flashing Delay */
        for (ms = 0; ms < 500; ms++)
        {
            R_TAU_MsDelay(1);

            /* poll for SW2 - not on interrupt */
            if (TRUE == Switch2_Poll(SWITCHHOLD_2))
            {
                g_switch_flag |= SWITCHHOLD_2;
                break;
            }
        }
    }

    /* Reset the flag variable */
    g_switch_flag = 0;
}
/***********************************************************************************************************************
End of function flash_lcd
***********************************************************************************************************************/


/* End user code. Do not edit comment generated here */
