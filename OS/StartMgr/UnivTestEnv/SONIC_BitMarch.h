/*
	File:		SONIC_BitMarch.h

	Contains:	This is the include file for the SONIC bitmarch subtest.

	Written by:	Joe Smyth

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).

*/

#ifndef _SONIC_BitMarch_
#define _SONIC_BitMarch_
//
//	SONIC_BitMarch.h
//

#include <CTETypes.h>
#include <SONIC_Common.h>

//
// SONIC_BitMarch error return values.
//
typedef enum SONIC_BitMarch_Error
{
	SONIC_BitMarch_Err_Ok,
	SONIC_BitMarch_Err_Unexpected,
	SONIC_BitMarch_Err_disabling_interrupts,
	SONIC_BitMarch_Err_on_Reset,
	SONIC_BitMarch_Err_in_bitWalk
} ;
#ifndef __cplusplus
typedef enum SONIC_BitMarch_Error SONIC_BitMarch_Error ;
#endif __cplusplus


//
// SONIC_BitMarch parameter block.
//
struct SONIC_BitMarch_Params
{
	SONIC_Registers_Union *Sonic ;	// ptr to the start of the Sonic register union, ie sonic base address
	int align_flag ;		// indicates 16/32 bit alignment, 0 for 16 bit, 1 for 32 bit
	int debug_mode ;		// If non-zero, the subtest will jump to Macsbug at start of test
} ;
#ifndef __cplusplus
typedef struct SONIC_BitMarch_Params SONIC_BitMarch_Params ;
#endif __cplusplus


//
// SONIC_BitMarch result block.
//
struct SONIC_BitMarch_Results
{
	int Silicon_Rev ;			// Silicon Revision of the Sonic under test
	int Reg_under_test;			// Number of register under test
	BitWalk16_PB	bitWalk16Params;	// Bit Walk parameter block
	BitWalk16_RB	bitWalk16Results;	// Bit Walk result block
} ;
#ifndef __cplusplus
typedef struct SONIC_BitMarch_Results SONIC_BitMarch_Results ;
#endif __cplusplus


// Function prototype for the Subtest.
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern Subtest SONIC_BitMarch ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _SONIC_BitMarch_