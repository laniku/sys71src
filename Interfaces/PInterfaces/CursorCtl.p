{
Created: Tuesday, August 2, 1988 at 12:24 PM
	CursorCtl.p
	Pascal Interface to the Macintosh Libraries

	
	<<< CursorCtl - Cursor Control Interface File >>>
	
	
	Copyright Apple Computer, Inc. 1984-1991
	All rights reserved
    This file is used in these builds: ROM System


	Change History (most recent first):

		 <2>	  8/8/91	JL		Updated Copyright.

	To Do:
	
	This file contains:
	
	InitCursorCtl(newCursors) - Init CursorCtl to load the 'acur' resource
	RotateCursor(counter) - Sequence through cursor frames for counter mod 32
	SpinCursor(increment) - Sequence mod 32 incrementing internal counter
	Hide_Cursor() - Hide the current cursor
	Show_Cursor(cursorKind) - Show the cursor
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT CursorCtl;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingCursorCtl}
{$SETC UsingCursorCtl := 1}


TYPE

{ Kinds of cursor supported by CursorCtl }
Cursors = (HIDDEN_CURSOR,I_BEAM_CURSOR,CROSS_CURSOR,PLUS_CURSOR,WATCH_CURSOR,
	ARROW_CURSOR);

acurPtr = ^Acur;
acurHandle = ^acurPtr;
Acur = RECORD
	n: INTEGER; 		{Number of cursors ("frames of film")}
	index: INTEGER; 	{ Next frame to show <for internal use>}
	frame1: INTEGER;	{'CURS' resource id for frame #1}
	fill1: INTEGER; 	{<for internal use>}
	frame2: INTEGER;	{'CURS' resource id for frame #2}
	fill2: INTEGER; 	{<for internal use>}
	frameN: INTEGER;	{'CURS' resource id for frame #N}
	fillN: INTEGER; 	{<for internal use>}
	END;



PROCEDURE InitCursorCtl(newCursors: UNIV acurHandle);
{ Initialize the CursorCtl unit. This should be called once prior to calling
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
 }

PROCEDURE RotateCursor(counter: LONGINT);
{ RotateCursor is called to rotate the "I am active" "beach ball" cursor, or to
animate whatever sequence of cursors set up by InitCursorCtl. The next cursor
("frame") is used when Counter % 32 = 0 (Counter is some kind of incrementing
or decrementing index maintained by the caller). A positive counter sequences
forward through the cursors (e.g., it rotates the "beach ball" cursor
clockwise), and a negative cursor sequences through the cursors backwards
(e.g., it rotates the "beach ball" cursor counterclockwise).  Note,
RotateCursor just does a Mac SetCursor call for the proper cursor picture.
  It is assumed the cursor is visible from a prior Show_Cursor call.
 }

PROCEDURE SpinCursor(increment: INTEGER);
{ SpinCursor is similar in function to RotateCursor, except that instead of
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
 }

PROCEDURE Hide_Cursor;
{ Hide the cursor if it is showing.This is this unit's call to the Mac
HideCursor routine.Thus the Mac cursor level is decremented by one when this
routine is called.
 }

PROCEDURE Show_Cursor(cursorKind: Cursors);
{ Increment the cursor level, which may have been decremented by Hide_Cursor,
and display the specified cursor if the level becomes 0 (it is never
incremented beyond 0).The CursorKind is the kind of cursor to show.  It is
one of the values HIDDEN_CURSOR, I_BEAM_CURSOR, CROSS_CURSOR, PLUS_CURSOR,
WATCH_CURSOR, and ARROW_CURSOR. Except for HIDDEN_CURSOR, a Mac SetCursor is
done for the specified cursor prior to doing a ShowCursor.	HIDDEN_CURSOR just
causes a ShowCursor call.  Note, ARROW_CURSOR will only work correctly if
there is already a grafPort set up pointed to by 0(A5).
 }


{$ENDC}    { UsingCursorCtl }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

