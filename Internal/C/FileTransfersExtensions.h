/*
	File:		FileTransfersExtensions.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 8/20/91	BH		remove FTSetupCleanup from public interfaces
		 <1>	 6/18/91	BH		first checked in

	To Do:
*/


#ifndef __FILETRANSFERSEXTENSIONS__
#define __FILETRANSFERSEXTENSIONS__

#ifndef __CTBUTILITIES__
#include <CTBUtilities.h>
#endif	__CTBUTILITIES__

#ifndef __FILETRANSFERS__
#include <FileTransfers.h>
#endif	__FILETRANSFERS__



/* FTChoose data structures */
struct FTChooseRec {
	long	reserved;
	long	msg;
	ProcPtr	idleProc;
	ProcPtr	filterProc;
	Str63	newTool;
	Ptr		newConfig;
	ProcPtr	eventProc;
};
typedef struct FTChooseRec FTChooseRec;
typedef FTChooseRec *FTChooseRecPtr;

/* FTChooseRec messages */
#define	ftChooseNoChangeHandle		1
#define	ftChooseBackdoor		2


#ifdef __cplusplus
extern "C" {
#endif
pascal short 	FTPChoose(FTHandle *hFT, Point where, FTChooseRec *cRec);
pascal void  	FTSetupCleanup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,long *magicCookie);
#ifdef __cplusplus
}
#endif

#endif __FILETRANSFERSEXTENSIONS__