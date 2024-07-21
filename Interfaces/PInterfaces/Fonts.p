
{
Created: Saturday, July 27, 1991 at 9:19 PM
 Fonts.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved


	Change History (most recent first):

		 <9>	 4/15/92	DCL		For New Inside Mac: Moved GetDefFontSize, GetSysFont, and
									GetAppFont from Script to Fonts.
		 <8>	 7/30/91	JL		Updated Copyright.
		 <7>	 1/29/91	JL		Need to include Quickdraw for Style.
		 <6>	 1/27/91	LN		Checked in Database generate file from DSG. changed parameter
									name in GetFontName from name to theName to match .h file.
		 <5>	  1/5/91	JDR		(dba) Changed useSpline to outlinePreferred, glyphCount to
									byteCount and turnOffLineHeight to preserveGlyph.
		 <4>	12/14/90	dba		<JDR> add calls for outline fonts
		 <3>	 5/18/90	JAL		Added Quickdraw Inclusion.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Fonts;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFonts}
{$SETC UsingFonts := 1}

{$I+}
{$SETC FontsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := FontsIncludes}

CONST
systemFont = 0;
applFont = 1;
newYork = 2;
geneva = 3;
monaco = 4;
venice = 5;
london = 6;
athens = 7;
sanFran = 8;
toronto = 9;
cairo = 11;
losAngeles = 12;
times = 20;
helvetica = 21;
courier = 22;
symbol = 23;
mobile = 24;
commandMark = 17;
checkMark = 18;
diamondMark = 19;
appleMark = 20;
propFont = 36864;
prpFntH = 36865;
prpFntW = 36866;
prpFntHW = 36867;
fixedFont = 45056;
fxdFntH = 45057;
fxdFntW = 45058;
fxdFntHW = 45059;
fontWid = 44208;

TYPE
FMInput = PACKED RECORD
 family: INTEGER;
 size: INTEGER;
 face: Style;
 needBits: BOOLEAN;
 device: INTEGER;
 numer: Point;
 denom: Point;
 END;

FMOutPtr = ^FMOutput;
FMOutput = PACKED RECORD
 errNum: INTEGER;
 fontHandle: Handle;
 bold: Byte;
 italic: Byte;
 ulOffset: Byte;
 ulShadow: Byte;
 ulThick: Byte;
 shadow: Byte;
 extra: SignedByte;
 ascent: Byte;
 descent: Byte;
 widMax: Byte;
 leading: SignedByte;
 unused: Byte;
 numer: Point;
 denom: Point;
 END;

FontRec = RECORD
 fontType: INTEGER;						{font type}
 firstChar: INTEGER;					{ASCII code of first character}
 lastChar: INTEGER;						{ASCII code of last character}
 widMax: INTEGER;						{maximum character width}
 kernMax: INTEGER;						{negative of maximum character kern}
 nDescent: INTEGER;						{negative of descent}
 fRectWidth: INTEGER;					{width of font rectangle}
 fRectHeight: INTEGER;					{height of font rectangle}
 owTLoc: INTEGER;						{offset to offset/width table}
 ascent: INTEGER;						{ascent}
 descent: INTEGER;						{descent}
 leading: INTEGER;						{leading}
 rowWords: INTEGER;						{row width of bit image / 2 }
 END;

FMetricRec = RECORD
 ascent: Fixed;							{base line to top}
 descent: Fixed;						{base line to bottom}
 leading: Fixed;						{leading between lines}
 widMax: Fixed;							{maximum character width}
 wTabHandle: Handle;					{handle to font width table}
 END;

WidEntry = RECORD
 widStyle: INTEGER;						{style entry applies to}
 END;

WidTable = RECORD
 numWidths: INTEGER;					{number of entries - 1}
 END;

AsscEntry = RECORD
 fontSize: INTEGER;
 fontStyle: INTEGER;
 fontID: INTEGER;						{font resource ID}
 END;

FontAssoc = RECORD
 numAssoc: INTEGER;						{number of entries - 1}
 END;

StyleTable = RECORD
 fontClass: INTEGER;
 offset: LONGINT;
 reserved: LONGINT;
 indexes: ARRAY [0..47] OF SignedByte;
 END;

NameTable = RECORD
 stringCount: INTEGER;
 baseFontName: Str255;
 END;

KernPair = RECORD
 kernFirst: CHAR;						{1st character of kerned pair}
 kernSecond: CHAR;						{2nd character of kerned pair}
 kernWidth: INTEGER;					{kerning in 1pt fixed format}
 END;

KernEntry = RECORD
 kernLength: INTEGER;					{length of this entry}
 kernStyle: INTEGER;					{style the entry applies to}
 END;

KernTable = RECORD
 numKerns: INTEGER;						{number of kerning entries}
 END;

WidthTable = PACKED RECORD
 tabData: ARRAY [1..256] OF Fixed;		{character widths}
 tabFont: Handle;						{font record used to build table}
 sExtra: LONGINT;						{space extra used for table}
 style: LONGINT;						{extra due to style}
 fID: INTEGER;							{font family ID}
 fSize: INTEGER;						{font size request}
 face: INTEGER;							{style (face) request}
 device: INTEGER;						{device requested}
 inNumer: Point;						{scale factors requested}
 inDenom: Point;						{scale factors requested}
 aFID: INTEGER;							{actual font family ID for table}
 fHand: Handle;							{family record used to build up table}
 usedFam: BOOLEAN;						{used fixed point family widths}
 aFace: Byte;							{actual face produced}
 vOutput: INTEGER;						{vertical scale output value}
 hOutput: INTEGER;						{horizontal scale output value}
 vFactor: INTEGER;						{vertical scale output value}
 hFactor: INTEGER;						{horizontal scale output value}
 aSize: INTEGER;						{actual size of actual font used}
 tabSize: INTEGER;						{total size of table}
 END;

FamRec = RECORD
 ffFlags: INTEGER;						{flags for family}
 ffFamID: INTEGER;						{family ID number}
 ffFirstChar: INTEGER;					{ASCII code of 1st character}
 ffLastChar: INTEGER;					{ASCII code of last character}
 ffAscent: INTEGER;						{maximum ascent for 1pt font}
 ffDescent: INTEGER;					{maximum descent for 1pt font}
 ffLeading: INTEGER;					{maximum leading for 1pt font}
 ffWidMax: INTEGER;						{maximum widMax for 1pt font}
 ffWTabOff: LONGINT;					{offset to width table}
 ffKernOff: LONGINT;					{offset to kerning table}
 ffStylOff: LONGINT;					{offset to style mapping table}
 ffProperty: ARRAY [1..9] OF INTEGER;	{style property info}
 ffIntl: ARRAY [1..2] OF INTEGER;		{for international use}
 ffVersion: INTEGER;					{version number}
 END;


PROCEDURE InitFonts;
 INLINE $A8FE;
PROCEDURE GetFontName(familyID: INTEGER;VAR name: Str255);
 INLINE $A8FF;
PROCEDURE GetFNum(name: Str255;VAR familyID: INTEGER);
 INLINE $A900;
FUNCTION RealFont(fontNum: INTEGER;size: INTEGER): BOOLEAN;
 INLINE $A902;
PROCEDURE SetFontLock(lockFlag: BOOLEAN);
 INLINE $A903;
FUNCTION FMSwapFont(inRec: FMInput): FMOutPtr;
 INLINE $A901;
PROCEDURE SetFScaleDisable(fscaleDisable: BOOLEAN);
 INLINE $A834;
PROCEDURE FontMetrics(theMetrics: FMetricRec);
 INLINE $A835;
PROCEDURE SetFractEnable(fractEnable: BOOLEAN);
FUNCTION IsOutline(numer: Point;denom: Point): BOOLEAN;
 INLINE $7000,$A854;
PROCEDURE SetOutlinePreferred(outlinePreferred: BOOLEAN);
 INLINE $7001,$A854;
FUNCTION GetOutlinePreferred: BOOLEAN;
 INLINE $7009,$A854;
FUNCTION OutlineMetrics(byteCount: INTEGER;textPtr: UNIV Ptr;numer: Point;
 denom: Point;VAR yMax: INTEGER;VAR yMin: INTEGER;awArray: FixedPtr;lsbArray: FixedPtr;
 boundsArray: RectPtr): OSErr;
 INLINE $7008,$A854;
PROCEDURE SetPreserveGlyph(preserveGlyph: BOOLEAN);
 INLINE $700A,$A854;
FUNCTION GetPreserveGlyph: BOOLEAN;
 INLINE $700B,$A854;
FUNCTION FlushFonts: OSErr;
 INLINE $700C,$A854;

FUNCTION GetDefFontSize: INTEGER;
 INLINE $3EB8,$0BA8,$6604,$3EBC,$000C;
FUNCTION GetSysFont: INTEGER;
 INLINE $3EB8,$0BA6;
FUNCTION GetAppFont: INTEGER;
 INLINE $3EB8,$0984;


{$ENDC} { UsingFonts }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

