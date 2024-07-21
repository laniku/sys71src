
{
Created: Monday, January 22, 1990 at 9:18 PM
	PasLibIntf.p
	Pascal Interface to the Macintosh Libraries

	Copyright Apple Computer, Inc.	1986-1991
	All rights reserved
    This file is used in these builds: ROM System

	
	
	Interface to the Pascal I/O and Memory Manager Library.
	Built-in procedure and function declarations are marked with
	the (* *) comment characters
	
			
				Change History (most recent first):
			
		 <4>	  8/8/91	JL		Try again.
		 <3>	  8/8/91	JL		Update copyright. Standardized header.
		 <2>	 3/13/91	JL		Checked in MPW version.  Changed Including MemTypes to Types.
			
				To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT PASLIBIntf;
  	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPASLIBINTF}
{$SETC UsingPASLIBINTF := 1}

{$I+}
{$SETC PASLIBINTFIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := PASLIBINTFIncludes}

	TYPE
	  PASCALPOINTER = ^INTEGER; { Universal POINTER type }
	  PASCALFILE = FILE; { Universal FILE type }
(*
 *	  PASCALBLOCK =    { Universal block of chars }
 *			PACKED ARRAY [0..511] OF CHAR;
 *)

	CONST
	  { <StdIO.h> PLSetVBuf styles }
	  _IOFBF = $00; { File buffering }
	  _IOLBF = $40; { Line buffering }
	  _IONBF = $04; { No buffering }

{
 Mac Pascal heap management
}

	PROCEDURE PLHeapInit(sizepheap: LONGINT; heapDelta: LONGINT;
						 memerrProc: UNIV PASCALPOINTER; allowNonCont: BOOLEAN;
						 forDispose: BOOLEAN);
{
 The following procedure is obsolete, use PLHeapInit
}

	PROCEDURE PLInitHeap(sizepheap: LONGINT; memerrProc: UNIV PASCALPOINTER;
						 allowNonCont: BOOLEAN; allowDispose: BOOLEAN);

	PROCEDURE PLSetNonCont(allowNonCont: BOOLEAN);

	PROCEDURE PLSetMErrProc(memerrProc: UNIV PASCALPOINTER);

	PROCEDURE PLSetHeapType(forDispose: BOOLEAN);

	PROCEDURE PLSetHeapCheck(DoIt: BOOLEAN);

{
 File I/O
}

(*
 *	  PROCEDURE
 *		RESET(VAR fvar:  UNIV PASCALFILE; OPT fname: STRING);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		REWRITE(VAR fvar: UNIV PASCALFILE; OPT fname: STRING);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		OPEN(VAR fvar:	UNIV PASCALFILE; fname: STRING);
 *		BUILTIN;
 *)

	PROCEDURE PLSetVBuf(VAR fvar: TEXT; buffer: UNIV PASCALPOINTER;
						style: INTEGER; bufsize: INTEGER);
(*
 *	  FUNCTION
 *		BLOCKREAD(
 *		  VAR fvar: FILE;
 *		  VAR buffer: UNIV PASCALBLOCK;
 *		  nBlocks: INTEGER;
 *		  OPT stBlock:INTEGER
 *		):
 *		INTEGER;
 *		BUILTIN;
 *
 *	  FUNCTION
 *		BLOCKWRITE(
 *		  VAR fvar: FILE;
 *		  VAR buffer: UNIV PASCALBLOCK;
 *		  nBlocks: INTEGER;
 *		  OPT stBlock:INTEGER
 *		):
 *		INTEGER;
 *		BUILTIN;
 *
 *	  FUNCTION
 *		BYTEREAD(
 *		  VAR fvar: FILE;
 *		  VAR buffer: UNIV PASCALBLOCK;
 *		  nBytes:  LONGINT;
 *		  OPT stByte: LONGINT
 *		):
 *		LONGINT;
 *		BUILTIN;
 *
 *	  FUNCTION
 *		BYTEWRITE(
 *		  VAR fvar: FILE;
 *		  VAR buffer: UNIV PASCALBLOCK;
 *		  nBytes:  LONGINT;
 *		  OPT stByte: LONGINT
 *		):
 *		LONGINT;
 *		BUILTIN;
 *
 *	  FUNCTION
 *		EOF(OPT VAR fvar: UNIV PASCALFILE):
 *		BOOLEAN;
 *		BUILTIN;
 *
 *	  FUNCTION
 *		EOLN(OPT VAR fvar: TEXT):
 *		BOOLEAN;
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		READ(VAR fvar: TEXT; OPT EXPR_LIST);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		READLN(OPT VAR fvar: TEXT; OPT EXPR_LIST);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		WRITE(VAR fvar: TEXT; OPT EXPR_LIST);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		WRITELN(OPT VAR fvar: TEXT; OPT EXPR_LIST);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		GET(VAR fvar: UNIV PASCALFILE);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		PUT(VAR fvar: UNIV PASCALFILE);
 *		BUILTIN;
 *
 *	  PROCEDURE
 *		SEEK(VAR fvar: UNIV PASCALFILE; recno: LONGINT);
 *		BUILTIN;
 *)

	FUNCTION PLFilePos(VAR fvar: UNIV PASCALFILE): LONGINT;

	PROCEDURE PLFlush(VAR fvar: TEXT);

	PROCEDURE PLCrunch(VAR fvar: UNIV PASCALFILE);
{
 Directory operations.
}

	PROCEDURE PLPurge(fname: STRING);

	PROCEDURE PLRename(oldFname, newFname: STRING);

{
 C string functions for Pascal strings
}
 	FUNCTION PLStrCmp(string1, string2: STR255): INTEGER;

	FUNCTION PLStrnCmp(string1, string2: STR255; n: INTEGER): INTEGER;

	FUNCTION PLStrCpy(VAR string1: STR255; string2: STR255): STRINGPTR;

	FUNCTION PLStrnCpy(VAR string1: STR255; string2: STR255; n: INTEGER): STRINGPTR;

	FUNCTION PLStrCat(VAR string1: STR255; string2: STR255): STRINGPTR;

	FUNCTION PLStrnCat(VAR string1: STR255; string2: STR255; n: INTEGER): STRINGPTR;

	FUNCTION PLStrChr(string1: STR255; c: CHAR): PTR;

	FUNCTION PLStrrChr(string1: STR255; c: CHAR): PTR;

	FUNCTION PLStrPBrk(string1, string2: STR255): PTR;

	FUNCTION PLStrSpn(string1, string2: STR255): INTEGER;

	FUNCTION PLStrStr(string1, string2: STR255): PTR;

	FUNCTION PLStrLen(string1: STR255): INTEGER;
	
	FUNCTION PLPos(STRING1: STR255; STRING2: STR255): INTEGER;

{$ENDC}    { UsingPASLIBINTF }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}
