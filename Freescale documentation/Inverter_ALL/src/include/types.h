/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2007 Freescale Semiconductor, Inc.
* (c) Copyright 2001-2004 Motorola, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name: types.h$
*
* $Date:      Feb-5-2007$
*
* $Version:   2.3.18.0$
*
* Description: Declaration of types for quick-start portable code
*              ITU definition of intrinsic functions
*
*****************************************************************************/

#ifndef __TYPES_H
#define __TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************
* Basic Types 
*******************************************************/

/* Generic word types for ITU compatibility */
typedef char           Word8;
typedef unsigned char  UWord8;
typedef short          Word16;
typedef unsigned short UWord16;
typedef long           Word32;
typedef unsigned long  UWord32;

typedef char           Int8;
typedef unsigned char  UInt8;
typedef int            Int16;
typedef unsigned int   UInt16;
typedef long           Int32;
typedef unsigned long  UInt32;

/* Fractional data types for portability */
typedef short          Frac16;
typedef long           Frac32;

typedef struct {
   Frac16     real;
   Frac16     imag;
} CFrac16;

typedef struct {
   Frac32     real;
   Frac32     imag;
} CFrac32;

/* Convert int/float to Frac16; constant x generates compile time constant */
//#define FRAC16(x) ((Frac16)((x) < (1- 2^(-15)) ? ((x) >= -1 ? (x)*0x8000 : 0x8000) : 0x7FFF))
#define FRAC16(x) ((Frac16)((x) < 0.999969482421875 ? ((x) >= -1 ? (x)*0x8000 : 0x8000) : 0x7FFF))
#define FRAC32(x) ((Frac32)((x) < 1 ? ((x) >= -1 ? (x)*0x80000000 : 0x80000000) : 0x7FFFFFFF))

/* Miscellaneous types */
#ifndef COMPILER_HAS_BOOL
typedef int bool;
#endif

/*******************************************************
* Constants
*******************************************************/

/* Function Result Values */
#define PASS  0
#define FAIL -1

#ifndef COMPILER_HAS_BOOL
#define true  1
#define false 0
#endif

#ifndef NULL
#define NULL ((void *)0)  /* or for C++ #define NULL 0 */
#endif

/*****************************************************
* Name mappings for DSP code portability
******************************************************/

/* void setnostat (void); */
#define setnosat   archSetNoSat

/* void setstat32 (void); */
#define setsat32   archSetSat32

/* void Stop (void); */
#define Stop        archStop

/* void Trap (void); */
#define Trap        archTrap

/* void Wait (void); */
#define Wait        archWait

/* void EnableInt (void); */
#define EnableInt   archEnableInt

/* void DisableInt (void); */
#define DisableInt  archDisableInt

#define MAX_32 (Word32)0x7fffffffL
#define MIN_32 (Word32)0x80000000L

#define MAX_16 (Word16)0x7fff
#define MIN_16 (Word16)0x8000

/*****************************************************
* type of peripheral register used in arch.h files
******************************************************/

#if !defined(COMPILER_HAS_ANON_MEMBERS) && defined(__MWERKS__)
#define COMPILER_HAS_ANON_MEMBERS 1
#endif

#define ARCH_REG(typ, reg) typ reg

#if COMPILER_HAS_ANON_MEMBERS

#define ARCH_REG1(typ, reg)             ARCH_REG(typ,reg)
#define ARCH_REG2(typ, reg, alt1)       union { ARCH_REG(typ,reg); ARCH_REG(typ,alt1); }
#define ARCH_REG3(typ, reg, alt1, alt2) union { ARCH_REG(typ,reg); ARCH_REG(typ,alt1); ARCH_REG(typ,alt2); }
#define ARCH_REG4(typ, reg, alt1, alt2, alt3) union { ARCH_REG(typ,reg); ARCH_REG(typ,alt1); ARCH_REG(typ,alt2); ARCH_REG(typ,alt3); }

#else /* !COMPILER_HAS_ANON_MEMBERS ... use only the one and only official register name */

#define ARCH_REG1(typ, reg)             ARCH_REG(typ,reg)
#define ARCH_REG2(typ, reg, alt1)       ARCH_REG(typ,reg)
#define ARCH_REG3(typ, reg, alt1, alt2) ARCH_REG(typ,reg)
#define ARCH_REG4(typ, reg, alt1, alt2, alt3) ARCH_REG(typ,reg)

#endif

#ifdef __cplusplus
}
#endif

#endif

