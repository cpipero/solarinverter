/******************************************************************************
*
* freemaster_cfg.h
*
* FreeMASTER Serial Communication Driver configuration file. This is the 
* placeholder file which further includes the main application configuration
* header file (appconfig.h) and enables the FreeMATSER driver is configured 
* in the Graphical Configuration Tool
*
* See all FreeMASTER configuration options in the "appconfig.h" file 
*
*******************************************************************************/

#ifndef __FREEMASTER_CFG_H
#define __FREEMASTER_CFG_H

#include "types.h"     	/* ITU types defined here (required in arch.h) */
#include "arch.h"      	/* SCI base address is defined in this file */
#include "appconfig.h"	/* FreeMASTER driver is configured by GCT */

/*
 * The GCT selects the communication channel using an enumeration constant,
 *  we need to convert it into USE_SCI or USE_JTAG settings 
 */

/* SCI_0 (or single SCI) */
#if (FMSTR_COMM_INTERFACE) == 1 
    #define FMSTR_USE_SCI  1
    #if defined(SCI0_BASE)
    #define FMSTR_SCI_BASE SCI0_BASE
    #elif defined(SCI_BASE)
    #define FMSTR_SCI_BASE SCI_BASE
    #else
    #error SCI_0 base address not specified in arch.h
    #endif

/* SCI_1 */
#elif (FMSTR_COMM_INTERFACE) == 2 
    #define FMSTR_USE_SCI  1
    #if defined(SCI1_BASE)
    #define FMSTR_SCI_BASE SCI1_BASE
    #else
    #error SCI_1 base address not specified in arch.h
    #endif
    
/* JTAG without (3) or with (4) the TDF bug workaround */
#elif (FMSTR_COMM_INTERFACE) == 3 || (FMSTR_COMM_INTERFACE) == 4 
    #define FMSTR_USE_JTAG 1
    #if defined(EONCE_BASE)
    #define FMSTR_JTAG_BASE EONCE_BASE
    #endif

    #if (FMSTR_COMM_INTERFACE) == 4
        #define FMSTR_USE_JTAG_TXFIX 1
    #else
        #define FMSTR_USE_JTAG_TXFIX 0
    #endif
    
#endif /* COMM_INTERFACE */

#endif /* __FREEMASTER_CFG_H */
