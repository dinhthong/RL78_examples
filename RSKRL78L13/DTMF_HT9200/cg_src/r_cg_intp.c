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
* File Name    : r_cg_intp.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for INTP module.
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
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_INTC_Create
* Description  : This function initializes INTP module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_Create(void)
{
    PMK0 = 1U;    /* disable INTP0 operation */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK1 = 1U;    /* disable INTP1 operation */
    PIF1 = 0U;    /* clear INTP1 interrupt flag */
    PMK2 = 1U;    /* disable INTP2 operation */
    PIF2 = 0U;    /* clear INTP2 interrupt flag */
    PMK3 = 1U;    /* disable INTP3 operation */
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
    PMK4 = 1U;    /* disable INTP4 operation */
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
    PMK5 = 1U;    /* disable INTP5 operation */
    PIF5 = 0U;    /* clear INTP5 interrupt flag */
    PMK6 = 1U;    /* disable INTP6 operation */
    PIF6 = 0U;    /* clear INTP6 interrupt flag */
    PMK7 = 1U;    /* disable INTP7 operation */
    PIF7 = 0U;    /* clear INTP7 interrupt flag */
    /* Set INTP0 level 1 priority */
    PPR10 = 0U;
    PPR00 = 1U;
    /* Set INTP7 level 1 priority */
    PPR17 = 0U;
    PPR07 = 1U;
    EGN0 = _01_INTP0_EDGE_FALLING_SEL | _80_INTP7_EDGE_FALLING_SEL;
    /* Set INTP7 pin */
    PFSEG5 &= 0xBFU;
    PM0 |= 0x04U;
}

/***********************************************************************************************************************
* Function Name: R_INTC0_Start
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC0_Start(void)
{
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
    PMK0 = 0U;    /* enable INTP0 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTC0_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC0_Stop(void)
{
    PMK0 = 1U;    /* disable INTP0 interrupt */
    PIF0 = 0U;    /* clear INTP0 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_INTC7_Start
* Description  : This function clears INTP7 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC7_Start(void)
{
    PIF7 = 0U;    /* clear INTP7 interrupt flag */
    PMK7 = 0U;    /* enable INTP7 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTC7_Stop
* Description  : This function disables INTP7 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC7_Stop(void)
{
    PMK7 = 1U;    /* disable INTP7 interrupt */
    PIF7 = 0U;    /* clear INTP7 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/*******************************************************************************
* Function Name: R_INTC0_IsFallingEdge
* Description  : This function returns 1 if the ITNC0 is set to falling edge 
*                triggered, otherwise 0.
* Arguments    : None
* Return Value : None
*******************************************************************************/
uint8_t R_INTC0_IsFallingEdge (void)
{
    uint8_t falling_edge_trig = 0x0;
    
    if (EGN0 & _01_INTP0_EDGE_FALLING_SEL)
    {
        falling_edge_trig = 1;
    }
        
    return falling_edge_trig;
    
}
/*******************************************************************************
* End of function R_INTC0_IsFallingEdge
*******************************************************************************/

/*******************************************************************************
* Function Name: R_INTC0_SetFallingEdge
* Description  : This function sets/clears the falling edge trigger for INTP0.
* Arguments    : uint8_t set_f_edge, 1 if setting falling edge triggered, 0 if 
*                clearing
* Return Value : None
*******************************************************************************/
void R_INTC0_SetFallingEdge (const uint8_t set_f_edge)
{
    if (1 == set_f_edge)
    {
        EGN0 |= _01_INTP0_EDGE_FALLING_SEL;    
    }
    else
    {
        EGN0 &= (uint8_t) ~_01_INTP0_EDGE_FALLING_SEL;    
    }
}
/******************************************************************************
* End of function R_INTC0_SetFallingEdge
*******************************************************************************/

/*******************************************************************************
* Function Name: R_INTC0_SetRisingEdge
* Description  : This function sets/clear the rising edge trigger for INTP0.
* Arguments    : uint8_t set_r_edge, 1 if setting rising edge triggered, 0 if
*                clearing
* Return Value : None
*******************************************************************************/
void R_INTC0_SetRisingEdge (const uint8_t set_r_edge)
{
    if (1 == set_r_edge)
    {
        EGP0 |= _01_INTP0_EDGE_RISING_SEL;    
    }
    else
    {
        EGP0 &= (uint8_t) ~_01_INTP0_EDGE_RISING_SEL;    
    }
}
/******************************************************************************
* End of function R_INTC0_SetRisingEdge
*******************************************************************************/

/*******************************************************************************
* Function Name: R_INTC7_IsFallingEdge
* Description  : This function returns 1 if the INTP7 is set to falling edge
*                triggered, otherwise 0.
* Arguments    : None
* Return Value : None
*******************************************************************************/
uint8_t R_INTC7_IsFallingEdge (void)
{
    uint8_t falling_edge_trig = 0x0;
    
    if (EGN0 & _80_INTP7_EDGE_FALLING_SEL)
    {
        falling_edge_trig = 1;
    }
        
    return falling_edge_trig;
    
}
/******************************************************************************
* End of function R_INTC7_IsFallingEdge
*******************************************************************************/
/*******************************************************************************
* Function Name: R_INTC7_SetFallingEdge
* Description  : This function sets/clears the falling edge trigger for INTP7.
* Arguments    : uint8_t set_f_edge, 1 if setting falling edge triggered, 0 
*                if clearing
* Return Value : None
*******************************************************************************/
void R_INTC7_SetFallingEdge (const uint8_t set_f_edge)
{
    if (1 == set_f_edge)
    {
        EGN0 |= _80_INTP7_EDGE_FALLING_SEL;
    }
    else
    {
        EGN0 &= (uint8_t) ~_80_INTP7_EDGE_FALLING_SEL;
    }
}
/*******************************************************************************
* End of function R_INTC7_SetFallingEdge
*******************************************************************************/
/*******************************************************************************
* Function Name: R_INTC7_SetRisingEdge
* Description  : This function sets/clear the rising edge trigger for INTP0.
* Arguments    : uint8_t set_r_edge, 1 if setting rising edge triggered, 0 if
*                clearing
* Return Value : None
*******************************************************************************/
void R_INTC7_SetRisingEdge (const uint8_t set_r_edge)
{
    if (1 == set_r_edge)
    {
        EGP0 |= _80_INTP7_EDGE_RISING_SEL;
    }
    else
    {
        EGP0 &= (uint8_t) ~_80_INTP7_EDGE_RISING_SEL;
    }
}
/******************************************************************************
* End of function R_INTC7_SetRisingEdge
******************************************************************************/
/* End user code. Do not edit comment generated here */
