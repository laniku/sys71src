/*
	File:		PPCNetwork.c

	Contains:	PPCNetwork related functions.

	Written by:	Sangam, Eric M. Trehus

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<46>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<45>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<44>	 9/29/91	DTY		Conditionalize <42> and <43> out of CubeE.
		<43>	 6/10/91	EMT		continue code reduction
		<42>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<41>	 1/14/91	EMT		<VC> Fix race condition in RemoveNetworkConnection.
		<40>	 1/11/91	EMT		<VC> Fix bug in IPCListPorts.
		<39>	12/13/90	EMT		<JSM> Remove race condition, add debug code (for debug versions)
		<38>	11/13/90	EMT		<stb> Remove redundant error checks in StartNetworkSession and
									ListNetworkPorts, add noUserNameErr back in (bug fix).
		<37>	 11/8/90	EMT		<stb> Change key used in scramble, and some error codes.
		<36>	 11/6/90	EMT		use STATIC in place of static for link maps
		<35>	10/30/90	EMT		Remove a tiny window of oppertunity
		<34>	10/24/90	EMT		Update error codes
		<33>	10/11/90	EMT		Add conditionals around debug code, remove reference to
	   								Assembly language completion routine glue.
		<32>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<31>	 9/14/90	EMT		Fix type problem
		<30>	  9/5/90	EMT		Remove a conditional that appears to cause 3.0C some problems
		<29>	  9/4/90	EMT		Fix priority 1 bug
	   <27+>	  9/4/90	EMT		Roll in Eric's changes
		<27>	 8/14/90	S		Fixed Bug in copying the user name in ProcessInform.
		<26>	  8/6/90	S		Bug Fixes.
		<25>	 6/28/90	S		To Improve Dynamic allocation of sessions.
	   <23+>	  6/1/90	EMT		Fix ConnectionRequestCompletion bug that causes failure in
									RepostConnectionListener when ADSP calls it directly
		<23>	  6/1/90	VC		Added the checking of UserFlag after getting the user record.
		<22>	 5/31/90	EMT		Added support to clear the originated flag on inform calls, and
									set it on start.
		<21>	 4/23/90	JSM		Add CopyReadBlk routine to copy readBlk to writeHdrBlk and
									writeBlk in NetIPCParams, fix bug in AuthAcceptCompletion, add
									AvoidDuplicateCompletion prototype, misc. other code size
									reductions.
		<20>	 4/10/90	S		To Include Checking of PPC Global Flag.
		<19>	 3/20/90	S		Fix Bugs Related NetInvisible Ports.
		<17>	 2/28/90	S		IPCListPort Info Returned to refelect Guest Selected Icon.
		<16>	 2/27/90	S		Fix the Guest Stuff.
		<15>	 2/27/90	S		To Make it work with ADSP 1.5(it did not).
		<14>	 2/23/90	S		Bug fix
		<13>	 2/20/90	S		Fix the actual length in write completion during error
									condition.
		<12>	 2/20/90	S		Bug Fix.
		<11>	 2/13/90	S		Bug Fix.
		<10>	  2/8/90	S		No Change.
		 <9>	  2/5/90	S		Changed Error Code For PPCStart(portClosedErr) if user close the
									port after making start.
		 <8>	  2/2/90	S		Fixed Crash on noInform Error.
		 <7>	 1/30/90	S		Changed ErrorCode on Open Completion.
		 <6>	 1/30/90	S		Bug Fixes for some error codes.
		 <5>	 1/26/90	S		Fix Writeing > 32k problem & reading 0 byte
		 <4>	 1/24/90	S		Fix Bug related ppcportclose when the session is being opened.
	   <1.7>	 11/8/89	CVC		Made changes to fix ppcreject crash
	   <1.6>	 11/6/89	KON		Fixed typo: SdssReject -> SessReject
	   <1.5>	 11/6/89	CVC		Fixed a bug in PPCReject
	   <1.4>	10/12/89	CCH		Fixed header
	  <•1.3>	10/12/89	CVC		Added access control stuff
	   <1.2>	 10/2/89	CVC		Fixed a bug in PPCInform call.
	   <1.1>	 9/25/89	ss		Added support for 'more' in PPCwrite call
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.

	   Old Revision History:

		06/05/89 	Sangam	    New Today
		07/20/89    Sangam      1.0d2 release today!
		08/01/89	Sangam		Fixed Bug in End session call
		08/02/89    Sangam      Fixed ADSP bug with a work around (ReadCompletion & RemoveCompletion)
		08/10/89	Sangam		Made Change to IPCListPorts calls
		08/10/89	Sangam		Added userEntry filed for read/write headers
		08/10/89	Sangam		Fixed a bug in listport call
		08/29/89    Sangam		Fixed duplicate completion with informPB
		08/30/89	Sangam		Fixed actualLength filed in Read Calls
		09/07/89	Sangam		Added Appletalk Phase2 Transition Routines
								so that Network can be switched dynamicallly.
		09/07/89    Sangam		Took out the gracefull end for outstanding write.
								Looks like ADSP will not time out anyway
		09/08/89	Sangam		Fixed a bug in WriteData (i.e. res->deadLock was set to 1
								which prevented completion routines being not called
		09/21/89	Sangam		Changed GetPortNames interface
		09/22/89 	Sangam		Removed destportName and destlocname from session data structure
		09/25/89	Sangam		Added support for 'more' in PPCwrite call
		09/26/89	Sangam      Major changes to support authentication
		09/27/89	Sangam      Made change to ListRead to take size of PortInfo
		10/09/89	Sangam		Made changes to support guest login
		11/08/89	Sangam      Made changes to fix ppcreject crash
		1/4/90      Sangam      Several Bug Fixes

*/

#include "PPCCommon.h"
#include <String.h>

/*----------------------------------------------------------------------------------------
	Constants used only in this file.
----------------------------------------------------------------------------------------*/
#define MaxADSPWrite 0x7FFF	// 32767 bytes is the most we should ever write.

/*----------------------------------------------------------------------------------------
	Prototypes for procedures used only in this file.
----------------------------------------------------------------------------------------*/
STATIC NetIPCParamsPtr GetRemSess(PPCGlobalParamsPtr ppcglobPtr);
STATIC void FreeRemSess(NetIPCParamsPtr theSess);
STATIC void RemoveCompletion(void);			// <44>
STATIC void BeginNetworkConnection(NetIPCParamsPtr sessPtr);
STATIC void AcceptNetworkConnection(NetIPCParamsPtr sessPtr);
STATIC void RemoveNetworkConnection(NetIPCParamsPtr sessPtr,Boolean abortFlag);
STATIC void NetLookUpCompletion(void);
STATIC void ConnectionEndCompletion(void);
STATIC void OpenCompletion(void);
STATIC void StartSendCompletion(void);
STATIC void StartCommandCompletion(void);
STATIC void AuthRespSendCompletion(void);
STATIC void AuthAcceptCompletion(void);
STATIC void ListSendCompletion(void);
STATIC void ListReadCompletion(void);
STATIC void ListCommandCompletion(void);
STATIC void RespConnectionEndCompletion(void);
STATIC void RespOpenCompletion(void);
STATIC void RecvSessReqCompletion(void);
STATIC void GuestRecCompletion(UserRecPb *uRec);
STATIC void UserRecCompletion(UserRecPb	*uRec);
STATIC void AuthSendCompletion(void);
STATIC void AuthRespCompletion(void);
STATIC void ProcessInform(NetIPCParams *sessPtr,unsigned short userFlags);
STATIC void RespSendCompletion(void);
STATIC void ARepostConnectionListener(void);
STATIC void RepostConnectionListener(DSPParamBlock *dsp);
STATIC void ListWrite(NetIPCParams *sessPtr);
STATIC void ListWriteCompletion(void);
STATIC void ListRespCompletion(void);

STATIC void BeginWriteBlock(NetIPCParamsPtr sessPtr);
STATIC void WriteHdrCompletion(void);
STATIC void WriteBlockData(NetIPCParamsPtr sessPtr);
STATIC void WriteBlockDataCompletion(void);
STATIC void CompleteWriteRequest(NetIPCParamsPtr sessPtr,OSErr result);

STATIC void BeginReadBlock(NetIPCParamsPtr sessPtr);
STATIC void ReadHdrCompletion(void);
STATIC void ReadBlockData(NetIPCParamsPtr sessPtr);
STATIC void ReadDataCompletion(void);
STATIC void ReadData(NetIPCParamsPtr sessPtr);
STATIC void CompleteReadRequest(NetIPCParamsPtr sessPtr,OSErr result);

STATIC void CopyReadBlk(NetIPCParamsPtr sessPtr);

/*----------------------------------------------------------------------------------------
	GetRemSess
----------------------------------------------------------------------------------------*/
STATIC NetIPCParamsPtr GetRemSess(PPCGlobalParamsPtr ppcglobPtr)
{
	NetIPCParamsPtr sessPtr;
	
	if(sessPtr = ServeQueue(&ppcglobPtr->freeRemSessQueue))
	{
		memset(sessPtr,0,sizeof(NetIPCParams));	// Wipe it clean
		sessPtr->sessUse = netUse;
		EnQueue(sessPtr,&ppcglobPtr->RemSessQueue);
	}
	return(sessPtr);
}

/*----------------------------------------------------------------------------------------
	FreeRemSess
----------------------------------------------------------------------------------------*/
STATIC void FreeRemSess(NetIPCParamsPtr theSess)
{
	PPCGlobalParamsPtr ppcglobPtr;
	PPCPortEntryPtr portPtr;
	
	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	portPtr = theSess->portEntry;
	DeleteFromQueue(&ppcglobPtr->RemSessQueue,(unsigned long)theSess,PointerCompare);
	if(portPtr)								// <44>if this session belongs to a port.
		--portPtr->sessCount;				// <44> update the port table.
	theSess->portEntry = (void *)-1;		// check for bug!
	EnQueue(theSess,&ppcglobPtr->freeRemSessQueue);
}

/*----------------------------------------------------------------------------------------
	RemoveNetworkConnection is responsible for scheduling a job to remove the network connection.
----------------------------------------------------------------------------------------*/
STATIC void RemoveNetworkConnection(NetIPCParamsPtr sessPtr,Boolean abortFlag)
{
	PPCGlobalParamsPtr ppcglobPtr;
	short sr;

	sr = spl(kNoInterrupts);
	if(sessPtr->sessState != AwaitAbortComp)	// if we arn't already aborting it then…
	{
		sessPtr->sessState = AwaitAbortComp;
		sessPtr->abortFlag = abortFlag;			// remember how we are aborting this.
		
		ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
		DeleteFromQueue(&ppcglobPtr->RemSessQueue,(unsigned long)sessPtr,PointerCompare);
		EnQueue(sessPtr,&ppcglobPtr->dspAbortQueue);	// place it in the queue of things to do.
		if(!ppcglobPtr->killSessPtr)					// if we are not busy then…
		{
			ppcglobPtr->killSessPtr = ServeQueue(&ppcglobPtr->dspAbortQueue);
			spl(sr);
			BlockMove((Ptr)&sessPtr->readBlk.dsp,(Ptr)&ppcglobPtr->dspRemovePB,sizeof(DSPParamBlock));
			RemoveConnectionEnd(sessPtr->abortFlag, // abort flag (Kill all pending requests)
								true,
								(ProcPtr)RemoveCompletion, // Completion Routine
								&ppcglobPtr->dspRemovePB);
			return;
		}
	}
	spl(sr);
}

/*---------------------------------------------------------------------------------------------------
	RemoveCompletion
---------------------------------------------------------------------------------------------------*/
STATIC void RemoveCompletion(void)
{
	PPCGlobalParamsPtr ppcglobPtr;
	PPCPortEntryPtr		portPtr;
	PPCParamBlockPtr	PB;
	NetIPCParams *sessPtr;
	
	ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
	sessPtr = ppcglobPtr->killSessPtr;

#ifdef DEBUG
	if(ppcglobPtr->dspRemovePB.ioResult)
		DebugStr("\pError in removing a network connection");
#endif
	PB = (PPCParamBlockPtr)sessPtr->endPB;
	KillReadAndWrite(sessPtr);
	portPtr = (PPCPortEntryPtr)sessPtr->portEntry; 
	FreeRemSess(sessPtr);
	if (PB)
		CompleteWithResult(PB,noErr);
	else if (portPtr) // Must be a PPCClose operation.
		CompleteClosePort(portPtr);
	
	// Don't change the next two lines or some day you may be sorry!!!
	ppcglobPtr->killSessPtr = sessPtr = ServeQueue(&ppcglobPtr->dspAbortQueue);
	if(sessPtr)
	{
		BlockMove((Ptr)&sessPtr->readBlk.dsp,(Ptr)&ppcglobPtr->dspRemovePB,sizeof(DSPParamBlock));
		RemoveConnectionEnd(sessPtr->abortFlag,
							true,
							(ProcPtr)RemoveCompletion, // Completion Routine
							&ppcglobPtr->dspRemovePB);
	}	
}

/*----------------------------------------------------------------------------------------
	StartNetworkSession
----------------------------------------------------------------------------------------*/
void StartNetworkSession(PPCStartPBPtr  startPB,
						  PPCPortEntryPtr    portPtr,
						  PPCGlobalParamsPtr ppcglobPtr)
{
	NetIPCParamsPtr	sessPtr;
		
	if ((startPB->userRefNum) && (!findUserByRef(startPB->userRefNum)))
	{
		CompleteWithResult(startPB,noUserRecErr);
		return;
	}
	if (!(sessPtr = GetRemSess(ppcglobPtr)))
	{
		CompleteWithResult(startPB,sessTableErr);
		return;
	}

	SetSessionTable((CommonSessionParamsPtr)sessPtr, portPtr, ppcglobPtr); 
	sessPtr->PBPtr = startPB; 				// First PB for this Session
	BeginNetworkConnection(sessPtr);
}

/*----------------------------------------------------------------------------------------
	AcceptNetworkSession
----------------------------------------------------------------------------------------*/
void AcceptNetworkSession(PPCAcceptPBPtr      acceptPB,
						   NetIPCParamsPtr  sessPtr)
{
	IPCAcceptBlkPtr        accept;
	
	accept =  (IPCAcceptBlkPtr)&((sessPtr)->writeBlk.buffer);
	accept->respType = SessAccept; 			// Stuff the message
	sessPtr->PBPtr   = acceptPB;
	AcceptNetworkConnection(sessPtr);
	
} // AcceptNetworkSession

/*----------------------------------------------------------------------------------------
	RejectNetworkSession
----------------------------------------------------------------------------------------*/
void RejectNetworkSession(PPCRejectPBPtr rejectPB,
						   NetIPCParamsPtr sessPtr)
{
	IPCRejectBlkPtr reject;

	reject =  (IPCRejectBlkPtr)&((sessPtr)->writeBlk.buffer);
	reject->respType = UserReject; 			// Stuff the message
	reject->rejectInfo = rejectPB->rejectInfo;
	sessPtr->PBPtr = rejectPB; 				// This will make sure that connection gets closed
	AcceptNetworkConnection(sessPtr);
} // RejectNetworkSession

/*----------------------------------------------------------------------------------------
	WriteNetworkData Begins to write the clients data immediatly if not already doing so in a
	previous request, otherwise it just leaves it on the queue for processing later.
----------------------------------------------------------------------------------------*/
void WriteNetworkData(PPCWritePBPtr writePB,
					  NetIPCParamsPtr  sessPtr) 
{
	short sr;
	
	AddWritePB(sessPtr,writePB);
	sr = spl(kNoInterrupts);
	if(!sessPtr->writePB)
	{
		sessPtr->writePB = GetWritePB(sessPtr);
		spl(sr);
		BeginWriteBlock(sessPtr);
	}
	else
		spl(sr);
} // WriteNetworkData

/*----------------------------------------------------------------------------------------
	ReadNetworkData begins to read data immediatly if not already doing so in a previous request,
	otherwise it just places the read on the queue for later processing.
----------------------------------------------------------------------------------------*/
void ReadNetworkData(PPCReadPBPtr readPB,
					  NetIPCParamsPtr  sessPtr)
{
	short sr;
	
	AddReadPB(sessPtr,readPB);
	sr = spl(kNoInterrupts);
	if(!sessPtr->readPB)
	{
		sessPtr->readPB = GetReadPB(sessPtr);
		spl(sr);
		BeginReadBlock(sessPtr);
	}
	else
		spl(sr);
} // ReadNetworkData


/*----------------------------------------------------------------------------------------
	EndNetworkSession
----------------------------------------------------------------------------------------*/
void EndNetworkSession(PPCEndPBPtr endPB,NetIPCParamsPtr sessPtr) 
{
	sessPtr->endPB = endPB; // Save it for later use.
	RemoveNetworkConnection(sessPtr,true);
}

/*----------------------------------------------------------------------------------------
	ListNetworkPorts is the entry point for a network Initiated IPCListPorts requests.  A session
	table is gotten, and initialized here.
----------------------------------------------------------------------------------------*/
void ListNetworkPorts(IPCListPortsPBPtr listPB,PPCGlobalParamsPtr ppcglobPtr)
{
	NetIPCParamsPtr sessPtr;
	PBWriteResPtr        res;
	
	res =(PBWriteResPtr)(listPB->Reserved);

	if (sessPtr = GetRemSess(ppcglobPtr))
	{
		SetSessionTable((CommonSessionParamsPtr)sessPtr, nil, ppcglobPtr); 
		sessPtr->PBPtr = listPB; // First PB for this Session
		sessPtr->portEntry = nil;
		BeginNetworkConnection(sessPtr);
	}
	else
		CompleteWithResult(listPB,sessTableErr);

} // ListNetworkPorts

/*----------------------------------------------------------------------------------------
	BeginNetworkConnection is where session establishment begins for both IPCListPorts and PPCStart.
	The first thing that occurs is an NBPLookup to find the destination address.
----------------------------------------------------------------------------------------*/
STATIC void BeginNetworkConnection(NetIPCParamsPtr sessPtr)
{
	IPCListPortsPBPtr listPB = sessPtr->PBPtr;
	PPCStartPBPtr  startPB = sessPtr->PBPtr;
	LocationNamePtr		  locationName;

	if (startPB->csCode == PPCStartCall)
	  locationName = startPB->locationName;
	else
	  locationName = listPB->locationName;

	
	sessPtr->sessState = AwaitLookupResp;
	NBPSetEntity((unsigned char *)sessPtr->miscData.nbpData.lkupentity,
				 (Ptr)&(locationName->u.nbpEntity.objStr),
				 (Ptr)&(locationName->u.nbpEntity.typeStr),
				 (Ptr)&(locationName->u.nbpEntity.zoneStr));
	
	LookupName((EntityName *)sessPtr->miscData.nbpData.lkupentity,
			   true,        // Get Asynchronously
			   (ProcPtr)NetLookUpCompletion, // Completion Routine
			   (unsigned char *)sessPtr->miscData.nbpData.lkupbuf, //lookup bufferptr
			   lkupbufSize, // BufferSize
			   (NBPparms *)&(sessPtr->miscData.nbpData.nbpPB));

}	// BeginNetworkConnection

/*---------------------------------------------------------------------------------------------------
	AcceptNetworkConnection
---------------------------------------------------------------------------------------------------*/
STATIC void AcceptNetworkConnection(NetIPCParamsPtr sessPtr)
{			
	sessPtr->sessState = AwaitAcceptSendComp;
			
	WriteToConnection(sizeof(IPCAcceptBlk),
					 (char *)&(sessPtr->writeBlk.buffer),
					 1, // eom 
					 1, // flush
					 true, // Asynchronously
					 (ProcPtr)RespSendCompletion, // Completion Routine
					 (DSPParamBlock *)&(sessPtr->writeBlk.dsp));
} // AcceptNetworkConnection

/*----------------------------------------------------------------------------------------
	NetLookUpCompletion is chained from BeginNetworkConnection.  This is a completion routine for
	an NBPLookup.  We are either trying to perform an IPCListPorts, or a PPCStart.
----------------------------------------------------------------------------------------*/
STATIC void NetLookUpCompletion(void)
{
	NBPparms			*nbpPB;
	NetIPCParamsPtr		sessPtr;
	PPCGlobalParamsPtr	ppcglobPtr;
	PPCStartPBPtr		startPB; 

	nbpPB = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(nbpPB,NetIPCParams,miscData.nbpData.nbpPB);
	startPB = (PPCStartPBPtr)sessPtr->PBPtr;	// Might be IPCListPorts as well.
	
	if (nbpPB->ioResult)
	{
		FreeRemSess(sessPtr);
		CompleteWithResult(startPB,nbpPB->ioResult);
	}
	else if	(nbpPB->parm.Lookup.numGotten == 0)
	{
		FreeRemSess(sessPtr);
		CompleteWithResult(startPB,noResponseErr);
	}
	else
	{
		BlockMove((char *)(nbpPB->parm.Lookup.retBuffPtr),
				  (char *)&(sessPtr->destAddr),
				  sizeof(AddrBlock));
				  	
	    ppcglobPtr = (PPCGlobalParamsPtr)getGlobal();
		sessPtr->sessState = AwaitDSPInit;
		CreateConnectionEnd((TRCCB *)&(sessPtr->ce), //ccbPtr
							    nil, // no user Routine
								DspSendQSize,
								sessPtr->sendQ,
								DspRecvQSize,
								sessPtr->recvQ,
								sessPtr->attnBuffer,
								0,	// ADSP picks our socket.
								ppcglobPtr->dspDrvrRef,
								true, // Asynhcronous
								(ProcPtr)ConnectionEndCompletion, // CompletionRoutine
								&sessPtr->readBlk.dsp);
	}
} // NetLookUpCompletion

/*----------------------------------------------------------------------------------------
	ConnectionEndCompletion is chained from NetLookUpCompletion.  This is a completion routine for
	a dspInit.  A new ADSP Connection Listener has been established.  The socket for this
	connection listener is different than the one where PPCToolBox name is registered.
----------------------------------------------------------------------------------------*/
STATIC void ConnectionEndCompletion(void)
{
  	NetIPCParams	*sessPtr;
  	PPCStartPBPtr	startPB;
	DSPParamBlock	*dsp;
  
	dsp = GetA0();
	sessPtr= TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	startPB = sessPtr->PBPtr;
    
  	if (dsp->ioResult)
	{
		CompleteWithResult(startPB,dsp->ioResult);
		FreeRemSess(sessPtr);
	}
	else
	{
		sessPtr->sessState = AwaitOpenComp;
		/* Copy the parameter Block */
		CopyReadBlk(sessPtr);

		OpenConnectionEnd(0, // remoteCID
						 (AddrBlock *)&(sessPtr->destAddr), // Remote Addess
						 (AddrBlock *)&(sessPtr->destAddr), // Filter Addess
						  0, // Initial sendSeq
						  0, // Initial sendWindow
						  0, // attnSendSeq
						  ocRequest, // ocMode
						  true, // Asynchronous
						  (ProcPtr)OpenCompletion, // Completion Routine
						  &sessPtr->readBlk.dsp);

	}
}

/*----------------------------------------------------------------------------------------
	OpenCompletion is chained from ConnectionEndCompletion.  This is a completion routine for
	a dspOpen call.  If all went well, we will have an ADSP connection established at this time.
	At this point we begin to diverge if we are performing an IPCListPorts, or a PPCStart.
	
	If PPCStart, then we transmit an IPCStartBlk structure (See PPCCommon.h for the format).
	If IPCListPorts, then we transmit an IPCListReqBlk structure. (See PPCCommon.h for the format).
----------------------------------------------------------------------------------------*/
STATIC void OpenCompletion(void)
{
	DSPParamBlock		*dsp;
  	NetIPCParams		*sessPtr;
	PPCStartPBPtr		startPB;
	UserEntryPtr		uEntry;

	dsp = GetA0();
	sessPtr= TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	startPB = sessPtr->PBPtr;	// in fact may be an IPCListPorts PB.
	if (dsp->ioResult)  
	{
		CompleteWithResult(startPB,sessPtr->sessState != AwaitAbortComp?
							noResponseErr:portClosedErr);
		sessPtr->PBPtr = NULL;
		RemoveNetworkConnection(sessPtr,false);
		return;

	}
	
	CopyReadBlk(sessPtr);	/* Copy the parameter Block */
	if (startPB->csCode == PPCStartCall)
	{
		IPCStartBlkPtr	startBlk;	// Protocol to begin PPCStart.

		startBlk =  &sessPtr->writeBlk.buffer.buffer.startBlk;
		if (startPB->userRefNum == 0)
			startBlk->userName[0] = 0; // No User Name
		
		// FIXME -- Can this be done earlier in the game???
		else if ((uEntry = findUserByRef(startPB->userRefNum)) == nil)
		{
			CompleteWithResult(startPB,noUserRecErr);
			RemoveNetworkConnection(sessPtr,false);
			return;
		}
		else
		{
			// This unscrambles the name we just looked up in the table.
			scramble (kNameKey, uEntry->name, (char *)(startBlk->userName));
		}
		sessPtr->sessState = AwaitStartSendComp;

		/* Prepare the header block */
		startBlk->reqType = SessRequest;
		startBlk->userData = startPB->userData;
		
		CopyPortName(&sessPtr->portEntry->portName,&startBlk->reqportName);
		CopyPortName(startPB->portName,&startBlk->destportName);
		GetLocationName((PPCGlobalParamsPtr)getGlobal(),sessPtr->portEntry,&startBlk->locationName);
		
		WriteToConnection(sizeof(IPCStartBlk),
						(char *)startBlk,
						1, // eom 
						1, // flush
						true, // Asynchronously
						(ProcPtr)StartSendCompletion, // Completion Routine
						(DSPParamBlock *)&(sessPtr->writeBlk.dsp)
						);
	}
	else if (startPB->csCode == IPCListPortsCall)
	{
		IPCListReqBlkPtr	list;
		IPCListPortsPBPtr 	listPB;
		
		sessPtr->sessState = AwaitListSendComp;
		list =  (IPCListReqBlkPtr)&(sessPtr->writeBlk.buffer);
		listPB = (IPCListPortsPBPtr)(startPB);
		list->reqType = ListRequest;
		list->startIndex = listPB->startIndex;
		list->requestCount = listPB->requestCount;
		CopyPortName(listPB->portName, &(list->portName));

		WriteToConnection(sizeof(IPCListReqBlk),
						 (char *)list,
						 1, // eom 
						 1, // flush
						 true, // Asynchronously
						 (ProcPtr)ListSendCompletion, // Completion Routine
						 &sessPtr->writeBlk.dsp);
	}
} // OpenCompletion

/*----------------------------------------------------------------------------------------
	StartSendCompletion is chained from OpenCompletion.  This is a completion routine for a 
	dspWrite call.  At this point we have written the IPCStartBlk structure.  We now prepare
	to read in the reply.  The format of the reply is described in an AuthInfoBlk structure.
----------------------------------------------------------------------------------------*/
STATIC void StartSendCompletion(void)
{
	DSPParamBlock	*dsp;
  	NetIPCParams	*sessPtr;
	PPCStartPBPtr	startPB;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
	if (dsp->ioResult)
	{
		if(startPB = sessPtr->PBPtr)
		{
			sessPtr->PBPtr = NULL;
			CompleteWithResult(startPB,dsp->ioResult);
		}
		
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		if(sessPtr->sessState == AwaitStartSendComp)
			sessPtr->sessState = AwaitAcceptResp;
		else
			sessPtr->sessState = AwaitAuthAccept;
		ReadFromConnection(sizeof(IPCBufBlk),
						  (char *)&(sessPtr->readBlk.buffer),
						  true, // Asynchronously
						  (ProcPtr)StartCommandCompletion, // completion Routine
						  &sessPtr->readBlk.dsp);
	}
} // StartSendCompletion

/*----------------------------------------------------------------------------------------
	StartCommandCompletion
----------------------------------------------------------------------------------------*/

STATIC void StartCommandCompletion(void)
{
	DSPParamBlock	*dsp;
	IPCReadBlk		*rblk;
  	NetIPCParams	*sessPtr;
	PPCStartPBPtr   startPB;
	IPCAcceptBlk	*ablk;
	AuthInfoBlk		*auth1, *auth2;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	rblk = &sessPtr->readBlk;

	startPB = sessPtr->PBPtr;
	startPB->rejectInfo = nil; // Assume this (If reject, this will change)

	if(sessPtr->sessState != AwaitAcceptResp &&
	   sessPtr->sessState != AwaitAuthAccept)
		startPB->ioResult = portClosedErr;		// Port must be closing.
	else if(dsp->ioResult)
		startPB->ioResult = dsp->ioResult;
	else if(!dsp->u.ioParams.actCount && !dsp->u.ioParams.eom)
		startPB->ioResult = destPortErr;
	else
	{

		ablk = (IPCAcceptBlk *)&(rblk->buffer);
		switch (ablk->respType)
		{
			case SessAccept:
			{
				sessPtr->sessState = DataXferState;
				sessPtr->PBPtr = NULL; // Nothing in the Que
				sessPtr->originator = true;	// we started this session.
				startPB->sessRefNum = sessPtr->sessRefNum;
				CompleteWithResult(startPB,noErr);
				return;
			}
			break;
			case AuthContinue:
			{
#ifdef DEBUG
				if(sessPtr->sessState != AwaitAcceptResp)
					Debugger();
#endif
				// Server wants the connection to be authenticated
				auth1 = (AuthInfoBlk *)ablk;
				if (!(GetAuthInfo((long *)auth1->authInfo, startPB->userRefNum)))
					startPB->ioResult = noUserRecErr;
				else
				{
					sessPtr->sessState = AwaitAuthRespSend;
					auth2 =(AuthInfoBlk *)&(sessPtr->writeBlk.buffer);
					auth2->respType = AuthInfoResp;
					auth2->authInfo[0] = auth1->authInfo[0];
					auth2->authInfo[1] = auth1->authInfo[1];
					WriteToConnection(sizeof(AuthInfoBlk),
									 (char *)auth2,
									 1, // eom 
									 1, // flush
									 true, // Asynchronously
									 (ProcPtr)StartSendCompletion, // Completion Routine
									 (DSPParamBlock *)&(sessPtr->writeBlk.dsp)
									 );
					return;
	
				}
			}
			break;
			case SessReject:
			{
				switch (ablk->rejectInfo)
				{
					case notVisible:
					case noPort:
						startPB->ioResult = destPortErr;
						break;
					case noInforms:
						startPB->ioResult = noInformErr;
						break;
					case noGuestEnabled:
						startPB->ioResult = guestNotAllowedErr;
						break;
					case iacDisabled:
						startPB->ioResult = userRejectErr;
						break;
					case noUserRec:	// UnKnown User on target computer.
						startPB->ioResult = noUserNameErr;
						break;
					case AuthFailure:
						startPB->ioResult = authFailErr;
						break;
				} // end switch ablk->rejectInfo
				startPB->rejectInfo = 0;
				
			}
			break;
			case UserReject:
			{
				startPB->ioResult = userRejectErr;
				startPB->rejectInfo = ablk->rejectInfo;
			}
			break;
			default:	// I don't think we can get here, unless were talking to a non-PPCToolBox.
				startPB->ioResult = networkErr;
			break;
		} // end switch ablk->respType
  } // End else
  CompleteWithResult(startPB,startPB->ioResult);
  sessPtr->PBPtr = NULL;
	RemoveNetworkConnection(sessPtr,false);

}

/*----------------------------------------------------------------------------------------
	ListSendCompletion is chained from OpenCompletion.
----------------------------------------------------------------------------------------*/

STATIC void ListSendCompletion(void)
{
	DSPParamBlock		*dsp;
	NetIPCParams        *sessPtr;
	IPCListPortsPBPtr    listPB;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
	listPB = sessPtr->PBPtr;
	if (dsp->ioResult != noErr)
	{
		CompleteWithResult(listPB,dsp->ioResult);
  		sessPtr->PBPtr = NULL;
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		sessPtr->sessState = AwaitListRead;
		ReadFromConnection(sizeof(PortInfoRec) * listPB->requestCount,
						  (Ptr)listPB->bufferPtr,
						  true, // Asynchronously
						  (ProcPtr)ListReadCompletion, // completion Routine
						  &sessPtr->readBlk.dsp);
	}
} // ListSendCompletion

/*----------------------------------------------------------------------------------------
	ListReadCompletion is chained from ListSendCompletion.
----------------------------------------------------------------------------------------*/
STATIC void ListReadCompletion(void)
{
	DSPParamBlock		*dsp;
	NetIPCParams		*sessPtr;
	IPCListPortsPBPtr   listPB;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	listPB = sessPtr->PBPtr;
	if (dsp->ioResult != noErr)
	{
		CompleteWithResult(listPB,dsp->ioResult);
	  	sessPtr->PBPtr = NULL;
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		sessPtr->sessState = AwaitListResp;
		ReadFromConnection(sizeof(IPCListRespBlk),
						  (char *)&(sessPtr->readBlk.buffer),
						  true, // Asynchronously
						  (ProcPtr)ListCommandCompletion, // completion Routine
						  &sessPtr->readBlk.dsp);
	}
} // ListReadCompletion

/*----------------------------------------------------------------------------------------
	ListCommandCompletion is chained from ListReadCompletion.
----------------------------------------------------------------------------------------*/
STATIC void ListCommandCompletion(void)
{
	DSPParamBlock		*dsp;
	IPCReadBlk			*rblk;
  	NetIPCParams		*sessPtr;
	IPCListPortsPBPtr   listPB;
	IPCListRespBlk		*lblk;
	
	dsp = GetA0();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	listPB = sessPtr->PBPtr;
  	sessPtr->PBPtr = NULL;
	if (dsp->ioResult != noErr)
		listPB->ioResult = dsp->ioResult;
	else
	{

		lblk = (IPCListRespBlk *)&(rblk->buffer);
		if (lblk->respType == ListResp)
		{
			listPB->ioResult = noErr;
			listPB->actualCount = lblk->actualCount;
		}
		else
			listPB->ioResult = networkErr;
	}
	CompleteWithResult(listPB,listPB->ioResult);
  	sessPtr->PBPtr = NULL;
	RemoveNetworkConnection(sessPtr,false);
} // ListCommandCompletion

/*----------------------------------------------------------------------------------------
	ConnectionRequestCompletion is chained from PPCInit.c:SetUpConnectionListeners, and 
	RepostConnectionListener.
	
	On Entry A0 has a pointer to a completed dspCLListen parameter block.  This is the
	point at which session conception begins for PPCToolbox.  Either its an IPCListPorts
	or a PPCStart that initiated the session, and we are here receiving it.
----------------------------------------------------------------------------------------*/
void ConnectionRequestCompletion(void)
{
	DSPParamBlock *dsp;
	NetIPCParamsPtr sessPtr;
	TRopenParams *open, *open2;
	DSPParamBlock *dsp2;
	PPCGlobalParams *ppcglobPtr;
	
	dsp = GetA0();
	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	if (dsp->ioResult == errAborted)
		return; // Looks like someone wants to remove listeners
	else if ((!(ppcglobPtr->allowIncommingRequests)) ||
				(!(sessPtr = GetRemSess(ppcglobPtr))))
		RejectConnectionRequest(dsp, 
								true, // Asynchronous
								(ProcPtr)ARepostConnectionListener
								);
    else
	{
		sessPtr->portEntry = 0; // we don't have them yet
		sessPtr->endPB = 0;     // we don't have them yet
		dsp2 = (DSPParamBlock *)&(sessPtr->writeBlk.dsp);
		open = (TRopenParams *)&(dsp->u.initParams);
		/* Copy the Session Parameters */
		open2 = (TRopenParams *)&(dsp2->u.initParams);
		open2->remoteCID = open->remoteCID;
	    open2->remoteAddress.aNet = open->remoteAddress.aNet;
		open2->remoteAddress.aNode = open->remoteAddress.aNode;
		open2->remoteAddress.aSocket = open->remoteAddress.aSocket;
		open2->sendSeq = open->sendSeq;
		open2->sendWindow = open->sendWindow;
		open2->attnSendSeq = open->attnSendSeq;
		sessPtr->sessState = AwaitRecvDSPInit;
		CreateConnectionEnd((TRCCB *)&(sessPtr->ce), //ccbPtr
							  nil, // no user Routine (we need a routine to release session
							  DspSendQSize,
							  sessPtr->sendQ,
							  DspRecvQSize,
							  sessPtr->recvQ,
							  sessPtr->attnBuffer,
							  ppcglobPtr->adspSocket,
							  ppcglobPtr->dspDrvrRef,
							  true, // Asynhcronous
							  (ProcPtr)RespConnectionEndCompletion, // CompletionRoutine
							  (DSPParamBlock *)&(sessPtr->readBlk.dsp)
					  		);

		RepostConnectionListener(dsp);
	}

} // ConnectionRequestCompletion

/*----------------------------------------------------------------------------------------
	RespConnectionEndCompletion is chained from ConnectionRequestCompletion.
	
	On Entry A0 contains a pointer to a completed dspInit parameter block that
	corresponds to the readBlk of our session.
	In the session table there is a copy of a completed dspCLListen PB in the
	writeBlk.  We use this PB to make the dspOpen since the remoteCID, remoteAddress,
	sendSeq, sendWindow, and attnSendSeq numbers are already correctly filled in.
----------------------------------------------------------------------------------------*/
STATIC void RespConnectionEndCompletion(void)
{
	DSPParamBlock *dsp;
	IPCReadBlk         *rblk;
  	NetIPCParams       *sessPtr;
	TRopenParams *open;
	DSPParamBlock *dsp2;
	
	dsp = GetA0();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	dsp2 = (DSPParamBlock *)&(sessPtr->writeBlk.dsp);
	open = (TRopenParams *)&(dsp2->u.initParams);

	if (dsp->ioResult) // some error occured
		FreeRemSess(sessPtr);
	else
	{
	  sessPtr->sessState = AwaitocAcceptComp;
	  OpenConnectionEnd(open->remoteCID, // remoteCID
					 (AddrBlock *)&(open->remoteAddress), // Remote Addess
					 (AddrBlock *)&(open->remoteAddress), // Filter Addess
					  open->sendSeq, // Initial sendSeq
					  open->sendWindow, // Initial sendWindow
					  open->attnSendSeq, // attnSendSeq
					  ocAccept, // ocMode
					  true, // Asynchronous
					  (ProcPtr)RespOpenCompletion, // Completion Routine
					  (DSPParamBlock *)&(sessPtr->readBlk.dsp)
					);
	}
} // RespConnectionEndCompletion

/*----------------------------------------------------------------------------------------
	RespOpenCompletion is chained from RespConnectionEndCompletion.  At this point the 
	ADSP session is fully established.
	
	On Entry A0 cointains a pointer to a completed dspOpen parameter block that corresponds
	to the sessions writeBlk.  Read in the first block of data that was written by PPC.
----------------------------------------------------------------------------------------*/
STATIC void RespOpenCompletion(void)
{
	DSPParamBlock *dsp;
  	NetIPCParams       *sessPtr;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);

	if (dsp->ioResult)
	{
		// some Error occured
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		sessPtr->sessState = AwaitRecvSessReq;
		ReadFromConnection(sizeof(IPCStartBlk),
					   (char *)&(sessPtr->readBlk.buffer),
					   true, // Asynchronously
					   (ProcPtr)RecvSessReqCompletion, // completion Routine
					   &sessPtr->readBlk.dsp);
	}


} // RespOpenCompletion

/*----------------------------------------------------------------------------------------
	RecvSessReqCompletion is chained from RespOpenCompletion.
----------------------------------------------------------------------------------------*/
STATIC void RecvSessReqCompletion(void)
{
	DSPParamBlock *dsp;
	IPCReadBlk         *rblk;
  	NetIPCParams       *sessPtr;
	IPCStartBlk        *sblk;
	PPCPortEntryPtr    portPtr;
	PPCGlobalParams    *ppcglobPtr;
	IPCAcceptBlkPtr    accept;
	IPCListReqBlkPtr   list;
	unsigned short sr;
	
	dsp = GetA0();
	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	sblk = (IPCStartBlk *)&(rblk->buffer);
	accept =  (IPCAcceptBlkPtr)&(sessPtr->writeBlk.buffer);

	
	if (dsp->ioResult == noErr && dsp->u.ioParams.actCount != 0) 
	{
		
    	/* Copy the parameter Block */
		CopyReadBlk(sessPtr);
		switch(sblk->reqType)
		{
			case SessRequest:
				if (portPtr = CheckPortName((PPCPortPtr)&(sblk->destportName),ppcglobPtr))
				{
					// We Have a valid Port
							
					SetSessionTable((CommonSessionParamsPtr)sessPtr, portPtr, ppcglobPtr); 

					if (portPtr->networkVisible)
					{
						// We have Port exported for network access
						if (portPtr->authRequest)
						{
							if (sblk->userName[0] == 0)
							{
								sessPtr->miscData.btreeData.guestRec = true;
							}
							else
								sessPtr->miscData.btreeData.guestRec = false;
							
							// Requires Authentication
							sessPtr->sessState = AwaitBtreeComp;
							if (ppcglobPtr->ugFile.refNum != 0)
							{
								getUserRec((UserRecPb *)&(sessPtr->miscData.btreeData),
										0, // Key ID
										(char *)sblk->userName,
										(ProcPtr)UserRecCompletion,
										ppcglobPtr->ugFile.refNum);
							}
							else
							{
								accept->rejectInfo = noUserRec;	// Trouble with BTree, deny knowing this user.
								accept->respType = SessReject;
								sessPtr->PBPtr = NULL;
								AcceptNetworkConnection(sessPtr);

							}
							return;
						}
						else
						{
							ProcessInform(sessPtr, 0 );
							return;
						}
					}
					else
						accept->rejectInfo = notVisible; //Only Internal
				}
				else
					accept->rejectInfo = noPort;
				accept->respType = SessReject;
				sessPtr->PBPtr = NULL;
				AcceptNetworkConnection(sessPtr);
				return;

			case ListRequest:
				DeleteFromQueue(&ppcglobPtr->RemSessQueue,(unsigned long)sessPtr,PointerCompare);
				SetSessionTable((CommonSessionParamsPtr)sessPtr, nil, ppcglobPtr); 
				sessPtr->PBPtr = NULL;
				sessPtr->portEntry = nil;
				sessPtr->sessState = AwaitListWriteComp;
				
				// For Later Guest Record Checkup
				list = (IPCListReqBlkPtr)sblk;
				list->userName[0] =0;

				sessPtr->miscData.btreeData.guestRec = true;

				EnQueue(sessPtr,&ppcglobPtr->ListSessQueue);
				sr = spl(kNoInterrupts);
				if (!ppcglobPtr->listsessPtr)
				{
					// we can process the request
					ppcglobPtr->listsessPtr = ServeQueue(&ppcglobPtr->ListSessQueue);
					spl(sr);
					ppcglobPtr->totalCount =  0; // Total count so far
					ppcglobPtr->listIndex = list->startIndex;
	                if (ppcglobPtr->ugFile.refNum != 0)
					{
						getUserRec((UserRecPb *)&(sessPtr->miscData.btreeData),
										0,	// Key ID
										(char *)list->userName,
										(ProcPtr)GuestRecCompletion,
										ppcglobPtr->ugFile.refNum);
					}
					else
					{
						ppcglobPtr->guestUnchecked = false;
						ListWrite(sessPtr);
					}
	
	    		}
				else
				{
					spl(sr);
				}
				return;
		} // end switch
	}
	// If it is not anyyone of the above abort it any way
	RemoveNetworkConnection(sessPtr,false);
} // RecvSessReqCompletion 


/*----------------------------------------------------------------------------------------
	GuestRecCompletion chained from RecvSessReqCompletion and UserRecCompletion.
----------------------------------------------------------------------------------------*/
STATIC void GuestRecCompletion(UserRecPb	*uRec)
{
	 NetIPCParams       *sessPtr;
	 PPCGlobalParams    *ppcglobPtr;


	 sessPtr = TOP_OF_RECORD_PTR(uRec,NetIPCParams,miscData.btreeData);
	 ppcglobPtr = (PPCGlobalParams *)getGlobal();

	 if (sessPtr->sessState == AwaitListWriteComp)
	 {
		ppcglobPtr->guestUnchecked = false;
		if ((uRec->btPb.ioResult == noErr) && 
			(uRec->u.ulRecord.ServerFlags & IACGuestEnabled))
			ppcglobPtr->guestUnchecked = true;
		ListWrite(sessPtr);
	 }

} // GuestRecCompletion
 
/*----------------------------------------------------------------------------------------
	UserRecCompletion chained from RecvSessReqCompletion.
----------------------------------------------------------------------------------------*/
STATIC void UserRecCompletion(UserRecPb	*uRec)
{
  	NetIPCParams       *sessPtr;
	IPCAcceptBlkPtr    accept;				// <44>
	AuthInfoBlkPtr	   auth;				// <44>
	
	sessPtr = TOP_OF_RECORD_PTR(uRec,NetIPCParams,miscData.btreeData);
	accept =  (IPCAcceptBlkPtr)&(sessPtr->writeBlk.buffer);

	if (sessPtr->sessState != AwaitBtreeComp)
	{
		RemoveNetworkConnection(sessPtr,false);
	}
	else if (uRec->btPb.ioResult) 
	{
		accept->rejectInfo = noUserRec;		// User name not in my BTree.
		accept->respType = SessReject;
  		sessPtr->PBPtr = NULL;
		AcceptNetworkConnection(sessPtr);
	}
	else if (uRec->guestRec) 
	{
		if (uRec->u.ulRecord.ServerFlags & IACGuestEnabled)
					// Guest is enabled
			ProcessInform(sessPtr, 0x0001);		
		else
		{
			accept->rejectInfo = noGuestEnabled;
			accept->respType = SessReject;
		  	sessPtr->PBPtr = NULL;
			AcceptNetworkConnection(sessPtr);
		}
	}
	else if (uRec->u.record.UserFlags & 0x0001)
	{
		sessPtr->sessState = AwaitRandWrite;
		auth = (AuthInfoBlkPtr)&(sessPtr->writeBlk.buffer);
		auth->respType = AuthContinue; 		// Send AuthInfo
		auth->authInfo[0] = uRec->random[0];
		auth->authInfo[1] = uRec->random[1];
		WriteToConnection(sizeof(AuthInfoBlk),
						(char *)&(sessPtr->writeBlk.buffer),
						1, 					// eom 
						1, 					// flush
						true, 				// Asynchronously
						(ProcPtr)AuthSendCompletion, // Completion Routine
						(DSPParamBlock *)&(sessPtr->writeBlk.dsp));
	}
	else
	{
		accept->rejectInfo = iacDisabled;	// <44>
		accept->respType = SessReject;		// <44>
	  	sessPtr->PBPtr = NULL;				// <44>
		AcceptNetworkConnection(sessPtr);
	}
}

/*----------------------------------------------------------------------------------------
	AuthSendCompletion is chained from UserRecCompletion.
----------------------------------------------------------------------------------------*/
STATIC void AuthSendCompletion(void)
{
	DSPParamBlock	*dsp;
	NetIPCParams    *sessPtr;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
	
	if ((dsp->ioResult) || (sessPtr->sessState != AwaitRandWrite))
	{
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		sessPtr->sessState = AwaitAuthResp;
		ReadFromConnection(sizeof(AuthInfoBlk),
						  (char *)&(sessPtr->readBlk.authBuf),
						  true, 			// Asynchronously
						  (ProcPtr)AuthRespCompletion, // completion Routine
						  &sessPtr->readBlk.dsp);
	}

} // AuthSendCompletion

/*----------------------------------------------------------------------------------------
	AuthRespCompletion is chained from AuthSendCompletion.
----------------------------------------------------------------------------------------*/
STATIC void AuthRespCompletion(void)
{
	DSPParamBlock *dsp;						// <44>
	AuthInfoBlkPtr 	   auth;				// <44>
	NetIPCParams		*sessPtr;
	IPCReadBlk         *rblk;
	UserRecPbPtr		uRec;
	IPCAcceptBlkPtr    accept;

	dsp = GetA0();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk.dsp);
	auth = (AuthInfoBlkPtr)&(sessPtr->readBlk.authBuf);


	if ((dsp->ioResult) || (sessPtr->sessState != AwaitAuthResp)
	     || (dsp->u.ioParams.actCount == 0) || (auth->respType != AuthInfoResp))
	{
		RemoveNetworkConnection(sessPtr,false);
	}
	else 
	{
		uRec = (UserRecPbPtr)&(sessPtr->miscData.btreeData);
		if ((auth->authInfo[0] == uRec->encryptedRandom[0]) &&
			(auth->authInfo[1] == uRec->encryptedRandom[1]))
		{
			ProcessInform(sessPtr, uRec->u.record.UserFlags); // Authenticated
		}
		else
		{
			accept =  (IPCAcceptBlkPtr)&(sessPtr->writeBlk.buffer);
			accept->rejectInfo = AuthFailure;
			accept->respType = SessReject;
		  	sessPtr->PBPtr = NULL;
			AcceptNetworkConnection(sessPtr);
		}
	}
}


/*----------------------------------------------------------------------------------------
	ProcessInform gets a pending PPCInform for the associated port and completes it, it also
	writes back the session accept response.  If no Informs are pending for the port, PPC Rejects
	the request and sets the rejectInfo to noInforms.
----------------------------------------------------------------------------------------*/
STATIC void ProcessInform(NetIPCParams *sessPtr,unsigned short userFlags)
{
	IPCStartBlk        *sblk;				// <44>
	PPCPortEntryPtr	portPtr;
	PPCInformPBPtr	informPB; 
	IPCAcceptBlkPtr    accept;
	PBWriteResPtr      res;

    
	sblk = (IPCStartBlk *)&(sessPtr->readBlk.buffer);
	portPtr = sessPtr->portEntry;
	accept =  (IPCAcceptBlkPtr)&(sessPtr->writeBlk.buffer);

	if (!(informPB = ServeQueue(&portPtr->informPBQueue)))
	{
		accept->respType = SessReject; 		// <44>  Stuff the message
		accept->rejectInfo = noInforms; 	// <44> No Oustanding Informs
	  	sessPtr->PBPtr = NULL;				// <44>
		AcceptNetworkConnection(sessPtr);
		return;
	}
		
	informPB->sessRefNum = sessPtr->sessRefNum;
	informPB->userData = sblk->userData;	// <44>
	informPB->serviceType = ppcServiceRealTime;
	informPB->requestType = ppcRemoteOrigin;

	res = (PBWriteResPtr)informPB->Reserved;
	if (userFlags & 0x0001)
		res->multiFinder = 0x01;
	else
		res->multiFinder = 0x00;

	if (informPB->portName)
		CopyPortName(&(sblk->reqportName), informPB->portName);
	
	if (informPB->locationName)
		BlockMove((char *)&(sblk->locationName), (char *)(informPB->locationName), sizeof(LocationNameRec));
	
	if(sblk->userName[0] < 31)
	{
		if (sblk->userName[0] == 0)
			BlockMove("\p<Guest>",sessPtr->userName,8); 
		else
			BlockMove((char *)sblk->userName,sessPtr->userName, sblk->userName[0] +1); 
		if (informPB->userName)
			BlockMove((char *)sblk->userName, (informPB->userName), sblk->userName[0] +1); 
	}

	sessPtr->originator = false;			// We did not originate this session.
	
	if (informPB->autoAccept)
	{
		sessPtr->PBPtr = informPB;
		accept->respType = SessAccept; 		// <44> Stuff the message
		AcceptNetworkConnection(sessPtr);
	}
	else
	{
	  	sessPtr->PBPtr = NULL;
		sessPtr->sessState = AwaitAcceptReq;
		CompleteWithResult(informPB,noErr);
	}
}

/*----------------------------------------------------------------------------------------
	RespSendCompletion is chained from AcceptNetworkConnection.
----------------------------------------------------------------------------------------*/
STATIC void RespSendCompletion(void)
{
	DSPParamBlock		*dsp;
    NetIPCParams		*sessPtr;
	PPCAcceptPBPtr		acceptPB;
	PBWriteResPtr		res;
	OSErr               result;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);

	acceptPB = sessPtr->PBPtr;
	res =(PBWriteResPtr)(acceptPB->Reserved);

	if ((acceptPB) && (acceptPB->csCode == PPCRejectCall))
		sessPtr->PBPtr = NULL;
		
	if ((result=dsp->ioResult)  || (acceptPB==nil) || acceptPB->csCode == PPCRejectCall)
	{
		sessPtr->PBPtr = NULL;
		RemoveNetworkConnection(sessPtr,false);
	}
	else
	{
		sessPtr->sessState = DataXferState;
		sessPtr->PBPtr = NULL;
	}
	if (result && acceptPB && acceptPB->csCode == PPCInformCall)
		SetPortInformQue((PPCInformPBPtr)acceptPB, sessPtr->portEntry); // Add the PB back
	else if (acceptPB)
		CompleteWithResult(acceptPB,result?noSessionErr:noErr);
} // RespSendCompletion

/*----------------------------------------------------------------------------------------
	ARepostConnectionListener is chained from ConnectionRequestCompletion.
----------------------------------------------------------------------------------------*/
STATIC void ARepostConnectionListener(void)
{
	RepostConnectionListener(GetA0());
}

STATIC void RepostConnectionListener(DSPParamBlock *dsp)
{
	PPCGlobalParams    *ppcglobPtr;
	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	if (ppcglobPtr->allowIncommingRequests)
	{
		// Incomming Requests are allowed.
    	if ((ListenConnectionRequest(dsp,   true,
								(ProcPtr)ConnectionRequestCompletion)))
		{
#ifdef DEBUG
			Debugger(); // should not happen
#endif
		}
	}
} // RepostConnectionListener

/*----------------------------------------------------------------------------------------
	ListWrite is called to write out the portInfo on an established network connection.  
----------------------------------------------------------------------------------------*/
STATIC void ListWrite(NetIPCParams *sessPtr)
{
	IPCReadBlk         *rblk;				// <44>
	PPCGlobalParams    *ppcglobPtr;
	IPCListReqBlkPtr   list;				// <44>
	Boolean            eom;
	unsigned short     actCount=0, remCount, reqCount;

	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	rblk = (IPCReadBlk *)&(sessPtr->readBlk);
	list = (IPCListReqBlkPtr)&(rblk->buffer);
	remCount = list->requestCount - ppcglobPtr->totalCount;
	if (remCount > MaxListEntries)
		reqCount = MaxListEntries;
	else
		reqCount = remCount;
		
	eom = true;                       		// assume we are going to exhaust
	ppcglobPtr->listContinue = false; 		//  assume we are going to exhaust
	if (!(GetPortNames(ppcglobPtr,
					   &list->portName,		// <44>
					   false,         		// nework request
					   ppcglobPtr->guestUnchecked, // Secure Machine ports or Not
					   ppcglobPtr->listIndex,
					   ppcglobPtr->listBuffer,
					   reqCount,
					   &actCount))) 
    {
		ppcglobPtr->totalCount += actCount;
		if (list->requestCount > ppcglobPtr->totalCount)
		{
			// User can receive some more
			eom = false; // we have some more processing
			ppcglobPtr->listContinue = true;

		 }
	}
	else
		ppcglobPtr->totalCount += actCount;
	
	ppcglobPtr->listIndex += actCount;

	WriteToConnection(sizeof(PortInfoRec) * actCount,
					(char *)ppcglobPtr->listBuffer,
					eom, 					// eom 
					1, 						// flush
					true, 					// Asynchronously
					(ProcPtr)ListWriteCompletion, // Completion Routine
					(DSPParamBlock *)&(sessPtr->writeBlk.dsp));
} // ListWrite

/*----------------------------------------------------------------------------------------
	ListWriteCompletion is chained from ListWrite.
----------------------------------------------------------------------------------------*/
STATIC void ListWriteCompletion(void)
{
	DSPParamBlock		*dsp;
	IPCReadBlk         *rblk;
  	NetIPCParams       *sessPtr, *sessPtr1;
	IPCListReqBlkPtr   list;
	IPCListRespBlkPtr  resp;
	PPCGlobalParams    *ppcglobPtr;

	dsp = GetA0();
	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
    list = (IPCListReqBlkPtr)&(rblk->buffer);

	if (dsp->ioResult)
	{
		// some Error occured
		RemoveNetworkConnection(sessPtr,false);
		ppcglobPtr->listsessPtr = sessPtr1 = ServeQueue(&ppcglobPtr->ListSessQueue);
		if (sessPtr1)
		{
		    // First Lookfor Guest Icon 2/28/90
			list = (IPCListReqBlkPtr)&sessPtr1->readBlk.buffer;
			ppcglobPtr->totalCount = 0;
			ppcglobPtr->listIndex = list->startIndex;

			if (ppcglobPtr->ugFile.refNum != 0)
			{
				getUserRec((UserRecPb *)&(sessPtr1->miscData.btreeData),
						0, // Key ID
						(char *)list->userName,
						(ProcPtr)GuestRecCompletion,
						ppcglobPtr->ugFile.refNum);
			}
			else
			{
				ppcglobPtr->guestUnchecked = false;
				ListWrite((NetIPCParams *)(ppcglobPtr->listsessPtr));
			}
		}
	}
	else if (ppcglobPtr->listContinue)
		ListWrite(sessPtr);   // need some more writing
	else
	{
		resp =  (IPCListRespBlkPtr)&(sessPtr->writeBlk.buffer);
	    resp->respType = ListResp; // Stuff the message
		resp->actualCount = ppcglobPtr->totalCount;
		sessPtr->sessState = AwaitListRespComp;
	    WriteToConnection(sizeof(IPCListRespBlk),
						  (char *)&(sessPtr->writeBlk.buffer),
						  1, // eom 
						  1, // flush
						  true, // Asynchronously
						  (ProcPtr)ListRespCompletion, // Completion Routine
						  &sessPtr->writeBlk.dsp);
	}
} // ListWriteCompletion

/*----------------------------------------------------------------------------------------
	ListRespCompletion is chained from ListWriteCompletion.  We have just completed the writing
	the response to an IPCListPorts request.  If we have another request pending, we begin processing
	that request here.
----------------------------------------------------------------------------------------*/

STATIC void ListRespCompletion(void)
{
	DSPParamBlock *dsp;
	IPCReadBlk         *rblk;
  	NetIPCParams       *sessPtr, *sessPtr1;
	IPCListReqBlkPtr   list;
	PPCGlobalParams    *ppcglobPtr;

	dsp = GetA0();
	ppcglobPtr = (PPCGlobalParams *)getGlobal();
	rblk = (IPCReadBlk *)dsp;
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
	list = (IPCListReqBlkPtr)&(rblk->buffer);

	RemoveNetworkConnection(sessPtr,false);
    
	ppcglobPtr->listsessPtr = sessPtr1 = ServeQueue(&ppcglobPtr->ListSessQueue);
	if (sessPtr1)
	{
		// First Lookfor Guest Icon 2/28/90
		list = (IPCListReqBlkPtr)&sessPtr1->readBlk.buffer;
		ppcglobPtr->totalCount = 0;
		ppcglobPtr->listIndex = list->startIndex;
		if (ppcglobPtr->ugFile.refNum != 0)
		{
			getUserRec((UserRecPb *)&(sessPtr1->miscData.btreeData),
					0, // Key ID
					(char *)list->userName,
					(ProcPtr)GuestRecCompletion,
					ppcglobPtr->ugFile.refNum);
		}
		else
		{
			ppcglobPtr->guestUnchecked = false;
			ListWrite(ppcglobPtr->listsessPtr);
		}
	}
} // ListRespCompletion

/*----------------------------------------------------------------------------------------
	BeginWriteBlock is the first real step in processing of a writePB.  It initializes the reserved
	fields for in the PPCWrite PB, and if we are to write a header, we do so, otherwise we call
	WriteBlockData to append data onto the current block.
----------------------------------------------------------------------------------------*/
STATIC void BeginWriteBlock(NetIPCParamsPtr sessPtr)
{
	PBWriteResPtr          res;				// <44>
	PPCWritePBPtr		   writePB;
	
	// Setup reserved fields in PPCWrite PB to initial values.
	writePB = sessPtr->writePB;
	
	res = (PBWriteResPtr)(writePB->Reserved);
	res->length = writePB->bufferLength;
	res->curBufPos = writePB->bufferPtr;
	if(sessPtr->writeHdr)
	{
		IPCHdrBlk *hdr;						// <44>
		Boolean HeaderOnly;					// True if client just wants the header only written.
		
		// This pisses me off, If I could change the protocol,
		// I could save 12 bytes, and the following 4 lines of code.
		hdr = &sessPtr->writeBlk.buffer.buffer.headerBlk;
		hdr->blockCreator = writePB->blockCreator;
		hdr->blockType = writePB->blockType;
		hdr->userData = writePB->userData;
		HeaderOnly = !writePB->more &&  !writePB->bufferLength;	// usually false!
		sessPtr->writeHdr = !writePB->more;						// for next PPCWrite pb.

		WriteToConnection(sizeof(IPCHdrBlk),
						  (char *)hdr,
						  HeaderOnly,		// eom.
						  HeaderOnly,		// flush.
						  true,				// Asynchronously
						  (ProcPtr)WriteHdrCompletion, // Completion Routine
						  &sessPtr->writeBlk.dsp);
	}
	else
		WriteBlockData(sessPtr);
}


/*----------------------------------------------------------------------------------------
	WriteHdrCompletion is chained from BeginWriteBlock.  Assuming success, and their is data that
	is to follow the header, we call WrtieBlockData to handle that, otherwise we complete their
	PPCWrite call.
----------------------------------------------------------------------------------------*/
STATIC void WriteHdrCompletion(void)
{
	DSPParamBlock *dsp;						// <44>
	NetIPCParamsPtr sessPtr;
	PPCWritePBPtr writePB;

	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);

	if (dsp->ioResult)
	{
		RemoveNetworkConnection(sessPtr,false);
		return;
	}
	
	writePB = sessPtr->writePB;
	if(writePB->bufferLength)
		WriteBlockData(sessPtr);
	else
		CompleteWriteRequest(sessPtr,noErr);
}

/*----------------------------------------------------------------------------------------
	WriteBlockData is responsible for writing the data portion of a PPCBlock.  It breaks a block
	into MaxADSPWrite size chuncks so that ADSP can easily swallow it.
----------------------------------------------------------------------------------------*/
STATIC void WriteBlockData(NetIPCParamsPtr sessPtr)
{
	unsigned short         len; 
	unsigned char          eom;
	PBWriteResPtr          res;			// <44>
	PPCWritePBPtr		writePB;
	
	writePB = sessPtr->writePB;
	res = (PBWriteResPtr)(writePB->Reserved);
	if (res->length > MaxADSPWrite)
	{
		len = MaxADSPWrite;
		eom =false;
	}
	else
	{
		len =  res->length;				// <44>
		eom = !writePB->more;
	}
	sessPtr->writeHdr = !writePB->more;

    WriteToConnection(len,
					  res->curBufPos,
					  eom, 				// eom 
					  eom, 				// flush when we finish a block.
					  true, 			// Asynchronously
					  (ProcPtr)WriteBlockDataCompletion, // Completion Routine
					  &sessPtr->writeBlk.dsp);
}

/*----------------------------------------------------------------------------------------
	WriteBlockDataCompletion is chained from WriteBlockData.  If more data for a given PPCWrite
	is to be written, it calls WriteBlockData, otherwise the Write PB has completed, and it is
	time to complete that, and process any pending writes.
----------------------------------------------------------------------------------------*/
STATIC void WriteBlockDataCompletion(void)
{
	DSPParamBlock *dsp;					// <44>
	NetIPCParamsPtr sessPtr;
	PPCWritePBPtr writePB;
	PBWriteResPtr res;
	
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,writeBlk.dsp);
	writePB = sessPtr->writePB;
	res = (PBWriteResPtr)(writePB->Reserved);

	// Update reserved fields to indicate the amount to be written.
	res->length -= dsp->u.ioParams.actCount;
	res->curBufPos += dsp->u.ioParams.actCount;
	writePB->actualLength += dsp->u.ioParams.actCount;
	
	if (dsp->ioResult)
	{
		RemoveNetworkConnection(sessPtr,false);
		return;
	}

	if(res->length)						// <44> if there is more to write
	{
		WriteBlockData(sessPtr);
	}
	else
	{
		CompleteWriteRequest(sessPtr,noErr);
	}
}

/*----------------------------------------------------------------------------------------
	CompleteWriteRequest is responsible for completing a current write request, and start the next
	if any are pending.
----------------------------------------------------------------------------------------*/
STATIC void CompleteWriteRequest(NetIPCParamsPtr sessPtr,OSErr result)
{
	short sr;
	
	CompleteWithResult(sessPtr->writePB,result);
	
	sr = spl(kNoInterrupts);
	if(sessPtr->writePB = GetWritePB(sessPtr))
	{
		spl(sr);
		BeginWriteBlock(sessPtr);
	}
	else
		spl(sr);
}


/*----------------------------------------------------------------------------------------
	BeginReadBlock
----------------------------------------------------------------------------------------*/

STATIC void BeginReadBlock(NetIPCParamsPtr sessPtr)
{
	PPCReadPBPtr readPB;
	PBReadResPtr	res;					// <44>
    IPCHdrBlk		*hdr;					// <44>
	readPB = sessPtr->readPB;
	// Setup reserved fields in PPCRead PB to initial values.
	res = (PBReadResPtr)(readPB->Reserved);
	res->length = readPB->bufferLength;		// Count down from this length.
	res->curBufPos = readPB->bufferPtr;
	if(!sessPtr->readMore)					// if readHeader.
	{
		ReadFromConnection(sizeof(IPCHdrBlk),
						   (Ptr)&sessPtr->readBlk.buffer,
						   true, 			// Asynchronously
						   (ProcPtr)ReadHdrCompletion, // completion Routine
						   &sessPtr->readBlk.dsp);
	}
	else
	{
		hdr = &sessPtr->readBlk.buffer.buffer.headerBlk;
		readPB->blockCreator = hdr->blockCreator;
		readPB->blockType = hdr->blockType;
		readPB->userData = hdr->userData;
		ReadBlockData(sessPtr);
	}
}

/*----------------------------------------------------------------------------------------
	ReadHdrCompletion is chained from ReadData.
----------------------------------------------------------------------------------------*/
STATIC void ReadHdrCompletion(void)
{
	DSPParamBlock		*dsp;				// <44>
	PPCReadPBPtr		readPB;
	NetIPCParamsPtr		sessPtr;
	PBReadResPtr		res;				// <44>
    IPCHdrBlk			*hdr;
	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk);
	readPB = sessPtr->readPB;
	res = (PBReadResPtr)(readPB->Reserved);
	readPB->more = sessPtr->readMore = !dsp->u.ioParams.eom;	// do we need to read a different header?
	
	if (dsp->ioResult || (dsp->u.ioParams.actCount == 0 && dsp->u.ioParams.eom == 0) &&
						 (sessPtr->ce.state == sClosing || sessPtr->ce.state == sClosed))
	{
		RemoveNetworkConnection(sessPtr,false);
		return;
	}

	hdr = &sessPtr->readBlk.buffer.buffer.headerBlk;
	readPB->blockCreator = hdr->blockCreator;
	readPB->blockType = hdr->blockType;
	readPB->userData = hdr->userData;
	
	if(sessPtr->readMore)
		ReadBlockData(sessPtr);
	else
		CompleteReadRequest(sessPtr,noErr);
}

/*----------------------------------------------------------------------------------------
	ReadBlockData
----------------------------------------------------------------------------------------*/

STATIC void ReadBlockData(NetIPCParamsPtr sessPtr)
{
	PBReadResPtr	res;
	unsigned short	len;
	
	res = (PBReadResPtr)(sessPtr->readPB->Reserved);

	len = res->length < MaxADSPWrite?res->length:MaxADSPWrite;
	if (len) // User Does not want to read zero bytes
	{
		ReadFromConnection(len,
						   res->curBufPos,
						   true, // Asynchronously
						   (ProcPtr)ReadDataCompletion, // completion Routine
						   &sessPtr->readBlk.dsp);
	}
	else
		CompleteReadRequest(sessPtr,noErr);
}

/*----------------------------------------------------------------------------------------
	ReadDataCompletion
----------------------------------------------------------------------------------------*/
STATIC void ReadDataCompletion(void)
{
	DSPParamBlock	*dsp;					// <44>
	PPCReadPBPtr	readPB;
	NetIPCParamsPtr	sessPtr;
	PBReadResPtr	res;


	dsp = GetA0();
	sessPtr = TOP_OF_RECORD_PTR(dsp,NetIPCParams,readBlk);
	readPB = sessPtr->readPB;
	res = (PBReadResPtr)(readPB->Reserved);
	
	res->length -= dsp->u.ioParams.actCount;					// we have this much less to read.
	res->curBufPos += dsp->u.ioParams.actCount;					// next spot to append to clients buffer.
	readPB->actualLength += dsp->u.ioParams.actCount;			// update how much we put into clients buffer.
	readPB->more = sessPtr->readMore = !dsp->u.ioParams.eom;	// do we need to read a different header?
	

	if (dsp->ioResult || (dsp->u.ioParams.actCount == 0 && dsp->u.ioParams.eom == 0) &&
						 (sessPtr->ce.state == sClosing || sessPtr->ce.state == sClosed))
	{
		RemoveNetworkConnection(sessPtr,false);
		return;
	}

	if(res->length && sessPtr->readMore)	// <44>
		ReadBlockData(sessPtr);
	else	// EOM or clients buffer full.
		CompleteReadRequest(sessPtr,noErr);
} // ReadDataCompletion


/*----------------------------------------------------------------------------------------
	CompleteReadRequest is responsible for completing a current read request, and start the next
	if any are pending for this session.
----------------------------------------------------------------------------------------*/
STATIC void CompleteReadRequest(NetIPCParamsPtr sessPtr,OSErr result)
{
	short sr;
	
	CompleteWithResult(sessPtr->readPB,result);
	
	sr = spl(kNoInterrupts);
	if(sessPtr->readPB = GetReadPB(sessPtr))
	{
		spl(sr);
		BeginReadBlock(sessPtr);
	}
	else
		spl(sr);
}

/*----------------------------------------------------------------------------------------
	CopyReadBlk, copies the contents of a DSP parameter block (used for read operations). To a
	another parameter block (used for writing).
----------------------------------------------------------------------------------------*/
STATIC void CopyReadBlk(NetIPCParamsPtr sessPtr)
{
	BlockMove((char *)&(sessPtr->readBlk.dsp),
	(char *)&(sessPtr->writeBlk.dsp),
			  sizeof(DSPParamBlock));

} // CopyReadBlk
