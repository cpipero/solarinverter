/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_rec.c
*
* @brief  FreeMASTER Recorder implementation.
*
* @version 1.0.9.0
* 
* @date Apr-11-2007
* 
*******************************************************************************/

#include "freemaster.h"
#include "freemaster_private.h"
#include "freemaster_protocol.h"

#if FMSTR_USE_RECORDER

#include "freemaster_rec.h"

#if FMSTR_USE_FASTREC
#include "freemaster_fastrec.h"
#endif

/********************************************************
*  global variables (shared with FastRecorder if used)
********************************************************/

/* configuration variables */
FMSTR_U16  pcm_wRecTotalSmps;        /* number of samples to measure */
FMSTR_U16  pcm_wRecPostTrigger;      /* number of post-trigger samples to keep */
FMSTR_U8   pcm_nRecTriggerMode;      /* triger mode (0 = disabled, 1 = _/, 2 = \_) */
FMSTR_U16  pcm_wRecTimeDiv;          /* divisor of recorder "clock" */

FMSTR_U8    pcm_nRecVarCount;        /* number of active recorder variables */
FMSTR_ADDR  pcm_pRecVarAddr[FMSTR_MAX_SCOPE_VARS]; /* addresses of recorded variables */
FMSTR_SIZE8 pcm_pRecVarSize[FMSTR_MAX_SCOPE_VARS]; /* sizes of recorded variables */

/* runtime variables  */
FMSTR_U16   pcm_wRecBuffStartIx;     /* first sample index */

FMSTR_ADDR pcm_dwRecWritePtr;        /* write pointer in recorder buffer */
FMSTR_ADDR pcm_dwRecEndBuffPtr;      /* pointer to end of active recorder buffer */
FMSTR_U16  pcm_wRecTimeDivCtr;       /* recorder "clock" divisor counter */
FMSTR_U16  pcm_wStoprecCountDown;    /* post-trigger countdown counter */

/* recorder flags */
FMSTR_REC_FLAGS pcm_wRecFlags;

/***********************************
*  local variables 
***********************************/

/* configuration variables */
static FMSTR_ADDR pcm_nTrgVarAddr;          /* trigger variable address */
static FMSTR_U8   pcm_nTrgVarSize;          /* trigger variable threshold size */
static FMSTR_U8   pcm_bTrgVarSigned;        /* trigger compare mode (0 = unsigned, 1 = signed) */

/*lint -e{960} using union */
static union 
{
#if FMSTR_CFG_BUS_WIDTH == 1
    FMSTR_U8  u8; 
    FMSTR_S8  s8;
#endif
    FMSTR_U16 u16;
    FMSTR_S16 s16;
    FMSTR_U32 u32;
    FMSTR_S32 s32;
} pcm_uTrgThreshold;                        /* trigger threshold level (1,2 or 4 bytes) */

static FMSTR_ADDR  pcm_nRecBuffAddr;        /* recorder buffer address */
static FMSTR_SIZE  pcm_wRecBuffSize;        /* recorder buffer size */

/* compare functions prototype */
typedef FMSTR_BOOL (*FMSTR_PCOMPAREFUNC)(void);

/*/ pointer to active compare function */
static FMSTR_PCOMPAREFUNC pcm_pCompareFunc;

#if !FMSTR_REC_OWNBUFF && !FMSTR_USE_FASTREC
/* put buffer into far memory ? */
#if FMSTR_REC_FARBUFF
#pragma section fardata begin
#endif /* FMSTR_REC_FARBUFF */
/* statically allocated recorder buffer (FMSTR_REC_OWNBUFF is FALSE) */
static FMSTR_U8 pcm_pOwnRecBuffer[FMSTR_REC_BUFF_SIZE];
/* end of far memory section */
#if FMSTR_REC_FARBUFF
#pragma section fardata end
#endif /* FMSTR_REC_FARBUFF */
#endif /* FMSTR_REC_OWNBUFF */

/***********************************
*  local functions
***********************************/

static FMSTR_BOOL FMSTR_Compare8S(void);
static FMSTR_BOOL FMSTR_Compare8U(void);
static FMSTR_BOOL FMSTR_Compare16S(void);
static FMSTR_BOOL FMSTR_Compare16U(void);
static FMSTR_BOOL FMSTR_Compare32S(void);
static FMSTR_BOOL FMSTR_Compare32U(void);
static void FMSTR_Recorder2(void);

/**************************************************************************//*!
*
* @brief    Recorder Initialization
*
******************************************************************************/

void FMSTR_InitRec(void)
{   
    /* setup buffer pointer and size so IsInRecBuffer works even  
       before the recorder is first initialized and used */
    
#if FMSTR_REC_OWNBUFF || FMSTR_USE_FASTREC
    /* user wants to use his own buffer */
    pcm_nRecBuffAddr = 0U;
    pcm_wRecBuffSize = 0U;
#else
    /* size in native sizeof units (=bytes on most platforms) */
    pcm_wRecBuffSize = (FMSTR_SIZE) FMSTR_REC_BUFF_SIZE;
    FMSTR_ARR2ADDR(pcm_nRecBuffAddr, pcm_pOwnRecBuffer);
    
    /*lint -esym(528, pcm_pOwnRecBuffer) this symbol is used outside of lint sight */
#endif

#if FMSTR_USE_FASTREC
    FMSTR_InitFastRec();
#endif
}

/**************************************************************************//*!
*
* @brief    API: Replacing the recorder buffer with the user's one
*
* @param    pBuffer - user buffer pointer
* @param    wBuffSize - buffer size
*
* @note Use the FMSTR_SetUpBuff32 to pass the forced 32bit address in SDM
*
******************************************************************************/

void FMSTR_SetUpRecBuff(FMSTR_ADDR pBuffer, FMSTR_SIZE nBuffSize)
{    
    pcm_nRecBuffAddr = pBuffer;
    pcm_wRecBuffSize = nBuffSize;
}

/**************************************************************************//*!
*
* @brief    Handling SETUPREC and SETUPREC_EX commands
*
* @param    pMessageIO - original command (in) and response buffer (out) 
*
* @return   As all command handlers, the return value should be the buffer 
*           pointer where the response output finished (except checksum)
*
******************************************************************************/

FMSTR_BPTR FMSTR_SetUpRec(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_SIZE8 nRecVarsetSize;
    FMSTR_SIZE blen;
    FMSTR_U8 i, sz;

    /* de-initialize first   */
    FMSTR_AbortRec();

#if FMSTR_REC_OWNBUFF || FMSTR_USE_FASTREC
    /* user wants to use his own buffer, check if it is valid */
    if(!pcm_nRecBuffAddr || !pcm_wRecBuffSize)
    {
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVBUFF);
    }
#else
    /* size in native sizeof units (=bytes on most platforms) */
    pcm_wRecBuffSize = (FMSTR_SIZE)FMSTR_REC_BUFF_SIZE;
    FMSTR_ARR2ADDR(pcm_nRecBuffAddr, pcm_pOwnRecBuffer);
#endif

    /* seek the setup data */
    pMessageIO = FMSTR_SkipInBuffer(pMessageIO, 2U);
    pMessageIO = FMSTR_ValueFromBuffer8(&pcm_nRecTriggerMode, pMessageIO);
    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecTotalSmps, pMessageIO);
    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecPostTrigger, pMessageIO);
    pMessageIO = FMSTR_ValueFromBuffer16(&pcm_wRecTimeDiv, pMessageIO);

    /* address & size of trigger variable */
    pMessageIO = FMSTR_AddressFromBuffer(&pcm_nTrgVarAddr, pMessageIO);
    pMessageIO = FMSTR_ValueFromBuffer8(&pcm_nTrgVarSize, pMessageIO);

    /* trigger compare mode  */
    pMessageIO = FMSTR_ValueFromBuffer8(&pcm_bTrgVarSigned, pMessageIO);

    /* threshold value  */
    pMessageIO = FMSTR_ValueFromBuffer32(&pcm_uTrgThreshold.u32, pMessageIO);

    /* recorder variable count */
    pMessageIO = FMSTR_ValueFromBuffer8(&pcm_nRecVarCount, pMessageIO);

    /* rec variable information must fit into our buffers */
    if(!pcm_nRecVarCount || pcm_nRecVarCount > (FMSTR_U8)FMSTR_MAX_REC_VARS)
    {
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVBUFF);
    }

    /* calculate sum of sizes of all variables */
    nRecVarsetSize = 0U;

    /* get all addresses and sizes */
    for(i=0U; i<pcm_nRecVarCount; i++)
    {
        /* variable size */
        pMessageIO = FMSTR_ValueFromBuffer8(&sz, pMessageIO);
        
        pcm_pRecVarSize[i] = sz;
        nRecVarsetSize += sz;
        
        /* variable address */
        pMessageIO = FMSTR_AddressFromBuffer(&pcm_pRecVarAddr[i], pMessageIO);

        /* valid numeric variable sizes only */
        if(sz == 0U || sz > 8U)
        {
            return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVSIZE);
        }

#if FMSTR_CFG_BUS_WIDTH > 1U
        /* even sizes only */
        if(sz & 0x1)
        {
            return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVSIZE);
        }
#endif
        
#if FMSTR_USE_TSA && FMSTR_USE_TSA_SAFETY
        if(!FMSTR_CheckTsaSpace(pcm_pRecVarAddr[i], (FMSTR_SIZE8)sz, 0U))
        {
            return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_EACCESS);
        }
#endif
    }

    /* fast recorder handles trigger by itself */
#if !FMSTR_USE_FASTREC
    /* any trigger? */
    pcm_pCompareFunc = NULL;
    if(pcm_nRecTriggerMode)
    {
        /* access to trigger variable? */
#if FMSTR_USE_TSA && FMSTR_USE_TSA_SAFETY
        if(!FMSTR_CheckTsaSpace(pcm_nTrgVarAddr, (FMSTR_SIZE8)pcm_nTrgVarSize, 0U))
        {
            return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_EACCESS);
        }
#endif
        /* get compare function */
        switch(pcm_nTrgVarSize)
        {
#if FMSTR_CFG_BUS_WIDTH == 1U
        case 1: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare8S : FMSTR_Compare8U; break;
#endif
        case 2: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare16S : FMSTR_Compare16U; break;
        case 4: pcm_pCompareFunc = pcm_bTrgVarSigned ? FMSTR_Compare32S : FMSTR_Compare32U; break;
        
        /* invalid trigger variable size  */
        default:
            return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVSIZE);
        }
    }
#endif /* !FMSTR_USE_FASTREC */
    
    /* total recorder buffer length in native sizeof units (=bytes on most platforms) */
    blen = (FMSTR_SIZE) (pcm_wRecTotalSmps * nRecVarsetSize / FMSTR_CFG_BUS_WIDTH);

    /* recorder memory available? */
    if(blen > pcm_wRecBuffSize)
    {
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_INVSIZE);
    }

    /* remember the effective end of circular buffer */
    pcm_dwRecEndBuffPtr = pcm_nRecBuffAddr + blen;

#if FMSTR_USE_FASTREC
    if(!FMSTR_SetUpFastRec())
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_FASTRECERR);
#endif

    /* everything is okay    */
    pcm_wRecFlags.flg.bIsConfigured = 1U;

    return FMSTR_ConstToBuffer8(pResponse, FMSTR_STS_OK);
}

/**************************************************************************//*!
*
* @brief    Abort and de-initialize recorder
*
******************************************************************************/

void FMSTR_AbortRec(void)
{
    /* clear flags */
    pcm_wRecFlags.all = 0U;
}

/**************************************************************************//*!
*
* @brief    Check wether given memory region is inside the recorder buffer
*
* @param    dwAddr - address of the memory to be checked
* @param    wSize  - size of the memory to be checked
*
* @return   This function returns non-zero if user space is in recorder buffer
*
* This function is called as a pert of TSA-checking process when the PC host
* is requesting memory contents
*
******************************************************************************/

FMSTR_BOOL FMSTR_IsInRecBuffer(FMSTR_ADDR dwAddr, FMSTR_SIZE8 nSize)
{
    FMSTR_BOOL bRet = 0U;
    
    if(dwAddr >= pcm_nRecBuffAddr)
    {
        bRet = (dwAddr + nSize) <= (pcm_nRecBuffAddr + FMSTR_GetRecBuffSize());
    }
    
    return bRet;
}

/**************************************************************************//*!
*
* @brief    Get recorder memory size 
*
* @return   Recorder memory size in native sizeof units (=bytes on most platforms)
*
******************************************************************************/

FMSTR_SIZE FMSTR_GetRecBuffSize()
{
#if FMSTR_REC_OWNBUFF || FMSTR_USE_FASTREC
    return pcm_wRecBuffSize;
#else
    return (FMSTR_SIZE) FMSTR_REC_BUFF_SIZE;
#endif
}

/**************************************************************************//*!
*
* @brief    API: Pull the trigger of the recorder
*
* This function starts the post-trigger stop countdown
*
******************************************************************************/

void FMSTR_TriggerRec(void)
{
    if(!pcm_wRecFlags.flg.bIsStopping)
    {
        pcm_wRecFlags.flg.bIsStopping = 1U;
        pcm_wStoprecCountDown = pcm_wRecPostTrigger;
        
#if FMSTR_USE_FASTREC
        FMSTR_TriggerFastRec();
#endif
    }
}

/**************************************************************************//*!
*
* @brief    Handling STARTREC command
*
* @param    pMessageIO - original command (in) and response buffer (out) 
*
* @return   As all command handlers, the return value should be the length
*           of the response filled into the buffer (including status byte)
*
* This function starts recording (initializes internal recording variables 
* and flags)
*
******************************************************************************/

FMSTR_BPTR FMSTR_StartRec(FMSTR_BPTR pMessageIO)
{
    /* must be configured */
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STC_NOTINIT);
    }
        
    /* already running ? */
    if(pcm_wRecFlags.flg.bIsRunning)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STS_RECRUN);
    }
    
    /* initialize write pointer */
    pcm_dwRecWritePtr = pcm_nRecBuffAddr;
    
    /* current (first) sample index */
    pcm_wRecBuffStartIx = 0U;
    
    /* initialize time divisor */
    pcm_wRecTimeDivCtr = 0U;
    
    /* initiate virgin cycle */
    pcm_wRecFlags.flg.bIsStopping = 0U;          /* no trigger active */
    pcm_wRecFlags.flg.bTrgCrossActive = 0U;      /* waiting for threshold crossing */
    pcm_wRecFlags.flg.bInvirginCycle = 1U;       /* initial cycle */

    /* start fast recorder */
#if FMSTR_USE_FASTREC
    FMSTR_StartFastRec();
#endif
    
    /* run now */
    pcm_wRecFlags.flg.bIsRunning = 1U;           /* is running now! */

    return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STS_OK);
}

/**************************************************************************//*!
*
* @brief    Handling STOPREC command
*
* @param    pMessageIO - original command (in) and response buffer (out) 
*
* @return   As all command handlers, the return value should be the length
*           of the response filled into the buffer (including status byte)
*
* This function stops recording (same as manual trigger)
*
******************************************************************************/

FMSTR_BPTR FMSTR_StopRec(FMSTR_BPTR pMessageIO)
{
    /* must be configured */
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STC_NOTINIT);
    }
        
    /* already stopped ? */
    if(!pcm_wRecFlags.flg.bIsRunning)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STS_RECDONE);
    }
    
    /* simulate trigger */
    FMSTR_TriggerRec();

    return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STS_OK);
}

/**************************************************************************//*!
*
* @brief    Handling GETRECSTS command
*
* @param    pMessageIO - original command (in) and response buffer (out) 
*
* @return   As all command handlers, the return value should be the buffer 
*           pointer where the response output finished (except checksum)
*
* This function returns current recorder status
*
******************************************************************************/

FMSTR_BPTR FMSTR_GetRecStatus(FMSTR_BPTR pMessageIO)
{
    /* must be configured */
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STC_NOTINIT);
    }
        
    /* get run/stop status */
    return FMSTR_ConstToBuffer8(pMessageIO, (FMSTR_U8)(pcm_wRecFlags.flg.bIsRunning ? 
        FMSTR_STS_RECRUN : FMSTR_STS_RECDONE));
}

/**************************************************************************//*!
*
* @brief    Handling GETRECBUFF and GETRECBUFF_EX command
*
* @param    pMessageIO - original command (in) and response buffer (out) 
*
* @return   As all command handlers, the return value should be the buffer 
*           pointer where the response output finished (except checksum)
*
* This function returns recorder buffer information
*
******************************************************************************/

FMSTR_BPTR FMSTR_GetRecBuff(FMSTR_BPTR pMessageIO)
{
    /* must be configured */
    if(!pcm_wRecFlags.flg.bIsConfigured)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STC_NOTINIT);
    }
    
    /* must be stopped */
    if(pcm_wRecFlags.flg.bIsRunning)
    {
        return FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STC_SERVBUSY);
    }
    
#if FMSTR_USE_FASTREC
    FMSTR_GetFastRecBuff();
#endif
    
    /* fill the return info */
    pMessageIO = FMSTR_ConstToBuffer8(pMessageIO, FMSTR_STS_OK);
    pMessageIO = FMSTR_AddressToBuffer(pMessageIO, pcm_nRecBuffAddr);
    
    return FMSTR_ValueToBuffer16(pMessageIO, pcm_wRecBuffStartIx);
}

/* now follows the sampling routines, skip that if FastRecorder is used */
#if !FMSTR_USE_FASTREC

/**************************************************************************//*!
*
* @brief    Compare macro used in trigger detection
*
* @param    v - original command 
* @param    t - response buffer
*
* @return   zero when value is lower than threshold.
* @return   non-zero when value is greater than or equal as treshold
*
******************************************************************************/

#define CMP(v,t) ((FMSTR_BOOL)(((v) < (t)) ? 0 : 1))

#if FMSTR_CFG_BUS_WIDTH == 1U

static FMSTR_BOOL FMSTR_Compare8S()
{
    return CMP(FMSTR_GetS8(pcm_nTrgVarAddr), pcm_uTrgThreshold.s8);
}

static FMSTR_BOOL FMSTR_Compare8U()
{
    return CMP(FMSTR_GetU8(pcm_nTrgVarAddr), pcm_uTrgThreshold.u8);
}

#endif

static FMSTR_BOOL FMSTR_Compare16S()
{
    return CMP(FMSTR_GetS16(pcm_nTrgVarAddr), pcm_uTrgThreshold.s16);
}

static FMSTR_BOOL FMSTR_Compare16U()
{
    return CMP(FMSTR_GetU16(pcm_nTrgVarAddr), pcm_uTrgThreshold.u16);
}

static FMSTR_BOOL FMSTR_Compare32S()
{
    return CMP(FMSTR_GetS32(pcm_nTrgVarAddr), pcm_uTrgThreshold.s32);
}

static FMSTR_BOOL FMSTR_Compare32U()
{
    return CMP(FMSTR_GetU32(pcm_nTrgVarAddr), pcm_uTrgThreshold.u32);
}

/**************************************************************************//*!
*
* @brief    API: Recorder worker routine - can be called from application's timer ISR
*
*
* This returns quickly if recorder is not running, otherwise it calls quite lengthy 
* recorder routine which does all the recorder work (sampling, triggering)
*
******************************************************************************/

#if defined(FMSTR_PLATFORM_56F8xxx) || defined(FMSTR_PLATFORM_56F8xx)
#pragma interrupt called
#endif

void FMSTR_Recorder(void)
{
    /* recorder not active */
    if(!pcm_wRecFlags.flg.bIsRunning)
    {
        return ;
    }
    
    /* do the hard work      */
    FMSTR_Recorder2();
}

/**************************************************************************//*!
*
* @brief    Recorder function called when recorder is active
*
******************************************************************************/

#if defined(FMSTR_PLATFORM_56F8xxx) || defined(FMSTR_PLATFORM_56F8xx)
#pragma interrupt called
#endif

static void FMSTR_Recorder2(void)
{
    FMSTR_SIZE8 sz;
    FMSTR_BOOL cmp;
    FMSTR_U8 i;
    
    /* skip this call ? */
    if(pcm_wRecTimeDivCtr)
    {
        /* maybe next time... */
        pcm_wRecTimeDivCtr--;
        return;
    }
    
    /* re-initialize divider */
    pcm_wRecTimeDivCtr = pcm_wRecTimeDiv;

    /* take snapshot of variable values */
    for (i=0U; i<pcm_nRecVarCount; i++)
    {
        sz = pcm_pRecVarSize[i];
        FMSTR_CopyMemory(pcm_dwRecWritePtr, pcm_pRecVarAddr[i], sz);
        sz /= FMSTR_CFG_BUS_WIDTH;
        pcm_dwRecWritePtr += sz;
    }
    
    /* another sample taken (startIx "points" after sample just taken) */
    /* i.e. it points to the oldest sample */
    pcm_wRecBuffStartIx++;
    
    /* wrap around (circular buffer) ? */
    if(pcm_dwRecWritePtr >= pcm_dwRecEndBuffPtr)
    {   
        pcm_dwRecWritePtr = pcm_nRecBuffAddr;
        pcm_wRecFlags.flg.bInvirginCycle = 0U;
        pcm_wRecBuffStartIx = 0U;
    }

    /* no trigger testing in virgin cycle */
    if(pcm_wRecFlags.flg.bInvirginCycle)
    {
        return;
    }
    
    /* test trigger condition if still running */
    if(!pcm_wRecFlags.flg.bIsStopping && pcm_pCompareFunc != NULL)
    {
        /* compare trigger threshold */
        cmp = pcm_pCompareFunc();
        
        /* negated logic (falling-edge) ? */
        if(pcm_nRecTriggerMode == 2U)
        {
            cmp = !cmp;
        }
        
        /* above threshold ? */
        if(cmp)
        {
            /* were we at least once below threshold ? */
            if(pcm_wRecFlags.flg.bTrgCrossActive)
            {
                /* EDGE TRIGGER ! */
                FMSTR_TriggerRec();
            }
        }
        else
        {
            /* we got bellow threshold, now wait for being above threshold */
            pcm_wRecFlags.flg.bTrgCrossActive = 1U;
        }
    }
    
    /* in stopping mode ? (note that this bit might have been set just above!) */
    if(pcm_wRecFlags.flg.bIsStopping)
    {
        /* count down post-trigger samples expired ? */
        if(!pcm_wStoprecCountDown)
        {
            /* STOP RECORDER */
            pcm_wRecFlags.flg.bIsRunning = 0U;
            return;
        }
        
        /* perhaps next time */
        pcm_wStoprecCountDown--;
    }
}

#endif /* !FMSTR_USE_FASTREC */

#else /* FMSTR_USE_RECORDER */

/* use void recorder API functions */
void FMSTR_Recorder(void) 
{ 
}

void FMSTR_TriggerRec(void) 
{ 
}

void FMSTR_SetUpRecBuff(FMSTR_ADDR pBuffer, FMSTR_SIZE wBuffSize) 
{ 
	FMSTR_UNUSED(pBuffer);
	FMSTR_UNUSED(wBuffSize);
}

/*lint -efile(766, freemaster_protocol.h) include file is not used in this case */

#endif /* FMSTR_USE_RECORDER */


