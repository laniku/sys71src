/*
	File:		PPCBrowser.c

	Contains:	C routines for the PPC Browser
	
	Written by:	Jeff Miller

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

    This file is used in these builds:  Bigbang

	Change History (most recent first):

	   <SM2>	11/18/92	GMA		Set RomMapInsert to mapTrue before caliing GetResource on 'ppcc'
									-5856. we are trying to move these resources into ROM
									eventually.
		<36>	 10/2/90	JAL		Changed all occurances of GetMyZone to PPCGetMyZone because of conflict 
									with new AppleTalk Phase II.  Screwed up version <35>.
		<34>	 9/21/90	JSM		Update to use new "real" PPCToolbox.h (I checked, it generates
									exactly the same object code as the last revision.)
		<33>	 9/21/90	JSM		<VL> Make sure theLoc and thePortInfo are valid.
		<32>	 9/21/90	JSM		<TAR> Return paramErr if defaultSpecified and
									theLoc.locationKindSelector is ppcNBPTypeLocation.
		<31>	 9/16/90	JSM		Return paramErr if theLocNBPType contains a wildcard.
		<30>	 9/15/90	JSM		Update for new PPCToolbox.h.
		<29>	 9/14/90	JSM		Add support for theLocNBPType parameter.
		<28>	 8/21/90	JSM		Add support for default prompt.
		<27>	 7/25/90	JSM		Add FixMachRects and misc. other changes from the Diet Clinic.
		<26>	 6/25/90	JSM		Fix bug in CheckOurMachine where current selection was not
									updated correctly if our machine was inserted before it.
		<25>	 6/19/90	JSM		Remove CenterDialog, done via DLOG resource now.
		<24>	 5/29/90	JSM		Update to support new Chooser-style interface, look for machine
									name STR in System first before using <This Macintosh>.
		<23>	  5/3/90	JSM		Remove workaround for type select utilities bug.
		<22>	  5/3/90	JSM		Use the new type select utilities.
		<21>	  5/2/90	JSM		Don't compare authReq field in PortInfo when doing default
									selection.
		<20>	 4/24/90	JSM		More code size reduction: combine and cleanup routines to
									enable/disable and outline OK button.
		<19>	 4/13/90	JSM		Save and restore current GrafPort.
		<18>	  4/9/90	JSM		Use less code to show ports with the same nameStr.
		<17>	  4/8/90	JSM		Show ports with the same nameStr but different types.
		<16>	  4/5/90	JSM		Don't use GetIndPattern, call PenPatGray now.
		<15>	  4/3/90	JSM		Do nullEvent processing at updateEvt time, too.
		<14>	 3/27/90	JSM		Fix bug in MyListUpdate where LUpdate could be called with a
									NULL ListHandle.
		<13>	 3/26/90	JSM		Fix bug in PollNBP that caused crashes on 68000 machines,
									implement shift-tab support, change SelectAndReveal to scroll to
									top of list always.
		<12>	 3/23/90	JSM		Reduce code size, call filter proc every time PortInfo changes
									instead of just the first time it is returned.
		<11>	 3/22/90	JSM		Fix bug where home machine would not be selected if AppleTalk is
									enabled but there is no zone list.
		<10>	 3/19/90	JSM		Add support for machine not registered on network, always
									PPCInit, save and restore SetSelfSend state, use PortInfo
									instead of PortName.
		 <9>	 3/15/90	JSM		Add support for browser configuration resource.
		 <8>	 3/14/90	JSM		Return NoLocName in theLoc if a port in the local machine is
									chosen.
		 <7>	 3/14/90	JSM		Fix bug setting up application list when AppleTalk is disabled.
		 <6>	 3/12/90	JSM		Add support for zones coming and going.
		 <5>	  3/8/90	JSM		Update to do asynchronous NBP lookups and IPCListPorts.
		 <4>	  3/2/90	JSM		Update GetIndPattern calls to work with new ToolUtils.h.
		 <3>	 2/27/90	JSM		Add support for defaultSpecified.
		 <2>	 2/20/90	JSM		Add support for AppleTalk being disabled.
		 <1>	 2/19/90	JSM		First checked in.

	To Do:
	
		Improve error handling - not returning errors everywhere we should.
*/

/* get our private header */
#include	"PPCBrowserPriv.h"
#include	<Resources.h>

#define	ROMMapInsert	(* (short*) 0xB9E)

/* I M P O R T S */
short			InsertListCell(char *theStr, ListHandle theList, Boolean *unique);
void			PenPatGray();
Boolean			ContainsWildcard(char *theStr);

/* E X P O R T S */

pascal OSErr	MyPPCBrowser(const Str255 prompt, const Str255 applListLabel, 
					Boolean defaultSpecified, LocationNameRec *theLoc, PortInfoRec *thePortInfo,
					PPCFilterProcPtr portFilter, const Str32 theLocNBPType);

pascal Boolean	BrowseFilt(DialogPtr theDialog, EventRecord *theEvent, short *itemhit);

Boolean			PPCGetMyZone(Str32 homeZone);
OSErr			FillZoneList(ListHandle theZoneList);
void			NewZoneSelected(browseGlobals *globs);
void			NewMachSelected(browseGlobals *globs);
void			NewApplSelected(browseGlobals *globs);
void			ZoneListCommon(browseGlobals *globs);
void			ShowZoneList(browseGlobals *globs);
void			HideZoneList(browseGlobals *globs);
void			CheckOurMachine(browseGlobals *globs);

void			GetCurrentPortLoc(browseGlobals *globs, LocationNameRec *currLoc);
void			GetCurrentPortInfo(browseGlobals *globs, PortInfoRec *thePortInfo);
Boolean			ComparePortInfo(PortInfoRec *thePortInfo1, PortInfoRec *thePortInfo2);
short			ComparePortName(PPCPortRec *thePortName1, PPCPortRec *thePortName2);

short			CheckButtonKey(DialogPtr theDialog, EventRecord *theEvent);
void			HandleListKeys(browseGlobals *globs, EventRecord *theEvent);
void			HandleListArrows(char theChar, ListHandle theList);
void			FindMatch(ListHandle theList, TypeSelectRecord *theTSR);

void			SetupListUserItems(DialogPtr theDialog, short titleItem, short listItem,
					short listOutline);
ListHandle		CreateNewList(DialogPtr theDialog, short listItem, short numColumns);
void			EraseListRects(browseGlobals *globs);
void			EraseAndInvalItem(DialogPtr theDialog, short theItem);
void			FixListRects(browseGlobals *globs);
void			FixMachRects(DialogPtr theDialog, short bottDelta);
Boolean			GetSelectedCell(ListHandle list, Cell *theCell);
Boolean			GetSelectedText(ListHandle list, char *theText, Cell *theCell);
void			SelectAndReveal(Cell theCell, ListHandle theList);
void			SelectAndRevealArrows(Cell theCell, ListHandle theList);
void			SelectAndRevealRelative(Cell theCell, ListHandle theList);
Boolean			FindAndSelectCell(ListHandle theList, char *theText);
Boolean			FindAndSelectPortInfoCell(ListHandle theList, PortInfoRec *thePortInfo);

void			SetupDefaultButton(DialogPtr theDialog, short hilite);
void			FlashButton(DialogPtr theDialog, short itemNo);
pascal void		MyListUpdate(DialogPtr theDialog, short itemNo);
pascal void		RectOutline(DialogPtr theDialog, short itemNo);
void			FrameList(DialogPtr theDialog, short index);
pascal void		BtnOutline(DialogPtr theDialog, short itemNo);
pascal void		CenterTitleProc(DialogPtr dialog, short item);
void			SetItemHandle(DialogPtr dialog, short item, Handle procH);

OSErr			StartNBP(browseGlobals *globs, char *machZone);
void			StopNBP(browseGlobals *globs);
void			KillNBP(MPPPBPtr pb);
OSErr			PollNBP(browseGlobals *globs);
OSErr			GrowAndPostNBP(browseGlobals *globs);
void			AgeNBP(browseGlobals *globs);
OSErr			PostNBP(browseGlobals *globs);

OSErr			StartListPorts(browseGlobals *globs, LocationNameRec *portLocName);
OSErr			StopListPorts(browseGlobals *globs);
OSErr			KillListPorts(IPCListPortsPBPtr pb);
OSErr			PollListPorts(browseGlobals *globs);
OSErr			PostListPorts(browseGlobals *globs);

short			InsertPortInfo(PortInfoRec *thePortInfo, ListHandle theList,
					Boolean *unique);


/*FORM_FEED*/
/*
 *
 * OBJECT:		MyPPCBrowser
 *
 * DESCRIPTION:	External interface to the PPCBrowser
 *
 * INPUTS:		prompt:				String to prompt with.
 *				applListLabel:		Label for list of applications.
 *				defaultSpecified:	If true, try to select specified loc and port.
 *				theLoc:				Pointer for LocationNameRec.
 *				thePortInfo:		Pointer for PortInfoRec.
 *
 * OUTPUTS:		theLoc:				If noErr returned, filled in.
 *				thePortInfo:		If noErr returned, filled in.
 *
 * RETURNS:		noErr
 *				userCanceledError
 *				Other errors.
 *
 * MODIFICATIONS:
 *	01-18-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
pascal OSErr
MyPPCBrowser(const Str255 prompt, const Str255 applListLabel, Boolean defaultSpecified,
		LocationNameRec *theLoc, PortInfoRec *thePortInfo, PPCFilterProcPtr portFilter,
		const Str32 theLocNBPType)
{
	DialogPtr		theDialog;
	browseGlobals	*globs;
	short			itemh, i, rc;
	Cell			theCell;
	char			*theCellData;
	short			applListBott;
	short			type;
	Handle			h;
	Rect			r;
	BrowseConfigRes *configPtr;
	GrafPort		*oldPort;
	char			oldSelfSend;
	Str32			currZone;
	LocationNameRec	currLoc;
	MPPParamBlock	pb;
	
	/* make sure theLoc and thePortInfo are valid */
	if ((theLoc == NULL) || (thePortInfo == NULL))
		return paramErr;
	
	/* check for legal theLocNBPType */
	if ((theLocNBPType != NULL) && (theLocNBPType[0] != '\0'))
	{
		/* there is a type specified, check it */
		if (ContainsWildcard(theLocNBPType))
			/* type contains '=' or 'Å' */
			return paramErr;
	}
	
	/* check for legal default location */
	if (defaultSpecified && (theLoc->locationKindSelector == ppcNBPTypeLocation))
		/* ppcNBPTypeLocation location not supported for default matching */
		return paramErr;
	
	/* always PPCInit */
	if ((rc = PPCInit()) != noErr)
		return(rc);

	/* save current GrafPort */
	GetPort(&oldPort);
	
	/* we'll be working hard */
	SetCursor(*GetCursor(watchCursor));
	
	/* get our dialog */
	theDialog = GetNewDialog(BrowseDLOGID, NULL, (WindowPtr)(-1));
	SetPort(theDialog);
	
	/* set the windows font and size for the lists */
	TextFont(listFont);
	TextSize(listFontSize);
	
	/* set up our globals */
	globs = (browseGlobals*)NewPtr(sizeof(browseGlobals));

	/* save dialog */
	globs->theDialog = theDialog;
	
	/* reset type selecting */
	TypeSelectClear(&(globs->theTSR));
	
	/* get the difference in sizes between mach and appl lists */
	GetDItem(theDialog, ApplListItem, &type, &h, &r);
	applListBott = r.bottom;
	GetDItem(theDialog, MachListItem, &type, &h, &r);
	globs->machListBottDelta = applListBott - r.bottom;

	/* save filter specified by caller */
	globs->portFilter = portFilter;
	
	/* initially, we're trying to select the specified default or the home machine */
	globs->selectingDefault = true;
	
	/* dialog initially set up with zone list */
	globs->zoneListShown = true;

	/* save default location and port */
	globs->defaultSpecified = defaultSpecified;
	globs->theLoc = theLoc;
	globs->thePortInfo = thePortInfo;
	
	/* get NBP and PPC parameters from configuration resource */
	ROMMapInsert = mapTrue;								// <SM2> <GMA>
	h = GetResource(BrowseConfigType, BrowseConfigID);
	if (h)
	{
		/* got configuration resource, fill in globals */
		configPtr = (BrowseConfigRes*)*h;
		
		globs->NBPInterval = configPtr->NBPInterval;
		globs->NBPCount = configPtr->NBPCount;
		globs->NBPMaxLives = configPtr->NBPMaxLives;
		globs->NBPMaxToGet = configPtr->NBPMaxToGet;
		globs->NBPMaxIdle = configPtr->NBPMaxIdle;

		globs->PPCMaxToGet = configPtr->PPCMaxToGet;
		globs->PPCMaxIdle = configPtr->PPCMaxIdle;
		
		ReleaseResource(h);
	}
	else
	{
		/* no configuration resource, use default values */
		globs->NBPInterval = 1;
		globs->NBPCount = 5;
		globs->NBPMaxLives = 9;
		globs->NBPMaxToGet = 256;
		globs->NBPMaxIdle = 120;

		globs->PPCMaxToGet = 128;
		globs->PPCMaxIdle = 120;
	}
	
	/* set up for NBP lookup */
	globs->NBPpb = NULL;
	
	/* set up for listing PPC ports */
	globs->PPCpb = NULL;

	/* look for ports of any name and type */
	globs->PPCPort.nameScript = 0;					/* how do we determine this? */
	globs->PPCPort.name[0] = 0x01;					/* name wildcard */
	globs->PPCPort.name[1] = '=';
	globs->PPCPort.portKindSelector = ppcByString;	/* type is a string */
	globs->PPCPort.u.portTypeStr[0] = 0x01;			/* type wildcard */
	globs->PPCPort.u.portTypeStr[1] = '=';
	
	/* hang globals off of dialog */
	SetWRefCon(theDialog, (long)globs);
	
	/* set up to draw the prompt */
	SetItemHandle(theDialog, PromptText, (Handle)CenterTitleProc);
	
	/* save the prompt and application list title */
	if ((prompt == NULL) || (prompt[0] == '\0'))
	{
		/* no prompt specified, get default prompt */
		GetIndString(globs->promptStr, BrowseSTR, DefaultPromptStr);
	}
	else
	{
		/* use specified prompt */
		BlockMove(prompt, globs->promptStr, prompt[0]+1);
	}

	if ((applListLabel == NULL) || (applListLabel[0] == '\0'))
	{
		/* no title specified, get default application list title */
		GetIndString(globs->applListTitle, BrowseSTR, ApplTitle);
	}
	else
	{
		/* copy title specified by caller */
		BlockMove(applListLabel, globs->applListTitle, applListLabel[0]+1);
	}
	
	/* save NBP type to use for lookups */
	if ((theLocNBPType == NULL) || (theLocNBPType[0] == '\0'))
	{
		/* no NBP type specified, use default type "PPCToolbox" */
		GetIndString(globs->theLocNBPType, PPCToolboxSTR, PPCNBPType); 
	}
	else
	{
		/* use specified type */
		BlockMove(theLocNBPType, globs->theLocNBPType, theLocNBPType[0]+1);
	}
	
	/* see if AppleTalk is enabled (stolen from Chooser) */
	globs->hasAT = ((SPConfig) & 0x0F) == 1;
	
	if (globs->hasAT)
	{
		/* tell AppleTalk we want to see our own machine */
		pb.SETSELF.newSelfFlag = 1;
		PSetSelfSend(&pb, false);

		/* save current state of self send */
		oldSelfSend = pb.SETSELF.oldSelfFlag;
				
		/* see if we need a zone list */
		globs->hasZones = PPCGetMyZone(globs->homeZone);
	}
	else
		/* no AppleTalk, so no zones */
		globs->hasZones = false;
	
	/* fix up list title, list outline, and list rectangles appropriately */
	FixListRects(globs);
	
	/* always set up user items for zone list, even if there are currently no zones */
	SetupListUserItems(theDialog, ZoneText, ZoneListItem, ZoneListOutlineItem);
	
	/* allocate the lists */
	if (globs->hasZones)
	{
		/* we need a zone list - only one column */
		globs->theList[ZoneListIndex] = CreateNewList(theDialog, ZoneListItem, ZoneListColumns);

		/* fill zone list now */
		FillZoneList(globs->theList[ZoneListIndex]);
		
		if (defaultSpecified)
		{
			/* see if home zone specified, or local machine */
			if ((theLoc->locationKindSelector == ppcNoLocation) ||
				((theLoc->u.nbpEntity.zoneStr[0] == 0x01) &&
				(theLoc->u.nbpEntity.zoneStr[1] == '*')))
			{
				/* yes, so zone is our zone */
				theCellData = globs->homeZone;
			}
			else
			{
				/* no, use specified zone */
				theCellData = &(theLoc->u.nbpEntity.zoneStr[0]);
			}
			
			/* try to select the specified zone */
			if (!FindAndSelectCell(globs->theList[ZoneListIndex], theCellData))
			{
				/* couldn't select specified zone, just select our zone */
				FindAndSelectCell(globs->theList[ZoneListIndex], globs->homeZone);
				
				/* cancel further default selecting */
				globs->selectingDefault = false;
			}
		}
		else
		{
			/* no default specified, select home zone */
			FindAndSelectCell(globs->theList[ZoneListIndex], globs->homeZone);
		}
		
		/* save current zone cell */
		if (GetSelectedText(globs->theList[ZoneListIndex], currZone, &theCell))
			globs->zoneCell = theCell.v;
		else
			globs->zoneCell = NoCellSelected;
	}
	else
	{
		/* there are no zones */

		if (defaultSpecified)
		{
			/* see if home zone specified, or local machine */
			if (!((theLoc->locationKindSelector == ppcNoLocation) ||
				((theLoc->u.nbpEntity.zoneStr[0] == 0x01) &&
				(theLoc->u.nbpEntity.zoneStr[1] == '*'))))
			{
				/* another zone was specified, so cancel default selecting */
				globs->selectingDefault = false;
			}
		}

		/* no zone list */
		globs->theList[ZoneListIndex] = NULL;
		globs->zoneCell = NoCellSelected;
	}
	
	/* no machines or applications selected yet */
	globs->machCell = NoCellSelected;
	globs->applCell = NoCellSelected;

	/* allocate application list - two columns */
	SetupListUserItems(theDialog, ApplText, ApplListItem, ApplListOutlineItem);
	globs->theList[ApplListIndex] = CreateNewList(theDialog, ApplListItem, ApplListColumns);
		
	/* allocate machine list - two columns */
	SetupListUserItems(theDialog, MachText, MachListItem, MachListOutlineItem);
	globs->theList[MachListIndex] = CreateNewList(theDialog, MachListItem, MachListColumns);

	if (globs->hasAT)
	{
		/* start looking up machines on the network */
		if (globs->zoneCell == NoCellSelected)
		{
			/* no zones, use home zone */
			StartNBP(globs, globs->homeZone);
		}
		else
		{
			/* use currently selected zone */
			StartNBP(globs, currZone);
		}
	}
	else
	{
		/* no AppleTalk, so no need to do lookups */
		
		/* current location is our machine always */
		currLoc.locationKindSelector = ppcNoLocation;

		if (defaultSpecified)
		{
			/* see if local machine specified */
			if (theLoc->locationKindSelector != ppcNoLocation)
			{
				/* another machine was specified, so cancel default selecting */
				globs->selectingDefault = false;
			}
		}
		
		/* no AppleTalk, so our machine can't be registered on the network */
		globs->machineRegistered = false;
		
		/* add our machine to the list (this will be the only entry */
		CheckOurMachine(globs);

		if (globs->machCell != NoCellSelected)
		{
			/* start building the list of applications in the local machine */
			StartListPorts(globs, &currLoc);
		}
	}

	/* set up so that the application list is the current list */
	globs->currList = ApplListIndex;
	
	/* disable OK button */
	SetupDefaultButton(theDialog, buttonDisabledHilite);
	
	/* set up to draw the OK outline */
	SetItemHandle(theDialog, OKOutlineItem, (Handle)BtnOutline);

	/* we are now ready to display the window */
	ShowWindow(theDialog);
	
	InitCursor();
	
	do
	{
		ModalDialog(BrowseFilt, &itemh);
	} while ((itemh != 1) && (itemh != 2));
	
	if (itemh == 1)
	{
		/* OK hit */
		rc = noErr;
	
		/* return current port location */
		if (globs->hasAT)
			/* has AppleTalk, so get location */
			GetCurrentPortLoc(globs, theLoc);
		else
			/* local location only */
			theLoc->locationKindSelector = ppcNoLocation;
		
		/* return current port name */
		GetCurrentPortInfo(globs, thePortInfo);
	}
	else if (itemh == 2)
	{
		/* Cancel hit */
		rc = userCanceledErr;
	}
	
	/* stop any outstanding lookups and lists */
	StopNBP(globs);
	StopListPorts(globs);
	
	if (globs->hasAT)
	{
		/* restore self send state */
		pb.SETSELF.newSelfFlag = oldSelfSend;
		PSetSelfSend(&pb, false);
	}
	
	/* get rid of lists */
	for (i=0; i<3; i++)
	{
		if (globs->theList[i])
			LDispose(globs->theList[i]);
	}
	
	DisposDialog(theDialog);
	DisposPtr((Ptr)globs);
	
	/* restore old GrafPort */
	SetPort(oldPort);
	
	return(rc);	

} /* MyPPCBrowser() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		BrowseFilt
 *
 * DESCRIPTION:	Filter routine to handle the PPCBrowser dialog.
 *
 * INPUTS:		theDialog:	Pointer to dialog.
 *				theEvent:	Pointer to event record.
 *				itemhit:	Pointer to item hit.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		TRUE if OK or Cancel hit or double-click in application
 *				list, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
pascal Boolean
BrowseFilt(DialogPtr theDialog, EventRecord *theEvent, short *itemhit)
{
	short			currCell;
	Cell			theCell;
	Point			pt;
	Boolean			dblclick;
	short			item;
	short			index;
	browseGlobals	*globs;
	Boolean			hasZones;
	
	globs = GetBrowseGlobals(theDialog);
			
	switch (theEvent->what)
	{
		case nullEvent:
		case updateEvt:

			/*
				During null events, check zone status and poll for stuff.
				Note that if there is a pending update event for an
				application window behind us, it will sit at the top of
				the queue and we will never get any null events.  Thus, we
				have to do this processing for update events, too.
			*/

			if (globs->hasAT)
			{
				/* AppleTalk enabled, check if zone status has changed */
				hasZones = GetBridgeAddress() != 0;
				if (hasZones != globs->hasZones)
				{
					/* yes, need to update stuff accordingly */
					globs->hasZones = hasZones;
					if (hasZones)
						/* zones have appeared */
						ShowZoneList(globs);
					else
						/* zones have disappeared */
						HideZoneList(globs);
				}
			}
			
			/* if there is an NBPLookup outstanding, check it */
			if (globs->NBPpb)
				PollNBP(globs);

			/* if there is an IPCListPorts outstanding, check it */
			if (globs->PPCpb)
				PollListPorts(globs);

			break;
			
		case keyDown:
		case autoKey:
			/* check for OK or cancel */
			if ((item = CheckButtonKey(theDialog, theEvent)) != 0)
			{
				/* OK or cancel hit, return from ModalDialog */
				*itemhit = item;
				return(true);
			}
			else
			{
				/* not OK or Cancel, handle other keys */
				HandleListKeys(globs, theEvent);
				
				/* update lists if needed */
				switch (globs->currList)
				{
					case ZoneListIndex:
						NewZoneSelected(globs);
						break;
					
					case MachListIndex:
						NewMachSelected(globs);
						break;
					
					case ApplListIndex:
						NewApplSelected(globs);
						break;
				}
			}
			break;
				
		case mouseDown:
			pt = theEvent->where;
			GlobalToLocal(&pt);
			item = FindDItem(theDialog, pt) + 1;
			
			/* figure out which item we're in */
			index = item - ZoneListItem;
			switch (item)
			{
				case ZoneListItem:
					currCell = globs->zoneCell;
					break;

				case MachListItem:
					currCell = globs->machCell;
					break;

				case ApplListItem:
					currCell = globs->applCell;
					break;
				
				default:
					/* not in a list */
					index = -1;
					break;
			}
			
			if (index != -1)
			{
				/* clicked in a list, see if it's the active one */
				if (index != globs->currList)
				{
					/* erase old frame */
					PenMode(notPatCopy);
					FrameList(theDialog, globs->currList);
					
					/* draw the new frame */
					globs->currList = index;
					FrameList(theDialog, index);
				}
				
				/* handle the click */
				dblclick = LClick(pt, theEvent->modifiers,
					globs->theList[index]);
				
				/* see if selection has changed */
				if (!GetSelectedCell(globs->theList[index], &theCell))
					theCell.v = NoCellSelected;
				
				if (theCell.v != currCell)
				{
					/* selection has changed, no more default selection */
					globs->selectingDefault = false;
					
					/* handle change in selection */
					switch (item)
					{
						case ZoneListItem:
							NewZoneSelected(globs);
							break;
		
						case MachListItem:
							NewMachSelected(globs);
							break;
		
						case ApplListItem:
							NewApplSelected(globs);
							break;
					}
				}
				
				/* handle double click in application list */
				if (dblclick && (index == ApplListIndex) && (globs->applCell != NoCellSelected))
				{
					/* double click, cell selected */
					*itemhit = 1;
					FlashButton(theDialog, 1);
					return(true);
				}
			}
			break;
	}

	return(false);

} /* BrowseFilt() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		PPCGetMyZone
 *
 * DESCRIPTION:	Get name of current zone.  Returns "*" and false if no zones.
 *
 * INPUTS:		homeZone:		Pointer to buffer for zone.
 *
 * OUTPUTS:		homeZone:		Filled in with our zone.
 *
 * RETURNS:		TRUE if there are zones, FALSE otherwise.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
Boolean
PPCGetMyZone(Str32 homeZone)
{
	short			bridge, node, net;
	ATPPBPtr		thePBptr;
	OSErr			result;
	BDSElement		*theBDSPtr;
	
	/* assume no zones */
	homeZone[0] = 0x01;
	homeZone[1] = '*';
	
	bridge = GetBridgeAddress();
	GetNodeAddress(&node, &net);

//	if ((bridge == 0) && (net == 0))
	if (bridge == 0)
		/* no zones */
		return(false);

	/* get our zone name */
	thePBptr = (ATPPBPtr)NewPtr(sizeof(ATPParamBlock));
	
	thePBptr->ATPuserData = 0x07000000; 	/* PPCGetMyZone command */
	thePBptr->ATPatpFlags = 0;
	
	thePBptr->ATPaddrBlock.aNet = net;
	thePBptr->ATPaddrBlock.aNode = bridge;
	thePBptr->ATPaddrBlock.aSocket = 0x06; 	/* ZIP socket */
	
	thePBptr->ATPreqLength = 0; 			/* request is zero length */
	thePBptr->ATPreqPointer = 0L; 			/* pointer to request data */
	
	thePBptr->ATPbdsPointer = NewPtr(sizeof(BDSElement));
	theBDSPtr = (BDSElement*)(thePBptr->ATPbdsPointer);
	theBDSPtr->buffSize = 34;				/* 32 characters max */
	theBDSPtr->buffPtr = homeZone;			/* return zone name here */
	
	
	thePBptr->ATPnumOfBuffs = 0x01;			/* only one response */
	thePBptr->ATPtimeOutVal = 0x01;			/* one second timeout */
	thePBptr->ATPretryCount = 0x05;			/* retry five times */
	
	/* send the request */
	result = PSendRequest(thePBptr, false);

	/* clean up */
	DisposPtr(thePBptr->ATPbdsPointer);
	DisposPtr((Ptr)thePBptr);

	if (result != noErr)
	{
		/* error occurred */
		homeZone[0] = 0x01;
		homeZone[1] = '*';
		return(false);
	}

	return(true);
	
} /* PPCGetMyZone() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FillZoneList
 *
 * DESCRIPTION:	Fill specified list with zone names.  This should only be called once.
 *
 * INPUTS:		theZoneList:	ListHandle to fill.
 *
 * OUTPUTS:		None.
 *
 * RETURNS:		Errors from OpenXPP.
 *
 * MODIFICATIONS:
 *	01-18-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
OSErr
FillZoneList(ListHandle theZoneList)
{
	short			bridge, node, net;
	short			numZones, numFound, i;
	char			*ZonePtr;
	Boolean			unique;
	ATPPBPtr		thePBptr;
	OSErr			result;
	BDSElement		*theBDSPtr;

	bridge = GetBridgeAddress();
	GetNodeAddress(&node, &net);

//	if ((bridge == 0) && (net == 0))
	if (bridge == 0)
		/* no zones */
		return(noErr);

	/* get a list of zones */
	thePBptr = (ATPPBPtr)NewPtr(sizeof(ATPParamBlock));
		
	thePBptr->ATPaddrBlock.aNet = net;
	thePBptr->ATPaddrBlock.aNode = bridge;
	thePBptr->ATPaddrBlock.aSocket = 0x06; 	/* ZIP socket */
	
	thePBptr->ATPreqLength = 0; 			/* request is zero length */
	thePBptr->ATPreqPointer = 0L; 			/* pointer to request data */
	
	thePBptr->ATPbdsPointer = NewPtr(sizeof(BDSElement));
	theBDSPtr = (BDSElement*)(thePBptr->ATPbdsPointer);
	theBDSPtr->buffSize = 578;				/* size of buffer */
	theBDSPtr->buffPtr = NewPtr(578);		/* return zone names here */
	
	thePBptr->ATPnumOfBuffs = 0x01;			/* only one response */
	thePBptr->ATPtimeOutVal = 0x01;			/* one second timeout */

	/* get zones */
	numZones = 0;
	LDoDraw(false, theZoneList);
	do
	{
		/* fill in fields that get trashed */
		thePBptr->ATPatpFlags = 0;
		thePBptr->ATPretryCount = 0x05;			/* retry five times */
		
		/* munge in index with GetZoneList command */
		thePBptr->ATPuserData = 0x08000000 + (numZones + 1);
	
		/* send the request */
		result = PSendRequest(thePBptr, false);
		
		if (result != noErr)
			break;
		
		/* add zones retrieved */
		numFound = (theBDSPtr->userBytes & 0x0000FFFF);
		numZones += numFound;
	
		/* add zones to list in alphabetical order */
		ZonePtr = theBDSPtr->buffPtr;

		for(i=0; i < numFound; i++)
		{
			InsertListCell(ZonePtr, theZoneList, &unique);
			ZonePtr += *ZonePtr + 1;	/* March the zone ptr */
		}
		
	} while ((theBDSPtr->userBytes & 0xFF000000) == 0);		/* until LastFlag is non-zero */

	LDoDraw(true, theZoneList);

	/* clean up */
	DisposPtr(theBDSPtr->buffPtr);
	DisposPtr((Ptr)theBDSPtr);
	DisposPtr((Ptr)thePBptr);
		
	HLock((Handle)theZoneList);
	InvalRect(&((**theZoneList).rView));
	HUnlock((Handle)theZoneList);

	return(result);
}

/*FORM_FEED*/
/*
 *
 * OBJECT:		NewZoneSelected
 *
 * DESCRIPTION:	Handle updating when a new zone is selected.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
NewZoneSelected(browseGlobals *globs)
{
	Cell		theCell;
	ListHandle	theList;
	Str32		newZone;
	
	theList = globs->theList[ZoneListIndex];

	/* get current selection */
	if (!GetSelectedText(theList, newZone, &theCell))
		theCell.v = NoCellSelected;
	
	/* see if selection has changed */
	if (theCell.v != globs->zoneCell)
	{
		/* yes, need to update everything */
		globs->zoneCell = theCell.v;
		
		/* clear other lists */
		LDelRow(0, 0, globs->theList[MachListIndex]);
		LDelRow(0, 0, globs->theList[ApplListIndex]);
		
		/* no machines or applications selected */
		globs->machCell = NoCellSelected;
		globs->applCell = NoCellSelected;
		
		/* disable OK button */
		SetupDefaultButton(globs->theDialog, buttonDisabledHilite);
		
		/* kill any outstanding lookups and lists */
		StopNBP(globs);
		StopListPorts(globs);
		
		/* is there a current zone selected? */
		if (theCell.v != NoCellSelected)
		{
			/* yes, rebuild list of machines in current zone */
			StartNBP(globs, newZone);
		}
	}

} /* NewZoneSelected() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		NewMachSelected
 *
 * DESCRIPTION:	Handle updating when a new machine is selected.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
NewMachSelected(browseGlobals *globs)
{
	Cell				theCell;
	ListHandle			theList;
	Str32				newMach;
	LocationNameRec		currLoc;
	
	theList = globs->theList[MachListIndex];

	/* get current selection */
	if (!GetSelectedText(theList, newMach, &theCell))
		theCell.v = NoCellSelected;
	
	/* see if selection has changed */
	if (theCell.v != globs->machCell)
	{
		/* yes, need to update everything */
		globs->machCell = theCell.v;
		
		/* clear application list */
		LDelRow(0, 0, globs->theList[ApplListIndex]);
		
		/* no applications selected */
		globs->applCell = NoCellSelected;
		
		/* disable OK button */
		SetupDefaultButton(globs->theDialog, buttonDisabledHilite);
		
		/* kill any outstanding list ports */
		StopListPorts(globs);
		
		/* is there a current machine selected? */
		if (theCell.v != NoCellSelected)
		{
			/* yes, get the current location */
			GetCurrentPortLoc(globs, &currLoc);
			
			/* start building port list */
			StartListPorts(globs, &currLoc);
		}
	}

} /* NewMachSelected() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		NewApplSelected
 *
 * DESCRIPTION:	Handle updating when a new application is selected.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
NewApplSelected(browseGlobals *globs)
{
	short		hilite;
	Cell		theCell;
	ListHandle	theList;
	
	theList = globs->theList[ApplListIndex];

	/* see if selection has changed */
	if (!GetSelectedCell(theList, &theCell))
		theCell.v = NoCellSelected;
		
	/* see if selection has changed */
	if (theCell.v != globs->applCell)
	{
		/* yes */
		globs->applCell = theCell.v;
	
		/* disable OK button if there is no cell selected, otherwise enable it */
		hilite = (globs->applCell == NoCellSelected) ? buttonDisabledHilite : buttonEnabledHilite;
		SetupDefaultButton(globs->theDialog, hilite);
	}

} /* NewApplSelected() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		ZoneListCommon
 *
 * DESCRIPTION:	Common code when showing or hiding the zone list.
 *
 *				Zones have disappeared or reappeared on the network, so:
 *
 *				Cancel any outstanding lookups and lists.
 *				Terminate any default selection processing.
 *				Set all currently selected machine and application
 *				cell variables to NoCellSelected.
 *				Dispose of the current machine and application lists.
 *				Erase and inval the current list and title rectangles.
 *				Resize the list rectangles.
 *				Allocate new machine and application lists.
 *				Get the home zone.
 *				Make the application list the current list and disable OK button.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
ZoneListCommon(browseGlobals *globs)
{
	/* stop any outstanding lookups and lists */
	StopNBP(globs);
	StopListPorts(globs);
	
	SetCursor(*GetCursor(watchCursor));
	
	/* make sure we no longer do any default selecting */
	globs->selectingDefault = false;
	
	/* there is no longer anything selected */
	globs->machCell = NoCellSelected;
	globs->applCell = NoCellSelected;
	
	/* get rid of the current machine and application lists */
	LDispose(globs->theList[MachListIndex]);
	LDispose(globs->theList[ApplListIndex]);
	
	/* erase list and title rectangles */
	EraseListRects(globs);
	
	/* fix the zone and machine lists */
	FixListRects(globs);
	
	/* allocate new machine and application lists */
	globs->theList[MachListIndex] = CreateNewList(globs->theDialog, MachListItem, MachListColumns);
	globs->theList[ApplListIndex] = CreateNewList(globs->theDialog, ApplListItem, ApplListColumns);
	
	/* get the home zone */
	PPCGetMyZone(globs->homeZone);
		
	/* set up so that the application list is the current list */
	globs->currList = ApplListIndex;
		
	/* disable OK button */
	SetupDefaultButton(globs->theDialog, buttonDisabledHilite);
	
} /* ZoneListCommon() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		ShowZoneList
 *
 * DESCRIPTION:	Zones have reappeared on the network, so:
 *
 *				Call common code for showing and hiding zone lists.
 *				Allocate and fill zone list.
 *				Preselect our zone.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
ShowZoneList(browseGlobals *globs)
{
	Cell	theCell;
	
	/* use common code for most stuff */
	ZoneListCommon(globs);

	/* allocate new zone list */
	globs->theList[ZoneListIndex] = CreateNewList(globs->theDialog, ZoneListItem, ZoneListColumns);
	
	/* fill zone list now */
	FillZoneList(globs->theList[ZoneListIndex]);

	/* try to select home zone */
	FindAndSelectCell(globs->theList[ZoneListIndex], globs->homeZone);
	
	/* save current zone cell */
	if (GetSelectedText(globs->theList[ZoneListIndex], globs->homeZone, &theCell))
	{
		globs->zoneCell = theCell.v;

		/* start looking up */
		StartNBP(globs, globs->homeZone);
	}
	else
		/* couldn't select our zone */
		globs->zoneCell = NoCellSelected;
	
	InitCursor();

} /* ShowZoneList() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		HideZoneList
 *
 * DESCRIPTION:	Zones have disappeared from the network, so:
 *
 *				Cancel any outstanding lookups and lists.
 *				Terminate any default selection processing.
 *				Set all currently selected zone cell variable to NoCellSelected.
 *				Dispose of the current zone list.
 *				Start a new lookup in the '*' zone.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
HideZoneList(browseGlobals *globs)
{
	/* use common code for most stuff */
	ZoneListCommon(globs);
	
	/* there is no longer a zone selected */
	globs->zoneCell = NoCellSelected;
	
	/* get rid of current zone list */
	LDispose(globs->theList[ZoneListIndex]);
	globs->theList[ZoneListIndex] = NULL;
	
	/* start a new lookup */
	StartNBP(globs, globs->homeZone);
	
	InitCursor();

} /* HideZoneList() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		CheckOurMachine
 *
 * DESCRIPTION:	After the first NBP lookup completes for our home zone, we need
 *				to check and see if our machine was returned.  If it wasn't
 *				(implying that the PPCToolbox didn't register it on the
 *				network), we need to generate an entry for it in the machine
 *				list ourselves.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-19-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
CheckOurMachine(browseGlobals *globs)
{
	ListHandle		theList;
	Cell			theCell;
	Boolean			unique;
	MachListData	theData;
	char			**machName;
	Str32			ownMachineStr;
	
	if (globs->machineRegistered)
		/* we found our machine on the network already */
		return;
	
	/*
		We didn't find our machine on the network, so we have
		to generate an entry for it.  Check to see if the machine
		name string is in the System, if not or if it is empty
		then use the default name.
	*/
	
	theList = globs->theList[MachListIndex];
	
	/* look for name in system */
	machName = GetResource('STR ', PPCMachNameSTR);
	
	if ((machName == NULL) || (**machName == '\0'))
	{
		/* no machine name or null machine name, use default */
		GetIndString(ownMachineStr, BrowseSTR, NoMachineStr);
	}
	else
	{
		/* machine name in System, probably just network access disabled */
		BlockMove(*machName, ownMachineStr, (**machName) + 1);
	}
	
	/* try to insert it */
	theCell.v = InsertListCell(ownMachineStr, theList, &unique);
	
	/*
		If the default name is not unique (i.e. some moron on
		the network has named his machine the same thing), we
		override the network version and use the default name
		to refer to our machine.
	*/

	theCell.h = 1;
	theData.isHomeMachine = true;
	LSetCell((Ptr)&theData, sizeof(MachListData), theCell, theList);
	
	if (unique)
	{
		/* cell was unique, if it was inserted before the current cell, need to update */
		if (theCell.v <= globs->machCell)
			globs->machCell++;
	}
	
	/* try to do default selecting, if necessary */
	if (globs->selectingDefault)
	{
		/* see if we're selecting ourselves */
		if ((!globs->defaultSpecified) || (globs->theLoc->locationKindSelector == ppcNoLocation))
		{
			/* yes */
			if (FindAndSelectCell(theList, ownMachineStr))
			{
				/* should always have found it, since we just inserted it */
				NewMachSelected(globs);
			}
		}
	}

} /* CheckOurMachine() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		GetCurrentPortLoc
 *
 * DESCRIPTION:	Build current port location from currently selected machine.
 *				If currently selected machine is the local machine, sets
 *				currLoc->locationKindSelector to ppcNoLocation.
 *
 * INPUTS:		globs:			Pointer to globals.
 *				currLoc:		Pointer to LocationNameRec to be filled in.
 *
 * OUTPUTS:		currLoc:		Filled in.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-10-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
GetCurrentPortLoc(browseGlobals *globs, LocationNameRec *currLoc)
{
	Cell			theCell;
	short			theLen;
	MachListData	theData;
	
	/* get currently select cell in machine list */
	GetSelectedCell(globs->theList[MachListIndex], &theCell);
	
	/* see if this it is the local machine */
	theCell.h = 1;
	theLen = sizeof(MachListData);
	LGetCell((Ptr)&theData, &theLen, theCell, globs->theList[MachListIndex]);
	
	if (theData.isHomeMachine)
	{
		/* yes, no location name */
		currLoc->locationKindSelector = ppcNoLocation;
		return;
	}
	
	/* always NBP */
	currLoc->locationKindSelector = ppcNBPLocation;
	
	/* have to fill in object, type, and zone in entity */
	
	/* get object name from machine list */
	GetSelectedText(globs->theList[MachListIndex], &(currLoc->u.nbpEntity.objStr[0]),
		&theCell);
	
	/* get type name from globals */
	BlockMove(globs->theLocNBPType, &(currLoc->u.nbpEntity.typeStr[0]), globs->theLocNBPType[0]+1);
	
	/* get zone from zone list, if there is one */
	if (globs->hasZones)
		GetSelectedText(globs->theList[ZoneListIndex],
			&(currLoc->u.nbpEntity.zoneStr[0]), &theCell);
	else
	{
		/* no zones, just use '*' */
		currLoc->u.nbpEntity.zoneStr[0] = 0x01;
		currLoc->u.nbpEntity.zoneStr[1] = '*';
	}

} /* GetCurrentPortLoc() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		GetCurrentPortInfo
 *
 * DESCRIPTION:	Build current port info from currently selected application.
 *				Note that the PortInfo is stored in the second column of
 *				the application list.
 *
 * INPUTS:		globs:			Pointer to globals.
 *				currPortInfo:	Pointer to PortInfoRec to be filled in.
 *
 * OUTPUTS:		currPortInfo:	Filled in.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-10-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
GetCurrentPortInfo(browseGlobals *globs, PortInfoRec *currPortInfo)
{
	Cell			theCell;
	short			theLen;
	ApplListData	theData;
	
	/* get currently selected application */
	GetSelectedCell(globs->theList[ApplListIndex], &theCell);
	
	/* read port from data in column 2 */
	theCell.h = 1;
	theLen = sizeof(ApplListData);
	LGetCell((Ptr)&theData, &theLen, theCell, globs->theList[ApplListIndex]);
	
	/* copy over PortInfoRec */
	BlockMove((Ptr)&(theData.thePortInfo), (Ptr)currPortInfo, sizeof(PortInfoRec));

} /* GetCurrentPortInfo() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		ComparePortInfo
 *
 * DESCRIPTION:	Compare two PortInfoRec structures.  Return TRUE if they are the
 *				same, FALSE otherwise.
 *
 * INPUTS:		thePortInfo1:	Pointer to first PortInfoRec.
 *				thePortInfo2:	Pointer to second PortInfoRec.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		TRUE if records are the same, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-23-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
Boolean
ComparePortInfo(PortInfoRec *thePortInfo1, PortInfoRec *thePortInfo2)
{
	Boolean		rc;
	PPCPortRec	*name1, *name2;
	
	/* check authRequired */
	rc = (thePortInfo1->authRequired == thePortInfo2->authRequired);
	
	if (rc)
	{
		/* get pointers to port names */
		name1 = &(thePortInfo1->name);
		name2 = &(thePortInfo2->name);

		/* compare scriptCode (not done by ComparePortName) */
		rc = (name1->nameScript == name2->nameScript);
		
		if (rc)
		{
			/* compare rest of PPCPortRec */
			rc = (ComparePortName(name1, name2) == 0);
		}
	}
	
	return(rc);

} /* ComparePortInfo() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		ComparePortName
 *
 * DESCRIPTION:	Compare two PPCPortRec structures (except nameScript).  Returns 0 if
 *				PortNames are the same, <0 if thePortName1 < thePortName2, or >0 if
 *				thePortName1 > thePortName2.
 *
 *				Comparison criteria is as follows:
 *
 *				name
 *				portKindSelector (ppcByCreatorAndType before ppcByString)
 *				creator/type or typeStr
 *
 *				Note that in the PPCToolbox name and typeStr are treated as just
 *				bytes, so to compare them we use a straight byte compare.
 *
 * INPUTS:		thePortName1:	Pointer to first PPCPortRec.
 *				thePortName2:	Pointer to second PPCPortRec.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		<0	if thePortName1 < thePortName2
 *				 0	if thePortName1 = thePortName2
 *				>0	if thePortName1 > thePortName2
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	04-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
short
ComparePortName(PPCPortRec *thePortName1, PPCPortRec *thePortName2)
{
	short		rc;
	short		port1Len, port2Len;
	
	/* first, compare nameStr */
	port1Len = thePortName1->name[0];
	port2Len = thePortName2->name[0];
	
	/* compare using shorter length */
	rc = (short)memcmp(&(thePortName1->name[1]), &(thePortName2->name[1]),
					(port1Len < port2Len) ? port1Len : port2Len);
	
	if ((rc == 0) && (port1Len != port2Len))
	{
		/* memcmp said they were equal, but lengths are actually different */
		/* shorter name is smaller */
		rc = (port1Len < port2Len) ? -1 : 1;
	}
	
	if (rc == 0)
	{
		/* names are the same, now check type selectors */
		if (thePortName1->portKindSelector != thePortName2->portKindSelector)
		{
			/* different selectors, ppcByCreatorAndType is smaller */
			rc = (thePortName1->portKindSelector == ppcByCreatorAndType) ? -1 : 1;
		}
		else
		{
			/* type selectors are the same, now check type */
			if (thePortName1->portKindSelector == ppcByCreatorAndType)
			{
				/* both are ppcByCreatorAndType */
				rc = (short)memcmp(&(thePortName1->u.port.creator),
						&(thePortName2->u.port.creator), 8);
			}
			else
			{
				/* both are ppcByString */
				port1Len = thePortName1->u.portTypeStr[0];
				port2Len = thePortName2->u.portTypeStr[0];

				/* compare using shorter length */
				rc = (short)memcmp(&(thePortName1->u.portTypeStr[1]),
						&(thePortName2->u.portTypeStr[1]),
						(port1Len < port2Len) ? port1Len : port2Len);
				
				if ((rc == 0) && (port1Len != port2Len))
				{
					/* memcmp said they were equal, but lengths are actually different */
					/* shorter type is smaller */
					rc = (port1Len < port2Len) ? -1 : 1;
				}
			}
		}
	}
	
	return(rc);

} /* ComparePortName() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		CheckButtonKey
 *
 * DESCRIPTION:	If enter or return pressed and OK button is enabled, returns 1.
 *				If command-. or escape is pressed, returns 2.  Otherwise, returns 0.
 *				Buttons are hilited appropriately.
 *
 * INPUTS:		theDialog:			Pointer to the dialog.
 *				theEvent:			Pointer to event (should be autokey or keydown).
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
short
CheckButtonKey(DialogPtr theDialog, EventRecord *theEvent)
{
	short		type;
	Handle		h;
	Rect		r;
	char		theChar;

	theChar = theEvent->message & charCodeMask;

	/* check for return or enter */
	if (theChar == charReturn || theChar == charEnter)
	{
		/* yes, see if OK is enabled */
		GetDItem(theDialog, 1, &type, &h, &r);
		if ((**(ControlHandle)h).contrlHilite == 0)
		{
			/* yes, flash button and return 1 */
			FlashButton(theDialog, 1);
			return(1);
		}
	}
	else
	{
		/* check for cmd-. or escape for Cancel */
		if (((theChar == charPeriod) && ((theEvent->modifiers & cmdKey) != 0))
			|| ((theChar == charEscape) &&
				(((theEvent->message & keyCodeMask) >> 8) == kcEscape)))
		{
			/* yes, flash button and return 2 */
			FlashButton(theDialog, 2);
			return(2);
		}
	}
	
	/* otherwise, return 0 */
	return(0);

} /* CheckButtonKey() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		HandleListKeys
 *
 * DESCRIPTION:	Handle a keydown or autokey event in a list.
 *
 *				Uses Type Select Utilities.
 *
 *				Arrow, delete/backspace, and clear keys clear the TypeSelectRecord.
 *
 * INPUTS:		globs:			Pointer to globals.
 *				theEvent:		Event record.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-07-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
HandleListKeys(browseGlobals *globs, EventRecord *theEvent)
{
	ListHandle		theList;
	short			index;
	char			theChar;
	
	theList = globs->theList[globs->currList];
	
	theChar = theEvent->message & charCodeMask;
	
	/* tabbing is always valid, if there is more than one list */
	if (theChar == charTab)
	{
		/* clear TypeSelectRecord */
		TypeSelectClear(&(globs->theTSR));
		
		/* we always have at least two lists */
		if ((theEvent->modifiers & shiftKey) != 0)
		{
			/* shift-tab means go backwards */
			index = globs->currList - 1;

			/* have we gone too far backwards? */
			if (globs->hasZones)
			{
				if (index < ZoneListIndex)
				{
					/* went past zones, wrap to applications */
					index = ApplListIndex;
				}
			}
			else
			{
				if (index < MachListIndex)
				{
					/* no zones, went past machines, wrap to applications */
					index = ApplListIndex;
				}
			}
		}
		else
		{
			/* tab means go forwards */
			index = globs->currList + 1;

			/* have we gone too far forwards? */
			if (index > ApplListIndex)
			{
				/* wrap to zones or machines */
				if (globs->hasZones)
					index = ZoneListIndex;
				else
					index = MachListIndex;
			}
		}

		/* erase old frame */
		PenMode(notPatCopy);
		FrameList(globs->theDialog, globs->currList);
		
		/* draw the new frame */
		globs->currList = index;
		FrameList(globs->theDialog, index);
		
		return;
	}

	/* check for an empty list */
	if ((**theList).dataBounds.top == (**theList).dataBounds.bottom)
		/* empty list */
		return;
	
	/* anything else cancels default selecting */
	globs->selectingDefault = false;
	
	switch (theChar)
	{
		case charUpArrow:
		case charDownArrow:
			HandleListArrows(theChar, theList);
			/* clear TypeSelectRecord */
			TypeSelectClear(&(globs->theTSR));
			break;
		
		default:
			/* only handle arrow and tab autokeys */
			if (theEvent->what == autoKey)
				break;
			
			/* not an autokey, let type select utilites handle it */
			if (TypeSelectNewKey(theEvent, &(globs->theTSR)))
			{
				/* try to find matching list entry */
				FindMatch(theList, &(globs->theTSR));
			}
			break;

	} /* switch (theChar) */

} /* HandleListKeys() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		HandleListArrows
 *
 * DESCRIPTION:	Handle an up or down arrow keydown or autokey event in a list.
 *				Assumes list has at least one item in it.
 *
 * INPUTS:		theChar:		Character that was typed (up or down arrow)
 *				theList:		ListHandle it applies to.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-07-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
HandleListArrows(char theChar, ListHandle theList)
{
	short		offset;
	short		bottomCell = (**theList).dataBounds.bottom - 1;
	Cell		theCell;
	
	/* get currently selected cell, if any */
	if (!GetSelectedCell(theList, &theCell))
	{
		/* no cell selected */
		if (theChar == charDownArrow)
			/* down arrow, select top cell */
			theCell.v = 0;
		else
			/* up arrow, select bottom cell */
			theCell.v = bottomCell;
	}
	else
	{
		/* cell currently selected */
		
		/* if we're at the top and up arrow, or
			at the bottom and down arrow, do nothing */
		if (((theCell.v == 0) && (theChar == charUpArrow)) ||
			((theCell.v == bottomCell) && (theChar == charDownArrow)))
		{
			return;
		}
		
		/* unselect old cell */
		LSetSelect(false, theCell, theList);
		
		/* get which way were going */
		if (theChar == charUpArrow)
			offset = -1;
		else
			offset = 1;
		
		theCell.v += offset;
	}
	
	/* select new cell */
	SelectAndRevealArrows(theCell, theList);

} /* HandleListArrows() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FindMatch
 *
 * DESCRIPTION:	Select and scroll to the closest matching cell in a list.
 *				Assumes list has at least one item in it.  Also assumes
 *				list is sorted, so we can use TypeSelectCompare.
 *
 *
 * INPUTS:		theList:		List to find match in.
 *				theTSR:			Pointer to current TypeSelectRecord.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
FindMatch(ListHandle theList, TypeSelectRecord *theTSR)
{
	Cell		theCell, oldCell;
	short		len;
	Boolean		foundit;
	char		theCellStr[32];
	
	/* search list for what to select */
	theCell.h = 0;
	theCell.v = 0;
	foundit = false;
	
	do
	{
		/* are we at the end of the list? */
		if (theCell.v == (**theList).dataBounds.bottom)
		{
			/* yes, select last item */
			theCell.v--;
			foundit = true;
		}
		else
		{
			/* check current cell */
			len = 32;
			LGetCell(&(theCellStr[1]), &len, theCell, theList);
			theCellStr[0] = len;
			
			/* call type select utilities */
			/* ?? how do we determine script code ?? */
			if (TypeSelectCompare(theTSR, 0, theCellStr) <= 0)
			{
				/* typed in string is <= cell string, so this is it */
				foundit = true;
			}
			else
			{
				/* try next cell */
				theCell.v++;
			}
		}
	} while (!foundit);
	
	/* deselect any currently selected cell */
	if (GetSelectedCell(theList, &oldCell))
	{
		LSetSelect(false, oldCell, theList);
	}

	/* select new cell */
//	SelectAndRevealRelative(theCell, theList);
	SelectAndReveal(theCell, theList);

} /* FindMatch() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SetupListUserItems
 *
 * DESCRIPTION:	Set up so that the list updates and the outline is drawn.
 *				Also set up so list title is drawn.
 *
 * INPUTS:		theDialog:			Pointer to the dialog with list.
 *				listTitle:			Item number of title.
 *				listItem:			Item number of list.
 *				listOutline:		Item number of user item for outline.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-26-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
SetupListUserItems(DialogPtr theDialog, short listTitle, short listItem, short listOutline)
{
	short		itemtype;
	Handle		item;
	Rect		box;
	
	/* set up so title is drawn */
	SetItemHandle(theDialog, listTitle, (Handle)CenterTitleProc);
	
	GetDItem(theDialog, listItem, &itemtype, &item, &box);
	
	/* The list is inset one pixel from the outline */
	InsetRect(&box, 1, 1);

	/* point to our list update proc */
	SetDItem(theDialog, listItem, userItem, (Handle)MyListUpdate, &box);

	GetDItem(theDialog, listOutline, &itemtype, &item, &box);
	
	/* 
		The outline rect is outset (1 + listFrameSize) pixels from the
		actual outline.  This is so, when the active frame has
		to be drawn, the clip region is set up OK.
	*/
	InsetRect(&box, -(1 + listFrameSize), -(1 + listFrameSize));

	/* point to our outline framing proc */
	SetDItem(theDialog, listOutline, userItem, (Handle)RectOutline, &box);

} /* SetupListUserItems() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		CreateNewList
 *
 * DESCRIPTION:	Make a list in the specified dialog.
 *
 * INPUTS:		theDialog:			Pointer to the dialog with list.
 *				listItem:			Item number of list.
 *				numColumns:			Number of columns in list (1 or 2).
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Handle to newly created list.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
ListHandle
CreateNewList(DialogPtr theDialog, short listItem, short numColumns)
{
	Rect		bounds;
	Cell		theCell;
	short		itemtype;
	Handle		item;
	Rect		box;
	ListHandle	list;
	
	/* list is one or two columns */
	SetRect(&bounds, 0, 0, numColumns, 0);
	
	/* get the list item */
	GetDItem(theDialog, listItem, &itemtype, &item, &box);

	/* adjust for scroll bars */
	box.right -= 16 - 1;
	
	/* calculate width of a cell, so second column isn't displayed */
	theCell.h = box.right - box.left;
	
	/* use default height for a cell */
	theCell.v = 0;

	/* make a new list */
	list = LNew(&box, &bounds, theCell, 0, theDialog, true, false, false, true);
	
	/* don't hilite empty cells and only select one cell at a time */
	(**list).selFlags = lNoNilHilite + lOnlyOne; 

	/* return the list handle */
	return(list);

} /* CreateNewList() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		EraseListRects
 *
 * DESCRIPTION:	Erase and invalidate the outline and title rectangles
 *				for the three lists.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		Nothing.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
EraseListRects(browseGlobals *globs)
{
	DialogPtr	theDialog;

	theDialog = globs->theDialog;
	
	EraseAndInvalItem(theDialog, ZoneListOutlineItem);
	EraseAndInvalItem(theDialog, ZoneText);
	
	EraseAndInvalItem(theDialog, MachListOutlineItem);
	EraseAndInvalItem(theDialog, MachText);
	
	EraseAndInvalItem(theDialog, ApplListOutlineItem);
	EraseAndInvalItem(theDialog, ApplText);
	
	/* erase the current frame, too */
	PenMode(notPatCopy);
	FrameList(theDialog, globs->currList);

} /* EraseListRects() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		EraseAndInvalItem
 *
 * DESCRIPTION:	Erase and invalidate rectangle for specified item.
 *
 * INPUTS:		theDialog:			Pointer to the dialog.
 *				theItem:			Item number to erase and inval.
 *
 * OUTPUTS:		Nothing.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-23-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
EraseAndInvalItem(DialogPtr theDialog, short theItem)
{
	short		type;
	Handle		h;
	Rect		r;

	GetDItem(theDialog, theItem, &type, &h, &r);
	EraseRect(&r);
	InvalRect(&r);

} /* EraseAndInvalItem() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FixListRects
 *
 * DESCRIPTION:	Adjust the list title, outline, and content rectangles
 *				for the zone and machine lists.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		Nothing.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
FixListRects(browseGlobals *globs)
{
	DialogPtr	theDialog;
	
	theDialog = globs->theDialog;
	
	/* note that hasZones will be false if no zones or no AppleTalk */
	if (!globs->hasZones)
	{
		/* no zones, see if we need to hist the zone list and resize the mach list */
		if (globs->zoneListShown)
		{
			/* hide the zone list stuff */
			HideDItem(theDialog, ZoneText);
			HideDItem(theDialog, ZoneListItem);
			HideDItem(theDialog, ZoneListOutlineItem);
	
			/* grow the lists */
			FixMachRects(theDialog, globs->machListBottDelta);
			
			/* we're hiding the zone list */
			globs->zoneListShown = false;
		}
	}
	else
	{
		/* zones exist, see if we need to show the zone list and resize the mach list */
		if (!globs->zoneListShown)
		{
			/* shrink the lists */
			FixMachRects(theDialog, -(globs->machListBottDelta));
			
			/* reveal the zone list */
			ShowDItem(theDialog, ZoneText);
			ShowDItem(theDialog, ZoneListItem);
			ShowDItem(theDialog, ZoneListOutlineItem);

			/* we're showing the zone list */
			globs->zoneListShown = true;
		}
	}

} /* FixListRects() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FixMachRects
 *
 * DESCRIPTION:	Adjust the bottoms of the machine list and outline
 *				rectangles when zones appear and disappear.
 *
 * INPUTS:		theDialog:		PPC Browser dialog
 *				bottDelta:		How much to adjust the bottom of the rects by.
 *
 * OUTPUTS:		Nothing.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
FixMachRects(DialogPtr theDialog, short bottDelta)
{
	short		type;
	Handle		h;
	Rect		r;

	/* first, do the machine list */
	GetDItem(theDialog, MachListItem, &type, &h, &r);
	InvalRect(&r);
	r.bottom += bottDelta;
	SetDItem(theDialog, MachListItem, type, h, &r);
	InvalRect(&r);

	/* and the machine list outline */
	GetDItem(theDialog, MachListOutlineItem, &type, &h, &r);
	InvalRect(&r);
	r.bottom += bottDelta;
	SetDItem(theDialog, MachListOutlineItem, type, h, &r);
	InvalRect(&r);

} /* FixMachRects() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		GetSelectedCell
 *
 * DESCRIPTION:	Get first cell selected in specified list, if any.
 *
 * INPUTS:		list:			Handle to list to be checked.
 *
 * OUTPUTS:		theCell:		Pointer to cell selected, if any.
 * 
 * RETURNS:		TRUE if a selected cell was found, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	12-24-87	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1987
 *	All rights reserved.
 *
 */
Boolean
GetSelectedCell(ListHandle list, Cell *theCell)
{	
	/* start with first cell */
	theCell->h = 0;
	theCell->v = 0;
	
	return(LGetSelect(true, theCell, list));

} /* GetSelectedCell() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		GetSelectedText
 *
 * DESCRIPTION:	Get text of first cell selected in specified list.
 *				Assumes all cells are Str32.
 *
 * INPUTS:		list:			Handle to list to be checked.
 *				theText:		Pointer to buffer to text.
 *
 * OUTPUTS:		theText:		Text of the cell (pascal string).
 *				theCell:		Pointer to cell selected, if any.
 * 
 * RETURNS:		TRUE if a selected cell was found, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-29-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
Boolean
GetSelectedText(ListHandle list, char *theText, Cell *theCell)
{
	short		len;
	Boolean		rc;
	
	/* get currently selected cell */
	if (rc = GetSelectedCell(list, theCell))
	{
		/* cell currently selected, get its text */
		len = 32;
		LGetCell(&(theText[1]), &len, *theCell, list);
		theText[0] = len;
	}
	else
	{
		/* no cell selected */
		theText[0] = '\0';
	}
	
	return(rc);

} /* GetSelectedText() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SelectAndReveal
 *
 * DESCRIPTION:	Select and reveal a cell in a list.
 *				If cell is already visible, just select it.
 *				Otherwise, try to make the cell topmost
 *				in the list, then select it.
 *
 * INPUTS:		theCell:		Cell to select.
 *				theList:		List with cell.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
SelectAndReveal(Cell theCell, ListHandle theList)
{	
	/* see if cell is visible */
	HLock((Handle)theList);
	if (!PtInRect(theCell, &((**theList).visible)))
	{
		/* cell not visible, try to make it topmost in list */
		LScroll(0, theCell.v - (**theList).visible.top, theList);
	}
	HUnlock((Handle)theList);
	
	/* select cell */
	LSetSelect(true, theCell, theList);
	
} /* SelectAndReveal() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SelectAndRevealArrows
 *
 * DESCRIPTION:	Select and reveal a cell in a list when
 *				an arrow key is hit.  If cell is already visible,
 *				just select it.  Otherwise, scroll the cell into
 *				view and then select it.
 *
 * INPUTS:		theCell:		Cell to select.
 *				theList:		List with cell.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
SelectAndRevealArrows(Cell theCell, ListHandle theList)
{
	short		offset;
	
	/* select cell */
	LSetSelect(true, theCell, theList);
	
	/* see if cell is visible */
	HLock((Handle)theList);
	if (!PtInRect(theCell, &((**theList).visible)))
	{
		/* no, need to scroll into view */
		if (theCell.v <= (**theList).visible.top)
		{
			/* need to scroll up */
			offset = theCell.v - (**theList).visible.top;
		}
		else
		{
			/* need to scroll down */
			offset = theCell.v - (**theList).visible.bottom + 1;
		}

		LScroll(0, offset, theList);
	}
	HUnlock((Handle)theList);
	
} /* SelectAndRevealArrows() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SelectAndRevealRelative
 *
 * DESCRIPTION:	Select and reveal a cell in a list, trying to center it
 *				in the middle.
 *
 * INPUTS:		theCell:		Cell to select.
 *				theList:		List with cell.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
SelectAndRevealRelative(Cell theCell, ListHandle theList)
{
	short		middle;
	
	/* calculate middle of visible rectangle */
	middle = (((**theList).visible.bottom - (**theList).visible.top) / 2)
				+ (**theList).visible.top;
	
	/* are we in the middle? */
	if (theCell.v != middle)
	{
		LScroll(0, theCell.v - middle, theList);
	}

	/* select cell */
	LSetSelect(true, theCell, theList);
	
} /* SelectAndRevealRelative() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FindAndSelectCell
 *
 * DESCRIPTION:	Find and select cell with specified data in list.
 *
 *				Still to do: may need to pass in comparison routine to LSearch.
 *
 * INPUTS:		theList:		List with cell.
 *				theText:		Data to find.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		TRUE if cell found, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-27-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
Boolean
FindAndSelectCell(ListHandle theList, char *theText)
{
	Cell	theCell, oldCell;

	/* find the specified cell and select it */
	theCell.h = 0;
	theCell.v = 0;
	if (LSearch(&(theText[1]), (short)theText[0], NULL, &theCell, theList))
	{
		if (GetSelectedCell(theList, &oldCell))
		{
			LSetSelect(false, oldCell, theList);
		}
	
//		SelectAndRevealRelative(theCell, theList);
		SelectAndReveal(theCell, theList);
		return(true);
	}
	else
		return(false);

} /* FindAndSelectCell() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FindAndSelectPortInfoCell
 *
 * DESCRIPTION:	Find and select cell with specified PortInfoRec in list.
 *				Does not match on authRequired, only PortName field in PortInfoRec.
 *
 *				Still to do: may need to pass in comparison routine to LSearch.
 *
 * INPUTS:		theList:		List with cell.
 *				thePortInfo:	PortInfoRec to find.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		TRUE if cell found, FALSE otherwise.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	04-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
Boolean
FindAndSelectPortInfoCell(ListHandle theList, PortInfoRec *thePortInfo)
{
	Cell			theCell, oldCell;
	Boolean			done, foundit = false;
	short			theLen;
	ApplListData	theData;
	
	/* find the first cell with the right name */
	theCell.h = 0;
	theCell.v = 0;
	if (LSearch(&(thePortInfo->name.name[1]), (short)thePortInfo->name.name[0],
		NULL, &theCell, theList))
	{
		/* found cell, now compare the rest of the PortInfoRec */
		done = false;
		theCell.h = 1;
		do
		{
			/* get current PortInfoRec */
			theLen = sizeof(ApplListData);
			LGetCell((Ptr)&theData, &theLen, theCell, theList);
			
			/* compare it */

			/* compare nameScript (not done by ComparePortName) */
			if ((thePortInfo->name.nameScript ==
				theData.thePortInfo.name.nameScript) &&
				(ComparePortName(&(thePortInfo->name),
					&(theData.thePortInfo.name)) == 0))
			{
				/* found it */
				done = true;
				foundit = true;
			}
			else
			{
				/* check next cell */
				theCell.v++;
				if (theCell.v == (**theList).dataBounds.bottom)
				{
					/* went off end of list */
					done = true;
				}
			}
		} while (!done);
		
		if (foundit)
		{
			/* found it, unselect any old cell */
			if (GetSelectedCell(theList, &oldCell))
			{
				LSetSelect(false, oldCell, theList);
			}
			
			/* select first column */
			theCell.h = 0;
		
	//		SelectAndRevealRelative(theCell, theList);
			SelectAndReveal(theCell, theList);
		}
	}

	return(foundit);
	
} /* FindAndSelectPortInfoCell() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SetupDefaultButton
 *
 * DESCRIPTION:	Enable or disable default button.
 *
 * INPUTS:		theDialog:		Pointer to the dialog with button.
 *				hilite:			Value to set contrlHilite to.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
void
SetupDefaultButton(DialogPtr theDialog, short hilite)
{
	browseGlobals	*globs;
	short			type;
	Handle			h;
	Rect			r;
	
	SetPort(theDialog);
	GetDItem(theDialog, 1, &type, &h, &r);
	
	/* is it already set correctly? */
	if ((**(ControlHandle)h).contrlHilite != hilite)
	{
		/* no, enable or disable control */
		HiliteControl((ControlHandle)h, hilite);
		
		/* set flag in globals */
		globs = GetBrowseGlobals(theDialog);
		globs->okEnabled = (hilite == buttonEnabledHilite);
	
		/* make sure outline gets redrawn correctly */
		InsetRect(&r,-4,-4);
		InvalRect(&r);
	}

} /* SetupDefaultButton() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FlashButton
 *
 * DESCRIPTION:	Flash specified button in a dialog.
 *
 * INPUTS:		theDialog:		Dialog with button.
 *				itemNo:			Item number of button.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-10-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
FlashButton(DialogPtr theDialog, short itemNo)
{
	short		type;
	long		ticks;
	Handle		h;
	Rect		r;

	/* get the button */
	GetDItem(theDialog, itemNo, &type, &h, &r);

	/* flash it */
	HiliteControl((ControlHandle)h, 1);
	ticks = TickCount() + 8L;
	while (ticks > TickCount())
		;
	HiliteControl((ControlHandle)h, 0);

} /* FlashButton() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		MyListUpdate
 *
 * DESCRIPTION:	Useritem routine to handle update events for lists in dialogs.
 *
 * INPUTS:		theDialog:			Pointer to the dialog with list.
 *				itemNo:				Item number of list.
 *
 * OUTPUTS:		Nothing.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
pascal void
MyListUpdate(DialogPtr theDialog, short itemNo)
{
	short				index;
	browseGlobals		*globs;
	RgnHandle			updargn; 
	short				itemtype;
	Handle				item;
	Rect				box;

	/* get globals from dialog */
	globs = GetBrowseGlobals(theDialog);
	
	/* figure out the right list - assumes zero based index */
	index = itemNo - ZoneListItem;
	
	/* we can get called even for hidden items, so check for a list */
	if (globs->theList[index] != NULL)
	{
		/* update the list */
		GetDItem(theDialog, itemNo, &itemtype, &item, &box);

		updargn = NewRgn();
		RectRgn(updargn, &box);
	
		LUpdate(updargn, globs->theList[index]);
	
		DisposeRgn(updargn);
	}
	
} /* MyListUpdate() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		RectOutline
 *
 * DESCRIPTION:	Useritem routine to outline a list in a dialog.
 *
 * INPUTS:		theDialog:			Pointer to the dialog with list.
 *				itemNo:				Item number of list.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	01-22-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
pascal void
RectOutline(DialogPtr theDialog, short itemNo)
{
	short			itemtype, index;
	browseGlobals	*globs;
	Handle			item;
	Rect			box;

	GetDItem(theDialog, itemNo, &itemtype, &item, &box);
	
	/* inset item rectangle to get real outline */
	InsetRect(&box, 1 + listFrameSize, 1 + listFrameSize);
	PenSize(1,1);
	FrameRect(&box);

	/* get globals from dialog */
	globs = GetBrowseGlobals(theDialog);
	
	/* figure what list we are - assumes zero based index */
	index = itemNo - ZoneListOutlineItem;
	
	/* is this the active list? */
	if (globs->currList == index)
		/* yes, draw the frame around it */
		FrameList(theDialog, index);
	
} /* RectOutline() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		FrameList
 *
 * DESCRIPTION:	Frame (or erase frame if PenMode set right) specified list.
 *
 * INPUTS:		theDialog:		Pointer to dialog.
 *				index:			Index of list.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-09-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
FrameList(DialogPtr theDialog, short index)
{
	short			itemNo;
	Handle			itemH;
	short			itemT;
	Rect			itemR;
	
	/* figure out item number of outline - assumes zero based index */
	itemNo = index + ZoneListOutlineItem;

	/* get the box */
	GetDItem(theDialog, itemNo, &itemT, &itemH, &itemR);
	
	/* use thick pen */
	PenSize(listFrameSize, listFrameSize);
	
	/* frame it */
	FrameRect(&itemR);
	
	PenNormal();

} /* FrameList() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		BtnOutline
 *
 * DESCRIPTION:	Useritem routine to outline a button in a dialog.
 *				Outlines in black or gray depending on okEnabled in globals.
 *
 * INPUTS:		theDialog:			Pointer to the dialog with button.
 *				itemNo:				Item number of button.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	04-24-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 *
 */
pascal void
BtnOutline(DialogPtr theDialog, short itemNo)
{
	browseGlobals	*globs;
	short		itemtype;
	Handle		item;
	Rect		box;
	PenState	pnState;
	
	globs = GetBrowseGlobals(theDialog);

	GetPenState(&pnState);

	GetDItem(theDialog, itemNo, &itemtype, &item, &box);
	PenSize(3,3);
	InsetRect(&box,-4,-4);

	if (!(globs->okEnabled))
	{
		/* button disabled, use gray */
		PenPatGray();
	}

	FrameRoundRect(&box,16,16);

	SetPenState(&pnState);

} /* BtnOutline() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		CenterTitleProc
 *
 * DESCRIPTION:	User item procedure to draw centered titles.
 *				Used to draw prompt and titles for the three lists.
 *
 * INPUTS:		dialog:			Pointer to dialog.
 *				item:			Item number.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
pascal void
CenterTitleProc(DialogPtr dialog, short item)
{
	Handle			itemH;
	short			itemT;
	Rect			itemR;
	browseGlobals	*globs;
	char			str[256];
	
	GetDItem(dialog, item, &itemT, &itemH, &itemR);
	
	/* get the appropriate string */
	switch (item)
	{
		case PromptText:
			/* read prompt from globals */
			globs = GetBrowseGlobals(dialog);
			BlockMove(globs->promptStr, str, globs->promptStr[0] + 1);
			break;
		
		case ZoneText:
			GetIndString(str, BrowseSTR, ZoneTitle);
			break;
		
		case MachText:
			GetIndString(str, BrowseSTR, MachTitle);
			break;
		
		case ApplText:
			/* special case - can be customized */
			globs = GetBrowseGlobals(dialog);
			BlockMove(globs->applListTitle, str, globs->applListTitle[0] + 1);
			break;
	}

	/* use Chicago 12 */
	TextFont(0);
	TextSize(12);

	TextBox(&(str[1]), str[0], &itemR, teJustCenter);
	
	/* restore for list stuff */
	TextFont(listFont);
	TextSize(listFontSize);

} /* CenterTitleProc() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		SetItemHandle
 *
 * DESCRIPTION:	Sets item's handle.
 *
 * INPUTS:		dialog:			Pointer to dialog.
 *				item:			Item number.
 *				procH:			Proc pointer.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	09-24-87	JSM - Ported from Config.
 *
 *	Copyright Apple Computer, Inc. 1987
 *	All rights reserved.
 *
 */
void
SetItemHandle(DialogPtr dialog, short item, Handle procH)
{
	short	type;
	Handle	h;
	Rect	r;
	
	GetDItem(dialog, item, &type, &h, &r);
	SetDItem(dialog, item, userItem, procH, &r);

} /* SetItemHandle() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		StartNBP
 *
 * DESCRIPTION:	Start the NBP lookup for the machine list in the current zone.
 *
 * INPUTS:		globs:			Pointer to globals.
 *				machZone:		Zone to look in.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	02-11-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
StartNBP(browseGlobals *globs, char *machZone)
{
	MPPPBPtr		pb;
	char			equalStr[2];
	
	/* are we doing an NBP lookup in our home zone? */
	globs->firstHomeLookup = (IUCompString(machZone, globs->homeZone) == 0);
	globs->machineRegistered = false;

	/* allocate parameter block for NBP */
	pb = globs->NBPpb = (MPPPBPtr)NewPtr(sizeof(MPPParamBlock));
	
	/* allocate initial return buffer for NBP */
	pb->NBPretBuffPtr = NewPtr(NBPGuess);
	
	/* look for specified entities, matching any name */
	equalStr[0] = 0x01;
	equalStr[1] = '=';
	NBPSetEntity((Ptr)&(globs->NBPEntity), equalStr, globs->theLocNBPType, machZone);
	
	/* set up fields not set up by PostNBP */
	pb->MPPioCompletion = NULL;						/* no completion routine */
	pb->NBPentityPtr = (Ptr)&(globs->NBPEntity);	/* ->entity name */
	pb->NBPretBuffSize = NBPGuess;					/* return buffer size */
	pb->NBPmaxToGet = globs->NBPMaxToGet;			/* maximum matches to get */
	
	return(PostNBP(globs));

} /* StartNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		StopNBP
 *
 * DESCRIPTION:	Stops the current NBP lookup.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
StopNBP(browseGlobals *globs)
{
	MPPPBPtr		pb = globs->NBPpb;
	
	/* make sure there is a lookup in progress */
	if (pb == NULL)
		return;
	
	/* is the lookup done? */
	if (pb->MPPioResult > 0)
	{
		/* no, let's kill it */
		KillNBP(pb);
	}
	
	/* clean up buffers */
	DisposPtr(pb->NBPretBuffPtr);
	DisposPtr((Ptr)pb);
	globs->NBPpb = NULL;
	
} /* StopNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		KillNBP
 *
 * DESCRIPTION:	Kills the current NBP lookup.
 *
 * INPUTS:		pb:				MPPPBPtr to kill.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
KillNBP(MPPPBPtr pb)
{
	MPPParamBlock	killPB;

	/* kill specified NBP lookup */
	killPB.NBPnKillQEl = (Ptr)pb;		/* pb to kill */
	PKillNBP(&killPB, false);			/* kill synchronously */
	
} /* KillNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		PollNBP
 *
 * DESCRIPTION:	Check to see if any new names have arrived in the in-progress
 *				NBPLookup.  If any have, make sure they're unique and add
 *				them to the machine list.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
PollNBP(browseGlobals *globs)
{
	MPPPBPtr		pb = globs->NBPpb;
	ListHandle		theList;
	short			i, currNumGotten, numNew, rc;
	Cell			theCell;
	Boolean			unique, listChanged;
	short			myNode, myNet, currNet;
	MachListData	theData;
	Ptr				currResponse, currNetPtr;
	char			*currSelection;
	Str32			homeMachine;
	
	/*
		First, check to see if we are still waiting
		to do the next NBP lookup.
	*/

	if (globs->NBPBackingOff)
	{
		/* yes, check if we're done waiting */
		if (TickCount() >= globs->NBPBackoff)
		{
			/* yes, post a new NBP lookup */
			rc = PostNBP(globs);
		}
		else
			/* still backing off */
			rc = noErr;
		
		return(rc);
	}
			
	/* no home machine yet */
	homeMachine[0] = '\0';
	
	/* get address of this machine */
	GetNodeAddress(&myNode, &myNet);
	
	/* mark all newly seen names as new */
	theData.age = globs->NBPMaxLives;
	theCell.h = 1;
	
	/*
		Process any newly received responses.
	*/

	currNumGotten = pb->NBPnumGotten;
	if (currNumGotten != globs->NBPNumFound)
	{
		/* we've gotten new responses */
		theList = globs->theList[MachListIndex];
		LDoDraw(false, theList);
		listChanged = false;
		currNetPtr = (Ptr)&currNet;
		
		do
		{
			/* point to first new response in return buffer */
			currResponse = pb->NBPretBuffPtr + globs->NBPOffset;
	
			/* only look at new ones */
			numNew = currNumGotten - globs->NBPNumFound;
			
			/* insert any names found */
			for(i=1; i<=numNew; i++)
			{
				/* get current net, avoiding address errors */
				*currNetPtr = *(unsigned char*)(currResponse + tupleNet);
				*(currNetPtr + 1) = *(unsigned char*)(currResponse + tupleNet + 1);

				/* see if this entity is on this machine */
				if ((*((unsigned char*)(currResponse + tupleNode)) == myNode) &&
						(currNet == myNet))
				{
					/* this is in our machine */
					BlockMove(currResponse + tupleName, homeMachine,
						(currResponse + tupleName)[0] + 1);
					theData.isHomeMachine = true;
					
					/* set flag in globals */
					globs->machineRegistered = true;
				}
				else
				{
					/* this is not our machine */
					theData.isHomeMachine = false;
				}
					
				/* try to insert it */
				theCell.v = InsertListCell(currResponse + tupleName, theList, &unique);
				
				if (unique)
				{
					/* cell was unique, so list has changed */
					listChanged = true;
					
					/* if it was inserted before the current cell, need to update */
					if (theCell.v <= globs->machCell)
						globs->machCell++;
				}
				
				/* mark it as new */
				LSetCell((Ptr)&theData, sizeof(MachListData), theCell, theList);
				
				/* bump currResponse to next response */
				currResponse += tupleName;				/* bump past address */
				currResponse += currResponse[0] + 1;	/* bump past object name */
				currResponse += currResponse[0] + 1;	/* bump past type */
				currResponse += currResponse[0] + 1;	/* bump past zone */
			}
		
			/* update current offset */
			globs->NBPOffset = (short)(currResponse - pb->NBPretBuffPtr);
						
			/* check if any more names came in while we were working */
			globs->NBPNumFound = currNumGotten;
			currNumGotten = pb->NBPnumGotten;

		} while (currNumGotten != globs->NBPNumFound);
		
		/*
			Done processing new responses.  Now try to do
			default selection, if necessary.
		*/
		if (globs->selectingDefault)
		{
			/* see if we're selecting ourselves */
			if ((!globs->defaultSpecified) || (globs->theLoc->locationKindSelector == ppcNoLocation))
			{
				/* yes */
				currSelection = homeMachine;
			}
			else
			{
				/* use default location specified by caller */
				currSelection = &(globs->theLoc->u.nbpEntity.objStr[0]);
			}
			
			if (currSelection[0] != '\0')
			{
				/* try and select specified cell */
				if (FindAndSelectCell(theList, currSelection))
				{
					/* found it */
					NewMachSelected(globs);
				}
			}
		}

		LDoDraw(true, theList);
		
		if (listChanged)
		{
			/* need to inval the list */
			HLock((Handle)theList);
			InvalRect(&((**theList).rView));
			HUnlock((Handle)theList);
		}
		
		/*
			If the current lookup has overflowed, then stop it,
			grow the response buffer, and post a new lookup.
		*/

		if ((pb->NBPretBuffSize - globs->NBPOffset) < NBPOverflowTolerance)
		{
			/* overflowed, kill current lookup */
			KillNBP(pb);
			
			/* grow buffer and post a new lookup */
			return(GrowAndPostNBP(globs));
		}
	}
	
	/*
		Done processing new responses, now see if the lookup
		has completed.
	*/
	
	if (pb->MPPioResult <= 0)
	{
		/* lookup has completed, check for overflow */
		if ((pb->NBPretBuffSize - globs->NBPOffset) < NBPOverflowTolerance)
		{
			/* we've overflowed, grow buffer and post a new lookup */
			return(GrowAndPostNBP(globs));
		}
		else
		{
			/* no overflow, age current names */
			AgeNBP(globs);
			
			/* do we need to check for our machine? */
			if (globs->firstHomeLookup)
			{
				/* don't check anymore */
				globs->firstHomeLookup = false;
				CheckOurMachine(globs);
			}
			
			/* wait awhile before posting another lookup */
			globs->NBPBackingOff = true;
			globs->NBPBackoff = TickCount() + globs->NBPMaxIdle;
		}
	}
	
	return(noErr);

} /* PollNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		GrowAndPostNBP
 *
 * DESCRIPTION:	Grow the NBP response buffer and post a new lookup.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-08-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
GrowAndPostNBP(browseGlobals *globs)
{
	MPPPBPtr		pb = globs->NBPpb;
	unsigned short	newBuffSize;
	
	/* add increment to the buffer size and check to see if it is too large */
	newBuffSize = pb->NBPretBuffSize + NBPIncrement;
	
	if (newBuffSize <= (globs->NBPMaxToGet * NBPMaxResponseSize))
	{
		/* buffer not too large, try to increase the size */
		DisposPtr(pb->NBPretBuffPtr);
		pb->NBPretBuffPtr = NewPtr(newBuffSize);
		
		if (pb->NBPretBuffPtr == NULL)
		{
			/* couldn't get larger buffer */
			pb->NBPretBuffPtr = NewPtr(pb->NBPretBuffSize);
		}
		else
		{
			/* got new buffer */
			pb->NBPretBuffSize = newBuffSize;
		}
	}

	/* post new lookup */
	return(PostNBP(globs));

} /* GrowAndPostNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		AgeNBP
 *
 * DESCRIPTION:	Go through the list of machines and age and delete any which
 *				are too old.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Nothing.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
void
AgeNBP(browseGlobals *globs)
{
	ListHandle		theList;
	short			numRows, theLen;
	Cell			theCell;
	MachListData	theData;
	
	theList = globs->theList[MachListIndex];
	
	/* we're looking at the second column */
	theCell.h = 1;
	
	/* see how many rows to check */
	numRows = (**theList).dataBounds.bottom - (**theList).dataBounds.top;
	
	/* scan the list from the bottom up */
	while (numRows != 0)
	{
		/* get age data on current cell */
		theLen = sizeof(MachListData);
		theCell.v = numRows-1;
		LGetCell((Ptr)&theData, &theLen, theCell, theList);
		
		/* don't age our own machine */
		if (!theData.isHomeMachine)
		{
			if (theData.age <= 0)
			{
				/* this cell has aged too much, delete it */
				LDelRow(1, numRows-1, theList);
	
				/* are we deleting the currently selected cell? */
				if (numRows-1 == globs->machCell)
				{
					/* yes, update */
					NewMachSelected(globs);
				}
				else if (numRows-1 < globs->machCell)
				{
					/* deleting a row before currently selected cell */
					globs->machCell--;
				}
			}
			else
			{
				/* age this cell */
				theData.age--;
			
				LSetCell((Ptr)&theData, sizeof(MachListData), theCell, theList);
			}
		}
		
		/* move to next row */
		numRows--;
	}

} /* AgeNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		PostNBP
 *
 * DESCRIPTION:	Posts a new NBP lookup.  Resets NBPnumGotten, NBPcount,
 *				and NBPinterval in the MPPPBPtr, and NBPBackingOff,
 *				NBPNumFound, and NBPOffset in the globals, then calls PLookupName.
 *				If PLookupName does not start successfully, cleans up.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors from PLookupName.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
PostNBP(browseGlobals *globs)
{
	MPPPBPtr		pb = globs->NBPpb;
	short			rc;

	/* initialize globals */
	globs->NBPBackingOff = false;				/* we're not backing off */
	globs->NBPNumFound = 0;						/* we've haven't fetched any */
	globs->NBPOffset = 0;						/* responses yet */

	pb->NBPnumGotten = 0;						/* NBP lookup hasn't gotten any yet */
	pb->NBPinterval = globs->NBPInterval;		/* retry interval */
	pb->NBPcount = globs->NBPCount;				/* retry count */
	
	/* start asynchronous lookup */
	rc = PLookupName(pb, true);

	if (rc != noErr)
	{
		/* PLookupName failed, clean up */
		DisposPtr(pb->NBPretBuffPtr);
		DisposPtr((Ptr)pb);
		globs->NBPpb = NULL;
	}
	
	return(rc);

} /* PostNBP() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		StartListPorts
 *
 * DESCRIPTION:	Start the IPCListPorts call for the specified location.
 *
 * INPUTS:		globs:			Pointer to globals.
 *				portLocName:	Location of port.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
StartListPorts(browseGlobals *globs, LocationNameRec *portLocName)
{
	IPCListPortsPBPtr	pb;
	
	/* allocate parameter block for IPCListPorts */
	globs->PPCpb = pb = (IPCListPortsPBPtr)NewPtr(sizeof(IPCListPortsPBRec));
	
	/* allocate initial return buffer for IPCListPorts */
	pb->bufferPtr = (PortInfoRec*)NewPtr(PPCGuess * sizeof(PortInfoRec));
	
	/* save specified location in globals */
	BlockMove((Ptr)portLocName, (Ptr)&(globs->PPCLoc), sizeof(LocationNameRec));
	
	/* set up pb for IPCListPorts */
	pb->ioCompletion = NULL;				/* no completion routine */
	pb->requestCount = PPCGuess;			/* start with PPCGuess ports max */
	pb->portName = &(globs->PPCPort);		/* port name to look for */
	pb->locationName = &(globs->PPCLoc);	/* location to look in */
	
	/* start the IPCListPorts asynchronously */
	return(PostListPorts(globs));

} /* StartListPorts() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		StopListPorts
 *
 * DESCRIPTION:	Stops the current IPCListPorts.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
StopListPorts(browseGlobals *globs)
{
	IPCListPortsPBPtr	pb = globs->PPCpb;
	
	/* make sure there is an IPCListPorts in progress */
	if (pb == NULL)
		return(noErr);
	
	/* is the IPCListPorts done? */
	if (pb->ioResult > 0)
	{
		/* no, let's kill it */
		KillListPorts(pb);
	}
	
	/* clean up buffers */
	DisposPtr((Ptr)pb->bufferPtr);
	DisposPtr((Ptr)pb);
	globs->PPCpb = NULL;
	
	return(noErr);

} /* StopListPorts() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		KillListPorts
 *
 * DESCRIPTION:	Kills the current IPCListPorts.
 *
 * INPUTS:		pb:				MPPPBPtr to kill.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors from PKillNBP.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-03-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
KillListPorts(IPCListPortsPBPtr pb)
{	
	/* this could take some time for now */
	SetCursor(*GetCursor(watchCursor));
	
	/* for now, just wait for it to complete */
	while (pb->ioResult > 0)
		;
	
	InitCursor();

	return(noErr);
	
} /* KillListPorts() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		PollListPorts
 *
 * DESCRIPTION:	Check to see if the current IPCListPorts has completed.
 *				If it has, add any new ports to the list and delete ones
 *				that no longer exist.  Handles overflows, too.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
PollListPorts(browseGlobals *globs)
{
	IPCListPortsPBPtr		pb = globs->PPCpb;
	PortInfoRec				*portInfo;
	PPCFilterProcPtr		portFilter;
	ListHandle				theList;
	short					numRows, theLen;
	short					i, rc;
	Cell					theCell;
	Boolean					unique, listChanged;
	ApplListData			theData;
	unsigned short			newBuffSize;
	Boolean					portOK;
//	char					tempstr[255];
	
	/*
		First, check to see if we are still waiting
		to do the next IPCListPorts.
	*/

	if (globs->PPCBackingOff)
	{
		/* yes, check if we're done */
		if (TickCount() >= globs->PPCBackoff)
		{
			/* yes, post a new IPCListPorts */
			rc = PostListPorts(globs);
		}
		else
			/* still backing off */
			rc = noErr;
		
		return(rc);
	}
			
	/* is the current list ports done? */
	if (pb->ioResult > 0)
	{
		/* no, let's wait some more */
		return(noErr);
	}
	
//	if (pb->ioResult != noErr)
//	{
//		sprintf(tempstr, "PollListPorts: error - %d", pb->ioResult);
//		c2pstr(tempstr);
//		DebugStr(tempstr);
//	}
	
	if (pb->ioResult == noResponseErr)
	{
		/*
			We get tons of these errors because the PPCToolbox doesn't
			do an NBP lookup long enough.  Just ignore it and start over.
		*/
		
		/* post a new IPCListPorts */
		return(PostListPorts(globs));
	}
	
	/*
		The current IPCListPorts has completed, so we have to
		process the responses.  First, mark all current ports
		in the list as no longer existing.
	*/
	theList = globs->theList[ApplListIndex];
	theCell.h = 1;
	numRows = (**theList).dataBounds.bottom - (**theList).dataBounds.top;
	
	LDoDraw(false, theList);
	listChanged = false;
	
	while (numRows != 0)
	{
		/* get data on current cell */
		theLen = sizeof(ApplListData);
		theCell.v = numRows-1;
		LGetCell((Ptr)&theData, &theLen, theCell, theList);
		
		/* set exists to false for current cell */
		theData.exists = false;
		LSetCell((Ptr)&theData, sizeof(ApplListData), theCell, theList);
		
		/* move to next row */
		numRows--;
	}
	
	/* get current filter proc, if any */
	portFilter = globs->portFilter;
	
	/*
		Now, go through all the returned ports and try to
		add them to the list.
	*/

	/* start at the beginning of the buffer */
	portInfo = (PortInfoRec*)pb->bufferPtr;
	
	for (i = 1; i <= pb->actualCount; i++)
	{
		/* try to add current port to list */
		theCell.v = InsertListCell(&(portInfo->name.name[0]), theList,
			&unique);
		
		if (!unique)
		{
			/*
				Tried to insert a port with the same name.
				Note that we can have port's with the same name, but
				the type could be different.  We will show these twice,
				in a consistent order, although they will look the same
				in the list.
			*/
			theCell.v = InsertPortInfo(portInfo, theList, &unique);
		}
		
		portOK = true;
		
		if (portFilter != NULL)
		{
			if (unique)
			{
//				sprintf(tempstr, "PollListPorts - inserting at row %d", theCell.v);
//				c2pstr(tempstr);
//				DebugStr(tempstr);

				/* cell was unique, so it hasn't been filtered yet */
				if (!(portOK = (portFilter)(&(globs->PPCLoc),
					portInfo)))
				{
					/* filter proc rejected it, so delete the cell we just inserted */
					LDelRow(1, theCell.v, theList);
				}
			}
			else
			{
				/*
					The cell wasn't unique, so it passed the filter proc already.
					However, some characteristics of the PortInfoRec may have
					changed (e.g. authRequired), so check to make sure.
				*/
	
				/* get data on current cell */
				theLen = sizeof(ApplListData);
				LGetCell((Ptr)&theData, &theLen, theCell, theList);
				
				/* has the PortInfoRec changed? */
				if (!ComparePortInfo(&(theData.thePortInfo), portInfo))
				{
					/* yes, run it through the filterProc again */
					if (!(portOK = (portFilter)(&(globs->PPCLoc),
						portInfo)))
					{
						/* filter proc rejected it, so delete the cell */
						LDelRow(1, theCell.v, theList);
					}
				}
			}
		}
		
		if (portOK)
		{
			/* port wasn't filtered out */
					
			/* get data on current cell */
			theLen = sizeof(ApplListData);
			LGetCell((Ptr)&theData, &theLen, theCell, theList);
			
			/* this port exists */
			theData.exists = true;
			
			/* update the PortInfoRec (not always necessary, but big deal) */
			BlockMove((Ptr)portInfo, (Ptr)&(theData.thePortInfo),
				sizeof(PortInfoRec));
			
			if (unique)
			{
				/* cell was unique, so list has changed */
				listChanged = true;
				
				/* if it was inserted before the current cell, need to update */
				if (theCell.v <= globs->applCell)
					globs->applCell++;
			}
			
			/* set the new cell data */
			LSetCell((Ptr)&theData, sizeof(ApplListData), theCell, theList);
		}
		
		/* move to the next returned port */
		portInfo++;
	}
	
	/* make sure everything gets updated */
	LDoDraw(true, theList);
	
	if (listChanged)
	{
		/* need to inval the list */
		HLock((Handle)theList);
		InvalRect(&((**theList).rView));
		HUnlock((Handle)theList);
	}
		
	/*
		We've gone through all of the returned ports.  Now, delete any
		ports from the list that no longer exist.
	*/
	numRows = (**theList).dataBounds.bottom - (**theList).dataBounds.top;
	
	while (numRows != 0)
	{
		/* get data on current cell */
		theLen = sizeof(ApplListData);
		theCell.v = numRows-1;
		LGetCell((Ptr)&theData, &theLen, theCell, theList);
		
		if (!theData.exists)
		{
			/* port no longer exists, delete it */
			LDelRow(1, numRows-1, theList);

			/* are we deleting the currently selected cell? */
			if (numRows-1 == globs->applCell)
			{
				/* yes, update */
				NewApplSelected(globs);
			}
			else if (numRows-1 < globs->applCell)
			{
				/* deleting a row before currently selected cell */
				globs->applCell--;
			}
		}
		
		/* move to next row */
		numRows--;
	}
	
	/*
		Now, try to do default selection, if necessary.
	*/
	
	if (globs->selectingDefault)
	{
		/* see if we have to select a specified application */
		if (globs->defaultSpecified)
		{
			/* yes, try and find it */
			if (FindAndSelectPortInfoCell(theList, globs->thePortInfo))
			{
				/* found it */
				NewApplSelected(globs);
				
				/* we're done default selecting */
				globs->selectingDefault = false;
			}
		}
		else
		{
			/* no default selection from caller, just select first in list */
			if ((**theList).dataBounds.top != (**theList).dataBounds.bottom)
			{
				/* list isn't empty, select first cell */
				theCell.h = 0;
				theCell.v = 0;
//				SelectAndRevealRelative(theCell, theList);
				SelectAndReveal(theCell, theList);
				NewApplSelected(globs);
				
				/* we're done default selecting */
				globs->selectingDefault = false;
			}
		}
		
	}

	/*
		We're done processing the IPCListPorts, if we have overflowed
		increase the buffer size and post a new list ports.
	*/
	if (pb->actualCount == pb->requestCount)
	{
		/* returned all ports we have room for, increment buffer */
		newBuffSize = (pb->requestCount + PPCIncrement) * sizeof(PortInfoRec);
		
		/* is it too large? */
		if (newBuffSize <= (globs->PPCMaxToGet * sizeof(PortInfoRec)))
		{
			/* no, try to increase the size */
			DisposPtr((Ptr)pb->bufferPtr);
			pb->bufferPtr = (PortInfoRec*)NewPtr(newBuffSize);
			
			if (pb->bufferPtr == NULL)
			{
				/* couldn't get larger buffer */
				pb->bufferPtr = (PortInfoRec*)NewPtr(pb->requestCount * sizeof(PortInfoRec));
			}
			else
			{
				/* got new buffer */
				pb->requestCount += PPCIncrement;
			}
		}
		
		/* list it again */
		return(PostListPorts(globs));
	}
	
	/* now, lets wait awhile before doing another ListPorts */
	globs->PPCBackingOff = true;
	globs->PPCBackoff = TickCount() + globs->PPCMaxIdle;
	
	return(noErr);

} /* PollListPorts() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		PostListPorts
 *
 * DESCRIPTION:	Posts a new IPCListPorts.  Resets PPCBackingOff
 *				in the globals, and startIndex and actualCount in the
 *				IPCListPortParams, then calls IPCListPorts.  If IPCListPorts
 *				does not start successfully, cleans up.
 *
 * INPUTS:		globs:			Pointer to globals.
 *
 * OUTPUTS:		None.
 * 
 * RETURNS:		Errors from PLookupName.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	03-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
OSErr
PostListPorts(browseGlobals *globs)
{
	IPCListPortsPBPtr	pb = globs->PPCpb;
	short	rc;
	
	globs->PPCBackingOff = false;
	pb->startIndex = 0;							/* start with first port */
	pb->actualCount = 0;						/* haven't gotten any ports yet */
	
	rc = IPCListPorts(pb, true);				/* start asynchronous list ports */

	if (rc != noErr)
	{
		/* IPCListPorts failed, clean up */
		DisposPtr((Ptr)pb->bufferPtr);
		DisposPtr((Ptr)pb);
		globs->PPCpb = NULL;
	}
	
	return(rc);

} /* PostListPorts() */

/*FORM_FEED*/
/*
 *
 * OBJECT:		InsertPortInfo
 *
 * DESCRIPTION:	InsertListCell has said that a cell with the specified port name
 *				already exists in the list.  For ports, however, duplicate
 *				name's are OK, so we have to see if the port specified by
 *				thePortInfo is really there.
 *
 *				We can't do a binary search, since we have to find the first
 *				entry in the list with the specified port name.  The location
 *				of the duplicate found by InsertListCell isn't used here because
 *				InsertListCell uses a binary search, so it may not be the first match
 *				in the list.
 *
 *				The secondary sorting on ports is based on the type.  The actual sort
 *				method used isn't that important, since they'll all look the same to
 *				the user anyway.  However, it needs to be consistent, since theoretically
 *				IPCListPorts can return ports in any order (although in reality it doesn't
 *				at the moment).  See the header on ComparePortName for more information
 *				on the sorting method used.
 *
 *				As in InsertListCell, it only inserts unique cells, and sets unique to FALSE
 *				if the cell already exists.  Returns row where cell was inserted, or
 *				row where matching cell exists.
 *
 *				Still to do: may need to pass in comparison routine to LSearch.
 *
 * INPUTS:		thePortInfo:		Pointer to PortInfoRec to insert.
 *				theList:			Port list.
 *
 * OUTPUTS:		unique:				TRUE if cell was unique and inserted, FALSE otherwise.
 * 
 * RETURNS:		Row where cell was inserted or matching cell exists.
 *
 * EFFECTS:		None.
 *
 * MODIFICATIONS:
 *	04-06-90	JSM - Created.
 *
 *	Copyright Apple Computer, Inc. 1990
 *	All rights reserved.
 */
short
InsertPortInfo(PortInfoRec *thePortInfo, ListHandle theList, Boolean *unique)
{
	Boolean			done;
	short			compResult;
	short			theLen;
	Cell			theCell;
	ApplListData	theData;
	
	/* find the first matching cell in the list */
	theCell.h = 0;
	theCell.v = 0;
	
	/* this LSearch should work, since InsertListCell found a match already */
	LSearch(&(thePortInfo->name.name[1]), (short)thePortInfo->name.name[0],
		NULL, &theCell, theList);

	/* 
		Now, go down through the list of matching cells and
		figure out where to put this one.
	*/
	theCell.h = 1;
	done = false;
	while (!done)
	{
		/* get PortInfoRec for current cell */
		theLen = sizeof(ApplListData);
		LGetCell((Ptr)&theData, &theLen, theCell, theList);
		
		/* compare the names */
		compResult = ComparePortName(&(thePortInfo->name),
			&(theData.thePortInfo.name));
		
		if (compResult <= 0)
		{
			/* same ports, or port to insert < current port, so we're done */
			done = true;
			*unique = (compResult != 0);
		}
		else
		{
			/* port to insert still > current port */

			/* check next cell */
			theCell.v++;
			
			/* are we off the end of the list? */
			if (theCell.v == (**theList).dataBounds.bottom)
			{
				/* yes, insert cell at the end */
				done = true;
				*unique = true;
			}
		}
	} /* while (!done) */

	if (*unique == true)
	{
		/* cell was unique, insert it */
		LAddRow(1, theCell.v, theList);

		/* set the port name in column 0, PollListPorts sets column 1 */
		theCell.h = 0;
		LSetCell(&(thePortInfo->name.name[1]), thePortInfo->name.name[0],
			theCell, theList);
	}
	
	return(theCell.v);	

} /* InsertPortInfo() */
