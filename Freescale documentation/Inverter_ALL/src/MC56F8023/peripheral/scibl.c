/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  scibl.c
*
* $Date:      Jan-30-2009$
*
* $Version:   2.3.15.0$
*
* Description: Source file for the SCI Driver. BLOCKING/NON_BLOCKING Implementation
*
*******************************************************************************/

#include "qs.h"

/* we don't care about missing baudrates */
#define SCI_DISABLE_BAUDRATE_WARNING 1

#include "sci.h"
#include "scihl.h"

/* compile this file only if BLOCKING/NON_BLOCKING mode is selected */
#if SCI_HIGHLEVEL_MODE == SCI_HIGHLEVEL_MODE_BLOCKING

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************
 * global variables used in read/write functions    
 ****************************************************/

volatile UWord16 sci0_status = 0;        /* status word */
volatile UWord16 sci0_TxCounter = 0;     /* TX counter */
volatile UWord16 sci0_RxCounter = 0;     /* RX counter */

volatile UWord16 sci1_status = 0;        /* status word */
volatile UWord16 sci1_TxCounter = 0;     /* TX counter */
volatile UWord16  sci1_RxCounter = 0;    /* RX counter */
 
#ifdef SCI_0
static volatile const SCI0CHAR *sci0_TxDataPtr;  /* pointer to TX data */
static volatile SCI0CHAR *sci0_RxDataPtr; /* pointer to RX data */
#endif

#ifdef SCI_1
static volatile const SCI1CHAR *sci1_TxDataPtr;    /* pointer to TX data */
static volatile SCI1CHAR *sci1_RxDataPtr; /* pointer to RX data */
#endif

#ifdef SCI_0

/********************************************************************************
 read_SCI_0_NON_BLOCKING() function performs nonblocking SCI read 
********************************************************************************/

void read_SCI_0_NON_BLOCKING(SCI0CHAR *data, UWord16 size)
{
	sci0_RxDataPtr = data;
	sci0_RxCounter = size;
	
	/* read in progress */
	periphBitSet(SCI_STATUS_READ_INPROGRESS,&sci0_status);  /* read in progress */

	/* clear exception if any */		
	if(ioctl(SCI_0, SCI_GET_ERROR, NULL)) /* read SCI status register */
		ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */
	
	/* enable all RX interrupts */
	ioctl(SCI_0, SCI_INT_ENABLE, SCI_RX_FULL | SCI_RX_ERROR);
}

#if SCI_VERSION <= 3
/* Sci0RxFullISR() function performs nonblocking SCI block read using buffers */
#pragma interrupt on
void Sci0RxFullISR(void)
{
	/* if read is currently in progress */
	if (periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci0_status))
	{
		/* clear RDRF by reading data reg */
		*sci0_RxDataPtr = (SCI0CHAR) ioctl(SCI_0, SCI_READ_DATA, NULL); 

		/* character hook */		
		#ifdef SCI_0_RX_CHAR_HOOK
		if(SCI_0_RX_CHAR_HOOK(*sci0_RxDataPtr))
			return; /* hook returned nonzero: discard received character */	
		#endif
		
		/* advance data pointer */
		sci0_RxDataPtr++;
		
		/* end of read ? */
		if (!--sci0_RxCounter)
		{
			/* read operation finished */
			periphBitClear(SCI_STATUS_READ_INPROGRESS, &sci0_status);
			/* disable all RX interrupts */
			ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
			
			/* call end-of-read hook (it may start another non-blocking read) */
			#ifdef SCI_0_RX_FINISHED_HOOK
 			SCI_0_RX_FINISHED_HOOK();
			#endif
		}
	}
	else
	{
		/* disable all RX interrupts */
		ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
	}
}
#pragma interrupt off

/* SCI module error handling */

#pragma interrupt on
void Sci0RxErrorISR(void)
{
	periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci0_status);
	
	/* call rx-error hook (during read process only) */
	#ifdef SCI_0_RX_ERROR_HOOK
	if(periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci0_status))
		SCI_0_RX_ERROR_HOOK();
	#endif
	
	/* ack error */
	periphMemDummyRead(&SCI_0->scisr);
	ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);
}
#pragma interrupt off

#else /* #if SCI_VERSION >= 4 */
/* Sci0RxFullErrISR() function performs nonblocking SCI block read using buffers 
 * and SCI module error handling */
#pragma interrupt on
void Sci0RxFullErrISR(void)
{
	UInt16 status_reg;
	
	status_reg=ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);

	/* Cleaar flags */
	ioctl(SCI_0, SCI_GET_STATUS_REG, NULL);
	ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);

	/* SCI Receiver Full/Overrun */
	if (status_reg&(SCI_RX_FULL_FLAG|SCI_OVERRUN_FLAG))
	{
	/* Receiver Full Interrupt */
		/* if read is currently in progress */
		if (periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci0_status))
		{
			/* clear RDRF by reading data reg */
			*sci0_RxDataPtr = (SCI0CHAR) ioctl(SCI_0, SCI_READ_DATA, NULL); 

			/* character hook */		
			#ifdef SCI_0_RX_CHAR_HOOK
			if(SCI_0_RX_CHAR_HOOK(*sci0_RxDataPtr))
				return; /* hook returned nonzero: discard received character */	
			#endif
		
			/* advance data pointer */
			sci0_RxDataPtr++;
		
			/* end of read ? */
			if (!--sci0_RxCounter)
			{
				/* read operation finished */
				periphBitClear(SCI_STATUS_READ_INPROGRESS, &sci0_status);
				/* disable all RX interrupts */
				ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
			
				/* call end-of-read hook (it may start another non-blocking read) */
				#ifdef SCI_0_RX_FINISHED_HOOK
 				SCI_0_RX_FINISHED_HOOK();
				#endif
			}
		}
		else
		{
			/* disable all RX interrupts */
			ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
		}
	}

	/* SCI Receiver Error (Framing error)/SCI Receiver Error (Parity error)/
	 * SCI Receiver Error (Noise Flag)/SCI Receiver Error (Overrun Flag)/
	 * 	 SCI Receiver Error (LIN Sync Error) */
	if (status_reg&(SCI_NOISE_FLAG|SCI_FRAMING_ERROR_FLAG|SCI_PARITY_ERROR_FLAG|SCI_OVERRUN_FLAG|SCI_LIN_SYNC_ERROR_FLAG))
	{
	/* Receive Error Interrupt */
		periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci0_status);
	
		/* call rx-error hook (during read process only) */
		#ifdef SCI_0_RX_ERROR_HOOK
		if(periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci0_status))
			SCI_0_RX_ERROR_HOOK();
		#endif
	
		/* ack error */
		periphMemDummyRead(&SCI_0->scisr);
		ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);
	}
}
#pragma interrupt off

#endif /* SCI_VERSION >= 4 */


/********************************************************************************
 read_SCI_0_BLOCKING() function performs blocking SCI block read using buffers 
********************************************************************************/

void read_SCI_0_BLOCKING(SCI0CHAR *data, UWord16 size)
{
	/* if no read is currently in progress */
	if (!periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci0_status))
	{
		/* disable RX interrupts */
		ioctl(SCI_0, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
		
		sci0_RxDataPtr = data;
		sci0_RxCounter = size;

		/* note that SCI_STATUS_READ_INPROGRESS stays 0 all the time here */
		while (sci0_RxCounter)
		{
		    /* clear exception if any */		
		    if(ioctl(SCI_0, SCI_GET_ERROR, NULL))   /* read SCI status register */
		    {
		    	ioctl(SCI_0, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */
				periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci0_status);

				/* call rx-error hook */
				#ifdef SCI_0_RX_ERROR_HOOK
				SCI_0_RX_ERROR_HOOK();
				#endif
			}
		    	
		    /* data polling mechanism */
			if (ioctl(SCI_0, SCI_GET_RX_FULL, NULL))
			{
				*sci0_RxDataPtr = (SCI0CHAR) ioctl(SCI_0, SCI_READ_DATA, NULL); 
				
				/* character hook */		
				#ifdef SCI_0_RX_CHAR_HOOK
				if(SCI_0_RX_CHAR_HOOK(*sci0_RxDataPtr))
					continue; /* hook returned nonzero: discard received character */	
				#endif
				
				sci0_RxDataPtr++;
				sci0_RxCounter--;
			}
		}
	}
}

/********************************************************************************
 write_SCI_0_NON_BLOCKING() function performs nonblocking SCI block write using buffers 
********************************************************************************/

void write_SCI_0_NON_BLOCKING(const SCI0CHAR *data, UWord16 size)
{
	sci0_TxDataPtr = data;
	sci0_TxCounter = size;
 	
 	/* write in progress */
	periphBitSet(SCI_STATUS_WRITE_INPROGRESS, &sci0_status); 

	/* enable tx-empty interrupt */
	ioctl(SCI_0, SCI_INT_ENABLE, SCI_TX_EMPTY);
}

/* Sci0TransmitterEmptyISR() function performs nonblocking SCI block write using buffers */

#pragma interrupt on
void Sci0TxEmptyISR(void)
{
	/* read out status register */
 	periphMemDummyRead(&SCI_0->scisr);

	/* call hook to handle character being sent */
	#ifdef SCI_0_TX_CHAR_HOOK
	/* user hook may supply his own character (or abort the write op) */
	if(SCI_0_TX_CHAR_HOOK(*sci0_TxDataPtr))
		return; 
	#endif

	/* this write clears interrupt flag (see reading stat.reg above) */
 	ioctl(SCI_0, SCI_WRITE_DATA, *sci0_TxDataPtr++);

	if (!--sci0_TxCounter)
	{
		/* write operation finished */	
		periphBitClear(SCI_STATUS_WRITE_INPROGRESS, &sci0_status);  
		/* disable TX interrupt */
		ioctl(SCI_0, SCI_INT_DISABLE, SCI_TX_EMPTY);

		/* call hook, it can issue another non-blocking write operation */		
		#ifdef SCI_0_TX_FINISHED_HOOK
		SCI_0_TX_FINISHED_HOOK();
		#endif
	}
}
#pragma interrupt off

/********************************************************************************
 write_SCI_0_BLOCKING() function performs blocking SCI block write using buffers 
********************************************************************************/

void write_SCI_0_BLOCKING(const SCI0CHAR *data, UWord16 size)
{
	/* if no write is currently in progress */
	if (!periphBitTest(SCI_STATUS_WRITE_INPROGRESS, &sci0_status))
	{	
		sci0_TxDataPtr = data;
		sci0_TxCounter = size;

		/* disable TX interrupts */
		ioctl(SCI_0, SCI_INT_DISABLE, SCI_TX_EMPTY);
	
		/* while there is anything to send */
		while(sci0_TxCounter)
		{
			/* read status and test TDRE bit */
			if ((ioctl(SCI_0, SCI_GET_STATUS_REG, NULL) & SCI_SCISR_TDRE))
			{
				/* call hook to handle character being sent */
				#ifdef SCI_0_TX_CHAR_HOOK
				/* user hook may supply his own character (or abort the write op) */
				if(SCI_0_TX_CHAR_HOOK(*sci0_TxDataPtr))
					continue;
				#endif

				/* write data register and clear TDRE flag */
		 		ioctl(SCI_0, SCI_WRITE_DATA, *sci0_TxDataPtr++);
		 		sci0_TxCounter--;
		 	}
		}
	}
}

#endif /* SCI_0 */

/* 

Note: use SCI_0 code as a template, duplicate it and use
Replace (Ctrl+H) in selected duplicated code, 

	select "Regular Expression" and specify:

		Find: ([Ss][Cc][Ii]_*)0
		Replace: \11

*/


#ifdef SCI_1

/********************************************************************************
 read_SCI_1_NON_BLOCKING() function performs nonblocking SCI read 
********************************************************************************/

void read_SCI_1_NON_BLOCKING(SCI1CHAR *data, UWord16 size)
{
	sci1_RxDataPtr = data;
	sci1_RxCounter = size;
	
	/* read in progress */
	periphBitSet(SCI_STATUS_READ_INPROGRESS,&sci1_status);  /* read in progress */

	/* clear exception if any */		
	if(ioctl(SCI_1, SCI_GET_ERROR, NULL)) /* read SCI status register */
		ioctl(SCI_1, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */
	
	/* enable all RX interrupts */
	ioctl(SCI_1, SCI_INT_ENABLE, SCI_RX_FULL | SCI_RX_ERROR);
}

/* Sci1RxFullISR() function performs nonblocking SCI block read using buffers */

#pragma interrupt on
void Sci1RxFullISR(void)
{
	/* if read is currently in progress */
	if (periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci1_status))
	{
		/* clear RDRF by reading data reg */
		*sci1_RxDataPtr = (SCI1CHAR) ioctl(SCI_1, SCI_READ_DATA, NULL); 

		/* character hook */		
		#ifdef SCI_1_RX_CHAR_HOOK
		if(SCI_1_RX_CHAR_HOOK(*sci1_RxDataPtr))
			return; /* hook returned nonzero: discard received character */	
		#endif
		
		/* advance data pointer */
		sci1_RxDataPtr++;
		
		/* end of read ? */
		if (!--sci1_RxCounter)
		{
			/* read operation finished */
			periphBitClear(SCI_STATUS_READ_INPROGRESS, &sci1_status);
			/* disable all RX interrupts */
			ioctl(SCI_1, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
			
			/* call end-of-read hook (it may start another non-blocking read) */
			#ifdef SCI_1_RX_FINISHED_HOOK
 			SCI_1_RX_FINISHED_HOOK();
			#endif
		}
	}
	else
	{
		/* disable all RX interrupts */
		ioctl(SCI_1, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
	}
}
#pragma interrupt off

/* SCI module error handling */

#pragma interrupt on
void Sci1RxErrorISR(void)
{
	periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci1_status);
	
	/* call rx-error hook (during read process only) */
	#ifdef SCI_1_RX_ERROR_HOOK
	if(periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci1_status))
		SCI_1_RX_ERROR_HOOK();
	#endif
	
	/* ack error */
	periphMemDummyRead(&SCI_1->scisr);
	ioctl(SCI_1, SCI_CLEAR_STATUS_REG, NULL);
}
#pragma interrupt off

/********************************************************************************
 read_SCI_1_BLOCKING() function performs blocking SCI block read using buffers 
********************************************************************************/

void read_SCI_1_BLOCKING(SCI1CHAR *data, UWord16 size)
{
	/* if no read is currently in progress */
	if (!periphBitTest(SCI_STATUS_READ_INPROGRESS, &sci1_status))
	{
		/* disable RX interrupts */
		ioctl(SCI_1, SCI_INT_DISABLE, SCI_RX_FULL | SCI_RX_ERROR);
		
		sci1_RxDataPtr = data;
		sci1_RxCounter = size;

		/* note that SCI_STATUS_READ_INPROGRESS stays 0 all the time here */
		while (sci1_RxCounter)
		{
		    /* clear exception if any */		
		    if(ioctl(SCI_1, SCI_GET_ERROR, NULL))   /* read SCI status register */
		    {
		    	ioctl(SCI_1, SCI_CLEAR_STATUS_REG, NULL);	/* clear exception */
				periphBitSet(SCI_STATUS_EXCEPTION_EXIST, &sci1_status);

				/* call rx-error hook */
				#ifdef SCI_1_RX_ERROR_HOOK
				SCI_1_RX_ERROR_HOOK();
				#endif
			}
		    	
		    /* data polling mechanism */
			if (ioctl(SCI_1, SCI_GET_RX_FULL, NULL))
			{
				*sci1_RxDataPtr = (SCI1CHAR) ioctl(SCI_1, SCI_READ_DATA, NULL); 
				
				/* character hook */		
				#ifdef SCI_1_RX_CHAR_HOOK
				if(SCI_1_RX_CHAR_HOOK(*sci1_RxDataPtr))
					continue; /* hook returned nonzero: discard received character */	
				#endif
				
				sci1_RxDataPtr++;
				sci1_RxCounter--;
			}
		}
	}
}

/********************************************************************************
 write_SCI_1_NON_BLOCKING() function performs nonblocking SCI block write using buffers 
********************************************************************************/

void write_SCI_1_NON_BLOCKING(const SCI1CHAR *data, UWord16 size)
{
	sci1_TxDataPtr = data;
	sci1_TxCounter = size;
 	
 	/* write in progress */
	periphBitSet(SCI_STATUS_WRITE_INPROGRESS, &sci1_status); 

	/* enable tx-empty interrupt */
	ioctl(SCI_1, SCI_INT_ENABLE, SCI_TX_EMPTY);
}

/* Sci1TransmitterEmptyISR() function performs nonblocking SCI block write using buffers */

#pragma interrupt on
void Sci1TxEmptyISR(void)
{
	/* read out status register */
 	periphMemDummyRead(&SCI_1->scisr);

	/* call hook to handle character being sent */
	#ifdef SCI_1_TX_CHAR_HOOK
	/* user hook may supply his own character (or abort the write op) */
	if(SCI_1_TX_CHAR_HOOK(*sci1_TxDataPtr))
		return; 
	#endif

	/* this write clears interrupt flag (see reading stat.reg above) */
 	ioctl(SCI_1, SCI_WRITE_DATA, *sci1_TxDataPtr++);

	if (!--sci1_TxCounter)
	{
		/* write operation finished */	
		periphBitClear(SCI_STATUS_WRITE_INPROGRESS, &sci1_status);  
		/* disable TX interrupt */
		ioctl(SCI_1, SCI_INT_DISABLE, SCI_TX_EMPTY);

		/* call hook, it can issue another non-blocking write operation */		
		#ifdef SCI_1_TX_FINISHED_HOOK
		SCI_1_TX_FINISHED_HOOK();
		#endif
	}
}
#pragma interrupt off

/********************************************************************************
 write_SCI_1_BLOCKING() function performs blocking SCI block write using buffers 
********************************************************************************/

void write_SCI_1_BLOCKING(const SCI1CHAR *data, UWord16 size)
{
	/* if no write is currently in progress */
	if (!periphBitTest(SCI_STATUS_WRITE_INPROGRESS, &sci1_status))
	{	
		sci1_TxDataPtr = data;
		sci1_TxCounter = size;

		/* disable TX interrupts */
		ioctl(SCI_1, SCI_INT_DISABLE, SCI_TX_EMPTY);
	
		/* while there is anything to send */
		while(sci1_TxCounter)
		{
			/* read status and test TDRE bit */
			if ((ioctl(SCI_1, SCI_GET_STATUS_REG, NULL) & SCI_SCISR_TDRE))
			{
				/* call hook to handle character being sent */
				#ifdef SCI_1_TX_CHAR_HOOK
				/* user hook may supply his own character (or abort the write op) */
				if(SCI_1_TX_CHAR_HOOK(*sci1_TxDataPtr))
					continue;
				#endif

				/* write data register and clear TDRE flag */
		 		ioctl(SCI_1, SCI_WRITE_DATA, *sci1_TxDataPtr++);
		 		sci1_TxCounter--;
		 	}
		}
	}
}

#endif /* SCI_1 */

#ifdef __cplusplus
}
#endif

#endif /* SCI_HIGHLEVEL_MODE == SCI_HIGHLEVEL_MODE_BLOCKING */
