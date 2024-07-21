
/************************************************************

Created: Saturday, July 27, 1991 at 4:33 PM
 Menus.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1992
  All rights reserved.



	Change History (most recent first):

		<23>	 6/26/92	DCL		Miner Formatting Changes. Digging deep for things to do. Getting
									the file ready for ETO 8.
		<22>	 3/27/92	DC		number not known <KSM> - added InsertIntlResMenu and
									reindtroduced InsertFontResMenu
		<21>	  3/9/92	DCL		For New Improved Inside Mac: Added Call names without Abbrevs.:
									AppendResMenu (AddResMenu), DeleteMCEntries (DelMCEntries),
									DeleteMenuItem (DelMenuItem), DisposeMCInfo (DispMCInfo),
									GetMenuHandle (GetMHandle), InsertMenuItem (InsMenuItem),
									SetMenuItemText (SetItem), GetMenuItemText (GetItem). Affected
									Files: Menus.[ph], Traps.[aph].
		<20>	 2/28/92	DCL		Moved GetMBarHeight from Script.h to Menus.h
		<19>	 2/17/92	MH		Remove defintion of InsertFontResMenu.  Not part of public
									interface  (yet?)
		<18>	 9/17/91	MH		params of InsertFontResMenu to standard DB output format
		<17>	 8/22/91	KSM		DCC,#Bruges: Added utility routine InsertFontResMenu for Finder.
		<16>	 7/30/91	JL		Updated Copyright.
		<15>	  2/5/91	stb		gs: remove SaveBits, RestoreBits, DiscardBits
		<14>	 1/28/91	LN		Checked in Database generate file from DSG. Grouping enums into
									groups of 20. Used type SavedBits instead of long to match .p
									file.
		<13>	 1/25/91	stb		JDR: change long bits in SaveBits to long *bits
		<12>	12/20/90	JL		changed constStr255Parameter to ConstStr255Param
		<11>	11/28/90	JL		Put formal parameter names back.
		<10>	11/14/90	JL		Changing InvalidMenuBar back to InvalMenuBar because Invalid is
									misleading. All Inval… calls should be expanded to Invalidate if
									they are expanded at all.
		 <9>	 11/7/90	JL		Changed all #defines to anonymous enums
		 <8>	 11/4/90	dba		used constStr255Parameter; got rid of some extraneous parameter
									names
		 <7>	10/11/90	JL		changed InvalMenuBar to InvalidMenuBar and fixed MenuCRsrc.
		 <6>	 5/31/90	KSM		Add InvalMenuBar and Save/Restore/Discard Bits calls.
		 <5>	  3/5/90	BBH		fixed mCalcItemMsg and mDrawItemMsg
		 <4>	  3/2/90	BBH		added mCalcItemMsg and mDrawItemMsg
	<2>		JAL 	02/08/90 Added MenuCRsrc data structure

************************************************************/


#ifndef __MENUS__
#define __MENUS__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif


enum {


#define noMark '\0'		/*mark symbol for MarkItem*/

/* menu defProc messages */

 mDrawMsg = 0,
 mChooseMsg = 1,
 mSizeMsg = 2,
 mDrawItemMsg = 4,
 mCalcItemMsg = 5,
 textMenuProc = 0,
 hMenuCmd = 27,			/*itemCmd == 0x001B ==> hierarchical menu*/
 hierMenu = -1,			/*a hierarchical menu - for InsertMenu call*/
 mPopUpMsg = 3,			/*menu defProc messages - place yourself*/
 mctAllItems = -98,		/*search for all Items for the given ID*/
 mctLastIDIndic = -99	/*last color table entry has this in ID field*/
};

struct MenuInfo {
 short menuID;
 short menuWidth;
 short menuHeight;
 Handle menuProc;
 long enableFlags;
 Str255 menuData;
};

typedef struct MenuInfo MenuInfo;
typedef MenuInfo *MenuPtr, **MenuHandle;

struct MCEntry {
 short mctID;			/*menu ID.  ID = 0 is the menu bar*/
 short mctItem;			/*menu Item. Item = 0 is a title*/
 RGBColor mctRGB1;		/*usage depends on ID and Item*/
 RGBColor mctRGB2;		/*usage depends on ID and Item*/
 RGBColor mctRGB3;		/*usage depends on ID and Item*/
 RGBColor mctRGB4;		/*usage depends on ID and Item*/
 short mctReserved;		/*reserved for internal use*/
};

typedef struct MCEntry MCEntry;
typedef MCEntry *MCEntryPtr;


typedef MCEntry MCTable[1], *MCTablePtr, **MCTableHandle;







struct MenuCRsrc {
 short numEntries;		/*number of entries*/
 MCTable mcEntryRecs;	/*ARRAY [1..numEntries] of MCEntry*/
};

typedef struct MenuCRsrc MenuCRsrc;
typedef MenuCRsrc *MenuCRsrcPtr, **MenuCRsrcHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitMenus(void)
 = 0xA930; 
pascal MenuHandle NewMenu(short menuID,const Str255 menuTitle)
 = 0xA931; 
pascal MenuHandle GetMenu(short resourceID)
 = 0xA9BF; 
pascal void DisposeMenu(MenuHandle theMenu)
 = 0xA932; 
pascal void AppendMenu(MenuHandle menu,ConstStr255Param data)
 = 0xA933; 
pascal void AddResMenu(MenuHandle theMenu,ResType theType)
 = 0xA94D; 
pascal void AppendResMenu(MenuHandle theMenu,ResType theType)
 = 0xA94D; 
pascal void InsertResMenu(MenuHandle theMenu,ResType theType,short afterItem)
 = 0xA951; 
pascal void InsertMenu(MenuHandle theMenu,short beforeID)
 = 0xA935; 
pascal void DrawMenuBar(void)
 = 0xA937; 
pascal void InvalMenuBar(void)
 = 0xA81D; 
pascal void DeleteMenu(short menuID)
 = 0xA936; 
pascal void ClearMenuBar(void)
 = 0xA934; 
pascal Handle GetNewMBar(short menuBarID)
 = 0xA9C0; 
pascal Handle GetMenuBar(void)
 = 0xA93B; 
#define GetMBarHeight() (* (short*) 0x0BAA)
pascal void SetMenuBar(Handle menuList)
 = 0xA93C; 
pascal void InsMenuItem(MenuHandle theMenu,ConstStr255Param itemString,
 short afterItem)
 = 0xA826; 
pascal void InsertMenuItem(MenuHandle theMenu,ConstStr255Param itemString,
 short afterItem)
 = 0xA826; 
pascal void DelMenuItem(MenuHandle theMenu,short item)
 = 0xA952; 
pascal void DeleteMenuItem(MenuHandle theMenu,short item)
 = 0xA952; 
pascal long MenuKey(short ch)
 = 0xA93E; 
pascal void HiliteMenu(short menuID)
 = 0xA938; 
pascal void SetItem(MenuHandle theMenu,short item,ConstStr255Param itemString)
 = 0xA947; 
pascal void SetMenuItemText(MenuHandle theMenu,short item,ConstStr255Param itemString)
 = 0xA947; 
pascal void GetItem(MenuHandle theMenu,short item,Str255 itemString)
 = 0xA946; 
pascal void GetMenuItemText(MenuHandle theMenu,short item,Str255 itemString)
 = 0xA946; 
pascal void DisableItem(MenuHandle theMenu,short item)
 = 0xA93A; 
pascal void EnableItem(MenuHandle theMenu,short item)
 = 0xA939; 
pascal void CheckItem(MenuHandle theMenu,short item,Boolean checked)
 = 0xA945; 
pascal void SetItemMark(MenuHandle theMenu,short item,short markChar)
 = 0xA944; 
pascal void GetItemMark(MenuHandle theMenu,short item,short *markChar)
 = 0xA943; 
pascal void SetItemIcon(MenuHandle theMenu,short item,short iconIndex)
 = 0xA940; 
pascal void GetItemIcon(MenuHandle theMenu,short item,short *iconIndex)
 = 0xA93F; 
pascal void SetItemStyle(MenuHandle theMenu,short item,short chStyle)
 = 0xA942; 
pascal void GetItemStyle(MenuHandle theMenu,short item,Style *chStyle); 
pascal void CalcMenuSize(MenuHandle theMenu)
 = 0xA948; 
pascal short CountMItems(MenuHandle theMenu)
 = 0xA950; 
pascal MenuHandle GetMHandle(short menuID)
 = 0xA949; 
pascal MenuHandle GetMenuHandle(short menuID)
 = 0xA949; 
pascal void FlashMenuBar(short menuID)
 = 0xA94C; 
pascal void SetMenuFlash(short count)
 = 0xA94A; 
pascal long MenuSelect(Point startPt)
 = 0xA93D; 
pascal void InitProcMenu(short resID)
 = 0xA808; 
pascal void GetItemCmd(MenuHandle theMenu,short item,short *cmdChar)
 = 0xA84E; 
pascal void SetItemCmd(MenuHandle theMenu,short item,short cmdChar)
 = 0xA84F; 
pascal long PopUpMenuSelect(MenuHandle menu,short top,short left,short popUpItem)
 = 0xA80B; 
pascal long MenuChoice(void)
 = 0xAA66; 
pascal void DelMCEntries(short menuID,short menuItem)
 = 0xAA60; 
pascal void DeleteMCEntries(short menuID,short menuItem)
 = 0xAA60; 
pascal MCTableHandle GetMCInfo(void)
 = 0xAA61; 
pascal void SetMCInfo(MCTableHandle menuCTbl)
 = 0xAA62; 
pascal void DispMCInfo(MCTableHandle menuCTbl)
 = 0xAA63; 
pascal void DisposeMCInfo(MCTableHandle menuCTbl)
 = 0xAA63; 
pascal MCEntryPtr GetMCEntry(short menuID,short menuItem)
 = 0xAA64; 
pascal void SetMCEntries(short numEntries,MCTablePtr menuCEntries)
 = 0xAA65; 
pascal void InsertFontResMenu(MenuHandle theMenu, short afterItem,
				short scriptFilter)
 = {0x303C, 0x0400, 0xA825};
pascal void InsertIntlResMenu(MenuHandle theMenu, ResType theType,
				short afterItem, short scriptFilter)
 = {0x303C, 0x0601, 0xA825};
MenuHandle newmenu(short menuID,char *menuTitle); 
void getitem(MenuHandle menu,short item,char *itemString); 
void appendmenu(MenuHandle menu,char *data); 
void insmenuitem(MenuHandle theMenu,char *itemString,short afterItem); 
long menuselect(Point *startPt); 
void setitem(MenuHandle menu,short item,char *itemString); 
#ifdef __cplusplus
}
#endif

#endif
