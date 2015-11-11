/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  pwm.h
*
* $Date:      Mar-24-2009$
*
* $Version:   2.3.44.0$
*
* Description: Header file for the PWM driver
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  PWM_VERSION_1 .. 56F83xx devices, see MC56F8300UM.pdf
*  PWM_VERSION_2 .. 56F801x devices, see MC56F8000RM.pdf
*  PWM_VERSION_3 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  PWM_VERSION_4 .. 56F800x devices, see MC56F8006RM.pdf
*
*******************************************************************************/

#ifndef __PWM_H
#define __PWM_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before pwm.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Pulse Width Modulator (PWM) modules incorporate three complementary, individually
* programmable PWM signal outputs.
* Each module is also capable of supporting six independent PWM functions 
* to enhance motor control functionality. 
* Complementary operation permits programmable dead-time insertion,
* distortion correction via current sensing by software, and separate top and bottom output
* polarity control. The up-counter value is programmable to support a continuously variable
* PWM frequency. Both edge- and center-aligned synchronous pulse width control (full 0%
* to 100% modulation) are supported. 
*
* The device is capable of controlling most motor types: 
*      ACIM (AC Induction Motors)
*      BDC and BLDC (Brush and Brushless DC motors)
*      SRM and VRM (Switched and Variable Reluctance Motors)
*      Stepper motors
*
* The PWMs incorporate fault protection and cycle-by-cycle current limiting with sufficient
* output drive capability to directly drive standard opto-isolators.
*
* Write-once protection feature for key parameters is also included. A patented PWM
* waveform distortion correction circuit is also provided. Each PWM is double-buffered and
* includes interrupt controls to permit integral reload rates to be programmable from 1 to 16.
* The PWM modules also provide a reference output to synchronize the Analog-to-Digital
* Converters.
*
* For more information, please refer to the user manual for the particular chip that you
* are using, such as the MC56F8300 Peripheral Manual, for a description
* of the PWM device.
*
* The PWM device driver interface uses "ioctl" call to control specific PWM functions
* during operation. For details see "ioctl" call.
*
******************************************************************************/

/************************************************************
* PWM module identifiers, correspond to module base address
*************************************************************/

#ifdef PWMA_BASE
#define PWM_A  (&ArchIO.PwmA)
#endif

#ifdef PWMB_BASE
#define PWM_B  (&ArchIO.PwmB)
#endif

/* single ("anonymous") module on some devices */
#ifdef PWM_BASE
#define PWM    (&ArchIO.Pwm)
#define PWM_A  (&ArchIO.Pwm)  /* aliased to PWM_A */
#endif

/*************************************************************
* arch.h should define device-specific information about PWM
**************************************************************/

#if !defined(PWM_VERSION) || !defined(PWM_HAS_FAULTS) || !defined(PWM_HAS_IS_PINS)
#error PWM not properly described in arch.h (old Quick_Start version?)
#endif

/****************************************************
* Configurable items, i.e. defines, for appconfig.h
*****************************************************

  #define INTERRUPT_VECTOR_ADDR_yy  // specify interrupt handler routine
  #define INT_PRIORITY_LEVEL_yy     // interrupt level : (INTC_DISABLED, INTC_LEVEL0, ... INTC_LEVEL2)

  #define  PWM_x_PMCTL_INIT     0x0000 
  #define  PWM_x_PMFCTL_INIT    0x0000
  #define  PWM_x_PMOUT_INIT     0x0000
  #define  PWM_x_PWMCM_INIT     0x0000
  #define  PWM_x_PMDEADTM_INIT  0x0000
  #define  PWM_x_PMDISMAP1_INIT 0x0000
  #define  PWM_x_PMDISMAP2_INIT 0x0000
  #define  PWM_x_PMCFG_INIT     0x0000
  #define  PWM_x_PMCCR_INIT     0x0000

  where:
         x  is PWM module (A or B)
         yy  is interrupt vector number
            e.g. On 56F8346
                80 - PWM A Fault
                79 - PWM B Fault
                78 - PWM A Reload
                77 - PWM B Reload
*/

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl( PWM_module_identifier, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                             PARAMETERS, COMMENTS
------------------------------------------------------------------ */
#define PWM_INIT                          /* NULL */

#define PWM_SET_RELOAD_FREQUENCY          /* PWM_RELOAD_OPPORTUNITY_X */ 
#define PWM_HALF_CYCLE_RELOAD             /* PWM_ENABLE / PWM_DISABLE  */
#define PWM_SET_CURRENT_POLARITY          /* (PWM_IPOL_0 | PWM_IPOL_1 | PWM_IPOL_2) / PWM_ZERO_MASK  */
#define PWM_SET_PRESCALER                 /* PWM_PRESCALER_DIV_X  */
#define PWM_RELOAD_INT                    /* PWM_ENABLE / PWM_DISABLE  */
#define PWM_DEVICE                        /* PWM_ENABLE / PWM_DISABLE  */
#define PWM_CLEAR_RELOAD_FLAG             /* NULL  */
#define PWM_LOAD_OK                       /* NULL  */

#if PWM_HAS_IS_PINS
#define PWM_SET_CURRENT_SENSING           /* PWM_CORRECTION_XX  */
#endif

#define PWM_FAULT_INT_ENABLE              /* any combination of PWM_FAULT_x  */
#define PWM_FAULT_INT_DISABLE             /* any combination of PWM_FAULT_x  */
#define PWM_SET_AUTOMATIC_FAULT_CLEAR     /* any combination of PWM_FAULT_x  */
#define PWM_SET_MANUAL_FAULT_CLEAR        /* any combination of PWM_FAULT_x  */

#define PWM_CLEAR_FAULT_FLAG              /* any combination of PWM_FAULT_x  */
#define PWM_TEST_FAULT_FLAGS              /* any combination of PWM_FAULT_x  test selected FAULT flags */
#define PWM_TEST_FAULT_PINS               /* any combination of PWM_FAULT_x, test current state of selected FAULT pins */

#define PWM_OUTPUT_PAD                    /* PWM_ENABLE / PWM_DISABLE  */
#define PWM_OUTPUT_SOFTWARE_CONTROL       /* pwm_tPWMSignalMask  */
#define PWM_OUTPUT_CONTROL                /* pwm_tPWMSignalMask  */
 
#define PWM_SET_MODULO                    /* value */
#define PWM_GET_MODULO                    /* NULL  */
         
#define PWM_SET_DEADTIME                  /* value  */
        
#define PWM_WRITE_DISABLE_MAPPING_REG1    /* value  */
#define PWM_WRITE_DISABLE_MAPPING_REG2    /* value  */

#define PWM_SET_ALIGNMENT                 /* PWM_ALIGN_EDGE / PWM_ALIGN_CENTER  */
#define PWM_SET_NEG_TOP_SIDE_POLARITY     /* (PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01) / PWM_ZERO_MASK  */
#define PWM_SET_NEG_BOTTOM_SIDE_POLARITY  /* (PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01) / PWM_ZERO_MASK  */
#define PWM_SET_INDEPENDENT_OPERATION     /* (PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01) / PWM_ZERO_MASK */
#define PWM_SET_INDEPENDENT_MODE          /* PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01 */
#define PWM_SET_COMPLEMENTARY_MODE        /* PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01 */
#define PWM_SET_WRITE_PROTECT             /* NULL  */
          
#define PWM_HARDWARE_ACCELERATION         /* PWM_ENABLE / PWM_DISABLE  */
#define PWM_SET_CHANNEL_MASK              /* pwm_tPWMSignalMask  */
#define PWM_SET_LOAD_MODE                 /* PWM_LOAD_xx  */
#define PWM_SET_SWAP                      /* (PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01) / PWM_ZERO_MASK */

#define PWM_WRITE_VALUE_REG_0             /* value  */
#define PWM_WRITE_VALUE_REG_1             /* value  */
#define PWM_WRITE_VALUE_REG_2             /* value  */
#define PWM_WRITE_VALUE_REG_3             /* value  */
#define PWM_WRITE_VALUE_REG_4             /* value  */
#define PWM_WRITE_VALUE_REG_5             /* value  */
#define PWM_WRITE_VALUE_REGS_COMPL        /* pwm_sComplementaryValues*  */
#define PWM_WRITE_VALUE_REGS_INDEP        /* pwm_sIndependentValues*  */
#define PWM_READ_FAULT_STATUS_REG         /* NULL  */
#define PWM_READ_COUNTER_REG              /* NULL */
#define PWM_READ_CONTROL_REG              /* NULL  */

#define PWM_READ_PORT_REG                 /* NULL  */
#define PWM_GET_FAULT_INPUTS              /* NULL */
#define PWM_GET_FAULT_INPUT_0             /* NULL */
#define PWM_GET_FAULT_INPUT_1             /* NULL */
#define PWM_GET_FAULT_INPUT_2             /* NULL */
#define PWM_GET_FAULT_INPUT_3             /* NULL */
#if PWM_HAS_IS_PINS 
#define PWM_GET_CURRENT_STATUS_INPUTS     /* NULL */
#endif 

#define PWM_SOFTWARE_OUTPUTS_CONTROL      /* pwm_sOutputControl*  */
#define PWM_UPDATE_VALUE_REG_0            /* value  */
#define PWM_UPDATE_VALUE_REG_1            /* value  */
#define PWM_UPDATE_VALUE_REG_2            /* value  */
#define PWM_UPDATE_VALUE_REG_3            /* value  */
#define PWM_UPDATE_VALUE_REG_4            /* value  */
#define PWM_UPDATE_VALUE_REG_5            /* value  */
#define PWM_UPDATE_VALUE_REGS_COMPL       /* pwm_sComplementaryValues*  */
#define PWM_UPDATE_VALUE_REGS_INDEP       /* pwm_sIndependentValues*  */  
#define PWM_UPDATE_VALUE_SET_VLMODE       /* pwm_sUpdateValueSetVlmode*  */    
#define PWM_SET_MASK_SWAP                 /* pwm_sChannelControl*  */    

/* 56F8xxx specific commands */ 
#define PWM_DEBUG_OPERATION               /* PWM_STOP / PWM_RUN */
#define PWM_WAIT_OPERATION                /* PWM_STOP / PWM_RUN */
#define PWM_MASK_SWAP_OPERATION           /* PWM_80X_COMPATIBLE / PWM_ENHANCED */

#define PWM_SET_HALF_CYCLE_INTERNAL_CORRECTION    /* PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01 */
#define PWM_SET_FULL_CYCLE_INTERNAL_CORRECTION    /* PWM_CHANNEL_45 | PWM_CHANNEL_23 | PWM_CHANNEL_01 */
#define PWM_READ_INTERNAL_CORRECTION_CONTROL_REG  /* NULL  */

/*******************************************************************************
  commands applicable to newer version of PWM module (80xx)
*******************************************************************************/

#if PWM_VERSION >= 2

#define PWM_SET_DEADTIME_0          /* value  */
#define PWM_SET_DEADTIME_1          /* value  */
 
#define PWM_SET_SOURCE_0            /* PWM_SOURCE_xxx_0 */
#define PWM_SET_SOURCE_1            /* PWM_SOURCE_xxx_1 / PWM_SOURCE_SRC_0 */
#define PWM_SET_SOURCE_2            /* PWM_SOURCE_xxx_2 / PWM_SOURCE_SRC_0 */

#define PWM_SET_COMPARE_INVERT_0    /* PWM_NORMAL / PWM_INVERT */
#define PWM_SET_COMPARE_INVERT_1    /* PWM_NORMAL / PWM_INVERT */
#define PWM_SET_COMPARE_INVERT_2    /* PWM_NORMAL / PWM_INVERT */
#define PWM_SET_COMPARE_INVERT_3    /* PWM_NORMAL / PWM_INVERT */
#define PWM_SET_COMPARE_INVERT_4    /* PWM_NORMAL / PWM_INVERT */
#define PWM_SET_COMPARE_INVERT_5    /* PWM_NORMAL / PWM_INVERT */

#endif /* PWM_VERSION >= 2 */

/*******************************************************************************
  commands applicable to newer version of PWM module (802x/3x)
*******************************************************************************/

#if PWM_VERSION >= 3

#define PWM_SET_ACTIVE_HIGH_FAULTS  /* any combination of PWM_FAULT_x */
#define PWM_SET_ACTIVE_LOW_FAULTS   /* any combination of PWM_FAULT_x */

#define PWM_DISABLE_SYNC            /* NULL, disable SYNC input/output, revert pin to FAULT2 operation */
#define PWM_ENABLE_SYNC_OUT         /* NULL, enable SYNC signal output on FAULT2 pin */
#define PWM_ENABLE_SYNC_IN          /* UWord16 1..0x7fff, enable SYNC input in time window of given size */

#define PWM_READ_FILT0_REG          /* NULL, returns value of FAULT fiter register 0 */
#define PWM_READ_FILT1_REG          /* NULL, returns value of FAULT fiter register 1 */
#define PWM_READ_FILT2_REG          /* NULL, returns value of FAULT fiter register 2 */
#define PWM_READ_FILT3_REG          /* NULL, returns value of FAULT fiter register 3 */
#define PWM_WRITE_FILT0_REG         /* UWord16, writes FAULT filter register 0 */
#define PWM_WRITE_FILT1_REG         /* UWord16, writes FAULT filter register 1 */
#define PWM_WRITE_FILT2_REG         /* UWord16, writes FAULT filter register 2 */
#define PWM_WRITE_FILT3_REG         /* UWord16, writes FAULT filter register 3 */

#endif /* PWM_VERSION >= 3 */

/*******************************************************************************
  commands applicable to newer version of PWM module (800x)
*******************************************************************************/

#if PWM_VERSION >= 4

#define PWM_SET_PULSE_EDGE_CONTROL_0 /* PWM_xxx_MODE (NORMAL/PWMVAL) This bit controls PWM0/PWM1 pair. (ICCTRL->PEC0) */
#define PWM_SET_PULSE_EDGE_CONTROL_1 /* PWM_xxx_MODE (NORMAL/PWMVAL) This bit controls PWM2/PWM3 pair. (ICCTRL->PEC1) */
#define PWM_SET_PULSE_EDGE_CONTROL_2 /* PWM_xxx_MODE (NORMAL/PWMVAL) This bit controls PWM4/PWM5 pair. (ICCTRL->PEC2) */

#endif /* PWM_VERSION >= 4 */


/****************************************************************************
* PWM constants and type declarations use in the ioctl functions
*****************************************************************************/

#define PWM_ENABLE                      1
#define PWM_DISABLE                     0

#define PWM_ZERO_MASK                   0x0000   

#define PWM_IPOL_0                      PWM_PMCTL_IPOL_0
#define PWM_IPOL_1                      PWM_PMCTL_IPOL_1
#define PWM_IPOL_2                      PWM_PMCTL_IPOL_2

#define PWM_RELOAD_OPPORTUNITY_1        0
#define PWM_RELOAD_OPPORTUNITY_2        1
#define PWM_RELOAD_OPPORTUNITY_3        2
#define PWM_RELOAD_OPPORTUNITY_4        3
#define PWM_RELOAD_OPPORTUNITY_5        4
#define PWM_RELOAD_OPPORTUNITY_6        5
#define PWM_RELOAD_OPPORTUNITY_7        6
#define PWM_RELOAD_OPPORTUNITY_8        7
#define PWM_RELOAD_OPPORTUNITY_9        8
#define PWM_RELOAD_OPPORTUNITY_10       9
#define PWM_RELOAD_OPPORTUNITY_11       10
#define PWM_RELOAD_OPPORTUNITY_12       11
#define PWM_RELOAD_OPPORTUNITY_13       12
#define PWM_RELOAD_OPPORTUNITY_14       13
#define PWM_RELOAD_OPPORTUNITY_15       14
#define PWM_RELOAD_OPPORTUNITY_16       15

#define PWM_PRESCALER_DIV_1             0
#define PWM_PRESCALER_DIV_2             1
#define PWM_PRESCALER_DIV_4             2
#define PWM_PRESCALER_DIV_8             3

#define PWM_CORRECTION_NO               0
#define PWM_CORRECTION_SOFTWARE         1
#define PWM_CORRECTION_DURING_DEADTIME  2
#define PWM_CORRECTION_DURING_CYCLE     3

#if (PWM_HAS_FAULTS) & 1
#define PWM_FAULT_0                     PWM_PMFSA_FTACK0
#endif
#if (PWM_HAS_FAULTS) & 2
#define PWM_FAULT_1                     PWM_PMFSA_FTACK1
#endif
#if (PWM_HAS_FAULTS) & 4
#define PWM_FAULT_2                     PWM_PMFSA_FTACK2
#endif
#if (PWM_HAS_FAULTS) & 8
#define PWM_FAULT_3                     PWM_PMFSA_FTACK3
#endif

#define PWM_ALIGN_EDGE                  1
#define PWM_ALIGN_CENTER                0

#define PWM_CHANNEL_45                  0x0004
#define PWM_CHANNEL_23                  0x0002
#define PWM_CHANNEL_01                  0x0001

#define PWM_LOAD_INDEP                  0
#define PWM_LOAD_FROM_0_TO_5            1
#define PWM_LOAD_FROM_0_TO_3            2

#define PWM_STOP                        0
#define PWM_RUN                         1

#define PWM_80X_COMPATIBLE              0
#define PWM_ENHANCED                    1

#if PWM_VERSION >= 2

#define PWM_NORMAL                      0x00
#define PWM_INVERT                      0x01

#endif

#if PWM_VERSION == 2

#define PWM_SOURCE_PWM                  0x00
#define PWM_SOURCE_ADC_0                0x01
#define PWM_SOURCE_PWMSRC_0             0x02
#define PWM_SOURCE_TMR_0                0x03
#define PWM_SOURCE_ADC_1                0x01
#define PWM_SOURCE_PWMSRC_1             0x02
#define PWM_SOURCE_TMR_1                0x03
#define PWM_SOURCE_SRC_0                0x04
#define PWM_SOURCE_ADC_2                0x01
#define PWM_SOURCE_PWMSRC_2             0x02
#define PWM_SOURCE_TMR_2                0x03

#elif PWM_VERSION >= 3

#define PWM_SOURCE_PWM                  0x00
#define PWM_SOURCE_PWMSRC               0x01
#define PWM_SOURCE_PWMSRC_0             0x01
#define PWM_SOURCE_PWMSRC_1             0x01
#define PWM_SOURCE_PWMSRC_2             0x01
#define PWM_SOURCE_SRC_0                0x02

#endif /* PWM_VERSION 2,3 */

#if PWM_VERSION >= 4

#define PWM_NORMAL_MODE                 0x00
#define PWM_PWMVAL_MODE                 0x01

#endif /* PWM_VERSION 4 */




 
/****************************************************************************/

/*  pwm_tPWMChannelSwap contains three control bits representing channel 
    swapping of PWM signals. The bits can be combined in a numerical value
    that represents the union of the appropriate bits.  For example, 
    the value 0x05 indicates that PWM channel 0 and 1 are swapped, 
    channel 4 and 5 are swapped. 
*/
typedef UWord16 pwm_tPWMChannelSwap;    

/*  pwm_tSignalMask contains six control bits representing six PWM signals, 
    shown below. The bits can be combined in a numerical value that represents 
    the union of the appropriate bits. For example, the value 0x15 indicates
    that PWM signals 0, 2, and 4 are set. 
*/
typedef UWord16 pwm_tPWMSignalMask;    

typedef struct
{
    Word16  pwmChannel_0_Value;
    Word16  pwmChannel_2_Value;
    Word16  pwmChannel_4_Value;
} pwm_sComplementaryValues;

typedef struct
{
    Word16  pwmChannel_0_Value;
    Word16  pwmChannel_1_Value;
    Word16  pwmChannel_2_Value;
    Word16  pwmChannel_3_Value;
    Word16  pwmChannel_4_Value;
    Word16  pwmChannel_5_Value;
} pwm_sIndependentValues;

typedef struct
{
    pwm_tPWMSignalMask   SoftwareControlled;
    pwm_tPWMSignalMask   OutputControl;
} pwm_sOutputControl;

typedef struct
{
    Word16    DutyCycle;
    UWord16   Vlmode;
} pwm_sUpdateValueSetVlmode;

typedef struct
{
    pwm_tPWMSignalMask     Mask;
    pwm_tPWMChannelSwap   Swap;
} pwm_sChannelControl;

/*  mc_tSignalMask is now obsolete and replaced by a pwm_tSignalMask type
    It is defined here for backward compatibility only
*/
typedef UWord16 mc_tPWMSignalMask;    
                                        
#define MC_PWM_SIGNAL_0       0x0001
#define MC_PWM_SIGNAL_1       0x0002
#define MC_PWM_SIGNAL_2       0x0004
#define MC_PWM_SIGNAL_3       0x0008
#define MC_PWM_SIGNAL_4       0x0010
#define MC_PWM_SIGNAL_5       0x0020
#define MC_PWM_NO_SIGNALS     0x0000     /* No (none) PWM signal */ 
#define MC_PWM_ALL_SIGNALS   (MC_PWM_SIGNAL_0 | MC_PWM_SIGNAL_1 | MC_PWM_SIGNAL_2 | \
                              MC_PWM_SIGNAL_3 | MC_PWM_SIGNAL_4 | MC_PWM_SIGNAL_5)

/*****************************************************************
* PWM Register Bits Defines, used in ioct command implementation
******************************************************************/

/* PWM Control Register PMCTL */
#define PWM_PMCTL_LDFQ_MASK    0xf000   /* Load Frequency Bits */  
#define PWM_PMCTL_LDFQ_0       0x1000   /* Load Frequency Bit 0 */  
#define PWM_PMCTL_LDFQ_1       0x2000   /* Load Frequency Bit 1 */  
#define PWM_PMCTL_LDFQ_2       0x4000   /* Load Frequency Bit 2 */  
#define PWM_PMCTL_LDFQ_3       0x8000   /* Load Frequency Bit 3 */  
#define PWM_PMCTL_HALF         0x0800   /* Half Cycle Reload */
#define PWM_PMCTL_IPOL_MASK    0x0700   /* Current Polarity Bits */  
#define PWM_PMCTL_IPOL_0       0x0100   /* Current Polarity Bit 0 */  
#define PWM_PMCTL_IPOL_1       0x0200   /* Current Polarity Bit 1 */  
#define PWM_PMCTL_IPOL_2       0x0400   /* Current Polarity Bit 2 */  
#define PWM_PMCTL_PRSC_MASK    0x00c0   /* Prescaler Bits */  
#define PWM_PMCTL_PRSC_0       0x0040   /* Prescaler Bit 0 */  
#define PWM_PMCTL_PRSC_1       0x0080   /* Prescaler Bit 1 */  
#define PWM_PMCTL_PWMRIE       0x0020   /* Reload Interrupt Enable Bit */
#define PWM_PMCTL_PWMF         0x0010   /* Reload Flag */
#define PWM_PMCTL_ISENS_MASK   0x000c   /* Current Sense Bits */  
#define PWM_PMCTL_ISENS_0      0x0004   /* Current Sense Bit 0 */  
#define PWM_PMCTL_ISENS_1      0x0008   /* Current Sense Bit 1 */  
#define PWM_PMCTL_LDOK         0x0002   /* Load Okay Bit */
#define PWM_PMCTL_PWMEN        0x0001   /* PWM Enable Bit */

/* PWM Fault Control Register PMFCTL */
#define PWM_PMFCTL_FIE3        0x0080   /* Fault3 Pin Interrupt Enable Bit */
#define PWM_PMFCTL_FMODE3      0x0040   /* Fault3 Pin Clearing Mode Bit */
#define PWM_PMFCTL_FIE2        0x0020   /* Fault2 Pin Interrupt Enable Bit */
#define PWM_PMFCTL_FMODE2      0x0010   /* Fault2 Pin Clearing Mode Bit */
#define PWM_PMFCTL_FIE1        0x0008   /* Fault1 Pin Interrupt Enable Bit */
#define PWM_PMFCTL_FMODE1      0x0004   /* Fault1 Pin Clearing Mode Bit */
#define PWM_PMFCTL_FIE0        0x0002   /* Fault0 Pin Interrupt Enable Bit */
#define PWM_PMFCTL_FMODE0      0x0001   /* Fault0 Pin Clearing Mode Bit */
#if PWM_VERSION >= 3
#define PWM_PMFCTL_FPOL0       0x0100
#define PWM_PMFCTL_FPOL1       0x0200
#define PWM_PMFCTL_FPOL2       0x0400
#define PWM_PMFCTL_FPOL3       0x0800
#endif /* PWM_VERSION >= 3 */


/* PWM Fault Status & Acknowledge Register PMFSA */
#define PWM_PMFSA_FPIN3        0x8000
#define PWM_PMFSA_FFLAG3       0x4000
#define PWM_PMFSA_FPIN2        0x2000
#define PWM_PMFSA_FFLAG2       0x1000
#define PWM_PMFSA_FPIN1        0x0800
#define PWM_PMFSA_FFLAG1       0x0400
#define PWM_PMFSA_FPIN0        0x0200
#define PWM_PMFSA_FFLAG0       0x0100
#define PWM_PMFSA_FTACK3       0x0040   /* Fault3 Pin Acknowledge Bit */
#define PWM_PMFSA_FTACK2       0x0010   /* Fault2 Pin Acknowledge Bit */
#define PWM_PMFSA_FTACK1       0x0004   /* Fault1 Pin Acknowledge Bit */
#define PWM_PMFSA_FTACK0       0x0001   /* Fault0 Pin Acknowledge Bit */

/* PWM Output Control Register PMOUT */
#define PWM_PMOUT_PAD_EN       0x8000   /* Output Pad Output Enable */
#define PWM_PMOUT_OUTCTL_MASK  0x3f00   /* Output Control Enables OUTCTL5-0 */
#define PWM_PMOUT_OUT_MASK     0x003f   /* Output Control Bits OUT5-0 */

/* PWM Config Register PMCFG */
#define PWM_PMCFG_DBG_EN       0x4000   /* EOnCE debug mode, enable PWM outputs */
#define PWM_PMCFG_WAIT_EN      0x2000   /* WAIT mode, enable PWM outputs */
#define PWM_PMCFG_EDG          0x1000   /* Edge-Aligned or Center-Aligned PWM's */
#define PWM_PMCFG_TOPNEG_MASK  0x0700   /* Top-side PWM Polarity Bits, channel 5-0 */
#define PWM_PMCFG_TOPNEG45     0x0400   /* Top-side PWM Polarity Bit, channel 4-5 */
#define PWM_PMCFG_TOPNEG23     0x0200   /* Top-side PWM Polarity Bit, channel 2-3 */
#define PWM_PMCFG_TOPNEG01     0x0100   /* Top-side PWM Polarity Bit, channel 0-1 */
#define PWM_PMCFG_BOTNEG_MASK  0x0070   /* Bottom-side PWM Polarity Bits, channel 5-0 */
#define PWM_PMCFG_BOTNEG45     0x0040   /* Bottom-side PWM Polarity Bit, channel 4-5 */
#define PWM_PMCFG_BOTNEG23     0x0020   /* Bottom-side PWM Polarity Bit, channel 2-3 */
#define PWM_PMCFG_BOTNEG01     0x0010   /* Bottom-side PWM Polarity Bit, channel 0-1 */
#define PWM_PMCFG_INDEP_MASK   0x000e   /* Independent or Complementary Pair, channel 5-0 */
#define PWM_PMCFG_INDEP45      0x0008   /* Independent or Complementary Pair Operation, channel 4-5 */
#define PWM_PMCFG_INDEP23      0x0004   /* Independent or Complementary Pair Operation, channel 2-3 */
#define PWM_PMCFG_INDEP01      0x0002   /* Independent or Complementary Pair Operation, channel 0-1 */
#define PWM_PMCFG_WP           0x0001   /* Write Protect Bit */

/* PWM Channel Control Register PMCCR */
#define PWM_PMCCR_ENHA         0x8000   /* Enable Hardware Accelerator */
#define PWM_PMCCR_nBX          0x4000   /* DSP56F80X Compatibility */
#define PWM_PMCCR_MSK_MASK     0x3f00   /* Mask bits */
#define PWM_PMCCR_VLMODE_MASK  0x0030   /* Value Register Load Mode bits */
#define PWM_PMCCR_SWP_MASK     0x0007   /* Swap bits */

/* PWM Port Register PMPORT */
#define PWM_PMPORT_IS2         0x0040   /* Current Status Input IS2 */
#define PWM_PMPORT_IS1         0x0020   /* Current Status Input IS1 */
#define PWM_PMPORT_IS0         0x0010   /* Current Status Input IS0 */
#define PWM_PMPORT_IS_MASK     0x0070   /* Current Status Inputs */
#define PWM_PMPORT_FAULT3      0x0008   /* Fault Status Input #3 */
#define PWM_PMPORT_FAULT2      0x0004   /* Fault Status Input #2 */
#define PWM_PMPORT_FAULT1      0x0002   /* Fault Status Input #1 */
#define PWM_PMPORT_FAULT0      0x0001   /* Fault Status Input #0 */
#define PWM_PMPORT_FAULT_MASK  0x000f   /* Fault Status Inputs */

/* PWM Internal Correction Control Register PMICCR */
#define PWM_PMICCR_PCE2        0x0020   /* Pulse Edge Control 2 */
#define PWM_PMICCR_PCE1        0x0010   /* Pulse Edge Control 1 */
#define PWM_PMICCR_PCE0        0x0008   /* Pulse Edge Control 0 */
#define PWM_PMICCR_ICC2        0x0004   /* Internal Current Control 2 */
#define PWM_PMICCR_ICC1        0x0002   /* Internal Current Control 1 */
#define PWM_PMICCR_ICC0        0x0001   /* Internal Current Control 0 */

/* Mask applied when acessing PWMDISMAP register */

#define PWM_FAULT_1_2_3_ELIMINATE \
    ((PWM_HAS_FAULTS) | \
    ((PWM_HAS_FAULTS) << 4) | \
    ((PWM_HAS_FAULTS) << 8) | \
    ((PWM_HAS_FAULTS) << 12))

/* VERSION_2 registers */
#if PWM_VERSION == 2

/* PWM Source Control Register PMSRC */
#define PWM_PMSRC_SRC0_MASK    0x0003
#define PWM_PMSRC_SRC1_MASK    0x001C
#define PWM_PMSRC_SRC2_MASK    0x00E0
    
#endif /* PWM_VERSION == 2 */
    
/* VERSION_2+ registers */
#if PWM_VERSION >= 2

#define PWM_PMSRC_CINV0        0x0100
#define PWM_PMSRC_CINV1        0x0200
#define PWM_PMSRC_CINV2        0x0400
#define PWM_PMSRC_CINV3        0x0800
#define PWM_PMSRC_CINV4        0x1000
#define PWM_PMSRC_CINV5        0x2000

#endif /* PWM_VERSION_2 */

/* VERSION_3+ registers */
#if PWM_VERSION >= 3

/* PWM Source Control Register PMSRC */
#define PWM_PMSRC_SRC0_MASK    0x0001
#define PWM_PMSRC_SRC1_MASK    0x000C
#define PWM_PMSRC_SRC2_MASK    0x0060

/* Synchronization window register */
#define PWM_SYNC_OUT_EN        0x8000
#define PWM_SYNC_WINDOW_MASK   0x7fff

/* Fault fiter registers */
#define PWM_FILT_CNT_MASK      0x0700
#define PWM_FILT_PER_MASK      0x00ff

#endif /* PWM_VERSION_3 */

/*******************************************************************************
    Bit names of older SDK version, maintained here for backward compatibility.
*******************************************************************************/

/* Do not use for new development ! */
#define PWM_LDFQ_0    PWM_PMCTL_LDFQ_0
#define PWM_LDFQ_1    PWM_PMCTL_LDFQ_1
#define PWM_LDFQ_2    PWM_PMCTL_LDFQ_2
#define PWM_LDFQ_3    PWM_PMCTL_LDFQ_3
#define PWM_LDFQ      PWM_PMCTL_LDFQ_MASK
#define PWM_HALF      PWM_PMCTL_HALF     
#define PWM_IPOL      PWM_PMCTL_IPOL_MASK  
#define PWM_PRSC_0    PWM_PMCTL_PRSC_0 
#define PWM_PRSC_1    PWM_PMCTL_PRSC_1 
#define PWM_PRSC      PWM_PMCTL_PRSC_MASK
#define PWM_PWMRIE    PWM_PMCTL_PWMRIE
#define PWM_PWMF      PWM_PMCTL_PWMF  
#define PWM_ISENS_0   PWM_PMCTL_ISENS_0  
#define PWM_ISENS_1   PWM_PMCTL_ISENS_1  
#define PWM_ISENS     PWM_PMCTL_ISENS_MASK
#define PWM_LDOK      PWM_PMCTL_LDOK 
#define PWM_PWMEN     PWM_PMCTL_PWMEN
#define PWM_FIE_3     PWM_PMFCTL_FIE3   
#define PWM_FIE_2     PWM_PMFCTL_FIE2   
#define PWM_FIE_1     PWM_PMFCTL_FIE1   
#define PWM_FIE_0     PWM_PMFCTL_FIE0   
#define PWM_FMODE_3   PWM_PMFCTL_FMODE3
#define PWM_FMODE_2   PWM_PMFCTL_FMODE2
#define PWM_FMODE_1   PWM_PMFCTL_FMODE1
#define PWM_FMODE_0   PWM_PMFCTL_FMODE0
#define PWM_FTACK_3   PWM_PMFSA_FTACK3
#define PWM_FTACK_2   PWM_PMFSA_FTACK2
#define PWM_FTACK_1   PWM_PMFSA_FTACK1
#define PWM_FTACK_0   PWM_PMFSA_FTACK0
#define PWM_PAD_EN    PWM_PMOUT_PAD_EN     
#define PWM_OUTCTL    PWM_PMOUT_OUTCTL_MASK
#define PWM_OUT       PWM_PMOUT_OUT_MASK
#define PWM_DBG_EN    PWM_PMCFG_DBG_EN     
#define PWM_WAIT_EN   PWM_PMCFG_WAIT_EN    
#define PWM_EDG       PWM_PMCFG_EDG        
#define PWM_TOPNEG45  PWM_PMCFG_TOPNEG45   
#define PWM_TOPNEG23  PWM_PMCFG_TOPNEG23   
#define PWM_TOPNEG01  PWM_PMCFG_TOPNEG01   
#define PWM_TOPNEG    PWM_PMCFG_TOPNEG_MASK
#define PWM_BOTNEG45  PWM_PMCFG_BOTNEG45   
#define PWM_BOTNEG23  PWM_PMCFG_BOTNEG23   
#define PWM_BOTNEG01  PWM_PMCFG_BOTNEG01   
#define PWM_BOTNEG    PWM_PMCFG_BOTNEG_MASK
#define PWM_INDEP45   PWM_PMCFG_INDEP45    
#define PWM_INDEP23   PWM_PMCFG_INDEP23    
#define PWM_INDEP01   PWM_PMCFG_INDEP01    
#define PWM_INDEP     PWM_PMCFG_INDEP_MASK
#define PWM_WP        PWM_PMCFG_WP         
#define PWM_ENHA      PWM_PMCCR_ENHA
#define PWM_nBX       PWM_PMCCR_nBX 

/***********************************************************************
* PWM init
***********************************************************************/

void pwmInit(arch_sPWM *pPwmBase);
#define ioctlPWM_INIT(pPwmBase, param) pwmInit(pPwmBase)

/* PWM Control Register */

#define ioctlPWM_SET_RELOAD_FREQUENCY(pPwmBase, param) \
  periphBitGrpSet(PWM_PMCTL_LDFQ_MASK, ((param) << 12), &((pPwmBase)->pmctl))

#define ioctlPWM_HALF_CYCLE_RELOAD(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCTL_HALF, &((pPwmBase)->pmctl)); \
  else periphBitClear(PWM_PMCTL_HALF, &((pPwmBase)->pmctl))

#define ioctlPWM_SET_CURRENT_POLARITY(pPwmBase, param) \
  periphBitGrpRS(PWM_PMCTL_IPOL_MASK, param, &((pPwmBase)->pmctl))

#define ioctlPWM_SET_PRESCALER(pPwmBase, param) \
  periphBitGrpSet(PWM_PMCTL_PRSC_MASK, ((param) << 6), &((pPwmBase)->pmctl))
  
#define ioctlPWM_RELOAD_INT(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCTL_PWMRIE, &((pPwmBase)->pmctl)); \
  else periphBitClear(PWM_PMCTL_PWMRIE, &((pPwmBase)->pmctl))

#if PWM_HAS_IS_PINS
#define ioctlPWM_SET_CURRENT_SENSING(pPwmBase, param) \
  periphBitGrpSet(PWM_PMCTL_ISENS_MASK, ((param) << 2), &((pPwmBase)->pmctl))
#endif

#define ioctlPWM_DEVICE(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCTL_PWMEN, &((pPwmBase)->pmctl)); \
  else periphBitClear(PWM_PMCTL_PWMEN, &((pPwmBase)->pmctl))

#define ioctlPWM_CLEAR_RELOAD_FLAG(pPwmBase, param) \
  periphBitClear(PWM_PMCTL_PWMF, &((pPwmBase)->pmctl))

#define ioctlPWM_LOAD_OK(pPwmBase, param) \
  periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl))

/* PWM Fault Control Register */
    
#define ioctlPWM_FAULT_INT_ENABLE(pPwmBase, param) \
  periphBitSet(((param)<<1) & (PWM_PMFCTL_FIE0 | PWM_PMFCTL_FIE1 | \
    PWM_PMFCTL_FIE2 | PWM_PMFCTL_FIE3), &((pPwmBase)->pmfctl))

#define ioctlPWM_FAULT_INT_DISABLE(pPwmBase, param) \
  periphBitClear(((param)<<1) & (PWM_PMFCTL_FIE0 | PWM_PMFCTL_FIE1 | \
    PWM_PMFCTL_FIE2 | PWM_PMFCTL_FIE3), &((pPwmBase)->pmfctl))

#define ioctlPWM_SET_AUTOMATIC_FAULT_CLEAR(pPwmBase, param) \
  periphBitSet((param) & (PWM_PMFCTL_FMODE0 | PWM_PMFCTL_FMODE1 | \
    PWM_PMFCTL_FMODE2 | PWM_PMFCTL_FMODE3), &((pPwmBase)->pmfctl))

#define ioctlPWM_SET_MANUAL_FAULT_CLEAR(pPwmBase, param) \
  periphBitClear((param) & (PWM_PMFCTL_FMODE0 | PWM_PMFCTL_FMODE1 | \
    PWM_PMFCTL_FMODE2 | PWM_PMFCTL_FMODE3), &((pPwmBase)->pmfctl))

#if PWM_VERSION >= 3

#define ioctlPWM_SET_ACTIVE_HIGH_FAULTS(pPwmBase, param) \
  periphBitClear((((param) & (PWM_FAULT_0)) ? PWM_PMFCTL_FPOL0 : 0) | \
      (((param) & (PWM_FAULT_1)) ? PWM_PMFCTL_FPOL1 : 0) | \
      (((param) & (PWM_FAULT_2)) ? PWM_PMFCTL_FPOL2 : 0) | \
      (((param) & (PWM_FAULT_3)) ? PWM_PMFCTL_FPOL3 : 0), &((pPwmBase)->pmfctl))
    
#define ioctlPWM_SET_ACTIVE_LOW_FAULTS(pPwmBase, param) \
  periphBitSet((((param) & (PWM_FAULT_0)) ? PWM_PMFCTL_FPOL0 : 0) | \
      (((param) & (PWM_FAULT_1)) ? PWM_PMFCTL_FPOL1 : 0) | \
      (((param) & (PWM_FAULT_2)) ? PWM_PMFCTL_FPOL2 : 0) | \
      (((param) & (PWM_FAULT_3)) ? PWM_PMFCTL_FPOL3 : 0), &((pPwmBase)->pmfctl))

#endif /* PWM_VERSION >= 3 */

/* PWM Fault Status & Acknowledge Register */

#define ioctlPWM_CLEAR_FAULT_FLAG(pPwmBase, param) \
  periphMemWrite((param) & (PWM_PMFSA_FTACK0 | PWM_PMFSA_FTACK1 | \
    PWM_PMFSA_FTACK2 | PWM_PMFSA_FTACK3), &((pPwmBase)->pmfsa))
          
#define ioctlPWM_TEST_FAULT_PINS(pPwmBase, param) \
  periphBitTest(((param) << 9) & (PWM_PMFSA_FPIN0 | PWM_PMFSA_FPIN1 | \
    PWM_PMFSA_FPIN2 | PWM_PMFSA_FPIN3), &((pPwmBase)->pmfsa))
          
#define ioctlPWM_TEST_FAULT_FLAGS(pPwmBase, param) \
  periphBitTest(((param) << 8) & (PWM_PMFSA_FFLAG0 | PWM_PMFSA_FFLAG1 | \
    PWM_PMFSA_FFLAG2 | PWM_PMFSA_FFLAG3), &((pPwmBase)->pmfsa))
          
/* PWM Output Control Register */

#define ioctlPWM_OUTPUT_PAD(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMOUT_PAD_EN, &((pPwmBase)->pmout)); \
  else periphBitClear(PWM_PMOUT_PAD_EN, &((pPwmBase)->pmout))

#define ioctlPWM_OUTPUT_SOFTWARE_CONTROL(pPwmBase, param) \
  periphBitGrpRS(PWM_PMOUT_OUTCTL_MASK, ((param) << 8), &((pPwmBase)->pmout))

#define ioctlPWM_OUTPUT_CONTROL(pPwmBase, param) \
  periphBitGrpRS(PWM_PMOUT_OUT_MASK, param, &((pPwmBase)->pmout))

          
/* PWM Counter Modulo Register */

#define ioctlPWM_SET_MODULO(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmcm))

#define ioctlPWM_GET_MODULO(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pwmcm))

         
/* PWM Deadtime Register */

#if PWM_VERSION <= 1

#define ioctlPWM_SET_DEADTIME(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pmdeadtm))

#elif PWM_VERSION >= 2

#define ioctlPWM_SET_DEADTIME(pPwmBase, param) \
  { periphMemWrite(param, &((pPwmBase)->pmdeadtm0)); \
    periphMemWrite(param, &((pPwmBase)->pmdeadtm1)); }

#define ioctlPWM_SET_DEADTIME_0(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pmdeadtm0))

#define ioctlPWM_SET_DEADTIME_1(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pmdeadtm1))

#else
#error Unknown PWM version
#endif  

/* PWM Disable Mapping Register 1 */

#define ioctlPWM_WRITE_DISABLE_MAPPING_REG1(pPwmBase, param) \
  periphMemWrite((param) & PWM_FAULT_1_2_3_ELIMINATE, &((pPwmBase)->pmdismap1))
          
/* PWM Disable Mapping2 Register */

#define ioctlPWM_WRITE_DISABLE_MAPPING_REG2(pPwmBase, param) \
  periphMemWrite((param) & PWM_FAULT_1_2_3_ELIMINATE, &((pPwmBase)->pmdismap2))

/* PWM Config Register */

#define ioctlPWM_DEBUG_OPERATION(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCFG_DBG_EN, &((pPwmBase)->pmcfg)); \
  else periphBitClear(PWM_PMCFG_DBG_EN, &((pPwmBase)->pmcfg))

#define ioctlPWM_WAIT_OPERATION(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCFG_WAIT_EN, &((pPwmBase)->pmcfg)); \
  else periphBitClear(PWM_PMCFG_WAIT_EN, &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_ALIGNMENT(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCFG_EDG, &((pPwmBase)->pmcfg)); \
  else periphBitClear(PWM_PMCFG_EDG, &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_NEG_TOP_SIDE_POLARITY(pPwmBase, param) \
  periphBitGrpRS(PWM_PMCFG_TOPNEG_MASK, ((param) << 8), &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_NEG_BOTTOM_SIDE_POLARITY(pPwmBase, param) \
  periphBitGrpRS(PWM_PMCFG_BOTNEG_MASK, ((param) << 4), &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_INDEPENDENT_OPERATION(pPwmBase, param) \
  periphBitGrpRS(PWM_PMCFG_INDEP_MASK, ((param) << 1), &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_INDEPENDENT_MODE(pPwmBase, param) \
  periphBitSet(((param) << 1), &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_COMPLEMENTARY_MODE(pPwmBase, param) \
  periphBitClear(((param) << 1), &((pPwmBase)->pmcfg))

#define ioctlPWM_SET_WRITE_PROTECT(pPwmBase, param) \
  periphBitSet(PWM_PMCFG_WP, &((pPwmBase)->pmcfg))
          

/* PWM Channel Control Register */

#define ioctlPWM_HARDWARE_ACCELERATION(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \
  else periphBitClear(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr))
          
#define ioctlPWM_MASK_SWAP_OPERATION(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMCCR_nBX, &((pPwmBase)->pmccr)); \
  else periphBitClear(PWM_PMCCR_nBX, &((pPwmBase)->pmccr))

#define ioctlPWM_SET_CHANNEL_MASK(pPwmBase, param) \
  periphBitGrpRS(PWM_PMCCR_MSK_MASK, ((param) << 8), &((pPwmBase)->pmccr))
          
#define ioctlPWM_SET_LOAD_MODE(pPwmBase, param) \
  { periphBitClear(~((((param) << 4)) | (~PWM_PMCCR_VLMODE_MASK)), &((pPwmBase)->pmccr)); \
    periphBitSet(((param) << 4), &((pPwmBase)->pmccr)); } 
/*
#define ioctlPWM_SET_LOAD_MODE(pPwmBase, param) \
  { periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr));  \
    periphBitClear(~(((((UWord16)(param)) << 4)) | (~PWM_PMCCR_VLMODE_MASK)), &((pPwmBase)->pmccr)); \
    periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr));  \
    periphBitSet((((UWord16)(param)) << 4), &((pPwmBase)->pmccr)); } 
*/
/*  periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); -- needed in older PWM rev  */
 
#define ioctlPWM_SET_SWAP(pPwmBase, param) \
  { periphBitClear(~((param) | (~PWM_PMCCR_SWP_MASK)), &((pPwmBase)->pmccr)); \
    periphBitSet(param, &((pPwmBase)->pmccr)); } 

/*
#define ioctlPWM_SET_SWAP(pPwmBase, param) \
  { periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr));  \
    periphBitClear(~((((UWord16)(param))) | (~PWM_PMCCR_SWP_MASK)), &((pPwmBase)->pmccr)); \
    periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr));  \
    periphBitSet(((UWord16)(param)), &((pPwmBase)->pmccr)); } 
*/          
/*  periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr));  needed in older PWM rev  */
 
 
/* PWM Fault Status & Acknowledge Register */

#define ioctlPWM_READ_FAULT_STATUS_REG(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pmfsa))

          
/* PWM Counter Register */

#define ioctlPWM_READ_COUNTER_REG(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pmcnt))
 
/* 
#define ioctlPWM_WRITE_COUNTER_REG(pPwmBase, param) \
  periphMemWrite(((UWord16)(param)), &((pPwmBase)->pmcnt))
*/ 

          
/* PWM Control Register */

#define ioctlPWM_READ_CONTROL_REG(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pmctl))

          
/* PWM Port Register */

#define ioctlPWM_READ_PORT_REG(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pmport))

#if PWM_HAS_IS_PINS 
#define ioctlPWM_GET_CURRENT_STATUS_INPUTS(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_IS_MASK) 
#endif

#define ioctlPWM_GET_FAULT_INPUTS(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_FAULT_MASK) 


#define ioctlPWM_GET_FAULT_INPUT_0(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_FAULT0)

#define ioctlPWM_GET_FAULT_INPUT_1(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_FAULT1)

#define ioctlPWM_GET_FAULT_INPUT_2(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_FAULT2)

#define ioctlPWM_GET_FAULT_INPUT_3(pPwmBase, param) \
  (periphMemRead(&((pPwmBase)->pmport)) & PWM_PMPORT_FAULT3)


          

/* PWM Value Registers */

#define ioctlPWM_WRITE_VALUE_REG_0(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmval[0]))
          
#define ioctlPWM_WRITE_VALUE_REG_1(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmval[1]))

#define ioctlPWM_WRITE_VALUE_REG_2(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmval[2]))

#define ioctlPWM_WRITE_VALUE_REG_3(pPwmBase, param) \
  periphMemWrite(param , &((pPwmBase)->pwmval[3]))

#define ioctlPWM_WRITE_VALUE_REG_4(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmval[4]))

#define ioctlPWM_WRITE_VALUE_REG_5(pPwmBase, param) \
  periphMemWrite(param, &((pPwmBase)->pwmval[5]))

#define ioctlPWM_WRITE_VALUE_REGS_COMPL(pPwmBase, param) \
  { periphMemWrite( ((pwm_sComplementaryValues*)(param))->pwmChannel_0_Value, &((pPwmBase)->pwmval[0])); \
    periphMemWrite( ((pwm_sComplementaryValues*)(param))->pwmChannel_2_Value, &((pPwmBase)->pwmval[2])); \
    periphMemWrite( ((pwm_sComplementaryValues*)(param))->pwmChannel_4_Value, &((pPwmBase)->pwmval[4]));}

#define ioctlPWM_WRITE_VALUE_REGS_INDEP(pPwmBase, param) \
  { periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_0_Value , &((pPwmBase)->pwmval[0])); \
    periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_1_Value , &((pPwmBase)->pwmval[1])); \
    periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_2_Value , &((pPwmBase)->pwmval[2])); \
    periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_3_Value , &((pPwmBase)->pwmval[3])); \
    periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_4_Value , &((pPwmBase)->pwmval[4])); \
    periphMemWrite( ((pwm_sIndependentValues*)(param))->pwmChannel_5_Value , &((pPwmBase)->pwmval[5]));}

#define ioctlPWM_UPDATE_VALUE_REG_0(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[0])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REG_1(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[1])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REG_2(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[2])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REG_3(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[3])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REG_4(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[4])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REG_5(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, param ), &((pPwmBase)->pwmval[5])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); } 

#define ioctlPWM_UPDATE_VALUE_REGS_COMPL(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sComplementaryValues*)(param))->pwmChannel_0_Value) , &((pPwmBase)->pwmval[0])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sComplementaryValues*)(param))->pwmChannel_2_Value) , &((pPwmBase)->pwmval[2])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sComplementaryValues*)(param))->pwmChannel_4_Value) , &((pPwmBase)->pwmval[4])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); }

#define ioctlPWM_UPDATE_VALUE_REGS_INDEP(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_0_Value) , &((pPwmBase)->pwmval[0])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_1_Value) , &((pPwmBase)->pwmval[1])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_2_Value) , &((pPwmBase)->pwmval[2])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_3_Value) , &((pPwmBase)->pwmval[3])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_4_Value) , &((pPwmBase)->pwmval[4])); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sIndependentValues*)(param))->pwmChannel_5_Value) , &((pPwmBase)->pwmval[5])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); }

          
/* PWM Output Control Register */

#define ioctlPWM_SOFTWARE_OUTPUTS_CONTROL(pPwmBase, param) \
  { UWord16 TempOutctl;  \
    TempOutctl = PWM_PMOUT_PAD_EN | ((pwm_sOutputControl*)(param))->SoftwareControlled << 8 | ((pwm_sOutputControl*)(param))->OutputControl; \
    periphMemWrite((TempOutctl), &((pPwmBase)->pmout)); } 


/* PWM Channel Control Register */
          
#define ioctlPWM_SET_MASK_SWAP(pPwmBase, param) \
  { UWord16 TempChannelControl;  \
    TempChannelControl = periphMemRead(&((pPwmBase)->pmccr)) & (PWM_PMCCR_VLMODE_MASK | PWM_PMCCR_ENHA | PWM_PMCCR_nBX); \
    TempChannelControl = (((pwm_sChannelControl*)(param))->Mask << 8) | TempChannelControl | ((pwm_sChannelControl*)(param))->Swap; \
    periphMemWrite((TempChannelControl), &((pPwmBase)->pmccr)); } 

/*
#define ioctlPWM_SET_MASK_SWAP(pPwmBase, param) \
  { UWord16 TempChannelControl;  \
    TempChannelControl = periphMemRead(&((pPwmBase)->pmccr))& PWM_PMCCR_VLMODE_MASK; \
    TempChannelControl = PWM_PMCCR_ENHA | (((pwm_sChannelControl*)param)->Mask << 8) | TempChannelControl | ((pwm_sChannelControl*)param)->Swap; \
    periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \
    periphMemWrite((TempChannelControl), &((pPwmBase)->pmccr)); } 
*/ 
/*  periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \ needed in older PWM rev   */


#define ioctlPWM_UPDATE_VALUE_SET_VLMODE(pPwmBase, param) \
  { Word16 TempModulus;  \
    TempModulus = (Word16) periphMemRead(&((pPwmBase)->pwmcm)); \
    periphBitClear(PWM_PMCCR_VLMODE_MASK, &((pPwmBase)->pmccr)); \
    periphBitSet( ( (((pwm_sUpdateValueSetVlmode*)(param))->Vlmode) << 4 ), &((pPwmBase)->pmccr)); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sUpdateValueSetVlmode*)(param))->DutyCycle) , &((pPwmBase)->pwmval[0])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); }

/*
#define ioctlPWM_UPDATE_VALUE_SET_VLMODE(pPwmBase, param) \
  { UWord16 TempModulus;  \
    TempModulus = periphMemRead(&((pPwmBase)->pwmcm)); \
    periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \
    periphBitClear(PWM_PMCCR_VLMODE_MASK, &((pPwmBase)->pmccr)); \
    periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \
    periphBitSet( ( (((pwm_sUpdateValueSetVlmode*)param)->Vlmode) << 4 ), &((pPwmBase)->pmccr)); \
    periphMemWrite( mult_r( TempModulus, ((pwm_sUpdateValueSetVlmode*)param)->DutyCycle) , &((pPwmBase)->pwmval[0])); \
    periphBitSet(PWM_PMCTL_LDOK, &((pPwmBase)->pmctl)); }
*/
/*  periphBitSet(PWM_PMCCR_ENHA, &((pPwmBase)->pmccr)); \ needed in older PWM rev          */


/* PWM Internal Correction Control Register */

#define ioctlPWM_SET_HALF_CYCLE_INTERNAL_CORRECTION(pPwmBase, param) \
  periphBitSet(param, &((pPwmBase)->pmiccr))


#define ioctlPWM_SET_FULL_CYCLE_INTERNAL_CORRECTION(pPwmBase, param) \
  periphBitClear(param, &((pPwmBase)->pmiccr))

#define ioctlPWM_READ_INTERNAL_CORRECTION_CONTROL_REG(pPwmBase, param) \
  periphMemRead(&((pPwmBase)->pmiccr))

/* PWM_VERSION_2-only PWM Internal Source Control Register (PMSRC) */

#if PWM_VERSION >= 2

#define ioctlPWM_SET_SOURCE_0(pPwmBase, param) \
  periphBitGrpSet(PWM_PMSRC_SRC0_MASK, param, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_SOURCE_1(pPwmBase, param) \
  periphBitGrpSet(PWM_PMSRC_SRC1_MASK, ((param) << 2), &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_SOURCE_2(pPwmBase, param) \
  periphBitGrpSet(PWM_PMSRC_SRC2_MASK, ((param) << 5), &((pPwmBase)->pmsrc))


#define ioctlPWM_SET_COMPARE_INVERT_0(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV0, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV0, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_COMPARE_INVERT_1(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV1, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV1, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_COMPARE_INVERT_2(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV2, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV2, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_COMPARE_INVERT_3(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV3, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV3, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_COMPARE_INVERT_4(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV4, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV4, &((pPwmBase)->pmsrc))

#define ioctlPWM_SET_COMPARE_INVERT_5(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMSRC_CINV5, &((pPwmBase)->pmsrc)); \
  else periphBitClear(PWM_PMSRC_CINV5, &((pPwmBase)->pmsrc))
 

#endif /* PWM_VERSION_2 */

#if PWM_VERSION >= 3

/* enable SYNC signal output on FAULT2 pin */
#define ioctlPWM_ENABLE_SYNC_OUT(pPwmBase, param) \
  periphMemWrite(PWM_SYNC_OUT_EN, &((pPwmBase)->sync))

/* enable SYNC input in time window of given size */
#define ioctlPWM_ENABLE_SYNC_IN(pPwmBase, param) \
  periphMemWrite((param) & (PWM_SYNC_WINDOW_MASK) & (~(PWM_SYNC_OUT_EN)), &((pPwmBase)->sync))

/* disable SYNC input/output, revert pin to FAULT2 operation */
#define ioctlPWM_DISABLE_SYNC(pPwmBase, param) \
  periphMemWrite(0, &((pPwmBase)->sync))

/* returns value of fiter register */
#define ioctlPWM_READ_FILT0_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->ffilt0))   
#define ioctlPWM_READ_FILT1_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->ffilt1))   
#define ioctlPWM_READ_FILT2_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->ffilt2))   
#define ioctlPWM_READ_FILT3_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->ffilt3))   

/* writes filter register */
#define ioctlPWM_WRITE_FILT0_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->ffilt0))
#define ioctlPWM_WRITE_FILT1_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->ffilt1))
#define ioctlPWM_WRITE_FILT2_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->ffilt2))
#define ioctlPWM_WRITE_FILT3_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->ffilt3))

#endif /* PWM_VERSION_3 */

#if PWM_VERSION >= 4

/* PWM Internal Correction Control Register */
#define ioctlPWM_SET_PULSE_EDGE_CONTROL_0(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMICCR_PCE0, &((pPwmBase)->pmiccr)); \
  else periphBitClear(PWM_PMICCR_PCE0, &((pPwmBase)->pmiccr))
  
#define ioctlPWM_SET_PULSE_EDGE_CONTROL_1(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMICCR_PCE1, &((pPwmBase)->pmiccr)); \
  else periphBitClear(PWM_PMICCR_PCE1, &((pPwmBase)->pmiccr))

#define ioctlPWM_SET_PULSE_EDGE_CONTROL_2(pPwmBase, param) \
  if (param) periphBitSet(PWM_PMICCR_PCE2, &((pPwmBase)->pmiccr)); \
  else periphBitClear(PWM_PMICCR_PCE2, &((pPwmBase)->pmiccr))

  
#endif /* PWM_VERSION_4 */

  
#ifdef __cplusplus
}
#endif

#endif
