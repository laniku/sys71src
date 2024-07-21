/************************************************************
	FileTransferTools.h
	C Interface to the CommToolBox File Transfer tools

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved
		
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <7>	 8/28/91	CH		Updated interface headers for consistency.
		 <6>	 7/25/91	JL		Checked in database generated file from DSG.  Changed all
									#defines to anonymous enums.
		 <5>	  7/2/91	BH		fix misspelling of ftReceiveMsg
		 <4>	 6/26/91	BH		add messages for ftSendMsg and ftReceiveMsg
		 <3>	 10/9/90	JAL		took out IfDef CPlusPlus not needed anymore.
		 <2>	 3/14/90	BBH		fix inclusion of FTIntf.h
		 <1>	 3/12/90	BBH		first checked in

	To Do:
************************************************************/


#ifndef __FILETRANSFERTOOLS__
#define __FILETRANSFERTOOLS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __FILETRANSFERS__
#include <FileTransfers.h>
#endif


enum {


/* Control */
 ftInitMsg = 0,
 ftDisposeMsg = 1,
 ftSuspendMsg = 2,
 ftResumeMsg = 3,
 ftMenuMsg = 4,
 ftEventMsg = 5,
 ftActivateMsg = 6,
 ftDeactivateMsg = 7,
 ftGetErrorStringMsg = 8,

 ftAbortMsg = 52,

 ftStartMsg = 100,
 ftExecMsg = 102,
 ftSendMsg = 103,
 ftReceiveMsg = 104,

/*Setup */
 ftSpreflightMsg = 0,
 ftSsetupMsg = 1,
 ftSitemMsg = 2,
 ftSfilterMsg = 3,
 ftScleanupMsg = 4,

/* validate */
 ftValidateMsg = 0
};
enum {
 ftDefaultMsg = 1,

/* scripting */
 ftMgetMsg = 0,
 ftMsetMsg = 1,

/* localization */
 ftL2English = 0,
 ftL2Intl = 1

/* DEFs */

#define		fdefType		'fdef'
#define		fsetType		'fset'
#define		fvalType		'fval'
#define		flocType		'floc'
#define		fscrType		'fscr'

#define		fbndType		'fbnd'
#define		fverType		'vers'
};

struct FTSetupStruct {
	DialogPtr	theDialog;			/* the dialog form the application */
	short		count;				/* first appended item */
	Ptr			theConfig;			/* the config record to setup */
	short		procID;				/* procID of the tool */
};

typedef struct FTSetupStruct FTSetupStruct;
typedef FTSetupStruct *FTSetupPtr;	


	
#endif