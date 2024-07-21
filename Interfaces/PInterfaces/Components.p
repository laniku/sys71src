{
	File:		Components.p

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1991-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <4>	11/17/92	PKE		Fix broken System build: Add missing parenthesis in
									ComponentSetTarget.
		 <3>	11/13/92	JDR		Updated to the QuickTime 1.5 release of the interfaces.  General
									rearrangement of the stuff too.
		 <2>	11/23/91	YK		Removed gestaltComponentMgr.  It's already in GestaltEqu.p.
		 <1>	11/21/91	JH		first checked in

}


{
Created: Wednesday, August 14, 1991 at 12:11 PM
 Components.p
 Pascal Interface to the Macintosh Libraries

 Copyright Apple Computer, Inc. 1990 - 1991
 All rights reserved

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Components;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingComponents}
{$SETC UsingComponents := 1}

{$I+}
{$SETC ComponentsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := ComponentsIncludes}

CONST
kAnyComponentType =			0;
kAnyComponentSubType = 		0;
kAnyComponentManufacturer =	0;
kAnyComponentFlagsMask =	0;

cmpWantsRegisterMessage = $80000000;

kComponentOpenSelect = -1;							{ComponentInstance for this open}
kComponentCloseSelect = -2;							{ComponentInstance for this close}
kComponentCanDoSelect = -3;							{selector # being queried}
kComponentVersionSelect = -4;						{no params}
kComponentRegisterSelect = -5;						{no params}
kComponentTargetSelect = -6;						{ComponentInstance for top of call chain}


defaultComponentIdentical = 0;						{Set Default Component flags}
defaultComponentAnyFlags = 1;
defaultComponentAnyManufacturer = 2;
defaultComponentAnySubType = 4;
defaultComponentAnyFlagsAnyManufacturer = defaultComponentAnyFlags+defaultComponentAnyManufacturer;
defaultComponentAnyFlagsAnyManufacturerAnySubType = defaultComponentAnyFlags+defaultComponentAnyManufacturer+defaultComponentAnySubType;

TYPE
ComponentDescription = RECORD
 componentType: OSType;								{A unique 4-byte code indentifying the command set}
 componentSubType: OSType;							{Particular flavor of this instance}
 componentManufacturer: OSType;						{Vendor indentification}
 componentFlags: LONGINT;							{8 each for Component,Type,SubType,Manuf/revision}
 componentFlagsMask: LONGINT;						{Mask for specifying which flags to consider in search, zero during registration}
 END;

ResourceSpec = RECORD
 resType: OSType;									{4-byte code }
 resId: INTEGER;									{  }
 END;

ComponentResourcePtr = ^ComponentResource;
ComponentResourceHandle = ^ComponentResourcePtr;
ComponentResource = RECORD
 cd: ComponentDescription;							{Registration parameters}
 component: ResourceSpec;							{resource where Component code is found}
 componentName: ResourceSpec;						{name string resource}
 componentInfo: ResourceSpec;						{info string resource}
 componentIcon: ResourceSpec;						{icon resource}
 END;

{Structure received by Component: }
ComponentParameters = PACKED RECORD
 flags: CHAR;										{call modifiers: sync/async, deferred, immed, etc}
 paramSize: CHAR;									{size in bytes of actual parameters passed to this call}
 what: INTEGER;										{routine selector, negative for Component management calls}
 params: ARRAY [0..0] OF LONGINT;					{actual parameters for the indicated routine}
 END;


Component = ^ComponentRecord;
ComponentRecord = RECORD
 data: ARRAY [0..0] OF LONGINT;
 END;

ComponentInstance = ^ComponentInstanceRecord;
ComponentInstanceRecord = RECORD
 data: ARRAY [0..0] OF LONGINT;
 END;

ComponentResult = LONGINT;

ComponentRoutine = LONGINT;

ComponentFunction = LONGINT;



{*******************************************************
*                                                     *
*              APPLICATION LEVEL CALLS                *
*                                                     *
*******************************************************
* Component Database Add, Delete, and Query Routines
*******************************************************
}
FUNCTION RegisterComponent(cd: ComponentDescription;componentEntryPoint: ComponentRoutine;
 global: INTEGER;componentName: Handle;componentInfo: Handle;componentIcon: Handle): Component;
 INLINE $7001,$A82A;
FUNCTION RegisterComponentResource(tr: ComponentResourceHandle;global: INTEGER): Component;
 INLINE $7012,$A82A;
FUNCTION UnregisterComponent(aComponent: Component): OSErr;
 INLINE $7002,$A82A;

FUNCTION FindNextComponent(aComponent: Component;looking: ComponentDescription): Component;
 INLINE $7004,$A82A;
FUNCTION CountComponents(looking: ComponentDescription): LONGINT;
 INLINE $7003,$A82A;

FUNCTION GetComponentInfo(aComponent: Component;cd: ComponentDescription;
 componentName: Handle;componentInfo: Handle;componentIcon: Handle): OSErr;
 INLINE $7005,$A82A;
FUNCTION GetComponentListModSeed: LONGINT;
 INLINE $7006,$A82A;


{*******************************************************
* Component Instance Allocation and dispatch routines
*******************************************************
}
FUNCTION OpenComponent(aComponent: Component): ComponentInstance;
 INLINE $7007,$A82A;
FUNCTION CloseComponent(aComponentInstance: ComponentInstance): OSErr;
 INLINE $7008,$A82A;

FUNCTION GetComponentInstanceError(aComponentInstance: ComponentInstance): OSErr;
 INLINE $700A,$A82A;


{ direct calls to the Components }
FUNCTION ComponentFunctionImplemented(ci: ComponentInstance;ftnNumber: INTEGER): LONGINT;
 INLINE $2F3C,$2,$FFFD,$7000,$A82A;
FUNCTION GetComponentVersion(ci: ComponentInstance): LONGINT;
 INLINE $2F3C,$0,$FFFC,$7000,$A82A;
FUNCTION ComponentSetTarget(ci: ComponentInstance;target: ComponentInstance): LONGINT;
 INLINE $2F3C,$4,$FFFA,$7000,$A82A;

{****************************************************
*                                                    *
*               CALLS MADE BY Components             *
*                                                    *
******************************************************}


{*******************************************************
* Component Management routines
*******************************************************
}
PROCEDURE SetComponentInstanceError(aComponentInstance: ComponentInstance;
 theError: OSErr);
 INLINE $700B,$A82A;

FUNCTION GetComponentRefcon(aComponent: Component): LONGINT;
 INLINE $7010,$A82A;
PROCEDURE SetComponentRefcon(aComponent: Component;theRefcon: LONGINT);
 INLINE $7011,$A82A;

FUNCTION OpenComponentResFile(aComponent: Component): INTEGER;
 INLINE $7015,$A82A;
FUNCTION CloseComponentResFile(refnum: INTEGER): OSErr;
 INLINE $7018,$A82A;


{*******************************************************
* Component Instance Management routines
*******************************************************
}
FUNCTION GetComponentInstanceStorage(aComponentInstance: ComponentInstance): Handle;
 INLINE $700C,$A82A;
PROCEDURE SetComponentInstanceStorage(aComponentInstance: ComponentInstance;
 theStorage: Handle);
 INLINE $700D,$A82A;

FUNCTION GetComponentInstanceA5(aComponentInstance: ComponentInstance): LONGINT;
 INLINE $700E,$A82A;
PROCEDURE SetComponentInstanceA5(aComponentInstance: ComponentInstance;
 theA5: LONGINT);
 INLINE $700F,$A82A;

FUNCTION CountComponentInstances(aComponent: Component): LONGINT;
 INLINE $7013,$A82A;

{ useful helper routines for convenient method dispatching }
FUNCTION CallComponentFunction(params: ComponentParameters;func: ComponentFunction): LONGINT;
 INLINE $70FF,$A82A;
FUNCTION CallComponentFunctionWithStorage(storage: Handle;params: ComponentParameters;
 func: ComponentFunction): LONGINT;
 INLINE $70FF,$A82A;
FUNCTION DelegateComponentCall(originalParams: ComponentParameters;
 ci: ComponentInstance): LONGINT;
 INLINE $7024,$A82A;


FUNCTION SetDefaultComponent(aComponent: Component;flags: INTEGER): OSErr;
 INLINE $701E,$A82A;
FUNCTION  OpenDefaultComponent(componentType: OSType; componentSubType: OSType ) : ComponentInstance;
 INLINE $7021,$A82A;
FUNCTION CaptureComponent(capturedComponent: Component;capturingComponent: Component): Component;
 INLINE $701C,$A82A;
FUNCTION UncaptureComponent(aComponent: Component): OSErr;
 INLINE $701D,$A82A;
FUNCTION RegisterComponentResourceFile(resRefNum: INTEGER;global: INTEGER): LONGINT;
 INLINE $7014,$A82A;


{$ENDC} {UsingComponents}

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

