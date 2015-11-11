/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  occs.c
*
* $Date:      Jan-30-2009$
*
* $Version:   2.3.14.0$
*
* Description: Source file for the On-chip Clock Synthesis driver
*
*****************************************************************************/

#include "qs.h"
#include "occs.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

void occsInit(void)
{
	/* Note: The PLL is setup early in the startup.c code */
}


/* calculate core (=peripheral bus) frequency */

#if OCCS_VERSION == 1

UWord32 occsGetIPBusFreq(UWord32 oscFreq)
{
	UWord16 divBy, scaler;

	divBy = periphMemRead(&ArchIO.Pll.plldb);
	scaler = divBy>>8;
	scaler &= 0x0003;	/* ==prescaler */

	/* prescaler frequency */
	oscFreq >>= ++scaler;
	
	/* Postscaler Output ? (otherwise assume prescaler output) */
	if (periphBitTest(OCCS_PLLCR_ZSRC_POSTSCALER, &ArchIO.Pll.pllcr))
	{
		scaler = divBy>>10;
		divBy &= 0x007F;
		scaler &= 0x0003; 	/* ==postscaler */
		
		oscFreq *= ++divBy;
		oscFreq >>= ++scaler;
	}
	
	return oscFreq;
}

#endif

#if  (OCCS_VERSION >= 2) && (OCCS_VERSION <= 3) 

/* Fixed PLL OCCS */
UWord32 occsGetIPBusFreq(UWord32 oscFreq)
{
	UWord16 scaler;

	/* Postscaler Output ? */
	if (periphBitTest(OCCS_PLLCR_ZSRC_POSTSCALER, &ArchIO.Pll.pllcr))
	{
		scaler = periphMemRead(&ArchIO.Pll.plldb);
		scaler = (scaler>>8) & 0x7;

		if(scaler > 5)
			scaler = 5;		
		
		oscFreq *= 24/3;		/* fixed PLL / fixed divider for sys_clk2x */
		oscFreq >>= scaler;		/* postscaler */
	}

	/* sys_clk2x --> sys_clk */
	oscFreq >>= 1;
	return oscFreq;
}

#endif

#if  OCCS_VERSION >= 4 

/* Fixed PLL OCCS */
UWord32 occsGetIPBusFreq(UWord32 oscFreq)
{
	UWord16 scaler;

		scaler = periphMemRead(&ArchIO.Pll.plldb);
		scaler = (scaler>>8) & 0xf;

		if(scaler > 8)
			scaler = 8;		

	/* PLL Output ? */
	if (periphBitTest(OCCS_PLL_OSC_OUTPUT, &ArchIO.Pll.pllcr))
	{
		oscFreq *= 24/3;		/* fixed PLL / fixed divider for sys_clk2x */
	}
	oscFreq >>= scaler;		/* postscaler */
	/* sys_clk2x --> sys_clk */
	oscFreq >>= 1;
	return oscFreq;
}

#endif



#ifdef __cplusplus
}
#endif

