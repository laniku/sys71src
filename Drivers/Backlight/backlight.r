/*
	File:		backlight.r

	Contains:	resource header for backlight driver

	Written by:	Andy Gong

	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):


	*** Rolled into 7.0

		 <2>	 1/24/91	ag		changed to pass in directory.
		 <1>	 1/24/91	ag		first checked in

	To Do:
*/

/*
 *	Define header for driver resource
 *
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

type 'DRVR' as 'DRVW';			/* Map 'DRVW' => 'DRVR' */

/*
 *	Header for backlight driver
 *
 */
resource 'DRVR' (-16511, ".Backlight", sysheap) {
	needLock,				
	dontNeedTime,			
	dontNeedGoodbye,
	statusEnable,
	ctlEnable,				/* Desk accessories only do Control calls */
	noWriteEnable,
	noReadEnable,
	0,						/* drvrDelay - Wake up 60 ticks */
	0, 						/* drvrEMask */
	0,						/* drvrMenu */
	".Backlight",			/* drvrName */
	/*
	 * This directive inserts the contents of the DRVW resource
	 * produced by linking DRVRRuntime.o with our DA code
	 */
	$$resource(Obj, 'DRVW', -16511)
};
