
{
Created: Friday, September 15, 1989 at 5:01 PM
	SANE.p
	Pascal Interface to the Macintosh Libraries

	Copyright Apple Computer, Inc.	1985-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <3>	 2/17/92	MH		Move def on Extended80 to types.p, and include types.p
		 <2>	  8/8/91	JL		Updated Copyright.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT SANE;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSANE}
{$SETC UsingSANE := 1}

{$I+}
{$SETC SANEIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := SANEIncludes}

{ Elems881 mode set by -d Elems881=true on Pascal command line }

{$IFC UNDEFINED Elems881}
{$SETC Elems881 = FALSE}
{$ENDC}


CONST
{$IFC OPTION(MC68881)}

{*======================================================================*
 *	The interface specific to the MC68881 SANE library	*
 *======================================================================*}

Inexact = 8;
DivByZero = 16;
Underflow = 32;
Overflow = 64;
Invalid = 128;
CurInex1 = 256;
CurInex2 = 512;
CurDivByZero = 1024;
CurUnderflow = 2048;
CurOverflow = 4096;
CurOpError = 8192;
CurSigNaN = 16384;
CurBSonUnor = 32768;


{$ELSEC}

{*======================================================================*
 *	The interface specific to the software SANE library    *
 *======================================================================*}

Invalid = 1;
Underflow = 2;
Overflow = 4;
DivByZero = 8;
Inexact = 16;
IEEEDefaultEnv = 0; 	{IEEE-default floating-point environment constant}


{$ENDC}

{*======================================================================*
 *	The common interface for the SANE library	 *
 *======================================================================*}

DecStrLen = 255;
SigDigLen = 20; 		{for 68K; use 28 in 6502 SANE}


TYPE

RelOp = (GreaterThan,LessThan,EqualTo,Unordered);

NumClass = (SNaN,QNaN,Infinite,ZeroNum,NormalNum,DenormalNum);

RoundDir = (ToNearest,Upward,Downward,TowardZero);

RoundPre = (ExtPrecision,DblPrecision,RealPrecision);

DecimalKind = (FloatDecimal,FixedDecimal);

{$IFC OPTION(MC68881)}

{*======================================================================*
 *	The interface specific to the MC68881 SANE library	*
 *======================================================================*}
Exception = LONGINT;

Environment = RECORD
	FPCR: LONGINT;
	FPSR: LONGINT;
	END;

TrapVector = RECORD
	Unordered: LONGINT;
	Inexact: LONGINT;
	DivByZero: LONGINT;
	Underflow: LONGINT;
	OpError: LONGINT;
	Overflow: LONGINT;
	SigNaN: LONGINT;
	END;

{$ELSEC}

{*======================================================================*
*  The interface specific to the software SANE library	  *
*======================================================================*}

Exception = INTEGER;

Environment = INTEGER;

Extended96 = ARRAY [0..5] OF INTEGER;

MiscHaltInfo = RECORD
	HaltExceptions: INTEGER;
	PendingCCR: INTEGER;
	PendingD0: LONGINT;
	END;

{$ENDC}

{*======================================================================*
*  The common interface for the SANE library	*
*======================================================================*}

DecStr = STRING[DecStrLen];

DecForm = RECORD
	style: DecimalKind;
	digits: INTEGER;
	END;

Decimal = RECORD
	sgn: 0..1;
	exp: INTEGER;
	sig: STRING[SigDigLen];
	END;

CStrPtr = ^CHAR;



{$IFC OPTION(MC68881)}

{ return IEEE default environment }
FUNCTION IEEEDefaultEnv: environment;
PROCEDURE SetTrapVector(Traps: trapvector);
PROCEDURE GetTrapVector(VAR Traps: trapvector);
FUNCTION X96toX80(x: Extended): extended80;
FUNCTION X80toX96(x: extended80): Extended;
{$IFC Elems881 = false}

{ sine }FUNCTION Sin(x: Extended): Extended;
FUNCTION Cos(x: Extended): Extended;
FUNCTION ArcTan(x: Extended): Extended;
FUNCTION Exp(x: Extended): Extended;
FUNCTION Ln(x: Extended): Extended;
FUNCTION Log2(x: Extended): Extended;
FUNCTION Ln1(x: Extended): Extended;
FUNCTION Exp2(x: Extended): Extended;
FUNCTION Exp1(x: Extended): Extended;
FUNCTION Tan(x: Extended): Extended;
{$ENDC}

{$ELSEC}

{ return halt vector }FUNCTION GetHaltVector: LONGINT;
PROCEDURE SetHaltVector(v: LONGINT);
FUNCTION X96toX80(x: Extended96): Extended;
FUNCTION X80toX96(x: Extended): Extended96;
FUNCTION Log2(x: Extended): Extended;
FUNCTION Ln1(x: Extended): Extended;
FUNCTION Exp2(x: Extended): Extended;
FUNCTION Exp1(x: Extended): Extended;
FUNCTION Tan(x: Extended): Extended;
{$ENDC}


{*======================================================================*
*  The common interface for the SANE library	*
*======================================================================*}

{---------------------------------------------------
* Conversions between numeric binary types.
---------------------------------------------------}

FUNCTION Num2Integer(x: Extended): INTEGER;
FUNCTION Num2Longint(x: Extended): LONGINT;
FUNCTION Num2Real(x: Extended): real;
FUNCTION Num2Double(x: Extended): DOUBLE;
FUNCTION Num2Extended(x: Extended): Extended;
FUNCTION Num2Comp(x: Extended): Comp;
PROCEDURE Num2Dec(f: decform;x: Extended;VAR d: decimal);
FUNCTION Dec2Num(d: decimal): Extended;
PROCEDURE Num2Str(f: decform;x: Extended;VAR s: DecStr);
FUNCTION Str2Num(s: DecStr): Extended;
PROCEDURE Str2Dec(s: DecStr;VAR Index: INTEGER;VAR d: decimal;VAR ValidPrefix: BOOLEAN);
PROCEDURE CStr2Dec(s: CStrPtr;VAR Index: INTEGER;VAR d: decimal;VAR ValidPrefix: BOOLEAN);
PROCEDURE Dec2Str(f: decform;d: decimal;VAR s: DecStr);
FUNCTION Remainder(x: Extended;y: Extended;VAR quo: INTEGER): Extended;
FUNCTION Rint(x: Extended): Extended;
FUNCTION Scalb(n: INTEGER;x: Extended): Extended;
FUNCTION Logb(x: Extended): Extended;
FUNCTION CopySign(x: Extended;y: Extended): Extended;
FUNCTION NextReal(x: real;y: real): real;
FUNCTION NextDouble(x: DOUBLE;y: DOUBLE): DOUBLE;
FUNCTION NextExtended(x: Extended;y: Extended): Extended;
FUNCTION XpwrI(x: Extended;i: INTEGER): Extended;
FUNCTION XpwrY(x: Extended;y: Extended): Extended;
FUNCTION Compound(r: Extended;n: Extended): Extended;
FUNCTION Annuity(r: Extended;n: Extended): Extended;
FUNCTION RandomX(VAR x: Extended): Extended;
FUNCTION ClassReal(x: real): NumClass;
FUNCTION ClassDouble(x: DOUBLE): NumClass;
FUNCTION ClassComp(x: Comp): NumClass;
FUNCTION ClassExtended(x: Extended): NumClass;
FUNCTION SignNum(x: Extended): INTEGER;
FUNCTION NAN(i: INTEGER): Extended;
PROCEDURE SetException(e: Exception;b: BOOLEAN);
FUNCTION TestException(e: Exception): BOOLEAN;
PROCEDURE SetHalt(e: Exception;b: BOOLEAN);
FUNCTION TestHalt(e: Exception): BOOLEAN;
PROCEDURE SetRound(r: RoundDir);
FUNCTION GetRound: RoundDir;
PROCEDURE SetPrecision(p: RoundPre);
FUNCTION GetPrecision: RoundPre;
PROCEDURE SetEnvironment(e: environment);
PROCEDURE GetEnvironment(VAR e: environment);
PROCEDURE ProcEntry(VAR e: environment);
PROCEDURE ProcExit(e: environment);
FUNCTION Relation(x: Extended;y: Extended): RelOp;

{$ENDC}    { UsingSANE }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

