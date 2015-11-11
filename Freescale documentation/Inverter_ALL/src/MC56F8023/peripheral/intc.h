/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  intc.h
*
* $Date:      Feb-12-2007$
*
* $Version:   2.3.27.0$
*
* Description: Header file for the Interrupt Controller driver
*
*******************************************************************************/

#ifndef __INTC_H
#define __INTC_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before intc.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
    ITCN module identifier, correspond to module base address
*******************************************************************************/

#define INTC        (&ArchIO.Intc)

/*************************************************************
* arch.h should define device-specific information about INTC
**************************************************************/

#if !defined(INTC_VERSION)
#error INTC not properly described in arch.h (old Quick_Start version?)
#endif

/*******************************************************************************
    Defines for appconfig.h
********************************************************************************/
/*  
    #define INT_VECTOR_ADDR_n       interrupt handler for interrupt n
    #define INT_PRIORITY_LEVEL_n    one of the INTC_DISABLED, INTC_LEVEL0, 
                                      INTC_LEVEL1, INTC_LEVEL2 or INTC_LEVEL3

    #define INTC_ICTL_INIT  // initial value of INTC Control Register

    #define INTC_FIM0_INIT  // initial value for Fast Interrupt Match register 0 (interrupt number 1-80)
    #define INTC_FIM1_INIT  // initial value for Fast Interrupt Match register 1 (interrupt number 1-80)

    #define INTC_FIVA0_INIT // [optional] addr of fast int. 0 handler 
                            //          - appropriate INT_VECTOR_ADDR_n used if this is not specified
    #define INTC_FIVA1_INIT // [optional] addr of fast int. 1 handler
                            //          - appropriate INT_VECTOR_ADDR_n used if this is not specified

*/

/*******************************************************************************
    ioctl() commands
********************************************************************************
 command                            parameters and commentary */

#define INTC_INIT                   /* initialize module */
#define INTC_INTERRUPTS             /* INTC_ENABLE, INTC_DISABLE */
#define INTC_SET_IPL_n              /* n = given interrupt, param is one of INTC_DISABLED or INTC_LEVELx */
#define INTC_SET_IPL_n_RAW          /* n = given interrupt, param is a two-bit IPL value in the IPR register */
#define INTC_GET_IPL_n_RAW          /* n = given interrupt, use NULL as param, return value is a two-bit IPL value */
#define INTC_SET_FASTINT0           /* interrupt number which is to be set as fast interrupt 0 */
#define INTC_SET_FASTINT0_VEC       /* fast interrupt 0 ISR handler address */
#define INTC_SET_FASTINT1           /* interrupt number which is to be set as fast interrupt 1 */
#define INTC_SET_FASTINT1_VEC       /* fast interrupt 1 ISR handler address  */
#define INTC_GET_PENDING_FLAG       /* interrupt number */

/* Note to reading ICTL register in interrupt handlers: the bits in register do not
   reflect the current processor state until the interrupt is acknowledged */
#define INTC_READ_CONTROL_REG       /* NULL, returns ICTL register */
#define INTC_GET_INT_STATE          /* NULL, returns nonzero if interrupt is being sent to core (ICTL_INT) */
#define INTC_GET_INT_LEVEL          /* NULL, returns current level of execution (ICTL_IPIC) */
#define INTC_GET_INT_NUMBER         /* NULL, returns number of currently processed interrupt (ICTL_VAB) */

/* IRQA and IRQB pins are not always both present of device (80xx has neither of them) */
#if INTC_HAS_IRQPINS
#define INTC_READ_IRQPINS           /* INTC_IRQA | INTC_IRQB, reads state of external interrupt pins */
#define INTC_SELECT_EDGE_MODE       /* INTC_IRQA | INTC_IRQB, sets interrupts to be an falling-edge-sensitive */
#define INTC_SELECT_LEVEL_MODE      /* INTC_IRQA | INTC_IRQB, sets interrupts to be an low-level-sensitive */
#endif

/*******************************************************************************
    command parameters
*******************************************************************************/

#define INTC_DISABLE    0
#define INTC_ENABLE     1

/* interrupt priority levels */
#define INTC_DISABLED   0
#define INTC_LEVEL0     1
#define INTC_LEVEL1     2
#define INTC_LEVEL2     3
#define INTC_LEVEL3     4

#if INTC_HAS_IRQPINS & 1
#define INTC_IRQA 1
#endif
#if INTC_HAS_IRQPINS & 2
#define INTC_IRQB 2
#endif

/*******************************************************************************
    register bit names and masks
*******************************************************************************/

/* INTC_ICTL */
#define INTC_ICTL_INT         0x8000
#define INTC_ICTL_IPIC_MASK   0x6000
#define INTC_ICTL_VAB_MASK    0x1fc0
#define INTC_ICTL_INTDIS      0x0020
#define INTC_ICTL_IRQBSTATE   0x0008
#define INTC_ICTL_IRQASTATE   0x0004
#define INTC_ICTL_IRQBEDG     0x0002
#define INTC_ICTL_IRQAEDG     0x0001

/*******************************************************************************
    Implementation
*******************************************************************************/

/* accessing the index, shift and mask value using a given interrupt number (constant) 
   see intctarget.h for actual IPR macro values for each individual interrupt */
#define INTC_IPR_INTn_INDEX(n) INTC_IPR_INT##n##_INDEX
#define INTC_IPR_INTn_SHIFT(n) INTC_IPR_INT##n##_SHIFT
#define INTC_IPR_INTn_MASK(n)  INTC_IPR_INT##n##_MASK

/* macros to determine what kind the given interrupt is (see intctarget.h for mask value) */
#define INTC_IS_IPL123_INT(n)   ( (1L<<(n)) & INTC_IPL123_INTS )

/* a code to execute when a user tries to set an invalid IPL */
void INTC_InvalidIPL(UWord16 nInterruptNumber, UWord16 nRequestedLevel);
#define INTC_INVALID_IPL(n,x)  ( INTC_InvalidIPL(n,x), 0 )

/* convert INTC_LEVELn to actual IPR register bits (interrupts with levels 0,1,2) */
#define INTC_GET_IPL012_BITS(n,x) \
    ( ((x) <= INTC_DISABLED) ? 0 : ( ((x) <= INTC_LEVEL2) ? (x) : INTC_INVALID_IPL(n,x) ) )

/* convert INTC_LEVELn to actual IPR register bits (interrupts with levels 1,2,3) */
#define INTC_GET_IPL123_BITS(n,x) \
    ( ((x) <= INTC_DISABLED) ? 0 : ( (((x) <= INTC_LEVEL3) && ((x) != INTC_LEVEL0)) ? ((x)-1) : INTC_INVALID_IPL(n,x) ) )

/* make the IPR value (IPL bits shifted to proper position) for a given interrupt */    
#define INTC_MAKE_IPR_VALUE(n,x) \
    ( (UWord16) (( INTC_IS_IPL123_INT(n) ? INTC_GET_IPL123_BITS(n,x) : INTC_GET_IPL012_BITS(n,x) ) << INTC_IPR_INTn_SHIFT(n)) )

/* generic macros which are to be reused by ioctl implementation for specific interrupt number */
#define INTC_SET_IPL123_n(n, pIntcBase, param) \
    periphBitGrpZS(INTC_IPR_INTn_MASK(n), INTC_GET_IPL123_BITS(n,param) << INTC_IPR_INTn_SHIFT(n), \
        &pIntcBase->ipr[INTC_IPR_INTn_INDEX(n)])

#define INTC_SET_IPL012_n(n, pIntcBase, param) \
    periphBitGrpZS(INTC_IPR_INTn_MASK(n), INTC_GET_IPL012_BITS(n,param) << INTC_IPR_INTn_SHIFT(n), \
        &pIntcBase->ipr[INTC_IPR_INTn_INDEX(n)])

#define INTC_SET_IPLRAW_n(n, pIntcBase, param) \
    periphBitGrpZS(INTC_IPR_INTn_MASK(n), (param) << INTC_IPR_INTn_SHIFT(n), \
        &pIntcBase->ipr[INTC_IPR_INTn_INDEX(n)])

#define INTC_GET_IPLRAW_n(n, pIntcBase) \
    ( (periphMemRead(&(pIntcBase)->ipr[INTC_IPR_INTn_INDEX(n)]) & INTC_IPR_INTn_MASK(n)) >> INTC_IPR_INTn_SHIFT(n) )


/*******************************************************************************
    fast interrupt ISR prototypes
*******************************************************************************/

#ifdef INTC_FIVA0_INIT
void INTC_FIVA0_INIT(void);
#endif
#ifdef INTC_FIVA1_INIT
void INTC_FIVA1_INIT(void);
#endif

/*******************************************************************************
    ioctl Implementation
*******************************************************************************/

void intcInit(arch_sIntc *pIntcBase);
#define ioctlINTC_INIT(pIntcBase, param) intcInit(pIntcBase)

#define ioctlINTC_SET_FASTINT0(pIntcBase, param)    \
  periphMemWrite(param, &((pIntcBase)->fim0))

#define ioctlINTC_SET_FASTINT0_VEC(pIntcBase, param)    \
  { periphMemWrite((UWord16)(((UWord32)(param)) & 0xffff), &((pIntcBase)->fival0)); \
    periphMemWrite((UWord16)(((UWord32)(param)) >> 16), &((pIntcBase)->fivah0)); } 

#define ioctlINTC_SET_FASTINT1(pIntcBase, param)    \
  periphMemWrite(param, &((pIntcBase)->fim1))

#define ioctlINTC_SET_FASTINT1_VEC(pIntcBase, param)    \
  { periphMemWrite((UWord16)(((UWord32)(param)) & 0xffff), &((pIntcBase)->fival1)); \
    periphMemWrite((UWord16)(((UWord32)(param)) >> 16), &((pIntcBase)->fivah1)); } 

#define ioctlINTC_GET_PENDING_FLAG(pIntcBase, param)    \
  periphBitTest(1<<(((param)-1)%16), &((pIntcBase)->irqp[((param)-1)/16]))

#define ioctlINTC_READ_CONTROL_REG(pIntcBase, param)    \
  periphMemRead(&((pIntcBase)->ictl))

#define ioctlINTC_GET_INT_STATE(pIntcBase, param)   \
  periphBitTest(INTC_ICTL_INT, &((pIntcBase)->ictl))
     
#define ioctlINTC_GET_INT_LEVEL(pIntcBase, param)   \
  ( periphBitTest(INTC_ICTL_IPIC_MASK, &((pIntcBase)->ictl)) >> 13 )
     
#define ioctlINTC_GET_INT_NUMBER(pIntcBase, param)  \
  ( periphBitTest(INTC_ICTL_VAB_MASK, &((pIntcBase)->ictl)) >> 6 )

#define ioctlINTC_INTERRUPTS(pIntcBase, param)  \
  if(param) periphBitClear(INTC_ICTL_INTDIS, &((pIntcBase)->ictl)); \
  else periphBitSet(INTC_ICTL_INTDIS, &((pIntcBase)->ictl))

#ifdef INTC_READ_IRQPINS
#define ioctlINTC_READ_IRQPINS(pIntcBase, param)    \
  (periphBitTest(INTC_ICTL_IRQASTATE | INTC_ICTL_IRQBSTATE, &((pIntcBase)->ictl)) >> 2)
#endif

#ifdef INTC_SELECT_EDGE_MODE
#define ioctlINTC_SELECT_EDGE_MODE(pIntcBase, param)    \
  periphBitSet(param, &((pIntcBase)->ictl))
#endif

#ifdef INTC_SELECT_LEVEL_MODE
#define ioctlINTC_SELECT_LEVEL_MODE(pIntcBase, param)   \
  periphBitClear(param, &((pIntcBase)->ictl))
#endif
     
/* device-dependent Interrupt Controller settings */
#include "intctarget.h"

#ifdef __cplusplus
}
#endif

#endif

