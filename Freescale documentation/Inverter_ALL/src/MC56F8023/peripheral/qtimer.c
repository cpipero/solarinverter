/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: qtimer_8xxx.c$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.16.0$
*
* Description: Source file for the Quad Timer (QT) driver
*
*******************************************************************************/

#include "qs.h"
#include "qtimer.h"
#include "initconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

void qtInit(arch_sTimerChannel *pTimerBase)
{
#pragma unused(pTimerBase)

#if QT_A0_INIT_USED && defined(QTIMER_A0)
	if (pTimerBase == QTIMER_A0) {
		#ifdef QT_A0_ENBL_INIT
			periphMemWrite(QT_A0_ENBL_INIT, &pTimerBase->enbl);
		#endif
		#ifdef QT_A0_CMP1_INIT
			periphMemWrite(QT_A0_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_A0_CMP2_INIT
			periphMemWrite(QT_A0_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_A0_LOAD_INIT
			periphMemWrite(QT_A0_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_A0_CNTR_INIT
			periphMemWrite(QT_A0_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_A0_CMPLD1_INIT
			periphMemWrite(QT_A0_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_A0_CMPLD2_INIT
			periphMemWrite(QT_A0_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_A0_SCR_INIT
			periphMemWrite(QT_A0_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_A0_CTRL_INIT
			periphMemWrite(QT_A0_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_A0_COMSCR_INIT
			periphMemWrite(QT_A0_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_A0_FILT_INIT
			periphMemWrite(QT_A0_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_A1_INIT_USED && defined(QTIMER_A1)
	if (pTimerBase == QTIMER_A1) {
		#ifdef QT_A1_CMP1_INIT
			periphMemWrite(QT_A1_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_A1_CMP2_INIT
			periphMemWrite(QT_A1_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_A1_LOAD_INIT
			periphMemWrite(QT_A1_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_A1_CNTR_INIT
			periphMemWrite(QT_A1_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_A1_CMPLD1_INIT
			periphMemWrite(QT_A1_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_A1_CMPLD2_INIT
			periphMemWrite(QT_A1_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_A1_SCR_INIT
			periphMemWrite(QT_A1_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_A1_CTRL_INIT
			periphMemWrite(QT_A1_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_A1_COMSCR_INIT
			periphMemWrite(QT_A1_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_A1_FILT_INIT
			periphMemWrite(QT_A1_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_A2_INIT_USED && defined(QTIMER_A2)
	if (pTimerBase == QTIMER_A2) {
		#ifdef QT_A2_CMP1_INIT
			periphMemWrite(QT_A2_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_A2_CMP2_INIT
			periphMemWrite(QT_A2_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_A2_LOAD_INIT
			periphMemWrite(QT_A2_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_A2_CNTR_INIT
			periphMemWrite(QT_A2_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_A2_CMPLD1_INIT
			periphMemWrite(QT_A2_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_A2_CMPLD2_INIT
			periphMemWrite(QT_A2_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_A2_SCR_INIT
			periphMemWrite(QT_A2_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_A2_CTRL_INIT
			periphMemWrite(QT_A2_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_A2_COMSCR_INIT
			periphMemWrite(QT_A2_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_A2_FILT_INIT
			periphMemWrite(QT_A2_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_A3_INIT_USED && defined(QTIMER_A3)
	if (pTimerBase == QTIMER_A3) {
		#ifdef QT_A3_CMP1_INIT
			periphMemWrite(QT_A3_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_A3_CMP2_INIT
			periphMemWrite(QT_A3_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_A3_LOAD_INIT
			periphMemWrite(QT_A3_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_A3_CNTR_INIT
			periphMemWrite(QT_A3_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_A3_CMPLD1_INIT
			periphMemWrite(QT_A3_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_A3_CMPLD2_INIT
			periphMemWrite(QT_A3_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_A3_SCR_INIT
			periphMemWrite(QT_A3_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_A3_CTRL_INIT
			periphMemWrite(QT_A3_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_A3_COMSCR_INIT
			periphMemWrite(QT_A3_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_A3_FILT_INIT
			periphMemWrite(QT_A3_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else
#endif

#if QT_B0_INIT_USED && defined(QTIMER_B0)
	if (pTimerBase == QTIMER_B0) {
		#ifdef QT_B0_ENBL_INIT
			periphMemWrite(QT_B0_ENBL_INIT, &pTimerBase->enbl);
		#endif
		#ifdef QT_B0_CMP1_INIT
			periphMemWrite(QT_B0_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_B0_CMP2_INIT
			periphMemWrite(QT_B0_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_B0_LOAD_INIT
			periphMemWrite(QT_B0_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_B0_CNTR_INIT
			periphMemWrite(QT_B0_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_B0_CMPLD1_INIT
			periphMemWrite(QT_B0_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_B0_CMPLD2_INIT
			periphMemWrite(QT_B0_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_B0_SCR_INIT
			periphMemWrite(QT_B0_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_B0_CTRL_INIT
			periphMemWrite(QT_B0_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_B0_COMSCR_INIT
			periphMemWrite(QT_B0_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_B0_FILT_INIT
			periphMemWrite(QT_B0_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_B1_INIT_USED && defined(QTIMER_B1)
	if (pTimerBase == QTIMER_B1) {
		#ifdef QT_B1_CMP1_INIT
			periphMemWrite(QT_B1_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_B1_CMP2_INIT
			periphMemWrite(QT_B1_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_B1_LOAD_INIT
			periphMemWrite(QT_B1_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_B1_CNTR_INIT
			periphMemWrite(QT_B1_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_B1_CMPLD1_INIT
			periphMemWrite(QT_B1_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_B1_CMPLD2_INIT
			periphMemWrite(QT_B1_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_B1_SCR_INIT
			periphMemWrite(QT_B1_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_B1_CTRL_INIT
			periphMemWrite(QT_B1_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_B1_COMSCR_INIT
			periphMemWrite(QT_B1_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_B1_FILT_INIT
			periphMemWrite(QT_B1_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_B2_INIT_USED && defined(QTIMER_B2)
	if (pTimerBase == QTIMER_B2) {
		#ifdef QT_B2_CMP1_INIT
			periphMemWrite(QT_B2_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_B2_CMP2_INIT
			periphMemWrite(QT_B2_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_B2_LOAD_INIT
			periphMemWrite(QT_B2_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_B2_CNTR_INIT
			periphMemWrite(QT_B2_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_B2_CMPLD1_INIT
			periphMemWrite(QT_B2_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_B2_CMPLD2_INIT
			periphMemWrite(QT_B2_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_B2_SCR_INIT
			periphMemWrite(QT_B2_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_B2_CTRL_INIT
			periphMemWrite(QT_B2_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_B2_COMSCR_INIT
			periphMemWrite(QT_B2_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_B2_FILT_INIT
			periphMemWrite(QT_B2_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_B3_INIT_USED && defined(QTIMER_B3)
	if (pTimerBase == QTIMER_B3) {
		#ifdef QT_B3_CMP1_INIT
			periphMemWrite(QT_B3_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_B3_CMP2_INIT
			periphMemWrite(QT_B3_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_B3_LOAD_INIT
			periphMemWrite(QT_B3_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_B3_CNTR_INIT
			periphMemWrite(QT_B3_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_B3_CMPLD1_INIT
			periphMemWrite(QT_B3_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_B3_CMPLD2_INIT
			periphMemWrite(QT_B3_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_B3_SCR_INIT
			periphMemWrite(QT_B3_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_B3_CTRL_INIT
			periphMemWrite(QT_B3_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_B3_COMSCR_INIT
			periphMemWrite(QT_B3_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_B3_FILT_INIT
			periphMemWrite(QT_B3_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else
#endif

#if QT_C0_INIT_USED && defined(QTIMER_C0)
	if (pTimerBase == QTIMER_C0) {
		#ifdef QT_C0_ENBL_INIT
			periphMemWrite(QT_C0_ENBL_INIT, &pTimerBase->enbl);
		#endif
		#ifdef QT_C0_CMP1_INIT
			periphMemWrite(QT_C0_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_C0_CMP2_INIT
			periphMemWrite(QT_C0_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_C0_LOAD_INIT
			periphMemWrite(QT_C0_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_C0_CNTR_INIT
			periphMemWrite(QT_C0_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_C0_CMPLD1_INIT
			periphMemWrite(QT_C0_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_C0_CMPLD2_INIT
			periphMemWrite(QT_C0_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_C0_SCR_INIT
			periphMemWrite(QT_C0_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_C0_CTRL_INIT
			periphMemWrite(QT_C0_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_C0_COMSCR_INIT
			periphMemWrite(QT_C0_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_C0_FILT_INIT
			periphMemWrite(QT_C0_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_C1_INIT_USED && defined(QTIMER_C1)
	if (pTimerBase == QTIMER_C1) {
		#ifdef QT_C1_CMP1_INIT
			periphMemWrite(QT_C1_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_C1_CMP2_INIT
			periphMemWrite(QT_C1_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_C1_LOAD_INIT
			periphMemWrite(QT_C1_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_C1_CNTR_INIT
			periphMemWrite(QT_C1_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_C1_CMPLD1_INIT
			periphMemWrite(QT_C1_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_C1_CMPLD2_INIT
			periphMemWrite(QT_C1_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_C1_SCR_INIT
			periphMemWrite(QT_C1_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_C1_CTRL_INIT
			periphMemWrite(QT_C1_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_C1_COMSCR_INIT
			periphMemWrite(QT_C1_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_C1_FILT_INIT
			periphMemWrite(QT_C1_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_C2_INIT_USED && defined(QTIMER_C2)
	if (pTimerBase == QTIMER_C2) {
		#ifdef QT_C2_CMP1_INIT
			periphMemWrite(QT_C2_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_C2_CMP2_INIT
			periphMemWrite(QT_C2_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_C2_LOAD_INIT
			periphMemWrite(QT_C2_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_C2_CNTR_INIT
			periphMemWrite(QT_C2_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_C2_CMPLD1_INIT
			periphMemWrite(QT_C2_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_C2_CMPLD2_INIT
			periphMemWrite(QT_C2_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_C2_SCR_INIT
			periphMemWrite(QT_C2_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_C2_CTRL_INIT
			periphMemWrite(QT_C2_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_C2_COMSCR_INIT
			periphMemWrite(QT_C2_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_C2_FILT_INIT
			periphMemWrite(QT_C2_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_C3_INIT_USED && defined(QTIMER_C3)
	if (pTimerBase == QTIMER_C3) {
		#ifdef QT_C3_CMP1_INIT
			periphMemWrite(QT_C3_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_C3_CMP2_INIT
			periphMemWrite(QT_C3_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_C3_LOAD_INIT
			periphMemWrite(QT_C3_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_C3_CNTR_INIT
			periphMemWrite(QT_C3_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_C3_CMPLD1_INIT
			periphMemWrite(QT_C3_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_C3_CMPLD2_INIT
			periphMemWrite(QT_C3_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_C3_SCR_INIT
			periphMemWrite(QT_C3_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_C3_CTRL_INIT
			periphMemWrite(QT_C3_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_C3_COMSCR_INIT
			periphMemWrite(QT_C3_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_C3_FILT_INIT
			periphMemWrite(QT_C3_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else
#endif

#if QT_D0_INIT_USED && defined(QTIMER_D0)
	if (pTimerBase == QTIMER_D0) {
		#ifdef QT_D0_ENBL_INIT
			periphMemWrite(QT_D0_ENBL_INIT, &pTimerBase->enbl);
		#endif
		#ifdef QT_D0_CMP1_INIT
			periphMemWrite(QT_D0_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_D0_CMP2_INIT
			periphMemWrite(QT_D0_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_D0_LOAD_INIT
			periphMemWrite(QT_D0_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_D0_CNTR_INIT
			periphMemWrite(QT_D0_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_D0_CMPLD1_INIT
			periphMemWrite(QT_D0_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_D0_CMPLD2_INIT
			periphMemWrite(QT_D0_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_D0_SCR_INIT
			periphMemWrite(QT_D0_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_D0_CTRL_INIT
			periphMemWrite(QT_D0_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_D0_COMSCR_INIT
			periphMemWrite(QT_D0_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_D0_FILT_INIT
			periphMemWrite(QT_D0_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_D1_INIT_USED && defined(QTIMER_D1)
	if (pTimerBase == QTIMER_D1) {
		#ifdef QT_D1_CMP1_INIT
			periphMemWrite(QT_D1_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_D1_CMP2_INIT
			periphMemWrite(QT_D1_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_D1_LOAD_INIT
			periphMemWrite(QT_D1_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_D1_CNTR_INIT
			periphMemWrite(QT_D1_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_D1_CMPLD1_INIT
			periphMemWrite(QT_D1_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_D1_CMPLD2_INIT
			periphMemWrite(QT_D1_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_D1_SCR_INIT
			periphMemWrite(QT_D1_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_D1_CTRL_INIT
			periphMemWrite(QT_D1_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_D1_COMSCR_INIT
			periphMemWrite(QT_D1_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_D1_FILT_INIT
			periphMemWrite(QT_D1_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_D2_INIT_USED && defined(QTIMER_D2)
	if (pTimerBase == QTIMER_D2) {
		#ifdef QT_D2_CMP1_INIT
			periphMemWrite(QT_D2_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_D2_CMP2_INIT
			periphMemWrite(QT_D2_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_D2_LOAD_INIT
			periphMemWrite(QT_D2_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_D2_CNTR_INIT
			periphMemWrite(QT_D2_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_D2_CMPLD1_INIT
			periphMemWrite(QT_D2_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_D2_CMPLD2_INIT
			periphMemWrite(QT_D2_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_D2_SCR_INIT
			periphMemWrite(QT_D2_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_D2_CTRL_INIT
			periphMemWrite(QT_D2_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_D2_COMSCR_INIT
			periphMemWrite(QT_D2_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_D2_FILT_INIT
			periphMemWrite(QT_D2_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_D3_INIT_USED && defined(QTIMER_D3)
	if (pTimerBase == QTIMER_D3) {
		#ifdef QT_D3_CMP1_INIT
			periphMemWrite(QT_D3_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_D3_CMP2_INIT
			periphMemWrite(QT_D3_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_D3_LOAD_INIT
			periphMemWrite(QT_D3_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_D3_CNTR_INIT
			periphMemWrite(QT_D3_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_D3_CMPLD1_INIT
			periphMemWrite(QT_D3_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_D3_CMPLD2_INIT
			periphMemWrite(QT_D3_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_D3_SCR_INIT
			periphMemWrite(QT_D3_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_D3_CTRL_INIT
			periphMemWrite(QT_D3_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_D3_COMSCR_INIT
			periphMemWrite(QT_D3_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_D3_FILT_INIT
			periphMemWrite(QT_D3_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else
#endif

#if QT_0_INIT_USED && defined(QTIMER_0)
	if (pTimerBase == QTIMER_0) {
		#ifdef QT_0_ENBL_INIT
			periphMemWrite(QT_0_ENBL_INIT, &pTimerBase->enbl);
		#endif
		#ifdef QT_0_CMP1_INIT
			periphMemWrite(QT_0_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_0_CMP2_INIT
			periphMemWrite(QT_0_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_0_LOAD_INIT
			periphMemWrite(QT_0_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_0_CNTR_INIT
			periphMemWrite(QT_0_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_0_CMPLD1_INIT
			periphMemWrite(QT_0_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_0_CMPLD2_INIT
			periphMemWrite(QT_0_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_0_SCR_INIT
			periphMemWrite(QT_0_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_0_CTRL_INIT
			periphMemWrite(QT_0_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_0_COMSCR_INIT
			periphMemWrite(QT_0_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_0_FILT_INIT
			periphMemWrite(QT_0_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_1_INIT_USED && defined(QTIMER_1)
	if (pTimerBase == QTIMER_1) {
		#ifdef QT_1_CMP1_INIT
			periphMemWrite(QT_1_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_1_CMP2_INIT
			periphMemWrite(QT_1_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_1_LOAD_INIT
			periphMemWrite(QT_1_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_1_CNTR_INIT
			periphMemWrite(QT_1_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_1_CMPLD1_INIT
			periphMemWrite(QT_1_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_1_CMPLD2_INIT
			periphMemWrite(QT_1_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_1_SCR_INIT
			periphMemWrite(QT_1_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_1_CTRL_INIT
			periphMemWrite(QT_1_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_1_COMSCR_INIT
			periphMemWrite(QT_1_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_1_FILT_INIT
			periphMemWrite(QT_1_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_2_INIT_USED && defined(QTIMER_2)
	if (pTimerBase == QTIMER_2) {
		#ifdef QT_2_CMP1_INIT
			periphMemWrite(QT_2_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_2_CMP2_INIT
			periphMemWrite(QT_2_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_2_LOAD_INIT
			periphMemWrite(QT_2_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_2_CNTR_INIT
			periphMemWrite(QT_2_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_2_CMPLD1_INIT
			periphMemWrite(QT_2_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_2_CMPLD2_INIT
			periphMemWrite(QT_2_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_2_SCR_INIT
			periphMemWrite(QT_2_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_2_CTRL_INIT
			periphMemWrite(QT_2_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_2_COMSCR_INIT
			periphMemWrite(QT_2_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_2_FILT_INIT
			periphMemWrite(QT_2_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else 
#endif

#if QT_3_INIT_USED && defined(QTIMER_3)
	if (pTimerBase == QTIMER_3) {
		#ifdef QT_3_CMP1_INIT
			periphMemWrite(QT_3_CMP1_INIT, &pTimerBase->tmrcmp1);
		#endif
		#ifdef QT_3_CMP2_INIT
			periphMemWrite(QT_3_CMP2_INIT, &pTimerBase->tmrcmp2);
		#endif
		#ifdef QT_3_LOAD_INIT
			periphMemWrite(QT_3_LOAD_INIT, &pTimerBase->tmrload);
		#endif
		#ifdef QT_3_CNTR_INIT
			periphMemWrite(QT_3_CNTR_INIT, &pTimerBase->tmrcntr);
		#endif
		#ifdef QT_3_CMPLD1_INIT
			periphMemWrite(QT_3_CMPLD1_INIT, &pTimerBase->tmrcmpld1);
		#endif
		#ifdef QT_3_CMPLD2_INIT
			periphMemWrite(QT_3_CMPLD2_INIT, &pTimerBase->tmrcmpld2);
		#endif
		#ifdef QT_3_SCR_INIT
			periphMemWrite(QT_3_SCR_INIT, &pTimerBase->tmrscr);
		#endif
		#ifdef QT_3_CTRL_INIT
			periphMemWrite(QT_3_CTRL_INIT, &pTimerBase->tmrctrl);
		#endif
		#ifdef QT_3_COMSCR_INIT
			periphMemWrite(QT_3_COMSCR_INIT, &pTimerBase->tmrcomscr);
		#endif
		#ifdef QT_3_FILT_INIT
			periphMemWrite(QT_3_FILT_INIT, &pTimerBase->filt);
		#endif
	}
	else
#endif

	; /* last else case */
}

#ifdef __cplusplus
}
#endif
