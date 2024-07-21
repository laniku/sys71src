/*
				File:		68KOpCodes.h
			
				Contains:	This file contains C macros which compile into inline 680x0
							instructions.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
#ifndef _68KOpCodes_
#define _68KOpCodes_
//
//	68KOpCodes.h
//
//	If you have usefull inline C functions that emulate 680x0 instructions,
//	send them to Mark Appleman, (408)-974-5740 {x45740}, APPLEMAN.M, M/S 60-M.


#include "GenericTypes.h"

//
// NOP()
//
void NOP(void) =
{
	0x4e71				// nop
} ;

//
// BKPT_7()
//
void BKPT_7(void) =
{
	0x484f				// bkpt		#7
} ;


// For the following three inline functions, TST_B, TST_W, and TST_L,
//	the stack looks like this:
//	sp+0	--> addr

//
// TST_B()
//
void TST_B(void *addr) =
{
	0x2057,				// move.l	addr(sp),a0
	0x4a10				// tst.b	(a0)
} ;

//
// TST_W()
//
void TST_W(void *addr) =
{
	0x2057,				// move.l	addr(sp),a0
	0x4a50				// tst.w	(a0)
} ;

//
// TST_L()
//
void TST_L(void *addr) =
{
	0x2057,				// move.l	addr(sp),a0
	0x4a90				// tst.l	(a0)
} ;


// For the following three inline functions, ROL_B, ROL_W, and ROL_L,
//	the stack looks like this:
//	sp+0	--> theByte
//	sp+4	--> count

//
// ROL_B()
//
UBYTE ROL_B(UBYTE theByte, unsigned int count) =
{
	0x2017,				// move.l	theByte(sp),d0
	0x222f, 0x0004,			// move.l	count(sp),d1
	0xe338				// rol.b	d1,d0
} ;

//
// ROL_W()
//
UWORD ROL_W(UWORD theWord, unsigned int count) =
{
	0x2017,				// move.l	theByte(sp),d0
	0x222f, 0x0004,			// move.l	count(sp),d1
	0xe378				// rol.w	d1,d0
} ;

//
// ROL_L()
//
ULONG ROL_L(ULONG theLong, unsigned int count) =
{
	0x2017,				// move.l	theByte(sp),d0
	0x222f, 0x0004,			// move.l	count(sp),d1
	0xe3b8				// rol.l	d1,d0
} ;


//
// CPUSHL()
//
//	NOTE: This #pragma had to be redeclared under the old MPW C syntax, without the
//		__ for A0. The Horror ROM uses MPW 3.0 tools (not 3.2), so this needs
//		to be changed back if the ROM starts using 3.2 final (or later).
//
//		AARON	AARON	AARON
//
//#if "this is 3.0"

//static void CPUSHL(void *lineAddress) = 
//{
//	0x????	// Move.l	4(sp), a0
//	0xF4E8	// CPUSHL <dataCache>,(a0)									// instruction cache. -- Sean
//};


//#else

//				#pragma parameter CPUSHL(__A0)
static void CPUSHL(void *lineAddress) = 
{
	0xF4E8	// CPUSHL <dataCache>,(a0)									// instruction cache. -- Sean
};

//#endif

#endif _68KOpCodes_