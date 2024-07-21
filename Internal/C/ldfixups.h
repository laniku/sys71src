/*
	File:		ldfixups.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 6/22/92	ejb		first checked in
		 <1>	 6/12/92	APS		first checked in

*/

/* MAK NOTE:  This file must be used by the LINKER, COFFCVT, and the LOADER.  It would 	*/
/* be judicious to make sure that a copy of this is not changed without consistency	  	*/
/* checks for the other two programs.													*/
/* (IDEALLY, of course, only one file should exist.)									*/

/* ---------------------------------------------------------------------------
	LDFIXUPS.H
	This file contains all the #defines and declarations used to do loader
	fixups.  Loader Fixups occur when an address is involved in an
	auto-initialization, either through C pointers or anywhere else.
	Instead of fixing those instances up at link time (which produces
	the wrong results due to our sectionalized architecture), we send
	down the necessary information in the executable COFF to coffcvt and
	the loader, in which the resolution ultimately takes place.
	------------------------------------------------------------------------*/

#define MAXFILESIZE		50		/* number pulled from hat, change at whim */
#define PATH_SEPARATOR	':'		/* our path separator is a colon.			*/

/* These are just provided in case some bizzare cross-platform work 		*/
/* is done such that we need our freads, fwrites, etc. to be consistent.	*/
/* L_ stands for "loader stuff", these are the sizes used when writing  	*/
/* out to or reading from the loader relocation section.					*/

#define MAX_SYMSIZE 32			/* 31 chars plus 1 for the NULL */
#define L_INTSIZE 		4		/* sizeof an int on our system */
#define L_SHORTSIZE 	2		/* sizeof a short int on our system */
#define L_NODESIZE		10+MAX_SYMSIZE


/* don't change this struct without changing it's size define, above. */
struct relocation_node
{	unsigned long whatToPatch;		/* sectn & offset of guy who's getting initialized */
	unsigned long valToPatchWith;	/* sectn & offset of address going into whatToPatch*/
	unsigned short relocationType;	/* relocation type: will need when we do patch-up  */
	char symName[MAX_SYMSIZE];		/* valToPatchWith's symbol name; to a max size.	   */
};
	

/*
 * 	DSP3210 generics JUST THE ONES WE NEED
 *	SEE RELOC.H in the LINKER SOURCE FOR COMPLETE LIST
 */
 

#define	R_DSP_16D		044
#define	R_DSP_16SD		045

#define	R_DSP_24D		047
#define	R_DSP_24SD		051

#define	R_DSP_32D		054
#define	R_DSP_32SD		055
