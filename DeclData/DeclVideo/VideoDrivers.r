/*
	File:		VideoDrivers.r

	Contains:	The includes to build a giant “.rsrc” file.

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	10/27/93	fau		Added the ATI resources to the list.
	   <SM4>	 6/14/93	kc		Roll in Ludwig.
	   <LW3>	 5/19/93	fau		Added CivicPict2.rsrc to the list.
	   <LW2>	 4/30/93	fau		Added CivicPict.rsrc to the list.
	   <SM3>	01-12-93	jmp		Added initial support for CSC.
	   <SM2>	 11/2/92	kc		Change ObjDir to RsrcDir and add not 'SINL'.
		 <1>	10-17-92	jmp		first checked in
*/

#include "Types.r"
#include "ROMLink.r"

include $$Shell("RsrcDir")"ApolloDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CivicDeclVideo.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CivicDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CivicPict.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CivicPict2.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CivicPrimaryInit.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CSCDeclVideo.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CSCDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"CSCPrimaryInit.rsrc" not 'SINL';
include $$Shell("RsrcDir")"DAFBDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"DBLiteDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"RBVDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"SonoraDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"SonoraDeclVideo.rsrc" not 'SINL';
include $$Shell("RsrcDir")"SonoraPrimaryInit.rsrc" not 'SINL';
include $$Shell("RsrcDir")"TimDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"V8Driver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"ATIDeclVideo.rsrc" not 'SINL';
include $$Shell("RsrcDir")"ATIDriver.rsrc" not 'SINL';
include $$Shell("RsrcDir")"ATIDeclMonitors.rsrc" not 'SINL';
include $$Shell("RsrcDir")"ATIPrimaryInit.rsrc" not 'SINL';

/*
include $$Shell("RsrcDir")".rsrc";
*/