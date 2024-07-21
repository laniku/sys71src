/*
 	File:	GenericInterface.h
 
 	Written by:	Mark Appleman 
 
 	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.
 
 	Change History (most recent first):
 
	   <SM2>	  5/2/92	kc		Roll in Horror. Comments follow:
		<H2>	  3/6/92	AL		Upgraded to CTE v2.1 (copied over from XXTest project).
 		   
 */
#ifndef _GenericInterface_
#define _GenericInterface_
//
//	GenericInterface.h
//

#include "CTETypes.h"
#include "ExecuteDTM.h"
#include <Files.h>



int GI_InitInterface(void *globs, long size) ;
int GI_ExecuteDTM(CTEInfo *kernelInfo, 
		CTEDTMExecutionOptions *executionOptions,
		CTETestInfo *testInfo, 
		CTESubtestInfo *subtestInfo, 
		CTEDTMExecutionResults *executionResults) ;

// Generic Interface functions that manage the CTE Workspace.
void *GI_AllocPermMem(CTEGlobals *globs, int size) ;
void *GI_AllocTempMem(CTEGlobals *globs, int size) ;
void GI_FreeTempMem(CTEGlobals *globs) ;

// Generic Interface functions that allow access the the CTE globals.
NumVersion *GI_GetVersion(CTEGlobals *globs) ;
char *GI_GetCommentary(CTEGlobals *globs) ;

CTEDTMExecutionOptions GI_GetDefaultExecutionOptions(void) ;

#endif _GenericInterface_