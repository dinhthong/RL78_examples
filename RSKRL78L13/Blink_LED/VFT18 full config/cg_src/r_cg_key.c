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
* File Name    : r_cg_key.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMD
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for KEY module.
* Creation Date: 5/14/2021
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
#include "r_cg_key.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_KEY_Create
* Description  : This function initializes the key return module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_KEY_Create(void)
{
    volatile uint8_t w_count;

    /* Set KR0 pin */
    PFSEG1 &= 0xEFU;
    PU7 |= 0x01U;
    PM7 |= 0x01U;
    /* Set KR1 pin */
    PFSEG1 &= 0xDFU;
    PU7 |= 0x02U;
    PM7 |= 0x02U;
    /* Set KR2 pin */
    PFSEG1 &= 0xBFU;
    PU7 |= 0x04U;
    PM7 |= 0x04U;
    /* Set KR3 pin */
    PFSEG1 &= 0x7FU;
    PU7 |= 0x08U;
    PM7 |= 0x08U;
    /* Set KR4 pin */
    PFSEG2 &= 0xFEU;
    PU7 |= 0x10U;
    PM7 |= 0x10U;
    /* Set KR5 pin */
    PFSEG2 &= 0xFDU;
    PU7 |= 0x20U;
    PM7 |= 0x20U;
    /* Set KR6 pin */
    PFSEG2 &= 0xFBU;
    PU7 |= 0x40U;
    PM7 |= 0x40U;
    /* Set KR7 pin */
    PFSEG2 &= 0xF7U;
    PU7 |= 0x80U;
    PM7 |= 0x80U;
    KRMK = 1U;  /* disable INTKR operation */
    KRIF = 0U;  /* clear INTKR interrupt flag */
    /* Set INTKR low priority */
    KRPR1 = 1U;
    KRPR0 = 1U;
    KRCTL = _80_KR_RETURN_FLAG_USED | _00_KR_DETECTION_EDGE_FALL;
    KRM0 = _01_KR0_SIGNAL_DETECT_ON | _02_KR1_SIGNAL_DETECT_ON | _04_KR2_SIGNAL_DETECT_ON | _08_KR3_SIGNAL_DETECT_ON | 
           _10_KR4_SIGNAL_DETECT_ON | _20_KR5_SIGNAL_DETECT_ON | _40_KR6_SIGNAL_DETECT_ON | _80_KR7_SIGNAL_DETECT_ON;

    /* Change the waiting time according to the system  */
    for (w_count = 0U; w_count <= KEY_WAITTIME; w_count++)
    {   
        NOP();
    }
}
/***********************************************************************************************************************
* Function Name: R_KEY_Start
* Description  : This function clears INTKR interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_KEY_Start(void)
{
    KRIF = 0U;  /* clear INTKR interrupt flag */
    KRMK = 0U;  /* enable INTKR operation */
}
/***********************************************************************************************************************
* Function Name: R_KEY_Stop
* Description  : This function disables INTKR interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_KEY_Stop(void)
{
    KRMK = 1U;  /* disable INTKR operation */
    KRIF = 0U;  /* clear INTKR interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
