/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  spi.h
*
* $Date:      Mar-30-2009$
*
* $Version:   2.3.32.0$
*
* Description: Header file for the SPI driver.
*
* This file supports different hardware versions of the module. A version
* of module used in your project is defined in the "arch.h" processor 
* architecture definition file.
*
*  SPI_VERSION_1 .. 56F83xx and 56F801x devices, see MC56F8300UM.pdf, MC56F8000RM.pdf
*  SPI_VERSION_2 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*  SPI_VERSION_3 .. 56F800x devices, see MC56F800xRM.pdf
*
*******************************************************************************/

#ifndef __SPI_H
#define __SPI_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before spi.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************
* SPI module identifiers, correspond to module base address
*************************************************************/

#ifdef SPI0_BASE
#define SPI_0 (&ArchIO.Spi0)
#endif

#ifdef SPI1_BASE
#define SPI_1 (&ArchIO.Spi1)
#endif

/* single ("anonymous") module on some devices */
#ifdef SPI_BASE
#define SPI     (&ArchIO.Spi)
#define SPI_0   (&ArchIO.Spi) /* aliased to SPI_0 */
#endif

/*************************************************************
* arch.h should define device-specific information about SPI
**************************************************************/

#if !defined(SPI_VERSION)
#error SPI not properly described in arch.h (old Quick_Start version?)
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Serial Peripheral Interface (SPI) module allows full-duplex, synchronous,
* serial communication between the MC and peripheral devices, including other MCs.
* Software can poll SPI status flags, or SPI operation can be interrupt
* driven. This block contains four 16-bit memory mapped registers for control
* parameters, status, and data transfer.
* 
* Features of the SPI module include:
*   • Full-duplex operation
*   • Master and slave modes
*   • Double-buffered operation with separate transmit and receive registers
*   • Programmable length transmissions (2 to 16 bits)
*   • Programmable transmit and receive shift order (MSB first or last bit transmitted)
*   • Eight master mode frequencies (maximum = bus frequency ÷ 2)
*   • Maximum slave mode frequency = bus frequency ÷ 2
*   • Clock ground for reduced Radio Frequency (RF) interference
*   • Serial clock with programmable polarity and phase
*   • Two separately enabled interrupts
*      — SPI Receiver Full (SPRF)
*      — SPI Transmitter Empty (SPTE)
*   • Mode fault error flag interrupt capability
*   • Wired OR mode functionality enabling connection to multiple SPIs
*
* For more information, please refer to the user manual for the particular
* chip that you are using, such as the MC56F8300 Peripheral Manual,
* for a description of the SPI device.
*
* The SPI device driver interface uses "ioctl" call to control specific
* SPI functions during operation. For details see "ioctl" call.
*
******************************************************************************/

/******************************************************************************
* type of SPI characters and buffers (can be defined as "char" in appconfig.h) 
******************************************************************************/

#ifndef SPI0CHAR
#define SPI0CHAR UWord16    /* HawkV1 compatible 16bit characters by default */
#endif

#ifndef SPI1CHAR
#define SPI1CHAR UWord16    /* HawkV1 compatible 16bit characters by default */
#endif

/****************************************************
* Configurable items, i.e. defines, for appconfig.h
****************************************************

    #define INT_VECTOR_ADDR_yy isr_routine      // specify interrupt handler routine
    #define INT_PRIORITY_LEVEL_yy INTC_LEVEL1   // interrupt level : (INTC_DISABLED, INTC_LEVEL0,...INTC_LEVEL2)
  
    #define SPI_0_SPSCR_INIT  0         // SPI0 Status Control Reg (SPSCR)
    #define SPI_0_SPDSCR_INIT 0x000F    // SPI0 Data Size Reg (SPDSR) num=(num_bits-1) 

    dtto for SPI_1
 
  where:
         yy  is interrupt vector number
         
            e.g. on 56F8346:
                40 - SPI 0 Receiver Full
                41 - SPI 0 Transmitter Empty
                
                38 - SPI 1 Receiver Full
                39 - SPI 1 Transmitter Empty
                
                
  To enable NON_BLOCKING SPI_0 read & write functions, do:
  
    #define INT_VECTOR_ADDR_40 Spi0RxFullISR
    #define INT_VECTOR_ADDR_41 Spi0TxEmptyISR
    #define INT_PRIORITY_LEVEL_40 INTC_LEVEL1
    #define INT_PRIORITY_LEVEL_41 INTC_LEVEL1

  To install read & write hooks, define
  
    #define SPI_0_ERROR_HOOK         rx_error_hook      // all operations
    #define SPI_0_RX_CHAR_HOOK       rx_char_hook       // all operations
    #define SPI_0_TX_CHAR_HOOK       tx_char_hook       // all operations
    #define SPI_0_RX_FINISHED_HOOK   rx_finished_hook   // NON_BLOCKING operation only 
    #define SPI_0_TX_FINISHED_HOOK   tx_finished_hook   // NON_BLOCKING operation only 

  where:
  
    UWord16 rx_char_hook(UWord16 rxchar)  // is called for each character received (both bl/nobl), 
                                          // return nonzero to discard received character
                                          // return zero to accept received character
                                          // you can use SPI_READ_CANCEL command to abort operation
                                          
    void rx_finished_hook(void)           // called when non-blocking read finishes
    
    void error_hook(void)                 // called when error occures during read (both bl/nonbl)
                                          // read SPI_x->spisr to get status register
    
    UWord16 tx_char_hook(UWord16 txchar)  // called after each character transmitted (both bl/nonbl)
                                          // return nonzero to not to transmit next buffered character 
                                                (you have to write SPIDR yourself using SPI_WRITE_DATA)
                                          // return zero to continue with transmission
                                          // you can use SPI_WRITE_CANCEL command to abort operation
                                          
    void tx_finished_hook(void)           // called when non-blocking write finishes


  In any hook function, you can issue new (NON_BLOCKING) read or write operation. 
 
 */


/***************************************************
* SPI Ioctl commands
****************************************************/
/* command                    |        Param       */

/* SPI status and control register commands */
#define SPI_INIT                /* NULL */
#define SPI_DEVICE              /* SPI_ENABLE / SPI_DISABLE */
#define SPI_SET_MODE            /* SPI_MASTER(1) / SPI_SLAVE(0) */
#define SPI_SET_ORDER           /* SPI_LSB_FIRST(1) / SPI_MSB_FIRST(0) - DSO bit*/
#define SPI_SET_CLOCK_POLARITY  /* SPI_RISING_EDGE(1) / SPI_FALLING_EDGE(0) - CPOL bit */
#define SPI_SET_CLOCK_PHASE     /* SPI_SCLK_EDGE(1) / SPI_SS_EDGE - CPHA bit (which edge starts slave transmission) */
#define SPI_SET_MODE_FAULT      /* SPI_ENABLE / SPI_DISABLE - MODFEN bit (ena/dis mode fault) */
#define SPI_SET_BAUD_DIV        /* SPI_DIVx(2/4/8/16/32/64/128/256), sets baudrate divider 
                                on MC56F800x (2/4/8/16/32/64/128/256/512/1024/2048/4096)*/

/* interrrupts enable disable */
#define SPI_RX_FULL_INT         /* SPI_ENABLE / SPI_DISABLE - receive interrupt */
#define SPI_TX_EMPTY_INT        /* SPI_ENABLE / SPI_DISABLE - transmit interrupt */
#define SPI_ERROR_INT           /* SPI_ENABLE / SPI_DISABLE - error (overflow/mode fault) interrupt */
#define SPI_INT_ENABLE          /* SPI_TX_EMPTY | SPI_RX_FULL | SPI_ERROR */
#define SPI_INT_DISABLE         /* SPI_TX_EMPTY | SPI_RX_FULL | SPI_ERROR */

/* SPI data and control register commands */
#define SPI_SET_TX_DATA_SIZE    /* data size (2..16) - writes data_size-1 to SPDSCR) */
#define SPI_SET_WIRED_OR_MODE   /* SPI_NORMAL / SPI_OPEN_DRAIN */

/* data registers */
#define SPI_WRITE_DATA          /* UWord16: transmit data 2-16bits */
#define SPI_READ_DATA           /* NULL */

/* test SPI status bits - can be used directly in condition */
/* if it is used in assignement then it returns bit value in original bit position */
#define SPI_GET_TX_EMPTY        /* NULL, test SPTE bit */
#define SPI_GET_RX_FULL         /* NULL, test SPRF bit */
#define SPI_GET_RX_OVERFLOW     /* NULL, test OVRF bit */
#define SPI_GET_MODE_FAULT      /* NULL, test MODF bit */

#define SPI_READ_CONTROL_REG    /* NULL */
#define SPI_WRITE_CONTROL_REG   /* UWord16 */

#define SPI_GET_ERROR           /* NULL */
#define SPI_CLEAR_MODE_FAULT    /* NULL */

/* commands for high-level operations (BLOCKING/NON_BLOCKING read, write) */
#define SPI_CLEAR_EXCEPTION     /* NULL */
#define SPI_GET_STATUS          /* NULL */
#define SPI_WRITE_CANCEL        /* NULL */
#define SPI_READ_CANCEL         /* NULL */

/****************************************************************************
* SPI Version 2 commands (802x3x)
*****************************************************************************/

#if SPI_VERSION >= 2
#define SPI_MULT_BAUD_DIV       /* SPI_MULT_DIV_1x / SPI_MULT_DIV_2x, multiply divisor value */
#define SPI_TEST_SS_INPUT       /* NULL, return immediate state of SS input pin */
#define SPI_SET_SS_MODE         /* one of SPI_SS_xxx (the two SPI_SS_AUTO_xxx may be combined) */ 
#define SPI_SET_SS_OUTPUT       /* boolean, sets SS pin value in SPI_SS_MANUAL_OUT mode */ 
#define SPI_SET_SS_WIRED_OR_MODE /* SPI_OPEN_DRAIN/SPI_NORMAL, set SS pin mode */ 
#define SPI_OVERRIDE_SS_INPUT   /* SPI_ENABLE / SPI_DISABLE, override internal SS input with value of SPMSTR bit */ 
#endif /* SPI_VERSION >= 2 */

#if SPI_VERSION == 2
#define SPI_WRITE_DATA_DELAY    /* UWord16 (0..0x1fff), sets inter-word delay in IPbus clocks */

#define SPI_QUEUED_MODE          /* SPI_ENABLE / SPI_DISABLE, enable SPI FIFOs */
#define SPI_SET_TXEMPTY_CONDITION /* SPI_TXEMPTY_WHEN_xxx, or value 0..3 how many words in TX FIFO causes TXEMPTY condition */
#define SPI_SET_RXFULL_CONDITION  /* SPI_RXFULL_WHEN_xxx, or value 0..3 how many words (plus 1) in RX FIFO causes RXFULL condition */
#define SPI_CAN_READ_DATA       /* NULL, returns non-zero if valid data are waiting in receive FIFO */
#define SPI_CAN_WRITE_DATA      /* NULL, returns non-zero if free space in TX FIFO enables data write */
#endif /* SPI_VERSION == 2 */


/****************************************************************************
* read/write modes of operation
*****************************************************************************/

#define BLOCKING      /* blocking mode for read/write functions */
#define NON_BLOCKING  /* non-blocking mode for read/write functions */

/****************************************************************************
* SPI constants and type declarations used in the ioctl functions
*****************************************************************************/

#define SPI_ENABLE        1
#define SPI_DISABLE       0

#define SPI_MASTER        1
#define SPI_SLAVE         0

#define SPI_MSB_FIRST     0
#define SPI_LSB_FIRST     1

#define SPI_RISING_EDGE   1
#define SPI_FALLING_EDGE  0

#define SPI_SCLK_EDGE     1
#define SPI_SS_EDGE       0

#define SPI_OPEN_DRAIN    1
#define SPI_NORMAL        0

/* SPI_SET_BAUD_DIV */
#define SPI_DIV2        SPI_SPSCR_SPR_DIV2  
#define SPI_DIV4        SPI_SPSCR_SPR_DIV4  
#define SPI_DIV8        SPI_SPSCR_SPR_DIV8  
#define SPI_DIV16       SPI_SPSCR_SPR_DIV16 
#define SPI_DIV32       SPI_SPSCR_SPR_DIV32 
#define SPI_DIV64       SPI_SPSCR_SPR_DIV64 
#define SPI_DIV128      SPI_SPSCR_SPR_DIV128
#define SPI_DIV256      SPI_SPSCR_SPR_DIV256
#if SPI_VERSION >= 3
#define SPI_DIV512      (SPI_SPSCR_SPR_DIV2 | SPI_SPDSCR_SPR3)   
#define SPI_DIV1024     (SPI_SPSCR_SPR_DIV4 | SPI_SPDSCR_SPR3)
#define SPI_DIV2048     (SPI_SPSCR_SPR_DIV8  | SPI_SPDSCR_SPR3)
#define SPI_DIV4096     (SPI_SPSCR_SPR_DIV16  | SPI_SPDSCR_SPR3)
#endif


/* interrupts */
#define SPI_TX_EMPTY    SPI_SPSCR_SPTIE
#define SPI_RX_FULL     SPI_SPSCR_SPRIE
#define SPI_ERROR       SPI_SPSCR_ERRIE

#if SPI_VERSION >= 2

/* divisor multiplcation factor */
#define SPI_MULT_DIV_1x 0
#define SPI_MULT_DIV_2x 1

/* TXEMPTY condition */
#define SPI_TXEMPTY_WHEN_FIFO_EMPTY        0
#define SPI_TXEMPTY_WHEN_1_OR_LESS_IN_FIFO 1
#define SPI_TXEMPTY_WHEN_2_OR_LESS_IN_FIFO 2
#define SPI_TXEMPTY_WHEN_3_OR_LESS_IN_FIFO 3

/* RXFULL condition */
#define SPI_RXFULL_WHEN_1_OR_MORE_IN_FIFO  0
#define SPI_RXFULL_WHEN_2_OR_MORE_IN_FIFO  1
#define SPI_RXFULL_WHEN_3_OR_MORE_IN_FIFO  2
#define SPI_RXFULL_WHEN_4_OR_MORE_IN_FIFO  3

/* SS mode */
#define SPI_SS_INPUT            0
#define SPI_SS_MANUAL_OUT       SPI_SPDSCR_SS_DDR
#define SPI_SS_AUTO_ENVELOPE    (SPI_SPDSCR_SS_DDR | SPI_SPDSCR_SS_AUTO)
#define SPI_SS_AUTO_STROBE      (SPI_SPDSCR_SS_DDR | SPI_SPDSCR_SS_STRB)

/* SS manual out value */
#define SPI_HIGH 1
#define SPI_LOW  0

#endif /* SPI_VERSION >= 2 */

/* status generated by read/write functions -> check by SPI0_GET_STATUS command */

#define SPI_STATUS_WRITE_INPROGRESS     0x0001    /* write to SPI is in progress */
#define SPI_STATUS_READ_INPROGRESS      0x0002    /* read from SPI is in progress */
#define SPI_STATUS_EXCEPTION_EXIST      0x0010    /* exception exists - HW exception if only this flag is set
                                                           - SW exception if other exception flags are set */
#define SPI_EXCEPTION_BUFFER_OVERFLOW   0x0020    /* buffer overflow - some bytes were thrown away */
/* exception codes */
#define SPI_EXCEPTION_OVERRUN           0x0040
#define SPI_EXCEPTION_MODE_FAULT        0x0080

/*****************************************************************
* SPI Register Bits Defines, used in ioctl command implementation
******************************************************************/

/* SPI Status and Control Register (SPSCR) */
#define SPI_SPSCR_SPR_MASK      0xe000
#define SPI_SPSCR_SPR_DIV2      0x0000
#define SPI_SPSCR_SPR_DIV4      0x2000
#define SPI_SPSCR_SPR_DIV8      0x4000
#define SPI_SPSCR_SPR_DIV16     0x6000
#define SPI_SPSCR_SPR_DIV32     0x8000
#define SPI_SPSCR_SPR_DIV64     0xa000
#define SPI_SPSCR_SPR_DIV128    0xc000
#define SPI_SPSCR_SPR_DIV256    0xe000
#define SPI_SPSCR_DSO           0x1000
#define SPI_SPSCR_ERRIE         0x0800
#define SPI_SPSCR_MODFEN        0x0400
#define SPI_SPSCR_SPRIE         0x0200
#define SPI_SPSCR_SPMSTR        0x0100
#define SPI_SPSCR_CPOL          0x0080
#define SPI_SPSCR_CPHA          0x0040
#define SPI_SPSCR_SPE           0x0020
#define SPI_SPSCR_SPTIE         0x0010
#define SPI_SPSCR_SPRF          0x0008
#define SPI_SPSCR_OVRF          0x0004
#define SPI_SPSCR_MODF          0x0002
#define SPI_SPSCR_SPTE          0x0001

/* SPI DataSize and Control Register (SPDSCR) */
#define SPI_SPDSCR_WOM          0x8000
#define SPI_SPDSCR_TDMAEN       0x4000
#define SPI_SPDSCR_RDMAEN       0x2000
#define SPI_SPDSCR_DS_MASK      0x000f
#define SPI_SPDSCR_DS2          0x0001
#define SPI_SPDSCR_DS3          0x0002
#define SPI_SPDSCR_DS4          0x0003
#define SPI_SPDSCR_DS5          0x0004
#define SPI_SPDSCR_DS6          0x0005
#define SPI_SPDSCR_DS7          0x0006
#define SPI_SPDSCR_DS8          0x0007
#define SPI_SPDSCR_DS9          0x0008
#define SPI_SPDSCR_DS10         0x0009
#define SPI_SPDSCR_DS11         0x000a
#define SPI_SPDSCR_DS12         0x000b
#define SPI_SPDSCR_DS13         0x000c
#define SPI_SPDSCR_DS14         0x000d
#define SPI_SPDSCR_DS15         0x000e
#define SPI_SPDSCR_DS16         0x000f

#if SPI_VERSION >= 2
#define SPI_SPDSCR_BD2x         0x1000
#define SPI_SPDSCR_SS_IN        0x0800
#define SPI_SPDSCR_SS_DATA      0x0400
#define SPI_SPDSCR_SS_ODM       0x0200
#define SPI_SPDSCR_SS_AUTO      0x0100
#define SPI_SPDSCR_SS_DDR       0x0080
#define SPI_SPDSCR_SS_STRB      0x0040
#define SPI_SPDSCR_SS_OVER      0x0020
#endif

#if SPI_VERSION >= 3
#define SPI_SPDSCR_SPR3         0x0010
#endif


/* FIFO control register */
#if SPI_VERSION >= 2
#define SPI_FIFO_TFCNT_MASK     0x7000
#define SPI_FIFO_TFCNT_FULL     0x4000
#define SPI_FIFO_RFCNT_MASK     0x0700
#define SPI_FIFO_RFCNT_FULL     0x0400
#define SPI_FIFO_TFWM_MASK      0x0060
#define SPI_FIFO_RFWM_MASK      0x000c
#define SPI_FIFO_FIFO_ENA       0x0001
#endif

/* Delay Register */
#if SPI_VERSION >= 2
#define SPI_DELAY_WAIT_MASK     0x1fff
#endif

/*******************************************************************************
    Bit names of older SDK version, maintained here for backward compatibility.
*******************************************************************************/

/* Do not use for new development ! */
#define SPI_SPE     SPI_SPSCR_SPE
#define SPI_SPTIE   SPI_SPSCR_SPTIE
#define SPI_CPHA    SPI_SPSCR_CPHA
#define SPI_CPOL    SPI_SPSCR_CPOL
#define SPI_SPMSTR  SPI_SPSCR_SPMSTR
#define SPI_SPRIE   SPI_SPSCR_SPRIE
#define SPI_MODFEN  SPI_SPSCR_MODFEN
#define SPI_ERRIE   SPI_SPSCR_ERRIE
#define SPI_DSO     SPI_SPSCR_DSO
#define SPI_SPTE    SPI_SPSCR_SPTE
#define SPI_MODF    SPI_SPSCR_MODF
#define SPI_OVRF    SPI_SPSCR_OVRF
#define SPI_SPRF    SPI_SPSCR_SPRF


/****************************************************************************
* SPI function prototypes
*****************************************************************************/

void spiInit(arch_sSPI *pSpiBase);

void Spi0TxEmptyISR(void);
void Spi0RxFullISR(void);
void write_SPI_0_NON_BLOCKING(const SPI0CHAR *buf, UWord16 size);
void read_SPI_0_NON_BLOCKING(SPI0CHAR *buf, UWord16 size);
void write_SPI_0_BLOCKING(const SPI0CHAR *buf, UWord16 size);
void read_SPI_0_BLOCKING(SPI0CHAR *buf, UWord16 size);

void Spi1TxEmptyISR(void);
void Spi1RxFullISR(void);
void write_SPI_1_NON_BLOCKING(const SPI1CHAR *buf, UWord16 size);
void read_SPI_1_NON_BLOCKING(SPI1CHAR *buf, UWord16 size);
void write_SPI_1_BLOCKING(const SPI1CHAR *buf, UWord16 size);
void read_SPI_1_BLOCKING(SPI1CHAR *buf, UWord16 size);

/***********************************************************************
* hook prototypes - we define prototypes ourselves - to assure proper 
*                   return and argument types
***********************************************************************/

#ifdef SPI_0_RX_CHAR_HOOK
UWord16 SPI_0_RX_CHAR_HOOK(UWord16);
#endif
#ifdef SPI_0_RX_FINISHED_HOOK
void SPI_0_RX_FINISHED_HOOK(void);
#endif
#ifdef SPI_0_ERROR_HOOK
void SPI_0_ERROR_HOOK(void);
#endif
#ifdef SPI_0_TX_CHAR_HOOK
UWord16 SPI_0_TX_CHAR_HOOK(UWord16);
#endif
#ifdef SPI_0_TX_FINISHED_HOOK
void SPI_0_TX_FINISHED_HOOK(void);
#endif

#ifdef SPI_1_RX_CHAR_HOOK
UWord16 SPI_1_RX_CHAR_HOOK(UWord16);
#endif
#ifdef SPI_1_RX_FINISHED_HOOK
void SPI_1_RX_FINISHED_HOOK(void);
#endif
#ifdef SPI_1_ERROR_HOOK
void SPI_1_ERROR_HOOK(void);
#endif
#ifdef SPI_1_TX_CHAR_HOOK
UWord16 SPI_1_TX_CHAR_HOOK(UWord16);
#endif
#ifdef SPI_1_TX_FINISHED_HOOK
void SPI_1_TX_FINISHED_HOOK(void);
#endif

/***********************************************************************
* SPI is a module name alias to SPI_0 (on some devices)
***********************************************************************/

#ifdef SPI
    #define read_SPI_NON_BLOCKING  read_SPI_0_NON_BLOCKING
    #define read_SPI_BLOCKING      read_SPI_0_BLOCKING
    #define write_SPI_NON_BLOCKING write_SPI_0_NON_BLOCKING
    #define write_SPI_BLOCKING     write_SPI_0_BLOCKING
#endif

/***********************************************************************
* status variables for read/wrire functions
***********************************************************************/

extern volatile UWord16 spi0_status;
extern volatile UWord16 spi0_RxCounter;
extern volatile UWord16 spi0_TxCounter;

extern volatile UWord16 spi1_status;
extern volatile UWord16 spi1_RxCounter;
extern volatile UWord16 spi1_TxCounter;

/***********************************************************************
* ioctl implementation
***********************************************************************/

/* module names for internal use in ioctl implementation */

#define __SPI_0 SPI_0

#ifdef SPI_1
#define __SPI_1 SPI_1
#else
#define __SPI_1 ((arch_sSPI*)NULL)
#endif
 
/***********************************************************************
* SPI init
***********************************************************************/

#define ioctlSPI_INIT(pSpiBase, param) spiInit(pSpiBase)

/***********************************************************************
* SPI control command macros
***********************************************************************/

/* SPI peripheral enable/disable */
#define ioctlSPI_DEVICE(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_SPE, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_SPE, &((pSpiBase)->spscr))

/* SPI MASTER/SLAVE mode set */
#define ioctlSPI_SET_MODE(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_SPMSTR, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_SPMSTR, &((pSpiBase)->spscr))

/* SPI data shift order set */
#define ioctlSPI_SET_ORDER(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_DSO, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_DSO, &((pSpiBase)->spscr))
 
/* SPI clock polarity set */
#define ioctlSPI_SET_CLOCK_POLARITY(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_CPOL, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_CPOL, &((pSpiBase)->spscr))

/* SPI clock phase set */
#define ioctlSPI_SET_CLOCK_PHASE(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_CPHA, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_CPHA, &((pSpiBase)->spscr))

/* SPI mode fault detect set */
#define ioctlSPI_SET_MODE_FAULT(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_MODFEN, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_MODFEN, &((pSpiBase)->spscr))

/* SPI receive interrupt enable/disable */
#define ioctlSPI_RX_FULL_INT(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_SPRIE, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_SPRIE, &((pSpiBase)->spscr))

/* SPI transmit interrupt enable/disable */
#define ioctlSPI_TX_EMPTY_INT(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_SPTIE, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_SPTIE, &((pSpiBase)->spscr))

/* SPI transmit interrupt enable/disable */
#define ioctlSPI_ERROR_INT(pSpiBase, param) \
  if (param) periphBitSet(SPI_SPSCR_ERRIE, &((pSpiBase)->spscr)); \
  else periphBitClear(SPI_SPSCR_ERRIE, &((pSpiBase)->spscr))

#define ioctlSPI_INT_ENABLE(pSpiBase, param)        \
  periphBitSet (param, &((pSpiBase)->spscr))

#define ioctlSPI_INT_DISABLE(pSpiBase, param)       \
  periphBitClear (param, &((pSpiBase)->spscr))
  
/* set SPI baud divisor */
#if SPI_VERSION <= 2
#define ioctlSPI_SET_BAUD_DIV(pSpiBase, param) \
  periphBitGrpRS(SPI_SPSCR_SPR_MASK, param, &((pSpiBase)->spscr))
#else /* SPI_VERSION >= 3 */
 #define ioctlSPI_SET_BAUD_DIV(pSpiBase, param) \
  {periphBitGrpRS(SPI_SPSCR_SPR_MASK, param, &((pSpiBase)->spscr)); \
  periphBitGrpRS(SPI_SPDSCR_SPR3, param, &((pSpiBase)->spdsr));}
#endif /* SPI_VERSION >= 3 */

/* set data size */
#define ioctlSPI_SET_TX_DATA_SIZE(pSpiBase, param) \
  periphBitGrpSR(SPI_SPDSCR_DS_MASK, (param)-1, &((pSpiBase)->spdsr))
  
/* set wired-or mode */
#define ioctlSPI_SET_WIRED_OR_MODE(pSpiBase, param) \
  { if (param) periphBitSet(SPI_SPDSCR_WOM, &((pSpiBase)->spdsr)); \
    else periphBitClear(SPI_SPDSCR_WOM, &((pSpiBase)->spdsr)); }

/* read SPI cpntrol register */
#define ioctlSPI_READ_CONTROL_REG(pSpiBase, param) \
  periphMemRead(&((pSpiBase)->spscr))

/* write SPI cpntrol register */
#define ioctlSPI_WRITE_CONTROL_REG(pSpiBase, param) \
  periphMemWrite(param, &((pSpiBase)->spscr))

/* write SPI Tx register */
#define ioctlSPI_WRITE_DATA(pSpiBase, param) \
  periphMemWrite(param, &((pSpiBase)->spdtr))
  
/* reads SPI Rx register */
#define ioctlSPI_READ_DATA(pSpiBase, param) \
  periphMemForcedRead(&((pSpiBase)->spdrr))

/* test SPI Tx reg. empty bit */
#define ioctlSPI_GET_TX_EMPTY(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_SPTE, &((pSpiBase)->spscr))

/* test SPI Rx reg. full bit */
#define ioctlSPI_GET_RX_FULL(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_SPRF, &((pSpiBase)->spscr))

/* test SPI overflow bit */
#define ioctlSPI_GET_RX_OVERFLOW(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_OVRF, &((pSpiBase)->spscr))
  
/* test SPI mode fault occurence bit */
#define ioctlSPI_GET_MODE_FAULT(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_MODF, &((pSpiBase)->spscr))

/* test SPI two error bits */
#define ioctlSPI_GET_ERROR(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_MODF | SPI_SPSCR_OVRF, &((pSpiBase)->spscr))

/* clear SPI mode fault occurence bit - cleared by writing "1" to MODF */
/* note: it is the only clear-by-write-one bit in SPSCR, we don't need to use periphSafeAckByOne() */
#define ioctlSPI_CLEAR_MODE_FAULT(pSpiBase, param) \
  periphBitSet(SPI_SPSCR_MODF, &((pSpiBase)->spscr))

#if SPI_VERSION >= 2
/* multiply divisor value 2x */
#define ioctlSPI_MULT_BAUD_DIV(pSpiBase, param)    \
  if (param) periphBitSet(SPI_SPDSCR_BD2x, &((pSpiBase)->spdsr)); \
  else periphBitClear(SPI_SPDSCR_BD2x, &((pSpiBase)->spdsr))

/* return immediate state of SS input pin */
#define ioctlSPI_TEST_SS_INPUT(pSpiBase, param)    \
  periphBitTest(SPI_SPDSCR_SS_IN, &((pSpiBase)->spdsr))

/* set SS pin function */ 
#define ioctlSPI_SET_SS_MODE(pSpiBase, param)    \
  periphBitGrpSet(SPI_SPDSCR_SS_AUTO | SPI_SPDSCR_SS_DDR | SPI_SPDSCR_SS_STRB, param, &((pSpiBase)->spdsr))

/* sets SS pin value in SPI_SS_MANUAL_OUT mode */ 
#define ioctlSPI_SET_SS_OUTPUT(pSpiBase, param)    \
  if (param) periphBitSet(SPI_SPDSCR_SS_DATA, &((pSpiBase)->spdsr)); \
  else periphBitClear(SPI_SPDSCR_SS_DATA, &((pSpiBase)->spdsr))

/* set SS pin mode */ 
#define ioctlSPI_SET_SS_WIRED_OR_MODE(pSpiBase, param)    \
  if (param) periphBitSet(SPI_SPDSCR_SS_ODM, &((pSpiBase)->spdsr)); \
  else periphBitClear(SPI_SPDSCR_SS_ODM, &((pSpiBase)->spdsr))

/* override internal SS input*/
#define ioctlSPI_OVERRIDE_SS_INPUT(pSpiBase, param)    \
  if (param) periphBitSet(SPI_SPDSCR_SS_OVER, &((pSpiBase)->spdsr)); \
  else periphBitClear(SPI_SPDSCR_SS_OVER, &((pSpiBase)->spdsr))
#endif /* SPI_VERSION >= 2 */


#if SPI_VERSION == 2
/* write inter-word delay */
#define ioctlSPI_WRITE_DATA_DELAY(pSpiBase, param)    \
  periphMemWrite(param, &((pSpiBase)->delay))

/* enable SPI FIFOs */
#define ioctlSPI_QUEUED_MODE(pSpiBase, param)    \
  if (param) periphBitSet(SPI_FIFO_FIFO_ENA, &((pSpiBase)->fifo)); \
  else periphBitClear(SPI_FIFO_FIFO_ENA, &((pSpiBase)->fifo))
  
/* set how many words in TX FIFO causes TXEMPTY condition */  
#define ioctlSPI_SET_TXEMPTY_CONDITION(pSpiBase, param)    \
  periphBitGrpSet(SPI_FIFO_TFWM_MASK, (param) << 5, &((pSpiBase)->fifo))

/* set how many words (plus 1) in RX FIFO causes RXFULL condition */  
#define ioctlSPI_SET_RXFULL_CONDITION(pSpiBase, param)    \
  periphBitGrpSet(SPI_FIFO_RFWM_MASK, (param) << 2, &((pSpiBase)->fifo))

/* returns non-zero if valid data are waiting in receive FIFO */
#define ioctlSPI_CAN_READ_DATA(pSpiBase, param)    \
  (periphMemRead(&((pSpiBase)->fifo)) & SPI_FIFO_RFCNT_MASK)

/* returns non-zero if free space in TX FIFO enables data write */
#define ioctlSPI_CAN_WRITE_DATA(pSpiBase, param)    \
  (!(periphMemRead(&((pSpiBase)->fifo)) & SPI_FIFO_TFCNT_FULL))

#endif /* SPI_VERSION == 2 */


/***********************************************************************
* End-of-life commands (maintained for backward compatibility only)
***********************************************************************/

#define ioctlSPI_WRITE(pSpiBase, param) \
  periphMemWrite(param, &((pSpiBase)->spdtr))

#define ioctlSPI_READ(pSpiBase, param) \
  periphMemRead(&((pSpiBase)->spdrr))

#define ioctlSPI_ERROR_IS_OVERFLOW(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_OVRF, &((pSpiBase)->spscr))

#define ioctlSPI_ERROR_IS_MODEFAULT(pSpiBase, param) \
  periphBitTest(SPI_SPSCR_MODF, &((pSpiBase)->spscr))

#define ioctlSPI_SET_DATA_SIZE(pSpiBase, param) \
  periphBitGrpSR(SPI_SPDSCR_DS_MASK, (param)-1, &((pSpiBase)->spdsr))

#define ioctlSPI_INT_SELECT(pSpiBase, param)        \
  periphBitGrpRS (SPI_SPSCR_SPTIE | SPI_SPSCR_SPRIE | SPI_SPSCR_ERRIE, param, &((pSpiBase)->spscr))


/***********************************************************************
* High level driver commands
***********************************************************************/

/* clear status */
#define ioctlSPI_CLEAR_EXCEPTION(pSpiBase, param)  \
  periphBitClear(SPI_STATUS_EXCEPTION_EXIST | SPI_EXCEPTION_BUFFER_OVERFLOW |\
          SPI_EXCEPTION_OVERRUN | SPI_EXCEPTION_MODE_FAULT, &spi0_status)

/* get status */
#define ioctlSPI_GET_STATUS(pSpiBase, param)  \
  (((pSpiBase) == __SPI_0) ? periphMemRead(&spi0_status) :   \
  (((pSpiBase) == __SPI_1) ? periphMemRead(&spi1_status) : 0 ))

/* cancel SPI write operation */
#define ioctlSPI_WRITE_CANCEL(pSpiBase, param)  \
  if ((pSpiBase) == __SPI_0) { \
    periphBitClear(SPI_SPSCR_SPTIE, (UWord16 *) &__SPI_0->spscr); \
    periphMemWrite(0x0000, &spi0_TxCounter); \
    periphBitClear(SPI_STATUS_WRITE_INPROGRESS, &spi0_status); \
  } else if((pSpiBase) == __SPI_1) { \
    periphBitClear(SPI_SPSCR_SPTIE, (UWord16 *) &__SPI_1->spscr); \
    periphMemWrite(0x0000, &spi1_TxCounter); \
    periphBitClear(SPI_STATUS_WRITE_INPROGRESS, &spi1_status); \
  }
    
/* cancel SPI read operation */
#define ioctlSPI_READ_CANCEL(pSpiBase, param)  \
  if ((pSpiBase) == __SPI_0) { \
    periphBitClear(SPI_SPSCR_SPRIE, (UWord16 *) &__SPI_0->spscr); \
    periphMemWrite(0x0000, &spi0_RxCounter); \
    periphBitClear(SPI_STATUS_READ_INPROGRESS, &spi0_status); \
  } else if((pSpiBase) == __SPI_1) { \
    periphBitClear(SPI_SPSCR_SPRIE, (UWord16 *) &__SPI_1->spscr); \
    periphMemWrite(0x0000, &spi1_RxCounter); \
    periphBitClear(SPI_STATUS_READ_INPROGRESS, &spi1_status); \
  }

#ifdef __cplusplus
}
#endif

#endif
