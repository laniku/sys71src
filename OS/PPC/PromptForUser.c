/*
	File:		PromptForUser.c

	Contains:	Utility routines for looking up the internationally correct '¥'
				symbol. Routines provided by Kevin MacDonell

	Written by:	Fred Monroe, Kevin MacDonell

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	  4/2/92	FM		#1020547 Utility routines for looking up the internationally
									correct '¥' symbol. Provided by Kevin MacDonell

*/

#include "Types.h"
#include "QuickDraw.h"
#include "Memory.h"
#include "Resources.h"
#include "Windows.h"
#include "ToolUtils.h"
#include "OSUtils.h"
#include "TextEdit.h"
#include "Fonts.h"
#include "Controls.h"
#include "Menus.h"
#include "Script.h"
#include "SysEqu.h"
#include "Script.h"
#include "Packages.h"

#include "PromptForUser.h"

// for pascal calling convetions
// Get the system scripts bullet characterÉ ( a.k.a. - tokenCenterDot)

pascal char GetPasswordBullet(void)
{
		char 	myMark;
		short 	sysFont = (*((short *) SysFontFam));
		
		myMark = GetIntlTokenChar(tokenCenterDot,Font2Script(sysFont), BulletMark);							// no checkmark available

		return (myMark);
}


// Get a character out of the itl4 given a script and tokenÉ

char GetIntlTokenChar(short whichToken, short whichScript, char defaultChar)
{
	Handle	itl4H;
	long	offset, len;

	// Look up the untoken table -- bail if we canÕt get it
	IUGetItlTable(whichScript, iuUnTokenTable, &itl4H, &offset, &len);
	if (itl4H && (offset > 0) && (len >= 0))
	{
		char *sp = (*itl4H + offset);				// Point to start of untoken table
		if (whichToken <= ((short *)sp)[1])			// Check if token has valid index
		{
			sp += ((short *)sp)[2+whichToken];		// Add the string offset and voli‡!
			if (*sp == 1) defaultChar = sp[1];		// Might be 2-byte, so check length byte
		}
	}
	return(defaultChar);
}