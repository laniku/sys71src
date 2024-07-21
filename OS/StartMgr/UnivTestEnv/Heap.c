/*
				File:		Heap.c
			
				Contains:	This file contains the heap controller functions
							of the Common Test Environment.  These functions allow
							the caller to allocate and de-allocate memory in the
							CTE global area.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
 		   
 */
//
//	Heap.c
//

#include "GenericTypes.h"
#include "CTETypes.h"
#include "Heap.h"
#include <String.h>

// Alignment macros (NOTE: n and size must be intergal types 
// and size must be a power of 2).
#define AlignUp(n, size)	(-(-n & ~(size - 1)))
#define AlignDown(n, size)	(n & ~(size - 1))

//
//	InitHeap() - Initialize the CTE heap.
//
void *InitHeap(CTEGlobals *globs, void *baseAddr, long size)
{	
	globs->heapPermPtr = globs->heapBottom = 
			(void *)AlignUp((long)baseAddr, sizeof(long)) ;
	globs->heapTempPtr = globs->heapTop = 
			(void *)AlignDown((long)baseAddr + size, sizeof(long)) ; ;
	
	return(globs->heapBottom) ;
}


void *AllocPermMem(CTEGlobals *globs, long size)
{
	BYTE *newPermPtr ;
	void *memPtr ;
	
	// Make size a multiple of a longword.
	size = AlignUp(size, sizeof(long)) ;
		
	newPermPtr = (BYTE *)globs->heapPermPtr + size ;
	
	if(newPermPtr > globs->heapTempPtr)
	{
		memPtr = NULL ;			// out of heap mem.
	}else{
		memPtr = globs->heapPermPtr ;
		globs->heapPermPtr = (void *)newPermPtr ;
	}
	
	return(memPtr) ;
}

void *AllocTempMem(CTEGlobals *globs, long size)
{
	BYTE *newTempPtr ;
	void *memPtr ;
	
	// Make size a multiple of a longword.
	size = AlignUp(size, sizeof(long)) ;
		
	newTempPtr = (BYTE *)globs->heapTempPtr - size ;
	
	if(newTempPtr < globs->heapPermPtr)
	{
		memPtr = NULL ;
	}else{
		globs->heapTempPtr = (void *)newTempPtr ;
		memPtr = globs->heapTempPtr ;
		//memset(memPtr, 0, size) ;
		{
			ULONG *longPtr = memPtr;
			
			// TERROR ALERT! HORROR ALERT! Link with StdClib.o if
			//	Carl Hewitt and/or Steve Christensen allows it so that
			//	the "shift" instruction can be removed.
			//	Aaron 2/2/92
			//long longCount = size / sizeof(ULONG) ;
			long longCount = size >> 2 ;
			
			
			while(longCount > 0)
			{
				*longPtr++ = 0 ;
				longCount-- ;
			}
		}
	}
	
	return(memPtr) ;
}

void FreeTempMem(CTEGlobals *globs)
{
	globs->heapTempPtr = globs->heapTop ;
}
