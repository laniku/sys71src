
/************************************************************

Created: Saturday, July 27, 1991 at 6:14 PM
 ROMDefs.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

	   <SM2>	 6/14/93	kc		Roll in Ludwig.
	   <LW2>	 2/24/93	fau		Added the DTS-blessed id's for catIntBus, typXPT and typSIM.
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	  2/5/91	stb		gs: correct case
		 <8>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <7>	 11/7/90	JL		Changed all #defines to anonymous enums.
		 <6>	 7/18/90	jmp		Added various constantes to match CARDS & DRIVERS (2nd Edition),
									and corrected a couple of errors.
		 <5>	  7/2/90	jmp		Added sGammaDir constant.
		 <2>	  1/2/90	BG		Added equates for 68040 identification
	   <1.1>	 11/9/88	CCH		Fixed headers and removed projector resource.
	   <1.0>	 11/9/88	CCH		Adding to EASE.
************************************************************/


#ifndef __ROMDEFS__
#define __ROMDEFS__


enum {

 appleFormat = 1,						/*Format of Declaration Data (IEEE will assign real value)*/
 romRevision = 1,						/*Revision of Declaration Data Format*/
 testPattern = 1519594439,				/*FHeader long word test pattern*/

 sCodeRev = 2,							/*Revision of code (For sExec)*/
 sCPU68000 = 1,							/*CPU type = 68000*/
 sCPU68020 = 2,							/*CPU type = 68020*/
 sCPU68030 = 3,							/*CPU type = 68030*/
 sCPU68040 = 4,							/*CPU type = 68040*/
 sMacOS68000 = 1,						/*Mac OS, CPU type = 68000*/
 sMacOS68020 = 2,						/*Mac OS, CPU type = 68020*/
 sMacOS68030 = 3,						/*Mac OS, CPU type = 68030*/
 sMacOS68040 = 4,						/*Mac OS, CPU type = 68040*/

 board = 0,								/*Board sResource - Required on all boards*/
 displayVideoAppleTFB = 16843009,		/*Video with Apple parameters for TFB card.*/
 displayVideoAppleGM = 16843010,		/*Video with Apple parameters for GM card.*/
 networkEtherNetApple3Com = 33620225,	/*Ethernet with apple parameters for 3-Comm card.*/
 testSimpleAppleAny = -2147417856,		/*A simple test sResource.*/
 endOfList = 255,						/*End of list*/
 defaultTO = 100,						/*100 retries.*/

 sRsrcType = 1							/*Type of sResource*/
};
enum {
 sRsrcName = 2,							/*Name of sResource*/
 sRsrcIcon = 3,							/*Icon*/
 sRsrcDrvrDir = 4,						/*Driver directory*/
 sRsrcLoadDir = 5,						/*Load directory*/
 sRsrcBootRec = 6,						/*sBoot record*/
 sRsrcFlags = 7,						/*sResource Flags*/
 sRsrcHWDevId = 8,						/*Hardware Device Id*/
 minorBaseOS = 10,						/*Offset to base of sResource in minor space.*/
 minorLength = 11,						/*Length of sResource’s address space in standard slot space.*/
 majorBaseOS = 12,						/*Offset to base of sResource in Major space.*/
 majorLength = 13,						/*Length of sResource in super slot space.*/
 sRsrccicn = 15,						/*Color icon*/
 sRsrcicl8 = 16,						/*8-bit (indexed) icon*/
 sRsrcicl4 = 17,						/*4-bit (indexed) icon*/
 sGammaDir = 64,						/*sGamma directory*/
 sDRVRDir = 16,							/*sDriver directory*/

 drSwApple = 1,							/*To ask for or define an Apple-compatible SW device.*/
 drHwTFB = 1,							/*HW ID for the TFB (original Mac II) video card.*/
 drHw3Com = 1,							/*HW ID for the Apple EtherTalk card.*/
 drHwBSC = 3
};
enum {
 catBoard = 1,							/*Category for board types.*/
 catTest = 2,							/*Category for test types -- not used much.*/
 catDisplay = 3,						/*Category for display (video) cards.*/
 catNetwork = 4,						/*Category for Networking cards.*/
 catIntBus = 0xc,						/*Category for Intelligent Busses */

 boardId = 32,							/*Board Id*/
 pRAMInitData = 33,						/*sPRAM init data*/
 primaryInit = 34,						/*Primary init record*/
 timeOutConst = 35,						/*Time out constant*/
 vendorInfo = 36,						/*Vendor information List. See Vendor List, below*/
 boardFlags = 37,						/*Board Flags*/
 secondaryInit = 38,					/*Secondary init record/code*/
 sRsrcVidNames = 65,					/*Video mode name directory*/

 vendorId = 1,							/*Vendor Id*/
 serialNum = 2,							/*Serial number*/
 revLevel = 3,							/*Revision level*/
 partNum = 4,							/*Part number*/
 date = 5,								/*Last revision date of the card*/

 typeBoard = 0,							/*Type for board types.*/
 typeApple = 1,
 typeVideo = 1,							/*Type for video types.*/
 typeXPT = 0xb,							/* Type for Transport (SCSI) types */
 typeSIM = 0xc							/* Type for SCSI SIMs */
};
enum {
 typeEtherNet = 1,						/*Type for ethernet types.*/
 testByte = 32,							/*Test byte.*/
 testWord = 33,							/*0021*/
 testLong = 34,							/*Test Long.*/
 testString = 35						/*Test String.*/
};


#endif
