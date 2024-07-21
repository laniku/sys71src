
{
Created: Saturday, July 27, 1991 at 8:04 PM
 Balloons.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: BigBang

	Change History (most recent first):

		<20>	 7/30/91	JL		Updated Copyright. Restored Comments. <19> 1/28/91 LN Checked in
									Database Generated File from DSG.
		<18>	 1/24/91	stb		RC: remove HMFillCitationString; change all pic’s to pict’s
		<17>	12/14/90	dba		<JDR> get rid of RectPtr which is now in Types.p
		<16>	 9/24/90	RLC		Fix the interface to HMGetIndHelpMsg to pass $1306 as the
									selector (not $1106) as there are 19 words of parameters (not 17
									as originally counted). This will result in a crash if this call
									is made as procHelper won't copy enuf parameters to & from the
									stack!
		<15>	 9/14/90	RLC		Fix the messed up file that projector corrupted (again).
		<14>	 8/31/90	RLC		Remove extraneous and incorrect equates (all new for b2).
		<13>	 8/22/90	RLC		Remove some extraneous constants.
	   <11+>	 8/17/90	RLC		Add some new constants to support the new interfaces.
	   <10+>	 7/24/90	RLC		Update HMShowBalloon(), remove HMMouseInApplRgn(), add
									HMGetIndHelpMsg().
		<9+>	 6/12/90	RLC		Change Help menu id's and icons to -16490.
		 <9>	 5/31/90	RLC		Change HMState to HMGetHelpMenuHandle function.
		 <8>	 4/24/90	RLC		Add HMGetDialogResID & HMGetMenuResID.
		<6+>	 4/17/90	RLC		Add reference to HMFillCitationString routine.
		 <6>	 4/11/90	KSM		New equates for system menu patch.
		<4+>	  4/5/90	RLC		Add new HMExtractHelpMsg interface.
		 <4>	  4/4/90	KSM		Now $USES Traps.p and the pre-defined constant _Pack14 instead
									of $A830 or ourPackNum.
		 <3>	  4/3/90	ngk		Converted to auto-including interface file
		 <2>	 3/20/90	RLC		Rip some extraneous CONSTs.
		 <1>	 3/20/90	RLC		first checked in

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Balloons;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingBalloons}
{$SETC UsingBalloons := 1}

{$I+}
{$SETC BalloonsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingMenus}
{$I $$Shell(PInterfaces)Menus.p}
{$ENDC}
{$IFC UNDEFINED UsingTextEdit}
{$I $$Shell(PInterfaces)TextEdit.p}
{$ENDC}
{$IFC UNDEFINED UsingTraps}
{$I $$Shell(PInterfaces)Traps.p}
{$ENDC}
{$SETC UsingIncludes := BalloonsIncludes}

CONST
hmBalloonHelpVersion = $0002;	{ The real version of the Help Manager }

{Help Mgr error range: -850 to -874}
hmHelpDisabled = -850;			{ Show Balloons mode was off, call to routine ignored }
hmBalloonAborted = -853;		{ Returned if mouse was moving or mouse wasn't in window port rect }
hmSameAsLastBalloon = -854;		{ Returned from HMShowMenuBalloon if menu & item is same as last time }
hmHelpManagerNotInited = -855;	{ Returned from HMGetHelpMenuHandle if help menu not setup }
hmSkippedBalloon = -857;		{ Returned from calls if helpmsg specified a skip balloon }
hmWrongVersion = -858;			{ Returned if help mgr resource was the wrong version }
hmUnknownHelpType = -859;		{ Returned if help msg record contained a bad type }
hmOperationUnsupported = -861;	{ Returned from HMShowBalloon call if bad method passed to routine }
hmNoBalloonUp = -862;			{ Returned from HMRemoveBalloon if no balloon was visible when call was made }
hmCloseViewActive = -863;		{ Returned from HMRemoveBalloon if CloseView was active }

kHMHelpMenuID = -16490;			{ Resource ID and menu ID of help menu }
kHMAboutHelpItem = 1;			{ help menu item number of About Balloon Help… }
kHMShowBalloonsItem = 3;		{ help menu item number of Show/Hide Balloons }

kHMHelpID = -5696;				{ ID of various Help Mgr package resources (in Pack14 range) }
kBalloonWDEFID = 126;			{ Resource ID of the WDEF proc used in standard balloons }

{ Dialog item template type constant }
helpItem = 1;					{ key value in DITL template that corresponds to the help item }

{ Options for Help Manager resources in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources }
hmDefaultOptions = 0;			{ default options for help manager resources }
hmUseSubID = 1;					{ treat resID's in resources as subID's of driver base ID (for Desk Accessories) }
hmAbsoluteCoords = 2;			{ ignore window port origin and treat rectangles as absolute coords (local to window) }
hmSaveBitsNoWindow = 4;			{ don't create a window, just blast bits on screen. No update event is generated }
hmSaveBitsWindow = 8;			{ create a window, but restore bits behind window when window goes away & generate update event }
hmMatchInTitle = 16;			{ for hwin resources, match string anywhere in window title string }

{ Constants for Help Types in 'hmnu', 'hdlg', 'hrct', 'hovr', & 'hfdr' resources }
kHMStringItem = 1;				{ pstring used in resource }
kHMPictItem = 2;				{ 'PICT' ResID used in resource }
kHMStringResItem = 3;			{ 'STR#' ResID & index used in resource }
kHMTEResItem = 6;				{ Styled Text Edit ResID used in resource ('TEXT' & 'styl') }
kHMSTRResItem = 7;				{ 'STR ' ResID used in resource }
kHMSkipItem = 256;				{ don't display a balloon }
kHMCompareItem = 512;			{ Compare pstring in menu item w/ PString in resource item ('hmnu' only) }
kHMNamedResourceItem = 1024;	{ Use pstring in menu item to get 'STR#', 'PICT', or 'STR ' resource ('hmnu' only) }
kHMTrackCntlItem = 2048;		{ Reserved }

{ Constants for hmmHelpType's when filling out HMMessageRecord }
khmmString = 1;					{ help message contains a PString }
khmmPict = 2;					{ help message contains a resource ID to a 'PICT' resource }
khmmStringRes = 3;				{ help message contains a res ID & index to a 'STR#' resource }
khmmTEHandle = 4;				{ help message contains a Text Edit handle }
khmmPictHandle = 5;				{ help message contains a Picture handle }
khmmTERes = 6;					{ help message contains a res ID to 'TEXT' & 'styl' resources }
khmmSTRRes = 7;					{ help message contains a res ID to a 'STR ' resource }

{ ResTypes for Styled TE Handles in Resources }
kHMTETextResType = 'TEXT';		{ Resource Type of text data for styled TE record w/o style info }
kHMTEStyleResType = 'styl';		{ Resource Type of style information for styled TE record }

{ Generic defines for the state parameter used when extracting 'hmnu' & 'hdlg' messages }
kHMEnabledItem = 0;				{ item is enabled, but not checked or control value = 0 }
kHMDisabledItem = 1;			{ item is disabled, grayed in menus or disabled in dialogs }
kHMCheckedItem = 2;				{ item is enabled, and checked or control value = 1 }
kHMOtherItem = 3;				{ item is enabled, and control value > 1 }

{ Resource Types for whichType parameter used when extracting 'hmnu' & 'hdlg' messages }
kHMMenuResType = 'hmnu';		{ ResType of help resource for supporting menus }
kHMDialogResType = 'hdlg';		{ ResType of help resource for supporting dialogs }
kHMWindListResType = 'hwin';	{ ResType of help resource for supporting windows }
kHMRectListResType = 'hrct';	{ ResType of help resource for rectangles in windows }
kHMOverrideResType = 'hovr';	{ ResType of help resource for overriding system balloons }
kHMFinderApplResType = 'hfdr';	{ ResType of help resource for custom balloon in Finder }

{ Method parameters to pass to HMShowBalloon }
kHMRegularWindow = 0;			{ Create a regular window floating above all windows }
kHMSaveBitsNoWindow = 1;		{ Just save the bits and draw (for MDEF calls) }
kHMSaveBitsWindow = 2;			{ Regular window, save bits behind, AND generate update event }

TYPE
HMStringResType = RECORD
 hmmResID: INTEGER;
 hmmIndex: INTEGER;
 END;

HMMessageRecPtr    = ^HMMessageRecord;
HMMessageRecord    = RECORD
                hmmHelpType            : INTEGER;
                CASE INTEGER OF
                khmmString:
                    (hmmString: STR255);
                khmmPict:
                    (hmmPict: INTEGER);
                khmmStringRes:
                    (hmmStringRes: HMStringResType);
                khmmTEHandle:
                    (hmmTEHandle: TEHandle);
                khmmPictHandle:
                    (hmmPictHandle: PicHandle);
                khmmTERes:
                    (hmmTERes: INTEGER);
                khmmSTRRes:
                    (hmmSTRRes: INTEGER);
                END;



{  Public Interfaces  }
FUNCTION HMGetHelpMenuHandle(VAR mh: MenuHandle): OSErr;
 INLINE $303C,$0200,_Pack14;
FUNCTION HMShowBalloon(aHelpMsg: HMMessageRecord;
                       tip: Point;
                       alternateRect: RectPtr;
                       tipProc: Ptr;
                       theProc: INTEGER;
                       variant: INTEGER;
                       method: INTEGER): OSErr;
 INLINE $303C,$0B01,_Pack14;
FUNCTION HMRemoveBalloon: OSErr;
 INLINE $303C,$0002,_Pack14;
FUNCTION HMGetBalloons: BOOLEAN;
 INLINE $303C,$0003,_Pack14;
FUNCTION HMSetBalloons(flag: BOOLEAN): OSErr;
 INLINE $303C,$0104,_Pack14;
FUNCTION HMShowMenuBalloon(itemNum: INTEGER;
                           itemMenuID: INTEGER;
                           itemFlags: LONGINT;
                           itemReserved: LONGINT;
                           tip: Point;
                           alternateRect: RectPtr;
                           tipProc: Ptr;
                           theProc: INTEGER;
                           variant: INTEGER): OSErr;
 INLINE $303C,$0E05,_Pack14;
FUNCTION HMGetIndHelpMsg(whichType: ResType;
                         whichResID: INTEGER;
                         whichMsg: INTEGER;
                         whichState: INTEGER;
                         VAR options: LONGINT;
                         VAR tip: Point;
                         VAR altRect: Rect;
                         VAR theProc: INTEGER;
                         VAR variant: INTEGER;
                         VAR aHelpMsg: HMMessageRecord;
                         VAR count: INTEGER): OSErr;
 INLINE $303C,$1306,_Pack14;
FUNCTION HMIsBalloon: BOOLEAN;
 INLINE $303C,$0007,_Pack14;
FUNCTION HMSetFont(font: INTEGER): OSErr;
 INLINE $303C,$0108,_Pack14;
FUNCTION HMSetFontSize(fontSize: INTEGER): OSErr;
 INLINE $303C,$0109,_Pack14;
FUNCTION HMGetFont(VAR font: INTEGER): OSErr;
 INLINE $303C,$020A,_Pack14;
FUNCTION HMGetFontSize(VAR fontSize: INTEGER): OSErr;
 INLINE $303C,$020B,_Pack14;
FUNCTION HMSetDialogResID(resID: INTEGER): OSErr;
 INLINE $303C,$010C,_Pack14;
FUNCTION HMSetMenuResID(menuID: INTEGER;
                        resID: INTEGER): OSErr;
 INLINE $303C,$020D,_Pack14;
FUNCTION HMBalloonRect(aHelpMsg: HMMessageRecord;
                       VAR coolRect: Rect): OSErr;
 INLINE $303C,$040E,_Pack14;
FUNCTION HMBalloonPict(aHelpMsg: HMMessageRecord;
                       VAR coolPict: PicHandle): OSErr;
 INLINE $303C,$040F,_Pack14;
FUNCTION HMScanTemplateItems(whichID: INTEGER;
                             whichResFile: INTEGER;
                             whichType: ResType): OSErr;
 INLINE $303C,$0410,_Pack14;
FUNCTION HMExtractHelpMsg(whichType: ResType;whichResID: INTEGER;whichMsg: INTEGER;
 whichState: INTEGER;VAR aHelpMsg: HMMessageRecord): OSErr;
 INLINE $303C,$0711,_Pack14;
FUNCTION HMGetDialogResID(VAR resID: INTEGER): OSErr;
 INLINE $303C,$0213,_Pack14;
FUNCTION HMGetMenuResID(menuID: INTEGER;VAR resID: INTEGER): OSErr;
 INLINE $303C,$0314,_Pack14;
FUNCTION HMGetBalloonWindow(VAR window: WindowPtr): OSErr;
 INLINE $303C,$0215,_Pack14;


{$ENDC} { UsingBalloons }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

