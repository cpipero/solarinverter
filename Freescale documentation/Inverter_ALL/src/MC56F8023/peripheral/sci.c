/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  sci.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.19.0$
*
* Description: Header file for the SCI driver.
*
*******************************************************************************/

#include "qs.h"

/* in sci.h, ignore that we whave not included occs.h before
  (otherwise we would get error that baudrates are inaccessible) */
#define SCI_DISABLE_BAUDRATE_WARNING 1

#include "sci.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************

    sciInit() function performs the SCI module static configuration
    based on the configurable items from appconfig.h 

    It is the same for any higher software layer implementation used

********************************************************************************/

void sciInit(arch_sSCI *pSciBase)
{
#pragma unused(pSciBase)

#if SCI_0_INIT_USED && defined(SCI_0)
	if (pSciBase == SCI_0)
	{
		#ifdef SCI_0_SCIBR_INIT
		periphMemWrite(SCI_0_SCIBR_INIT, &pSciBase->scibr);
		#endif
		
		#ifdef SCI_0_SCICR_INIT
		periphMemWrite(SCI_0_SCICR_INIT, &pSciBase->scicr);
		#endif

		/* SCI_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef SCI_0_SCICR2_INIT
		periphMemWrite(SCI_0_SCICR2_INIT, &pSciBase->scicr2);
		#endif
	}
	else
#endif	

#if SCI_1_INIT_USED && defined(SCI_1)
	if (pSciBase == SCI_1)
	{
		#ifdef SCI_1_SCIBR_INIT
		periphMemWrite(SCI_1_SCIBR_INIT, &pSciBase->scibr);
		#endif
		
		#ifdef SCI_1_SCICR_INIT
		periphMemWrite(SCI_1_SCICR_INIT, &pSciBase->scicr);
		#endif

		/* SCI_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef SCI_1_SCICR2_INIT
		periphMemWrite(SCI_1_SCICR2_INIT, &pSciBase->scicr2);
		#endif
	}
	else
#endif

	; /* last else case */
}


#ifdef __cplusplus
}
#endif
