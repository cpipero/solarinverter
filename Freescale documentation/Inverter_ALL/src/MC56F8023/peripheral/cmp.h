/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  cmp.h
*
* $Date:      Feb-15-2007$
*
* $Version:   2.3.7.0$
*
* Description: Header file for the CMP driver
*
*******************************************************************************/

#ifndef __CMP_H
#define __CMP_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before cmp.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The comparator (CMP) includes a digital control interface and an analog 
* comparator module. The analog comparator also includes a five-input analog 
* switching matrix with the continuous-time differential-input analog
* comparator function. The five analog inputs include three GPIO (referred 
* to as CIN1, CIN2, and CIN3), a CMP input, and an import input from another 
* comparator module. The switching matrix supports the independent connection
* of the analog inputs to the + and – input of the analog comparator and to the 
* comparator’s export output. 
*
******************************************************************************/

/************************************************************
* CMP module identifiers
*************************************************************/

#ifdef CMPA_BASE
#define CMP_A (&ArchIO.CmpA)
#endif
#ifdef CMPB_BASE
#define CMP_B (&ArchIO.CmpB)
#endif

/*************************************************************
* arch.h should define device-specific information about CMP
**************************************************************/

#if !defined(CMP_VERSION)
#error CMP not properly described in arch.h
#endif

/****************************************************
* Configurable items, i.e. defines for appconfig.h
*****************************************************

  #define CMP_x_CTRL_INIT
  #define CMP_x_FILT_INIT

  #define INTERRUPT_VECTOR_ADDR_yy  userISR  //specify interrupt handler routine : e.g. cmpaISR
  #define INT_PRIORITY_LEVEL_yy     INTC_xxx // interrupt level : (INTC_DISABLED, INTC_LEVEL0,
                                             //                    INTC_LEVEL1 or INTC_LEVEL2)
  where:
         yy  is interrupt vector number
            e.g. On 56F8037
                53 - CMP_A comparator interrupt

*/

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl( CMP_n, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                      PARAMETERS, COMMENTS
--------------------------------------------------------*/

#define CMP_INIT                   /* NULL */
#define CMP_MODULE                 /* CMP_ENABLE/CMP_DISABLE, enable/disable comparator module */
#define CMP_INVERT                 /* CMP_ENABLE/CMP_DISABLE, enable inverter on output */
#define CMP_SELECT_POS_INPUT       /* CMP_CINx/CMP_DAC/CMP_IMPORT, select positive CMP input */
#define CMP_SELECT_NEG_INPUT       /* CMP_CINx/CMP_DAC/CMP_IMPORT, select negative CMP input */
#define CMP_SELECT_EXPORT_OUTPUT   /* CMP_CINx/CMP_DAC, select CMP export output */
#define CMP_INT_ENABLE             /* CMP_RISING_EDGE|CMP_FALLING_EDGE, enable interrupt(s) */
#define CMP_INT_DISABLE            /* CMP_RISING_EDGE|CMP_FALLING_EDGE, enable interrupt(s) */
#define CMP_READ_INT_FLAGS         /* NULL, returns CMP_RISING_EDGE|CMP_FALLING_EDGE */
#define CMP_CLEAR_INT_FLAGS        /* UWord16 value read by CMP_READ_INT_FLAGS, Clears CMP interrupt flags */     
#define CMP_READ_OUTPUT            /* NULL, returns zero/nonzero current comparator state */
#define CMP_READ_FILT_REG          /* NULL, returns value of fiter register */
#define CMP_WRITE_FILT_REG         /* UWord16, writes filter register */

/*****************************************************************************
* CMP ioctl command parameters 
******************************************************************************/

#define CMP_ENABLE      1
#define CMP_DISABLE     0

#define CMP_CIN0        0
#define CMP_CIN1        1
#define CMP_CIN2        2
#define CMP_DAC         3
#define CMP_IMPORT      4

#define CMP_RISING_EDGE   CMP_STAT_RC
#define CMP_FALLING_EDGE  CMP_STAT_FC

/****************************************************************************
* register and bit names used in the ioctl functions below
*****************************************************************************/

/* CMP Control register */

#define CMP_CTRL_RCIE         0x8000
#define CMP_CTRL_FCIE         0x4000
#define CMP_CTRL_ESEL_MASK    0x0c00
#define CMP_CTRL_ESEL_CIN1    0x0000
#define CMP_CTRL_ESEL_CIN2    0x0400
#define CMP_CTRL_ESEL_CIN3    0x0800
#define CMP_CTRL_ESEL_DAC     0x0c00
#define CMP_CTRL_NSEL_MASK    0x01c0
#define CMP_CTRL_NSEL_CIN1    0x0000
#define CMP_CTRL_NSEL_CIN2    0x0040
#define CMP_CTRL_NSEL_CIN3    0x0080
#define CMP_CTRL_NSEL_DAC     0x00c0
#define CMP_CTRL_NSEL_IMPORT  0x0100
#define CMP_CTRL_PSEL_MASK    0x001c
#define CMP_CTRL_PSEL_CIN1    0x0000
#define CMP_CTRL_PSEL_CIN2    0x0004
#define CMP_CTRL_PSEL_CIN3    0x0008
#define CMP_CTRL_PSEL_DAC     0x000c
#define CMP_CTRL_PSEL_IMPORT  0x0010
#define CMP_CTRL_INV          0x0002
#define CMP_CTRL_PDN          0x0001

/* CMP Status register */

#define CMP_STAT_RC           0x8000
#define CMP_STAT_FC           0x4000
#define CMP_STAT_COUT         0x0001

/* CMP Filter register */

#define CMP_FILT_CNT_MASK     0x0700
#define CMP_FILT_PER_MASK     0x00ff

/****************************************************************************
* CMP ioctl macro implementation
*****************************************************************************/

/***********************************************************************
* CMP init
***********************************************************************/

void cmpInit(arch_sCMP *pCmpBase);
#define ioctlCMP_INIT(pCmpBase, param) cmpInit(pCmpBase)

/***********************************************************************
* CMP control register
***********************************************************************/

/* Enable/Disable CMP module */
#define ioctlCMP_MODULE(pCmpBase, param) \
  if (param) periphBitClear(CMP_CTRL_PDN, &((pCmpBase)->ctrl)); \
  else periphBitSet(CMP_CTRL_PDN, &((pCmpBase)->ctrl))

#define ioctlCMP_INVERT(pCmpBase, param) \
  if (param) periphBitSet(CMP_CTRL_INV, &((pCmpBase)->ctrl)); \
  else periphBitClear(CMP_CTRL_INV, &((pCmpBase)->ctrl))

/* select positive CMP input */
#define ioctlCMP_SELECT_POS_INPUT(pCmpBase, param) \
  periphBitGrpSet(CMP_CTRL_PSEL_MASK, (param) << 2,  &((pCmpBase)->ctrl))

/* select negative CMP input */
#define ioctlCMP_SELECT_NEG_INPUT(pCmpBase, param) \
  periphBitGrpSet(CMP_CTRL_NSEL_MASK, (param) << 6,  &((pCmpBase)->ctrl))

/* select export output */
#define ioctlCMP_SELECT_EXPORT_OUTPUT(pCmpBase, param) \
  periphBitGrpSet(CMP_CTRL_ESEL_MASK, (param) << 10,  &((pCmpBase)->ctrl))

/* enable interrupts */
#define ioctlCMP_INT_ENABLE(pCmpBase, param) \
  periphBitSet((param) & (CMP_CTRL_RCIE | CMP_CTRL_FCIE),  &((pCmpBase)->ctrl))

/* disable interrupts */
#define ioctlCMP_INT_DISABLE(pCmpBase, param) \
  periphBitClear((param) & (CMP_CTRL_RCIE | CMP_CTRL_FCIE),  &((pCmpBase)->ctrl))

/***********************************************************************
* CMP control register
***********************************************************************/

/* disable interrupts */
#define ioctlCMP_READ_INT_FLAGS(pCmpBase, param) \
  periphBitTest(CMP_STAT_RC | CMP_STAT_FC,  &((pCmpBase)->stat))

/* clear interrupts */
#define ioctlCMP_CLEAR_INT_FLAGS(pCmpBase, param) \
  periphMemWrite((param) & (CMP_STAT_RC | CMP_STAT_FC),  &((pCmpBase)->stat))

#define ioctlCMP_READ_OUTPUT(pCmpBase, param) \
  periphBitTest(CMP_STAT_COUT, &((pCmpBase)->stat))

/***********************************************************************
* CMP filter register
***********************************************************************/

#define ioctlCMP_READ_FILT_REG(pCmpBase, param) \
  periphMemRead(&((pCmpBase)->filt))
  
#define ioctlCMP_WRITE_FILT_REG(pCmpBase, param) \
  periphMemWrite(param,  &((pCmpBase)->filt))

#ifdef __cplusplus
}
#endif

#endif                                      
