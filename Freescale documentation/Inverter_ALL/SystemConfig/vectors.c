/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: vectors_803x.c$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.3.0$
*
* Description: 56F802x/3x Interrupt Vector Table (63 interrupts, INTC_VERSION_4)
*
*****************************************************************************/

#include "qs.h"

#ifndef INTC_VERSION_4
#error Bad INTC version defined in arch.h, or wrong vectors.c used
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* reference to startup code */

void Start(void);

/* for each interrupt vector, we (re)define HERE its correct prototype -
   - So, in the case the user defines BAD prototype himself e.g. in appconfig.h,
     the compiler warns him here about function prototype redefinition */
     
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

/* unhandled exception "handler" */

static asm void unhandled_interrupt(void)
{
	/* retrieve VAB field from ICTL register */
	move.l  #ArchIO.Intc.ictl,R0
	move.w  X:(R0),X0
	asrr.w  #6,X0
	bfclr   #0xff80,X0

	/* Interrupt number is stored in X0 register */	
	debughlt
	
	/* Loop forever */
	bra *+0
}

/* illegal instruction interrupt ($04) */

#ifndef INT_VECTOR_ADDR_2
#define INT_VECTOR_ADDR_2 ill_op

static asm void ill_op(void)
{
	debughlt	
	nop
	rti
}

#endif

/* hardware stack overflow interrupt ($08) */

#ifndef INT_VECTOR_ADDR_4
#define INT_VECTOR_ADDR_4 hws_overflow

static asm void hws_overflow(void)
{
	debughlt	
	nop
	rti
}

#endif
	
/* misaligned long word access interrupt ($0A) */

#ifndef INT_VECTOR_ADDR_5
#define INT_VECTOR_ADDR_5 misalign

static asm void misalign(void)
{
	debughlt	
	nop
	rti
}

#endif

/* PLL lost of lock interrupt ($20) */

#ifndef INT_VECTOR_ADDR_16
#define INT_VECTOR_ADDR_16 pll_losslock

static asm void pll_losslock(void)
{
	debughlt
	nop
	rti
}

#endif

/***************************
 *
 * Interrupt vectors table
 *
 ***************************/

#pragma define_section interrupt_vectors "interrupt_vectors.text"  RX
#pragma section interrupt_vectors begin

static asm void int_vec(void)
{
	jmp >Start;           	/* Reset */
	
#ifdef INT_VECTOR_ADDR_1	
	jmp >INT_VECTOR_ADDR_1	/* COP Reset */							
#else
	jmp >Start;		
#endif
	
#ifdef INT_VECTOR_ADDR_2	/* 0x04: Illegal Instruction */
	jsr >INT_VECTOR_ADDR_2
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_3	/* 0x06: SW Interrupt 3 */
	jsr >INT_VECTOR_ADDR_3
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_4	/* 0x08: HW Stack Overflow */
	jsr >INT_VECTOR_ADDR_4
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_5	/* 0x0A: Misaligned Long Word Access */
	jsr >INT_VECTOR_ADDR_5
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_6	/* 0x0C: OnCE Step Counter */
	jsr >INT_VECTOR_ADDR_6
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_7	/* 0x0E: OnCE Breakpoint Unit */
	jsr >INT_VECTOR_ADDR_7
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_8	/* 0x10: OnCE Trace Buffer */
	jsr >INT_VECTOR_ADDR_8
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_9	/* 0x12: OnCE Transmit Register Empty */
	jsr >INT_VECTOR_ADDR_9
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_10	/* 0x14: OnCE Receive Register Full */
	jsr >INT_VECTOR_ADDR_10
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_11	/* 0x16: SW Interrupt 2 */
	jsr >INT_VECTOR_ADDR_11
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_12	/* 0x18: SW Interrupt 1 */
	jsr >INT_VECTOR_ADDR_12
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_13	/* 0x1A: SW Interrupt 0 */
	jsr >INT_VECTOR_ADDR_13
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_14	/* 0x1C: Reserved */
	jsr >INT_VECTOR_ADDR_14
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_15	/* 0x1E: LVI Low Voltage Detector */
	jsr >INT_VECTOR_ADDR_15
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_16	/* 0x20: PLL */
	jsr >INT_VECTOR_ADDR_16
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_17	/* 0x22: HFM Error */
	jsr >INT_VECTOR_ADDR_17
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_18	/* 0x24: HFM Command Complete */
	jsr >INT_VECTOR_ADDR_18
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_19	/* 0x26: HFM Command, Buffers Empty */
	jsr >INT_VECTOR_ADDR_19
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_20	/* 0x28: MSCAN Error */
	jsr >INT_VECTOR_ADDR_20
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_21	/* 0x2A: MSCAN Receive */
	jsr >INT_VECTOR_ADDR_21
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_22	/* 0x2C: MSCAN Transmit */
	jsr >INT_VECTOR_ADDR_22
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_23	/* 0x2E: MSCAN Wake-up */
	jsr >INT_VECTOR_ADDR_23
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_24	/* 0x30: GPIO D */
	jsr >INT_VECTOR_ADDR_24
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_25	/* 0x32: GPIO C */
	jsr >INT_VECTOR_ADDR_25
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_26	/* 0x34: GPIO B */
	jsr >INT_VECTOR_ADDR_26
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_27	/* 0x36: GPIO A */
	jsr >INT_VECTOR_ADDR_27
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_28	/* 0x38: SPI 0 Receiver Full */
	jsr >INT_VECTOR_ADDR_28
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_29	/* 0x3A: SPI 0 Transmitter Empty */
	jsr >INT_VECTOR_ADDR_29
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_30	/* 0x3C: SPI 1 Receiver Full */
	jsr >INT_VECTOR_ADDR_30
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_31	/* 0x3E: SPI 1 Transmitter Empty */
	jsr >INT_VECTOR_ADDR_31
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_32	/* 0x40: SCI 0 Transmitter Empty */
	jsr >INT_VECTOR_ADDR_32
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_33	/* 0x42: SCI 0 Transmitter Idle */
	jsr >INT_VECTOR_ADDR_33
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_34	/* 0x44: SCI 0 Receiver Error */
	jsr >INT_VECTOR_ADDR_34
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_35	/* 0x46: SCI 0 Receiver Full */
	jsr >INT_VECTOR_ADDR_35
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_36	/* 0x48: SCI 1 Transmitter Empty */
	jsr >INT_VECTOR_ADDR_36
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_37	/* 0x4a: SCI 1 Transmitter Idle */
	jsr >INT_VECTOR_ADDR_37
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_38	/* 0x4c: SCI 1 Receiver Error */
	jsr >INT_VECTOR_ADDR_38
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_39	/* 0x4e: SCI 1 Receiver Full */
	jsr >INT_VECTOR_ADDR_39
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_40	/* 0x50: I2C Error */
	jsr >INT_VECTOR_ADDR_40
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_41	/* 0x52: I2C General */
	jsr >INT_VECTOR_ADDR_41
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_42	/* 0x54: I2C Receive */
	jsr >INT_VECTOR_ADDR_42
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_43	/* 0x56: I2C Transmit */
	jsr >INT_VECTOR_ADDR_43
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_44	/* 0x58: I2C Status */
	jsr >INT_VECTOR_ADDR_44
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_45	/* 0x5a: Timer A Channel 0 */
	jsr >INT_VECTOR_ADDR_45
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_46	/* 0x5c: Timer A Channel 1 */
	jsr >INT_VECTOR_ADDR_46
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_47	/* 0x5e: Timer A Channel 2 */
	jsr >INT_VECTOR_ADDR_47	
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_48	/* 0x60: Timer A Channel 3 */
	jsr >INT_VECTOR_ADDR_48
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_49	/* 0x62: Timer B Channel 0 */
	jsr >INT_VECTOR_ADDR_49
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_50	/* 0x64: Timer B Channel 1 */
	jsr >INT_VECTOR_ADDR_50
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_51	/* 0x66: Timer B Channel 2 */
	jsr >INT_VECTOR_ADDR_51
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_52	/* 0x68: Timer B Channel 3 */
	jsr >INT_VECTOR_ADDR_52
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_53	/* 0x6a: Analog Comparator A */
	jsr >INT_VECTOR_ADDR_53
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_54	/* 0x6c: Analog Comparator B */
	jsr >INT_VECTOR_ADDR_54
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_55	/* 0x6e: Interval Timer PIT 0 */
	jsr >INT_VECTOR_ADDR_55
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_56	/* 0x70: Interval Timer PIT 1 */
	jsr >INT_VECTOR_ADDR_56
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_57	/* 0x72: Interval Timer PIT 2 */
	jsr >INT_VECTOR_ADDR_57
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_58	/* 0x74: ADC ADA Conversion Complete */
	jsr >INT_VECTOR_ADDR_58
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_59	/* 0x76: ADC ADB Conversion Complete */
	jsr >INT_VECTOR_ADDR_59
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_60	/* 0x78: ADC Zero Crossing or Limit Error */
	jsr >INT_VECTOR_ADDR_60
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_61	/* 0x7a: PWM Reload */
	jsr >INT_VECTOR_ADDR_61
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_62	/* 0x7c: PWM Fault */
	jsr >INT_VECTOR_ADDR_62
#else
	jsr >unhandled_interrupt
#endif
#ifdef INT_VECTOR_ADDR_63	/* 0x7e: SW Interrupt LP */
	jsr >INT_VECTOR_ADDR_63
#else
	jsr >unhandled_interrupt
#endif
}

#pragma section interrupt_vectors end

#ifdef __cplusplus
}
#endif

