/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_pipes.c
*
* @brief  FreeMASTER lossless "stream" communication 
*
* @version 1.0.3.0
* 
* @date Apr-11-2007
* 
*******************************************************************************
*
* This file contains the FreeMASTER PIPE implementation, whcih enables a
* lossless data I/O streams between PC and embedded application
* 
*******************************************************************************/

#include "freemaster.h"
#include "freemaster_private.h"
#include "freemaster_protocol.h"

#if FMSTR_USE_PIPES

/***********************************
*  local variables 
***********************************/

/* runtime flags */
typedef union 
{
    FMSTR_FLAGS all;
    
    struct 
    {
        unsigned bExpectOdd : 1;     /* now expecting even round */
        unsigned bInComm : 1;      /* in protocol handler now */
        unsigned bLocked : 1;      /* data buffer access is locked */
    } flg;
    
} FMSTR_PIPE_FLAGS;

typedef struct 
{
    FMSTR_ADDR pBuff;
    FMSTR_PIPE_SIZE nSize;
    FMSTR_PIPE_SIZE nWP;
    FMSTR_PIPE_SIZE nRP;
    
} FMSTR_PIPE_BUFF;

typedef struct 
{
    /* pipe configuration */
    FMSTR_PIPE_BUFF rx;
    FMSTR_PIPE_BUFF tx;
    FMSTR_PIPE_PORT nPort;
    FMSTR_PPIPEFUNC pCallback;

    /* runtime information */    
    FMSTR_PIPE_FLAGS flags;
    FMSTR_U8 nLastBytesReceived;
} FMSTR_PIPE;

static FMSTR_PIPE pcm_pipes[FMSTR_MAX_PIPES_COUNT];

/***********************************
*  local functions 
***********************************/

static FMSTR_PIPE* FMSTR_FindPipe(FMSTR_PIPE_PORT nPort);
static FMSTR_PIPE_SIZE FMSTR_PipeGetBytesFree(FMSTR_PIPE_BUFF* pbuff);
static FMSTR_PIPE_SIZE FMSTR_PipeGetBytesReady(FMSTR_PIPE_BUFF* pbuff);
static void FMSTR_PipeDiscardBytes(FMSTR_PIPE_BUFF* pbuff, FMSTR_SIZE8 count);
static FMSTR_BPTR FMSTR_PipeReceive(FMSTR_BPTR pMessageIO, FMSTR_PIPE* pp, FMSTR_SIZE8 size);
static FMSTR_BPTR FMSTR_PipeTransmit(FMSTR_BPTR pMessageIO, FMSTR_PIPE* pp, FMSTR_SIZE8 size);

/**************************************************************************//*!
*
* @brief  Initialization of pipes layer
*
******************************************************************************/

void FMSTR_InitPipes(void)
{
    FMSTR_INDEX i;
    
    for(i=0; i<FMSTR_MAX_PIPES_COUNT; i++)
        pcm_pipes[i].nPort = 0;
}

/**************************************************************************//*!
*
* @brief  API: Opening the pipe
*
******************************************************************************/

FMSTR_HPIPE FMSTR_PipeOpen(FMSTR_PIPE_PORT nPort, FMSTR_PPIPEFUNC pCallback,
                           FMSTR_ADDR pRxBuff, FMSTR_PIPE_SIZE nRxSize, 
                           FMSTR_ADDR pTxBuff, FMSTR_PIPE_SIZE nTxSize)
{
    FMSTR_PIPE* pp = &pcm_pipes[0];
    FMSTR_INDEX ifree = -1;
    FMSTR_INDEX i;
    
    for(i=0; i<FMSTR_MAX_PIPES_COUNT; i++, pp++)
    {
        /* find first free pipe */
        if(pp->nPort == 0 && ifree < 0)
            ifree = i;
        /* look for existing pipe with the same port */
        if(pp->nPort == nPort)
            break;
    }
    
    /* pipe not found */
    if(i >= FMSTR_MAX_PIPES_COUNT)
    {
        /* create new pipe */
        if(ifree >= 0)
            pp = &pcm_pipes[ifree];
        /* no slot for creating pipe */
        else
            return NULL;
    }

    /* disable pipe (just in case the interrupt would come now) */
    pp->nPort = 0;
    
    /* initialize pipe */
    pp->rx.pBuff = pRxBuff;
    pp->rx.nSize = nRxSize;
    pp->rx.nWP = 0;
    pp->rx.nRP = 0;
    pp->tx.pBuff = pTxBuff;
    pp->tx.nSize = nTxSize;
    pp->tx.nWP = 0;
    pp->tx.nRP = 0;
    pp->flags.all = 0;
    pp->pCallback = pCallback;
    pp->nPort = nPort;
    
    return (FMSTR_HPIPE) pp;
}

/**************************************************************************//*!
*
* @brief  PIPE API: Close pipe
*
******************************************************************************/

void FMSTR_PipeClose(FMSTR_HPIPE hpipe)
{
    FMSTR_PIPE* pp = (FMSTR_PIPE*) hpipe;
    
    /* un-initialize pipe */
    if(pp != NULL)
        pp->nPort = 0;
}

/**************************************************************************//*!
*
* @brief  PIPE API: Write data to a pipe
*
******************************************************************************/

FMSTR_PIPE_SIZE FMSTR_PipeWrite(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size)
{
    FMSTR_PIPE* pp = (FMSTR_PIPE*) hpipe;
    FMSTR_PIPE_BUFF* pbuff = &pp->tx;
    FMSTR_PIPE_SIZE total = FMSTR_PipeGetBytesFree(pbuff);
    FMSTR_PIPE_SIZE s;

    /* when invalid address is given, return number of bytes free */
    if(addr)
    {
        /* only fill the free space */
        if(size > total)
            size = total;
        else
            total = size;
        
        /* frame to rest of cyclic buffer */
        if(size > 0)
        {
            /* total bytes available in the rest of buffer */
            s = (pbuff->nSize - pbuff->nWP) * FMSTR_CFG_BUS_WIDTH;
            if(s > (FMSTR_PIPE_SIZE) size)
                s = (FMSTR_PIPE_SIZE) size;
            
            /* get the bytes */
            FMSTR_CopyMemory(pbuff->pBuff + pbuff->nWP, addr, (FMSTR_SIZE8) s);
            addr += s / FMSTR_CFG_BUS_WIDTH;
            
            /* advance & wrap pointer */
            pbuff->nWP += s / FMSTR_CFG_BUS_WIDTH;
            if(pbuff->nWP >= pbuff->nSize)
                pbuff->nWP = 0;
        
            /* rest of frame to a (wrapped) beggining of buffer */
            size -= (FMSTR_SIZE8) s;
            if(size > 0)
            {
                FMSTR_CopyMemory(pbuff->pBuff + pbuff->nWP, addr, (FMSTR_SIZE8) size);
                pbuff->nWP += size / FMSTR_CFG_BUS_WIDTH;
            }
        }
    }
    
    return total;
}

/**************************************************************************//*!
*
* @brief  PIPE API: Read data from a pipe
*
******************************************************************************/

FMSTR_PIPE_SIZE FMSTR_PipeRead(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size)
{
    FMSTR_PIPE* pp = (FMSTR_PIPE*) hpipe;
    FMSTR_PIPE_BUFF* pbuff = &pp->rx;
    FMSTR_PIPE_SIZE total = FMSTR_PipeGetBytesReady(pbuff);
    FMSTR_PIPE_SIZE s;

    /* when invalid address is given, return number of bytes available */
    if(addr)
    {
        /* only return what we have */
        if(size > total)
            size = total;
        else
            total = size;
        
        /* rest of cyclic buffer */
        if(size > 0)
        {
            
            /* total bytes available in the rest of buffer */
            s = (pbuff->nSize - pbuff->nRP) * FMSTR_CFG_BUS_WIDTH;
            if(s > (FMSTR_PIPE_SIZE) size)
                s = (FMSTR_PIPE_SIZE) size;
            
            /* put bytes */
            FMSTR_CopyMemory(addr, pbuff->pBuff + pbuff->nRP, (FMSTR_SIZE8) s);
            addr += s / FMSTR_CFG_BUS_WIDTH;
            
            /* advance & wrap pointer */
            pbuff->nRP += s / FMSTR_CFG_BUS_WIDTH;
            if(pbuff->nRP >= pbuff->nSize)
                pbuff->nRP = 0;
        
            /* rest of frame to a (wrapped) beggining of buffer */
            size -= (FMSTR_SIZE8) s;
            if(size > 0)
            {
                FMSTR_CopyMemory(addr, pbuff->pBuff + pbuff->nRP, (FMSTR_SIZE8) size);
                pbuff->nRP += size / FMSTR_CFG_BUS_WIDTH;
            }
        }
    }
    
    return total;
}

/**************************************************************************//*!
*
* @brief  Find pipe by port number
*
******************************************************************************/

static FMSTR_PIPE* FMSTR_FindPipe(FMSTR_PIPE_PORT nPort)
{
    FMSTR_PIPE* pp = &pcm_pipes[0];
    FMSTR_INDEX i;
    
    for(i=0; i<FMSTR_MAX_PIPES_COUNT; i++, pp++)
    {
        /* look for existing pipe with the same port */
        if(pp->nPort == nPort)
            return pp;
    }
    
    return NULL;
}

/**************************************************************************//*!
*
* @brief  Get number of bytes free in the buffer
*
******************************************************************************/

static FMSTR_PIPE_SIZE FMSTR_PipeGetBytesFree(FMSTR_PIPE_BUFF* pbuff)
{
    FMSTR_PIPE_SIZE free;

    if(pbuff->nWP < pbuff->nRP)
    {
        free = pbuff->nRP - pbuff->nWP;
    }
    else
    {
        free = pbuff->nSize - pbuff->nWP + pbuff->nRP;
    }
    
    /* never let WP reach RP */
    free--;
    
    return free * FMSTR_CFG_BUS_WIDTH;
}

static FMSTR_PIPE_SIZE FMSTR_PipeGetBytesReady(FMSTR_PIPE_BUFF* pbuff)
{
    FMSTR_PIPE_SIZE full;

    if(pbuff->nWP >= pbuff->nRP)
    {
        full = pbuff->nWP - pbuff->nRP;
    }
    else
    {
        full = pbuff->nSize - pbuff->nRP + pbuff->nWP;
    }
    
    return full * FMSTR_CFG_BUS_WIDTH;
}

static void FMSTR_PipeDiscardBytes(FMSTR_PIPE_BUFF* pbuff, FMSTR_SIZE8 count)
{
    FMSTR_PIPE_SIZE rest = pbuff->nSize - pbuff->nRP;
    FMSTR_PIPE_SIZE total, rp;
    
    total = FMSTR_PipeGetBytesReady(pbuff);
    if(count > total)
        count = total;
    
    count /= FMSTR_CFG_BUS_WIDTH;

    /* will RP wrap? */
    if(rest <= count)
    {
        rp = count - rest;
    }
    else
    {
        rp = pbuff->nRP + count;
    }
        
    pbuff->nRP = rp;
}

// get data from frame into our Rx buffer, we are already sure it fits

static FMSTR_BPTR FMSTR_PipeReceive(FMSTR_BPTR pMessageIO, FMSTR_PIPE* pp, FMSTR_SIZE8 size)
{
    FMSTR_PIPE_BUFF* pbuff = &pp->rx;
    FMSTR_PIPE_SIZE s;
    
    /* frame to rest of cyclic buffer */
    if(size > 0)
    {
        /* total bytes available in the rest of buffer */
        s = (pbuff->nSize - pbuff->nWP) * FMSTR_CFG_BUS_WIDTH;
        if(s > (FMSTR_PIPE_SIZE) size)
            s = (FMSTR_PIPE_SIZE) size;
        
        /* get the bytes */
        pMessageIO = FMSTR_CopyFromBuffer(pbuff->pBuff + pbuff->nWP, pMessageIO, (FMSTR_SIZE8) s);
        
        /* advance & wrap pointer */
        pbuff->nWP += s / FMSTR_CFG_BUS_WIDTH;
        if(pbuff->nWP >= pbuff->nSize)
            pbuff->nWP = 0;
    
        /* rest of frame to a (wrapped) beggining of buffer */
        size -= (FMSTR_SIZE8) s;
        if(size > 0)
        {
            pMessageIO = FMSTR_CopyFromBuffer(pbuff->pBuff + pbuff->nWP, pMessageIO, size);
            pbuff->nWP += size / FMSTR_CFG_BUS_WIDTH;
        }
    }
    
    return pMessageIO;
}

// put data into the comm buffer, wa are already sure it fits, buffer's RP is not modified

static FMSTR_BPTR FMSTR_PipeTransmit(FMSTR_BPTR pMessageIO, FMSTR_PIPE* pp, FMSTR_SIZE8 size)
{
    FMSTR_PIPE_BUFF* pbuff = &pp->tx;
    FMSTR_PIPE_SIZE s, nRP = pbuff->nRP;;
    
    /* frame to rest of cyclic buffer */
    if(size > 0)
    {
        /* total bytes available in the rest of buffer */
        s = (pbuff->nSize - nRP) * FMSTR_CFG_BUS_WIDTH;
        if(s > (FMSTR_PIPE_SIZE) size)
            s = (FMSTR_PIPE_SIZE) size;
        
        /* put bytes */
        pMessageIO = FMSTR_CopyToBuffer(pMessageIO, pbuff->pBuff + nRP, (FMSTR_SIZE8) s);
        
        /* advance & wrap pointer */
        nRP += s / FMSTR_CFG_BUS_WIDTH;
        if(nRP >= pbuff->nSize)
            nRP = 0;
    
        /* rest of frame to a (wrapped) beggining of buffer */
        size -= (FMSTR_SIZE8) s;
        if(size > 0)
        {
            pMessageIO = FMSTR_CopyToBuffer(pMessageIO, pbuff->pBuff + nRP, size);
        }
    }
    
    return pMessageIO;
}


/**************************************************************************//*!
*
* @brief  Handling PIPE commands
*
* @param  pMessageIO - original command (in) and response buffer (out) 
*
******************************************************************************/

FMSTR_BPTR FMSTR_PipeFrame(FMSTR_BPTR pMessageIO)
{
    FMSTR_BPTR pResponse = pMessageIO;
    FMSTR_U8 i, nFrameLen, nByte, nPort;
    FMSTR_PIPE* pp;
    
    /* skip command byte */
    pMessageIO = FMSTR_SkipInBuffer(pMessageIO, 1);
    
    /* get frame length */
    pMessageIO = FMSTR_ValueFromBuffer8(&nFrameLen, pMessageIO);
    
    /* need at least port number and tx-discard bytes */
    if(nFrameLen < 1)
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_PIPEERR);
    
    /* get port number and even/odd flag */
    pMessageIO = FMSTR_ValueFromBuffer8(&nPort, pMessageIO);

    /* get pipe by port */
    pp = FMSTR_FindPipe(nPort & 0x7f);

    /* pipe port must exist (i.e. be open) */    
    if(!pp)
        return FMSTR_ConstToBuffer8(pResponse, FMSTR_STC_PIPEERR);
    
    /* data-in are valid only in "matching" request (even to even, odd to odd) */
    if(nPort & 0x80)
    {
        if(!pp->flags.flg.bExpectOdd)
            nFrameLen = 0;
        else
            pp->flags.flg.bExpectOdd = !pp->flags.flg.bExpectOdd;
        
    }
    else
    {
        if(pp->flags.flg.bExpectOdd)
            nFrameLen = 0;
        else
            pp->flags.flg.bExpectOdd = !pp->flags.flg.bExpectOdd;
    }    

    /* process received data */
    if(nFrameLen > 0)
    {
        /* first byte tells me how many output bytes can be discarded from my 
           pipe-transmit buffer (this is how PC acknowledges how many bytes it 
           received and saved from the last response) */
        pMessageIO = FMSTR_ValueFromBuffer8(&nByte, pMessageIO);
           
        /* discard bytes from pipe's transmit buffer */
        if(nByte)
            FMSTR_PipeDiscardBytes(&pp->tx, nByte);
        
        /* next come (nFrameLen-2) bytes to be received */
        if(nFrameLen > 2)
        {
            /* how many bytes may I accept? */
            FMSTR_PIPE_SIZE rxFree = FMSTR_PipeGetBytesFree(&pp->rx);
            /* how many bytes PC want to push? */
            FMSTR_PIPE_SIZE rxToRead = nFrameLen - 2;
            /* round to bus width */
            rxToRead /= FMSTR_CFG_BUS_WIDTH;
            rxToRead *= FMSTR_CFG_BUS_WIDTH;
            
            /* get the lower of the two numbers */
            if(rxFree < rxToRead)
                rxToRead = rxFree;
            
            /* get frame data */
            pMessageIO = FMSTR_PipeReceive(pMessageIO, pp, (FMSTR_SIZE8) rxToRead);
            
            /* this is the number to be returned to PC to inform it how
               many bytes it may discard in his transmit buffer */
            pp->nLastBytesReceived = rxToRead;
        }
        else
        {
            /* no bytes received */
            pp->nLastBytesReceived = 0;
        }
    }
    
    /* now call the pipe's handler, it may read or write data */
    if(pp->pCallback)
    {
        pp->flags.flg.bInComm = 1;
        pp->pCallback((FMSTR_HPIPE) pp);
        pp->flags.flg.bInComm = 0;
    }
    
    /* now put our output data */
    {
        /* how many bytes are waiting to be sent? */
        FMSTR_PIPE_SIZE txAvail = FMSTR_PipeGetBytesReady(&pp->tx);
        /* how many bytes I can safely put? */
        FMSTR_PIPE_SIZE txToSend = FMSTR_COMM_BUFFER_SIZE - 3;
        /* round to bus width */
        txToSend /= FMSTR_CFG_BUS_WIDTH;
        txToSend *= FMSTR_CFG_BUS_WIDTH;
        
        /* get the lower of two values */
        if(txAvail < txToSend)
            txToSend = txAvail;
        
        /* build frame length */
        nFrameLen = ((FMSTR_U8)txToSend) + 2;
        
        /* send pipe's transmit data back */
        pResponse = FMSTR_ConstToBuffer8(pResponse, FMSTR_STS_OK | FMSTR_STSF_VARLEN);
        pResponse = FMSTR_ValueToBuffer8(pResponse, nFrameLen);
        pResponse = FMSTR_ValueToBuffer8(pResponse, nPort);
    
        /* inform PC how many bytes it may discard from its pipe's transmit buffer */
        nByte = pp->nLastBytesReceived;
        pResponse = FMSTR_ValueToBuffer8(pResponse, nByte);

        /* put data */    
        if(txToSend)
            pResponse = FMSTR_PipeTransmit(pResponse, pp, txToSend);        
    }
    
    return pResponse;
}

#else /* FMSTR_USE_PIPES */

/* implement void pipe-API functions */

FMSTR_HPIPE FMSTR_PipeOpen(FMSTR_PIPE_PORT nPort, FMSTR_PPIPEFUNC pCallback,
                           FMSTR_ADDR pRxBuff, FMSTR_PIPE_SIZE nRxSize, 
                           FMSTR_ADDR pTxBuff, FMSTR_PIPE_SIZE nTxSize)
{
    FMSTR_UNUSED(nPort);
    FMSTR_UNUSED(pCallback);
    FMSTR_UNUSED(pRxBuff);
    FMSTR_UNUSED(nRxSize);
    FMSTR_UNUSED(pTxBuff);
    FMSTR_UNUSED(nTxSize);
    
    return NULL;
}

void FMSTR_PipeClose(FMSTR_HPIPE hpipe)
{
    FMSTR_UNUSED(hpipe);
}

FMSTR_SIZE FMSTR_PipeWrite(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size)
{
    FMSTR_UNUSED(hpipe);
    FMSTR_UNUSED(addr);
    FMSTR_UNUSED(size);
    
    return 0U;
}

FMSTR_SIZE FMSTR_PipeRead(FMSTR_HPIPE hpipe, FMSTR_ADDR addr, FMSTR_PIPE_SIZE size)
{
    FMSTR_UNUSED(hpipe);
    FMSTR_UNUSED(addr);
    FMSTR_UNUSED(size);
    
    return 0U;
}

/*lint -efile(766, freemaster_protocol.h) include file is not used in this case */

#endif /* FMSTR_USE_PIPES */
