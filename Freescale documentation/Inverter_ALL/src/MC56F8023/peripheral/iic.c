/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* File Name:  iic.c
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.10.0$
*
* Description: Source file for the I2C driver (803x devices)
*
*****************************************************************************/

#include "qs.h"
#include "iic.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 iicInit() function performs the I2C module static configuration
 based on the configurable items from appconfig.h 
********************************************************************************/

void iicInit(arch_sIIC *pI2cBase)
{
#pragma unused(pI2cBase)

    /* disable I2C module to enable write-access to configuration registers */
    periphMemWrite(0, &pI2cBase->enbl);

    /* write timing registers */
    #ifdef IIC_SSHCNT_INIT
    periphMemWrite(IIC_SSHCNT_INIT, &pI2cBase->sshcnt);
    #endif
    #ifdef IIC_SSLCNT_INIT
    periphMemWrite(IIC_SSLCNT_INIT, &pI2cBase->sslcnt);
    #endif
    #ifdef IIC_FSHCNT_INIT
    periphMemWrite(IIC_FSHCNT_INIT, &pI2cBase->fshcnt);
    #endif
    #ifdef IIC_FSLCNT_INIT
    periphMemWrite(IIC_FSLCNT_INIT, &pI2cBase->fslcnt);
    #endif

    /* FIFO control registers */
    #ifdef IIC_RXFT_INIT  
    periphMemWrite(IIC_RXFT_INIT, &pI2cBase->rxft);
    #endif
    #ifdef IIC_TXFT_INIT  
    periphMemWrite(IIC_TXFT_INIT, &pI2cBase->txft);
    #endif

    /* write slave configuration */
    #ifdef IIC_SAR_INIT   
    periphMemWrite(IIC_SAR_INIT, &pI2cBase->sar);
    #endif

    /* write master/slave control register */
    #ifdef IIC_CTRL_INIT  
    periphMemWrite(IIC_CTRL_INIT, &pI2cBase->ctrl);
    #endif
    
    periphMemWrite(0x55, &pI2cBase->tar);
    
    /* enable interrupts */
    #ifdef IIC_IENBL_INIT 
    periphMemWrite(IIC_IENBL_INIT, &pI2cBase->ienbl);
    #endif

    /* start IIC module (if configured so) */
    #ifdef IIC_ENBL_INIT
    periphMemWrite(IIC_ENBL_INIT, &pI2cBase->enbl);
    #endif
}

/* wait until IIC activity flag goes low, timeout is measured in 16x bus cycles
   (provided the code runs from zero waitstate memory which is true for 56F802x/3x */

static asm void IIC_WaitActIdle(register arch_sIIC *pIicBase, register UWord16 timeout)
{
loop:
        /* exit loop when ACT zero */
        brclr IIC_STAT_ACT, X:(pIicBase+IIC_STAT_OFFSET), <<exit_loop   /* 6 cycles */
        
        nop; nop;       /* 2 cycles */
        dec.w timeout   /* 1 cycle */
        nop             /* 2 cycles */
        bne <loop       /* 5 cycles */

        nop
        nop
        
exit_loop:        
        rts
}

/* wait until IIC activity flag goes high, timeout is measured in 16x bus cycles
   (provided the code runs from zero waitstate memory which is true for 56F802x/3x */

static asm void IIC_WaitActBusy(register arch_sIIC *pIicBase, register UWord16 timeout)
{
loop:
        /* exit loop when ACT set */
        brset IIC_STAT_ACT, X:(pIicBase+IIC_STAT_OFFSET), <<exit_loop   /* 6 cycles */
        
        nop; nop;       /* 2 cycles */
        dec.w timeout   /* 1 cycle */
        nop             /* 2 cycles */
        bne <loop       /* 5 cycles */

        nop
        nop
        
exit_loop:        
        rts
}

/* this function safely disables the IIC module. it does not exactly follow the 
   recommended procedure, but shall still do its job provided the passed 
   "timeout" value is specified properly (should be longer than one IIC byte time) */

UWord16 IIC_TryGracefulShutdown(register arch_sIIC *pIicBase, register UWord16 timeout)
{
    /* wait until both slave and master go idle */
    IIC_WaitActIdle(pIicBase, timeout);
    
    /* error if still busy */
    if(ioctl(pIicBase, IIC_TEST_STATUS_FLAGS, IIC_STAT_ACT))
        return IIC_SHUTDOWN_STILLBUSY;
    
    /* disable IIC module */
    ioctl(pIicBase, IIC_MODULE, IIC_DISABLE);

    /* wait to check if anything goes active again */
    IIC_WaitActBusy(pIicBase, timeout);
    
    /* re-enable and report error if master or slave went busy again */
    if(ioctl(pIicBase, IIC_TEST_STATUS_FLAGS, IIC_STAT_ACT))
    {
        ioctl(pIicBase, IIC_MODULE, IIC_ENABLE);
        return IIC_SHUTDOWN_REACTIVATED;
    }
    
    /* ok, module properly detached from the bus */
    return IIC_SHUTDOWN_SUCCESS;
}

#ifdef __cplusplus
}
#endif

