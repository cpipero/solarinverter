/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  sys.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.5.0$
*
* Description: SYS (system reset and support functions) driver SIM_VERSION_3
*
*****************************************************************************/

#include "qs.h"
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/* initialization of SYS (SIM) system support functions */

void sysInit(arch_sSIM *pSimBase)
{
#pragma unused(pSimBase)

	#ifdef SIM_CONROL_INIT
	periphMemWrite(SIM_CONROL_INIT, &pSimBase->sim_control);
	#endif
 
	#ifdef SIM_CLKOSR_INIT
	periphMemWrite(SIM_CLKOSR_INIT, &pSimBase->sim_clkosr);
	#endif

	#ifdef SIM_GPSA0_INIT
	periphMemWrite(SIM_GPSA0_INIT, &pSimBase->sim_gpsa0);
	#endif

	#ifdef SIM_GPSA1_INIT
	periphMemWrite(SIM_GPSA1_INIT, &pSimBase->sim_gpsa1);
	#endif

	#ifdef SIM_GPSB0_INIT
	periphMemWrite(SIM_GPSB0_INIT, &pSimBase->sim_gpsb0);
	#endif

	#ifdef SIM_GPSB1_INIT
	periphMemWrite(SIM_GPSB1_INIT, &pSimBase->sim_gpsb1);
	#endif

	#ifdef SIM_GPSCD_INIT
	periphMemWrite(SIM_GPSCD_INIT, &pSimBase->sim_gpscd);
	#endif

	#ifdef SIM_IPS0_INIT
	periphMemWrite(SIM_IPS0_INIT, &pSimBase->sim_ips0);
	#endif

	#ifdef SIM_IPS1_INIT
	periphMemWrite(SIM_IPS1_INIT, &pSimBase->sim_ips1);
	#endif

	#ifdef SIM_IPS2_INIT
	periphMemWrite(SIM_IPS2_INIT, &pSimBase->sim_ips2);
	#endif

	#ifdef SIM_PCR_INIT
	periphMemWrite(SIM_PCR_INIT, &pSimBase->sim_pcr);
	#endif

	#ifdef SIM_SD0_INIT
	periphMemWrite(SIM_SD0_INIT, &pSimBase->sim_sd0);
	#endif

	#ifdef SIM_SD1_INIT
	periphMemWrite(SIM_SD1_INIT, &pSimBase->sim_sd1);
	#endif

	#ifdef SIM_PCE0_INIT
	periphMemWrite(SIM_PCE0_INIT, &pSimBase->sim_pce0);
	#endif

	#ifdef SIM_PCE1_INIT
	periphMemWrite(SIM_PCE1_INIT, &pSimBase->sim_pce1);
	#endif

	#ifdef SIM_PROT_INIT
	periphMemWrite(SIM_PROT_INIT, &pSimBase->sim_prot);
	#endif

	/* LVI is initialized here as a part of SYS initialization */	
	#ifdef LVI_CONTROL_INIT
	periphMemWrite(LVI_CONTROL_INIT, &LVI->lvictlr);
	#endif
}

#ifdef __cplusplus
}
#endif
