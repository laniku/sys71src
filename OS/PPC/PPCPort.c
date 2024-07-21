/*
	File:		PPCPort.c

	Contains:	PPCPort Management Functions.

	Written by:	Sangam, Eric M. Trehus
	Copyright:	© 1990-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	  3/9/93	PN		Remove ReQueueInformPB,Insert, Push,InitQueue, TraverseQueue
									which is no longer used
		<27>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<26>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<25>	 9/29/91	DTY		Conditionalize <21> through <24> out of CubeE.
		<24>	 6/26/91	EMT		Add more range checking to ValidPortName
		<23>	 6/12/91	EMT		Stop attempting to keep track of the number of pending messages.
		<22>	 6/10/91	EMT		Optimize code for size, Combined WildPortMatch and
									ComparePortName into 1 procedure, while fixing bugs in both of
									these procedures.
		<21>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<20>	 1/11/91	EMT		<VC> Fix bug in GetPortNames.
		<19>	 11/8/90	EMT		<stb>Continue working on the IPCListPorts fix
		<18>	 11/6/90	EMT		Begin work on fixing IPCListPorts, change not yet in place, but
									needed to check in file
		<17>	10/30/90	EMT		Fix GetPortTable
		<16>	10/18/90	EMT		Change userName to machineName where needed
		<15>	10/11/90	EMT		Make changes to obsole CompletionGlue.a
		<14>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<13>	 9/15/90	EMT		make reserved byte in portInfo always 0.
		<12>	  9/5/90	EMT		Make this file C3.0 Friendly
	   <10+>	  9/4/90	EMT		Roll in Eric's changes
		<10>	 7/10/90	dba		fix C warnings
		 <9>	 6/28/90	S		To Improve dynamic allocation scheme for the ports.
		 <8>	 3/20/90	S		Bug Fix in GetPortNames Call.
		 <7>	 2/28/90	S		To support Guest Selection in GetPortNames.
		 <6>	 2/27/90	S		To Make authRequest nonOptional.
		 <5>	 1/24/90	S		Fix Some Comments.
		<4>	     1/24/90	S		Fix Bug in WildPortMatch function & returning
		 							authRequired false for local ipclistport calls.
		<2+>	 1/5/90	Sangam		Some Error Code Changes

	   Old Revision History:

		05/31/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		07/25/89	Sangam      Changed FreePortTable and added ClosePortCompletion
		08/25/89    Sangam      Chganged GetPortNames to new IPCListPorts
		09/19/89    Sangam      Started changing to new PortName interface
								Added ValidPortName and CopyPortName routines
		09/27/89	Sangam		Copying script code in CopyPortName
		1/4/90      Sangam      Some Bug Fixes

*/

#include "PPCCommon.h"
#include <String.h>

/*----------------------------------------------------------------------------------------
	Prototypes used in this file only!
----------------------------------------------------------------------------------------*/

STATIC void NBPRemoveCompletion(void);
STATIC Boolean WildPortMatch(PPCPortPtr name1,PPCPortPtr name2);


OSErr ClosePortTable(PPCClosePBPtr	closePB,
					PPCPortEntryPtr		portPtr,
					PPCGlobalParamsPtr	ppcglobPtr)
{
	Boolean freePortTable;
	PPCInformPBPtr informPB;
	
	freePortTable = true;
	portPtr->openPB = (Ptr)closePB;	// Keep for later.

	while (informPB = ServeQueue(&portPtr->informPBQueue))
		CompleteWithResult(informPB,portClosedErr);

	#ifdef IPMIncluded
	if(portPtr->PortQueueRef)
	{
		freePortTable = false;
		
	}
	#endif
	
	if (portPtr->nbpRegistered) // PortName was registered with nbp
	{
		PortLocationTablePtr locInfo;
		
		freePortTable = false;
		locInfo = portPtr->locationInfo;
		RemoveName((EntityName *)&locInfo->nteQEle.nt.entityData,
				   true,
				   (ProcPtr)NBPRemoveCompletion,
				   &locInfo->nbpPB);
	}

	if (portPtr->sessCount)
	{
		freePortTable = false;
		CleanSessions(portPtr, ppcglobPtr);
	}
	
	if(freePortTable)
		CompleteClosePort(portPtr);
	return(noErr);
}

STATIC void NBPRemoveCompletion(void)
{
	PPCPortEntryPtr			portPtr;
    PortLocationTablePtr	locInfo;
	
	locInfo = GetA0();
	portPtr = locInfo->portPtr;
	portPtr->nbpRegistered = false;			// nolonger registered.
	CompleteClosePort(portPtr);
} // PortCloseCompletion 

/*---------------------------------------------------------------------------------------------------
	CompleteClosePort makes sure that the PPCClose operation has completed all outstanding
	PPCInform calls, Ended all sessions, and un-registered the NBP LocName.  With all
	these accomplished, the port table is freed and the closePB is completed with a
	result of noErr.
---------------------------------------------------------------------------------------------------*/

void CompleteClosePort(PPCPortEntryPtr portPtr)
{
	if(portPtr->nbpRegistered ||
	#ifdef IPMIncluded 
		portPtr->PortQueueRef ||
	#endif
		portPtr->sessCount ||
		portPtr->informPBQueue.qSize)
			return;	// Port not fully closed.
	else
	{
		PPCClosePBPtr closePB;
		
		if (closePB = (PPCClosePBPtr)portPtr->openPB)	// if there was a PPCClose call
		{
			portPtr->openPB = NULL;		// Prevention
			FreePortTable(portPtr);
			CompleteWithResult(closePB,noErr);
		}
	}
}

/*----------------------------------------------------------------------------------------
	CheckPortName returns the port that has the given port name.
----------------------------------------------------------------------------------------*/
PPCPortEntryPtr CheckPortName(PPCPortPtr portName,PPCGlobalParamsPtr ppcglobPtr)
{
	PPCPortEntryPtr portPtr;
		
	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if (ComparePortName(portName, (PPCPortPtr)(&portPtr->portName.nameScript)))
			return portPtr;
	}
	return(NULL);
}

/*----------------------------------------------------------------------------------------
	ValidPortName verifies the structure and portKindSelector for any detectable errors.
----------------------------------------------------------------------------------------*/
Boolean ValidPortName(PPCPortPtr name)
{
	if (name->portKindSelector == ppcByString || name->portKindSelector == ppcByCreatorAndType)
	{
		if (name->name[0] > 32)
			return false;
		if (name->portKindSelector == ppcByString)
		{
		   if (name->u.portTypeStr[0] > 32)
				return false;
		}
		return true;
	}
	return false;
} // ValidPortName

Boolean ComparePortName(PPCPortPtr name1,PPCPortPtr name2)
{
    unsigned char len;
	
	if (name1->nameScript != name2->nameScript)
		return false;
	if (name1->portKindSelector != name2->portKindSelector)
		return false;
	if (!(CompareByte(name1->name, name2->name, name1->name[0]+1)))
		return false;	
	if (name1->portKindSelector == ppcByCreatorAndType)
		len  = 8;
	else
		len = name1->u.portTypeStr[0]+1;
	return CompareByte(name1->u.portTypeStr, name2->u.portTypeStr, len);
	
} // ComparePortName

/*----------------------------------------------------------------------------------------
	Since a PPCPortEntry nolonger wastes space by keeping a locationName structure in
	tact, we have this routine that constructs one based on the given port.
----------------------------------------------------------------------------------------*/
void GetLocationName(PPCGlobalParamsPtr	ppcglobPtr,
					 PPCPortEntryPtr portPtr,
					 LocationNamePtr locationName)
{
	locationName->locationKindSelector = ppcNBPLocation;
	BlockMove(ppcglobPtr->machineName,&locationName->u.nbpEntity.objStr,sizeof(Str32));
	BlockMove(ppcglobPtr->zoneName,&locationName->u.nbpEntity.zoneStr,sizeof(Str32));
	if(portPtr->locationInfo)
		BlockMove(portPtr->locationInfo->typeStr,&locationName->u.nbpEntity.typeStr,sizeof(Str32));
	else
		BlockMove(ppcglobPtr->configData.ppctoolboxName,&locationName->u.nbpEntity.typeStr,sizeof(Str32));
}

/*----------------------------------------------------------------------------------------
	PortRefNumCompare compares the portRefNum passed in to the portRefNum in the port.
----------------------------------------------------------------------------------------*/
STATIC Boolean PortRefNumCompare(PPCPortEntryPtr portPtr,unsigned long portRefNum)
{
	return(portPtr->portRefNum == (PPCPortRefNum)portRefNum);
}

/*----------------------------------------------------------------------------------------
	DeletePortByRefNum removes and returns the port specified by the portRefNum parameter.
----------------------------------------------------------------------------------------*/
PPCPortEntryPtr DeletePortByRefNum(unsigned short portRefNum,PPCGlobalParamsPtr ppcglobPtr)
{
	return DeleteFromQueue(&ppcglobPtr->OpenPortQueue,(unsigned long)portRefNum,(SearchFuncPtr)PortRefNumCompare);
}

/*----------------------------------------------------------------------------------------
	PortRefNumtoPtr finds the port specified by its portRefNum parameter.
----------------------------------------------------------------------------------------*/
PPCPortEntryPtr PortRefNumtoPtr(unsigned short portRefNum,PPCGlobalParamsPtr ppcglobPtr)
{
	return SearchQueue(&ppcglobPtr->OpenPortQueue,(unsigned long)portRefNum,(SearchFuncPtr)PortRefNumCompare,1);
}

/*----------------------------------------------------------------------------------------
	GetUniquePortRefNum returns a portRefNum that is not in use
----------------------------------------------------------------------------------------*/
STATIC short GetUniquePortRefNum(PPCGlobalParamsPtr ppcglobPtr)
{
	PPCPortEntryPtr portPtr;
	short portRefNum;
	short p;
	
	p = spl(kNoInterrupts);
StartOver:	
	portRefNum = ppcglobPtr->nextPortRefNum++;
	if(!ppcglobPtr->nextPortRefNum)	// nextPortRefNum can't be 0.
		++ppcglobPtr->nextPortRefNum;	
	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if(portPtr->portRefNum == portRefNum)
			goto StartOver;	// Should rarely happen!
	}
	spl(p);
	return(portRefNum);
}

/*----------------------------------------------------------------------------------------
	GetPortTable puts together and initializes a port structure.  If the port has a
	location name associated with it, a PortLocationTable is linked with the port.  If
	the port supports store and forward, then a PortSFTable is linked with the port.
	NULL is returned if some strucute cannot be gotten that is required, and all
	associated memory is returned to the proper pools.
----------------------------------------------------------------------------------------*/

PPCPortEntryPtr GetPortTable(PPCOpenPBPtr openPB,PPCGlobalParamsPtr ppcglobPtr)
{
	PPCPortEntryPtr portPtr;
			
	if(portPtr = ServeQueue(&ppcglobPtr->freePortQueue))
	{
		PortLocationTablePtr locInfo;	// <25>

		memset(portPtr,0,sizeof(PPCPortEntry));
		openPB->portRefNum = portPtr->portRefNum = GetUniquePortRefNum(ppcglobPtr);
		CopyPortName((openPB->portName), &(portPtr->portName));
		portPtr->serviceType = openPB->serviceType;
		portPtr->authRequest = true; 	// no longer an option (openPB->authRequest;)
		portPtr->networkVisible = openPB->networkVisible;
		portPtr->serviceType = openPB->serviceType;
		portPtr->openPB = (Ptr)openPB;

		if(openPB->networkVisible && openPB->locationName)
		{
			if(portPtr->locationInfo = locInfo = ServeQueue(&ppcglobPtr->freeLocationQueue))
			{
				locInfo->portPtr = portPtr;
				BlockMove(openPB->locationName->u.nbpType,locInfo->typeStr,sizeof(Str32));
			}
			else	// Should not ever ever happen in a million billion years, but just in case!
			{
				FreePortTable(portPtr);
				return(NULL);
			}
		}
		EnQueue(portPtr,&ppcglobPtr->OpenPortQueue);	// Its open!
		return(portPtr);
	}
	return(NULL);
}

/*----------------------------------------------------------------------------------------
	FreePortTable frees a port and any linked structures.
----------------------------------------------------------------------------------------*/
void FreePortTable(PPCPortEntryPtr  portPtr)
{
	PPCGlobalParamsPtr   	ppcglobPtr;

	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	DeleteFromQueue(&ppcglobPtr->OpenPortQueue,(unsigned long)portPtr,PointerCompare);
	
	if(portPtr->locationInfo)
		EnQueue(portPtr->locationInfo,&ppcglobPtr->freeLocationQueue);
	EnQueue(portPtr,&ppcglobPtr->freePortQueue);
}

void SetPortInformQue(PPCInformPBPtr PB,PPCPortEntryPtr  portPtr)
{
	EnQueue(PB,&portPtr->informPBQueue);
}


/*----------------------------------------------------------------------------------------
	GetPortNames fills a buffer with PortInfo.  The result of this operation is true if
	all of the remaining would fit into the specified buffer.  False is returned if the
	reqCount+1 port is found.
----------------------------------------------------------------------------------------*/
Boolean GetPortNames(PPCGlobalParamsPtr	ppcglobPtr,
					 PPCPortPtr			name,
					 Boolean			local, 
					 Boolean			guestUnChecked,
					 unsigned short		index,
					 PortInfoPtr		buffPtr,
					 unsigned short		reqCount,
					 unsigned short		*actCount)
{
	PPCPortEntryPtr    portPtr;
	unsigned short     currentIndex = 0;
	unsigned long      offSet =0;

	
	*actCount = 0;
	if (!reqCount)
		return true;

	FOREACHELEMENT(portPtr,&ppcglobPtr->OpenPortQueue)
	{
		if 	(index != currentIndex)
		{
			if (local || portPtr->networkVisible)
			{
				if (WildPortMatch(name, &portPtr->portName))
					++currentIndex;
			}
		}
		else			
		{
			if (local || portPtr->networkVisible)
			{
				if (WildPortMatch(name, &portPtr->portName))
				{
					if (*actCount == reqCount)
						return false; 	// we don't have enough space in the buffer
			
					buffPtr->filler1 = 0;	// Reserved for future expansion.
					if (local || guestUnChecked)
						buffPtr->authRequired = false; // Local or Guest is Enabled in user&Groups
					else
						buffPtr->authRequired = true;  // 

					CopyPortName(&portPtr->portName, &buffPtr->name);
					buffPtr++; 
					++*actCount;
				}
			}
		}
	}
	return true;
} // GetPortNames

STATIC Boolean WildPortMatch(PPCPortPtr name1,PPCPortPtr name2)
{
	Boolean wildType = false;
	Boolean wildName = false;
	unsigned char len;
	
	if ((name1->name[0] == 1) && 
		(name1->name[1] == metaCharacter))
		wildName = true;
		
	if ((name1->u.portTypeStr[0] == 1) && 
	   (name1->u.portTypeStr[1] == metaCharacter))
		wildType = true;

	if (wildName && wildType)
		return true; // some one wants all the names
	
	if (!wildName)
	{
		if (!(wildName = CompareByte((Ptr)(name1->name),
						    (Ptr)(name2->name),
						     name1->name[0]+1)))
			return false; // Name Did not Match
		
	}
	
	if (!wildType)
	{
		if (name1->portKindSelector != name2->portKindSelector)
			return false;
		else
		{
			if (name1->portKindSelector == ppcByCreatorAndType)
				len = 8;
			else
				len = name1->u.portTypeStr[0]+1;
			if (!(wildType = CompareByte((Ptr)(name1->u.portTypeStr),
						    (Ptr)(name2->u.portTypeStr),
						     len)))
			   return false;
		}
	}
	if (wildName && wildType)
		return true; // Both Name and Type Match

} // WildPortMatch
