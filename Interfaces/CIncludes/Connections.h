/************************************************************
	Connections.h
	C Interface to the Connection Manager

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		<17>	10/30/91	BH		CMStatus's parameter of type CMBufferSizes * changed to
									CMBufferSizes.  This does not change code generated, but
									conforms to handling of Str255's [e.g. _GetIndString]
		<16>	 8/27/91	CH		Updated interface headers for consistency.
		<15>	 8/20/91	BH		remove CMSetupCleanup from public interfaces
		<14>	 7/25/91	JL		Checked in database generated file from DSG. Changed param type
									of CMStatus from a
									CMBufferSizes to a *CMBufferSizes to match Pascal.  Made flags
									unsigned types.
		<13>	  7/2/91	BH		added application procptr definitions
		<12>	 6/25/91	JNG		Finish Adding 1.1 stuff
		<12>	 6/25/91	JNG		Finish adding 1.1 stuff
		<11>	 6/18/91	JL		Restoring constCMBufferSizesParameter as ConstCMBufferSizesParam
									to be consistent with other similar types like ConstStr255Param.
									Also restored parameter types of Void * to replace generic Ptr
									types and ConstStr255Param to replace const str255 types. Also
									changed // comments that BH just added to the ANSI standard.
		<10>	 6/18/91	BH		move 1.1 stuff here
		 <9>	 6/17/91	JL		Checked in official MPW 3.2Ä version. Temporarily removed
									constCMBufferSizesParameter declaration to make the file match
									the shipped version. Temporarily changed parameter types with
									Void * back to Ptr and ConstStr255Param to const str255 to make
									the file match the shipped version. Restored function parameter
									names taken out by Darin. Added the word "extern" to the
									cplusplus conditional. Updated header (first 6 lines of this
									file) to match shipped version.
		 <8>	 1/14/91	CP		Added cmStatusReserved0 bit to the flags field <BBH>
		 <6>	 11/4/90	dba		get rid of stuff after #endif (not allowed by the ANSI
									standard); used constStr255Parameter, and created
									constCMBufferSizesParameter since CMBufferSizes is an array too;
									got rid of some obsolete use of __cplusplus got rid of some
									extraneous parameter names; made some parameters void* instead
									of Ptr, including more const
		 <5>	 10/3/90	kaz		Changing // comments for ANSI compatibility <jng>
		 <4>	  6/4/90	BBH		moved new stuff to ConnectionsExtensions.x
		 <3>	 4/12/90	BBH		added cmUserCancel
		 <2>	 3/14/90	BBH		fix includes
		 <1>	 3/12/90	BBH		first checked in

	To Do:
************************************************************/


#ifndef	__CONNECTIONS__
#define __CONNECTIONS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __CTBUTILITIES__
#include <CTBUtilities.h>
#endif


enum {


/*	current Connection Manager version	*/
 curCMVersion = 2,

/*	current Connection Manager Environment Record version 	*/
 curConnEnvRecVers = 0,

/* CMErr */
 cmGenericError = -1,
 cmNoErr = 0,
 cmRejected = 1,
 cmFailed = 2,
 cmTimeOut = 3,
 cmNotOpen = 4,
 cmNotClosed = 5,
 cmNoRequestPending = 6,
 cmNotSupported = 7,
 cmNoTools = 8,
 cmUserCancel = 9,
 cmUnknownError = 11
};

typedef	OSErr CMErr;



enum {
 	cmData 			= 1 << 0,
	cmCntl 			= 1 << 1,
	cmAttn 			= 1 << 2,
	cmDataNoTimeout	= 1 << 4,
	cmCntlNoTimeout = 1 << 5,
	cmAttnNoTimeout = 1 << 6,
	cmDataClean 	= 1 << 8,
	cmCntlClean		= 1 << 9,
	cmAttnClean		= 1 << 10,
/*		Only for CMRecFlags (not CMChannel) in the rest of this enum	*/
	cmNoMenus 		= 1 << 16,
	cmQuiet			= 1 << 17,
	cmConfigChanged	= 1 << 18
};

/* CMRecFlags and CMChannel		*/
/*		Low word of CMRecFlags is same as CMChannel	*/
typedef long CMRecFlags;


typedef short CMChannel;




enum {
	cmStatusOpening = 1 << 0,
	cmStatusOpen = 1 << 1,
	cmStatusClosing = 1 << 2,
	cmStatusDataAvail 	= 1 << 3,
	cmStatusCntlAvail 	= 1 << 4,
	cmStatusAttnAvail 	= 1 << 5,

	cmStatusDRPend 		= 1 << 6,		/* data read pending	*/
	cmStatusDWPend 		= 1 << 7,		/* data write pending	*/
	cmStatusCRPend 		= 1 << 8,		/* cntl read pending	*/
	cmStatusCWPend 		= 1 << 9,		/* cntl write pending	*/
	cmStatusARPend 		= 1 << 10,		/* attn read pending	*/
	cmStatusAWPend 		= 1 << 11,		/* attn write pending	*/

	cmStatusBreakPend 	= 1 << 12,
	cmStatusListenPend 	= 1 << 13,
	cmStatusIncomingCallPresent = 1 << 14,

	cmStatusReserved0	= 1 << 15
};
typedef unsigned long CMStatFlags;

enum {cmDataIn,cmDataOut,cmCntlIn,cmCntlOut,cmAttnIn,cmAttnOut,cmRsrvIn,
 cmRsrvOut};
typedef unsigned short CMBufFields;


typedef Ptr CMBuffers[8];
typedef long CMBufferSizes[8];
typedef const long *ConstCMBufferSizesParam;

enum {cmSearchSevenBit =	1 << 0};
typedef unsigned short CMSearchFlags;

enum {cmFlagsEOM		=	1 << 0};
typedef unsigned short CMFlags;


struct ConnEnvironRec {
	short		version;
	long		baudRate;
	short		dataBits;
	CMChannel	channels;
	Boolean		swFlowControl;
	Boolean		hwFlowControl;
	CMFlags		flags;
};

typedef struct ConnEnvironRec ConnEnvironRec;
typedef ConnEnvironRec *ConnEnvironRecPtr;

struct ConnRecord {
	short		procID;
	CMRecFlags	flags;
	CMErr		errCode;
	long		refCon;
	long		userData;
	ProcPtr		defProc;
	Ptr			config;
	Ptr			oldConfig;
	long		asyncEOM;
	long		reserved1;
	long		reserved2;
	Ptr			cmPrivate;
	CMBuffers		bufferArray;
	CMBufferSizes	bufSizes;
	long		mluField;
	CMBufferSizes	asyncCount;
};

typedef struct ConnRecord ConnRecord;
typedef ConnRecord *ConnPtr, **ConnHandle;


/*	application routines type definitions */
typedef pascal void  (*ConnectionSearchCallBackProcPtr) (ConnHandle hConn, Ptr matchPtr, long refNum);
typedef pascal void  (*ConnectionCompletionProcPtr) (ConnHandle hConn);
typedef pascal void  (*ConnectionChooseIdleProcPtr) (void);

enum {


/* CMIOPB constants and structure */
 cmIOPBQType = 10,
 cmIOPBversion = 0
};

struct CMIOPB {
	QElemPtr	qLink;
	short		qType;			/* cmIOPBQType */
	ConnHandle	hConn;
	Ptr			theBuffer;
	long		count;
	CMFlags		flags;
	ConnectionCompletionProcPtr userCompletion;
	long		timeout;
	CMErr		errCode;
	CMChannel	channel;
	long		asyncEOM;
	long		reserved1;
	short		reserved2;
	short		version;		/* cmIOPBversion */
	long		refCon;			/* for application */
	long		toolData1;		/* for tool */
	long		toolData2;		/* for tool */
};

typedef struct CMIOPB CMIOPB;
typedef CMIOPB *CMIOPBPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal CMErr		InitCM(void);
pascal Handle 		CMGetVersion(ConnHandle hConn);
pascal short 		CMGetCMVersion(void);

pascal ConnHandle	CMNew(short procID,CMRecFlags flags,ConstCMBufferSizesParam desiredSizes,
						long refCon,long userData);

pascal void 		CMDispose(ConnHandle hConn);

pascal CMErr 		CMListen(ConnHandle hConn,Boolean async,ConnectionCompletionProcPtr completor,
						long timeout);
pascal CMErr 		CMAccept(ConnHandle hConn,Boolean accept);

pascal CMErr 		CMOpen(ConnHandle hConn,Boolean async,ConnectionCompletionProcPtr completor,
						long timeout);
pascal CMErr 		CMClose(ConnHandle hConn,Boolean async,ConnectionCompletionProcPtr completor,
						long timeout,Boolean now);

pascal CMErr 		CMAbort(ConnHandle hConn);

pascal CMErr 		CMStatus(ConnHandle hConn,CMBufferSizes sizes,CMStatFlags *flags);
pascal void 		CMIdle(ConnHandle hConn);

pascal void 		CMReset(ConnHandle hConn);

pascal void 		CMBreak(ConnHandle hConn,long duration,Boolean async,ConnectionCompletionProcPtr completor);

pascal CMErr 		CMRead(ConnHandle hConn,void *theBuffer,long *toRead,CMChannel theChannel,
			Boolean async,ConnectionCompletionProcPtr completor,long timeout,CMFlags *flags);
pascal CMErr 		CMWrite(ConnHandle hConn,const void *theBuffer,long *toWrite,
			CMChannel theChannel,Boolean async,ConnectionCompletionProcPtr completor,
			long timeout,CMFlags flags);

pascal CMErr 		CMIOKill(ConnHandle hConn,short which);

pascal void 		CMActivate(ConnHandle hConn,Boolean activate);
pascal void 		CMResume(ConnHandle hConn,Boolean resume);
pascal Boolean 		CMMenu(ConnHandle hConn,short menuID,short item);

pascal Boolean 		CMValidate(ConnHandle hConn);
pascal void 		CMDefault(Ptr *theConfig,short procID,Boolean allocate);

pascal Handle 		CMSetupPreflight(short procID,long *magicCookie);
pascal Boolean 		CMSetupFilter(short procID,const void *theConfig,short count,
 DialogPtr theDialog,EventRecord *theEvent,short *theItem,long *magicCookie);
pascal void  CMSetupSetup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,long *magicCookie);
pascal void  CMSetupItem(short procID,const void *theConfig,short count,
 DialogPtr theDialog,short *theItem,long *magicCookie);
pascal void  CMSetupXCleanup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,Boolean OKed,long *magicCookie);
pascal void  CMSetupPostflight(short procID);

pascal Ptr 			CMGetConfig(ConnHandle hConn);
pascal short	 	CMSetConfig(ConnHandle hConn,const void *thePtr);

pascal OSErr 		CMIntlToEnglish(ConnHandle hConn,const void *inputPtr,Ptr *outputPtr,
 short language);
pascal OSErr 		CMEnglishToIntl(ConnHandle hConn,const void *inputPtr,Ptr *outputPtr,
 short language);

pascal long 		CMAddSearch(ConnHandle hConn,ConstStr255Param theString,CMSearchFlags flags,
 ConnectionSearchCallBackProcPtr callBack);
pascal void			CMRemoveSearch(ConnHandle hConn,long refnum);
pascal void			CMClearSearch(ConnHandle hConn);

pascal CMErr	 	CMGetConnEnvirons(ConnHandle hConn,ConnEnvironRec *theEnvirons);

pascal short	 	CMChoose(ConnHandle *hConn,Point where,ConnectionChooseIdleProcPtr idleProc);

pascal void			CMEvent(ConnHandle hConn,const EventRecord *theEvent);

pascal void 		CMGetToolName(short procID,Str255 name);
pascal short 		CMGetProcID(ConstStr255Param name);

pascal void			CMSetRefCon(ConnHandle hConn,long refCon);
pascal long 		CMGetRefCon(ConnHandle hConn);

pascal long 		CMGetUserData(ConnHandle hConn);
pascal void 		CMSetUserData(ConnHandle hConn,long userData);

pascal void			CMGetErrorString(ConnHandle hConn,short id,Str255 errMsg);

pascal CMErr  		CMNewIOPB(ConnHandle hConn,CMIOPBPtr *theIOPB);
pascal CMErr		CMDisposeIOPB(ConnHandle hConn,CMIOPBPtr theIOPB);

pascal CMErr		CMPBRead(ConnHandle hConn,CMIOPBPtr theIOPB,Boolean async);
pascal CMErr		CMPBWrite(ConnHandle hConn,CMIOPBPtr theIOPB,Boolean async);
pascal CMErr		CMPBIOKill(ConnHandle hConn,CMIOPBPtr theIOPB);
#ifdef __cplusplus
}
#endif

#endif