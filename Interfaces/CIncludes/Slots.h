
/************************************************************

Created: Saturday, July 27, 1991 at 6:43 PM
 Slots.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved

	Change History (most recent first):

		<11>	 3/23/92	JSM		OSEvents.h is obsolete, use Events.h instead.
		<10>	 7/31/91	JL		Updated Copyright.
		 <9>	  2/4/91	JL		changed aSync parameter names to async.
		 <8>	 1/27/91	LN		Checked in Database generate file from DSG. changed
									OpenSlotASync to OpenSlotAsync to be consistent with others.
		 <7>	 1/23/91	stb		BBM: change spParamData in SpBlock type from Ptr to a LONGINT;
									fix selectors 8,9,A,B,C,1D.
		 <6>	12/14/90	dba		<JDR> define inlines for some calls that were missing them
		 <5>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <4>	10/21/90	gbm		(with dba) Made compatible with 3.2 C compiler (and incompatible
									with previous compilers).
		 <4>	10/10/90	JAL		New style #Pragma Parameters for MPW 3.2 C
		 <3>	 4/16/90	djw		Add new slot manager definitions

	To Do:
************************************************************/


#ifndef __SLOTS__
#define __SLOTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


enum {

 fCardIsChanged = 1,			/*Card is Changed field in StatusFlags field of sInfoArray*/
 fCkForSame = 0,				/*For SearchSRT. Flag to check for SAME sResource in the table. */
 fCkForNext = 1,				/*For SearchSRT. Flag to check for NEXT sResource in the table. */
 fWarmStart = 2,				/*If this bit is set then warm start else cold start.*/

 stateNil = 0,					/*State*/
 stateSDMInit = 1,				/*:Slot declaration manager Init*/
 statePRAMInit = 2,				/*:sPRAM record init*/
 statePInit = 3,				/*:Primary init*/
 stateSInit = 4,				/*:Secondary init*/

/* flags for spParamData */
 fall = 0,						/* bit 0: set=search enabled/disabled sRsrc's */
 foneslot = 1,					/*    1: set=search sRsrc's in given slot only */
 fnext = 2						/*    2: set=search for next sRsrc */
};

struct SlotIntQElement {
 Ptr sqLink;					/*ptr to next element*/
 short sqType;					/*queue type ID for validity*/
 short sqPrio;					/*priority*/
 ProcPtr sqAddr;				/*interrupt service routine*/
 long sqParm;					/*optional A1 parameter*/
};

typedef struct SlotIntQElement SlotIntQElement;
typedef SlotIntQElement *SQElemPtr;

struct SpBlock {
 long spResult;					/*FUNCTION Result*/
 Ptr spsPointer;				/*structure pointer*/
 long spSize;					/*size of structure*/
 long spOffsetData;				/*offset/data field used by sOffsetData*/
 Ptr spIOFileName;				/*ptr to IOFile name for sDisDrvrName*/
 Ptr spsExecPBlk;				/*pointer to sExec parameter block.*/
 long spParamData;				/*misc parameter data (formerly spStackPtr).*/
 long spMisc;					/*misc field for SDM.*/
 long spReserved;				/*reserved for future expansion*/
 short spIOReserved;			/*Reserved field of Slot Resource Table*/
 short spRefNum;				/*RefNum*/
 short spCategory;				/*sType: Category*/
 short spCType;					/*Type*/
 short spDrvrSW;				/*DrvrSW*/
 short spDrvrHW;				/*DrvrHW*/
 char spTBMask;					/*type bit mask bits 0..3 mask words 0..3*/
 char spSlot;					/*slot number*/
 char spID;						/*structure ID*/
 char spExtDev;					/*ID of the external device*/
 char spHwDev;					/*Id of the hardware device.*/
 char spByteLanes;				/*bytelanes from card ROM format block*/
 char spFlags;					/*standard flags*/
 char spKey;					/*Internal use only*/
};

typedef struct SpBlock SpBlock;
typedef SpBlock *SpBlockPtr;

struct SInfoRecord {
 Ptr siDirPtr;					/*Pointer to directory*/
 short siInitStatusA;			/*initialization E*/
 short siInitStatusV;			/*status returned by vendor init code*/
 char siState;					/*initialization state*/
 char siCPUByteLanes;			/*0=[d0..d7] 1=[d8..d15]*/
 char siTopOfROM;				/*Top of ROM= $FssFFFFx: x is TopOfROM*/
 char siStatusFlags;			/*bit 0 - card is changed*/
 short siTOConst;				/*Time Out C for BusErr*/
 char siReserved[2];			/*reserved*/
 Ptr siROMAddr;					/* addr of top of ROM */
 char siSlot;					/* slot number */
 char siPadding[3];				/* reserved */
};

typedef struct SInfoRecord SInfoRecord;
typedef SInfoRecord *SInfoRecPtr;

struct SDMRecord {
 ProcPtr sdBEVSave;				/*Save old BusErr vector*/
 ProcPtr sdBusErrProc;			/*Go here to determine if it is a BusErr*/
 ProcPtr sdErrorEntry;			/*Go here if BusErrProc finds real BusErr*/
 long sdReserved;				/*Reserved*/
};

typedef struct SDMRecord SDMRecord;

struct FHeaderRec {
 long fhDirOffset;				/*offset to directory*/
 long fhLength;					/*length of ROM*/
 long fhCRC;					/*CRC*/
 char fhROMRev;					/*revision of ROM*/
 char fhFormat;					/*format - 2*/
 long fhTstPat;					/*test pattern*/
 char fhReserved;				/*reserved*/
 char fhByteLanes;				/*ByteLanes*/
};

typedef struct FHeaderRec FHeaderRec;
typedef FHeaderRec *FHeaderRecPtr;

struct SEBlock {
 unsigned char seSlot;			/*Slot number.*/
 unsigned char sesRsrcId;		/*sResource Id.*/
 short seStatus;				/*Status of code executed by sExec.*/
 unsigned char seFlags;			/*Flags*/
 unsigned char seFiller0;		/*Filler, must be SignedByte to align on odd boundry*/
 unsigned char seFiller1;		/*Filler*/
 unsigned char seFiller2;		/*Filler*/
 long seResult;					/*Result of sLoad.*/
 long seIOFileName;				/*Pointer to IOFile name.*/
 unsigned char seDevice;		/*Which device to read from.*/
 unsigned char sePartition;		/*The partition.*/
 unsigned char seOSType;		/*Type of OS.*/
 unsigned char seReserved;		/*Reserved field.*/
 unsigned char seRefNum;		/*RefNum of the driver.*/
 unsigned char seNumDevices;	/* Number of devices to load.*/
 unsigned char seBootState;		/*State of StartBoot code.*/
};

typedef struct SEBlock SEBlock;


#ifdef __cplusplus
extern "C" {
#endif
/*  Principle  */
#pragma parameter __D0 SReadByte(__A0)
pascal OSErr SReadByte(SpBlockPtr spBlkPtr)
 = {0x7000,0xA06E}; 
#pragma parameter __D0 SReadWord(__A0)
pascal OSErr SReadWord(SpBlockPtr spBlkPtr)
 = {0x7001,0xA06E}; 
#pragma parameter __D0 SReadLong(__A0)
pascal OSErr SReadLong(SpBlockPtr spBlkPtr)
 = {0x7002,0xA06E}; 
#pragma parameter __D0 SGetCString(__A0)
pascal OSErr SGetCString(SpBlockPtr spBlkPtr)
 = {0x7003,0xA06E}; 
#pragma parameter __D0 SGetBlock(__A0)
pascal OSErr SGetBlock(SpBlockPtr spBlkPtr)
 = {0x7005,0xA06E}; 
#pragma parameter __D0 SFindStruct(__A0)
pascal OSErr SFindStruct(SpBlockPtr spBlkPtr)
 = {0x7006,0xA06E}; 
#pragma parameter __D0 SReadStruct(__A0)
pascal OSErr SReadStruct(SpBlockPtr spBlkPtr)
 = {0x7007,0xA06E}; 

/*  Special  */
#pragma parameter __D0 SReadInfo(__A0)
pascal OSErr SReadInfo(SpBlockPtr spBlkPtr)
 = {0x7010,0xA06E}; 
#pragma parameter __D0 SReadPRAMRec(__A0)
pascal OSErr SReadPRAMRec(SpBlockPtr spBlkPtr)
 = {0x7011,0xA06E}; 
#pragma parameter __D0 SPutPRAMRec(__A0)
pascal OSErr SPutPRAMRec(SpBlockPtr spBlkPtr)
 = {0x7012,0xA06E}; 
#pragma parameter __D0 SReadFHeader(__A0)
pascal OSErr SReadFHeader(SpBlockPtr spBlkPtr)
 = {0x7013,0xA06E}; 
#pragma parameter __D0 SNextSRsrc(__A0)
pascal OSErr SNextSRsrc(SpBlockPtr spBlkPtr)
 = {0x7014,0xA06E}; 
#pragma parameter __D0 SNextTypeSRsrc(__A0)
pascal OSErr SNextTypeSRsrc(SpBlockPtr spBlkPtr)
 = {0x7015,0xA06E}; 
#pragma parameter __D0 SRsrcInfo(__A0)
pascal OSErr SRsrcInfo(SpBlockPtr spBlkPtr)
 = {0x7016,0xA06E}; 
#pragma parameter __D0 SCkCardStat(__A0)
pascal OSErr SCkCardStat(SpBlockPtr spBlkPtr)
 = {0x7018,0xA06E}; 
#pragma parameter __D0 SReadDrvrName(__A0)
pascal OSErr SReadDrvrName(SpBlockPtr spBlkPtr)
 = {0x7019,0xA06E}; 
#pragma parameter __D0 SFindDevBase(__A0)
pascal OSErr SFindDevBase(SpBlockPtr spBlkPtr)
 = {0x701B,0xA06E}; 
#pragma parameter __D0 SFindBigDevBase(__A0)
pascal OSErr SFindBigDevBase(SpBlockPtr spBlkPtr)
 = {0x701C,0xA06E}; 

/*  Advanced  */
#pragma parameter __D0 InitSDeclMgr(__A0)
pascal OSErr InitSDeclMgr(SpBlockPtr spBlkPtr)
 = {0x7020,0xA06E}; 
#pragma parameter __D0 SPrimaryInit(__A0)
pascal OSErr SPrimaryInit(SpBlockPtr spBlkPtr)
 = {0x7021,0xA06E}; 
#pragma parameter __D0 SCardChanged(__A0)
pascal OSErr SCardChanged(SpBlockPtr spBlkPtr)
 = {0x7022,0xA06E}; 
#pragma parameter __D0 SExec(__A0)
pascal OSErr SExec(SpBlockPtr spBlkPtr)
 = {0x7023,0xA06E}; 
#pragma parameter __D0 SOffsetData(__A0)
pascal OSErr SOffsetData(SpBlockPtr spBlkPtr)
 = {0x7024,0xA06E}; 
#pragma parameter __D0 SInitPRAMRecs(__A0)
pascal OSErr SInitPRAMRecs(SpBlockPtr spBlkPtr)
 = {0x7025,0xA06E}; 
#pragma parameter __D0 SReadPBSize(__A0)
pascal OSErr SReadPBSize(SpBlockPtr spBlkPtr)
 = {0x7026,0xA06E}; 
#pragma parameter __D0 SCalcStep(__A0)
pascal OSErr SCalcStep(SpBlockPtr spBlkPtr)
 = {0x7028,0xA06E}; 
#pragma parameter __D0 SInitSRsrcTable(__A0)
pascal OSErr SInitSRsrcTable(SpBlockPtr spBlkPtr)
 = {0x7029,0xA06E}; 
#pragma parameter __D0 SSearchSRT(__A0)
pascal OSErr SSearchSRT(SpBlockPtr spBlkPtr)
 = {0x702A,0xA06E}; 
#pragma parameter __D0 SUpdateSRT(__A0)
pascal OSErr SUpdateSRT(SpBlockPtr spBlkPtr)
 = {0x702B,0xA06E}; 
#pragma parameter __D0 SCalcSPointer(__A0)
pascal OSErr SCalcSPointer(SpBlockPtr spBlkPtr)
 = {0x702C,0xA06E}; 
#pragma parameter __D0 SGetDriver(__A0)
pascal OSErr SGetDriver(SpBlockPtr spBlkPtr)
 = {0x702D,0xA06E}; 
#pragma parameter __D0 SPtrToSlot(__A0)
pascal OSErr SPtrToSlot(SpBlockPtr spBlkPtr)
 = {0x702E,0xA06E}; 
#pragma parameter __D0 SFindSInfoRecPtr(__A0)
pascal OSErr SFindSInfoRecPtr(SpBlockPtr spBlkPtr)
 = {0x702F,0xA06E}; 
#pragma parameter __D0 SFindSRsrcPtr(__A0)
pascal OSErr SFindSRsrcPtr(SpBlockPtr spBlkPtr)
 = {0x7030,0xA06E}; 
#pragma parameter __D0 SDeleteSRTRec(__A0)
pascal OSErr SDeleteSRTRec(SpBlockPtr spBlkPtr)
 = {0x7031,0xA06E}; 

pascal OSErr OpenSlot(ParmBlkPtr paramBlock,Boolean async); 
#pragma parameter __D0 OpenSlotSync(__A0)
pascal OSErr OpenSlotSync(ParmBlkPtr paramBlock)
 = 0xA200; 
#pragma parameter __D0 OpenSlotAsync(__A0)
pascal OSErr OpenSlotAsync(ParmBlkPtr paramBlock)
 = 0xA600; 

/*  Device Manager Slot Support  */
#pragma parameter __D0 SIntInstall(__A0,__D0)
pascal OSErr SIntInstall(SQElemPtr sIntQElemPtr,short theSlot)
 = 0xA075; 
#pragma parameter __D0 SIntRemove(__A0,__D0)
pascal OSErr SIntRemove(SQElemPtr sIntQElemPtr,short theSlot)
 = 0xA076; 

#pragma parameter __D0 SVersion(__A0)
pascal OSErr SVersion(SpBlockPtr spBlkPtr)
 = {0x7008,0xA06E}; 
#pragma parameter __D0 SetSRsrcState(__A0)
pascal OSErr SetSRsrcState(SpBlockPtr spBlkPtr)
 = {0x7009,0xA06E}; 
#pragma parameter __D0 InsertSRTRec(__A0)
pascal OSErr InsertSRTRec(SpBlockPtr spBlkPtr)
 = {0x700A,0xA06E}; 
#pragma parameter __D0 SGetSRsrc(__A0)
pascal OSErr SGetSRsrc(SpBlockPtr spBlkPtr)
 = {0x700B,0xA06E}; 
#pragma parameter __D0 SGetTypeSRsrc(__A0)
pascal OSErr SGetTypeSRsrc(SpBlockPtr spBlkPtr)
 = {0x700C,0xA06E}; 
#pragma parameter __D0 SGetSRsrcPtr(__A0)
pascal OSErr SGetSRsrcPtr(SpBlockPtr spBlkPtr)
 = {0x701D,0xA06E}; 
#ifdef __cplusplus
}
#endif

#endif
