/*
	File:		CodeFragmentsTrap.h

	Contains:	Inline glue for Code Fragment Manager

	Written by:	Dave Falkenburg

	Copyright:	© 1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 12/7/92	DRF		first checked in
		 <5>	 12/3/92	HSC		Added the rest of the CFM functions defs
		 <4>	 11/2/92	DRF		InterfaceTool has changed, so redo <3> the new way.
		 <3>	10/30/92	DRF		Added “#ifdef applec” so we don’t put glue for this into
									PrivateInterfaceLib!
		 <2>	10/26/92	DRF		Added prerequisite #includes so that InterfaceTool doesn’t choke
		 <1>	10/22/92	DRF		first checked in

*/

#ifndef		__CODEFRAGMENTSTRAP__
#define		__CODEFRAGMENTSTRAP__

#pragma push
#pragma skipping on
#ifndef	interface_glue

/* <3>,<4> Don’t generate glue for this stuff!!! */

#include <Types.h>
#include <Memory.h>
#include <Files.h>
#include <Processes.h>
#include <CodeFragments.h>

//
// System Programmer's Interface
//
//        Functions that do actions
//

FragErr FragCreateContext  ( FragContextID      *contextID,
                             THz                 heapZone, 
                             AddressSpaceID      addressSpace, 
                             TaskID              taskID,
                             TeamID              teamID, 
                             Mask                contextFlags )
	= {0x303C,0x0000,0xAA5A};

FragErr FragPrepare        ( FragContextID       contextID,
                             FragmentLocatorPtr  fragLocator,
                             Str63               libName,
                             Boolean             attachDynamic,
                             OSType              architecture,
                             FragConnectionID   *connectionID,
                             LogicalAddress     *entryAddress,
                             Str63               errName )
	= {0x303C,0x0001,0xAA5A};

FragErr FragRelease        ( FragContextID       contextID, 
                             FragConnectionID    connectionID,
                             Mask                releaseWhich,
                             Boolean             normalTerm )
	= {0x303C,0x0002,0xAA5A};


FragErr FragRegister       ( FragmentLocatorPtr  fragLocator,
                             Boolean             beforePMSP,
                             long                updateLevel,
                             Str63               libName,
                             Boolean             unregister )
	= {0x303C,0x0003,0xAA5A};

FragErr FragAddSearchFcn   ( FragSearchProcPtr   SearchFcn,
                             Boolean             callFirst )
	= {0x303C,0x0004,0xAA5A};


FragErr FragGetRegisterInfo   ( long             libIndex,
                                RegisteredInfo  *registerInfo )
	= {0x303C,0x0005,0xAA5A};
	

FragErr FragResolveSymbol  ( FragContextID       contextID,
                             FragConnectionID    connectionID,
                             Str255              symbolName,
                             SymClass           *symbolClass,
                             long               *symbolIndex,
                             LogicalAddress     *symbolAddress )
	= {0x303C,0x0006,0xAA5A};


FragErr FragGetContextInfo   ( FragContextID    contextID,
                               Boolean          nextContext,
                               ContextInfo     *contextInfo )
	= {0x303C,0x0007,0xAA5A};
	

FragErr FragGetConnectionInfo( FragContextID     contextID,
                               FragConnectionID  connectionID,
                               Boolean           nextConnection,
                               ConnectionInfo   *connectionInfo )
	= {0x303C,0x0008,0xAA5A};
	

FragErr FragGetSectionInfo   ( FragContextID     contextID,
                               FragConnectionID  connectionID,
                               long              sectionIndex,
                               long              sectionCount,
                               SectionInfo      *sectionInfo )
	= {0x303C,0x0009,0xAA5A};


#endif	/* interface_glue */
#pragma pop

#endif
