/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  intctarget.h
*
* $Date:      Feb-6-2007$
*
* $Version:   2.3.6.0$
*
* Description: Header file for the MC56F802x/803x device specific implementation 
*              of the interrupt controller driver
*
*****************************************************************************/

#ifndef __INTCTARGET_H
#define __INTCTARGET_H

/* bitmask of system interrupts which can be set to levels 1,2,3 only */

#define INTC_IPL123_INTS 0x187c0L /* interrupts 6,7,8,9,10,15,16 */

/* bit values for IPR registers */

#define INTC_IPR_INT6_INDEX  0
#define INTC_IPR_INT6_SHIFT  0
#define INTC_IPR_INT6_MASK   (3<<INTC_IPR_INT6_SHIFT)
#define INTC_IPR_INT6_IPLDIS 0
#define INTC_IPR_INT6_IPL1   (1<<INTC_IPR_INT6_SHIFT)
#define INTC_IPR_INT6_IPL2   (2<<INTC_IPR_INT6_SHIFT)
#define INTC_IPR_INT6_IPL3   (3<<INTC_IPR_INT6_SHIFT)

#define INTC_IPR_INT7_INDEX  0
#define INTC_IPR_INT7_SHIFT  2
#define INTC_IPR_INT7_MASK   (3<<INTC_IPR_INT7_SHIFT)
#define INTC_IPR_INT7_IPLDIS 0
#define INTC_IPR_INT7_IPL1   (1<<INTC_IPR_INT7_SHIFT)
#define INTC_IPR_INT7_IPL2   (2<<INTC_IPR_INT7_SHIFT)
#define INTC_IPR_INT7_IPL3   (3<<INTC_IPR_INT7_SHIFT)

#define INTC_IPR_INT8_INDEX  0
#define INTC_IPR_INT8_SHIFT  4
#define INTC_IPR_INT8_MASK   (3<<INTC_IPR_INT8_SHIFT)
#define INTC_IPR_INT8_IPLDIS 0
#define INTC_IPR_INT8_IPL1   (1<<INTC_IPR_INT8_SHIFT)
#define INTC_IPR_INT8_IPL2   (2<<INTC_IPR_INT8_SHIFT)
#define INTC_IPR_INT8_IPL3   (3<<INTC_IPR_INT8_SHIFT)

#define INTC_IPR_INT9_INDEX  0
#define INTC_IPR_INT9_SHIFT  6
#define INTC_IPR_INT9_MASK   (3<<INTC_IPR_INT9_SHIFT)
#define INTC_IPR_INT9_IPLDIS 0
#define INTC_IPR_INT9_IPL1   (1<<INTC_IPR_INT9_SHIFT)
#define INTC_IPR_INT9_IPL2   (2<<INTC_IPR_INT9_SHIFT)
#define INTC_IPR_INT9_IPL3   (3<<INTC_IPR_INT9_SHIFT)

#define INTC_IPR_INT10_INDEX  0
#define INTC_IPR_INT10_SHIFT  8
#define INTC_IPR_INT10_MASK   (3<<INTC_IPR_INT10_SHIFT)
#define INTC_IPR_INT10_IPLDIS 0
#define INTC_IPR_INT10_IPL1   (1<<INTC_IPR_INT10_SHIFT)
#define INTC_IPR_INT10_IPL2   (2<<INTC_IPR_INT10_SHIFT)
#define INTC_IPR_INT10_IPL3   (3<<INTC_IPR_INT10_SHIFT)

#define INTC_IPR_INT15_INDEX  0
#define INTC_IPR_INT15_SHIFT  12
#define INTC_IPR_INT15_MASK   (3<<INTC_IPR_INT15_SHIFT)
#define INTC_IPR_INT15_IPLDIS 0
#define INTC_IPR_INT15_IPL1   (1<<INTC_IPR_INT15_SHIFT)
#define INTC_IPR_INT15_IPL2   (2<<INTC_IPR_INT15_SHIFT)
#define INTC_IPR_INT15_IPL3   (3<<INTC_IPR_INT15_SHIFT)

#define INTC_IPR_INT16_INDEX  0
#define INTC_IPR_INT16_SHIFT  14
#define INTC_IPR_INT16_MASK   (3<<INTC_IPR_INT16_SHIFT)
#define INTC_IPR_INT16_IPLDIS 0
#define INTC_IPR_INT16_IPL1   (1<<INTC_IPR_INT16_SHIFT)
#define INTC_IPR_INT16_IPL2   (2<<INTC_IPR_INT16_SHIFT)
#define INTC_IPR_INT16_IPL3   (3<<INTC_IPR_INT16_SHIFT)

#define INTC_IPR_INT17_INDEX  1
#define INTC_IPR_INT17_SHIFT  0
#define INTC_IPR_INT17_MASK   (3<<INTC_IPR_INT17_SHIFT)
#define INTC_IPR_INT17_IPLDIS 0
#define INTC_IPR_INT17_IPL0   (1<<INTC_IPR_INT17_SHIFT)
#define INTC_IPR_INT17_IPL1   (2<<INTC_IPR_INT17_SHIFT)
#define INTC_IPR_INT17_IPL2   (3<<INTC_IPR_INT17_SHIFT)

#define INTC_IPR_INT18_INDEX  1
#define INTC_IPR_INT18_SHIFT  2
#define INTC_IPR_INT18_MASK   (3<<INTC_IPR_INT18_SHIFT)
#define INTC_IPR_INT18_IPLDIS 0
#define INTC_IPR_INT18_IPL0   (1<<INTC_IPR_INT18_SHIFT)
#define INTC_IPR_INT18_IPL1   (2<<INTC_IPR_INT18_SHIFT)
#define INTC_IPR_INT18_IPL2   (3<<INTC_IPR_INT18_SHIFT)

#define INTC_IPR_INT19_INDEX  1
#define INTC_IPR_INT19_SHIFT  4
#define INTC_IPR_INT19_MASK   (3<<INTC_IPR_INT19_SHIFT)
#define INTC_IPR_INT19_IPLDIS 0
#define INTC_IPR_INT19_IPL0   (1<<INTC_IPR_INT19_SHIFT)
#define INTC_IPR_INT19_IPL1   (2<<INTC_IPR_INT19_SHIFT)
#define INTC_IPR_INT19_IPL2   (3<<INTC_IPR_INT19_SHIFT)

#define INTC_IPR_INT20_INDEX  1
#define INTC_IPR_INT20_SHIFT  6
#define INTC_IPR_INT20_MASK   (3<<INTC_IPR_INT20_SHIFT)
#define INTC_IPR_INT20_IPLDIS 0
#define INTC_IPR_INT20_IPL0   (1<<INTC_IPR_INT20_SHIFT)
#define INTC_IPR_INT20_IPL1   (2<<INTC_IPR_INT20_SHIFT)
#define INTC_IPR_INT20_IPL2   (3<<INTC_IPR_INT20_SHIFT)

#define INTC_IPR_INT21_INDEX  1
#define INTC_IPR_INT21_SHIFT  8
#define INTC_IPR_INT21_MASK   (3<<INTC_IPR_INT21_SHIFT)
#define INTC_IPR_INT21_IPLDIS 0
#define INTC_IPR_INT21_IPL0   (1<<INTC_IPR_INT21_SHIFT)
#define INTC_IPR_INT21_IPL1   (2<<INTC_IPR_INT21_SHIFT)
#define INTC_IPR_INT21_IPL2   (3<<INTC_IPR_INT21_SHIFT)

#define INTC_IPR_INT22_INDEX  1
#define INTC_IPR_INT22_SHIFT  10
#define INTC_IPR_INT22_MASK   (3<<INTC_IPR_INT22_SHIFT)
#define INTC_IPR_INT22_IPLDIS 0
#define INTC_IPR_INT22_IPL0   (1<<INTC_IPR_INT22_SHIFT)
#define INTC_IPR_INT22_IPL1   (2<<INTC_IPR_INT22_SHIFT)
#define INTC_IPR_INT22_IPL2   (3<<INTC_IPR_INT22_SHIFT)

#define INTC_IPR_INT23_INDEX  1
#define INTC_IPR_INT23_SHIFT  12
#define INTC_IPR_INT23_MASK   (3<<INTC_IPR_INT23_SHIFT)
#define INTC_IPR_INT23_IPLDIS 0
#define INTC_IPR_INT23_IPL0   (1<<INTC_IPR_INT23_SHIFT)
#define INTC_IPR_INT23_IPL1   (2<<INTC_IPR_INT23_SHIFT)
#define INTC_IPR_INT23_IPL2   (3<<INTC_IPR_INT23_SHIFT)

#define INTC_IPR_INT24_INDEX  1
#define INTC_IPR_INT24_SHIFT  14
#define INTC_IPR_INT24_MASK   (3<<INTC_IPR_INT24_SHIFT)
#define INTC_IPR_INT24_IPLDIS 0
#define INTC_IPR_INT24_IPL0   (1<<INTC_IPR_INT24_SHIFT)
#define INTC_IPR_INT24_IPL1   (2<<INTC_IPR_INT24_SHIFT)
#define INTC_IPR_INT24_IPL2   (3<<INTC_IPR_INT24_SHIFT)

#define INTC_IPR_INT25_INDEX  2
#define INTC_IPR_INT25_SHIFT  0
#define INTC_IPR_INT25_MASK   (3<<INTC_IPR_INT25_SHIFT)
#define INTC_IPR_INT25_IPLDIS 0
#define INTC_IPR_INT25_IPL0   (1<<INTC_IPR_INT25_SHIFT)
#define INTC_IPR_INT25_IPL1   (2<<INTC_IPR_INT25_SHIFT)
#define INTC_IPR_INT25_IPL2   (3<<INTC_IPR_INT25_SHIFT)

#define INTC_IPR_INT26_INDEX  2
#define INTC_IPR_INT26_SHIFT  2
#define INTC_IPR_INT26_MASK   (3<<INTC_IPR_INT26_SHIFT)
#define INTC_IPR_INT26_IPLDIS 0
#define INTC_IPR_INT26_IPL0   (1<<INTC_IPR_INT26_SHIFT)
#define INTC_IPR_INT26_IPL1   (2<<INTC_IPR_INT26_SHIFT)
#define INTC_IPR_INT26_IPL2   (3<<INTC_IPR_INT26_SHIFT)

#define INTC_IPR_INT27_INDEX  2
#define INTC_IPR_INT27_SHIFT  4
#define INTC_IPR_INT27_MASK   (3<<INTC_IPR_INT27_SHIFT)
#define INTC_IPR_INT27_IPLDIS 0
#define INTC_IPR_INT27_IPL0   (1<<INTC_IPR_INT27_SHIFT)
#define INTC_IPR_INT27_IPL1   (2<<INTC_IPR_INT27_SHIFT)
#define INTC_IPR_INT27_IPL2   (3<<INTC_IPR_INT27_SHIFT)

#define INTC_IPR_INT28_INDEX  2
#define INTC_IPR_INT28_SHIFT  6
#define INTC_IPR_INT28_MASK   (3<<INTC_IPR_INT28_SHIFT)
#define INTC_IPR_INT28_IPLDIS 0
#define INTC_IPR_INT28_IPL0   (1<<INTC_IPR_INT28_SHIFT)
#define INTC_IPR_INT28_IPL1   (2<<INTC_IPR_INT28_SHIFT)
#define INTC_IPR_INT28_IPL2   (3<<INTC_IPR_INT28_SHIFT)

#define INTC_IPR_INT29_INDEX  2
#define INTC_IPR_INT29_SHIFT  8
#define INTC_IPR_INT29_MASK   (3<<INTC_IPR_INT29_SHIFT)
#define INTC_IPR_INT29_IPLDIS 0
#define INTC_IPR_INT29_IPL0   (1<<INTC_IPR_INT29_SHIFT)
#define INTC_IPR_INT29_IPL1   (2<<INTC_IPR_INT29_SHIFT)
#define INTC_IPR_INT29_IPL2   (3<<INTC_IPR_INT29_SHIFT)

#define INTC_IPR_INT30_INDEX  2
#define INTC_IPR_INT30_SHIFT  10
#define INTC_IPR_INT30_MASK   (3<<INTC_IPR_INT30_SHIFT)
#define INTC_IPR_INT30_IPLDIS 0
#define INTC_IPR_INT30_IPL0   (1<<INTC_IPR_INT30_SHIFT)
#define INTC_IPR_INT30_IPL1   (2<<INTC_IPR_INT30_SHIFT)
#define INTC_IPR_INT30_IPL2   (3<<INTC_IPR_INT30_SHIFT)

#define INTC_IPR_INT31_INDEX  2
#define INTC_IPR_INT31_SHIFT  12
#define INTC_IPR_INT31_MASK   (3<<INTC_IPR_INT31_SHIFT)
#define INTC_IPR_INT31_IPLDIS 0
#define INTC_IPR_INT31_IPL0   (1<<INTC_IPR_INT31_SHIFT)
#define INTC_IPR_INT31_IPL1   (2<<INTC_IPR_INT31_SHIFT)
#define INTC_IPR_INT31_IPL2   (3<<INTC_IPR_INT31_SHIFT)

#define INTC_IPR_INT32_INDEX  2
#define INTC_IPR_INT32_SHIFT  14
#define INTC_IPR_INT32_MASK   (3<<INTC_IPR_INT32_SHIFT)
#define INTC_IPR_INT32_IPLDIS 0
#define INTC_IPR_INT32_IPL0   (1<<INTC_IPR_INT32_SHIFT)
#define INTC_IPR_INT32_IPL1   (2<<INTC_IPR_INT32_SHIFT)
#define INTC_IPR_INT32_IPL2   (3<<INTC_IPR_INT32_SHIFT)

#define INTC_IPR_INT33_INDEX  3
#define INTC_IPR_INT33_SHIFT  0
#define INTC_IPR_INT33_MASK   (3<<INTC_IPR_INT33_SHIFT)
#define INTC_IPR_INT33_IPLDIS 0
#define INTC_IPR_INT33_IPL0   (1<<INTC_IPR_INT33_SHIFT)
#define INTC_IPR_INT33_IPL1   (2<<INTC_IPR_INT33_SHIFT)
#define INTC_IPR_INT33_IPL2   (3<<INTC_IPR_INT33_SHIFT)

#define INTC_IPR_INT34_INDEX  3
#define INTC_IPR_INT34_SHIFT  2
#define INTC_IPR_INT34_MASK   (3<<INTC_IPR_INT34_SHIFT)
#define INTC_IPR_INT34_IPLDIS 0
#define INTC_IPR_INT34_IPL0   (1<<INTC_IPR_INT34_SHIFT)
#define INTC_IPR_INT34_IPL1   (2<<INTC_IPR_INT34_SHIFT)
#define INTC_IPR_INT34_IPL2   (3<<INTC_IPR_INT34_SHIFT)

#define INTC_IPR_INT35_INDEX  3
#define INTC_IPR_INT35_SHIFT  4
#define INTC_IPR_INT35_MASK   (3<<INTC_IPR_INT35_SHIFT)
#define INTC_IPR_INT35_IPLDIS 0
#define INTC_IPR_INT35_IPL0   (1<<INTC_IPR_INT35_SHIFT)
#define INTC_IPR_INT35_IPL1   (2<<INTC_IPR_INT35_SHIFT)
#define INTC_IPR_INT35_IPL2   (3<<INTC_IPR_INT35_SHIFT)

#define INTC_IPR_INT36_INDEX  3
#define INTC_IPR_INT36_SHIFT  6
#define INTC_IPR_INT36_MASK   (3<<INTC_IPR_INT36_SHIFT)
#define INTC_IPR_INT36_IPLDIS 0
#define INTC_IPR_INT36_IPL0   (1<<INTC_IPR_INT36_SHIFT)
#define INTC_IPR_INT36_IPL1   (2<<INTC_IPR_INT36_SHIFT)
#define INTC_IPR_INT36_IPL2   (3<<INTC_IPR_INT36_SHIFT)

#define INTC_IPR_INT37_INDEX  3
#define INTC_IPR_INT37_SHIFT  8
#define INTC_IPR_INT37_MASK   (3<<INTC_IPR_INT37_SHIFT)
#define INTC_IPR_INT37_IPLDIS 0
#define INTC_IPR_INT37_IPL0   (1<<INTC_IPR_INT37_SHIFT)
#define INTC_IPR_INT37_IPL1   (2<<INTC_IPR_INT37_SHIFT)
#define INTC_IPR_INT37_IPL2   (3<<INTC_IPR_INT37_SHIFT)

#define INTC_IPR_INT38_INDEX  3
#define INTC_IPR_INT38_SHIFT  10
#define INTC_IPR_INT38_MASK   (3<<INTC_IPR_INT38_SHIFT)
#define INTC_IPR_INT38_IPLDIS 0
#define INTC_IPR_INT38_IPL0   (1<<INTC_IPR_INT38_SHIFT)
#define INTC_IPR_INT38_IPL1   (2<<INTC_IPR_INT38_SHIFT)
#define INTC_IPR_INT38_IPL2   (3<<INTC_IPR_INT38_SHIFT)

#define INTC_IPR_INT39_INDEX  3
#define INTC_IPR_INT39_SHIFT  12
#define INTC_IPR_INT39_MASK   (3<<INTC_IPR_INT39_SHIFT)
#define INTC_IPR_INT39_IPLDIS 0
#define INTC_IPR_INT39_IPL0   (1<<INTC_IPR_INT39_SHIFT)
#define INTC_IPR_INT39_IPL1   (2<<INTC_IPR_INT39_SHIFT)
#define INTC_IPR_INT39_IPL2   (3<<INTC_IPR_INT39_SHIFT)

#define INTC_IPR_INT40_INDEX  3
#define INTC_IPR_INT40_SHIFT  14
#define INTC_IPR_INT40_MASK   (3<<INTC_IPR_INT40_SHIFT)
#define INTC_IPR_INT40_IPLDIS 0
#define INTC_IPR_INT40_IPL0   (1<<INTC_IPR_INT40_SHIFT)
#define INTC_IPR_INT40_IPL1   (2<<INTC_IPR_INT40_SHIFT)
#define INTC_IPR_INT40_IPL2   (3<<INTC_IPR_INT40_SHIFT)

#define INTC_IPR_INT41_INDEX  4
#define INTC_IPR_INT41_SHIFT  0
#define INTC_IPR_INT41_MASK   (3<<INTC_IPR_INT41_SHIFT)
#define INTC_IPR_INT41_IPLDIS 0
#define INTC_IPR_INT41_IPL0   (1<<INTC_IPR_INT41_SHIFT)
#define INTC_IPR_INT41_IPL1   (2<<INTC_IPR_INT41_SHIFT)
#define INTC_IPR_INT41_IPL2   (3<<INTC_IPR_INT41_SHIFT)

#define INTC_IPR_INT42_INDEX  4
#define INTC_IPR_INT42_SHIFT  2
#define INTC_IPR_INT42_MASK   (3<<INTC_IPR_INT42_SHIFT)
#define INTC_IPR_INT42_IPLDIS 0
#define INTC_IPR_INT42_IPL0   (1<<INTC_IPR_INT42_SHIFT)
#define INTC_IPR_INT42_IPL1   (2<<INTC_IPR_INT42_SHIFT)
#define INTC_IPR_INT42_IPL2   (3<<INTC_IPR_INT42_SHIFT)

#define INTC_IPR_INT43_INDEX  4
#define INTC_IPR_INT43_SHIFT  4
#define INTC_IPR_INT43_MASK   (3<<INTC_IPR_INT43_SHIFT)
#define INTC_IPR_INT43_IPLDIS 0
#define INTC_IPR_INT43_IPL0   (1<<INTC_IPR_INT43_SHIFT)
#define INTC_IPR_INT43_IPL1   (2<<INTC_IPR_INT43_SHIFT)
#define INTC_IPR_INT43_IPL2   (3<<INTC_IPR_INT43_SHIFT)

#define INTC_IPR_INT44_INDEX  4
#define INTC_IPR_INT44_SHIFT  6
#define INTC_IPR_INT44_MASK   (3<<INTC_IPR_INT44_SHIFT)
#define INTC_IPR_INT44_IPLDIS 0
#define INTC_IPR_INT44_IPL0   (1<<INTC_IPR_INT44_SHIFT)
#define INTC_IPR_INT44_IPL1   (2<<INTC_IPR_INT44_SHIFT)
#define INTC_IPR_INT44_IPL2   (3<<INTC_IPR_INT44_SHIFT)

#define INTC_IPR_INT45_INDEX  4
#define INTC_IPR_INT45_SHIFT  8
#define INTC_IPR_INT45_MASK   (3<<INTC_IPR_INT45_SHIFT)
#define INTC_IPR_INT45_IPLDIS 0
#define INTC_IPR_INT45_IPL0   (1<<INTC_IPR_INT45_SHIFT)
#define INTC_IPR_INT45_IPL1   (2<<INTC_IPR_INT45_SHIFT)
#define INTC_IPR_INT45_IPL2   (3<<INTC_IPR_INT45_SHIFT)

#define INTC_IPR_INT46_INDEX  4
#define INTC_IPR_INT46_SHIFT  10
#define INTC_IPR_INT46_MASK   (3<<INTC_IPR_INT46_SHIFT)
#define INTC_IPR_INT46_IPLDIS 0
#define INTC_IPR_INT46_IPL0   (1<<INTC_IPR_INT46_SHIFT)
#define INTC_IPR_INT46_IPL1   (2<<INTC_IPR_INT46_SHIFT)
#define INTC_IPR_INT46_IPL2   (3<<INTC_IPR_INT46_SHIFT)

#define INTC_IPR_INT47_INDEX  4
#define INTC_IPR_INT47_SHIFT  12
#define INTC_IPR_INT47_MASK   (3<<INTC_IPR_INT47_SHIFT)
#define INTC_IPR_INT47_IPLDIS 0
#define INTC_IPR_INT47_IPL0   (1<<INTC_IPR_INT47_SHIFT)
#define INTC_IPR_INT47_IPL1   (2<<INTC_IPR_INT47_SHIFT)
#define INTC_IPR_INT47_IPL2   (3<<INTC_IPR_INT47_SHIFT)

#define INTC_IPR_INT48_INDEX  4
#define INTC_IPR_INT48_SHIFT  14
#define INTC_IPR_INT48_MASK   (3<<INTC_IPR_INT48_SHIFT)
#define INTC_IPR_INT48_IPLDIS 0
#define INTC_IPR_INT48_IPL0   (1<<INTC_IPR_INT48_SHIFT)
#define INTC_IPR_INT48_IPL1   (2<<INTC_IPR_INT48_SHIFT)
#define INTC_IPR_INT48_IPL2   (3<<INTC_IPR_INT48_SHIFT)

#define INTC_IPR_INT49_INDEX  5
#define INTC_IPR_INT49_SHIFT  0
#define INTC_IPR_INT49_MASK   (3<<INTC_IPR_INT49_SHIFT)
#define INTC_IPR_INT49_IPLDIS 0
#define INTC_IPR_INT49_IPL0   (1<<INTC_IPR_INT49_SHIFT)
#define INTC_IPR_INT49_IPL1   (2<<INTC_IPR_INT49_SHIFT)
#define INTC_IPR_INT49_IPL2   (3<<INTC_IPR_INT49_SHIFT)

#define INTC_IPR_INT50_INDEX  5
#define INTC_IPR_INT50_SHIFT  2
#define INTC_IPR_INT50_MASK   (3<<INTC_IPR_INT50_SHIFT)
#define INTC_IPR_INT50_IPLDIS 0
#define INTC_IPR_INT50_IPL0   (1<<INTC_IPR_INT50_SHIFT)
#define INTC_IPR_INT50_IPL1   (2<<INTC_IPR_INT50_SHIFT)
#define INTC_IPR_INT50_IPL2   (3<<INTC_IPR_INT50_SHIFT)

#define INTC_IPR_INT51_INDEX  5
#define INTC_IPR_INT51_SHIFT  4
#define INTC_IPR_INT51_MASK   (3<<INTC_IPR_INT51_SHIFT)
#define INTC_IPR_INT51_IPLDIS 0
#define INTC_IPR_INT51_IPL0   (1<<INTC_IPR_INT51_SHIFT)
#define INTC_IPR_INT51_IPL1   (2<<INTC_IPR_INT51_SHIFT)
#define INTC_IPR_INT51_IPL2   (3<<INTC_IPR_INT51_SHIFT)

#define INTC_IPR_INT52_INDEX  5
#define INTC_IPR_INT52_SHIFT  6
#define INTC_IPR_INT52_MASK   (3<<INTC_IPR_INT52_SHIFT)
#define INTC_IPR_INT52_IPLDIS 0
#define INTC_IPR_INT52_IPL0   (1<<INTC_IPR_INT52_SHIFT)
#define INTC_IPR_INT52_IPL1   (2<<INTC_IPR_INT52_SHIFT)
#define INTC_IPR_INT52_IPL2   (3<<INTC_IPR_INT52_SHIFT)

#define INTC_IPR_INT53_INDEX  5
#define INTC_IPR_INT53_SHIFT  8
#define INTC_IPR_INT53_MASK   (3<<INTC_IPR_INT53_SHIFT)
#define INTC_IPR_INT53_IPLDIS 0
#define INTC_IPR_INT53_IPL0   (1<<INTC_IPR_INT53_SHIFT)
#define INTC_IPR_INT53_IPL1   (2<<INTC_IPR_INT53_SHIFT)
#define INTC_IPR_INT53_IPL2   (3<<INTC_IPR_INT53_SHIFT)

#define INTC_IPR_INT54_INDEX  5
#define INTC_IPR_INT54_SHIFT  10
#define INTC_IPR_INT54_MASK   (3<<INTC_IPR_INT54_SHIFT)
#define INTC_IPR_INT54_IPLDIS 0
#define INTC_IPR_INT54_IPL0   (1<<INTC_IPR_INT54_SHIFT)
#define INTC_IPR_INT54_IPL1   (2<<INTC_IPR_INT54_SHIFT)
#define INTC_IPR_INT54_IPL2   (3<<INTC_IPR_INT54_SHIFT)

#define INTC_IPR_INT55_INDEX  5
#define INTC_IPR_INT55_SHIFT  12
#define INTC_IPR_INT55_MASK   (3<<INTC_IPR_INT55_SHIFT)
#define INTC_IPR_INT55_IPLDIS 0
#define INTC_IPR_INT55_IPL0   (1<<INTC_IPR_INT55_SHIFT)
#define INTC_IPR_INT55_IPL1   (2<<INTC_IPR_INT55_SHIFT)
#define INTC_IPR_INT55_IPL2   (3<<INTC_IPR_INT55_SHIFT)

#define INTC_IPR_INT56_INDEX  5
#define INTC_IPR_INT56_SHIFT  14
#define INTC_IPR_INT56_MASK   (3<<INTC_IPR_INT56_SHIFT)
#define INTC_IPR_INT56_IPLDIS 0
#define INTC_IPR_INT56_IPL0   (1<<INTC_IPR_INT56_SHIFT)
#define INTC_IPR_INT56_IPL1   (2<<INTC_IPR_INT56_SHIFT)
#define INTC_IPR_INT56_IPL2   (3<<INTC_IPR_INT56_SHIFT)

#define INTC_IPR_INT57_INDEX  6
#define INTC_IPR_INT57_SHIFT  0
#define INTC_IPR_INT57_MASK   (3<<INTC_IPR_INT57_SHIFT)
#define INTC_IPR_INT57_IPLDIS 0
#define INTC_IPR_INT57_IPL0   (1<<INTC_IPR_INT57_SHIFT)
#define INTC_IPR_INT57_IPL1   (2<<INTC_IPR_INT57_SHIFT)
#define INTC_IPR_INT57_IPL2   (3<<INTC_IPR_INT57_SHIFT)

#define INTC_IPR_INT58_INDEX  6
#define INTC_IPR_INT58_SHIFT  2
#define INTC_IPR_INT58_MASK   (3<<INTC_IPR_INT58_SHIFT)
#define INTC_IPR_INT58_IPLDIS 0
#define INTC_IPR_INT58_IPL0   (1<<INTC_IPR_INT58_SHIFT)
#define INTC_IPR_INT58_IPL1   (2<<INTC_IPR_INT58_SHIFT)
#define INTC_IPR_INT58_IPL2   (3<<INTC_IPR_INT58_SHIFT)

#define INTC_IPR_INT59_INDEX  6
#define INTC_IPR_INT59_SHIFT  4
#define INTC_IPR_INT59_MASK   (3<<INTC_IPR_INT59_SHIFT)
#define INTC_IPR_INT59_IPLDIS 0
#define INTC_IPR_INT59_IPL0   (1<<INTC_IPR_INT59_SHIFT)
#define INTC_IPR_INT59_IPL1   (2<<INTC_IPR_INT59_SHIFT)
#define INTC_IPR_INT59_IPL2   (3<<INTC_IPR_INT59_SHIFT)

#define INTC_IPR_INT60_INDEX  6
#define INTC_IPR_INT60_SHIFT  6
#define INTC_IPR_INT60_MASK   (3<<INTC_IPR_INT60_SHIFT)
#define INTC_IPR_INT60_IPLDIS 0
#define INTC_IPR_INT60_IPL0   (1<<INTC_IPR_INT60_SHIFT)
#define INTC_IPR_INT60_IPL1   (2<<INTC_IPR_INT60_SHIFT)
#define INTC_IPR_INT60_IPL2   (3<<INTC_IPR_INT60_SHIFT)

#define INTC_IPR_INT61_INDEX  6
#define INTC_IPR_INT61_SHIFT  8
#define INTC_IPR_INT61_MASK   (3<<INTC_IPR_INT61_SHIFT)
#define INTC_IPR_INT61_IPLDIS 0
#define INTC_IPR_INT61_IPL0   (1<<INTC_IPR_INT61_SHIFT)
#define INTC_IPR_INT61_IPL1   (2<<INTC_IPR_INT61_SHIFT)
#define INTC_IPR_INT61_IPL2   (3<<INTC_IPR_INT61_SHIFT)

#define INTC_IPR_INT62_INDEX  6
#define INTC_IPR_INT62_SHIFT  10
#define INTC_IPR_INT62_MASK   (3<<INTC_IPR_INT62_SHIFT)
#define INTC_IPR_INT62_IPLDIS 0
#define INTC_IPR_INT62_IPL0   (1<<INTC_IPR_INT62_SHIFT)
#define INTC_IPR_INT62_IPL1   (2<<INTC_IPR_INT62_SHIFT)
#define INTC_IPR_INT62_IPL2   (3<<INTC_IPR_INT62_SHIFT)



/*******************************************************************************
	ioctl commands to set or get the interrupt IPL
*******************************************************************************/

#define INTC_SET_IPL_6
#define INTC_SET_IPL_6_RAW
#define INTC_GET_IPL_6_RAW
#define ioctlINTC_SET_IPL_6(pIntcBase, param)     INTC_SET_IPL123_n(6, pIntcBase, param)
#define ioctlINTC_SET_IPL_6_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(6, pIntcBase, param)
#define ioctlINTC_GET_IPL_6_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(6, pIntcBase)

#define INTC_SET_IPL_7
#define INTC_SET_IPL_7_RAW
#define INTC_GET_IPL_7_RAW
#define ioctlINTC_SET_IPL_7(pIntcBase, param)     INTC_SET_IPL123_n(7, pIntcBase, param)
#define ioctlINTC_SET_IPL_7_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(7, pIntcBase, param)
#define ioctlINTC_GET_IPL_7_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(7, pIntcBase)

#define INTC_SET_IPL_8
#define INTC_SET_IPL_8_RAW
#define INTC_GET_IPL_8_RAW
#define ioctlINTC_SET_IPL_8(pIntcBase, param)     INTC_SET_IPL123_n(8, pIntcBase, param)
#define ioctlINTC_SET_IPL_8_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(8, pIntcBase, param)
#define ioctlINTC_GET_IPL_8_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(8, pIntcBase)

#define INTC_SET_IPL_9
#define INTC_SET_IPL_9_RAW
#define INTC_GET_IPL_9_RAW
#define ioctlINTC_SET_IPL_9(pIntcBase, param)     INTC_SET_IPL123_n(9, pIntcBase, param)
#define ioctlINTC_SET_IPL_9_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(9, pIntcBase, param)
#define ioctlINTC_GET_IPL_9_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(9, pIntcBase)

#define INTC_SET_IPL_10
#define INTC_SET_IPL_10_RAW
#define INTC_GET_IPL_10_RAW
#define ioctlINTC_SET_IPL_10(pIntcBase, param)     INTC_SET_IPL123_n(10, pIntcBase, param)
#define ioctlINTC_SET_IPL_10_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(10, pIntcBase, param)
#define ioctlINTC_GET_IPL_10_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(10, pIntcBase)

#define INTC_SET_IPL_15
#define INTC_SET_IPL_15_RAW
#define INTC_GET_IPL_15_RAW
#define ioctlINTC_SET_IPL_15(pIntcBase, param)     INTC_SET_IPL123_n(15, pIntcBase, param)
#define ioctlINTC_SET_IPL_15_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(15, pIntcBase, param)
#define ioctlINTC_GET_IPL_15_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(15, pIntcBase)

#define INTC_SET_IPL_16
#define INTC_SET_IPL_16_RAW
#define INTC_GET_IPL_16_RAW
#define ioctlINTC_SET_IPL_16(pIntcBase, param)     INTC_SET_IPL123_n(16, pIntcBase, param)
#define ioctlINTC_SET_IPL_16_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(16, pIntcBase, param)
#define ioctlINTC_GET_IPL_16_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(16, pIntcBase)

#define INTC_SET_IPL_17
#define INTC_SET_IPL_17_RAW
#define INTC_GET_IPL_17_RAW
#define ioctlINTC_SET_IPL_17(pIntcBase, param)     INTC_SET_IPL012_n(17, pIntcBase, param)
#define ioctlINTC_SET_IPL_17_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(17, pIntcBase, param)
#define ioctlINTC_GET_IPL_17_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(17, pIntcBase)

#define INTC_SET_IPL_18
#define INTC_SET_IPL_18_RAW
#define INTC_GET_IPL_18_RAW
#define ioctlINTC_SET_IPL_18(pIntcBase, param)     INTC_SET_IPL012_n(18, pIntcBase, param)
#define ioctlINTC_SET_IPL_18_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(18, pIntcBase, param)
#define ioctlINTC_GET_IPL_18_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(18, pIntcBase)

#define INTC_SET_IPL_19
#define INTC_SET_IPL_19_RAW
#define INTC_GET_IPL_19_RAW
#define ioctlINTC_SET_IPL_19(pIntcBase, param)     INTC_SET_IPL012_n(19, pIntcBase, param)
#define ioctlINTC_SET_IPL_19_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(19, pIntcBase, param)
#define ioctlINTC_GET_IPL_19_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(19, pIntcBase)

#define INTC_SET_IPL_20
#define INTC_SET_IPL_20_RAW
#define INTC_GET_IPL_20_RAW
#define ioctlINTC_SET_IPL_20(pIntcBase, param)     INTC_SET_IPL012_n(20, pIntcBase, param)
#define ioctlINTC_SET_IPL_20_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(20, pIntcBase, param)
#define ioctlINTC_GET_IPL_20_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(20, pIntcBase)

#define INTC_SET_IPL_21
#define INTC_SET_IPL_21_RAW
#define INTC_GET_IPL_21_RAW
#define ioctlINTC_SET_IPL_21(pIntcBase, param)     INTC_SET_IPL012_n(21, pIntcBase, param)
#define ioctlINTC_SET_IPL_21_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(21, pIntcBase, param)
#define ioctlINTC_GET_IPL_21_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(21, pIntcBase)

#define INTC_SET_IPL_22
#define INTC_SET_IPL_22_RAW
#define INTC_GET_IPL_22_RAW
#define ioctlINTC_SET_IPL_22(pIntcBase, param)     INTC_SET_IPL012_n(22, pIntcBase, param)
#define ioctlINTC_SET_IPL_22_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(22, pIntcBase, param)
#define ioctlINTC_GET_IPL_22_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(22, pIntcBase)

#define INTC_SET_IPL_23
#define INTC_SET_IPL_23_RAW
#define INTC_GET_IPL_23_RAW
#define ioctlINTC_SET_IPL_23(pIntcBase, param)     INTC_SET_IPL012_n(23, pIntcBase, param)
#define ioctlINTC_SET_IPL_23_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(23, pIntcBase, param)
#define ioctlINTC_GET_IPL_23_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(23, pIntcBase)

#define INTC_SET_IPL_24
#define INTC_SET_IPL_24_RAW
#define INTC_GET_IPL_24_RAW
#define ioctlINTC_SET_IPL_24(pIntcBase, param)     INTC_SET_IPL012_n(24, pIntcBase, param)
#define ioctlINTC_SET_IPL_24_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(24, pIntcBase, param)
#define ioctlINTC_GET_IPL_24_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(24, pIntcBase)

#define INTC_SET_IPL_25
#define INTC_SET_IPL_25_RAW
#define INTC_GET_IPL_25_RAW
#define ioctlINTC_SET_IPL_25(pIntcBase, param)     INTC_SET_IPL012_n(25, pIntcBase, param)
#define ioctlINTC_SET_IPL_25_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(25, pIntcBase, param)
#define ioctlINTC_GET_IPL_25_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(25, pIntcBase)

#define INTC_SET_IPL_26
#define INTC_SET_IPL_26_RAW
#define INTC_GET_IPL_26_RAW
#define ioctlINTC_SET_IPL_26(pIntcBase, param)     INTC_SET_IPL012_n(26, pIntcBase, param)
#define ioctlINTC_SET_IPL_26_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(26, pIntcBase, param)
#define ioctlINTC_GET_IPL_26_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(26, pIntcBase)

#define INTC_SET_IPL_27
#define INTC_SET_IPL_27_RAW
#define INTC_GET_IPL_27_RAW
#define ioctlINTC_SET_IPL_27(pIntcBase, param)     INTC_SET_IPL012_n(27, pIntcBase, param)
#define ioctlINTC_SET_IPL_27_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(27, pIntcBase, param)
#define ioctlINTC_GET_IPL_27_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(27, pIntcBase)

#define INTC_SET_IPL_28
#define INTC_SET_IPL_28_RAW
#define INTC_GET_IPL_28_RAW
#define ioctlINTC_SET_IPL_28(pIntcBase, param)     INTC_SET_IPL012_n(28, pIntcBase, param)
#define ioctlINTC_SET_IPL_28_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(28, pIntcBase, param)
#define ioctlINTC_GET_IPL_28_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(28, pIntcBase)

#define INTC_SET_IPL_29
#define INTC_SET_IPL_29_RAW
#define INTC_GET_IPL_29_RAW
#define ioctlINTC_SET_IPL_29(pIntcBase, param)     INTC_SET_IPL012_n(29, pIntcBase, param)
#define ioctlINTC_SET_IPL_29_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(29, pIntcBase, param)
#define ioctlINTC_GET_IPL_29_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(29, pIntcBase)

#define INTC_SET_IPL_30
#define INTC_SET_IPL_30_RAW
#define INTC_GET_IPL_30_RAW
#define ioctlINTC_SET_IPL_30(pIntcBase, param)     INTC_SET_IPL012_n(30, pIntcBase, param)
#define ioctlINTC_SET_IPL_30_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(30, pIntcBase, param)
#define ioctlINTC_GET_IPL_30_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(30, pIntcBase)

#define INTC_SET_IPL_31
#define INTC_SET_IPL_31_RAW
#define INTC_GET_IPL_31_RAW
#define ioctlINTC_SET_IPL_31(pIntcBase, param)     INTC_SET_IPL012_n(31, pIntcBase, param)
#define ioctlINTC_SET_IPL_31_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(31, pIntcBase, param)
#define ioctlINTC_GET_IPL_31_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(31, pIntcBase)

#define INTC_SET_IPL_32
#define INTC_SET_IPL_32_RAW
#define INTC_GET_IPL_32_RAW
#define ioctlINTC_SET_IPL_32(pIntcBase, param)     INTC_SET_IPL012_n(32, pIntcBase, param)
#define ioctlINTC_SET_IPL_32_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(32, pIntcBase, param)
#define ioctlINTC_GET_IPL_32_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(32, pIntcBase)

#define INTC_SET_IPL_33
#define INTC_SET_IPL_33_RAW
#define INTC_GET_IPL_33_RAW
#define ioctlINTC_SET_IPL_33(pIntcBase, param)     INTC_SET_IPL012_n(33, pIntcBase, param)
#define ioctlINTC_SET_IPL_33_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(33, pIntcBase, param)
#define ioctlINTC_GET_IPL_33_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(33, pIntcBase)

#define INTC_SET_IPL_34
#define INTC_SET_IPL_34_RAW
#define INTC_GET_IPL_34_RAW
#define ioctlINTC_SET_IPL_34(pIntcBase, param)     INTC_SET_IPL012_n(34, pIntcBase, param)
#define ioctlINTC_SET_IPL_34_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(34, pIntcBase, param)
#define ioctlINTC_GET_IPL_34_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(34, pIntcBase)

#define INTC_SET_IPL_35
#define INTC_SET_IPL_35_RAW
#define INTC_GET_IPL_35_RAW
#define ioctlINTC_SET_IPL_35(pIntcBase, param)     INTC_SET_IPL012_n(35, pIntcBase, param)
#define ioctlINTC_SET_IPL_35_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(35, pIntcBase, param)
#define ioctlINTC_GET_IPL_35_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(35, pIntcBase)

#define INTC_SET_IPL_36
#define INTC_SET_IPL_36_RAW
#define INTC_GET_IPL_36_RAW
#define ioctlINTC_SET_IPL_36(pIntcBase, param)     INTC_SET_IPL012_n(36, pIntcBase, param)
#define ioctlINTC_SET_IPL_36_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(36, pIntcBase, param)
#define ioctlINTC_GET_IPL_36_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(36, pIntcBase)

#define INTC_SET_IPL_37
#define INTC_SET_IPL_37_RAW
#define INTC_GET_IPL_37_RAW
#define ioctlINTC_SET_IPL_37(pIntcBase, param)     INTC_SET_IPL012_n(37, pIntcBase, param)
#define ioctlINTC_SET_IPL_37_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(37, pIntcBase, param)
#define ioctlINTC_GET_IPL_37_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(37, pIntcBase)

#define INTC_SET_IPL_38
#define INTC_SET_IPL_38_RAW
#define INTC_GET_IPL_38_RAW
#define ioctlINTC_SET_IPL_38(pIntcBase, param)     INTC_SET_IPL012_n(38, pIntcBase, param)
#define ioctlINTC_SET_IPL_38_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(38, pIntcBase, param)
#define ioctlINTC_GET_IPL_38_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(38, pIntcBase)

#define INTC_SET_IPL_39
#define INTC_SET_IPL_39_RAW
#define INTC_GET_IPL_39_RAW
#define ioctlINTC_SET_IPL_39(pIntcBase, param)     INTC_SET_IPL012_n(39, pIntcBase, param)
#define ioctlINTC_SET_IPL_39_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(39, pIntcBase, param)
#define ioctlINTC_GET_IPL_39_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(39, pIntcBase)

#define INTC_SET_IPL_40
#define INTC_SET_IPL_40_RAW
#define INTC_GET_IPL_40_RAW
#define ioctlINTC_SET_IPL_40(pIntcBase, param)     INTC_SET_IPL012_n(40, pIntcBase, param)
#define ioctlINTC_SET_IPL_40_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(40, pIntcBase, param)
#define ioctlINTC_GET_IPL_40_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(40, pIntcBase)

#define INTC_SET_IPL_41
#define INTC_SET_IPL_41_RAW
#define INTC_GET_IPL_41_RAW
#define ioctlINTC_SET_IPL_41(pIntcBase, param)     INTC_SET_IPL012_n(41, pIntcBase, param)
#define ioctlINTC_SET_IPL_41_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(41, pIntcBase, param)
#define ioctlINTC_GET_IPL_41_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(41, pIntcBase)

#define INTC_SET_IPL_42
#define INTC_SET_IPL_42_RAW
#define INTC_GET_IPL_42_RAW
#define ioctlINTC_SET_IPL_42(pIntcBase, param)     INTC_SET_IPL012_n(42, pIntcBase, param)
#define ioctlINTC_SET_IPL_42_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(42, pIntcBase, param)
#define ioctlINTC_GET_IPL_42_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(42, pIntcBase)

#define INTC_SET_IPL_43
#define INTC_SET_IPL_43_RAW
#define INTC_GET_IPL_43_RAW
#define ioctlINTC_SET_IPL_43(pIntcBase, param)     INTC_SET_IPL012_n(43, pIntcBase, param)
#define ioctlINTC_SET_IPL_43_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(43, pIntcBase, param)
#define ioctlINTC_GET_IPL_43_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(43, pIntcBase)

#define INTC_SET_IPL_44
#define INTC_SET_IPL_44_RAW
#define INTC_GET_IPL_44_RAW
#define ioctlINTC_SET_IPL_44(pIntcBase, param)     INTC_SET_IPL012_n(44, pIntcBase, param)
#define ioctlINTC_SET_IPL_44_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(44, pIntcBase, param)
#define ioctlINTC_GET_IPL_44_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(44, pIntcBase)

#define INTC_SET_IPL_45
#define INTC_SET_IPL_45_RAW
#define INTC_GET_IPL_45_RAW
#define ioctlINTC_SET_IPL_45(pIntcBase, param)     INTC_SET_IPL012_n(45, pIntcBase, param)
#define ioctlINTC_SET_IPL_45_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(45, pIntcBase, param)
#define ioctlINTC_GET_IPL_45_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(45, pIntcBase)

#define INTC_SET_IPL_46
#define INTC_SET_IPL_46_RAW
#define INTC_GET_IPL_46_RAW
#define ioctlINTC_SET_IPL_46(pIntcBase, param)     INTC_SET_IPL012_n(46, pIntcBase, param)
#define ioctlINTC_SET_IPL_46_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(46, pIntcBase, param)
#define ioctlINTC_GET_IPL_46_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(46, pIntcBase)

#define INTC_SET_IPL_47
#define INTC_SET_IPL_47_RAW
#define INTC_GET_IPL_47_RAW
#define ioctlINTC_SET_IPL_47(pIntcBase, param)     INTC_SET_IPL012_n(47, pIntcBase, param)
#define ioctlINTC_SET_IPL_47_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(47, pIntcBase, param)
#define ioctlINTC_GET_IPL_47_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(47, pIntcBase)

#define INTC_SET_IPL_48
#define INTC_SET_IPL_48_RAW
#define INTC_GET_IPL_48_RAW
#define ioctlINTC_SET_IPL_48(pIntcBase, param)     INTC_SET_IPL012_n(48, pIntcBase, param)
#define ioctlINTC_SET_IPL_48_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(48, pIntcBase, param)
#define ioctlINTC_GET_IPL_48_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(48, pIntcBase)

#define INTC_SET_IPL_49
#define INTC_SET_IPL_49_RAW
#define INTC_GET_IPL_49_RAW
#define ioctlINTC_SET_IPL_49(pIntcBase, param)     INTC_SET_IPL012_n(49, pIntcBase, param)
#define ioctlINTC_SET_IPL_49_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(49, pIntcBase, param)
#define ioctlINTC_GET_IPL_49_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(49, pIntcBase)

#define INTC_SET_IPL_50
#define INTC_SET_IPL_50_RAW
#define INTC_GET_IPL_50_RAW
#define ioctlINTC_SET_IPL_50(pIntcBase, param)     INTC_SET_IPL012_n(50, pIntcBase, param)
#define ioctlINTC_SET_IPL_50_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(50, pIntcBase, param)
#define ioctlINTC_GET_IPL_50_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(50, pIntcBase)

#define INTC_SET_IPL_51
#define INTC_SET_IPL_51_RAW
#define INTC_GET_IPL_51_RAW
#define ioctlINTC_SET_IPL_51(pIntcBase, param)     INTC_SET_IPL012_n(51, pIntcBase, param)
#define ioctlINTC_SET_IPL_51_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(51, pIntcBase, param)
#define ioctlINTC_GET_IPL_51_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(51, pIntcBase)

#define INTC_SET_IPL_52
#define INTC_SET_IPL_52_RAW
#define INTC_GET_IPL_52_RAW
#define ioctlINTC_SET_IPL_52(pIntcBase, param)     INTC_SET_IPL012_n(52, pIntcBase, param)
#define ioctlINTC_SET_IPL_52_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(52, pIntcBase, param)
#define ioctlINTC_GET_IPL_52_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(52, pIntcBase)

#define INTC_SET_IPL_53
#define INTC_SET_IPL_53_RAW
#define INTC_GET_IPL_53_RAW
#define ioctlINTC_SET_IPL_53(pIntcBase, param)     INTC_SET_IPL012_n(53, pIntcBase, param)
#define ioctlINTC_SET_IPL_53_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(53, pIntcBase, param)
#define ioctlINTC_GET_IPL_53_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(53, pIntcBase)

#define INTC_SET_IPL_54
#define INTC_SET_IPL_54_RAW
#define INTC_GET_IPL_54_RAW
#define ioctlINTC_SET_IPL_54(pIntcBase, param)     INTC_SET_IPL012_n(54, pIntcBase, param)
#define ioctlINTC_SET_IPL_54_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(54, pIntcBase, param)
#define ioctlINTC_GET_IPL_54_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(54, pIntcBase)

#define INTC_SET_IPL_55
#define INTC_SET_IPL_55_RAW
#define INTC_GET_IPL_55_RAW
#define ioctlINTC_SET_IPL_55(pIntcBase, param)     INTC_SET_IPL012_n(55, pIntcBase, param)
#define ioctlINTC_SET_IPL_55_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(55, pIntcBase, param)
#define ioctlINTC_GET_IPL_55_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(55, pIntcBase)

#define INTC_SET_IPL_56
#define INTC_SET_IPL_56_RAW
#define INTC_GET_IPL_56_RAW
#define ioctlINTC_SET_IPL_56(pIntcBase, param)     INTC_SET_IPL012_n(56, pIntcBase, param)
#define ioctlINTC_SET_IPL_56_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(56, pIntcBase, param)
#define ioctlINTC_GET_IPL_56_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(56, pIntcBase)

#define INTC_SET_IPL_57
#define INTC_SET_IPL_57_RAW
#define INTC_GET_IPL_57_RAW
#define ioctlINTC_SET_IPL_57(pIntcBase, param)     INTC_SET_IPL012_n(57, pIntcBase, param)
#define ioctlINTC_SET_IPL_57_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(57, pIntcBase, param)
#define ioctlINTC_GET_IPL_57_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(57, pIntcBase)

#define INTC_SET_IPL_58
#define INTC_SET_IPL_58_RAW
#define INTC_GET_IPL_58_RAW
#define ioctlINTC_SET_IPL_58(pIntcBase, param)     INTC_SET_IPL012_n(58, pIntcBase, param)
#define ioctlINTC_SET_IPL_58_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(58, pIntcBase, param)
#define ioctlINTC_GET_IPL_58_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(58, pIntcBase)

#define INTC_SET_IPL_59
#define INTC_SET_IPL_59_RAW
#define INTC_GET_IPL_59_RAW
#define ioctlINTC_SET_IPL_59(pIntcBase, param)     INTC_SET_IPL012_n(59, pIntcBase, param)
#define ioctlINTC_SET_IPL_59_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(59, pIntcBase, param)
#define ioctlINTC_GET_IPL_59_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(59, pIntcBase)

#define INTC_SET_IPL_60
#define INTC_SET_IPL_60_RAW
#define INTC_GET_IPL_60_RAW
#define ioctlINTC_SET_IPL_60(pIntcBase, param)     INTC_SET_IPL012_n(60, pIntcBase, param)
#define ioctlINTC_SET_IPL_60_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(60, pIntcBase, param)
#define ioctlINTC_GET_IPL_60_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(60, pIntcBase)

#define INTC_SET_IPL_61
#define INTC_SET_IPL_61_RAW
#define INTC_GET_IPL_61_RAW
#define ioctlINTC_SET_IPL_61(pIntcBase, param)     INTC_SET_IPL012_n(61, pIntcBase, param)
#define ioctlINTC_SET_IPL_61_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(61, pIntcBase, param)
#define ioctlINTC_GET_IPL_61_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(61, pIntcBase)

#define INTC_SET_IPL_62
#define INTC_SET_IPL_62_RAW
#define INTC_GET_IPL_62_RAW
#define ioctlINTC_SET_IPL_62(pIntcBase, param)     INTC_SET_IPL012_n(62, pIntcBase, param)
#define ioctlINTC_SET_IPL_62_RAW(pIntcBase, param) INTC_SET_IPLRAW_n(62, pIntcBase, param)
#define ioctlINTC_GET_IPL_62_RAW(pIntcBase, param) INTC_GET_IPLRAW_n(62, pIntcBase)



/* we have to make sure that all INT_PRIORITY_LEVEL_x are defined */

#ifdef INT_PRIORITY_LEVEL_1
#error The interrupt 1 has fixed priority level. You can not define INT_PRIORITY_LEVEL_1
#endif
#ifdef INT_PRIORITY_LEVEL_2
#error The interrupt 2 has fixed priority level. You can not define INT_PRIORITY_LEVEL_2
#endif
#ifdef INT_PRIORITY_LEVEL_3
#error The interrupt 3 has fixed priority level. You can not define INT_PRIORITY_LEVEL_3
#endif
#ifdef INT_PRIORITY_LEVEL_4
#error The interrupt 4 has fixed priority level. You can not define INT_PRIORITY_LEVEL_4
#endif
#ifdef INT_PRIORITY_LEVEL_5
#error The interrupt 5 has fixed priority level. You can not define INT_PRIORITY_LEVEL_5
#endif
#ifndef INT_PRIORITY_LEVEL_6
#define INT_PRIORITY_LEVEL_6 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_7
#define INT_PRIORITY_LEVEL_7 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_8
#define INT_PRIORITY_LEVEL_8 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_9
#define INT_PRIORITY_LEVEL_9 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_10
#define INT_PRIORITY_LEVEL_10 INTC_DISABLED
#endif
#ifdef INT_PRIORITY_LEVEL_11
#error The interrupt 11 has fixed priority level. You can not define INT_PRIORITY_LEVEL_11
#endif
#ifdef INT_PRIORITY_LEVEL_12
#error The interrupt 12 has fixed priority level. You can not define INT_PRIORITY_LEVEL_12
#endif
#ifdef INT_PRIORITY_LEVEL_13
#error The interrupt 13 has fixed priority level. You can not define INT_PRIORITY_LEVEL_13
#endif
#ifdef INT_PRIORITY_LEVEL_14
#error The interrupt 14 has fixed priority level. You can not define INT_PRIORITY_LEVEL_14
#endif
#ifndef INT_PRIORITY_LEVEL_15
#define INT_PRIORITY_LEVEL_15 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_16
#define INT_PRIORITY_LEVEL_16 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_17
#define INT_PRIORITY_LEVEL_17 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_18
#define INT_PRIORITY_LEVEL_18 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_19
#define INT_PRIORITY_LEVEL_19 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_20
#define INT_PRIORITY_LEVEL_20 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_21
#define INT_PRIORITY_LEVEL_21 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_22
#define INT_PRIORITY_LEVEL_22 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_23
#define INT_PRIORITY_LEVEL_23 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_24
#define INT_PRIORITY_LEVEL_24 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_25
#define INT_PRIORITY_LEVEL_25 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_26
#define INT_PRIORITY_LEVEL_26 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_27
#define INT_PRIORITY_LEVEL_27 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_28
#define INT_PRIORITY_LEVEL_28 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_29
#define INT_PRIORITY_LEVEL_29 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_30
#define INT_PRIORITY_LEVEL_30 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_31
#define INT_PRIORITY_LEVEL_31 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_32
#define INT_PRIORITY_LEVEL_32 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_33
#define INT_PRIORITY_LEVEL_33 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_34
#define INT_PRIORITY_LEVEL_34 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_35
#define INT_PRIORITY_LEVEL_35 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_36
#define INT_PRIORITY_LEVEL_36 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_37
#define INT_PRIORITY_LEVEL_37 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_38
#define INT_PRIORITY_LEVEL_38 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_39
#define INT_PRIORITY_LEVEL_39 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_40
#define INT_PRIORITY_LEVEL_40 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_41
#define INT_PRIORITY_LEVEL_41 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_42
#define INT_PRIORITY_LEVEL_42 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_43
#define INT_PRIORITY_LEVEL_43 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_44
#define INT_PRIORITY_LEVEL_44 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_45
#define INT_PRIORITY_LEVEL_45 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_46
#define INT_PRIORITY_LEVEL_46 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_47
#define INT_PRIORITY_LEVEL_47 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_48
#define INT_PRIORITY_LEVEL_48 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_49
#define INT_PRIORITY_LEVEL_49 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_50
#define INT_PRIORITY_LEVEL_50 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_51
#define INT_PRIORITY_LEVEL_51 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_52
#define INT_PRIORITY_LEVEL_52 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_53
#define INT_PRIORITY_LEVEL_53 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_54
#define INT_PRIORITY_LEVEL_54 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_55
#define INT_PRIORITY_LEVEL_55 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_56
#define INT_PRIORITY_LEVEL_56 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_57
#define INT_PRIORITY_LEVEL_57 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_58
#define INT_PRIORITY_LEVEL_58 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_59
#define INT_PRIORITY_LEVEL_59 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_60
#define INT_PRIORITY_LEVEL_60 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_61
#define INT_PRIORITY_LEVEL_61 INTC_DISABLED
#endif
#ifndef INT_PRIORITY_LEVEL_62
#define INT_PRIORITY_LEVEL_62 INTC_DISABLED
#endif
#ifdef INT_PRIORITY_LEVEL_63
#error The interrupt 63 has fixed priority level. You can not define INT_PRIORITY_LEVEL_63
#endif


/* for each interrupt vector, define here its correct prototype */

#ifdef INT_VECTOR_ADDR_1
void INT_VECTOR_ADDR_1(void);
#endif
#ifdef INT_VECTOR_ADDR_2
void INT_VECTOR_ADDR_2(void);
#endif
#ifdef INT_VECTOR_ADDR_3
void INT_VECTOR_ADDR_3(void);
#endif
#ifdef INT_VECTOR_ADDR_4
void INT_VECTOR_ADDR_4(void);
#endif
#ifdef INT_VECTOR_ADDR_5
void INT_VECTOR_ADDR_5(void);
#endif
#ifdef INT_VECTOR_ADDR_6
void INT_VECTOR_ADDR_6(void);
#endif
#ifdef INT_VECTOR_ADDR_7
void INT_VECTOR_ADDR_7(void);
#endif
#ifdef INT_VECTOR_ADDR_8
void INT_VECTOR_ADDR_8(void);
#endif
#ifdef INT_VECTOR_ADDR_9
void INT_VECTOR_ADDR_9(void);
#endif
#ifdef INT_VECTOR_ADDR_10
void INT_VECTOR_ADDR_10(void);
#endif
#ifdef INT_VECTOR_ADDR_11
void INT_VECTOR_ADDR_11(void);
#endif
#ifdef INT_VECTOR_ADDR_12
void INT_VECTOR_ADDR_12(void);
#endif
#ifdef INT_VECTOR_ADDR_13
void INT_VECTOR_ADDR_13(void);
#endif
#ifdef INT_VECTOR_ADDR_14
void INT_VECTOR_ADDR_14(void);
#endif
#ifdef INT_VECTOR_ADDR_15
void INT_VECTOR_ADDR_15(void);
#endif
#ifdef INT_VECTOR_ADDR_16
void INT_VECTOR_ADDR_16(void);
#endif
#ifdef INT_VECTOR_ADDR_17
void INT_VECTOR_ADDR_17(void);
#endif
#ifdef INT_VECTOR_ADDR_18
void INT_VECTOR_ADDR_18(void);
#endif
#ifdef INT_VECTOR_ADDR_19
void INT_VECTOR_ADDR_19(void);
#endif
#ifdef INT_VECTOR_ADDR_20
void INT_VECTOR_ADDR_20(void);
#endif
#ifdef INT_VECTOR_ADDR_21
void INT_VECTOR_ADDR_21(void);
#endif
#ifdef INT_VECTOR_ADDR_22
void INT_VECTOR_ADDR_22(void);
#endif
#ifdef INT_VECTOR_ADDR_23
void INT_VECTOR_ADDR_23(void);
#endif
#ifdef INT_VECTOR_ADDR_24
void INT_VECTOR_ADDR_24(void);
#endif
#ifdef INT_VECTOR_ADDR_25
void INT_VECTOR_ADDR_25(void);
#endif
#ifdef INT_VECTOR_ADDR_26
void INT_VECTOR_ADDR_26(void);
#endif
#ifdef INT_VECTOR_ADDR_27
void INT_VECTOR_ADDR_27(void);
#endif
#ifdef INT_VECTOR_ADDR_28
void INT_VECTOR_ADDR_28(void);
#endif
#ifdef INT_VECTOR_ADDR_29
void INT_VECTOR_ADDR_29(void);
#endif
#ifdef INT_VECTOR_ADDR_30
void INT_VECTOR_ADDR_30(void);
#endif
#ifdef INT_VECTOR_ADDR_31
void INT_VECTOR_ADDR_31(void);
#endif
#ifdef INT_VECTOR_ADDR_32
void INT_VECTOR_ADDR_32(void);
#endif
#ifdef INT_VECTOR_ADDR_33
void INT_VECTOR_ADDR_33(void);
#endif
#ifdef INT_VECTOR_ADDR_34
void INT_VECTOR_ADDR_34(void);
#endif
#ifdef INT_VECTOR_ADDR_35
void INT_VECTOR_ADDR_35(void);
#endif
#ifdef INT_VECTOR_ADDR_36
void INT_VECTOR_ADDR_36(void);
#endif
#ifdef INT_VECTOR_ADDR_37
void INT_VECTOR_ADDR_37(void);
#endif
#ifdef INT_VECTOR_ADDR_38
void INT_VECTOR_ADDR_38(void);
#endif
#ifdef INT_VECTOR_ADDR_39
void INT_VECTOR_ADDR_39(void);
#endif
#ifdef INT_VECTOR_ADDR_40
void INT_VECTOR_ADDR_40(void);
#endif
#ifdef INT_VECTOR_ADDR_41
void INT_VECTOR_ADDR_41(void);
#endif
#ifdef INT_VECTOR_ADDR_42
void INT_VECTOR_ADDR_42(void);
#endif
#ifdef INT_VECTOR_ADDR_43
void INT_VECTOR_ADDR_43(void);
#endif
#ifdef INT_VECTOR_ADDR_44
void INT_VECTOR_ADDR_44(void);
#endif
#ifdef INT_VECTOR_ADDR_45
void INT_VECTOR_ADDR_45(void);
#endif
#ifdef INT_VECTOR_ADDR_46
void INT_VECTOR_ADDR_46(void);
#endif
#ifdef INT_VECTOR_ADDR_47
void INT_VECTOR_ADDR_47(void);
#endif
#ifdef INT_VECTOR_ADDR_48
void INT_VECTOR_ADDR_48(void);
#endif
#ifdef INT_VECTOR_ADDR_49
void INT_VECTOR_ADDR_49(void);
#endif
#ifdef INT_VECTOR_ADDR_50
void INT_VECTOR_ADDR_50(void);
#endif
#ifdef INT_VECTOR_ADDR_51
void INT_VECTOR_ADDR_51(void);
#endif
#ifdef INT_VECTOR_ADDR_52
void INT_VECTOR_ADDR_52(void);
#endif
#ifdef INT_VECTOR_ADDR_53
void INT_VECTOR_ADDR_53(void);
#endif
#ifdef INT_VECTOR_ADDR_54
void INT_VECTOR_ADDR_54(void);
#endif
#ifdef INT_VECTOR_ADDR_55
void INT_VECTOR_ADDR_55(void);
#endif
#ifdef INT_VECTOR_ADDR_56
void INT_VECTOR_ADDR_56(void);
#endif
#ifdef INT_VECTOR_ADDR_57
void INT_VECTOR_ADDR_57(void);
#endif
#ifdef INT_VECTOR_ADDR_58
void INT_VECTOR_ADDR_58(void);
#endif
#ifdef INT_VECTOR_ADDR_59
void INT_VECTOR_ADDR_59(void);
#endif
#ifdef INT_VECTOR_ADDR_60
void INT_VECTOR_ADDR_60(void);
#endif
#ifdef INT_VECTOR_ADDR_61
void INT_VECTOR_ADDR_61(void);
#endif
#ifdef INT_VECTOR_ADDR_62
void INT_VECTOR_ADDR_62(void);
#endif
#ifdef INT_VECTOR_ADDR_63
void INT_VECTOR_ADDR_63(void);
#endif


/* now we can define the init values for all IPR registers */

#define INTC_IPR0_INIT (0\
		| INTC_MAKE_IPR_VALUE(6, INT_PRIORITY_LEVEL_6) \
		| INTC_MAKE_IPR_VALUE(7, INT_PRIORITY_LEVEL_7) \
		| INTC_MAKE_IPR_VALUE(8, INT_PRIORITY_LEVEL_8) \
		| INTC_MAKE_IPR_VALUE(9, INT_PRIORITY_LEVEL_9) \
		| INTC_MAKE_IPR_VALUE(10, INT_PRIORITY_LEVEL_10) \
		| INTC_MAKE_IPR_VALUE(15, INT_PRIORITY_LEVEL_15) \
		| INTC_MAKE_IPR_VALUE(16, INT_PRIORITY_LEVEL_16) \
		)
#define INTC_IPR1_INIT (0\
		| INTC_MAKE_IPR_VALUE(17, INT_PRIORITY_LEVEL_17) \
		| INTC_MAKE_IPR_VALUE(18, INT_PRIORITY_LEVEL_18) \
		| INTC_MAKE_IPR_VALUE(19, INT_PRIORITY_LEVEL_19) \
		| INTC_MAKE_IPR_VALUE(20, INT_PRIORITY_LEVEL_20) \
		| INTC_MAKE_IPR_VALUE(21, INT_PRIORITY_LEVEL_21) \
		| INTC_MAKE_IPR_VALUE(22, INT_PRIORITY_LEVEL_22) \
		| INTC_MAKE_IPR_VALUE(23, INT_PRIORITY_LEVEL_23) \
		| INTC_MAKE_IPR_VALUE(24, INT_PRIORITY_LEVEL_24) \
		)
#define INTC_IPR2_INIT (0\
		| INTC_MAKE_IPR_VALUE(25, INT_PRIORITY_LEVEL_25) \
		| INTC_MAKE_IPR_VALUE(26, INT_PRIORITY_LEVEL_26) \
		| INTC_MAKE_IPR_VALUE(27, INT_PRIORITY_LEVEL_27) \
		| INTC_MAKE_IPR_VALUE(28, INT_PRIORITY_LEVEL_28) \
		| INTC_MAKE_IPR_VALUE(29, INT_PRIORITY_LEVEL_29) \
		| INTC_MAKE_IPR_VALUE(30, INT_PRIORITY_LEVEL_30) \
		| INTC_MAKE_IPR_VALUE(31, INT_PRIORITY_LEVEL_31) \
		| INTC_MAKE_IPR_VALUE(32, INT_PRIORITY_LEVEL_32) \
		)
#define INTC_IPR3_INIT (0\
		| INTC_MAKE_IPR_VALUE(33, INT_PRIORITY_LEVEL_33) \
		| INTC_MAKE_IPR_VALUE(34, INT_PRIORITY_LEVEL_34) \
		| INTC_MAKE_IPR_VALUE(35, INT_PRIORITY_LEVEL_35) \
		| INTC_MAKE_IPR_VALUE(36, INT_PRIORITY_LEVEL_36) \
		| INTC_MAKE_IPR_VALUE(37, INT_PRIORITY_LEVEL_37) \
		| INTC_MAKE_IPR_VALUE(38, INT_PRIORITY_LEVEL_38) \
		| INTC_MAKE_IPR_VALUE(39, INT_PRIORITY_LEVEL_39) \
		| INTC_MAKE_IPR_VALUE(40, INT_PRIORITY_LEVEL_40) \
		)
#define INTC_IPR4_INIT (0\
		| INTC_MAKE_IPR_VALUE(41, INT_PRIORITY_LEVEL_41) \
		| INTC_MAKE_IPR_VALUE(42, INT_PRIORITY_LEVEL_42) \
		| INTC_MAKE_IPR_VALUE(43, INT_PRIORITY_LEVEL_43) \
		| INTC_MAKE_IPR_VALUE(44, INT_PRIORITY_LEVEL_44) \
		| INTC_MAKE_IPR_VALUE(45, INT_PRIORITY_LEVEL_45) \
		| INTC_MAKE_IPR_VALUE(46, INT_PRIORITY_LEVEL_46) \
		| INTC_MAKE_IPR_VALUE(47, INT_PRIORITY_LEVEL_47) \
		| INTC_MAKE_IPR_VALUE(48, INT_PRIORITY_LEVEL_48) \
		)
#define INTC_IPR5_INIT (0\
		| INTC_MAKE_IPR_VALUE(49, INT_PRIORITY_LEVEL_49) \
		| INTC_MAKE_IPR_VALUE(50, INT_PRIORITY_LEVEL_50) \
		| INTC_MAKE_IPR_VALUE(51, INT_PRIORITY_LEVEL_51) \
		| INTC_MAKE_IPR_VALUE(52, INT_PRIORITY_LEVEL_52) \
		| INTC_MAKE_IPR_VALUE(53, INT_PRIORITY_LEVEL_53) \
		| INTC_MAKE_IPR_VALUE(54, INT_PRIORITY_LEVEL_54) \
		| INTC_MAKE_IPR_VALUE(55, INT_PRIORITY_LEVEL_55) \
		| INTC_MAKE_IPR_VALUE(56, INT_PRIORITY_LEVEL_56) \
		)
#define INTC_IPR6_INIT (0\
		| INTC_MAKE_IPR_VALUE(57, INT_PRIORITY_LEVEL_57) \
		| INTC_MAKE_IPR_VALUE(58, INT_PRIORITY_LEVEL_58) \
		| INTC_MAKE_IPR_VALUE(59, INT_PRIORITY_LEVEL_59) \
		| INTC_MAKE_IPR_VALUE(60, INT_PRIORITY_LEVEL_60) \
		| INTC_MAKE_IPR_VALUE(61, INT_PRIORITY_LEVEL_61) \
		| INTC_MAKE_IPR_VALUE(62, INT_PRIORITY_LEVEL_62) \
		)


#endif /* __INTCTARGET_H */

