{
	File:		ConnectionsExtensions.p

	Contains:	Internal interfaces to new Conn Mgr calls

	Written by:	Byron Han

	Copyright:	© 1988-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	 8/27/91	JSM		Cleanup header.
		 <5>	 8/20/91	BH		remove CMSetupCleanup from public interfaces
		 <4>	 6/18/91	BH		remove 1.1 stuff and moved to ConnectionTools.p and
									Connections.p
		 <3>	 1/14/91	CP		;Removed CMConnectPrep and added CMListenPrep and CMOpenPrep.
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
		 <2>	11/27/90	kaz		Moving CMExtensions tool messages to Internal; Renamed CMHCalls
									to CMPBCalls; added new calls for CMPBOpen, etc <jng>

}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT ConnectionsExtensions;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingConnectionsExtensions}
{$SETC UsingConnectionsExtensions := 1}

{$I+}
{$SETC ConnectionsExtensionsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingDialogs}
{$I Dialogs.p}
{$ENDC}

{$IFC UNDEFINED UsingCTBUtilities}
{$I CTBUtilities.p}
{$ENDC}

{$SETC UsingIncludes := ConnectionsExtensionsIncludes}

CONST
{ CMChooseRec messages	}
	cmChooseNoChangeHandle	=	1;
	cmChooseNoDialog		=	2;
	cmChooseNoChangeTool	=	4;
	
TYPE
	{ CMChoose data structures }
	CMChooseRecPtr 	=	^CMChooseRec;
	CMChooseRec		=	RECORD
		reserved	:	LONGINT;
		msg			:	LONGINT;
		idleProc	:	ProcPtr;
		filterProc	:	ProcPtr;
		newTool		:	Str63;
		newConfig	:	Ptr;
		eventProc	:	ProcPtr;
	END;
	
{	New Calls }
FUNCTION 	CMPChoose(VAR hConn:ConnHandle; where: Point; VAR cRec: CMChooseRec) : INTEGER;

PROCEDURE 	CMSetupCleanup(procID: INTEGER;theConfig: Ptr;count: INTEGER;
 theDialog: DialogPtr;VAR magicCookie: LONGINT);
 
{$ENDC} {UsingConnectionsExtensions}

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

