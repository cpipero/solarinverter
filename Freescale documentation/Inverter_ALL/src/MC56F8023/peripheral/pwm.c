/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: pwm_8xxx.c$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.21.0$
*
* Description: Source file for the PWM driver
*
*****************************************************************************/

#include "qs.h"
#include "pwm.h"
#include "initconfig.h"

/********************************************************************************
 pwmInit() function performs the PWM module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void pwmInit(arch_sPWM *pPwmBase)
{
#pragma unused(pPwmBase)

#if PWM_A_INIT_USED && defined(PWM_A) 
	if(pPwmBase == PWM_A)
	{  
		#if PWM_A_USE_PWMVAL
			#ifdef PWM_A_PWMVAL0_INIT
			periphMemWrite(PWM_A_PWMVAL0_INIT, (UWord16*) &pPwmBase->pwmval[0]);
			#endif
			#ifdef PWM_A_PWMVAL1_INIT
			periphMemWrite(PWM_A_PWMVAL1_INIT, (UWord16*) &pPwmBase->pwmval[1]);
			#endif
			#ifdef PWM_A_PWMVAL2_INIT
			periphMemWrite(PWM_A_PWMVAL2_INIT, (UWord16*) &pPwmBase->pwmval[2]);
			#endif
			#ifdef PWM_A_PWMVAL3_INIT
			periphMemWrite(PWM_A_PWMVAL3_INIT, (UWord16*) &pPwmBase->pwmval[3]);
			#endif
			#ifdef PWM_A_PWMVAL4_INIT
			periphMemWrite(PWM_A_PWMVAL4_INIT, (UWord16*) &pPwmBase->pwmval[4]);
			#endif
			#ifdef PWM_A_PWMVAL5_INIT
			periphMemWrite(PWM_A_PWMVAL5_INIT, (UWord16*) &pPwmBase->pwmval[5]);
			#endif
		#endif

		#ifdef PWM_A_PMFCTL_INIT
		periphMemWrite(PWM_A_PMFCTL_INIT, &pPwmBase->pmfctl);
		#endif
		#ifdef PWM_A_PWMCM_INIT
		periphMemWrite(PWM_A_PWMCM_INIT, &pPwmBase->pwmcm);
		#endif
		/* PWM_VERSION_1-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_PMDEADTM_INIT
		periphMemWrite(PWM_A_PMDEADTM_INIT, &pPwmBase->pmdeadtm);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_PMDEADTM0_INIT
		periphMemWrite(PWM_A_PMDEADTM0_INIT, &pPwmBase->pmdeadtm0);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_PMDEADTM1_INIT
		periphMemWrite(PWM_A_PMDEADTM1_INIT, &pPwmBase->pmdeadtm1);
		#endif
		#ifdef PWM_A_PMDISMAP1_INIT
		periphMemWrite(PWM_A_PMDISMAP1_INIT, &pPwmBase->pmdismap1);
		#endif
		#ifdef PWM_A_PMDISMAP2_INIT
		periphMemWrite(PWM_A_PMDISMAP2_INIT, &pPwmBase->pmdismap2);
		#endif
		#ifdef PWM_A_PMCCR_INIT
		/* write-enable and initialize PMCCR register */
		periphBitSet(PWM_PMCCR_ENHA, &pPwmBase->pmccr);	
		periphMemWrite(PWM_A_PMCCR_INIT, &pPwmBase->pmccr);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_PMSRC_INIT
		periphMemWrite(PWM_A_PMSRC_INIT, &pPwmBase->pmsrc);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_SYNC_INIT
		periphMemWrite(PWM_A_SYNC_INIT, &pPwmBase->sync);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_A_FFILT0_INIT
		periphMemWrite(PWM_A_FFILT0_INIT, &pPwmBase->ffilt0);
		#endif
		#ifdef PWM_A_FFILT1_INIT
		periphMemWrite(PWM_A_FFILT1_INIT, &pPwmBase->ffilt1);
		#endif
		#ifdef PWM_A_FFILT2_INIT
		periphMemWrite(PWM_A_FFILT2_INIT, &pPwmBase->ffilt2);
		#endif
		#ifdef PWM_A_FFILT3_INIT
		periphMemWrite(PWM_A_FFILT3_INIT, &pPwmBase->ffilt3);
		#endif
		/* the WP bit in PMCFG may now lock write access to PMSRC, PMDISMAPn, 
		   PMDEADTMn, PMCFG, SYNC, FFILTn, and PMCCR.ENHA bit */
		#ifdef PWM_A_PMCFG_INIT
		periphMemWrite(PWM_A_PMCFG_INIT, &pPwmBase->pmcfg);
		#endif
		#ifdef PWM_A_PMICCR_INIT
		periphMemWrite(PWM_A_PMICCR_INIT, &pPwmBase->pmiccr);
		#endif
		#ifdef PWM_A_PMCTL_INIT
		periphMemWrite(PWM_A_PMCTL_INIT, &pPwmBase->pmctl);
		if((PWM_A_PMCTL_INIT & PWM_PMCTL_LDOK) > 0 )  /* Load OK set inside GCT */
			periphBitSet(PWM_PMCTL_LDOK, &pPwmBase->pmctl);
		#endif
		#ifdef PWM_A_PMOUT_INIT
		periphMemWrite(PWM_A_PMOUT_INIT, &pPwmBase->pmout);
		#endif
	}
	else
#endif

#if PWM_B_INIT_USED && defined(PWM_B) 
	if(pPwmBase == PWM_B)
	{  
		#if PWM_B_USE_PWMVAL
			#ifdef PWM_B_PWMVAL0_INIT
			periphMemWrite(PWM_B_PWMVAL0_INIT, (UWord16*) &pPwmBase->pwmval[0]);
			#endif
			#ifdef PWM_B_PWMVAL1_INIT
			periphMemWrite(PWM_B_PWMVAL1_INIT, (UWord16*) &pPwmBase->pwmval[1]);
			#endif
			#ifdef PWM_B_PWMVAL2_INIT
			periphMemWrite(PWM_B_PWMVAL2_INIT, (UWord16*) &pPwmBase->pwmval[2]);
			#endif
			#ifdef PWM_B_PWMVAL3_INIT
			periphMemWrite(PWM_B_PWMVAL3_INIT, (UWord16*) &pPwmBase->pwmval[3]);
			#endif
			#ifdef PWM_B_PWMVAL4_INIT
			periphMemWrite(PWM_B_PWMVAL4_INIT, (UWord16*) &pPwmBase->pwmval[4]);
			#endif
			#ifdef PWM_B_PWMVAL5_INIT
			periphMemWrite(PWM_B_PWMVAL5_INIT, (UWord16*) &pPwmBase->pwmval[5]);
			#endif
		#endif
		
		#ifdef PWM_B_PMFCTL_INIT
		periphMemWrite(PWM_B_PMFCTL_INIT, &pPwmBase->pmfctl);
		#endif
		#ifdef PWM_B_PWMCM_INIT
		periphMemWrite(PWM_B_PWMCM_INIT, &pPwmBase->pwmcm);
		#endif
		/* PWM_VERSION_1-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_PMDEADTM_INIT
		periphMemWrite(PWM_B_PMDEADTM_INIT, &pPwmBase->pmdeadtm);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_PMDEADTM0_INIT
		periphMemWrite(PWM_B_PMDEADTM1_INIT, &pPwmBase->pmdeadtm0);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_PMDEADTM1_INIT
		periphMemWrite(PWM_B_PMDEADTM1_INIT, &pPwmBase->pmdeadtm1);
		#endif
		#ifdef PWM_B_PMDISMAP1_INIT
		periphMemWrite(PWM_B_PMDISMAP1_INIT, &pPwmBase->pmdismap1);
		#endif
		#ifdef PWM_B_PMDISMAP2_INIT
		periphMemWrite(PWM_B_PMDISMAP2_INIT, &pPwmBase->pmdismap2);
		#endif
		#ifdef PWM_B_PMCCR_INIT
		/* write-enable and initialize PMCCR register */
		periphBitSet(PWM_PMCCR_ENHA, &pPwmBase->pmccr);	
		periphMemWrite(PWM_B_PMCCR_INIT, &pPwmBase->pmccr);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_PMSRC_INIT
		periphMemWrite(PWM_B_PMSRC_INIT, &pPwmBase->pmsrc);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_SYNC_INIT
		periphMemWrite(PWM_B_SYNC_INIT, &pPwmBase->sync);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_B_FFILT0_INIT
		periphMemWrite(PWM_B_FFILT0_INIT, &pPwmBase->ffilt0);
		#endif
		#ifdef PWM_B_FFILT1_INIT
		periphMemWrite(PWM_B_FFILT1_INIT, &pPwmBase->ffilt1);
		#endif
		#ifdef PWM_B_FFILT2_INIT
		periphMemWrite(PWM_B_FFILT2_INIT, &pPwmBase->ffilt2);
		#endif
		#ifdef PWM_B_FFILT3_INIT
		periphMemWrite(PWM_B_FFILT3_INIT, &pPwmBase->ffilt3);
		#endif
		/* the WP bit in PMCFG may now lock write access to PMSRC, PMDISMAPn, 
		   PMDEADTMn, PMCFG, SYNC, FFILTn, and PMCCR.ENHA bit */
		#ifdef PWM_B_PMCFG_INIT
		periphMemWrite(PWM_B_PMCFG_INIT, &pPwmBase->pmcfg);
		#endif
		#ifdef PWM_B_PMICCR_INIT
		periphMemWrite(PWM_B_PMICCR_INIT, &pPwmBase->pmiccr);
		#endif
		#ifdef PWM_B_PMCTL_INIT
		periphMemWrite(PWM_B_PMCTL_INIT, &pPwmBase->pmctl);
		if((PWM_B_PMCTL_INIT & PWM_PMCTL_LDOK) > 0 )  /* Load OK set inside GCT */
			periphBitSet(PWM_PMCTL_LDOK, &pPwmBase->pmctl);
		#endif
		#ifdef PWM_B_PMOUT_INIT
		periphMemWrite(PWM_B_PMOUT_INIT, &pPwmBase->pmout);
		#endif
	}
	else
#endif

#if PWM_INIT_USED && defined(PWM) 

	#if PWM_A_INIT_USED
	/* please remove any PWM_A_xxx_INIT macros from your appconfig.h 
	 * PWM_A is just an alias to the one and only "PWM" module */
	#warning PWM is same as PWM_A but both are configured in appconfig.h
	#endif

	if(pPwmBase == PWM)
	{  
		#if PWM_USE_PWMVAL
			#ifdef PWM_PWMVAL0_INIT
			periphMemWrite(PWM_PWMVAL0_INIT, (UWord16*) &pPwmBase->pwmval[0]);
			#endif
			#ifdef PWM_PWMVAL1_INIT
			periphMemWrite(PWM_PWMVAL1_INIT, (UWord16*) &pPwmBase->pwmval[1]);
			#endif
			#ifdef PWM_PWMVAL2_INIT
			periphMemWrite(PWM_PWMVAL2_INIT, (UWord16*) &pPwmBase->pwmval[2]);
			#endif
			#ifdef PWM_PWMVAL3_INIT
			periphMemWrite(PWM_PWMVAL3_INIT, (UWord16*) &pPwmBase->pwmval[3]);
			#endif
			#ifdef PWM_PWMVAL4_INIT
			periphMemWrite(PWM_PWMVAL4_INIT, (UWord16*) &pPwmBase->pwmval[4]);
			#endif
			#ifdef PWM_PWMVAL5_INIT
			periphMemWrite(PWM_PWMVAL5_INIT, (UWord16*) &pPwmBase->pwmval[5]);
			#endif
		#endif
		
		#ifdef PWM_PMFCTL_INIT
		periphMemWrite(PWM_PMFCTL_INIT, &pPwmBase->pmfctl);
		#endif
		#ifdef PWM_PWMCM_INIT
		periphMemWrite(PWM_PWMCM_INIT, &pPwmBase->pwmcm);
		#endif
		/* PWM_VERSION_1-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_PMDEADTM_INIT
		periphMemWrite(PWM_PMDEADTM_INIT, &pPwmBase->pmdeadtm);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_PMDEADTM0_INIT
		periphMemWrite(PWM_PMDEADTM0_INIT, &pPwmBase->pmdeadtm0);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_PMDEADTM1_INIT
		periphMemWrite(PWM_PMDEADTM1_INIT, &pPwmBase->pmdeadtm1);
		#endif
		#ifdef PWM_PMDISMAP1_INIT
		periphMemWrite(PWM_PMDISMAP1_INIT, &pPwmBase->pmdismap1);
		#endif
		#ifdef PWM_PMDISMAP2_INIT
		periphMemWrite(PWM_PMDISMAP2_INIT, &pPwmBase->pmdismap2);
		#endif
		#ifdef PWM_PMCCR_INIT
		/* write-enable and initialize PMCCR register */
		periphBitSet(PWM_PMCCR_ENHA, &pPwmBase->pmccr);	
		periphMemWrite(PWM_PMCCR_INIT, &pPwmBase->pmccr);
		#endif
		/* PWM_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_PMSRC_INIT
		periphMemWrite(PWM_PMSRC_INIT, &pPwmBase->pmsrc);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_SYNC_INIT
		periphMemWrite(PWM_SYNC_INIT, &pPwmBase->sync);
		#endif
		/* PWM_VERSION_3-only  (see module strucutre and target MCU in arch.h) */
		#ifdef PWM_FFILT0_INIT
		periphMemWrite(PWM_FFILT0_INIT, &pPwmBase->ffilt0);
		#endif
		#ifdef PWM_FFILT1_INIT
		periphMemWrite(PWM_FFILT1_INIT, &pPwmBase->ffilt1);
		#endif
		#ifdef PWM_FFILT2_INIT
		periphMemWrite(PWM_FFILT2_INIT, &pPwmBase->ffilt2);
		#endif
		#ifdef PWM_FFILT3_INIT
		periphMemWrite(PWM_FFILT3_INIT, &pPwmBase->ffilt3);
		#endif
		/* the WP bit in PMCFG may now lock write access to PMSRC, PMDISMAPn, 
		   PMDEADTMn, PMCFG, SYNC, FFILTn, and PMCCR.ENHA bit */
		#ifdef PWM_PMCFG_INIT
		periphMemWrite(PWM_PMCFG_INIT, &pPwmBase->pmcfg);
		#endif
		#ifdef PWM_PMICCR_INIT
		periphMemWrite(PWM_PMICCR_INIT, &pPwmBase->pmiccr);
		#endif
		#ifdef PWM_PMCTL_INIT
		periphMemWrite(PWM_PMCTL_INIT, &pPwmBase->pmctl);
		if((PWM_PMCTL_INIT & PWM_PMCTL_LDOK) > 0 )  /* Load OK set inside GCT */
			periphBitSet(PWM_PMCTL_LDOK, &pPwmBase->pmctl);
		#endif
		#ifdef PWM_PMOUT_INIT
		periphMemWrite(PWM_PMOUT_INIT, &pPwmBase->pmout);
		#endif
	}
	else
#endif

	; /* last else case */
}
