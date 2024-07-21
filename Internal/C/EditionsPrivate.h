/*
	File:		EditionsPrivate.h

	Contains:	Subset of Private Editions Mgr routines needed in C.

	Written by:	Nick Kledzik

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	 8/27/91	JSM		Cleanup header.
		 <3>	 1/14/91	ngk		add PubCBRecord definition
		 <2>	 3/16/90	ngk		Added DrawPreviewn private routine.
		 <1>	  1/8/90	ngk		first checked into BBS

*/

#ifndef __EDITIONSPRIVATE__
#define __EDITIONSPRIVATE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __EDITIONS__
#include <Editions.h>
#endif

#define kDontOpenEditionViewFormat 'doev'

typedef Handle AppRefNum;

struct PubCBRecord
{
	PubCBRecord**		nextPubCB;		/* for double linked list of PCBs */
	PubCBRecord**		prevPubCB;		/* for double linked list of PCBs */
	Handle				usageInfo;		/* (TotalAppUsageHandle) usage info or NIL if not an edition file */
	long				volumeInfo;		/* (VolumeAttributes) info about volume container is on */
	long				pubCNodeID;		/* fileID of container file */
	long				lastVolMod;		/* (Timestamp) last known volume mod date */
	long				lastDirMod;		/* (Timestamp) last known folder mod date */
	PubCBRecord**		oldPubCB;		/* or NIL if publisher is not writting */
	AppRefNum			publisherApp;	/* or NIL if no publisher registered */
	SectionHandle		publisher;		/* or NIL if no publisher registered */
	AliasHandle			publisherAlias;	/* or NIL if publisher is not writting*/
	short				publisherCount;	/* number of register publishers */
	SectionType			publisherKind;	/* the kind of publisher we have */
	Boolean				fileMissing;	/* the file is known to be non-existent */
	short				fileRefNum;		/* or kClosedFile if closed */
	short				openMode;		/* read-only, read/write, map in memory */
	unsigned long		fileMark;		/* cache of logical EOF when writing */
	short				rangeLockStart;	/* 0 or offset into edition file of current lock */
	short				rangeLockLen;	/* 0 or length of current rangelock */
	Handle				allocMap;		/* (AllocationMapHandle) map of file when open */
	Handle				formats;		/* (FormatListHandle) formats from file when open */
	EditionInfoRecord	info;			/* could be trimmed back to end of filename */
};
typedef PubCBRecord *PubCBPtr;
typedef PubCBRecord **PubCBHandle;


/* ====================================== Internal Routines ======================================== */


	pascal OSErr DrawPreview(Handle theData, FormatType theFormat, const Rect *previewRect)
		= { 0x303C, 0x06F6, 0xA82D };
			
			
	pascal OSErr GetCurrentAppRefNum(AppRefNum *thisApp)
		= { 0x303C, 0x02F8, 0xA82D };


	pascal OSErr PostSectionEvent(SectionHandle sectionH, AppRefNum toApp, ResType classID)
		= { 0x303C, 0x06FA, 0xA82D };


	pascal OSErr EditionBackGroundTask(void)
		= { 0x303C, 0x00FC, 0xA82D };

			
	pascal OSErr QuitEditionPack(void)
		= { 0x303C, 0x00FE, 0xA82D };


#endif		/* __EDITIONSPRIVATE__ */
