/*
	File:		Hash.c

	Contains:	some killer hash, Man

	Written by:	Patrick Dyson

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM3>	12/10/92	chp		Cleaned up EASE to BBS change history conversion.
	   <SM2>	12/10/92	chp		Added an #include <stdlib.h> to supply a prototype for exit().
	   <1.1>	12/11/89	PWD		Changed hash size input to always strip the low bits of the size
									to avoid illegal input.
	   <1.0>	10/31/89	PWD		Adding to EASE

*/

#include	<Types.h>
#include <fcntl.h>
#include <stdio.h>
#include	<stdlib.h>
#include	<Errors.h>
#include <Memory.h>
#include <Quickdraw.h>
#include <Fonts.h>
#include <Events.h>


#define hashSize 		4
#define maxSBoxCount 	8
#define errorFile  		2		/* normally set up for standard error */
#define	NUMTIMES		100
typedef unsigned long int 	sBox[256];
typedef	unsigned long int 	rotatedsBox[4][8][256];
typedef	unsigned long int	sBoxs[8][256];


//extern sBox standardSBoxes[maxSBoxCount];

/* The following routine is a simple error exit routine  -- it prints a
   message and aborts */
void    errAbort (s)
	char   *s;
{
	int     length;

	for (length = 0; s[length] != 0; length++);
	write (errorFile, s, length);
	write (errorFile, "\n", 1);
	exit (1);
};

/*	Hash512

	Takes as parameters an output buffer, some input data, initial keys, and the
	base address of the pre-rotated s-block table.
	
	The output parameter is modified to include the signature of the block which
	should be hashed down when it too reaches 64 bytes.
	
	This routine is taken from Ralph Merkle's (Xerox Corp) reference implementation and has
	been slightly modified for speed and environment by Patrick Dyson.
*/

void    Hash512 (output, input, p0, p1, p2, rotatedRightBase)
unsigned long int output[];				/* keys to carry, or signature */
unsigned long int input[];				/* block of input data */
unsigned long int p0, p1, p2;			/* initial, or carried over, keys */
rotatedsBox 	rotatedRightBase;	/* pointer to base of s-box table */

{

	/* This routine is a specialized version of HashN.  It is optimized
	   for speed, and assumes that the parameter wordCount is always 16,
	   and that hashSize is always 4. It hashes 512 bits, hence its name.  */
	/* You need not try to figure out this routine unless you wish to
	   figure out a fast implementation of Snefru  */

	/* the following are two pointers to S-boxes  */
	unsigned long int *SBox0;
	unsigned long int *SBox1;


	/* the array 'block' is divided into 16 distinct variables */
	unsigned long int block0, block1, block2, block3;
	unsigned long int block4, block5, block6, block7;
	unsigned long int block8, block9, block10, block11;
	unsigned long int block12, block13, block14, block15;
#ifdef DEBUG
	short	i;
#endif

	unsigned long int SBoxEntry;	/* just a temporary */

#ifdef DEBUG
	if (wordCount != 16)
		errAbort ("Hash512 called with wordCount != 16");
	if (hashSize != 4)
		errAbort ("Hash512 called with hashSize != 4");
#endif

	/* initialize the block to be encrypted from the input  */
	/* Note that in theory block<i> should be kept in register.  Not all
	   compilers can do this, even when there are enough registers --
	   this will degrade performance significantly.  */
	block0 = input[0];
	block1 = input[1];
	block2 = input[2];
	block3 = input[3];
	block4 = input[4];
	block5 = input[5];
	block6 = input[6];
	block7 = input[7];
	block8 = input[8];
	block9 = input[9];
	block10 = input[10];
	block11 = input[11];
	block12 = input[12];
	block13 = input[13];
	block14 = input[14];
	block15 = input[15];


#ifdef	DEBUG
	for (index = 0; index < 2 * localSecurityLevel; index += 2) {
#endif

		/* Mix in the parameter that parameterizes this instance of
		   the hash function */
		block0 ^= p0;
		block1 ^= p1;
		block2 ^= p2;

		/* set up the base address for the two S-box pointers.  */
		SBox0 = rotatedRightBase[0][0];
		SBox1 = SBox0 + 256;


		/* In the following unrolled code, the basic 'assembly
		   language' block that is repeated is:
		
		1    temp1 = shift(block<i>, shiftConstant) 2    temp2 =
		   temp1 & 0x3fc 3    temp3 = SBox<0 or 1> + temp2 4    temp4
		   = *temp3 5    block<i-1> ^= temp4 6    block<i+1> ^= temp4
		
		In step 1, we simply shift the ith 32-bit block to bring the
		   8-bit byte into the right position.  Note that we will
		   also build-in a left-shift by 2 bits at this stage, to
		   eliminate the left shift required later because we are
		   indexing into an array of 4-byte table entries.
		
		In step 2, we mask off the desired 8 bits.  Note that 0x3fc
		   is simply 0xff << 2.
		
		In step 3, we use a normal integer add to compute the actual
		   address of the S-box entry.  Note that one of two pointers
		   is used, as appropriate.  Temp3 then holds the actual byte
		   address of the desired S-box entry.
		
		In step 4, we load the 4-byte S-box entry.
		
		In steps 5 and 6, we XOR the loaded S-box entry with both the
		   previous and the next 32-bit entries in the 'block' array.
		
		Typical optimizing comilers might fail to put all the
		   block<i> variables into registers. This can result in
		   significant performance degradation. Also, most compilers
		   will use a separate left-shift-by-2 after masking off the
		   needed 8 bits, but the performance degradation caused by
		   this oversight should be modest.
		
		*/

		SBoxEntry = SBox0[block0 & 0xff];
		block1 ^= SBoxEntry;
		block15 ^= SBoxEntry;
		SBoxEntry = SBox0[block1 & 0xff];
		block2 ^= SBoxEntry;
		block0 ^= SBoxEntry;
		SBoxEntry = SBox1[block2 & 0xff];
		block3 ^= SBoxEntry;
		block1 ^= SBoxEntry;
		SBoxEntry = SBox1[block3 & 0xff];
		block4 ^= SBoxEntry;
		block2 ^= SBoxEntry;
		SBoxEntry = SBox0[block4 & 0xff];
		block5 ^= SBoxEntry;
		block3 ^= SBoxEntry;
		SBoxEntry = SBox0[block5 & 0xff];
		block6 ^= SBoxEntry;
		block4 ^= SBoxEntry;
		SBoxEntry = SBox1[block6 & 0xff];
		block7 ^= SBoxEntry;
		block5 ^= SBoxEntry;
		SBoxEntry = SBox1[block7 & 0xff];
		block8 ^= SBoxEntry;
		block6 ^= SBoxEntry;
		SBoxEntry = SBox0[block8 & 0xff];
		block9 ^= SBoxEntry;
		block7 ^= SBoxEntry;
		SBoxEntry = SBox0[block9 & 0xff];
		block10 ^= SBoxEntry;
		block8 ^= SBoxEntry;
		SBoxEntry = SBox1[block10 & 0xff];
		block11 ^= SBoxEntry;
		block9 ^= SBoxEntry;
		SBoxEntry = SBox1[block11 & 0xff];
		block12 ^= SBoxEntry;
		block10 ^= SBoxEntry;
		SBoxEntry = SBox0[block12 & 0xff];
		block13 ^= SBoxEntry;
		block11 ^= SBoxEntry;
		SBoxEntry = SBox0[block13 & 0xff];
		block14 ^= SBoxEntry;
		block12 ^= SBoxEntry;
		SBoxEntry = SBox1[block14 & 0xff];
		block15 ^= SBoxEntry;
		block13 ^= SBoxEntry;
		SBoxEntry = SBox1[block15 & 0xff];
		block0 ^= SBoxEntry;
		block14 ^= SBoxEntry;

		/* SBox0 = rotatedRightStandardSBoxes[2][index];  */
		SBox0 += 2 * maxSBoxCount * 256;
		SBox1 = SBox0 + 256;

		SBoxEntry = SBox0[(block0 >> 16) & 0xff];
		block1 ^= SBoxEntry;
		block15 ^= SBoxEntry;
		SBoxEntry = SBox0[(block1 >> 16) & 0xff];
		block2 ^= SBoxEntry;
		block0 ^= SBoxEntry;
		SBoxEntry = SBox1[(block2 >> 16) & 0xff];
		block3 ^= SBoxEntry;
		block1 ^= SBoxEntry;
		SBoxEntry = SBox1[(block3 >> 16) & 0xff];
		block4 ^= SBoxEntry;
		block2 ^= SBoxEntry;
		SBoxEntry = SBox0[(block4 >> 16) & 0xff];
		block5 ^= SBoxEntry;
		block3 ^= SBoxEntry;
		SBoxEntry = SBox0[(block5 >> 16) & 0xff];
		block6 ^= SBoxEntry;
		block4 ^= SBoxEntry;
		SBoxEntry = SBox1[(block6 >> 16) & 0xff];
		block7 ^= SBoxEntry;
		block5 ^= SBoxEntry;
		SBoxEntry = SBox1[(block7 >> 16) & 0xff];
		block8 ^= SBoxEntry;
		block6 ^= SBoxEntry;
		SBoxEntry = SBox0[(block8 >> 16) & 0xff];
		block9 ^= SBoxEntry;
		block7 ^= SBoxEntry;
		SBoxEntry = SBox0[(block9 >> 16) & 0xff];
		block10 ^= SBoxEntry;
		block8 ^= SBoxEntry;
		SBoxEntry = SBox1[(block10 >> 16) & 0xff];
		block11 ^= SBoxEntry;
		block9 ^= SBoxEntry;
		SBoxEntry = SBox1[(block11 >> 16) & 0xff];
		block12 ^= SBoxEntry;
		block10 ^= SBoxEntry;
		SBoxEntry = SBox0[(block12 >> 16) & 0xff];
		block13 ^= SBoxEntry;
		block11 ^= SBoxEntry;
		SBoxEntry = SBox0[(block13 >> 16) & 0xff];
		block14 ^= SBoxEntry;
		block12 ^= SBoxEntry;
		SBoxEntry = SBox1[(block14 >> 16) & 0xff];
		block15 ^= SBoxEntry;
		block13 ^= SBoxEntry;
		SBoxEntry = SBox1[(block15 >> 16) & 0xff];
		block0 ^= SBoxEntry;
		block14 ^= SBoxEntry;


		/* SBox0 = rotatedRightStandardSBoxes[1][index];  */
		SBox0 -= maxSBoxCount * 256;
		SBox1 = SBox0 + 256;

		SBoxEntry = SBox0[block0 >> 24];
		block1 ^= SBoxEntry;
		block15 ^= SBoxEntry;
		SBoxEntry = SBox0[block1 >> 24];
		block2 ^= SBoxEntry;
		block0 ^= SBoxEntry;
		SBoxEntry = SBox1[block2 >> 24];
		block3 ^= SBoxEntry;
		block1 ^= SBoxEntry;
		SBoxEntry = SBox1[block3 >> 24];
		block4 ^= SBoxEntry;
		block2 ^= SBoxEntry;
		SBoxEntry = SBox0[block4 >> 24];
		block5 ^= SBoxEntry;
		block3 ^= SBoxEntry;
		SBoxEntry = SBox0[block5 >> 24];
		block6 ^= SBoxEntry;
		block4 ^= SBoxEntry;
		SBoxEntry = SBox1[block6 >> 24];
		block7 ^= SBoxEntry;
		block5 ^= SBoxEntry;
		SBoxEntry = SBox1[block7 >> 24];
		block8 ^= SBoxEntry;
		block6 ^= SBoxEntry;
		SBoxEntry = SBox0[block8 >> 24];
		block9 ^= SBoxEntry;
		block7 ^= SBoxEntry;
		SBoxEntry = SBox0[block9 >> 24];
		block10 ^= SBoxEntry;
		block8 ^= SBoxEntry;
		SBoxEntry = SBox1[block10 >> 24];
		block11 ^= SBoxEntry;
		block9 ^= SBoxEntry;
		SBoxEntry = SBox1[block11 >> 24];
		block12 ^= SBoxEntry;
		block10 ^= SBoxEntry;
		SBoxEntry = SBox0[block12 >> 24];
		block13 ^= SBoxEntry;
		block11 ^= SBoxEntry;
		SBoxEntry = SBox0[block13 >> 24];
		block14 ^= SBoxEntry;
		block12 ^= SBoxEntry;
		SBoxEntry = SBox1[block14 >> 24];
		block15 ^= SBoxEntry;
		block13 ^= SBoxEntry;
		SBoxEntry = SBox1[block15 >> 24];
		block0 ^= SBoxEntry;
		block14 ^= SBoxEntry;


		/* SBox0 = rotatedRightStandardSBoxes[3][index];  */
		SBox0 += 2 * maxSBoxCount * 256;
		SBox1 = SBox0 + 256;

		SBoxEntry = SBox0[(block0 >> 8) & 0xff];
		block1 ^= SBoxEntry;
		block15 ^= SBoxEntry;
		SBoxEntry = SBox0[(block1 >> 8) & 0xff];
		block2 ^= SBoxEntry;
		block0 ^= SBoxEntry;
		SBoxEntry = SBox1[(block2 >> 8) & 0xff];
		block3 ^= SBoxEntry;
		block1 ^= SBoxEntry;
		SBoxEntry = SBox1[(block3 >> 8) & 0xff];
		block4 ^= SBoxEntry;
		block2 ^= SBoxEntry;
		SBoxEntry = SBox0[(block4 >> 8) & 0xff];
		block5 ^= SBoxEntry;
		block3 ^= SBoxEntry;
		SBoxEntry = SBox0[(block5 >> 8) & 0xff];
		block6 ^= SBoxEntry;
		block4 ^= SBoxEntry;
		SBoxEntry = SBox1[(block6 >> 8) & 0xff];
		block7 ^= SBoxEntry;
		block5 ^= SBoxEntry;
		SBoxEntry = SBox1[(block7 >> 8) & 0xff];
		block8 ^= SBoxEntry;
		block6 ^= SBoxEntry;
		SBoxEntry = SBox0[(block8 >> 8) & 0xff];
		block9 ^= SBoxEntry;
		block7 ^= SBoxEntry;
		SBoxEntry = SBox0[(block9 >> 8) & 0xff];
		block10 ^= SBoxEntry;
		block8 ^= SBoxEntry;
		SBoxEntry = SBox1[(block10 >> 8) & 0xff];
		block11 ^= SBoxEntry;
		block9 ^= SBoxEntry;
		SBoxEntry = SBox1[(block11 >> 8) & 0xff];
		block12 ^= SBoxEntry;
		block10 ^= SBoxEntry;
		SBoxEntry = SBox0[(block12 >> 8) & 0xff];
		block13 ^= SBoxEntry;
		block11 ^= SBoxEntry;
		SBoxEntry = SBox0[(block13 >> 8) & 0xff];
		block14 ^= SBoxEntry;
		block12 ^= SBoxEntry;
		SBoxEntry = SBox1[(block14 >> 8) & 0xff];
		block15 ^= SBoxEntry;
		block13 ^= SBoxEntry;
		SBoxEntry = SBox1[(block15 >> 8) & 0xff];
		block0 ^= SBoxEntry;
		block14 ^= SBoxEntry;


#ifdef DEBUG
	};			/* end of index going from 0 to
				   2*localSecurityLevel-2 in steps of 2 */
#endif

/*  XOR the parameter with the next-to-the-last three words of the block */
    block14 ^= p0;
    block13 ^= p1;
    block12 ^= p2;

	output[0] = input[0] ^ block15;
	output[1] = input[1] ^ block14;
	output[2] = input[2] ^ block13;
	output[3] = input[3] ^ block12;


};


int	do_hash(rotatedsBox	rotatedRightStandardSBoxes)

{

	int	i;
	unsigned long int	hasharray[16];
	unsigned long int	p0=0,p1=1,p2=2;
	int	starttime;
	

	starttime = TickCount();
	
	for (i=0;i<NUMTIMES;i++) {
		Hash512(hasharray,hasharray,p0,p1,p2,rotatedRightStandardSBoxes);
		};
	
	fprintf(stderr,"%d iterations took%d\n",NUMTIMES,TickCount()-starttime);
	
	starttime = TickCount();
	
	for (i=0;i<NUMTIMES;i++) ;
	
	fprintf(stderr,"%d iterations of a blank loop took %d\n",
			NUMTIMES,TickCount()-starttime);
	return 0;
};

extern	sBoxs	*GetsBoxBase();	// from hash.a

/*	generate_boxes
	Takes a pointer to the unrotated sBoxs, allocates and generates a pre-rotated
	substitution box for the Hash512 routine.
*/
short	generate_boxes(	sBoxs			*thesBoxBase,		/* unrotated substitution boxes */
						rotatedsBox		**rotatedRightStandardSBoxes) /* target boxes */
{	
	*rotatedRightStandardSBoxes = (rotatedsBox *) NewPtr(sizeof(sBox)*hashSize*maxSBoxCount);
	if (*rotatedRightStandardSBoxes == NULL) return MemError();
	
	{
		int     index;	/* ranges over the S box indices  */
		register unsigned long int	*sBoxEntry;
		register unsigned long int *SBox0;
		register short i;
		register char leftshift,rightshift;

	for (index = 0; index < maxSBoxCount; index++)	{
	
		sBoxEntry	= (*thesBoxBase)[index];
		SBox0		= (**rotatedRightStandardSBoxes)[0][index];
			for (i = 0; i < 256; i++)		/* rotation = 0 */
				*SBox0++ = *sBoxEntry++;
				
		sBoxEntry	= (*thesBoxBase)[index];
		SBox0 		= (**rotatedRightStandardSBoxes)[1][index];
		leftshift	= 24;
		rightshift	= 8;
			for (i = 0; i < 256; i++)		/* rotation = 1 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
				
		sBoxEntry	= (*thesBoxBase)[index];
		SBox0 		= (**rotatedRightStandardSBoxes)[2][index];
		leftshift	= rightshift = 16;
			for (i = 0; i < 256; i++)		/* rotation = 2 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
				
		sBoxEntry	= (*thesBoxBase)[index];
		SBox0 		= (**rotatedRightStandardSBoxes)[3][index];
		leftshift	= 8;
		rightshift	= 24;
			for (i = 0; i < 256; i++)		/* rotation = 3 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
		};

	};
	return 0;
};

/*	generate_hash
	Takes an arbitrary (assumed multiple of 64 bytes) buffer (input) and initial keys
	(p0,p1,p2) and generates a signature (output). The signature is 128 bits long. The
	rotated s-boxs will be created if passed in as NULL, assumed generated already otherwise.
	The input buffer is assumed (size) bytes.
	
	The output buffer is used in repeated calls to Hash512 and therefore has an undefined
	value during the call, becoming defined only on exit.
	
	The basis of the hash function is to take 64 byte inputs and generate 16 byte outputs.
	the outputs are accumulated 4 times, then hashed into the lower 16 bytes. This means
	that the Hash512 function is called size/64 + size/(256-64) - 1 times. The size/64
	is the number of calls for the image, the size/(256-64) is to hash down the 64 byte
	output into the lower sixteen bytes, using the upper 192 bytes as output buffers
	for the ongoing hash, the - 1 because you get to use the first 16 bytes of the 
	output buffer once.
	
	This procedure allocates memory for the rotated sboxes with a newptr call from the
	current heap. It will never dispose of memory, but will return an error if it
	runs out of memory.
*/
short	generate_hash(	sBoxs			*sBoxs,		// unrotated substitution boxes
						rotatedsBox		**rotatedRightStandardSBoxes, // place for rotated ones
						unsigned int	*input,		// input buffer
						unsigned int	*output,	// output buffer
						unsigned int	size)		// size of input buffer
{	short 			error;				// returned by generate_boxes
	unsigned int 	temp_output[16];	// temporary holder of the unhashed output
	register int	datasize = size, output_loc;

	register unsigned int	p0 = 0,	/* initial keys */
							p1 = 0,
							p2 = size*8; // varies directly as the number of input bits
							
	size = size & 0xFFFFFC0;				// make sure we are multiple of 64 bytes
	
	if (*rotatedRightStandardSBoxes == NULL) 
		if(error = generate_boxes(sBoxs,rotatedRightStandardSBoxes)) return error;
	
	// initialize our temporary output buffer
	for (output_loc = 0;output_loc < 16;output_loc++) temp_output[output_loc] = 0;
	output_loc = 0;

	do	{
		Hash512(&temp_output[output_loc],input,p0,p1,p2,*rotatedRightStandardSBoxes); // generate hash
		p2 		+= 1;
		size 	-= 64;		// decrement by (512/8) bits
		input 	+= 16;		// bump by 64 bytes
		output_loc	+= 4;	// bump the output buffer pointer
		
		if (output_loc >= 16) {	// the output buffer is full, hash it down 
		
			Hash512(temp_output,temp_output,p0,p1,p2,*rotatedRightStandardSBoxes);
			output_loc	= 4;		// point at the first unused block
			p2			+= 1;
			};
		} while (size > 0);
	
	// final hash down into the passed output buffer
	
	Hash512(output,temp_output,p0,p1,p2,*rotatedRightStandardSBoxes);
	
	return 0;	// no errors after generate_boxes
};
						
						
main(){
	int	rotatetime = TickCount();
	int	numrotates = NUMTIMES / 100;
	rotatedsBox		*rotatedRightStandardSBoxes
					= NewPtr(sizeof(sBox)*hashSize*maxSBoxCount);
	rotatedsBox		*checkrotatedRightStandardSBoxes
					= NewPtr(sizeof(sBox)*hashSize*maxSBoxCount);
	sBoxs			*sBoxBase;
	rotatedsBox		*theFastsBox;
	unsigned int	input[16],output[4],p0=0,p1=0,p2=0,k;
	short			error;

	for (k=0;k<16;k++) input[k] = 0;	// init the input & output buffers
	for (k=0;k<4;k++)  output[k]= 0;
	
	sBoxBase	= GetsBoxBase();
	theFastsBox	= NULL;
//
// try the pup here!!
//
// prime it.. make the memory manager give us the block and build the rotated boxes
	rotatetime = TickCount();
	error =	generate_hash(	sBoxBase,
						&theFastsBox,
						input,
						output,
						1024*1024);
	if (error == NULL) DisposPtr((Ptr)theFastsBox);
	rotatetime = TickCount()-rotatetime;
	fprintf(stderr,"hash of 1 meg took %d ticks, %d seconds\n "
					,rotatetime,rotatetime/60);
		
	fprintf(stderr,"we got... %d for error,\n %X\t%X\t%X\t%X\t\n",
					error,output[0],output[1],output[2],output[3]);

#ifdef SPEED_TESTS
	if ((rotatedRightStandardSBoxes == NULL) || (checkrotatedRightStandardSBoxes == NULL))
		DebugStr("\p whoops, out of memory");
	while (numrotates--)
		/* Set up the rotated array for the fast hash routine  */
	{
		int     index;	/* ranges over the S box indices  */
		register unsigned long int	*sBoxEntry;
		register unsigned long int *SBox0;
		register short i;
		register char leftshift,rightshift;

	for (index = 0; index < maxSBoxCount; index++)	{
	
		sBoxEntry	= (*sBoxBase)[index];
		SBox0		= (*rotatedRightStandardSBoxes)[0][index];
			for (i = 0; i < 256; i++)		/* rotation = 0 */
				*SBox0++ = *sBoxEntry++;
				
		sBoxEntry	= (*sBoxBase)[index];
		SBox0 		= (*rotatedRightStandardSBoxes)[1][index];
		leftshift	= 24;
		rightshift	= 8;
			for (i = 0; i < 256; i++)		/* rotation = 1 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
				
		sBoxEntry	= (*sBoxBase)[index];
		SBox0 		= (*rotatedRightStandardSBoxes)[2][index];
		leftshift	= rightshift = 16;
			for (i = 0; i < 256; i++)		/* rotation = 2 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
				
		sBoxEntry	= (*sBoxBase)[index];
		SBox0 		= (*rotatedRightStandardSBoxes)[3][index];
		leftshift	= 8;
		rightshift	= 24;
			for (i = 0; i < 256; i++)		/* rotation = 3 */
				*SBox0++ = ((*sBoxEntry >> rightshift) | (*sBoxEntry++ << leftshift));
		};

	};
	
	fprintf(stderr,"The initial rotation  took %d\n",
				TickCount()-rotatetime);

//
//	Set up the reference version of the same thing
//
	/* Set up the rotated array for the fast hash routine  */
	{
		int     index;	/* ranges over the S box indices  */
		int     rotation;	/* ranges over the four possible
					   byte-rotations  */
		int     i;	/* ranges over the 256 possible S-box entries    */
		int		lineno = 0;

		for (index = 0; index < maxSBoxCount; index++)
			for (rotation = 0; rotation < 4; rotation++)
				for (i = 0; i < 256; i++)
					(*checkrotatedRightStandardSBoxes)[rotation][index][i] =
						((*sBoxBase)[index][i] >> (rotation * 8)) |
						((*sBoxBase)[index][i] << (32 - rotation * 8));

//
//	Now check if our version worked...
//
			for (index = 0; index < maxSBoxCount; index++)
			for (rotation = 0; rotation < 4; rotation++)
				for (i = 0; i < 256; i++)	{
#ifdef DUMPSBOXES
					fprintf(stdout,"%d)\t%X\n",
							++lineno,
							(*rotatedRightStandardSBoxes)[rotation][index][i]);
#else
					if ((*checkrotatedRightStandardSBoxes)[rotation][index][i] !=
						(*rotatedRightStandardSBoxes)[rotation][index][i]) DebugStr("\pCheck failed");
#endif
					};

	};

//	do_hash(*rotatedRightStandardSBoxes);
	/* Now try hashing something.  Note that we're testing both HashN and
	   Hash512 here  */
	{
		unsigned long int testInput[16];
		unsigned long int testOutput[hashSize];
		unsigned long int testP;
		int     j,i;

		for (i = 0; i < 16; i++)
			testInput[i] = 0;	/* zero the input */
		for (i = 0; i < 50; i++) {
		    testP = i;
			Hash512(testOutput, testInput, testP, testP, testP, *rotatedRightStandardSBoxes);
			for (j = 0; j < hashSize; j++)
				testInput[j] = testOutput[j];
		};
		if ((testOutput[0] != 3322084822) || (testOutput[1] != 2015524574) ||
		    (testOutput[2] != 2594724576) || (testOutput[3] != 532340662)
			)
			errAbort ("Test hash of 64 bytes of 0 failed");
	};

#endif
	DisposPtr((Ptr)rotatedRightStandardSBoxes);
	DisposPtr((Ptr)checkrotatedRightStandardSBoxes);
};
