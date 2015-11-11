/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  sci.h
*
* $Date:      Mar-24-2009$
*
* $Version:   2.3.39.0$
*
* Description: Header file for the SCI driver.
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  SCI_VERSION_1 .. 56F83xx devices, see MC56F8300UM.pdf
*  SCI_VERSION_2 .. 56F801x devices, see MC56F8000RM.pdf
*  SCI_VERSION_3 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  SCI_VERSION_4 .. 56F800x devices ,see MC56F8006.pdf
*
*******************************************************************************/

#ifndef __SCI_H
#define __SCI_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before sci.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
* SCI module identifiers 
*************************************************************/

#ifdef SCI0_BASE
#define SCI_0   (&ArchIO.Sci0)
#endif

#ifdef SCI1_BASE
#define SCI_1   (&ArchIO.Sci1)
#endif

/* single ("anonymous") module on some devices */
#ifdef SCI_BASE
#define SCI     (&ArchIO.Sci)
#define SCI_0   (&ArchIO.Sci) /* aliased to SCI_0 */
#endif

/*************************************************************
* arch.h should define device-specific information about SCI
**************************************************************/

#if !defined(SCI_VERSION)
#error SCI not properly described in arch.h (old Quick_Start version?)
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Serial Communications Interface (SCI) module module allows asynchronous
* serial communications with peripheral devices and other MCs.
* 
* Features
*   • Full-duplex or single wire operation
*   • Standard mark/space Non-Return-to-Zero (NRZ) format
*   • 13-bit baud rate selection
*   • Programmable 8-bit or 9-bit data format
*   • Separately enabled transmitter and receiver
*   • Separate receiver and transmitter MC interrupt requests
*   • Programmable polarity for transmitter and receiver
*   • Two receiver wake up methods:
*      — Idle line
*      — Address mark
*   • Interrupt-driven operation with seven flags:
*      — Transmitter empty
*      — Transmitter idle
*      — Receiver full
*      — Receiver overrun
*      — Noise error
*      — Framing error
*      — Parity error
*   • Receiver framing error detection
*   • Hardware parity checking
*   • 1/16 bit-time noise detection
*
* For more information, please refer to the user manual for the particular
* chip that you are using, such as the MC56F8300 Peripheral Manual,
* for a description of the SCI device.
*
* The SCI device driver interface uses "ioctl" call to control specific
* SCI functions during operation. For details see "ioctl" call.
*
******************************************************************************/

/******************************************************************************
* type of SCI characters and buffers (can be defined as "char" in appconfig.h) 
******************************************************************************/

/* HawkV1 compatible 16bit characters by default */
#ifndef SCI0CHAR
#define SCI0CHAR UWord16    
#endif
#ifndef SCI1CHAR
#define SCI1CHAR UWord16    
#endif

/****************************************************
* Configurable items, i.e. defines, for appconfig.h
*****************************************************

  #define SCI0CHAR char                         // type of SCI character (select char or UWord16)
  #define SCI_CORE_FREQ  4000000                // specify SCI module clock (optional)

  #define INT_VECTOR_ADDR_yy isr_routine        // specify interrupt handler routine
  #define INT_PRIORITY_LEVEL_yy INTC_LEVEL1     // interrupt level : (INTC_DISABLED, INTC_LEVEL0,...INTC_LEVEL2)
  
  #define SCI_0_SCIBR_INIT 0x0000               // initial value for baud-rate register
  #define SCI_0_SCICR_INIT 0x0000               // initial value for control register
  dtto for SCI_1

  #define SCI_0_HIGHLEVEL_MODE 0 | 1 | 2        // select hi-level software layer:
                                                // 0 = none
                                                // 1 = BLOCKING/NON_BLOCKING operation
                                                // 2 = BUFFERED operation

  where:
         yy  is interrupt vector number
         
            e.g. on 56F8346:
                72 - SCI 0 Receiver Full
                71 - SCI 0 Receiver Error
                69 - SCI 0 Transmitter Idle
                68 - SCI 0 Transmitter Empty
                
                46 - SCI 1 Receiver Full
                45 - SCI 1 Receiver Error
                43 - SCI 1 Transmitter Idle
                42 - SCI 1 Transmitter Empty 
        
                
  To enable NON_BLOCKING or BUFFERED SCI_0 read & write functions, do:
  
    #define INT_VECTOR_ADDR_68 Sci0RxFullISR
    #define INT_VECTOR_ADDR_67 Sci0RxErrorISR
    #define INT_VECTOR_ADDR_64 Sci0TxEmptyISR
    #define INT_PRIORITY_LEVEL_68 INTC_LEVEL1
    #define INT_PRIORITY_LEVEL_67 INTC_LEVEL1
    #define INT_PRIORITY_LEVEL_64 INTC_LEVEL1

  To enable BUFFERED operations, also specify the sizes of the buffers
  
    #define SCI_0_RX_BUFFER_SIZE XXX    // size of RX circular buffer (RX disabled when 0 or undefined)
    #define SCI_0_TX_BUFFER_SIZE XXX    // size of TX circular buffer (TX disabled when 0 or undefined)
    #define SCI_0_RX_BUFFER_PTR name    // [optional] name of the buffer to use by RX (allocated when not defined)
    #define SCI_0_TX_BUFFER_PTR name    // [optional] name of the buffer to use by TX (allocated when not defined)

  To activate buffer space monitoring during BUFFERED operation
  
    #define SCI_0_RX_BUFFER_LOWLIMIT 10  // buffer is considered low if free space sinks bellow this number 
    #define SCI_0_RX_BUFFER_OKLIMIT  15  // [optional] buffer is considered OK if free space grows above this number 
                                            (when not defined, SCI_0_RX_BUFFER_LOWLIMIT is used)
    
    #define SCI_0_RX_XONXOFF 1           // implement XON/XOFF signaling for receiveing buffer
    #define SCI_0_XONCHAR   0x11         // [optional] XON character (when not defined, 0x11 is used)
    #define SCI_0_XOFFCHAR  0x13         // [optional] XOFF character (when not defined, 0x13 is used)

  To install read & write hooks, define
  
    #define SCI_0_RX_CHAR_HOOK       rx_char_hook       // all operations
    #define SCI_0_RX_ERROR_HOOK      rx_error_hook      // all operations
    #define SCI_0_TX_CHAR_HOOK       tx_char_hook       // all operations
    #define SCI_0_RX_FINISHED_HOOK   rx_finished_hook   // NON_BLOCKING operation only 
    #define SCI_0_TX_FINISHED_HOOK   tx_finished_hook   // NON_BLOCKING operation only 
    #define SCI_0_RX_LOWBUFFER_HOOK  rx_lowbuffer_hook  // BUFFERED operation only 

  where:
  
    UWord16 rx_char_hook(UWord16 rxchar)  // is called for each character received (both bl/nobl), 
                                          // return nonzero to discard received character
                                          // return zero to accept received character
                                          // you can use SCI_READ_CANCEL command to abort operation
                                          
    void rx_finished_hook(void)           // called when non-blocking read finishes
    
    void rx_error_hook(void)              // called when error occures during read (both bl/nonbl)
                                          // read SCI_x->scisr to get status register
    
    UWord16 tx_char_hook(UWord16 txchar)  // called after each character transmitted (both bl/nonbl)
                                          // return nonzero to not to transmit next buffered character 
                                                (you have to write SCIDR yourself using SCI_WRITE_DATA)
                                          // return zero to continue with transmission
                                          // you can use SCI_WRITE_CANCEL command to abort operation
                                          
    void tx_finished_hook(void)           // called when non-blocking write finishes

    void rx_lowbuffer_hook(bool bIsFull)  // called when circular buffer is near to be full during
                                             BUFFERED operation. The "bIsFull" is "true" when buffer
                                             just get full or "false" when it is getting free again.
    

  In any hook function, you can issue new (NON_BLOCKING or BUFFERED) read or write operation. 
   
*/

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl(SCI_module_identifier, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                      PARAMETERS, COMMENTS
--------------------------------------------------------*/

#define SCI_INIT                 /* NULL */
#define SCI_SET_BAUDRATE         /* One of the SCI_BAUDxxx constants (or divisor value) */
#define SCI_OPERATING_MODE       /* SCI_NORMAL_MODE | SCI_INTERNAL_LOOP_MODE | SCI_SINGLE_WIRE_MODE */
#define SCI_TRANSMITTER          /* SCI_ENABLE / SCI_DISABLE */
#define SCI_RECEIVER             /* SCI_ENABLE / SCI_DISABLE */
#define SCI_WAKEUP_CONDITION     /* SCI_WAKE_BY_ADDRESS / SCI_WAKE_BY_IDLE */
#define SCI_WAIT                 /* NULL */
#define SCI_WAKEUP               /* NULL */
#define SCI_DATA_FORMAT          /* SCI_WORD_9BIT / SCI_WORD_8BIT */
#define SCI_PARITY               /* SCI_PARITY_ODD / SCI_PARITY_EVEN / SCI_PARITY_NONE */
#define SCI_DATA_POLARITY        /* SCI_INVERTED / SCI_NOT_INVERTED */
#define SCI_STOP_IN_WAIT         /* SCI_ENABLE / SCI_DISABLE */
#define SCI_SEND_BREAK           /* NULL */

#define SCI_TX_EMPTY_INT         /* SCI_ENABLE / SCI_DISABLE */
#define SCI_TX_IDLE_INT          /* SCI_ENABLE / SCI_DISABLE */
#define SCI_RX_FULL_INT          /* SCI_ENABLE / SCI_DISABLE */
#define SCI_RX_ERROR_INT         /* SCI_ENABLE / SCI_DISABLE */
#define SCI_INT_ENABLE           /* SCI_TX_EMPTY | SCI_TX_IDLE | SCI_RX_FULL | SCI_RX_ERROR | SCI_RX_IDLE */
#define SCI_INT_DISABLE          /* SCI_TX_EMPTY | SCI_TX_IDLE | SCI_RX_FULL | SCI_RX_ERROR | SCI_RX_IDLE */

#define SCI_READ_CONTROL_REG     /* NULL */
#define SCI_WRITE_CONTROL_REG    /* UWord16 */

#define SCI_GET_STATUS_REG       /* NULL */
#define SCI_CLEAR_STATUS_REG     /* NULL */
#define SCI_TEST_STATUS_REG      /* SCI_TX_EMPTY_FLAG | SCI_TX_IDLE_FLAG | SCI_RX_FULL_FLAG | 
                                    SCI_RX_IDLE_LINE_FLAG | SCI_OVERRUN_FLAG | SCI_NOISE_FLAG | 
                                    SCI_FRAMING_ERROR_FLAG | SCI_PARITY_ERROR_FLAG | SCI_RX_ACTIVE_FLAG |
                                    SCI_LIN_SYNC_ERROR_FLAG (not all platforms) */

#define SCI_READ_DATA            /* NULL */
#define SCI_WRITE_DATA           /* UWord16 */

#define SCI_GET_TX_EMPTY         /* NULL */
#define SCI_GET_TX_IDLE          /* NULL */
#define SCI_GET_RX_FULL          /* NULL */
#define SCI_GET_RX_IDLE          /* NULL */
#define SCI_GET_ERROR            /* NULL */
#define SCI_GET_RX_OVERRUN       /* NULL */
#define SCI_GET_RX_NOISE_ERROR   /* NULL */
#define SCI_GET_RX_FRAMING_ERROR /* NULL */
#define SCI_GET_RX_PARITY_ERROR  /* NULL */
#define SCI_GET_RX_ACTIVE        /* NULL */

/****************************************************************************
* SCI Version 2 commands (801x)
*****************************************************************************/

#if SCI_VERSION >= 2 
#define SCI_LIN_MODE             /* SCI_ENABLE / SCI_DISABLE */
#define SCI_GET_LIN_SYNC_ERROR   /* NULL */
#endif

/****************************************************************************
* SCI Version 3 commands (802x3x)
*****************************************************************************/

#if SCI_VERSION == 3
#define SCI_QUEUED_MODE           /* SCI_ENABLE / SCI_DISABLE, enable SCI FIFOs */
#define SCI_SET_TXEMPTY_CONDITION /* SCI_TXEMPTY_WHEN_xxx, or value 0..3 how many words in TX FIFO causes TXEMPTY condition */
#define SCI_SET_RXFULL_CONDITION  /* SCI_RXFULL_WHEN_xxx, or value 0..3 how many words (plus 1) in RX FIFO causes RXFULL condition */
#define SCI_CAN_READ_DATA         /* NULL, returns non-zero if valid data are waiting in receive FIFO */
#define SCI_CAN_WRITE_DATA        /* NULL, returns non-zero if free space in TX FIFO enables data write */
#endif


/****************************************************************************
* high-level ioctl commands
*****************************************************************************/

#define SCI_GET_STATUS           /* NULL */
#define SCI_CLEAR_EXCEPTION      /* NULL */

/* for BLOCKING/NON_BLOCKING read/write operation */
#define SCI_WRITE_CANCEL         /* NULL */
#define SCI_READ_CANCEL          /* NULL */

/* for BUFFERED read/write operation */
#define SCI_BUFFERED_RX         /* SCI_ENABLE / SCI_DISABLE */
#define SCI_BUFFERED_TX         /* SCI_ENABLE / SCI_DISABLE */
#define SCI_GET_RX_CHARS_READY  /* NULL */
#define SCI_GET_RX_BUFFER_FREESPACE /* NULL */
#define SCI_GET_TX_BUFFER_FREESPACE /* NULL */
#define SCI_SEND_XON            /* signalize XON condition */
#define SCI_SEND_XOFF           /* signalize XOFF condition */

/****************************************************************************
* read/write modes of operation
*****************************************************************************/

#define BLOCKING      /* blocking mode for read/write functions */
#define NON_BLOCKING  /* non-blocking mode for read/write functions */
#define BUFFERED      /* buffered in circular buffer - implemented in scib.

/* Note: 

    BLOCKING and NON_BLOCKING are implemented in scibl.c
    BUFFERED is implemented in scibf.c. Compile the sci.c.

!!  BUFFERED is mutually exclusive to BLOCKING/NON_BLOCKING !!
*/

/****************************************************************************
* SCI constants use in the ioctl functions (command parameters)
*****************************************************************************/

#define SCI_ENABLE               1
#define SCI_DISABLE              0

#define SCI_NORMAL_MODE          0
#define SCI_INTERNAL_LOOP_MODE   SCI_SCICR_LOOP
#define SCI_SINGLE_WIRE_MODE     (SCI_SCICR_LOOP | SCI_SCICR_RSRC)

#define SCI_WAKE_BY_ADDRESS      1 
#define SCI_WAKE_BY_IDLE         0 

#define SCI_WORD_9BIT            1 
#define SCI_WORD_8BIT            0 

#define SCI_PARITY_NONE          0
#define SCI_PARITY_EVEN          SCI_SCICR_PE
#define SCI_PARITY_ODD           (SCI_SCICR_PE | SCI_SCICR_PT)

#define SCI_NOT_INVERTED         0 
#define SCI_INVERTED             1 

#define SCI_TX_EMPTY    SCI_SCICR_TEIE
#define SCI_TX_IDLE     SCI_SCICR_TIIE
#define SCI_RX_FULL     SCI_SCICR_RFIE
#define SCI_RX_ERROR    SCI_SCICR_REIE

#if SCI_VERSION == 3
/* TXEMPTY condition */
#define SCI_TXEMPTY_WHEN_FIFO_EMPTY        0
#define SCI_TXEMPTY_WHEN_1_OR_LESS_IN_FIFO 1
#define SCI_TXEMPTY_WHEN_2_OR_LESS_IN_FIFO 2
#define SCI_TXEMPTY_WHEN_3_OR_LESS_IN_FIFO 3

/* RXFULL condition */
#define SCI_RXFULL_WHEN_1_OR_MORE_IN_FIFO  0
#define SCI_RXFULL_WHEN_2_OR_MORE_IN_FIFO  1
#define SCI_RXFULL_WHEN_3_OR_MORE_IN_FIFO  2
#define SCI_RXFULL_WHEN_4_OR_MORE_IN_FIFO  3
#endif /* SCI_VERSION == 3 */

/* end-of-life: */
#define SCI_LOOP_DISABLE         0
#define SCI_LOOP_ENABLE          SCI_SCICR_LOOP
#define SCI_LOOP_SINGLE_WIRE     (SCI_SCICR_LOOP | SCI_SCICR_RSRC)

/* XON/XOFF characters for BUFFERED operation implemented in scib.c */

#ifndef SCI_0_XONCHAR
#define SCI_0_XONCHAR  0x11
#endif
#ifndef SCI_0_XOFFCHAR
#define SCI_0_XOFFCHAR 0x13
#endif

#ifndef SCI_1_XONCHAR
#define SCI_1_XONCHAR  0x11
#endif
#ifndef SCI_1_XOFFCHAR
#define SCI_1_XOFFCHAR 0x13
#endif

/* low/ok limits for detecting the receiver's buffer-full and buffer-ok conditions 
 * define ok-limit if it is not defined and low-limit detection is activated */
 
#if defined(SCI_0_RX_BUFFER_LOWLIMIT) && !defined(SCI_0_RX_BUFFER_OKLIMIT)
#define SCI_0_RX_BUFFER_OKLIMIT SCI_0_RX_BUFFER_LOWLIMIT
#endif

#if SCI_0_RX_BUFFER_LOWLIMIT > SCI_0_RX_BUFFER_OKLIMIT
#warning possibly invalid condition SCI_0_RX_BUFFER_LOWLIMIT > SCI_0_RX_BUFFER_OKLIMIT
#endif

/* if SCI_CORE_FREQ (SCI clock) is not defined in appconfig.h, take it from OCCS */

#if !defined(SCI_CORE_FREQ) && defined(EXTCLK)

    /* use the OCCS value */
    #ifdef OCCS_CORE_FREQ
        #define SCI_CORE_FREQ OCCS_CORE_FREQ
    
    #else   
        /* warn user that baudrate constants will not be available */
        #if !SCI_DISABLE_BAUDRATE_WARNING
        #warning Can not calculate SCI_CORE_FREQ, please include occs.h before sci.h
        #endif
        
    #endif /* OCCS_CORE_FREQ */
#endif /* !SCI_CORE_FREQ && EXTCLK */

/* SCI baud rates only for various core frequency (SCI_CORE_FREQ) */
/* scrip generated: see script code below */

#ifdef SCI_CORE_FREQ

#if (SCI_CORE_FREQ) == 80000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	   22	// error 1.36% (real: 227273) 
#define SCI_BAUD_115200	   43	// error 0.94% (real: 116279) 
#define SCI_BAUD_76800	   65	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   87	// error 0.22% (real: 57471) 
#define SCI_BAUD_38400	  130	// error 0.16% (real: 38462) 
#define SCI_BAUD_28800	  174	// error 0.22% (real: 28736) 
#define SCI_BAUD_19200	  260	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	  347	// error 0.06% (real: 14409) 
#define SCI_BAUD_9600	  521	// error 0.03% (real: 9597) 
#define SCI_BAUD_4800	 1042	// error 0.04% (real: 4798) 
#define SCI_BAUD_2400	 2083	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 4167	// error 0.00% (real: 1200) 

#elif (SCI_CORE_FREQ) == 60000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	   16	// error 1.73% (real: 234375) 
#define SCI_BAUD_115200	   33	// error 1.36% (real: 113636) 
#define SCI_BAUD_76800	   49	// error 0.35% (real: 76531) 
#define SCI_BAUD_57600	   65	// error 0.16% (real: 57692) 
#define SCI_BAUD_38400	   98	// error 0.35% (real: 38265) 
#define SCI_BAUD_28800	  130	// error 0.16% (real: 28846) 
#define SCI_BAUD_19200	  195	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	  260	// error 0.16% (real: 14423) 
#define SCI_BAUD_9600	  391	// error 0.09% (real: 9591) 
#define SCI_BAUD_4800	  781	// error 0.04% (real: 4802) 
#define SCI_BAUD_2400	 1563	// error 0.04% (real: 2399) 
#define SCI_BAUD_1200	 3125	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 6250	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 52000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	   14	// error 0.76% (real: 232143) 
#define SCI_BAUD_115200	   28	// error 0.76% (real: 116071) 
#define SCI_BAUD_76800	   42	// error 0.76% (real: 77381) 
#define SCI_BAUD_57600	   56	// error 0.76% (real: 58036) 
#define SCI_BAUD_38400	   85	// error 0.43% (real: 38235) 
#define SCI_BAUD_28800	  113	// error 0.14% (real: 28761) 
#define SCI_BAUD_19200	  169	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	  226	// error 0.13% (real: 14381) 
#define SCI_BAUD_9600	  339	// error 0.14% (real: 9587) 
#define SCI_BAUD_4800	  677	// error 0.02% (real: 4801) 
#define SCI_BAUD_2400	 1354	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 2708	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 5417	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 40000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	   11	// error 1.36% (real: 227273) 
#define SCI_BAUD_115200	   22	// error 1.36% (real: 113636) 
#define SCI_BAUD_76800	   33	// error 1.36% (real: 75758) 
#define SCI_BAUD_57600	   43	// error 0.94% (real: 58140) 
#define SCI_BAUD_38400	   65	// error 0.16% (real: 38462) 
#define SCI_BAUD_28800	   87	// error 0.22% (real: 28736) 
#define SCI_BAUD_19200	  130	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	  174	// error 0.22% (real: 14368) 
#define SCI_BAUD_9600	  260	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  521	// error 0.04% (real: 4798) 
#define SCI_BAUD_2400	 1042	// error 0.04% (real: 2399) 
#define SCI_BAUD_1200	 2083	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 4167	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 32000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	    9	// error 3.55% (real: 222222) 
#define SCI_BAUD_115200	   17	// error 2.12% (real: 117647) 
#define SCI_BAUD_76800	   26	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   35	// error 0.79% (real: 57143) 
#define SCI_BAUD_38400	   52	// error 0.16% (real: 38462) 
#define SCI_BAUD_28800	   69	// error 0.65% (real: 28986) 
#define SCI_BAUD_19200	  104	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	  139	// error 0.08% (real: 14388) 
#define SCI_BAUD_9600	  208	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  417	// error 0.08% (real: 4796) 
#define SCI_BAUD_2400	  833	// error 0.04% (real: 2401) 
#define SCI_BAUD_1200	 1667	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 3333	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 20000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	    5	// error 8.51% (real: 250000) 
#define SCI_BAUD_115200	   11	// error 1.36% (real: 113636) 
#define SCI_BAUD_76800	   16	// error 1.73% (real: 78125) 
#define SCI_BAUD_57600	   22	// error 1.36% (real: 56818) 
#define SCI_BAUD_38400	   33	// error 1.36% (real: 37879) 
#define SCI_BAUD_28800	   43	// error 0.94% (real: 29070) 
#define SCI_BAUD_19200	   65	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	   87	// error 0.22% (real: 14368) 
#define SCI_BAUD_9600	  130	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  260	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	  521	// error 0.04% (real: 2399) 
#define SCI_BAUD_1200	 1042	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 2083	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 16000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	    4	// error 8.51% (real: 250000) 
#define SCI_BAUD_115200	    9	// error 3.55% (real: 111111) 
#define SCI_BAUD_76800	   13	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   17	// error 2.12% (real: 58824) 
#define SCI_BAUD_38400	   26	// error 0.16% (real: 38462) 
#define SCI_BAUD_28800	   35	// error 0.80% (real: 28571) 
#define SCI_BAUD_19200	   52	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	   69	// error 0.65% (real: 14493) 
#define SCI_BAUD_9600	  104	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  208	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	  417	// error 0.08% (real: 2398) 
#define SCI_BAUD_1200	  833	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 1667	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 8000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	    2	// error 8.51% (real: 250000) 
#define SCI_BAUD_115200	    4	// error 8.51% (real: 125000) 
#define SCI_BAUD_76800	    7	// error 6.99% (real: 71429) 
#define SCI_BAUD_57600	    9	// error 3.55% (real: 55556) 
#define SCI_BAUD_38400	   13	// error 0.16% (real: 38462) 
#define SCI_BAUD_28800	   17	// error 2.12% (real: 29412) 
#define SCI_BAUD_19200	   26	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	   35	// error 0.79% (real: 14286) 
#define SCI_BAUD_9600	   52	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  104	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	  208	// error 0.17% (real: 2404) 
#define SCI_BAUD_1200	  417	// error 0.08% (real: 1199) 
#define SCI_BAUD_600	  833	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 4000000 && SCI_VERSION <= 2
#define SCI_BAUD_230400	    1	// error 8.51% (real: 250000) 
#define SCI_BAUD_115200	    2	// error 8.51% (real: 125000) 
#define SCI_BAUD_76800	    3	// error 8.51% (real: 83333) 
#define SCI_BAUD_57600	    4	// error 8.51% (real: 62500) 
#define SCI_BAUD_38400	    7	// error 6.99% (real: 35714) 
#define SCI_BAUD_28800	    9	// error 3.55% (real: 27778) 
#define SCI_BAUD_19200	   13	// error 0.16% (real: 19231) 
#define SCI_BAUD_14400	   17	// error 2.12% (real: 14706) 
#define SCI_BAUD_9600	   26	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	   52	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	  104	// error 0.17% (real: 2404) 
#define SCI_BAUD_1200	  208	// error 0.17% (real: 1202) 
#define SCI_BAUD_600	  417	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 2000000 && SCI_VERSION <= 2
#define SCI_BAUD_115200	    1	// error 8.51% (real: 125000) 
#define SCI_BAUD_57600	    2	// error 8.51% (real: 62500) 
#define SCI_BAUD_38400	    3	// error 8.51% (real: 41667) 
#define SCI_BAUD_28800	    4	// error 8.51% (real: 31250) 
#define SCI_BAUD_19200	    7	// error 6.99% (real: 17857) 
#define SCI_BAUD_14400	    9	// error 3.55% (real: 13889) 
#define SCI_BAUD_9600	   13	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	   26	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	   52	// error 0.17% (real: 2404) 
#define SCI_BAUD_1200	  104	// error 0.17% (real: 1202) 
#define SCI_BAUD_600	  208	// error 0.17% (real: 601) 

#elif (SCI_CORE_FREQ) == 1000000 && SCI_VERSION <= 2
#define SCI_BAUD_57600	    1	// error 8.51% (real: 62500) 
#define SCI_BAUD_28800	    2	// error 8.51% (real: 31250) 
#define SCI_BAUD_19200	    3	// error 8.51% (real: 20833) 
#define SCI_BAUD_14400	    4	// error 8.51% (real: 15625) 
#define SCI_BAUD_9600	    7	// error 6.99% (real: 8929) 
#define SCI_BAUD_4800	   13	// error 0.17% (real: 4808) 
#define SCI_BAUD_2400	   26	// error 0.17% (real: 2404) 
#define SCI_BAUD_1200	   52	// error 0.17% (real: 1202) 
#define SCI_BAUD_600	  104	// error 0.17% (real: 601) 

#elif (SCI_CORE_FREQ) == 32000000 && SCI_VERSION >= 3
#define SCI_BAUD_230400	   69	// error 0.64% (real: 231884) 
#define SCI_BAUD_115200	  138	// error 0.64% (real: 115942) 
#define SCI_BAUD_76800	  208	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	  277	// error 0.28% (real: 57761) 
#define SCI_BAUD_38400	  416	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	  555	// error 0.10% (real: 28828) 
#define SCI_BAUD_19200	  833	// error 0.04% (real: 19207) 
#define SCI_BAUD_14400	 1111	// error 0.01% (real: 14401) 
#define SCI_BAUD_9600	 1666	// error 0.03% (real: 9603) 
#define SCI_BAUD_4800	 3333	// error 0.00% (real: 4800) 
#define SCI_BAUD_2400	 6666	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	13333	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	26666	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 20000000 && SCI_VERSION >= 3
#define SCI_BAUD_230400	   43	// error 0.94% (real: 232558) 
#define SCI_BAUD_115200	   86	// error 0.94% (real: 116279) 
#define SCI_BAUD_76800	  130	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	  173	// error 0.35% (real: 57803) 
#define SCI_BAUD_38400	  260	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	  347	// error 0.06% (real: 28818) 
#define SCI_BAUD_19200	  520	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	  694	// error 0.06% (real: 14409) 
#define SCI_BAUD_9600	 1041	// error 0.06% (real: 9606) 
#define SCI_BAUD_4800	 2083	// error 0.00% (real: 4800) 
#define SCI_BAUD_2400	 4166	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 8333	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	16666	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 16000000 && SCI_VERSION >= 3
#define SCI_BAUD_230400	   34	// error 2.12% (real: 235294) 
#define SCI_BAUD_115200	   69	// error 0.64% (real: 115942) 
#define SCI_BAUD_76800	  104	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	  138	// error 0.64% (real: 57971) 
#define SCI_BAUD_38400	  208	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	  277	// error 0.28% (real: 28880) 
#define SCI_BAUD_19200	  416	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	  555	// error 0.10% (real: 14414) 
#define SCI_BAUD_9600	  833	// error 0.03% (real: 9603) 
#define SCI_BAUD_4800	 1666	// error 0.02% (real: 4801) 
#define SCI_BAUD_2400	 3333	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 6666	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	13333	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 8000000 && SCI_VERSION >= 3
#define SCI_BAUD_230400	   17	// error 2.12% (real: 235294) 
#define SCI_BAUD_115200	   34	// error 2.12% (real: 117647) 
#define SCI_BAUD_76800	   52	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   69	// error 0.64% (real: 57971) 
#define SCI_BAUD_38400	  104	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	  138	// error 0.64% (real: 28985) 
#define SCI_BAUD_19200	  208	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	  277	// error 0.28% (real: 14440) 
#define SCI_BAUD_9600	  416	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  833	// error 0.02% (real: 4801) 
#define SCI_BAUD_2400	 1666	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 3333	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 6666	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 4000000 && SCI_VERSION >= 3
#define SCI_BAUD_230400	    8	// error 8.51% (real: 250000) 
#define SCI_BAUD_115200	   17	// error 2.12% (real: 117647) 
#define SCI_BAUD_76800	   26	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   34	// error 2.12% (real: 58823) 
#define SCI_BAUD_38400	   52	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	   69	// error 0.64% (real: 28985) 
#define SCI_BAUD_19200	  104	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	  138	// error 0.64% (real: 14492) 
#define SCI_BAUD_9600	  208	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  416	// error 0.15% (real: 4807) 
#define SCI_BAUD_2400	  833	// error 0.00% (real: 2400) 
#define SCI_BAUD_1200	 1666	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 3333	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 2000000 && SCI_VERSION >= 3
#define SCI_BAUD_115200	    8	// error 8.51% (real: 125000) 
#define SCI_BAUD_76800	   13	// error 0.16% (real: 76923) 
#define SCI_BAUD_57600	   17	// error 2.12% (real: 58823) 
#define SCI_BAUD_38400	   26	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	   34	// error 2.12% (real: 29411) 
#define SCI_BAUD_19200	   52	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	   69	// error 0.64% (real: 14492) 
#define SCI_BAUD_9600	  104	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  208	// error 0.15% (real: 4807) 
#define SCI_BAUD_2400	  416	// error 0.12% (real: 2403) 
#define SCI_BAUD_1200	  833	// error 0.00% (real: 1200) 
#define SCI_BAUD_600	 1666	// error 0.00% (real: 600) 

#elif (SCI_CORE_FREQ) == 1000000 && SCI_VERSION >= 3
#define SCI_BAUD_57600	    8	// error 8.51% (real: 62500) 
#define SCI_BAUD_38400	   13	// error 0.16% (real: 38461) 
#define SCI_BAUD_28800	   17	// error 2.12% (real: 29411) 
#define SCI_BAUD_19200	   26	// error 0.16% (real: 19230) 
#define SCI_BAUD_14400	   34	// error 2.12% (real: 14705) 
#define SCI_BAUD_9600	   52	// error 0.16% (real: 9615) 
#define SCI_BAUD_4800	  104	// error 0.15% (real: 4807) 
#define SCI_BAUD_2400	  208	// error 0.12% (real: 2403) 
#define SCI_BAUD_1200	  416	// error 0.08% (real: 1201) 
#define SCI_BAUD_600	  833	// error 0.00% (real: 600) 

/*
  --- Add your BAUD rate definitions HERE ---
 */

#elif !SCI_DISABLE_BAUDRATE_WARNING

/* Note for the user: you can use the PERL script to generate the SCI_BAUD values 
   for your exotic core speed. See the PERL script at the end of this file. */
#warning Baud rate generator constants not available for this value of SCI_CORE_FREQ

#endif /* no other SCI_CORE_FREQ */
#endif /* SCI_CORE_FREQ */


/* status bits generated by read/write functions -> SCI0_GET_STATUS, SCI1_GET_STATUS commands */

#define SCI_STATUS_WRITE_INPROGRESS       0x0010    /* write to SCI is in progress */
#define SCI_STATUS_READ_INPROGRESS        0x0020    /* read from SCI is in progress */
#define SCI_STATUS_EXCEPTION_EXIST        0x0040    /* exception exists - HW exception if only this flag is set
                                                                        - SW exception if other exception flags are set */
#define SCI_STATUS_RX_BUFFER_LOW          0x0080    /* RX circular buffer near to be full */
#define SCI_STATUS_XOFF_PENDING           0x0100    /* internal flag */
#define SCI_STATUS_XON_PENDING            0x0200    /* internal flag */

#define SCI_EXCEPTION_BUFFER_OVERFLOW     0x0008    /* buffer overflow - some bytes were thrown away */

#define SCI_TX_EMPTY_FLAG                 SCI_SCISR_TDRE
#define SCI_TX_IDLE_FLAG                  SCI_SCISR_TIDLE
#define SCI_RX_FULL_FLAG                  SCI_SCISR_RDRF 
#define SCI_RX_IDLE_LINE_FLAG             SCI_SCISR_RIDLE
#define SCI_OVERRUN_FLAG                  SCI_SCISR_OR   
#define SCI_NOISE_FLAG                    SCI_SCISR_NF   
#define SCI_FRAMING_ERROR_FLAG            SCI_SCISR_FE   
#define SCI_PARITY_ERROR_FLAG             SCI_SCISR_PF   
#define SCI_RX_ACTIVE_FLAG                SCI_SCISR_RAF  

#if SCI_VERSION >= 2
#define SCI_LIN_SYNC_ERROR_FLAG           SCI_SCISR_LSE
#endif

/* high level driver modes */
#define SCI_HIGHLEVEL_MODE_NONE       0
#define SCI_HIGHLEVEL_MODE_BLOCKING   1
#define SCI_HIGHLEVEL_MODE_BUFFERED   2

/*****************************************************************
* SCI Register Bits Defines, used in ioctl command implementation
******************************************************************/

/* SCI BAud Rate Register bits */
#if SCI_VERSION <= 2
#define SCI_SCIBR_SBR_MASK       0x1fff
#else /* SCI_VERSION >= 3*/
#define SCI_SCIBR_SBR_MASK       0xfff8
#define SCI_SCIBR_FRAC_SBR_MASK  0x0003
#endif

/* SCI Control Register bits */
#define SCI_SCICR_LOOP        0x8000
#define SCI_SCICR_SWAI        0x4000
#define SCI_SCICR_RSRC        0x2000
#define SCI_SCICR_M           0x1000
#define SCI_SCICR_WAKE        0x0800
#define SCI_SCICR_POL         0x0400
#define SCI_SCICR_PE          0x0200
#define SCI_SCICR_PT          0x0100
#define SCI_SCICR_TEIE        0x0080
#define SCI_SCICR_TIIE        0x0040
#define SCI_SCICR_RFIE        0x0020
#define SCI_SCICR_REIE        0x0010
#define SCI_SCICR_TE          0x0008
#define SCI_SCICR_RE          0x0004
#define SCI_SCICR_RWU         0x0002
#define SCI_SCICR_SBK         0x0001

/* SCI Control Register 2 bits */
#if SCI_VERSION >= 2
#define SCI_SCICR2_LIN_MODE   0x0008
#endif
#if SCI_VERSION == 3
#define SCI_SCICR2_FIFO_EN    0x0020
#define SCI_SCICR2_RFWM_MASK  0x00c0
#define SCI_SCICR2_RFCNT_MASK 0x0700
#define SCI_SCICR2_RFCNT_FULL 0x0400
#define SCI_SCICR2_TFWM_MASK  0x1800
#define SCI_SCICR2_TFCNT_MASK 0xe000
#define SCI_SCICR2_TFCNT_FULL 0x8000
#endif

/* SCI Status registers bits */
#define SCI_SCISR_TDRE        0x8000
#define SCI_SCISR_TIDLE       0x4000
#define SCI_SCISR_RDRF        0x2000
#define SCI_SCISR_RIDLE       0x1000
#define SCI_SCISR_OR          0x0800
#define SCI_SCISR_NF          0x0400
#define SCI_SCISR_FE          0x0200
#define SCI_SCISR_PF          0x0100
#define SCI_SCISR_RAF         0x0001

#if SCI_VERSION >= 2
#define SCI_SCISR_LSE         0x0008
#endif


/*******************************************************************************
    Bit names of older SDK version, maintained here for backward compatibility.
*******************************************************************************/

/* Do not use for new development ! */
#define SCI_LOOP    SCI_SCICR_LOOP     
#define SCI_SWAI    SCI_SCICR_SWAI    
#define SCI_RSRC    SCI_SCICR_RSRC    
#define SCI_M       SCI_SCICR_M       
#define SCI_WAKE    SCI_SCICR_WAKE    
#define SCI_POL     SCI_SCICR_POL     
#define SCI_PE      SCI_SCICR_PE      
#define SCI_PT      SCI_SCICR_PT      
#define SCI_TEIE    SCI_SCICR_TEIE    
#define SCI_TIIE    SCI_SCICR_TIIE    
#define SCI_RIE     SCI_SCICR_RFIE    
#define SCI_REIE    SCI_SCICR_REIE    
#define SCI_TE      SCI_SCICR_TE      
#define SCI_RE      SCI_SCICR_RE
#define SCI_RWU     SCI_SCICR_RWU
#define SCI_SBK     SCI_SCICR_SBK    
#define SCI_TDRE    SCI_SCISR_TDRE 
#define SCI_TIDLE   SCI_SCISR_TIDLE   
#define SCI_RDRF    SCI_SCISR_RDRF    
#define SCI_RIDLE   SCI_SCISR_RIDLE   
#define SCI_OR      SCI_SCISR_OR      
#define SCI_NF      SCI_SCISR_NF      
#define SCI_FE      SCI_SCISR_FE      
#define SCI_PF      SCI_SCISR_PF      
#define SCI_RAF     SCI_SCISR_RAF   

/***********************************************************************
* status variables for (NON)BLOCKING read/write functions
***********************************************************************/

extern volatile UWord16 sci0_status;
extern volatile UWord16 sci1_status;
extern volatile UWord16 sci0_RxCounter;
extern volatile UWord16 sci1_RxCounter;
extern volatile UWord16 sci0_TxCounter;
extern volatile UWord16 sci1_TxCounter;

/***********************************************************************
* ioctl implementation
***********************************************************************/

/* module names for internal use in ioctl implementation */

#define __SCI_0 SCI_0

#ifdef SCI_1
#define __SCI_1 SCI_1
#else
#define __SCI_1 ((arch_sSCI*)NULL)
#endif

/* SCI Init */

void sciInit(arch_sSCI *sciBase);
#define ioctlSCI_INIT(sciBase, param) sciInit(sciBase)

/* SCI Baud Rate Register */

#define ioctlSCI_SET_BAUDRATE(pSciBase, param) \
    periphMemWrite(param, &((pSciBase)->scibr)) 
            
/* SCI Control Register */

#define ioctlSCI_OPERATING_MODE(pSciBase, param) \
  periphBitGrpRS(SCI_SCICR_LOOP | SCI_SCICR_RSRC, param, &((pSciBase)->scicr))
  
#define ioctlSCI_TRANSMITTER(pSciBase, param)       \
  if (param) periphBitSet (SCI_SCICR_TE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_TE, &((pSciBase)->scicr))

#define ioctlSCI_RECEIVER(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR_RE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_RE, &((pSciBase)->scicr))

#define ioctlSCI_WAKEUP_CONDITION(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR_WAKE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_WAKE, &((pSciBase)->scicr))

#define ioctlSCI_DATA_FORMAT(pSciBase, param)       \
  if (param) periphBitSet (SCI_SCICR_M, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_M, &((pSciBase)->scicr))

#define ioctlSCI_PARITY(pSciBase, param)        \
  periphBitGrpRS(SCI_SCICR_PE | SCI_SCICR_PT, param, &((pSciBase)->scicr))

#define ioctlSCI_DATA_POLARITY(pSciBase, param)     \
  if (param) periphBitSet (SCI_SCICR_POL, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_POL, &((pSciBase)->scicr))

#define ioctlSCI_STOP_IN_WAIT(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR_SWAI, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_SWAI, &((pSciBase)->scicr))\

#define ioctlSCI_SEND_BREAK(pSciBase, param)        \
  { periphBitSet (SCI_SCICR_SBK, &((pSciBase)->scicr)); \
    periphBitClear (SCI_SCICR_SBK, &((pSciBase)->scicr)); }

#define ioctlSCI_TX_EMPTY_INT(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR_TEIE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_TEIE, &((pSciBase)->scicr))

#define ioctlSCI_TX_IDLE_INT(pSciBase, param)       \
  if (param) periphBitSet (SCI_SCICR_TIIE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_TIIE, &((pSciBase)->scicr))

#define ioctlSCI_RX_FULL_INT(pSciBase, param)       \
  if (param) periphBitSet (SCI_SCICR_RFIE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_RFIE, &((pSciBase)->scicr))

#define ioctlSCI_RX_ERROR_INT(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR_REIE, &((pSciBase)->scicr)); \
  else periphBitClear (SCI_SCICR_REIE, &((pSciBase)->scicr))

#define ioctlSCI_INT_ENABLE(pSciBase, param)        \
  periphBitSet (((SCI_SCICR_TEIE | SCI_SCICR_TIIE | SCI_SCICR_RFIE | SCI_SCICR_REIE) & (param)), &((pSciBase)->scicr))

#define ioctlSCI_INT_DISABLE(pSciBase, param)       \
  periphBitClear (((SCI_SCICR_TEIE | SCI_SCICR_TIIE | SCI_SCICR_RFIE | SCI_SCICR_REIE) & (param)), &((pSciBase)->scicr))
  
#define ioctlSCI_READ_CONTROL_REG(pSciBase, param)      \
   periphMemRead (&((pSciBase)->scicr))

#define ioctlSCI_WRITE_CONTROL_REG(pSciBase, param)     \
   periphMemWrite (param, &((pSciBase)->scicr))

#define ioctlSCI_WAIT(pSciBase, param)      \
  periphBitSet (SCI_SCICR_RWU, &((pSciBase)->scicr))

#define ioctlSCI_WAKEUP(pSciBase, param)        \
  periphBitClear (SCI_SCICR_RWU, &((pSciBase)->scicr))
            
/* SCI Status Register */

#define ioctlSCI_TEST_STATUS_REG(pSciBase, param)  \
  periphBitTest(param, &((pSciBase)->scisr))

#define ioctlSCI_GET_STATUS_REG(pSciBase, param)  \
  periphMemForcedRead(&((pSciBase)->scisr))

/* write any value */
#define ioctlSCI_CLEAR_STATUS_REG(pSciBase, param) \
    periphMemWrite(0, &((pSciBase)->scisr)) 

#define ioctlSCI_GET_TX_EMPTY(pSciBase, param)  \
  periphBitTest(SCI_SCISR_TDRE, &((pSciBase)->scisr))

#define ioctlSCI_GET_TX_IDLE(pSciBase, param)  \
  periphBitTest(SCI_SCISR_TIDLE, &((pSciBase)->scisr))

#define ioctlSCI_GET_RX_FULL(pSciBase, param)  \
  periphBitTest(SCI_SCISR_RDRF, &((pSciBase)->scisr))

#define ioctlSCI_GET_RX_IDLE(pSciBase, param)  \
  periphBitTest(SCI_SCISR_RIDLE, &((pSciBase)->scisr))

#define ioctlSCI_GET_RX_OVERRUN(pSciBase, param)  \
  periphBitTest(SCI_SCISR_OR, &((pSciBase)->scisr))

#define ioctlSCI_GET_RX_NOISE_ERROR(pSciBase, param)  \
  periphBitTest(SCI_SCISR_NF, &((pSciBase)->StatusReg))

#define ioctlSCI_GET_RX_FRAMING_ERROR(pSciBase, param)  \
  periphBitTest(SCI_SCISR_FE, &((pSciBase)->scisr))
             
#define ioctlSCI_GET_RX_PARITY_ERROR(pSciBase, param)  \
  periphBitTest(SCI_SCISR_PF, &((pSciBase)->scisr))

#define ioctlSCI_GET_RX_ACTIVE(pSciBase, param)  \
  periphBitTest(SCI_SCISR_RAF, &((pSciBase)->scisr))

#if SCI_VERSION >= 2
#define ioctlSCI_GET_LIN_SYNC_ERROR(pSciBase, param)  \
  periphBitTest(SCI_SCISR_LSE, &((pSciBase)->scisr))
#endif


/* SCI Data Register */

#define ioctlSCI_READ_DATA(pSciBase, param)    \
  periphMemForcedRead(&((pSciBase)->scidr))

#define ioctlSCI_WRITE_DATA(pSciBase, param)    \
  periphMemWrite(param, &((pSciBase)->scidr))

/* SCI Control Register 2 */

#if SCI_VERSION >= 2
#define ioctlSCI_LIN_MODE(pSciBase, param)      \
  if (param) periphBitSet (SCI_SCICR2_LIN_MODE, &((pSciBase)->scicr2)); \
  else periphBitClear (SCI_SCICR2_LIN_MODE, &((pSciBase)->scicr2))
#endif

#if SCI_VERSION == 3
#define ioctlSCI_QUEUED_MODE(pSciBase, param)    \
  if (param) periphBitSet (SCI_SCICR2_FIFO_EN, &((pSciBase)->scicr2)); \
  else periphBitClear (SCI_SCICR2_FIFO_EN, &((pSciBase)->scicr2))
  
/* set how many words in TX FIFO causes TXEMPTY condition */  
#define ioctlSCI_SET_TXEMPTY_CONDITION(pSciBase, param)    \
  periphBitGrpSet(SCI_SCICR2_TFWM_MASK, (param) << 11, &((pSciBase)->scicr2))

/* set how many words (plus 1) in RX FIFO causes RXFULL condition */  
#define ioctlSCI_SET_RXFULL_CONDITION(pSciBase, param)    \
  periphBitGrpSet(SCI_SCICR2_RFWM_MASK, (param) << 6, &((pSciBase)->scicr2))

/* returns non-zero if valid data are waiting in receive FIFO */
#define ioctlSCI_CAN_READ_DATA(pSciBase, param)    \
  (periphMemRead(&((pSciBase)->scicr2)) & SCI_SCICR2_RFCNT_MASK)

/* returns non-zero if free space in TX FIFO enables data write */
#define ioctlSCI_CAN_WRITE_DATA(pSciBase, param)    \
  (!(periphMemRead(&((pSciBase)->scicr2)) & SCI_SCICR2_TFCNT_FULL))

#endif /* SCI_VERSION == 3 */


/***********************************************************************
 * End-Of-Life commands
 **********************************************************************/

#define ioctlSCI_SET_BAUDRATE_DIV(pSciBase, param) \
  periphMemWrite(param, &((pSciBase)->scibr))   
            
#define ioctlSCI_LOOP_MODE(pSciBase, param)     \
  periphBitGrpRS(SCI_SCICR_LOOP | SCI_SCICR_RSRC, param, &((pSciBase)->scicr))

#define ioctlSCI_MODULE_IN_WAIT(pSciBase, param)        \
  if (param) periphBitClear (SCI_SCICR_SWAI, &((pSciBase)->scicr)); \
  else periphBitSet (SCI_SCICR_SWAI, &((pSciBase)->scicr))\

#define ioctlSCI_GET_ERROR(pSciBase, param)  \
  periphBitTest((SCI_SCISR_OR | SCI_SCISR_NF | SCI_SCISR_FE | SCI_SCISR_PF), &((pSciBase)->scisr))

#define ioctlSCI_INT_SELECT(pSciBase, param)        \
  periphBitGrpRS (SCI_SCICR_TEIE | SCI_SCICR_TIIE | SCI_SCICR_RFIE | SCI_SCICR_REIE, \
    ((SCI_SCICR_TEIE | SCI_SCICR_TIIE | SCI_SCICR_RFIE | SCI_SCICR_REIE) & (param)), &((pSciBase)->scicr))

/***********************************************************************
 * High level operations
 **********************************************************************/

/* SCI_CLEAR_EXCEPTION */

#define ioctlSCI_CLEAR_EXCEPTION(pSciBase, param)  \
  if ((pSciBase) == __SCI_0) periphBitClear(SCI_STATUS_EXCEPTION_EXIST | SCI_EXCEPTION_BUFFER_OVERFLOW, &sci0_status);  \
  else if ((pSciBase) == __SCI_1) periphBitClear(SCI_STATUS_EXCEPTION_EXIST | SCI_EXCEPTION_BUFFER_OVERFLOW, &sci1_status)

/* SCI_GET_STATUS */

#define ioctlSCI_GET_STATUS(pSciBase, param)  \
  (((pSciBase) == __SCI_0) ? sci0_status : \
  (((pSciBase) == __SCI_1) ? sci1_status : 0))

/***********************************************************************
 * NONBLOCKING operations (implemented also in scibf.c)
 **********************************************************************/

/* SCI_READ_CANCEL */

#define ioctlSCI_READ_CANCEL(pSciBase, param) { \
  if ((pSciBase) == __SCI_0) { \
    periphMemWrite(0, &sci0_RxCounter); /* clear counter */ \
    periphBitClear(SCI_STATUS_READ_INPROGRESS, &sci0_status); /* clear flag */  \
    periphBitClear(SCI_SCICR_RFIE | SCI_SCICR_REIE, &__SCI_0->scicr); /* disable interrupts */  \
  } else if ((pSciBase) == __SCI_1) { \
    periphMemWrite(0, &sci1_RxCounter); /* clear counter */ \
    periphBitClear(SCI_STATUS_READ_INPROGRESS, &sci1_status); /* clear flag */  \
    periphBitClear(SCI_SCICR_RFIE | SCI_SCICR_REIE, &__SCI_1->scicr); /* disable interrupts */  \
  }}
 
/* SCI_WRITE_CANCEL */

#define ioctlSCI_WRITE_CANCEL(pSciBase, param) { \
  if ((pSciBase) == __SCI_0) { \
    periphMemWrite(0, &sci0_TxCounter); /* clear counter */ \
    periphBitClear(SCI_STATUS_WRITE_INPROGRESS, &sci0_status); /* clear flag */ \
    periphBitClear(SCI_TEIE | SCI_TIIE, &__SCI_0->scicr); /* disable interrupts */ \
  } else if((pSciBase) == __SCI_1) { \
    periphMemWrite(0, &sci1_TxCounter); /* clear counter */ \
    periphBitClear(SCI_STATUS_WRITE_INPROGRESS, &sci1_status); /* clear flag */ \
    periphBitClear (SCI_TEIE | SCI_TIIE, &__SCI_1->scicr); /* disable interrupts */ \
  }}


/***********************************************************************
 * BUFFERED operations (implemented also in scibf.c)
 **********************************************************************/

#define ioctlSCI_BUFFERED_RX(pSciBase, param) { \
  if ((pSciBase) == __SCI_0) { \
    if(param) sci0BufferedRxEnable(); \
    else sci0BufferedRxDisable(); \
  } else if ((pSciBase) == __SCI_1) {\
    if(param) sci1BufferedRxEnable(); \
    else sci1BufferedRxDisable(); \
  }}
    
#define ioctlSCI_BUFFERED_TX(pSciBase, param) { \
  if ((pSciBase) == __SCI_0) { \
    if(param) sci0BufferedTxEnable(); \
    else sci0BufferedTxDisable(); \
  } else if ((pSciBase) == __SCI_1) {\
    if(param) sci1BufferedTxEnable(); \
    else sci1BufferedTxDisable(); \
  }}

#define ioctlSCI_GET_RX_CHARS_READY(pSciBase, param)  \
  ((UWord16)((((pSciBase) == __SCI_0) ? sci0BufferedRxGetLen() : \
  (((pSciBase) == __SCI_1) ? sci1BufferedRxGetLen() : 0))))

#define ioctlSCI_GET_RX_BUFFER_FREESPACE(pSciBase, param)  \
  ((UWord16)((((pSciBase) == __SCI_0) ? sci0BufferedRxGetFree() : \
  (((pSciBase) == __SCI_1) ? sci1BufferedRxGetFree() : 0))))
  
#define ioctlSCI_GET_TX_BUFFER_FREESPACE(pSciBase, param)  \
  ((UWord16)((((pSciBase) == __SCI_0) ? sci0BufferedTxGetFree() : \
  (((pSciBase) == __SCI_1) ? sci1BufferedTxGetFree() : 0))))

inline void ioctlSCI_SEND_XON(arch_sSCI *pSciBase, void*)
{
    if (pSciBase == __SCI_0) 
    {
        if(ioctl(__SCI_0, SCI_GET_TX_EMPTY, NULL)) /* send directly */ 
            ioctl(__SCI_0, SCI_WRITE_DATA, SCI_0_XONCHAR); 
        else { /* remember to send in in next TX interrupt */ 
            periphBitSet(SCI_STATUS_XON_PENDING, &sci0_status);
            ioctl(__SCI_0, SCI_INT_ENABLE, SCI_TX_EMPTY); }
    } 
    else if (pSciBase == __SCI_1) 
    { 
        if(ioctl(__SCI_1, SCI_GET_TX_EMPTY, NULL)) /* send directly */ 
            ioctl(__SCI_1, SCI_WRITE_DATA, SCI_1_XONCHAR); 
        else { /* remember to send in in next TX interrupt */ 
            periphBitSet(SCI_STATUS_XON_PENDING, &sci1_status);
            ioctl(__SCI_1, SCI_INT_ENABLE, SCI_TX_EMPTY); }
    }
}

inline void ioctlSCI_SEND_XOFF(arch_sSCI *pSciBase, void*)
{
    if (pSciBase == __SCI_0) 
    {
        if(ioctl(__SCI_0, SCI_GET_TX_EMPTY, NULL)) /* send directly */ 
            ioctl(__SCI_0, SCI_WRITE_DATA, SCI_0_XOFFCHAR); 
        else { /* remember to send in in next TX interrupt */ 
            periphBitSet(SCI_STATUS_XOFF_PENDING, &sci0_status);
            ioctl(__SCI_0, SCI_INT_ENABLE, SCI_TX_EMPTY); }
    } 
    else if (pSciBase == __SCI_1) 
    { 
        if(ioctl(__SCI_1, SCI_GET_TX_EMPTY, NULL)) /* send directly */ 
            ioctl(__SCI_1, SCI_WRITE_DATA, SCI_1_XOFFCHAR); 
        else { /* remember to send in in next TX interrupt */ 
            periphBitSet(SCI_STATUS_XOFF_PENDING, &sci1_status);
            ioctl(__SCI_1, SCI_INT_ENABLE, SCI_TX_EMPTY); }
    }
}

/***********************************************************************
* SCI BLOCKING/NON_BLOCKING prototypes (implemented in scibl.c)
***********************************************************************/

void read_SCI_0_NON_BLOCKING(SCI0CHAR *data, UWord16 size);
void read_SCI_0_BLOCKING(SCI0CHAR *data, UWord16 size);

void write_SCI_0_NON_BLOCKING(const SCI0CHAR *data, UWord16 size);
void write_SCI_0_BLOCKING(const SCI0CHAR *data, UWord16 size);

void read_SCI_1_NON_BLOCKING(SCI1CHAR *data, UWord16 size);
void read_SCI_1_BLOCKING(SCI1CHAR *data, UWord16 size);

void write_SCI_1_NON_BLOCKING(const SCI1CHAR *data, UWord16 size);
void write_SCI_1_BLOCKING(const SCI1CHAR *data, UWord16 size);

/***********************************************************************
* BUFFERED SCI prototypes (implemented in scibf.c)
***********************************************************************/

Word16 read_SCI_0_BUFFERED(SCI0CHAR *data, UWord16 size);
Word16 read_SCI_1_BUFFERED(SCI1CHAR *data, UWord16 size);

Word16 write_SCI_0_BUFFERED(const SCI0CHAR *data, UWord16 size);
Word16 write_SCI_1_BUFFERED(const SCI1CHAR *data, UWord16 size);

void sci0BufferedRxEnable(void);
void sci0BufferedRxDisable(void);
void sci0BufferedTxEnable(void);
void sci0BufferedTxDisable(void);
Word16 sci0BufferedRxGetLen(void);
Word16 sci0BufferedRxGetFree(void);
Word16 sci0BufferedTxGetFree(void);

void sci1BufferedRxEnable(void);
void sci1BufferedRxDisable(void);
void sci1BufferedTxEnable(void);
void sci1BufferedTxDisable(void);
Word16 sci1BufferedRxGetLen(void);
Word16 sci1BufferedRxGetFree(void);
Word16 sci1BufferedTxGetFree(void);

/***********************************************************************
* SCI is a module name alias to SCI_0
***********************************************************************/

#ifdef SCI
    #define read_SCI_BUFFERED  read_SCI_0_BUFFERED
    #define write_SCI_BUFFERED write_SCI_0_BUFFERED

    #define read_SCI_NON_BLOCKING  read_SCI_0_NON_BLOCKING
    #define read_SCI_BLOCKING      read_SCI_0_BLOCKING
    #define write_SCI_NON_BLOCKING write_SCI_0_NON_BLOCKING
    #define write_SCI_BLOCKING     write_SCI_0_BLOCKING
#endif

/***********************************************************************
* common SCI prototypes (implemented (different way) in both scibl.c and scibf.c)
***********************************************************************/

void Sci0RxFullISR(void);
void Sci0TxEmptyISR(void);
void Sci0RxErrorISR(void);
void Sci0RxFullErrISR(void);

void Sci1RxFullISR(void);
void Sci1TxEmptyISR(void);
void Sci1RxErrorISR(void);

/***********************************************************************
* hook prototypes - we define prototypes ourselves - to assure proper 
*                   return and argument types
***********************************************************************/

#ifdef SCI_0_RX_CHAR_HOOK
UWord16 SCI_0_RX_CHAR_HOOK(UWord16);
#endif
#ifdef SCI_0_RX_FINISHED_HOOK
void SCI_0_RX_FINISHED_HOOK(void);
#endif
#ifdef SCI_0_RX_ERROR_HOOK
void SCI_0_RX_ERROR_HOOK(void);
#endif
#ifdef SCI_0_TX_CHAR_HOOK
UWord16 SCI_0_TX_CHAR_HOOK(UWord16);
#endif
#ifdef SCI_0_TX_FINISHED_HOOK
void SCI_0_TX_FINISHED_HOOK(void);
#endif
/* hook for BUFFERED operations */
#ifdef SCI_0_RX_LOWBUFFER_HOOK
void SCI_0_RX_LOWBUFFER_HOOK(bool bIsFull);
#endif

#ifdef SCI_1_RX_CHAR_HOOK
UWord16 SCI_1_RX_CHAR_HOOK(UWord16);
#endif
#ifdef SCI_1_RX_FINISHED_HOOK
void SCI_1_RX_FINISHED_HOOK(void);
#endif
#ifdef SCI_1_RX_ERROR_HOOK
void SCI_1_RX_ERROR_HOOK(void);
#endif
#ifdef SCI_1_TX_CHAR_HOOK
UWord16 SCI_1_TX_CHAR_HOOK(UWord16);
#endif
#ifdef SCI_1_TX_FINISHED_HOOK
void SCI_1_TX_FINISHED_HOOK(void);
#endif
/* hook for BUFFERED operations */
#ifdef SCI_1_RX_LOWBUFFER_HOOK
void SCI_1_RX_LOWBUFFER_HOOK(bool bIsFull);
#endif


#ifdef __cplusplus
}
#endif

#endif

