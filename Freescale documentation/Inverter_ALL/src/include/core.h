/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: core.h$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.5.0$
*
* Description: Core-specific (architecture-specific) macros
*
******************************************************************************/

#ifndef __CORE_H
#define __CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef archEnableInt
/* In case this error is hit, your arch.h file is perhaps accessed in the old 
   version of the Quick_Start source tree. Please replace your arch.h file with 
   the one distributed with the latest version of Quick_Start */
#error Obsolete code in arch.h. Please upgrade your arch.h file
#endif

/**************************************************************
* standard Metrowerks intrinsics work well with Quick_Start
**************************************************************/

#ifdef __MWERKS__
#include <intrinsics_56800E.h>
#define ITU_INTRINSICS
#endif

/**************************************************************
* Architecture-specific macros used in Quick_Start apps
**************************************************************/

/* Get limit bit */
inline Word16 archGetLimitBit(void)
{
	register Word16 ret;
	asm {
		move.w SR,ret
		bfclr 0xffbf,ret
	}
	return ret;
}

/* Clear sticky limit bit */
#define archResetLimitBit() asm { bfclr #0x40,SR; nop; nop; }

/* clear saturation mode */
#define archSetNoSat() asm { bfclr #0x10,OMR; nop; nop; }

/* set saturation mode */
#define archSetSat32() asm { bfset #0x10,OMR; nop; nop; }

/* set saturation mode and return it previous value */
inline Word16 archGetSetSaturationMode (register bool bSatMode)
{
	register Word16 ret;
	asm {
		move.w OMR,ret
		bfclr 0xffef,ret
	}
	if(bSatMode)				/* using "if" enables compile-time optimization */
	{
		asm { bfset 0x10,OMR; nop; nop; }
	}
	else
	{
		asm { bfclr 0x10,OMR; nop; nop; }
	}
	return ret;	
}

/* Set two's-complement rounding */
#define archSet2CompRound() asm { bfset #0x20,OMR; nop; nop; }

/* Set convergent rounding */
#define archSetConvRound() asm { bfclr #0x20,OMR; nop; nop; }

/* STOP */
#define archStop() asm(STOP)

/* Software Interrupt */
#define archTrap() asm(SWI)

/* WAIT */
#define archWait() asm(WAIT)

/* Debug Halt */
#define archDebugHalt() asm(DEBUGHLT)

/* Enable Interrupts on certain levels */
#define archEnableInt() asm(bfclr #0x0300,SR)
#define archEnableIntLvl123() asm { bfset #0x0300,SR; bfclr #0x0200,SR }
#define archEnableIntLvl23()  asm { bfset #0x0300,SR; bfclr #0x0100,SR }

/* Disable Interrupts */
#define archDisableInt() asm { bfset #0x0300,SR; nop; nop; nop; nop; nop; nop }

/* Push SR on HWS and disable interrupts  */
#define archPushIntAndDisable() asm { moveu.w SR,HWS; nop; nop; bfset #0x0300,SR; nop; nop; nop; nop; nop }

/* Pop SR from HWS (renew the state before calling archPushIntAndDisable() */
#define archPopIntMask() asm { moveu.w HWS,SR }

/* Save SR into register (in C declare as "register UWord16")  */
#define archSaveIntAndDisable(intsave) asm { move.w SR,intsave; bfset #0x0300,SR; nop; nop; nop; nop; nop }

/* Restore SR from register */
#define archRestoreIntMask(intsave) asm { moveu.w intsave,SR }

inline void archDelay(register UWord16 ticks)
{
	asm { 
		nop
		nop
		do ticks,archDelay1
   		nop
archDelay1:
	}
}

/********************************************************
* Additional Intrinsics and operation primitives
********************************************************/

/* substitute for shl intrinsic - shift only in 1 direction !!!
   original shl() remain usable, for shifts by immediate number
   the original shl may be better
*/
inline Word16 shl2(register Word16 num, register Word16 shift)
{
	asm { asll.w shift,num }
	return num;
}

/* substitute for shr intrinsic - shift only in 1 direction !!!
   same situation as in shl2()
*/
inline Word16 shr2(register Word16 num, register Word16 shift)
{
	asm { asrr.w shift,num }
	return num;
}

/*  Primitives (impyuu, impysu)  */

inline UWord32 impyuu(register UWord16 unsigA, register UWord16 unsigB)
{
	register UWord32 l;
	asm {

		.iasm_reg2regsetcopyflag off
		
		move.w unsigA,A0
		move.w unsigB,B0
		Impyuu A0,B0,l		/* thanks to impyuu F0,F0,FFF, we can use 'l' as destination */
		
		.iasm_reg2regsetcopyflag on
	}
	return l;
}

inline Word32 impysu(register Word16 sigA, register UWord16 unsigB)
{
	register Word32 l;
	asm {
		.iasm_reg2regsetcopyflag off
		
		move.w sigA,A1
		move.w unsigB,B0
		Impysu A1,B0,Y		/* unlike impyuu, there is no impysu F0,F0,FFF (must use Y) */
		nop					/* let Y propagate through pipeline */
		
		.iasm_reg2regsetcopyflag on
		
		tfr Y,l				/* transfer Y to return register */
	}
	return l;
}

#ifdef __cplusplus
}
#endif

#endif

