
{
Created: Saturday, July 27, 1991 at 10:42 PM
 Quickdraw.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    
	Change History (most recent first):

		<19>	  7/6/92	KON		No longer need bits 5 and 6 in gdFlags. Move bit 4 to bit 6.
		<18>	 6/30/92	KON		Add three new gdFlags: Bit 4 hasAuxMenuBar, Bit 5
									pixelsAreSlewSlow, and Bit 6 whiteIsOff.
		<17>	 5/29/92	DCL		Moved StdText from QuickDraw to QuickDrawText.
		<16>	  5/5/92	DCL		For New Inside Mac: removing 'sc' prefixes from some calls,
									moving some calls from script to TextUtils, and moving some from
									TextUtils & QuickDraw to QuickdrawText. Weeeeeeee!
		<15>	 4/15/92	DCL		For New Inside Mac: Moved many definitions from Script to
									TextUtils and QuickDraw. And added new synonyms. #1025005
		<14>	 7/31/91	JL		Updated Copyright. Restored Comments.
		<13>	  2/4/91	JL		Added burstDevice and ext32Device.
		<12>	 1/28/91	LN		Checked in Database Generated File from DSG. Added Dispose
									synonym for Dispos calls.
		<11>	12/14/90	KON		Change name of PICT2Header to OpenCPicParams.[smc]
		 <10>	 10/3/90	JAL		Added Inline for GetMaskTable, Added BitMapToRegionGlue call 
		 							for pre Mac II machines, changed QDProcsPtr to a CQDProcsPtr
									in CGrafPort, added RGBDirect, baseAddr32, rgnOverflowErr, 
									and insufficientStackErr
		 <9>	 9/15/90	KON		Added CopyDeepMask, OpenCPicture, and PICT2Header record.
		 <8>	 9/14/90	csd		Added interfaces for the DeviceLoop call.
		 <7>	  9/4/90	kaz		Adding grayishTextOr text mode.
		 <6>	 6/19/90	DVB		Add "ColorSpecPtr" type

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Quickdraw;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingQuickdraw}
{$SETC UsingQuickdraw := 1}

{$I+}
{$SETC QuickdrawIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdrawText}
{$I $$Shell(PInterfaces)QuickdrawText.p}
{$ENDC}
{$SETC UsingIncludes := QuickdrawIncludes}

CONST
invalColReq = -1;							{invalid color table request}

{ transfer modes }
srcCopy = 0;								{the 16 transfer modes}
srcOr = 1;
srcXor = 2;
srcBic = 3;
notSrcCopy = 4;
notSrcOr = 5;
notSrcXor = 6;
notSrcBic = 7;
patCopy = 8;
patOr = 9;
patXor = 10;
patBic = 11;
notPatCopy = 12;
notPatOr = 13;
notPatXor = 14;
notPatBic = 15;

{ Special Text Transfer Mode }
grayishTextOr = 49;

{ Arithmetic transfer modes }
blend = 32;
addPin = 33;
addOver = 34;
subPin = 35;
addMax = 37;
adMax = 37;
subOver = 38;
adMin = 39;
ditherCopy = 64;

{ Transparent mode constant }
transparent = 36;

{ QuickDraw color separation constants }
normalBit = 0;								{normal screen mapping}
inverseBit = 1;								{inverse screen mapping}
redBit = 4;									{RGB additive mapping}
greenBit = 3;
blueBit = 2;
cyanBit = 8;								{CMYBk subtractive mapping}
magentaBit = 7;
yellowBit = 6;
blackBit = 5;
blackColor = 33;							{colors expressed in these mappings}
whiteColor = 30;
redColor = 205;
greenColor = 341;
blueColor = 409;
cyanColor = 273;
magentaColor = 137;
yellowColor = 69;

picLParen = 0;								{standard picture comments}
picRParen = 1;


clutType = 0;								{0 if lookup table}
fixedType = 1;								{1 if fixed table}
directType = 2;								{2 if direct values}

gdDevType = 0;								{0 = monochrome 1 = color}
hasAuxMenuBar = 6;							{1 if device has an aux menu bar on it}
burstDevice = 7;
ext32Device = 8;
ramInit = 10;								{1 if initialized from 'scrn' resource}
mainScreen = 11;							{1 if main screen }
allInit = 12;								{1 if all devices initialized }
screenDevice = 13;							{1 if screen device [not used]}
noDriver = 14;								{1 if no driver for this GDevice }
screenActive = 15;							{1 if in use}

hiliteBit = 7;								{flag bit in HiliteMode (lowMem flag)}
pHiliteBit = 0;								{flag bit in HiliteMode used with BitClr procedure}

defQDColors = 127;							{resource ID of clut for default QDColors}

{ pixel type }
RGBDirect = 16;								{16 & 32 bits/pixel pixelType value }

{ pmVersion values }
baseAddr32 = 4;								{pixmap base address is 32-bit address}

rgnOverflowErr = -147;						{Region accumulation failed. Resulting region may be currupt }
insufficientStackErr = -149;				{QuickDraw could not complete the operation }



TYPE
GrafVerb = (frame,paint,erase,invert,fill);

PixelType = (chunky,chunkyPlanar,planar);



PatPtr = ^Pattern;
PatHandle = ^PatPtr;

Pattern = PACKED ARRAY [0..7] OF 0..255;

QDByte = SignedByte;

QDPtr = Ptr;								{ blind pointer }

QDHandle = Handle;							{ blind handle }



QDErr = INTEGER;

Bits16 = ARRAY [0..15] OF INTEGER;



DeviceLoopFlags = SET OF (singleDevices,dontMatchSeeds,allDevices,DeviceLoopFlags3,
 DeviceLoopFlags4,DeviceLoopFlags5,DeviceLoopFlags6,DeviceLoopFlags7,DeviceLoopFlags8,
 DeviceLoopFlags9,DeviceLoopFlags10,DeviceLoopFlags11,DeviceLoopFlags12,
 DeviceLoopFlags13,DeviceLoopFlags14,DeviceLoopFlags15,DeviceLoopFlags16,
 DeviceLoopFlags17,DeviceLoopFlags18,DeviceLoopFlags19,DeviceLoopFlags20,
 DeviceLoopFlags21,DeviceLoopFlags22,DeviceLoopFlags23,DeviceLoopFlags24,
 DeviceLoopFlags25,DeviceLoopFlags26,DeviceLoopFlags27,DeviceLoopFlags28,
 DeviceLoopFlags29,DeviceLoopFlags30,DeviceLoopFlags31);


BitMapPtr = ^BitMap;
BitMapHandle = ^BitMapPtr;
BitMap = RECORD
 baseAddr: Ptr;
 rowBytes: INTEGER;
 bounds: Rect;
 END;

CursPtr = ^Cursor;
CursHandle = ^CursPtr;
Cursor = RECORD
 data: Bits16;
 mask: Bits16;
 hotSpot: Point;
 END;

PenState = RECORD
 pnLoc: Point;
 pnSize: Point;
 pnMode: INTEGER;
 pnPat: Pattern;
 END;

RgnPtr = ^Region;
RgnHandle = ^RgnPtr;
Region = RECORD
 rgnSize: INTEGER;							{size in bytes}
 rgnBBox: Rect;								{enclosing rectangle}
 END;

PicPtr = ^Picture;
PicHandle = ^PicPtr;
Picture = RECORD
 picSize: INTEGER;
 picFrame: Rect;
 END;

PolyPtr = ^Polygon;
PolyHandle = ^PolyPtr;
Polygon = RECORD
 polySize: INTEGER;
 polyBBox: Rect;
 polyPoints: ARRAY [0..0] OF Point;
 END;

QDProcsPtr = ^QDProcs;
QDProcs = RECORD
 textProc: Ptr;
 lineProc: Ptr;
 rectProc: Ptr;
 rRectProc: Ptr;
 ovalProc: Ptr;
 arcProc: Ptr;
 polyProc: Ptr;
 rgnProc: Ptr;
 bitsProc: Ptr;
 commentProc: Ptr;
 txMeasProc: Ptr;
 getPicProc: Ptr;
 putPicProc: Ptr;
 END;

GrafPtr = ^GrafPort;
GrafPort = RECORD
 device: INTEGER;
 portBits: BitMap;
 portRect: Rect;
 visRgn: RgnHandle;
 clipRgn: RgnHandle;
 bkPat: Pattern;
 fillPat: Pattern;
 pnLoc: Point;
 pnSize: Point;
 pnMode: INTEGER;
 pnPat: Pattern;
 pnVis: INTEGER;
 txFont: INTEGER;
 txFace: Style;								{txFace is unpacked byte but push as short}
 txMode: INTEGER;
 txSize: INTEGER;
 spExtra: Fixed;
 fgColor: LONGINT;
 bkColor: LONGINT;
 colrBit: INTEGER;
 patStretch: INTEGER;
 picSave: Handle;
 rgnSave: Handle;
 polySave: Handle;
 grafProcs: QDProcsPtr;
 END;


WindowPtr = GrafPtr;

{typedef pascal Boolean (*ColorSearchProcPtr)(RGBColor *rgb, long *position);
typedef pascal Boolean (*ColorComplementProcPtr)(RGBColor *rgb);}

RGBColor = RECORD
 red: INTEGER;								{magnitude of red component}
 green: INTEGER;							{magnitude of green component}
 blue: INTEGER;								{magnitude of blue component}
 END;

ColorSpecPtr = ^ColorSpec;
ColorSpec = RECORD
 value: INTEGER;							{index or other value}
 rgb: RGBColor;								{true color}
 END;


CSpecArray = ARRAY [0..0] OF ColorSpec;

CTabPtr = ^ColorTable;
CTabHandle = ^CTabPtr;
ColorTable = RECORD
 ctSeed: LONGINT;							{unique identifier for table}
 ctFlags: INTEGER;							{high bit: 0 = PixMap; 1 = device}
 ctSize: INTEGER;							{number of entries in CTTable}
 ctTable: CSpecArray;						{array [0..0] of ColorSpec}
 END;

MatchRec = RECORD
 red: INTEGER;
 green: INTEGER;
 blue: INTEGER;
 matchData: LONGINT;
 END;

PixMapPtr = ^PixMap;
PixMapHandle = ^PixMapPtr;
PixMap = RECORD
 baseAddr: Ptr;								{pointer to pixels}
 rowBytes: INTEGER;							{offset to next line}
 bounds: Rect;								{encloses bitmap}
 pmVersion: INTEGER;						{pixMap version number}
 packType: INTEGER;							{defines packing format}
 packSize: LONGINT;							{length of pixel data}
 hRes: Fixed;								{horiz. resolution (ppi)}
 vRes: Fixed;								{vert. resolution (ppi)}
 pixelType: INTEGER;						{defines pixel type}
 pixelSize: INTEGER;						{# bits in pixel}
 cmpCount: INTEGER;							{# components in pixel}
 cmpSize: INTEGER;							{# bits per component}
 planeBytes: LONGINT;						{offset to next plane}
 pmTable: CTabHandle;						{color map for this pixMap}
 pmReserved: LONGINT;						{for future use. MUST BE 0}
 END;

PixPatPtr = ^PixPat;
PixPatHandle = ^PixPatPtr;
PixPat = RECORD
 patType: INTEGER;							{type of pattern}
 patMap: PixMapHandle;						{the pattern's pixMap}
 patData: Handle;							{pixmap's data}
 patXData: Handle;							{expanded Pattern data}
 patXValid: INTEGER;						{flags whether expanded Pattern valid}
 patXMap: Handle;							{Handle to expanded Pattern data}
 pat1Data: Pattern;							{old-Style pattern/RGB color}
 END;

CCrsrPtr = ^CCrsr;
CCrsrHandle = ^CCrsrPtr;
CCrsr = RECORD
 crsrType: INTEGER;							{type of cursor}
 crsrMap: PixMapHandle;						{the cursor's pixmap}
 crsrData: Handle;							{cursor's data}
 crsrXData: Handle;							{expanded cursor data}
 crsrXValid: INTEGER;						{depth of expanded data (0 if none)}
 crsrXHandle: Handle;						{future use}
 crsr1Data: Bits16;							{one-bit cursor}
 crsrMask: Bits16;							{cursor's mask}
 crsrHotSpot: Point;						{cursor's hotspot}
 crsrXTable: LONGINT;						{private}
 crsrID: LONGINT;							{private}
 END;

CIconPtr = ^CIcon;
CIconHandle = ^CIconPtr;
CIcon = RECORD
 iconPMap: PixMap;							{the icon's pixMap}
 iconMask: BitMap;							{the icon's mask}
 iconBMap: BitMap;							{the icon's bitMap}
 iconData: Handle;							{the icon's data}
 iconMaskData: ARRAY [0..0] OF INTEGER;		{icon's mask and BitMap data}
 END;

GammaTblPtr = ^GammaTbl;
GammaTblHandle = ^GammaTblPtr;
GammaTbl = RECORD
 gVersion: INTEGER;							{gamma version number}
 gType: INTEGER;							{gamma data type}
 gFormulaSize: INTEGER;						{Formula data size}
 gChanCnt: INTEGER;							{number of channels of data}
 gDataCnt: INTEGER;							{number of values/channel}
 gDataWidth: INTEGER;						{bits/corrected value (data packed to next larger byte size)}
 gFormulaData: ARRAY [0..0] OF INTEGER;		{data for formulas followed by gamma values}
 END;

ITabPtr = ^ITab;
ITabHandle = ^ITabPtr;
ITab = RECORD
 iTabSeed: LONGINT;							{copy of CTSeed from source CTable}
 iTabRes: INTEGER;							{bits/channel resolution of iTable}
 iTTable: ARRAY [0..0] OF SignedByte;		{byte colortable index values}
 END;

SProcPtr = ^SProcRec;
SProcHndl = ^SProcPtr;
SProcRec = RECORD
 nxtSrch: Handle;							{SProcHndl Handle to next SProcRec}
 srchProc: ProcPtr;							{pointer to search procedure}
 END;

CProcPtr = ^CProcRec;
CProcHndl = ^CProcPtr;
CProcRec = RECORD
 nxtComp: CProcHndl;						{CProcHndl Handle to next CProcRec}
 compProc: ProcPtr;							{pointer to complement procedure}
 END;

GDPtr = ^GDevice;
GDHandle = ^GDPtr;
GDevice = RECORD
 gdRefNum: INTEGER;							{driver's unit number}
 gdID: INTEGER;								{client ID for search procs}
 gdType: INTEGER;							{fixed/CLUT/direct}
 gdITable: ITabHandle;						{Handle to inverse lookup table}
 gdResPref: INTEGER;						{preferred resolution of GDITable}
 gdSearchProc: SProcHndl;					{search proc list head}
 gdCompProc: CProcHndl;						{complement proc list}
 gdFlags: INTEGER;							{grafDevice flags word}
 gdPMap: PixMapHandle;						{describing pixMap}
 gdRefCon: LONGINT;							{reference value}
 gdNextGD: GDHandle;						{GDHandle Handle of next gDevice}
 gdRect: Rect;								{ device's bounds in global coordinates}
 gdMode: LONGINT;							{device's current mode}
 gdCCBytes: INTEGER;						{depth of expanded cursor data}
 gdCCDepth: INTEGER;						{depth of expanded cursor data}
 gdCCXData: Handle;							{Handle to cursor's expanded data}
 gdCCXMask: Handle;							{Handle to cursor's expanded mask}
 gdReserved: LONGINT;						{future use. MUST BE 0}
 END;

GVarPtr = ^GrafVars;
GVarHandle = ^GVarPtr;
GrafVars = RECORD
 rgbOpColor: RGBColor;						{color for addPin  subPin and average}
 rgbHiliteColor: RGBColor;					{color for hiliting}
 pmFgColor: Handle;							{palette Handle for foreground color}
 pmFgIndex: INTEGER;						{index value for foreground}
 pmBkColor: Handle;							{palette Handle for background color}
 pmBkIndex: INTEGER;						{index value for background}
 pmFlags: INTEGER;							{flags for Palette Manager}
 END;

CQDProcsPtr = ^CQDProcs;
CQDProcs = RECORD
 textProc: Ptr;
 lineProc: Ptr;
 rectProc: Ptr;
 rRectProc: Ptr;
 ovalProc: Ptr;
 arcProc: Ptr;
 polyProc: Ptr;
 rgnProc: Ptr;
 bitsProc: Ptr;
 commentProc: Ptr;
 txMeasProc: Ptr;
 getPicProc: Ptr;
 putPicProc: Ptr;
 opcodeProc: Ptr;							{fields added to QDProcs}
 newProc1: Ptr;
 newProc2: Ptr;
 newProc3: Ptr;
 newProc4: Ptr;
 newProc5: Ptr;
 newProc6: Ptr;
 END;

CGrafPtr = ^CGrafPort;
CGrafPort = RECORD
 device: INTEGER;
 portPixMap: PixMapHandle;					{port's pixel map}
 portVersion: INTEGER;						{high 2 bits always set}
 grafVars: Handle;							{Handle to more fields}
 chExtra: INTEGER;							{character extra}
 pnLocHFrac: INTEGER;						{pen fraction}
 portRect: Rect;
 visRgn: RgnHandle;
 clipRgn: RgnHandle;
 bkPixPat: PixPatHandle;					{background pattern}
 rgbFgColor: RGBColor;						{RGB components of fg}
 rgbBkColor: RGBColor;						{RGB components of bk}
 pnLoc: Point;
 pnSize: Point;
 pnMode: INTEGER;
 pnPixPat: PixPatHandle;					{pen's pattern}
 fillPixPat: PixPatHandle;					{fill pattern}
 pnVis: INTEGER;
 txFont: INTEGER;
 txFace: Style;								{txFace is unpacked byte  push as short}
 txMode: INTEGER;
 txSize: INTEGER;
 spExtra: Fixed;
 fgColor: LONGINT;
 bkColor: LONGINT;
 colrBit: INTEGER;
 patStretch: INTEGER;
 picSave: Handle;
 rgnSave: Handle;
 polySave: Handle;
 grafProcs: CQDProcsPtr;
 END;


CWindowPtr = CGrafPtr;

ReqListRec = RECORD
 reqLSize: INTEGER;							{request list size}
 reqLData: ARRAY [0..0] OF INTEGER;			{request list data}
 END;

OpenCPicParams = RECORD
 srcRect: Rect;
 hRes: Fixed;
 vRes: Fixed;
 version: INTEGER;
 reserved1: INTEGER;
 reserved2: LONGINT;
 END;


DeviceLoopDrawingProcPtr = ProcPtr;


VAR
{$PUSH}
{$J+}
 thePort: GrafPtr;
 white: Pattern;
 black: Pattern;
 gray: Pattern;
 ltGray: Pattern;
 dkGray: Pattern;
 arrow: Cursor;
 screenBits: BitMap;
 randSeed: LONGINT;
{$POP}



PROCEDURE InitGraf(globalPtr: Ptr);
 INLINE $A86E;
PROCEDURE OpenPort(port: GrafPtr);
 INLINE $A86F;
PROCEDURE InitPort(port: GrafPtr);
 INLINE $A86D;
PROCEDURE ClosePort(port: GrafPtr);
 INLINE $A87D;
PROCEDURE SetPort(port: GrafPtr);
 INLINE $A873;
PROCEDURE GetPort(VAR port: GrafPtr);
 INLINE $A874;
PROCEDURE GrafDevice(device: INTEGER);
 INLINE $A872;
PROCEDURE SetPortBits(bm: BitMap);
 INLINE $A875;
PROCEDURE PortSize(width: INTEGER;height: INTEGER);
 INLINE $A876;
PROCEDURE MovePortTo(leftGlobal: INTEGER;topGlobal: INTEGER);
 INLINE $A877;
PROCEDURE SetOrigin(h: INTEGER;v: INTEGER);
 INLINE $A878;
PROCEDURE SetClip(rgn: RgnHandle);
 INLINE $A879;
PROCEDURE GetClip(rgn: RgnHandle);
 INLINE $A87A;
PROCEDURE ClipRect(r: Rect);
 INLINE $A87B;
PROCEDURE BackPat(pat: Pattern);
 INLINE $A87C;
PROCEDURE InitCursor;
 INLINE $A850;
PROCEDURE SetCursor(crsr: Cursor);
 INLINE $A851;
PROCEDURE HideCursor;
 INLINE $A852;
PROCEDURE ShowCursor;
 INLINE $A853;
PROCEDURE ObscureCursor;
 INLINE $A856;
PROCEDURE HidePen;
 INLINE $A896;
PROCEDURE ShowPen;
 INLINE $A897;
PROCEDURE GetPen(VAR pt: Point);
 INLINE $A89A;
PROCEDURE GetPenState(VAR pnState: PenState);
 INLINE $A898;
PROCEDURE SetPenState(pnState: PenState);
 INLINE $A899;
PROCEDURE PenSize(width: INTEGER;height: INTEGER);
 INLINE $A89B;
PROCEDURE PenMode(mode: INTEGER);
 INLINE $A89C;
PROCEDURE PenPat(pat: Pattern);
 INLINE $A89D;
PROCEDURE PenNormal;
 INLINE $A89E;
PROCEDURE MoveTo(h: INTEGER;v: INTEGER);
 INLINE $A893;
PROCEDURE Move(dh: INTEGER;dv: INTEGER);
 INLINE $A894;
PROCEDURE LineTo(h: INTEGER;v: INTEGER);
 INLINE $A891;
PROCEDURE Line(dh: INTEGER;dv: INTEGER);
 INLINE $A892;
PROCEDURE ForeColor(color: LONGINT);
 INLINE $A862;
PROCEDURE BackColor(color: LONGINT);
 INLINE $A863;
PROCEDURE ColorBit(whichBit: INTEGER);
 INLINE $A864;
PROCEDURE SetRect(VAR r: Rect;left: INTEGER;top: INTEGER;right: INTEGER;
 bottom: INTEGER);
 INLINE $A8A7;
PROCEDURE OffsetRect(VAR r: Rect;dh: INTEGER;dv: INTEGER);
 INLINE $A8A8;
PROCEDURE InsetRect(VAR r: Rect;dh: INTEGER;dv: INTEGER);
 INLINE $A8A9;
FUNCTION SectRect(src1: Rect;src2: Rect;VAR dstRect: Rect): BOOLEAN;
 INLINE $A8AA;
PROCEDURE UnionRect(src1: Rect;src2: Rect;VAR dstRect: Rect);
 INLINE $A8AB;
FUNCTION EqualRect(rect1: Rect;rect2: Rect): BOOLEAN;
 INLINE $A8A6;
FUNCTION EmptyRect(r: Rect): BOOLEAN;
 INLINE $A8AE;
PROCEDURE FrameRect(r: Rect);
 INLINE $A8A1;
PROCEDURE PaintRect(r: Rect);
 INLINE $A8A2;
PROCEDURE EraseRect(r: Rect);
 INLINE $A8A3;
PROCEDURE InvertRect(r: Rect);
 INLINE $A8A4;
PROCEDURE FillRect(r: Rect;pat: Pattern);
 INLINE $A8A5;
PROCEDURE FrameOval(r: Rect);
 INLINE $A8B7;
PROCEDURE PaintOval(r: Rect);
 INLINE $A8B8;
PROCEDURE EraseOval(r: Rect);
 INLINE $A8B9;
PROCEDURE InvertOval(r: Rect);
 INLINE $A8BA;
PROCEDURE FillOval(r: Rect;pat: Pattern);
 INLINE $A8BB;
PROCEDURE FrameRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER);
 INLINE $A8B0;
PROCEDURE PaintRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER);
 INLINE $A8B1;
PROCEDURE EraseRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER);
 INLINE $A8B2;
PROCEDURE InvertRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER);
 INLINE $A8B3;
PROCEDURE FillRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER;
 pat: Pattern);
 INLINE $A8B4;
PROCEDURE FrameArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER);
 INLINE $A8BE;
PROCEDURE PaintArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER);
 INLINE $A8BF;
PROCEDURE EraseArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER);
 INLINE $A8C0;
PROCEDURE InvertArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER);
 INLINE $A8C1;
PROCEDURE FillArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER;pat: Pattern);
 INLINE $A8C2;
FUNCTION NewRgn: RgnHandle;
 INLINE $A8D8;
PROCEDURE OpenRgn;
 INLINE $A8DA;
PROCEDURE CloseRgn(dstRgn: RgnHandle);
 INLINE $A8DB;
FUNCTION BitMapToRegionGlue(region: RgnHandle;bMap: BitMap): OSErr;
FUNCTION BitMapToRegion(region: RgnHandle;bMap: BitMap): OSErr;
 INLINE $A8D7;
PROCEDURE DisposeRgn(rgn: RgnHandle);
 INLINE $A8D9;
PROCEDURE CopyRgn(srcRgn: RgnHandle;dstRgn: RgnHandle);
 INLINE $A8DC;
PROCEDURE SetEmptyRgn(rgn: RgnHandle);
 INLINE $A8DD;
PROCEDURE SetRectRgn(rgn: RgnHandle;left: INTEGER;top: INTEGER;right: INTEGER;
 bottom: INTEGER);
 INLINE $A8DE;
PROCEDURE RectRgn(rgn: RgnHandle;r: Rect);
 INLINE $A8DF;
PROCEDURE OffsetRgn(rgn: RgnHandle;dh: INTEGER;dv: INTEGER);
 INLINE $A8E0;
PROCEDURE InsetRgn(rgn: RgnHandle;dh: INTEGER;dv: INTEGER);
 INLINE $A8E1;
PROCEDURE SectRgn(srcRgnA: RgnHandle;srcRgnB: RgnHandle;dstRgn: RgnHandle);
 INLINE $A8E4;
PROCEDURE UnionRgn(srcRgnA: RgnHandle;srcRgnB: RgnHandle;dstRgn: RgnHandle);
 INLINE $A8E5;
PROCEDURE DiffRgn(srcRgnA: RgnHandle;srcRgnB: RgnHandle;dstRgn: RgnHandle);
 INLINE $A8E6;
PROCEDURE XorRgn(srcRgnA: RgnHandle;srcRgnB: RgnHandle;dstRgn: RgnHandle);
 INLINE $A8E7;
FUNCTION RectInRgn(r: Rect;rgn: RgnHandle): BOOLEAN;
 INLINE $A8E9;
FUNCTION EqualRgn(rgnA: RgnHandle;rgnB: RgnHandle): BOOLEAN;
 INLINE $A8E3;
FUNCTION EmptyRgn(rgn: RgnHandle): BOOLEAN;
 INLINE $A8E2;
PROCEDURE FrameRgn(rgn: RgnHandle);
 INLINE $A8D2;
PROCEDURE PaintRgn(rgn: RgnHandle);
 INLINE $A8D3;
PROCEDURE EraseRgn(rgn: RgnHandle);
 INLINE $A8D4;
PROCEDURE InvertRgn(rgn: RgnHandle);
 INLINE $A8D5;
PROCEDURE FillRgn(rgn: RgnHandle;pat: Pattern);
 INLINE $A8D6;
PROCEDURE ScrollRect(r: Rect;dh: INTEGER;dv: INTEGER;updateRgn: RgnHandle);
 INLINE $A8EF;
PROCEDURE CopyBits(srcBits: BitMap;dstBits: BitMap;srcRect: Rect;dstRect: Rect;
 mode: INTEGER;maskRgn: RgnHandle);
 INLINE $A8EC;
PROCEDURE SeedFill(srcPtr: Ptr;dstPtr: Ptr;srcRow: INTEGER;dstRow: INTEGER;
 height: INTEGER;words: INTEGER;seedH: INTEGER;seedV: INTEGER);
 INLINE $A839;
PROCEDURE CalcMask(srcPtr: Ptr;dstPtr: Ptr;srcRow: INTEGER;dstRow: INTEGER;
 height: INTEGER;words: INTEGER);
 INLINE $A838;
PROCEDURE CopyMask(srcBits: BitMap;maskBits: BitMap;dstBits: BitMap;srcRect: Rect;
 maskRect: Rect;dstRect: Rect);
 INLINE $A817;
FUNCTION OpenPicture(picFrame: Rect): PicHandle;
 INLINE $A8F3;
PROCEDURE PicComment(kind: INTEGER;dataSize: INTEGER;dataHandle: Handle);
 INLINE $A8F2;
PROCEDURE ClosePicture;
 INLINE $A8F4;
PROCEDURE DrawPicture(myPicture: PicHandle;dstRect: Rect);
 INLINE $A8F6;
PROCEDURE KillPicture(myPicture: PicHandle);
 INLINE $A8F5;
FUNCTION OpenPoly: PolyHandle;
 INLINE $A8CB;
PROCEDURE ClosePoly;
 INLINE $A8CC;
PROCEDURE KillPoly(poly: PolyHandle);
 INLINE $A8CD;
PROCEDURE OffsetPoly(poly: PolyHandle;dh: INTEGER;dv: INTEGER);
 INLINE $A8CE;
PROCEDURE FramePoly(poly: PolyHandle);
 INLINE $A8C6;
PROCEDURE PaintPoly(poly: PolyHandle);
 INLINE $A8C7;
PROCEDURE ErasePoly(poly: PolyHandle);
 INLINE $A8C8;
PROCEDURE InvertPoly(poly: PolyHandle);
 INLINE $A8C9;
PROCEDURE FillPoly(poly: PolyHandle;pat: Pattern);
 INLINE $A8CA;
PROCEDURE SetPt(VAR pt: Point;h: INTEGER;v: INTEGER);
 INLINE $A880;
PROCEDURE LocalToGlobal(VAR pt: Point);
 INLINE $A870;
PROCEDURE GlobalToLocal(VAR pt: Point);
 INLINE $A871;
FUNCTION Random: INTEGER;
 INLINE $A861;
PROCEDURE StuffHex(thingPtr: Ptr;s: Str255);
 INLINE $A866;
FUNCTION GetPixel(h: INTEGER;v: INTEGER): BOOLEAN;
 INLINE $A865;
PROCEDURE ScalePt(VAR pt: Point;srcRect: Rect;dstRect: Rect);
 INLINE $A8F8;
PROCEDURE MapPt(VAR pt: Point;srcRect: Rect;dstRect: Rect);
 INLINE $A8F9;
PROCEDURE MapRect(VAR r: Rect;srcRect: Rect;dstRect: Rect);
 INLINE $A8FA;
PROCEDURE MapRgn(rgn: RgnHandle;srcRect: Rect;dstRect: Rect);
 INLINE $A8FB;
PROCEDURE MapPoly(poly: PolyHandle;srcRect: Rect;dstRect: Rect);
 INLINE $A8FC;
PROCEDURE SetStdProcs(VAR procs: QDProcs);
 INLINE $A8EA;
PROCEDURE StdRect(verb: GrafVerb;r: Rect);
 INLINE $A8A0;
PROCEDURE StdRRect(verb: GrafVerb;r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER);
 INLINE $A8AF;
PROCEDURE StdOval(verb: GrafVerb;r: Rect);
 INLINE $A8B6;
PROCEDURE StdArc(verb: GrafVerb;r: Rect;startAngle: INTEGER;arcAngle: INTEGER);
 INLINE $A8BD;
PROCEDURE StdPoly(verb: GrafVerb;poly: PolyHandle);
 INLINE $A8C5;
PROCEDURE StdRgn(verb: GrafVerb;rgn: RgnHandle);
 INLINE $A8D1;
PROCEDURE StdBits(VAR srcBits: BitMap;VAR srcRect: Rect;dstRect: Rect;mode: INTEGER;
    maskRgn: RgnHandle);
    INLINE $A8EB;
PROCEDURE StdComment(kind: INTEGER;dataSize: INTEGER;dataHandle: Handle);
 INLINE $A8F1;
PROCEDURE StdGetPic(dataPtr: Ptr;byteCount: INTEGER);
 INLINE $A8EE;
PROCEDURE StdPutPic(dataPtr: Ptr;byteCount: INTEGER);
 INLINE $A8F0;
PROCEDURE AddPt(src: Point;VAR dst: Point);
 INLINE $A87E;
FUNCTION EqualPt(pt1: Point;pt2: Point): BOOLEAN;
 INLINE $A881;
FUNCTION PtInRect(pt: Point;r: Rect): BOOLEAN;
 INLINE $A8AD;
PROCEDURE Pt2Rect(pt1: Point;pt2: Point;VAR dstRect: Rect);
 INLINE $A8AC;
PROCEDURE PtToAngle(r: Rect;pt: Point;VAR angle: INTEGER);
 INLINE $A8C3;
FUNCTION PtInRgn(pt: Point;rgn: RgnHandle): BOOLEAN;
 INLINE $A8E8;
PROCEDURE StdLine(newPt: Point);
 INLINE $A890;
PROCEDURE OpenCPort(port: CGrafPtr);
 INLINE $AA00;
PROCEDURE InitCPort(port: CGrafPtr);
 INLINE $AA01;
PROCEDURE CloseCPort(port: CGrafPtr);
 INLINE $A87D;
FUNCTION NewPixMap: PixMapHandle;
 INLINE $AA03;
PROCEDURE DisposPixMap(pm: PixMapHandle);
 INLINE $AA04;
PROCEDURE DisposePixMap(pm: PixMapHandle);
 INLINE $AA04;
PROCEDURE CopyPixMap(srcPM: PixMapHandle;dstPM: PixMapHandle);
 INLINE $AA05;
FUNCTION NewPixPat: PixPatHandle;
 INLINE $AA07;
PROCEDURE DisposPixPat(pp: PixPatHandle);
 INLINE $AA08;
PROCEDURE DisposePixPat(pp: PixPatHandle);
 INLINE $AA08;
PROCEDURE CopyPixPat(srcPP: PixPatHandle;dstPP: PixPatHandle);
 INLINE $AA09;
PROCEDURE PenPixPat(pp: PixPatHandle);
 INLINE $AA0A;
PROCEDURE BackPixPat(pp: PixPatHandle);
 INLINE $AA0B;
FUNCTION GetPixPat(patID: INTEGER): PixPatHandle;
 INLINE $AA0C;
PROCEDURE MakeRGBPat(pp: PixPatHandle;myColor: RGBColor);
 INLINE $AA0D;
PROCEDURE FillCRect(r: Rect;pp: PixPatHandle);
 INLINE $AA0E;
PROCEDURE FillCOval(r: Rect;pp: PixPatHandle);
 INLINE $AA0F;
PROCEDURE FillCRoundRect(r: Rect;ovalWidth: INTEGER;ovalHeight: INTEGER;
 pp: PixPatHandle);
 INLINE $AA10;
PROCEDURE FillCArc(r: Rect;startAngle: INTEGER;arcAngle: INTEGER;pp: PixPatHandle);
 INLINE $AA11;
PROCEDURE FillCRgn(rgn: RgnHandle;pp: PixPatHandle);
 INLINE $AA12;
PROCEDURE FillCPoly(poly: PolyHandle;pp: PixPatHandle);
 INLINE $AA13;
PROCEDURE RGBForeColor(color: RGBColor);
 INLINE $AA14;
PROCEDURE RGBBackColor(color: RGBColor);
 INLINE $AA15;
PROCEDURE SetCPixel(h: INTEGER;v: INTEGER;cPix: RGBColor);
 INLINE $AA16;
PROCEDURE SetPortPix(pm: PixMapHandle);
 INLINE $AA06;
PROCEDURE GetCPixel(h: INTEGER;v: INTEGER;VAR cPix: RGBColor);
 INLINE $AA17;
PROCEDURE GetForeColor(VAR color: RGBColor);
 INLINE $AA19;
PROCEDURE GetBackColor(VAR color: RGBColor);
 INLINE $AA1A;
PROCEDURE SeedCFill(srcBits: BitMap;dstBits: BitMap;srcRect: Rect;dstRect: Rect;
 seedH: INTEGER;seedV: INTEGER;matchProc: ProcPtr;matchData: LONGINT);
 INLINE $AA50;
PROCEDURE CalcCMask(srcBits: BitMap;dstBits: BitMap;srcRect: Rect;dstRect: Rect;
 seedRGB: RGBColor;matchProc: ProcPtr;matchData: LONGINT);
 INLINE $AA4F;
FUNCTION OpenCPicture(newHeader: OpenCPicParams): PicHandle;
 INLINE $AA20;
PROCEDURE OpColor(color: RGBColor);
 INLINE $AA21;
PROCEDURE HiliteColor(color: RGBColor);
 INLINE $AA22;
PROCEDURE DisposCTable(cTable: CTabHandle);
 INLINE $AA24;
PROCEDURE DisposeCTable(cTable: CTabHandle);
 INLINE $AA24;
FUNCTION GetCTable(ctID: INTEGER): CTabHandle;
 INLINE $AA18;
FUNCTION GetCCursor(crsrID: INTEGER): CCrsrHandle;
 INLINE $AA1B;
PROCEDURE SetCCursor(cCrsr: CCrsrHandle);
 INLINE $AA1C;
PROCEDURE AllocCursor;
 INLINE $AA1D;
PROCEDURE DisposCCursor(cCrsr: CCrsrHandle);
 INLINE $AA26;
PROCEDURE DisposeCCursor(cCrsr: CCrsrHandle);
 INLINE $AA26;
FUNCTION GetCIcon(iconID: INTEGER): CIconHandle;
 INLINE $AA1E;
PROCEDURE PlotCIcon(theRect: Rect;theIcon: CIconHandle);
 INLINE $AA1F;
PROCEDURE DisposCIcon(theIcon: CIconHandle);
 INLINE $AA25;
PROCEDURE DisposeCIcon(theIcon: CIconHandle);
 INLINE $AA25;
PROCEDURE SetStdCProcs(VAR procs: CQDProcs);
 INLINE $AA4E;
FUNCTION GetMaxDevice(globalRect: Rect): GDHandle;
 INLINE $AA27;
FUNCTION GetCTSeed: LONGINT;
 INLINE $AA28;
FUNCTION GetDeviceList: GDHandle;
 INLINE $AA29;
FUNCTION GetMainDevice: GDHandle;
 INLINE $AA2A;
FUNCTION GetNextDevice(curDevice: GDHandle): GDHandle;
 INLINE $AA2B;
FUNCTION TestDeviceAttribute(gdh: GDHandle;attribute: INTEGER): BOOLEAN;
 INLINE $AA2C;
PROCEDURE SetDeviceAttribute(gdh: GDHandle;attribute: INTEGER;value: BOOLEAN);
 INLINE $AA2D;
PROCEDURE InitGDevice(qdRefNum: INTEGER;mode: LONGINT;gdh: GDHandle);
 INLINE $AA2E;
FUNCTION NewGDevice(refNum: INTEGER;mode: LONGINT): GDHandle;
 INLINE $AA2F;
PROCEDURE DisposGDevice(gdh: GDHandle);
 INLINE $AA30;
PROCEDURE DisposeGDevice(gdh: GDHandle);
 INLINE $AA30;
PROCEDURE SetGDevice(gd: GDHandle);
 INLINE $AA31;
FUNCTION GetGDevice: GDHandle;
 INLINE $AA32;
FUNCTION Color2Index(myColor: RGBColor): LONGINT;
 INLINE $AA33;
PROCEDURE Index2Color(index: LONGINT;VAR aColor: RGBColor);
 INLINE $AA34;
PROCEDURE InvertColor(VAR myColor: RGBColor);
 INLINE $AA35;
FUNCTION RealColor(color: RGBColor): BOOLEAN;
 INLINE $AA36;
PROCEDURE GetSubTable(myColors: CTabHandle;iTabRes: INTEGER;targetTbl: CTabHandle);
 INLINE $AA37;
PROCEDURE MakeITable(cTabH: CTabHandle;iTabH: ITabHandle;res: INTEGER);
 INLINE $AA39;
PROCEDURE AddSearch(searchProc: ProcPtr);
 INLINE $AA3A;
PROCEDURE AddComp(compProc: ProcPtr);
 INLINE $AA3B;
PROCEDURE DelSearch(searchProc: ProcPtr);
 INLINE $AA4C;
PROCEDURE DelComp(compProc: ProcPtr);
 INLINE $AA4D;
PROCEDURE SubPt(src: Point;VAR dst: Point);
 INLINE $A87F;
PROCEDURE SetClientID(id: INTEGER);
 INLINE $AA3C;
PROCEDURE ProtectEntry(index: INTEGER;protect: BOOLEAN);
 INLINE $AA3D;
PROCEDURE ReserveEntry(index: INTEGER;reserve: BOOLEAN);
 INLINE $AA3E;
PROCEDURE SetEntries(start: INTEGER;count: INTEGER;aTable: CSpecArray);
 INLINE $AA3F;
PROCEDURE SaveEntries(srcTable: CTabHandle;resultTable: CTabHandle;VAR selection: ReqListRec);
 INLINE $AA49;
PROCEDURE RestoreEntries(srcTable: CTabHandle;dstTable: CTabHandle;VAR selection: ReqListRec);
 INLINE $AA4A;
FUNCTION QDError: INTEGER;
 INLINE $AA40;
PROCEDURE CopyDeepMask(srcBits: BitMap;maskBits: BitMap;dstBits: BitMap;
 srcRect: Rect;maskRect: Rect;dstRect: Rect;mode: INTEGER;maskRgn: RgnHandle);
 INLINE $AA51;
PROCEDURE DeviceLoop(drawingRgn: RgnHandle;drawingProc: DeviceLoopDrawingProcPtr;
 userData: LONGINT;flags: DeviceLoopFlags);
 INLINE $ABCA;
FUNCTION GetMaskTable: Ptr;
 INLINE $A836,$2E88;


{$ENDC} { UsingQuickdraw }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

