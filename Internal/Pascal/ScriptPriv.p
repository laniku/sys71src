{
	File:		ScriptPriv.p

	Contains:	Private Pascal definitions for Script Mgr (these assume System 7.0).

	Written by:	Kevin S. MacDonell

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	 8/28/91	JSM		Cleanup header.
		 <3>	12/14/90	SMB		(csd) I forgot the approval signature for the previous change.
		 <2>	12/14/90	SMB		Moving KeyScript verb, smKeyModalDialog, here and renaming it
									smKeyDisableAboutKybds. Also adding new KeyScript verb
									smKeyEnableAboutKybds.
		 <1>	 7/31/90	KSM		first checked in
		 <0>	 7/25/90	KSM		New Today.

}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT ScriptPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingScriptPriv}
{$SETC UsingScriptPriv := 1}

{$I+}
{$SETC ScriptPrivIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}

{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}

{$SETC UsingIncludes := ScriptPrivIncludes}

	CONST
	{ Moved these KeyScript verbs here since adding smKeyEnableAboutKybds after the 7.0 interfaces have
  	 frozen. (and we also don't believe a developer will ever want them!)									<13>
	}
		smKeyDisableAboutKybds = -13;		{ Disable ‘About…’ menu item since another dialog is up	}	{<2>}
		smKeyEnableAboutKybds = -14;		{ Enable ‘About…’ menu item	}								{<2>}


	FUNCTION IsCmdChar(keyEvent: EventRecord; test: CHAR): BOOLEAN;
		INLINE $2F3C, $8206, $FFD0, $A8B5;

 {$ENDC}    { UsingScriptPriv }


{$IFC NOT UsingIncludes}
    END.
{$ENDC}

