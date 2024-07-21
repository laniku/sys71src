/*
	MPWTypes.r -- Type Declarations for Rez and DeRez
	
	Copyright Apple Computer, Inc. 1986-1991
	All rights reserved.


	Change History (most recent first):

		 <3>	 6/24/92	DCL		Changed #ifndef __MPWTYPES.R__ to __MPWTYPES_R__  at the request
									of the MPW team (3.2.3 rez broke on the periods)
		 <2>	  8/8/91	JL		Updated Copyright.

	To Do:
*/

#ifndef __MPWTYPES_R__
#define __MPWTYPES_R__

/*
 * Macintosh Programmer's Workshop
 * DRVR resource type 'DRVR' (requires DRVRRuntime.o)
 */

# define mDownMask		   2		/* Event mask values for drvrEMask */
# define mUpMask		   4
# define keyDownMask	   8
# define keyUpMask		  16
# define autoKeyMask	  32
# define updateMask 	  64
# define diskMask		 128
# define activMask		 256
# define networkMask	1024
# define driverMask 	2048
# define everyEvent 	  -1

/*
 * When building a DRVR resource, insert the line:
 *
 *		type 'DRVR' as 'DRVW';
 *
 * in your resource file before your "resource 'DRVR' ..." declaration.
 */

type 'DRVW' {
	boolean = 0;							/* unused */
	boolean dontNeedLock,	 needLock;		/* lock drvr in memory	*/
	boolean dontNeedTime,	 needTime;		/* for periodic action	*/
	boolean dontNeedGoodbye, needGoodbye;	/* call before heap reinit*/
	boolean noStatusEnable,  statusEnable;	/* responds to status	*/
	boolean noCtlEnable,	 ctlEnable; 	/* responds to control	*/
	boolean noWriteEnable,	 writeEnable;	/* responds to write	*/
	boolean noReadEnable,	 readEnable;	/* responds to read 	*/

	byte = 0;					/* low byte of drvrFlags word unused */

	unsigned integer;			/* driver delay (ticks) */
	integer;					/* desk acc event mask	*/
	integer;					/* driver menu ID		*/

	unsigned integer = 50;		/* offset to DRVRRuntime open	*/
	unsigned integer = 54;		/* offset to DRVRRuntime prime	*/
	unsigned integer = 58;		/* offset to DRVRRuntime control*/
	unsigned integer = 62;		/* offset to DRVRRuntime status */
	unsigned integer = 66;		/* offset to DRVRRuntime close	*/

	pstring[31];				/* driver name */

	hex string; 				/* driver code (use $$resource(...)) */
};

#endif __MPWTYPES_R__
