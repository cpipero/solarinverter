/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster.h
*
* @brief  FreeMASTER Driver main API header file
*
* @version 1.0.9.0
* 
* @date Apr-11-2007
* 
*******************************************************************************
*
* This is the only header file needed to be included by the user application
* to implement the FreeMASTER interface. In addition, user has to write her 
* "freemaster_cfg.h" configuration file and put it anywhere on the #include path
*
*******************************************************************************/

#ifndef __FREEMASTER_H
#define __FREEMASTER_H

/* identify our current platform */
#define FMSTR_PLATFORM_56F8xxx 1

/* user configuration */
#include "freemaster_cfg.h"

/*****************************************************************************
* Global types
******************************************************************************/

typedef unsigned long  FMSTR_ADDR;   /* CPU address type (use integer data type on 56F8xxx) */
typedef unsigned short FMSTR_SIZE;   /* general size type (at least 16 bits) */
typedef unsigned short FMSTR_BOOL;   /* general boolean type  */

/* application command-specific types */
typedef unsigned short FMSTR_APPCMD_CODE;
typedef unsigned short FMSTR_APPCMD_DATA, *FMSTR_APPCMD_PDATA;
typedef unsigned short FMSTR_APPCMD_RESULT;

/* pointer to application command callback handler */
typedef FMSTR_APPCMD_RESULT (*FMSTR_PAPPCMDFUNC)(FMSTR_APPCMD_CODE,FMSTR_APPCMD_PDATA,FMSTR_SIZE);

/* pipe-related tyeps */
typedef void* FMSTR_HPIPE;  /* pipe handle */
typedef unsigned short FMSTR_PIPE_PORT; /* pipe port identifier (unsigned, 7 bits used) */
typedef unsigned short FMSTR_PIPE_SIZE; /* pipe buffer size type (unsigned, at least 8 bits) */

/* pointer to pipe event handler */
typedef void (*FMSTR_PPIPEFUNC)(FMSTR_HPIPE);

/*****************************************************************************
* TSA-related user types and macros
******************************************************************************/

#include "freemaster_tsa.h"

/*****************************************************************************
* Constants
******************************************************************************/

/* application command status information  */
#define FMSTR_APPCMDRESULT_NOCMD      0xffU
#define FMSTR_APPCMDRESULT_RUNNING    0xfeU
#define MFSTR_APPCMDRESULT_LASTVALID  0xf7U  /* F8-FF are reserved  */

/* recorder time base declaration helpers */
#define FMSTR_REC_BASE_SECONDS(x)  ((x) & 0x3fffU)
#define FMSTR_REC_BASE_MILLISEC(x) (((x) & 0x3fffU) | 0x4000U)
#define FMSTR_REC_BASE_MICROSEC(x) (((x) & 0x3fffU) | 0x8000U)
#define FMSTR_REC_BASE_NANOSEC(x)  (((x) & 0x3fffU) | 0xc000U)

/*****************************************************************************
* Global functions 
******************************************************************************/

/* FreeMASTER serial communication API */
void FMSTR_Init(void); /* general initiazlation */
void FMSTR_Poll(void); /* polling call, use in SHORT_INTR and POLL_DRIVEN modes */
void FMSTR_Isr(void);  /* SCI/JTAG interrupt handler for LONG_INTR and SHORT_INTR modes */

/* recorder API */
void FMSTR_Recorder(void);
void FMSTR_TriggerRec(void);
void FMSTR_SetUpRecBuff(FMSTR_ADDR nBuffAddr, FMSTR_SIZE nBuffSize);

/* Application commands API */
FMSTR_APPCMD_CODE  FMSTR_GetAppCmd(void);
FMSTR_APPCMD_PDATA FMSTR_GetAppCmdData(FMSTR_SIZE* pDataLen);
FMSTR_BOOL         FMSTR_RegisterAppCmdCall(FMSTR_APPCMD_CODE nAppCmdCode, FMSTR_PAPPCMDFUNC pCallbackFunc);

void FMSTR_AppCmdAck(FMSTR_APPCMD_RESULT nResultCode);
void FMSTR_AppCmdSetResponseData(FMSTR_ADDR nResultDataAddr, FMSTR_SIZE nResultDataLen);

/* Transport layer API */
FMSTR_HPIPE FMSTR_PipeOpen(FMSTR_PIPE_PORT nPort, FMSTR_PPIPEFUNC pCallback,
                           FMSTR_ADDR pRxBuff, FMSTR_PIPE_SIZE nRxSize, 
                           FMSTR_ADDR pTxBuff, FMSTR_PIPE_SIZE nTxSize);
void FMSTR_PipeClose(FMSTR_HPIPE hpipe);
FMSTR_PIPE_SIZE FMSTR_PipeWrite(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size);
FMSTR_PIPE_SIZE FMSTR_PipeRead(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size);

#endif /* __FREEMASTER_H */

