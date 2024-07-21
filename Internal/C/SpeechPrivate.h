/*
	File:		ManagerPriv.h

	Contains:	Private Interface for Speech Manager Internals

	Written by:	Tim Schaaff

	Copyright:	© 1991-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 4/23/93	MC		?
		 <1>	 3/10/93	JDR		first checked in
		 <1>	 3/10/93	JDR		moved to {IntCIncludes}
------------------------------------
		 <2>	 1/26/93	TIM		#0,<TIM>: Add Notification Mgr routine to kill idle channels
									created by SpeakString.
		 <7>	11/10/92	TIM		Moved FailErr macro to CoolMacros.h
		 <6>	 9/15/92	TIM		Added cool Pascal string copy inline.
		 <5>	  8/3/92	TIM		Clean up code so JDR doesn't thrash me so much during code
									review.
		 <4>	 7/27/92	TIM		Add speechMgrVersion to SpeechGlobalsRec definition
		 <3>	 7/23/92	TIM		Clean up the file a bit.
		 <2>	 7/17/92	JDR		make it a link patch
		 <1>	 7/ 1/92	TIM		Added Voice list defines
		 <0>	 11/6/91	TIM		first checked in

*/

#ifndef _ManagerPriv_
#define _ManagerPriv_

#include <ExpandMemPriv.h>					/* kludge to avoid conflicts in Sound Mgr */
#ifndef __SOUNDPRIVATE__
#include "SoundPrivate.h"					/* pick up private defines from SADISM code */
#endif
#include <Components.h>
#include <Notification.h>
#include <Speech.h>

#define USE_SYSTEM_HEAP				true	/* true to allocate channel memory from SysZone, false for ApplZone */
#define TRACE						false	/* set true to break at every proc entry */
#define DEBUG_PRINTS				false	/* set true to compile in debug diagnostic calls */

#if TRACE
#define TraceMsg(msg) DebugStr("\p"#msg)
#else
#define TraceMsg(msg) ((void)0)
#endif

#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
#define ABS(a) (((a) < 0) ? -(a) : (a))

#if DEBUG_PRINTS
#define ShowNum(label, num)		if (gSpeechGlobals->flags & kDebug) fprintf(stdout,label,(num))
#ifdef THINK_C
#define ShowPStr(label, pstr)	if (gSpeechGlobals->flags & kDebug) fprintf(stdout,label"\"%#s\"", (pstr))
#else
#define ShowPStr(label, pstr)	if (gSpeechGlobals->flags & kDebug) fprintf(stdout,label"\"%.*s\"", (pstr)[0], &((pstr)[1]))
#endif
#define ShowOSType(label, type)	if (gSpeechGlobals->flags & kDebug) fprintf(stdout,label"\'%.4s\'", &(type))
#define ShowStr(label)			if (gSpeechGlobals->flags & kDebug) fprintf(stdout,label)
#define ShowCR()				if (gSpeechGlobals->flags & kDebug) fprintf(stdout,"\n")
#else
#define ShowNum(label, num)		((void)0)
#define ShowPStr(label, pstr)	((void)0)
#define ShowOSType(label, type)	((void)0)
#define ShowStr(label)			((void)0)
#define ShowCR()				((void)0)
#endif

#define ShowNumCR(label, num)		{ShowNum(label,num); ShowCR();}
#define ShowPStrCR(label, pstr)		{ShowPStr(label, pstr); ShowCR();}
#define ShowOSTypeCR(label, type)	{ShowOSType(label, type); ShowCR();}
#define ShowStrCR(label)			{ShowStr(label); ShowCR();}

// Speech globals defines

#define speechToolNum	0xC

#ifndef __SOUNDPRIVATE__
#define gSpeechGlobals	((SpeechGlobalsPtr) SndGlobals->unused2)
#else
#define gSpeechGlobals	((SpeechGlobalsPtr) (GetSadismGlobals()->speechGlobals))
#endif

enum {										/* flag defines for VoiceListRec 'flags' field */
	kExtensionVoice 	= (1 << 0),			/* bit set if voice was found in Extension folder */
	kSystemVoice 		= (1 << 1),			/* bit set if voice was found in System Folder*/
	kApplicationVoice 	= (1 << 2)			/* bit set if voice was found in app resource file chain */
};

typedef struct VoiceListRec VoiceListRec, *VoiceListPtr, **VoiceListHandle;

struct VoiceListRec {
	VoiceListHandle		nextVox;			/* forward link to next record or nil if end of list */
	VoiceSpec			vox;				/* the voice spec info */
	VoiceFileInfo		file;				/* file spec & resource id for voice */
	unsigned short		flags;				/* some control/info flags that might be useful */
};

enum {										/* flag defines for SpeechChanRec 'flags' field */
	kPrivateChan 	= (1 << 0),				/* bit set if SpeechChannel is owned by Speech Mgr (for SpeakString) */
	kNMRecInstalled = (1 << 1)				/* bit set if Notification Mgr task has been installed on this channel */
};

typedef struct SpeechChanRec {
	struct SpeechChanRec  	*nextChan;		/* link ptr to next active speech chan or NULL if at end of list */
	ProcessSerialNumber		appPSN;			/* application that created the channel */
	long					A5World;		/* latched copy of A5 when channel was first allocated */
	struct SpeechChanRec 	**selfHandle;	/* will hold copy of handle to ourself (THIS IS WIERD) */
	SpeechChannel	   		theChan;		/* the ComponentInstance allocated for this SpeechChannel */
	Str255					speakStr;		/* a Pascal string used by SpeakString */
	unsigned short			flags;			/* some control/info flags for us to use */
	NMRec					notifyRec;		/* Notification Mgr record for tracking SpeakString channels */
} SpeechChanRec, *SpeechChanRecPtr, **SpeechChanRecHandle;

typedef pascal void (*SADProcPtr)(void);	/* for SoundAppDead proc ptr */

enum {										/* flag defines for SpeechGlobalsRec */
	kDebug 		= (1 << 0),					/* set bit to enable debugging diagnostics */
	kSysHeap 	= (1 << 1)					/* set bit to force allocation of VoiceListRecords in System heap */
};

typedef struct SpeechGlobalsRec {
	SpeechChanRecPtr	 chanQHead;			/* head ptr for linked list of active speech channels */
	VoiceListHandle		 voxList;			/* list of voices known to Speech Manger */
	unsigned long		 systemModDate;		/* Date/time of last modification to System Folder */
	long				 systemVersion;		/* System software version number from Gestalt */
	unsigned short		 flags;				/* just some bits to play with */
	VoiceSpec			 defaultVoice;		/* voice spec for default voice from prefs resource */
	long			 	 defaultRate;		/* Rate for default voice from prefs resource */
	long				 defaultPitch;		/* Pitch for default voice from prefs resource */
	long				speechMgrVersion;	/* version value for currently installed Speech Manager */
} SpeechGlobalsRec, *SpeechGlobalsPtr, **SpeechGlobalsHandle;


#ifndef __SOUNDPRIVATE__
// Here's a very cool Pascal string copy inline routine.

#pragma parameter PStringCopy(__A0,__A1)
void PStringCopy(StringPtr source, StringPtr destination) =
			{0x7000, 0x1010, 0x12D8, 0x51C8, 0xFFFC};

//		moveq	#0,d0			; clear the index register
//		move.b	(A0),D0			; get string length
//Loop	move.b	(A0)+,(A1)+		; copy bytes, one greater for length byte
//		dbra	D0,Loop			;
#endif

//Private Speech Manager Traps



#define privSetDefaultVoice				'pvox'		// Set default voice (SetSpeechDefaults)
#define privSetDefaultPitch				'ppit'		// Set default voice (SetSpeechDefaults)
#define privSetDefaultRate				'prat'		// Set default voice (SetSpeechDefaults)



pascal OSErr SetSpeechDefaults (OSType selector, void *defaultInfo)
	= {0x203C,0x0464,0x000C,0xA800};

pascal OSErr GetSpeechDefaults (OSType selector, void *defaultInfo)
	= {0x203C,0x0468,0x000C,0xA800};

pascal OSErr AddSpeechChannelToList (SpeechChannel ch)  /* put SpeechChannel into SpeechGlobals channel queue */
	= {0x203C,0x026C,0x000C,0xA800};

pascal OSErr ShutDownSpeechManager ( void )
	= {0x203C,0x0070,0x000C,0xA800};

pascal OSErr KillIdlePrivateChannels ( Boolean curProcessOnly )
	= {0x203C,0x0174,0x000C,0xA800};

pascal OSErr KillProcessChannels ( void )
	= {0x203C,0x0078,0x000C,0xA800};

pascal OSErr RegisterVoices (long whereToSearch, VoiceListHandle *voxList) /* finds and registers voices in various places */
	= {0x203C,0x047C,0x000C,0xA800};

pascal OSErr UnRegisterVoices (unsigned short whichVoices, VoiceListHandle *voxList)
	= {0x203C,0x0480,0x000C,0xA800};

#endif