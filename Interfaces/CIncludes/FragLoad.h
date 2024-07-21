/*
	File:		FragLoad.h

	Contains:	CFM Public API

	Written by:	Erik Eidt, Alan Lillich, Jeff Cobb

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<15>	 6/16/93	ELE		(with AWL) Added new error code for UserInitProcFailure.
		<14>	  6/9/93	jrc		(with SP) In the CFMTrap macro, remove the cast of (arg) to
									signed short. This was confusing the interfacer.
		<13>	  6/9/93	EPT		Changes for Universal Headers. Synched up with Reality.
		<12>	  6/5/93	BT		(With JRG) "#ifndef interface_glue" should only be bracketing
									the prototypes, not the type information.  This was causing a
									problem for ProcessesPriv.h where Eric was expecting some type
									information to be available.
		<11>	 5/10/93	jrc		Make C++ Happy.
		<10>	  4/7/93	jrc		Use symbolic names for the MixedMode and CFM A-traps.
		 <9>	 3/17/93	JRG		Change how procinfos are constructed
		 <8>	  3/4/93	AWL		Change to "pascal" routines for Dagon.
		 <7>	  3/2/93	jrc		Fix Erik's fixes. "FourBytes" not "FourByte".
		 <6>	 3/2/93		ELE		Fixed two typo's in proc infos.
		 <5>	 2/18/93	ELE		Moved a bunch of stuff into here
		                               from CodeFragments.h
		 <4>	 2/15/93	ELE		Added kAnyArchType.
		 <3>	 1/28/93	jrc		Rev for d4 MixedMode.

*/

/*******************************************************************************

FILENAME
    FragLoad.h

COPYRIGHT
    Copyright © Apple Computer, Inc. 1992
    All rights reserved.

*******************************************************************************/


#ifndef __FRAGLOAD__
#define __FRAGLOAD__ 1


#include <Types.h>
#include <Files.h>
#include <Traps.h>

typedef long			ConnectionID;
typedef unsigned long	Mask;
typedef unsigned char	SymClass;

#define kPowerPC 'pwpc'	// use as the architecture type
#define kAnyArchType 0x3f3f3f3f // '????'

#define kNoLibName					((unsigned char *) 0)
#define kNoConnectionID				((ConnectionID) 0)
#define kUnresolvedSymbolAddress	((Ptr) 0x0)

enum {	// use for findFlags mask
        kLoadLib		= 1,	// use existing connection if possible
        kFindLib		= 2,	// just see if library is already loaded
        kLoadNewCopy	= 5,	// load a new instance no matter what
		kUseInPlace		= 0x80	// use container's sections in place
};

enum {
      kCodeSym   = 0,
      kDataSym   = 1,
      kTVectSym  = 2,
      kTOCSym    = 3,
      kGlueSym   = 4
};



/************************************************************************/
/*         for fragment initialization routines                         */
/************************************************************************/

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

struct FragmentLocator {
   long where;
   union {
      MemFragment  inMem;
      DiskFragment onDisk;
      SegmentedFragment inSegs;
   } u;
};
typedef struct FragmentLocator FragmentLocator, *FragmentLocatorPtr;


// NOTE: when fragLocator. where == kOnDisk, then
//       fragLocator. u. onDisk. fileSpec is a pointer
//       to the file that the library belonged to.
//       the pointer is valid only for the duration
//       of the init routine's invocation, so make
//       a copy of the filespec if it is important
struct InitBlock {
   long              contextID;
   long              closureID;
   long              connectionID;
   FragmentLocator   fragLocator;
   Ptr               libName;
   long              reserved4a;
   long              reserved4b;
   long              reserved4c;
   long              reserved4d;
};
typedef struct InitBlock InitBlock, *InitBlockPtr;


// prototype for initialization routines
// Pascal calling conventions
// NOTE: initialization routines may comfortably ignore
//       their parameters, however, they must return 
//       an error status (ie: noErr) in order to succeed
//       with the load of the library
typedef pascal OSErr ConnectionInitializationRoutine ( InitBlockPtr initBlkPtr );

// termination routines get no parameters / return value
// Pascal calling conventions
typedef pascal void  ConnectionTerminationRoutine    ( void );


/************************************************************************/
/*                for building shared libraries                         */
/************************************************************************/

#define kCFMRsrcType 'cfrg'
#define kSHLBFileType 'shlb'


/************************************************************************/
/*                error codes                                           */
/************************************************************************/

enum {
   fragNoErr                   =     0,
   fragContextNotFound         = -2800,   // contextID was not valid
   fragConnectionIDNotFound    = -2801,   // connecionID was not valid
   fragSymbolNotFound          = -2802,   // symbol was not found in connection
   fragSectionNotFound         = -2803,   // section was not found
   fragLibNotFound             = -2804,   // library name not found in Frag registry
   fragDupRegLibName           = -2805,   // registered name already in use
   fragFormatUnknown           = -2806,   // fragment container format unknown
   fragHadUnresolveds          = -2807,   // loaded fragment had unacceptable unresolveds
   fragHadSoftUnresolveds      = -2808,   // loaded fragment has acceptable unresolveds
   fragNoMem                   = -2809,   // out of memory for interal bookkeeping
   fragNoAddrSpace             = -2810,   // out of memory in user's address space for loadable section
   fragNoContextIDs            = -2811,   // no more context id’s
   fragObjectInitSeqErr        = -2812,   // order error during user initialization function invocation
   fragImportTooOld            = -2813,   // import library was too old and therefore incompatible
   fragImportTooNew            = -2814,   // import library was too new and therefore incompatible
   fragInitLoop                = -2815,   // circularity detected in mandatory initialization order
   fragInitRtnUsageErr         = -2816,   // boot library has initialization routine
   fragLibConnErr              = -2817,   // error connecting to library (error occured in sub prepare)
   fragMgrInitErr              = -2818,   // error in initailization of this manager
   fragConstErr                = -2819,   // internal inconstistancy
   fragCorruptErr              = -2820,   // fragment container corrupted (known format)
   fragUserInitProcErr         = -2821,   // user intialization routine did not return noErr
   fragLastErrCode             = -2899    // last reserved error code number
};


#if TurnOff68KCFMTraps || __powerc || powerc
#define CFMTrap(arg) /* don't want trap: 68k-code to link directly */
#else
#define CFMTrap(arg) = { 0x3F3C, arg, _CodeFragmentDispatch }
#endif

#ifdef __cplusplus
extern "C" {
#endif


pascal OSErr GetSharedLibrary ( Str63         libName,
                                OSType        archType,
                                Mask          findFlags,
                                ConnectionID *connID,
                                Ptr          *mainAddr,
                                Str255        errName )
		CFMTrap ( 1 );

#define GetSharedLibraryProcInfo				\
		(kPascalStackBased			|			\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode) |	\
		STACK_PARAM_FIELD(3, kFourByteCode) |	\
		STACK_PARAM_FIELD(4, kFourByteCode) |	\
		STACK_PARAM_FIELD(5, kFourByteCode) |	\
		STACK_PARAM_FIELD(6, kFourByteCode))


pascal OSErr GetDiskFragment   ( FSSpecPtr     fileSpec,
						         long		   offset,
						         long		   length,
						         Str63		   fragName,
                                 Mask          findFlags,
                                 ConnectionID *connID,
                                 Ptr          *mainAddr,
                                 Str255        errName )
		CFMTrap ( 2 );

#define GetDiskFragmentProcInfo			\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode) |	\
		STACK_PARAM_FIELD(3, kFourByteCode) |	\
		STACK_PARAM_FIELD(4, kFourByteCode) |	\
		STACK_PARAM_FIELD(5, kFourByteCode) |	\
		STACK_PARAM_FIELD(6, kFourByteCode) |	\
		STACK_PARAM_FIELD(7, kFourByteCode) |	\
		STACK_PARAM_FIELD(8, kFourByteCode))


pascal OSErr GetMemFragment    ( Ptr           memAddr,
                                 long          length,
						         Str63		   fragName,
                                 Mask          findFlags,
                                 ConnectionID *connID,
                                 Ptr          *mainAddr,
                                 Str255        errName )
		CFMTrap ( 3 );

#define GetMemFragmentProcInfo			\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode) |	\
		STACK_PARAM_FIELD(3, kFourByteCode) |	\
		STACK_PARAM_FIELD(4, kFourByteCode) |	\
		STACK_PARAM_FIELD(5, kFourByteCode) |	\
		STACK_PARAM_FIELD(6, kFourByteCode) |	\
		STACK_PARAM_FIELD(7, kFourByteCode))


pascal OSErr CloseConnection   ( ConnectionID  *connID )
		CFMTrap ( 4 );

#define CloseConnectionProcInfo		\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode))


pascal OSErr FindSymbol        ( ConnectionID  connID,
                                 Str255        symName,
                                 Ptr          *symAddr,
                                 SymClass     *symClass )
		CFMTrap ( 5 );

#define FindSymbolProcInfo				\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode) |	\
		STACK_PARAM_FIELD(3, kFourByteCode) |	\
		STACK_PARAM_FIELD(4, kFourByteCode))

    
pascal OSErr CountSymbols      ( ConnectionID  connID,
                                 long         *symCount )
		CFMTrap ( 6 );

#define CountSymbolsProcInfo			\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode))


pascal OSErr GetIndSymbol      ( ConnectionID  connID,
                                 long		   symIndex,
                                 Str255        symName,
                                 Ptr          *symAddr,
                                 SymClass     *symClass )
		CFMTrap ( 7 );

#define GetIndSymbolProcInfo			\
		(kPascalStackBased			|	\
		STACK_RESULT_FIELD(kTwoByteCode) |		\
		STACK_PARAM_FIELD(1, kFourByteCode) |	\
		STACK_PARAM_FIELD(2, kFourByteCode) |	\
		STACK_PARAM_FIELD(3, kFourByteCode) |	\
		STACK_PARAM_FIELD(4, kFourByteCode) |	\
		STACK_PARAM_FIELD(5, kFourByteCode))


#ifdef __cplusplus
}
#endif

#endif
