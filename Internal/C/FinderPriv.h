/*
	File:		FinderPriv.h	

	Contains:	File types of alias files and other Finder/system things.
	
				!!! This file must also be Rez-able !!!
				
	Copyright:	© 1990-1991 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <6>	 8/27/91	JSM		Cleanup header.
		 <5>	 6/18/91	JL		Changing FinderInterface.h to Finder.h
		 <4>	 1/19/91	PP		(ngk) Move container alias type definitions to
									FinderInterface.h.
		 <3>	10/18/90	ngk		Added kApplicationAliasType
		 <2>	 8/31/90	ngk		Rez is brain dead, so now use slash-star style comments
		 <1>	 8/30/90	ngk		first checked in
		 <0>	 8/30/90	ngk		created from Finder:AliasFile.h

*/

#ifndef __FINDERPRIV__
#define __FINDERPRIV__

// fmap table mapping alias file type to icon ID's
#define  rAliasTypeMapTable			(-16505)	

#include $$Shell("CIncludes")"Finder.h"

#endif __FINDERPRIV__
