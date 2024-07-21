
/************************************************************

Created: Saturday, July 27, 1991 at 6:39 PM
 SCSI.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

	   <SM2>	 5/29/93	PW		Adding sbMac constant and rearranged a little more logically.
		 <6>	 7/31/91	JL		Updated Copyright.
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <4>	 11/7/90	JL		Changed all #defines to anonymous enums

	To Do:
************************************************************/


#ifndef __SCSI__
#define __SCSI__

#ifndef __TYPES__
#include <Types.h>
#endif

/* TIB opcodes */

enum {
 scInc	= 1,
 scNoInc= 2,
 scAdd	= 3,
 scMove	= 4,
 scLoop	= 5,
 scNop	= 6,
 scStop	= 7,
 scComp	= 8
};

/* SCSI Manager errors */

enum {
 scCommErr		= 2,				/*communications error, operation timeout*/
 scArbNBErr		= 3,				/*arbitration timeout waiting for not BSY*/
 scBadParmsErr	= 4,				/*bad parameter or TIB opcode*/
 scPhaseErr		= 5,				/*SCSI bus not in correct phase for attempted operation*/
 scCompareErr	= 6,				/*data compare error*/
 scMgrBusyErr	= 7,				/*SCSI Manager busy */
 scSequenceErr	= 8,				/*attempted operation is out of sequence*/
 scBusTOErr		= 9,				/*CPU bus timeout*/
 scComplPhaseErr= 10				/*SCSI bus wasn't in Status phase*/
};


/* Driver Descriptor Map */

/*	signature word for Block 0 */
#define sbSIGWord 0x4552
/*	system type for Mac */
#define sbMac 1

struct Block0 {
 unsigned short sbSig;				/*unique value for SCSI block 0*/
 unsigned short sbBlkSize;			/*block size of device*/
 unsigned long sbBlkCount;			/*number of blocks on device*/
 unsigned short sbDevType;			/*device type*/
 unsigned short sbDevId;			/*device id*/
 unsigned long sbData;				/*not used*/
 unsigned short sbDrvrCount;		/*driver descriptor count*/
 unsigned long ddBlock;				/*1st driver's starting block*/
 unsigned short ddSize;				/*size of 1st driver (512-byte blks)*/
 unsigned short ddType;				/*system type (1 for Mac+)*/
 unsigned short ddPad[243];			/*ARRAY[0..242] OF INTEGER; not used*/
};
typedef struct Block0 Block0;


/* Partition Map Entry */

/* OLD partition map signature */
#define pdSigWord 0x5453
#define oldPMSigWord pdSigWord

/* NEW partition map signature */
#define pMapSIG  0x504D
#define newPMSigWord pMapSIG

struct Partition {
 unsigned short pmSig;				/*unique value for map entry blk*/
 unsigned short pmSigPad;			/*currently unused*/
 unsigned long pmMapBlkCnt;			/*# of blks in partition map*/
 unsigned long pmPyPartStart;		/*physical start blk of partition*/
 unsigned long pmPartBlkCnt;		/*# of blks in this partition*/
 unsigned char pmPartName[32];		/*ASCII partition name*/
 unsigned char pmParType[32];		/*ASCII partition type*/
 unsigned long pmLgDataStart;		/*log. # of partition's 1st data blk*/
 unsigned long pmDataCnt;			/*# of blks in partition's data area*/
 unsigned long pmPartStatus;		/*bit field for partition status*/
 unsigned long pmLgBootStart;		/*log. blk of partition's boot code*/
 unsigned long pmBootSize;			/*number of bytes in boot code*/
 unsigned long pmBootAddr;			/*memory load address of boot code*/
 unsigned long pmBootAddr2;			/*currently unused*/
 unsigned long pmBootEntry;			/*entry point of boot code*/
 unsigned long pmBootEntry2;		/*currently unused*/
 unsigned long pmBootCksum;			/*checksum of boot code*/
 unsigned char pmProcessor[16];		/*ASCII for the processor type*/
 unsigned short pmPad[188];			/*512 bytes long currently unused*/
};
typedef struct Partition Partition;


/* TIB instruction */

struct SCSIInstr {
 unsigned short scOpcode;
 unsigned long scParam1;
 unsigned long scParam2;
};

typedef struct SCSIInstr SCSIInstr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr SCSIReset(void)
 = {0x4267,0xA815}; 
pascal OSErr SCSIGet(void)
 = {0x3F3C,0x0001,0xA815}; 
pascal OSErr SCSISelect(short targetID)
 = {0x3F3C,0x0002,0xA815}; 
pascal OSErr SCSICmd(Ptr buffer,short count)
 = {0x3F3C,0x0003,0xA815}; 
pascal OSErr SCSIRead(Ptr tibPtr)
 = {0x3F3C,0x0005,0xA815}; 
pascal OSErr SCSIRBlind(Ptr tibPtr)
 = {0x3F3C,0x0008,0xA815}; 
pascal OSErr SCSIWrite(Ptr tibPtr)
 = {0x3F3C,0x0006,0xA815}; 
pascal OSErr SCSIWBlind(Ptr tibPtr)
 = {0x3F3C,0x0009,0xA815}; 
pascal OSErr SCSIComplete(short *stat,short *message,unsigned long wait)
 = {0x3F3C,0x0004,0xA815}; 
pascal short SCSIStat(void)
 = {0x3F3C,0x000A,0xA815}; 
pascal OSErr SCSISelAtn(short targetID)
 = {0x3F3C,0x000B,0xA815}; 
pascal OSErr SCSIMsgIn(short *message)
 = {0x3F3C,0x000C,0xA815}; 
pascal OSErr SCSIMsgOut(short message)
 = {0x3F3C,0x000D,0xA815}; 
#ifdef __cplusplus
}
#endif

#endif
