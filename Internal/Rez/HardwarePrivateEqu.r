//__________________________________________________________________________________________________
//
//   File:       HardwarePrivateEqu.r (generated from HardwarePrivateEqu.a)
//
//   Contains:   Macintosh assembly equates THAT ARE NOT TO BE RELEASED TO THE WORLD.
//
//   Copyright:  © 1990-1993 by Apple Computer, Inc., all rights reserved.
//
//   Change History (most recent first):
//
//     <SM14+>	 8/4/93		JDR		private sound defines are in SoundPrivate.a
//     <SM14>	  6/9/93	kc		Roll in Ludwig.
//	    <LW2>	 2/24/93	chp		Added equates for the PSC wait/request multiplexer control bits
//									in VIA1.
//     <SM13>     8/17/92    CCH     Bumped HeapStart to $2800.
//     <SM12>      8/7/92    JDB     Changed Singer control register to have 0 for the output
//                                   attenuation and  5 for the input gain.
//     <SM11>    07-14-92    jmp     (ag,H24) Change the name of a bit from PontiSndExtMic to
//                                   PontiSndIntMic
//                                   (jmp,H23) Added some additional DAFB equates for the WombatDAFB
//                                   code.
//                                   (BG,H22) Added one more djMEMC-related symbolic definition
//                                   (dj_MaxBanks).
//     <SM10>     6/21/92    ejb     Adding bit field definitions for dspOverrun register in PSC.
//      <SM9>     6/21/92    RB      Adding runtime support for EVT1 and EVT2 Cyclones. Defined
//                                   temporary equates for  the EVT1 Cyclone units.
//      <SM8>     6/18/92    KW      (BG,H21) Added djMEMC memory controller equates for Wombat and
//                                   WLCD.
//                                   (jmp,H20) Wombat has a different dot-clock chip than
//                                   Spike/Eclipse/Zydeco, so I added an equate to reflect this.
//      <SM7>     6/18/92    RB      Added equates for the new EVT2 (final offsets) of the VIA2 on
//                                   Cyclone. The old values are still supported under the
//                                   conditional forEVT1. These should be deleted once everyone moves
//                                   to EVT2 boards. Did the same with MUNIBase as well.
//      <SM6>      6/4/92    KW      (fau,P18) Added and equate for Civic_VidInDble to support Civic
//                                   II.
//      <SM5>     5/25/92    RB      Removed a forCyclone conditional. This should be the last one
//                                   left. Renamed MSCBank1Enable to MSCBank8M.
//      <SM4>     5/21/92    RB      Making changes for Cyclone. Some comments may be duplicated due
//                                   to the Pandora/Terror history. <P17> 5/13/92 KW (ag,H18) Added
//                                   Ponti Definitions. (BG,H17) Added symbol v2MicCtl to the VIA2
//                                   bit definitions. This is a microphone control bit that is
//                                   defined for Wombat. Also updated some comments from Eclipse and
//                                   Zydeco to the appropriate Quadra names. <P16> 4/16/92 KW (SWC,
//                                   H16) Set bufWorldSize to 8K so Macsbug won't load into the
//                                   middle of DBLite's sound buffer and get trashed when a sound is
//                                   played. <P15> 03/24/92 jmp Renamed one of the MMC registers to
//                                   something more appropriate (i.e., MMC_Interlace to
//                                   MMC_ClockSelect). <P14> 03/22/92 jmp Put back <P12>. <P13>
//                                   3/19/92 FU Rolled back changes in <P12>. <P12> 3/18/92 FU
//                                   (SWC,H15) Added SCSI DiskMode bit definitions for Niagra to the
//                                   VIA 1 list. <P11> 03/04/92 jmp Updated the comments and changed
//                                   the names of some of the Civic-related equates. <P10> 02/28/92
//                                   jmp (ejb) Turned off the DSP frame-interrupt enable bit so that
//                                   DSP driver doesn’t suffer frame overrun when it trys to boot the
//                                   DSP. <P9> 02/20/92 jmp (JC,H14) Define PatchFlags in unused by
//                                   of ROM header ($0014). Define PatchBits based on available
//                                   features in BBSStartup. Include support for Horror based and
//                                   Pandora (Cyclone) based ROMs. <P8> 2/19/92 chp (jmp,H13) Put a
//                                   “hasSonora1” conditional around the Sonora video control
//                                   register base address to reflect impending hardware changes to
//                                   Sonora. <P7> 02/07/92 jmp (HJR,H12) Added new Niagra Equates.
//                                   (SWC,H11) One more go-round on MSC configuration: RAM bank 1
//                                   needs to be disabled since there's only 2MB on DBLite LC.
//                                   (SWC,H10) Fixed the MSC configuration value: it needs to be
//                                   setup for a minimum amount of RAM so that the sound FIFO will
//                                   always exist in real RAM for BootBeep. (SWC,H9) Added an equate
//                                   for the default MSC configuration register value. Also, added
//                                   Civic and Civic-related equates for Cyclone. <P6> 2/5/92 RMP
//                                   Added MUNI equates. <P5> 1/21/92 mal Added PSC VIA2 equates <P4>
//                                   1/18/92 RMP Added PSC sound equates. <P3> 1/15/92 RP Fixed
//                                   header (sorry). <P2> 1/15/92 RP Added new VIA definition bits
//                                   and MMC equates.
//      <SM3>     5/17/92    kc      Roll in Horror Changes. Comments follow:
//      <H16>      4/8/92    SWC     Set bufWorldSize to 8K so Macsbug won't load into the middle of
//                                   DBLite's sound buffer and get trashed when a sound is played.
//      <H15>      3/3/92    SWC     Added SCSI DiskMode bit definitions for Niagra to the VIA 1
//                                   list.
//      <H14>     2/19/92    JC      Define PatchFlags in unused by of ROM header ($0014). Define
//                                   PatchBits based on available features in BBSStartup.  Include
//                                   support for Horror based and Pandora (Cyclone) based ROMs.
//      <H11>     1/23/92    SWC     One more go-round on MSC configuration: RAM bank 1 needs to be
//                                   disabled since there's only 2MB on DBLite LC.
//      <H10>     1/22/92    SWC     Fixed the MSC configuration value: it needs to be setup for a
//                                   minimum amount of RAM so that the sound FIFO will always exist
//                                   in real RAM for BootBeep.
//       <H9>     1/22/92    SWC     Added an equate for the default MSC configuration register
//                                   value.
//       <H8>    12/20/91    JC      Create common Via2/RBV offset equates and temporary redefinition
//                                   on Sonora Specific builds to only use RBV offsets
//       <H6>    12/03/91    jmp     Added various (but not yet complete) SonoraAddr and
//                                   Sonora-VDACAddr equates.  Sorry to have cancelled your check-out
//                                   swc, but we had pressing needs.
//       <H5>    11/26/91    jmp     Added equates for the GSC.
//       <H4>    11/25/91    SAM     Added Sonora specific equate for RAMSize reg.
//       <H2>      8/5/91    SWC     Added MSCPowerCycle, the offset to the power cycle register from
//                                   the base of the MSC.

//      <T21>      7/8/91    HJR     Rename JAWSAuxWaitS to JAWSEconoMode register to reflect its new
//                                   pupose in life.
//      <T20>     5/24/91    jmp     Added another VIA2, port A, bit-7 equate for Spike & Eclipse:
//                                   v2SyncOnGreen.  This bit allows us to enable & disable the
//                                   sync-on-green signal in ACDC.
//      <T19>     5/10/91    djw     Add sound input select bits for Eclipse in VIA2
//      <T18>      5/1/91    HJR     Added in register definitions for the MSC memory controller
//                                   (DB-Lite).
//      <T17>      4/1/91    BG      Modified the v2Keyswitch bit definition to agree with what it
//                                   will be on DVT Eclipse.
//      <T14>      3/3/91    BG      Added bit definition for Eclipse Keyswitch bit in VIA2.
//      <T12>     2/16/91    BG      Added Orwell constants to deal with 33MHz.
//       <T8>     1/18/91    CCH     Added equates for Spike's VIA2.
//       <T6>     11/7/90    BG      Made changes for new rev. of Orwell (2) permanent.
//      <SM2>     4/22/92    RB      Moved the start of the System heap in order to get some space
//                                   for vector tables. This movement of the heap from $2000 to $2100
//                                   is for experimentation and will need to be changed at a later
//                                   date.
//       <35>    12/31/91    RB      Renamed JAWSAuxWaitS to JAWSEconoMode to reflect its real
//                                   purpose.
//       <34>    12/29/91    RB      Updated some of the Terror constants.
//       <33>    10/28/91    SAM/KSM Rolled in Regatta file.
//       
//
//        <2>      8/8/91    SAM     (pdw, ag) Added some equates from HardwarePrivateEqu in 
//                                   TERROR.
//        <1>      8/8/91    SAM     Split off from 7.0 GM sources.
//
//
//       <32>     10/1/91    JSM     Don’t use eclipseDebug.
//       <31>     8/30/91    DTY     Complicate matters so onMac32 stuff doesn’t get defined for
//                                   onMac, onMacPP, or onMacHc. (Since these aren’t defined in
//                                   BBSStartup anymore, this is necessary.)
//       <30>     8/22/91    JSM     Clean up header.
//       <29>     7/24/91    MH      Added conditional wrapper(s) to prevent duplication of public
//                                   interface declarations: TimeSCSIDB
//       <28>     1/30/91    gbm     sab, #38: Change the ‘already including this file’ variable to
//                                   all uppercase (for security reasons)
//       <27>    11/26/90    gbm     (and bbm) On 7.0 (and other places eventually) HiIntMask will be
//                                   $0700 instead of $0300 all the time, not just when on a
//                                   non-Plus.
//       <26>    10/22/90    JJ      Rex V8: Added equates for V8 registers
//       <25>     9/24/90    BG      Added symbolic names for the Data and Instruction Cache enable
//                                   bits for the CACRs of various machines.
//       <24>     9/13/90    MSH     A couple of VIA2 assignments have changed for TIM.
//       <23>      9/1/90    BG      Updated and added various constants to agree with the EVT1
//                                   version of the Eclipse board.
//       <22>     7/11/90    gbm     Take out some things that are in SysEqu.a
//       <21>      7/6/90    CCH     Changed default ROM wait states and RAM refresh rate for
//                                   Eclipse.
//       <20>     6/27/90    CCH     Took out the conditionals around TestInRam!
//       <19>     6/27/90    CCH     TestInRAM macro gets compiled when eclipseDebug is set.
//       <18>     5/24/90    HJR     Update Machine equate to 7 instead of 6 for newer machines.
//       <16>      4/4/90    HJR     Clean up some build problems.
//       <15>      4/4/90    MSH     forrom removal.
//       <14>      4/4/90    MSH     Merged HardwareEqu.a back into HardwarePrivateEqu.a and
//                                   restructured/rewrote the resultant file. This action obsoletes
//                                   HardwareEqu.a. All future equate additions should be done to
//                                   HardwarePrivateEqu.a only.
//       <13>     3/29/90    MSH     Add VIA2 labels for Waimea.
//       <12>     3/22/90    JJ      Force definition of onElsie=0 if onElsie is undefined.
//       <11>     2/14/90    DAF     Added VISA register names.  Since Elsie isn't fully integrated,
//                                   it doesn't have  real feature conditional yet.
//       <10>      2/9/90    BG      Modified ORWELL_INIT value to reflect the parts being used on
//                                   the Eclipse prototype.
//        <9>      2/9/90    JJ      Added RvExp, offset of RBV Expansion Register in Elsie.
//        <8>      2/9/90    BG      Moved EQUs for the Eclipse VIA2 out of the -ELSEIF onEclipse-,
//                                   as those definitions will be used even if the -onEclipse-
//                                   conditional stuff is not used.
//        <7>      2/2/90    BG      Missed one re-definition in previous change.
//        <6>      2/2/90    BG      Modified some bits in the Eclipse VIA2 buffer A description to
//                                   have relevant mnemonic names.
//        <5>     1/31/90    BG      Added Orwell-specific register bit definitions, address offsets
//                                   and configuration register initial values.
//        <4>     1/30/90    BG      Added Eclipse-specific hardware constant definitions.
//        <3>     1/18/90    SWC     Updating FMCInit and FMCRPUInit with the final values.
//        <2>     1/12/90    CCH     Added missing ENDIF.
//        <1>     1/11/90    CCH     Moved in private equates from “HardwareEqu.a”.
//
//   NOTE:
//
//       For change history versions not mentioned in the above -Change History-, refer
//       to <Sources>:Interfaces:AIncludes:HardwareEqu.a.
//

#ifndef __INCLUDINGHARDWAREPRIVATEEQU__
#define __INCLUDINGHARDWAREPRIVATEEQU__ 1


                
//__________________________________________________________________________________________
//
// Welcome to the New Hardware Equates File.  By following some simple procedures this file
// can keep its youthful appearance for years to come.  This file is a recombination of
// HardwareEqu.a and HardwarePrivateEqu.a.  Everyone should be using this file only.  Please
// change any of your files that use either of the hardware equate files to use only this one.
// HardwareEqu.a will be left as an historical artifact for future generations.
//
// To help you navigate through this file use the "Mark" menu item, and please help to keep
// it current.  When you add a new section, add a handy mark to find it again.  Equates are
// grouped in a semi-logical way in the follwing order:
//
//       Chip Offsets - Register offsets for the 'standard' Mac peripheral chips.
//       Chip Offsets 2 - Register offsets for the 'non-standard' Mac peripheral chips.
//       VIA1 - Register offsets and pin descriptions.
//       VIA2 - Register offsets and pin descriptions.
//       RBV - Register offsets and pin descriptions.
//       VISA - Register offsets and pin descriptions.
//       Memory Controllers - Register definitions and miscellaneous equates.
//       Interrupts - Auto vector names and mask definitions.
//       Miscellaneous - The "Smorgasboard" of equates.
//       Old 16 Bit Equates - Machine dependent equates for Mac, MacPP, HcMac, and Mac16.
//
//
//__________________________________________________________________________________________





//__________________________________________________________________________________________
//
//
// Chip Offsets - Register offsets for "standard" Mac chips.  This includes the following:
//                IWM, SWIM, SCC, SCSI (with and without DMA), ASC.
//
//
//__________________________________________________________________________________________


//---------------------------------------------------
// IWM Offsets
//---------------------------------------------------

#define ph0L                     0                       // disk address offsets from base
#define ph0H                     $200
#define ph1L                     $400
#define ph1H                     $600
#define ph2L                     $800
#define ph2H                     $A00
#define ph3L                     $C00
#define ph3H                     $E00
#define mtrOff                   $1000
#define mtrOn                    $1200
#define intDrive                 $1400                   // enable internal drive address
#define extDrive                 $1600                   // enable external drive address
#define q6L                      $1800
#define q6H                      $1A00
#define q7L                      $1C00
#define q7H                      $1E00

#define IWMInitMode              $17                     // initial IWM mode setting              <3.5>

//---------------------------------------------------
//  SWIM offsets
//---------------------------------------------------

#define wData                    $0000                   //Write a data byte
#define wMark                    $0200                   //Write a mark byte
#define wCRC                     $0400                   //Write a 2-byte CRC (1 access does both)
#define wIWMConfig               (wCRC)                    //Set IWM configuration
#define wParams                  $0600                   //Set the 16 parameter registers
#define wPhase                   $0800                   //Set phase lines states and directions
#define wSetup                   $0A00                   //Set the current configuration
#define wZeroes                  $0C00                   //Mode reg: 1's clr bits, 0's=don't care
#define wOnes                    $0E00                   //Mode reg: 1's set bits, 0's=don't care
#define rData                    $1000                   //Read a data byte
#define rCorrection              (rData)                   //Read the correction factor
#define rMark                    $1200                   //Read a mark byte
#define rError                   $1400                   //Error register
#define rParams                  $1600                   //Parameters (16 bytes deep at this addr)
#define rPhase                   $1800                   //Phase lines states and directions
#define rSetup                   $1A00                   //Read the current configuration
#define rStatus                  $1C00                   //Status (returns current mode reg value)
#define rHandshake               $1E00                   //Handshake register


//---------------------------------------------------
// 8530 SCC Offsets
//---------------------------------------------------

#define aData                    6                       // offset for A channel data
#define aCtl                     2                       // offset for A channel control
#define bData                    4                       // offset for B channel data
#define bCtl                     0                       // offset for B channel control
#define sccData                  4                       // general offset for data from control
#define rxBF                     0                       // SCC receive buffer full
#define txBE                     2                       // SCC transmit buffer empty
#define RxCA                     0                       // Receive Character Available           


//---------------------------------------------------
// 53C80 SCSI Register Defs, Offsets
//---------------------------------------------------

#define sCDR                     $00                     // Current SCSI Read Data
#define sODR                     $00                     // Output data register
#define sICR                     $10                     // Initiator Command Register - READ/WRITE
#define iRST                     $80                     // *RST asserted
#define iAIP                     $40                     // arbitration in progress (read)
#define bAIP                     6                       // bit test for arbitration in progress
#define aTMD                     $40                     // assert Test Mode (write)
#define iLA                      $20                     // Lost arbitration (read)
#define bLA                      5                       // bit test for Lost Arbitration
#define aDIFF                    $20                     // assert Differential enable (write)
#define iACK                     $10                     // *ACK is asserted
#define iBSY                     $08                     // *BSY is asserted
#define iSEL                     $04                     // *SEL is asserted
#define iATN                     $02                     // *ATN is asserted
#define iDB                      $01                     // Data bus is asserted
#define sMR                      $20                     // Mode Register - READ/WRITE
#define iBDMA                    $80                     // Block Mode DMA
#define iTGT                     $40                     // Target Mode
#define iPTY                     $20                     // Enable Parity Checking
#define iIPTY                    $10                     // Enable Parity interrupt
#define iIEOP                    $08                     // Enable EOP interrupt
#define iMBSY                    $04                     // Monitor BSY
#define iDMA                     $02                     // DMA Mode
#define iARB                     $01                     // Arbitration
#define sTCR                     $30                     // Target Command Register - READ/WRITE
#define iREQ                     $08                     // Assert *REQ
#define iMSG                     $04                     // Assert *MSG
#define iCD                      $02                     // Assert C/*D
#define iIO                      $01                     // Assert I/*O
#define sCSR                     $40                     // Current SCSI Bus Status (READ)
#define aRST                     $80                     // *RST
#define aBSY                     $40                     // *BSY
#define bBSY                     6                       // bit test for *BSY
#define aREQ                     $20                     // *REQ
#define bREQ                     5                       // bit test for *REQ
#define aMSG                     $10                     // *MSG
#define bMSG                     4                       // bit test for *MSG
#define aCD                      $08                     // C/*D
#define bCD                      3                       // bit test for C/*D
#define aIO                      $04                     // I/*O
#define bIO                      2                       // bit test for I/*O
#define aSEL                     $02                     // *SEL
#define bSEL                     1                       // bit test for *SEL
#define aDBP                     $01                     // *DBP
#define sSER                     $40                     // Select Enable Register (WRITE)
#define sBSR                     $50                     // Bus & Status Register (READ)
#define iEDMA                    $80                     // End of DMA
#define bEDMA                    7                       // bit test for end of DMA
#define iDMAR                    $40                     // DMA Request
#define bDMAR                    6                       // bit test for DMA Req
#define iPERR                    $20                     // Parity Error
#define iIREQ                    $10                     // Interrupt Request
#define bIREQ                    4                       // bit test for interrupt
#define iPM                      $08                     // Phase Match
#define bPM                      3                       // bit test for Phase Match
#define iBERR                    $04                     // Bus Error
#define ATN                      $02                     // *ATN
#define ACK                      $01                     // *ACK
#define bACK                     0                       // bit test for ACK
#define sDMAtx                   $50                     // DMA Transmit Start (WRITE)
#define sIDR                     $60                     // Data input register (READ)
#define sTDMArx                  $60                     // Start Target DMA receive (WRITE)
#define sRESET                   $70                     // Reset Parity/Interrupt (READ)
#define sIDMArx                  $70                     // Start Initiator DMA receive (WRITE)


//---------------------------------------------------
//  SCSI DMA chip register offsets
//---------------------------------------------------

//  Note that the 53C80 registers are provided on the SCSI DMA chip.  The registers
//  described here are in addition to the 53C80 registers.

#define sDCTRL                   $80
#define bDMAEN                   0                       // bit to enable SCSI DMA
#define iDMAEN                   $0001                   // mask to enable SCSI DMA
#define bINTREN                  1                       // bit to enable SCSI DMA interrupts
#define iINTREN                  $0002                   // mask to enable SCSI DMA interrupts
#define bTIMEEN                  2                       // bit to enable watchdog timer intr's
#define iTIMEEN                  $0004                   // mask to enable watchdog timer intr's
#define bHSKEN                   3                       // bit to enable hardware-handshaking (write)
#define iHSKEN                   $0008                   // mask to enable hardware-handshaking (write)
#define bRESET                   4                       // bit to reset SCSI DMA chip (write)
#define iRESET                   $0010                   // mask to reset SCSI DMA chip (write)
#define bFIFO                    4                       // bit indicating bytes left in FIFO (read)
#define iFIFO                    $0010                   // mask indicating bytes left in FIFO (read)
#define bTEST                    5                       // bit to enable SCSI Test Mode (write)
#define iTEST                    $0020                   // mask to enable SCSI Test Mode (write)
#define bSCSIP                   6                       // bit indicating SCSI intr pending (read)
#define iSCSIP                   $0040                   // mask indicating SCSI intr pending (read)
#define bTIMEP                   7                       // bit indicating timer intr pending (read)
#define iTIMEP                   $0080                   // mask indicating timer intr pending (read)
#define bDMABERR                 8                       // bit indicating DMA bus error (read)
#define iDMABERR                 $0100                   // mask indicating DMA bus error (read)
#define iARBID                   $0E00                   // mask to get target ID for arbitration
#define bARBIDEN                 12                      // bit to enable hardware arbitration
#define iARBIDEN                 $1000                   // mask to enable hardware arbitration
#define bWONARB                  13                      // bit indicating successful arbitration
#define iWONARB                  $2000                   // mask indicating successful arbitration
#define iINFIFO                  $C000                   // mask to get bytes left in FIFO (read)

#define sDCNT                    $C0

#define sDADDR                   $100

#define sDTIME                   $140

#define sTEST                    $180


//__________________________________________________________________________________________
//
//
// Chip Offsets - Register offsets for "non standard" Mac chips.  This includes the following:
//                OSS and IOP.
//
//
//__________________________________________________________________________________________


//---------------------------------------------------
//  OSS (Operating System Support) Chip Address & Offsets
//---------------------------------------------------

#define OSSMskFirst              $000                    //offset to first interrupt mask register
#define OSSMskSlot9              (OSSMskFirst)             //offset to slot 9 interrupt mask register
#define OSSMskSlotA              $001                    //offset to slot A interrupt mask register
#define OSSMskSlotB              $002                    //offset to slot B interrupt mask register
#define OSSMskSlotC              $003                    //offset to slot C interrupt mask register
#define OSSMskSlotD              $004                    //offset to slot D interrupt mask register
#define OSSMskSlotE              $005                    //offset to slot E interrupt mask register
#define OSSMskPSwm               $006                    //offset to SWIM PIC interrupt mask register
#define OSSMskPScc               $007                    //offset to SCC PIC interrupt mask register
#define OSSMskSnd                $008                    //offset to Sound interrupt mask register
#define OSSMskScsi               $009                    //offset to SCSI interrupt mask register
#define OSSMsk60Hz               $00A                    //offset to 60 Hz interrupt mask register
#define OSSMskVia1               $00B                    //offset to VIA1 interrupt mask register
#define OSSMskRTC                $00C                    //offset to RTC interrupt mask register
#define OSSMskADB                $00D                    //offset to ADB interrupt mask register (not used)       <5.1>
#define OSSMskRPU                $00E                    //offset to RPU interrupt mask register                  <4.8>
#define OSSMskLast               (OSSMskRPU)               //offset to last interrupt mask register

#define rpuReset                 $010                    // RPU write offset to reset serial ptr                  <4.9>

#define OSSIntStat               $202                    //offset to interrupt status register. Bits are:         <3.7>
                                                    //  15:  interrupt 15 (spare) pending
                                                    //  14:  interrupt 14 (RPU) pending                      <4.8>
                                                    //  13:  interrupt 13 (spare) pending                    <5.1>
                                                    //  12:  interrupt 12 (RTC) pending
                                                    //  11:  interrupt 11 (VIA1) pending
                                                    //  10:  interrupt 10 (60 Hz) pending
                                                    //   9:  interrupt 9 (SCSI) pending
                                                    //   8:  interrupt 8 (sound) pending
                                                    //   7:  interrupt 7 (SCC PIC) pending
                                                    //   6:  interrupt 6 (SWIM PIC) pending
                                                    //   5:  interrupt 5 (slot E) pending
                                                    //   4:  interrupt 4 (slot D) pending
                                                    //   3:  interrupt 3 (slot C) pending
                                                    //   2:  interrupt 2 (slot B) pending
                                                    //   1:  interrupt 1 (slot A) pending
                                                    //   0:  interrupt 0 (slot 9) pending

//••••• NOTE: In the new OSS, the interrupt status register is a long word starting at $200.         <3.7>
//•••••       Since only the low-order word is currently used, making a single change here           <3.7>
//•••••       has less impact on the ROM sources.  When we permanently switch over to the            <3.7>
//•••••       new OSS hardware, then it may make sense to fix this equate and change all its         <3.7>
//•••••       uses from MOVE.Ws to MOVE.Ls.                                                          <3.7>

#define OSSRomCntl               $204                    //offset to ROM control register.  Bits are:
                                                    //  <to be specified - see Steve Ray's spec>             <2.0>

#define OSSPwrOff                (OSSRomCntl)              //power off is now a bit in the ROM control register     <5.1>
#define OSSPwrOffBit             7                       //    7:  write a 1 here to power off the machine        <2.1><3.7>

#define OSSCntrCntl              $205                    //offset to counter control register.  Bits are
                                                    //  7-2:  unused
                                                    //    1:  test control.  A 1 causes each 4 bit
                                                    //        counter segment to count in parallel
                                                    //    0:  counter hold.  A 1 holds current value
                                                    //        so all 64 bits can be read.  Hold doesn't
                                                    //        affect counting, though!

#define OSSInpStat               $206                    //offset to input status register.  Bits are
                                                    //  7-2:  not used, read as zero
                                                    //    1:  SCC write request. Not used if PIC present
                                                    //    0:  mini-phono device plugged in flag.  A 1
                                                    //        means a device IS plugged in.

#define OSS60HzAck               $207                    //offset to 'Clear 60 Hz interrupt flag' register.  Both <3.7>
                                                    // writes and reads clear it, so might as well write it.

#define OSSCounter               $208                    //offset to 64 bit counter register.  Low order 8
                                                    //.bits are always read as zero (maybe not in future...)

//  Bit numbers in OSS interrupt status register

#define OSSIntIOPSWIM            6                       //bit # of SWIM IOP in interrupt status register
#define OSSIntIOPSCC             7                       //bit # of SCC IOP in interrupt status register  
#define OSSIntSound              8                       //bit # of ASC in interrupt status register      
#define OSSIntSCSI               9                       //bit # of SCSI in interrupt status register
#define OSSIntVBL60Hz            10                      //bit # of 60Hz VBL in interrupt status register 
#define OSSIntVia1               11                      //bit # of VIA 1 in interrupt status register
#define OSSIntRTC                12                      //bit # of RTC in interrupt status register      
#define OSSIntADB                13                      //bit # of ADB in interrupt status register
#define OSSIntRPU                14                      //bit # of RPU in interrupt status register      <4.8>
#define OSSIntLast               14                      //bit # of last interrupt source

#define OSSRomInit               $D                      // initial value for ROM control register<3.5>


//---------------------------------------------------
//  IOP (Input Output Processor) Chip Offsets and bit definitions
//---------------------------------------------------

#define iopRamAddrH              ($0000-$20)               // high byte of shared RAM address register
#define iopRamAddrL              ($0002-$20)               // low byte of shared RAM address register
#define iopRamAddr               (iopRamAddrL-1)           // WORD access to shared RAM address register

#define iopRamData               ($0008-$20)               // shared RAM data register (byte, word, or long)
#define iopStatCtl               ($0004-$20)               // IOP Status and Control register

//   bit numbers within the iopStatCtl register
#define iopInBypassMode          0                       // IOP is in BYPASS mode
#define iopIncEnable             1                       // enable addr pointer increment
#define iopRun                   2                       // 0 -> reset IOP, 1 -> run IOP
#define iopGenInterrupt          3                       // interrupt the IOP
#define iopInt0Active            4                       // interrupt 0 active
#define iopInt1Active            5                       // interrupt 1 active
#define iopBypassIntReq          6                       // peripheral chip interrupt request in bypass mode
#define iopSCCWrReq              7                       // 0 -> SCC REQ active, 1 -> inactive

//   commands bytes to write to the iopStatCtl register
#define setIopIncEnable          ((1<<iopIncEnable)|(1<<iopRun))      
#define clrIopIncEnable          ((0<<iopIncEnable)|(1<<iopRun)) 
#define clrIopInt0               ((1<<iopInt0Active)|(1<<iopRun)|(1<<iopIncEnable))
#define clrIopInt1               ((1<<iopInt1Active)|(1<<iopRun)|(1<<iopIncEnable))
#define setIopGenInt             ((1<<iopGenInterrupt)|(1<<iopRun)|(1<<iopIncEnable))
#define resetIopRun              ((0<<iopRun)|(1<<iopInt0Active)|(1<<iopInt1Active)|(1<<iopIncEnable)) 
#define setIopRun                ((1<<iopRun)|(1<<iopInt0Active)|(1<<iopInt1Active)|(1<<iopIncEnable))


//__________________________________________________________________________________________
//
//
// VIA1 or Equivalent Pin Definitions and Register Offsets - Multiple names for the same pin
// are grouped together.  New definitions for VIA1 pins are added such that the grouping is
// maintained.
//
//
//__________________________________________________________________________________________

//---------------------------------------------------
// 6522 VIA1 (and VIA2) register offsets
//---------------------------------------------------

#define vBufB                    0                       // BUFFER B
#define vBufAH                   $200                    // buffer a (with handshake) [ Dont use! ]
#define vDIRB                    $400                    // DIRECTION B
#define vDIRA                    $600                    // DIRECTION A
#define vT1C                     $800                    // TIMER 1 COUNTER (L.O.)
#define vT1CH                    $A00                    // timer 1 counter (high order)
#define vT1L                     $C00                    // TIMER 1 LATCH (L.O.)
#define vT1LH                    $E00                    // timer 1 latch (high order)
#define vT2C                     $1000                   // TIMER 2 LATCH (L.O.)
#define vT2CH                    $1200                   // timer 2 counter (high order)
#define vSR                      $1400                   // SHIFT REGISTER
#define vACR                     $1600                   // AUX. CONTROL REG.
#define vPCR                     $1800                   // PERIPH. CONTROL REG.
#define vIFR                     $1A00                   // INT. FLAG REG.
#define vIER                     $1C00                   // INT. ENABLE REG.
#define vBufA                    $1E00                   // BUFFER A
#define vBufD                    (vBufA)                   // disk head select is buffer A          <3.5>

//---------------------------------------------------
// VIA IFR/IER bits
//---------------------------------------------------

#define ifCA2                    0                       // CA2 interrupt
#define ifCA1                    1                       // CA1 interrupt
#define ifSR                     2                       // SR shift register done
#define ifCB2                    3                       // CB2 interrupt
#define ifCB1                    4                       // CB1 interrupt
#define ifT2                     5                       // T2 timer2 interrupt
#define ifT1                     6                       // T1 timer1 interrupt
#define ifIRQ                    7                       // any interrupt


//---------------------------------------------------
// VIA1 Port A definitions
//---------------------------------------------------

#define vSound                   $7                      // sound volume bits (0..2)  (output)
            
#define vTestJ                   0                       // Burn In Test jumper       (input)
            
#define vCpuId0                  1                       // CPU Identification bit 0  (input)
#define vCpuId1                  2                       // CPU Identification bit 1  (input)
#define vSync                    3                       // Synchronous modem
#define vOverlay                 4                       // overlay bit (overlay when 1)
#define vCpuId2                  4                       // CPU Identification bit 2
#define vReqAEnable              4                       // enable ReqA into vSCCWrReq (PSC only)		<LW2>
#define vHeadSel                 5                       // head select line for Sony
#define vCpuId3                  6                       // CPU Identification bit 3
#define vRev8Bd                  6                       // =0 for rev 8 board>
#define vReqBEnable              6                       // enable ReqB into vSCCWrReq (PSC only)		<LW2>
#define vSCCWrReq                7                       // SCC write/request line

//---------------------------------------------------
// VIA1 Port B definitions
//---------------------------------------------------

#define vEclipseLED              0                       // flashable Eclipse LED (how quaint!)       <23>
#define vRTCData                 0                       // real time clock data
#define vRMP0                    0                       // Reserved for RMP (PSC only)
#define vRTCClk                  1                       // real time clock clock pulses
#define vRMP1                    1                       // Reserved for RMP (PSC only)
#define vRTCEnb                  2                       // clock enable (0 for enable)
#define vRMP2                    2                       // Reserved for RMP (PSC only)
#define vFDBInt                  3                       // Front Desk bus interrupt
#define vXcvrsesbit              3                       // Egret transceiver session bit         <6>
#define vSDMCable                3                       // SCSI DiskMode cable sense for Dartanian   <H15>
#define vCudaTREQ                3                       // Cuda transaction request input        <P2><SM4> rb
#define vSDMDiskID               4                       // DiskMode HD ID (bits 4-6) for Dartanian   <H15>
#define vFDesk1                  4                       // Front Desk bus state bit 0
#define vViafullbit              4                       // Egret via full bit                    <6>
#define vCudaBYTEACK             4                       // Cuda byte acknowledge output          <P2><SM4> rb
#define vFDesk2                  5                       // Front Desk bus state bit 1
#define vSyssesbit               5                       // Egret system session bit              <6><SM4> rb
#define vCudaTIP                 5                       // Cuda interface transaction in progress output <P2>
#define vAUXIntEnb               6                       // switch to A/UX interrupt scheme (output)  <23>
#define vPGCEnb                  6                       // Parity Generator/Checker enable (0 for enable)
#define vJMPDude6                6                       // Reserved for JMP (PSC only)
#define vPGCErr                  7                       // Parity Generator/Checker error    (input)
#define vSndEnb                  7                       // /sound enable (reset when 1)      (output)
#define vSWInt                   7                       // cause a software interrupt    (output)    <23>
#define vJMPDude7                7                       // Reserved for JMP (PSC only)



//__________________________________________________________________________________________
//
//
// VIA2 or Equivalent Pin Definitions and Register Offsets - Multiple names for the same pin
// are grouped together.  New definitions for VIA2 pins are added such that the grouping is
// maintained.
//
//
//__________________________________________________________________________________________

//---------------------------------------------------
// VIA2 Port A definitions
//---------------------------------------------------

#define v2IRQ1                   0                       // slot 1 interrupt
#define v2EnetIRQ                0                       // on-board ethernet                             <8><23>
#define v2IRQ2                   1                       // slot 2 interrupt
#define v2IRQ3                   2                       // slot 3 interrupt
#define v2IRQ4                   3                       // slot 4 interrupt
#define v2IRQ5                   4                       // slot 5 interrupt
#define v2IRQ6                   5                       // slot 6 interrupt
#define v2RAM0                   6                       // RAM size bit 0
#define v2LCDIRQ                 6                       // on-board LCD video
#define v2VideoIRQ               6                       // on-board video                                <8><23>
#define v2RAM1                   7                       // RAM size bit 1
#define v2CardIn                 7                       // on-board video
#define v2SyncOnGreen            7                       // for enabling/disabling Sync-on-Green (DAFB)   <T20>

//---------------------------------------------------
// VIA2 Port B definitions
//---------------------------------------------------

#define v2ConfigLE               0                       // DFAC config latch enable                      <T8>
#define v2CDis                   0                       // cache disable (when 1)    <3.3>
#define v2Keyswitch              0                       // 900/950 ONLY - keyswitch shadow bit (1=SECURE)<T14><T17><SM4> rb
#define v2BusLk                  1                       // Bus lockout
#define v2PMack                  1                       // Power manager handshake acknowledge
#define v2PowerOff               2                       // soft power off signal (when 0)
                                                    // (also 900/950 keyswitch OFF bit)              <T17><SM4> rb
#define v2PMreq                  2                       // Power manager handshake request
#define v2ConfigData             3                       // DFAC config data                              <T8>
#define v2FC3                    3                       // PMMU FC3 indicator
#define vFC3                     3                       // PMMU FC3 indicator
#define v2SndInSel0              3                       // Eclipse only - sound input select bit 0       <t19><H17>
#define v2ConfigClk              4                       // DFAC config clock                             <T8>
#define v2TM1A                   4                       // bit for NUBus
#define v2TM0A                   5                       // and another
#define v2Speed                  5                       // 25/33 Mhz 68040 input (0=25MHz, 1=33 MHz)
#define v2MicCtl                 5                       // microphone control on Wombats                 <H17><SM4> rb
#define v2HMMU                   5                       // HMMU 24/32                                    <15> HJR
#define v2CDis2                  6                       // On Tim the CDIS is on pb6                     <15> HJR
#define v2SndExt                 6                       // 1 = internal speaker, 0 = ext. audio
#define v2SndInSel1              6                       // Q900/950 only - sound input select bit 1      <t19><SM4> rb
#define v2VBL                    7                       // pseudo VBL signal
#define v2ModemRST               7                       // Modem.Reset                                   <15> HJR



                                                    // temporary Cyclone equates <SM4> rb, start, <SM5> rb


// <SM7> rb, • TEMP EQUATES

#define CycloneEVT1Reg           $A55A2800               // id which identifies an EVT1 cyclone in CPURegID <SM9> rb
#define PSCVIA2SIntEVT1          $000                    // Slot interrupt reg. offset                    <SM9> rb
#define PSCVIA2IFREVT1           $004                    // VIA2 interrupt flag reg. offset               <SM9> rb
#define PSCVIA2IEREVT1           $008                    // VIA2 interrupt enable reg. offset             <SM9> rb

#define PSCVIA2SInt              $1E00                   // Slot interrupt reg. offset                    <SM7> rb
#define PSCVIA2IFR               $1A00                   // VIA2 interrupt flag reg. offset               <SM7> rb
#define PSCVIA2IER               $1C00                   // VIA2 interrupt enable reg. offset             <SM7> rb


// PSC VIA2 Slot Interrupt Register equates
#define PSCSlotC                 3                       // slot C int.
#define PSCSlotD                 4                       // slot D int.
#define PSCSlotE                 5                       // slot E int.
#define PSCOVBVBL                6                       // on-board video vbl int.

// PSC VIA2 Interrupt Flag and Interrupt Enable Registers equates
#define PSCSCSI0                 0                       // SCSI int., same as bit 3
#define PSCSlot                  1                       // any slot int.
#define PSCMUNI                  2                       // MUNI int.
#define PSCSCSI3                 3                       // SCSI int.
#define PSCFDC                   5                       // floppy int.
#define PSCSNDFRM                6                       // sound frame int.
#define PSCANY                   7                       // any of the above
    
                                                    // <SM4> rb, end, <SM5> rb


//----------
//RBV (Ram Based Video) register definitions
//----------

#define RvDataB                  $000                    // VIA2 data reg. B equivalent   <v1.4><2.5>
#define RvExp                    $001                    // RBV Expansion Register        <3>
#define RvSInt                   $002                    // Slot interrupts reg.          <v1.4><2.5>
#define RvIFR                    $003                    // interrupt flag reg.           <v1.4><2.5>
#define RvMonP                   $010                    // monitor parameters reg.       <v1.4><2.5>
#define RvChpT                   $011                    // chip test reg.                <v1.4><2.5>
#define RvSEnb                   $012                    // Slot interrupt enable reg.    <v1.4><2.5>
#define RvIER                    $013                    // interrupt flag enable reg.    <v1.4><2.5>

//----------
//Common Via 2 and RBV (Ram Based Video) register offsets
//----------


#define Rv2DataB                 (vBufB|RvDataB)          // RBV/VIA2 data reg. B equivalent   <H8>
#define Rv2Exp                   (RvExp)                   // RBV Expansion Register            <H8>
#define Rv2SInt                  (RvSInt)                  // Slot interrupts reg.              <H8>
#define Rv2IFR                   (vIFR|RvIFR)             // RBV/VIA2 interrupt flag reg.      <H8>
#define Rv2MonP                  (RvMonP)                  // monitor parameters reg.           <H8>
#define Rv2ChpT                  (RvChpT)                  // chip test reg.                    <H8>
#define Rv2SEnb                  (RvSEnb)                  // Slot interrupt enable reg.        <H8>
#define Rv2IER                   (vIER|RvIER)             // iRBV/VIA2 interrupt enable reg.   <H8>

    
//  ======  VIA2 BufferB Equivalent   Address: $50026000  =====                                  <v1.4>
#define RvCDis                   0                       // cache disable (when 1)                    <v1.4><3.3>
#define RvBusLk                  1                       // Bus lockout                               <v1.4>
#define RvPowerOff               2                       // soft power off signal (when 0)            <v1.4>
#define RvCFlush                 3                       // Flush external cache (when 0)             <v1.4>
#define RvTM1A                   4                       // bit for NUBus                             <v1.4>
#define RvTM0A                   5                       // and another                               <v1.4>
#define RvSndExt                 6                       // 1 = internal speaker, 0 = ext. audio      <v1.4>
                                                    // jack in use                               <v1.4>
#define RvPGCTest                7                       // 1 = generate good parity, 0 = generate errors

//  ======  Future Expansion   Address: $50026001     =====                                      <v1.4>

//  ======  Slot Interrupts   Address: $50026002  =====                                          <v1.4>
#define RvIRQ1                   0                       // slot 1 interrupt                          <v1.4>
#define RvIRQ2                   1                       // slot 2 interrupt                          <v1.4>
#define RvIRQ3                   2                       // slot 3 interrupt                          <v1.4>
#define RvIRQ4                   3                       // slot 4 interrupt                          <v1.4>
#define RvIRQ5                   4                       // slot 5 interrupt                          <v1.4>
#define RvIRQ6                   5                       // slot 6 interrupt                          <v1.4>
#define RvIRQ0                   6                       // slot 0 interrupt or internal video        <v1.4>
                                                    // blanking interrupt                        <v1.4>
//RvResr         EQU         7                       ; reserved                                  <v1.4>

//  ======  Interrupt Flags   Address: $50026003  =====                                          <v1.4>
#define RvSCSIDRQ                0                       // 1 = SCSI DRQ interrupt                    <v1.4>
#define RvAnySlot                1                       // 1 = any slot(0-6).IRQ int                 <v1.4>
#define RvExpIRQ                 2                       // 1 = expansion int. (reserved)             <v1.4>
#define RvSCSIRQ                 3                       // 1 = SCSI IRQ interrupt                    <v1.4>
#define RvSndIRQ                 4                       // 1 = Apple Sound Chip interrup             <v1.4>
//RvResr         EQU         5                       ; reserved                                  <v1.4>
//RvResr         EQU         6                       ; reserved                                  <v1.4>
//RvSetClr       EQU         7                       ; on READ, 1 = any enable interrupt         <v1.4>
                                                    // on WRITE, 1 = 1-bits in bits 0-6 write 1's<v1.4>
                                                    //           0 = 1-bits in bits 0-6 write 0's<v1.4>

//  ======  Monitor Parameters   Address: $50026010   =====                                      <v1.4>
#define RvColor1                 0                       // (lsb) R/W 000 = 1bit, 001 = 2 bit         <v1.4>
#define RvColor2                 1                       //       R/W 010 = 4bit, 011 = 8 bit         <v1.4>
#define RvColor3                 2                       // (msb) Read 1xx = Reserved                 <v1.4>
#define RvMonID1                 3                       // READ 000,011,100=reserved; x01=15" monitor<v1.4>
#define RvMonID2                 4                       // 010=Mod'IIGSmonitor;110=MacII monitors    <v1.4>
#define RvMonID3                 5                       // 111= 9" build in monitor                  <v1.4>
#define RvVIDOff                 6                       // 1 = Video off                             <v1.4>
#define RvVID3St                 7                       // 1 = all video outputs tri-stated          <v1.4>

//  ======  Chip Test   Address: $50026011    =====                                              <v1.4>
#define RvC60                    0                       // 1 = C60 clock run 128 x normal            <v1.4>
#define RvSpd1                   1                       // (lsb) 00 = normal, 01=medium              <v1.4>
#define RvSpd2                   2                       // (msb) 10 = fast, 11 = very fast           <v1.4>
#define RvHndShk3                3                       // 1=VID.REQ & VID.RES tri-stated            <v1.4>
#define RvIOClk3                 4                       // 1=C16M, C8M, C3.7M tri-stated             <v1.4>
#define RvC30M                   5                       // 1=30.24 mHz clock for all monitors        <v1.4>
#define RvSDTClk                 6                       // 1 = Dot clock halted                      <v1.4>
#define RvTstRes                 7                       // 1 = reset video counters                  <v1.4>

//  ======  Slot Interrupts Enable   Address: $50026012   =====                                  <v1.4>
#define RvIRQ1En                 0                       // slot 1 interrupt enabled                  <v1.4>
#define RvIRQ2En                 1                       // slot 2 interrupt enabled                  <v1.4>
#define RvIRQ3En                 2                       // slot 3 interrupt enabled                  <v1.4>
#define RvIRQ4En                 3                       // slot 4 interrupt enabled                  <v1.4>
#define RvIRQ5En                 4                       // slot 5 interrupt enabled                  <v1.4>
#define RvIRQ6En                 5                       // slot 6 interrupt enabled                  <v1.4>
#define RvIRQ0En                 6                       // slot 0 interrupt or internal video enabled<v1.4>
//RvSetClr       EQU         7                       ; on READs, always reads 0                  <v1.4>
                                                    // on WRITEs, 1 = 1-bits in bits 0-6 write 1's<v1.4>
                                                    //           0 = 1-bits in bits 0-6 write 0's<v1.4>

//  ======  Interrupt Flags Enable   Address: $50026013   =====
#define RvSCSIDRQEn              0                       // 1 = SCSI DRQ interrupt enabled            <v1.4>
#define RvAnySlotEn              1                       // 1 = any slot(0-6).IRQ int. enabled        <v1.4>
#define RvExpIRQEn               2                       // 1 = expansion int. (reserved) enabled     <v1.4>
#define RvSCSIRQEn               3                       // 1 = SCSI IRQ interrupt enabled            <v1.4>
#define RvSndIRQEn               4                       // 1 = Apple Sound Chip interrupt enabled    <v1.4>
//RvResr         EQU         5                       ; reserved                                  <v1.4>
//RvResr         EQU         6                       ; reserved                                  <v1.4>
//RvSetClr       EQU         7                       ; on READs, always reads 1                  <v1.4>
                                                    // on WRITEs, 1 = 1-bits in bits 0-6 write 1's<v1.4>
                                                    //           0 = 1-bits in bits 0-6 write 0's<v1.4>

//----------
// VDAC register definitions
//----------

#define vDACwAddReg              $0000                   //   offset from vDACBase for write address reg
#define vDACrAddReg              $000C                   //   offset from vDACBase for read address register <v4.2>
#define vDACwDataReg             $0004                   //   offset from vDACBase for write data reg

#define vDACPixRdMask            $0008                   //   offset from vDACBase for pixel mask


//__________________________________________________________________________________________
//
//
// VISA Pin Definitions and Register Offsets - Multiple names for the same pin are grouped
// together.  New definitions for VISA pins are added such that the grouping is maintained.
//
//
//__________________________________________________________________________________________
                

//----------
// VISA register definitions - generally, these equates are a precise subset 
//       of the RBV equates.  
//----------

// these registers are accessed off of VIA1 lomem
#define VsData1A                 $1E00                   // VIA1 data reg A
#define VsData1B                 $0000                   // VIA1 data reg B

// these registers are accessed off of VISA lomem
#define VsData2B                 $000                    // VIA2 data reg B equivalent
#define VsExp                    $001                    // VISA Expansion Register
#define VsSInt                   $002                    // Slot Interrupt Register
#define VsIFR                    $003                    // Interrupt Flag Register
#define VsMonP                   $010                    // Monitor Parameters Register
#define VsSEnb                   $012                    // Slot Interrupt Enable Register
#define VsIER                    $013                    // Interrupt Flag Enable Register

//  ======  VIA2 BufferB Equivalent   Address: $50026000  =====
//*VsResr        EQU         0                       ; reserved
//*VsResr        EQU         1                       ; reserved
//*VsResr        EQU         2                       ; reserved
#define VsFC3                    3                       // select 32-bit map.  0=24 bit, 1=32 bit
//*VsResr        EQU         4                       ; reserved
//*VsResr        EQU         5                       ; reserved
#define VsSndExt                 6                       // Always reads as 1 - play sounds in Mono
//*VsResr        EQU         7                       ; reserved

//  ======  Future Expansion   Address: $50026001     =====
#define VsA2Mode                 0                       // 0=512*384 mode, 1=560*384 mode
#define VsVResEn                 1                       // 1=enable vertical counter reset for video genlock
#define VsFlWrEn                 2                       // 1=enable writes to flash EEPROM
#define Vs1BV                    3                       // 1=low base for 1-bit mode, 0=high base
#define VsPg2                    4                       // 1=main video page, 0=sec video page
//*VsResr        EQU         5                       ; reserved
#define VsSiz0                   6                       // RAM size control bit 00=1MB, 01=1.5MB
#define VsSiz1                   7                       //   10=3MB,11=9MB           

//  ======  Slot Interrupts   Address: $50026002  =====
//*VsResr        EQU         0                       ; reserved
//*VsResr        EQU         1                       ; reserved
//*VsResr        EQU         2                       ; reserved
//*VsResr        EQU         3                       ; reserved
//*VsResr        EQU         4                       ; reserved
#define VsSIRQ                   5                       // expansion slot interrupt
#define VsVBLInt                 6                       // slot zero (built-in) VBL interrupt
//*VsResr        EQU         7                       ; reserved


//  ======  Interrupt Flags   Address: $50026003  =====
#define VsSCSIDRQ                0                       // 1 = SCSI DRQ interrup
#define VsAnySlot                1                       // 1 = any slot(0-6).IRQ int
//*VsResr        EQU         2                       ; reserved
#define VsSCSIRQ                 3                       // 1 = SCSI IRQ interrupt
#define VsSndIRQ                 4                       // 1 = Apple Sound Chip interrupt
//RvResr         EQU         5                       ; reserved
//RvResr         EQU         6                       ; reserved
#define RvSetClr                 7                       // on READ, 1 = any enabled interrupt
                                                    // on WRITE, 1 = 1-bits in bits 0-6 write 1's
                                                    //           0 = 1-bits in bits 0-6 write 0's

//  ======  Monitor Parameters   Address: $50026010   =====
//*VsResr        EQU         0                       ; (lsb)
#define VsColor                  1                       // (compat w/RBV) R/W 000 = 1bit, R/W 010 = 4bit
//*VsResr        EQU         2                       ; (msb) 
#define VsMonConn                3                       // (lsb)1=no monitor connected
//*VsResr        EQU         4                       ; (compat w/RBV)
#define VsMonSel                 5                       // (msb) Monitor select 1=Jersey, 0=Rubik
//*VsResr        EQU         6                       ; reserved
//*VsResr        EQU         7                       ; reserved


//  ======  Slot Interrupts Enable   Address: $50026012   =====
//*VsResr        EQU         0                       ; reserved
//*VsResr        EQU         1                       ; reserved
//*VsResr        EQU         2                       ; reserved
//*VsResr        EQU         3                       ; reserved
//*VsResr        EQU         4                       ; reserved
#define VsExtIRQEn               5                       // expansion slot interrupt enabled
#define VsIntIRQEn               6                       // internal video interrupt enabled
#define VsSetClr                 7                       // on READs, always reads 0
                                                    // on WRITEs, 1 = 1-bits in bits 0-6 write 1's
                                                    //           0 = 1-bits in bits 0-6 write 0's

//  ======  Interrupt Flags Enable   Address: $50026013   =====
#define VsSCSIDRQEn              0                       // 1 = SCSI DRQ interrupt enabled
#define VsAnySlotEn              1                       // 1 = any slot(0-6).IRQ int. enabled
//*VsResr        EQU         2                       ; reserved
#define VsSCSIRQEn               3                       // 1 = SCSI IRQ interrupt enabled
#define VsSndIRQEn               4                       // 1 = Apple Sound Chip interrupt enabled
//VsResr         EQU         5                       ; reserved
//VsResr         EQU         6                       ; reserved
//RvSetClr       EQU         7                       ; on READs, always reads 1
                                                    // on WRITEs, 1 = 1-bits in bits 0-6 write 1's
                                                    //           0 = 1-bits in bits 0-6 write 0's


//----------
// V8 register definitions - generally compatible with the VISA equates above, but a few equates
//   have changed names.
//----------

// these registers are accessed off of the V8 lomem
#define V8Exp                    $001                    // V8 Expansion Register
#define V8SInt                   $002                    // V8 Slot Interrupt Register
#define V8MonP                   $010                    // Monitor Parameters Register
#define V8SEnb                   $012                    // Slot Interrupt Enable Register

//  ======  Future Expansion   Address: $50F26001     =====
#define V8A2Mode                 0                       // 0=512*384 mode, 1=560*384 mode
#define V8512Row                 1                       // 1=V8 rowbytes is 256, 0=rowbytes is 512
#define V8vRAMIn                 2                       // 1=refresh video from vRAM, 0=refresh from dRAM
//*V8Resr        EQU         3                       ; no 1BV on V8
//*V8Resr        EQU         4                       ; no VP2 on V8
#define V8Siz0                   5                       // RAM size control bit 0
#define V8Siz1                   6                       // RAM size control bit 1
#define V8Siz2                   7                       // RAM size control bit 2    

//  ======  Monitor Parameters   Address: $50F26010   =====
#define V8Col0                   0                       // Video depth control bit 0
#define V8Col1                   1                       // Video depth control bit 1
#define V8Col2                   2                       // Video depth control bit 2
#define V8MonID1                 3                       // Monitor sense ID bit 1
#define V8MonID2                 4                       // Monitor sense ID bit 2
#define V8MonID3                 5                       // Monitor sense ID bit 3
//*VsResr        EQU         6                       ; reserved
//*VsResr        EQU         7                       ; reserved

//  ======  Slot Interrupts Enable   Address: $50F26012   =====
//*V8Resr        EQU         0                       ; reserved
//*V8Resr        EQU         1                       ; reserved
//*V8Resr        EQU         2                       ; reserved
//*V8Resr        EQU         3                       ; reserved
//*V8Resr        EQU         4                       ; reserved
#define V8ExtIRQEn               5                       // expansion slot interrupt enabled
#define V8IntIRQEn               6                       // internal video interrupt enabled
//*V8Resr        EQU         7                       ; reserved


//----------
// Elsie VDAC register definitions
//----------

// VISA/Bt450 registers

#define VsDACwAddReg             $0000                   //   offset from vDACBase for write address reg
#define VsDACwDataReg            $0001                   //   offset from vDACBase for write data reg

// V8/Ariel registers

#define V8DACrAddReg             $0000                   // offset for read address reg
#define V8DACwAddReg             $0000                   // offset for write address reg
#define V8DACrDataReg            $0001                   // offset for read data reg
#define V8DACwDataReg            $0001                   // offset for write data reg
#define V8DACrCntlReg            $0002                   // offset for read control reg
#define V8DACwCntlReg            $0002                   // offset for write control reg
#define V8DACrKeyReg             $0003                   // offset for read key color reg
#define V8DACwKeyReg             $0003                   // offset for write key color reg

#define V8vRAMBase               $50F40000               // base address of V8 VRAM, if present

// End of VISA changes                               <4> <cv>

                
//----------
// DAFB register definitions (offsets from DAFBBase in ProductInfo) ($F980 0000)
//----------

#define DAFB_BaseOffset              $0              // DAFB offset from DAFBBase
#define DAFB_ParmSize                $5              // size of DAFB programmed subset
#define DAFB_NumRegs                 ((16-4))          // Number of DAFB registers (Color Regs are really vRAM).    

#define DAFB_VidBaseHi               $0              // DAFB video base address, bits 20:9
#define DAFB_VidBaseLo               $4              // DAFB video base address, bits 8:5 (4:0 always zero)
#define DAFB_RowWords                $8              // DAFB rowlongs size
#define DAFB_ClkCfg                  $C              // DAFB clock configuration 
#define DAFB_Config                  $10             // DAFB general configuration
#define DAFB_BlkWrtEn                $14             // DAFB block write enable
#define DAFB_PgMdEn                  $18             // DAFB page mode enable
#define DAFB_Sense                   $1C             // DAFB sense line
#define DAFB_Reset                   $20             // DAFB reset control
#define DAFB_SCSIch0                 $24             // Turbo SCSI channel 0 control (not used)
#define DAFB_SCSIch1                 $28             // Turbo SCSI channel 1 control (not used)
#define DAFB_Test                    $2C             // DAFB test control

#define DAFB_CRB0                    $30             // vRAM Color Register, bank 0
#define DAFB_CRB1                    $34             // vRAM Color Register, bank 1
#define DAFB_CRB2                    $38             // vRAM Color Register, bank 2
#define DAFB_CRB3                    $3C             // vRAM Color Register, bank 3

//----------
// Swatch (in DAFB) register definitions (offsets from DAFBBase in ProductInfo)
//----------

#define Swatch_BaseOffset            $100            // Swatch offset from DAFBBase
#define Swatch_BaseOffset1           $124            // parameter offset
#define Swatch_ParmSize1             $12             // size of Swatch parameter list
#define Swatch_NumRegs               30              // Number of Swatch registers.

#define Swatch_Mode                  $100            // Swatch general control
#define Swatch_IntMsk                $104            // Swatch interrupt control
#define Swatch_IntStat               $108            // Swatch interrupt status
#define Swatch_ClrCrsrInt            $10C            // Swatch clear cursor interrupt (not used in this form)
#define Swatch_ClrAnimInt            $110            // Swatch clear animation interrupt (not used in this form)
#define Swatch_ClrVBLInt             $114            // Swatch clear VBL interrupt (not used in this form)
#define Swatch_CrsrLine              $118            // Swatch cursor interrupt trigger line
#define Swatch_AnimLine              $11C            // Swatch animation interrupt trigger line
#define Swatch_Test                  $120            // Swatch counter test
#define Swatch_HSyncRegs             $124            // Swatch horizontal sync registers (set as a group)
#define Swatch_HSerr                 $124            //   HSerr
#define Swatch_Hlfln                 $128            //   Hlfln
#define Swatch_HEq                   $12C            //   HEq
#define Swatch_HSP                   $130            //   HSP
#define Swatch_HBWay                 $134            //   HBWay
#define Swatch_HBrst                 $138            //   HBrst
#define Swatch_HBP                   $13C            //   HBP
#define Swatch_HAL                   $140            //   HAL
#define Swatch_HFP                   $144            //   HFP
#define Swatch_HPix                  $148            //   HPix
#define Swatch_VSyncRegs             $14C            // Swatch vertical sync registers (set as a group)
#define Swatch_VHLine                $14C            //   VHLine
#define Swatch_VSync                 $150            //   VSync
#define Swatch_VBPEq                 $154            //   VBPEq
#define Swatch_VBP                   $158            //   VBP
#define Swatch_VAL                   $15C            //   VAL
#define Swatch_VFP                   $160            //   VFP
#define Swatch_VFPEq                 $164            //   VFPEq
#define Swatch_TimeAdj               $168            // Swatch miscellaneous timing adjust
#define Swatch_ActLine               $16C            // Swatch active video line (read-only)
                
//----------
// ACDC register definitions (offsets from DAFBBase in ProductInfo, also in vDACBase)
//----------
                
#define ACDC_AddrReg                 $200            // set position in ACDC internal RAM
#define ACDC_DataReg                 $210            // read/write data in ACDC internal RAM
#define ACDC_ConfigReg               $220            // ACDC offset from DAFBBase
#define ACDC_ParmSize                $1              // size of ACDC parameter list


//----------
// National Clock Chip register definitions (offsets from DAFBBase in ProductInfo)
//----------

#define Clk_BaseOffset               $300            // National offset from DAFBBase
#define Clk_ParmSize                 $10             // size of National parameter list
#define Clk_ParmSize1                $0A             // (Once programmed, the last six bytes are always the same.)

//----------
// Misc. DAFB Parms
//----------
#define Misc_ParmSize                $4              // Just for consistency with other DAFB parms.


//----------
// GSC register definitions (offsets from VDACAddr in ProductInfo) ($50F2 0000)                  <H5> jmp 
//----------
#define GSCDeviceID              $00                     // Device revision register; read only.
#define GSCPanelID               $01                     // “Senseline” read/write register.
#define GSCPanelControl          $02                     // Switches r/w sense of PanelID reg.
#define GSCPanelSetup            $03                     // Panel intialization register.
#define GSCGrayScale             $04                     // The depth-switching register.
#define GSCPolyAdj               $05                     // Allows for grayscale adjustment.
#define GSCPanelAdj              $06                     // Allows for panel adjustment.
#define GSCACDClk                $07                     // Who knows?
#define GSCRefreshRate           $08                     // Refresh cycles per scanline.
#define GSCBlankShade            $09                     // Shade of gray for depth switches.
#define GSCPanelSkew             $0A                     // Who knows?

#define GSCDiag0                 $1D                     // Undocumented “diagnostic” registers.
#define GSCDiag1                 $1E
#define GSCDiag2                 $1F


//----------
// Sonora register definitions (offsets from SonoraAddr in ProductInfo) ($50F0 0000)             <H4><H6>
//----------

#define SonoraVIA2Base           $26000                  // Base address of VIA2

#define SonoraVIA2Data           $00                     // VIA2 Data Register
#define SonoraRAMSize            $01                     // DRAM config
#define SonoraSlotIFR            $02                     // Slot Interrupt Flags Register
#define SonoraVIA2IFR            $03                     // VIA2 Interrupt Flags Register
#define SonoraVRAMSize           $04                     // VRAM config
#define SonoraSpeedReg           $05                     // System CPU Speed (waitstate) Register
#define SonoraSlotIER            $12                     // Slot Interrupt Enable Register
#define SonoraVIA2IER            $13                     // Interrupt Flag Register
#define SonoraVdCtlBase          $28000                  // Base address of video control registers

#define SonoraVdModeReg          $00                     // Monitor code and video blanking register
#define SonoraVdColrReg          $01                     // Framebuffer pixel depth control register
#define SonoraVdSenseRg          $02                     // Senseline register

// Bits for Misc Sonora Regs
//
#define SonoraSetClr             7                       // on WRITEs, 1 = 1-bits in bits 0-6 write 1's
                                                    //            0 = 1-bits in bits 0-6 write 0's

// Bits for SonoraSlotIER 
//
#define SonoraVBLIRQEn           6                       // Enable/Disable built-in video VBL

//----------
// Ariel register definitions (offsets from VDACAddr in ProductInfo) ($50F2 4000)                <H6>
//----------
#define ArielAddrReg             0                       // Offset to r/w address register
#define ArielDataReg             1                       // Offset to r/w data register
#define ArielConfigReg           2                       // Offset to r/w control register
#define ArielKeyReg              3                       // Offset to r/w key color register


//----------
// MMC register definitions (offsets from MMCAddr in ProductInfo) ($50F3 0400)               <P2><SM4> rb, start
//----------

#define MMC_DRAMspeed0           $00                     // DRAM timing register 0 [M0].
#define MMC_DRAMspeed1           $04                     // DRAM timing register 1 [M1].

#define MMC_CPUspeed0            $08                     // Clock speed 0 [M2].
#define MMC_CPUspeed1            $0C                     // Clock speed 1 [M3].

#define MMC_ROMspeed0            $10                     // ROM cycle time 0 [M4].
#define MMC_ROMspeed1            $14                     // ROM cycle time 1 [M5].
#define MMC_ROMspeed2            $18                     // ROM cycle time 2 [M6].

#define MMC_DSPspeed             $1C                     // DSP clock speed [M7].

#define MMC_DRAMwidth0           $20                     // DRAM width 0 [M8].
#define MMC_DRAMwidth1           $24                     // DRAM width 1 [M9].
#define MMC_DRAMwidth2           $28                     // DRAM width 2 [M10].
#define MMC_DRAMwidth3           $2C                     // DRAM width 3 [M11].

#define MMC_EPROMmode            $30                     // EPROM mode [M12].

#define MMC_DRAMrange2           $34                     // DRAM bank range 0 [M13].
#define MMC_DRAMrange1           $38                     // DRAM bank range 1 [M14].
#define MMC_DRAMrange0           $3C                     // DRAM bank range 2 [M15].

#define MMC_CPUID0               $40                     // CPU ID 0 [M16].
#define MMC_CPUID1               $44                     // CPU ID 1 [M17].

#define MMC_ClockSelect          $48                     // Endeavor Input Clock Select (NTSC/PAL) [M18].

#define MMC_Bypass               $4C                     // RGB or Composite bypass [M19].

//----------
// MUNI (NuBus) register definitions                                                             <P6>
//----------

// <SM7> rb, • TEMP for EVT1                         ;                                           <SM7> rb

#define MUNIBaseEVT1             $50F30800               // Base address of Muni for EVT1             <SM9> rb


#define MUNIBase                 $50F30000               // Base address of Muni.                     <SM7> rb

    
    
#define MUNI_IntCntrl            $00                     // Interrupt control register.
#define MUNI_IntStatus           $04                     // Interrupt status register.
#define MUNI_Control             $08                     // System control register.
#define MUNI_BlkAttmpt           $0C                     // Block attempt register.
#define MUNI_Status              $10                     // Status register.
#define MUNI_Test                $14                     // Test control register.

//----------
// Civic register definitions (offsets from CivicAddr in ProductInfo) ($50F3 6000)
//----------

#define Civic_VBLInt             $000                    // Read-only VBL flag register
#define Civic_VBLEnb             $110                    // Enables VBL interrupt.
#define Civic_VBLClr             $120                    // Clear VBL interrupt.

#define Civic_Enable             $004                    // Enables Civic’s timing generator (Casio).
#define Civic_Reset              $10C                    // Resets Casio.

#define Civic_VDCInt             $008                    // Read-only VDC flag register.
#define Civic_VDCClr             $00C                    // Clears VDC interrupt.
#define Civic_VDCEnb             $010                    // Enables VDC interrupt.
#define Civic_VDCClk             $018                    // Enables VDC clock.

#define Civic_VidInSize          $014                    // Controls video-in Rows (1024 vs. 1536 bytes).

#define Civic_VidInDble          $208                    // Controls whether Civic Doubles each Video-in Field

#define Civic_ScanCtl            $01C                    // Controls progressive vs. interlaced scans.

#define Civic_GSCDivide          $020                    // Controls graphics clock divide count.
#define Civic_VSCDivide          $02C                    // Controls video-in clock divide count.

#define Civic_VRAMSize           $040                    // Controls VRAM sizing (1 vs. 2 Mbytes).

#define Civic_RfrshCtl           $044                    // Controls the refresh mode.

#define Civic_BusSize            $04C                    // Controls the bus size (32 vs. 64 bits).

#define Civic_SpeedCtl           $050                    // Controls the timing (25 vs. 33 MHz).

#define Civic_ConvEnb            $054                    // Enables convolution.

#define Civic_ReadSense          $088                    // Sense-line registers.
#define Civic_SenseCtl           $058                    //
#define Civic_Sense0             $05C                    //
#define Civic_Sense1             $060                    //
#define Civic_Sense2             $064                    //
#define Civic_SenseTst           $068                    //

#define Civic_SyncClr            $06C                    // Disables RGB (Sync) output. 

#define Civic_BaseAddr           $0C0                    // Base address of active video.
#define Civic_RowWords           $094                    // Row long words of active video.

#define Civic_AdjF1              $128                    // Timing adjust registers.
#define Civic_AdjF2              $124                    // 
#define Civic_Piped              $440                    //

#define Civic_HSerr              $180                    // Horizontal timing registers.
#define Civic_HlfLn              $280                    //
#define Civic_HEq                $2C0                    //
#define Civic_HSP                $300                    //
#define Civic_HBWay              $340                    //
#define Civic_HAL                $380                    //
#define Civic_HFP                $3C0                    //
#define Civic_HPix               $400                    //

#define Civic_VHLine             $480                    // Vertical timing registers.            
#define Civic_VSync              $4C0                    // 
#define Civic_VBPEqu             $500                    // 
#define Civic_VBP                $540                    //
#define Civic_VAL                $580                    // 
#define Civic_VFP                $640                    // 
#define Civic_VFPEqu             $680                    // 
#define Civic_CurLine            $6C0                    //

#define Civic_VInHAL             $1C0                    // Video-in timing registers.
#define Civic_VInHFPD            $200                    //
#define Civic_VInHFP             $240                    //
#define Civic_VInVAL             $5C0                    //
#define Civic_VInVFP             $600                    //

#define Civic_HLDB               $114                    // Horizontal test/control registers.
#define Civic_HHLTB              $118                    // 
#define Civic_HActHi             $11C

#define Civic_VLDB               $100                    // VSync test/control registers.
#define Civic_VHLTB              $104                    //
#define Civic_VActHi             $108                    //

#define Civic_TestEnb            $12C                    // Enables Casio test mode.
#define Civic_CntTest            $140                    // Count test register.

//----------
// Sebastian register definitions (offsets from SebastianAddr in ProductInfo) ($50F3 0000)
//----------

#define SebastAddrReg            $000                    // CLUT/DAC Address register.
#define SebastDataReg            $010                    // CLUT/DAC Data register.
#define SebastPCBR               $020                    // CLUT/DAC Pixel Bus Control register.

//----------
// Endeavor register definitions
//----------

#define Endeavor                 $50F2E000               // Base address of Endeavor in Cyclone.

#define EndeavorM                $000                    // 8-bit numerator.
#define EndeavorN                $010                    // 8-bit denominator.
#define EndeavorClk              $020                    // Clock select (A or B).


                                                    //                               <SM4> rb, end
//----------
// MSC register definitions (offsets from MSCAddr in ProductInfo) ($50F2 6000)
//----------

#define MSCSlotIFR               $02                     // slots interrupt flags
#define MSCVIA2IFR               $03                     // VIA 2 interrupt flags
#define MSCConfig                $10                     // RAM, clock configuration
#define MSCSlotIER               $12                     // slots interrupt enables
#define MSCVIA2IER               $13                     // VIA 2 interrupt enables
#define MSCClkCntl               $21                     // peripherals clock control
#define MSCSndCntl               $22                     // sound control
#define MSCFlashWrEnb            $23                     // flash ROM write enable
#define MSCPowerCycle            ($50FA0000-$50F26000)     // CPU power off control register            <H2>

//  ======  VIA2 BufferB Equivalent      Address: $50F26000   =====
#define MSCExpansion             0                       // 0 = enable on-board external cache (not currently used)
//v2PMack        EQU         1                       ; Power manager handshake acknowledge
//v2PMreq        EQU         2                       ; Power manager handshake request
//reserved3      EQU         3                       ; reserved
//reserved4      EQU         4                       ; reserved
//reserved5      EQU         5                       ; reserved
//reserved6      EQU         6                       ; reserved
//reserved7      EQU         7                       ; reserved

//  ======  Slot Interrupt Flags         Address: $50F26002   =====
//reserved0      EQU         0                       ; reserved
//reserved1      EQU         1                       ; reserved
//reserved2      EQU         2                       ; reserved
//reserved3      EQU         3                       ; reserved
//reserved4      EQU         4                       ; reserved
//RvIRQE         EQU         5                       ; slot E interrupt
//RvIRQLCD       EQU         6                       ; LCD display VBL interrupt
//reserved7      EQU         7                       ; reserved

//  ======  VIA 2 Interrupt Flags        Address: $50F26003   =====
//RvSCSIDRQ      EQU         0                       ; 1 = SCSI DRQ interrupt
//RvAnySlot      EQU         1                       ; 1 = any slot(0-6).IRQ int
//reserved2      EQU         2                       ; reserved
//RvSCSIRQ       EQU         3                       ; 1 = SCSI IRQ interrupt
//RvSndIRQ       EQU         4                       ; 1 = Apple Sound Chip interrup
//reserved5      EQU         5                       ; reserved
//reserved6      EQU         6                       ; reserved
//RvSetClr       EQU         7                       ; on READ, 1 = any enable interrupt

//  ======  MSC Configuration            Address: $50F26010   =====
#define MSC25MHz                 0                       // 1 = 25MHz system, 0 = 33MHz system
#define MSCEconoBit              1                       // 1 = econo-mode enabled (switches to 16MHz)
#define MSCFastROM               2                       // 1 = 100ns ROMs installed, 0 = 120ns ROMs installed
//reserved3      EQU         3                       ; reserved
#define MSCBank8M                4                       // 1 = banks 4-7 are 8MB, 0=banks 4-7 are 2MB
#define MSCSize0                 5                       // RAM size bit
#define MSCSize1                 6                       // RAM size bit
#define MSCSize2                 7                       // RAM size bit

//  ======  Slot Interrupt Enables       Address: $50F26012   =====
//reserved0      EQU         0                       ; reserved
//reserved1      EQU         1                       ; reserved
//reserved2      EQU         2                       ; reserved
//reserved3      EQU         3                       ; reserved
//reserved4      EQU         4                       ; reserved
//RvIRQEEn       EQU         5                       ; slot E interrupt enabled
//RvIRQLCDEn     EQU         6                       ; LCD display VBL interrupt enabled
//RvSetClr       EQU         7                       ; on READs, always reads 0

//  ======  VIA 2 Interrupt Enables      Address: $50F26013   =====
//RvSCSIDRQEn    EQU         0                       ; 1 = SCSI DRQ interrupt enabled
//RvAnySlotEn    EQU         1                       ; 1 = any slot(0-6).IRQ int. enabled
//reserved2      EQU         2                       ; reserved
//RvSCSIRQEn     EQU         3                       ; 1 = SCSI IRQ interrupt enabled
//RvSndIRQEn     EQU         4                       ; 1 = Apple Sound Chip interrupt enabled
//reserved5      EQU         5                       ; reserved
//reserved6      EQU         6                       ; reserved
//RvSetClr       EQU         7                       ; on READs, always reads 0
                                                    // on WRITEs, 1 = 1-bits in bits 0-6 write 1's
                                                    //           0 = 1-bits in bits 0-6 write 0's

//  ======  Peripherals Clock Control    Address: $50F26021   =====
#define MSCIOClk                 0                       // 1=15.6672MHz I/O clock running, 0=stopped
#define MSCSCCClk                1                       // 1=3.672MHz SCC clock running, 0=stopped
#define MSCSCSIReset             2                       // 1=SCSI reset not asserted, 0=reset asserted (clocks stop)
#define MSCLCDReset              3                       // 1=LCD reset not asserted, 0=reset asserted (clocks stop)
//reserved4      EQU         4                       ; reserved
//reserved5      EQU         5                       ; reserved
//reserved6      EQU         6                       ; reserved
//reserved7      EQU         7                       ; reserved

//  ======  Sound Control                Address: $50F26022   =====
#define MSCSndPower              0                       // 1=DFAC power on, 0=DFAC power off
//reserved1      EQU         1                       ; reserved
//reserved2      EQU         2                       ; reserved
//reserved3      EQU         3                       ; reserved
//reserved4      EQU         4                       ; reserved
//reserved5      EQU         5                       ; reserved
#define MSCSndBusy               6                       // 1=access to FIFO since last access to this register
#define MSCSndLatch              7                       // 1=DFAC is powered up and initialized


#define MSCDefConfig             ((1<<MSC25MHz)|(0<<MSCEconoBit)|(0<<MSCFastROM)|(0<<MSCBank8M)|(0<<MSCSize0))        // set 2MB so there's real RAM for BootBeep  <H10>



//__________________________________________________________________________________________
//
//
// Memory Controllers - Register Definitions and Misc Equates for Memory Controllers.  Included
// are: FMC, ORWELL, JAWS, Niagra, Ponti, djMEMC.
//
//
//__________________________________________________________________________________________


//---------------------------------------------------
//  FMC (Fitch Memory Controller) Equates 
//---------------------------------------------------

#define FMCConfig                $0                      // offset to configuration register.  It is a 16
                                                    // bit wide register with a 1 bit wide data port
                                                    // on d24, so do byte writes (and rotates) and
                                                    // let dynamic bus sizing replicate it on d24-31.

#define FMCLatch                 $10                     // offset to 'latch config data' register (latches
                                                    // on a write to here)
#define FMCInit                  $F3EF                   // config reg initial value              <4.5><4.6><4.9><1>
#define FMCRPUInit               $F3FF                   // config reg initial value (parity)     <1>


//---------------------------------------------------
//  Orwell Memory Controller Equates <5>
//---------------------------------------------------

//   Orwell only has one input/output data bit.  So to store or retrieve any configuration register      
//   information, you must read/write a succession of long-word addresses, starting at the addresses     
//   below, with the ONLY valid data bit being {reg}:0.  Valued being read must be assembled one bit     
//   at a time; values being written must be loaded into the config registers 1 bit at a time.  The      
//   new config. register values do not become active until a "latch" register address associated        
//   with the config. register is written.                                                               
//
//   The below addresses correspond to longword addresses where bit 0 of whatever data register used to  
//   read/write the location will be stored.  The Orwell configuration register is a 34-bit register,    
//   with each bit written to/read by addressing the appropriate longword offset.                        
//
//   The configuration register can be thought of like this:                                             
//
//       +---------------------------------------------------------------------------------------------+ 
//       | PAR_ODD | PAR_ENB | REFRESH | ROM_SPEED | DRAM_SPEED | CLK_SPEED | BANK_D | BANK_C | BANK_B | 
//       +---------------------------------------------------------------------------------------------+ 
//           28        27     26     24 23       21  20       19     18      17   12  11    6  5      0  
//
//                                                                                                               <T6>
//       +---------------------------------------------------------------------+                                 <T6>
//       |    RAS    | Optional WRITE | Optional Read  | Optional Read  | Page |                                 <T6>
//       | Precharge |   wait state   | 2nd wait state | 1st wait state | Mode |                                 <T6>
//       +---------------------------------------------------------------------+                                 <T6>
//            33            32                31               30          29                                    <T6>

//           ***     Register Offsets    ***                                                             

#define OrCfgRegAddr                 0                       // starting offset of config reg. bits               
#define OrCfgRegSize                 34                      // number of bits in the configuration register              <T6>

#define OrBankFieldSize              6                       // each bank config. reg. field is 6 bits wide       
#define OrBankBCfgAddr               (OrCfgRegAddr)            // starting offset of BankB(5:0)                     
#define OrBankCCfgAddr               (OrBankBCfgAddr+(4*OrBankFieldSize))// starting offset of BankC(5:0)           
#define OrBankDCfgAddr               (OrBankCCfgAddr+(4*OrBankFieldSize))// starting offset of BankD(5:0)           
#define OrClkSpeedAddr               (OrBankDCfgAddr+(4*OrBankFieldSize))// starting address of Clock_Speed         
                                                        // ... Clock_Speed is 1 bit (0=25MHz)                
#define OrDRAMSpeedAddr              (OrClkSpeedAddr+4)        // starting address of DRAM Speed(1:0)               
#define OrDRAMFieldSize              2                       // DRAM speed config reg. field is 2 bits wide       
#define OrROMSpeedAddr               (OrDRAMSpeedAddr+(4*OrDRAMFieldSize))// starting address of ROM Speed(2:0)     
#define OrROMFieldSize               3                       // ROM speed config reg. field is 3 bits wide        
#define OrRefreshAddr                (OrROMSpeedAddr+(4*OrROMFieldSize))// starting address of Refresh Rate(2:0)    
#define OrRefreshSize                3                       // Refresh speed config reg. field is 3 bits wide    
#define OrParityEnbAddr              (OrRefreshAddr+(4*OrRefreshSize))// starting address of parity enable/disable  
                                                        // ... Parity_Enable is 1 bit (0=parity OFF)         
#define OrParityTypAddr              (OrParityEnbAddr+4)       // starting address of parity type (even/odd)        
                                                        // ... Parity_Type is 1 bit (0=parity EVEN)          
#define OrPageMode                   (OrParityTypAddr+4)       //                                                           <T6>
#define OrWaitRead1                  (OrPageMode+4)            //                                                           <T6>
#define OrWaitRead2                  (OrWaitRead1+4)           //                                                           <T6>
#define OrWaitWrite1                 (OrWaitRead2+4)           //                                                           <T6>
#define OrRASPrecharge               (OrWaitWrite1+4)          //                                                           <T6>

#define OrLatchOffset                $A0                     // offset from start of config reg. where latches live       <T6>
#define OrwellLatches                (OrCfgRegAddr+OrLatchOffset)// starting address of Latch Addresses                     <T6>

#define OrLoadBanks                  (OrwellLatches)           // Load Bank Config Reg. Latch address                       <T6>
#define OrLoadSpeeds                 (OrLoadBanks+4)           // Load Clock, DRAM and ROM Speeds Latch address     
#define OrLoadRefresh                (OrLoadSpeeds+4)          // Load Refresh interval Latch address               
#define OrLoadParity                 (OrLoadRefresh+4)         // Load Parity enable/disable and type Latch address 

#define OrLoadMode                   (OrLoadParity+4)          // Load Page Mode On/Off address                             <T6>
#define OrLoadWaitStates             (OrLoadMode+4)            // Load Read/Write extra waitstates address                  <T6>
#define OrLoadPrecharge              (OrLoadWaitStates+4)      // Load RAS precharge address                                <T6>

#define OrParityStatus               $100                    // A0-BC = LS 8 bits, C0-DC   = LM 8 bits                    <T6>
                                                        // E0-FC = HM 8 bits, 100-11C = MS 8 bits
#define OrParErrInByte0              $180                    // =1 if parity error occurred in byte 0             
#define OrParErrInByte1              $184                    // =1 if parity error occurred in byte 1             
#define OrParityError                $188                    // =1 if parity error occurred (period)              

//           ***     Initializing Values at Bootup Time      ***                                         

#define ORINITBankB                  $10                     // 10=Bank B at 64MB
#define ORINITBankC                  $20                     // 20=Bank C at 128MB
#define ORINITBankD                  $30                     // 30=Bank D at 192MB

#define ORINITClock25                1                       // 1=25MHz, 0=33MHz                                          <T12>
#define ORINITClock33                0                       //                                                           <T12>
#define ORINITDRAMSpeed              1                       // 0=100ns, 1=80ns, 2=60ns                           <10>
#define ORINITROMSpeed25             2                       // *n* = Clock_Access-3 (0 = 3 Clock_Access)                 <T6><T12>
#define ORINITROMSpeed33             4                       // *n* = Clock_Access-3 (0 = 3 Clock_Access)                 <T6><T12>
#define ORINITREFRESH25              2                       // 0=25MHz 7.8µsec,  1=33MHz, 7.8µsec                <21>    <T12>
                                                        // 2=25MHz 15.6µsec, 3=33MHz 15.6µsec                <21>    <T12>
#define ORINITREFRESH33              3                       //                                                   <21>    <T12>
#define ORINITParity                 0                       // 0=parity OFF, 1=parity ON
#define ORINITParType                1                       // 0=even, 1=odd

//   Additional (programmable) wait states for reads and writes

#define ORINITPageMode               0                       // 0=off, 1=on                                               <T6>
#define ORINITWaitRd1                0                       // 0=off, 1=on (unless Rd2 = 1, in which case it is interpreted as off)<T6>
#define ORINITWaitRd2                0                       // 0=off, 1=on (unless Rd1 = 1, in which case it is interpreted as off)<T6>
#define ORINITWaitWr1                0                       // 0=off, 1=on                                               <T6>
#define ORINITRAS25                  0                       // 0=2 cycles, 1=3 cycles                                    <T6>
#define ORINITRAS33                  1                       //                                                           <T12>

//   These are 32-bit constants that hold all but 2 bits of the initial defaults we                                    .
//   would want to jam into the Orwell configuration register.  These are arranged                                     .
//   in order the register is memory-mapped to facilitate the code that sticks them                                    .
//   in the register.  There are two bits that don't fit in a 32-bit constant, the                                     .
//   optional -OrWaitWrite1- and the not-so-optional -OrRASPrecharge-.  Those values                                   .
//   are used and initialized separately.                                                                              .

#define ORWELL_INIT25          ((ORINITWaitRd2<<31)|\
                                (ORINITWaitRd1<<30)|\
                                (ORINITPageMode<<29)|\
                                (ORINITParType<<28)|\
                                (ORINITParity<<27)|\
                                (ORINITREFRESH25<<24)|\
                                (ORINITROMSpeed25<<21)|\
                                (ORINITDRAMSpeed<<19)|\
                                (ORINITClock25<<18)|\
                                (ORINITBankD<<12)|\
                                (ORINITBankC<<6)|\
                                (ORINITBankB))
#define ORWELL_INIT33          ((ORINITWaitRd2<<31)|\
                                (ORINITWaitRd1<<30)|\
                                (ORINITPageMode<<29)|\
                                (ORINITParType<<28)|\
                                (ORINITParity<<27)|\
                                (ORINITREFRESH33<<24)|\
                                (ORINITROMSpeed33<<21)|\
                                (ORINITDRAMSpeed<<19)|\
                                (ORINITClock33<<18)|\
                                (ORINITBankD<<12)|\
                                (ORINITBankC<<6)|\
                                (ORINITBankB))


//---------------------------------------------------
// JAWS Memory Controller Equates
//---------------------------------------------------

#define JAWSRAMWaitS             $00000                  // RAM wait state control register offset
#define JAWSEconoMode            $04000                  // Econo-Mode register offset                                    <21> HJR
#define JAWSROMWaitS             $06000                  // ROM wait state control register offset

#define JAWSMemConfigA           $10000                  // Contiguous memory (knitting) registers
#define JAWSMemConfigB           $12000                  // Contiguous memory (knitting) registers
#define JAWSMemConfigC           $14000                  // Contiguous memory (knitting) registers

#define JAWSPowerCycle           $20000                  // CPU power off control register
#define JAWSSetCPUClock          $22000                  // Controls the CPU clock frequency
#define JAWSPCBLevel             $30000                  // Selects between SCC and SCC/SCSI combo
#define JAWSLockRAM              $32000                  // Puts RAM in self refresh state
#define JAWSGetCPUClock          $34000                  // Returns the CPU clock frequency

//---------------------------------------------------
// Niagra Memory Controller Equates
//---------------------------------------------------

#define NiagraVidCntCtr          $02000                  // Video count options                                   <21> HJR
#define NiagraGUR                $16000                  // General Utility Registers (ponti register access)<SM4> rb
#define NiagraVidAcc1            $22000                  // Video Accesses thru 64
#define NiagraVidAcc2            $24000                  // Video Accesses thru 512
#define NiagraVidAcc3            $26000                  // Video Accesses thru 2K
#define NiagraFlashEnbl          $30000                  // Enable flash from Niagra
#define NiagraFPUAcc             $34000                  // FPU access detected
#define NiagraSpeedReg           $36000                  // Returns the CPU clock frequency

//---------------------------------------------------                                <SM4> rb, start
// Ponti Register Equates  (NiagraGUR register space + offset
//---------------------------------------------------

#define PontiSPIMdmCtl               $000
#define PontiSndCtl                  $400
#define PontiSPISftReg               $800
#define PontiLmpSftCtl               $C00

// Ponti PontiSPIMdmCtl bit definitions
#define PontiSPIMdmId                0               // (1 = SPI modem connected)
#define PontiSPIAck                  2               // (1 = ack idle)
#define PontiSPIReq                  3               // (1 = req idle)
#define PontiSPIIrq                  4               // (1 = interrupting) 

// Ponti PontiSoundCtl bit definitions
#define PontiSndSPIIrqMsk            0               // (1 = mask int)            - irq mask for PontiSPIIrq 
#define PontiSndIntMic               1               // (1 = using internal mic)  - flag to check which mike is used  <H22> 
#define PontiSndLatchClr             2               // (pulse high to clear)     - line directly to latch
#define PontiSndLatchData            3               // (1 = snd ckt used)        - output value of the sound latch
#define PontiSndPWMOff               4               // (1 = PWM off)             - ultimate off to remove "pop"
#define PontiSndPwrOn                5               // (1 = power snd ckt)       - sw equal of latch output
#define PontiSndMux0                 6               // (1 = ???)
#define PontiSndMux1                 7               // (1 = modem sound {regardless of Mux0})

// Ponti PontiLmpSftCtl bit definitions
#define PontiLmpOff                  0               // (1 = backlight on)        - turn on the backlight tube 
#define PontiLmpHWCtl                1               // (1 = Hardware control)    - if set, hardware control loop 
#define PontiLmpMux0                 2               // (1 = 1/2 pot)             - 1/2 scale pot reduction
#define PontiLmpMux1                 3               // (1 = 1/4 pot)             - 1/4 scale pot reduction
#define PontiLmpSPIDir               4               // (1 = shift out)           - direction of shift register
                                                //                                       <SM4> rb, end
//-------------------------------------                                                                      <H21> thru next <H21>
//   djMEMC memory controller equates
//-------------------------------------

//   This hard-coded I/O address is in here because there is no more room in the 
//   Universal tables to hold this information.

#define MEMCAddr                 $50F0E000               // same for both Wombat + WLCD memory maps

#define MEMCRegisterStart        0
#define MEMCIntleaveEnable       (MEMCRegisterStart)       // DRAM interleave enable reg.
#define dj_OneBufferedBusBit     5
//   djMEMC supports up to a maximum of 10 (TEN) DRAM banks
#define dj_MaxBanks              10                      //                                                       <H22>

#define MEMCDRAMCfg0             (MEMCIntleaveEnable+4)    // Bank 0 cfg reg
#define MEMCDRAMCfg1             (MEMCDRAMCfg0+4)          // Bank 1 cfg reg
#define MEMCDRAMCfg2             (MEMCDRAMCfg1+4)          // Bank 2 cfg reg
#define MEMCDRAMCfg3             (MEMCDRAMCfg2+4)          // Bank 3 cfg reg
#define MEMCDRAMCfg4             (MEMCDRAMCfg3+4)          // Bank 4 cfg reg
#define MEMCDRAMCfg5             (MEMCDRAMCfg4+4)          // Bank 5 cfg reg
#define MEMCDRAMCfg6             (MEMCDRAMCfg5+4)          // Bank 6 cfg reg
#define MEMCDRAMCfg7             (MEMCDRAMCfg6+4)          // Bank 7 cfg reg
#define MEMCDRAMCfg8             (MEMCDRAMCfg7+4)          // Bank 8 cfg reg
#define MEMCDRAMCfg9             (MEMCDRAMCfg8+4)          // Bank 9 cfg reg

#define MEMCmemTop               (MEMCDRAMCfg9+4)          // Top of stitched RAM
#define MEMCconfig               (MEMCmemTop+4)            // "Multiple bit DRAM/ROM configuration register"
#define MEMCRefresh              (MEMCconfig+4)            // DRAM refresh rate register


//__________________________________________________________________________________________
//
//
// Interrupt Vector Definitions and Masks
//
//
//__________________________________________________________________________________________

            
            
//---------------------------------------------------
// Interrupt Masks
//---------------------------------------------------

#define hiIntMask                $0700                   // programmer switch only
#define pwrOffEnbl               $2500                   // mask to allow poweroff interrupts
#define sccIntMask               $0400                   // SCC interrupt level
#define sccEnblMask              $FBFF                   // mask to enable SCC interrupts
#define slotIntMask              $0200                   // slot's interrupt level    <v1.4><1.9>
#define viaIntMask               $0100                   // VIA1 interrupt level
#define loIntMask                $0100


//---------------------------------------------------
// Hardware Base Addresses
//---------------------------------------------------

#define WrOffs                   0                       // SCSI write addrs are same as read base
#define MskIOP1                  1                       // IOP 1 (SWIM) is level 1 interrupt
#define MskVIA1                  1                       // VIA 1 is level 1
#define MskADB                   1                       // ADB is level 1
#define Msk60Hz                  1                       // 60 Hz is level 1
#define MskSCSI                  2                       // SCSI is level 2
#define MskSound                 2                       // sound is level 2                      <4.5>
#define MskSlots                 2                       // slots are level 2 interrupts
#define MskRTC                   3                       // RTC is level 3
#define MskIOP0                  4                       // IOP 0 (& SCC chip) is level 4
#define MskPwrOff                6                       // Poweroff button is level 6
#define MskNMI                   7                       // NMI switch is level 7

            
// ---------------------------------------------------------------------------------------------------   <T8>
//       Bit definitions for the Cache Control Register (CACR) on various CPUs                           <T8>
// ---------------------------------------------------------------------------------------------------   <T8>
//
//   020 CACR:       (from MC68020 User's Manual, 3rd Ed.  pg. 6-3)                                      <T8>
//           +------------------------------------------------+                                          <T8>
//           |  0  ..............  0 |  C  |  CE  |  F  |  E  |                                          <T8>
//           +------------------------------------------------+                                          <T8>
//             31                  4    3      2     1     0                                             <T8>
//
//               C   =  Clear Cache                                                                      <T8>
//               CE  =  Clear Entry                                                                      <T8>
//               F   =  Freeze Cache                                                                     <T8>
//               E   =  Enable (Inst.) Cache                                                             <T8>
//
//
//   030 CACR:       (from MC68030 User's Manual, 2nd Ed.  pg 6-15)                                      <T8>
//           +------------------------------------------------------------------------------------+      <T8>
//           |  0  ...  0  | WA | DBE | CD | CED | FD | ED | 0 | 0 | 0 | IBE | CI | CEI | FI | EI |      <T8>
//           +------------------------------------------------------------------------------------+      <T8>
//            31       14    13    12   11    10    9    8   7   6   5    4    3     2    1     0        <T8>
//
//               WA  =   Write Allocate                                                                  <T8>
//               DBE =   Data Burst Allocate                                                             <T8>
//               CD  =   Clear Data Cache                                                                <T8>
//               CED =   Clear Entry in Data Cache                                                       <T8>
//               FD  =   Freeze Data Cache                                                               <T8>
//               ED  =   Enable Data Cache                                                               <T8>
//               IBE =   Instruction Burst Enable                                                        <T8>
//               CI  =   Clear Instruction Cache                                                         <T8>
//               CEI =   Clear Entry in Instruction Cache                                                <T8>
//               FI  =   Freeze Instruction Cache                                                        <T8>
//               EI  =   Enable Instruction Cache                                                        <T8>
//
//
//   040 CACR:       (from MC68040 User's Manual, 1st Ed.,  pg. 7-19)                                    <T8>
//           +-------------------------------------+                                                     <T8>
//           |  DE  |  0 ... 0  |  IE  |  0 ... 0  |                                                     <T8>
//           +-------------------------------------+                                                     <T8>
//              31    30     16    15    14     0                                                        <T8>
//
//               DE  =   Enable Data Cache                                                               <T8>
//               IE  =   Enable Instruction Cache                                                        <T8>
//

//   MC68040 CACR bits of note:

#define CACR_IE_040                  15              // bit # of instruction cache enable/disable on 040s     <T8>
#define CACR_DE_040                  31              // bit # of data cache enable/disable on 040s            <T8>

//   MC68020 and MC68030 CACR bits of note:

#define CACR_EI_020_030              0               // bit # of inst. cache enable/disable on 020/030s       <T8>
#define CACR_FI_020_030              1               // bit # of inst. cache freeze on 020/030s               <T8>
#define CACR_CEI_020_030             2               // bit # of inst. cache flush entry on 020/030s          <T8>
#define CACR_CI_020_030              3               // bit # of inst. cache flush on 020/030s                <T8>
#define CACR_IBE_030                 4               // bit # of data cache burst enable on 030s              <T8>
#define CACR_ED_030                  8               // bit # of data cache enable/disable on 030s            <T8>
#define CACR_FD_030                  9               // bit # of data cache freeze on 030s                    <T8>
#define CACR_CED_030                 10              // bit # of data cache flush entry on 030s               <T8>
#define CACR_CD_030                  11              // bit # of data cache flush on 030s                     <T8>
#define CACR_DBE_030                 12              // bit # of data cache burst enable on 030s              <T8>
#define CACR_WA_030                  13              // bit # of write allocate enable on 030s                <T8>            
            
//__________________________________________________________________________________________
//
//
// Miscellaneous Equates - Look Here If You Can't Find It Anywhere Else.
//
//
//__________________________________________________________________________________________



#define Machine                  7                       // new Machine number for patches            <18>

//---------------------------------------------------
// System Software Information
//---------------------------------------------------

#define numOsTrap                256                     // number of os traps
#define ToolTable                $0E00                   // start of toolbox trap table
#define numTbTrap                1024                    // number of toolbox traps
#define numTrapMask              (numTbTrap-1)             // mask for number of tb traps
#define JMemMgr24                $1E00                   // jump vector start for 24 bit Memory Manager       <v1.9>
#define JMemMgr32                $1F00                   // jump vector start for 32 bit Memory Manager       <v1.9>
#define HeapStart                $2800                   // Low mem is now 10k bytes                          <SM13>
#define defSysHeap               $18000                  // Default size of the system heap
#define nDfltStackSize           $6000                   // Default stack size

//**** maybe not so temporary to allow things to build ****                                   <3.5>
#define oneSecConst              8                       // gets converted to $80000 for onesec constant<3.5>
#if BlackBirdDebug
#define ROMStart				 $40000000
#else
#define ROMStart                 $40800000               // starting address of final ROM code    <3.5>
#endif

#define snd2MemTop               $300                    // SoundLow to Memtop
#define pwm2MemTop               $2FF                    // PWMBuffer to MemTop
#define bufWorldSize             8192                    // total size of the BufPtr world        <H16>

//---------------------------------------------------                                <SM4> rb, start
//  Sound parameters                                                                         <P4>
//---------------------------------------------------
#define sampleSize               4               // number of bytes per sample
#define bufferSize               960             // number of samples per buffer
#define sampleRate               (24 * 1024)       // 24KHz sample rate

//---------------------------------------------------
//  PSC Hardware Defs
//---------------------------------------------------

// === Hardware Base Addresses ===
#define PSCBase                  $50f31000       // Base address of the PSC

//---------------------------------------------------
//  PSC Sound Register Offsets
//---------------------------------------------------
#define sndComCtl                $200            // [word] sound and communications control 
#define singerCtl                $204            // [long] singer sound CODEC control
#define singerStat               $208            // [long] singer sound CODEC status  (read only)
#define sndPhase                 $20c            // [long] sound subsystem phase  (read only)
#define sndInBase                $210            // [long] sound input double-buffer base address 
#define sndOutBase               $214            // [long] sound output double buffer base address 
#define sndSize                  $218            // [word] sound input and output buffer size 
#define dspOverRun               $21C            // [byte] DSP overrun status register.

//---------------------------------------------------
//  PSC Sound Register Bit Definitions
//---------------------------------------------------
// === sndComCtl register ===
#define pSubFrmInSel             0               // singer sound CODEC input subframe select
#define pSubFrmInSel1            0               // singer sound CODEC input subframe select, lsbit
#define pSubFrmInSel2            1               // singer sound CODEC input subframe select, msbit

#define pSubFrmOutSel            2               // singer sound CODEC output subframe select
#define pSubFrmOutSel1           2               // singer sound CODEC output subframe select, lsbit
#define pSubFrmOutSel2           3               // singer sound CODEC output subframe select 
#define pSubFrmOutSel3           4               // singer sound CODEC output subframe select 
#define pSubFrmOutSel4           5               // singer sound CODEC output subframe select, msbit

#define pFrmIntEn                6               // frame interrupt enable
#define pSndInEn                 7               // sound input DMA enable
#define pSndOutEn                8               // sound output DMA enable

#define pSndRate                 9               // singer sound CODEC sampling rate control
#define pSndRate1                9               // singer sound CODEC sampling rate control, lsbit
#define pSndRate2                10              // singer sound CODEC sampling rate control, msbit

#define pComRate                 11              // communications CODEC sampling rate contrl
#define pComRate1                11              // communications CODEC sampling rate contrl, lsbit
#define pComRate2                12              // communications CODEC sampling rate contrl, msbit
//               equ         13              ; unused
//               equ         14              ; unused
//               equ         15              ; unused


#define sndComCtlInit            ((0<<pSubFrmInSel)|\
                                  (0<<pSubFrmOutSel)|\
								  (0<<pFrmIntEn)|\
								  (0<<pSndInEn)|\
								  (0<<pSndOutEn)|\
								  (0<<pSndRate)|\
								  (0<<pComRate))

#define soundOutEnable           ((0<<pSubFrmInSel)|\
								  (1<<pSubFrmOutSel)|\
								  (0<<pFrmIntEn)|\
								  (0<<pSndInEn)|\
								  (1<<pSndOutEn)|\
								  (0<<pSndRate)|\
								  (0<<pComRate))



// === singerCtl register ===
#define pOutputPort          0                   // set digital output port
#define pOutputPort1             0               // set digital output port, lsb
#define pOutputPort2             1               // set digital output port
#define pOutputPort3             2               // set digital output port
#define pOutputPort4             3               // set digital output port, msb

#define pRightAtten              4               // right ouput attenutaion
#define pRightAtten1             4               // right ouput attenutaion, lsb
#define pRightAtten2             5               // right ouput attenutaion
#define pRightAtten3             6               // right ouput attenutaion
#define pRightAtten4             7               // right ouput attenutaion, msb

#define pLeftAtten               8               // Left ouput attenutaion
#define pLeftAtten1              8               // Left ouput attenutaion, lsb
#define pLeftAtten2              9               // Left ouput attenutaion
#define pLeftAtten3              10              // Left ouput attenutaion
#define pLeftAtten4              11              // Left ouput attenutaion, msb

#define pRightGain               12              // right input gain
#define pRightGain1              12              // right input gain, lsb
#define pRightGain2              13              // right input gain
#define pRightGain3              14              // right input gain
#define pRightGain4              15              // right input gain, msb

#define pLeftGain                16              // left input gain
#define pLeftGain1               16              // left input gain, lsb
#define pLeftGain2               17              // left input gain
#define pLeftGain3               18              // left input gain
#define pLeftGain4               19              // left input gain, msb

#define pRightInMux              20              // right input mux
#define pLeftInMux               21              // left input mux
#define pMute                    22              // mute bit
#define pExpCtl                  23              // expand bit for control
//               equ         24              ; unused
//               equ         25              ; unused
//               equ         26              ; unused
//               equ         27              ; unused
//               equ         28              ; unused
//               equ         29              ; unused
//               equ         30              ; unused
//               equ         31              ; unused

#define singerCtlInit            (($F<<pOutputPort)|\
							      (0<<pRightAtten)|\
								  (0<<pLeftAtten)|\
								  ($5<<pRightGain)|\
								  ($5<<pLeftGain)|\
								  (0<<pRightInMux)|\
								  (0<<pLeftInMux)|\
								  (1<<pMute)|\
								  (0<<pExpCtl))
                
#define unMute                   (($F<<pOutputPort)|\
								  (0<<pRightAtten)|\
								  (0<<pLeftAtten)|\
								  ($5<<pRightGain)|\
								  ($5<<pLeftGain)|\
								  (0<<pRightInMux)|\
								  (0<<pLeftInMux)|\
								  (0<<pMute)|\
								  (0<<pExpCtl))
                


// === singerStat register ===
#define pInputPort1              0               // set digital Input port, lsb
#define pInputPort2              1               // set digital Input port
#define pInputPort3              2               // set digital Input port
#define pInputPort4              3               // set digital Input port, msb
//               equ         4               ; unused
//               equ         5               ; unused
//               equ         6               ; unused
//               equ         7               ; unused
//               equ         8               ; unused
//               equ         9               ; unused
//               equ         10              ; unused
//               equ         11              ; unused
#define pRevNum1                 12              // revision number, lsb
#define pRevNum2                 13              // revision number
#define pRevNum3                 14              // revision number
#define pRevNum4                 15              // revision number, msb
#define pSingerStatus1           16              // status bits, lsb
#define pSingerStatus2           17              // status bits
#define pSingerStatus3           18              // status bits
#define pSingerStatus4           19              // status bits, msb
#define pOFRight                 20              // right channel overflow
#define pOFLeft                  21              // left channel overflow
#define pValidData               22              // valid sound data
#define pExpStat                 23              // expand bit for status
//               equ         24              ; unused
//               equ         25              ; unused
//               equ         26              ; unused
//               equ         27              ; unused
//               equ         28              ; unused
//               equ         29              ; unused
//               equ         30              ; unused
//               equ         31              ; unused

 
// === sound phase register ===
#define pPreScaleLSB             0               // pre-scaler lsbit
#define pReScaleMSB              5               // pre-Scaler msbit
#define pOffsetLSB               6               // sample offset lsbit
#define pOffsetMSB               17              // sample offset msbit
//               equ         18              ; unused
//               equ         19              ; unused
//               equ         20              ; unused
//               equ         21              ; unused
//               equ         22              ; unused
//               equ         23              ; unused
//               equ         24              ; unused
//               equ         25              ; unused
//               equ         26              ; unused
//               equ         27              ; unused
//               equ         28              ; unused
//               equ         29              ; unused
//               equ         30              ; unused
//               equ         31              ; unused

#define phaseOffsetMsk           $003FFFC0       //                                       <SM4> rb, end

//---------------------------------------------------
// PSC DSP Register Bit Definitions                      <SM10> ejb
//---------------------------------------------------

// === dspOverrun register ===
#define pdspReset                0               // when set places the dsp in reset state
#define pdspResetEn              1               // when cleared disables the dspReset bit
#define pdspFrameOvr             2               // when set indicates cat2 frame overrun on the dsp
//               equ         3               ; unused
//               equ         4               ; unused
//               equ         5               ; unused
//               equ         6               ; unused
#define pdspSet                  7               // "0" clears, "1" sets for any bit field [0:6] containing a "1"

//---------------------------------------------------
// ???
//---------------------------------------------------

#define seRegs                   $0C30                   // offset to Sys Error Regs w/o Overlay

//---------------------------------------------------
// Hardware configuration bits.
//---------------------------------------------------

#define hwCbSCSI                 15                      // SCSI port present
#define hwCbClock                14                      // New clock chip present
#define hwCbExPRAM               13                      // Extra Parameter Ram valid.
#define hwCbFPU                  12                      // FPU chip present.
#define hwCbMMU                  11                      // Some kind of MMU present (see MMUType for what kind).
#define hwCbADB                  10                      // Apple Desktop Bus present.
#define hwCbAUX                  9                       // Running A/UX                  <2.8>
#define hwCbPwrMgr               8                       // Power Manager present         <2.8>
#define hwCmSCSI                 ((1 << hwCbSCSI))
#define hwCmClock                ((1 << hwCbClock))
#define hwCmExPRAM               ((1 << hwCbExPRAM))
#define hwCmFPU                  ((1 << hwCbFPU))
#define hwCmMMU                  ((1 << hwCbMMU))
#define hwCmADB                  ((1 << hwCbADB))
#define hwCmAUX                  ((1 << hwCbAUX))
#define hwCmPwrMgr               ((1 << hwCbPwrMgr))


//---------------------------------------------------
// HcMac Clock Change Addresses
//---------------------------------------------------

#define Clock16M                 $FE0000                 // Go to sixteen megahertz clock throughput
#define Clock1M                  $FE0002                 // Go to one megahertz clock throughput (adds 64 wait states)


//---------------------------------------------------
// SCC Clock Rates, Baud Rate Constants
//---------------------------------------------------

#define nuMacClock               36864
#define nuMacConst               115200

#define macClock                 36707                   // in Hz * 100
#define macConst                 114709                  // in Hz/32

#define hcMacClock               36720                   // SCC clock rates
#define hcMacConst               114750


//---------------------------------------------------
// Deep Shit Rectangle info
//---------------------------------------------------

#define dsRectTL                 ((64<<16)+32)             // top left = 64,32
#define dsRectBR                 ((190<<16)+480)           // bottom right = 190,480
#define dsRectHei                ((DSrectBR & $FFFF0000)-(DSrectTL & $FFFF0000)>>16)
#define dsRectLen                ((DSrectBR & $FFFF)-(DSrectTL & $FFFF))


//---------------------------------------------------
// System Error Equates
//---------------------------------------------------

#define seVars                   (seRegs)                  // start of system error data space (wrap city)
#define seVSize                  128                     // # of bytes in space
#define seD0                     (seVars)                  // loc of saved reg D0
#define seA0                     (seD0+32)                 // loc of saved reg A0
#define seA7                     (seA0+28)                 // loc of saved reg A7
#define sePC                     (seA7+4)                  // loc of saved PC
#define seSR                     (sePC+4)                  // loc of saved SR
#define seAccess                 (seSR+2)                  // PC address during bus/address error
#define seCmdSize                (seAccess+4)              // # of bytes of parameters passed in _debugger call
#define se000BE                  (seCmdSize+2)             // 8 bytes of bus error info for 68000
#define seLastVar                (se000BE+8)               // last var in System Error data space


//---------------------------------------------------
// ROM based debugger nub
//---------------------------------------------------

#define rdPort                   (seLastVar)               // Number of port currently in use (0 => no link, 1 => A, 2 => B)
#define rdCode                   (rdPort+2)                // Ptr to code download buffer.
#define rdAtrap                  (rdCode+4)                // Saved Rom Atrap handler
#define rdLowTrap                (rdAtrap+4)               // low value for trap handling
#define rdHiTrap                 (rdLowTrap+2)             // high value for trap handling
#define rdResult                 (rdHiTrap+2)              // result of executing down-loaded code, etc. (16 bytes)
#define rdEnd                    (rdResult+16)             // end of vars


//---------------------------------------------------
// Microbug
//---------------------------------------------------

// NOTE: Keep mbDotAddr immediately before mBlocAddr

#define mbBufSize                34
#define mbBuffer                 (seLastVar)               // buffer for input
#define mbSign                   (mbBuffer+mbBufSize)      // ST => negative sign during conversion
#define mbDotAddr                (mbSign+2)                // saved address
#define mBlocAddr                (mbDotAddr+4)             // saved location


//---------------------------------------------------
// Alternate ROM vectors
//---------------------------------------------------

#define DiagROM                  $F80000                 // Alternate ROM - initial vector
#define DiagROM1                 $F80080                 // Alternate ROM - memory sizing vector
#define DiagROM2                 $F80088                 // Alternate ROM - init I/O vector


//---------------------------------------------------
// Timing constants
//---------------------------------------------------

#define VIAClockHz               783360                  // VIA clock rate is 783360 Hz.      <2.8>
#define nTicks                   (VIAClockHz/1000)         // VIA timer ticks per msec
#define oneSecTicks              60                      // ticks, of course
#ifndef __SysEqu___
#define TimeSCSIDB               $0B24                   // DBRAs & SCSI access per millisecond <1.9>
#endif

#define ramChk                   1024                    // Amount of memory tested for stack.



//__________________________________________________________________________________________
//
//
// ROM Header RECORD Definition
//
//
//__________________________________________________________________________________________

#define ROMHeader             0             // offsets to fields in base of ROM
#define ROMHeader_ResetSP         0                       // $0000 SP to be loaded at reset time
#define ROMHeader_CheckSum                 (ResetSP)                 // $0000 hiram stuffs checksum here
#define ROMHeader_ResetPC         4                       // $0004 PC to be loaded at reset time
#define ROMHeader_MachineNumber   8                       // $0008 Machine Number
#define ROMHeader_ROMVersion      9                       // $0009 ROM Version Number
#define ROMHeader_ReStart         10                       // $000A JMP to StartBoot routine
#define ROMHeader_BadDisk         14                       // $000E JMP to eject disk, and ReBoot routine
#define ROMHeader_ROMRelease      18                       // $0012 ROM Release in HEX, eg. $10B5 is 1.0ß5
#define ROMHeader_PatchFlags      20                       // $0014 ROM overpatch basis                 <H14>       
//**Pad**:                 DS.B        1                       // $0015 unused                              <H14>
#define ROMHeader_ForeighOSTbl    22                       // $0016 offset to foreign OS vector table
#define ROMHeader_RomRsrc         26                       // $001A HiRam stuffs offset to ROM rsrc header here
#define ROMHeader_Eject           30                       // $001E JMP to DoEject routine
#define ROMHeader_DispTableOff    34                       // $0022 offset to the compressed dispatch table
#define ROMHeader_Critical        38                       // $0026 JMP to Critical error handler
#define ROMHeader_ResetEntry      42                       // $002A JMP to Reset Entry Point routine.
#define ROMHeader_RomLoc          46                       // $002E (Bit 0: In Ram, Bit 1: In Emulator)
//**Pad**:                 DS.B        1                       // $002F unused
#define ROMHeader_CheckSum0       48                       // $0030 checksum 0
#define ROMHeader_CheckSum1       52                       // $0034 checksum 1
#define ROMHeader_CheckSum2       56                       // $0038 checksum 2
#define ROMHeader_CheckSum3       60                       // $003C checksum 3
#define ROMHeader_RomSize         64                       // $0040 HiRam stuffs size of ROM in bytes here
// endr ROMHeader


//---------------------------------------------------
// Romulator ROM location bits and TestFor Macro                                                                 
//---------------------------------------------------

#define locValid1                7                       // this must be 1
#define locValid2                6                       // this must be 0
#define inEmulatorBit            1                       // running in emulator
#define inRamBit                 0                       // running in ram

        
#define ForAmusementOnly         0

#if ForAmusementOnly

//__________________________________________________________________________________________
//
//
// Old 16 bit Equates for onMac, onMacPP, and onHcMac
//
//
//__________________________________________________________________________________________

//=======================================;
//  Macintosh Plus Hardware Information  ;
//=======================================;

#define hwCfgBits                (hwCmSCSI|hwCmClock)
#define machine                  0
#define rom85Bits                $7F                     // New ROMs, No Power Off.

// === Interrupt Masks ===
#define hiIntMask                $0700                   // programmer switch only
#define sccIntMask               $0200                   // SCC interrupt Level       <1.5>
#define sccEnblMask              $F9FF                   // mask to enable SCC interrupts
#define viaIntMask               $0100                   // mask for VIA (and VBL) interrupts
#define loIntMask                $0100

// === VIA1 BUFFER A ===
//vSound         EQU         $7                      ; sound volume bits (0..2)
#define vSndPg2                  3                       // select sound page 2 if 0
//vOverlay       EQU         4                       ; overlay bit (overlay when 1)
//vHeadSel       EQU         5                       ; head select line for Sony
#define vPage2                   6                       // select video page 2 if 0
//vSCCWrReq      EQU         7                       ; SCC write/request line

#define vAOut                    ((vSound)|\
                                  (1<<vSndPg2)|\
								  (1<<vOverlay)|\
								  (1<<vHeadSel)|\
								  (1<<vPage2)|\
								  (0<<vSCCWrReq))
								  
#define vAInit                   ((1)|\
                                  (1<<vSndPg2)|\
								  (0<<vOverlay)|\
								  (1<<vHeadSel)|\
								  (1<<vPage2)|\
								  (0<<vSCCWrReq))


// === VIA1 BUFFER B ===
//vRTCData       EQU         0                       ; real time clock data
//vRTCClk        EQU         1                       ; real time clock clock pulses
//vRTCEnb        EQU         2                       ; clock enable (0 for enable)
#define vSW                      3                       // mouse switch (0 when down)
#define vX2                      4                       // mouse X level
#define vY2                      5                       // mouse Y level
#define vH4                      6                       // horizontal sync
//vSndEnb        EQU         7                       ; /sound enable (reset when 1)

#define vBOut                    ((1<<vRTCData)|\
                                  (1<<vRTCClk)|\
								  (1<<vRTCEnb)|\
								  (0<<vSW)|\
								  (0<<vX2)|\
								  (0<<vY2)|\
								  (0<<vH4)|\
								  (1<<vSndEnb))

#define vBInit                   ((1<<vRTCData)|\
                                  (1<<vRTCClk)|\
								  (1<<vRTCEnb)|\
								  (0<<vSW)|\
								  (0<<vX2)|\
								  (0<<vY2)|\
								  (0<<vH4)|\
								  (1<<vSndEnb))

#define vBufM                    (vBufB)                   // mouse state is buffer B


// === Hardware Base Addresses ===

#define PhaseRead                $F00000                 // Phase read address

#define VBase                    $EFE1FE                 // VIA base address
#define AVBufA                   (VBase+vBufA)             // VIA buffer A
#define AVBufB                   (VBase+vBufB)             // VIA buffer B
#define AVBufM                   (VBase+vBufM)             // VIA buffer with mouse button bit

#define SCCRBase                 $9FFFF8                 // SCC base read address
#define SCCWBase                 $BFFFF9                 // SCC base write address
#define sccWrite                 (SCCWBase-SCCRBase)       // general offset for write from read

#define SCSIRd                   $580000                 // base addr SCSI interface - READ
#define SCSIWr                   $580001                 // base addr SCSI interface - WRITE
#define wrOffs                   (SCSIWr-SCSIRd)           // write addrs are +1 to the read base

#define SoundLow                 $3FFD00                 // sound buffer start address
#define snd2MemTop               $300                    // SoundLow to Memtop

#define PWMBuffer                $3FFD01                 // PWM bytes are low bytes
#define pwm2MemTop               $2FF                    // PWMBuffer to MemTop

// === Video Parameters ===

#define ScreenLow                $3FA700                 // top of screen screen address
#define scrn2MemTop              $5900                   // ScreenBase to Memtop

// === Hardware Base Addresses ===

#define romBSize                 $20000                  // 128K bytes in ROM $0075
#define ROMStart                 $400000                 // starting address of ROM code

#define DBase                    $DFE1FF                 // disk address base

// === System Software Information ===
#define bufWorldSize             (scrn2MemTop)             // total size of the BufPtr world

#define oneSecConst              2                       // gets converted to $20000 for onesec constant
#define numOsTrap                256                     // number of os traps
#define ToolTable                $0C00                   // start of toolbox trap table
#define numTbTrap                512                     // number of toolbox traps
#define numTrapMask              (numTbTrap-1)             // mask for number of tb traps
#define HeapStart                $1400                   // Mac Plus starting point
#define defSysHeap               $B700                   // Default size of the system heap
#define nDfltStackSize           $2000                   // Default stack size

#define oneSec                   95528                   // looptimes                     *** patch only ***
#define halfSec                  (onesec/2)                //                               *** patch only ***
#define stlDelay                 $30                     // default bus settle delay      *** patch only ***
#define ROMDoEject               $40001E                 // jump to DoEject utility       *** patch only ***
#define dACKRd                   $200                    // offset of psuedo-DMA - READ   *** patch only ***


//=======================================;
//   Macintosh SE Hardware Information   ;
//=======================================;

#define hwCfgBits                (hwCmSCSI|hwCmClock|hwCmADB)
#define machine                  2
#define rom85Bits                $7F                     // New ROMs, No Power Off.

// === Interrupt Masks ===
#define hiIntMask                $0700                   // programmer switch only
#define sccIntMask               $0200                   // SCC interrupt Level       <1.5>
#define sccEnblMask              $F9FF                   // mask to enable SCC interrupts
#define viaIntMask               $0100                   // mask for VIA (and VBL) interrupts
#define loIntMask                $0100

// === VIA1 BUFFER A ===
//vSound         EQU         $7                      ; sound volume bits (0..2)
//vSync          EQU         3                       ; Synchronous modem
#define vDriveSel                4                       // int drive select (lower drive when 1)
//vHeadSel       EQU         5                       ; head select line for Sony
#define vPage2                   6                       // select video page 2 if 0
//vSCCWrReq      EQU         7                       ; SCC write/request line

#define vAOut                    ((vSound)|\
                                  (1<<vSync)|\
								  (1<<vDriveSel)|\
								  (1<<vHeadSel)|\
								  (1<<vPage2)|\
								  (0<<vSCCWrReq))

#define vAInit                   ((1)|\
    							  (1<<vSync)|\
								  (0<<vDriveSel)|\
								  (1<<vHeadSel)|\
								  (1<<vPage2)|\
								  (0<<vSCCWrReq))



// === VIA1 BUFFER B ===
//vRTCData       EQU         0                       ; real time clock data
//vRTCClk        EQU         1                       ; real time clock clock pulses
//vRTCEnb        EQU         2                       ; clock enable (0 for enable)
//vFDBInt        EQU         3                       ; Front Desk bus interrupt
//vFDesk1        EQU         4                       ; Front Desk bus state bit 0
//vFDesk2        EQU         5                       ; Front Desk bus state bit 1
#define vSCSIMask                6                       // SCSI IRQ mask
#define vH4                      (vSCSIMask)               // SCSI IRQ mask (was horiz. sync)
//vSndEnb        EQU         7                       ; /sound enable (reset when 1)

#define vBOut                    ((1<<vRTCData)|\
								  (1<<vRTCClk)|\
								  (1<<vRTCEnb)|\
								  (0<<vFDBInt)|\
								  (1<<vFDesk1)|\
								  (1<<vFDesk2)|\
								  (1<<vSCSIMask)|\
								  (1<<vSndEnb) )

#define vBInit                   ((1<<vRTCData)|\
								  (1<<vRTCClk)|\
								  (1<<vRTCEnb)|\
								  (0<<vFDBInt)|\
								  (1<<vFDesk1)|\
								  (1<<vFDesk2)|\
								  (1<<vSCSIMask)|\
								  (1<<vSndEnb))

// === Hardware Base Addresses ===

#define VBase                    $EFE1FE                 // VIA base address
#define AVBufA                   (VBase+vBufA)             // VIA buffer A
#define AVBufB                   (VBase+vBufB)             // VIA buffer B

#define SCCRBase                 $9FFFF8                 // SCC base read address
#define SCCWBase                 $BFFFF9                 // SCC base write address
#define sccWrite                 (SCCWBase-SCCRBase)       // general offset for write from read

#define SCSIRd                   $5FF000                 // base addr SCSI interface - READ
#define SCSIWr                   $5FF001                 // base addr SCSI interface - WRITE
#define MacSCSIBase              $5FF000                 // base addr SCSI READ interface
#define MacSCSIDMA               $5FF200                 // base addr SCSI DMA
#define MacSCSIHsk               $5FF200                 // base addr SCSI handshake
#define wrOffs                   (SCSIWr-SCSIRd)           // write addrs are +1 to the read base

#define SoundLow                 $3FFD00                 // sound buffer start address
#define snd2MemTop               $300                    // SoundLow to Memtop

#define PWMBuffer                $3FFD01                 // PWM bytes are low bytes
#define pwm2MemTop               $2FF                    // PWMBuffer to MemTop

// === Video Parameters ===

#define ScreenLow                $3FA700                 // top of screen screen address
#define scrn2MemTop              $5900                   // ScreenBase to Memtop

// === Hardware Base Addresses ===

#define romBSize                 $40000                  // 256K bytes in present ROM
#define ROMStart                 $400000                 // starting address of ROM code              

#define DBase                    $DFE1FE                 // disk address base

// === System Software Information ===
#define bufWorldSize             (scrn2MemTop)             // total size of the BufPtr world

#define oneSecConst              2                       // gets converted to $20000 for onesec constant
#define numOsTrap                256                     // number of os traps
#define ToolTable                $0E00                   // start of toolbox trap table

#define numTbTrap                512                     // number of toolbox traps
#define numTrapMask              (numTbTrap-1)             // mask for number of tb traps
#define HeapStart                $1600                   // Aladdin starting point

#define defSysHeap               $18000                  // Default size of the system heap
#define nDfltStackSize           $2000                   // Default stack size


//===========================================;
//   Macintosh Portable Hardware Information ;
//===========================================;

#define hwCfgBits                (hwCmSCSI|hwCmClock|hwCmADB|hwCbPwrMgr)                // <2.8>
#define machine                  3
#define rom85Bits                $7F                     // New ROMs, No Power Off.


// === Interrupt Masks ===
#define hiIntMask                $0700                   // programmer switch only
#define sccIntMask               $0200                   // SCC interrupt Level       <1.5>
#define sccEnblMask              $F9FF                   // mask to enable SCC interrupts
#define viaIntMask               $0100                   // mask for VIA (and VBL) interrupts
#define loIntMask                $0100


// === VIA1 BUFFER A ===
                                                    // 68000 <-> PowerMgr data bus
#define vAIn                     $00                     // VBufA output bits (all inputs)
#define vAOut                    $FF                     // VBufA output bits (all outputs)
#define vAInit                   $00                     // VBufA initial values


// === VIA1 BUFFER B ===
#define vPMreq                   0                       // Power manager handshake request
#define vPMack                   1                       // Power manager handshake acknowledge
#define vTestJ                   2                       // Test jumper
//vSync          EQU         3                       ; Synchronous modem
#define vDriveSel                4                       // int drive select (lower drive when 1)
//vHeadSel       EQU         5                       ; head select line for Sony
#define vStereo                  6                       // Stereo sound enable
//vSCCWrReq      EQU         7                       ; SCC write/request line        (input)
//vSndEnb        EQU         7                       ; /sound enable (reset when 1)  (output)

#define vBOut                    ((1<<vPMreq)|\
                                  (0<<vPMack)|\
								  (0<<vTestJ)|\
								  (1<<vSync)|\
								  (1<<vDriveSel)|\
								  (1<<vHeadSel)|\
								  (0<<vStereo)|\
								  (1<<vSndEnb))

#define vBInit                   ((1<<vPMreq)|\
                                  (1<<vPMack)|\
								  (1<<vTestJ)|\
								  (1<<vSync)|\
								  (1<<vDriveSel)|\
								  (0<<vHeadSel)|\
								  (1<<vStereo)|\
								  (1<<vSndEnb))

#define vBufD                    (vBufB)                   // disk head select is buffer B


// === Hardware Base Addresses ===

#define VBase                    $F70000                 // VIA base address
#define AVBufA                   (VBase+vBufA)             // VIA buffer A
#define AVBufB                   (VBase+vBufB)             // VIA buffer B

#define SCCRBase                 $FD0000                 // SCC base read address
#define SCCWBase                 $FD8000                 // SCC base write address
#define sccWrite                 (SCCWBase-SCCRBase)       // general offset for write from read

#define SCSIRd                   $F90000                 // base address of SCSI interface - READ
#define SCSIWr                   $F90001                 // base address of SCSI interface - WRITE
#define MacSCSIBase              $F90000                 // base address of SCSI READ interface
#define MacSCSIDMA               $F90200                 // base address of SCSI DMA
#define MacSCSIHsk               $F90200                 // base address of SCSI handshake
#define wrOffs                   (SCSIWr-SCSIRd)           // write addrs are +1 to the read base

#define SndBase                  $FB0000                 // sound chip's base address

#define MapperBase               $FC0000                 // Mapper RAM base address

#define RAMconfigBase            $FE0200                 // Internal/external RAM control register
#define RAMconfigInit            $0006                   // Init test register                        <v2.6>

// === Video Parameters ===

#define ScreenLow                $FA8000                 // top of screen screen address
#define hcVideoSize              $8000                   // 32k of video memory
#define HcVideoStart             (ScreenLow)
#define HcVideoEnd               (HcVideoStart+hcVideoSize)
#define NTSCMaxX                 512                     // NTSC output is narrow
#define NTSCOffset               8                       //  and centered
#define LCDmode                  0                       // Normal built in screen
#define Mac2mode                 1                       // Custom screen for Mac2
#define NTSCmode                 2                       // NTSC output for Topanga

// === Hardware Base Addresses ===

#define romBSize                 $40000                  // 256K bytes in present ROM
#define ROMStart                 $900000                 // starting address of ROM code

#define DBase                    $F6E1FF                 // disk address base             

#define AccessBase               $FC0200                 // SLIM card DTACK counter load address (what a mouthful)
#define SLIMinserted             3                       // SLIMs inserted bit                        <v2.6>

// === System Software Information ===
#define snd2MemTop               $300                    // SoundLow to Memtop
#define pwm2MemTop               $2FF                    // PWMBuffer to MemTop
#define bufWorldSize             (snd2MemTop)              // total size of the BufPtr world

#define oneSecConst              2                       // gets converted to $20000 for onesec constant
#define numOsTrap                256                     // number of os traps
#define ToolTable                $0E00                   // start of toolbox trap table
#define numTbTrap                1024                    // number of toolbox traps
#define numTrapMask              (numTbTrap-1)             // mask for number of tb traps
#define HeapStart                $1E00                   // Portable starting point   <1.2>
#define DefSysHeap               $18000                  // Default size of the system heap
#define NDfltStackSize           $2000                   // Default stack size


//===================================================;
//   Universal 16 bit Macintosh Hardware Information ;
//===================================================;


// === Interrupt Masks ===
#define hiIntMask                $0700                   // programmer switch only
#define sccIntMask               $0200                   // SCC interrupt Level       <1.5>
#define sccEnblMask              $F9FF                   // mask to enable SCC interrupts
#define viaIntMask               $0100                   // mask for VIA (and VBL) interrupts
#define loIntMask                $0100

// === VIA1 BUFFER A ===
//vSound         EQU         $7                      ; sound volume bits (0..2)
#define vSndPg2                  3                       // select sound page 2 if 0
//vSync          EQU         3                       ; Synchronous modem
//vOverlay       EQU         4                       ; overlay bit (overlay when 1)
//vDriveSel      EQU         4                       ; int drive select (lower drive when 1)
//vHeadSel       EQU         5                       ; head select line for Sony
#define vPage2                   6                       // select video page 2 if 0
//vSCCWrReq      EQU         7                       ; SCC write/request line

// === VIA1 BUFFER B ===
//vRTCData       EQU         0                       ; real time clock data
//vRTCClk        EQU         1                       ; real time clock clock pulses
//vRTCEnb        EQU         2                       ; clock enable (0 for enable)
#define vSW                      3                       // mouse switch (0 when down)
//vFDBInt        EQU         3                       ; Front Desk bus interrupt
#define vX2                      4                       // mouse X level
//vFDesk1        EQU         4                       ; Front Desk bus state bit 0
#define vY2                      5                       // mouse Y level
//vFDesk2        EQU         5                       ; Front Desk bus state bit 1
#define vH4                      6                       // horizontal sync
#define vSCSIMask                6                       // SCSI IRQ mask
//vSndEnb        EQU         7                       ; /sound enable (reset when 1)

#define vPMreq                   0                       // Power manager handshake request
#define vPMack                   1                       // Power manager handshake acknowledge
#define vTestJ                   2                       // Test jumper
//vSync          EQU         3                       ; Synchronous modem
//vDriveSel      EQU         4                       ; int drive select (lower drive when 1)
//vHeadSel       EQU         5                       ; head select line for Sony
#define vStereo                  6                       // Stereo sound enable
//vSCCWrReq      EQU         7                       ; SCC write/request line        (input)

// === VIA1 BUFFER A/B ===
//vSync          EQU         3                       ; Synchronous modem                     <3.1>
#define vDriveSel                4                       // int drive select (lower drive when 1) <3.1>
//vHeadSel       EQU         5                       ; head select line for Sony             <3.1>
//vSCCWrReq      EQU         7                       ; SCC write/request line                <3.1>

// === Hardware Base Addresses ===

#define wrOffs                   1                       // write addrs are +1 to the read base

// === System Software Information ===

#define numOsTrap                256                     // number of os traps
#define ToolTable                $0E00                   // start of toolbox trap table
#define numTbTrap                1024                    // number of toolbox traps
#define numTrapMask              (numTbTrap-1)             // mask for number of tb traps
#define HeapStart                $1E00                   // Laguna starting point <1.2>
#define DefSysHeap               $18000                  // Default size of the system heap
#define NDfltStackSize           $2000                   // Default stack size



#endif                               // ForAmusementOnly

#define HardwarePrivate          1

#endif                                // __INCLUDINGHARDWAREPRIVATEEQU__

