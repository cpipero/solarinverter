/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_private.h
*
* @brief  FreeMASTER driver private declarations, used internally by the driver
*
* @version 1.0.19.0
* 
* @date Apr-11-2007
* 
*******************************************************************************/

#ifndef __FREEMASTER_PRIVATE_H
#define __FREEMASTER_PRIVATE_H

#ifndef __FREEMASTER_H
#error Please include the freemaster.h master header file before the freemaster_private.h
#endif

#include "freemaster_cfg.h"

/******************************************************************************
* Platform-dependent types, macros and functions
******************************************************************************/

#undef FMSTR_PLATFORM

/* platform macro FMSTR_PLATFORM_xxxxxxx should be defined  */
/* as "non-zero" in the "freemaster.h" file */

#if defined(FMSTR_PLATFORM_56F8xx)
    #if FMSTR_PLATFORM_56F8xx
    #include "freemaster_56F8xx.h"
    #define FMSTR_PLATFORM 56F8xx
    #else
    #undef FMSTR_PLATFORM_56F8xx
    #endif
#endif

#if defined(FMSTR_PLATFORM_56F8xxx)
    #if FMSTR_PLATFORM_56F8xxx
    #include "freemaster_56F8xxx.h"
    #define FMSTR_PLATFORM 56F8xxx
    #else
    #undef FMSTR_PLATFORM_56F8xxx
    #endif
#endif

#if defined(FMSTR_PLATFORM_HC12)
    #if FMSTR_PLATFORM_HC12
    #include "freemaster_HC12.h"
    #define FMSTR_PLATFORM HC12
    #else
    #undef FMSTR_PLATFORM_HC12
    #endif
#endif

#if defined(FMSTR_PLATFORM_HC08)
    #if FMSTR_PLATFORM_HC08
    #include "freemaster_HC08.h"
    #define FMSTR_PLATFORM HC08
    #else
    #undef FMSTR_PLATFORM_HC08
    #endif
#endif

#if defined(FMSTR_PLATFORM_MPC55xx)
    #if FMSTR_PLATFORM_MPC55xx
    #include "freemaster_MPC55xx.h"
    #define FMSTR_PLATFORM MPC55xx
    #else
    #undef FMSTR_PLATFORM_MPC55xx
    #endif
#endif

#if defined(FMSTR_PLATFORM_MPC5xx)
    #if FMSTR_PLATFORM_MPC5xx
    #include "freemaster_MPC5xx.h"
    #define FMSTR_PLATFORM MPC5xx
    #else
    #undef FMSTR_PLATFORM_MPC5xx
    #endif
#endif

#if defined(FMSTR_PLATFORM_MCF52xx)
    #if FMSTR_PLATFORM_MCF52xx
    #include "freemaster_MCF52xx.h"
    #define FMSTR_PLATFORM MCF52xx
    #else
    #undef FMSTR_PLATFORM_MCF52xx
    #endif
#endif

#ifndef FMSTR_PLATFORM
#error Unknown FreeMASTER driver platform
#endif

/******************************************************************************
* NULL needed
******************************************************************************/

#ifndef NULL
#define NULL ((void *) 0)
#endif

/******************************************************************************
* Boolean values
******************************************************************************/

#ifndef FMSTR_TRUE
#define FMSTR_TRUE 1U
#endif

#ifndef FMSTR_FALSE
#define FMSTR_FALSE 0U
#endif

/******************************************************************************
* Global non-API functions (used internally in FreeMASTER driver)
******************************************************************************/

void FMSTR_InitSerial(void);
void FMSTR_ProtocolDecoder(FMSTR_BPTR pMessageIO);
void FMSTR_SendResponse(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nLength);
void FMSTR_ProcessSCI(void);
void FMSTR_ProcessJTAG(void);

FMSTR_BPTR FMSTR_GetBoardInfo(FMSTR_BPTR pMessageIO);

FMSTR_BPTR FMSTR_ReadMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMem(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_WriteVar(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteVarMask(FMSTR_BPTR pMessageIO, FMSTR_SIZE8 nSize);
FMSTR_BPTR FMSTR_WriteMemMask(FMSTR_BPTR pMessageIO);

void FMSTR_InitAppCmds(void);
FMSTR_BPTR FMSTR_StoreAppCmd(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetAppCmdRespData(FMSTR_BPTR pMessageIO);

void FMSTR_InitScope(void);
FMSTR_BPTR FMSTR_SetUpScope(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_ReadScope(FMSTR_BPTR pMessageIO);

void FMSTR_InitRec(void);
FMSTR_BPTR FMSTR_SetUpRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StartRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_StopRec(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecStatus(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetRecBuff(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_IsInRecBuffer(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize);
FMSTR_SIZE FMSTR_GetRecBuffSize(void);
void FMSTR_AbortRec(void);

void FMSTR_InitTsa(void);
FMSTR_BPTR FMSTR_GetTsaInfo(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_GetStringLen(FMSTR_BPTR pMessageIO);
FMSTR_BOOL FMSTR_CheckTsaSpace(FMSTR_ADDR nAddr, FMSTR_SIZE8 nSize, FMSTR_BOOL bWriteAccess);
FMSTR_U16  FMSTR_StrLen(FMSTR_ADDR nAddr);

void FMSTR_InitSfio(void);
FMSTR_BPTR FMSTR_SfioFrame(FMSTR_BPTR pMessageIO);
FMSTR_BPTR FMSTR_SfioGetResp(FMSTR_BPTR pMessageIO);

void FMSTR_InitPipes(void);
FMSTR_BPTR FMSTR_PipeFrame(FMSTR_BPTR pMessageIO);

/****************************************************************************************
* Potentialy unused variable declaration
*****************************************************************************************/

#ifdef  _lint
#define FMSTR_UNUSED(sym) /*lint -esym(715,sym) -esym(818,sym) -esym(529,sym) -e{960} */
#else
#define FMSTR_UNUSED(sym) ((sym),0)
#endif

/******************************************************************************
* Configuration check 
******************************************************************************/

/* polling mode as default when nothing selected */
#if !defined(FMSTR_POLL_DRIVEN) && !defined(FMSTR_LONG_INTR) && !defined(FMSTR_SHORT_INTR)
    #define FMSTR_LONG_INTR   0
    #define FMSTR_SHORT_INTR  0
    #define FMSTR_POLL_DRIVEN 1
#endif

/* otherwise, "undefined" means false for all three options */
#ifndef FMSTR_POLL_DRIVEN
#define FMSTR_POLL_DRIVEN 0
#endif
#ifndef FMSTR_LONG_INTR
#define FMSTR_LONG_INTR 0
#endif
#ifndef FMSTR_SHORT_INTR
#define FMSTR_SHORT_INTR 0
#endif

#if (FMSTR_LONG_INTR && (FMSTR_SHORT_INTR || FMSTR_POLL_DRIVEN)) || \
    (FMSTR_SHORT_INTR && (FMSTR_LONG_INTR || FMSTR_POLL_DRIVEN)) || \
    (FMSTR_POLL_DRIVEN && (FMSTR_LONG_INTR || FMSTR_SHORT_INTR)) || \
    !(FMSTR_POLL_DRIVEN || FMSTR_LONG_INTR || FMSTR_SHORT_INTR)
    /* mismatch in interrupt modes, only one can be selected */
    #error You have to enable exctly one of FMSTR_LONG_INTR or FMSTR_SHORT_INTR or FMSTR_POLL_DRIVEN
#endif

#if FMSTR_SHORT_INTR
    /* default short-interrupt FIFO size */
    #ifndef FMSTR_COMM_RQUEUE_SIZE
    #define FMSTR_COMM_RQUEUE_SIZE 32
    #endif

    #if !FMSTR_COMM_RQUEUE_SIZE
    #undef  FMSTR_COMM_RQUEUE_SIZE
    #define FMSTR_COMM_RQUEUE_SIZE 32
    #endif
    
    #if FMSTR_COMM_RQUEUE_SIZE < 1
    #error Error in FMSTR_COMM_RQUEUE_SIZE value.
    #endif
#endif

/* disable both JTAG and SCI by default */
/* one of these is typically already enabled in freemaster_cfg.h */
#ifndef FMSTR_USE_JTAG
#define FMSTR_USE_JTAG 0
#endif
#ifndef FMSTR_USE_SCI
    #if defined(FMSTR_SCI_BASE) && !FMSTR_USE_JTAG
    #define FMSTR_USE_SCI 1
    #else
    #define FMSTR_USE_SCI 0
    #endif
#endif

/* SCI does not have a transmission double buffer (kind of queue) */
/* (if not specified differently in platform-dependent header file) */
#if FMSTR_USE_SCI
#ifndef FMSTR_SCI_HAS_TXQUEUE
#define FMSTR_SCI_HAS_TXQUEUE 0
#endif
#endif

/* read memory commands are ENABLED by default */
#ifndef FMSTR_USE_READMEM
#define FMSTR_USE_READMEM 1
#endif
#ifndef FMSTR_USE_WRITEMEM
#define FMSTR_USE_WRITEMEM 1
#endif
#ifndef FMSTR_USE_WRITEMEMMASK 
#define FMSTR_USE_WRITEMEMMASK 1
#endif

/* read variable commands are DISABLED by default */
#ifndef FMSTR_USE_READVAR
#define FMSTR_USE_READVAR 0
#endif
#ifndef FMSTR_USE_WRITEVAR
#define FMSTR_USE_WRITEVAR 0
#endif
#ifndef FMSTR_USE_WRITEVARMASK 
#define FMSTR_USE_WRITEVARMASK 0
#endif

/* default scope settings */
#ifndef FMSTR_USE_SCOPE
#define FMSTR_USE_SCOPE 0
#endif

#ifndef FMSTR_MAX_SCOPE_VARS
#define FMSTR_MAX_SCOPE_VARS 8
#endif

/* check scope settings */
#if FMSTR_USE_SCOPE
    #if FMSTR_MAX_SCOPE_VARS > 8 || FMSTR_MAX_SCOPE_VARS < 2
        #error Error in FMSTR_MAX_SCOPE_VARS value. Use a value in range 2..8
    #endif
#endif  

/* default recorder settings */
#ifndef FMSTR_USE_RECORDER
#define FMSTR_USE_RECORDER 0
#endif

#ifndef FMSTR_MAX_REC_VARS
#define FMSTR_MAX_REC_VARS 8
#endif

#ifndef FMSTR_REC_FARBUFF
#define FMSTR_REC_FARBUFF 0
#endif

#ifndef FMSTR_REC_OWNBUFF
#define FMSTR_REC_OWNBUFF 0
#endif

#ifndef FMSTR_USE_FASTREC
#define FMSTR_USE_FASTREC 0
#endif

/* check recorder settings */
#if FMSTR_USE_RECORDER || FMSTR_USE_FASTREC
    #if FMSTR_MAX_REC_VARS > 8 || FMSTR_MAX_REC_VARS < 2
        #error Error in FMSTR_MAX_REC_VARS value. Use a value in range 2..8
    #endif
    
    /* 0 means recorder time base is "unknown" */
    #ifndef FMSTR_REC_TIMEBASE
    #define FMSTR_REC_TIMEBASE 0 
    #endif
    
    /* default recorder buffer size is 256 */
    #ifndef FMSTR_REC_BUFF_SIZE
    #define FMSTR_REC_BUFF_SIZE 256
    #endif

    #if !FMSTR_USE_READMEM
    #error Recorder needs the FMSTR_USE_READMEM feature
    #endif
#endif  

/* fast recorder requires its own allocation of recorder buffer */
#if FMSTR_USE_FASTREC
    #if FMSTR_REC_OWNBUFF
        #error Fast recorder requires its own buffer allocation
    #endif
#endif

/* default app.cmds settings */
#ifndef FMSTR_USE_APPCMD
#define FMSTR_USE_APPCMD 0
#endif

#ifndef FMSTR_APPCMD_BUFF_SIZE
#define FMSTR_APPCMD_BUFF_SIZE 16
#endif

#ifndef FMSTR_MAX_APPCMD_CALLS
#define FMSTR_MAX_APPCMD_CALLS 0
#endif

/* TSA configuration check */
#ifndef FMSTR_USE_TSA
#define FMSTR_USE_TSA 0
#endif

#ifndef FMSTR_USE_TSA_SAFETY
#define FMSTR_USE_TSA_SAFETY 0
#endif

#if FMSTR_USE_TSA
    #if !FMSTR_USE_READMEM
        #error TSA needs the FMSTR_USE_READMEM feature
    #endif
#endif

/* SFIO not used by default */
#ifndef FMSTR_USE_SFIO
#define FMSTR_USE_SFIO 0
#endif

/* check SFIO settings */
#if FMSTR_USE_SFIO

    /* The SFIO configuration files (sfio.h and optionally also the sfio_cfg.h) exist 
       in project to define SFIO parameters. */
    #include "sfio.h"
    
    #ifndef SFIO_MAX_INPUT_DATA_LENGTH
    #error  SFIO_MAX_INPUT_DATA_LENGTH was not defined in sfio_cfg.h
    #endif
    #ifndef SFIO_MAX_OUTPUT_DATA_LENGTH
    #error  SFIO_MAX_OUTPUT_DATA_LENGTH was not defined in sfio_cfg.h
    #endif
    
#endif    

/* use transport "pipe" functionality */
#ifndef FMSTR_USE_PIPES
#define FMSTR_USE_PIPES 0
#endif

#if FMSTR_USE_PIPES
    
    #warning FreeMASTER Pipes feature is still in a prototype/experimental version.
    
    #ifndef FMSTR_MAX_PIPES_COUNT
    #define FMSTR_MAX_PIPES_COUNT 1
    #endif
    
    /* at least one */
    #if FMSTR_MAX_PIPES_COUNT < 1
    #warning No sense to allocate zero-count pipes. Disabling pipes.
    #undef  FMSTR_USE_PIPES
    #define FMSTR_USE_PIPES 0
    #endif
    
#endif

/* what kind of board information structure will be sent? */
#ifndef FMSTR_USE_BRIEFINFO
    #if FMSTR_USE_RECORDER
        /* recorder requires full info */
        #define FMSTR_USE_BRIEFINFO 0
    #else
        /* otherwise no brief info is enough */
        #define FMSTR_USE_BRIEFINFO 1
    #endif
#endif

/* check what kind of board info is sent */
#if FMSTR_USE_BRIEFINFO
    #if FMSTR_USE_RECORDER
        #warning The full information structure must be used when recorder is to be used
        #undef  FMSTR_USE_BRIEFINFO
        #define FMSTR_USE_BRIEFINFO 1
    #endif
#endif

/* automatic buffer size by default */
#ifndef FMSTR_COMM_BUFFER_SIZE
#define FMSTR_COMM_BUFFER_SIZE 0
#endif

/* check minimal buffer size required for all enabled features */
#if FMSTR_COMM_BUFFER_SIZE
    
    /* basic commands (getinfobrief, write/read memory etc.) */
    #if FMSTR_USE_BRIEFINFO && FMSTR_COMM_BUFFER_SIZE < 11 
    #error FMSTR_COMM_BUFFER_SIZE set too small for basic FreeMASTER commands (11 bytes)
    #endif

    /* full info required */
    #if !(FMSTR_USE_BRIEFINFO) && FMSTR_COMM_BUFFER_SIZE < 35
    #error FMSTR_COMM_BUFFER_SIZE set too small for GETINFO command (size 35)
    #endif

    /* application commands */
    #if FMSTR_USE_APPCMD && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_APPCMD_BUFF_SIZE)+1)
    #error FMSTR_COMM_BUFFER_SIZE set too small for SENDAPPCMD command (size FMSTR_APPCMD_BUFF_SIZE+1)
    #endif

    /* configuring scope (EX) */
    #if FMSTR_USE_SCOPE && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_MAX_SCOPE_VARS)*5+1)
    #error FMSTR_COMM_BUFFER_SIZE set too small for SETUPSCOPEEX command (size FMSTR_MAX_SCOPE_VARS*5+1)
    #endif

    /* configuring recorder (EX) */
    #if FMSTR_USE_RECORDER && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_MAX_REC_VARS)*5+18)
    #error FMSTR_COMM_BUFFER_SIZE set too small for SETUPRECEX command (size FMSTR_MAX_REC_VARS*5+18)
    #endif
    
    /* SFIO encapsulation */
    #if FMSTR_USE_SFIO
    #if (FMSTR_COMM_BUFFER_SIZE < ((SFIO_MAX_INPUT_DATA_LENGTH)+1)) || \
        (FMSTR_COMM_BUFFER_SIZE < ((SFIO_MAX_OUTPUT_DATA_LENGTH)+1))
    #error FMSTR_COMM_BUFFER_SIZE set too small for SFIO encapsulation (see SFIO_MAX_xxx_DATA_LENGTH)
    #endif
    #endif

/* automatic: determine required buffer size based on features enabled */
#else
    /* smallest for basic commands (getinfobrief, write/read memory etc.) */
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE 11

    /* full info required */
    #if !(FMSTR_USE_BRIEFINFO) && FMSTR_COMM_BUFFER_SIZE < 35
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE 35
    #endif

    /* using application commands (must accomodate maximal app.cmd data length) */
    #if FMSTR_USE_APPCMD && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_APPCMD_BUFF_SIZE)+1)
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE ((FMSTR_APPCMD_BUFF_SIZE)+1)
    #endif

    /* configuring scope (EX) */
    #if FMSTR_USE_SCOPE && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_MAX_SCOPE_VARS)*5+1)
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE ((FMSTR_MAX_SCOPE_VARS)*5+1)
    #endif

    /* configuring recorder (EX) */
    #if FMSTR_USE_RECORDER && FMSTR_COMM_BUFFER_SIZE < ((FMSTR_MAX_REC_VARS)*5+18)
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE ((FMSTR_MAX_REC_VARS)*5+18)
    #endif

    /* SFIO encapsulation (in buffer) */
    #if FMSTR_USE_SFIO
    #if FMSTR_COMM_BUFFER_SIZE < ((SFIO_MAX_INPUT_DATA_LENGTH)+1)
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE ((SFIO_MAX_INPUT_DATA_LENGTH)+1)
    #endif
    #endif
    
    /* SFIO encapsulation (out buffer) */
    #if FMSTR_USE_SFIO
    #if FMSTR_COMM_BUFFER_SIZE < ((SFIO_MAX_OUTPUT_DATA_LENGTH)+1)
    #undef  FMSTR_COMM_BUFFER_SIZE
    #define FMSTR_COMM_BUFFER_SIZE ((SFIO_MAX_OUTPUT_DATA_LENGTH)+1)
    #endif
    #endif
    
#endif

#endif /* __FREEMASTER_PRIVATE_H */

