/*
	File:		Cyclone_VDig.r

	Contains:	Cyclone VDig resources

	Written by:	Dan Hitchens x4-3117

	Copyright:	© 1992-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM6>	 6/14/93	kc		Roll in Ludwig.
	   <LW3>	12/23/92	fau		Modified the code and STR  resources to use the blessed id's
									from MSAD.
	   <LW2>	12/11/92	DH		Took out str resouces;  Redefined thng resource (instead of
									DeRezed format.);  Now assumes str resources are in the gibbley.
	   <SM5>	 8/28/92	DH		Changed M3TV to m3tv.
	   <SM4>	 8/24/92	DH		Change mfr. from aapl to appl and added subtype M3TV.
	   <SM3>	  7/6/92	fau		Changed 'thng' res id to 200 so it doesn't conflict with one of
									the sound components.
	   <SM2>	 6/29/92	DH		Changed 'CODE' resource to 'code'
		 <1>	  6/3/92	RLM		first checked in
		<P2>	 4/30/92	DH		Took out vers resource.

*/
#include "Types.r"
#include "MPWTypes.r"
#include "ImageCodec.r"


resource 'thng' (-16727) {
	'vdig',
	'm3tv',
	'appl',
	0x80000000,
	0x80000000,
	'code',
	-16729,
	'STR ',
	-16721,
	'STR ',
	-16722,
	0,
	0
};
