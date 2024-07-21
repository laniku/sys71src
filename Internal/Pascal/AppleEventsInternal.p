{
	File:		AppleEventsInternal.p

	Contains:	Types and Records for using standard six AppleEvents.

	Written by:	Nick Kledzik

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	  2/1/91	DFH		stb,WS#DFH-910131c:Added Process Mgr defined AppleEvent codes
									under their old names (for compatibility for now).
		 <3>	  2/1/91	DFH		BAC,WS#DFH-910131c:Replaced aeErrorValueKeyword ('errv') with
									aeErrorNumberKeyword ('errn').
		 <2>	  9/5/90	ngk		Fix auto-include name
		 <1>	  9/5/90	ngk		first checked in
		 <0>	  9/05/90	ngk 	moved from [PInterfaces]AppleEvents.p to here
		----------------------------------------------------
		<12>	DFH	16 Apr 90	Removed aeProcessParamType.
		<11>	DFH	16 Apr 90	Changed saeOpenDocumentMsgID to 'odoc', saePrintDocumentMsgID
								to 'pdoc'.  Added saeLaunchedWithoutDocs, saeAnswer,
								aeErrorValueKeyword, and AppleEventReply.
		<10>	ngk 3/22/90		Changed AETFDescriptor AETFParameter in regular expr.
		<9>		ngk 3/20/90		Changed PACKED ARRAY [0..3] to [1..4]
		<8>		ngk 3/20/90		fix comments
		<7>		ngk 3/20/90		Changed for 7.0a8 AppleEvents format
		<6>		DFH 12 Mar 90	Removed aeDebuggerNotify
		<5>		ngk 3/10/90		Big change for 7.0a8 AppleEvents format
		<3>		ngk 2/06/90		clean up standard header records
		
		1.1	ngk 12/01/1989		Renamed aeUnexpectedQuit to aeApplicationDied, and
								refcon to amsRefcon
		1.0	ngk 11/01/1989		initial EASE release

	To Do:
}
	

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}


{$IFC NOT UsingIncludes}
	UNIT AppleEventsInternal;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingAppleEventsInternal}
{$SETC UsingAppleEventsInternal := 1}

{$I+}
{$SETC AppleEventsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I Types.p}
{$ENDC}
{$SETC UsingIncludes := AppleEventsIncludes}

TYPE
    MsgClass    = PACKED ARRAY [1..4] OF CHAR;
    MsgID       = PACKED ARRAY [1..4] OF CHAR;
    KeyWord     = PACKED ARRAY [1..4] OF CHAR;
    ParamType 	= ResType; { superset of resources types and new ones }

	{ this template is used to extract the MsgClass and MsgID }
	{ fields from a highlevel event }
	HighLevelEventRecord =	RECORD
								what:		INTEGER;	{ always kHighLevelEvent }
								class:		MsgClass;
								reserved1:	LONGINT;
								ID:			MsgID;
								reserved2: 	INTEGER;
							END;

{ standard AppleEvent Message class and IDs }
CONST
	standardAppleEventMsgClass	=	'aevt';
	
	saeLaunchedWithoutDocs		=	'oapp'; { no direct object }
	saeNewDocumentMsgID			=	'new '; { no direct object }
	saeOpenDocumentMsgID		=	'odoc'; { direct object is file or list of files }
	saePrintDocumentMsgID		=	'pdoc'; { direct object is file or list of files }
	saeQuitMsgID				=	'quit'; { no direct object }
	saeSetUpMenusMsgID			=	'mens'; { no direct object }
	saeGetPropertyMsgID			=	'getp'; 
	saeAnswer					=	'ansr'; 
	aeCreatorType = 'crea';
	aeQuitAll = 'quia';
	aeShutDown = 'shut';
	aeRestart = 'rest';
	aeApplicationDied = 'obit';
	aeProcessKeyword = 'psn ';
	aeProcessParamType = 'psn ';



{ 
After receiving a high level event, you can get its message buffer by calling 
AcceptHighLevelEvent.  The format of the buffer as a regular expression is:

	AETFHeader (AETFParameter)* aeEndOfMetaDataKeyword (AETFParameter)*

The header tells you the protocol and version.  We recommend that everyone uses
the AppleEvent Transport Format (AETF) protocol.  Following the header is zero
or more "meta-parameters" (For the short term, you may ignore them).
Following them is an end of metaparameters keyword (';;;;') and then zero or 
more "regular parameters".  The most important regular parameter is
the "direct object".  It is distinguished by the keyword of '----'.  It is the
object of the message (e.g. which document to open).  

You will probably want to write a routine that can walk the parameters
and find a descriptor by keyword.

}


TYPE
	AETFHeaderPtr = ^AETFHeader;
	AETFHeader	  = RECORD
						signature:		LONGINT;	{ always 'aevt' }
						majorVersion:	INTEGER;	{ always 1 (for now) }
						minorVersion:	INTEGER;	{ always 1 (for now) }
					END;

	{ A Descriptor is chunk of data that has a type and length. }
	AETFDescriptorPtr = ^AETFDescriptor;
	AETFDescriptor = RECORD
						dataType:		ParamType;	
						dataLength:		LONGINT;	
						{data:			ARRAY [0..dataLength] OF Bytes;} { start of actual data }
					END;

	{ A Parameter is a Keyword and Descriptor. }
	AETFParameterPtr = ^AETFParameter;
	AETFParameter = RECORD
						key:			KeyWord;	
						descriptor:		AETFDescriptor;
					END;

{ standard keywords (used to distinguish Parameters) }
CONST	
	aeEndOfMetaDataKeyword		=	';;;;';
	aeDirectObjectKeyword		=	'----';
	aeErrorNumberKeyword		=	'errn';


{ standard parameter types }
CONST
	aeListParamType 			=	'list';
	aeAliasParamType	 		=	'alis';
	aeTemporaryIDParamType		=	'tid ';
	aeLongintParamType			=	'long';
	aeIntegerParamType			=	'shor';
	aeTextParamType				=	'TEXT';
	aeBooleanParamType			=	'bool';
	aeTrueParamType				=	'true';
	aeFalseParamType			=	'fals';
	aePropertyParamType			=	'prop';
	aeEnumerateParamType		=	'enum';
	

{ Standard reply message }
TYPE
	AppleEventReply	  = RECORD
						messageHeader:	AETFHeader;		{ == saeAnswer }
						metaDataMark:	KeyWord;
						errorCodeHdr:	AETFParameter;	{ == aeErrorNumberKeyword, aeLongintParamType }
						errorValue:		LONGINT;		{ sign-extended OSErr }
					END;
	

{$ENDC}    { UsingAppleEventsInternal }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}
