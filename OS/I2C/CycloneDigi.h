/* Apple Cyclone Hardware Unique CycloneDigi.h */

/* 
	File name: 	CycloneDigi.h 
	Function:	Header file for a Cyclone digitizer component
	History:	1/27/92	New today
*/

#ifndef _CycloneDigi_
#define	_CycloneDigi_
#endif

/* ------Constants unique to Cyclone ------------------------------------------------------------*/

/* Cyclone video defaults */
#define kWhiteDefault		0
#define kBlackDefault		0xffff
#define kBrightDefault		0x7fff
#define kContrastDefault	0
#define kHueDefault			0x7fff
#define kSaturationDefault	0x2c00					/* saturation for normal NTSC */
#define kDMSD_Chip			0x8a					/* Philips DMSD I2c chip address */
#define kVDC_Chip			0xb8					/* Philips VDC I2c chip address */

#define kVDoubleLine		0x50036208				/* Civic II double video lines on output; disable=1, enable=0 */

/* ------CLUT Addresses for Sebastian (as defined in PSC ERS.)---------------------------------- */
#define kSeb_CLUT_Addr		0x50f30000				/* addr. for access to CLUT/Test Address Register */

#define kSeb_CLUT_Data		0x50f30010				/* addr. for access to CLUT Data Register */

#define kSeb_CLUT_Ctrl		0x50f30020				/* addr. for access to CLUT Control Register */
#define kSeb_Ctrl_16		0x08					/* Sebastian Ctrl., 8/16 bit video select, 0=8-bit, 1=16-bit video*/
#define kSeb_Ctrl_CLUTSel	0x40					/* Sebastian Ctrl., CLUT select 0=graphics, 1=video */
#define kSeb_Ctrl_OverE		0x80					/* Sebastian Ctrl., Overlay Enable bit; 1=enable.

#define kSeb_CLUT_TData		0x50f30030				/* addr. for access to CLUT Test Data Register */

/* ------CIVIC Addresses------------------------------------------------------------------------ */
#define kCIVIC_vinVFP		0x50036600				/* Video In Vertical Front Porch */
#define kCBITS_vinVFP		12						

#define kCIVIC_vinVAL		0x500365c0				/* Video In Vertical Active Area */
#define kCBITS_vinVAL		12

#define kCIVIC_vinHFP		0x50036240				/* Video In Horz. Front Porch */
#define kCBITS_vinHFP		12

#define kCIVIC_evblankdelay	0x50036200				/* Video early Horz. Front Porch */
#define kCBITS_evblankdelay	2

#define kCIVIC_vinEHAL		0x500361c0				/* Video In Horz. Active Area */
#define kCBITS_vinEHAL		12

#define kCIVIC_conv			0x50036054				/* Convolution enable bit */
#define kCBITS_conv			1

#define kCIVIC_d64_32		0x5003604c				/* 64 or 32 bit wode graphics memory */
#define kCBITS_d64_32		1

#define kCIVIC_VSCDIVIDE	0x5003602c				/* Used to control 8-bit or 16-bit video-in */
#define kCBITS_VSCDIVIDE	1

#define kCIVIC_vdc_clock_e	0x50036018				/* VDC clock enable (allow or not VRAM access from VDC)*/
#define kCBITS_vdc_clock_e	1

#define kCIVIC_big_small_v	0x50036014				/* Video-in big/small video line */
#define kCBITS_big_small_v	1	

#define kCIVIC_vdc_int_e	0x50036010				/* VDC Field Interrupt enable */
#define kCBITS_vdc_int_e	1

#define kCIVIC_clr_vdc_int	0x5003600c				/* Clear VDC Interrupt */
#define kCBITS_clr_vdc_int	1	

#define kCIVIC_vdc_int		0x50036008				/* Contains VDC interrupt */
#define kCBITS_vdc_int		1

#define kCIVIC_VAL			0x50036580				/* Graphics Vertical Active Area start */
#define kCBITS_VAL			12

#define kCIVIC_HAL			0x50036380				/* Graphics Horz. Active Line start */
#define kCBITS_HAL			12








