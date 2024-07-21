/*
	File:		PPCCommon.h

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	  3/9/93	PN		Remove ReQueueInformPB,Insert, Push,InitQueue, TraverseQueue
									which is no longer used
		<44>	 4/14/92	BBM		<JSM>: Remove unfinished PPC code that is under the contitional
									“TheFutute”, and remove the conditional “CubeE” since that is
									reality. Remove conditionals, since all they do is confuse.
		<43>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		<42>	 9/29/91	DTY		Conditionalize <38> thru <41> out of the CubeE build.
		<41>	 6/26/91	EMT		Add support to kill PPCInform calls
		<40>	 6/12/91	EMT		Remove code that references the number of pending messages
		<39>	 6/10/91	EMT		Check for duplicate completion.
		<38>	  6/4/91	EMT		Roll in StoreAndForward Revisions
		<37>	 1/22/91	EMT		VC: Add prototype OpenUGBT
		<36>	 1/11/91	EMT		<VC> Fix buffer related to IPCListPorts bug, reduced
									MaxListEntries from 15 to 7. Any larger than 7 is a waste of
									memory.
		<35>	12/13/90	EMT		<JSM> Support FlagShip name changes
		<34>	11/28/90	EMT		<VC> Add prototype for FakeCompletion, and DMFix.
		<33>	 11/8/90	EMT		<stb> Add a link field to the UserEntry structure, and change
									the globals to contain a queue of user entries in palce of the
									expensive array. This should help cut down on memory use, since
									most of the time 16 refnums are not being used.
		<32>	 11/6/90	EMT		Remove CheckLocName and add two new functions to take its place
		<31>	10/30/90	EMT		Modify TOP_OF_RECORD_PTR to work around bug in MPW 3.2b3
									compiler.
		<30>	10/24/90	EMT		Add prototype for PPCRemove in PPCPatch.a
		<29>	10/19/90	JSM		Update prototypes for PPCEntry.c.
		<28>	10/18/90	EMT		Remove atDrvrVersNum, use PPCPortRefNum and PPCSessRefNum
	   								in the globals.  Change field name from userName to machineName.
									Fixed many structures that have character arrays 32 bytes, when
									they needed to be declared as Str32.
		<27>	10/12/90	EMT		Update for new record definitions.
		<26>	 9/26/90	EMT		Remove prototypes for functions used only in 1 file
		<25>	 9/21/90	EMT		Update constants, types, and field names as dictated by
									PPCToolBox.h
		<24>	 9/15/90	ngk		Changed quoting to fix search path for ppcToolBox.h
		<23>	 9/14/90	EMT		change prototypes
		<22>	 9/14/90	VC		Changed "nextUserRef" in the Global and "ref" in the UserEntry
									to be a unsigned long.
		<21>	 9/14/90	VC		(type Return by accident when entering comments)
		<20>	  9/5/90	EMT		Change the field name (Size) within the QUEUE type to qSize.
									This prevents C3.0 from blowing up.
		<19>	  9/4/90	EMT		Eric's Changes rolled in
		<18>	 8/10/90	S		To Include Constants to Get String Resources for PPCToolBox and
									Default Login.
		<17>	  8/8/90	S		Included SleepQue Element in PPCGlobalParams.
		<16>	 6/28/90	S		To Improve the dynamic allocation scheme and fix other bugs.
		<15>	  6/1/90	EMT		Adding prototypes for RepostConnectionListener
		<14>	  6/1/90	VC		Added the definition of iacDisabled.
		<13>	 5/31/90	EMT		Added support for force ending of network sessions that did not
									originate on host machine
		<12>	 4/17/90	JSM		Comment out unused fields in BTFileInfo.
		<11>	 4/17/90	JSM		#ifdef ppcPrep field in globals.
		<10>	 4/10/90	S		Gestalt Support and Global PPCCheck Box support.
		 <9>	 3/21/90	S		To Include Configuration Params.
		 <8>	 3/20/90	S		To Add Configurable Parameter Record to Globals.
		 <6>	 2/28/90	S		Fix IPCListPort Call with GuestIcon Enabled.
		 <5>	 2/27/90	S		include noGuestEnabled definition.
		 <4>	 2/27/90	S		To use Guest Record for user&Groups.
		 <3>	 2/13/90	S		Change AtalkEvent Constants.
		 <2>	12/28/89	dba		use quotes around the names of local header files, angle
									brackets around the names of header files from Interfaces or
									Internals
	   <1.3>	10/12/89	CCH		Fixed header
	  <•1.2>	10/12/89	CVC		Added access control stuff
	   <1.1>	 9/25/89	ss		Added Support for 'more' in PPCWrite calls.
	   <1.0>	 9/18/89	CVC		Adding PPC toolbox for the first time.


	   Old Revision History:

		07/20/89    	Sangam      1.0d2 release today!
		07/25/89		Sangam		Added RemoveName and ClosePortCompletion
		08/10/89		Sangam      Made Changes for IPCListPorts call
		09/22/89 		Sangam		Removed destportName and destlocname from session data structure
		09/25/89		Sangam		Added Support for 'more' in PPCWrite calls

*/

#ifndef __PPCCOMMON__
#define __PPCCOMMON__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __ERRORS__
#include <Errors.h>
#endif

#ifndef __RESOURCES__
#include <Resources.h>
#endif

#ifndef __TOOLUTILS__
#include <ToolUtils.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __DEVICES__
#include <Devices.h>
#endif

#ifndef __POWER__
#include <Power.h>
#endif

#include <BTEqu.h>
#include "UserGroup.h"

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif

#ifndef __ADSP__
#include "ADSP.h"
#endif

#ifndef __PPCTOOLBOX__
#include <PPCToolBox.h>
#endif

#ifndef __STDDEF__
#include <StdDef.h>
#endif

#define TOP_OF_RECORD_PTR(ptr,type,field) (type *)(((char *)ptr) - offsetof(type,field))

#define kNoInterrupts 0x2500		// Set status register to this when we don't want any interrupts.

/*----------------------------------------------------------------------------------------
	PPCCommand Values
----------------------------------------------------------------------------------------*/
#define PPCOpenCall          1
#define PPCStartCall         2
#define PPCInformCall        3
#define PPCAcceptCall        4
#define PPCRejectCall        5
#define PPCWriteCall         6
#define PPCReadCall          7
#define PPCEndCall           8
#define PPCCloseCall         9
#define IPCListPortsCall 	10

/*----------------------------------------------------------------------------------------
	Port & Session States
----------------------------------------------------------------------------------------*/
#define Free                 0
#define inUse                1

#define AwaitLookupResp      3
#define AwaitDSPInit         4
#define AwaitOpenComp        5
#define AwaitAcceptResp      6
#define AwaitAcceptReq       7	// Inform has completed, waiting for client.
#define DataXferState        8
#define AwaitAbortComp       9
#define AwaitStartSendComp  10
#define AwaitAcceptSendComp 11
#define AwaitRejectComp     12

#define AwaitRecvDSPInit    14
#define AwaitocAcceptComp   15
#define AwaitRecvSessReq    16

#define	AwaitListSendComp   17
#define	AwaitListRead		18
#define	AwaitListResp		19
#define	AwaitListWriteComp	20
#define AwaitListRespComp	21

#define AwaitBtreeComp      22
#define AwaitRandWrite      23
#define AwaitAuthResp       24
#define AwaitAuthRespSend	25
#define AwaitAuthAccept     26

/*----------------------------------------------------------------------------------------
	Since Beta systems are built without MacsBug symbols, but a map is generated, static
	declared functions will be difficult to find.  But static makes the code easier to maintain
	when trying to figure out the scope of a change.  So I introduce a #define STATIC that has the
	semantic meaining to the programmer, but not to the linker and compiler.
----------------------------------------------------------------------------------------*/
#ifdef INITVERSION
#define STATIC static
#else
#define STATIC
#endif

/*----------------------------------------------------------------------------------------
	Keys used in scrambling names and passwords.
----------------------------------------------------------------------------------------*/
#ifdef DEBUG	// Keep it cleartext in case we are in debug mode.
#define kNameKey 0
#define kPassWordKey 0
#else
#define kNameKey 0xA5
#define kPassWordKey 0x5A
#endif

/*----------------------------------------------------------------------------------------
	For Portable
----------------------------------------------------------------------------------------*/
#define SleepQueType	16
#define sleepRequest	1
#define sleepDemand		2
#define WakeupCall		3

/*----------------------------------------------------------------------------------------
	Other misc. defines
----------------------------------------------------------------------------------------*/
#define metaCharacter   '='  // meta character
#define lkupbufSize 200                   // Buffer for NBPLookup call

#define kPPCPriority 0

/*----------------------------------------------------------------------------------------
	Network Session Data Structre
----------------------------------------------------------------------------------------*/
#define  SendDataSize    1024
#define  RecvDataSize    1024
#define  DspSendQSize    SendDataSize + SendDataSize/8 +1
#define  DspRecvQSize    RecvDataSize + RecvDataSize/8 +1
#define  MaxListEntries  7   // Maximum number entries that can be packed in a single packet

#define  SessRequest      'SREQ'   // Session Request
#define  SessAccept       'SAPT'   // Session Accept
#define  SessReject       'SREJ'   // Session Rejct By PPCToolBox
#define  ListRequest      'LPRT'   // List Port Names
#define  ListResp         'LRSP'   // List Response
#define  UserReject       'UREJ'   // user made the rejection
#define  AuthContinue	  'ACNT'   // Continue with Authentication
#define  AuthInfoResp     'ARSP'   // Packet has Authentication Info Response

/*----------------------------------------------------------------------------------------
	Reasons for session Reject by the system (SREJ)
----------------------------------------------------------------------------------------*/
#define notVisible          1   // user has set port networkVisible to false
#define noPort              2   // Requested Port was not found
#define noUserRec			3   // noUser Rec for the used
#define AuthFailure			4   // Authentication Falied
#define noInforms			5   // No Outstanding Informs
#define noGuestEnabled      6   // Guest is not enabled
#define iacDisabled	        7   // IAC Switch disabled

#define  locUse       0
#define  netUse       1
#define  ipmUse       2

#define  LocSessType 	0x40000000
#define  NetSessType 	0x80000000
#define  IpmSessType 	0xc0000000

#define  MaxSessRefNum  0x3fffffff


#define MAX_LOGIN		16
#define BTCacheSize		8				// ???????????????????????????

/*----------------------------------------------------------------------------------------
	AppleTalk Events.  These declarations should be in AppleTalk.h, so when they are, delete
	these.
----------------------------------------------------------------------------------------*/
#ifndef AOpenTask
#define	AOpenTask					0					//	.MPP just opened
#define	AReservedTask				1					//	reserved
#define	ACloseTellTask				2					//	.MPP is closing down
#define	ACloseAskTask				3					//	Ok for .MPP to close?
#define	ACanclAskTask				4					//	.MPP Close was Cancelled
#define	ANetworkTransition			5					//	.MPP Network ADEV transition
#define	ANameChangeTellTask			6					//	NBP Name has changed
#define	ANameChangeAskTask			7					//	Ok to change NBP Name?
#define	ACancelNameChange			8					//	NBP Name Change was cancelled
#endif

/*----------------------------------------------------------------------------------------
	The following should be defined within Gestault.h, when they are, remove them from here.
----------------------------------------------------------------------------------------*/
#ifndef gestaltFlagshipAttr
#define	gestaltFlagshipAttr				'flag'
#define	gestaltFlagshipPresent			0			//	Flagship is installed
#define	gestaltFlagNameRegistered		1			//	A Flagship name is registered
#endif

/* Values for call Completion flag */
#define ReadWriteComp   1
#define NoReadWriteComp 0

typedef struct ELEMENT
{
	struct ELEMENT *Next;
}ELEMENT;

typedef struct QUEUE
{
	ELEMENT *Head;
	ELEMENT *Tail;
	long	qSize;
}QUEUE;

typedef struct PortLocationTable
{
	NBPparms            nbpPB;				// PB for making NBP Calls
	NamesTableEntry 	nteQEle;   			// ppcToolBox NBP name holder (RegName)
	Str32				typeStr;			// NBP Type used when opening the port
	struct PPCPortEntry *portPtr;			// pointer to the PPCPortEntry
}PortLocationTable, *PortLocationTablePtr;

typedef struct PPCPortEntry
{
	void 					*next;				// Queue Link.
	PPCPortRefNum			portRefNum;			// Port Identifier
	unsigned short			sessCount;			// Number of sessions open on this port.
	unsigned char   		serviceType;		// What type of service (RealTime, or StoreForward or Both)
	Boolean					authRequest;		// Is user required to be authenticated
	Boolean					networkVisible;		// Is this port visible over the network
	Boolean					nbpRegistered;		// Was this locationName was nbp registered
	QUEUE					informPBQueue;		// Linked list of pending PPCInform calls.
	Ptr             		openPB;				// Pointer to the User PB in the PPCOpen Call
	PPCPortRec      		portName;			// Port Name
	PortLocationTablePtr	locationInfo;		// NBP or NAS name to locate this port on the network
	#ifdef IPMIncluded
	PMQueueRef		PortQueueRef;			// IPM Queue reference number for this port.
	PMSeqNum		lastSeqNum;				// Last Sequence Number informed called on.
	PMParamBlock	PB;						// PB used for opening a queue.
	#endif
} PPCPortEntry, *PPCPortEntryPtr;

#define SessionHeader \
	void					*Next;			/* Q-Link */\
	unsigned short			sessState;		/* Session State */\
	unsigned char			sessUse;		/* Session is used for LOCALIPC or NETIPC or IPM */\
	Boolean					readMore;		/* If true don't read header again */\
	Boolean					writeHdr;		/* If true write header (To support 'more' in PPCWrite */\
	Boolean					originator;		/* if true, I started the session, false if inform accepted. */\
	PPCSessRefNum			sessRefNum;		/* Session Identifier */\
	unsigned long			conRef;			/* Connection Reference */\
	PPCPortEntryPtr			portEntry;		/* Pointer to Port owning this session */\
	PPCEndPBPtr				endPB;			/* end PB, or NULL */\
	QUEUE					readQueue;		/* Queue of pending reads */\
	QUEUE					writeQueue;		/* Queue of pending writes */\
	PPCReadPBPtr			readPB;			/* Current ReadPB */\
	PPCWritePBPtr			writePB;		/* Current WritePB */\
	void					*PBPtr			/* Other single PB's are kept here */

typedef struct CommonSessionParams
{
	SessionHeader;
} CommonSessionParams, *CommonSessionParamsPtr;

/* Intra Machine Session Data Structure */
typedef CommonSessionParams LocalIPCParams, *LocalIPCParamsPtr;

typedef struct IPCStartBlk
{
	unsigned long	reqType;		// Session Request Type
	unsigned long	userData;		// Msg Type for the session Request
	PPCPortRec      reqportName;	// Requestors Port Name
	PPCPortRec      destportName;	// Destination Port Name
	LocationNameRec	locationName;	// Requestors Port Location
	Str32			userName;		// User's name for authentication
}IPCStartBlk, *IPCStartBlkPtr;

typedef struct IPCListReqBlk
{
	unsigned long	reqType;		// Session Request Type
	unsigned short	startIndex;     // Start Index
	unsigned short	requestCount;   // Number of entries to be returned
	PPCPortRec		portName;       // Port Name we are looking for
	Str32			userName;		// Not Required.
}IPCListReqBlk, *IPCListReqBlkPtr;

typedef struct IPCListRespBlk
{
	unsigned long	respType;        // Session Request Type
	unsigned short	actualCount;    // Actual Number of entries to be returned
}IPCListRespBlk, *IPCListRespBlkPtr;

typedef struct IPCAcceptBlk
{
	unsigned long respType;
	unsigned long rejectInfo;
} IPCAcceptBlk, IPCRejectBlk, *IPCAcceptBlkPtr, *IPCRejectBlkPtr;

typedef struct IPCHdrBlk
{
	OSType blockCreator;	// Msg Block Creator
	OSType blockType;		// Message Block Type
	long userData;			// user filed
} IPCHdrBlk, *IPCHdrBlkPtr;

typedef struct AuthInfoBlk
{
	unsigned long respType;    // Type of authentication response
	unsigned long authInfo[2]; // Authentication Information
} AuthInfoBlk, *AuthInfoBlkPtr;

typedef struct IPCBufBlk
{
	union
	{
		IPCStartBlk       startBlk;
		IPCAcceptBlk      acceptBlk;
		IPCRejectBlk      rejectBlk;
		IPCHdrBlk         headerBlk;
		IPCListReqBlk     lreqBlk;
		IPCListRespBlk    lrespBlk;
		AuthInfoBlk       authBlk;
	} buffer;
}IPCBufBlk, *IPCBufBlkPtr;

typedef struct IPCReadBlk
{
	DSPParamBlock	dsp;		// ADSP PB
	IPCBufBlk		buffer;		// Buffer for IPC's Internal Reads/Writes
	AuthInfoBlk		authBuf;	// Buffer to receive auth verification
} IPCReadBlk, *IPCReadBlkPtr;

typedef struct
{
	DSPParamBlock	dsp;		// ADSP PB
	IPCBufBlk	buffer;			// Buffer for IPC's Internal Reads
} IPCWriteHdrBlk,IPCWriteBlk, *IPCWriteBlkPtr;

typedef struct PPCSessionNBP
{
	NBPparms            nbpPB;							// PB for making NBP Calls
	unsigned char       lkupentity[sizeof(EntityName)];	// LookUp entity
	unsigned char       lkupbuf[lkupbufSize];			// LookUp buffer
} PPCSessionNBP, *PPCSessionNBPPtr;

typedef struct BTKey
{
	char keyLen;
	char keyFiller;
	long dirID;
	Str31 CName;
}BTKey;

typedef struct UserRecPb
{
	BTioParam	btPb;						// PB for B-Tree calls
	ProcPtr		usrCompletion;
	union
	{
		UserAcRecord	record;				// Returns user record
		ULInfoRecord    ulRecord;
	}u;
	long			random[2];				// Random Number
	long			encryptedRandom[2];		// Random Number
	unsigned short  guestRec;				// Guest Boolean
	BTKey			key;
} UserRecPb, *UserRecPbPtr;

typedef union
{
	PPCSessionNBP nbpData;
	UserRecPb	  btreeData;
} SessMiscData, *SessMiscDataPtr;

typedef struct NetIPCParams
{
	SessionHeader;
	Boolean				abortFlag;					// Used durning an abort.
	SessMiscData        miscData;					// NBP lookup and Btree Data
	AddrBlock           destAddr;					// Destination Address
	TRCCB               ce;							// Connection End (CE) Memory
	unsigned char       attnBuffer[attnBufSize];	// Attention Buffer for CE
	unsigned char       sendQ[DspSendQSize];		// SendQ Buffer
	unsigned char       recvQ[DspRecvQSize];		// RecvQ Buffer
	IPCReadBlk          readBlk;					// IPC ReadBlock
	IPCWriteBlk         writeBlk;					// write Block
	Str32				userName;					// user who started with me.
} NetIPCParams, *NetIPCParamsPtr;

typedef struct
{
	PPCPortRec	srcPPCPortRec;
	Str32		userName;
	long		userData;
}IPMInformData;

typedef struct
{
	OSType	blockCreator;
	OSType	blockType;
	unsigned long userData;
	unsigned long blockLength;
}PPCRWData;

/* IPM Session Data Stucture */
typedef struct IPMParams
{
	SessionHeader;
#ifdef IPMIncluded
	PPCInformParamsPtr	InformPB;					// User's Inform PB.
	PMMsgRef			msgRef;						// Refnum of IPM Session.
	PMParamBlock		PB;							// PB used during IPM Session.
	PMFixedHdrInfo		FixedInfo;					// Fixed info obtained from sess.
	IPMInformData		informData;					// 1st block in Msg.
	unsigned long		topOfBlock;					// Offset to current block.
	unsigned long		endOfMsg;					// Offset to end of msg.
	PPCRWData			rwData;						// At beginning of each data block.
#endif
}IPMParams, *IPMParamsPtr;


typedef struct ListenerParams
{
	TRCCB               ce;      // Connection End (CE) Memory
	DSPParamBlock       dsp1;    // ADSP PB1
	DSPParamBlock       dsp2;    // ADSP PB2
}ListenerParams, ListenerParamsPtr;

typedef struct UserEntry
{
	void			*next;
	unsigned long	ref;
	Str32			name;
	char			password[9];
	char			stuff;
} UserEntry, *UserEntryPtr;

typedef struct BTFileInfo
{
	short refNum;
} BTFileInfo, *BTFileInfoPtr;

typedef struct StartSecureParam
{
	StringPtr		prompt;
	Boolean			*guestSelected;
	Boolean			allowGuest;
	char			stuff1;
	Boolean			useDefault;
	char			stuff2;
	StringPtr		userName;
	PPCStartPBPtr	startPb;
} StartSecureParam,	*StartSecureParamPtr;

typedef struct GetDefaultParam
{
	StringPtr		userName;
	unsigned long	*userRef;
} GetDefaultParam,*GetDefaultParamPtr;
	
typedef struct PPCConfigInfo
{
	unsigned char freePortMin;
	unsigned char freePortMax;
	
	unsigned char freeLocSessMin;
	unsigned char freeLocSessMax;
	
	unsigned char freeRemSessMin;
	unsigned char freeRemSessMax;
	
	unsigned char freeIPMSessMin;
	unsigned char freeIPMSessMax;
	unsigned char adspTimeout;       // ADSP time out (6 = 1 sec)
	unsigned char adspRetries;      // ADSP Retries     
	unsigned char nbpTimeout;       // NBP time out interval 8-tick units
	unsigned char nbpRetries;      // NBP retries
	
	Str32			ppctoolboxName;		// Our IPCToolBoxName
	
} PPCConfigInfo, *PPCConfigInfoPtr;


typedef struct PPCGlobalParams
{
	unsigned long		inEntry;					// Nesting level of PPCEntry.
	Boolean				canLocal;          			// Support local IPC.
	Boolean				canRemote;		 			// Support remote IPC.
	Boolean				canIPM;						// Support StoreAndForward.
	Boolean				allowIncommingRequests;		// Accept Incoming Requests.
	Boolean				mppOpen;					// True if MPP driver is open.
	Boolean				unused2;

	Boolean				unused3;
	Boolean				inited;						// PPC has been initialized.
	
	QUEUE				UserEntryQueue;				// Linked list of user entries.
	QUEUE				BeginLRQueue;				// Linked list of PPCStart and IPCListPorts.
	QUEUE				freePortQueue;				// Linked list of free ports.
	QUEUE				freeLocationQueue;			// Linked list of free NBP Location tables

	QUEUE				freeLocSessQueue;			// Linked list of free session tables (for local use).
	QUEUE				freeRemSessQueue;			// Linked list of free session tables (for remote use).
	QUEUE				freeIPMSessQueue;			// Linked list of free session tables (for IPM use).	
	QUEUE				OpenPortQueue;				// Linked list of ports that are open.
	QUEUE				LocSessQueue;				// Linked list of local sessions that are active.
	QUEUE				RemSessQueue;				// Linked list of remote sessions that are active.
	QUEUE				IPMSessQueue;				// Linked list of IPM sessions that are active.
	QUEUE				dspAbortQueue;				// Queue of sessions to be aborted.
	QUEUE				CompletedPBQueue;			// Client PB's that are completed.
	QUEUE				ListSessQueue;				// Linked list of remote List Session requests waiting.

	NetIPCParams		*listsessPtr;				// Active list session request.
	NetIPCParams		*killSessPtr;				// Pointer to current session being killed.
	OSErr				netErr;						// Network error which caused localOnly Condition

	short				dspDrvrRef;					// ADSP driver Reference
	unsigned char		adspSocket;					// ADSP Socket Number
	unsigned char		guestUnchecked;				// guestUnchecked for IPC ListPorts.
	PPCPortRefNum		nextPortRefNum;				// Next Port Identifier
	PPCSessRefNum		nextSessRefNum;				// Next Session Identifier
	unsigned long		nextUserRef;				// Next user reference number
	PPCConfigInfo		configData;					// Configuration Info
	Str32				machineName;				// user Name
	Str32				zoneName;					// Our current zone
	unsigned char		whichName;					// Index to active name.				
	Boolean				AltNameRegistered;			// True if 2 PPCToolboxes registered.
	NamesTableEntry		nteQEle[2];					// ppcToolBox NBP name holder (RegName)


	ListenerParams		dspListener;				// Buffer for ADSP Listener
	PortInfoRec			listBuffer[MaxListEntries];	// list buffer (for listport)
	unsigned short		totalCount;					// used for listports call
	unsigned short		listIndex;					// used for listports call
	Boolean				listContinue;				// continue processing
	ATQEntry			trQEle;						// Apple Talk Transition QEle
	SleepQRec			sleepQEle;             		// SleepQ Element.
	BTFileInfo			ugFile;						// Info for User Group file
	Handle				ppcIcon;

	DSPParamBlock		dspRemovePB;				// Used to Abort ADSP Sessions
	XCallParam			xpb;						// Used for GetMyZone requests.
	//------------------------------- IPM Stuff here ----------------------------
	#ifdef IPMIncluded
	PMContextRef		contextRef;					// IPM Context for PPC ToolBox.
	PMComposedRecipient	PPCQueue;					// PPC's IPM Queue.
	long				theRLI;						// Empty RLI.
	EntityName			xtnValue;					// xtnValue for PPCQueue.
	RString				sender;						// sender for PPCToolBox.
	#endif

} PPCGlobalParams, *PPCGlobalParamsPtr;

/* Internal usage for the Reserved field in the PB */
typedef struct PPCReserved
{
	unsigned char            cmdMode;       // Sync or Async
	unsigned char            callCmp;       // Call Completion. See PPBWriteRes
	unsigned char            unused[2];     // Network read
	unsigned char            unUsed;        // Not used For Now
	unsigned long            ApplA5;		// A5 for the application
	unsigned long            notUsed1;      // Pointer to PPC Globals
	unsigned long            notUsed2;      // Pointer to this PB's Port
	unsigned long            notUsed3;      // Pointer to this PB's Session
} PPCReserved, *PPCReservedPtr;

typedef struct PBWriteRes
{
	unsigned char            cmdMode;       // Synch or Asynch
	unsigned char            callCmp;       // Call Completion
	unsigned char            deadLock;      // whether completion routine to be called at write
	unsigned char            multiFinder;   // Indicate Multi finder about access control flags
	unsigned long            ApplA5;		// A5 for the application
	Ptr            			 curBufPos;     // Current Buffer Position
	unsigned long            length;        // Remaining length
	unsigned long            notUsed;       // Not used
} PBWriteRes, *PBWriteResPtr, PBReadRes, *PBReadResPtr;

/*----------------------------------------------------------------------------------------
	Function Type Declarations
----------------------------------------------------------------------------------------*/
typedef Boolean (*SearchFuncPtr)(void *ptr,unsigned long Value);
typedef Boolean (*BestFuncPtr)(void *Best,void *Contender);
typedef void (*FreeFuncPtr)(void *);

/*----------------------------------------------------------------------------------------
	Inline assembly functions.
----------------------------------------------------------------------------------------*/
unsigned long GetD0() = {0x2000};		/*	Move.L	D0,D0 */
unsigned long GetD1() = {0x2001};		/*	Move.L	D1,D0 */
unsigned long GetD2() = {0x2002};		/*	Move.L	D2,D0 */
unsigned long GetD3() = {0x2003};		/*	Move.L	D3,D0 */
unsigned long GetD4() = {0x2004};		/*	Move.L	D4,D0 */
unsigned long GetD5() = {0x2005};		/*	Move.L	D5,D0 */
unsigned long GetD6() = {0x2006};		/*	Move.L	D6,D0 */
unsigned long GetD7() = {0x2007};		/*	Move.L	D7,D0 */

void *GetA0() = {0x2008};		/*	Move.L	A0,D0 */
void *GetA1() = {0x2009};		/*	Move.L	A1,D0 */
void *GetA2() = {0x200A};		/*	Move.L	A2,D0 */
void *GetA3() = {0x200B};		/*	Move.L	A3,D0 */
void *GetA4() = {0x200C};		/*	Move.L	A4,D0 */
void *GetA5() = {0x200D};		/*	Move.L	A5,D0 */
void *GetA6() = {0x200E};		/*	Move.L	A6,D0 */
void *GetA7() = {0x200F};		/*	Move.L	A7,D0 */

void SetD0(unsigned long Rn) = {0x202F,0x0000};			/*	Move.L (A7),D0	*/
void SetD1(unsigned long Rn) = {0x222F,0x0000};			/*	Move.L (A7),D1	*/
void SetD2(unsigned long Rn) = {0x242F,0x0000};			/*	Move.L (A7),D2	*/
void SetD3(unsigned long Rn) = {0x262F,0x0000};			/*	Move.L (A7),D3	*/
void SetD4(unsigned long Rn) = {0x282F,0x0000};			/*	Move.L (A7),D4	*/
void SetD5(unsigned long Rn) = {0x2A2F,0x0000};			/*	Move.L (A7),D5	*/
void SetD6(unsigned long Rn) = {0x2C2F,0x0000}; 		/*	Move.L (A7),D6	*/
void SetD7(unsigned long Rn) = {0x2E2F,0x0000}; 		/*	Move.L (A7),D7	*/

void SetA0(void *Rn) = {0x206F,0x0000};			/*	Move.L (A7),A0	*/
void SetA1(void *Rn) = {0x226F,0x0000};			/*	Move.L (A7),A1	*/
void SetA2(void *Rn) = {0x246F,0x0000};			/*	Move.L (A7),A2	*/
void SetA3(void *Rn) = {0x266F,0x0000};			/*	Move.L (A7),A3	*/
void SetA4(void *Rn) = {0x286F,0x0000};			/*	Move.L (A7),A4	*/
void MySetA5(void *Rn) = {0x2A6F,0x0000};		/*	Move.L (A7),A5	*/
void SetA6(void *Rn) = {0x2C6F,0x0000};			/*	Move.L (A7),A6	*/
pascal void SetA7(void *Rn) = {0x2E6F,0x0000};	/*	Move.L (A7),A7	*/
unsigned short spl(x) = {0x40C0, 0x46EF, 0x0002};
/*
	The above inline function will genarate
		Move SR, 	D0
		Move 2(A7), SR
	and can be used to disable interrupt by calling it with kNoInterrupts
	and restore after the event.
*/

/*----------------------------------------------------------------------------------------
	Macro Procedures.
----------------------------------------------------------------------------------------*/
#define CopyPortName(n1,n2)	/* n2 <- n1 */\
	BlockMove((Ptr)n1,(Ptr)n2,sizeof(PPCPortRec))

#define CopyLocationName(l1,l2)	/* l2 <- l1 */\
	BlockMove((Ptr)l1,(Ptr)l2,sizeof(LocationNameRec))

#define CompareByte(ptr1, ptr2, length) !memcmp(ptr1,ptr2,length)

#define FOREACHELEMENT(Elm,Queue) \
	for((ELEMENT *)Elm = (Queue)->Head;Elm;(ELEMENT *)Elm = ((ELEMENT *)Elm)->Next)

#define AddReadPB(sessPtr,readPB) \
	EnQueue(readPB,&sessPtr->readQueue)

#define AddWritePB(sessPtr,wrtiePB)	\
	EnQueue(writePB,&sessPtr->writeQueue)

#define GetReadPB(sessPtr) \
	ServeQueue(&sessPtr->readQueue)

#define GetWritePB(sessPtr) \
	ServeQueue(&sessPtr->writeQueue)

/*----------------------------------------------------------------------------------------
	Prototypes from PromptForUser.a
----------------------------------------------------------------------------------------*/
pascal OSErr PromptForUser (StringPtr,Handle,StringPtr,StringPtr,
									short,
									Boolean,
									short*,
									ProcPtr,
									PPCStartPBPtr);
/*----------------------------------------------------------------------------------------
	Prototypes from BTreeCGlue.a
----------------------------------------------------------------------------------------*/
short BTSEARCHPPC (BTioParam *btioparam, short async);

/*----------------------------------------------------------------------------------------
	Prototypes from BTIntf.a
----------------------------------------------------------------------------------------*/
pascal OSErr OpenUGBT(short, long, Str255, short, short*);

/*----------------------------------------------------------------------------------------
	Prototypes for routines in maindes.o
----------------------------------------------------------------------------------------*/
pascal short BldFSKey(long keyDirID,StringPtr keyCName,Ptr keyBuf);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCAuth.c
----------------------------------------------------------------------------------------*/
OSErr ppcStartSecure (StartSecureParam *pu);
OSErr ppcGetDefaultUser (GetDefaultParam *pu);
OSErr ppcDeleteUser (unsigned long *userRef);

void scramble( unsigned char key, StringPtr pSrc, StringPtr pDest);
getUserRec (UserRecPb *urec, int keyID, char *keyName,
			int (*ppcComplete)(), short refNum);
Boolean GetAuthInfo(long *authInfo, unsigned long refNum);
UserEntryPtr findUserByRef (unsigned long ref);

/*---------------------------------------------------------------------------------------------------
	Prototypes from DSP.c
---------------------------------------------------------------------------------------------------*/
OSErr OpenADSPDriver(short *refNum);

OSErr CreateConnectionListener(Ptr ccbPtr,
							   DSPParamBlock *dsp,
							   unsigned short dspDrvrRef,
							   unsigned char  socket,
							   Boolean  async,
							   ProcPtr  compRoutine);

OSErr ListenConnectionRequest(DSPParamBlock *dsp,
							  Boolean async,
							  ProcPtr compRoutine);


void RejectConnectionRequest(DSPParamBlock *dsp, Boolean async, ProcPtr compRoutine);

OSErr RemoveConnectionListener(unsigned char abortFlag,
						  	   Boolean        async,
						  	   ProcPtr        compRoutine,
				          	   DSPParamBlock  *dsp);

OSErr CreateConnectionEnd(TRCCB *ccbPtr,
						  ProcPtr userRoutine,
						  unsigned short   sendQSize,
						  unsigned char    *sendQ,
                  		  unsigned short   recvQSize,
						  unsigned char    *recvQ,
						  unsigned char    *attnPtr,
						  unsigned char    socket,
						  short            drvrRef,
             			  Boolean          async,
						  ProcPtr          compRoutine,
						  DSPParamBlock    *dsp);

OSErr OpenConnectionEnd(unsigned short remoteCid,
				        AddrBlock      *remoteAddr,
						AddrBlock      *filterAddr,
						unsigned long  sendSeq,
						unsigned short sendWindow,
						unsigned long  attnSendSeq,
						unsigned char  ocMode,
						Boolean        async,
						ProcPtr        compRoutine,
						DSPParamBlock  *dsp);

OSErr RemoveConnectionEnd(unsigned char abortFlag,
						  Boolean        async,
						  ProcPtr        compRoutine,
				          DSPParamBlock  *dsp);


OSErr WriteToConnection(unsigned short reqCount,
						unsigned char  *dataPtr,
						unsigned char  eom,
						unsigned char  flush,
						Boolean        async,
						ProcPtr        compRoutine,
						DSPParamBlock  *dsp);

OSErr ReadFromConnection(unsigned short reqCount,
						 unsigned char  *dataPtr,
						 Boolean        async,
						 ProcPtr        compRoutine,
						 DSPParamBlock  *dsp);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCEntry.c
----------------------------------------------------------------------------------------*/
OSErr ppcOpen(PPCOpenPBPtr openPB);
OSErr ppcStart(PPCStartPBPtr startPB);
OSErr ppcInform(PPCInformPBPtr informPB);
OSErr ppcAccept(PPCAcceptPBPtr acceptPB);
OSErr ppcReject(PPCRejectPBPtr rejectPB);
OSErr ppcWrite(PPCWritePBPtr writePB);
OSErr ppcRead(PPCReadPBPtr readPB);
OSErr ppcEnd(PPCEndPBPtr endPB);
OSErr ppcClose(PPCClosePBPtr closePB);
OSErr ppcListPorts(IPCListPortsPBPtr listPB);
OSErr CompleteWithResult(void *PB,OSErr Result);
OSErr VerifyLocNameFormat(LocationNamePtr locName);
Boolean LocationNameLocal(LocationNamePtr locName);
OSErr DMFix(OSErr Result,void *thePB);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCInit.c
----------------------------------------------------------------------------------------*/
OSErr PPCSetUp(void);
pascal void PPCSHUTDOWN(void);

short PPCCountAcceptedNetworkSessions(unsigned char *userName);	// <42>
OSErr PPCCloseUserSessions(unsigned char *userName);			// <42>
OSErr PPCCheckDupNBPName(void);									// <42>

pascal OSErr PPCGESTALTFUNCTION(long selector, long *myResp);
OSErr PPCSystemTask(void);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCLocal.c
----------------------------------------------------------------------------------------*/
void StartLocalSession(PPCStartPBPtr			startPB,
						PPCPortEntryPtr			srcportPtr,
						PPCGlobalParamsPtr		ppcglobPtr);

void AcceptLocalSession(PPCAcceptPBPtr			acceptPB,
						 CommonSessionParamsPtr destSess,
						 PPCGlobalParamsPtr		ppcglobPtr);

void RejectLocalSession(PPCRejectPBPtr			rejectPB,
						 CommonSessionParamsPtr destSess,
						 PPCGlobalParamsPtr     ppcglobPtr);

void WriteLocalData(PPCWritePBPtr			writePB,
					CommonSessionParamsPtr	srcSess,
					PPCGlobalParamsPtr     	ppcglobPtr);

void ReadLocalData(PPCReadPBPtr				readPB,
					CommonSessionParamsPtr		destSess,
					PPCGlobalParamsPtr			ppcglobPtr);

void EndLocalSession(PPCEndPBPtr				endPB,
					  CommonSessionParamsPtr	srcSess,
					  PPCGlobalParamsPtr		ppcglobPtr);

void ListLocalPorts(IPCListPortsPBPtr listPB,PPCGlobalParamsPtr ppcglobPtr);

/*---------------------------------------------------------------------------------------------------
	Prototypes from PPCNbp.c
---------------------------------------------------------------------------------------------------*/
OSErr RegisterName(unsigned char *objName,
				   unsigned char *objType,
				   unsigned char *zone,
				   unsigned char socket,
				   Boolean       async,
				   ProcPtr       compRoutine,
				   Ptr           ntePtr,
				   NBPparms      *nbpPB);

OSErr LookupName(EntityName     *name,
				 Boolean        async,
				 ProcPtr        compRoutine,
				 unsigned char  *bufPtr,
				 short          bufSize,
				 NBPparms       *nbpPB);

OSErr RemoveName(EntityName *name,
				 Boolean	async,
				 ProcPtr 	compRoutine,
				 NBPparms	*nbpPB);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCNetwork.c
----------------------------------------------------------------------------------------*/
void StartNetworkSession(PPCStartPBPtr  startPB,
						  PPCPortEntryPtr    portPtr,
						  PPCGlobalParamsPtr ppcglobPtr);

void AcceptNetworkSession(PPCAcceptPBPtr      acceptPB,
						   NetIPCParamsPtr  sessPtr);

void RejectNetworkSession(PPCRejectPBPtr rejectPB,
						   NetIPCParamsPtr sessPtr);

void WriteNetworkData(PPCWritePBPtr writePB,
					   NetIPCParamsPtr  sessPtr);

void ReadNetworkData(PPCReadPBPtr readPB,
					  NetIPCParamsPtr  sessPtr);

void EndNetworkSession(PPCEndPBPtr endPB,NetIPCParamsPtr sessPtr); 

void ListNetworkPorts(IPCListPortsPBPtr listPB,PPCGlobalParamsPtr ppcglobPtr);

void ConnectionRequestCompletion(void);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCPatch.a
----------------------------------------------------------------------------------------*/
Ptr setupGlobal(long length);

OSErr PPCRemove(void);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCPort.c
----------------------------------------------------------------------------------------*/

OSErr ClosePortTable(PPCClosePBPtr		closePB,
					PPCPortEntryPtr		portPtr,
					PPCGlobalParamsPtr	ppcglobPtr);

void CompleteClosePort(PPCPortEntryPtr portPtr);

PPCPortEntryPtr CheckPortName(PPCPortPtr portName,PPCGlobalParamsPtr ppcglobPtr);
Boolean ValidPortName(PPCPortPtr name);
Boolean ComparePortName(PPCPortPtr name1,PPCPortPtr name2);

void GetLocationName(PPCGlobalParamsPtr	ppcglobPtr,
					 PPCPortEntryPtr portPtr,
					 LocationNamePtr locationName);

PPCPortEntryPtr DeletePortByRefNum(unsigned short portRefNum,PPCGlobalParamsPtr ppcglobPtr);
PPCPortEntryPtr PortRefNumtoPtr(unsigned short portRefNum,PPCGlobalParamsPtr ppcglobPtr);

PPCPortEntryPtr GetPortTable(PPCOpenPBPtr openPB,PPCGlobalParamsPtr ppcglobPtr);

void FreePortTable(PPCPortEntryPtr portPtr);

void SetPortInformQue(PPCInformPBPtr PB,PPCPortEntryPtr  portPtr);


Boolean GetPortNames(PPCGlobalParamsPtr	ppcglobPtr,
					 PPCPortPtr			name,
					 Boolean			local, 
					 Boolean			guestUnChecked,
					 unsigned short		index,
					 PortInfoPtr		buffPtr,
					 unsigned short		reqCount,
					 unsigned short		*actCount);

/*----------------------------------------------------------------------------------------
	Prototypes from PPCSession.c
----------------------------------------------------------------------------------------*/
CommonSessionParamsPtr SessRefNumtoPtr(PPCSessRefNum sessRefNum,PPCGlobalParamsPtr ppcglobPtr);
CommonSessionParamsPtr DeleteSessByRefNum(PPCSessRefNum sessRefNum,PPCGlobalParamsPtr ppcglobPtr);

unsigned long GetSessionRefNum(unsigned char sessUse,PPCGlobalParamsPtr ppcglobPtr);

void SetSessionTable(CommonSessionParamsPtr sessPtr,
					 PPCPortEntryPtr        portPtr,
					 PPCGlobalParamsPtr     ppcglobPtr);

void CleanSessions(PPCPortEntryPtr portPtr,PPCGlobalParamsPtr ppcglobPtr);
void KillReadAndWrite(void *sessPtr);

/*----------------------------------------------------------------------------------------
	Prototypes for PPCUtil.a
----------------------------------------------------------------------------------------*/
void AddtoAtalkQ(Ptr tranQEle);
void RmvfromAtalkQ(Ptr tranQEle);
PPCGlobalParamsPtr getGlobal(void);
unsigned short callCompletion(PPCParamBlockPtr PB, OSErr cmdResult);
void FakeCompletion(void *);
/*----------------------------------------------------------------------------------------
	Prototypes for PPCUtilities.c
----------------------------------------------------------------------------------------*/
Boolean PointerCompare(void *ptr,unsigned long Value);
void EnQueue(void *Element,QUEUE *Queue);
void *ServeQueue(QUEUE *Queue);
void *SearchQueue(QUEUE *Queue,unsigned long Value,SearchFuncPtr SearchFunc,int Nth);
void *DeleteFromQueue(QUEUE *Queue,unsigned long Value,SearchFuncPtr SearchFunc);
void DeleteMultiple(QUEUE *Queue,unsigned long Value,SearchFuncPtr DoProc);

void *NewMem(long len);
void DisposeMem(void *Mem);

void Replenish(PPCGlobalParamsPtr ppcglobPtr);
void Excess(PPCGlobalParamsPtr ppcglobPtr);

#endif