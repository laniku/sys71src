/*
	File:		TerminalsExtensions.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 8/20/91	BH		remove TMSetupCleanup from public interfaces
		 <2>	 6/25/91	JNG		Merge in TerminalsPriv.h
		 <1>	 6/18/91	BH		first checked in

	To Do:
*/

#ifndef __TERMINALSEXTENSIONS__
#define __TERMINALSEXTENSIONS__


#ifndef __TERMINALS__
#include <Terminals.h>
#endif	__TERMINALS__

struct LineDataBlock {
		Ptr				dataPtr;
		long			dataSize;
		Ptr				attrPtr;
		long			attrSize;
		long			reserved;
};

#ifndef _cplusplus
typedef struct LineDataBlock LineDataBlock;
#endif

/* TMChoose data structures */
struct TMChooseRec {
	long	reserved;
	long	msg;
	ProcPtr	idleProc;
	ProcPtr	filterProc;
	Str63	newTool;
	Ptr		newConfig;
	ProcPtr	eventProc;
};
typedef struct TMChooseRec TMChooseRec;
typedef TMChooseRec *TMChooseRecPtr;

/* TMChooseRec messages */
#define	tmChooseNoChangeHandle		1
#define	tmChooseNoDialog			2
#define tmChooseNoChangeTool		4


extern pascal void TMPeekLine(TermHandle hTerm, short lineNo, LineDataBlock *theLineData);
pascal short 	TMPChoose(TermHandle *hTerm, Point where, TMChooseRec *cRec);
pascal void  	TMSetupCleanup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,long *magicCookie);

#endif  __TERMINALSEXTENSIONS__