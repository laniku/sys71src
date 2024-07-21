{
	File:		TerminalsPriv.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/14/90	BBH		first checked in

	To Do:
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT TerminalsPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED TerminalsPriv}
{$SETC TerminalsPriv := 1}

{$I+}
{$SETC TerminalsPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED Terminals}
	{$I Terminals.p}
{$ENDC}
{$SETC UsingIncludes := TerminalsPrivIncludes}

TYPE
	LineDataBlock		= 	RECORD
		dataPtr			:	Ptr;
		dataSize		:	LONGINT;
		attrPtr			:	Ptr;
		attrSize		:	LONGINT;
		
		reserved		:	LONGINT;
	END;
	
PROCEDURE TMPeekLine(hTerm: TermHandle; lineNo: INTEGER; 
					VAR theLineData: LineDataBlock);

{$ENDC}    { TerminalsPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

