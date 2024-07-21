
{
Created: Saturday, July 27, 1991 at 10:24 PM
 Palettes.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1987-1991
  All rights reserved
    This file is used in these builds: BigBang

	Change History (most recent first):

		<11>	  8/8/91	JL		Fixed GetGray call. Wrong selector; someone translated 12
									decimal to 12 hex.
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	 1/30/91	JL		checked in database generated file from dsg.
		 <8>	 1/18/91	KON		Change SaveFore, SaveBack, RestoreFore, RestoreBack to coincide
									with IM interfaces. [CEL]
		 <7>	  1/9/91	dvb		Change return type of HasDepth to INTEGER.
		 <6>	12/13/90	dvb		Make .h and .p and .a files consistent.
		 <5>	 11/5/90	JL		Returned pmInhibit equates.
		 <4>	 9/15/90	DC		added GetGray and CheckColors
		 <3>	 6/19/90	DVB		Add in the latest PMgr dispatchs

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Palettes;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPalettes}
{$SETC UsingPalettes := 1}

{$I+}
{$SETC PalettesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingWindows}
{$I $$Shell(PInterfaces)Windows.p}
{$ENDC}
{$SETC UsingIncludes := PalettesIncludes}

CONST
pmCourteous = 0;							{Record use of color on each device touched.}
pmTolerant = $0002;							{render ciRGB if ciTolerance is exceeded by best match.}
pmAnimated = $0004;							{reserve an index on each device touched and render ciRGB.}
pmExplicit = $0008;							{no reserve, no render, no record; stuff index into port.}

pmWhite = $0010;
pmBlack = $0020;

pmInhibitG2 = $0100;
pmInhibitC2 = $0200;
pmInhibitG4 = $0400;
pmInhibitC4 = $0800;
pmInhibitG8 = $1000;
pmInhibitC8 = $2000;


{ NSetPalette Update Constants }
pmNoUpdates = $8000;						{no updates}
pmBkUpdates = $A000;						{background updates only}
pmFgUpdates = $C000;						{foreground updates only}
pmAllUpdates = $E000;						{all updates}

TYPE
ColorInfo = RECORD
 ciRGB: RGBColor;							{true RGB values}
 ciUsage: INTEGER;							{color usage}
 ciTolerance: INTEGER;						{tolerance value}
 ciDataFields: ARRAY [0..2] OF INTEGER;		{private fields}
 END;

PalettePtr = ^Palette;
PaletteHandle = ^PalettePtr;
Palette = RECORD
 pmEntries: INTEGER;						{entries in pmTable}
 pmDataFields: ARRAY [0..6] OF INTEGER;		{private fields}
 pmInfo: ARRAY [0..0] OF ColorInfo;
 END;


PROCEDURE InitPalettes;
 INLINE $AA90;
FUNCTION NewPalette(entries: INTEGER;srcColors: CTabHandle;srcUsage: INTEGER;
 srcTolerance: INTEGER): PaletteHandle;
 INLINE $AA91;
FUNCTION GetNewPalette(PaletteID: INTEGER): PaletteHandle;
 INLINE $AA92;
PROCEDURE DisposePalette(srcPalette: PaletteHandle);
 INLINE $AA93;
PROCEDURE ActivatePalette(srcWindow: WindowPtr);
 INLINE $AA94;
PROCEDURE SetPalette(dstWindow: WindowPtr;srcPalette: PaletteHandle;cUpdates: BOOLEAN);
 INLINE $AA95;
PROCEDURE NSetPalette(dstWindow: WindowPtr;srcPalette: PaletteHandle;nCUpdates: INTEGER);
 INLINE $AA95;
FUNCTION GetPalette(srcWindow: WindowPtr): PaletteHandle;
 INLINE $AA96;
PROCEDURE CopyPalette(srcPalette: PaletteHandle;dstPalette: PaletteHandle;
 srcEntry: INTEGER;dstEntry: INTEGER;dstLength: INTEGER);
 INLINE $AAA1;
PROCEDURE PmForeColor(dstEntry: INTEGER);
 INLINE $AA97;
PROCEDURE PmBackColor(dstEntry: INTEGER);
 INLINE $AA98;
PROCEDURE AnimateEntry(dstWindow: WindowPtr;dstEntry: INTEGER;srcRGB: RGBColor);
 INLINE $AA99;
PROCEDURE AnimatePalette(dstWindow: WindowPtr;srcCTab: CTabHandle;srcIndex: INTEGER;
 dstEntry: INTEGER;dstLength: INTEGER);
 INLINE $AA9A;
PROCEDURE GetEntryColor(srcPalette: PaletteHandle;srcEntry: INTEGER;VAR dstRGB: RGBColor);
 INLINE $AA9B;
PROCEDURE SetEntryColor(dstPalette: PaletteHandle;dstEntry: INTEGER;srcRGB: RGBColor);
 INLINE $AA9C;
PROCEDURE GetEntryUsage(srcPalette: PaletteHandle;srcEntry: INTEGER;VAR dstUsage: INTEGER;
 VAR dstTolerance: INTEGER);
 INLINE $AA9D;
PROCEDURE SetEntryUsage(dstPalette: PaletteHandle;dstEntry: INTEGER;srcUsage: INTEGER;
 srcTolerance: INTEGER);
 INLINE $AA9E;
PROCEDURE CTab2Palette(srcCTab: CTabHandle;dstPalette: PaletteHandle;srcUsage: INTEGER;
 srcTolerance: INTEGER);
 INLINE $AA9F;
PROCEDURE Palette2CTab(srcPalette: PaletteHandle;dstCTab: CTabHandle);
 INLINE $AAA0;
FUNCTION Entry2Index(entry: INTEGER): LONGINT;
 INLINE $7000,$AAA2;
PROCEDURE RestoreDeviceClut(gd: GDHandle);
 INLINE $7002,$AAA2;
PROCEDURE ResizePalette(p: PaletteHandle;size: INTEGER);
 INLINE $7003,$AAA2;
PROCEDURE SaveFore(VAR c: ColorSpec);
 INLINE $303C,$040D,$AAA2;
PROCEDURE SaveBack(VAR c: ColorSpec);
 INLINE $303C,$040E,$AAA2;
PROCEDURE RestoreFore(c: ColorSpec);
 INLINE $303C,$040F,$AAA2;
PROCEDURE RestoreBack(c: ColorSpec);
 INLINE $303C,$0410,$AAA2;
FUNCTION SetDepth(gd: GDHandle;depth: INTEGER;whichFlags: INTEGER;flags: INTEGER): OSErr;
 INLINE $303C,$0A13,$AAA2;
FUNCTION HasDepth(gd: GDHandle;depth: INTEGER;whichFlags: INTEGER;flags: INTEGER): INTEGER;
 INLINE $303C,$0A14,$AAA2;
FUNCTION PMgrVersion: INTEGER;
 INLINE $7015,$AAA2;
PROCEDURE SetPaletteUpdates(p: PaletteHandle;updates: INTEGER);
 INLINE $303C,$0616,$AAA2;
FUNCTION GetPaletteUpdates(p: PaletteHandle): INTEGER;
 INLINE $303C,$0417,$AAA2;
FUNCTION GetGray(device: GDHandle;backGround: RGBColor;VAR foreGround: RGBColor): BOOLEAN;
 INLINE $303C,$0C19,$AAA2;


{$ENDC} { UsingPalettes }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

