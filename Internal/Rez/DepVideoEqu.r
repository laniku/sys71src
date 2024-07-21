/*
	File:		DepVideoEqu.r

   	Contains:   These are the configuration ROM equates that are specific only to 
   	            built-in video.  This includes mode information, sResource IDs,
    	           etc., etc….

	Written by:	David Fung/Mike Puckett, September 25, 1990

	Copyright:	© 1991-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM32>	 1/24/94	rab		Sync this file with DepVideoEqu.a. This fixes the video problems
									on DAFB based CPUs…
	  <SM31>	  1/4/94	PN		Add the rest of support for CSC panels from KAOS.
	  <SM30>	12/14/93	PN		Update the CPU resources ID to match DepVideoEqu.a.
	  <SM29>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines
	  <SM28>	12-06-93	jmp		Removed the driver version equates since they aren’t used here
									anyway.
	  <SM27>	11/10/93	fau		Update from SuperMunggio <SMG2>.
	  <SMG2>	10/27/93	fau		Added ATI directory support.
	  <SM26>	 11/9/93	KW		added srsrc's for stp machines
	  <SM25>	 11/8/93	JRH		boxDBLite16 is now boxPowerBookDuo250. boxDBLite20 is now
									boxPenLite.
	  <SM24>	 10/6/93	RC		took out PDM EVT1 support
	  <SM23>	08-16-93	jmp		Brought many of the board sRsrc IDs in this file up-to-date with
									DepVideoEqu.a.
	  <SM22>	 8/12/93	KW		adding two more smurf wombats
	  <SM21>	 8/11/93	KW		adding some new srsrc equates for some new smurf machines
	  <SM20>	08-06-93	jmp		Updated the timing constants used by the Display Manager for
									non-intelligent displays.
	  <SM19>	08-03-93	jmp		Began cleaning up the support for dynamically allocating RAM in
									PDM for video, as well as added initial support for the three
									new Apple multiscan displays.
		<18>	  6/1/93	IH		Add timing info for video modes
	  <SM17>	 4/29/93	fau		Synchronized with Ludwig.
	   <LW7>	 4/14/93	fau		Changes due to the new way of doing things in Civic: renumbered
									and deleted some of the spID's, added some more variables to the
									Civic structures.
	  <SM16>	04-07-93	jmp		Added the multiscan family mode to the Sonora/PDM sResource IDs
									to support the Display Manager.
	  <SM15>	  4/6/93	fau		Synchronized with Ludwig, yet again.
	   <LW5>	  4/5/93	fau		Added the Puma support in the video parameters for Civic.
	  <SM14>	  4/5/93	chp		Synchronize with Ludwig.
	  <SM13>	04-01-93	jmp		Added support for the no-VRAM case for Sonora/PDM.
	   <LW4>	 3/22/93	fau		Added sRsrc_BdTempest.
	  <SM12>	  3/5/93	CCH		Added sRsrc ID for Mace on Sonora/PDM.
	   <LW3>	 2/24/93	fau		Added the sRsrc_SCSI_Transport equate.
	   <LW2>	 2/16/93	fau		Updated it to reflect the changes in DepVideoEqu.a (there should
									be a tool).  Essentially, I renumbered and added spID's for
									Civic-based CPU's.
	  <SM11>	01-12-93	jmp		Added initial support for CSC.
	  <SM10>	01-11-93	jmp		Updated a *few* things from HORROR; still need to do the BoxFlag
									stuff (but would have to update InternalOnlyEqu.r).
	   <SM9>	12/23/92	RC		Added Support for Smurf on Wombat
	   <SM8>	 12/4/92	fau		Changed sRsrc_BdCyclone to use BoxCyclone33 instead of
									BoxCyclone.
	   <SM7>	11/11/92	fau		Added support for Clifton on Civic-based CPU's and a bit in PRAM
									for composite out.
	   <SM6>	10-29-92	jmp		Added support for 33 MHz WLCD.
	   <SM5>	10-25-92	HY		Added support for LCII boxflag.
	   <SM4>	10-17-92	jmp		Added support for PDM.
	   <SM3>	 10/8/92	fau		Added support for Civic's new 19" rowbytes/baseaddress.
	   <SM2>	 10/6/92	GDW		Changed CPU resource IDs and added sRsrc_CPUMac040

*/
//
//     <SM17>      8/9/92    CCH     Added support for video on Quadras with RISC cards.
//     <SM16>    07-14-92    jmp     (jmp,H41) Added in support to make the DAFB part of built-in
//                                   video work correctly among Spike, Eclipse, Zydeco, and all
//                                   Wombat/WLCD CPUs.
//                                   (jmp,H40) Fixed the DAFBBWrite macro to work better when being
//                                   run via the Cub card.
//                                   (jmp,H39) Tightened and eliminated a number of the DAFB macros.
//                                   Also, added a pRAM bit for remembering whether AltSense was
//                                   enabled the last reboot. (At the momment, this bit is only used
//                                   for DAFB because it puts out the sync-on-green signal, and we
//                                   might want to keep the same sync-on-green state even though the
//                                   AltSense code changed.  I don’t think Vail or Cyclone need to
//                                   know that AltSense was enabled last reboot, but they could use
//                                   this bit if they ever did.)
//                                   (jmp,H38) Made the DAFBReadSenseLines macro work better with
//                                   Wombat DAFBs (due to the fact that the WombatDAFB is not tied to
//                                   the ’040 reset instruction like other DAFB-based CPUs are).
//                                   (jmp,H37) Added yet another base-address constant for Wombat.
//                                   (jmp,H36) Needed some new base-address constants for Wombat.
//                                   (jmp,H35) Added first-pass support for the Wombat version of
//                                   DAFB.
//                                   (jmp,H34) Cleaned up the DAFB byte and word write macros, and a
//                                   fixed a minor bug in the DAFBIdle macro (the way it was
//                                   originally written, there could have been cases where the AC824A
//                                   would NOT have put back into “compatible” mode).
//     <SM15>     7/13/92    CCH     Modified DAFBBWrite macro to perform byte writes.
//     <SM14>     7/7/92     CSS     Change references for boxApollo to boxClassisII.
//     <SM13>      7/7/92    fau     Moved the equ for sRsrc_BdWombat20 to the correct location as
//                                   the boxWombat20 flag moved from 29 to 52.
//     <SM12>     6/26/92    fau     Remove DSP3210 sRsrc in Cyclone, since the DSP is not slot
//                                   manager-based anymore.  Added ID's for 12" and 13" monitor
//                                   support for composite out.
//     <SM11>     6/19/92    KW      (fau,P23) Moved DSP srsrc from $F0 to $F8.  We had reserved $40
//                                   id's for displays with video-in disabled, but only $30 for
//                                   displays with video-in disabled.  Changed it to $35 for each, so
//                                   video-in id's run all the way to $F7.  Added id's for Goldfish
//                                   out of composite.
//     <SM10>     6/18/92    KW      Rolled back in SM8
//      <SM9>     6/17/92    KW      Roll back to SM7
//      <SM8>     6/17/92    KW      (jmp,H34) Cleaned up the DAFB byte and word write macros, and a
//                                   fixed a minor bug in the DAFBIdle macro (the way it was
//                                   originally written, there could have been cases where the AC824A
//                                   would NOT have put back into “compatible” mode).
//                                   (jmp,H33) Eliminated yet even more of the old DAFBVidParams
//                                   fields, so I adjusted the data structures accordingly.
//                                   (jmp,H31) Updated the SonoraVidParams record to accomdate
//                                   Omega-2 and added some new burn-in constants.
//                                   (fau,P21) Added video-in equates for Vesuvio, Kong, Rubik, 19"
//                                   Display and all VGA families for Civic-based CPU's.
//      <SM7>      6/4/92    KW      (jmp,H30) Added some new data structures for describing the
//                                   newly-compacted DAFB vidParams.
//                                   (BG,H29) Changed various Wombat-style BoxFlag references to
//                                   their new, more descriptive names.
//                                   (jmp,H28) Eliminated support for the no-vRAM case in V8-base
//                                   systems.
//                                   (jmp,H27) Changed the “sRsrcZydecoDir” name to the more generic
//                                   “sRsrcBFBasedDir” (BF=BoxFlag) name.
//                                   (jmp,H26) Added some base-address constants for V8 to eliminate
//                                   the VideoInfo arrays in Universal.a.
//                                   (jmp,H25) Added some new CPU board ID constants (based on
//                                   BoxFlag), added some new DAFB constants for Wombat, and added
//                                   some conditionals for nuking the Apollo stuff and killing the
//                                   Slot Manager checksum of Slot $0’s DeclData as it’s somewhat
//                                   redundant.
//                                   KW Removed FirstVidMode,SecondVid etc since already in VideoEqu
//      <SM6>     5/21/92    RB      Making changes for Cyclone
//      <SM5>     5/17/92    kc      Roll in Horror changes. Comments follow:
//      <H24>    04/24/92    jmp     Added constants to support the “switch-on-the-fly” Rubik-512 to
//                                   Rubik-560 and vice-versa call for Sonora.
//      <H23>    04/20/92    jmp     Added constants to support the 640x400 mode of the HiRes
//                                   displays.
//      <H22>     3/17/92    SWC     Renamed boxDBLite->boxDBLite25 and boxDBLiteLC->boxDBLite33, and
//                                   added equates for boxDBLite16 and boxDBLite20.
//      <H21>    02/20/92    jmp     (jmp,Z27) Changed the DAFB clock-select equates from
//                                   Bset/clr-oriented to Bfins/Bfext-oriented.
//      <H20>    02/19/92    jmp     Changed the Condor references to Wombat.
//      <H19>     2/18/92    JC      Changed boxCarnation to boxCarnation33 and boxVail to boxVail25.
//      <H18>     2/17/92    SAM     Changed boxCondor to boxWombat.
//      <H17>    01/27/92    jmp     Moved some equates from DepVideoEqu.a to ROMEqu.a.
//      <H16>    01/22/92    jmp     (jmp,Z26) Renamed all the “NoConnect” equates to “AltSense.”
//      <H15>     1/14/92    SWC     Updated boxFlag labels to use shipping product names.
//      <H14>    01/11/92    jmp     Added equates for the newly-defined extended sense codes.
//      <H13>    12/19/91    jmp     Added the initial support for Rubik-560 mode for Sonora.
//      <H12>    12/17/91    jmp     Added a new baseAddr offset for Kong & Vesuvio on DAFB.
//      <H11>    12/16/91    HJR     Added Dartanian sRsrc_BdDartanian equate.
//      <H10>    12/12/91    jmp     Added more Sonora-related equates and some new DBLiteLC equates.
//       <H9>    11/27/91    jmp     Added massive amounts of Sonora equates.
//       <H8>    11/26/91    jmp     Added some GSC and DBLite equates.
//       <H7>    11/12/91    jmp     Defined two new DAFBFlag bits to indicate the size of vRam.
//       <H6>    11/05/91    jmp     Added more 19” display equates for DAFB.
//       <H5>    11/01/91    jmp     Added equates for (eventually) supporting 19” displays with
//                                   DAFB.
//       <H4>    10/29/91    jmp     Changed the Spike33 names to Condor.
//       <H3>    10/24/91    jmp     Added in constants to support the gray-scale DB-Lite (up to
//                                   4bpp) LCD display.
//       <H2>    10/24/91    jmp     Updating to Zydeco-TERROR version.
//      <SM4>      4/7/92    JSM     Roll-in changes from Reality:
//                                    <2>     3/24/92    JSM     Nuke more code names: boxAuroraCX25 is boxMacIIci, boxF19 is
//                                                               boxMacIIfx.
//      <SM3>     3/31/92    JSM     Rolled this file into Reality.
//      <SM2>     2/11/92    RB      Update to reflect the Zydeco changes (beta). Updated boxFlags
//      <SM1>    12/29/91    RB      first checked in
//   ----------------------------------------------------------------------
//   Zydeco History:
//       <26>    01/20/92    jmp     Renamed all the “NoConnect” equates to “AltSense.”
//       <25>    01/09/92    jmp     Added equates for the newly-defined extended sense codes.
//       <24>    12/17/91    jmp     Added a new baseAddr offset for Kong & Vesuvio on DAFB.
//       <23>    11/08/91    jmp     Defined two new DAFBFlag bits to indicate the size of vRam.
//       <22>    11/05/91    jmp     Added equates for supporting 19” Displays with DAFB.
//       <21>    10/16/91    jmp     Modified the DAFBIdle & DAFBReset macros to set & reset a flags
//                                   register saying whether DAFB video is active or not.  This was
//                                   added to support turning video back on immediately in the event
//                                   that the video driver was closed and needed to be opened again
//                                   during “normal” operation of the CPU.
//       <20>    09/17/91    jmp     When “grounding out” the ECL clock, we also needed to make sure
//                                   the 100 Mhz clock is shut off.  This 100 Mhz clock is controlled
//                                   by bit 9 (PIXSEL0) in the DAFB clock configuration register.  I
//                                   just added an equate for this.
//       <19>    09/17/91    jmp     Added support for “grounding out” the ECL clock signals in
//                                   software using the AMD-ACDC for Zydeco/Spike33 CPUs.
//       <18>    09/13/91    jmp     Added support for 16pp on Rubik displays when only 512K of vRAM
//                                   is around in preparation for Spike33s.
//       <17>     8/26/91    jmp     Added support for a Spike33-type box.
//       <16>     8/21/91    jmp     Changed all the Eclipse33 references to Zydeco.
//       <15>      8/9/91    jmp     Added equates to fix a problem with NTSC & PAL family modes
//                                   where changing the amount of vRAM didn’t cause DAFB’s part of
//                                   PrimaryInit to re-validate the SP_LastConfig pRAM byte.  Also,
//                                   added a boundary equate to distinguish 16bpp-capable DAFB sRsrcs
//                                   from non-16bb-capable sRsrcs.
//       <14>      8/7/91    jmp     Added 16bpp support for all applicable DAFB displays.
//       <13>     7/29/91    jmp     Added equates for supporting Eclipse33 (Zydeco) & TIM-LC.
//       <12>     7/13/91    jmp     Added constants to support extending the factory burn-in
//                                   no-connect code.
//       <11>     7/11/91    jmp     Added code to more intelligently handle the enabling & disabling
//                                   of page mode.
// ———————————————————————————————————————————————————————————————————————————————————————
//     Pre-Zydeco ROM comments begin here.
// ———————————————————————————————————————————————————————————————————————————————————————
//       <10>     6/29/91    jmp     Changed the DAFBDriver version number back to $00 from $01.
//        <9>     6/27/91    jmp     Added version number constants for the various DAFB revisions.
//        <8>     6/26/91    jmp     Rewrote the ACDC-whacking code to be more AC842A (AMD) friendly.
//        <7>     6/25/91    jmp     Fixed the problem where 16bpp was not sticking.
//        <6>     6/24/91    jmp     Added support for 16bpp Vesuvio & RGB Portrait displays.
//        <5>     6/17/91    jmp     Updated the base address offsets and rowbytes for NTSC, PAL,
//                                   SuperVGA, GoldFish, Kong, and Vesuvio in order to accomodate
//                                   Mitsubishi vRams.  Also, updated the MinorLength values to
//                                   accomodate the new base addresses and rowbytes.
//        <4>     5/25/91    jmp     The DAFBIdle macro was shutting off DAFB entirely.  For the most
//                                   part, this is NOT wrong; however, if we completely shut DAFB off
//                                   at driver close time, and someone reopens the driver before the
//                                   machine is restarted, we can’t get video going again without
//                                   going thru the entire DAFB reset cycle, which causes the screen
//                                   to jump.  So, I now just kill sync and video refresh, which does
//                                   exactly what I need.
//        <3>     5/24/91    jmp     Added support for sync-on-green in DAFB and cleaned up the
//                                   DAFBResetDelay macro.
//        <2>     5/22/91    jmp     Now enable/disable fast page mode depending on whether DAFB is
//                                   configured for row interleave vRam accesses.  I only added this
//                                   to the driver version of the DAFBSpeed macro because we don’t
//                                   need to do this in PrimaryInit.
//        <1>     5/22/91    jmp     Changed name to DepVideoEqu.a from RBVDepVideoEqu.a to reflect
//                                   the fact that this file is used by all built-in videos, not
//                                   just RBV.
//       <25>     5/15/91    jmp     Added DB-Lite support.  Also, had the wrong constant for
//                                   indexedSenseFP; should have been 1 not 5 (5 is for
//                                   indexedSenseRGBFP).  This caused the Portrait Display to not be
//                                   luminance-mapped when “Color” mode was turned on.
//       <24>     5/10/91    jmp     Added sRsrc constants for SuperVGA.  Aliased IsSlow to Is16 (bit
//                                   11) in GFlags for supporting 25 vs. 33 MHz CPU configs.  Added
//                                   new DAFBSpeed macros for PrimaryInit & Driver.  Code review
//                                   changes:  cleaned up the DAFB macros.
//       <23>     4/26/91    jmp     Added a new baseAddr offset constant for PAL convolved.
//       <22>     4/25/91    jmp     Updated dafb33MhzConfig constant to new value for 80ns VRam.
//       <21>     4/23/91    jmp     Added indexedSense codes for the 2P and FP displays, and fixed
//                                   the Minor/MajorLength values for non-convolved PAL were wrong
//                                   (i.e., they were zero).
//       <20>     4/15/91    djw     Add spId for functional video sRsrc's video attibutes (a data
//                                   field).
//       <19>      4/4/91    jmp     My previous “optimization” caused some DAFB 1 machines to hang.
//                                   So, I now read the DAFB test register 4 times, which could take
//                                   as long as 480 ns.  We only 320 ns DAFB reset writes (even on
//                                   DAFB 1s), so this should be okay.
//       <18>      4/3/91    jmp     Reduced the number of Nops in the DAFBResetDelay macro to two
//                                   (from eight).  I determined this value empirically; before, I
//                                   was just guessing based on Dale Adam’s spec.
//       <17>      4/1/91    jmp     SixteenBitGray & ThirtyTwoBitGray were inverted!
//       <16>     3/25/91    jmp     Added a record for Slot pRam.
//       <15>     3/18/91    jmp     Updated rowbytes constants for 32bpp PAL.
//       <14>      3/8/91    jmp     Added a 768 rowbytes constant, and made the defmBaseOffset
//                                   constants for PAL & NTSC more general.
//       <13>      3/4/91    jmp     Added equates (spIDs) for standard and inverse gamma tables.
//                                   Added equates for factory burn-in stuff.
//       <12>     2/25/91    jmp     Added DAFBSpeed macro for supporting 33Mhz DAFBs.
//       <11>     2/15/91    jmp     Added various comments and cleaned up file.  Added
//                                   “indexEntries” equate for the -1 modes of Get/SetEntries.  Also,
//                                   added macro for checking/setting 33Mhz operation of DAFB.
//       <10>     2/10/91    jmp     Updated NTSC and PAL data for 4/8bpp convolved.  Added
//                                   defmBaseOffset to screen clearing params.  Added in “Misc”
//                                   params to video params for ChkMode in driver.  The Rubik gamma
//                                   table contained the 4•8/8•24 gType id!  And updated GoldFish’s
//                                   clock parameters (to match those of the Portrait Display).
//        <9>      2/3/91    jmp     Added the new rowbytes values (ST/FF) for PAL.  Added
//                                   MinorLength values for NTSCFF/ST a,b and PALFF/ST a.  Added new
//                                   defmBaseOffsets for NTSCST and PALST.  Added sRsrc ID for 040
//                                   CPU family.  And added base address offset constant for NTSC and
//                                   PAL.
//        <8>     1/30/91    jmp     Added constants and macros to support the extended sense line
//                                   encodings.  Added a macro for doing DAFB resets.  Added NTSCFF
//                                   and NTSCST data.
//        <7>     1/24/91    jmp     Added some constants to support extended-sense-line displays.
//        <6>     1/21/91    jmp     Incremental change -- added support (spIDs) for monitors that
//                                   have both RGB and Mono-Only types.
//        <5>     1/15/91    DAF     Added DAFB equates (billions of them), updated SONIC equates,
//                                   moved some slot decl ROM type equates to ROMEqu.a. Also changed
//                                   video spIDs to new ranges.
//        <4>      1/9/91    JK      Added Sonic Ethernet, Eclipse and Spike support.
//        <3>    12/11/90    JJ      Mac LC: Change all box flag references for Mac LC to use symbol
//                                   boxMacLC.
//        <2>    12/11/90    HJR     Integration of V8 and Tim video into Terror Project.
//        <5>     6/12/90    JJ      Add support for Elsie Apple II emulation video modes.
//        <4>     4/30/90    JJ      Adding multiple board sRsrc support.
//        <3>      4/9/90    JJ      Rolling in changes from Reality.  Original comments below.
//        {4}      4/3/90    DAF     Added equates for support of Elsie Video features.
//        {3}      4/3/90    DF      Relocated driver private storage flag bit name equates here from
//                                   RBVDriver.a.  They are shared with the Elsie driver here now
//        <2>     2/15/90    CV      Rolling in changes from Reality. Original comments below.
//        {2}     2/14/90    DAF     Updated equates for integration with Elsie video code.
//      <2.0>     7/16/89    GMR     Rolling in changes from 'Reality'. Original 'Reality' version is
//                                   2.1. Original comments are below.
//      <2.1>     7/11/89    DAF     FOR AURORA BUILD - Added equates for 1MB RAM size and flag word
//                                   for non-16MHz machines
//      <2.0>     7/11/89    DAF     FOR AURORA BUILD - Relocated a lot of equates from here to
//                                   ROMEqu.a
//                7/10/89    DAF     Relocated many equates from this file to ROMEqu.a where they
//                                   really belong. Generally cleaned up file. Changed MinorLength
//                                   equates to be true size of frame buffer rather than rounded
//                                   size.
//      <1.9>     6/30/89    CSL     Updated CPUShift to place CPU sRsrc id's in the proper range
//      <1.8>     6/30/89    DAF     Added a number of new equates for the declaration ROM, including
//                                   board and CPU IDs
//                6/30/89    DAF     Corrected CPUShift to place the sRsrc directory entries in the
//                                   appropriate order.
//                6/28/89    DAF     Added equates for the monitor sense ID's. Added official board
//                                   and drHwIDs for RBV machines. Added false board IDs for other
//                                   CPUs. Corrected RAM lengths since MMU.a does 32K wraparounds on
//                                   frame buffer
//      <1.7>     5/27/89    DAF     Updated equates for minor length in each of the different Aurora
//                                   video modes
//      <1.6>     5/16/89    DAF     Updated equates to make video mode family names a superuser
//                                   feature
//                5/16/89    DAF     Added name dir shift value
//      <1.5>     5/15/89    DAF     Added some new equates in support of PrimaryInit and declData
//                                   changes
//                 5/6/89    DAF     Added sNameDirFlags, name ResIDs
//     <•1.4>     4/15/89    DAF     Added sGammaDirectory equate
//                4/15/89    DAF     Added sGammaDir
//      <1.3>     2/27/89    DAF     Removed A/UX 1.0 driver equates
//                2/27/89    DAF     Removed A/UX equates, added scrnInval definition for now.
//      <1.2>     2/21/89    djw     deleted equates for new slot manager temporarily put in this
//                                   file
//      <1.1>    11/14/88    DAF     Removed redundant hardware equates (now in HardwareEqu.a)
//      <1.0>    11/11/88    DAF     Adding to EASE for the first time.
//               10/31/88    DAF     Integrated some equates from the old DeclData.a file
//               10/26/88    DAF     New today.

// Various build flags…
//
#define ApolloSupported          0           // Apollo isn’t really supported by Horror, so no use carrying it around.
#define RBVSupported             0           // Apollo isn’t really supported by Horror, so no use carrying it around.
#define TIMSupported             0           // Apollo isn’t really supported by Horror, so no use carrying it around.
#define CheckSumEnabled          0           // No need to have the SlotManager checksum us since the ROM start code does it, too!

// Driver Version Numbers…
//
#define CurRBVDrvrVersion        $0000       // Word-sized version numbers (like 'vers' resources).
#define CurElsieDrvrVersion      $0000
#define CurV8DrvrVersion         $0001
#define CurTimDrvrVersion        $0000
#define CurDAFBDrvrVersion       $0007       // Spike/Eclipse are 0.0, Zydeco is 0.1/0.2, Wombat is 0.3.
#define CurApolloDrvrVersion     $0000
#define CurDBLiteDrvrVersion     $0001
#define CurSonoraDrvrVersion     $0001
#define CurCSCDrvrVersion	     $0001   
#define CurCivicDrvrVersion      $0001   

// Misc Equates…
//
#define kMegRAM                  $100000     // constant for 1Mb
#define k1536KvRAM               $180000     // constant for 1.5Mb        

#define k256KvRAM                ((256*1024))  // constant for 256Kb
#define k512KvRAM                ((512*1024))  // constant for 512Kb
#define k1MvRAM                  ((1024*1024)) // constant for 1MB
#define k2MvRAM                  (2*k1MvRAM)   // constant for 2MB

#define seSuccess                1           // sucessful sExec

#define ROMRevLevel              5             // sucessful sExec

#define CPUShift                 $B0         // add this value to board spIDs to
                                        //   create CPUspIDs

#define ClrDepthBitsMask         $F8         // bit mask to clear V8 and Ariel control register screen
                                        //   depth bits (top 5 bits)
                                        
#define indexEntries             (-1)          // -1 mode for Get/SetEntries.
#define alphaEntries             (-2)          // -2 mode for Get/SetEntries (uses alpha channel in CLUT)

#define burnInSiz                $0004       // Number of bytes in pRAM for burn-in signature.
#define burnInLoc                $00FC       // Where burn-in signature starts in pRAM.
#define burnInSig                ('RNIN')      // The burn-in signature.
#define burnInSigAlt             ('SRNN')      // The alternate burn-in signature.

#define burnInSig12              ('RN12')      // These are the new burn-in signatures.  They
#define burnInSig13              ('RN13')      //   define all the Apple-produced displays.
#define burnInSig15              ('RN15')      //   We could define similar signatures for
#define burnInSig16              ('RN16')      //   things like VGA, NTSC, and PAL, but the
#define burnInSig19              ('RN19')      //   factory probably couldn’t use them anyway.
#define burnInSig21              ('RN21')

// Timing mode constants for Display Manager MultiMode support
// Corresponding	.h equates are in DisplaysPriv.h
//					.a equates are in DepVideoEqu.a
//					.r equates are in DepVideoEqu.r

#define timingInvalid			0			//  Unknown timing… force user to confirm.

#define timingApple12			130			//  512x384 (60 Hz) Rubik timing.
#define timingApple12x			135			//  560x384 (60 Hz) Rubik-560 timing.
#define timingApple13			140			//  640x480 (67 Hz) HR timing.
#define timingApple13x			145			//  640x400	(67 Hz) HR-400 timing.
#define timingAppleVGA			150			//  640x480 (60 Hz) VGA timing.
#define timingApple15			160			//  640x870 (75 Hz) FPD timing.
#define timingApple15x			165			//  640x818	(75 Hz) FPD-818 timing.
#define timingApple16			170			//  832x624 (75 Hz) GoldFish timing.
#define timingAppleSVGA			180			//  800x600 (56 Hz) SVGA timing.
#define timingApple1Ka			190			// 1024x768 (60 Hz) VESA 1K-60Hz timing.
#define timingApple1Kb			200			// 1024x768 (70 Hz) VESA 1K-70Hz timing.
#define timingApple19			210			// 1024x768 (75 Hz) Apple 19" RGB.
#define timingApple21			220			// 1152x870 (75 Hz) Apple 21" RGB.
#define timingAppleNTSC_ST		230			//  512x384 (60 Hz, interlaced, non-convolved).
#define timingAppleNTSC_FF		232			//  640x480 (60 Hz, interlaced, non-convolved).
#define timingAppleNTSC_STconv	234			//  512x384 (60 Hz, interlaced, convolved).
#define timingAppleNTSC_FFconv	236			//  640x480 (60 Hz, interlaced, convolved).
#define timingApplePAL_ST		238			//  640x480 (50 Hz, interlaced, non-convolved).
#define timingApplePAL_FF		240			//  768x576 (50 Hz, interlaced, non-convolved).
#define timingApplePAL_STconv	242			//  640x480 (50 Hz, interlaced, non-convolved).
#define timingApplePAL_FFconv	244			//  768x576 (50 Hz, interlaced, non-convolved).

// Various extra Control/Status calls used by built-in video
//
#define cscV8GoodBye             128         // Used by V8Driver for graying the screen at reset time.
#define cscRubik560              129         // Used by the SonoraDriver to toggle the Rubik-560 mode.

#define cscSyncOnGreen           128         // Used by DAFBDriver for enabling/disabling sync on green.
#define csc16bpp                 129         // Used by DAFBDriver for allowing/blocking 16bpp when AC842A is around.
#define cscPageMode              130         // Used by DAFBDriver for enabling/disabling page mode.
#define cscAltSense              131         // Used for enabling sRsrcs via the alternate sense pRAM byte (DAFB/Sonora/Civic).
#define cscPowerSelect           132         // Used for bypassing RGB outputs (enabling composite-out) on Civic.
#define cscSleepWake	         134         // Used for bypassing RGB outputs (enabling composite-out) on Civic.

#define cscVideoIn               128         // Used by CivicDriver for enabling/disabling video-in.

// Slot pRAM
//
// Slot pRam is used in various ways.  The first two bytes are used by the Slot Manager to record
// the slot’s boardID.  The remaining bytes are left undefined by the Slot Manager.  Built-in
// video uses Slot pRam as follows:
//
#define SP_Params             0
#define SP_Params_SP_BoardID          0           // BoardID.
#define SP_Params_SP_Depth            2           // spID of Depth (Mode).                     (vendorUse1)
#define SP_Params_SP_LastConfig       3           // spID of last boot-up configuration.       (vendorUse2)
#define SP_Params_SP_DfltConfig       4           // spID of default configuration…            (vendorUse3)
#define SP_Params_SP_MonID            5           // Sense code of last display.               (vendorUse4)
#define SP_Params_SP_Flags            6           // Various flags.                            (vendorUse5)
#define SP_Params_SP_AltSense         7           // Alternate senseID byte.                   (vendorUse6)
#define SP_Params_SP_Size             8
// endr SP_Params
                    
// Slot pRAM flag bits
//
#define spSyncOnGreen            0           // True if we’re supposed to put sync on green (DAFB).
#define spHas16bppACDC           1           // True if AC842A is around on DAFB.
#define spAllow16bpp             2           // True if we’re allowing 16bpp to be used on DAFB.
#define spPageMode               3           // True if we’re enabling DAFB’s PageMode.
#define spHas16bppSRsrc          4           // True if we’ve actually using a 16bpp sRsrc on DAFB.
#define spAltSenseEnb            5           // True if AltSense was used before (for keeping SOG state).

#define spVRAMBit0               0           // These two bits are used to encode the amount of
#define spVRAMBit1               1           //   vRAM available in Sonara-based CPUs.

#define numSPVRamBits            2           // Width for Bfins/Bfext of spVRAMBits
#define spVRAMBits               (31-spVRAMBit1) // Offset for Bfins/Bfext.

#define spKbdNMI                 2           // True if we’re enabling Keyboard NMI (Sonora).
#define spFamilyChanged          2           // the family mode changed on PDM; always reset in PrimayrInit.
#define spNoVRAM                 3           // True if video RAM is not VRAM-based.

#define spVideoIn                0           // True if we’re supposed to enable video-in (Civic).
#define spCompOut				 1			 // True if we should drive out composite even if no monitor connected (CIVIC)
#define spCompOutPAL			 2			 // If spCompOut is set, then this tells us (if true), to drive PAL.  (CIVIC)
#define spOpenComponent			 3			 // True if True if Open call to a component is for registering purposes only!  (Civic)

// Slot pRAM alternate senseID masks
//
#define spAltSenseValidMask      $40         // Upper two bits must be valid in order to use lower six.
#define spAltSenseMask           $3F         // Lower six bits are the indexed (mapped) sense code.

#define spAltSenseDisable        $80         // Bits used for temporarily disabling the alternate senseID.

// Definition of each of the entries in the ‘scrn’ resource.
//
#define ScrnRecord            0
#define ScrnRecord_srDrvrHW            0           // Hardware id of video card.
#define ScrnRecord_srSlot              2           // Slot number.
#define ScrnRecord_srDCtlDevBase       4           // DCtlDevBase (baseAddr) from AuxDCE.
#define ScrnRecord_srMode              8           // Mode (spID) of depth.
#define ScrnRecord_srFlagMask          10           // ????
#define ScrnRecord_srFlags             12           // GDevice flags.
#define ScrnRecord_srColorTable        14           // RsrcID of desired ‘clut’.
#define ScrnRecord_srGammaTable        16           // RsrcID of desicred ‘gama’.
#define ScrnRecord_srRect              18           // GDevice rectangle.
#define ScrnRecord_srCtlCount          26           // ????
#define ScrnRecord_ScrnRecSize              28
// endr ScrnRecord

// Various DAFB Equates…
// 
// The screen clearing code for DAFB is pretty straight forward with a couple of minor wrinkles.  The
// wrinkles come about because NTSC and PAL support both “safe title” (ST) and “full frame” (FF) display
// areas.  Since the ST mode is always smaller in area than a display’s FF area, the “non-viewable” area
// in the ST mode must be “blacked out.”  But, in order to keep the code general, we always try to
// draw the border.  In order to do this, we must carry around the FF vs. ST information.  The following
// SC_Params record is where that information is housed.  
//
#define SC_Params             0
#define SC_Params_SC_ActiveWidth      0           // Number of doublelongs-1 (per row) for active part of screen.
#define SC_Params_SC_BorderHeight     2           // Number of rows for Top/Bottom section of border.
#define SC_Params_SC_BorderWidth      4           // Number of longs-1 for Top/Bottom section of border.
#define SC_Params_SC_BorderSide       6           // Number of longs for Left/Right section of border (in Middle).
#define SC_Params_SC_SkipFactor       8           // Difference between rowbytes and cleared part of screen.
#define SC_Params_SC_Size                  10
// endr SC_Params

#define DAFBBppParams         0 // This structure is used for switching depths.

#define DAFBBppParams_dbpRowWords         0           // Framebuffer params.
#define DAFBBppParams_dbpClkCfg           2           //
#define DAFBBppParams_dbpConfig           4           //

#define DAFBBppParams_dbpHSerr            6           // Horizontal timing params.
#define DAFBBppParams_dbpHlfLn            8           //
#define DAFBBppParams_dbpHEq              10           //
#define DAFBBppParams_dbpHSP              12           //
#define DAFBBppParams_dbpHBWay            14           //
#define DAFBBppParams_dbpHBrst            16           //
#define DAFBBppParams_dbpHBP              18           //
#define DAFBBppParams_dbpHAL              20           //
#define DAFBBppParams_dbpHFP              22           //
#define DAFBBppParams_dbpHPix             24           //
#define DAFBBppParams_dbpTimingAdj        26           //

#define DAFBBppParams_dbpACDCPCBR         28           // ACDC (CLUT/DAC) PCBR.

#define DAFBBppParams_dbpTimingAdjAMD     30           // Alternate AMD parameters
#define DAFBBppParams_dbpHALAMD           32           //
#define DAFBBppParams_dbpHFPAMD           34           //

#define DAFBBppParams_DBPSize                  36
// endr DAFBBppParams

#define DAFBVidParams         0 // This structure is used for programming DAFB.

#define DAFBVidParams_dvpNSC8531          0          // The NSC-8531 programmable clock parameters.
#define DAFBVidParams_dvpNSC8534          10           // The NSC-8534 programmable clock parameters.

#define DAFBVidParams_DVPMaxModeBase           16           
#define DAFBVidParams_dvpMaxModeA         16           // Maximum mode (depth) for A-sized sRsrc.
#define DAFBVidParams_dvpMaxModeB         17           // Maximum mode (depth) for B-sized sRsrc.

#define DAFBVidParams_dvpBadDepth         18           // Index of depth having “bad” AMD param; 0 if okay.
#define DAFBVidParams_dvpFudge            19           // Fudge factor to add to bad AMD param.

#define DAFBVidParams_dvpNumRows          20           // Number of rows-1 for active (QD) part of screen.

#define DAFBVidParams_dvpVHLine           22           // Vertical timing params.
#define DAFBVidParams_dvpVSync            24           //
#define DAFBVidParams_dvpVBPEq            26           //
#define DAFBVidParams_dvpVBP              28           //
#define DAFBVidParams_dvpVAL              30           //
#define DAFBVidParams_dvpVFP              32           //
#define DAFBVidParams_dvpVFPEq            34           //

#define DAFBVidParams_DVPHdrSize               36           // 

#define DAFBVidParams_dvpRowWords         36           // Keep up-to-date with DAFBBppParams.
#define DAFBVidParams_dvpClkCfg           38           // (Used for 1bpp in PrimaryInit.)
#define DAFBVidParams_dvpConfig           40           //
#define DAFBVidParams_dvpHSerr            42           //
#define DAFBVidParams_dvpHlfLn            44           //
#define DAFBVidParams_dvpHEq              46           //
#define DAFBVidParams_dvpHSP              48           //
#define DAFBVidParams_dvpHBWay            50           //
#define DAFBVidParams_dvpHBrst            52           //
#define DAFBVidParams_dvpHBP              54           //
#define DAFBVidParams_dvpHAL              56           //
#define DAFBVidParams_dvpHFP              58           //
#define DAFBVidParams_dvpHPix             60           //
#define DAFBVidParams_dvpTimingAdj        62           //
#define DAFBVidParams_dvpACDCPCBR         64           //
#define DAFBVidParams_dvpTimingAdj1       66           //
#define DAFBVidParams_dvpHAL1             68           //
#define DAFBVidParams_dvpHFP1             70           //
// endr DAFBVidParams

// Versions of the DAFB chip (accessed on the DAFBTest register). 
//
#define DAFB1Vers            $00             // DAFB 1:  Original hardware release.
#define DAFB2Vers            $01             // DAFB 2:  Fix for NTSC & PAL 1,2 bpp modes.
#define DAFB3Vers            $02             // DAFB 3:  Support for AC842A (16bpp ACDC).
#define DAFB4Vers            $03             // DAFB 4:  The Wombat DAFB. 
    
// Instead of burning valuable pRAM to communicate between PrimaryInit/SecondaryInit and the video
// driver, we use a conviently unused DAFB 12-bit register.
//
#define DAFBFlags                (Swatch_Test) // A conveniently unused DAFB 12-bit register.

#define rvBeenHere                0          // The “beenHere” flag for the Remote Video Switch.
#define rvChanged                 1          // Says whether the remote video switch has changed states.
#define rvRemoteState             2          // The “beenHere” state of remote video.

#define isWombat                  3          // If this bit is set, we’ve got a WombatDAFB.

#define RadiusTPDBit              4          // If this bit is set, a Radius TPD is attached.
#define RadiusDevType             5          // RadiusTPD DevType: 0=monochrome, 1=color.

#define wLin16Bpp                 6          // For Wombat, set if using the linear 16bpp CLUT/DAC.
#define w40MHz                    7          // For Wombat, set if running at 40Hz.

#define vRamBit0                  9          // These two bits say whether there is 512K, 1Meg, or 
#define vRamBit1                 10          //   2Megs of vRAM associated with DAFB.

#define numVRamBits               2          // Width for Bfins/Bfext of the vRamBits.
#define vRamBits                 (31-vRamBit1) // Offset for Bfins/Bfext.

#define videoEnabled             11          // Set if video is actually turned on.

// DAFB supports a large number of displays, some of which do NOT share the same base address as
// the others.  The reason for this is due to hardware constraints (e.g., in order to clock the
// data out fast enough for some large displays and convolved modes, it is necessary to interleave
// and align vRam).
//
#define DAFBStdOffset            $1000       // Active video offset from base of frame buffer vRAM for most displays.
#define DAFB2POffset             $0A00       // Active video offset for Kong & Vesuvio (1-16bpp).
#define DAFB2POffsetW            $0080       // Acivie video offset for Wombat (1-8bpp).
#define DAFBBSOffset             $0E00       // Active video offset for GoldFish & SuperVGA (1-32bpp).
#define DAFBBSOffsetW            $0080       // Active video offset for Wombat BS, 1-32bpp.
#define DAFBNTSCOffset           $1020       // Active video offset for NTSC Displays.
#define DAFBNTSCConvOff          $1400       // Active video offset for NTSC convolved Displays.
#define DAFBPALOffset            $0E20       // Active video offset for PAL Displays.
#define DAFBPALOffsetW           $0700       // Acitve video offset for PAL on Wombat.
#define DAFBPALConvOff           $1420       // Active video offset for PAL convolved Displays.

// DAFB supports several displays that are in the “extended” sense line range.  Since the raw
// values that come back from doing the extended sense-line algorithm do not map into a nice
// tablular form like the “normal” sense line codes do, we map the few extended-sense-line displays
// that we support into the bottom of the normal sense line table.
//
// Notes:  The “normal” sense displays fall in the range of 0..7, where 7 means “go try the
//         extended sense codes.”  So, we map the extended sense codes from 8 (yeah, we have
//         blank entry).
//
//         Radius exploits the fact that the extended sense algorithm is generally only tried
//         when a 7 is read back.  That is, for their two TPD displays (one color, the other
//         monochrome), they use 3 as the trigger for doing the extended sense algorithm.  To
//         distinguish the two displays from each other, they just reverse the polarity of the
//         the diode on sense lines b & c.  (Note:  This technique could be used for sense
//         codes 5 and 6, too.)
//
//         So, it should be noted, that there are four types of extended sense codes.  We
//         just use types 3, 6, and 7; type 5 is reserved.
//

#define extended2P               $35         // Raw Extended Sense for the Two-Page Display.
#define extended2PRdRGB          $31         // Raw Extended Sense for Radius’ Color TPD.
#define extended2PRdMono         $34         // Raw Extended Sense for Radius’ Mono TPD.

#define extendedRGBFP            $1E         // Raw Extended Sense for the RGB Full-Page Display.

#define extendedHR               $2B         // Raw Extended Sense for the Hi-Res Display (type-6 extended sense).
#define extendedMSB1			 $03		 // Raw Extended Sense for Band-1 Multiscan Displays (14", GS thru GF).
#define extendedMSB2			 $0B		 // Raw Extended Sense for Band-2 Multiscan Displays (17", HR thru 19).
#define extendedMSB3			 $23		 // Raw Extended Sense for Band-3 Multiscan Displays (20", HR thru 2P).

#define extendedNoConnect        $3F         // Raw Extended Sense for no connect.
#define extendedSensePALBox      $00         // Raw Extended Sense for PAL Encoder.
#define extendedSenseNTSC        $14         // Raw Extended Sense for NTSC Encoder.
#define extendedSenseVGA         $17         // Raw Extended Sense for VGA.
#define extendedSenseLP          $2D         // Raw Extended Sense for GoldFish.
#define extendedSenseGF          $2D         // Raw Extended Sense for GoldFish.
#define extendedSensePAL         $30         // Raw Extended Sense for PAL.
#define extendedSense19          $3A         // Raw Extended Sense for Third-Party 19” Displays.

#define indexedSenseRGB2P         0          // For switching to 16bpp.
#define indexedSenseFP            1          // For Mono-Only configs.
#define indexedSenseRubik         2          // For factory burn-in testing.
#define indexedSense2P            3          // For Mono-Only configs.
#define indexedSenseNTSC          4          // To Map NTSC encoder boxes to NTSC displays.
#define indexedSenseRGBFP         5          // For switching to 16bpp.
#define indexedSenseHR            6          // DAF said we should do HR for the factory.
#define indexedNoConnect          7          // (Here for consistency only.)
#define indexedSenseVGA           8          // Mapped Sense For VGA. 
#define indexedSensePAL           9          // Mapped Sense For PAL.
#define indexedSenseLP           10          // Mapped Sense For GoldFish.
#define indexedSenseGF           10          // Mapped Sense For GoldFish.
#define indexedSense19           11          // Mapped Sense For 19" Displays.
#define pIndexRdMono             12          // Pseudo Index for Radius’ Mono TPD. (DAFB)
#define indexedSenseMSB1		 12			 // Mapped Sense For Band-1 Multiscan Displays.
#define indexedSenseMSB2		 13			 // Mapped Sense For Band-2 Multiscan Displays.
#define indexedSenseMSB3		 14			 // Mapped Sense For Band-3 Multiscan Displays.

#define dafbSenseLineA            2          // Numbers for bit-I/O on DAFB senselines.
#define dafbSenseLineB            1          //
#define dafbSenseLineC            0          //

#define dafbAMask                 3          // Masks for reading/writing DAFB senselines.
#define dafbBMask                 5          //
#define dafbCMask                 6          //

#define tristateDAFBSense         7          // Value for tri-stating DAFB senselines.

// Resetting the DAFB is a process that requires 5 steps.  First, the Swatch is released from
// its reset state.  Then the Swatch reset mode is reassertd and re-released.  Finally,
// the vRam and video refresh state machines are reset.  The following equates are the masks
// for setting the right bits in the DAFB reset register.
//

#define dafbReleaseSwatch         3          // See comments above.
#define dafbReassertSwatch        7          //
#define dafbReleaseVRamSM         2          //
#define dafbReleaseVideoSM        0          //

#define dafbResetIdle             7          // Value to idle DAFB reset register.
#define dafbDisableSwatch         $FF1       // Value to disable Swatch.
#define dafbEnableSwatch          $FF2       // Value to enable Swatch.

// In order for the ACDC and for the Clock to be programmed correctly, the DAFB_Config
//   register must be set up for the right CPU clock speed (which just means turning
//   on the WriteAccess bit in the DAFBConfig register).
//
// DAFB supports the fast page mode operation of the VRams.  However, the only place where it
//   really makes sense to turn this mode on (all the time) is when the VRams are configured
//   for the row-interleave access (which is generally 640x480 @ 32bpp).  Bit 1 of the
//   DAFBConfig register is RowInterleave enable/disable bit; it is bit 30 for bit-field
//   extraction & insertion, and that’s how we use it.
//
// Update to above:  It really makes more sense to just turn page mode OFF when the VRams are
//   configured for word-interleave.
//
// Wombat info:  The WombatDAFB doesn’t support either word or row interleaving of VRam, so
//   we just mask out those bits on Wombat in the DAFBSpeed macros.
//

#define dafb33MHzConfig          $00000800                           // Mask for 33MHz setup (non-Wombat).
#define dafb33MHzConfigW         $00000200                           // Mask for Wombat 33MHz setup.
#define dafb40MHzConfigW         $00000A00                           // Mask for Wombat 40MHz setup.
#define dafbWaitConfig           $00000F00                           // Mask for turning on ALL wait-states.

#define dafbNoInterleave         $00000FFC                           // Mask to clear interleave bits.                                
#define dafbRowIntBit            30                                  // Bfins/Bfext-style numbers.
#define dafbWrdIntBit            31                                              

// On the WombatDAFB, the enable/disable for the sync-on-green signal bit 9 (PIXSEL0) of the Clock
//   configuration register.  In order to do this without disturbing the other bit-fields in this
//   register, we use the bit-field insertion instruction; so, bit 9 is bit 22 for Bfins.
//

#define dafbSyncOnGreen          22                                  // Bfins/Bfext-style number.

// Originally, we used the “real” VBL interrupt line for doing VBL interrupts.  However, it
//   turned out VBL was generated at vSync, and this was way too late in the cycle.  So,
//   to resolve this problem, we actually use the cursor interrupt line, which we can
//   program ourselves. 

#define dafbIntStatusBit          2

#define dafbDisableVInts         $0
#define dafbEnableVInts          $4

// With the AMD-ACDC (AC842A), the ECL clock signals can be enabled and disabled in software.  The
//   only time we want to disable the ECL clock signals is when the PIXSEL1 (bit 10) of the DAFB clock
//   configuration register is zero.  In AC842A, bit 4 in PCBR1 selects whether the ECL or LD clock
//   signals are used.  (Note:  When we do set the acdcPCS, we must also ensure that PIXSEL0 (bit 9)
//   is set so that the 100Mhz clock is not passed thru DAFB, but instead uses the programmable
//   clock generator.)

#define acdcPCS                  (31-4)                                // Bfins/Bfext-style numbers.

#define dafbPixSel0              (31-9)
#define dafbPixSel1              (31-10)

                    
//
// Various DB-Lite Equates…
//
// Switching depths on DB-Lite is pretty straight forward.  The following equates are for the GSCGrayScale register.
//   They are Bfins/Bfext-type equates, so the bit-number is reverse of normal.
// 

#define GSCLevelWidth             3                                  // Number of bits in level field.        

#define GSCLevelBit0              0                                  // The GSC-level bits.
#define GSCLevelBit1              1
#define GSCLevelBit2              2

#define GSCLevelBits             (31-GSCLevelBit2)                     // For use with Bfins/Bfext.

#define GSCBlankBit              (31-5)                                // For enabling/disabling screen blanking. 

//
// Various CSC Equates…
//
// The following record describes the video parameters for CSC built-in video.  The first
//	few parameters are for graying the screen, setting up sRsrcs, etc….  The rest of
//	the parameters are the actual values that are programmed into the CSC registers.

#define CSCBppParams           0
#define CSCBppParams_cscbpFRCControl  0           // Number of doublelongs-1 (per row) for active part of screen.
#define CSCBppParams_cscbpPolyMAdj    1           // Number of rows for Top/Bottom section of border.
#define CSCBppParams_cscbpPolyNAdj    2           // Number of longs-1 for Top/Bottom section of border.
#define CSCBppParams_cscbpGFRCControl 3           // Number of longs for Left/Right section of border (in Middle).
#define CSCBppParams_cscbpGPolyMAdj   4           // Difference between rowbytes and cleared part of screen.
#define CSCBppParams_cscbpGPolyNAdj   5
#define CSCBppParams_CSCBppSize       6
// endr CSCBppParams

#define CSCVidParams          0 // This structure is used for programming CSC.
#define CSCVidParams_cscvpMaxModeBase    0
#define CSCVidParams_cscvp512KMax        0
#define CSCVidParams_cscvp1MegMax        1

#define CSCVidParams_cscvpNumRows        2           

#define CSCVidParams_cscvpPanelType      4
#define CSCVidParams_cscvpPanelSetup     5

#define CSCVidParams_cscvpHSkewHi        6
#define CSCVidParams_cscvpHSkewLo        7
#define CSCVidParams_cscvpVSkewHi        8
#define CSCVidParams_cscvpVSkewLo        9

#define CSCVidParams_cscvpACDClkHi       10
#define CSCVidParams_cscvpACDClkLo       11
#define CSCVidParams_cscvpLPStart        12
#define CSCVidParams_cscvpLPWidth        13
#define CSCVidParams_cscvpFLMControl     14

#define CSCVidParams_cscvpDataOutForm    15

#define CSCVidParams_CSCVPHdrSize        16 

#define CSCVidParams_cscvpFRCControl     16
#define CSCVidParams_cscvpPolyMAdj       17 
#define CSCVidParams_cscvpPolyNAdj       18
#define CSCVidParams_cscvpGFRCControl    19
#define CSCVidParams_cscvpGPolyMAdj      20
#define CSCVidParams_cscvpGPolyNAdj      21
#define CSCVidParams_CSCVPSize           22
// endr CSCVidParams

//
// The interrupt flags and enable bits are housed within the DisplayStatus register.  The
//	following equates are setting and clearing CSC VBL interrupts.  The DisplayStatus
//	register also controls “panel shading.”  The CSCUnBlank equate is for taking
//	the display from an “off” state (blanked) to an “on” state (unblanked).
//

#define CSCDSIER              0
#define CSCDSIFR              1
#define CSCDSRBlankCtl        2
#define CSCDSRBlankSts        3

#define CSCUnblank            12

//
// Misc CSC bits/masks for various CSC registers…
//

#define CSCPnlPwr              3
#define CSCPnlDataInv          2

#define CSCPaletteBypass       1

#define CSCInvertVRAM          3
#define CSCBetterDither        0

//
// Unlike most CLUT/DACs used in the various Macintosh CPUs, the CSC CLUT/DAC is called a
//	Palette and is completely contained within the CSC itself.  One of the Palette
//	registers (called the PaletteMask) is used for logically removing video.  We actually
//	want all video data to be displayed, so we set the mask register to all 1’s (i.e.,
//	the PaletteMask is AND’d with the video data).
//

#define CSCNoMask              255

//
// The CSC is a reasonably programmable LCD controller.  And, as a result, it supports several
//	sizes and styles of LCDs.  The list below is the set of panel IDs that identify the
//	various LCDs that could potentially be supported by CPUs using the CSC.
//
// Note:  In order to keep things sane (I think), we have allowed each of the products using
//	CSC to have it’s own set of panel IDs.
//

// Escher/Yeager List…
//
#define isC_S_TFT_640x480              0
#define isG_S_TFT_640x400              4
#define isG_D_STN_640x400              6

// BlackBird List…
//
#define isC_S_TFT_640x480a             0
#define isC_D_STN_640x480              1
#define isC_S_TFT_640x480b             2
#define isC_S_TFT_640x480c             3
#define isC_S_TFT_640x480d             4
#define isG_D_STN_640x480              5
#define isG_S_TFT_640x480              6

#define isNoConnect                    7
#define tristateCSC                    7

//
// Various Sonora Equates…
//
// The following record describes the video parameters for Sonora built-in video.  The first
//   set of parameters are for the Omega (clock generator) chip.  The monitor code value
//   tells Sonora the type of sync and h/v “line” values to use.  The other parameters are
//   for graying the screen, setting up sRsrcs, etc….
//

#define SonoraOmega           0
#define SonoraOmega_SOmegaN             0                                   // Omega N,D,P values.                               
#define SonoraOmega_SOmegaD             1
#define SonoraOmega_SOmegaP             2
//**Pad**:                     Ds.b    1
#define SonoraOmega_SOmegaSize               4
// endr SonoraOmega

#define SonoraVidParams       0
#define SonoraVidParams_svpOmega1           0                                   // Omega1 Values.
#define SonoraVidParams_svpOmega2           4                                   // Omega2 Values.
#define SonoraVidParams_SVPOmegaSize             8
#define SonoraVidParams_svpMonitorCode      8                                   // Monitor code value.
//**Pad**:                     Ds.b    1                                   // <pad>
#define SonoraVidParams_svpMaxModeBase           10
#define SonoraVidParams_svp256Max           10                                   // Max depths:   256K,
#define SonoraVidParams_svp512Max           11                                   //               512K,
#define SonoraVidParams_svp768Max           12                                   //               768K.
//**Pad**:                     Ds.b    1                                   // <pad>
#define SonoraVidParams_svpNumRows          14                                   // Number of rows (-1).
#define SonoraVidParams_SVPHdrSize               16
#define SonoraVidParams_svp1bppRowLongs     16                                   // 1bpp rowlongs-1.
#define SonoraVidParams_svp2bppRowLongs     18                                   // 2bpp rowlongs-1.
#define SonoraVidParams_svp4bppRowLongs     20                                   // 4bpp rowlongs-1.
#define SonoraVidParams_svp8bppRowLongs     22                                   // 8bpp rowlongs-1.
#define SonoraVidParams_svp16bppRowLongs    24                                   // 16bpp rowlongs-1.
#define SonoraVidParams_SVPSize                  26
// endr SonoraVidParams
                    
#define OmegaNBits               7                                   // Number of bits in Omega N field.
#define OmegaDBits               7                                   // Number of bits in Omega D field.
#define OmegaPBits               2                                   // Number of bits in Omega P field.

// Once we determine how much vRAM is actually installed into a Sonora System, we have to
//   tell Sonora how much is there.  Currently, Sonora Systems are limited to 768K, but
//   1024K is possible, so we’ll support it anyway.
//

#define Sonora256K               0                                   // Bank0=256K,Bank1=0.
#define Sonora512Ka              1                                   // Bank0=256K,Bank1=256K.
#define Sonora512Kb              4                                   // Bank0=512K,Bank1=0.
#define Sonora768Ka              2                                   // Bank0=256K,Bank1=512K.
#define Sonora768Kb              5                                   // Bank0=512K,Bank1=256K.
#define Sonora1024K              6                                   // Bank0=512K,Bank1=512K.

#define SonoraWrap               512                                 // Where Sonora wraps vRAM.  Why?

// The senselines for Sonora-based systems are very similar to DAFB.  The main difference is that
//   the Sonora uses the top nybble of the senseline regiters for input and the bottom nybble for
//   output.
//

#define sonoraSenseLineA         2                                   // Numbers for bit-I/O on Sonora senselines.
#define sonoraSenseLineB         1                                   //
#define sonoraSenseLineC         0                                   //

#define sonoraAMask              3                                   // Masks for reading/writing Sonora senselines.
#define sonoraBMask              5                                   //
#define sonoraCMask              6                                   //

#define tristateSonoraSense      7                                   // Value for tri-stating Sonora senselines.

// Miscellenous Sonora equates…
//

#define SonoraVidBlnkBit         7                                   // Bit 7 of the SonoraVdModeReg.


//
// Various Civic Equates…
//

#define fCivicVidIn                  0                               // cvpFlags bit flag -> true if sRsrc is a video-in sRsrc.
#define mCivicGrBpp                  7                               // mask to determine the graphics bpp depth from Sebast PCBR
#define mspVideoIn                   1                               // mask to ANDI into SP_Flags to isolate the video in flag.
#define fCivicVidInBpp               3                               // SebastPCBR's video-in bpp bit (0 based)
#define fCivicConvEnb                5                               // SebastPCBR's convolution enable bit
#define fCivicVidinCLUT              6                               // SebastPCBR's CLUT Select Bit: (0 selects graphics CLUT, 1 selects Video-in CLUT)
#define fCivicVidInOvly              7                               // SebastPCBR's overlay enable bit (0-based)
#define vCivicGr16Bpp                4                               // SebastPCBR's value for 16bpp graphics on D2-D0
#define vCivicVidInBase              $50200800                       // The Video-in VRAM's base address
#define LoadCliftonControl			 $1E05							 // Word to load the Control Register in Clfton
#define LoadCliftonProgram			 $1E04							 // Word to load the Program Register in Clfton
#define LoadCliftonMuxRef			 $1E00							 // Word to enable the mux reference in Clfton
#define	ControlWordSize				 14								 // Size in bits of the Clifton control/program word

#define CivicEntry                0                     // Defines the entries in the CivicRecord (below).
#define CivicEntry_offset              0
#define CivicEntry_width               2
#define CivicEntry_CESize                       4
// endr CivicEntry

#define CivicRecord               0                     // This structure is used to read/write Civic registers.
#define CivicRecord_VBLInt              0                               // $00
#define CivicRecord_Enable              4                               // $04
#define CivicRecord_VDCInt              8                               // $08
#define CivicRecord_VDCClr              12                               // $0C
#define CivicRecord_VDCEnb              16                               // $10
#define CivicRecord_VidInSize           20                               // $14
#define CivicRecord_VDCClk              24                               // $18
#define CivicRecord_ScanCtl             28                               // $1C
#define CivicRecord_GSCDivide           32                               // $20
#define CivicRecord_VSCDivide           36                               // $24
#define CivicRecord_VRAMSize            40                               // $28
#define CivicRecord_RefreshCtl          44                               // $2C
#define CivicRecord_BusSize             48                               // $30
#define CivicRecord_SpeedCtl            52                               // $34
#define CivicRecord_ConvEnb             56                               // $38
#define CivicRecord_SenseCtl            60                               // $3C
#define CivicRecord_Sense0              64                               // $40
#define CivicRecord_Sense1              68                               // $44
#define CivicRecord_Sense2              72                               // $48
#define CivicRecord_Tristate            76                               // $4C
#define CivicRecord_SyncClr             80                               // $50
#define CivicRecord_ReadSense           84                               // $54
#define CivicRecord_RowWords            88                               // $58
#define CivicRecord_BaseAddr            92                               // $5C
#define CivicRecord_VLDB                96                               // $60
#define CivicRecord_VHLTB               100                               // $64
#define CivicRecord_VActHi              104                               // $68
#define CivicRecord_Reset               108                               // $6C
#define CivicRecord_VBLEnb              112                               // $70
#define CivicRecord_HLDB                116                               // $74
#define CivicRecord_HHLTB               120                               // $78
#define CivicRecord_HActHi              124                               // $7C
#define CivicRecord_VBLClr              128                               // $80
#define CivicRecord_AdjF2               132                               // $84
#define CivicRecord_AdjF1               136                               // $88
#define CivicRecord_TestEnb             140                               // $8C
#define CivicRecord_CntTest             144                               // $90
#define CivicRecord_HSerr               148                               // $94
#define CivicRecord_VInHAL              152                               // $98
#define CivicRecord_VInHFPD             156                               // $9C
#define CivicRecord_VInHFP              160                               // $A0
#define CivicRecord_HlfLn               164                               // $A4
#define CivicRecord_HEq                 168                               // $A8
#define CivicRecord_HSP                 172                               // $AC
#define CivicRecord_HBWay               176                               // $B0
#define CivicRecord_HAL                 180                               // $B4
#define CivicRecord_HFP                 184                               // $B8
#define CivicRecord_HPix                188                               // $BC
#define CivicRecord_PipeD               192                               // $C0
#define CivicRecord_VHLine              196                               // $C4
#define CivicRecord_VSync               200                               // $C8
#define CivicRecord_VBPEq               204                               // $CC
#define CivicRecord_VBP                 208                               // $D0
#define CivicRecord_VAL                 212                               // $D4
#define CivicRecord_VInVAL              216                               // $D8
#define CivicRecord_VInVFP              220                               // $DC
#define CivicRecord_VFP                 224                               // $E0
#define CivicRecord_VFPEq               228                               // $E4
#define CivicRecord_CurLine             232                               // $E8
#define CivicRecord_VInDoubleLine       236                               // $EC   (Civic II register)
// endr CivicRecord

#define CivicBppParams            0                     // This structure is used for switching depths.

#define CivicBppParams_cbpBusSize          0                               // Framebuffer Params.
#define CivicBppParams_cbpGSCDivide        2                               // 
#define CivicBppParams_cbpRowWords         4                               //
#define CivicBppParams_cbpAdjF1            6                               //
#define CivicBppParams_cbpAdjF2            8                               //
#define CivicBppParams_cbpPipeD            10                               //

#define CivicBppParams_cbpSebastPCBR       12                               // Sebastion (CLUT/DAC) PCBR.

#define CivicBppParams_cbpHSerr            14                               // Horizontal timing params.
#define CivicBppParams_cbpHlfLn            16                               //
#define CivicBppParams_cbpHEq              18                               //
#define CivicBppParams_cbpHSP              20                               //
#define CivicBppParams_cbpHBWay            22                               //
#define CivicBppParams_cbpHAL              24                               //
#define CivicBppParams_cbpHFP              26                               //
#define CivicBppParams_cbpHPix             28                               //

#define CivicBppParams_CBPSize                      30
// endr CivicBppParams

#define CivicVidParams            0                     // This structure is used to program Civic.

#define CivicVidParams_CVPMaxModeBase               0
#define CivicVidParams_cvpMaxMode          0                               // Max Graphics mode
#define CivicVidParams_cvpMaxMode          1                               // Max Video-in mode

#define CivicVidParams_cvpFlags            2                               // Misc Flags byte.
#define CivicVidParams_cvpConvEnb          3                               // Only set if cvpScanCtl = interlaced.
#define CivicVidParams_cvpNTSCid           4                               // spID of NTSC timing for this resolution
#define CivicVidParams_cvpPALid            6                               // spID of PAL timing for this resolution
#define CivicVidParams_cvpConvNTSCid       8                               // spID of PAL timing for this resolution
#define CivicVidParams_cvpConvPALid        9                               // spID of PAL timing for this resolution

#define CivicVidParams_cvpEndeavorM        10                               // Endeavor (VidClk) params.
#define CivicVidParams_cvpEndeavorN        11                               //
#define CivicVidParams_cvpEndeavorClk      12                               //
#define CivicVidParams_cvpScanCtl          13                               // Progressive/Interlaced.
                    
#define CivicVidParams_cvpCliftonW		   14								// Clifton's W Parameter
#define CivicVidParams_cvpCliftonWSize	   18								// W Parameter size
#define	CivicVidParams_cvpCliftonClk	   19								// Clifton's Clock Select

#define CivicVidParams_cvpPumaW			   20								// Puma's W Parameter
#define CivicVidParams_cvpPumaWSize	 	   24								// W Parameter size
#define	CivicVidParams_cvpPumaClk		   25								// Puma's Clock Select

#define CivicVidParams_cvpVHLine           26                               // Vertical timing params.
#define CivicVidParams_cvpVSync            28
#define CivicVidParams_cvpVBPEq            30
#define CivicVidParams_cvpVBP              32
#define CivicVidParams_cvpVAL              30
#define CivicVidParams_cvpVFP              34
#define CivicVidParams_cvpVFPEq            36
#define CivicVidParams_cvpNumRows          38                               // Number of rows - 1.

#define CivicVidParams_CVPHdrSize                   40
                    
#define CivicVidParams_cvpBusSize          40                               // Keep up-to-date with CivicBppParams.
#define CivicVidParams_cvpGSCDivide        42                               // Keep up-to-date with CivicBppParams.
#define CivicVidParams_cvpRowWords         44                               // (Used for 1bpp in PrimaryInit.)
#define CivicVidParams_cvpAdjF1            46
#define CivicVidParams_cvpAdjF2            48
#define CivicVidParams_cvpPipeD            50
#define CivicVidParams_cvpSebastPCBR       52
#define CivicVidParams_cvpHSerr            54
#define CivicVidParams_cvpHlfLn            56
#define CivicVidParams_cvpHEq              58
#define CivicVidParams_cvpHSP              60
#define CivicVidParams_cvpHBWay            62
#define CivicVidParams_cvpHAL              64
#define CivicVidParams_cvpHFP              66
#define CivicVidParams_cvpHPix             68
// endr CivicVidParams

// The senselines for Civic-based systems are completely unlike the DAFB- and Sonora-base systems.
//   However, by strategic use of the Civic sense-line macros, Civic-based systems are made to
//   look like the DAFB- and Sonora-base systems.  Neat, huh?
//

#define civicSenseLineA          2                                   // Numbers for bit-I/O on Civic senselines.
#define civicSenseLineB          1                                   //
#define civicSenseLineC          0                                   //

#define civicAMask               3                                   // Masks for reading/writing Sonora senselines.
#define civicBMask               5                                   //
#define civicCMask               6                                   //


//
// Internal equates shared by all built-in video drivers and PrimaryInits.
//

// Flags within GFlags word

#define GrayFlag                 15          // luminance mapped if GFlags(GrayFlag) = 1
#define IntDisFlag               14          // interrupts disabled if GFlags(IntFlag) =1
#define IsMono                   13          // true if monochrome only display (Portrait/Kong)
#define UseSeq                   12          // true if sequence mode SetEntries
#define UseTrans                 12          // True if we’re supposed to translate 5-bit into 8 (DAFB 16bpp).
#define Is16                     11          // true if 16Mhz (Slow) CPU
#define IsSlow                   11          // True if Slow CPU (for DAFB, 20/25Mhz is slow, 33/40MHz is not).
#define IsSleeping               11          // True if CPU is sleeping (PowerBook/LCDs).
#define HasAlpha                 11          // True if writing the alpha bits to the CLUT (Civic).
#define IsDirect                 10          // true if direct video mode, else chunkyIndexed
#define PsuedoIndex               9          // true if SetEntries request was mapped to indexed from sequential
                                        //   (due to screen depth hardware requirements)
#define Has16bppSRsrc             9          // True if FifthVidMode is 16bpp instead of 32bpp (DAFB).
#define SyncOnGreen               8          // True if we’re supposed to put sync on green (DAFB).
#define InRubik560Mode            8          // True if we started up in Rubik-560 mode (Sonora).
#define InBlanking                8          // True if we’re supposed to be blanking the LCD (GSC/CSC).
#define videoInEnb                8          // True if video-in is enabled (i.e., 32-bit wide graphics/video bus, Civic).

#define CompositeSyncOn           7          // True if driving out of Composite port (Civic)
#define NTSCTimingOn              6          // True if driving out NTSC out of Composite port (Civic)
#define ConvolutionOn             5          // True if driving out with AppleConvolution out of Composite port (Civic)

//---------------------------------------------------
// 
// Rowbytes, page count, and bounds constants
//
//---------------------------------------------------

// rowbytes constants for the Mac II Hi-Res monitor/VGA monitor
//
#define OBMHRRB                   80         // rowbytes for one-bit mode
#define TBMHRRB                  160         // rowbytes for two-bit mode
#define FBMHRRB                  320         // rowbytes for four-bit mode
#define EBMHRRB                  640         // rowbytes for eight-bit mode
#define D16BMHRRB               1280         // rowbytes for sixteen-bit mode

// rowbytes constants for the Mono/RGB Full-Page Display
//
#define OBMFPRB                   80         // rowbytes for one-bit mode
#define TBMFPRB                  160         // rowbytes for two-bit mode
#define FBMFPRB                  320         // rowbytes for four-bit mode
#define EBMFPRB                  640         // rowbytes for eight-bit mode

// rowbytes constants for the noninterlaced Apple // GS (Rubik) Monitor
//
#define OBMGSRB                   64         // rowbytes for one-bit mode
#define TBMGSRB                  128         // rowbytes for two-bit mode
#define FBMGSRB                  256         // rowbytes for four-bit mode
#define EBMGSRB                  512         // rowbytes for eight-bit mode
#define D16BMGSRB               1024         // rowbytes for sixteen-bit mode

// rowbytes constants for the noninterlaced Apple // GS (Rubik) Monitor in 560 mode
//
#define OBMGS560RB                70         // rowbytes for one-bit mode
#define TBMGS560RB               140         // rowbytes for two-bit mode
#define FBMGS560RB               280         // rowbytes for four-bit mode
#define EBMGS560RB               560         // rowbytes for eight-bit mode
#define D16BMGS560RB            1120         // rowbytes for sixteen-bit mode

// rowbytes constants for an SE-sized monitor
//
#define OBMSERB                   64         // rowbytes for one-bit mode
#define TBMSERB                  128         // rowbytes for two-bit mode
#define FBMSERB                  256         // rowbytes for four-bit mode
#define EBMSERB                  512         // rowbytes for eight-bit mode

// rowbytes constants for the GoldFish Display
//
#define OBMGFRB                  104         // rowbytes for one-bit mode
#define TBMGFRB                  208         // rowbytes for two-bit mode
#define FBMGFRB                  416         // rowbytes for four-bit mode
#define EBMGFRB                  832         // rowbytes for eight-bit mode

// rowbytes for Tim/DB-Lite LCD display
//
#define OBMLCDRB                 80          // rowbytes for one-bit mode
#define TBMLCDRB                160          // rowbytes for two-bit mode
#define FBMLCDRB                320          // rowbytes for four-bit mode
#define EBMLCDRB                640          // rowbytes for eight-bit mode
#define D16BMLCDRB             1280          // rowbytes for sixteen-bit mode

// rowbytes for Apollo display
//
#define OBMApolloRB              64          // rowbytes for one-bit mode

// rowbytes for V8 hardware
//
#define V8_512_RB                512
#define V8_1024_RB               1024

// rowbytes for DAFB hardware
//
#define DAFB_512_RB               512
#define DAFB_576_RB               576
#define DAFB_832_RB               832
#define DAFB_1024_RB             1024
#define DAFB_1152_RB             1152
#define DAFB_1664_RB             1664
#define DAFB_2048_RB             2048
#define DAFB_2304_RB             2304
#define DAFB_3328_RB             3328
#define DAFB_4096_RB             4096

// rowbytes/base addresses for Civic hardware
//
#define Civic_256_RB             256
#define Civic_512_RB             (DAFB_512_RB)
#define Civic_576_RB             (DAFB_576_RB)
#define Civic_832_RB             (DAFB_832_RB)
#define Civic_1024_RB            (DAFB_1024_RB)
#define Civic_1152_RB            (DAFB_1152_RB)
#define Civic_1280_RB            1280
#define Civic_1536_RB            1536
#define Civic_1664_RB            (DAFB_1664_RB)
#define Civic_2048_RB            (DAFB_2048_RB)
#define Civic_2304_RB            (DAFB_2304_RB)
#define Civic_2560_RB            2560
#define Civic_3328_RB            (DAFB_3328_RB)

#define Civic_256_Base           256
#define Civic_1280_Base          1280
#define Civic_1536_Base          1536
#define Civic_1792_Base          1792
#define Civic_2048_Base          2048
#define Civic_2560_Base          2560
#define Civic_3584_Base          3584
#define Civic_4096_Base          4096

// page counts for all (maybe one of these days we’ll support more than one page?)
//
#define OBMPagesHR               1
#define TBMPagesHR               1
#define FBMPagesHR               1
#define EBMPagesHR               1
#define D16BMPagesHR             1

#define OBMPagesFP               1
#define TBMPagesFP               1
#define FBMPagesFP               1
#define EBMPagesFP               1

#define OBMPagesGS               1
#define TBMPagesGS               1
#define FBMPagesGS               1
#define EBMPagesGS               1
#define D16BMPagesGS             1

#define OBMPagesGF               1
#define TBMPagesGF               1
#define FBMPagesGF               1
#define EBMPagesGF               1

#define OBMPagesSE               1
#define TBMPagesSE               1
#define FBMPagesSE               1
#define EBMPagesSE               1

#define OBMPagesA2Em             1
#define TBMPagesA2Em             1
#define FBMPagesA2Em             1
#define EBMPagesA2Em             1

#define OBMPagesLCD              1
#define TBMPagesLCD              1
#define FBMPagesLCD              1
#define defPagesLCD              1

#define OBMPagesApollo           1

// since they are all 1 page anyway… 
    
#define defPages_DAFB            1
#define defPages_Sonora          1
#define defPages_Civic           1

//
// Bounds constants
//

// for the Mac II Hi-Res Monitor
//
#define defmBounds_THR           0                           // top
#define defmBounds_LHR           0                           // left
#define defmBounds_BHR           480                         // bottom
#define defmBounds_RHR           640                         // right

#define defmBounds_THR400        0                           // top
#define defmBounds_LHR400        0                           // left
#define defmBounds_BHR400        400                         // bottom
#define defmBounds_RHR400        640                         // right

#define defmBounds_THRMAZ        0                           // top
#define defmBounds_LHRMAZ        0                           // left
#define defmBounds_BHRMAZ        512                         // bottom
#define defmBounds_RHRMAZ        704                         // right

// for the Full Page Display
//
#define defmBounds_TFP           0                           // top
#define defmBounds_LFP           0                           // left
#define defmBounds_BFP           870                         // bottom
#define defmBounds_RFP           640                         // right

#define defmBounds_TFPb           0                           // top
#define defmBounds_LFPb           0                           // left
#define defmBounds_BFPb           818                         // bottom
#define defmBounds_RFPb           640                         // right

// for the noninterlaced Apple // GS Monitor
//
#define defmBounds_TGS           0                           // top
#define defmBounds_LGS           0                           // left
#define defmBounds_BGS           384                         // bottom
#define defmBounds_RGS           512                         // right

// for the Mac SE-Type monitor
//
#define defmBounds_TSE           0                           // top
#define defmBounds_LSE           0                           // left
#define defmBounds_BSE           342                         // bottom
#define defmBounds_RSE           512                         // right

// for the Apple // emulation mode on the Rubik display 
//
#define defmBounds_TA2Em         0                           // top
#define defmBounds_LA2Em         0                           // left
#define defmBounds_BA2Em         384                         // bottom
#define defmBounds_RA2Em         560                         // right

#define defmBounds_TGS560        0                           // top
#define defmBounds_LGS560        0                           // left
#define defmBounds_BGS560        384                         // bottom
#define defmBounds_RGS560        560                         // right

// for VGA-compatible displays
//
#define defmBounds_TVGA          0                           // top
#define defmBounds_LVGA          0                           // left
#define defmBounds_BVGA          480                         // bottom
#define defmBounds_RVGA          640                         // right

// for SuperVGA-compatible displays
//
#define defmBounds_TSVGA         0                           // top
#define defmBounds_LSVGA         0                           // left
#define defmBounds_BSVGA         600                         // bottom
#define defmBounds_RSVGA         800                         // right

// for Landscape Page (Goldfish) displays
//
#define defmBounds_TLP           0                           // top
#define defmBounds_LLP           0                           // left
#define defmBounds_BLP           624                         // bottom
#define defmBounds_RLP           832                         // right 

#define defmBounds_TGF           0                           // top
#define defmBounds_LGF           0                           // left
#define defmBounds_BGF           624                         // bottom
#define defmBounds_RGF           832                         // right 

// for 19” displays
//
#define defmBounds_T19           0                           // top
#define defmBounds_L19           0                           // left
#define defmBounds_B19           768                         // bottom
#define defmBounds_R19           1024                        // right

// for 2-Page displays
//
#define defmBounds_T2P           0                           // top
#define defmBounds_L2P           0                           // left
#define defmBounds_B2P           870                         // bottom
#define defmBounds_R2P           1152                        // right

// For NTSC (Full Frame) displays
//
#define defmBounds_TNTSCFF       0                           // top
#define defmBounds_LNTSCFF       0                           // left
#define defmBounds_BNTSCFF       480                         // bottom
#define defmBounds_RNTSCFF       640                         // right

// For NTSC (Safe Title) displays
//
#define defmBounds_TNTSCST       0                           // top
#define defmBounds_LNTSCST       0                           // left
#define defmBounds_BNTSCST       384                         // bottom
#define defmBounds_RNTSCST       512                         // right 

// For PAL (Full Frame) displays
//
#define defmBounds_TPALFF        0                           // top
#define defmBounds_LPALFF        0                           // left
#define defmBounds_BPALFF        576                         // bottom
#define defmBounds_RPALFF        768                         // right

// For PAL (Safe Title) displays
//
#define defmBounds_TPALST        0                           // top
#define defmBounds_LPALST        0                           // left
#define defmBounds_BPALST        480                         // bottom
#define defmBounds_RPALST        640                         // right

// for the TIM/DB-Lite LCD display
//
#define defmBounds_TLCD          0                           // top
#define defmBounds_LLCD          0                           // left
#define defmBounds_BLCD          400                         // bottom
#define defmBounds_RLCD          640                         // right

// for the VGA-sized (“Big”) LCD display
//
#define defmBounds_TBigLCD       0                           // top
#define defmBounds_LBigLCD       0                           // left
#define defmBounds_BBigLCD       480                         // bottom
#define defmBounds_RBigLCD       640                         // right

#define defmBounds_THR399       0                           // top
#define defmBounds_LHR399       0                           // left
#define defmBounds_BHR399       399                         // bottom
#define defmBounds_RHR399       640                         // right

// for the Apollo display
//
#define defmBounds_TApollo       0                           // top
#define defmBounds_LApollo       0                           // left
#define defmBounds_BApollo       342                         // bottom
#define defmBounds_RApollo       512                         // right

//
// screen resolution in dpi (fixed format)
//

#define HResHR                   $480000                     // 72 HPixels/inch
#define VResHR                   $480000                     // 72 VPixels/inch

#define HResFP                   $500000                     // 80 HPixels/inch
#define VResFP                   $500000                     // 80 VPixels/inch

#define HResGS                   $480000                     // 72 HPixels/inch
#define VResGS                   $480000                     // 72 VPixels/inch

#define HResSE                   $480000                     // 72 HPixels/inch
#define VResSE                   $480000                     // 72 VPixels/inch

#define HResA2Em                 $480000                     // 72 HPixels/inch
#define VResA2Em                 $480000                     // 72 VPixels/inch

#define HRes2P                   $4D0000                     // 77 HPixels/inch
#define VRes2P                   $4D0000                     // 77 VPixels/inch

#define HResLP                   $480000                     // 72 HPixels/inch
#define VResLP                   $480000                     // 72 VPixels/inch

#define HResGF                   $480000                     // 72 HPixels/inch
#define VResGF                   $480000                     // 72 VPixels/inch

#define HRes19                   $480000                     // 72 HPixels/inch
#define VRes19                   $480000                     // 72 VPixels/inch

#define HResNTSC                 $480000                     // 72 HPixels/inch
#define VResNTSC                 $480000                     // 72 VPixels/ince

#define HResPAL                  $480000                     // 72 HPixels/inch
#define VResPAL                  $480000                     // 72 HPixels/inch

#define HResLCD                  $480000                     // 72 HPixels/inch
#define VResLCD                  $480000                     // 72 VPixels/inch

#define HResApollo               $480000                     // 72 HPixels/inch
#define VResApollo               $480000                     // 72 VPixels/inch

//---------------------------------------------------
//
// Miscellaneous constants
//
//---------------------------------------------------

#define IndexedBlack             (-1)                          // black for indexed modes
#define DirectBlack               0                          // black for direct modes

#define IndexedWhite              0                          // white for indexed modes
#define DirectWhite              (-1)                          // white for direct modes

#define OneBitGray               $AAAAAAAA
#define TwoBitGray               $CCCCCCCC
#define FourBitGray              $F0F0F0F0
#define EightBitGray             $FF00FF00
#define SixteenBitGray           $0000FFFF
#define ThirtyTwoBitGray         $00000000                   // need to do this twice (2nd time NOT’d)

#define GrayPatSize              4

#define defVersion               0                           // Version = 0
#define defPixelType             0                           // pixeltype=chunky
#define ChunkyDirect             16                          // pixelType=ChunkyDirect
#define defCmpCount              1                           // Number of components in pixel
#define defmPlaneBytes           0                           // Offset from one plane to the next

#define defmDevType              (clutType)                    // clutType = 0

#define defMinorBase             0                           // Video RAM Offset is 0

//
// Each different video configuration has a different RAM length field.  These are the
//   length requirements for each RBV configuration, varying from one-bit only to up to eight
//   bit modes.  The MMU allocation table's rounding factor is 32K, so these values are
//   rounded to that size.  The size table that this is based on is included in the
//   GetRBVSize routine in StartInit.a.  The [a,b,c,d] assignment reflects the way that
//   the spIDs were assigned ('a' is the normal default, 'b' was the 1MB main RAM default,
//   'c' and 'd' were assigned if those modes were possible).
//

#define MinorLengthHRa       ((defmBounds_RHR*defmBounds_BHR*8)/8) // RAM for up to 8-bit mode
#define MinorLengthHRb       ((defmBounds_RHR*defmBounds_BHR*1)/8) // RAM for up to 1-bit mode
#define MinorLengthHRc       ((defmBounds_RHR*defmBounds_BHR*4)/8) // RAM for up to 4-bit mode
#define MinorLengthHRd       ((defmBounds_RHR*defmBounds_BHR*2)/8) // RAM for up to 2-bit mode

#define MinorLengthGSa       ((defmBounds_RGS*defmBounds_BGS*8)/8) // RAM for up to 8-bit mode
#define MinorLengthGSb       ((defmBounds_RGS*defmBounds_BGS*1)/8) // RAM for up to 1-bit mode
#define MinorLengthGSc       ((defmBounds_RGS*defmBounds_BGS*4)/8) // RAM for up to 4-bit mode
#define MinorLengthGSd       ((defmBounds_RGS*defmBounds_BGS*2)/8) // RAM for up to 2-bit mode

#define MinorLengthSEa       ((defmBounds_RSE*defmBounds_BSE*8)/8) // RAM for up to 8-bit mode
#define MinorLengthSEb       ((defmBounds_RSE*defmBounds_BSE*1)/8) // RAM for up to 1-bit mode
#define MinorLengthSEc       ((defmBounds_RSE*defmBounds_BSE*4)/8) // RAM for up to 4-bit mode
#define MinorLengthSEd       ((defmBounds_RSE*defmBounds_BSE*2)/8) // RAM for up to 2-bit mode

#define MinorLengthFPa       ((defmBounds_RFP*defmBounds_BFP*4)/8) // RAM for up to 4-bit mode
#define MinorLengthFPb       ((defmBounds_RFP*defmBounds_BFP*1)/8) // RAM for up to 1-bit mode
#define MinorLengthFPc       ((defmBounds_RFP*defmBounds_BFP*2)/8) // RAM for up to 2-bit mode

//
// Here are the minor lengths for V8 configurations.  Each depth has the same rowbytes for
//   a particular vRAM configuration, so there aren't as many permutations as for the RBV.
//   As in the declaration structures, 'a' configuration is the 512K flavor, and 'b' is the 256K 
//   vRAM configuration.
//
#define MinorLength_V8_HRa       ((1024*defmBounds_BHR))   
#define MinorLength_V8_HRb       (( 512*defmBounds_BHR))

#define MinorLength_V8_GSa       ((1024*defmBounds_BGS))
#define MinorLength_V8_GSb       (( 512*defmBounds_BGS))

#define MinorLength_V8_VGAa      ((1024*defmBounds_BVGA))      
#define MinorLength_V8_VGAb      (( 512*defmBounds_BVGA))

#define MinorLength_V8_A2Ema     ((1024*defmBounds_BA2Em))     // RAM for any depth on V8 w/512K vRAM
#define MinorLength_V8_A2Emb     (( 512*defmBounds_BA2Em))     // RAM for any depth on V8 w/256K vRAM

//
// Here are the minor lengths for the DAFB configurations.  These reflect the frame
//   buffer size at the greatest screen depth for a given memory configuration.  Note
//   that rowbytes is constant for a given depth and display (i.e., you may change
//   rowbytes on a depth-to-depth change, but 4-bit Hi-Res mode ALWAYS has the same
//   rowbytes regardless if you have 0.5M,1.0M, or 2.0M of vRAM).
//
#define MinorLength_DAFB_FPa                 ((DAFB_512_RB*defmBounds_BFP))
#define MinorLength_DAFB_FPb                 ((DAFB_1024_RB*defmBounds_BFP))
#define MinorLength_DAFB_2Pa                 ((DAFB_576_RB*defmBounds_B2P))
#define MinorLength_DAFB_2Pb                 ((DAFB_1152_RB*defmBounds_B2P))
#define MinorLength_DAFB_LPa                 ((DAFB_832_RB*defmBounds_BLP))
#define MinorLength_DAFB_LPax                ((DAFB_1664_RB*defmBounds_BLP))
#define MinorLength_DAFB_LPb                 ((DAFB_3328_RB*defmBounds_BLP))
#define MinorLength_DAFB_GSa                 ((DAFB_1024_RB*defmBounds_BGS))
#define MinorLength_DAFB_GSb                 ((DAFB_2048_RB*defmBounds_BGS))
#define MinorLength_DAFB_HRa                 ((DAFB_1024_RB*defmBounds_BHR))
#define MinorLength_DAFB_HRax                ((DAFB_2048_RB*defmBounds_BHR))
#define MinorLength_DAFB_HRb                 ((DAFB_4096_RB*defmBounds_BHR))
#define MinorLength_DAFB_VGAa                ((DAFB_1024_RB*defmBounds_BVGA))
#define MinorLength_DAFB_VGAax               ((DAFB_2048_RB*defmBounds_BVGA))
#define MinorLength_DAFB_VGAb                ((DAFB_4096_RB*defmBounds_BVGA))
#define MinorLength_DAFB_NTSCFFa             ((DAFB_1024_RB*defmBounds_BNTSCFF))
#define MinorLength_DAFB_NTSCFFax            ((DAFB_2048_RB*defmBounds_BNTSCFF))
#define MinorLength_DAFB_NTSCFFb             ((DAFB_4096_RB*defmBounds_BNTSCFF))
#define MinorLength_DAFB_NTSCconvFF          ((DAFB_1024_RB*defmBounds_BNTSCFF))
#define MinorLength_DAFB_NTSCSTa             ((DAFB_1024_RB*defmBounds_BNTSCST))
#define MinorLength_DAFB_NTSCSTax            ((DAFB_2048_RB*defmBounds_BNTSCST))
#define MinorLength_DAFB_NTSCSTb             ((DAFB_4096_RB*defmBounds_BNTSCST))
#define MinorLength_DAFB_NTSCconvST          ((DAFB_1024_RB*defmBounds_BNTSCST))
#define MinorLength_DAFB_PALFFa              ((DAFB_832_RB*defmBounds_BPALFF))
#define MinorLength_DAFB_PALFFax             ((DAFB_1664_RB*defmBounds_BPALFF))
#define MinorLength_DAFB_PALFFb              ((DAFB_3328_RB*defmBounds_BPALFF))
#define MinorLength_DAFB_PALconvFF           ((DAFB_1024_RB*defmBounds_BPALFF))
#define MinorLength_DAFB_PALSTa              ((DAFB_832_RB*defmBounds_BPALST))
#define MinorLength_DAFB_PALSTax             ((DAFB_1664_RB*defmBounds_BPALST))
#define MinorLength_DAFB_PALSTb              ((DAFB_3328_RB*defmBounds_BPALST))
#define MinorLength_DAFB_PALconvST           ((DAFB_1024_RB*defmBounds_BPALST))
#define MinorLength_DAFB_SVGAa               ((DAFB_832_RB*defmBounds_BSVGA))
#define MinorLength_DAFB_SVGAax              ((DAFB_1664_RB*defmBounds_BSVGA))
#define MinorLength_DAFB_SVGAb               ((DAFB_3328_RB*defmBounds_BSVGA))
#define MinorLength_DAFB_FPbx                ((DAFB_2048_RB*defmBounds_BFP))
#define MinorLength_DAFB_2Pbx                ((DAFB_2304_RB*defmBounds_B2P))

#define MinorLength_DAFB_19a                 ((DAFB_512_RB*defmBounds_B19))            
#define MinorLength_DAFB_19b                 ((DAFB_1024_RB*defmBounds_B19))
#define MinorLength_DAFB_19bx                ((DAFB_2048_RB*defmBounds_B19))   

// Here is the minor lengths for LCD-based CPUs.
//
#define MinorLengthLCD						(defmBounds_RLCD*defmBounds_BLCD*1)/8				// RAM for 1-bit mode 
#define MinorLengthGSCLCD					(defmBounds_RLCD*defmBounds_BLCD*4)/8				// RAM for 4-bit mode
#define MinorLengthGSC480					(defmBounds_RBigLCD*defmBounds_BBigLCD*4)/8			// RAM for 4-bit mode

#define MinorLength_640x400					(defmBounds_RLCD*defmBounds_BLCD*16)/8				// RAM for 16-bit mode.
#define MinorLength_640x480					(defmBounds_RBigLCD*defmBounds_BBigLCD*8)/8			// RAM for 8-bit mode.

// VSC

#define MinorLength_VSC_FPa			(FBMHRRB*defmBounds_BFP)
#define MinorLength_VSC_FPb			(EBMHRRB*defmBounds_BFP)
#define MinorLength_VSC_GS			(EBMHRRB*defmBounds_BGS)
#define MinorLength_VSC_HR			(EBMHRRB*defmBounds_BHR)

// Here is the minor length for Apollo.
// 
#define MinorLengthApollo                    ((defmBounds_RApollo*defmBounds_BApollo*1)/8)     // RAM for 1-bit mode.

// Here are the minor lengths for Sonora CPUs.
//
#define MinorLength_Sonora_FP                ((OBMFPRB*defmBounds_BFP))                        // Also used by RGBFP.
#define MinorLength_Sonora_FPa               ((TBMFPRB*defmBounds_BFP))
#define MinorLength_Sonora_FPb               ((FBMFPRB*defmBounds_BFP))
#define MinorLength_Sonora_FPc               ((EBMFPRB*defmBounds_BFP))

#define MinorLength_Sonora_GS                ((OBMGSRB*defmBounds_BGS))
#define MinorLength_Sonora_GSa               ((EBMGSRB*defmBounds_BGS))
#define MinorLength_Sonora_GSb               ((D16BMGSRB*defmBounds_BGS))

#define MinorLength_Sonora_GS560a            ((EBMGS560RB*defmBounds_BGS560))
#define MinorLength_Sonora_GS560b            ((D16BMGS560RB*defmBounds_BGS560))

#define MinorLength_Sonora_HR                ((OBMHRRB*defmBounds_BHR))                        // Also used by VGA.
#define MinorLength_Sonora_HRa               ((FBMHRRB*defmBounds_BHR))
#define MinorLength_Sonora_HRb               ((EBMHRRB*defmBounds_BHR))
#define MinorLength_Sonora_HRc               ((D16BMHRRB*defmBounds_BHR))

#define MinorLength_Sonora_HR400a            ((EBMHRRB*defmBounds_BHR400))
#define MinorLength_Sonora_HR400b            ((D16BMHRRB*defmBounds_BHR400))

#define MinorLength_Sonora_GF                ((OBMGFRB*defmBounds_BGF))
#define MinorLength_Sonora_GFa               ((TBMGFRB*defmBounds_BGF))
#define MinorLength_Sonora_GFb               ((EBMGFRB*defmBounds_BGF))


// Here are the minor lengths for Civic CPUs.
//
#define MinorLength_Civic_FPa                ((Civic_1024_RB*defmBounds_BFP))
#define MinorLength_Civic_FPb                ((Civic_2048_RB*defmBounds_BFP))

#define MinorLength_Civic_viFPa              ((Civic_512_RB*defmBounds_BFP))
#define MinorLength_Civic_viFPb              ((Civic_1024_RB*defmBounds_BFP))

#define MinorLength_Civic_GS                 ((Civic_2048_RB*defmBounds_BGS))
#define MinorLength_Civic_GS560              ((Civic_2560_RB*defmBounds_BGS560))

#define MinorLength_Civic_2Pa                ((Civic_1152_RB*defmBounds_B2P))
#define MinorLength_Civic_vi2Pa              ((Civic_576_RB*defmBounds_B2P))
#define MinorLength_Civic_2Pb                ((Civic_2304_RB*defmBounds_B2P))

#define MinorLength_Civic_NTSCFFa            ((Civic_2048_RB*defmBounds_BNTSCFF))
#define MinorLength_Civic_NTSCFFb            ((Civic_2560_RB*defmBounds_BNTSCFF))
#define MinorLength_Civic_NTSCST             ((Civic_2048_RB*defmBounds_BNTSCST))

#define MinorLength_Civic_NTSCFFConv         ((Civic_1024_RB*defmBounds_BNTSCFF))
#define MinorLength_Civic_NTSCSTConv         ((Civic_1024_RB*defmBounds_BNTSCST))

#define MinorLength_Civic_HRa                ((Civic_2048_RB*defmBounds_BHR))
#define MinorLength_Civic_HRb                ((Civic_2560_RB*defmBounds_BHR))
#define MinorLength_Civic_HR400              ((Civic_2560_RB*defmBounds_BHR400))
#define MinorLength_Civic_HRMAZa             ((Civic_1664_RB*defmBounds_BHRMAZ))
#define MinorLength_Civic_HRMAZb             ((Civic_3328_RB*defmBounds_BHRMAZ))

#define MinorLength_Civic_viHRa              ((Civic_1024_RB*defmBounds_BHR))
#define MinorLength_Civic_viHRb              ((Civic_2048_RB*defmBounds_BHR))
#define MinorLength_Civic_viHR400            ((Civic_1280_RB*defmBounds_BHR400))
#define MinorLength_Civic_viHRMAZa           ((Civic_832_RB*defmBounds_BHRMAZ))
#define MinorLength_Civic_viHRMAZb           ((Civic_1664_RB*defmBounds_BHRMAZ))

#define MinorLength_Civic_PALFFa             ((Civic_1664_RB*defmBounds_BPALFF))
#define MinorLength_Civic_PALFFb             ((Civic_3328_RB*defmBounds_BPALFF))
#define MinorLength_Civic_PALSTa             ((Civic_1024_RB*defmBounds_BPALST))
#define MinorLength_Civic_PALSTb             ((Civic_2048_RB*defmBounds_BPALST))

#define MinorLength_Civic_PALFFConv          ((Civic_1024_RB*defmBounds_BPALFF))
#define MinorLength_Civic_PALSTConv          ((Civic_1024_RB*defmBounds_BPALST))

#define MinorLength_Civic_viPALFF            ((Civic_1664_RB*defmBounds_BPALFF))

#define MinorLength_Civic_VGAa               ((Civic_2048_RB*defmBounds_BVGA))
#define MinorLength_Civic_VGAb               ((Civic_2560_RB*defmBounds_BVGA))

#define MinorLength_Civic_SVGAa              ((Civic_1664_RB*defmBounds_BSVGA))
#define MinorLength_Civic_SVGAb              ((Civic_3328_RB*defmBounds_BSVGA))

#define MinorLength_Civic_GFa                ((Civic_1664_RB*defmBounds_BGF))
#define MinorLength_Civic_GFb                ((Civic_3328_RB*defmBounds_BGF))

#define MinorLength_Civic_19a                ((Civic_1024_RB*defmBounds_B19))
#define MinorLength_Civic_19b                ((Civic_2048_RB*defmBounds_B19))

// Misc…
//
#define defmBaseOffset                       0                       // Offset to base of video RAM
#define Civic_M512_Offset                    -512             // Offset to base of video RAM for some Civic modes
#define Civic_1280_Offset                    1280             // Offset to base of video RAM for some Civic modes
#define Civic_1792_Offset                    1792             // Offset to base of video RAM for some Civic modes
#define Civic_2048_Offset                    2048             // Offset to base of video RAM for some Civic modes

// For NTSC, we have two sizes:  “Safe Title” (ST) and “Full Frame” (FF), where ST is the
// smaller size.  Because QuickDraw doesn’t support a changing base address, we have to
// “lie” to it about where the base address really is.  So, we do this with an offset.
// To calculate the offset, we do the following.  First, we calculate the horizontal offset.
// We know that there are 1024 “real” pixels and 640 viewable pixels for NTSCFF.  So, we
// have (with 512 viewable pixels for NTSCST):
//
//           640 - 512 = 128  (difference between FF and ST).
//           128/2     =  64  (calculate the center).
//
// To calculate the vertical offset, we know there are 480 viewable rows for NTSCFF and
// 384 for NTSCST:
//
//           480 - 384 =  96 (difference between FF and ST).
//           96/2      =  48 (calculate the center).
//
// In order to calculate the base offset, we now just multiply the vertical dimension
// by rowbytes (1024 in 1-8bb, and 4096 in 32bpp), and add in the number of pixels
// we want per depth (for 1-8bb 64/bpp and 64*4 for 32bpp for rowbytes).
//
// Similar logic was used to derive the PAL base address offsets.
//
//
#define NTSC_RB                  (DAFB_1024_RB)                // Rowbytes for the indexed modes for NTSC
#define PAL_RB                   (DAFB_832_RB)                 //   and PAL.
#define PAL_RB_Conv              (DAFB_1024_RB)                //

#define NTSC_Mid_RB              (DAFB_2048_RB)                // Rowbytes for the direct modes for NTSC
#define NTSC_Big_RB              (DAFB_4096_RB)                //   and PAL.
#define PAL_Mid_RB               (DAFB_1664_RB)                //
#define PAL_Big_RB               (DAFB_3328_RB)                //

#define defmNTSCSTBase           ((NTSC_RB*48))                // Offset to NTSCST base, 1-8bpp.
#define defmNTSCSTB1             (defmNTSCSTBase+(64/8))       // defmNTSCSTBase + 64 pixels (by depth).
#define defmNTSCSTB2             (defmNTSCSTBase+(64/4))       //
#define defmNTSCSTB4             (defmNTSCSTBase+(64/2))       //
#define defmNTSCSTB8             (defmNTSCSTBase+(64/1))       //
#define defmNTSCSTB16            ((NTSC_Mid_RB*48)+(64*2))     // 16bpp defmNTSCSTBase + 64 pixels.
#define defmNTSCSTB32            ((NTSC_Big_RB*48)+(64*4))     // 32bpp defmNTSCSTBase + 64 pixels.

#define defmPALSTBase            ((PAL_RB*48))                 // Offset to PALST base, 1-8bb.
#define defmPALSTB1              (defmPALSTBase+(64/8))        // defmPALSTBase + 64 pixels (by depth).
#define defmPALSTB2              (defmPALSTBase+(64/4))        //
#define defmPALSTB4              (defmPALSTBase+(64/2))        //
#define defmPALSTB8              (defmPALSTBase+(64/1))        //
#define defmPALSTB16             ((PAL_Mid_RB*48)+(64*2))      // 16bpp defmPALSTBase + 64 pixels.
#define defmPALSTB32             ((PAL_Big_RB*48)+(64*4))      // 32bpp defmPALSTBase + 64 pixels.

#define defmPALSTBConv           ((PAL_RB_Conv*48))            // Offset to PALST base convolved, 1-8bb.
#define defmPALSTB1Conv          (defmPALSTBConv+(64/8))       // defmPALSTBConv + 64 pixels (by depth).
#define defmPALSTB2Conv          (defmPALSTBConv+(64/4))       //
#define defmPALSTB4Conv          (defmPALSTBConv+(64/2))       //
#define defmPALSTB8Conv          (defmPALSTBConv+(64/1))       //

#define bSlot0rbv                6                           // bit # of slot zero interrupt enable
                                                        //   in RBV slot interrupt enable register
#define bEnable                  7                           // bit # that writes ones when
                                                        //   talking to interrupts register
                                                                                                                
//
// These are the monitor ID's as seen by the RBV sense register
//

#define FPIdMono                 1                           // full page monitor, monochrome
#define GSId                     2                           // 512*384
#define FPIdColor                5                           // full page monitor, color
#define HRId                     6                           // 640*480
#define SEId                     7                           // 512*342

//
// Because we ran out of contiguous functional sRsrc IDs in the Zydeco time-frame,
//   we came up with a method of having sRsrc directory directories, or super
//   sRsrc directories.  The method of choosing which super sRsrc directory
//   is applicable is the responsibility of a new piece of code called a
//   SuperInit.  For CPUs done in the Zydeco (or Zydeco-near) time frame, 
//   the sRsrcBFBasedDir is used.  For unknown CPUs, a minimal sRsrc directory
//   is selected.  All other CPUs can have their own sRsrc directories.
//
#define sRsrcUnknownDir          1                           // sRsrc Directory for unknown CPUs.
#define sRsrcUnknownBd           1                           // Unknown board sRsrc.

#define sRsrcBFBasedDir          $7F                         // CPUs supported in the BoxFlag-based sRsrc directory.
#define sRsrcSonoraDir           $7E                         // CPUs supported in the Sonora sRsrc directory.
#define sRsrcCivicDir            $7D                         // CPUs supported in the Civic sRsrc directory.
#define sRsrcCSCDir				 $7C						 // CPUS supported in the CSC sRsrc directory.
#define sRsrcATIDir				 $7B						 // CPUS supported in the ATI sRsrc directory.

//---------------------------------------------------------------------
//   General and sRsrc IDs in the sRsrcZydecoDir Directory
//---------------------------------------------------------------------

//
// These are the local definitions for the sRsrcIDs in the slot zero (RBV) video config
//   ROM.  The naming convention is pretty simple:
//
//               sRsrcID = sRsrc_VidXxxYYz, where
//
//                   Xxx = built-in video CPU name,  Rbv for Mac IIci and Erickson
//                                                   Els for Elsie
//                                                   Ecl for Eclipse
//                                                   Por for Waimea
//                   YY = display type,  HR for High-Resolution Display (640*480)
//                                       FP for Portrait Display (640*870)
//                                       GS for Rubik Display (512*384)
//                                       SE for SE-link 9" monitor (512*342)
//                   z  = memory allocation configuration - each sRsrc list supports
//                        a different set of screen depths.  This part of the name
//                        just makes each configuration unique.  There's no 16 vs. 25
//                        MHz identifier now, since all screen depth combinations are
//                        enumerated.
//                                           
// PrimaryInit handles these configurations differently depending on the amount of 
//   RAM available in the CPU.  By default, if more than 1MB of RAM is available in
//   the system, then the full capacity sRsrc for this monitor is selected.  If only
//   1MB is available, then the 1-bit only sRsrc is selected.  This default can be over-
//   ridden by the user in Monitors.
//
// Here's how the sRsrc IDs are assigned:
//
//               Bit 7 = always set for video sRsrc IDs (by convention)
//               Bit 6 = with bit 5, identifies the type of CPU.  00=ci/Erickson
//               Bit 5 =   01=Elsie
//               Bit 4 = option bit 2, set for 16Mhz default configurations
//               Bit 3 = option bit 1, set for 1MB default configurations
//               Bit 2 = RBV monitor ID bit
//               Bit 1 = RBV monitor ID bit
//               Bit 0 = RBV monitor ID bit
//
// The low-order bits are shifted over from what's read in the RBV monitor ID register.
//   They are shifted down to make it easier to make decisions about screen size, etc
//   later.  The high bit is always set to distinguish function sRsrc lists from
//   system-defined lists.  The two option bits describe alternate sRsrc lists which
//   differ in the different available screen depths.  There are up to four combinations
//   of the bits - 1-bit only, 1- and 2-bit only, 1-,2-, and 4-bit, and (for some
//   monitors) 1-,2-,4-, and 8-bit modes. The actual combinations are arbitrary, but
//   are contrived so that the defaults for different CPU configurations (clock speed
//   and memory) can be generated by setting a single bit.  The other combinations are
//   valid, but must be selected via the video family selector in Monitors.  For
//   example, a 5MB Aurora 25 w/HR monitor sets is spID $86.  This same combo with 
//   1MB of RAM is $8E, and so on.  

//
// The IDs for the multiple board sRsrcs are based directly on the boxFlag identifier.
//   These sRsrcs are tagged as inactive at startup.  Only the Aurora25 board resource
//   is active at start, so it determines the system configuration and installs the
//   appropriate board sRsrc list.
//

//
// The PrimaryInit code DEPENDS on never allowing $80 to be a valid video sRsrc spID.
//

//
// The sRsrcID for each board resource is equal to it's boxflag+shift value.  The shift is required 
//   since the Mac II box flag is 0, but 0 is an illegal spID value to the Slot Manager
//

#define BoardspIDShift           1                                 		// board spID shift value

#define sRsrc_BdMacII            (boxMacII+BoardspIDShift)        		// (0+BoardspIDShift)
#define sRsrc_BdMacIIx           (boxMacIIx+BoardspIDShift)       		// (1+BoardspIDShift)
#define sRsrc_BdMacIIcx          (boxMacIIcx+BoardspIDShift)      		// (2+BoardspIDShift)
#define sRsrc_BdMacSE30          (boxSE30+BoardspIDShift)          		// (3+BoardspIDShift)
#define sRsrc_BdMacIIci          (boxMacIIci+BoardspIDShift)      		// (5+BoardspIDShift)
#define sRsrc_BdMacIIfx          (boxMacIIfx+BoardspIDShift)      		// (7+BoardspIDShift)
#define sRsrc_BdErickson         (boxMacIIsi+BoardspIDShift)       		// (12+BoardspIDShift)
#define sRsrc_BdElsie            (boxMacLC+BoardspIDShift)         		// (13+BoardspIDShift)
#define sRsrc_BdEclipse          (boxQuadra900+BoardspIDShift)     		// (14+BoardspIDShift)
#define sRsrc_BdTIM              (boxPowerBook170+BoardspIDShift)  		// (15+BoardspIDShift)
#define sRsrc_BdSpike            (boxQuadra700+BoardspIDShift)     		// (16+BoardspIDShift)
#define sRsrc_BdApollo           (boxClassicII+BoardspIDShift)     		// (17+BoardspIDShift)
#define sRsrc_BdTIMLC            (boxPowerBook140+BoardspIDShift)  		// (19+BoardspIDshift)
#define sRsrc_BdZydeco           (boxQuadra950+BoardspIDShift)     		// (20+BoardspIDShift)
#define sRsrc_BdDBLite25         (boxPowerBookDuo210+BoardspIDShift)    // (23+BoardspIDShift)
#define sRsrc_BdWombat25         (boxCentris650+BoardspIDShift)      	// (24+BoardspIDShift)
#define sRsrc_BdDBLite33         (boxPowerBookDuo230+BoardspIDShift)	// (26+BoardspIDshift)
#define sRsrc_BdDartanian        (boxPowerBook180+BoardspIDShift)     	// (27+BoardsplDshift)
#define sRsrc_BdDartanianLC      (boxPowerBook160+BoardspIDShift)   	// (28+BoardspIDShift)
#define sRsrc_BdWombat33F        (boxQuadra800+BoardspIDShift)     		// (29+BoardspIDShift)
#define sRsrc_BdWombat33         (boxQuadra650+BoardspIDShift)      	// (30+BoardspIDShift)
#define sRsrc_BdLCII			 (boxMacLCII+BoardspIDShift)	   		// (31+BoardspIDShift) <SM5>
#define sRsrc_BdDBLite16         (boxPowerBookDuo250+BoardspIDShift)	// (32+BoardspIDshift)	<SM25>
#define sRsrc_BdDBLite20         (boxPenLite+BoardspIDShift)      		// (33+BoardspIDshift)	<SM25>
#define sRsrc_BdWombat40         (boxWombat40+BoardspIDShift)     		// (45+BoardspIDShift)
#define sRsrc_BdWLCD20           (boxCentris610+BoardspIDShift)        	// (46+BoardspIDShift)
#define sRsrc_BdWLCD25           (boxQuadra610+BoardspIDShift)        	// (47+BoardspIDShift)
#define sRsrc_BdWombat20         (boxWombat20+BoardspIDShift)      		// (52+BoardspIDshift)
#define sRsrc_BdWombat40F        (boxWombat40F+BoardspIDShift)    		// (53+BoardspIDshift)
#define sRsrc_BdRiscQuadra700	 (boxRiscQuadra700+BoardspIDShift)   	// (55+BoardspIDShift)	<SM21>
#define sRsrc_BdWLCD33			 (boxWLCD33+BoardspIDShift)		 		// (57+BoardspIDshift)
#define sRsrc_BdRiscCentris650   (boxRiscCentris650+BoardspIDShift)    	// (76+BoardspIDShift)	<SM21>
#define sRsrc_BdRiscQuadra900    (boxRiscQuadra900+BoardspIDShift)    	// (98+BoardspIDShift)	<SM21>
#define sRsrc_BdRiscQuadra950    (boxRiscQuadra950+BoardspIDShift)    	// (99+BoardspIDShift)	<SM21>
#define sRsrc_BdRiscCentris610   (boxRiscCentris610+BoardspIDShift)    	// (100+BoardspIDShift)	<SM21>
#define sRsrc_BdRiscQuadra800	 (boxRiscQuadra800+BoardspIDShift)    	// (101+BoardspIDShift)	<SM21>
#define sRsrc_BdRiscQuadra610	 (boxRiscQuadra610+BoardspIDShift)    	// (102+BoardspIDShift)	<SM22>
#define sRsrc_BdRiscQuadra650	 (boxRiscQuadra650+BoardspIDShift)    	// (103+BoardspIDShift)	<SM22>
#define sRsrc_BdSTPQ700			 (boxSTPQ700+BoardspIDShift)			// (110+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPQ900			 (boxSTPQ900+BoardspIDShift)			// (111+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPQ950			 (boxSTPQ950+BoardspIDShift)			// (112+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPC610			 (boxSTPC610+BoardspIDShift)			// (113+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPC650			 (boxSTPC650+BoardspIDShift)			// (114+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPQ610			 (boxSTPQ610+BoardspIDShift)			// (115+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPQ650			 (boxSTPQ650+BoardspIDShift)			// (116+BoardspIDshift)	<SM27>
#define sRsrc_BdSTPQ800			 (boxSTPQ800+BoardspIDShift)			// (117+BoardspIDshift)	<SM27>

// -------- RBV System sRsrc IDs --------

#define sRsrc_VidRbvHRa          $86                             // Mac II High-Res Display (1,2,4,8)
#define sRsrc_VidRbvHRb          $96                             // Mac II High-Res Display (1,2,4)
#define sRsrc_VidRbvHRc          $9E                             // Mac II High-Res Display (1,2)
#define sRsrc_VidRbvHRd          $8E                             // Mac II High-Res Display (1 only)

#define sRsrc_VidRbvFPa          $81                             // Page Display (1,2,4)
#define sRsrc_VidRbvFPb          $91                             // Page Display (1,2)
#define sRsrc_VidRbvFPc          $89                             // Page Display (1 only)

#define sRsrc_VidRbvGSa          $82                             // nonInterlaced GS Display (1,2,4,8)
#define sRsrc_VidRbvGSb          $92                             // nonInterlaced GS Display (1,2,4)
#define sRsrc_VidRbvGSc          $9A                             // nonInterlaced GS Display (1,2)
#define sRsrc_VidRbvGSd          $8A                             // nonInterlaced GS Display (1 only)

#define sRsrc_VidRbvSEa          $87                             // Mac SE display (1,2,4,8)
#define sRsrc_VidRbvSEb          $97                             // Mac SE display (1,2,4)
#define sRsrc_VidRbvSEc          $9F                             // Mac SE display (1,2)
#define sRsrc_VidRbvSEd          $8F                             // Mac SE display (1 only)

// -------- Elsie V8 sRsrc IDs --------

// in this set of IDs, the bits are assigned by feature:
//
//           Bit 7       =   always on for functional sRsrcIDs
//           Bit 6-5     =   01 for Elsie/V8
//           Bit 4       =   0 if vRAM video, 1 if no vRAM with Jersey, 1 if A2 mode with Rubik
//           Bit 3       =   0 if 512K vRAM, 1 if 256K vRAM
//           Bit 2-0     =   monitor ID bits (010 = Rubik, 110 = Hi-Res RGB, 011 = VGA).  These
//                           sense combinations are similar to the RBV, but the V8 doesn't support
//                           the portrait display.  The VGA has an extended sense combination that
//                           looks like the portrait code if the lines aren't driven.  So we effectively
//                           share that code.
//

#define sRsrc_NeverMatch         $A0                // This sRsrc is NEVER implemented!  It's
                                                    //   used to allow sRsrc pruning to work 
                                                    //   with no connected display.
                                                    // It is used by all slot zero configurations.

#define sRsrc_Vid_V8_GSa         $A2                // 512K VRAM V8 + Rubik (1,2,4,8,16)
#define sRsrc_Vid_V8_GSb         $AA                // 256K VRAM V8 + Rubik (1,2,4,8)

#define sRsrc_Vid_V8_A2Ema       $B2                // 512K VRAM V8 + A// (1,2,4,8)
#define sRsrc_Vid_V8_A2Emb       $BA                // 256K VRAM V8 + A// (1,2,4)

#define sRsrc_Vid_V8_HRa         $A6                // 512K VRAM V8 + Hi-Res (1,2,4,8)
#define sRsrc_Vid_V8_HRb         $AE                // 256K VRAM V8 + Hi-Res (1,2,4)

#define sRsrc_Vid_V8_VGAa        $A3                // 512K VRAM V8 + VGA (1,2,4,8)
#define sRsrc_Vid_V8_VGAb        $AB                // 256K VRAM V8 + VGA (1,2,4)

// -------- DB-Lite LCD sRsrc IDs ------
//
#define sRsrc_Vid_GSC_LCD        $BB            	// DB-Lite grayscale (640x400) built-in LCD display.

// -------- DAFB sRsrc IDs --------

#define sRsrc_Vid_DAFB_19a               $BE        // 19” 1,2,4         (Ugh:  There’s no where
#define sRsrc_Vid_DAFB_19b               $BF        // 19” 1,2,4,8           else to put these!)

// -------- DAFB sRsrc IDs --------

// In this group of spIDs, the assignment is much more arbitrary than the others
//   where properties are associated with bits.  Generally, there are two sets of
//   modes - a full capability with more memory and a reduced capability with less RAM.
//   The mapping of these two flavors on top of the three vRAM sizes is dependent on the
//   type of display and isn't obvious.
//
//           Progressive scan ID's - $C0-$CF, where even IDs are the lower functionality
//                                            and full function = lower function+1
//           Interlaced scan ID's  - $D0-$DF, with the same relationship between evens
//                                            and odds as the progressive scan displays.
//                                            Also, convolved modes (which only work with
//                                            2MB RAM) are the higher functionality  
//                                            ID+8 (even if the higher func. mode is a 
//                                            1MB mode)
//

// Zydeco update:  Because the Zydeco (Eclipse 33) has the AC842A (16bpp-capable ACDC), we
//   needed a few more sResources.  Note that the even sRsrcs are still the lesser capable
//   sRsrc IDs.

#define sRsrc_Vid_DAFB_FPa               $C0             // Full-Page 1,2,4
#define sRsrc_Vid_DAFB_FPb               $C1             // Full-Page 1,2,4,8

#define sRsrc_Vid_DAFB_GSa               $C2             // Rubik 1,2,4,8
#define sRsrc_Vid_DAFB_GSb               $C3             // Rubik 1,2,4,8,32

#define sRsrc_Vid_DAFB_2Pa               $C4             // Two-Page 1,2,4
#define sRsrc_Vid_DAFB_2Pb               $C5             // Two-Page 1,2,4,8

#define sRsrc_Vid_DAFB_LPa               $C6             // GoldFish 1,2,4,8          
#define sRsrc_Vid_DAFB_LPb               $C7             // GoldFish 1,2,4,8,32

#define sRsrc_Vid_DAFB_HRa               $C8             // HiRes 1,2,4,8
#define sRsrc_Vid_DAFB_HRb               $C9             // HiRes 1,2,4,8,32

#define sRsrc_Vid_DAFB_VGAa              $CA             // VGA 1,2,4,8
#define sRsrc_Vid_DAFB_VGAb              $CB             // VGA 1,2,4,8,32

#define sRsrc_Vid_DAFB_RGBFPa            $CC             // RGBPort 1,2,4
#define sRsrc_Vid_DAFB_RGBFPb            $CD             // RGBPort 1,2,4,8

#define sRsrc_Vid_DAFB_RGB2Pa            $CE             // Vesuvio 1,2,4
#define sRsrc_Vid_DAFB_RGB2Pb            $CF             // Vesuvio 1,2,4,8

#define sRsrc_Vid_DAFB_NTSCSTa           $D0             // NTSC ST 1,2,4,8
#define sRsrc_Vid_DAFB_NTSCSTb           $D1             // NTSC ST 1,2,4,8,32
#define sRsrc_Vid_DAFB_NTSCFFa           $D2             // NTSC FF 1,2,4,8
#define sRsrc_Vid_DAFB_NTSCFFb           $D3             // NTSC FF 1,2,4,8,32

#define sRsrc_Vid_DAFB_PALSTa            $D4             // PAL ST 1,2,4,8
#define sRsrc_Vid_DAFB_PALSTb            $D5             // PAL ST 1,2,4,8,32
#define sRsrc_Vid_DAFB_PALFFa            $D6             // PAL FF 1,2,4,8
#define sRsrc_Vid_DAFB_PALFFb            $D7             // PAL FF 1,2,4,8,32

#define sRsrc_Vid_DAFB_NTSCconvSTx       $D8             // NTSC ST conv 1,2,4,8 (dif ID only for 16bpp)
#define sRsrc_Vid_DAFB_NTSCconvST        $D9             // NTSC ST conv 1,2,4,8
#define sRsrc_Vid_DAFB_NTSCconvFFx       $DA             // NTSC FF conv 1,2,4,8 (dif ID only for 16bpp)
#define sRsrc_Vid_DAFB_NTSCconvFF        $DB             // NTSC FF conv 1,2,4,8

#define sRsrc_Vid_DAFB_PALconvSTx        $DC             // PAL ST conv 1,2,4,8 (dif ID only for 16bpp)
#define sRsrc_Vid_DAFB_PALconvST         $DD             // PAL ST conv 1,2,4,8
#define sRsrc_Vid_DAFB_PALconvFFx        $DE             // PAL FF conv 1,2,4,8 (dif ID only for 16bpp)
#define sRsrc_Vid_DAFB_PALconvFF         $DF             // PAL FF conv 1,2,4,8

// -------- TIM LCD sRsrc IDs ----------
//
#define sRsrc_Vid_Tim_LCD                $E0             // TIM built-in LCD display

// -------- Apollo sRsrc IDs -----------
//
#define sRsrc_Vid_Apollo                 $E1             // Apollo built-in video 

// ------- Extra DAFB sRsrc IDs  -------
//
#define MinDAFB16bppSRsrc                $E2             // DAFB 16bpp-capable sRsrc boundry.

#define sRsrc_Vid_DAFB_HRax              $E2             // HiRes 1,2,4,8,16
#define sRsrc_Vid_DAFB_HRbx              $E3             // HiRes 1,2,4,8,16,32

#define sRsrc_Vid_DAFB_VGAax             $E4             // VGA 1,2,4,8,16
#define sRsrc_Vid_DAFB_VGAbx             $E5             // VGA 1,2,4,8,16,32

#define sRsrc_Vid_DAFB_LPax              $E6             // GoldFish 1,2,4,8,16
#define sRsrc_Vid_DAFB_LPbx              $E7             // GoldFish 1,2,4,8,16,32

#define sRsrc_Vid_DAFB_SVGAax            $E8             // SuperVGA 1,2,4,8,16
#define sRsrc_Vid_DAFB_SVGAbx            $E9             // SuperVGA 1,2,4,8,16,32

#define sRsrc_Vid_DAFB_SVGAa             $EA             // SuperVGA 1,2,4,8
#define sRsrc_Vid_DAFB_SVGAb             $EB             // SuperVGA 1,2,4,8,32

#define sRsrc_Vid_DAFB_GSx               $EC             // Rubik 1,2,4,8,16,32
#define sRsrc_Vid_DAFB_GSz               $EE             // Rubik 1,2,4,8,16 (note that it’s out of order here)

#define sRsrc_Vid_DAFB_RGBFPbx           $ED             // RGBPort 1,2,4,8,16
#define sRsrc_Vid_DAFB_RGB2Pbx           $EF             // Vesuvio 1,2,4,8,16

#define sRsrc_Vid_DAFB_NTSCSTax          $F0             // NTSC ST 1,2,4,8,16
#define sRsrc_Vid_DAFB_NTSCSTbx          $F1             // NTSC ST 1,2,4,8,16,32
#define sRsrc_Vid_DAFB_NTSCFFax          $F2             // NTSC FF 1,2,4,8,16
#define sRsrc_Vid_DAFB_NTSCFFbx          $F3             // NTSC FF 1,2,4,8,16,32

#define sRsrc_Vid_DAFB_PALSTax           $F4             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_DAFB_PALSTbx           $F5             // PAL ST 1,2,4,8,16,32
#define sRsrc_Vid_DAFB_PALFFax           $F6             // PAL FF 1,2,4,8,16
#define sRsrc_Vid_DAFB_PALFFbx           $F7             // PAL FF 1,2,4,8,16

#define sRsrc_Vid_DAFB_Reserved          $F8             // Reserved for future use.
#define sRsrc_Vid_DAFB_19bx              $F9             // 19” 1,2,4,8,16

#define pSRsrc_Vid_DAFB_2PRdRGB          $FD             // Psuedo-sRsrcID for Radius ColorTPD (1,2,4,8[,16]).
#define pSRsrc_Vid_DAFB_2PRdMono         $FE             // Psuedo-sRsrcID for Radius MonoTPD (1,2,4,8).

//
// The following sRsrcs are non-video sRsrcs.  As much as it makes sense, we should attempt to use
//   the same sRsrc IDs in directories other than the Zydeco sRsrc directory.
//
// -------- CPU Resource IDs -----------
//

#define sRsrc_CPUMacIIci                 $FA             // Used for ’030 (and Mac LC) CPU sRsrcs.
#define sRsrc_CPUMac030                  $FA             // Just an alias for the “IIci” CPU sRsrc.
#define sRsrc_CPUMac040                  $FB             // CPU sRsrc for ’040 machines.

#define sRsrc_Reserved1                  $FC             // Reserved for future use.

// -------- Onboard Ethernet ID --------
//
#define sRsrc_Sonic                      $FD             // Sonic onboard Ethernet chip.
#define sRsrc_Ethernet                   $FD             // Just an alias for future non-Sonic Ethernet chips.

#define sRsrc_Reserved2                  $FE             // Reserved for future use except in the Zydeco sRsrc dir.

// -------- SCSI Transport ID --------
//
#define sRsrc_SCSI_Transport             $FA             // Reserved for future use except in the Zydeco sRsrc dir.

//
// Double Exposure related stuff.  This card should have a config ROM on it, but doesn't so
//   we have a double exposure functional sRsrc that could potentially be plumbed in.  This
//   spID is set to be higher than all video functional sRsrcs.  
//

#define sRsrc_DoubleExposure             $FE             // special functional resource for Double
                                                    //   Exposure functional sRsrc
                                                    
#define CPU_FlagsID                      $80
#define hasPixelClock                    0               // bit indicating that card provides a pixel clock
#define hasIWM                           1               // card has an IWM
#define hasJoystick                      2               // card has a joystick port
#define hasDERegs                        15              // card uses the initial DE register set
#define CPU_Flags                        ( 0|(1<<hasPixelClock)|(1<<hasIWM)|(1<<hasJoystick)|(1<<hasDERegs) )
            
// Double Exposure hardware regs
//
#define A2eAdrsReg                       $1c
#define A2eDataReg                       $10

//---------------------------------------------------------------------
//   sRsrc IDs in the sRsrcSonoraDir Directory
//---------------------------------------------------------------------

// Define the board sRsrc strategy for the sRsrcSonraDir.  We just use the boxFlag for
//   covenience.  Unlike the Zydeco directory, we don’t need to add 1 because none
//   of the Sonora-based CPUs can have a boxFlag of zero.
// 
#define sRsrc_BdVail               		(boxLCIII)       // Board sResource ID for the Vail CPU.
#define sRsrc_BdPDM                		(boxPDM80F)  	 // Board sResource ID for PDM.							<sm24>

// -------- Vail/PDM sRsrc IDs ----------
//

#define sRsrc_Vid_Sonora_FP				 $80			 // Full-Page 1 (PDM)
#define sRsrc_Vid_Sonora_FPa             $81             // Full-Page 1,2
#define sRsrc_Vid_Sonora_FPb             $82             // Full-Page 1,2,4
#define sRsrc_Vid_Sonora_FPc             $83             // Full-Page 1,2,4,8

#define sRsrc_Vid_Sonora_GS				 $84			 // Rubik 1 (PDM)
#define sRsrc_Vid_Sonora_GSa             $85             // Rubik 1,2,4,8
#define sRsrc_Vid_Sonora_GSb             $86             // Rubik 1,2,4,8,16
#define sRsrc_Vid_Sonora_GSM			 $87			 // GSM=GSb

#define sRsrc_Vid_Sonora_GS560a          $88             // Rubik-560 1,2,4,8 (Vail)
#define sRsrc_Vid_Sonora_GS560b          $89             // Rubik-560 1,2,4,8,16 (Vail)

#define sRsrc_Vid_Sonora_RGBFP			 $8A			 // RGB Full-Page 1 (PDM)
#define sRsrc_Vid_Sonora_RGBFPa          $8B             // RGB Full-Page 1,2
#define sRsrc_Vid_Sonora_RGBFPb          $8C             // RGB Full-Page 1,2,4
#define sRsrc_Vid_Sonora_RGBFPc          $8D             // RGB Full-Page 1,2,4,8

#define sRsrc_Vid_Sonora_HR				 $8E			 // HiRes 1 (PDM)
#define sRsrc_Vid_Sonora_HRa             $8F             // HiRes 1,2,4
#define sRsrc_Vid_Sonora_HRb             $90             // HiRes 1,2,4,8
#define sRsrc_Vid_Sonora_HRc             $91             // HiRes 1,2,4,8,16
#define sRsrc_Vid_Sonora_MSB1			 $92			 // MSB1 -> HRc

#define sRsrc_Vid_Sonora_HR400a          $93             // HiRes-400 1,2,4,8 (Vail)
#define sRsrc_Vid_Sonora_HR400b          $94             // HiRes-400 1,2,4,8,16 (Vail)

#define sRsrc_Vid_Sonora_VGA			 $95			 // VGA 1 (PDM)
#define sRsrc_Vid_Sonora_VGAa            $96             // VGA 1,2,4
#define sRsrc_Vid_Sonora_VGAb            $97             // VGA 1,2,4,8
#define sRsrc_Vid_Sonora_VGAc            $98             // VGA 1,2,4,8,16

#define sRsrc_Vid_Sonora_GF				 $99			 // GoldFish 1 (PDM)
#define sRsrc_Vid_Sonora_GFa             $9A             // GoldFish 1,2
#define sRsrc_Vid_Sonora_GFb             $9B             // GoldFish 1,2,4,8
#define sRsrc_Vid_Sonora_MSB2			 $9C			 // MSB2 -> MSB3 -> GFb

#define	sRsrc_Sonora_Mace				 $EF			 // Mace ethernet on Sonora		<SM12>

#define sRsrc_Sonora_NeverMatch          $FE             // The “null” Sonora sRsrc.

//---------------------------------------------------------------------
//	sRsrc IDs in the sRsrcCSCDir Directory
//---------------------------------------------------------------------

// Define the board sRsrc strategy for the sRsrcCSCDir.  
// 
#define sRsrc_BdEscher					$01				 // Board sResource ID for Escher-style CPUs (Duos).
#define sRsrc_BdBlackBird				$02				 // Board sResource ID for BlackBirds (All-in-One).
#define sRsrc_BdYeager					$03				 // Board sResource ID for Yeager (Duos).

// -------- CSC sRsrc IDs ----------
//
#define sRsrc_Vid_CSC_640x400a			$80				 // 1,2,4,8
#define sRsrc_Vid_CSC_640x400b			$81				 // 1,2,4,8,16

#define sRsrc_Vid_CSC_640x480a			$82				 // 1,2,4,8
#define sRsrc_Vid_CSC_C_S_TFT_399			$80				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, Sharp]
#define sRsrc_Vid_CSC_C_S_TFT_480			$81				// 1,2,4,8

#define sRsrc_Vid_CSC_C_S_TFT_399a			$82				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, Sharp]
#define sRsrc_Vid_CSC_C_S_TFT_480a			$83				// 1,2,4,8

#define sRsrc_Vid_CSC_C_D_STN_480			$85				// 1,2,4,8		[Color, STN, Dual-Drive, 64$480, Sharp]

#define sRsrc_Vid_CSC_C_S_TFT_399b			$86				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, NEC]
#define sRsrc_Vid_CSC_C_S_TFT_480b			$87				// 1,2,4,8

#define sRsrc_Vid_CSC_C_S_TFT_399c			$88				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, Hosiden]
#define sRsrc_Vid_CSC_C_S_TFT_480c			$89				// 1,2,4,8

#define sRsrc_Vid_CSC_C_S_TFT_399d			$8A				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, Toshiba]
#define sRsrc_Vid_CSC_C_S_TFT_480d			$8B				// 1,2,4,8

#define sRsrc_Vid_CSC_G_D_STN_400			$8D				// 1,2,4 		[Gray, STN, Dual-Drive, 64$400, Sharp]
#define sRsrc_Vid_CSC_G_S_TFT_400			$8F				// 1,2,4 		[Gray, TFT, Single-Drive, 64$400, Hosiden]

#define sRsrc_Vid_CSC_G_D_STN_480			$90				// 1,2,4			[Gray, STN, Dual-Drive, 64$480, Sharp]
#define sRsrc_Vid_CSC_G_S_TFT_480			$91				// 1,2,4			[Gray, TFT, Single-Drive, 64$400, Hosiden]

#define sRsrc_Vid_CSC_C_S_TFT_399y			$92				// 1,2,4,8,16	[Color, TFT, Single-Drive, 64$480, Toshiba]
#define sRsrc_Vid_CSC_C_S_TFT_480y			$93				// 1,2,4,8

#define sRsrc_Vid_CSC_G_D_STN_400y			$94				// 1,2,4 		[Gray, STN, Dual-Drive, 64$400, Sharp]
#define sRsrc_Vid_CSC_G_S_TFT_400y			$95				// 1,2,4 		[Gray, TFT, Single-Drive, 64$400, Hosiden]

#define sRsrc_CSC_NeverMatch			$FE				 // The “null” CSC sRsrc.

// -------- VSC sRsrc IDs ----------
//
#define sRsrc_Vid_VSC_FPb					$80	
#define sRsrc_Vid_VSC_FPa					$81				

#define sRsrc_Vid_VSC_GS					$82	

#define sRsrc_Vid_VSC_RGBFPb				$84				
#define sRsrc_Vid_VSC_RGBFPa				$85	

#define sRsrc_Vid_VSC_HR					$86				

#define BBExtVidBdID						$59

//---------------------------------------------------------------------
//   sRsrc IDs in the sRsrcCivicDir Directory
//---------------------------------------------------------------------

// Define the board sRsrc strategy for the sRsrcCivicDir.  We just use the boxFlag for
//   covenience.  Unlike the Zydeco directory, we don’t need to add 1 because none
//   of the Cyclone-based CPUs can have a boxFlag of zero.
// 
#define sRsrc_BdCyclone                  (boxQuadra840AV)      // Board sRsrc ID for the Cyclone family of CPUs.
#define sRsrc_BdTempest                  (boxCentris660AV)     // Board sRsrc ID for the Cyclone family of CPUs.

// -------- Cyclone sRsrc IDs ----------
//

// The functional sRsrcs in Cyclone are distributed as follows:
//       
//       $80 - $EF are the video sRsrcs IDs
//
//       $F0 - $FD are for misc. sRsrc IDs (e.g, Mace, DSP, etc…).
//
//       $FE is reserved as the “null” sRsrc ID.

#define sRsrc_Vid_Civic_NTSCFFConva      $80             // NTSC FF Conv 1,2,4,8
#define sRsrc_Vid_Civic_NTSCSTConv       $81             // NTSC ST Conv 1,2,4,8

#define sRsrc_Vid_Civic_PALFFConva       $84             // PAL FF Conv 1,2,4,8
#define sRsrc_Vid_Civic_PALSTConva       $85             // PAL ST Conv 1,2,4,8

// ------  Video-in ID's

#define sRsrc_Vid_Civic_vi2PRGBa         $88             // Vesuvio 1,2,4
#define sRsrc_Vid_Civic_vi2PRGBb         $89             // Vesuvio 1,2,4,8
#define sRsrc_Vid_Civic_vi2PRGB512       $8A             // Vesuvio (512x384) 1,2,4,8
#define sRsrc_Vid_Civic_vi2PRGB640a      $8B             // Vesuvio (640x480) 1,2,4,8
#define sRsrc_Vid_Civic_vi2PRGB640b      $8C             // Vesuvio (640x480) 1,2,4,8
#define sRsrc_Vid_Civic_vi2PRGB768a      $8D             // Vesuvio (768x576) 1,2,4,8
#define sRsrc_Vid_Civic_vi2PRGB768b      $8E             // Vesuvio (768x576) 1,2,4,8

#define sRsrc_Vid_Civic_viFPa            $91             // Full-Page 1,2,4
#define sRsrc_Vid_Civic_viFPb            $92             // Full-Page 1,2,4,8
#define sRsrc_Vid_Civic_viFP512          $93             // Full-Page (512x384) 1,2,4,8
#define sRsrc_Vid_Civic_viFP640          $94             // Full-Page (640x480) 1,2,4,8

#define sRsrc_Vid_Civic_viGS             $97             // Rubik 1,2,4,8,16
#define sRsrc_Vid_Civic_viGS560          $98             // Rubik-560 1,2,4,8,16

#define sRsrc_Vid_Civic_vi2Pa            $9B             // Two-Page 1,2,4
#define sRsrc_Vid_Civic_vi2Pb            $9C             // Two-Page 1,2,4,8
#define sRsrc_Vid_Civic_vi2P512          $9D             // Two-Page (512x384) 1,2,4,8
#define sRsrc_Vid_Civic_vi2P640          $9E             // Two-Page (640x480) 1,2,4,8
#define sRsrc_Vid_Civic_vi2P768          $9F             // Two-Page (768x576) 1,2,4,8

#define sRsrc_Vid_Civic_viNTSCFFa        $A2             // NTSC FF 1,2,4,8
#define sRsrc_Vid_Civic_viNTSCFFb        $A3             // NTSC FF 1,2,4,8,16
#define sRsrc_Vid_Civic_viNTSCST         $A4             // NTSC ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viNTSCFFConva    $A5             // NTSC ST 1,2,4,8 (Actually, non-Conv)
#define sRsrc_Vid_Civic_viNTSCFFConvb    $A6             // NTSC ST 1,2,4,8,16 (Actually, non-Conv)
#define sRsrc_Vid_Civic_viNTSCSTConv     $A7             // NTSC ST 1,2,4,8,16 (Actually, non-Conv)

#define sRsrc_Vid_Civic_viFPRGBa         $AA             // Full-Page RGB 1,2,4
#define sRsrc_Vid_Civic_viFPRGBb         $AB             // Full-Page RGB 1,2,4,8

#define sRsrc_Vid_Civic_viHRa            $B0             // HiRes 1,2,4,8
#define sRsrc_Vid_Civic_viHRb            $B1             // HiRes 1,2,4,8,16
#define sRsrc_Vid_Civic_viHRNTSCST       $B2             // HiRes (512x384) 1,2,4,8,16
#define sRsrc_Vid_Civic_viHR400          $B3             // HiRes (640x400) 1,2,4,8,16
#define sRsrc_Vid_Civic_viHRMAZa         $B4             // HiRes (704x512) 1,2,4,8
#define sRsrc_Vid_Civic_viHRMAZb         $B5             // HiRes (704x512) 1,2,4,8,16

#define sRsrc_Vid_Civic_viPALFFa         $B8             // PAL FF 1,2,4,8
#define sRsrc_Vid_Civic_viPALFFb         $B9             // PAL FF 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALSTa         $BA             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALSTb         $BB             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALFFConva     $BC             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALFFConvb     $BD             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALSTConva     $BE             // PAL ST 1,2,4,8,16
#define sRsrc_Vid_Civic_viPALSTConvb     $BF             // PAL ST 1,2,4,8,16

#define sRsrc_Vid_Civic_viVGAa           $C2             // VGA 1,2,4,8
#define sRsrc_Vid_Civic_viVGAb           $C3             // VGA 1,2,4,8,16

#define sRsrc_Vid_Civic_viSVGA56a        $C7             // SVGA (56Hz) 1,2,4,8
#define sRsrc_Vid_Civic_viSVGA56b        $C8             // SVGA (56Hz) 1,2,4,8,16

#define sRsrc_Vid_Civic_viSVGA72a        $CC             // SVGA (72Hz) 1,2,4,8
#define sRsrc_Vid_Civic_viSVGA72b        $CD             // SVGA (72Hz) 1,2,4,8,16

#define sRsrc_Vid_Civic_viSxVGA60a       $D1             // SxVGA (60Hz) 1,2,4
#define sRsrc_Vid_Civic_viSxVGA60b       $D2             // SxVGA (60Hz) 1,2,4,8

#define sRsrc_Vid_Civic_viSxVGA70a       $D6             // SxVGA (70Hz) 1,2,4
#define sRsrc_Vid_Civic_viSxVGA70b       $D7             // SxVGA (70Hz) 1,2,4,8

#define sRsrc_Vid_Civic_viGFa            $DB             // GoldFish 1,2,4,8,16
#define sRsrc_Vid_Civic_viGFb            $DC             // GoldFish 1,2,4,8,16
#define sRsrc_Vid_Civic_viGFNTSCST       $DD             // Goldfish 512x384 (Underscan NTSC)
#define sRsrc_Vid_Civic_viGFNTSCFFa      $DE             // Goldfish 640x480 (Overscan NTSC)
#define sRsrc_Vid_Civic_viGFNTSCFFb      $DF             // Goldfish 640x480 (Overscan NTSC)
#define sRsrc_Vid_Civic_viGFPALFFa       $E0             // Goldfish 768x576 (Overscan PAL)
#define sRsrc_Vid_Civic_viGFPALFFb       $E1             // Goldfish 768x576 (Overscan PAL)

#define sRsrc_Vid_Civic_vi19a            $E4             // 19" 1,2,4
#define sRsrc_Vid_Civic_vi19b            $E5             // 19" 1,2,4,8



// ------

#define sRsrc_Civic_NeverMatch           $FE             // The “null” sRsrc ID

//---------------------------------------------------------------------
//   sRsrc IDs in the sRsrcATIDir Directory
//---------------------------------------------------------------------

// Define the board sRsrc strategy for the sRsrcCivicDir.  We just use the boxFlag for
//   covenience.  Unlike the Zydeco directory, we don’t need to add 1 because none
//   of the ATI-based CPUs can have a boxFlag of zero.
// 


// -------- ATI sRsrc IDs ----------
//

#define sRsrc_VideoHR  				   $80             // Hi-Res
#define sRsrc_ATI_NeverMatch           $FE             // The “null” sRsrc ID
