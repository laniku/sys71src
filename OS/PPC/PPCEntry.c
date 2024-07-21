/*
	File:		PPCEntry.c

	Contains:	PPC Dispatcher of various calls

	Written by:	Sangam, Eric M. Trehus
	
	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<39>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<38>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<37>	 9/30/91	DTY		Dean’s in the dog house. The System build got derailed with that
									last change.
		<36>	 9/29/91	DTY		Conditionalize <33> through <35> out of CubeE.
		<35>	 6/26/91	EMT		Add support to kill PPCInform calls
		<34>	 6/10/91	EMT		Check for duplicate completion.
		<33>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<32>	  1/7/91	EMT		<VC> Fix bug that causes machine to hang in PPCStart and
									IPCListPorts, related to GetMyZone call.
		<31>	12/13/90	EMT		<JSM> Change calling conventions to support new glue, and Inline
									Async/Sync parameterless calls.
		<30>	11/28/90	EMT		<VC> Fix/Work around bug that prevents my completion routine
									from being called.
		<29>	 11/8/90	EMT		Change how PPCStart and IPCListports determine if the session is
									local or not. Because we can't assume that the zone name in our
									globals is correct.
		<28>	 11/6/90	EMT		Changing CheckLocName to not used IUEqualString where it is not
									needed
		<27>	10/30/90	EMT		Fix usage and bug in PPCCommonPBEntry, that would not call
									completion routine if an error occured because we weren't
									initialized or had no globals.
		<26>	10/19/90	JSM		<EMT> Break out PPCEntry() into separate routines for new
									dispatching scheme.
		<25>	10/18/90	EMT		Change userName to machineName where needed
		<24>	10/11/90	EMT		Remove #define DEBUG
		<23>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<22>	 9/16/90	EMT		Fix bug
		<21>	 9/15/90	EMT		Fix CheckLocName bug introduced.
		<20>	 9/14/90	EMT		Make changes to support only type specification in PPCOpen with
									location name.
		<19>	  9/5/90	EMT		Make this file C3.0 friendly
		<18>	  9/4/90	EMT		Eric's changes rolled in
		<17>	  8/6/90	S		Bug Fixes.
		<16>	 6/28/90	S		To Improve Dynamic allocation and fix other bugs.
		<15>	 4/24/90	S		To Un fix Jeff's code changes.
		<14>	 4/18/90	JSM		Add prototype for AvoidDuplicateCompletion, miscellaneous code
									size reductions.
		<13>	 4/10/90	S		To Support Network IPCList Port call when incomming sessions are
									prevented.
		<11>	  3/5/90	S		Don't Look for User &Group File at PPCOpen.
		<10>	 2/27/90	S		Don't allow BOTH for PPCOpen.
		 <9>	 2/13/90	S		Some Error Code Changes.
		 <8>	  2/7/90	S		Bug Fix with PPCOpen call.
		 <7>	  2/5/90	S		Included check to ignore duplicate check for locName for
									PPCOpen.
		 <6>	  2/5/90	S		Included Checking for netVisible Flag before making NBP
									registration.
		 <5>	 1/30/90	S		Bug Fixes
		<3+>	 1/12/90	S		Bug Fixes
		<2+>	  1/5/90	S		Some Error Codes
	   <1.3>	10/12/89	CVC		no change
	   <1.2>	10/12/89	CVC		Handling NoLocName in PortLocName
	   <1.1>	 9/25/89	ss		Support port types.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.
	   
	   Old Revision History:

		05/30/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		07/25/89	Sangam      Nbp name is concatenated strings for setuser nbp name
		08/01/89	Sangam		Fixed PPOpen for not registering name when ADSP is not there
		08/09/89    Sangam      Reverted back to unpacked format for location name
		10/09/89	Sangam      Handling NoLocName in PortLocName.
								Returning noUserRecErr if user & group file is not there
								but user wants authentication
		1/4/90      Sangam      Some bug fixes and return errorcode changes.
*/

#include "PPCCommon.h"
#include <Packages.h>

/*----------------------------------------------------------------------------------------
	Prototypes used only in this file.
----------------------------------------------------------------------------------------*/

STATIC Boolean PPCCommonPBEntry(void *PB, PPCGlobalParamsPtr *ppcglobPtrPtr);
STATIC OSErr PPCCommonPBExit(void *PB, PPCGlobalParamsPtr ppcglobPtr);
STATIC void NetOpenCompletion(void);					// <36>
STATIC void CallCompletionRoutine(PPCParamBlockPtr PB,OSErr ioResult);
STATIC Boolean LocNameTaken(LocationNamePtr locationName,PPCGlobalParamsPtr ppcglobPtr);
STATIC void BeginLocalOrRemote(PPCGlobalParamsPtr ppcglobPtr,PPCParamBlockPtr PB,void *portPtr);
STATIC void LocalOrNot(void);
STATIC void DoGetMyZone(XCallParam *xpb,Boolean async,ProcPtr compRtn,Str32	zoneName);

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCOpen call.
----------------------------------------------------------------------------------------*/
OSErr ppcOpen(PPCOpenPBPtr openPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
 	PPCPortEntryPtr		portPtr;						// <36>
	LocationNamePtr theLocName;
	
	if (PPCCommonPBEntry(openPB, &ppcglobPtr))			// do common entry code for parameter block based calls
	{
		openPB->csCode = PPCOpenCall;					// save command code
		openPB->nbpRegistered = false;
		openPB->portRefNum = 0;
		theLocName = openPB->locationName;
		if(openPB->resFlag)								// <36> Enforce resFlag == 0
		{												// <36>
			CompleteWithResult(openPB,badReqErr);		// <36>
			goto Done;									// <36>
		}												// <36>
	
		if (!ValidPortName(openPB->portName))			// <36> make sure the Port name looks good
		{												// <36>
			CompleteWithResult(openPB,badPortNameErr);	// <36>
			goto Done;									// <36>
		}
		
		if (CheckPortName(openPB->portName, ppcglobPtr))	// make sure the Port name is not already in use
		{
			CompleteWithResult(openPB,portNameExistsErr);
			goto Done;
		}
		
		if (openPB->serviceType != ppcServiceRealTime)	// make sure we support this serviceType
		{
			CompleteWithResult(openPB,badServiceMethodErr);
			goto Done;
		}
		if (openPB->networkVisible && openPB->locationName)
		{
			if (theLocName->locationKindSelector != ppcNBPTypeLocation)
			{
				CompleteWithResult(openPB,nameTypeErr);	// <36>
				goto Done;								// <36>
			}
			
			if (theLocName->u.nbpType[0] > 32 || theLocName->u.nbpType[0] == 0)
			{
				CompleteWithResult(openPB,badLocNameErr);
				goto Done;
			}

			if(LocNameTaken(openPB->locationName,ppcglobPtr))
			{
				CompleteWithResult(openPB,nbpDuplicate);
				goto Done;
			}
		}
		
		if (!(portPtr = GetPortTable(openPB, ppcglobPtr)))	// make sure this port exists
		{
			CompleteWithResult(openPB,noPortErr);
			goto Done;
		}
		
		if (portPtr->locationInfo)		// If client wants a location name with the port
		{
			if(ppcglobPtr->allowIncommingRequests)	// Are we allowing incomming IAC.
			{
				PortLocationTablePtr locInfo;
				
				locInfo = portPtr->locationInfo;
				RegisterName(ppcglobPtr->machineName,		// use our machine name
							 locInfo->typeStr, 				// use the type specified.
							 "\p*",							// always *
							 ppcglobPtr->adspSocket,		// socket to register name on
							 true,							// Call ASyncronously 
							 (ProcPtr)NetOpenCompletion,	// NBPCompletion routine
							 (Ptr)&locInfo->nteQEle,		// ntePtr
							 &locInfo->nbpPB);				// PB for NBP call
							 
			}
			else	// Port open, location name not registered.
			{
				portPtr->openPB = nil;		// This is important
				CompleteWithResult(openPB,noErr);
				goto Done;
			}
		}
		else	// Port open without a location name.
		{
			portPtr->openPB = nil;		// This is important
			CompleteWithResult(openPB,noErr);
			goto Done;
		}
	}
Done:
	return PPCCommonPBExit(openPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCStart call.
----------------------------------------------------------------------------------------*/
OSErr ppcStart(PPCStartPBPtr startPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	OSErr				result;
 	PPCPortEntryPtr		portPtr;
	
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(startPB, &ppcglobPtr))
	{
		startPB->csCode = PPCStartCall;								// save command code
		if (!ValidPortName(startPB->portName))
		{
			CompleteWithResult(startPB,badPortNameErr);
		}
		else if (startPB->serviceType != ppcServiceRealTime)
		{
			CompleteWithResult(startPB,badServiceMethodErr);
		}
		else if ((portPtr = PortRefNumtoPtr(startPB->portRefNum, ppcglobPtr)) == nil)
		{
			CompleteWithResult(startPB,noPortErr);		// <36>
		}
		else if (result = VerifyLocNameFormat(startPB->locationName))
		{
			CompleteWithResult(startPB,result);
		}
		else
			BeginLocalOrRemote(ppcglobPtr,(PPCParamBlockPtr)startPB,portPtr);
	}
	return  PPCCommonPBExit(startPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCInformCall.
----------------------------------------------------------------------------------------*/
OSErr ppcInform(PPCInformPBPtr informPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
 	PPCPortEntryPtr		portPtr;
	
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(informPB, &ppcglobPtr))
	{
		informPB->csCode = PPCInformCall;							// save command code
		if ((portPtr = PortRefNumtoPtr(informPB->portRefNum, ppcglobPtr)) == nil)
		{
			CompleteWithResult(informPB,noPortErr);
		}
#ifdef notDefined										// <36>
		else											// <36>
		if(portPtr->serviceType == StoreAndForward || portPtr->serviceType == Both) // <36>
		{												// <36>
		}												// <36>
#endif													// <36>
		else											// <36>
		{												// <36>
			SetPortInformQue(informPB, portPtr);		// <36> Wait for somthing.
		}												// <36>
	}
	return PPCCommonPBExit(informPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCAccept call.
----------------------------------------------------------------------------------------*/
OSErr ppcAccept(PPCAcceptPBPtr acceptPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	CommonSessionParams	*sessPtr;
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(acceptPB, &ppcglobPtr))
	{
		acceptPB->csCode = PPCAcceptCall;							// save command code
		if ((sessPtr = SessRefNumtoPtr(acceptPB->sessRefNum, ppcglobPtr)) == nil)
		{
			CompleteWithResult(acceptPB,noSessionErr);
		}
		else if (sessPtr->sessState != AwaitAcceptReq)
		{
			if (sessPtr->sessState == AwaitAbortComp)
				CompleteWithResult(acceptPB,noSessionErr);
			else
				CompleteWithResult(acceptPB,badReqErr);
		}
		else if (sessPtr->sessUse == locUse)
		{
			AcceptLocalSession(acceptPB, sessPtr,ppcglobPtr);
		}
		else if (sessPtr->sessUse == netUse)
		{
			AcceptNetworkSession(acceptPB,(NetIPCParamsPtr)sessPtr);
		}
		else
		{
			CompleteWithResult(acceptPB,paramErr);	// <36>
		}
	}
	
	return PPCCommonPBExit(acceptPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCReject call.
----------------------------------------------------------------------------------------*/
OSErr ppcReject(PPCRejectPBPtr rejectPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	CommonSessionParams	*sessPtr;

	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(rejectPB, &ppcglobPtr))
	{
		rejectPB->csCode = PPCRejectCall;			// save command code
		if ((sessPtr = SessRefNumtoPtr(rejectPB->sessRefNum, ppcglobPtr)) == nil)
		{
			CompleteWithResult(rejectPB,noSessionErr);
		}
		else if (sessPtr->sessState != AwaitAcceptReq)
		{
		   if (sessPtr->sessState == AwaitAbortComp)
				CompleteWithResult(rejectPB,noSessionErr);
		   else
				CompleteWithResult(rejectPB,badReqErr);
		}
		else if (sessPtr->sessUse == locUse)
		{
			RejectLocalSession(rejectPB, sessPtr, ppcglobPtr);
		}
		else if (sessPtr->sessUse == netUse)
		{
			RejectNetworkSession(rejectPB,(NetIPCParamsPtr)sessPtr);
		}
		else
		{
			CompleteWithResult(rejectPB,paramErr);	// <36>
		}
	}
	
	return PPCCommonPBExit(rejectPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCWrite call.
----------------------------------------------------------------------------------------*/
OSErr ppcWrite(PPCWritePBPtr writePB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	CommonSessionParams	*sessPtr;
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(writePB, &ppcglobPtr))
	{
		writePB->csCode = PPCWriteCall;				// save command code
		writePB->actualLength = 0;
		if ((sessPtr = SessRefNumtoPtr(writePB->sessRefNum,  ppcglobPtr)) == nil)
		{
			CompleteWithResult(writePB,noSessionErr);	// <36>
		}
		else if (sessPtr->sessState != DataXferState)
		{
		   if (sessPtr->sessState == AwaitAbortComp)
				CompleteWithResult(writePB,noSessionErr);
		   else
				CompleteWithResult(writePB,badReqErr);
		}
		else if (sessPtr->sessUse == locUse)
		{
			WriteLocalData( writePB, sessPtr, ppcglobPtr);
		}
		else if (sessPtr->sessUse == netUse)
		{
			WriteNetworkData(writePB,(NetIPCParamsPtr)sessPtr);
		}
		else										// <36>
		{											// <36>
			CompleteWithResult(writePB,paramErr);	// <36>
		}
	}
	return PPCCommonPBExit(writePB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCRead call.
----------------------------------------------------------------------------------------*/
OSErr ppcRead(PPCReadPBPtr readPB)
{
	PPCGlobalParamsPtr	ppcglobPtr;
	CommonSessionParams	*sessPtr;

	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(readPB, &ppcglobPtr))
	{
		readPB->csCode = PPCReadCall;				// save command code
		readPB->actualLength = 0;
		if ((sessPtr = SessRefNumtoPtr(readPB->sessRefNum, ppcglobPtr)) == nil)
		{
			CompleteWithResult(readPB,noSessionErr);	// <36>
		}
		else if (sessPtr->sessState != DataXferState)
		{

		   if (sessPtr->sessState == AwaitAbortComp)
				CompleteWithResult(readPB,noSessionErr);
		   else
				CompleteWithResult(readPB,badReqErr);
		}
		else if (sessPtr->sessUse == locUse)
		{
			ReadLocalData( readPB, sessPtr, ppcglobPtr);
		}
		else if (sessPtr->sessUse == netUse)
		{
			ReadNetworkData( readPB,(NetIPCParamsPtr)sessPtr);
		}
		else
		{
			CompleteWithResult(readPB,paramErr);
		}
	}
	
	return PPCCommonPBExit(readPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCEnd call.
----------------------------------------------------------------------------------------*/
OSErr ppcEnd(PPCEndPBPtr endPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	CommonSessionParams	*sessPtr;
	
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(endPB, &ppcglobPtr))
	{
		endPB->csCode = PPCEndCall;									// save command code
		if (sessPtr = SessRefNumtoPtr(endPB->sessRefNum, ppcglobPtr))
		{
			if (sessPtr->sessState == DataXferState)
			{
				if (sessPtr->sessUse == locUse)
				{
					sessPtr = DeleteSessByRefNum(endPB->sessRefNum, ppcglobPtr);
					EndLocalSession( endPB, sessPtr, ppcglobPtr);
				}
				else if (sessPtr->sessUse == netUse)
				{
					sessPtr = DeleteSessByRefNum(endPB->sessRefNum, ppcglobPtr);
					EndNetworkSession(endPB,(NetIPCParamsPtr) sessPtr);
				}
				else
				{
					CompleteWithResult(endPB,noSessionErr);
				}
			}
			else
			{
				CompleteWithResult(endPB,noSessionErr);
			}
		}
		else
		{
			CompleteWithResult(endPB,noSessionErr);
		}
	}
	
	return PPCCommonPBExit(endPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the PPCClose call.
----------------------------------------------------------------------------------------*/
OSErr ppcClose(PPCClosePBPtr closePB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
 	PPCPortEntryPtr		portPtr;
	
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(closePB, &ppcglobPtr))
	{
		closePB->csCode = PPCCloseCall;								// save command code
		if (portPtr = DeletePortByRefNum(closePB->portRefNum, ppcglobPtr))
		{
			ClosePortTable(closePB, portPtr, ppcglobPtr);
		}
		else
		{
			CompleteWithResult(closePB,noPortErr);
		}
	}
	
	return PPCCommonPBExit(closePB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	Main entry point to the IPCListPorts call.
----------------------------------------------------------------------------------------*/
OSErr ipcListPorts(IPCListPortsPBPtr listPB)
{
    PPCGlobalParamsPtr	ppcglobPtr;
	OSErr				result;
	
	
	// do common entry code for parameter block based calls
	if (PPCCommonPBEntry(listPB, &ppcglobPtr))
	{
		listPB->csCode = IPCListPortsCall;				// save command code
		if (!ValidPortName(listPB->portName))
		{

			CompleteWithResult(listPB,badPortNameErr);	// <36>
		}
		else if (result = VerifyLocNameFormat(listPB->locationName))
		{
			CompleteWithResult(listPB,result);
		}
		else
			BeginLocalOrRemote(ppcglobPtr,(PPCParamBlockPtr)listPB,NULL);
	}
	
	return PPCCommonPBExit(listPB, ppcglobPtr);
}

/*----------------------------------------------------------------------------------------
	PPCCommonPBEntry is called at the beginning of all parameter block based calls.  It returns true
	if PPC can even deal with PB calls right now.  We make sure we have globals, and that we are
	initialized first.  We then prepare ourself to process the request.
	
	WARNING:  This routine has strange calling conventions.  It depends upon register D1 having the
	the PPCToolBox trap word in register D1.  C
----------------------------------------------------------------------------------------*/
STATIC Boolean PPCCommonPBEntry(void *PB, PPCGlobalParamsPtr *ppcglobPtrPtr)
PPCParamBlockPtr PB;
{
	PPCGlobalParamsPtr	ppcglobPtr;
	PBWriteResPtr		res;							// <36>
	unsigned short		PPCTrap;

	PPCTrap = GetD1();
#ifdef DEBUG
	if(PPCTrap != 0xA0DD && PPCTrap != 0xA4DD)
		DebugStr("\pRegister D1 did not have our trap word");
#endif
	if(*ppcglobPtrPtr = ppcglobPtr = getGlobal())	// get globals
	{
		// save application's A5

		res = (PBWriteResPtr)(PB->startParam.Reserved);	// <36>
		res->ApplA5 = GetA5();							// <36>
		res->cmdMode = PPCTrap & 0x0400?true:false;		// <36>

		if (!ppcglobPtr->inited)
		{
			CompleteWithResult(PB,notInitErr);
			return(false);
		}
	
		// mark PB as busy
		PB->startParam.ioResult = 1;
	
		// increment nesting level
		++ppcglobPtr->inEntry;
	
		
		// replenish resources if call made synchronously
		if(!res->cmdMode)								// <36>
			Replenish(ppcglobPtr);
		
		return(true);	// We are prepared to process this request.
	}
	else	// No Globals, return false and let PPCCommonPBExit handle it.
	{
		return false;
	}
}
		
/*----------------------------------------------------------------------------------------
	PPCCommonPBExit is called at the end of all parameter block based calls.  Note if
	PPCCommonPBEntry returned false because we don't have globals, we will no this here
	since the ppcglobPtr will be NULL.  So we have to complete the request differently in
	this because CompleteWithResult depends upon globals being present.
----------------------------------------------------------------------------------------*/
STATIC OSErr PPCCommonPBExit(void *PB, PPCGlobalParamsPtr ppcglobPtr)
PPCParamBlockPtr PB;
{
	short result = PB->startParam.ioResult;
	
	if(ppcglobPtr)	// Should always be no zero, but one never knows!
	{
		if(ppcglobPtr->inEntry == 1)	// If at outermost Entry in stack frame
		{
			PPCParamBlockPtr tempPB;	// complete all pending calls.
			
			do
			{
				short p;
				
				p = spl(kNoInterrupts);	// Extremely Critical Code.
				if(!ppcglobPtr->CompletedPBQueue.qSize)	// if the queue is empty
				{
					--ppcglobPtr->inEntry;	// We will allow direct call of comp routines.
					spl(p);					// restore the interrupt level.
					break;					// Done with this loop.
				}
				else	// Somthing is in the queue!
				{
					spl(p);	// Restore interrupts to the way they were.
					tempPB = ServeQueue(&ppcglobPtr->CompletedPBQueue);	// Get user PB.
					CallCompletionRoutine(tempPB,tempPB->startParam.ioResult);	// Call comp routine
				}
			}
			while(true);	// Repeat until the queue is empty.

			if (!((PBWriteResPtr)(PB->startParam.Reserved))->cmdMode)	// <36> if Synchronous
			{
				while (PB->startParam.ioResult == 1);	// Wait for the call to complete.
				return PB->startParam.ioResult;
			}
		}
		else	// Not at top level.
			--ppcglobPtr->inEntry;	// Decrease our level indicator.
		
		// if call still processing, return noErr, else return result
		return(result == 1 ? noErr : result);
	}
	else
	{
		CallCompletionRoutine(PB,noGlobalsErr);
		return(noGlobalsErr);
	}
}

STATIC void NetOpenCompletion(void)
{
	PPCPortEntryPtr			portPtr;
	PortLocationTablePtr	locInfo;
	PPCOpenPBPtr			openPB;
	
	locInfo = GetA0();
	portPtr = locInfo->portPtr;
	openPB = (PPCOpenPBPtr)(portPtr->openPB); /* get back the openPB */
	
	if (locInfo->nbpPB.ioResult == noErr)
		portPtr->nbpRegistered = openPB->nbpRegistered = true; // we did register with nbp
	portPtr->openPB = nil; // This is important
	CompleteWithResult(openPB,noErr);
} // NetNBPCompletion

STATIC void CallCompletionRoutine(PPCParamBlockPtr PB,OSErr ioResult)
{
	PPCReservedPtr res = (PPCReservedPtr)(&(PB->startParam.Reserved[0]));
	
	if (res->cmdMode)  // if Asynchronous 
	{
		callCompletion(PB, ioResult); // Save AppA5 and call completion
	}
}

/*----------------------------------------------------------------------------------------
	CompleteWithResult prepares and completes the usage of the client's parameter block
	with the specified result code.  If we are not inEntry, then the call is complete
	immediatly, otherwise it is place on the CompletedPBQueue to be served later when the
	stack unwinds within PPCCommonPBExit.
----------------------------------------------------------------------------------------*/
OSErr CompleteWithResult(void *PB,OSErr Result)
PPCParamBlockPtr PB;
{
	PPCGlobalParamsPtr   	ppcglobPtr;

	PB->closeParam.ioResult = Result;
	ppcglobPtr = getGlobal();
	if(ppcglobPtr->inEntry)
	{
		EnQueue(PB,&ppcglobPtr->CompletedPBQueue);
	}
	else
		CallCompletionRoutine(PB,Result);
	return(Result);	// For callers convience!
}

/*----------------------------------------------------------------------------------------
	VerifyLocNameFormat is used to verify that a location name can be used to start a
	session.  It just checks the structure.
----------------------------------------------------------------------------------------*/
OSErr VerifyLocNameFormat(LocationNamePtr locName)
{
	if(locName)
	{
		if (locName->locationKindSelector == ppcNoLocation)
			return noErr; // NoLocation implies local.

		if (locName->locationKindSelector != ppcNBPLocation)
			return nameTypeErr; // we don't understand any other type
		
		if (locName->u.nbpEntity.objStr[0] > 32 || locName->u.nbpEntity.typeStr[0] > 32 ||
			locName->u.nbpEntity.zoneStr[0] > 32)
			return badLocNameErr;
		
		// NOTE: little known AppleTalk fact, a zero length zone string indicates this zone.
		// That is why I won't check for minimum length on the zone string here.
		if (locName->u.nbpEntity.objStr[0] == 0 || locName->u.nbpEntity.typeStr[0] == 0)
			return badLocNameErr;
		
	}
	return(noErr);
}

/*----------------------------------------------------------------------------------------
	LocationNameLocal Determines if the given location name exists on this machine.
----------------------------------------------------------------------------------------*/
Boolean LocationNameLocal(LocationNamePtr locName)
{
	PortLocationTablePtr locInfo;
	PPCGlobalParamsPtr ppcglobPtr;
	PPCPortEntryPtr  portPtr;					// <36>

	if(!locName)
		return(true);
	if (locName->locationKindSelector == ppcNoLocation)
 		return(true);

	ppcglobPtr = getGlobal();
	if(locName->u.nbpEntity.zoneStr[0] == 0 ||
	  (locName->u.nbpEntity.zoneStr[0] == 1 && locName->u.nbpEntity.zoneStr[1] == '*') ||
	  EqualString(locName->u.nbpEntity.zoneStr,ppcglobPtr->zoneName,false,true))
	{
		// At this point the zone is our zone, so we will check the object.
		if(EqualString(locName->u.nbpEntity.objStr,ppcglobPtr->machineName,false,true))
		{
			if(EqualString(locName->u.nbpEntity.typeStr, ppcglobPtr->configData.ppctoolboxName,false,true))
				return(true);
			else
			{
				short sr;
				
				sr = spl(kNoInterrupts);		// Make sure we don't have any problems.

				FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
				{
					if (locInfo = portPtr->locationInfo)
					{
						if (EqualString(locName->u.nbpEntity.typeStr, locInfo->typeStr,false,true))
						{
							spl(sr);
							return(true); 		// Name is locally registered already
						}
					}
				}
				spl(sr);
			}
		}
	}
NotLocal:
	return(false);
}

/*----------------------------------------------------------------------------------------
	LocNameTaken determines if the typeStr is currently in use in this machine for some
	port.
----------------------------------------------------------------------------------------*/
STATIC Boolean LocNameTaken(LocationNamePtr locationName,PPCGlobalParamsPtr ppcglobPtr)
{
	short sr;
	Boolean isTaken;
	PPCPortEntryPtr  portPtr;					// <36>

	isTaken = false;
	sr = spl(kNoInterrupts);

	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if(portPtr->locationInfo)
		{
			if(EqualString(locationName->u.nbpType,
						   portPtr->locationInfo->typeStr,
						   false,true))	/* case insensitive, diacritical sensitive */
			{
				isTaken = true;
				break;
			}
		}
	}
	spl(sr);
	return(isTaken);
}

/*----------------------------------------------------------------------------------------
	BeginLocalOrRemote begins a local or remote request for IPCListPorts or PPCStart.  It has a
	side effect of updating our global down-below with our current zone name, keeping it fresh.  NOTE
	there exists an interesting, but harmless race condition, worst case we perform a GetMyZone call
	and when it completes have nothing to processes, casue it was already taken care of.
----------------------------------------------------------------------------------------*/
STATIC void BeginLocalOrRemote(PPCGlobalParamsPtr ppcglobPtr,PPCParamBlockPtr PB,void *portPtr)
{
	short sr;
	
	PB->startParam.intUsePtr = portPtr;		// Remember this for later in case of PPCStart.
	EnQueue(PB,&ppcglobPtr->BeginLRQueue);
	sr = spl(kNoInterrupts);
	if(ppcglobPtr->BeginLRQueue.qSize == 1)	// Not currently performing a GetMyZone.
	{
		spl(sr);
		DoGetMyZone(&ppcglobPtr->xpb,		// Use this parameter block
					true,					// do this asyncrhonously
					(ProcPtr)LocalOrNot,	// Completion Routine.
					&ppcglobPtr->zoneName);	// here is where to put the zone name.
	}
	else
		spl(sr);
}


/*----------------------------------------------------------------------------------------
	LocalOrNot is chained from BeginLocalOrRemote.  It processes the list pending IPCListPorts
	and PPCStart requests by branching to the appropriate routine, or completing the request with
	an error if we don't support remote request.
----------------------------------------------------------------------------------------*/
STATIC void LocalOrNot(void)
{
	PPCGlobalParamsPtr ppcglobPtr;
	Boolean Local;
	PPCParamBlockPtr PB;
	
	ppcglobPtr = getGlobal();
	
	if(ppcglobPtr->xpb.ioResult)
		BlockMove("\p*",ppcglobPtr->zoneName,2);
		
	while(PB = ServeQueue(&ppcglobPtr->BeginLRQueue))	// Batch process the requests.
	{
		Local = LocationNameLocal(PB->startParam.locationName);
		if (!Local && !ppcglobPtr->canRemote)	// If its remote, and we can't, then
		{
			CompleteWithResult(PB,localOnlyErr);
			continue;
		}

		if(PB->startParam.csCode == PPCStartCall)
		{
			if(Local)
				StartLocalSession((PPCStartPBPtr)PB,(PPCPortEntryPtr)PB->startParam.intUsePtr, ppcglobPtr);
			else
				StartNetworkSession((PPCStartPBPtr)PB,(PPCPortEntryPtr)PB->startParam.intUsePtr, ppcglobPtr);
		}
		else	// Must be an IPCListPorts request
		{
			if(Local)
				ListLocalPorts((IPCListPortsPBPtr)PB, ppcglobPtr);
			else
				ListNetworkPorts((IPCListPortsPBPtr)PB, ppcglobPtr);
		}
	}
}

/*----------------------------------------------------------------------------------------
	DoGetMyZone performs the task of a GetMyZone call, its just a nice interface to perform such
	a boring task.
----------------------------------------------------------------------------------------*/
STATIC void DoGetMyZone(XCallParam *xpb,
						Boolean async,
						ProcPtr compRtn,
						Str32	zoneName)
{
	OSErr result;

	xpb->ioCompletion = compRtn;
	xpb->zipBuffPtr = (Ptr)zoneName;
	xpb->zipInfoField[0] = 0;
	xpb->zipInfoField[1] = 0;
	xpb->xppTimeout = 1;
	xpb->xppRetry = 3;
	if (getGlobal()->mppOpen)
	{
#ifdef JimFixedTheGlue
		result = DMFix(GetMyZone((XPPParmBlkPtr)xpb, async),xpb);
#else
		xpb->csCode = xCall;
		xpb->xppSubCode = zipGetMyZone;
		xpb->ioRefNum = xppRefNum;
		result = DMFix(PBControl((ParmBlkPtr)xpb, async),xpb);
#endif
	}
	else	// pretend we are .XPP for a moment.
	{
		BlockMove("\p*",zoneName,2);
		xpb->ioResult = noErr;
		FakeCompletion(xpb);
	}

}

/*----------------------------------------------------------------------------------------
	DMFix checks to see if the error code in a parameter block was returned
	by the Device Manager.  The Device Manger fails to call the completion routine specified in
	the parameter block.  So I will check for the known cases when this happens, and if its one of
	them, call the completion routine as if I were the device manager doing its job properly.
----------------------------------------------------------------------------------------*/
OSErr DMFix(OSErr Result,void *thePB)
MPPparms *thePB;
{
	
	if(Result == notOpenErr || Result == badUnitErr)
	{
		if(thePB->ioCompletion)	// Assume if completion routine specified, call is async.
		{
				FakeCompletion(thePB);	// Calls the completion routine with Device Manager calling conventions.
		}
	}
	return(Result);
}
