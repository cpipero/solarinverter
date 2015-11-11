/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  iic.h
*
* $Date:      Feb-14-2007$
*
* $Version:   2.3.13.0$
*
* Description: Header file for the I2C low-level driver
*
* This file only supports one hardware version of the module (IIC_VERSION_2). 
* A version  of module used in your project is defined in the "arch.h" 
* processor architecture definition file.
*
*  IIC_VERSION_1 .. 56F801x devices, see MC56F8000RM.pdf
*  IIC_VERSION_2 .. 56F802x/3x devices, see MC56F802x3xRM.pdf
*
*******************************************************************************/

#ifndef __IIC_H
#define __IIC_H

/* qs.h is a master header file, which must be included */
#if !defined(__ARCH_H) || !defined(__PERIPH_H) || !defined(__APPCONFIG_H)
#error Please include qs.h before iic.h
#endif

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*
*                      General Interface Description
*
*
* The Inter-IC Bus (IIC or I2C) is a two-wire, bidirectional serial bus that provides 
* a simple, efficient method of data exchange between devices. Being a two-wire device, 
* the IIC Bus minimizes the need for large numbers of connections between devices, 
* and eliminates the need for an address decoder.
* 
* This bus is suitable for applications requiring occasional communications over a 
* short distance between a number of devices. It also provides flexibility, allowing 
* additional devices to be connected to the bus for further expansion and system 
* development.
*
* For more information, please refer to the user manual for the particular chip that you
* are using, such as the MC56F802x/3x Peripheral Manual, for a description
* of the I2C device.
*
* The I2C device driver interface uses "ioctl" call to control specific I2C functions
* during operation. For details see "ioctl" call.
*
******************************************************************************/

/************************************************************
* I2C module identifier
*************************************************************/

#ifdef IIC_BASE
#define IIC (&ArchIO.Iic)
#define I2C IIC
#endif

/*************************************************************
* arch.h should define device-specific information about IIC
**************************************************************/

#if !defined(IIC_VERSION)
#error IIC not properly described in arch.h (old Quick_Start version?)
#endif

#if !defined(IIC_VERSION_2)
#error This file implements IIC version 2 only (56F802x/3x devices or later)
#endif

/****************************************************
* Configurable items, i.e. defines for appconfig.h
*****************************************************

    #define IIC_ENBL_INIT  
    #define IIC_CTRL_INIT  
    #define IIC_SAR_INIT   
    #define IIC_RXFT_INIT  
    #define IIC_TXFT_INIT  
    #define IIC_SSHCNT_INIT
    #define IIC_SSLCNT_INIT
    #define IIC_FSHCNT_INIT
    #define IIC_FSLCNT_INIT
    #define IIC_IENBL_INIT 
   
    #define INT_VECTOR_ADDR_yy      iic_isr_xx
    #define INT_PRIORITY_LEVEL_yy   // one of INTC_DISABLED, INTC_LEVEL0, INTC_LEVEL1 or INTC_LEVEL2
   
    where:  
         yy is IIC interrupt vector number (40-44 on MC56F802x/3x)
   
*/ 

/*****************************************************************
* ioctl() commands
*
*  Word16 ioctl( I2C, Command_name, Parameter );
*
******************************************************************

 COMMAND NAME                      PARAMETERS, COMMENTS
--------------------------------------------------------*/

#define IIC_INIT                    /* NULL */

#define IIC_MODULE                  /* IIC_ENABLE/IIC_DISABLE; Enable/disable IIC module */
#define IIC_TRY_GRACEFUL_SHUTDOWN   /* UWord16 as activity timeout value (in 16x-core-clocks), 0 is max=65536x16 clocks
                                       Tries to perform gracefull disconnect, returns IIC_SHUTDOWN_xxx codes */

/* configuration-time only commands (IIC has to be disabled)*/
#define IIC_SLAVE_OPERATION         /* IIC_ENABLE/IIC_DISABLE; Enable/disable slave operation */
#define IIC_MASTER_OPERATION        /* IIC_ENABLE/IIC_DISABLE; Enable/disable master operation */
#define IIC_USE_REPEATED_START      /* IIC_ENABLE/IIC_DISABLE; Enable/disable master repeated-start */
#define IIC_SET_ADDRESS             /* UWord16 address, set slave address, use IIC_10BIT_ADDRESS flag for 10-bit address */
#define IIC_SET_SPEED_MODE          /* IIC_NORMAL_SPEED/IIC_FAST_SPEED; Set master-mode speed mode */
#define IIC_SET_SSHCNT              /* UWord16 - the SSHCNT value in clock cycles */
#define IIC_SET_SSLCNT              /* UWord16 - the SSLCNT value in clock cycles */
#define IIC_SET_FSHCNT              /* UWord16 - the FSHCNT value in clock cycles */
#define IIC_SET_FSLCNT              /* UWord16 - the FSLCNT value in clock cycles */

/* master-initiated transactions */
#define IIC_CAN_INITIATE_TRANSACTION /* NULL, returns nonzero if master transaction can be started */
#define IIC_INITIATE_TRANSACTION     /* UWord16 target address; initiate normal transaction to the target
                                        optionally OR with IIC_10BIT_ADDRESS flag to specify 10-bit addr */
#define IIC_INITIATE_SB_TRANSACTION  /* UWord16 target address; initiate start-byte transaction to the target
                                        optionally OR with IIC_10BIT_ADDRESS flag to specify 10-bit addr */
#define IIC_INITIATE_GC_TRANSACTION  /* NULL, initiate general-call write transaction (to address 0) */

#define IIC_MASTER_TRANSACTION_ACTIVE /* returns non-zero when master state machine is active */

/* data io */
#define IIC_CAN_READ_DATA            /* NULL, returns nonzero if RX FIFO contains any byte to be read */
#define IIC_READ_DATA                /* NULL, read byte from RX FIFO */

#define IIC_CAN_WRITE_DATA           /* NULL, returns nonzero if there is a space in TX FIFO to accept data */
#define IIC_WRITE_DATA               /* data byte as UWord16, write data to TX FIFO */

#define IIC_CAN_REQUEST_DATA         /* NULL, returns nonzero if there is a space in RX FIFO to accept data */
#define IIC_READ_REQUEST             /* NULL, request to clock-in one byte as a part of master-receive */

/* interrupts */
#define IIC_INT_ENABLE               /* combination of IIC_xxx_INT; enable given interrupts */
#define IIC_INT_DISABLE              /* combination of IIC_xxx_INT; disable given interrupts */
#define IIC_READ_INT_FLAGS           /* NULL; read all interrupt flags */
#define IIC_TEST_INT_FLAGS           /* combination of IIC_xxx_INT; test given interrupt flag(s) */

#define IIC_CLEAR_EINT_FLAGS         /* combination of IIC_xxx_INT; clear given ERROR interrupt flags */
#define IIC_CLEAR_GINT_FLAGS         /* combination of IIC_xxx_INT; clear given GENERALCALL interrupt flags */
#define IIC_CLEAR_TINT_FLAGS         /* combination of IIC_xxx_INT; clear given TX interrupt flags, except TXEMPTY */
#define IIC_CLEAR_SINT_FLAGS         /* combination of IIC_xxx_INT; clear given STATUS interrupt flags */

#define IIC_CLEAR_ALL_INTS           /* NULL, clears all interrupt sources and TXABRTSRC register */
#define IIC_READ_TXABORT_SOURCE      /* NULL, returns value of TXABRTSRC register */
#define IIC_CLEAR_TXABORT_SOURCE     /* NULL, clears TXABRT interrupt and TXABRTSRC register */

/* status */
#define IIC_READ_STATUS_FLAGS        /* NULL, read all status register */
#define IIC_TEST_STATUS_FLAGS        /* combination of IIC_STAT_xxx, test given status flags */

/****************************************************************************
* IIC PARAMETERS DEFINITION
*****************************************************************************/

#define IIC_DISABLE        0
#define IIC_ENABLE         1

#define IIC_NORMAL_SPEED   IIC_CTRL_SPD_STD
#define IIC_FAST_SPEED     IIC_CTRL_SPD_FAST

/* flag to OR with a number to specify extended 10-bit address */
#define IIC_10BIT_ADDRESS  IIC_TAR_ADDRMST

/* IIC ERROR interrupts */
#define IIC_TXABRT_INT     IIC_IENBL_TXABRT  
#define IIC_TXOVR_INT      IIC_IENBL_TXOVR   
#define IIC_RXOVR_INT      IIC_IENBL_RXOVR   
#define IIC_RXUND_INT      IIC_IENBL_RXUND   

/* IIC GENERALCALL interrupts */
#define IIC_GC_INT         IIC_IENBL_GC      

/* IIC RECEIVER interrupts */
#define IIC_RXFULL_INT     IIC_IENBL_RXFULL  

/* IIC TRANSMITTER interrupts */
#define IIC_TXDONE_INT     IIC_IENBL_TXDONE  
#define IIC_RDREQ_INT      IIC_IENBL_RDREQ   
#define IIC_TXEMPTY_INT    IIC_IENBL_TXEMPTY 

/* IIC STATUS interrupts */
#define IIC_STDET_INT      IIC_IENBL_STDET   
#define IIC_STPDET_INT     IIC_IENBL_STPDET  
#define IIC_ACT_INT        IIC_IENBL_ACT     

/* IIC_TRY_GRACEFUL_SHUTDOWN error codes */
#define IIC_SHUTDOWN_SUCCESS      0
#define IIC_SHUTDOWN_STILLBUSY    1
#define IIC_SHUTDOWN_REACTIVATED  2

/****************************************************************************
* register and bit names used in the ioctl functions below
*****************************************************************************/

/* IIC Control Register */
#define IIC_CTRL_SLVDIS          0x0040
#define IIC_CTRL_RSTEN           0x0020
#define IIC_CTRL_ADDRMST         0x0010
#define IIC_CTRL_ADDRSLV         0x0008
#define IIC_CTRL_SPD_MASK        0x0006
#define IIC_CTRL_SPD_FAST        0x0004
#define IIC_CTRL_SPD_STD         0x0002
#define IIC_CTRL_MSTEN           0x0001

/* IIC Target Address Register */
#define IIC_TAR_ADDRMST          0x1000
#define IIC_TAR_SPCL             0x0800
#define IIC_TAR_GCSTRT           0x0400
#define IIC_TAR_TA_MASK          0x03ff

/* IIC Slave Address Register */
#define IIC_SAR_SA_MASK          0x03ff

/* IIC Data Buffer and Command Register */
#define IIC_DATA_CMD             0x0100
#define IIC_DATA_DAT_MASK        0x00ff

/* IIC Interrupt Status Register */
#define IIC_ISTAT_GC             0x0800
#define IIC_ISTAT_STDET          0x0400
#define IIC_ISTAT_STPDET         0x0200
#define IIC_ISTAT_ACT            0x0100
#define IIC_ISTAT_TXDONE         0x0080
#define IIC_ISTAT_TXABRT         0x0040
#define IIC_ISTAT_RDREQ          0x0020
#define IIC_ISTAT_TXEMPTY        0x0010
#define IIC_ISTAT_TXOVR          0x0008
#define IIC_ISTAT_RXFULL         0x0004
#define IIC_ISTAT_RXOVR          0x0002
#define IIC_ISTAT_RXUND          0x0001

/* IIC Interrupt Enable Register */
#define IIC_IENBL_GC             0x0800
#define IIC_IENBL_STDET          0x0400
#define IIC_IENBL_STPDET         0x0200
#define IIC_IENBL_ACT            0x0100
#define IIC_IENBL_TXDONE         0x0080
#define IIC_IENBL_TXABRT         0x0040
#define IIC_IENBL_RDREQ          0x0020
#define IIC_IENBL_TXEMPTY        0x0010
#define IIC_IENBL_TXOVR          0x0008
#define IIC_IENBL_RXFULL         0x0004
#define IIC_IENBL_RXOVR          0x0002
#define IIC_IENBL_RXUND          0x0001

/* IIC Raw Interrupt Status Register */
#define IIC_RISTAT_GC            0x0800
#define IIC_RISTAT_STDET         0x0400
#define IIC_RISTAT_STPDET        0x0200
#define IIC_RISTAT_ACT           0x0100
#define IIC_RISTAT_TXDONE        0x0080
#define IIC_RISTAT_TXABRT        0x0040
#define IIC_RISTAT_RDREQ         0x0020
#define IIC_RISTAT_TXEMPTY       0x0010
#define IIC_RISTAT_TXOVR         0x0008
#define IIC_RISTAT_RXFULL        0x0004
#define IIC_RISTAT_RXOVR         0x0002
#define IIC_RISTAT_RXUND         0x0001

/* IIC Receive FIFO Threshold Register */
#define IIC_RXFT_RXTL_MASK       0x0003

/* IIC Receive FIFO Level Register */
#define IIC_RXFLR_RXFL_MASK      0x0007

/* IIC Transmit FIFO Threshold Register */
#define IIC_TXFT_TXTL_MASK       0x0003

/* IIC Transmit FIFO Level Register */
#define IIC_TXFLR_TXFL_MASK      0x0007

/* IIC Enable Register */
#define IIC_ENBL_EN              0x0001

/* IIC Status Register */
#define IIC_STAT_SLVACT          0x0040
#define IIC_STAT_MSTACT          0x0020
#define IIC_STAT_RFF             0x0010
#define IIC_STAT_RFNE            0x0008
#define IIC_STAT_TFE             0x0004
#define IIC_STAT_TFNF            0x0002
#define IIC_STAT_ACT             0x0001

/* IIC status register offset (needed in iic.c) */
#define IIC_STAT_OFFSET          0x38

/* IIC Raw Interrupt Status Register */
#define IIC_TXABRTSRC_SLVRD      0x8000
#define IIC_TXABRTSRC_SLVAL      0x4000
#define IIC_TXABRTSRC_SLVFLSH    0x2000
#define IIC_TXABRTSRC_AL         0x1000
#define IIC_TXABRTSRC_MSTDIS     0x0800
#define IIC_TXABRTSRC_RNORST     0x0400
#define IIC_TXABRTSRC_SNORST     0x0200
#define IIC_TXABRTSRC_SACKDET    0x0080
#define IIC_TXABRTSRC_GCREAD     0x0020
#define IIC_TXABRTSRC_GCNACK     0x0010
#define IIC_TXABRTSRC_TDNACK     0x0008
#define IIC_TXABRTSRC_AD2NACK    0x0004
#define IIC_TXABRTSRC_AD1NACK    0x0002
#define IIC_TXABRTSRC_AD7NACK    0x0001

/****************************************************************************
* I2C ioctl macro implementation
*****************************************************************************/

/***********************************************************************
* I2C init
***********************************************************************/

void iicInit(arch_sIIC *pIicBase);
#define ioctlIIC_INIT(pIicBase, bParam) iicInit(pIicBase)

/* Enable/disable IIC module */
#define ioctlIIC_MODULE(pIicBase, param) \
  if (param) periphBitSet(IIC_ENBL_EN, &((pIicBase)->enbl)); \
  else periphBitClear(IIC_ENBL_EN, &((pIicBase)->enbl))

UWord16 IIC_TryGracefulShutdown(arch_sIIC *pIicBase, UWord16 timeout);
#define ioctlIIC_TRY_GRACEFUL_SHUTDOWN(pIicBase, param) \
  IIC_TryGracefulShutdown(pIicBase, param)

/* Enable/disable slave operation */
#define ioctlIIC_SLAVE_OPERATION(pIicBase, param) \
  if (param) periphBitClear(IIC_CTRL_SLVDIS, &((pIicBase)->ctrl)); \
  else periphBitSet(IIC_CTRL_SLVDIS, &((pIicBase)->ctrl))

/* Enable/disable master operation */
#define ioctlIIC_MASTER_OPERATION(pIicBase, param) \
  if (param) periphBitSet(IIC_CTRL_MSTEN, &((pIicBase)->ctrl)); \
  else periphBitClear(IIC_CTRL_MSTEN, &((pIicBase)->ctrl))       

/* set slave address, use IIC_10BIT_ADDRESS flag to specify 10-bit address */
#define ioctlIIC_SET_ADDRESS(pIicBase, param) { \
  periphMemWrite((param) & IIC_SAR_SA_MASK, &((pIicBase)->sar)); \
  if ((param) & IIC_10BIT_ADDRESS) periphBitSet(IIC_CTRL_ADDRSLV, &((pIicBase)->ctrl)); \
  else periphBitClear(IIC_CTRL_ADDRSLV, &((pIicBase)->ctrl)); }

/* Enable/disable master repeated-start */
#define ioctlIIC_USE_REPEATED_START(pIicBase, param) \
  if (param) periphBitSet(IIC_CTRL_RSTEN, &((pIicBase)->ctrl)); \
  else periphBitClear(IIC_CTRL_RSTEN, &((pIicBase)->ctrl))         

/* Set master-mode speed mode */
#define ioctlIIC_SET_SPEED_MODE(pIicBase, param) \
  periphBitGrpSet(IIC_CTRL_SPD_MASK, param, &((pIicBase)->ctrl))

/* write the SSHCNT register value */
#define ioctlIIC_SET_SSHCNT(pIicBase, param) \
  if((param) > 8) periphMemWrite((param)-8, &((pIicBase)->sshcnt)); \
  else periphMemWrite(0, &((pIicBase)->sshcnt))

/* write SSLCNT register value */
#define ioctlIIC_SET_SSLCNT(pIicBase, param) \
  if((param) > 1) periphMemWrite((param)-1, &((pIicBase)->sslcnt)); \
  else periphMemWrite(0, &((pIicBase)->sslcnt))

/* write FSHCNT register value */
#define ioctlIIC_SET_FSHCNT(pIicBase, param) \
  if((param) > 8) periphMemWrite((param)-8, &((pIicBase)->fshcnt)); \
  else periphMemWrite(0, &((pIicBase)->fshcnt))

/* write FSLCNT register value */
#define ioctlIIC_SET_FSLCNT(pIicBase, param) \
  if((param) > 1) periphMemWrite((param)-1, &((pIicBase)->fslcnt)); \
  else periphMemWrite(0, &((pIicBase)->fslcnt))

/* returns nonzero if master transaction can be started */
#define ioctlIIC_CAN_INITIATE_TRANSACTION(pIicBase, param) \
  ( periphBitTest(IIC_STAT_MSTACT | IIC_STAT_TFE, &((pIicBase)->stat)) == IIC_STAT_TFE )

/* initiate normal transaction to the target */
#define ioctlIIC_INITIATE_TRANSACTION(pIicBase, param) \
  periphMemWrite(((param) & (IIC_TAR_TA_MASK | IIC_TAR_ADDRMST)), &((pIicBase)->tar))

/* initiate start byte transaction to the target */
#define ioctlIIC_INITIATE_SB_TRANSACTION(pIicBase, param) \
  periphMemWrite(((param) & (IIC_TAR_TA_MASK | IIC_TAR_ADDRMST)) | IIC_TAR_SPCL | IIC_TAR_GCSTRT, \
    &((pIicBase)->tar))

/* initiate general-call write transaction (to address 0) */
#define ioctlIIC_INITIATE_GC_TRANSACTION(pIicBase, param) \
  periphBitGrpSet(IIC_TAR_SPCL | IIC_TAR_GCSTRT, IIC_TAR_SPCL, &((pIicBase)->tar))

/* data io */
#define ioctlIIC_READ_DATA(pIicBase, param) \
  ( periphMemForcedRead(&((pIicBase)->data)) & 0xff )
  
#define ioctlIIC_WRITE_DATA(pIicBase, param) \
  periphMemWrite((param) & 0xff, &((pIicBase)->data))

#define ioctlIIC_READ_REQUEST(pIicBase, param) \
  periphMemWrite(0x100, &((pIicBase)->data))

/* enable given interrupts */
#define ioctlIIC_INT_ENABLE(pIicBase, param) \
  periphBitSet(param, &((pIicBase)->ienbl))
             
/* disable given interrupts */             
#define ioctlIIC_INT_DISABLE(pIicBase, param) \
  periphBitClear(param, &((pIicBase)->ienbl))

/* read all interrupt flags */
#define ioctlIIC_READ_INT_FLAGS(pIicBase, param) \
  periphMemRead(&((pIicBase)->ristat))

/* test given interrupt flag(s) */
#define ioctlIIC_TEST_INT_FLAGS(pIicBase, param) \
  periphBitTest(param, &((pIicBase)->ristat))

/* clear given ERROR interrupt flags */
#define ioctlIIC_CLEAR_EINT_FLAGS(pIicBase, param) { \
  if((param) & IIC_TXABRT_INT) periphMemDummyRead(&((pIicBase)->clrtxabrt)); \
  if((param) & IIC_TXOVR_INT ) periphMemDummyRead(&((pIicBase)->clrtxovr)); \
  if((param) & IIC_RXOVR_INT ) periphMemDummyRead(&((pIicBase)->clrrxovr)); \
  if((param) & IIC_RXUND_INT ) periphMemDummyRead(&((pIicBase)->clrrxund)); }

/* clear given GENERALCALL interrupt flags */
#define ioctlIIC_CLEAR_GINT_FLAGS(pIicBase, param) { \
  if((param) & IIC_GC_INT) periphMemDummyRead(&((pIicBase)->clrgc)); }

/* clear given TRANSMITTER interrupt flags */
#define ioctlIIC_CLEAR_TINT_FLAGS(pIicBase, param) { \
  if((param) & IIC_TXDONE_INT) periphMemDummyRead(&((pIicBase)->clrtxdone)); \
  if((param) & IIC_RDREQ_INT ) periphMemDummyRead(&((pIicBase)->clrrdreq)); }
  
/* clear given STATUS interrupt flags */
#define ioctlIIC_CLEAR_SINT_FLAGS(pIicBase, param) { \
  if((param) & IIC_STDET_INT ) periphMemDummyRead(&((pIicBase)->clrstdet)); \
  if((param) & IIC_STPDET_INT) periphMemDummyRead(&((pIicBase)->clrstpdet)); \
  if((param) & IIC_ACT_INT   ) periphMemDummyRead(&((pIicBase)->clract)); }

/* clears all interrupt sources and TXABORT_SOURCE */
#define ioctlIIC_CLEAR_ALL_INTS(pIicBase, param) \
  periphMemDummyRead(&((pIicBase)->clrint))

/* returns value of TXABRTSRC register */
#define ioctlIIC_READ_TXABORT_SOURCE(pIicBase, param) \
  periphMemRead(&((pIicBase)->txabrtsrc))

/* clears TXABRTSRC register */
#define ioctlIIC_CLEAR_TXABORT_SOURCE(pIicBase, param) \
  periphMemDummyRead(&((pIicBase)->clrtxabrt))

/* returns non-zero when master state machine is active */
#define ioctlIIC_MASTER_TRANSACTION_ACTIVE(pIicBase, param) \
  periphBitTest(IIC_STAT_MSTACT, &((pIicBase)->stat))
  
/* returns nonzero if RX FIFO contains any byte to be read */
#define ioctlIIC_CAN_READ_DATA(pIicBase, param) \
  periphBitTest(IIC_STAT_RFNE, &((pIicBase)->stat))

/* returns nonzero if there is a space in TX FIFO to accept data */
#define ioctlIIC_CAN_WRITE_DATA(pIicBase, param) \
  periphBitTest(IIC_STAT_TFNF, &((pIicBase)->stat))

/* returns nonzero if RX FIFO is not full */
#define ioctlIIC_CAN_REQUEST_DATA(pIicBase, param) \
  ( ! periphBitTest(IIC_STAT_RFF, &((pIicBase)->stat)) )

/* read all status register */
#define ioctlIIC_READ_STATUS_FLAGS(pIicBase, param) \
  periphMemRead(&((pIicBase)->stat))

/* test given status flags */
#define ioctlIIC_TEST_STATUS_FLAGS(pIicBase, param) \
  periphBitTest(param, &((pIicBase)->stat))

#ifdef __cplusplus
}
#endif

#endif                                      
