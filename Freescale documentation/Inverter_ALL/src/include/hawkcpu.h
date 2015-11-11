/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: hawkcpu.h$
*
* $Date:      Nov-27-2008$
*
* $Version:   2.3.13.0$
*
* Description: This file defines what periheral modules and other resources are
*              available on the chip selected in "appconfig.h" file
*
******************************************************************************/

#ifndef __HAWKCPU_H
#define __HAWKCPU_H

#include "appconfig.h"

/* 83xx (HawkV2 classic) family */
#if defined(MC56F8322) || \
	defined(MC56F8323) || \
	defined(MC56F8335) || \
	defined(MC56F8345) || \
	defined(MC56F8346) || \
	defined(MC56F8347) || \
	defined(MC56F8355) || \
	defined(MC56F8356) || \
	defined(MC56F8357) || \
	defined(MC56F8365) || \
	defined(MC56F8366) || \
	defined(MC56F8367) || \
	/* obsolete part name */ \
	defined(DSP56F836) || \
	defined(DSP56F8323)

	#define MC56F83xx 1 	

	#if defined(MC56F8322) || \
		defined(MC56F8323)
		#define MC56F832x 1
	#endif

	#if defined(MC56F8335)
		#define MC56F833x 1
	#endif

	#if defined(MC56F8345) || \
		defined(MC56F8346) || \
		defined(MC56F8347)
		#define MC56F834x 1
	#endif

	#if defined(MC56F8355) || \
		defined(MC56F8356) || \
		defined(MC56F8357)
		#define MC56F835x 1
	#endif

	#if defined(MC56F8365) || \
		defined(MC56F8366) || \
		defined(MC56F8367)
		#define MC56F836x 1
	#endif

	/* LQFP128 package */
	#if defined(MC56F8335) || \
		defined(MC56F8345) || \
		defined(MC56F8355) || \
		defined(MC56F8365)
		#define MC56F83x5 1
	#endif

	/* LQFP144 package */
	#if defined(MC56F8346) || \
		defined(MC56F8356) || \
		defined(MC56F8366)
		#define MC56F83x6 1
	#endif

	/* LQFP160 package */
	#if defined(MC56F8347) || \
		defined(MC56F8357) || \
		defined(MC56F8367)
		#define MC56F83x7 1
	#endif

/* 80xx (HawkV2 Anguilla) family */
#elif defined(MC56F8011) || \
	defined(MC56F8012) || \
	defined(MC56F8013) || \
	defined(MC56F8014) || \
	defined(MC56F8023) || \
	defined(MC56F8025) || \
	defined(MC56F8036) || \
	defined(MC56F8037) || \
	defined(MC56F8002) || \
	defined(MC56F8006)
	
	#define MC56F80xx 1		
	
    #if defined(MC56F8011) || \
    	defined(MC56F8012) || \
    	defined(MC56F8013) || \
    	defined(MC56F8014)	
	    #define MC56F801x 1
	#endif

    /* 802x/3x (Anguilla Blue) family */
    #if defined(MC56F8023) || \
    	defined(MC56F8025)
	    #define MC56F802x 1
	#endif
	
    #if defined(MC56F8036) || \
    	defined(MC56F8037)
	    #define MC56F803x 1
	#endif
	
	/* 800x (Anguilla White) family */
    #if defined(MC56F8002) || \
        defined(MC56F8006)
        #define MC56F800x 1 
    #endif
#else

	/* many Quick_Start-related code depends on knowing what device is used */
	#error Unknown device (or not defined in appconfig.h?)
	
#endif

#endif /* __HAWKCPU_H */
