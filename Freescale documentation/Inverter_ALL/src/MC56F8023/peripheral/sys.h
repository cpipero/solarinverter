/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  sys.h
*
* $Date:      Dec-18-2007$
*
* $Version:   2.3.10.0$
*
* Description: SIM, low voltage interrupt (LVI) and various system 
*              support macros and definitions for MC56F8023
*
*****************************************************************************/

#ifndef __SYS_H
#define __SYS_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before sys.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
* system module identifiers, correspond to module base address
*************************************************************/

#define SYS (&ArchIO.Sim)
#define SIM (&ArchIO.Sim)
#define LVI (&ArchIO.Lvi)

/***********************************************************************
* SYS static configuration items for appconfig.h
***********************************************************************/

/*
    initial register values:

        #ifdef SIM_CONROL_INIT
        #ifdef SIM_CLKOSR_INIT
        #ifdef SIM_GPSA0_INIT
        #ifdef SIM_GPSA1_INIT
        #ifdef SIM_GPSB0_INIT
        #ifdef SIM_GPSB1_INIT
        #ifdef SIM_GPSCD_INIT
        #ifdef SIM_IPS0_INIT
        #ifdef SIM_IPS1_INIT
        #ifdef SIM_IPS2_INIT
        #ifdef SIM_PCR_INIT
        #ifdef SIM_PSD0_INIT
        #ifdef SIM_SD1_INIT
        #ifdef SIM_PCE0_INIT
        #ifdef SIM_PCE1_INIT
        #ifdef SIM_PROT_INIT
        #ifdef LVI_CONTROL_INIT

    #define INTERRUPT_VECTOR_ADDR_yy  userISR //specify interrupt handler routine : e.g. lviISR
    #define INT_PRIORITY_LEVEL_yy     INTC_xxx // interrupt level : (INTC_DISABLED, INTC_LEVEL0,
                                               //                    INTC_LEVEL1 or INTC_LEVEL2)
  where:
         yy  is interrupt vector number
            e.g. On 56F8037
                15 - Low Voltage Detector (Power sense)

*/


/***************************************************
* SYS ioctl commands
****************************************************/
/* command                         Param, description       */

#define SYS_INIT                   /* NULL, SIM & LVI registers initialization acc.to appconfig.h */

#define SYS_STOP                   /* SYS_ENABLE(_PERMANENT)/SYS_DISABLE(_PERMANENT); "stop" instruction ena/dis/perm */
#define SYS_WAIT                   /* SYS_ENABLE(_PERMANENT)/SYS_DISABLE(_PERMANENT); "wait" instruction ena/dis/perm */

#define SYS_SOFTWARE_RESET         /* NULL, issue software reset */
#define SYS_ONCE                   /* SYS_ENABLE/SYS_DISABLE, OnCE module enable */

#define SYS_ENABLE_IN_STOP         /* combination of SYS_xxx_MOD, enable  modules in STOP mode */
#define SYS_DISABLE_IN_STOP        /* combination of SYS_xxx_MOD, disable modules in STOP mode */

#define SYS_PERIPH_CLK_ENABLE      /* combination of SYS_xxx_MOD, enable peripheral clock  */
#define SYS_PERIPH_CLK_DISABLE     /* combination of SYS_xxx_MOD, disable peripheral clock  */

#define SYS_HS_CLOCK_ENABLE        /* combination of SYS_HS_xxx, enable high-speed clock */
#define SYS_HS_CLOCK_DISABLE       /* combination of SYS_HS_xxx, enable high-speed clock */
                                      
#define SYS_SET_TA1_SOURCE         /* one of SYS_TA1SRC_xxx, set internal signal routing */
#define SYS_SET_TA2_SOURCE         /* one of SYS_TA2SRC_xxx, set internal signal routing */
#define SYS_SET_TA3_SOURCE         /* one of SYS_TA3SRC_xxx, set internal signal routing */
#define SYS_SET_PSRC0_SOURCE       /* one of SYS_PSRC0SRC_xxx, set internal signal routing */
#define SYS_SET_PSRC1_SOURCE       /* one of SYS_PSRC1SRC_xxx, set internal signal routing */
#define SYS_SET_PSRC2_SOURCE       /* one of SYS_PSRC2SRC_xxx, set internal signal routing */
#define SYS_SET_FAULT1_SOURCE      /* one of SYS_FAULT1SRC_xxx, set internal signal routing */
#define SYS_SET_FAULT2_SOURCE      /* one of SYS_FAULT2SRC_xxx, set internal signal routing */
#define SYS_SET_DAC0SYNC_SOURCE    /* one of SYS_DAC0SYNCSRC_xxx, set internal signal routing */

#define SYS_SET_A6PAD_FUNCTION     /* one of SYS_A6PAD_xxx, package pin function selection */
#define SYS_SET_A5PAD_FUNCTION     /* one of SYS_A5PAD_xxx, package pin function selection */
#define SYS_SET_A4PAD_FUNCTION     /* one of SYS_A4PAD_xxx, package pin function selection */

#define SYS_SET_B7PAD_FUNCTION     /* one of SYS_B7PAD_xxx, package pin function selection */
#define SYS_SET_B6PAD_FUNCTION     /* one of SYS_B6PAD_xxx, package pin function selection */
#define SYS_SET_B5PAD_FUNCTION     /* one of SYS_B5PAD_xxx, package pin function selection */
#define SYS_SET_B4PAD_FUNCTION     /* one of SYS_B4PAD_xxx, package pin function selection */
#define SYS_SET_B3PAD_FUNCTION     /* one of SYS_B3PAD_xxx, package pin function selection */
#define SYS_SET_B2PAD_FUNCTION     /* one of SYS_B2PAD_xxx, package pin function selection */
#define SYS_SET_B1PAD_FUNCTION     /* one of SYS_B1PAD_xxx, package pin function selection */
#define SYS_SET_B0PAD_FUNCTION     /* one of SYS_B0PAD_xxx, package pin function selection */



#define SYS_SET_POWER_MODE         /* SYS_NORMAL_POWER/SYS_REDUCED_POWER | SYS_POWER_MODE_PERMANENT */
#define SYS_GET_POWER_MODE         /* NULL, returns UWord16 */

#define SYS_TEST_RESET_SOURCE      /* any of SYS_xxx_RESET, get/test type of the previous RESET */
#define SYS_CLEAR_RESET_SOURCE     /* any of SYS_xxx_RESET, clear apropriate bit in reset staus register */

#define SYS_WRITE_SW_CONTROL_REG0  /* UWord16, write SIM software control register 0 */
#define SYS_READ_SW_CONTROL_REG0   /* NULL, returns UWord16 */
#define SYS_WRITE_SW_CONTROL_REG1  /* UWord16, write SIM software control register 1 */
#define SYS_READ_SW_CONTROL_REG1   /* NULL, returns UWord16 */
#define SYS_WRITE_SW_CONTROL_REG2  /* UWord16, write SIM software control register 2 */
#define SYS_READ_SW_CONTROL_REG2   /* NULL, returns UWord16 */
#define SYS_WRITE_SW_CONTROL_REG3  /* UWord16, write SIM software control register 3 */
#define SYS_READ_SW_CONTROL_REG3   /* NULL, returns UWord16 */

#define SYS_READ_LSH_JTAG_ID       /* NULL, returns JTAG ID as UWord16 */
#define SYS_READ_MSH_JTAG_ID       /* NULL, returns JTAG ID as UWord16 */

#define SYS_CLKOUT                 /* SYS_ENABLE/SYS_DISABLE, enable CLKOUT pin */
#define SYS_CLKOUT_SELECT          /* one of SYS_CLKOUT_xxx, select CLSKOUT source */

#define SYS_ACLK_ENABLE            /* any of SYS_ACLK_xx, reprogram A0-A3 pins for dedicated clock-outs */
#define SYS_ACLK_DISABLE           /* any of SYS_ACLK_xx, revert A0-A3 pins to their original function */

#define SYS_WRITE_IO_SHORT_ADDR_LOCATION_REG  /* UWord32, set I/O short address mode base address */
#define SYS_READ_IO_SHORT_ADDR_LOCATION_REG   /* NULL, returns UWord32 */

#define SYS_WPROTECT_CLOCK_SETTINGS /* SYS_ENABLE(_PERMANENT)/SYS_DISABLE(_PERMANENT); write protect PCE, SD and PCR */
#define SYS_WPROTECT_SIGNALS_ROUTING /* SYS_ENABLE(_PERMANENT)/SYS_DISABLE(_PERMANENT); write protect IPS and GPSxx */

#define LVI_INT_ENABLE               /* LVI_22V_LEVEL|LVI_27V_LEVEL, low voltage interrupt enable */
#define LVI_INT_DISABLE              /* LVI_22V_LEVEL|LVI_27V_LEVEL, low voltage interrupt disable */
#define LVI_GET_LOW_VOLTAGE          /* LVI_22V_LEVEL|LVI_27V_LEVEL, test low voltage interrupt flags */
#define LVI_GET_NONSTICKY_INT_SOURCE /* LVI_22V_LEVEL|LVI_27V_LEVEL */
#define LVI_CLEAR_LOW_VOLTAGE_INT    /* LVI_INT|LVI_22V_LEVEL|LVI_27V_LEVEL, clear interrupt flags */

/****************************************************************************
* SYS constants and type declarations used in the ioctl functions
*****************************************************************************/

#define SYS_DISABLE           0
#define SYS_ENABLE            1

/* for permanent enable/disable */
#define SYS_DISABLE_PERMANENT 2
#define SYS_ENABLE_PERMANENT  3

/* High Speed clock enable in modules */
#define SYS_HS_TMRB  SIM_PCR_TMRB
#define SYS_HS_TMRA  SIM_PCR_TMRA
#define SYS_HS_PWM   SIM_PCR_PWM
#define SYS_HS_I2C   SIM_PCR_I2C

/* reset sources */
#define SYS_SW_RESET        SIM_RSTSTS_SWR  
#define SYS_COP_RESET       (SIM_RSTSTS_COP_TOR | SIM_RSTSTS_COP_LOR)
#define SYS_COP_TOR_RESET   SIM_RSTSTS_COP_TOR
#define SYS_COP_LOR_RESET   SIM_RSTSTS_COP_LOR
#define SYS_EXTERN_RESET    SIM_RSTSTS_EXTR
#define SYS_POWER_ON_RESET  SIM_RSTSTS_POR  
#define SYS_ALL_RESETS      (SIM_RSTSTS_SWR | SIM_RSTSTS_COP_TOR | SIM_RSTSTS_COP_LOR | SIM_RSTSTS_EXTR | SIM_RSTSTS_POR)
#define SYS_ANY_RESET       SYS_ALL_RESETS

/* large regulator modes */
#define SYS_NORMAL_POWER            0
#define SYS_REDUCED_POWER           SIM_POWER_LRSTDBY0
#define SYS_POWER_MODE_PERMANENT    SIM_POWER_LRSTDBY1

/* module clock-enables and modules in stop */
#define SYS_CMPB_MOD    ((UWord32)(SIM_PCE0_CMPB))
#define SYS_CMPA_MOD    ((UWord32)(SIM_PCE0_CMPA))
#define SYS_DAC1_MOD    ((UWord32)(SIM_PCE0_DAC1))
#define SYS_DAC0_MOD    ((UWord32)(SIM_PCE0_DAC0))
#define SYS_ADC_MOD     ((UWord32)(SIM_PCE0_ADC))
#define SYS_I2C_MOD     ((UWord32)(SIM_PCE0_I2C))
#define SYS_SCI0_MOD    ((UWord32)(SIM_PCE0_SCI0))
#define SYS_SPI0_MOD    ((UWord32)(SIM_PCE0_SPI0))
#define SYS_PWM_MOD     ((UWord32)(SIM_PCE0_PWM))
#define SYS_PIT0_MOD    (((UWord32)(SIM_PCE1_PIT0))<<16)
#define SYS_TA3_MOD     (((UWord32)(SIM_PCE1_TA3))<<16)
#define SYS_TA2_MOD     (((UWord32)(SIM_PCE1_TA2))<<16)
#define SYS_TA1_MOD     (((UWord32)(SIM_PCE1_TA1))<<16)
#define SYS_TA0_MOD     (((UWord32)(SIM_PCE1_TA0))<<16)

/* clock-enables parameters for bacwardward comaptibility */
#define SYS_CMPB_CLK    SYS_CMPB_MOD  
#define SYS_CMPA_CLK    SYS_CMPA_MOD  
#define SYS_DAC1_CLK    SYS_DAC1_MOD  
#define SYS_DAC0_CLK    SYS_DAC0_MOD  
#define SYS_ADC_CLK     SYS_ADC_MOD 
#define SYS_I2C_CLK     SYS_I2C_MOD 
#define SYS_SCI0_CLK    SYS_SCI0_MOD  
#define SYS_SPI0_CLK    SYS_SPI0_MOD  
#define SYS_PWM_CLK     SYS_PWM_MOD 
#define SYS_TA3_CLK     SYS_TA3_MOD 
#define SYS_TA2_CLK     SYS_TA2_MOD 
#define SYS_TA1_CLK     SYS_TA1_MOD 
#define SYS_TA0_CLK     SYS_TA0_MOD 

/* internal signal routing */
#define SYS_TA3SRC_PIN           SIM_IPS2_TA3_PIN       
#define SYS_TA3SRC_PWMSYNC       SIM_IPS2_TA3_PWMSYNC
#define SYS_TA2SRC_PIN           SIM_IPS2_TA2_PIN    
#define SYS_TA2SRC_PWMSYNC       SIM_IPS2_TA2_PWMSYNC
#define SYS_TA1SRC_PIN           SIM_IPS2_TA1_PIN    
#define SYS_TA1SRC_PWMSYNC       SIM_IPS2_TA1_PWMSYNC
#define SYS_DAC0SYNCSRC_PIT0     SIM_IPS1_DSYNC0_PIT0   
#define SYS_DAC0SYNCSRC_PWMSYNC  SIM_IPS1_DSYNC0_PWMSYNC
#define SYS_DAC0SYNCSRC_TA0      SIM_IPS1_DSYNC0_TA0    
#define SYS_DAC0SYNCSRC_TA1      SIM_IPS1_DSYNC0_TA1    
#define SYS_PSRC2SRC_PIN         SIM_IPS0_PSRC2_PIN      
#define SYS_PSRC2SRC_TA3         SIM_IPS0_PSRC2_TA3      
#define SYS_PSRC2SRC_ADCSAMP2    SIM_IPS0_PSRC2_ADCSAMP2 
#define SYS_PSRC2SRC_COUTA_A     SIM_IPS0_PSRC2_COUTA_A  
#define SYS_PSRC2SRC_COUTB_A     SIM_IPS0_PSRC2_COUTB_A  
#define SYS_PSRC1SRC_PIN         SIM_IPS0_PSRC1_PIN      
#define SYS_PSRC1SRC_TA2         SIM_IPS0_PSRC1_TA2      
#define SYS_PSRC1SRC_ADCSAMP1    SIM_IPS0_PSRC1_ADCSAMP1 
#define SYS_PSRC1SRC_COUTA_A     SIM_IPS0_PSRC1_COUTA_A  
#define SYS_PSRC1SRC_COUTB_A     SIM_IPS0_PSRC1_COUTB_A  
#define SYS_PSRC0SRC_PIN         SIM_IPS0_PSRC0_PIN      
#define SYS_PSRC0SRC_TA0         SIM_IPS0_PSRC0_TA0      
#define SYS_PSRC0SRC_ADCSAMP0    SIM_IPS0_PSRC0_ADCSAMP0 
#define SYS_PSRC0SRC_COUTA_A     SIM_IPS0_PSRC0_COUTA_A  
#define SYS_PSRC0SRC_COUTB_A     SIM_IPS0_PSRC0_COUTB_A  
#define SYS_FAULT2SRC_PIN        SIM_IPS0_FAULT2_PIN    
#define SYS_FAULT2SRC_COUTB_A    SIM_IPS0_FAULT2_COUTB_A
#define SYS_FAULT1SRC_PIN        SIM_IPS0_FAULT1_PIN    
#define SYS_FAULT1SRC_COUTA_A    SIM_IPS0_FAULT1_COUTA_A


/* pad functions */
#define SYS_A4PAD_PWM4      SIM_GPSA0_A4_PWM4
#define SYS_A4PAD_FAULT1    SIM_GPSA0_A4_FAULT1
#define SYS_A4PAD_TA2       SIM_GPSA0_A4_TA2
#define SYS_A5PAD_PWM5      SIM_GPSA0_A5_PWM5
#define SYS_A5PAD_FAULT2    SIM_GPSA0_A5_FAULT2
#define SYS_A5PAD_TA3       SIM_GPSA0_A5_TA3
#define SYS_A6PAD_FAULT0    SIM_GPSA0_A6_FAULT0
#define SYS_A6PAD_TA0       SIM_GPSA0_A6_TA0
#define SYS_B0PAD_SCLK0     SIM_GPSB0_B0_SCLK0
#define SYS_B0PAD_SCL       SIM_GPSB0_B0_SCL
#define SYS_B1PAD_SS0       SIM_GPSB0_B1_SS0
#define SYS_B1PAD_SDA       SIM_GPSB0_B1_SDA
#define SYS_B2PAD_MISO0     SIM_GPSB0_B2_MISO0
#define SYS_B2PAD_TA2       SIM_GPSB0_B2_TA2
#define SYS_B2PAD_PSRC0     SIM_GPSB0_B2_PSRC0
#define SYS_B3PAD_MOSI0     SIM_GPSB0_B3_MOSI0
#define SYS_B3PAD_TA3       SIM_GPSB0_B3_TA3
#define SYS_B3PAD_PSRC1     SIM_GPSB0_B3_PSRC1
#define SYS_B4PAD_TA0       SIM_GPSB0_B4_TA0
#define SYS_B4PAD_CLKO      SIM_GPSB0_B4_CLKO
#define SYS_B4PAD_SS1       SIM_GPSB0_B4_SS1
#define SYS_B4PAD_PSRC2     SIM_GPSB0_B4_PSRC2
#define SYS_B5PAD_TA1       SIM_GPSB0_B5_TA1
#define SYS_B5PAD_FAULT3    SIM_GPSB0_B5_FAULT3
#define SYS_B5PAD_CLKIN     SIM_GPSB0_B5_CLKIN
#define SYS_B6PAD_RXD       SIM_GPSB0_B6_RXD
#define SYS_B6PAD_SDA       SIM_GPSB0_B6_SDA
#define SYS_B6PAD_CLKIN     SIM_GPSB0_B6_CLKIN
#define SYS_B7PAD_TXD0      SIM_GPSB1_B7_TXD0
#define SYS_B7PAD_SCL       SIM_GPSB1_B7_SCL

/* clkout mux */
#define SYS_CLKOUT_SYSCLK   0x00    /* sys_clk */
#define SYS_CLKOUT_IPBCLK   0x01    /* periph_clk */
#define SYS_CLKOUT_HSCLK    0x02    /* hs_perf clk */

/* clock output on GPIO_A */
#define SYS_ACLK_OSC        SIM_CLKOSR_PWM3 /* A3 as oscillator out */
#define SYS_ACLK_SYSCLK     SIM_CLKOSR_PWM2 /* A2 as sys_clk */
#define SYS_ACLK_SYSCLK2x   SIM_CLKOSR_PWM1 /* A1 as sys_clk2x */
#define SYS_ACLK_SYSCLK3x   SIM_CLKOSR_PWM0 /* A0 as HS clock */

/* LVI levels */
#define LVI_22V_LEVEL       LVI_CONTROL_LVIE22 
#define LVI_27V_LEVEL       LVI_CONTROL_LVIE27
#define LVI_INT             0x0004

/****************************************************************************
* register bit names and masks
*****************************************************************************/

/* SIM_CONTROL */
#define SIM_CONTROL_ONCEEBL             0x0020
#define SIM_CONTROL_SWRST               0x0010
#define SIM_CONTROL_STOPDIS_MASK        0x000c
#define SIM_CONTROL_STOPDIS_ENABLE      0x0000
#define SIM_CONTROL_STOPDIS_SOFT        0x0004
#define SIM_CONTROL_STOPDIS_PERMANENT   0x0008
#define SIM_CONTROL_WAITDIS_MASK        0x0003
#define SIM_CONTROL_WAITDIS_ENABLE      0x0000
#define SIM_CONTROL_WAITDIS_SOFT        0x0001
#define SIM_CONTROL_WAITDIS_PERMANENT   0x0002

/* SIM_RSTSTS */
#define SIM_RSTSTS_SWR          0x0040
#define SIM_RSTSTS_COP_TOR      0x0020
#define SIM_RSTSTS_COP_LOR      0x0010
#define SIM_RSTSTS_EXTR         0x0008
#define SIM_RSTSTS_POR          0x0004

/* SIM_POWER */
#define SIM_POWER_LRSTDBY0      0x0001
#define SIM_POWER_LRSTDBY1      0x0002
#define SIM_POWER_LRSTDBY_MASK  0x0003

/* SIM_CLKOSR */
#define SIM_CLKOSR_PWM3         0x0200
#define SIM_CLKOSR_PWM2         0x0100
#define SIM_CLKOSR_PWM1         0x0080
#define SIM_CLKOSR_PWM0         0x0040
#define SIM_CLKOSR_CLKDIS       0x0020
#define SIM_CLKOSR_CLKOSEL_MASK 0x001f
#define SIM_CLKOSR_CLKOSEL_SYSCLK 0x0000
#define SIM_CLKOSR_CLKOSEL_IPBCLK 0x0001
#define SIM_CLKOSR_CLKOSEL_HSCLK  0x0002

/* SIM_PCR */
#define SIM_PCR_TMRB            0x8000
#define SIM_PCR_TMRA            0x4000
#define SIM_PCR_PWM             0x2000
#define SIM_PCR_I2C             0x1000

/* SIM_PCE0 */
#define SIM_PCE0_CMPB           0x8000
#define SIM_PCE0_CMPA           0x4000
#define SIM_PCE0_DAC1           0x2000
#define SIM_PCE0_DAC0           0x1000
#define SIM_PCE0_ADC            0x0400
#define SIM_PCE0_I2C            0x0040
#define SIM_PCE0_SCI0           0x0010
#define SIM_PCE0_SPI0           0x0004
#define SIM_PCE0_PWM            0x0001

/* SIM_PCE1 */
#define SIM_PCE1_PIT0           0x1000
#define SIM_PCE1_TA3            0x0008
#define SIM_PCE1_TA2            0x0004
#define SIM_PCE1_TA1            0x0002
#define SIM_PCE1_TA0            0x0001

/* SIM_SD0 */
#define SIM_SD0_CMPB            0x8000
#define SIM_SD0_CMPA            0x4000
#define SIM_SD0_DAC1            0x2000
#define SIM_SD0_DAC0            0x1000
#define SIM_SD0_ADC             0x0400
#define SIM_SD0_I2C             0x0040
#define SIM_SD0_SCI0            0x0010
#define SIM_SD0_SPI0            0x0004
#define SIM_SD0_PWM             0x0001

/* SIM_SD1 */
#define SIM_SD1_PIT0            0x1000
#define SIM_SD1_TA3             0x0008
#define SIM_SD1_TA2             0x0004
#define SIM_SD1_TA1             0x0002
#define SIM_SD1_TA0             0x0001

/* SIM_PROT */
#define SIM_PROT_PCEP_MASK      0x000c
#define SIM_PROT_PCEP_PROT      0x0004
#define SIM_PROT_PCEP_LOCK      0x0008
#define SIM_PROT_GIPSP_MASK     0x0003
#define SIM_PROT_GIPSP_PROT     0x0001
#define SIM_PROT_GIPSP_LOCK     0x0002

/* SIM_GPSA0 */
#define SIM_GPSA0_A6            0x1000
#define SIM_GPSA0_A6_FAULT0     0x0000
#define SIM_GPSA0_A6_TA0        0x1000
#define SIM_GPSA0_A5_MASK       0x0c00
#define SIM_GPSA0_A5_PWM5       0x0000
#define SIM_GPSA0_A5_FAULT2     0x0400
#define SIM_GPSA0_A5_TA3        0x0800
#define SIM_GPSA0_A4_MASK       0x0300
#define SIM_GPSA0_A4_PWM4       0x0000
#define SIM_GPSA0_A4_FAULT1     0x0100
#define SIM_GPSA0_A4_TA2        0x0200


/* SIM_GPSB0 */
#define SIM_GPSB0_B6_MASK       0x6000
#define SIM_GPSB0_B6_RXD        0x0000
#define SIM_GPSB0_B6_SDA        0x2000
#define SIM_GPSB0_B6_CLKIN      0x4000
#define SIM_GPSB0_B5_MASK       0x1800
#define SIM_GPSB0_B5_TA1        0x0000
#define SIM_GPSB0_B5_FAULT3     0x0800
#define SIM_GPSB0_B5_CLKIN      0x1000
#define SIM_GPSB0_B4_MASK       0x0700
#define SIM_GPSB0_B4_TA0        0x0000
#define SIM_GPSB0_B4_CLKO       0x0100
#define SIM_GPSB0_B4_SS1        0x0200
#define SIM_GPSB0_B4_PSRC2      0x0400
#define SIM_GPSB0_B3_MASK       0x00c0
#define SIM_GPSB0_B3_MOSI0      0x0000
#define SIM_GPSB0_B3_TA3        0x0040
#define SIM_GPSB0_B3_PSRC1      0x0080
#define SIM_GPSB0_B2_MASK       0x0030
#define SIM_GPSB0_B2_MISO0      0x0000
#define SIM_GPSB0_B2_TA2        0x0010
#define SIM_GPSB0_B2_PSRC0      0x0020
#define SIM_GPSB0_B1            0x0004
#define SIM_GPSB0_B1_SS0        0x0000
#define SIM_GPSB0_B1_SDA        0x0004
#define SIM_GPSB0_B0            0x0001
#define SIM_GPSB0_B0_SCLK0      0x0000
#define SIM_GPSB0_B0_SCL        0x0001

/* SIM_GPSB1 */
#define SIM_GPSB1_B7            0x0001
#define SIM_GPSB1_B7_TXD0       0x0000
#define SIM_GPSB1_B7_SCL        0x0001


/* SIM_IPS0 */
#define SIM_IPS0_FAULT2         0x2000
#define SIM_IPS0_FAULT2_PIN     0x0000
#define SIM_IPS0_FAULT2_COUTB_A 0x2000
#define SIM_IPS0_FAULT1         0x0800
#define SIM_IPS0_FAULT1_PIN     0x0000
#define SIM_IPS0_FAULT1_COUTA_A 0x0800
#define SIM_IPS0_PSRC2_MASK     0x01c0
#define SIM_IPS0_PSRC2_PIN      0x0000
#define SIM_IPS0_PSRC2_TA3      0x0040
#define SIM_IPS0_PSRC2_ADCSAMP2 0x0080
#define SIM_IPS0_PSRC2_COUTA_A  0x00c0
#define SIM_IPS0_PSRC2_COUTB_A  0x0100
#define SIM_IPS0_PSRC1_MASK     0x0038
#define SIM_IPS0_PSRC1_PIN      0x0000
#define SIM_IPS0_PSRC1_TA2      0x0008
#define SIM_IPS0_PSRC1_ADCSAMP1 0x0010
#define SIM_IPS0_PSRC1_COUTA_A  0x0018
#define SIM_IPS0_PSRC1_COUTB_A  0x0020
#define SIM_IPS0_PSRC0_MASK     0x0007
#define SIM_IPS0_PSRC0_PIN      0x0000
#define SIM_IPS0_PSRC0_TA0      0x0001
#define SIM_IPS0_PSRC0_ADCSAMP0 0x0002
#define SIM_IPS0_PSRC0_COUTA_A  0x0003
#define SIM_IPS0_PSRC0_COUTB_A  0x0004

/* SIM_IPS1 */
#define SIM_IPS1_DSYNC0_MASK    0x0007
#define SIM_IPS1_DSYNC0_PIT0    0x0000
#define SIM_IPS1_DSYNC0_PIT1    0x0001
#define SIM_IPS1_DSYNC0_PIT2    0x0002
#define SIM_IPS1_DSYNC0_PWMSYNC 0x0003
#define SIM_IPS1_DSYNC0_TA0     0x0004
#define SIM_IPS1_DSYNC0_TA1     0x0005

/* SIM_IPS2 */
#define SIM_IPS2_TA3            0x1000
#define SIM_IPS2_TA3_PIN        0x0000
#define SIM_IPS2_TA3_PWMSYNC    0x1000
#define SIM_IPS2_TA2            0x0100
#define SIM_IPS2_TA2_PIN        0x0000
#define SIM_IPS2_TA2_PWMSYNC    0x0100
#define SIM_IPS2_TA1            0x0010
#define SIM_IPS2_TA1_PIN        0x0000
#define SIM_IPS2_TA1_PWMSYNC    0x0010

/* LVI_CONTROL */
#define LVI_CONTROL_LVIE27      0x0002
#define LVI_CONTROL_LVIE22      0x0001

/* LVI_STATUS */
#define LVI_STATUS_LVI          0x0010
#define LVI_STATUS_LVIS27S      0x0008
#define LVI_STATUS_LVIS22S      0x0004
#define LVI_STATUS_LVIS27       0x0002
#define LVI_STATUS_LVIS22       0x0001

/***********************************************************************
* SYS control command macros
***********************************************************************/

/* SYS initialization */
void sysInit(arch_sSIM *pSimBase);
#define ioctlSYS_INIT(pSimBase, param) sysInit(pSimBase)

/* reprogramable "stop" instruction disable */ 
#define ioctlSYS_STOP(pSimBase, param) \
  periphBitGrpSet(SIM_CONTROL_STOPDIS_MASK, (param)<<2, &((pSimBase)->sim_control))

/* reprogramable "wait" instruction disable */ 
#define ioctlSYS_WAIT(pSimBase, param) \
  periphBitGrpSet(SIM_CONTROL_WAITDIS_MASK, param, &((pSimBase)->sim_control))

/* subset of teh ones above, maintained for backward compatibility */
#define ioctlSYS_STOP_PERMANENT_DISABLE(pSimBase, param) \
  periphBitGrpSet(SIM_CONTROL_STOPDIS_MASK, (SYS_DISABLE_PERMANENT)<<2, &((pSimBase)->sim_control))
#define ioctlSYS_WAIT_PERMANENT_DISABLE(pSimBase, param) \
  periphBitGrpSet(SIM_CONTROL_WAITDIS_MASK, SYS_DISABLE_PERMANENT, &((pSimBase)->sim_control))

/* issue software reset */
#define ioctlSYS_SOFTWARE_RESET(pSimBase, param) \
  periphBitSet(SIM_CONTROL_SWRST, &((pSimBase)->sim_control))

/* OnCE enable/disable */
#define ioctlSYS_ONCE(pSimBase, param) \
  if(param) periphBitSet(SIM_CONTROL_ONCEEBL, &((pSimBase)->sim_control));\
  else periphBitClear(SIM_CONTROL_ONCEEBL, &((pSimBase)->sim_control))

/* backward compatibility macros */
#define ioctlSYS_ONCE_ENABLE(pSimBase, param) \
  periphBitSet(SIM_CONTROL_ONCEEBL, &((pSimBase)->sim_control))
#define ioctlSYS_ONCE_DISABLE(pSimBase, param) \
  periphBitClear(SIM_CONTROL_ONCEEBL, &((pSimBase)->sim_control))

/* enable modules in STOP mode */
#define ioctlSYS_ENABLE_IN_STOP(pSimBase, param) { \
  if((param) & 0xffff0000L) periphBitSet((UWord16)((param)>>16), &((pSimBase)->sim_sd1));   \
  if((param) & 0x0000ffff)  periphBitSet((UWord16)((param)&0xffff), &((pSimBase)->sim_sd0)); }
  
/* disable modules in STOP mode */
#define ioctlSYS_DISABLE_IN_STOP(pSimBase, param) { \
  if((param) & 0xffff0000L) periphBitClear((UWord16)((param)>>16), &((pSimBase)->sim_sd1));   \
  if((param) & 0x0000ffff)  periphBitClear((UWord16)((param)&0xffff), &((pSimBase)->sim_sd0)); }

/* enable peripheral clock */
#define ioctlSYS_PERIPH_CLK_ENABLE(pSimBase, param) { \
  if((param) & 0xffff0000L) periphBitSet((UWord16)((param)>>16), &((pSimBase)->sim_pce1));   \
  if((param) & 0x0000ffff)  periphBitSet((UWord16)((param)&0xffff), &((pSimBase)->sim_pce0)); }

/* disable peripheral clock */
#define ioctlSYS_PERIPH_CLK_DISABLE(pSimBase, param)  { \
  if((param) & 0xffff0000L) periphBitClear((UWord16)((param)>>16), &((pSimBase)->sim_pce1));   \
  if((param) & 0x0000ffff)  periphBitClear((UWord16)((param)&0xffff), &((pSimBase)->sim_pce0)); }

/* enable High_Speed clock for peripheral modules */
#define ioctlSYS_HS_CLOCK_ENABLE(pSimBase, param) \
  periphBitSet(param, &((pSimBase)->sim_pcr))

/* disable High_Speed clock for peripheral modules */
#define ioctlSYS_HS_CLOCK_DISABLE(pSimBase, param) \
  periphBitClear(param, &((pSimBase)->sim_pcr))

/* pins configuration usign GPS registers */
#define ioctlSYS_SET_A4PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSA0_A4_MASK, param, &((pSimBase)->sim_gpsa0))

#define ioctlSYS_SET_A5PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSA0_A5_MASK, param, &((pSimBase)->sim_gpsa0))

#define ioctlSYS_SET_A6PAD_FUNCTION(pSimBase, param) \
  if(param) periphBitSet(SIM_GPSA0_A6, &((pSimBase)->sim_gpsa0)); \
  else periphBitClear(SIM_GPSA0_A6, &((pSimBase)->sim_gpsa0))



#define ioctlSYS_SET_B0PAD_FUNCTION(pSimBase, param) \
  if(param) periphBitSet(SIM_GPSB0_B0, &((pSimBase)->sim_gpsb0)); \
  else periphBitClear(SIM_GPSB0_B0, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B1PAD_FUNCTION(pSimBase, param) \
  if(param) periphBitSet(SIM_GPSB0_B1, &((pSimBase)->sim_gpsb0)); \
  else periphBitClear(SIM_GPSB0_B1, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B2PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSB0_B2_MASK, param, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B3PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSB0_B3_MASK, param, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B4PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSB0_B4_MASK, param, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B5PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSB0_B5_MASK, param, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B6PAD_FUNCTION(pSimBase, param) \
  periphBitGrpSet(SIM_GPSB0_B6_MASK, param, &((pSimBase)->sim_gpsb0))

#define ioctlSYS_SET_B7PAD_FUNCTION(pSimBase, param) \
  if(param) periphBitSet(SIM_GPSB1_B7, &((pSimBase)->sim_gpsb1)); \
  else periphBitClear(SIM_GPSB1_B7, &((pSimBase)->sim_gpsb1))





/* internal signal routing in IPS registers */
#define ioctlSYS_SET_FAULT1_SOURCE(pSimBase, param) \
  if(param) periphBitSet(SIM_IPS0_FAULT1, &((pSimBase)->sim_ips0)); \
  else periphBitClear(SIM_IPS0_FAULT1, &((pSimBase)->sim_ips0))

#define ioctlSYS_SET_FAULT2_SOURCE(pSimBase, param) \
  if(param) periphBitSet(SIM_IPS0_FAULT2, &((pSimBase)->sim_ips0)); \
  else periphBitClear(SIM_IPS0_FAULT2, &((pSimBase)->sim_ips0))

#define ioctlSYS_SET_PSRC0_SOURCE(pSimBase, param) \
  periphBitGrpSet(SIM_IPS0_PSRC0_MASK, param, &((pSimBase)->sim_ips0))

#define ioctlSYS_SET_PSRC1_SOURCE(pSimBase, param) \
  periphBitGrpSet(SIM_IPS0_PSRC1_MASK, param, &((pSimBase)->sim_ips0))

#define ioctlSYS_SET_PSRC2_SOURCE(pSimBase, param) \
  periphBitGrpSet(SIM_IPS0_PSRC2_MASK, param, &((pSimBase)->sim_ips0))

#define ioctlSYS_SET_DAC0SYNC_SOURCE(pSimBase, param) \
  periphBitGrpSet(SIM_IPS1_DSYNC0_MASK, param, &((pSimBase)->sim_ips1))


#define ioctlSYS_SET_TA1_SOURCE(pSimBase, param) \
  if(param) periphBitSet(SIM_IPS2_TA1, &((pSimBase)->sim_ips2)); \
  else periphBitClear(SIM_IPS2_TA1, &((pSimBase)->sim_ips2))

#define ioctlSYS_SET_TA2_SOURCE(pSimBase, param) \
  if(param) periphBitSet(SIM_IPS2_TA2, &((pSimBase)->sim_ips2)); \
  else periphBitClear(SIM_IPS2_TA2, &((pSimBase)->sim_ips2))

#define ioctlSYS_SET_TA3_SOURCE(pSimBase, param) \
  if(param) periphBitSet(SIM_IPS2_TA3, &((pSimBase)->sim_ips2)); \
  else periphBitClear(SIM_IPS2_TA3, &((pSimBase)->sim_ips2))

/* set large-regulator mode */
#define ioctlSYS_SET_POWER_MODE(pSimBase, param) \
  periphBitGrpZS(SIM_POWER_LRSTDBY_MASK, param, &((pSimBase)->sim_power))

/* get large-regulator mode */
#define ioctlSYS_GET_POWER_MODE(pSimBase, param) \
  periphBitTest(SIM_POWER_LRSTDBY_MASK, &((pSimBase)->sim_power))
  
/* test reset status SWR, COPR, EXTR, POR bits */
#define ioctlSYS_TEST_RESET_SOURCE(pSimBase, param) \
  periphBitTest(param, &((pSimBase)->sim_rststs))

/* clear reset status SWR, COPR, EXTR, POR bits */
#define ioctlSYS_CLEAR_RESET_SOURCE(pSimBase, param) \
  periphMemInvBitSet(param, &((pSimBase)->sim_rststs))

/* SIM software control registers */ 
#define ioctlSYS_WRITE_SW_CONTROL_REG0(pSimBase, param) \
  periphMemWrite(param, &((pSimBase)->sim_scr0))

#define ioctlSYS_WRITE_SW_CONTROL_REG1(pSimBase, param) \
  periphMemWrite(param, &((pSimBase)->sim_scr1))

#define ioctlSYS_WRITE_SW_CONTROL_REG2(pSimBase, param) \
  periphMemWrite(param, &((pSimBase)->sim_scr2))

#define ioctlSYS_WRITE_SW_CONTROL_REG3(pSimBase, param) \
  periphMemWrite(param, &((pSimBase)->sim_scr3))

#define ioctlSYS_READ_SW_CONTROL_REG0(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_scr0))

#define ioctlSYS_READ_SW_CONTROL_REG1(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_scr1))

#define ioctlSYS_READ_SW_CONTROL_REG2(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_scr2))

#define ioctlSYS_READ_SW_CONTROL_REG3(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_scr3))

/* enable/disable CLKOUT pin */
#define ioctlSYS_CLKOUT(pSimBase, param) \
  if(param) periphBitClear(SIM_CLKOSR_CLKDIS, &((pSimBase)->sim_clkosr));\
  else periphBitSet(SIM_CLKOSR_CLKDIS, &((pSimBase)->sim_clkosr))
  
/* enable/disable CLKOUT pin, backward comaptibility only */
#define ioctlSYS_CLKOUT_ENABLE(pSimBase, param)  \
  periphBitClear(SIM_CLKOSR_CLKDIS, &((pSimBase)->sim_clkosr))
#define ioctlSYS_CLKOUT_DISABLE(pSimBase, param) \
  periphBitSet(SIM_CLKOSR_CLKDIS, &((pSimBase)->sim_clkosr))

/* select CLSKOUT source */
#define ioctlSYS_CLKOUT_SELECT(pSimBase, param)  \
  periphBitGrpSet(SIM_CLKOSR_CLKOSEL_MASK, param, &((pSimBase)->sim_clkosr))

/* JTAG ID */
#define ioctlSYS_READ_LSH_JTAG_ID(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_lsh_id))

#define ioctlSYS_READ_MSH_JTAG_ID(pSimBase, param) \
  periphMemRead(&((pSimBase)->sim_msh_id))

/* reprogram A0-A3 pins for dedicated clock-outs */
#define ioctlSYS_ACLK_ENABLE(pSimBase, param)    \
  periphBitSet(param, &((pSimBase)->sim_clkosr))

/* revert A0-A3 pins to their original function */
#define ioctlSYS_ACLK_DISABLE(pSimBase, param)   \
  periphBitClear(param, &((pSimBase)->sim_clkosr))

/* memory reference via the I/O short address mode */
#define ioctlSYS_WRITE_IO_SHORT_ADDR_LOCATION_REG(pSimBase, param) \
  { periphMemWrite((UWord16)(((UWord32)(param)) & 0xFFFF), &((pSimBase)->sim_isall));   \
    periphMemWrite((UWord16)(((UWord32)(param)) >> 16), &((pSimBase)->sim_isalh));  }

#define ioctlSYS_READ_IO_SHORT_ADDR_LOCATION_REG(pSimBase, param) \
  (  (UWord32) periphMemRead(&((pSimBase)->sim_isall)) | \
    ((UWord32)(periphMemRead(&((pSimBase)->sim_isalh)) & 3) << 16) )

/* write protect PCE, SD and PCR */
#define ioctlSYS_WPROTECT_CLOCK_SETTINGS(pSimBase, param)    \
  periphBitGrpSet(SIM_PROT_PCEP_MASK, ((param)<<2), &((pSimBase)->sim_prot))

/* write protect IPS and GPSxx */
#define ioctlSYS_WPROTECT_SIGNALS_ROUTING(pSimBase, param)    \
  periphBitGrpSet(SIM_PROT_GIPSP_MASK, (param), &((pSimBase)->sim_prot))

/********** LVI **********/

/* LVI low voltage interrupt enable */
#define ioctlLVI_INT_ENABLE(pLviBase, param) \
  periphBitSet(param, &((pLviBase)->lvictlr))

/* LVI low voltage interrupt disable */
#define ioctlLVI_INT_DISABLE(pLviBase, param) \
  periphBitClear(param, &((pLviBase)->lvictlr))

/* LVI low voltage interrupt selection */
#define ioctlLVI_INT_SELECT(pLviBase, param) \
  periphBitGrpSR(LVI_CONTROL_LVIE22|LVI_CONTROL_LVIE27, param, &((pLviBase)->lvictlr))

/* test LVI Status LVIS27, LVIS22 bits */
#define ioctlLVI_GET_LOW_VOLTAGE(pLviBase, param) \
  periphBitTest(((param) << 2), &((pLviBase)->lvisr))

#define ioctlLVI_GET_NONSTICKY_INT_SOURCE(pLviBase, param) \
  periphBitTest(param, &((pLviBase)->lvisr))

/* clear LVI Status LVIS27, LVIS22 bits (cleared by writing "1") */

/* on 802x/3x, the LVI INT flag sometimes fails to get cleared. This typically
   happens when result of LVI equation: 
            LVI = (LVIS27 AND LVIE27) or (LVIS22 AND LVIE22) 
   is TRUE during clearing. It is more likely to happen when PLL is off. 
   Also, rising of the LVI interrupt is sensitive to edges of the LVI bit, 
   which means the interrupt is never raised again if clearing LVI bit fails.
*/    
#if 0  
#define ioctlLVI_CLEAR_LOW_VOLTAGE_INT(pLviBase, param) \
  periphMemWrite(((param) << 2), &((pLviBase)->lvisr))
#else
/* a workaround is to clear the LVI INT flag during LVIExx temporarily zeroed */
#define ioctlLVI_CLEAR_LOW_VOLTAGE_INT(pLviBase, param) \
  if((param) & LVI_INT) \
  { UWord16 tmp = periphMemRead(&((pLviBase)->lvictlr)); \
    periphMemWrite(0, &((pLviBase)->lvictlr)); \
    periphMemWrite(((param) << 2), &((pLviBase)->lvisr)); \
    periphMemWrite(tmp, &((pLviBase)->lvictlr)); } \
  else periphMemWrite(((param) << 2), &((pLviBase)->lvisr));
#endif

#ifdef __cplusplus
}
#endif

#endif

