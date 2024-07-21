/*
	File:		PrintTraps.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	 2/18/92	MH		This file is now a stub, provided for backward compatibility
									with existing sources, which includes Printing.h. This file has
									provided access to the print manager via the trap _PrGlue, while
									Printing.h has supported access via glue routines in
									interfaces.o. That was only necessary to support execution on a
									Mac Plus or earlier running system 4.0 or earlier. It is no
									longer necessary to support that configuration in current
									internal or external product development. The file printing.h
									has been updated to use the _PrGlue trap inline.
		 <3>	 11/7/90	JL		Changed all #defines to anonymus enums

	To Do:
*/

/************************************************************

Created: Thursday, September 7, 1989 at 5:45 PM
	PrintTraps.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	1985-1989
	All rights reserved

************************************************************/

/* This file is provided to support existing references to it. The up to date interface is
   defined in Printing.h
*/

#ifndef __PRINTING__
#include <Printing.h>
#endif
