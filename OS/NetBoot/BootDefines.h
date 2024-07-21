/*EASE$$$ READ ONLY COPY of file ÒBootDefines.hÓ
** 1.0	PWD 10/30/1989 Adding to EASE
** END EASE MODIFICATION HISTORY */
#define			osMax				10

#define			coffeeBreak			5	/* # of packets to process before serviceing to another request */
#define			sleeptime			0	/* used in waitnextevent */

#define			rootDirID			2	/* dir id of root is always 2 in HFS */

#define			kSysEnvironsVersion	1	/* used with sysEnvirons call */

#define			userNameLength		32	/* bytes in a user name + pascal len byte */
#define			serverNameLength	33	/* bytes in a server name + pascal len byte */
#define			zoneNameLength		33	/* bytes in a zone name + pascal len byte */
#define			volNameLength		32	/* bytes in volume name + pascal len byte */
#define			appNameLength		32	/* bytes in application name + pascal len byte */


#define			recordErr			-1  /* error opening or reading user record */
#define			noImageErr			-2	/* no image for machine of the request's type */

#define			itemMax				10	/* max # of requestBuf items */
#define			ABPSckt 			10	/* Socket # reserved for use with this protocol */
#define			thispversion		1	/* ABP version */

#define			User_record_request	1	/* from workstation */
#define			User_record_reply	2	/* from server */
#define			Boot_image_request	3	/* from workstation */
#define			Boot_image_reply	4	/* from server */
#define			Image_done			5	/* from server */
#define			User_record_update	6	/* from workstation */
#define			User_update_reply	7	/* from server */

#define			AShandle			0x00000B50	/* handle to AppleShare fileserver globals */

#define			ABP					10	/* Atalk Boot Protocol DDP type */	
#define			MaxIDs				3	/* Number of machines supported by this init 0,1,2 */
#define			bitmapsize			512 /* max bytes in a bitmap */
#define			disksector			512 /* # of image bytes we send at a time */

#define			imageCreator		'ATBT'	/* file creator for image files used with booting */
#define			imageType			'IMAG'	/* file type for image files used with booting */


/*
	Resource ID constants.
*/
#define	vbltaskID		100				/* id of our vbl task code resource */

#define	appleID			128 			/* This is a resource/menu ID */
#define	fileID 			129 			/* ditto */
#define	editID 			130 			/* ditto */
#define	serverID		131				/* ditto */


#define	appleMenu		0				/* MyMenus[] array indexes */
#define	aboutMeItem		1

#define	fileMenu		1				/* MyMenus[] array indexes */
#define closeItem	 	1
#define	quitItem 		3

#define	editMenu		2				/* MyMenus[] array indexes */
#define	undoItem 		1
#define	cutItem			3
#define	copyItem 		4
#define	pasteItem		5
#define	clearItem		6

#define serverMenu		3				/* MyMenu[] array indexes */
#define windowItem		1
#define	haltstartItem	2


#define menuCount		4

/*
  	For the About bootserver... DLOG
*/
#define	aboutMeDLOG		128
#define	okButton		1
#define	authorItem		2			/* For SetIText */
#define	languageItem	3			/* For SetIText */

/*
	string resources
*/
#define	haltmenustring	100			/* menu text id */
#define startmenustring	101			/* ditto */
#define hideWindstring	102			/* ditto */
#define showWindstring	103

/*
	Alert Box ID's
*/

#define myNoteAlertID		-900	/* ID of our NoteAlert alert box */ 
#define myNoteAlertListID	-901	/* and its DITL ID */


/*
	errors for alert box
*/

#define	errSTRlist		100			/* STR# resource list of err messages			*/
#define	ASserverErr		1			/* file server not found;	[1] of errSTR#list	*/
#define	ImageErr		2			/* can't find/open image;	[2] of errSTR#list  */
#define memErr			3			/* memory error;			[3]					*/
#define	vblErr			4			/* vbl install error							*/
#define sktErr			5			/* open socket error							*/
#define resErr			6			/* resource not found							*/
#define UGErr			7			/* users & groups file error					*/

#define	windowID		128			/* the server window ID 						*/












/*
	HIWORD and LOWORD macros, for readability.
*/
#define HIWORD(aLong)		(((aLong) >> 16) & 0xFFFF)
#define LOWORD(aLong)		((aLong) & 0xFFFF)



