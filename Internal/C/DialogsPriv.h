/*
	File:		DialogsPrivate.h

	Contains:	C interfaces to the private Dialog Manager routines

	Written by:	Nick Kledzik

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <7>	 11/7/92	JDR		Removed the now publicly defined routines, StdFilterProc,
									GetStdFilterProc, SetDialogDefaultItem, SetDialogCancelItem,
									SetDialogTracksCursor.
		 <6>	 3/31/92	KSM		#1021993,<DTY>: DTY: #1021993: Exported CitationsCH call - now
									returns OSErr (for dispatcher). Created new calls: Cite4 for
									easy-of-use, and the fully generic CitationsSH. Added definition
									of CiteListPtr and MAXCITES beomes MAXCITATIONS.
		 <5>	 8/27/91	JSM		Cleanup header.
		 <4>	12/12/90	KSM		Fix typo.
		 <3>	 12/3/90	RLC		<ksm> Change the IsFrontWindowModal and IsWindowModal routines
									to GetFrontWindowModalClass and GetWindowModalClass.
		 <2>	10/30/90	KSM		<ngk> Add emulateOrigFilterBit equate.
		 <1>	10/29/90	ngk		first checked in
		 <0>	  10/28/90	ngk		first checked into BBS

*/

#ifndef __DIALOGSPRIV__
#define __DIALOGSPRIV__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif
//--------------------------------------------------------------------------------------

pascal OSErr GetFrontWindowModalClass(short* modalClass)
	= { 0x303C, 0x0201, 0xAA68 };

pascal OSErr GetWindowModalClass(WindowPtr theWindow, short* modalClass)
	= { 0x303C, 0x0402, 0xAA68 };

//--------------------------------------------------------------------------------------
// the following is interface to StdFilterProc features

/* bits in spareFlags */
#define	cannotTwitchOutOfDialogBit		7
#define	systemHandlesMenusBit			6
#define	systemHandlesDefaultButtonBit	5
#define	systemHandlesCancelButtonBit	4
#define	systemTracksCursorBit			3
#define emulateOrigFilterBit			2

#define	cannotTwitchOutOfDialogMask		0x80
#define	systemHandlesMenusMask			0x40
#define	systemHandlesDefaultButtonMask	0x20
#define	systemHandlesCancelButtonMask	0x10
#define	systemTracksCursorMask			0x08
#define	emulateOrigFilterMask			0x04

//--------------------------------------------------------------------------------------
// the following is interface to new citation substitution routines <6>
#define MAXCITATIONS 10
typedef StringPtr *CiteListPtr;		// Really: StringPtr[MAXCITATIONS]

pascal OSErr Cite4(StringHandle baseString,ConstStr255Param p0,ConstStr255Param p1,ConstStr255Param p2,ConstStr255Param p3)
	= { 0x303C, 0x0AFB, 0xAA68 };

pascal OSErr CitationsSH(StringHandle baseString,short numCitations,CiteListPtr citations)
	= { 0x303C, 0x07FC, 0xAA68 };

pascal OSErr CitationsCH(CharsHandle baseString,long offset,short numCitations,CiteListPtr citations)
	= { 0x303C, 0x05FD, 0xAA68 };

#endif		/* __DIALOGSPRIV__ */
