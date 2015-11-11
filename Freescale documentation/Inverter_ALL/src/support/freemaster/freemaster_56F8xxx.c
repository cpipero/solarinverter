/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_56F8xxx.c
*
* @brief  FreeMASTER Driver 56F800E-hardware dependent stuff
*
* @version 1.0.9.0
* 
* @date May-17-2007
* 
*******************************************************************************/

#include "freemaster.h"
#include "freemaster_private.h"

/*******************************************************************************
*
* @brief    API: Main SCI/JTAG Interrupt handler call
*
* This Interrupt Service Routine handles the SCI interrupts for the FreeMASTER 
* driver. In case you want to handle the interrupt in the application yourselves,
* call the FMSTR_ProcessSCI function which does the same job but is not compiled
* as an Interrupt Service Routine.
*
* In poll-driven mode (FMSTR_POLL_DRIVEN) this function does nothing.
*
*******************************************************************************/

/* 56F8xxx interrupt routine declaration, user has to  */
/* direct vector to the FMSTR_Isr function */
#pragma interrupt saveall

void FMSTR_Isr(void)
{
#if FMSTR_LONG_INTR || FMSTR_SHORT_INTR

    /* process serial interface */
#if FMSTR_USE_SCI
    FMSTR_ProcessSCI(); 
    
#elif FMSTR_USE_JTAG
    FMSTR_ProcessJTAG(); 
#endif
    
#endif
}

/* automatic inlining may cause problems with C calling convention assumed below */
#pragma dont_inline on

/**************************************************************************//*!
*
* @brief    The "memcpy" used internally in FreeMASTER driver
*
* @param    nDestAddr - destination memory address
* @param    nSrcAddr  - source memory address
* @param    nSize     - memory size (always in bytes)
*
* @return This function returns a pointer to next destination byte
*
******************************************************************************
*
* This function accepts both 16bit or 32bit address and works correctly 
* even in the SDM mode. Buffer address is a standard ANSI C pointer
*
* Warning: This call assumes CodeWarrior style of passing parameters,
* i.e. 32 bit operands passed in A and B accumulators
*
* Warning2: FMSTR_ADDR type MUST be numeric! (UWord type)
*
******************************************************************************/

void FMSTR_CopyMemory(FMSTR_ADDR nDestAddr, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize)
{
    register FMSTR_U8* pSrc = NULL;
    register FMSTR_U8* pDest = NULL;
    register FMSTR_U16 tmp = 0;

    /* from the lint point of view, these are realy unused */
    FMSTR_UNUSED(nDestAddr);
    FMSTR_UNUSED(nSrcAddr);
    FMSTR_UNUSED(pSrc);
    FMSTR_UNUSED(pDest);
    FMSTR_UNUSED(tmp);
        
#ifdef __MWERKS__
    /*lint -e{506,774} condition always true/false */
    if(sizeof(FMSTR_ADDR) == 4U)
    {
        asm ( move.l A10, pDest );  /* first 32bit argument is in A */
        asm ( move.l B10, pSrc );   /* second 32bit argument is in B */
    }
    else
    {
        asm ( move.w Y0, pDest );   /* first 16bit argument is in Y0 */
        asm ( move.w Y1, pSrc );    /* second 16bit argument is in Y1 */
    }
#else
#error CodeWarrior calling convention assumed, please fix this code for your compiler
#endif
    
    while(nSize--)
    {
        /* assembler must be used to handle 32bit addresses in SDM mode */
        /* this will get better after Metrowerks implements "far" pointers */
        asm 
        {
            move.bp X:(pSrc)+,tmp
            move.bp tmp,X:(pDest)+
        }
    }
}

/**************************************************************************//*!
*
* @brief  Write-into the communication buffer memory
*
* @param  pDestBuff - pointer to destination memory in communication buffer
* @param  nSrcAddr  - source memory address
* @param  nSize     - buffer size (always in bytes)
*
* @return This function returns a pointer to next byte in comm. buffer
*
******************************************************************************
*
* This function accepts both 16bit or 32bit address and works correctly 
* even in the SDM mode. Buffer address is a standard ANSI C pointer
*
* Warning: This call assumes CodeWarrior style of passing parameters,
* i.e. 32 bit operands passed in A and B accumulators
*
* Warning2: FMSTR_ADDR type MUST be numeric! (UWord type)
*
******************************************************************************/

FMSTR_BPTR FMSTR_CopyToBuffer(FMSTR_BPTR pDestBuff, FMSTR_ADDR nSrcAddr, FMSTR_SIZE8 nSize)
{
    register FMSTR_U8* pSrc;
    register FMSTR_U8* pDest = pDestBuff;
    register FMSTR_U16 tmp;
    
    FMSTR_UNUSED(nSrcAddr);

#ifdef __MWERKS__
    /*lint -e{506,774} condition always true/false */
    if(sizeof(FMSTR_ADDR) == 4U)
    {
        asm ( move.l A10, pSrc );   /* first 32bit argument is in A */
    }
    else
    {
        asm ( move.w Y0, pSrc );    /* first 16bit argument is in Y0 */
    }
        
#else
#error CodeWarrior calling convention assumed, please fix this code for your compiler
#endif
    
    while(nSize--)
    {
        /* assembler must be used to handle 32bit addresses in SDM mode */
        /* this will get better after Metrowerks implements "far" pointers */
        asm 
        {
            move.bp X:(pSrc)+,tmp
            move.bp tmp,X:(pDest)+
        }
    }
    
    return (FMSTR_BPTR)pDest;
}

/**************************************************************************//*!
*
* @brief  Read-out memory from communication buffer
*
* @param  nDestAddr - destination memory address
* @param  pSrcBuff  - pointer to source memory in communication buffer
* @param  nSize     - buffer size (always in bytes)
*
* @return This function returns a pointer to next byte in comm. buffer
*
******************************************************************************
*
* This function accepts both 16bit or 32bit address and works correctly 
* even in the SDM mode. Buffer address is a standard ANSI C pointer
*
* Warning: This call assumes CodeWarrior style of passing parameters,
* i.e. 32 bit operands passed in A and B accumulators
*
* Warning2: FMSTR_ADDR type MUST be numeric! (UWord type)
*
******************************************************************************/

FMSTR_BPTR FMSTR_CopyFromBuffer(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize)
{
    register FMSTR_U8* pSrc = pSrcBuff;
    register FMSTR_U8* pDest;
    register FMSTR_U16 tmp;
    
    FMSTR_UNUSED(nDestAddr);

#ifdef __MWERKS__
    /*lint -e{506,774} condition always true/false */
    if(sizeof(FMSTR_ADDR) == 4U)
    {
        asm ( move.l A10, pDest );  /* first 32bit argument is in A */
    }
    else
    {
        asm ( move.w Y0, pDest );   /* first 16bit argument is in Y0 */
    }
#else
#error CodeWarrior calling convention assumed, please fix this code for your compiler
#endif
    
    while(nSize--)
    {
        /* assembler must be used to handle 32bit addresses in SDM mode */
        /* this will get better after Metrowerks implements "far" pointers */
        asm 
        {
            move.bp X:(pSrc)+,tmp
            move.bp tmp,X:(pDest)+
        }
    }
    
    return (FMSTR_BPTR) pSrc;
}


/**************************************************************************//*!
*
* @brief  Read-out memory from communication buffer, perform AND-masking
*
* @param  nDestAddr - destination memory address
* @param  pSrcBuff  - source memory in communication buffer, mask follows data
* @param  nSize     - buffer size (always in bytes)
*
******************************************************************************
*
* This function accepts both 16bit or 32bit address and works correctly 
* even in the SDM mode. Buffer address is a standard ANSI C pointer
*
* Warning: This call assumes CodeWarrior style of passing parameters,
* i.e. 32 bit operands passed in A and B accumulators
*
* Warning2: FMSTR_ADDR type MUST be numeric! (UWord type)
*
******************************************************************************/

void FMSTR_CopyFromBufferWithMask(FMSTR_ADDR nDestAddr, FMSTR_BPTR pSrcBuff, FMSTR_SIZE8 nSize)
{
    register FMSTR_U8* pSrc = pSrcBuff;
    register FMSTR_U8* pDest;
    register FMSTR_U16 stmp, dtmp, mask;

    FMSTR_UNUSED(nDestAddr);

#ifdef __MWERKS__
    asm ( move.l A10, pDest );  /* first 32bit argument is in A = dwDestAddr -> pd */
    asm ( move.w Y0, N );
#else
#error CodeWarrior calling convention assumed, please fix this code for your compiler
#endif

    while(nSize--)
    {
        /* assembler must be used to handle 32bit addresses in SDM mode */
        /* this will get better after Metrowerks implements "far" pointers */
        asm 
        {
            /* fetch mask byte */
            move.bp X:(pSrc+N),mask
            
            /* fetch source byte */
            move.bp X:(pSrc)+,stmp
            
            /* fetch original destination value */
            move.bp X:(pDest),dtmp
        }
        
        /* perform AND-masking */
        /*lint -esym(530, stmp, dtmp, mask) prevent symbol not initialized message */
        stmp = (stmp & mask) | (dtmp & ~mask);

        asm
        {
            /* put the result back       */
            move.bp stmp,X:(pDest)+
        }
    }
}

#pragma dont_inline reset

/**************************************************************************//*!
*
* @brief  Select an address size to be used in next access to a comm. buffer
*
* @param  bNextAddrIsEx - when non zero, next expected address is 32bit wide
*                       - when zero, next expected address is 16bit wide
*
******************************************************************************/

#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS

static FMSTR_BOOL pcm_bUseExAddr;

void FMSTR_SetExAddr(FMSTR_BOOL bNextAddrIsEx)
{
    pcm_bUseExAddr = bNextAddrIsEx;
}

#endif

/**************************************************************************//*!
*
* @brief    Fetch 16/32 bit address from buffer
*
* @param  pAddr - ANSI C pointer to a variable which is to receive the result
* @param  pSrc  - pointer to a source memory in communication buffer
*
* @return This function returns a pointer to next byte in comm. buffer
*
******************************************************************************/

FMSTR_BPTR FMSTR_AddressFromBuffer(FMSTR_ADDR* pAddr, FMSTR_BPTR pSrc)
{
    /* do we have to differentiate the EX and non-EX access? */
#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS
    if(pcm_bUseExAddr)
#endif  
    {
#if FMSTR_USE_EX_CMDS
        /* fetch 32bit value */
        FMSTR_U32 nAddr32;
        pSrc = FMSTR_ValueFromBuffer32(&nAddr32, pSrc);
        /* and convert it to the address type */
        *pAddr = (FMSTR_ADDR) nAddr32;
#endif      
    }
#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS
    else
#endif  
    {
#if FMSTR_USE_NOEX_CMDS
        /* fetch 16bit value */
        FMSTR_U16 nAddr16;
        pSrc = FMSTR_ValueFromBuffer16(&nAddr16, pSrc);
        /* and convert it to the address type */
        *pAddr = (FMSTR_ADDR) nAddr16;
#endif      
    }
    
    return pSrc;
}

/**************************************************************************//*!
*
* @brief    Store 16/32 bit address to buffer
*
* @param  pDest - pointer to a destination memory in communication buffer
* @param  pSrc  - memory address value
*
* @return This function returns a pointer to next byte in comm. buffer
*
******************************************************************************/

FMSTR_BPTR FMSTR_AddressToBuffer(FMSTR_BPTR pDest, FMSTR_ADDR nAddr)
{
    /* do we have to differentiate the EX and non-EX access? */
#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS
    if(pcm_bUseExAddr)
#endif  
    {
#if FMSTR_USE_EX_CMDS
        /* put the address as a 32bit value */
        pDest = FMSTR_ValueToBuffer32(pDest, (FMSTR_U32) nAddr);
#endif      
    }
#if FMSTR_USE_EX_CMDS && FMSTR_USE_NOEX_CMDS
    else
#endif  
    {
#if FMSTR_USE_NOEX_CMDS
        /* put the address as a 16bit value */
        pDest = FMSTR_ValueToBuffer16(pDest, (FMSTR_U16) nAddr);
#endif
    }
    
    return pDest;
}

