/************************************************************

Created: Saturday, July 27, 1991 at 7:21 PM
 Timer.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1993
  All rights reserved



	Change History (most recent first):

		<13>	  7/7/93	DTY		Change USES68KINLINES to USESROUTINEDESCRIPTORS. Add CallXProc
									and NewXProc macros.
		<12>	  6/7/93	EPT		More ProcPtr/UPP work.
		<11>	  6/3/93	EPT		Fixed TimeMgrTask definition.
		<10>	  6/3/93	EPT		Synch up with NuReality.
		 <9>	 4/14/93	DTY		More ProcPtr work.
		 <8>	 2/24/93	JDR		Added kTMTaskActive according to Inside Mac VI.
		 <7>	 2/15/93	KIP		Change #ifdef USESROUTINEDESCRIPTORS to #ifndef
									USESROUTINEDESCRIPTORS to help Dean out.
		 <6>	  2/9/93	DTY		If we’re using routine descriptors, typedef ’ProcPtrs to be
									UniversalProcPtrs so that the caller can pass a real routine
									address, or a pointer to a routine descriptor. This causes
									parameter type checking to be lost, which is why we only do this
									if routine descriptors are used.
		 <5>	 7/31/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	 12/3/90	JDR		<dba> Use #pragma parameter and inlines.

************************************************************/


#ifndef __TIMER__
#define __TIMER__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


typedef struct TMTask TMTask, *TMTaskPtr;

#if USESROUTINEDESCRIPTORS
enum {
 uppTimerProcInfo = kRegisterBased | REGISTER_PARAM_FIELD(1, kA1, kFourByteCode)
};

typedef pascal void (*TimerProcPtr)(TMTaskPtr tmTaskPtr);
typedef UniversalProcPtr TimerUPP;

#define CallTimerProc(userRoutine, tmTaskPtr)			\
		CallUniversalProc(userRoutine, uppTimerProcInfo, tmTaskPtr)
#define NewTimerProc(userRoutine)						\
		(TimerUPP) NewRoutineDescriptor(userRoutine, uppTimerProcInfo, GetCurrentISA())
#else
typedef pascal void (*TimerProcPtr)(void);
typedef TimerProcPtr TimerUPP;

#define CallTimerProc(userRoutine, tmTaskPtr)			\
		(*userRoutine)()
#define NewTimerProc(userRoutine)						\
		(TimerUPP) (userRoutine)
#endif

#define kTMTaskActive (1<<15)		/* high bit of qType is set if task is active */

struct TMTask {
 QElemPtr 			qLink;
 short 				qType;
 TimerUPP			tmAddr;
 long 				tmCount;
 long 				tmWakeUp;
 long 				tmReserved;
};

#ifdef __cplusplus
extern "C" {
#endif
#pragma parameter InsTime(__A0)
pascal void InsTime(QElemPtr tmTaskPtr)
 = 0xA058;
#pragma parameter InsXTime(__A0)
pascal void InsXTime(QElemPtr tmTaskPtr)
 = 0xA458;
#pragma parameter PrimeTime(__A0,__D0)
pascal void PrimeTime(QElemPtr tmTaskPtr,long count)
 = 0xA05A;
#pragma parameter RmvTime(__A0)
pascal void RmvTime(QElemPtr tmTaskPtr)
 = 0xA059;
#ifdef __cplusplus
}
#endif

#endif
