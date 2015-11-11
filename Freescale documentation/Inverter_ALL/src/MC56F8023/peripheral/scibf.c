/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  scibf.c
*
* $Date:      Jan-30-2009$
*
* $Version:   2.3.18.0$
*
* Description: Source file for the SCI Driver. BUFFERED Operations Implementation.
*
*******************************************************************************/

#include "qs.h"

/* we don't care about missing baudrates */
#define SCI_DISABLE_BAUDRATE_WARNING 1

#include "sci.h"
#include "scihl.h"

/* compile this file only if BUFFERED mode is selected */
#if SCI_HIGHLEVEL_MODE == SCI_HIGHLEVEL_MODE_BUFFERED

#ifdef __cplusplus
extern "C" {
#endif

volatile UWord16 sci0_status = 0;      	/* status word */
volatile UWord16 sci1_status = 0;      	/* status word */

/****************************************************
 * global variables used in read/write functions    
 ****************************************************/
 
#ifdef SCI_0

/* RX buffer size must be supplied (otherwise, read operation is not available) */
#ifndef SCI_0_RX_BUFFER_SIZE
#define SCI_0_RX_BUFFER_SIZE 0
#endif

#if SCI_0_RX_BUFFER_SIZE>0
/* RX buffer pointer "may" be supplied (we allocate our one if needed) */
#ifndef SCI_0_RX_BUFFER_PTR
SCI0CHAR SCI_0_RX_BUFFER_PTR[SCI_0_RX_BUFFER_SIZE];
#endif
static volatile Word16 sci0_RxWP;  	/* RX buffer Write Pointer (index) */
static volatile Word16 sci0_RxRP;  	/* RX buffer Read Pointer (index) */
#endif /* SCI_0_RX_BUFFER_SIZE */

/* TX buffer size must be supplied (otherwise, write operation is not available) */
#ifndef SCI_0_TX_BUFFER_SIZE
#define SCI_0_TX_BUFFER_SIZE 0
#endif

#if SCI_0_TX_BUFFER_SIZE>0
/* TX buffer pointer "may" be supplied (we allocate our one if needed) */
#ifndef SCI_0_TX_BUFFER_PTR
SCI0CHAR SCI_0_TX_BUFFER_PTR[SCI_0_TX_BUFFER_SIZE];
#endif
static volatile Word16 sci0_TxWP;  	/* RX buffer Write Pointer (index) */
static volatile Word16 sci0_TxRP;  	/* RX buffer Read Pointer (index) */
#endif /* SCI_0_RX_BUFFER_SIZE */

#endif /* SCI_0 */

#ifdef SCI_1

/* RX buffer size must be supplied (otherwise, read operation is not available) */
#ifndef SCI_1_RX_BUFFER_SIZE
#define SCI_1_RX_BUFFER_SIZE 0
#endif

#if SCI_1_RX_BUFFER_SIZE>0
/* RX buffer pointer "may" be supplied (we allocate our one if needed) */
#ifndef SCI_1_RX_BUFFER_PTR
SCI1CHAR SCI_1_RX_BUFFER_PTR[SCI_1_RX_BUFFER_SIZE];
#endif
static volatile Word16 sci1_RxWP;  	/* RX buffer Write Pointer (index) */
static volatile Word16 sci1_RxRP;  	/* RX buffer Read Pointer (index) */
#endif /* SCI_1_RX_BUFFER_SIZE */

/* TX buffer size must be supplied (otherwise, write operation is not available) */
#ifndef SCI_1_TX_BUFFER_SIZE
#define SCI_1_TX_BUFFER_SIZE 0
#endif

#if SCI_1_TX_BUFFER_SIZE>0
/* TX buffer pointer "may" be supplied (we allocate our one if needed) */
#ifndef SCI_1_TX_BUFFER_PTR
SCI1CHAR SCI_1_TX_BUFFER_PTR[SCI_1_TX_BUFFER_SIZE];
#endif
static volatile Word16 sci1_TxWP;  	/* RX buffer Write Pointer (index) */
static volatile Word16 sci1_TxRP;  	/* RX buffer Read Pointer (index) */
#endif /* SCI_1_RX_BUFFER_SIZE */

#endif /* SCI_1 */

/* disable XONXOFF when macro is undefined */
#ifndef SCI_0_RX_XONXOFF
#define SCI_0_RX_XONXOFF 0
#endif
#ifndef SCI_1_RX_XONXOFF
#define SCI_1_RX_XONXOFF 0
#endif

/* read operation */
#if defined(SCI_0) && SCI_0_RX_BUFFER_SIZE>0

/********************************************************************************
 sci0BufferedRxEnable/Disable - start/stop buffered RX operation
********************************************************************************/

/* enable buffered RX - start receiving into our circular buffer */

void sci0BufferedRxEnable(void)
{
	sci0_RxWP = 0;
	sci0_RxRP = 0;
	
	periphBitClear(SCI_STATUS_RX_BUFFER_LOW | SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, 
		&sci0_status);

	/* clear exception if any */		
	if(ioctl(SCI_0, SCI_GET_ERROR, NULL)) /* read SCI status register */
		ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */

	/* enable RX interrupts */	
	ioctl(SCI_0, SCI_INT_ENABLE, SCI_RX_FULL | SCI_RX_ERROR);
	
	/* call buffer-empty hook (e.g. to set CTS pin on RS232) */
	#ifdef SCI_0_RX_LOWBUFFER_HOOK
	SCI_0_RX_LOWBUFFER_HOOK(false);
	#endif
	
	/* send XON character */
	#if SCI_0_RX_XONXOFF
	ioctl(SCI_0, SCI_SEND_XON, NULL);
	#endif
}

void sci0BufferedRxDisable(void)
{
	/* call buffer-full hook (e.g. to clear CTS pin on RS232) */
	#ifdef SCI_0_RX_LOWBUFFER_HOOK
	SCI_0_RX_LOWBUFFER_HOOK(true);
	#endif
	
	/* send XOFF character */
	#if SCI_0_RX_XONXOFF
	ioctl(SCI_0, SCI_SEND_XOFF, NULL);
	/* wait until XOFF is sent */	
	while(!ioctl(SCI_0, SCI_GET_TX_EMPTY, NULL)) 
		; /* empty loop */ 
	#endif
	
	/* disable TX interrupt */
	ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
}

/* get number of characters ready to read */

Word16 sci0BufferedRxGetLen(void)
{
	register Word16 rxlen;
	
	rxlen = sci0_RxWP - sci0_RxRP;
	if(rxlen < 0)
		rxlen += SCI_0_RX_BUFFER_SIZE;
		
	return rxlen;
}

/* get free space in RX buffer */

Word16 sci0BufferedRxGetFree(void)
{
	register Word16 rxfree;
	
	rxfree = sci0_RxRP - sci0_RxWP - 1;
	if(rxfree < 0)
		rxfree += SCI_0_RX_BUFFER_SIZE;
		
	return rxfree;
}

/* read out the characters in the rx buffer */

Word16 read_SCI_0_BUFFERED(SCI0CHAR *data, UWord16 size)
{
	register Word16 i = 0;
	
	while(size-- > 0 && sci0_RxWP != sci0_RxRP)
	{
		*data++ = SCI_0_RX_BUFFER_PTR[sci0_RxRP++];
		/* another character recieved */
		i++;
		/* modulo arithmetic (circular buffer) */
		if(sci0_RxRP >= SCI_0_RX_BUFFER_SIZE)
			sci0_RxRP = 0;
	}
	
	/* have we recoverred from buffer-full condition ? */
	#ifdef SCI_0_RX_BUFFER_LOWLIMIT
	if(periphBitTest(SCI_STATUS_RX_BUFFER_LOW, &sci0_status) && sci0BufferedRxGetFree() > SCI_0_RX_BUFFER_OKLIMIT)
	{
		/* call buffer-empty hook (e.g. to set CTS pin on RS232) */
		#ifdef SCI_0_RX_LOWBUFFER_HOOK
		SCI_0_RX_LOWBUFFER_HOOK(false);
		#endif
		
		/* send XON character */
		#if SCI_0_RX_XONXOFF
		ioctl(SCI_0, SCI_SEND_XON, NULL);
		#endif

		/* remember we are out of the buffer-full condition */			
		periphBitClear(SCI_STATUS_RX_BUFFER_LOW, &sci0_status);
	}
	#endif /* SCI_0_RX_BUFFER_LOWLIMIT */
		
	return i;
}

#if SCI_VERSION <= 3
/* Sci0RxFullISR() function  */

#pragma interrupt on
void Sci0RxFullISR(void)
{
	register rxfree;

	/* read status register */
	ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);
	
	/* now clear RDRF by reading data reg */
	SCI_0_RX_BUFFER_PTR[sci0_RxWP] = (SCI0CHAR) ioctl(SCI_0, SCI_READ_DATA, NULL); 

	/* how much free space is left in the buffer ? */
	rxfree = sci0_RxRP - sci0_RxWP - 1;
	if(rxfree < 0)
		rxfree += SCI_0_RX_BUFFER_SIZE;

	/* space OK, we can advance write pointer */
	if(rxfree)
	{
		/* call hook first */
		#ifdef SCI_0_RX_CHAR_HOOK
		if(SCI_0_RX_CHAR_HOOK(SCI_0_RX_BUFFER_PTR[sci0_RxWP]))
			return; /* hook returned nonzero: discard received character */	
		#endif
	
		/* advance wp in modulo arithmetic (circular buffer) */
		if(++sci0_RxWP >= SCI_0_RX_BUFFER_SIZE)
			sci0_RxWP = 0;
	}
	else
		periphBitSet(SCI_STATUS_EXCEPTION_EXIST | SCI_EXCEPTION_BUFFER_OVERFLOW, &sci0_status);

	/* any RX buffer-full handling ? */
	#ifdef SCI_0_RX_BUFFER_LOWLIMIT
	if(rxfree <= SCI_0_RX_BUFFER_LOWLIMIT)
	{
		/* when buffer-full condition just enterred */
		if(!(sci0_status & SCI_STATUS_RX_BUFFER_LOW))
		{
			/* call low-buffer hook (e.g. clear CTS pin on RS232) */
			#ifdef SCI_0_RX_LOWBUFFER_HOOK
			SCI_0_RX_LOWBUFFER_HOOK(true);
			#endif
			
			/* XON/XOFF copntrol ? */
			#if SCI_0_RX_XONXOFF
			ioctl(SCI_0, SCI_SEND_XOFF, NULL);
			#endif

			/* remember we already did this action */			
			periphBitSet(SCI_STATUS_RX_BUFFER_LOW, &sci0_status);
		}
	}
	#endif /* SCI_0_RX_BUFFER_LOWLIMIT */
}
#pragma interrupt off

/* SCI module error handling */

#pragma interrupt on
void Sci0RxErrorISR(void)
{
	periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci0_status);
	
	/* call rx-error hook */
	#ifdef SCI_0_RX_ERROR_HOOK
	SCI_0_RX_ERROR_HOOK();
	#endif
	
	/* ack error */
	ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);
	ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);
}
#pragma interrupt off

#else /* #if SCI_VERSION >= 4 */
/* Sci0RxFullErrISR() function performs nonblocking SCI block read using buffers 
 * and SCI module error handling */
#pragma interrupt on
void Sci0RxFullErrISR(void)
{
	register rxfree;
	UInt16 status_reg;

	status_reg=ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);

	/* Cleaar flags */
	ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);
	ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);

	/* SCI Receiver Full/Overrun */
	if (status_reg&(SCI_RX_FULL_FLAG|SCI_OVERRUN_FLAG))
	{
		/* now clear RDRF by reading data reg */
		SCI_0_RX_BUFFER_PTR[sci0_RxWP] = (SCI0CHAR) ioctl(SCI_0, SCI_READ_DATA, NULL); 

		/* how much free space is left in the buffer ? */
		rxfree = sci0_RxRP - sci0_RxWP - 1;
		if(rxfree < 0)
			rxfree += SCI_0_RX_BUFFER_SIZE;

		/* space OK, we can advance write pointer */
		if(rxfree)
		{
			/* call hook first */
			#ifdef SCI_0_RX_CHAR_HOOK
			if(SCI_0_RX_CHAR_HOOK(SCI_0_RX_BUFFER_PTR[sci0_RxWP]))
				return; /* hook returned nonzero: discard received character */	
			#endif
	
			/* advance wp in modulo arithmetic (circular buffer) */
			if(++sci0_RxWP >= SCI_0_RX_BUFFER_SIZE)
				sci0_RxWP = 0;
		}
		else
			periphBitSet(SCI_STATUS_EXCEPTION_EXIST | SCI_EXCEPTION_BUFFER_OVERFLOW, &sci0_status);

		/* any RX buffer-full handling ? */
		#ifdef SCI_0_RX_BUFFER_LOWLIMIT
		if(rxfree <= SCI_0_RX_BUFFER_LOWLIMIT)
		{
			/* when buffer-full condition just enterred */
			if(!(sci0_status & SCI_STATUS_RX_BUFFER_LOW))
			{
				/* call low-buffer hook (e.g. clear CTS pin on RS232) */
				#ifdef SCI_0_RX_LOWBUFFER_HOOK
				SCI_0_RX_LOWBUFFER_HOOK(true);
				#endif
			
				/* XON/XOFF copntrol ? */
				#if SCI_0_RX_XONXOFF
				ioctl(SCI_0, SCI_SEND_XOFF, NULL);
				#endif

				/* remember we already did this action */			
				periphBitSet(SCI_STATUS_RX_BUFFER_LOW, &sci0_status);
			}
		}
		#endif /* SCI_0_RX_BUFFER_LOWLIMIT */
	}

	/* SCI Receiver Error (Framing error)/SCI Receiver Error (Parity error)/
	 * SCI Receiver Error (Noise Flag)/SCI Receiver Error (Overrun Flag)/
	 * 	 SCI Receiver Error (LIN Sync Error) */
	if (status_reg&(SCI_NOISE_FLAG|SCI_FRAMING_ERROR_FLAG|SCI_PARITY_ERROR_FLAG|SCI_OVERRUN_FLAG|SCI_LIN_SYNC_ERROR_FLAG))
	{
		periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci0_status);
	
		/* call rx-error hook */
		#ifdef SCI_0_RX_ERROR_HOOK
		SCI_0_RX_ERROR_HOOK();
		#endif
	}
}
#pragma interrupt off

#endif /* SCI_VERSION >= 4 */

#else /* SCI_0_RX_BUFFER_SIZE (read operation implemented) */

/* The functions must be defined so the ioctl commands which call them
   can compile. Normally, these functions will be optimized-out so they
   are not even linked. We do define them here for the case the optimizer 
   is turned off  */
   
void sci0BufferedRxEnable(void) {}
void sci0BufferedRxDisable(void) {}
Word16 sci0BufferedRxGetLen(void) { return 0; }
Word16 sci0BufferedRxGetFree(void) { return 0; }

#endif /* SCI_0_RX_BUFFER_SIZE (read operation implemented) */

/* write operation */
#if defined(SCI_0) && SCI_0_TX_BUFFER_SIZE>0

void sci0BufferedTxEnable(void)
{
	sci0_TxWP = 0;
	sci0_TxRP = 0;
	
	ioctl(SCI_0, SCI_INT_DISABLE, SCI_TX_EMPTY);
}

void sci0BufferedTxDisable(void)
{
	ioctl(SCI_0, SCI_INT_DISABLE, SCI_TX_EMPTY);
}

/* get free space in TX buffer */

Word16 sci0BufferedTxGetFree(void)
{
	register Word16 txfree;
	
	txfree = sci0_TxRP - sci0_TxWP - 1;
	if(txfree < 0)
		txfree += SCI_0_TX_BUFFER_SIZE;
		
	return txfree;
}

Word16 write_SCI_0_BUFFERED(const SCI0CHAR *data, UWord16 size)
{
	register Word16 newWP;
	Word16 i = 0;
	
	while(size-- > 0)
	{
		/* theoretical value of write pointer (if there is any space left) */
		newWP = sci0_TxWP + 1;
		if(newWP >= SCI_0_TX_BUFFER_SIZE)
			newWP = 0;
			
		/* any space left in buffer ? */
		if(newWP == sci0_TxRP)
			break;
			
		/* OK, place character to buffer */
		SCI_0_TX_BUFFER_PTR[sci0_TxWP] = *data++;
		sci0_TxWP = newWP;
		
		/* another character sent */
		i++;
	}

	ioctl(SCI_0, SCI_INT_ENABLE, SCI_TX_EMPTY);
	return i;
}

/* Sci0TxEmptyISR() function */

#pragma interrupt on
void Sci0TxEmptyISR(void)
{
	/* read status register */
	ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);

	/* XON/XOFF priority characters ? */
	#if SCI_0_RX_XONXOFF
	if(periphBitTest(SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, &sci0_status))
	{
		if(periphBitTest(SCI_STATUS_XON_PENDING, &sci0_status))
		 	ioctl(SCI_0, SCI_WRITE_DATA, SCI_0_XONCHAR);
	  	else
		 	ioctl(SCI_0, SCI_WRITE_DATA, SCI_0_XOFFCHAR);
		 	
	 	periphBitClear(SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, &sci0_status);
	 	goto continue_TX;
	}
	#endif

	/* call hook to handle character being sent */
	#ifdef SCI_0_TX_CHAR_HOOK
	/* user hook may supply his own character */
	if(SCI_0_TX_CHAR_HOOK(SCI_0_TX_BUFFER_PTR[sci0_TxRP]))
		return; 
	#endif

	/* just send another buffered character */
 	ioctl(SCI_0, SCI_WRITE_DATA, SCI_0_TX_BUFFER_PTR[sci0_TxRP]);

	/* advance read pointer */ 	
	if(++sci0_TxRP >= SCI_0_TX_BUFFER_SIZE)
		sci0_TxRP = 0;
	
 	/* any next char ? */
continue_TX: 	
 	if(sci0_TxRP == sci0_TxWP)
		ioctl(SCI_0, SCI_INT_DISABLE, SCI_TX_EMPTY);
}
#pragma interrupt off

#else /* SCI_0_TX_BUFFER_SIZE (write operation implemented) */

/* The functions must be defined so the ioctl commands which call them
   can compile. Normally, these functions will be optimized-out so they
   are not even linked. We do define them here for the case the optimizer 
   is turned off  */
   
void sci0BufferedTxEnable(void) {}
void sci0BufferedTxDisable(void) {}
Word16 sci0BufferedTxGetFree(void) { return 0; }

#endif /* SCI_0_TX_BUFFER_SIZE (write operation implemented) */

/* 

Note: use SCI_0 code as a template, duplicate it and use
Replace (Ctrl+H) in selected duplicated code, 

	select "Regular Expression" and specify:

		Find: ([Ss][Cc][Ii]_*)0
		Replace: \11

*/


/* read operation */
#if defined(SCI_1) && SCI_1_RX_BUFFER_SIZE>0

/********************************************************************************
 sci1BufferedRxEnable/Disable - start/stop buffered RX operation
********************************************************************************/

/* enable buffered RX - start receiving into our circular buffer */

void sci1BufferedRxEnable(void)
{
	sci1_RxWP = 0;
	sci1_RxRP = 0;
	
	periphBitClear(SCI_STATUS_RX_BUFFER_LOW | SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, 
		&sci1_status);

	/* clear exception if any */		
	if(ioctl(SCI_1, SCI_GET_ERROR, NULL)) /* read SCI status register */
		ioctl(SCI_1, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */

	/* enable RX interrupts */	
	ioctl(SCI_1, SCI_INT_ENABLE, SCI_RX_FULL | SCI_RX_ERROR);
	
	/* call buffer-empty hook (e.g. to set CTS pin on RS232) */
	#ifdef SCI_1_RX_LOWBUFFER_HOOK
	SCI_1_RX_LOWBUFFER_HOOK(false);
	#endif
	
	/* send XON character */
	#if SCI_1_RX_XONXOFF
	ioctl(SCI_1, SCI_SEND_XON, NULL);
	#endif
}

void sci1BufferedRxDisable(void)
{
	/* call buffer-full hook (e.g. to clear CTS pin on RS232) */
	#ifdef SCI_1_RX_LOWBUFFER_HOOK
	SCI_1_RX_LOWBUFFER_HOOK(true);
	#endif
	
	/* send XOFF character */
	#if SCI_1_RX_XONXOFF
	ioctl(SCI_1, SCI_SEND_XOFF, NULL);
	/* wait until XOFF is sent */	
	while(!ioctl(SCI_1, SCI_GET_TX_EMPTY, NULL)) 
		; /* empty loop */ 
	#endif
	
	/* disable TX interrupt */
	ioctl(SCI_1, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
}

/* get number of characters ready to read */

Word16 sci1BufferedRxGetLen(void)
{
	register Word16 rxlen;
	
	rxlen = sci1_RxWP - sci1_RxRP;
	if(rxlen < 0)
		rxlen += SCI_1_RX_BUFFER_SIZE;
		
	return rxlen;
}

/* get free space in RX buffer */

Word16 sci1BufferedRxGetFree(void)
{
	register Word16 rxfree;
	
	rxfree = sci1_RxRP - sci1_RxWP - 1;
	if(rxfree < 0)
		rxfree += SCI_1_RX_BUFFER_SIZE;
		
	return rxfree;
}

/* read out the characters in the rx buffer */

Word16 read_SCI_1_BUFFERED(SCI1CHAR *data, UWord16 size)
{
	register Word16 i = 0;
	
	while(size-- > 0 && sci1_RxWP != sci1_RxRP)
	{
		*data++ = SCI_1_RX_BUFFER_PTR[sci1_RxRP++];
		/* another character recieved */
		i++;
		/* modulo arithmetic (circular buffer) */
		if(sci1_RxRP >= SCI_1_RX_BUFFER_SIZE)
			sci1_RxRP = 0;
	}
	
	/* have we recoverred from buffer-full condition ? */
	#ifdef SCI_1_RX_BUFFER_LOWLIMIT
	if(periphBitTest(SCI_STATUS_RX_BUFFER_LOW, &sci1_status) && sci1BufferedRxGetFree() > SCI_1_RX_BUFFER_OKLIMIT)
	{
		/* call buffer-empty hook (e.g. to set CTS pin on RS232) */
		#ifdef SCI_1_RX_LOWBUFFER_HOOK
		SCI_1_RX_LOWBUFFER_HOOK(false);
		#endif
		
		/* send XON character */
		#if SCI_1_RX_XONXOFF
		ioctl(SCI_1, SCI_SEND_XON, NULL);
		#endif

		/* remember we are out of the buffer-full condition */			
		periphBitClear(SCI_STATUS_RX_BUFFER_LOW, &sci1_status);
	}
	#endif /* SCI_1_RX_BUFFER_LOWLIMIT */
		
	return i;
}

/* Sci1RxFullISR() function  */

#pragma interrupt on
void Sci1RxFullISR(void)
{
	register rxfree;

	/* read status register */
	ioctl(SCI_1, SCI_GET_STATUS_REG, NULL);
	
	/* now clear RDRF by reading data reg */
	SCI_1_RX_BUFFER_PTR[sci1_RxWP] = (SCI1CHAR) ioctl(SCI_1, SCI_READ_DATA, NULL); 

	/* how much free space is left in the buffer ? */
	rxfree = sci1_RxRP - sci1_RxWP - 1;
	if(rxfree < 0)
		rxfree += SCI_1_RX_BUFFER_SIZE;

	/* space OK, we can advance write pointer */
	if(rxfree)
	{
		/* call hook first */
		#ifdef SCI_1_RX_CHAR_HOOK
		if(SCI_1_RX_CHAR_HOOK(SCI_1_RX_BUFFER_PTR[sci1_RxWP]))
			return; /* hook returned nonzero: discard received character */	
		#endif
	
		/* advance wp in modulo arithmetic (circular buffer) */
		if(++sci1_RxWP >= SCI_1_RX_BUFFER_SIZE)
			sci1_RxWP = 0;
	}
	else
		periphBitSet(SCI_STATUS_EXCEPTION_EXIST | SCI_EXCEPTION_BUFFER_OVERFLOW, &sci1_status);

	/* any RX buffer-full handling ? */
	#ifdef SCI_1_RX_BUFFER_LOWLIMIT
	if(rxfree <= SCI_1_RX_BUFFER_LOWLIMIT)
	{
		/* when buffer-full condition just enterred */
		if(!(sci1_status & SCI_STATUS_RX_BUFFER_LOW))
		{
			/* call low-buffer hook (e.g. clear CTS pin on RS232) */
			#ifdef SCI_1_RX_LOWBUFFER_HOOK
			SCI_1_RX_LOWBUFFER_HOOK(true);
			#endif
			
			/* XON/XOFF copntrol ? */
			#if SCI_1_RX_XONXOFF
			ioctl(SCI_1, SCI_SEND_XOFF, NULL);
			#endif

			/* remember we already did this action */			
			periphBitSet(SCI_STATUS_RX_BUFFER_LOW, &sci1_status);
		}
	}
	#endif /* SCI_1_RX_BUFFER_LOWLIMIT */
}
#pragma interrupt off

/* SCI module error handling */

#pragma interrupt on
void Sci1RxErrorISR(void)
{
	periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci1_status);
	
	/* call rx-error hook */
	#ifdef SCI_1_RX_ERROR_HOOK
	SCI_1_RX_ERROR_HOOK();
	#endif
	
	/* ack error */
	ioctl(SCI_1, SCI_GET_STATUS_REG, NULL);
	ioctl(SCI_1, SCI_CLEAR_STATUS_REG, NULL);
}
#pragma interrupt off

#else /* SCI_1_RX_BUFFER_SIZE (read operation implemented) */

/* The functions must be defined so the ioctl commands which call them
   can compile. Normally, these functions will be optimized-out so they
   are not even linked. We do define them here for the case the optimizer 
   is turned off  */
   
void sci1BufferedRxEnable(void) {}
void sci1BufferedRxDisable(void) {}
Word16 sci1BufferedRxGetLen(void) { return 0; }
Word16 sci1BufferedRxGetFree(void) { return 0; }

#endif /* SCI_1_RX_BUFFER_SIZE (read operation implemented) */

/* write operation */
#if defined(SCI_1) && SCI_1_TX_BUFFER_SIZE>0

void sci1BufferedTxEnable(void)
{
	sci1_TxWP = 0;
	sci1_TxRP = 0;
	
	ioctl(SCI_1, SCI_INT_DISABLE, SCI_TX_EMPTY);
}

void sci1BufferedTxDisable(void)
{
	ioctl(SCI_1, SCI_INT_DISABLE, SCI_TX_EMPTY);
}

/* get free space in TX buffer */

Word16 sci1BufferedTxGetFree(void)
{
	register Word16 txfree;
	
	txfree = sci1_TxRP - sci1_TxWP - 1;
	if(txfree < 0)
		txfree += SCI_1_TX_BUFFER_SIZE;
		
	return txfree;
}

Word16 write_SCI_1_BUFFERED(const SCI1CHAR *data, UWord16 size)
{
	register Word16 newWP;
	Word16 i = 0;
	
	while(size-- > 0)
	{
		/* theoretical value of write pointer (if there is any space left) */
		newWP = sci1_TxWP + 1;
		if(newWP >= SCI_1_TX_BUFFER_SIZE)
			newWP = 0;
			
		/* any space left in buffer ? */
		if(newWP == sci1_TxRP)
			break;
			
		/* OK, place character to buffer */
		SCI_1_TX_BUFFER_PTR[sci1_TxWP] = *data++;
		sci1_TxWP = newWP;
		
		/* another character sent */
		i++;
	}

	ioctl(SCI_1, SCI_INT_ENABLE, SCI_TX_EMPTY);
	return i;
}

/* Sci1TxEmptyISR() function */

#pragma interrupt on
void Sci1TxEmptyISR(void)
{
	/* read status register */
	ioctl(SCI_1, SCI_GET_STATUS_REG, NULL);

	/* XON/XOFF priority characters ? */
	#if SCI_1_RX_XONXOFF
	if(periphBitTest(SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, &sci1_status))
	{
		if(periphBitTest(SCI_STATUS_XON_PENDING, &sci1_status))
		 	ioctl(SCI_1, SCI_WRITE_DATA, SCI_1_XONCHAR);
	  	else
		 	ioctl(SCI_1, SCI_WRITE_DATA, SCI_1_XOFFCHAR);
		 	
	 	periphBitClear(SCI_STATUS_XON_PENDING | SCI_STATUS_XOFF_PENDING, &sci1_status);
	 	goto continue_TX;
	}
	#endif

	/* call hook to handle character being sent */
	#ifdef SCI_1_TX_CHAR_HOOK
	/* user hook may supply his own character */
	if(SCI_1_TX_CHAR_HOOK(SCI_1_TX_BUFFER_PTR[sci1_TxRP]))
		return; 
	#endif

	/* just send another buffered character */
 	ioctl(SCI_1, SCI_WRITE_DATA, SCI_1_TX_BUFFER_PTR[sci1_TxRP]);

	/* advance read pointer */ 	
	if(++sci1_TxRP >= SCI_1_TX_BUFFER_SIZE)
		sci1_TxRP = 0;
	
 	/* any next char ? */
continue_TX: 	
 	if(sci1_TxRP == sci1_TxWP)
		ioctl(SCI_1, SCI_INT_DISABLE, SCI_TX_EMPTY);
}
#pragma interrupt off

#else /* SCI_1_TX_BUFFER_SIZE (write operation implemented) */

/* The functions must be defined so the ioctl commands which call them
   can compile. Normally, these functions will be optimized-out so they
   are not even linked. We do define them here for the case the optimizer 
   is turned off  */
   
void sci1BufferedTxEnable(void) {}
void sci1BufferedTxDisable(void) {}
Word16 sci1BufferedTxGetFree(void) { return 0; }

#endif /* SCI_1_TX_BUFFER_SIZE (write operation implemented) */

#ifdef __cplusplus
}
#endif

#endif /* SCI_HIGHLEVEL_MODE == SCI_HIGHLEVEL_MODE_BUFFERED */

