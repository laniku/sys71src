/*
	File:		QueueUtils.h

	Contains:	header stuff for QueueUtils.a routine(s)

	Notes:

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SMG2>	 9/29/93	chp		Fix “include once” SET variable naming conventions.
	   <SM6>	10/14/93	pdw		<MC> roll-in.
	   <SM5>	 9/12/93	pdw		Changed name of EnqueueHead to CEnqueueHead to avoid conflict
									with newly added ROM OS routine.
	   <SM4>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <SM3>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <SM2>	11/20/92	DCB		Got rid of include to solve makefile dependency problem

*/

#ifndef __QUEUEUTILS__
#define __QUEUEUTILS__

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif


void	CEnqueueHead(QElemPtr qElement,QHdrPtr qHeader);


#endif __QUEUEUTILS__
