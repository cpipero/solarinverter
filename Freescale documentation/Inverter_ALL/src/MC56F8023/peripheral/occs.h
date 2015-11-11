/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name: occs.h
*
* $Date:      May-4-2009$
*
* $Version:   2.3.46.0$
*
* Description: Header file for the On-chip Clock Synthesis (OCCS) driver.
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  OCCS_VERSION_1 .. 56F83xx devices, see MC56F8300UM.pdf
*  OCCS_VERSION_2 .. 56F801x devices, see MC56F8000RM.pdf
*  OCCS_VERSION_3 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  OCCS_VERSION_4 .. 56F800x devices, see MC56F80006RM.pdf
*
*******************************************************************************/

#ifndef __OCCS_H
#define __OCCS_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before occs.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
    OCCS base address used as device handle in ioctl()
*******************************************************************************/

#define OCCS (&ArchIO.Pll)

/*************************************************************
* arch.h should define device-specific information about OCCS
**************************************************************/

#if !defined(OCCS_VERSION) || !defined(OCCS_HAS_RXOSC)
#error OCCS not properly described in arch.h (old Quick_Start version?)
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The On-Chip Clock Synthesis (OCCS) module allows product design using inexpensive
* 8MHz crystals to run the MC56F8300 at frequencies up to 60Mhz. This module provides
* the 2X system clock frequency to the System Integration Module (SIM), using it to
* generate the various chip clocks. This module also produces the OSC_CLK signals.
* 
* The OCCS module interfaces with the Oscillator and PLL, as well as having an On-Chip
* prescaler. The OCCS module characteristics include:
* • Oscillator can be crystal controlled or driven from an external clock generator
* • Two-bit prescaler can divide oscillator output by 1, 2, 4 or 8 prior to its
*   use as the PLL source clock
* • Two-bit postscaler provides similar control for the PLL output
* • Ability to power down the internal PLL
* • Provides 2X master clock frequency and OSC_CLK signals.
* • Safety shutdown feature available in the event the PLL reference clock disappears
* 
* The clock generation module provides the programming interface for both the PLL
* and on and off-chip oscillators.
*
* For more information, please refer to the user manual for the particular chip that you
* are using, such as the MC56F8300 Peripheral Manual, for a description
* of the OCCS device.
*
* The OCCS device driver interface uses "ioctl" call to control specific OCCS functions
* during operation. For details see "ioctl" call.
*
* Note: A simplified OCCS module is implemented on MF56F80xx devices (no prescaler, 
*       fixed PLL multiplier). Consult MC56F8000 Peripheral Manual for more details.
*
******************************************************************************/

/*******************************************************************************
    Defines for appconfig.h
********************************************************************************/

/*
    #define EXTCLK                  8000000UL   // board oscillator frequency
	#define EXTCLK 					9000000L	//
	EXTAL
    #define INT_VECTOR_ADDR_yy      occsISR
    #define INT_PRIORITY_LEVEL_yy   // one of INTC_DISABLED, INTC_LEVEL0, INTC_LEVEL1 or INTC_LEVEL2

    #define OCCS_PLLCR_INIT         0x82        // lock detector on, postscaler (PLL) used
    #define OCCS_PLLDB_INIT         0x2019      // 52 MHz MC core, 208 MHz VCO
    #define OCCS_OSCTL_INIT         0x0000
    #define OCCS_REQUIRED_LOCK_MODE 0x20        // 0x20 (LCK0-fine) or 0x40 (LCK1-coarse)

    where:  
         yy is PLL (OCCS) interrupt vector number (e.g. 21 on MC56F8346)
*/


/*******************************************************************************
    ioctl() commands
********************************************************************************
        command                     parameters and commentary */
        
#define OCCS_INIT                   /* NULL, occsInit function is called (initialization) */

#define OCCS_SET_LORTP              /* value 1..15, sets Loss-of-clock timer period in Fout/2 cycles */

#define OCCS_INT_ENABLE             /* (OCCS_LOL1_INT_ANY_EDGE / OCCS_LOL1_INT_FALLING_EDGE / OCCS_LOL1_INT_RISING_EDGE) |
                                       (OCCS_LOL0_INT_ANY_EDGE / OCCS_LOL0_INT_FALLING_EDGE / OCCS_LOL0_INT_RISING_EDGE) |
                                        OCCS_LOSS_OF_CLOCK_INT */
#define OCCS_INT_DISABLE            /* OCCS_LOL1_INT |  OCCS_LOL0_INT | OCCS_LOSS_OF_CLOCK_INT */

#define OCCS_LOCK_DETECTOR          /* OCCS_ENABLE / OCCS_DISABLE */

#define OCCS_SET_ZCLOCK_SOURCE      /* OCCS_POSTSCALER_OUTPUT / OCCS_PRESCALER_OUTPUT(83xx only) / 
                                       OCCS_MSTR_OSC_OUTPUT(80xx only)  
                                       (800x) - OCCS_xxx_OSC_OUTPUT (PLL/MSTR) */
#define OCCS_GET_ZCLOCK_SOURCE      /* NULL, returns the same values as OCCS_SET_ZCLOCK_SOURCE parameters,
                                       any other value means synchronizing is in progress */

#define OCCS_READ_FLAG              /* OCCS_STATUS_xxx (LOCK_LOST_INT1 | LOCK_LOST_INT0 | CLOCK_LOST | ( LOCK_1 | LOCK_0) | POWER_DOWN | ZCLOCK | CRYSTAL_READY(800x only))
                                       returns 0 if flag is cleared, non-zero if flag is set */
#define OCCS_CLEAR_FLAG             /* OCCS_STATUS_xxx (LOCK_LOST_INT1 | LOCK_LOST_INT0 | CLOCK_LOST) */

#define OCCS_GET_IPBUS_FREQ         /* oscillator frequency [Hz](UWord32), returns IPBus Clock frequency [Hz] (UWord32) */

#define OCCS_WRITE_CONTROL_REG      /* 16 bit value */
#define OCCS_WRITE_DIVIDE_BY_REG    /* 16 bit value */
#define OCCS_WRITE_OSC_CONTROL_REG  /* 16 bit value */

#define OCCS_READ_CONTROL_REG       /* NULL, returns UWord16 */
#define OCCS_READ_DIVIDE_BY_REG     /* NULL, returns UWord16 */
#define OCCS_READ_STATUS_REG        /* NULL, returns UWord16 */
#define OCCS_READ_OSC_CONTROL_REG   /* NULL, returns UWord16 */

/*******************************************************************************
    Full OCCS (8xxx family) clock configuration commands
*******************************************************************************/

#if OCCS_VERSION == 1

#define OCCS_SET_CORE_CLOCK         /* OCCS_CLOCK_IN_DIVIDE_BY_x | OCCS_CLOCK_OUT_DIVIDE_BY_y | DivBy,
                                       where x and y are 1,2,4 or 8. Range of DivBy is 1 to 128
                                       After command is executed the VCO frequency and MC core frequency is
                                       Fvco = Fosc*(DivBy+1)/x  (recommended Fvco range is 80MHz to 240MHz)
                                       Fzclk = Fvco/(4*y) */
                                    
#define OCCS_SET_POSTSCALER         /* OCCS_CLOCK_OUT_DIVIDE_BY_x, where x is 1,2,4 or 8 */
#define OCCS_SET_DIVIDE_BY          /* value  1 to 128, use this command only when ZCLOCK Source is set to prescaler */
#define OCCS_SET_PRESCALER          /* OCCS_CLOCK_IN_DIVIDE_BY_x, where x is 1,2,4 or 8 
                                       use this command only when ZCLOCK Source is set to prescaler */
#define OCCS_POWER_MODE             /* OCCS_HIGH_POWER / OCCS_LOW_POWER,  set resonator/crystal power mode */
#define OCCS_DIRECT_CLOCK_MODE      /* OCCS_ENABLE/OCCS_DISABLE, set clkin mode on XTAL (turn off osc)  */

#endif

#if OCCS_VERSION <= 2
#define OCCS_TURN_OFF_CHARGE_PUMP   /* NULL, use this command only in the event of loss of clock */
#define OCCS_SHUTDOWN               /* NULL, shutdown chip on loss-of-clock (charge pump must be off) */
#endif

/*******************************************************************************
    Fixed-PLL OCCS (80xx family) clock configuration commands
*******************************************************************************/

#if OCCS_VERSION >= 2

#define OCCS_SET_CORE_CLOCK         /* OCCS_CLOCK_OUT_DIVIDE_BY_x, where x are 1,2,4,8,16 or 32 (64,128,256 only 800x)
                                       After command is executed the VCO frequency and MC core frequency is
                                       Fvco = Fosc*24/3  (recommended Fvco range is 80MHz to 240MHz) 
                                       Fzclk = Fvco/(2*x)
                                       Note: as there is no prescaler nor PLL div-by, this command is 
                                             same as the OCCS_SET_POSTSCALER */
                                    
#define OCCS_SET_POSTSCALER         /* OCCS_CLOCK_OUT_DIVIDE_BY_x, where x is 1,2,4,8,16 or 32 (64,128,256 only 800x)*/

#endif

/*******************************************************************************
    Internal Relaxation Oscillator commands
*******************************************************************************/

#if OCCS_HAS_RXOSC

#define OCCS_SET_PRESCALER_CLOCK    /* OCCS_INTERNAL_RELAX_OSC / OCCS_CRYSTAL_OSC, 
                                       OCCS_CRYSTAL_OSC should only be set if XTAL and EXTAL pin functions are enabled
                                       in the appropriate GPIO control register. */
#define OCCS_INTERNAL_RELAX_OSC_OPERATION  /* OCCS_ENABLE / OCCS_DISABLE / OCCS_STANDBY(80xx only),
                                              Power-down the relaxation oscillator if the crystal oscillator is being used.
                                              To prevent loss of clock to the core or the PLL, set this bit only if
                                              the prescaler clock source has been changed to the crystal oscillator
                                              by setting the PRECS bit in PLLCR. */ 
#define OCCS_ADJUST_RELAX_OSC_FREQ  /* UWord16 value in range of 0 to 1023 (0x000 - 0x3FF) */
#define OCCS_TRIM_RELAX_OSC_8MHZ    /* NULL, trim the internal relaxation oscillator to 8MHz as measured at the factory */

#endif /* OCCS_HAS_RXOSC */

/*******************************************************************************
    New Features of OCCS_VERSION_3
*******************************************************************************/

#if OCCS_VERSION == 3
#define OCCS_SELECT_EXT_CLOCK_SOURCE /* OCCS_CLKIN_PRI/OCCS_CLKIN_ALT/OCCS_CLKIN_OSC */
#endif

#if OCCS_VERSION >= 3
#define OCCS_POWER_MODE              /* OCCS_HIGH_POWER / OCCS_LOW_POWER,  set resonator/crystal power mode */
#define OCCS_DIRECT_CLOCK_MODE       /* OCCS_ENABLE/OCCS_DISABLE, set clkin mode on XTAL (turn off osc)  */

#define OCCS_WPROTECT_PLL_SETTINGS   /* OCCS_ENABLE(_PERMANENT)/OCCS_DISABLE(_PERMANENT); write protect PLL settings */
#define OCCS_WPROTECT_OSC_SETTINGS   /* OCCS_ENABLE(_PERMANENT)/OCCS_DISABLE(_PERMANENT); write protect Oscillator settings */
#define OCCS_WPROTECT_CLK_SETTINGS   /* OCCS_ENABLE(_PERMANENT)/OCCS_DISABLE(_PERMANENT); write protect Clock settings */

#define OCCS_SET_CLOCK_CHECK         /* OCCS_ENABLE/OCCS_DISABLE */
#define OCCS_TEST_CLOCK_CHECK        /* NULL, test if clock checking function has finished */
#define OCCS_READ_CLOCK_CHECK_REFERENCE		/* NULL, returns UWord16 */
#define OCCS_READ_CLOCK_CHECK_TARGET       	/* NULL, returns UWord16 */
#endif

/*******************************************************************************
    New Features of OCCS_VERSION_4
*******************************************************************************/

#if OCCS_VERSION >= 4
#define OCCS_SELECT_EXT_CLOCK_SOURCE /* OCCS_CLKIN_CLKIN / OCCS_CLKIN_EXTAL */
#define OCCS_SELECT_FREQ_RANGE       /* OCCS_32KHZ_CRYSTAL / OCCS_1MHZ_TO_16MHZ_CRYSTAL */
#endif



/*******************************************************************************
    Compatibility registers names with previous versions
*******************************************************************************/

//New name for PLL Control Register
#if (!defined(OCCS_PLLCR_INIT) && defined(OCCS_CTRL_INIT))
#define OCCS_PLLCR_INIT OCCS_CTRL_INIT
#endif

//New name for Divide by register
#if (!defined(OCCS_PLLDB_INIT) && defined(OCCS_DIVBY_INIT))
#define OCCS_PLLDB_INIT OCCS_DIVBY_INIT
#endif

//New name for OCCS Status Register
#if (!defined(OCCS_PLLSR_INIT) && defined(OCCS_STAT_INIT))
#define OCCS_PLLSR_INIT OCCS_STAT_INIT
#endif


/*******************************************************************************
    command parameters
*******************************************************************************/

#define OCCS_DISABLE                    0
#define OCCS_ENABLE                     1

/* for permanent enable/disable */
#define OCCS_DISABLE_PERMANENT          2
#define OCCS_ENABLE_PERMANENT           3

#if OCCS_VERSION >= 2
#define OCCS_STANDBY                    -1
#endif

#if OCCS_HAS_RXOSC
#define OCCS_INTERNAL_RELAX_OSC         0
#define OCCS_CRYSTAL_OSC                1
#endif

#define OCCS_LOW_POWER                  1
#define OCCS_HIGH_POWER                 0

#define OCCS_POSTSCALER_OUTPUT          OCCS_PLLCR_ZSRC_POSTSCALER
#define OCCS_PRESCALER_OUTPUT           OCCS_PLLCR_ZSRC_PRESCALER

#if OCCS_VERSION >= 2
    /* alternate name for prescaler clock */
    #define OCCS_MSTR_OSC_OUTPUT        OCCS_PLLCR_ZSRC_PRESCALER
#endif

#if OCCS_VERSION >= 3
    /* alternate name for prescaler clock */
    #define OCCS_PLL_OSC_OUTPUT        OCCS_PLLCR_ZSRC_POSTSCALER
#endif

#define OCCS_LOL1_INT                   OCCS_PLLCR_PLLIE1_MASK
#define OCCS_LOL0_INT                   OCCS_PLLCR_PLLIE0_MASK
#define OCCS_LOL1_INT_ANY_EDGE          OCCS_PLLCR_PLLIE1_ANYEDGE
#define OCCS_LOL1_INT_FALLING_EDGE      OCCS_PLLCR_PLLIE1_FALLINGEDGE
#define OCCS_LOL1_INT_RISING_EDGE       OCCS_PLLCR_PLLIE1_RISINGEDGE
#define OCCS_LOL0_INT_ANY_EDGE          OCCS_PLLCR_PLLIE0_ANYEDGE
#define OCCS_LOL0_INT_FALLING_EDGE      OCCS_PLLCR_PLLIE0_FALLINGEDGE
#define OCCS_LOL0_INT_RISING_EDGE       OCCS_PLLCR_PLLIE0_RISINGEDGE

#define OCCS_INT1                       OCCS_PLLCR_PLLIE1_MASK
#define OCCS_INT0                       OCCS_PLLCR_PLLIE0_MASK
#define OCCS_INT1_ANY_EDGE              OCCS_PLLCR_PLLIE1_ANYEDGE
#define OCCS_INT1_FALLING_EDGE          OCCS_PLLCR_PLLIE1_FALLINGEDGE
#define OCCS_INT1_RISING_EDGE           OCCS_PLLCR_PLLIE1_RISINGEDGE
#define OCCS_INT0_ANY_EDGE              OCCS_PLLCR_PLLIE0_ANYEDGE
#define OCCS_INT0_FALLING_EDGE          OCCS_PLLCR_PLLIE0_FALLINGEDGE
#define OCCS_INT0_RISING_EDGE           OCCS_PLLCR_PLLIE0_RISINGEDGE
#define OCCS_LOSS_OF_CLOCK_INT          OCCS_PLLCR_LOCIE

#define OCCS_CLOCK_OUT_DIVIDE_BY_1      OCCS_PLLDB_PLLCOD_1
#define OCCS_CLOCK_OUT_DIVIDE_BY_2      OCCS_PLLDB_PLLCOD_2
#define OCCS_CLOCK_OUT_DIVIDE_BY_4      OCCS_PLLDB_PLLCOD_4
#define OCCS_CLOCK_OUT_DIVIDE_BY_8      OCCS_PLLDB_PLLCOD_8

#if OCCS_VERSION == 1
    #define OCCS_CLOCK_IN_DIVIDE_BY_1   OCCS_PLLDB_PLLCID_1
    #define OCCS_CLOCK_IN_DIVIDE_BY_2   OCCS_PLLDB_PLLCID_2
    #define OCCS_CLOCK_IN_DIVIDE_BY_4   OCCS_PLLDB_PLLCID_4
    #define OCCS_CLOCK_IN_DIVIDE_BY_8   OCCS_PLLDB_PLLCID_8
    
#else /* OCCS_VERSION >= 2 */
    #define OCCS_CLOCK_OUT_DIVIDE_BY_16 OCCS_PLLDB_PLLCOD_16
    #define OCCS_CLOCK_OUT_DIVIDE_BY_32 OCCS_PLLDB_PLLCOD_32
    
#endif

#if OCCS_VERSION >= 4
    #define OCCS_CLOCK_OUT_DIVIDE_BY_64  OCCS_PLLDB_PLLCOD_64
    #define OCCS_CLOCK_OUT_DIVIDE_BY_128 OCCS_PLLDB_PLLCOD_128
    #define OCCS_CLOCK_OUT_DIVIDE_BY_256 OCCS_PLLDB_PLLCOD_256
#endif
    
#define OCCS_STATUS_LOCK_LOST_INT1      OCCS_PLLSR_LOLI1
#define OCCS_STATUS_LOCK_LOST_INT0      OCCS_PLLSR_LOLI0
#define OCCS_STATUS_CLOCK_LOST          OCCS_PLLSR_LOCI
#define OCCS_STATUS_LOCK_1              OCCS_PLLSR_LCK1
#define OCCS_STATUS_LOCK_0              OCCS_PLLSR_LCK0
#define OCCS_STATUS_POWER_DOWN          OCCS_PLLSR_PLLPD
#define OCCS_STATUS_ZCLOCK_PRESCALER    OCCS_PLLSR_ZSRC_PRESCALER
#define OCCS_STATUS_ZCLOCK_POSTSCALER   OCCS_PLLSR_ZSRC_POSTSCALER
#define OCCS_STATUS_ZCLOCK             OCCS_PLLSR_ZSRC_MASK

#if OCCS_VERSION == 3
#define OCCS_CLKIN_PRI                  OCCS_OSCTL_EXT_SEL_PRI
#define OCCS_CLKIN_ALT					        OCCS_OSCTL_EXT_SEL_ALT
#define OCCS_CLKIN_OSC 					        OCCS_OSCTL_EXT_SEL_OSC
#endif

#if OCCS_VERSION >= 4
#define OCCS_32KHZ_CRYSTAL              1
#define OCCS_1MHZ_TO_16MHZ_CRYSTAL      0
#define OCCS_STATUS_CRYSTAL_READY       OCCS_PLLSR_COSC_RDY
#define OCCS_CLKIN_CLKIN                OCCS_OSCTL_EXT_SEL_CLKIN
#define OCCS_CLKIN_EXTAL                OCCS_OSCTL_EXT_SEL_EXTAL
#endif

/*******************************************************************************
    register bit names and masks
*******************************************************************************/

/* OCCS_PLLCR register bits */
#define OCCS_PLLCR_PLLIE1_MASK          0xC000
#define OCCS_PLLCR_PLLIE1_ANYEDGE       0xC000
#define OCCS_PLLCR_PLLIE1_FALLINGEDGE   0x8000
#define OCCS_PLLCR_PLLIE1_RISINGEDGE    0x4000
#define OCCS_PLLCR_PLLIE1_DISABLED      0x0000
#define OCCS_PLLCR_PLLIE0_MASK          0x3000
#define OCCS_PLLCR_PLLIE0_ANYEDGE       0x3000
#define OCCS_PLLCR_PLLIE0_FALLINGEDGE   0x2000
#define OCCS_PLLCR_PLLIE0_RISINGEDGE    0x1000
#define OCCS_PLLCR_PLLIE0_DISABLED      0x0000
#define OCCS_PLLCR_LOCIE                0x0800
#define OCCS_PLLCR_LCKON                0x0080
#define OCCS_PLLCR_PLLPD                0x0010
#define OCCS_PLLCR_ZSRC_MASK            0x0003
#define OCCS_PLLCR_ZSRC_POSTSCALER      0x0002
#define OCCS_PLLCR_ZSRC_PRESCALER       0x0001

#if OCCS_VERSION <= 2
#define OCCS_PLLCR_CHPMPTRI             0x0040
#endif

/* OCCS_PLLCR register bits on devices with Relaxation Oscillator */
#if OCCS_HAS_RXOSC
    #define OCCS_PLLCR_PRECS            0x0004
#endif

/* OCCS_PLLDB register bits */
#define OCCS_PLLDB_LORTP_MASK           0xf000

#if OCCS_VERSION == 1
    #define OCCS_PLLDB_PLLCOD_MASK      0x0c00
    #define OCCS_PLLDB_PLLCOD_8         0x0c00
    #define OCCS_PLLDB_PLLCOD_4         0x0800
    #define OCCS_PLLDB_PLLCOD_2         0x0400
    #define OCCS_PLLDB_PLLCOD_1         0x0000
    #define OCCS_PLLDB_PLLCID_MASK      0x0300
    #define OCCS_PLLDB_PLLCID_8         0x0300
    #define OCCS_PLLDB_PLLCID_4         0x0200
    #define OCCS_PLLDB_PLLCID_2         0x0100
    #define OCCS_PLLDB_PLLCID_1         0x0000
    #define OCCS_PLLDB_PLLDB_MASK       0x007f

/* OCCS_PLLDB register bits on fixed PLL devices (e.g. 80xx)  */
#else   /*OCCS_VERSION >= 2*/
    #define OCCS_PLLDB_PLLCOD_32        0x0500
    #define OCCS_PLLDB_PLLCOD_16        0x0400
    #define OCCS_PLLDB_PLLCOD_8         0x0300
    #define OCCS_PLLDB_PLLCOD_4         0x0200
    #define OCCS_PLLDB_PLLCOD_2         0x0100
    #define OCCS_PLLDB_PLLCOD_1         0x0000
#endif


#if OCCS_VERSION == 2 || OCCS_VERSION == 3
    #define OCCS_PLLDB_PLLCOD_MASK      0x0700
    #define OCCS_PLLDB_PLLCOD_32c       0x0700
    #define OCCS_PLLDB_PLLCOD_32b       0x0600
#endif


#if OCCS_VERSION >= 4
    #define OCCS_PLLDB_PLLCOD_MASK      0x0f00
    #define OCCS_PLLDB_PLLCOD_256h      0x0f00
    #define OCCS_PLLDB_PLLCOD_256g      0x0e00
    #define OCCS_PLLDB_PLLCOD_256f      0x0d00
    #define OCCS_PLLDB_PLLCOD_256e      0x0c00
    #define OCCS_PLLDB_PLLCOD_256d      0x0b00
    #define OCCS_PLLDB_PLLCOD_256c      0x0a00
    #define OCCS_PLLDB_PLLCOD_256b      0x0900
    #define OCCS_PLLDB_PLLCOD_256       0x0800
    #define OCCS_PLLDB_PLLCOD_128       0x0700
    #define OCCS_PLLDB_PLLCOD_64        0x0600
#endif

/* OCCS_PLLSR register bits */
#define OCCS_PLLSR_LOLI1                0x8000
#define OCCS_PLLSR_LOLI0                0x4000
#define OCCS_PLLSR_LOCI                 0x2000
#define OCCS_PLLSR_LCK1                 0x0040
#define OCCS_PLLSR_LCK0                 0x0020
#define OCCS_PLLSR_PLLPD                0x0010
#define OCCS_PLLSR_ZSRC_MASK            0x0003
#define OCCS_PLLSR_ZSRC_SYNCA           0x0003
#define OCCS_PLLSR_ZSRC_POSTSCALER      0x0002
#define OCCS_PLLSR_ZSRC_PRESCALER       0x0001
#define OCCS_PLLSR_ZSRC_SYNCB           0x0000

#if OCCS_VERSION >= 4
#define OCCS_PLLSR_COSC_RDY             0x0004
#endif

/* Oscillator Control Register */
#define OCCS_OSCTL_COHL                 0x2000

/* Oscillator Control Register on devices with Relaxation Oscillator */
#if OCCS_HAS_RXOSC
    #define OCCS_OSCTL_ROPD             0x8000
    #define OCCS_OSCTL_CLKMODE          0x1000
    #define OCCS_OSCTL_TRIM_MASK        0x03FF

    #if OCCS_VERSION >= 2
        #define OCCS_OSCTL_ROSB         0x4000
    #endif
#endif

#if OCCS_VERSION == 3
    #define OCCS_OSCTL_EXT_SEL_MASK     0x0c00
    #define OCCS_OSCTL_EXT_SEL_PRI      0x0000
    #define OCCS_OSCTL_EXT_SEL_ALT      0x0400
    #define OCCS_OSCTL_EXT_SEL_OSC      0x0800
#endif

#if OCCS_VERSION >= 4
    #define OCCS_OSCTL_EXT_SEL_CLKIN    0x0400
    #define OCCS_OSCTL_EXT_SEL_EXTAL    0x0000
    #define OCCS_OSCTL_RANGE            0x0800
#endif

/* External Clock Check Register */

#if OCCS_VERSION == 3
    #define OCCS_CLKCHK_REF_CNT         0x7f00
    #define OCCS_CLKCHK_CHK_EN          0x8000
    #define OCCS_CLKCHK_TARGET_CNT      0x00ff
#endif

#if OCCS_VERSION >= 4
    #define OCCS_CLKCHR_REF_CNT         0x7fff
    #define OCCS_CLKCHR_CHK_EN          0x8000
    #define OCCS_CLKCHT_TARGET_CNT      0x00ff

#endif


/* Protection Register */
#if OCCS_VERSION >= 3
    #define OCCS_PROT_FRQEP_MASK        0x0030
    #define OCCS_PROT_FRQEP_PROT        0x0010
    #define OCCS_PROT_FRQEP_LOCK        0x0020
    #define OCCS_PROT_OSCEP_MASK        0x000c
    #define OCCS_PROT_OSCEP_PROT        0x0004
    #define OCCS_PROT_OSCEP_LOCK        0x0008
    #define OCCS_PROT_PLLEP_MASK        0x0003
    #define OCCS_PROT_PLLEP_PROT        0x0001
    #define OCCS_PROT_PLLEP_LOCK        0x0002
#endif

/*******************************************************************************
    Calculate core clock frequency (if EXTCLK is available or if using RX_OSC)
*******************************************************************************/

/* first decide master clock (MSTR_OSC) */
#ifndef OCCS_MSTROSC_FREQ
    #if OCCS_HAS_RXOSC
        #if !defined(OCCS_PLLCR_INIT) || !((OCCS_PLLCR_INIT) & (OCCS_PLLCR_PRECS))
            #if OCCS_USE_FACTORY_TRIM && defined(OCCS_RXOSC_RETRIM_CLK)
            #define OCCS_MSTROSC_FREQ (OCCS_RXOSC_RETRIM_CLK)  /* Re-trimmed RX OSC used */
            #else
            #define OCCS_MSTROSC_FREQ 8000000L  /* Nominal RX OSC used */
            #endif
        #elif (defined(EXTCLK) && (OCCS_VERSION <= 3))
            #define OCCS_MSTROSC_FREQ (EXTCLK)  /* External clock used */
        #elif (OCCS_VERSION >= 4)
        	#if (defined(OCCS_OSCTL_INIT) && !((OCCS_OSCTL_INIT) & (OCCS_OSCTL_EXT_SEL_CLKIN)))
				#if defined(EXTAL) 
					#define OCCS_MSTROSC_FREQ (EXTAL)  /* Crystal clock used */
				#endif 
			#elif defined(EXTCLK)
				#define OCCS_MSTROSC_FREQ (EXTCLK)  /* External clock used */
			#endif
        #endif
    #else
        #if (defined(EXTCLK) && (OCCS_VERSION <= 3))
            #define OCCS_MSTROSC_FREQ (EXTCLK)  /* External clock used */
        #elif (OCCS_VERSION >= 4)
        	#if (defined(OCCS_OSCTL_INIT) && !(OCCS_OSCTL_INIT&OCCS_OSCTL_EXT_SEL_CLKIN))
				#if defined(EXTAL) 
					#define OCCS_MSTROSC_FREQ (EXTAL)  /* Crystal clock used */
				#endif 
			#elif defined(EXTCLK)
				#define OCCS_MSTROSC_FREQ (EXTCLK)  /* External clock used */
			#endif
        #endif
    #endif
#endif /* OCCS_MSTROSC_FREQ */

#if !defined(OCCS_CORE_FREQ) && defined(OCCS_MSTROSC_FREQ)

    /* Standard OCCS clock calculation */
    #if OCCS_VERSION == 1

        /* when PLLDB register INIT value is not defined, we will use its reset value */
        #ifdef OCCS_PLLDB_INIT
        #define __OCCS_PLLDB_INIT OCCS_PLLDB_INIT
        #else
        #define __OCCS_PLLDB_INIT 0x201d    /* PLLDB reset value on OCCS_VERSION_1  */
        #endif

        /* PLL active */
        #if defined(OCCS_PLLCR_INIT) && ((OCCS_PLLCR_INIT & 3) == 2)
            #define OCCS_CORE_FREQ (((OCCS_MSTROSC_FREQ)*(((__OCCS_PLLDB_INIT) & 0x7f)+1)) \
                / (1<<(((__OCCS_PLLDB_INIT)>>8)&0x3))  /* prescaler  */ \
                / (1<<(((__OCCS_PLLDB_INIT)>>10)&0x3)) /* postscaler */ \
                / 4)
                
        /* PLL not active */
        #else
        
            #define OCCS_CORE_FREQ ((OCCS_MSTROSC_FREQ) \
                / (1<<(((__OCCS_PLLDB_INIT)>>8)&0x3)) /* prescaler */   \
                / 2)
                
        #endif

	#endif
    /* Fixed PLL settings (e.g. 80xx devices) */
    #if  (OCCS_VERSION >= 2) && (OCCS_VERSION <= 3)

        /* when PLLDB register INIT value is not defined, we will use its reset value */
        #ifdef OCCS_PLLDB_INIT
        #define __OCCS_PLLDB_INIT OCCS_PLLDB_INIT
        #else
        #define __OCCS_PLLDB_INIT 0x0000    /* PLLDB reset value on OCCS_VERSION_2+ */
        #endif

        /* PLL active */
        #if defined(OCCS_PLLCR_INIT) && ((OCCS_PLLCR_INIT & 3) == 2)
        
            /* postscaler */
            #if (1<<(((__OCCS_PLLDB_INIT)>>8)&0x7)) <= 32
            #define __OCCS_POSTSCALER (1<<(((__OCCS_PLLDB_INIT)>>8)&0x7))
            #else
            #define __OCCS_POSTSCALER 32
            #endif
            
            #define OCCS_CORE_FREQ (((OCCS_MSTROSC_FREQ)*24) / __OCCS_POSTSCALER / 6)
                
        /* PLL not active */
        #else
        
            #define OCCS_CORE_FREQ ((OCCS_MSTROSC_FREQ) / 2)
                
        #endif
    
    #endif

    #if  OCCS_VERSION >= 4

        /* when PLLDB register INIT value is not defined, we will use its reset value */
        #ifdef OCCS_PLLDB_INIT
        #define __OCCS_PLLDB_INIT OCCS_PLLDB_INIT
        #else
        #define __OCCS_PLLDB_INIT 0x2000    /* PLLDB reset value on OCCS_VERSION_4 */
        #endif

        /* postscaler */
        #if (1<<(((__OCCS_PLLDB_INIT)>>8)&0xf)) <= 256
        #define __OCCS_POSTSCALER (1<<(((__OCCS_PLLDB_INIT)>>8)&0xf))
        #else
        #define __OCCS_POSTSCALER 256
        #endif

        /* PLL active */
        #if defined(OCCS_PLLCR_INIT) && ((OCCS_PLLCR_INIT & 3) == 2)
        
            #define OCCS_CORE_FREQ (((OCCS_MSTROSC_FREQ)*24) / __OCCS_POSTSCALER / 6)
                
        /* PLL not active */
        #else
        
            #define OCCS_CORE_FREQ ((OCCS_MSTROSC_FREQ / __OCCS_POSTSCALER) / 2)
                
        #endif
    
    #endif


#endif /* !OCCS_CORE_FREQ && OCCS_MSTROSC_FREQ */

/*******************************************************************************
    Function Prototypes
*******************************************************************************/

/* module initialization */
void occsInit(void);

/* Function parameters: OscFreq - oscillator frequency [Hz]
   Function returns IP Bus frequency [Hz]. */
UWord32 occsGetIPBusFreq(UWord32 oscFreq); 

/* Function parameters: OscFreq - oscillator frequency [Hz]
   Function returns Core Bus frequency [Hz]. */
#define occsGetCoreFreq occsGetIPBusFreq

/*******************************************************************************
    Implementations of OCCS ioctl() commands
*******************************************************************************/
#define ioctlOCCS_INIT(pOccsBase, param)        occsInit()

#if OCCS_VERSION == 1
#define ioctlOCCS_SET_CORE_CLOCK(pOccsBase, param) \
    { \
        periphMemWrite(OCCS_PLLCR_LCKON | OCCS_PLLCR_ZSRC_PRESCALER, &((pOccsBase)->pllcr)); \
        periphBitGrpSet(OCCS_PLLDB_PLLCOD_MASK | OCCS_PLLDB_PLLCID_MASK | OCCS_PLLDB_PLLDB_MASK, \
            ((param) & (OCCS_PLLDB_PLLCOD_MASK | OCCS_PLLDB_PLLCID_MASK)) | \
            (((param)-1) & OCCS_PLLDB_PLLDB_MASK), &((pOccsBase)->plldb)); \
        while (!periphBitTest(OCCS_PLLSR_LCK1, &((pOccsBase)->pllsr))) \
            ; \
        periphMemWrite(OCCS_PLLCR_LCKON | OCCS_PLLCR_ZSRC_POSTSCALER, &((pOccsBase)->pllcr)); \
    }

#else /* OCCS_VERSION >= 2 */
#define ioctlOCCS_SET_CORE_CLOCK(pOccsBase, param) \
    { \
        periphMemWrite(OCCS_PLLCR_LCKON | OCCS_PLLCR_ZSRC_PRESCALER, &((pOccsBase)->pllcr)); \
        periphBitGrpSet(OCCS_PLLDB_PLLCOD_MASK, param, &((pOccsBase)->plldb)); \
        while (!periphBitTest(OCCS_PLLSR_LCK1, &((pOccsBase)->pllsr))) \
            ; \
        periphMemWrite(OCCS_PLLCR_LCKON | OCCS_PLLCR_ZSRC_POSTSCALER, &((pOccsBase)->pllcr)); \
    }
#endif

#define ioctlOCCS_SET_POSTSCALER(pOccsBase, param) \
    periphBitGrpSR(OCCS_PLLDB_PLLCOD_MASK, param, &((pOccsBase)->plldb))

#ifdef OCCS_SET_PRESCALER
#define ioctlOCCS_SET_PRESCALER(pOccsBase, param) \
    periphBitGrpSR(OCCS_PLLDB_PLLCID_MASK, param, &((pOccsBase)->plldb))
#endif

#ifdef OCCS_SET_DIVIDE_BY
#define ioctlOCCS_SET_DIVIDE_BY(pOccsBase, param) \
    periphBitGrpSR(OCCS_PLLDB_PLLDB_MASK, (param) - 1, &((pOccsBase)->plldb))
#endif

#define ioctlOCCS_SET_LORTP(pOccsBase, param) \
    periphBitGrpSR(OCCS_PLLDB_LORTP_MASK, (param) << 12, &((pOccsBase)->plldb))

#ifdef OCCS_TURN_OFF_CHARGE_PUMP
#define ioctlOCCS_TURN_OFF_CHARGE_PUMP(pOccsBase, param) \
    periphBitSet(OCCS_PLLCR_CHPMPTRI, &((pOccsBase)->pllcr))
#endif

#define ioctlOCCS_INT_ENABLE(pOccsBase, param) \
    periphBitSet(param, &((pOccsBase)->pllcr))

#define ioctlOCCS_ENABLE_INT(pOccsBase, param) \
    periphBitSet(param, &((pOccsBase)->pllcr))

#define ioctlOCCS_SET_ZCLOCK_SOURCE(pOccsBase, param) \
    periphBitGrpSet(OCCS_PLLCR_ZSRC_MASK, param, &((pOccsBase)->pllcr))

#define ioctlOCCS_GET_ZCLOCK_SOURCE(pOccsBase, param) \
    periphBitTest(OCCS_PLLSR_ZSRC_SYNCA, &((pOccsBase)->pllsr))

#define ioctlOCCS_INT_DISABLE(pOccsBase, param) \
    periphBitClear(param, &((pOccsBase)->pllcr))

#define ioctlOCCS_DISABLE_INT(pOccsBase, param) \
    periphBitClear(param, &((pOccsBase)->pllcr))

#define ioctlOCCS_READ_FLAG(pOccsBase, param) \
    periphBitTest(param, &((pOccsBase)->pllsr))

#define ioctlOCCS_CLEAR_FLAG(pOccsBase, param) \
    periphSafeAckByOne(OCCS_PLLSR_LOLI1 | OCCS_PLLSR_LOLI0 | OCCS_PLLSR_LOCI, param, &((pOccsBase)->pllsr))

#define ioctlOCCS_LOCK_DETECTOR(pOccsBase, param) \
    if (param) periphBitSet(OCCS_PLLCR_LCKON, &((pOccsBase)->pllcr)); \
    else periphBitClear(OCCS_PLLCR_LCKON, &((pOccsBase)->pllcr))

#ifdef OCCS_POWER_MODE
#define ioctlOCCS_POWER_MODE(pOccsBase, param) \
    if (param) periphBitSet(OCCS_OSCTL_COHL, &((pOccsBase)->osctl)); \
    else periphBitClear(OCCS_OSCTL_COHL, &((pOccsBase)->osctl))
#endif

#ifdef OCCS_DIRECT_CLOCK_MODE
#define ioctlOCCS_DIRECT_CLOCK_MODE(pOccsBase, param) \
    if (param) periphBitSet(OCCS_OSCTL_CLKMODE, &((pOccsBase)->osctl)); \
    else periphBitClear(OCCS_OSCTL_CLKMODE, &((pOccsBase)->osctl))
#endif

#define ioctlOCCS_GET_IPBUS_FREQ(pOccsBase, param) occsGetIPBusFreq(param)

#ifdef OCCS_SELECT_FREQ_RANGE
#define ioctlOCCS_SELECT_FREQ_RANGE(pOccsBase, param) \
    if (param) periphBitSet(OCCS_OSCTL_RANGE, &((pOccsBase)->osctl)); \
    else periphBitClear(OCCS_OSCTL_RANGE, &((pOccsBase)->osctl))
#endif

/* Reading(writing) from(to) registers */
#define ioctlOCCS_WRITE_CONTROL_REG(pOccsBase, param) \
    periphMemWrite(param, &((pOccsBase)->pllcr))

#define ioctlOCCS_WRITE_DIVIDE_BY_REG(pOccsBase, param) \
    periphMemWrite(param, &((pOccsBase)->plldb))

#define ioctlOCCS_WRITE_OSC_CONTROL_REG(pOccsBase, param) \
    periphMemWrite(param, &((pOccsBase)->osctl))

#ifdef OCCS_SHUTDOWN
#define ioctlOCCS_SHUTDOWN(pOccsBase, param) { \
    periphMemWrite(0xDEAD, &((pOccsBase)->shutdown)); \
    while (1) ; }
#endif

#define ioctlOCCS_READ_CONTROL_REG(pOccsBase, param) \
    periphMemRead(&((pOccsBase)->pllcr))

#define ioctlOCCS_READ_DIVIDE_BY_REG(pOccsBase, param) \
    periphMemRead(&((pOccsBase)->plldb))

#define ioctlOCCS_READ_STATUS_REG(pOccsBase, param) \
    periphMemRead(&((pOccsBase)->pllsr))

#define ioctlOCCS_READ_OSC_CONTROL_REG(pOccsBase, param) \
    periphMemRead(&((pOccsBase)->osctl))

#if OCCS_VERSION >= 3
#define ioctlOCCS_WPROTECT_PLL_SETTINGS(pOccsBase, param) \
    periphBitGrpSet(OCCS_PROT_PLLEP_MASK, param, &((pOccsBase)->prot))
    
#define ioctlOCCS_WPROTECT_OSC_SETTINGS(pOccsBase, param) \
    periphBitGrpSet(OCCS_PROT_OSCEP_MASK, ((param) << 2), &((pOccsBase)->prot))
    
#define ioctlOCCS_WPROTECT_CLK_SETTINGS(pOccsBase, param) \
    periphBitGrpSet(OCCS_PROT_FRQEP_MASK, ((param) << 4), &((pOccsBase)->prot))
#endif /* OCCS_VERSION >= 3 */

#if OCCS_VERSION == 3
#define ioctlOCCS_SET_CLOCK_CHECK(pOccsBase, param) \
    if (param) periphBitSet(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchk)); \
    else periphBitClear(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchk))

#define ioctlOCCS_READ_CLOCK_CHECK_REFERENCE(pOccsBase, param) \
    (periphMemRead(&((pOccsBase)->clkchk)) & OCCS_CLKCHK_REF_CNT)>>8

#define ioctlOCCS_READ_CLOCK_CHECK_TARGET(pOccsBase, param) \
    (periphMemRead(&((pOccsBase)->clkchk))) & OCCS_CLKCHK_TARGET_CNT)

#define ioctlOCCS_SELECT_EXT_CLOCK_SOURCE(pOccsBase, param) \
    periphBitGrpSet(OCCS_OSCTL_EXT_SEL_MASK,param, &((pOccsBase)->osctl))

#define ioctlOCCS_TEST_CLOCK_CHECK(pOccsBase, param) \
    periphBitTest(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchk))

#elif OCCS_VERSION >= 4 //different name of register clkchk->clkchkr

#define ioctlOCCS_SELECT_EXT_CLOCK_SOURCE(pOccsBase, param) \
    if (param) periphBitSet(OCCS_OSCTL_EXT_SEL_CLKIN, &((pOccsBase)->osctl)); \
    else periphBitClear(OCCS_OSCTL_EXT_SEL_CLKIN, &((pOccsBase)->osctl))

#define ioctlOCCS_SET_CLOCK_CHECK(pOccsBase, param) \
    if (param) periphBitSet(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchkr)); \
    else periphBitClear(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchkr))

#define ioctlOCCS_READ_CLOCK_CHECK_REFERENCE(pOccsBase, param) \
    (periphMemRead(&((pOccsBase)->clkchkr)) & OCCS_CLKCHR_REF_CNT)

#define ioctlOCCS_READ_CLOCK_CHECK_TARGET(pOccsBase, param) \
    (periphMemRead(&((pOccsBase)->clkchkt)) & OCCS_CLKCHT_TARGET_CNT)

#define ioctlOCCS_TEST_CLOCK_CHECK(pOccsBase, param) \
    periphBitTest(OCCS_CLKCHR_CHK_EN, &((pOccsBase)->clkchkr))

#endif /* OCCS_VERSION >= 4 */



/*******************************************************************************
    Internal Relaxation Oscillator commands
*******************************************************************************/

#if OCCS_HAS_RXOSC

#define ioctlOCCS_SET_PRESCALER_CLOCK(pOccsBase, param) \
  if (param) periphBitSet(OCCS_PLLCR_PRECS, &((pOccsBase)->pllcr)); \
  else periphBitClear(OCCS_PLLCR_PRECS, &((pOccsBase)->pllcr))

#define ioctlOCCS_ADJUST_RELAX_OSC_FREQ(pOccsBase, param) \
  periphBitGrpSet(OCCS_OSCTL_TRIM_MASK, param, &((pOccsBase)->osctl))

#define ioctlOCCS_TRIM_RELAX_OSC_8MHZ(pOccsBase, param) \
  periphBitGrpSet(OCCS_OSCTL_TRIM_MASK, ArchIO.Hfm.fmopt1, &((pOccsBase)->osctl))

#if OCCS_VERSION == 1
/* ENABLE/DISABLE only */
#define ioctlOCCS_INTERNAL_RELAX_OSC_OPERATION(pOccsBase, param) \
  if (param) periphBitClear(OCCS_OSCTL_ROPD, &((pOccsBase)->osctl)); \
  else periphBitSet(OCCS_OSCTL_ROPD, &((pOccsBase)->osctl))

#else /* OCCS_VERSION >= 2 */
/* ENABLE(>0)/STANDBY(<0)/DISABLE(0) modes */
#define ioctlOCCS_INTERNAL_RELAX_OSC_OPERATION(pOccsBase, param) \
  if ((param) > 0) periphBitClear(OCCS_OSCTL_ROPD | OCCS_OSCTL_ROSB, &((pOccsBase)->osctl)); \
  else if ((param) < 0) periphBitGrpRS(OCCS_OSCTL_ROPD | OCCS_OSCTL_ROSB, OCCS_OSCTL_ROSB, &((pOccsBase)->osctl)); \
  else periphBitGrpRS(OCCS_OSCTL_ROPD | OCCS_OSCTL_ROSB, OCCS_OSCTL_ROPD, &((pOccsBase)->osctl))

#endif

#endif /* OCCS_HAS_RXOSC */

#ifdef __cplusplus
}
#endif

#endif

