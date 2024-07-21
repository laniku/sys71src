/************************************************************
	TerminalTools.h
	C Interface to the CommToolBox terminal tools

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
		
    This file is used in these builds: ROM System

	Change History (most recent first):

		 <4>	 8/28/91	CH		Updated interface headers for consistency.
		 <3>	 7/25/91	JL		Checked in database generated file from DSG.
		 <2>	 3/14/90	BBH		repair inclusion of TMIntf (we renamed the interface files)
		 <1>	 3/12/90	BBH		first checked in

	To Do:
************************************************************/


#ifndef __TERMINALTOOLS__
#define __TERMINALTOOLS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __TERMINALS__
#include <Terminals.h>
#endif


enum {


#define	tdefType			'tdef'
#define	tvalType			'tval'
#define	tsetType			'tset'
#define	tlocType			'tloc'
#define	tscrType			'tscr'
#define	tbndType			'tbnd'
#define	tverType			'vers'

/* messages */

 tmInitMsg = 0,
 tmDisposeMsg = 1,
 tmSuspendMsg = 2,
 tmResumeMsg = 3,
 tmMenuMsg = 4,
 tmEventMsg = 5,
 tmActivateMsg = 6,
 tmDeactivateMsg = 7,
 tmGetErrorStringMsg = 8,

 tmIdleMsg = 50,
 tmResetMsg = 51,

 tmKeyMsg = 100,
 tmStreamMsg = 101,
 tmResizeMsg = 102, 
 tmUpdateMsg = 103, 
 tmClickMsg	 = 104,
 tmGetSelectionMsg = 105,
 tmSetSelectionMsg = 106,
 tmScrollMsg = 107, 
 tmClearMsg = 108
};
enum {
 tmGetLineMsg = 109,
 tmPaintMsg	 = 110,
 tmCursorMsg = 111,
 tmGetEnvironsMsg = 112,	
 tmDoTermKeyMsg = 113,
 tmCountTermKeysMsg = 114,
 tmGetIndTermKeyMsg = 115,

/* messages for validate DefProc    */
 tmValidateMsg = 0,
 tmDefaultMsg = 1,

/* messages for Setup DefProc    */
 tmSpreflightMsg = 0,
 tmSsetupMsg = 1,
 tmSitemMsg	 = 2,
 tmSfilterMsg = 3,
 tmScleanupMsg = 4,

/* messages for scripting defProc    */
 tmMgetMsg = 0,
 tmMsetMsg = 1,

/* messages for localization defProc  */
 tmL2English = 0,
 tmL2Intl = 1
};

struct TMSearchBlock {
		StringHandle	theString;
		Rect			where;
		TMSearchTypes	searchType;
		ProcPtr			callBack;
		short			refnum;
		struct TMSearchBlock	*next;
};

typedef struct TMSearchBlock TMSearchBlock;
typedef TMSearchBlock *TMSearchBlockPtr;

struct TMSetupStruct {
		DialogPtr		theDialog;
		short			count;
		Ptr				theConfig;
	short procID; /* procID of the tool */
};

typedef struct TMSetupStruct TMSetupStruct;
typedef TMSetupStruct *TMSetupPtr;



#endif