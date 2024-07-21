/*
	File:		ATIDeclGamma.r

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
//Name:		ATIDeclGamma.r
//Creator:	George D. Wilson Jr.
//Date:		5/19/92
//
//Purpose:	Gamma table declarations
//
//Category:	Gamma Tables
//File:		ATIDeclGamma.r
//
//Detailed:	This file contains gamma table definitions for standard
//			Apple monitors.
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

#include 	"ROMLink.r"
#include	"Types.r"

//=====================================================================
//				Gamma resource tables
//=====================================================================
#define ColorGammaID	2000
#define HiResGammaID	2001
#define GrayGammaID		2002
#define RubikGammaID	2003


resource 'gdir' (700, "_GammaDirHiRes") {{
  128, l{"HiResGamma"};
}};


resource 'gdir' (710, "_GammaDir_16") {{
  128, l{"HiResGamma"};
  129, l{"ColorGamma"};
}};



resource 'node' (720, "ColorGamma") {{
	blocksize{};
		
	word   {ColorGammaID};								// gamma res ID
	cstring{"Page-White Gamma"};
	align  {2};	
		
	word   {$0000};										// gVersion
	word   {$0000};										// gType
	word   {$0000};										// gFormulaSize
	word   {$0003};										// gChanCnt
	word   {$0100};										// gDataCnt
	word   {$0008};										// gChanWidth
		
	longs{{
		$00030609;$0C101012;$13151616;$181B1C1E;		// red channel
		$1F222326;$282B2C2F;$3234373A;$3C3F4041;
		$42434445;$46474749;$4A4B4C4D;$4E4F5051;
		$52535454;$56565758;$595A5B5C;$5D5E5F60;
		$61626364;$65666768;$696A6B6C;$6D6E6F70;
		$71727273;$74757677;$78797A7A;$7B7C7D7E;
		$7F818283;$83848586;$8788898A;$8A8B8C8D;
		$8E8F9091;$92939394;$95969798;$98999A9B;
		$9C9D9E9F;$A0A1A1A2;$A3A4A4A5;$A6A7A8A8;
		$A9AAABAC;$ADADAEAF;$B0B1B2B2;$B3B4B5B5;
		$B6B7B8B8;$B9BABBBC;$BCBDBEBF;$C0C0C1C2;
		$C3C3C4C5;$C6C6C7C8;$C9C9CACB;$CCCDCDCE;
		$CFD0D1D1;$D2D3D4D4;$D5D6D7D7;$D8D9DADA;
		$DBDCDDDE;$DEDFE0E1;$E1E2E3E4;$E4E5E6E7;
		$E7E8E9EA;$EAEBECED;$EEEEEFF0;$F1F1F2F3;
		$F4F4F5F6;$F7F8F8F9;$FAFBFBFC;$FDFEFFFF;
	}};

	longs{{		
		$00030609;$0C101018;$20202223;$24252728;	// green channel
		$292C2D2E;$30323437;$383A3D3F;$40414242;
		$43444445;$46474849;$4A4A4B4C;$4D4E4F50;
		$51525354;$55565758;$595B5C5D;$5E5F6061;
		$62636465;$65666768;$696A6B6C;$6D6E6F70;
		$71717273;$74747576;$77787979;$7A7B7C7D;
		$7E7F8081;$82838484;$85868788;$88898A8B;
		$8C8D8E8E;$8F909192;$93939495;$96969798;
		$999A9A9B;$9C9D9E9E;$9FA0A1A2;$A2A3A4A5;
		$A5A6A7A8;$A8A9AAAB;$ABACADAE;$AFAFB0B1;
		$B2B2B3B4;$B5B5B6B7;$B7B8B9BA;$BABBBCBD;
		$BDBEBFC0;$C1C1C2C3;$C3C4C5C6;$C6C7C8C9;
		$C9CACBCC;$CCCDCECF;$CFD0D1D2;$D2D3D4D4;
		$D5D6D6D7;$D8D9D9DA;$DBDCDCDD;$DEDEDFE0;
		$E1E1E2E3;$E4E4E5E6;$E6E7E8E9;$E9EAEBEC;
		$ECEDEEEF;$EFF0F1F2;$F2F3F4F4;$F5F6F7F7;
	}};
	
	longs{{
		$00020508;$0A0D1010;$10202022;$23232425;		// blue channel
		$25272829;$2A2C2D2E;$2F303233;$34363738;
		$3A3C3D3F;$40414142;$42434444;$45454647;
		$4748494A;$4A4B4C4D;$4D4E4F4F;$51515253;
		$54555656;$5758595A;$5B5C5D5E;$5F606061;
		$62626364;$64656666;$67686969;$6A6B6C6C;
		$6D6E6F6F;$70717272;$73747475;$76777778;
		$79797A7B;$7C7C7D7E;$7F808182;$82838484;
		$85868687;$8888898A;$8A8B8C8D;$8D8E8F90;
		$90919192;$93939495;$95969797;$9899999A;
		$9B9B9C9D;$9D9E9FA0;$A0A1A1A2;$A3A3A4A4;
		$A5A6A6A7;$A7A8A9A9;$AAABABAC;$ADADAEAF;
		$AFB0B0B1;$B2B2B3B3;$B4B5B5B6;$B6B7B8B8;
		$B9BABABB;$BBBCBDBD;$BEBFBFC0;$C0C1C2C2;
		$C3C3C4C5;$C5C6C6C7;$C8C8C9C9;$CACBCBCC;
		$CCCDCECE;$CFD0D0D1;$D1D2D3D3;$D4D4D5D6;
	}};
}};

	
resource 'node' (730, "HiResGamma") {{	
	blocksize{};
	
	word   {HiResGammaID};								// gamma res ID
	cstring{"Mac Std Gamma"};
	align  {2};	

	word{$0000};										// gVersion
	word{$0000};										// gType
	word{$0000};										// gFormulaSize
	word{$0001};										// gChanCnt
	word{$0100};										// gDataCnt
	word{$0008};										// gChanWidth

	longs{{		
		$0005090B;$0E101315;$17191B1D;$1E202224;				
		$2527282A;$2C2D2F30;$31333436;$37383A3B;
		$3C3E3F40;$42434445;$4748494A;$4B4D4E4F;
		$50515254;$55565758;$595A5B5C;$5E5F6061;
		$62636465;$66676869;$6A6B6C6D;$6E6F7071;
		$72737475;$76777879;$7A7B7C7D;$7E7F8081;
		$81828384;$85868788;$898A8B8C;$8C8D8E8F;
		$90919293;$94959596;$9798999A;$9B9B9C9D;
		$9E9FA0A1;$A1A2A3A4;$A5A6A6A7;$A8A9AAAB;
		$ABACADAE;$AFB0B0B1;$B2B3B4B4;$B5B6B7B8;
		$B8B9BABB;$BCBCBDBE;$BFC0C0C1;$C2C3C3C4;
		$C5C6C7C7;$C8C9CACA;$CBCCCDCD;$CECFD0D0;
		$D1D2D3D3;$D4D5D6D6;$D7D8D9D9;$DADBDCDC;
		$DDDEDFDF;$E0E1E1E2;$E3E4E4E5;$E6E7E7E8;
		$E9E9EAEB;$ECECEDEE;$EEEFF0F1;$F1F2F3F3;
		$F4F5F5F6;$F7F8F8F9;$FAFAFBFC;$FCFDFEFF;
	}};
}};



	
resource 'node' (740, "GrayGamma") {{	
	blocksize{};
	
	word   {GrayGammaID};								// gamma res ID
	cstring{"Mac Gray Gamma"};
	align  {2};	

	word{$0000};										// gVersion
	word{$0000};										// gType
	word{$0000};										// gFormulaSize
	word{$0001};										// gChanCnt
	word{$0100};										// gDataCnt
	word{$0008};										// gChanWidth

	longs{{		
		$000A141D;$23262B2E;$30323437;$393B3C3E;
		$40414244;$4547484A;$4B4D4E4F;$50515254;
		$55565758;$5A5B5C5D;$5E5F6061;$63646566;
		$6768696A;$6B6C6D6E;$6F707171;$72737475;
		$76777879;$7A7B7C7D;$7E7F8080;$81828384;
		$84858687;$88898A8A;$8B8C8D8E;$8F909091;
		$92929394;$95969797;$98999A9A;$9B9C9D9E;
		$9E9FA0A1;$A1A2A3A3;$A4A5A6A7;$A7A8A9AA;
		$AAABACAD;$ADAEAFAF;$B0B1B2B2;$B3B4B4B5;
		$B6B6B7B7;$B8B9B9BA;$BBBCBCBD;$BEBEBFC0;
		$C0C1C2C2;$C3C4C5C5;$C6C6C7C8;$C8C9CACB;
		$CCCDCDCE;$CFCFD0D0;$D1D2D2D3;$D3D4D5D6;
		$D6D7D7D8;$D9D9DADA;$DBDCDDDD;$DEDFDFE0;
		$E0E1E2E3;$E3E4E5E5;$E6E6E7E7;$E8E8E9EA;
		$EAEBEBEC;$EDEDEEEF;$F0F0F1F2;$F2F3F4F4;
		$F5F5F6F7;$F7F8F9FA;$FAFBFCFC;$FDFEFEFF;
	}};
}};



	
resource 'node' (750, "RubikGamma") {{	
	blocksize{};
	
	word   {RubikGammaID};								// gamma res ID
	cstring{"Mac RGB Gamma"};
	align  {2};	

	word{$0000};										// gVersion
	word{$0000};										// gType
	word{$0000};										// gFormulaSize
	word{$0001};										// gChanCnt
	word{$0100};										// gDataCnt
	word{$0008};										// gChanWidth

	longs{{		
		$05070809;$0B0C0D0F;$10111214;$15161819;
		$1A1C1D1E;$20212223;$24262829;$2A2C2D2F;
		$30313334;$36373839;$3A3C3D3E;$40414243;
		$44454648;$494B4C4D;$4E4F5051;$52535455;
		$5758595A;$5B5C5D5E;$5F606163;$63656567;
		$67696A6B;$6C6D6E6F;$70717273;$74757677;
		$78797A7A;$7B7C7D7E;$7F818283;$83848586;
		$8788898A;$8B8C8D8E;$8E909091;$92939394;
		$95969798;$999A9B9C;$9D9E9FA0;$A0A1A2A3;
		$A4A4A5A6;$A7A8A9AA;$AAACADAD;$AEAEB0B1;
		$B2B3B3B4;$B5B6B7B8;$B9B9BABB;$BCBDBEBF;
		$BFC0C1C2;$C2C3C4C5;$C6C7C8C9;$CACBCCCD;
		$CDCECECF;$D0D1D2D3;$D3D4D5D6;$D6D7D8D8;
		$D9DADBDC;$DDDEDEDF;$E0E1E1E2;$E3E4E4E5;
		$E6E7E7E8;$E9EAEBEC;$EDEEEEEF;$EFF0F1F2;
		$F3F3F4F5;$F6F7F8F8;$F9F9FAFB;$FCFDFEFF;
	}};
}};

