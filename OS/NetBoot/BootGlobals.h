/*EASE$$$ READ ONLY COPY of file ÒBootGlobals.hÓ
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */


extern void myListener();	/* These are asm lang. code */
extern QElemPtr DeQReqBuf(QHdr *quePtr,QElemPtr aptr);
extern void processQueue();
extern void processVBL();
extern void delayMilSec(short);
extern void readUserRecord();
extern void	sendUserRecord();
extern void closeUserRecord();
extern void	readImage();
extern void writeImage();
extern void closeImage();
extern void writeUserRecord();
extern void sendUpdateReply();

typedef char block[disksector];


typedef struct
{
	char	serverName[34];	/* server name to boot off of */
	char	serverZone[34];	/* and the zone it lives in */
	char	serverVol[34];	/* and the volume name */
	short	serverAuthMeth;	/* authentication method to use (none, clear txt, rand) */
	int		sysDirID,		/* the dir id of the blessed folder there */
			userDirID;		/* and of the user folder */
}OlduserRecord;


// This defines the portion of a user record which should
// be stored on disk by the boot server.
typedef struct
{
	long	finderInfo[8];					// blessed folder dir id, startup folder dir id etc...
	char	bootBlocks[135];				// see Inside Mac V-135
}store;	

// This defines a user record.
// Some of these fields can be determined on the fly by the boot server,
// while others are stored on disk by the boot server
typedef struct
{
	char	serverName[serverNameLength];	// server name to boot off of 
	char	serverZone[zoneNameLength];		// and the zone it lives in
	char	serverVol[volNameLength];		// the volume name
	short	serverAuthMeth;					// authentication method to use (none, clear txt, rand)
	long	sharedSysDirID;					// dir id of shared system folder
	long	userDirID;						// dir id of the user's private system folder
	store	storeage						// fields to be stored on disk for the user
}userRecord;


// This defines the user-record reply sent to workstations.
typedef struct
{
	char			Command;	/* record reply command */
	char			pversion;	/* version of boot protocol spoken by requestor */
	short			osID;		/* type and version of os */
	long			userData;	/* time stamp goes here */
	short			blockSize;	/* number of bytes per block */
	short			imageID;	/* image ID */
	short			result;		/* error codes */
	long			imageSize;	/* size of image in blocks */
	userRecord		userRec;	/* the user's "boot blocks" */
}UserRecReply;


// This defines the user-record-update reply sent to workstations.
typedef struct
{
	char			Command;	/* record update command */
	char			pversion;	/* version of boot protocol spoken by requestor */
	short			result;		/* results of update */
	long			userData;	/* stamp goes here */
}UserUpdateReply;



// This defines the image reply sent to workstations.
typedef struct
{
	char			Command;		/* type of request this is */
	char			pversion;		/* version of this protocol */
	short			imageID;		/*  ?  */
	short			blockNum;		/* block number of this image */
	block			data;			/* the actual block of data */
}ImageReply;



typedef struct
{
	char			Command;		/* type of request this is */
	char			pversion;		/* version of this protocol */
	short			imageID;		/*  ?  */
	short			result;			/* error field */
}ImageDone;



typedef struct
{
	short			osID;						/* type and version of os */
	long			userData;					/* time stamp goes here */
	char			userName[userNameLength]; 	/* key to finding thier record */
}urr;	// User Record Req


typedef struct
{
	short			imageID;			/* the image being requested */
	char			section;			/* "section" of the image the bitmap refers to */
	char			flags;				/* bit 0 means to send entire image */
	short			replyDelay;			/* minimum needed inter-packet delay in milliseconds */
	char			bitmap[bitmapsize];	/* bitmap of the section of the image requested */
	Boolean			done;				/* true when bitmap clear */
	Boolean			ORflag;				/* used by server when replying: notes if bitmap has been ORed */
	unsigned short	lastblk;			/* "	": an index used to tell what blk was last sent */
}bir; // Boot Image Req


typedef struct
{
	short			osID;						/* type and version of os */
	long			userData;					/* time stamp goes here */
	char			userName[userNameLength]; 	/* key to finding thier record */
	userRecord		userRec;					/* the user's "boot blocks" */
}uru; // user record update request


// This defines the structure of queue element that are designed to hold
// all request (of all boot protocol types) received from workstations.
typedef struct
{
    QElem			*qLink;		/* all request are placed in a queue */
    short 			qType;		/* not used */
	unsigned short	netnum;		/* the network this request comes from */
	unsigned char	node;		/* the node this request comes from */
	char			Command;	/* type of request this is */
	char			pversion;	/* version of boot protocol spoken by requestor */
	char			filler;
	union{							
		urr			urr;		/* user record request */
		bir			bir;		/* boot image request */
		uru			uru;		/* user record update request */
	}reqtype;
}requestBuf;


typedef struct {
	short			os;
	short			version;		
	short			imageSize;
	short			delay;
}bootRez;


// An array of the following will keep info about 
// each os we support handy.
typedef struct
{
	long		imageSize;		/* # of blocks in the image  */
	short		fileRefNum,		/* images kept open at all times, store file ref num here */
				imageVersion,	/* version of this image */
				delay;			/* server suggested minimum inter-packet delay */
}oosDataRec;


// An linked-list of the following will keep info about 
// each os we support handy.
typedef struct
{
	long		link;			/* for the linked list */
	long		imageSize;		/* # of blocks in the image  */
	short		fileRefNum,		/* images kept open at all times, store file ref num here */
				imageVersion,	/* version of this image */
				delay;			/* server suggested minimum inter-packet delay */
}osDataRec;

typedef struct
{				
	long			Next;			/* this is just a portion of the tStatRec Record taken */
	long			Filler0;		/* from the AppleShare file server code.  Server needs */
	short			VersionID;		/* it to get a ptr to the server name string. */
	short			MaxVolCount;
	long			Last;
	short			numSessions;
	short			currReqs;
	StringPtr		SrvrNamePtr;	/* we need this when we register ourselves */
} serverinfo;



// we define our own vbl record so that we can carry
// around a ptr to our server globals
typedef struct
{
	VBLTask		standard;		// this is the normal vbl record
	Ptr			globalsPtr;		// here we will carry a ptr to our globals
}myVBLTask;
	
	

/*
	Global variables.
*/
typedef struct 
{
	requestBuf		*gbufptr;
	requestBuf		*gcurrentReqPtr; 	// all asynch calls use this to get at current request buffer
	QHdr			gFreeLst;			// a queue of free buffers 
	QHdr			gUserRecReq;		// a queue of user-record requests
	QHdr			gImageReq;			// a queue of boot-image request
	QHdr			gUserUpdateReq;		// a queue of user-record-update requests
	short			gintlevel;			// flag to control asynch processing (keep only one outstanding at a time)
	UserRecReply	gmyUserRecReply;
	ImageReply		gmyImageReply;
	UserUpdateReply gmyUserUpdateReply;
	ImageDone		gmyImageDone;
	ParamBlockRec	gPBrec;				// this is for making asynch file calls (8 bytes)
	MPPParamBlock	gmyddpWrite;  		// for ddp write
	AddrBlock		gmydestAddr;		// ditto
	char			gmyheader[18];		// ditto
	char			gmywds[600];		// ditto
	HParamBlockRec	gmyHPB;
	MPPPBPtr		gddppbptr;
	MPPPBPtr		gnamepbptr;
	OSErr			gerrCode;
	short			gmyNode;
	short			gmyNet;
	short			gworkLoad;
	myVBLTask		*gVBL;				// ptr to VBLTask in the system heap
	long			gsleepstart;
	EntityPtr	 	gntePtr;
	ProcPtr			gioprocessQueue;
#if false	
	ProcPtr			gioprocessVBL;
	ProcPtr			gioimageDone;
	ProcPtr			gioreadUserRecord;
	ProcPtr			giosendUserRecord;
	ProcPtr			giocloseUserRecord;
	ProcPtr			gioopenImage;
	ProcPtr			gioreadImage;
	ProcPtr			giowriteImage;
	ProcPtr			giocloseImage;
#endif	
	SysEnvRec		gworld;
	oosDataRec		gosData[osMax];
	osDataRec		gosData					// root of linked list
	Boolean 		gDoneFlag;				// TRUE when File/Quit choosen
	TEHandle		gTextH;					// The TextEdit handle
	Boolean			gHaltFlag;				// true if halted, false otherwise
	Boolean			gWindFlag;				// true if showing, false otherwise
	char			gafname[200];
} Globals,*GlobalsPtr;

extern GlobalsPtr GetGPtr();			// returns ptr to above Globals


/*
	Global variables.
*/
#define		bufptr 				GetGPtr()->gbufptr
#define		intlevel 			GetGPtr()->gintlevel
#define		myHPB				GetGPtr()->gmyHPB
#define		myHPBptr			GetGPtr()->gmyHPBptr
#define		ddppbptr			GetGPtr()->gddppbptr
#define		namepbptr			GetGPtr()->gnamepbptr
#define		FreeLst				GetGPtr()->gFreeLst
#define		UserRecReq			GetGPtr()->gUserRecReq
#define		ImageReq			GetGPtr()->gImageReq
#define		UserUpdateReq		GetGPtr()->gUserUpdateReq
#define		errCode				GetGPtr()->gerrCode
#define		PBrec				GetGPtr()->gPBrec
#define		myddpWrite			GetGPtr()->gmyddpWrite
#define		myUserRecReply		GetGPtr()->gmyUserRecReply
#define		myImageReply		GetGPtr()->gmyImageReply
#define		myImageDone			GetGPtr()->gmyImageDone
#define		myUserUpdateReply	GetGPtr()->gmyUserUpdateReply
#define		mydestAddr 			GetGPtr()->gmydestAddr
#define		myheader 			GetGPtr()->gmyheader
#define		mywds				GetGPtr()->gmywds
#define		currentReqPtr 		GetGPtr()->gcurrentReqPtr
#define		ioprocessQueue 		GetGPtr()->gioprocessQueue
#define		ioprocessVBL 		GetGPtr()->gioprocessVBL
#define		ioimageDone			GetGPtr()->gioimageDone
#define		myNode 				GetGPtr()->gmyNode
#define		myNet 				GetGPtr()->gmyNet
#define		workLoad 			GetGPtr()->gworkLoad
#define		VBL 				GetGPtr()->gVBL
#define		sleepstart 			GetGPtr()->gsleepstart
#define		ntePtr				GetGPtr()->gntePtr
#define		ioreadUserRecord 	GetGPtr()->gioreadUserRecord
#define		iosendUserRecord 	GetGPtr()->giosendUserRecord
#define		iocloseUserRecord 	GetGPtr()->giocloseUserRecord
#define		world 				GetGPtr()->gworld
#define		ioopenImage 		GetGPtr()->gioopenImage
#define		ioreadImage			GetGPtr()->gioreadImage
#define		iowriteImage 		GetGPtr()->giowriteImage
#define		iocloseImage 		GetGPtr()->giocloseImage
#define		osData 				GetGPtr()->gosData
#define		DoneFlag 			GetGPtr()->gDoneFlag
#define		TextH 				GetGPtr()->gTextH
#define		HaltFlag 			GetGPtr()->gHaltFlag
#define		WindFlag 			GetGPtr()->gWindFlag
#define		afname 				GetGPtr()->gafname

