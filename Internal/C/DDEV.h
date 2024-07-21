/************************************************************

Created: Tuesday, March 21, 1989 at 9:39 AM
	DDEV.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	 1989-90
	All rights reserved

	Change History (most recent first):

		 <6>	 11/8/90	JL		Changed #defines to anonymous enums.
		 <3>	  1/4/90	JSM		Change some variable names in response to suggestions from
									documentation.
		 <2>	12/19/89	JSM		Cleanup after initial checkin.
		 <1>	12/19/89	JSM		Adding to public includes for the first time.
	   <2.2>	 11/7/89	JSM		Changed kDBUnGetVal to kDBUnGetItem.
	   <2.1>	 10/6/89	JSM		Updated to make SnarfMan a PACK.
	   <2.0>	 8/29/89	JSM		Updated for new version 2 API.
	   <1.8>	  8/7/89	JSM		Added kDBKill message.
	   <1.7>	 7/26/89	JSM		Added ddev flags stuff.
	   <1.6>	 7/19/89	JSM		Changed 'type' to 'dataType' in DDEVParams.
	   <1.5>	 7/15/89	JSM		Added DDEVParamsPtr typedef.
	   <1.4>	  6/9/89	JSM		Moved pb field in ddevParams.
	   <1.3>	 5/31/89	JSM		Added pb field to DDEVParams.
	   <1.2>	 5/18/89	JSM		Added new message selectors.
	   <1.1>	 4/28/89	JSM		Added some new stuff.
	   <1.0>	 4/11/89	JSM		Added to EASE for the first time.
************************************************************/


#ifndef __DDEV__
#define __DDEV__

#ifndef __DATABASEACCESS__
#include <DatabaseAccess.h>
#endif __DATABASEACCESS__

/* messages for ddev */
enum {kDBInit = 0};
enum {kDBEnd = 1};
enum {kDBGetConnInfo = 2};
enum {kDBGetSessionNum = 3};
enum {kDBSend = 4};
enum {kDBSendItem = 5};
enum {kDBExec = 6};
enum {kDBState = 7};
enum {kDBGetErr = 8};
enum {kDBBreak = 9};
enum {kDBGetItem = 10};
enum {kDBUnGetItem = 11};
enum {kDBKill = 12};
enum {kDBOpen = 100};
enum {kDBClose = 101};
enum {kDBIdle = 102};

/*  resource IDs of misc. resources  */

enum {kDDEVName = 128};                 /* ID of 'STR ' resource with ddev name */
enum {kDDEVID = 128};                   /* ID of 'ddev' resource */
enum {kDDEVFlags = 128};                /* ID of 'dflg' resource */

enum {kAsyncSupported = 0x00000001};    /* bit for async support */


/* structure of 'dflg' resource */
struct DDEVFlags {
	long			version;		/* always 0 for this release */
	long			flags;			/* flags */
};

#ifndef __cplusplus
typedef struct DDEVFlags DDEVFlags;
#endif

struct DDEVParams {
	short			message;		/* action for ddev */
	long			ddevStorage;	/* storage for ddev */
	DBAsyncParmBlkPtr	asyncPB;	/* async parameter block pointer */
	long			sessID; 		/* session ID */
	long			returnedID; 	/* session ID returned by DBGetConnInfo */
	long			version;		/* version returned by DBGetConnInfo */
	long			start;			/* start returned by DBGetConnInfo */
	StringPtr		host;			/* host for DBInit and DBGetConnInfo */
	StringPtr		user;			/* user for DBInit and DBGetConnInfo */
	StringPtr		password;		/* password for DBInit and DBGetConnInfo */
	StringPtr		connStr;		/* connection str for DBInit and DBGetConnInfo */
	StringPtr		network;		/* network for DBGetConnInfo */
	Ptr 			buffer; 		/* buffer used in several calls */
	long			err1;			/* error 1 for DBGetErr */
	long			err2;			/* error 2 for DBGetErr */
	StringPtr		item1;			/* item 1 for DBGetErr */
	StringPtr		item2;			/* item 2 for DBGetErr */
	StringPtr		errorMsg;		/* errorMsg for DBGetErr */
	long			timeout;		/* timeout for DBGetItem */
	DBType			dataType;		/* type for several calls */
	short			sessNum;		/* session number for DBGetConnInfo
										and DBGetSessionNum */
	short			state;			/* state for DBGetConnInfo */
	short			len;			/* length of buffer */
	short			places; 		/* places for DBSendItem and DBGetItem */
	short			flags;			/* flags for DBSendItem and DBGetItem */
	Boolean 		abort;			/* abort for DBBreak */
};

#ifndef __cplusplus
typedef struct DDEVParams DDEVParams;
#endif

typedef DDEVParams *DDEVParamsPtr;

#endif __DDEV__
