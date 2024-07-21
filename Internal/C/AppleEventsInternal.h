/*
	File:		AppleEventsInternal.h

	Contains:	Types and structs for receiving the standard six AppleEvents.

	Written by:	Nick Kledzik

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <5>	 8/27/91	JSM		Cleanup header.
		 <4>	  2/5/91	Lai		include addtional constants used internally by the AppleEvents
									manager
		 <3>	  2/1/91	DFH		stb,WS#DFH-910131c:Moved Process Mgr defined codes here, since
									AppleEvent manager has new names for them , and we don't want to
									break any compiles at this point.
		 <2>	  2/1/91	DFH		BAC,WS#DFH-910131c:Replaced aeErrorValueKeyword ('errv') with
									aeErrorNumberKeyword ('errn').
		 <1>	  9/5/90	ngk		first checked in

		 <0>	  9/05/90	ngk		Moved from {CIncludes}AppleEvents.h to here
		---------------------------------------------------------------------------
		<11>	DFH	16 Apr 90		Changed saeOpenDocumentMsgID to 'odoc', saePrintDocumentMsgID
									to 'pdoc'.  Added saeLaunchedWithoutDocs, saeAnswer,
									aeErrorValueKeyword, and AppleEventReply.
		<10>	ngk 4/2/90			Renamed class field in HighLevelEventRecord
		 <9>	DFH	23 Mar 90		Corrected the majorVersion to be a short, as per ERS.
		 <8>	ngk	3/22/90			Changed AETFDescriptor AETFParameter in regular expr.
		 <7>	ngk	3/20/90			Change to new 7.0a8 format for message buffers. Removed
									constants and structs for non-standard appleevents
		 <6>	DFH	12 Mar 90		Added AppleEventMessage
		 <5>	DFH	12 Mar 90		Removed aeDebuggerNotify
		1.1		ngk 12/01/1989		Renamed aeUnexpectedQuit to aeApplicationDied, and
									refcon to amsRefCon
		1.0		ngk 11/01/1989		initial EASE release
*/


#ifndef __APPLEEVENTSINTERNAL__
#define __APPLEEVENTSINTERNAL__

#ifndef __TYPES__
#include <Types.h>
#endif

typedef unsigned long	MsgClass;
typedef unsigned long	MsgID;
typedef unsigned long	KeyWord;
typedef unsigned long	ParamType;


/* this template is used to extract the MsgClass and MsgID */
/* fields from a highlevel event */
struct HighLevelEventRecord {
	short		what;				/* always kHighLevelEvent */
	MsgClass	mClass;			
	long 		reserved1;			
	MsgID		mID;			
	short		reserved2;			
	};
#ifndef __cplusplus
typedef struct HighLevelEventRecord		HighLevelEventRecord;
#endif

/* Codes from AppleEvents.h under the names they were supposed remain, but didn't */
#define standardAppleEventMsgClass		'aevt'		/* kCoreEventClass */
#define	saeLaunchedWithoutDocs			'oapp'		/* kAEOpenApplication */
#define saeOpenDocumentMsgID			'odoc'		/* kAEOpenDocuments */
#define saePrintDocumentMsgID			'pdoc'		/* kAEPrintDocuments */
#define saeQuitMsgID					'quit'		/* kAEQuitApplication */
#define	saeAnswer						'ansr'		/* kAEAnswer */
#define aeCreatorType					'crea'		/* kAECreatorType */
#define aeQuitAll						'quia'		/* kAEQuitAll */
#define aeShutDown						'shut'		/* kAEShutDown */
#define aeRestart						'rest'		/* kAERestart */
#define aeApplicationDied				'obit'		/* kAEApplicationDied */
#define aeProcessKeyword				'psn '		/* keyProcessSerialNumber */
#define aeProcessParamType				'psn '		/* typeProcessSerialNumber */
#define aeDirectObjectKeyword			'----'		/* keyDirectObject */
#define	aeErrorNumberKeyword			'errn'		/* keyErrorNumber */
#define aeListParamType 				'list'		/* typeAEList */
#define aeAliasParamType	 			'alis'		/* typeAlias */
#define aeLongintParamType				'long'		/* typeLongInteger */
#define aeIntegerParamType				'long'		/* typeInteger */
#define aeTextParamType					'TEXT'		/* typeChar */
#define aeBooleanParamType				'bool'		/* typeBoolean */
#define aeTrueParamType					'true'		/* typeTrue */
#define aeFalseParamType				'fals'		/* typeFalse */
#define aeEnumerateParamType			'enum'		/* typeEnumerated */

/* addition constants used by AppleEvent manager internally */

#define aeReplyRequestedKeyword			'repq'		/* the client wants a reply */
#define aeBeforeTimeKeyword				'befo'		/* do it before this time */

#define aeWaitLongerMSGID				'wait'		/* wait longer AppleEvent */
#define aeSwitchToFrontMSGID			'cans'		/* please switch to front */

/* enumerator used in the interactLevel */
#define aeNeverInteractEnum				'nevi'
#define aeCanInteractEnum				'cani'
#define aeCanSwitchIfInteractEnum		'cans'
#define aeAlwaysInteractEnum			'alwi'
#define aeAlwaysSwitchIfInteractEnum	'alws'

/* Codes we thought of in December 1989 that might be unused now (January 91) */
#define saeNewDocumentMsgID				'new '
#define saeSetUpMenusMsgID				'mens'
#define saeGetPropertyMsgID				'getp'
#define aeTemporaryIDParamType			'tid '
#define aePropertyParamType				'prop'

/*
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
 */


struct AETFHeader
{
	long	signature;		/* always 'aevt' */
	short	majorVersion; 	/* always 1 (for now) */		
	short	minorVersion; 	/* always 1 (for now) */
};
#ifndef __cplusplus
typedef struct AETFHeader	AETFHeader;
#endif
typedef AETFHeader	*AETFHeaderPtr;

#define 	aeEndOfMetaDataKeyword		';;;;'

/* A Descriptor is chunk of data that has a type and length. */
struct AETFDescriptor
{
	ParamType	dataType;
	long		dataLength; 		
	/* char[]	data;  start of actual data */
};
#ifndef __cplusplus
typedef struct AETFDescriptor	AETFDescriptor;
#endif
typedef AETFDescriptor	*AETFDescriptorPtr;

/* A Parameter is a Keyword and Descriptor. */
struct AETFParameter
{
	KeyWord				key;
	AETFDescriptor		descriptor; 		
};
#ifndef __cplusplus
typedef struct AETFParameter	AETFParameter;
#endif
typedef AETFParameter	*AETFParameterPtr;

/* Standard reply message */
typedef struct AppleEventReply {
	AETFHeader		messageHeader;		/* == saeAnswer */
	KeyWord			metaDataMark;
	AETFParameter	errorCodeHdr;		/* == aeErrorNumberKeyword, aeLongintParamType */
	long			errorValue;			/* sign-extended OSErr */
} AppleEventReply;
	
	
#endif /* __APPLEEVENTSINTERNAL__ */
