/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  cop.h
*
* $Date:      Mar-23-2009$
*
* $Version:   2.3.28.0$
*
* Description: Header file for COP (Computer Operating Properly - Watchdog) 
*              low-level driver 
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  COP_VERSION_1 .. 56F83xx and 56F801x devices, see MC56F8300UM.pdf, MC56F8000RM.pdf
*  COP_VERSION_2 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  COP_VERSION_3 .. 56F800x devices, see MC56F800xRM.pdf
*
*****************************************************************************/

#ifndef __COP_H
#define __COP_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before cop.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
* COP module identifier, corresponds to module base address
*************************************************************/

#define COP (&ArchIO.Cop)

/*************************************************************
* arch.h should define device-specific information about COP
**************************************************************/

#if !defined(COP_VERSION)
#error COP not properly described in arch.h (old Quick_Start version?)
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Computer Operating Properly (COP) module is used to help software recover
* from runaway code. The COP is a free-running down counter once enabled is
* designed to generate a reset when reaching zero. Software must periodically
* service the COP to clear the counter and prevent a reset.
*
* For more information, please refer to the user manual for the particular
* chip that you are using, such as the MC56F8300 Peripheral Manual,
* for a description of the COP device.
*
* The COP device driver interface uses "ioctl" call to control specific
* COP functions during operation. For details see "ioctl" call.
*
******************************************************************************/

/***********************************************************************
* COP static configuration items for appconfig.h
***********************************************************************/
/*
    #define COP_COPCTL_INIT 0x0002
anguila white:
    #define COP_COPCTL_INIT 0x0302
    #define COP_COPTO_INIT  0xFFFF

    #define INTERRUPT_VECTOR_ADDR_1  // specify interrupt handler routine
*/

//New name for control register
#ifdef COP_COPCTRL_INIT
#define COP_COPCTL_INIT COP_COPCTRL_INIT
#endif


/***************************************************
* COP ioctl commands
****************************************************/
/* command                    |    Param, Description       */

#define COP_INIT                /* NULL, COP peripheral initialization  */
#define COP_DEVICE              /* COP_ENABLE/COP_DISABLE, enables/disables COP watchdog counter */
#define COP_WRITE_PROTECT       /* NULL, Write-protect COP settings (until Reset) */
#define COP_SET_TIMEOUT         /* UWord16, Sets COP Timeout Value */

#define COP_RUN_IN_STOP         /* COP_ENABLE/COP_DISABLE, controls the state of COP in WAIT mode */  
#define COP_RUN_IN_WAIT         /* COP_ENABLE/COP_DISABLE, controls the state of COP in STOP mode */  

#define COP_READ_COUNTER        /* NULL, reads current status of COP counter */

#define COP_CLEAR_COUNTER       /* NULL, clears COP counter (both steps are performed) */
#define COP_CLEAR_COUNTER_PART1 /* NULL, clears COP counter (1st step of the sequence) */
#define COP_CLEAR_COUNTER_PART2 /* NULL, clears COP counter (2nd step of the sequence) */

/****************************************************************************
* New COP features (802x3x and later)
*****************************************************************************/

#if COP_VERSION >= 2
#define COP_LOR_WATCHDOG        /* COP_ENABLE/COP_DISABLE, enables/disables Loss-of-reference clock watchdog*/
#endif

#if COP_VERSION == 2
#define COP_SET_CLOCK_SOURCE    /* COP_xxx (MSTR_OSC/RLX_OSC/IPBUS_CLK), selects COP clock source */
#endif

/****************************************************************************
* New COP features (800x)
*****************************************************************************/
#if COP_VERSION >= 3
#define COP_SET_CLOCK_SOURCE    /* COP_xxx (1KHZ/IPBUS/COSC/ROSC), selects COP clock source */
#define COP_SET_CLOCK_PRESCALER /* COP_xxx (DIV1024/DIV256/DIV16/DIV1), sets prescaler */
#endif



/****************************************************************************
* COP constants and type declarations used in the ioctl functions
*****************************************************************************/

#define COP_ENABLE    1
#define COP_DISABLE   0

/* COP control register, obsolete macros */

#define COP_CSEN   COP_COPCTL_CSEN
#define COP_CWEN   COP_COPCTL_CWEN
#define COP_CEN    COP_COPCTL_CEN 
#define COP_CWP    COP_COPCTL_CWP 

#define COP_MSTR_OSC  0

#if COP_VERSION == 2
#define COP_RLX_OSC     COP_COPCTL_CLKSEL
#endif

#if COP_VERSION <= 2 
#define COP_BYPS        COP_COPCTL_BYPS
#define COP_IPBUS_CLK   COP_COPCTL_BYPS
#endif

#if COP_VERSION >= 3
#define COP_DIV1024     COP_COPCTL_PSS_DIV1024
#define COP_DIV256      COP_COPCTL_PSS_DIV256
#define COP_DIV16       COP_COPCTL_PSS_DIV16
#define COP_DIV1        COP_COPCTL_PSS_DIV1
#define COP_1KHZ_CLK    COP_COPCTL_CLKSEL_1KHZ
#define COP_IPBUS_CLK   COP_COPCTL_CLKSEL_IPBUS
#define COP_COSC_CLK    COP_COPCTL_CLKSEL_COSC
#define COP_ROSC_CLK    COP_COPCTL_CLKSEL_ROSC
#endif
/****************************************************************************
* COP registers and bits
*****************************************************************************/

/* COP control register */
#define COP_COPCTL_CSEN    0x0008
#define COP_COPCTL_CWEN    0x0004
#define COP_COPCTL_CEN     0x0002
#define COP_COPCTL_CWP     0x0001

#if COP_VERSION <= 2  
#define COP_COPCTL_BYPS    0x0010
#endif

#if COP_VERSION == 2
#define COP_COPCTL_CLOREN  0x0020
#define COP_COPCTL_CLKSEL  0x0040
#endif

#if COP_VERSION >= 3
#define COP_COPCTL_PSS_MASK     0x0300
#define COP_COPCTL_PSS_DIV1024  0x0300
#define COP_COPCTL_PSS_DIV256   0x0200
#define COP_COPCTL_PSS_DIV16    0x0100
#define COP_COPCTL_PSS_DIV1     0x0000
#define COP_COPCTL_CLKSEL_MASK  0x0060
#define COP_COPCTL_CLKSEL_1KHZ  0x0060
#define COP_COPCTL_CLKSEL_IPBUS 0x0040
#define COP_COPCTL_CLKSEL_COSC  0x0020
#define COP_COPCTL_CLKSEL_ROSC  0x0000
#define COP_COPCTL_CLOREN       0x0010
#endif

/***********************************************************************
* COP control command macros
***********************************************************************/

/* COP initialization */
void copInit(arch_sCOP *pCopBase);
#define ioctlCOP_INIT(pCopBase, param) copInit(pCopBase)

/* COP peripheral enable/disable - functional only if COP Write protect Bit (CWP) is not set */
#define ioctlCOP_DEVICE(pCopBase, param) \
  if (param) periphBitSet(COP_COPCTL_CEN, &((pCopBase)->copctl)); \
  else periphBitClear(COP_COPCTL_CEN, &((pCopBase)->copctl))

/* COP peripheral write protect  - functional only if COP Write protect Bit (CWP) is not set */
/* if this command issued any subsequent write to COPCTL (COP Control Reg.) is blocked */
#define ioctlCOP_WRITE_PROTECT(pCopBase, param) \
  periphBitSet(COP_COPCTL_CWP, &((pCopBase)->copctl))

/* COP Run in Stop mode enable/disable */
#define ioctlCOP_RUN_IN_STOP(pCopBase, param) \
  if (param) periphBitSet(COP_COPCTL_CSEN, &((pCopBase)->copctl)); \
  else periphBitClear(COP_COPCTL_CSEN, &((pCopBase)->copctl))

/* COP Run in Stop mode enable/disable */
#define ioctlCOP_RUN_IN_WAIT(pCopBase, param) \
  if (param) periphBitSet(COP_COPCTL_CWEN, &((pCopBase)->copctl)); \
  else periphBitClear(COP_COPCTL_CWEN, &((pCopBase)->copctl))

/* sets COP timeout interval, param value is decremented before write to timeout reg */
#define ioctlCOP_SET_TIMEOUT(pCopBase, param) \
  periphMemWrite((param)-1, &((pCopBase)->copto))

/* reads current status of COP counter*/
#define ioctlCOP_READ_COUNTER(pCopBase, param) \
  periphMemRead(&((pCopBase)->copctr))

/* clears(service) COP timer */
#define ioctlCOP_CLEAR_COUNTER(pCopBase, param) \
  { periphMemWrite(0x5555, &((pCopBase)->copctr));\
    periphMemWrite(0xAAAA, &((pCopBase)->copctr)); }

#define ioctlCOP_CLEAR_COUNTER_PART1(pCopBase, param) \
  periphMemWrite(0x5555, &((pCopBase)->copctr))

#define ioctlCOP_CLEAR_COUNTER_PART2(pCopBase, param) \
  periphMemWrite(0xAAAA, &((pCopBase)->copctr))



#if COP_VERSION == 2

/* Enables Loss-of-reference clock watchdog*/
#define ioctlCOP_LOR_WATCHDOG(pCopBase, param) \
  if (param) periphBitClear(COP_COPCTL_CLOREN, &((pCopBase)->copctl)); \
  else periphBitSet(COP_COPCTL_CLOREN, &((pCopBase)->copctl))

/* Selects COP clock source */
#define ioctlCOP_SET_CLOCK_SOURCE(pCopBase, param) \
  periphBitGrpSet(COP_COPCTL_CLKSEL | COP_COPCTL_BYPS, param, &((pCopBase)->copctl))

#endif


#if COP_VERSION >= 3

/* Enables Loss-of-reference clock watchdog*/
#define ioctlCOP_LOR_WATCHDOG(pCopBase, param) \
  if (param) periphBitSet(COP_COPCTL_CLOREN, &((pCopBase)->copctl)); \
  else periphBitClear(COP_COPCTL_CLOREN, &((pCopBase)->copctl))

/* Selects COP clock source */
#define ioctlCOP_SET_CLOCK_SOURCE(pCopBase, param) \
  periphBitGrpSet(COP_COPCTL_CLKSEL_MASK, param, &((pCopBase)->copctl))

/* Selects COP clock prescaler */
#define ioctlCOP_SET_CLOCK_PRESCALER(pCopBase, param) \
  periphBitGrpSet(COP_COPCTL_PSS_MASK, param, &((pCopBase)->copctl))
  
#endif

#ifdef __cplusplus
}
#endif

#endif
