
{
Created: Friday, November 15, 1991 at 9:35 AM
 SysEqu.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		 <9>	 4/16/92	DCL		For New Inside Mac: Added SysDirection as a synonym for
									TESysJust.
		 <8>	 4/14/92	DCL		Added new improved names in the continued pursuit of
									name-nirvana in IM 2nd Edition.
		 <7>	 2/17/92	MH		Corrected value of timeSCSIDB from 0DA6 to 0B24.
		 <6>	11/19/91	JL		Added ToolScratch and ApplScratch as per I.M. vol. I p. 85.
		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/28/91	LN		Checked in Database Generated File from DSG. Adjusted comments
									to match .h file.
		 <3>	 3/15/90	BBH		
		 <1>	  1/3/90	ngk		first checked in

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT SysEqu;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSysEqu}
{$SETC UsingSysEqu := 1}


CONST
PCDeskPat = $20B;				{[GLOBAL VAR]  desktop pat, top bit only! others are in use}
HiKeyLast = $216;				{[GLOBAL VAR]  Same as KbdVars}
KbdLast = $218;					{[GLOBAL VAR]  Same as KbdVars+2}
ExpandMem = $2B6;				{[GLOBAL VAR]  pointer to expanded memory block}
SCSIBase = $0C00;				{[GLOBAL VAR]  (long) base address for SCSI chip read}
SCSIDMA = $0C04;				{[GLOBAL VAR]  (long) base address for SCSI DMA}
SCSIHsk = $0C08;				{[GLOBAL VAR]  (long) base address for SCSI handshake}
SCSIGlobals = $0C0C;			{[GLOBAL VAR]  (long) ptr for SCSI mgr locals}
RGBBlack = $0C10;				{[GLOBAL VAR]  (6 bytes) the black field for color}
RGBWhite = $0C16;				{[GLOBAL VAR]  (6 bytes) the white field for color}
RowBits = $0C20;				{[GLOBAL VAR]  (word) screen horizontal pixels}
ColLines = $0C22;				{[GLOBAL VAR]  (word) screen vertical pixels}
ScreenBytes = $0C24;			{[GLOBAL VAR]  (long) total screen bytes}
NMIFlag = $0C2C;				{[GLOBAL VAR]  (byte) flag for NMI debounce}
VidType = $0C2D;				{[GLOBAL VAR]  (byte) video board type ID}
VidMode = $0C2E;				{[GLOBAL VAR]  (byte) video mode (4=4bit color)}
SCSIPoll = $0C2F;				{[GLOBAL VAR]  (byte) poll for device zero only once.}
SEVarBase = $0C30;				{[GLOBAL VAR] }
MMUFlags = $0CB0;				{[GLOBAL VAR]  (byte) cleared to zero (reserved for future use)}
MMUType = $0CB1;				{[GLOBAL VAR]  (byte) kind of MMU present}
MMU32bit = $0CB2;				{[GLOBAL VAR]  (byte) boolean reflecting current machine MMU mode}
MMUFluff = $0CB3;				{[GLOBAL VAR]  (byte) fluff byte forced by reducing MMUMode to MMU32bit.}
MMUTbl = $0CB4;					{[GLOBAL VAR]  (long) pointer to MMU Mapping table}
MMUTblSize = $0CB8;				{[GLOBAL VAR]  (long) size of the MMU mapping table}
SInfoPtr = $0CBC;				{[GLOBAL VAR]  (long) pointer to Slot manager information}
ASCBase = $0CC0;				{[GLOBAL VAR]  (long) pointer to Sound Chip}
SMGlobals = $0CC4;				{ (long) pointer to Sound Manager Globals}
TheGDevice = $0CC8;				{[GLOBAL VAR]  (long) the current graphics device}
CQDGlobals = $0CCC;				{ (long) quickDraw global extensions}
ADBBase = $0CF8;				{[GLOBAL VAR]  (long) pointer to Front Desk Buss Variables}
WarmStart = $0CFC;				{[GLOBAL VAR]  (long) flag to indicate it is a warm start}
TimeDBRA = $0D00;				{[GLOBAL VAR]  (word) number of iterations of DBRA per millisecond}
TimeSCCDB = $0D02;				{[GLOBAL VAR]  (word) number of iter's of SCC access & DBRA.}
SlotQDT = $0D04;				{[GLOBAL VAR]  ptr to slot queue table}
SlotPrTbl = $0D08;				{[GLOBAL VAR]  ptr to slot priority table}
SlotVBLQ = $0D0C;				{[GLOBAL VAR]  ptr to slot VBL queue table}
ScrnVBLPtr = $0D10;				{[GLOBAL VAR]  save for ptr to main screen VBL queue}
SlotTICKS = $0D14;				{[GLOBAL VAR]  ptr to slot tickcount table}
TableSeed = $0D20;				{[GLOBAL VAR]  (long) seed value for color table ID's}
SRsrcTblPtr = $0D24;			{[GLOBAL VAR]  (long) pointer to slot resource table.}
JVBLTask = $0D28;				{[GLOBAL VAR]  vector to slot VBL task interrupt handler}
WMgrCPort = $0D2C;				{[GLOBAL VAR]  window manager color port }
VertRRate = $0D30;				{[GLOBAL VAR]  (word) Vertical refresh rate for start manager. }
ChunkyDepth = $0D60;			{[GLOBAL VAR]  depth of the pixels}
CrsrPtr = $0D62;				{[GLOBAL VAR]  pointer to cursor save area}
PortList = $0D66;				{[GLOBAL VAR]  list of grafports}
MickeyBytes = $0D6A;			{[GLOBAL VAR]  long pointer to cursor stuff}
QDErrLM = $0D6E;				{[GLOBAL VAR] QDErr has name conflict w/ type. QuickDraw error code [word]}
VIA2DT = $0D70;					{[GLOBAL VAR]  32 bytes for VIA2 dispatch table for NuMac}
SInitFlags = $0D90;				{[GLOBAL VAR]  StartInit.a flags [word]}
DTQueue = $0D92;				{[GLOBAL VAR]  (10 bytes) deferred task queue header}
DTQFlags = $0D92;				{[GLOBAL VAR]  flag word for DTQueue}
DTskQHdr = $0D94;				{[GLOBAL VAR]  ptr to head of queue}
DTskQTail = $0D98;				{[GLOBAL VAR]  ptr to tail of queue}
JDTInstall = $0D9C;				{[GLOBAL VAR]  (long) ptr to deferred task install routine}
HiliteRGB = $0DA0;				{[GLOBAL VAR]  6 bytes: rgb of hilite color}
TimeSCSIDB = $0B24;				{[GLOBAL VAR]  (word) number of iter's of SCSI access & DBRA}
DSCtrAdj = $0DA8;				{[GLOBAL VAR]  (long) Center adjust for DS rect.}
IconTLAddr = $0DAC;				{[GLOBAL VAR]  (long) pointer to where start icons are to be put.}
VideoInfoOK = $0DB0;			{[GLOBAL VAR]  (long) Signals to CritErr that the Video card is ok}
EndSRTPtr = $0DB4;				{[GLOBAL VAR]  (long) Pointer to the end of the Slot Resource Table (Not the SRT buffer).}
SDMJmpTblPtr = $0DB8;			{[GLOBAL VAR]  (long) Pointer to the SDM jump table}
JSwapMMU = $0DBC;				{[GLOBAL VAR]  (long) jump vector to SwapMMU routine}
SdmBusErr = $0DC0;				{[GLOBAL VAR]  (long) Pointer to the SDM busErr handler}
LastTxGDevice = $0DC4;			{[GLOBAL VAR]  (long) copy of TheGDevice set up for fast text measure}
NewCrsrJTbl = $88C;				{[GLOBAL VAR]  location of new crsr jump vectors}
JAllocCrsr = $88C;				{[GLOBAL VAR]  (long) vector to routine that allocates cursor}
JSetCCrsr = $890;				{[GLOBAL VAR]  (long) vector to routine that sets color cursor}
JOpcodeProc = $894;				{[GLOBAL VAR]  (long) vector to process new picture opcodes}
CrsrBase = $898;				{[GLOBAL VAR]  (long) scrnBase for cursor}
CrsrDevice = $89C;				{[GLOBAL VAR]  (long) current cursor device}
SrcDevice = $8A0;				{[GLOBAL VAR]  (LONG) Src device for Stretchbits}
MainDevice = $8A4;				{[GLOBAL VAR]  (long) the main screen device}
DeviceList = $8A8;				{[GLOBAL VAR]  (long) list of display devices}
CrsrRow = $8AC;					{[GLOBAL VAR]  (word) rowbytes for current cursor screen}
QDColors = $8B0;				{[GLOBAL VAR]  (long) handle to default colors}
HiliteMode = $938;				{[GLOBAL VAR]  used for color highlighting}
BusErrVct = $08;				{[GLOBAL VAR]  bus error vector}
RestProc = $A8C;				{[GLOBAL VAR]  Resume procedure f InitDialogs [pointer]}
ROM85 = $28E;					{[GLOBAL VAR]  (word) actually high bit - 0 for ROM vers $75 (sic) and later}
ROMMapHndl = $B06;				{[GLOBAL VAR]  (long) handle of ROM resource map}
ScrVRes = $102;					{[GLOBAL VAR] Pixels per inch vertically (word)
   screen vertical dots/inch [word]}
ScrHRes = $104;					{[GLOBAL VAR] Pixels per inch horizontally (word)
   screen horizontal dots/inch [word]}
ScrnBase = $824;				{[GLOBAL VAR] Address of main screen buffer
   Screen Base [pointer]}
ScreenRow = $106;				{[GLOBAL VAR]  rowBytes of screen [word]}
MBTicks = $16E;					{[GLOBAL VAR]  tick count @ last mouse button [long]}
JKybdTask = $21A;				{[GLOBAL VAR]  keyboard VBL task hook [pointer]}
KeyLast = $184;					{[GLOBAL VAR]  ASCII for last valid keycode [word]}
KeyTime = $186;					{[GLOBAL VAR]  tickcount when KEYLAST was rec'd [long]}
KeyRepTime = $18A;				{[GLOBAL VAR]  tickcount when key was last repeated [long]}
SPConfig = $1FB;				{[GLOBAL VAR] Use types for serial ports (byte)
   config bits: 4-7 A, 0-3 B (see use type below)}
SPPortA = $1FC;					{[GLOBAL VAR] Modem port configuration (word)
   SCC port A configuration [word]}
SPPortB = $1FE;					{[GLOBAL VAR] Printer port configuration (word)
   SCC port B configuration [word]}
SCCRd = $1D8;					{[GLOBAL VAR] SCC read base address
   SCC base read address [pointer]}
SCCWr = $1DC;					{[GLOBAL VAR] SCC write base address
   SCC base write address [pointer]}
DoubleTime = $2F0;				{[GLOBAL VAR] Double-click interval in ticks (long)
   double click ticks [long]}
CaretTime = $2F4;				{[GLOBAL VAR] Caret-blink interval in ticks (long)
   caret blink ticks [long]}
KeyThresh = $18E;				{[GLOBAL VAR] Auto-key threshold (word)
   threshold for key repeat [word]}
KeyRepThresh = $190;			{[GLOBAL VAR] Auto-key rate (word)
   key repeat speed [word]}
SdVolume = $260;				{[GLOBAL VAR] Current speaker volume (byte:  low-order three bits only)
   Global volume(sound) control [byte]}
Ticks = $16A;					{[GLOBAL VAR] Current number of ticks since system startup (long)
   Tick count, time since boot [unsigned long]}
TimeLM = $20C;					{[GLOBAL VAR] Time has name conflict w/ type. Clock time (extrapolated) [long]}
MonkeyLives = $100;				{[GLOBAL VAR]  monkey lives if >= 0 [word]}
SEvtEnb = $15C;					{[GLOBAL VAR] 0 if SystemEvent should return FALSE (byte)
   enable SysEvent calls from GNE [byte]}
JournalFlag = $8DE;				{[GLOBAL VAR] Journaling mode (word)
   journaling state [word]}
JournalRef = $8E8;				{[GLOBAL VAR] Reference number of journaling device driver (word)
   Journalling driver's refnum [word]}
BufPtr = $10C;					{[GLOBAL VAR] Address of end of jump table
   top of application memory [pointer]}
StkLowPt = $110;				{[GLOBAL VAR]  Lowest stack as measured in VBL task [pointer]}
TheZone = $118;					{[GLOBAL VAR] Address of current heap zone
   current heap zone [pointer]}
ApplLimit = $130;				{[GLOBAL VAR] Application heap limit
   application limit [pointer]}
SysZone = $2A6;					{[GLOBAL VAR] Address of system heap zone
   system heap zone [pointer]}
ApplZone = $2AA;				{[GLOBAL VAR] Address of application heap zone
   application heap zone [pointer]}
HeapEnd = $114;					{[GLOBAL VAR] Address of end of application heap zone
   end of heap [pointer]}
HiHeapMark = $BAE;				{[GLOBAL VAR]  (long) highest address used by a zone below sp<01Nov85 JTC>}
MemErr = $220;					{[GLOBAL VAR]  last memory manager error [word]}
UTableBase = $11C;				{[GLOBAL VAR] Base address of unit table
   unit I/O table [pointer]}
UnitNtryCnt = $1D2;				{[GLOBAL VAR]  count of entries in unit table [word]}
JFetch = $8F4;					{[GLOBAL VAR] Jump vector for Fetch function
   fetch a byte routine for drivers [pointer]}
JStash = $8F8;					{[GLOBAL VAR] Jump vector for Stash function
   stash a byte routine for drivers [pointer]}
JIODone = $8FC;					{[GLOBAL VAR] Jump vector for IODone function
   IODone entry location [pointer]}
DrvQHdr = $308;					{[GLOBAL VAR] Drive queue header (10 bytes)
   queue header of drives in system [10 bytes]}
BootDrive = $210;				{[GLOBAL VAR]  drive number of boot drive [word]}
EjectNotify = $338;				{[GLOBAL VAR]  eject notify procedure [pointer]}
IAZNotify = $33C;				{[GLOBAL VAR]  world swaps notify procedure [pointer]}
SFSaveDisk = $214;				{[GLOBAL VAR] Negative of volume reference number used by Standard File Package (word)
   last vRefNum seen by standard file [word]}
CurDirStore = $398;				{[GLOBAL VAR]  save dir across calls to Standard File [long]}
OneOne = $A02;					{[GLOBAL VAR] $00010001
   constant $00010001 [long]}
MinusOne = $A06;				{[GLOBAL VAR] $FFFFFFFF
   constant $FFFFFFFF [long]}
Lo3Bytes = $31A;				{[GLOBAL VAR] $00FFFFFF
   constant $00FFFFFF [long]}
ROMBase = $2AE;					{[GLOBAL VAR] Base address of ROM
   ROM base address [pointer]}
RAMBase = $2B2;					{[GLOBAL VAR] Trap dispatch table's base address for routines in RAM
   RAM base address [pointer]}
SysVersion = $15A;				{[GLOBAL VAR]  version # of RAM-based system [word]}
RndSeed = $156;					{[GLOBAL VAR] Random number seed (long)
   random seed/number [long]}
Scratch20 = $1E4;				{[GLOBAL VAR] 20-byte scratch area
   scratch [20 bytes]}
Scratch8 = $9FA;				{[GLOBAL VAR] 8-byte scratch area
   scratch [8 bytes]}
ToolScratch = $9CE;				{[GLOBAL VAR] 8-byte scratch area
   scratch [8 bytes]}
ApplScratch = $A78;				{[GLOBAL VAR] 12-byte application scratch area
   scratch [12 bytes]}
ScrapSize = $960;				{[GLOBAL VAR] Size in bytes of desk scrap (long)
   scrap length [long]}
ScrapHandle = $964;				{[GLOBAL VAR] Handle to desk scrap in memory
   memory scrap [handle]}
ScrapCount = $968;				{[GLOBAL VAR] Count changed by ZeroScrap (word)
   validation byte [word]}
ScrapState = $96A;				{[GLOBAL VAR] Tells where desk scrap is (word)
   scrap state [word]}
ScrapName = $96C;				{[GLOBAL VAR] Pointer to scrap file name (preceded by length byte)
   pointer to scrap name [pointer]}
IntlSpec = $BA0;				{[GLOBAL VAR]  (long) - ptr to extra Intl data }
SwitcherTPtr = $286;			{[GLOBAL VAR]  Switcher's switch table }
CPUFlag = $12F;					{[GLOBAL VAR]  $00=68000, $01=68010, $02=68020 (old ROM inits to $00)}
VIA = $1D4;						{[GLOBAL VAR] VIA base address
   VIA base address [pointer]}
IWM = $1E0;						{[GLOBAL VAR]  IWM base address [pointer]}
Lvl1DT = $192;					{[GLOBAL VAR] Level-1 secondary interrupt vector table (32 bytes)
   Interrupt level 1 dispatch table [32 bytes]}
Lvl2DT = $1B2;					{[GLOBAL VAR] Level-2 secondary interrupt vector table (32 bytes)
   Interrupt level 2 dispatch table [32 bytes]}
ExtStsDT = $2BE;				{[GLOBAL VAR] External/status interrupt vector table (16 bytes)
   SCC ext/sts secondary dispatch table [16 bytes]}
SPValid = $1F8;					{[GLOBAL VAR] Validity status (byte)
   validation field ($A7) [byte]}
SPATalkA = $1F9;				{[GLOBAL VAR] AppleTalk node ID hint for modem port (byte)
   AppleTalk node number hint for port A}
SPATalkB = $1FA;				{[GLOBAL VAR] AppleTalk node ID hint for printer port (byte)
   AppleTalk node number hint for port B}
SPAlarm = $200;					{[GLOBAL VAR] Alarm setting (long)
   alarm time [long]}
SPFont = $204;					{[GLOBAL VAR] Application font number minus 1 (word)
   default application font number minus 1 [word]}
SPKbd = $206;					{[GLOBAL VAR] Auto-key threshold and rate (byte)
   kbd repeat thresh in 4/60ths [2 4-bit]}
SPPrint = $207;					{[GLOBAL VAR] Printer connection (byte)
   print stuff [byte]}
SPVolCtl = $208;				{[GLOBAL VAR] Speaker volume setting in parameter RAM (byte)
   volume control [byte]}
SPClikCaret = $209;				{[GLOBAL VAR] Double-click and caret-blink times (byte)
   double click/caret time in 4/60ths[2 4-bit]}
SPMisc1 = $20A;					{[GLOBAL VAR]  miscellaneous [1 byte]}
SPMisc2 = $20B;					{[GLOBAL VAR] Mouse scaling, system startup disk, menu blink (byte)
   miscellaneous [1 byte]}
GetParam = $1E4;				{[GLOBAL VAR]  system parameter scratch [20 bytes]}
SysParam = $1F8;				{[GLOBAL VAR] Low-memory copy of parameter RAM (20 bytes)
   system parameter memory [20 bytes]}
CrsrThresh = $8EC;				{[GLOBAL VAR] Mouse-scaling threshold (word) 
   delta threshold for mouse scaling [word]}
JCrsrTask = $8EE;				{[GLOBAL VAR]  address of CrsrVBLTask [long]}
MTemp = $828;					{[GLOBAL VAR]  Low-level interrupt mouse location [long]}
RawMouse = $82C;				{[GLOBAL VAR]  un-jerked mouse coordinates [long]}
CrsrRect = $83C;				{[GLOBAL VAR]  Cursor hit rectangle [8 bytes]}
TheCrsr = $844;					{[GLOBAL VAR]  Cursor data, mask & hotspot [68 bytes]}
CrsrAddr = $888;				{[GLOBAL VAR]  Address of data under cursor [long]}
CrsrSave = $88C;				{[GLOBAL VAR]  data under the cursor [64 bytes]}
CrsrVis = $8CC;					{[GLOBAL VAR]  Cursor visible? [byte]}
CrsrBusy = $8CD;				{[GLOBAL VAR]  Cursor locked out? [byte]}
CrsrNew = $8CE;					{[GLOBAL VAR]  Cursor changed? [byte]}
CrsrState = $8D0;				{[GLOBAL VAR]  Cursor nesting level [word]}
CrsrObscure = $8D2;				{[GLOBAL VAR]  Cursor obscure semaphore [byte]}
KbdVars = $216;					{[GLOBAL VAR]  Keyboard manager variables [4 bytes]}
KbdType = $21E;					{[GLOBAL VAR]  keyboard model number [byte]}
MBState = $172;					{[GLOBAL VAR]  current mouse button state [byte]}
KeyMapLM = $174;				{[GLOBAL VAR] KeyMap has name conflict w/ type. Bitmap of the keyboard [4 longs]}
KeypadMap = $17C;				{[GLOBAL VAR]  bitmap for numeric pad-18bits [long]}
Key1Trans = $29E;				{[GLOBAL VAR]  keyboard translator procedure [pointer]}
Key2Trans = $2A2;				{[GLOBAL VAR]  numeric keypad translator procedure [pointer]}
JGNEFilter = $29A;				{[GLOBAL VAR]  GetNextEvent filter proc [pointer]}
KeyMVars = $B04;				{[GLOBAL VAR]  (word) for ROM KEYM proc state}
Mouse = $830;					{[GLOBAL VAR]  processed mouse coordinate [long]}
CrsrPin = $834;					{[GLOBAL VAR]  cursor pinning rectangle [8 bytes]}
CrsrCouple = $8CF;				{[GLOBAL VAR]  cursor coupled to mouse? [byte]}
CrsrScale = $8D3;				{[GLOBAL VAR]  cursor scaled? [byte]}
MouseMask = $8D6;				{[GLOBAL VAR]  V-H mask for ANDing with mouse [long]}
MouseOffset = $8DA;				{[GLOBAL VAR]  V-H offset for adding after ANDing [long]}
AlarmState = $21F;				{[GLOBAL VAR]  Bit7=parity, Bit6=beeped, Bit0=enable [byte]}
VBLQueue = $160;				{[GLOBAL VAR] Vertical retrace queue header (10 bytes)
   VBL queue header [10 bytes]}
SysEvtMask = $144;				{[GLOBAL VAR] System event mask (word)
   system event mask [word]}
SysEvtBuf = $146;				{[GLOBAL VAR]  system event queue element buffer [pointer]}
EventQueue = $14A;				{[GLOBAL VAR] Event queue header (10 bytes)
   event queue header [10 bytes]}
EvtBufCnt = $154;				{[GLOBAL VAR]  max number of events in SysEvtBuf - 1 [word]}
GZRootHnd = $328;				{[GLOBAL VAR] Handle to relocatable block not to be moved by grow zone function
   root handle for GrowZone [handle]}
GZRootPtr = $32C;				{[GLOBAL VAR]  root pointer for GrowZone [pointer]}
GZMoveHnd = $330;				{[GLOBAL VAR]  moving handle for GrowZone [handle]}
MemTop = $108;					{[GLOBAL VAR] Address of end of RAM (on Macintosh XL, end of RAM available to applications)
   top of memory [pointer]}
MmInOK = $12E;					{[GLOBAL VAR]  initial memory mgr checks ok? [byte]}
HpChk = $316;					{[GLOBAL VAR]  heap check RAM code [pointer]}
MaskBC = $31A;					{[GLOBAL VAR]  Memory Manager Byte Count Mask [long]}
MaskHandle = $31A;				{[GLOBAL VAR]  Memory Manager Handle Mask [long]}
MaskPtr = $31A;					{[GLOBAL VAR]  Memory Manager Pointer Mask [long]}
MinStack = $31E;				{[GLOBAL VAR] Minimum space allotment for stack (long)
   min stack size used in InitApplZone [long]}
DefltStack = $322;				{[GLOBAL VAR] Default space allotment for stack (long) 
   default size of stack [long]}
MMDefFlags = $326;				{[GLOBAL VAR]  default zone flags [word]}
DSAlertTab = $2BA;				{[GLOBAL VAR] Pointer to system error alert table in use
   system error alerts [pointer]}
DSAlertRect = $3F8;				{[GLOBAL VAR] Rectangle enclosing system error alert (8 bytes)
   rectangle for disk-switch alert [8 bytes]}
DSDrawProc = $334;				{[GLOBAL VAR]  alternate syserror draw procedure [pointer]}
DSWndUpdate = $15D;				{[GLOBAL VAR]  GNE not to paintBehind DS AlertRect? [byte]}
WWExist = $8F2;					{[GLOBAL VAR]  window manager initialized? [byte]}
QDExist = $8F3;					{[GLOBAL VAR]  quickdraw is initialized [byte]}
ResumeProc = $A8C;				{[GLOBAL VAR] Address of resume procedure
   Resume procedure from InitDialogs [pointer]}
DSErrCode = $AF0;				{[GLOBAL VAR] Current system error ID (word)
   last system error alert ID}
IntFlag = $15F;					{[GLOBAL VAR]  reduce interrupt disable time when bit 7 = 0}
SerialVars = $2D0;				{[GLOBAL VAR]  async driver variables [16 bytes]}
ABusVars = $2D8;				{[GLOBAL VAR] Pointer to AppleTalk variables
  ;Pointer to AppleTalk local variables}
ABusDCE = $2DC;					{[GLOBAL VAR] ;Pointer to AppleTalk DCE}
PortAUse = $290;				{[GLOBAL VAR]  bit 7: 1 = not in use, 0 = in use}
PortBUse = $291;				{[GLOBAL VAR] Current availability of serial port B (byte)
   port B use, same format as PortAUse}
SCCASts = $2CE;					{[GLOBAL VAR]  SCC read reg 0 last ext/sts rupt - A [byte]}
SCCBSts = $2CF;					{[GLOBAL VAR]  SCC read reg 0 last ext/sts rupt - B [byte]}
DskErr = $142;					{[GLOBAL VAR]  disk routine result code [word]}
PWMBuf2 = $312;					{[GLOBAL VAR]  PWM buffer 1 (or 2 if sound) [pointer]}
SoundPtr = $262;				{[GLOBAL VAR] Pointer to four-tone record
   4VE sound definition table [pointer]}
SoundBase = $266;				{[GLOBAL VAR] Pointer to free-form synthesizer buffer
   sound bitMap [pointer]}
SoundVBL = $26A;				{[GLOBAL VAR]  vertical retrace control element [16 bytes]}
SoundDCE = $27A;				{[GLOBAL VAR]  sound driver DCE [pointer]}
SoundActive = $27E;				{[GLOBAL VAR]  sound is active? [byte]}
SoundLevel = $27F;				{[GLOBAL VAR] Amplitude in 740-byte buffer (byte)
   current level in buffer [byte]}
CurPitch = $280;				{[GLOBAL VAR] Value of count in square-wave synthesizer buffer (word)
   current pitch value [word]}
DskVerify = $12C;				{[GLOBAL VAR]  used by 3.5 disk driver for read/verify [byte]}
TagData = $2FA;					{[GLOBAL VAR]  sector tag info for disk drivers [14 bytes]}
BufTgFNum = $2FC;				{[GLOBAL VAR] File tags buffer:  file number (long)
   file number [long]}
BufTgFFlg = $300;				{[GLOBAL VAR] File tags buffer:  flags (word:  bit 1=1 if resource fork) 
   flags [word]}
BufTgFBkNum = $302;				{[GLOBAL VAR] File tags buffer:  logical block number (word)
   logical block number [word]}
BufTgDate = $304;				{[GLOBAL VAR] File tags buffer:  date and time of last modification (long)
   time stamp [word]}
ScrDmpEnb = $2F8;				{[GLOBAL VAR] 0 if GetNextEvent shouldn't process Command-Shift-number combinations (byte)
   screen dump enabled? [byte]}
ScrDmpType = $2F9;				{[GLOBAL VAR]  FF dumps screen, FE dumps front window [byte]}
ScrapVars = $960;				{[GLOBAL VAR]  scrap manager variables [32 bytes]}
ScrapInfo = $960;				{[GLOBAL VAR]  scrap length [long]}
ScrapEnd = $980;				{[GLOBAL VAR]  end of scrap vars}
ScrapTag = $970;				{[GLOBAL VAR]  scrap file name [STRING[15]]}
LaunchFlag = $902;				{[GLOBAL VAR]  from launch or chain [byte]}
SaveSegHandle = $930;			{[GLOBAL VAR]  seg 0 handle [handle]}
CurJTOffset = $934;				{[GLOBAL VAR] Offset to jump table from location pointed to by A5 (word)
   current jump table offset [word]}
CurPageOption = $936;			{[GLOBAL VAR] Sound/screen buffer configuration passed to Chain or Launch (word)
   current page 2 configuration [word]}
LoaderPBlock = $93A;			{[GLOBAL VAR]  param block for ExitToShell [10 bytes]}
CurApRefNum = $900;				{[GLOBAL VAR] Reference number of current application's resource file (word)
   refNum of application's resFile [word]}
CurrentA5 = $904;				{[GLOBAL VAR] Address of boundary between application globals and application parameters
   current value of A5 [pointer]}
CurStackBase = $908;			{[GLOBAL VAR] Address of base of stack; start of application globals
   current stack base [pointer]}
CurApName = $910;				{[GLOBAL VAR] Name of current application (length byte followed by up to 31 characters)
   name of application [STRING[31]]}
LoadTrap = $12D;				{[GLOBAL VAR]  trap before launch? [byte]}
SegHiEnable = $BB2;				{[GLOBAL VAR]  (byte) 0 to disable MoveHHi in LoadSeg}

{ Window Manager Globals }
WindowList = $9D6;				{[GLOBAL VAR] Pointer to first window in window list; 0 if using events but not windows
  Z-ordered linked list of windows [pointer]}
PaintWhite = $9DC;				{[GLOBAL VAR] Flag for whether to paint window white before update event (word)
  erase newly drawn windows? [word]}
WMgrPort = $9DE;				{[GLOBAL VAR] Pointer to Window Manager port 
  window manager's grafport [pointer]}
GrayRgn = $9EE;					{[GLOBAL VAR] Handle to region drawn as desktop
  rounded gray desk region [handle]}
CurActivate = $A64;				{[GLOBAL VAR] Pointer to window to receive activate event
  window slated for activate event [pointer]}
CurDeactive = $A68;				{[GLOBAL VAR] Pointer to window to receive deactivate event
  window slated for deactivate event [pointer]}
DragHook = $9F6;				{[GLOBAL VAR] Address of procedure to execute during TrackGoAway, DragWindow, GrowWindow, DragGrayRgn, TrackControl, and DragControl
  user hook during dragging [pointer]}
DeskPattern = $A3C;				{[GLOBAL VAR] Pattern with which desktop is painted (8 bytes)
  desk pattern [8 bytes]}
DeskHook = $A6C;				{[GLOBAL VAR] Address of procedure for painting desktop or responding to clicks on desktop
  hook for painting the desk [pointer]}
GhostWindow = $A84;				{[GLOBAL VAR] Pointer to window never to be considered frontmost
  window hidden from FrontWindow [pointer]}

{ Text Edit Globals }
TEDoText = $A70;				{[GLOBAL VAR] Address of TextEdit multi-purpose routine
  textEdit doText proc hook [pointer]}
TERecal = $A74;					{[GLOBAL VAR] Address of routine to recalculate line starts for TextEdit
  textEdit recalText proc hook [pointer]}
TEScrapLength = $AB0;			{[GLOBAL VAR] Size in bytes of TextEdit scrap (long)
  textEdit Scrap Length [word]}
TEScrpLength = $AB0;			{[GLOBAL VAR] Size in bytes of TextEdit scrap (long)
  textEdit Scrap Length [word]}
TEScrpHandle = $AB4;			{[GLOBAL VAR] Handle to TextEdit scrap
  textEdit Scrap [handle]}
TEWdBreak = $AF6;				{[GLOBAL VAR] default word break routine [pointer]}
TEWordBreak = $AF6;				{[GLOBAL VAR] default word break routine [pointer]}
WordRedraw = $BA5;				{[GLOBAL VAR] (byte) - used by TextEdit RecalDraw}
TESysJust = $BAC;				{[GLOBAL VAR] (word) system justification (intl. textEdit)      obsolete }
SysDirection = $BAC;			{[GLOBAL VAR] (word) system justification (intl. textEdit)}

{ Resource Manager Globals }
TopMapHndl = $A50;				{[GLOBAL VAR] Handle to resource map of most recently opened resource file
  topmost map in list [handle]}
SysMapHndl = $A54;				{[GLOBAL VAR] Handle to map of system resource file
  system map [handle]}
SysMap = $A58;					{[GLOBAL VAR] Reference number of system resource file (word)
  reference number of system map [word]}
CurMap = $A5A;					{[GLOBAL VAR] Reference number of current resource file (word) 
  reference number of current map [word]}
ResReadOnly = $A5C;				{[GLOBAL VAR] Read only flag [word]}
ResLoad = $A5E;					{[GLOBAL VAR] Current SetResLoad state (word)
  Auto-load feature [word]}
ResErr = $A60;					{[GLOBAL VAR] Current value of ResError (word)
  Resource error code [word]}
ResErrProc = $AF2;				{[GLOBAL VAR] Address of resource error procedure
  Resource error procedure [pointer]}
SysResName = $AD8;				{[GLOBAL VAR] Name of system resource file (length byte followed by up to 19 characters)
  Name of system resource file [STRING[19]]}
RomMapInsert = $B9E;			{[GLOBAL VAR] (byte) determines if we should link in map}
TmpResLoad = $B9F;				{[GLOBAL VAR] second byte is temporary ResLoad value.}

{ Menu Mgr globals }
MBarHeight = $BAA;				{[GLOBAL VAR] height of the menu bar}

{ CommToolbox Global }
CommToolboxGlobals = $0BB4;		{[GLOBAL VAR] pointer to CommToolbox globals }


{$ENDC} { UsingSysEqu }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

