/*
	File:		Recorder.h

	Contains:	header stuff for various C utility stuff

	Notes:		In-line assembly for atomic bit operations

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	   <SM8>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC2>	11/10/93	pdw		Added ERR_RECORD_ON support by breaking IfRecordEvent apart from
									IfRecordError.
	   <SM7>	10/14/93	pdw		<MC> roll-in.
	   <SM6>	  7/8/93	pdw		Addin IfRecordError define.
	   <SM5>	 6/29/93	pdw		Massive checkins: Change asynchronicity mechanism to CallMachine
									stack switching mechanism.  Adding support for Cold Fusion.
									Rearranging HW/SW Init code. Some code optimizations.
	   <SM4>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM3>	 3/20/93	PW		Recording on by default again.
	   <SM2>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW2>	 1/12/93	DCB		Changed RECORD_ON use to pay attention to -d defines in C
									command line.
		 <1>	11/17/92	PW		first checked in

*/

#ifndef __Recorder__
#define __Recorder__ 1


//ÑÑÑÑ Prototype ÑÑÑÑ
void	RecordEvent( long a, long b);


#if RECORD_ON
#define IfRecordEvent(a,b)	RecordEvent(a,b)
#else
#define IfRecordEvent(a,b) 
#endif


#if ERR_RECORD_ON
#define IfRecordError(a) 	RecordEvent(a,'Err!')
#else
#define IfRecordError(a) 
#endif



#endif	// __Recorder__
