#include "version.h"
#include "hawkcpu.h"

#define TARGET_SDM                  /* Small Data Model */
#define TARGET_CODE_PFLASH          /* Code located in internal flash */
#define TARGET_CONSTDATA_INTRAM     /* Constants and const variables located in x RAM */
#define TARGET_INITDATA_PFLASH      /* Initialization values for global variables located in pFlash */
#define TARGET_DATA_INTRAM          /* Variables located in internal RAM */

#pragma define_section fardata  "fardata.data" "fardata.bss" RW  /* can be used to put far data (after 0x10000) */
#pragma define_section pramcode "pramcode.text" RWX  /* can be used to put code to program ram */

#if 0   /*
#
# This is quite tricky here. We are using this file as BOTH linker command 
# file AND the C-preprocessor prefix file for selected target.
#
# In C prefix file, we define a set of macros to enable conditional compilation 
# based on target settings. For example, you can disable compilation of memory 
# initialization using Rom_to_Ram features when such is not used. 
#
# */

# memory use for this LCF: 
#
# interrupt vectors --> pROM starting at zero, reset vectors also in bootflash
#      program code --> pROM
#         constants --> same as initialized variables
#      dynamic data --> pROM copied to internal xRAM
#         variables --> int xRAM
#


MEMORY 
{
    .p_flash_ROM          (RX)  : ORIGIN = 0x4000,   LENGTH = 0x4000

    ###############################
    # The internal RAM is physically shared among P-RAM and X-RAM so the user 
    # has to do partitioning between the two when putting variables. These two
    # lines define full memory areas (just for an information, not used for variables).
    .p_all_internal_RAM   (RWX) : ORIGIN = 0x8000, LENGTH = 0x0800
    .x_all_internal_RAM   (RW)  : ORIGIN = 0x0000, LENGTH = 0x0800

    ###############################
    # the partitioning is made here (0x7e0 of X-RAM vs. 0x020 of P-RAM)
    .p_internal_RAM         (RWX) : ORIGIN = 0x87e0, LENGTH = 0x0020
    .x_internal_RAM         (RW)  : ORIGIN = 0x0001, LENGTH = 0x07df 

    # ximage MUST be set same as x_internal_RAM above (with X flag set)
    .p_internal_RAM_ximage  (RX)  : ORIGIN = 0x0001, LENGTH = 0x07df
    
    .x_onchip_peripherals   (RW)  : ORIGIN = 0xF000, LENGTH = 0x1000
    .x_EOnCE                (R)   : ORIGIN = 0xFFFF00, LENGTH = 0x0100
}

# we ensure the interrupt vector section is not deadstripped here

KEEP_SECTION{ interrupt_vectors.text }

SECTIONS 
{
    # bounds for internal RAM checking (define before .x_internal_RAM is used!)
    F_Linternal_RAM_addr = ADDR(.x_internal_RAM);
    F_Linternal_RAM_size = SIZEOF(.x_internal_RAM)/2;

    # Our interrupt table is put to begining of the internal pFlash
    # VBA (vectors base) register is set to this address in startup code
    
    .interrupt_vectors :
    {
        * (interrupt_vectors.text)  
       
    } > .p_flash_ROM

    # interrupt table address
    F_Linterrupt_vectors_addr = ADDR(.interrupt_vectors);

    .executing_code :
    {
        # .text sections
        
        * (.text)
        * (rtlib.text)
        * (fp_engine.text)
        * (user.text)    
         
    } >> .p_flash_ROM

    .p_flash_ROM_data :
    {
        # initialized __pmem constants stay in p_flash ROM
        
        * (.const.data.char.pmem)
        * (.const.data.pmem)
        
        # save address where the init data image start in pROM
        _datap_ROM_addr = .;
        
    } >> .p_flash_ROM

    .pmemdata_image :  AT(_datap_ROM_addr)  # data load address is in pFlash
    {
        # __pmem .data sections (init values saved in pROM)
        
        # remember data start so we can copy data later to pRAM
        _datap_RAM_addr = .; 
        
        * (pramcode.text)    # treat pramcode just like initialized __pmem data
        * (.data.char.pmem)
        * (.data.pmem)
        . = . + .%2;

        _datap_RAM_end = .;
        _datap_size = _datap_RAM_end - _datap_RAM_addr;

        # calculate address for next part of pROM data
        _data_ROM_addr = _datap_ROM_addr + _datap_size;
        
    } > .p_internal_RAM
        
    .pmemdata :
    {
        # __pmem .bss section
        
        _BSSP_START = .;
        * (.bss.char.pmem)
        * (.bss.pmem)
        . = . + .%2;
        _BSSP_END = .;
        
    } >> .p_internal_RAM

    .data_image : AT(_data_ROM_addr) 
    {                             
        # the data sections (init values saved in pROM)
        
        # remember data start so we can copy data later to xRAM
        _data_RAM_addr = .; 
        
        * (fp_state.data)
        * (rtlib.data)
        * (.const.data.char)  
        * (.const.data)
        * (.data.char)      
        * (.data)       
        . = . + .%2;
   
        _data_RAM_end = .;
        _data_size = _data_RAM_end - _data_RAM_addr;
        
    } > .p_internal_RAM_ximage

    .data :
    {
        # save space for the pROM data copy 
        . = _data_RAM_end;
            
        # .bss section
        
        _BSS_START = .;
        * (rtlib.bss.lo)
        * (rtlib.bss)
        * (.bss.char)
        * (.bss)
        . = . + .%2;
        _BSS_END   = .;

        # setup the heap address 
        
        . = ALIGN(4);
        _HEAP_ADDR = .;
        _HEAP_SIZE = 0x0;
        _HEAP_END = _HEAP_ADDR + _HEAP_SIZE; 
        . = _HEAP_END;

        # setup the stack address 
        
        _min_stack_size = 0x100;
        _stack_addr = _HEAP_END;
        _stack_end  = _stack_addr + _min_stack_size;
        . = _stack_end;
        
    } > .x_internal_RAM    # internal RAM for data

    # used by MSL 
        
    F_heap_addr   = _HEAP_ADDR;
    F_heap_end    = _HEAP_END;

    # stationery init code uses these globals:

    F_Lstack_addr   = _stack_addr;

    # BSS addresses used in init code

    F_Lbss_start   = _BSS_START;
    F_Lbss_end     = _BSS_END;
    F_Lbss_size    = _BSS_END - _BSS_START;

    F_Lbssp_start  = _BSSP_START;
    F_Lbssp_end    = _BSSP_END;
    F_Lbssp_size   = _BSSP_END - _BSSP_START;
    
    # data ROM to RAM copying used in init code
    
    F_Ldata_ROM_addr = _data_ROM_addr;
    F_Ldata_RAM_addr = _data_RAM_addr;
    F_Ldata_size = _data_size;

    F_Ldatap_ROM_addr = _datap_ROM_addr;
    F_Ldatap_RAM_addr = _datap_RAM_addr;
    F_Ldatap_size = _datap_size;
    
    # peripheral registers
    FArchIO = ADDR(.x_onchip_peripherals);
}

#endif  /* end of code excluded by C-compiler */
