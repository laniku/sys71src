{
	File:		FileTransferToolsPriv.p

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
UNIT FileTransferToolsPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED FileTransferToolsPriv}
{$SETC FileTransferToolsPriv := 1}


INTERFACE

CONST
	ftCleanupMsg		=	101;
	
{$ENDC}    { FileTransferToolsPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

