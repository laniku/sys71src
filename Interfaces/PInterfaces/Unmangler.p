{
Created: Wednesday, July 16, 1991 at 2:05 PM
    Unmangler.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc. 1988-1991
        All rights reserved
    This file is used in these builds: ROM System

	Change History (most recent first):

		 <2>	  8/8/91	JL		Standardized header and Inclusion conditionals. Updated
									copyright

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT Unmangler;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingUnmangler}
{$SETC UsingUnmangler := 1}

{$I+}
{$SETC UnmanglerIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := UnmanglerIncludes}

		(*
		FUNCTION unmangle(dst: UNIV Ptr; src: UNIV Ptr; limit: LongInt): LongInt; C;
			{This function unmangles C++ mangled symbols (i.e. a symbol with a type signature).
			 The mangled C string is passed in ÒsrcÓ and the unmangled C string is returned in
			 ÒdstÓ.  Up to ÒlimitÓ characters (not including terminating null) may be retured
			 in ÒdstÓ.
		 
			 The function returns,
		 
				 -1 ==> error, probably because symbol was not mangled, but looked like it was
					0 ==> symbol wasn't mangled; not copied either
					1 ==> symbol was mangled; unmangled result fit in buffer
					2 ==> symbol was mangled; unmangled result truncated to fit in buffer}
		*)
		
		FUNCTION Unmangle(dst: UNIV StringPtr; src: UNIV StringPtr; limit: LongInt): LongInt;
			{This function unmangles C++ mangled symbols (i.e. a symbol with a type signature).
			 The mangled Pascal string is passed in ÒsrcÓ and the unmangled Pascal string is
			 returned in ÒdstÓ.  Up to ÒlimitÓ characters may be retured in ÒdstÓ.
			
			 The function returns,
			 
				 -1 ==> error, probably because symbol was not mangled, but looked like it was
					0 ==> symbol wasn't mangled; not copied either
					1 ==> symbol was mangled; unmangled result fit in buffer
					2 ==> symbol was mangled; unmangled result truncated to fit in buffer
					 
			 This function is identical to unmangle() above except that all the strings are
			 Pascal instead of C strings.
			}


{$ENDC}    { UsingUnmangler }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

