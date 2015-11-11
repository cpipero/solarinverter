/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  dac.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.6.0$
*
* Description: Source file for the DAC driver
*
*****************************************************************************/

#include "qs.h"
#include "dac.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 dacInit() function performs the DAC module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void dacInit(arch_sDAC *pDacBase)
{
#pragma unused(pDacBase)

#if DAC_0_INIT_USED && defined(DAC_0)
	if (pDacBase == DAC_0)
	{
	    /* make sure the FORMAT is set to right-aligned */
	    #if defined(DAC_0_DATA_INIT) || defined(DAC_0_MINVAL_INIT) || \
            defined(DAC_0_STEP_INIT) || defined(DAC_0_MAXVAL_INIT)
		periphBitClear(DAC_CTRL_FORMAT, &pDacBase->ctrl);
		#endif
		
		#ifdef DAC_0_MINVAL_INIT
		periphMemWrite(DAC_0_MINVAL_INIT, &pDacBase->minval);
		#endif
		
		#ifdef DAC_0_MAXVAL_INIT
		periphMemWrite(DAC_0_MAXVAL_INIT, &pDacBase->maxval);
		#endif
		
		#ifdef DAC_0_STEP_INIT
		periphMemWrite(DAC_0_STEP_INIT, &pDacBase->step);
		#endif
		
		#ifdef DAC_0_DATA_INIT
		periphMemWrite(DAC_0_DATA_INIT, &pDacBase->data);
		#endif
		
		#ifdef DAC_0_CTRL_INIT
		periphMemWrite(DAC_0_CTRL_INIT, &pDacBase->ctrl);
		#endif
	}
	else
#endif	

#if DAC_1_INIT_USED && defined(DAC_1)
	if (pDacBase == DAC_1)
	{
	    /* make sure the FORMAT is set to right-aligned */
	    #if defined(DAC_1_DATA_INIT) || defined(DAC_1_MINVAL_INIT) || \
            defined(DAC_1_STEP_INIT) || defined(DAC_1_MAXVAL_INIT)
		periphBitClear(DAC_CTRL_FORMAT, &pDacBase->ctrl);
        #endif
        		
		#ifdef DAC_1_MINVAL_INIT
		periphMemWrite(DAC_1_MINVAL_INIT, &pDacBase->minval);
		#endif
		
		#ifdef DAC_1_MAXVAL_INIT
		periphMemWrite(DAC_1_MAXVAL_INIT, &pDacBase->maxval);
		#endif
		
		#ifdef DAC_1_STEP_INIT
		periphMemWrite(DAC_1_STEP_INIT, &pDacBase->step);
		#endif
		
		#ifdef DAC_1_DATA_INIT
		periphMemWrite(DAC_1_DATA_INIT, &pDacBase->data);
		#endif
		
		#ifdef DAC_1_CTRL_INIT
		periphMemWrite(DAC_1_CTRL_INIT, &pDacBase->ctrl);
		#endif
	}
	else
#endif	

	; /* last else case */
}


#ifdef __cplusplus
}
#endif

