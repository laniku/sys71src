{
	File:		IconUtilsPriv.p

	Contains:	Private Pascal Interface for color icon plotting utilities

	Written by:	Nick Kledzik

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<13>	 3/20/92	DC		Added UpdateIconGlobals to private interfaces
		<12>	 3/19/92	DC		Changed the printerPortCache field in the GlobalIconData
									structure so that the structure would not change (and Radius
									products will not break)
		<11>	 3/17/92	DC		Exported all definitions to Icons.p except get and set icon
									device, SetLabel and internal data structures.
		<10>	10/29/91	DC		Conditionalized last change to protect CubeE
		 <9>	 8/30/91	DC		Added printerPortCache to the globals to allow improved printing
									case check.
		 <8>	 8/28/91	JSM		Cleanup header.
		 <7>	  1/8/91	JDR		(dba) Removing private Icon Utilities routines.
		 <6>	11/19/90	DC		ngk - Moved System Icon ID's from private to public
		 <5>	 9/15/90	DC		changed setlabel to live here
		 <4>	  9/6/90	DC		Fixed the definition of icon global structure for selected cluts
		 <3>	 7/25/90	DC		Added ExpandMem structure for parallelism with IconUtilsPriv.h
		 <2>	 7/23/90	DC		brought up to date with IconUtilsPriv.p
		 <1>	  6/6/90	ngk		first checked in
		<0+>	  6/6/90	ngk		Added generic icon ID definitions
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT IconUtilsPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingIconUtilsPriv}
{$SETC UsingIconUtilsPriv := 1}

{$I+}
{$SETC IconUtilsPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingIcons}
	{$I Icons.p}
{$ENDC}
{$SETC UsingIncludes := IconUtilsPrivIncludes}


CONST

	genericIconBase						= -4000;	
	popupMenuSymbolResource				= -3990;
	standalonePopupMenuSymbolResource	= -3986;

	genericMailboxIconResource			= -3987; 	{excise from 7.0}
	genericLetterIconResource			= -3988;	{excise from 7.0}
	
	{ IconType's }
	largeIcon1 	= 0;
	largeIcon4 	= 1;
	largeIcon8 	= 2;
	smallIcon1 	= 3;
	smallIcon4 	= 4;
	smallIcon8 	= 5;
	miniIcon1 	= 6;
	miniIcon4 	= 7;
	miniIcon8 	= 8;
	aCIcon		= 128;
	
	IconSpace		= miniIcon8 + 1;
	IconDepthSpace	= smallIcon1 - largeIcon1;
	IconSizeSpace	= IconSpace DIV IconDepthSpace;

	transformMask 	=	$03;
	labelShift		=	$08;
	labelMask		=	$0F00;
	Labels			=	8;
	Sets			=	8;
	
TYPE
	IconType	= INTEGER;
	
	IconSuiteHandle = ^IconSuitePtr;
	IconSuitePtr 	= ^IconSuite;
	IconSuite		= RECORD
						isTag:		INTEGER;	{ 0=>suite, 1=>cache }
						isLabel:	INTEGER;
						table:		ARRAY [0..IconSpace-1] OF Handle;
					END;

	IconCacheHandle = ^IconCachePtr;
	IconCachePtr 	= ^IconCache;
	IconCache		= RECORD
						theSuite:	IconSuite;
						userPtr:	Ptr;
						userMethod:	IconGetter;
					END;
					
	DeviceCheck		= RECORD
						theDevice:				GDHandle;
						theSeed:				LONGINT;
						checkMask:				LONGINT;
						checkResults:			LONGINT;
						disabledCheckMask:		LONGINT;
						disabledCheckResults:	LONGINT;
					END;
					
	Strings			= ARRAY[0..Labels-1] OF Handle;
	
	GlobalIconDataHandle	= ^GlobalIconDataPtr;
	GlobalIconDataPtr		= ^GlobalIconData;
	GlobalIconData	= RECORD
						labelStrings:		Strings;
						seeds:				ARRAY [0..((Labels*Sets)-1)] OF LONGINT;
						colorTables:		ARRAY [0..((Labels*Sets)-1)] OF CTabHandle;
						originals:			ARRAY [0..1] OF CTabHandle;
						labelColors:		ARRAY [0..Labels-1] OF RGBColor;
						indexLists:			ARRAY [0..1] OF Handle;
						virtualScreen:		GDHandle;
						deviceListSize:		LONGINT;
						deviceCheckList:	ARRAY[0..0] OF DeviceCheck;
					END;
					

	PROCEDURE SetIconDevice(theScreen: GDHandle);
		INLINE $303C, $0218, $ABC9;
		
	PROCEDURE GetIconDevice(VAR theScreen: GDHandle);
		INLINE $303C, $0220, $ABC9;
		

	FUNCTION SetLabel(labelNumber: INTEGER; labelColor: RGBColor;
						labelString: Str255): OSErr;
		INLINE $303C, $050C, $ABC9;
	
{$IFC TheFuture}
	FUNCTION UpdateIconGlobals: OSErr;
		INLINE $303C, $0021, $ABC9;
{$ENDC}

{$ENDC}    { UsingIconUtilsPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}
