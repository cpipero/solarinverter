/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: initconfig.h$
*
* $Date:      Apr-14-2009$
*
* $Version:   2.3.14.0$
*
* Description: This file is used to collect statistics about modules configured
*              in the "appconfig.h" file. The information is used to optimize 
*              initialization function of each peripheral module.
*
******************************************************************************/

#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#if defined (ADC_A_ADCCAL_INIT) || \
    defined (ADC_A_ADCPOWER_INIT) || \
    defined (ADC_A_ADCR1_INIT) || \
    defined (ADC_A_ADCR2_INIT) || \
    defined (ADC_A_ADHLMT0_INIT) || \
    defined (ADC_A_ADHLMT1_INIT) || \
    defined (ADC_A_ADHLMT2_INIT) || \
    defined (ADC_A_ADHLMT3_INIT) || \
    defined (ADC_A_ADHLMT4_INIT) || \
    defined (ADC_A_ADHLMT5_INIT) || \
    defined (ADC_A_ADHLMT6_INIT) || \
    defined (ADC_A_ADHLMT7_INIT) || \
    defined (ADC_A_ADLLMT0_INIT) || \
    defined (ADC_A_ADLLMT1_INIT) || \
    defined (ADC_A_ADLLMT2_INIT) || \
    defined (ADC_A_ADLLMT3_INIT) || \
    defined (ADC_A_ADLLMT4_INIT) || \
    defined (ADC_A_ADLLMT5_INIT) || \
    defined (ADC_A_ADLLMT6_INIT) || \
    defined (ADC_A_ADLLMT7_INIT) || \
    defined (ADC_A_ADLST1_INIT) || \
    defined (ADC_A_ADLST2_INIT) || \
    defined (ADC_A_ADLST3_INIT) || \
    defined (ADC_A_ADLST4_INIT) || \
    defined (ADC_A_ADOFS0_INIT) || \
    defined (ADC_A_ADOFS1_INIT) || \
    defined (ADC_A_ADOFS2_INIT) || \
    defined (ADC_A_ADOFS3_INIT) || \
    defined (ADC_A_ADOFS4_INIT) || \
    defined (ADC_A_ADOFS5_INIT) || \
    defined (ADC_A_ADOFS6_INIT) || \
    defined (ADC_A_ADOFS7_INIT) || \
    defined (ADC_A_ADSDIS_INIT) || \
    defined (ADC_A_ADZCC_INIT)
#define ADC_A_INIT_USED 1
#endif

#if defined (ADC_B_ADCCAL_INIT) || \
    defined (ADC_B_ADCPOWER_INIT) || \
    defined (ADC_B_ADCR1_INIT) || \
    defined (ADC_B_ADCR2_INIT) || \
    defined (ADC_B_ADHLMT0_INIT) || \
    defined (ADC_B_ADHLMT1_INIT) || \
    defined (ADC_B_ADHLMT2_INIT) || \
    defined (ADC_B_ADHLMT3_INIT) || \
    defined (ADC_B_ADHLMT4_INIT) || \
    defined (ADC_B_ADHLMT5_INIT) || \
    defined (ADC_B_ADHLMT6_INIT) || \
    defined (ADC_B_ADHLMT7_INIT) || \
    defined (ADC_B_ADLLMT0_INIT) || \
    defined (ADC_B_ADLLMT1_INIT) || \
    defined (ADC_B_ADLLMT2_INIT) || \
    defined (ADC_B_ADLLMT3_INIT) || \
    defined (ADC_B_ADLLMT4_INIT) || \
    defined (ADC_B_ADLLMT5_INIT) || \
    defined (ADC_B_ADLLMT6_INIT) || \
    defined (ADC_B_ADLLMT7_INIT) || \
    defined (ADC_B_ADLST1_INIT) || \
    defined (ADC_B_ADLST2_INIT) || \
    defined (ADC_B_ADLST3_INIT) || \
    defined (ADC_B_ADLST4_INIT) || \
    defined (ADC_B_ADOFS0_INIT) || \
    defined (ADC_B_ADOFS1_INIT) || \
    defined (ADC_B_ADOFS2_INIT) || \
    defined (ADC_B_ADOFS3_INIT) || \
    defined (ADC_B_ADOFS4_INIT) || \
    defined (ADC_B_ADOFS5_INIT) || \
    defined (ADC_B_ADOFS6_INIT) || \
    defined (ADC_B_ADOFS7_INIT) || \
    defined (ADC_B_ADSDIS_INIT) || \
    defined (ADC_B_ADZCC_INIT)
#define ADC_B_INIT_USED 1
#endif

#if defined (ADC_ADCCAL_INIT) || \
    defined (ADC_ADCPOWER_INIT) || \
    defined (ADC_ADCR1_INIT) || \
    defined (ADC_ADCR2_INIT) || \
    defined (ADC_ADHLMT0_INIT) || \
    defined (ADC_ADHLMT1_INIT) || \
    defined (ADC_ADHLMT2_INIT) || \
    defined (ADC_ADHLMT3_INIT) || \
    defined (ADC_ADHLMT4_INIT) || \
    defined (ADC_ADHLMT5_INIT) || \
    defined (ADC_ADHLMT6_INIT) || \
    defined (ADC_ADHLMT7_INIT) || \
    defined (ADC_ADLLMT0_INIT) || \
    defined (ADC_ADLLMT1_INIT) || \
    defined (ADC_ADLLMT2_INIT) || \
    defined (ADC_ADLLMT3_INIT) || \
    defined (ADC_ADLLMT4_INIT) || \
    defined (ADC_ADLLMT5_INIT) || \
    defined (ADC_ADLLMT6_INIT) || \
    defined (ADC_ADLLMT7_INIT) || \
    defined (ADC_ADLST1_INIT) || \
    defined (ADC_ADLST2_INIT) || \
    defined (ADC_ADLST3_INIT) || \
    defined (ADC_ADLST4_INIT) || \
    defined (ADC_ADOFS0_INIT) || \
    defined (ADC_ADOFS1_INIT) || \
    defined (ADC_ADOFS2_INIT) || \
    defined (ADC_ADOFS3_INIT) || \
    defined (ADC_ADOFS4_INIT) || \
    defined (ADC_ADOFS5_INIT) || \
    defined (ADC_ADOFS6_INIT) || \
    defined (ADC_ADOFS7_INIT) || \
    defined (ADC_ADSDIS_INIT) || \
    defined (ADC_ADZCC_INIT)
#define ADC_INIT_USED 1
#endif

#if defined (ADC_0_ADCS2_INIT) || \
    defined (ADC_0_ADCCFG_INIT) || \
    defined (ADC_0_ADCSC1A_INIT) || \
    defined (ADC_0_ADCSC1B_INIT)
#define ADC_0_INIT_USED 1
#endif

#if defined (ADC_1_ADCS2_INIT) || \
    defined (ADC_1_ADCCFG_INIT) || \
    defined (ADC_1_ADCSC1A_INIT) || \
    defined (ADC_1_ADCSC1B_INIT)
#define ADC_1_INIT_USED 1
#endif


#if defined (DEC_0_DECCR_INIT) || \
    defined (DEC_0_FIR_INIT) || \
    defined (DEC_0_LIR_INIT) || \
    defined (DEC_0_UIR_INIT) || \
    defined (DEC_0_WTR_INIT)
#define DEC_0_INIT_USED 1
#endif

#if defined (DEC_1_DECCR_INIT) || \
    defined (DEC_1_FIR_INIT) || \
    defined (DEC_1_LIR_INIT) || \
    defined (DEC_1_UIR_INIT) || \
    defined (DEC_1_WTR_INIT)
#define DEC_1_INIT_USED 1
#endif

#if defined (DEC_DECCR_INIT) || \
    defined (DEC_FIR_INIT) || \
    defined (DEC_LIR_INIT) || \
    defined (DEC_UIR_INIT) || \
    defined (DEC_WTR_INIT)
#define DEC_INIT_USED 1
#endif

#if defined (FCAN_CTL0_INIT) || \
    defined (FCAN_CTL1_INIT) || \
    defined (FCAN_IMASK1_INIT) || \
    defined (FCAN_MCR_INIT) || \
    defined (FCAN_RX14MASKH_INIT) || \
    defined (FCAN_RX14MASKL_INIT) || \
    defined (FCAN_RX15MASKH_INIT) || \
    defined (FCAN_RX15MASKL_INIT) || \
    defined (FCAN_RXGMASKH_INIT) || \
    defined (FCAN_RXGMASKL_INIT)
#define FCAN_INIT_USED 1
#endif

#if defined (FCAN2_CTL0_INIT) || \
    defined (FCAN2_CTL1_INIT) || \
    defined (FCAN2_IMASK1_INIT) || \
    defined (FCAN2_MCR_INIT) || \
    defined (FCAN2_RX14MASKH_INIT) || \
    defined (FCAN2_RX14MASKL_INIT) || \
    defined (FCAN2_RX15MASKH_INIT) || \
    defined (FCAN2_RX15MASKL_INIT) || \
    defined (FCAN2_RXGMASKH_INIT) || \
    defined (FCAN2_RXGMASKL_INIT)
#define FCAN2_INIT_USED 1
#endif

#if defined (GPIO_A_DDR_INIT) || \
    defined (GPIO_A_DRIVE_INIT) || \
    defined (GPIO_A_DR_INIT) || \
    defined (GPIO_A_IENR_INIT) || \
    defined (GPIO_A_IPOLR_INIT) || \
    defined (GPIO_A_PER_INIT) || \
    defined (GPIO_A_PPMODE_INIT) || \
    defined (GPIO_A_PUR_INIT)
#define GPIO_A_INIT_USED 1
#endif

#if defined (GPIO_B_DDR_INIT) || \
    defined (GPIO_B_DRIVE_INIT) || \
    defined (GPIO_B_DR_INIT) || \
    defined (GPIO_B_IENR_INIT) || \
    defined (GPIO_B_IPOLR_INIT) || \
    defined (GPIO_B_PER_INIT) || \
    defined (GPIO_B_PPMODE_INIT) || \
    defined (GPIO_B_PUR_INIT)
#define GPIO_B_INIT_USED 1
#endif

#if defined (GPIO_C_DDR_INIT) || \
    defined (GPIO_C_DRIVE_INIT) || \
    defined (GPIO_C_DR_INIT) || \
    defined (GPIO_C_IENR_INIT) || \
    defined (GPIO_C_IPOLR_INIT) || \
    defined (GPIO_C_PER_INIT) || \
    defined (GPIO_C_PPMODE_INIT) || \
    defined (GPIO_C_PUR_INIT)
#define GPIO_C_INIT_USED 1
#endif

#if defined (GPIO_D_DDR_INIT) || \
    defined (GPIO_D_DRIVE_INIT) || \
    defined (GPIO_D_DR_INIT) || \
    defined (GPIO_D_IENR_INIT) || \
    defined (GPIO_D_IPOLR_INIT) || \
    defined (GPIO_D_PER_INIT) || \
    defined (GPIO_D_PPMODE_INIT) || \
    defined (GPIO_D_PUR_INIT)
#define GPIO_D_INIT_USED 1
#endif

#if defined (GPIO_E_DDR_INIT) || \
    defined (GPIO_E_DRIVE_INIT) || \
    defined (GPIO_E_DR_INIT) || \
    defined (GPIO_E_IENR_INIT) || \
    defined (GPIO_E_IPOLR_INIT) || \
    defined (GPIO_E_PER_INIT) || \
    defined (GPIO_E_PPMODE_INIT) || \
    defined (GPIO_E_PUR_INIT)
#define GPIO_E_INIT_USED 1
#endif

#if defined (GPIO_F_DDR_INIT) || \
    defined (GPIO_F_DRIVE_INIT) || \
    defined (GPIO_F_DR_INIT) || \
    defined (GPIO_F_IENR_INIT) || \
    defined (GPIO_F_IPOLR_INIT) || \
    defined (GPIO_F_PER_INIT) || \
    defined (GPIO_F_PPMODE_INIT) || \
    defined (GPIO_F_PUR_INIT)
#define GPIO_F_INIT_USED 1
#endif

#if defined (PWM_A_PMCCR_INIT) || \
    defined (PWM_A_PMCFG_INIT) || \
    defined (PWM_A_PMCTL_INIT) || \
    defined (PWM_A_PMDEADTM0_INIT) || \
    defined (PWM_A_PMDEADTM1_INIT) || \
    defined (PWM_A_PMDEADTM_INIT) || \
    defined (PWM_A_PMDISMAP1_INIT) || \
    defined (PWM_A_PMDISMAP2_INIT) || \
    defined (PWM_A_PMFCTL_INIT) || \
    defined (PWM_A_PMICCR_INIT) || \
    defined (PWM_A_PMOUT_INIT) || \
    defined (PWM_A_PMSRC_INIT) || \
    defined (PWM_A_SYNC_INIT) || \
    defined (PWM_A_FFILT0_INIT) || \
    defined (PWM_A_FFILT1_INIT) || \
    defined (PWM_A_FFILT2_INIT) || \
    defined (PWM_A_FFILT3_INIT) || \
    defined (PWM_A_PWMCM_INIT) || \
    defined (PWM_A_PWMVAL0_INIT) || \
    defined (PWM_A_PWMVAL1_INIT) || \
    defined (PWM_A_PWMVAL2_INIT) || \
    defined (PWM_A_PWMVAL3_INIT) || \
    defined (PWM_A_PWMVAL4_INIT) || \
    defined (PWM_A_PWMVAL5_INIT)
#define PWM_A_INIT_USED 1
#endif

#if defined (PWM_B_PMCCR_INIT) || \
    defined (PWM_B_PMCFG_INIT) || \
    defined (PWM_B_PMCTL_INIT) || \
    defined (PWM_B_PMDEADTM0_INIT) || \
    defined (PWM_B_PMDEADTM1_INIT) || \
    defined (PWM_B_PMDEADTM_INIT) || \
    defined (PWM_B_PMDISMAP1_INIT) || \
    defined (PWM_B_PMDISMAP2_INIT) || \
    defined (PWM_B_PMFCTL_INIT) || \
    defined (PWM_B_PMICCR_INIT) || \
    defined (PWM_B_PMOUT_INIT) || \
    defined (PWM_B_PMSRC_INIT) || \
    defined (PWM_B_SYNC_INIT) || \
    defined (PWM_B_FFILT0_INIT) || \
    defined (PWM_B_FFILT1_INIT) || \
    defined (PWM_B_FFILT2_INIT) || \
    defined (PWM_B_FFILT3_INIT) || \
    defined (PWM_B_PWMCM_INIT) || \
    defined (PWM_B_PWMVAL0_INIT) || \
    defined (PWM_B_PWMVAL1_INIT) || \
    defined (PWM_B_PWMVAL2_INIT) || \
    defined (PWM_B_PWMVAL3_INIT) || \
    defined (PWM_B_PWMVAL4_INIT) || \
    defined (PWM_B_PWMVAL5_INIT)
#define PWM_B_INIT_USED 1
#endif

#if defined (PWM_PMCCR_INIT) || \
    defined (PWM_PMCFG_INIT) || \
    defined (PWM_PMCTL_INIT) || \
    defined (PWM_PMDEADTM0_INIT) || \
    defined (PWM_PMDEADTM1_INIT) || \
    defined (PWM_PMDEADTM_INIT) || \
    defined (PWM_PMDISMAP1_INIT) || \
    defined (PWM_PMDISMAP2_INIT) || \
    defined (PWM_PMFCTL_INIT) || \
    defined (PWM_PMICCR_INIT) || \
    defined (PWM_PMOUT_INIT) || \
    defined (PWM_PMSRC_INIT) || \
    defined (PWM_SYNC_INIT) || \
    defined (PWM_FFILT0_INIT) || \
    defined (PWM_FFILT1_INIT) || \
    defined (PWM_FFILT2_INIT) || \
    defined (PWM_FFILT3_INIT) || \
    defined (PWM_PWMCM_INIT) || \
    defined (PWM_PWMVAL0_INIT) || \
    defined (PWM_PWMVAL1_INIT) || \
    defined (PWM_PWMVAL2_INIT) || \
    defined (PWM_PWMVAL3_INIT) || \
    defined (PWM_PWMVAL4_INIT) || \
    defined (PWM_PWMVAL5_INIT)
#define PWM_INIT_USED 1
#endif

#if defined (QT_A0_CMP1_INIT) || \
    defined (QT_A0_CMP2_INIT) || \
    defined (QT_A0_CMPLD1_INIT) || \
    defined (QT_A0_CMPLD2_INIT) || \
    defined (QT_A0_CNTR_INIT) || \
    defined (QT_A0_COMSCR_INIT) || \
    defined (QT_A0_CTRL_INIT) || \
    defined (QT_A0_LOAD_INIT) || \
    defined (QT_A0_FILT_INIT) || \
    defined (QT_A0_ENBL_INIT) || \
    defined (QT_A0_SCR_INIT)
#define QT_A0_INIT_USED 1
#endif

#if defined (QT_A1_CMP1_INIT) || \
    defined (QT_A1_CMP2_INIT) || \
    defined (QT_A1_CMPLD1_INIT) || \
    defined (QT_A1_CMPLD2_INIT) || \
    defined (QT_A1_CNTR_INIT) || \
    defined (QT_A1_COMSCR_INIT) || \
    defined (QT_A1_CTRL_INIT) || \
    defined (QT_A1_LOAD_INIT) || \
    defined (QT_A1_FILT_INIT) || \
    defined (QT_A1_SCR_INIT)
#define QT_A1_INIT_USED 1
#endif

#if defined (QT_A2_CMP1_INIT) || \
    defined (QT_A2_CMP2_INIT) || \
    defined (QT_A2_CMPLD1_INIT) || \
    defined (QT_A2_CMPLD2_INIT) || \
    defined (QT_A2_CNTR_INIT) || \
    defined (QT_A2_COMSCR_INIT) || \
    defined (QT_A2_CTRL_INIT) || \
    defined (QT_A2_LOAD_INIT) || \
    defined (QT_A2_FILT_INIT) || \
    defined (QT_A2_SCR_INIT)
#define QT_A2_INIT_USED 1
#endif

#if defined (QT_A3_CMP1_INIT) || \
    defined (QT_A3_CMP2_INIT) || \
    defined (QT_A3_CMPLD1_INIT) || \
    defined (QT_A3_CMPLD2_INIT) || \
    defined (QT_A3_CNTR_INIT) || \
    defined (QT_A3_COMSCR_INIT) || \
    defined (QT_A3_CTRL_INIT) || \
    defined (QT_A3_LOAD_INIT) || \
    defined (QT_A3_FILT_INIT) || \
    defined (QT_A3_SCR_INIT)
#define QT_A3_INIT_USED 1
#endif

#if defined (QT_B0_CMP1_INIT) || \
    defined (QT_B0_CMP2_INIT) || \
    defined (QT_B0_CMPLD1_INIT) || \
    defined (QT_B0_CMPLD2_INIT) || \
    defined (QT_B0_CNTR_INIT) || \
    defined (QT_B0_COMSCR_INIT) || \
    defined (QT_B0_CTRL_INIT) || \
    defined (QT_B0_LOAD_INIT) || \
    defined (QT_B0_FILT_INIT) || \
    defined (QT_B0_ENBL_INIT) || \
    defined (QT_B0_SCR_INIT)
#define QT_B0_INIT_USED 1
#endif

#if defined (QT_B1_CMP1_INIT) || \
    defined (QT_B1_CMP2_INIT) || \
    defined (QT_B1_CMPLD1_INIT) || \
    defined (QT_B1_CMPLD2_INIT) || \
    defined (QT_B1_CNTR_INIT) || \
    defined (QT_B1_COMSCR_INIT) || \
    defined (QT_B1_CTRL_INIT) || \
    defined (QT_B1_LOAD_INIT) || \
    defined (QT_B1_FILT_INIT) || \
    defined (QT_B1_SCR_INIT)
#define QT_B1_INIT_USED 1
#endif

#if defined (QT_B2_CMP1_INIT) || \
    defined (QT_B2_CMP2_INIT) || \
    defined (QT_B2_CMPLD1_INIT) || \
    defined (QT_B2_CMPLD2_INIT) || \
    defined (QT_B2_CNTR_INIT) || \
    defined (QT_B2_COMSCR_INIT) || \
    defined (QT_B2_CTRL_INIT) || \
    defined (QT_B2_LOAD_INIT) || \
    defined (QT_B2_FILT_INIT) || \
    defined (QT_B2_SCR_INIT)
#define QT_B2_INIT_USED 1
#endif

#if defined (QT_B3_CMP1_INIT) || \
    defined (QT_B3_CMP2_INIT) || \
    defined (QT_B3_CMPLD1_INIT) || \
    defined (QT_B3_CMPLD2_INIT) || \
    defined (QT_B3_CNTR_INIT) || \
    defined (QT_B3_COMSCR_INIT) || \
    defined (QT_B3_CTRL_INIT) || \
    defined (QT_B3_LOAD_INIT) || \
    defined (QT_B3_FILT_INIT) || \
    defined (QT_B3_SCR_INIT)
#define QT_B3_INIT_USED 1
#endif

#if defined (QT_C0_CMP1_INIT) || \
    defined (QT_C0_CMP2_INIT) || \
    defined (QT_C0_CMPLD1_INIT) || \
    defined (QT_C0_CMPLD2_INIT) || \
    defined (QT_C0_CNTR_INIT) || \
    defined (QT_C0_COMSCR_INIT) || \
    defined (QT_C0_CTRL_INIT) || \
    defined (QT_C0_LOAD_INIT) || \
    defined (QT_C0_FILT_INIT) || \
    defined (QT_C0_ENBL_INIT) || \
    defined (QT_C0_SCR_INIT)
#define QT_C0_INIT_USED 1
#endif

#if defined (QT_C1_CMP1_INIT) || \
    defined (QT_C1_CMP2_INIT) || \
    defined (QT_C1_CMPLD1_INIT) || \
    defined (QT_C1_CMPLD2_INIT) || \
    defined (QT_C1_CNTR_INIT) || \
    defined (QT_C1_COMSCR_INIT) || \
    defined (QT_C1_CTRL_INIT) || \
    defined (QT_C1_LOAD_INIT) || \
    defined (QT_C1_FILT_INIT) || \
    defined (QT_C1_SCR_INIT)
#define QT_C1_INIT_USED 1
#endif

#if defined (QT_C2_CMP1_INIT) || \
    defined (QT_C2_CMP2_INIT) || \
    defined (QT_C2_CMPLD1_INIT) || \
    defined (QT_C2_CMPLD2_INIT) || \
    defined (QT_C2_CNTR_INIT) || \
    defined (QT_C2_COMSCR_INIT) || \
    defined (QT_C2_CTRL_INIT) || \
    defined (QT_C2_LOAD_INIT) || \
    defined (QT_C2_FILT_INIT) || \
    defined (QT_C2_SCR_INIT)
#define QT_C2_INIT_USED 1
#endif

#if defined (QT_C3_CMP1_INIT) || \
    defined (QT_C3_CMP2_INIT) || \
    defined (QT_C3_CMPLD1_INIT) || \
    defined (QT_C3_CMPLD2_INIT) || \
    defined (QT_C3_CNTR_INIT) || \
    defined (QT_C3_COMSCR_INIT) || \
    defined (QT_C3_CTRL_INIT) || \
    defined (QT_C3_LOAD_INIT) || \
    defined (QT_C3_FILT_INIT) || \
    defined (QT_C3_SCR_INIT)
#define QT_C3_INIT_USED 1
#endif

#if defined (QT_D0_CMP1_INIT) || \
    defined (QT_D0_CMP2_INIT) || \
    defined (QT_D0_CMPLD1_INIT) || \
    defined (QT_D0_CMPLD2_INIT) || \
    defined (QT_D0_CNTR_INIT) || \
    defined (QT_D0_COMSCR_INIT) || \
    defined (QT_D0_CTRL_INIT) || \
    defined (QT_D0_LOAD_INIT) || \
    defined (QT_D0_FILT_INIT) || \
    defined (QT_D0_ENBL_INIT) || \
    defined (QT_D0_SCR_INIT)
#define QT_D0_INIT_USED 1
#endif

#if defined (QT_D1_CMP1_INIT) || \
    defined (QT_D1_CMP2_INIT) || \
    defined (QT_D1_CMPLD1_INIT) || \
    defined (QT_D1_CMPLD2_INIT) || \
    defined (QT_D1_CNTR_INIT) || \
    defined (QT_D1_COMSCR_INIT) || \
    defined (QT_D1_CTRL_INIT) || \
    defined (QT_D1_LOAD_INIT) || \
    defined (QT_D1_FILT_INIT) || \
    defined (QT_D1_SCR_INIT)
#define QT_D1_INIT_USED 1
#endif

#if defined (QT_D2_CMP1_INIT) || \
    defined (QT_D2_CMP2_INIT) || \
    defined (QT_D2_CMPLD1_INIT) || \
    defined (QT_D2_CMPLD2_INIT) || \
    defined (QT_D2_CNTR_INIT) || \
    defined (QT_D2_COMSCR_INIT) || \
    defined (QT_D2_CTRL_INIT) || \
    defined (QT_D2_LOAD_INIT) || \
    defined (QT_D2_FILT_INIT) || \
    defined (QT_D2_SCR_INIT)
#define QT_D2_INIT_USED 1
#endif

#if defined (QT_D3_CMP1_INIT) || \
    defined (QT_D3_CMP2_INIT) || \
    defined (QT_D3_CMPLD1_INIT) || \
    defined (QT_D3_CMPLD2_INIT) || \
    defined (QT_D3_CNTR_INIT) || \
    defined (QT_D3_COMSCR_INIT) || \
    defined (QT_D3_CTRL_INIT) || \
    defined (QT_D3_LOAD_INIT) || \
    defined (QT_D3_FILT_INIT) || \
    defined (QT_D3_SCR_INIT)
#define QT_D3_INIT_USED 1
#endif

#if defined (QT_0_CMP1_INIT) || \
    defined (QT_0_CMP2_INIT) || \
    defined (QT_0_CMPLD1_INIT) || \
    defined (QT_0_CMPLD2_INIT) || \
    defined (QT_0_CNTR_INIT) || \
    defined (QT_0_COMSCR_INIT) || \
    defined (QT_0_CTRL_INIT) || \
    defined (QT_0_LOAD_INIT) || \
    defined (QT_0_FILT_INIT) || \
    defined (QT_0_ENBL_INIT) || \
    defined (QT_0_SCR_INIT)
#define QT_0_INIT_USED 1
#endif

#if defined (QT_1_CMP1_INIT) || \
    defined (QT_1_CMP2_INIT) || \
    defined (QT_1_CMPLD1_INIT) || \
    defined (QT_1_CMPLD2_INIT) || \
    defined (QT_1_CNTR_INIT) || \
    defined (QT_1_COMSCR_INIT) || \
    defined (QT_1_CTRL_INIT) || \
    defined (QT_1_LOAD_INIT) || \
    defined (QT_1_FILT_INIT) || \
    defined (QT_1_SCR_INIT)
#define QT_1_INIT_USED 1
#endif

#if defined (QT_2_CMP1_INIT) || \
    defined (QT_2_CMP2_INIT) || \
    defined (QT_2_CMPLD1_INIT) || \
    defined (QT_2_CMPLD2_INIT) || \
    defined (QT_2_CNTR_INIT) || \
    defined (QT_2_COMSCR_INIT) || \
    defined (QT_2_CTRL_INIT) || \
    defined (QT_2_LOAD_INIT) || \
    defined (QT_2_FILT_INIT) || \
    defined (QT_2_SCR_INIT)
#define QT_2_INIT_USED 1
#endif

#if defined (QT_3_CMP1_INIT) || \
    defined (QT_3_CMP2_INIT) || \
    defined (QT_3_CMPLD1_INIT) || \
    defined (QT_3_CMPLD2_INIT) || \
    defined (QT_3_CNTR_INIT) || \
    defined (QT_3_COMSCR_INIT) || \
    defined (QT_3_CTRL_INIT) || \
    defined (QT_3_LOAD_INIT) || \
    defined (QT_3_FILT_INIT) || \
    defined (QT_3_SCR_INIT)
#define QT_3_INIT_USED 1
#endif

#if defined (SCI_0_SCIBR_INIT) || \
    defined (SCI_0_SCICR2_INIT) || \
    defined (SCI_0_SCICR_INIT)
#define SCI_0_INIT_USED 1
#endif

#if defined (SCI_1_SCIBR_INIT) || \
    defined (SCI_1_SCICR2_INIT) || \
    defined (SCI_1_SCICR_INIT)
#define SCI_1_INIT_USED 1
#endif

#if defined (SPI_0_SPDSCR_INIT) || \
    defined (SPI_0_SPDSR_INIT) || \
    defined (SPI_0_FIFO_INIT) || \
    defined (SPI_0_DELAY_INIT) || \
    defined (SPI_0_SPSCR_INIT)
#define SPI_0_INIT_USED 1
#endif

#if defined (SPI_1_SPDSCR_INIT) || \
    defined (SPI_1_SPDSR_INIT) || \
    defined (SPI_1_FIFO_INIT) || \
    defined (SPI_1_DELAY_INIT) || \
    defined (SPI_1_SPSCR_INIT)
#define SPI_1_INIT_USED 1
#endif

#if defined (SPI_SPDSCR_INIT) || \
    defined (SPI_SPDSR_INIT) || \
    defined (SPI_FIFO_INIT) || \
    defined (SPI_DELAY_INIT) || \
    defined (SPI_SPSCR_INIT)
#define SPI_INIT_USED 1
#endif

#if defined (PIT_MOD_INIT) || \
    defined (PIT_CTRL_INIT)
#define PIT_INIT_USED 1
#endif

#if defined (PIT_0_MOD_INIT) || \
    defined (PIT_0_CTRL_INIT)
#define PIT_0_INIT_USED 1
#endif

#if defined (PIT_1_MOD_INIT) || \
    defined (PIT_1_CTRL_INIT)
#define PIT_1_INIT_USED 1
#endif

#if defined (PIT_2_MOD_INIT) || \
    defined (PIT_2_CTRL_INIT)
#define PIT_2_INIT_USED 1
#endif

#if defined (DAC_0_CTRL_INIT) || \
    defined (DAC_0_DATA_INIT) || \
    defined (DAC_0_STEP_INIT) || \
    defined (DAC_0_MINVAL_INIT) || \
    defined (DAC_0_MAXVAL_INIT)
#define DAC_0_INIT_USED 1
#endif

#if defined (DAC_1_CTRL_INIT) || \
    defined (DAC_1_DATA_INIT) || \
    defined (DAC_1_STEP_INIT) || \
    defined (DAC_1_MINVAL_INIT) || \
    defined (DAC_1_MAXVAL_INIT)
#define DAC_1_INIT_USED 1
#endif

#if defined (CMP_A_CTRL_INIT) || \
    defined (CMP_A_FILT_INIT)
#define CMP_A_INIT_USED 1
#endif

#if defined (CMP_B_CTRL_INIT) || \
    defined (CMP_B_FILT_INIT)
#define CMP_B_INIT_USED 1
#endif

#if defined (HSCMP_0_CR0_INIT) || \
    defined (HSCMP_0_CR1_INIT) || \
    defined (HSCMP_0_FPR_INIT) || \
    defined (HSCMP_0_SCR_INIT) || \
    defined (HSCMP_0_PCR_INIT)
#define HSCMP_0_INIT_USED 1
#endif

#if defined (HSCMP_1_CR0_INIT) || \
    defined (HSCMP_1_CR1_INIT) || \
    defined (HSCMP_1_FPR_INIT) || \
    defined (HSCMP_1_SCR_INIT) || \
    defined (HSCMP_1_PCR_INIT)
#define HSCMP_1_INIT_USED 1
#endif

#if defined (HSCMP_2_CR0_INIT) || \
    defined (HSCMP_2_CR1_INIT) || \
    defined (HSCMP_2_FPR_INIT) || \
    defined (HSCMP_2_SCR_INIT) || \
    defined (HSCMP_2_PCR_INIT)
#define HSCMP_2_INIT_USED 1
#endif

#endif


