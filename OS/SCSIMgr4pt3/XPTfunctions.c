/*
	File:		XPTfunctions.c

	Contains:	routines that implement the SCSI Action functions that are handled
				by the XPT layer

	Entry points:
	
	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM5>	10/14/93	pdw		<MC> roll-in.
	   <SM4>	 6/29/93	pdw		Made it use DBRAs!
	   <SM3>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM2>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).

*/

#include <Types.h>
#include <Memory.h>
#include "ACAM.h"
#include "XPT.h"


/*********************************************************************************
	SCSI_RegisterAsyncEvent 	-	Register a callback for an async event
*********************************************************************************/


/*********************************************************************************
	Clear 	-	clear a range of memory
*********************************************************************************/

void
Clear( char * where, short len)
{
	for (len-=1; len>=0; --len) 
		*where++ = 0;
}
