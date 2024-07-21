/*
	File:		DeclData.r

	Contains:	Shared resource declarations for DeclData components.

	Copyright:	© 1989-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM28>	 1/20/94	PN		Remove the remaining slot resource types "_CPUMac20" to fix DAFB
									video display.
	  <SM27>	  1/4/94	PN		Add the rest of support for more CSC panels from KAOS.
	  <SM26>	12/14/93	PN		Obsolete the CPUMac020 resources.
	  <SM25>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	10/27/93	fau		Added the ATIDir to the SuperDirectory.
	  <SM24>	 11/9/93	KW		added some srsrc's for stp machines
	  <SM23>	08-16-93	jmp		Eliminated an extraneous Wombat/WLCD board sRsrc entry.
	  <SM22>	 8/12/93	KW		adding two more smurf wombats
	  <SM21>	 8/11/93	KW		adding some srsrc for a few more smurf machines
	  <SM20>	08-06-93	jmp		Added to the list of timinginfo constants, which is not complete
									yet, but is good enough for the Sonora/PDM support.
	  <SM19>	08-03-93	jmp		Updated the copyright notice and changed the various display
									name strings to the new resolution/vertical refresh rate format
									(i.e.,  the original Apple display names no longer make sense --
									too many share the same sense codes).
		<18>	  6/1/93	IH		Add timing info for video modes
	  <SM17>	  4/5/93	chp		Synchronize with Ludwig.
	  <SM16>	04-01-93	jmp		Removed the reference to SuperMario (SM) in the VendorInfo.
	  <SM15>	  3/9/93	jmp		Updated the rev-level to reflect the fact that SuperMario is
									different from Ludwig.
	   <LW6>	  3/8/93	fau		Changed the SCSITransport DrHw field to be the board resource
									for Cyclone, for lack of a better number.
	   <LW5>	  3/1/93	DCB		Changed typSIM to typeXPT for the transport sRsrc.
	   <LW4>	 2/24/93	fau		Added a sRsrc for the SCSI Transport, as well as typ and cstr
									entries for it.
	   <LW3>	 2/16/93	fau		Changed the name of the HRNTSC names to 512x384/640x480/768x576.
	  <SM14>	01-12-93	jmp		Added initial support for CSC.
	  <SM13>	01-11-93	jmp		Compacted the DBLite/Dart video data to now match what’s in
									HORROR.
	  <SM12>	01-07-93	jmp		Added a VideoNames directory for V8-based built-in video.
	  <SM11>	12/23/92	RC		Added support for running Smurf on Wombat (boxRiscWombat)
	  <SM10>	12-10-92	jmp		Fixed the DAFB Two-Page and 21" Color Display 8bpp entries for
									Brooktree CLUT/DAC CPUs (i.e., production Quadra 700/900).  The
									TimingAdj value was off by one.
	   <SM9>	 11/2/92	kc		Change ObjDir to RsrcDir
	   <SM8>	10-29-92	jmp		Added support for 33 MHz WLCD.
	   <SM7>	10/26/92	HY		Added support for LC II boxflag. Defined sRsrc_BdLCII.
	   <SM6>	10/19/92	RB		Removed more video resources from the LC II (1 Meg) ROM build
									for the LC930
	   <SM5>	10-17-92	jmp		Needed to the change the 'decl' IDs of various externally
									referenced components.
	   <SM4>	10/14/92	RB		When building for a 1 Meg LC930 ROM, exclude unused components.
	   <SM3>	 10/8/92	fau		Added separate 2bpp/8bpp parameter structures for Civic-based
									CPU's.
		 <SM2>	 10/6/92	GDW		Fixed missing text.
		 <SM1>	 10/6/92	GDW		New location for ROMLink tool.

*/
//     <SM18>     8/20/92     AK     Removed last part of format block (starting with Rom Length Size.)
//                                   SMRomImage.r now supplies this. This is a test for ROMLink. 
//     <SM17>      8/9/92    CCH     Added video support for Quadras with RISC cards.
//     <SM16>     7/29/92    fau     Fixed bug in the Civic vidParams for the full-page displays,
//                                   where I forgot to take the base address out of the data
//                                   structure.  Update the Endeavor M,N and clock select on the
//                                   Goldfish and Full page displays to use lower M,N.  This got rid
//                                   of the jitter on EVT3 on those displays.  Also updated the 2pg
//                                   monitors to lower M,N values.
//     <SM15>     7/28/92    fau     Updated PAL Convolution parameters to be exactly 4x the
//                                   non-convolved and moved the base to 4096 (from 2048) -- even
//                                   though 'cause of a bug in Civic, PALConv won't work at 25MHz.
//                                   Because of that, changed the equivalent PAL spID's for switching
//                                   between RGB Syncs and PAL Composite syncs to the non-convolved
//                                   parameters.  Added equivalent spID's for NTSC/PAL composite
//                                   syncs to all vidparams that needed them.  Adjusted the serration
//                                   timing on PAL and some of the vertical timings on NTSC and PAL
//                                   per the hardware guy (L. Thompson), so that they meet the CCIR
//                                   spec.  Change the name of the equivalent modes  from
//                                   Under/Overscan to 512x384 et.al.
//     <SM14>    07-14-92    jmp     (SWC,H47) Changed the ctSeed for the 1-, 2-, and 4-bit fixed
//                                   CLUTs used for the grayscale LCDs to help fix a QuickDraw bug.
//                                   InitGDevice calls GetDevPixMap to fill in the device's PixMap,
//                                   including its CLUT. For fixed devices, it then generates a new
//                                   ctSeed, which causes problems in IconUtilities because the LCD's
//                                   CLUT doesn't match the current display mode/depth.
//                                   (djw,H46) Add sVidAttribute flag to indicate a "built-in"
//                                   display (fBuiltInDisplay) on all applicable video sRsrc's.
//                                   (jmp,H45) Added in support to make the DAFB-related DeclData
//                                   work correctly among Spike, Eclipse, Zydeco, and all Wombat/WLCD
//                                   CPUs.
//                                   (jmp,H44) Added support for PAL and NTSC on Wombat.
//                                   (jmp,H43) Adjusted a number of the DAFBVidParams to be more
//                                   compatible with Wombat.  (In doing this, I have temporarily
//                                   caused some aesthetically unpleasing artifacts to occur on
//                                   Spike/Eclipse/Zydeco, but I will fix these problems shortly.)
//                                   (jmp,H42) Added first-pass support for the Wombat version of
//                                   DAFB (i.e., add the NSC-8534 clock chip params to the supported
//                                   progressive scan displays; interlaced displays to follow soon).
//     <SM13>      7/7/92    fau     Moved sRsrc_BdWombat20 to the correct location in the resource
//                                   directory, since the boxflagWombat20 moved from 29 to 52.
//                                   Corrected some problems in the DAFB video parameters entries
//                                   that happenned at the <H41> roll-in.
//     <SM12>     6/26/92    fau     Changed HSERR parameter on Civic Interlaced displays (to 1/2 of
//                                   original value).  Change clock timing for PAL displays in Civic
//                                   to a 14.78MHz dot clock per Eric Baden and Larry Thompson
//                                   request  (that is the correct timing, not 14.75).  Added
//                                   composite out support for 12" and 13" displays.
//     <SM11>     6/22/92    mal     changed label decldataethernet to decldatasonic
//     <SM10>     6/20/92    ejb     Removed all trace of BOMII DSP3210 Driver from DeclData.  Its
//                                   now going to be just a regular ROM resource like the RTMgr.
//      <SM9>     6/19/92    KW      (fau,P28) Added support for GoldFish displays switching to
//                                   composite out. Kludgy, but will go away when we implement a
//                                   dynamic desktop. RSN...
//      <SM8>     6/18/92    KW      (jmp,H41) Eliminated yet even more of the old DAFBVidParams
//                                   fields.
//                                   (jmp,H39) Tweaked the 15.6672 MHz Omega-2’s P value from
//                                   previous check-in.
//                                   (jmp,H38) Updated the SonoraVidParams for the Omega-2.
//                                   (fau,P26) Added video-in configurations for Vesuvio, Kong,
//                                   Rubik, 19" Display and all VGA families for Civic-based CPU's.
//      <SM7>     6/18/92    RB      Changed the entry of the DSP driver (ATT3210) so it won't get
//                                   opened automatically at PrimaryInit time. The current DSP driver
//                                   breaks on Cyclone EVT2.
//      <SM6>      6/4/92    KW      (jmp,H37) Fixed a few minor typos that prevented some displays
//                                   form working correctly on REAL Quadra 900/700s (i.e., ones that
//                                   have Brooktree DACs). (jmp,H36) Compacted the DAFB vidParam
//                                   tables. (djw,H35) Added secondaryInit to board sRsrc for DBLite
//                                   and Dartanian. (BG,H34) Changed various Wombat-style BoxFlag
//                                   references to their new, more descriptive names. (jmp,H33)
//                                   Eliminated support for the no-vRAM case in V8-based systems.
//                                   (jmp,H32) Changed the “sRsrcZydecoDir” name to the more generic
//                                   “sRsrcBFBasedDir” (BF=BoxFlag) name. (jmp,H31) Changed the
//                                   hard-coded values in my last check-in into equates. (jmp,H30)
//                                   Added real MinorBaseOffsets for the V8-based sResources.
//                                   (jmp,H29) Just added the SecondaryInit entry to Wombat board
//                                   sRsrc. (jmp,H28) Took a lot of “air” out of this file by
//                                   combining lots of tables that are exactly the same except for
//                                   their names. Also, conditionally dropped support for Apollo,
//                                   since this ROM can’t do it anyway. Conditionally removed the
//                                   checksumming. (jmp,H26) Did a couple of things for the
//                                   Sonora-based CPUs: 1) Added a 640x400 mode for the HiRes
//                                   display, and 2) fixed a problem in the GoldFish 256K of vRAM
//                                   configuration where only 2bpp is possible but I supporting upto
//                                   4bpp.
//      <SM5>     5/21/92    RB      Making changes for Cyclone. Moved some changes from Pandora. It
//                                   seems like Mike should look at this file because Pandora is out
//                                   of Zync with Horror in Sonora (today). Changed 'The SuperMario
//                                   ROM' to 'The SM ROM' NEVER have someone else's copyright in ROM
//                                   !!!
//      <SM4>     5/16/92    kc      Roll in Horror and Zydeco Changes. Comments follow:
//      <H27>     4/21/92    SWC     Added INCLUDE of PowerPrivEqu.a for PrimaryInit.a.
//      <H26>    04/20/92    jmp     Did a couple of things for the Sonora-based CPUs:  1)  Added a
//                                   640x400 mode for the HiRes display, and 2) fixed a problem in
//                                   the GoldFish 256K of vRAM configuration where only 2bpp is
//                                   possible but I supporting upto 4bpp.
//      <H25>     3/17/92    SWC     Renamed boxDBLite->boxDBLite25 and boxDBLiteLC->boxDBLite33, and
//                                   added boxDBLite16 and boxDBLite20 to the lists.
//      <H24>      3/6/92    SWC     Added DockingEqu.a to the INCLUDEs list.
//      <H23>    02/19/92    jmp     Changed all the Condor references to Wombat.
//      <H22>    01/30/92    jmp     Fixed a couple of typo’s I introduced in <H19>.
//      <H21>    01/29/92    jmp     (jmp,Z27) Added two new INCLUDES for GestaltEqu.a and
//                                   GestaltPrivateEqu.a for the SecondaryInit System fixes.
//      <H20>    01/27/92    jmp     (BG,Z26)  Added an INCLUDE for IOPrimitiveEqu.a for
//                                   SecondaryInit.a.  Also, cleaned up the vidAttributes fields on
//                                   the LCD-based sRsrcs.
//      <H19>    01/22/92    jmp     (jmp,Z25) Added SecondaryInit entries for Spike & Eclipse as
//                                   well as for Zydeco.
//                                   (jmp,Z24) Added an include for ShutDownEqu.a.
//      <H18>    01/14/92    jmp     Fixed a problem I introduced during my last check-in (I inserted
//                                   the RdTPD DAFB vidParams in front of the 19x vidParams, and it
//                                   should have been the other way around).
//      <H17>    01/11/92    jmp     Added rudimentary support for the newly-defined extended sense
//                                   codes.
//      <H16>    01/07/92    jmp     Updated the Brooktree-DAC Timing Adjust value in the Kong and
//                                   Vesuvio DAFB vidParams due to change <H14> below.
//      <H15>    12/19/91    jmp     Added the initial support for Rubik-560 mode for Sonora.
//      <H14>    12/17/91    jmp     Updated the Kong/Vesuvio, GoldFish, SuperVGA, and PAL
//                                   non-convolved tables so that all depths within each
//                                   configuration share a common base address.  Also, tweaked the
//                                   19" Display parameters to generate a 60.2 KHz clock rather than
//                                   a 59.9 KHz clock.
//      <H13>    12/16/91    HJR     Added support for Dartanian.
//      <H12>    12/12/91    jmp     Added in the rest of the Sonora initial support.
//      <H11>    11/27/91    jmp     Started adding support for Sonora.
//      <H10>    11/26/91    jmp     Added support for a 640x480 LCD screen as well as 640x400 LCD
//                                   screen.
//       <H9>    11/25/91    jmp     Moved the DAFB vidParams from the functional sRrsrcs to the
//                                   board sRsrcs -- this significantly reduced the size of this
//                                   file!
//       <H8>    11/12/91    jmp     Added the “Mac Std Gamma” table to the VGA and SVGA sRsrcs as
//                                   requested by MacDTS.
//       <H7>    11/05/91    jmp     Added preliminary support for 19" Displays for DAFB-based CPUs.
//       <H6>    11/01/91    jmp     We now have two DBLite functional sRsrcs.  One is for the
//                                   developmental black/white-only LCD displays (controller), while
//                                   the other is for the grayscale LCD controller.  Currently, only
//                                   the black/white sRsrc is used.
//       <H5>    10/31/91    jmp     Marketing (Ross Ely) finally admitted that defaulting to the
//                                   6500°K gamma table for Vesuvio & GoldFish was a bad idea, so I
//                                   am now defaulting to the 9300°K gamma table on those displays.
//                                   Yeah!
//        <4>    10/29/91    jmp     Added the initial support for super sRsrc directories.
//        <3>    10/24/91    jmp     Added the gray-scale (thru 4bpp) mVidParams for DB-Lite and
//                                   updated the Horror ROM VendorInfo sRsrc.
//        <2>    10/24/91    jmp     Updating to Zydeco-TERROR version.
// ———————————————————————————————————————————————————————————————————————————————————————
//     Pre-Horror ROM comments begin here.
// ———————————————————————————————————————————————————————————————————————————————————————
//        <3>     3/31/92    JSM     Rolled this file into Reality.
//        <2>     2/11/92    RB      Need to include ROMPrivateEqu.a and align a few labels to avoid
//                                   warnings.
//       <26>     1/22/92    BG      Added an INCLUDE for IOPrimitiveEqu.a for SecondaryInit.a.
//       <25>    01/21/92    jmp     Added SecondaryInit entries for Spike & Eclipse as well as for
//                                   Zydeco.
//       <24>    01/20/92    jmp     Added an include for ShutDownEqu.a.
//       <23>    01/09/92    jmp     Added rudimentary support for the newly-defined extended sense
//                                   codes.
//       <22>    01/07/92    jmp     Updated the Brooktree-DAC Timing Adjust value in the Kong and
//                                   Vesuvio DAFB vidParams due to change <21> below.
//       <21>    12/17/91    jmp     Updated the Kong/Vesuvio, GoldFish, SuperVGA, and PAL
//                                   non-convolved tables so that all depths within each
//                                   configuration share a common base address.  Also, tweaked the
//                                   19” Display parameters to generate a 60.2 KHz clock rather than
//                                   a 59.9 KHz clock.
//       <20>    11/11/91    jmp     Added the “Mac Std Gamma” table to the VGA and SVGA sRsrcs as
//                                   requested by MacDTS.
//       <19>    11/05/91    jmp     Added preliminary support for 19” Displays for DAFB-based CPUs.
//       <18>    10/31/91    jmp     Marketing (Ross Ely) finally admitted that defaulting to the
//                                   6500°K gamma table for Vesuvio & GoldFish was a bad idea, so I
//                                   am now defaulting to the 9300°K gamma table on those displays.
//                                   Yeah!
//       <17>    10/03/91    jmp     Added a SecondaryInit off the Zydeco board sRsrc.  We’re doing
//                                   this to fix any Zydeco-specific System Disk Regatta-related
//                                   problems.
//       <16>    09/13/91    jmp     Added support for 16pp on Rubik displays when only 512K of vRAM
//                                   is around in preparation for Spike33s.
//       <15>     8/26/91    jmp     Added the Zydeco ROM part numbers.
//       <14>     8/26/91    jmp     Added support for a Spike33-type box.
//       <13>     8/21/91    jmp     Changed all the Eclipse33 references to Zydeco.
//       <12>     8/20/91    jmp     Just updated the supported CPU code name list.
//       <11>      8/9/91    jmp     Added support to fix a problem with NTSC & PAL family modes
//                                   where changing the amount of vRAM didn’t cause DAFB’s part of
//                                   PrimaryInit to re-validate the SP_LastConfig pRAM byte.
//       <10>      8/7/91    jmp     Added 16bpp support for all applicable DAFB displays.
//        <9>     7/29/91    jmp     Added the Eclipse33 (Zydeco) & TIM-LC board sRsrcs.
// ———————————————————————————————————————————————————————————————————————————————————————
//     Pre-Zydeco ROM comments begin here.
// ———————————————————————————————————————————————————————————————————————————————————————
//        <8>     6/29/91    jmp     Added the alternate AC842A-compatible timing adjust, horizontal
//                                   active line, and horizontal front porch DAFB paramters.
//        <7>     6/28/91    jmp     Fixed the HFP value in the DAFB VGA parameters, and fixed the
//                                   TA, HAL, and HFP values in the DAFB SuperVGA parameters.
//        <6>     6/24/91    jmp     Added support for 16bpp Vesuvio & RGB Portrait displays.
//        <5>     6/17/91    jmp     Reset the base address of NTSC, PAL, SuperVGA, Kong, and
//                                   Vesuvio.  Also, changed the rowbytes of PAL and SuperVGA to be
//                                   the same as GoldFish.
//        <4>     6/10/91    jmp     Had to change the clock parameters for HR & GoldFish on Spike &
//                                   Eclipse PVT units to eliminate possible jitter.
//        <3>      6/4/91    jmp     Made the RGB Portrait name more generic, sinc Apple doesn’t
//                                   manufacture one, and pointed the RGB Portrait gamma directory to
//                                   the HR gamma directory instead of the one used by Vesuvio &
//                                   GoldFish.
//        <2>     5/22/91    jmp     Corrected the flags in the DB-Lite functional sRsrc to reflect
//                                   the fact that DB-Lite’s frame buffer is 32-bit addressed.
//                                   Updated the Apollo, Tim, and DB-Lite functional sRsrcs to
//                                   contain the fOpenAtStart flag.  Added the ROM (surface mount)
//                                   part numbers for Spike & Eclipse.  Eliminated the hardware IDs
//                                   on the gamma tables so that the strategy for built-in video is
//                                   again universal (this works because all the current built-in
//                                   videos that have DACs have similar response curves).  Removed
//                                   the blanking pedestal on all PAL modes because the PAL standard
//                                   specifies that the black & blanking levels are the same.
//        <1>     5/22/91    jmp     Changed name to DeclData.a from DeclDataRBV.a to reflect
//                                   the fact that this file is used by all built-in videos, not
//                                   just RBV.
//       <29>     5/15/91    jmp     Added DB-Lite support.  Also, removed the multi-bit icons and
//                                   added a new icon for TIM (also used by DB-Lite for now).
//       <28>     5/10/91    jmp     Added the 4•8/8•24’s Vesuvio & GoldFish (calibrated) gamma
//                                   tables.  Added all the appropriate data to support SuperVGA.
//       <27>     4/26/91    jmp     Updated the PAL convolved baseAddr.
//       <26>     4/25/91    jmp     Added a preliminary (i.e., un-calibrated) alternate gamma table
//                                   for Vesuvio & GoldFish.  This gamma table is for the the
//                                   “natural” 9300°K heat point of those displays.
//       <25>     4/23/91    jmp     Eliminated duplicate NTSC parameters.
//       <24>     4/19/91    jmp     Cleaned up the NTSC & PAL parameters; several modes were
//                                   “fuzzy.”  Put a 1bpp icon in the board sResource for Eclipse,
//                                   Spike, TIM, and Apollo.  Put in an icon suite for Eclipse &
//                                   Spike, but am not currently pointing at it.  Eliminated gamma
//                                   tables for NTSC, PAL, and VGA because we don’t know what kind of
//                                   displays users’ will be hooking up.  Pointed Vesuvio & GoldFish
//                                   at the same (yet uncalibrated) gamma table being used by version
//                                   1.2d1 of the 8•24 card.  Finally, moved PrimaryInit to the end
//                                   of the file so that code-common data (i.e., data shared among
//                                   the Drivers & PrimaryInit) can be declared in the DeclData file
//                                   itself.
//       <23>     4/16/91    jmp     Updated fixed tables for TIM & Apollo.
//       <22>     4/15/91    djw     Add spId for functional video sRsrc's video attibutes (a data
//                                   field) for Tim.
//       <20>      4/4/91    jmp     Updated various string names to be consistent across all uses
//                                   (e.g., made all references to “HiRes” look like “Hi-Res”).
//       <19>      4/1/91    jmp     Forgot to mention two other things in previous check-in: 1)
//                                   Removed support for DAFB 1, and 2) Added R-G-B 6500 & 9300 gamma
//                                   tables for Vesuvio and GoldFish.
//       <18>      4/1/91    jmp     Changed the Monitors cdev name of VGA from “VGA Display” to “VGA
//                                   640x480” for consistency with NTSC & PAL.  That is, we only use
//                                   the term “Display” for monitors we know about; the NTSC, PAL and
//                                   VGA modes specify industry standards rather than particular
//                                   display types.  Also, added an R-G-B 2.2 (D65) gamma table for
//                                   interlaced displays; 2.2 is the common value used for NTSC gamma
//                                   correction, and D65 (6500° K) is the heat temperature of the
//                                   phosphors commonly used in TV (broadcast & reception).
//       <17>     3/18/91    jmp     Added in DAFB 2 support.  The DAFB 2 data is still
//                                   conditionalized for now, so we can take it out very easily if we
//                                   need to.  Also, removed some old data from earlier attempts to
//                                   fix the 1bpp Rubik screen clearing stuff.
//       <16>      3/8/91    jmp     Needed to set rowbytes to 512 for FP @ 1, 2, and 4bb so that FPa
//                                   would actually finti into 512K of vRam.  Needed to set rowbytes
//                                   for PAL @ 1, 2, 4, and 8bpp so that PALa would actuall fit into
//                                   512K of vRam.  Had to add new mVidParams for PAL convolved modes
//                                   due to the change in rowbytes for the non-convolved modes.
//                                   Added a vidName directory for TIM and Apollo.
//       <15>      3/4/91    jmp     Fixed problems (bad entries) in Rubik’s inverse gamma table.
//                                   Fixed problems (bad entries) in HR’s inverse gamma table.
//                                   Reduced video refresh counts by -1 across the board.  Needed to
//                                   make real entries for RGB2P and RGBFP (for gamma correction).
//                                   Used same gamma table for VGA as Rubik (due to similarity in
//                                   clock rates).  Added new gamma table for NTSC & PAL (uncorrect,
//                                   actually, need to add real one later).
//       <14>     2/25/91    jmp     Moved driver directory to its proper place (i.e., according to
//                                   its sRsrc-ID number).  Moved all drivers to the very end of the
//                                   file.  Added support for CPU and Video icons.  The gamma tables
//                                   for RubikRBV & RubikACDC were identical, so I eliminated one of
//                                   them.  Updated the GS video params to reflect the fact that
//                                   Rubik 1bpp has a 1pixel wide “border” at the top (bottom doesn’t
//                                   matter since it will be drawn offscreen).  Added inverse gamma
//                                   tables.  The 32bpp screen clearing params for GoldFish were
//                                   incorrect.  The 8bpp screen clearing params for the two-page
//                                   display were incorrect.
//       <13>     2/15/91    jmp     Updated NTSC & PAL data to fix “darkening” problem in the
//                                   full-frame convolved modes. Added support for doing only 4/8bpp
//                                   in NTSC & PAL convolved modes. This has been conditionalized
//                                   with CurDAFBDrvrVersion. Needed to INCLUDE
//                                   'HardwarePrivateEqu.a' for checking for 33 vs. 25 Mhz CPU
//                                   operation.
//       <12>     2/12/91    jmp     Updated NTSC & PAL data for 4/8bpp convolved (for both FF & ST
//                                   modes).  Added defmBaseOffset to screen clear params.  Added in
//                                   “Misc” params to video params for ChkMode (in DAFBDriver.a).
//                                   Fixed the gType id for the Rubik Gamma Table.  And updated the
//                                   GoldFish’s clock parameters to match the Portrait’s as per Larry
//                                   Forsblad’s latest spec.
//       <11>      2/3/91    jmp     Added PAL video and Slot Manager data; commented out 32bpp
//                                   params. Added in NTSC and PAL ST defmBaseOffsets. Added family
//                                   names NTSC and PAL video families, as well as video names for
//                                   each kind of supported display. Added ’040 CPU family sRsrc. And
//                                   fixed the ordering of the DoubleExposure sRsrc.
//       <10>     1/31/91    JK      Added INCLUDE of SonicEqu.a for Sonic initialization.
//        <9>     1/30/91    jmp     Several fixes:  Fixed rowbytes (in mVidParams) in 32bpp mode for
//                                   GoldFish.  Added NTSCFF & NTSCST video and Slot Manager data.
//                                   For now, though, only NTSCST is up, and it is in the upper
//                                   lefthand corner of the display.  Eventually, it will be
//                                   centered.  Also, fixed a problem in the VGA video data (HFP was
//                                   10 pixels off in all modes).  Finally, doubled rowbytes for
//                                   1-8bpp for Rubik displays to fix 1bpp problem:  The baseAddr is
//                                   set 512 bytes back from where QuickDraw thinks it so that none
//                                   of the 1bpp jitter can be seen.
//        <8>     1/24/91    jmp     Added support for extended-sense-line displays, but this a long
//                                   way from finished.
//        <7>     1/22/91    jmp     The RGB versions of the Two-Page and Portrait DAFB vidParam
//                                   OSLstEntries were out of order.
//        <6>     1/21/91    jmp     Incremental change -- added support for monitors that have both
//                                   RGB and Mono-Only types (for now that means the Portrait and
//                                   Kong).
//        <5>     1/15/91    jmp     Corrected several parameters in the DAFB sVidParams data.  Still
//                                   having problems with 1 bpp mode on Rubik displays.
//        <4>     1/15/91    DAF     Added DAFB structures (tons of them - way too many to tag).
//                                   Many, many, many new structures, and data.
//        <3>      1/9/91    JK      Added Sonic Ethernet, Eclipse, and Spike support.
//        <2>    12/11/90    HJR     Integration of Rex and Tim video into Terror Project.
//

//
//   The Sixth Generation of the Slot 0 Config ROM image.
//
//       0.0 = Simple config ROM ID for Mac II motherboard ROM, no functional sRsrcs.
//       1.0 = Built-in video for RBV (Mac IIci) hardware.
//       2.0 = Support for multiple built-in video devices RBV & VISA (Mac LC).
//       3.0 = Support for even more video (DAFB2, TIM, Apollo, DB-Lite) and SONIC Ethernet.
//       3.1 = Support for Zydeco (Eclipse33) video (DAFB3).
//       4.0 = The Horror DeclData.
//       5.0 = The Ludwig (Cyclone/Tempest/LC930) DeclData.
//		 5.1 = The SuperMario DeclData.
//
//   This file (which includes a number of other files) is the source of
//   the slot 0 configuration ROM which describes a subset of the motherboard
//   features.  Specifically, this version of the config ROM contains the
//   functional slot Resources (sRsrcs) for devices which were previously
//   defined as NuBus additions, and have migrated to the motherboard.  This
//   class of devices include video and Ethernet communications, both of 
//   which had fully defined Slot Manager interfaces.  In this way, these
//   motherboard devices can be accessed in an implementation-independent
//   manner by software that already knows how to use the Slot Manager.  
//   Other motherboard devices (serial ports, SCSI, etc.) could be 
//   represented as part of slot 0 as well, but these functions are 
//   identified to the system in other ways.
//
//-------------------------------------------------------------------
//   Supported CPU code name list (to make sense of stray comments): 
//-------------------------------------------------------------------
//       Mac II, IIx, IIcx, SE/30 
//       Cobra II -> Aurora -> Aurora25/16 -> Pacific/Atlantic -> IIci
//		 F19 -> Zone5 -> IIfx
//       Erickson -> Rafiki -> Hobie Cat -> IIsi
//       Elsie -> Rex -> LC
//
//       TIM -> PowerBook 170
//       Eclipse -> Quadra 900
//       Spike -> Quadra 700
//       Apollo -> Classic II
//       TIM-LC -> PowerBook 140
//       Eclipse33 -> Zydeco -> Quadra 950
//       DB-Lite -> PowerBook Duo 210/230
//       Spike33 -> Condor -> Wombat/WLCD -> Centris/Quadra 800
//
//       Vail -> Lego -> LC III
//       Carnation/Carnation3 -> Died
//       TimII -> Dartanian/Monet -> PowerBook 160/180
//
//       Cyclone ->
//		 Tempest ->
//
//-------------------------------------------------------------------
//   Hardware code names that pop up in the config ROM code:
//-------------------------------------------------------------------
//       RBV   -  non-programmable video hardware in the IIci and IIsi
//                supports the Hi-Res, Portrait, Rubik, and an SE-sized grayscale display
//       VISA  -  a simple non-programmable video controller in the early Elsie.  Never produced.
//       V8    -  the replacement for the VISA in the production Elsie with much greater functionality.
//                supports the Hi-Res, Rubik, and VGA displays.
//       JAWS  -  the single mode flat-panel display controller in the 030-family portables.
//       DAFB  -  highly-programmable video controller in the Eclipse25/33 and Spike machines,
//                supports all Apple displays including interlaced video.
//       Ariel  - the (Brooktree-like) CLUT/DAC in the Elsie/Sonora machines.
//       ACDC   - the CLUT/DAC in the DAFB machines (also in the 8•24/8*24 GC cards).
//       Eagle  - the one-bit only controller that is in Apollo machines.  It is virtually
//                identical to V8.
//       MSC    - the LCD display control for DB-Lite machines.
//       GSC    - the LCD grayscale controller for DB-Lites and Dartanians.
//       Sonora - kitchen-sink ASIC that is RBV-like in it’s programability (or lack there of), but video
//                is just one of it’s subfunctions.
//       Civic  - highly-programmable video controller in the Cyclone CPU(s), similar functionality
//                to that of DAFB, except that it also supports video-in.
//       Sebastian
//              - the CLUT/DAC used by Civic, includes an alpha channel to support video-in.
//-------------------------------------------------------------------
//   Displays supported by this code (ST=safe title interlaced modes, FF=full frame):
//-------------------------------------------------------------------
//       Hi-Res (HR)           -  640*480, 67Hz refresh, 30.2400MHz dot clock, RGB and Monochrome
//       Hi-Res 400            -  640*400, 67Hz refresh, 30.2400MHz dot clock, RGB and Monochrome
//       Hi-Res MAZ            -  704*512, 67Hz refresh, 33.0400MHz dot clock, RGB and Monochrome
//       Rubik (GS)            -  512*384, 60Hz refresh, 15.6672MHz dot clock, RGB
//       Rubik-560             -  560*384, 60Hz refresh, 17.2340MHz dot clock, RGB
//       Portrait (FP & RGBFP) -  640*870, 75Hz refresh, 57.2832MHz dot clock, RGB and Monochrome
//       Two-Page (2P & RGB2P) - 1152*870, 75Hz refresh,100.0000MHz dot clock, RGB and Monochrome
//       Goldfish (LP,GF)      -  832*624, 75Hz refresh, 57.2832MHz dot clock, RGB
//       VGA                   -  640*480, 59Hz refresh, 25.1750MHz dot clock, RGB
//       SuperVGA (SVGA)       -  800*600, 56Hz refresh, 36.0000MHz dot clock, RGB (VESA)
//                             -  800*600, 72Hz refresh, 50.0000MHz dot clock, RGB (VESA)
//       SuperVGA (SxVGA)      - 1024x768, 60Hz refresh, 65.0000MHz dot clock, RGB (VESA)
//                             - 1024x768, 70Hz refresh, 75.0000MHz dot clock, RGB (VESA)
//       19"                   - 1024*768, 75Hz refresh, 60.2400MHz dot clock  RGB
//       SE-like               -  512*342, 60Hz refresh, ??.????MHz dot clock, Monochrome
//       NTSC_ST               -  512*384, 60Hz interlaced refresh, 12.2727MHz dot clock, RGB
//       NTSC_FF               -  640*480, 60Hz interlaced refresh, 12.2727MHz dot clock, RGB
//       PAL_ST                -  614*460, 50Hz interlaced refresh, 14.7500MHz dot clock, RGB
//       PAL_FF                -  768*576, 50Hz interlaced refresh, 14.7500MHz dot clock, RGB
//		 GSC_LCD			   -  640*400, 60Hz psuedo-refresh, active matrix or supertwish, Monochrome to 4bpp.
//		 640x400 LCD		   -  640x400, 60Hz psuedo-refresh, active matrix or supertwish, RGB.
//		 640x480 LCD		   -  640x480, 60Hz psuedo-refresh, active matrix or supertwish, RGB.
//

#include "Types.r"
#include "ROMLink.r"

#include "DepVideoEqu.r"
#include "HardwarePrivateEqu.r"
#include "InternalOnlyEqu.r"
#include "Quickdraw.r"

//-------------------------------------------------------------
//
//           Super sRsrc Directory
//
//           This is the sRsrc directory directory, or super sRsrc
//               directory.  It contains entries to all supported
//               sRsrc directories.
//
//-------------------------------------------------------------

resource 'spdr' (130, "_sRsrcSuperDir") {{
  sRsrcUnknownDir,  l{"_sRsrcUnknownDir"};		// Minimal sRsrc dir.
  
#if !LC930
  sRsrcATIDir,  	a{"_sRsrcATIDir"};			// The ATI-based CPUs directory.
  sRsrcCSCDir,		a{"_sRsrcCSCDir"};			// The CSC-based CPUs directory.
  sRsrcCivicDir,    a{"_sRsrcCivicDir"};		// The Civic-based CPUs directory.
  sRsrcSonoraDir,   a{"_sRsrcSonoraDir"};		// The Sonora-based CPUs directory.
#endif

  sRsrcBFBasedDir,  l{"_sRsrcBFBasedDir"};		// The BoxFlag-based CPUs directory. <P25>
}};

                
//-------------------------------------------------------------
//           Unknown sRsrc Directory
//
//           This is a minimal sRsrc Directory.  This sRsrc
//               directory will only be chosen when the
//               SuperInit is run on an unknown CPU.
//-------------------------------------------------------------

resource 'sdir' (135, "_sRsrcUnknownDir") {{
  sRsrcUnknownBD,   l{"_sRsrcUnknownBd"};		// Minimal board sRsrc directory.
}};


resource 'boar' (140, "_sRsrcUnknownBd") {{
  sRsrcType,        l{"_BoardType"};			// Minimal board sRsrc.
  sRsrcName,        c{"Unknown Macintosh"}; 
  BoardId,          d{0}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

//-------------------------------------------------------------
//
//           BoxFlag-based sRsrc Directory
//
//           This sRsrc Directory supports all Slot-Manager-
//               capable CPUs whose board sRsrcs and functional
//               sRsrcs are/were based on BoxFlag.
//
//-------------------------------------------------------------

resource 'sdir' (160, "_sRsrcBFBasedDir") {{

  sRsrc_BdMacII,    l{"_sRsrc_BdMacII"};					// Board sResources
  sRsrc_BdMacIIx,   l{"_sRsrc_BdMacIIx"}; 
  sRsrc_BdMacIIcx,  l{"_sRsrc_BdMacIIcx"}; 
  sRsrc_BdMacSE30,  l{"_sRsrc_BdMacSE30"}; 
  sRsrc_BdMacIIci,  l{"_sRsrc_BdMacIIci"}; 
  sRsrc_BdMacIIfx,  l{"_sRsrc_BdMacIIfx"}; 
  sRsrc_BdErickson, l{"_sRsrc_BdErickson"}; 
  sRsrc_BdElsie,    l{"_sRsrc_BdElsie"}; 

#if !LC930
  sRsrc_BdEclipse,  l{"_sRsrc_BdEclipse"}; 
  sRsrc_BdTIM,      l{"_sRsrc_BdTIM"}; 
  sRsrc_BdSpike,    l{"_sRsrc_BdSpike"}; 
  sRsrc_BdApollo,   l{"_sRsrc_BdApollo"}; 
  sRsrc_BdTIMLC,    l{"_sRsrc_BdTIM"}; 
  sRsrc_BdZydeco,   l{"_sRsrc_BdZydeco"}; 
  sRsrc_BdDBLite25, l{"_sRsrc_BdDBLite"}; 
  sRsrc_BdWombat25, l{"_sRsrc_BdWombat"};					// <H34>
  sRsrc_BdDBLite33, l{"_sRsrc_BdDBLite"}; 
  sRsrc_BdDartanian, l{"_sRsrc_BdDartanian"}; 
  sRsrc_BdDartanianLC, l{"_sRsrc_BdDartanian"}; 
  sRsrc_BdWombat33F, l{"_sRsrc_BdWombat"};					// <H34><H40>
  sRsrc_BdWombat33, l{"_sRsrc_BdWombat"}; 
#endif

  sRsrc_BdLCII,		l{"_sRsrc_BdElsie"};					// <SM7>
  
#if !LC930
  sRsrc_BdDBLite16, l{"_sRsrc_BdDBLite"}; 
  sRsrc_BdDBLite20, l{"_sRsrc_BdDBLite"}; 
  sRsrc_BdWombat40, l{"_sRsrc_BdWombat"};					// <H34>
  sRsrc_BdWLCD20,   l{"_sRsrc_BdWombat"};					// <H34>
  sRsrc_BdWLCD25,   l{"_sRsrc_BdWombat"};					// <H34>
  sRsrc_BdWombat20, l{"_sRsrc_BdWombat"}; 
  sRsrc_BdWombat40F,l{"_sRsrc_BdWombat"}; 

  sRsrc_BdRiscQuadra700,    l{"_sRsrc_BdSpike"}; 			// <SM21>
  sRsrc_BdWLCD33,			l{"_sRsrc_BdWombat"}; 

  sRsrc_BdRiscCentris650, 	l{"_sRsrc_BdWombat"}; 			// <SM21>

 sRsrc_BdRiscQuadra900,  	l{"_sRsrc_BdEclipse"}; 			// <SM21>
 sRsrc_BdRiscQuadra950,   	l{"_sRsrc_BdZydeco"}; 			// <SM21>
 sRsrc_BdRiscCentris610, 	l{"_sRsrc_BdWombat"}; 			// <SM21>
 sRsrc_BdRiscQuadra800, 	l{"_sRsrc_BdWombat"}; 			// <SM21>
 sRsrc_BdRiscQuadra610, 	l{"_sRsrc_BdWombat"}; 			// <SM22>
 sRsrc_BdRiscQuadra650, 	l{"_sRsrc_BdWombat"}; 			// <SM22>


 sRsrc_BdSTPQ700,			l{"_sRsrc_BdSpike"}; 			// <SM24>
 sRsrc_BdSTPQ900, 			l{"_sRsrc_BdEclipse"}; 			// <SM24>
 sRsrc_BdSTPQ950,  			l{"_sRsrc_BdZydeco"}; 			// <SM24>
 sRsrc_BdSTPC610,   		l{"_sRsrc_BdWombat"}; 			// <SM24>
 sRsrc_BdSTPC650, 			l{"_sRsrc_BdWombat"}; 			// <SM24>
 sRsrc_BdSTPQ610, 			l{"_sRsrc_BdWombat"}; 			// <SM24>
 sRsrc_BdSTPQ650, 			l{"_sRsrc_BdWombat"}; 			// <SM24>
 sRsrc_BdSTPQ800, 			l{"_sRsrc_BdWombat"}; 			// <SM24>

#endif

//
// These are the directory entries for RBV-based machines.  
//

#if !LC930
  
  sRsrc_VidRbvFPa,  l{"_sRsrc_VidRbvFPa"};					// Portrait (1,2,4) 
  sRsrc_VidRbvGSa,  l{"_sRsrc_VidRbvGSa"};					// Rubik (1,2,4,8) 
  sRsrc_VidRbvHRa,  l{"_sRsrc_VidRbvHRa"};					// High-Res (1,2,4,8)
  sRsrc_VidRbvSEa,  l{"_sRsrc_VidRbvSEa"};					// SE (1,2,4,8)
                
  sRsrc_VidRbvFPc,  l{"_sRsrc_VidRbvFPc"};					// Portrait (1 only) 
  sRsrc_VidRbvGSd,  l{"_sRsrc_VidRbvGSd"};					// Rubik (1 only) 
  sRsrc_VidRbvHRd,  l{"_sRsrc_VidRbvHRd"};					// High-Res (1 only) 
  sRsrc_VidRbvSEd,  l{"_sRsrc_VidRbvSEd"};					// SE (1 only) 
                
  sRsrc_VidRbvFPb,  l{"_sRsrc_VidRbvFPb"};					// Portrait (1,2) 
  sRsrc_VidRbvGSb,  l{"_sRsrc_VidRbvGSb"};					// Rubik (1,2,4)
  sRsrc_VidRbvHRb,  l{"_sRsrc_VidRbvHRb"};					// High-Res (1,2,4) 
  sRsrc_VidRbvSEb,  l{"_sRsrc_VidRbvSEb"};					// SE (1,2,4) 
                
  sRsrc_VidRbvGSc,  l{"_sRsrc_VidRbvGSc"};					// Rubik (1,2)
  sRsrc_VidRbvHRc,  l{"_sRsrc_VidRbvHRc"};					// High-Res (1,2) 
  sRsrc_VidRbvSEc,  l{"_sRsrc_VidRbvSEc"};					// SE (1,2)
#endif

//
// These are the directory entries for V8-based machines.  
//
  sRsrc_Vid_V8_GSa, l{"_sRsrc_Vid_V8_GSa"};					// Rubik, 512K VRAM configuration
  sRsrc_Vid_V8_VGAa, l{"_sRsrc_Vid_V8_VGAa"};				// VGA, 512K VRAM configuration
  sRsrc_Vid_V8_HRa, l{"_sRsrc_Vid_V8_HRa"};					// Hi-Res, 512K VRAM configuration

  sRsrc_Vid_V8_GSb, l{"_sRsrc_Vid_V8_GSb"};					// Rubik, 256K VRAM configuration
  sRsrc_Vid_V8_VGAb, l{"_sRsrc_Vid_V8_VGAb"};				// VGA, 256K VRAM configuration
  sRsrc_Vid_V8_HRb, l{"_sRsrc_Vid_V8_HRb"};					// Hi-Res, 256K VRAM configuration
                                                                
  sRsrc_Vid_V8_A2Ema, l{"_sRsrc_Vid_V8_A2Ema"};				// A2 emulation, 512K VRAM configuration
  sRsrc_Vid_V8_A2Emb, l{"_sRsrc_Vid_V8_A2Emb"};				// A2 emulation, 256K VRAM configuration
//                                                     		; all Rubik configs require VRAM
//
// DBLite has very simple video capabilites (for now).
//

#if !LC930

  sRsrc_Vid_GSC_LCD, l{"_sRsrc_Vid_GSC_LCD"};				// 1,2,4 (640x400)

//
// This range is used for the DAFB-based directory entries.  Lots of modes, so this is complicated.
//
    
  sRsrc_Vid_DAFB_19a, l{"_sRsrc_Vid_DAFB_19a"};				// 19" (1,2,4)
  sRsrc_Vid_DAFB_19b, l{"_sRsrc_Vid_DAFB_19b"};				// 19" (1,2,4,8)
                
  sRsrc_Vid_DAFB_FPa, l{"_sRsrc_Vid_DAFB_FPa"};				// Portrait (1,2,4)
  sRsrc_Vid_DAFB_FPb, l{"_sRsrc_Vid_DAFB_FPb"};				// Portrait (1,2,4,8)

  sRsrc_Vid_DAFB_GSa, l{"_sRsrc_Vid_DAFB_GSa"};				// Rubik (1,2,4,8)
  sRsrc_Vid_DAFB_GSb, l{"_sRsrc_Vid_DAFB_GSb"};				// Rubik (1,2,4,8,32)

  sRsrc_Vid_DAFB_2Pa, l{"_sRsrc_Vid_DAFB_2Pa"};				// 2-Page (1,2,4)
  sRsrc_Vid_DAFB_2Pb, l{"_sRsrc_Vid_DAFB_2Pb"};				// 2-Page (1,2,4,8)

  sRsrc_Vid_DAFB_LPa, l{"_sRsrc_Vid_DAFB_LPa"};				// Goldfish (1,2,4,8)
  sRsrc_Vid_DAFB_LPb, l{"_sRsrc_Vid_DAFB_LPb"};				// Goldfish (1,2,4,8,32)

  sRsrc_Vid_DAFB_HRa, l{"_sRsrc_Vid_DAFB_HRa"};				// High-Res (1,2,4,8)
  sRsrc_Vid_DAFB_HRb, l{"_sRsrc_Vid_DAFB_HRb"};				// High-Res (1,2,4,8,32)

  sRsrc_Vid_DAFB_VGAa, l{"_sRsrc_Vid_DAFB_VGAa"};			// VGA (1,2,4,8)             
  sRsrc_Vid_DAFB_VGAb, l{"_sRsrc_Vid_DAFB_VGAb"};			// VGA (1,2,4,8,32)              

  sRsrc_Vid_DAFB_RGBFPa, l{"_sRsrc_Vid_DAFB_RGBFPa"};		// RGB Portrait (1,2,4)
  sRsrc_Vid_DAFB_RGBFPb, l{"_sRsrc_Vid_DAFB_RGBFPb"};		// RGB Portrait (1,2,4,8)

  sRsrc_Vid_DAFB_RGB2Pa, l{"_sRsrc_Vid_DAFB_RGB2Pa"};		// RGB 2-Page (1,2,4)
  sRsrc_Vid_DAFB_RGB2Pb, l{"_sRsrc_Vid_DAFB_RGB2Pb"};		// RGB 2-Page (1,2,4,8)

  sRsrc_Vid_DAFB_NTSCSTa, l{"_sRsrc_Vid_DAFB_NTSCSTa"};		// NTSC safe title (1,2,4,8)
  sRsrc_Vid_DAFB_NTSCSTb, l{"_sRsrc_Vid_DAFB_NTSCSTb"};		// NTSC safe title (1,2,4,8,32)
  sRsrc_Vid_DAFB_NTSCFFa, l{"_sRsrc_Vid_DAFB_NTSCFFa"};		// NTSC full frame (1,2,4,8)
  sRsrc_Vid_DAFB_NTSCFFb, l{"_sRsrc_Vid_DAFB_NTSCFFb"}; 	// NTSC full frame (1,2,4,8,32)

  sRsrc_Vid_DAFB_PALSTa, l{"_sRsrc_Vid_DAFB_PALSTa"};		// PAL safe title (1,2,4,8)
  sRsrc_Vid_DAFB_PALSTb, l{"_sRsrc_Vid_DAFB_PALSTb"};		// PAL safe title (1,2,4,8,32)
  sRsrc_Vid_DAFB_PALFFa, l{"_sRsrc_Vid_DAFB_PALFFa"};		// PAL full frame (1,2,4,8)
  sRsrc_Vid_DAFB_PALFFb, l{"_sRsrc_Vid_DAFB_PALFFb"};		// PAL full frame (1,2,4,8,32)

  sRsrc_Vid_DAFB_NTSCconvSTx, l{"_sRsrc_Vid_DAFB_NTSCconvST"};	// NTSC ST, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_NTSCconvST, l{"_sRsrc_Vid_DAFB_NTSCconvST"};	// NTSC ST, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_NTSCconvFFx, l{"_sRsrc_Vid_DAFB_NTSCconvFF"};	// NTSC FF, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_NTSCconvFF, l{"_sRsrc_Vid_DAFB_NTSCconvFF"};	// NTSC FF, convolved (1,2,4,8)
                
  sRsrc_Vid_DAFB_PALconvSTx, l{"_sRsrc_Vid_DAFB_PALconvST"};	// PAL ST, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_PALconvST, l{"_sRsrc_Vid_DAFB_PALconvST"};		// PAL ST, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_PALconvFFx, l{"_sRsrc_Vid_DAFB_PALconvFF"};	// PAL FF, convolved (1,2,4,8)
  sRsrc_Vid_DAFB_PALconvFF, l{"_sRsrc_Vid_DAFB_PALconvFF"};		// PAL FF, convolved (1,2,4,8)
                
//
// The portables have very simple video capabilities - a single sRsrc.
//
  sRsrc_Vid_Tim_LCD, l{"_sRsrc_Vid_Tim_LCD"};					// 1bpp only
                
//
// Apollo also has very simple video capabilites.
//
  sRsrc_Vid_Apollo, l{"_sRsrc_Vid_Apollo"};						// 1bpp only

//
// Ugh.  I needed more entries for DAFB, so I had to put them here.
//
                
  sRsrc_Vid_DAFB_HRax, l{"_sRsrc_Vid_DAFB_HRax"};			// HiRes (1,2,4,8,16)
  sRsrc_Vid_DAFB_HRbx, l{"_sRsrc_Vid_DAFB_HRbx"};			// HiRes (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_VGAax, l{"_sRsrc_Vid_DAFB_VGAax"};			// VGA (1,2,4,8,16)
  sRsrc_Vid_DAFB_VGAbx, l{"_sRsrc_Vid_DAFB_VGAbx"};			// VGA (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_LPax, l{"_sRsrc_Vid_DAFB_LPax"};			// GoldFish (1,2,4,8,16)
  sRsrc_Vid_DAFB_LPbx, l{"_sRsrc_Vid_DAFB_LPbx"};			// GoldFish (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_SVGAax, l{"_sRsrc_Vid_DAFB_SVGAax"};		// SuperVGA (1,2,4,8,16)
  sRsrc_Vid_DAFB_SVGAbx, l{"_sRsrc_Vid_DAFB_SVGAbx"};		// SuperVGA (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_SVGAa, l{"_sRsrc_Vid_DAFB_SVGAa"};			// SuperVGA (1,2,4,8)
  sRsrc_Vid_DAFB_SVGAb, l{"_sRsrc_Vid_DAFB_SVGAb"};			// SuperVGA (1,2,4,8,32)
                
  sRsrc_Vid_DAFB_GSx, l{"_sRsrc_Vid_DAFB_GSx"};				// Rubik (1,2,4,8,16,32)
  sRsrc_Vid_DAFB_RGBFPbx, l{"_sRsrc_Vid_DAFB_RGBFPbx"};		// RGBPort (1,2,4,8,16)
  sRsrc_Vid_DAFB_GSz, l{"_sRsrc_Vid_DAFB_GSz"};				// Rubik (1,2,4,8,16)
  sRsrc_Vid_DAFB_RGB2Pbx, l{"_sRsrc_Vid_DAFB_RGB2Pbx"};		// Vesuvio (1,2,4,8,16)
                
  sRsrc_Vid_DAFB_NTSCSTax, l{"_sRsrc_Vid_DAFB_NTSCSTax"};	// NTSC ST (1,2,4,8,16)
  sRsrc_Vid_DAFB_NTSCSTbx, l{"_sRsrc_Vid_DAFB_NTSCSTbx"};	// NTSC ST (1,2,4,8,16,32)
  sRsrc_Vid_DAFB_NTSCFFax, l{"_sRsrc_Vid_DAFB_NTSCFFax"};	// NTSC FF (1,2,4,8,16)
  sRsrc_Vid_DAFB_NTSCFFbx, l{"_sRsrc_Vid_DAFB_NTSCFFbx"};	// NTSC FF (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_PALSTax, l{"_sRsrc_Vid_DAFB_PALSTax"};		// PAL ST (1,2,4,8,16)
  sRsrc_Vid_DAFB_PALSTbx, l{"_sRsrc_Vid_DAFB_PALSTbx"};		// PAL ST extended (1,2,4,8,16,32)
  sRsrc_Vid_DAFB_PALFFax, l{"_sRsrc_Vid_DAFB_PALFFax"};		// PAL FF (1,2,4,8,16)
  sRsrc_Vid_DAFB_PALFFbx, l{"_sRsrc_Vid_DAFB_PALFFbx"};		// PAL FF extended (1,2,4,8,16,32)
                
  sRsrc_Vid_DAFB_19bx, l{"_sRsrc_Vid_DAFB_19bx"};			// 19" (1,2,4,8,16)

#endif

//
// The final range is reserved for miscellaneous stuff - Ethernet and Double Exposure.  There's also some
//   CPU sResources to identify ROM families.
//

  sRsrc_CPUMacIIci, l{"_sRsrc_CPUMacIIci"};
  sRsrc_CPUMac040,  l{"_sRsrc_CPUMacO40"}; 

#if !LC930
  sRsrc_Sonic,      l{"_sRsrc_Sonic"};						// Onboard Sonic Ethernet chip
#endif

  sRsrc_DoubleExposure, l{"_sRsrc_DoubleExposure"};			// special sRsrc for no-config
//                                                          ;   ROM Double Exposure 
                
}};


//-------------------------------------------------------------
//
//           sRsrc_Board Lists
//
//           These board sResources contain the “card” name seen by the  
//               Monitors cdev.
//           Another important part of the board sRsrc is the PrimaryInit code.
//               This universal section of code performs all necessary sRsrc 
//               pruning which entails a full identification of the CPU type
//               and configuration.  On entry to the routine, the full contents
//               of the sRsrc directory are presented.  On exit, only one board
//               sRsrc, one video sRsrc, and any other miscellaneous sRsrcs
//               remain.
//           In theory, each board sRsrc should contain a PrimaryInit entry.
//               The Slot Manager expects only one board sRsrc and one PrimaryInit 
//               per card.  Since the Slot Manager scans in ascending spID order, 
//               only the first entry in the directory (the Mac II resource) has
//               a PrimaryInit.  After this universal PrimaryInit runs everything
//               that needs to happen has happened, so there's no need for 
//               the ultimate board sRsrc list to run another PrimaryInit.
//
//-------------------------------------------------------------

resource 'boar' (165, "_sRsrc_BdMacII") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh II"}; 
  BoardId,          d{MIIBoardId}; 
  PrimaryInit,      l{"_sPrimaryInitRec"};	// This PrimaryInit is universal for all machines
  VendorInfo,       l{"_VendorInfo"};		// supported by this sRsrc directory.
}};

resource 'boar' (175, "_sRsrc_BdMacIIx") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh IIx"};
  BoardId,          d{MIIxBoardId}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (185, "_sRsrc_BdMacIIcx") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh IIcx"};
  BoardId,          d{MIIcxBoardId}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (195, "_sRsrc_BdMacSE30") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh SE/30"};
  BoardId,          d{SE30BoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (205, "_sRsrc_BdMacIIci") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh IIci Built-In Video"};
  BoardId,          d{ciVidBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (215, "_sRsrc_BdMacIIfx") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh IIfx"}; 
  BoardId,          d{MIIfxBoardId}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (225, "_sRsrc_BdErickson") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh A Built-In Video"};
  BoardId,          d{EricksonBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
}};

resource 'boar' (235, "_sRsrc_BdElsie") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh B Built-In Video"};
  BoardId,          d{ElsieBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  sRsrcVidNames,    l{"_V8VidNameDir"};
}};

#if !LC930

resource 'boar' (245, "_sRsrc_BdEclipse") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh C Built-In Video"};
  sRsrcIcon,        l{"_VidICONEclipse"}; 
  BoardId,          d{EclipseBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DAFBVidNameDir"};
  sVidParmDir,      l{"_VidParmDir_DAFB"}; 
}};

resource 'boar' (255, "_sRsrc_BdTIM") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh D Built-In Video"};
  sRsrcIcon,        l{"_VidICONTIM"}; 
  BoardId,          d{TIMBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  sRsrcVidNames,    l{"_TIMVidNameDir"};
}};

resource 'boar' (265, "_sRsrc_BdSpike") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh E Built-In Video"}; 
  sRsrcIcon,        l{"_VidICONSpike"}; 
  BoardId,          d{SpikeBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DAFBVidNameDir"};
  sVidParmDir,      l{"_VidParmDir_DAFB"}; 
}};

resource 'boar' (275, "_sRsrc_BdApollo") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh F Built-In Video"};
  sRsrcIcon,        l{"_VidICONApollo"}; 
  BoardId,          d{ApolloBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  sRsrcVidNames,    l{"_ApolloVidNameDir"};
}};

resource 'boar' (285, "_sRsrc_BdZydeco") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh G Built-In Video"}; 
  sRsrcIcon,        l{"_VidICONZydeco"}; 
  BoardId,          d{ZydecoBrdID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DAFBVidNameDir"};
  sVidParmDir,      l{"_VidParmDir_DAFB"}; 
}};

resource 'boar' (295, "_sRsrc_BdDBLite") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh H Built-In Video"};
  BoardId,          d{DBLiteBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DBLiteVidNameDir"}; // 
}};

resource 'boar' (305, "_sRsrc_BdWombat") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh I Built-In Video"};
  sRsrcIcon,        l{"_VidICONWombat"}; 
  BoardId,          d{WombatBrdID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DAFBVidNameDir"}; // 
  sVidParmDir,      l{"_VidParmDir_DAFB"}; 
}};
            
resource 'boar' (315, "_sRsrc_BdDartanian") {{
  sRsrcType,        l{"_BoardType"}; 
  sRsrcName,        c{"Macintosh J Built-In Video"}; 
  BoardId,          d{DartanianBoardID}; 
  VendorInfo,       l{"_VendorInfo"}; 
  SecondaryInit,    l{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_DartanianVidNameDir"}; 
}};

#endif

//=====================================================================
// Primary/Secondary/Super Init records
//=====================================================================

resource 'node' (418, "_sPrimaryInitRec") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"PrimaryInit.rsrc"};
				   type{'decl'};
				     id{200};}}};
}};

resource 'node' (419, "_sSecondaryInit") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"SecondaryInit.rsrc"};
				   type{'decl'};
				     id{210};}}};
}};

resource 'node' (420, "_sSuperInitRec") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"SuperInit.rsrc"};
				   type{'decl'};
				     id{220};}}};
}};

//-------------------------------------------------------------
//               Video Name Directory
//-------------------------------------------------------------
// 
// A name directory is structured identically to that of a gamma directory.
// For each possible video sRsrc spID, there is a corresponding OSLstEntry
// pointing to the name data.  Also, each name data block contains a word-sized
// localization id.
//

resource 'vdir' (345, "_DAFBVidNameDir") {{

  sRsrc_Vid_DAFB_19a, 		l{"_sName_19"}; 
  sRsrc_Vid_DAFB_19b, 		l{"_sName_19"}; 
                
  sRsrc_Vid_DAFB_FPa, 		l{"_sName_FP"}; 
  sRsrc_Vid_DAFB_FPb, 		l{"_sName_FP"}; 
                
  sRsrc_Vid_DAFB_GSa, 		l{"_sName_GS"}; 
  sRsrc_Vid_DAFB_GSb, 		l{"_sName_GS"}; 
                
  sRsrc_Vid_DAFB_2Pa, 		l{"_sName_2P"}; 
  sRsrc_Vid_DAFB_2Pb, 		l{"_sName_2P"}; 
                
  sRsrc_Vid_DAFB_LPa, 		l{"_sName_LP"}; 
  sRsrc_Vid_DAFB_LPb, 		l{"_sName_LP"}; 
                
  sRsrc_Vid_DAFB_HRa, 		l{"_sName_HR"}; 
  sRsrc_Vid_DAFB_HRb, 		l{"_sName_HR"}; 
                
  sRsrc_Vid_DAFB_VGAa, 		l{"_sName_VGA"}; 
  sRsrc_Vid_DAFB_VGAb, 		l{"_sName_VGA"}; 
                
  sRsrc_Vid_DAFB_RGBFPa, 	l{"_sName_RGBFP"}; 
  sRsrc_Vid_DAFB_RGBFPb, 	l{"_sName_RGBFP"}; 
                
  sRsrc_Vid_DAFB_RGB2Pa, 	l{"_sName_RGB2P"}; 
  sRsrc_Vid_DAFB_RGB2Pb, 	l{"_sName_RGB2P"}; 
                
  sRsrc_Vid_DAFB_NTSCSTa, 	l{"_sName_NTSCST"}; 
  sRsrc_Vid_DAFB_NTSCSTb, 	l{"_sName_NTSCST"}; 
  sRsrc_Vid_DAFB_NTSCFFa, 	l{"_sName_NTSCFF"}; 
  sRsrc_Vid_DAFB_NTSCFFb, 	l{"_sName_NTSCFF"}; 
                
  sRsrc_Vid_DAFB_PALSTa, 	l{"_sName_PALST"}; 
  sRsrc_Vid_DAFB_PALSTb, 	l{"_sName_PALST"}; 
  sRsrc_Vid_DAFB_PALFFa, 	l{"_sName_PALFF"}; 
  sRsrc_Vid_DAFB_PALFFb, 	l{"_sName_PALFF"}; 
                
  sRsrc_Vid_DAFB_NTSCconvSTx, l{"_sName_NTSCconvST"}; 
  sRsrc_Vid_DAFB_NTSCconvST,  l{"_sName_NTSCconvST"}; 
  sRsrc_Vid_DAFB_NTSCconvFFx, l{"_sName_NTSCconvFF"}; 
  sRsrc_Vid_DAFB_NTSCconvFF,  l{"_sName_NTSCconvFF"}; 
                
  sRsrc_Vid_DAFB_PALconvSTx,  l{"_sName_PALconvST"}; 
  sRsrc_Vid_DAFB_PALconvST,   l{"_sName_PALconvST"}; 
  sRsrc_Vid_DAFB_PALconvFFx,  l{"_sName_PALconvFF"}; 
  sRsrc_Vid_DAFB_PALconvFF,   l{"_sName_PALconvFF"}; 
                
  sRsrc_Vid_DAFB_HRax, l{"_sName_HR"}; 
  sRsrc_Vid_DAFB_HRbx, l{"_sName_HR"}; 
                
  sRsrc_Vid_DAFB_VGAax, l{"_sName_VGA"}; 
  sRsrc_Vid_DAFB_VGAbx, l{"_sName_VGA"}; 
                
  sRsrc_Vid_DAFB_LPax, l{"_sName_LP"}; 
  sRsrc_Vid_DAFB_LPbx, l{"_sName_LP"}; 
                
  sRsrc_Vid_DAFB_SVGAax, l{"_sName_SVGA56"}; 
  sRsrc_Vid_DAFB_SVGAbx, l{"_sName_SVGA56"}; 
                
  sRsrc_Vid_DAFB_SVGAa, l{"_sName_SVGA56"}; 
  sRsrc_Vid_DAFB_SVGAb, l{"_sName_SVGA56"}; 
                
  sRsrc_Vid_DAFB_GSx, l{"_sName_GS"}; 
  sRsrc_Vid_DAFB_RGBFPbx, l{"_sName_RGBFP"}; 
  sRsrc_Vid_DAFB_GSz, l{"_sName_GS"}; 
  sRsrc_Vid_DAFB_RGB2Pbx, l{"_sName_RGB2P"}; 
                
  sRsrc_Vid_DAFB_NTSCSTax, l{"_sName_NTSCST"}; 
  sRsrc_Vid_DAFB_NTSCSTbx, l{"_sName_NTSCST"}; 
  sRsrc_Vid_DAFB_NTSCFFax, l{"_sName_NTSCFF"}; 
  sRsrc_Vid_DAFB_NTSCFFbx, l{"_sName_NTSCFF"}; 
                
  sRsrc_Vid_DAFB_PALSTax, l{"_sName_PALST"}; 
  sRsrc_Vid_DAFB_PALSTbx, l{"_sName_PALST"}; 
  sRsrc_Vid_DAFB_PALFFax, l{"_sName_PALFF"}; 
  sRsrc_Vid_DAFB_PALFFbx, l{"_sName_PALFF"}; 
                
  sRsrc_Vid_DAFB_19bx, l{"_sName_19"}; 
                
}};

resource 'vdir' (350, "_V8VidNameDir") {{

	sRsrc_Vid_V8_GSa,	l{"_sName_GS"};
	sRsrc_Vid_V8_VGAa,	l{"_sName_VGA"};
	sRsrc_Vid_V8_HRa,	l{"_sName_HR"};
	
	sRsrc_Vid_V8_GSb,	l{"_sName_GS"};
	sRsrc_Vid_V8_VGAb,	l{"_sName_VGA"};
	sRsrc_Vid_V8_HRb,	l{"_sName_HR"};
}};

resource 'vmna' (360, "_sName_FP")     		{128, " 640 x 870, 75 Hz (Grayscale Only)"};
resource 'vmna' (365, "_sName_GS")     		{129, " 512 x 384, 60 Hz"};
resource 'vmna' (370, "_sName_2P")     		{130, "1152 x 870, 75 Hz (Grayscale Only)"};
resource 'node' (375, "_sName_GF")     		{{include{l{"_sName_LP"}};}};
resource 'vmna' (380, "_sName_LP")     		{131, " 832 x 624, 75 Hz"};
resource 'vmna' (385, "_sName_HR")     		{133, " 640 x 480, 67 Hz"};
resource 'vmna' (390, "_sName_VGA")   		{134, " 640 x 480, 60 Hz (VGA)"};
resource 'vmna' (395, "_sName_SVGA56") 		{135, " 800 x 600, 56 Hz (SVGA)"};
resource 'vmna' (400, "_sName_RGBFP")  		{136, " 640 x 870, 75 Hz"};
resource 'vmna' (405, "_sName_RGB2P")  		{137, "1152 x 870, 75 Hz"};
resource 'vmna' (410, "_sName_NTSCST") 		{138, " 512 x 384, NTSC"};
resource 'vmna' (415, "_sName_NTSCFF") 		{139, " 640 x 480, NTSC"};
resource 'vmna' (420, "_sName_PALST")  		{140, " 640 x 480, PAL"};
resource 'vmna' (425, "_sName_PALFF")  		{141, " 768 x 576, PAL"};
resource 'vmna' (430, "_sName_NTSCconvST") 	{142, " 512 x 384, NTSC Convolved"};
resource 'vmna' (435, "_sName_NTSCconvFF") 	{143, " 640 x 480, NTSC Convolved"};
resource 'vmna' (440, "_sName_PALconvST") 	{144, " 640 x 480, PAL Convolved"};
resource 'vmna' (445, "_sName_PALconvFF") 	{145, " 768 x 576, PAL Convolved"};
resource 'vmna' (450, "_sName_19")        	{146, "1024 x 768, 75 Hz"};
resource 'vmna' (455, "_sName_GS560")  		{147, " 560 x 384, 60 Hz"};
resource 'vmna' (460, "_sName_SVGA72") 		{148, " 800 x 600, 72 Hz (VESA)"};
resource 'vmna' (465, "_sName_SxVGA60") 	{149, "1024 x 768, 60 Hz (VESA)"};
resource 'vmna' (470, "_sName_SxVGA70") 	{150, "1024 x 768, 70 Hz (VESA)"};
resource 'vmna' (475, "_sName_HR400") 		{151, " 640 x 400, 67 Hz"};
resource 'vmna' (480, "_sName_HRMAZ") 		{151, " 704 x 512, 67 Hz"};
resource 'vmna' (485, "_sName_512x384") 	{152, " 512 x 384"};
resource 'vmna' (495, "_sName_640x480") 	{154, " 640 x 480"};
resource 'vmna' (500, "_sName_768x576") 	{155, " 768 x 576"};

// We’ve got the room, so what the heck:  Let’s put video name directories in for TIMs, Apollos, DB-Lites!
//
resource 'vdir' (505, "_TIMVidNameDir") {{
  sRsrc_Vid_Tim_LCD, l{"_sName_LCD"}; 
}};

resource 'node' (510, "_DartanianVidNameDir") {{
  include{l{"_DBLiteVidNameDir"}};
}};

resource 'vdir' (515, "_DBLiteVidNameDir") {{
  sRsrc_Vid_GSC_LCD, l{"_sName_LCD"}; 
}};

resource 'vdir' (520, "_ApolloVidNameDir") {{
  sRsrc_Vid_Apollo, l{"_sName_Apollo"}; 
}};

resource 'vmna' (525, "_sName_LCD")    {128, " 640 x 400 (Black & White)"};
resource 'vmna' (530, "_sName_Apollo") {128, " 512 x 342 (Black & White)"};

                
//-------------------------------------------------------------
//               Board Type
//-------------------------------------------------------------

resource 'styp' (535, "_BoardType") {CatBoard, TypBoard, 0, 0};

//-------------------------------------------------------------
//               Vendor Info
//-------------------------------------------------------------

resource 'vend' (540, "_VendorInfo") {{
  VendorId,         c{"Copyright © 1986-1993 by Apple Computer, Inc.  All Rights Reserved."};
  RevLevel,         c{"Macintosh CPU Family 5.1"};     // offset to revision 
  PartNum,          c{"Universal DeclROM"};            // offset to part number descriptor
  Date,             c{$$Date};                  	   // offset to ROM build date descriptor
}};

//-------------------------------------------------------------
//               CPU sResource List
//-------------------------------------------------------------


resource 'node' (575, "_sRsrc_CPUMacIIci") {{
  include{l{"_sRsrc_CPUMac030"}};
}};

resource 'srsc' (575, "_sRsrc_CPUMac030") {{
  sRsrcType,        l{"_CPUMacIIci"};					// ’030 Class Machines (plus MacII & LC).
  sRsrcName,        l{"_CPUMacIIciName"}; 
  MajRAMSp,         l{"_MajRAMSp"}; 
  MinROMSp,         l{"_MinROMSp"}; 
}};

                    
resource 'srsc' (578, "_sRsrc_CPUMacO40") {{
  sRsrcType,        l{"_CPUMacO40"};					// ’040 Class Machines.
  sRsrcName,        l{"_CPUMac040Name"}; 
  MajRAMSp,         l{"_MajRAMSp"}; 
  MinROMSp,         l{"_MinROMSp"}; 
}};


resource 'styp' (583, "_CPUMacIIci") {CatCPU, Typ68030, DrSwMacCPU, drHWRBV};      
resource 'styp' (585, "_CPUMacO40")  {CatCPU, Type68040, DrSwMacCPU, drHwRBV};

resource 'node' (590, "_CPUMacIIciName") {{
  cstring{"CPU_68030_\_MacIIFamily"};					// Name of sResource
}};

resource 'node' (595, "_CPUMac040Name") {{
  cstring{"CPU_68040"};									// Name of sResource
}};

resource 'node' (600, "_MajRAMSp") {{
  longs{{$00000000;$3FFFFFFF;}};						// RAM space
}};

resource 'node' (605, "_MinROMSp") {{
  longs{{$F0800000;$F0FFFFFF;}};						// ROM space
}};

//-------------------------------------------------------------
//               Functional sResources
//-------------------------------------------------------------

resource 'srsc' (610, "_sRsrc_VidRbvHRa") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthHRa"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvHR"}; 


//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMHR"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMHR"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBMHR"}; 

}};


//----------------------------------

resource 'srsc' (615, "_sRsrc_VidRbvHRb") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthHRb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvHR"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMHR"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMHR"};					// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (620, "_sRsrc_VidRbvHRc") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthHRc"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvHR"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMHR"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (625, "_sRsrc_VidRbvHRd") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthHRd"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvHR"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMHR"};					// offset to OneBitMode parameters

}};


//----------------------------------

resource 'srsc' (630, "_sRsrc_VidRbvFPa") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthFPa"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDir_FP"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMFP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMFP"};					// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (635, "_sRsrc_VidRbvFPb") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthFPb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDir_FP"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMFP"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (640, "_sRsrc_VidRbvFPc") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthFPc"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDir_FP"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMFP"};					// offset to OneBitMode parameters

}};


//----------------------------------

resource 'srsc' (645, "_sRsrc_VidRbvGSa") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthGSa"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMGS"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMGS"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMGS"};					// offset to TwoBitMode parameters
  FourthVidMode,    l{"_EBMGS"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (650, "_sRsrc_VidRbvGSb") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthGSb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMGS"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMGS"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMGS"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (655, "_sRsrc_VidRbvGSc") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthGSc"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMGS"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMGS"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (660, "_sRsrc_VidRbvGSd") {{
  sRsrcType,        l{"_VideoTypeRBV"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};			// offset to driver directory
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthGSd"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMGS"};					// offset to OneBitMode parameters

}};


//----------------------------------

resource 'srsc' (665, "_sRsrc_VidRbvSEa") {{
  sRsrcType,        l{"_VideoTypeRBV"};					// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};					// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthSEa"};				// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvSE"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMSE"};						// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMSE"};						// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMSE"};						// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBMSE"};						// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (670, "_sRsrc_VidRbvSEb") {{
  sRsrcType,        l{"_VideoTypeRBV"};					// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};					// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthSEb"};				// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvSE"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMSE"};						// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMSE"};						// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMSE"};						// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (675, "_sRsrc_VidRbvSEc") {{
  sRsrcType,        l{"_VideoTypeRBV"};					// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};					// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthSEc"};				// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvSE"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMSE"};						// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMSE"};						// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (680, "_sRsrc_VidRbvSEd") {{
  sRsrcType,        l{"_VideoTypeRBV"};					// Video Type descriptor
  sRsrcName,        l{"_VideoNameRBV"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirRBV"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseRBV"};					// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthSEd"};				// offset to frame buffer length

  sGammaDir,        a{"_GammaDirRbvSE"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMSE"};						// offset to OneBitMode parameters

}};


//----------------------------------

resource 'srsc' (685, "_sRsrc_Vid_V8_GSa") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_GSa"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_GSa"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_GSa"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_GSa"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_V8_GSa"};					// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_V8_GS"};					// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (690, "_sRsrc_Vid_V8_GSb") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_GSb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_GSb"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_GSb"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_GSb"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_V8_GSb"};					// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (695, "_sRsrc_Vid_V8_A2Ema") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_A2Ema"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_A2Ema"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_A2Ema"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_A2Ema"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_V8_A2Ema"};					// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (700, "_sRsrc_Vid_V8_A2Emb") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_A2Emb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsGS"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_A2Emb"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_A2Emb"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_A2Emb"};					// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (705, "_sRsrc_Vid_V8_HRa") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_HRa"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsHR"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_HRa"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_HRa"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_HRa"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_V8_HR"};					// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (710, "_sRsrc_Vid_V8_HRb") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_HRb"};			// offset to frame buffer length

  sGammaDir,        a{"_GammaDirElsHR"}; 

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_HRb"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_HRb"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_HRb"};					// offset to FourBitMode parameters

}};


//----------------------------------
//
// The two VGA modes have the same configurations and capabilities as the Mac II High-Res, so, to 
//   save a little ROM space, we have a distinct sRsrc list, but the elements of this list all
//   point to High-Res data structures.
//

resource 'srsc' (715, "_sRsrc_Vid_V8_VGAa") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_VGAa"};			// offset to frame buffer length

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_HRa"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_HRa"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_HRa"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_V8_HR"};					// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (720, "_sRsrc_Vid_V8_VGAb") {{
  sRsrcType,        l{"_VideoTypeElsie"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameV8"};					// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirElsie"};				// offset to driver directory
  sRsrcHWDevID,     d{1};								// hardware device id

  MinorBaseOS,      l{"_MinorBaseElsie"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLength_V8_VGAb"};			// offset to frame buffer length

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_V8_HRb"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_V8_HRb"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_V8_HRb"};					// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (725, "_sRsrc_Vid_DAFB_19a") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_19a"}; 

  sGammaDir,        a{"_GammaDir_DAFB_19"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_19"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_19"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_19"};				// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (730, "_sRsrc_Vid_DAFB_19b") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_19b"}; 

  sGammaDir,        a{"_GammaDir_DAFB_19"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_19"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_19"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_19"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_19"};				// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (735, "_sRsrc_Vid_DAFB_19bx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_19bx"}; 

  sGammaDir,        a{"_GammaDir_DAFB_19"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_19"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_19"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_19"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_19"};				// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_19"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (740, "_sRsrc_Vid_DAFB_FPa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_FPa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_FP"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_FP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_FP"};				// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (745, "_sRsrc_Vid_DAFB_FPb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_FPb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_FP"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_FP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_FP"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_FP"};				// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (750, "_sRsrc_Vid_DAFB_2Pa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFB2PW"}; 
  MinorLength,      l{"_MinorLength_DAFB_2Pa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_2P"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_2P"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_2P"};				// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (755, "_sRsrc_Vid_DAFB_2Pb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFB2PW"}; 
  MinorLength,      l{"_MinorLength_DAFB_2Pb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_2P"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_2P"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_2P"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_2P"};				// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (760, "_sRsrc_Vid_DAFB_LPa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBSW"}; 
  MinorLength,      l{"_MinorLength_DAFB_LPa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_LP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_LP"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_LP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_LP"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_LP"};				// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (765, "_sRsrc_Vid_DAFB_LPb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBS"}; 
  MinorLength,      l{"_MinorLength_DAFB_LPb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_LP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_LP"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_LP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_LP"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_LP"};				// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_LP"};			// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (770, "_sRsrc_Vid_DAFB_LPax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBSW"}; 
  MinorLength,      l{"_MinorLength_DAFB_LPax"}; 

  sGammaDir,        a{"_GammaDir_DAFB_LP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_LP"};				// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_LP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_LP"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_LP"};				// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_LP"};			// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (775, "_sRsrc_Vid_DAFB_LPbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBS"}; 
  MinorLength,      l{"_MinorLength_DAFB_LPb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_LP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_LP"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_LP"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_LP"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_LP"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_LP"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_LP"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (780, "_sRsrc_Vid_DAFB_GSa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_GSa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_GS"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_GS"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_GS"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_GS"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (785, "_sRsrc_Vid_DAFB_GSb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_GSb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_GS"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_GS"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_GS"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_GS"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_GS"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (790, "_sRsrc_Vid_DAFB_GSx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_GSb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_GS"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_GS"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_GS"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_GS"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_GS"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_GS"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (795, "_sRsrc_Vid_DAFB_GSz") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_GSb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_GS"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_GS"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_GS"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_GS"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_GS"};		// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'node' (800, "_sRsrc_Vid_DAFB_VGAa") {{
  include{l{"_sRsrc_Vid_DAFB_HRa"}};
}};

resource 'srsc' (805, "_sRsrc_Vid_DAFB_HRa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_HRa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_HR"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_HR"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_HR"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_HR"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'node' (810, "_sRsrc_Vid_DAFB_VGAb") {{
  include{l{"_sRsrc_Vid_DAFB_HRb"}};
}};

resource 'srsc' (815, "_sRsrc_Vid_DAFB_HRb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_HRb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_HR"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_HR"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_HR"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_HR"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_HR"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'node' (820, "_sRsrc_Vid_DAFB_VGAax") {{
  include{l{"_sRsrc_Vid_DAFB_HRax"}};
}};

resource 'srsc' (825, "_sRsrc_Vid_DAFB_HRax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_HRax"}; 

  sGammaDir,        a{"_GammaDir_DAFB_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_HR"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_HR"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_HR"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_HR"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_HR"};		// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'node' (830, "_sRsrc_Vid_DAFB_VGAbx") {{
  include{l{"_sRsrc_Vid_DAFB_HRbx"}};
}};

resource 'srsc' (835, "_sRsrc_Vid_DAFB_HRbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_HRb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_HR"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_HR"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_HR"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_HR"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_HR"};	// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_HR"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (840, "_sRsrc_Vid_DAFB_SVGAa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBSW"}; 
  MinorLength,      l{"_MinorLength_DAFB_SVGAa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_VGA"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_SVGA"};	// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_SVGA"};	// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_SVGA"};	// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_SVGA"};	// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (845, "_sRsrc_Vid_DAFB_SVGAb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBS"}; 
  MinorLength,      l{"_MinorLength_DAFB_SVGAb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_VGA"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_SVGA"};	// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_SVGA"};	// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_SVGA"};	// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_SVGA"};	// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_SVGA"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (850, "_sRsrc_Vid_DAFB_SVGAax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBSW"}; 
  MinorLength,      l{"_MinorLength_DAFB_SVGAax"}; 

  sGammaDir,        a{"_GammaDir_DAFB_VGA"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_SVGA"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_SVGA"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_SVGA"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_SVGA"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_SVGA"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (855, "_sRsrc_Vid_DAFB_SVGAbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBBS"}; 
  MinorLength,      l{"_MinorLength_DAFB_SVGAb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_VGA"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_SVGA"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_SVGA"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_SVGA"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_SVGA"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_SVGA"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_SVGA"};		// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (860, "_sRsrc_Vid_DAFB_RGBFPa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_FPa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGBFP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_FP"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_FP"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_FP"};			// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (865, "_sRsrc_Vid_DAFB_RGBFPb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_FPb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGBFP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_FP"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_FP"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_FP"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_FP"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (870, "_sRsrc_Vid_DAFB_RGBFPbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBStd"}; 
  MinorLength,      l{"_MinorLength_DAFB_FPbx"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGBFP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_FP"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_FP"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_FP"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_FP"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_FP"};		// offset to SixteenBitMode parameters
                
}};


//----------------------------------


resource 'srsc' (875, "_sRsrc_Vid_DAFB_RGB2Pa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFB2PW"}; 
  MinorLength,      l{"_MinorLength_DAFB_2Pa"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGB2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_2P"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_2P"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_2P"};			// offset to FourBitMode parameters

}};


//----------------------------------

resource 'srsc' (880, "_sRsrc_Vid_DAFB_RGB2Pb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFB2PW"}; 
  MinorLength,      l{"_MinorLength_DAFB_2Pb"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGB2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_2P"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_2P"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_2P"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_2P"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (885, "_sRsrc_Vid_DAFB_RGB2Pbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFB2P"}; 
  MinorLength,      l{"_MinorLength_DAFB_2Pbx"}; 

  sGammaDir,        a{"_GammaDir_DAFB_RGB2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBM_DAFB_2P"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_2P"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_2P"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_2P"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_2P"};		// offset to SixteenBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (890, "_sRsrc_Vid_DAFB_NTSCSTa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCSTa"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCST"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCST"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCST"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCST"};		// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (895, "_sRsrc_Vid_DAFB_NTSCSTb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCSTb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCST"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCST"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCST"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCST"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_NTSCST"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (900, "_sRsrc_Vid_DAFB_NTSCSTax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCSTax"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCST"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCST"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCST"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCST"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_NTSCST"};	// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (905, "_sRsrc_Vid_DAFB_NTSCSTbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCSTb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCST"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCST"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCST"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCST"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_NTSCST"};	// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_NTSCST"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (910, "_sRsrc_Vid_DAFB_NTSCconvST") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSCConv"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCconvST"}; 

  FirstVidMode,     l{"_OBM_DAFB_NTSCSTconv"};	// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCSTconv"};	// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCSTconv"};	// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCSTconv"};	// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (915, "_sRsrc_Vid_DAFB_NTSCFFa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCFFa"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCFF"};	// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCFF"};	// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCFF"};	// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCFF"};	// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (920, "_sRsrc_Vid_DAFB_NTSCFFb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCFFb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCFF"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCFF"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCFF"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCFF"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_NTSCFF"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (925, "_sRsrc_Vid_DAFB_NTSCFFax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCFFax"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCFF"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCFF"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCFF"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCFF"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_NTSCFF"};	// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (930, "_sRsrc_Vid_DAFB_NTSCFFbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSC"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCFFb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCFF"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCFF"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCFF"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCFF"};		// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_NTSCFF"};	// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_NTSCFF"};	// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (935, "_sRsrc_Vid_DAFB_NTSCconvFF") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBNTSCConv"}; 
  MinorLength,      l{"_MinorLength_DAFB_NTSCconvFF"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_NTSCFFconv"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_NTSCFFconv"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_NTSCFFconv"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_NTSCFFconv"};		// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (940, "_sRsrc_Vid_DAFB_PALSTa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALW"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALSTa"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALST"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (945, "_sRsrc_Vid_DAFB_PALSTb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPAL"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALSTb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALST"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_PALST"};			// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (950, "_sRsrc_Vid_DAFB_PALSTax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALW"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALSTax"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALST"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_PALST"};			// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (955, "_sRsrc_Vid_DAFB_PALSTbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPAL"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALSTb"}; 
                
  FirstVidMode,     l{"_OBM_DAFB_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALST"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_PALST"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_PALST"};			// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------


resource 'srsc' (960, "_sRsrc_Vid_DAFB_PALconvST") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALConv"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALconvST"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALSTconv"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALSTconv"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALSTconv"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALSTconv"};		// offset to EightBitMode parameters

}};



//----------------------------------

resource 'srsc' (965, "_sRsrc_Vid_DAFB_PALFFa") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALW"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALFFa"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALFF"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (970, "_sRsrc_Vid_DAFB_PALFFb") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPAL"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALFFb"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALFF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D32BM_DAFB_PALFF"};			// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (975, "_sRsrc_Vid_DAFB_PALFFax") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALW"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALFFax"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALFF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_PALFF"};			// offset to SixteenBitMode parameters

}};


//----------------------------------

resource 'srsc' (980, "_sRsrc_Vid_DAFB_PALFFbx") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPAL"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALFFb"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALFF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_DAFB_PALFF"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_DAFB_PALFF"};			// offset to ThirtyTwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (985, "_sRsrc_Vid_DAFB_PALconvFF") {{
  sRsrcType,        l{"_VideoTypeDAFB"}; 
  sRsrcName,        l{"_VideoNameDAFB"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirDAFB"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseDAFBPALConv"}; 
  MinorLength,      l{"_MinorLength_DAFB_PALconvFF"}; 

  FirstVidMode,     l{"_OBM_DAFB_PALFFconv"};		// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBM_DAFB_PALFFconv"};		// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBM_DAFB_PALFFconv"};		// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_DAFB_PALFFconv"};		// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (990, "_sRsrc_Vid_Tim_LCD") {{
  sRsrcType,        l{"_VideoTypeTim"};				// Video Type descriptor
  sRsrcName,        l{"_VideoNameTim"};				// offset to Video Name string
  sRsrcDrvrDir,     l{"_VidDrvrDirTim"};			// offset to driver directory
  sRsrcFlags,       d{(0|(1<<fOpenAtStart))};		// flags
  sRsrcHWDevID,     d{1};							// hardware device id

  MinorBaseOS,      l{"_MinorBaseTim"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthLCD"};			// offset to frame buffer length

  sVidAttributes,   d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay))}; // built-in display                              <h46>

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMLCD"};					// offset to OneBitMode parameters

}};

                
//----------------------------------

resource 'srsc' (995, "_sRsrc_Vid_Apollo") {{
  sRsrcType,        l{"_VideoTypeApollo"};			// Video type descriptor.
  sRsrcName,        l{"_VideoNameApollo"};			// Offset to video name string.
  sRsrcDrvrDir,     l{"_VidDrvrDirApollo"};			// Offset to driver directory.
  sRsrcFlags,       d{(0|(1<<fOpenAtStart))};		// flags
  sRsrcHwDevID,     d{1};							// Hardware device ID.
                
  MinorBaseOS,      l{"_MinorBaseApollo"};			// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthApollo"};		// offset to frame buffer length

  sVidAttributes,   d{(0|(1<<fBuiltInDisplay))};	// built-in display                              <h46>

//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMApollo"};				// offset to OneBitMode parameters

}};


//----------------------------------

resource 'srsc' (1005, "_sRsrc_Vid_GSC_LCD") {{
  sRsrcType,        l{"_VideoTypeGSC"};				// Video type descriptor.
  sRsrcName,        l{"_VideoNameGSC"};				// Offset to video name string.
  sRsrcDrvrDir,     l{"_VidDrvrDirGSC"};			// Offset to driver directory.
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHwDevID,     d{1};							// Hardware device ID.
                
  MinorBaseOS,      l{"_MinorBaseGSC"};				// offset to frame buffer array offset
  MinorLength,      l{"_MinorLengthGSCLCD"};		// offset to frame buffer length

  sVidAttributes,   d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay))}; // built-in display                              <h46>
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     l{"_OBMLCD"};					// offset to OneBitMode parameters
  SecondVidMode,    l{"_TBMLCD"};					// offset to TwoBitMode parameters
  ThirdVidMode,     l{"_FBMLCD"};					// offset to FourBitMode paramters

}};

//----------------------------------

resource 'srsc' (1570, "_sRsrc_Sonic") {{
  sRsrcType,        l{"_NetSonic"};				// Network type descriptor
  sRsrcName,        l{"_NetSonicName"};			// offset to name string
  sRsrcDrvrDir,     l{"_NetSonicDrvrDir"};		// offset to driver directory
  sRsrcFlags,       d{0};						// don't open this device at start
  sRsrcHWDevId,     d{1};						// the first of many onboard Ethernet chips
}};


resource 'srsc' (1575, "_sRsrc_Mace") {{
  sRsrcType,        l{"_NetMace"};				// Network type descriptor
  sRsrcName,        l{"_NetMaceName"};			// offset to name string
  sRsrcDrvrDir,     l{"_NetMaceDrvrDir"};		// offset to driver directory
  sRsrcFlags,       d{0};						// don't open this device at start
  sRsrcHWDevId,     d{2};						// the second of many onboard Ethernet chips
}};


//----------------------------------

resource 'srsc' (1580, "_sRsrc_DoubleExposure") {{
  sRsrcType,        l{"_CPUDblExp"}; 
  sRsrcName,        l{"_CPUDblExpName"}; 
  CPU_FlagsID,      d{CPU_Flags};				// tells that we have a pixel clock
}};

//----------------------------------

resource 'srsc' (1581, "_sRsrc_SCSI_Transport") {{ 
  sRsrcType,        l{"_SCSITransport"}; 
  sRsrcName,        l{"_SCSITransName"}; 
}};


//-------------------------------------------------------------
//               Resource Types
//-------------------------------------------------------------

resource 'styp' (1585, "_VideoTypeRBV")   	{CatDisplay, TypVideo, DrSwApple, DrHwRBV};
resource 'styp' (1590, "_VideoTypeElsie") 	{CatDisplay, TypVideo, DrSwApple, DrHwElsie};
resource 'styp' (1595, "_VideoTypeTim")   	{CatDisplay, TypVideo, DrSwApple, DrHwTim};
resource 'styp' (1600, "_VideoTypeDAFB")  	{CatDisplay, TypVideo, DrSwApple, DrHwDAFB};
resource 'styp' (1605, "_VideoTypeApollo") 	{CatDisplay, TypVideo, DrSwApple, DrHwApollo};
resource 'styp' (1610, "_VideoTypeGSC") 	{CatDisplay, TypVideo, DrSwApple, DrHwGSC};
resource 'styp' (1625, "_NetSonic")       	{CatNetwork, TypEthernet, DrSwApple, DrHwSonic};
resource 'styp' (1630, "_NetMace")  		{CatNetwork, TypEthernet, DrSwApple, DrHwMace};
resource 'styp' (1635, "_CPUDblExp") 		{CatCPU, 	 TypAppleII, DrSwAppleIIe, DrHwDblExp};
resource 'styp' (1636, "_SCSITransport") 	{CatIntBus,  TypXPT, DrSwApple, sRsrc_BdCyclone};

//-------------------------------------------------------------
//               Resource Names
//-------------------------------------------------------------

resource 'cstr' (1640, "_VideoNameRBV")    {"Display_Video_Apple_RBV1"};
resource 'cstr' (1645, "_VideoNameV8")     {"Display_Video_Apple_V8"};

#if !LC930

resource 'cstr' (1650, "_VideoNameTim")    {"Display_Video_Apple_TIM"};
resource 'cstr' (1655, "_VideoNameDAFB")   {"Display_Video_Apple_DAFB"};
resource 'cstr' (1660, "_VideoNameApollo") {"Display_Video_Apple_Apollo"};                
resource 'cstr' (1665, "_VideoNameGSC")    {"Display_Video_Apple_DBLite"};
resource 'cstr' (1680, "_NetSonicName")    {"Network_Ethernet_Apple_Sonic"};
resource 'cstr' (1685, "_NetMaceName")     {"Network_Ethernet_Apple_Mace"};

#endif

resource 'cstr' (1690, "_CPUDblExpName")   {"CPU_AppleII_AppleIIe_FeatureCard"};
resource 'cstr' (1691, "_SCSITransName")   {"IntelligentBus_Transport_Apple"};

//-------------------------------------------------------------
//               Resource Icons
//-------------------------------------------------------------

// The current implementation of the Monitors cdev (i.e., versions 4.x - 7.0) lamely looks at the board
// sRsrc for its icon.  And, for 7.0, Monitors’ current icon-plotting mechanism isn’t very studly.  So,
// I have come up with in interrim solution:  For now I’ll only include 1-bit icons at the CPU (board sResource)
// level.
//

#if !LC930

resource 'node' (1695, "_VidICONCyclone") {{
  include{l{"_VidICONVail"}};
}};

resource 'node' (1700, "_VidICONVail") {{
  include{l{"_VidICONCarnation"}};
}};

resource 'node' (1705, "_VidICONCarnation") {{
  include{l{"_VidICONZydeco"}};
}};

resource 'node' (1710, "_VidICONZydeco") {{
  include{l{"_VidICONEclipse"}};
}};

resource 'node' (1715, "_VidICONEclipse") {{
  include{l{"_VidICONSpike"}};
}};

resource 'node' (1720, "_VidICONSpike") {{
  include{l{"_VidICONWombat"}};
}};

resource 'ICON' (1725, "_VidICONWombat") {
  $"3FFFE000400010004FFF900050005000"
  $"55505000500050005500500050007FFC"
  $"5400400250004FF25000500A5000554A"
  $"4FFFD00A4000550A3FFFD00A0800540A"
  $"3BFF500A2000540A3FFFD00A0000500A"
  $"3FFE500A40014FF24FF9400250053FFC"
  $"5505081050057BDE5405400250057FFE"
  $"500500004FF90000400100003FFE0000"
};

                
resource 'ICON' (1730, "_VidICONTIM") {
  $"00000000000000000000000000000000"
  $"00000000000000000000000000000000"
  $"00000000000000000000000000000000"
  $"00000000000000020000000500000009"
  $"00000012000000240000004800000090"
  $"00000120000002400000048000000900"
  $"00000E0000001C0000DB7E0001FFC200"
  $"7F004200803F420080004200FFFFFC00"
};


resource 'ICON' (1735, "_VidICONApollo") {
  $"0000000007FFFFE00800001008000010"
  $"08FFFF10090000900955509009000090"
  $"09550090090000900950009009000090"
  $"09500090090000900954009009000090"
  $"0900009008FFFF100800001008000010"
  $"08000010080000100800FF1008000010"
  $"08000010080000100800001007FFFFE0"
  $"04000020040000200400002007FFFFE0"
};


//-------------------------------------------------------------
//               Driver Directory
//-------------------------------------------------------------

resource 'ddir' (1740, "_VidDrvrDirRBV") {{
  sMacOS68020, l{"_sRBVDrvrDir"};
}};

resource 'ddir' (1750, "_VidDrvrDirDAFB") {{
  sMacOS68020, l{"_sDAFBDrvrDir"};
}};

resource 'ddir' (1755, "_VidDrvrDirTim") {{
  sMacOS68020, l{"_sTimDrvrDir"};
}};

resource 'ddir' (1760, "_VidDrvrDirApollo") {{
  sMacOS68020, l{"_sApolloDrvrDir"};
}};
                    
resource 'ddir' (1765, "_VidDrvrDirGSC") {{
  sMacOS68020, l{"_sGSCDrvrDir"};
}};
                    
resource 'ddir' (1780, "_NetSonicDrvrDir") {{
  sMacOS68020, l{"_sSonicDrvrDir"};
}};
                    
resource 'ddir' (1785, "_NetMaceDrvrDir") {{
  sMacOS68020, l{"_sMaceDrvrDir"};
}};

#endif
                    
resource 'ddir' (1745, "_VidDrvrDirElsie") {{
  sMacOS68020, l{"_sV8DrvrDir"};
}};

//==================================================================
// Bring in the driver images
//==================================================================

#if !LC930
resource 'node' (570, "_sRBVDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{60};}}};
}};


resource 'node' (571, "_sDAFBDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{40};}}};
}};

resource 'node' (572, "_sTimDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{90};}}};
}};

resource 'node' (573, "_sApolloDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{10};}}};
}};

resource 'node' (574, "_sGSCDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{50};}}};
}};

resource 'node' (578, "_sSonicDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataSonic.rsrc"};
				   type{'decl'};
				     id{1};}}};
}};

resource 'node' (579, "_sMaceDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataMace.rsrc"};
				   type{'decl'};
				     id{1};}}};
}};

#endif

resource 'node' (560, "_sV8DrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{100};}}};
}};

//-------------------------------------------------------------
//               Minor/Major Bases/Lengths
//-------------------------------------------------------------

resource 'node' (1790, "_MinorBaseRBV") {{
	include{l{"_MinorBaseElsie"}};
}};

resource 'node' (1795, "_MinorBaseElsie") {{
	include{l{"_MinorBaseTim"}};
}};

resource 'node' (1800, "_MinorBaseTim") {{
	include{l{"_MinorBaseApollo"}};
}};

resource 'node' (1805, "_MinorBaseApollo") {{
	include{l{"_MinorBaseGSC"}};
}};

resource 'node' (1810, "_MinorBaseGSC") {{
	include{l{"_MinorBaseSonora"}};
}};

resource 'long' (1815, "_MinorBaseSonora")  {defMinorBase};
resource 'long' (1820, "_MinorBaseDAFBStd") {DAFBStdOffset}; 
resource 'long' (1825, "_MinorBaseDAFB2P")  {DAFB2POffset};
resource 'long' (1830, "_MinorBaseDAFB2PW") {DAFB2POffsetW};
resource 'long' (1835, "_MinorBaseDAFBBS")  {DAFBBSOffset};
resource 'long' (1840, "_MinorBaseDAFBBSW") {DAFBBSOffsetW};
resource 'long' (1845, "_MinorBaseDAFBNTSC") {DAFBNTSCOffset};
resource 'long' (1850, "_MinorBaseDAFBNTSCConv") {DAFBNTSCConvOff};
resource 'long' (1855, "_MinorBaseDAFBPAL") {DAFBPALOffset};
resource 'long' (1860, "_MinorBaseDAFBPALW") {DAFBPALOffsetW};
resource 'long' (1865, "_MinorBAseDAFBPALConv") {DAFBPALConvOff};


resource 'long' (1990, "_MinorLengthHRa") {MinorLengthHRa};
resource 'long' (1995, "_MinorLengthHRb") {MinorLengthHRb};
resource 'long' (2000, "_MinorLengthHRc") {MinorLengthHRc};
resource 'long' (2005, "_MinorLengthHRd") {MinorLengthHRd};
resource 'long' (2010, "_MinorLengthFPa") {MinorLengthFPa};
resource 'long' (2015, "_MinorLengthFPb") {MinorLengthFPb};
resource 'long' (2020, "_MinorLengthFPc") {MinorLengthFPc};
resource 'long' (2025, "_MinorLengthSEa") {MinorLengthSEa};
resource 'long' (2030, "_MinorLengthSEb") {MinorLengthSEb};
resource 'long' (2035, "_MinorLengthSEc") {MinorLengthSEc};
resource 'long' (2040, "_MinorLengthSEd") {MinorLengthSEd};
resource 'long' (2045, "_MinorLengthGSa") {MinorLengthGSa};
resource 'long' (2050, "_MinorLengthGSb") {MinorLengthGSb};
resource 'long' (2055, "_MinorLengthGSc") {MinorLengthGSc};
resource 'long' (2060, "_MinorLengthGSd") {MinorLengthGSd};
resource 'long' (2065, "_MinorLength_V8_HRa") {MinorLength_V8_HRa};
resource 'long' (2070, "_MinorLength_V8_HRb") {MinorLength_V8_HRb};
resource 'long' (2075, "_MinorLength_V8_GSa") {MinorLength_V8_GSa};
resource 'long' (2080, "_MinorLength_V8_GSb") {MinorLength_V8_GSb};
resource 'long' (2085, "_MinorLength_V8_VGAa") {MinorLength_V8_VGAa};
resource 'long' (2090, "_MinorLength_V8_VGAb") {MinorLength_V8_VGAb};
resource 'long' (2095, "_MinorLength_V8_A2Ema") {MinorLength_V8_A2Ema};
resource 'long' (2100, "_MinorLength_V8_A2Emb") {MinorLength_V8_A2Emb};
resource 'long' (2105, "_MinorLength_DAFB_FPa") {MinorLength_DAFB_FPa};
resource 'long' (2110, "_MinorLength_DAFB_FPb") {MinorLength_DAFB_FPb};
resource 'long' (2115, "_MinorLength_DAFB_FPbx") {MinorLength_DAFB_FPbx};
resource 'long' (2120, "_MinorLength_DAFB_2Pa") {MinorLength_DAFB_2Pa};
resource 'long' (2125, "_MinorLength_DAFB_2Pb") {MinorLength_DAFB_2Pb};
resource 'long' (2130, "_MinorLength_DAFB_2Pbx") {MinorLength_DAFB_2Pbx};
resource 'long' (2135, "_MinorLength_DAFB_LPa") {MinorLength_DAFB_LPa};
resource 'long' (2140, "_MinorLength_DAFB_LPax") {MinorLength_DAFB_LPax};
resource 'long' (2145, "_MinorLength_DAFB_LPb") {MinorLength_DAFB_LPb;};

resource 'node' (2150, "_MinorLength_DAFB_NTSCconvST") {{
	include{l{"_MinorLength_DAFB_NTSCSTa"}};
}};

resource 'node' (2155, "_MinorLength_DAFB_NTSCSTa") {{
	include{l{"_MinorLength_DAFB_GSa"}};
}};

resource 'long' (2160, "_MinorLength_DAFB_GSa") {MinorLength_DAFB_GSa};
resource 'node' (2165, "_MinorLength_DAFB_NTSCSTax") {{
	include{l{"_MinorLength_DAFB_GSb"}};
}};

resource 'long' (2170, "_MinorLength_DAFB_GSb") {MinorLength_DAFB_GSb};
resource 'long' (2175, "_MinorLength_DAFB_NTSCSTb") {MinorLength_DAFB_NTSCSTb};

resource 'node' (2180, "_MinorLength_DAFB_NTSCconvFF") {{
	include{l{"_MinorLength_DAFB_NTSCFFa"}};
}};

resource 'node' (2185, "_MinorLength_DAFB_NTSCFFa") {{
	include{l{"_MinorLength_DAFB_VGAa"}};
}};

resource 'node' (2190, "_MinorLength_DAFB_VGAa") {{
	include{l{"_MinorLength_DAFB_HRa"}};
}};

resource 'long' (2195, "_MinorLength_DAFB_HRa") {MinorLength_DAFB_HRa};

resource 'node' (2200, "_MinorLength_DAFB_NTSCFFax") {{
	include{l{"_MinorLength_DAFB_VGAax"}};
}};

resource 'node' (2205, "_MinorLength_DAFB_VGAax") {{
	include{l{"_MinorLength_DAFB_HRax"}};
}};

resource 'long' (2210, "_MinorLength_DAFB_HRax") {MinorLength_DAFB_HRax};

resource 'node' (2215, "_MinorLength_DAFB_NTSCFFb") {{
	include{l{"_MinorLength_DAFB_VGAb"}};
}};

resource 'node' (2220, "_MinorLength_DAFB_VGAb") {{
	include{l{"_MinorLength_DAFB_HRb"}};
}};

resource 'long' (2225, "_MinorLength_DAFB_HRb") {MinorLength_DAFB_HRb};
resource 'long' (2230, "_MinorLength_DAFB_PALFFa") {MinorLength_DAFB_PALFFa};
resource 'long' (2235, "_MinorLength_DAFB_PALFFax") {MinorLength_DAFB_PALFFax};
resource 'long' (2240, "_MinorLength_DAFB_PALFFb") {MinorLength_DAFB_PALFFb};
resource 'long' (2245, "_MinorLength_DAFB_PALconvFF") {MinorLength_DAFB_PALconvFF};
resource 'long' (2250, "_MinorLength_DAFB_PALSTa") {MinorLength_DAFB_PALSTa};
resource 'long' (2255, "_MinorLength_DAFB_PALSTax") {MinorLength_DAFB_PALSTax};
resource 'long' (2260, "_MinorLength_DAFB_PALSTb") {MinorLength_DAFB_PALSTb};
resource 'long' (2265, "_MinorLength_DAFB_PALconvST") {MinorLength_DAFB_PALconvST};
resource 'long' (2270, "_MinorLength_DAFB_SVGAa") {MinorLength_DAFB_SVGAa};
resource 'long' (2275, "_MinorLength_DAFB_SVGAax") {MinorLength_DAFB_SVGAax};
resource 'long' (2280, "_MinorLength_DAFB_SVGAb") {MinorLength_DAFB_SVGAb};
resource 'long' (2285, "_MinorLength_DAFB_19a") {MinorLength_DAFB_19a};
resource 'long' (2290, "_MinorLength_DAFB_19b") {MinorLength_DAFB_19b};
resource 'long' (2295, "_MinorLength_DAFB_19bx") {MinorLength_DAFB_19bx};
resource 'long' (2305, "_MinorLengthGSCLCD") {MinorLengthGSCLCD};
resource 'long' (2310, "_MinorLengthLCD") {MinorLengthLCD};
resource 'long' (2315, "_MinorLengthApollo") {MinorLengthApollo};

//-------------------------------------------------------------
//               Video Parameters Directory
//-------------------------------------------------------------
//
//   This directory holds references to data blocks containing the hardware
//   setup parameters for the various modes and configurations of the 
//   hardware.
//
//   DAFB
//   ----
//   Here's the organization of the data - there's a block for each type of
//   display.  The 'a' (reduced functionality) and 'b' (full functionality)
//   entries may point at the same block of parameters, since the 'b' set
//   is a superset of the 'a' group for these current configurations.  Each
//   block has a bunch of parameters which are device specific, the format
//   of which is known only to the consumers.  For DAFB, this includes
//   DAFB setup info, Swatch info, ACDC info, National clock chip info, and
//   screen clearing information (skip factor, longs/row, number of rows).  
//   There is one set of this information for each of the supported screen depths.  
//
//   For more detailed information about what all the data in this section
//   actually means, the following ERS should be consulted:
//
//       1) AC842, 9/12/88 -- the ACDC ERS, Apple Computer, Inc.
//       2) AC842A, Risc Products Gropu, Apple Computer, Inc.
//       3) DP8531/32/33 Programmable Clock Generator, 4/27/89 -- National ERS,
//           National Semiconductor.
//       4) DAFB, Eclipse Direct Access Frame Buffer Controller Specification -- DAFB ERS,
//           Apple Computer, Inc.
//       5) Wombat/djMEMC ERS?
//
//   Sonora
//   ------
//   Sonora is much more simple than DAFB.  The first set of parameteres are for the
//   Omega; they are used to generate the correct dot-clock per display.  The next
//   parameter is the value used to tell Sonora which display is attached.  Following
//   that is a set of parameters that says which bit-depths are valid in the various
//   vRAM configurations.  Finally, there is a set of parameters that describes the
//   number of rows and the rowbytes per bit-depth per display.
//
//   Civic
//   -----
//   <fau to fill this in>
//-------------------------------------------------------------

resource 'list' (2740, "_VidParmDir_DAFB") {{

  sRsrc_Vid_DAFB_19a, l{"_sVidParms_DAFB_19"};							// 19" Display
  sRsrc_Vid_DAFB_19b, l{"_sVidParms_DAFB_19"}; 
                
  sRsrc_Vid_DAFB_FPa, l{"_sVidParms_DAFB_FP"};							// Portrait
  sRsrc_Vid_DAFB_FPb, l{"_sVidParms_DAFB_FP"}; 

  sRsrc_Vid_DAFB_GSa, l{"_sVidParms_DAFB_GS"};							// Rubik
  sRsrc_Vid_DAFB_GSb, l{"_sVidParms_DAFB_GS"}; 

  sRsrc_Vid_DAFB_2Pa, l{"_sVidParms_DAFB_2P"};							// 2-Page (Kong)
  sRsrc_Vid_DAFB_2Pb, l{"_sVidParms_DAFB_2P"}; 

  sRsrc_Vid_DAFB_LPa, l{"_sVidParms_DAFB_LP"};							// Goldfish
  sRsrc_Vid_DAFB_LPb, l{"_sVidParms_DAFB_LP"}; 

  sRsrc_Vid_DAFB_HRa, l{"_sVidParms_DAFB_HR"};							// High-Res (Mono & RGB)
  sRsrc_Vid_DAFB_HRb, l{"_sVidParms_DAFB_HR"}; 

  sRsrc_Vid_DAFB_VGAa, l{"_sVidParms_DAFB_VGA"};						// VGA
  sRsrc_Vid_DAFB_VGAb, l{"_sVidParms_DAFB_VGA"}; 
                
  sRsrc_Vid_DAFB_RGBFPa, l{"_sVidParms_DAFB_FP"};						// RGB Portrait
  sRsrc_Vid_DAFB_RGBFPb, l{"_sVidParms_DAFB_FP"}; 

  sRsrc_Vid_DAFB_RGB2Pa, l{"_sVidParms_DAFB_2P"};						// RGB 2-Page (Vesuvio)
  sRsrc_Vid_DAFB_RGB2Pb, l{"_sVidParms_DAFB_2P"}; 

  sRsrc_Vid_DAFB_NTSCSTa, l{"_sVidParms_DAFB_NTSCST"};					// NTSC ST
  sRsrc_Vid_DAFB_NTSCSTb, l{"_sVidParms_DAFB_NTSCST"}; 

  sRsrc_Vid_DAFB_NTSCFFa, l{"_sVidParms_DAFB_NTSCFF"};					// NTSC FF
  sRsrc_Vid_DAFB_NTSCFFb, l{"_sVidParms_DAFB_NTSCFF"}; 

  sRsrc_Vid_DAFB_PALSTa, l{"_sVidParms_DAFB_PALST"};					// PAL ST
  sRsrc_Vid_DAFB_PALSTb, l{"_sVidParms_DAFB_PALST"}; 

  sRsrc_Vid_DAFB_PALFFa, l{"_sVidParms_DAFB_PALFF"};					// PAL FF
  sRsrc_Vid_DAFB_PALFFb, l{"_sVidParms_DAFB_PALFF"}; 
                
  sRsrc_Vid_DAFB_NTSCconvSTx, l{"_sVidParms_DAFB_NTSCconvST"};			// NTSC ST convolved
  sRsrc_Vid_DAFB_NTSCconvST, l{"_sVidParms_DAFB_NTSCconvST"};			// NTSC ST convolved
  sRsrc_Vid_DAFB_NTSCconvFFx, l{"_sVidParms_DAFB_NTSCconvFF"};			// NTSC FF convolved
  sRsrc_Vid_DAFB_NTSCconvFF, l{"_sVidParms_DAFB_NTSCconvFF"};			// NTSC FF convolved
                
  sRsrc_Vid_DAFB_PALconvSTx, l{"_sVidParms_DAFB_PALconvST"};			// PAL ST convolved
  sRsrc_Vid_DAFB_PALconvST, l{"_sVidParms_DAFB_PALconvST"};				// PAL ST convolved
  sRsrc_Vid_DAFB_PALconvFFx, l{"_sVidParms_DAFB_PALconvFF"};			// PAL FF convolved
  sRsrc_Vid_DAFB_PALconvFF, l{"_sVidParms_DAFB_PALconvFF"};				// PAL FF convolved

  sRsrc_Vid_DAFB_HRax, l{"_sVidParms_DAFB_HR"};							// HiRes 16bpp
  sRsrc_Vid_DAFB_HRbx, l{"_sVidParms_DAFB_HR"};							// HiRes 16/32bpp
                
  sRsrc_Vid_DAFB_VGAax, l{"_sVidParms_DAFB_VGA"};						// VGA 16bpp
  sRsrc_Vid_DAFB_VGAbx, l{"_sVidParms_DAFB_VGA"};						// VGA 16/32bpp
                
  sRsrc_Vid_DAFB_LPax, l{"_sVidParms_DAFB_LP"};							// GoldFish 16bpp
  sRsrc_Vid_DAFB_LPbx, l{"_sVidParms_DAFB_LP"};							// GoldFish 16/32bpp
                
  sRsrc_Vid_DAFB_SVGAax, l{"_sVidParms_DAFB_SVGA"};						// SuperVGA
  sRsrc_Vid_DAFB_SVGAbx, l{"_sVidParms_DAFB_SVGA"}; 
  sRsrc_Vid_DAFB_SVGAa, l{"_sVidParms_DAFB_SVGA"};						// 
  sRsrc_Vid_DAFB_SVGAb, l{"_sVidParms_DAFB_SVGA"};						// 
                
  sRsrc_Vid_DAFB_GSx, l{"_sVidParms_DAFB_GS"};							// Rubik 16/32bpp
  sRsrc_Vid_DAFB_RGBFPbx, l{"_sVidParms_DAFB_FP"};						// RGBPort 16bpp
  sRsrc_Vid_DAFB_GSz, l{"_sVidParms_DAFB_GS"};							// Rubik 16bpp
  sRsrc_Vid_DAFB_RGB2Pbx, l{"_sVidParms_DAFB_2P"};						// Vesuvio 16bpp
                                
  sRsrc_Vid_DAFB_NTSCSTax, l{"_sVidParms_DAFB_NTSCST"};					// NTSC ST 16bpp
  sRsrc_Vid_DAFB_NTSCSTbx, l{"_sVidParms_DAFB_NTSCST"};					// NTSC ST 16/32bpp
  sRsrc_Vid_DAFB_NTSCFFax, l{"_sVidParms_DAFB_NTSCFF"};					// NTSC FF 16bpp
  sRsrc_Vid_DAFB_NTSCFFbx, l{"_sVidParms_DAFB_NTSCFF"};					// NTSC FF 16/32bpp
                
  sRsrc_Vid_DAFB_PALSTax, l{"_sVidParms_DAFB_PALST"};					// PAL ST 16bpp
  sRsrc_Vid_DAFB_PALSTbx, l{"_sVidParms_DAFB_PALST"};					// PAL ST 16/32bpp
  sRsrc_Vid_DAFB_PALFFax, l{"_sVidParms_DAFB_PALFF"};					// PAL FF 16bpp
  sRsrc_Vid_DAFB_PALFFbx, l{"_sVidParms_DAFB_PALFF"};					// PAL FF 16/32bpp
                                
  sRsrc_Vid_DAFB_19bx, l{"_sVidParms_DAFB_19"};							// 19" 16bpp             
                
  pSRsrc_Vid_DAFB_2PRdRGB, l{"_sVidParms_DAFB_2PRdRGB"};				// Radius ColorTPD
  pSRsrc_Vid_DAFB_2PRdMono, l{"_sVidParms_DAFB_2PRdMono"};				// Radius MonoTPD                
                
}};



// This #define's are a stopgap measure for now.
#define firstVidMode  0x80
#define secondVidMode 0x81
#define thirdVidMode  0x82
#define fourthVidMode 0x83
#define fifthVidMode  0x84
#define sixthVidMode  0x85



//
// Full Page Display parameters
//
resource 'node' (2755, "_sVidParms_DAFB_FP") {{
  blocksize{};                                               // block size        

// Clock chip parms
//
  bytes{{$0E;$07;$00;$00;$0B;$00;$00;$00;$00;$02;}};         // 8531 chip parms.
  words{{$2C05;$01A0;$7E00;}};                               // 8534 chip parms.

// Misc params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BFP-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$072C;$072A;$0004;$0009;$0058;$0724;$072A;}};       // Static Swatch Params.

// One bit mode parameters
//
  words{{$0080;$060E;$0010;}};                               // DAFB parms
  words{{$0176;$00D0;$0014;$019F;$0027;$002D;}};             // Dynamic Swatch parms
  words{{$003F;$004B;$018B;$019E;$001D;}};
  words{{$00A0;}};                                           // ACDC parms
  words{{$001A;$0048;$0188;}};                               // AMD params
                
  words{{((defmBounds_RFP*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_RFP*1)/8));}};            // SkipFactor

// Two bit mode parameters
//
  words{{$0080;$0606;$0010;}};                               // DAFB parms
  words{{$0176;$00D0;$0014;$019F;$0027;$002D;}};             // Dynamic Swatch parms
  words{{$003F;$004B;$018B;$019E;$0035;}};
  words{{$00A8;}};                                           // ACDC parms
  words{{$0032;$0048;$0188;}};                               // AMD params
                
  words{{((defmBounds_RFP*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_RFP*2)/8));}};            // SkipFactor

// Four bit mode parameters
//
  words{{$0080;$0602;$0010;}};                               // DAFB parms
  words{{$0176;$00D0;$0014;$019F;$0027;$002D;}};             // Dynamic Swatch parms
  words{{$003F;$004B;$018B;$019E;$0041;}};
  words{{$00B0;}};                                           // ACDC parms
  words{{$003E;$0048;$0188;}};                               // AMD params
                
  words{{((defmBounds_RFP*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_RFP*4)/8));}};            // SkipFactor

// Eight bit mode parameters
//
  words{{$0100;$0600;$0010;}};                               // DAFB parms
  words{{$0176;$00D0;$0014;$019F;$0027;$002D;}};             // Dynamic Swatch parms
  words{{$003F;$004B;$018B;$019E;$0047;}};
  words{{$00B8;}};                                           // ACDC parms
  words{{$0044;$0048;$0188;}};                               // AMD params
                
  words{{((defmBounds_RFP*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RFP*8)/8));}};           // SkipFactor

// Sixteen bit mode parameters

  words{{$0200;$06FF;$0011;}};                               // DAFB parms
  words{{$0176;$00D0;$0014;$019F;$0027;$002D;}};             // Dynamic Swatch parms
  words{{$003F;$004B;$018B;$019E;$004A;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$0047;$0048;$0188;}};                               // AMD params
                
  words{{((defmBounds_RFP*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RFP*16)/8));}};          // SkipFactor
}};



//
// 19" DAFB parameters
//
resource 'node' (2760, "_sVidParms_DAFB_19") {{
  blocksize{};                                               // block size
                
// Clock chip parms
  bytes{{$08;$0F;$00;$00;$0F;$01;$00;$00;$00;$01;}};         // 8531 chip parms
  words{{$3C04;$0040;$0400;}};                               // 8534 chip parms.

// Misc params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_B19-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$0648;$0646;$0004;$0009;$0040;$0640;$0644;}};       // Static Swatch params.
  
// One bit mode parameters
//
  words{{$0080;$0606;$0030;}};                               // DAFB parms
  words{{$012A;$00A5;$000C;$014B;$0017;$001A;}};             // Dynamic Swatch parms
  words{{$0023;$003F;$013F;$014A;$0029;}};
  words{{$00C0;}};                                           // ACDC parms
  words{{$0029;$003F;$013F;}};                               // AMD params

  words{{((defmBounds_R19*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_R19*1)/8));}};            // SkipFactor
                
// Two bit mode parameters
//
  words{{$0080;$0602;$0030;}};                               // DAFB parms
  words{{$012A;$00A5;$000C;$014B;$0017;$001A;}};             // Dynamic Swatch parms
  words{{$0023;$003F;$013F;$014A;$0035;}};
  words{{$00C8;}};                                           // ACDC parms
  words{{$0035;$003F;$013F;}};                               // AMD params

  words{{((defmBounds_R19*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_R19*2)/8));}};            // SkipFactor
                
// Four bit mode parameters
//
  words{{$0080;$0600;$0030;}};                               // DAFB parms
  words{{$012A;$00A5;$000C;$014B;$0017;$001A;}};             // Dynamic Swatch parms
  words{{$0023;$003F;$013F;$014A;$003B;}};
  words{{$00D0;}};                                           // ACDC parms
  words{{$003B;$003F;$013F;}};                               // AMD params

  words{{((defmBounds_R19*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_512_RB-((defmBounds_R19*4)/8));}};            // SkipFactor
                
// Eight bit mode parameters
//
  words{{$0100;$06FF;$0030;}};                               // DAFB parms
  words{{$012A;$00A5;$000C;$014B;$0017;$001A;}};             // Dynamic Swatch parms
  words{{$0023;$003F;$013F;$014A;$003F;}};
  words{{$00D8;}};                                           // ACDC parms
  words{{$003F;$003F;$013F;}};                               // AMD params

  words{{((defmBounds_R19*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_R19*8)/8));}};           // SkipFactor
                
// Sixteen bit mode parameters
//
  words{{$0200;$06FF;$0031;}};                               // DAFB parms
  words{{$0254;$014A;$0018;$0297;$002F;$0035;}};             // Dynamic Swatch parms
  words{{$0047;$0081;$0281;$0296;$0080;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$0080;$0081;$0281;}};                               // AMD params

  words{{((defmBounds_R19*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_R19*16)/8));}};          // SkipFactor
}};



//
// Rubik parameters
//
resource 'node' (2765, "_sVidParms_DAFB_GS") {{
  blocksize{};                                               // block size        

// Clock chip parms
  bytes{{$0E;$05;$00;$00;$0F;$00;$00;$00;$00;$03;}};         // 8531 chip parms
  words{{$1C05;$40A0;$7A00;}};                               // 8534 chip parms

// Misc params
//
  bytes{{SixthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BGS-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$032E;$032C;$0004;$0009;$002A;$032A;$032B;}};       // Static Swatch Params.

// One bit mode parameters
//
  words{{$0100;$061E;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Dynamic Swatch parms
  words{{$004F;$0068;$0268;$027E;$000A;}};
  words{{$0080;}};                                           // ACDC parms
  words{{$0005;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RGS*1)/8));}};           // SkipFactor

// Two bit mode parameters
//
  words{{$0100;$060E;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Dynamic Swatch parms
  words{{$004F;$0068;$0268;$027E;$003A;}};
  words{{$0088;}};                                           // ACDC parms
  words{{$0035;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RGS*2)/8));}};           // SkipFactor

// Four bit mode parameters
//
  words{{$0100;$0606;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Dynamic Swatch parms
  words{{$004F;$0068;$0268;$027E;$0052;}};
  words{{$0090;}};                                           // ACDC parms
  words{{$004D;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RGS*4)/8));}};           // SkipFactor

// Eight bit mode parameters
//
  words{{$0100;$0602;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Dynamic Swatch parms
  words{{$004F;$0068;$0268;$027E;$005E;}};
  words{{$0098;}};                                           // ACDC parms
  words{{$0059;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RGS*8)/8));}};           // SkipFactor

// Sixteen bit mode parameters
//
  words{{$0100;$0600;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Swatch parms
  words{{$004F;$0063;$0263;$027E;$005F;}};
  words{{$009E;}};                                           // ACDC parms
  words{{$005F;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RGS*16)/8));}};          // SkipFactor

// Thirty-Two bit mode parameters
//
  words{{$0200;$06FF;$0050;}};                               // DAFB parms
  words{{$025E;$0140;$0010;$027F;$001F;$002B;}};             // Dynamic Swatch parms
  words{{$004F;$0069;$0269;$027E;$0069;}};
  words{{$009C;}};                                           // ACDC parms
  words{{$0063;$0063;$0263;}};                               // AMD params

  words{{((defmBounds_RGS*32)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RGS*32)/8));}};          // SkipFactor
}};



//
// Two-Page Display parameters
//
resource 'node' (2770, "_sVidParms_DAFB_2P") {{
  blocksize{};                                               // block size        

// Clock chip parms
//
  bytes{{$0E;$0B;$00;$00;$06;$02;$00;$00;$00;$00;}};         // 8531 chip parms
  words{{$1C04;$0040;$1400;}};                               // 8534 chip parms

// Misc params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      // MaxMode a,b
  bytes{{FourthVidMode-FirstVidMode;-1;}};                   // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_B2P-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$0726;$0724;$0004;$0009;$0052;$071E;$0722;}};       // Static Swatch Params. 

// One bit mode parameters
//
  words{{$0090;$0406;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$016B;$001F;$0022;}};             // Dynamic Swatch parms
  words{{$002B;$0040;$0160;$016A;$002A;}};
  words{{$00C0;}};                                           // ACDC parms
  words{{$0029;$003F;$015F;}};                               // AMD params

  words{{((defmBounds_R2P*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*1)/8));}};            // SkipFactor

// Two bit mode parameters
//
  words{{$0090;$0402;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$016B;$001F;$0022;}};             // Dynamic Swatch parms
  words{{$002B;$0040;$0160;$016A;$0036;}};
  words{{$00C8;}};                                           // ACDC parms
  words{{$0035;$003F;$015F;}};                               // AMD params

  words{{((defmBounds_R2P*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*2)/8));}};            // SkipFactor

// Four bit mode parameters
//
  words{{$0090;$0400;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$016B;$001F;$0022;}};             // Dynamic Swatch parms
  words{{$002B;$0040;$0160;$016A;$003C;}};
  words{{$00D0;}};                                           // ACDC parms
  words{{$003B;$003F;$015F;}};                               // AMD params

  words{{((defmBounds_R2P*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*4)/8));}};            // SkipFactor

// Eight bit mode parameters
//
  words{{$0120;$4FF;$0011;}};                                // DAFB parms
  words{{$014A;$00B6;$0010;$016B;$001F;$0022;}};             // Dynamic Swatch parms
  words{{$002B;$0040;$0160;$016A;$003F;}};
  words{{$00D8;}};                                           // ACDC parms
  words{{$003F;$003F;$015F;}};                               // AMD params

  words{{((defmBounds_R2P*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1152_RB-((defmBounds_R2P*8)/8));}};           // SkipFactor

// Sixteen bit mode parameters
//
  words{{$0240;$4FF;$0011;}};                                // DAFB parms
  words{{$0294;$016C;$0020;$02D7;$003F;$0045;}};             // Dynamic Swatch parms
  words{{$0057;$0087;$02C7;$02D6;$0086;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$0080;$0081;$02C1;}};                               // AMD params

  words{{((defmBounds_R2P*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2304_RB-((defmBounds_R2P*16)/8));}};          // SkipFactor
}};



//
// Radius ColorTPD parameters
//
resource 'node' (2775, "_sVidParms_DAFB_2PRdRGB") {{
  blocksize{};                                               // block size     

// Clock chip parms
//
  bytes{{$0E;$0B;$00;$00;$06;$02;$00;$00;$00;$00;}};         // 8531 chip parms
  words{{$1C04;$0040;$1400;}};                               // 8534 chip parms

// Misc params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      // MaxMode a,b
  bytes{{FourthVidMode-FirstVidMode;-1;}};                   // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_B2P-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$0720;$071E;$0004;$0009;$0046;$0712;$071C;}};       // Static Swatch parms.

// One bit mode parameters
//
  words{{$0090;$0406;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0045;}};
  words{{$00C0;}};                                           // ACDC parms
  words{{$0045;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*1)/8));}};            // SkipFactor

// Two bit mode parameters
//
  words{{$0090;$0402;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dyamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0051;}};
  words{{$00C8;}};                                           // ACDC parms
  words{{$0051;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*2)/8));}};            // SkipFactor

// Four bit mode parameters
//
  words{{$0090;$0400;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0057;}};
  words{{$00D0;}};                                           // ACDC parms
  words{{$0057;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*4)/8));}};            // SkipFactor

// Eight bit mode parameters
//
  words{{$0120;$04FF;$0011;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$005A;}};
  words{{$00D8;}};                                           // ACDC parms
  words{{$005B;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1152_RB-((defmBounds_R2P*8)/8));}};           // SkipFactor
                
// Sixteen bit mode parameters
//
  words{{$0240;$04FF;$0011;}};                               // DAFB parms
  words{{$0294;$016C;$0020;$02FF;$0057;$005D;}};             // Dynamic Swatch parms
  words{{$006F;$00B9;$02F9;$02FE;$00B8;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$00B8;$00B9;$02F9;}};                               // AMD params

  words{{((defmBounds_R2P*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2304_RB-((defmBounds_R2P*16)/8));}};          // SkipFactor
}};



//
// Radius MonoTPD parameters
//
resource 'node' (2780, "_sVidParms_DAFB_2PRdMono") {{
  blocksize{};                                               // block size       

// Clock chip parms
//
  bytes{{$0E;$0B;$00;$00;$06;$02;$00;$00;$00;$00;}};         // 8531 chip parms
  words{{$1C04;$0040;$1400;}};                               // 8534 chip parms

// Misc params
//
  bytes{{ThirdVidMode-FirstVidMode;FourthVidMode-FirstVidMode;}}; // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_B2P-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$0730;$072E;$001C;$0021;$0056;$0722;$072C;}};       // Static Swatch parms

// One bit mode parameters
//
  words{{$0090;$0406;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0045;}};
  words{{$00C0;}};                                           // ACDC parms
  words{{$0045;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*1)/8));}};            // SkipFactor

// Two bit mode parameters
//
  words{{$0090;$0402;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0051;}};
  words{{$00C8;}};                                           // ACDC parms
  words{{$0051;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*2)/8));}};            // SkipFactor

// Four bit mode parameters
//
  words{{$0090;$0400;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$0057;}};
  words{{$00D0;}};                                           // ACDC parms
  words{{$0057;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_576_RB-((defmBounds_R2P*4)/8));}};            // SkipFactor

// Eight bit mode parameters
//
  words{{$0120;$04FF;$0010;}};                               // DAFB parms
  words{{$014A;$00B6;$0010;$017F;$002B;$002E;}};             // Dynamic Swatch parms
  words{{$0037;$005B;$017B;$017E;$005B;}};
  words{{$00D8;}};                                           // ACDC parms
  words{{$005B;$005B;$017B;}};                               // AMD params

  words{{((defmBounds_R2P*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1152_RB-((defmBounds_R2P*8)/8));}};           // SkipFactor
}};



//
// Goldfish Display parameters
//
resource 'node' (2785, "_sVidParms_DAFB_LP") {{
  blocksize{};                                               // block size        

// Clock chip parms
//
  bytes{{$0E;$07;$00;$00;$0B;$00;$00;$00;$00;$02;}};         // 8531 chip parms.
  words{{$2C05;$01A0;$7E00;}};                               // 8534 chip parms.

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{FifthVidMode-FirstVidMode;-1;}};                    // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BLP-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$0536;$0534;$0004;$0009;$0052;$0532;$0533;}};       // Static Swatch Parms.

// One bit mode parameters
//
  words{{$00D0;$060E;$0010;}};                               // DAFB parms
  words{{$021E;$0120;$0010;$023F;$001F;$0025;}};             // Dynamic Swatch parms
  words{{$0037;$008B;$022B;$023E;$005D;}};
  words{{$00A0;}};                                           // ACDC parms
  words{{$005B;$0089;$0229;}};                               // AMD params
                
  words{{((defmBounds_RLP*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RLP*1)/8));}};            // SkipFactor

// Two bit mode parameters
//
  words{{$00D0;$0606;$0010;}};                               // DAFB parms
  words{{$021E;$0120;$0010;$023F;$001F;$0025;}};             // Dynamic Swatch parms
  words{{$0037;$008B;$022B;$023E;$0075;}};
  words{{$00A8;}};                                           // ACDC parms
  words{{$0073;$0089;$0229;}};                               // AMD params
                
  words{{((defmBounds_RLP*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RLP*2)/8));}};            // SkipFactor

// Four bit mode parameters
//
  words{{$00D0;$0602;$0010;}};                               // DAFB parms
  words{{$021E;$0120;$0010;$023F;$001F;$0025;}};             // Dynamic Swatch parms
  words{{$0037;$008B;$022B;$023E;$0081;}};
  words{{$00B0;}};                                           // ACDC parms
  words{{$007F;$0089;$0229;}};                               // AMD params
                
  words{{((defmBounds_RLP*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RLP*4)/8));}};            // SkipFactor

// Eight bit mode parameters
//
  words{{$00D0;$0600;$0010;}};                               // DAFB parms
  words{{$021E;$0120;$0010;$023F;$001F;$0025;}};             // Dynamic Swatch parms
  words{{$0037;$008B;$022B;$023E;$0087;}};
  words{{$00B8;}};                                           // ACDC parms
  words{{$0085;$0089;$0229;}};                               // AMD params
                
  words{{((defmBounds_RLP*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RLP*8)/8));}};            // SkipFactor

// Sixteen bit mode parameters
//
  words{{$01A0;$06FF;$0011;}};                               // DAFB parms
  words{{$021E;$0120;$0010;$023F;$001F;$0025;}};             // Dynamic Swatch parms
  words{{$0037;$0089;$0229;$023E;$0088;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$0089;$0089;$0229;}};                               // AMD params
                
  words{{((defmBounds_RLP*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1664_RB-((defmBounds_RLP*16)/8));}};          // SkipFactor

// Thirty-Two bit mode parameters
//
  words{{$0340;$0000;$0011;}};                               // DAFB parms
  words{{$043E;$0240;$0020;$047F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0119;$0459;$047E;$0118;}};
  words{{$003C;}};                                           // ACDC parms
  words{{$0113;$0113;$0453;}};                               // AMD params

  words{{((defmBounds_RLP*32)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_3328_RB-((defmBounds_RLP*32)/8));}};          // SkipFactor
}};



//
// Hi-Res Display parameters
//
resource 'node' (2790, "_sVidParms_DAFB_HR") {{
  blocksize{};                                               // block size        
                
// Clock chip parms
//
  bytes{{$0E;$0F;$00;$00;$05;$01;$00;$00;$00;$03;}};         // 8531 parms
  words{{$1C05;$8190;$6700;}};                               // 8534 parms

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BHR-1;}};                                // ActiveHeight

// Static DAFB params
//
  words{{$041A;$0418;$0004;$0009;$0052;$0412;$0416;}};       // Static Swatch parms

// One bit mode parameters
//
  words{{$0100;$061E;$0030;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0098;$0318;$035E;$003A;}};
  words{{$0080;}};                                           // ACDC parms
  words{{$0035;$0093;$0313;}};                               // AMD params
                
  words{{((defmBounds_RHR*1)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RHR*1)/8));}};           // SkipFactor

// Two bit mode parameters
//
  words{{$0100;$060E;$0030;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0098;$0318;$035E;$006A;}};
  words{{$0088;}};                                           // ACDC parms
  words{{$0065;$0093;$0313;}};                               // AMD params

  words{{((defmBounds_RHR*2)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RHR*2)/8));}};           // SkipFactor

// Four bit mode parameters
//
  words{{$0100;$0606;$0030;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0098;$0318;$035E;$0082;}};
  words{{$0090;}};                                           // ACDC parms
  words{{$007D;$0093;$0313;}};                               // AMD params

  words{{((defmBounds_RHR*4)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RHR*4)/8));}};           // SkipFactor

// Eight bit mode parameters
//
  words{{$0100;$0602;$0030;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0098;$0318;$035E;$008E;}};
  words{{$0098;}};                                           // ACDC parms
  words{{$0089;$0093;$0313;}};                               // AMD params

  words{{((defmBounds_RHR*8)/64)-1;}};                       // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RHR*8)/8));}};           // SkipFactor

// Sixteen bit mode parameters
//
  words{{$0200;$0600;$0030;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0093;$0313;$035E;$008F;}};
  words{{$009E;}};                                           // ACDC parms
  words{{$008F;$0093;$0313;}};                               // AMD params

  words{{((defmBounds_RHR*16)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RHR*16)/8));}};          // SkipFactor

// Thirty-Two bit mode parameters
//
  words{{$0400;$06FF;$0032;}};                               // DAFB parms
  words{{$031E;$01B0;$0020;$035F;$003F;$004B;}};             // Dynamic Swatch parms
  words{{$006F;$0099;$0319;$035E;$0099;}};
  words{{$009C;}};                                           // ACDC parms
  words{{$0093;$0093;$0313;}};                               // AMD params

  words{{((defmBounds_RHR*32)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_4096_RB-((defmBounds_RHR*32)/8));}};          // SkipFactor
}};



//
// VGA Display parameters
//
resource 'node' (2795, "_sVidParms_DAFB_VGA") {{
  blocksize{};                                               // block size        

// Clock chip parms
//
  bytes{{$0F;$01;$01;$00;$09;$03;$00;$00;$00;$02;}};         // 8531 chip parms
  words{{$2C05;$8130;$3F00;}};                               // 8534 chip parms

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BVGA-1;}};                               // ActiveHeight

// Static DAFB params
//
  words{{$041A;$0418;$0002;$0007;$0044;$0404;$0408;}};       // Static Swatch parms.

// One bit mode parameters
//
  words{{$0100;$061E;$0030;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0088;$0308;$031E;$002A;}};
  words{{$0080;}};                                           // ACDC parms
  words{{$0025;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*1)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RVGA*1)/8));}};          // SkipFactor

// Two bit mode parameters
//
  words{{$0100;$060E;$0030;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0088;$0308;$031E;$005A;}};
  words{{$0088;}};                                           // ACDC parms
  words{{$0055;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*2)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RVGA*2)/8));}};          // SkipFactor

// Four bit mode parameters
//
  words{{$0100;$0606;$0030;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0088;$0308;$031E;$0072;}};
  words{{$0090;}};                                           // ACDC parms
  words{{$006D;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*4)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RVGA*4)/8));}};          // SkipFactor

// Eight bit mode parameters
//
  words{{$0100;$0602;$0030;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0088;$0308;$031E;$007E;}};
  words{{$0098;}};                                           // ACDC parms
  words{{$0079;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*8)/64)-1;}};                      // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RVGA*8)/8));}};          // SkipFactor

// Sixteen bit mode parameters
//
  words{{$0200;$0600;$0030;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0083;$0303;$031E;$007F;}};
  words{{$009E;}};                                           // ACDC parms
  words{{$007F;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*16)/64)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RVGA*16)/8));}};         // SkipFactor

// Thirty-Two bit mode parameters
//
  words{{$0400;$06FF;$0032;}};                               // DAFB parms
  words{{$026E;$0190;$0030;$031F;$005F;$006B;}};             // Dynamic Swatch parms
  words{{$007E;$0089;$0309;$031E;$0089;}};
  words{{$009C;}};                                           // ACDC parms
  words{{$0083;$0083;$0303;}};                               // AMD params

  words{{((defmBounds_RVGA*32)/64)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_4096_RB-((defmBounds_RVGA*32)/8));}};         // SkipFactor
}};



//
// SuperVGA Display parameters
//
resource 'node' (2800, "_sVidParms_DAFB_SVGA") {{
  blocksize{};                                               // block size
                
// Clock chip parms
//
  bytes{{$0C;$0F;$00;$00;$03;$02;$00;$00;$00;$02;}};         // 8531 chip parms
  words{{$1C04;$80A0;$3600;}};                               // 8534 chip parms

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{FifthVidMode-FirstVidMode;-1;}};                    // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BSVGA-1;}};                              // ActiveHeight

// Static DAFB params
//
  words{{$04E8;$04E6;$001A;$001F;$0028;$04D8;$04DC;}};       // Static Swatch parms

// One bit mode parameters
//
  words{{$00D0;$060E;$0030;}};                               // DAFB parms
  words{{$01C6;$0100;$001C;$01FF;$0037;$003D;}};             // Dynamic Swatch parms
  words{{$004F;$0063;$01F3;$01FE;$0035;}};
  words{{$00A0;}};                                           // ACDC parms
  words{{$0032;$0060;$01F0;}};                               // AMD params
            
  words{{((defmBounds_RSVGA*1)/32)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RSVGA*1)/8));}};          // SkipFactor

// Two bit mode parameters
//
  words{{$00D0;$0606;$0030;}};                               // DAFB parms
  words{{$01C6;$0100;$001C;$01FF;$0037;$003D;}};             // Dynamic Swatch parms
  words{{$004F;$0063;$01F3;$01FE;$004D;}};
  words{{$00A8;}};                                           // ACDC parms
  words{{$004A;$0060;$01F0;}};                               // AMD params

  words{{((defmBounds_RSVGA*2)/32)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RSVGA*2)/8));}};          // SkipFactor

// Four bit mode parameters
//
  words{{$00D0;$0602;$0030;}};                               // DAFB parms
  words{{$01C6;$0100;$001C;$01FF;$0037;$003D;}};             // Dynamic Swatch parms
  words{{$004F;$0063;$01F3;$01FE;$0059;}};
  words{{$00B0;}};                                           // ACDC parms
  words{{$0056;$0060;$001F0;}};                              // AMD params

  words{{((defmBounds_RSVGA*4)/32)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RSVGA*4)/8));}};          // SkipFactor

// Eight bit mode parameters
//
  words{{$00D0;$0600;$0030;}};                               // DAFB parms
  words{{$01C6;$0100;$001C;$01FF;$0037;$003D;}};             // Dynamic Swatch parms
  words{{$004F;$0063;$01F3;$01FE;$005F;}};
  words{{$00B8;}};                                           // ACDC parms
  words{{$005C;$0060;$01F0;}};                               // AMD params

  words{{((defmBounds_RSVGA*8)/32)-1;}};                     // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RSVGA*8)/8));}};          // SkipFactor

// Sixteen bit mode parameters
//
  words{{$01A0;$06FF;$0031;}};                               // DAFB parms
  words{{$01C6;$0100;$001C;$01FF;$0037;$003D;}};             // Dynamic Swatch parms
  words{{$004F;$0060;$01F0;$01FE;$005F;}};
  words{{$00BE;}};                                           // ACDC parms
  words{{$0060;$0060;$01F0;}};                               // AMD params
 
  words{{((defmBounds_RSVGA*16)/32)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1664_RB-((defmBounds_RSVGA*16)/8));}};        // SkipFactor

// Thirty-two bit mode parameters
//
  words{{$0340;$0000;$0031;}};                               // DAFB parms
  words{{$038C;$0200;$0038;$03FF;$006F;$007B;}};             // Dynamic Swatch parms
  words{{$009F;$00C9;$03E9;$03FE;$00C8;}};
  words{{$003C;}};                                           // ACDC parms
  words{{$00C3;$00C3;$03E3;}};                               // AMD params

  words{{((defmBounds_RSVGA*32)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_3328_RB-((defmBounds_RSVGA*32)/8));}};        // SkipFactor
}};



//
// NTSC (Safe Title) Display parameters
//
resource 'node' (2805, "_sVidParms_DAFB_NTSCST") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0C;$01;$02;$00;$07;$03;$00;$00;$00;$04;}};         // 8531 chip parms
  words{{$1C05;$C1A0;$3600;}};                               // 8534 chip parms
                
// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BNTSCST-1;}};                            // ActiveHeight

// Static DAFB params
//
  words{{$020D;$020C;$0005;$000B;$0023;$0203;$0206;}};       // Static Swatch params

// One bit mode params
//
  words{{$0200;$061E;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0814;}};
  words{{$0080;}};                                           // ACDC params
  words{{$080F;$006D;$02ED;}};                               // AMD params
                
  words{{((defmBounds_RNTSCST*1)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*1)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*1)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*1)/8));}};       // SkipFactor

// Two bit mode params
//
  words{{$0200;$060E;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0844;}};
  words{{$0088;}};                                           // ACDC params
  words{{$083F;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCST*2)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*2)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*2)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*2)/8));}};       // SkipFactor

// Four bit mode params
//
  words{{$0200;$0606;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$085C;}};
  words{{$0090;}};                                           // ACDC params
  words{{$0857;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCST*4)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*4)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*4)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*4)/8));}};       // SkipFactor

// Eight bit mode params
//
  words{{$0200;$0602;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0868;}};
  words{{$0098;}};                                           // ACDC params
  words{{$0863;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCST*8)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*8)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*8)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*8)/8));}};       // SkipFactor

// Sixteen bit mode params
//
  words{{$0400;$0600;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$006D;$02ED;$030A;$0869;}};
  words{{$009E;}};                                           // ACDC params
  words{{$0869;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCST*16)/64)-1;}};                  // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*16)/32)-1;}};                  // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*16)/32;}}; // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RNTSCFF*16)/8));}};      // SkipFactor

// Thirty-two bit mode params
//
  words{{$0800;$06FF;$0076;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0073;$02F3;$030A;$0873;}};
  words{{$009C;}};                                           // ACDC params
  words{{$086D;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCST*32)/64)-1;}};                  // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*32)/32)-1;}};                  // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*32)/32;}}; // BorderSide
  words{{(DAFB_4096_RB-((defmBounds_RNTSCFF*32)/8));}};      // SkipFactor
}};



//
// NTSC (Full Frame) Display parameters
//
resource 'node' (2810, "_sVidParms_DAFB_NTSCFF") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0C;$01;$02;$00;$07;$03;$00;$00;$00;$04;}};         // 8531 chip parms
  words{{$1C05;$C1A0;$3600;}};                               // 8534 chip parms

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BNTSCFF-1;}};                            // ActiveHeight

// Static DAFB params
//
  words{{$020D;$020C;$0005;$000B;$0023;$0203;$0206;}};       // Static Swatch params

// One bit mode params
//
  words{{$0200;$061E;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0814;}};
  words{{$0080;}};                                           // ACDC params
  words{{$080F;$006D;$02ED;}};                               // AMD params
                
  words{{((defmBounds_RNTSCFF*1)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*1)/8));}};       // SkipFactor

// Two bit mode params
//
  words{{$0200;$060E;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0844;}};
  words{{$0088;}};                                           // ACDC params
  words{{$083F;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*2)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*2)/8));}};       // SkipFactor

// Four bit mode params
//
  words{{$0200;$0606;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$085C;}};
  words{{$0090;}};                                           // ACDC params
  words{{$0857;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*4)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*4)/8));}};       // SkipFactor

// Eight bit mode params
//
  words{{$0200;$0602;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0072;$02F2;$030A;$0868;}};
  words{{$0098;}};                                           // ACDC params
  words{{$0863;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*8)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*8)/8));}};       // SkipFactor

// Sixteen bit mode params
//
  words{{$0400;$0600;$0074;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$006D;$02ED;$030A;$0869;}};
  words{{$009E;}};                                           // ACDC params
  words{{$0869;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*16)/64)-1;}};                  // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_2048_RB-((defmBounds_RNTSCFF*16)/8));}};      // SkipFactor

// Thirty-two bit mode params
//
  words{{$0800;$06FF;$0076;}};                               // DAFB params
  words{{$014C;$0186;$001D;$030B;$0039;$003F;}};             // Dynamic Swatch params
  words{{$0062;$0073;$02F3;$030A;$0873;}};
  words{{$009C;}};                                           // ACDC params
  words{{$086D;$006D;$02ED;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*32)/64)-1;}};                  // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_4096_RB-((defmBounds_RNTSCFF*32)/8));}};      // SkipFactor
}};



//
// NTSC (Safe Title Convolved) Display parameters
//
resource 'node' (2815, "_sVidParms_DAFB_NTSCconvST") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0C;$01;$02;$00;$07;$03;$00;$00;}};                 // Clock chip parms
  bytes{{$00;$02;$05;$06;$04;$01;$00;$00;}};

// Misc params
//
  bytes{{FourthVidMode-FirstVidMode;FourthVidMode-FirstVidMode;}}; // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BNTSCST-1;}};                            // ActiveHeight

// Static DAFB params
//
  words{{$020D;$020C;$0005;$000B;$0023;$0203;$0206;}};       // Static Swatch params

// One bit mode params
//
  words{{$0200;$060E;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00BE;$05EC;$0616;$08A0;}};
  words{{$00A1;}};                                           // ACDC params
  words{{$089C;$00BA;$05BA;}};                               // AMD params
                
  words{{((defmBounds_RNTSCST*1)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*1)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*1)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*1)/8));}};       // SkipFactor

// Two bit mode params
//
  words{{$0200;$0606;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00D6;$05EC;$0616;$08C8;}};
  words{{$00A9;}};                                           // ACDC params
  words{{$08C4;$00D2;$05D2;}};                               // AMD params

  words{{((defmBounds_RNTSCST*2)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*2)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*2)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*2)/8));}};       // SkipFactor
                
// Four bit mode params
//
  words{{$0200;$0602;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00E2;$05EC;$0616;$08DC;}};
  words{{$00B1;}};                                           // ACDC params
  words{{$08D8;$00DE;$05DE;}};                               // AMD params

  words{{((defmBounds_RNTSCST*4)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*4)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*4)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*4)/8));}};       // SkipFactor
                
// Eight bit mode params
//
  words{{$0200;$0600;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00E8;$05EC;$0616;$08E6;}};
  words{{$00B9;}};                                           // ACDC params
  words{{$08E2;$00E4;$05E4;}};                               // AMD params

  words{{((defmBounds_RNTSCST*8)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BNTSCFF-defmBounds_BNTSCST)/2;}};       // BorderHeight
  words{{((defmBounds_RNTSCFF*8)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RNTSCFF-defmBounds_RNTSCST)/2)*8)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*8)/8));}};       // SkipFactor
}};

                

//
// NTSC (Full Frame Convolved) Display parameters
//
resource 'node' (2820, "_sVidParms_DAFB_NTSCconvFF") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0C;$01;$02;$00;$07;$03;$00;$00;}};                 // Clock chip parms
  bytes{{$00;$02;$05;$06;$04;$01;$00;$00;}};

// Misc params
//
  bytes{{FourthVidMode-FirstVidMode;FourthVidMode-FirstVidMode;}}; // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BNTSCFF-1;}};                            // ActiveHeight

// Static DAFB params
//
  words{{$020D;$020C;$0005;$000B;$0023;$0203;$0206;}};       // Static Swatch params

// One bit mode params
//
  words{{$0200;$060E;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00BE;$05EC;$0616;$08A0;}};
  words{{$00A1;}};                                           // ACDC params
  words{{$089C;$00BA;$05BA;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*1)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*1)/8));}};       // SkipFactor

// Two bit mode params
//
  words{{$0200;$0606;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00D6;$05EC;$0616;$08C8;}};
  words{{$00A9;}};                                           // ACDC params
  words{{$08C4;$00D2;$05D2;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*2)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*2)/8));}};       // SkipFactor

// Four bit mode params
//
  words{{$0200;$0602;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00E2;$05EC;$0616;$08DC;}};
  words{{$00B1;}};                                           // ACDC params
  words{{$08D8;$00DE;$05DE;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*4)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*4)/8));}};       // SkipFactor

// Eight bit mode params
//
  words{{$0200;$0600;$007C;}};                               // DAFB params
  words{{$0298;$030C;$003A;$0617;$0073;$007F;}};             // Dynamic Swatch params
  words{{$00B1;$00E8;$05EC;$0616;$08E6;}};
  words{{$00B9;}};                                           // ACDC params
  words{{$08E2;$00E4;$05E4;}};                               // AMD params

  words{{((defmBounds_RNTSCFF*8)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RNTSCFF*8)/8));}};       // SkipFactor
}};



//
// PAL (Safe Title) Display parameters
//
resource 'node' (2825, "_sVidParms_DAFB_PALST") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0D;$09;$01;$00;$06;$04;$00;$01;$01;$03;}};         // 8531 chip params
  words{{$1C05;$C0A0;$6E00;}};

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{FifthVidMode-FirstVidMode;-1;}};                    // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BPALST-1;}};                             // ActiveHeight

// Static DAFB params
//
  words{{$0271;$0270;$0004;$0009;$0027;$0267;$026B;}};       // Static Swatch params

// One bit mode params
//
  words{{$01A0;$061E;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0834;}};
  words{{$0000;}};                                           // ACDC params
  words{{$082F;$008D;$038D;}};                               // AMD params
                
  words{{((defmBounds_RPALST*1)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*1)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*1)/32;}}; // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*1)/8));}};         // SkipFactor

// Two bit mode params
//
  words{{$01A0;$060E;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0864;}};
  words{{$0008;}};                                           // ACDC params
  words{{$085F;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALST*2)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*2)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*2)/32;}}; // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*2)/8));}};         // SkipFactor

// Four bit mode params
//
  words{{$01A0;$0606;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$087C;}};
  words{{$0010;}};                                           // ACDC params
  words{{$0877;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALST*4)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*4)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*4)/32;}}; // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*4)/8));}};         // SkipFactor

// Eight bit mode params
//
  words{{$01A0;$0602;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0888;}};
  words{{$0018;}};                                           // ACDC params
  words{{$0883;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALST*8)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*8)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*8)/32;}}; // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*8)/8));}};         // SkipFactor

// Sixteen bit mode params
//
  words{{$0340;$0600;$0075;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$008D;$038D;$03AE;$0887;}};
  words{{$001E;}};                                           // ACDC params
  words{{$0888;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALST*16)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*16)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*16)/32;}}; // BorderSide
  words{{(DAFB_1664_RB-((defmBounds_RPALFF*16)/8));}};       // SkipFactor

// Thirty-Two bit mode params
//
  words{{$0680;$06FF;$0075;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0093;$0393;$03AE;$0892;}};
  words{{$001C;}};                                           // ACDC params
  words{{$088C;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALST*32)/64)-1;}};                   // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*32)/32)-1;}};                   // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*32)/32;}}; // BorderSide
  words{{(DAFB_3328_RB-((defmBounds_RPALFF*32)/8));}};       // SkipFactor
}};



//
// PAL (Full Frame) Display parameters
//
resource 'node' (2830, "_sVidParms_DAFB_PALFF") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0D;$09;$01;$00;$06;$04;$00;$01;$01;$03;}};         // 8531 chip params
  words{{$1C05;$C0A0;$6E00;}};

// Misc params
//
  bytes{{FifthVidMode;SixthVidMode;}};                       // MaxMode a,b
  bytes{{FifthVidMode-FirstVidMode;-1;}};                    // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BPALFF-1;}};                             // ActiveHeight

// Static DAFB params
//
  words{{$0271;$0270;$0004;$0009;$0027;$0267;$026B;}};       // Static Swatch params

// One bit mode params
//
  words{{$01A0;$061E;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0834;}};
  words{{$0000;}};                                           // ACDC params
  words{{$082F;$008D;$038D;}};                               // AMD params
                
  words{{((defmBounds_RPALFF*1)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*1)/8));}};         // SkipFactor

// Two bit mode params
//
  words{{$01A0;$060E;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0864;}};
  words{{$0008;}};                                           // ACDC params
  words{{$085F;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALFF*2)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*2)/8));}};         // SkipFactor

// Four bit mode params
//
  words{{$01A0;$0606;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$087C;}};
  words{{$0010;}};                                           // ACDC params
  words{{$0877;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALFF*4)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*4)/8));}};         // SkipFactor

// Eight bit mode params
//
  words{{$01A0;$0602;$0074;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0092;$0392;$03AE;$0888;}};
  words{{$0018;}};                                           // ACDC params
  words{{$0883;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALFF*8)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_832_RB-((defmBounds_RPALFF*8)/8));}};         // SkipFactor

// Sixteen bit mode params
//
  words{{$0340;$0600;$0075;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$008D;$038D;$03AE;$0887;}};
  words{{$001E;}};                                           // ACDC params
  words{{$0888;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALFF*16)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1664_RB-((defmBounds_RPALFF*16)/8));}};       // SkipFactor

// Thirty-Two bit mode params
//
  words{{$0680;$06FF;$0075;}};                               // DAFB params
  words{{$0192;$01D8;$0023;$03AF;$0045;$0049;}};             // Dynamic Swatch params
  words{{$006D;$0093;$0393;$03AE;$0892;}};
  words{{$001C;}};                                           // ACDC params
  words{{$088C;$008D;$038D;}};                               // AMD params

  words{{((defmBounds_RPALFF*32)/64)-1;}};                   // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_3328_RB-((defmBounds_RPALFF*32)/8));}};       // SkipFactor
}};



//
// PAL (Safe Title Convolved) Display parameters
//
resource 'node' (2835, "_sVidParms_DAFB_PALconvST") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0D;$09;$01;$00;$06;$04;$00;$01;}};                 // Clock chip params
  bytes{{$01;$01;$05;$06;$00;$01;$00;$00;}};

// Misc params
//
  bytes{{FourthVidMode-FirstVidMode;FourthVidMode-FirstVidMode;}}; // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BPALST-1;}};                             // ActiveHeight

// Static DAFB params
//
  words{{$0271;$0270;$0004;$0009;$0027;$0267;$026B;}};       // Static Swatch params

// One bit mode params
//
  words{{$0200;$060E;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$00FE;$072C;$075E;$08E0;}};
  words{{$0021;}};                                           // ACDC params
  words{{$08DC;$00FA;$06FA;}};                               // AMD params
                
  words{{((defmBounds_RPALST*1)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*1)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*1)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*1)/8));}};        // SkipFactor

// Two bit mode params
//
  words{{$0200;$0606;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0116;$072C;$075E;$0908;}};
  words{{$0029;}};                                           // ACDC params
  words{{$0904;$0112;$0712;}};                               // AMD params

  words{{((defmBounds_RPALST*2)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*2)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*2)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*2)/8));}};        // SkipFactor

// Four bit mode params
//
  words{{$0200;$0602;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0122;$072C;$075E;$091C;}};
  words{{$0031;}};                                           // ACDC params
  words{{$0918;$011E;$071E;}};                               // AMD params

  words{{((defmBounds_RPALST*4)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*4)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*4)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*4)/8));}};        // SkipFactor

// Eight bit mode params
//
  words{{$0200;$0600;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0128;$072C;$075E;$0926;}};
  words{{$0039;}};                                           // ACDC params
  words{{$0922;$0124;$0724;}};                               // AMD params

  words{{((defmBounds_RPALST*8)/64)-1;}};                    // ActiveWidth
  words{{(defmBounds_BPALFF-defmBounds_BPALST)/2;}};         // BorderHeight
  words{{((defmBounds_RPALFF*8)/32)-1;}};                    // BorderWidth
  words{{(((defmBounds_RPALFF-defmBounds_RPALST)/2)*8)/32;}}; // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*8)/8));}};        // SkipFactor
}};



//
// PAL (Full Frame Convolved) Display parameters
//
resource 'node' (2840, "_sVidParms_DAFB_PALconvFF") {{
  blocksize{};                                               // block size
                
// Clock chip params
//
  bytes{{$0D;$09;$01;$00;$06;$04;$00;$01;}};                 // Clock chip params
  bytes{{$01;$01;$05;$06;$00;$01;$00;$00;}};

// Misc params
//
  bytes{{FourthVidMode-FirstVidMode;FourthVidMode-FirstVidMode;}}; // MaxMode a,b
  bytes{{-1;-1;}};                                           // Non-Wombat AMD TimingAdj Fudge
  words{{defmBounds_BPALFF-1;}};                             // ActiveHeight

// Static DAFB params
//
  words{{$0271;$0270;$0004;$0009;$0027;$0267;$026B;}};       // Static Swatch params.
                
// One bit mode params
//
  words{{$0200;$060E;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$00FE;$072C;$075E;$08E0;}};
  words{{$0021;}};                                           // ACDC params
  words{{$08DC;$00FA;$06FA;}};                               // AMD params

  words{{((defmBounds_RPALFF*1)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*1)/8));}};        // SkipFactor

// Two bit mode params
//
  words{{$0200;$0606;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0116;$072C;$075E;$0908;}};
  words{{$0029;}};                                           // ACDC params
  words{{$0904;$0112;$0712;}};                               // AMD params

  words{{((defmBounds_RPALFF*2)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*2)/8));}};        // SkipFactor

// Four bit mode params
//
  words{{$0200;$0602;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0122;$072C;$075E;$091C;}};
  words{{$0031;}};                                           // ACDC params
  words{{$0918;$011E;$071E;}};                               // AMD params

  words{{((defmBounds_RPALFF*4)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*4)/8));}};        // SkipFactor

// Eight bit mode params
//
  words{{$0200;$0600;$007C;}};                               // DAFB params
  words{{$0324;$03B0;$0046;$075F;$008B;$0093;}};             // Dynamic Swatch params
  words{{$00DB;$0128;$072C;$075E;$0926;}};
  words{{$0039;}};                                           // ACDC params
  words{{$0922;$0124;$0724;}};                               // AMD params

  words{{((defmBounds_RPALFF*8)/64)-1;}};                    // ActiveWidth
  words{{0;}};                                               // BorderHeight
  words{{0-1;}};                                             // BorderWidth
  words{{0;}};                                               // BorderSide
  words{{(DAFB_1024_RB-((defmBounds_RPALFF*8)/8));}};        // SkipFactor
}};


//-------------------------------------------------------------
//               One-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (3180, "_OBMHR") {{
  mVidParams,       l{"_OBVParmsHR"};						// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesHR};							// number of video pages in this configuration
  mDevType,         d{defmDevType};							// device type
}};


resource 'vmod' (3185, "_OBMHR400") {{
  mVidParams,       l{"_OBVParmsHR400"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};

resource 'vmod' (3187, "_OBMHR399") {{
  mVidParams,       l{"_OBVParmsHR399"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3190, "_OBMFP") {{
  mVidParams,       l{"_OBVParmsFP"};						// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesFP};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3195, "_OBMGS") {{
  mVidParams,       l{"_OBVParmsGS"};						// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3200, "_OBMGS560") {{
  mVidParams,       l{"_OBVParmsGS560"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3205, "_OBMGF") {{
  mVidParams,       l{"_OBVParmsGF"};						// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesGF};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3210, "_OBMSE") {{
  mVidParams,       l{"_OBVParmsSE"};						// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesSE};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3215, "_OBM_V8_HRa") {{
  mVidParams,       l{"_OBVParms_V8_HRa"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                     	 // device type
}};


resource 'vmod' (3220, "_OBM_V8_HRb") {{
  mVidParams,       l{"_OBVParms_V8_HRb"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3225, "_OBM_V8_GSa") {{
  mVidParams,       l{"_OBVParms_V8_GSa"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3230, "_OBM_V8_GSb") {{
  mVidParams,       l{"_OBVParms_V8_GSb"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3235, "_OBM_V8_A2Ema") {{
  mVidParams,       l{"_OBVParms_V8_A2Em"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesA2Em};                     	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (3240, "_OBM_V8_A2Emb") {{
  mVidParams,       l{"_OBVParms_V8_A2Em"};					// offset to vid parameters for this configuration
  mPageCnt,         d{OBMPagesA2Em};                     	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'node' (3245, "_OBM_Civic_19") {{
  include{l{"_OBM_DAFB_19"}};
}};

resource 'vmod' (3250, "_OBM_DAFB_19") {{
  mVidParams,       l{"_OBVParms_DAFB_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3255, "_OBM_Civic_FP") {{
  include{l{"_OBM_DAFB_FP"}};
}};

resource 'vmod' (3260, "_OBM_DAFB_FP") {{
  mVidParams,       l{"_OBVParms_DAFB_FP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3265, "_OBM_Civic_2P") {{
  mVidParams,       l{"_OBVParms_Civic_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3270, "_OBM_Civic_vi2P") {{
  include{l{"_OBM_DAFB_2P"}};
}};

resource 'vmod' (3275, "_OBM_DAFB_2P") {{
  mVidParams,       l{"_OBVParms_DAFB_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3280, "_OBM_Civic_GF") {{
  include{l{"_OBM_DAFB_LP"}};
}};

resource 'vmod' (3285, "_OBM_DAFB_LP") {{
  mVidParams,       l{"_OBVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3290, "_OBM_Civic_NTSCSTConv") {{
  include{l{"_OBM_Civic_NTSCST"}};
}};

resource 'node' (3295, "_OBM_Civic_NTSCST") {{
  include{l{"_OBM_Civic_GS"}};
}};

resource 'node' (3300, "_OBM_Civic_GS") {{
  include{l{"_OBM_DAFB_GS"}};
}};

resource 'vmod' (3305, "_OBM_DAFB_GS") {{
  mVidParams,       l{"_OBVParms_DAFB_GS"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

                
resource 'vmod' (3310, "_OBM_Civic_GS560") {{
  mVidParams,       l{"_OBVParms_Civic_GS560"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3315, "_OBM_Civic_PALSTConv") {{
  include{l{"_OBM_Civic_PALST"}};
}};

resource 'node' (3320, "_OBM_Civic_PALST") {{
  include{l{"_OBM_Civic_NTSCFFconv"}};
}};

resource 'node' (3325, "_OBM_Civic_NTSCFFconv") {{
  include{l{"_OBM_Civic_NTSCFF"}};
}};

resource 'node' (3330, "_OBM_Civic_NTSCFF") {{
  include{l{"_OBM_Civic_VGA"}};
}};

resource 'node' (3335, "_OBM_Civic_VGA") {{
  include{l{"_OBM_Civic_HR"}};
}};

resource 'node' (3340, "_OBM_Civic_HR") {{
  include{l{"_OBM_DAFB_NTSCFF"}};
}};

resource 'node' (3345, "_OBM_DAFB_NTSCFF") {{
  include{l{"_OBM_DAFB_NTSCFFconv"}};
}};

resource 'node' (3350, "_OBM_DAFB_NTSCFFconv") {{
  include{l{"_OBM_DAFB_VGA"}};
}};

resource 'node' (3355, "_OBM_DAFB_VGA") {{
  include{l{"_OBM_DAFB_HR"}};
}};

resource 'vmod' (3360, "_OBM_DAFB_HR") {{
  mVidParams,       l{"_OBVParms_DAFB_640by480"};				// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3365, "_OBM_Civic_HR400") {{
  mVidParams,       l{"_OBVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};

                
resource 'vmod' (3370, "_OBM_Civic_HRMAZ") {{
  mVidParams,       l{"_OBVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3375, "_OBM_Civic_SVGA") {{
  include{l{"_OBM_DAFB_SVGA"}};
}};

resource 'vmod' (3380, "_OBM_DAFB_SVGA") {{
  mVidParams,       l{"_OBVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3385, "_OBM_DAFB_NTSCST") {{
  include{l{"_OBM_DAFB_NTSCSTconv"}};
}};

resource 'vmod' (3390, "_OBM_DAFB_NTSCSTconv") {{
  mVidParams,       l{"_OBVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3395, "_OBM_DAFB_PALST") {{
  mVidParams,       l{"_OBVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3400, "_OBM_DAFB_PALSTconv") {{
  mVidParams,       l{"_OBVParms_DAFB_PALSTconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

                
resource 'node' (3405, "_OBM_Civic_PALFF") {{
  include{l{"_OBM_DAFB_PALFF"}};
}};

resource 'vmod' (3410, "_OBM_DAFB_PALFF") {{
  mVidParams,       l{"_OBVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3415, "_OBM_Civic_PALFFConv") {{
  include{l{"_OBM_DAFB_PALFFconv"}};
}};

resource 'vmod' (3420, "_OBM_DAFB_PALFFconv") {{
  mVidParams,       l{"_OBVParms_DAFB_PALFFconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3425, "_OBMLCD") {{
  mVidParams,       l{"_OBVParmsLCD"};						// offset to vid parameters for this configuration
  mTable,           l{"_OBVFixedCLUTLCD"};					// offset to device color table (fixed device)
  mPageCnt,         d{OBMPagesLCD};                      	// number of video pages in this configuration
  mDevType,         d{fixedType};                        	// device type
}};

resource 'vmod' (3430, "_OBMLCD480") {{
  mVidParams,       l{"_OBVParmsHR"};						// offset to vid parameters for this configuration
  mTable,           l{"_OBVFixedCLUTLCD"};					// offset to device color table (fixed device)
  mPageCnt,         d{OBMPagesLCD};                      	// number of video pages in this configuration
  mDevType,         d{fixedType};                        	// device type
}};

                
resource 'vmod' (3435, "_OBMApollo") {{
  mVidParams,       l{"_OBVParmsApollo"};					// offset to vid parameters for this configuration
  mTable,           l{"_OBVFixedCLUTApollo"};				// offset to device color table (fixed device)
  mPageCnt,         d{OBMPagesApollo};                  	// number of video pages in this configuration
  mDevType,         d{fixedType};                       	// device type
}};


// Fixed CLUTs…
//
resource 'node' (3440, "_OBVFixedCLUTApollo") {{
  include{l{"_OBVFixedCLUTLCD"}};
}};

resource 'node' (3445, "_OBVFixedCLUTLCD") {{
  include{l{"_OBVFixedCLUT"}};
}};

resource 'node' (3450, "_OBVFixedCLUT") {{
  blocksize{};                                               // Physical Block Size.
                
  longs{{32+1;}};                                            // ctSeed
  words{{$0000;}};                                           // ctFlags
  words{{$0001;}};                                           // ctSize (n - 1)
                
  words{{$0000;$FFFF;$FFFF;$FFFF;}};                         // value, r,g,b (white entry).
  words{{$0001;$0000;$0000;$0000;}};                         // value, r,g,b (black entry).
}};



// VidParams…
//
resource 'node' (3455, "_OBVParmsHR") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3460, "_OBVParmsHR400") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR400;defmBounds_LHR400;defmBounds_BHR400;defmBounds_RHR400;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};

resource 'node' (3462, "_OBVParmsHR399") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR399;defmBounds_LHR399;defmBounds_BHR399;defmBounds_RHR399;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3465, "_OBVParmsFP") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMFPRB;}};                                         // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3470, "_OBVParmsGS") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{OBMGSRB;}};                                         // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3475, "_OBVParmsGS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{OBMGS560RB;}};                                      // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3480, "_OBVParmsGF") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{OBMGFRB;}};                                         // physRowBytes
  words{{defmBounds_TGF;defmBounds_LGF;defmBounds_BGF;defmBounds_RGF;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGF;}};                                          // bmHRes
  longs{{VResGF;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3485, "_OBVParmsSE") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMSERB;}};                                         // physRowBytes
  words{{defmBounds_TSE;defmBounds_LSE;defmBounds_BSE;defmBounds_RSE;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResSE;}};                                          // bmHRes
  longs{{VResSE;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3490, "_OBVParms_DAFB_640by480") {{
  include{l{"_OBVParms_V8_HRa"}};
}};

resource 'node' (3495, "_OBVParms_V8_HRa") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3500, "_OBVParms_V8_HRb") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3505, "_OBVParms_DAFB_GS") {{
  include{l{"_OBVParms_V8_GSa"}};
}};

resource 'node' (3510, "_OBVParms_V8_GSa") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3515, "_OBVParms_V8_GSb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3520, "_OBVParms_V8_A2Em") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3525, "_OBVParms_DAFB_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3530, "_OBVParms_DAFB_FP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};
  longs{{VResFP;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3535, "_OBVParms_Civic_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1152_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3540, "_OBVParms_DAFB_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_576_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3545, "_OBVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3550, "_OBVParms_Civic_GS560") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3555, "_OBVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3560, "_OBVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_832_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3565, "_OBVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3570, "_OBVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB1;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3575, "_OBVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB1;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3580, "_OBVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3585, "_OBVParms_DAFB_PALSTconv") {{
  blocksize{};
  longs{{defmPALSTB1Conv;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3590, "_OBVParms_DAFB_PALFFconv") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{1;}};
  words{{defCmpCount;}};
  words{{1;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3595, "_OBVParmsLCD") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{OBMLCDRB;}};                                        // physRowBytes
  words{{defmBounds_TLCD;defmBounds_LLCD;defmBounds_BLCD;defmBounds_RLCD;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLCD;}};                                         // bmHRes
  longs{{VResLCD;}};                                         // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3605, "_OBVParmsApollo") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{OBMApolloRB;}};                                     // physRowBytes
  words{{defmBounds_TApollo;defmBounds_LApollo;defmBounds_BApollo;defmBounds_RApollo;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResApollo;}};                                      // bmHRes
  longs{{VResApollo;}};                                      // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{1;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{1;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


//-------------------------------------------------------------
//               Two-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (3610, "_TBMHR") {{
  mVidParams,       l{"_TBVParmsHR"};					// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesHR};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3615, "_TBMHR400") {{
  mVidParams,       l{"_TBVParmsHR400"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesHR};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};

resource 'vmod' (3617, "_TBMHR399") {{
  mVidParams,       l{"_TBVParmsHR399"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesHR};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3620, "_TBMFP") {{
  mVidParams,       l{"_TBVParmsFP"};					// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesFP};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3625, "_TBMGS") {{
  mVidParams,       l{"_TBVParmsGS"};					// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesGS};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3630, "_TBMGS560") {{
  mVidParams,       l{"_TBVParmsGS560"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesGS};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3635, "_TBMGF") {{
  mVidParams,       l{"_TBVParmsGF"};					// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesGF};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3640, "_TBMSE") {{
  mVidParams,       l{"_TBVParmsSE"};					// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesSE};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3645, "_TBM_V8_HRa") {{
  mVidParams,       l{"_TBVParms_V8_HRa"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesHR};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3650, "_TBM_V8_HRb") {{
  mVidParams,       l{"_TBVParms_V8_HRb"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesHR};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3655, "_TBM_V8_GSa") {{
  mVidParams,       l{"_TBVParms_V8_GSa"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesGS};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3660, "_TBM_V8_GSb") {{
  mVidParams,       l{"_TBVParms_V8_GSb"};				// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesGS};                      // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3665, "_TBM_V8_A2Ema") {{
  mVidParams,       l{"_TBVParms_V8_A2Ema"};			// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesA2Em};                    // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3670, "_TBM_V8_A2Emb") {{
  mVidParams,       l{"_TBVParms_V8_A2Emb"};			// offset to vid parameters for this configuration
  mPageCnt,         d{TBMPagesA2Em};                    // number of video pages in this configuration
  mDevType,         d{defmDevType};                     // device type
}};


resource 'vmod' (3675, "_TBM_Civic_19") {{
  mVidParams,       l{"_TBVParms_Civic_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

resource 'vmod' (3680, "_TBM_DAFB_19") {{
  mVidParams,       l{"_TBVParms_DAFB_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3685, "_TBM_Civic_FP") {{
  include{l{"_TBM_DAFB_FP"}};
}};

resource 'vmod' (3690, "_TBM_DAFB_FP") {{
  mVidParams,       l{"_TBVParms_DAFB_FP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3695, "_TBM_Civic_2P") {{
  mVidParams,       l{"_TBVParms_Civic_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3700, "_TBM_Civic_vi2P") {{
  include{l{"_TBM_DAFB_2P"}};
}};

resource 'vmod' (3705, "_TBM_DAFB_2P") {{
  mVidParams,       l{"_TBVParms_DAFB_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3710, "_TBM_Civic_GF") {{
  include{l{"_TBM_DAFB_LP"}};
}};

resource 'vmod' (3715, "_TBM_DAFB_LP") {{
  mVidParams,       l{"_TBVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3720, "_TBM_Civic_NTSCSTconv") {{
  include{l{"_TBM_Civic_NTSCST"}};
}};

resource 'node' (3725, "_TBM_Civic_NTSCST") {{
  include{l{"_TBM_Civic_GS"}};
}};

resource 'node' (3730, "_TBM_Civic_GS") {{
  include{l{"_TBM_DAFB_GS"}};
}};

resource 'vmod' (3735, "_TBM_DAFB_GS") {{
  mVidParams,       l{"_TBVParms_DAFB_GS"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3740, "_TBM_Civic_GS560") {{
  mVidParams,       l{"_TBVParms_Civic_GS560"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3745, "_TBM_Civic_PALSTConv") {{
  include{l{"_TBM_Civic_PALST"}};
}};

resource 'node' (3750, "_TBM_Civic_PALST") {{
  include{l{"_TBM_Civic_NTSCFFConv"}};
}};

resource 'node' (3755, "_TBM_Civic_NTSCFFConv") {{
  include{l{"_TBM_Civic_NTSCFF"}};
}};

resource 'node' (3760, "_TBM_Civic_NTSCFF") {{
  include{l{"_TBM_Civic_VGA"}};
}};

resource 'node' (3765, "_TBM_Civic_VGA") {{
  include{l{"_TBM_Civic_HR"}};
}};

resource 'node' (3770, "_TBM_Civic_HR") {{
  include{l{"_TBM_DAFB_NTSCFF"}};
}};

resource 'node' (3775, "_TBM_DAFB_NTSCFF") {{
  include{l{"_TBM_DAFB_NTSCFFconv"}};
}};

resource 'node' (3780, "_TBM_DAFB_NTSCFFconv") {{
  include{l{"_TBM_DAFB_VGA"}};
}};

resource 'node' (3785, "_TBM_DAFB_VGA") {{
  include{l{"_TBM_DAFB_HR"}};
}};

resource 'vmod' (3790, "_TBM_DAFB_HR") {{
  mVidParams,       l{"_TBVParms_DAFB_640by480"}; // a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

                
resource 'vmod' (3795, "_TBM_Civic_HR400") {{
  mVidParams,       l{"_TBVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3800, "_TBM_Civic_HRMAZ") {{
  mVidParams,       l{"_TBVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3805, "_TBM_Civic_SVGA") {{
  include{l{"_TBM_DAFB_SVGA"}};
}};

resource 'vmod' (3810, "_TBM_DAFB_SVGA") {{
  mVidParams,       l{"_TBVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3815, "_TBM_DAFB_NTSCST") {{
  include{l{"_TBM_DAFB_NTSCSTconv"}};
}};

resource 'vmod' (3820, "_TBM_DAFB_NTSCSTconv") {{
  mVidParams,       l{"_TBVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3825, "_TBM_DAFB_PALST") {{
  mVidParams,       l{"_TBVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3830, "_TBM_DAFB_PALSTconv") {{
  mVidParams,       l{"_TBVParms_DAFB_PALSTconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

    
resource 'node' (3835, "_TBM_Civic_PALFF") {{
  include{l{"_TBM_DAFB_PALFF"}};
}};

resource 'vmod' (3840, "_TBM_DAFB_PALFF") {{
  mVidParams,       l{"_TBVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (3845, "_TBM_Civic_PALFFConv") {{
  include{l{"_TBM_DAFB_PALFFconv"}};
}};

resource 'vmod' (3850, "_TBM_DAFB_PALFFconv") {{
  mVidParams,       l{"_TBVParms_DAFB_PALFFconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (3855, "_TBMLCD") {{
  mVidParams,       l{"_TBVParmsLCD"};					// offset to vid parameters for this configuration
  mTable,           l{"_TBVFixedCLUTLCD"};				// offset to device color table (fixed device)
  mPageCnt,         d{TBMPagesLCD};                     // number of video pages in this configuration
  mDevType,         d{fixedType};                       // device type
}};

resource 'vmod' (3860, "_TBMLCD480") {{
  mVidParams,       l{"_TBVParmsHR"};					// offset to vid parameters for this configuration
  mTable,           l{"_TBVFixedCLUTLCD"};				// offset to device color table (fixed device)
  mPageCnt,         d{TBMPagesLCD};                     // number of video pages in this configuration
  mDevType,         d{fixedType};                       // device type
}};


// Fixed CLUTs…
//
resource 'node' (3865, "_TBVFixedCLUTLCD") {{
  blocksize{};                                               // Physical Block Size.
                
  longs{{32+2;}};                                            // ctSeed
  words{{$0000;}};                                           // ctFlags
  words{{$0003;}};                                           // ctSize (n - 1)
                
  words{{$0000;$FFFF;$FFFF;$FFFF;}};                         // value, r,g,b (white entry).
  words{{$0001;$AAAA;$AAAA;$AAAA;}};                         // value, r,g,b (ltGray entry).
  words{{$0002;$5555;$5555;$5555;}};                         // value, r,g,b (dkGray entry).
  words{{$0003;$0000;$0000;$0000;}};                         // value, r,g,b (black entry).
}};



resource 'node' (3870, "_TBVParmsHR") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3875, "_TBVParmsHR400") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR400;defmBounds_LHR400;defmBounds_BHR400;defmBounds_RHR400;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};

resource 'node' (3877, "_TBVParmsHR399") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR399;defmBounds_LHR399;defmBounds_BHR399;defmBounds_RHR399;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3880, "_TBVParmsFP") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMFPRB;}};                                         // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3885, "_TBVParmsGS") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{TBMGSRB;}};                                         // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3890, "_TBVParmsGS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{TBMGS560RB;}};                                      // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3895, "_TBVParmsGF") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{TBMGFRB;}};                                         // physRowBytes
  words{{defmBounds_TGF;defmBounds_LGF;defmBounds_BGF;defmBounds_RGF;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGF;}};                                          // bmHRes
  longs{{VResGF;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3900, "_TBVParmsSE") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMSERB;}};                                         // physRowBytes
  words{{defmBounds_TSE;defmBounds_LSE;defmBounds_BSE;defmBounds_RSE;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResSE;}};                                          // bmHRes
  longs{{VResSE;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3905, "_TBVParms_DAFB_640by480") {{
  include{l{"_TBVParms_V8_HRa"}};
}};

resource 'node' (3910, "_TBVParms_V8_HRa") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3915, "_TBVParms_V8_HRb") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3920, "_TBVParms_DAFB_GS") {{
  include{l{"_TBVParms_V8_GSa"}};
}};

resource 'node' (3925, "_TBVParms_V8_GSa") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3930, "_TBVParms_V8_GSb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3935, "_TBVParms_V8_A2Ema") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3940, "_TBVParms_V8_A2Emb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (3943, "_TBVParms_Civic_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_256_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};

resource 'node' (3945, "_TBVParms_DAFB_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};

resource 'node' (3950, "_TBVParms_DAFB_FP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};
  longs{{VResFP;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3955, "_TBVParms_Civic_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1152_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3960, "_TBVParms_DAFB_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_576_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3965, "_TBVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3970, "_TBVParms_Civic_GS560") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3975, "_TBVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3980, "_TBVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_832_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3985, "_TBVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3990, "_TBVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB2;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (3995, "_TBVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB2;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4000, "_TBVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4005, "_TBVParms_DAFB_PALSTconv") {{
  blocksize{};
  longs{{defmPALSTB2Conv;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4010, "_TBVParms_DAFB_PALFFconv") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{2;}};
  words{{defCmpCount;}};
  words{{2;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4015, "_TBVParmsLCD") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{TBMLCDRB;}};                                        // physRowBytes
  words{{defmBounds_TLCD;defmBounds_LLCD;defmBounds_BLCD;defmBounds_RLCD;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLCD;}};                                         // bmHRes
  longs{{VResLCD;}};                                         // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{2;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{2;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


//-------------------------------------------------------------
//               Four-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (4025, "_FBMHR") {{
  mVidParams,       l{"_FBVParmsHR"};						// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4030, "_FBMHR400") {{
  mVidParams,       l{"_FBVParmsHR400"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};

resource 'vmod' (4033, "_FBMHR399") {{
  mVidParams,       l{"_FBVParmsHR399"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4035, "_FBMFP") {{
  mVidParams,       l{"_FBVParmsFP"};						// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesFP};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4040, "_FBMGS") {{
  mVidParams,       l{"_FBVParmsGS"};						// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4045, "_FBMGS560") {{
  mVidParams,       l{"_FBVParmsGS560"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4050, "_FBMGF") {{
  mVidParams,       l{"_FBVParmsGF"};						// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesGF};                      	// number of video pages in this configuration
  mDevType,         d{defmDevType};                     	// device type
}};


resource 'vmod' (4055, "_FBMSE") {{
  mVidParams,       l{"_FBVParmsSE"};						// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesSE};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4060, "_FBM_V8_HRa") {{
  mVidParams,       l{"_FBVParms_V8_HRa"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4065, "_FBM_V8_HRb") {{
  mVidParams,       l{"_FBVParms_V8_HRb"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4070, "_FBM_V8_GSa") {{
  mVidParams,       l{"_FBVParms_V8_GSa"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4075, "_FBM_V8_GSb") {{
  mVidParams,       l{"_FBVParms_V8_GSb"};					// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4080, "_FBM_V8_A2Ema") {{
  mVidParams,       l{"_FBVParms_V8_A2Ema"};				// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesA2Em};                     	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4085, "_FBM_V8_A2Emb") {{
  mVidParams,       l{"_FBVParms_V8_A2Emb"};				// offset to vid parameters for this configuration
  mPageCnt,         d{FBMPagesA2Em};                     	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'node' (4090, "_FBM_Civic_19") {{
  include{l{"_FBM_DAFB_19"}};
}};

resource 'vmod' (4095, "_FBM_DAFB_19") {{
  mVidParams,       l{"_FBVParms_DAFB_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4100, "_FBM_Civic_FP") {{
  include{l{"_FBM_DAFB_FP"}};
}};

resource 'vmod' (4105, "_FBM_DAFB_FP") {{
  mVidParams,       l{"_FBVParms_DAFB_FP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4110, "_FBM_Civic_2P") {{
  mVidParams,       l{"_FBVParms_Civic_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4115, "_FBM_Civic_vi2P") {{
  include{l{"_FBM_DAFB_2P"}};
}};

resource 'vmod' (4120, "_FBM_DAFB_2P") {{
  mVidParams,       l{"_FBVParms_DAFB_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4125, "_FBM_Civic_GF") {{
  include{l{"_FBM_DAFB_LP"}};
}};

resource 'vmod' (4130, "_FBM_DAFB_LP") {{
  mVidParams,       l{"_FBVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4135, "_FBM_Civic_NTSCSTconv") {{
  include{l{"_FBM_Civic_NTSCST"}};
}};

resource 'node' (4140, "_FBM_Civic_NTSCST") {{
  include{l{"_FBM_Civic_GS"}};
}};

resource 'node' (4145, "_FBM_Civic_GS") {{
  include{l{"_FBM_DAFB_GS"}};
}};

resource 'vmod' (4150, "_FBM_DAFB_GS") {{
  mVidParams,       l{"_FBVParms_DAFB_GS"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4155, "_FBM_Civic_GS560") {{
  mVidParams,       l{"_FBVParms_Civic_GS560"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4160, "_FBM_Civic_PALSTConv") {{
  include{l{"_FBM_Civic_PALST"}};
}};

resource 'node' (4165, "_FBM_Civic_PALST") {{
  include{l{"_FBM_Civic_NTSCFFConv"}};
}};

resource 'node' (4170, "_FBM_Civic_NTSCFFConv") {{
  include{l{"_FBM_Civic_NTSCFF"}};
}};

resource 'node' (4175, "_FBM_Civic_NTSCFF") {{
  include{l{"_FBM_Civic_VGA"}};
}};

resource 'node' (4180, "_FBM_Civic_VGA") {{
  include{l{"_FBM_Civic_HR"}};
}};

resource 'node' (4185, "_FBM_Civic_HR") {{
  include{l{"_FBM_DAFB_NTSCFF"}};
}};

resource 'node' (4190, "_FBM_DAFB_NTSCFF") {{
  include{l{"_FBM_DAFB_NTSCFFconv"}};
}};

resource 'node' (4195, "_FBM_DAFB_NTSCFFconv") {{
  include{l{"_FBM_DAFB_VGA"}};
}};

resource 'node' (4200, "_FBM_DAFB_VGA") {{
  include{l{"_FBM_DAFB_HR"}};
}};

resource 'vmod' (4205, "_FBM_DAFB_HR") {{
  mVidParams,       l{"_FBVParms_DAFB_640by480"};		// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4210, "_FBM_Civic_HR400") {{
  mVidParams,       l{"_FBVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4215, "_FBM_Civic_HRMAZ") {{
  mVidParams,       l{"_FBVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4220, "_FBM_Civic_SVGA") {{
  include{l{"_FBM_DAFB_SVGA"}};
}};

resource 'vmod' (4225, "_FBM_DAFB_SVGA") {{
  mVidParams,       l{"_FBVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4230, "_FBM_DAFB_NTSCST") {{
  include{l{"_FBM_DAFB_NTSCSTconv"}};
}};

resource 'vmod' (4235, "_FBM_DAFB_NTSCSTconv") {{
  mVidParams,       l{"_FBVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4240, "_FBM_DAFB_PALST") {{
  mVidParams,       l{"_FBVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4245, "_FBM_DAFB_PALSTconv") {{
  mVidParams,       l{"_FBVParms_DAFB_PALSTconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4250, "_FBM_Civic_PALFF") {{
  include{l{"_FBM_DAFB_PALFF"}};
}};

resource 'vmod' (4255, "_FBM_DAFB_PALFF") {{
  mVidParams,       l{"_FBVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4260, "_FBM_Civic_PALFFconv") {{
  include{l{"_FBM_DAFB_PALFFconv"}};
}};

resource 'vmod' (4265, "_FBM_DAFB_PALFFconv") {{
  mVidParams,       l{"_FBVParms_DAFB_PALFFconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4270, "_FBMLCD") {{
  mVidParams,       l{"_FBVParmsLCD"};						// offset to vid parameters for this configuration
  mTable,           l{"_FBVFixedCLUTLCD"};					// offset to device color table (fixed device)
  mPageCnt,         d{FBMPagesLCD};                      	// number of video pages in this configuration
  mDevType,         d{fixedType};                        	// device type
}};

resource 'vmod' (4275, "_FBMLCD480") {{
  mVidParams,       l{"_FBVParmsHR"};						// offset to vid parameters for this configuration
  mTable,           l{"_FBVFixedCLUTLCD"};					// offset to device color table (fixed device)
  mPageCnt,         d{FBMPagesLCD};                      	// number of video pages in this configuration
  mDevType,         d{fixedType};                        	// device type
}};


// Fixed CLUTs…
//
resource 'node' (4280, "_FBVFixedCLUTLCD") {{
  blocksize{};                                               // Physical Block Size.
                
  longs{{32+4;}};                                            // ctSeed
  words{{$0000;}};                                           // ctFlags
  words{{$000F;}};                                           // ctSize (n - 1)
                
  words{{$0000;$FFFF;$FFFF;$FFFF;}};                         // value, r,g,b (white entry).
  words{{$0001;$EEEE;$EEEE;$EEEE;}};                         // value, r,g,b (gray1 entry).
  words{{$0002;$DDDD;$DDDD;$DDDD;}};                         // value, r,g,b (gray2 entry).
  words{{$0003;$CCCC;$CCCC;$CCCC;}};                         // value, r,g,b (gray3 entry).
  words{{$0004;$BBBB;$BBBB;$BBBB;}};                         // value, r,g,b (gray4 entry).
  words{{$0005;$AAAA;$AAAA;$AAAA;}};                         // value, r,g,b (gray5 entry).
  words{{$0006;$9999;$9999;$9999;}};                         // value, r,g,b (gray6 entry).
  words{{$0007;$8888;$8888;$8888;}};                         // value, r,g,b (gray7 entry).
  words{{$0008;$7777;$7777;$7777;}};                         // value, r,g,b (gray8 entry).
  words{{$0009;$6666;$6666;$6666;}};                         // value, r,g,b (gray9 entry).
  words{{$000A;$5555;$5555;$5555;}};                         // value, r,g,b (grayA entry).
  words{{$000B;$4444;$4444;$4444;}};                         // value, r,g,b (grayB entry).
  words{{$000C;$3333;$3333;$3333;}};                         // value, r,g,b (grayC entry).
  words{{$000D;$2222;$2222;$2222;}};                         // value, r,g,b (grayD entry).
  words{{$000E;$1111;$1111;$1111;}};                         // value, r,g,b (grayE entry).
  words{{$000F;$0000;$0000;$0000;}};                         // value, r,g,b (black entry).
}};



resource 'node' (4285, "_FBVParmsHR") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4290, "_FBVParmsHR400") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR400;defmBounds_LHR400;defmBounds_BHR400;defmBounds_RHR400;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};

resource 'node' (4293, "_FBVParmsHR399") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR399;defmBounds_LHR399;defmBounds_BHR399;defmBounds_RHR399;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4295, "_FBVParmsFP") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMFPRB;}};                                         // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4300, "_FBVParmsGS") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{FBMGSRB;}};                                         // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4305, "_FBVParmsGS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{FBMGS560RB;}};                                      // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4310, "_FBVParmsGF") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{FBMGFRB;}};                                         // physRowBytes
  words{{defmBounds_TGF;defmBounds_LGF;defmBounds_BGF;defmBounds_RGF;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGF;}};                                          // bmHRes
  longs{{VResGF;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4315, "_FBVParmsSE") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMSERB;}};                                         // physRowBytes
  words{{defmBounds_TSE;defmBounds_LSE;defmBounds_BSE;defmBounds_RSE;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResSE;}};                                          // bmHRes
  longs{{VResSE;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4320, "_FBVParms_DAFB_640by480") {{
  include{l{"_FBVParms_V8_HRa"}};
}};

resource 'node' (4325, "_FBVParms_V8_HRa") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4330, "_FBVParms_V8_HRb") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4335, "_FBVParms_DAFB_GS") {{
  include{l{"_FBVParms_V8_GSa"}};
}};

resource 'node' (4340, "_FBVParms_V8_GSa") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4345, "_FBVParms_V8_GSb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4350, "_FBVParms_V8_A2Ema") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4355, "_FBVParms_V8_A2Emb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4360, "_FBVParms_DAFB_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4365, "_FBVParms_DAFB_FP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_512_RB;}};
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};
  longs{{VResFP;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4370, "_FBVParms_Civic_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1152_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4375, "_FBVParms_DAFB_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_576_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4380, "_FBVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4385, "_FBVParms_Civic_GS560") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4390, "_FBVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4395, "_FBVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_832_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4400, "_FBVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4405, "_FBVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB4;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4410, "_FBVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB4;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4415, "_FBVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4420, "_FBVParms_DAFB_PALSTconv") {{
  blocksize{};
  longs{{defmPALSTB4Conv;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4425, "_FBVParms_DAFB_PALFFconv") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{4;}};
  words{{defCmpCount;}};
  words{{4;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4430, "_FBVParmsLCD") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{FBMLCDRB;}};                                        // physRowBytes
  words{{defmBounds_TLCD;defmBounds_LLCD;defmBounds_BLCD;defmBounds_RLCD;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLCD;}};                                         // bmHRes
  longs{{VResLCD;}};                                         // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{4;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{4;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


//-------------------------------------------------------------
//               Eight-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (4440, "_EBMHR") {{
  mVidParams,       l{"_EBVParmsHR"};						// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4445, "_EBMHR400") {{
  mVidParams,       l{"_EBVParmsHR400"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};

resource 'vmod' (4447, "_EBMHR399") {{
  mVidParams,       l{"_EBVParmsHR399"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4450, "_EBMFP") {{
  mVidParams,       l{"_EBVParmsFP"};						// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesFP};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4455, "_EBMGS") {{
  mVidParams,       l{"_EBVParmsGS"};						// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4460, "_EBMGS560") {{
  mVidParams,       l{"_EBVParmsGS560"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4465, "_EBMGF") {{
  mVidParams,       l{"_EBVParmsGF"};						// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesGF};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                     	// device type
}};


resource 'vmod' (4470, "_EBMSE") {{
  mVidParams,       l{"_EBVParmsSE"};						// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesSE};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4475, "_EBM_V8_HR") {{
  mVidParams,       l{"_EBVParms_V8_HR"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesHR};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4480, "_EBM_V8_GSa") {{
  mVidParams,       l{"_EBVParms_V8_GSa"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4485, "_EBM_V8_GSb") {{
  mVidParams,       l{"_EBVParms_V8_GSb"};					// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesGS};                       	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4490, "_EBM_V8_A2Ema") {{
  mVidParams,       l{"_EBVParms_V8_A2Ema"};				// offset to vid parameters for this configuration
  mPageCnt,         d{EBMPagesA2Em};                     	// number of video pages in this configuration
  mDevType,         d{defmDevType};                      	// device type
}};


resource 'vmod' (4495, "_EBM_Civic_19") {{
  mVidParams,       l{"_EBVParms_Civic_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4500, "_EBM_DAFB_19") {{
  mVidParams,       l{"_EBVParms_DAFB_19"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4505, "_EBM_Civic_FP") {{
  include{l{"_EBM_DAFB_FP"}};
}};

resource 'vmod' (4510, "_EBM_DAFB_FP") {{
  mVidParams,       l{"_EBVParms_DAFB_FP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4515, "_EBM_Civic_2P") {{
  include{l{"_EBM_DAFB_2P"}};
}};

resource 'vmod' (4520, "_EBM_DAFB_2P") {{
  mVidParams,       l{"_EBVParms_DAFB_2P"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4525, "_EBM_Civic_GF") {{
  include{l{"_EBM_DAFB_LP"}};
}};

resource 'vmod' (4530, "_EBM_DAFB_LP") {{
  mVidParams,       l{"_EBVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4535, "_EBM_Civic_NTSCSTconv") {{
  include{l{"_EBM_Civic_NTSCST"}};
}};

resource 'node' (4540, "_EBM_Civic_NTSCST") {{
  include{l{"_EBM_Civic_GS"}};
}};

resource 'node' (4545, "_EBM_Civic_GS") {{
  include{l{"_EBM_DAFB_GS"}};
}};

resource 'vmod' (4550, "_EBM_DAFB_GS") {{
  mVidParams,       l{"_EBVParms_DAFB_GS"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4555, "_EBM_Civic_GS560") {{
  mVidParams,       l{"_EBVParms_Civic_GS560"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4560, "_EBM_Civic_PALSTConv") {{
  include{l{"_EBM_Civic_PALST"}};
}};

resource 'node' (4565, "_EBM_Civic_PALST") {{
  include{l{"_EBM_Civic_NTSCFFConv"}};
}};

resource 'node' (4570, "_EBM_Civic_NTSCFFConv") {{
  include{l{"_EBM_Civic_NTSCFF"}};
}};

resource 'node' (4575, "_EBM_Civic_NTSCFF") {{
  include{l{"_EBM_Civic_VGA"}};
}};

resource 'node' (4580, "_EBM_Civic_VGA") {{
  include{l{"_EBM_Civic_HR"}};
}};

resource 'node' (4585, "_EBM_Civic_HR") {{
  include{l{"_EBM_DAFB_NTSCFF"}};
}};

resource 'node' (4590, "_EBM_DAFB_NTSCFF") {{
  include{l{"_EBM_DAFB_NTSCFFconv"}};
}};

resource 'node' (4595, "_EBM_DAFB_NTSCFFconv") {{
  include{l{"_EBM_DAFB_VGA"}};
}};

resource 'node' (4600, "_EBM_DAFB_VGA") {{
  include{l{"_EBM_DAFB_HR"}};
}};

resource 'vmod' (4605, "_EBM_DAFB_HR") {{
  mVidParams,       l{"_EBVParms_DAFB_640by480"};			// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4610, "_EBM_Civic_HR400") {{
  mVidParams,       l{"_EBVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};

                
resource 'vmod' (4615, "_EBM_Civic_HRMAZ") {{
  mVidParams,       l{"_EBVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4620, "_EBM_Civic_SVGA") {{
  include{l{"_EBM_DAFB_SVGA"}};
}};

resource 'vmod' (4625, "_EBM_DAFB_SVGA") {{
  mVidParams,       l{"_EBVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4630, "_EBM_DAFB_NTSCST") {{
  include{l{"_EBM_DAFB_NTSCSTconv"}};
}};

resource 'vmod' (4635, "_EBM_DAFB_NTSCSTconv") {{
  mVidParams,       l{"_EBVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4640, "_EBM_DAFB_PALST") {{
  mVidParams,       l{"_EBVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'vmod' (4645, "_EBM_DAFB_PALSTconv") {{
  mVidParams,       l{"_EBVParms_DAFB_PALSTconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4650, "_EBM_Civic_PALFF") {{
  include{l{"_EBM_DAFB_PALFF"}};
}};

resource 'vmod' (4655, "_EBM_DAFB_PALFF") {{
  mVidParams,       l{"_EBVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4660, "_EBM_Civic_PALFFconv") {{
  include{l{"_EBM_DAFB_PALFFconv"}};
}};

resource 'vmod' (4665, "_EBM_DAFB_PALFFconv") {{
  mVidParams,       l{"_EBVParms_DAFB_PALFFconv"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};


resource 'node' (4670, "_EBVParmsHR") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{EBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4675, "_EBVParmsHR400") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{EBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR400;defmBounds_LHR400;defmBounds_BHR400;defmBounds_RHR400;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};

resource 'node' (4678, "_EBVParmsHR399") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{EBMHRRB;}};                                         // physRowBytes
  words{{defmBounds_THR399;defmBounds_LHR399;defmBounds_BHR399;defmBounds_RHR399;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4680, "_EBVParmsFP") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{EBMFPRB;}};                                         // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4685, "_EBVParmsGS") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{EBMGSRB;}};                                         // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4690, "_EBVParmsGS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{EBMGS560RB;}};                                      // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4695, "_EBVParmsGF") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{EBMGFRB;}};                                         // physRowBytes
  words{{defmBounds_TGF;defmBounds_LGF;defmBounds_BGF;defmBounds_RGF;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGF;}};                                          // bmHRes
  longs{{VResGF;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4700, "_EBVParmsSE") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{EBMSERB;}};                                         // physRowBytes
  words{{defmBounds_TSE;defmBounds_LSE;defmBounds_BSE;defmBounds_RSE;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResSE;}};                                          // bmHRes
  longs{{VResSE;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4705, "_EBVParms_DAFB_640by480") {{
  include{l{"_EBVParms_V8_HR"}};
}};

resource 'node' (4710, "_EBVParms_V8_HR") {{
  blocksize{};                                               // physical Block Size

  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4715, "_EBVParms_DAFB_GS") {{
  include{l{"_EBVParms_V8_GSa"}};
}};

resource 'node' (4720, "_EBVParms_V8_GSa") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4725, "_EBVParms_V8_GSb") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_512_RB;}};                                       // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4730, "_EBVParms_V8_A2Ema") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TA2Em;defmBounds_LA2Em;defmBounds_BA2Em;defmBounds_RA2Em;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{defPixelType;}};                                    // bmPixelType
  words{{8;}};                                               // bmPixelSize
  words{{defCmpCount;}};                                     // bmCmpCount
  words{{8;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4733, "_EBVParms_Civic_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1152_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};

resource 'node' (4735, "_EBVParms_DAFB_19") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};
  longs{{VRes19;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4740, "_EBVParms_DAFB_FP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};
  longs{{VResFP;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4745, "_EBVParms_DAFB_2P") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_1152_RB;}};
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};
  longs{{VRes2P;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4750, "_EBVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4755, "_EBVParms_Civic_GS560") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4760, "_EBVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1024_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4765, "_EBVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_832_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4770, "_EBVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4775, "_EBVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB8;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4780, "_EBVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB8;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4785, "_EBVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_832_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4790, "_EBVParms_DAFB_PALSTconv") {{
  blocksize{};
  longs{{defmPALSTB8Conv;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (4795, "_EBVParms_DAFB_PALFFconv") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_1024_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{defPixelType;}};
  words{{8;}};
  words{{defCmpCount;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


//-------------------------------------------------------------
//               Sixteen-Bit per pixel parameters
//-------------------------------------------------------------

//** WARNING: Added an 0xff000000 entry at end.
resource 'vmod' (4800, "_D16BMHR") {{
  mVidParams,       l{"_D16BVParmsHR"};						// offset to vid parameters for this configuration
  mPageCnt,         d{D16BMPagesHR};                     	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (4805, "_D16BMHR400") {{
  mVidParams,       l{"_D16BVParmsHR400"};					// offset to vid parameters for this configuration
  mPageCnt,         d{D16BMPagesHR};                     	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};

resource 'vmod' (4807, "_D16BMHR399") {{
  mVidParams,       l{"_D16BVParmsHR399"};					// offset to vid parameters for this configuration
  mPageCnt,         d{D16BMPagesHR};                     	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'node' (4810, "_D16BMGS") {{
  include{l{"_D16BM_V8_GS"}};
}};

resource 'vmod' (4815, "_D16BM_V8_GS") {{
  mVidParams,       l{"_D16BVParms_V8_GS"};					// offset to vid parameters for this configuration
  mPageCnt,         d{D16BMPagesGS};                     	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (4820, "_D16BMGS560") {{
  mVidParams,       l{"_D16BVParms_GS560"};					// offset to vid parameters for this configuration
  mPageCnt,         d{D16BMPagesGS};                     	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (4825, "_D16BM_Civic_19") {{
  mVidParams,       l{"_D16BVParms_Civic_19"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_Civic};                   	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (4830, "_D16BM_DAFB_19") {{
  mVidParams,       l{"_D16BVParms_DAFB_19"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (4835, "_D16BM_DAFB_FP") {{
  mVidParams,       l{"_D16BVParms_DAFB_FP"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};

                
resource 'vmod' (4840, "_D16BM_Civic_FP") {{
  mVidParams,       l{"_D16BVParms_Civic_FP"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_Civic};                   	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'node' (4845, "_D16BM_Civic_2P") {{
  include{l{"_D16BM_DAFB_2P"}};
}};

resource 'vmod' (4850, "_D16BM_DAFB_2P") {{
  mVidParams,       l{"_D16BVParms_DAFB_2P"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'node' (4855, "_D16BM_Civic_GF") {{
  include{l{"_D16BM_DAFB_LP"}};
}};

resource 'vmod' (4860, "_D16BM_DAFB_LP") {{
  mVidParams,       l{"_D16BVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (4865, "_D16BM_Civic_NTSCST") {{
  include{l{"_D16BM_Civic_GS"}};
}};

resource 'node' (4870, "_D16BM_Civic_GS") {{
  include{l{"_D16BM_DAFB_GS"}};
}};

resource 'vmod' (4875, "_D16BM_DAFB_GS") {{
  mVidParams,       l{"_D16BVParms_DAFB_GS"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};

    
resource 'vmod' (4880, "_D16BM_Civic_GS560") {{
  mVidParams,       l{"_D16BVParms_Civic_GS560"};			// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_Civic};                  	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};

                
resource 'node' (4885, "_D16BM_Civic_PALST") {{
  include{l{"_D16BM_Civic_NTSCFF"}};
}};

resource 'vmod' (4890, "_D16BM_Civic_NTSCFF") {{
  mVidParams,       l{"_D16BVParms_Civic_NTSCFF"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'node' (4895, "_D16BM_Civic_VGA") {{
  include{l{"_D16BM_Civic_HR"}};
}};

resource 'node' (4900, "_D16BM_Civic_HR") {{
  include{l{"_D16BM_DAFB_NTSCFF"}};
}};

resource 'node' (4905, "_D16BM_DAFB_NTSCFF") {{
  include{l{"_D16BM_DAFB_VGA"}};
}};

resource 'node' (4910, "_D16BM_DAFB_VGA") {{
  include{l{"_D16BM_DAFB_HR"}};
}};

resource 'vmod' (4915, "_D16BM_DAFB_HR") {{
  mVidParams,       l{"_D16BVParms_DAFB_640by480"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};

                                
resource 'vmod' (4920, "_D16BM_Civic_HR400") {{
  mVidParams,       l{"_D16BVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};

                
resource 'vmod' (4925, "_D16BM_Civic_HRMAZ") {{
  mVidParams,       l{"_D16BVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'node' (4930, "_D16BM_Civic_SVGA") {{
  include{l{"_D16BM_DAFB_SVGA"}};
}};

resource 'vmod' (4935, "_D16BM_DAFB_SVGA") {{
  mVidParams,       l{"_D16BVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (4940, "_D16BM_DAFB_NTSCST") {{
  mVidParams,       l{"_D16BVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (4945, "_D16BM_DAFB_PALST") {{
  mVidParams,       l{"_D16BVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (4950, "_D16BM_Civic_PALFF") {{
  include{l{"_D16BM_DAFB_PALFF"}};
}};

resource 'vmod' (4955, "_D16BM_DAFB_PALFF") {{
  mVidParams,       l{"_D16BVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (4960, "_D16BVParmsHR") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{D16BMHRRB;}};                                       // physRowBytes
  words{{defmBounds_THR;defmBounds_LHR;defmBounds_BHR;defmBounds_RHR;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4965, "_D16BVParmsHR400") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{D16BMHRRB;}};                                       // physRowBytes
  words{{defmBounds_THR400;defmBounds_LHR400;defmBounds_BHR400;defmBounds_RHR400;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};

resource 'node' (4967, "_D16BVParmsHR399") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{D16BMHRRB;}};                                       // physRowBytes
  words{{defmBounds_THR399;defmBounds_LHR399;defmBounds_BHR399;defmBounds_RHR399;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResHR;}};                                          // bmHRes
  longs{{VResHR;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4970, "_D16BVParms_DAFB_GS") {{
  include{l{"_D16BVParms_V8_GS"}};
}};

resource 'node' (4975, "_D16BVParms_V8_GS") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{V8_1024_RB;}};                                      // physRowBytes
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4980, "_D16BVParms_GS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{D16BMGS560RB;}};                                    // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4985, "_D16BVParms_Civic_19") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{Civic_2560_RB;}};                                   // physRowBytes
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};                                          // bmHRes
  longs{{VRes19;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4990, "_D16BVParms_DAFB_19") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{DAFB_2048_RB;}};                                    // physRowBytes
  words{{defmBounds_T19;defmBounds_L19;defmBounds_B19;defmBounds_R19;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes19;}};                                          // bmHRes
  longs{{VRes19;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (4995, "_D16BVParms_DAFB_FP") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{DAFB_2048_RB;}};                                    // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (5000, "_D16BVParms_Civic_FP") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{Civic_1280_RB;}};                                   // physRowBytes
  words{{defmBounds_TFP;defmBounds_LFP;defmBounds_BFP;defmBounds_RFP;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResFP;}};                                          // bmHRes
  longs{{VResFP;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (5005, "_D16BVParms_DAFB_2P") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{DAFB_2304_RB;}};                                    // physRowBytes
  words{{defmBounds_T2P;defmBounds_L2P;defmBounds_B2P;defmBounds_R2P;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HRes2P;}};                                          // bmHRes
  longs{{VRes2P;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (5010, "_D16BVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_1664_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5015, "_D16BVParms_Civic_GS560") {{
  blocksize{};                                               // physical Block Size
  longs{{defmBaseOffset;}};
  words{{Civic_1280_RB;}};                                   // physRowBytes
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};                                      // bmVersion
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};                                          // bmHRes
  longs{{VResGS;}};                                          // bmVRes
  words{{ChunkyDirect;}};                                    // bmPixelType
  words{{16;}};                                              // bmPixelSize
  words{{3;}};                                               // bmCmpCount
  words{{5;}};                                               // bmCmpSize
  longs{{defmPlaneBytes;}};                                  // bmPlaneBytes
}};


resource 'node' (5020, "_D16BVParms_Civic_NTSCFF") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1280_RB;}};
  words{{0;0;480;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5025, "_D16BVParms_DAFB_640by480") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_2048_RB;}};
  words{{0;0;480;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5030, "_D16BVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1280_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5035, "_D16BVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_1664_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5040, "_D16BVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_1664_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5045, "_D16BVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB16;}};
  words{{DAFB_2048_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5050, "_D16BVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB16;}};
  words{{DAFB_1664_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5055, "_D16BVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_1664_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{ChunkyDirect;}};
  words{{16;}};
  words{{3;}};
  words{{5;}};
  longs{{defmPlaneBytes;}};
}};


//-------------------------------------------------------------
//               ThirtyTwo-Bit per pixel parameters
//-------------------------------------------------------------

resource 'node' (5060, "_D32BM_Civic_GF") {{
  include{l{"_D32BM_DAFB_LP"}};
}};

resource 'vmod' (5065, "_D32BM_DAFB_LP") {{
  mVidParams,       l{"_D32BVParms_DAFB_LP"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5070, "_D32BM_Civic_NTSCST") {{
  include{l{"_D32BM_Civic_GS"}};
}};

resource 'node' (5075, "_D32BM_Civic_GS") {{
  include{l{"_D32BM_DAFB_GS"}};
}};

resource 'vmod' (5080, "_D32BM_DAFB_GS") {{
  mVidParams,       l{"_D32BVParms_DAFB_GS"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (5085, "_D32BM_Civic_GS560") {{
  mVidParams,       l{"_D32BVParms_Civic_GS560"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5090, "_D32BM_Civic_PALST") {{
  include{l{"_D32BM_Civic_NTSCFF"}};
}};

resource 'node' (5095, "_D32BM_Civic_NTSCFF") {{
  include{l{"_D32BM_Civic_VGA"}};
}};

resource 'node' (5100, "_D32BM_Civic_VGA") {{
  include{l{"_D32BM_Civic_HR"}};
}};

resource 'vmod' (5105, "_D32BM_Civic_HR") {{
  mVidParams,       l{"_D32BVParms_Civic_640by480"};		// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (5110, "_D32BM_Civic_HR400") {{
  mVidParams,       l{"_D32BVParms_Civic_HR400"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};

                
resource 'vmod' (5115, "_D32BM_Civic_HRMAZ") {{
  mVidParams,       l{"_D32BVParms_Civic_HRMAZ"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5120, "_D32BM_DAFB_NTSCFF") {{
  include{l{"_D32BM_DAFB_VGA"}};
}};

resource 'node' (5125, "_D32BM_DAFB_VGA") {{
  include{l{"_D32BM_DAFB_HR"}};
}};

resource 'vmod' (5130, "_D32BM_DAFB_HR") {{
  mVidParams,       l{"_D32BVParms_DAFB_640by480"};		// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5135, "_D32BM_Civic_SVGA") {{
  include{l{"_D32BM_DAFB_SVGA"}};
}};

resource 'vmod' (5140, "_D32BM_DAFB_SVGA") {{
  mVidParams,       l{"_D32BVParms_DAFB_SVGA"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (5145, "_D32BM_DAFB_NTSCST") {{
  mVidParams,       l{"_D32BVParms_DAFB_NTSCST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (5150, "_D32BM_DAFB_PALST") {{
  mVidParams,       l{"_D32BVParms_DAFB_PALST"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5155, "_D32BM_Civic_PALFF") {{
  include{l{"_D32BM_DAFB_PALFF"}};
}};

resource 'vmod' (5160, "_D32BM_DAFB_PALFF") {{
  mVidParams,       l{"_D32BVParms_DAFB_PALFF"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (5165, "_D32BVParms_DAFB_LP") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_3328_RB;}};
  words{{defmBounds_TLP;defmBounds_LLP;defmBounds_BLP;defmBounds_RLP;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResLP;}};
  longs{{VResLP;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5170, "_D32BVParms_DAFB_GS") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_2048_RB;}};
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS;defmBounds_RGS;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5175, "_D32BVParms_Civic_GS560") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_2560_RB;}};
  words{{defmBounds_TGS560;defmBounds_LGS560;defmBounds_BGS560;defmBounds_RGS560;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResGS;}};
  longs{{VResGS;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};



resource 'node' (5180, "_D32BVParms_DAFB_640by480") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_4096_RB;}};
  words{{0;0;480;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5185, "_D32BVParms_Civic_640by480") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_2560_RB;}};
  words{{0;0;480;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5190, "_D32BVParms_Civic_HR400") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_2560_RB;}};
  words{{0;0;400;640;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5195, "_D32BVParms_Civic_HRMAZ") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{Civic_3328_RB;}};
  words{{0;0;512;704;}};                                     // who needs equates in a file of this size?
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5200, "_D32BVParms_DAFB_SVGA") {{
  blocksize{};

  longs{{defmBaseOffset;}};
  words{{DAFB_3328_RB;}};
  words{{defmBounds_TSVGA;defmBounds_LSVGA;defmBounds_BSVGA;defmBounds_RSVGA;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{$00480000;}};                                       // 72 hdpi
  longs{{$00480000;}};                                       // 72 vdpi
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5205, "_D32BVParms_DAFB_NTSCST") {{
  blocksize{};
  longs{{defmNTSCSTB32;}};
  words{{DAFB_4096_RB;}};
  words{{defmBounds_TNTSCST;defmBounds_LNTSCST;defmBounds_BNTSCST;defmBounds_RNTSCST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResNTSC;}};
  longs{{VResNTSC;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5210, "_D32BVParms_DAFB_PALST") {{
  blocksize{};
  longs{{defmPALSTB32;}};
  words{{DAFB_3328_RB;}};
  words{{defmBounds_TPALST;defmBounds_LPALST;defmBounds_BPALST;defmBounds_RPALST;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};


resource 'node' (5215, "_D32BVParms_DAFB_PALFF") {{
  blocksize{};
  longs{{defmBaseOffset;}};
  words{{DAFB_3328_RB;}};
  words{{defmBounds_TPALFF;defmBounds_LPALFF;defmBounds_BPALFF;defmBounds_RPALFF;}};
  words{{defVersion;}};
  words{{0;}};                                               // packType not used
  longs{{0;}};                                               // packSize not used
  longs{{HResPAL;}};
  longs{{VResPAL;}};
  words{{ChunkyDirect;}};
  words{{32;}};
  words{{3;}};
  words{{8;}};
  longs{{defmPlaneBytes;}};
}};

resource 'long' (2650, "_timingInvalid")		{timingInvalid};
resource 'long' (2651, "_timingApple12")		{timingApple12};
resource 'long' (2652, "_timingApple12x")		{timingApple12x};
resource 'long' (2653, "_timingApple13")		{timingApple13};
resource 'long' (2654, "_timingApple13x")		{timingApple13x};
resource 'long' (2655, "_timingAppleVGA")		{timingAppleVGA};
resource 'long' (2656, "_timingApple15")		{timingApple15};
resource 'long' (2657, "_timingApple16")		{timingApple16};

//-------------------------------------------------------------
//               Extended Format/Header Block
//-------------------------------------------------------------
                
resource 'xfrm' (6000, "Root") {
	l{"_sSuperInitRec"},
	l{"_sRsrcSuperDir"},
	l{"_sRsrcUnknownDir"},
	1,								// RomRevision
	appleFormat,
	0,
	0x0F							// Byte lanes
};
	
#if 0				
resource 'node' (6000, "Root") {{
	include{l{"_RootDirectory"}};
	long{testPattern};
	byte{0};
	// Stuff below is part of regular format block.
	offset{l{"_sRsrcUnknownDir"}};
    romlength{};  /* ROM Length  */
    romcrc{};  /* CRC  */
    byte{1};
    byte{1};
    long{testPattern};
    byte{0};
    byte{0x0F};
}};

resource 'list' (6001, "_RootDirectory") {{
	appleFormat,	include{a{"OffsetTo_sSuperInitRec"}};
	sSuperDir,		l{"_sRsrcSuperDir"};
}};
				

#endif
