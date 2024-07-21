{
	File: PackIntf.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the Package Manager are now found in Packages.p.
	This file, which includes Packages.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT PackIntf;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPackIntf}
{$SETC UsingPackIntf := 1}

{$I+}
{$SETC PackIntfIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPackages}
{$I $$Shell(PInterfaces)Packages.p}
{$ENDC}
{$SETC UsingIncludes := PackIntfIncludes}

{$ENDC}    { UsingPackIntf }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

