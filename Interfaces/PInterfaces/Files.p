
{
Created: Tuesday, July 30, 1991 at 4:00 PM
 Files.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: BigBang


	Change History (most recent first):

		<37>	11/19/91	JL		Changed lower case 'of' spelling to uppercase in FSSpecArray for
									consistency.
		<36>	 7/30/91	JL		Updated Copyright. Restored comments.
		<35>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Changed field comments in
									records: AFPVolMountInfo and VolMountInfoHeader to match C
									header. Also moved the Ptr declaration to those records to
									before the record declaration to match DSG Database output.
									Added comment on the constant, ioDirFlag, to match C header.
									Lost correct '91 copyright date but will restore it later. Added
									AppleShareMediaType constant to be consistent with C header.
		<34>	  2/5/91	dnf		stb, gs, Add VolMountInfoHeader.
		<33>	  2/4/91	JL		changed ioDirFlag back to 3. A BTST and a BitTst are different
									so the assembly and higher level languages have to be different.
									It's better to leave it the way it always has been.
		<32>	  2/1/91	stb		dnf,dnf003: change the inlines to set the HFS bit (10 in the
									trap word) for all HFS calls which have a dirID (CatSearch,
									Get|SetForeignPrivs).
		<31>	 1/28/91	LN		Checked in Database Generated File from DSG. changed SIGNEDBYTE
									to SignedByte in numerous places. Only built in types like
									INTEGER should be in all uppercase.anged file to match C header.
		<30>	 1/25/91	stb		JDR: add fsUnixPriv
		<29>	 1/23/91	stb		RC: harmonize with Files.h
		<28>	 1/18/91	stb		& dnf; add Get/SetForeignPrivs; add authentication constants;
									changed vMServerAdr to a Handle
		<27>	 1/10/91	PP		(ngk) Add VolumeMount header structure.
		<26>	  1/7/91	JDR		(dba) Adding routines PBGetVolMountInfoSize, PBGetVolMountInfo,
									and PBVolumeMount.
		<25>	  1/2/91	dba		(JDR) fix AllocContig trap word
		<24>	 12/6/90	JL		Fixed PBLockRange,PBUnlockRange,PBSetVInfo Sync and ASync inline
									code. Wasn't getting selector into A0 and was calling wrong trap
									numbers.
		<23>	 12/5/90	dba		<dnf> Fix inlines for PBOpenDFSync, PBOpenDFAsync,
									PBHOpenDFSync, and PBHOpenDFAsync. Add GetVolParmsInfoBuffer
									definition, definitions for desktop database icon types, and
									definitions for vMAttrib bits.
	  	<22>	10/30/90	dnf		(dnf/ngk) Move FSpCreateResFile and FSpOpenResFile header to appropriate
	   								resource header files.   Added OpenDF and HOpenDF high-level glue.
									Removed async parameter for DTGetPath, DTCloseDown and DTOpenInform.
									(dnf/th) Changed FXInfo and DXInfo to add fdXFlags/frXFlags fields.
		<21>	10/10/90	JL		Fixed Inline for QHdrs and uncommented PBCatSearch
		<20>	  10/8/90	JAL		Added Sync and Async calls to get around calling glue each time.
		<19>	  9/6/90	JNG		Change CHARS to SIGNEDBYTES
		<17>	  9/5/90	JNG		Update FXInfo and DXInfo
		<16>	 8/29/90	dnf		Add FSpExchangeFiles, Fix definition of FSpCreateResFile
		<15>	  8/6/90	dnf		Add inline dispatching for code FSp traps. Remove FSpGlue.
		<14>	  8/6/90	dnf		Add definitions for FSp traps
		<13>	  8/4/90	ngk		Change StringPtr to Str255 in FS routines.
		<12>	 6/20/90	ngk		Change FSSpec glue to not use pointers, since they are implicit
									in Pascal.
		<11>	  6/2/90	dnf		Correct length of priv array in CatPositionRec, add FSSpecPtr,
									add definitions for FSP glue.
		<10>	  5/4/90	dnf		Add MakeFSSpec function definition
		 <9>	 4/25/90	dnf		Fix DTPBRec
		 <8>	 4/13/90	dnf		Add ioAPPLParID, ioDTLgLen and ioDTPyLen to DTParam.  Move it
									out of HParamBlockRec (since it's now too big) and rename it
									(since there's a different convention for things that aren't in
									HParamBlockRec).
		 <7>	 3/16/90	dnf		Added FSSpec record and AltAccessParam. Changed DT call names to
									match latest from traps.a. Added OpenDF/HOpenDF and
									Get/SetAltAccess. Removed obsolete call names again and also
									removed non-existant high-level FileOpen calls.
		 <6>	 3/02/90	JAL		Put PBH calls back for compatibility.
		 <5>	 2/25/90	dnf		Fix CatSearch and Desktop manager param blocks. Remove obsolete
									call names. Add SpecBits constants.
** 1.2	ngk 11/11/1989 	Added Desktop manger calls
** 1.1	EKN 07/31/1989 Added FIDParam and FileIDs calls.
** 1.0	CCH 11/17/1988 Adding to EASE.
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Files;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFiles}
{$SETC UsingFiles := 1}

{$I+}
{$SETC FilesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingSegLoad}
{$I $$Shell(PInterfaces)SegLoad.p}
{$ENDC}
{$SETC UsingIncludes := FilesIncludes}

CONST

{ Finder Constants }
fsAtMark = 0;
fOnDesk = 1;
fsCurPerm = 0;
fHasBundle = 8192;
fsRdPerm = 1;
fInvisible = 16384;
fTrash = -3;
fsWrPerm = 2;
fDesktop = -2;
fsRdWrPerm = 3;
fDisk = 0;
fsRdWrShPerm = 4;
fsFromStart = 1;
fsFromLEOF = 2;
fsFromMark = 3;
rdVerify = 64;
ioDirFlg = 3;								{ see IM IV-125 }
ioDirMask = $10;
fsRtParID = 1;
fsRtDirID = 2;

{ CatSearch SearchBits Constants }
fsSBPartialName = 1;
fsSBFullName = 2;
fsSBFlAttrib = 4;
fsSBFlFndrInfo = 8;
fsSBFlLgLen = 32;
fsSBFlPyLen = 64;
fsSBFlRLgLen = 128;
fsSBFlRPyLen = 256;
fsSBFlCrDat = 512;
fsSBFlMdDat = 1024;
fsSBFlBkDat = 2048;
fsSBFlXFndrInfo = 4096;
fsSBFlParID = 8192;
fsSBNegate = 16384;
fsSBDrUsrWds = 8;
fsSBDrNmFls = 16;
fsSBDrCrDat = 512;
fsSBDrMdDat = 1024;
fsSBDrBkDat = 2048;
fsSBDrFndrInfo = 4096;
fsSBDrParID = 8192;

{ vMAttrib (GetVolParms) bit position constants }
bLimitFCBs = 31;
bLocalWList = 30;
bNoMiniFndr = 29;
bNoVNEdit = 28;
bNoLclSync = 27;
bTrshOffLine = 26;
bNoSwitchTo = 25;
bNoDeskItems = 20;
bNoBootBlks = 19;
bAccessCntl = 18;
bNoSysDir = 17;
bHasExtFSVol = 16;
bHasOpenDeny = 15;
bHasCopyFile = 14;
bHasMoveRename = 13;
bHasDesktopMgr = 12;
bHasShortName = 11;
bHasFolderLock = 10;
bHasPersonalAccessPrivileges = 9;
bHasUserGroupList = 8;
bHasCatSearch = 7;
bHasFileIDs = 6;
bHasBTreeMgr = 5;
bHasBlankAccessPrivileges = 4;

{ Desktop Database icon Constants }
kLargeIcon = 1;
kLarge4BitIcon = 2;
kLarge8BitIcon = 3;
kSmallIcon = 4;
kSmall4BitIcon = 5;
kSmall8BitIcon = 6;

kLargeIconSize = 256;
kLarge4BitIconSize = 512;
kLarge8BitIconSize = 1024;
kSmallIconSize = 64;
kSmall4BitIconSize = 128;
kSmall8BitIconSize = 256;

{ Foreign Privilege Model Identifiers }
fsUnixPriv = 1;

{ Version Release Stage Codes }
developStage = $20;
alphaStage = $40;
betaStage = $60;
finalStage = $80;

{ Authentication Constants }
kNoUserAuthentication = 1;
kPassword = 2;
kEncryptPassword = 3;
kTwoWayEncryptPassword = 6;

TYPE
CInfoType = (hFileInfo,dirInfo);


FXInfo = RECORD
 fdIconID: INTEGER;							{Icon ID}
 fdUnused: ARRAY [1..3] OF INTEGER;			{unused but reserved 6 bytes}
 fdScript: SignedByte;						{Script flag and number}
 fdXFlags: SignedByte;						{More flag bits}
 fdComment: INTEGER;						{Comment ID}
 fdPutAway: LONGINT;						{Home Dir ID}
 END;

DInfo = RECORD
 frRect: Rect;								{folder rect}
 frFlags: INTEGER;							{Flags}
 frLocation: Point;							{folder location}
 frView: INTEGER;							{folder view}
 END;

DXInfo = RECORD
 frScroll: Point;							{scroll position}
 frOpenChain: LONGINT;						{DirID chain of open folders}
 frScript: SignedByte;						{Script flag and number}
 frXFlags: SignedByte;						{More flag bits}
 frComment: INTEGER;						{comment}
 frPutAway: LONGINT;						{DirID}
 END;

GetVolParmsInfoBuffer = RECORD
 vMVersion: INTEGER;						{version number}
 vMAttrib: LONGINT;							{bit vector of attributes (see vMAttrib constants)}
 vMLocalHand: Handle;						{handle to private data}
 vMServerAdr: LONGINT;						{AppleTalk server address or zero}
 vMVolumeGrade: LONGINT;					{approx. speed rating or zero if unrated}
 vMForeignPrivID: INTEGER;					{foreign privilege model supported or zero if none}
 END;

CInfoPBPtr = ^CInfoPBRec;
CInfoPBRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 ioFRefNum: INTEGER;
 ioFVersNum: SignedByte;
 filler1: SignedByte;
 ioFDirIndex: INTEGER;
 ioFlAttrib: SignedByte;
 filler2: SignedByte;
 CASE CInfoType OF
   hFileInfo:
  (ioFlFndrInfo: FInfo;
  ioDirID: LONGINT;
  ioFlStBlk: INTEGER;
  ioFlLgLen: LONGINT;
  ioFlPyLen: LONGINT;
  ioFlRStBlk: INTEGER;
  ioFlRLgLen: LONGINT;
  ioFlRPyLen: LONGINT;
  ioFlCrDat: LONGINT;
  ioFlMdDat: LONGINT;
  ioFlBkDat: LONGINT;
  ioFlXFndrInfo: FXInfo;
  ioFlParID: LONGINT;
  ioFlClpSiz: LONGINT);
   dirInfo:
  (ioDrUsrWds: DInfo;
  ioDrDirID: LONGINT;
  ioDrNmFls: INTEGER;
  filler3: ARRAY [1..9] OF INTEGER;
  ioDrCrDat: LONGINT;
  ioDrMdDat: LONGINT;
  ioDrBkDat: LONGINT;
  ioDrFndrInfo: DXInfo;
  ioDrParID: LONGINT);
 END;

{ Catalog position record }
CatPositionRec = RECORD
 initialize: LONGINT;
 priv: ARRAY [1..6] OF INTEGER;
 END;

FSSpecPtr = ^FSSpec;
FSSpecHandle = ^FSSpecPtr;
FSSpec = RECORD
 vRefNum: INTEGER;
 parID: LONGINT;
 name: Str63;
 END;

FSSpecArrayPtr = ^FSSpecArray;
FSSpecArrayHandle = ^FSSpecArrayPtr;

FSSpecArray = ARRAY [0..0] OF FSSpec;


{ The following are structures to be filled out with the _GetVolMountInfo call
 and passed back into the _VolumeMount call for external file system mounts. }

VolumeType = OSType;						{ the "signature" of the file system }

CONST
AppleShareMediaType = 'afpm';				{ the signature for AppleShare }

TYPE
VolMountInfoPtr = ^VolMountInfoHeader;
VolMountInfoHeader = RECORD
 length: INTEGER;							{ length of location data (including self) }
 media: VolumeType;							{ type of media.  Variable length data follows }
 END;

AFPVolMountInfoPtr = ^AFPVolMountInfo;
AFPVolMountInfo = RECORD
 length: INTEGER;							{ length of location data (including self) }
 media: VolumeType;							{ type of media }
 flags: INTEGER;							{ bits for no messages, no reconnect }
 nbpInterval: SignedByte;					{ NBP Interval parameter (IM2, p.322) }
 nbpCount: SignedByte;						{ NBP Interval parameter (IM2, p.322) }
 uamType: INTEGER;							{ User Authentication Method }
 zoneNameOffset: INTEGER;					{ short positive offset from start of struct to Zone Name }
 serverNameOffset: INTEGER;					{ offset to pascal Server Name string }
 volNameOffset: INTEGER;					{ offset to pascal Volume Name string }
 userNameOffset: INTEGER;					{ offset to pascal User Name string }
 userPasswordOffset: INTEGER;				{ offset to pascal User Password string }
 volPasswordOffset: INTEGER;				{ offset to pascal Volume Password string }
 AFPData: PACKED ARRAY [1..144] OF CHAR;	{ variable length data may follow }
 END;

DTPBPtr = ^DTPBRec;
DTPBRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 ioDTRefNum: INTEGER;
 ioIndex: INTEGER;
 ioTagInfo: LONGINT;
 ioDTBuffer: Ptr;
 ioDTReqCount: LONGINT;
 ioDTActCount: LONGINT;
 filler1: SignedByte;
 ioIconType: SignedByte;
 filler2: INTEGER;
 ioDirID: LONGINT;
 ioFileCreator: OSType;
 ioFileType: OSType;
 ioFiller3: LONGINT;
 ioDTLgLen: LONGINT;
 ioDTPyLen: LONGINT;
 ioFiller4: ARRAY [1..14] OF INTEGER;
 ioAPPLParID: LONGINT;
 END;

HParmBlkPtr = ^HParamBlockRec;
HParamBlockRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 CASE ParamBlkType OF
   IOParam:
  (ioRefNum: INTEGER;
  ioVersNum: SignedByte;
  ioPermssn: SignedByte;
  ioMisc: Ptr;
  ioBuffer: Ptr;
  ioReqCount: LONGINT;						{size of buffer area}
  ioActCount: LONGINT;						{length of vol parms data}
  ioPosMode: INTEGER;
  ioPosOffset: LONGINT);
   FileParam:
  (ioFRefNum: INTEGER;
  ioFVersNum: SignedByte;
  filler1: SignedByte;
  ioFDirIndex: INTEGER;
  ioFlAttrib: SignedByte;
  ioFlVersNum: SignedByte;
  ioFlFndrInfo: FInfo;
  ioDirID: LONGINT;
  ioFlStBlk: INTEGER;
  ioFlLgLen: LONGINT;
  ioFlPyLen: LONGINT;
  ioFlRStBlk: INTEGER;
  ioFlRLgLen: LONGINT;
  ioFlRPyLen: LONGINT;
  ioFlCrDat: LONGINT;
  ioFlMdDat: LONGINT);
   VolumeParam:
  (filler2: LONGINT;
  ioVolIndex: INTEGER;
  ioVCrDate: LONGINT;
  ioVLsMod: LONGINT;
  ioVAtrb: INTEGER;
  ioVNmFls: INTEGER;
  ioVBitMap: INTEGER;
  ioAllocPtr: INTEGER;
  ioVNmAlBlks: INTEGER;
  ioVAlBlkSiz: LONGINT;
  ioVClpSiz: LONGINT;
  ioAlBlSt: INTEGER;
  ioVNxtCNID: LONGINT;
  ioVFrBlk: INTEGER;
  ioVSigWord: INTEGER;
  ioVDrvInfo: INTEGER;
  ioVDRefNum: INTEGER;
  ioVFSID: INTEGER;
  ioVBkUp: LONGINT;
  ioVSeqNum: INTEGER;
  ioVWrCnt: LONGINT;
  ioVFilCnt: LONGINT;
  ioVDirCnt: LONGINT;
  ioVFndrInfo: ARRAY [1..8] OF LONGINT);
   AccessParam:
  (filler3: INTEGER;
  ioDenyModes: INTEGER;						{access rights data}
  filler4: INTEGER;
  filler5: SignedByte;
  ioACUser: SignedByte;						{access rights for directory only}
  filler6: LONGINT;
  ioACOwnerID: LONGINT;						{owner ID}
  ioACGroupID: LONGINT;						{group ID}
  ioACAccess: LONGINT);						{access rights}
   ObjParam:
  (filler7: INTEGER;
  ioObjType: INTEGER;						{function code}
  ioObjNamePtr: Ptr;						{ptr to returned creator/group name}
  ioObjID: LONGINT);						{creator/group ID}
   CopyParam:
  (ioDstVRefNum: INTEGER;					{destination vol identifier}
  filler8: INTEGER;
  ioNewName: Ptr;							{ptr to destination pathname}
  ioCopyName: Ptr;							{ptr to optional name}
  ioNewDirID: LONGINT);						{destination directory ID}
   WDParam:
  (filler9: INTEGER;
  ioWDIndex: INTEGER;
  ioWDProcID: LONGINT;
  ioWDVRefNum: INTEGER;
  filler10: INTEGER;
  filler11: LONGINT;
  filler12: LONGINT;
  filler13: LONGINT;
  ioWDDirID: LONGINT);
   FIDParam:
  (filler14: LONGINT;
  ioDestNamePtr: StringPtr;
  filler15: LONGINT;
  ioDestDirID: LONGINT;
  filler16: LONGINT;
  filler17: LONGINT;
  ioSrcDirID: LONGINT;
  filler18:  INTEGER;
  ioFileID:  LONGINT);
   CSParam:
  (ioMatchPtr: FSSpecArrayPtr;				{match array}
  ioReqMatchCount: LONGINT; 				{maximum allowable matches}
  ioActMatchCount: LONGINT; 				{actual match count}
  ioSearchBits: LONGINT;   					{search criteria selector}
  ioSearchInfo1: CInfoPBPtr; 				{search values and range lower bounds}
  ioSearchInfo2: CInfoPBPtr; 				{search values and range upper bounds}
  ioSearchTime: LONGINT;  					{length of time to run the search}
  ioCatPosition: CatPositionRec; 			{current position in the catalog}
  ioOptBuffer: Ptr;   						{optional performance enhancement buffer}
  ioOptBufSize: LONGINT);  					{length of buffer pointed to by ioOptBuffer}
   ForeignPrivParam:
    (filler21: LONGINT;
  filler22: LONGINT;
  ioForeignPrivBuffer: Ptr;
  ioForeignPrivReqCount: LONGINT;
  ioForeignPrivActCount: LONGINT;
  filler23: LONGINT;
  ioForeignPrivDirID: LONGINT;
  ioForeignPrivInfo1: LONGINT;
  ioForeignPrivInfo2: LONGINT;
  ioForeignPrivInfo3: LONGINT;
  ioForeignPrivInfo4: LONGINT);
 END;

CMovePBPtr = ^CMovePBRec;
CMovePBRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 filler1: LONGINT;
 ioNewName: StringPtr;
 filler2: LONGINT;
 ioNewDirID: LONGINT;
 filler3: ARRAY [1..2] OF LONGINT;
 ioDirID: LONGINT;
 END;

WDPBPtr = ^WDPBRec;
WDPBRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 filler1: INTEGER;
 ioWDIndex: INTEGER;
 ioWDProcID: LONGINT;
 ioWDVRefNum: INTEGER;
 filler2: ARRAY [1..7] OF INTEGER;
 ioWDDirID: LONGINT;
 END;

FCBPBPtr = ^FCBPBRec;
FCBPBRec = RECORD
 qLink: QElemPtr;
 qType: INTEGER;
 ioTrap: INTEGER;
 ioCmdAddr: Ptr;
 ioCompletion: ProcPtr;
 ioResult: OSErr;
 ioNamePtr: StringPtr;
 ioVRefNum: INTEGER;
 ioRefNum: INTEGER;
 filler: INTEGER;
 ioFCBIndx: INTEGER;
 filler1: INTEGER;
 ioFCBFlNm: LONGINT;
 ioFCBFlags: INTEGER;
 ioFCBStBlk: INTEGER;
 ioFCBEOF: LONGINT;
 ioFCBPLen: LONGINT;
 ioFCBCrPs: LONGINT;
 ioFCBVRefNum: INTEGER;
 ioFCBClpSiz: LONGINT;
 ioFCBParID: LONGINT;
 END;

{ Numeric version part of 'vers' resource }
NumVersion = PACKED RECORD
 CASE INTEGER OF
   0:
  (majorRev: SignedByte;					{1st part of version number in BCD}
  minorRev: 0..9;							{2nd part is 1 nibble in BCD}
  bugFixRev: 0..9;							{3rd part is 1 nibble in BCD}
  stage: SignedByte;						{stage code: dev, alpha, beta, final}
  nonRelRev: SignedByte);					{revision level of non-released version}
   1:
  (version: LONGINT);						{to use all 4 fields at one time}
 END;

{ 'vers' resource format }
VersRecPtr = ^VersRec;
VersRecHndl = ^VersRecPtr;
VersRec = RECORD
 numericVersion: NumVersion;				{encoded version number}
 countryCode: INTEGER;						{country code from intl utilities}
 shortVersion: Str255;						{version number string - worst case}
 reserved: Str255;							{longMessage string packed after shortVersion}
 END;


FUNCTION PBOpen(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBOpenSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A000,$3E80;
FUNCTION PBOpenAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A400,$3E80;
FUNCTION PBClose(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBCloseSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A001,$3E80;
FUNCTION PBCloseAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A401,$3E80;
FUNCTION PBRead(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBReadSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A002,$3E80;
FUNCTION PBReadAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A402,$3E80;
FUNCTION PBWrite(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBWriteSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A003,$3E80;
FUNCTION PBWriteAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A403,$3E80;
FUNCTION PBGetVInfo(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetVInfoSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A007,$3E80;
FUNCTION PBGetVInfoAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A407,$3E80;
FUNCTION PBGetVol(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetVolSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A014,$3E80;
FUNCTION PBGetVolAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A414,$3E80;
FUNCTION PBSetVol(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetVolSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A015,$3E80;
FUNCTION PBSetVolAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A415,$3E80;
FUNCTION PBFlushVol(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBFlushVolSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A013,$3E80;
FUNCTION PBFlushVolAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A413,$3E80;
FUNCTION PBCreate(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBCreateSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A008,$3E80;
FUNCTION PBCreateAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A408,$3E80;
FUNCTION PBDelete(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBDeleteSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A009,$3E80;
FUNCTION PBDeleteAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A409,$3E80;
FUNCTION PBOpenDF(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBOpenDFSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$701A,$A060,$3E80;
FUNCTION PBOpenDFAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$701A,$A460,$3E80;
FUNCTION PBOpenRF(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBOpenRFSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A00A,$3E80;
FUNCTION PBOpenRFAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A40A,$3E80;
FUNCTION PBRename(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBRenameSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A00B,$3E80;
FUNCTION PBRenameAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A40B,$3E80;
FUNCTION PBGetFInfo(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetFInfoSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A00C,$3E80;
FUNCTION PBGetFInfoAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A40C,$3E80;
FUNCTION PBSetFInfo(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetFInfoSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A00D,$3E80;
FUNCTION PBSetFInfoAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A40D,$3E80;
FUNCTION PBSetFLock(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetFLockSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A041,$3E80;
FUNCTION PBSetFLockAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A441,$3E80;
FUNCTION PBRstFLock(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBRstFLockSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A042,$3E80;
FUNCTION PBRstFLockAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A442,$3E80;
FUNCTION PBSetFVers(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetFVersSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A043,$3E80;
FUNCTION PBSetFVersAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A443,$3E80;
FUNCTION PBAllocate(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBAllocateSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A010,$3E80;
FUNCTION PBAllocateAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A410,$3E80;
FUNCTION PBGetEOF(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetEOFSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A011,$3E80;
FUNCTION PBGetEOFAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A411,$3E80;
FUNCTION PBSetEOF(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetEOFSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A012,$3E80;
FUNCTION PBSetEOFAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A412,$3E80;
FUNCTION PBGetFPos(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetFPosSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A018,$3E80;
FUNCTION PBGetFPosAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A418,$3E80;
FUNCTION PBSetFPos(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetFPosSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A044,$3E80;
FUNCTION PBSetFPosAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A444,$3E80;
FUNCTION PBFlushFile(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBFlushFileSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A045,$3E80;
FUNCTION PBFlushFileAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A445,$3E80;
FUNCTION PBMountVol(paramBlock: ParmBlkPtr): OSErr;
FUNCTION PBUnmountVol(paramBlock: ParmBlkPtr): OSErr;
FUNCTION PBEject(paramBlock: ParmBlkPtr): OSErr;
FUNCTION PBOffLine(paramBlock: ParmBlkPtr): OSErr;

FUNCTION PBCatSearch(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBCatSearchSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7018,$A260,$3E80;
FUNCTION PBCatSearchAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7018,$A660,$3E80;

PROCEDURE AddDrive(drvrRefNum: INTEGER;drvNum: INTEGER;qEl: DrvQElPtr);
FUNCTION FSOpen(fileName: Str255;vRefNum: INTEGER;VAR refNum: INTEGER): OSErr;
FUNCTION OpenDF(fileName: Str255;vRefNum: INTEGER;VAR refNum: INTEGER): OSErr;
FUNCTION FSClose(refNum: INTEGER): OSErr;
FUNCTION FSRead(refNum: INTEGER;VAR count: LONGINT;buffPtr: Ptr): OSErr;
FUNCTION FSWrite(refNum: INTEGER;VAR count: LONGINT;buffPtr: Ptr): OSErr;
FUNCTION GetVInfo(drvNum: INTEGER;volName: StringPtr;VAR vRefNum: INTEGER;
 VAR freeBytes: LONGINT): OSErr;
FUNCTION GetFInfo(fileName: Str255;vRefNum: INTEGER;VAR fndrInfo: FInfo): OSErr;
FUNCTION GetVol(volName: StringPtr;VAR vRefNum: INTEGER): OSErr;
FUNCTION SetVol(volName: StringPtr;vRefNum: INTEGER): OSErr;
FUNCTION UnmountVol(volName: StringPtr;vRefNum: INTEGER): OSErr;
FUNCTION Eject(volName: StringPtr;vRefNum: INTEGER): OSErr;
FUNCTION FlushVol(volName: StringPtr;vRefNum: INTEGER): OSErr;
FUNCTION Create(fileName: Str255;vRefNum: INTEGER;creator: OSType;fileType: OSType): OSErr;
FUNCTION FSDelete(fileName: Str255;vRefNum: INTEGER): OSErr;
FUNCTION OpenRF(fileName: Str255;vRefNum: INTEGER;VAR refNum: INTEGER): OSErr;
FUNCTION Rename(oldName: Str255;vRefNum: INTEGER;newName: Str255): OSErr;
FUNCTION SetFInfo(fileName: Str255;vRefNum: INTEGER;fndrInfo: FInfo): OSErr;
FUNCTION SetFLock(fileName: Str255;vRefNum: INTEGER): OSErr;
FUNCTION RstFLock(fileName: Str255;vRefNum: INTEGER): OSErr;
FUNCTION Allocate(refNum: INTEGER;VAR count: LONGINT): OSErr;
FUNCTION GetEOF(refNum: INTEGER;VAR logEOF: LONGINT): OSErr;
FUNCTION SetEOF(refNum: INTEGER;logEOF: LONGINT): OSErr;
FUNCTION GetFPos(refNum: INTEGER;VAR filePos: LONGINT): OSErr;
FUNCTION SetFPos(refNum: INTEGER;posMode: INTEGER;posOff: LONGINT): OSErr;
FUNCTION GetVRefNum(fileRefNum: INTEGER;VAR vRefNum: INTEGER): OSErr;

FUNCTION PBOpenWD(paramBlock: WDPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBOpenWDSync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7001,$A260,$3E80;
FUNCTION PBOpenWDAsync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7001,$A660,$3E80;
FUNCTION PBCloseWD(paramBlock: WDPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBCloseWDSync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7002,$A260,$3E80;
FUNCTION PBCloseWDAsync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7002,$A660,$3E80;
FUNCTION PBHSetVol(paramBlock: WDPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBHSetVolSync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$A215,$3E80;
FUNCTION PBHSetVolAsync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$A615,$3E80;
FUNCTION PBHGetVol(paramBlock: WDPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetVolSync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$A214,$3E80;
FUNCTION PBHGetVolAsync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$A614,$3E80;
FUNCTION PBCatMove(paramBlock: CMovePBPtr;async: BOOLEAN): OSErr;
FUNCTION PBCatMoveSync(paramBlock: CMovePBPtr): OSErr;
 INLINE $205F,$7005,$A260,$3E80;
FUNCTION PBCatMoveAsync(paramBlock: CMovePBPtr): OSErr;
 INLINE $205F,$7005,$A660,$3E80;
FUNCTION PBDirCreate(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBDirCreateSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7006,$A260,$3E80;
FUNCTION PBDirCreateAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7006,$A660,$3E80;
FUNCTION PBGetWDInfo(paramBlock: WDPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetWDInfoSync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7007,$A260,$3E80;
FUNCTION PBGetWDInfoAsync(paramBlock: WDPBPtr): OSErr;
 INLINE $205F,$7007,$A660,$3E80;
FUNCTION PBGetFCBInfo(paramBlock: FCBPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetFCBInfoSync(paramBlock: FCBPBPtr): OSErr;
 INLINE $205F,$7008,$A260,$3E80;
FUNCTION PBGetFCBInfoAsync(paramBlock: FCBPBPtr): OSErr;
 INLINE $205F,$7008,$A660,$3E80;
FUNCTION PBGetCatInfo(paramBlock: CInfoPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetCatInfoSync(paramBlock: CInfoPBPtr): OSErr;
 INLINE $205F,$7009,$A260,$3E80;
FUNCTION PBGetCatInfoAsync(paramBlock: CInfoPBPtr): OSErr;
 INLINE $205F,$7009,$A660,$3E80;
FUNCTION PBSetCatInfo(paramBlock: CInfoPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetCatInfoSync(paramBlock: CInfoPBPtr): OSErr;
 INLINE $205F,$700A,$A260,$3E80;
FUNCTION PBSetCatInfoAsync(paramBlock: CInfoPBPtr): OSErr;
 INLINE $205F,$700A,$A660,$3E80;

FUNCTION PBAllocContig(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBAllocContigSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A210,$3E80;
FUNCTION PBAllocContigAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$A610,$3E80;
FUNCTION PBLockRange(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBLockRangeSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7010,$A260,$3E80;
FUNCTION PBLockRangeAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7010,$A660,$3E80;
FUNCTION PBUnlockRange(paramBlock: ParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBUnlockRangeSync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7011,$A260,$3E80;
FUNCTION PBUnlockRangeAsync(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7011,$A660,$3E80;
FUNCTION PBSetVInfo(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetVInfoSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$700B,$A260,$3E80;
FUNCTION PBSetVInfoAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$700B,$A660,$3E80;
FUNCTION PBHGetVInfo(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetVInfoSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A207,$3E80;
FUNCTION PBHGetVInfoAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A607,$3E80;
FUNCTION PBHOpen(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHOpenSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A200,$3E80;
FUNCTION PBHOpenAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A600,$3E80;
FUNCTION PBHOpenRF(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHOpenRFSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A20A,$3E80;
FUNCTION PBHOpenRFAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A60A,$3E80;
FUNCTION PBHOpenDF(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHOpenDFSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$701A,$A260,$3E80;
FUNCTION PBHOpenDFAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$701A,$A660,$3E80;

FUNCTION PBHCreate(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHCreateSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A208,$3E80;
FUNCTION PBHCreateAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A608,$3E80;
FUNCTION PBHDelete(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHDeleteSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A209,$3E80;
FUNCTION PBHDeleteAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A609,$3E80;
FUNCTION PBHRename(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHRenameSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A20B,$3E80;
FUNCTION PBHRenameAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A60B,$3E80;
FUNCTION PBHRstFLock(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHRstFLockSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A242,$3E80;
FUNCTION PBHRstFLockAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A642,$3E80;
FUNCTION PBHSetFLock(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHSetFLockSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A241,$3E80;
FUNCTION PBHSetFLockAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A641,$3E80;
FUNCTION PBHGetFInfo(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetFInfoSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A20C,$3E80;
FUNCTION PBHGetFInfoAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A60C,$3E80;
FUNCTION PBHSetFInfo(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHSetFInfoSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A20D,$3E80;
FUNCTION PBHSetFInfoAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$A60D,$3E80;

FUNCTION PBMakeFSSpec(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBMakeFSSpecSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$701B,$A260,$3E80;
FUNCTION PBMakeFSSpecAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$701B,$A660,$3E80;

PROCEDURE FInitQueue;
 INLINE $A016;
FUNCTION GetFSQHdr: QHdrPtr;
 INLINE $2EBC,$0000,$0360;
FUNCTION GetDrvQHdr: QHdrPtr;
 INLINE $2EBC,$0000,$0308;
FUNCTION GetVCBQHdr: QHdrPtr;
 INLINE $2EBC,$0000,$0356;
FUNCTION HGetVol(volName: StringPtr;VAR vRefNum: INTEGER;VAR dirID: LONGINT): OSErr;
FUNCTION HSetVol(volName: StringPtr;vRefNum: INTEGER;dirID: LONGINT): OSErr;
FUNCTION HOpen(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;permission: SignedByte;
 VAR refNum: INTEGER): OSErr;
FUNCTION HOpenDF(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;permission: SignedByte;
 VAR refNum: INTEGER): OSErr;
FUNCTION HOpenRF(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;permission: SignedByte;
 VAR refNum: INTEGER): OSErr;
FUNCTION AllocContig(refNum: INTEGER;VAR count: LONGINT): OSErr;
FUNCTION HCreate(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;creator: OSType;
 fileType: OSType): OSErr;
FUNCTION DirCreate(vRefNum: INTEGER;parentDirID: LONGINT;directoryName: Str255;
 VAR createdDirID: LONGINT): OSErr;
FUNCTION HDelete(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255): OSErr;
FUNCTION HGetFInfo(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;VAR fndrInfo: FInfo): OSErr;
FUNCTION HSetFInfo(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;fndrInfo: FInfo): OSErr;
FUNCTION HSetFLock(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255): OSErr;
FUNCTION HRstFLock(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255): OSErr;
FUNCTION HRename(vRefNum: INTEGER;dirID: LONGINT;oldName: Str255;newName: Str255): OSErr;
FUNCTION CatMove(vRefNum: INTEGER;dirID: LONGINT;oldName: Str255;newDirID: LONGINT;
 newName: Str255): OSErr;
FUNCTION OpenWD(vRefNum: INTEGER;dirID: LONGINT;procID: LONGINT;VAR wdRefNum: INTEGER): OSErr;
FUNCTION CloseWD(wdRefNum: INTEGER): OSErr;
FUNCTION GetWDInfo(wdRefNum: INTEGER;VAR vRefNum: INTEGER;VAR dirID: LONGINT;
 VAR procID: LONGINT): OSErr;

{  shared environment  }
FUNCTION PBHGetVolParms(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetVolParmsSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7030,$A260,$3E80;
FUNCTION PBHGetVolParmsAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7030,$A660,$3E80;
FUNCTION PBHGetLogInInfo(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetLogInInfoSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7031,$A260,$3E80;
FUNCTION PBHGetLogInInfoAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7031,$A660,$3E80;
FUNCTION PBHGetDirAccess(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHGetDirAccessSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7032,$A260,$3E80;
FUNCTION PBHGetDirAccessAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7032,$A660,$3E80;
FUNCTION PBHSetDirAccess(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHSetDirAccessSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7033,$A260,$3E80;
FUNCTION PBHSetDirAccessAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7033,$A660,$3E80;
FUNCTION PBHMapID(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHMapIDSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7034,$A260,$3E80;
FUNCTION PBHMapIDAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7034,$A660,$3E80;
FUNCTION PBHMapName(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHMapNameSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7035,$A260,$3E80;
FUNCTION PBHMapNameAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7035,$A660,$3E80;
FUNCTION PBHCopyFile(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHCopyFileSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7036,$A260,$3E80;
FUNCTION PBHCopyFileAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7036,$A660,$3E80;
FUNCTION PBHMoveRename(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHMoveRenameSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7037,$A260,$3E80;
FUNCTION PBHMoveRenameAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7037,$A660,$3E80;
FUNCTION PBHOpenDeny(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHOpenDenySync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7038,$A260,$3E80;
FUNCTION PBHOpenDenyAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7038,$A660,$3E80;
FUNCTION PBHOpenRFDeny(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBHOpenRFDenySync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7039,$A260,$3E80;
FUNCTION PBHOpenRFDenyAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7039,$A660,$3E80;

FUNCTION PBExchangeFiles(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBExchangeFilesSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7017,$A260,$3E80;
FUNCTION PBExchangeFilesAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7017,$A660,$3E80;
FUNCTION PBCreateFileIDRef(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBCreateFileIDRefSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7014,$A260,$3E80;
FUNCTION PBCreateFileIDRefAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7014,$A660,$3E80;
FUNCTION PBResolveFileIDRef(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBResolveFileIDRefSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7016,$A260,$3E80;
FUNCTION PBResolveFileIDRefAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7016,$A660,$3E80;
FUNCTION PBDeleteFileIDRef(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBDeleteFileIDRefSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7015,$A260,$3E80;
FUNCTION PBDeleteFileIDRefAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7015,$A660,$3E80;

FUNCTION PBGetForeignPrivs(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBGetForeignPrivsSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7060,$A260,$3E80;
FUNCTION PBGetForeignPrivsAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7060,$A660,$3E80;
FUNCTION PBSetForeignPrivs(paramBlock: HParmBlkPtr;async: BOOLEAN): OSErr;
FUNCTION PBSetForeignPrivsSync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7061,$A260,$3E80;
FUNCTION PBSetForeignPrivsAsync(paramBlock: HParmBlkPtr): OSErr;
 INLINE $205F,$7061,$A660,$3E80;

{  Desktop Manager  }
FUNCTION PBDTGetPath(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7020,$A260,$3E80;
FUNCTION PBDTCloseDown(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7021,$A260,$3E80;
FUNCTION PBDTAddIcon(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTAddIconSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7022,$A260,$3E80;
FUNCTION PBDTAddIconAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7022,$A660,$3E80;
FUNCTION PBDTGetIcon(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTGetIconSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7023,$A260,$3E80;
FUNCTION PBDTGetIconAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7023,$A660,$3E80;
FUNCTION PBDTGetIconInfo(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTGetIconInfoSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7024,$A260,$3E80;
FUNCTION PBDTGetIconInfoAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7024,$A660,$3E80;
FUNCTION PBDTAddAPPL(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTAddAPPLSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7025,$A260,$3E80;
FUNCTION PBDTAddAPPLAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7025,$A660,$3E80;
FUNCTION PBDTRemoveAPPL(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTRemoveAPPLSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7026,$A260,$3E80;
FUNCTION PBDTRemoveAPPLAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7026,$A660,$3E80;
FUNCTION PBDTGetAPPL(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTGetAPPLSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7027,$A260,$3E80;
FUNCTION PBDTGetAPPLAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7027,$A660,$3E80;
FUNCTION PBDTSetComment(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTSetCommentSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7028,$A260,$3E80;
FUNCTION PBDTSetCommentAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7028,$A660,$3E80;
FUNCTION PBDTRemoveComment(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTRemoveCommentSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7029,$A260,$3E80;
FUNCTION PBDTRemoveCommentAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$7029,$A660,$3E80;
FUNCTION PBDTGetComment(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTGetCommentSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702A,$A260,$3E80;
FUNCTION PBDTGetCommentAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702A,$A660,$3E80;
FUNCTION PBDTFlush(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTFlushSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702B,$A260,$3E80;
FUNCTION PBDTFlushAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702B,$A660,$3E80;
FUNCTION PBDTReset(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTResetSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702C,$A260,$3E80;
FUNCTION PBDTResetAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702C,$A660,$3E80;
FUNCTION PBDTGetInfo(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTGetInfoSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702D,$A260,$3E80;
FUNCTION PBDTGetInfoAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702D,$A660,$3E80;
FUNCTION PBDTOpenInform(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702E,$A060,$3E80;
FUNCTION PBDTDelete(paramBlock: DTPBPtr;async: BOOLEAN): OSErr;
FUNCTION PBDTDeleteSync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702F,$A060,$3E80;
FUNCTION PBDTDeleteAsync(paramBlock: DTPBPtr): OSErr;
 INLINE $205F,$702F,$A460,$3E80;

{  VolumeMount traps  }
FUNCTION PBGetVolMountInfoSize(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$703F,$A260,$3E80;
FUNCTION PBGetVolMountInfo(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7040,$A260,$3E80;
FUNCTION PBVolumeMount(paramBlock: ParmBlkPtr): OSErr;
 INLINE $205F,$7041,$A260,$3E80;

{  FSp traps  }
FUNCTION FSMakeFSSpec(vRefNum: INTEGER;dirID: LONGINT;fileName: Str255;
 VAR spec: FSSpec): OSErr;
 INLINE $303C, $0001, $AA52;
FUNCTION FSpOpenDF(spec: FSSpec;permission: SignedByte;VAR refNum: INTEGER): OSErr;
 INLINE $303C, $0002, $AA52;
FUNCTION FSpOpenRF(spec: FSSpec ;permission: SignedByte;VAR refNum: INTEGER): OSErr;
 INLINE $303C, $0003, $AA52;
FUNCTION FSpCreate(spec: FSSpec ;creator: OSType;fileType: OSType;scriptTag: ScriptCode): OSErr;
 INLINE $303C, $0004, $AA52;
FUNCTION FSpDirCreate(spec: FSSpec;scriptTag: ScriptCode;VAR createdDirID: LONGINT): OSErr;
 INLINE $303C, $0005, $AA52;
FUNCTION FSpDelete(spec: FSSpec): OSErr;
 INLINE $303C, $0006, $AA52;
FUNCTION FSpGetFInfo(spec: FSSpec;VAR fndrInfo: FInfo): OSErr;
 INLINE $303C, $0007, $AA52;
FUNCTION FSpSetFInfo(spec: FSSpec;fndrInfo: FInfo): OSErr;
 INLINE $303C, $0008, $AA52;
FUNCTION FSpSetFLock(spec: FSSpec): OSErr;
 INLINE $303C, $0009, $AA52;
FUNCTION FSpRstFLock(spec: FSSpec): OSErr;
 INLINE $303C, $000A, $AA52;
FUNCTION FSpRename(spec: FSSpec;newName: Str255): OSErr;
 INLINE $303C, $000B, $AA52;
FUNCTION FSpCatMove(source: FSSpec;dest: FSSpec): OSErr;
 INLINE $303C, $000C, $AA52;
FUNCTION FSpExchangeFiles(source: FSSpec;dest: FSSpec): OSErr;
 INLINE $303C, $000F, $AA52;


{$ENDC} { UsingFiles }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

