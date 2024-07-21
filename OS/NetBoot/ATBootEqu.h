/*
	File:		ATBootEqu.h

	Contains:	C equates for the atboot driver and protocol in general

	Written by:	Patrick Dyson

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <5>	  3/9/90	PWD		Added support for no guest boot, changed wildcard match string,
									grew driver globals to include number of failed attempts and the
									last big error.
		 <4>	 2/20/90	PWD		fixed equates for boot blocks, allow arbitrary sized user record
									replies that pass through to the downloaded code.
		 <3>	 1/25/90	PWD		fixed equates for boot blocks.
	   <1.1>	12/12/89	PWD		Added support for self-authenticating images
	   <1.0>	10/30/89	PWD		Adding to EASE

	To Do:
*/

/*EASE$$$ READ ONLY COPY of file “ATBootEqu.h”
** 1.1	PWD 12/12/1989 Added support for self-authenticating images
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */
#include	<BootDefines.h>
#define	BOOTDDPTYPE		10
#define	BOOTSOCKET		10
#define			userNameLength		34	/* bytes in a user name */

/* round-trip smoothing */
#define	SMOOTHING_FACTOR	4

/* image reception errors */
#define	IMAGE_TOO_BIG		-2		/* not enough memory to receive image */
#define	NOT_FOUND			-3		/* a valid server didn't respond in the timeout */
#define	TIMED_OUT			-4		/* image didn't make it in time */
#define	SIGNATURE_BAD		-5		/* image signature didn't match pram */
#define	DS_ERROR			-6		/* internal error (nil pointer somewhere) */

/* signature sizes */
#define	HASH_SIZE			16		/* output of hash routine in bytes */
#define	STORED_SIZE			8		/* our stored hash value */
#define	STORED_WILDCARD		'PWD '		/* matches anything... */
#define	GUEST_BOOTING		0x40	// no guest boot if 0
#define	CHECK_USER_RECORD	0x20	// XOR in hash of user record if 1

/* buffer sizes and maximum number of servers */
#define	INVALID_ADDR	-1L						/* node FF is invalid... */
#define	INVALID_IMAGE	0xFFFF					/* a bogus image id */
#define	MAX_SERVERS		2						/* how many nbp can look for... */
												/* space for name, addr, and nbp internal */
#define	MAX_NBP_BUFFER	MAX_SERVERS*(sizeof(EntityName)+9)
												/* space for iopb, wds, packetptr */
#define	MAX_LOOKUP_FAILURES		5				// NOT_FOUND errors tolerated

#define	IS_INVALID(a) ((a.aNet == 0xFFFF) && (a.aNode == 0xFF) && (a.aSocket == 0xFF))
#define	SET_INVALID(a) a.aNet = 0xFFFF; \
a.aNode = 0xFF; \
a.aSocket = 0xFF;

/*
 *	Errors returned by the server. 
*/
#define	ERROR_BASE		-6000
#define	SERVER_ERROR	(ERROR_BASE - 1)

/*
 *	Offsets within a received packet
*/

typedef	struct	{
	unsigned	char	packetType;		/* The command number */
	unsigned	char	packetVersion;	/* Protocol version number */
	unsigned	short	packetImage;	/* The image this block belongs to */
	unsigned	short	packetBlockNo;	/* The block of the image (starts with 1) */
	unsigned	char	packetData[512];/* the data portion of the packet */
	} BootBlock,*BootBlockPtr;

// This defines a user record.
// Some of these fields can be determined on the fly by the boot server,
// while others are stored on disk by the boot server
typedef struct
{
	char	serverName[serverNameLength];	// server name to boot off of 
	char	serverZone[zoneNameLength];		// and the zone it lives in
	char	serverVol[volNameLength];		// the volume name
	short	serverAuthMeth;					// authentication method to use (none, clear txt, rand)
	unsigned	long	sharedSysDirID;		// dir id of shared system folder
	unsigned	long	userDirID;			// dir id of the user's private system folder
	unsigned	long	finderInfo[8];		// blessed folder dir id, startup folder dir id etc...
	unsigned	char	bootBlocks[138];	// see Inside Mac V-135
	unsigned	short	bootFlag;			// server based flags
	unsigned	char	pad[306-18];		// <pd 5>pad to ddpMaxData
}userRecord;

// This defines the user record reply sent to workstations.
typedef struct
{
	unsigned	char		Command;	/* record or image request command word */
	unsigned	char		pversion;	/* version of boot protocol spoken by requestor */
	unsigned	short		osID;		/* type and version of os */
	unsigned	int			userData;	/* time stamp goes here */
	unsigned	short		blockSize;	/* size of blocks we will send */
	unsigned	short		imageID;	/* image ID */
	short					result;		/* error codes */
	unsigned	int			imageSize;	/* size of image in blocks */
	userRecord	userRec;	/* tell user where to go */
}BootPktRply;

typedef struct
{
	unsigned	short	imageID;	/* */
	unsigned	char	section;	/* "section" of the image the bitmap refers to */
	unsigned	char	flags;		/* ??? */
	unsigned	short	replyDelay;
	unsigned	char	bitmap[512];	/* bitmap of the section of the image requested */
}bir; // Boot Image Req


// This defines the structure of packets received from
// workstations.
typedef struct
{
	unsigned	char	Command;	/* record or image request command word */
	unsigned	char	pversion;	/* version of boot protocol spoken by requestor */
	unsigned	bir		bir;		/* on request type (record or image request) */
}requestBuf;

typedef	struct	{
	short		bogus;		/* this tuple timed out or returned error */
	int			time_sent;	/* tickcount when this server was sent a packet */
	AddrBlock	server_addr	/* where is this server? */
	} server_tuple;

typedef	struct	{
	unsigned	char	type;		/* packet type */
	unsigned	char	version;	/* protocol version */
	unsigned	short	machineID;	/* our machineID  */
	unsigned	int		timestamp;	/* when this was sent */
	char				userName[userNameLength]; 	/* key to finding their record */
	} UserRecordRequest;
	
typedef struct
{
	unsigned	char	Command;		/* type of request this is */
	unsigned	char	pversion;		/* version of this protocol */
	unsigned	short	imageID;		/*  ?  */
	unsigned	short	result;			/* error field */
}ImageDone;

typedef struct
{
	unsigned	short	osID;						/* type and version of os */
	unsigned	long	userData;					/* time stamp goes here */
	char				userName[userNameLength]; 	/* key to finding thier record */
	userRecord			userRec;					/* the user's "boot blocks" */
}uru; // user record update request

typedef	struct	{
	unsigned short	bootImageID;			/* set <> -1 if we know our image */
	unsigned short	machineID;				/* our machine ID */
	Ptr				bitmapBase;				/* ptr to receive bitmap */
	unsigned short	lastBlockNo;			/* number of blocks to receive */
	unsigned short	packetsReceived;		/* how many packets have we gotten */
	Ptr				imageBuffer;			/* ptr to image buffer */
	unsigned short	blockSize;				/* size of single blocks in bytes */
	int				trafficTimer;			/* Time when the last packet from our server for 
												our image arrived (ticks) */
	int				progressTimer;			/* Time that the last NEW block for our image arrived */
	int				retransThreshold;		/* Time between retransmissions (4*roundtrip) */
	short			roundTrip;				/* Time to base retransmissions on */
	short			backOff;				/* multiplier for retransmission */
	int				lastRetransmission;		/* time of last transmission */
	AddrBlock		server_addr;	/* set to our server address (<> -1) */
	server_tuple	*tuple_table;	/* the tuple table of server candidates */
	union	{
		UserRecordRequest	userRecord;
		BootPktRply			userReply;
		char				readPacketArea[586];	/* socket listener read area */
		} u ;
	} SocketListenerGlobals,*SktLsnGPtr;

typedef	struct	{
	MPPParamBlock	MPPpb;		/* a param block to queue this up with */
	WDSElement 		wds[3];		/* the write data structure that describes this */
	UserRecordRequest	record;	/* the data to send (packet to pass to DDP) */
	} RequestPacket;

typedef	struct	{
	MPPParamBlock	MPPpb;		/* a param block to queue this up with */
	WDSElement 		wds[3];		/* the write data structure that describes this */
	requestBuf	record;	/* the data to send (packet to pass to DDP) */
	} ImageRequestPacket;

typedef	struct	{
	char			myEntry[50];		/* what to look for */
	Ptr				nbpBuffer;		/* where to put it */
	short			errCode;		/* what happened */
	MPPParamBlock	myABRecord;		/* pb to ask with */
	} nbpLookupRecord;

typedef	struct	{
	short		netBootRefNum;		// refnum of the .netBoot driver (0 if not open) 
	short		error;				// last error recorded (from protocol or signature) 
	Ptr			netimageBuffer;		// place to put the downloaded image 
	unsigned	int		netImageSignature[4]; // the downloaded image signature (generated)
	AddrBlock	netServerAddr;		// source server address 
	BootPktRply	ur;					// the user record returned by the server 
	Ptr			StartGlobals;		// a place for the start code to store things
	bootVars	*pram;				// the pram record, read in
	short		numAttempts;		// number of failed attempts
	short		bigError;			// the error that makes us net boot
	} DGlobals;

typedef	struct	{
			char		privates[76];
			long 		randSeed;
			BitMap 		screenBits;
			Cursor 		arrow;
			Pattern 	dkGray;
			Pattern 	ltGray;
			Pattern 	gray;
			Pattern 	black;
			Pattern 	white;
			GrafPtr 	thePort;
			GrafPtr		globs;
			GrafPort	ourPort;		// place to stash our port when we open it
			short		curIcon;
			}	GrafWorld;

extern pascal OSErr ATPBOpen(ParamBlockRec *pb,Boolean aSync); 	/* from ATBootUtil.a */
typedef	short (*j_code)(	short		command,
							DGlobals	*g,
							int			**var1,
							int			**var2);

extern int 		myGetA5();					/* return A5 */
extern	void	mySetA5(int oldA5);			/* set A5 to the passed value */

extern	void	go_rom(Ptr p);
extern	void	do_erase();



#define hashSize 		4
#define maxSBoxCount 	8
#define errorFile  		2		/* normally set up for standard error */
#define	NUMTIMES		100
typedef unsigned long int 	sBox[256];
typedef	unsigned long int 	rotatedsBox[4][8][256];
typedef	unsigned long int	sBoxs[8][256];

