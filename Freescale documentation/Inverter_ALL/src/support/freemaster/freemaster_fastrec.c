/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_fastrec.c
*
* @brief  FreeMASTER 56F800E-hardware dependent fast-recorder routines
*
* @version 1.0.2.0
* 
* @date Sep-6-2006
* 
*******************************************************************************/

#include "freemaster.h"
#include "freemaster_private.h"

#if FMSTR_USE_RECORDER && FMSTR_USE_FASTREC

#include "freemaster_fastrec.h"

/* global variables */
FMSTR_ADDR pcm_dwFastRecWritePtr;
FMSTR_ADDR pcm_dwFastRecStartBuffPtr;
FMSTR_ADDR pcm_dwFastRecEndBuffPtr;

/* statically allocated recorder buffer (FMSTR_REC_OWNBUFF is FALSE) */
#if FMSTR_REC_FARBUFF
#pragma section fardata begin
#endif /* FMSTR_REC_FARBUFF */
static FMSTR_U16 pcm_pFastRecBuffer[FMSTR_REC_BUFF_SIZE/2];
/* end of far memory section */
#if FMSTR_REC_FARBUFF
#pragma section fardata end
#endif /* FMSTR_REC_FARBUFF */

/**************************************************************************//*!
*
* @brief    Fast Recorder Initialization
*
******************************************************************************/

void FMSTR_InitFastRec(void)
{
    /* get array pointer as 32bit value */    
    FMSTR_ARR2ADDR(pcm_dwFastRecStartBuffPtr, pcm_pFastRecBuffer);
    
    /* base driver requires byte-addressing */
    FMSTR_SetUpRecBuff(pcm_dwFastRecStartBuffPtr * 2, FMSTR_REC_BUFF_SIZE);
}

/**************************************************************************//*!
*
* @brief    Check if recorder configuration can be used in fast-recorder mode
*
******************************************************************************/

FMSTR_BOOL FMSTR_SetUpFastRec(void)
{
    FMSTR_INDEX i;
    
    /* check all recorder variables */
    for(i=0; i<pcm_nRecVarCount; i++)
    {
        /* only word-sized variables allowed */
        if(pcm_pRecVarSize[i] != 2)
            return 0;
        
        /* byte-pointer address must be word-aligned */
        if(pcm_pRecVarAddr[i] & 1)
            return 0;
        
        /* convert byte-pointer to word-pointer */
        pcm_pRecVarAddr[i] /= 2;
    }    

    pcm_dwFastRecEndBuffPtr = pcm_dwFastRecStartBuffPtr + pcm_wRecTotalSmps * pcm_nRecVarCount;

    /* our fast-trigger implementation requires post-trigger is not zero (zero would be 0xffff) */
    if(pcm_wRecPostTrigger == 0)
        pcm_wRecPostTrigger = 1;
    
    return 1;
}

/**************************************************************************//*!
*
* @brief    Notification from base recorder driver: start recording
*
******************************************************************************/

void FMSTR_StartFastRec(void)
{
    pcm_dwFastRecWritePtr = pcm_dwFastRecStartBuffPtr;
}

/**************************************************************************//*!
*
* @brief    Notification from base recorder driver: manual trigger
*
******************************************************************************/

void FMSTR_TriggerFastRec(void)
{
}

/**************************************************************************//*!
*
* @brief    Notification from base recorder driver: prepare return data
*
******************************************************************************/

void FMSTR_GetFastRecBuff(void)
{
    FMSTR_ADDR a;    
    
    /* calculate index of the first sample */
    a = pcm_dwFastRecWritePtr - pcm_dwFastRecStartBuffPtr;
    
    /* word-pointer offset divided by number of (word-wide-only) variables */
    pcm_wRecBuffStartIx = (FMSTR_U16)(a / (FMSTR_U16)pcm_nRecVarCount);
}

#endif /* FMSTR_USE_RECORDER && FMSTR_USE_FASTREC */


