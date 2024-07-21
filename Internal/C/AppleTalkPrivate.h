/*
	File:		AppleTalkPrivate.h

	Contains:	C declarations for things that are private to AppleTalk

	Written by:	Mike Shoemaker

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 1/18/91	mbs		(jg) First moved to BBS
		 <5>	 1/13/91	mbs		Fix comments, copyright.
		 <4>	 1/13/91	mbs		Change #defines to enums, add transition queue privates
		 <3>	11/27/90	mbs		For AddNodeIDParms structure, change type of NodeArrayPtr to
									long * rather than void * (Greg Seitz request)
		 <2>	10/31/90	mbs		Fix typo in remove node ID typedef
				10/23/90	mbs		created

	To Do:
*/

#ifndef __APPLETALKPRIVATE__
#define __APPLETALKPRIVATE__

#ifndef __APPLETALK__
#include <AppleTalk.h>
#endif

/*
** Internal csCodes for .MPP
*/
enum {NetworkWrite = 261};				/* DDP write with src addr */
enum {AddNodeID = 262};					/* Add Multinode (will change) */
enum {RemoveNodeID = 263};				/* Unimplemented */
enum {Get976Hooks = 264};				/* Get address of 976 vars */


/*
** NetworkWrite
*/
typedef struct {
    MPPATPHeader 
    char 		filler;				/* unused */
    char 		checksumFlag;		/*  -> check sum flag */
    Ptr 		wdsPointer;			/*  -> write data structure */
} NetworkWriteparms;

/*
** AddNodeID -- Interface will change
*/
typedef struct {
    MPPATPHeader 
	char		filler[8];			/* unused */
	short		NodesReq;			/* <-> Nodes requested, nodes gotten */
	long*		NodeArrayPtr;		/*  -> Ptr to node array. [0] is our node */
} AddNodeIDparms;

/*
** RemoveNodeID -- Not implemented yet
*/
typedef struct {
    MPPATPHeader 
} RemoveNodeIDparms;

/*
** Get976Hooks
*/
typedef struct {
    MPPATPHeader 
	void*		pRouterAddr;		/*  -> address of this variable */
	void*		pConfig;			/*  -> address of this variable */
	void*		pZoneHint;			/*  -> address of this variable */
	void*		pCableLo;			/*  -> address of this variable */
	void*		pCableHi;			/*  -> address of this variable */
	void*		pHkPtr976;			/*  -> address of this variable */
	void*		pHkSelfSendPtr;		/*  -> address of this variable */
} Get976Hooksparms;



/*
*************************************************************************************
** Internal stuff for AppleTalk transition Queue
*************************************************************************************
*/

/*
** Internal network queue transition types
*/
enum {ATTransNetworkTransition = 5};	/* .MPP Network ADEV transition */
enum {ATTransNameChangeTellTask = 6};	/* NBP Name has changed */
enum {ATTransNameChangeAskTask = 7};	/* Ok to change NBP Name? */
enum {ATTransCancelNameChange = 8};		/* NBP Name Change was cancelled */

/*
** Pointer to this structure passed for ATTransNameChangeAskTask
*/
typedef struct NameChangeInfo {
	Str32 newObjStr;				// new NBP name
	StringPtr name;					// -> name of ATEvent handler that NAK'd the event
}
	NameChangeInfo, *NameChgPtr, **NameChgHdl;

#endif