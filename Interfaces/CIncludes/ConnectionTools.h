/************************************************************
	ConnectionTools.h
	C Interface to CommToolBox Connection tools

		Copyright Apple Computer, Inc. 1988-1991
		All rights reserved

    This file is used in these builds: BigBang

	Change History (most recent first):

		 <9>	 8/28/91	CH		More crap about consistency.
		 <8>	 8/28/91	CH		Updated interface headers for consistency.
		 <7>	 7/25/91	JL		Checked in database generated file from DSG.  Changed all
									#defines to enums.
		 <6>	 6/18/91	BH		ctb 1.1 stuff moved here
		 <5>	 3/13/91	JL		MPW-ized file.  Took out CPlusPlus conditional around struct
									typedefs.
		 <4>	11/27/90	kaz		Moving CMExtensions tool messages to Internal <jng>
		 <3>	 10/3/90	kaz		Changing // comments for ANSI compatibility <jng>
		 <2>	 3/14/90	BBH		fixed interfaces
		 <1>	 3/12/90	BBH		first checked in

	To Do:
************************************************************/


#ifndef __CONNECTIONTOOLS__
#define __CONNECTIONTOOLS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __CONNECTIONS__
#include <Connections.h>
#endif


enum {


/* messages for DefProc */
 cmInitMsg = 0,
 cmDisposeMsg = 1,
 cmSuspendMsg = 2,
 cmResumeMsg = 3,
 cmMenuMsg = 4,
 cmEventMsg = 5,
 cmActivateMsg = 6,
 cmDeactivateMsg = 7,

 cmIdleMsg = 50,
 cmResetMsg = 51,
 cmAbortMsg = 52,

 cmReadMsg = 100,
 cmWriteMsg = 101,
 cmStatusMsg = 102,
 cmListenMsg = 103,
 cmAcceptMsg = 104,
 cmCloseMsg = 105,
 cmOpenMsg = 106,
 cmBreakMsg = 107,
 cmIOKillMsg = 108
};
enum {
 cmEnvironsMsg = 109,
 
/* new connection tool messages for ctb 1.1 */
 cmNewIOPBMsg = 110,
 cmDisposeIOPBMsg = 111,
 cmGetErrorStringMsg = 112,
 cmPBReadMsg = 113,
 cmPBWriteMsg = 114,
 cmPBIOKillMsg = 115,

/*	messages for validate DefProc	*/
 cmValidateMsg = 0,
 cmDefaultMsg = 1,
	
/*	messages for Setup DefProc	*/
 cmSpreflightMsg = 0,
 cmSsetupMsg = 1,
 cmSitemMsg = 2,
 cmSfilterMsg = 3,
 cmScleanupMsg = 4,
	
/*	messages for scripting defProc	*/
 cmMgetMsg = 0,
 cmMsetMsg = 1,
	
/*	messages for localization defProc	*/
 cmL2English = 0,
 cmL2Intl = 1

/*    private data constants */

#define cdefType	'cdef'		/* main connection definition procedure	*/
#define cvalType	'cval'		/* validation definition procedure	*/
#define csetType	'cset'		/* connection setup definition procedure	*/
#define clocType	'cloc'		/* connection configuration localization defProc	*/
#define cscrType	'cscr'		/* connection scripting defProc interfaces	*/

#define cbndType	'cbnd'		/* bundle type for connection	*/
#define cverType	'vers'	
};

struct CMDataBuffer {
	Ptr		thePtr;
	long	count;
	CMChannel channel;
	CMFlags	flags;
};

typedef struct CMDataBuffer CMDataBuffer;
typedef CMDataBuffer *CMDataBufferPtr;

struct CMCompletorRecord {
	Boolean	async;
	ProcPtr	completionRoutine;
};

typedef struct CMCompletorRecord CMCompletorRecord;
typedef CMCompletorRecord *CMCompletorPtr;

/*	Private Data Structure	*/

struct CMSetupStruct {
	DialogPtr theDialog;
	short count;
	Ptr theConfig;
	short	procID;			  /* procID of the tool	*/
};

typedef struct CMSetupStruct CMSetupStruct;
typedef CMSetupStruct *CMSetupPtr;



#endif