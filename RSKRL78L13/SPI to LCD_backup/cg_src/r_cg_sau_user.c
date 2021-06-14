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
* File Name    : r_cg_sau_user.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for SAU module.
* Creation Date: 5/4/2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTCSI00 r_csi00_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
/* Start user code for include. Do not edit comment generated here */

/* Some of the code in this file is generated using "Application Leading Tool (Applilet)" */
/* Warnings exist in this module. */

/* Useful macros and function prototypes for controlling the LCD interface. */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_csi00_rx_address;         /* csi00 receive buffer address */
extern volatile uint16_t  g_csi00_rx_length;           /* csi00 receive data length */
extern volatile uint16_t  g_csi00_rx_count;            /* csi00 receive data count */
extern volatile uint8_t * gp_csi00_tx_address;         /* csi00 send buffer address */
extern volatile uint16_t  g_csi00_send_length;         /* csi00 send data length */
extern volatile uint16_t  g_csi00_tx_count;            /* csi00 send data count */

/* Start user code for global. Do not edit comment generated here */

/* Declaration of the CSI00 transmit buffer */
//char g_csi00_txbuffer[TRANSFER_LENGTH] = "0 CSI00 to CSI10 Loopback Test";

/* Declaration of the CSI10 transmit buffer */
char g_csi00_txbuffer[1] = {0};

/* Declaration of CSI00 receive buffers */
//char g_csi00_rxbuffer[TRANSFER_LENGTH] = "                             ";

/* Declaration of CSI10 receive buffers */
//char g_csi10_rxbuffer[TRANSFER_LENGTH] = "                             ";

/* Declaration of loopback test success flag */
static volatile test_status_t g_test_status;

/* Declaration of loopback test in progress flag */
static volatile uint8_t sending_in_progress = 0;
static volatile uint8_t sending_one_byte = 0;

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_csi00_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_csi00_interrupt(void)
{
    // uint8_t err_type;

    // err_type = (uint8_t)(SSR00 & _0001_SAU_OVERRUN_ERROR);
    // SIR00 = (uint16_t)err_type;

    // if (err_type != 1U)
    if (sending_one_byte == 1)
    {
        sending_one_byte = 0;
        r_csi00_callback_sendend();
    }
    else if (g_csi00_tx_count > 0U)
    {
        SIO00 = *gp_csi00_tx_address;
        gp_csi00_tx_address++;
        g_csi00_tx_count--;
    }
    else
    {
        r_csi00_callback_sendend();    /* complete send */
    }
}
/***********************************************************************************************************************
* Function Name: r_csi00_callback_sendend
* Description  : This function is a callback function when CSI00 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    sending_in_progress = 0;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/*******************************************************************************
* Function Name: Sync_Transfer
* Description  : This function clears the CSI00 and CSI01 receive buffers before
*                starting serial operations. CSI00 and CSI01 are configured to
*                transmit and receive data between either channels. A timer is
*                used to create a delay to allow completion of data transfers.
* Argument     : None
* Return value : None
*******************************************************************************/
void Sync_Send_Array (const uint8_t * ptrString, uint8_t len)
{
    sending_in_progress = 1;

    R_CSI00_Start();

    R_CSI00_Send_Array ((uint8_t * const)ptrString,len);

    while(sending_in_progress)
    {

    }
}

void Sync_Send_Byte (uint8_t byte)
{
    sending_one_byte = 1;

    sending_in_progress = 1;
    
    R_CSI00_Start();

    R_CSI00_Send_Byte(byte);

    while(sending_in_progress)
    {

    }



}






// void Sync_Transfer (void)
// {
//     /* Declare a loop count variable */
//     uint8_t i = 0;

//     /* Clear the CSI00 and CSI10 receive buffers */
//     for (i = 0; i < TRANSFER_LENGTH; i++)
//     {
//         /* Clear buffer location pointed by the loop count value */
//         g_csi10_rxbuffer[i] = 0;

//         /* Clear buffer location pointed by the loop count value */
//         g_csi00_rxbuffer[i] = 0;
//     }

//     /* Set the g_test_in_progress to 1 */
//     g_test_in_progress = 1;

//     /* Start CSI10 operations */
//     R_CSI10_Start();

//     /* Start CSI00 operations */
//     R_CSI00_Start();

//     /* Specify the CSI10 transmit and receive buffer sizes and addresses.
//        Casting to ensure correct data types used. */
//     R_CSI10_Send_Receive ((uint8_t * const)g_csi10_txbuffer,
//                           TRANSFER_LENGTH,
//                           (uint8_t * const)g_csi10_rxbuffer);

//     R_CSI00_Send_Receive ((uint8_t * const)g_csi00_txbuffer,
//                           TRANSFER_LENGTH,
//                           (uint8_t * const)g_csi00_rxbuffer);

//     /* Wait for g_test_in_progress flag to clear */
//     while (g_test_in_progress)
//     {
//         /* Wait */
//     }

//     /* Display the test status */
//     switch (g_test_status)
//     {
//         case TEST_CLK_ERR:
//         {
//             Display_Panel_String(PANEL_LCD_LINE1, " ERR0 ");
//         }
//         break;

//         case TEST0_ERR:
//         {
//             Display_Panel_String(PANEL_LCD_LINE1, " ERR1 ");
//         }
//         break;

//         case TEST1_ERR:
//         {
//             Display_Panel_String(PANEL_LCD_LINE1, " ERR2 ");
//         }
//         break;

//         case TEST_FAILED:
//         {
//             Display_Panel_String(PANEL_LCD_LINE1, " XXX ");
//         }
//         break;

//         case TEST_PASS:
//         {
//             Display_Panel_String(PANEL_LCD_LINE1, " OK  ");
//         }
//         break;

//         default:
//         {
//             /* Do Nothing */
//         }
//         break;
//     }
// } 

/*******************************************************************************
* End of function Sync_Transfer
*******************************************************************************/
/* End user code. Do not edit comment generated here */
