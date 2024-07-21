{
	File: MacPrint.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the non-ROM based Print Manager are now found in Printing.p.
	This file, which includes Printing.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT MacPrint;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMacPrint}
{$SETC UsingMacPrint := 1}

{$I+}
{$SETC MacPrintIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPrinting}
{$I $$Shell(PInterfaces)Printing.p}
{$ENDC}
{$SETC UsingIncludes := MacPrintIncludes}

{$ENDC}    { UsingMacPrint }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

