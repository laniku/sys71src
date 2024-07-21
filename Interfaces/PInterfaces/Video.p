
{
Created: Sunday, July 28, 1991 at 12:23 AM
 Video.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <4>	 7/31/91	JL		Updated Copyright.
		 <3>	 1/27/91	LN		Checked in Database generate file from DSG. Added cscGrayScreen
									to match .h file.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Video;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingVideo}
{$SETC UsingVideo := 1}

{$I+}
{$SETC VideoIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := VideoIncludes}

CONST
mBaseOffset = 1;			{Id of mBaseOffset.}
mRowBytes = 2;				{Video sResource parameter Id's }
mBounds = 3;				{Video sResource parameter Id's }
mVersion = 4;				{Video sResource parameter Id's }
mHRes = 5;					{Video sResource parameter Id's }
mVRes = 6;					{Video sResource parameter Id's }
mPixelType = 7;				{Video sResource parameter Id's }
mPixelSize = 8;				{Video sResource parameter Id's }
mCmpCount = 9;				{Video sResource parameter Id's }
mCmpSize = 10;				{Video sResource parameter Id's }
mPlaneBytes = 11;			{Video sResource parameter Id's }
mVertRefRate = 14;			{Video sResource parameter Id's }
mVidParams = 1;				{Video parameter block id.}
mTable = 2;					{Offset to the table.}
mPageCnt = 3;				{Number of pages}
mDevType = 4;				{Device Type}

oneBitMode = 128;			{Id of OneBitMode Parameter list.}
twoBitMode = 129;			{Id of TwoBitMode Parameter list.}
fourBitMode = 130;			{Id of FourBitMode Parameter list.}
eightBitMode = 131;			{Id of EightBitMode Parameter list.}
sixteenBitMode = 132;		{Id of SixteenBitMode Parameter list.}
thirtyTwoBitMode = 133;		{Id of ThirtyTwoBitMode Parameter list.}

firstVidMode = 128;			{The new, better way to do the above. }
secondVidMode = 129;		{ QuickDraw only supports six video }
thirdVidMode = 130;			{ at this time.      }
fourthVidMode = 131;
fifthVidMode = 132;
sixthVidMode = 133;

spGammaDir = 64;
spVidNamesDir = 65;

{ Control Codes }
cscReset = 0;
cscKillIO = 1;
cscSetMode = 2;
cscSetEntries = 3;
cscSetGamma = 4;
cscGrayPage = 5;
cscGrayScreen = 5;
cscSetGray = 6;
cscSetInterrupt = 7;
cscDirectSetEntries = 8;
cscSetDefaultMode = 9;

{ Status Codes }
cscGetMode = 2;
cscGetEntries = 3;
cscGetPageCnt = 4;
cscGetPages = 4;			{ This is what C&D 2 calls it. }
cscGetPageBase = 5;
cscGetBaseAddr = 5;			{ This is what C&D 2 calls it. }
cscGetGray = 6;
cscGetInterrupt = 7;
cscGetGamma = 8;
cscGetDefaultMode = 9;

TYPE
VPBlockPtr = ^VPBlock;
VPBlock = RECORD
 vpBaseOffset: LONGINT;		{Offset to page zero of video RAM (From minorBaseOS).}
 vpRowBytes: INTEGER;		{Width of each row of video memory.}
 vpBounds: Rect;			{BoundsRect for the video display (gives dimensions).}
 vpVersion: INTEGER;		{PixelMap version number.}
 vpPackType: INTEGER;
 vpPackSize: LONGINT;
 vpHRes: LONGINT;			{Horizontal resolution of the device (pixels per inch).}
 vpVRes: LONGINT;			{Vertical resolution of the device (pixels per inch).}
 vpPixelType: INTEGER;		{Defines the pixel type.}
 vpPixelSize: INTEGER;		{Number of bits in pixel.}
 vpCmpCount: INTEGER;		{Number of components in pixel.}
 vpCmpSize: INTEGER;		{Number of bits per component}
 vpPlaneBytes: LONGINT;		{Offset from one plane to the next.}
 END;

VDEntRecPtr = ^VDEntryRecord;
VDEntryRecord = RECORD
 csTable: Ptr;				{(long) pointer to color table entry=value, r,g,b:INTEGER}
 END;

{ Parm block for SetGray control call }
VDGrayPtr = ^VDGrayRecord;
VDGrayRecord = RECORD
 csMode: BOOLEAN;			{Same as GDDevType value (0=mono, 1=color)}
 END;

{ Parm block for SetEntries control call }
VDSetEntryPtr = ^VDSetEntryRecord;
VDSetEntryRecord = RECORD
 csTable: ^ColorSpec;		{Pointer to an array of color specs}
 csStart: INTEGER;			{Which spec in array to start with, or -1}
 csCount: INTEGER;			{Number of color spec entries to set}
 END;

{ Parm block for SetGamma control call }
VDGamRecPtr = ^VDGammaRecord;
VDGammaRecord = RECORD
 csGTable: Ptr;				{pointer to gamma table}
 END;

VDPgInfoPtr = ^VDPageInfo;
VDPageInfo = RECORD
 csMode: INTEGER;			{(word) mode within device}
 csData: LONGINT;			{(long) data supplied by driver}
 csPage: INTEGER;			{(word) page to switch in}
 csBaseAddr: Ptr;			{(long) base address of page}
 END;

VDSzInfoPtr = ^VDSizeInfo;
VDSizeInfo = RECORD
 csHSize: INTEGER;			{(word) desired/returned h size}
 csHPos: INTEGER;			{(word) desired/returned h position}
 csVSize: INTEGER;			{(word) desired/returned v size}
 csVPos: INTEGER;			{(word) desired/returned v position}
 END;

VDSettingsPtr = ^VDSettings;
VDSettings = RECORD
 csParamCnt: INTEGER;		{(word) number of params}
 csBrightMax: INTEGER;		{(word) max brightness}
 csBrightDef: INTEGER;		{(word) default brightness}
 csBrightVal: INTEGER;		{(word) current brightness}
 csCntrstMax: INTEGER;		{(word) max contrast}
 csCntrstDef: INTEGER;		{(word) default contrast}
 csCntrstVal: INTEGER;		{(word) current contrast}
 csTintMax: INTEGER;		{(word) max tint}
 csTintDef: INTEGER;		{(word) default tint}
 csTintVal: INTEGER;		{(word) current tint}
 csHueMax: INTEGER;			{(word) max hue}
 csHueDef: INTEGER;			{(word) default hue}
 csHueVal: INTEGER;			{(word) current hue}
 csHorizDef: INTEGER;		{(word) default horizontal}
 csHorizVal: INTEGER;		{(word) current horizontal}
 csHorizMax: INTEGER;		{(word) max horizontal}
 csVertDef: INTEGER;		{(word) default vertical}
 csVertVal: INTEGER;		{(word) current vertical}
 csVertMax: INTEGER;		{(word) max vertical}
 END;



{$ENDC} { UsingVideo }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

