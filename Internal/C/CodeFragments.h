/*
    File:       CodeFragments.h

    Contains:   Code Fragment Manager: 
                System Programmer's Interface

    Written by: Erik L Eidt 

    Copyright:  © 1992 by Apple Computer, Inc., all rights reserved.

    Change History (most recent first):

		 <1>	 12/7/92	DRF		first checked in
		 <7>	11/11/92	ELE		char ==> unsigned char
		 <6>	 11/3/92	NL		Added back #include <Memory.h>, because it is definitely needed!
									Specifically, for the THz typedef, as well as for prototypes for
									functions (eg: GetZone()).
		 <5>	10/28/92	WSK		Remove "#include <Memory.h>" (not needed).
		 					Bracket "#include"s with "#ifndefs" so native debugger can
		 					be compiled using this file (by #defining the symbols and
							substituting its own definitions as required).
		 <4>	10/22/92	DRF		Get rid of inline glue from <3>.  Moved it to a new file,
									CodeFragmentsTrap.h.  This way we can still build GoNative, and
									only those folks who need to use the trap interface will have it
									defined.
		 <3>	10/22/92	DRF		Added inline glue for 68K to call FragCreateContext,
									FragPrepare, FragRelease, and FragRegister.
		 <2>	 10/6/92	jrc		Changed "typedef struct" syntax to agree with Sean's
									InterfaceTool.  Also changed "typedef enum".
		 <7>	 9/30/92	ELE		change TCFLProcs from typedef to struct so CFLoader.h still not
									required
		 <6>	 9/30/92	ELE		add TVersionNum type
		 <5>	 9/29/92	ELE		make Dave F. happy!
		 <4>	 9/29/92	ELE		remove include of CFLoader.h
		 <3>	 9/23/92	ELE		change tab settings
		 <2>	 9/23/92	ELE		had to add blank line onto end of file - MPW C was complaining									about illegal character
		 <1>	 9/18/92	ELE		first checked in

*/


#ifndef __CODEFRAGMENTS__

#define __CODEFRAGMENTS__ 1

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __FILES__
#include <Files.h>
#endif

#ifndef __PROCESSES__
#include <Processes.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

// typedefs that probably should be in some other system header
typedef long  TaskID;
typedef long  TeamID;
typedef long  AddressSpaceID;
typedef unsigned long LogicalAddress;     // the type used for addresses in address spaces
typedef unsigned long TVersionNum;	/* Version number */


typedef long FragContextID;               // ID’s to identify the app, agent, task or team
                                          //   to which a module should attached
typedef LogicalAddress FragConnectionID;  // the value interpreted only by the Frag
typedef unsigned long Mask;               // for flags
typedef unsigned char SymClass;           // for symbol class of export symbols

typedef OSErr FragErr;


// system & boot context value
#define kSystemFragContext 1


// default values for creating contexts
#define kDefaultTaskID (long) (GetZone ())       // unique to an app
#define kDefaultTeamID 1                         // the BLUE world
#define kDefaultAddrSpaceID 1                    // the Mac address space

enum { kDefaultContext = 0, kFragDebugApp = 1, 
       kFragDebugAll    = 2, kFragInSystem = 4 };


// values for preparing objects
enum { kDefaultPlacement,  kUseMemInPlace };
enum { kAttachStatic,      kAttachDynamic };
#define kNoLibName ((unsigned char *) 0)
#define kNoLocator ((FragmentLocatorPtr) 0)
#define kPowerPC 'pwpc'


// values for releasing contexts
#define kAllConnections ((FragConnectionID) 0)
enum { kTaskID = 1, kTeamID = 2, kAddressSpace = 4, kDefaultRelease = kTaskID };
enum { kAbnormalTerm, kNormalTerm };


// for registering libraries with Frag
enum { kAfterPMSP, kBeforePMSP };
enum { kFullLib,   kUpdateLib  };
enum { kRegister,  kUnregister };


// fragment locator description types
enum { kOnDiskFlat, kInMem, kOnDiskSegmented };

struct MemFragment {   
   Ptr         address;
   long        length;
   Boolean     inPlace;
};
typedef struct MemFragment MemFragment;


struct DiskFragment {
   FSSpecPtr   fileSpec;
   long        offset;
   long        length;
};
typedef struct DiskFragment DiskFragment;


struct SegmentedFragment {
   FSSpecPtr   fileSpec;
   OSType      rsrcType;
   short       rsrcID;
};
typedef struct SegmentedFragment SegmentedFragment;

struct FragmentLocator{
   long where;
   union {
      MemFragment  inMem;
      DiskFragment onDisk;
      SegmentedFragment inSegs;
   } u;
};
typedef struct FragmentLocator FragmentLocator, *FragmentLocatorPtr;


// search function types
enum { kAfterOthers, kBeforeOthers };

typedef FragErr (*FragSearchProcPtr) ( Str63             pNamePtr, 
                                       long              updateLevel,
                                       short             vRefNum,
                                       long              parID,
                                       TVersionNum       linkedVersion,
                                       TVersionNum       oldDefVersion,
                                       OSType            architecure,
                                       FragmentLocator  *fragLoc,
                                       Boolean          *isPrivate,
                                       long             *position );
                                    

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
                             Mask                contextFlags );
			     
FragErr FragPrepare        ( FragContextID       contextID,
                             FragmentLocatorPtr  fragLocator,
                             Str63               libName,
                             Boolean             attachDynamic,
                             OSType              architecture,
                             FragConnectionID   *connectionID,
                             LogicalAddress     *entryAddress,
                             Str63               errName );

FragErr FragRelease        ( FragContextID       contextID, 
                             FragConnectionID    connectionID,
                             Mask                releaseWhich,
                             Boolean             normalTerm );


FragErr FragRegister       ( FragmentLocatorPtr  fragLocator,
                             Boolean             beforePMSP,
                             long                updateLevel,
                             Str63               libName,
                             Boolean             unregister );

FragErr FragAddSearchFcn   ( FragSearchProcPtr   SearchFcn,
                             Boolean             callFirst );

//
// System Programmer's Interface
//
//        Functions that return information
//

struct RegisteredInfo{
   Str63   libName;
   FragmentLocator fragLocator;
};
typedef struct RegisteredInfo RegisteredInfo;


FragErr FragGetRegisterInfo   ( long             libIndex,
                                RegisteredInfo  *registerInfo );


FragErr FragResolveSymbol  ( FragContextID       contextID,
                             FragConnectionID    connectionID,
                             Str255              symbolName,
                             SymClass           *symbolClass,
                             long               *symbolIndex,
                             LogicalAddress     *symbolAddress );


struct ContextInfo {
   FragContextID    contextID;
   THz             heapZone;
   AddressSpaceID  addressSpace;
   TaskID          taskID;
   TeamID          teamID;
};
typedef struct ContextInfo ContextInfo;

FragErr FragGetContextInfo   ( FragContextID    contextID,
                               Boolean          nextContext,
                               ContextInfo     *contextInfo );


struct ConnectionInfo {
   FragConnectionID connectionID;
   OSType           loaderType;
   FragmentLocator  fragLocator;
   long             sectionCount;
   long             symbolCount;
   struct TCFLProcs *theProcs;
   struct TCFLPrivateInfo *containerInfo;
};
typedef struct ConnectionInfo ConnectionInfo;

FragErr FragGetConnectionInfo( FragContextID     contextID,
                               FragConnectionID  connectionID,
                               Boolean           nextConnection,
                               ConnectionInfo   *connectionInfo );


struct SectionInfo {
   LogicalAddress  sectionAddress;
   long            sectionLength;
   Boolean         executable;
   Boolean         writeable;
   long            shareCount;
};
typedef struct SectionInfo SectionInfo;

FragErr FragGetSectionInfo   ( FragContextID     contextID,
                               FragConnectionID  connectionID,
                               long              sectionIndex,
                               long              sectionCount,
                               SectionInfo      *sectionInfo );



#define kUnresolvedSymbolAddress 0x0

//
// Error codes and other constants
//

enum {
   fragNoErr = 0,
   fragContextNotFound        // contextID was not valid
                  = -10000,
   fragConnectionIDNotFound,  // connecionID was not valid
   fragSymbolNotFound,        // symbol was not found in connection
   fragSectionNotFound,       // section was not found
   fragLibNotFound,           // library name not found in Frag registry
   fragHadUnresolveds,        // loaded fragment had unacceptable unresolveds
   fragHadSoftUnresolveds,    // loaded fragment has acceptable unresolveds
   fragNoMem,                 // out of memory for interal bookkeeping
   fragNoAddrSpace,           // out of memory in user's address space for loadable section
   fragNoContextIDs,          // no more context id’s
   fragObjectInitSeqErr,      // order error during user initialization function invocation
   fragImportTooOld,          // import library was too old and therefore incompatible
   fragImportTooNew,          // import library was too new and therefore incompatible
   fragInitLoop,              // circularity detected in mandatory initialization order
   fragInitRtnUsageErr,       // boot library has initialization routine
   fragMgrInitErr             // error in initailization of this manager
};
typedef long FragErrors;


#define kFirstOrLastInTask 1
#define kFirstOrLastInTeam 2
#define kFirstOrLastInGroup 4

typedef OSErr ConnectionInitializationRoutine ( Mask              flags, 
                                                FragConnectionID  connectionID );
typedef void  ConnectionTerminationRoutine    ( Mask              flags, 
                                                FragConnectionID  connectionID );


#endif /* __CODEFRAGMENTS__ */



