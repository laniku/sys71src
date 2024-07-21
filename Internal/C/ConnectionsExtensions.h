/*
	File:		ConnectionsExtensions.h

	Copyright:	© 1988-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <9>	 10/4/91	JSM		Change PsychoticFarmerOrLater conditionals to TheFuture.
		 <8>	 10/2/91	DTY		Conditionalize <5> and <6> out of CubeE.  Reintroduce the cmPBx
									#defines for CubeE.
		 <7>	 8/27/91	JSM		Cleanup header.
		 <6>	 8/20/91	BH		remove CMSetupCleanup from public interfaces
		 <5>	 6/18/91	BH		remove 1.1 stuff to mainline interfaces
		 <4>	 1/14/91	CP		;Removed CMConnectPrep and added CMListenPrep and CMOpenPrep.
									;Renamed CMFreeIORec to CMDisposeIOPB.
									;Renamed CMAllocateIORec to CMNewIOPB.
									;Removed param block from CMPBAccept, CMPBListen, CMPBClose,
									CMPBOpen, and CMConnectCleanup.
									;Changed reserved0 (long) in CMIORec to asyncEOM (long).  It
									already was called this in the .a file.
									;Changed reserved2 (long) in CMIORec to reserved2 (short) and
									version (short).
									;Added async, completor, and timeout parameters to CMListenPrep
									and CMOpenPrep.
									;Renamed CMIORec to CMIOPB  <BBH>
		 <3>	11/27/90	kaz		Moving CMExtensions tool messages to Internal; Renamed  CMHCalls
									to CMPBCalls; added new calls for CMPBOpen, etc. <jng>
		 <2>	 11/4/90	dba		get rid of unnecessary use of __cpluscplus

*/

#ifndef	__CONNECTIONSEXTENSIONS__
#define __CONNECTIONSEXTENSIONS__

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif

#ifndef __CTBUTILITIES__
#include <CTBUtilities.h>
#endif

#ifndef __CONNECTIONS__
#include <Connections.h>
#endif

/* CMChoose data structures */
struct CMChooseRec {
	long	reserved;
	long	msg;
	ProcPtr	idleProc;
	ProcPtr	filterProc;
	Str63	newTool;
	Ptr		newConfig;
	ProcPtr	eventProc;
};
typedef struct CMChooseRec CMChooseRec;
typedef CMChooseRec *CMChooseRecPtr;

#if CubeE									// <8> Bring back for CubeE
#define cmPBOpenMsg				116
#define cmPBCloseMsg			117
#define cmPBListenMsg			118
#define cmPBAcceptMsg			119
#define cmListenPrepMsg			120
#define cmOpenPrepMsg			121
#define cmConnectCleanupMsg		122
#endif										// <8>

/* CMChooseRec messages */
#define	cmChooseNoChangeHandle		1
#define	cmChooseNoDialog			2
#define	cmChooseNoChangeTool		4

#ifdef __cplusplus
extern "C" {
#endif
// new calls
extern pascal short 	CMPChoose(ConnHandle *hConn, Point where, CMChooseRec *cRec);

#if CubeE									// <8> Bring back for CubeE
extern pascal void 		CMSetupXCleanup(short procID, Ptr theConfig, short count,
							DialogPtr theDialog, Boolean OKed, long *magicCookie );
extern pascal void		CMGetErrorString(ConnHandle hConn, short id, Str255 errMsg);

extern pascal CMErr  	CMNewIOPB(ConnHandle hConn, CMIOPBPtr *theIOPB);
extern pascal CMErr	 	CMDisposeIOPB(ConnHandle hConn, CMIOPBPtr theIOPB);

extern pascal CMErr	 	CMPBRead(ConnHandle hConn, CMIOPBPtr theIOPB, Boolean async);
extern pascal CMErr	 	CMPBWrite(ConnHandle hConn, CMIOPBPtr theIOPB, Boolean async);
extern pascal CMErr	 	CMPBIOKill(ConnHandle hConn, CMIOPBPtr theIOPB);

extern pascal CMErr	 	CMPBOpen(ConnHandle hConn, Boolean async);
extern pascal CMErr	 	CMPBClose(ConnHandle hConn, Boolean async);
extern pascal CMErr	 	CMPBListen(ConnHandle hConn, Boolean async);
extern pascal CMErr	 	CMPBAccept(ConnHandle hConn, Boolean async, Boolean accept);
extern pascal CMErr	 	CMListenPrep(ConnHandle hConn, Boolean async, ProcPtr completor,
							long timeout);
extern pascal CMErr	 	CMOpenPrep(ConnHandle hConn, Boolean async, ProcPtr completor,
							long timeout);
extern pascal void	 	CMConnectCleanup(ConnHandle hConn);
#endif										// <8>
#if TheFuture								// <8>
pascal void  	CMSetupCleanup(short procID,const void *theConfig,short count,
 DialogPtr theDialog,long *magicCookie);
#endif

#ifdef __cplusplus
}
#endif

#endif
