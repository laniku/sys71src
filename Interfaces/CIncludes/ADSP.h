
/************************************************************

Created: Tuesday, July 30, 1991 at 11:01 AM
 ADSP.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1986-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606

	Change History (most recent first):

		 <6>	 7/30/91	JL		Updated Copyright. Change #defines to enums. Reformatted structs
									to match database.
		 <5>	 1/27/91	LN		Checked in Database generate file from DSG.
		<4>	03/07/90	JAL	Changed records for C Plus Plus support.
 1.0	CVC 11/02/1989 First time add the file to CInclude

	To Do:

************************************************************/


#ifndef __ADSP__
#define __ADSP__

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif


enum {


/* driver control ioResults */
 errRefNum = -1280,				/* bad connection refNum */
 errAborted = -1279,			/* control call was aborted */
 errState = -1278,				/* bad connection state for this operation */
 errOpening = -1277,			/* open connection request failed */
 errAttention = -1276,			/* attention message too long */
 errFwdReset = -1275,			/* read terminated by forward reset */
 errDSPQueueSize = -1274,		/* DSP Read/Write Queue Too small */
 errOpenDenied = -1273,			/* open connection request was denied */

/*driver control csCodes*/
 dspInit = 255,					/* create a new connection end */
 dspRemove = 254,				/* remove a connection end */
 dspOpen = 253,					/* open a connection */
 dspClose = 252,				/* close a connection */
 dspCLInit = 251,				/* create a connection listener */
 dspCLRemove = 250,				/* remove a connection listener */
 dspCLListen = 249,				/* post a listener request */
 dspCLDeny = 248,				/* deny an open connection request */
 dspStatus = 247,				/* get status of connection end */
 dspRead = 246,					/* read data from the connection */
 dspWrite = 245,				/* write data on the connection */
 dspAttention = 244				/* send an attention message */
};
enum {
 dspOptions = 243,				/* set connection end options */
 dspReset = 242,				/* forward reset the connection */
 dspNewCID = 241,				/* generate a cid for a connection end */

/* connection opening modes */
 ocRequest = 1,					/* request a connection with remote */
 ocPassive = 2,					/* wait for a connection request from remote */
 ocAccept = 3,					/* accept request as delivered by listener */
 ocEstablish = 4,				/* consider connection to be open */

/* connection end states */
 sListening = 1,				/* for connection listeners */
 sPassive = 2,					/* waiting for a connection request from remote */
 sOpening = 3,					/* requesting a connection with remote */
 sOpen = 4,						/* connection is open */
 sClosing = 5,					/* connection is being torn down */
 sClosed = 6,					/* connection end state is closed */

/* client event flags */
 eClosed = 0x80,				/* received connection closed advice */
 eTearDown = 0x40,				/* connection closed due to broken connection */
 eAttention = 0x20,				/* received attention message */
 eFwdReset = 0x10,				/* received forward reset advice */

/* miscellaneous constants */
 attnBufSize = 570,				/* size of client attention buffer */
 minDSPQueueSize = 100			/* Minimum size of receive or send Queue */
};

/* connection control block */
struct TRCCB {
 unsigned char *ccbLink;		/* link to next ccb */
 unsigned short refNum;			/* user reference number */
 unsigned short state;			/* state of the connection end */
 unsigned char userFlags;		/* flags for unsolicited connection events */
 unsigned char localSocket;		/* socket number of this connection end */
 AddrBlock remoteAddress;		/* internet address of remote end */
 unsigned short attnCode;		/* attention code received */
 unsigned short attnSize;		/* size of received attention data */
 unsigned char *attnPtr;		/* ptr to received attention data */
 unsigned char reserved[220];	/* for adsp internal use */
};

typedef struct TRCCB TRCCB;
typedef TRCCB *TPCCB;

/* init connection end parameters */
struct TRinitParams {
 TPCCB ccbPtr;					/* pointer to connection control block */
 ProcPtr userRoutine;			/* client routine to call on event */
 unsigned short sendQSize;		/* size of send queue (0..64K bytes) */
 unsigned char *sendQueue;		/* client passed send queue buffer */
 unsigned short recvQSize;		/* size of receive queue (0..64K bytes) */
 unsigned char *recvQueue;		/* client passed receive queue buffer */
 unsigned char *attnPtr;		/* client passed receive attention buffer */
 unsigned char localSocket;		/* local socket number */
};

typedef struct TRinitParams TRinitParams;

/* open connection parameters */
struct TRopenParams {
 unsigned short localCID;		/* local connection id */
 unsigned short remoteCID;		/* remote connection id */
 AddrBlock remoteAddress;		/* address of remote end */
 AddrBlock filterAddress;		/* address filter */
 unsigned long sendSeq;			/* local send sequence number */
 unsigned short sendWindow;		/* send window size */
 unsigned long recvSeq;			/* receive sequence number */
 unsigned long attnSendSeq;		/* attention send sequence number */
 unsigned long attnRecvSeq;		/* attention receive sequence number */
 unsigned char ocMode;			/* open connection mode */
 unsigned char ocInterval;		/* open connection request retry interval */
 unsigned char ocMaximum;		/* open connection request retry maximum */
};

typedef struct TRopenParams TRopenParams;

/* close connection parameters */
struct TRcloseParams {
 unsigned char abort;			/* abort connection immediately if non-zero */
};

typedef struct TRcloseParams TRcloseParams;

/* client status parameter block */
struct TRstatusParams {
 TPCCB ccbPtr;					/* pointer to ccb */
 unsigned short sendQPending;	/* pending bytes in send queue */
 unsigned short sendQFree;		/* available buffer space in send queue */
 unsigned short recvQPending;	/* pending bytes in receive queue */
 unsigned short recvQFree;		/* available buffer space in receive queue */
};

typedef struct TRstatusParams TRstatusParams;

/* read/write parameter block */
struct TRioParams {
 unsigned short reqCount;		/* requested number of bytes */
 unsigned short actCount;		/* actual number of bytes */
 unsigned char *dataPtr;		/* pointer to data buffer */
 unsigned char eom;				/* indicates logical end of message */
 unsigned char flush;			/* send data now */
};

typedef struct TRioParams TRioParams;

/* attention parameter block */
struct TRattnParams {
 unsigned short attnCode;		/* client attention code */
 unsigned short attnSize;		/* size of attention data */
 unsigned char *attnData;		/* pointer to attention data */
 unsigned char attnInterval;	/* retransmit timer in 10-tick intervals */
};

typedef struct TRattnParams TRattnParams;

/* client send option parameter block */
struct TRoptionParams {
 unsigned short sendBlocking;	/* quantum for data packets */
 unsigned char sendTimer;		/* send timer in 10-tick intervals */
 unsigned char rtmtTimer;		/* retransmit timer in 10-tick intervals */
 unsigned char badSeqMax;		/* threshold for sending retransmit advice */
 unsigned char useCheckSum;		/* use ddp packet checksum */
};

typedef struct TRoptionParams TRoptionParams;

/* new cid parameters */
struct TRnewcidParams {
 unsigned short newcid;			/* new connection id returned */
};

typedef struct TRnewcidParams TRnewcidParams;

/* ADSP CntrlParam ioQElement , driver control call parameter block*/
struct DSPParamBlock {
 struct QElem *qLink;
 short qType;
 short ioTrap;
 Ptr ioCmdAddr;
 ProcPtr ioCompletion;
 OSErr ioResult;
 char *ioNamePtr;
 short ioVRefNum;
 short ioCRefNum;				/* adsp driver refNum */
 short csCode;					/* adsp driver control code */
 long qStatus;					/* adsp internal use */
 short ccbRefNum;
 union{
  TRinitParams initParams;		/*dspInit, dspCLInit*/
  TRopenParams openParams;		/*dspOpen, dspCLListen, dspCLDeny*/
  TRcloseParams closeParams;	/*dspClose, dspRemove*/
  TRioParams ioParams;			/*dspRead, dspWrite*/
  TRattnParams attnParams;		/*dspAttention*/
  TRstatusParams statusParams;	/*dspStatus*/
  TRoptionParams optionParams;	/*dspOptions*/
  TRnewcidParams newCIDParams;	/*dspNewCID*/
  } u;
};

typedef struct DSPParamBlock DSPParamBlock;
typedef DSPParamBlock *DSPPBPtr;



#endif
