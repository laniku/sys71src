/*
	File:		IntlUtilsPriv.h

	Contains:	Private C Interface for International utilities

	Written by:	Nick Kledzik

	Copyright:	© 1990-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	 2/18/92	ngk		Add glue to fix bug in 7.0 version of TypeSelectNewKey. It
									requires high word of D0 to be zero to work.
		 <5>	 8/27/91	JSM		Cleanup header.
		 <4>	  1/2/91	PKE		(bbm) Add interface for private IUClearCacheSys routine.
		 <3>	 9/10/90	PKE		Add interface for private GetScriptItl routine.
		 <2>	  7/2/90	PKE		Added interfaces for private routines IUMagWString,
									IUMagWPString, IUTextOrderSys. Added auto-include of Types.h for
									definition of ScriptCode (and now LangCode too).
		 <1>	  5/2/90	ngk		first checked in
		 
*/

#ifndef __IntlUtilsPriv__
#define __IntlUtilsPriv__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __PACKAGES__
#include <Packages.h>
#endif

/* possible TSCode's */
#define tsPreviousSelectMode	(-1)
#define tsNormalSelectMode		0
#define tsNextSelectMode		1	

typedef short	TSCode;

struct TypeSelectRecord
{
	unsigned long		tsrLastKeyTime;		
	ScriptCode			tsrScript; 	
	Str63				tsrKeyStrokes;		
};
#ifndef __cplusplus
typedef struct TypeSelectRecord	TypeSelectRecord;
#endif

typedef pascal Boolean (*IndexToStringProcPtr) (short		item,
												ScriptCode	*itemsScript,
												StringPtr	*itemsStringPtr,
												void		*yourDataPtr);


	pascal TypeSelectClear(TypeSelectRecord *tsr)
		= { 0x3F3C, 0x0028, 0xA9ED };


	pascal Boolean TypeSelectNewKey(const EventRecord	*theEvent,
								  TypeSelectRecord		*tsr)
		= { 0x7000, 0x3F3C, 0x002A, 0xA9ED };


	pascal short TypeSelectFindItem(const TypeSelectRecord	*tsr,
									short					listSize,
									TSCode					selectMode,
									IndexToStringProcPtr	getStringProc,
									void					*yourDataPtr)
		= { 0x3F3C, 0x002C, 0xA9ED };
		
	
	pascal short TypeSelectCompare(	const TypeSelectRecord	*tsr,
									ScriptCode				testStringScript,
									StringPtr				testStringPtr)
		= { 0x3F3C, 0x002E, 0xA9ED };
		

	pascal short IUMagWString(Ptr aPtr,Ptr bPtr,short aLen,short bLen) 						/* <2> */
		= { 0x3F3C, 0x0012, 0xA9ED };
	
	pascal short IUMagWPString(Ptr aPtr,Ptr bPtr,short aLen,short bLen,Handle intlParam) 	/* <2> */
		= { 0x3F3C, 0x0026, 0xA9ED }; 
	
	pascal short IUTextOrderSys(Ptr aPtr,Ptr bPtr,short aLen,short bLen,ScriptCode aScript,	/* <2> */
		ScriptCode bScript,LangCode aLang,LangCode bLang)
		= { 0x3F3C, 0x0030, 0xA9ED }; 
	
	pascal Handle IUGetItlScript(short theID, ScriptCode script, short sysFlag)				/* <3> */
		= { 0x3F3C, 0x0032, 0xA9ED }; 
	
	pascal void IUClearCacheSys(void)														/* <4> */
		= { 0x3F3C, 0x0034, 0xA9ED }; 
	
#endif		/* __IntlUtilsPriv__ */
