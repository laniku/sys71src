/*
	File:		BootItt.h

	Contains:	Definitions and Structures for booting with the new SCSI Manager

	Entry points:

	Written by:	Clinton Bauder

	Copyright:	© 1992-1994 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):
	
	  <SM15>	 1/13/94	chp		Lose the local redefinitions of dNeedLock and dRAMBased.
	  <SM14>	11/22/93	pdw		Rolling in from <MCxx>.
	   <MC3>	 11/9/93	pdw		Fixed problem with almost-bootable floppies where, after they
									failed, we booted from a non-default volume.
	  <SM13>	10/14/93	pdw		<MC> roll-in.
	   <MC2>	 9/26/93	pdw		Changed some pbs.
	  <SM12>	 8/23/93	pdw		Adding function prototypes for the two new Ck4<pram> functions.
	  <SM11>	 5/29/93	PW		Fixing up ipl_rec_area typedefs.
	  <SM10>	 5/29/93	PW		Temporarily added IPLRecord.h contents here. I will make a new
									.h when we finalize what will be in it.
	   <SM9>	  5/5/93	PW		Converted names to meanies-friendly names.  Updated with latest
									from Ludwig stuff.
	   <LW7>	 4/14/93	DCB		Removed definitions of SCSIAtomic and Uniplemented
	   <LW6>	  3/8/93	PW		Removing Lo-mem definitions. (Included SysEqu instead in the
									including files instead).
	   <LW5>	  3/1/93	DCB		Changed startup PRAM to match slot drivers.
	   <LW4>	 2/13/93	PW		Moved SetLoadFlag macro to a routine in BootItt.c for SCSIDrvrs
									lo-mem support. Rolled in some of the PDM changes to make it
									easier to remain sane.
	   <SM6>	  2/4/93	PW		Added unused short to BootInfo structure to make it native
									aligned.
	   <SM5>	  2/1/93	PW		Update from the latest of Ludwig. Also changes required for PDM
									(will update Ludwig with these as needed myself).
	   <LW3>	 1/27/93	DCB		Added defines for CmdOptShiftDel startup sequence to fix Radar
									Bug 1051033.
	   <LW2>	 1/27/93	PW		Converted to 16-bit LUN and back again.
	   <SM4>	10/30/92	DCB		Changed to reflect new acam.h
	   <SM3>	 9/16/92	CB		Fixed a minor boot problem with HD SC Setup wherein async
									drivers didn't load because the mount flag value contained
									garbage. This might have also caused problems with some third
									party disk drivers.
	   <SM2>	 7/28/92	PW		First real check-in.
		 <0>	 6/24/92	DCB		New Today 

*/

#ifndef __BOOTITT__
#define __BOOTITT__

#ifndef __XPTPRIV__
#include "XPTpriv.h"
#endif


/* Structure definitions */

typedef struct {
	ulong		ddBlock;
	ushort		ddSize;
	ushort		ddType;
} ddMap;

typedef struct {
	DeviceIdent		DevIdent;
	SCSI_IO		 	*ioPB;
	Boolean			IdentMsg;
} DevInfo;

typedef struct {
	DefStartRec 	startPRAM;			// long word
	ushort			BusCount;
	ushort			defltDrvrRefNum;	// ref num of driver for default boot device
	ulong			IDmasks[];
} BootInfo;


/* Function Prototypes */

Boolean ISITT();
void 	INITSCSIBOOT( void );
short	ITTBOOT( ulong onlyStartup, Boolean * forceBootPtr );

short	ScRead( DevInfo *, ulong, ulong, ushort, Ptr);
ulong	CheckSumDrvr( Ptr driver,ushort length );
OSErr 	SOpenDriver(SpBlockPtr sp);
Boolean Ck4IgnoreCmdShOptDel( void);
Boolean Ck4OnlyLoadFromDefault( void);

/* Useful Macros */

#define	TestLoadFlag(a,b) ((1 << b.targetID) & a->IDmasks[b.bus])		// <SM4>

short	JmpToDrvr( long devIDorTargID, Ptr theDriver, Ptr DrvrDescMap, Ptr HFSPartBlock);

#define CmdShiftOptDel	0x8805			// command, shift, option and delete keys down bits
#define	lm_KeyMap		0x174			// bitmap of the keyboard [2 longs]
#define SCSIDrvrs (*(uchar *)0xb2e)


/* slot category and type values, values were established by DTS */
#define	CatIntBus	0xC			/* Intelligent bus sRsrc_Type from DTS */

#define	TypXPT	0x000B			/* official XPT type */
#define	TypSIM	0x000C			/* official SIM type */
#define	DrvrSwScsi43	0x1		/* official software protocol */



/*****************************************************************************
 
Here is the C structure that describes the AIX format block 0.
int's are 4 bytes, short's are 2.  The type unique_id_t is 4 int's long.
 
What you have to to is look for the value IPLRECID in the first 4 bytes and if
it matches, look in the boot_lv_start field.  This will point you to a block
that looks like an Apple driver descriptor block (block 0 on an apple drive).
The next block will be the start of the partition map.
 
My assumption is that you'll use the information out of that Apple partition
map to load our secondary loader as an Apple_driver.  We'll specify (using the
CPU type field) whether we want to be launched as emulated 68K code or as
native PowerPC code.
 
One question... do you want the block numbers in the driver partition entry to
specify real physical block numbers or block numbers offset by boot_lv_start?
We can do either, but if we offset the block numbers is it a problem if the
block number is negative?
 
One other question... I assume your code will ignore the drive if the block
pointed to by boot_lv_start doesn't look like an Apple block 0.  This is the
behavior we would like so PDM won't try to boot IBM RS/6000 drives.
 
If you have any questions, give my a call at 2-6202 or drop me e-mail (Quick
mail prefered).
 
Thanks,
Jeff
 
*****************************************************************************/

#ifndef _H_BOOTRECORD
#define _H_BOOTRECORD

/*
 * COMPONENT_NAME: (KBOOT) bootrecord.h header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
 
/*****************************************************************************/
/*                                                                           */
/* This file defines the IPL Record template. The IPL Record information is  */
/* contained on one sector.                                                  */
/*                                                                           */
/* Acronyms used in this file:                                               */
/*   PSN          Physical Sector Number                                     */
/*   IPL          Initial Program Load                                       */
/*   BLV          Boot    Logical Volume                                     */
/*   SLV          Service Logical Volume                                     */
/*                                                                           */
/* General notes:                                                            */
/*   Fragmentation implies that code which is loaded into memory may not be  */
/*   loaded in one completely contiguous area and inherently refers to memory*/
/*   above the first megabyte bound of memory since the processor environment*/
/*   requires the first meg to be good. That is, code which crosses or is    */
/*   completely contained above the first meg of memory may need to be       */
/*   fragmented. This is reflected in the value of the "boot_frag" flag which*/
/*   is defined below.                                                       */
/*                                                                           */
/* Usage examples for this file:                                             */
/*                                                                           */
/*   IPL_REC_PTR my_rec_ptr          defines my_rec_ptr as a pointer to the  */
/*                                   struct "ipl_rec_area".                  */
/*                                                                           */
/*   IPL_REC my_rec                  can be used to define memory space for  */
/*                                   an ipl record.                          */
/*                                                                           */
/*   sizeof(IPL_REC)                 will return the size (in bytes) of      */
/*                                   ipl_rec_area                            */
/*                                                                           */
/*   my_rec.field_name               either of these can be used to access   */
/*   my_rec_ptr->field_name          an element of the ipl record (shown     */
/*                                   here as "field_name").                  */
/*                                                                           */
/*****************************************************************************/

typedef long unique_id_t[4];

typedef struct ipl_rec_area
{
    unsigned long     IPL_record_id;    /* This physical volume contains a   */
                                        /* valid IPL record if and only if   */
                                        /* this field contains IPLRECID      */
 
#define IPLRECID 0xc9c2d4c1
 
    char              reserved1[20];
    unsigned long     formatted_cap;    /* Formatted capacity. The number of */
                                        /* sectors available after formatting*/
                                        /* The presence or absence of bad    */
                                        /* blocks does not alter this value. */
 
    char              last_head;        /* THIS IS DISKETTE INFORMATION      */
                                        /* The number of heads minus 1. Heads*/
                                        /* are number from 0 to last_head.   */
 
    char              last_sector;      /* THIS IS DISKETTE INFORMATION      */
                                        /* The number of sectors per track.  */
                                        /* Sectors are numbered from 1 to    */
                                        /* last_sector.                      */
 
    char              reserved2[6];
 
    unsigned long     boot_code_length; /* Boot code length in sectors. A 0  */
                                        /* value implies no boot code present*/
 
    unsigned long     boot_code_offset; /* Boot code offset. Must be 0 if no */
                                        /* boot code present, else contains  */
                                        /* byte offset from start of boot    */
                                        /* code to first instruction.        */
 
    unsigned long     boot_lv_start;    /* Contains the PSN of the start of  */
                                        /* the BLV.                          */
 
    unsigned long     boot_prg_start;   /* Boot code start. Must be 0 if no  */
                                        /* boot code present, else contains  */
                                        /* the PSN of the start of boot code.*/
 
    unsigned long     boot_lv_length;   /* BLV length in sectors.            */
 
    unsigned long     boot_load_add;    /* 512 byte boundary load address for*/
                                        /* boot code.                        */
 
    char              boot_frag;        /* Boot code fragmentation flag. Must*/
                                        /* be 0 if no fragmentation allowed, */
                                        /* else must be 0x01.                */
 
    char              reserved3[3];
 
    unsigned short    basecn_length;    /* Number of sectors for base        */
                                        /* customization. Normal mode.       */
 
    unsigned short    basecs_length;    /* Number of sectors for base        */
                                        /* customization. Service mode.      */
 
    unsigned long     basecn_start;     /* Starting PSN value for base       */
                                        /* customization. Normal mode.       */
 
    unsigned long     basecs_start;     /* Starting PSN value for base       */
                                        /* customization. Service mode.      */
 
    char              reserved4[24];
 
    unsigned long      L_length;        /* Service code length in sectors.   */
                                        /* A 0 value implies no service code */
                                        /* present.                          */
 
    unsigned long     ser_code_offset;  /* Service code offset. Must be 0 if */
                                        /* no service code is present, else  */
                                        /* contains byte offset from start of*/
                                        /* service code to first instruction.*/
 
    unsigned long     ser_lv_start;     /* Contains the PSN of the start of  */
                                        /* the SLV.                          */
 
    unsigned long     ser_prg_start;    /* Service code start. Must be 0 if  */
                                        /* service code is not present, else */
                                        /* contains the PSN of the start of  */
                                        /* service code.                     */
 
    unsigned long     ser_lv_length;    /* SLV length in sectors.            */
 
    unsigned long     ser_load_add;     /* 512 byte boundary load address for*/
                                        /* service code.                     */
 
    char              ser_frag;         /* Service code fragmentation flag.  */
                                        /* Must be 0 if no fragmentation     */
                                        /* allowed, else must be 0x01.       */
    char              reserved5[3];
 
    unique_id_t       pv_id;            /* The unique identifier for this    */
                                        /* physical volume.                  */
    char              dummy[512 - 128 - sizeof(unique_id_t)];
} ipl_rec_area;


#endif /* _H_BOOTRECORD */
 
#endif __BOOTITT__