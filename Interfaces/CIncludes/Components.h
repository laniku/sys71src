/*
	File:		Components.h

	Contains:	Component Manager API

	Copyright:	© 1991-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	 9/22/93	JDR		corrected misspelling of componentHasMultiplePlatforms
	   <SM5>	 9/14/93	JDR		Updated for native component support, and a few other minor
									things for version 3 component manager.
		 <5>	  6/2/93	DTY		Synch up with NuReality version of this file.
		 <4>	 2/24/93	JDR		Added kAppleManufacturer.
		 <3>	11/13/92	JDR		Updated to the QuickTime 1.5 release of the interfaces.  General
									rearrangement of the stuff too.
		 <2>	11/23/91	YK		Removed gestaltComponentMgr.  It's already in GestaltEqu.h.
		 <1>	11/21/91	JH		first checked in

*/


#ifndef __COMPONENTS__
#define __COMPONENTS__

#ifndef __TYPES__
#include <Types.h>
#endif

enum {
#define kAppleManufacturer 'appl'		/*Apple supplied components*/
#define kComponentResourceType 'thng'	/*a components resource type*/

 kSmallestArray = 1,

 kAnyComponentType = 0,
 kAnyComponentSubType = 0,
 kAnyComponentManufacturer = 0,
 kAnyComponentFlagsMask = 0,

 cmpWantsRegisterMessage = 1L<<31,

 kComponentOpenSelect = -1,				/*ComponentInstance for this open*/
 kComponentCloseSelect = -2,			/*ComponentInstance for this close*/
 kComponentCanDoSelect = -3,			/*selector # being queried*/
 kComponentVersionSelect = -4,			/*no params*/
 kComponentRegisterSelect = -5,			/*no params*/
 kComponentTargetSelect = -6,			/*ComponentInstance for top of call chain*/
 kComponentUnregisterSelect = -7,		/*no params*/

/*Component Resource Extension flags*/
 componentDoAutoVersion = (1<<0),
 componentWantsUnregister = (1<<1),
 componentAutoVersionIncludeFlags = (1<<2),
 componentHasMultiplePlatforms = (1<<3),

/*Set Default Component flags*/
 defaultComponentIdentical = 0,
 defaultComponentAnyFlags = (1<<0),
 defaultComponentAnyManufacturer = (1<<1),
 defaultComponentAnySubType = (1<<2),
 defaultComponentAnyFlagsAnyManufacturer = (defaultComponentAnyFlags+defaultComponentAnyManufacturer),
 defaultComponentAnyFlagsAnyManufacturerAnySubType = (defaultComponentAnyFlags+defaultComponentAnyManufacturer+defaultComponentAnySubType)
};

struct ComponentDescription {
 OSType componentType;					/*A unique 4-byte code indentifying the command set*/
 OSType componentSubType;				/*Particular flavor of this instance*/
 OSType componentManufacturer;			/*Vendor indentification*/
 unsigned long componentFlags;			/*8 each for Component,Type,SubType,Manuf/revision*/
 unsigned long componentFlagsMask;		/*Mask for specifying which flags to consider in search, zero during registration*/
};
typedef struct ComponentDescription ComponentDescription;

struct ResourceSpec {
 OSType resType;						/*4-byte code*/
 short resId;
};
typedef struct ResourceSpec ResourceSpec;

struct ComponentResource {
 ComponentDescription cd;				/*Registration parameters*/
 ResourceSpec component;				/*resource where Component code is found*/
 ResourceSpec componentName;			/*name string resource*/
 ResourceSpec componentInfo;			/*info string resource*/
 ResourceSpec componentIcon;			/*icon resource*/
};
typedef struct ComponentResource ComponentResource;
typedef ComponentResource *ComponentResourcePtr, **ComponentResourceHandle;

struct ComponentPlatformInfo {
 long componentFlags;					/*flags of Component*/
 ResourceSpec component;				/*resource where Component code is found*/
 short platformType;					/*gestaltSysArchitecture result*/
};
typedef struct ComponentPlatformInfo ComponentPlatformInfo;

struct ComponentResourceExtension {
 long componentVersion;					/*version of Component*/
 long componentRegisterFlags;			/*flags for registration*/
 short componentIconFamily;				/*resource id of Icon Family*/
};
typedef struct ComponentResourceExtension ComponentResourceExtension;

struct ComponentPlatformInfoArray {
 long count;
 ComponentPlatformInfo platformArray[1];
};
typedef struct ComponentPlatformInfoArray ComponentPlatformInfoArray;

struct ExtComponentResource {
 ComponentDescription cd;				/*Registration parameters*/
 ResourceSpec component;				/*resource where Component code is found*/
 ResourceSpec componentName;			/*name string resource*/
 ResourceSpec componentInfo;			/*info string resource*/
 ResourceSpec componentIcon;			/*icon resource*/
 long componentVersion;					/*version of Component*/
 long componentRegisterFlags;			/*flags for registration*/
 short componentIconFamily;				/*resource id of Icon Family*/
 long count;							/*elements in platformArray*/
 ComponentPlatformInfo platformArray[1];
};
typedef struct ExtComponentResource ExtComponentResource;

struct ComponentParameters {
 unsigned char flags;					/*call modifiers: sync/async, deferred, immed, etc*/
 unsigned char paramSize;				/*size in bytes of actual parameters passed to this call*/
 short what;							/*routine selector, negative for Component management calls*/
 long params[kSmallestArray];			/*actual parameters for the indicated routine*/
};
typedef struct ComponentParameters ComponentParameters;

struct ComponentRecord {
 long data[1];
};
typedef struct ComponentRecord ComponentRecord;
typedef ComponentRecord *Component;

struct ComponentInstanceRecord {
 long data[1];
};
typedef struct ComponentInstanceRecord ComponentInstanceRecord;
typedef ComponentInstanceRecord *ComponentInstance;

typedef long ComponentResult;

#pragma procname ComponentRoutine
typedef pascal ComponentResult (*ComponentRoutineProcPtr)(ComponentParameters *cp,Handle componentStorage);
typedef ComponentRoutineProcPtr ComponentRoutine;

#pragma procname ComponentFunction
typedef pascal ComponentResult (*ComponentFunctionProcPtr)(void);
typedef ComponentFunctionProcPtr ComponentFunction;

#define ComponentCallNow( callNumber, paramSize ) \
  {0x2F3C,paramSize,callNumber,0x7000,0xA82A}


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************
 * Component Database Add, Delete, and Query Routines
 ********************************************************/

pascal Component RegisterComponent(ComponentDescription *cd,ComponentRoutineProcPtr componentEntryPoint,
 short global,Handle componentName,Handle componentInfo,Handle componentIcon)
 = {0x7001,0xA82A};
pascal Component RegisterComponentResource(ComponentResourceHandle tr,short global)
 = {0x7012,0xA82A};
pascal OSErr UnregisterComponent(Component aComponent)
 = {0x7002,0xA82A};

pascal Component FindNextComponent(Component aComponent,ComponentDescription *looking)
 = {0x7004,0xA82A};
pascal long CountComponents(ComponentDescription *looking)
 = {0x7003,0xA82A};

pascal OSErr GetComponentInfo(Component aComponent,ComponentDescription *cd,
 Handle componentName,Handle componentInfo,Handle componentIcon)
 = {0x7005,0xA82A};
pascal long GetComponentListModSeed(void)
 = {0x7006,0xA82A};


/********************************************************
 * Component Instance Allocation and dispatch routines
 ********************************************************/

pascal ComponentInstance OpenComponent(Component aComponent)
 = {0x7007,0xA82A};
pascal OSErr CloseComponent(ComponentInstance aComponentInstance)
 = {0x7008,0xA82A};

pascal OSErr GetComponentInstanceError(ComponentInstance aComponentInstance)
 = {0x700A,0xA82A};

/*direct calls to the Components*/
pascal long ComponentFunctionImplemented(ComponentInstance ci,short ftnNumber)
 = {0x2F3C,0x2,0xFFFD,0x7000,0xA82A};
pascal long GetComponentVersion(ComponentInstance ci)
 = {0x2F3C,0x0,0xFFFC,0x7000,0xA82A};
pascal long ComponentSetTarget(ComponentInstance ci,ComponentInstance target)
 = {0x2F3C,0x4,0xFFFA,0x7000,0xA82A};
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************
 * Component Management routines
 ********************************************************/

pascal void SetComponentInstanceError(ComponentInstance aComponentInstance,
 OSErr theError)
 = {0x700B,0xA82A};

pascal long GetComponentRefcon(Component aComponent)
 = {0x7010,0xA82A};
pascal void SetComponentRefcon(Component aComponent,long theRefcon)
 = {0x7011,0xA82A};

pascal short OpenComponentResFile(Component aComponent)
 = {0x7015,0xA82A};
pascal OSErr CloseComponentResFile(short refnum)
 = {0x7018,0xA82A};

/********************************************************
 * Component Instance Management routines
 ********************************************************/

pascal Handle GetComponentInstanceStorage(ComponentInstance aComponentInstance)
 = {0x700C,0xA82A};
pascal void SetComponentInstanceStorage(ComponentInstance aComponentInstance,Handle theStorage)
 = {0x700D,0xA82A};

pascal long GetComponentInstanceA5(ComponentInstance aComponentInstance)
 = {0x700E,0xA82A};
pascal void SetComponentInstanceA5(ComponentInstance aComponentInstance,long theA5)
 = {0x700F,0xA82A};

pascal long CountComponentInstances(Component aComponent)
 = {0x7013,0xA82A};

/*useful helper routines for convenient method dispatching*/
pascal long CallComponentFunction(ComponentParameters *params,ComponentFunctionProcPtr func)
 = {0x70FF,0xA82A};
pascal long CallComponentFunctionWithStorage(Handle storage,ComponentParameters *params,
 ComponentFunctionProcPtr func)
 = {0x70FF,0xA82A};
pascal long DelegateComponentCall(ComponentParameters *originalParams,ComponentInstance ci)
 = {0x7024,0xA82A};
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
pascal OSErr SetDefaultComponent(Component aComponent,short flags)
 = {0x701E,0xA82A};
pascal ComponentInstance OpenDefaultComponent( OSType componentType, OSType componentSubType )
 = {0x7021,0xA82A};
pascal Component CaptureComponent(Component capturedComponent,Component capturingComponent)
 = {0x701C,0xA82A};
pascal OSErr UncaptureComponent(Component aComponent)
 = {0x701D,0xA82A};
pascal long RegisterComponentResourceFile(short resRefNum, short global)
 = {0x7014,0xA82A};
pascal OSErr GetComponentIconSuite(Component aComponent, Handle *iconSuite)
 = {0x7029,0xA82A};

#ifdef __cplusplus
}
#endif


#endif
