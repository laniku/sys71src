
{
Created: Monday, July 22, 1991 at 7:01 PM
 Icons.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		<22>	 6/11/92	DCL		Changed  INTEGER type  to IconAlignmentType &  IconTransformType
									in PlotIconHandle, PlotSICNHandle, PlotCIconHandle.  ¥ Changed
									inline codes in  IconSuiteToRgn, IconIDToRgn,  ForEachIconDo to
									match the codes in the C header (assuming that the C is
									correct) ¥ Changed the Includes statements.  Minor bug fix. ¥
									Changed all uses of "alignment" in prototypes to "align" for
									consistancy within and between the c & h files.  Happy Happy Joy
									Joy.
		<21>	 3/17/92	DC		Imported all definitions from IconUtilsPriv.p except get and set
									icon device and SetLabel.
		<20>	 7/23/91	JL		Checked in File from database. Changed mini1BitMask from a
									'sicn' to a 'icm#' to match C file.
		<19>	 1/17/91	DC		csd - forgot initials
		<18>	 1/17/91	DC		add genericExtensionIconResource (-16415)
		<17>	 1/16/91	JDR		(dba) Renamed spoolFolderIconResource into
									printMonitorFolderIconResource.
		<16>	  1/7/91	JDR		(dba) Removing private Icon Utilities routines from the public
									interfaces.
		<15>	11/29/90	DC		ngk - Add interface for GetIconDevice.
		<14>	11/19/90	DC		ngk - Moved System Icon ID's from private to public and added
									interfaces for PlotIconHandle PlotSICNHandle and PlotCIconHandle
		<13>	 10/8/90	JAL		Fixed Inclusion lines to conform to MPW standards.
		<12>	 9/19/90	DC		Changed some routine names to be more descriptive
		<11>	 9/15/90	DC		Remove SetLabel from public interfaces
		<11>	 9/15/90	DC		Removed SetLabel from public interface
		<10>	 7/25/90	DC		Added interfaces for Get/Set cache Procs/Data
		 <9>	 7/23/90	DC		Added interfaces for SetOneScreen, etc.
		 <8>	 7/12/90	DC		Removed support for ttGhost
		 <7>	  7/5/90	DC		Added all hit-testing and region-producing interfaces.  Also
									labeling constants and GetLabel and SetLabel interfaces
		 <6>	 6/29/90	DC		Fix lack of semi-colons in label definitions
		 <5>	 6/29/90	DC		Brought up to date with interfaces for civilized languages
									(syntax bugs, indeed!)
		 <4>	  6/6/90	ngk		fix syntax bugs in definitions
		 <3>	 5/31/90	DC		Minor Interface cleanup (still untested)
		 <2>	 5/30/90	DC		Minor fix
		 <1>	 5/30/90	DC		first checked in Icons.p (untested)

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT Icons;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingIcons}
{$SETC UsingIcons := 1}

{$I+}
{$SETC IconsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickDraw}
{$I $$Shell(PInterfaces)QuickDraw.p}
{$ENDC}
{$SETC UsingIncludes := IconsIncludes}



CONST

{ The following are icons for which there are both icon suites and SICNs. }
genericDocumentIconResource = -4000;
genericStationeryIconResource = -3985;
genericEditionFileIconResource = -3989;
genericApplicationIconResource = -3996;
genericDeskAccessoryIconResource = -3991;

genericFolderIconResource = -3999;
privateFolderIconResource = -3994;

floppyIconResource = -3998;
trashIconResource = -3993;

{ The following are icons for which there are SICNs only. }
desktopIconResource = -3992;
openFolderIconResource = -3997;
genericHardDiskIconResource = -3995;
genericFileServerIconResource = -3972;
genericSuitcaseIconResource = -3970;
genericMoverObjectIconResource = -3969;

{ The following are icons for which there are icon suites only. }
genericPreferencesIconResource = -3971;
genericQueryDocumentIconResource = -16506;
genericExtensionIconResource = -16415;

systemFolderIconResource = -3983;
appleMenuFolderIconResource = -3982;
startupFolderIconResource = -3981;
ownedFolderIconResource = -3980;
dropFolderIconResource = -3979;
sharedFolderIconResource = -3978;
mountedFolderIconResource = -3977;
controlPanelFolderIconResource = -3976;
printMonitorFolderIconResource = -3975;
preferencesFolderIconResource = -3974;
extensionsFolderIconResource = -3973;

fullTrashIconResource = -3984;

large1BitMask = 'ICN#';
large4BitData = 'icl4';
large8BitData = 'icl8';
small1BitMask = 'ics#';
small4BitData = 'ics4';
small8BitData = 'ics8';
mini1BitMask = 'icm#';
mini4BitData = 'icm4';
mini8BitData = 'icm8';


	{ IconAlignmentType values	}
atNone				=	$0;
atVerticalCenter	=	$1;
atTop				=	$2;
atBottom			=	$3;
atHorizontalCenter	=	$4;
atAbsoluteCenter	=	(atVerticalCenter + atHorizontalCenter);
atCenterTop			=	(atTop + atHorizontalCenter);
atCenterBottom		=	(atBottom + atHorizontalCenter);
atLeft				=	$8;
atCenterLeft		=	(atVerticalCenter + atLeft);
atTopLeft			=	(atTop + atLeft);
atBottomLeft		=	(atBottom + atLeft);
atRight				=	$C;
atCenterRight		=	(atVerticalCenter + atRight);
atTopRight			=	(atTop + atRight);
atBottomRight		=	(atBottom + atRight);

	{ IconTransformType values }
ttNone				=	$0;
ttDisabled			=	$1;
ttOffline			=	$2;
ttOpen				=	$3;
ttLabel1			=	$0100;
ttLabel2			=	$0200;
ttLabel3			=	$0300;
ttLabel4			=	$0400;
ttLabel5			=	$0500;
ttLabel6			=	$0600;
ttLabel7			=	$0700;
ttSelected			=	$4000;
ttSelectedDisabled	=	(ttSelected + ttDisabled);
ttSelectedOffline	=	(ttSelected + ttOffline);
ttSelectedOpen		=	(ttSelected + ttOpen);
	
	{ IconSelectorValue masks }
svLarge1Bit			=	$00000001;
svLarge4Bit			=	$00000002;
svLarge8Bit			=	$00000004;
svSmall1Bit			=	$00000100;
svSmall4Bit			=	$00000200;
svSmall8Bit			=	$00000400;
svMini1Bit			=	$00010000;
svMini4Bit			=	$00020000;
svMini8Bit			=	$00040000;
svAllLargeData		=	$000000ff;
svAllSmallData		=	$0000ff00;
svAllMiniData		=	$00ff0000;
svAll1BitData		=	(svLarge1Bit + svSmall1Bit + svMini1Bit);
svAll4BitData		=	(svLarge4Bit + svSmall4Bit + svMini4Bit);
svAll8BitData		=	(svLarge8Bit + svSmall8Bit + svMini8Bit);
svAllAvailableData	=	$ffffffff;
	
TYPE
	IconSelectorValue	=	LONGINT;
	IconAlignmentType	=	INTEGER;
	IconTransformType	=	INTEGER;

	IconAction			=	ProcPtr;	{
											FUNCTION IconAction(theType: ResType;
														VAR theIcon: Handle;
														yourDataPtr: Ptr): OSErr;
										}
										
	IconGetter			=	ProcPtr;	{
											FUNCTION IconGetter(theType: ResType;
														yourDataPtr: Ptr): Handle;
										}


	FUNCTION PlotIconID(theRect: Rect;
						align: IconAlignmentType;
						transform: IconTransformType;
						theResID: INTEGER): OSErr;
		INLINE	$303C, $0500, $ABC9;
	
	FUNCTION NewIconSuite(VAR theIconSuite: Handle): OSErr;
		INLINE	$303C, $0207, $ABC9;
	
	FUNCTION AddIconToSuite(theIconData: Handle;
							theSuite: Handle;
							theType: ResType): OSErr;
		INLINE	$303C, $0608, $ABC9;
	
	FUNCTION GetIconFromSuite(VAR theIconData: Handle;
							theSuite: Handle;
							theType: ResType): OSErr;
		INLINE	$303C, $0609, $ABC9;
	
	FUNCTION ForEachIconDo(theSuite: Handle;
							selector: IconSelectorValue;
							action: IconAction;
							yourDataPtr: Ptr): OSErr;
		INLINE	$303C, $080A, $ABC9;
	
	FUNCTION GetIconSuite(VAR theIconSuite: Handle;
							theResID: INTEGER;
							selector: IconSelectorValue): OSErr;
		INLINE	$303C, $0501, $ABC9;
	
	FUNCTION DisposeIconSuite(theIconSuite: Handle;
							disposeData: BOOLEAN): OSErr;
		INLINE	$303C, $0302, $ABC9;
	
	FUNCTION PlotIconSuite(theRect: Rect;
							align: IconAlignmentType;
							transform: IconTransformType;
							theIconSuite: Handle): OSErr;
		INLINE	$303C, $0603, $ABC9;
	
	FUNCTION MakeIconCache(VAR theHandle: Handle;
							makeIcon: IconGetter;
							yourDataPtr: UNIV Ptr): OSErr;
		INLINE	$303C, $0604, $ABC9;
	
	FUNCTION LoadIconCache(theRect: Rect;
							align: IconAlignmentType;
							transform: IconTransformType;
							theIconCache: Handle): OSErr;
		INLINE	$303C, $0606, $ABC9;

	FUNCTION PlotIconMethod(theRect: Rect;
							align: IconAlignmentType;
							transform: IconTransformType;
							theMethod: IconGetter;
							yourDataPtr: UNIV Ptr): OSErr;
		INLINE $303C, $0805, $ABC9;
	
	FUNCTION GetLabel(labelNumber: INTEGER; VAR labelColor: RGBColor;
							VAR labelString: Str255): OSErr;
		INLINE $303C, $050B, $ABC9;
	
	FUNCTION PtInIconID(testPt: Point; iconRect: Rect;
					align: IconAlignmentType; iconID: INTEGER): BOOLEAN;
		INLINE $303C, $060D, $ABC9;

	FUNCTION PtInIconSuite(testPt: Point; iconRect: Rect;
					align: IconAlignmentType;
					theIconSuite: Handle): BOOLEAN;
		INLINE $303C, $070E, $ABC9;

	FUNCTION PtInIconMethod(testPt: Point; iconRect: Rect;
					align: IconAlignmentType;
					theMethod: IconGetter; yourDataPtr: Ptr): BOOLEAN;
		INLINE $303C, $090F, $ABC9;

	FUNCTION RectInIconID(testRect: Rect; iconRect: Rect;
					align: IconAlignmentType; iconID: INTEGER): BOOLEAN;
		INLINE $303C, $0610, $ABC9;

	FUNCTION RectInIconSuite(testRect: Rect; iconRect: Rect;
					align: IconAlignmentType;
					theIconSuite: Handle): BOOLEAN;
		INLINE $303C, $0711, $ABC9;

	FUNCTION RectInIconMethod(testRect: Rect; iconRect: Rect;
					align: IconAlignmentType;
					theMethod: IconGetter; yourDataPtr: Ptr): BOOLEAN;
		INLINE $303C, $0912, $ABC9;

	FUNCTION IconIDToRgn(theRgn: RgnHandle; iconRect: Rect;
					align: IconAlignmentType; iconID: INTEGER): OSErr;
		INLINE $303C, $0613, $ABC9;

	FUNCTION IconSuiteToRgn(theRgn: RgnHandle; iconRect: Rect;
					align: IconAlignmentType;
					theIconSuite: Handle): OSErr;
		INLINE $303C, $0714, $ABC9;

	FUNCTION IconMethodToRgn(theRgn: RgnHandle; iconRect: Rect;
					align: IconAlignmentType;
					theMethod: IconGetter; yourDataPtr: Ptr): OSErr;
		INLINE $303C, $0915, $ABC9;

	FUNCTION SetSuiteLabel(theSuite: Handle; theLabel: INTEGER): OSErr;
		INLINE $303C, $0316, $ABC9;

	FUNCTION GetSuiteLabel(theSuite: Handle): INTEGER;
		INLINE $303C, $0217, $ABC9;

	FUNCTION GetIconCacheData(theCache: Handle; VAR theData: Ptr): OSErr;
		INLINE $303C, $0419, $ABC9;
		
	FUNCTION SetIconCacheData(theCache: Handle; theData: Ptr): OSErr;
		INLINE $303C, $041A, $ABC9;
		
	FUNCTION GetIconCacheProc(theCache: Handle; VAR theProc: IconGetter): OSErr;
		INLINE $303C, $041B, $ABC9;
		
	FUNCTION SetIconCacheProc(theCache: Handle; theProc: IconGetter): OSErr;
		INLINE $303C, $041C, $ABC9;

	FUNCTION PlotIconHandle(theRect: Rect; align: IconAlignmentType;
					transform: IconTransformType; theIcon: Handle): OSErr;
		INLINE $303C, $061D, $ABC9;

	FUNCTION PlotSICNHandle(theRect: Rect; align: IconAlignmentType;
					transform: IconTransformType; theSICN: Handle): OSErr;
		INLINE $303C, $061E, $ABC9;

	FUNCTION PlotCIconHandle(theRect: Rect; align: IconAlignmentType;
					transform: IconTransformType; theCIcon: CIconHandle): OSErr;
		INLINE $303C, $061F, $ABC9;

{$ENDC} { UsingIcons }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

