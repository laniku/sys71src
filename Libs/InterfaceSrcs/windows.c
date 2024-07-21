/*
	File:		windows.c
	Written by:	Helder
	Copyright:	© 1991 by Apple Computer, Inc., all rights reserved.
	Change History (most recent first):

		 <2>	10/16/91	stb		change result from int to short
*/

#include <types.h>

pascal Boolean TrackBox(w, p, pc)
 char *w;
 Point p;
 short pc;
 extern 0xA83B;

short trackbox(w, pptr, pc)
char *w;
Point *pptr;
short pc;
{
	return TrackBox(w, *pptr, pc);
}
