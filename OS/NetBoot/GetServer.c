/*
	File:		GetServer.c

	Copyright:	© 1989-1992 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	12/10/92	chp		Added an #include <string.h> to supply a prototype for memset().
		 <9>	11/23/92	DTY		Fix FillRect call in show_Icon so that this file compiles again
									with the new QuickDraw.h.
		 <8>	 2/27/91	PKE		KS: (affects ROM build only) Change thesocket from char back to
									short to match current AppleTalk.h (see <6>). Fixes Mac32 build.
									Per Kevin Stinson, because he doesn't have write access.
		 <7>	11/18/90	PWD		Restore our borrowed lomem (B50) to -1 after closing the socket.
		 <6>	  10/9/90	JAL		Changed theSocket to a char to match change in AppleTalk.h.
		 <5>	  3/9/90	PWD		Faster server lookup; more aggressive retries for missed image
									blocks.
		 <4>	 2/20/90	PWD		More aggressive about sending wks_reqs if the server is found.
		 <3>	  2/1/90	PWD		re-checking in after fighting with projector
		 <3>	  2/1/90	PWD		Always allocate memory on the heap.
	   <1.1>	12/12/89	PWD		Added support for self-authenticating images
	   <1.0>	10/30/89	PWD		Adding to EASE

	To Do:
*/

/*EASE$$$ READ ONLY COPY of file “GetServer.c”
** 1.1	PWD 12/12/1989 Added support for self-authenticating images
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */
/*	File:	GetServer.c
	Project:Das Boot
	Author:	Patrick Dyson
	
	These routines find the server, set up our socket listener, and send the
	user map request.
*/
/*
Modification History
--------------------------
5/30/89 10:19:20 AM	: New Today
5/31/89 2:49:45 PM	: find_server done, support routines in progress.
5/31/89 8:10:25 PM	: support routines done. To do: socket listener mods, open/close skt
6/1/89 7:29:03 PM	: socket listener routine for user record reply done.
6/5/89 2:14:22 PM	: socket listener does image packets now, separate C glue for that 
						packet type. Single copy restored for image data.
6/9/89 9:52:29 AM	: request backoff for user requests done. Receive image bitmap setting
						put into socket listener. Starting image data request retransmission,
						history, and backoff.
6/14/89 1:23:24 PM	: Boot protocol first phase done. Retransmissions constant, dynamic memory,
						statistics, etc.
6/19/89 6:33:36 PM	: Dynamic retransmission backoff during image reception. More errors checked.
==================
TO BE DONE
==================
•	Multiple-section images
•	Memory allocation & sizing schemes

date -s


*/

#include	<Types.h>
#include	<Errors.h>
#include	<Memory.h>
#include	<OSUtils.h>
#include	<Devices.h>
#include	<QuickDraw.h>	/* for netBoot.h */
#include	<AppleTalk.h>	/* just for kicks !*/
#include	<Events.h>
#include	<Resources.h>
#include	<SysEqu.h>		/* BufPtr */
#include	<Packages.h>	/* NumToString */
#include	<string.h>		/* memset() */

#include	"netBoot.h"		/* general equates for network booting */

#include	"ATBootEqu.h"	/* the equates for the ATBoot driver */


/* setupGrafWorld(&DQDGlobals); */

void	setupGrafWorld(GrafWorld *g)
{
	mySetA5((int)&(g->globs));
	InitGraf((Ptr)&(g->thePort));
	OpenPort(&(g->ourPort));
};

void	killGrafWorld(GrafWorld *g)
{
	ClosePort(&(g->ourPort));
};


void	centerRect(	Rect	*r,
					short	HOffset,
					short	VOffset)
{
	r->top	+= ((r->bottom-r->top) >> 1) - VOffset;	/* center and offset */
	r->left	+= ((r->right-r->left) >> 1) - HOffset;
	r->bottom = r->top + VOffset + VOffset;
	r->right  = r->left + HOffset + HOffset;
};


/*	show_Icon

	Plot the passed icon into the passed grafworld. The grafworld must have been set up
	by setting A5 and calling setupGrafWorld.

	if erase is non-zero we fill the to-be-plotted space with gray first to avoid
	holes under small, masked icons.
	
*/
extern void	myGetMask();
extern Ptr	myGetIcn(int whichIcon);

void	show_Icon(GrafWorld	*g,Ptr	iconPtr,int	erase)
{
		BitMap		srcBits,maskBits;
		Rect		dstRect = g->ourPort.portRect;
		
		centerRect(&dstRect,16,16);		/* make it the middle of the screen */
		
		SetPort(&(g->ourPort));
		srcBits.baseAddr	= iconPtr;
		srcBits.rowBytes	= 4;
		SetRect(&(srcBits.bounds),0,0,32,32);
		
		maskBits.baseAddr	= (Ptr)myGetMask;
		maskBits.rowBytes	= 4;
		SetRect(&(maskBits.bounds),0,0,32,32);
		
		if (erase) FillRect(&dstRect,&(g->gray));	// erase any remnant icon.
		
		CopyMask(&srcBits,&maskBits,&(g->ourPort.portBits),
					&(srcBits.bounds),&(maskBits.bounds),&dstRect);

};

void	showProgress(register GrafWorld	*g)
{
	Ptr		p;
	int		erase = 0;		// set to 1 if erase before plot icon.
		
	if (g->curIcon >= 3) return;

	if (g->curIcon == 0) erase = 1;
		
	p = myGetIcn(g->curIcon);
	
	g->curIcon++;
		
	show_Icon(g,p,erase);
};


/*	send_wksURequestPacket takes a fully formed packet and a destination address
	and issues a synchronous ddpWrite to send the packet. It returns any error.
*/

OSErr	send_wksURequestPacket(	RequestPacket	*req,
								AddrBlock		to)
{	char	DDPheader[17];
	
	/*	At this point the socket, checksumflag, and wds 
		pointer are set up. We need to set up the wds block */
	
	/* stamp the packet */
	req->record.timestamp = TickCount();
	
	/* build the wds */
	BuildDDPwds(	(Ptr) req->wds,					/* the wds for this write */
					(Ptr) DDPheader,					/* stuffed by this call */
					(char *) &(req->record),		/* the packet to send */
					to,							/* the destination address */
					BOOTDDPTYPE,				/* the DDP type */
					sizeof(UserRecordRequest));	/* the packet size */

	return PWriteDDP(&(req->MPPpb),false);
};

/*	do_synch_lookup performs a quick, small synchronous lookup for servers and 
	returns any result in nbpBuffer, any non-fatal error in the result field
	of nbpStuff, and any fatal error as a function result.
*/
#define		SYNCH_INTERVAL	2		/* (eight tick units) Randy Carr numbers (InterPoll) */
#define		SYNCH_COUNT		2		/* same, takes 1/2 second... */
#define		TO_GET			2

OSErr	do_lookup(	Str255			type,		/* the type string to lookup */
					Str255			name,
					Ptr				nbpBuffer,	/* the buffer to write into */
					nbpLookupRecord	*nbpStuff,	/* working storage */
					short			numToGet,
					Boolean			asynch,
					char			interval,
					char			count)
{
	register MPPParamBlock	*mppPb = &(nbpStuff->myABRecord);
	
	NBPSetEntity(nbpStuff->myEntry,name,type,"\p*");
		
	mppPb->NBPentityPtr		= &(nbpStuff->myEntry[0]);
	mppPb->NBPinterval		= interval;			/* magic numbers */
	mppPb->NBPcount			= count;
	mppPb->NBPretBuffPtr	= nbpBuffer;
	mppPb->NBPretBuffSize	= MAX_NBP_BUFFER;
	mppPb->NBPmaxToGet		= numToGet;
	mppPb->MPPioCompletion	= NULL;

	/* there are no non-fatal errors */
	
	return PLookupName(&(nbpStuff->myABRecord),asynch);
};


void	make_wksURequestPacket(	UserRecordRequest	*requestInfo,	/* to fill out req */
								RequestPacket	*r)
{	
		/* and the DDP info.. */
	
	r->MPPpb.DDPsocket			= BOOTSOCKET;
	r->MPPpb.DDPchecksumFlag	= false;
	r->MPPpb.DDPwdsPointer		= (Ptr)(r->wds);
	
		/* and the user info..  */
	r->record	= *requestInfo;
		/* moved to the wds info stage */
	
};

void	myNumToStr(short number, Str255 string)
{	
	char	*translate = "0123456789ABCDEF";
	
	string[1] = *(translate + (number & 0x000F));
	string[2] = *(translate + ((number >> 4) & 0x000F));
	string[3] = *(translate + ((number >> 8) & 0x000F));
	string[4] = *(translate + ((number >> 12) & 0x000F));
	string[0] = (char)4;
};

/*	find_server looks for the server in a structured way. First, send our 
	request to hint, if valid. Next, do a synchronous lookup for the first
	two servers with a short timeout and small retry rate. 
	
	The socket listener communicates with the world through it's globals struct.
	This includes our current image id and boot server, buffers, and errors.
		
	The hint that we stored is given one directed request to respond, then is 
	expected to get caught by the two succeeding lookups.
	
	This routine has been changed to find the first appropriate server - the one
	with a name matchine the number stored in pram.
*/

struct	AddrBlock	find_server(	unsigned char		interval,
									unsigned char		count,
									Str255				type,	/* what to nbp for */
									unsigned short		number, /* who to nbp for */
									UserRecordRequest	*requestInfo,	/* to fill out req */
									SktLsnGPtr			SktGPtr)/* the socket listeners globals */
{	RequestPacket	req;
	Ptr				nbpBuffer = NULL;	/* buffer of nbp names table entries */
	nbpLookupRecord	nbpStuff;			/* buffer for nbplookups */
	AddrBlock		server_addr;
	EntityName		curEntity;	/* for nbpextract */
	AddrBlock		to;			/* for nbpextract */
	short			tuple = 1;	/* for nbpextract */
	Str255			server_ID;	/* for the lookup */


	/* make sure our socket listener is doing things, clear any requests */
	SET_INVALID(server_addr);
	if (SktGPtr == NULL)	goto exit;
	
	SktGPtr->bootImageID	= INVALID_IMAGE;
	
	/* make the server name */
	myNumToStr(number,&server_ID);
	
	/* build our request packet */
	make_wksURequestPacket(requestInfo,&req);

#ifdef USE_HINT
	/* send a request to the hint, if it is valid */
	if ((*(int *)&hint) != INVALID_ADDR) {
		short error;
		register int now = TickCount();

		error = send_wksURequestPacket(&req,hint);
		// wait a short while for a response... unless we got an error (like no such address)
		now = TickCount();
		while (((TickCount()-now) < SktGPtr->retransThreshold) &&
				(SktGPtr->bootImageID == INVALID_IMAGE) && (error == 0)) ;

		};
#endif
	nbpBuffer = NewPtrSys(MAX_NBP_BUFFER);
	if (nbpBuffer == NULL) 	goto exit;

	/* do a synchronous lookup for the first two servers. */
	if (SktGPtr->bootImageID == INVALID_IMAGE)
		if (do_lookup(type,server_ID,nbpBuffer,&nbpStuff,1,false,interval,count)) 	goto exit;	// if an error...

	/* send requests to any valid replies */
	
	/* while the soket listener hasn't found a reply && we are not out of servers
		&& nbpextract doesn't have a problem, send requests. The key is
		(SktGPtr->bootImageID == INVALID_IMAGE) which will change when we
		get a valid response. */

	while ((SktGPtr->bootImageID == INVALID_IMAGE) && 
			(tuple <= nbpStuff.myABRecord.NBPnumGotten) &&
			((nbpStuff.errCode = NBPExtract(nbpBuffer,nbpStuff.myABRecord.NBPnumGotten,
				tuple++,&curEntity,&to)) == noErr)) {
				
		send_wksURequestPacket(&req,to);
		
		}; /* while loop */

		/* if we found a bootserver, we stop looking, start sending (wait retrans) */
		// timeout is nbpVars.interval * 8 * 8 which is 8 ticks per interval unit, eight times
		// We retransmit four times, at timeout/4 = (interval * 8 * 2)
	
	if (nbpStuff.myABRecord.NBPnumGotten > 0)
		{	register int	start = TickCount(),		// at the tone, the time is...
							retrans_interval = interval<<4;
			int				last_sent = start;
			int				max_wait;					// how long we can wait 
			
			max_wait = retrans_interval<<2;				// standard retrans interval*8
			
			while (((TickCount()-start) < max_wait) &&
					(SktGPtr->bootImageID == INVALID_IMAGE)) 
					
				if ((TickCount()-last_sent) > retrans_interval)	{
					last_sent = TickCount();
					send_wksURequestPacket(&req,to);
					};
			};
exit:
	if (SktGPtr->bootImageID != INVALID_IMAGE) server_addr = SktGPtr->server_addr;		/* stuff the found server addr */
					
	if (nbpBuffer != NULL) DisposPtr(nbpBuffer);
	
	return	server_addr;

};


/*	CLISTENER is called by the socket listener just after it reads the packet into
	an area in the globals. The listener checks that the packet is of our ddptype before
	calling, all other checks are left to us.
	
	We handle only user record replies. Packet filtering is done by the socket listener.
	Communication with other routines is done through the socket listener globals area, 
	a pointer to which is passed to us by the listener.
	
	User record replies are tested for validity, and return result. Bad records, or 
	those with non-zero error codes, and we update the tupletable. A good record and
	we update the image id in the globals. This makes the findserver routine quit looking
	and booting continues.
	
	We update the retransmission timer with the round trip time*4.
	
*/

void	CLISTENER(	AddrBlock	from,		/* packet source address */
					SktLsnGPtr	SktGPtr )	/* pointer to shared globals */
{	

	if (SktGPtr->u.userReply.osID == SktGPtr->machineID) {
			/* did we succeed ?*/
		if (SktGPtr->u.userReply.result == noErr) {
		
			/* no need to update the tuple table, just signal that we got a good one */
			
			SktGPtr->bootImageID = SktGPtr->u.userReply.imageID;
			SktGPtr->server_addr = from;
			
			/* now update the retransmit timer to (4*roundtrip). The packet was stamped
				at the time it left, we subtract that from the time now & *4 it */
			/* we update the roundtrip delay for the next portion - the image reception.
				*/
			SktGPtr->roundTrip = (TickCount()-SktGPtr->u.userReply.userData) << 2;
			SktGPtr->roundTrip = (SktGPtr->roundTrip < DEFAULT_ROUNDTRIP) ? DEFAULT_ROUNDTRIP : SktGPtr->roundTrip;
			};
		};
};

/*	DOIMAGEDATA is called by the socket listener AFTER reading the packet into the 
	appropriate area in the image storage buffer. The main task is to "do the protocol
	stuff". This involves retransmission timers, reception bitmaps, etc.
	
	Image data packets are stored in the image data area, and several tracking fields are
	updated. The first is the image bitmap, set to indicate a new packet. Next is the
	progress and retransmission timers. We update the retransmission timer. If it is
	ours and we didn't have one already, we also update the progress timer. This allows
	the user-level routine to figure out when to retransmit an image request.
	
	The handler passes -1 in goodPacket if the packet was from our server and for our
	image, but one we already had. It passes 0 if the above and we didn't have this
	one yet.
*/

void	DOIMAGEDATA(	SktLsnGPtr	SktGPtr,	/* pointer to shared globals */
						int			newOne)		/* 0 if new packet, -1 if have already */
{
	int		now	= TickCount();
	
		/* a new, good packet has arrived */
	if (newOne == 0)	{

		if (SktGPtr->lastRetransmission) { /* non-zero if no data packets yet */
//			SktGPtr->roundTrip = ((SktGPtr->roundTrip * SMOOTHING_FACTOR) + 
//								  (now-SktGPtr->lastRetransmission)) / (SMOOTHING_FACTOR + 1);
			SktGPtr->lastRetransmission = 0;
			};
			
		SktGPtr->progressTimer = now;
		SktGPtr->packetsReceived++;
		};
	
		/* any packet resets these */
	SktGPtr->trafficTimer = now;	/* and record when we got it */
};

void	makeImageRequest(	ImageRequestPacket		*r,
							SocketListenerGlobals	*g)
{	unsigned	short	i,mybitmapsize,lastbits = 0;

	r->MPPpb.DDPsocket			= BOOTSOCKET;
	r->MPPpb.DDPchecksumFlag	= false;
	r->MPPpb.DDPwdsPointer		= (Ptr)(r->wds);

	r->record.Command	= 3;
	r->record.pversion	= 1;
	
	r->record.bir.imageID	= g->bootImageID;
	r->record.bir.section	= 0;
	r->record.bir.flags		= 0;
	
	mybitmapsize = g->lastBlockNo / 8;	/* one bit block, eight bits per byte */
	if (lastbits = (g->lastBlockNo >> 3)) {
		mybitmapsize++;
		};
	
	for (i=0;i<mybitmapsize;i++) r->record.bir.bitmap[i] = 0xFF;
	if (lastbits) r->record.bir.bitmap[mybitmapsize-1] = 0xFF;
};

/*	makeBitmap takes two bitmaps: the already-received bitmap with a bit set for each 
	block received, and the request bitmap which needs a bit set for each block that we
	don't have. We make the dest = ~the source.
*/
void	makeBitmap(	char	*receivedMap,
					char	*retransMap,
					short	sizeInBits)
{
	short	size = (sizeInBits / 8);
	
	while (size--) *retransMap++ = ~(*receivedMap++);
	
	/* if there is a partial byte on the end, doittoit */
	if (sizeInBits >> 3) {
		*retransMap = ~(*receivedMap);
		};
};


OSErr	sendImageRequest(	ImageRequestPacket		*r,
							AddrBlock				to,
							SocketListenerGlobals	*g)
{	char	DDPheader[17];
	
	/*	At this point the socket, checksumflag, and wds 
		pointer are set up. We need to set up the wds block */
	
	/* build the wds */
	BuildDDPwds(	(Ptr) r->wds,				/* the wds for this write */
					(Ptr) DDPheader,			/* stuffed by this call */
					(char *) &(r->record),		/* the packet to send */
					to,							/* the destination address */
					BOOTDDPTYPE,				/* the DDP type */
				/* header + bitmap size + 1 if the bitmap is not evenly divided by 8 */
					8+(g->lastBlockNo / 8)+((g->lastBlockNo >> 3) ? 1 : 0));	/* the packet size */

	return PWriteDDP(&(r->MPPpb),false);

};

extern	void	BOOTLISTEN();
extern	void	BOOTSTORAGE(Ptr p);

/*	get_image implements the Apple Boot Protocol Phase II. It looks up the server, sends
	user requests, asks for an image, and does the retransmissions as necessary.
	
	get_image returns 0 if all went well, an error code if not. The error codes
	are defined and enumerated in ATBootEqu.h. In the event of an error the
	code backs out as necessary, disposing and closing what needs be. The error
	code is held in ret_val and disposal goes through a common exit (err_exit).
*/

#define		BITMAP_BYTES		512		/* bytes in a bitmap, one based */


extern int	get_image(	
				int					lookup_timeout,	/* how long (ticks) to look for the server */
				unsigned short		server_ID,
				UserRecordRequest	*requestInfo,	/* to fill out req */ 
				unsigned char		nbpVars,		/* nbp timeouts for lookup */
				Ptr					*buffer,		/* a place to return the image... */
				AddrBlock			*netServerAddr,	/* a place to return the server address */
				BootPktRply			*ur)				/* place to return the user record */
{
	
	SocketListenerGlobals	g;	/* our socket listener globals */
	short					error,i;
	short					thesocket = 0;		/* show socket not opened */				/*<8>*/
	AddrBlock				theserver;			/* to be returned by findserver */
	unsigned char			interval,			/* place for unpacked nbpVars */
							count;
	int						now;
	int						ret_val = 0;		/* function result holder */
	ImageRequestPacket		imageRequest;
	char					bitmap[BITMAP_BYTES];		/* bitmap of outstanding image packets */
	int						OldA5;				/* place to stash caller's A5 */
	GrafWorld				GrafStuff;
	
	memset((char *)&GrafStuff, 0, sizeof(GrafWorld));

	OldA5	= myGetA5();
	setupGrafWorld(&GrafStuff);

	/* set up the socket listener globals */
	g.bootImageID		= INVALID_IMAGE;
	g.machineID			= MACHINE_MAC;
	g.bitmapBase		= (Ptr) bitmap;
	g.lastBlockNo		= 0;
	g.packetsReceived	= 0;
	g.imageBuffer		= NULL;
	g.blockSize			= 0;
	g.trafficTimer		= 0;
	g.progressTimer		= 0;
	g.retransThreshold	= lookup_timeout >> 3;				// start with 1/8th the time
	g.roundTrip			= DEFAULT_ROUNDTRIP;
	g.backOff			= DEFAULT_BACKOFF;
	g.lastRetransmission		= 0;
	(* (int *)&g.server_addr) 	= INVALID_ADDR;				// cast for C 3.0
	
	/* set up the socket listener's globals pointer */
#ifdef	DEBUG
	DebugStr("\pSetting up listener globals");
#endif
	BOOTSTORAGE((Ptr) &g);
	
	/* open appletalk */
	error = MPPOpen();
	
	if (error) return error;
	
	/* build the nbpVars */
	if (nbpVars != 0x00) {
		interval = (nbpVars & 0x0F) * 4;	// low nibble is interval between lookups
		count	 = (nbpVars & 0xF0) >> 4;	// high nibble is count of lookups
		}
	else {	
		interval = 4;
		count	 = 1;
		};

	/* open our socket */
	thesocket	= BOOTSOCKET;
	error = DDPOpenSocket(&thesocket,(Ptr)BOOTLISTEN);
	if (error) return error;

	/* findserver */
	requestInfo->type		= 1;
	requestInfo->version	= 1;
// set by caller from pram:	requestInfo->machineID	= 1;
	requestInfo->timestamp	= 0;
// set by caller from pram:	strcpy(requestInfo->userName,"Patrick");
	
	SET_INVALID(theserver);
	theserver	= find_server(interval,count,"\pBootServer",server_ID,requestInfo,&g);
		
	if ((g.bootImageID != INVALID_IMAGE) && 
		((*(int *)&theserver) != INVALID_ADDR)) {	/* we found an image */
		
		/* set the globals to the newly acquired values */
		g.blockSize		= g.u.userReply.blockSize;	/* send size */
		g.lastBlockNo	= g.u.userReply.imageSize - 1;	/* even number of blocks */
		
		if ((g.lastBlockNo/8 >= BITMAP_BYTES-1) || 		// bigger than we can ask for
		   ((g.lastBlockNo*g.blockSize) > 
		   ((*(long *)(BufPtr)) / 4)))	{				// bigger than we can fit
			ret_val = IMAGE_TOO_BIG;
			goto err_exit;
			};
			
		if ((g.imageBuffer	= NewPtrSys(g.u.userReply.imageSize*g.u.userReply.blockSize)) == NULL) {
			ret_val = IMAGE_TOO_BIG;
			goto err_exit;
			};

		/* build the image request */
		makeImageRequest(&imageRequest,&g);
		
		/* reset the machine */
		for (i=0;i<(g.lastBlockNo/8)+1;i++) bitmap[i] = 0x00;
		
			/* g.packetsReceived is 1 based, g.lastBlockNo is zero based. This
				makes the limit comparison below a <= one... */

		while ((g.packetsReceived <= g.lastBlockNo) && (g.retransThreshold < lookup_timeout)) {
			/* if not progress or no packets, retransmit request */
			now = TickCount();
			
			if ((g.packetsReceived*3 / g.lastBlockNo) >= GrafStuff.curIcon)
				showProgress(&GrafStuff);				// tell the world that we are working on it
			
			if (((now-g.trafficTimer)  > g.retransThreshold) ||	/* we got an image packet */
				((now-g.progressTimer) > g.retransThreshold*50) 
				){ 
				if (g.lastRetransmission != 0) {	/* no packets since last request */
					g.backOff += g.backOff;			/* double the backoff factor */
					g.retransThreshold = g.backOff*g.roundTrip;	/* update the retransmission */
					};
					
				makeBitmap(bitmap,imageRequest.record.bir.bitmap,g.lastBlockNo);
				g.trafficTimer = g.progressTimer = g.lastRetransmission = now;
				(void) sendImageRequest(&imageRequest,theserver,&g);
				};		
			}; /* while packet not in... */
			
		}
	else	ret_val = NOT_FOUND;	/* we didn't find an image... */

err_exit:
	/* dispos of the graf world */
	killGrafWorld(&GrafStuff);
	/* restore A5 */
	mySetA5(OldA5);
	
	/* close the socket */
	if (thesocket) 
		error = DDPCloseSocket(thesocket);

	/* reset our borrowed lomem */
	BOOTSTORAGE((Ptr) -1L);						// PWD <7> reset B50 to -1
	
	/* return that most treasured buffer! */
	if ((g.imageBuffer != NULL) && (ret_val)) DisposPtr((Ptr) g.imageBuffer);
	else	*buffer = g.imageBuffer;
	
	if (ret_val) return ret_val;
	
	if (g.packetsReceived <= g.lastBlockNo)		return TIMED_OUT;
	if ((* (int *)&theserver) == INVALID_ADDR) 	return NOT_FOUND;
	
	*(int *)netServerAddr = *(int *)&theserver;	// return the server addr for pram hint
	BlockMove((Ptr)&(g.u.userReply),(Ptr)ur,sizeof(BootPktRply)); // return the user record
	
	return ret_val;
};

