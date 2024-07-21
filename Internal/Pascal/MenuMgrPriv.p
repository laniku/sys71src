{
	File:		MenuMgrPriv.p

	Contains:	The MenuMgrPriv unit is a unit shell.

	Written by:	Kevin S. MacDonell

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <5>	 6/14/91	JL		Moved SavedBits here from the Public Interface File: Menus.p.
		 <4>	 1/28/91	JAL		(LN) Adding SaveBits,RestoreBits, and DiscardBits from Menus.p
		 <3>	 1/21/91	DFH		(KSM) Adding System Menu constants from MenuMgrPriv.a.
		 <2>	  6/8/90	KSM		Add IsSystemMenu call.
		 <1>	 5/14/90	KSM		New today.
		 <0>	 3/16/90	KSM		New Today.

	To Do:
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT MenuMgrPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMenuMgrPriv}
{$SETC UsingMenuMgrPriv := 1}

{$I+}
{$SETC MenuMgrPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingMemory}
{$I Types.p}
{$I Menus.p}
{$ENDC}
{$SETC UsingIncludes := MenuMgrPrivIncludes}

{ System Menu IDs as we know them }
CONST
	kLoSystemMenuRange			=	$B000;		{ This is -20480 (the lowest value) }
	kHiSystemMenuRange			=	$BFFF;		{ This is -16385 (the highest value) }

	kApplicationMenuID			=	$BF97;		{ -16489: The application menu ID }
	kHelpMenuID					=	$BF96;		{ -16490: The help menu ID }
	kScriptMenuID				=	$BF95;		{ -16491: The keyboard menu ID }

TYPE
SavedBits = LONGINT;                    { For Save/Restore/Discard Bits calls }


{ The MenuDispatch calls }

	FUNCTION GetMenuTitleRect(menuID: INTEGER; VAR theRect: Rect): OSErr;
		INLINE $303C, $04FF, $A825;

	FUNCTION GetMBARRect(VAR theRect: Rect): OSErr;
		INLINE $303C, $04FE, $A825;

	FUNCTION GetAppMenusRect(VAR theRect: Rect): OSErr;
		INLINE $303C, $04FD, $A825;

	FUNCTION GetSysMenusRect(VAR theRect: Rect): OSErr;
		INLINE $303C, $04FC, $A825;

	FUNCTION DrawMBARString(bannerMsg: StringPtr; scriptID: INTEGER; teJust: INTEGER): OSErr;
		INLINE $303C, $08FB, $A825;

	FUNCTION IsSystemMenu(menuID: INTEGER; VAR isSys: BOOLEAN): OSErr;
		INLINE $303C, $03FA, $A825;

FUNCTION SaveBits(saveRect: Rect; purgeable: BOOLEAN; VAR bits: SavedBits): OSErr;
	INLINE $303C, $0501, $A81E;
FUNCTION RestoreBits(bits: SavedBits): OSErr;
	INLINE $303C, $0202, $A81E;
FUNCTION DiscardBits(bits: SavedBits): OSErr;
	INLINE $303C, $0203, $A81E;



 {$ENDC}    { UsingMenuMgrPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

