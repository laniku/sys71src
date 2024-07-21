/*
	File:		TerminalsPriv.h

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/14/90	BBH		first checked in

	To Do:
*/

#ifndef	__TerminalPriv__
#define	__TerminalPriv__

struct LineDataBlock {
		Ptr				dataPtr;
		long			dataSize;
		Ptr				attrPtr;
		long			attrSize;
		long			reserved;
};

#ifndef _cplusplus
typedef struct LineDataBlock LineDataBlock;
#endif

extern pascal void TMPeekLine(TermHandle hTerm, short lineNo, LineDataBlock *theLineData);
#endif	__TerminalPriv__