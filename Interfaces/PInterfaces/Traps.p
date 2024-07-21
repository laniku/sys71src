
{
Created: Tuesday, July 23, 1991 at 4:27 PM
 Traps.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved

	Change History (most recent first):

		 <5>	 3/30/93	IH		Add Display Manager Trap
		<15>	10/16/92	DTY		Add BlockMoveData.
		<14>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<13>	 3/10/92	DCL		For New Improved Inside Mac: Added Call names without Abbrevs.:
									SecsToDate (Secs2Date) and DateToSecs (Date2Secs). Affected
									Files: OSUtils.[ph], Traps.[aph].
		<12>	  3/9/92	DCL		For New Improved Inside Mac: Added Call names without Abbrevs.:
									AppendResMenu (AddResMenu), DeleteMCEntries (DelMCEntries),
									DeleteMenuItem (DelMenuItem), DisposeMCInfo (DispMCInfo),
									GetMenuHandle (GetMHandle), InsertMenuItem (InsMenuItem),
									SetMenuItemText (SetItem), GetMenuItemText (GetItem). Affected
									Files: Menus.[ph], Traps.[aph].
		<11>	 2/18/92	MH		Replace contents with ETO 6 file which matches Traps.a in order
									and content. This should make it easier to keep the Traps.a,
									Traps.h and Traps.p in synch, especially if the interfaces data
									base is used to do so. Move _ComponentDispatch and add
									_PowerDispatch to match the current BBS version of Traps.a.
		<10>	 7/23/91	JL		Checked in Database generated file from DSG. Matched C header:
									Changed ReAllocHandle to ReallocHandle. Moved VInstall and
									CommToolboxDispatch.
		 <9>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Added _GestaltDispatch
									Trap to be consistent with C header.
		 <8>	12/14/90	dba		<JDR> add new Memory Manager traps; coming soon, restructuring
									the whole file and making it match Traps.a and Traps.h
		 <7>	 10/3/90	JAL		Added HCreateResFile and HOpenResFile. Lots more to do.
		 <6>	 9/14/90	csd		Added DeviceLoop
		 <5>	  8/6/90	dnf		Add HFSPinaforeDispatch
		 <4>	  4/5/90	KSM		Added the InvalMenuBar trap $A81D.
		 <3>	 3/16/90	BBH		add CommToolboxDispatch

}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Traps;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingTraps}
{$SETC UsingTraps := 1}


CONST

{ 
; QuickDraw

 }
_CopyMask = $A817;
_MeasureText = $A837;
_GetMaskTable = $A836;
_CalcMask = $A838;
_SeedFill = $A839;
_InitCursor = $A850;
_SetCursor = $A851;
_HideCursor = $A852;
_ShowCursor = $A853;
_ShieldCursor = $A855;
_ObscureCursor = $A856;
_BitAnd = $A858;
_BitXOr = $A859;
_BitNot = $A85A;
_BitOr = $A85B;
_BitShift = $A85C;
_BitTst = $A85D;
_BitSet = $A85E;
_BitClr = $A85F;
_Random = $A861;
_ForeColor = $A862;
_BackColor = $A863;
_ColorBit = $A864;
_GetPixel = $A865;
_StuffHex = $A866;
_LongMul = $A867;
_FixMul = $A868;
_FixRatio = $A869;
_HiWord = $A86A;
_LoWord = $A86B;
_FixRound = $A86C;
_InitPort = $A86D;
_InitGraf = $A86E;
_OpenPort = $A86F;
_LocalToGlobal = $A870;
_GlobalToLocal = $A871;
_GrafDevice = $A872;
_SetPort = $A873;
_GetPort = $A874;
_SetPBits = $A875;
_PortSize = $A876;
_MovePortTo = $A877;
_SetOrigin = $A878;
_SetClip = $A879;
_GetClip = $A87A;
_ClipRect = $A87B;
_BackPat = $A87C;
_ClosePort = $A87D;
_AddPt = $A87E;
_SubPt = $A87F;
_SetPt = $A880;
_EqualPt = $A881;
_StdText = $A882;
_DrawChar = $A883;
_DrawString = $A884;
_DrawText = $A885;
_TextWidth = $A886;
_TextFont = $A887;
_TextFace = $A888;
_TextMode = $A889;
_TextSize = $A88A;
_GetFontInfo = $A88B;
_StringWidth = $A88C;
_CharWidth = $A88D;
_SpaceExtra = $A88E;
_StdLine = $A890;
_LineTo = $A891;
_Line = $A892;
_MoveTo = $A893;
_Move = $A894;
_ShutDown = $A895;
_HidePen = $A896;
_ShowPen = $A897;
_GetPenState = $A898;
_SetPenState = $A899;
_GetPen = $A89A;
_PenSize = $A89B;
_PenMode = $A89C;
_PenPat = $A89D;
_PenNormal = $A89E;
_Unimplemented = $A89F;
_StdRect = $A8A0;
_FrameRect = $A8A1;
_PaintRect = $A8A2;
_EraseRect = $A8A3;
_InverRect = $A8A4;
_FillRect = $A8A5;
_EqualRect = $A8A6;
_SetRect = $A8A7;
_OffsetRect = $A8A8;
_InsetRect = $A8A9;
_SectRect = $A8AA;
_UnionRect = $A8AB;
_Pt2Rect = $A8AC;
_PtInRect = $A8AD;
_EmptyRect = $A8AE;
_StdRRect = $A8AF;
_FrameRoundRect = $A8B0;
_PaintRoundRect = $A8B1;
_EraseRoundRect = $A8B2;
_InverRoundRect = $A8B3;
_FillRoundRect = $A8B4;
_StdOval = $A8B6;
_FrameOval = $A8B7;
_PaintOval = $A8B8;
_EraseOval = $A8B9;
_InvertOval = $A8BA;
_FillOval = $A8BB;
_SlopeFromAngle = $A8BC;
_StdArc = $A8BD;
_FrameArc = $A8BE;
_PaintArc = $A8BF;
_EraseArc = $A8C0;
_InvertArc = $A8C1;
_FillArc = $A8C2;
_PtToAngle = $A8C3;
_AngleFromSlope = $A8C4;
_StdPoly = $A8C5;
_FramePoly = $A8C6;
_PaintPoly = $A8C7;
_ErasePoly = $A8C8;
_InvertPoly = $A8C9;
_FillPoly = $A8CA;
_OpenPoly = $A8CB;
_ClosePgon = $A8CC;
_ClosePoly = $A8CC;
_KillPoly = $A8CD;
_OffsetPoly = $A8CE;
_PackBits = $A8CF;
_UnpackBits = $A8D0;
_StdRgn = $A8D1;
_FrameRgn = $A8D2;
_PaintRgn = $A8D3;
_EraseRgn = $A8D4;
_InverRgn = $A8D5;
_FillRgn = $A8D6;
_BitMapRgn = $A8D7;
_BitMapToRegion = $A8D7;
_NewRgn = $A8D8;
_DisposRgn = $A8D9;
_DisposeRgn = $A8D9;
_OpenRgn = $A8DA;
_CloseRgn = $A8DB;
_CopyRgn = $A8DC;
_SetEmptyRgn = $A8DD;
_SetRecRgn = $A8DE;
_RectRgn = $A8DF;
_OfsetRgn = $A8E0;
_OffsetRgn = $A8E0;
_InsetRgn = $A8E1;
_EmptyRgn = $A8E2;
_EqualRgn = $A8E3;
_SectRgn = $A8E4;
_UnionRgn = $A8E5;
_DiffRgn = $A8E6;
_XOrRgn = $A8E7;
_PtInRgn = $A8E8;
_RectInRgn = $A8E9;
_SetStdProcs = $A8EA;
_StdBits = $A8EB;
_CopyBits = $A8EC;
_StdTxMeas = $A8ED;
_StdGetPic = $A8EE;
_ScrollRect = $A8EF;
_StdPutPic = $A8F0;
_StdComment = $A8F1;
_PicComment = $A8F2;
_OpenPicture = $A8F3;
_ClosePicture = $A8F4;
_KillPicture = $A8F5;
_DrawPicture = $A8F6;
_Layout = $A8F7;
_ScalePt = $A8F8;
_MapPt = $A8F9;
_MapRect = $A8FA;
_MapRgn = $A8FB;
_MapPoly = $A8FC;

{ 
; Toolbox

 }
_Count1Resources = $A80D;
_Get1IxResource = $A80E;
_Get1IxType = $A80F;
_Unique1ID = $A810;
_TESelView = $A811;
_TEPinScroll = $A812;
_TEAutoView = $A813;
_Pack8 = $A816;
_FixATan2 = $A818;
_XMunger = $A819;
_HOpenResFile = $A81A;
_HCreateResFile = $A81B;
_Count1Types = $A81C;
_Get1Resource = $A81F;
_Get1NamedResource = $A820;
_MaxSizeRsrc = $A821;
_InsMenuItem = $A826;
_InsertMenuItem = $A826;
_HideDItem = $A827;
_HideDialogItem = $A827;
_ShowDItem = $A828;
_ShowDialogItem = $A828;
_LayerDispatch = $A829;
_Pack9 = $A82B;
_Pack10 = $A82C;
_Pack11 = $A82D;
_Pack12 = $A82E;
_Pack13 = $A82F;
_Pack14 = $A830;
_Pack15 = $A831;
_ScrnBitMap = $A833;
_SetFScaleDisable = $A834;
_FontMetrics = $A835;
_ZoomWindow = $A83A;
_TrackBox = $A83B;
_PrGlue = $A8FD;
_InitFonts = $A8FE;
_GetFName = $A8FF;
_GetFNum = $A900;
_FMSwapFont = $A901;
_RealFont = $A902;
_SetFontLock = $A903;
_DrawGrowIcon = $A904;
_DragGrayRgn = $A905;
_NewString = $A906;
_SetString = $A907;
_ShowHide = $A908;
_CalcVis = $A909;
_CalcVBehind = $A90A;
_ClipAbove = $A90B;
_PaintOne = $A90C;
_PaintBehind = $A90D;
_SaveOld = $A90E;
_DrawNew = $A90F;
_GetWMgrPort = $A910;
_CheckUpDate = $A911;
_InitWindows = $A912;
_NewWindow = $A913;
_DisposWindow = $A914;
_DisposeWindow = $A914;
_ShowWindow = $A915;
_HideWindow = $A916;
_GetWRefCon = $A917;
_SetWRefCon = $A918;
_GetWTitle = $A919;
_SetWTitle = $A91A;
_MoveWindow = $A91B;
_HiliteWindow = $A91C;
_SizeWindow = $A91D;
_TrackGoAway = $A91E;
_SelectWindow = $A91F;
_BringToFront = $A920;
_SendBehind = $A921;
_BeginUpDate = $A922;
_EndUpDate = $A923;
_FrontWindow = $A924;
_DragWindow = $A925;
_DragTheRgn = $A926;
_InvalRgn = $A927;
_InvalRect = $A928;
_ValidRgn = $A929;
_ValidRect = $A92A;
_GrowWindow = $A92B;
_FindWindow = $A92C;
_CloseWindow = $A92D;
_SetWindowPic = $A92E;
_GetWindowPic = $A92F;
_InitMenus = $A930;
_NewMenu = $A931;
_DisposMenu = $A932;
_DisposeMenu = $A932;
_AppendMenu = $A933;
_ClearMenuBar = $A934;
_InsertMenu = $A935;
_DeleteMenu = $A936;
_DrawMenuBar = $A937;
_InvalMenuBar = $A81D;
_HiliteMenu = $A938;
_EnableItem = $A939;
_DisableItem = $A93A;
_GetMenuBar = $A93B;
_SetMenuBar = $A93C;
_MenuSelect = $A93D;
_MenuKey = $A93E;
_GetItmIcon = $A93F;
_SetItmIcon = $A940;
_GetItmStyle = $A941;
_SetItmStyle = $A942;
_GetItmMark = $A943;
_SetItmMark = $A944;
_CheckItem = $A945;
_GetItem = $A946;
_GetMenuItemText = $A946;
_SetItem = $A947;
_SetMenuItemText = $A947;
_CalcMenuSize = $A948;
_GetMHandle = $A949;
_GetMenuHandle = $A949;
_SetMFlash = $A94A;
_PlotIcon = $A94B;
_FlashMenuBar = $A94C;
_AddResMenu = $A94D;
_AppendResMenu = $A94D;
_PinRect = $A94E;
_DeltaPoint = $A94F;
_CountMItems = $A950;
_InsertResMenu = $A951;
_DelMenuItem = $A952;
_DeleteMenuItem = $A952;
_UpdtControl = $A953;
_NewControl = $A954;
_DisposControl = $A955;
_DisposeControl = $A955;
_KillControls = $A956;
_ShowControl = $A957;
_HideControl = $A958;
_MoveControl = $A959;
_GetCRefCon = $A95A;
_GetControlReference = $A95A;
_SetCRefCon = $A95B;
_SetControlReference = $A95B;
_SizeControl = $A95C;
_HiliteControl = $A95D;
_GetCTitle = $A95E;
_GetControlTitle = $A95E;
_SetCTitle = $A95F;
_SetControlTitle = $A95F;
_GetCtlValue = $A960;
_GetControlValue = $A960;
_GetMinCtl = $A961;
_GetControlMinimum = $A961;
_GetMaxCtl = $A962;
_GetControlMaximum = $A962;
_SetCtlValue = $A963;
_SetControlValue = $A963;
_SetMinCtl = $A964;
_SetControlMinimum = $A964;
_SetMaxCtl = $A965;
_SetControlMaximum = $A965;
_TestControl = $A966;
_DragControl = $A967;
_TrackControl = $A968;
_DrawControls = $A969;
_GetCtlAction = $A96A;
_GetControlAction = $A96A;
_SetCtlAction = $A96B;
_SetControlAction = $A96B;
_FindControl = $A96C;
_Draw1Control = $A96D;
_Dequeue = $A96E;
_Enqueue = $A96F;
_WaitNextEvent = $A860;
_GetNextEvent = $A970;
_EventAvail = $A971;
_GetMouse = $A972;
_StillDown = $A973;
_Button = $A974;
_TickCount = $A975;
_GetKeys = $A976;
_WaitMouseUp = $A977;
_UpdtDialog = $A978;
_InitDialogs = $A97B;
_GetNewDialog = $A97C;
_NewDialog = $A97D;
_SelIText = $A97E;
_SelectDialogItemText = $A97E;
_IsDialogEvent = $A97F;
_DialogSelect = $A980;
_DrawDialog = $A981;
_CloseDialog = $A982;
_DisposDialog = $A983;
_DisposeDialog = $A983;
_FindDItem = $A984;
_FindDialogItem = $A984;
_Alert = $A985;
_StopAlert = $A986;
_NoteAlert = $A987;
_CautionAlert = $A988;
_ParamText = $A98B;
_ErrorSound = $A98C;
_GetDItem = $A98D;
_GetDialogItem = $A98D;
_SetDItem = $A98E;
_SetDialogItem = $A98E;
_SetIText = $A98F;
_SetDialogItemText = $A98F;
_GetIText = $A990;
_GetDialogItemText = $A990;
_ModalDialog = $A991;
_DetachResource = $A992;
_SetResPurge = $A993;
_CurResFile = $A994;
_InitResources = $A995;
_RsrcZoneInit = $A996;
_OpenResFile = $A997;
_UseResFile = $A998;
_UpdateResFile = $A999;
_CloseResFile = $A99A;
_SetResLoad = $A99B;
_CountResources = $A99C;
_GetIndResource = $A99D;
_CountTypes = $A99E;
_GetIndType = $A99F;
_GetResource = $A9A0;
_GetNamedResource = $A9A1;
_LoadResource = $A9A2;
_ReleaseResource = $A9A3;
_HomeResFile = $A9A4;
_SizeRsrc = $A9A5;
_GetResAttrs = $A9A6;
_SetResAttrs = $A9A7;
_GetResInfo = $A9A8;
_SetResInfo = $A9A9;
_ChangedResource = $A9AA;
_AddResource = $A9AB;
_AddReference = $A9AC;
_RmveResource = $A9AD;
_RmveReference = $A9AE;
_ResError = $A9AF;
_WriteResource = $A9B0;
_CreateResFile = $A9B1;
_SystemEvent = $A9B2;
_SystemClick = $A9B3;
_SystemTask = $A9B4;
_SystemMenu = $A9B5;
_OpenDeskAcc = $A9B6;
_CloseDeskAcc = $A9B7;
_GetPattern = $A9B8;
_GetCursor = $A9B9;
_GetString = $A9BA;
_GetIcon = $A9BB;
_GetPicture = $A9BC;
_GetNewWindow = $A9BD;
_GetNewControl = $A9BE;
_GetRMenu = $A9BF;
_GetNewMBar = $A9C0;
_UniqueID = $A9C1;
_SysEdit = $A9C2;
_OpenRFPerm = $A9C4;
_RsrcMapEntry = $A9C5;
_Secs2Date = $A9C6;
_SecondsToDate = $A9C6;
_Date2Secs = $A9C7;
_DateToSeconds = $A9C7;
_SysBeep = $A9C8;
_SysError = $A9C9;
_PutIcon = $A9CA;
_Munger = $A9E0;
_HandToHand = $A9E1;
_PtrToXHand = $A9E2;
_PtrToHand = $A9E3;
_HandAndHand = $A9E4;
_InitPack = $A9E5;
_InitAllPacks = $A9E6;
_Pack0 = $A9E7;
_Pack1 = $A9E8;
_Pack2 = $A9E9;
_Pack3 = $A9EA;
_FP68K = $A9EB;
_Pack4 = $A9EB;
_Elems68K = $A9EC;
_Pack5 = $A9EC;
_Pack6 = $A9ED;
_DECSTR68K = $A9EE;
_Pack7 = $A9EE;
_PtrAndHand = $A9EF;
_LoadSeg = $A9F0;
_UnLoadSeg = $A9F1;
_Launch = $A9F2;
_Chain = $A9F3;
_ExitToShell = $A9F4;
_GetAppParms = $A9F5;
_GetResFileAttrs = $A9F6;
_SetResFileAttrs = $A9F7;
_MethodDispatch = $A9F8;
_InfoScrap = $A9F9;
_UnlodeScrap = $A9FA;
_UnloadScrap = $A9FA;
_LodeScrap = $A9FB;
_LoadScrap = $A9FB;
_ZeroScrap = $A9FC;
_GetScrap = $A9FD;
_PutScrap = $A9FE;
_Debugger = $A9FF;
_DisplayDispatch = $ABEB;
_IconDispatch = $ABC9;
_DebugStr = $ABFF;

{ 
; Resource Manager

 }
_ResourceDispatch = $A822;

{ 
; PPCToolbox

 }
_PPC = $A0DD;

{ 
; Alias Manager

 }
_AliasDispatch = $A823;

{ 
; Device Manager (some shared by the File Manager)

 }
_Open = $A000;
_Close = $A001;
_Read = $A002;
_Write = $A003;
_Control = $A004;
_Status = $A005;
_KillIO = $A006;

{ 
; File Manager

 }
_GetVolInfo = $A007;
_Create = $A008;
_Delete = $A009;
_OpenRF = $A00A;
_Rename = $A00B;
_GetFileInfo = $A00C;
_SetFileInfo = $A00D;
_UnmountVol = $A00E;
_HUnmountVol = $A20E;
_MountVol = $A00F;
_Allocate = $A010;
_GetEOF = $A011;
_SetEOF = $A012;
_FlushVol = $A013;
_GetVol = $A014;
_SetVol = $A015;
_FInitQueue = $A016;
_Eject = $A017;
_GetFPos = $A018;
_SetFilLock = $A041;
_RstFilLock = $A042;
_SetFilType = $A043;
_SetFPos = $A044;
_FlushFile = $A045;
_HOpen = $A200;
_HGetVInfo = $A207;
_HCreate = $A208;
_HDelete = $A209;
_HOpenRF = $A20A;
_HRename = $A20B;
_HGetFileInfo = $A20C;
_HSetFileInfo = $A20D;
_AllocContig = $A210;
_HSetVol = $A215;
_HGetVol = $A214;
_HSetFLock = $A241;
_HRstFLock = $A242;

{ 
; dispatch trap for remaining File Manager (and Desktop Manager) calls

 }
_FSDispatch = $A060;
_HFSDispatch = $A260;

{ 
; High level FSSpec calls

 }
_HighLevelFSDispatch = $AA52;

{ 
; Memory Manager

 }
_InitZone = $A019;
_GetZone = $A11A;
_SetZone = $A01B;
_FreeMem = $A01C;
_MaxMem = $A11D;
_NewPtr = $A11E;
_NewPtrSys = $A51E;
_NewPtrClear = $A31E;
_NewPtrSysClear = $A71E;
_DisposPtr = $A01F;
_DisposePtr = $A01F;
_SetPtrSize = $A020;
_GetPtrSize = $A021;
_NewHandle = $A122;
_NewHandleClear = $A322;
_DisposHandle = $A023;
_DisposeHandle = $A023;
_SetHandleSize = $A024;
_GetHandleSize = $A025;
_HandleZone = $A126;
_ReallocHandle = $A027;
_RecoverHandle = $A128;
_HLock = $A029;
_HUnlock = $A02A;
_EmptyHandle = $A02B;
_InitApplZone = $A02C;
_SetApplLimit = $A02D;
_BlockMove = $A02E;
_BlockMoveData = $A22E;
_MemoryDispatch = $A05C;
_MemoryDispatchA0Result = $A15C;
_DeferUserFn = $A08F;
_DebugUtil = $A08D;

{ 
; Event Manager

 }
_PostEvent = $A02F;
_PPostEvent = $A12F;
_OSEventAvail = $A030;
_GetOSEvent = $A031;
_FlushEvents = $A032;
_VInstall = $A033;
_VRemove = $A034;
_OffLine = $A035;
_MoreMasters = $A036;
_WriteParam = $A038;
_ReadDateTime = $A039;
_SetDateTime = $A03A;
_Delay = $A03B;
_CmpString = $A03C;
_DrvrInstall = $A03D;
_DrvrRemove = $A03E;
_InitUtil = $A03F;
_ResrvMem = $A040;
_GetTrapAddress = $A146;
_SetTrapAddress = $A047;
_GetOSTrapAddress = $A346;
_SetOSTrapAddress = $A247;
_GetToolTrapAddress = $A746;
_SetToolTrapAddress = $A647;
_GetToolBoxTrapAddress = $A746;
_SetToolBoxTrapAddress = $A647;
_PtrZone = $A148;
_HPurge = $A049;
_HNoPurge = $A04A;
_SetGrowZone = $A04B;
_CompactMem = $A04C;
_PurgeMem = $A04D;
_AddDrive = $A04E;
_RDrvrInstall = $A04F;
_LwrString = $A056;
_UprString = $A054;
_SetApplBase = $A057;
_HWPriv = $A198;

{ 
; New names for (mostly) new flavors of old LwrString trap (redone <13>)
 }
_LowerText = $A056;
_StripText = $A256;
_UpperText = $A456;
_StripUpperText = $A656;

{ 
; Temporary Memory routines

 }
_OSDispatch = $A88F;
_RelString = $A050;
_CompareString = $A050;
_ReadXPRam = $A051;
_WriteXPRam = $A052;
_InsTime = $A058;
_InsXTime = $A458;
_RmvTime = $A059;
_PrimeTime = $A05A;
_PowerOff = $A05B;
_MaxBlock = $A061;
_PurgeSpace = $A162;
_MaxApplZone = $A063;
_MoveHHi = $A064;
_StackSpace = $A065;
_NewEmptyHandle = $A166;
_HSetRBit = $A067;
_HClrRBit = $A068;
_HGetState = $A069;
_HSetState = $A06A;
_InitFS = $A06C;
_InitEvents = $A06D;
_StripAddress = $A055;
_Translate24To32 = $A091;
_SetAppBase = $A057;
_SwapMMUMode = $A05D;
_SlotVInstall = $A06F;
_SlotVRemove = $A070;
_AttachVBL = $A071;
_DoVBLTask = $A072;
_SIntInstall = $A075;
_SIntRemove = $A076;
_CountADBs = $A077;
_GetIndADB = $A078;
_GetADBInfo = $A079;
_SetADBInfo = $A07A;
_ADBReInit = $A07B;
_ADBOp = $A07C;
_GetDefaultStartup = $A07D;
_SetDefaultStartup = $A07E;
_InternalWait = $A07F;
_RGetResource = $A80C;
_GetVideoDefault = $A080;
_SetVideoDefault = $A081;
_DTInstall = $A082;
_SetOSDefault = $A083;
_GetOSDefault = $A084;
_IOPInfoAccess = $A086;
_IOPMsgRequest = $A087;
_IOPMoveData = $A088;

{ 
; Power Manager

 }
_PowerDispatch = $A09F;
_PMgrOp = $A085;
_IdleUpdate = $A285;
_IdleState = $A485;
_SerialPower = $A685;
_Sleep = $A08A;
_SleepQInstall = $A28A;
_SlpQInstall = $A28A;
_SleepQRemove = $A48A;
_SlpQRemove = $A48A;

{ 
; Comm. Toolbox

 }
_CommToolboxDispatch = $A08B;
_SysEnvirons = $A090;

{ 
; Egret Manager

 }
_EgretDispatch = $A092;
_Gestalt = $A1AD;
_NewGestalt = $A3AD;
_ReplaceGestalt = $A5AD;
_GetGestaltProcPtr = $A7AD;
_InitProcMenu = $A808;
_GetItemCmd = $A84E;
_SetItemCmd = $A84F;
_PopUpMenuSelect = $A80B;
_KeyTrans = $A9C3;
_KeyTranslate = $A9C3;

{ 
; TextEdit

 }
_TEGetText = $A9CB;
_TEInit = $A9CC;
_TEDispose = $A9CD;
_TextBox = $A9CE;
_TETextBox = $A9CE;
_TESetText = $A9CF;
_TECalText = $A9D0;
_TESetSelect = $A9D1;
_TENew = $A9D2;
_TEUpdate = $A9D3;
_TEClick = $A9D4;
_TECopy = $A9D5;
_TECut = $A9D6;
_TEDelete = $A9D7;
_TEActivate = $A9D8;
_TEDeactivate = $A9D9;
_TEIdle = $A9DA;
_TEPaste = $A9DB;
_TEKey = $A9DC;
_TEScroll = $A9DD;
_TEInsert = $A9DE;
_TESetJust = $A9DF;
_TESetAlignment = $A9DF;
_TEGetOffset = $A83C;
_TEDispatch = $A83D;
_TEStyleNew = $A83E;

{ 
; Color Quickdraw

 }
_OpenCPort = $AA00;
_InitCPort = $AA01;
_CloseCPort = $A87D;
_NewPixMap = $AA03;
_DisposPixMap = $AA04;
_DisposePixMap = $AA04;
_CopyPixMap = $AA05;
_SetPortPix = $AA06;
_NewPixPat = $AA07;
_DisposPixPat = $AA08;
_DisposePixPat = $AA08;
_CopyPixPat = $AA09;
_PenPixPat = $AA0A;
_BackPixPat = $AA0B;
_GetPixPat = $AA0C;
_MakeRGBPat = $AA0D;
_FillCRect = $AA0E;
_FillCOval = $AA0F;
_FillCRoundRect = $AA10;
_FillCArc = $AA11;
_FillCRgn = $AA12;
_FillCPoly = $AA13;
_RGBForeColor = $AA14;
_RGBBackColor = $AA15;
_SetCPixel = $AA16;
_GetCPixel = $AA17;
_GetCTable = $AA18;
_GetForeColor = $AA19;
_GetBackColor = $AA1A;
_GetCCursor = $AA1B;
_SetCCursor = $AA1C;
_AllocCursor = $AA1D;
_GetCIcon = $AA1E;
_PlotCIcon = $AA1F;
_OpenCPicture = $AA20;
_OpColor = $AA21;
_HiliteColor = $AA22;
_CharExtra = $AA23;
_DisposCTable = $AA24;
_DisposeCTable = $AA24;
_DisposCIcon = $AA25;
_DisposeCIcon = $AA25;
_DisposCCursor = $AA26;
_DisposeCCursor = $AA26;
_SeedCFill = $AA50;
_CalcCMask = $AA4F;
_CopyDeepMask = $AA51;

{ 
; Routines for video devices

 }
_GetMaxDevice = $AA27;
_GetCTSeed = $AA28;
_GetDeviceList = $AA29;
_GetMainDevice = $AA2A;
_GetNextDevice = $AA2B;
_TestDeviceAttribute = $AA2C;
_SetDeviceAttribute = $AA2D;
_InitGDevice = $AA2E;
_NewGDevice = $AA2F;
_DisposGDevice = $AA30;
_DisposeGDevice = $AA30;
_SetGDevice = $AA31;
_GetGDevice = $AA32;
_DeviceLoop = $ABCA;

{ 
; Color Manager

 }
_Color2Index = $AA33;
_Index2Color = $AA34;
_InvertColor = $AA35;
_RealColor = $AA36;
_GetSubTable = $AA37;
_UpdatePixMap = $AA38;

{ 
; Dialog Manager

 }
_NewCDialog = $AA4B;
_NewColorDialog = $AA4B;
_MakeITable = $AA39;
_AddSearch = $AA3A;
_AddComp = $AA3B;
_SetClientID = $AA3C;
_ProtectEntry = $AA3D;
_ReserveEntry = $AA3E;
_SetEntries = $AA3F;
_QDError = $AA40;
_SaveEntries = $AA49;
_RestoreEntries = $AA4A;
_DelSearch = $AA4C;
_DelComp = $AA4D;
_SetStdCProcs = $AA4E;
_StdOpcodeProc = $ABF8;

{ 
; added to Toolbox for color

 }
_SetWinColor = $AA41;
_GetAuxWin = $AA42;
_SetCtlColor = $AA43;
_SetControlColor = $AA43;
_GetAuxCtl = $AA44;
_GetAuxiliaryControlRecord = $AA44;
_NewCWindow = $AA45;
_GetNewCWindow = $AA46;
_SetDeskCPat = $AA47;
_GetCWMgrPort = $AA48;
_GetCVariant = $A809;
_GetControlVariant = $A809;
_GetWVariant = $A80A;

{ 
; added to Menu Manager for color

 }
_DelMCEntries = $AA60;
_DeleteMCEntries = $AA60;
_GetMCInfo = $AA61;
_SetMCInfo = $AA62;
_DispMCInfo = $AA63;
_DisposeMCInfo = $AA63;
_GetMCEntry = $AA64;
_SetMCEntries = $AA65;

{ 
; Menu Manager

 }
_MenuChoice = $AA66;

{ 
; Dialog Manager?

 }
_ModalDialogMenuSetup = $AA67;
_DialogDispatch = $AA68;

{ 
; Font Manager

 }
_SetFractEnable = $A814;
_FontDispatch = $A854;

{ 
; Palette Manager

 }
_InitPalettes = $AA90;
_NewPalette = $AA91;
_GetNewPalette = $AA92;
_DisposePalette = $AA93;
_ActivatePalette = $AA94;
_SetPalette = $AA95;
_NSetPalette = $AA95;
_GetPalette = $AA96;
_PmForeColor = $AA97;
_PmBackColor = $AA98;
_AnimateEntry = $AA99;
_AnimatePalette = $AA9A;
_GetEntryColor = $AA9B;
_SetEntryColor = $AA9C;
_GetEntryUsage = $AA9D;
_SetEntryUsage = $AA9E;
_CTab2Palette = $AA9F;
_Palette2CTab = $AAA0;
_CopyPalette = $AAA1;
_PaletteDispatch = $AAA2;

{ 
; Sound Manager

 }
_SoundDispatch = $A800;
_SndDisposeChannel = $A801;
_SndAddModifier = $A802;
_SndDoCommand = $A803;
_SndDoImmediate = $A804;
_SndPlay = $A805;
_SndControl = $A806;
_SndNewChannel = $A807;
_SlotManager = $A06E;
_ScriptUtil = $A8B5;
_SCSIDispatch = $A815;
_Long2Fix = $A83F;
_Fix2Long = $A840;
_Fix2Frac = $A841;
_Frac2Fix = $A842;
_Fix2X = $A843;
_X2Fix = $A844;
_Frac2X = $A845;
_X2Frac = $A846;
_FracCos = $A847;
_FracSin = $A848;
_FracSqrt = $A849;
_FracMul = $A84A;
_FracDiv = $A84B;
_FixDiv = $A84D;
_NMInstall = $A05E;
_NMRemove = $A05F;

{ 
; All QDOffscreen Routines go through one trap with a selector

 }
_QDExtensions = $AB1D;

{ 
; UserDelay

 }
_UserDelay = $A84C;

{ 
; Component Manager

 }
_ComponentDispatch = $A82A;

_InitDogCow = $A89F;
_EnableDogCow = $A89F;
_DisableDogCow = $A89F;
_Moof = $A89F;
_HFSPinaforeDispatch = $AA52;





{$ENDC} { UsingTraps }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

