/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: qs.h$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.4.0$
*
* Description: This is the master header file for quick start projects. It 
*              includes all the neccesary system files needed by quick start
*              sources. The peripheral driver headers are NOT included.
*
******************************************************************************/

#ifndef __QS_H
#define __QS_H

#ifndef DSP56800E_QUICK_START_VERSION
/* 
   In all Quick_Start applications and stationery, the version.h file is 
   included in the .lcf file of each target. The .lcf is in-turn used as 
   a prefix file (or included in prefix text). 
   
   Having the DSP56800E_QUICK_START_VERSION macro NOT defined means 
   the compiler does not use the .lcf file as a prefix file which may 
   lead to other compilation issues. Please check the target settings. 
*/
#warning version.h should be included in the compiler prefix header file
#endif

#include "version.h"
#include "types.h"

/* device configuration */
#include "appconfig.h"
#include "hawkcpu.h"

/* peripheral map */
#include "arch.h"

/* core and peripheral access macros */
#include "core.h"
#include "periph.h"

#endif

