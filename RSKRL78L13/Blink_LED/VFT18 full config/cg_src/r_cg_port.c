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
* File Name    : r_cg_port.c
* Version      : Applilet4 for RL78/L13 V1.00.00.02 [10 May 2013]
* Device(s)    : R5F10WMD
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Port module.
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
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    PFSEG0 = _80_PFSEG07_SEG | _00_PFSEG06_PORT | _00_PFSEG05_PORT | _00_PFSEG04_PORT;
    PFSEG1 = _00_PFSEG15_PORT | _00_PFSEG14_PORT | _00_PFSEG13_PORT | _00_PFSEG12_PORT | _00_PFSEG11_PORT | 
             _00_PFSEG10_PORT | _00_PFSEG09_PORT | _00_PFSEG08_PORT;
    PFSEG2 = _00_PFSEG23_PORT | _40_PFSEG22_SEG | _00_PFSEG21_PORT | _10_PFSEG20_SEG | _00_PFSEG19_PORT | 
             _00_PFSEG18_PORT | _00_PFSEG17_PORT | _00_PFSEG16_PORT;
    PFSEG3 = _00_PFSEG30_PORT | _00_PFSEG29_PORT | _00_PFSEG28_PORT | _00_PFSEG27_PORT | _00_PFSEG26_PORT | 
             _00_PFSEG25_PORT | _01_PFSEG24_SEG | _04_PFDEG_DEFAULT;
    PFSEG4 = _00_PFSEG38_PORT | _00_PFSEG37_PORT | _00_PFSEG36_PORT | _00_PFSEG35_PORT | _08_PFSEG34_SEG | 
             _00_PFSEG33_PORT | _00_PFSEG32_PORT | _00_PFSEG31_PORT;
    PFSEG5 = _00_PFSEG46_PORT | _40_PFSEG45_SEG | _00_PFSEG44_PORT | _10_PFSEG43_SEG | _00_PFSEG42_PORT | 
             _04_PFSEG41_SEG | _02_PFSEG40_SEG | _00_PFSEG39_PORT;
    P0 = _00_Pn1_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
    P1 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 | 
         _00_Pn7_OUTPUT_0;
    P2 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0;
    P3 = _00_Pn5_OUTPUT_0;
    P4 = _00_Pn1_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | 
         _00_Pn7_OUTPUT_0;
    P5 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
    P13 = _00_Pn0_OUTPUT_0;
    PU5 = _20_PUn5_PULLUP_ON;
    PU7 = _01_PUn0_PULLUP_ON | _02_PUn1_PULLUP_ON | _04_PUn2_PULLUP_ON | _08_PUn3_PULLUP_ON | _10_PUn4_PULLUP_ON | 
          _20_PUn5_PULLUP_ON | _40_PUn6_PULLUP_ON | _80_PUn7_PULLUP_ON;
    PMC1 = _00_PMCn0_DI_ON | _00_PMCn1_DI_ON | _00_PMCn2_DI_ON | _00_PMCn3_DI_ON | _F0_PMC1_DEFAULT;
    PMC2 = _00_PMCn2_DI_ON | _00_PMCn3_DI_ON | _00_PMCn4_DI_ON | _00_PMCn5_DI_ON | _03_PMC2_DEFAULT;
    ADPC = _02_ADPC_DI_ON;
    PM0 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _04_PMn2_NOT_USE | _00_PMn3_MODE_OUTPUT | _10_PMn4_NOT_USE | 
          _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
    PM1 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | 
          _00_PMn4_MODE_OUTPUT | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _00_PMn7_MODE_OUTPUT;
    PM2 = _01_PMn0_MODE_INPUT | _02_PMn1_NOT_USE | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | 
          _00_PMn4_MODE_OUTPUT | _20_PMn5_MODE_INPUT | _40_PMn6_MODE_INPUT | _80_PMn7_NOT_USE;
    PM3 = _01_PMn0_NOT_USE | _02_PMn1_MODE_INPUT | _04_PMn2_NOT_USE | _08_PMn3_MODE_INPUT | _10_PMn4_NOT_USE | 
          _00_PMn5_MODE_OUTPUT | _C0_PM3_DEFAULT;
    PM4 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _04_PMn2_NOT_USE | _00_PMn3_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | 
          _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
    PM5 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _08_PMn3_NOT_USE | 
          _10_PMn4_MODE_INPUT | _20_PMn5_NOT_USE | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
    PM13 = _00_PMn0_MODE_OUTPUT | _FE_PM13_DEFAULT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
