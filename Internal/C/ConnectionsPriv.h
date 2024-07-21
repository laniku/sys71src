/*
	File:		ConnectionsPriv.h

	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 8/27/91	JSM		Cleanup header.
		 <2>	 1/14/91	CP		Added cmStatushConnLocked constants (a new flags field bit)
									<BBH>
		 <1>	 3/14/90	BBH		first checked in

*/

#ifndef	__ConnectionsPriv__
#define	__ConnectionsPriv__

//	private data structures for the Connection Manager

/*	private bits of the flags field of the connection record */
enum {
	cmStatushConnLocked	= 1 << 15		// connection handled was already locked
};

typedef struct CMSearchBlock {
		QElemPtr		qLink;
		short			qType;
		Str255			theString;
		ProcPtr			callBack;
		short			flags;
} CMSearchBlock, *CMSearchBlockPtr;

typedef struct CMSearch {
		long				hashValue;
		unsigned char		bufferPtr;
		unsigned char		padding;
		unsigned char		buffer[256];
		ProcPtr				ReadCallBack;
		Ptr					ReadBuffer;
		short				ReadChannelIn;
		QHdr				theQueue;
		Boolean				hashNotValid;
} CMSearch, *CMSearchPtr;

#endif	__ConnectionsPriv__