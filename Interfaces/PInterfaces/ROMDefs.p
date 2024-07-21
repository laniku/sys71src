
{
Created: Saturday, July 27, 1991 at 11:16 PM
 ROMDefs.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

	Change History (most recent first):

	   <SM2>	 6/14/93	kc		Roll in Ludwig.
	   <LW2>	 2/24/93	fau		Added the DTS-blessed id's for typXPT, typSIM, and catIntBus.
		 <6>	 7/31/91	JL		Updated Copyright.
		 <5>	  2/4/91	JL		Changed spelling of sRsrccicn, sRsrcicl8, sRsrcicl4 to
									sRsrccicn, sRsrcicl8, sRsrcicl4 to match the documentation.
		 <4>	 1/28/91	LN		Checked in Database Generated File from DSG. Match .h file.
		 <3>	  1/2/90	CD		Removed duplicate definition of sMacOS68020
		 <2>	  1/2/90	BG		Added equates for 68040 identification
	   <1.0>	11/17/88	CCH		Adding to EASE.

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT ROMDefs;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingROMDefs}
{$SETC UsingROMDefs := 1}


CONST
appleFormat = 1;						{Format of Declaration Data (IEEE will assign real value)}
romRevision = 1;						{Revision of Declaration Data Format}
testPattern = 1519594439;				{FHeader long word test pattern}

sCodeRev = 2;							{Revision of code (For sExec)}
sCPU68000 = 1;							{CPU type = 68000}
sCPU68020 = 2;							{CPU type = 68020}
sCPU68030 = 3;							{CPU type = 68030}
sCPU68040 = 4;							{CPU type = 68040}
sMacOS68000 = 1;						{Mac OS, CPU type = 68000}
sMacOS68020 = 2;						{Mac OS, CPU type = 68020}
sMacOS68030 = 3;						{Mac OS, CPU type = 68030}
sMacOS68040 = 4;						{Mac OS, CPU type = 68040}

board = 0;								{Board sResource - Required on all boards}
displayVideoAppleTFB = 16843009;		{Video with Apple parameters for TFB card.}
displayVideoAppleGM = 16843010;			{Video with Apple parameters for GM card.}
networkEtherNetApple3Com = 33620225;	{Ethernet with apple parameters for 3-Comm card.}
testSimpleAppleAny = -2147417856;		{A simple test sResource.}
endOfList = 255;						{End of list}
defaultTO = 100;						{100 retries.}

sRsrcType = 1;							{Type of sResource}
sRsrcName = 2;							{Name of sResource}
sRsrcIcon = 3;							{Icon}
sRsrcDrvrDir = 4;						{Driver directory}
sRsrcLoadDir = 5;						{Load directory}
sRsrcBootRec = 6;						{sBoot record}
sRsrcFlags = 7;							{sResource Flags}
sRsrcHWDevId = 8;						{Hardware Device Id}
minorBaseOS = 10;						{Offset to base of sResource in minor space.}
minorLength = 11;						{Length of sResource’s address space in standard slot space.}
majorBaseOS = 12;						{Offset to base of sResource in Major space.}
majorLength = 13;						{Length of sResource in super slot space.}
sRsrccicn = 15;							{Color icon}
sRsrcicl8 = 16;							{8-bit (indexed) icon}
sRsrcicl4 = 17;							{4-bit (indexed) icon}
sGammaDir = 64;							{sGamma directory}
sDRVRDir = 16;							{sDriver directory}

drSwApple = 1;							{To ask for or define an Apple-compatible SW device.}
drHwTFB = 1;							{HW ID for the TFB (original Mac II) video card.}
drHw3Com = 1;							{HW ID for the Apple EtherTalk card.}
drHwBSC = 3;
catBoard = 1;							{Category for board types.}
catTest = 2;							{Category for test types -- not used much.}
catDisplay = 3;							{Category for display (video) cards.}
catNetwork = 4;							{Category for Networking cards.}
catIntBus = 11;							{Category for Intelligent busses.}

boardId = 32;							{Board Id}
pRAMInitData = 33;						{sPRAM init data}
primaryInit = 34;						{Primary init record}
timeOutConst = 35;						{Time out constant}
vendorInfo = 36;						{Vendor information List. See Vendor List, below}
boardFlags = 37;						{Board Flags}
secondaryInit = 38;						{Secondary init record/code}
sRsrcVidNames = 65;						{Video mode name directory}

vendorId = 1;							{Vendor Id}
serialNum = 2;							{Serial number}
revLevel = 3;							{Revision level}
partNum = 4;							{Part number}
date = 5;								{Last revision date of the card}

typeBoard = 0;							{Type for board types.}
typeApple = 1;
typeVideo = 1;							{Type for video types.}
typeEtherNet = 1;						{Type for ethernet types.}
typeXPT=11;								{Type for SCSI Transport types.}
typeSIM=12;								{Type for SCSI SIM Types.}
testByte = 32;							{Test byte.}
testWord = 33;							{0021}
testLong = 34;							{Test Long.}
testString = 35;						{Test String.}


{$ENDC} { UsingROMDefs }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

