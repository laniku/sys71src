/*
	File:		PPCNbp.c


	Written by:	Sangam

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 9/30/91	DTY		first checked in
		 <5>	11/28/90	EMT		<VC> Apply DMFix.
		 <4>	10/11/90	EMT		fix hardwire of values in RemoveName, and added prototypes.
		 <3>	 3/21/90	S		To GetTime Out Values from Configuration.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

	To Do:
*/

/*EASE$$$ READ ONLY COPY of file ÒPPCNbp.cÓ
** 1.0	CVC 09/18/1989 Adding PPC toolbox for the first time.
** END EASE MODIFICATION HISTORY */
/*
	
	© 1989-1990 by Apple Computer, Inc.  All rights reserved.
	
	File: PPCNbp.c Ð NBPRelated Calls
	
Revision History:
When   		Who      	What
----   		---         ----
05/30/89 	Sangam	    New Today
07/20/89    Sangam      1.0d2 release today!
07/25/89    Sangam      Added RemoveName function


*/

#include "PPCCommon.h"

OSErr RegisterName(unsigned char *objName,
				   unsigned char *objType,
				   unsigned char *zone,
				   unsigned char socket,
				   Boolean       async,
				   ProcPtr       compRoutine,
				   Ptr           ntePtr,
				   NBPparms      *nbpPB)
{
	PPCGlobalParamsPtr   ppcglobPtr;
	
	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	NBPSetNTE(ntePtr, (Str32)objName, (Str32)objType, (Str32)zone, socket);
	
	nbpPB->ioCompletion = compRoutine;
	nbpPB->interval = ppcglobPtr->configData.nbpTimeout;  
	nbpPB->count    = ppcglobPtr->configData.nbpRetries;  

	nbpPB->NBPPtrs.ntQElPtr = ntePtr;
	nbpPB->parm.verifyFlag = true; // For Now
	
	return DMFix(PRegisterName((MPPPBPtr)nbpPB, async),nbpPB);
	
} // RegisterName 

OSErr LookupName(EntityName     *name,
				 Boolean        async,
				 ProcPtr        compRoutine,
				 unsigned char  *bufPtr,
				 short          bufSize,
				 NBPparms       *nbpPB)
{
	PPCGlobalParamsPtr   ppcglobPtr;
	
	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();

	nbpPB->ioCompletion = compRoutine;
	nbpPB->interval = ppcglobPtr->configData.nbpTimeout;  
	nbpPB->count    = ppcglobPtr->configData.nbpRetries;  

	nbpPB->NBPPtrs.entityPtr = (char *)name;
	nbpPB->parm.Lookup.retBuffPtr = bufPtr;
	nbpPB->parm.Lookup.retBuffSize = bufSize;
	nbpPB->parm.Lookup.maxToGet = 1;
	return DMFix(PLookupName((MPPPBPtr)nbpPB, async),nbpPB);
} //LookupName


OSErr RemoveName(EntityName *name,
				 Boolean	async,
				 ProcPtr 	compRoutine,
				 NBPparms	*nbpPB)
{
	nbpPB->ioCompletion = compRoutine;
	nbpPB->NBPPtrs.entityPtr = (char *)name;
	return DMFix(PRemoveName((MPPPBPtr)nbpPB, async),nbpPB);
}
