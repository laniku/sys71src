/*
	File:		PromptForUser.h

	Contains:	Utility routines for looking up the internationally correct '¥'
				symbol. Routines provided by Kevin MacDonell

	Written by:	Fred Monroe, Kevin MacDonell

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	  4/2/92	FM		#1020547 make GetBullet use pascal calling conventions
		 <2>	  4/1/92	FM		Utility routines for looking up the internationally correct '¥'
									symbol. Provided by Kevin MacDonell

*/

//	low memory globals used
#define			SysFontFam			0x0BA6

//	characters
#define			BulletMark			0xA5

pascal char GetPasswordBullet(void);
char GetIntlTokenChar(short whichToken, short whichScript, char defaultChar);
