/*
	File:		NetBoot.h

	Contains:	xxx put contents here (or delete the whole line) xxx

	Written by:	xxx put name of writer here (or delete the whole line) xxx

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	  3/9/90	PWD		Added to bbs, changed equates for xo.
	   <1.1>	12/12/89	PWD		Added support for self-authenticating images
	   <1.0>	10/30/89	PWD		Adding to EASE

	To Do:
*/

/*EASE$$$ READ ONLY COPY of file “netBoot.h”
** 1.1	PWD 12/12/1989 Added support for self-authenticating images
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */
#ifndef	__APPLETALK__
#include	"AppleTalk.h"
#endif

#ifndef	__QUICKDRAW__
#include	"QuickDraw.h"
#endif


/* csCodes for the protocol boot driver */
#define	getBootBlocks	1		/* return boot blocks in ioBuffer */
#define	getSysVol		2		/* get a system volume & be ready to mount */
#define	mountSysVol		3		/* mount the volume (filesystem is initted) */
#define	goodBye			4		/* netBoot driver is going away */
#define	getDriverGlobals	5	/* return the driver globals... */

/* and some error codes to return from getBootBlocks control call */
/* these will be mapped by the netBoot driver into something reasonable */

#define		dTryAgain	-1		/* negative for non-fatal */
#define		dNoError	0		/* zero for no error */
#define		dNeverAgain	1		/* positive for fatal */

#define	NONFATAL	offLinErr	// the "something reasonable" from above
#define	FATAL		noDriveErr

/* error codes returned by the FINDNOPENDRIVER routine */

#define		dProtocolNotFound	-10		/* couldn't map the pram protocol id to a
											boot protocol driver */

/* csCodes for the management driver */
#define		ejectCode		7
#define		showIcon		6
#define		goodByeKiss		5
#define		getGlobals		4
#define		getPRAM			3
#define		setPRAM			2

/* some more interesting equates */
#define		CatBoot			40
#define		TypDRVR			2
#define		TypRemote		1
#define		DrSwATalk		1

/* boot protocol constants */
#define		MACHINE_MAC		1		/* mac machine id */

#define		DEFAULT_RETRANS		15		/* ticks between request retransmissions, default */
#define		DEFAULT_ROUNDTRIP	4		/* first guess for roundtrip for smoothing */
#define		DEFAULT_BACKOFF		1		/* first backoff exponent */

#define		DEFAULT_PRAM_TIMEOUT	2	/* timeout in seconds for server looking */
#define		TICKS_PER_SECOND		60	/* ticks per second */

/* pram constants */

// the osType byte (set via the start manager)
#define		MAC_OS			0x00	/* mac os from getosdefault */

// the preferred protocol byte
#define		BOOT_DEFAULT	0x00	/* boot using the default (currently appletalk) */
#define		BOOT_ATALK		0x01	/* boot using appletalk */
#define		BOOT_IP			0x02	/* boot using IP */

// the flags byte
#define		BOOT_ENABLE		0x80	/* bit for booting (0 = boot) */
#define		BOOT_RESERVED	0x70	/* reserved bits */
#define		BOOT_RETRIES	0x0F	/* number of seconds to skip net booting (0-15) */


typedef	struct	{
	unsigned char	nbpVars;		/* address of last server that we booted off of */
	unsigned char	timeout;		/* seconds to wait for bootserver response */
	unsigned int	signature[4];	/* image signature */
	char			userName[31];	/* an array of char, no length byte */
	char			password[8];	/* '' */
	short			serverNum;		/* the server number */
	} ATPRAMrec;

typedef	struct	{
	char	osType;			/* preferred os to boot from */
	char	protocol;		/* preferred protocol to boot from */
	char	errors;			/* last error in network booting */
	char	flags;			/* flags for: never net boot, boot first, etc. */
	union	{
		ATPRAMrec	atPRAM;	/* the AppleTalk PRAM definition */
		char	pad[68];	/* to reserve the space for other definitions */
		} u;
	} bootVars;

typedef	struct	{
	char	dProto,				// Protocol to look for
			dProtoSlot,			// slot that it is in (if slot based)
			dProtoID,			// ID (slot resource ID)
			dProtoDriveNum;		// drive queue entry number
	short	dProtoRefNum;		// refnum of the driver (0 if not opened)
	short	dLastError;			// last error returned
	int		*doldToExtFS;		// place to save external file system hook when
								// we patch in our routine to catch the mount
								/* and now the quickdraw globals... */
	struct  {
			char privates[76];
			long randSeed;
			BitMap screenBits;
			Cursor arrow;
			Pattern dkGray;
			Pattern ltGray;
			Pattern gray;
			Pattern black;
			Pattern white;
			GrafPtr thePort;
			}	dQDGlobals;
	
	GrafPort	*dMyPort;		/* and our port pointer... */
	
	} dGlobals;
	
extern void	pdbzero(char *c,int length);

typedef	struct	{
    QElem	*qLink;			/* queue link in header*/
    short	qType;			/* type byte for safety check*/
    short	ioTrap;			/* FS: the Trap*/
    Ptr		ioCmdAddr;		/* FS: address to dispatch to*/
    ProcPtr ioCompletion;	/* completion routine addr (0 for synch calls)*/
    OSErr	ioResult;		/* result code*/
    StringPtr ioNamePtr;	/* ptr to Vol:FileName string*/
    short	ioVRefNum;		/* volume refnum (DrvNum for Eject and MountVol)*/
    short	ioCRefNum;		/* refNum for I/O operation*/
    short	csCode;			/* word for control status code*/
	Ptr		returnVCB;		/* place to return pointer to generated VCB */
	Ptr		returnDrvQ;		/* place to return pointer to generated drive queue entry */
    short 	csParam[7];		/* pad */
} netBootPBRec, *netBootPBPtr;
