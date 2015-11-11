/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  cmp.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.4.0$
*
* Description: Source file for the CMP driver
*
*****************************************************************************/

#include "qs.h"
#include "cmp.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 cmpInit() function performs the CMP module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void cmpInit(arch_sCMP *pCmpBase)
{
#pragma unused(pCmpBase)

#if CMP_A_INIT_USED && defined(CMP_A)
	if (pCmpBase == CMP_A)
	{
		#ifdef CMP_A_CTRL_INIT
		periphMemWrite(CMP_A_CTRL_INIT, &pCmpBase->ctrl);
		#endif
		
		#ifdef CMP_A_FILT_INIT
		periphMemWrite(CMP_A_FILT_INIT, &pCmpBase->filt);
		#endif
	}
	else
#endif	

#if CMP_B_INIT_USED && defined(CMP_B)
	if (pCmpBase == CMP_B)
	{
		#ifdef CMP_B_CTRL_INIT
		periphMemWrite(CMP_B_CTRL_INIT, &pCmpBase->ctrl);
		#endif
		
		#ifdef CMP_B_FILT_INIT
		periphMemWrite(CMP_B_FILT_INIT, &pCmpBase->filt);
		#endif
	}
	else
#endif	

	; /* last else case */
}

#ifdef __cplusplus
}
#endif

