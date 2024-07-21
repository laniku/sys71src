/*
	File:		CUtils.h

	Contains:	header stuff for various C utility stuff

	Notes:		In-line assembly for atomic bit operations

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM7>	11/22/93	pdw		Added disassembly comment.
	  <SMG2>	 9/29/93	chp		Fix up header and standardize conditional inclusion.
	   <SM5>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	10/12/93	pdw		Added support for Synchronous data transfers, rewrote State
									Machine, message handling etc.
	   <SM4>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM3>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <SM2>	11/20/92	DCB		Removed include of types.h

*/

#ifndef __CUTILS__
#define __CUTILS__

#ifndef __TYPES__
#include <Types.h>
#endif


#pragma parameter __D0	bset(__D0,__A0)
Boolean					bset(unsigned short bitNum, unsigned char * byte) = {0x01d0,0x56c0}; 
																		//   bset   sne D0
#pragma parameter __D0	bclr(__D0,__A0)
Boolean					bclr(unsigned short bitNum, unsigned char * byte) = {0x0190,0x56c0}; 

#pragma parameter __D0	btst(__D0,__A0)
Boolean					btst(unsigned short bitNum, unsigned char * byte) = {0x0110,0x56c0}; 


#define btst32(bit,addr) ( btst( (bit)%8, ((char *)(addr))+32-((bit)/4)) )

#define MAX(a,b)	((a)>(b)?(a):(b))
#define MIN(a,b)	((a)<(b)?(a):(b))


#endif __CUTILS__
