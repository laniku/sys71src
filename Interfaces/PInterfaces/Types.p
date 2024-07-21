
{
Created: Saturday, January 5, 1991 at 9:27 AM
 Types.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved.


	Change History (most recent first):

		<13>	  5/5/92	DCL		For New Inside Mac: Moved definition of STYLE to Types to break
									a circular dependancy. It won't work in QDText (the NIIM-correct
									place for it) Yuk. Someday we've got to find a better place.
		<12>	 2/17/92	MH		Corrected error in change history <11>
		<11>	 2/17/92	MH		Moved def of Extended80 here from SANE.p and expanded the
									defintion so that it is defined as extended when mc68881 is off.
									This type is now used in several different interface files where
									extended used to be used. The extended type varies with the
									setting of mc68881, but toolbox and os interactions must use an
									80 bit  rather than 96 bit type.
		<10>	 7/31/91	JL		Updated Copyright. Changed integer to INTEGER.
		<9>		 6/14/91	JL		Checked in official MPW 3.2Ä version. MacApp declares the types
									IntegerPtr and LongIntPtr so we put the conditional: "$IFC
									UNDEFINED qMacApp" around there declarations.
		 <8>	 1/27/91	LN		Checked in Database generate file from DSG. Reordered file.
		 <7>	  1/3/91	JDR		(dba) Adding Str32 type for AppleTalk.p
		 <6>	12/14/90	dba		<JDR> change OrBetter to OrLater; add Ptr types
		 <5>	11/13/90	PP		(PP/ngk) Added definition of symbols SystemSixOrBetter and
									SystemSevenOrBetter. Default initialization for both is false.
		 <4>	  7/2/90	PKE		Moved definition of LangCode here from Packages.p.
		 <3>	 5/29/90	ngk		Added definition of ScriptCode from Packages
		 <2>	 2/13/90			Official MPW version
		 <1>	12/17/89	CCH		Adding for the first time into BBS.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Types;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTypes}
{$SETC UsingTypes := 1}

{$IFC UNDEFINED SystemSevenOrLater}
{$SETC SystemSevenOrLater := FALSE}
{$ENDC}

{$IFC UNDEFINED SystemSixOrLater}
{$SETC SystemSixOrLater := SystemSevenOrLater}
{$ENDC}



CONST
noErr = 0;					{All is well}




TYPE
Byte = 0..255;				{ unsigned byte for fontmgr }
SignedByte = - 128..127;	{ any byte in memory }
Ptr = ^SignedByte;
Handle = ^Ptr;				{  pointer to a master pointer }

{$IFC UNDEFINED qMacApp}
IntegerPtr = ^INTEGER;
LongIntPtr = ^LONGINT;
{$ENDC}

Fixed = LONGINT;			{ fixed point arithmatic type }
FixedPtr = ^Fixed;
Fract = LONGINT;
FractPtr = ^Fract;
{$IFC OPTION(MC68881)}
Extended80 = ARRAY [0..4] OF INTEGER;
{$ELSEC}
Extended80 = EXTENDED;
{$ENDC}

VHSelect = (v,h);


ProcPtr = Ptr;				{ pointer to a procedure }

StringPtr = ^Str255;
StringHandle = ^StringPtr;

Str255 = String[255];		{ maximum string size }

Str63 = String[63];

Str32 = String[32];

Str31 = String[31];

Str27 = String[27];

Str15 = String[15];



OSErr = INTEGER;			{ error code }
OSType = PACKED ARRAY [1..4] OF CHAR;
OSTypePtr = ^OSType;
ResType = PACKED ARRAY [1..4] OF CHAR;
ResTypePtr = ^ResType;
ScriptCode = INTEGER;
LangCode = INTEGER;


PointPtr = ^Point;
Point = RECORD
 CASE INTEGER OF
   1:
  (v: INTEGER; 				{vertical coordinate}
  h: INTEGER); 				{horizontal coordinate}
   2:
  (vh: ARRAY[VHSelect] OF INTEGER);
 END;

RectPtr = ^Rect;
Rect = RECORD
 CASE INTEGER OF
   1:
  (top: INTEGER;
  left: INTEGER;
  bottom: INTEGER;
  right: INTEGER);
   2:
  (topLeft: Point;
  botRight: Point);
 END;

StyleItem = (bold,italic,underline,outline,shadow,condense,extend);

Style = SET OF StyleItem;



PROCEDURE Debugger;
 INLINE $A9FF;
PROCEDURE DebugStr(aStr: Str255);
 INLINE $ABFF;
PROCEDURE SysBreak;
 INLINE $303C,$FE16,$A9C9;
PROCEDURE SysBreakStr(debugStr: Str255);
 INLINE $303C,$FE15,$A9C9;
PROCEDURE SysBreakFunc(debugFunc: Str255);
 INLINE $303C,$FE14,$A9C9;


{$ENDC} { UsingTypes }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

