/*
	File:		NetBoot.c

	Contains:	The "guts" of the boot management driver.
				The actual driver is in assembly and is in NetBoot.a.

	Written by:	Patrick Dyson

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <5>	 11/9/90	dba		<JSM> change <NetBoot.h> to "NetBoot.h"
		 <4>	  3/9/90	PWD		For XO: Allocate all memory in the system         heap now to
									avoid crash when sys heap grows,         Inline open for
									pc-relative atboot driver,         open atboot if pram = 0
									(default protocol).
		 <3>	 2/20/90	PWD		For XO: Allocate all memory in the system heap now to avoid
									crash when sys heap grows, Inline open for pc-relative atboot
									driver, open atboot if pram = 0 (default protocol).
		 <2>	  2/1/90	PWD		Allocate all memory in the system heap now to avoid crash when
									sys heap grows
	   <1.1>	12/12/89	PWD		Added support for self-authenticating images
	   <1.0>	10/30/89	PWD		Adding to EASE
				  5/1/89			Implemented and minor testing done. Looking at flags stuff now.
				 4/12/89			New Today

	To Do:
*/

#include	<Types.h>
#include	<stdio.h>
#include	<ErrMgr.h>
#include	<Errors.h>
#include	<Slots.h>
#include	<ROMDefs.h>
#include	<Memory.h>
#include	<OSUtils.h>
#include	<Devices.h>
#include	<Start.h>
#include	<QuickDraw.h>
#include	<Traps.h>
#include	"NetBoot.h"

/*	read/write pram utility. the selector chooses read/write, the pointer
	is to a buffer that the caller allocates.
*/
#define	PRAMwrite	0
#define	PRAMread	1
void	TESTPRAM(Ptr	buf,short	selector);

short	rwPRAM(	char	*prec,
				short	selector)
{
	TESTPRAM((Ptr) prec,selector);
	return 0;
};
short	set_PRAM(	bootVars	*bv)
{
	(void) rwPRAM((char *)bv,PRAMwrite);

	return 0;
};

/*	This allocates and builds a bootVars record from our pram, other pram, and low mem.
	It will return any error encountered.
*/

short	get_PRAM(	bootVars	**bv)
{
	*bv = (bootVars *)NewPtrSysClear(sizeof(bootVars));
	if (*bv == NULL) return MemError();

			/* Get our pram record */
	(void) rwPRAM((Ptr)*bv,PRAMread);

	return 0;
};

/*	this finds the first boot record matching the passed protocol and returns
	the slot, ID and ExtID of said record. It also now fetches the driver name.

	This function is called if the protocol is not on the motherboard.

	The function result is 0 for success, an the non-zero slot manager error
	otherwise.
*/
short	find_BPTentry(	unsigned char	protocol,
						char	*slot,
						char	*ID,
						char	*ExtDev,
						char	*name)
{
#define	SftwrMask	1		/* the 1 bit (don't care about hardware) (IMV5, p.444) */

	short		err;
	SpBlock		pb;

	pdbzero((char *)&pb,sizeof(SpBlock));

	pb.spCategory	=	CatBoot;		/* only booters */
	pb.spCType		=	TypRemote;		/* only remote ones */
	pb.spDrvrSW		=	protocol;		/* only the protocol we care about */
	pb.spTBMask		=	SftwrMask;		/* don't care about  hardware */

	err = SNextTypeSRsrc(&pb);

#ifdef	DEBUG
	fprintf(stdout,"slot\tID\tExtDev\tres\trefNum\tcat\tType\n\n");
	fprintf(stdout,"%d\t%d\t%d\t%d\t%d\t%d\t%d\n",pb.spSlot,pb.spID,
			pb.spExtDev,pb.spIOReserved,pb.spRefNum,pb.spCategory,pb.spCType);
#endif

	if (err != 0) return err;

	pb.spResult = (Ptr)name;

	err = SReadDrvrName(&pb);
#ifdef DEBUG
	fprintf(stderr,"read returns: %d\n",err);
#endif

	*slot	= pb.spSlot;
	*ID		= pb.spID;
	*ExtDev	= pb.spExtDev;

	return err;
};

/*	This finds and opens the protocol boot driver for an associated protocol id.
	it calls functions in this module as well as assembly (BootUtils.a).

	The boot record can either reside in slot rom or our local table. If it is
	a rom based protocol we special case and just look there.

	If an error occurs during the initialization routines, we walk out
	cleanly - disposing and closing as necessary - and return the error.
*/
#define	driveSize	0x4000L		/* an arbitrary drive size */

pascal short AddMyDrive(int drvSize, short	drvrRef, Ptr storage);
short	DoATBootOpen(ParamBlockRec	*pb);

short	FINDNOPENDRIVER(dGlobals	*g)
{
	bootVars		*pramRec = NULL;	/* allocated by get_PRAM */
	short			error;
	unsigned char	slot,				/* the slot, ID and Ext ID of the boot protocol table entry */
			ID,
			ExtDev;
	ParamBlockRec	pb;
	char			name[34];			/* this will be a pstring of the driver name */

	/* read pram */
	(void) get_PRAM(&pramRec);

	if (pramRec->protocol == DrSwATalk) {	/* this is handled locally */

		pdbzero((char *)&pb,sizeof(ParamBlockRec));	/* zero that puppy */
		pb.ioParam.ioNamePtr	= "\p.ATBOOT";		/* a pname */
		pb.slotDevParam.ioRefNum = DoATBootOpen(&pb);
		}
	else	{ /* look in slot land */

		if (NGetTrapAddress(_SlotManager,OSTrap) != GetTrapAddress(_Unimplemented)) {

			/* find a boot protocol table entry matching PRAM */
			error = find_BPTentry(pramRec->protocol,&slot,&ID,&ExtDev,name);
			if (error != 0) goto error_exit;

			/* open the associated driver */
			pdbzero((char *)&pb,sizeof(SlotDevParam));	/* zero that puppy */

			pb.slotDevParam.ioSlot	= slot;
			pb.slotDevParam.ioID	= ID;
			pb.slotDevParam.ioNamePtr = (Ptr)name;		/* a pname */
			error = OpenSlot(&pb,0);					/* Open, IMMED */

			g->dProtoSlot		= slot;
			g->dProtoID			= ID;
			}
		else	{	// out of luck!
			error = dProtocolNotFound;
			goto error_exit;
			};
		};

	if ((error != 0) || (pb.slotDevParam.ioRefNum == 0)) {
		if (error == 0) error = openErr;
		goto error_exit;
		};

	/* return our hard work! */
	g->dProto			= pramRec->protocol;		/* set management driver globals */
	g->dProtoRefNum		= pb.slotDevParam.ioRefNum;

error_exit:
	if (pramRec != NULL) DisposPtr((Ptr)pramRec);

	return error;
};

/*	DOOPEN

	This is called by the open glue of the netboot driver. It needs to check to see
	if booting is enabled - if so we install ourselves in the drive queue.
*/
short	DOOPEN(short	driveRefNum, dGlobals	*g)
{	short		driveNum;
	char		flags;
	bootVars	*pramRec;	/* to be allocated by get_PRAM */

	if (get_PRAM(&pramRec) || (pramRec == NULL)) return openErr; /* get pram, punt if error */
	flags = pramRec->flags;
	DisposPtr((Ptr)pramRec);

	if ((flags & BOOT_ENABLE) == 0) return openErr;	/* if not configured, punt */

	/* install ourselves in the drive queue */
	driveNum = AddMyDrive(driveSize,driveRefNum, (Ptr) g);

	return 0;
};


/*	Find the first drive queue entry with the passed refnum and remove it.
	While we are at it, dispos of the entry.
*/

void	findNRemoveDrive(short	refNum)
{
	DrvQElPtr	dq ;
	QHdrPtr		QHead = 0x308;

	dq = (DrvQElPtr) (QHead->qHead);

	while ((dq != (DrvQElPtr)(QHead->qTail)) && (dq->dQRefNum != refNum))
		dq = (DrvQElPtr)(dq->qLink);

	if (dq->dQRefNum == refNum)	{
		Dequeue((QElemPtr)dq,QHead);
		DisposPtr((Ptr)dq);
		};
};

/*	DOCLOSE (all caps for the linker!) walks the globals, closing the boot protocol
	driver if open, removing any drive queue element that points to us (refNum), and
	disposing of our globals.

	We return any error as a function result - the assembly translates any error into
	a closErr. We ignore any close errors on the boot protocol driver.

	We will not be called if the driver storage is null.
*/

short	DOCLOSE(dGlobals	*g,short refnum)
{
	/* find & remove any drive queue entry pointing to us */
	findNRemoveDrive(refnum);

	/* close the boot protocol driver, if open */
	if (g->dProtoRefNum != 0) {
		ParamBlockRec	pb;
		short		error;

		pb.ioParam.ioCompletion	= NULL;
		pb.ioParam.ioRefNum		= g->dProtoRefNum;

		error = PBClose(&pb,0);
		};

	/* close and dispose of our grafport, if any */
	if (g->dMyPort != NULL)	{
		ClosePort(g->dMyPort);
		DisposPtr((Ptr)(g->dMyPort));
		g->dMyPort = (GrafPtr)0;
		};

	/* dispos of our globals */
	DisposPtr((Ptr) g);

	return 0;
};


/* This is the guts of the read call of the boot management driver. It is called
	on response to a read or write to the disk drive. The driver checks for null
	globals, then pushes our arguments and JSR's to us. Our responsibilities are:

		- check that this is the read that we think that it is
		- make sure that we have a protocol boot driver to call
		- call the protocol boot driver to get the boot blocks
		- map any error to #OffLinErr (non-fatal) or #NoDriveErr (fatal)
		- call boot protocol drive a second time for getSysVol
		- hook into extfs to trap mountvol call (next boot stage, past _InitFS)
*/
#define	aRdCmd	2		/* a read call */
#define	aWrCmd	3		/* a write call */

#define	ToExtFS		0x3F2L					// hook for external file systems

void myExtFSFilter();	// in netBoot.a

short	DOREAD(dGlobals	*g,ParamBlockRec	*pb)
{	short			error = 0;
	ParamBlockRec	callPb;

		/* if the low byte of the trap word is read, we are golden! */
	if ((pb->ioParam.ioTrap & 0x00FF) != aRdCmd)	return FATAL;

		/* this moved for sanity reasons... */
	error = FINDNOPENDRIVER(g);

	if (error) return FATAL;

	if ((callPb.ioParam.ioRefNum = g->dProtoRefNum) == 0) return FATAL;

		/* make the magic control call on the driver */
	callPb.cntrlParam.csCode	= getBootBlocks;

	callPb.ioParam.ioCompletion	= NULL;						/* pass through most params */
	callPb.ioParam.ioReqCount	= pb->ioParam.ioReqCount;
	callPb.ioParam.ioPosMode	= pb->ioParam.ioPosMode;
	callPb.ioParam.ioPosOffset	= pb->ioParam.ioPosOffset;
	callPb.ioParam.ioBuffer		= pb->ioParam.ioBuffer;
	callPb.ioParam.ioMisc		= pb->ioParam.ioMisc;

	error = PBControl(&callPb,0);	/* synch call */

	if (error == 0) { 					// if no error, go ahead and ask the boot
										// protocol driver to get the sys vol and
										// preflight the boot.
		netBootPBRec	getPB;

		getPB.csCode	= getSysVol;
		getPB.ioCRefNum	= g->dProtoRefNum;

		error = PBControl((ParmBlkPtr)&getPB,false);

			/* save the old toextfs hook (getBootBlocks may have changed it)	*/
		g->doldToExtFS = *((int **) ToExtFS);

			/* hook in our routine (assembly, in netBoot.a) */
			// This will be the next, and last, hook through the netboot driver. The
			// next call should be a close from somewhere.
		*((int **) ToExtFS) = (int *) myExtFSFilter;
		};


	if (error != 0) {
								/* save original error code */
		g->dLastError	= error;
								/* map error to something reasonable */
								/* negative errors will be non-fatal, positive fatal */
		error = (error > 0) ? FATAL : NONFATAL;
		};
	pb->ioParam.ioActCount	= callPb.ioParam.ioActCount;

	return error;
};
