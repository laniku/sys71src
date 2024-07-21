{
	File:		FileTransfersPriv.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/14/90	BBH		first checked in
		 <1>	 3/14/90	BBH		first checked in

	To Do:
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT FileTransfersPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED FileTransfersPriv}
{$SETC FileTransfersPriv := 1}

{$I+}
{$SETC FileTransfersPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED FileTransfers}
	{$I FileTransfers.p}
{$ENDC}
{$SETC UsingIncludes := FileTransfersPrivIncludes}

	
FUNCTION FTCleanup(hFT : FTHandle; now : BOOLEAN) : FTErr;

{$ENDC}    { FileTransfersPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

