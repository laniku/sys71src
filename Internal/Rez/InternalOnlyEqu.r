/*
	File:		InternalOnlyEqu.r

   	Contains:   Internal Only Equates

	Written by: Robert Klein and the Teen Tones

	Copyright:  © 1990-1993 by Apple Computer, Inc., all rights reserved.
	
	Change History (most recent first):
	
	  <SM15>	11/23/93	rab		Recycled boxCarnation33. Now is boxSoftmacSUN. Changed boxlfag
									#127 to boxExtended to signify new extended boxflag mechanism.
	  <SM14>	11/16/93	RLE		fix what appears to be a typo from my previous checkin
	  <SM13>	11/11/93	rab		Added boxflags for Softmac…
	  <SM12>	11/10/93	fau		Added boxflag for TNTProto1, reussing one from Tesseract.
	  <SM11>	 11/9/93	RLE		added boxflags for 603-based PowerBooks
	  <SM10>	 11/9/93	KW		added boxflags for STP machines
	   <SM9>	 11/8/93	JRH		boxDBLite16 is now boxPowerBookDuo250. boxDBLite20 is now
									boxPenLite. boxEscher25 is now boxYeagerFSTN. boxEscher33 is now
									boxPowerBookDuo270C.
	   <SM8>	08-16-93	jmp		Brought the BoxFlag list up-to-date with InternalOnlyEqu.a.
	   <SM7>	 8/11/93	KW		adding some new smurf machines
		 <6>	 7/21/93	JRH		Changed the definition of boxPenLite, and added Yeager boxFlags
									and a few others that were missing.
	   <SM5>	04-01-93	jmp		Sync’ed up the BoxFlag list to match the InternalOnlyEqu.a file.
	   <SM4>	12/23/92	RC		Added Support for Smurf on Wombat
	   <SM3>	 12/4/92	fau		Added boxTempest33 and boxCyclone40.  Changed boxCyclone to
									boxCyclone33 and boxTempest to boxTempest25.
	   <SM2>	10-29-92	jmp		Sync’ed-up the BoxFlag list with the HORROR, Excelsior, and
									Reality projects.
*/
//     <SM14>     8/17/92    CCH     Added equates for new universal flag longwords.
//     <SM13>      8/9/92    CCH     Added boxflags for PDM and Tesseract.
//     <SM12>      7/7/92    CSS     Note that with this update we are current upto Reality
//                                   <R22>.  Update from Reality:
//                                   <21> 4/8/92 JSM #1026795: Add boxMacLCII (a.k.a. Foster Farms).
//     <SM11>      7/1/92    GA      change old boxflagwombat20 to boxwombat33f
//     <SM10>      7/1/92    GA      adding new boxflags for wombat and moving boxcycloneevt1 from 49
//                                   to 54
//      <SM9>     6/21/92    RB      Added a temporary boxCycloneEVT1 so that we can support EVT1
//                                   boards for a couple of weeks by doing runtime checks.
//      <SM8>      6/4/92    KW      roll back in SM5,SM6
//      <SM7>      6/4/92    KW      rolled back to SM4 until I get other video stuff building and
//                                   added
//      <SM6>      6/4/92    KW      Adding boxWombat25... Missed it with last checkin
//      <SM5>      6/4/92    KW      (NJV,H20) Added LongBSR6 macro.
//                                   (djw,H22) Add boxFlag for powerbook 145
//                                   (BG,H21) Changed boxWombatLC to boxWombat20, boxWombat to
//                                   boxWombat25. Added boxWombat40, boxWLCD20, boxWLCD25.
//      <SM4>     5/17/92    kc      Roll in Horror Changes. Add boxFlags for new machines. Add
//                                   DockingGlobals equ. Add BigBSR5 macor
//      <SM3>      4/7/92    JSM     Renumber boxVail, boxCarnation, and boxDBLite; roll-in changes from Reality:
//       <20>     3/24/92    JSM     Nuke more code names: boxAuroraCX25 is boxMacIIci, boxF19 is
//                                   boxMacIIfx.
//      <SM2>     2/11/92    RB      Updated box flag values
//       <19>    12/26/91    RB      Removed PowerMgr definitions, these are now in their own file.
//                                   PowerPrivEqu.a
//       <18>     12/2/91    SAM     Changed boxFlag names for the released CPUs to their official
//                                   names.
//       <17>    10/28/91    SAM/KSM Rolled in Regatta changes.
//       
//                                    <9>     8/30/91    SAM     (ag) changed low power warn level on TIM to 5.85
//                                    <8>     8/22/91    SAM     Updating equates to more closely resemble the TERROR sources.
//                                    <7>      8/1/91    SAM     Added box flag for Zydeco (which equals Eclipse33). Updating
//                                                               InVidFlags.
//                                    <6>     7/25/91    SAM     Reconfiguring the box flag values for the new CPUs.
//                                    <5>     7/18/91    SAM     Added a boxFlag for Eclipse33
//                                    <4>      7/1/91    SAM     Added fields to the PmgrRec for Bad Battery stuff.
//                                    <3>     6/14/91    SAM     Added boxDBLite and boxAsahi. (HJR) Updated this file so its
//                                                               equal with the one in TERROR. (ag) added definition of new bit
//                                                               in pmgrflag.
//                                    <1>     5/22/91    SAM     Split off from 7.0 GM sources.
//
//       <16>      8/6/91    KIP     Add boxflag values for new CPUs.
//       <15>     7/24/91    MH      Added conditional wrapper(s) to prevent duplication of public
//                                   interface declarations: SleepRequest, SleepDemand, SleepWakeUp,
//                                   SleepqType, NoCalls, NoRequest, ADBBase, SlotQDT, SlotPrTbl,
//                                   SlotVBLQ, ScrnVBLPtr, SlotTICKS
//       <14>     4/10/91    ag      change pmfree word to pmgrflag and pmfree bytes. changed bit
//                                   definition of insleep flag.
//       <13>     2/15/91    ag      MSH: #BRC 80886 - Added a bit definition in sleep flags.
//       <12>     1/30/91    gbm     sab, #38: Change the ‘already including this file’ variable to
//                                   all uppercase (for security reasons)
//       <11>      1/8/91    SAM     Added BoxFlags for Spike and Apollo.
//       <10>    10/22/90    JJ      Rex V8: Change all box flag references to use boxMacLC. Get rid
//                                   of boxElsie and boxElsieV8.
//        <9>     9/25/90    SAM     Changing boxFlag names for XO, Elsie & Erickson to Classic, LC ,
//                                   and IIsi BoxMacLC/MacIIsi.
//        <8>     9/13/90    MSH     Added some LCD video RAM locations to be used by TIM for power
//                                   cycling and sleep.
//        <7>      7/9/90    JJ      Add box flag for V8 Elsie.
//        <6>      5/8/90    MSH     Add new power cycling equs for Waimea.
//        <4>      4/4/90    MSH     Add Waimea box flag.
//        <3>      2/8/90    HJR     Change box flag to those of Private.a, Rev. 5.
//        <2>      2/4/90    GA      Added Low Mem global definition for Egret Manager "EgretBase"
//        <1>     1/30/90    CCH     Moved in REAL private equates from Private.a.
//

// Memory Manager
//————————————————————————————————————————————————————————————————————————————————————
//
//   This file contains proprietary information and should not be released outside
//   of Apple Computer.  This is important!  
//
//————————————————————————————————————————————————————————————————————————————————————
//
//

#ifndef __INCLUDINGINTERNALONLYEQU__
#define __INCLUDINGINTERNALONLYEQU__ 1


//  **********  IMPORTANT ****************
//  *******    DO NOT RELEASE FOLLOWING EQUs TO OUTSIDE of Apple Computer *********
//  *********
#define tagBC32                  0                       // Tag field [byte]                              <v1.7>
#define MPtag32                  1                       // Master Pointer Tag field [byte]               <v1.7>
#define SizeCor32                3                       // size correction field [byte]                  <v1.7>
#define blkSize32                4                       // physical block size [long]                    <v1.7>
#define handle32                 8                       // back pointer to master pointer [pointer]      <v1.7>
#define blkData32                12                      // data starts here                              <v1.7>

#define tagBC24                  0                       // Tag and Byte Count field [long]               <v1.7>
#define handle24                 4                       // back pointer to master pointer [pointer]      <v1.7>
#define blkData24                8                       // data starts here                              <v1.7>

#define minFree                  12                      // (minimum block size) for old MemManager       <v2.0>
#define minFree24                12                      // (minimum block size) for 24 bit MemManager    <v2.0>
#define minFree32                16                      // (minimum block size) for 32 bit MemManager    <v2.0>
#define freeTag                  $0                      // Tag for Free block
#define nRelTag                  $40000000               // Tag for Non-Relocatable block
#define relTag                   $80000000               // Tag for Relocatable block
#define minAddr                  $0                      // Min legal address
#define maxAddr                  $800000                 // Max legal address for 512K machine
#define maxMasters               $1000                   // Ridiculously large allocation chunk size
#define dfltMasters              32                      // Default to 32 master pointers

#define MMPRAMloc            $0001008A           // PRAM location for memory manager flag (1 byte)        <v2.1>
#define MMFlags              $1EFC               // (1 byte) low memory location to store the flags       <v2.1>
// bit settings in MMflags:
#define MMStartMode          $0                  // .... ...n, n=0 for 24 bit, n=1 for 32 bit             <v2.1>
#define MMMixed              $1                  // .... ..n., n=0 for no mixed mode, n=1 for mixed 23/32 mode        <v2.1>
#define MMSysheap            $2                  // .... .n.., n=0 for 24 bit system heap, n=1 for 32 bit system heap <v2.1>
#define MMROZheap            $3                  // .... n..., n=0 for 24 bit ROZ heap, n=1 for 32 bit ROZ heap       <v2.1>
#define mmHighSysHeap        $4                  // ... n...., n=1 for system heap starting way high, 0 for normal    <3.3>

#define SystemInfo           $0B73               // System Info Byte                                      <v3.7>
// bit settings in SystemInfo byte
#define Systemis24bit        $0                  // .... ...n, n=1 for 24 bit, n=0 for 32 bit system      <v3.7>
#define Sysheapis24bit       $1                  // .... ..n., n=1 for 24 bit, n=0 for 32 bit system heap <v4.1>


#define PhysMemTop           $1EF8               // Total physical RAM --- including memory for screen buffer         <v2.8>
#define RealMemTop           $1EF4               // amount of physcial RAM available for system use                   <v2.8>
                                            // --- not including memory for screen buffer                        <v2.8>
#define Phys2Log             $1EF0               // Physical to logical address convertion for MMU translation table  <v2.8>

#define vMMNoPrologue        $1EE0               // jump vector to MMnoPrologue                           <v3.7>
#define vMMPPrologue         $1EE4               // jump vector to MMPPrologue                            <v3.7>
#define vMMPrologue          $1EE8               // jump vector to MMPrologue                             <v3.7>
#define vMMHPrologue         $1EEC               // jump vector to MMHPrologue                            <v3.7>
#define vMMRHPrologue        $1FE0               // jump vector to MMRHPrologue                           <v3.7>
#define vMMMMPrologue        $1FE4               // jump vector to MMMMPrologue
#define vMMEpilogue          $1FE8               // jump vector to MMEpilogue                             <v3.7>
#define vMMNoErrEpilogue     $1FEC               // jump vector to MMNoErrEpilogue                        <v3.7>

#define LockMemCT            $1FF4               // (4) bytes, Lock Memory count                          <v3.9>
#define DockingGlobals       $1FF8               // pointer to docking globals                            <H12>

//-------------------------------------------------------------------
//
// Time Manager Local Variable Struct
//

#define TimeVars                 $B30                    // the low memory pointer to the variable struct

//   the following only apply to the old time manager, and may be used in patch files.
#define TTInt                    0                       // time of this interrupt cycle [long]
#define TTAppoint                4                       // pointer to next appointment in MSQueue [long]
#define MSQueue                  8                       // queue header for MS Queue [10 bytes]
#define MSLSize                  18                      // size of these variables for allocation purposes

//-------------------------------------------------------------------
//   Misc low memory private variables
//
#define SCCIOPFlag               $0BFE       // low mem copy of SCC IOP mode PRAM byte as of startup time     <4.9>
#define IOPMgrVars               $0C28       // low memory pointer to IOPmgr data structures      <3.1>

#ifndef __SysEqu__
#define ADBBase                  $0CF8       // (long) pointer to Front Desk Buss Variables       <3.1>
#endif

#define EgretBase                $0DE0       // Egret Manager global variables <2>

#ifndef __SysEqu__
#define SlotQDT                  $0D04       // ptr to slot Int queue table                       <3.1>
#define SlotPrTbl                $0D08       // ptr to slot priority table (ROM $78 only)         <3.1>
#define SlotVBLQ                 $0D0C       // ptr to slot VBL queue table (ROM $78 only)        <3.1>
#define ScrnVBLPtr               $0D10       // save for ptr to main screen VBL queue             <3.1>
#define SlotTICKS                $0D14       // ptr to slot tickcount table (ROM $78 only)        <3.1>
#endif

#define AddrMapFlags             $0DD0       // (long) valid bits for base addresses 0-31  (universal ROM)    <2.7>
#define AddrMapFlags1            $2400       // (long) valid bits for base addresses 32-63 (universal ROM)    <SM14>
#define AddrMapFlags2            $2404       // (long) valid bits for base addresses 64-95 (universal ROM)    <SM14>
#define UnivROMFlags             $0DD4       // (long) product specific flags for universal ROM  0-31         <2.7>
#define UnivROMFlags1            $2408       // (long) product specific flags for universal ROM 32-63         <SM14>
#define UnivROMFlags2            $240C       // (long) product specific flags for universal ROM 64-95         <SM14>
#define UnivInfoPtr              $0DD8       // (long) Pointer to configuration information for universal ROM <2.7>


//-------------------------------------------------------------------
// Equates for values that the BoxFlag global may take:  each identifies
// a particular logic board.

#define BoxFlag                  $0CB3       // (byte) identifies which product we are running on             <3.6>

#define boxUnknown               $FD         // unknown product                                               <3.6>
#define boxPlus                  $FE         // a Mac Plus                                                    <3.6>
#define boxSE                    $FF         // a Mac SE                                                      <3.6>
#define boxMacII                 0           // a Mac II                                                      <3.6>
#define boxMacIIx                1           // a Mac IIx                                                     <3.6>
#define boxMacIIcx               2           // a Mac IIcx                                                    <3.6>
#define boxSE30                  3           // a Mac SE 30                                                   <3.6>
#define boxPortable              4           // a Mac Portable                                                <3.6>
#define boxMacIIci               5           // Aurora 25MHz 3 slot package                                   <3.6>
#define boxFourSquare            6           // a Four Square (030, 68882, 6 slots, MDU, 2 IOPs, SCSI DMA) (never shipped)    <3.6>
#define boxMacIIfx               7           // a F19 (030, 68882, 6 slots, OSS, BIUs, MC, 2 IOPs, SCSI DMA)  <3.6>
#define boxAuroraCX16            8           // Aurora 16MHz 3 slot package (never shipped)                   <3.6>
#define boxAuroraSE25            9           // Aurora 25MHz SE30 package (reserved for future)               <3.6>
#define boxAuroraSE16            10          // Aurora 16MHz SE30 package (reserved for future)               <3.6>
#define boxMacClassic            11          // XO (SE with 1 int floppy, brightness PWM)                     <3>     <9>
#define boxMacIIsi               12          // Erickson (20MHz, 030, optl 68882, MDU, RBV,1 direct slot)     <3>     <9>
#define boxMacLC                 13          // Elsie (16 MHz, 020, 1 direct slot, V8 chip)                   <3><7>  <9>
#define boxQuadra900             14          // Eclipse (040, 5 slots+PDS, VIA1&2, Orwell MCA, 2 IOPs, SCSI DMA)  <5.1>
#define boxPowerBook170          15          // Tim (25 MHz, 030, optional FPU, VIA1&2, JAWS, PMGR, 1 direct slot <4>
#define boxQuadra700             16          // Spike (25MHz 040)
#define boxClassicII             17          // Apollo
#define boxPowerBook100          18          // Asahi (Its a Sony!) Portable                                  <2>
#define boxPowerBook140          19          // TimLC 16 Mhz Tim; no FPU
#define boxQuadra950             20          // a Mac Quadra 950 (33MHz 040, 5 slots+PDS, VIA1&2, Orwell MCA, 2 IOPs, SCSI 2*53c96)   <H18>
#define boxLCIII                 21          // Vail (25 MHz, 030, optional FPU, 1 PDS, Sonora)                   <H14>
#define boxSoftmacSUN	         22          // Softmac on Sun, (recycled, was boxCarnation33)										<SM15>
#define boxPowerBookDuo210       23          // a PowerBook Duo 210 (25MHz 030, PMGR, expansion connector, no floppy)
#define boxCentris650            24          // Wombat (25MHz 040 or 040LC, 3 slots+PDS, VIA1&2, djMEMC, SCSI 53c96, optional enet)<H21>
#define boxColumbia              25          // Columbia (25 Mhz, 030, PDS, Atlantis Decoder, Color Classic)
#define boxPowerBookDuo230       26          // a PowerBook Duo 230 (33MHz 030, PMGR, expansion connector, no floppy)          <H16>
#define boxPowerBook180          27          // a PowerBook 180 (33Mhz, 030, FPU, VIA1&2, Niagra, PMGR, 1 direct slot) 
#define boxPowerBook160          28          // a PowerBook 160 (25Mhz, 030, FPU, VIA1&2, Niagra, PMGR, 1 direct slot)
#define boxQuadra800             29          // Wombat (20MHz 040LC, 3 slots+PDS, VIA1&2, djMEMC, SCSI 53c96, optional enet)      <H21>
#define boxQuadra650             30          // Wombat (33Mhz 040, 3 slots+PDS, VIA1&2, djMEMC, SCSI53c96, enet)                  <H21>
#define boxMacLCII               31          // Foster Farms (68030 LC)
#define boxPowerBookDuo250       32          // Duo 250 (Ansel)						<SM9>
#define boxPenlite			     33	 		 // Pen-based DUO
#define boxVail16                34          // Vail (16 MHz, 030, optional FPU, 1 PDS, Sonora)                   <H14>
#define boxCarnation25           35          // Carnation (25 MHz, 030, FPU, 3 NuBus slots)                       <H14>
#define boxCarnation16           36          // Carnation (16 MHz, 030, FPU, 3 NuBus slots)                       <H14>
#define boxCyclone33             37          // Cyclone                                                           <H14>
#define boxBrazil16L             38          // Brazil (16Mhz, Lego package)                                      <H15>
#define boxBrazil32L             39          // Brazil (32MHz on motherboard, Lego package)                       <H15>
#define boxBrazil16F             40          // Brazil (16MHz, Fridgidaire minitower package)                     <H15>
#define boxBrazil32F             41          // Brazil (32MHz on motherboard, Fridgidaire package)                <H15>
#define boxBrazilC               42          // Brazil (any speed, any package for consumer release)              <H15>
#define boxSlice                 43          // Slice                                                             <H17>
#define boxMonet                 44          // Monet (33MHz 030/FPU, VIA1&2, Niagara, PMGR, 16 color LCD, 1 direct slot) <H19>
#define boxWombat40              45          // Wombat (40MHz 040, 3 slots+PDS, VIA1&2, djMEMC, SCSI 53c96, enet)                 <H21>
#define boxCentris610            46          // WLCD (20 MHz 040LC, PDS only, VIA1&2, djMEMC, SCSI 53c96, optional enet)          <H21>
#define boxQuadra610             47          // WLCD (25 MHz 040LC, PDS only, VIA1&2, djMEMC, SCSI 53c96, optional enet)          <H21>
#define boxPowerBook145          48          // PowerBook 145 (25MHz 030, no FPU, otherwise same as 140)                          <H22>
#define boxBrazil32cF            49			 // Brazil (32MHz w/ext cache, Fridgidaire package)
#define boxHook                  50			 // Hook.
#define boxUnused				 51			 //  (was a Consumer WLCD ... now unused) 													<H26><SM41>
#define boxWombat20				 52			 //  Wombat (20MHz 040LC, 3 slots+PDS, VIA1&2, djMEMC, SCSI 53c96, optional enet, Lego)	<H26>
#define boxWombat40F			 53			 //  Wombat (40MHz 040, 3 slots+PDS, VIA1&2, djMEMC, SCSI 53c96, enet, Frigidaire package)	<H26>
#define boxCentris660AV			 54			 //  (In HORROR, Reality, and Excelsior, this is called BoxCycloneEVT1.)
#define boxPDM					 55			 //  Mac/RISC dude (88100 ... (temp) )
#define boxRiscQuadra700		 55			 //  Quadra 700 w/Risc Card																<SM40>
#define boxVail33				 56			 //  Vail (33 MHz, 030, optional FPU, 1 PDS, ENET, Sonora)									<H31>
#define boxWLCD33				 57			 //  WLCD (33 MHz 040, PDS only, VIA1&2, djMEMC, SCSI 53c96, optional enet, QFC)			<H31>
#define boxPDM66F				 58			 //  PDM/Cold Fusion (66 Mhz 601, Fridge)													<SM41>
#define boxPDM80F				 59			 //  PDM/Cold Fusion (80 Mhz 601, Fridge)													<SM41>
#define boxPDM100F				 60			 //  PDM/Cold Fusion (100 Mhz 601, Fridge)													<SM41>
#define boxTNTProto1			 61			 //  TNT Bringup Board															<H31>
#define boxTesseractF			 62			 //  Tesseract (66 Mhz 601, Frigidaire)													<H31>
#define boxTesseractC			 63			 //  Tesseract (66 Mhz 601, Consumer)														<H31>
#define boxJust930				 64			 //  930																					<H31>
#define boxHokusai				 65			 //  Hokusai (33MHz 030/FPU, VIA1&2, Niagara, PMGR, 256 color TFT LCD, 1 direct slot)		<H31>
#define boxBlackbird			 66			 //  Blackbird (50/25MHz 040,   VIA1&2, Pratt, PGE, 256 color 9.4" TFT LCD, 1 direct slot)			<H31>
#define boxBlackbirdLC			 67			 //  Blackbird (50/25MHz 040LC, VIA1&2, Pratt, PGE, 256 color 9.4" STN LCD, 1 direct slot)		<H31>
#define boxPDMEvt1				 68			 //  PDM (? Mhz 601, WLCD, Evt1)		<SAM>												<H31>
#define boxPDM50WLCD			 69			 //  PDM (50 Mhz 601, WLCD)			<SAM>												<H31>
#define boxYeagerFSTN			 70			 //  LC040 Duo with FSTN																	<SM9>
#define boxPowerBookDuo270C		 71			 //  33MHz Escher (030, PMGR, expansion connector, no floppy, 256 color TFT LCD, FPU)		<SM9>
#define boxQuadra840AV			 72			 //  Cyclone <40 Mhz, 040, FPU, 3NuBus slots+DAVE+PUS)										<SM18>
#define boxTempest33			 73			 //  Tempest <33 Mhz, 040LC, 1 Direct Slot slots+DAVE+PUS)									<SM18>
#define boxHook33				 74			 //  Hook 33MHz
#define boxSlice25				 75			 //  Slice 25MHz
#define boxRiscCentris650		 76			 //  Centris650 w/RISC Smurf card															<SM40>
#define boxSlice33				 77			 //  								<15>
#define boxNorad				 78			 //  a PowerBook 160 at 33Mhz (see above)
#define boxBudMan				 79			 //  25MHz DBLite with SWIM-2 Floppy and Midas (touchpad)
#define boxPrimus20				 80			 //  Primus  (20MHz 040LC, 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, LC package)				<H37><SM28>
#define boxOptimus20			 81			 //  Optimus (20MHz 040LC, 1 LC slot, 1 CommSlot, VIA1&2, MEMCjr, SCSI 53c96, Hook package)<H37><SM28>
#define boxHookTV				 82			 //  HookTV  (32MHz 030, no slots, TV Tuner, VIA1&2, VISA decoder, 512k VRAM soldered)	<SM30>
#define boxLC475				 83			 //  Primus  (25MHz 040LC, 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, LC package)				<H38><SM31><SM41>
#define boxPrimus33				 84			 //  Primus  (33MHz 040LC, 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, LC package)				<H38><SM31>
#define boxOptimus25			 85			 //  Optimus (25MHz 040LC, 1 LC slot, 1 CommSlot, VIA1&2, MEMCjr, SCSI 53c96, Hook package)<H38><SM31>
#define boxLC575				 86			 //  Optimus (33MHz 040  , 1 LC slot, 1 CommSlot, VIA1&2, MEMCjr, SCSI 53c96, Hook package)<H38><SM31><SM41>
#define boxAladdin20			 87			 //  Aladdin (20MHz 040LC, 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, ELB package)				<H38><SM31>
#define boxQuadra605			 88			 //  Aladdin (25MHz 040LC, 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, ELB package)				<H38><SM31><SM41>
#define boxAladdin33			 89			 //  Aladdin (33MHz 040  , 1 LC slot, VIA1&2, MEMCjr, SCSI 53c96, ELB package)				<H38><SM31>
#define boxMalcolm25			 90			 //  Malcolm (25MHz 040(,LC), PDS only, VIA1&2, MEMCjr, SCSI 53c96, optional ENet, QFC)	<SM35>
#define boxMalcolm33			 91			 //  Malcolm (33MHz 040, PDS only, VIA1&2, MEMCjr, SCSI 53c96, optional ENet, QFC)	<SM35>
#define boxSlimus25				 92			 //  Slimus  (25MHz 040LC, exactly like an Optimus except in a Color Classic box)			<SM36>
#define boxSlimus33				 93			 //  Slimus  (33MHz 040LC, exactly like an Optimus except in a Color Classic box)			<SM36>
#define boxPDM66WLCD			 94			 //  PDM (66Mhz 601, WLCD)
#define boxPDM80WLCD			 95			 //  PDM (80Mhz 601, WLCD)
#define boxYeagerG				 96			 //  Yeager DUO (25MHz 040LC, PMGR, expansion connector, no floppy, MBT, Gray AM)
#define boxYeagerC				 97			 //  Yeager DUO (25MHz 040LC, PMGR, expansion connector, no floppy, MBT, Color AM)
#define boxRiscQuadra900		 98			 //  900 with Smurf card																	<SM40>
#define boxRiscQuadra950	 	 99			 //  950 with Smurf card																	<SM40>
#define boxRiscCentris610		100			 //  C610 with Smurf card																	<SM40>
#define boxRiscQuadra800		101			 //  Q800 with Smurf card																	<SM40>
#define boxRiscQuadra610		102			 //  Q610 with Smurf card																	<SM40>
#define boxRiscQuadra650		103			 //  Q650 with Smurf card																	<SM40>
#define boxRiscTempest			104			 //  Tempest with Smurf card																<SM40>
#define boxPDM50L				105			 //  PDM/Carl Sagan (50MHz 601, HMC, AMIC, AWACS, Mace ENet, Lego package)					<SM41>
#define boxPDM66L				106			 //  PDM/Carl Sagan (66MHz 601, HMC, AMIC, AWACS, Mace ENet, Lego package)					<SM41>
#define boxPDM80L				107			 //  PDM/Carl Sagan (80MHz 601, HMC, AMIC, AWACS, Mace ENet, Lego package)					<SM41>
#define boxBlackbirdBFD			108			 //  Blackbird (66/33MHz 040LC, VIA1&2, Pratt, PGE, 256 color 10.X" TFT LCD, 1 direct slot)	<H31>
#define boxJedi					109			 // Jedi (33MHz, 030, low cost AIO powerbook, MSC, IDE, floppy )							<SM46>
#define boxSTPQ700				110			 // Q700 with STP card																		<SM10>
#define boxSTPQ900				111			 // Q900 with STP card																		<SM10>
#define boxSTPQ950				112			 // Q950 with STP card																		<SM10>
#define boxSTPC610				113			 // C610 with STP card																		<SM10>
#define boxSTPC650				114			 // C650 with STP card																		<SM10>
#define boxSTPQ610				115			 // Q610 with STP card																		<SM10>
#define boxSTPQ650				116			 // Q650 with STP card																		<SM10>
#define boxSTPQ800				117			 // Q800 with STP card																		<SM10>
#define boxAJ					118			 // AJ (66 MHz 603, duo powerbook)															<SM11>
#define boxAJ80					119			 // AJ (80 MHz 603, duo powerbook)															<SM11>
#define boxMalcolmBB			120			 // Malcolm (argh, same name as WLCD II)(66 MHz 603 upgrade to Blackbird)					<SM11>
#define boxMalcolmBB80			121			 // Malcolm (argh, same name as WLCD II)(80 MHz 603 upgrade to Blackbird)					<SM11>
#define boxM2					122			 // M2 (66 MHz 603, duo powerbook)															<SM11>
#define boxM280					123			 // M2 (80 MHz 603, duo powerbook)															<SM11>
#define boxSoftmacHP			124			 // Softmac on HP																			<SM13>
#define boxSoftmacIBM			125			 // Softmac on IBM																			<SM13>
#define boxSoftmacAUX			126			 // Softmac on AUX																			<SM13>
#define boxExtended				127			 // Uses new extended boxflag mechanism																			<SM13>
#define boxLastKnown			boxExtended	 //  Please, always update this entry!
 
#endif   // ...already included 
