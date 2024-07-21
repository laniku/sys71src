/*
	File:		PPCLocal.c

	Contains:	PPC Local Session Management Calls

	Written by:	Sangam

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<22>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<21>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<20>	 9/29/91	DTY		Conditionalize <17> thru <19> out of CubeE.
		<19>	 6/26/91	EMT		Add support to kill PPCStart calls
		<18>	 6/10/91	EMT		Optimize code for size
		<17>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<16>	 11/6/90	EMT		Fix warning
		<15>	10/30/90	EMT		Seperate Read and Write PB's into their own queue's.
		<14>	10/18/90	EMT		Fix functions to have prototype declarations
		<13>	10/11/90	EMT		add conditional around debug code
		<13>	10/11/90	EMT		add conditional around debug code
		<12>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<11>	  9/4/90	EMT		Roll in Eric's changes
		<10>	 6/28/90	S		To Improve Dynamic allocation of sessions.
		 <9>	 4/17/90	JSM		Add prototype for AvoidDuplicateCompletion, fix bug where
									AvoidDuplicateCompletion was being called with extra parameter.
		 <8>	 3/20/90	S		Bug Fix. Returning the wrong user name.
		 <7>	 2/27/90	S		ErrorCode Fix.
		 <6>	 2/20/90	S		Some ErrorCode Changes.
		 <5>	 2/13/90	S		Some Bug Fix.
		 <4>	  2/8/90	S		Minor Bug Fix.
		 <3>	 1/30/90	S		Bug Fixes.
	   <1.4>	10/12/89	CCH		Fixed header
	  <•1.3>	10/12/89	CVC		Added Access Control
	   <1.2>	 10/2/89	CVC		Fixed a big in PPCInform call.
	   <1.1>	 9/25/89	ss		Added Support for 'more' in PPCWrite calls.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

	   Old Revision History:

		06/05/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		08/10/89	Sangam		Made changes to accomadate new IPCListPorts call
		08/10/89	Sangam		Added userEntry filed for read/write headers
		09/08/89	Sangam		Changed the errorcode for PPCReject to rejectErr
		09/11/89	Sangam		Fixed the problem of completion not being called(some times)
								in accept and reject session functions.
		09/15/89	Sangam		Changed the errorcode to rejectErr (when inform is not outstanding)
		09/19/89    Sangam      Returning the Right port name portname at PPCInform Call to build special
								version for Jay.
		09/21/89	Sangam      Changed the interface to GetPortNames call
		09/22/89 	Sangam		Removed destportName and destlocname from session data structure
		09/25/89    Sangam		Added Support for 'more' in PPCWrite calls.
		01/04/90    Sangam      Bug fix for actualLength in read/write calls.

*/

#include "PPCCommon.h"
#include <String.h>

/*----------------------------------------------------------------------------------------
	Prototypes of functions used only in this file.
----------------------------------------------------------------------------------------*/
STATIC void LocalTransfer(CommonSessionParamsPtr writeSess,
				   CommonSessionParamsPtr readSess);

/*----------------------------------------------------------------------------------------
	GetLocSess returns the a new local session table.
----------------------------------------------------------------------------------------*/

STATIC LocalIPCParamsPtr GetLocSess(PPCGlobalParamsPtr ppcglobPtr)
{
	LocalIPCParamsPtr theSess;
	
	if(theSess = ServeQueue(&ppcglobPtr->freeLocSessQueue))
	{
		memset(theSess,0,sizeof(LocalIPCParams));
		theSess->sessUse = locUse;
		EnQueue(theSess,&ppcglobPtr->LocSessQueue);
	}
	return(theSess);
}

STATIC void FreeLocSess(LocalIPCParamsPtr sessPtr)
{
	PPCGlobalParamsPtr ppcglobPtr;
	PPCPortEntryPtr portPtr;

	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	portPtr = sessPtr->portEntry;
	DeleteFromQueue(&ppcglobPtr->LocSessQueue,(unsigned long)sessPtr,PointerCompare);
	if(portPtr)						// <20> if this session belongs to a port.
		--portPtr->sessCount;		// <20> update the port table.
	EnQueue(sessPtr,&ppcglobPtr->freeLocSessQueue);
}

void StartLocalSession(PPCStartPBPtr		startPB,
					   PPCPortEntryPtr		srcportPtr,
					   PPCGlobalParamsPtr	ppcglobPtr)
{
	PPCPortEntryPtr         destportPtr;
	CommonSessionParamsPtr  srcSess, destSess;
	PPCInformPBPtr      informPB;
	PBWriteResPtr           res;	// <20>
	unsigned short          i;		// <20>
	unsigned char           *temp;	// <20>

	res =(PBWriteResPtr)(startPB->Reserved);

	if (!(destportPtr = CheckPortName(startPB->portName, ppcglobPtr)))
	{
		CompleteWithResult(startPB,destPortErr);
		return;
	}

	if (!(informPB = ServeQueue(&destportPtr->informPBQueue)))
	{
		CompleteWithResult(startPB,noInformErr);
		return;
	}

	if (!(srcSess =(CommonSessionParamsPtr)GetLocSess(ppcglobPtr)))
	{
		SetPortInformQue(informPB, destportPtr); // Add the PB back
		CompleteWithResult(startPB,sessTableErr);
		return;
	}
	if (!(destSess = (CommonSessionParamsPtr)GetLocSess(ppcglobPtr)))
	{
		FreeLocSess((LocalIPCParamsPtr)srcSess);  /* Free the Source Session table */
		SetPortInformQue(informPB, destportPtr); // Add the PB back
CompleteStartPBWithResult:
		CompleteWithResult(startPB,sessTableErr);
		return;
	}
	
	SetSessionTable(srcSess, srcportPtr, ppcglobPtr);
	SetSessionTable(destSess, destportPtr, ppcglobPtr); 
	
	srcSess->conRef = destSess->sessRefNum;
	destSess->conRef = srcSess->sessRefNum;

	
	informPB->sessRefNum = destSess->sessRefNum;
	informPB->serviceType = ppcServiceRealTime;
	informPB->userData = startPB->userData;
	informPB->requestType = ppcLocalOrigin;
	if (informPB->portName)
		CopyPortName(&(srcportPtr->portName),informPB->portName);
	
	if (informPB->locationName)
	{
		temp = (unsigned char *)(informPB->locationName);
		for (i=0; i< sizeof(LocationNameRec); i++)
			*temp++ = '\0';
	}

	if (informPB->userName)

	   *informPB->userName = '\0'; 	// No User Name for local Session
	if (informPB->autoAccept)
	{
		srcSess->sessState = DataXferState;
	    destSess->sessState =  DataXferState;
		startPB->sessRefNum = srcSess->sessRefNum;
		srcSess->PBPtr = NULL;
		CompleteWithResult(informPB,noErr);
		CompleteWithResult(startPB,noErr);
		return;
	}
	else
	{
		srcSess->sessState = AwaitAcceptResp;
	    destSess->sessState =  AwaitAcceptReq;
		srcSess->PBPtr = startPB; 	// Remember the Start PB for this session.
		CompleteWithResult(informPB,noErr);
	}	
} // StartLocalSession

void AcceptLocalSession(PPCAcceptPBPtr acceptPB,
						CommonSessionParamsPtr destSess,
						PPCGlobalParamsPtr ppcglobPtr)
{
	CommonSessionParamsPtr srcSess;
	PPCStartPBPtr      startPB;
	
	if (!(srcSess = SessRefNumtoPtr(destSess->conRef, ppcglobPtr)))
	{
		FreeLocSess((LocalIPCParamsPtr)destSess);
		CompleteWithResult(acceptPB,noSessionErr);
		return;
	}

	srcSess->sessState =  DataXferState;
	destSess->sessState = DataXferState;
	startPB = srcSess->PBPtr;
	startPB->sessRefNum = srcSess->sessRefNum;
	srcSess->PBPtr = NULL;
	destSess->PBPtr = NULL;
	CompleteWithResult(startPB,noErr);
	CompleteWithResult(acceptPB,noErr);
} // AcceptLocalSession

void RejectLocalSession(PPCRejectPBPtr     rejectPB,
						CommonSessionParamsPtr destSess,
						PPCGlobalParamsPtr     ppcglobPtr)
{
	CommonSessionParamsPtr srcSess;
	PPCStartPBPtr      startPB;
	
	if (!(srcSess = SessRefNumtoPtr(destSess->conRef, ppcglobPtr)))
	{
		FreeLocSess((LocalIPCParamsPtr)destSess);
		CompleteWithResult(rejectPB,noSessionErr);
		return;
	}
	startPB = srcSess->PBPtr;
	FreeLocSess((LocalIPCParamsPtr)destSess);
	FreeLocSess((LocalIPCParamsPtr)srcSess);
	startPB->rejectInfo =  rejectPB->rejectInfo;
	CompleteWithResult(startPB,userRejectErr);
	CompleteWithResult(rejectPB, noErr);
}


void WriteLocalData(PPCWritePBPtr      	writePB,
					CommonSessionParamsPtr srcSess,
					PPCGlobalParamsPtr     ppcglobPtr)
{
	CommonSessionParamsPtr destSess;
	PBWriteResPtr          res;

	res = (PBWriteResPtr)(writePB->Reserved);
	res->curBufPos = writePB->bufferPtr;
	res->length = writePB->bufferLength;

	if (destSess = SessRefNumtoPtr(srcSess->conRef, ppcglobPtr))
	{
		AddWritePB(srcSess,writePB);
		if(!srcSess->writePB)		// if not currently writing then
		{
			srcSess->writePB = GetWritePB(srcSess);
			if(destSess->readPB)
				LocalTransfer(srcSess, destSess);
			
		}
	}
	else
		CompleteWithResult(writePB,noSessionErr);
} // WriteLocalData

void ReadLocalData(PPCReadPBPtr readPB,
				   CommonSessionParamsPtr destSess,
				   PPCGlobalParamsPtr ppcglobPtr)
{
	CommonSessionParamsPtr srcSess;
	PBWriteResPtr          res;

	res = (PBWriteResPtr)(readPB->Reserved);

	if (srcSess = SessRefNumtoPtr(destSess->conRef, ppcglobPtr))
	{
		AddReadPB(destSess,readPB);
		if(!destSess->readPB)
		{
			destSess->readPB = GetReadPB(destSess);
			if(srcSess->writePB)
				LocalTransfer(srcSess, destSess);
		}
	}
	else
		CompleteWithResult(readPB,noSessionErr);
} // ReadLocalData

void EndLocalSession(PPCEndPBPtr         endPB,
					 CommonSessionParamsPtr srcSess,
					 PPCGlobalParamsPtr     ppcglobPtr)
{
	CommonSessionParamsPtr     destSess;
	PPCPortEntryPtr            portPtr;

	
	portPtr = srcSess->portEntry;
	destSess = DeleteSessByRefNum(srcSess->conRef,ppcglobPtr);
	if (srcSess->sessState == AwaitAcceptResp)
	{
		if (destSess)
		{
			FreeLocSess((LocalIPCParamsPtr)destSess);
		}
		CompleteWithResult(srcSess->PBPtr, portClosedErr);
		FreeLocSess((LocalIPCParamsPtr)srcSess);
	}
	else if (srcSess->sessState == AwaitAcceptReq)
	{
		if (destSess)
		{
			CompleteWithResult(destSess->PBPtr,destPortErr);
			FreeLocSess((LocalIPCParamsPtr)destSess);
		}
		FreeLocSess((LocalIPCParamsPtr)srcSess);
	}
	else if (srcSess->sessState == DataXferState)
	{
		if (destSess)
		{
			KillReadAndWrite(destSess);
			FreeLocSess((LocalIPCParamsPtr)destSess);
		}
		KillReadAndWrite(srcSess);
		FreeLocSess((LocalIPCParamsPtr)srcSess);
	}
#ifdef DEBUG
	else
		DebugStr("\pSrcSession in unknown state, doesn't get freed");
#endif
	if (endPB)
		CompleteWithResult(endPB,noErr);
	else								// <20> Must be a PPCClose operation.
		CompleteClosePort(portPtr);		// <20>
} // EndLocalSession

void ListLocalPorts(IPCListPortsPBPtr listPB,PPCGlobalParamsPtr ppcglobPtr)
{
    GetPortNames(ppcglobPtr,listPB->portName,
				 true, // local
				 true, // guetstUnChecked
				 listPB->startIndex, 
				 (PortInfoPtr)listPB->bufferPtr,
				 listPB->requestCount, &(listPB->actualCount));
	CompleteWithResult(listPB,noErr);
} //ListLocalPorts 


STATIC void LocalTransfer(CommonSessionParamsPtr writeSess,
						  CommonSessionParamsPtr readSess)
{
	PPCWritePBPtr      writePB;
	PPCReadPBPtr       readPB;
	unsigned long xferLength;
	PBWriteResPtr res;
	unsigned char *dataPtr;
	
	while((writePB = writeSess->writePB) && (readPB = readSess->readPB))
	{
		res = (PBWriteResPtr)(writePB->Reserved);	
		if  (res->length > readPB->bufferLength -readPB->actualLength)
			xferLength = readPB->bufferLength - readPB->actualLength;
		else
			xferLength = res->length;	// <20>
		/* Copy the Data */
		dataPtr = (unsigned char *)(readPB->bufferPtr + readPB->actualLength);
		BlockMove((char *)res->curBufPos, dataPtr,xferLength);
		writePB->actualLength += xferLength;
		res->curBufPos+=xferLength;
		res->length-=xferLength;	

		readPB->blockCreator = writePB->blockCreator;
		readPB->blockType = writePB->blockType;
		readPB->userData = writePB->userData;
		readPB->actualLength = readPB->actualLength + xferLength;

		if (res->length)				// <20> If we have more to write for this request.
		{
			readPB->more = true;
		}
		else
		{
			readPB->more = writePB->more;
			CompleteWithResult(writePB,noErr);
			writeSess->writePB = GetWritePB(writeSess);
		}
		
		// if no more to read, or the read buffer is full then
		if (!readPB->more || (readPB->actualLength == readPB->bufferLength))	
		{
			CompleteWithResult(readPB,noErr);
			readSess->readPB = GetReadPB(readSess);
		}
	}
} // LocalTransfer