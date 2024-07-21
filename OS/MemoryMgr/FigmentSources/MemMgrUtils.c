/*
	File:		MemMgrUtils.c  (used to be Utilities.c)

	Contains:	Memory Manager Utilities

	Written by:	Jeff Crawford

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <8>	  8/5/93	BT		<BT, JC> We came, we saw, we initialed...
		 <7>	 7/19/93	BT		Radar #1100608. Move MemMgr.h after MemMgrDebug.h includes area.
									This allows internal_debugging to be dfined in here and MemMgr.h
									will catch it.
		 <6>	  6/2/93	JC		Conditionalized out MoveBytes routine for all compiles but
									linked_thinkc_app.
		 <5>	 5/24/93	JC		Changed XXX to DbgXXX for all debug routines.
		 <4>	 5/19/93	JC		Began changes as requested by the code review.
		 <3>	 4/21/93	BT		<ewa> Fix capitalization of includes
		 <1>	 6/10/92	JC		New Today

*/

#ifndef THINK_C
	#ifdef StarTrek
		#include <MacTypes.h>
		#include <MacMem.h>
	#else
		#include <Types.h>
		#include <Memory.h>
	#endif
#endif

#ifdef StarTrek
	#include "MemDebug.h"
	#include "MemMgr.h"
	#include "MemRout.h"
#else
	#include "MemMgrDebug.h"
	#include "MemMgr.h"
	#include "MemoryRoutines.h"
#endif

#ifdef patchedIn
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef THINK_C
	/* This will overcome the 32k limit */
	#pragma segment Figment
#endif

#ifdef linked_thinkc_app
void MOVEBYTES(const void* theSource, void* theDestination, ulong length)
	{
	ulong*		source = (ulong*) theSource;
	ulong*		dest = (ulong*) theDestination;
	ulong		fragCount;			/*	serves as both a length and quadlong count
									for the beginning and main fragment */
	
	DbgCheckSize(length);
	
	/* Decide whether to copy while incrementing or copy while decrementing */
	if (source > dest)
		{
		/* copy bytes by incrementing pointers (ie. move bytes down). */
		
		/* fix up beginning to get us on a 64 byte boundary */
		if (fragCount = (length & (64-1)))
			{
			length -= fragCount; 		/* subtract fragment from length now */
			#ifdef quadLongWordAligned
				fragCount >>= 4; 			/* divide by 16 to get a count, for loop */
			#else
				fragCount >>= 2; 			/* divide by 4 to get a count, for loop */
			#endif
			do
				{
				#ifdef quadLongWordAligned
					/* move 16 bytes */
					*dest++ = *source++; *dest++ = *source++; *dest++ = *source++; *dest++ = *source++; 
				#else
					/* move 4 bytes */
					*dest++ = *source++;
				#endif
				}
			while (--fragCount);
			}
	
		/* Are we finished yet? */	
		if (!length)
			return;
	
		IfDbgMsg(length & (64-1), "misaligned size", length);
		
		/* Time to turn on the fire hose */
		length >>= 6;		/* divide by 64 to get count */
		do	
			{
			/* spray 64 bytes at a time */
			*dest++ = *source++; *dest++ = *source++; *dest++ = *source++; *dest++ = *source++; 
			*dest++ = *source++; *dest++ = *source++; *dest++ = *source++; *dest++ = *source++; 
			*dest++ = *source++; *dest++ = *source++; *dest++ = *source++; *dest++ = *source++; 
			*dest++ = *source++; *dest++ = *source++; *dest++ = *source++; *dest++ = *source++; 
			}
		while (--length);
		}
	else
		{
		/* move bytes by decrementing pointers (ie. move bytes up) */
		
		/* fix pointer to point to the top of there regions */
		source = (ulong*) ((char*)source + length);
		dest = (ulong*) ((char*)dest + length);
		
		/* fix up beginning to get us on a 64 byte boundary */
		if (fragCount = (length & (64-1)))
			{
			length -= fragCount; 		/* subtract fragment from length now */
			#ifdef quadLongWordAligned
				fragCount >>= 4; 			/* divide by 16 to get a count, for loop */
			#else
				fragCount >>= 2; 			/* divide by 4 to get a count, for loop */
			#endif
			do
				{
				#ifdef quadLongWordAligned
					/* move 16 bytes */
					*--dest = *--source; *--dest = *--source; *--dest = *--source; *--dest = *--source; 
				#else
					/* move 4 bytes */
					*--dest = *--source;
				#endif
				}
			while (--fragCount);
			}
	
		/* Are we finished yet? */	
		if (!length)
			return;
	
		IfDbgMsg(length & (64-1), "misaligned size", length);
		
		/* Time to turn on the fire hose */
		length >>= 6;		/* divide by 64 to get count */
		do
			{
			/* spray 64 bytes at a time */
			*--dest = *--source; *--dest = *--source; *--dest = *--source; *--dest = *--source; 
			*--dest = *--source; *--dest = *--source; *--dest = *--source; *--dest = *--source; 
			*--dest = *--source; *--dest = *--source; *--dest = *--source; *--dest = *--source; 
			*--dest = *--source; *--dest = *--source; *--dest = *--source; *--dest = *--source; 
			}
		while (--length);
		}
	}
#endif /* linked_thinkc_app */

/* same as FillBytes except that it works a (quad) long word boundaries. This should
	make Jim Reekes happy. */
void CLEARBYTES(void* block, ulong length)
	{
	ulong	fill = 0;
	ulong*	dataPtr = (ulong*) block;
	ulong	fragCount;			/*	serves as both a length and quadlong count
									for the beginning and main fragment */
	
	DbgCheckSize(length);
	
	/* fix up beginning to get us on a 64 byte boundary */
	if (fragCount = (length & (64-1)))
		{
		length -= fragCount; 		/* subtract fragment from length now */
		#ifdef quadLongWordAligned
			fragCount >>= 4; 			/* divide by 16 to get a count, for DBRA loop */
		#else
			fragCount >>= 2; 			/* divide by 4 to get a count, for DBRA loop */
		#endif
		do
			{
			#ifdef quadLongWordAligned
				/* clear 16 bytes */
				*dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill;
			#else
				/* clear 4 bytes */
				*dataPtr++ = fill;
			#endif
			}
		while (--fragCount);
		}

	/* Are we finished yet? */	
	if (!length)
		return;

	IfDbgMsg(length & (64-1), "misaligned size", length);
	
	/* Time to turn on the fire hose */
	length >>= 6;		/* divide by 64 to get count */
	do
		{
		/* spray 64 bytes at a time */
		*dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill;
		*dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill;
		*dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill;
		*dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill; *dataPtr++ = fill;
		}
	while (--length);
	}


#define shiftBytesLong	2
/* This is a left over from Skia, might become debug code only. 
	this treats fill as long-aligned and also works for reverse byte order machines. */
void FillBytes(void* block, long length, long fill)
	{
	long *b = (long*) block;
	int	remnant;
	long byteMask =  (1 << shiftBytesLong) - 1;
	
	if( (long)b & byteMask )
	{
		long	fillData = fill;										/* this will work on all byte order machines */
		char	*ptrToFill = (char *)&fillData + ((long)b & byteMask);	/* the fill data is long-aligned */
		do 
			{
			*(char*)b = *ptrToFill++;
			b = (long*) ((char *)b + 1);
			if ( --length == 0 )
				return;
			}
		while( (long)b & byteMask );
	}
	remnant = length & byteMask;

	length >>= shiftBytesLong;
	if( length >= 8 ) {
		register long length8 = length >> 3;
		length &= 7;
		while( length8-- ) {
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
			*b++ = fill;
		}
	}
	
	while( --length >= 0 )
		*b++ = fill;
		
	if (remnant)
		{
		long	fillData = fill;						/* this will work on all byte order machines */
		char*	ptrToFill = (char*) &fillData;
		do
			{
			*(char *)b = *ptrToFill++;
			b = (long *)((char *)b + 1);
			}
		while (--remnant);
		}
	}


