/*
	File:		TerminalToolPrivate.h

	Contains:	Private interfaces for terminal tools

	Written by:	Byron Han

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 3/14/90	BBH		first checked in
	
		
	--------before move to BBS------	
		<11>	 2/20/90	BBH		moved constants for pattern indices into xtoolpatterns.h
		<10>	 2/19/90	BBH		add CurFMInput low memory global
		 <9>	 2/19/90	BBH		add constants for indices into the sysPatListID
		 <8>	 2/19/90	BBH		Added constants for accessing local ID of the STR# containing
									the terminal tool bell and click sound names and the indices as
									well
				6/26/89		BBH		Added LineDataBlock and tmPeekLineMsg
				6/7/89		kaz		¥ Moved LineInfoRec here from TMIntf files

	To Do:
*/

#ifndef __TERMINALTOOLSPRIVATE__
#define __TERMINALTOOLSPRIVATE__

/*	Private Tool Messages */
#define			tmPeekLineMsg		200

struct LineInfoRec {
		Ptr				linePtr;
		short			lineSize;
		Ptr				attrPtr;
		short			attrSize;
		Ptr				lineAttrPtr;
		short			lineAttrSize;
};

#ifndef _cplusplus
typedef struct LineInfoRec LineInfoRec;
#endif

typedef LineInfoRec *LineInfoPtr;
typedef	LineInfoRec	**LineInfoH;


#endif __TERMINALTOOLSPRIVATE__
