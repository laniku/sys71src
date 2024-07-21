
{
Created: Wednesday, July 31, 1991 at 7:56 AM
 Resources.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved


	Change History (most recent first):

		 <9>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do.
		 <8>	 4/21/92	DTY		#1018901,<gbm>: Add interface for GetNextFOND.
		 <7>	 7/31/91	JL		Updated Copyright.
		 <6>	 7/26/91	stb		use inlines for HOpenResFile and HCreateResFile when
									SystemSevenOrLater
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	 12/7/90	dba		<gbm> Add partial resource calls.

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Resources;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingResources}
{$SETC UsingResources := 1}

{$I+}
{$SETC ResourcesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := ResourcesIncludes}

CONST
resSysHeap = 64;	{System or application heap?}
resPurgeable = 32;	{Purgeable resource?}
resLocked = 16;		{Load it in locked?}
resProtected = 8;	{Protected?}
resPreload = 4;		{Load in on OpenResFile?}
resChanged = 2;		{Resource changed?}
mapReadOnly = 128;	{Resource file read-only}
mapCompact = 64;	{Compact resource file}
mapChanged = 32;	{Write map out at updat}

{ Values for setting RomMapInsert and TmpResLoad }
mapTrue = $FFFF;	{insert ROM map w/ TmpResLoad = TRUE.}
mapFalse = $FF00;	{insert ROM map w/ TmpResLoad = FALSE.}

FUNCTION InitResources: INTEGER;
 INLINE $A995;
PROCEDURE RsrcZoneInit;
 INLINE $A996;
PROCEDURE CloseResFile(refNum: INTEGER);
 INLINE $A99A;
FUNCTION ResError: INTEGER;
 INLINE $A9AF;
FUNCTION CurResFile: INTEGER;
 INLINE $A994;
FUNCTION HomeResFile(theResource: Handle): INTEGER;
 INLINE $A9A4;
PROCEDURE CreateResFile(fileName: Str255);
 INLINE $A9B1;
FUNCTION OpenResFile(fileName: Str255): INTEGER;
 INLINE $A997;
PROCEDURE UseResFile(refNum: INTEGER);
 INLINE $A998;
FUNCTION CountTypes: INTEGER;
 INLINE $A99E;
FUNCTION Count1Types: INTEGER;
 INLINE $A81C;
PROCEDURE GetIndType(VAR theType: ResType;index: INTEGER);
 INLINE $A99F;
PROCEDURE Get1IndType(VAR theType: ResType;index: INTEGER);
 INLINE $A80F;
PROCEDURE SetResLoad(load: BOOLEAN);
 INLINE $A99B;
FUNCTION CountResources(theType: ResType): INTEGER;
 INLINE $A99C;
FUNCTION Count1Resources(theType: ResType): INTEGER;
 INLINE $A80D;
FUNCTION GetIndResource(theType: ResType;index: INTEGER): Handle;
 INLINE $A99D;
FUNCTION Get1IndResource(theType: ResType;index: INTEGER): Handle;
 INLINE $A80E;
FUNCTION GetResource(theType: ResType;theID: INTEGER): Handle;
 INLINE $A9A0;
FUNCTION Get1Resource(theType: ResType;theID: INTEGER): Handle;
 INLINE $A81F;
FUNCTION GetNamedResource(theType: ResType;name: Str255): Handle;
 INLINE $A9A1;
FUNCTION Get1NamedResource(theType: ResType;name: Str255): Handle;
 INLINE $A820;
PROCEDURE LoadResource(theResource: Handle);
 INLINE $A9A2;
PROCEDURE ReleaseResource(theResource: Handle);
 INLINE $A9A3;
PROCEDURE DetachResource(theResource: Handle);
 INLINE $A992;
FUNCTION UniqueID(theType: ResType): INTEGER;
 INLINE $A9C1;
FUNCTION Unique1ID(theType: ResType): INTEGER;
 INLINE $A810;
FUNCTION GetResAttrs(theResource: Handle): INTEGER;
 INLINE $A9A6;
PROCEDURE GetResInfo(theResource: Handle;VAR theID: INTEGER;VAR theType: ResType;
 VAR name: Str255);
 INLINE $A9A8;
PROCEDURE SetResInfo(theResource: Handle;theID: INTEGER;name: Str255);
 INLINE $A9A9;
PROCEDURE AddResource(theResource: Handle;theType: ResType;theID: INTEGER;
 name: Str255);
 INLINE $A9AB;
FUNCTION SizeResource(theResource: Handle): LONGINT;
 INLINE $A9A5;
FUNCTION MaxSizeRsrc(theResource: Handle): LONGINT;
 INLINE $A821;
FUNCTION RsrcMapEntry(theResource: Handle): LONGINT;
 INLINE $A9C5;
PROCEDURE SetResAttrs(theResource: Handle;attrs: INTEGER);
 INLINE $A9A7;
PROCEDURE ChangedResource(theResource: Handle);
 INLINE $A9AA;
PROCEDURE RmveResource(theResource: Handle);
 INLINE $A9AD;
PROCEDURE UpdateResFile(refNum: INTEGER);
 INLINE $A999;
PROCEDURE WriteResource(theResource: Handle);
 INLINE $A9B0;
PROCEDURE SetResPurge(install: BOOLEAN);
 INLINE $A993;
FUNCTION GetResFileAttrs(refNum: INTEGER): INTEGER;
 INLINE $A9F6;
PROCEDURE SetResFileAttrs(refNum: INTEGER;attrs: INTEGER);
 INLINE $A9F7;
FUNCTION OpenRFPerm(fileName: Str255;vRefNum: INTEGER;permission: SignedByte): INTEGER;
 INLINE $A9C4;
FUNCTION RGetResource(theType: ResType;theID: INTEGER): Handle;
 INLINE $A80C;
FUNCTION HOpenResFile(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;
 permission: SignedByte): INTEGER;
{$IFC SystemSevenOrLater }
 INLINE $A81A;
{$ENDC}
PROCEDURE HCreateResFile(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255);
{$IFC SystemSevenOrLater }
 INLINE $A81B;
{$ENDC}

FUNCTION FSpOpenResFile(spec: FSSpec;permission: SignedByte): INTEGER;
 INLINE $303C,$000D,$AA52;
PROCEDURE FSpCreateResFile(spec: FSSpec;creator: OSType;fileType: OSType;
 scriptTag: ScriptCode);
 INLINE $303C,$000E,$AA52;

{  partial resource calls  }
PROCEDURE ReadPartialResource(theResource: Handle;offset: LONGINT;buffer: UNIV Ptr;
 count: LONGINT);
 INLINE $7001,$A822;
PROCEDURE WritePartialResource(theResource: Handle;offset: LONGINT;buffer: UNIV Ptr;
 count: LONGINT);
 INLINE $7002,$A822;
PROCEDURE SetResourceSize(theResource: Handle;newSize: LONGINT);
 INLINE $7003,$A822;
FUNCTION GetNextFOND(fondHandle: Handle): Handle;
 INLINE $700A,$A822;



{$ENDC} { UsingResources }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

