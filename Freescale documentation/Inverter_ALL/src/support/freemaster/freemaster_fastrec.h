/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2006 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
****************************************************************************//*!
*
* @file   freemaster_fastrec.h
*
* @brief  FreeMASTER Fast Recorder implementation for 56F8xxx.
*
* @version 1.0.3.0
* 
* @date Feb-6-2007
* 
*******************************************************************************/

#ifndef __FREEMASTER_FASTREC_H
#define __FREEMASTER_FASTREC_H

#include "freemaster.h"
#include "freemaster_private.h"
#include "freemaster_rec.h"

#if FMSTR_USE_RECORDER 
#if FMSTR_USE_FASTREC

/*************************************
 Fast recorder global variables 
*************************************/

extern FMSTR_ADDR pcm_dwFastRecWritePtr;
extern FMSTR_ADDR pcm_dwFastRecStartBuffPtr;
extern FMSTR_ADDR pcm_dwFastRecEndBuffPtr;

/*************************************
 Fast recorder internal API
*************************************/

void FMSTR_InitFastRec(void);
FMSTR_BOOL FMSTR_SetUpFastRec(void);
void FMSTR_StartFastRec(void);
void FMSTR_TriggerFastRec(void);
void FMSTR_GetFastRecBuff(void);

/*************************************
 Inline sampling function 
*************************************/

#define FMSTR_FASTREC_BEGIN(do_fdiv) \
{ \
    register FMSTR_U16 flags; \
    register FMSTR_U16 tmp; \
    register FMSTR_U16* pdest; \
    register FMSTR_U16* ptemp; \
    \
    if(do_fdiv) \
    { \
        /* skip this call ? */ \
        if(pcm_wRecTimeDivCtr) \
        { \
            /* maybe next time... */ \
            pcm_wRecTimeDivCtr--; \
            asm { bra skip_all; } \
        } \
        \
        /* re-initialize divider */ \
        pcm_wRecTimeDivCtr = pcm_wRecTimeDiv; \
    } \
    \
    asm \
    { \
        move.w pcm_wRecFlags.all, flags; \
        brclr FMSTR_REC_FLAG_bIsRunning, flags, skip_all; \
        move.l pcm_dwFastRecWritePtr, pdest; \
    }

#define FMSTR_FASTREC_BEGINTRIG() \
    asm \
    { \
        /* triger is disabled during virgin cycle */ \
        brset FMSTR_REC_FLAG_bInvirginCycle, flags, trig_end; \
        \
        /* already in stopping mode? (trigger happened in the past) */ \
        brclr FMSTR_REC_FLAG_bIsStopping, flags, trig_test; \
        \
        /* yes, decrement counter and test if underflown */ \
        dec.w pcm_wStoprecCountDown; \
        \
        /* if zero not yet reached, nothing more to do */ \
        /* NOTE: initial down-counter value is never zero */ \
        bne trig_end; \
        \
        /* do stop now */ \
        bfclr FMSTR_REC_FLAG_bIsRunning, flags; \
        bra trig_end; \
    }

#define FMSTR_FASTREC_IMPLTRIG_FULL(cond) \
    asm { trig_test: } \
    \
    if(cond) \
    { \
        asm \
        { \
            /* tigger armed? */ \
            brclr FMSTR_REC_FLAG_bTrgCrossActive, flags, trig_end; \
            \
            /* pull the trigger now */ \
    	    move.w pcm_wRecPostTrigger, tmp; \
    	    move.w tmp, pcm_wStoprecCountDown; \
    	    bfset FMSTR_REC_FLAG_bIsStopping, flags; \
        } \
	} \
    else \
    { \
        /* trigger is now armed */ \
        asm { bfset FMSTR_REC_FLAG_bTrgCrossActive, flags } \
    }

#define FMSTR_FASTREC_IMPLTRIG_SIMPLE(cond) \
    asm { trig_test: } \
    \
    if(cond) \
    { \
        asm \
        { \
            /* pull the trigger now */ \
    	    move.w pcm_wRecPostTrigger, tmp; \
    	    move.w tmp, pcm_wStoprecCountDown; \
    	    bfset FMSTR_REC_FLAG_bIsStopping, flags; \
        } \
	}

#define FMSTR_FASTREC_IMPLTRIG_IMMEDIATE(cond) \
    asm { trig_test: } \
    \
    if(cond) \
    { \
        asm \
        { \
            /* hard-stop now (no pretrigger will be there) */ \
    	    bfset FMSTR_REC_FLAG_bIsStopping, flags; \
        } \
	}

#define FMSTR_FASTREC_ENDTRIG() \
    asm { trig_end: }

#define FMSTR_FASTREC_TRIGGER_FULL(cond) \
    FMSTR_FASTREC_BEGINTRIG() \
    FMSTR_FASTREC_IMPLTRIG_FULL(cond) \
    FMSTR_FASTREC_ENDTRIG()

#define FMSTR_FASTREC_TRIGGER_SIMPLE(cond) \
    FMSTR_FASTREC_BEGINTRIG() \
    FMSTR_FASTREC_IMPLTRIG_SIMPLE(cond) \
    FMSTR_FASTREC_ENDTRIG()

#define FMSTR_FASTREC_TRIGGER_IMMEDIATE(cond) \
    FMSTR_FASTREC_BEGINTRIG() \
    FMSTR_FASTREC_IMPLTRIG_IMMEDIATE(cond) \
    FMSTR_FASTREC_ENDTRIG()

#define FMSTR_FASTREC_TRIGGER_VOID() \
    FMSTR_FASTREC_BEGINTRIG() \
    asm { trig_test: } \
    FMSTR_FASTREC_ENDTRIG()

#define FMSTR_FASTREC_STDVARS() \
    { \
        register FMSTR_U16* padrs; \
        \
        asm \
        { \
            move.l #>pcm_pRecVarAddr, padrs; \
            move.w pcm_nRecVarCount, tmp; \
            \
            do tmp, copy_loop_end; \
            move.l X:(padrs)+, ptemp; \
            move.w X:(ptemp), tmp; \
            move.w tmp, X:(pdest)+; \
            \
        copy_loop_end: \
        } \
    }

#define FMSTR_FASTREC_VAR16(var16) \
    asm \
    { \
        move.w var16, tmp; \
        move.w tmp, X:(pdest)+; \
    }

#define FMSTR_FASTREC_END() \
    asm \
    { \
        /* compare pdest with a wrap location */ \
        move.l pcm_dwFastRecEndBuffPtr, ptemp; \
        cmpa pdest, ptemp; \
        bgt no_wrap; \
        \
        /* do wrap, reset write pointer to buffer start */ \
        move.l pcm_dwFastRecStartBuffPtr, pdest; \
        \
        /* remember virgin cycle is over (trigger now enabled) */ \
        bfclr FMSTR_REC_FLAG_bInvirginCycle, flags; \
        \
    no_wrap: \
        /* save write pointer back to memory */ \
        move.l pdest, pcm_dwFastRecWritePtr; \
        \
        /* save flags back to memory */ \
        move.w flags, pcm_wRecFlags.all; \
        \
    skip_all: \
    } \
}


inline FMSTR_FastRecorder(register FMSTR_BOOL bTriggerNow)
{
    FMSTR_FASTREC_BEGIN(1)
    FMSTR_FASTREC_STDVARS()
    FMSTR_FASTREC_TRIGGER_FULL(bTriggerNow)
    FMSTR_FASTREC_END()
 }

/* normal recorder call emulated using fast recorder routine */

inline void FMSTR_Recorder(void)
{
    FMSTR_FastRecorder(0);
}

#else /* FMSTR_USE_FASTREC */

/* fast recorder is de-activated, emulate using normal recorder */

inline void FMSTR_FastRecorder(FMSTR_BOOL bTriggerNow)
{
    if(bTriggerNow)
        FMSTR_TriggerRec();
    
    FMSTR_Recorder();
}

#endif /* FMSTR_USE_FASTREC */

#else /* FMSTR_USE_RECORDER */

/* recorder is not implemented, use empty fast-recorder call */

inline void FMSTR_FastRecorder(FMSTR_BOOL bTriggerNow)
{
}

#endif /* FMSTR_USE_RECORDER */
#endif /* __FREEMASTER_FASTREC_H */

