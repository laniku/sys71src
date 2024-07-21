
{
Created: Friday, August 2, 1991 at 11:40 PM
 Signal.p
 Pascal Interface to the Macintosh Libraries

	Signal Handling interface.
	This must be compatible with C's <signal.h>

  Copyright Apple Computer, Inc. 1986, 1987, 1988, 1991
  All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <3>	 9/17/91	MH		remove last 4 lines of usingInclude stuff. They only do
									something when you include other files.
		 <2>	  8/8/91	JL		Updated Copyright. Standardized Header.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Signal;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingSignal}
{$SETC UsingSignal := 1}


TYPE
	SignalMap = 	INTEGER;
	SignalHandler = ^LONGINT;	{ Pointer to function }

CONST
	SIG_ERR =	   -1;			{ Returned by IEsignal on error }
	SIG_IGN =		0;
	SIG_DFL =		1;
	SIG_HOLD =		3;
	SIG_RELEASE =	5;

	SIGABRT =		$0001;
	SIGINT =		$0002;		{ Currently only SIGINT implemented }
	SIGFPE =		$0004;
	SIGILL =		$0008;
	SIGSEGV =		$0010;
	SIGTERM =		$0020;

{ Signal Handling Functions }

FUNCTION
	IEsignal(sigNum: LONGINT; sigHdlr: UNIV SignalHandler):
	SignalHandler; C;

FUNCTION
	IEraise(sigNum: LONGINT):
	LONGINT; C;


{$ENDC} { UsingSignal }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}
