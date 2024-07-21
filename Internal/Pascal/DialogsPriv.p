{
	File:		DialogsPriv.p

	Contains:	Pascal interfaces to the Dialog Manager routines

	Written by:	Nick Kledzik

	Copyright:	© 1985-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <7>	 11/7/92	JDR		Removed the now publicly defined routines, StdFilterProc,
									GetStdFilterProc, SetDialogDefaultItem, SetDialogCancelItem,
									SetDialogTracksCursor.
		 <6>	 3/31/92	KSM		#1021993,<DTY>: Exported CitationsCH call - now returns OSErr
									(for dispatcher). Created new calls: Cite4 for easy-of-use, and
									the fully generic CitationsSH. Added definition of CiteListPtr
									and MAXCITES beomes MAXCITATIONS.
		 <5>	 8/27/91	JSM		Cleanup header.
		 <4>	 12/3/90	RLC		<ksm> Change the IsFrontWindowModal and IsWindowModal routines
									to GetFrontWindowModalClass and GetWindowModalClass.
		 <3>	10/30/90	KSM		<ngk> Add emulateOrigFilterBit equate.
		 <2>	10/29/90	ngk		updated new private calls
		 <1>	 9/19/90	ngk		first checked in
		 <0>	  9/19/90	ngk		created

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT DialogsPriv;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDialogsPriv}
{$SETC UsingDialogsPriv := 1}

{$I+}
{$SETC DialogsPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingDialogs}
{$I Dialogs.p}
{$ENDC}
{$SETC UsingIncludes := DialogsPrivIncludes}


	{ this will be renamed }
	FUNCTION GetFrontWindowModalClass(VAR modalClass: INTEGER): OSErr;
		INLINE $303C, $0201, $AA68;


	{ this will be renamed }
	FUNCTION GetWindowModalClass(theWindow: WindowPtr; VAR modalClass: INTEGER): OSErr;
		INLINE $303C, $0402, $AA68;



{$ENDC}




{ the following is interface to StdFilterProc features }
CONST
	{ bits in spareFlags }
	cannotTwitchOutOfDialogBit		= 7;
	systemHandlesMenusBit			= 6;
	systemHandlesDefaultButtonBit	= 5;
	systemHandlesCancelButtonBit	= 4;
	systemTracksCursorBit			= 3;
	emulateOrigFilterBit			= 2;

	cannotTwitchOutOfDialogMask		= $80;
	systemHandlesMenusMask			= $40;
	systemHandlesDefaultButtonMask	= $20;
	systemHandlesCancelButtonMask	= $10;
	systemTracksCursorMask			= $08;
	emulateOrigFilterMask			= $04;


{ the following is interface to new citation substitution routines <6>}
CONST
	MAXCITATIONS = 10;
TYPE
	CiteList = ARRAY [1..MAXCITATIONS] OF StringPtr;
	CiteListPtr = ^CiteList;

	FUNCTION Cite4(baseString: StringHandle; p0,p1,p2,p3: StringPtr): OSErr;
		INLINE $303C, $0AFB, $AA68;

	FUNCTION CitationsSH(baseString: StringHandle;
					numCitations: INTEGER; citations: CiteListPtr): OSErr;
		INLINE $303C, $07FC, $AA68;

	FUNCTION CitationsCH(baseString: CharsHandle;offset: LONGINT;
					numCitations: INTEGER; citations: CiteListPtr): OSErr;
		INLINE $303C, $05FD, $AA68;


{$IFC NOT UsingIncludes}
	END.
{$ENDC}

