/*
	File:		VDigUtils.c

	Contains:	Utilities for the Video Digitizer Component.

	Written by:	Fernando Urbina

	Copyright:	© 1993 by Apple Computer, Inc. All rights reserved.

	Change History (most recent first):

		 <1>	  6/3/93	kc		first checked in
	   <LW7>	 4/14/93	fau		Got rid of obsolete routines and made Enable/DisableVideo in to
									do essentially nothing.
	   <LW6>	  4/5/93	fau		Changed the csCode to use the ones defined in DepVideo.h.
	   <LW5>	  4/4/93	fau		When checking the GetVidIn csMode, made sure to look at only bit
									0 by anding with 0x01.
	   <LW4>	 2/22/93	fau		Changed the GetMaxVidMode routine to use the new
									GetCompOutCapabilities call to the driver that will return the
									maximum mode with video in.  This fixes a bug when dynamically
									switching video-in when the graphics bpp is too high.
	   <LW3>	 2/17/93	fau		Backed out the previous change because the driver reverted to
									its original mode.
	   <LW2>	 2/16/93	fau		Updated the call to cscGetVideoIn to reflect the new interface
									in the driver.  (The enabled bit is bit 1, not bit 0).
		 <1>	  1/4/93	fau		first checked in

*/

#include <Palettes.h>
#include <Video.h>
#include <RomDefs.h>
#include <Slots.h>
#include <Video.h>
#include <DepVideo.h>
#include <ToolUtils.h>
#include <Devices.h>
#include "Cyclone.h"

/********************************************************************
*
*	P R O T O T Y P E S
*
********************************************************************/
Boolean				IsItRegisterRoutine();
unsigned 	long	GetBaseAddress();
pascal OSErr		EnableVideoIn(GDHandle gdh);
pascal OSErr		DisableVideoIn(GDHandle gdh);

/********************************************************************
*
*	IsItRegisterRoutine:  Will return true if the "Doing an open component"
*   				      for registering in the slot 0 PRAM vendor5 byte
*                         is true
*
********************************************************************/
Boolean	IsItRegisterRoutine()
{
	SpBlock		aSpBlock;
	OSErr		result;
	char		spBytes[8];
	Boolean		itsRegistering = false;
		   
	aSpBlock.spSlot = 0;
	aSpBlock.spResult = (long) spBytes;
	result = SReadPRAMRec(&aSpBlock);
	
	if (result == noErr)
	{
		/* Is bit 6 ON */ 
		itsRegistering =  (spBytes[6] &= (0x01 << spOpenComponent)) == 0 ? false : true ;
	}
	
	return (itsRegistering);
}

/********************************************************************
*
*
*
********************************************************************/
pascal OSErr	EnableVideoIn(GDHandle gdh)
{

	OSErr		retstat = noErr;
	VDFlag		myFlag;
	CntrlParam	pb;
	
	/* Check to see if video-in is not enabled */
	/* Setup the Control Parameter block */

	pb.ioCRefNum = (**gdh).gdRefNum;
	pb.ioCompletion = nil;
	pb.ioNamePtr = nil;
	pb.ioVRefNum = 0;
	pb.csCode = cscGetVideoIn;
	* (Ptr *) &pb.csParam[0] = (Ptr) (&myFlag);

	retstat = PBStatus((ParmBlkPtr) &pb,false);
	
	return (retstat);
}

/********************************************************************
*
*
*
********************************************************************/
pascal OSErr	DisableVideoIn(GDHandle gdh)
{
	OSErr		retstat = noErr;
	VDFlag		myFlag;
	CntrlParam	pb;
	
	/* Check to see if video-in is not enabled */
	/* Setup the Control Parameter block */
	
	pb.ioCRefNum = (**gdh).gdRefNum;
	pb.ioCompletion = nil;
	pb.ioNamePtr = nil;
	pb.ioVRefNum = 0;
	pb.csCode = cscGetVideoIn;
	* (Ptr *) &pb.csParam[0] = (Ptr) (&myFlag);

	retstat = PBStatus((ParmBlkPtr) &pb,false);

	return (retstat);
}

/********************************************************************
*
*
*
********************************************************************/
unsigned long	GetBaseAddress()
{
	SpBlock		mySpBlock;
	OSErr		myError;

	mySpBlock.spParamData = 1;
	mySpBlock.spCategory = catDisplay;
	mySpBlock.spCType = typeVideo;
	mySpBlock.spDrvrSW = 0;
	mySpBlock.spDrvrHW = 0;
	mySpBlock.spTBMask = 3;
	mySpBlock.spSlot = 0;
	mySpBlock.spID = 0;
	mySpBlock.spExtDev = 0;
	
	myError = SNextTypeSRsrc(&mySpBlock);
	myError = SFindDevBase(&mySpBlock);
	
	return( (unsigned long) mySpBlock.spResult );
}


 