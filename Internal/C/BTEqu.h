/*
	File:		BTEqu.h

	Contains:	B*Tree Manager equates

	Written by:	Kenny SC. Tung

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <9>	11/20/91	KST		Adding assert "__BTequ__".
		 <8>	  8/3/90	KST		Adding a new field ioBTWriteFlag in BTioParam structure.
		 <7>	 7/17/90	KST		btRsrvedErr is no longer used.
		 <6>	 7/17/90	KST		Adding 2 error codes -428 and -429.
		 <5>	  7/6/90	KST		Changing maxKeyLen from 127 to 129 per AppleMail request.
		 <4>	  4/4/90	KST		Adding new error code -- "btDepthErr".
		 <3>	 3/29/90	KST		Adding a new field ioBTKCProc in BTioParam. adding a new error
									code, and updated BTree glue codes.
		 <2>	 2/22/90	KST		Adding a new field "ioBTDataSize" in BTioParam.
		 <1>	 2/21/90	HJR		Moved from Interfaces:CIncludes to Internal:C.
		 <3>	  2/6/90	KST		Adding a new call, BTUpdateKD.
		 <2>	  2/6/90	KST		Adding glue code.
	   <1.3>	11/22/89	KST		Changed B*Tree error code from -400 to -410.
	   <1.2>	 9/18/89	KST		added a new kdDTString type.
	   <1.1>	 6/15/89	KST		Includes Files.h if __FILES__ undefined.
	   <1.0>	 6/15/89	KST		Added BTreeEqu.h file.

	To Do:
*/


#ifndef __FILES__
#include <files.h>
#endif

#ifndef __BTEQU__
#define __BTEQU__

#define		caseSens	0x10		/* case sensitive = 16 */
#define		diacNsens	0x20		/* diac not sensitive = 32 */

/* key descriptor */
#define		kdSkip			0
#define		kdByte			1	/* unsigned */
#define		kdWord			4	/* unsigned */
#define		kdLong			6	/* unsigned */
#define		kdSignedByte	2	/* signed */
#define		kdSignedWord	5	/* signed */
#define		kdSignedLong	7	/* signed */
#define		kdString		3
#define		kdFLString		8	/* fixed length string */
#define		kdDTString		9	/* replace default key for DTDB */
#define		kdUseKCProc		10	/* always uses key comparison procedure	<28Mar90> */

typedef struct BTParam {
    ParamBlockHeader
	short	ioRefNum;		/* 24 */
	short	ioBTNodeSize;	/* 26 */
	short	ioBTMaxKLen;	/* 28 */
	short	ioBTDepth;		/* 30 */
	long	ioBTRecNum;		/* 32 */
	long	ioBTNNodes;		/* 36 */
	long	ioBTFreeNode;	/* 40 */
	long	ioBTClumpSize;	/* 44 */
	long	ioDirID;		/* 48 */
	Ptr		ioBTKDPtr;		/* 52 */
	short	ioBTKDReqCount;	/* 56 */
	short	ioBTKDActCount;	/* 58 */
} BTParam;

typedef struct BTIOParam {
    ParamBlockHeader
	short	ioRefNum;		/* 24 */
	char	ioBTWriteFlag;	/* 26 used by BTFlush only */
	char	ioPermssn;		/* 27 */
	Ptr		ioMisc;			/* 28 */
	Ptr		ioBuffer;		/* 32 */
	long	ioReqCount;		/* 36 */
	long	ioActCount;		/* 40 */
	Ptr		ioBTKeyPtr;		/* 44 */
	long	ioDirID;		/* 48 don't move above this */
	long	ioBTHint1;		/* 52 */
	long	ioBTHint2;		/* 56 */
	short	ioBTHint3;		/* 60 */
	short	ioBTHint4;		/* 62 reserved */
	long	ioBTHint5;		/* 64 reserved */
	short	ioBTPosMode;	/* 68 */
	short	ioKReqCount;	/* 70 */
	short	ioKActCount;	/* 72 */
	long	ioBTRsrvUID;	/* 74 */
	long	ioBTDataSize;	/* 78 */
	Ptr		ioBTKCProc;		/* 82 */	/* only used by BTOpen, this will override KD */
} BTioParam;


#define		kdMaxLen		24
#define		MaxKeyLen		129			/* doesn't include length byte */

/* error code */
#define		notBTree		-410
#define		btBadNode		-411
#define		btSizeErr		-412
#define		btNoSpace		-413
#define		btDupRecErr		-414
#define		btRecNotFnd		-415
#define		btKeyLenErr		-416
#define		btKeyAttrErr	-417
#define 	btKeyFdErr		-418
#define 	btPMInvalid		-419
#define 	btKDLenErr		-420
#define 	btKDTypeErr		-421
#define		btBadUIDErr		-422

#define		btNoKDErr		-424			/* no key descriptor in the header */
#define		btDepthErr		-425			/* tree depth > maxDepth		<04Apr90> */
#define		btNoKCProcErr	-426			/* no Key Comp procedure error	<28Mar90> */
#define		btVersionErr	-427			/* Btree version error (for future release) */
#define		btEofErr		-428			/* BTGetRec reading beyond EOF */
#define		btBofErr		-429			/* BTGetRec reading before BOF */

#ifdef __safe_link
extern "C" {
#endif
pascal short BTInit		 (BTParam   *btparam,   short async);
pascal short BTOpen		 (BTioParam *btioparam, short async);
pascal short BTClose	 (BTioParam *btioparam, short async);
pascal short BTInsRec	 (BTioParam *btioparam, short async);
pascal short BTSetRec	 (BTioParam *btioparam, short async);
pascal short BTReplRec	 (BTioParam *btioparam, short async);
pascal short BTSearch	 (BTioParam *btioparam, short async);
pascal short BTGetRec	 (BTioParam *btioparam, short async);
pascal short BTDelete	 (BTioParam *btioparam, short async);
pascal short BTGetInfo	 (BTParam   *btparam,   short async);
pascal short BTFlush	 (BTioParam *btioparam, short async);
pascal short BTCleanUp	 (BTioParam *btioparam, short async);
pascal short BTRsrvAccess(BTioParam *btioparam, short async);
pascal short BTRelAccess (BTioParam *btioparam, short async);
pascal short BTGetUid 	 (BTioParam *btioparam, short async);
pascal short BTUpdateKD	 (BTParam   *btparam,   short async);
#ifdef __safe_link
}
#endif

#endif