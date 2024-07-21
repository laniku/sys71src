{
	File:		IntlUtilsPriv.p

	Contains:	Private Pascal Interface for International utilities

	Written by:	Nick Kledzik

	Copyright:	© 1990, 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	 2/18/92	ngk		Add glue to fix bug in 7.0 version of TypeSelectNewKey. It
									requires high word of D0 to be zero to work.
		 <3>	 9/10/90	PKE		Add interface for private GetScriptItl routine.
		 <2>	  7/2/90	PKE		Added interfaces for private routines IUMagWString,
									IUMagWPString, IUTextOrderSys.
		 <1>	  5/2/90	ngk		first checked in

	To Do:
	
}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT IntlUtilsPriv;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingIntlUtilsPriv}
{$SETC UsingIntlUtilsPriv := 1}

{$I+}
{$SETC IntlUtilsPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingPackages}
{$I $$Shell(PInterfaces)Packages.p}
{$ENDC}
{$SETC UsingIncludes := IntlUtilsPrivIncludes}
	
	
CONST
	{ possible TSCode's }
	tsPreviousSelectMode	=	-1;
	tsNormalSelectMode		=	0;
	tsNextSelectMode		=	1;	

TYPE
	TypeSelectRecord = RECORD
							tsrLastKeyTime:	LONGINT;	
							tsrScript:		ScriptCode;
							tsrKeyStrokes:	Str63;
						END;
						
	TSCode = INTEGER;


   IndexToStringProcPtr = ProcPtr;  { FUNCTION(item: INTEGER; VAR itemsScript: ScriptCode;
									           VAR itemsStringPtr: StringPtr; yourDataPtr: Ptr): BOOLEAN; }
	


	PROCEDURE TypeSelectClear(VAR tsr: TypeSelectRecord);
    	INLINE $3F3C,$0028,$A9ED; 
	
	FUNCTION TypeSelectNewKey(theEvent: EventRecord;
							VAR tsr: TypeSelectRecord): BOOLEAN;
    	INLINE $7000, $3F3C,$002A,$A9ED; 
	
	
	FUNCTION TypeSelectFindItem(tsr: TypeSelectRecord;
								listSize: INTEGER;
								selectMode: TSCode;
								getStringProc: IndexToStringProcPtr; 
								yourDataPtr: UNIV Ptr): INTEGER;
    	INLINE $3F3C,$002C,$A9ED; 
	
	
	
	FUNCTION TypeSelectCompare(tsr: TypeSelectRecord; 
								testStringScript: ScriptCode;
								testStringPtr: StringPtr): INTEGER;
    	INLINE $3F3C,$002E,$A9ED; 
	
				
	FUNCTION IUMagWString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER): INTEGER;	{ <2> }
		INLINE $3F3C,$0012,$A9ED;
	
	FUNCTION IUMagWPString(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;			 	{ <2> }
		intlParam: Handle): INTEGER;
		INLINE $3F3C,$0026,$A9ED; 
	
	FUNCTION IUTextOrderSys(aPtr: Ptr;bPtr: Ptr;aLen: INTEGER;bLen: INTEGER;			{ <2> }
		aScript: ScriptCode;bScript: ScriptCode;aLang: LangCode;
		bLang: LangCode): INTEGER;
		INLINE $3F3C,$0030,$A9ED; 

	FUNCTION IUGetScriptItl(theID: INTEGER; script: ScriptCode;							{ <3> }
		sysFlag: INTEGER): Handle;
		INLINE $3F3C,$0032,$A9ED; 


{$ENDC}    { UsingIntlUtilsPriv }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

