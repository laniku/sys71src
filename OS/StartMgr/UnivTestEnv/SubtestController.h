/*
				File:		SubtestController.h
			
				Contains:	This is the include file for the subtest controller section
							of the Common Test Environment.
			
				Written by:	Mark Appleman
			
				Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.
			
				Change History (most recent first):
			
		 <1>	  9/4/90	SS		first checked in

		 		To Do:
*/
#ifndef _SubtestController_
#define _SubtestController_

#include "CTETypes.h"
#include "List.h"
#include "Heap.h"

#define SUBTEST_NAME_SIZE	40

struct SubtestNode
{
	Node node ;
	Subtest *subtestPtr ;
	int subtestSize ;
	int pbSize ;
	int rbSize ;
	char *name ;
} ;
#ifndef __cplusplus
typedef struct SubtestNode SubtestNode ;
#endif __cplusplus

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

SubtestNode *InstallSubtest(CTEGlobals *globs, SubtestID id, Subtest *theSubtest,
					int codeSize, char *name, int pbSize, int rbSize) ;
SubtestNode *FindSubtest(CTEGlobals *globs, SubtestID id) ;
SubtestErr DoSubtest(CTEGlobals *globs) ;

#ifdef __cplusplus
}	// close the extern "C" declaration
#endif __cplusplus

#endif _SubtestController_
