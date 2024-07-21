
{
Created: Saturday, July 27, 1991 at 7:47 PM
 AppleEvents.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1989-1991
  All rights reserved
 
	This file is used in these builds: BigBang

	Change History (most recent first):

		<30>	 7/30/91	JL		Updated Copyright.
		<29>	 6/14/91	JL		Checked in official MPW 3.2Ä version. Lost correct '91 copyright
									date but will restore it later. Reformatted comments to match
									the DSG Database output.
		<28>	  2/5/91	stb		eeh: add missing constants; tweak comments
		<27>	  2/1/91	DFH		stb,WS#DFH-910131c:Added Process Mgr defined AppleEvent codes.
		<26>	 1/29/91	LN		Checked in Database Generated file from DSG.
									removed conditional on using data base access
									from around; corrected keykeySelectProc to
									keySelectProc
		<25+>	1/28/91		JAL		Checked in Database Generated file from DSG.
									removed conditional on using data base access
									from around; corrected keykeySelectProc to 
									keySelectProc
		<25>	12/13/90	Lai		Add the keyword for 'errn'
		<24>	 11/9/90	ngk		Added auto-include of Notification.p.
		<23>	10/10/90	Lai		Change QElemPtr to NMRecPtr to be consistent with Notification
									manager.
		<22>	10/10/90	JL		Changed theEventID to theAEEventID to remain consistent in
									AEGetEventHandler
		<21>	 10/2/90	Lai		New error constant errAEParamMissed for use by applications.
		<20>	 9/25/90	Lai		Bug fix for jfr0009, change order of parameter in special
									handler calls.
		<19>	 9/21/90	Lai		Fix misspelling in keyEventSourceAtt (r missing).
		<18>	 9/20/90	Lai		Add error constant errIllegalIndex
		<17>	 9/19/90	Lai		Add returnID parameter to the reply filter template
		<16>	 9/15/90	Lai		New interface for IdleProc
		<15>	 9/10/90	Lai		Correct spelling theAEEEEventClass to theAEEventClass
		<14>	 9/10/90	Lai		Correct inline for AEInstallCoercionHandler and
									AEGetCoercionHandler
		<13>	  9/7/90	Lai		This file is now the interface for the AppleEvent Manager.
		-------------------------------
		<12>	DFH	16 Apr 90	Removed aeProcessParamType.
		<11>	DFH	16 Apr 90	Changed saeOpenDocumentMsgID to 'odoc', saePrintDocumentMsgID
								to 'pdoc'.	Added saeLaunchedWithoutDocs, saeAnswer,
								aeErrorValueKeyword, and AppleEventReply.
		<10>	ngk 3/22/90		Changed AETFDescriptor AETFParameter in regular expr.
		<9>		ngk 3/20/90		Changed PACKED ARRAY [0..3] to [1..4]
		<8>		ngk 3/20/90		fix comments
		<7>		ngk 3/20/90		Changed for 7.0a8 AppleEvents format
		<6>		DFH 12 Mar 90	Removed aeDebuggerNotify
		<5>		ngk 3/10/90		Big change for 7.0a8 AppleEvents format
		<3>		ngk 2/06/90		clean up standard header records
		
		1.1	ngk 12/01/1989		Renamed aeUnexpectedQuit to aeApplicationDied, and
								refcon to amsRefcon
		1.0	ngk 11/01/1989		initial EASE release

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT AppleEvents;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingAppleEvents}
{$SETC UsingAppleEvents := 1}

{$I+}
{$SETC AppleEventsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$IFC UNDEFINED UsingMemory}
{$I $$Shell(PInterfaces)Memory.p}
{$ENDC}
{$IFC UNDEFINED UsingOSUtils}
{$I $$Shell(PInterfaces)OSUtils.p}
{$ENDC}
{$IFC UNDEFINED UsingEvents}
{$I $$Shell(PInterfaces)Events.p}
{$ENDC}
{$IFC UNDEFINED UsingEPPC}
{$I $$Shell(PInterfaces)EPPC.p}
{$ENDC}
{$IFC UNDEFINED UsingNotification}
{$I $$Shell(PInterfaces)Notification.p}
{$ENDC}
{$SETC UsingIncludes := AppleEventsIncludes}

CONST
typeBoolean = 'bool';
typeChar = 'TEXT';
typeSMInt = 'shor';
typeInteger = 'long';
typeSMFloat = 'sing';
typeFloat = 'doub';
typeLongInteger = 'long';
typeShortInteger = 'shor';
typeLongFloat = 'doub';
typeShortFloat = 'sing';
typeExtended = 'exte';
typeComp = 'comp';
typeMagnitude = 'magn';
typeAEList = 'list';
typeAERecord = 'reco';
typeTrue = 'true';
typeFalse = 'fals';
typeAlias = 'alis';
typeEnumerated = 'enum';
typeType = 'type';
typeAppParameters = 'appa';
typeProperty = 'prop';
typeFSS = 'fss ';
typeKeyword = 'keyw';
typeSectionH = 'sect';
typeWildCard = '****';

typeApplSignature = 'sign';
typeSessionID = 'ssid';
typeTargetID = 'targ';
typeProcessSerialNumber = 'psn ';
typeNull = 'null';					{the type of null/nonexistent data}

kCoreEventClass = 'aevt';

kAEOpenApplication = 'oapp';
kAEOpenDocuments = 'odoc';
kAEPrintDocuments = 'pdoc';
kAEQuitApplication = 'quit';

kAECreatorType = 'crea';
kAEQuitAll = 'quia';
kAEShutDown = 'shut';
kAERestart = 'rest';
kAEApplicationDied = 'obit';
keyProcessSerialNumber = 'psn ';

keyErrorNumber = 'errn';
keyErrorString = 'errs';

kAEAnswer = 'ansr';

keyDirectObject = '----';


{ keyword used in install special handler }
keyPreDispatch = 'phac';			{ PreHandler Accessor Call }
keySelectProc = 'selh';				{ More selector Call }

{ keywords used in attributes }
keyTransactionIDAttr = 'tran';
keyReturnIDAttr = 'rtid';
keyEventClassAttr = 'evcl';
keyEventIDAttr = 'evid';
keyAddressAttr = 'addr';
keyOptionalKeywordAttr = 'optk';
keyTimeoutAttr = 'timo';
keyInteractLevelAttr = 'inte';		{this attribute is read only will be set in AESend}
keyEventSourceAttr = 'esrc';		{ this attribute is read only }
keyMissedKeywordAttr = 'miss';		{ this attribute is read only }

{ constants for use in AESendMode }
kAENoReply = $00000001;				{ Sender doesn't want a reply to event }
kAEQueueReply = $00000002;			{ Sender wants a reply but won't wait }
kAEWaitReply = $00000003;			{ Sender wants a reply and will be waiting }

kAENeverInteract = $00000010;		{ Server should not interact with user }
kAECanInteract = $00000020;			{ Server may try to interact with user }
kAEAlwaysInteract = $00000030;		{ Server should always interact with user where appropriate }

kAECanSwitchLayer = $00000040;		{ Interaction may switch layer }

kAEDontReconnect = $00000080;		{ don't reconnect if there is a sessClosedErr from PPCToolbox }

kAEWantReceipt = nReturnReceipt;	{ Send wants a receipt of message }

{ constants to be used in AESendPriority }
kAENormalPriority = $00000000;		{ Post message at the end of event queue }
kAEHighPriority = nAttnMsg;			{ Post message at the front of the event queue }

{ special constants in generating events }
kAnyTransactionID = 0;				{ no transaction is in use }
kAutoGenerateReturnID = -1;			{ AECreateAppleEvent will generate a session-unique ID }

{ constant for use AESend }
kAEDefaultTimeout = -1;				{ timeout value determined by AEM }
kNoTimeOut = -2;					{ wait until reply comes back, however long it takes }

{ dispatch parameter to AEResumeTheCurrentEvent takes a pointer to a dispatch
table, or one of these two constants }
kAENoDispatch = 0;
kAEUseStandardDispatch = -1;

{ Error messages in response to reading and writing event contents }
errAECoercionFail = -1700;
errAEDescNotFound = -1701;
errAECorruptData = -1702;
errAEWrongDataType = -1703;
errAENotAEDesc = -1704;
errAEBadListItem = -1705;			{ Specified list item does not exist }
errAENewerVersion = -1706;			{ Need newer version of AppleEvent Manager }
errAENotAppleEvent = -1707;			{ The event is not in AppleEvent format }

{ Error messages in response to sending/receiving a message }
errAEEventNotHandled = -1708;		{ The AppleEvent was not handled by any handler }
errAEReplyNotValid = -1709;			{ AEResetTimer was passed an invalid reply parameter }
errAEUnknownSendMode = -1710;		{ Mode wasn't NoReply, WaitReply, or QueueReply;  or Interaction level is unknown }
errAEWaitCanceled = -1711;			{ In AESend, User cancelled out of wait loop for  reply or receipt }
errAETimeout = -1712;				{ AppleEvent timed out }

errAENoUserInteraction = -1713;		{ no user interaction allowed }
errAENotASpecialFunction = -1714;	{ there is no special function with this keyword }
errAEParamMissed = -1715;			{ a required parameter was not accessed }

errAEUnknownAddressType = -1716;	{ The target address type is not known }
errAEHandlerNotFound = -1717;		{ No handler in the dispatch tables fits the parameters to
             AEGetEventHandler or AEGetCoercionHandler }

errAEReplyNotArrived = -1718;		{ the contents of the reply you are accessing have not arrived yet }
errAEIllegalIndex = -1719;			{ Index is out of range in a put operation }

TYPE
AEKeyword    = PACKED ARRAY [1..4] OF CHAR;
AEEventClass  = PACKED ARRAY [1..4] OF CHAR;
AEEventID    = PACKED ARRAY [1..4] OF CHAR;
DescType = ResType;

{ tagged data, the standard AppleEvent data type }
AEDesc = RECORD
 descriptorType: DescType;
 dataHandle: Handle;
 END;


AEAddressDesc = AEDesc;				{ an AEDesc which contains addressing data }
AEDescList = AEDesc;				{ a list of AEDesc is a special kind of AEDesc }
AERecord = AEDescList;				{ AERecord is a list of keyworded AEDesc }
AppleEvent = AERecord;				{ an AERecord that contains an AppleEvent }
AESendMode = LONGINT;				{ Type of parameter to AESend }
AESendPriority = INTEGER;			{ Type of priority param of AESend }

{ type of param to AEGetInteractionAllowed and AESetInteractionAllowed }
AEInteractAllowed = (kAEInteractWithSelf,kAEInteractWithLocal,kAEInteractWithAll);

{ Return param to AEGetTheCurrentEvent, and kAEEventSource attribute }
AEEventSource = (kAEUnknownSource,kAEDirectCall,kAESameProcess,kAELocalProcess,
 kAERemoteProcess);


{ types for AppleEvent Array support 

 Basic data type of attibutes & parameters}
AEKeyDesc = RECORD
 descKey: AEKeyword;
 descContent: AEDesc;
 END;


AEArrayType = (kAEDataArray,kAEPackedArray,kAEHandleArray,kAEDescArray,
 kAEKeyDescArray);


{ Array routines support these different types of elements}
AEArrayData = RECORD
 case AEArrayType OF
  kAEDataArray: 
   (AEDataArray:   Array[0..0] OF Integer);
  kAEPackedArray: 
   (AEPackedArray:  Packed Array[0..0] OF Char);
  kAEHandleArray: 
   (AEHandleArray:  Array[0..0] OF Handle);
  kAEDescArray: 
   (AEDescArray:   Array[0..0] OF AEDesc);
  kAEKeyDescArray: 
   (AEKeyDescArray:  Array[0..0] OF AEKeyDesc);
 END;
 
AEArrayDataPointer = ^AEArrayData;



EventHandlerProcPtr = ProcPtr;
IdleProcPtr = ProcPtr;
EventFilterProcPtr = ProcPtr;


{   *********************************************************************
The following calls apply to any AEDesc. Every result descriptor is created for you,
so you will be responsible for memory management of the descriptors so created.
Purgeable descriptor data is not supported: the AEM does not call LoadResource.   }
FUNCTION AECreateDesc(typeCode: DescType;
                      dataPtr: Ptr;
                      dataSize: Size;
                      VAR result: AEDesc): OSErr;
 INLINE $303C, $0825, $A816;
FUNCTION AECoercePtr(typeCode: DescType;
                     dataPtr: Ptr;
                     dataSize: Size;
                     toType: DescType;
                     VAR result: AEDesc): OSErr;
 INLINE $303C, $0A02, $A816;
FUNCTION AECoerceDesc(theAEDesc: AEDesc;
                      toType: DescType;
                      VAR result: AEDesc): OSErr;
 INLINE $303C, $0603, $A816;
FUNCTION AEDisposeDesc(VAR theAEDesc: AEDesc): OSErr;
 INLINE $303C, $0204, $A816;
FUNCTION AEDuplicateDesc(theAEDesc: AEDesc;VAR result: AEDesc): OSErr;
 INLINE $303C, $0405, $A816;

{ *********************************************************************
 The following calls apply to AEDescList.
  Since AEDescList is a subtype of AEDesc, the calls in the previous
  section can also be used for AEDescList. All list and array indices are 1-based.
  If the data was greater than maximumSize in the routines below, then actualSize will
  be greater than maximumSize, but only maximumSize bytes will actually be retrieved. }
FUNCTION AECreateList(factoringPtr: Ptr;
                      factoredSize: Size;
                      isRecord: BOOLEAN;
                      VAR resultList: AEDescList): OSErr;
 INLINE $303C, $0706, $A816;
FUNCTION AECountItems(theAEDescList: AEDescList;
                      VAR theCount: LONGINT): OSErr;
 INLINE $303C, $0407, $A816;
FUNCTION AEPutPtr(theAEDescList: AEDescList;
                  index: LONGINT;
                  typeCode: DescType;
                  dataPtr: Ptr;
                  dataSize: Size): OSErr;
 INLINE $303C, $0A08, $A816;
FUNCTION AEPutDesc(theAEDescList: AEDescList;
                   index: LONGINT;
                   theAEDesc: AEDesc): OSErr;
 INLINE $303C, $0609, $A816;
FUNCTION AEGetNthPtr(theAEDescList: AEDescList;
                     index: LONGINT;
                     desiredType: DescType;
                     VAR theAEKeyword: AEKeyword;
                     VAR typeCode: DescType;
                     dataPtr: Ptr;
                     maximumSize: Size;
                     VAR actualSize: Size): OSErr;
 INLINE $303C, $100A, $A816;
FUNCTION AEGetNthDesc(theAEDescList: AEDescList;
                      index: LONGINT;
                      desiredType: DescType;
                      VAR theAEKeyword: AEKeyword;
                      VAR result: AEDesc): OSErr;
 INLINE $303C, $0A0B, $A816;
FUNCTION AESizeOfNthItem(theAEDescList: AEDescList;
                         index: LONGINT;
                         VAR typeCode: DescType;
                         VAR dataSize: Size): OSErr;
 INLINE $303C, $082A, $A816;
FUNCTION AEGetArray(theAEDescList: AEDescList;
                    arrayType: AEArrayType;
                    arrayPtr: AEArrayDataPointer;
                    maximumSize: Size;
                    VAR itemType: DescType;
                    VAR itemSize: Size;
                    VAR itemCount: LONGINT): OSErr;
 INLINE $303C, $0D0C, $A816;
FUNCTION AEPutArray(theAEDescList: AEDescList;
                    arrayType: AEArrayType;
                    arrayPtr: AEArrayDataPointer;
                    itemType: DescType;
                    itemSize: Size;
                    itemCount: LONGINT): OSErr;
 INLINE $303C, $0B0D, $A816;
FUNCTION AEDeleteItem(theAEDescList: AEDescList;
                      index: LONGINT): OSErr;
 INLINE $303C, $040E, $A816;

{ *********************************************************************
The following calls apply to AERecord.
  Since AERecord is a subtype of AEDescList, the calls in the previous
  sections can also be used for AERecord
  an AERecord can be created by using AECreateList with isRecord set to true  }
FUNCTION AEPutKeyPtr(theAERecord: AERecord;
                     theAEKeyword: AEKeyword;
                     typeCode: DescType;
                     dataPtr: Ptr;
                     dataSize: Size): OSErr;
 INLINE $303C, $0A0F, $A816;
FUNCTION AEPutKeyDesc(theAERecord: AERecord;
                      theAEKeyword: AEKeyword;
                      theAEDesc: AEDesc): OSErr;
 INLINE $303C, $0610, $A816;
FUNCTION AEGetKeyPtr(theAERecord: AERecord;
                     theAEKeyword: AEKeyword;
                     desiredType: DescType;
                     VAR typeCode: DescType;
                     dataPtr: Ptr;
                     maximumSize: Size;
                     VAR actualSize: Size): OSErr;
 INLINE $303C, $0E11, $A816;
FUNCTION AEGetKeyDesc(theAERecord: AERecord;
                      theAEKeyword: AEKeyword;
                      desiredType: DescType;
                      VAR result: AEDesc): OSErr;
 INLINE $303C, $0812, $A816;
FUNCTION AESizeOfKeyDesc(theAERecord: AERecord;
                         theAEKeyword: AEKeyword;
                         VAR typeCode: DescType;
                         VAR dataSize: Size): OSErr;
 INLINE $303C, $0829, $A816;
FUNCTION AEDeleteKeyDesc(theAERecord: AERecord;
                         theAEKeyword: AEKeyword): OSErr;
 INLINE $303C, $0413, $A816;

{ 
 *********************************************************************
 The following calls are used to pack and unpack parameters from records of
 type AppleEvent. Since AppleEvent is a subtype of AERecord, the calls in the previous
 sections can also be used for variables of type AppleEvent. The next six calls
 are in fact identical to the six calls for AERecord.
 }
FUNCTION AEPutParamPtr(theAppleEvent: AppleEvent;
                       theAEKeyword: AEKeyword;
                       typeCode: DescType;
                       dataPtr: Ptr;
                       dataSize: Size): OSErr;
 INLINE $303C,$0A0F,$A816;
FUNCTION AEPutParamDesc(theAppleEvent: AppleEvent;
                        theAEKeyword: AEKeyword;
                        theAEDesc: AEDesc): OSErr;
 INLINE $303C,$0610,$A816;
FUNCTION AEGetParamPtr(theAppleEvent: AppleEvent;
                       theAEKeyword: AEKeyword;
                       desiredType: DescType;
                       VAR typeCode: DescType;
                       dataPtr: Ptr;
                       maximumSize: Size;
                       VAR actualSize: Size): OSErr;
 INLINE $303C,$0E11,$A816;
FUNCTION AEGetParamDesc(theAppleEvent: AppleEvent;
                        theAEKeyword: AEKeyword;
                        desiredType: DescType;
                        VAR result: AEDesc): OSErr;
 INLINE $303C,$0812,$A816;
FUNCTION AESizeOfParam(theAppleEvent: AppleEvent;
                       theAEKeyword: AEKeyword;
                       VAR typeCode: DescType;
                       VAR dataSize: Size): OSErr;
 INLINE $303C,$0829,$A816;
FUNCTION AEDeleteParam(theAppleEvent: AppleEvent;
                       theAEKeyword: AEKeyword): OSErr;
 INLINE $303C,$0413,$A816;

{ *********************************************************************
The following calls also apply to type AppleEvent.  Message attributes are far more restricted, and
can only be accessed through the following 5 calls. The various list and record routines cannot be used
to access the attributes of an event.  }
FUNCTION AEGetAttributePtr(theAppleEvent: AppleEvent;
                           theAEKeyword: AEKeyword;
                           desiredType: DescType;
                           VAR typeCode: DescType;
                           dataPtr: Ptr;
                           maximumSize: Size;
                           VAR actualSize: Size): OSErr;
 INLINE $303C,$0E15,$A816;
FUNCTION AEGetAttributeDesc(theAppleEvent: AppleEvent;
                            theAEKeyword: AEKeyword;
                            desiredType: DescType;
                            VAR result: AEDesc): OSErr;
 INLINE $303C,$0826,$A816;
FUNCTION AESizeOfAttribute(theAppleEvent: AppleEvent;
                           theAEKeyword: AEKeyword;
                           VAR typeCode: DescType;
                           VAR dataSize: Size): OSErr;
 INLINE $303C,$0828,$A816;
FUNCTION AEPutAttributePtr(theAppleEvent: AppleEvent;
                           theAEKeyword: AEKeyword;
                           typeCode: DescType;
                           dataPtr: Ptr;
                           dataSize: Size): OSErr;
 INLINE $303C,$0A16,$A816;
FUNCTION AEPutAttributeDesc(theAppleEvent: AppleEvent;
                            theAEKeyword: AEKeyword;
                            theAEDesc: AEDesc): OSErr;
 INLINE $303C,$0627,$A816;

{ *********************************************************************
 The next four calls are basic routines used to create, send, and process AppleEvents.  }
FUNCTION AECreateAppleEvent(theAEEventClass: AEEventClass;
                            theAEEventID: AEEventID;
                            target: AEAddressDesc;
                            returnID: INTEGER;
                            transactionID: LONGINT;
                            VAR result: AppleEvent): OSErr;
 INLINE $303C,$0B14,$A816;
FUNCTION AESend(theAppleEvent: AppleEvent;
                VAR reply: AppleEvent;
                sendMode: AESendMode;
                sendPriority: AESendPriority;
                timeOutInTicks: LONGINT;
                idleProc: IdleProcPtr;
                filterProc: EventFilterProcPtr): OSErr;
 INLINE $303C,$0D17,$A816;
FUNCTION AEProcessAppleEvent(theEventRecord: EventRecord): OSErr;
 INLINE $303C,$021B,$A816;

{ During event processing, an event handler may realize that it is likely
to exceed the client's timeout limit. Passing the reply to this
routine causes a wait event to be generated to ask the client for more time.  }
FUNCTION AEResetTimer(reply: AppleEvent): OSErr;
 INLINE $303C,$0219,$A816;

{   *********************************************************************
The following four calls are available for applications which need more sophisticated control
over when and how events are processed. Applications which implement multi-session servers or 
which implement their own internal event queueing will probably be the major clients of these
routines.  

 Can be called from within a handler to prevent the AEM from disposing of
the AppleEvent when the handler returns. Can be used to asynchronously process the 
event (as in MacApp). }
FUNCTION AESuspendTheCurrentEvent(theAppleEvent: AppleEvent): OSErr;
 INLINE $303C,$022B,$A816;

{ 
  Tells the AppleEvent manager that processing is either about to resume or has
 been completed on a previously suspended event. The procPtr passed in as the
 dispatcher parameter will be called to attempt to redispatch the event. Several
 constants for the dispatcher parameter allow special behavior. They are:
 - kAEUseStandardDispatch means redispatch as if the event was just received, using the
  standard AppleEvent Dispatcher.
 - kAENoDispatch means ignore the parameter.
  Use this in the case where no redispatch is needed, and the event has been handled.
 - non nil means call the routine which dispatcher points to.
 }
FUNCTION AEResumeTheCurrentEvent(theAppleEvent: AppleEvent;
                                 reply: AppleEvent;
                                 dispatcher: EventHandlerProcPtr;
                                 handlerRefcon: LONGINT): OSErr;
 INLINE $303C,$0818,$A816;

{ Allows application to examine the currently executing event }
FUNCTION AEGetTheCurrentEvent(VAR theAppleEvent: AppleEvent): OSErr;
 INLINE $303C,$021A,$A816;

{ Set the current event to the parameter }
FUNCTION AESetTheCurrentEvent(theAppleEvent: AppleEvent): OSErr;
 INLINE $303C,$022C,$A816;

{ 
 *********************************************************************
  The following three calls are used to allow applications to behave courteously 
 when a user interaction such as a dialog box is needed. 
 }
FUNCTION AEGetInteractionAllowed(VAR level: AEInteractAllowed): OSErr;
 INLINE $303C,$021D,$A816;
FUNCTION AESetInteractionAllowed(level: AEInteractAllowed): OSErr;
 INLINE $303C,$011E,$A816;
FUNCTION AEInteractWithUser(timeOutInTicks: LONGINT;
                            nmReqPtr: NMRecPtr;
                            idleProc: IdleProcPtr): OSErr;
 INLINE $303C,$061C,$A816;

{  *********************************************************************
 These calls are used to set up and modify the event dispatch table  }
 
{ Add an AppleEvent Handler  }
FUNCTION AEInstallEventHandler(theAEEventClass: AEEventClass;
                               theAEEventID: AEEventID;
                               handler: EventHandlerProcPtr;
                               handlerRefcon: LONGINT;
                               isSysHandler: BOOLEAN): OSErr;
 INLINE $303C,$091F,$A816;

{  Remove an AppleEvent Handler  }
FUNCTION AERemoveEventHandler(theAEEventClass: AEEventClass;
                              theAEEventID: AEEventID;
                              handler: EventHandlerProcPtr;
                              isSysHandler: BOOLEAN): OSErr;
 INLINE $303C,$0720,$A816;

{  Get the corresponding AppleEvent Handler  }
FUNCTION AEGetEventHandler(theAEEventClass: AEEventClass;
                           theAEEventID: AEEventID;
                           VAR handler: EventHandlerProcPtr;
                           VAR handlerRefcon: LONGINT;
                           isSysHandler: BOOLEAN): OSErr;
 INLINE $303C,$0921,$A816;

{  *********************************************************************
 These calls are used to set up and modify the coercion dispatch table   }
FUNCTION AEInstallCoercionHandler(fromType: DescType;
                                  toType: DescType;
                                  handler: ProcPtr;
                                  handlerRefcon: LONGINT;
                                  fromTypeIsDesc: BOOLEAN;
                                  isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $0A22, $A816;

{  Remove a Coercion Handler  }
FUNCTION AERemoveCoercionHandler(fromType: DescType;
                                 toType: DescType;
                                 handler: ProcPtr;
                                 isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $0723, $A816;

{  Get the corresponding Coercion Handler  }
FUNCTION AEGetCoercionHandler(fromType: DescType;
                              toType: DescType;
                              VAR handler: ProcPtr;
                              VAR handlerRefcon: LONGINT;
                              VAR fromTypeIsDesc: BOOLEAN;
                              isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $0B24, $A816;

{ 
   *********************************************************************
 These calls are used to set up and modify special hooks into the AppleEvent Manager.

 Install the special handler named by the Keyword   }
FUNCTION AEInstallSpecialHandler(functionClass: AEKeyword;
                                 handler: ProcPtr;
                                 isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $0500, $A816;

{  Remove the special handler named by the Keyword  }
FUNCTION AERemoveSpecialHandler(functionClass: AEKeyword;
                                handler: ProcPtr;
                                isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $0501, $A816;

{  Get the special handler named by the Keyword  }
FUNCTION AEGetSpecialHandler(functionClass: AEKeyword;
                             VAR handler: ProcPtr;
                             isSysHandler: BOOLEAN): OSErr;
 INLINE $303C, $052D, $A816;


{$ENDC} { UsingAppleEvents }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

