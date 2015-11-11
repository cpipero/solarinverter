/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  dac.h
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.8.0$
*
* Description: Header file for the DAC driver
*
*******************************************************************************/

#ifndef __DAC_H
#define __DAC_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before dac.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Programmable Interval Timer (DAC) module contains a 16-bit up counter, 
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
* DAC module identifiers
*************************************************************/

#ifdef DAC0_BASE
#define DAC_0 (&ArchIO.Dac0)
#endif
#ifdef DAC1_BASE
#define DAC_1 (&ArchIO.Dac1)
#endif

/*************************************************************
* arch.h should define device-specific information about DAC
**************************************************************/

#if !defined(DAC_VERSION)
#error DAC not properly described in arch.h
#endif

/****************************************************
* Configurable items, i.e. defines for appconfig.h
*****************************************************

  #define DAC_x_CTRL_INIT 
  #define DAC_x_DATA_INIT 
  #define DAC_x_STEP_INIT
  #define DAC_x_MAXVAL_INIT
  #define DAC_x_MINVAL_INIT

*/

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl( DAC_n, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                      PARAMETERS, COMMENTS
--------------------------------------------------------*/

#define DAC_INIT                    /* NULL */
#define DAC_MODULE                  /* DAC_ENABLE/DAC_DISABLE */
#define DAC_SET_DATA_FORMAT         /* DAC_xxx_ALIGNED_FMT */
#define DAC_SET_SYNC_SOURCE         /* DAC_xxx_SOURCE */
#define DAC_SET_AUTO_MODE           /* DAC_AUTO_xxx */
#define DAC_ENABLE_FILTER           /* UWord16 value 1-7, 0 causes filter 7 */
#define DAC_DISABLE_FILTER          /* NULL */

#define DAC_WRITE_CONTROL_REG      /* UWord16 */
#define DAC_READ_CONTROL_REG       /* NULL */

#define DAC_WRITE_DATA             /* UWord16 */
#define DAC_READ_DATA              /* NULL */
#define DAC_WRITE_STEP             /* UWord16 */
#define DAC_READ_STEP              /* NULL */
#define DAC_WRITE_MINVAL           /* UWord16 */
#define DAC_READ_MINVAL            /* NULL */
#define DAC_WRITE_MAXVAL           /* UWord16 */
#define DAC_READ_MAXVAL            /* NULL */

/***********************************************************************************************************
** DAC PARAMETERS DEFINITION                                                                        **
***********************************************************************************************************/

#define DAC_ENABLE               1
#define DAC_DISABLE              0

#define DAC_RIGHT_ALIGNED_FMT    0
#define DAC_LEFT_ALIGNED_FMT     1   

#define DAC_IPBUS_SOURCE         0
#define DAC_SYNCIN_SOURCE        1

#define DAC_AUTO_OFF             0
#define DAC_AUTO_SAWTOOTH1       (DAC_CTRL_AUTO | DAC_CTRL_UP)
#define DAC_AUTO_SAWTOOTH2       (DAC_CTRL_AUTO | DAC_CTRL_DOWN)
#define DAC_AUTO_TRIANGLE        (DAC_CTRL_AUTO | DAC_CTRL_UP | DAC_CTRL_DOWN)

/****************************************************************************
* register and bit names used in the ioctl functions below
*****************************************************************************/

/* CTRL register */
#define DAC_CTRL_FILT_CNT_MASK   0xe000
#define DAC_CTRL_FILT_EN         0x1000
#define DAC_CTRL_UP              0x0020
#define DAC_CTRL_DOWN            0x0010
#define DAC_CTRL_AUTO            0x0008
#define DAC_CTRL_SYNC_EN         0x0004
#define DAC_CTRL_FORMAT          0x0002
#define DAC_CTRL_PDN             0x0001

/****************************************************************************
* DAC ioctl macro implementation
*****************************************************************************/

/* DAC init */

void dacInit(arch_sDAC *pDacBase);
#define ioctlDAC_INIT(pDacBase, param) dacInit(pDacBase)

/* DAC control register */

#define ioctlDAC_MODULE(pDacBase, param) \
  if (param) periphBitClear(DAC_CTRL_PDN, &((pDacBase)->ctrl)); \
  else periphBitSet(DAC_CTRL_PDN, &((pDacBase)->ctrl))

#define ioctlDAC_SET_DATA_FORMAT(pDacBase, param) \
  if (param) periphBitSet(DAC_CTRL_FORMAT, &((pDacBase)->ctrl)); \
  else periphBitClear(DAC_CTRL_FORMAT, &((pDacBase)->ctrl))
  
#define ioctlDAC_SET_SYNC_SOURCE(pDacBase, param) \
  if (param) periphBitSet(DAC_CTRL_SYNC_EN, &((pDacBase)->ctrl)); \
  else periphBitClear(DAC_CTRL_SYNC_EN, &((pDacBase)->ctrl))
  
#define ioctlDAC_SET_AUTO_MODE(pDacBase, param) \
  periphBitGrpSet(DAC_CTRL_AUTO | DAC_CTRL_UP | DAC_CTRL_DOWN, \
    param, &((pDacBase)->ctrl))

#define ioctlDAC_ENABLE_FILTER(pDacBase, param) \
  if(param) periphBitGrpRS(DAC_CTRL_FILT_CNT_MASK | DAC_CTRL_FILT_EN, \
    DAC_CTRL_FILT_EN | ((UWord16)(param)) << 13, &((pDacBase)->ctrl)); \
  else periphBitSet(DAC_CTRL_FILT_CNT_MASK | DAC_CTRL_FILT_EN, &((pDacBase)->ctrl))

#define ioctlDAC_DISABLE_FILTER(pDacBase, param) \
  periphBitClear(DAC_CTRL_FILT_CNT_MASK | DAC_CTRL_FILT_EN, &((pDacBase)->ctrl))

#define ioctlDAC_WRITE_CONTROL_REG(pDacBase, param) \
  periphMemWrite(param, &((pDacBase)->ctrl))

#define ioctlDAC_READ_CONTROL_REG(pDacBase, param) \
  periphMemRead(&((pDacBase)->ctrl))

/* DAC data register */

#define ioctlDAC_WRITE_DATA(pDacBase, param) \
  periphMemWrite(param, &((pDacBase)->data))

#define ioctlDAC_READ_DATA(pDacBase, param) \
  periphMemRead(&((pDacBase)->data))

/* DAC auto-mode registers */

#define ioctlDAC_WRITE_STEP(pDacBase, param) \
  periphMemWrite(param, &((pDacBase)->step))

#define ioctlDAC_READ_STEP(pDacBase, param) \
  periphMemRead(&((pDacBase)->step))

#define ioctlDAC_WRITE_MINVAL(pDacBase, param) \
  periphMemWrite(param, &((pDacBase)->minval))

#define ioctlDAC_READ_MINVAL(pDacBase, param) \
  periphMemRead(&((pDacBase)->minval))

#define ioctlDAC_WRITE_MAXVAL(pDacBase, param) \
  periphMemWrite(param, &((pDacBase)->maxval))

#define ioctlDAC_READ_MAXVAL(pDacBase, param) \
  periphMemRead(&((pDacBase)->maxval))


#ifdef __cplusplus
}
#endif

#endif                                      
