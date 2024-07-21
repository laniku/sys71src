{
	File:		StandardFilePriv.p

	Contains:	definitions needed to use Standard File's LDEF or other resources

	Written by:	Nick Kledzik

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 10/1/91	JSM		first checked in
		 <0>	 10/1/91	JSM		Created from StandardFile3Priv.p.

	Modification history from StandardFile3Priv.p below:

		 <5>	  8/8/90	ngk		update to match StandardFIle3Priv.a
		 <4>	  6/6/90	ngk		Moved generic icon ID definitions to IconUtilsPriv
		 <3>	 4/10/90	ngk		some resources have new IDs
		 <2>	 2/25/90	ngk		Fix comments
		 <1>	 2/25/90	ngk		first checked in

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT StandardFilePriv;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingStandardFilePriv}
{$SETC UsingStandardFilePriv := 1}

{$I+}
{$SETC StandardFilePrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := StandardFilePrivIncludes}

CONST
	sfLDEFresourceID	= -4000;
	
	{ standard strings in STR# }
	rStandardFileStringsID		= 	-6046;
	sfDesktopName		=	1;
	sfTrashName			=	2;
	sfOpenName			=	3;
	sfErrDiskLocked		= 	4;
	sfErrNoPrivileges	=	5;
	sfErrBadFilename	=	6;
	sfErrSystemError	=	7;
	sfErrBadAlias	 	=	8;
	sfErrSaveOnFolder	=	9;
	sfFolderNameExists	=	10;
	

TYPE
	SFListCellData	=	RECORD
							cdUserBytes:	ARRAY[1..8] OF INTEGER;
							cdIconID:		INTEGER;	{ resource ID of SICN }
							cdIconLeft:		BOOLEAN;	{ normally TRUE }
							cdJust:			SignedByte; { normally teJustLeft }
							cdScript:		ScriptCode; 	
							cdFont:			INTEGER;	
							cdDimmed:		BOOLEAN;	{ if true then dim cell }
							cdStyle:		Style;
							cdSize:			INTEGER;
							cdText:			Str63;
						END;

{$ENDC}    { UsingStandardFilePriv }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

