/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: arch.h$
*
* $Date:      Mar-21-2007$
*
* $Version:   2.3.4.0$
*
* Description: Peripheral space map of the MC56F8023 device
*
*****************************************************************************/

#ifndef __ARCH_H
#define __ARCH_H

#ifndef __TYPES_H
#error types.h must be included before arch.h
#endif

/* System Integration Module */

#define SIM_VERSION 4
#define SIM_VERSION_4

typedef volatile struct 
{
    ARCH_REG4(UWord16, sim_control, sim_ctrl, control, ControlReg);
    ARCH_REG4(UWord16, sim_rststs,  sim_rstat, rststs, StatusReg);
    ARCH_REG3(UWord16, sim_scr0,    sim_swc0, scr0);
    ARCH_REG3(UWord16, sim_scr1,    sim_swc1, scr1);
    ARCH_REG3(UWord16, sim_scr2,    sim_swc2, scr2);
    ARCH_REG3(UWord16, sim_scr3,    sim_swc3, scr3);
    ARCH_REG3(UWord16, sim_msh_id,  sim_mshid, msh_id);
    ARCH_REG3(UWord16, sim_lsh_id,  sim_lshid, lsh_id);
    ARCH_REG3(UWord16, sim_power,   sim_pwr, power);
    ARCH_REG1(UWord16, reserved1);
    ARCH_REG3(UWord16, sim_clkosr,  sim_clkout, clkosr);
    ARCH_REG1(UWord16, sim_pcr);
    ARCH_REG1(UWord16, sim_pce0);
    ARCH_REG1(UWord16, sim_pce1);
    ARCH_REG1(UWord16, sim_sd0);
    ARCH_REG1(UWord16, sim_sd1);
    ARCH_REG3(UWord16, sim_isalh,   sim_iosahi, isalh);
    ARCH_REG3(UWord16, sim_isall,   sim_iosalo, isall);
    ARCH_REG1(UWord16, sim_prot);
    ARCH_REG1(UWord16, sim_gpsa0);
    ARCH_REG1(UWord16, sim_gpsa1);
    ARCH_REG1(UWord16, sim_gpsb0);
    ARCH_REG1(UWord16, sim_gpsb1);
    ARCH_REG1(UWord16, sim_gpscd);
    ARCH_REG1(UWord16, sim_ips0);
    ARCH_REG1(UWord16, sim_ips1);
    ARCH_REG1(UWord16, sim_ips2);
    ARCH_REG1(UWord16, reserved2[5]);

} arch_sSIM;

/* Quad Timer Module */

#define QT_VERSION 2
#define QT_VERSION_2

typedef volatile struct
{
    ARCH_REG4(UWord16, tmrcmp1,   comp1, cmp1, CompareReg1);
    ARCH_REG4(UWord16, tmrcmp2,   comp2, cmp2, CompareReg2);
    ARCH_REG4(UWord16, tmrcap,    capt, cap, CaptureReg);
    ARCH_REG3(UWord16, tmrload,   load, LoadReg);
    ARCH_REG3(UWord16, tmrhold,   hold, HoldReg);
    ARCH_REG3(UWord16, tmrcntr,   cntr, CounterReg);
    ARCH_REG3(UWord16, tmrctrl,   ctrl, ControlReg);
    ARCH_REG4(UWord16, tmrscr,    sctrl, scr, StatusControlReg);
    ARCH_REG2(UWord16, tmrcmpld1, cmpld1);
    ARCH_REG2(UWord16, tmrcmpld2, cmpld2);
    ARCH_REG3(UWord16, tmrcomscr, csctrl, comscr);
    ARCH_REG1(UWord16, filt);
    ARCH_REG1(UWord16, reserved[3]);
    ARCH_REG1(UWord16, enbl);

} arch_sTimerChannel;

typedef volatile struct
{
    ARCH_REG2(arch_sTimerChannel, ch0, Channel0);
    ARCH_REG2(arch_sTimerChannel, ch1, Channel1);
    ARCH_REG2(arch_sTimerChannel, ch2, Channel2);
    ARCH_REG2(arch_sTimerChannel, ch3, Channel3);

} arch_sTimer;

/* PWM Module */

#define PWM_VERSION 3
#define PWM_VERSION_3
#define PWM_HAS_FAULTS  0xf
#define PWM_HAS_IS_PINS 0x0

typedef volatile struct
{
    ARCH_REG3(UWord16, pmctl,     ctrl, ControlReg);
    ARCH_REG3(UWord16, pmfctl,    fctrl, FaultControlReg);
    ARCH_REG3(UWord16, pmfsa,     fltack, FaultStatusReg);
    ARCH_REG3(UWord16, pmout,     out, OutputControlReg);
    ARCH_REG3(UWord16, pmcnt,     cntr, CounterReg);
    ARCH_REG3(UWord16, pwmcm,     cmod, CounterModuloReg);
    ARCH_REG3(Word16,  pwmval[6], val[6], ValueReg[6]);
    ARCH_REG3(UWord16, pmdeadtm0, dtim0, DeadtimeReg0); /* VERSION_2-specific */
    ARCH_REG3(UWord16, pmdeadtm1, dtim1, DeadtimeReg1); /* VERSION_2-specific */
    ARCH_REG3(UWord16, pmdismap1, dmap0, DisableMapping1Reg);
    ARCH_REG3(UWord16, pmdismap2, dmap1, DisableMapping2Reg);
    ARCH_REG3(UWord16, pmcfg,     cnfg, ConfigReg);
    ARCH_REG3(UWord16, pmccr,     cctrl, ChannelControlReg);
    ARCH_REG3(UWord16, pmport,    port, PortReg);
    ARCH_REG2(UWord16, pmiccr,    icctrl);
    ARCH_REG2(UWord16, pmsrc,     sctrl);  /* VERSION_2-specific */
    ARCH_REG1(UWord16, sync);   /* VERSION_3-specific */
    ARCH_REG1(UWord16, ffilt0); /* VERSION_3-specific */
    ARCH_REG1(UWord16, ffilt1); /* VERSION_3-specific */
    ARCH_REG1(UWord16, ffilt2); /* VERSION_3-specific */
    ARCH_REG1(UWord16, ffilt3); /* VERSION_3-specific */
    ARCH_REG1(UWord16, reserved[6]);

} arch_sPWM;

/* Interrupt Controller */

#define INTC_VERSION 4
#define INTC_VERSION_4
#define INTC_HAS_IRQPINS 0

typedef volatile struct
{
    ARCH_REG2(UWord16, ipr[7],     PriorityReg[7]);
    ARCH_REG2(UWord16, vba,        VecBaseReg);
    ARCH_REG2(UWord16, fim0,       FastInt0MatchReg);
    ARCH_REG2(UWord16, fival0,     FastInt0AddrLReg);
    ARCH_REG2(UWord16, fivah0,     FastInt0AddrHReg);
    ARCH_REG2(UWord16, fim1,       FastInt1MatchReg);
    ARCH_REG2(UWord16, fival1,     FastInt1AddrLReg);
    ARCH_REG2(UWord16, fivah1,     FastInt1AddrHReg);
    ARCH_REG2(UWord16, irqp[4],    IntPendingReg[4]);
    ARCH_REG1(UWord16, reserved1[4]);
    ARCH_REG2(UWord16, ictl,       ControlReg);
    ARCH_REG1(UWord16, reserved2[9]);

} arch_sIntc;

/* A/D Converter */

#define ADC_VERSION 3
#define ADC_VERSION_3

typedef volatile struct
{
    ARCH_REG4(UWord16, adctl1,    ctrl1, adcr1, Control1Reg);
    ARCH_REG4(UWord16, adctl2,    ctrl2, adcr2, Control2Reg);
    ARCH_REG3(UWord16, adzcc,     zxctrl, ZeroCrossControlReg);
    ARCH_REG3(UWord16, adlst1,    clist1, ChannelList1Reg);
    ARCH_REG3(UWord16, adlst2,    clist2, ChannelList2Reg);
    ARCH_REG3(UWord16, adlst3,    clist3, ChannelList3Reg);
    ARCH_REG3(UWord16, adlst4,    clist4, ChannelList4Reg);
    ARCH_REG3(UWord16, adsdis,    sdis, DisableReg);
    ARCH_REG3(UWord16, adstat,    stat, StatusReg);
    ARCH_REG1(UWord16, cnrdy);
    ARCH_REG3(UWord16, adlstat,   limstat, LimitReg);
    ARCH_REG3(UWord16, adzcstat,  zxstat, ZeroCrossStatusReg);
    ARCH_REG3(UWord16, adrslt[16], rslt[16], ResultReg[16]);
    ARCH_REG3(UWord16, adllmt[8], lolim[8], LowLimitReg[8]);
    ARCH_REG3(UWord16, adhlmt[8], hilim[8], HighLimitReg[8]);
    ARCH_REG3(UWord16, adofs[8],  offst[8], OffsetReg[8]);
    ARCH_REG2(UWord16, adcpower,  pwr);
    ARCH_REG2(UWord16, adc_cal,   cal);

    ARCH_REG1(UWord16, reserved[10]);

} arch_sADC;

/* Queued Serial Communication Interface */

#define SCI_VERSION 3
#define SCI_VERSION_3

typedef volatile struct
{
    ARCH_REG2(UWord16, scibr,    BaudRateReg);
    ARCH_REG2(UWord16, scicr,    ControlReg);
    ARCH_REG2(UWord16, scicr2,   ControlReg2); /* VERSION_2,3-specific */
    ARCH_REG2(UWord16, scisr,    StatusReg);
    ARCH_REG2(UWord16, scidr,    DataReg);
    ARCH_REG1(UWord16, reserved2[11]);

} arch_sSCI;

/* Serial Peripheral Interface */

#define SPI_VERSION 2
#define SPI_VERSION_2

typedef volatile struct
{
    ARCH_REG3(UWord16, spscr,    sctrl, ControlReg);
    ARCH_REG4(UWord16, spdsr,    dsctrl, spdscr, DataSizeReg);
    ARCH_REG3(UWord16, spdrr,    drcv, DataRxReg);
    ARCH_REG3(UWord16, spdtr,    dxmit, DataTxReg);
    ARCH_REG1(UWord16, fifo);
    ARCH_REG1(UWord16, delay);
    ARCH_REG1(UWord16, reserved[10]);

} arch_sSPI;

/* IIC Interface */

#define IIC_VERSION 2
#define IIC_VERSION_2

typedef volatile struct
{
    ARCH_REG1(UWord16, ctrl);
    ARCH_REG1(UWord16, reserved1);
    ARCH_REG1(UWord16, tar);
    ARCH_REG1(UWord16, reserved2);
    ARCH_REG1(UWord16, sar);
    ARCH_REG1(UWord16, reserved3[3]);
    
    ARCH_REG1(UWord16, data);
    ARCH_REG1(UWord16, reserved4);   
    ARCH_REG1(UWord16, sshcnt);
    ARCH_REG1(UWord16, reserved5);   
    ARCH_REG1(UWord16, sslcnt);
    ARCH_REG1(UWord16, reserved6);   
    ARCH_REG1(UWord16, fshcnt);
    ARCH_REG1(UWord16, reserved7);   
    
    ARCH_REG1(UWord16, fslcnt);
    ARCH_REG1(UWord16, reserved8[5]);   
    ARCH_REG1(UWord16, istat);
    ARCH_REG1(UWord16, reserved9);   
    
    ARCH_REG1(UWord16, ienbl);
    ARCH_REG1(UWord16, reserved10);   
    ARCH_REG1(UWord16, ristat);
    ARCH_REG1(UWord16, reserved11);   
    ARCH_REG1(UWord16, rxft);
    ARCH_REG1(UWord16, reserved12);   
    ARCH_REG1(UWord16, txft);
    ARCH_REG1(UWord16, reserved13);   
    
    ARCH_REG1(UWord16, clrint);
    ARCH_REG1(UWord16, reserved14);   
    ARCH_REG1(UWord16, clrrxund);
    ARCH_REG1(UWord16, reserved15);   
    ARCH_REG1(UWord16, clrrxovr);
    ARCH_REG1(UWord16, reserved16);   
    ARCH_REG1(UWord16, clrtxovr);
    ARCH_REG1(UWord16, reserved17);   
    
    ARCH_REG1(UWord16, clrrdreq);
    ARCH_REG1(UWord16, reserved18);   
    ARCH_REG1(UWord16, clrtxabrt);
    ARCH_REG1(UWord16, reserved19);   
    ARCH_REG1(UWord16, clrtxdone);
    ARCH_REG1(UWord16, reserved20);   
    ARCH_REG1(UWord16, clract);
    ARCH_REG1(UWord16, reserved21);   
    
    ARCH_REG1(UWord16, clrstpdet);
    ARCH_REG1(UWord16, reserved22);   
    ARCH_REG1(UWord16, clrstdet);
    ARCH_REG1(UWord16, reserved23);   
    ARCH_REG1(UWord16, clrgc);
    ARCH_REG1(UWord16, reserved24);   
    ARCH_REG1(UWord16, enbl);
    ARCH_REG1(UWord16, reserved25);   
    
    ARCH_REG1(UWord16, stat);
    ARCH_REG1(UWord16, reserved26);   
    ARCH_REG1(UWord16, txflr);
    ARCH_REG1(UWord16, reserved27);   
    ARCH_REG1(UWord16, rxflr);
    ARCH_REG1(UWord16, reserved28[3]);   
    
    ARCH_REG1(UWord16, txabrtsrc);
    ARCH_REG1(UWord16, reserved29[7]);   

    ARCH_REG1(UWord16, reserved30[0x38]);   
    
} arch_sIIC;

/* Watchdog Module */

#define COP_VERSION 2
#define COP_VERSION_2

typedef volatile struct
{
    ARCH_REG2(UWord16, copctl,   ControlReg);
    ARCH_REG2(UWord16, copto,    TimeoutReg);
    ARCH_REG2(UWord16, copctr,   ServiceReg);
    ARCH_REG1(UWord16, reserved[13]);

} arch_sCOP;

/* PLL/OCCS Module */

#define OCCS_VERSION 3
#define OCCS_VERSION_3
#define OCCS_HAS_RXOSC 1

typedef volatile struct
{
    ARCH_REG3(UWord16, pllcr,   ctrl, ControlReg);
    ARCH_REG3(UWord16, plldb,   divby, DivideReg);
    ARCH_REG3(UWord16, pllsr,   stat, StatusReg);
    ARCH_REG1(UWord16, reserved1);
    ARCH_REG1(UWord16, _shutdown);
    ARCH_REG2(UWord16, osctl,   octrl);
    ARCH_REG1(UWord16, clkchk);
    ARCH_REG1(UWord16, prot);
    ARCH_REG1(UWord16, reserved2[8]);

} arch_sPLL;

/* General Purpose I/O */

#define GPIO_VERSION 2
#define GPIO_VERSION_2

typedef volatile struct
{
    ARCH_REG3(UWord16, pur,      pupen, PullUpReg);
    ARCH_REG3(UWord16, dr,       data, DataReg);
    ARCH_REG3(UWord16, ddr,      ddir, DataDirectionReg);
    ARCH_REG3(UWord16, per,      peren, PeripheralReg);
    ARCH_REG3(UWord16, iar,      iassrt, IntAssertReg);
    ARCH_REG3(UWord16, ienr,     ien, IntEnableReg);
    ARCH_REG3(UWord16, ipolr,    iepol, IntPolarityReg);
    ARCH_REG3(UWord16, ipr,      ipend, IntPendingReg);
    ARCH_REG3(UWord16, iesr,     iedge, IntEdgeSensReg);
    ARCH_REG3(UWord16, ppmode,   ppoutm, PushPullModeReg);
    ARCH_REG3(UWord16, rawdata,  rdata, RawInputReg);
    ARCH_REG2(UWord16, drive,    DriveStrengthReg); /* VERSION_2,3-specific */
    ARCH_REG1(UWord16, reserved[4]);

} arch_sPort;

/* Lov-Voltage Detector */

#define LVI_VERSION 1
#define LVI_VERSION_1

typedef volatile struct
{
    ARCH_REG3(UWord16, lvictlr,  ctrl, control);
    ARCH_REG3(UWord16, lvisr,    stat, status);
    ARCH_REG1(UWord16, test);
    ARCH_REG1(UWord16, reserved[13]);

} arch_sLVI;

/* Flash Memory Module */

#define HFM_VERSION 2
#define HFM_VERSION_2

typedef volatile struct
{
    ARCH_REG2(UWord16, fmclkd,     clkd);
    ARCH_REG3(UWord16, fmcr,       cnfg, mcr);
    ARCH_REG1(UWord16, fmtst);
    ARCH_REG3(UWord16, fmsech,     sechi, sech);
    ARCH_REG3(UWord16, fmsecl,     seclo, secl);
    ARCH_REG2(UWord16, fmmntr,     mntr);
    ARCH_REG1(UWord16, reserved1[10]);
    ARCH_REG2(UWord16, fmprot,     prot);
    ARCH_REG1(UWord16, reserved2);
    ARCH_REG2(UWord16, fmstat,     stat);
    ARCH_REG2(UWord16, fmustat,    ustat);
    ARCH_REG2(UWord16, fmcmd,      cmd);
    ARCH_REG2(UWord16, fmctl,      ctl);
    ARCH_REG1(UWord16, fhadr);
    ARCH_REG1(UWord16, reserved3);
    ARCH_REG1(UWord16, fmdata);
    ARCH_REG1(UWord16, reserved4);
    ARCH_REG2(UWord16, fmopt0,     ifropt0);
    ARCH_REG3(UWord16, fmopt1,     opt1, ifropt1);
    ARCH_REG2(UWord16, fmmemsel,   ifrmemsel);
    ARCH_REG1(UWord16, fmtstsig);
    ARCH_REG1(UWord16, reserved5[226]);

} arch_sHFM;

/* Periodic Interrupt Timer */

#define PIT_VERSION 1
#define PIT_VERSION_1

typedef volatile struct {
    ARCH_REG1(UWord16, ctrl);
    ARCH_REG1(UWord16, mod);
    ARCH_REG1(UWord16, cntr);
    ARCH_REG1(UWord16, reserved[13]);

} arch_sPIT;

/* Digital to Analog Converter */

#define DAC_VERSION 1
#define DAC_VERSION_1

typedef volatile struct {
    ARCH_REG1(UWord16, ctrl);
    ARCH_REG1(UWord16, data);
    ARCH_REG1(UWord16, step);
    ARCH_REG1(UWord16, minval);
    ARCH_REG1(UWord16, maxval);
    ARCH_REG1(UWord16, reserved[11]);

} arch_sDAC;

/* Analog Comparator */

#define CMP_VERSION 1
#define CMP_VERSION_1

typedef volatile struct {
    ARCH_REG1(UWord16, ctrl);
    ARCH_REG1(UWord16, stat);
    ARCH_REG1(UWord16, filt);
    ARCH_REG1(UWord16, reserved[13]);

} arch_sCMP;

/* EOnCE Module */

typedef volatile struct {

    ARCH_REG1(UWord16, reserved[0xfd]);
    ARCH_REG2(UWord16, otxrxsr, TxRxStatusControlReg);
    ARCH_REG3(UWord32, orx, otx, RxTxReg);

} arch_sEOnCE;

/* peripheral space base addresses */

#define TMRA_BASE    0xF000
#define ADC_BASE     0xF080
#define PWM_BASE     0xF0C0
#define INTC_BASE    0xF0E0
#define SIM_BASE     0xF100
#define COP_BASE     0xF120
#define PLL_BASE     0xF130
#define LVI_BASE     0xF140
#define GPIO_A_BASE  0xF150
#define GPIO_B_BASE  0xF160
#define GPIO_C_BASE  0xF170
#define GPIO_D_BASE  0xF180
#define PIT0_BASE    0xF190
#define DAC0_BASE    0xF1C0
#define DAC1_BASE    0xF1D0
#define CMPA_BASE    0xF1E0
#define CMPB_BASE    0xF1F0
#define SCI0_BASE    0xF200
#define SPI0_BASE    0xF220
#define IIC_BASE     0xF280
#define HFM_BASE     0xF400
#define EONCE_BASE   0xFFFF00

/* complete periphiperal space described by single structure */

typedef volatile struct
{
    arch_sTimer    TimerA;         /* TMRA_BASE    0xF000 */
    arch_sTimer    TimerB_unused;
    arch_sADC      Adc;            /* ADC_BASE     0xF080 */
    arch_sPWM      Pwm;            /* PWM_BASE     0xF0C0 */
    arch_sIntc     Intc;           /* INTC_BASE    0xF0E0 */
    arch_sSIM      Sim;            /* SIM_BASE     0xF100 */
    arch_sCOP      Cop;            /* COP_BASE     0xF120 */
    arch_sPLL      Pll;            /* PLL_BASE     0xF130 */
    arch_sLVI      Lvi;            /* LVI_BASE     0xF140 */
    arch_sPort     PortA;          /* GPIO_A_BASE  0xF150 */
    arch_sPort     PortB;          /* GPIO_B_BASE  0xF160 */
    arch_sPort     PortC;          /* GPIO_C_BASE  0xF170 */
    arch_sPort     PortD;          /* GPIO_D_BASE  0xF180 */
    arch_sPIT      Pit0;           /* PIT0_BASE    0xF190 */
    arch_sPIT      Pit1_unused;
    arch_sPIT      Pit2_unused;
    arch_sDAC      Dac0;           /* DAC0_BASE    0xF1C0 */
    arch_sDAC      Dac1;           /* DAC1_BASE    0xF1D0 */
    arch_sCMP      CmpA;           /* CMPA_BASE    0xF1E0 */
    arch_sCMP      CmpB;           /* CMPB_BASE    0xF1F0 */
    arch_sSCI      Sci0;           /* SCI0_BASE    0xF200 */
    arch_sSCI      Sci1_unused;
    arch_sSPI      Spi0;           /* SPI0_BASE    0xF220 */
    arch_sSPI      Spi1_unused;
    UWord16        reserved1[0x40];
    arch_sIIC      Iic;            /* IIC_BASE     0xF280 */
    UWord16        reserved2[0x100];
    arch_sHFM      Hfm;            /* HFM_BASE     0xF400 */
    UWord16        reserved3[0x400];
    UWord16        reserved4[0xFF0600];
    arch_sEOnCE    EOnCE;          /* EOnCE_BASE   0xFFFF00 */ 
    
} arch_sIO;

/* The location of the following structure is defined in linker.cmd */
extern arch_sIO    ArchIO;

/* you can try to use direct address access too */
//#define ArchIO (*(volatile arch_sIO*) 0xf000)

#endif

