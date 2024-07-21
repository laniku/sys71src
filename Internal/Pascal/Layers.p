{
	File:		Layers.p

	Contains:	The Layers unit is a unit shell.

	Written by:	Ed Tecot
					Pascal unit translated from Layers.h by Kevin S. MacDonell
					The whole thing redone by Randy Carr

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		<11>	 7/28/92	DCL		Moved applicationFloatKind & systemFloatKind constants out of
									the public eye and into the private Layers header file. At the
									request of TechPubs, and with moral support from Dean, Greg and
									Kenny.
		<10>	 8/28/91	JSM		Cleanup header.
		 <9>	  1/3/91	VL		(RLC) Add a new public routine RedrawAll.
		 <8>	  9/7/90	DFH		Changed SetLayerLock to GetDeskPort
		 <7>	 7/23/90	EMT		Changed IsLayerLocked to WindowType.
		 <5>	 3/16/90	DC		Added interface for CheckWindow
		 <4>	 3/15/90	ngk		Update Pascal interface to match C headers.
		 <3>	  3/7/90	DC		Changed names of some window positioning constants
		 <1>	 2/21/90	HJR		Moved from Interfaces:PInterfaces to Internal:Pascal
		 <2>	 2/20/90	DC		Added PositionWIndow, AutoPositionWindow, GetWindowState,
									SetWindowState
	   <1.3>	10/16/89	ngk		Oops! AutoIncluded too much
	   <1.2>	10/16/89	ngk		Changed it from unit file to an MPW interface file
	   <1.1>	 6/14/89	KSM		Removed compiler flag for tear off menus
	   <1.0>	  6/1/89	KSM		Pascal interface to the new Layer Manager.

}

{$IFC UNDEFINED UsingIncludes}
	{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT Layers;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingLayers}
{$SETC UsingLayers := 1}

{$I+}
{$SETC LayersIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingMemory}
	{$I Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingWindows}
	{$I Windows.p}
{$ENDC}
{$SETC UsingIncludes := LayersIncludes}

CONST

applicationFloatKind = 6;		{ floating window created by applications }
systemFloatKind = 7;			{ floating window belongs to text services }

TYPE	
		LocationControlValues = (lcMainScreen, lcParentWindowScreen, lcParentWindow);
		
		HorizontalControlValues = (hcNoHorizontalControl, hcCenter);
		
		VerticalControlValues = (vcNoVerticalControl, vcDocumentCenter, vcAlertCenter, vcStagger);
		
		CheckControlValues = (ccFrame, ccDragBar, ccContent);
		
		LayerPtr	=	GrafPtr;
		LayerPeek	=	^LayerRecord;
		LayerRecord	=	RECORD
			 port:			GrafPort;
			 windowKind:	INTEGER;
			 visible:		BOOLEAN;
			 reserved1:		BOOLEAN;
			 neverActive:	BOOLEAN;
			 reserved2:		BOOLEAN;
			 strucRgn:		RgnHandle;
			 contRgn:		RgnHandle;
			 updateRgn:		RgnHandle;
			 reserved3:		LONGINT;
			 parent:		LayerPeek;
			 auxWinHead:	AuxWinHandle;
			 reserved4:		INTEGER;
			 auxCtlHead:	AuxCtlHandle;
			 nextWindow:	WindowPeek;
			 subWindows:	WindowPeek;
			 refCon:		LONGINT;
		END;

		WindowActionProcPtr = ProcPtr; { Action(window: WindowPeek; parent: LayerPeek; callBackPtr: Ptr); }
		


		FUNCTION NewLayer(VAR lStorage: LayerPtr; visible, neverActive: BOOLEAN; behind: WindowPtr; refCon: LONGINT): OsErr;
			INLINE $7001,$A829;
			
		FUNCTION IsLayer( window: WindowPtr ): BOOLEAN;
			INLINE $7002,$A829;
			
		FUNCTION GetCurLayer: LayerPtr;
			INLINE $7003,$A829;
			
		PROCEDURE SetCurLayer( layer: LayerPtr );
			INLINE $7004,$A829;
			
		FUNCTION SwapCurLayer( layer: LayerPtr ): LayerPtr;
			INLINE $7005,$A829;
			
		FUNCTION GetSubWindows( layer: LayerPtr ): WindowPeek;
			INLINE $7006,$A829;
			
		FUNCTION FindLayer(pt: Point; VAR window: WindowPtr): OSErr;
			INLINE $7007,$A829;
			
		PROCEDURE PositionWindow(whichWindow: WindowPtr; referenceRect: Rect;
								findScreen: BOOLEAN;
								horizontalControl: HorizontalControlValues;
								verticalControl: VerticalControlValues);
			INLINE $7008,$A829;
			
		PROCEDURE AutoPositionWindow(whichWindow: WindowPtr; where: LocationControlValues;
								horizontalControl: HorizontalControlValues;
								verticalControl: VerticalControlValues);
			INLINE $7009,$A829;
			
		FUNCTION GetWindowState(whichWindow: WindowPtr; windState: Handle;
								VAR infoSize: Size): OSErr;
			INLINE $700A,$A829;
			
		FUNCTION SetWindowState(whichWindow: WindowPtr; windState: Handle): OSErr;
			INLINE $700B,$A829;
	
		FUNCTION CheckWindow(whichWindow: WindowPtr;
							checkControl: CheckControlValues;
							entirelyOnScreen: BOOLEAN): BOOLEAN;
			INLINE $700C,$A829;
	
		PROCEDURE RedrawAll;
			INLINE $700D,$A829;
			
		{ Beginning of private Layer interfaces }

		FUNCTION InitLayers: OSErr;
			INLINE $7000,$A829;
			
		FUNCTION GetRootLayer: LayerPtr;
			INLINE $70FF,$A829;
			
		FUNCTION ActiveWindow: WindowPtr;
			INLINE $70FE,$A829;
			
		PROCEDURE FrontWindowIn(layer: LayerPtr);
			INLINE $70FD,$A829;
			
		FUNCTION CheckUpdateIn(VAR event: EventRecord; layer: LayerPtr): LayerPtr;
			INLINE $70FC,$A829;
			
		FUNCTION GetDeskPort(VAR port: GrafPtr): OSErr;
			INLINE $70FB,$A829;
			
		FUNCTION WindowType(window: WindowPtr): INTEGER;
			INLINE $70FA,$A829;
			
		FUNCTION GetParent(window: WindowPtr): LayerPeek;
			INLINE $70F9,$A829;

		FUNCTION EachWindow(start,stop: WindowPeek; parent: LayerPeek;
							action: WindowActionProcPtr;  callBackPtr: Ptr): LayerPeek;
			INLINE $70F8,$A829;

 {$ENDC}    { UsingLayers }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}


