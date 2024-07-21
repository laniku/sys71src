/************************************************************

Created: Friday, August 2, 1991 at 3:45 PM
 RTLib.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1990-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Updated copyright. Standardizing the file to meet ANSI and DSG
									standards.

	To Do:
************************************************************/

#ifndef __RTLib__
#define __RTLib__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*		Error Codes		*/

enum { eRTNoErr=0, eRTBadVersion=2, eRTInvalidOp=4, eRTInvalidJTPtr=6 };


/*		Action Codes		*/

enum { kRTSysErr=0, kRTRetry=1, kRTContinue=2 };


/*		Runtime Operations		*/

enum	{	kRTGetVersion=10,		kRTGetVersionA5=11,
		 	kRTGetJTAddress=12,	kRTGetJTAddressA5=13,
		 	kRTSetPreLoad=14,		kRTSetPreLoadA5=15,
		 	kRTSetSegLoadErr=16,	kRTSetSegLoadErrA5=17,
		 	kRTSetPostLoad=18,	kRTSetPostLoadA5=19,
		 	kRTSetPreUnload=20,	kRTSetPreUnloadA5=21,
		 	kRTPreLaunch=22,		kRTPostLaunch=23
		};


/*		Version and Jump Table Entry Address Parameters		*/

struct RTGetVersionParam {
	unsigned short	fVersion;
};

typedef struct RTGetVersionParam RTGetVersionParam;


struct RTGetJTAddrParam {
	void*	fJTAddr;
	void*	fCodeAddr;
};

typedef struct RTGetJTAddrParam RTGetJTAddrParam;


/*		RTState Definition		*/

struct RTState {
	unsigned short	fVersion;				/* run-time version */
	void*				fSP;						/* SP: &-of user return address */
	void*				fJTAddr;					/* PC: &-of called jump table entry */
	long				fRegisters[15];		/* registers D0-D7 and A0-A6 when */
													/*		_LoadSeg was called */
	short				fSegNo;					/*	segment number */
	ResType			fSegType;				/*	segment type (normally 'CODE') */
	long				fSegSize;				/*	segment size */
	Boolean			fSegInCore;				/*	true if segment is in memory */
	Boolean			fReserved1;				/* (reserved for future use) */
	OSErr				fOSErr;					/*	error number */
	long				fReserved2;				/* (reserved for future use) */
};

typedef struct RTState RTState;


/*		Version Definitions		*/

#define	kVersion32bit			0xFFFF			
#define	kVersion16bit			0x0000					


/*		User Handler Definition		*/

typedef pascal short (*SegLoadHdlrPtr) (RTState* state);


/*		Segment Loader Hook Parameters		*/

struct RTSetSegLoadParam {
	SegLoadHdlrPtr	fUserHdlr;
	SegLoadHdlrPtr	fOldUserHdlr;
};

typedef struct RTSetSegLoadParam RTSetSegLoadParam;


/*		Runtime Parameter Block		*/

struct RTPB {
	short	fOperation;
	void*	fA5;
	union	{
		RTGetVersionParam	fVersionParam;
		RTGetJTAddrParam	fJTAddrParam;
		RTSetSegLoadParam	fSegLoadParam;
	} fRTParam;
};

typedef struct RTPB RTPB;

pascal OSErr Runtime (RTPB* runtime_parms);


#ifdef __cplusplus
}
#endif

#endif	/* __RTLib__ */

