/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  cop.c
*
* $Date:      Oct-30-2008$
*
* $Version:   2.3.12.0$
*
* Description: Source file for the COP Driver
*
*****************************************************************************/

#include "qs.h"
#include "cop.h"

#ifdef __cplusplus
extern "C" {
#endif

/* initialization of COP (watchdog) */

void copInit(arch_sCOP *pCopBase)
{
#pragma unused(pCopBase)

	/* we are writing to COP Timeout reg first to allow using
	   write protect bit (CWP) in COP Control Reg */ 
	
	#ifdef COP_COPTO_INIT
	  periphMemWrite(COP_COPTO_INIT, &pCopBase->copto);
	#endif
	#ifdef COP_COPCTL_INIT
	periphMemWrite(COP_COPCTL_INIT, &pCopBase->copctl);
	#endif
	/* COP Service Register is not initialized */
}

#ifdef __cplusplus
}
#endif
