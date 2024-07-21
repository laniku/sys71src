
{
Created: Saturday, July 27, 1991 at 10:35 PM
 Printing.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: BigBang Sys606

	Change History (most recent first):

		 <5>	 2/18/92	MH		This file now uses the inline access to the _PrGlue trap which
									was formerly provided in PrintTraps.p. The glue routines from
									interfaces.o which were formerly accessed via this file were
									only necessary to support execution on a Mac Plus or earlier
									running system 4.0 or earlier. It is no longer necessary to
									support that configuration in current internal or external
									product development. The file PrintTraps.p is now a stub which
									only includes this file.
		 <4>	  8/8/91	JL		Added OpNotImpl as Found in IM v. V p. 411
		 <3>	 7/31/91	JL		Updated Copyright. Restored Comments.
		 <2>	 1/28/91	LN		Checked in Database Generated File from DSG. Added PrIdleProcPtr
									to match .h file.
	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Printing;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPrinting}
{$SETC UsingPrinting := 1}

{$I+}
{$SETC PrintingIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$IFC UNDEFINED UsingDialogs}
{$I $$Shell(PInterfaces)Dialogs.p}
{$ENDC}
{$SETC UsingIncludes := PrintingIncludes}

CONST
iPFMaxPgs = 128;
iPrPgFract = 120;						{Page scale factor. ptPgSize (below) is in units of 1/iPrPgFract}
iPrPgFst = 1;							{Page range constants}
iPrPgMax = 9999;
iPrRelease = 3;							{Current version number of the code.}
iPrSavPFil = -1;
iPrAbort = $0080;
iPrDevCtl = 7;							{The PrDevCtl Proc's ctl number}
lPrReset = $00010000;					{The PrDevCtl Proc's CParam for reset}
lPrLineFeed = $00030000;
lPrLFStd = $0003FFFF;					{The PrDevCtl Proc's CParam for std paper advance}
lPrLFSixth = $0003FFFF;
lPrPageEnd = $00020000;					{The PrDevCtl Proc's CParam for end page}
lPrDocOpen = $00010000;
lPrPageOpen = $00040000;
lPrPageClose = $00020000;
lPrDocClose = $00050000;
iFMgrCtl = 8;							{The FMgr's Tail-hook Proc's ctl number}
iMscCtl = 9;							{The FMgr's Tail-hook Proc's ctl number}
iPvtCtl = 10;							{The FMgr's Tail-hook Proc's ctl number}
iMemFullErr = -108;
iIOAbort = -27;
pPrGlobals = $00000944;					{The PrVars lo mem area:}
bDraftLoop = 0;
bSpoolLoop = 1;
bUser1Loop = 2;
bUser2Loop = 3;
fNewRunBit = 2;
fHiResOK = 3;
fWeOpenedRF = 4;

{Driver constants }
iPrBitsCtl = 4;
lScreenBits = 0;
lPaintBits = 1;
lHiScreenBits = $00000002;				{The Bitmap Print Proc's Screen Bitmap param}
lHiPaintBits = $00000003;				{The Bitmap Print Proc's Paint [sq pix] param}
iPrIOCtl = 5;
iPrEvtCtl = 6;							{The PrEvent Proc's ctl number}
lPrEvtAll = $0002FFFD;					{The PrEvent Proc's CParam for the entire screen}
lPrEvtTop = $0001FFFD;					{The PrEvent Proc's CParam for the top folder}
iPrDrvrRef = -3;
getRslDataOp = 4;
setRslOp = 5;
draftBitsOp = 6;
noDraftBitsOp = 7;
getRotnOp = 8;
NoSuchRsl = 1;
OpNotImpl = 2;							{the driver doesn't support this opcode}
RgType1 = 1;

TYPE
TFeed = (feedCut,feedFanfold,feedMechCut,feedOther);

TScan = (scanTB,scanBT,scanLR,scanRL);


TPRect = ^Rect;							{ A Rect Ptr }
PrIdleProcPtr = ProcPtr;
PItemProcPtr = ProcPtr;

TPPrPort = ^TPrPort;
TPrPort = RECORD
 gPort: GrafPort;						{The Printer's graf port.}
 gProcs: QDProcs;						{..and its procs}
 lGParam1: LONGINT;						{16 bytes for private parameter storage.}
 lGParam2: LONGINT;
 lGParam3: LONGINT;
 lGParam4: LONGINT;
 fOurPtr: BOOLEAN;						{Whether the PrPort allocation was done by us.}
 fOurBits: BOOLEAN;						{Whether the BitMap allocation was done by us.}
 END;

{ Printing Graf Port. All printer imaging, whether spooling, banding, etc, happens "thru" a GrafPort.
  This is the "PrPeek" record. }
TPPrInfo = ^TPrInfo;
TPrInfo = RECORD
 iDev: INTEGER;							{Font mgr/QuickDraw device code}
 iVRes: INTEGER;						{Resolution of device, in device coordinates}
 iHRes: INTEGER;						{..note: V before H => compatable with Point.}
 rPage: Rect;							{The page (printable) rectangle in device coordinates.}
 END;

{ Print Info Record: The parameters needed for page composition. }
TPPrStl = ^TPrStl;
TPrStl = RECORD
 wDev: INTEGER;
 iPageV: INTEGER;
 iPageH: INTEGER;
 bPort: SignedByte;
 feed: TFeed;
 END;

TPPrXInfo = ^TPrXInfo;
TPrXInfo = RECORD
 iRowBytes: INTEGER;
 iBandV: INTEGER;
 iBandH: INTEGER;
 iDevBytes: INTEGER;
 iBands: INTEGER;
 bPatScale: SignedByte;
 bUlThick: SignedByte;
 bUlOffset: SignedByte;
 bUlShadow: SignedByte;
 scan: TScan;
 bXInfoX: SignedByte;
 END;

TPPrJob = ^TPrJob;
TPrJob = RECORD
 iFstPage: INTEGER;						{Page Range.}
 iLstPage: INTEGER;
 iCopies: INTEGER;						{No. copies.}
 bJDocLoop: SignedByte;					{The Doc style: Draft, Spool, .., and ..}
 fFromUsr: BOOLEAN;						{Printing from an User's App (not PrApp) flag}
 pIdleProc: PrIdleProcPtr;				{The Proc called while waiting on IO etc.}
 pFileName: StringPtr;					{Spool File Name: NIL for default.}
 iFileVol: INTEGER;						{Spool File vol, set to 0 initially}
 bFileVers: SignedByte;					{Spool File version, set to 0 initially}
 bJobX: SignedByte;						{An eXtra byte.}
 END;

TPrFlag1 = PACKED RECORD
 f15: BOOLEAN;
 f14: BOOLEAN;
 f13: BOOLEAN;
 f12: BOOLEAN;
 f11: BOOLEAN;
 f10: BOOLEAN;
 f9: BOOLEAN;
 f8: BOOLEAN;
 f7: BOOLEAN;
 f6: BOOLEAN;
 f5: BOOLEAN;
 f4: BOOLEAN;
 f3: BOOLEAN;
 f2: BOOLEAN;
 fLstPgFst: BOOLEAN;
 fUserScale: BOOLEAN;
 END;

{ Print Job: Print "form" for a single print request. }
TPPrint = ^TPrint;
THPrint = ^TPPrint;
TPrint = RECORD
 iPrVersion: INTEGER;					{(2) Printing software version}
 prInfo: TPrInfo;						{(14) the PrInfo data associated with the current style.}
 rPaper: Rect;							{(8) The paper rectangle [offset from rPage]}
 prStl: TPrStl;							{(8)  This print request's style.}
 prInfoPT: TPrInfo;						{(14)  Print Time Imaging metrics}
 prXInfo: TPrXInfo;						{(16)  Print-time (expanded) Print info record.}
 prJob: TPrJob;							{(20) The Print Job request (82)  Total of the above; 120-82 = 38 bytes needed to fill 120}
 CASE INTEGER OF
   0:
  (printX: ARRAY [1..19] OF INTEGER);
   1:
  (prFlag1: TPrFlag1;   				{a word of flags}
  iZoomMin: INTEGER;
  iZoomMax: INTEGER;
  hDocName: StringHandle); 				{current doc's name, nil = front window}
 END;

{ The universal 120 byte printing record }
TPPrStatus = ^TPrStatus;
TPrStatus = RECORD
 iTotPages: INTEGER;					{Total pages in Print File.}
 iCurPage: INTEGER;						{Current page number}
 iTotCopies: INTEGER;					{Total copies requested}
 iCurCopy: INTEGER;						{Current copy number}
 iTotBands: INTEGER;					{Total bands per page.}
 iCurBand: INTEGER;						{Current band number}
 fPgDirty: BOOLEAN;						{True if current page has been written to.}
 fImaging: BOOLEAN;						{Set while in band's DrawPic call.}
 hPrint: THPrint;						{Handle to the active Printer record}
 pPrPort: TPPrPort;						{Ptr to the active PrPort}
 hPic: PicHandle;						{Handle to the active Picture}
 END;

{ Print Status: Print information during printing. }
TPPfPgDir = ^TPfPgDir;
THPfPgDir = ^TPPfPgDir;
TPfPgDir = RECORD
 iPages: INTEGER;
 iPgPos: ARRAY [0..128] OF LONGINT;		{ARRAY [0..iPfMaxPgs] OF LONGINT}
 END;

{ PicFile = a TPfHeader followed by n QuickDraw Pics (whose PicSize is invalid!) }
TPPrDlg = ^TPrDlg;
TPrDlg = RECORD
 Dlg: DialogRecord;						{The Dialog window}
 pFltrProc: ModalFilterProcPtr;			{The Filter Proc.}
 pItemProc: PItemProcPtr;				{The Item evaluating proc.}
 hPrintUsr: THPrint;					{The user's print record.}
 fDoIt: BOOLEAN;
 fDone: BOOLEAN;
 lUser1: LONGINT;						{Four longs for user's to hang global data.}
 lUser2: LONGINT;						{...Plus more stuff needed by the particular printing dialog.}
 lUser3: LONGINT;
 lUser4: LONGINT;
 END;


PDlgInitProcPtr = ProcPtr;

TGnlData = RECORD
 iOpCode: INTEGER;
 iError: INTEGER;
 lReserved: LONGINT;					{more fields here depending on call}
 END;

TRslRg = RECORD
 iMin: INTEGER;
 iMax: INTEGER;
 END;

TRslRec = RECORD
 iXRsl: INTEGER;
 iYRsl: INTEGER;
 END;

TGetRslBlk = RECORD
 iOpCode: INTEGER;
 iError: INTEGER;
 lReserved: LONGINT;
 iRgType: INTEGER;
 xRslRg: TRslRg;
 yRslRg: TRslRg;
 iRslRecCnt: INTEGER;
 rgRslRec: ARRAY [1..27] OF TRslRec;
 END;

TSetRslBlk = RECORD
 iOpCode: INTEGER;
 iError: INTEGER;
 lReserved: LONGINT;
 hPrint: THPrint;
 iXRsl: INTEGER;
 iYRsl: INTEGER;
 END;

TDftBitsBlk = RECORD
 iOpCode: INTEGER;
 iError: INTEGER;
 lReserved: LONGINT;
 hPrint: THPrint;
 END;

TGetRotnBlk = RECORD
 iOpCode: INTEGER;
 iError: INTEGER;
 lReserved: LONGINT;
 hPrint: THPrint;
 fLandscape: BOOLEAN;
 bXtra: SignedByte;
 END;

TPBitMap = ^BitMap;						{ A BitMap Ptr }

TN = 0..15;								{ a Nibble }

TPWord = ^TWord;
THWord = ^TPWord;
TWord = PACKED RECORD
 CASE INTEGER OF
   0:
  (c1,c0: CHAR);
   1:
  (b1,b0: SignedByte);
   2:
  (usb1,usb0: Byte);
   3:
  (n3,n2,n1,n0: TN);
   4:
  (f15,f14,f13,f12,f11,f10,f9,f8,f7,f6,f5,f4,f3,f2,f1,f0: BOOLEAN);
   5:
  (i0: INTEGER);
 END;

TPLong = ^TLong;
THLong = ^TPLong;
TLong = RECORD
 CASE INTEGER OF
   0:
  (w1,w0: TWord);
   1:
  (b1,b0: LONGINT);
   2:
  (p0: Ptr);
   3:
  (h0: Handle);
   4:
  (pt: Point);
 END;


PROCEDURE PrPurge;
 INLINE $2F3C,$A800,$0000,$A8FD;
PROCEDURE PrNoPurge;
 INLINE $2F3C,$B000,$0000,$A8FD;
PROCEDURE PrOpen;
 INLINE $2F3C,$C800,$0000,$A8FD;
PROCEDURE PrClose;
 INLINE $2F3C,$D000,$0000,$A8FD;
PROCEDURE PrintDefault(hPrint: THPrint);
 INLINE $2F3C,$2004,$0480,$A8FD;
FUNCTION PrValidate(hPrint: THPrint): BOOLEAN;
 INLINE $2F3C,$5204,$0498,$A8FD;
FUNCTION PrStlDialog(hPrint: THPrint): BOOLEAN;
 INLINE $2F3C,$2A04,$0484,$A8FD;
FUNCTION PrJobDialog(hPrint: THPrint): BOOLEAN;
 INLINE $2F3C,$3204,$0488,$A8FD;
FUNCTION PrStlInit(hPrint: THPrint): TPPrDlg;
 INLINE $2F3C,$3C04,$040C,$A8FD;
FUNCTION PrJobInit(hPrint: THPrint): TPPrDlg;
 INLINE $2F3C,$4404,$0410,$A8FD;
PROCEDURE PrJobMerge(hPrintSrc: THPrint;hPrintDst: THPrint);
 INLINE $2F3C,$5804,$089C,$A8FD;
FUNCTION PrDlgMain(hPrint: THPrint;pDlgInit: PDlgInitProcPtr): BOOLEAN;
 INLINE $2F3C,$4A04,$0894,$A8FD;
FUNCTION PrOpenDoc(hPrint: THPrint;pPrPort: TPPrPort;pIOBuf: Ptr): TPPrPort;
 INLINE $2F3C,$0400,$0C00,$A8FD;
PROCEDURE PrCloseDoc(pPrPort: TPPrPort);
 INLINE $2F3C,$0800,$0484,$A8FD;
PROCEDURE PrOpenPage(pPrPort: TPPrPort;pPageFrame: TPRect);
 INLINE $2F3C,$1000,$0808,$A8FD;
PROCEDURE PrClosePage(pPrPort: TPPrPort);
 INLINE $2F3C,$1800,$040C,$A8FD;
PROCEDURE PrPicFile(hPrint: THPrint;pPrPort: TPPrPort;pIOBuf: Ptr;pDevBuf: Ptr;
 VAR prStatus: TPrStatus);
 INLINE $2F3C,$6005,$1480,$A8FD;
FUNCTION PrError: INTEGER;
 INLINE $2F3C,$BA00,$0000,$A8FD;
PROCEDURE PrSetError(iErr: INTEGER);
 INLINE $2F3C,$C000,$0200,$A8FD;
PROCEDURE PrGeneral(pData: Ptr);
 INLINE $2F3C,$7007,$0480,$A8FD;
PROCEDURE PrDrvrOpen;
 INLINE $2F3C,$8000,$0000,$A8FD;
PROCEDURE PrDrvrClose;
 INLINE $2F3C,$8800,$0000,$A8FD;
PROCEDURE PrCtlCall(iWhichCtl: INTEGER;lParam1: LONGINT;lParam2: LONGINT;
 lParam3: LONGINT);
 INLINE $2F3C,$A000,$0E00,$A8FD;
FUNCTION PrDrvrDCE: Handle;
 INLINE $2F3C,$9400,$0000,$A8FD;
FUNCTION PrDrvrVers: INTEGER;
 INLINE $2F3C,$9A00,$0000,$A8FD;


{$ENDC} { UsingPrinting }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

