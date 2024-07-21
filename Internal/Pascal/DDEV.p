{

Created: Tuesday, March 21, 1989 at 9:39 AM
	DDEV.p
	Pascal Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc. 1989-90
	All rights reserved

	Change History (most recent first):

		 <2>	  1/4/90	JSM		Change some variable names in response to suggestions from
									documentation.
		 <1>	12/19/89	JSM		Adding to public includes for the first time.

}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT DDEV;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingDDEV}
{$SETC UsingDDEV := 1}

{$I+}
{$SETC DDEVIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingDatabaseAccess}
{$I $$Shell(PInterfaces)DatabaseAccess.p}
{$ENDC}
{$SETC UsingIncludes := DDEVIncludes}

CONST

{ messages for ddev }
kDBInit = 0;
kDBEnd = 1;
kDBGetConnInfo = 2;
kDBGetSessionNum = 3;
kDBSend = 4;
kDBSendItem = 5;
kDBExec = 6;
kDBState = 7;
kDBGetErr = 8;
kDBBreak = 9;
kDBGetItem = 10;
kDBUnGetItem = 11;
kDBKill = 12;
kDBOpen = 100;
kDBClose = 101;
kDBIdle = 102;

{ resource IDs of misc. resources }
kDDEVName = 128;		{ ID of 'STR ' resource with ddev name }
kDDEVID = 128;			{ ID of 'ddev' resource }
kDDEVFlags = 128;		{ ID of 'dflg' resource }

kAsyncSupported = $00000001;	{ bit for async support }

TYPE

{ structure of 'dflg' resource }
DDEVFlags = RECORD
	version:		LONGINT;		{ always 0 for this release }
	flags:			LONGINT;		{ flags }
	END;

DDEVParams = RECORD
	message:		INTEGER;
	ddevStorage:	LONGINT;
	asyncPB:		DBAsyncParmBlkPtr;
	sessID: 		LONGINT;
	returnedID: 	LONGINT;
	version:		LONGINT;
	start:			LONGINT;
	host:			StringPtr;
	user:			StringPtr;
	password:		StringPtr;
	connStr:		StringPtr;
	network:		StringPtr;
	buffer: 		Ptr;
	err1:			LONGINT;
	err2:			LONGINT;
	item1:			StringPtr;
	item2:			StringPtr;
	errorMsg:		StringPtr;
	timeout:		LONGINT;
	dataType:		DBType;
	sessNum:		INTEGER;
	state:			INTEGER;
	len:			INTEGER;
	places: 		INTEGER;
	flags:			INTEGER;
	abort:			Boolean;
	END;

{$ENDC}    { UsingDDEV }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

