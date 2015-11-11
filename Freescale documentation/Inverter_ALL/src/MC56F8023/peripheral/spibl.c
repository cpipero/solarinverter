/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  spibl.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.10.0$
*
* Description: Source file for the SPI Driver. BLOCKING/NON_BLOCKING Implementation
*
*****************************************************************************/

#include "qs.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************
 * global variables used in read/write functions    
 ****************************************************/

#ifdef SPI_0
volatile UWord16 spi0_status = 0;
static volatile const SPI0CHAR *spi0_TxDataPtr;
volatile UWord16 spi0_TxCounter = 0;
static volatile SPI0CHAR *spi0_RxDataPtr;
volatile UWord16 spi0_RxCounter = 0;
#endif

#ifdef SPI_1
volatile UWord16 spi1_status = 0;
static volatile const SPI1CHAR *spi1_TxDataPtr;
volatile UWord16 spi1_TxCounter = 0;
static volatile SPI1CHAR *spi1_RxDataPtr;
volatile UWord16 spi1_RxCounter = 0;
#endif

#ifdef SPI_0

/****************************************************************************
* read_SPI_0_NON_BLOCKING function performs nonblocking SPI read 
*****************************************************************************/

void read_SPI_0_NON_BLOCKING(SPI0CHAR *buf, UWord16 size)
{   
	spi0_RxDataPtr = buf;
	spi0_RxCounter = size;

	/* read in progress */
	periphBitSet(SPI_STATUS_READ_INPROGRESS,&spi0_status);
	
	/* clear pending error if any */		
	if(ioctl(SPI_0, SPI_GET_ERROR, NULL)) /* read SPI status register */
	{
		periphMemDummyRead(&SPI_0->spdrr);			/* clear OVRF */
		ioctl(SPI_0, SPI_CLEAR_MODE_FAULT, NULL);	/* clear MODF */
	}
	
	if(ioctl(SPI_0, SPI_GET_RX_FULL, NULL)) /* read SPI status register */
	{
		periphMemDummyRead(&SPI_0->spdrr);			/* clear SPRF */
	}
	
	ioctl(SPI_0, SPI_INT_ENABLE, SPI_RX_FULL);  /* Rx int enable */
	
	/* receive operations are started when 1St char. is received */
	/* in MASTER mode it is necessary write to SPI to receive char. concurently */
	/* with transmition - transfer is initiated by writing */        
}

/* Spi0RxFullISR() function performs nonblocking SPI block read  */

#pragma interrupt on
void Spi0RxFullISR(void)
{
	/* if read is currently in progress */
	if (periphBitTest(SPI_STATUS_READ_INPROGRESS, &spi0_status))
	{
		/* handle errors */
		if(ioctl(SPI_0, SPI_GET_ERROR, NULL))
		{
			if (ioctl(SPI_0, SPI_GET_MODE_FAULT, NULL))
			{
				/* fault mode detected - for SLAVE /SS pin went high during transmission */
				/* for MASTER /SS pin went low during transmission  */
				ioctl(SPI_0, SPI_CLEAR_MODE_FAULT, NULL); /* clear MODF flag */
				periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_MODE_FAULT, &spi0_status);   
			}
			if (ioctl(SPI_0, SPI_GET_RX_OVERFLOW, NULL))
			{
				/* RX reg. overflow - previous character wasn't read and new one received */
				/* OVRF flag is cleared automatically by SPSCR reading */
				periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_OVERRUN, &spi0_status);   
			}

			/* call error hook */
			#ifdef SPI_0_ERROR_HOOK
			SPI_0_ERROR_HOOK();
			#endif
		}
	
		/* this reading data register (after error checking) clears OVRF and SPRF */ 
		*spi0_RxDataPtr = (SPI0CHAR) ioctl(SPI_0, SPI_READ_DATA, NULL); 

		/* character hook */		
		#ifdef SPI_0_RX_CHAR_HOOK
		if(SPI_0_RX_CHAR_HOOK(*spi0_RxDataPtr))
			return; /* hook returned nonzero: discard received character */	
		#endif
	
		/* advance data pointer */	
		spi0_RxDataPtr++;
		
		/* end of read ? */
		if (!--spi0_RxCounter)
		{
			/* read operation finished */
			periphBitClear(SPI_STATUS_READ_INPROGRESS,&spi0_status);
			/* Rx int disable */
			ioctl(SPI_0, SPI_INT_DISABLE, SPI_RX_FULL);  
			
			/* call end-of-read hook (it may start another non-blocking read) */
			#ifdef SPI_0_RX_FINISHED_HOOK
 			SPI_0_RX_FINISHED_HOOK();
			#endif
		}
	}
	else
	{
		/* Rx int disable */
		ioctl(SPI_0, SPI_INT_DISABLE, SPI_RX_FULL);  
	}
}
#pragma interrupt off


/********************************************************************************
 read_SPI_0_BLOCKING() function performs blocking SPI read
********************************************************************************/

void read_SPI_0_BLOCKING(SPI0CHAR *buf, UWord16 size)
{   
	/* if no read is in progress */
	if (!periphBitTest(SPI_STATUS_READ_INPROGRESS,&spi0_status))
	{
		/* prepare buffer pointer and count variable */   
		spi0_RxDataPtr = buf;
		spi0_RxCounter = size;

		/* note that SPI_STATUS_READ_INPROGRESS stays 0 all the time here */
		while (spi0_RxCounter)
		{
		    /* clear exception if any */		
		    if(ioctl(SPI_0, SPI_GET_ERROR, NULL))
		    {
				if (ioctl(SPI_0, SPI_GET_MODE_FAULT, NULL))
				{
					/* fault mode detected - for SLAVE /SS pin went high during transmission */
					/* for MASTER /SS pin went low during transmission  */
					ioctl(SPI_0, SPI_CLEAR_MODE_FAULT, NULL); /* clear MODF flag */
					periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_MODE_FAULT, &spi0_status);   
				}
				if (ioctl(SPI_0, SPI_GET_RX_OVERFLOW, NULL))
				{
					/* RX reg. overflow - previous character wasn't read and new one received */
					/* OVRF flag is cleared automatically by SPSCR reading */
					periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_OVERRUN, &spi0_status);   
				}

				/* call error hook */
				#ifdef SPI_0_ERROR_HOOK
				SPI_0_ERROR_HOOK();
				#endif
			}
		    	
		    /* data polling mechanism */
			if (ioctl(SPI_0, SPI_GET_RX_FULL, NULL))
			{
				*spi0_RxDataPtr = (SPI0CHAR) ioctl(SPI_0, SPI_READ_DATA, NULL); 
				
				/* character hook */		
				#ifdef SPI_0_RX_CHAR_HOOK
				if(SPI_0_RX_CHAR_HOOK(*spi0_RxDataPtr))
					continue; /* hook returned nonzero: discard received character */	
				#endif
				
				spi0_RxDataPtr++;
				spi0_RxCounter--;
			}
		}
	}
}


/********************************************************************************
 write_SPI_0_NON_BLOCKING() function performs nonblocking SPI write 
********************************************************************************/

void write_SPI_0_NON_BLOCKING(const SPI0CHAR *buf, UWord16 size)
{   
	/* prepare buffer pointer and count variable */
	spi0_TxDataPtr = buf;
	spi0_TxCounter = size;

	/* write in progress */
	periphBitSet(SPI_STATUS_WRITE_INPROGRESS, &spi0_status);  
	
	/* TX int enable */
	ioctl(SPI_0, SPI_TX_EMPTY_INT, SPI_ENABLE ); 
}


/* interrupt handler for uart Tx reg. empty interrupt */
#pragma interrupt on
void Spi0TxEmptyISR(void)
{
	/* call hook to handle character sent */
	#ifdef SPI_0_TX_CHAR_HOOK
	/* user hook may supply his own character (or abort the write op) */
	if(SPI_0_TX_CHAR_HOOK(*spi0_TxDataPtr))
		return; 
	#endif

	/* write byte to Tx reg (this also clears SPTE) */
	ioctl(SPI_0,SPI_WRITE_DATA, *spi0_TxDataPtr++); 

	if (!--spi0_TxCounter)
	{
		/* write operation finished */
		periphBitClear(SPI_STATUS_WRITE_INPROGRESS, &spi0_status);  
		/* TX int disable */
		ioctl(SPI_0, SPI_TX_EMPTY_INT, SPI_DISABLE ); 
		
		#ifdef SPI_0_TX_FINISHED_HOOK
		SPI_0_TX_FINISHED_HOOK();
		#endif
	}
}
#pragma interrupt off


/********************************************************************************
 write_SPI_0_BLOCKING() function performs blocking SPI block write using buffers 
********************************************************************************/

void write_SPI_0_BLOCKING(const SPI0CHAR *buf, UWord16 size)
{
	/* wait if write is currently in progress */   
	while (periphBitTest(SPI_STATUS_WRITE_INPROGRESS, &spi0_status))
	    /* nop */ ;

	spi0_TxDataPtr = buf;
	spi0_TxCounter = size;

	/* disable TX interrupts */
	ioctl(SPI_0, SPI_INT_DISABLE, SPI_TX_EMPTY);
	
	/* this bit can be cleared in the hook procedure */
	while(spi0_TxCounter)
	{
		/* read status and test SPTE bit */
		if ((ioctl(SPI_0, SPI_GET_TX_EMPTY, NULL)))
		{
			/* user hook may supply his own character (or break the loop) */
			#ifdef SPI_0_TX_CHAR_HOOK
			if(SPI_0_TX_CHAR_HOOK(*spi0_TxDataPtr))
				continue;
			#endif

			/* write data register and clear SPTE flag */
	 		ioctl(SPI_0, SPI_WRITE_DATA, *spi0_TxDataPtr++);
	 		spi0_TxCounter--;
	 	}
	}
}

#endif /* SPI_0 */

/* 

Note: use SPI_0 code as a template, duplicate it and use
Replace (Ctrl+H) in selected duplicated code, 

	select "Regular Expression" and specify:

		Find: ([Ss][Pp][Ii]_*)0
		Replace: \11

*/

#ifdef SPI_1

/****************************************************************************
* read_SPI_1_NON_BLOCKING function performs nonblocking SPI read 
*****************************************************************************/

void read_SPI_1_NON_BLOCKING(SPI1CHAR *buf, UWord16 size)
{   
	spi1_RxDataPtr = buf;
	spi1_RxCounter = size;

	/* read in progress */
	periphBitSet(SPI_STATUS_READ_INPROGRESS,&spi1_status);
	
	/* clear pending error if any */		
	if(ioctl(SPI_1, SPI_GET_ERROR, NULL)) /* read SPI status register */
	{
		periphMemDummyRead(&SPI_1->spdrr);			/* clear OVRF */
		ioctl(SPI_1, SPI_CLEAR_MODE_FAULT, NULL);	/* clear MODF */
	}
	
	if(ioctl(SPI_0, SPI_GET_RX_FULL, NULL)) /* read SPI status register */
	{
		periphMemDummyRead(&SPI_0->spdrr);			/* clear SPRF */
	}
	
	ioctl(SPI_1, SPI_INT_ENABLE, SPI_RX_FULL);  /* Rx int enable */
	
	/* receive operations are started when 1St char. is received */
	/* in MASTER mode it is necessary write to SPI to receive char. concurently */
	/* with transmition - transfer is initiated by writing */        
}

/* Spi1RxFullISR() function performs nonblocking SPI block read  */

#pragma interrupt on
void Spi1RxFullISR(void)
{
	/* if read is currently in progress */
	if (periphBitTest(SPI_STATUS_READ_INPROGRESS, &spi1_status))
	{
		/* handle errors */
		if(ioctl(SPI_1, SPI_GET_ERROR, NULL))
		{
			if (ioctl(SPI_1, SPI_GET_MODE_FAULT, NULL))
			{
				/* fault mode detected - for SLAVE /SS pin went high during transmission */
				/* for MASTER /SS pin went low during transmission  */
				ioctl(SPI_1, SPI_CLEAR_MODE_FAULT, NULL); /* clear MODF flag */
				periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_MODE_FAULT, &spi1_status);   
			}
			if (ioctl(SPI_1, SPI_GET_RX_OVERFLOW, NULL))
			{
				/* RX reg. overflow - previous character wasn't read and new one received */
				/* OVRF flag is cleared automatically by SPSCR reading */
				periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_OVERRUN, &spi1_status);   
			}

			/* call error hook */
			#ifdef SPI_1_ERROR_HOOK
			SPI_1_ERROR_HOOK();
			#endif
		}
	
		/* this reading data register (after error checking) clears OVRF and SPRF */ 
		*spi1_RxDataPtr = (SPI1CHAR) ioctl(SPI_1, SPI_READ_DATA, NULL); 

		/* character hook */		
		#ifdef SPI_1_RX_CHAR_HOOK
		if(SPI_1_RX_CHAR_HOOK(*spi1_RxDataPtr))
			return; /* hook returned nonzero: discard received character */	
		#endif
	
		/* advance data pointer */	
		spi1_RxDataPtr++;
		
		/* end of read ? */
		if (!--spi1_RxCounter)
		{
			/* read operation finished */
			periphBitClear(SPI_STATUS_READ_INPROGRESS,&spi1_status);
			/* Rx int disable */
			ioctl(SPI_1, SPI_INT_DISABLE, SPI_RX_FULL);  
			
			/* call end-of-read hook (it may start another non-blocking read) */
			#ifdef SPI_1_RX_FINISHED_HOOK
 			SPI_1_RX_FINISHED_HOOK();
			#endif
		}
	}
	else
	{
		/* Rx int disable */
		ioctl(SPI_1, SPI_INT_DISABLE, SPI_RX_FULL);  
	}
}
#pragma interrupt off


/********************************************************************************
 read_SPI_1_BLOCKING() function performs blocking SPI read
********************************************************************************/

void read_SPI_1_BLOCKING(SPI1CHAR *buf, UWord16 size)
{   
	/* if no read is in progress */
	if (!periphBitTest(SPI_STATUS_READ_INPROGRESS,&spi1_status))
	{
		/* prepare buffer pointer and count variable */   
		spi1_RxDataPtr = buf;
		spi1_RxCounter = size;

		/* note that SPI_STATUS_READ_INPROGRESS stays 0 all the time here */
		while (spi1_RxCounter)
		{
		    /* clear exception if any */		
		    if(ioctl(SPI_1, SPI_GET_ERROR, NULL))
		    {
				if (ioctl(SPI_1, SPI_GET_MODE_FAULT, NULL))
				{
					/* fault mode detected - for SLAVE /SS pin went high during transmission */
					/* for MASTER /SS pin went low during transmission  */
					ioctl(SPI_1, SPI_CLEAR_MODE_FAULT, NULL); /* clear MODF flag */
					periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_MODE_FAULT, &spi1_status);   
				}
				if (ioctl(SPI_1, SPI_GET_RX_OVERFLOW, NULL))
				{
					/* RX reg. overflow - previous character wasn't read and new one received */
					/* OVRF flag is cleared automatically by SPSCR reading */
					periphBitSet(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_OVERRUN, &spi1_status);   
				}

				/* call error hook */
				#ifdef SPI_1_ERROR_HOOK
				SPI_1_ERROR_HOOK();
				#endif
			}
		    	
		    /* data polling mechanism */
			if (ioctl(SPI_1, SPI_GET_RX_FULL, NULL))
			{
				*spi1_RxDataPtr = (SPI1CHAR) ioctl(SPI_1, SPI_READ_DATA, NULL); 
				
				/* character hook */		
				#ifdef SPI_1_RX_CHAR_HOOK
				if(SPI_1_RX_CHAR_HOOK(*spi1_RxDataPtr))
					continue; /* hook returned nonzero: discard received character */	
				#endif
				
				spi1_RxDataPtr++;
				spi1_RxCounter--;
			}
		}
	}
}


/********************************************************************************
 write_SPI_1_NON_BLOCKING() function performs nonblocking SPI write 
********************************************************************************/

void write_SPI_1_NON_BLOCKING(const SPI1CHAR *buf, UWord16 size)
{   
	/* prepare buffer pointer and count variable */
	spi1_TxDataPtr = buf;
	spi1_TxCounter = size;

	/* write in progress */
	periphBitSet(SPI_STATUS_WRITE_INPROGRESS, &spi1_status);  
	
	/* TX int enable */
	ioctl(SPI_1, SPI_TX_EMPTY_INT, SPI_ENABLE ); 
}


/* interrupt handler for uart Tx reg. empty interrupt */

#pragma interrupt on
void Spi1TxEmptyISR(void)
{
	/* call hook to handle character sent */
	#ifdef SPI_1_TX_CHAR_HOOK
	/* user hook may supply his own character (or abort the write op) */
	if(SPI_1_TX_CHAR_HOOK(*spi1_TxDataPtr))
		return; 
	#endif

	/* write byte to Tx reg (this also clears SPTE) */
	ioctl(SPI_1,SPI_WRITE_DATA, *spi1_TxDataPtr++); 

	if (!--spi1_TxCounter)
	{
		/* write operation finished */
		periphBitClear(SPI_STATUS_WRITE_INPROGRESS, &spi1_status);  
		/* TX int disable */
		ioctl(SPI_1, SPI_TX_EMPTY_INT, SPI_DISABLE ); 
		
		#ifdef SPI_1_TX_FINISHED_HOOK
		SPI_1_TX_FINISHED_HOOK();
		#endif
	}
}
#pragma interrupt off


/********************************************************************************
 write_SPI_1_BLOCKING() function performs blocking SPI block write using buffers 
********************************************************************************/

void write_SPI_1_BLOCKING(const SPI1CHAR *buf, UWord16 size)
{
	/* wait if write is currently in progress */   
	while (periphBitTest(SPI_STATUS_WRITE_INPROGRESS, &spi1_status))
	    /* nop */;
	
	spi1_TxDataPtr = buf;
	spi1_TxCounter = size;

	/* disable TX interrupts */
	ioctl(SPI_1, SPI_INT_DISABLE, SPI_TX_EMPTY);
	
	/* this bit can be cleared in the hook procedure */
	while(spi1_TxCounter)
	{
		/* read status and test SPTE bit */
		if ((ioctl(SPI_1, SPI_GET_TX_EMPTY, NULL)))
		{
			/* user hook may supply his own character (or break the loop) */
			#ifdef SPI_1_TX_CHAR_HOOK
			if(SPI_1_TX_CHAR_HOOK(*spi1_TxDataPtr))
				continue;
			#endif

			/* write data register and clear SPTE flag */
	 		ioctl(SPI_1, SPI_WRITE_DATA, *spi1_TxDataPtr++);
	 		spi1_TxCounter--;
	 	}
	}
	
}

#endif /* SPI_1 */



#ifdef __cplusplus
}
#endif
