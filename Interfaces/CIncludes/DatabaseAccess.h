
/************************************************************

Created: Monday, July 22, 1991 at 4:03 PM
 DatabaseAccess.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		<27>	 9/10/91	MH		Remove typeChar. It was intentionally moved to AppleEvents.h in
									<25> but not noted in change history. Then erroneously replaced
									in <26> (by moi)
		<26>	 9/10/91	MH		Replace def of typeChar inadvertantly dropped in <25>
		<25>	 7/23/91	JL		Match Pascal File: Fixed comments, Added ColInfoHandle and
									ColTypesHandle typedefs. Changed field types in ResultRecord to
									use new types. Added typeNone constant.
		<24>	 6/14/91	JL		Changed Ptr of ResListElem struct to ResListPtr to match pascal
									Interface file. Removed conditionalized constants: typeBoolean -
									> typeFloat. They belong in AppleEvents.h. Updated copyright
									date.
		<22>	12/12/90	JL		Put formal paramter names back.
		<21>	 11/8/90	JL		Changed all #defines to anonymous enums
		<20>	 11/4/90	dba		get rid of stuff after #endif (not allowed by the ANSI
									standard);
									use (void) instead of ();
									used constStr255Parameter;
									got rid of some extraneous parameter names;
									made some parameters void* instead of Ptr
		<19>	  10/9/90	JAL		CPlusPlus update. Took out unNeeded Noditionals.
		<18>	  9/7/90	ngk		Conditionalized the definition of some data types if AppleEvents
									has alreday been included.
		<17>	  8/2/90	JSM		Add kDBNullFlag.
		<16>	  7/1/90	JSM		Change typeChar constant from 'char' to 'TEXT'.
		<15>	  7/1/90	JSM		Update some DBType constants to conform to AppleEvents
									conventions.
		<14>	 4/27/90	JSM		Remove QuitDBPack call.
		<13>	 3/13/90	JSM		Remove kDBGetItemEndOfRow message, add DBColInfoRecord, update
									ResultsRecord, bump version number on InitDBPack, change names
									of ResultsHandler routines to ResultHandler.
		<12>	 2/26/90	JSM		Change selectors to use new dispatcher, eliminate gaps between
									return codes, bump version on InitDBPack.
		<11>	 2/22/90	JSM		Add kDBStartQueryComplete.
		 <9>	  2/8/90	JSM		Restore change history.
		 <7>	  2/6/90	JSM		Remove rcDBCancel and rcDBStatusCancel, add
		 							kDBGetQueryResultsComplete.
		 <6>	  2/5/90	JSM		Remove obsolete return code rcDBBadCol.
		 <4>	  1/4/90	JSM		Change some variable names in response to suggestions from
									documentation.
		 <3>	12/22/89	JSM		Add kDBLastColFlag.
		 <2>	12/19/89	JSM		Cleanup after initial checkin.
		 <1>	12/19/89	JSM		Adding to public includes for the first time.
	   <2.2>	 11/7/89	JSM		Added status functions, changed DBUnGetVal to DBUnGetItem,
									bumped version on InitDBPack.
	   <2.1>	 10/6/89	JSM		Updated to make SnarfMan a PACK.
	   <2.0>	 8/29/89	JSM		Updated for new version 2 API.
	   <1.8>	  8/7/89	JSM		Added new rc's, added colLens to ResultsRecord, added kill and
									results-to-text stuff.
	   <1.7>	 7/26/89	JSM		Added new return code rcDBAsyncNotSupp.
	   <1.6>	 7/19/89	JSM		Changed 'type' to 'theType' in ResListElem, 'type' to 'dataType'
									elsewhere.
	   <1.5>	 6/22/89	JSM		DBType now OSType, removed handle in ResListElem, updated
									DBGetRow interface.
	   <1.4>	  6/9/89	JSM		Added 4 byte data types, ddevRef to async param block.
	   <1.3>	 5/31/89	JSM		Removed rcDBReady and rcDBSize errors, added async support.
	   <1.2>	 5/18/89	JSM		Removed selectors, now return OSErrs, added version and id to
									QueryRecord, now use lowercase resource types.
	   <1.1>	 4/28/89	JSM		Added high-level information.
	   <1.0>	 4/11/89	JSM		Added to EASE for the first time.

************************************************************/


#ifndef __DATABASEACCESS__
#define __DATABASEACCESS__

#ifndef __RESOURCES__
#include <Resources.h>
#endif


enum {


/* error and status codes */
 rcDBNull = -800,
 rcDBValue = -801,
 rcDBError = -802,
 rcDBBadType = -803,
 rcDBBreak = -804,
 rcDBExec = -805,
 rcDBBadSessID = -806,
 rcDBBadSessNum = -807,			/* bad session number for DBGetConnInfo */

 rcDBBadDDEV = -808,			/* bad ddev specified on DBInit */

 rcDBAsyncNotSupp = -809,		/* ddev does not support async calls */
 rcDBBadAsyncPB = -810,			/* tried to kill a bad pb */

 rcDBNoHandler = -811,			/* no app handler for specified data type */

 rcDBWrongVersion = -812,		/* incompatible versions */
 rcDBPackNotInited = -813,		/* attempt to call other routine before InitDBPack */

/* messages for status functions for DBStartQuery */
 kDBUpdateWind = 0,
 kDBAboutToInit = 1,
 kDBInitComplete = 2,
 kDBSendComplete = 3,
 kDBExecComplete = 4,
 kDBStartQueryComplete = 5
};
enum {

/* messages for status functions for DBGetQueryResults */
 kDBGetItemComplete = 6,
 kDBGetQueryResultsComplete = 7,

/* data type codes */

#define typeNone 'none'
#define typeDate 'date'
#define typeTime 'time'
#define typeTimeStamp 'tims'
#define typeDecimal 'deci'
#define typeMoney 'mone'
#define typeVChar 'vcha'
#define typeVBin 'vbin'
#define typeLChar 'lcha'
#define typeLBin 'lbin'
#define typeDiscard 'disc'

/* "dummy" types for DBResultsToText */
#define typeUnknown 'unkn'
#define typeColBreak 'colb'
#define typeRowBreak 'rowb'

/* pass this in to DBGetItem for any data type */
#define typeAnyType (DBType)0

/* infinite timeout value for DBGetItem */

 kDBWaitForever = -1,

/*  flags for DBGetItem  */
 kDBLastColFlag = 0x0001,
 kDBNullFlag = 0x0004
};

typedef OSType DBType;

/* structure for asynchronous parameter block */
struct DBAsyncParamBlockRec {
 ProcPtr completionProc;		/* pointer to completion routine */
 OSErr result;					/* result of call */
 long userRef;					/* for application's use */
 long ddevRef;					/* for ddev's use */
 long reserved;					/* for internal use */
};

typedef struct DBAsyncParamBlockRec DBAsyncParamBlockRec;
typedef DBAsyncParamBlockRec *DBAsyncParmBlkPtr;

/* structure for resource list in QueryRecord */
struct ResListElem {
 ResType theType;				/* resource type */
 short id;						/* resource id */
};

typedef struct ResListElem ResListElem;
typedef ResListElem *ResListPtr, **ResListHandle;

/* structure for query list in QueryRecord */
typedef Handle **QueryListHandle;

struct QueryRecord {
 short version;					/* version */
 short id;						/* id of 'qrsc' this came from */
 Handle queryProc;				/* handle to query def proc */
 Str63 ddevName;				/* ddev name */
 Str255 host;					/* host name */
 Str255 user;					/* user name */
 Str255 password;				/* password */
 Str255 connStr;				/* connection string */
 short currQuery;				/* index of current query */
 short numQueries;				/* number of queries in list */
 QueryListHandle queryList;		/* handle to array of handles to text */
 short numRes;					/* number of resources in list */
 ResListHandle resList;			/* handle to array of resource list elements */
 Handle dataHandle;				/* for use by query def proc */
 long refCon;					/* for use by application */
};

typedef struct QueryRecord QueryRecord;
typedef QueryRecord *QueryPtr, **QueryHandle;

/* structure of column types array in ResultsRecord */
typedef Handle ColTypesHandle;

/* structure for column info in ResultsRecord */
struct DBColInfoRecord {
 short len;
 short places;
 short flags;
};

typedef struct DBColInfoRecord DBColInfoRecord;

typedef Handle ColInfoHandle;

/* structure of results returned by DBGetResults */
struct ResultsRecord {
 short numRows;					/* number of rows in result */
 short numCols;					/* number of columns per row */
 ColTypesHandle colTypes;		/* data type array */
 Handle colData;				/* actual results */
 ColInfoHandle colInfo;			/* DBColInfoRecord array */
};

typedef struct ResultsRecord ResultsRecord;


#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr InitDBPack(void)
 = {0x3F3C,0x0004,0x303C,0x0100,0xA82F}; 
pascal OSErr DBInit(long *sessID,ConstStr63Param ddevName,ConstStr255Param host,
 ConstStr255Param user,ConstStr255Param passwd,ConstStr255Param connStr,
 DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0E02,0xA82F}; 
pascal OSErr DBEnd(long sessID,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0403,0xA82F}; 
pascal OSErr DBGetConnInfo(long sessID,short sessNum,long *returnedID,long *version,
 Str63 ddevName,Str255 host,Str255 user,Str255 network,Str255 connStr,long *start,
 OSErr *state,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x1704,0xA82F}; 
pascal OSErr DBGetSessionNum(long sessID,short *sessNum,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0605,0xA82F}; 
pascal OSErr DBSend(long sessID,char *text,short len,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0706,0xA82F}; 
pascal OSErr DBSendItem(long sessID,DBType dataType,short len,short places,
 short flags,void *buffer,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0B07,0xA82F}; 
pascal OSErr DBExec(long sessID,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0408,0xA82F}; 
pascal OSErr DBState(long sessID,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0409,0xA82F}; 
pascal OSErr DBGetErr(long sessID,long *err1,long *err2,Str255 item1,Str255 item2,
 Str255 errorMsg,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0E0A,0xA82F}; 
pascal OSErr DBBreak(long sessID,Boolean abort,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x050B,0xA82F}; 
pascal OSErr DBGetItem(long sessID,long timeout,DBType *dataType,short *len,
 short *places,short *flags,void *buffer,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x100C,0xA82F}; 
pascal OSErr DBUnGetItem(long sessID,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x040D,0xA82F}; 
pascal OSErr DBKill(DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x020E,0xA82F}; 
pascal OSErr DBGetNewQuery(short queryID,QueryHandle *query)
 = {0x303C,0x030F,0xA82F}; 
pascal OSErr DBDisposeQuery(QueryHandle query)
 = {0x303C,0x0210,0xA82F}; 
pascal OSErr DBStartQuery(long *sessID,QueryHandle query,ProcPtr statusProc,
 DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0811,0xA82F}; 
pascal OSErr DBGetQueryResults(long sessID,ResultsRecord *results,long timeout,
 ProcPtr statusProc,DBAsyncParmBlkPtr asyncPB)
 = {0x303C,0x0A12,0xA82F}; 
pascal OSErr DBResultsToText(ResultsRecord *results,Handle *theText)
 = {0x303C,0x0413,0xA82F}; 
pascal OSErr DBInstallResultHandler(DBType dataType,ProcPtr theHandler,
 Boolean isSysHandler)
 = {0x303C,0x0514,0xA82F}; 
pascal OSErr DBRemoveResultHandler(DBType dataType)
 = {0x303C,0x0215,0xA82F}; 
pascal OSErr DBGetResultHandler(DBType dataType,ProcPtr *theHandler,Boolean getSysHandler)
 = {0x303C,0x0516,0xA82F}; 
#ifdef __cplusplus
}
#endif

#endif
