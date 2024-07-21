/*
	File:		GestaltLookup.c

	Contains:	Gestalt data structure manipulation routines.

	Written by:	Carl C. Hewitt

	Copyright:	© 1988-1990, 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	11/10/93	fau		Removed ulong typedef since it's now in Types.h.
	   <SM4>	 5/18/93	RC		perfomance/bug fix changed a > to >> in FindLong
	   <SM3>	  4/8/93	CSS		Use GestaltPrivateEqu.h, and remove definitions in this file.
		<11>	10/28/92	DTY		Use Get/Set macros to access ExpandMem.
		<10>	12/13/90	SAM		Making Gestalt check for a nil proc ptr on _NewGestalt calls.
		 <9>	  8/8/90	CCH		Now only uses the stripped address during the check for function
									location.
		 <8>	  8/1/90	SAM		NewGestalt now calls stripAddress with the ProcPtr passed to it
									before checking to see if it is in the sys heap.
		 <7>	 7/17/90	dba		get rid of MemUtils.h
		 <6>	 7/10/90	dba		add prototypes
		 <5>	  7/7/90	dba		change routine names to match Interface.o
		 <4>	 1/16/90	cch		Fixed unitialized variable in newGestalt.
		 <3>	 1/15/90	CCH		Fixed routine to add Gestalt selectors to allow Gestalt to be
									called when interrupts are off.
		 <2>	  1/3/90	CCH		Changed Gestalt equate file name.
		 <1>	  1/2/90	CCH		Changed name from Gestalt.c.
	   <1.9>	 7/16/89	CCH		Changes: (NEEDED FOR 6.0.4 AND AURORA) - Removed unnecessary
									Hlocks and HUnlocks.
	   <1.8>	 7/14/89	CCH		Changes: (NEEDED FOR 6.0.4 AND AURORA AND ESPRIT) - Fixed bug in
									check for gestalt function location.
	   <1.7>	 7/10/89	CCH		Changes: (NEEDED FOR AURORA) - Added check to make sure new
									gestalt functions are in the sys heap.
	   <1.6>	 5/25/89	CCH		Added new parameter to getGestalt function to allow it pass back
									old values when replacing codes.
	   <1.5>	 5/18/89	CCH		Several changes to Gestalt: - rewrote getGestalt in assembly and
									moved to Gestalt.a - changed prefix to Gestalt equates to
									"gestalt" - changed to new error codes
	   <1.4>	 4/16/89	CCH		Changed equates to new naming convention.
	   <1.3>	 4/13/89	CCH		Gestalt now passes through the return values of function code
									routines.
	   <1.2>	 3/30/89	CCH		Optimized everything.
	   <1.1>	  3/2/89	CCH		Moved init code to GestaltInit.c, and cleaned up some stuff.
	   <1.0>	 2/21/89	CCH		Adding to EASE for the first time.
*/

/*********************************************************************************
 *
 *	File:	Gestalt.c
 *
 *	Data structure access routines for Gestalt.
 *
 *	By Carl C. Hewitt
 *	November 30th, 1988
 *
 *	© Copyright 1988-1989 Apple Computer, Inc.
 *
 *********************************************************************************/
#include <SysEqu.h>
#include <Types.h>
#include <Memory.h>
#include <Errors.h>
#include <ExpandMemPriv.h>
#include <GestaltEqu.h>
#include <GestaltPrivateEqu.h>

/************************
 *	types local to this file
 ************************/

typedef ulong LongEntry[2];				/* long entry */
typedef LongEntry *LongEntryPtr;		/* ptr to a long entry */
typedef	ulong (*FuncPtr)();				/* ptr to a function that returns a long */

#define	GestaltPtr	((GestaltGlobalsPtr) (GetExpandMemGestalt()))

/************************
 *	prototypes
 ************************/
OSErr newGestalt(ulong replace, ulong selector, ulong value, ulong *oldProc);
OSErr removeLong(ulong selector, ulong* oldValue);
OSErr findLong(ulong selector, int* index);


/*********************************************************************************
 *	function:	newGestalt(replace, selector, value, oldProc)
 *				ulong selector;
 *				ulong value;
 *				int replace;
 *				ulong *oldProc;
 *	purpose:	adds the specified long into the table as entry #selector, or changes
 *				it if it already exists.  replace determines whether this is an add or
 *				replace function.  true means replace, false means add
 *
 *				Replace	Exists	Error	Action
 *				ÑÑÑÑÑÑÑ	ÑÑÑÑÑÑ	ÑÑÑÑÑ	ÑÑÑÑÑÑ
 *				false	false	no		add
 *				false	true	yes		-
 *				true	false	yes		-
 *				true	true	no		replace
 *
 *	lastmod:	1/15/90
 *********************************************************************************/
OSErr
newGestalt(ulong replace, ulong selector, ulong value, ulong *oldProc)
{
	LongEntryPtr	tablePtr;
	Handle			tempTable, myHandle;
	int 			i, index, found;
	ulong			*destPtr, *srcPtr, size, strippedVal;
	OSErr			myResult;

	if (!(value) || (value & 1))								/* proc ptr must be even */
		return(paramErr);

	/** Make sure the gestalt function is in the System Heap <1.7> **/

	strippedVal = StripAddress((Ptr)value);		/* gotta lose them high bits... <8><9> */
	if ((strippedVal > **(ulong**)SysZone) && (strippedVal < StripAddress(*(Ptr*)ROMBase)))
		return(gestaltLocationErr);

	/** Make a new table to make our changes to so we can use Gestalt from  **/
	/** interrupt routines 													**/

	size = GetHandleSize( GestaltPtr->tableH );	/* get the size of the table */
	tempTable = NewHandleSysClear( size );
	if (*(short*)MemErr)						/* was there a problem? */
		return(memFullErr);
	destPtr = (ulong*) *tempTable;				/* get a pointer to the new table */
	srcPtr = (ulong*) *GestaltPtr->tableH;		/* get a pointer to the orginal one */
	for (i=0; i<size; i+=4)						/* copy the original to the new */
		*destPtr++ = *srcPtr++;

	/** The selector has been validated by here, now find where the entry should	**/
	/** be in the table, whether it exists or not, and is the add or change valid?	**/

	myResult = noErr;							/* assume we find no errors */
	found = true;								/* assume it's in the table */
	if (!findLong(selector, &index))
	{
		if (replace)							/* trying to _change_ nonexistant selector? */
			myResult = gestaltUndefSelectorErr;
		else
		{
			SetHandleSize(tempTable, (GestaltPtr->slotsUsed + 1) * sizeof(LongEntry));
			if (*(short*)MemErr)				/* was there a problem? */
				myResult = memFullErr;
			else
				found = false;
		}
	}
	else
		if (!replace)							/* trying to add an existing selector? */
			myResult = gestaltDupSelectorErr;

	if (myResult != noErr)						/* any errors? */
	{
		DisposHandle(tempTable);				/* get rid of our temporary table */
		return(myResult);
	}

	/** index now contains the index that the entry should be put in at, 	**/
	/** so increase the table size by one entry, and shift everything above	**/
	/** index up by one entry. 												**/

	tablePtr = (LongEntryPtr) *tempTable;
	if (!found)									/* if not in table, add it */
	{
		for (i=GestaltPtr->slotsUsed; i > index; i--)	/* shift entries up by one */
		{
			tablePtr[i][0] = tablePtr[i-1][0];
			tablePtr[i][1] = tablePtr[i-1][1];
		}
		GestaltPtr->slotsUsed++;				/* there is now one more entry */
		tablePtr[index][0] = selector;			/* add the entry information */
	}
	if (replace)								/* if replacing, save old value */
		*oldProc = tablePtr[index][1];
	tablePtr[index][1] = value;					/* associate this value with the selector */

	/** Swap the tables that are used during a lookup. **/

	myHandle = GestaltPtr->tableH;
	GestaltPtr->tableH = tempTable;
	DisposHandle(myHandle);

	return(noErr);
} /*newGestalt*/


/*********************************************************************************
 *	function:	removeLong(selector, oldValue)
 *				ulong selector;
 *				ulong *oldValue;
 *	purpose:	removes the specified long from the table, and returns the old
 *				value.
 *	lastmod:	7/15/89
 *********************************************************************************/
OSErr
removeLong(ulong selector, ulong* oldValue)
{
	int index, i;
	LongEntryPtr tablePtr;

	if (!findLong(selector, &index))		/* the selector has to exist to delete it! */
		return(gestaltUndefSelectorErr);

	/** index now contains the index of the entry should be deleted			**/
	/** so decrease the table size by one entry, and shift everything above	**/
	/** index down by one entry. 											**/

	tablePtr = (LongEntryPtr) *GestaltPtr->tableH;
	*oldValue = tablePtr[index][1];			/* get the old value */
	for (i=index; i < (GestaltPtr->slotsUsed-1); i++) {	/* shift entries down by one */
		tablePtr[i][0] = tablePtr[i+1][0];
		tablePtr[i][1] = tablePtr[i+1][1];
	} /*for*/
	GestaltPtr->slotsUsed--;				/* there is now one less entry */

	SetHandleSize(GestaltPtr->tableH, GestaltPtr->slotsUsed * sizeof(LongEntry));

	return(noErr);
} /*removeLong*/


/*********************************************************************************
 *	function:	findLong(selector, index)
 *				ulong selector;
 *				int *index;
 *	purpose:	returns true if the specified entry is in the table, false other-
 *				wise.  If true is returned, index contains the index of the entry,
 *				otherwise, index will contain the index where the entry should be
 *				added.
 *	lastmod:	7/15/89
 *********************************************************************************/
OSErr
findLong(ulong selector, int* index)
{
	int i, min, max;
	LongEntryPtr tablePtr;

	tablePtr = (LongEntryPtr) *GestaltPtr->tableH;

	/** do a binary search on the table for the selector **/

	min = 0;
	max = GestaltPtr->slotsUsed-1;
	do {
		i = min + ((max - min) >> 1);		/* get middle of range */
		if (tablePtr[i][0] > selector)		/* are we too high? (is that possible?) */
			max = i;
		else if (tablePtr[i][0] < selector)	/* are we too low? */
			min = i+1;
		else {
			*index = i;						/* we got it! */
			return(true);
		}
	} while (max != min);					/* until we know it's not there */
	*index = min;

	return(false);
} /*findLong*/



