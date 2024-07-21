{
	File:		QuickdrawText.p
	 Pascal Interface to the Macintosh Libraries

	Copyright:	© 1983-1992 by Apple Computer, Inc.
	All rights reserved.

	Change History (most recent first):

		 <3>	  8/4/92	DCL		Changed the textLen parameter to textLength in the prototypes
									for PortionText, VisibleLength, PixelToChar & CharToPixel.
		 <2>	 5/29/92	DCL		Moved StdText from QuickDraw to QuickDrawText and fixed up some
									comments.
		 <1>	  5/5/92	DCL		first checked in

}



{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT QuickdrawText;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingQuickdrawText}
{$SETC UsingQuickdrawText := 1}

{$I+}
{$SETC QuickdrawTextIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingIntlResources}
{$I $$Shell(PInterfaces)IntlResources.p}
{$ENDC}
{$SETC UsingIncludes := QuickdrawTextIncludes}

CONST

{ CharToPixel directions }
leftCaret = 0;								{Place caret for left block}
rightCaret = -1;								{Place caret for right block}
hilite = 1;									{Direction is SysDirection}

smLeftCaret = 0;								{Place caret for left block        obsolete }
smRightCaret = -1;								{Place caret for right block    obsolete }
smHilite = 1;									{Direction is TESysJust            obsolete }

{Constants for styleRunPosition argument in PortionLine, DrawJustified,
 MeasureJustified, CharToPixel, and PixelToChar.}
onlyStyleRun = 0;								{ This is the only style run on the line }
leftStyleRun = 1;								{ This is leftmost of multiple style runs on the line }
rightStyleRun = 2;								{ This is rightmost of multiple style runs on the line }
middleStyleRun = 3;							{ There are multiple style runs on the line and this 
 is neither the leftmost nor the rightmost. }
smOnlyStyleRun = 0;								{      obsolete  }
smLeftStyleRun = 1;								{      obsolete  }
smRightStyleRun = 2;								{      obsolete  }
smMiddleStyleRun = 3;							{      obsolete  }

TYPE

{ type for styleRunPosition parameter in PixelToChar etc. }
JustStyleCode = INTEGER;

FontInfo = RECORD
 ascent: INTEGER;
 descent: INTEGER;
 widMax: INTEGER;
 leading: INTEGER;
 END;

FormatOrder = ARRAY [0..0] OF INTEGER;
FormatOrderPtr = ^FormatOrder;
FormatStatus = INTEGER;



FUNCTION Pixel2Char(textBuf: Ptr;textLen: INTEGER;slop: INTEGER;pixelWidth: INTEGER;
 VAR leadingEdge: BOOLEAN): INTEGER;
 INLINE $2F3C,$820E,$0014,$A8B5;
FUNCTION Char2Pixel(textBuf: Ptr;textLen: INTEGER;slop: INTEGER;offset: INTEGER;
 direction: INTEGER): INTEGER;
 INLINE $2F3C,$820C,$0016,$A8B5;
 
 {  New for 7.0  }
FUNCTION PixelToChar(textBuf: Ptr;textLength: LONGINT;slop: Fixed;pixelWidth: Fixed;
 VAR leadingEdge: BOOLEAN;VAR widthRemaining: Fixed;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point): INTEGER;
 INLINE $2F3C,$8222,$002E,$A8B5;
FUNCTION NPixel2Char(textBuf: Ptr;textLen: LONGINT;slop: Fixed;pixelWidth: Fixed;
 VAR leadingEdge: BOOLEAN;VAR widthRemaining: Fixed;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point): INTEGER;
 INLINE $2F3C,$8222,$002E,$A8B5;
FUNCTION CharToPixel(textBuf: Ptr;textLength: LONGINT;slop: Fixed;offset: LONGINT;
 direction: INTEGER;styleRunPosition: JustStyleCode;numer: Point;denom: Point): INTEGER;
 INLINE $2F3C,$821C,$0030,$A8B5;
FUNCTION NChar2Pixel(textBuf: Ptr;textLen: LONGINT;slop: Fixed;offset: LONGINT;
 direction: INTEGER;styleRunPosition: JustStyleCode;numer: Point;denom: Point): INTEGER;
 INLINE $2F3C,$821C,$0030,$A8B5;
PROCEDURE DrawJustified(textPtr: Ptr;textLength: LONGINT;slop: Fixed;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point);
 INLINE $2F3C,$8016,$0032,$A8B5;
PROCEDURE NDrawJust(textPtr: Ptr;textLength: LONGINT;slop: Fixed;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point);
 INLINE $2F3C,$8016,$0032,$A8B5;
PROCEDURE MeasureJustified(textPtr: Ptr;textLength: LONGINT;slop: Fixed;charLocs: Ptr;
 styleRunPosition: JustStyleCode;numer: Point;denom: Point);
 INLINE $2F3C,$801A,$0034,$A8B5;
PROCEDURE NMeasureJust(textPtr: Ptr;textLength: LONGINT;slop: Fixed;charLocs: Ptr;
 styleRunPosition: JustStyleCode;numer: Point;denom: Point);
 INLINE $2F3C,$801A,$0034,$A8B5;
FUNCTION NPortionText(textPtr: Ptr;textLen: LONGINT;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point): Fixed;
 INLINE $2F3C,$8412,$0036,$A8B5;
FUNCTION PortionLine(textPtr: Ptr;textLen: LONGINT;styleRunPosition: JustStyleCode;
 numer: Point;denom: Point): Fixed;
 INLINE $2F3C,$8412,$0036,$A8B5;

PROCEDURE HiliteText(textPtr: Ptr;textLength: INTEGER;firstOffset: INTEGER;
 secondOffset: INTEGER;VAR offsets: OffsetTable);
 INLINE $2F3C,$800E,$001C,$A8B5;
PROCEDURE DrawJust(textPtr: Ptr;textLength: INTEGER;slop: INTEGER);
 INLINE $2F3C,$8008,$001E,$A8B5;
PROCEDURE MeasureJust(textPtr: Ptr;textLength: INTEGER;slop: INTEGER;charLocs: Ptr);
 INLINE $2F3C,$800C,$0020,$A8B5;

FUNCTION PortionText(textPtr: Ptr;textLength: LONGINT): Fixed;
 INLINE $2F3C,$8408,$0024,$A8B5;
FUNCTION VisibleLength(textPtr: Ptr;textLength: LONGINT): LONGINT;
 INLINE $2F3C,$8408,$0028,$A8B5;
PROCEDURE GetFormatOrder(ordering: FormatOrderPtr;firstFormat: INTEGER;
 lastFormat: INTEGER;lineRight: BOOLEAN;rlDirProc: Ptr;dirParam: Ptr);
 INLINE $2F3C,$8012,$FFFC,$A8B5;


PROCEDURE TextFont(font: INTEGER);
 INLINE $A887;
PROCEDURE TextFace(face: Style);
 INLINE $A888;
PROCEDURE TextMode(mode: INTEGER);
 INLINE $A889;
PROCEDURE TextSize(size: INTEGER);
 INLINE $A88A;
PROCEDURE SpaceExtra(extra: Fixed);
 INLINE $A88E;
PROCEDURE DrawChar(ch: CHAR);
 INLINE $A883;
PROCEDURE DrawString(s: Str255);
 INLINE $A884;
PROCEDURE DrawText(textBuf: Ptr;firstByte: INTEGER;byteCount: INTEGER);
 INLINE $A885;
FUNCTION CharWidth(ch: CHAR): INTEGER;
 INLINE $A88D;
FUNCTION StringWidth(s: Str255): INTEGER;
 INLINE $A88C;
FUNCTION TextWidth(textBuf: Ptr;firstByte: INTEGER;byteCount: INTEGER): INTEGER;
 INLINE $A886;
PROCEDURE MeasureText(count: INTEGER;textAddr: Ptr;charLocs: Ptr);
 INLINE $A837;
PROCEDURE GetFontInfo(VAR info: FontInfo);
 INLINE $A88B;

PROCEDURE CharExtra(extra: Fixed);
 INLINE $AA23;
 
PROCEDURE StdText(count: INTEGER;textAddr: Ptr;numer: Point;denom: Point);
 INLINE $A882;
FUNCTION StdTxMeas(byteCount: INTEGER;textAddr: Ptr;VAR numer: Point;VAR denom: Point;
 VAR info: FontInfo): INTEGER;
 INLINE $A8ED;


{$ENDC} { UsingQuickdrawText }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

