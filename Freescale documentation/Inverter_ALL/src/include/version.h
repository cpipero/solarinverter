/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: version.h$
*
* $Date:      Oct-7-2008$
*
* Description: Defines the quick-start version constants 
*
*****************************************************************************/

#ifndef __VERSION_H
#define __VERSION_H

/*****************************************************************************
           RELEASE LIST - HISTORY

release       symbol                                           value
------------------------------------------------------------------------------
0.Beta        DSP56800E_QUICK_START_VERSION_0_BETA             0x0000
1.0           DSP56800E_QUICK_START_VERSION_1_0                0x0100
1.1           DSP56800E_QUICK_START_VERSION_1_1                0x0101
2.0-Beta      DSP56800E_QUICK_START_VERSION_2_0BETA            0x01ff
2.0           DSP56800E_QUICK_START_VERSION_2_0                0x0200
2.1           DSP56800E_QUICK_START_VERSION_2_1                0x0201
2.2           DSP56800E_QUICK_START_VERSION_2_2                0x0202
2.3-Beta      DSP56800E_QUICK_START_VERSION_2_3BETA            0x0203
2.3-Beta2     DSP56800E_QUICK_START_VERSION_2_3BETA2           0x0203
2.3           DSP56800E_QUICK_START_VERSION_2_3                0x0203
2.4-Alpha     DSP56800E_QUICK_START_VERSION_2_4                0x0204
*****************************************************************************/

#define VERSION_MAKE(major,minor) ((major)<<8 | (minor))
#define VERSION_MAJOR(ver) ((ver)>>8)
#define VERSION_MINOR(ver) ((ver)&0xff)

#define DSP56800E_QUICK_START_VERSION 		VERSION_MAKE(2,4)
#define DSP56800E_QUICK_START_MINOR_VERSION	VERSION_MINOR(DSP56800E_QUICK_START_VERSION)
#define DSP56800E_QUICK_START_MAJOR_VERSION	VERSION_MAJOR(DSP56800E_QUICK_START_VERSION)

#define DSP56800E_QUICK_START_VERSION_2_4

#endif /* __VERSION_H */
