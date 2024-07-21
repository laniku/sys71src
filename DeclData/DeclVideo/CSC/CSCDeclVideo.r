/*
	File:		CSCDeclVideo.r

	Contains:	DeclData info for the CSC hardware.
	
	Written by:	Mike Puckett, January 12, 1993.

	Copyright:	© 1993-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM4>	 1/24/94	rab		Changed MinorLength_640x400b to MinorLength640x400 to match
									DepVideoEqu and sync with Kaos.
	   <SM3>	  1/4/94	PN		Add additional support for the rest of CSC panels from Kaos.
	   <SM2>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines
		 <1>	01-12-93	jmp		first checked in
*/

//-------------------------------------------------------------
// 				Includes/Equates
//-------------------------------------------------------------

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
//				CSC sRsrc Directory
//-------------------------------------------------------------

resource 'sdir' (6000, "_sRsrcCSCDir") {{

	sRsrc_BdEscher,			l{"_sRsrc_BdEscher"};							// Board sResources
	sRsrc_BdBlackBird,		l{"_sRsrc_BdBlackBird"};
	sRsrc_BdYeager,			l{"_sRsrc_BdYeager"};

// Functional sRsrcs for CSC-based video.
//
	sRsrc_Vid_CSC_C_S_TFT_399,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 $80
	sRsrc_Vid_CSC_C_S_TFT_480,	l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8 $81
	
	sRsrc_Vid_CSC_C_S_TFT_399a,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 $82
	sRsrc_Vid_CSC_C_S_TFT_480a, l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8
	
	sRsrc_Vid_CSC_C_D_STN_480,	l{"_sRsrc_Vid_CSC_640x480_STN"};				// 1,2,4,8 $85

	sRsrc_Vid_CSC_C_S_TFT_399b,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 
	sRsrc_Vid_CSC_C_S_TFT_480b,	l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8 
	
	sRsrc_Vid_CSC_C_S_TFT_399c,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 
	sRsrc_Vid_CSC_C_S_TFT_480c,	l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8 
	
	sRsrc_Vid_CSC_C_S_TFT_399d,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 
	sRsrc_Vid_CSC_C_S_TFT_480d,	l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8 
	
	sRsrc_Vid_CSC_G_D_STN_400,	l{"_sRsrc_Vid_CSC_640x400Gray"};				// 1,2,4
	sRsrc_Vid_CSC_G_S_TFT_400,	l{"_sRsrc_Vid_CSC_640x400Gray"};				// 1,2,4
	
	sRsrc_Vid_CSC_G_D_STN_480,	l{"_sRsrc_Vid_CSC_640x480Gray"};				// 1,2,4
	sRsrc_Vid_CSC_G_S_TFT_480,	l{"_sRsrc_Vid_CSC_640x480GrayTFT"};				// 1,2,4,8 
	
	sRsrc_Vid_CSC_C_S_TFT_399y,	l{"_sRsrc_Vid_CSC_640x399_TFT"};				// 1,2,4,8,16 
	sRsrc_Vid_CSC_C_S_TFT_480y,	l{"_sRsrc_Vid_CSC_640x480_TFT"};				// 1,2,4,8 
	
	sRsrc_Vid_CSC_G_D_STN_400y,	l{"_sRsrc_Vid_CSC_640x400Gray"};				// 1,2,4
	sRsrc_Vid_CSC_G_S_TFT_400y,	l{"_sRsrc_Vid_CSC_640x400Gray"};				// 1,2,4
	
	

// Miscellaneous sRsrcs for CSC.
// 
	sRsrc_CPUMac030,		a{"_sRsrc_CPUMac030"};						// CPU sRsrcs.
	sRsrc_CPUMac040,		a{"_sRsrc_CPUMacO40"};

	sRsrc_Sonic,			a{"_sRsrc_Sonic"};							// Sonic sRrsc.

}};

//-------------------------------------------------------------
// 				Board sRsrc List
//-------------------------------------------------------------

resource 'boar' (6010,"_sRsrc_BdEscher") {{
  	sRsrcType,	  a{"_BoardType"}; 
 	sRsrcName,    c{"CSC Built-in Video"};
 	BoardId,      d{EscherBoardID}; 
 	PrimaryInit,  a{"_sCSCPrimaryInit"}; 
 	VendorInfo,   a{"_VendorInfo"}; 
  	sRsrcVidNames,l{"_CSCVidNameDir"}; 
  	sVidParmDir,  l{"_VidParmDir_CSC"}; 
}};
resource 'boar' (6020,"_sRsrc_BdBlackBird") {{
  	sRsrcType,	  a{"_BoardType"}; 
 	sRsrcName,    c{"CSC-2 Built-In Video"};
 	BoardId,      d{BlackBirdBdID}; 
 	PrimaryInit,  a{"_sCSCPrimaryInit"}; 
 	VendorInfo,   a{"_VendorInfo"}; 
  	sRsrcVidNames,l{"_CSCVidNameDir"}; 
  	sVidParmDir,  l{"_VidParmDir_CSC"}; 
}};
resource 'boar' (6030,"_sRsrc_BdYeager") {{
  	sRsrcType,	  a{"_BoardType"}; 
 	sRsrcName,    c{"CSC-3 Built-In Video"};
 	BoardId,      d{YeagerBoardID}; 
 	PrimaryInit,  a{"_sCSCPrimaryInit"}; 
 	VendorInfo,   a{"_VendorInfo"}; 
  	sRsrcVidNames,l{"_CSCVidNameDir"}; 
  	sVidParmDir,  l{"_VidParmDir_CSC"}; 
}};

//-------------------------------------------------------------
//				Video Name Directory
//-------------------------------------------------------------

resource 'vdir' (6000, "_CSCVidNameDir") {{
	sRsrc_Vid_CSC_C_S_TFT_399, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480, l{"_sName_BigCLCD"};
	
	sRsrc_Vid_CSC_C_S_TFT_399a, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480a, l{"_sName_BigCLCD"};
	
	sRsrc_Vid_CSC_C_D_STN_480, l{"_sName_BigCLCD"};
	
	sRsrc_Vid_CSC_C_S_TFT_399b, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480b, l{"_sName_BigCLCD"};

	sRsrc_Vid_CSC_C_S_TFT_399c, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480c, l{"_sName_BigCLCD"};

	sRsrc_Vid_CSC_C_S_TFT_399d, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480d, l{"_sName_BigCLCD"};

	sRsrc_Vid_CSC_G_D_STN_400, l{"_sName_GrayLCD400"};
	sRsrc_Vid_CSC_G_S_TFT_400, l{"_sName_GrayLCD400"};

	sRsrc_Vid_CSC_G_D_STN_480, l{"_sName_GrayLCD480"};
	sRsrc_Vid_CSC_G_S_TFT_480, l{"_sName_GrayLCD480x"};
	
	sRsrc_Vid_CSC_C_S_TFT_399y, l{"_sName_ColorLCD"};
	sRsrc_Vid_CSC_C_S_TFT_480y, l{"_sName_BigCLCD"};
	
	sRsrc_Vid_CSC_G_D_STN_400y, l{"_sName_GrayLCD400"};
	sRsrc_Vid_CSC_G_S_TFT_400y, l{"_sName_GrayLCD400"};

}};
resource 'vmna' (6000,"_sName_ColorLCD")		{128, "640 x 400, Thousands of Colors"};
resource 'vmna' (6010,"_sName_BigCLCD")			{129, "640 x 480, 256 Colors or Grays"};
resource 'vmna' (6020,"_sName_GrayLCD400")		{130, "640 x 400, 16 Grays"};
resource 'vmna' (6030,"_sName_GrayLCD480")		{131, "640 x 480, 16 Grays"};
resource 'vmna' (6040,"_sName_GrayLCD480x")		{132, "640 x 480, 64 Grays"};


//-------------------------------------------------------------
//				Functional sResources
//-------------------------------------------------------------

resource 'srsc' (6000,"_sRsrc_Vid_CSC_640x399_TFT") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseCSC"};
	MinorLength,	l{"_MinorLength_640x400"};
	sGammaDir,		a{"_GammaDir_CSC_TFT"};
	
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack)|(1<<fDimMinAt1))};

	FirstVidMode,	a{"_OBMHR399"};
	SecondVidMode,	a{"_TBMHR399"};
	ThirdVidMode,	a{"_FBMHR399"};
	FourthVidMode,	a{"_EBMHR399"};
	FifthVidMode,	a{"_D16BMHR399"};
				
}};
				
//----------------------------------

resource 'srsc' (6010,"_sRsrc_Vid_CSC_640x480_TFT") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseCSC"};
	MinorLength,	l{"_MinorLength_640x480"};
	sGammaDir,		a{"_GammaDir_CSC_TFT"};
	
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack)|(1<<fDimMinAt1))};

	FirstVidMode,	a{"_OBMHR"};
	SecondVidMode,	a{"_TBMHR"};
	ThirdVidMode,	a{"_FBMHR"};
	FourthVidMode,	a{"_EBMHR"};
				
}};

//----------------------------------

resource 'srsc' (6020,"_sRsrc_Vid_CSC_640x480GrayTFT") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseCSC"};
	MinorLength,	l{"_MinorLength_640x480"};
	//sGammaDir,		a{"_GammaDir_CSC_Linear"};
			
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack)|(0<<fDimMinAt1))};

	FirstVidMode,	a{"_OBMHR"};
	SecondVidMode,	a{"_TBMHR"};
	ThirdVidMode,	a{"_FBMHR"};
	FourthVidMode,	a{"_EBMHR"};
				
}};

resource 'srsc' (6030,"_sRsrc_Vid_CSC_640x480_STN") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseCSC"};
	MinorLength,	l{"_MinorLength_640x480"};
	//sGammaDir,		a{"_GammaDir_CSC_Linear"};
				
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack))};

	FirstVidMode,	a{"_OBMHR"};
	SecondVidMode,	a{"_TBMHR"};
	ThirdVidMode,	a{"_FBMHR"};
	FourthVidMode,	a{"_EBMHR"};
				
}};
resource 'srsc' (6040,"_sRsrc_Vid_CSC_640x400Gray") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseGSC"};
	MinorLength,	l{"_MinorLengthGSCLCD"};
			
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack)|(0<<fDimMinAt1))};

	FirstVidMode,	a{"_OBMLCD"};
	SecondVidMode,	a{"_TBMLCD"};
	ThirdVidMode,	a{"_FBMLCD"};
				
}};
resource 'srsc' (6050,"_sRsrc_Vid_CSC_640x480Gray") {{

	sRsrcType,		l{"_VideoTypeCSC"};
	sRsrcName,		l{"_VideoNameCSC"};
	sRsrcDrvrDir,	l{"_VidDrvrDirCSC"};
	sRsrcFlags,		d{(0|(1<<f32BitMode)|(1<<fOpenAtStart))};
	sRsrcHWDevID,	d{1};

	MinorBaseOS,	l{"_MinorBaseCSC"};
	MinorLength,	l{"_MinorLengthGSC480"};
			
	sVidAttributes,	d{(0|(1<<fLCDScreen)|(1<<fBuiltInDisplay)|(1<<fDefaultColor)|(1<<fActiveBlack)|(0<<fDimMinAt1))};

	FirstVidMode,	a{"_OBMLCD480"};
	SecondVidMode,	a{"_TBMLCD480"};
	ThirdVidMode,	a{"_FBMLCD480"};
				
}};

//-------------------------------------------------------------
//				Resource Types
//-------------------------------------------------------------

resource 'styp' (6000, "_VideoTypeCSC")	{CatDisplay, TypVideo, DrSwApple, DrHwCSC};

//-------------------------------------------------------------
//				Resource Names
//-------------------------------------------------------------

resource 'cstr' (6000, "_VideoNameCSC")	{"Display_Video_Apple_CSC"};

//-------------------------------------------------------------
//				Driver Directory
//-------------------------------------------------------------

resource 'ddir' (6000, "_VidDrvrDirCSC") {{
  sMacOS68020, l{"_sCSCDrvrDir"};
}};

resource 'node' (6000,"_sCSCDrvrDir") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{6000};}}};
}};

//-------------------------------------------------------------
//				Minor/Major Bases/Lengths
//-------------------------------------------------------------

resource 'long' (6000,"_MinorBaseCSC") {defMinorBase};
resource 'long' (6005,"_MinorBaseGSC") {defMinorBase};

resource 'long' (6010,"_MinorLength_640x400") {MinorLength_640x400};
resource 'long' (6040,"_MinorLength_640x480") {MinorLength_640x480};
resource 'long' (6050,"_MinorLengthGSCLCD") {MinorLengthGSCLCD};
resource 'long' (6060,"_MinorLengthGSC480") {MinorLengthGSC480};

//-------------------------------------------------------------
//				Video Parameters
//-------------------------------------------------------------

resource 'list' (6000, "_VidParmDir_CSC") {{

	sRsrc_Vid_CSC_C_S_TFT_399,	l{"_sVidParams_CSC_C_S_TFT_399"};	// Color, TFT, Single-Drive, 640x480	[Sharp-Escher]
	sRsrc_Vid_CSC_C_S_TFT_480,	l{"_sVidParams_CSC_C_S_TFT_480"};
	
	sRsrc_Vid_CSC_C_S_TFT_399a,	l{"_sVidParams_CSC_C_S_TFT_399a"};	// Color, TFT, Single-Drive, 640x480	[Sharp]
	sRsrc_Vid_CSC_C_S_TFT_480a,	l{"_sVidParams_CSC_C_S_TFT_480a"};
	
	sRsrc_Vid_CSC_C_D_STN_480,	l{"_sVidParams_CSC_C_D_STN_480"};	// 640x480-sized Panels
	
	sRsrc_Vid_CSC_C_S_TFT_399b,	l{"_sVidParams_CSC_C_S_TFT_399b"};	// Color, TFT, Single-Drive, 640x480	[NEC]
	sRsrc_Vid_CSC_C_S_TFT_480b,	l{"_sVidParams_CSC_C_S_TFT_480b"};
	
	sRsrc_Vid_CSC_C_S_TFT_399c,	l{"_sVidParams_CSC_C_S_TFT_399c"};	// Color, TFT, Single-Drive, 640x480	[Hosiden]
	sRsrc_Vid_CSC_C_S_TFT_480c,	l{"_sVidParams_CSC_C_S_TFT_480c"};
	
	sRsrc_Vid_CSC_C_S_TFT_399d,	l{"_sVidParams_CSC_C_S_TFT_399d"};	// Color, TFT, Single-Drive, 640x480	[Toshiba]
	sRsrc_Vid_CSC_C_S_TFT_480d,	l{"_sVidParams_CSC_C_S_TFT_480d"};
	
	sRsrc_Vid_CSC_G_D_STN_400,	l{"_sVidParams_CSC_G_D_STN_400"};	// Gray, STN, Dual-Drive, 640x400	[Sharp-Escher]
	sRsrc_Vid_CSC_G_S_TFT_400,	l{"_sVidParams_CSC_G_S_TFT_400"};	//Gray, TFT, Single-Drive, 640x400	[Hosiden-Escher]
	
	sRsrc_Vid_CSC_G_D_STN_480,	l{"_sVidParams_CSC_G_D_STN_480"};	// Gray, STN, Dual-Drive, 640x480	[Sharp]
	sRsrc_Vid_CSC_G_S_TFT_480,	l{"_sVidParams_CSC_G_S_TFT_480"};	//Gray, TFT, Single-Drive, 640x480	[Hosiden]
	
	sRsrc_Vid_CSC_C_S_TFT_399y,	l{"_sVidParams_CSC_C_S_TFT_399y"};	// Color, TFT, Single-Drive, 640x480	[Sharp]
	sRsrc_Vid_CSC_C_S_TFT_480y,	l{"_sVidParams_CSC_C_S_TFT_480y"};
	
	sRsrc_Vid_CSC_G_D_STN_400y,	l{"_sVidParams_CSC_G_D_STN_400y"};	// Gray, STN, Dual-Drive, 640x400	[Sharp-Yeager]
	sRsrc_Vid_CSC_G_S_TFT_400y,	l{"_sVidParams_CSC_G_S_TFT_400y"};	//Gray, TFT, Single-Drive, 640x400	[Hosiden-Yeager]
	
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [Sharp]
//
resource 'node' (6004,"_sVidParams_CSC_C_S_TFT_399") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$05;}};										// PanelType, PanelSetup
	bytes{{$08;$09;$02;$0D;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$01;$00;$00;$01;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$05;$0A;$05}};						// 4pp
	bytes{{$05;$0A;$05;$05;$0A;$05}};						// 8pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [Sharp]
//
resource 'node' (6006,"_sVidParams_CSC_C_S_TFT_480") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$09;$02;$04;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$01;$00;$00;$01;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$04;$0A;$05}};						// 4pp
	bytes{{$05;$0A;$05;$04;$0A;$05}};						// 8pp
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [Sharp]
//
resource 'node' (6008,"_sVidParams_CSC_C_S_TFT_399a") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$06;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$0D;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$05;$0A;$05}};						// 8pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [Sharp]
//
resource 'node' (6010,"_sVidParams_CSC_C_S_TFT_480a") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$04;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$05;$0A;$05}};						// 8pp
}};

//
// 640x480 Parameters (CSC)
//
resource 'node' (6020,"_sVidParams_CSC_C_D_STN_480") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$0D;$04;}};										// PanelType, PanelSetup
	bytes{{$00;$0D;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$06}};											// DataOutForm

	bytes{{$03;$06;$03;$03;$06;$03}};						// 1pp
	bytes{{$03;$06;$03;$03;$06;$03}};						// 2pp
	bytes{{$03;$06;$03;$03;$06;$03}};						// 4pp
	bytes{{$03;$06;$03;$03;$06;$03}};						// 8pp
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [NEC]
//
resource 'node' (6030,"_sVidParams_CSC_C_S_TFT_399b") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$05;}};										// PanelType, PanelSetup
	bytes{{$0A;$0A;$03;$0F;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$06;$00;$00;$07;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$07;$00;$00}};						// 4pp
	bytes{{$06;$00;$00;$06;$00;$00}};						// 8pp
	bytes{{$06;$00;$00;$06;$00;$00}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [NEC]
//
resource 'node' (6040,"_sVidParams_CSC_C_S_TFT_480b") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$04;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$06;$00;$00;$07;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$07;$00;$00}};						// 4pp
	bytes{{$06;$00;$00;$06;$00;$00}};						// 8pp
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [Hosiden]
//
resource 'node' (6050,"_sVidParams_CSC_C_S_TFT_399c") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$05;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$0D;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$02;$02;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 8pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [Hosiden]
//
resource 'node' (6060,"_sVidParams_CSC_C_S_TFT_480c") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$00;$06;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$02;$02;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 8pp
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [Toshiba]
//
resource 'node' (6070,"_sVidParams_CSC_C_S_TFT_399d") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$05;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$05;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$0F}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 8pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [Toshiba]
//
resource 'node' (6080,"_sVidParams_CSC_C_S_TFT_480d") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$0A;$02;$05;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$0F}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 2pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 4pp
	bytes{{$04;$0A;$05;$05;$0A;$05}};						// 8pp
}};


//
// Gray, STN, Dual-Drive, 640x400 (CSC) [Sharp-Escher]
//
resource 'node' (6100,"_sVidParams_CSC_G_D_STN_400") {{
	blocksize{};
	
	bytes{{ThirdVidMode;ThirdVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BLCD-1;}};							// 480 Rows.
				
	bytes{{$0B;$00;}};										// PanelType, PanelSetup
	bytes{{$00;$02;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$04}};											// DataOutForm

	bytes{{$00;$00;$00;$06;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$02;$05;$0A}};						// 2pp
	bytes{{$00;$00;$00;$03;$05;$0A}};						// 4pp
}};

//
// Gray, TFT, Single-Drive, 640x400 (CSC) [Hosiden-Escher]
//
resource 'node' (6110,"_sVidParams_CSC_G_S_TFT_400") {{
	blocksize{};
	
	bytes{{ThirdVidMode;ThirdVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BLCD-1;}};							// 480 Rows.
				
	bytes{{$03;$00;}};										// PanelType, PanelSetup
	bytes{{$00;$02;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$07}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$00;$00;$00}};						// 2pp
	bytes{{$00;$00;$00;$04;$0A;$05}};						// 4pp
}};

//
// Gray, STN, Dual-Drive, 640x480 (CSC) [Sharp]
//
resource 'node' (6120,"_sVidParams_CSC_G_D_STN_480") {{
	blocksize{};
	
	bytes{{ThirdVidMode;ThirdVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$0F;$00;}};										// PanelType, PanelSetup
	bytes{{$00;$02;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$04}};											// DataOutForm

	bytes{{$00;$00;$00;$06;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$02;$05;$0A}};						// 2pp
	bytes{{$00;$00;$00;$03;$05;$0A}};						// 4pp
}};

//
// Gray, TFT, Single-Drive, 640x480 (CSC) [Hosiden]
//
resource 'node' (6130,"_sVidParams_CSC_G_S_TFT_480") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$00;}};										// PanelType, PanelSetup
	bytes{{$00;$02;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$07}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$00;$00;$00}};						// 2pp
	bytes{{$00;$00;$00;$00;$00;$00}};						// 4pp
	bytes{{$00;$00;$00;$05;$0A;$05}};						// 8pp
}};

//
// Color, TFT, Single-Drive, 640x480 Panel in 640x399 mode for “Thousands” (CSC) [Sharp-Yeager]
//
resource 'node' (6140,"_sVidParams_CSC_C_S_TFT_399y") {{
	blocksize{};
	
	bytes{{FifthVidMode;FifthVidMode;}};					// MaxModes: 512K,1Meg
	words{{(defmBounds_BLCD-1)-1;}};							// 480 Rows.
				
	bytes{{$01;$05;}};										// PanelType, PanelSetup
	bytes{{$08;$09;$02;$0D;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$01;$00;$00;$01;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$05;$0A;$05}};						// 4pp
	bytes{{$05;$0A;$05;$05;$0A;$05}};						// 8pp
	bytes{{$04;$0A;$05;$04;$0A;$05}};						// 16pp
}};

//
// Color, TFT, Single-Drive, 640x480 (CSC) [Sharp-Yeager]
//
resource 'node' (6150,"_sVidParams_CSC_C_S_TFT_480y") {{
	blocksize{};
	
	bytes{{FourthVidMode;FourthVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BBigLCD-1;}};							// 480 Rows.
				
	bytes{{$05;$07;}};										// PanelType, PanelSetup
	bytes{{$08;$09;$02;$04;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$06;$05}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$08}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$01;$00;$00;$01;$00;$00}};						// 2pp
	bytes{{$06;$00;$00;$04;$0A;$05}};						// 4pp
	bytes{{$05;$0A;$05;$04;$0A;$05}};						// 8pp
}};

//
// Gray, STN, Dual-Drive, 640x400 (CSC) [Sharp-Yeager]
//
resource 'node' (6160,"_sVidParams_CSC_G_D_STN_400y") {{
	blocksize{};
	
	bytes{{ThirdVidMode;ThirdVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BLCD-1;}};							// 480 Rows.
				
	bytes{{$0B;$00;}};										// PanelType, PanelSetup
	bytes{{$00;$0B;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$04}};											// DataOutForm

	bytes{{$00;$00;$00;$06;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$02;$05;$0A}};						// 2pp
	bytes{{$00;$00;$00;$03;$05;$0A}};						// 4pp
}};

//
// Gray, TFT, Single-Drive, 640x400 (CSC) [Hosiden-Yeager]
//
resource 'node' (6170,"_sVidParams_CSC_G_S_TFT_400y") {{
	blocksize{};
	
	bytes{{ThirdVidMode;ThirdVidMode;}};					// MaxModes: 512K,1Meg
	words{{defmBounds_BLCD-1;}};							// 480 Rows.
				
	bytes{{$03;$00}};										// PanelType, PanelSetup
	bytes{{$00;$0B;$00;$00;}};								// HSkew Hi/Lo, VSkew Hi/Lo
	bytes{{$00;$00;$01;$01;$00}};							// ACDClk Hi/Lo, LP Start/Width, FLMControl
	bytes{{$07}};											// DataOutForm

	bytes{{$00;$00;$00;$00;$00;$00}};						// 1pp
	bytes{{$00;$00;$00;$00;$00;$00}};						// 2pp
	bytes{{$00;$00;$00;$04;$0A;$05}};						// 4pp
}};

//-------------------------------------------------------------
//				PrimaryInit
//-------------------------------------------------------------

resource 'node' (6200,"_sCSCPrimaryInit") {{
	blocksize{};
	include{match{{file{$$Shell("RsrcDir")"DeclDataVideo.rsrc"};
				   type{'decl'};
				     id{6030};}}};
}};
