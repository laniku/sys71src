/*EASE$$$ READ ONLY COPY of file Ònewfind.cÓ
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */
struct	addrblock	find_server(	struct	AddrBlock	hint,	/* last server we booted */
									Str255				type,	/* what to nbp for */
									int					timeout,/* how long, total, to look */
									UserRecordRequest	*requestInfo,	/* to fill out req */
									SktLsnGPtr			SktGPtr)/* the socket listeners globals */
{
	Boolean		send_confirm = false;	// send an nbpconfirm first (hint was valid)
	register	shakjhd		*globals;	// pointer to our struct if we have a lookup going on
	EntityName		curEntity;			// for nbpextract 
	AddrBlock		to;					// for nbpextract
	
	globals = SktGPtr->lookupBuffer;	// dereference for speed and sanity
	
	if (globals == NULL) {
	
		// Allocate the buffer and set the flag that the lookup is done to indicate
		// that we should start another one
		globals = SktGPtr->lookupBuffer = (shakjhd *) NewPtr(sizeof(shakjhd));
		if (globals == NULL) return MemError();
		
		globals->lookup_done = true;
		
		
		if (hint == 0) {
			// build the guest booting lookup request
			}
		else if (hint == FF) {
			// build the lookup from the pram id
			}
		else {
			// send an nbp confirm to the hint with the id from pram.
			//
			send_confirm = true;
			}
		}
	
	if (send_confirm) {
		globals->error = PConfirmName(&(globals->myABRecord),false);	// send synchronous confirm
		};

	// Now start the lookup to the server. We hang around one second the first time,
	// later just checking the buffer and continuing.

	if (globals->myABRecord.MPP.ioResult <= 0) {	// if the call has completed

		globals->error = NBPExtract(globals->nbpBuffer,					// the lookup buffer
									nbpStuff.myABRecord.NBPnumGotten,	// number of valid buffer entries
									1,									// we only want one
									&curEntity,							// copy the object name here
									&to);								// copy the address here
									
		if (globals->error == 0) {
			globals->error = get_user_record(globals);
			if () {
				DisposPtr((Ptr)globals);
				SktGPtr->lookupBuffer = NULL;
				return true;
				}
			else	{
				return false;		
				}
			}
		else {		// not found yet, start another lookup
			// Start another lookup		
			};
		};
		

