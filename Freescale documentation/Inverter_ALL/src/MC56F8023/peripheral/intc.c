/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  intc.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.15.0$
*
* Description: Source file for the Interrupt Controller driver for MC56F8xxx
*
*****************************************************************************/

#include "qs.h"
#include "intc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* this macro is used to concatenate two given atoms but it allows atom translation 
 * in the case atom is another macro (e.g. INTC_FIM0_INIT to a number assigned) */
#define _CAT(a,b) _CAT1(a,b)
#define _CAT1(a,b) a##b
 
/* if fast interrupt 0 or 1 are to be initialized but no handler address was specified
   for them, we will use standard INT_VECTOR_ADDR_n as their handlers
   
   where n = INTC_FIM0_INIT or INTC_FIM0_INIT
*/
   
#if INTC_FIM0_INIT
#ifndef INTC_FIVA0_INIT
#define INTC_FIVA0_INIT _CAT(INT_VECTOR_ADDR_, INTC_FIM0_INIT)
#endif
#endif /* INTC_FIM0_INIT */

#if INTC_FIM1_INIT
#ifndef INTC_FIVA1_INIT
#define INTC_FIVA1_INIT _CAT(INT_VECTOR_ADDR_, INTC_FIM1_INIT)
#endif
#endif /* INTC_FIM1_INIT */

/* we also need to prototype the fast interrupt handlers  */
#ifdef INTC_FIVA0_INIT
void INTC_FIVA0_INIT(void);
#endif
#ifdef INTC_FIVA1_INIT
void INTC_FIVA1_INIT(void);
#endif

void intcInit(arch_sIntc *pIntcBase)
{
#pragma unused(pIntcBase)

	#ifdef INTC_ICTL_INIT
	periphMemWrite(INTC_ICTL_INIT,&pIntcBase->ictl);
	#endif 

	/* IPRn_INIT values are defined internally in intc.h, based on INT_PRIORITY_LEVEL_n macros */
	#ifdef INTC_IPR0_INIT
	periphMemWrite(INTC_IPR0_INIT,&pIntcBase->ipr[0]);
	#endif
	#ifdef INTC_IPR1_INIT
	periphMemWrite(INTC_IPR1_INIT,&pIntcBase->ipr[1]);
	#endif
	#ifdef INTC_IPR2_INIT
	periphMemWrite(INTC_IPR2_INIT,&pIntcBase->ipr[2]);
	#endif
	#ifdef INTC_IPR3_INIT
	periphMemWrite(INTC_IPR3_INIT,&pIntcBase->ipr[3]);
	#endif
	#ifdef INTC_IPR4_INIT
	periphMemWrite(INTC_IPR4_INIT,&pIntcBase->ipr[4]);
	#endif

	/* the following IPR registers are only defined for 802x3x and 83xx */	
	#ifdef INTC_IPR5_INIT
	periphMemWrite(INTC_IPR5_INIT,&pIntcBase->ipr[5]);
	#endif
	#ifdef INTC_IPR6_INIT
	periphMemWrite(INTC_IPR6_INIT,&pIntcBase->ipr[6]);
	#endif
	
	/* the following IPR registers are only defined for 83xx */	
	#ifdef INTC_IPR7_INIT
	periphMemWrite(INTC_IPR7_INIT,&pIntcBase->ipr[7]);
	#endif
	#ifdef INTC_IPR8_INIT
	periphMemWrite(INTC_IPR8_INIT,&pIntcBase->ipr[8]);
	#endif
	#ifdef INTC_IPR9_INIT
	periphMemWrite(INTC_IPR9_INIT,&pIntcBase->ipr[9]);
	#endif
	
	/* IPR10 is only available on 836x */	
	#ifdef INTC_IPR10_INIT
	periphMemWrite(INTC_IPR10_INIT,&pIntcBase->ipr10);
	#endif

	/* fast interrupt 0 handler */
	#ifdef INTC_FIVA0_INIT
	periphMemWrite((UWord16) (((UWord32)INTC_FIVA0_INIT) >> 16),&pIntcBase->fivah0);
	periphMemWrite((UWord16) (((UWord32)INTC_FIVA0_INIT) & 0xffff),&pIntcBase->fival0);
	#endif

	/* fast interrupt 0 match register (must be non-zero) */
	#if INTC_FIM0_INIT
	
		/* verify whether it is at level 2 */
		#define INT_PRIORITY_LEVEL_FASTINT0 _CAT(INT_PRIORITY_LEVEL_, INTC_FIM0_INIT)
		#if INT_PRIORITY_LEVEL_FASTINT0 != INTC_LEVEL2
		#warning Fast interrupt 0 must be preset to priority level 2 (check your INT_PRIORITY_LEVEL_n setting)
		#endif
		
		periphMemWrite((UWord16) INTC_FIM0_INIT,&pIntcBase->fim0);
		
	#endif

	/* fast interrupt 1 handler */
	#ifdef INTC_FIVA1_INIT
	periphMemWrite((UWord16) (((UWord32)INTC_FIVA1_INIT) >> 16),&pIntcBase->fivah1);
	periphMemWrite((UWord16) (((UWord32)INTC_FIVA1_INIT) & 0xffff),&pIntcBase->fival1);
	#endif

	/* fast interrupt 1 match register (must be non-zero) */
	#if INTC_FIM1_INIT
	
		/* verify whether it is at level 2 */
		#define INT_PRIORITY_LEVEL_FASTINT1 _CAT(INT_PRIORITY_LEVEL_, INTC_FIM1_INIT)
		#if INT_PRIORITY_LEVEL_FASTINT1 != INTC_LEVEL2
		#warning Fast interrupt 1 must be preset to priority level 2 (check your INT_PRIORITY_LEVEL_n setting)
		#endif

		periphMemWrite((UWord16) INTC_FIM1_INIT,&pIntcBase->fim1);
		
	#endif

}

/* this function gets invoked if an invalid IPL is being assigned to an interrupt source */

void INTC_InvalidIPL(UWord16 nInterruptNumber, UWord16 nRequestedLevel)
{
    #pragma unused (nInterruptNumber)
    #pragma unused (nRequestedLevel)

	/* in case your code stops here in the debugger, you have 
	   tried to set an invalid interrupt level */
	archDebugHalt();
}

#ifdef __cplusplus
}
#endif
