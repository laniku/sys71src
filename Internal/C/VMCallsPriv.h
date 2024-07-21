/*
	File:		VMCallsPriv.h

	Contains:	Private internal calls for VM (called via MemoryDispatch)

	Written by:	Eric Anderson

	Copyright:	© 1989-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	10/28/91	SAM/KSM	Rolled in Regatta file.
	
	Regatta Change History:

		 <3>	 7/18/91	SAM		Changing a rude comment.
		 <2>	 7/18/91	SAM		(ewa) Added 2 new selectors for logical and physical bytes
		 <1>	 7/18/91	SAM		Split off from 7.0 GM sources.

	7.0 Change History:
		 <1>	  4/2/91	DTY		first checked in
		4/2/91			ewa		dty: Created file for BBS folks

	To Do:
*/

#ifndef __TYPES__
#include <Types.h>
#endif


/* VM calls */

#ifdef __cplusplus
extern "C" {
#endif
/* Tell VM to finish its installation (MemoryDispatch -1) */
pascal void VM_FinishInstall(void)
    = {0x70FF,0xA05C}; 

/* Tell VM to hold the current system heap (MemoryDispatch -2) */
#pragma parameter __D0 VM_HoldSystemHeap
pascal OSErr VM_HoldSystemHeap(void)
    = {0x70FE,0xA05C};
	
/* Get the number of holdable bytes (MemoryDispatch -3) */
#pragma parameter __D0 VM_GetHoldableBytes
pascal unsigned long VM_GetHoldableBytes(void)
    = {0x70FD,0xA05C}; 
	
/* Get the minimum point BufPtr can grow down into (MemoryDispatch -4) */
#pragma parameter __D0 VM_GetMinBufPtr
pascal unsigned long VM_GetMinBufPtr(void)
    = {0x70FC,0xA05C}; 

/* Get the number of physical bytes in VM's world (MemoryDispatch -5) */
#pragma parameter __D0 VM_GetPhysicalBytes
pascal unsigned long VM_GetPhysicalBytes(void)
    = {0x70FB,0xA05C}; 

/* Get the number of logical bytes in VM's world (MemoryDispatch -6) */
#pragma parameter __D0 VM_GetLogicalBytes
pascal unsigned long VM_GetLogicalBytes(void)
    = {0x70FA,0xA05C}; 

#ifdef __cplusplus
}
#endif
