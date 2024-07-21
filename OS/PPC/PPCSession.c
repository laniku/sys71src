/*
	File:		PPCPort.c

	Contains:	PPCPort Management Functions.

	Written by:	Sangam
	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<12>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<11>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<10>	 9/29/91	DTY		Conditionalize out <9> for CubeE.
		 <9>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		 <8>	11/15/90	EMT		<stb> Fix priority 1 bug in KillReadAndWrite
		 <7>	 11/6/90	EMT		use STATIC in place of static for link maps
		 <6>	10/30/90	EMT		Seperate Read and Write PB's into their own queue's.
		 <5>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<10>	 7/10/90	dba		fix C warnings
		 <9>	 6/28/90	S		To Improve dynamic allocation scheme for the ports.
		 <8>	 3/20/90	S		Bug Fix in GetPortNames Call.
		 <7>	 2/28/90	S		To support Guest Selection in GetPortNames.
		 <6>	 2/27/90	S		To Make authRequest nonOptional.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

	   Old Revision History:

		06/05/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		08/17/89	Sangam		Fixed a bug in FreeSession Table
		09/22/89 	Sangam		Removed destportName and destlocname from session data structure
								Changed SetSessionTable accordingly
		09/25/89	sangam		Added support for 'more' in PPCWrite calls
		11/17/89    sangam      Fixed RemovePortSessionQ bug

*/

#include "PPCCommon.h"

STATIC QUEUE *QueueFromSessRefNum(unsigned long sessRefNum,PPCGlobalParamsPtr ppcglobPtr)
{
	QUEUE *SessionQueue;

	SessionQueue = NULL;				// <25>
	if(sessRefNum)
	{
		if ((sessRefNum & LocSessType) == LocSessType)
			SessionQueue = &ppcglobPtr->LocSessQueue; 
		
		else if ((sessRefNum & NetSessType) == NetSessType)
			SessionQueue = &ppcglobPtr->RemSessQueue; 
		
		else if ((sessRefNum & IpmSessType) == IpmSessType) 
			SessionQueue = &ppcglobPtr->IPMSessQueue; 
	}
	return(SessionQueue);
}

STATIC Boolean SessRefNumCompare(CommonSessionParamsPtr sessPtr,PPCSessRefNum sessRefNum)
{
	return(sessPtr->sessRefNum == sessRefNum);
}

CommonSessionParamsPtr SessRefNumtoPtr(PPCSessRefNum sessRefNum,PPCGlobalParamsPtr ppcglobPtr)
{
	QUEUE *SessionQueue;
	CommonSessionParamsPtr     sessPtr;
	
	sessPtr = NULL;
	if(SessionQueue = QueueFromSessRefNum(sessRefNum,ppcglobPtr))
		sessPtr = SearchQueue(SessionQueue,sessRefNum,(SearchFuncPtr)SessRefNumCompare,1);
	return(sessPtr);
}

CommonSessionParamsPtr DeleteSessByRefNum(PPCSessRefNum sessRefNum,PPCGlobalParamsPtr ppcglobPtr)
{
	QUEUE *SessionQueue;
	CommonSessionParamsPtr     sessPtr;
	
	sessPtr = NULL;
	if(SessionQueue = QueueFromSessRefNum(sessRefNum,ppcglobPtr))
		sessPtr = DeleteFromQueue(SessionQueue,sessRefNum,(SearchFuncPtr)SessRefNumCompare);
	return(sessPtr);
}

/*---------------------------------------------------------------------------------------------------
	GetSessionRefNum is responsible for returning a unique refnum for a given session kind.
---------------------------------------------------------------------------------------------------*/
unsigned long GetSessionRefNum(unsigned char sessUse,PPCGlobalParamsPtr ppcglobPtr)
{
	unsigned long sessRefNum;
	unsigned short saveint;

	saveint = spl(kNoInterrupts);
	sessRefNum = ppcglobPtr->nextSessRefNum;
	
	if (sessUse == locUse)
	    sessRefNum |= LocSessType;
	else if (sessUse == netUse)
		sessRefNum |= NetSessType;
	else
		sessRefNum |= IpmSessType;
	
	if (ppcglobPtr->nextSessRefNum == MaxSessRefNum)
		ppcglobPtr->nextSessRefNum =1;
	else
		ppcglobPtr->nextSessRefNum+=1;
	
	spl(saveint);
	return sessRefNum;
}

/*---------------------------------------------------------------------------------------------------
	SetSessionTable is responsible for initializing some of the common fields in a session header.
	This procedure also gets a unique Session refnum for the session.
---------------------------------------------------------------------------------------------------*/
void SetSessionTable(CommonSessionParamsPtr sessPtr,
					 PPCPortEntryPtr        portPtr,
					 PPCGlobalParamsPtr     ppcglobPtr)
{
	sessPtr->sessRefNum = GetSessionRefNum(sessPtr->sessUse, ppcglobPtr);
	sessPtr->conRef = 0;
	if(sessPtr->portEntry = portPtr)	// <25>
		++portPtr->sessCount;			// <25>
	sessPtr->endPB = nil;
	sessPtr->readMore = false;
	sessPtr->writeHdr = true;	
} // SetSessionTable


STATIC Boolean PortSessCompare(CommonSessionParamsPtr sessPtr,PPCPortEntryPtr portPtr)
{
	return(sessPtr->portEntry == portPtr);
}

/*---------------------------------------------------------------------------------------------------
	CleanSessions kills all sessions for a given port.
---------------------------------------------------------------------------------------------------*/
void CleanSessions(PPCPortEntryPtr portPtr,PPCGlobalParamsPtr ppcglobPtr)
{
	CommonSessionParamsPtr sessPtr;
	
	while(sessPtr = DeleteFromQueue(&ppcglobPtr->LocSessQueue,(unsigned long)portPtr,(SearchFuncPtr)PortSessCompare))
	{
		EndLocalSession(nil, sessPtr, ppcglobPtr);
	}
	while(sessPtr = DeleteFromQueue(&ppcglobPtr->RemSessQueue,(unsigned long)portPtr,(SearchFuncPtr)PortSessCompare))
	{
		EndNetworkSession(nil,(NetIPCParamsPtr) sessPtr);
	}
} // CleanSessions

/*---------------------------------------------------------------------------------------------------
	KillReadAndWrite completes all the outstanding read and write parameter blocks for this session
	with a sessClosedErr.
---------------------------------------------------------------------------------------------------*/
void KillReadAndWrite(void *sessPtr)
CommonSessionParamsPtr sessPtr;
{
	void *PB;
	if(sessPtr->readPB)
	{
		CompleteWithResult(sessPtr->readPB,sessClosedErr);
		sessPtr->readPB = NULL;
	}
		
	if(sessPtr->writePB)
	{
		CompleteWithResult(sessPtr->writePB,sessClosedErr);
		sessPtr->writePB = NULL;
	}

	while(PB = GetReadPB(sessPtr))
		CompleteWithResult(PB,sessClosedErr);

	while(PB = GetWritePB(sessPtr))
		CompleteWithResult(PB,sessClosedErr);
}
