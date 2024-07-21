{
Created: Tuesday, August 2, 1988 at 12:26 PM
	ErrMgr.p
	Pascal Interface to the Macintosh Libraries


	<<< ErrMgr - Error File Manager Routines Interface File >>> 
	
	
	Copyright Apple Computer, Inc.	1987-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Updated Copyright.

	To Do:

	This file contains:
	
	InitErrMgr(toolname, sysename, Nbrs)  - ErrMgr initialization
	CloseErrMgr()						  - Close ErrMgr message files
	GetSysErrText(Nbr, Msg) 			  - Get a system error message for a number
	GetToolErrText(Nbr, Insert, Msg)	  - Get a tool error message for a number
	AddErrInsert(insert, msgString) 	  - Add an insert to a message
	
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT ErrMgr;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingErrMgr}
{$SETC UsingErrMgr := 1}

{$I+}
{$SETC ErrMgrIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := ErrMgrIncludes}


PROCEDURE InitErrMgr(toolErrFilename: Str255;sysErrFilename: Str255;showToolErrNbrs: BOOLEAN);
{ ErrMgr initialization.This must be done before using any other ErrMgr
routine.  Set showToolErrNbrs to true if you want all tool messages to contain
the error number following the message text enclosed in parentheses (e.g.,
"<msg txt> ([OS] Error <n>)"; system error messages always contain the error
number).  The toolErrFileName parameter is used to specify the name of a
tool-specific error file, and should be the NULL or a null string if not used
(or if the tool's data fork is to be used as the error file, see
GetToolErrText for futher details). The sysErrFileName parameter is used to
specify the name of a system error file, and should normally be the NULL or a
null string, which causes the ErrMgr to look in the MPW Shell directory for
"SysErrs.Err" (see GetSysErrText). }

PROCEDURE CloseErrMgr; C;
{ Ideally a CloseErrMgr should be done at the end of execution to make sure all
files opened by the ErrMgr are closed.	You can let normal program termination
do the closing.  But if you are a purist...
 }

PROCEDURE GetSysErrText(msgNbr: INTEGER;errMsg: StringPtr);
(* Get the error message text corresponding to system error number errNbr from
the system error message file (whose name was specified in the InitErrMgr
call).	The text of the message is returned in errMsg and the function returns
a pointer to errMsg.  The maximum length of the message is limited to 254
characters.

Note, if a system message filename was not specified to InitErrMgr, then the
ErrMgr assumes the message file contained in the file "SysErrs.Err".  This
file is first accessed as "                                 {ShellDirectory}SysErrs.Err" on the assumption that
SysErrs.Err is kept in the same directory as the MPW Shell.  If the file
cannot be opened, then an open is attempted on "SysErrs.Err" in the System
Folder. *)

PROCEDURE AddErrInsert(insert: Str255;msgString: StringPtr); C;
{ Add another insert to an error message string.This call is used when more
than one insert is to be added to a message (because it contains more than
one '^' character).
 }

PROCEDURE GetToolErrText(msgNbr: INTEGER;errInsert: Str255;errMsg: StringPtr);
(* Get the error message text corresponding to tool error number errNbr from
the tool error message file (whose name was specified in the InitErrMgr
call).	The text of the message is returned in errMsg and the function returns
a pointer to errMsg.  The maximum length of the message is limited to 254
characters.  If the message is to have an insert, then ErrInsert should be a
pointer to it.	Otherwise it should be either be a null string or a NULL
pointer.

Inserts are indicated in error messages by specifying a '^' to indicate where
the insert is to be placed.

Note, if a tool message filename was not specified to InitErrMgr, then the
ErrMgr assumes the message file contained in the data fork of the tool calling
the ErrMgr.  This name is contained in the Shell variable	{Command} and the
value of that variable is used to open the error message file. *)



{$ENDC}    { UsingErrMgr }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

