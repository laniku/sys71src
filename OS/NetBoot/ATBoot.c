/**************************************************************************************************
	File:		ATBoot.c

	Contains:	xxx put contents here xxx

	Written by:	Pat Dyson

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	  3/9/90	PWD		Never write to pram, keep errors across boot attempts, retry
									server multiple times before switching to guest.
		 <5>	 2/20/90	PWD		Always allocate memory on the system heap.
		 <4>	  2/1/90	PWD		Always allocate memory on the system heap.
		 <3>	12/19/89	PD		Adding to bbs, fixed low memory, large image bug
	   <1.1>	12/12/89	PWD		Added support for self-authenticating images
	   <1.0>	10/30/89	PWD		Adding to EASE

	To Do:
**************************************************************************************************/

#include	<Types.h>
#include	<Errors.h>
#include	<Events.h>
#include	<Memory.h>
#include	<Devices.h>
#include	<Slots.h>
#include	<Start.h>
#include	<AppleTalk.h>
#include	"netBoot.h"
#include	"ATBootEqu.h"


/*	read/write pram utility. the selector chooses read/write, the pointer
	is to a buffer that the caller allocates.
*/
#define	PRAMwrite	0
#define	PRAMread	1
extern	void	TESTPRAM(Ptr	buf,short	selector);

short	rwPRAM(	char	*prec,
				short	selector)
{
	TESTPRAM((Ptr) prec,selector);
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

short	set_PRAM(	bootVars	*bv)
{
	(void) rwPRAM((Ptr)bv,PRAMwrite);

	return 0;
};

/* compare_signature
	Compares two signatures, basically just a binary compare, but 0's in the
	stored signature will match anything...

	Our stored signature is eight bytes; the generated signature is 16 bytes,
	we only compare the most significant eight bytes.
*/
short	compare_signature(	unsigned long int *generated_signature,
							unsigned long int *stored_signature,
							char 			  *image,
							unsigned long int  size) // prevent recursion
{	short		i;

		// check for zeroed stored signature
	i = 0;
	while ((i < STORED_SIZE/4) && (*(stored_signature+i) == STORED_WILDCARD))  i++;

	if (i >= STORED_SIZE/4) {	// wildcard match. We look at the end of the image for the
								// signature. This allows us to do "weak" auth.


		if (image != NULL) {
			return compare_signature( 	generated_signature,	// the image hash id
								(unsigned long int *)(image+size-16), // the place to look
								NULL,					// the image
								size);					// its size
			}
		else {	// this only happens if there is a wildcard match AND the
				// "end-of-image" signature is a wildcard also. We don't support
				// that.
			return SIGNATURE_BAD;
			};
								// Since we now have a valid signature we write it back to the
								// pram record so that it will get stored and be right the
								// next time.

		BlockMove((Ptr)generated_signature,(Ptr)stored_signature,STORED_SIZE);
		return 0;
		};

		// Not wildcard, check for exact match.
	i = 0;
	while ((i < STORED_SIZE/4) &&
		   (*(stored_signature+i) == *(generated_signature+i))) i++;

	if (i >= STORED_SIZE/4) return	0; // exact match

	return	SIGNATURE_BAD;		// no match
};

void	copy_userName(	char	*src,
						char	*dest)
{
	register char i=0;
	register char *s = src;

	while ((*src++ != (char)0) && (i++ < 31)) ;		// get the length
	if (i >= 31) i = 31;							// make sure we are within reason
	BlockMove(s,(dest+1),i);						// move that puppy
	*dest = i;
};

/*	get_the_image

	This procedure is called by the control dispatcher to handle the getBootBlocks
	control call from the netBoot driver.

	We need to pick up some machine information and PRAM stuff and call get_image
*/
// from GetServer.c
extern int	get_image(	int					lookup_timeout,	/* how long (ticks) to look for the server */
						unsigned short		server_ID,
				UserRecordRequest	*requestInfo,	/* to fill out req */
				unsigned char		nbpVars,				/* the last node number that we booted off of */
				Ptr					*buffer,		/* a place to return the image... */
				AddrBlock			*netServerAddr,	/* a place to return the server address */
				BootPktRply			*ur);			/* place to return the user record */

// from hash.c
extern short	generate_hash(	sBoxs			*sBoxs,		// unrotated substitution boxes
						rotatedsBox		**rotatedRightStandardSBoxes, // place for rotated ones
						unsigned int	*input,		// input buffer
						unsigned int	*output,	// output buffer
						unsigned int	size);		// size of input buffer

// from hash.a
extern	sBoxs	*GetsBoxBase();	// from hash.a

short	get_the_image(	DGlobals	*g)

{	UserRecordRequest	urr;	/* user and machine info */
	short				error;
	int					*val1,*val2;

	urr.machineID = g->pram->osType;					/* extend to a long machine id */
	copy_userName(g->pram->u.atPRAM.userName,urr.userName);	/* copy the users name */

	if (g->pram->u.atPRAM.timeout == 0) g->pram->u.atPRAM.timeout = DEFAULT_PRAM_TIMEOUT;

	error = get_image(	g->pram->u.atPRAM.timeout*TICKS_PER_SECOND,// how long to wait
						g->pram->u.atPRAM.serverNum,				// who the server is
						&urr,
						g->pram->u.atPRAM.nbpVars,	// timeouts for lookups
						(Ptr *)&(g->netimageBuffer),// place to put downloaded image
						&(g->netServerAddr),		// source bootserver address
						&(g->ur));					// user record to fill out

	if (error == 0) {	// generate signature and compare against pram value
						// the hash function will allocate a 32k pointer block
						// in the current heap. Be sure to set the heap to
						// where you want it allocated...
		rotatedsBox			*boxes;

		boxes = NULL;

		error = generate_hash(GetsBoxBase(),&boxes,
							(unsigned int *)(g->netimageBuffer), // input
							g->netImageSignature,	// output
							(unsigned int) GetPtrSize((Ptr)(g->netimageBuffer))-64);

			// the only error is an out-of-memory error, boxes will not be allocated...
		if (error) return error;

		DisposPtr((Ptr) boxes);

			// Compare to stored signature. If there is a wildcard match, the passed stored
			// signature buffer will be overwritten with the new value to be stored when
			// the server address is stored, below.
			//
			// The last 64 bytes are not hashed above as they are part of the self-authentication.
		error = compare_signature(	g->netImageSignature,
									g->pram->u.atPRAM.signature,
									g->netimageBuffer,
									(unsigned int) GetPtrSize((Ptr)(g->netimageBuffer)));

		if (error == 0) {
//			(void) set_PRAM(g->pram);									// write it out
			}
		else	{
			DisposPtr((Ptr)(g->netimageBuffer));				// dispos of the bad image
			g->netimageBuffer = NULL;
			return error;
			};
		// Now we have the downloaded image in memory, have checked it and saved the
		// server address, now we execute it. j_code is a short *(), defined in
		// ATBootEqu.h.
		if (g->netimageBuffer != NULL) error = ((j_code)(g->netimageBuffer))(getBootBlocks,g,&val1,&val2);
		else error = DS_ERROR;

		if (error) return error;
		};

	return error;
};
/*	DOATCONTROL (all caps for the linker)

	This procedure is called by the assembly glue in ATBoot.a to handle control
	calls to the driver. Currently these consist of

	getBootBlocks	:	do that magic shit.
	getSystem		:	preflight the boot process (pass on to downloaded code).
	Mount			:	actually vcbenqueue the sucker.
	goodBye			:	the netBoot driver is going away

	getDriverGlobals		:	return the driver globals

*/
extern short DOATCONTROL(	netBootPBRec	*pb,/* our pb */
							DGlobals		*g)	/* pointer to driver globals */
{
	int				*val1,*val2;			// possible return values from downloaded code
	register short	error = g->error;		// dereference for speed

	if (g->pram == NULL) 	// if we don't have the pram record...
		if ((error = get_PRAM(&(g->pram))) != 0) return error;

	switch (pb->csCode)	{

	case getBootBlocks	:	error = get_the_image(g);
							if (error == 0)							// we got no error, return the boot blocks
								BlockMove(	g->ur.userRec.bootBlocks,
											((ParmBlkPtr)pb)->ioParam.ioBuffer,
											((ParmBlkPtr)pb)->ioParam.ioReqCount);
							break;
	case getSysVol		:	if (g->netimageBuffer != NULL)	{
								error =
								((j_code)(g->netimageBuffer))(getSysVol,g,&val1,&val2);
								}
							else error = DS_ERROR;
							break;
	case mountSysVol	:	if (g->netimageBuffer != NULL)	{
								error =
								((j_code)(g->netimageBuffer))(mountSysVol,g,&val1,&val2);
								if (error == 0) {
									pb->returnVCB	= (Ptr) val1;		// pick up the returned parameters
									pb->returnDrvQ	= (Ptr) val2;
									};
								}
							else error = DS_ERROR;

							break;
	case goodBye		:	error = paramErr;
							break;
	case getDriverGlobals	: pb->returnVCB = (Ptr) g;
							break;
	default				:	error = paramErr;
							break;
	};
	
	if (((g->pram->flags & GUEST_BOOTING) == 0) &&				// if we support guest booting
		(g->pram->u.atPRAM.serverNum != 0)		&&				// and we are not already guest booting
		(error)								)					// and there was an error
		if (g->numAttempts++ >= MAX_LOOKUP_FAILURES) {
			val1 = (int *)g->pram->u.atPRAM.signature;
			*val1++ = STORED_WILDCARD;*val1 = STORED_WILDCARD;		// set image id to self-authenticate
			g->pram->u.atPRAM.serverNum = 0;						// and server id to guest boot
			g->pram->u.atPRAM.userName[0] = 0;						// and user name to do the same
			g->numAttempts = 0;										// and reset the number of attempts
			g->bigError = error;									// record the error for later analysis
			};

	return error;
};
