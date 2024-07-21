{
	File:		TerminalToolsPriv.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/14/90	BBH		first checked in

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT TerminalToolsPriv;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED TerminalToolsPriv}
{$SETC TerminalToolsPriv := 1}


CONST
{	Private Terminal Tool Messages			}
	tmPeekLineMsg		=	200;
	
TYPE

	LineInfoH			=	^LineInfoPtr;
	LineInfoPtr			=	^LineInfoRec;
	LineInfoRec			= 	RECORD
		linePtr			:	Ptr;
		lineSize		:	INTEGER;
		attrPtr			:	Ptr;
		attrSize		:	INTEGER;
		lineAttrPtr		:	Ptr;
		lineAttrSize	:	INTEGER;
	END;
	
{$ENDC}    { TerminalToolsPriv }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}


