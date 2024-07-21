/*
 	File:	OtherSupport.c
 
 	Written by:	Mark Appleman 
 
 	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.
 
 	Change History (most recent first):
 
		 <1>	 5/16/92	kc		first checked in
		 <1>	  3/6/92	AL		first checked in
 		   
 */
//
//	OtherSupport.c
//

#include "CTETypes.h"


//
// CTEDoIdle()
//
void CTEDoIdle(CTEInfo *info)
{
	void (*idleMethod)(void *idleMethodArg) = info->executionOptions->idleMethod ;
	
	if(idleMethod != NULL)
		(*idleMethod)(info->executionOptions->idleMethodArg) ;
}