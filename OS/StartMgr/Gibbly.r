/*
	File:		Gibbly.r

	Contains:	System Enabler (Gibbly) for SuperMario based ROMs used for ROM Development phase

	Written by:	Ricardo Batista and Fred Monroe

	Copyright:	© 1992-93 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM5>	 11/3/93	SAM		Set the ROM gibbly time stamp back to the "ROMBuildTime"
	   <SM4>	 7/20/93	SAM		Removed all the outdated an usless boxflags from the ROM gibbly
									because the loader don't check for boxflags in ROM gibblies.
	   <SM3>	 6/28/93	kc		Changed the ROM Gibly date to be 2805970000 , which is Monday,
									November 30, 1992 12:06:40 PM. This is so that the Disk based
									Gibbly will have date later than Novemeber and when the disk
									Gibbly works we automatically use that Gibbly instead.
	   <SM2>	 6/14/93	kc		Roll in Ludwig.
	   <LW5>	12/17/92	fau		Added 2 'wedg' resources to the ROVM resource.
	   <LW2>	12/14/92	GS		Removed 'ppat' 18 for portables, from the 'romv' resource.
									Removed all 'cmtb', 'ppci', and 'ppcc' resources by request of
									gma.
	  <SM18>	02/10/93	HY		Remove LC930 specific code. Removed STR #-16395 resource.
	  <SM17>	 1/29/93	RB		Removed ppt# (0) and PAT# (0) from the override list, since the
									Control Panel 'General' wants to modify this resource when the
									user double clicks on the desktop icon.
	  <SM16>	01-07-93	jmp		Removed 'gama' ID=0 from the 'rovm' list, as it is ONLY need
									from ROM.
	  <SM15>	01/09/93	HY		Change LCR name (LCII boxflag).
	  <SM14>	12/18/92	HY		Added string list of machine names for LC930 only.
	  <SM13>	12/16/92	HI		Removed 'wctb' 0 and 'cctb' 0 from the ROM overrides list. This
	  								allows these resources to be modified in the System File and,
									hence, window and control colors to be modified through the
									Color CDEV. (Hoon Im)
	  <SM12>	12/14/92	rab		Removed ppat 16 from the ROM overrides list. This is the ppat
									for the Desktop pattern and shouldn't be in ROM.
	  <SM11>	12/14/92	RB		Added more box flags for the ROM gibbly and re-enabled the ROM
									build time.
	  <SM10>	 12/9/92	RB		Re-enable rom resources that we want to override the system file
									with.
	   <SM9>	 12/4/92	RB		Re-enabled some of the resources we wanted to override the
									system with. We are debugging the AddrMap.
	   <SM8>	 12/1/92	RB		Created a 'rovm' resource to override some system resources
									which we want used from ROM since the ROM versions are up to
									date.
	   <SM7>	 9/18/92	GMA		removing support for Cyclone and Cyclone EVT1
	   <SM6>	 7/28/92	RB		Changed the ROM Gibly date to be 2805970000 , which is Monday,
									November 30, 1992 12:06:40 PM. This is so that the Disk based
									Gibbly will have date later than Novemeber and when the disk
									Gibbly works we automatically use that Gibbly instead.
	   <SM5>	  7/1/92	GMA		moved boxcycloneevt1 from 37 to 36
	   <SM4>	  7/1/92	GMA		moved cyclone boxflag from 31 to 37
	   <SM3>	  7/1/92	RB		Disable the ROMBuildTIme variable temporarily. Use a time stamp
									of $AAAAAAAA. This Gibbly will be useless on the D9 build. Also
									added box flag for boxCycloneEVT1 (a temp boxflag)
	   <SM2>	 5/22/92	PN		Adding box flags up to Cyclone
		 <1>	 4/14/92	RB		first checked in

*/

#include "SysTypes.r"
#include "Types.r"
#include "SysPrivTypes.r"

resource 'gbly' (-16385, sysHeap) {
	GibblyVersion1,
	ROMBuildTime,					// 2805970000,					// Time stamp						<MC2>
	{
									// Gibbly loader doesnt check the list of machines for a ROM gibbly
									// so it doesn't do us any good to include a hardcoded list...		<SAM>
	};
};


// Ideally, all of these resources should override the system, but something is not working quite
// right here, we got a build tomorrow and so we are leaving this on state were it fixes the
// Claris bugs, but is not a finished solution until we get all of these things working right.

resource 'rovm' ( 0, locked) {
	{
	'pixs', -14335; 'pixs', -14334; 'pixs', -10199; 'pixs', -10200; 'pixs', -10201; 'pixs', -10202;
	'pixs', -10203; 'pixs', -10204; 'pixs', -10205; 'pixs', -10206; 'pixs', -10207; 'pixs', -10208;
	'CDEF', 0; 'CDEF', 1;
	'WDEF', 0; 'WDEF', 1; 'WDEF', 126;
//	'wctb', 0;
//	'cctb', 0;
	'CURS', 1; 'CURS', 2; 'CURS', 3; 'CURS', 4;
	'MBDF', 0;
	'MDEF', 0;
//	'ppat', 16; 'ppat', 18;
	'ics#', -16386;
	'ics4', -16386;
	'ics8', -16386;
	'rtt#', -5728;
//	'ppcc', -5856;
	'KCAP', 1; 'KCAP', 2; 'KCAP', 4; 'KCAP', 5; 
	'KCHR', 0;
	'KMAP', 0; 'KMAP', 2;
	'LDEF', 0; 'LDEF', 19; 'LDEF', -32510; 'LDEF', -32512;
	'PACK', 0; 'PACK', 12;
	'PACK', 3; 'PACK', 7; 'PACK', 8; 'PACK', 9; 'PACK', 11; 'PACK', 13; 'PACK', 14; 'PACK', 15;
	'clut', 1; 'clut', 2; 'clut', 4; 'clut', 5; 'clut', 8; 'clut', 9; 'clut', 127;
//	'ppci', -16409;
//	'cmtb', -32508; 'cmtb', -32509; 'cmtb', -32510; 'cmtb', -32511; 'cmtb', -32512;
	'mitq', 0;
	'proc', -32512; 'proc', -32511; 'proc', -32510; 'proc', -16498; 'proc', -16497; 'proc', -5728, 'proc', -5727;
	'pslt', 20; 'pslt', 26;
	'snd ', 1;
	'wedg', -5759; 'wedg', -5760;
	};
};

