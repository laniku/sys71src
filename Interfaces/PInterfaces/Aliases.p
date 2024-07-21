
{
Created: Saturday, July 27, 1991 at 7:46 PM
 Aliases.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
    This file is used in these builds: BigBang


	Change History (most recent first):

		<18>	 7/30/91	JL		Updated Copyright.
		<17>	  2/4/91	JL		changed fullpath to fullPath; changed spelling capitalization.
		<16>	  1/28/91	JAL		(MH)kARMmountVol etc. are now explicitly 32 bit constants (8 hex digits)
									Checked in Database generated file.
		<15>	  1/7/91	JDR		(dba) NewAliasMinimalFromFullpath had its case incorrect and is
									now NewAliasMinimalFromFullPath to match the .h interface. Also
									corrected the case for fullPathLength and fullPath.
		<14>	11/29/90	PP		(PP/ich) Fix a typo in Filter proc comment.
		<13>	  8/6/90	PP		zoneName in MinimalFullpathAlias is Str32 and not Str31.
		<12>	  7/2/90	PP		Add ResolveAliasFile.
		<11>	 6/20/90	ngk		Removed CanonicalFileSpec and replaced it with FSSpec.
	   								Added type def for AliasFilterProcPtr.  Changed 
									yourDataPtr type to UNIV Ptr.
		<10>	 6/15/90	PP		Remove SelectAlias.
		 <9>	 4/10/90	PP		Add kARMnoUI bit for rules mask.
		 <8>	  4/7/90	ngk		Change fromFile back to an CanonicalFileSpecPtr, since it can be
									NIL.
		 <7>	  4/5/90	PP		Add kARMsearchRelFirst to MatchAlias rulesMask. Rename
									"callbackPtr" to "yourDataPtr".
		 <6>	 3/20/90	PP		Add interfaces for minimal alias support.  userType in alias
									record is OSType and not ResType.
		 <3>	 1/26/90	ngk		Changed CanonicalFileSpecPtr to CanonicalFileSpec in NewAlias
		 <2>	  1/7/90	ngk		Fix comments
		 <1>	  1/7/90	ngk		Renamed from Alias.p to Aliases.p
	   <1.9>	12/15/89	prp		Fix parameter variable names.
	   <1.8>	 10/2/89	prp		Added 'GetAliasInfo' routine.
	   <1.7>	 9/18/89	ngk		removed old API definitions.
	   <1.6>	 9/18/89	prp		SelectAlias, MatchAlias and UpdateAlias has API changes with
									additional parameters.
	   <1.5>	  9/6/89	prp		Added DisposeAlias back until DPMgr is in sync.
	   <1.4>	  9/6/89	prp		Changes from CodeReview.
	   <1.3>	  8/7/89	prp		Added SelectAlias routine as an external interface.
	   <1.2>	 6/12/89	prp		Took out emphasize relative path rules bit.
	   <1.1>	  6/8/89	prp		Alias Manager Trap # changed from $A825 to $A823
	   <1.0>	 5/30/89	ngk		Submitted for first time
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Aliases;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingAliases}
{$SETC UsingAliases := 1}

{$I+}
{$SETC AliasesIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingDialogs}
{$I $$Shell(PInterfaces)Dialogs.p}
{$ENDC}
{$IFC UNDEFINED UsingAppleTalk}
{$I $$Shell(PInterfaces)AppleTalk.p}
{$ENDC}
{$IFC UNDEFINED UsingFiles}
{$I $$Shell(PInterfaces)Files.p}
{$ENDC}
{$SETC UsingIncludes := AliasesIncludes}

CONST
rAliasType = 'alis';				{ Aliases are stored as resources of this type }

{ define alias resolution action rules mask }
kARMMountVol = $00000001;			{ mount the volume automatically }
kARMNoUI = $00000002;				{ no user interface allowed during resolution }
kARMMultVols = $00000008;			{ search on multiple volumes }
kARMSearch = $00000100;				{ search quickly }
kARMSearchMore = $00000200;			{ search further }
kARMSearchRelFirst = $00000400;		{ search target on a relative path first }

{ define alias record information types }
asiZoneName = -3;					{ get zone name }
asiServerName = -2;					{ get server name }
asiVolumeName = -1;					{ get volume name }
asiAliasName = 0;					{ get aliased file/folder/volume name }
asiParentName = 1;					{ get parent folder name }


TYPE
{ define the alias record that will be the blackbox for the caller }
AliasPtr = ^AliasRecord;
AliasHandle = ^AliasPtr;
AliasRecord = RECORD
 userType: OSType;					{ appl stored type like creator type }
 aliasSize: INTEGER;				{ alias record size in bytes, for appl usage }
 END;


AliasInfoType = INTEGER;			{ alias record information type }
AliasFilterProcPtr = ProcPtr;


{  create a new alias between fromFile-target and return alias record handle  }
FUNCTION NewAlias(fromFile: FSSpecPtr;
                  target: FSSpec;
                  VAR alias: AliasHandle): OSErr;
 INLINE $7002,$A823;

{ create a minimal new alias for a target and return alias record handle }
FUNCTION NewAliasMinimal(target: FSSpec;
                         VAR alias: AliasHandle): OSErr;
 INLINE $7008,$A823;

{ create a minimal new alias from a target fullpath (optional zone and server name) and return alias record handle  }
FUNCTION NewAliasMinimalFromFullPath(fullPathLength: INTEGER;
                                     fullPath: Ptr;
                                     zoneName: Str32;
                                     serverName: Str31;
                                     VAR alias: AliasHandle): OSErr;
 INLINE $7009,$A823;

{ given an alias handle and fromFile, resolve the alias, update the alias record and return aliased filename and wasChanged flag. }
FUNCTION ResolveAlias(fromFile: FSSpecPtr;
                      alias: AliasHandle;
                      VAR target: FSSpec;
                      VAR wasChanged: BOOLEAN): OSErr;
 INLINE $7003,$A823;

{ given an alias handle and an index specifying requested alias information type, return the information from alias record as a string. }
FUNCTION GetAliasInfo(alias: AliasHandle;
                      index: AliasInfoType;
                      VAR theString: Str63): OSErr;
 INLINE $7007,$A823;

{  given a file spec, return target file spec if input file spec is an alias.
 It resolves the entire alias chain or one step of the chain.  It returns
 info about whether the target is a folder or file; and whether the input
 file spec was an alias or not.  }
FUNCTION ResolveAliasFile(VAR theSpec: FSSpec;
                          resolveAliasChains: BOOLEAN;
                          VAR targetIsFolder: BOOLEAN;
                          VAR wasAliased: BOOLEAN): OSErr;
 INLINE $700C,$A823;

{   Low Level Routines 
given an alias handle and fromFile, match the alias and return aliased filename(s) and needsUpdate flag }
FUNCTION MatchAlias(fromFile: FSSpecPtr;
                    rulesMask: LONGINT;
                    alias: AliasHandle;
                    VAR aliasCount: INTEGER;
                    aliasList: FSSpecArrayPtr;
                    VAR needsUpdate: BOOLEAN;
                    aliasFilter: AliasFilterProcPtr;
                    yourDataPtr: UNIV Ptr): OSErr;
 INLINE $7005,$A823;

{ given a fromFile-target pair and an alias handle, update the lias record pointed to by alias handle to represent target as the new alias. }
FUNCTION UpdateAlias(fromFile: FSSpecPtr;
                     target: FSSpec;
                     alias: AliasHandle;
                     VAR wasChanged: BOOLEAN): OSErr;
 INLINE $7006,$A823;


{$ENDC} { UsingAliases }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

