/*
	File:		ATIDefROM.r

	Contains:	xxx put contents here xxx

	Written by:	xxx put writers here xxx

	Copyright:	© 1993 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <1>	 11/5/93	fau		first checked in
		 <1>	10/27/93	fau		first checked in
		 <1>	10/19/93	fau		first checked in

*/

//--------------------------------------------------------------------------
//start
//
//Name:		ATIDefROM.r
//Creator:	George D. Wilson Jr.
//Date:		9/19/92
//
//Purpose:	Defintions for ATI monitors declaration ROM.
//
//Category:	Header File
//File:		ATIDefROM.r
//
//Detailed:	This file contains definitions for video modes for the Apple
//			13" and 16" monitors.
//
//Note:
//
//History:
//
//	  Date		Programmer					Modification
//	--------	----------		-----------------------------------------
//
//stop
//------------------------------------------------------------------------*/

#define clutType  			 		0         				// 0 if lookup table
#define fixedType 			 		1         				// 1 if fixed table
#define directType			 		2         				// 2 if direct values

#define defPixelType				0						// pixeltype=chunky
#define ChunkyDirect				16						// pixelType=ChunkyDirect

#define defmDevType					clutType				// clutType = 0

#define sRsrc_VideoHR_ATI			$80						// Video parameter sResource id
#define sRsrc_Video16				$81						// Video parameter sResource id
#define sRsrc_VideoHR_Diamond		$90

//*************************************************************
//Constants
//*************************************************************
//
// Parameter definitions {For Primary init}
//
#define defScrnRow			$0080			//Bytes per pixel line
#define defMinorBase		0				//Video RAM Offset is 0
#define defMinorLength		$4B000			//Video RAM length is $40000
  
#define defBaseOffset		$00000000		//Offset for ROM

//=============================================================================
// Parameter definitions One bit-per-pixel Hi-Res 13"
//=============================================================================
#define onemBaseOffset			defBaseOffset	//Offset to base of video RAM
#define onemRowBytesHR			$0050			//Rowbytes
#define onemBounds_THR			0				//Bounds.Top
#define onemBounds_LHR			0				//Bounds.Left
#define onemBounds_BHR			480				//Bounds.Bottom
#define onemBounds_RHR			640				//Bounds.Right
#define oneVersion				0				//Version = 0
#define onemHRes				$480000			//Horizontal Pixels/inch
#define onemVRes				$480000			//Vertical pixels/inch
#define onePixelType			clutType		//0 = Chunky
#define onePixelSize			1				//Number of bits per pixel
#define oneCmpCount				1				//Number of components in pixel
#define oneCmpSize				1				//Number of bits per component
#define onemPlaneBytes			0				//Offset from one plane to the next.
#define onemPageCnt				1				//Total number of pages
#define onemVertRefRate			67				//Vert refresh rate

#define onemDevType				0				//0 = CLUTType

//=============================================================================
// Parameter definitions Two bit-per-pixel
//=============================================================================
#define twomBaseOffset			defBaseOffset	//Offset to base of video RAM
#define twomRowBytesHR			$00A0		//Rowbytes
#define twomBounds_THR			0			//Bounds.Top
#define twomBounds_LHR			0			//Bounds.Left
#define twomBounds_BHR			480			//Bounds.Bottom
#define twomBounds_RHR			640			//Bounds.Right
#define twoVersion				0			//Version = 0
#define twomHRes				$480000		//Horizontal Pixels/inch
#define twomVRes				$480000		//Vertical pixels/inch
#define twoPixelType			clutType	//0 = Chunky
#define twoPixelSize			2			//Number of bits per pixel
#define twoCmpCount				1			//Number of components in pixel
#define twoCmpSize				2			//Number of bits per component
#define twomPlaneBytes			0			//Offset from one plane to the next.
#define twomPageCnt				1			//Total number of pages
#define twomVertRefRate			67			//Vert refresh rate

#define twomDevType				0			//0 = CLUTType

//=============================================================================
// Parameter definitions Four bit-per-pixel
//=============================================================================
#define fourmBaseOffset			defBaseOffset	//Offset to base of video RAM
#define fourmRowBytesHR			$0140		//Rowbytes
#define fourmBounds_THR			0			//Bounds.Top
#define fourmBounds_LHR			0			//Bounds.Left
#define fourmBounds_BHR			480			//Bounds.Bottom
#define fourmBounds_RHR			640			//Bounds.Right
#define fourVersion				0			//Version = 0
#define fourmHRes				$480000		//Horizontal Pixels/inch
#define fourmVRes				$480000		//Vertical pixels/inch
#define fourPixelType			clutType	//0 = Chunky
#define fourPixelSize			4			//Number of bits per pixel
#define fourCmpCount			1			//Number of components in pixel
#define fourCmpSize				4			//Number of bits per component
#define fourmPlaneBytes			0			//Offset from one plane to the next.
#define fourmPageCnt			1			//Total number of pages
#define fourmVertRefRate		67			//Vert refresh rate

#define onemDevType				0			//0 = CLUTType

//=============================================================================
// Parameter definitions Eight bit-per-pixel
//=============================================================================
#define eightmBaseOffset			defBaseOffset	//Offset to base of video RAM
#define eightmRowBytesHR			$0400		//Rowbytes
#define eightmBounds_THR			0			//Bounds.Top
#define eightmBounds_LHR			0			//Bounds.Left
#define eightmBounds_BHR			480			//Bounds.Bottom
#define eightmBounds_RHR			640			//Bounds.Right
#define eightVersion				0			//Version = 0
#define eightmHRes					$480000		//Horizontal Pixels/inch
#define eightmVRes					$480000		//Vertical pixels/inch
#define eightPixelType				clutType	//0 = Chunky
#define eightPixelSize				8			//Number of bits per pixel
#define eightCmpCount				1			//Number of components in pixel
#define eightCmpSize				8			//Number of bits per component
#define eightmPlaneBytes			0			//Offset from one plane to the next.
#define eightmPageCnt				1			//Total number of pages
#define eightmVertRefRate			67			//Vert refresh rate

#define onemDevType					0			//0 = CLUTType

//=============================================================================
// Parameter definitions Sixteen bit-per-pixel
//=============================================================================
#define sixteenmBaseOffset				defBaseOffset		//Offset to base of video RAM 
#define sixteenmRowBytesHR				$0500			//Rowbytes
#define sixteenmBounds_THR				0				//Bounds.Top
#define sixteenmBounds_LHR				0				//Bounds.Left
#define sixteenmBounds_BHR				480				//Bounds.Bottom
#define sixteenmBounds_RHR				640				//Bounds.Right
#define sixteenVersion					0				//Version = 0
#define sixteenmHRes					$480000			//Horizontal Pixels/inch
#define sixteenmVRes					$480000			//Vertical pixels/inch
#define sixteenPixelType				$10				//0 = Chunky $10 = Direct
#define sixteenPixelSize				16				//Number of bits per in pixel
#define sixteenCmpCount					3				//Number of components in pixel
#define sixteenCmpSize					5				//Number of bits per component
#define sixteenmPlaneBytes				0				//Offset from one plane to the next.
#define sixteenmPageCnt					1				//Total number of pages
#define sixteenmVertRefRate				67				//Vert refresh rate

#define sixteenmDevType					ChunkyDirect	//0 = CLUTType

//=============================================================================
// Parameter definitions One bit-per-pixel
//=============================================================================
#define onemRowBytes16			104			//Rowbytes
#define onemBounds_T16			0			//Bounds.Top
#define onemBounds_L16			0			//Bounds.Left
#define onemBounds_B16			624			//Bounds.Bottom
#define onemBounds_R16			832			//Bounds.Right
//=============================================================================
// Parameter definitions Two bit-per-pixel
//=============================================================================
#define twomRowBytes16			208			//Rowbytes
#define twomBounds_T16			0			//Bounds.Top
#define twomBounds_L16			0			//Bounds.Left
#define twomBounds_B16			624			//Bounds.Bottom
#define twomBounds_R16			832			//Bounds.Right
//=============================================================================
// Parameter definitions Four bit-per-pixel
//=============================================================================
#define fourmRowBytes16			416			//Rowbytes
#define fourmBounds_T16			0			//Bounds.Top
#define fourmBounds_L16			0			//Bounds.Left
#define fourmBounds_B16			624			//Bounds.Bottom
#define fourmBounds_R16			832			//Bounds.Right
//=============================================================================
// Parameter definitions Eight bit-per-pixel
//=============================================================================
#define eightmRowBytes16		832			//Rowbytes
#define eightmBounds_T16		0			//Bounds.Top
#define eightmBounds_L16		0			//Bounds.Left
#define eightmBounds_B16		624			//Bounds.Bottom
#define eightmBounds_R16		832			//Bounds.Right

//=====================================================================
//	Video parameter sRsrc resource IDs
//=====================================================================

#define sRsrcVidATIHR			$80			// Hi-Res 1,2,4,8,16bpp
#define sRsrcVidATI16			$81			// 16" 1,2,4,8bpp
#define sRsrcVidATIFP			$82			// 15" full page
#define sRsrcVidATI12			$83			// 12" monochrome?????



//=====================================================================
//	Special defines for SuperMario Build
//=====================================================================
//#define sRsrcUnknownDir				1							// sRsrc Directory for unknown CPUs.
//#define sRsrcUnknownBd				1							// Unknown board sRsrc.

//#define sRsrcBFBasedDir				$7F							// CPUs supported (or thought about) in the Zydeco ROM.

//#define sRsrc_Vid_DAFB_HRa			$C8							// HiRes 8,16,32
//#define sRsrc_Vid_DAFB_LPa			$C6							// GoldFish 8,16,32			


//#define BoardspIDShift				1								// board spID shift value


//#define sRsrc_BdSpike				boxQuadra700+BoardspIDShift		// (16+BoardspIDShift)

