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
* Creation Date: 5/4/2021
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
#include "r_cg_sau.h"
#include "r_cg_rtc.h"
/* Start user code for include. Do not edit comment generated here */
#include "switch.h"
#include "IO_Config.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "LCDlib.h"
#include "Sys.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile rtc_counter_value_t stRTC_Data;
volatile uint8_t time_str[10];

rtc_counter_value_t setRTC_Data;


/* Some of the code in this file is generated using "Application Leading Tool (Applilet)" */
/* Warnings exist in this module. */

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

        // LCD_CS  = 0;
        // LCD_RST = 0;   // LED2 to Rest pin of LCD
        // R_TAU_MsDelay(500);
        // LCD_RST = 1;
	
	    // LCD_write(0, 0xA3);   // LCD set bias_7
        // LCD_write(0, 0x40);    // LCD set start line
        // LCD_write(0, 0x2C); // LCD set power control
        // R_TAU_MsDelay(50);  // 
        // LCD_write(0, 0x2E);  // LCD set power control
        // R_TAU_MsDelay(50);
        // LCD_write(0, 0x2F);// LCD set power control
        // R_TAU_MsDelay(10);
        
        // LCD_write(0, 0xAF);   // LCD display ON
        // LCD_write(0, 0xA4);   // all pixel off

        // LCD_write(0, 0x81);   //LCD set EV
        // LCD_write(0, 10);      // LCD set contrast
        
        // LCD_write(0, 0xA1);     // LCD set ADC reverse
        // LCD_write(0, 0xC8);     // LCD set vertical direction
        // LCD_write(0, 0x24);     // LCD set regulation ratio

        // LCD_write(0, 0xB0);     // LCD start page
        // LCD_write(0, 0x04);     //  LCD start column LSB byte
        // LCD_write(0, 0x10);        //  LCD start column MSB byte

        // R_TAU_MsDelay(3000);
        // LCD_write(0, 0xA5);   // all pixel on
        // R_TAU_MsDelay(500);
        // LCD_write(0, 0xA4);
        // R_TAU_MsDelay(500);
        // LCD_write(0, 0xA5);
        // R_TAU_MsDelay(500);
        // LCD_write(0, 0xA4);
        // R_TAU_MsDelay(500);

        // LCD_write(1, 0xFF);
        // R_TAU_MsDelay(1500);
        // LCD_write(1, 0xFE);
        // R_TAU_MsDelay(1500);
        // LCD_write(1, 0xFC);
        // R_TAU_MsDelay(1500);
        // LCD_write(1, 0xF8);
        // R_TAU_MsDelay(1500);

        LCD_init();
        LCD_write(0, 0x40);
        LCD_write(0, 0xB0);
        LCD_write(0, 0x04);

        LCD_putc('!');
        R_TAU_MsDelay(1000);
        LCD_putc(' ');
        R_TAU_MsDelay(1000);
        LCD_putc('@');
        R_TAU_MsDelay(1000);
        LCD_putc(0x7F);
        R_TAU_MsDelay(1000);

        LCD_gotoXY(4,0);
        LCD_putc(0x7e);
        R_TAU_MsDelay(1000);

        LCD_clear();
        LCD_gotoXY(4,0);
        LCD_puts("abcd 1234");
        R_TAU_MsDelay(1000);
    
    /* Start the RTC */
    R_RTC_Start();

    /* Wait at least 2*fRTC clock cycles */
    R_TAU_MsDelay(2);

    /* Set the RTC interrupt to 1 second */
    R_RTC_Set_ConstPeriodInterruptOn(ONESEC);

    setRTC_Data.sec = 0x55;
    setRTC_Data.min = 0x11;
    setRTC_Data.hour = 0x23;

    LCD_gotoXY(4,3);
    LCD_puts(time_str);
    R_TAU_MsDelay(3000);
    LCD_gotoXY(4,3);
    LCD_puts(time_str);
    R_TAU_MsDelay(3000);
    R_RTC_Set_CounterValue(setRTC_Data);
    while (1U)
    {

        

        
        LCD_gotoXY(4,3);
        LCD_puts(time_str);
	
 
      /*  LCD_A0 = 0; // LED3 to Register Select pin of LCD
       g_csi00_txbuffer[0] = 0xA3;
       Sync_Send();

       // Select start line
       g_csi00_txbuffer[0] = 0x40;  //0x55
       Sync_Send();

       g_csi00_txbuffer[0] = 0x2C;
       Sync_Send();
       R_TAU_MsDelay(50);

       g_csi00_txbuffer[0] = 0x2E;
       Sync_Send();
       R_TAU_MsDelay(50);

       g_csi00_txbuffer[0] = 0x2F;
       Sync_Send();
       R_TAU_MsDelay(10);     

       g_csi00_txbuffer[0] = 0xAF;
       Sync_Send();        

       g_csi00_txbuffer[0] = 0xA4;
       Sync_Send();

       //LCD set contrast
       g_csi00_txbuffer[0] = 0x81;
       Sync_Send();
       g_csi00_txbuffer[0] = 10;
       Sync_Send();

       R_TAU_MsDelay(20);
       // LCD set non-mirror (ADC select) - Truc x
       g_csi00_txbuffer[0] = 0xA1;
       Sync_Send(); 
       R_TAU_MsDelay(20);

       //LCD set SEG direction - Truc y
       g_csi00_txbuffer[0] = 0xC8;
       Sync_Send(); 
       R_TAU_MsDelay(20);

       //LCD set resistor ratio
       g_csi00_txbuffer[0] = 0x24;
       Sync_Send();   



       //Set start page
       g_csi00_txbuffer[0] = 0xB0;	//0xB3
       Sync_Send(); 

       //Set start conlumn
       g_csi00_txbuffer[0] = 0x04;   //0x06
       Sync_Send();
       g_csi00_txbuffer[0] = 0x10;  //0x16
       Sync_Send();





       R_TAU_MsDelay(3000);

       g_csi00_txbuffer[0] = 0xA5;
       Sync_Send();
       R_TAU_MsDelay(500);

       g_csi00_txbuffer[0] = 0xA4;
       Sync_Send();
       R_TAU_MsDelay(500);

       g_csi00_txbuffer[0] = 0xA5;
       Sync_Send();
       R_TAU_MsDelay(500);
	
	    g_csi00_txbuffer[0] = 0xA4;
       Sync_Send();
       R_TAU_MsDelay(500);

       // Write a char to LCD
       LCD_A0 = 1;
       g_csi00_txbuffer[0] = 0xFF;
       Sync_Send();
       R_TAU_MsDelay(1500);

       g_csi00_txbuffer[0] = 0xFE;
       Sync_Send();
       R_TAU_MsDelay(1500);

       g_csi00_txbuffer[0] = 0xFC;
       Sync_Send();
       R_TAU_MsDelay(1500);

       g_csi00_txbuffer[0] = 0xF8;
       Sync_Send();
       R_TAU_MsDelay(1500);


 */









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
