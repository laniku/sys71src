{
	File: MemTypes.p

	As of MPW 3.0, interface files were reorganized to more closely
	match "Inside Macintosh" reference books and be more consistant
	from language to language.
	
	Interfaces for the basic type definitions are now found in Types.p.
	This file, which includes Types.p, is provided for compatibility
	with old sources.

	Pascal Interface to the Macintosh Libraries
	Copyright Apple Computer, Inc. 1988
	All Rights Reserved
}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT MemTypes;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingMemTypes}
{$SETC UsingMemTypes := 1}

{$I+}
{$SETC MemTypesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := MemTypesIncludes}

{$ENDC}    { UsingMemTypes }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

