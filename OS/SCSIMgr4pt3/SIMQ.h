/*
	File:		SIMQ.h

	Contains:	header stuff for the core of the Apple SIM layer

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SMG2>	 9/29/93	chp		Include some prerequisite headers if necessary.
	   <SM9>	10/14/93	pdw		<MC> roll-in.
	   <SM8>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM7>	 3/20/93	PW		rolled in Ludwig changes.
	   <LW2>	  3/1/93	DCB		Added an ID parameter to the ResetQ function so that it could be
									used for ResetDevice as well as ResetBus.
	   <SM5>	11/20/92	DCB		Removed include files to solve makefile dependency problems
	   <SM4>	 10/8/92	PW		Changed minor prototype details.
	   <SM3>	 9/11/92	DCB		Added queue support for the (singular) ResetDevice Parameter
									block.
	   <SM2>	 8/31/92	DCB		Added some function prototypes.

*/

#ifndef __SIMQ__
#define __SIMQ__

#ifndef __SIMCOREPRIV__
#include "SIMCorePriv.h"
#endif


/******** Function Prototypes ********/

SIM_IO *	GetNextReadyIO( SIMglobals * SIMg);
void		ResetQueues( SIMglobals * SIMg, uchar ID); 				// <LW2>
void		EnQIO( SIM_IO *ioPtr, SIMglobals * SIMg);
void		DeQIO( SIM_IO *ioPtr, SIMglobals * SIMg);
SIM_IO *	FindIO( SIM_IO * ioPtr, SIMglobals * SIMg);				// <SM2>
SIM_IO *	FindIOFromID( uchar TargetID, SIMglobals * SIMg);		// <SM3>
void		SwitchQ( SIM_IO * ioPtr, QHdrPtr newQ );				// <SM2>


#endif __SIMQ__
