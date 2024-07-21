
/************************************************************

Created: Tuesday, July 30, 1991 at 1:18 PM
 AppleTalk.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		<10>	 11/8/91	JL		Changed BDSPtr from a pointer to the BDSType struct to a pointer
									to the same type as the BDSType struct. BDSType is an array and
									therefore a pointer to it would be a pointer to a pointer.
		 <9>	 7/30/91	JL		Reformatted unions to match database.  Updated Copyright.
									Restored Comments.
		 <8>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Changed the socket param
									types of the funcitons: DDPCloseSocket, ATPOpenSocket, and
									ATPCloseSocket from char back to short. Changed first param type
									of ATPOpenSocket from a const AddrBlock * to an AddrBlock. Added
									and deleted lines to match shipped version. Updated creation
									date (3rd line of this file.)
		 <7>	 1/28/91	LN		Checked in Database generate file from DSG. Grouping enums into
									groups of 20 for C++ support.
		 <6>	 1/21/91	mbs		(pd) The first parameter to DDPOpensocket should be a short * or
									the Interface.o glue code will break.
		 <5>	 1/19/91	mbs		(jg) change #defines to enums, Added csCodes for .MPP, .ATP, and
									.XPP drivers. Remove 4th parameter to ATPreFlightEvent.
		 <4>	  1/3/91	JDR		(dba) Removed LAddAEQ, LRmvAEQ, PCancelATalkClosePrep,
									LAPGetATQ, RemoveHdlBlocks and added ATPKillAllGetReq, ATEvent,
									ATPreFlightEvent. Moved Str32 to Types.h and making it an
									unsigned char.
		<3> 	10/9/90		JAL		Changed xCallParam to XCallParam
		<2> 	10/4/90		JAL		Updated to AppleTalk Phase II. 
									Changed sockets from shorts to chars.
									Added const to netAddr in BuildDDPwds
	   <1.1>	10/31/89	PWD		Changed BuildDDPWds to the real definition.
	   <1.0>	 11/9/88	CCH		Adding to EASE.
************************************************************/


#ifndef __APPLETALK__
#define __APPLETALK__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


enum {


/* Driver unit and reference numbers (ADSP is dynamic) */

 mppUnitNum = 9,			/* MPP unit number */
 atpUnitNum = 10,			/* ATP unit number */
 xppUnitNum = 40,			/* XPP unit number */
 mppRefNum = -10,			/* MPP reference number */
 atpRefNum = -11,			/* ATP reference number */
 xppRefNum = -41,			/* XPP reference number */

/* .MPP csCodes */

 lookupReply = 242,			/* This command queued to ourself */
 writeLAP = 243,			/* Write out LAP packet */
 detachPH = 244,			/* Detach LAP protocol handler */
 attachPH = 245,			/* Attach LAP protocol handler */
 writeDDP = 246,			/* Write out DDP packet */
 closeSkt = 247,			/* Close DDP socket */
 openSkt = 248,				/* Open DDP socket */
 loadNBP = 249,				/* Load NBP command-executing code */
 lastResident = 249,		/* Last resident command */
 confirmName = 250,			/* Confirm name */
 lookupName = 251,			/* Look up name on internet */
 removeName = 252,			/* Remove name from Names Table */
 registerName = 253,		/* Register name in Names Table */
 killNBP = 254				/* Kill outstanding NBP request */
};
enum {
 unloadNBP = 255,			/* Unload NBP command code */
 setSelfSend = 256,			/* MPP: Set to allow writes to self */
 SetMyZone = 257,			/* Set my zone name */
 GetATalkInfo = 258,		/* get AppleTalk information */
 ATalkClosePrep = 259,		/* AppleTalk close query */

/* .ATP csCodes */

 nSendRequest = 248,		/* NSendRequest code */
 relRspCB = 249,			/* Release RspCB */
 closeATPSkt = 250,			/* Close ATP socket */
 addResponse = 251,			/* Add response code | Require open skt */
 sendResponse = 252,		/* Send response code */
 getRequest = 253,			/* Get request code */
 openATPSkt = 254,			/* Open ATP socket */
 sendRequest = 255,			/* Send request code */
 relTCB = 256,				/* Release TCB */
 killGetReq = 257,			/* Kill GetRequest */
 killSendReq = 258,			/* Kill SendRequest */
 killAllGetReq = 259,		/* Kill all getRequests for a skt */

/* .XPP csCodes */

 openSess = 255,			/* Open session */
 closeSess = 254,			/* Close session */
 userCommand = 253			/* User command */
};
enum {
 userWrite = 252,			/* User write */
 getStatus = 251,			/* Get status */
 afpCall = 250,				/* AFP command (buffer has command code) */
 getParms = 249,			/* Get parameters */
 abortOS = 248,				/* Abort open session request */
 closeAll = 247,			/* Close all open sessions */
 xCall = 246,				/* .XPP extended calls */

/* Transition Queue transition types */
 ATTransOpen = 0,			/*AppleTalk has opened*/
 ATTransClose = 2,			/*AppleTalk is about to close*/
 ATTransClosePrep = 3,		/*Is it OK to close AppleTalk ?*/
 ATTransCancelClose = 4,	/*Cancel the ClosePrep transition*/

 afpByteRangeLock = 1,		/*AFPCall command codes*/
 afpVolClose = 2,			/*AFPCall command codes*/
 afpDirClose = 3,			/*AFPCall command codes*/
 afpForkClose = 4,			/*AFPCall command codes*/
 afpCopyFile = 5,			/*AFPCall command codes*/
 afpDirCreate = 6,			/*AFPCall command codes*/
 afpFileCreate = 7,			/*AFPCall command codes*/
 afpDelete = 8,				/*AFPCall command codes*/
 afpEnumerate = 9			/*AFPCall command codes*/
};
enum {
 afpFlush = 10,				/*AFPCall command codes*/
 afpForkFlush = 11,			/*AFPCall command codes*/
 afpGetDirParms = 12,		/*AFPCall command codes*/
 afpGetFileParms = 13,		/*AFPCall command codes*/
 afpGetForkParms = 14,		/*AFPCall command codes*/
 afpGetSInfo = 15,			/*AFPCall command codes*/
 afpGetSParms = 16,			/*AFPCall command codes*/
 afpGetVolParms = 17,		/*AFPCall command codes*/
 afpLogin = 18,				/*AFPCall command codes*/
 afpContLogin = 19,			/*AFPCall command codes*/
 afpLogout = 20,			/*AFPCall command codes*/
 afpMapID = 21,				/*AFPCall command codes*/
 afpMapName = 22,			/*AFPCall command codes*/
 afpMove = 23,				/*AFPCall command codes*/
 afpOpenVol = 24,			/*AFPCall command codes*/
 afpOpenDir = 25,			/*AFPCall command codes*/
 afpOpenFork = 26,			/*AFPCall command codes*/
 afpRead = 27,				/*AFPCall command codes*/
 afpRename = 28,			/*AFPCall command codes*/
 afpSetDirParms = 29		/*AFPCall command codes*/
};
enum {
 afpSetFileParms = 30,		/*AFPCall command codes*/
 afpSetForkParms = 31,		/*AFPCall command codes*/
 afpSetVolParms = 32,		/*AFPCall command codes*/
 afpWrite = 33,				/*AFPCall command codes*/
 afpGetFlDrParms = 34,		/*AFPCall command codes*/
 afpSetFlDrParms = 35,		/*AFPCall command codes*/
 afpDTOpen = 48,			/*AFPCall command codes*/
 afpDTClose = 49,			/*AFPCall command codes*/
 afpGetIcon = 51,			/*AFPCall command codes*/
 afpGtIcnInfo = 52,			/*AFPCall command codes*/
 afpAddAPPL = 53,			/*AFPCall command codes*/
 afpRmvAPPL = 54,			/*AFPCall command codes*/
 afpGetAPPL = 55,			/*AFPCall command codes*/
 afpAddCmt = 56,			/*AFPCall command codes*/
 afpRmvCmt = 57,			/*AFPCall command codes*/
 afpGetCmt = 58,			/*AFPCall command codes*/
 afpAddIcon = 192,			/*Special code for ASP Write commands*/

 xppLoadedBit = 5,			/* XPP bit in PortBUse */
 scbMemSize = 192,			/* Size of memory for SCB */
 xppFlagClr = 0				/* Cs for AFPCommandBlock */
};
enum {
 xppFlagSet = 128,			/* StartEndFlag & NewLineFlag fields. */

 lapSize = 20,
 ddpSize = 26,
 nbpSize = 26,
 atpSize = 56,

#define MPPioCompletion MPP.ioCompletion
#define MPPioResult MPP.ioResult
#define MPPioRefNum MPP.ioRefNum
#define MPPcsCode MPP.csCode
#define LAPprotType LAP.protType
#define LAPwdsPointer LAP.LAPptrs.wdsPointer
#define LAPhandler LAP.LAPptrs.handler
#define DDPsocket DDP.socket
#define DDPchecksumFlag DDP.checksumFlag
#define DDPwdsPointer DDP.DDPptrs.wdsPointer
#define DDPlistener DDP.DDPptrs.listener
#define NBPinterval NBP.interval
#define NBPcount NBP.count
#define NBPntQElPtr NBP.NBPPtrs.ntQElPtr
#define NBPentityPtr NBP.NBPPtrs.entityPtr
#define NBPverifyFlag NBP.parm.verifyFlag
#define NBPretBuffPtr NBP.parm.Lookup.retBuffPtr
#define NBPretBuffSize NBP.parm.Lookup.retBuffSize
#define NBPmaxToGet NBP.parm.Lookup.maxToGet
#define NBPnumGotten NBP.parm.Lookup.numGotten
#define NBPconfirmAddr NBP.parm.Confirm.confirmAddr
#define NBPnKillQEl NBPKILL.nKillQEl
#define NBPnewSocket NBP.parm.Confirm.newSocket
#define ATPioCompletion ATP.ioCompletion
#define ATPioResult ATP.ioResult
#define ATPuserData ATP.userData
#define ATPreqTID ATP.reqTID
#define ATPioRefNum ATP.ioRefNum
#define ATPcsCode ATP.csCode
#define ATPatpSocket ATP.atpSocket
#define ATPatpFlags ATP.atpFlags
#define ATPaddrBlock ATP.addrBlock
#define ATPreqLength ATP.reqLength
#define ATPreqPointer ATP.reqPointer
#define ATPbdsPointer ATP.bdsPointer
#define ATPtimeOutVal SREQ.timeOutVal
#define ATPnumOfResps SREQ.numOfResps
#define ATPretryCount SREQ.retryCount
#define ATPnumOfBuffs OTH1.u0.numOfBuffs
#define ATPbitMap OTH1.u0.bitMap
#define ATPrspNum OTH1.u0.rspNum
#define ATPbdsSize OTH2.bdsSize
#define ATPtransID OTH2.transID
#define ATPaKillQEl KILL.aKillQEl


 atpXOvalue = 32,			/*ATP exactly-once bit */
 atpEOMvalue = 16,			/*ATP End-Of-Message bit */
 atpSTSvalue = 8,			/*ATP Send-Transmission-Status bit */
 atpTIDValidvalue = 2,		/*ATP trans. ID valid bit */
 atpSendChkvalue = 1,		/*ATP send checksum bit */

 zipGetLocalZones = 5,
 zipGetZoneList = 6,
 zipGetMyZone = 7,

 LAPMgrPtr = 0xB18,			/*Entry point for LAP Manager*/
 LAPMgrCall = 2,			/*Offset to LAP routines*/
 LAddAEQ = 23,				/*LAPAddATQ routine selector*/
 LRmvAEQ = 24				/*LAPRmvATQ routine selector*/
};

enum {tLAPRead,tLAPWrite,tDDPRead,tDDPWrite,tNBPLookup,tNBPConfirm,tNBPRegister,
 tATPSndRequest,tATPGetRequest,tATPSdRsp,tATPAddRsp,tATPRequest,tATPResponse};
typedef unsigned char ABCallType;

enum {lapProto,ddpProto,nbpProto,atpProto};
typedef unsigned char ABProtoType;


typedef Byte ABByte;


struct LAPAdrBlock {
 unsigned char dstNodeID;
 unsigned char srcNodeID;
 ABByte lapProtType;
};

typedef struct LAPAdrBlock LAPAdrBlock;

struct ATQEntry {
 struct ATQEntry *qLink;	/*next queue entry*/
 short qType;				/*queue type*/
 ProcPtr CallAddr;			/*pointer to your routine*/
};

typedef struct ATQEntry ATQEntry;
typedef ATQEntry *ATQEntryPtr;

struct AddrBlock {
 short aNet;
 unsigned char aNode;
 unsigned char aSocket;
};

typedef struct AddrBlock AddrBlock;

/* Real definition of EntityName is 3 PACKED strings of any length (32 is just an example). No
offests for Asm since each String address must be calculated by adding length byte to last string ptr.
In Pascal, String(32) will be 34 bytes long since fields never start on an odd byte unless they are 
only a byte long. So this will generate correct looking interfaces for Pascal and C, but they will not
be the same, which is OK since they are not used. */
struct EntityName {
 Str32 objStr;
 char pad1;					/*Str32's aligned on even word boundries.*/
 Str32 typeStr;
 char pad2;
 Str32 zoneStr;
 char pad3;
};

typedef struct EntityName EntityName;
typedef EntityName *EntityPtr;

struct RetransType {
 unsigned char retransInterval;
 unsigned char retransCount;
};

typedef struct RetransType RetransType;

struct BDSElement {
 short buffSize;
 Ptr buffPtr;
 short dataSize;
 long userBytes;
};

typedef struct BDSElement BDSElement;


typedef BDSElement BDSType[8];
typedef BDSElement *BDSPtr;
typedef char BitMapType;

struct ATLAPRec {
 ABCallType abOpcode;
 short abResult;
 long abUserReference;
 LAPAdrBlock lapAddress;
 short lapReqCount;
 short lapActCount;
 Ptr lapDataPtr;
};

typedef struct ATLAPRec ATLAPRec;
typedef ATLAPRec *ATLAPRecPtr, **ATLAPRecHandle;

struct ATDDPRec {
 ABCallType abOpcode;
 short abResult;
 long abUserReference;
 short ddpType;
 short ddpSocket;
 AddrBlock ddpAddress;
 short ddpReqCount;
 short ddpActCount;
 Ptr ddpDataPtr;
 short ddpNodeID;
};

typedef struct ATDDPRec ATDDPRec;
typedef ATDDPRec *ATDDPRecPtr, **ATDDPRecHandle;

struct ATNBPRec {
 ABCallType abOpcode;
 short abResult;
 long abUserReference;
 EntityPtr nbpEntityPtr;
 Ptr nbpBufPtr;
 short nbpBufSize;
 short nbpDataField;
 AddrBlock nbpAddress;
 RetransType nbpRetransmitInfo;
};

typedef struct ATNBPRec ATNBPRec;
typedef ATNBPRec *ATNBPRecPtr, **ATNBPRecHandle;

struct ATATPRec {
 ABCallType abOpcode;
 short abResult;
 long abUserReference;
 short atpSocket;
 AddrBlock atpAddress;
 short atpReqCount;
 Ptr atpDataPtr;
 BDSPtr atpRspBDSPtr;
 BitMapType atpBitMap;
 short atpTransID;
 short atpActCount;
 long atpUserData;
 Boolean atpXO;
 Boolean atpEOM;
 short atpTimeOut;
 short atpRetries;
 short atpNumBufs;
 short atpNumRsp;
 short atpBDSSize;
 long atpRspUData;
 Ptr atpRspBuf;
 short atpRspSize;
};

typedef struct ATATPRec ATATPRec;
typedef ATATPRec *ATATPRecPtr, **ATATPRecHandle;

typedef struct {
 char cmdByte;
 char startEndFlag;
 short forkRefNum;
 long rwOffset;
 long reqCount;
 char newLineFlag;
 char newLineChar;
}AFPCommandBlock;


#define XPPPBHeader \
 QElem *qLink;\
 short qType;\
 short ioTrap;\
 Ptr ioCmdAddr;\
 ProcPtr ioCompletion;\
 OSErr ioResult;\
 long cmdResult;\
 short ioVRefNum;\
 short ioRefNum;\
 short csCode;

typedef struct {
 XPPPBHeader 
 short sessRefnum;			/*Offset to session refnum*/
 char aspTimeout;			/*Timeout for ATP*/
 char aspRetry;				/*Retry count for ATP*/
 short cbSize;				/*Command block size*/
 Ptr cbPtr;					/*Command block pointer*/
 short rbSize;				/*Reply buffer size*/
 Ptr rbPtr;					/*Reply buffer pointer*/
 short wdSize;				/*Write Data size*/
 Ptr wdPtr;					/*Write Data pointer*/
 char ccbStart[296];		/*CCB memory allocated for driver afpWrite max size(CCB)=296 all other calls=150*/
}XPPPrmBlk;


typedef struct {
 XPPPBHeader 
 short sessRefnum;			/*Offset to session refnum */
 char aspTimeout;			/*Timeout for ATP */
 char aspRetry;				/*Retry count for ATP */
 short cbSize;				/*Command block size */
 Ptr cbPtr;					/*Command block pointer */
 short rbSize;				/*Reply buffer size */
 Ptr rbPtr;					/*Reply buffer pointer */
 AddrBlock afpAddrBlock;	/*block in AFP login */
 Ptr afpSCBPtr;				/*SCB pointer in AFP login */
 Ptr afpAttnRoutine;		/*routine pointer in AFP login */
 char ccbFill[144];			/*CCB memory allocated for driver  Login needs only 150 bytes BUT CCB really starts in the middle of AFPSCBPtr and also clobbers AFPAttnRoutine. */
}AFPLoginPrm;


typedef struct {
 XPPPBHeader 
 short sessRefnum;			/*Offset to session refnum */
 char aspTimeout;			/*Timeout for ATP */
 char aspRetry;				/*Retry count for ATP */
 AddrBlock serverAddr;		/*Server address block */
 Ptr scbPointer;			/*SCB pointer */
 Ptr attnRoutine;			/*Attention routine pointer*/
}ASPOpenPrm;

typedef ASPOpenPrm *ASPOpenPrmPtr;

typedef struct {
 XPPPBHeader 
 Ptr abortSCBPtr;			/*SCB pointer for AbortOS */
}ASPAbortPrm;


typedef struct {
 XPPPBHeader 
 short aspMaxCmdSize;		/*For SPGetParms*/
 short aspQuantumSize;
 short numSesss;
}ASPGetparmsBlk;


typedef struct {
 XPPPBHeader 
 short xppSubCode;
 char xppTimeout;			/*retry interval (seconds)*/
 char xppRetry;				/*retry count*/
 short filler1;
 Ptr zipBuffPtr;			/*pointer to buffer (must be 578 bytes)*/
 short zipNumZones;			/*no. of zone names in this response*/
 char zipLastFlag;			/*non-zero if no more zones*/
 char filler2;				/*filler*/
 char zipInfoField[70];		/*on initial call, set first word to zero*/
}XCallParam;


typedef struct {
 short entryLength;
 Ptr entryPtr;
}WDSElement;


typedef struct {
 AddrBlock nteAddress;		/*network address of entity*/
 char filler;
 char entityData[99];		/*Object, Type & Zone*/
}NTElement;


typedef struct {
 Ptr qNext;					/*ptr to next NTE*/
 NTElement nt;
}NamesTableEntry;


#define MPPATPHeader \
 QElem *qLink;   			/*next queue entry*/\
 short qType;   			/*queue type*/\
 short ioTrap;   			/*routine trap*/\
 Ptr ioCmdAddr;   			/*routine address*/\
 ProcPtr ioCompletion; 		/*completion routine*/\
 OSErr ioResult;   			/*result code*/\
 long userData;   			/*Command result (ATP user bytes)*/\
 short reqTID;   			/*request transaction ID*/\
 short ioRefNum;   			/*driver reference number*/\
 short csCode;   			/*Call command code*/

typedef struct {
 MPPATPHeader 
}MPPparms;


typedef struct {
 MPPATPHeader 
 char protType;				/*ALAP protocol Type */
 char filler;
 union {
  Ptr wdsPointer;			/*-> write data structure*/
  Ptr handler;				/*-> protocol handler routine*/
  } LAPptrs;
}LAPparms;


typedef struct {
 MPPATPHeader 
 char socket;				/*socket number */
 char checksumFlag;			/*check sum flag */
 union {
  Ptr wdsPointer;			/*-> write data structure*/
  Ptr listener;				/*->write data structure or -> Listener*/
  } DDPptrs;
}DDPparms;


typedef struct {
 MPPATPHeader 
 char interval;				/*retry interval */
 char count;				/*retry count */
 union {
  Ptr ntQElPtr;
  Ptr entityPtr;
  } NBPPtrs;
 union {
  char verifyFlag;
  struct {
   Ptr retBuffPtr;
   short retBuffSize;
   short maxToGet;
   short numGotten;
   } Lookup;
  struct {
   AddrBlock confirmAddr;
   char newSocket;
   } Confirm;
  } parm;
}NBPparms;


typedef struct {
 MPPATPHeader 
 char newSelfFlag;			/*self-send toggle flag */
 char oldSelfFlag;			/*previous self-send state */
}SetSelfparms;


typedef struct {
 MPPATPHeader 
 Ptr nKillQEl;				/*ptr to i/o queue element to cancel */
}NBPKillparms;


typedef struct {
 MPPATPHeader 				/*max. concurrent NBP requests*/
 short version;				/*requested info version*/
 Ptr varsPtr;				/*pointer to well known MPP vars*/
 Ptr DCEPtr;				/*pointer to MPP DCE*/
 short portID;				/*port number [0..7]*/
 long configuration;		/*32-bit configuration word*/
 short selfSend;			/*non zero if SelfSend enabled*/
 short netLo;				/*low value of network range*/
 short netHi;				/*high value of network range*/
 long ourAdd;				/*our 24-bit AppleTalk address*/
 long routerAddr;			/*24-bit address of (last) router*/
 short numOfPHs;			/*max. number of protocol handlers*/
 short numOfSkts;			/*max. number of static sockets*/
 short numNBPEs;			/*max. concurrent NBP requests*/
 Ptr nTQueue;				/*pointer to registered name queue*/
 short LAlength;			/*length in bytes of data link addr*/
 Ptr linkAddr;				/*data link address returned*/
 Ptr zoneName;				/*zone name returned*/
}GetAppleTalkInfoParm;


typedef struct {
 MPPATPHeader 
 Ptr appName;				/*pointer to application name in buffer*/
}ATalkClosePrepParm;


typedef union {
 MPPparms MPP;				/*General MPP parms*/
 LAPparms LAP;				/*ALAP calls*/
 DDPparms DDP;				/*DDP calls*/
 NBPparms NBP;				/*NBP calls*/
 SetSelfparms SETSELF ;
 NBPKillparms NBPKILL ;
 GetAppleTalkInfoParm GAIINFO;
 ATalkClosePrepParm ATALKCLOSE;
}MPPParamBlock;

typedef MPPParamBlock *MPPPBPtr;

#define MOREATPHeader \
 char atpSocket;			/*currbitmap for requests or ATP socket number*/\
 char atpFlags;				/*control information*/\
 AddrBlock addrBlock;		/*source/dest. socket address*/\
 short reqLength;			/*request/response length*/\
 Ptr reqPointer;			/*->request/response Data*/\
 Ptr bdsPointer;			/*->response BDS */


typedef struct {
 MPPATPHeader 
 MOREATPHeader 
}ATPparms;


typedef struct {
 MPPATPHeader 
 MOREATPHeader 
 char filler;				/*numOfBuffs */
 char timeOutVal;			/*timeout interval */
 char numOfResps;			/*number of responses actually received */
 char retryCount;			/*number of retries */
 short intBuff;				/*used internally for NSendRequest */
 char TRelTime;				/*TRelease time for extended send request */
}SendReqparms;


typedef struct {
 MPPATPHeader 
 MOREATPHeader 
 union {
  char bitMap;				/*bitmap received */
  char numOfBuffs;			/*number of responses being sent*/
  char rspNum;				/*sequence number*/
  } u0;
}ATPmisc1;


typedef struct {
 MPPATPHeader 
 MOREATPHeader 
 char filler;
 char bdsSize;				/*number of BDS elements */
 short transID;				/*transaction ID recd. */
}ATPmisc2;


typedef struct {
 MPPATPHeader 
 MOREATPHeader 
 Ptr aKillQEl;				/*ptr to i/o queue element to cancel*/
}Killparms;


union ATPParamBlock {
 ATPparms ATP;				/*General ATP parms*/
 SendReqparms SREQ;			/*sendrequest parms*/
 ATPmisc1 OTH1;				/*and a few others*/
 ATPmisc2 OTH2;				/*and a few others*/
 Killparms KILL;			/*and a few others*/
};

typedef union ATPParamBlock ATPParamBlock;
typedef ATPParamBlock *ATPPBPtr;

union XPPParamBlock {
 XPPPrmBlk XPP;
 ASPGetparmsBlk GETPARM;
 ASPAbortPrm ABORT;
 ASPOpenPrm OPEN;
 AFPLoginPrm LOGIN;
 XCallParam XCALL;
};

typedef union XPPParamBlock XPPParamBlock;
typedef XPPParamBlock *XPPParmBlkPtr;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr OpenXPP(short *xppRefnum); 
pascal OSErr ASPOpenSession(ASPOpenPrmPtr thePBptr,Boolean async); 
pascal OSErr ASPCloseSession(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPAbortOS(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPGetParms(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPCloseAll(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPUserWrite(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPUserCommand(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr ASPGetStatus(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr AFPCommand(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr GetLocalZones(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr GetZoneList(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr GetMyZone(XPPParmBlkPtr thePBptr,Boolean async); 
pascal OSErr PAttachPH(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PDetachPH(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PWriteLAP(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr POpenSkt(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PCloseSkt(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PWriteDDP(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PRegisterName(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PLookupName(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PConfirmName(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PRemoveName(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PSetSelfSend(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PKillNBP(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PGetAppleTalkInfo(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr PATalkClosePrep(MPPPBPtr thePBptr,Boolean async); 
pascal OSErr POpenATPSkt(ATPPBPtr thePBptr,Boolean async); 
pascal OSErr PCloseATPSkt(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PSendRequest(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PGetRequest(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PSendResponse(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PAddResponse(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PRelTCB(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PRelRspCB(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PNSendRequest(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PKillSendReq(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr PKillGetReq(ATPPBPtr thePBPtr,Boolean async); 
pascal OSErr ATPKillAllGetReq(ATPPBPtr thePBPtr,Boolean async); 
pascal void BuildLAPwds(Ptr wdsPtr,Ptr dataPtr,short destHost,short prototype,
 short frameLen); 
pascal void BuildDDPwds(Ptr wdsPtr,Ptr headerPtr,Ptr dataPtr,const AddrBlock netAddr,
 short ddpType,short dataLen); 
pascal void NBPSetEntity(Ptr buffer,Ptr nbpObject,Ptr nbpType,Ptr nbpZone); 
pascal void NBPSetNTE(Ptr ntePtr,Ptr nbpObject,Ptr nbpType,Ptr nbpZone,
 short socket); 
pascal short GetBridgeAddress(void); 
pascal short BuildBDS(Ptr buffPtr,Ptr bdsPtr,short buffSize); 
pascal OSErr MPPOpen(void); 
pascal OSErr MPPClose(void); 
pascal OSErr LAPOpenProtocol(ABByte theLAPType,Ptr protoPtr); 
pascal OSErr LAPCloseProtocol(ABByte theLAPType); 
pascal OSErr LAPWrite(ATLAPRecHandle abRecord,Boolean async); 
pascal OSErr LAPRead(ATLAPRecHandle abRecord,Boolean async); 
pascal OSErr LAPRdCancel(ATLAPRecHandle abRecord); 
pascal OSErr LAPAddATQ(ATQEntryPtr theATQEntry); 
pascal OSErr LAPRmvATQ(ATQEntryPtr theATQEntry); 
pascal OSErr DDPOpenSocket(short *theSocket,Ptr sktListener); 
pascal OSErr DDPCloseSocket(short theSocket); 
pascal OSErr DDPRead(ATDDPRecHandle abRecord,Boolean retCksumErrs,Boolean async); 
pascal OSErr DDPWrite(ATDDPRecHandle abRecord,Boolean doChecksum,Boolean async); 
pascal OSErr DDPRdCancel(ATDDPRecHandle abRecord); 
pascal OSErr ATPLoad(void); 
pascal OSErr ATPUnload(void); 
pascal OSErr ATPOpenSocket(AddrBlock addrRcvd,short *atpSocket); 
pascal OSErr ATPCloseSocket(short atpSocket); 
pascal OSErr ATPSndRequest(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPRequest(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPReqCancel(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPGetRequest(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPSndRsp(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPAddRsp(ATATPRecHandle abRecord); 
pascal OSErr ATPResponse(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr ATPRspCancel(ATATPRecHandle abRecord,Boolean async); 
pascal OSErr NBPRegister(ATNBPRecHandle abRecord,Boolean async); 
pascal OSErr NBPLookup(ATNBPRecHandle abRecord,Boolean async); 
pascal OSErr NBPExtract(Ptr theBuffer,short numInBuf,short whichOne,EntityName *abEntity,
 AddrBlock *address); 
pascal OSErr NBPConfirm(ATNBPRecHandle abRecord,Boolean async); 
pascal OSErr NBPRemove(EntityPtr abEntity); 
pascal OSErr NBPLoad(void); 
pascal OSErr NBPUnload(void); 
pascal OSErr GetNodeAddress(short *myNode,short *myNet); 
pascal Boolean IsMPPOpen(void); 
pascal Boolean IsATPOpen(void); 
pascal void ATEvent(long event,Ptr infoPtr); 
pascal OSErr ATPreFlightEvent(long event,long cancel,Ptr infoPtr); 
#ifdef __cplusplus
}
#endif

#endif
