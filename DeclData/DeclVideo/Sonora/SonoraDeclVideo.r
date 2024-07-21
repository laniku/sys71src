/*
	File:		SonoraDeclVideo.r

	Contains:	Video monitor/timing for Sonora.

	Copyright:	© 1989-1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	  <SM16>	12/14/93	PN		Obsolete the CPUMac020 resources.
	  <SM15>	 10/6/93	RC		Change the name of the PDM video to "Built-In DRAM Video" - as
									per Product Marketing's request.
	  <SM14>	09-23-93	jmp		Commented out the PDM-specific video name directory to eliminate
									the list of family modes for the RAM allocation stuff (which
									isn’t happening anyway).
	  <SM13>	08-06-93	jmp		More completely filled out the timingInfo list.
	  <SM12>	08-03-93	jmp		Began cleaning up the support for dynamically allocating RAM in
									PDM for video.
		<11>	 6/22/93	IH		Update timing directory to include a timing mode for the sonora
									multi sync functional sResource.
		<10>	  6/1/93	IH		Added video timing directory
	   <SM9>	04-07-93	jmp		Added initial low-level support for the Display Manager.
	   <SM8>	04-01-93	jmp		Added support for the fact that PDM uses RAM instead of VRAM for
									by adding a 1bpp-only mode to all the supported displays, as
									well as added a new video-name directory as a (hopefully)
									temporary interface to this feature.
	   <SM7>	  3/9/93	jmp		Changed the name of the PDM board sRsrc to “AMIC Built-in
									Video.”
	   <SM6>	  3/5/93	CCH		Made some mods to support Mace on Sonora/PDM.
	   <SM5>	  3/4/93	dwc		Added DeclDataPDMMace definition for PDM ENET.
	   <SM4>	 11/2/92	kc		Change ObjDir to RsrcDir.
	   <SM3>	10-17-92	jmp		Added initial support for PDM.
	   <SM2>	10-17-92	jmp		Needed to the change the 'decl' IDs of various externally
									referenced components.
	   <SM1>	 10/6/92	GDW		New location for ROMLink tool.
*/

//===================================================================
// Includes
//===================================================================

#include "Types.r"

#define	_NO_SINL_ // Don’t need 'SINL' resource here.
#include "ROMLink.r"
#undef	_NO_SINL_

#include "DepVideoEqu.r"
#include "HardwarePrivateEqu.r"
#include "InternalOnlyEqu.r"
#include "Quickdraw.r"

// This #define's are a stopgap measure for now.
#define firstVidMode  0x80
#define secondVidMode 0x81
#define thirdVidMode  0x82
#define fourthVidMode 0x83
#define fifthVidMode  0x84
#define sixthVidMode  0x85

//-------------------------------------------------------------
// Driver Directory
//-------------------------------------------------------------
resource 'ddir' (1770, "_VidDrvrDirSonora") {{
  sMacOS68020, l{"_sSonoraDrvrDir"};
}};

resource 'node' (575, "_sSonoraDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{70};}}};
}};

resource 'srsc' (1577, "_sRsrc_Sonora_Mace") {{
  sRsrcType,        l{"_NetPDMMace"};			// Network type descriptor
  sRsrcName,        l{"_NetPDMMaceName"};		// offset to name string
  sRsrcDrvrDir,     l{"_NetPDMMaceDrvrDir"};	// offset to driver directory
  sRsrcFlags,       d{0};						// don't open this device at start
  sRsrcHWDevId,     d{2};						// the second of many onboard Ethernet chips
}};

resource 'ddir' (1786, "_NetPDMMaceDrvrDir") {{
  sMacOS68020, l{"_sPDMMaceDrvrDir"};
}};

resource 'node' (561, "_sPDMMaceDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataPDMMace.rsrc"};
				   type{'decl'};
				     id{1};}}};
}};

//=====================================================================
// Primary Init record
//=====================================================================

resource 'node' (421, "_sSonoraPrimaryInit") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{80};}}};
}};

//-------------------------------------------------------------
// Resource Types
//-------------------------------------------------------------

resource 'styp' (1615, "_VideoTypeSonora") 	{CatDisplay, TypVideo, DrSwApple, DrHwSonora};
resource 'styp' (1633, "_NetPDMMace")  		{CatNetwork, TypEthernet, DrSwApple, DrHwMace};

//-------------------------------------------------------------
// Resource Names
//-------------------------------------------------------------

resource 'cstr' (1670, "_VideoNameSonora") {"Display_Video_Apple_Sonora"};
resource 'cstr' (1686, "_NetPDMMaceName")  {"Network_Ethernet_Apple_PDM_Mace"};

resource 'long' (2318, "_MinorLength_Sonora_FP")  {MinorLength_Sonora_FP};
resource 'long' (2320, "_MinorLength_Sonora_FPa") {MinorLength_Sonora_FPa};
resource 'long' (2325, "_MinorLength_Sonora_FPb") {MinorLength_Sonora_FPb};
resource 'long' (2330, "_MinorLength_Sonora_FPc") {MinorLength_Sonora_FPc};
resource 'long' (2332, "_MinorLength_Sonora_GS")  {MinorLength_Sonora_GS};
resource 'long' (2335, "_MinorLength_Sonora_GSa") {MinorLength_Sonora_GSa};
resource 'long' (2340, "_MinorLength_Sonora_GSb") {MinorLength_Sonora_GSb};
resource 'long' (2345, "_MinorLength_Sonora_GS560a") {MinorLength_Sonora_GSa};
resource 'long' (2350, "_MinorLength_Sonora_GS560b") {MinorLength_Sonora_GSb};
resource 'long' (2352, "_MinorLength_Sonora_HR")  {MinorLength_Sonora_HR};
resource 'long' (2355, "_MinorLength_Sonora_HRa") {MinorLength_Sonora_HRa};
resource 'long' (2360, "_MinorLength_Sonora_HRb") {MinorLength_Sonora_HRb};
resource 'long' (2365, "_MinorLength_Sonora_HRc") {MinorLength_Sonora_HRc};
resource 'long' (2370, "_MinorLength_Sonora_HR400a") {MinorLength_Sonora_HR400a};
resource 'long' (2375, "_MinorLength_Sonora_HR400b") {MinorLength_Sonora_HR400b};
resource 'long' (2378, "_MinorLength_Sonora_GF")  {MinorLength_Sonora_GF};
resource 'long' (2380, "_MinorLength_Sonora_GFa") {MinorLength_Sonora_GFa};
resource 'long' (2385, "_MinorLength_Sonora_GFb") {MinorLength_Sonora_GFb};

//-------------------------------------------------------------
// Board resources
//-------------------------------------------------------------

resource 'boar' (325, "_sRsrc_BdVail") {{
  sRsrcType,        a{"_BoardType"}; 
  sRsrcName,        c{"Macintosh AA Built-In Video"};
  sRsrcIcon,        a{"_VidICONVail"}; 
  BoardId,          d{VailBoardID}; 
  PrimaryInit,      a{"_sSonoraPrimaryInit"}; 
  VendorInfo,       a{"_VendorInfo"}; 
  SecondaryInit,    a{"_sSecondaryInit"}; 
  sRsrcVidNames,    l{"_SonoraVidNameDir"}; 
  sVidParmDir,      l{"_VidParmDir_Sonora"}; 
}};

resource 'boar' (345, "_sRsrc_BdPDM") {{
  sRsrcType,        a{"_BoardType"}; 
  sRsrcName,        c{"Built-In DRAM Video"};												// <sm 15>
  sRsrcIcon,        a{"_VidICONVail"}; 
  BoardId,          d{PDMBrdID}; 
  VendorInfo,       a{"_VendorInfo"}; 
  SecondaryInit,    a{"_sSecondaryInit"}; 
//sRsrcVidNames,    l{"_PDMVidNameDir"}; 
  sRsrcVidNames,    l{"_SonoraVidNameDir"}; 
  sVidAuxParams,    l{"_SonoraVidAuxParamsDir_Sonora"}; 
  sVidParmDir,      l{"_VidParmDir_Sonora"}; 
}};
                
//-------------------------------------------------------------
//
//           Sonora sRsrc Directory
//
//           Only CPUs possessing the Sonora or Sonora-like
//				functionality should be placed in this
//				directory
//
//-------------------------------------------------------------

resource 'sdir' (155, "_sRsrcSonoraDir") {{

  sRsrc_BdVail,     l{"_sRsrc_BdVail"};							// Board sResources
  sRsrc_BdPDM,      l{"_sRsrc_BdPDM"};
                
// Functional sRsrcs for Sonora built-in video.
//

  sRsrc_Vid_Sonora_FP,  l{"_sRsrc_Vid_Sonora_FP"};				// Full-Page (1,PDM)
  sRsrc_Vid_Sonora_FPa, l{"_sRsrc_Vid_Sonora_FPa"};				// Full-Page (1,2)
  sRsrc_Vid_Sonora_FPb, l{"_sRsrc_Vid_Sonora_FPb"};				// Full-Page (1,2,4)
  sRsrc_Vid_Sonora_FPc, l{"_sRsrc_Vid_Sonora_FPc"};				// Full-Page (1,2,4,8)
                
  sRsrc_Vid_Sonora_GS,  l{"_sRsrc_Vid_Sonora_GS"};				// Rubik (1,PDM)
  sRsrc_Vid_Sonora_GSa, l{"_sRsrc_Vid_Sonora_GSa"};				// Rubik (1,2,4,8)
  sRsrc_Vid_Sonora_GSb, l{"_sRsrc_Vid_Sonora_GSb"};				// Rubik (1,2,4,8,16)
  sRsrc_Vid_Sonora_GSM, l{"_sRsrc_Vid_Sonora_GSb"};				// GSM=GSb
                
  sRsrc_Vid_Sonora_GS560a, l{"_sRsrc_Vid_Sonora_GS560a"};		// Rubik-560 (1,2,4,8)
  sRsrc_Vid_Sonora_GS560b, l{"_sRsrc_Vid_Sonora_GS560b"};		// Rubik-560 (1,2,4,8,16)
                
  sRsrc_Vid_Sonora_RGBFP,  l{"_sRsrc_Vid_Sonora_RGBFP"};		// RGB Full-Page (1,PDM)
  sRsrc_Vid_Sonora_RGBFPa, l{"_sRsrc_Vid_Sonora_RGBFPa"};		// RGB Full-Page (1,2)
  sRsrc_Vid_Sonora_RGBFPb, l{"_sRsrc_Vid_Sonora_RGBFPb"};		// RGB Full-Page (1,2,4)
  sRsrc_Vid_Sonora_RGBFPc, l{"_sRsrc_Vid_Sonora_RGBFPc"};		// RGB Full-Page (1,2,4,8)
                
  sRsrc_Vid_Sonora_HR,  l{"_sRsrc_Vid_Sonora_HR"};				// HiRes (1,PDM)
  sRsrc_Vid_Sonora_HRa, l{"_sRsrc_Vid_Sonora_HRa"};				// HiRes (1,2,4)
  sRsrc_Vid_Sonora_HRb, l{"_sRsrc_Vid_Sonora_HRb"};				// HiRes (1,2,4,8)
  sRsrc_Vid_Sonora_HRc, l{"_sRsrc_Vid_Sonora_HRc"};				// HiRes (1,2,4,8,16)
  sRsrc_Vid_Sonora_MSB1,l{"_sRsrc_Vid_Sonora_HRc"};				// MSB1=HRc
  
  sRsrc_Vid_Sonora_HR400a, l{"_sRsrc_Vid_Sonora_HR400a"};		// HiRes-400 (1,2,4,8)
  sRsrc_Vid_Sonora_HR400b, l{"_sRsrc_Vid_Sonora_HR400b"};		// HiRes-400 (1,2,4,8,16)
                
  sRsrc_Vid_Sonora_VGA,  l{"_sRsrc_Vid_Sonora_VGA"};			// VGA (1,PDM)
  sRsrc_Vid_Sonora_VGAa, l{"_sRsrc_Vid_Sonora_VGAa"};			// VGA (1,2,4)
  sRsrc_Vid_Sonora_VGAb, l{"_sRsrc_Vid_Sonora_VGAb"};			// VGA (1,2,4,8)
  sRsrc_Vid_Sonora_VGAc, l{"_sRsrc_Vid_Sonora_VGAc"};			// VGA (1,2,4,8,16)
                
  sRsrc_Vid_Sonora_GF,  l{"_sRsrc_Vid_Sonora_GF"};				// GoldFish (1,PDM)
  sRsrc_Vid_Sonora_GFa, l{"_sRsrc_Vid_Sonora_GFa"};				// GoldFish (1,2)
  sRsrc_Vid_Sonora_GFb, l{"_sRsrc_Vid_Sonora_GFb"};				// GoldFish (1,2,4,8)
  sRsrc_Vid_Sonora_MSB2, l{"_sRsrc_Vid_Sonora_GFb"};			// MSB1=MSB2=GFb

// Miscellaneous sRsrcs for Sonora.
// 
  sRsrc_Sonora_Mace,	l{"_sRsrc_Sonora_Mace"};				// Sonora Mace sRrsc.
  sRsrc_CPUMac030,  	a{"_sRsrc_CPUMac030"};					// CPU sRsrc.
  sRsrc_Sonic,			a{"_sRsrc_Sonic"};						// Sonic sRrsc.

}};

resource 'list' (2745, "_VidParmDir_Sonora") {{

  sRsrc_Vid_Sonora_FP,  l{"_sVidParms_Sonora_FP"};						// Portrait
  sRsrc_Vid_Sonora_FPa, l{"_sVidParms_Sonora_FP"};
  sRsrc_Vid_Sonora_FPb, l{"_sVidParms_Sonora_FP"}; 
  sRsrc_Vid_Sonora_FPc, l{"_sVidParms_Sonora_FP"}; 
                
  sRsrc_Vid_Sonora_GS,  l{"_sVidParms_Sonora_GS"};						// Rubik
  sRsrc_Vid_Sonora_GSa, l{"_sVidParms_Sonora_GS"};
  sRsrc_Vid_Sonora_GSb, l{"_sVidParms_Sonora_GS"}; 
  sRsrc_Vid_Sonora_GSM, l{"_sVidParms_Sonora_GS"}; 

  sRsrc_Vid_Sonora_GS560a, l{"_sVidParms_Sonora_GS560"};				// Rubik-560
  sRsrc_Vid_Sonora_GS560b, l{"_sVidParms_Sonora_GS560"}; 
                
  sRsrc_Vid_Sonora_RGBFP,  l{"_sVidParms_Sonora_FP"};					// RGB Portrait
  sRsrc_Vid_Sonora_RGBFPa, l{"_sVidParms_Sonora_FP"};
  sRsrc_Vid_Sonora_RGBFPb, l{"_sVidParms_Sonora_FP"}; 
  sRsrc_Vid_Sonora_RGBFPc, l{"_sVidParms_Sonora_FP"}; 

  sRsrc_Vid_Sonora_HR,  l{"_sVidParms_Sonora_HR"};						// Hi-Res
  sRsrc_Vid_Sonora_HRa, l{"_sVidParms_Sonora_HR"};
  sRsrc_Vid_Sonora_HRb, l{"_sVidParms_Sonora_HR"}; 
  sRsrc_Vid_Sonora_HRc, l{"_sVidParms_Sonora_HR"}; 
  sRsrc_Vid_Sonora_MSB1, l{"_sVidParms_Sonora_HR"}; 					// MSB1=HR
                
  sRsrc_Vid_Sonora_HR400a, l{"_sVidParms_Sonora_HR400"};				// Hi-Res 400
  sRsrc_Vid_Sonora_HR400b, l{"_sVidParms_Sonora_HR400"}; 
                
  sRsrc_Vid_Sonora_VGA,  l{"_sVidParms_Sonora_VGA"};					// VGA
  sRsrc_Vid_Sonora_VGAa, l{"_sVidParms_Sonora_VGA"};
  sRsrc_Vid_Sonora_VGAb, l{"_sVidParms_Sonora_VGA"}; 
  sRsrc_Vid_Sonora_VGAc, l{"_sVidParms_Sonora_VGA"}; 
                
  sRsrc_Vid_Sonora_GF,  l{"_sVidParms_Sonora_GF"};						// GoldFish
  sRsrc_Vid_Sonora_GFa, l{"_sVidParms_Sonora_GF"};
  sRsrc_Vid_Sonora_GFb, l{"_sVidParms_Sonora_GF"};
  sRsrc_Vid_Sonora_MSB2, l{"_sVidParms_Sonora_GF"}; 					// MSB2=GF
}};

//===================================================================
// Video name parameters directory
//===================================================================

resource 'vdir' (350, "_SonoraVidNameDir") {{

  sRsrc_Vid_Sonora_FP,  a{"_sName_FP"}; 
  sRsrc_Vid_Sonora_FPa, a{"_sName_FP"}; 
  sRsrc_Vid_Sonora_FPb, a{"_sName_FP"}; 
  sRsrc_Vid_Sonora_FPc, a{"_sName_FP"}; 
                
  sRsrc_Vid_Sonora_GS,  a{"_sName_GS"}; 
  sRsrc_Vid_Sonora_GSa, a{"_sName_GS"}; 
  sRsrc_Vid_Sonora_GSb, a{"_sName_GS"}; 
  sRsrc_Vid_Sonora_GSM, a{"_sName_GS"}; 
                
  sRsrc_Vid_Sonora_GS560a, a{"_sName_GS560"}; 
  sRsrc_Vid_Sonora_GS560b, a{"_sName_GS560"}; 
                
  sRsrc_Vid_Sonora_RGBFP,  a{"_sName_RGBFP"}; 
  sRsrc_Vid_Sonora_RGBFPa, a{"_sName_RGBFP"}; 
  sRsrc_Vid_Sonora_RGBFPb, a{"_sName_RGBFP"}; 
  sRsrc_Vid_Sonora_RGBFPc, a{"_sName_RGBFP"}; 

  sRsrc_Vid_Sonora_HR,  a{"_sName_HR"}; 
  sRsrc_Vid_Sonora_HRa, a{"_sName_HR"}; 
  sRsrc_Vid_Sonora_HRb, a{"_sName_HR"}; 
  sRsrc_Vid_Sonora_HRc, a{"_sName_HR"};
  sRsrc_Vid_Sonora_MSB1, a{"_sName_HR"};
                
  sRsrc_Vid_Sonora_HR400a, a{"_sName_HR400"}; 
  sRsrc_Vid_Sonora_HR400b, a{"_sName_HR400"}; 
                
  sRsrc_Vid_Sonora_VGA,  a{"_sName_VGA"}; 
  sRsrc_Vid_Sonora_VGAa, a{"_sName_VGA"}; 
  sRsrc_Vid_Sonora_VGAb, a{"_sName_VGA"}; 
  sRsrc_Vid_Sonora_VGAc, a{"_sName_VGA"}; 
                
  sRsrc_Vid_Sonora_GF,  a{"_sName_GF"}; 
  sRsrc_Vid_Sonora_GFa, a{"_sName_GF"}; 
  sRsrc_Vid_Sonora_GFb, a{"_sName_GF"};
  sRsrc_Vid_Sonora_MSB2,a{"_sName_GF"};
                              
}};

resource 'vdir' (352, "_PDMVidNameDir") {{

  sRsrc_Vid_Sonora_FP,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_FPc, a{"_sName_8bppG"}; 
                
  sRsrc_Vid_Sonora_GS,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_GSa, a{"_sName_8bpp"}; 
  sRsrc_Vid_Sonora_GSb, a{"_sName16bpp"}; 
  sRsrc_Vid_Sonora_GSM, a{"_sName_GS"}; 
                
  sRsrc_Vid_Sonora_RGBFP,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_RGBFPc, a{"_sName_8bpp"}; 

  sRsrc_Vid_Sonora_HR,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_HRb, a{"_sName_8bpp"}; 
  sRsrc_Vid_Sonora_HRc, a{"_sName16bpp"};
  sRsrc_Vid_Sonora_MSB1,a{"_sName_HR"};
                
  sRsrc_Vid_Sonora_VGA,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_VGAb, a{"_sName_8bpp"}; 
  sRsrc_Vid_Sonora_VGAc, a{"_sName16bpp"}; 
                
  sRsrc_Vid_Sonora_GF,  a{"_sName_1bpp"}; 
  sRsrc_Vid_Sonora_GFb, a{"_sName_8bpp"};
  sRsrc_Vid_Sonora_MSB2,a{"_sName_GF"};
                              
}};

resource 'vmna' (550, "_sName_1bpp")     		{170, "Black & White Only"};
resource 'vmna' (555, "_sName_8bpp")     		{170, "256 Colors or Grays"};
resource 'vmna' (560, "_sName_8bppG")     		{170, "256 Grays"};
resource 'vmna' (565, "_sName16bpp")     		{170, "Thousands of Colors"};

//===================================================================
// Supported video modes
//===================================================================

resource 'srsc' (1013, "_sRsrc_Vid_Sonora_FP") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FP"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters

}};

//----------------------------------

resource 'srsc' (1015, "_sRsrc_Vid_Sonora_FPa") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPa"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters

}};

//----------------------------------

resource 'srsc' (1020, "_sRsrc_Vid_Sonora_FPb") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPb"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMFP"};					// offset to FourBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1025, "_sRsrc_Vid_Sonora_FPc") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPc"}; 

  sGammaDir,        a{"_GammaDir_FP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMFP"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMFP"};					// offset to EightBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1027, "_sRsrc_Vid_Sonora_GS") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GS"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
  FirstVidMode,     a{"_OBMGS"};					// offset to OneBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1030, "_sRsrc_Vid_Sonora_GSa") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GSa"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
  FirstVidMode,     a{"_OBMGS"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGS"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMGS"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMGS"};					// offset to EightBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1035, "_sRsrc_Vid_Sonora_GSb") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GSb"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
  FirstVidMode,     a{"_OBMGS"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGS"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMGS"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMGS"};					// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BMGS"};					// offset to SixteenBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1040, "_sRsrc_Vid_Sonora_GS560a") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GS560a"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
  FirstVidMode,     a{"_OBMGS560"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGS560"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMGS560"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMGS560"};					// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1045, "_sRsrc_Vid_Sonora_GS560b") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GS560b"}; 

  sGammaDir,        a{"_GammaDir_GS"}; 
                
  FirstVidMode,     a{"_OBMGS560"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGS560"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMGS560"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMGS560"};					// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BMGS560"};				// offset to SixteenBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1047, "_sRsrc_Vid_Sonora_RGBFP") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FP"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters

}};

//----------------------------------

resource 'srsc' (1050, "_sRsrc_Vid_Sonora_RGBFPa") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPa"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters

}};


//----------------------------------

resource 'srsc' (1055, "_sRsrc_Vid_Sonora_RGBFPb") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPb"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMFP"};					// offset to FourBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1060, "_sRsrc_Vid_Sonora_RGBFPc") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_FPc"}; 

  sGammaDir,        a{"_GammaDir_RGBFP"}; 
                
  FirstVidMode,     a{"_OBMFP"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMFP"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMFP"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMFP"};					// offset to EightBitMode parameters
                
}};

//----------------------------------

resource 'node' (1062, "_sRsrc_Vid_Sonora_HR") {{
  include{l{"_sRsrc_Vid_Sonora_VGA"}};
}};

resource 'srsc' (1064, "_sRsrc_Vid_Sonora_VGA") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HR"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR"};					// offset to OneBitMode parameters

}};


//----------------------------------

resource 'node' (1065, "_sRsrc_Vid_Sonora_HRa") {{
  include{l{"_sRsrc_Vid_Sonora_VGAa"}};
}};

resource 'srsc' (1070, "_sRsrc_Vid_Sonora_VGAa") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HRa"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMHR"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMHR"};					// offset to FourBitMode parameters

}};


//----------------------------------

resource 'node' (1075, "_sRsrc_Vid_Sonora_HRb") {{
  include{l{"_sRsrc_Vid_Sonora_VGAb"}};
}};

resource 'srsc' (1080, "_sRsrc_Vid_Sonora_VGAb") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HRb"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMHR"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMHR"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMHR"};					// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'node' (1085, "_sRsrc_Vid_Sonora_HRc") {{
  include{l{"_sRsrc_Vid_Sonora_VGAc"}};
}};

resource 'node' (1088, "_sRsrc_Vid_Sonora_MS") {{
  include{l{"_sRsrc_Vid_Sonora_VGAc"}};
}};

resource 'srsc' (1090, "_sRsrc_Vid_Sonora_VGAc") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HRc"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMHR"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMHR"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMHR"};					// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BMHR"};					// offset to SixteenBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1095, "_sRsrc_Vid_Sonora_HR400a") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HR400a"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR400"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMHR400"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMHR400"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMHR400"};					// offset to EightBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1100, "_sRsrc_Vid_Sonora_HR400b") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_HR400b"}; 

  sGammaDir,        a{"_GammaDir_HR"}; 
                
  FirstVidMode,     a{"_OBMHR400"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMHR400"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMHR400"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMHR400"};					// offset to EightBitMode parameters
  FifthVidMode,     a{"_D16BMHR400"};				// offset to SixteenBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1102, "_sRsrc_Vid_Sonora_GF") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GF"}; 

  sGammaDir,        a{"_GammaDir_GF"}; 
                
  FirstVidMode,     a{"_OBMGF"};					// offset to OneBitMode parameters
                
}};

//----------------------------------

resource 'srsc' (1105, "_sRsrc_Vid_Sonora_GFa") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GFa"}; 

  sGammaDir,        a{"_GammaDir_GF"}; 
                
  FirstVidMode,     a{"_OBMGF"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGF"};					// offset to TwoBitMode parameters
                
}};


//----------------------------------

resource 'srsc' (1110, "_sRsrc_Vid_Sonora_GFb") {{
  sRsrcType,        l{"_VideoTypeSonora"}; 
  sRsrcName,        l{"_VideoNameSonora"}; 
  sRsrcDrvrDir,     l{"_VidDrvrDirSonora"}; 
  sRsrcFlags,       d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))}; // 32-bit base address for frame buffer
  sRsrcHWDevID,     d{1}; 

  MinorBaseOS,      a{"_MinorBaseSonora"}; 
  MinorLength,      l{"_MinorLength_Sonora_GFb"}; 

  sGammaDir,        a{"_GammaDir_GF"}; 
                
  FirstVidMode,     a{"_OBMGF"};					// offset to OneBitMode parameters
  SecondVidMode,    a{"_TBMGF"};					// offset to TwoBitMode parameters
  ThirdVidMode,     a{"_FBMGF"};					// offset to FourBitMode parameters
  FourthVidMode,    a{"_EBMGF"};					// offset to EightBitMode parameters
                
}};


//===================================================================
// Video data parameters
//===================================================================

//
// Portrait Paramters (Sonora)
//
resource 'node' (2845, "_sVidParms_Sonora_FP") {{
  blocksize{};                                               // block size
                
  bytes{{53;29;1;0;}};                                       // Omega-1 N,D,P values.
  bytes{{53;29;1;0;}};                                       // Omega-2 N,D,P values.
  bytes{{1;0;}};                                             // Monitor code value.
  bytes{{SecondVidMode;ThirdVidMode;FourthVidMode;0;}};      // MaxModes: 256,512,768.
  bytes{{FourthVidMode;0;FirstVidMode;0;}};       			 // MaxModes: 600,300,68.
  words{{defmBounds_BFP-1;}};                                // Rows.

// Depth Params
//
  words{{(OBMFPRB/4)-1;}};
  words{{(TBMFPRB/4)-1;}};
  words{{(FBMFPRB/4)-1;}};
  words{{(EBMFPRB/4)-1;}};
}};



//
// Rubik Parameters (Sonora)
//
resource 'node' (2850, "_sVidParms_Sonora_GS") {{
  blocksize{};                                               // block size
            
  bytes{{44;44;2;0;}};                                       // Omega-1 N,D,P values.
  bytes{{0;0;2;0;}};                                         // Omega-2 N,D,P values.
  bytes{{2;0;}};                                             // Monitor code value.
  bytes{{FourthVidMode;FifthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  bytes{{FifthVidMode;FourthVidMode;FirstVidMode;0;}};       // MaxModes: 600,300,68.
  words{{defmBounds_BGS-1;}};                                // Rows.

// Depth Params
//
  words{{(OBMGSRB/4)-1;}};
  words{{(TBMGSRB/4)-1;}};
  words{{(FBMGSRB/4)-1;}};
  words{{(EBMGSRB/4)-1;}};
  words{{(D16BMGSRB/4)-1;}};
}};


                        
//
// Rubik Parameters, 560 mode (Sonora)
//
resource 'node' (2855, "_sVidParms_Sonora_GS560") {{
  blocksize{};                                               // block size
            
  bytes{{44;40;2;0;}};                                       // Omega-1 N,D,P values.
  bytes{{54;49;2;0;}};                                       // Omega-2 N,D,P values.
  bytes{{10;0;}};                                            // Monitor code value.
  bytes{{FourthVidMode;FifthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  bytes{{FourthVidMode;FifthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  words{{defmBounds_BGS560-1;}};                             // Rows.

// Depth Params
//
  words{{(OBMGS560RB/4)-1;}};
  words{{(TBMGS560RB/4)-1;}};
  words{{(FBMGS560RB/4)-1;}};
  words{{(EBMGS560RB/4)-1;}};
  words{{(D16BMGS560RB/4)-1;}};
}};



//
// Hi-Res Parameters (Sonora)
//
resource 'node' (2860, "_sVidParms_Sonora_HR") {{
  blocksize{};                                               // block size
                
  bytes{{55;57;1;0;}};                                       // Omega-1 N,D,P values.
  bytes{{55;57;1;0;}};                                       // Omega-2 N,D,P values.
  bytes{{6;0;}};                                             // Monitor code value.
  bytes{{ThirdVidMode;FourthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  bytes{{FifthVidMode;FourthVidMode;FirstVidMode;0;}};       // MaxModes: 600,300,68.
  words{{defmBounds_BHR-1;}};                                // Rows.

// Depth Params
//
  words{{(OBMHRRB/4)-1;}};
  words{{(TBMHRRB/4)-1;}};
  words{{(FBMHRRB/4)-1;}};
  words{{(EBMHRRB/4)-1;}};
  words{{(D16BMHRRB/4)-1;}};
}};



//
// Hi-Res 400 Parameters (Sonora)
//
resource 'node' (2865, "_sVidParms_Sonora_HR400") {{
  blocksize{};                                               // block size
                
  bytes{{55;57;1;0;}};                                       // Omega-1 N,D,P values.
  bytes{{55;57;1;0;}};                                       // Omega-2 N,D,P values.
  bytes{{13;0;}};                                            // Monitor code value.
  bytes{{FourthVidMode;FifthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  bytes{{FourthVidMode;FifthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  words{{defmBounds_BHR400-1;}};                             // Rows.

// Depth Params
//
  words{{(OBMHRRB/4)-1;}};
  words{{(TBMHRRB/4)-1;}};
  words{{(FBMHRRB/4)-1;}};
  words{{(EBMHRRB/4)-1;}};
  words{{(D16BMHRRB/4)-1;}};
}};



//
// VGA Parameters (Sonora)
//
resource 'node' (2870, "_sVidParms_Sonora_VGA") {{
  blocksize{};                                               // block size
                
  bytes{{45;28;2;0;}};                                       // Omega-1 N,D,P values.
  bytes{{53;33;2;0;}};                                       // Omega-2 N,D,P values.
  bytes{{11;0;}};                                            // Monitor code value.
  bytes{{ThirdVidMode;FourthVidMode;FifthVidMode;0;}};       // MaxModes: 256,512,768.
  bytes{{FifthVidMode;FourthVidMode;FirstVidMode;0;}};       // MaxModes: 600,300,68.
  words{{defmBounds_BHR-1;}};                                // Rows.

// Depth Params
//
  words{{(OBMHRRB/4)-1;}};
  words{{(TBMHRRB/4)-1;}};
  words{{(FBMHRRB/4)-1;}};
  words{{(EBMHRRB/4)-1;}};
  words{{(D16BMHRRB/4)-1;}};
}};



//
// GoldFish Parameters (Sonora)
//
resource 'node' (2875, "_sVidParms_Sonora_GF") {{
  blocksize{};                                               // block size
                
  bytes{{53;29;1;0;}};                                       // Omega-1 N,D,P values.
  bytes{{53;29;1;0;}};                                       // Omega-2 N,D,P values.
  bytes{{9;0;}};                                             // Monitor code value.
  bytes{{SecondVidMode;FourthVidMode;FourthVidMode;0;}};     // MaxModes: 256,512,768.
  bytes{{FourthVidMode;0;FirstVidMode;0;}};       			 // MaxModes: 600,300,68.
  words{{defmBounds_BGF-1;}};                                // Rows.

// Depth Params
//
  words{{(OBMGFRB/4)-1;}};
  words{{(TBMGFRB/4)-1;}};
  words{{(FBMGFRB/4)-1;}};
  words{{(EBMGFRB/4)-1;}};
}};


//
// VidAux Parameters (Sonora)
//

resource 'list' (2670, "_SonoraVidAuxParamsDir_Sonora") {{

  sRsrc_Vid_Sonora_FP,  a{"_timingApple15"};							// Portrait
  sRsrc_Vid_Sonora_FPa, a{"_timingApple15"};
  sRsrc_Vid_Sonora_FPb, a{"_timingApple15"}; 
  sRsrc_Vid_Sonora_FPc, a{"_timingApple15"}; 
 
  sRsrc_Vid_Sonora_GS,  a{"_timingApple12"};							// Rubik
  sRsrc_Vid_Sonora_GSa, a{"_timingApple12"};
  sRsrc_Vid_Sonora_GSb, a{"_timingApple12"}; 
  sRsrc_Vid_Sonora_GSM, a{"_timingApple12"}; 

  sRsrc_Vid_Sonora_GS560a, a{"_timingApple12x"};						// Rubik-560
  sRsrc_Vid_Sonora_GS560b, a{"_timingApple12x"};
                
  sRsrc_Vid_Sonora_RGBFP,  a{"_timingApple15"};							// RGB Portrait
  sRsrc_Vid_Sonora_RGBFPa, a{"_timingApple15"};
  sRsrc_Vid_Sonora_RGBFPb, a{"_timingApple15"}; 
  sRsrc_Vid_Sonora_RGBFPc, a{"_timingApple15"}; 

  sRsrc_Vid_Sonora_HR,  a{"_timingApple13"};							// Hi-Res
  sRsrc_Vid_Sonora_HRa, a{"_timingApple13"};
  sRsrc_Vid_Sonora_HRb, a{"_timingApple13"}; 
  sRsrc_Vid_Sonora_HRc, a{"_timingApple13"}; 
  sRsrc_Vid_Sonora_MSB1, a{"_timingApple13"}; 							// MSB1=HR
  
  sRsrc_Vid_Sonora_HR400a, a{"_timingApple13x"};						// Hi-Res 400
  sRsrc_Vid_Sonora_HR400b, a{"_timingApple13x"};
                
  sRsrc_Vid_Sonora_VGA,  a{"_timingAppleVGA"};							// VGA
  sRsrc_Vid_Sonora_VGAa, a{"_timingAppleVGA"};							// VGA
  sRsrc_Vid_Sonora_VGAb, a{"_timingAppleVGA"}; 
  sRsrc_Vid_Sonora_VGAc, a{"_timingAppleVGA"}; 
                
  sRsrc_Vid_Sonora_GFa, a{"_timingApple16"};							// GoldFish
  sRsrc_Vid_Sonora_GFb, a{"_timingApple16"};
  sRsrc_Vid_Sonora_MSB2, a{"_timingApple16"}; 							// MSB1=HR
                
}};
