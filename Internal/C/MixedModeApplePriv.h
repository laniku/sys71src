/*
	File:		MixedModePrivate.h

	Contains:	Private interfaces for the Mixed Mode mechanism

	Written by:	Bruce Jones

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 12/7/92	DRF		first checked in
		 <7>	 12/7/92	DRF		Change inline glue for Get/SetNativeFPRs to use 16-bit inline
									hex, instead of the nice 32-bit constants. The compiler was only
									using the low 16-bits of each constant!
		 <6>	 12/4/92	DRF		Changed names of Get/SetFPRs to Get/SetNativeFPRs
		 <4>	 11/9/92	JCM		Fix typo in kSetFPRSelector
		 <3>	 11/9/92	DRF		Added GetFPRs() and SetFPRs() so that the Process Manager can
									get and set the preserved native floating point registers
									(fpr14-fpr31).  NOTE: We only compile this in for the mac-based
									compiler.
		 <2>	10/12/92	EPT		Added macros OSTrapTableAddress and TBTrapTableAddress.
		 <3>	 9/19/92	LC		Add declarations of entry point names.
		 <2>	  9/9/92	LC		Moved some private definitions to MixedMode.h so that a user can
									use the macro "BuildRoutineDescriptor"
		 <1>	  9/1/92	BKJ		first checked in
		 		 8/28/92	BKJ		change to reflect latest ERS
		 		  6/2/92	BKJ		first checked in
				 4/20/92	BKJ		First Created

*/


#ifndef __MIXEDMODEAPPLEPRIVATE__
#define __MIXEDMODEAPPLEPRIVATE__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MIXEDMODE__
#include <MixedMode.h>
#endif

enum
	{
	kGetNativeFPRSelector=16,		/* MixedMode selector for GetNativeFPRs() */
	kSetNativeFPRSelector=17		/* MixedMode selector for SetNativeFPRs() */
	};

#define OSTrapTableAddress(trapNum) (((trapNum & 0x00FF) << 2) + 0x400)
#define TBTrapTableAddress(trapNum) (((trapNum & 0x03FF) << 2) + 0xE00)

#define kMM68KContextGlobalName "\pEmulated68KContext"
#define kMMEmulatorReturnGlobalName "\pEmulatorReturn"

OSErr
V0InitializeMixedMode (void);

ProcPtr
GetCustomParamProc (RoutineDescriptor theDescriptor);

OSErr
SetCustomParamProc (RoutineDescriptor theDescriptor, 
					ProcPtr newProc);

#pragma	push
#pragma skipping on
#ifndef	interface_glue
#ifdef	applec

pascal OSErr
GetNativeFPRs (Ptr fprStorage, long firstReg, long lastReg)
= {0xFEED,0x0000,0x4B4F,0x4348,kGetNativeFPRSelector};
/*	== {kGoMixedMode, kMixedModeMagicCookie, kGetNativeFPRSelector}	*/

pascal OSErr
SetNativeFPRs (Ptr fprStorage, long firstReg, long lastReg)
= {0xFEED,0x0000,0x4B4F,0x4348,kSetNativeFPRSelector};
/*	== {kGoMixedMode, kMixedModeMagicCookie, kSetNativeFPRSelector}	*/

#endif
#endif
#pragma	pop

#endif