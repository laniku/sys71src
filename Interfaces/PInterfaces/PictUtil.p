
{
Created: Tuesday, July 23, 1991 at 2:54 PM
 PictUtil.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <5>	 7/23/91	JL		Checked in File from database. Adjusted comments. Reformatted
									structs to match output from database.
		 <4>	 1/16/91	JDR		(dba) Renamed METHOD_SYSTEM to systemMethod, METHOD_POPULAR to
									popularMethod, and METHOD_MEDIAN to medianMethod
		 <3>	 9/21/90	gbm		(Actually DDG) Updated selectors to work with ProcHelper.
		 <2>	 9/19/90	DDG		Fixed the header.
		 <1>	 9/19/90	DDG		first checked in

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT PictUtil;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPictUtil}
{$SETC UsingPictUtil := 1}

{$I+}
{$SETC PictUtilIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingPalettes}
{$I $$Shell(PInterfaces)Palettes.p}
{$ENDC}
{$SETC UsingIncludes := PictUtilIncludes}

CONST

{ verbs for the GetPictInfo, GetPixMapInfo, and NewPictInfo calls }
returnColorTable = 1;
returnPalette = 2;
recordComments = 4;
recordFontInfo = 8;
suppressBlackAndWhite = 16;

{ color pick methods }
systemMethod = 0;					{system color pick method}
popularMethod = 1;					{method that chooses the most popular set of colors}
medianMethod = 2;					{method that chooses a good average mix of colors}

{ color bank types }
ColorBankIsCustom = -1;
ColorBankIsExactAnd555 = 0;
ColorBankIs555 = 1;

TYPE
PictInfoID = LONGINT;

CommentSpecPtr = ^CommentSpec;
CommentSpecHandle = ^CommentSpecPtr;
CommentSpec = RECORD
 count: INTEGER;					{ number of occurrances of this comment ID }
 ID: INTEGER;						{ ID for the comment in the picture }
 END;

FontSpecPtr = ^FontSpec;
FontSpecHandle = ^FontSpecPtr;
FontSpec = RECORD
 pictFontID: INTEGER;				{ ID of the font in the picture }
 sysFontID: INTEGER;				{ ID of the same font in the current system file }
 size: ARRAY [0..3] OF LONGINT;		{ bit array of all the sizes found (1..127) (bit 0 means > 127) }
 style: INTEGER;					{ combined style of all occurrances of the font }
 nameOffset: LONGINT;				{ offset into the fontNamesHdl handle for the font’s name }
 END;

PictInfoPtr = ^PictInfo;
PictInfoHandle = ^PictInfoPtr;
PictInfo = RECORD
 version: INTEGER;					{ this is always zero, for now }
 uniqueColors: LONGINT;				{ the number of actual colors in the picture(s)/pixmap(s) }
 thePalette: PaletteHandle;			{ handle to the palette information }
 theColorTable: CTabHandle;			{ handle to the color table }
 hRes: Fixed;						{ maximum horizontal resolution for all the pixmaps }
 vRes: Fixed;						{ maximum vertical resolution for all the pixmaps }
 depth: INTEGER;					{ maximum depth for all the pixmaps (in the picture) }
 sourceRect: Rect;					{ the picture frame rectangle (this contains the entire picture) }
 textCount: LONGINT;				{ total number of text strings in the picture }
 lineCount: LONGINT;				{ total number of lines in the picture }
 rectCount: LONGINT;				{ total number of rectangles in the picture }
 rRectCount: LONGINT;				{ total number of round rectangles in the picture }
 ovalCount: LONGINT;				{ total number of ovals in the picture }
 arcCount: LONGINT;					{ total number of arcs in the picture }
 polyCount: LONGINT;				{ total number of polygons in the picture }
 regionCount: LONGINT;				{ total number of regions in the picture }
 bitMapCount: LONGINT;				{ total number of bitmaps in the picture }
 pixMapCount: LONGINT;				{ total number of pixmaps in the picture }
 commentCount: LONGINT;				{ total number of comments in the picture }
 uniqueComments: LONGINT;			{ the number of unique comments in the picture }
 commentHandle: CommentSpecHandle;	{ handle to all the comment information }
 uniqueFonts: LONGINT;				{ the number of unique fonts in the picture }
 fontHandle: FontSpecHandle;		{ handle to the FontSpec information }
 fontNamesHandle: Handle;			{ handle to the font names }
 reserved1: LONGINT;
 reserved2: LONGINT;
 END;


FUNCTION GetPictInfo(thePictHandle: PicHandle;
                     VAR thePictInfo: PictInfo;
                     verb: INTEGER;
                     colorsRequested: INTEGER;
                     colorPickMethod: INTEGER;
                     version: INTEGER): OSErr;
 INLINE $303C,$0800,$A831;
FUNCTION GetPixMapInfo(thePixMapHandle: PixMapHandle;
                       VAR thePictInfo: PictInfo;
                       verb: INTEGER;
                       colorsRequested: INTEGER;
                       colorPickMethod: INTEGER;
                       version: INTEGER): OSErr;
 INLINE $303C,$0801,$A831;
FUNCTION NewPictInfo(VAR thePictInfoID: PictInfoID;
                     verb: INTEGER;
                     colorsRequested: INTEGER;
                     colorPickMethod: INTEGER;
                     version: INTEGER): OSErr;
 INLINE $303C,$0602,$A831;
FUNCTION RecordPictInfo(thePictInfoID: PictInfoID;
                        thePictHandle: PicHandle): OSErr;
 INLINE $303C,$0403,$A831;
FUNCTION RecordPixMapInfo(thePictInfoID: PictInfoID;
                          thePixMapHandle: PixMapHandle): OSErr;
 INLINE $303C,$0404,$A831;
FUNCTION RetrievePictInfo(thePictInfoID: PictInfoID;
                          VAR thePictInfo: PictInfo;
                          colorsRequested: INTEGER): OSErr;
 INLINE $303C,$0505,$A831;
FUNCTION DisposPictInfo(thePictInfoID: PictInfoID): OSErr;
 INLINE $303C,$0206,$A831;


{$ENDC} { UsingPictUtil }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

