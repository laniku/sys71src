{
	File: PaletteMgr.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the Palette Manager are now found in Palettes.p.
	This file, which includes Palettes.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT PaletteMgr;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPaletteMgr}
{$SETC UsingPaletteMgr := 1}

{$I+}
{$SETC PaletteMgrIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPalettes}
{$I $$Shell(PInterfaces)Palettes.p}
{$ENDC}
{$SETC UsingIncludes := PaletteMgrIncludes}

{$ENDC}    { UsingPaletteMgr }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

