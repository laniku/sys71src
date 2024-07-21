/*
	File:		ROMFastTraps.h

	Contains:	Routines to make traps in ROM call directly.

	Written by:	Chas. Spillar

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 3/31/93	IH		Make the ROMFastTraps use true/false (as set by the FeaturesSet
									make scripts) not defined/undefined to determine whether to use
									fast traps. All builds were using fast traps because the #define
									was always defined.
		 <SM2>	11/4/92		CSS		Fixed so __GenToolboxTrapCode ands the trap
		 							word with 3FF to get the trap number rather
									than FF.
		 <SM1>	10/22/92	CSS		First checked in.

	Note:
	Don't forget to turn on the flag ROMFastTraps in StandardEqu.a so that the correct
	code is compiled when StandardEqu.d is built.  This is currently required in ROMObj.make
	and in the Build script.
	
	To Do:
*/


#ifndef	__ROMFastTrapsIncluded__
#define	__ROMFastTrapsIncluded__

#if	ROMFastTraps
	#define	__GenToolboxTrapCode(Trap)	0x4EB0,0x81E1,0xE00+(0x3FF&Trap)*4
//still need to handle autopop in __GenToolboxTrapCode
	#define	__GenOSTrapCode(Trap)		0x48E7,((Trap&0x100)?0x6040:0x60C0),\
										0x323C,Trap,\
 										0x4EB0,0x81E1,(0x400+(Trap&0xFF)*4),\
 										0x4CDF,((Trap&0x100)?0x0206:0x0306),\
 										0x4A40
#else
	#define	__GenToolboxTrapCode(Trap)	Trap
	#define	__GenOSTrapCode(Trap)		Trap
#endif

#endif