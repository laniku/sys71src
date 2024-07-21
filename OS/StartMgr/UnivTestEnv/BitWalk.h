/*
				File:		BitWalk.h
			
				Contains:	This file contains the data structures, etc., which are
							needed by the bitwalk routines.  These routines
							are available for use by subtests running in the CTE.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
		 <1>	 12/14/90	SS		first checked in
 		   
 */
#ifndef _BitWalk_
#define _BitWalk_
//
//	BitWalk.h
//

#include "GenericTypes.h"


//
//	BitWalk8 parameters and results.
//
typedef struct BitWalk8_PB
{
	UBYTE *bytePtr ;
	UBYTE dontWriteMask ;
	UBYTE doWriteBits ;
	UBYTE dontCareMask ;
	UBYTE initialPattern ;
	UBYTE finalValue ;
	BYTE pad[3] ;
	void (*writeMethod)(struct CTEGlobals *info, UBYTE *bytePtr, UBYTE writeValue) ;
	UBYTE (*readMethod)(struct CTEGlobals *info, UBYTE *bytePtr) ;
} BitWalk8_PB ;

typedef struct BitWalk8_RB
{
	UBYTE pattern ;
	UBYTE writeValue ;
	UBYTE readValue ;
	UBYTE failedBits ;
	UBYTE shiftCount ;
	BYTE phase ;
	BYTE pad[2] ;
} BitWalk8_RB ;


//
//	BitWalk16 parameters and results.
//
typedef struct BitWalk16_PB
{
	UWORD *wordPtr ;
	UWORD dontWriteMask ;
	UWORD doWriteBits ;
	UWORD dontCareMask ;
	UWORD initialPattern ;
	UWORD finalValue ;
	WORD pad[1] ;
	void (*writeMethod)(struct CTEGlobals *info, UWORD *wordPtr, UWORD writeValue) ;
	UWORD (*readMethod)(struct CTEGlobals *info, UWORD *wordPtr) ;
} BitWalk16_PB ;

typedef struct BitWalk16_RB
{
	UWORD pattern ;
	UWORD writeValue ;
	UWORD readValue ;
	UWORD failedBits ;
	BYTE phase ;
	BYTE pad[1] ;
	UWORD shiftCount ;
} BitWalk16_RB ;


//
//	BitWalk32 parameters and results.
//
typedef void BitWalk32WriteMethod(struct CTEGlobals *info, ULONG *longPtr, ULONG writeValue) ;
typedef ULONG BitWalk32ReadMethod(struct CTEGlobals *info, ULONG *longPtr) ;

typedef struct BitWalk32_PB
{
	ULONG *longPtr ;
	ULONG dontWriteMask ;
	ULONG doWriteBits ;
	ULONG dontCareMask ;
	ULONG initialPattern ;
	ULONG finalValue ;
	void (*writeMethod)(struct CTEGlobals *info, ULONG *longPtr, ULONG writeValue) ;
	ULONG (*readMethod)(struct CTEGlobals *info, ULONG *longPtr) ;
} BitWalk32_PB ;

typedef struct BitWalk32_RB
{
	ULONG pattern ;
	ULONG writeValue ;
	ULONG readValue ;
	ULONG failedBits ;
	BYTE phase ;
	BYTE pad[3] ;
	ULONG shiftCount ;
} BitWalk32_RB ;


//
// Function Prototypes.
//
#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern UBYTE BitWalk8(struct CTEGlobals *info, BitWalk8_PB *bw8Params, BitWalk8_RB *bw8results) ;
extern UWORD BitWalk16(struct CTEGlobals *info, BitWalk16_PB *bw16params, BitWalk16_RB *bw16results) ;
extern ULONG BitWalk32(struct CTEGlobals *info, BitWalk32_PB *bw32params, BitWalk32_RB *bw32results) ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus


#endif _BitWalk_