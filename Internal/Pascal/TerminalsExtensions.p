{
	File:		TerminalsExtensions.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 8/20/91	BH		remove TMSetupCleanup from public interfaces
		 <1>	 6/18/91	BH		first checked in

	To Do:
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT TerminalsExtensions;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTerminalsExtensions}
{$SETC UsingTerminalsExtensions := 1}

{$I+}
{$SETC TerminalsExtensionsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingDialogs}
{$I $$Shell(PInterfaces)Dialogs.p}
{$ENDC}

{$IFC UNDEFINED UsingCTBUtilities}
{$I $$Shell(PInterfaces)CTBUtilities.p}
{$ENDC}

{$IFC UNDEFINED UsingConnections}
{$I $$Shell(PInterfaces)Connections.p}
{$ENDC}

{$IFC UNDEFINED UsingTerminals}
{$I $$Shell(PInterfaces)Terminals.p}
{$ENDC}

{$SETC UsingIncludes := TerminalsExtensionsIncludes}

CONST
{ TMChooseRec messages	}
	tmChooseNoChangeHandle	=	1;
	tmChooseNoDialog		=	2;
	tmChooseNoChangeTool	=	4;
	
TYPE	
	{ TMChoose data structures }
	TMChooseRecPtr 	=	^TMChooseRec;
	TMChooseRec		=	RECORD
		reserved	:	LONGINT;
		msg			:	LONGINT;
		idleProc	:	ProcPtr;
		filterProc	:	ProcPtr;
		newTool		:	Str63;
		newConfig	:	Ptr;
		eventProc	:	ProcPtr;
	END;
	
FUNCTION 	TMPChoose(VAR hTerm:TermHandle; where: Point; VAR cRec: TMChooseRec) : INTEGER;

PROCEDURE 	TMSetupCleanup(procID: INTEGER;theConfig: Ptr;count: INTEGER;
 theDialog: DialogPtr;VAR magicCookie: LONGINT);
{$ENDC} {UsingTerminalsExtensions}

{$IFC NOT UsingIncludes}
	END.
{$ENDC}
