/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  qtimer.h
*
* $Date:      Mar-27-2009$
*
* $Version:   2.3.31.0$
*
* Description: Header file for the Quad Timer driver.
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  QT_VERSION_1 .. 56F83xx and 56F801x devices, see MC56F8300UM.pdf, MC56F8000RM.pdf
*  QT_VERSION_2 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  QT_VERSION_3 .. 56F800x devices, see MC56F800xRM.pdf
*
*******************************************************************************/

#ifndef __QTIMER_H
#define __QTIMER_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before qtimer.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Quad Timer module contains four identical counter/timer groups. Each 16-bit
* counter/timer group contains a prescaler, a counter, a load register, a hold register, a
* capture register, two compare registers, and two status and control registers.
* All of the registers except the prescaler are read/write capable.
* 
* The Load register provides the initialization value to the counter when the counter’s
* terminal value has been reached.
* The Hold register captures the counter’s value when other registers are being read.
* This feature supports the reading of cascaded counters.
* The Capture register enables an external signal to take a snapshot of the counter’s
* current value.
* 
* The CMP1 and CMP2 registers provide the values to which the counter is compared. If a
* match occurs, the OFLAG signal can be set, cleared, or toggled. At match time, an
* interrupt is generated if enabled, and the new compare value is loaded into CMP1 or
* CMP2 registers from CMPLD1 and CMPLD2 when enabled.
* 
* The Prescaler provides different time bases useful for clocking the counter/timer.
* The Counter provides the ability to count internal or external events. Input pins
* can be shared within a Timer module (set of four timer/counters).
*
* For more information, please refer to the user manual for the particular chip
* that you are using, such as the MC56F8300 Peripheral Manual, for a description
* of the Quad Timer device.
*
* The QT device driver interface uses "ioctl" call to control specific QT functions
* during operation. For details see "ioctl" call.
*
******************************************************************************/

/*******************************************************************************
    Quad Timer module identifiers 
*******************************************************************************/

#ifdef TMRA_BASE
#define QTIMER_A0   (&ArchIO.TimerA.ch0)
#define QTIMER_A1   (&ArchIO.TimerA.ch1)
#define QTIMER_A2   (&ArchIO.TimerA.ch2)
#define QTIMER_A3   (&ArchIO.TimerA.ch3)
#endif

#ifdef TMRB_BASE
#define QTIMER_B0   (&ArchIO.TimerB.ch0)
#define QTIMER_B1   (&ArchIO.TimerB.ch1)
#define QTIMER_B2   (&ArchIO.TimerB.ch2)
#define QTIMER_B3   (&ArchIO.TimerB.ch3)
#endif

#ifdef TMRC_BASE
#define QTIMER_C0   (&ArchIO.TimerC.ch0)
#define QTIMER_C1   (&ArchIO.TimerC.ch1)
#define QTIMER_C2   (&ArchIO.TimerC.ch2)
#define QTIMER_C3   (&ArchIO.TimerC.ch3)
#endif

#ifdef TMRD_BASE
#define QTIMER_D0   (&ArchIO.TimerD.ch0)
#define QTIMER_D1   (&ArchIO.TimerD.ch1)
#define QTIMER_D2   (&ArchIO.TimerD.ch2)
#define QTIMER_D3   (&ArchIO.TimerD.ch3)
#endif

/* single ("anonymous") module on some devices */
#ifdef TMR_BASE
#define QTIMER_0    (&ArchIO.Timer.ch0)
#define QTIMER_1    (&ArchIO.Timer.ch1)
#if QT_VERSION <= 2
#define QTIMER_2    (&ArchIO.Timer.ch2)
#define QTIMER_3    (&ArchIO.Timer.ch3)
#endif
#endif

/*************************************************************
* arch.h should define device-specific information about QT
**************************************************************/

#if !defined(QT_VERSION)
#error QTimer (QT) not properly described in arch.h (old Quick_Start version?)
#endif

/*******************************************************************************
    Defines for appconfig.h for each timer/counter
********************************************************************************

    #define INT_VECTOR_ADDR_yy          qtxxISR
    #define INT_PRIORITY_LEVEL_yy       one of INTC_DISABLED, INTC_LEVEL0, INTC_LEVEL1 or INTC_LEVEL2

    #define QT_xx_CTRL_INIT    0x0000
    #define QT_xx_SCR_INIT     0x0000
    #define QT_xx_CMP1_INIT    0x0000
    #define QT_xx_CMP2_INIT    0x0000
    #define QT_xx_LOAD_INIT    0x0000
    #define QT_xx_CNTR_INIT    0x0000
    #define QT_xx_CMPLD1_INIT  0x0000
    #define QT_xx_CMPLD2_INIT  0x0000
    #define QT_xx_COMSCR_INIT  0x0000

    where:
    xx is timer/counter:
        D0,D1,D2,D3,C0,C1,C2,C3,B0,B1,B2,B3,A0,A1,A2,A3
        
    yy is corresponding interrupt vector
        e.g. on 56F8346: 
            D: 52,53,54,55
            C: 56,57,58,59
            B: 60,61,62,63
            A: 64,65,66,67
    
*/

/*******************************************************************************
    ioctl() commands
*******************************************************************************/

/*      command                         parameters and commentary */
#define QT_INIT                         /* NULL */
#define QT_SET_COUNT_MODE               /* see below QT_xxx_MODE */
#define QT_SET_PRIMARY_SOURCE           /* see below */
#define QT_SET_SECONDARY_SOURCE         /* one of QT_COUNTER0_INPUT, QT_COUNTER1_INPUT, QT_COUNTER2_INPUT, QT_COUNTER3_INPUT */
#define QT_SET_COUNT_ONCE               /* QT_COUNT_REPEATEDLY / QT_UNTIL_COMPARE_AND_STOP */
#define QT_SET_COUNT_LENGTH             /* QT_ROLL_OVER / QT_UNTIL_COMPARE_AND_REINIT */
#define QT_SET_COUNT_DIRECTION          /* QT_COUNT_UP / QT_COUNT_DOWN */
#define QT_CO_CHANNEL_INIT              /* QT_ENABLE / QT_DISABLE */
#define QT_SET_OUTPUT_MODE              /* see below */

#define QT_CLEAR_FLAG                   /* QT_COMPARE_FLAG | QT_OVERFLOW_FLAG | QT_INPUT_EDGE_FLAG | QT_VAL_FLAG */
#define QT_CLEAR_COMPARE_FLAG           /* QT_COMPARE1_FLAG | QT_COMPARE2_FLAG */
#define QT_READ_FLAG                    /* QT_COMPARE_FLAG | QT_OVERFLOW_FLAG | QT_INPUT_EDGE_FLAG | QT_VAL_FLAG, returns 0x0000 - bits are cleared, or returns 0x8000 (Timer Compare Flag is set) | 0x2000 (Timer Overflow Flag is set) | 0x0800 (Input Edge Flag is set) | 0x0008 (VAL Flag is set) */
#define QT_READ_COMPARE_FLAG            /* QT_COMPARE1_FLAG | QT_COMPARE2_FLAG  returns 0x0000 - bits are cleared, or returns 0x0020 (Timer Compare 2 Flag is set) | 0x0010 (Timer Compare 1 Flag is set) */
#define QT_INT_ENABLE                   /* QT_COMPARE_INT | QT_COMPARE1_INT | QT_COMPARE2_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT */
#define QT_INT_DISABLE                  /* QT_COMPARE_INT | QT_COMPARE1_INT | QT_COMPARE2_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT */
#define QT_SET_INPUT_POLARITY           /* QT_NORMAL_POLARITY / QT_INVERTED_POLARITY */
#define QT_READ_EXT_INPUT_PIN           /* NULL, returns 0x0000 (input pin is 0) or 0x0100 (input pin is 1) */
#define QT_SET_CAPTURE_MODE             /* QT_CAPTURE_DISABLED / QT_RISING_EDGE / QT_FALLING_EDGE / QT_BOTH_EDGES */
#define QT_MASTER_MODE                  /* QT_ENABLE / QT_DISABLE */
#define QT_EXT_OFLAG_FORCE              /* QT_ENABLE / QT_DISABLE */
#define QT_FORCE_OFLAG                  /* QT_ONE / QT_ZERO0 - (force OFLAG to 1) / (force OFLAG to 0),  use this command only if timer is disabled */
#define QT_SET_OUTPUT_POLARITY          /* QT_NORMAL_POLARITY / QT_INVERTED_POLARITY */
#define QT_OUTPUT_ON_EXT_PIN            /* QT_ENABLE / QT_DISABLE */

#define QT_SET_LOAD_CONTROL1            /* QT_NEVER_PRELOAD / QT_LOAD_ON_CMP1 / QT_LOAD_ON_CMP2 */
#define QT_SET_LOAD_CONTROL2            /* QT_NEVER_PRELOAD / QT_LOAD_ON_CMP1 / QT_LOAD_ON_CMP2 */

#define QT_WRITE_CONTROL_REG            /* UWord16, 16 bit value */
#define QT_WRITE_STATUS_CONTROL_REG     /* UWord16, 16 bit value */
#define QT_WRITE_CMP_STATUS_CONTROL_REG /* UWord16, 16 bit value */
#define QT_WRITE_COMPARE_REG1           /* UWord16, 16 bit value */
#define QT_WRITE_COMPARE_REG2           /* UWord16, 16 bit value */
#define QT_WRITE_PRELOAD_COMPARE_REG1   /* UWord16, 16 bit value */
#define QT_WRITE_PRELOAD_COMPARE_REG2   /* UWord16, 16 bit value */
#define QT_WRITE_LOAD_REG               /* UWord16, 16 bit value */
#define QT_WRITE_COUNTER_REG            /* UWord16, 16 bit value */

#define QT_READ_CONTROL_REG             /* NULL, returns UWord16 */
#define QT_READ_STATUS_CONTROL_REG      /* NULL, returns UWord16 */
#define QT_READ_CMP_STATUS_CONTROL_REG  /* NULL, returns UWord16 */
#define QT_READ_COMPARE_REG1            /* NULL, returns UWord16 */
#define QT_READ_COMPARE_REG2            /* NULL, returns UWord16 */
#define QT_READ_LOAD_REG                /* NULL, returns UWord16 */
#define QT_READ_COUNTER_REG             /* NULL, returns UWord16 */
#define QT_READ_CAPTURE_REG             /* NULL, returns UWord16 */
#define QT_READ_HOLD_REG                /* NULL, returns UWord16 */

#if QT_VERSION >= 2
#define QT0_MASS_ENABLE             /* QTIMER_n0 only!, param: combination of QT_CHx, mass enable timer channels */
#define QT0_MASS_DISABLE            /* QTIMER_n0 only!, param: combination of QT_CHx, mass disable timer channels */
#define QT_READ_FILT_REG            /* NULL, returns value of fiter register */
#define QT_WRITE_FILT_REG           /* UWord16, writes filter register */
#endif


/*******************************************************************************
    QT constants used in the ioctl() as parameters
*******************************************************************************/
/* enable/disable */
#define QT_DISABLE                      0
#define QT_ENABLE                       1

/* Modes (used in QT_SET_COUNT_MODE command) */
#define QT_NO_OPERATION                 0x0000
#define QT_COUNT_RISING_EDGES_MODE      0x2000
#define QT_COUNT_BOTH_EDGES_MODE        0x4000
#define QT_GATED_COUNT_MODE             0x6000
#define QT_QUADRATURE_COUNT_MODE        0x8000
#define QT_SIGNED_COUNT_MODE            0xA000
#define QT_TRIGGERED_COUNT_MODE         0xC000
#define QT_CASCADE_COUNT_MODE           0xE000

 /* special modes */                           /* Mask */
#define QT_ONE_SHOT_MODE                0xC065 /* COUNTMODE|ONCE|LENGTH|OUTMODE */
#define QT_PULSE_OUTPUT_MODE            0x2047 /* COUNTMODE|ONCE|OUTMODE */
#define QT_FIXED_FREQ_PWM_MODE          0x2006 /* COUNTMODE|ONCE|LENGTH|OUTMODE */
#define QT_VARIABLE_FREQ_PWM_MODE       0x2024 /* COUNTMODE|ONCE|LENGTH|OUTMODE */


/* Primary Count Sources (used in QT_SET_PRIMARY_SOURCE command).
   Secondary Count Sources (used in QT_SET_SECONDARY_SOURCE command). */
   
#define QT_COUNTER0_INPUT               0   /*0x0000*/
#define QT_COUNTER1_INPUT               1   /*0x0200*/
#define QT_COUNTER2_INPUT               2   /*0x0400*/
#define QT_COUNTER3_INPUT               3   /*0x0600*/
#define QT_COUNTER0_OUTPUT              4   /*0x0800*/
#define QT_COUNTER1_OUTPUT              5   /*0x0A00*/
#define QT_COUNTER2_OUTPUT              6   /*0x0C00*/
#define QT_COUNTER3_OUTPUT              7   /*0x0E00*/
#define QT_IPBUS_DIV_1                  8   /*0x1000*/
#define QT_IPBUS_DIV_2                  9   /*0x1200*/
#define QT_IPBUS_DIV_4                  10  /*0x1400*/
#define QT_IPBUS_DIV_8                  11  /*0x1600*/
#define QT_IPBUS_DIV_16                 12  /*0x1800*/
#define QT_IPBUS_DIV_32                 13  /*0x1A00*/
#define QT_IPBUS_DIV_64                 14  /*0x1C00*/
#define QT_IPBUS_DIV_128                15  /*0x1E00*/

/* END OF LIFE: deprecated names of parameters, to be removed in future versions */
#define QT_PRESCALER_DIV_1              8   /*0x1000*/
#define QT_PRESCALER_DIV_2              9   /*0x1200*/
#define QT_PRESCALER_DIV_4              10  /*0x1400*/
#define QT_PRESCALER_DIV_8              11  /*0x1600*/
#define QT_PRESCALER_DIV_16             12  /*0x1800*/
#define QT_PRESCALER_DIV_32             13  /*0x1A00*/
#define QT_PRESCALER_DIV_64             14  /*0x1C00*/
#define QT_PRESCALER_DIV_128            15  /*0x1E00*/

/* Continuous or one shot counting modes (used in QT_SET_COUNT_ONCE command) */
#define QT_COUNT_REPEATEDLY             0
#define QT_UNTIL_COMPARE_AND_STOP       1

/* Length (used in QT_SET_COUNT_LENGTH command) */
#define QT_ROLL_OVER                    0
#define QT_UNTIL_COMPARE_AND_REINIT     1

/* Count Directions (used in QT_SET_COUNT_DIRECTION command) */
#define QT_COUNT_UP                     0
#define QT_COUNT_DOWN                   1

/* Output Modes (used in QT_SET_OUTPUT_MODE command) */
#define QT_SET_WHILE_ACTIVE             0
#define QT_CLEAR_ON_COMPARE             1
#define QT_SET_ON_COMPARE               2
#define QT_TOGGLE_ON_COMPARE            3
#define QT_TOGGLE_USING_ALT_COMPARE     4
#define QT_CLEAR_ON_SECONDARY           5
#define QT_CLEAR_ON_COUNTER_ROLLOVER    6
#define QT_GATED_CLOCK_WHILE_ACTIVE     7
#define QT_ASSERT_ON_GATED_CLOCK        7 /* deprecated, do NOT use */

/* Quad Timer Interrupts Flags and Interrupt Enable bits */
#define QT_COMPARE_FLAG                 QT_SCR_TCF
#define QT_OVERFLOW_FLAG                QT_SCR_TOF
#define QT_INPUT_EDGE_FLAG              QT_SCR_IEF
#define QT_VAL_FLAG                     QT_SCR_VAL
#define QT_COMPARE1_FLAG                QT_COMSCR_TCF1
#define QT_COMPARE2_FLAG                QT_COMSCR_TCF2

#define QT_COMPARE_INT                  QT_SCR_TCFIE
#define QT_OVERFLOW_INT                 QT_SCR_TOFIE
#define QT_INPUT_EDGE_INT               QT_SCR_IEFIE
#define QT_COMPARE1_INT                 QT_COMSCR_TCF1EN
#define QT_COMPARE2_INT                 QT_COMSCR_TCF2EN

/* Input and Output polarity select (used in QT_INPUT_POLARITY command) */
#define QT_NORMAL_POLARITY              0
#define QT_INVERTED_POLARITY            1

/* Input Capture Mode (used in QT_SET_CAPTURE_MODE command) */
#define QT_CAPTURE_DISABLED             0   /*0x0000*/
#define QT_RISING_EDGE                  1   /*0x0040*/
#define QT_FALLING_EDGE                 2   /*0x0080*/
#define QT_BOTH_EDGES                   3   /*0x00C0*/

/* Compare Preload Mode */
#define QT_NEVER_PRELOAD                0
#define QT_LOAD_ON_CMP1                 1
#define QT_LOAD_ON_CMP2                 2

/* forced value */
#define QT_ONE                          1
#define QT_ZERO                         0

/* mass enable/disable timer channels */
#define QT_CH0      QT_ENBL_CH0
#define QT_CH1      QT_ENBL_CH1
#define QT_CH2      QT_ENBL_CH2
#define QT_CH3      QT_ENBL_CH3


/*******************************************************************************
    Register and bit names
*******************************************************************************/

/* CONTROL REGISTER */
#define QT_CTRL_COUNTMODE_MASK          0xe000
#define QT_CTRL_PRIMSOURCE_MASK         0x1e00
#define QT_CTRL_SECSOURCE_MASK          0x0180
#define QT_CTRL_ONCE                    0x0040
#define QT_CTRL_LENGTH                  0x0020
#define QT_CTRL_DIR                     0x0010
#define QT_CTRL_CO_INIT                 0x0008
#define QT_CTRL_OUTMODE_MASK            0x0007

/* STATUS CONTROL REGISTER */
#define QT_SCR_TCF                      0x8000
#define QT_SCR_TCFIE                    0x4000
#define QT_SCR_TOF                      0x2000
#define QT_SCR_TOFIE                    0x1000
#define QT_SCR_IEF                      0x0800
#define QT_SCR_IEFIE                    0x0400
#define QT_SCR_IPS                      0x0200
#define QT_SCR_INPUT                    0x0100
#define QT_SCR_CAPMODE_MASK             0x00c0
#define QT_SCR_MSTR                     0x0020
#define QT_SCR_EEOF                     0x0010
#define QT_SCR_VAL                      0x0008
#define QT_SCR_FORCE                    0x0004
#define QT_SCR_OPS                      0x0002
#define QT_SCR_OEN                      0x0001

/* COMPARATOR STATUS CONTROL REGISTER */
#define QT_COMSCR_CL1_MASK              0x0003
#define QT_COMSCR_CL2_MASK              0x000c
#define QT_COMSCR_TCF2EN                0x0080
#define QT_COMSCR_TCF1EN                0x0040
#define QT_COMSCR_TCF2                  0x0020
#define QT_COMSCR_TCF1                  0x0010

#if QT_VERSION >= 2
#define QT_ENBL_CH0 0x0001
#define QT_ENBL_CH1 0x0002
#define QT_ENBL_CH2 0x0004
#define QT_ENBL_CH3 0x0008
#endif


/*******************************************************************************
    Bit names of older SDK version, maintained here for backward compatibility.
*******************************************************************************/

/* Do not use for new development ! */
#define QT_COUNT_ONCE_BIT               QT_CTRL_ONCE
#define QT_COUNT_LENGTH_BIT             QT_CTRL_LENGTH
#define QT_COUNT_DIRECTION_BIT          QT_CTRL_DIR
#define QT_CO_INIT_BIT                  QT_CTRL_CO_INIT
#define QT_INPUT_POLARITY_BIT           QT_SCR_IPS
#define QT_EXT_INPUT_PIN                QT_SCR_INPUT
#define QT_MASTER_MODE_BIT              QT_SCR_MSTR
#define QT_ENABLE_OFLAG_FORCE_BIT       QT_SCR_EEOF
#define QT_OFLAG_VALUE_BIT              QT_SCR_VAL
#define QT_FORCE_OFLAG_BIT              QT_SCR_FORCE
#define QT_OUTPUT_POLARITY_BIT          QT_SCR_OPS
#define QT_OUTPUT_ENABLE_BIT            QT_SCR_OEN

/*******************************************************************************
    Implementations of Quad Timer ioctl() commands
*******************************************************************************/

void qtInit(arch_sTimerChannel *pTimerBase);
#define ioctlQT_INIT(pTimerBase, param) qtInit(pTimerBase)

/* Control Register */
#define ioctlQT_SET_COUNT_MODE(pTimerBase, param) \
  if((param) == QT_PULSE_OUTPUT_MODE) \
  { periphBitGrpSet(QT_CTRL_COUNTMODE_MASK | QT_CTRL_ONCE | QT_CTRL_OUTMODE_MASK, param, &((pTimerBase)->tmrctrl)); } \
  else if((param) == QT_FIXED_FREQ_PWM_MODE || (param) == QT_VARIABLE_FREQ_PWM_MODE || (param) == QT_ONE_SHOT_MODE) \
  { periphBitGrpSet(QT_CTRL_COUNTMODE_MASK | QT_CTRL_ONCE | QT_CTRL_LENGTH | QT_CTRL_OUTMODE_MASK, param, &((pTimerBase)->tmrctrl)); } \
  else periphBitGrpSet(QT_CTRL_COUNTMODE_MASK, param, &((pTimerBase)->tmrctrl))

#define ioctlQT_SET_PRIMARY_SOURCE(pTimerBase, param) \
  periphBitGrpSet(QT_CTRL_PRIMSOURCE_MASK, (param) << 9, &((pTimerBase)->tmrctrl))

#define ioctlQT_SET_SECONDARY_SOURCE(pTimerBase, param) \
  periphBitGrpSet(QT_CTRL_SECSOURCE_MASK, (param) << 7, &((pTimerBase)->tmrctrl))

#define ioctlQT_SET_COUNT_ONCE(pTimerBase, param) \
  if (param) periphBitSet(QT_CTRL_ONCE, &((pTimerBase)->tmrctrl)); \
  else periphBitClear(QT_CTRL_ONCE, &((pTimerBase)->tmrctrl))
                
#define ioctlQT_SET_COUNT_LENGTH(pTimerBase, param) \
  if (param) periphBitSet(QT_CTRL_LENGTH, &((pTimerBase)->tmrctrl)); \
  else periphBitClear(QT_CTRL_LENGTH, &((pTimerBase)->tmrctrl))

#define ioctlQT_SET_COUNT_DIRECTION(pTimerBase, param) \
  if (param) periphBitSet(QT_CTRL_DIR, &((pTimerBase)->tmrctrl)); \
  else periphBitClear(QT_CTRL_DIR, &((pTimerBase)->tmrctrl))

#define ioctlQT_CO_CHANNEL_INIT(pTimerBase, param) \
  if (param) periphBitSet(QT_CTRL_CO_INIT, &((pTimerBase)->tmrctrl)); \
  else periphBitClear(QT_CTRL_CO_INIT, &((pTimerBase)->tmrctrl))

#define ioctlQT_SET_OUTPUT_MODE(pTimerBase, param) \
  periphBitGrpSet(QT_CTRL_OUTMODE_MASK, param, &((pTimerBase)->tmrctrl))

#define ioctlQT_CLEAR_FLAG(pTimerBase, param) \
  periphBitClear(param, &((pTimerBase)->tmrscr))

#define ioctlQT_CLEAR_COMPARE_FLAG(pTimerBase, param) \
  periphBitClear(param, &((pTimerBase)->tmrcomscr))

#define ioctlQT_READ_FLAG(pTimerBase, param) \
  periphBitTest(param, &((pTimerBase)->tmrscr))

#define ioctlQT_READ_COMPARE_FLAG(pTimerBase, param) \
  periphBitTest(param, &((pTimerBase)->tmrcomscr))

#define ioctlQT_INT_ENABLE(pTimerBase, param) \
  { \
    if( ((param) & ~(QT_COMPARE1_INT | QT_COMPARE2_INT)) ) \
         periphBitSet(((param) & ~(QT_COMPARE1_INT | QT_COMPARE2_INT)), &((pTimerBase)->tmrscr)); \
    if( ((param) & ~(QT_COMPARE_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT)) ) \
         periphBitSet(((param) & ~(QT_COMPARE_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT)), &((pTimerBase)->tmrcomscr)); \
  }

#define ioctlQT_INT_DISABLE(pTimerBase, param) \
  { \
    if( ((param) & ~(QT_COMPARE1_INT | QT_COMPARE2_INT)) ) \
         periphBitClear(((param) & ~(QT_COMPARE1_INT | QT_COMPARE2_INT)), &((pTimerBase)->tmrscr)); \
    if( ((param) & ~(QT_COMPARE_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT)) ) \
         periphBitClear(((param) & ~(QT_COMPARE_INT | QT_OVERFLOW_INT | QT_INPUT_EDGE_INT)), &((pTimerBase)->tmrcomscr)); \
  }

#define ioctlQT_SET_INPUT_POLARITY(pTimerBase, param) \
  if (param) periphBitSet(QT_SCR_IPS, &((pTimerBase)->tmrscr)); \
  else periphBitClear(QT_SCR_IPS, &((pTimerBase)->tmrscr))

#define ioctlQT_READ_EXT_INPUT_PIN(pTimerBase, param) \
  periphBitTest(QT_SCR_INPUT, &((pTimerBase)->tmrscr))

#define ioctlQT_SET_CAPTURE_MODE(pTimerBase, param) \
  periphBitGrpSet(QT_SCR_CAPMODE_MASK, (param) << 6, &((pTimerBase)->tmrscr))

#define ioctlQT_MASTER_MODE(pTimerBase, param) \
  if (param) periphBitSet(QT_SCR_MSTR, &((pTimerBase)->tmrscr)); \
  else periphBitClear(QT_SCR_MSTR, &((pTimerBase)->tmrscr))

#define ioctlQT_EXT_OFLAG_FORCE(pTimerBase, param) \
  if (param) periphBitSet(QT_SCR_EEOF, &((pTimerBase)->tmrscr)); \
  else periphBitClear(QT_SCR_EEOF, &((pTimerBase)->tmrscr))

#define ioctlQT_FORCE_OFLAG(pTimerBase, param) \
  if(param) periphBitSet(QT_SCR_VAL|QT_SCR_FORCE, &((pTimerBase)->tmrscr)); \
  else { periphBitClear(QT_SCR_VAL, &((pTimerBase)->tmrscr)); \
         periphBitSet(QT_SCR_FORCE, &((pTimerBase)->tmrscr)); }

/* alias for QT_FORCE_OFLAG */
#define ioctlQT_SET_OUTPUT_SIGNAL(pTimerBase, param) \
  { if(param) periphBitSet(QT_SCR_VAL, &((pTimerBase)->tmrscr)); \
    else periphBitClear(QT_SCR_VAL, &((pTimerBase)->tmrscr)); \
    periphBitSet(QT_SCR_FORCE, &((pTimerBase)->tmrscr)); }

#define ioctlQT_SET_OUTPUT_POLARITY(pTimerBase, param) \
  if (param) periphBitSet(QT_SCR_OPS, &((pTimerBase)->tmrscr)); \
  else periphBitClear(QT_SCR_OPS, &((pTimerBase)->tmrscr))

#define ioctlQT_OUTPUT_ON_EXT_PIN(pTimerBase, param) \
  if (param) periphBitSet(QT_SCR_OEN, &((pTimerBase)->tmrscr)); \
  else periphBitClear(QT_SCR_OEN, &((pTimerBase)->tmrscr))

/* Comparator Status and Control Register */
#define ioctlQT_SET_LOAD_CONTROL1(pTimerBase, param) \
  periphBitGrpSet(QT_COMSCR_CL1_MASK, param, &((pTimerBase)->tmrcomscr))

#define ioctlQT_SET_LOAD_CONTROL2(pTimerBase, param) \
  periphBitGrpSet(QT_COMSCR_CL2_MASK, (param) << 2, &((pTimerBase)->tmrcomscr))

/* Reading(writing) from(to) registers */
#define ioctlQT_WRITE_CONTROL_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrctrl))

#define ioctlQT_WRITE_STATUS_CONTROL_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrscr))

#define ioctlQT_WRITE_CMP_STATUS_CONTROL_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcomscr))

#define ioctlQT_WRITE_COMPARE_REG1(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcmp1))

#define ioctlQT_WRITE_COMPARE_REG2(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcmp2))

#define ioctlQT_WRITE_PRELOAD_COMPARE_REG1(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcmpld1))

#define ioctlQT_WRITE_PRELOAD_COMPARE_REG2(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcmpld2))

#define ioctlQT_WRITE_LOAD_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrload))

#define ioctlQT_WRITE_COUNTER_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->tmrcntr))

#define ioctlQT_READ_CONTROL_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrctrl))

#define ioctlQT_READ_STATUS_CONTROL_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrscr))

#define ioctlQT_READ_CMP_STATUS_CONTROL_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrcomscr))

#define ioctlQT_READ_COMPARE_REG1(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrcmp1))

#define ioctlQT_READ_COMPARE_REG2(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrcmp2))

#define ioctlQT_READ_LOAD_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrload))

#define ioctlQT_READ_COUNTER_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrcntr))

#define ioctlQT_READ_CAPTURE_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrcap))

#define ioctlQT_READ_HOLD_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->tmrhold))

#if QT_VERSION >= 2
/* mass enable timer channels */
#define ioctlQT0_MASS_ENABLE(pTimerBase, param) \
  periphBitSet(param, &((pTimerBase)->enbl))

/* mass disable timer channels */
#define ioctlQT0_MASS_DISABLE(pTimerBase, param) \
  periphBitClear(param, &((pTimerBase)->enbl))

/* returns value of fiter register */
#define ioctlQT_READ_FILT_REG(pTimerBase, param) \
  periphMemRead(&((pTimerBase)->filt))   

/* writes filter register */
#define ioctlQT_WRITE_FILT_REG(pTimerBase, param) \
  periphMemWrite(param, &((pTimerBase)->filt))

#endif /* QT_VERSION 2 */


#ifdef __cplusplus
}
#endif

#endif
