/************************************************************

Created: Thursday, September 7, 1989 at 9:11 PM
	CursorCtl.h
	C Interface to the Macintosh Libraries


	
	<<< CursorCtl - Cursor Control Header File >>>
	
	Copyright Apple Computer, Inc. 1985-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <3>	  8/8/91	JL		Update copyright

	This file contains:
	
	InitCursorCtl(newCursors) - Init CursorCtl to load the 'acur' resource
	RotateCursor(counter)	  - Sequence through cursor frames for counter mod 32
	SpinCursor(increment)	  - Sequence mod 32 incrementing internal counter
	Hide_Cursor()			  - Hide the current cursor
	Show_Cursor(cursorKind)   - Show the cursor

************************************************************/


#ifndef __CURSORCTL__
#define __CURSORCTL__

enum {HIDDEN_CURSOR,I_BEAM_CURSOR,CROSS_CURSOR,PLUS_CURSOR,WATCH_CURSOR,
	ARROW_CURSOR};
typedef unsigned char Cursors;

struct Acur {
	short n;		/*Number of cursors ("frames of film")*/
	short index;	/* Next frame to show <for internal use>*/
	short frame1;	/*'CURS' resource id for frame #1*/
	short fill1;	/*<for internal use>*/
	short frame2;	/*'CURS' resource id for frame #2*/
	short fill2;	/*<for internal use>*/
	short frameN;	/*'CURS' resource id for frame #N*/
	short fillN;	/*<for internal use>*/
};

typedef struct Acur acur,*acurPtr,**acurHandle;

#ifdef __cplusplus
extern "C" {
#endif
pascal void InitCursorCtl(acurHandle newCursors);
/*
	Initialize the CursorCtl unit. This should be called once prior to calling
	RotateCursor or SpinCursor. It need not be called if only Hide_Cursor or
	Show_Cursor are used. If NewCursors is NULL, InitCursorCtl loads in the
	'acur' resource and the 'CURS' resources specified by the 'acur' resource
	ids.  If any of the resources cannot be loaded, the cursor will not be
	changed.
	
	The 'acur' resource is assumed to either be in the currently running tool or
	application, or the MPW Shell for a tool, or in the System file.  The 'acur'
	resource id must be 0 for a tool or application, 1 for the Shell, and 2 for
	the System file.
	
	If NewCursors is not NULL, it is ASSUMED to be a handle to an 'acur' formatted
	resource designated by the caller and it will be used instead of doing a
	GetResource on 'acur'. Note, if RotateCursor or SpinCursor are called without
	calling InitCursorCtl, then RotateCursor and SpinCursor will do the call for
	the user the first time it is called.  However, the possible disadvantage of
	using this technique is that the resource memory allocated may have
	undesirable affect (fragmentation?) on the application. Using InitCursorCtl
	has the advantage of causing the allocation at a specific time determined by
	the user.
	
	Caution: InitCursorCtl MODIFIES the 'acur' resource in memory.	Specifically,
	it changes each FrameN/fillN integer pair to a handle to the corresponding
	'CURS' resource also in memory.  Thus if NewCursors is not NULL when
	InitCursorCtl is called, the caller must guarantee NewCursors always points to
	a "fresh" copy of an 'acur' resource.  This need only be of concern to a
	caller who wants to repeatly use multiple 'acur' resources during execution of
	their programs.
*/

pascal void RotateCursor(long counter); 
/*
	RotateCursor is called to rotate the "I am active" "beach ball" cursor, or to
	animate whatever sequence of cursors set up by InitCursorCtl. The next cursor
	("frame") is used when Counter % 32 = 0 (Counter is some kind of incrementing
	or decrementing index maintained by the caller). A positive counter sequences
	forward through the cursors (e.g., it rotates the "beach ball" cursor
	clockwise), and a negative cursor sequences through the cursors backwards
	(e.g., it rotates the "beach ball" cursor counterclockwise).  Note,
	RotateCursor just does a Mac SetCursor call for the proper cursor picture.
	  It is assumed the cursor is visible from a prior Show_Cursor call.
*/

pascal void SpinCursor(short increment);
/*
	SpinCursor is similar in function to RotateCursor, except that instead of
	passing a counter, an Increment is passed an added to a counter maintained
	here.  SpinCursor is provided for those users who do not happen to have a
	convenient counter handy but still want to use the spinning "beach ball"
	cursor, or any sequence of cursors set up by InitCursorCtl.  A positive 
	increment sequences forward through the curos (rotating the "beach ball"
	cursor clockwise), and a negative increment sequences backward through the
	cursors (rotating the "beach ball" cursor counter-clockwise).  A zero value
	for the increment resets the counter to zero.  Note, it is the increment, and
	not the value of the counter that determines the sequencing direction of the
	cursor (and hence the spin direction of the "beach ball" cursor).
*/

pascal void Hide_Cursor(void);
/*
	Hide the cursor if it is showing.This is this unit's call to the Mac
	HideCursor routine.Thus the Mac cursor level is decremented by one when this
	routine is called.
*/

pascal void Show_Cursor(Cursors cursorKind);
/*
	Increment the cursor level, which may have been decremented by Hide_Cursor,
	and display the specified cursor if the level becomes 0 (it is never
	incremented beyond 0).The CursorKind is the kind of cursor to show.  It is
	one of the values HIDDEN_CURSOR, I_BEAM_CURSOR, CROSS_CURSOR, PLUS_CURSOR,
	WATCH_CURSOR, and ARROW_CURSOR. Except for HIDDEN_CURSOR, a Mac SetCursor is
	done for the specified cursor prior to doing a ShowCursor.	HIDDEN_CURSOR just
	causes a ShowCursor call.  Note, ARROW_CURSOR will only work correctly if
	there is already a grafPort set up pointed to by 0(A5).
*/
#ifdef __cplusplus
}
#endif

#endif
