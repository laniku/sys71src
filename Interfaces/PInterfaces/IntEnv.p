{
Created: Wednesday, June 27, 1990 at 6:42 PM
    IntEnv.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc. 1989-1991
        All rights reserved
    This file is used in these builds: ROM System

			
				Change History (most recent first):
			
		 <3>	  8/8/91	JL		Updated Copyright.
		 <2>	 3/13/91	JL		Checked in MPW version.
			
				To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT IntEnv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingIntEnv}
{$SETC UsingIntEnv := 1}

{$I+}
{$SETC IntEnvIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingPasLibIntf}
{$I $$Shell(PInterfaces)PasLibIntf.p}
{$ENDC}
{$SETC UsingIncludes := IntEnvIncludes}

	CONST

	  { CMD words for IEfaccess(), from <fcntl.h> }

	  F_OPEN = $6400; { (('d'<<8)|00), d => "directory" ops }
	  F_DELETE = $6401;
	  F_RENAME = $6402;

	  F_GTABINFO = $6500; { (('e'<<8)|00), e => "editor" ops }
	  F_STABINFO = $6501;
	  F_GFONTINFO = $6502;
	  F_SFONTINFO = $6503;
	  F_GPRINTREC = $6504;
	  F_SPRINTREC = $6505;
	  F_GSELINFO = $6506;
	  F_SSELINFO = $6507;
	  F_GWININFO = $6508;
	  F_SWININFO = $6509;
	  F_GSCROLLINFO = $6510;
	  F_SSCROLLINFO = $6511;

	  { Open modes for IEopen(), from <fcntl.h> }

	  O_RDONLY = $0000;
	  O_WRONLY = $0001;
	  O_RDWR = $0002;
	  O_APPEND = $0008;
	  O_RSRC = $0010;
	  O_CREAT = $0100;
	  O_TRUNC = $0200;
	  O_EXCL = $0400;

	  { IOCtl parameters }

	  FIOINTERACTIVE = $6602; { (('f'<<8)|02), f => "open file" ops }
	  FIOBUFSIZE = $6603;
	  FIOFNAME = $6604;
	  FIOREFNUM = $6605;
	  FIOSETEOF = $6606;

	TYPE
	  IEString = STRING;
	  IEStringPtr = ^IEString;
	  IEStringVec = ARRAY [0..8191] OF IEStringPtr;
	  IEStringVecPtr = ^IEStringVec;

	  {$PUSH}
	  {$J+} { EXPORTed unit globals }

	VAR
	  ArgC: LONGINT;
	  ArgV: IEStringVecPtr;
	  _EnvP: IEStringVecPtr;

	  Diagnostic: TEXT;
	  {$POP}

	FUNCTION IEStandAlone: BOOLEAN;

	FUNCTION IEgetenv(envName: STRING; VAR envValue: UNIV IEString): BOOLEAN;

	FUNCTION IEfaccess(fName: STRING; opCode: LONGINT;
					   arg: UNIV LONGINT): LONGINT;

	PROCEDURE IEopen(VAR fvar: UNIV PASCALFILE; fName: STRING; mode: LONGINT);

	FUNCTION IEioctl(VAR fvar: UNIV PASCALFILE; request: LONGINT;
					 arg: UNIV LONGINT): LONGINT;

	FUNCTION IElseek(VAR fvar: UNIV PASCALFILE; offset: LONGINT;
					 whence: LONGINT): LONGINT;

	PROCEDURE IEatexit(exitProc: UNIV LONGINT);
	  C;

	PROCEDURE IEexit(status: LONGINT);
	  C;

	PROCEDURE IE_exit(status: LONGINT);
	  C;

{$ENDC}    { UsingIntEnv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

