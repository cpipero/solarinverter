/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  pit.c
*
* $Date:      Feb-19-2009$
*
* $Version:   2.3.5.0$
*
* Description: Source file for the PIT driver
*
*****************************************************************************/

#include "qs.h"
#include "pit.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 pitInit() function performs the PIT module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void pitInit(arch_sPIT *pPitBase)
{
#pragma unused (pPitBase)

#if PIT_INIT_USED && defined(PIT)
	if (pPitBase == PIT)
	{
		#ifdef PIT_MOD_INIT
		periphMemWrite(PIT_MOD_INIT, &pPitBase->mod);
		#endif
		
		#ifdef PIT_CTRL_INIT
		periphMemWrite(PIT_CTRL_INIT, &pPitBase->ctrl);
		#endif
	}
	else
#endif	

#if PIT_0_INIT_USED && defined(PIT_0)
	if (pPitBase == PIT_0)
	{
		#ifdef PIT_0_MOD_INIT
		periphMemWrite(PIT_0_MOD_INIT, &pPitBase->mod);
		#endif
		
		#ifdef PIT_0_CTRL_INIT
		periphMemWrite(PIT_0_CTRL_INIT, &pPitBase->ctrl);
		#endif
	}
	else
#endif	

#if PIT_1_INIT_USED && defined(PIT_1)
	if (pPitBase == PIT_1)
	{
		#ifdef PIT_1_MOD_INIT
		periphMemWrite(PIT_1_MOD_INIT, &pPitBase->mod);
		#endif
		
		#ifdef PIT_1_CTRL_INIT
		periphMemWrite(PIT_1_CTRL_INIT, &pPitBase->ctrl);
		#endif
	}
	else
#endif	

#if PIT_2_INIT_USED && defined(PIT_2)
	if (pPitBase == PIT_2)
	{
		#ifdef PIT_2_MOD_INIT
		periphMemWrite(PIT_2_MOD_INIT, &pPitBase->mod);
		#endif
		
		#ifdef PIT_2_CTRL_INIT
		periphMemWrite(PIT_2_CTRL_INIT, &pPitBase->ctrl);
		#endif
	}
	else
#endif	

	; /* last else case */
}


#ifdef __cplusplus
}
#endif

