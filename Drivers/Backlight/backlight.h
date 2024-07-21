/*
	File:		backlight.h

	Contains:	definitions for backlight driver

	Written by:	Andy Gong  x6595

	Copyright:	© 1990-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

	   <SM7>	  1/5/94	kc		Add Function ProtoTypes to prevent compiler warnings.
	   <SM6>	12/13/93	PN		Roll in KAOs and Horror changes to support Malcom and AJ
									machines
	   <SM5>	 9/2/93		SKH		Roll in changes from Horror
	   <SM4>	 2/11/93	CSS		Remove boxflags from this file.  
	   								Update from Horror.  Comments follow <H10-2>:
	   <H10>	 1/21/93	RLE		add Escher box flags
		<H9>	 6/30/92	ag		Added new type definitions.
		<H8>	  5/7/92	ag		Added new type definitions to accomodate table changes.
		<H7>	 4/24/92	ag		added new hardware dependent field for general use by hardware
									dependent code.  added new typedefs to allow for easier type
									conhersion.
		<H6>	12/17/91	SWC		Added boxDBLiteLC.
		<H5>	12/16/91	HJR		Added boxDartanian.
	    <H4>	 11/5/91	SWC		Fixed boxDBLite again because we got pushed out to a new value.
		<H3>	 9/10/91	SWC		Fixed boxAsahi and boxDBLite to reflect final values.
		<H2>	  8/5/91	SWC		Added boxDBLite to list of CPUs we work with.
 		 <8>	 3/30/92	JSM		Rolled this file into SuperMario project.
		 <7>	 3/24/92	JSM		Nuke boxFlag codenames.
		 <6>	10/28/91	SAM		Rolled in Regatta file.
	
									Regatta Change History:
							
									 <7>	  8/8/91	SAM		(ag) Updated boxFlag constants in this file (yuk!)
									 <6>	 7/30/91	SAM		(ag) changed version to 1.0.2
									 <5>	 7/18/91	SAM		(ag) added box flag constants, changed global definitions
									 <4>	 6/30/91	SAM		Merged from TERROR [<4><5>].
									 <3>	 6/14/91	SAM		(ag) Added sample interval field to global definition.
									 <1>	 5/15/91	SAM		Split off from TERRORProj.
							
									Terror Change History:
							
									 <5>	 6/26/91	ag		added support for table change as a function of charger and
																voltage.  New fields in global include slewing flags and rates,
																procedure proc definition to call to handle table changes, and
																voltage thresholds for hysteresis on table changes.
									 <4>	 6/24/91	ag		Added table pointer elements and other variables to global data
																structure.  Added new define for range set call.
									 <3>	 6/10/91	ag		Added sample interval field to global definition.
									 <2>	  4/2/91	ag		added definitions for globals.
									 <1>	 1/23/91	ag		first checked in

		 <5>	 11/8/90	ag		change range of backlight, max now 30
		 <4>	 9/25/90	ag		added asahi support
		<1+>	 8/15/90	ag		adding get range function to status call
				90/07/27	ag		new today
*/

/*
 *
 *	VERSION		0xMMmm
 *		MM - Major Version number
 *		mm - minor Version number
 *
 */
#define	DRIVERMAJORVERSION		0x0100
#define	DRIVERMINORVERSION		0x0001
#define DRIVERVERSION			(DRIVERMAJORVERSION + DRIVERMINORVERSION)

/* Control Calls */
#define KCONTROLCALL			0x4300
#define kSetScreenBrightness	(KCONTROLCALL + 1)
#define kSaveScreenBrightness	(KCONTROLCALL + 2)
#define kCdevActive				(KCONTROLCALL + 3)
#define kSetBrightnessKeys		(KCONTROLCALL + 4)

#define	kSavePKeys				(KCONTROLCALL + 5)
#define	kSetRange				(KCONTROLCALL + 6)

#define	kSetTable				(KCONTROLCALL + 7)

/* Status Calls */
#define KSTATUSCALL				0x5300
#define kGetScreenBrightness	(KSTATUSCALL + 1)
#define kGetBrightnessKeys		(KSTATUSCALL + 2)
#define kGetBrightnessRange		(KSTATUSCALL + 3)

#define kGetPBacklight			(KSTATUSCALL + 4)
#define kGetPKey				(KSTATUSCALL + 5)
#define kGetMaximum				(KSTATUSCALL + 6)

#define KGetVersion				(KSTATUSCALL + 7)
#define kGetUserInput			(KSTATUSCALL + 8)

/* range limits */
#define kMaxRangeValue			4
#define kMinRangeValue			0

/* key bits */
#define kBacklightControl		0x01
#define kBacklightShift			0x02
#define kBacklightOption		0x04

#define	INVALID_BRIGHTNESS	-1


/* ID routines */

#define	DRIVERNAME				".Backlight"

#define BACKLIGHTSIGREG			(* ((char *) 0xFC0200))	
#define BACKLIGHTSIG_ARUBA		((char) 0xA5)
#define BACKLIGHTSIG_UPGRD		((char) 0xA3)
#define BACKLIGHTSIG_ASAHI		((char) 0xAD)

/* 
 *		aruba             0   1   0   1
 *		upgrade           0   0   1   1
 * 		ashsi             1   1   0   1
 *
 *		+---+---+---+---+---+---+---+---+		
 *		| 1 | 0 | 1 | 0 | x | x | x | x |
 *		+---+---+---+---+---+---+---+---+		
 *		                  ^   ^   ^   ^
 *		                  |   |   |   |
 *		PWM	 -------------+   |   |   |
 *		ON BIT POSITIVE ------+   |   |
 *		5 Volt Table   -----------+   |
 *		COUNT Up ---------------------+
 *
 *
 */

#define	PWM_CTL			0x08
#define	ON_HIGH			0x04
#define	TABLE_5V		0x02
#define	COUNT_DWNBIT	0x01

#define KEY_MASK			0xE0					/* key mask */
#define	KEY_VALUE_MASK		0x07					/* mask for set value */
#define VALUE_MASK			0x1F					/* signature mask */

#define	JAWS_SPEED_FSTN_REG_PTR	((unsigned char *) 0x50FB4000)
#define	JAWS_25MHZ				0x01
#define	JAWS_FSTN				0x02


#define PORTABLE_BACKLIGHT()	((BACKLIGHTSIGREG == BACKLIGHTSIG_ARUBA) || (BACKLIGHTSIGREG == BACKLIGHTSIG_UPGRD) || (BACKLIGHTSIGREG == BACKLIGHTSIG_ASAHI))

typedef struct
	{
	Ptr					globals;
	VBLTask				vblpb;
	} vblstruct;

typedef struct
	{
	short				minimum;
	short				maximum;
	unsigned char		table[];
	} setTableType;									/* <H8> new structure for tables */

typedef struct
	{
	SleepQRec		sleepQelement;					/* sleep queue element, MUST stay on top */
	vblstruct		brightnessVbl;					/* vbl element for background functions */
	unsigned short	version;

	unsigned int	reserved	:24;				/* unused flags */
	unsigned int	slewChange	:1;					/* unused flags */
	unsigned int	lowTable	:1;					/* unused flags */
	unsigned int	dualTable	:1;					/* unused flags */
	unsigned int	freeflag	:1;					/* call pmgr AtoD instead of temp status */
	unsigned int	flyByWire	:1;					/* is this software control throught hardware input controls */
	unsigned int	vbl_ok		:1;					/* allow background functions */
	unsigned int	kbdactive	:1;					/* used for kbd repeat, indicated kbd currently adj backlight */
	unsigned int	disableHWinput	:1;				/* flag used to enable user input scanning */

	int				(*setlevelproc)();				/* pointer to set backlight routine */
	int				(*userInputProc)();				/* pointer to read user control routine */
	OSErr			(*controlProc)();
	OSErr			(*statusProc)();
	int				(*closeProc)();					/* pointer to shutdown routine */
	void			(*tableProc)();					/* pointer to shutdown routine */

	short			slewLimit;
	unsigned short	lowThreshold;
	unsigned short	hiThreshold;
	setTableType	*settingTable;					/* <H8> pointer to record now */
	setTableType	*settingTableLow;				/* <H8> pointer to record now */
	setTableType	*settingTableHigh;				/* <H8> pointer to record now */
	short			*maximumTable;

	short			lastLevel;						/* last power level */
	short			powerRange;						/* battery power range */
	short			userRange;						/* user power range */
	short			userInputSampleRate;			/* rate of sampling user input (ticks) */
	short			userBrightness;					/* user requested brightness */
	short			lastHWSetting;

	
	short			mousedownTicks;					/* first notice of mouse down in tick count */
	short			keycodes;						/* key combinations */
	short			lastatod;						/* last raw a to d value */
	
	Ptr				hardwareDependentPtr;			/* private storage for hardware dependent code */
	} driverGlobaltypes, *driverGlobalPtr;

typedef struct 
	{
	int					setProc;
	int					getProc;
	int					open;
	int					close;
	int					control;
	int					status;
	int					tableProc;
	int					maxTable;
	int					lowTable;
	int					hiTable;
	int					hwDependentVar;

	} *cpuBkltRoutinePtr;

typedef struct 
	{
	unsigned long		flags;
	short				userInputSampleRate;
	unsigned short		lowThreshold; /*low hysteresis threshold */
	unsigned short		hiThreshold	;	/* high hysteresis threshold */
	} *cpuBkltInfoPtr;

typedef struct 
	{
	cpuBkltRoutinePtr	bkltroutines;
	cpuBkltInfoPtr		bkltinfo;
	} cpuDependentInfoType,*cpuDependentInfoPtr;



#define	PEG_TO_LIMITS(value,max,min)	value = (value > max) ? max : (value < min) ? min : value

#define GetPramBrightness()		( GetBacklightInfo(VALUE_MASK, 0) - 1 )
#define GetPramKeyData()		GetBacklightInfo(KEY_MASK, 5)

													/* add backlight value offset */
#define	SaveBrightness(new)		SaveBacklightInfo(new+1,VALUE_MASK, 0)
#define	SaveKeyData(new)		SaveBacklightInfo(new,KEY_MASK, 5)

/* <H8> new ponti defintions */
#define	PONTILMPCTLREG			*((unsigned char *) 0x50f96C00)
#define	PONTILMPON				0
#define	PONTILMPHWCTL			1
#define	PONTILMPMUX0			2
#define	PONTILMPMUX1			3

typedef	int 	(*intFunction)();
typedef OSErr	(*osFunction)();
typedef void	(*voidFunction)();

int abs(int);
unsigned char GetPortableValues(int	parameter);
OSErr InitPWMControls(driverGlobalPtr globalPtr);
unsigned char Get_AtoD(int channel);
unsigned char Get_PGEButton(int	channel);
int SetPWM(int new, driverGlobalPtr globalPtr);