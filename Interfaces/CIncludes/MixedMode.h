/*
	File:		MixedMode.h

	Contains:	Headers and interfaces for the Mixed Mode mechanism

	Written by:	Bruce Jones

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 12/7/92	DRF		first checked in
		<18>	11/13/92	DRF		Fix a bug in BuildRoutineDescriptor macro. We were building
									kLoadAndExecute RDs and not kExecute types! Of course,
									CodeFragMgrDispatch and MixedModeDispatch were the only two
									users of this macro, so nobody knew it was broken.
		<17>	 11/8/92	BKJ		Rolled back
	   <13+>	10/26/92	SP		Adding definition for m68KRegisterSizePhase
		<13>	10/22/92	DRF		Added inline 68K trap glue for NewRoutineDescriptor and
									DisposeRoutineDescriptor
		<12>	10/19/92	DRF		Changed declaration of NewRoutineDescriptor and
									DisposeRoutineDescriptor to match Sean’s clearer syntax.
		<11>	10/13/92	SP		Changing all m68k's to m68K
		<10>	10/08/92	SP		Adding phase and offset enum for the parameters.
		 <9>	 10/4/92	BKJ		Current version is 1
		 <8>	 10/1/92	jrg		Made smaller enum blocks and changed typedef for InterfaceTool
		 <7>	 9/29/92	BKJ		Fix bug in BuildRoutineDescriptor macro.
		 <6>	 9/28/92	stb		add special cases as used by the rest of the public interfaces
		 <5>	 9/18/92	LC		changing kGoMixedMode to 0xFEED0000
		 <4>	 9/10/92	EPT		Added (long) typecasts to enum constants. Changed constants to
									conform to new procInfo definition.
		 <3>	  9/9/92	LC		Added Macro "BuildRoutineDescriptor, which allows static
									declaration of a routine descriptor at compile time.  In order
									to have this macro, many private declarations had to be brought
									over from MixedModeApplePrivate.h, including kGoMixedMode, and
									kMixedModeMagicCookie.
		 <2>	  9/2/92	BKJ		Get rid of numParams parameter to BuildProcInfo &
									CallRoutineDescriptor calls.
		 <1>	  9/1/92	BKJ		first checked in
		 		 8/28/92	BKJ		change to reflect latest ERS
				  6/5/92	BKJ		Continued Development
				 4/17/92	BKJ		Created

*/



#ifndef __MIXEDMODE__
#define __MIXEDMODE__

#ifndef __TYPES__
#include <Types.h>
#endif

#define	kGoMixedMode 0xFEED0000

#define	kMixedModeMagicCookie 0x4B4F4348

#define PARAMETER_SIZE(size) \
	(((size) == 4) ? 3 : (((size) == 2) ? 1 : (((size) == 1) ? 2 : 0)))
	
enum {
	kResultPhase = 4,			/* bit offset for result field */
	kParameterPhase = 6,
	kParameterOffset = 2,
	m68KRegisterOffset = 6,
	m68KRegisterOut = 0x20,
	m68KRegisterIn = 0x10,
	m68KRegisterParameterPhase = 2,
	m68KRegisterA0 = 0,
	m68KRegisterA1 = 1,
	m68KRegisterD0 = 2,
	m68KRegisterD1 = 3
};


enum {
	kPStackBased = 0, 
	kCStackBased = 1, 
	kRegisterBased = 2, 
	kD0DispStackBased = 8,
	kD1DispStackBased = 12,
	kStackDispStackBased = 14,
	kStackDispRegisterBased = 10,
	kSpecialCaseProcInfoType = 5
	};
typedef short CallingConventionType;


enum {
	// the Mixed Mode error codes
	mmInternalError = -2526,
	kMMErr2 = -2527,
	kMMErr3 = -2528,
	kMMErr4 = -2529,
	kMMErr5 = -2530,
	kMMErr6 = -2531,
	kMMErr7 = -2532,
	kMMErr8 = -2533,
	kMMErr9 = -2534,
	kMMErr10 = -2535
};
typedef short MMErrType;

enum {
	kRegisterD0 = 0,
	kRegisterD1,
	kRegisterD2,
	kRegisterD3,
	kRegisterD4,
	kRegisterD5,
	kRegisterD6,
	kRegisterD7,
	kRegisterA0,
	kRegisterA1,
	kRegisterA2,
	kRegisterA3,
	kRegisterA4,
	kRegisterA5,
	kRegisterA6,
	kRegisterA7
};
typedef short RegisterSelectorType;

enum {kLoadAndExecute = 0, kExecute, kReturnFrom};
typedef short SelectorType;

enum {kCodeTypeUnknown = -1, kCodeTypeCurrentWorld, kCodeType68K, kCodeTypePower};
typedef long CodeType;

typedef long ProcInfoType;

typedef struct private_RoutineDescriptor* RoutineDescriptor;


/* ProcInfo selectors for each of the parameters */

/* Pascal and C Stack based parameter constants */
/* Stack-based dispatched uses these, but only P2 and up */
enum {
	m68KStackP1Byte = (long)0x00000080,
	m68KStackP1Word = (long)0x00000040,
	m68KStackP1Long = (long)0x000000C0,
	m68KStackP2Byte = (long)0x00000200,
	m68KStackP2Word = (long)0x00000100,
	m68KStackP2Long = (long)0x00000300,
	m68KStackP3Byte = (long)0x00000800,
	m68KStackP3Word = (long)0x00000400,
	m68KStackP3Long = (long)0x00000C00,
	m68KStackP4Byte = (long)0x00002000,
	m68KStackP4Word = (long)0x00001000,
	m68KStackP4Long = (long)0x00003000,
	m68KStackP5Byte = (long)0x00008000,
	m68KStackP5Word = (long)0x00004000,
	m68KStackP5Long = (long)0x0000C000,
	m68KStackP6Byte = (long)0x00020000,
	m68KStackP6Word = (long)0x00010000,
	m68KStackP6Long = (long)0x00030000,
	m68KStackP7Byte = (long)0x00080000,
	m68KStackP7Word = (long)0x00040000,
	m68KStackP7Long = (long)0x000C0000,
	m68KStackP8Byte = (long)0x00200000,
	m68KStackP8Word = (long)0x00100000,
	m68KStackP8Long = (long)0x00300000,
	m68KStackP9Byte = (long)0x00800000,
	m68KStackP9Word = (long)0x00400000,
	m68KStackP9Long = (long)0x00C00000,
	m68KStackP10Byte = (long)0x02000000,
	m68KStackP10Word = (long)0x01000000,
	m68KStackP10Long = (long)0x03000000,
	m68KStackP11Byte = (long)0x08000000,
	m68KStackP11Word = (long)0x04000000,
	m68KStackP11Long = (long)0x0C000000,
	m68KStackP12Byte = (long)0x20000000,
	m68KStackP12Word = (long)0x10000000,
	m68KStackP12Long = (long)0x30000000,
	m68KStackP13Byte = (long)0x80000000,
	m68KStackP13Word = (long)0x40000000,
	m68KStackP13Long = (long)0xC0000000
};

enum {
/* Register based parameter constants */
/* Also used for register-based dispatching */
	m68KRegisterP1In 	= (long)0x00000400,
	m68KRegisterP1Out 	= (long)0x00000800,
	m68KRegisterP1InOut = (long)0x00000C00,
	m68KRegisterP2In 	= (long)0x00010000,
	m68KRegisterP2Out 	= (long)0x00020000,
	m68KRegisterP2InOut = (long)0x00030000,
	m68KRegisterP3In 	= (long)0x00400000,
	m68KRegisterP3Out 	= (long)0x00800000,
	m68KRegisterP3InOut = (long)0x00C00000,
	m68KRegisterP4In 	= (long)0x10000000,
	m68KRegisterP4Out 	= (long)0x20000000,
	m68KRegisterP4InOut = (long)0x30000000
};

enum {
	m68KRegisterP1Byte = (long)0x00000200,
	m68KRegisterP1Word = (long)0x00000100,
	m68KRegisterP1Long = (long)0x00000300,
	m68KRegisterP2Byte = (long)0x00008000,
	m68KRegisterP2Word = (long)0x00004000,
	m68KRegisterP2Long = (long)0x0000C000,
	m68KRegisterP3Byte = (long)0x00200000,
	m68KRegisterP3Word = (long)0x00100000,
	m68KRegisterP3Long = (long)0x00300000,
	m68KRegisterP4Byte = (long)0x08000000,
	m68KRegisterP4Word = (long)0x04000000,
	m68KRegisterP4Long = (long)0x0C000000
};

enum {
	m68KRegisterP1A0 = (long)0x00000000,
	m68KRegisterP1A1 = (long)0x00000040,
	m68KRegisterP1D0 = (long)0x00000080,
	m68KRegisterP1D1 = (long)0x000000C0,
	m68KRegisterP2A0 = (long)0x00000000,
	m68KRegisterP2A1 = (long)0x00001000,
	m68KRegisterP2D0 = (long)0x00002000,
	m68KRegisterP2D1 = (long)0x00003000,
	m68KRegisterP3A0 = (long)0x00000000,
	m68KRegisterP3A1 = (long)0x00040000,
	m68KRegisterP3D0 = (long)0x00080000,
	m68KRegisterP3D1 = (long)0x000C0000,
	m68KRegisterP4A0 = (long)0x00000000,
	m68KRegisterP4A1 = (long)0x01000000,
	m68KRegisterP4D0 = (long)0x02000000,
	m68KRegisterP4D1 = (long)0x03000000
};

enum {

/* Dispatched constants for kStackDispRegisterBased type (selector on stack) */
	m68KStackSelectorByte = (long)0x00000020,
	m68KStackSelectorWord = (long)0x00000010,
	m68KStackSelectorLong = (long)0x00000030,

/* Dispatched constants for all dispatched stack-based types */
	m68KRegSelectorByte = (long)0x00000080,
	m68KRegSelectorWord = (long)0x00000040,
	m68KRegSelectorLong = (long)0x000000C0,

/* Selectors for the ProcInfo result size fields */
	kNoReturnValue = (long)0x00000000,
	k68KByteReturned = (long)0x00000020,
	k68KWordReturned = (long)0x00000010,		/* 68K word - two bytes */
	k68KLongReturned = (long)0x00000030			/* 68K long - four bytes */
};

/* all of the special cases enumerated */
enum {
	kSpecialCaseHighHook = 0x0100,
	kSpecialCaseCaretHook = 0x0100,
	kSpecialCaseEOLHook = 0x0200,
	kSpecialCaseWidthHook = 0x0300,
	kSpecialCaseNWidthHook = 0x0400,
	kSpecialCaseTextWidthHook = 0x0500,
	kSpecialCaseDrawHook = 0x0600,
	kSpecialCaseHitTestHook = 0x0700,
	kSpecialCaseTEFindWord = 0x0800,
	kSpecialCaseADBRoutines = 0x0900,
	kSpecialCaseProtocolHandler = 0x0A00,
	kSpecialCaseSocketListener = 0x0B00
};
/*
	Explanation of special cases:
	*****************************
	1 = C calling conventions, Rect on stack, pointer in A3, no return value
	2 = Register-based; inputs in D0, A3, A4; output is Z flag of 
		status register (see VI-15-26)
	3 = Register-based; inputs in D0, D1, A0, A3, A4; output in D1 (see VI-15-27)
	4 = Register-based; inputs in D0, D1, D2, A0, A2, A3, A4; output in D1 
		(see VI-15-27)
	5 = Register-based; inputs in D0, D1, A0, A3, A4; output in D1 (see VI-15-28)
	6 = Register-based; inputs in D0, D1, A0, A3, A4; no output (see VI-15-28)
	7 = Register-based; inputs in D0, D1, D21, A0, A3, A4; outputs in
		D0, D1, D2 (See VI-15-29)
	8 = Register-based; inputs in D0, D2, A3, A4; outputs in D0, D1 (see VI-15-30)
	9 = Register-based; inputs in A0, A1, A2, D0; no outputs (see V-371)
	A = Register-based; inputs in A0, A1, A2, A3, A4, D1.w; output in Z (see II-326)
	B = Register-based; inputs in A0, A1, A2, A3, A4, D0.b, D1.w; output in Z 
		(see II-329)

*/

RoutineDescriptor
NewRoutineDescriptor(ProcPtr theProc, 
						ProcInfoType procInfo, 
						CodeType typeOfCode)
	= {0x303C,0x0000,0xAA59};	/* <13> */

void
DisposeRoutineDescriptor (RoutineDescriptor theDescriptor)
	= {0x303C,0x0001,0xAA59};	/* <13> */

long
CallRoutineDescriptor (RoutineDescriptor theRoutine,
						ProcInfoType procInfo,
						...);
CodeType
GetCodeType (RoutineDescriptor theDescriptor);

OSErr
SetCodeType (RoutineDescriptor theDescriptor,
			CodeType newCodeType);

ProcInfoType
BuildProcInfo(CallingConventionType callingConvention, 
				short resultSize, 
				...);

ProcInfoType
GetProcInfo (RoutineDescriptor theDescriptor);

OSErr
SetProcInfo (RoutineDescriptor theDescriptor, 
			ProcInfoType newProcInfo);

ProcPtr
GetTheProc (RoutineDescriptor theDescriptor);

OSErr
SetTheProc (RoutineDescriptor theDescriptor, 
			ProcPtr newProc);

long
GetEmulatorRegister (RegisterSelectorType registerSelector);

long
SetEmulatorRegister (RegisterSelectorType registerSelector,
					long newValue);


enum {kRoutineDescriptorVersion = 1};

struct private_RoutineDescriptor {
	long				goMixedMode;			// unused 68K instruction						 0
	long				magicCookie;			// unique identifier							 4
	SelectorType		selector;				// mixed mode selector							 8
	short				version;				// 0 for now, increment as needed				10
	ProcInfoType		procInfo;				// calling conventions							12
	ProcPtr				customParamProc;		// Procedure to convert params					16
	CodeType			executionMode;			// to different types of code					20
	ProcPtr				procDescriptor;			// Descriptor of routine we are going to call	24
	long				unused;					// must be 0									28
};

typedef struct private_RoutineDescriptor private_RoutineDescriptor;
typedef private_RoutineDescriptor *private_RoutineDescriptorPtr, **private_RoutineDescriptorHandle;

/* a macro which creates a static instance of a routine descriptor */
#define BuildRoutineDescriptor(procInfo, procedure) 				\
	{																\
		kGoMixedMode,				/* GoMixedMode instruction */	\
		kMixedModeMagicCookie,		/* Mixed Mode magic cookie */	\
		kExecute,					/* selector <18> */				\
		kRoutineDescriptorVersion,	/* version */					\
		(procInfo),					/* ProcInfo */					\
		0,							/* custom param proc */			\
		kCodeTypePower,				/* execution mode */			\
		(void *) (procedure),		/* theProc */					\
		0,							/* list terminator */			\
	}


#endif