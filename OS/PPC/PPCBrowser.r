/*
	File:		PPCBrowser.r

	Contains:	Resources for the PPC Browser.
				This file assumes SystemSevenOrBetter.
				Don't set resource attributes here, done in Sys.r.

	Written by:	Jeff Miller

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	11/18/92	GMA		added type def for 'ppci' and resource def for 'ppci' -16409 so
									we can include this resource in ROM.
		 <3>	 9/12/90	JSM		Update to latest help strings.
		 <2>	 8/21/90	JSM		Add default prompt, change default port list title.
		 <1>	  8/2/90	JSM		First checked in.

*/

#include "Types.r"
#include "SysTypes.r"
#include "BalloonTypes.r"

// resource ID for all browser resources
#define browserResID		-5856

// browser configuration resource
resource 'ppcc' (browserResID) {
	1,		// NBP lookup interval
	5,		// NBP lookup count
	9,		// NBP maximum lives an entry has before deletion
	256,	// NBP maximum number of entities
	120,	// NBP idle time in ticks between lookups
	128,	// PPC maximum number of ports
	120		// PPC idle time in ticks between list ports
};
type 'ppci'															// <SM2><GMA>
{
	byte;		// freePortMin
	byte;		// freePortMax
	byte;		// freeLocSessMin
	byte;		// freeLocSessMax
	byte;		// freeRemSessMin
	byte;		// freeRemSessMax
	byte;		// freeIPMSessMin
	byte;		// freeIPMSessMax
	byte;		// ADSP time out (6 = 1 sec)
	byte;		// ADSP Retries
	byte;		// NBP time out interval 8-tick units
	byte;		// NBP retries
	pstring;	// NBP Type of PPC Toolbox.
};


resource 'ppci' (-16409)											// <SM2><GMA>
{
	1,2,			// Min,Max of PPC Ports
	1,2,			// Min,Max of Loc Sess
	1,2,			// Min,Max of Rem Sess
	0,1,			// Min,Max of IPM Sess
	30,				// 5 Seconds
	4,				// 4 Retries
	1,				// NBP Lookup Interval <264>
	18,				// NBP Lookup Count <264>
	"PPCToolBox"	// NBP Type of PPC Toolbox.
};

// browser dialog
resource 'DLOG' (browserResID) {
	{0, 0, 268, 442},
	dBoxProc,
	invisible,
	noGoAway,
	0x0,
	browserResID,
	"",
	alertPositionMainScreen
};

// browser DITL
resource 'DITL' (browserResID) { {
		{243, 367, 263, 437},Button {enabled, "OK"},			// OK button
		{243, 283, 263, 353},Button {enabled, "Cancel"},		// Cancel button
		{243, 367, 263, 437},UserItem {disabled},				// OK button outline

		{2, 5, 18, 437},UserItem {disabled},					// prompt
		{146, 5, 162, 216},UserItem {disabled},					// zone list title
		{20, 5, 36, 216},UserItem {disabled},					// machine list title
		{20, 226, 36, 437},UserItem {disabled},					// PPC port list title

		{165, 5, 263, 216},UserItem {enabled},					// zone list
		{39, 5, 137, 216},UserItem {enabled},					// machine list
		{39, 226, 233, 437},UserItem {enabled},					// PPC port list
		{165, 5, 263, 216},UserItem {disabled},					// zone list outline
		{39, 5, 137, 216},UserItem {disabled},					// machine list outline
		{39, 226, 233, 437},UserItem {disabled},				// PPC port list outline

		{-1,-1,-1,-1},HelpItem {disabled,HMScanhdlg{browserResID}}	// help item
}};

// browser strings
resource 'STR#' (browserResID) { {
		"AppleTalk Zones",		// zone list
		"Macintoshes",			// machine list
		"Programs",				// PPC port list
		"Choose a program to link to:",		// default prompt
		"<This Macintosh>",		// name of current machine when not registered on the network

		// help string for enabled OK button
		"To confirm your selection and close this dialog box, click this button.",

		// help string for disabled OK button
		"To confirm your selection and close this dialog box, click this button."
		"  Not available now because you have not selected a program to link.",
		
		// help string for Cancel button
		"To close the dialog box without linking a program on the network, click"
		" this button.",
		
		// help string for zone list
		"To find the program you want to link and the Macintosh it's on, "
		"click the name of the zone that the Macintosh is in.",
		
		// help string for machine list
		"To choose the Macintosh that contains the program you want to link, "
		"click its name in this list.",
		
		// help string for port list
		"To link to a program, click its name in this list."
}};

// browser help

// offsets into STR# of help messages
#define hOK				6
#define hOKDimmed		7
#define hCancel			8
#define hZoneList		9
#define hMachList		10
#define hPortList		11

// help dialog template
resource 'hdlg' (browserResID) {
	HelpMgrVersion,								// Help Version
	0,											// offset to 1st item
	0,											// options
	0,											// theProc
	0,											// variant
	HMSkipItem {},								// skip missing message
	{
		HMStringResItem {						// 1 - OK button
			{0,0}, {0,0,0,0},
			browserResID, hOK,					// enabled
			browserResID, hOKDimmed,			// disabled
			browserResID, hOK,
			browserResID, hOK
		},
	
		HMStringResItem {						// 2 - Cancel button
			{0,0}, {0,0,0,0},
			browserResID, hCancel,				// enabled always
			browserResID, hCancel,
			browserResID, hCancel,
			browserResID, hCancel
		},
	
		HMSkipItem {},							// 3 - OK outline

		HMSkipItem {},							// 4 - prompt

		HMSkipItem {},							// 5 - zone list title

		HMSkipItem {},							// 6 - machine list title

		HMSkipItem {},							// 7 - PPC port list title

		HMStringResItem {						// 8 - zone list
			{0,0}, {0,0,0,0},
			browserResID, hZoneList,
			browserResID, hZoneList,
			browserResID, hZoneList,
			browserResID, hZoneList
		},
	
		HMStringResItem {						// 9 - machine list
			{0,0}, {0,0,0,0},
			browserResID, hMachList,
			browserResID, hMachList,
			browserResID, hMachList,
			browserResID, hMachList
		},
	
		HMStringResItem {						// 10 - PPC port list
			{0,0}, {0,0,0,0},
			browserResID, hPortList,
			browserResID, hPortList,
			browserResID, hPortList,
			browserResID, hPortList
		}
		
		// no help for other dialog items
}};

