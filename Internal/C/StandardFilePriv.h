/*
	File:		StandardFilePriv.h

	Contains:	Definitions needed to use Standard File's LDEF or other resources

	Written by:	Nick Kledzik

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
		 <1>	 10/1/91	JSM		first checked in
		 <0>	 10/1/91	JSM		Created from StandardFile3Priv.h.

	Modification history from StandardFile3Priv.h below:

		 <4>	  8/8/90	ngk		update to match StandardFIle3Priv.a
		 <3>	  6/6/90	ngk		Moved generic icon IDs to IconUtilsPriv
		 <2>	 4/10/90	ngk		renumbered some resource IDs
		 <1>	 2/25/90	ngk		first checked in

*/



#ifndef __STANDARDFILEPRIV__
#define __STANDARDFILEPRIV__

#include <Quickdraw.h>

/* resource ID of Standard File's LDEF*/
#define	sfLDEFresourceID	 (-4000)


/* standard strings in STR# */
#define rStandardFileStringsID	(-6046)
#define sfDesktopName			1
#define sfTrashName				2
#define sfOpenName				3
#define sfErrDiskLocked		 	4
#define sfErrNoPrivileges		5
#define sfErrBadFilename		6
#define sfErrSystemError		7
#define sfErrBadAlias	 		8
#define sfErrSaveOnFolder		9
#define sfFolderNameExists		10
						
struct SFListCellData
{
	short[6] 		cdUserBytes;	/* ignored by LDEF, can be whatever you want */	
	short	 		cdIconID;		/* resource ID of SICN */
	Boolean 		cdIconLeft;		/* normally TRUE */
	char			cdJust;			/* normally teJustLeft */
	ScriptCode		cdScript;		
	short			cdFont;		
	Boolean			cdDimmed;		/* if true then dim cell */
	Style			cdStyle;		
	short			cdSize;		
	Str63			cdText;			/* can be any length pascal string */
};

#ifndef __cplusplus
typedef struct SFListCellData	SFListCellData;
#endif


#endif		/* __STANDARDFILEPRIV__ */
