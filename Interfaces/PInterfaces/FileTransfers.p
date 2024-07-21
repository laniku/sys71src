{************************************************************
	FileTransfers.p
	Pascal Interface to the File Transfer Manager

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
		
    This file is used in these builds: ROM System

	Change History (most recent first):

		<12>	 8/28/91	CH		Updated interface headers for consistency.
		<11>	 8/20/91	BH		remove FTSetupCleanup from public interfaces
		<10>	 7/25/91	JL		Checked in database generated file from DSG.  Added
									FileTransferReadProcPtr - > FileTransferChooseIdleProcPtr and
									utilized them to match C file. Changed 2nd param type of FTSend
									from FSSpecArray to FSSpecArrayPtr to match C header.
		 <9>	  7/9/91	BH		reinclude ftWriteFileInfo and renumber ftXXXXGetFPost and
									ftXXXXSetFPos
		 <8>	  7/3/91	BH		removed ftFullDuplex
		 <7>	 6/26/91	BH		oops - i screwed up the build - fixed declarations of FTSend and
									FTReceive
		 <6>	 6/26/91	BH		added FTSend, FTReceive, and constants for read and write procs
									and new constant for ftMultipleFileSend
		 <5>	 6/25/91	JNG		Add ftConfigChanged
		 <4>	 6/18/91	BH		remove chooserec structure and other constants
		 <3>	 6/18/91	BH		remove choose stuff
		 <2>	 3/13/91	JL		MPW-ized inclusions of other files.  Include files from the
									PInterfaces directory of mpw
		 <1>	 3/17/90	BBH		first checked in to BBS

	To Do:
************************************************************}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT FileTransfers;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFileTransfers}
{$SETC UsingFileTransfers := 1}

{$I+}
{$SETC FileTransfersIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPackages}
{$I $$Shell(PInterfaces)Packages.p}
{$ENDC}
{$IFC UNDEFINED UsingCTBUtilities}
{$I $$Shell(PInterfaces)CTBUtilities.p}
{$ENDC}
{$IFC UNDEFINED UsingConnections}
{$I $$Shell(PInterfaces)Connections.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := FileTransfersIncludes}

CONST

{ current file transfer manager version }
curFTVersion		=	2;
	
{ FTErr }
ftGenericError		=	-1;
ftNoErr				=	0;
ftRejected			=	1;
ftFailed			=	2;
ftTimeOut			=	3;
ftTooManyRetry		=	4;
ftNotEnoughDSpace	=	5;
ftRemoteCancel		=	6;
ftWrongFormat		=	7;
ftNoTools			=	8;
ftUserCancel		=	9;
ftNotSupported		=	10;

TYPE
FTErr				=	OSErr;

CONST

{ FTFlags }
ftIsFTMode			=	$00000001;
ftNoMenus			=	$00000002;
ftQuiet				=	$00000004;
ftConfigChanged		=	$00000010;
ftSucc				=	$00000080;

TYPE
FTFlags				= 	LONGINT;


CONST

{ FTAttributes }
ftSameCircuit		=	$0001;
ftSendDisable 		=	$0002;
ftReceiveDisable	=	$0004;
ftTextOnly			=	$0008;
ftNoStdFile			=	$0010;
ftMultipleFileSend	=	$0020;

TYPE
FTAttributes		=	INTEGER;


CONST

{ FTDirection }
ftReceiving			=	0;
ftTransmitting		=	1;

TYPE
FTDirection			=	INTEGER;
			

FTPtr				=	^FTRecord;
FTHandle			=	^FTPtr;
FTRecord			=	PACKED RECORD
	procID:		INTEGER;
	flags:		FTFlags;
	errCode:	FTErr;
	refCon:		LONGINT;
	userData:	LONGINT;
	defProc:	ProcPtr;
	config:		Ptr;
	oldConfig:	Ptr;
	environsProc:	ProcPtr;
	reserved1:	LONGINT;		
	reserved2:	LONGINT;		
	ftPrivate:	Ptr;
	sendProc:  	ProcPtr;
	recvProc:	ProcPtr;
	writeProc:	ProcPtr;
	readProc:	ProcPtr;
	owner:		WindowPtr;
	direction:	FTDirection;
	theReply: 	SFReply;
	writePtr:	LONGINT;
	readPtr:	LONGINT;
	theBuf:		^char;
	bufSize:	LONGINT;
	autoRec:	Str255;
	attributes:	FTAttributes;
 END;


CONST

{ FTReadProc messages }
ftReadOpenFile 		= 	0; 		{ count = forkFlags, buffer = pblock from PBGetFInfo }
ftReadDataFork		=	1;
ftReadRsrcFork		=	2;
ftReadAbort			=	3;
ftReadComplete		=	4;
ftReadSetFPos 		= 	6; 		{ count = forkFlags, buffer = pBlock same as PBSetFPos }
ftReadGetFPos 		= 	7; 		{ count = forkFlags, buffer = pBlock same as PBGetFPos }


{ FTWriteProc messages }
ftWriteOpenFile 	= 	0; 		{ count = forkFlags, buffer = pblock from PBGetFInfo }
ftWriteDataFork		=	1;
ftWriteRsrcFork		=	2;
ftWriteAbort		=	3;
ftWriteComplete		=	4;
ftWriteFileInfo		=	5;
ftWriteSetFPos 		= 	6; 		{ count = forkFlags, buffer = pBlock same as PBSetFPos }
ftWriteGetFPos 		= 	7; 		{ count = forkFlags, buffer = pBlock same as PBGetFPos }


{	fork flags }
ftOpenDataFork		=	1;
ftOpenRsrcFork		=	2;

TYPE
{	application routines type definitions }
FileTransferReadProcPtr = ProcPtr;
FileTransferWriteProcPtr = ProcPtr;

FileTransferSendProcPtr = ProcPtr;
FileTransferReceiveProcPtr = ProcPtr;

FileTransferEnvironsProcPtr = ProcPtr;

FileTransferNotificationProcPtr = ProcPtr;
FileTransferChooseIdleProcPtr = ProcPtr;

FUNCTION 	InitFT: FTErr;
FUNCTION 	FTGetVersion(hFT: FTHandle): Handle;
FUNCTION 	FTGetFTVersion: INTEGER;

FUNCTION 	FTNew(procID: INTEGER;flags: FTFlags;sendProc: FileTransferSendProcPtr;
 recvProc: FileTransferReceiveProcPtr;readProc: FileTransferReadProcPtr;
 writeProc: FileTransferWriteProcPtr;environsProc: FileTransferEnvironsProcPtr;
 owner: WindowPtr;refCon: LONGINT;userData: LONGINT): FTHandle;
			
PROCEDURE 	FTDispose(hFT: FTHandle);

FUNCTION 	FTStart(hFT: FTHandle;direction: FTDirection;fileInfo: SFReply): FTErr;
FUNCTION 	FTAbort(hFT: FTHandle): FTErr;

FUNCTION	FTSend(hFT: FTHandle;numFiles: INTEGER;pFSSpec: FSSpecArrayPtr;
 notifyProc: FileTransferNotificationProcPtr): FTErr;
FUNCTION	FTReceive(hFT: FTHandle;pFSSpec: FSSpecPtr;notifyProc: FileTransferNotificationProcPtr): FTErr;

PROCEDURE 	FTExec(hFT: FTHandle);

PROCEDURE 	FTActivate(hFT: FTHandle;activate: BOOLEAN);
PROCEDURE 	FTResume(hFT: FTHandle;resume: BOOLEAN);
FUNCTION	FTMenu(hFT: FTHandle;menuID: INTEGER;item: INTEGER): BOOLEAN;

FUNCTION 	FTChoose(VAR hFT: FTHandle;where: Point;idleProc: FileTransferChooseIdleProcPtr): INTEGER;
PROCEDURE 	FTEvent(hFT: FTHandle;theEvent: EventRecord);

FUNCTION  	FTValidate(hFT: FTHandle): BOOLEAN;
PROCEDURE 	FTDefault(VAR theConfig: Ptr;procID: INTEGER;allocate: BOOLEAN);

FUNCTION  	FTSetupPreflight(procID: INTEGER;VAR magicCookie: LONGINT): Handle;
PROCEDURE 	FTSetupSetup(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr;
			VAR magicCookie: LONGINT);
FUNCTION  	FTSetupFilter(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr; 
			VAR theEvent: EventRecord;VAR theItem: INTEGER;VAR magicCookie: LONGINT): BOOLEAN;
PROCEDURE 	FTSetupItem(procID: INTEGER;theConfig: Ptr;count: INTEGER;theDialog: DialogPtr;
			VAR theItem: INTEGER;VAR magicCookie: LONGINT);
PROCEDURE 	FTSetupXCleanup(procID: INTEGER;theConfig: Ptr;count: INTEGER;
			theDialog: DialogPtr;OKed: BOOLEAN;VAR magicCookie: LONGINT);

PROCEDURE 	FTSetupPostflight(procID: INTEGER);

FUNCTION  	FTGetConfig(hFT: FTHandle): Ptr;
FUNCTION  	FTSetConfig(hFT: FTHandle;thePtr: Ptr): INTEGER;

FUNCTION 	FTIntlToEnglish(hFT: FTHandle;inputPtr: Ptr;VAR outputPtr: Ptr;
				language: INTEGER): OSErr;
FUNCTION 	FTEnglishToIntl(hFT: FTHandle;inputPtr: Ptr;VAR outputPtr: Ptr;
				language: INTEGER): OSErr;

PROCEDURE 	FTGetToolName(procID: INTEGER;VAR name: Str255);
FUNCTION  	FTGetProcID(name: Str255): INTEGER;

PROCEDURE 	FTSetRefCon(hFT: FTHandle;refCon: LONGINT);
FUNCTION  	FTGetRefCon(hFT: FTHandle): LONGINT;

PROCEDURE 	FTSetUserData(hFT: FTHandle;userData: LONGINT);
FUNCTION  	FTGetUserData(hFT: FTHandle): LONGINT;

PROCEDURE	FTGetErrorString(hFT: FTHandle;id: INTEGER;VAR errMsg: Str255);


{$ENDC} { UsingFileTransfers }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

