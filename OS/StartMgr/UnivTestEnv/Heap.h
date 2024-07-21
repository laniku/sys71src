/*
				File:		Heap.h
			
				Contains:	This is the include file for the heap controller 
							of the Common Test Environment.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
 		   
 */
#ifndef _Heap_
#define _Heap_
//
//	Heap.h
//

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

extern void *InitHeap(CTEGlobals *globs, void *baseAddr, long size) ;
extern void *AllocPermMem(CTEGlobals *globs, int size) ;
extern void *AllocTempMem(CTEGlobals *globs, int size) ;
extern void FreeTempMem(CTEGlobals *globs) ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _Heap_