/*
	File:		EndianAware.h

	Contains:	macros for 68K clients that are aware of platform endian-ness

	Written by:	Craig Prouse

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 12/1/93	chp		Give inline functions external C linkage to make #pragma
									parameter work in C++ builds.
	   <SM1>	11/10/93	fau		first checked in

*/

#ifndef __ENDIANAWARE__
#define __ENDIANAWARE__

#ifndef littleEndian
#define littleEndian 1
#endif


#if littleEndian

#ifdef __cplusplus
extern "C" {
#endif

#pragma parameter __D0 EndianSwap16 (__D0)
unsigned short EndianSwap16 (unsigned short) =
{
	0xE158							//		ROL.W	#8,D0
};

#pragma parameter __D0 EndianSwap32 (__D0)
unsigned long EndianSwap32 (unsigned long) =
{
	0xE158,							//		ROL.W	#8,D0
	0x4840,							//		SWAP	D0
	0xE158							//		ROL.W	#8,D0
};

#ifdef __cplusplus
}
#endif

#else

#define EndianSwap16(a) (a)
#define EndianSwap32(a) (a)

#endif litteEndian

#endif __ENDIANAWARE__
