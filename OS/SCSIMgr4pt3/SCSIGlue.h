/*
	File:		SCSIGlue.h

	Contains:	prototypes for stuff in SCSIGlue.a

	Written by:	Paul Wolf

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM11>	11/22/93	pdw		Rolling in from <MCxx>.
	  <SM10>	11/21/93	pdw		Removed IllegalInstruction and UnimplentedATrap procedures.
	  <SMG3>	 9/29/93	chp		Include ACAM.h if necessary.
	  <SMG2>	 9/22/93	chp		Add a TestFor for Grand Central.
	   <SM8>	10/14/93	pdw		<MC> roll-in.
	   <SM7>	 8/13/93	pdw		Changed TestFor_Orwell to TestFor_OrwellExists
	   <SM6>	 7/17/93	pdw		Added VMRunning routine header.
	   <SM5>	  5/5/93	PW		Adding IllegalInstr() and UnimplementedATrap() functions.
	   <SM4>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW5>	 4/14/93	DCB		Added prototype for CallOldXPT
	   <LW4>	 2/17/93	PW		Rolled in some of the PDM changes to make it easier to remain
									sane.
	   <SM3>	  4/8/93	DCB		Added glue for TestForDJMEMC and TestForOrwell
	   <SM2>	 1/31/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/27/93	PW		Changed VMEnableUserCode prototype to return void again because
									that last fix was a bogus way of doing it.
	   <LW2>	 1/12/93	DCB		Changed prototype for VMEnableUserCode.

*/

#ifndef __SCSIGLUE__
#define __SCSIGLUE__

#ifndef __ACAM__
#include "ACAM.h"
#endif


Boolean	TestFor_SCSI96_1Exists( void);
Boolean	TestFor_SCSI96_2Exists( void);
Boolean	TestFor_PSCExists( void);
Boolean	TestFor_HMCDecoder( void);
Boolean	TestFor_djMEMCExists( void);
Boolean	TestFor_OrwellExists( void);
Boolean TestFor_GrandCentralExists( void);
void	VMEnableUserCode( void);		// enable user code (Åallow page faults)
void	VMDisableUserCode( void);		// disable user code (Åpage faults fatal)
Boolean	VMRunning( void);

OSErr	CallOldXPT( SCSI_PB *,ulong, ulong );		// call an XPT that isn't installed as a trap


#endif __SCSIGLUE__
