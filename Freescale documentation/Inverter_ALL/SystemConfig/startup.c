/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: startup.c$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.27.0$
*
* Description: DSP56F800E_Quick_Start startup code
*
*****************************************************************************/

#include "qs.h"

/* OMR mode bits */

#define OMR_CM  0x0100
#define OMR_XP  0x0080
#define OMR_R   0x0020
#define OMR_SA  0x0010
#define OMR_EX  0x0008

/* initial OMR value: 

    set OMR_INIT in appconfig.h or 
    TARGET_OMR_INIT is set in prefix (lcf) file 
*/

#ifndef TARGET_OMR_INIT
#define TARGET_OMR_INIT 0
#endif

#ifndef OMR_INIT
#define OMR_INIT 0|(TARGET_OMR_INIT)
#endif

/* verify some OMR bits:

    XP=0 to enable harvard architecture
    CM=0 (optional for C)
    R=0  (required for C)
    SA=0 (required for C) 
    EX=0 (rquired for CodeWarrior debugging (CW-2.0-Alpha2)
*/
    
#if (OMR_INIT & (OMR_CM|OMR_XP|OMR_R|OMR_SA))
#warning Initial OMR value might be invalid for the C project
#endif
#if (OMR_INIT) & OMR_EX
#warning MetroWerks CodeWarrior cannot debug projects with OMR.EX bit set
#endif

/* ARCH_VECTBL_ADDR_LCF macro is now obsolete, VBA is taken from LCF by default */

#if defined(ARCH_VECTBL_ADDR_LCF) && !(ARCH_VECTBL_ADDR_LCF)
/* emulating original behavior, which used to use ARCH_VECTBL_ADDR */
#ifndef ARCH_VECTBL_ADDR
#define ARCH_VECTBL_ADDR 0
#endif
#endif

/* vector table location to be taken from the Linker Command File ? */

#if ARCH_VECTBL_ADDR_LCF && defined(ARCH_VECTBL_ADDR)
#warning Vector Table location will be taken from Linker Command File (ignoring ARCH_VECTBL_ADDR)
#undef ARCH_VECTBL_ADDR /* force LCF value to be used */
#endif

/* it can be specified in appconfig.h whether to wait for PLL coarse or fine state */

#ifndef OCCS_REQUIRED_LOCK_MODE
#define OCCS_REQUIRED_LOCK_MODE 0x20 /* coarse (LCK0) by default */
#endif
#if (OCCS_REQUIRED_LOCK_MODE != 0x40) && (OCCS_REQUIRED_LOCK_MODE != 0x20)
#error OCCS_REQUIRED_LOCK_MODE must be one of 0x20 (LCK0-coarse) or 0x40 (LCK1-fine)
#endif

/* test values for RAM testing */

#ifndef CONFIG_INTRAM_CHECKVALUE1
#define CONFIG_INTRAM_CHECKVALUE1 0xaaaa
#endif
#ifndef CONFIG_INTRAM_CHECKVALUE2
#define CONFIG_INTRAM_CHECKVALUE2 0x5555
#endif

/* prototypes */

asm void Start(void);
extern void userPreMain(void);
extern void userPostMain(void);
extern void main(void);

/* external constants defined in LCF */

extern _Lstack_addr;
extern _Ldata_size;
extern _Ldata_ROM_addr;
extern _Ldata_RAM_addr;
extern _Ldata2_size;
extern _Ldata2_ROM_addr;
extern _Ldata2_RAM_addr;
extern _Ldatap_size;
extern _Ldatap_ROM_addr;
extern _Ldatap_RAM_addr;
extern _Lbss_size;
extern _Lbss_start;
extern _Lbss2_size;
extern _Lbss2_start;
extern _Lbssp_size;
extern _Lbssp_start;
extern _Linternal_RAM_addr;
extern _Linternal_RAM_size;
extern _Linterrupt_vectors_addr;

asm void Start(void)
{
/* relocate vector table properly */
    #ifdef ARCH_VECTBL_ADDR
    move.l ARCH_VECTBL_ADDR,A
    #else 
    move.l #_Linterrupt_vectors_addr,A
    #endif
    asrr.l #7,A
    move.w A0,ArchIO.Intc.vba

/* clear COP watchdog counter, keep clearing values in registers C1,D1,R5 */
    moveu.w #ArchIO.Cop.copctr,R5
    move.w 0x5555,C1
    move.w 0xAAAA,D1
    move.w C1,X:(R5)
    move.w D1,X:(R5)

/* setup the OMR */
    bfset OMR_INIT,omr
    nop
    nop

/* setup the m01 register for linear addressing */
    move.w  #-1,x0
    moveu.w x0,m01

/* clear (read-out) the hardware stack */
    moveu.w hws,la
    moveu.w hws,la
    nop
    nop

/* configure external oscillator and clock mode */

#ifdef OCCS_OSCTL_INIT
#define OSCTL_TEMP (OCCS_OSCTL_INIT & 0x3fff) /* keep internal oscillator enabled */
    move.w  #OSCTL_TEMP,ArchIO.Pll.osctl      /* OSCTL, even if PLL is not used */
    nop
    nop
#endif

/* setup the PLL according to appconfig.h values */

#ifdef OCCS_PLLDB_INIT
    move.w  OCCS_PLLDB_INIT,ArchIO.Pll.plldb  /* PLLDB, even if PLL is not used */
    nop
    nop
#endif

/* load factory trimming value of the internal relaxation oscillator? */

#if OCCS_USE_FACTORY_TRIM
    
/* first move factory value to Y1 */    
    move.w  ArchIO.Hfm.fmopt1,y1
    bfclr   #0xfc00,y1
    
/* re-trim rxosc frequency? */

#if defined(OCCS_RXOSC_RETRIM_CLK)
#if (OCCS_RXOSC_RETRIM_CLK) != 8000000
    
#define MULDIV_CONST(a,b,c) ((((a)*(b)) + ((c)/2)) / (c))
#define RETRIM_COEFF (MULDIV_CONST(0x10000,8000000/256,(OCCS_RXOSC_RETRIM_CLK)/256)-0x10000)

#if RETRIM_COEFF >= 32768
    #warning Required frequency is too far from 8 MHz. Fixed to a closest value.
    #undef  RETRIM_COEFF
    #define RETRIM_COEFF 32767
#elif RETRIM_COEFF < -32768
    #warning Required frequency is too far from 8 MHz. Fixed to a closest value.
    #undef  RETRIM_COEFF
    #define RETRIM_COEFF -32768
#endif

    add.w #(1282-0x200),Y1
    move.w Y1,A0
    move.w #(RETRIM_COEFF), A1
    
    /* Y1 = (A0 * A1 / 0x10000) which is the corrective offset for original FMOPT */
    IMPYSU A1,A0,Y
    add.l 0x7fff,Y
    add.w ArchIO.Hfm.fmopt1,Y1

retrim_test_negative:   /* test of result is negative */
    cmp.w 0,Y1
    bge retrim_test_oveflow
    nop

    move.w #0,Y1        /* result negative, use minimal possible value */
    bra <retrim_done

retrim_test_oveflow:    /* tets if result overflew to or over 0x400 */
    cmp.w 0x400,Y1
    blt retrim_done
    move.w #0x3ff,Y1    /* above 0x3ff, use this maximum possible value */
    
retrim_done:
    
#endif /* OCCS_RXOSC_RETRIM_CLK != 8000000 */
#endif /* OCCS_RXOSC_RETRIM_CLK defined */

/* now save Y0 to proper place in OSCCTL register */
    move.w  ArchIO.Pll.osctl,x0
    bfclr   #0x03ff,x0
    or.w    y1,x0
    move.w  x0,ArchIO.Pll.osctl
    nop

#endif /* OCCS_USE_FACTORY_TRIM */


#ifdef OCCS_PLLCR_INIT

/* on new devices, some external pins may be needed if PLLCR.PRESC=1 */

#if defined(OCCS_VERSION_3) && defined(SIM_VERSION_4) && (OCCS_PLLCR_INIT & 0x4)

    /* first get EXT_SEL and CLK_MODE values (see OSCTL register) */
    #ifdef OCCS_OSCTL_INIT
    #define _OCCS_EXTSEL  (((OCCS_OSCTL_INIT) >> 10) & 0x3)
    #define _OCCS_CLKMODE (((OCCS_OSCTL_INIT) >> 12) & 0x1)
    #else
    #define _OCCS_EXTSEL  0 /* reset value is 0 */
    #define _OCCS_CLKMODE 1 /* reset value is 1 */
    #endif

    /* primary external clock on GPIO_B6 */
    #if _OCCS_EXTSEL == 0   
    bfset 0x4000, ArchIO.Sim.sim_gpsb0
    bfclr 0x2000, ArchIO.Sim.sim_gpsb0
    bfset 0x0040, ArchIO.PortB.per
        
    /* alternate external clock on GPIO_B5 */        
    #elif _OCCS_EXTSEL == 1 
    bfset 0x1000, ArchIO.Sim.sim_gpsb0
    bfclr 0x0800, ArchIO.Sim.sim_gpsb0
    bfset 0x0020, ArchIO.PortB.per
    
    /* external clock on XTAL (GPIO_D5)*/
    #elif _OCCS_CLKMODE 
    bfset 0x1000, ArchIO.Sim.sim_gpscd
    bfset 0x0020, ArchIO.PortD.per
        
    /* crystal on EXTAL and XTAL pins (GPIO_D4 and GPIO_D5)*/
    #else 
    bfclr 0x1000, ArchIO.Sim.sim_gpscd
    bfset 0x0030, ArchIO.PortD.per

    /* give it some time until crystal/resonator stabilizes */
    /* we now run from internal relaxation oscillator / 2 (i.e. 4MHz) */
    move.w #5000,x0   /* wait 50ms */
    do x0,waitosc     
    rep 36; nop;      /* sigle loop pass takes 40 cycles */
    move.w C1,X:(R5)  /* and also clears the watchdog */
    move.w D1,X:(R5)
waitosc:        

    #endif /* _OCCS_EXTSEL cases */

    /* switch to external clock source (set PRESC=1) */
    nop;
    bfset 0x4,ArchIO.Pll.pllcr
    nop 
    nop
    
#endif /* defined(OCCS_VERSION_3) && (OCCS_PLLCR_INIT & 0x4) */

#if ((OCCS_PLLCR_INIT & 3) == 2) /* PLL active ? */

#define PLLCR_TEMP (OCCS_PLLCR_INIT & 0xfc | 0x01) /* interrupts off and PLL bypassed */

    brclr 1,ArchIO.Pll.pllcr,skip_pll_lock /* skip PLL in simulator mode */
    move.w  #PLLCR_TEMP,ArchIO.Pll.pllcr   /* PLL lock detector ON, core still on prescaler */

pll_lock:
    move.w C1,X:(R5)  /* clear COP watchdog counter while waiting in the loop */  
    move.w D1,X:(R5)
    
    brclr   OCCS_REQUIRED_LOCK_MODE,ArchIO.Pll.pllsr,pll_lock   /* test lock (LCK1 or LCK0) */

    nop
    nop
    move.w  OCCS_PLLCR_INIT,ArchIO.Pll.pllcr  /* PLL is locked: final PLL setup */

skip_pll_lock:
    move.w  ArchIO.Pll.pllsr,x0     /* clear pending clkgen interrupts */
    move.w  x0,ArchIO.Pll.pllsr
    nop

#else /* ((OCCS_PLLCR_INIT & 3) == 2) PLL not active */

    move.w  OCCS_PLLCR_INIT,ArchIO.Pll.pllcr    /* just write the PLLCR init value */

#endif /* ((OCCS_PLLCR_INIT & 3) == 2) */
#endif /* OCCS_PLLCR_INIT */

#ifdef OCCS_OSCTL_INIT
    move.w  OCCS_OSCTL_INIT,ArchIO.Pll.osctl
    nop
    nop
#endif

/* setup memory regions (chip-selects) according to appconfig.h values */

#ifdef SEMI_BASE

    moveu.w #ArchIO.Semi.csbar, R0
    moveu.w #ArchIO.Semi.csor,  R1
    moveu.w #ArchIO.Semi.cstc,  R2
    
#ifdef SEMI_CSBAR0_INIT
    move.w SEMI_CSBAR0_INIT, X:(R0+0)
#endif
#ifdef SEMI_CSOR0_INIT
    move.w SEMI_CSOR0_INIT, X:(R1+0)
#endif
#ifdef SEMI_CSTC0_INIT
    move.w SEMI_CSTC0_INIT, X:(R2+0)
#endif
#ifdef SEMI_CSBAR1_INIT
    move.w SEMI_CSBAR1_INIT, X:(R0+1)
#endif
#ifdef SEMI_CSOR1_INIT
    move.w SEMI_CSOR1_INIT, X:(R1+1)
#endif
#ifdef SEMI_CSTC1_INIT
    move.w SEMI_CSTC1_INIT, X:(R2+1)
#endif
#ifdef SEMI_CSBAR2_INIT
    move.w SEMI_CSBAR2_INIT, X:(R0+2)
#endif
#ifdef SEMI_CSOR2_INIT
    move.w SEMI_CSOR2_INIT, X:(R1+2)
    bfset 0x0001, ArchIO.PortD.per      /* enable CS2 on GPIO PD0 */
#endif
#ifdef SEMI_CSTC2_INIT
    move.w SEMI_CSTC2_INIT, X:(R2+2)
#endif
#ifdef SEMI_CSBAR3_INIT
    move.w SEMI_CSBAR3_INIT, X:(R0+3)
#endif
#ifdef SEMI_CSOR3_INIT
    move.w SEMI_CSOR3_INIT, X:(R1+3)
    bfset 0x0002, ArchIO.PortD.per      /* enable CS3 on GPIO PD1 */
#endif
#ifdef SEMI_CSTC3_INIT
    move.w SEMI_CSTC3_INIT, X:(R2+3)
#endif
#ifdef SEMI_CSBAR4_INIT
    move.w SEMI_CSBAR4_INIT, X:(R0+4)
#endif
#ifdef SEMI_CSOR4_INIT
    move.w SEMI_CSOR4_INIT, X:(R1+4)
    bfset 0x0004, ArchIO.PortD.per      /* enable CS4 on GPIO PD2 */
#endif
#ifdef SEMI_CSTC4_INIT
    move.w SEMI_CSTC4_INIT, X:(R2+4)
#endif
#ifdef SEMI_CSBAR5_INIT
    move.w SEMI_CSBAR5_INIT, X:(R0+5)
#endif
#ifdef SEMI_CSOR5_INIT
    move.w SEMI_CSOR5_INIT, X:(R1+5)
    bfset 0x0008, ArchIO.PortD.per      /* enable CS5 on GPIO PD3 */
#endif
#ifdef SEMI_CSTC5_INIT
    move.w SEMI_CSTC5_INIT, X:(R2+5)
#endif
#ifdef SEMI_CSBAR6_INIT
    move.w SEMI_CSBAR6_INIT, X:(R0+6)
#endif
#ifdef SEMI_CSOR6_INIT
    move.w SEMI_CSOR6_INIT, X:(R1+6)
    bfset 0x0010, ArchIO.PortD.per      /* enable CS6 on GPIO PD4 */
#endif
#ifdef SEMI_CSTC6_INIT
    move.w SEMI_CSTC6_INIT, X:(R2+6)
#endif
#ifdef SEMI_CSBAR7_INIT
    move.w SEMI_CSBAR7_INIT, X:(R0+7)
#endif
#ifdef SEMI_CSOR7_INIT
    move.w SEMI_CSOR7_INIT, X:(R1+7)
    bfset 0x0020, ArchIO.PortD.per      /* enable CS7 on GPIO PD5 */
#endif
#ifdef SEMI_CSTC7_INIT
    move.w SEMI_CSTC7_INIT, X:(R2+7)
#endif

/* global wait states not covered by CS registers */
#ifdef SEMI_BCR_INIT
    move.w SEMI_BCR_INIT, ArchIO.Semi.bcr
#endif

#endif /* SEMI_BASE */


/* internal RAM memory test */

#ifdef INTXRAM_CHECK_ENABLED
#ifndef TARGET_DATA_INTRAM
#warning Internal Memory Checking is active but variables go elsewhere
#endif

    move.l  #>>_Linternal_RAM_addr,r1       /* memory pointer */
    move.l  #>>_Linternal_RAM_size,r2       /* memory size */
    move.w  CONFIG_INTRAM_CHECKVALUE1, x0   /* x0=write/test value 1 */
    move.w  CONFIG_INTRAM_CHECKVALUE2, y0   /* y0=write/test value 2; */
    move.w  #0,b                            /* b0=0, b1 will be used as "b" */
    
    rep r2; move.w x0,x:(r1)+               /* fill memory with value test1 */
    
    move.l  #>>_Linternal_RAM_addr,r1       /* initialize verify memory pointer */
    do      r2,end_intramcheck1             /* start verify loop */

    move.w C1,X:(R5)                        /* clear COP watchdog counter */  
    move.w D1,X:(R5)

    cmp.w   x:(r1),x0                       /* TEST1: read & compare */
    beq     <t1passed                       /* TEST1: OK ? */
    debughlt
    
t1passed:
    move.w  y0,x:(r1)                       /* TEST2: write test2 */
    move.w  x:(r1+1),y1                     /* read from incremented address (see TEST3) */
    cmp.w   x:(r1),y0                       /* read written value & compare (should be test2) */
    beq     <t2passed                       /* TEST2: OK ? */
    
    nop
    debughlt /* !! MEMORY TEST FAILED !! */
    STOP

t2passed:
    move.w  lc,b                            /* skip TEST3 for the last memory cell (when LC==1) */
    cmp.w   #1,b    
    ble     <t3passed                       
    cmp.w   y1,x0                           /* TEST3: value from incremented address should be ==test1 */
    beq     <t3passed                       /* TEST3: OK ? */
    
    nop
    debughlt /* !! MEMORY TEST FAILED !! */
    STOP
    
t3passed:
    move.w  b0,x:(r1)+                      /* clear checked memory location */
    nop
    nop                                     /* without nops, the branch to t3passed above */
    nop                                     /* could confuse the hardware loop unit */
    
end_intramcheck1:
#endif

/* initialize stack */

    move.l #>>_Lstack_addr,r0
    bftsth #$0001,r0
    bcc <noinc
    adda #1,r0
noinc:
    tfra    r0,sp
    move.w  #0,r1
    nop
    move.w  r1,x:(sp)
    adda    #1,sp   

/* clear BSS segment (can't use 'do' and its 16 bit loop counter) */

    move.l  #>>_Lbss_size,r2        /* bss size */
    tsta.l  r2
    beq <end_clearbss;              /* skip if size is 0 */
    move.l  #>>_Lbss_start,r1       /* dest address */
    move.w  #0,x0
loop_clearbss:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  x0,x:(r1)+              /* clear value at r1 */
    dectsta r2;                     /* long loop counter */
    bne <loop_clearbss;
end_clearbss:

/* clear BSS2 segment (can't use 'do' and its 16 bit loop counter) */

#ifdef SEMI_BASE /* only if far space is physically available */

    move.l  #>>_Lbss2_size,r2       /* bss size */
    tsta.l  r2
    beq <end_clearbss2;             /* skip if size is 0 */
    move.l  #>>_Lbss2_start,r1      /* dest address */
    move.w  #0,x0
loop_clearbss2:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  x0,x:(r1)+              /* clear value at r1 */
    dectsta r2;                     /* long loop counter */
    bne <loop_clearbss2;
end_clearbss2:

#endif

/* clear BSSP (program RAM) segment (can't use 'do' and its 16 bit loop counter) */

    move.l  #>>_Lbssp_size,r2       /* bssp size */
    tsta.l  r2
    beq <end_clearbssp;             /* skip if size is 0 */
    move.l  #>>_Lbssp_start,r1      /* dest address */
    move.w  #0,x0
loop_clearbssp:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  x0,p:(r1)+              /* clear value at r1 */
    dectsta r2;                     /* long loop counter */
    bne <loop_clearbssp;
end_clearbssp:

    
/* copy variable initialization data from xFlash to destination (16bit LC ok) */

#ifdef TARGET_INITDATA_XFLASH
    move.l  #>>_Ldata_size,r2       /* set data size */
    move.l  #>>_Ldata_ROM_addr,r3   /* src address -- xROM data start */
    move.l  #>>_Ldata_RAM_addr,r1   /* dest address -- xRAM data start */
    do      r2,end_xrom2xram        /* copy for r2 times */
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  x:(r3)+,x0              /* fetch value at address r3 */
    move.w  x0,x:(r1)+              /* stash value at address r1 */
end_xrom2xram:

/* dtto for fardata (if available) */

#ifdef SEMI_BASE
    move.l  #>>_Ldata2_size,r2      /* set data size */
    move.l  #>>_Ldata2_ROM_addr,r3  /* src address -- xROM data start */
    move.l  #>>_Ldata2_RAM_addr,r1  /* dest address -- xRAM data start */
    do      r2,end_xrom2xram2       /* copy for r2 times */
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  x:(r3)+,x0              /* fetch value at address r3 */
    move.w  x0,x:(r1)+              /* stash value at address r1 */
end_xrom2xram2:
#endif

#endif

/* copy variable initialization data from pFlash to destination (long loop) */

#ifdef TARGET_INITDATA_PFLASH
    move.l  #>>_Ldata_size,r2       /* set data size */
    tsta.l  r2
    beq <end_prom2xram
    move.l  #>>_Ldata_ROM_addr,r3   /* src address -- xROM data start */
    move.l  #>>_Ldata_RAM_addr,r1   /* dest address -- xRAM data start */
loop_prom2xram:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  p:(r3)+,x0              /* fetch value at address r3 */
    move.w  x0,x:(r1)+              /* stash value at address r1 */
    dectsta r2
    bne <loop_prom2xram
end_prom2xram:

/* dtto for fardata (if available) */

#ifdef SEMI_BASE
    move.l  #>>_Ldata2_size,r2      /* set data size */
    tsta.l  r2
    beq <end_prom2xram2
    move.l  #>>_Ldata2_ROM_addr,r3  /* src address -- xROM data start */
    move.l  #>>_Ldata2_RAM_addr,r1  /* dest address -- xRAM data start */
loop_prom2xram2:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  p:(r3)+,x0              /* fetch value at address r3 */
    move.w  x0,x:(r1)+              /* stash value at address r1 */
    dectsta r2
    bne <loop_prom2xram2
end_prom2xram2:
#endif

#endif

/* in any flash-based target, do copy pram-variable initialization data 
   (and ram-based code) from pFlash storage to destination in program-ram */

#ifdef TARGET_CODE_PFLASH
    move.l  #>>_Ldatap_size,r2      /* set data size */
    tsta.l  r2
    beq <end_prom2pram
    move.l  #>>_Ldatap_ROM_addr,r3  /* src address -- pROM data start */
    move.l  #>>_Ldatap_RAM_addr,r1  /* dest address -- pRAM data start */
loop_prom2pram:
    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    move.w  p:(r3)+,x0              /* fetch value at address r3 */
    move.w  x0,p:(r1)+              /* stash value at address r1 */
    dectsta r2
    bne <loop_prom2pram
end_prom2pram:
#endif

/* call userPreMain() from appconfig.c */
    jsr userPreMain

/* call main() */
    move.w  #0,y0                   /* pass parameters to main() */
    move.w  #0,r2
    move.w  #0,r3

    move.w  C1,X:(R5)               /* clear COP watchdog counter */  
    move.w  D1,X:(R5)
    
    jsr main                        /* call the user program */
    
/* call userPostMain() from appconfig.c */
    jsr userPostMain
    

/*   The fflush calls where removed because they added code */
/*   growth in cases where the user is not using any debugger IO. */
/*   Users should now make these calls at the end of main if they use debugger IO */

/*  move.w  #0,r2 */
/*  jsr     fflush          ; flush file IO */
/*  jsr     fflush_console  ; flush console IO   */

/*  end of program; halt CPU     */

    nop
    debughlt
    STOP
}
