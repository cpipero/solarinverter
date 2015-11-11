/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  pit.h
*
* $Date:      May-4-2009$
*
* $Version:   2.3.10.0$
*
* Description: Header file for the PIT driver
*
* HSCMP_VERSION_1 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*                    56F800x devices, see MC56F80006RM.pdf
* 
*******************************************************************************/

#ifndef __PIT_H
#define __PIT_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before pit.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Programmable Interval Timer (PIT) module contains a 16-bit up counter, 
* a modulo register and a control register. The modulo and control registers 
* are read/writable. The counter is read only.
*
* The modulo register is loaded with a value to count to and the prescaler is 
* set to determine the counting rate. When enabled, the counter counts up to 
* the modulo value and sets a flag (and an interrupt request if enabled), 
* resets to $0000, and resumes counting.
*
******************************************************************************/

/************************************************************
* PIT module identifiers
*************************************************************/

#ifdef PIT_BASE
#define PIT (&ArchIO.Pit)
#endif
#ifdef PIT0_BASE
#define PIT_0 (&ArchIO.Pit0)
#endif
#ifdef PIT1_BASE
#define PIT_1 (&ArchIO.Pit1)
#endif
#ifdef PIT2_BASE
#define PIT_2 (&ArchIO.Pit2)
#endif

/*************************************************************
* arch.h should define device-specific information about PIT
**************************************************************/

#if !defined(PIT_VERSION)
#error PIT not properly described in arch.h
#endif

/****************************************************
* Configurable items, i.e. defines for appconfig.h
*****************************************************

  #define PIT_CTRL_INIT 
  #define PIT_MOD_INIT  

  #define INTERRUPT_VECTOR_ADDR_yy  userISR  //specify interrupt handler routine : e.g. pit0ISR
  #define INT_PRIORITY_LEVEL_yy     INTC_xxx // interrupt level : (INTC_DISABLED, INTC_LEVEL0,
                                             //                    INTC_LEVEL1 or INTC_LEVEL2)
  where:
         yy  is interrupt vector number
            e.g. On 56F8037
                55 - PIT_0 rollover interrupt

*/

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl( PIT_n, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                      PARAMETERS, COMMENTS
--------------------------------------------------------*/

#define PIT_INIT                   /* NULL */
#define PIT_COUNTER                /* PIT_ENABLE/PIT_DISABLE, enable/disable counter */     
#define PIT_SLAVE_MODE             /* PIT_ENABLE/PIT_DISABLE, enable/disable slave mode */     
#define PIT_ROLLOVER_INT           /* PIT_ENABLE/PIT_DISABLE, enable/disable PIT interrupt */     
#define PIT_CLEAR_ROLLOVER_INT     /* NULL, Clear PIT interrupt flag */     
#define PIT_SET_PRESCALER          /* PIT_PRESCALER_xxx, set PIT prescaler */     

#define PIT_WRITE_MODULO_REG       /* UWord16, sets modulo value */     
#define PIT_READ_MODULO_REG        /* NULL, returns modulo value */     
#define PIT_READ_COUNTER_REG       /* NULL, returns UWord16 counter value */     

/***********************************************************************************************************
** PIT PARAMETERS DEFINITION                                                                        **
***********************************************************************************************************/

#define PIT_ENABLE            1
#define PIT_DISABLE           0

/* PIT_SET_PRESCALER arguments */
#define PIT_PRESCALER_1       PIT_CTRL_PRESCALER_DIV1     
#define PIT_PRESCALER_2       PIT_CTRL_PRESCALER_DIV2     
#define PIT_PRESCALER_4       PIT_CTRL_PRESCALER_DIV4     
#define PIT_PRESCALER_8       PIT_CTRL_PRESCALER_DIV8     
#define PIT_PRESCALER_16      PIT_CTRL_PRESCALER_DIV16    
#define PIT_PRESCALER_32      PIT_CTRL_PRESCALER_DIV32    
#define PIT_PRESCALER_64      PIT_CTRL_PRESCALER_DIV64    
#define PIT_PRESCALER_128     PIT_CTRL_PRESCALER_DIV128   
#define PIT_PRESCALER_256     PIT_CTRL_PRESCALER_DIV256   
#define PIT_PRESCALER_512     PIT_CTRL_PRESCALER_DIV512   
#define PIT_PRESCALER_1024    PIT_CTRL_PRESCALER_DIV1024  
#define PIT_PRESCALER_2048    PIT_CTRL_PRESCALER_DIV2048  
#define PIT_PRESCALER_4096    PIT_CTRL_PRESCALER_DIV4096  
#define PIT_PRESCALER_8192    PIT_CTRL_PRESCALER_DIV8192  
#define PIT_PRESCALER_16384   PIT_CTRL_PRESCALER_DIV16384 
#define PIT_PRESCALER_32768   PIT_CTRL_PRESCALER_DIV32768 


/****************************************************************************
* register and bit names used in the ioctl functions below
*****************************************************************************/

/* CTRL register */
#define PIT_CTRL_SLAVE                0x8000
#define PIT_CTRL_PRESCALER_MASK       0x0078
#define PIT_CTRL_PRESCALER_DIV1       0x0000
#define PIT_CTRL_PRESCALER_DIV2       0x0008
#define PIT_CTRL_PRESCALER_DIV4       0x0010
#define PIT_CTRL_PRESCALER_DIV8       0x0018
#define PIT_CTRL_PRESCALER_DIV16      0x0020
#define PIT_CTRL_PRESCALER_DIV32      0x0028
#define PIT_CTRL_PRESCALER_DIV64      0x0030
#define PIT_CTRL_PRESCALER_DIV128     0x0038
#define PIT_CTRL_PRESCALER_DIV256     0x0040
#define PIT_CTRL_PRESCALER_DIV512     0x0048
#define PIT_CTRL_PRESCALER_DIV1024    0x0050
#define PIT_CTRL_PRESCALER_DIV2048    0x0058
#define PIT_CTRL_PRESCALER_DIV4096    0x0060
#define PIT_CTRL_PRESCALER_DIV8192    0x0068
#define PIT_CTRL_PRESCALER_DIV16384   0x0070
#define PIT_CTRL_PRESCALER_DIV32768   0x0078
#define PIT_CTRL_PRF                  0x0004
#define PIT_CTRL_PRIE                 0x0002
#define PIT_CTRL_CNT_EN               0x0001

/****************************************************************************
* PIT ioctl macro implementation
*****************************************************************************/

/* PIT init */

void pitInit(arch_sPIT *pPitBase);
#define ioctlPIT_INIT(pPitBase, param) pitInit(pPitBase)

/* PIT control register */

/* Enable/Disable PIT counter */
#define ioctlPIT_COUNTER(pPitBase, param) \
  if (param) periphBitSet(PIT_CTRL_CNT_EN, &((pPitBase)->ctrl)); \
  else periphBitClear(PIT_CTRL_CNT_EN, &((pPitBase)->ctrl))

/* Enable/Disable PIT slave mode */
#define ioctlPIT_SLAVE_MODE(pPitBase, param) \
  if (param) periphBitSet(PIT_CTRL_SLAVE, &((pPitBase)->ctrl)); \
  else periphBitClear(PIT_CTRL_SLAVE, &((pPitBase)->ctrl))

/* Enable/disable PIT interrupt */
#define ioctlPIT_ROLLOVER_INT(pPitBase, param) \
  if(param) periphBitSet(PIT_CTRL_PRIE, &((pPitBase)->ctrl)); \
  else periphBitClear(PIT_CTRL_PRIE, &((pPitBase)->ctrl))

/* Clear PIT interrupt */
#define ioctlPIT_CLEAR_ROLLOVER_INT(pPitBase, param) \
  periphBitClear(PIT_CTRL_PRF, &((pPitBase)->ctrl))

/* Set PIT prescaler */
#define ioctlPIT_SET_PRESCALER(pPitBase, param) \
  periphBitGrpSR(PIT_CTRL_PRESCALER_MASK, param, &((pPitBase)->ctrl))

/* PIT counter/modulo registers */

#define ioctlPIT_WRITE_MODULO_REG(pPitBase, param) \
  periphMemWrite(param, &((pPitBase)->mod))

#define ioctlPIT_READ_MODULO_REG(pPitBase, param) \
  periphMemRead(&((pPitBase)->mod))

#define ioctlPIT_READ_COUNTER_REG(pPitBase, param) \
  periphMemRead(&((pPitBase)->cntr))

#ifdef __cplusplus
}
#endif

#endif                                      
