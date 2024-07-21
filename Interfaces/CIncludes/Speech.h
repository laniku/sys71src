/*
	File:		Speech.h

	Contains:	Interfaces to Speech Manager

	Written by:	Tim Schaaff

	Copyright:	© 1991-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	  8/4/93	JDR		synch with Reality and Sound Mgr.
		<12>	 6/22/93	DTY		Fix ProcPtrs again.
	   <10+>	 6/18/93	MC		
		<10>	 6/15/93	JDR		fix comment
		 <9>	 6/15/93	JDR		All errors belong in Error.h. Moved Speech Manager errors back
									to where they belong. Moved Gestalt info into GestaltEqu as well.
		 <8>	 6/15/93	JDR		Corrected DTY errors in typedefs.
		 <7>	 6/10/93	DTY		Add #pragma procnames for ProcPtr typedefs.
		 <6>	 6/10/93	DTY		Make struct definitions Interfacer studly.
		 <9>	 6/2/93		MC		Moved error codes back.
		 <8>	 3/10/93	JDR		moved error codes into Errors
		 <7>	 3/10/93	JDR		moved to {CIncludes}
		 <6>	 1/14/93	TIM		Rename badPhonemeText error return to badInputText.
		 <5>	11/30/92	TIM		Renamed callback function typedefs to fix name-space conflicts
									between Speech Mgr and Quicktime Movies.h and to make them more
									Speech Mgr specific.
		 <4>	10/28/92	TIM		Put badPhonemeText error code back into API.
		 <3>	 9/15/92	TIM		Removed badStructLen, unimplMsg, badSelector, badParmVal error
									return. Added “voiceNotFound” error return. Added length param
									to GetVoiceDescription. Prefixed some constants with “k” to
									conform to Apple naming conventions.
		 <2>	 7/23/92	TIM		Switch resource and file type defines over to the “official”
									ones from Brian McGhie.
		 <1>	 7/6/92		TIM		Add support for Voice management routines
		 <0>	 6/24/92	TIM		Bring interfaces up to date with 1.0a7 spec
		<-1>	 4/21/92	TIM		Bring interfaces up to date with 1.0a5 spec
		<-2>	 2/13/92	TIM		Bring interfaces up to date with 1.0a3 spec
		<-3>	11/19/91	TIM		Pass voice Handle argument to ReadNthVoice and ReadNamedVoice by
									reference
		<-4>	11/14/91	TIM		Flesh out more of the API
		<-5>	11/11/91	TIM		Bring interfaces up to date with ERS
		<-6>	 11/6/91	TIM		first checked in

*/

#ifndef _SPEECH_
#define _SPEECH_

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif


#define kTextToSpeechSynthType		 'ttsc'	/* Text-to-Speech Synthesizer component type 	*/
#define kTextToSpeechVoiceType		 'ttvd'	/* Text-to-Speech Voice resource type 			*/
#define kTextToSpeechVoiceFileType	 'ttvf'	/* Text-to-Speech Voice file type 				*/
#define kTextToSpeechVoiceBundleType 'ttvb'	/* Text-to-Speech Voice Bundle file type		*/

enum {										/* constants for SpeakBuffer and TextDone callback controlFlags bits */
	kNoEndingProsody 	= 1,
	kNoSpeechInterrupt 	= 2,
	kPreflightThenPause	= 4
};

enum {										/* constants for StopSpeechAt and PauseSpeechAt */
	kImmediate		= 0,
	kEndOfWord		= 1,
	kEndOfSentence	= 2
};

#define soStatus				'stat'		/* GetSpeechInfo & SetSpeechInfo selectors */
#define soErrors				'erro'
#define soInputMode				'inpt'
#define soCharacterMode			'char'
#define soNumberMode			'nmbr'
#define soRate					'rate'
#define soPitchBase				'pbas'
#define soPitchMod				'pmod'
#define soVolume				'volm'
#define soSynthType				'vers'
#define soRecentSync			'sync'
#define soPhonemeSymbols		'phsy'
#define soCurrentVoice			'cvox'
#define soCommandDelimiter		'dlim'
#define soReset					'rset'
#define soCurrentA5				'myA5'
#define soRefCon				'refc'
#define soTextDoneCallBack		'tdcb'
#define soSpeechDoneCallBack	'sdcb'
#define soSyncCallBack			'sycb'
#define soErrorCallBack			'ercb'
#define soPhonemeCallBack		'phcb'
#define soWordCallBack			'wdcb'
#define soSynthExtension		'xtnd'
#define soSndInit				'sndi'



/* Speaking Mode Constants */

#define modeText		'TEXT'		/* input mode constants 				*/
#define modePhonemes	'PHON'
#define modeNormal		'NORM'		/* character mode and number mode constants */
#define modeLiteral		'LTRL'

enum {								/* GetVoiceInfo selectors 				*/
	soVoiceDescription	= 'info',	/* gets basic voice info 				*/
	soVoiceFile			= 'fref'	/* gets voice file ref info 			*/
};

struct SpeechChannelRecord {
	long data[1];
};
typedef struct SpeechChannelRecord SpeechChannelRecord;

typedef SpeechChannelRecord *SpeechChannel;

struct VoiceSpec {
	OSType	creator;				/* creator id of required synthesizer 	*/
	OSType	id;						/* voice id on the specified synth 		*/
};
typedef struct VoiceSpec VoiceSpec;

enum {kNeuter = 0, kMale, kFemale};	/* returned in gender field below 		*/

struct VoiceDescription {
	long		length;				/* size of structure - set by application 	*/
	VoiceSpec 	voice;				/* voice creator and id info 				*/
	long		version;			/* version code for voice 					*/
	Str63		name;				/* name of voice 							*/
	Str255		comment;			/* additional text info about voice 		*/
	short		gender;				/* neuter, male, or female					*/
	short		age;				/* approximate age in years 				*/
	short		script;				/* script code of text voice can process 	*/
	short		language;			/* language code of voice output speech 	*/
	short 		region;				/* region code of voice output speech 		*/
	long		reserved[4];		/* always zero - reserved for future use	*/
};
typedef struct VoiceDescription VoiceDescription;

struct VoiceFileInfo {
	FSSpec		fileSpec;			/* volume, dir, & name information for voice file */
	short		resID;				/* resource id of voice in the file */
};
typedef struct VoiceFileInfo VoiceFileInfo;

struct SpeechStatusInfo {
	Boolean	outputBusy; 			/* TRUE if audio is playing 		*/
	Boolean	outputPaused;			/* TRUE if channel is paused 		*/
	long	inputBytesLeft; 		/* bytes left to process 			*/
	short	phonemeCode;			/* opcode for cur phoneme 			*/
};
typedef struct SpeechStatusInfo SpeechStatusInfo;

struct SpeechErrorInfo {
	short	count;					/* # of errs since last check 		*/
	OSErr	oldest;					/* oldest unread error 				*/
	long	oldPos;					/* char position of oldest err 		*/
	OSErr	newest;					/* most recent error 				*/
	long	newPos;					/* char position of newest err 		*/
};
typedef struct SpeechErrorInfo SpeechErrorInfo;

struct SpeechVersionInfo {
	OSType		synthType;			/* always ‘ttsc’ 					*/
	OSType		synthSubType;		/* synth flavor 					*/
	OSType		synthManufacturer;	/* synth creator ID 				*/
	long		synthFlags;			/* synth feature flags 				*/
	NumVersion	synthVersion; 		/* synth version number 			*/
};
typedef struct SpeechVersionInfo SpeechVersionInfo;

struct PhonemeInfo {
	short	opcode;					/* opcode for the phoneme 			*/
	Str15	phStr;					/* corresponding char string 		*/
	Str31	exampleStr;				/* word that shows use of phoneme 	*/
	short	hiliteStart;			/* segment of example word that	 	*/
	short	hiliteEnd;				/* should be hilighted (ala TextEdit) */
};
typedef struct PhonemeInfo PhonemeInfo;

struct PhonemeDescriptor {
	short		phonemeCount; 		/* # of elements 		*/
	PhonemeInfo	thePhonemes[1]; 	/* element list 		*/
};
typedef struct PhonemeDescriptor PhonemeDescriptor;

struct SpeechXtndData {
	OSType	synthCreator;			/* synth creator id 	*/
	Byte	synthData[2];			/* data TBD by synth 	*/
};
typedef struct SpeechXtndData SpeechXtndData;

struct DelimiterInfo {
	Byte	startDelimiter[2];		/* defaults to “[[“ 	*/
	Byte	endDelimiter[2];		/* defaults to “]]“ 	*/
};
typedef struct DelimiterInfo DelimiterInfo;

/* Text-done callback routine typedef */
#pragma procname SpeechTextDone
typedef pascal void (*SpeechTextDoneProcPtr) (SpeechChannel, long, Ptr *, long *, long *);
typedef SpeechTextDoneProcPtr SpeechTextDoneCBPtr;

/* Speech-done callback routine typedef */
#pragma procname SpeechDone
typedef pascal void (*SpeechDoneProcPtr) (SpeechChannel, long );
typedef SpeechDoneProcPtr SpeechDoneCBPtr;

/* Sync callback routine typedef */
#pragma procname SpeechSync
typedef pascal void (*SpeechSyncProcPtr) (SpeechChannel, long, OSType);
typedef SpeechSyncProcPtr SpeechSyncCBPtr;

/* Error callback routine typedef */
#pragma procname SpeechError
typedef pascal void (*SpeechErrorProcPtr) (SpeechChannel, long, OSErr, long);
typedef SpeechErrorProcPtr SpeechErrorCBPtr;

/* Phoneme callback routine typedef */
#pragma procname SpeechPhoneme
typedef pascal void (*SpeechPhonemeProcPtr) (SpeechChannel, long, short);
typedef SpeechPhonemeProcPtr SpeechPhonemeCBPtr;

/* Word callback routine typedef */
#pragma procname SpeechWord
typedef pascal void (*SpeechWordProcPtr) (SpeechChannel, long, long, short);
typedef SpeechWordProcPtr SpeechWordCBPtr;

#ifdef __cplusplus
extern "C" {
#endif

pascal NumVersion SpeechManagerVersion (void)
    = {0x203C,0x0000,0x000C,0xA800};

pascal OSErr MakeVoiceSpec (OSType creator, OSType id, VoiceSpec *voice)
    = {0x203C,0x0604,0x000C,0xA800};
pascal OSErr CountVoices (short *numVoices)
    = {0x203C,0x0108,0x000C,0xA800};
pascal OSErr GetIndVoice (short index, VoiceSpec *voice)
    = {0x203C,0x030C,0x000C,0xA800};
pascal OSErr GetVoiceDescription (VoiceSpec *voice, VoiceDescription *info, long infoLength)
    = {0x203C,0x0610,0x000C,0xA800};
pascal OSErr GetVoiceInfo (VoiceSpec *voice, OSType selector, void *voiceInfo)
    = {0x203C,0x0614,0x000C,0xA800};

pascal OSErr NewSpeechChannel (VoiceSpec *voice, SpeechChannel *chan)
    = {0x203C,0x0418,0x000C,0xA800};
pascal OSErr DisposeSpeechChannel (SpeechChannel chan)
    = {0x203C,0x021C,0x000C,0xA800};

pascal OSErr SpeakString (StringPtr s)
    = {0x203C,0x0220,0x000C,0xA800};
pascal OSErr SpeakText (SpeechChannel chan, Ptr textBuf, long textBytes)
    = {0x203C,0x0624,0x000C,0xA800};
pascal OSErr SpeakBuffer (SpeechChannel chan, Ptr textBuf, long textBytes, long controlFlags)
    = {0x203C,0x0828,0x000C,0xA800};

pascal OSErr StopSpeech (SpeechChannel chan)
    = {0x203C,0x022C,0x000C,0xA800};
pascal OSErr StopSpeechAt (SpeechChannel chan, long whereToStop)
    = {0x203C,0x0430,0x000C,0xA800};
pascal OSErr PauseSpeechAt (SpeechChannel chan, long whereToPause)
    = {0x203C,0x0434,0x000C,0xA800};
pascal OSErr ContinueSpeech (SpeechChannel chan)
    = {0x203C,0x0238,0x000C,0xA800};

pascal short SpeechBusy (void)
    = {0x203C,0x003C,0x000C,0xA800};
pascal short SpeechBusySystemWide (void)
    = {0x203C,0x0040,0x000C,0xA800};

pascal OSErr SetSpeechRate (SpeechChannel chan, Fixed rate)
    = {0x203C,0x0444,0x000C,0xA800};
pascal OSErr GetSpeechRate (SpeechChannel chan, Fixed *rate)
    = {0x203C,0x0448,0x000C,0xA800};
pascal OSErr SetSpeechPitch (SpeechChannel chan, Fixed pitch)
    = {0x203C,0x044C,0x000C,0xA800};
pascal OSErr GetSpeechPitch (SpeechChannel chan, Fixed *pitch)
    = {0x203C,0x0450,0x000C,0xA800};
pascal OSErr SetSpeechInfo (SpeechChannel chan, OSType selector, void *speechInfo)
    = {0x203C,0x0654,0x000C,0xA800};
pascal OSErr GetSpeechInfo (SpeechChannel chan, OSType selector, void *speechInfo)
    = {0x203C,0x0658,0x000C,0xA800};

pascal OSErr TextToPhonemes (SpeechChannel chan, Ptr textBuf, long textBytes, Handle phonemeBuf, long *phonemeBytes)
    = {0x203C,0x0A5C,0x000C,0xA800};

pascal OSErr UseDictionary (SpeechChannel chan, Handle dictionary)
    = {0x203C,0x0460,0x000C,0xA800};

#ifdef __cplusplus
}
#endif
#endif
