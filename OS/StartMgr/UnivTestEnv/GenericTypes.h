/*
				File:		GenericTypes.h
			
				Contains:	This file contains definitions of the generic data
							types used in the Common Test Environment.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
 		   
 */
#ifndef _GenericTypes_
#define _GenericTypes_
//
// GenericTypes.h
//

#include <Types.h>

typedef signed char 	BYTE ;
typedef unsigned char 	UBYTE ;
typedef signed short 	WORD ;
typedef unsigned short 	UWORD ;
typedef signed long 	LONG ;
typedef unsigned long 	ULONG ;

typedef int		Counter ;
typedef unsigned	UCounter ;
typedef short		ShortCounter ;
typedef unsigned short	UShortCounter ;
typedef BYTE		TinyCounter ;
typedef UBYTE		UTinyCounter ;

typedef int		Index ;
typedef unsigned	UIndex ;
typedef short		ShortIndex ;
typedef unsigned short	UShortIndex ;
typedef BYTE		TinyIndex ;
typedef UBYTE		UTinyIndex ;

//typedef signed short 	Integer ;
typedef Boolean		BOOLEAN ;

typedef signed short	FRACT16 ;
#define FRACT16EpsilonAsFloat		(0.000031)
#define UByteToFRACT16(theUByte)	(((theUByte) - 0x80 ) * 128)
#define FRACT16ToUByte(theFRACT16)	(((theFRACT16) / 128) + 0x80)
#define FloatToFRACT16(theFloat)	((FRACT16)((theFloat) * (float)(0x8000) + (FRACT16EpsilonAsFloat / 2)))
#define FRACT16ToFloat(theFRACT16)	((theFRACT16) / (float)(0x8000))

#define BitToMask(bitPosition)	(1 << bitPosition)

#endif _GenericTypes_