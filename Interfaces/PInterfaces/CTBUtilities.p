{************************************************************
	CTBUtilities.p
	Pascal Interface to the CommToolBox Utilities

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
		
	Change History (most recent first):

		<12>	 3/30/92	DTY		What’s Don up to now? 5 broken builds? Because Packages doesn’t
									include StandardFile any more, we need to do it ourselves to get
									DlgHookProcPtr.  Since this is the only thing that was needed
									out of Packages.p, nail Packages.p to keep build time to a
									minimum.
		<11>	 8/28/91	CH		Even more consistency changes.
		<10>	 8/28/91	CH		Updated interface headers for consistency.
		 <9>	  8/5/91	JL		Capatalized reserved word "ARRAY".
		 <8>	 7/25/91	JL		Checked in database generated file from DSG.
									Added NameFilterProcPtr, ZoneFilterProcPtr and DlgHookProcPtr to
									match C
									Used the ProcPtrs in the Function declaraions to match C.
									Used ModalFilterProcPtr and Included Dialogs to match C.
									Changed comments to match C.
		 <7>	 6/25/91	JNG		Move dialog manipulation routines into Dialogs.p
		 <6>	 3/13/91	JL		Added inclusion of Dialogs for the DialogPtr type.
		 <5>	 1/25/91	stb		JDR: remove records already defined in AppleTalk.p
		 <4>	 9/15/90	PWD		Added _StandardNBP in prep for renaming _NuLookup. <kaz> <crz>
		 <3>	 9/15/90	PWD		Moved popup constants to Controls.p.  <kaz> <crz>
		 <2>	 9/15/90	PWD		Renamed popupUseCQD to popupReserved. <kaz> <crz>
		 <1>	 3/14/90	BBH		first checked in

	To Do:
************************************************************}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT CTBUtilities;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingCTBUtilities}
{$SETC UsingCTBUtilities := 1}

{$I+}
{$SETC CTBUtilitiesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingStandardFile}
{$I $$Shell(PInterfaces)StandardFile.p}
{$ENDC}
{$IFC UNDEFINED UsingAppleTalk}
{$I $$Shell(PInterfaces)AppleTalk.p}
{$ENDC}
{$SETC UsingIncludes := CTBUtilitiesIncludes}

CONST

{ version of Comm Toolbox Utilities }
curCTBUVersion		= 2;

{    Error codes/types    }
ctbuGenericError	= -1;
ctbuNoErr			= 0;

TYPE
CTBUErr = OSErr;

CONST

{	Choose return codes}
chooseDisaster		= -2;
chooseFailed		= -1;
chooseAborted		=  0;
chooseOKMinor		=  1;
chooseOKMajor		=  2;
chooseCancel		=  3;

{	NuLookup return codes	}
nlOk				=	0;
nlCancel			=	1;
nlEject				=	2;

{	Name filter proc return codes	}
nameInclude			=	1;
nameDisable			=	2;
nameReject			=	3;

{	Zone filter proc return codes	}
zoneInclude			=	1;
zoneDisable			=	2;
zoneReject			=	3;

{    Values for hookProc items        }
hookOK				=	1;
hookCancel 			=	2;
hookOutline			=	3;
hookTitle			=	4;
hookItemList		=	5;
hookZoneTitle		=	6;
hookZoneList		=	7;
hookLine			=	8;
hookVersion			=	9;
hookReserved1		=	10;
hookReserved2 		=	11;
hookReserved3		=	12;
hookReserved4		=	13;

{    "virtual" hookProc items    }
hookNull			=	100;
hookItemRefresh		=	101;
hookZoneRefresh		=	102;
hookEject			=	103;
hookPreflight		=	104;
hookPostflight		=	105;
hookKeyBase			=	1000;

TYPE
{    NuLookup structures/constants    }
NLTypeEntry = RECORD
	hIcon: Handle;
	typeStr: Str32;
 END;


NLType 		= ARRAY [0..3] OF NLTypeEntry;

NBPReply = RECORD
	theEntity:	EntityName;
	theAddr:	AddrBlock;
 END;


NameFilterProcPtr = ProcPtr;
ZoneFilterProcPtr = ProcPtr;


FUNCTION	InitCTBUtilities: CTBUErr;
FUNCTION	CTBGetCTBVersion: INTEGER;


FUNCTION	StandardNBP(where: Point;prompt: Str255;numTypes: INTEGER;typeList: NLType;
				 nameFilter: NameFilterProcPtr;zoneFilter: ZoneFilterProcPtr;hookProc: DlgHookProcPtr;
				 VAR theReply: NBPReply): INTEGER;

FUNCTION	CustomNBP(where: Point;prompt: Str255;numTypes: INTEGER;typeList: NLType;
			   nameFilter: NameFilterProcPtr;zoneFilter: ZoneFilterProcPtr;hookProc: DlgHookProcPtr;
			   userData: LONGINT;dialogID: INTEGER;filterProc: ModalFilterProcPtr;VAR theReply: NBPReply): INTEGER;				   


{ Obsolete synonyms for above routines }
FUNCTION	NuLookup(where: Point;prompt: Str255;numTypes: INTEGER;typeList: NLType;
				 nameFilter: NameFilterProcPtr;zoneFilter: ZoneFilterProcPtr;hookProc: DlgHookProcPtr;
				 VAR theReply: NBPReply): INTEGER;

FUNCTION	NuPLookup(where: Point;prompt: Str255;numTypes: INTEGER;typeList: NLType;
			   nameFilter: NameFilterProcPtr;zoneFilter: ZoneFilterProcPtr;hookProc: DlgHookProcPtr;
			   userData: LONGINT;dialogID: INTEGER;filterProc: ModalFilterProcPtr;VAR theReply: NBPReply): INTEGER;
			   

{$ENDC}    { UsingCTBUtilities }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

