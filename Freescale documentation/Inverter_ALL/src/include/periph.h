/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: periph.h$
*
* $Date:      Dec-2-2008$
*
* $Version:   2.3.35.0$
*
* Description: Definition of quick_start "ioctl" macro and other macros for 
*              peripheral memory space access
*
*****************************************************************************/

#ifndef __PERIPH_H
#define __PERIPH_H

/*
*  Beginning in Quick_Start version 2.1, the qs.h master header file can 
*  be used to include all other Quick_Start system headers (core.h, types.h, 
*  arch.h, periph.h and appconfig.h) 
*
*  core.h is included here in case the old application is being compiled
*/
#ifndef __CORE_H
#include "core.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************
* ioctl commands macro 
*******************************************************/
#define ioctl(fd,cmd,prm) ioctl##cmd((fd),(prm))

/*******************************************************
* read / write commands macro 
*******************************************************/
#define write(fd,mode,address,size) write_##fd##_##mode(address,size)
#define read(fd,mode,address,size)  read_##fd##_##mode(address,size)

/*******************************************************
* Routines for Peripheral Memory Access
********************************************************
*  Parameter usage:
*   addr - architecture structure field
*   mask - bit to manipulate
*   Data - 16 bit word to assign or access  
********************************************************/

/* set bits using the bfset instruction */
#define periphBitSet(mask, addr)   (*(addr) |= (mask))

/* clear bits using the bfclr instruction */
#define periphBitClear(mask, addr) (*(addr) &= ~(mask))

/* bit-group manipulation macros changed in v2.3, use this macro for compatibility mode */
#if PERIPH_V22_COMPAT

/* set group of bits using an accumulator */
#define periphBitGrpSet(grpmask, mask, addr) ( *(addr) = ( (*(addr) & ~(grpmask)) | (mask)) )

/* Clear controls bit in register with flags which are cleared-by-write-one */
#define periphSafeBitClear(allFlagsBitsGrp, bitsToClear, addr) ( *(addr) = ( *(addr) & ~((bitsToClear) | (allFlagsBitsGrp)) ) )

/* Set controls bit in register with flags which are cleared-by-write-one */
#define periphSafeBitSet(allFlagsBitsGrp, bitsToSet, addr) ( *(addr) = ( (*(addr) & ~(bitsToClear)) | (allFlagsBitsGrp) )

/* set group of bits using an accumulator and clear flags which are cleared-by-write-one */
#define periphSafeBitGrpSet(allFlagsBitsGrp,grpmask, mask, addr) ( *(addr) = ( (*(addr) & ~((grpmask) | (allFlagsBitsGrp))) | (mask)) )

/* set group of bits using two non-interruptible instructions (first set ones, then reset zeroes) */
#define periphBitGrpSR(grpmask, mask, addr) \
	( (*(addr) |= ((mask) & (grpmask))) , (*(addr) &= ~((~(mask)) & (grpmask))) )

/* set group of bits using two non-interruptible instructions (first reset zeroes, then set ones) */
#define periphBitGrpRS(grpmask, mask, addr) \
	( (*(addr) &= ~((~(mask)) & (grpmask))) , (*(addr) |= ((mask) & (grpmask))) )

/* set group of bits using two non-interruptible instructions (first zero all group, then set ones) */
#define periphBitGrpZS(grpmask, mask, addr) \
	( (*(addr) &= ~(grpmask)) , ( *(addr) |= ((mask) & (grpmask))) )

#else

/* Note: begining in version 2.3, the bit-manipulation macros re-cast
   the target location to non-volatile, so the "void" instructions may
   be optimized-out from SR, RZ and ZS macros. Example of "void" are 
   bfset #0,X:(addr) or bfclr #0,X:(addr) which may be produced when 
   clearing or setting all bits in the bit-group */
                                        
/* set group of bits using an accumulator */
#define periphBitGrpSet(grpmask, mask, addr) { \
    register UWord16 __tmp = *(addr); \
    __tmp |= ((mask) & (grpmask)); \
    __tmp &= ~((~(mask)) & (grpmask)); \
    *(addr) = __tmp; \
    }

/* set group of bits using two non-interruptible instructions (first set ones, then reset zeroes) */
#define periphBitGrpSR(grpmask, mask, addr) \
	( (*(UWord16*)(addr) |= ((mask) & (grpmask))) , (*(UWord16*)(addr) &= ~((~(mask)) & (grpmask))) )

/* set group of bits using two non-interruptible instructions (first reset zeroes, then set ones) */
#define periphBitGrpRS(grpmask, mask, addr) \
	( (*(UWord16*)(addr) &= ~((~(mask)) & (grpmask))) , (*(UWord16*)(addr) |= ((mask) & (grpmask))) )

/* set group of bits using two non-interruptible instructions (first zero whole group, then set ones) */
#define periphBitGrpZS(grpmask, mask, addr) \
	( (*(UWord16*)(addr) &= ~(grpmask)) , ( *(UWord16*)(addr) |= ((mask) & (grpmask))) )


/* Clear controls bit in register with flags which are cleared-by-write-one */
#define periphSafeBitClear(allFlagsBitsGrp, bitsToClear, addr) \
	( 	periphBitClear( (allFlagsBitsGrp) | (bitsToClear), addr)  )

/* Set controls bit in register with flags which are cleared-by-write-one */
#define periphSafeBitSet(allFlagsBitsGrp, bitsToSet, addr) { \
    register UWord16 __tmp = *(addr); \
    __tmp |= ( bitsToSet ); \
    __tmp &= ~(allFlagsBitsGrp); \
    *(addr) = __tmp; \
    }

/* set group of bits using an accumulator and clear flags which are cleared-by-write-one */
#define periphSafeBitGrpSet(allFlagsBitsGrp,grpmask, mask, addr) { \
    register UWord16 __tmp = *(addr); \
    __tmp |= ( (mask) & ((allFlagsBitsGrp) | (grpmask)) ); \
    __tmp &= ~( (~(mask)) & ((allFlagsBitsGrp) | (grpmask)) ); \
    *(addr) = __tmp; \
    }


#endif /* PERIPH_V22_COMPAT */

/* clear (acknowlege) bit flags which are active-high and are cleared-by-write-one */
#define periphSafeAckByOne(allAckBitsGrp, bitsToAck, addr) \
	( ((~(bitsToAck)) & (allAckBitsGrp)) ? \
		(periphBitClear((~(bitsToAck)) & (allAckBitsGrp), addr)) : \
		(periphMemDummyReadWrite(addr),0) )

/* toggle bits using a bfchg instruction */
#define periphBitChange(mask, addr)     (*(addr) ^= (mask))

/* filter bits */
#define periphBitTest(mask, addr)       (*(addr) & (mask))

/* void periphMemInvBitSet(UWord16 mask, volatile UWord16 * addr); */
#define periphMemInvBitSet(mask, addr)   (*(addr) = (mask) | ~(*(addr)))

/* read peripheral memory space */
#define periphMemRead(addr) (*(addr))

/* write peripheral memory space */
#define periphMemWrite(data, addr) (*(addr) = (data))

/* a direct address is read and then overwritten with the value read */
inline void periphMemDummyReadWrite(register volatile UWord16* addr) 
{
	asm ( bfset #0, X:(addr) );
}

/* a direct address read, result is thrown away */
inline void periphMemDummyRead(register volatile UWord16* addr)
{
	register UWord16 reg;
	asm { move.w X:(addr),reg }
}

/* a direct address read, never optimized out (even if result is not used) */
inline UWord16 periphMemForcedRead(register volatile UWord16* addr)
{
	register UWord16 reg;
	asm { move.w X:(addr),reg }
	return reg;
}

#ifdef __cplusplus
}
#endif

#endif

