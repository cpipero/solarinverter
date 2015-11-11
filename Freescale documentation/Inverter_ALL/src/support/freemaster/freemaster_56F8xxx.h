/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_56F8xxx.h
*
* @brief  FreeMASTER Driver hardware dependent stuff
*
* @version 1.0.8.0
* 
* @date May-17-2007
* 
*******************************************************************************/

#ifndef __FREEMASTER_56F8xxx_H
#define __FREEMASTER_56F8xxx_H

/******************************************************************************
* platform-specific default configuration
******************************************************************************/

/* using 16bit addressing commands */
#ifndef FMSTR_USE_NOEX_CMDS
#define FMSTR_USE_NOEX_CMDS 1
#endif

/* using 32bit addressing commands */
#ifndef FMSTR_USE_EX_CMDS
#define FMSTR_USE_EX_CMDS   1
#endif

/* using inline access to buffer memory */
#ifndef FMSTR_USE_INLINE_BUFFER_ACCESS
#define FMSTR_USE_INLINE_BUFFER_ACCESS 0
#endif

/*****************************************************************************
* Board configuration information 
******************************************************************************/

#define FMSTR_PROT_VER           3U      /* protocol version 3 */
#define FMSTR_CFG_FLAGS          0U      /* board info flags */
#define FMSTR_CFG_BUS_WIDTH      1U      /* data bus width */
#define FMSTR_GLOB_VERSION_MAJOR 2U      /* driver version */
#define FMSTR_GLOB_VERSION_MINOR 0U
#define FMSTR_IDT_STRING "56F8xxx FreeMASTER Driver"
#define FMSTR_TSA_FLAGS FMSTR_TSA_INFO_HV2BA    /* HawkV2 TSA workaround */

/******************************************************************************
* platform-specific types
******************************************************************************/

typedef unsigned char  FMSTR_U8;     /* smallest memory entity (mostly 8bit) */
typedef unsigned short FMSTR_U16;    /* 16bit value */
typedef unsigned long  FMSTR_U32;    /* 32bit value */

typedef signed char    FMSTR_S8;     /* signed 8bit value */
typedef signed short   FMSTR_S16;    /* signed 16bit value */
typedef signed long    FMSTR_S32;    /* signed 32bit value */

typedef unsigned short FMSTR_FLAGS;  /* type to be union-ed with flags (at least 8 bits) */
typedef unsigned short FMSTR_SIZE8;  /* size value (at least 8 bits) */
typedef signed short   FMSTR_INDEX;  /* general for-loop index (must be signed) */

typedef unsigned char  FMSTR_BCHR;   /* type of a single character in comm.buffer */
typedef unsigned char* FMSTR_BPTR;   /* pointer within a communication buffer */

typedef unsigned short FMSTR_SCISR;  /* data type to store SCI status register */

/******************************************************************************
* communication buffer access functions (non-inline)
******************************************************************************/

void FMSTR_CopyMemory(FMSTR_ADDR nDestAddr, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyToBuffer(FMSTR_BPTR pDestBuff, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_CopyFromBuffer(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);
void FMSTR_CopyFromBufferWithMask(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_AddressFromBuffer(FMSTR_ADDR* pAddr, FMSTR_BPTR pSrc);
FMSTR_BPTR FMSTR_AddressToBuffer(FMSTR_BPTR pDest, FMSTR_ADDR nAddr);

/* FMSTR_SetExAddr is needed only if both EX and non-EX commands are used */
#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS
void FMSTR_SetExAddr(FMSTR_BOOL bNextAddrIsEx);
#else
/* otherwise, we know what addresses are used, (ignore FMSTR_SetExAddr) */
#define FMSTR_SetExAddr(bNextAddrIsEx) 
#endif

/******************************************************************************
* communication buffer access functions (inlines/functions - depending on cfg)
******************************************************************************/

#if FMSTR_USE_INLINE_BUFFER_ACCESS

inline FMSTR_BPTR FMSTR_ValueFromBuffer16(register FMSTR_U16* pDest, register FMSTR_BPTR pSrc)
{
    register FMSTR_U8* pd = (FMSTR_U8*) pDest;
    register FMSTR_U8 tmp;
    asm
    {
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
    }
    return pSrc;
}

inline FMSTR_BPTR FMSTR_ValueFromBuffer32(register FMSTR_U32* pDest, register FMSTR_BPTR pSrc)
{
    register FMSTR_U8* pd = (FMSTR_U8*) pDest;
    register FMSTR_U8 tmp;
    asm
    {
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
        move.bp X:(pSrc)+,tmp
        move.bp tmp,X:(pd)+
    }
    return pSrc;
}

inline FMSTR_BPTR FMSTR_ValueToBuffer16(register FMSTR_BPTR pDest, FMSTR_U16 src)
{
    register FMSTR_U8* ps = (FMSTR_U8*) & src;
    register FMSTR_U8 tmp;
    asm
    {
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
    }
    return pDest;
}

inline FMSTR_BPTR FMSTR_ValueToBuffer32(register FMSTR_BPTR pDest, FMSTR_U32 src)
{
    register FMSTR_U8* ps = (FMSTR_U8*) & src;
    register FMSTR_U8 tmp;
    asm
    {
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
        move.bp X:(ps)+,tmp
        move.bp tmp,X:(pDest)+
    }
    return pDest;
}

#else /* FMSTR_USE_INLINE_BUFFER_ACCESS */

inline FMSTR_BPTR FMSTR_ValueFromBuffer16(FMSTR_U16* pDest, FMSTR_BPTR pSrc)
{
    return FMSTR_CopyFromBuffer((FMSTR_ADDR)(FMSTR_U8*)pDest, pSrc, 2);
}

inline FMSTR_BPTR FMSTR_ValueFromBuffer32(FMSTR_U32* pDest, FMSTR_BPTR pSrc)
{
    return FMSTR_CopyFromBuffer((FMSTR_ADDR)(FMSTR_U8*)pDest, pSrc, 4);
}

inline FMSTR_BPTR FMSTR_ValueToBuffer16(FMSTR_BPTR pDest, FMSTR_U16 src)
{
    return FMSTR_CopyToBuffer(pDest, (FMSTR_ADDR)(FMSTR_U8*)&src, 2);
}

inline FMSTR_BPTR FMSTR_ValueToBuffer32(FMSTR_BPTR pDest, FMSTR_U32 src)
{
    return FMSTR_CopyToBuffer(pDest, (FMSTR_ADDR)(FMSTR_U8*)&src, 4);
}

#endif /* FMSTR_USE_INLINE_BUFFER_ACCESS */

/******************************************************************************
* communication buffer access inlines
******************************************************************************/

inline FMSTR_BPTR FMSTR_SkipInBuffer(FMSTR_BPTR pDest, FMSTR_SIZE8 nSize)
{
    return pDest + nSize;
}

inline FMSTR_BPTR FMSTR_ValueFromBuffer8(FMSTR_U8* pDest, register FMSTR_BPTR pSrc)
{
    *pDest = *pSrc++;
    return pSrc;
}

inline FMSTR_BPTR FMSTR_ValueToBuffer8(FMSTR_BPTR pDest, FMSTR_U8 src)
{
    *pDest++ = src;
    return pDest;
}

inline FMSTR_BPTR FMSTR_ConstToBuffer8(FMSTR_BPTR pDest, FMSTR_U8 src) 
{
    *pDest++ = src;
    return pDest; 
}

inline FMSTR_BPTR FMSTR_ConstToBuffer16(FMSTR_BPTR pDest, FMSTR_U16 src) 
{
    return FMSTR_ConstToBuffer8(FMSTR_ConstToBuffer8(pDest, (FMSTR_U8) src), (FMSTR_U8)(src>>8));
}

/****************************************************************************************
* memory access helper macros (used in recorder trigger compare routines)
*****************************************************************************************/

inline FMSTR_S8 FMSTR_GetS8(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_S8 tmp = 0;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( move.bp X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_S8*)addr;
    }   
}

inline FMSTR_U8 FMSTR_GetU8(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_U8 tmp = 0;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( moveu.bp X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_U8*)addr;
    }   
}

inline FMSTR_S16 FMSTR_GetS16(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_S16 tmp;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( asra raddr );
        asm ( move.w X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_S16*)(FMSTR_U8*)addr;
    }   
}

inline FMSTR_U16 FMSTR_GetU16(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_U16 tmp;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( asra raddr );
        asm ( move.w X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_U16*)(FMSTR_U8*)addr;
    }   
}

inline FMSTR_S32 FMSTR_GetS32(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_S32 tmp;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( asra raddr );
        asm ( move.l X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_S32*)(FMSTR_U8*)addr;
    }   
}

inline FMSTR_U32 FMSTR_GetU32(register FMSTR_ADDR addr)
{
    if(sizeof(FMSTR_ADDR) == 4)
    {
        register void* raddr;
        register FMSTR_U32 tmp;
        
        asm ( tfr addr,A );
        asm ( move.l A10, raddr );
        asm ( asra raddr );
        asm ( move.l X:(raddr),tmp );
        return tmp;
    }
    else
    {
        return *(FMSTR_U32*)(FMSTR_U8*)addr;
    }   
}

/****************************************************************************************
* Other helper macros
*****************************************************************************************/

/* This macro assigns C pointer to FMSTR_ADDR-typed variable */
/* should be done in assembly not to trim far-space pointers in SDM */

#define FMSTR_ARR2ADDR(addrvar,arr) /*lint -e{717} */ \
    do{ /*lint -esym(529,dw,rreg) -esym(530,dw,rreg) */ \
        register FMSTR_U32 dw;          \
        register void* rreg;            \
        asm ( move.l #>>arr, rreg );    \
        asm ( move.l rreg, dw );        \
        addrvar = (FMSTR_ADDR) dw;      \
    } while(0)

#define FMSTR_PTR2ADDR(tmpAddr, ptr) ( /*lint -e{923} */ tmpAddr = (FMSTR_ADDR) (FMSTR_U8*) ptr )

/****************************************************************************************
* Platform-specific configuration check
*****************************************************************************************/

/* sanity check, at least one of the modes should be enabled */
#if (!FMSTR_USE_EX_CMDS) && (!FMSTR_USE_NOEX_CMDS)
#error At least one of FMSTR_USE_EX_CMDS or FMSTR_USE_NOEX_CMDS should be set non-zero
#endif

/* JTAG / SCI selection */
#if FMSTR_USE_JTAG
    /* hardwired JTAG address on all HawkV2 devices */
    #ifndef FMSTR_JTAG_BASE
    #define FMSTR_JTAG_BASE 0xFFFF00 
    #endif
    
#elif FMSTR_USE_SCI
    /* user must select what SCI to use */
    #ifndef FMSTR_SCI_BASE
    #error You have to define FMSTR_SCI_BASE as a base address of SCI register space
    #endif
#endif

#if FMSTR_USE_SCI && FMSTR_USE_JTAG
#error You have to enable one of JTAG or SCI interface, not both
#endif

/****************************************************************************************
* General peripheral space access macros
*****************************************************************************************/

#define FMSTR_SETBIT(base, offset, bit)     (*(volatile FMSTR_U16*)(((FMSTR_U32)(base))+(offset)) |= bit)
#define FMSTR_CLRBIT(base, offset, bit)     (*(volatile FMSTR_U16*)(((FMSTR_U32)(base))+(offset)) &= (FMSTR_U16)~((FMSTR_U16)(bit)))
#define FMSTR_SETREG(base, offset, value)   (*(volatile FMSTR_U16*)(((FMSTR_U32)(base))+(offset)) = value)
#define FMSTR_GETREG(base, offset)          (*(volatile FMSTR_U16*)(((FMSTR_U32)(base))+(offset)))
#define FMSTR_SETREG32(base, offset, value) (*(volatile FMSTR_U32*)(((FMSTR_U32)(base))+(offset)) = value)
#define FMSTR_GETREG32(base, offset)        (*(volatile FMSTR_U32*)(((FMSTR_U32)(base))+(offset)))

/****************************************************************************************
* SCI module constants
*****************************************************************************************/

/* SCI module registers */
#define FMSTR_SCIBR_OFFSET 0U
#define FMSTR_SCICR_OFFSET 1U
#define FMSTR_SCISR_OFFSET 3U
#define FMSTR_SCIDR_OFFSET 4U

/* SCI Control Register bits */
#define FMSTR_SCICR_LOOP      0x8000U
#define FMSTR_SCICR_SWAI      0x4000U
#define FMSTR_SCICR_RSRC      0x2000U
#define FMSTR_SCICR_M         0x1000U
#define FMSTR_SCICR_WAKE      0x0800U
#define FMSTR_SCICR_POL       0x0400U
#define FMSTR_SCICR_PE        0x0200U
#define FMSTR_SCICR_PT        0x0100U
#define FMSTR_SCICR_TEIE      0x0080U
#define FMSTR_SCICR_TIIE      0x0040U
#define FMSTR_SCICR_RFIE      0x0020U
#define FMSTR_SCICR_REIE      0x0010U
#define FMSTR_SCICR_TE        0x0008U
#define FMSTR_SCICR_RE        0x0004U
#define FMSTR_SCICR_RWU       0x0002U
#define FMSTR_SCICR_SBK       0x0001U

/* SCI Status registers bits */
#define FMSTR_SCISR_TDRE      0x8000U
#define FMSTR_SCISR_TIDLE     0x4000U
#define FMSTR_SCISR_RDRF      0x2000U
#define FMSTR_SCISR_RIDLE     0x1000U
#define FMSTR_SCISR_OR        0x0800U
#define FMSTR_SCISR_NF        0x0400U
#define FMSTR_SCISR_FE        0x0200U
#define FMSTR_SCISR_PF        0x0100U
#define FMSTR_SCISR_RAF       0x0001U

/*******************************************************************************************
* SCI access macros
*****************************************************************************************/

/* transmitter enable/disable */
/*lint -emacro(923,FMSTR_SCI_TE, FMSTR_SCI_TD) : casting long to pointer */
#define FMSTR_SCI_TE() FMSTR_SETBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_TE)
#define FMSTR_SCI_TD() FMSTR_CLRBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_TE)

/* receiver enable/disable */
/*lint -emacro(923,FMSTR_SCI_RE, FMSTR_SCI_RD) : casting long to pointer */
#define FMSTR_SCI_RE() FMSTR_SETBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_RE)
#define FMSTR_SCI_RD() FMSTR_CLRBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_RE)

/* Transmitter-empty interrupt enable/disable : casting long to pointer */
/*lint -emacro(923,FMSTR_SCI_ETXI, FMSTR_SCI_DTXI) */
#define FMSTR_SCI_ETXI() FMSTR_SETBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_TEIE)
#define FMSTR_SCI_DTXI() FMSTR_CLRBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_TEIE)

/* Receiver-full interrupt enable/disable : casting long to pointer */
/*lint -emacro(923,FMSTR_SCI_ERXI, FMSTR_SCI_DRXI) */
#define FMSTR_SCI_ERXI() FMSTR_SETBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_RFIE)
#define FMSTR_SCI_DRXI() FMSTR_CLRBIT(FMSTR_SCI_BASE, FMSTR_SCICR_OFFSET, FMSTR_SCICR_RFIE)

/* Tranmsit character */
/*lint -emacro(923,FMSTR_SCI_PUTCHAR) : casting long to pointer */
#define FMSTR_SCI_PUTCHAR(ch) FMSTR_SETREG(FMSTR_SCI_BASE, FMSTR_SCIDR_OFFSET, ch)

/* Get received character */
/*lint -emacro(923,FMSTR_SCI_GETCHAR) : casting long to pointer */
#define FMSTR_SCI_GETCHAR() FMSTR_GETREG(FMSTR_SCI_BASE, FMSTR_SCIDR_OFFSET)

/* read status register */
/*lint -emacro(923,FMSTR_SCI_GETSR) : casting long to pointer */
#define FMSTR_SCI_GETSR()   FMSTR_GETREG(FMSTR_SCI_BASE, FMSTR_SCISR_OFFSET)

/* read & clear status register (clears error status bits only) */
/*lint -emacro(923,FMSTR_SCI_RDCLRSR) : casting long to pointer */
#define FMSTR_SCI_RDCLRSR() FMSTR_SETREG(FMSTR_SCI_BASE, FMSTR_SCISR_OFFSET, FMSTR_GETREG(FMSTR_SCI_BASE, FMSTR_SCISR_OFFSET))

/*******************************************************************************************
* JTAG access macros
*******************************************************************************************/

#define FMSTR_JTAG_OTXRXSR_OFFSET 0xfdU
#define FMSTR_JTAG_ORX_OFFSET     0xfeU
#define FMSTR_JTAG_OTX_OFFSET     0xfeU
#define FMSTR_JTAG_ORX1_OFFSET    0xffU
#define FMSTR_JTAG_OTX1_OFFSET    0xffU

/* OTXRXSR register */
#define FMSTR_JTAG_OTXRXSR_RDF 0x01U
#define FMSTR_JTAG_OTXRXSR_TDF 0x02U
#define FMSTR_JTAG_OTXRXSR_RIE 0x04U
#define FMSTR_JTAG_OTXRXSR_TIE 0x08U

#define _CHECK \
	if(FMSTR_GETREG(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET) & FMSTR_JTAG_OTXRXSR_RIE) \
		ioctl(GPIO_A, GPIO_SET_PIN, BIT_1); \
	else \
		ioctl(GPIO_A, GPIO_CLEAR_PIN, BIT_1)

/* enable/disable JTAG Rx-full interrupt */
/*lint -emacro(923,FMSTR_JTAG_ERXI,FMSTR_JTAG_DRXI) : casting long to pointer */
#define FMSTR_JTAG_ERXI() FMSTR_SETBIT(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET, FMSTR_JTAG_OTXRXSR_RIE)
#define FMSTR_JTAG_DRXI() FMSTR_CLRBIT(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET, FMSTR_JTAG_OTXRXSR_RIE)

/* enable/disable JTAG Tx-empty interrupt */
/*lint -emacro(923,FMSTR_JTAG_ETXI,FMSTR_JTAG_DTXI) : casting long to pointer */
#define FMSTR_JTAG_ETXI() FMSTR_SETBIT(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET, FMSTR_JTAG_OTXRXSR_TIE)
#define FMSTR_JTAG_DTXI() FMSTR_CLRBIT(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET, FMSTR_JTAG_OTXRXSR_TIE)

/* this macro verifies if the RIE bit is set (note that RIE is held low by HW until JTAG init) */
/*lint -emacro(923,FMSTR_JTAG_ERXI_CHECK,FMSTR_JTAG_ETXI_CHECK) : casting long to pointer */
#define FMSTR_JTAG_ERXI_CHECK() (FMSTR_GETREG(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET) & FMSTR_JTAG_OTXRXSR_RIE)
#define FMSTR_JTAG_ETXI_CHECK() (FMSTR_GETREG(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET) & FMSTR_JTAG_OTXRXSR_TIE)

/* get JTAG status register */
/*lint -emacro(923,FMSTR_JTAG_GETSR) : casting long to pointer */
#define FMSTR_JTAG_GETSR() FMSTR_GETREG(FMSTR_JTAG_BASE, FMSTR_JTAG_OTXRXSR_OFFSET)

/* Tranmsit JTAG word */
/*lint -emacro(923,FMSTR_JTAG_PUTDWORD) : casting long to pointer */
#define FMSTR_JTAG_PUTDWORD(ch) FMSTR_SETREG32(FMSTR_JTAG_BASE, FMSTR_JTAG_OTX_OFFSET, ch)

/* Get received word */
/*lint -emacro(923,FMSTR_JTAG_GETDWORD) : casting long to pointer */
#define FMSTR_JTAG_GETDWORD() FMSTR_GETREG32(FMSTR_JTAG_BASE, FMSTR_JTAG_ORX_OFFSET)

/* Get upper 16bit of received word */
/*lint -emacro(923,FMSTR_JTAG_GETWORD) : casting long to pointer */
#define FMSTR_JTAG_GETWORD() FMSTR_GETREG(FMSTR_JTAG_BASE, FMSTR_JTAG_ORX1_OFFSET)

#endif /* __FREEMASTER_56F8xxx_H */
