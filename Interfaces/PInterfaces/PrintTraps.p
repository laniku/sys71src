{
	File:		PrintTraps.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 2/18/92	MH		This file is now a stub, provided for backward compatibility
									with existing sources, which includes Printing.p. This file has
									provided access to the print manager via the trap _PrGlue, while
									Printing.p has supported access via glue routines in
									interfaces.o. The glue was only necessary to support execution
									on a Mac Plus or earlier running system 4.0 or earlier. It is no
									longer necessary to support that configuration in current
									internal or external product development. The file printing.p
									has been updated to use the _PrGlue trap inline.

}

{
Created: Tuesday, August 2, 1988 at 9:06 AM
	PrintTraps.p
	Pascal Interface to the Macintosh Libraries

	Copyright Apple Computer, Inc.	1985-1988
	All rights reserved
}

{This file is provided to support existing references to it. The up to date interface is
   defined in Printing.p
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT PrintTraps;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPrintTraps}
{$SETC UsingPrintTraps := 1}

{$I+}
{$SETC PrintTrapsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPrinting}
{$I $$Shell(PInterfaces)Printing.p}
{$ENDC}
{$SETC UsingIncludes := PrintTrapsIncludes}


{$ENDC}    { UsingPrintTraps }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

