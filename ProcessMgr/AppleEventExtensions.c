/*
	File:		AppleEventExtensions.c

	Contains:	Routines which support AppleEvents as an extension of EPPC.  Specifically,
				it handles automatic translation of standard AppleEvents saeOpen and
				saeQuit to Puppet Strings, and implements the system AppleEvents (e.g.
				aeQuitAll).

	Written by: David Harrison

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

    This file is used in these builds: BigBang

	Change History (most recent first):
	 
		 <6>	 2/18/91	DFH		BAC,WS#BAC 2/15-1:Add hack to make Installer 3.1 work, since
									they expect slightly obsolete four-letter codes in their
									AppleEvents.
		 <5>	  2/9/91	JWM		DFH,#79583:Restart and Shutdown don't work in low memory
									conditions. This involved several of the messages which are sent
									during the processing of a QuitAll message. The fix was to make
									a new version of ProcessMgrHiNewHandle which on failing to get
									memory from the Process Manager's heap would try to get memory
									from the system heap.
		 <4>	  2/1/91	DFH		stb,WS#DFH-910131c:Fixed HandleFeedback to allow for sender's
									being kSystemProcess (i.e. Puppet string translation).
		 <3>	  2/1/91	DFH		BAC,WS#DFH-910131c:saeAnswer keyword parameter with the OSErr is
									now the 'errn', rather than 'errv'.
		 <0>	 9/20/89	DFH		New Today.

*/ 

#pragma segment	kernel_segment

#include <Aliases.h>
#include <AppleEvents.h>
#include <AppleEventsInternal.h>
#include <Errors.h>
#include <EPPC.h>
#include <Files.h>
#include <SegLoad.h>
#include <MFPrivate.h>

#include "Lomem.h"
#include "Data.h"
#include "Glue.h"
#include "Puppet.h"
#include "OSDispatchPrivate.h"
#include "SysMisc.h"
#include "EppcPrivate.h"
#include "AppleEventExtensions.h"

/************************************************************************************
 *								 Utility routines.
 ************************************************************************************/

/* FindKeywordParameter.  Utility routine to return a pointer the parameter having
 * the specified keyword.  Does not return meta-parameters, since we have no use for
 * them yet.  Returns nil if not found.
 */
AETFParameter *
FindKeywordParameter(AETFHeader *pMsg, unsigned long msgSize, unsigned long keyword)
	{
	AETFParameter	*pParam;
	Ptr				limitPtr;
	Boolean			afterMetaParams;

	afterMetaParams = false;
	limitPtr = (Ptr) pMsg + msgSize;
	pParam = (AETFParameter *) ((Ptr) pMsg + sizeof(AETFHeader));
	while ((Ptr) pParam < limitPtr)
		{
		/* Find what we're looking for? */
		if ((pParam->key == keyword) && (afterMetaParams))
			return(pParam);
		
		/* Move to next parameter, by hook or by crook */
		if (pParam->key == aeEndOfMetaDataKeyword)
			{
			(Ptr) pParam += sizeof(KeyWord);
			afterMetaParams = true;
			}
		else
			(Ptr) pParam += pParam->descriptor.dataLength + sizeof(AETFParameter);
		}
	
	return(nil);
	}

/* ExamineDocList.  Given a message that could contain either a single AETFDescriptor or
 * a list of AETFDescriptors, determine the location of the first AETFDescriptor, and
 * the count of AETFDescriptors.  Does the right thing if pMsg == nil.
 */
void
ExamineDocList(AETFHeader *pMsg, unsigned long msgSize, AETFDescriptor **pFirstFile, short *paramCount)
	{
	AETFParameter		*pParam;
	short				parmCount;
	Ptr					pBuff;

	parmCount = 0;
	pBuff = nil;
	if ( (pMsg != nil) &&
		((pParam = FindKeywordParameter(pMsg, msgSize, aeDirectObjectKeyword)) != nil) )
		{
		if (pParam->descriptor.dataType == aeListParamType)
			{
			AETFDescriptorList	*pAEList;
			
			pAEList = (AETFDescriptorList *) &(pParam->descriptor);
			parmCount = pAEList->count;
			pBuff = (Ptr)pAEList + sizeof(AETFDescriptorList) + pAEList->hdrLength;
			}
		else if (pParam->descriptor.dataType == aeAliasParamType)
			{
			parmCount = 1;
			pBuff = (Ptr) pParam + sizeof(AETFParameter);
			}
		}
	
	/* Return pointer to first AETFDescriptor, and count */
	*pFirstFile = (AETFDescriptor *) pBuff;
	*paramCount = parmCount;
	}

/* NextListParam.  Moves to the next AETFDescriptor in a list (assumes no keyword). */
void
NextListParam(AETFDescriptor **ppParam)
	{
	AETFDescriptor	*pParam;
	Ptr				pBuff;
	
	/* Bump pointer by size of data */
	pParam = *ppParam;
	pBuff = (Ptr) pParam + sizeof(AETFDescriptor) + pParam->dataLength;
	
	/* Check even alignment */
	assert(WORD_ALIGNED((unsigned long) pBuff));

	*ppParam = (AETFDescriptor *) pBuff;
	}

/*************************************************************************************
 * The following routines convert the "standard" subset of AppleEvents to puppet
 * strings in the event the receiver does not understand EPPC.  Currently, the
 * translations we support are saeOpenDocumentMsgID and saeQuitMsgID.
 *
 * Translation works as follows.  When we install the puppet instructions, we include
 * the MFmsgBlk in the p_puppetvars, and post the return receipt, if any.  When
 * the puppet string is over (canceled or completed), postTranslationResult is called
 * with the MFmsgBlk, returning the result in an AppleEvent back to the original
 * sender.  Simple, eh?
 *
 * If the translation is canceled (e.g. the target's file menu Open item is disabled),
 * we leave the target as the foreground process, but a message is sent back to the
 * originator.
 ************************************************************************************/

/* Handy macros */	
#define SendOpenInstruction(pMsgBlk)		SendFileInstruction(instrOpen, pMsgBlk)
#define SendQuitInstruction(pMsgBlk)		SendGenericInstruction(instrQuit, pMsgBlk)

/* SendInstructions.  Given a completed instruction list and message block, install
 * them on the target process.  Makes sure that target will be the frontmost
 * application, since this is a requirement of puppet strings.
 */
OSErr
SendInstructions(EventListHdl eventListH, MFmsgBlkPtr msgBlk)
	{
	PEntryPtr	pProc;
	OSErr		switchError;

	/* Lock on target */
	pProc = PEntryFromPSN(&msgBlk->targetmfid.localPSN);
	assert(pProc != nil);
	
	/* Arrange to have him come forward. */
	if ( (pProc != pFrontProcess) && ((switchError = SetFrontProcess(&pProc->p_serialNumber)) != noErr) )
		return(switchError);
	
	/* Install the instructions */
	if ((switchError = CoreRequestScratchSwitchTask(pProc, eventListH, nil, 0, msgBlk)) != noErr)
		return(switchError);
	
	/* If the target is already frontmost, we have to put him in the mood to look at the
	 * puppet string.
	 */
	if (pProc == pFrontProcess)
		{
		CancelSleep(pProc);
		pProc->p_state = PRPUPPET;
		}
	
	return(noErr);
	}
 
/* SendGenericInstruction.  Sends a puppet string instruction that requires no parameters. */
OSErr
SendGenericInstruction(short theInstruction, MFmsgBlkPtr msgBlk)
	{
	EventListHdl	eventListH;
	EventListPtr	eventListP;
	OSErr			error;
	
	/* Make a new event list handle */
	if ((eventListH = GMBlk(SIZEOF_EVENTLIST_HDR+sizeof(EventRecord), &error)) == nil)
			return(error);
	eventListP = *eventListH;

	/* Fill in the details */
	eventListP->offset = SIZEOF_EVENTLIST_HDR;
	eventListP->count = 1;
	eventListP->events[0].what = app4Evt;
	eventListP->events[0].message = theInstruction << 24;
	
	/* Install the instructions, making sure the application will be frontmost */
	if ((error = SendInstructions(eventListH, msgBlk)) != noErr)
		DisposHandle(eventListH);
	
	return(error);
	}

/* AppFileAndDocList.  Convert an AppFile file specification into the AETFDescriptor
 * equivalent, and append this to the existing DocList handle.
 */
OSErr
AppFileAndDocList(AppParmRecHdl hAPH, unsigned long *pCurrOffset, Handle hDocList)
	{
	AppFile				*pAppFile;
	FSSpec				fileSpec;
	AETFDescriptor		parmDesc;
	AliasHandle			hAlias;
	OSErr				err;
	
	/* Make file spec for use with NewAliasMinimal */
	HLock(hAPH);
	pAppFile = ((Ptr) *hAPH) + *pCurrOffset;
	err = FSMakeFSSpec(pAppFile->vRefNum, 0, &(pAppFile->fName), &fileSpec);
	
	/* Update offset even in error case */
	*pCurrOffset += SizeOfThisAppFile(pAppFile);
	HUnlock(hAPH);
	
	/* Bail if error */
	if (err != noErr)
		return(err);
	
	/* Make a new alias record */
	if ((err = NewAliasMinimal(&fileSpec, &hAlias)) != noErr)
		return(err);

	/* Append new alias info to existing list.
	 * NOTE: The SetHandleSize in the error case assumes that the block shrinks
	 * at the top.
	 */
	parmDesc.dataType = aeAliasParamType;
	parmDesc.dataLength = GetHandleSize(hAlias);
	if ((err = PtrAndHand(&parmDesc, hDocList, sizeof(AETFDescriptor))) == noErr)
		if ((err = HandAndHand(hAlias, hDocList)) != noErr)
			SetHandleSize(hDocList, GetHandleSize(hDocList) - sizeof(AETFDescriptor));
	
	DisposHandle(hAlias);
	return(err);
	}

/* FileIDToAppFile.  Convert an AppleEvent file specification to one suitable for
 * APPARMHANDLE or puppet stringing.  Does not create a working directory, but
 * returns the vRefNum and dirID so one can be opened later.
 */
OSErr
FileIDToAppFile(AETFDescriptor *pFileID, AppFile *pAppFile, short *pVol, long *pDirID)
	{
	AliasHandle			hAlias;
	Boolean				aliasChanged;
	FSSpec				fileSpec;
	HFileParam			fInfoRec;
	OSErr				err;
	
	/* Can do nothing if the spec is not an alias */
	if (pFileID->dataType != aeAliasParamType)
		return(paramErr);
	
	/* Make an AliasHandle out of the spec */
	if ((err = PtrToHand((AliasPtr) ((Ptr) pFileID + sizeof(AETFDescriptor)), &hAlias, pFileID->dataLength)) != noErr)
		return(err);
	
	/* Distill a file spec out of the AliasHandle */
	err = ResolveAlias(nil, hAlias, &fileSpec, &aliasChanged);
	DisposHandle(hAlias);
	if (err != noErr)
		return(err);

	/* Return the file location info */
	pAppFile->vRefNum = 0;
	*pVol = fileSpec.vRefNum;
	*pDirID = fileSpec.parID;
	BlockMove(&(fileSpec.name), &(pAppFile->fName), Length(&(fileSpec.name))+1);
	
	/* Version is no longer used (it was an MFS concept), so zero it. */
	pAppFile->versNum = 0;

	/* Get the type. */
	fInfoRec.ioNamePtr = &(fileSpec.name);
	fInfoRec.ioVRefNum = fileSpec.vRefNum;
	fInfoRec.ioDirID = fileSpec.parID;
	fInfoRec.ioFDirIndex = 0;
	fInfoRec.ioCompletion = nil;
	if ((err = PBHGetFInfo(&fInfoRec, SyncHFS)) == noErr)
		pAppFile->fType = fInfoRec.ioFlFndrInfo.fdType;

	return(err);
	}
	
/* SendFileInstruction.  Sends a puppet string with a file spec to the given process.
 * The instruction must correspond to a menu command in the target app that causes that
 * app to bring up SFGetFile.  For example, instrOpen corresponds to the "File" menu 
 * "OpenÉ" (et al) item, which typically causes the app to call SFGetFile.
 * NOTE: A file instruction can not be the last in the instruction list!  This is
 * because the puppet machinery shuts down when the last instruction is popped (in
 * GetNextPuppetEvent()), but a file instruction is not really finished until later.
 * The patch to SFGetFile (IsForcedOpen()) still needs to hand the file spec to the
 * application.  We tack on a nullEvent as an extra instruction to keep the list alive.
 */
OSErr
SendFileInstruction(short instruction, MFmsgBlkPtr msgBlk)
	{
	short					evtCount;
	Size					theLength;
	AETFDescriptor			*pAEFileSpec;
	EventListHdl			eventListH;
	EventListPtr			eventListP;
	EventRecord				*pEvent;
	OSErr					error;
		
	/* Do a little research */
	ExamineDocList((AETFHeader *) msgBlk->addrOfMsg, msgBlk->eppcMsgBlk.msgLength, &pAEFileSpec, &evtCount);
	if (evtCount == 0)
		return(fnfErr);
	
	/* Make a new event list handle big enough for the instructions */
	evtCount++;
	theLength = SIZEOF_EVENTLIST_HDR + (evtCount * sizeof(EventRecord));
	if ((eventListH = GMBlk(theLength, &error)) == nil)
		return(error);

	/* Adjust addrOfMsg to point to the first file to open */
	msgBlk->addrOfMsg = (Ptr) pAEFileSpec;
	
	/* Fill in the list header info */
	eventListP = *eventListH;
	eventListP->offset = SIZEOF_EVENTLIST_HDR;
	eventListP->count = evtCount;
	
	/* Fill in the file instruction(s) */
	pEvent = &(eventListP->events[0]);
	while(--evtCount)
		{
		pEvent->what = app4Evt;
		pEvent->message = (instruction << 24);
		pEvent++;
		}
	
	/* Fill in the place holder instruction, a null event */
	pEvent->what = nullEvent+evtIsUnimportant;

	/* Send the thing off */
	if ((error = SendInstructions(eventListH, msgBlk)) != noErr)
		DisposHandle(eventListH);
	
	return(error);
	}

/* TranslateAppleEvent.  See whether the high-level event is a translatable AppleEvent.
 * If so, try to convert it to puppet strings.  This routine is called when it appears
 * that the only connection problem is that the receiver is not capable of EPPC.  The
 * err parameter is the address of the OSErr that EPPC will return to the caller of
 * PostHighLevelEvent.  We return the result of the translation attempt there, unless
 * the event is not one that we like to translate (leaving it alone in that case lets 
 * the PostHighLevelEvent caller get the usual connection error provided by EPPC/PPC).
 */
void
TranslateAppleEvent(MFmsgBlkPtr msgBlk, OSErr *err)
	{
	PEntryPtr				pDestProc;
	HighLevelEventRecord	*pAEvent;
	u_long					theCommand;
	OSErr					sendError;
	
	/* Is this an AppleEvent? */
	pAEvent = (HighLevelEventRecord *) &(msgBlk->eppcMsgBlk.theMsgEvent);
	if (pAEvent->mClass != standardAppleEventMsgClass)
		return;
	
	/* Can't do it if we're switching (or planning on it). */
	if (coercionState != CS_DONE)
		{
		*err = protocolErr;
		return;
		}
	
	/* Can't do it if destination is not a process that can come to the foreground, or
	 * is the current process (requirements of puppet strings).
	 */
	pDestProc = PEntryFromPSN(&msgBlk->targetmfid.localPSN);
	assert(pDestProc != nil);
	if ( (pDestProc == nil) || ((pDestProc->p_taskmode & modeOnlyBackground) != 0) || (pDestProc == pCurrentProcess) )
		return;
	
	/* See if it's one of the translatable set */
	if ((theCommand = pAEvent->mID) == saeQuitMsgID)
		sendError = SendQuitInstruction(msgBlk);

	else
		{
		/* Look for an AppleEvent that has a file spec. */
		if ((theCommand == saeOpenDocumentMsgID))
			sendError = SendOpenInstruction(msgBlk);
		
		else return;
		}
	
	/* We get here only if we tried to load the puppet instructions.  SendError
	 * holds the result.  If it worked, send a return receipt.  Otherwise, dump
	 * the message buffer.
	 */
	if (sendError == noErr)
		{
		if ((msgBlk->eppcMsgBlk.postingOptions & nReturnReceipt) != 0)
			postReturnReceipt(msgBlk, true);
		}
	else
		RelMsgEventBuffer(msgBlk);
	
	*err = sendError;
	}

/* postTranslationResult.  Pass the word back to the process that sent an AppleEvent
 * needing translation, now that the result is known.  Performs any necessary cleanup.
 * NOTE: Ideally, we want this message to look like it came from the process, not the
 * system, because it is really the last step in acting like the destination was
 * EPPC-aware.  Currently, though, it is done in SystemMode because PPC toolbox
 * requires that the sender have a port.  Also, the "sender" may be dead at this point.
 */
void
postTranslationResult(MFmsgBlkPtr mfMsgBlk, OSErr theResult)
	{
	/* Send AppleEvent with result back to originator (frees message block) */
	postResult(mfMsgBlk, theResult, &pCurrentProcess->p_serialNumber);
	}

/*************************************************************************************
 * The following routines translate from an APPPARMHANDLE to an saeOpenDocumentMsgID/
 * saePrintDocumentMsgID AppleEvent, or vice versa.  This is necessary when a
 * non-AppleEvent application is launching one that is, or vice versa.  These are just
 * utility routines for other modules (like SegmentLoaderPatches.c) to call.
 ************************************************************************************/
	
/* AEParmToAppParmHandle.  Convert the given AppParameters from AppleEventness into an
 * equivalent AppParmRecHdl.  Also sets up the p_appWDList for later consumption by
 * OpenAppWDs.  Note that we provide a trivial AppParmRecHdl in the case that there is
 * no DocList.  This is to accommodate applications that assume APPPARMHANDLE != nil.
 * NOTE: This assumes that the DocList will not be moved by the heap calls we make.
 * Currently, this is met because we're allocating in the new app's heap, which didn't
 * exist when the DocList was made.
 * NOTE: Locking the AppParmHandle is done explicitly for MacWrite 4.5 (and 4.6?) and
 * should someday be removed.
 */
AppParmRecHdl
AEParmToAppParmHandle(AppParametersPtr pAEParm, PCB **hPCB)
	{
	u_long					theCommand;
	AETFDescriptor			*pFileID;
	short		 			parmCount;
	short					theInstruction;
	AppParmRec				**hAPH;
	AppFile					*pAppFile;
	AppWDRecPtr				pWDInfoRec;
	AppWDListHdl			hWDInfo;
#define SIZEOF_MINAPPFILE	(sizeof(AppFile) - (sizeof(Str255) - sizeof(Str63)))
	
	/* So error recovery works correctly */
	hAPH = nil;
	hWDInfo = nil;
	
	/* Anything at all? */
	if (pAEParm == nil)
		goto ErrorRecovery;
		
	/* Is the AppleEvent something we can translate? */
	theCommand = ((HighLevelEventRecord *) (&pAEParm->theMsgEvent))->mID;
	if ((theCommand == saeOpenDocumentMsgID) || (theCommand == saeLaunchedWithoutDocs))
		theInstruction = appOpen;
	else if (theCommand == saePrintDocumentMsgID)
		theInstruction = appPrint;
	else
		goto ErrorRecovery;
		
	/* Get address of first file spec and count of specs */
	parmCount = 0;
	if (theCommand != saeLaunchedWithoutDocs)
		ExamineDocList( (AETFHeader *) ((Ptr) pAEParm + sizeof(AppParameters)), pAEParm->messageLength, &pFileID, &parmCount);

	/* Create an AppParmRecHdl as a relocatable block. */
	if ( (hAPH = NewAppParmHandle(sizeof(AppParmRec) + (parmCount * SIZEOF_MINAPPFILE))) == nil )
		goto ErrorRecovery;
		
	/* Set up the headers (assume block was zeroed by NewAppParmHandle) */
	(*hAPH)->message = theInstruction;
	
	/* Dice and slice each parameter */
	if (parmCount != 0)
		{
		short			goodCount;
		
		/* Create the parallel WD structure */
		if ( (hWDInfo = (AppWDListHdl) NewHandleClear(sizeof(AppWDList) + (parmCount * sizeof(AppWDRec)))) == nil )
			goto ErrorRecovery;
	
		/* Now translate each entry.  Save WD info in parallel structure */
		HLock(hWDInfo);
		pAppFile = &((*hAPH)->appFiles[0]);
		pWDInfoRec = &((*hWDInfo)->wdlDirectories);
		goodCount = 0;
		do
			{
			OSErr		err;
			
			/* Translate this entry */
			if ((err = FileIDToAppFile(pFileID, pAppFile, &pWDInfoRec->awdVolume, &pWDInfoRec->awdDirID)) == noErr)
				{
				goodCount++;
				NextAppFile(&pAppFile);
				pWDInfoRec++;
				}

			/* Call it a list if the heap pooped out */
			else if (err == memFullErr)
				break;

			/* Move on */
			NextListParam(&pFileID);
			} while (--parmCount);
		
		HUnlock(hWDInfo);
		
		/* Did we wash out? */
		if (((*hWDInfo)->wdlCount = (*hAPH)->count = goodCount) == 0)
			goto ErrorRecovery;
		
		/* Trim AppParmHandle back to just the needed size.
		 * NOTE: Assumes this can be done with the handle locked.
		 */
		SetHandleSize(hAPH, (Ptr) pAppFile - (Ptr) *hAPH);
		assert(MEMERROR == noErr);
		}
	else
		hWDInfo = nil;
	
	/* Finally, the point of all this */
	(*hPCB)->p_appWDList = hWDInfo;
	return(hAPH);

	/* Error handling code conveniently all in one place */
ErrorRecovery:
	if (hAPH != nil)
		DisposHandle(hAPH);
	
	if (hWDInfo != nil)
		DisposHandle(hWDInfo);
	
	/* Try to return trivial AppParmRecHdl) */
	(*hPCB)->p_appWDList = nil;
	return(NewAppParmHandle(sizeof(AppParmRec)));
	}

/* AppParmHandleToAEParm.  Build an AppParameters structure equivalent of the specified
 * AppParmRecHdl.  If hAPH is nil or purged, or the count is 0, an saeLaunchedWithoutDocs
 * AppleEvent is sent so the new app knows there are no documents.
 * NOTE: Caller should make sure the current heap is set correctly!!
 */
Handle
AppParmHandleToAEParm(AppParmRecHdl hAPH)
	{
	short						parmCount, theInstruction;
	AppParametersPtr			pAEParm;
	long						theCommand;
	u_size						msgSize;
	AppParameters				**hAEParm;
	
	/* Figure out what the command is, how many files there are, and the initial message size */
	if ( (hAPH == nil) || (*hAPH == nil) || ((parmCount = (*hAPH)->count) == 0) )
		{
		theCommand = saeLaunchedWithoutDocs;
		msgSize = 0;
		parmCount = 0;
		}
	else
		{
		theInstruction = (*hAPH)->message;
		if (theInstruction == appOpen)
			theCommand = saeOpenDocumentMsgID;
		else if (theInstruction == appPrint)
			theCommand = saePrintDocumentMsgID;
		else
			return(nil);
	
		/* This will grow as we add AETFDescriptors */
		msgSize = sizeof(AppleEventDocMsg);
		}
		
	/* Try to allocate the required amount of memory from the current heap */
	if ((hAEParm = (AppParameters **) NewHandleClear(sizeof(AppParameters) + msgSize)) == nil)
		return(nil);
	
	/* Build the message */
	if (msgSize != 0)
		{
		unsigned long	currOffset;
		unsigned long	goodCount;
		
		/* Lay down the AETFDescriptors */
		goodCount = 0;
		currOffset = sizeof(AppParmRec);
		while (parmCount--)
			{
			if (AppFileAndDocList(hAPH, &currOffset, (Handle) hAEParm) == noErr)
				goodCount++;
			}
		
		/* Fill in the message, or switch to saeLaunchedWithoutDocs if nothing converted */
		if (goodCount != 0)
			{
			AppleEventDocMsg	*pMsg;
			AETFDescriptorList	*pListHdr;
			
			msgSize = GetHandleSize(hAEParm) - sizeof(AppParameters);
			pMsg = (AppleEventDocMsg *) ((Ptr) *hAEParm + sizeof(AppParameters));
			GenericAEMessage(&pMsg->messageHeader);
			pMsg->metaDataMark = aeEndOfMetaDataKeyword;
			SetAEParmHeader((AETFParameter *) &pMsg->listParam, aeDirectObjectKeyword, aeListParamType, msgSize - sizeof(AppleEventDocMsg) + LISTEXTRA);
			pListHdr = &(pMsg->listParam.list);
			pListHdr->count = goodCount;
			pListHdr->hdrLength = 0;
			}
		else
			{
			theCommand = saeLaunchedWithoutDocs;
			msgSize = 0;
			}
		}

	/* Set the message size */
	pAEParm = *hAEParm;
	pAEParm->messageLength = msgSize;
		
	/* Fill in the HighLevelEventRecord */
	SetAppleEvent(theCommand, (HighLevelEventRecord *) &pAEParm->theMsgEvent);

	/* Return what we have made */
	return(hAEParm);
	}

/*************************************************************************************
 * The following routines implement the system AppleEvents.  We support is aeQuitAll,
 * aeCreatorType, aeRestart, and aeShutDown.  We do the aeQuitAll ourselves.  The
 * others we pass on to Finder.
 ************************************************************************************/

/* SendSystemQuit.  Utility subroutine to send aeQuit to specified process, based on
 * pSystemQuitAllMsg.
 * NOTE: This uses the refcon from the original aeQuitAll high-level event.  That way,
 * the target will naturally echo the proper refcon in its response.  If you decide to
 * use a different refcon, you have to be sure to restore it in any messages passed
 * through to the aeQuitAll initiator from a target (e.g. in HandleFeedback).
 */
OSErr
SendSystemQuit(PEntryPtr pDest)
	{
	OSErr					result;
	MFmsgBlkPtr				pMsgBlk;
	HighLevelEventRecord	theEvent;

	pMsgBlk = pSystemQuitAllMsg;
	pMsgBlk->targetmfid.localPSN = pDest->p_serialNumber;

	SetAppleEvent(saeQuitMsgID, &theEvent);

	(void) BeginSystemMode();
	result = PostHighLevelEvent((EventRecord *) &theEvent, (u_long) &pDest->p_serialNumber, pMsgBlk->eppcMsgBlk.userRefcon, pMsgBlk->addrOfMsg, pMsgBlk->eppcMsgBlk.msgLength, receiverIDisPSN);
	(void) EndSystemMode();
	if (result == noErr)
		(void) SetFrontProcess(&pDest->p_serialNumber);

	return(result);
	}

/* ContinueQuitAll.  Initiate or continue the shutting down of processes.  Sends a
 * Quit AppleEvent to the next eligible process.  Does all foreground processes
 * except Finder before starting in on the background ones (because if the user
 * cancels, it will be easier for him to restart just the foreground apps).
 * We want the Quit messages to look like they came from the system, so any result
 * messages can be ignored.
 */
void
ContinueQuitAll(void)
	{
	PEntryPtr		pProc, pKillerProc;
	LayerPtr		pLayer;
	MFmsgBlkPtr		pMsgBlk;

	assert(pSystemQuitAllMsg != nil)
	
	/* Cache some costly info.  Also, we want pMsgBlk to be valid even after we
	 * MUST nil the pSystemQuitAllMsg global.
	 */
	pMsgBlk = pSystemQuitAllMsg;
	pKillerProc = PEntryFromPSN(&(pMsgBlk->sendermfid.localPSN));
	assert(pKillerProc != nil);
	
	/* Look for foreground job to wipe */
	pProc = pFrontProcess;
	for (;;)
		{	
		/* OK to do right now if pProc is neither killer nor the Finder. */
		if ((pProc != pKillerProc) && (pProc != pShellProcess))
			{
			(void) SendSystemQuit(pProc);
			return;
			}
		
		/* Try to get next layer down.  Exit if we hit bottom. */
		if ((pLayer = LGetNextLayer(pProc->p_layer, false)) == nil)
			break;
		
		pProc = LayerOwner(pLayer);
		}
 	
	/* Foregrounders are gone, now try the background */
	pProc = pProcessList;
	while (pProc != nil)
		{
		if ( (pProc->p_state != PRNULL)
			&& (pProc != pKillerProc)
			&& (pProc != pShellProcess) )
			{
			assert((pProc->p_taskmode & modeOnlyBackground) != 0);
			if (SendSystemQuit(pProc) == noErr)
				return;
			pProc->p_state = PRNULL;
			}
			
		pProc = pProc->p_NextProcess;
		}
	
	/* Now do Finder, if he's not the one that started this whole thing */
	if ((pShellProcess != pKillerProc) && (pShellProcess != nil))
		{
		(void) SendSystemQuit(pShellProcess);
		return;
		}

	/* Everyone's gone!  Tell grim reaper the good news.  We want this message
	 * to look like it came from the system.
	 */
	assert(pMsgBlk == pSystemQuitAllMsg);
	pSystemQuitAllMsg = nil;
	postResult(pMsgBlk, noErr, nil);
	}

/* CancelQuitAll.  Cancel the system quit initiated by an application.  This is called
 * when either a) the intended victim sent a refusal, b) a high-level switch out of an
 * intended victim is occurring, or c) when the initiator himself has died.  We don't
 * have to worry about reviving background jobs, since they are not frozen until after
 * all foreground jobs have quit.
 * If an intendedVictim is specified, the QuitAll is being cancelled by a switch
 * (case b), and we need to send the result message to the originator.  We want this
 * message to look like it came from the system.  In the other cases a message is not
 * necessary: in case (a) the refusnik's message has already been relayed; in case (c)
 * the originator is too dead to care.
 */
void
CancelQuitAll(ProcessSerialNumberPtr intendedVictim)
	{
	MFmsgBlkPtr		msgBlk;

	msgBlk = pSystemQuitAllMsg;
	pSystemQuitAllMsg = nil;
	
	/* Send result only if caller wanted us to */
	if (intendedVictim == nil)
		RelMsgEventBuffer(msgBlk);
	else
		postResult(msgBlk, userCanceledErr, intendedVictim);
	}

/* HandleSystemQuit.  Make all applications other than the current one quit or go idle.
 * This puts the system in a quiescent state, useful prior to shutdown or major surgery.
 */
OSErr
HandleSystemQuit(MFmsgBlkPtr msgBlk)
	{
	/* make sure there will still be a user interface when all is done */
	if ((pCurrentProcess->p_taskmode & modeOnlyBackground) != 0)
		return(appIsDaemon);
		
	/* make sure no one else is shutting down already */
	if (pSystemQuitAllMsg != nil)
		return(tooManyReqs);
	
	/* set the scythe to swingin' */
	pSystemQuitAllMsg = msgBlk;
	ContinueQuitAll();
	return(noErr);
	}

/* AnswerWasFromQuitAll.  Determine whether the specified message is a reply from the
 * most recently targeted process in a QuitAll.  Mostly, allow for the message to
 * have been sent in system mode, since we PostResult does that.
 */
Boolean
AnswerWasFromQuitAll(register MFmsgBlkPtr pMsgBlk)
	{
	AETFParameter	*pParm;
	
	/* Check whether there is even a quitall in progress */
	if (pSystemQuitAllMsg == nil)
		return(false);
		
	/* We know right away if the sender has the same PSN as the most recent intended victim */
	if (EqualPSN(&pSystemQuitAllMsg->targetmfid.localPSN, &pMsgBlk->sendermfid.localPSN))
		return(true);
	
	/* The only other possibility is that we are seeing our own result message for the
	 * quit event we translated during a quitall.  In this case, the result message will
	 * contain the ProcessSerialNumber of the application that was being translated for.
	 */
	if (EqualPSNConst(kSystemProcess, &pMsgBlk->sendermfid.localPSN))
		{
		pParm = FindKeywordParameter((AETFHeader *) pMsgBlk->addrOfMsg, pMsgBlk->eppcMsgBlk.msgLength, aeProcessKeyword);
		if ( (pParm != nil)
			&& (pParm->descriptor.dataType == aeProcessParamType)
			&& (EqualPSN((ProcessSerialNumber *) ((Ptr) pParm + sizeof(AETFParameter)), &pSystemQuitAllMsg->targetmfid.localPSN)) )		
			return(true);
		}

	return(false);
	}

/* HandleFeedback.  Deal with a message returned by a previous destination.  The only
 * responses we care about are negative ones from intended victims of saeQuitMsgID
 * (we cancel the aeQuitAll).
 */
OSErr
HandleFeedback(MFmsgBlkPtr pMsgBlk)
	{
	AETFParameter	*pParm;
	PEntryPtr		pDestProc;

	/* Is there a QuitAll in progress? */
	if (AnswerWasFromQuitAll(pMsgBlk))
		{
		/* Cancel the QuitAll if the process is refusing to die. */
		pParm = FindKeywordParameter((AETFHeader *) pMsgBlk->addrOfMsg, pMsgBlk->eppcMsgBlk.msgLength, keyErrorNumber);
		if ( (pParm != nil)
			&& (pParm->descriptor.dataType == aeLongintParamType)
			&& ((*(long *) ((Ptr) pParm + sizeof(AETFParameter))) != noErr) )
			{
			/* Make Installer 3.1 work.  That product was shipped before 7.0 went final, but
			 * relied on 7.0 features such as AppleEvents.  In the mean time, some four-letter
			 * codes changed, including the keyword for params holding an OSErr, and the
			 * keyword and type for params holding a ProcessSerialNumber.
			 */
			if (((pDestProc = PEntryFromPSN(&pSystemQuitAllMsg->sendermfid.localPSN)) != nil) &&
				(pDestProc->p_signature == 'cfbj'))
				{
				/* Convert (only?) keyErrorNumber parameter keyword to 'errv' */
				pParm->key = 'errv';

				/* Convert (only?) aeProcessKeyword parameter keyword and type to 'proc' */
				pParm = FindKeywordParameter((AETFHeader *) pMsgBlk->addrOfMsg, pMsgBlk->eppcMsgBlk.msgLength, aeProcessKeyword);
				if (pParm != nil)
					{
					pParm->key = 'proc';
					if (pParm->descriptor.dataType == aeProcessKeyword)
						pParm->descriptor.dataType = 'proc';
					}
				}
				
			pMsgBlk->targetmfid.localPSN = pSystemQuitAllMsg->sendermfid.localPSN;
			postMsg(pMsgBlk);
			CancelQuitAll(nil);
			return(noErr);
			}
		}

	RelMsgEventBuffer(pMsgBlk);
	return(noErr);
	}

/* HandleSystemMessage.  Handle a message ostensibly addressed to "the system".
 * If we implement the message, do it.  Otherwise, return an unimpErr so callers
 * from the future know where we stand.
 * NOTE: We just pass aeCreatorType, aeRestart, and aeShutDown straight on to Finder,
 * but having programmers address it to us (rather than Finder) gives us the option of
 * doing something meaningful in the future.
 */
void
HandleSystemMessage(MFmsgBlkPtr pMsgBlk, OSErr *err)
	{
	HighLevelEventRecord	*pAEvent;
	u_long					theCommand;
	OSErr					resultVal;
	
	/* Is this an AppleEvent? */
	resultVal = unimpErr;
	pAEvent = (HighLevelEventRecord *) &(pMsgBlk->eppcMsgBlk.theMsgEvent);
	if (pAEvent->mClass == standardAppleEventMsgClass)
		{
		theCommand = pAEvent->mID;
		
		/* A dose of morphine, perhaps? */
		if (theCommand == aeQuitAll)
			{
			resultVal = HandleSystemQuit(pMsgBlk);
			}
		
		/* Response to a message we sent earlier? */
		else if (theCommand == saeAnswer)
				{
				resultVal = HandleFeedback(pMsgBlk);
				}
		
		/* Look for events handled by Finder */
		else if ( (theCommand == aeCreatorType) ||
					(theCommand == aeRestart) ||
					(theCommand == aeShutDown) )
				{
				if ((pShellProcess != nil) && (pShellProcess != ((Ptr) -1)) && (ShellWasFinderType))
					{
					pMsgBlk->targetmfid.localPSN = pShellProcess->p_serialNumber;
					pAEvent->mClass = FINDERS_TYPE;
					postMsg(pMsgBlk);
					*err = noErr;
					return;
					}
				}
		}

	/* If we were able to do anything, send a return receipt. */
	if (resultVal == noErr)
		{
		if ((pMsgBlk->eppcMsgBlk.postingOptions & nReturnReceipt) != 0)
			postReturnReceipt(pMsgBlk, true);
		}
	
	*err = resultVal;
	}

/* postResult.  Send OSErr back to sender of given message, and free the message. */
void
postResult(MFmsgBlkPtr mfMsgBlk, OSErr theResult, ProcessSerialNumberPtr pIntendedPSN)
	{
	HighLevelEventRecord	theEvent;
	unsigned long			msgRefcon;
	ProcessSerialNumber		receiverID;
	PEntryPtr				pDestProc;
	unsigned long			errorKeyword, processKeyword, processType;
	MyAppleEventReply		mBuff;
	
	/* Prepare the parameters for send (before freeing buffer!) */
	receiverID = mfMsgBlk->sendermfid.localPSN;
	msgRefcon = mfMsgBlk->eppcMsgBlk.userRefcon;

	/* Fill in the high-level event record */
	SetAppleEvent(saeAnswer, &theEvent);
	
	/* Fill in the message. */
	GenericAEMessage(&mBuff.basicReply.messageHeader);
	mBuff.basicReply.metaDataMark = aeEndOfMetaDataKeyword;
			
	/* Make Installer 3.1 work.  That product was shipped before 7.0 went final, but
	 * relied on 7.0 features such as AppleEvents.  In the mean time, some four-letter
	 * codes changed, including the keyword for params holding an OSErr, and the
	 * keyword and type for params holding a ProcessSerialNumber.
	 */
	errorKeyword = keyErrorNumber;
	processKeyword = aeProcessKeyword;
	processType = aeProcessParamType;
	if (((pDestProc = PEntryFromPSN(&receiverID)) != nil) &&
		(pDestProc->p_signature == 'cfbj'))
		{
		errorKeyword = 'errv';
		processKeyword = 'proc';
		processType = 'proc';
		}

	SetAEParmHeader(&mBuff.basicReply.errorCodeHdr, errorKeyword, aeLongintParamType, sizeof(long));
	mBuff.basicReply.errorValue = (long) theResult;
	SetAEParmHeader(&mBuff.processHdr, processKeyword, processType, sizeof(ProcessSerialNumber));
	if (pIntendedPSN != nil)
		mBuff.process = *pIntendedPSN;
	else
		SetPSN(kNoProcess, &mBuff.process);
	
	/* Release the buffer (to free some memory before the send), and send the EPPC. */
	RelMsgEventBuffer(mfMsgBlk);
	(void) BeginSystemMode();
	(void) PostHighLevelEvent((EventRecord *) &theEvent, (unsigned long) &receiverID, msgRefcon, &mBuff, sizeof(MyAppleEventReply), receiverIDisPSN);
	(void) EndSystemMode();
	}
