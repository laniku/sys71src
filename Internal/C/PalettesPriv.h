/*
	File:		PalettesPriv.h

	Contains:	PaletteMgr private field names

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	12/13/90	dvb		Make .h and .p and .a files consistent.
		 <2>	 3/30/90	EMT		fixed a few syntax errors.
		 <1>	 3/29/90	DVB		first checked in

	To Do:
*/

/* Make these field names seem to exist, based on the definitions in Palettes.h */
#define pmPrivate pmDataFields[2]

/* Masks for pmPrivate */
#define CForeMask	0x8000
#define CBackMask	0x4000

/* Internal routines that just might be of interest */
pascal PaletteHandle WhatPal(WindowPtr window) = {0x303C,0x0405,0xAAA2};
pascal Boolean CheckColors(GDHandle , CTabHandle, short, short) = {0x303C,0x1218,0xAAA2};
