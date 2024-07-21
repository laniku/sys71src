/*
	File:		StandardEqu.h

	Contains:	all the files we typically need in BBS

	Written by:	Jim Reekes

	Copyright:	© 1991-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM2>	 8/17/93	JDR		Added LowMem.h
		 <1>	 6/24/92	JDR		first checked in

	This is used to generate a dump file for faster compiling.

	This file contains a list of the most commonly used interface files for C sources
	while building a system file.  I searched all of the .c files.  Below is a lising
	of the header files typically used by each of them.  This listing does not include
	any private files.  Only the public interfaces were considered.
*/

#include <Aliases.h>
#include <CommResources.h>
#include <Components.h>
#include <ConnectionTools.h>
#include <Controls.h>
#include <CTBUtilities.h>
#include <Devices.h>
#include <Dialogs.h>
#include <Errors.h>
#include <Events.h>
#include <Files.h>
#include <FixMath.h>
#include <Folders.h>
#include <Fonts.h>
#include <GestaltEqu.h>
#include <Icons.h>
#include <LowMem.h>
#include <Memory.h>
#include <Menus.h>
#include <OSUtils.h>
#include <Packages.h>
#include <Processes.h>
#include <Quickdraw.h>
#include <Resources.h>
#include <Retrace.h>
#include <Script.h>
#include <Sound.h>
#include <SoundInput.h>
#include <StdDef.h>
#include <SysEqu.h>
#include <Timer.h>
#include <ToolUtils.h>
#include <Traps.h>
#include <Types.h>
#include <Values.h>
#include <Windows.h>

#pragma dump "MPWHeaders"
