{
	File:		FileTransfersExtensions.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 8/20/91	BH		remove FTSetupCleanup from public interfaces
		 <1>	 6/18/91	BH		first checked in

	To Do:
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT FileTransfersExtensions;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingFileTransfersExtensions}
{$SETC UsingFileTransfersExtensions := 1}

{$I+}
{$SETC FileTransfersExtensionsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPackages}
{$I $$Shell(PInterfaces)Packages.p}
{$ENDC}
{$IFC UNDEFINED UsingCTBUtilities}
{$I $$Shell(PInterfaces)CTBUtilities.p}
{$ENDC}
{$IFC UNDEFINED UsingFileTransfers}
{$I $$Shell(PInterfaces)FileTransfers.p}
{$ENDC}

{$SETC UsingIncludes := FileTransfersExtensionsIncludes}

CONST
{ FTChooseRec messages	}
	ftChooseNoChangeHandle	=	1;
	ftChooseNoDialog		=	2;
	ftChooseNoChangeTool	=	4;

TYPE
	{ FTChoose data structures }
	FTChooseRecPtr 	=	^FTChooseRec;
	FTChooseRec		=	RECORD
		reserved	:	LONGINT;
		msg			:	LONGINT;
		idleProc	:	ProcPtr;
		filterProc	:	ProcPtr;
		newTool		:	Str63;
		newConfig	:	Ptr;
		eventProc	:	ProcPtr;
	END;
	

FUNCTION 	FTPChoose(VAR hFT:FTHandle; where: Point; VAR cRec: FTChooseRec) : INTEGER;
PROCEDURE 	FTSetupCleanup(procID: INTEGER;theConfig: Ptr;count: INTEGER;
 theDialog: DialogPtr;VAR magicCookie: LONGINT);

{$ENDC} {UsingFileTransfersExtensions}

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

