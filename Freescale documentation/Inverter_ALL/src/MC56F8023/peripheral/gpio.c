/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  gpio.c
*
* $Date:      Mar-24-2009$
*
* $Version:   2.3.17.0$
*
* Description: Source file for the GPIO driver
*
*****************************************************************************/

#include "qs.h"
#include "gpio.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 gpioInit() function performs the GPIO module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void gpioInit(arch_sPort *pGpioBase)
{
#pragma unused(pGpioBase)

#if GPIO_A_INIT_USED && defined(GPIO_A)
	if (pGpioBase == GPIO_A)
	{
		/* configure GPIO PORT A */
		#ifdef GPIO_A_PUR_INIT
		periphMemWrite(GPIO_A_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_A_DDR_INIT
		periphMemWrite(GPIO_A_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_A_DR_INIT
		periphMemWrite(GPIO_A_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_A_PER_INIT
		periphMemWrite(GPIO_A_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_A_IENR_INIT
		periphMemWrite(GPIO_A_IENR_INIT, &pGpioBase->ienr);
		#endif
		
		#ifdef GPIO_A_IPOLR_INIT
		periphMemWrite(GPIO_A_IPOLR_INIT, &pGpioBase->ipolr);
		#endif

  #if GPIO_VERSION <= 2
		#ifdef GPIO_A_PPMODE_INIT
		periphMemWrite(GPIO_A_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_A_DRIVE_INIT
		periphMemWrite(GPIO_A_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
		/* GPIO_VERSION_3-only */
		#ifdef GPIO_A_IFE_INIT
		periphMemWrite(GPIO_A_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_A_SLEW_INIT
		periphMemWrite(GPIO_A_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else 
#endif
	
#if GPIO_B_INIT_USED && defined(GPIO_B)
	if (pGpioBase == GPIO_B)
	{
		/* configure GPIO PORT B */
		#ifdef GPIO_B_PUR_INIT
		periphMemWrite(GPIO_B_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_B_DDR_INIT
		periphMemWrite(GPIO_B_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_B_DR_INIT
		periphMemWrite(GPIO_B_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_B_PER_INIT
		periphMemWrite(GPIO_B_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_B_IENR_INIT
		periphMemWrite(GPIO_B_IENR_INIT, &pGpioBase->ienr);
		#endif
		
		#ifdef GPIO_B_IPOLR_INIT
		periphMemWrite(GPIO_B_IPOLR_INIT, &pGpioBase->ipolr);
		#endif	

  #if GPIO_VERSION <= 2
		#ifdef GPIO_B_PPMODE_INIT
		periphMemWrite(GPIO_B_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_B_DRIVE_INIT
		periphMemWrite(GPIO_B_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
    /* GPIO_VERSION_3-only */
		#ifdef GPIO_B_IFE_INIT
		periphMemWrite(GPIO_B_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_B_SLEW_INIT
		periphMemWrite(GPIO_B_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else 
#endif
	
#if GPIO_C_INIT_USED && defined(GPIO_C)
	if (pGpioBase == GPIO_C)
	{
		/* configure GPIO PORT B */
		#ifdef GPIO_C_PUR_INIT
		periphMemWrite(GPIO_C_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_C_DDR_INIT
		periphMemWrite(GPIO_C_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_C_DR_INIT
		periphMemWrite(GPIO_C_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_C_PER_INIT
		periphMemWrite(GPIO_C_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_C_IENR_INIT
		periphMemWrite(GPIO_C_IENR_INIT, &pGpioBase->ienr);
		#endif
		
		#ifdef GPIO_C_IPOLR_INIT
		periphMemWrite(GPIO_C_IPOLR_INIT, &pGpioBase->ipolr);
		#endif	

  #if GPIO_VERSION <= 2
		#ifdef GPIO_C_PPMODE_INIT
		periphMemWrite(GPIO_C_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_C_DRIVE_INIT
		periphMemWrite(GPIO_C_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
    /* GPIO_VERSION_3-only */
		#ifdef GPIO_C_IFE_INIT
		periphMemWrite(GPIO_C_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_C_SLEW_INIT
		periphMemWrite(GPIO_C_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else 
#endif
	
#if GPIO_D_INIT_USED && defined(GPIO_D)
	if (pGpioBase == GPIO_D)
	{
		/* configure GPIO PORT D */
		#ifdef GPIO_D_PUR_INIT
		periphMemWrite(GPIO_D_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_D_DDR_INIT
		periphMemWrite(GPIO_D_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_D_DR_INIT
		periphMemWrite(GPIO_D_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_D_PER_INIT
		periphMemWrite(GPIO_D_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_D_IENR_INIT
		periphMemWrite(GPIO_D_IENR_INIT, &pGpioBase->ienr);
		#endif
		
		#ifdef GPIO_D_IPOLR_INIT
		periphMemWrite(GPIO_D_IPOLR_INIT,&pGpioBase->ipolr);
		#endif	

  #if GPIO_VERSION <= 2		
		#ifdef GPIO_D_PPMODE_INIT
		periphMemWrite(GPIO_D_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_D_DRIVE_INIT
		periphMemWrite(GPIO_D_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
    /* GPIO_VERSION_3-only */
		#ifdef GPIO_D_IFE_INIT
		periphMemWrite(GPIO_D_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_D_SLEW_INIT
		periphMemWrite(GPIO_D_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else 
#endif
	
#if GPIO_E_INIT_USED && defined(GPIO_E)
	if (pGpioBase == GPIO_E)
	{
		/* configure GPIO PORT E */
		#ifdef GPIO_E_PUR_INIT
		periphMemWrite(GPIO_E_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_E_DDR_INIT
		periphMemWrite(GPIO_E_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_E_DR_INIT
		periphMemWrite(GPIO_E_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_E_PER_INIT
		periphMemWrite(GPIO_E_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_E_IENR_INIT
		periphMemWrite(GPIO_E_IENR_INIT, &pGpioBase->ienr);
		#endif
	
		#ifdef GPIO_E_IPOLR_INIT
		periphMemWrite(GPIO_E_IPOLR_INIT, &pGpioBase->ipolr);
		#endif

  #if GPIO_VERSION <= 2		
		#ifdef GPIO_E_PPMODE_INIT
		periphMemWrite(GPIO_E_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_E_DRIVE_INIT
		periphMemWrite(GPIO_E_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
    /* GPIO_VERSION_3-only */
		#ifdef GPIO_E_IFE_INIT
		periphMemWrite(GPIO_E_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_E_SLEW_INIT
		periphMemWrite(GPIO_E_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else
#endif

#if GPIO_F_INIT_USED && defined(GPIO_F)
	if (pGpioBase == GPIO_F)
	{
		/* configure GPIO PORT E */
		#ifdef GPIO_F_PUR_INIT
		periphMemWrite(GPIO_F_PUR_INIT, &pGpioBase->pur);
		#endif
		
		#ifdef GPIO_F_DDR_INIT
		periphMemWrite(GPIO_F_DDR_INIT, &pGpioBase->ddr);
		#endif

		#ifdef GPIO_F_DR_INIT
		periphMemWrite(GPIO_F_DR_INIT, &pGpioBase->dr);
		#endif
		
		#ifdef GPIO_F_PER_INIT
		periphMemWrite(GPIO_F_PER_INIT, &pGpioBase->per);
		#endif
		
		#ifdef GPIO_F_IENR_INIT
		periphMemWrite(GPIO_F_IENR_INIT, &pGpioBase->ienr);
		#endif
	
		#ifdef GPIO_F_IPOLR_INIT
		periphMemWrite(GPIO_F_IPOLR_INIT, &pGpioBase->ipolr);
		#endif
		
  #if GPIO_VERSION <= 2		
		#ifdef GPIO_F_PPMODE_INIT
		periphMemWrite(GPIO_F_PPMODE_INIT, &pGpioBase->ppmode);
		#endif
  #endif

  #if GPIO_VERSION >= 2
		/* GPIO_VERSION_2-only  (see module strucutre and target MCU in arch.h) */
		#ifdef GPIO_F_DRIVE_INIT
		periphMemWrite(GPIO_F_DRIVE_INIT, &pGpioBase->drive);
		#endif
  #endif

  #if GPIO_VERSION >= 3	
    /* GPIO_VERSION_3-only */
		#ifdef GPIO_F_IFE_INIT
		periphMemWrite(GPIO_F_IFE_INIT, &pGpioBase->ife);
		#endif

		#ifdef GPIO_F_SLEW_INIT
		periphMemWrite(GPIO_F_SLEW_INIT, &pGpioBase->slew);
		#endif
  #endif
	}
	else
#endif

	; /* the last else command */
}
void gpioInitAll(void)
{
	#if GPIO_A_INIT_USED
	ioctl(GPIO_A, GPIO_INIT, NULL);
	#endif
	#if GPIO_B_INIT_USED
   	ioctl(GPIO_B, GPIO_INIT, NULL);
	#endif
	#if GPIO_C_INIT_USED
   	ioctl(GPIO_C, GPIO_INIT, NULL);
	#endif
	#if GPIO_D_INIT_USED
   	ioctl(GPIO_D, GPIO_INIT, NULL);
	#endif
	#if GPIO_E_INIT_USED
   	ioctl(GPIO_E, GPIO_INIT, NULL);
	#endif
	#if GPIO_F_INIT_USED
   	ioctl(GPIO_F, GPIO_INIT, NULL);
	#endif
}


#ifdef __cplusplus
}
#endif

