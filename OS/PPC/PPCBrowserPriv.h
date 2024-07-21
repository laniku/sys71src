/*
	File:		PPCBrowserPriv.h

	Contains:	Private header file for the PPC Browser
	
	Written by:	Jeff Miller

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

    This file is used in these builds:  

	Change History (most recent first):

		<18>	  7/5/92	csd		#1034096 <gbm>: Changed listFont and listFontSize to use the
									application font and size by setting them to 1 and 0
									respectively. This will make the Browser show the lists in the
									application font which works better for other script systems.
		<17>	 3/30/92	DCL		Include StandardFile.h. It used to be indirectly included
									through Packages.h.
		<16>	 9/21/90	JSM		Use angle brackets again since we're using the real
									PPCToolbox.h, update some stuff to reflect this.
		<15>	 9/15/90	ngk		Fix include of PPCToolbox to use quotes instead of angle
									brackets
		<14>	 9/14/90	JSM		Add theLocNBPType to globals.
		<13>	 8/21/90	JSM		Add DefaultPromptStr constant.
		<12>	 7/25/90	JSM		Add ZoneListColumns, MachListColumns, and AppListColumns
									constants, define NoCellSelected explicitly as a short to reduce
									code size.
		<11>	 7/11/90	JSM		#include String.h to avoid C compiler warnings.
		<10>	 5/29/90	JSM		Update to add support for new Chooser-style interface.
		 <9>	  5/3/90	JSM		#include IntlUtilsPriv, add support for type select utilities to
									globals.
		 <8>	 4/24/90	JSM		Add okEnabled field to globals, #define buttonEnabledHilite and
									buttonDisabledHilite.
		 <7>	 3/19/90	JSM		Add support for machine not registered on network, call filter
									with PortInfo instead of PortName.
		 <6>	 3/15/90	JSM		Add support for browser configuration resource.
		 <5>	 3/14/90	JSM		Update MachListData structure to specify local machine.
		 <4>	 3/12/90	JSM		Add support for zones coming and going.
		 <3>	  3/8/90	JSM		Update to do asynchronous NBP lookups and IPCListPorts.
		 <2>	 2/20/90	JSM		Add some lowmem #defines, add hasAT to browser globals.
		 <1>	 2/19/90	JSM		First checked in.

*/

#include	<Types.h>
#include	<stdio.h>
#include	<Resources.h>
#include	<ToolUtils.h>
#include	<Memory.h>
#include	<Errors.h>
#include	<Packages.h>
#include	<StandardFile.h>			/*<17>*/
#include	<Lists.h>
#include	<IntlUtilsPriv.h>
#include	<String.h>					/* for memcmp definition */
#include	<PPCToolbox.h>

/* resource types */
#define		BrowseConfigType 'ppcc'		/* browser configuration resource */

/* resource IDs to use */
#define		BrowseConfigID	-5856		/* browser configuration */
#define		BrowseDLOGID	-5856		/* browser dialog */
#define		BrowseSTR		-5856		/* browser STR# */
#define		PPCToolboxSTR	-16409		/* STR# with entity type of PPCToolbox */
#define		PPCMachNameSTR	-16413		/* STR with machine name */

/* items in browse dialog */
#define		OKOutlineItem		3		/* outline of OK button */
#define		PromptText			4		/* prompt at top of dialog */
#define		ZoneText			5		/* title for zone list */
#define		MachText			6		/* title for machine list */
#define		ApplText			7		/* title for application list */

/* note - keep lists sequential! */
#define		ZoneListItem		8		/* zone list */
#define		MachListItem		9		/* machine list */
#define		ApplListItem		10		/* application list */

/* note - keep list outlines sequential! */
#define		ZoneListOutlineItem	11		/* outline for zone list */
#define		MachListOutlineItem	12		/* outline for machine list */
#define		ApplListOutlineItem	13		/* outline for application list */

/* indexes into BrowseSTR */
#define		ZoneTitle			1		/* title for zone list */
#define		MachTitle			2		/* title for machine list */
#define		ApplTitle			3		/* default title for application list */
#define		DefaultPromptStr	4		/* default prompt */
#define		NoMachineStr		5		/* default name of local machine when there is no machine name */

/* indexes into PPCToolboxSTR */
#define		PPCNBPType			1		/* NBP type string - "PPCToolbox" */

/* indexes into theList - keep zero based */
#define		ZoneListIndex		0
#define		MachListIndex		1
#define		ApplListIndex		2

/* number of columns in each list */
#define		ZoneListColumns		1
#define		MachListColumns		2		/* second column not displayed, used to store data for each entry */
#define		ApplListColumns		2		/* second column not displayed, used to store data for each entry */

#define		typeDelay			60		/* long delay between keys for matching */

/* value for zoneCell, machCell, and applCell when no cell selected */
#define		NoCellSelected		((short)-1)

/* font information for list cell font */
#define		listFont			1		/* geneva */
#define		listFontSize		0

#define		listFrameSize		2		/* thickness of pen for framing of active list */

#define		buttonEnabledHilite	0		/* contrlHilite of enabled button */
#define		buttonDisabledHilite 255	/* contrlHilite of disabled button */

/* constants corresponding to keys of interest */
#define		charUpArrow			0x1E	/* up arrow key */
#define		charDownArrow		0x1F	/* down arrow key */
#define		charReturn			0x0D	/* return key */
#define		charEnter			0x03	/* enter key */
#define		charDelete			0x08	/* delete/backspace key */
#define		charClear			0x1B	/* clear key on keypad */
#define		charEscape			0x1B	/* escape key is same as clear key, so… */
#define		kcEscape			0x35	/* we need the key code to be unambiguous */
#define		charTab				0x09	/* tab key */
#define		charPeriod			0x2E	/* period character for Cancel */

/* some global variables we look at */
#define		KeyThresh			*((short*)0x18E)			/* key threshold */
#define		SPConfig			*((unsigned char*)0x1FB)	/* serial port config */

/* stuff for NBP */

/* defines stolen from ATalkEqu.a so we can look directly at the NBP response buffer */
#define		tupleNet			0		/* Offset to network no. [word] */
#define		tupleNode			2		/* Offset to node ID [byte] */
#define		tupleName			5		/* Offset to name part of tuple [byte] */

/* maximum size of a single response from a lookup (in bytes) */
#define		NBPMaxResponseSize	72		/* name + type + "\p*" + addrBlock */

/* minimum number of bytes left before growing response buffer */
#define		NBPOverflowTolerance NBPMaxResponseSize

/* initial guess at how big the response buffer should be (in bytes) */
#define		NBPGuess			512

/* how much to increment the response buffer size if we overflow (in bytes) */
#define		NBPIncrement		512

/* stuff for IPCListPorts */

/* initial guess at how many PPC ports we'll get for one location */
#define		PPCGuess			5

/* how many ports to increment the buffer by if we overflow */
#define		PPCIncrement		2

/* macro to get global variables */
#define		GetBrowseGlobals(theDialog)		(browseGlobals*)GetWRefCon(theDialog)

/*
	Structure for the PPC Browser configuration resource.
	This is in 'ppcc' resource id -5856.  Default values
	are in parentheses.
*/
typedef struct
{
	unsigned char	NBPInterval;			/* NBP lookup interval (1) */
	unsigned char	NBPCount;				/* NBP lookup count (5) */
	short			NBPMaxLives;			/* NBP maximum lives an entry has before deletion (9) */
	short			NBPMaxToGet;			/* NBP maximum number of entities (256) */
	short			NBPMaxIdle;				/* NBP idle time in ticks between lookups (120) */
	short			PPCMaxToGet;			/* PPC maximum number of ports (128) */
	short			PPCMaxIdle;				/* PPC idle time in ticks between list ports (120) */

} BrowseConfigRes;

/*
	Structure for list cell data for second column of machine list.
	We never actually display this, but use it to store further
	data related to the machine in column 0.
*/
typedef struct
{
	short			age;					/* for aging entries */
	Boolean			isHomeMachine;			/* true if this is the local machine */

} MachListData;

/*
	Structure for list cell data for second column of application list.
	We never actually display this, but use it to store further
	data related to the application in column 0.
*/
typedef struct
{
	Boolean			exists;					/* set to true if it exists */
	PortInfoRec		thePortInfo;			/* from IPCListPorts */

} ApplListData;

/* global variables hung off of dialog's refCon */
typedef struct
{
	DialogPtr		theDialog;				/* pointer to dialog */
	ListHandle		theList[3];				/* zone, machine, and application lists */
	short			machListBottDelta;		/* bottom coordinate of mach list */
	short			currList;				/* index into theList of current list */
	short			zoneCell;				/* currently selected row in zone list */
	short			machCell;				/* currently selected row in mach list */
	short			applCell;				/* currently selected row in appl list */
	
	/* stuff for doing NBP lookups */
	MPPParamBlock	*NBPpb;					/* parameter block for NBP */
	long			NBPBackoff;				/* backoff timer */
	short			NBPOffset;				/* current offset into the response buffer */
	short			NBPNumFound;			/* number of names found last time we looked */
	EntityName		NBPEntity;				/* the name we're looking up */
	Str32			homeZone;				/* name of the zone we're in */
	
	/* NBP configuration info from resource */
	unsigned char	NBPInterval;			/* NBP lookup interval */
	unsigned char	NBPCount;				/* NBP lookup count */
	short			NBPMaxLives;			/* NBP maximum lives an entry has before deletion */
	short			NBPMaxToGet;			/* NBP maximum number of entities */
	short			NBPMaxIdle;				/* NBP idle time in ticks between lookups */
	
	/* stuff for listing PPC ports */
	IPCListPortsPBRec *PPCpb;				/* parameter block for IPCListPorts */
	long			PPCBackoff;				/* backoff timer */
	LocationNameRec	PPCLoc;					/* location of ports we're looking up */
	PPCPortRec		PPCPort;				/* the port we're looking up */
	
	/* PPC configuration info from resource */
	short			PPCMaxToGet;			/* PPC maximum number of ports */
	short			PPCMaxIdle;				/* PPC idle time in ticks between list ports */
	
	/* stuff for list keyboard navigation */
	TypeSelectRecord theTSR;				/* record for type selecting */
	
	/* labels in browse dialog */
	char			promptStr[256];			/* prompt */
	char			applListTitle[256];		/* title for application list */
	
	/* parameters passed in by caller */
	PPCFilterProcPtr portFilter;			/* filter for port list */
	LocationNameRec	*theLoc;				/* default location */
	PortInfoRec		*thePortInfo;			/* default port info */
	Str32			theLocNBPType;			/* NBP type to use for location lookups */
	
	/* group Booleans here for alignment */
	Boolean			NBPBackingOff;			/* true if backing off NBP lookup */
	Boolean			PPCBackingOff;			/* true if backing off listing ports */
	Boolean			machineRegistered;		/* true if our machine is registered on the network */
	Boolean			firstHomeLookup;		/* true if doing first lookup in our home zone */
	Boolean			defaultSpecified;		/* true if trying to select a specified default */
	Boolean			selectingDefault;		/* true if trying to do any default selection */
	Boolean			hasZones;				/* true if zones present */
	Boolean			hasAT;					/* true if AppleTalk enabled */
	Boolean			okEnabled;				/* true if OK button enabled */
	Boolean			zoneListShown;			/* true if zone list shown */

} browseGlobals;

