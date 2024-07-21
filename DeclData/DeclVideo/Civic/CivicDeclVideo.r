/*
	File:		CivicDeclVideo.r

	Contains:	Civic video definitions.

	Copyright:	й 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM14>	 8/25/93	fau		BG changed sRsrc_BdCyclone from Cyclone33 to Cyclone40 (actually
									to Quadra840av) and it screwed up the ascending order of the
									board sresource ID's, so I rectified this.
	  <SM13>	 6/14/93	kc		Roll in Ludwig.
	  <LW17>	  6/4/93	fau		The viNTSCST spID did not have an equivalent spID for
									Convolution.
	  <LW16>	 5/24/93	FU		Modified the Endeavor parameters for the following monitors,
									trading accuracy for a lower divider on the PLL:  13" RGB, 12"
									RGB @512x384, 12" 560x384, VGA, SVGA (56Hz), and SxVGA (60Hz).
	  <LW15>	 5/19/93	fau		Added the CivicPict2 sRsrc.
	  <LW14>	 5/14/93	fau		Added #PUMA support.  Fixed bug #1084483.
	  <LW13>	 4/30/93	fau		Added the CivicPict sResource.
	  <SM12>	 4/29/93	fau		Synchronized with Ludwig.
	  <LW12>	 4/22/93	fau		Bug #1080212:  The 32bpp video parameters for QuickDraw for the
									GS560 had the bounds for a GS!
	  <LW11>	 4/15/93	fau		Fixed some spID problems with convolution on interlaced
									displays:  they either didn't have an equivalent, or in 1 case
									it was the 1 meg one instead of the 2 meg one.
	  <LW10>	 4/14/93	fau		Changes required for the new way of doing video-in:  deleted
									obsolete resources; added some new video-parameters that use a
									vpBaseOffset so that we can enable video-in on the fly, even if
									it has a different base-address (use the offset, + or -, from
									the base address of mode 80.)
	  <SM11>	  4/6/93	fau		Yet another synchro with Ludwig.
	   <LW9>	  4/5/93	fau		Added the parameters for Puma (W, W Size, and clock), but they
									are all 0 for now.
	  <SM10>	  4/5/93	chp		Synchronize with Ludwig.
	   <LW8>	 3/24/93	mal		Added block xfer sRsrcs to Cyclone/Tempest board sRsrcs.
	   <LW7>	 3/22/93	fau		Added a functional board sRsrc for Tempest.
	   <LW6>	  3/6/93	fau		Fixed bug #1069289:  Thousands and Millions in 16" monitor, no
									video-in, 1 Meg VRAM:  Video parameters were not allowing those
									values.  Fixed unreported bug with 21"RGB, video-in, 2 Megs:
									Functional sRsrc was allowing thousands, when max mode was 256
									colors.
	   <LW5>	 2/24/93	fau		Added the SCSI_Transport sRsrc.
	   <LW4>	 2/16/93	fau		Massive changes in the area of video-out capable monitors:
									Added support in that area for all Apple monitors.  Added
									"color" support for the 15" Full-Page.  Changed the name of this
									modes to only reflect the resolution.
	   <LW3>	12/21/92	fau		Split the resources for PALST into PALSTa and PALSTb.  This
									fixes bug #1057924.
	   <LW2>	12/14/92	fau		I was allowing Thousands in the GoldFish PALST and NTSCFF video
									parameters when you have 2 meg installed.  This shouldn't be.
	   <SM9>	 12/3/92	fau		Fixed bug in rowbytes for the SuperVGA modes that actually use
									the same rowbytes as the 19".    Added Clifton support the
									100MHz monitors.
	   <SM8>	11/11/92	fau		Fixed bug id: #1052489:  Problem with max vid mode on 12" in
									NTSC mode.  Changed clock timing for viPALST.  Added values for
									Clifton programming for all supported monitors.
	   <SM7>	 11/6/92	fau		Fixed the rowbytes for the 16" monitor in PAL overscan mode.
	   <SM6>	 11/2/92	kc		Change ObjDir to RsrcDir.
	   <SM5>	10/27/92	fau		Added Clifton'sW parameter to all our functional srsrc's.  This
									is to support Tempest in the near future.  For now, they are all
									0.
	   <SM4>	10/22/92	fau		Updated the 19" Civic-rowbytes for the no video-in case as in
									<SM2>.  This should've done before 'cause it's broken.
	   <SM3>	10-17-92	jmp		Needed to the change the 'decl' IDs of various externally
									referenced components.
	   <SM2>	 10/8/92	fau		Sync'ed up with the old Decldata:  2PRGB's base address moved to
									2560.  19" video-in base address moved to 256.  RowBytes for 19"
									2bpp and 8bpp moved to 8*32 and 36*32 in vidparams (256 and
									1152).  No 16bpp for 19" with video-in.
	   <SM1>	 10/6/92	GDW		New location for ROMLink tool.

*/


//===================================================================
// Includes
//===================================================================

#include "Types.r"

#define	_NO_SINL_ // Don╒t need 'SINL' resource here.
#include "ROMLink.r"
#undef	_NO_SINL_

#include "DepVideoEqu.r"
#include "HardwarePrivateEqu.r"
#include "InternalOnlyEqu.r"
#include "Quickdraw.r"

// This #define's are a stopgap measure for now.
#define firstVidMode  0x80				// 1 bpp
#define secondVidMode 0x81				// 2 bpp
#define thirdVidMode  0x82				// 4 bpp
#define fourthVidMode 0x83				// 8 bpp
#define fifthVidMode  0x84				// 16 bpp
#define sixthVidMode  0x85				// 32 bpp

//-------------------------------------------------------------
//
//           Civic sRsrc Directory
//
//           Only CPUs possessing the CIVIC ASIC should
//               be placed in this directory
//
//-------------------------------------------------------------

resource 'sdir' (150, "_sRsrcCivicDir") {{
  sRsrc_BdTempest,  l{"_sRsrc_BdTempest"}; // Tempest sResource
  sRsrc_BdCyclone,  l{"_sRsrc_BdCyclone"}; // Cyclone Board sResource
                
// Functional sRsrcs for Civic built-in video (graphics-only).
//
                
  sRsrc_Vid_Civic_NTSCFFConva, l{"_sRsrc_Vid_Civic_NTSCFFConva"};	// NTSC FF Conv (1,2,4,8)
  sRsrc_Vid_Civic_NTSCSTConv, l{"_sRsrc_Vid_Civic_NTSCSTConv"};	// NTSC ST Conv (1,2,4,8)
                
                
  sRsrc_Vid_Civic_PALFFConva, l{"_sRsrc_Vid_Civic_PALFFConva"};	// PAL FF Conv (1,2,4,8)
  sRsrc_Vid_Civic_PALSTConva, l{"_sRsrc_Vid_Civic_PALSTConva"};	// PAL ST Conv (1,2,4,8)
                

// Functional sRsrcs for Civic built-in video with video-in.
//
  sRsrc_Vid_Civic_vi2PRGBa, l{"_sRsrc_Vid_Civic_vi2PRGBa"};		// Vesuvio (1,2,4)
  sRsrc_Vid_Civic_vi2PRGBb, l{"_sRsrc_Vid_Civic_vi2PRGBb"};		// Vesuvio (1,2,4,8)
  sRsrc_Vid_Civic_vi2PRGB512, l{"_sRsrc_Vid_Civic_vi2PRGB512"};		// Vesuvio (512x384) 1,2,4,8,16
  sRsrc_Vid_Civic_vi2PRGB640a, l{"_sRsrc_Vid_Civic_vi2PRGB640a"};	// Vesuvio (640x480) 1,2,4,8
  sRsrc_Vid_Civic_vi2PRGB768a, l{"_sRsrc_Vid_Civic_vi2PRGB768a"};	// Vesuvio (768x576) 1,2,4
                
  sRsrc_Vid_Civic_viFPa, l{"_sRsrc_Vid_Civic_viFPa"};			// Full-Page (1,2,4)
  sRsrc_Vid_Civic_viFPb, l{"_sRsrc_Vid_Civic_viFPb"};			// Full-Page (1,2,4,8)
  sRsrc_Vid_Civic_viFP512, l{"_sRsrc_Vid_Civic_viFP512"};		// Full-Page 512x384 (1,2,4,8)
  sRsrc_Vid_Civic_viFP640, l{"_sRsrc_Vid_Civic_viFP640"};		// Full-Page 640x480 (1,2,4,8)
                
  sRsrc_Vid_Civic_viGS, l{"_sRsrc_Vid_Civic_viGS"};				// Rubik (1,2,4,8,16)
  sRsrc_Vid_Civic_viGS560, l{"_sRsrc_Vid_Civic_viGS560"};		// Rubik-560 (1,2,4,8,16)
                
  sRsrc_Vid_Civic_vi2Pa, l{"_sRsrc_Vid_Civic_vi2Pa"};			// Kong (1,2,4)
  sRsrc_Vid_Civic_vi2Pb, l{"_sRsrc_Vid_Civic_vi2Pb"};			// Kong (1,2,4,8)
  sRsrc_Vid_Civic_vi2P512, l{"_sRsrc_Vid_Civic_vi2P512"};		// Kong 512x384 (1,2,4,8)
  sRsrc_Vid_Civic_vi2P640, l{"_sRsrc_Vid_Civic_vi2P640"};		// Kong 640x480 (1,2,4,8)
  sRsrc_Vid_Civic_vi2P768, l{"_sRsrc_Vid_Civic_vi2P768"};		// Kong 768x576 (1,2,4,8)
               
  sRsrc_Vid_Civic_viNTSCFFa, l{"_sRsrc_Vid_Civic_viNTSCFFa"};	// NTSC FF (1,2,4,8)
  sRsrc_Vid_Civic_viNTSCFFb, l{"_sRsrc_Vid_Civic_viNTSCFFb"};	// NTSC FF (1,2,4,8,16)
  sRsrc_Vid_Civic_viNTSCST, l{"_sRsrc_Vid_Civic_viNTSCST"};		// NTSC ST (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viFPRGBa, l{"_sRsrc_Vid_Civic_viFPRGBa"};		// Full-Page RGB (1,2,4)
  sRsrc_Vid_Civic_viFPRGBb, l{"_sRsrc_Vid_Civic_viFPRGBb"};		// Full-Page RGB (1,2,4,8)

  sRsrc_Vid_Civic_viHRa, l{"_sRsrc_Vid_Civic_viHRa"};			// HiRes (1,2,4,8)
  sRsrc_Vid_Civic_viHRb, l{"_sRsrc_Vid_Civic_viHRb"};			// HiRes (1,2,4,8,16)
  sRsrc_Vid_Civic_viHRNTSCST, l{"_sRsrc_Vid_Civic_viHRNTSCST"};	// HiRes 512x384 (1,2,4,8)
  sRsrc_Vid_Civic_viHR400, l{"_sRsrc_Vid_Civic_viHR400"};		// HiRes-400 (1,2,4,8,16)

  sRsrc_Vid_Civic_viPALFFa, l{"_sRsrc_Vid_Civic_viPALFFa"};		// PAL FF (1,2,4,8)
  sRsrc_Vid_Civic_viPALFFb, l{"_sRsrc_Vid_Civic_viPALFFb"};		// PAL FF (1,2,4,8,16)
  sRsrc_Vid_Civic_viPALSTa, l{"_sRsrc_Vid_Civic_viPALSTa"};		// PAL ST (1,2,4,8)
  sRsrc_Vid_Civic_viPALSTb, l{"_sRsrc_Vid_Civic_viPALSTb"};		// PAL ST (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viVGAa, l{"_sRsrc_Vid_Civic_viVGAa"};			// VGA (1,2,4,8)
  sRsrc_Vid_Civic_viVGAb, l{"_sRsrc_Vid_Civic_viVGAb"};			// VGA (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viSVGA56a, l{"_sRsrc_Vid_Civic_viSVGA56a"};	// SVGA-56Hz (1,2,4,8)
  sRsrc_Vid_Civic_viSVGA56b, l{"_sRsrc_Vid_Civic_viSVGA56b"};	// SVGA-56Hz (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viSVGA72a, l{"_sRsrc_Vid_Civic_viSVGA72a"};	// SVGA-72Hz (1,2,4,8)
  sRsrc_Vid_Civic_viSVGA72b, l{"_sRsrc_Vid_Civic_viSVGA72b"};	// SVGA-72Hz (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viSxVGA60a, l{"_sRsrc_Vid_Civic_viSxVGA60a"};	// SxVGA-60Hz (1,2,4,8)
  sRsrc_Vid_Civic_viSxVGA60b, l{"_sRsrc_Vid_Civic_viSxVGA60b"};	// SxVGA-60Hz (1,2,4,8,16)
                
  sRsrc_Vid_Civic_viSxVGA70a, l{"_sRsrc_Vid_Civic_viSxVGA70a"};	// SxVGA-70Hz (1,2,4)
  sRsrc_Vid_Civic_viSxVGA70b, l{"_sRsrc_Vid_Civic_viSxVGA70b"};	// SxVGA-70Hz (1,2,4,8)
                
  sRsrc_Vid_Civic_viGFa, l{"_sRsrc_Vid_Civic_viGFa"};			// GoldFish (1,2,4,8,16)
  sRsrc_Vid_Civic_viGFb, l{"_sRsrc_Vid_Civic_viGFb"};			// GoldFish (1,2,4,8,16)
  sRsrc_Vid_Civic_viGFNTSCST, l{"_sRsrc_Vid_Civic_viGFNTSCST"};		// GoldFish 512x384 (1,2,4,8,16)
  sRsrc_Vid_Civic_viGFNTSCFFa, l{"_sRsrc_Vid_Civic_viGFNTSCFFa"};	// GoldFish 640x480 (1,2,4,8)
  sRsrc_Vid_Civic_viGFNTSCFFb, l{"_sRsrc_Vid_Civic_viGFNTSCFFb"};	// GoldFish 640x480 (1,2,4,8,16)
  sRsrc_Vid_Civic_viGFPALFFa, l{"_sRsrc_Vid_Civic_viGFPALFFa"};		// GoldFish 768x576 (1,2,4,8)
  sRsrc_Vid_Civic_viGFPALFFb, l{"_sRsrc_Vid_Civic_viGFPALFFb"};		// GoldFish 768x576 (1,2,4,8,16)

                
  sRsrc_Vid_Civic_vi19a, l{"_sRsrc_Vid_Civic_vi19a"};			// 19" (1,2,4)
  sRsrc_Vid_Civic_vi19b, l{"_sRsrc_Vid_Civic_vi19b"};			// 19" (1,2,4,8)

// Miscellaneous sRsrcs for Civic-based CPUs.
//

  sRsrc_SCSI_Transport,  a{"_sRsrc_SCSI_Transport"};			// SCSI Transport sResource
  sRsrc_CPUMac040,  a{"_sRsrc_CPUMacO40"};						// CPU sResource
  sRsrc_Ethernet,   a{"_sRsrc_Mace"};							// Mace sResource
                
}};


//-------------------------------------------------------------
// Board resource
//-------------------------------------------------------------

resource 'boar' (335, "_sRsrc_BdCyclone") {{
  sRsrcType,        a{"_BoardType"}; 
  sRsrcName,        c{"Macintosh 3A"}; 
  sRsrcIcon,        a{"_VidICONCyclone"};
  sBlockTransferInfo, long{( 0 | \
  									(1<<fIsMaster) | \
									(1<<fMstrLockedXfer) | \
									(1<<fMstrXferSz4) | \
									(1<<fIsSlave) | \
									(1<<fSlvXferSz16) | \
									(1<<fSlvXferSz8) | \
									(1<<fSlvXferSz4) | \
									(1<<fSlvXferSz2) 
									)};
  sMaxLockedTransferCount, long{4};
  BoardId,          d{CycloneBrdID}; 
  PrimaryInit,      l{"_sCivicPrimaryInit"}; 
  VendorInfo,       a{"_VendorInfo"}; 
  sRsrcVidNames,    l{"_CivicVidNameDir"}; 
  sVidParmDir,      l{"_VidParmDir_Civic"}; 
  sUndefinedID,		a{"_sCivicPict"};
}};

resource 'boar' (337, "_sRsrc_BdTempest") {{
  sRsrcType,        a{"_BoardType"}; 
  sRsrcName,        c{"Macintosh 3B"}; 
  sRsrcIcon,        a{"_VidICONCyclone"}; 
  sBlockTransferInfo, long{( 0 | 	\
  									(1<<fIsMaster) | \
									(1<<fMstrLockedXfer) | \
									(1<<fMstrXferSz4) | \
									(1<<fIsSlave) | \
									(1<<fSlvXferSz16) | \
									(1<<fSlvXferSz8) | \
									(1<<fSlvXferSz4) | \
									(1<<fSlvXferSz2) 
									)};
  sMaxLockedTransferCount, long{4};
  BoardId,          d{TempestBrdID}; 
  PrimaryInit,      l{"_sCivicPrimaryInit"}; 
  VendorInfo,       a{"_VendorInfo"}; 
  sRsrcVidNames,    l{"_CivicVidNameDir"}; 
  sVidParmDir,      l{"_VidParmDir_Civic"}; 
  sUndefinedID,		a{"_sCivicPict2"};
}};

//=====================================================================
// Primary Init records
//=====================================================================

resource 'node' (422, "_sCivicPrimaryInit") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{30};}}};
}};

//=====================================================================
// Civic Picture
//=====================================================================

resource 'node' (423, "_sCivicPict") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{32};}}};
}};

resource 'node' (424, "_sCivicPict2") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{33};}}};
}};

//===================================================================
// Video name parameters directory
//===================================================================

resource 'vdir' (355, "_CivicVidNameDir") {{
                
  sRsrc_Vid_Civic_NTSCFFConva, a{"_sName_NTSCconvFF"}; 
  sRsrc_Vid_Civic_NTSCSTConv, a{"_sName_NTSCconvST"}; 
                
  sRsrc_Vid_Civic_PALFFConva, a{"_sName_PALConvFF"}; 
  sRsrc_Vid_Civic_PALSTConva, a{"_sName_PALConvST"}; 
                
  sRsrc_Vid_Civic_vi2PRGBa, a{"_sName_RGB2P"}; 
  sRsrc_Vid_Civic_vi2PRGBb, a{"_sName_RGB2P"}; 
  sRsrc_Vid_Civic_vi2PRGB512, a{"_sName_512x384"}; 
  sRsrc_Vid_Civic_vi2PRGB640a, a{"_sName_640x480"}; 
  sRsrc_Vid_Civic_vi2PRGB768a, a{"_sName_768x576"}; 
                
  sRsrc_Vid_Civic_viFPa, a{"_sName_FP"}; 
  sRsrc_Vid_Civic_viFPb, a{"_sName_FP"}; 
  sRsrc_Vid_Civic_viFP512, a{"_sName_512x384"}; 
  sRsrc_Vid_Civic_viFP640, a{"_sName_640x480"}; 
                
  sRsrc_Vid_Civic_viGS, a{"_sName_GS"}; 
  sRsrc_Vid_Civic_viGS560, a{"_sName_GS560"}; 
                
  sRsrc_Vid_Civic_vi2Pa, a{"_sName_2P"}; 
  sRsrc_Vid_Civic_vi2Pb, a{"_sName_2P"}; 
  sRsrc_Vid_Civic_vi2P512, a{"_sName_512x384"}; 
  sRsrc_Vid_Civic_vi2P640, a{"_sName_640x480"}; 
  sRsrc_Vid_Civic_vi2P768, a{"_sName_768x576"}; 

  sRsrc_Vid_Civic_viNTSCFFa, a{"_sName_NTSCFF"}; 
  sRsrc_Vid_Civic_viNTSCFFb, a{"_sName_NTSCFF"}; 
  sRsrc_Vid_Civic_viNTSCST, a{"_sName_NTSCST"}; 
                
  sRsrc_Vid_Civic_viFPRGBa, a{"_sName_RGBFP"}; 
  sRsrc_Vid_Civic_viFPRGBb, a{"_sName_RGBFP"}; 
                
  sRsrc_Vid_Civic_viHRa, a{"_sName_HR"}; 
  sRsrc_Vid_Civic_viHRb, a{"_sName_HR"}; 
  sRsrc_Vid_Civic_viHRNTSCST, a{"_sName_512x384"}; 
  sRsrc_Vid_Civic_viHR400, a{"_sName_HR400"}; 

  sRsrc_Vid_Civic_viPALFFa, a{"_sName_PALFF"}; 
  sRsrc_Vid_Civic_viPALFFb, a{"_sName_PALFF"}; 
  sRsrc_Vid_Civic_viPALSTa, a{"_sName_PALST"}; 
  sRsrc_Vid_Civic_viPALSTb, a{"_sName_PALST"}; 
                
  sRsrc_Vid_Civic_viVGAa, a{"_sName_VGA"}; 
  sRsrc_Vid_Civic_viVGAb, a{"_sName_VGA"}; 
                
  sRsrc_Vid_Civic_viSVGA56a, a{"_sName_SVGA56"}; 
  sRsrc_Vid_Civic_viSVGA56b, a{"_sName_SVGA56"}; 
                
  sRsrc_Vid_Civic_viSVGA72a, a{"_sName_SVGA72"}; 
  sRsrc_Vid_Civic_viSVGA72b, a{"_sName_SVGA72"}; 
                
  sRsrc_Vid_Civic_viSxVGA60a, a{"_sName_SxVGA60"}; 
  sRsrc_Vid_Civic_viSxVGA60b, a{"_sName_SxVGA60"}; 
                
  sRsrc_Vid_Civic_viSxVGA70a, a{"_sName_SxVGA70"}; 
  sRsrc_Vid_Civic_viSxVGA70b, a{"_sName_SxVGA70"}; 
                
  sRsrc_Vid_Civic_viGFa, a{"_sName_GF"}; 
  sRsrc_Vid_Civic_viGFb, a{"_sName_GF"}; 
  sRsrc_Vid_Civic_viGFNTSCST, a{"_sName_512x384"}; 
  sRsrc_Vid_Civic_viGFNTSCFFa, a{"_sName_640x480"}; 
  sRsrc_Vid_Civic_viGFNTSCFFb, a{"_sName_640x480"}; 
  sRsrc_Vid_Civic_viGFPALFFa, a{"_sName_768x576"}; 
  sRsrc_Vid_Civic_viGFPALFFb, a{"_sName_768x576"}; 
                
  sRsrc_Vid_Civic_vi19a, a{"_sName_19"}; 
  sRsrc_Vid_Civic_vi19b, a{"_sName_19"}; 
                


}};

//===================================================================
// Supported video modes and monitors
//===================================================================

//----------------------------------

resource 'srsc' (1120, "_sRsrc_Vid_Civic_vi2PRGBa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi2P"}; 
  MinorLength,      l{"_MinorLength_Civic_vi2Pa"}; 

  sGammaDir,        a{"_GammaDir_RGB2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_vi2P"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_vi2P"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_vi2P"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_Civic_vi2Pa"};			// offset to EightBitMode parameters with no video-in ее
                
}};


//----------------------------------

resource 'srsc' (1130, "_sRsrc_Vid_Civic_vi2PRGBb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi2P"}; 
  MinorLength,      l{"_MinorLength_Civic_2Pa"}; 

  sGammaDir,        a{"_GammaDir_RGB2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_vi2P"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_vi2P"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_vi2P"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_2P"};				// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_2Pa"};			// offset to SixteenBitMode parameters with no video in ее
                
}};

//----------------------------------

resource 'srsc' (1127, "_sRsrc_Vid_Civic_vi2PRGB512") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_viNTSCST"}; 
                
  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCST"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCST"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCST"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_NTSCSTa"};		// offset to SixteenBitMode parameters with no video in еее
                
}};

//----------------------------------

resource 'srsc' (1145, "_sRsrc_Vid_Civic_viFPa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viFP"}; 
  MinorLength,      l{"_MinorLength_Civic_viFPa"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_FP"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_FP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_FP"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_Civic_FPa"};			// offset to EightBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1150, "_sRsrc_Vid_Civic_viFPb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viFP"}; 
  MinorLength,      l{"_MinorLength_Civic_viFPb"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_FP"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_FP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_FP"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_FP"};				// offset to EightBitMode parameters

}};

//----------------------------------

resource 'node' (1151, "_sRsrc_Vid_Civic_vi2P512") {{
  include{l{"_sRsrc_Vid_Civic_viFP512"}};
}};

resource 'srsc' (1152, "_sRsrc_Vid_Civic_viFP512") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_viNTSCST"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCST"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCST"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCST"};			// offset to EightBitMode parameters

}};

//----------------------------------

resource 'node' (1153, "_sRsrc_Vid_Civic_vi2P640") {{
  include{l{"_sRsrc_Vid_Civic_viFP640"}};
}};

resource 'srsc' (1154, "_sRsrc_Vid_Civic_viFP640") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_NTSCFFa"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCFF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCFF"};			// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (1160, "_sRsrc_Vid_Civic_viGS") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viGS"}; 
  MinorLength,      l{"_MinorLength_Civic_GS"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_GS"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_GS"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_GS"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_GS"};				// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_GS"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_GSa"};			// offset to ThirtyTwoBitMode parameters with no video-in ее
                
}};


//----------------------------------

resource 'srsc' (1170, "_sRsrc_Vid_Civic_viGS560") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viGS"}; 
  MinorLength,      l{"_MinorLength_Civic_GS560"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_GS560"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_GS560"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_GS560"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_GS560"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_GS560"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_GS560a"};		// offset to ThirtyTwoBitMode parameters with no video-in ее
                
}};


//----------------------------------

resource 'srsc' (1185, "_sRsrc_Vid_Civic_vi2Pa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi2P"}; 
  MinorLength,      l{"_MinorLength_Civic_vi2Pa"}; 

  sGammaDir,        a{"_GammaDir_2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_DAFB_2P"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_DAFB_2P"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_DAFB_2P"};				// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_Civic_2Pa"};			// offset to EightBitMode parameters without video-in ее
                
}};


//----------------------------------

resource 'srsc' (1187, "_sRsrc_Vid_Civic_vi2Pb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi2P"}; 
  MinorLength,      l{"_MinorLength_Civic_vi2Pa"}; 

  sGammaDir,        a{"_GammaDir_2P"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_DAFB_2P"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_DAFB_2P"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_DAFB_2P"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_2P"};				// offset to EightBitMode parameters
                
}};

//----------------------------------

resource 'node' (1188, "_sRsrc_Vid_Civic_vi2PRGB768a") {{
  include{l{"_sRsrc_Vid_Civic_vi2P768"}};
}};

resource 'srsc' (1191, "_sRsrc_Vid_Civic_vi2P768") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viPALFF"}; 
  MinorLength,      l{"_MinorLength_Civic_viPALFF"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALFF"};			// offset to FourBitMode parameters
                
}};

                
//----------------------------------

resource 'node' (1211, "_sRsrc_Vid_Civic_vi2PRGB640a") {{
  include{l{"_sRsrc_Vid_Civic_viGFNTSCFFa"}};
}};

resource 'node' (1212, "_sRsrc_Vid_Civic_viGFNTSCFFa") {{
  include{l{"_sRsrc_Vid_Civic_viNTSCFFa"}};
}};

resource 'srsc' (1215, "_sRsrc_Vid_Civic_viNTSCFFa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_NTSCFFa"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCFF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCFF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_NTSCFFa"};		// offset to SixteenBitMode parameters without video-in ее
                
}};


//----------------------------------

resource 'node' (1218, "_sRsrc_Vid_Civic_viGFNTSCFFb") {{
  include{l{"_sRsrc_Vid_Civic_viNTSCFFb"}};
}};

resource 'srsc' (1220, "_sRsrc_Vid_Civic_viNTSCFFb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_NTSCFFa"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCFF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCFF"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_NTSCFF"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_NTSCFFa"};		// offset to SixteenBitMode parameters without video-in ее
                
}};


//----------------------------------

resource 'node' (1235, "_sRsrc_Vid_Civic_viHRNTSCST") {{
  include{l{"_sRsrc_Vid_Civic_viGFNTSCST"}};
}};

resource 'node' (1240, "_sRsrc_Vid_Civic_viGFNTSCST") {{
  include{l{"_sRsrc_Vid_Civic_viNTSCST"}};
}};

resource 'srsc' (1245, "_sRsrc_Vid_Civic_viNTSCST") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viNTSC"}; 
  MinorLength,      l{"_MinorLength_Civic_viNTSCST"}; 
                
  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCST"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCST"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCST"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_NTSCST"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_NTSCSTb"};		// offset to ThirtyTwoBitMode parameters without video-in ее
                
}};


//----------------------------------

resource 'srsc' (1260, "_sRsrc_Vid_Civic_NTSCFFConva") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_NTSCConv"}; 
  MinorLength,      l{"_MinorLength_Civic_NTSCFFConv"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCFFConv"};		// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCFFConv"};		// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCFFConv"};		// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCFFConv"};		// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1280, "_sRsrc_Vid_Civic_NTSCSTConv") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_NTSCConv"}; 
  MinorLength,      l{"_MinorLength_Civic_NTSCSTConv"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_NTSCSTConv"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_NTSCSTConv"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_NTSCSTConv"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_NTSCSTConv"};			// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1290, "_sRsrc_Vid_Civic_viFPRGBa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viFP"}; 
  MinorLength,      l{"_MinorLength_Civic_viFPa"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_FP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_FP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_FP"};					// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_Civic_FPa"};				// offset to EightBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1300, "_sRsrc_Vid_Civic_viFPRGBb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viFP"}; 
  MinorLength,      l{"_MinorLength_Civic_viFPb"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_FP"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_FP"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_FP"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_FP"};				// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_FPa"};			// offset to SixteenBitMode parameters without video-in ее

}};


//----------------------------------

resource 'node' (1325, "_sRsrc_Vid_Civic_viHRa") {{
  include{l{"_sRsrc_Vid_Civic_viVGAa"}};
}};

resource 'srsc' (1330, "_sRsrc_Vid_Civic_viVGAa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viHR"}; 
  MinorLength,      l{"_MinorLength_Civic_viHRa"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_HR"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_HR"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_HR"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_HR"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_HRa"};		// offset to SixteenBitMode parameters without video-in ее

}};


//----------------------------------

resource 'node' (1335, "_sRsrc_Vid_Civic_viHRb") {{
  include{l{"_sRsrc_Vid_Civic_viVGAb"}};
}};

resource 'srsc' (1340, "_sRsrc_Vid_Civic_viVGAb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viHR"}; 
  MinorLength,      l{"_MinorLength_Civic_viHRb"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_HR"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_HR"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_HR"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_HR"};				// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_HR"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_HRa"};			// offset to ThirtyTwoBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1350, "_sRsrc_Vid_Civic_viHR400") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viHR"}; 
  MinorLength,      l{"_MinorLength_Civic_viHR400"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_HR400"};				// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_HR400"};				// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_HR400"};				// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_HR400"};				// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_HR400"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_HR400a"};			// offset to ThirtyTwoBitMode parameters without video-in ее

}};

                
//----------------------------------

resource 'node' (1391, "_sRsrc_Vid_Civic_viGFPALFFa") {{
  include{l{"_sRsrc_Vid_Civic_viPALFFConva"}};
}};

resource 'node' (1392, "_sRsrc_Vid_Civic_viPALFFConva") {{
  include{l{"_sRsrc_Vid_Civic_viPALFFa"}};
}};

resource 'srsc' (1395, "_sRsrc_Vid_Civic_viPALFFa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viPALFF"}; 
  MinorLength,      l{"_MinorLength_Civic_viPALFF"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALFF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_PALFFa"};		// offset to SixteenBitMode parameters without video-in ее
                
}};

                
//----------------------------------

resource 'node' (1397, "_sRsrc_Vid_Civic_viGFPALFFb") {{
  include{l{"_sRsrc_Vid_Civic_viPALFFb"}};
}};

resource 'srsc' (1400, "_sRsrc_Vid_Civic_viPALFFb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viPALFF"}; 
  MinorLength,      l{"_MinorLength_Civic_viPALFF"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALFF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALFF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALFF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALFF"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_PALFF"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_PALFFa"};		// offset to SixteenBitMode parameters without video-in ее
                
}};

                
//----------------------------------

resource 'srsc' (1435, "_sRsrc_Vid_Civic_viPALSTa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viPALST"}; 
  MinorLength,      l{"_MinorLength_Civic_PALSTa"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALST"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_PALSTa"};		// offset to SixteenBitMode parameters without video-in ее

}};

                
//----------------------------------

resource 'srsc' (1437, "_sRsrc_Vid_Civic_viPALSTb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viPALST"}; 
  MinorLength,      l{"_MinorLength_Civic_PALSTa"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration
	
  FirstVidMode,     a{"_OBM_Civic_PALST"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALST"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALST"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALST"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_PALST"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_PALSTa"};		// offset to SixteenBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1440, "_sRsrc_Vid_Civic_PALFFConva") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_PALConv"}; 
  MinorLength,      l{"_MinorLength_Civic_PALFFConv"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALFFConv"};	// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALFFConv"};	// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALFFConv"};	// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALFFConv"};	// offset to EightBitMode parameters

}};


//----------------------------------

resource 'srsc' (1445, "_sRsrc_Vid_Civic_PALSTConva") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_PALConv"}; 
  MinorLength,      l{"_MinorLength_Civic_PALSTConv"}; 

  sGammaDir,        a{"_GammaDir_NTSC"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_PALSTConv"};		// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_PALSTConv"};		// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_PALSTConv"};		// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_PALSTConv"};		// offset to EightBitMode parameters

}};


//----------------------------------

resource 'node' (1460, "_sRsrc_Vid_Civic_viSVGA56a") {{
  include{l{"_sRsrc_Vid_Civic_viSVGA72a"}};
}};

resource 'srsc' (1465, "_sRsrc_Vid_Civic_viSVGA72a") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viSVGA"}; 
  MinorLength,      l{"_MinorLength_Civic_SVGAa"}; 

  sGammaDir,        a{"_GammaDir_VGA"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_SVGA"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_SVGA"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_SVGA"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_SVGA"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_SVGAa"};		// offset to SixteenBitMode parameters without video-in ее

}};


//----------------------------------

resource 'node' (1480, "_sRsrc_Vid_Civic_viSVGA56b") {{
  include{l{"_sRsrc_Vid_Civic_viSVGA72b"}};
}};

resource 'srsc' (1485, "_sRsrc_Vid_Civic_viSVGA72b") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viSVGA"}; 
  MinorLength,      l{"_MinorLength_Civic_SVGAb"}; 

  sGammaDir,        a{"_GammaDir_VGA"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_SVGA"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_SVGA"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_SVGA"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_SVGA"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_SVGA"};			// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_SVGAa"};		// offset to ThirtyTwoBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1500, "_sRsrc_Vid_Civic_viGFa") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viGF"}; 
  MinorLength,      l{"_MinorLength_Civic_GFa"}; 

  sGammaDir,        a{"_GammaDir_GF"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_GF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_GF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_GF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_GF"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_GFa"};		// offset to SixteenBitMode parameters without video-in ее

}};


//----------------------------------

resource 'srsc' (1505, "_sRsrc_Vid_Civic_viGFb") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_viGF"}; 
  MinorLength,      l{"_MinorLength_Civic_GFa"}; 

  sGammaDir,        a{"_GammaDir_GF"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_GF"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_GF"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_GF"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_GF"};			// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BM_Civic_GF"};		// offset to SixteenBitMode parameters
  SixthVidMode,     l{"_D32BM_Civic_GFa"};		// offset to ThirtyTwoBitMode parameters without video-in ее

}};


//----------------------------------

resource 'node' (1525, "_sRsrc_Vid_Civic_viSxVGA60a") {{
  include{l{"_sRsrc_Vid_Civic_viSxVGA70a"}};
}};

resource 'node' (1530, "_sRsrc_Vid_Civic_viSxVGA70a") {{
  include{l{"_sRsrc_Vid_Civic_vi19a"}};
}};

resource 'srsc' (1535, "_sRsrc_Vid_Civic_vi19a") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi19"}; 
  MinorLength,      l{"_MinorLength_Civic_19a"}; 

  sGammaDir,        a{"_GammaDir_19"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_19"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_19"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_19"};			// offset to FourBitMode parameters
  FourthVidMode,    l{"_EBM_Civic_19a"}; 		// offset to EightBitMode parameters without video-in ее

}};


//----------------------------------

resource 'node' (1555, "_sRsrc_Vid_Civic_viSxVGA60b") {{
  include{l{"_sRsrc_Vid_Civic_viSxVGA70b"}};
}};

resource 'node' (1560, "_sRsrc_Vid_Civic_viSxVGA70b") {{
  include{l{"_sRsrc_Vid_Civic_vi19b"}};
}};

resource 'srsc' (1565, "_sRsrc_Vid_Civic_vi19b") {{
  sRsrcType,        l{"_VideoTypeCivic"}; 
  sRsrcName,        l{"_VideoNameCivic"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirCivic"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      l{"_MinorBaseCivic_vi19"}; 
  MinorLength,      l{"_MinorLength_Civic_19b"}; 

  sGammaDir,        a{"_GammaDir_19"}; 
                
//Parameters - this consists of a list of the different modes supported by this hardware configuration

  FirstVidMode,     a{"_OBM_Civic_19"};			// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBM_Civic_19"};			// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBM_Civic_19"};			// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBM_Civic_19"};			// offset to EightBitMode parameters
  FifthVidMode,     l{"_D16BM_Civic_19a"};		// offset to SixteenBitMode parameters without video-in ее

}};

//-------------------------------------------------------------
// Resource Types
//-------------------------------------------------------------

resource 'styp' (1620, "_VideoTypeCivic") 	{CatDisplay, TypVideo, DrSwApple, DrHwCivic};

//-------------------------------------------------------------
// Resource Names
//-------------------------------------------------------------

resource 'cstr' (1675, "_VideoNameCivic")  {"Display_Video_Apple_Civic"};


//-------------------------------------------------------------
// Driver
//-------------------------------------------------------------

resource 'ddir' (1775, "_VidDrvrDirCivic") {{
  sMacOS68020, l{"_sCivicDrvrDir"};
}};

resource 'node' (576, "_sCivicDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{20};}}};
}};

//-------------------------------------------------------------
// Minor base
//-------------------------------------------------------------

resource 	'long' 	(1870, 		"_MinorBaseCivic_vi19"		) 	{Civic_256_Base};

resource 	'long' 	(1875, 		"_MinorBaseCivic_vi2P"		) 	{Civic_1280_Base};

resource 	'node' (1970, 		"_MinorBaseCivic_GS"		) 	{{
	include{l{					"_MinorBaseCivic_FP"		}};	}};
resource 	'node' 	(1880, 		"_MinorBaseCivic_FP"		) 	{{
	include{l{					"_MinorBaseCivic_HR"		}};	}};
resource	 'node' (1883, 		"_MinorBaseCivic_HR"		) 	{{
	include{l{					"_MinorBaseCivic_NTSC"		}};	}};
resource 	'node' 	(1885, 		"_MinorBaseCivic_NTSC"		) 	{{
	include{l{					"_MinorBaseCivic_PALST"		}};	}};
resource 	'node' (1890, 		"_MinorBaseCivic_PALST"		) 	{{
	include{l{					"_MinorBaseCivic_19"		}};	}};
resource 	'long' (1900, 		"_MinorBaseCivic_19"		) 	{Civic_1536_Base};

resource 	'node' (1905, 		"_MinorBaseCivic_viPALFF"	) 	{{
	include{l{					"_MinorBaseCivic_viSVGA"	}};	}};
resource 	'node' (1910, 		"_MinorBaseCivic_viSVGA"	) 	{{
	include{l{					"_MinorBaseCivic_viGF"		}};	}};
resource 	'long' (1920, 		"_MinorBaseCivic_viGF"	) 	{Civic_1792_Base};

resource 	'node' (1925, 		"_MinorBaseCivic_viGS"		) 	{{
	include{l{					"_MinorBaseCivic_viNTSC"	}};	}};
resource 	'node' (1930, 		"_MinorBaseCivic_viNTSC"	) 	{{
	include{l{					"_MinorBaseCivic_viPALST"	}};	}};
resource 	'node' (1935, 		"_MinorBaseCivic_viPALST"	) 	{{
	include{l{					"_MinorBaseCivic_viFP"		}};	}};
resource 	'node' (1940, 		"_MinorBaseCivic_viFP"		) 	{{
	include{l{					"_MinorBaseCivic_viHR"		}};	}};
resource 	'long' (1945, 		"_MinorBaseCivic_viHR"		) 	{Civic_2048_Base};

resource 	'long' (1947, 		"_MinorBaseCivic_2P"		) 	{Civic_2560_Base};

resource 	'node' (1955, 		"_MinorBaseCivic_PALFF"		) 	{{
	include{l{					"_MinorBaseCivic_GF"		}};	}};
resource 	'node' (1960, 		"_MinorBaseCivic_GF"		) 	{{
	include{l{					"_MinorBaseCivic_SVGA"		}};	}};
resource 	'long' (1965, 		"_MinorBaseCivic_SVGA"		) 	{Civic_3584_Base};

resource 	'node' (1980, 		"_MinorBaseCivic_PALConv"	) 	{{
	include{l{					"_MinorBaseCivic_NTSCConv"	}};	}};
resource 'long' (1985, 			"_MinorBaseCivic_NTSCConv"	) 	{Civic_4096_Base};

//-------------------------------------------------------------
// Minor length
//-------------------------------------------------------------

resource 'node' (2390, "_MinorLength_Civic_viFPb") {{include{l{"_MinorLength_Civic_FPa"}};}};
resource 'long' (2395, "_MinorLength_Civic_FPa") {MinorLength_Civic_FPa};
resource 'long' (2400, "_MinorLength_Civic_FPb") {MinorLength_Civic_FPb};
resource 'long' (2405, "_MinorLength_Civic_viFPa") {MinorLength_Civic_viFPa};
resource 'node' (2410, "_MinorLength_Civic_viNTSCST") {{include{l{"_MinorLength_Civic_GS"}};}};
resource 'node' (2415, "_MinorLength_Civic_GS") {{include{l{"_MinorLength_Civic_NTSCST"}};}};
resource 'long' (2420, "_MinorLength_Civic_NTSCST") {MinorLength_Civic_GS};
resource 'long' (2425, "_MinorLength_Civic_GS560") {MinorLength_Civic_GS560};
resource 'long' (2430, "_MinorLength_Civic_2Pa") {MinorLength_Civic_2Pa};
resource 'long' (2435, "_MinorLength_Civic_2Pb") {MinorLength_Civic_2Pb};
resource 'long' (2440, "_MinorLength_Civic_vi2Pa") {MinorLength_Civic_vi2Pa};
resource 'long' (2445, "_MinorLength_Civic_viHRa") {MinorLength_Civic_viHRa};

resource 'node' (2455, "_MinorLength_Civic_PALSTa") {{
	include{l{"_MinorLength_Civic_NTSCFFa"}};
}};

resource 'node' (2460, "_MinorLength_Civic_NTSCFFa") {{
	include{l{"_MinorLength_Civic_VGAa"}};
}};

resource 'node' (2465, "_MinorLength_Civic_VGAa") {{
	include{l{"_MinorLength_Civic_viHRb"}};
}};

resource 'node' (2470, "_MinorLength_Civic_viHRb") {{
	include{l{"_MinorLength_Civic_HRa"}};
}};

resource 'long' (2475, "_MinorLength_Civic_HRa") {MinorLength_Civic_HRa};

resource 'node' (2480, "_MinorLength_Civic_PALSTb") {{
	include{l{"_MinorLength_Civic_NTSCFFb"}};
}};

resource 'node' (2485, "_MinorLength_Civic_NTSCFFb") {{
	include{l{"_MinorLength_Civic_VGAb"}};
}};

resource 'node' (2490, "_MinorLength_Civic_VGAb") {{
	include{l{"_MinorLength_Civic_HRb"}};
}};

resource 'long' (2495, "_MinorLength_Civic_HRb") {MinorLength_Civic_HRb};
resource 'long' (2500, "_MinorLength_Civic_HR400") {MinorLength_Civic_HR400};

resource 'node' (2505, "_MinorLength_Civic_viPALST") {{
	include{l{"_MinorLength_Civic_viHR400"}};
}};

resource 'long' (2510, "_MinorLength_Civic_viHR400") {MinorLength_Civic_viHR400};

resource 'long' (2530, "_MinorLength_Civic_NTSCFFConv") {MinorLength_Civic_NTSCFFConv};
resource 'long' (2535, "_MinorLength_Civic_NTSCSTConv") {MinorLength_Civic_NTSCSTConv};
resource 'long' (2540, "_MinorLength_Civic_PALFFa") {MinorLength_Civic_PALFFa};
resource 'long' (2545, "_MinorLength_Civic_PALFFb") {MinorLength_Civic_PALFFb};
resource 'long' (2550, "_MinorLength_Civic_viPALFF") {MinorLength_Civic_viPALFF};
resource 'long' (2555, "_MinorLength_Civic_PALFFConv") {MinorLength_Civic_PALFFConv};
resource 'long' (2560, "_MinorLength_Civic_PALSTConv") {MinorLength_Civic_PALSTConv};
resource 'long' (2565, "_MinorLength_Civic_SVGAa") {MinorLength_Civic_SVGAa};
resource 'long' (2570, "_MinorLength_Civic_SVGAb") {MinorLength_Civic_SVGAb};
resource 'long' (2575, "_MinorLength_Civic_GFa") {MinorLength_Civic_GFa};
resource 'long' (2580, "_MinorLength_Civic_GFb") {MinorLength_Civic_GFb};
resource 'long' (2585, "_MinorLength_Civic_19a") {MinorLength_Civic_19a};
resource 'long' (2590, "_MinorLength_Civic_19b") {MinorLength_Civic_19b};

//-------------------------------------------------------------
//               Eight-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (9000, "_EBM_Civic_vi2Pa") {{
  mVidParams,       l{"_EBVParms_Civic_vi2Pa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

resource 'vmod' (9005, "_EBM_Civic_FPa") {{
  mVidParams,       l{"_EBVParms_Civic_FPa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

resource 'vmod' (9010, "_EBM_Civic_2Pa") {{
  mVidParams,       l{"_EBVParms_Civic_2Pa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

resource 'vmod' (9015, "_EBM_Civic_19a") {{
  mVidParams,       l{"_EBVParms_Civic_19a"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{defmDevType}; 
}};

resource 'node' (9020, "_EBVParms_Civic_vi2Pa") {{
  blocksize{};
  longs{{Civic_1280_Offset;}};
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

resource 'node' (9025, "_EBVParms_Civic_FPa") {{
  blocksize{};

  longs{{Civic_M512_Offset;}};
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

resource 'node' (9030, "_EBVParms_Civic_2Pa") {{
  blocksize{};

  longs{{Civic_1280_Offset;}};
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

resource 'node' (9035, "_EBVParms_Civic_19a") {{
  blocksize{};
  longs{{Civic_1280_Offset;}};
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

//-------------------------------------------------------------
//               Sixteen-Bit per pixel parameters
//-------------------------------------------------------------

resource 'vmod' (9040, "_D16BM_Civic_2Pa") {{
  mVidParams,       l{"_D16BVParms_Civic_2Pa"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'node' (9045, "_D16BM_Civic_NTSCSTa") {{
  include{l{"_D16BM_Civic_GSa"}};
}};

resource 'vmod' (9050, "_D16BM_Civic_GSa") {{
  mVidParams,       l{"_D16BVParms_Civic_GSa"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_DAFB};                    	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'node' (9055, "_D16BM_Civic_HRa") {{
  include{l{"_D16BM_Civic_PALSTa"}};
}};

resource 'node' (9060, "_D16BM_Civic_PALSTa") {{
  include{l{"_D16BM_Civic_NTSCFFa"}};
}};

resource 'vmod' (9065, "_D16BM_Civic_NTSCFFa") {{
  mVidParams,       l{"_D16BVParms_Civic_NTSCFFa"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9070, "_D16BM_Civic_FPa") {{
  mVidParams,       l{"_D16BVParms_Civic_FPa"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_Civic};                   	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};


resource 'vmod' (9075, "_D16BM_Civic_PALFFa") {{
  mVidParams,       l{"_D16BVParms_Civic_PALFFa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9080, "_D16BM_Civic_SVGAa") {{
  mVidParams,       l{"_D16BVParms_Civic_SVGAa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9085, "_D16BM_Civic_GFa") {{
  mVidParams,       l{"_D16BVParms_Civic_GFa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9090, "_D16BM_Civic_19a") {{
  mVidParams,       l{"_D16BVParms_Civic_19a"};				// offset to vid parameters for this configuration
  mPageCnt,         d{defPages_Civic};                   	// number of video pages in this configuration
  mDevType,         d{directType};                       	// device type
}};

resource 'node' (9095, "_D16BVParms_Civic_2Pa") {{
  blocksize{};                                               // physical Block Size
  longs{{Civic_1280_Offset;}};
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

resource 'node' (9100, "_D16BVParms_Civic_GSa") {{
  blocksize{};                                               // physical Block Size
  longs{{Civic_M512_Offset;}};
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

resource 'node' (9105, "_D16BVParms_Civic_PALFFa") {{
  blocksize{};
  longs{{Civic_1792_Offset;}};
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

resource 'node' (9110, "_D16BVParms_Civic_NTSCFFa") {{
  blocksize{};

  longs{{Civic_M512_Offset;}};
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

resource 'node' (9115, "_D16BVParms_Civic_SVGAa") {{
  blocksize{};
  longs{{Civic_1792_Offset;}};
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

resource 'node' (9120, "_D16BVParms_Civic_FPa") {{
  blocksize{};                                               // physical Block Size
  longs{{Civic_M512_Offset;}};
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

resource 'node' (9125, "_D16BVParms_Civic_GFa") {{
  blocksize{};

  longs{{Civic_1792_Offset;}};
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

resource 'node' (9130, "_D16BVParms_Civic_19a") {{
  blocksize{};                                               // physical Block Size
  longs{{Civic_1280_Offset;}};
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

//-------------------------------------------------------------
//               ThirtyTwo-Bit per pixel parameters
//-------------------------------------------------------------

resource 'node' (9133, "_D32BM_Civic_NTSCSTb") {{
  include{l{"_D32BM_Civic_GSa"}};
}};

resource 'vmod' (9135, "_D32BM_Civic_GSa") {{
  mVidParams,       l{"_D32BVParms_Civic_GSa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9140, "_D32BM_Civic_GS560a") {{
  mVidParams,       l{"_D32BVParms_Civic_GS560a"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (9145, "_D32BM_Civic_HRa") {{
  include{l{"_D32BM_Civic_PALSTa"}};
}};

resource 'node' (9150, "_D32BM_Civic_PALSTa") {{
  include{l{"_D32BM_Civic_NTSCFFa"}};
}};

resource 'vmod' (9155, "_D32BM_Civic_NTSCFFa") {{
  mVidParams,       l{"_D32BVParms_Civic_640by480a"};		// a number of different modes share this mVidParams block
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9160, "_D32BM_Civic_HR400a") {{
  mVidParams,       l{"_D32BVParms_Civic_HR400a"}; 
  mPageCnt,         d{defPages_Civic}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9165, "_D32BM_Civic_PALFFa") {{
  mVidParams,       l{"_D32BVParms_Civic_PALFFa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9170, "_D32BM_Civic_SVGAa") {{
  mVidParams,       l{"_D32BVParms_Civic_SVGAa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'vmod' (9175, "_D32BM_Civic_GFa") {{
  mVidParams,       l{"_D32BVParms_Civic_GFa"}; 
  mPageCnt,         d{defPages_DAFB}; 
  mDevType,         d{directType}; 
}};


resource 'node' (9180, "_D32BVParms_Civic_GSa") {{
  blocksize{};

  longs{{Civic_M512_Offset;}};
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

resource 'node' (9185, "_D32BVParms_Civic_GS560a") {{
  blocksize{};

  longs{{Civic_2048_Offset;}};
  words{{Civic_2560_RB;}};
  words{{defmBounds_TGS;defmBounds_LGS;defmBounds_BGS560;defmBounds_RGS560;}};		// <LW12>  
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

resource 'node' (9190, "_D32BVParms_Civic_640by480a") {{
  blocksize{};
  longs{{Civic_M512_Offset;}};
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


resource 'node' (9195, "_D32BVParms_Civic_HR400a") {{
  blocksize{};

  longs{{Civic_2048_Offset;}};
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

resource 'node' (9200, "_D32BVParms_Civic_PALFFa") {{
  blocksize{};
  longs{{Civic_1792_Offset;}};
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

resource 'node' (9205, "_D32BVParms_Civic_SVGAa") {{
  blocksize{};

  longs{{Civic_1792_Offset;}};
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

resource 'node' (9210, "_D32BVParms_Civic_GFa") {{
  blocksize{};
  longs{{Civic_1792_Offset;}};
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


//===================================================================
// Video parameters directory
//===================================================================

resource 'list' (2750, "_VidParmDir_Civic") {{
                                
  sRsrc_Vid_Civic_NTSCFFConva, l{"_sVidParms_Civic_NTSCFFConv"};		// (Video-in:   No video-in: 1,2,4,8 )	NTSCFF Conv (1 or 2 Meg)
  sRsrc_Vid_Civic_NTSCSTConv, l{"_sVidParms_Civic_NTSCSTConv"};			// (Video-in:   No video-in: 1,2,4,8 )	NTSCST Conv (1 or 2 Meg)
                                
  sRsrc_Vid_Civic_PALFFConva, l{"_sVidParms_Civic_PALFFConv"};			// (Video-in:   No video-in: 1,2,4,8 )	PALFF Conv (1 or 2 Meg)
  sRsrc_Vid_Civic_PALSTConva, l{"_sVidParms_Civic_PALSTConv"};			// (Video-in:   No video-in: 1,2,4,8 )	PALST Conv (1 or 2 Meg)


  sRsrc_Vid_Civic_vi2PRGBa, l{"_sVidParms_Civic_vi2PRGBa"};				// (Video-in: 1,2,4 	 No video-in: 8 )	2PRGB (1 Meg)
  sRsrc_Vid_Civic_vi2PRGBb, l{"_sVidParms_Civic_vi2PRGBb"};				// (Video-in: 1,2,4,8	 No video-in: 16 )	2PRGB (2 Meg)
  sRsrc_Vid_Civic_vi2PRGB512, l{"_sVidParms_Civic_vi2PRGB512"}; 		// (Video-in: 1,2,4,8    No video-in: 16 )	2PRGB512 (1 or 2 Meg)
  sRsrc_Vid_Civic_vi2PRGB640a, l{"_sVidParms_Civic_vi2PRGB640"}; 		// (Video-in: 1,2,4,8    No video-in: 16 )	2PRGB640 (1 or 2 Meg)
  sRsrc_Vid_Civic_vi2PRGB768a, l{"_sVidParms_Civic_vi2PRGB768"}; 		// (Video-in: 1,2,4 	 No video-in:  )	2PRGB768 (1 or 2 Meg)

  sRsrc_Vid_Civic_viFPa, l{"_sVidParms_Civic_viFPa"};					// (Video-in: 1,2,4 	 No video-in: 8 )	FP (1 Meg)
  sRsrc_Vid_Civic_viFPb, l{"_sVidParms_Civic_viFPb"};					// (Video-in: 1,2,4,8	 No video-in:   )	FP (2 Meg)
  sRsrc_Vid_Civic_viFP512, l{"_sVidParms_Civic_viFP512"};				// (Video-in: 1,2,4,8	 No video-in:   )	FP512 (1 or 2 Meg)
  sRsrc_Vid_Civic_viFP640, l{"_sVidParms_Civic_viFP640"};				// (Video-in: 1,2,4,8	 No video-in:   )	FP640 (1 or 2 Meg)
                
  sRsrc_Vid_Civic_viGS, l{"_sVidParms_Civic_viGS"};						// (Video-in: 1,2,4,8,16 No video-in: 32 )  GS (1 or 2 Meg)
  sRsrc_Vid_Civic_viGS560, l{"_sVidParms_Civic_viGS560"}; 				// (Video-in: 1,2,4,8,16 No video-in: 32 )  GS560 (1 or 2 Meg)
                
  sRsrc_Vid_Civic_vi2Pa, l{"_sVidParms_Civic_vi2Pa"};					// (Video-in: 1,2,4 	 No video-in: 8 )	2P (1 Meg)
  sRsrc_Vid_Civic_vi2Pb, l{"_sVidParms_Civic_vi2Pb"};					// (Video-in: 1,2,4,8	 No video-in:   )	2P (2 Meg)
  sRsrc_Vid_Civic_vi2P512, l{"_sVidParms_Civic_vi2P512"};				// (Video-in: 1,2,4,8	 No video-in:   )	2P512 (1 or 2 Meg)
  sRsrc_Vid_Civic_vi2P640, l{"_sVidParms_Civic_vi2P640"};				// (Video-in: 1,2,4,8	 No video-in:   )	2P640 (1 or 2 Meg)
  sRsrc_Vid_Civic_vi2P768, l{"_sVidParms_Civic_vi2P768"};				// (Video-in: 1,2,4 	 No video-in: 8 )	2P768 (1 or 2 Meg)			
               
  sRsrc_Vid_Civic_viNTSCFFa, l{"_sVidParms_Civic_viNTSCFFa"};			// (Video-in: 1,2,4,8    No video-in: 16 )	NTSC FF (1 Meg)
  sRsrc_Vid_Civic_viNTSCFFb, l{"_sVidParms_Civic_viNTSCFFb"};			// (Video-in: 1,2,4,8,16 No video-in: 32 )  NTSC FF (2 Meg)
  sRsrc_Vid_Civic_viNTSCST, l{"_sVidParms_Civic_viNTSCST"};				// (Video-in: 1,2,4,8,16 No video-in: 32 )  NTSCST (1 or 2 Meg)
                
  sRsrc_Vid_Civic_viFPRGBa, l{"_sVidParms_Civic_viFPRGBa"};				// (Video-in: 1,2,4 	 No video-in: 8 )	FPRGB (1 Meg)
  sRsrc_Vid_Civic_viFPRGBb, l{"_sVidParms_Civic_viFPRGBb"}; 			// (Video-in: 1,2,4,8	 No video-in: 16 )	FPRGB (2 Meg)

  sRsrc_Vid_Civic_viHRa, l{"_sVidParms_Civic_viHRa"};					// (Video-in: 1,2,4,8    No video-in: 16 )	HiRes (1 Meg)
  sRsrc_Vid_Civic_viHRb, l{"_sVidParms_Civic_viHRb"}; 					// (Video-in: 1,2,4,8,16 No video-in: 32 )  HiRes (2 Meg)
  sRsrc_Vid_Civic_viHRNTSCST, l{"_sVidParms_Civic_viHRNTSCST"};			// (Video-in: 1,2,4,8,16 No video-in: 32 )  HRNTSCST (1 or 2 Meg)
  sRsrc_Vid_Civic_viHR400, l{"_sVidParms_Civic_viHR400"}; 				// (Video-in: 1,2,4,8,16 No video-in: 32 )  HR400 (1 or 2 Meg)

  sRsrc_Vid_Civic_viPALFFa, l{"_sVidParms_Civic_viPALFFa"};				// (Video-in: 1,2,4,8    No video-in: 16 )	PAL FF (1 Meg)
  sRsrc_Vid_Civic_viPALFFb, l{"_sVidParms_Civic_viPALFFb"}; 			// (Video-in: 1,2,4,8,16 No video-in: 32 )  PAL FF (2 Meg)
  sRsrc_Vid_Civic_viPALSTa, l{"_sVidParms_Civic_viPALSTa"};				// (Video-in: 1,2,4,8    No video-in: 16 )	PALST (1 Meg)
  sRsrc_Vid_Civic_viPALSTb, l{"_sVidParms_Civic_viPALSTb"}; 			// (Video-in: 1,2,4,8,16 No video-in: 32 )  PALST (2 Meg)

  sRsrc_Vid_Civic_viVGAa, l{"_sVidParms_Civic_viVGAa"};					// (Video-in: 1,2,4,8    No video-in: 16 )  VGA (1 Meg)
  sRsrc_Vid_Civic_viVGAb, l{"_sVidParms_Civic_viVGAb"}; 				// (Video-in: 1,2,4,8,16 No video-in: 32 )  VGA (2 Meg)
                
  sRsrc_Vid_Civic_viSVGA56a, l{"_sVidParms_Civic_viSVGA56a"};			// (Video-in: 1,2,4,8    No video-in: 16 )  SVGA (56Hz) (1 Meg)
  sRsrc_Vid_Civic_viSVGA56b, l{"_sVidParms_Civic_viSVGA56b"}; 			// (Video-in: 1,2,4,8,16 No video-in: 32 )  SVGA (56Hz) (2 Meg)
                
  sRsrc_Vid_Civic_viSVGA72a, l{"_sVidParms_Civic_viSVGA72a"};			// (Video-in: 1,2,4,8    No video-in: 16 )  SVGA (72Hz) (1 Meg)
  sRsrc_Vid_Civic_viSVGA72b, l{"_sVidParms_Civic_viSVGA72b"}; 			// (Video-in: 1,2,4,8,16 No video-in: 32 )  SVGA (72Hz) (2 Meg)
                
  sRsrc_Vid_Civic_viSxVGA60a, l{"_sVidParms_Civic_viSxVGA60a"};			// (Video-in: 1,2,4   	 No video-in: 8 )   SxVGA (60Hz) (1 Meg)
  sRsrc_Vid_Civic_viSxVGA60b, l{"_sVidParms_Civic_viSxVGA60b"}; 		// (Video-in: 1,2,4,8 	 No video-in: 16 )  SxVGA (60Hz) (2 Meg)
                
  sRsrc_Vid_Civic_viSxVGA70a, l{"_sVidParms_Civic_viSxVGA70a"};			// (Video-in: 1,2,4   	 No video-in: 8 )   SxVGA (70Hz) (1 Meg)
  sRsrc_Vid_Civic_viSxVGA70b, l{"_sVidParms_Civic_viSxVGA70b"}; 		// (Video-in: 1,2,4,8 	 No video-in: 16 )  SxVGA (70Hz) (2 Meg)
                
  sRsrc_Vid_Civic_viGFa, l{"_sVidParms_Civic_viGFa"};					// (Video-in: 1,2,4,8    No video-in: 16 )	GoldFish (1 Meg)
  sRsrc_Vid_Civic_viGFb, l{"_sVidParms_Civic_viGFb"}; 					// (Video-in: 1,2,4,8,16 No video-in: 32 )  GoldFish (2 Meg)
  sRsrc_Vid_Civic_viGFNTSCST, l{"_sVidParms_Civic_viGFNTSCST"};			// (Video-in: 1,2,4,8,16 No video-in: 32 )  GoldFish (1 or 2 Meg)
  sRsrc_Vid_Civic_viGFNTSCFFa, l{"_sVidParms_Civic_viGFNTSCFFa"};		// (Video-in: 1,2,4,8    No video-in: 16 )  GoldFish (1 Meg)	
  sRsrc_Vid_Civic_viGFNTSCFFb, l{"_sVidParms_Civic_viGFNTSCFFb"};		// (Video-in: 1,2,4,8,16 No video-in: 32 )  GoldFish (2 Meg)	
  sRsrc_Vid_Civic_viGFPALFFa, l{"_sVidParms_Civic_viGFPALFFa"}; 		// (Video-in: 1,2,4,8    No video-in: 16 )  GoldFish (1 Meg)
  sRsrc_Vid_Civic_viGFPALFFb, l{"_sVidParms_Civic_viGFPALFFb"}; 		// (Video-in: 1,2,4,8,16 No video-in: 32 )  GoldFish (2 Meg)
                
  sRsrc_Vid_Civic_vi19a, l{"_sVidParms_Civic_vi19a"};					// (Video-in: 1,2,4   	 No video-in: 8 )   19" RGB (1 Meg)
  sRsrc_Vid_Civic_vi19b, l{"_sVidParms_Civic_vi19b"}; 					// (Video-in: 1,2,4,8 	 No video-in: 16 )  19" RGB (2 Meg)

}};


//===================================================================
// Video timing parameters
//===================================================================


// Vesuvio Video-In Parameters (Civic) (1 Meg)
//
resource 'node' (2885, "_sVidParms_Civic_vi2PRGBa") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;82;(1822+0);1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;18;0;0;128;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;18;0;0;128;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;18;0;0;128;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;36;0;0;128;3;}};                                  // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
}}; 

// Vesuvio Video-In Parameters (Civic) (2 Megs)
//
resource 'node' (2886, "_sVidParms_Civic_vi2PRGBb") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;82;(1822+0);1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;18;0;0;128;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;18;0;0;128;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;18;0;0;128;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;36;0;0;128;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.

// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;72;0;0;128;4;}};                                  // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
}};


// Vesuvio Video-In Parameters (Civic) (1 or 2 Meg)
// (512x384 Resolution)

resource 'node' (2890, "_sVidParms_Civic_vi2PRGB512") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;568;1336;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;288;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;288;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;288;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;288;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.

// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;288;4;}};                                  // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
}};


// Vesuvio Parameters (Civic) (1 or 2 Meg)
// (640x480 Resolution)

resource 'node' (2887, "_sVidParms_Civic_vi2PRGB640") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;472;1432;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;256;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;256;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;256;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;256;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.

// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;256;4;}};                                  // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
}};


// Vesuvio Parameters (Civic) (1 or 2 Meg)
// (768x576 Resolution)

resource 'node' (2888, "_sVidParms_Civic_vi2PRGB768") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{ThirdVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;376;1528;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;224;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;224;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;224;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
}};



//
// Full-Page Parameters (Civic) (1 Meg)
//
resource 'node' (2895, "_sVidParms_Civic_viFPa") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;ThirdVidMode}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk., ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;46;88;1828;1831;}};                     // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;72;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;16;0;0;72;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;72;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;3;}};                                   // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 16bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;152;20;}};                                 // Framebuffer Params.
  words{{752;416;40;831;79;153;793;830;}};                   // Horiz Params.
}};

//
// Full-Page Parameters (Civic) (2 Meg)
//
resource 'node' (2896, "_sVidParms_Civic_viFPb") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk., ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;46;88;1828;1831;}};                     // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;72;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;16;0;0;72;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;72;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 16bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;152;20;}};                                   // Framebuffer Params.
  words{{752;416;40;831;79;153;793;830;}};                    // Horiz Params.
}};


//
// Full-Page Parameters (Civic) (1 or 2 Meg)
// (512x384 Resolution)

resource 'node' (2897, "_sVidParms_Civic_viFP512") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk., ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;46;574;1342;1831;}};                     // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;104;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;105;361;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;104;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;105;361;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;104;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;105;361;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												  // Bus Size (0 = video-in)
  words{{0;32;0;0;104;19;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;105;361;414;}};                    // Horiz Params.

// 16bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{0;}};												   // Bus Size (0 = video-in)
  words{{0;32;0;0;216;20;}};                                   // Framebuffer Params.
  words{{752;416;40;831;79;217;729;830;}};                     // Horiz Params.
}};


//
// Full-Page Parameters (Civic) (1 or 2 Meg)
// 640x480 Resolution

resource 'node' (1898, "_sVidParms_Civic_viFP640") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk., ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;46;478;1438;1831;}};                     // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;72;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;72;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 16bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;152;20;}};                                   // Framebuffer Params.
  words{{752;416;40;831;79;153;793;830;}};                    // Horiz Params.
}};


//
// Rubik Parameters (Civic) (1 or 2 Meg)
//
resource 'node' (2910, "_sVidParms_Civic_viGS") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                  // Convolution NTSC, PAL spID's.

  bytes{{13;95;1;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$32a1c0;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$1dd080;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{24;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{814;812;4;23;42;810;811;}};                         // Vert. Params.
  words{{defmBounds_BGS-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;48;16;}};                                  // Framebuffer Params.
  words{{304;160;8;319;15;49;305;318;}};                     // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;48;17;}};                                  // Framebuffer Params.
  words{{304;160;8;319;15;49;305;318;}};                     // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;48;18;}};                                  // Framebuffer Params.
  words{{304;160;8;319;15;49;305;318;}};                     // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;48;19;}};                                  // Framebuffer Params.
  words{{304;160;8;319;15;49;305;318;}};                     // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;98;20;}};                                  // Framebuffer Params.
  words{{608;320;16;639;31;99;611;638;}};                    // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;64;0;0;98;5;}};                                   // Framebuffer Params.
  words{{608;320;16;639;31;99;611;638;}};                    // Horiz Params.
}};


                
//
// Rubik-560 Parameters (Civic) ( 1 or 2 Meg)
//
resource 'node' (2925, "_sVidParms_Civic_viGS560") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{14;93;1;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$105100;}};										 // Clifton's W Parameter
  bytes{{22;0;}};											 // Clifton's W Size, Clk
  longs{{$24d100;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{814;812;4;23;42;810;811;}};                         // Vert. Params.
  words{{defmBounds_BGS560-1;}};                             // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;56;16;}};                                  // Framebuffer Params.
  words{{328;176;12;351;23;57;337;350;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;56;17;}};                                  // Framebuffer Params.
  words{{328;176;12;351;23;57;337;350;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;56;18;}};                                  // Framebuffer Params.
  words{{328;176;12;351;23;57;337;350;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;56;19;}};                                  // Framebuffer Params.
  words{{328;176;12;351;23;57;337;350;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;114;20;}};                                 // Framebuffer Params.
  words{{656;352;24;703;47;115;675;702;}};                   // Horiz Params.
                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;114;5;}};                                  // Framebuffer Params.
  words{{656;352;24;703;47;115;675;702;}};                   // Horiz Params.
}};

                

// Kong Parameters (Civic) (1 Meg)
//
resource 'node' (2935, "_sVidParms_Civic_vi2Pa") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;82;(1822+0);1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;18;0;0;128;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;18;0;0;128;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;18;0;0;128;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;36;0;0;128;3;}};                                  // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
}};

// Kong Parameters (Civic) (2 Meg)
//
resource 'node' (2936, "_sVidParms_Civic_vi2Pb") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;82;(1822+0);1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;18;0;0;128;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;18;0;0;128;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;18;0;0;128;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;36;0;0;128;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;129;705;726;}};                   // Horiz Params.
}};

// Kong Parameters (Civic) (1 or 2 Meg)
// (512x384 Resolution)

resource 'node' (2937, "_sVidParms_Civic_vi2P512") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;568;1336;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;288;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;288;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;288;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;288;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;289;545;726;}};                   // Horiz Params.
}};


// Kong Parameters (Civic) (1 or 2 Meg)
// (640x480 Resolution)

resource 'node' (2938, "_sVidParms_Civic_vi2P640") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;472;1432;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;256;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;256;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;256;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;256;19;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;257;577;726;}};                   // Horiz Params.
}};


// Kong Parameters (Civic) (1 or 2 Meg)
// (768x576 Resolution)

resource 'node' (2939, "_sVidParms_Civic_vi2P768") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{ThirdVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{31;44;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$39c140;}};										 // Clifton's W Parameter
  bytes{{24;0;}};											 // Clifton's W Size, Clk
  longs{{$1d40b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1830;1828;4;43;376;1528;1825;}};                 // Vert. Params.
  words{{defmBounds_B2P-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;224;16;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;224;17;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;224;18;}};                                 // Framebuffer Params.
  words{{664;364;32;727;63;225;609;726;}};                   // Horiz Params.
}};


//
// NTSC (Full-Frame) Parameters (Civic) (1 Meg)
//

resource 'node' (2950, "_sVidParms_Civic_viNTSCFFa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}};  // Convolution NTSC, PAL spID's.		<LW14> #1084483

  bytes{{3;28;1;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$10d130;}};											 // Clifton's W Parameter
  bytes{{22;1;}};										 	 // Clifton's W Size, Clk
  longs{{$2cb070;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{525;524;4;9;34;514;519;}};                          // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;64;1;0;53;16;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;64;1;0;53;17;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;64;1;0;53;18;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;53;19;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;1;0;53;4;}};                                   // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.

// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;160;1;0;108;5;}};                                 // Framebuffer Params.
  words{{(722 >> 1);390;29;779;57;109;749;778;}};            // Horiz Params.
}};

//
// NTSC (Full-Frame) Parameters (Civic) (2 Meg)
//

resource 'node' (2951, "_sVidParms_Civic_viNTSCFFb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}};  // Convolution NTSC, PAL spID's.		<LW14> #1084483

  bytes{{3;28;1;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$10d130;}};											 // Clifton's W Parameter
  bytes{{22;1;}};										 	 // Clifton's W Size, Clk
  longs{{$2cb070;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{525;524;4;9;34;514;519;}};                          // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;64;1;0;53;16;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;64;1;0;53;17;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;64;1;0;53;18;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;53;19;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;54;374;388;}};             // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;80;1;0;107;20;}};                                 // Framebuffer Params.
  words{{(722 >> 1);390;30;779;56;108;748;778;}};            // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;160;1;0;108;5;}};                                 // Framebuffer Params.
  words{{(722 >> 1);390;29;779;57;109;749;778;}};            // Horiz Params.
}};


//
// NTSC (Full-Frame Convolved) Parameters (Civic) ( 1 or 2 Meg)
//
resource 'node' (2945, "_sVidParms_Civic_NTSCFFConv") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FourthVidMode;0}};                    			     // Max Graphics Mode, Max Video-in Mode
  bytes{{0;1;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};           // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}};    // Convolution NTSC, PAL spID's.

  bytes{{3;7;1;1;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$10c130;}};										 // Clifton's W Parameter
  bytes{{22;1;}};											 // Clifton's W Size, Clk
  longs{{$2c9070;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{525;524;4;9;35;513;519;}};                          // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{4;64;0;1;236;32;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;237;1517;1558;}};       // Horiz Params.
                
// 2bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{3;64;0;1;236;33;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;237;1517;1558;}};       // Horiz Params.
                
// 4bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{2;64;0;1;236;34;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;237;1517;1558;}};       // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;64;0;1;236;35;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;237;1517;1558;}};       // Horiz Params.
}};

                
//
// NTSC (Safe-Title) Parameters (Civic) (1 or 2 Meg)
//
resource 'node' (2965, "_sVidParms_Civic_viNTSCST") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.				<LW17>

  bytes{{3;28;1;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$10d130;}};											 // Clifton's W Parameter
  bytes{{22;1;}};										 	 // Clifton's W Size, Clk
  longs{{$2cb070;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{525;524;4;9;82;466;519;}};                          // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;64;1;0;85;16;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;86;342;388;}};             // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;64;1;0;85;17;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;86;342;388;}};             // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;64;1;0;85;18;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;86;342;388;}};             // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;85;19;}};                                  // Framebuffer Params.
  words{{(361 >> 1);195;15;389;28;86;342;388;}};             // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;171;20;}};                                 // Framebuffer Params.
  words{{(722 >> 1);390;30;778;56;172;684;778;}};            // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;128;1;0;172;5;}};                                 // Framebuffer Params.
  words{{(722 >> 1);390;29;779;57;173;685;778;}};            // Horiz Params.
}};



//
// NTSC (Safe-Title Convolved) Parameters (Civic) (1 or 2 Meg)
//
resource 'node' (2960, "_sVidParms_Civic_NTSCSTConv") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FourthVidMode;0}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{0;1;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};   // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{3;7;1;1;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$10c130;}};												 // Clifton's W Parameter
  bytes{{22;1;}};												 // Clifton's W Size, Clk
  longs{{$2c9070;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{525;524;4;9;83;465;519;}};                          // Vert. Params.
  words{{defmBounds_BNTSCST-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{4;64;0;1;364;32;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;365;1389;1558;}};       // Horiz Params.
                
// 2bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{3;64;0;1;364;33;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;365;1389;1558;}};       // Horiz Params.
                
// 4bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{2;64;0;1;364;34;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;365;1389;1558;}};       // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;64;0;1;364;35;}};                                 // Framebuffer Params.
  words{{(1444 >> 1);780;58;1559;115;365;1389;1558;}};       // Horiz Params.
}};

                
//
// Full-Page RGB Parameters (Civic) (1 Meg)
//
resource 'node' (2975, "_sVidParms_Civic_viFPRGBa") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FifthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;9;88;1828;1832;}};                      // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;72;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;16;0;0;72;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;72;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;3;}};                                   // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 16bpp Params (Only used for getting the 2x timing for video-in)
//               
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;152;20;}};
  words{{752;416;40;831;79;153;793;830;}};                   // Horiz Params.
}};

//
// Full-Page RGB Parameters (Civic) (2 Meg)
//
resource 'node' (2976, "_sVidParms_Civic_viFPRGBb") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1836;1834;4;9;88;1828;1832;}};                      // Vert. Params.
  words{{defmBounds_BFP-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;72;16;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;16;0;0;72;17;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;72;18;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.
                
// 16bpp Params
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;72;4;}};									 // Framebuffer Params.
  words{{376;208;20;415;39;73;393;414;}};                    // Horiz Params.

// 32bpp Params (Only used for getting the 2x timing for video-in)
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;152;5;}};									 // Framebuffer Params.
  words{{752;416;40;831;79;153;793;830;}};                   // Horiz Params.
}};

//
// Hi-Res Parameters (Civic) (1 Meg)
//
resource 'node' (2985, "_sVidParms_Civic_viHRa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};       // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};         // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}};  // Convolution NTSC, PAL spID's.


  bytes{{13;61;0;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$21c900;}};										 // Clifton's W Parameter
  bytes{{23;1;}};											 // Clifton's W Size, Clk
  longs{{$114890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1050;1048;4;43;82;1042;1045;}};                     // Vert. Params.
  words{{defmBounds_BHR-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;72;16;}};                                  // Framebuffer Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;72;17;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;18;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 16bpp Params
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;72;4;}};                                   // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;146;5;}};                                  // Civic/Sebastian Params.
  words{{800;432;32;863;63;147;787;862;}};                   // Horiz Params.
}};

//
// Hi-Res Parameters (Civic) (2 Meg)
//

resource 'node' (2986, "_sVidParms_Civic_viHRb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};       // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};         // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}};  // Convolution NTSC, PAL spID's.


  bytes{{13;61;0;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$21c900;}};										 // Clifton's W Parameter
  bytes{{23;1;}};											 // Clifton's W Size, Clk
  longs{{$114890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1050;1048;4;43;82;1042;1045;}};                     // Vert. Params.
  words{{defmBounds_BHR-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;72;16;}};                                  // Framebuffer Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;72;17;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;18;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 16bpp Params
//               
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;0;0;146;20;}};                                 // Civic/Sebastian Params.
  words{{800;432;32;863;63;147;787;862;}};                   // Horiz Params.

// 32bpp Params
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;146;5;}};                                  // Civic/Sebastian Params.
  words{{800;432;32;863;63;147;787;862;}};                   // Horiz Params.
}};


//
// Hi-Res Parameters (Civic) (1 or 2 Meg)
// (512x384)
resource 'node' (3165, "_sVidParms_Civic_viHRNTSCST") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{13;61;0;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$21c900;}};										 // Clifton's W Parameter
  bytes{{23;1;}};											 // Clifton's W Size, Clk
  longs{{$114890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1050;1048;4;43;178;946;1045;}};                     // Vert. Params.
  words{{defmBounds_BNTSCST-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;104;16;}};                                 // Framebuffer Params.
  words{{400;216;16;431;31;105;361;430;}};                   // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;104;17;}};                                 // Civic/Sebastian Params.
  words{{400;216;16;431;31;105;361;430;}};                   // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;104;18;}};                                 // Civic/Sebastian Params.
  words{{400;216;16;431;31;105;361;430;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;104;19;}};                                 // Civic/Sebastian Params.
  words{{400;216;16;431;31;105;361;430;}};                   // Horiz Params.
                
// 16bpp Params
//               
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;209;20;}};                                 // Civic/Sebastian Params.
  words{{800;432;32;863;63;210;722;862;}};                   // Horiz Params.
                
// 32bpp Params
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;64;0;0;210;5;}};                                  // Civic/Sebastian Params.
  words{{800;432;32;863;63;211;723;862;}};                   // Horiz Params.
}};


//
// Hi-Res (640x400) Parameters (Civic) (1 or 2 Meg)
//
resource 'node' (2995, "_sVidParms_Civic_viHR400") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{13;61;0;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$21c900;}};										 // Clifton's W Parameter
  bytes{{23;1;}};											 // Clifton's W Size, Clk
  longs{{$114890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1050;1048;4;83;162;962;1005;}};                     // Vert. Params.
  words{{defmBounds_BHR400-1;}};                             // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;72;16;}};                                  // Framebuffer Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;72;17;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;72;18;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;72;19;}};                                  // Civic/Sebastian Params.
  words{{400;216;16;431;31;73;393;430;}};                    // Horiz Params.
                
// 16bpp Params
//               
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;146;20;}};                                 // Civic/Sebastian Params.
  words{{800;432;32;863;63;147;787;862;}};                   // Horiz Params.
                
// 32bpp Params
//               
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;146;5;}};                                  // Civic/Sebastian Params.
  words{{800;432;32;863;63;147;787;862;}};                   // Horiz Params.
}};


//
// PAL Full-Frame Parameters (Civic) (1 Meg)
//
resource 'node' (3020, "_sVidParms_Civic_viPALFFa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{5;48;0;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$19d100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$125860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;9;38;614;619;}};                          // Vert. Params.
  words{{defmBounds_BPALFF-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;52;1;0;69;16;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;52;1;0;69;17;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;52;1;0;69;18;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;1;0;69;19;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;1;0;69;4;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;208;1;0;140;5;}};                                 // Framebuffer Params.
  words{{(874>>1);472;35;943;69;141;909;942;}};              // Horiz Params.
}};

//
// PAL Full-Frame Parameters (Civic) (2 Meg)
//
resource 'node' (3021, "_sVidParms_Civic_viPALFFb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{5;48;0;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$19d100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$125860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;9;38;614;619;}};                          // Vert. Params.
  words{{defmBounds_BPALFF-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;52;1;0;69;16;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;52;1;0;69;17;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;52;1;0;69;18;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;1;0;69;19;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;70;454;470;}};               // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;104;1;0;146;20;}};                                // Framebuffer Params.
  words{{(874>>1);472;35;943;69;147;915;942;}};              // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;208;1;0;140;5;}};                                 // Framebuffer Params.
  words{{(874>>1);472;35;943;69;141;909;942;}};              // Horiz Params.
}};


//
// PAL Full-Frame Convolved Parameters (Civic)
//
resource 'node' (3015, "_sVidParms_Civic_PALFFConv") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FourthVidMode;0}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{0;1;}};                                             // Misc Flags.
  bytes{{0;0;}};                       						 // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};   // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{5;12;0;1;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$19c100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$124860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;9;39;613;619;}};                          // Vert. Params.
  words{{defmBounds_BPALFF-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{4;64;0;1;300;32;}};                                 // Framebuffer Params.
  words{{(1748>>1);944;70;1887;139;301;1837;1886;}};         // Horiz Params.
                
// 2bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{3;64;0;1;300;33;}};                                 // Framebuffer Params.
  words{{(1748>>1);944;70;1887;139;301;1837;1886;}};         // Horiz Params.
                
// 4bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{2;64;0;1;300;34;}};                                 // Framebuffer Params.
  words{{(1748>>1);944;70;1887;139;301;1837;1886;}};         // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;64;0;1;300;35;}};                                 // Framebuffer Params.
  words{{(1748>>1);944;70;1887;139;301;1837;1886;}};         // Horiz Params.
}};


//
// PAL Safe-Title Video-In Parameters (Civic) (1 Meg)
//
resource 'node' (3035, "_sVidParms_Civic_viPALSTa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{5;48;0;1;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$19d100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$125860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;19;86;566;619;}};                         // Vert. Params.
  words{{defmBounds_BPALST-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;64;1;0;101;16;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;64;1;0;101;17;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;64;1;0;101;18;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;101;19;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;1;0;101;4;}};                                  // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;160;1;0;204;5;}};                                 // Framebuffer Params.
  words{{(874>>1);472;35;943;69;205;845;942;}};              // Horiz Params.
}};

//
// PAL Safe-Title Video-In Parameters (Civic) (2 Meg)
//
resource 'node' (3036, "_sVidParms_Civic_viPALSTb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{5;48;0;1;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$19d100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$125860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;19;86;566;619;}};                         // Vert. Params.
  words{{defmBounds_BPALST-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;64;1;0;101;16;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;64;1;0;101;17;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;64;1;0;101;18;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;1;0;101;19;}};                                 // Framebuffer Params.
  words{{(437>>1);236;18;471;34;102;422;470;}};              // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;80;1;0;210;20;}};                                 // Framebuffer Params.
  words{{(874>>1);472;35;943;69;211;851;942;}};              // Horiz Params.
                                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;160;1;0;204;5;}};                                 // Framebuffer Params.
  words{{(874>>1);472;35;943;69;205;845;942;}};              // Horiz Params.
}};


//
// PAL Safe-Title Convolved Parameters (Civic)
//
resource 'node' (3030, "_sVidParms_Civic_PALSTConv") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FourthVidMode;0}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{0;1;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  	// NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};  	// PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{5;12;0;1;}};                                        // Endeavor M,N,Clk, ScanCtl.
  longs{{$19c100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$124860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{625;624;4;19;87;565;619;}};                         // Vert. Params.
  words{{defmBounds_BPALST-1;}};                             // Number of rows.
                
// 1bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{4;64;0;1;407;32;}};                                 // Framebuffer Params.
  words{{872;944;72;1881;136;408;1688;1880;}};               // Horiz Params.
                
// 2bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{3;64;0;1;407;33;}};                                 // Framebuffer Params.
  words{{872;944;72;1881;136;408;1688;1880;}};               // Horiz Params.
                
// 4bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{2;64;0;1;407;34;}};                                 // Framebuffer Params.
  words{{872;944;72;1881;136;408;1688;1880;}};               // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;64;0;1;407;35;}};                                 // Framebuffer Params.
  words{{872;944;72;1881;136;408;1688;1880;}};               // Horiz Params.
}};

                

//
// VGA Parameters (Civic) (1 Meg)
//
resource 'node' (3045, "_sVidParms_Civic_viVGAa") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{11;62;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$2991d0;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$175060;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1052;1050;2;35;68;1028;1039;}};                     // Vert. Params.
  words{{defmBounds_BVGA-1;}};                               // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;64;16;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;64;17;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;64;18;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;64;19;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;64;4;}};                                   // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;130;5;}};                                  // Framebuffer Params.
  words{{704;400;48;799;95;131;771;798;}};                   // Horiz Params.
}};

//
// VGA Parameters (Civic) (2 Meg)
//
resource 'node' (3046, "_sVidParms_Civic_viVGAb") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{11;62;0;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$2991d0;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$175060;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1052;1050;2;35;68;1028;1039;}};                     // Vert. Params.
  words{{defmBounds_BVGA-1;}};                               // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;64;16;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;64;17;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;64;18;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;64;19;}};                                  // Framebuffer Params.
  words{{352;200;24;399;47;65;385;398;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;64;0;0;130;20;}};                                 // Framebuffer Params.
  words{{704;400;48;799;95;131;771;798;}};                   // Horiz Params.
                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;130;5;}};                                  // Framebuffer Params.
  words{{704;400;48;799;95;131;771;798;}};                   // Horiz Params.
}};
                

//
// SVGA (56Hz) Parameters (Civic) (1 Meg)
//
resource 'node' (3055, "_sVidParms_Civic_viSVGA56a") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{11;35;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$409370;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$20c910;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1250;1248;2;24;46;1246;1247;}};                     // Vert. Params.
  words{{defmBounds_BSVGA-1;}};                              // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;92;16;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;92;17;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;92;18;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;92;19;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;92;4;}};                                   // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;186;5;}};                                 // Framebuffer Params.
  words{{952;512;36;1023;71;187;987;1022;}};                 // Horiz Params.
}};

//
// SVGA (56Hz) Parameters (Civic) (2 Meg)
//
resource 'node' (3056, "_sVidParms_Civic_viSVGA56b") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{11;35;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$409370;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$20c910;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1250;1248;2;24;46;1246;1247;}};                     // Vert. Params.
  words{{defmBounds_BSVGA-1;}};                              // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;92;16;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;92;17;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;92;18;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;92;19;}};                                  // Framebuffer Params.
  words{{476;256;18;511;35;93;493;510;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;186;20;}};                                 // Framebuffer Params.
  words{{952;512;36;1023;71;187;987;1022;}};                 // Horiz Params.
                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;186;5;}};                                 // Framebuffer Params.
  words{{952;512;36;1023;71;187;987;1022;}};                 // Horiz Params.
}};

                                

//
// SVGA (72Hz) Parameters (Civic) (1 Meg)
//
resource 'node' (3065, "_sVidParms_Civic_viSVGA72a") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{24;55;1;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$0e4140;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$1d48b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1332;1330;10;33;56;1256;1293;}};                    // Vert. Params.
  words{{defmBounds_BSVGA-1;}};                              // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;84;16;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;84;17;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;84;18;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;84;19;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;84;4;}};                                   // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 32bpp Params  (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;170;5;}};                                 // Framebuffer Params.
  words{{920;520;60;1039;119;171;971;1038;}};                // Horiz Params.
}};

//
// SVGA (72Hz) Parameters (Civic) (2 Meg)
//
resource 'node' (3066, "_sVidParms_Civic_viSVGA72b") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{24;55;1;0;}};                                      // Endeavor M,N,Clk, ScanCtl.
  longs{{$0e4140;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$1d48b0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{23;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1332;1330;10;33;56;1256;1293;}};                    // Vert. Params.
  words{{defmBounds_BSVGA-1;}};                              // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;84;16;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;84;17;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;84;18;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;84;19;}};                                  // Framebuffer Params.
  words{{460;260;30;519;59;85;485;518;}};                    // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;170;20;}};                                 // Framebuffer Params.
  words{{920;520;60;1039;119;171;971;1038;}};                // Horiz Params.
                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;170;5;}};                                 // Framebuffer Params.
  words{{920;520;60;1039;119;171;971;1038;}};                // Horiz Params.
}};

                

//
// SxVGA (60Hz) Video-In Parameters (Civic) (1 Meg)
//
resource 'node' (3075, "_sVidParms_Civic_viSxVGA60a") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{21;37;1;0;}};                                     // Endeavor M,N,Clk, ScanCtl.
  longs{{$174100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$144860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1612;1610;10;39;68;(1604+0);1607;}};                // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;140;16;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;140;17;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;140;18;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;36;0;0;140;3;}};                                  // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
}};

//
// SxVGA (60Hz) Video-In Parameters (Civic) (2 Meg)
//
resource 'node' (3076, "_sVidParms_Civic_viSxVGA60b") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{21;37;1;0;}};                                     // Endeavor M,N,Clk, ScanCtl.
  longs{{$174100;}};										 // Clifton's W Parameter
  bytes{{23;0;}};											 // Clifton's W Size, Clk
  longs{{$144860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1612;1610;10;39;68;(1604+0);1607;}};                // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;140;16;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;140;17;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;140;18;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;36;0;0;140;19;}};                                 // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;140;4;}};                                  // Framebuffer Params.
  words{{604;336;34;671;67;141;653;670;}};                   // Horiz Params.
}};

                                
//
// SxVGA (70Hz) Video-In Parameters (Civic) (1 Meg)
//
resource 'node' (3085, "_sVidParms_Civic_viSxVGA70a") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                      			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{55;84;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$1a4130;}};										 // Clifton's W Parameter
  bytes{{22;1;}};											 // Clifton's W Size, Clk
  longs{{$244890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1612;1610;10;39;68;(1604+0);1607;}};                // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;132;16;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;132;17;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;132;18;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;36;0;0;132;3;}};                                  // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
}};

//
// SxVGA (70Hz) Video-In Parameters (Civic) (2 Meg)
//
resource 'node' (3086, "_sVidParms_Civic_viSxVGA70b") {{
  blocksize{};                                               // block size
                
// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{55;84;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$1a4130;}};										 // Clifton's W Parameter
  bytes{{22;1;}};											 // Clifton's W Size, Clk
  longs{{$244890;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;0;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1612;1610;10;39;68;(1604+0);1607;}};                // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;132;16;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;132;17;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;132;18;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;36;0;0;132;19;}};                                 // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;132;4;}};                                  // Framebuffer Params.
  words{{596;332;34;663;67;133;645;662;}};                   // Horiz Params.
}};
                


//
// GoldFish Parameters (Civic) (1 Meg)
//
resource 'node' (3095, "_sVidParms_Civic_viGFa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;82;1330;1331;}};                     // Vert. Params.
  words{{defmBounds_BGF-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;136;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;136;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;136;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;136;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;136;4;}};                                  // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;274;5;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;275;1107;1150;}};               // Horiz Params.
}};

//
// GoldFish Parameters (Civic) (2 Meg)
//
resource 'node' (3096, "_sVidParms_Civic_viGFb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;82;1330;1331;}};                     // Vert. Params.
  words{{defmBounds_BGF-1;}};                                // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;136;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;136;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;136;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;136;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;137;553;574;}};                   // Horiz Params.
                                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;274;20;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;275;1107;1150;}};               // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;274;5;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;275;1107;1150;}};               // Horiz Params.
}};


//
// GoldFish Parameters (Civic) (1 or 2 Meg)
// (512x384 Resolution)

resource 'node' (3130, "_sVidParms_Civic_viGFNTSCST") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       			 // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCST;sRsrc_Vid_Civic_viNTSCST;}};	// NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCSTConv;0;}};                    // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;322;1090;1331;}};                    // Vert. Params.
  words{{defmBounds_BNTSCST-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;216;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;217;473;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;216;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;217;473;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;216;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;217;473;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;216;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;217;473;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;433;20;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;434;946;1150;}};                // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;64;0;0;433;5;}};                                  // Framebuffer Params.
  words{{1088;576;32;1151;63;434;944;1150;}};                // Horiz Params.
}};

                

//
// GoldFish Parameters (Civic) (1 Meg)
// (640x480 Resolution)

resource 'node' (3135, "_sVidParms_Civic_viGFNTSCFFa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;226;1186;1331;}};                    // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;184;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;184;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;184;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;184;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;184;4;}};                                  // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;369;5;}};                                  // Framebuffer Params.
  words{{1088;576;32;1151;63;370;1010;1150;}};               // Horiz Params.
}};

//
// GoldFish Parameters (Civic) (2 Meg)
// (640x480 Resolution)

resource 'node' (3136, "_sVidParms_Civic_viGFNTSCFFb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.

  bytes{{sRsrc_Vid_Civic_viNTSCFFa;sRsrc_Vid_Civic_viNTSCFFb;}};  // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALSTa;sRsrc_Vid_Civic_viPALSTb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_NTSCFFConva;sRsrc_Vid_Civic_PALSTConva;}}; // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;226;1186;1331;}};                    // Vert. Params.
  words{{defmBounds_BNTSCFF-1;}};                            // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;32;0;0;184;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;32;0;0;184;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;32;0;0;184;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;32;0;0;184;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;185;505;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;40;0;0;369;20;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;370;1010;1150;}};               // Horiz Params.

// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;369;5;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;370;1010;1150;}};               // Horiz Params.
}};


//                
// GoldFish Parameters (Civic) (1 Meg)
// (768x576 Resolution)
resource 'node' (3145, "_sVidParms_Civic_viGFPALFFa") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FifthVidMode;}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;130;1282;1331;}};                    // Vert. Params.
  words{{defmBounds_BPALFF-1;}};                             // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;152;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;152;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;152;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;152;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;152;4;}};                                  // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 32bpp Params (Only used for getting the 2x timing for video-in)
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;305;5;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;306;1074;1150;}};               // Horiz Params.
}};

//                
// GoldFish Parameters (Civic) (2 Meg)
// (768x576 Resolution)
resource 'node' (3146, "_sVidParms_Civic_viGFPALFFb") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{SixthVidMode;FifthVidMode;}};                      // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                					         // NTSC 1Meg, 2Meg spIDs
  bytes{{sRsrc_Vid_Civic_viPALFFa;sRsrc_Vid_Civic_viPALFFb;}};    // PAL 1Meg, 2Meg spIDs
  bytes{{0;sRsrc_Vid_Civic_PALFFConva;}};                   // Convolution NTSC, PAL spID's.

  bytes{{1;2;1;0;}};                                         // Endeavor M,N,Clk, ScanCtl.
  longs{{$03b8170;}};										 // Clifton's W Parameter
  bytes{{25;1;}};											 // Clifton's W Size, Clk
  longs{{$164860;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{22;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1334;1332;4;43;130;1282;1331;}};                    // Vert. Params.
  words{{defmBounds_BPALFF-1;}};                             // Number of rows.

// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;26;0;0;152;16;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;26;0;0;152;17;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;26;0;0;152;18;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;26;0;0;152;19;}};                                 // Framebuffer Params.
  words{{544;288;16;575;31;153;537;574;}};                   // Horiz Params.
                
// 16bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;52;0;0;305;20;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;306;1074;1150;}};               // Horiz Params.
                
// 32bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;104;0;0;305;5;}};                                 // Framebuffer Params.
  words{{1088;576;32;1151;63;306;1074;1150;}};               // Horiz Params.
}};


//
// 19" Video-In Parameters (Civic) (1 Meg)
//
resource 'node' (3105, "_sVidParms_Civic_vi19a") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FourthVidMode;FourthVidMode;}};                     // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{44;63;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$4741b0;}};										 // Clifton's W Parameter
  bytes{{23;1;}};										     // Clifton's W Size, Clk
  longs{{$5dc0c0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{24;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1608;1606;4;34;64;(1600+0);1603;}};                 // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;128;16;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
        
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;128;17;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;128;18;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{1;36;0;0;128;3;}};                                  // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
}};

//
// 19" Video-In Parameters (Civic) (2 Meg)
//
resource 'node' (3106, "_sVidParms_Civic_vi19b") {{
  blocksize{};                                               // block size

// Misc Params
//
  bytes{{FifthVidMode;FourthVidMode;}};                       // Max Graphics Mode, Max Video-in Mode
  bytes{{1;0;}};                                             // Misc Flags.
  bytes{{0;0;}};                                             // NTSC 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // PAL 1Meg, 2Meg spIDs
  bytes{{0;0;}};                                             // Convolution NTSC, PAL spID's.

  bytes{{44;63;1;0;}};                                       // Endeavor M,N,Clk, ScanCtl.
  longs{{$4741b0;}};										 // Clifton's W Parameter
  bytes{{23;1;}};										     // Clifton's W Size, Clk
  longs{{$5dc0c0;}};										 // Puma's W Parameter							<LW14> #PUMA
  bytes{{24;1;}};											 // Puma's W Size, Clk							<LW14> #PUMA

  words{{1608;1606;4;34;64;(1600+0);1603;}};                 // Vert. Params.
  words{{defmBounds_B19-1;}};                                // Number of rows.
                
// 1bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{3;16;0;0;128;16;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
        
// 2bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{2;8;0;0;128;17;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.

// 4bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{1;16;0;0;128;18;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
                
// 8bpp Params
//
  words{{0;}};												 // Bus Size (0 = video-in)
  words{{0;36;0;0;128;19;}};                                 // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.

// 16bpp Params
//
  words{{1;}};												 // Bus Size (0 = video-in)
  words{{0;80;0;0;128;4;}};                                  // Framebuffer Params.
  words{{616;332;24;663;47;129;641;662;}};                   // Horiz Params.
}};

