/*
	File:		AppleEventExtensions.h

	Contains:	Interfaces to routines in AppleEventExtensions.c.  Also contains some
				AppleEvent Transport Format (AETF) information that we would ideally
				not know about.  Unfortunately, the AppleEvent Manager was not ready
				to use when we needed to write these routines.  By agreement between
				the AppleEvent Manager authors and the System 7.0 decision makers,
				the initial AETF was solidified enough for Finder and the Process Mgr
				to use.  This AETF format is to be acceptable in all future revisions
				of the AppleEvent Manager.

	Written by: David Harrison

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	 
		 <2>	10/31/90	DFH		Added function prototypes to get rid of warnings.
		 <0>	 9/20/89	DFH		New Today.

*/ 

#ifndef __APPLEEVENTSINTERNAL__
#include	<AppleEventsInternal.h>
#endif __APPLEEVENTSINTERNAL__

#ifndef __SYSMISC__
#include	"SysMisc.h"
#endif __SYSMISC__

/************************************************************************************
 *								 AETF information.
 ************************************************************************************/

/* Defines so we can look at AppleEvents format directly */
#define aeSignature			'aevt'
#define myAEMajorVersion	1
#define myAEMinorVersion	1

/* Structure that should be in {CIncludes} */
typedef struct AETFDescriptorList	{
	AETFDescriptor		aeID;								/* = aeListParamType */
	long 				count;
	long				hdrLength;
}	AETFDescriptorList;

/* Number of bytes in AETFDescriptorList that need to be accounted for in the
 * AETFDescriptor's dataLength field.
 */
#define LISTEXTRA		(sizeof(AETFDescriptorList) - sizeof(AETFDescriptor))

/************************************************************************************
 *					Structure of some AppleEvent messages we send.
 *
 * NOTE: Structures can not be used to look at messages we *receive*, since the message
 * format is flexible.  We must parse messages dynamically.
 ************************************************************************************/

/* Message format of saeOpenDocumentMsgID and saePrintDocumentMsgID we send */
typedef struct AppleEventListParameter {
	KeyWord					listKey;
	AETFDescriptorList		list;
} AppleEventListParameter;

typedef struct AppleEventDocMsg {
	AETFHeader				messageHeader;
	KeyWord					metaDataMark;
	AppleEventListParameter	listParam;
} AppleEventDocMsg;

/* Message format for saeAnswer we send */
typedef struct MyAppleEventReply {
	AppleEventReply			basicReply;
	AETFParameter			processHdr;
	ProcessSerialNumber		process;
} MyAppleEventReply;

/************************************************************************************
 *								 Utility macros.
 ************************************************************************************/

/* SetAppleEvent.  Make a HighLevelEventRecord suitable for AppleEvents. */
#define SetAppleEvent(aEvtCode, theEvent)					\
	{														\
	(theEvent)->mClass = standardAppleEventMsgClass;		\
	(theEvent)->mID = aEvtCode;								\
	(theEvent)->reserved1 = 0;								\
	(theEvent)->reserved2 = 0;								\
	}

/* GenericAEMessage.  Initializes the fixed part of an AppleEvent message buffer. */
#define GenericAEMessage(pMsg)								\
	{														\
	(pMsg)->signature = aeSignature;						\
	(pMsg)->majorVersion = myAEMajorVersion;				\
	(pMsg)->minorVersion = myAEMinorVersion;				\
	}

/* SetAEParmHeader.  Set up an AETFDescriptor header. */
#define SetAEParmHeader(pParm, keyValue, type, size)		\
	{														\
	(pParm)->key = keyValue;								\
	(pParm)->descriptor.dataType = type;					\
	(pParm)->descriptor.dataLength = size;					\
	}

/************************************************************************************
 *								 Utility routines.
 ************************************************************************************/

void			TranslateAppleEvent(MFmsgBlkPtr, OSErr *);
AETFParameter *	FindKeywordParameter(AETFHeader *, unsigned long, unsigned long);
void			NextListParam(AETFDescriptor **);
void			ExamineDocList(AETFHeader *, unsigned long, AETFDescriptor *, short *);
OSErr			FileIDToAppFile(AETFDescriptor *, AppFile *, short *, long *);
AppParmRecHdl	NewAppParmHandle(Size);
void			NextAppFile(AppFile **);
unsigned long	SizeOfThisAppFile(AppFile *);
OSErr			AppFileAndDocList(AppFile *, unsigned long *, Handle);
void			HandleSystemMessage(MFmsgBlkPtr, OSErr *);
OSErr			SendSystemQuit(PEntryPtr);
OSErr			HandleSystemQuit(MFmsgBlkPtr);
OSErr			SendGenericInstruction(short, MFmsgBlkPtr);
OSErr			SendFileInstruction(short, MFmsgBlkPtr);
OSErr			SendInstructions(EventListHdl, MFmsgBlkPtr);
void			postResult(MFmsgBlkPtr, OSErr, ProcessSerialNumberPtr);
void			ContinueQuitAll(void);
void			CancelQuitAll(ProcessSerialNumberPtr);
