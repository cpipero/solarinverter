/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  adc.h
*
* $Date:      Feb-13-2007$
*
* $Version:   2.3.41.0$
*
* Description: Header file for the ADC low-level driver
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  ADC_VERSION_1 .. 56F83xx devices, see MC56F8300UM.pdf
*  ADC_VERSION_2 .. 56F801x devices, see MC56F8000RM.pdf
*  ADC_VERSION_3 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*
*****************************************************************************/

#ifndef __ADC_H
#define __ADC_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before adc.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
* The Analog-to-Digital Converter (ADC) consists of two separate and complete ADCs,
* each with their own sample and hold circuits. A common digital control module
* configures and controls the functioning of these ADCs. 
*
* The ADC device driver interface uses "ioctl" call to control specific ADC functions
* during operation. For details see "ioctl" call.
*
******************************************************************************/

/************************************************************
* ADC module identifiers
*************************************************************/

#ifdef ADCA_BASE
#define ADC_A  (&ArchIO.AdcA)
#endif

#ifdef ADCB_BASE
#define ADC_B  (&ArchIO.AdcB)
#endif

/* single ("anonymous") module on some devices */
#ifdef ADC_BASE
#define ADC    (&ArchIO.Adc)
#endif

/*************************************************************
* arch.h should define device-specific information about ADC
**************************************************************/

#if !defined(ADC_VERSION)
#error ADC not properly described in arch.h (old Quick_Start version?)
#endif

/**************************************************************
* Configuration items for appconfig.h (init values, ...),
**************************************************************/

/* Configuration items for appconfig.h  *

    ADC_A_ADCR1_INIT    // control reg 1 
    ADC_A_ADCR2_INIT    // control reg 2    
    ADC_A_ADZCC_INIT    // zero cross control reg
    ADC_A_ADLST1_INIT   // channel list reg 1
    ADC_A_ADLST2_INIT   // channel list reg 2
    ADC_A_ADSDIS_INIT   // disable reg
    ADC_A_ADCPOWER_INIT // power control reg

    ADC_A_ADLLMT0_INIT  // low limit regs
    ADC_A_ADLLMT1_INIT 
    ADC_A_ADLLMT2_INIT 
    ADC_A_ADLLMT3_INIT 
    ADC_A_ADLLMT4_INIT 
    ADC_A_ADLLMT5_INIT 
    ADC_A_ADLLMT6_INIT 
    ADC_A_ADLLMT7_INIT 

    ADC_A_ADHLMT0_INIT  // high limit regs
    ADC_A_ADHLMT1_INIT  
    ADC_A_ADHLMT2_INIT  
    ADC_A_ADHLMT3_INIT  
    ADC_A_ADHLMT4_INIT  
    ADC_A_ADHLMT5_INIT  
    ADC_A_ADHLMT6_INIT  
    ADC_A_ADHLMT7_INIT  

    ADC_A_ADOFS0_INIT   // offset regs
    ADC_A_ADOFS1_INIT   
    ADC_A_ADOFS2_INIT   
    ADC_A_ADOFS3_INIT   
    ADC_A_ADOFS4_INIT   
    ADC_A_ADOFS5_INIT   
    ADC_A_ADOFS6_INIT   
    ADC_A_ADOFS7_INIT   


    // dtto for ADC_B


  #define INTERRUPT_VECTOR_ADDR_yy  // specify interrupt handler routine
  #define INT_PRIORITY_LEVEL_yy     // interrupt level : (INTC_DISABLED, INTC_LEVEL0, ... INTC_LEVEL2)

  where:
         yy  is interrupt vector number
            e.g. On 56F8346
                76 - ADC A Zero Crossing or Limit Error
                75 - ADC B Zero Crossing or Limit Error
                74 - ADC A Conversion Complete
                73 - ADC B Conversion Complete

                    on 56F8013 (ADC_VERSION_2)
                40 - ADC_A ADA Conversion Complete
                41 - ADC_A ADB Conversion Complete

*/

/***************************************************
* ADC Ioctl commands
****************************************************/
/* command                      |        Param     */

/* ADC control register 1 commands */
#define ADC_INIT                    /* NULL */
#define ADC_START                   /* NULL , ADC_VERSION_2: ADC_CONVERTER_0 / ADC_CONVERTER_1 */
#define ADC_STOP                    /* ADC_ON/ADC_OFF, ADC_VERSION_2: ADC_ON_CONVERTER_0 / ADC_ON_CONVERTER_1 / ADC_OFF_CONVERTER_0 / ADC_OFF_CONVERTER_1*/
#define ADC_SYNC                    /* ADC_ON/ADC_OFF, ADC_VERSION_2: ADC_ON_CONVERTER_0 / ADC_ON_CONVERTER_1 / ADC_OFF_CONVERTER_0 / ADC_OFF_CONVERTER_1*/
#define ADC_SET_CHANNEL_CONFIG      /* ADC_ANxx_ANyy_SE/ADC_ANxx_ANyy_DIFF */
#define ADC_SET_SCAN_MODE           /* ADC_SCAN_xxx */
#define ADC_INT_ENABLE              /* ADC_END_OF_SCAN | ADC_ZERO_CROSS | ADC_LOW_LIMIT | ADC_HIGH_LIMIT, ADC_VERSION_2: ADC_END_OF_SCAN_CONVERTER_0 / ADC_END_OF_SCAN_CONVERTER_1) */
#define ADC_INT_DISABLE             /* ADC_END_OF_SCAN | ADC_ZERO_CROSS | ADC_LOW_LIMIT | ADC_HIGH_LIMIT, ADC_VERSION_2: ADC_END_OF_SCAN_CONVERTER_0 / ADC_END_OF_SCAN_CONVERTER_1)  */
#define ADC_TEST_INT_ENABLED        /* ADC_END_OF_SCAN | ADC_ZERO_CROSS | ADC_LOW_LIMIT | ADC_HIGH_LIMIT, ADC_VERSION_2: ADC_END_OF_SCAN_CONVERTER_0 / ADC_END_OF_SCAN_CONVERTER_1)  */

/* ADC control register 2 set */
#define ADC_SET_DIVISOR             /* one of ADC_DIVxx or 5-bit UWord16 value */

/* write ADC zero cross register */
#define ADC_WRITE_ZERO_CROSS_CNTRL  /* ADC_Sx_ZC_DISABLE | ADC_Sx_ZC_POSITIVE_NEGATIVE | ADC_Sx_ZC_NEGATIVE_POSITIVE | ADC_Sx_ZC_ANY_CROSS */
#define ADC_ZERO_CROSS_CH0          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH1          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH2          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH3          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH4          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH5          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH6          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */
#define ADC_ZERO_CROSS_CH7          /* ADC_ZC_DISABLE / ADC_ZC_POS2NEG / ADC_ZC_NEG2POS / ADC_ZC_BOTH */

/* write ADC channel list registers */
#define ADC_SET_LIST_SAMPLE0        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE1        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE2        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE3        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE4        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE5        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE6        /* one of ADC_CHx, VERSION_2+: one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE7        /* one of ADC_CHX, VERSION_2+: one of ADC_ANAx/ADC_ANBx */

#if ADC_VERSION >= 3
#define ADC_SET_LIST_SAMPLE8        /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE9        /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE10       /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE11       /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE12       /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE13       /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE14       /* one of ADC_ANAx/ADC_ANBx */
#define ADC_SET_LIST_SAMPLE15       /* one of ADC_ANAx/ADC_ANBx */
#endif

/* write ADC sample disable register */
#define ADC_WRITE_SAMPLE_DISABLE    /* ADC_VERSION_1:  number 0-7 as UWord16
                                    /* ADC_VERSION_2+: any combination of ADC_SAMPLEx or ADC_ENABLE_ALL */

/* read ADC result register */
#define ADC_READ_SAMPLE             /* sample number 0-7 as UWord16 (0-15 on VERSION_3) */

/* read eight ADC result registers */
#define ADC_READ_ALL_SAMPLES        /* adc_tBuff; note: always reads 8 samples, even on VERSION_3 */

/* read ADC status register */
#define ADC_READ_STATUS             /* NULL */

/* write ADC low limit registers */
#define ADC_WRITE_LOW_LIMIT0        /* UWord16 : low limit (sample 0) */
#define ADC_WRITE_LOW_LIMIT1        /* UWord16 : low limit (sample 1) */
#define ADC_WRITE_LOW_LIMIT2        /* UWord16 : low limit (sample 2) */
#define ADC_WRITE_LOW_LIMIT3        /* UWord16 : low limit (sample 3) */
#define ADC_WRITE_LOW_LIMIT4        /* UWord16 : low limit (sample 4) */
#define ADC_WRITE_LOW_LIMIT5        /* UWord16 : low limit (sample 5) */
#define ADC_WRITE_LOW_LIMIT6        /* UWord16 : low limit (sample 6) */
#define ADC_WRITE_LOW_LIMIT7        /* UWord16 : low limit (sample 7) */

/* read ADC low limit register x */
#define ADC_READ_LOW_LIMIT          /* UWord16: sample number (0-7) */

/* write ADC high limit registers */
#define ADC_WRITE_HIGH_LIMIT0       /* UWord16 : high limit (sample 0) */
#define ADC_WRITE_HIGH_LIMIT1       /* UWord16 : high limit (sample 1) */
#define ADC_WRITE_HIGH_LIMIT2       /* UWord16 : high limit (sample 2) */
#define ADC_WRITE_HIGH_LIMIT3       /* UWord16 : high limit (sample 3) */
#define ADC_WRITE_HIGH_LIMIT4       /* UWord16 : high limit (sample 4) */
#define ADC_WRITE_HIGH_LIMIT5       /* UWord16 : high limit (sample 5) */
#define ADC_WRITE_HIGH_LIMIT6       /* UWord16 : high limit (sample 6) */
#define ADC_WRITE_HIGH_LIMIT7       /* UWord16 : high limit (sample 7) */

/* read ADC high limit register x */
#define ADC_READ_HIGH_LIMIT         /* UWord16: sample number (0-7) */

/* write ADC offset registers */
#define ADC_WRITE_OFFSET0           /* UWord16 : offset (sample 0) */
#define ADC_WRITE_OFFSET1           /* UWord16 : offset (sample 1) */
#define ADC_WRITE_OFFSET2           /* UWord16 : offset (sample 2) */
#define ADC_WRITE_OFFSET3           /* UWord16 : offset (sample 3) */
#define ADC_WRITE_OFFSET4           /* UWord16 : offset (sample 4) */
#define ADC_WRITE_OFFSET5           /* UWord16 : offset (sample 5) */
#define ADC_WRITE_OFFSET6           /* UWord16 : offset (sample 6) */
#define ADC_WRITE_OFFSET7           /* UWord16 : offset (sample 7) */

/* read ADC offset register x */
#define ADC_READ_OFFSET             /* UWord16: sample number (0-7) */

/* read ADC limit status register */
#define ADC_READ_LIMIT_STATUS       /* NULL */
/* read ADC zero crossing status register */
#define ADC_READ_ZERO_CROSS_STATUS  /* NULL */

/* test ADC status register bits - can be used directly in codition */
/* if it is used in assignement then it returns bit value in original position */
#define ADC_GET_STATUS_CIP          /* NULL (on VERSION_2+, optionally use combination of ADC_CONVERTER_x) */
#define ADC_GET_STATUS_EOSI         /* NULL (on VERSION_2+, optionally use combination of ADC_CONVERTER_x) */
#define ADC_GET_STATUS_ZCI          /* NULL */
#define ADC_GET_STATUS_LLMTI        /* NULL */
#define ADC_GET_STATUS_HLMTI        /* NULL */
#define ADC_GET_STATUS_RDY          /* UWord16 : sample number (0-7) (0-15 on ADC_VERSION_3+) */

/* test ADC limit status register bits */
#define ADC_GET_LIMIT_STATUS_LLS    /* UWord16 : sample number (0-7) */
#define ADC_GET_LIMIT_STATUS_HLS    /* UWord16 : sample number (0-7) */

#define ADC_GET_ZERO_CROSS_STATUS_ZCS   /* UWord16 : sample number (0-7) */

/* clear ADC status registers flags */
#define ADC_CLEAR_STATUS_EOSI           /* NULL (on VERSION_2+, optionally use combination of ADC_CONVERTER_x) */
#define ADC_CLEAR_STATUS_ZCI            /* NULL */
#define ADC_CLEAR_STATUS_LLMTI          /* NULL */
#define ADC_CLEAR_STATUS_HLMTI          /* NULL */

/* clearing bits in Limit Status, Zero Crossing Status reg individaully */
#define ADC_CLEAR_LIMIT_STATUS_HLS      /* UWord16 : sample number (0-7) */
#define ADC_CLEAR_LIMIT_STATUS_LLS      /* UWord16 : sample number (0-7) */
#define ADC_CLEAR_LIMIT_STATUS_BITS     /* any combination of ADC_LLSx or ADC_HLSx */
#define ADC_CLEAR_ZERO_CROSS_STATUS_ZCS /* UWord16 : sample number (0-7) */ 

/* Power Control Register */
#define ADC_POWER_DOWN             /* ADC_CONVERTER_0 | ADC_CONVERTER_1 | ADC_VOLTAGE_REF */
#define ADC_POWER_UP               /* ADC_CONVERTER_0 | ADC_CONVERTER_1 | ADC_VOLTAGE_REF */
#define ADC_POWER_SAVE_MODE        /* ADC_ON / ADC_OFF */
#define ADC_SET_POWER_UP_DELAY     /* number 0-63 as UWord16 */
#define ADC_GET_POWER_STATUS       /* ADC_CONVERTER_0 | ADC_CONVERTER_1 | ADC_VOLTAGE_REF */
#define ADC_READ_POWER_CONTROL_REG /* NULL */

/* calibration register ADC_CAL */
#if ADC_VERSION == 1
#define ADC_CALIB_ENABLE              /* ADC_CONVERTER_0 | ADC_CONVERTER_1 */
#define ADC_CALIB_DISABLE             /* ADC_CONVERTER_0 | ADC_CONVERTER_1 */
#define ADC_SET_CONVERTER0_CALIB_REF  /* ADC_VCAL_L / ADC_VCAL_H */
#define ADC_SET_CONVERTER1_CALIB_REF  /* ADC_VCAL_L / ADC_VCAL_H */
#endif /* ADC_VERSION_1 */

/****************************************************************************
* ADC ADC_VERSION_2-only commands
*****************************************************************************/

#if ADC_VERSION >= 2
/* ADC control register 2 set */
#define ADC_SIMULT                      /* ADC_ON / ADC_OFF */
/* Power Control Register */
#define ADC_AUTO_POWERDOWN_MODE         /* ADC_ON / ADC_OFF */
#define ADC_AUTO_STANDBY_MODE           /* ADC_ON / ADC_OFF */
#endif

#if ADC_VERSION == 2

/* calibration register ADC_CAL */
#define ADC_SET_VREFH_SOURCE            /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */
#define ADC_SET_VREFL_SOURCE            /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */

#elif ADC_VERSION >= 3

/* calibration register ADC_CAL */
#define ADC_SET_VREFH1_SOURCE           /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */
#define ADC_SET_VREFL1_SOURCE           /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */
#define ADC_SET_VREFH0_SOURCE           /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */
#define ADC_SET_VREFL0_SOURCE           /* ADC_VREF_SRC_INTERNAL / ADC_VREF_SRC_EXTERNAL */
#define ADC_SET_CALIB_SOURCE            /* ADC_DACx_TO_ANxx(_PASSTHRU) */ 

#endif /* ADC_VERSION >= 3 */



/****************************************************************************
* ADC command parameters
*****************************************************************************/

#define ADC_ENABLE  1
#define ADC_DISABLE 0

#if ADC_VERSION >= 2
#define ADC_ENABLE_CONVERTER_0          ADC_ENABLE
#define ADC_ENABLE_CONVERTER_1          (ADC_ENABLE | 0x10)
#define ADC_DISABLE_CONVERTER_0         ADC_DISABLE
#define ADC_DISABLE_CONVERTER_1         (ADC_DISABLE | 0x10)
#endif

#define ADC_ON  1
#define ADC_OFF 0

#if ADC_VERSION >= 2
#define ADC_ON_CONVERTER_0                  (ADC_ON)
#define ADC_ON_CONVERTER_1                  (ADC_ON|0x10)
#define ADC_OFF_CONVERTER_0                 ADC_OFF
#define ADC_OFF_CONVERTER_1                 (ADC_OFF|0x10)
#endif

/* divisor values */
#define ADC_DIV2   0
#define ADC_DIV4   1
#define ADC_DIV6   2
#define ADC_DIV8   3
#define ADC_DIV10  4
#define ADC_DIV12  5
#define ADC_DIV14  6
#define ADC_DIV16  7
#define ADC_DIV18  8
#define ADC_DIV20  9
#define ADC_DIV22  10
#define ADC_DIV24  11
#define ADC_DIV26  12
#define ADC_DIV28  13
#define ADC_DIV30  14
#define ADC_DIV32  15
#define ADC_DIV34  16
#define ADC_DIV36  17
#define ADC_DIV38  18
#define ADC_DIV40  19
#define ADC_DIV42  20
#define ADC_DIV44  21
#define ADC_DIV46  22
#define ADC_DIV48  23
#define ADC_DIV50  24
#define ADC_DIV52  25
#define ADC_DIV54  26
#define ADC_DIV56  27
#define ADC_DIV58  28
#define ADC_DIV60  29
#define ADC_DIV62  30
#define ADC_DIV64  31

/* interrupts */
#define ADC_END_OF_SCAN ADC_ADCR1_EOSIE 
#define ADC_ZERO_CROSS  ADC_ADCR1_ZCIE  
#define ADC_LOW_LIMIT   ADC_ADCR1_LLMTIE
#define ADC_HIGH_LIMIT  ADC_ADCR1_HLMTIE

#if ADC_VERSION >= 2
#define ADC_END_OF_SCAN_CONVERTER_0 ADC_ADCR1_EOSIE 
#define ADC_END_OF_SCAN_CONVERTER_1 (((UWord32)(ADC_ADCR1_EOSIE)) << 16)
#endif
                
/* zero crossing modes */
#define ADC_ZC_DISABLE 0    
#define ADC_ZC_POS2NEG 1
#define ADC_ZC_NEG2POS 2
#define ADC_ZC_BOTH    3

/* channel numbers */
#if ADC_VERSION == 1
#define ADC_CH0 0
#define ADC_CH1 1
#define ADC_CH2 2
#define ADC_CH3 3
#define ADC_CH4 4
#define ADC_CH5 5
#define ADC_CH6 6
#define ADC_CH7 7
#endif
#if ADC_VERSION >= 2
#define ADC_ANA0 0
#define ADC_ANA1 1
#define ADC_ANA2 2
#define ADC_ANA3 3
#define ADC_ANB0 4
#define ADC_ANB1 5
#define ADC_ANB2 6
#define ADC_ANB3 7
#endif
#if ADC_VERSION >= 3
#define ADC_ANA4 8
#define ADC_ANA5 9
#define ADC_ANA6 10
#define ADC_ANA7 11
#define ADC_ANB4 12
#define ADC_ANB5 13
#define ADC_ANB6 14
#define ADC_ANB7 15
#endif

/* channel configurations */
#if ADC_VERSION == 1
#define ADC_AN0_AN1_SE      0x0100
#define ADC_AN0_AN1_DIFF    0x0101
#define ADC_AN2_AN3_SE      0x0200
#define ADC_AN2_AN3_DIFF    0x0202
#define ADC_AN4_AN5_SE      0x0400
#define ADC_AN4_AN5_DIFF    0x0404
#define ADC_AN6_AN7_SE      0x0800
#define ADC_AN6_AN7_DIFF    0x0808
#endif
#if ADC_VERSION >= 2
#define ADC_ANA0_ANA1_SE    0x0100
#define ADC_ANA0_ANA1_DIFF  0x0101
#define ADC_ANA2_ANA3_SE    0x0200
#define ADC_ANA2_ANA3_DIFF  0x0202
#define ADC_ANB0_ANB1_SE    0x0400
#define ADC_ANB0_ANB1_DIFF  0x0404
#define ADC_ANB2_ANB3_SE    0x0800
#define ADC_ANB2_ANB3_DIFF  0x0808
#endif
#if ADC_VERSION >= 3
#define ADC_ANA4_ANA5_SE    0x1000
#define ADC_ANA4_ANA5_DIFF  0x1010
#define ADC_ANA6_ANA7_SE    0x2000
#define ADC_ANA6_ANA7_DIFF  0x2020
#define ADC_ANB4_ANB5_SE    0x4000
#define ADC_ANB4_ANB5_DIFF  0x4040
#define ADC_ANB6_ANB7_SE    0x8000
#define ADC_ANB6_ANB7_DIFF  0x8080
#endif

/* adc modes */
#define ADC_SCAN_ONCE_SEQUENTIAL    ADC_ADCR1_SMODE_ONCESEQ
#define ADC_SCAN_ONCE_SIMULTANEOUS  ADC_ADCR1_SMODE_ONCESIM
#define ADC_SCAN_LOOP_SEQUENTIAL    ADC_ADCR1_SMODE_LOOPSEQ
#define ADC_SCAN_LOOP_SIMULTANEOUS  ADC_ADCR1_SMODE_LOOPSIM
#define ADC_SCAN_TRIG_SEQUENTIAL    ADC_ADCR1_SMODE_TRIGSEQ
#define ADC_SCAN_TRIG_SIMULTANEOUS  ADC_ADCR1_SMODE_TRIGSIM

/* bit mask for testing of the status registers ADC_READ_STATUS (RDYx bits) */
#define ADC_S0      ADC_ADSTAT_RDY0
#define ADC_S1      ADC_ADSTAT_RDY1
#define ADC_S2      ADC_ADSTAT_RDY2
#define ADC_S3      ADC_ADSTAT_RDY3
#define ADC_S4      ADC_ADSTAT_RDY4
#define ADC_S5      ADC_ADSTAT_RDY5
#define ADC_S6      ADC_ADSTAT_RDY6
#define ADC_S7      ADC_ADSTAT_RDY7

/* bit values for limit status registers ADC_READ_LIMIT_STATUS and ADC_CLEAR_LIMIT_STATUS_BITS */
#define ADC_LLS0    ADC_ADLSTAT_LLS0
#define ADC_LLS1    ADC_ADLSTAT_LLS1
#define ADC_LLS2    ADC_ADLSTAT_LLS2
#define ADC_LLS3    ADC_ADLSTAT_LLS3
#define ADC_LLS4    ADC_ADLSTAT_LLS4
#define ADC_LLS5    ADC_ADLSTAT_LLS5
#define ADC_LLS6    ADC_ADLSTAT_LLS6
#define ADC_LLS7    ADC_ADLSTAT_LLS7
#define ADC_LLS_ALL (ADC_LLS0 | ADC_LLS1 | ADC_LLS2 | ADC_LLS3 |\
                     ADC_LLS4 | ADC_LLS5 | ADC_LLS6 | ADC_LLS7)

#define ADC_HLS0    ADC_ADLSTAT_HLS0
#define ADC_HLS1    ADC_ADLSTAT_HLS1
#define ADC_HLS2    ADC_ADLSTAT_HLS2
#define ADC_HLS3    ADC_ADLSTAT_HLS3
#define ADC_HLS4    ADC_ADLSTAT_HLS4
#define ADC_HLS5    ADC_ADLSTAT_HLS5
#define ADC_HLS6    ADC_ADLSTAT_HLS6
#define ADC_HLS7    ADC_ADLSTAT_HLS7
#define ADC_HLS_ALL (ADC_HLS0 | ADC_HLS1 | ADC_HLS2 | ADC_HLS3 |\
                     ADC_HLS4 | ADC_HLS5 | ADC_HLS6 | ADC_HLS7)

/* sample disable register */
#if ADC_VERSION == 2
#define ADC_SAMPLE0     (ADC_ADSDIS_DS0 | 0x8000)
#define ADC_SAMPLE1     (ADC_ADSDIS_DS1 | 0x8000)
#define ADC_SAMPLE2     (ADC_ADSDIS_DS2 | 0x8000)
#define ADC_SAMPLE3     (ADC_ADSDIS_DS3 | 0x8000)
#define ADC_SAMPLE4     (ADC_ADSDIS_DS4 | 0x8000)
#define ADC_SAMPLE5     (ADC_ADSDIS_DS5 | 0x8000)
#define ADC_SAMPLE6     (ADC_ADSDIS_DS6 | 0x8000)
#define ADC_SAMPLE7     (ADC_ADSDIS_DS7 | 0x8000)
#define ADC_ENABLE_ALL  0x8000
#elif ADC_VERSION >= 3
#define ADC_SAMPLE0     (ADC_ADSDIS_DS0  | 0x80000000)
#define ADC_SAMPLE1     (ADC_ADSDIS_DS1  | 0x80000000)
#define ADC_SAMPLE2     (ADC_ADSDIS_DS2  | 0x80000000)
#define ADC_SAMPLE3     (ADC_ADSDIS_DS3  | 0x80000000)
#define ADC_SAMPLE4     (ADC_ADSDIS_DS4  | 0x80000000)
#define ADC_SAMPLE5     (ADC_ADSDIS_DS5  | 0x80000000)
#define ADC_SAMPLE6     (ADC_ADSDIS_DS6  | 0x80000000)
#define ADC_SAMPLE7     (ADC_ADSDIS_DS7  | 0x80000000)
#define ADC_SAMPLE8     (ADC_ADSDIS_DS8  | 0x80000000)
#define ADC_SAMPLE9     (ADC_ADSDIS_DS9  | 0x80000000)
#define ADC_SAMPLE10    (ADC_ADSDIS_DS10 | 0x80000000)
#define ADC_SAMPLE11    (ADC_ADSDIS_DS11 | 0x80000000)
#define ADC_SAMPLE12    (ADC_ADSDIS_DS12 | 0x80000000)
#define ADC_SAMPLE13    (ADC_ADSDIS_DS13 | 0x80000000)
#define ADC_SAMPLE14    (ADC_ADSDIS_DS14 | 0x80000000)
#define ADC_SAMPLE15    (ADC_ADSDIS_DS15 | 0x80000000)
#define ADC_ENABLE_ALL  0x80000000
#endif
 
/* zero crossing control register - masks for samples and crossing types */
/* sample 0 */
#define ADC_S0_ZC_DISABLE              0x0000
#define ADC_S0_ZC_POSITIVE_NEGATIVE    0x0001
#define ADC_S0_ZC_NEGATIVE_POSITIVE    0x0002
#define ADC_S0_ZC_ANY_CROSS            0x0003
/* sample 1 */
#define ADC_S1_ZC_DISABLE              0x0000
#define ADC_S1_ZC_POSITIVE_NEGATIVE    0x0004
#define ADC_S1_ZC_NEGATIVE_POSITIVE    0x0008
#define ADC_S1_ZC_ANY_CROSS            0x000C
/* sample 2 */
#define ADC_S2_ZC_DISABLE              0x0000
#define ADC_S2_ZC_POSITIVE_NEGATIVE    0x0010
#define ADC_S2_ZC_NEGATIVE_POSITIVE    0x0020
#define ADC_S2_ZC_ANY_CROSS            0x0030
/* sample 3 */
#define ADC_S3_ZC_DISABLE              0x0000
#define ADC_S3_ZC_POSITIVE_NEGATIVE    0x0040
#define ADC_S3_ZC_NEGATIVE_POSITIVE    0x0080
#define ADC_S3_ZC_ANY_CROSS            0x00C0
/* sample 4 */
#define ADC_S4_ZC_DISABLE              0x0000
#define ADC_S4_ZC_POSITIVE_NEGATIVE    0x0100
#define ADC_S4_ZC_NEGATIVE_POSITIVE    0x0200
#define ADC_S4_ZC_ANY_CROSS            0x0300
/* sample 5 */
#define ADC_S5_ZC_DISABLE              0x0000
#define ADC_S5_ZC_POSITIVE_NEGATIVE    0x0400
#define ADC_S5_ZC_NEGATIVE_POSITIVE    0x0800
#define ADC_S5_ZC_ANY_CROSS            0x0C00
/* sample 6 */
#define ADC_S6_ZC_DISABLE              0x0000
#define ADC_S6_ZC_POSITIVE_NEGATIVE    0x1000
#define ADC_S6_ZC_NEGATIVE_POSITIVE    0x2000
#define ADC_S6_ZC_ANY_CROSS            0x3000
/* sample 7 */
#define ADC_S7_ZC_DISABLE              0x0000
#define ADC_S7_ZC_POSITIVE_NEGATIVE    0x4000
#define ADC_S7_ZC_NEGATIVE_POSITIVE    0x8000
#define ADC_S7_ZC_ANY_CROSS            0xC000

/* power control */
#define ADC_CONVERTER_0         ADC_ADCPOWER_PD0
#define ADC_CONVERTER_1         ADC_ADCPOWER_PD1
#define ADC_VOLTAGE_REF         ADC_ADCPOWER_PD2

/* calibration */
#define ADC_VCAL_L 0
#define ADC_VCAL_H 1

#if ADC_VERSION >= 2
#define ADC_VREF_SRC_INTERNAL 0
#define ADC_VREF_SRC_EXTERNAL 1
#endif

/* calibration source */
#if ADC_VERSION >= 2
#define ADC_ANA7_NORMAL              0x0500
#define ADC_ANA7_FROM_DAC0           0x0501
#define ADC_ANA7_FROM_DAC0_PASSTHRU  0x0505
#define ADC_ANB7_NORMAL              0x0a00
#define ADC_ANB7_FROM_DAC1           0x0a02
#define ADC_ANB7_FROM_DAC1_PASSTHRU  0x0a0a
#endif

/****************************************************************************
* obsolete parameters (do not use in new designs)
*****************************************************************************/

/* channel list registers - masks for samples & inputs */
/* sample 0 */
#define ADC_AN0_S0      0x0000
#define ADC_AN1_S0      0x0001
#define ADC_AN2_S0      0x0002
#define ADC_AN3_S0      0x0003
#define ADC_AN4_S0      0x0004
#define ADC_AN5_S0      0x0005
#define ADC_AN6_S0      0x0006
#define ADC_AN7_S0      0x0007
/* sample 1 */
#define ADC_AN0_S1      0x0000
#define ADC_AN1_S1      0x0010
#define ADC_AN2_S1      0x0020
#define ADC_AN3_S1      0x0030
#define ADC_AN4_S1      0x0040
#define ADC_AN5_S1      0x0050
#define ADC_AN6_S1      0x0060
#define ADC_AN7_S1      0x0070
/* sample 2 */
#define ADC_AN0_S2      0x0000
#define ADC_AN1_S2      0x0100
#define ADC_AN2_S2      0x0200
#define ADC_AN3_S2      0x0300
#define ADC_AN4_S2      0x0400
#define ADC_AN5_S2      0x0500
#define ADC_AN6_S2      0x0600
#define ADC_AN7_S2      0x0700
/* sample 3 */
#define ADC_AN0_S3      0x0000
#define ADC_AN1_S3      0x1000
#define ADC_AN2_S3      0x2000
#define ADC_AN3_S3      0x3000
#define ADC_AN4_S3      0x4000
#define ADC_AN5_S3      0x5000
#define ADC_AN6_S3      0x6000
#define ADC_AN7_S3      0x7000
/* sample 4 */
#define ADC_AN0_S4      0x0000
#define ADC_AN1_S4      0x0001
#define ADC_AN2_S4      0x0002
#define ADC_AN3_S4      0x0003
#define ADC_AN4_S4      0x0004
#define ADC_AN5_S4      0x0005
#define ADC_AN6_S4      0x0006
#define ADC_AN7_S4      0x0007
/* sample 5 */
#define ADC_AN0_S5      0x0000
#define ADC_AN1_S5      0x0010
#define ADC_AN2_S5      0x0020
#define ADC_AN3_S5      0x0030
#define ADC_AN4_S5      0x0040
#define ADC_AN5_S5      0x0050
#define ADC_AN6_S5      0x0060
#define ADC_AN7_S5      0x0070
/* sample 6 */
#define ADC_AN0_S6      0x0000
#define ADC_AN1_S6      0x0100
#define ADC_AN2_S6      0x0200
#define ADC_AN3_S6      0x0300
#define ADC_AN4_S6      0x0400
#define ADC_AN5_S6      0x0500
#define ADC_AN6_S6      0x0600
#define ADC_AN7_S6      0x0700
/* sample 7 */
#define ADC_AN0_S7      0x0000
#define ADC_AN1_S7      0x1000
#define ADC_AN2_S7      0x2000
#define ADC_AN3_S7      0x3000
#define ADC_AN4_S7      0x4000
#define ADC_AN5_S7      0x5000
#define ADC_AN6_S7      0x6000
#define ADC_AN7_S7      0x7000


/****************************************************************************
* register and bit names used in the ioctl functions below
*****************************************************************************/

/* control register (ADCR1) */
#define ADC_ADCR1_STOP                 0x4000
#define ADC_ADCR1_START                0x2000
#define ADC_ADCR1_SYNC                 0x1000
#define ADC_ADCR1_EOSIE                0x0800    
#define ADC_ADCR1_ZCIE                 0x0400    
#define ADC_ADCR1_LLMTIE               0x0200
#define ADC_ADCR1_HLMTIE               0x0100
#define ADC_ADCR1_SMODE_MASK           0x0007
#define ADC_ADCR1_SMODE_ONCESEQ        0x0000
#define ADC_ADCR1_SMODE_ONCESIM        0x0001
#define ADC_ADCR1_SMODE_LOOPSEQ        0x0002
#define ADC_ADCR1_SMODE_LOOPSIM        0x0003
#define ADC_ADCR1_SMODE_TRIGSEQ        0x0004
#define ADC_ADCR1_SMODE_TRIGSIM        0x0005
#if ADC_VERSION == 1
#define ADC_ADCR1_CHNCFG_MASK          0x00f0
#define ADC_ADCR1_CHNCFG_AN01_DIFF     0x0010
#define ADC_ADCR1_CHNCFG_AN23_DIFF     0x0020
#define ADC_ADCR1_CHNCFG_AN45_DIFF     0x0040
#define ADC_ADCR1_CHNCFG_AN67_DIFF     0x0080
#elif ADC_VERSION == 2
#define ADC_ADCR1_CHNCFG_MASK          0x00f0
#define ADC_ADCR1_CHNCFG_ANA01_DIFF    0x0010
#define ADC_ADCR1_CHNCFG_ANA23_DIFF    0x0020
#define ADC_ADCR1_CHNCFG_ANB01_DIFF    0x0040
#define ADC_ADCR1_CHNCFG_ANB23_DIFF    0x0080
#else /* ADC_VERSION >= 3 */
#define ADC_ADCR1_CHNCFG_L_MASK        0x00f0
#define ADC_ADCR1_CHNCFG_L_ANA01_DIFF  0x0010
#define ADC_ADCR1_CHNCFG_L_ANA23_DIFF  0x0020
#define ADC_ADCR1_CHNCFG_L_ANB01_DIFF  0x0040
#define ADC_ADCR1_CHNCFG_L_ANB23_DIFF  0x0080
#endif

/* control register (ADCR2) */
#define ADC_ADCR2_DIV_MASK             0x001f
#if ADC_VERSION >= 2
#define ADC_ADCR2_STOP                 0x4000
#define ADC_ADCR2_START                0x2000
#define ADC_ADCR2_SYNC                 0x1000
#define ADC_ADCR2_EOSIE                0x0800    
#define ADC_ADCR2_SIMULT               0x0020
#endif
#if ADC_VERSION >= 3
#define ADC_ADCR2_CHNCFG_H_MASK        0x03c0
#define ADC_ADCR2_CHNCFG_H_ANA45_DIFF  0x0040
#define ADC_ADCR2_CHNCFG_H_ANA67_DIFF  0x0080
#define ADC_ADCR2_CHNCFG_H_ANB45_DIFF  0x0100
#define ADC_ADCR2_CHNCFG_H_ANB67_DIFF  0x0200
#endif

/* sample disable register (ADSDIS) */
#define ADC_ADSDIS_DS0            0x0001
#define ADC_ADSDIS_DS1            0x0002
#define ADC_ADSDIS_DS2            0x0004
#define ADC_ADSDIS_DS3            0x0008
#define ADC_ADSDIS_DS4            0x0010
#define ADC_ADSDIS_DS5            0x0020
#define ADC_ADSDIS_DS6            0x0040
#define ADC_ADSDIS_DS7            0x0080
#if ADC_VERSION >= 3
#define ADC_ADSDIS_DS8            0x0100
#define ADC_ADSDIS_DS9            0x0200
#define ADC_ADSDIS_DS10           0x0400
#define ADC_ADSDIS_DS11           0x0800
#define ADC_ADSDIS_DS12           0x1000
#define ADC_ADSDIS_DS13           0x2000
#define ADC_ADSDIS_DS14           0x4000
#define ADC_ADSDIS_DS15           0x8000
#endif

/* status register ADSTAT */

#define ADC_ADSTAT_ZCI            0x0400    
#define ADC_ADSTAT_LLMTI          0x0200
#define ADC_ADSTAT_HLMTI          0x0100
#define ADC_ADSTAT_RDY7           0x0080
#define ADC_ADSTAT_RDY6           0x0040
#define ADC_ADSTAT_RDY5           0x0020
#define ADC_ADSTAT_RDY4           0x0010
#define ADC_ADSTAT_RDY3           0x0008
#define ADC_ADSTAT_RDY2           0x0004
#define ADC_ADSTAT_RDY1           0x0002
#define ADC_ADSTAT_RDY0           0x0001
#if ADC_VERSION == 1
#define ADC_ADSTAT_CIP            0x8000    
#define ADC_ADSTAT_EOSI           0x0800    
#else /* ADC_VERSION >= 2 */
#define ADC_ADSTAT_CIP0           0x8000    
#define ADC_ADSTAT_EOSI0          0x0800    
#define ADC_ADSTAT_CIP1           0x4000    
#define ADC_ADSTAT_EOSI1          0x1000    
#endif

/* limit status register ADLSTAT */
#define ADC_ADLSTAT_HLS7          0x8000
#define ADC_ADLSTAT_HLS6          0x4000
#define ADC_ADLSTAT_HLS5          0x2000
#define ADC_ADLSTAT_HLS4          0x1000
#define ADC_ADLSTAT_HLS3          0x0800
#define ADC_ADLSTAT_HLS2          0x0400
#define ADC_ADLSTAT_HLS1          0x0200
#define ADC_ADLSTAT_HLS0          0x0100
#define ADC_ADLSTAT_LLS7          0x0080
#define ADC_ADLSTAT_LLS6          0x0040
#define ADC_ADLSTAT_LLS5          0x0020
#define ADC_ADLSTAT_LLS4          0x0010
#define ADC_ADLSTAT_LLS3          0x0008
#define ADC_ADLSTAT_LLS2          0x0004
#define ADC_ADLSTAT_LLS1          0x0002
#define ADC_ADLSTAT_LLS0          0x0001

/* zero cross status register ZCSTAT */
#define ADC_ADZCSTAT_ZCS7          0x0080
#define ADC_ADZCSTAT_ZCS6          0x0040
#define ADC_ADZCSTAT_ZCS5          0x0020
#define ADC_ADZCSTAT_ZCS4          0x0010
#define ADC_ADZCSTAT_ZCS3          0x0008
#define ADC_ADZCSTAT_ZCS2          0x0004
#define ADC_ADZCSTAT_ZCS1          0x0002
#define ADC_ADZCSTAT_ZCS0          0x0001

/* power control register ADCPOWER */
#define ADC_ADCPOWER_PSTS2        0x1000
#define ADC_ADCPOWER_PSTS1        0x0800
#define ADC_ADCPOWER_PSTS0        0x0400
#define ADC_ADCPOWER_PUDELAY_MASK 0x03f0
#define ADC_ADCPOWER_PSM          0x0008
#define ADC_ADCPOWER_PD2          0x0004
#define ADC_ADCPOWER_PD1          0x0002
#define ADC_ADCPOWER_PD0          0x0001
#if ADC_VERSION >= 2
#define ADC_ADCPOWER_ASB          0x8000
#define ADC_ADCPOWER_APD          0x0008
#endif

/* calibration register ADC_CAL */
#if ADC_VERSION == 1
#define ADC_CAL_CRS1              0x0008
#define ADC_CAL_CAL1              0x0004
#define ADC_CAL_CRS0              0x0002
#define ADC_CAL_CAL0              0x0001
#endif
#if ADC_VERSION == 2
#define ADC_CAL_SEL_VREFH         0x8000
#define ADC_CAL_SEL_VREFLO        0x4000
#endif
#if ADC_VERSION >= 3
#define ADC_CAL_SEL_VREFH1        0x8000
#define ADC_CAL_SEL_VREFLO1       0x4000
#define ADC_CAL_SEL_VREFH0        0x2000
#define ADC_CAL_SEL_VREFLO0       0x1000
#define ADC_CAL_SEL_TEST1         0x0008
#define ADC_CAL_SEL_TEST0         0x0004
#define ADC_CAL_SEL_DAC1          0x0002
#define ADC_CAL_SEL_DAC0          0x0001
#endif

/* results buffer */
typedef UWord16 adc_tBuff[8];

/****************************************************************************
* ADC ioctl macro implementation
*****************************************************************************/

/***********************************************************************
* ADC init
***********************************************************************/

void adcInit(arch_sADC *pAdcBase);
#define ioctlADC_INIT(pAdcBase, param) adcInit(pAdcBase)

/***********************************************************************
* ADC Control Register
***********************************************************************/

/* start ADC conversion */
#ifdef ADC_VERSION_1

/* start ADC conversion */
#define ioctlADC_START(pAdcBase, param) \
  periphBitSet(ADC_ADCR1_START, &((pAdcBase)->adctl1))
                      
/* stop ADC conversion */
#define ioctlADC_STOP(pAdcBase, param) \
 if (param) periphBitSet(ADC_ADCR1_STOP, &((pAdcBase)->adctl1)); \
 else periphBitClear(ADC_ADCR1_STOP, &((pAdcBase)->adctl1))
 
/* switch on/off ADC conversion starting by SYNC (spec. timer output) */
#define ioctlADC_SYNC(pAdcBase, param) \
 if (param) periphBitSet(ADC_ADCR1_SYNC, &((pAdcBase)->adctl1)); \
 else periphBitClear(ADC_ADCR1_SYNC, &((pAdcBase)->adctl1))

/* enable/disable interrupt on the end of the ADC conversion */
#define ioctlADC_END_OF_SCAN_INT(pAdcBase, param) \
  if (param) periphBitSet(ADC_ADCR1_EOSIE, &((pAdcBase)->adctl1)); \
  else periphBitClear(ADC_ADCR1_EOSIE, &((pAdcBase)->adctl1))

/* enable interrupts */
#define ioctlADC_INT_ENABLE(pAdcBase, param)        \
  periphBitSet(param, &((pAdcBase)->adctl1))

/* enable interrupts */
#define ioctlADC_INT_DISABLE(pAdcBase, param)       \
  periphBitClear(param, &((pAdcBase)->adctl1))

/* test if given interrupts are enabled */
#define ioctlADC_TEST_INT_ENABLED(pAdcBase, param)  \
  periphBitTest(param, &((pAdcBase)->adctl1))

/* enable interrupts */
#define ioctlADC_INT_SELECT(pAdcBase, param)        \
  periphBitGrpRS (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE, \
    param, &((pAdcBase)->adctl1))
  
#else /* ADC_VERSION >= 2 */

#define ioctlADC_START(pAdcBase, param) \
  if((((UWord16)(param)) == ADC_CONVERTER_0) || (((UWord16)(param)) == 0)) \
    periphBitSet(ADC_ADCR1_START, &((pAdcBase)->adctl1)); \
  else if(((UWord16)(param)) == ADC_CONVERTER_1) \
    periphBitSet(ADC_ADCR2_START, &((pAdcBase)->adctl2))
                      
/* stop ADC conversion */
#define ioctlADC_STOP(pAdcBase, param) \
if((param) & 0x10) \
    if((param) & 0x1) periphBitSet(ADC_ADCR2_STOP, &((pAdcBase)->adctl2)); \
    else periphBitClear(ADC_ADCR2_STOP, &((pAdcBase)->adctl2)); \
else \
    if((param) & 0x1) periphBitSet(ADC_ADCR1_STOP, &((pAdcBase)->adctl1)); \
    else periphBitClear(ADC_ADCR1_STOP, &((pAdcBase)->adctl1))
 
/* switch on/off ADC conversion starting by SYNC (spec. timer output) */
#define ioctlADC_SYNC(pAdcBase, param) \
if((param) & 0x10) \
    if ((param) & 0x1) periphBitSet(ADC_ADCR2_SYNC, &((pAdcBase)->adctl2)); \
    else periphBitClear(ADC_ADCR2_SYNC, &((pAdcBase)->adctl2)); \
else \
    if((param) & 0x1) periphBitSet(ADC_ADCR1_SYNC, &((pAdcBase)->adctl1)); \
    else periphBitClear(ADC_ADCR1_SYNC, &((pAdcBase)->adctl1))

/* enable/disable interrupt on the end of the ADC conversion */
#define ioctlADC_END_OF_SCAN_INT(pAdcBase, param) \
if ((param) & 0x10) \
  if ((param) & 0x1) periphBitSet(ADC_ADCR2_EOSIE, &((pAdcBase)->adctl2)); \
  else periphBitClear(ADC_ADCR2_EOSIE, &((pAdcBase)->adctl2)); \
else \
  if ((param) & 0x1) periphBitSet(ADC_ADCR1_EOSIE, &((pAdcBase)->adctl1)); \
  else periphBitClear(ADC_ADCR1_EOSIE, &((pAdcBase)->adctl1))

/* enable interrupts */
#define ioctlADC_INT_ENABLE(pAdcBase, param) { \
  if((param) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE)) \
    periphBitSet ((param) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE), &((pAdcBase)->adctl1)); \
  if(((param) >> 16) & (ADC_ADCR2_EOSIE)) \
    periphBitSet (((param) >> 16) & (ADC_ADCR2_EOSIE), &((pAdcBase)->adctl2)); }

/* disable interrupts */
#define ioctlADC_INT_DISABLE(pAdcBase, param) { \
  if((param) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE)) \
    periphBitClear ((param) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE), &((pAdcBase)->adctl1)); \
  if(((param) >> 16) & (ADC_ADCR2_EOSIE)) \
    periphBitClear (((param) >> 16) & (ADC_ADCR2_EOSIE), &((pAdcBase)->adctl2)); }

/* test if given interrupts are enabled */
#define ioctlADC_TEST_INT_ENABLED(pAdcBase, param) ( \
  ( ((param) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE)) ? \
    periphBitTest (((UWord16)(param)) & (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE), &((pAdcBase)->adctl1)) : 0 ) | \
  ( (((param) >> 16) & (ADC_ADCR2_EOSIE)) ? \
    periphBitTest (((UWord16)((param) >> 16)) & (ADC_ADCR2_EOSIE), &((pAdcBase)->adctl2)) : 0 ) )

/* enable/disable interrupts */
#define ioctlADC_INT_SELECT(pAdcBase, param) { \
  periphBitGrpRS (ADC_ADCR1_EOSIE | ADC_ADCR1_ZCIE | ADC_ADCR1_LLMTIE | ADC_ADCR1_HLMTIE, param, &((pAdcBase)->adctl1)); \
  periphBitGrpRS (ADC_ADCR2_EOSIE, (param) >> 16, &((pAdcBase)->adctl2)); }

#endif  /* ADC_VERSION */
  
/* enable/disable interrupt on ADC zero crossing */
#define ioctlADC_ZERO_CROSS_INT(pAdcBase, param) \
  if (param) periphBitSet(ADC_ADCR1_ZCIE, &((pAdcBase)->adctl1)); \
  else periphBitClear(ADC_ADCR1_ZCIE, &((pAdcBase)->adctl1))
  
/* enable/disable interrupt on ADC low limit compare */
#define ioctlADC_LOW_LIMIT_INT(pAdcBase, param) \
 if (param) periphBitSet(ADC_ADCR1_LLMTIE, &((pAdcBase)->adctl1)); \
 else periphBitClear(ADC_ADCR1_LLMTIE, &((pAdcBase)->adctl1))
 
/* enable/disable interrupt on ADC high limit compare */
#define ioctlADC_HIGH_LIMIT_INT(pAdcBase, param) \
 if (param) periphBitSet(ADC_ADCR1_HLMTIE, &((pAdcBase)->adctl1)); \
 else periphBitClear(ADC_ADCR1_HLMTIE, &((pAdcBase)->adctl1))

/* write to CHNCFG[3:0] bits in ADCR1 */
#if ADC_VERSION <= 2

#define ioctlADC_SET_CHANNEL_CONFIG(pAdcBase, param) \
  periphBitGrpSet(ADC_ADCR1_CHNCFG_MASK & (((param)>>8)<<4), (param)<<4, &((pAdcBase)->adctl1))
  
#else /* ADC_VERSION >= 3 */

#define ioctlADC_SET_CHANNEL_CONFIG(pAdcBase, param) { \
    if((param) & 0x0f00) periphBitGrpSet(ADC_ADCR1_CHNCFG_L_MASK & ((param)>>(8-4)), (param)<<4, &((pAdcBase)->adctl1)); \
    if((param) & 0xf000) periphBitGrpSet(ADC_ADCR2_CHNCFG_H_MASK & ((param)>>(12-6)), (param)<<(6-4), &((pAdcBase)->adctl2)); \
  }  
#endif /* ADC_VERSION  */

/* write to SMODE[2:0] bits in ADCR1 */
#define ioctlADC_SET_SCAN_MODE(pAdcBase, param) \
  periphBitGrpSet(ADC_ADCR1_SMODE_MASK, param, &((pAdcBase)->adctl1))

/* set ADC clock divisor select */
#define ioctlADC_SET_DIVISOR(pAdcBase, param) \
  periphBitGrpSet(ADC_ADCR2_DIV_MASK, param, &((pAdcBase)->adctl2))

/* switch on/off parallel scan mode  */ 
#if ADC_VERSION >= 2
#define ioctlADC_SIMULT(pAdcBase, param) \
  if (param) periphBitSet(ADC_ADCR2_SIMULT, &((pAdcBase)->adctl2)); \
  else periphBitClear(ADC_ADCR2_SIMULT, &((pAdcBase)->adctl2))
#endif

/***********************************************************************
* ADC zero crossing register
***********************************************************************/

/* set ADC zero crossing control register */
#define ioctlADC_WRITE_ZERO_CROSS_CNTRL(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adzcc))
  
/* individual zero-cross settings for each channel (added) */
#define ioctlADC_ZERO_CROSS_CH0(pAdcBase, param) \
  periphBitGrpSet(3 << 0, (UWord16) ((param)<<0), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH1(pAdcBase, param) \
  periphBitGrpSet(3 << 2, (UWord16) ((param)<<2), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH2(pAdcBase, param) \
  periphBitGrpSet(3 << 4, (UWord16) ((param)<<4), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH3(pAdcBase, param) \
  periphBitGrpSet(3 << 6, (UWord16) ((param)<<6), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH4(pAdcBase, param) \
  periphBitGrpSet(3 << 8, (UWord16) ((param)<<8), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH5(pAdcBase, param) \
  periphBitGrpSet(3 << 10, (UWord16) ((param)<<10), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH6(pAdcBase, param) \
  periphBitGrpSet(3 << 12, (UWord16) ((param)<<12), &((pAdcBase)->adzcc))
#define ioctlADC_ZERO_CROSS_CH7(pAdcBase, param) \
  periphBitGrpSet(3 << 14, (UWord16) ((param)<<14), &((pAdcBase)->adzcc))
  

/* set ADC channel list register (end-of-life) */
#define ioctlADC_WRITE_CHANNEL_LIST1(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adlst1))
#define ioctlADC_WRITE_CHANNEL_LIST2(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adlst2))
  
/* individual channel list manipulation for each channel (added) */
#define ioctlADC_SET_LIST_SAMPLE0(pAdcBase, param) \
  periphBitGrpSet(0xf << 0, (UWord16) ((param)<<0), &((pAdcBase)->adlst1))
#define ioctlADC_SET_LIST_SAMPLE1(pAdcBase, param) \
  periphBitGrpSet(0xf << 4, (UWord16) ((param)<<4), &((pAdcBase)->adlst1))
#define ioctlADC_SET_LIST_SAMPLE2(pAdcBase, param) \
  periphBitGrpSet(0xf << 8, (UWord16) ((param)<<8), &((pAdcBase)->adlst1))
#define ioctlADC_SET_LIST_SAMPLE3(pAdcBase, param) \
  periphBitGrpSet(0xf << 12, (UWord16) ((param)<<12), &((pAdcBase)->adlst1))
  
#define ioctlADC_SET_LIST_SAMPLE4(pAdcBase, param) \
  periphBitGrpSet(0xf << 0, (UWord16) ((param)<<0), &((pAdcBase)->adlst2))
#define ioctlADC_SET_LIST_SAMPLE5(pAdcBase, param) \
  periphBitGrpSet(0xf << 4, (UWord16) ((param)<<4), &((pAdcBase)->adlst2))
#define ioctlADC_SET_LIST_SAMPLE6(pAdcBase, param) \
  periphBitGrpSet(0xf << 8, (UWord16) ((param)<<8), &((pAdcBase)->adlst2))
#define ioctlADC_SET_LIST_SAMPLE7(pAdcBase, param) \
  periphBitGrpSet(0xf << 12, (UWord16) ((param)<<12), &((pAdcBase)->adlst2))

#if ADC_VERSION >= 3
#define ioctlADC_SET_LIST_SAMPLE8(pAdcBase, param) \
  periphBitGrpSet(0xf << 0, (UWord16) ((param)<<0), &((pAdcBase)->adlst3))
#define ioctlADC_SET_LIST_SAMPLE9(pAdcBase, param) \
  periphBitGrpSet(0xf << 4, (UWord16) ((param)<<4), &((pAdcBase)->adlst3))
#define ioctlADC_SET_LIST_SAMPLE10(pAdcBase, param) \
  periphBitGrpSet(0xf << 8, (UWord16) ((param)<<8), &((pAdcBase)->adlst3))
#define ioctlADC_SET_LIST_SAMPLE11(pAdcBase, param) \
  periphBitGrpSet(0xf << 12, (UWord16) ((param)<<12), &((pAdcBase)->adlst3))

#define ioctlADC_SET_LIST_SAMPLE12(pAdcBase, param) \
  periphBitGrpSet(0xf << 0, (UWord16) ((param)<<0), &((pAdcBase)->adlst4))
#define ioctlADC_SET_LIST_SAMPLE13(pAdcBase, param) \
  periphBitGrpSet(0xf << 4, (UWord16) ((param)<<4), &((pAdcBase)->adlst4))
#define ioctlADC_SET_LIST_SAMPLE14(pAdcBase, param) \
  periphBitGrpSet(0xf << 8, (UWord16) ((param)<<8), &((pAdcBase)->adlst4))
#define ioctlADC_SET_LIST_SAMPLE15(pAdcBase, param) \
  periphBitGrpSet(0xf << 12, (UWord16) ((param)<<12), &((pAdcBase)->adlst4))
#endif
  
/* ADC sample disable register */
#if ADC_VERSION == 1

#define ioctlADC_WRITE_SAMPLE_DISABLE(pAdcBase, param) \
  periphBitGrpSR(0x00FF, (1 << ((UWord16)(param))), &((pAdcBase)->adsdis))

#elif ADC_VERSION == 2

#define ioctlADC_WRITE_SAMPLE_DISABLE(pAdcBase, param) \
  if((param) & 0x8000)\
    periphBitGrpSR(0x00FF, (0x00FF & (UWord16)(param)), &((pAdcBase)->adsdis)); \
  else \
    periphBitGrpSR(0x00FF, (1 << ((UWord16)(param))), &((pAdcBase)->adsdis))

#else /* ADC_VERSION >= 3 */

#define ioctlADC_WRITE_SAMPLE_DISABLE(pAdcBase, param) \
  if((param) & 0xFFFF0000L)\
    periphBitGrpSR(0xFFFF, (0xFFFF & (UWord16)(param)), &((pAdcBase)->adsdis)); \
  else \
    periphBitGrpSR(0xFFFF, (1 << ((UWord16)(param))), &((pAdcBase)->adsdis))

#endif /* ADC_VERSION */

/* write ADC low limit register x */
#define ioctlADC_WRITE_LOW_LIMIT0(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[0]))
#define ioctlADC_WRITE_LOW_LIMIT1(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[1]))
#define ioctlADC_WRITE_LOW_LIMIT2(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[2]))
#define ioctlADC_WRITE_LOW_LIMIT3(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[3]))
#define ioctlADC_WRITE_LOW_LIMIT4(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[4]))
#define ioctlADC_WRITE_LOW_LIMIT5(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[5]))
#define ioctlADC_WRITE_LOW_LIMIT6(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[6]))
#define ioctlADC_WRITE_LOW_LIMIT7(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adllmt[7]))

/* read ADC low limit register x */
#define ioctlADC_READ_LOW_LIMIT(pAdcBase, param)  \
  periphMemRead(&((pAdcBase)->adllmt[param]))
  
/* set ADC high limit register x */
#define ioctlADC_WRITE_HIGH_LIMIT0(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[0]))
#define ioctlADC_WRITE_HIGH_LIMIT1(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[1]))
#define ioctlADC_WRITE_HIGH_LIMIT2(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[2]))
#define ioctlADC_WRITE_HIGH_LIMIT3(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[3]))
#define ioctlADC_WRITE_HIGH_LIMIT4(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[4]))
#define ioctlADC_WRITE_HIGH_LIMIT5(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[5]))
#define ioctlADC_WRITE_HIGH_LIMIT6(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[6]))
#define ioctlADC_WRITE_HIGH_LIMIT7(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adhlmt[7]))
                                          
/* read ADC high limit register x */
#define ioctlADC_READ_HIGH_LIMIT(pAdcBase, param)  \
  periphMemRead(&((pAdcBase)->adhlmt[param]))
                                          
/* write ADC offset register x */
#define ioctlADC_WRITE_OFFSET0(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[0]))
#define ioctlADC_WRITE_OFFSET1(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[1]))
#define ioctlADC_WRITE_OFFSET2(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[2]))
#define ioctlADC_WRITE_OFFSET3(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[3]))
#define ioctlADC_WRITE_OFFSET4(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[4]))
#define ioctlADC_WRITE_OFFSET5(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[5]))
#define ioctlADC_WRITE_OFFSET6(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[6]))
#define ioctlADC_WRITE_OFFSET7(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adofs[7]))

/* read ADC offset register x */
#define ioctlADC_READ_OFFSET(pAdcBase, param) \
 periphMemRead(&((pAdcBase)->adofs[param]))
                                                                                                                                                                                                                                                                 
/* reads samples from result registers */
/* one at a time, param is the number of the Result reg (0-7) */
#define ioctlADC_READ_SAMPLE(pAdcBase, param) \
  periphMemRead(&((pAdcBase)->adrslt[param]))

/* reads samples from result registers - all 8 to the buffer pointed by pParam */
inline void AdcRdResults(adc_tBuff buff,volatile UWord16 *reg) {
    int i; for(i=0; i<8; i++) *buff++ = periphMemRead(reg++); 
}
#define ioctlADC_READ_ALL_SAMPLES(pAdcBase, param) \
  AdcRdResults(param,((UWord16*)&((pAdcBase)->adrslt[0])))

/* read ADC status register */
#define ioctlADC_READ_STATUS(pAdcBase, param) \
  periphMemRead(&((pAdcBase)->adstat))

#if ADC_VERSION == 1

/* test some ADC status bits */
#define ioctlADC_GET_STATUS_CIP(pAdcBase, param) \
  periphBitTest(ADC_ADSTAT_CIP, &((pAdcBase)->adstat))

#define ioctlADC_GET_STATUS_EOSI(pAdcBase, param) \
  periphBitTest(ADC_ADSTAT_EOSI, &((pAdcBase)->adstat))

/* clear ADC status bit - end of scan interrupt flag (EOSI) */
#define ioctlADC_CLEAR_STATUS_EOSI(pAdcBase, param) \
  periphMemWrite(ADC_ADSTAT_EOSI, &((pAdcBase)->adstat))

#else /* ADC_VERSION >= 2 */

/* test some ADC status bits */
#define ioctlADC_GET_STATUS_CIP(pAdcBase, param) \
  periphBitTest(((((UWord16)(param) & ADC_CONVERTER_0) | ((UWord16)(param) == 0)) ? ADC_ADSTAT_CIP0 : 0 )| \
    ((((UWord16)(param)) & ADC_CONVERTER_1) ? ADC_ADSTAT_CIP1 : 0), &((pAdcBase)->adstat))
  
#define ioctlADC_GET_STATUS_EOSI(pAdcBase, param) \
  periphBitTest(((((UWord16)(param) & ADC_CONVERTER_0) | ((UWord16)(param) == 0)) ? ADC_ADSTAT_EOSI0 : 0 )| \
    ((((UWord16)(param)) & ADC_CONVERTER_1) ? ADC_ADSTAT_EOSI1 : 0), &((pAdcBase)->adstat))

/* clear ADC status bit - end of scan interrupt flag (EOSI) */
#define ioctlADC_CLEAR_STATUS_EOSI(pAdcBase, param) \
  periphMemWrite(((((UWord16)(param) & ADC_CONVERTER_0) | ((UWord16)(param) == 0)) ? ADC_ADSTAT_EOSI0 : 0 )| \
    ((((UWord16)(param)) & ADC_CONVERTER_1) ? ADC_ADSTAT_EOSI1 : 0), &((pAdcBase)->adstat))

#endif  /* ADC_VERSION */

#define ioctlADC_GET_STATUS_ZCI(pAdcBase, param) \
  periphBitTest(ADC_ADSTAT_ZCI, &((pAdcBase)->adstat))

#define ioctlADC_GET_STATUS_LLMTI(pAdcBase, param) \
  periphBitTest(ADC_ADSTAT_LLMTI, &((pAdcBase)->adstat))

#define ioctlADC_GET_STATUS_HLMTI(pAdcBase, param) \
  periphBitTest(ADC_ADSTAT_HLMTI, &((pAdcBase)->adstat))

/* test ADC status - ready channel x flag (RDYx), x should be immediate */
#if ADC_VERSION <= 2
#define ioctlADC_GET_STATUS_RDY(pAdcBase, param) \
  periphBitTest(1 << ((UWord16)(param)), &((pAdcBase)->adstat))
#else /* ADC_VERSION >= 3 */
#define ioctlADC_GET_STATUS_RDY(pAdcBase, param) \
  periphBitTest(1 << ((UWord16)(param)), &((pAdcBase)->cnrdy))
#endif

/* write ADC status register */
#define ioctlADC_WRITE_STATUS(pAdcBase, param) \
  periphMemWrite((UWord16) (param), &((pAdcBase)->adstat))

/* reads ADC limit status register - contains all sample limit flag bits */
#define ioctlADC_READ_LIMIT_STATUS(pAdcBase, param) \
  periphMemRead(&((pAdcBase)->adlstat))

/* test ADC limit status - low limit sample flag x (LLSx) - each sample has distinctive flag bit */
#define ioctlADC_GET_LIMIT_STATUS_LLS(pAdcBase, param) \
  periphBitTest(1 << ((UWord16)(param)), &((pAdcBase)->adlstat))

/* test ADC limit status - high limit sample flag x (HLSx) - each sample has distinctive flag bit */
#define ioctlADC_GET_LIMIT_STATUS_HLS(pAdcBase, param) \
  periphBitTest(1 << ((UWord16)(param)+8), &((pAdcBase)->adlstat))

/* reads ADC zero cross status register */
#define ioctlADC_READ_ZERO_CROSS_STATUS(pAdcBase, param) \
  periphMemRead(&((pAdcBase)->adzcstat))

/* test ADC zero cross status - zero cross sample flag x (ZCSx) */
#define ioctlADC_GET_ZERO_CROSS_STATUS_ZCS(pAdcBase, param) \
  periphBitTest(1 << ((UWord16)(param)), &((pAdcBase)->adzcstat))

/* clear ADC status bit - low limit interrupt flag (LLMTI) */
/* cleared indirectly by clearing all LLSx flags in limit status registers */
#define ioctlADC_CLEAR_STATUS_LLMTI(pAdcBase, param) \
  periphMemWrite(0x00FF, &((pAdcBase)->adlstat))

/* clear ADC status bit - high limit interrupt flag (HLMTI) */
/* cleared indirectly by clearing all HLSx flags in limit status registers */
#define ioctlADC_CLEAR_STATUS_HLMTI(pAdcBase, param) \
  periphMemWrite(0xFF00, &((pAdcBase)->adlstat))

/* clear ADC status bit - zero cross interrupt flag (ZCI) */
#define ioctlADC_CLEAR_STATUS_ZCI(pAdcBase, param) \
  periphMemWrite(0x00FF, &((pAdcBase)->adzcstat))

/* clear bits in ADC limit status - low limit sample flag x (LLSx) */
#define ioctlADC_CLEAR_LIMIT_STATUS_LLS(pAdcBase, param) \
  periphMemWrite(1 << ((UWord16)(param)), &((pAdcBase)->adlstat))

/* clear bits in ADC limit status - high limit sample flag x (HLSx) */
#define ioctlADC_CLEAR_LIMIT_STATUS_HLS(pAdcBase, param) \
  periphMemWrite(1 << ((UWord16)(param)+8), &((pAdcBase)->adlstat))

/* clear bits in ADC zero cross status - zero cross sample flag x (ZCSx) */
#define ioctlADC_CLEAR_ZERO_CROSS_STATUS_ZCS(pAdcBase, param) \
  periphMemWrite(1 << ((UWord16)(param)), &((pAdcBase)->adzcstat))

/* clear ADC any combination of limiting status bits */
#define ioctlADC_CLEAR_LIMIT_STATUS_BITS(pAdcBase, param) \
  periphMemWrite(param, &((pAdcBase)->adlstat))
 

/***********************************************************************
* ADC power control register (ADCPOWER)
***********************************************************************/

#define ioctlADC_POWER_DOWN(pAdcBase, param) \
  periphBitSet((UWord16)(param), &((pAdcBase)->adcpower))

#define ioctlADC_POWER_UP(pAdcBase, param) \
  periphBitClear((UWord16)(param), &((pAdcBase)->adcpower))

#define ioctlADC_POWER_SAVE_MODE(pAdcBase, param) \
  if(param) periphBitSet(ADC_ADCPOWER_PSM, &((pAdcBase)->adcpower)); \
  else periphBitClear(ADC_ADCPOWER_PSM, &((pAdcBase)->adcpower))

#define ioctlADC_SET_POWER_UP_DELAY(pAdcBase, param) \
  periphBitGrpSet(ADC_ADCPOWER_PUDELAY_MASK, ((UWord16)(param) << 4), &((pAdcBase)->adcpower))

#define ioctlADC_GET_POWER_STATUS(pAdcBase, param) \
  periphBitTest(((UWord16)(param) << 10), &((pAdcBase)->adcpower))

#define ioctlADC_READ_POWER_CONTROL_REG(pAdcBase, param) \
  periphMemRead(&((pAdcBase)->adcpower))

#if ADC_VERSION >= 2
#define ioctlADC_AUTO_POWERDOWN_MODE(pAdcBase, param) \
  if(param) periphBitSet(ADC_ADCPOWER_APD, &((pAdcBase)->adcpower)); \
  else periphBitClear(ADC_ADCPOWER_APD, &((pAdcBase)->adcpower))

#define ioctlADC_AUTO_STANDBY_MODE(pAdcBase, param) \
  if(param) periphBitSet(ADC_ADCPOWER_ASB, &((pAdcBase)->adcpower)); \
  else periphBitClear(ADC_ADCPOWER_ASB, &((pAdcBase)->adcpower))
#endif

/***********************************************************************
* ADC calibration register ADC_CAL
***********************************************************************/

#if ADC_VERSION == 1

#define ioctlADC_CALIB_ENABLE(pAdcBase, param) \
  periphBitSet((((param) & ADC_CONVERTER_0) ? ADC_CAL_CAL0 : 0) | \
               (((param) & ADC_CONVERTER_1) ? ADC_CAL_CAL1 : 0), &((pAdcBase)->adc_cal))
  
#define ioctlADC_CALIB_DISABLE(pAdcBase, param) \
  periphBitClear((((param) & ADC_CONVERTER_0) ? ADC_CAL_CAL0 : 0) | \
                 (((param) & ADC_CONVERTER_1) ? ADC_CAL_CAL1 : 0), &((pAdcBase)->adc_cal))

#define ioctlADC_SET_CONVERTER0_CALIB_REF(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_CRS0, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_CRS0, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_CONVERTER1_CALIB_REF(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_CRS1, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_CRS1, &((pAdcBase)->adc_cal))

#elif ADC_VERSION == 2

#define ioctlADC_SET_VREFH_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFH, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFH, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_VREFL_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFLO, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFLO, &((pAdcBase)->adc_cal))

#elif ADC_VERSION >= 3

#define ioctlADC_SET_VREFH0_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFH0, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFH0, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_VREFH1_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFH1, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFH1, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_VREFL0_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFLO0, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFLO0, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_VREFL1_SOURCE(pAdcBase, param) \
  if (param) periphBitSet(ADC_CAL_SEL_VREFLO1, &((pAdcBase)->adc_cal)); \
  else periphBitClear(ADC_CAL_SEL_VREFLO1, &((pAdcBase)->adc_cal))

#define ioctlADC_SET_CALIB_SOURCE(pAdcBase, param) \
  periphBitGrpSet((ADC_CAL_SEL_TEST1 | ADC_CAL_SEL_TEST0 | ADC_CAL_SEL_DAC1 | ADC_CAL_SEL_DAC0) & \
    ((param)>>8), ((param) & 0xff), &((pAdcBase)->adc_cal))

#endif /* ADC_VERSION >= 3 */

 
#ifdef __cplusplus
}
#endif

#endif
