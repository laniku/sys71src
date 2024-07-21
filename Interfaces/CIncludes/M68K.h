/*
	File:		M68K.h

	Contains:	M680x0 macros and inline functions

	Written by:	Craig Prouse

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	11/10/93	fau		first checked in
	  <SMG2>	10/26/93	chp		Added an inline NOP function. This corresponds to a PowerPC
									EIEIO under 68K emulation.
		 <1>	 8/30/93	chp		first checked in

*/

#ifndef __M68K__
#define __M68K__


#ifdef m68k

//	WARNING: Items defined in this file are not portable. Inclusion of this file has no
//	effect unless compiling with the MPW 68K C compiler, which predefines the m68k flag.


typedef unsigned short StatusRegister;
typedef void *AddressRegister;


#pragma parameter __D0 GetA0
AddressRegister GetA0 (void) =
{
	0x2008							//		MOVE.L	A0,D0
};

#pragma parameter __D0 GetA1
AddressRegister GetA1 (void) =
{
	0x2009							//		MOVE.L	A1,D0
};

#pragma parameter __D0 DisableInterrupts
StatusRegister DisableInterrupts (void) =
{
	0x40C0,							//		MOVE	SR,D0
	0x007C, 0x0700					//		ORI		#$0700,SR
};

#pragma parameter RestoreStatusRegister (__D0)
void RestoreStatusRegister (StatusRegister) =
{
	0x46C0							//		MOVE	D0,SR
};

void NOP (void) =
{
	0x4E71							//		NOP
};


#endif m68k
#endif __M68K__
