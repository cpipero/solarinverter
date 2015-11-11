/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  scihl.h
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.7.0$
*
* Description: Header file for the SCI driver - calculation of HIGHLEVEL mode
*
*******************************************************************************/

#ifndef __SCIHL_H
#define __SCIHL_H

#ifndef __APPCONFIG_H
#error appconfig.h must be included before scihl.h
#endif

#ifndef __SCI_H
#error sci.h must be included before scihl.h
#endif

/* if not yet defined, test which high level mode will be used for SCI modules */
/* i.e. select the mode suitable for both SCI_0 and SCI_1 */

#ifndef SCI_HIGHLEVEL_MODE
#if SCI_0_HIGHLEVEL_MODE
/* same as SCI_0 */
#define SCI_HIGHLEVEL_MODE SCI_0_HIGHLEVEL_MODE
#if SCI_1_HIGHLEVEL_MODE && SCI_1_HIGHLEVEL_MODE != SCI_0_HIGHLEVEL_MODE
/* different non-zero modes for SCI_0 and SCI_1 */
#error Different high level modes selected for SCI_0 and SCI_1.
#endif
#elif SCI_1_HIGHLEVEL_MODE
/* same as SCI_1 */
#define SCI_HIGHLEVEL_MODE SCI_1_HIGHLEVEL_MODE
#else
/* no high-level function by default */
#define SCI_HIGHLEVEL_MODE SCI_HIGHLEVEL_MODE_NONE	
#endif
#endif

#endif /* __SCIHL_H */

