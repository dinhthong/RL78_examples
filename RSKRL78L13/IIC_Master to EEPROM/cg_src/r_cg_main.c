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
* Creation Date: 30/09/2013
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
#include "r_cg_iica.h"
#include "r_cg_lcd.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */

/* Some of the code in this file is generated using "Application Leading Tool (Applilet)" */
/* Warnings exist in this module. */

#include "lcd_panel.h"
#include "switch.h"
#include "rskrl78l13def.h"
#include <string.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/* Prototype declaration for master_eeprom */
static void master_eeprom (void);

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
    
    /* initialise the switch functions */
    Switch_Init();

    /* Enable and configure LCD display */
    Init_Display_Panel();
    
    Display_Panel_String(PANEL_LCD_LINE1, " IICM");

    while (1U)
    {
        /* Run the master_eeprom function forever */
        master_eeprom();
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
/*******************************************************************************
* Function Name : master_eeprom
* Description   : Enters an infinite loop with SW1 presses used
*                 write data to the EEPROM slave and SW2 presses to read from
*                 the EEPROM slave and compare the data read with the data
*                 written.
* Arguments     : none
* Return Value  : none
*******************************************************************************/
static void master_eeprom (void)
{
    /* Declare a variable for IIC command results */
    MD_STATUS   ret = 0;

    /* Initialise the write count variable */
    static char write_count = '0';

    /* Define read buffer array */
    char        read_buffer[] = "xxxxxxx";
    static char num_buff[4] = "   ";

    /* Initialise the write buffer */
    /* First byte is the address of the eeprom location we are writing to */
    /* This is always 0 */
    /* 2nd byte - X will be replaced with index of the write */
    /* which is incremented on each write */
    static char write_buffer[] = "\0\0XRL78L13";

    if (g_switch_flag & SWITCHHOLD_1)
    {
        /* Update the write_count field of the buffer before sending */
        write_buffer[EEPROM_WRITE_COUNT] = write_count;

        /* Write the buffer contents to the slave */
        ret = R_IICA0_Master_Send(EEPROM_DEVICE_ADDRESS,
                                  (uint8_t *)write_buffer,
                                  EEPROM_NUMB_WRITE,
                                  0xF);

        /* Wait for transmission to complete */
        R_IICA0_Master_Wait_Tx_Complete();

        /* Check that the write command succeeded */
        if (ret == MD_OK)
        {
            /* Display the sent data in the 2nd line of the LCD */
            Display_Panel_String(PANEL_LCD_LINE1, " M-Wr");
            num_buff[0] = write_buffer[2];
            Display_Panel_String(PANEL_LCD_LINE3, num_buff);
        }
        else
        {
            /* Display a message that an error occurred */
            Display_Panel_String(PANEL_LCD_LINE1, " ErrW");
        }

        /* Increment the write_count and reset it if it reaches ASCII 9+1 */
        if (0x3a == ++write_count)
        {
            write_count = '0';
        }

        /* Clear the switch flag */
        g_switch_flag &= (uint8_t) ~SWITCHHOLD_1;
    }
    else if (g_switch_flag & SWITCHHOLD_3)
    {
/* Read address should only be configured if an EEPROM is used as a slave */
#ifndef SLAVE_RL78L13

        /* Send dummy write to configure memory to be read i.e. 0 */
        ret = R_IICA0_Master_Send(EEPROM_DEVICE_ADDRESS,
                                  (uint8_t *)write_buffer,
                                  2u,
                                  0xF);

        /* Wait for transmission to complete */
        R_IICA0_Master_Wait_Tx_Complete();
#endif
        /* Receive the data */
        ret = R_IICA0_Master_Receive(EEPROM_DEVICE_ADDRESS | 0x01,
                                     (uint8_t *)read_buffer,
                                     EEPROM_RECEIVE_COUNT, 0xF);

        if (MD_OK != ret)
        {
           /* Display a message that an error occurred */
            Display_Panel_String(PANEL_LCD_LINE1, " ErrR");
         }

        /* Wait for reception to complete */
        R_IICA0_Master_Wait_Rx_Complete();

        /* Compare read and written data */
        if (0 == memcmp (read_buffer, write_buffer + 2, EEPROM_RECEIVE_COUNT))
        {
            /* Notify the user we read back ok */
            Display_Panel_String(PANEL_LCD_LINE1, " M-Rd");
         }
        else
        {
            /* Notify the user an error has occurred */
            Display_Panel_String(PANEL_LCD_LINE1, " ErrR");
        }

        /* Display the received data in the 2nd line of the LCD */
        num_buff[2] = read_buffer[0];
        Display_Panel_String(PANEL_LCD_LINE3, num_buff);

        /* Clear the switch flag */
        g_switch_flag &= (uint8_t) ~SWITCHHOLD_3;
    }
    else
    {
        /* Do nothing */
    }
}
/*******************************************************************************
* End of function master_eeprom
*******************************************************************************/

/* End user code. Do not edit comment generated here */
