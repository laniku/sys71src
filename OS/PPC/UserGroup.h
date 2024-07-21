/*
	File:		UserGroup.h

	Contains:	xxx put contents here (or delete the whole line) xxx

	Written by:	xxx put name of writer here (or delete the whole line) xxx

	Copyright:	© 1989-1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 4/10/90	S		To Support PPC Global Check Box.
		 <3>	 4/10/90	S		To Support PPC Global Check Box.
		 <2>	 2/27/90	S		To User Guest Record.
	   <1.0>	10/12/89	CVC		Adding Access Control for the first time.

	To Do:
*/

/*EASE$$$ READ ONLY COPY of file “UserGroup.h”
** 1.0	CVC 10/12/1989 Adding Access Control for the first time.
** END EASE MODIFICATION HISTORY */
#ifndef UserGroup_h
#define UserGroup_h

#define User 0
#define Group -1
#define nogroup  0
#define KeyUserID  1
#define MaxGroups  42

// flag constants
#define LoginEnabled  0x100
#define SuperUser  0x200
#define NoChangePwd  0x400
#define UInited  0x800
#define PhoneLogin  1
#define CallBack  2
#define GIconInited  1
#define GWindInited  2
#define Apple2  1
#define NoGuests  2
#define UGInited  4
#define IACGuestEnabled  16
#define IACGlobalEnabled 32

	// B-tree User Authentication Record
struct UserAcRecord
	{
	 char Password[8];		// user password
	 long UserID;			// user ID
	 short UserFlags;		// user flags: LoginEnabled, SuperUser, NoChangePwd, inited
	 Point IconLoc;			// location of user icon
	 long Spare[4];			// extra space
	 short NumGroups;		// number of groups the user belongs to
	 long Groups[MaxGroups]; // groups the user belongs to	
	};
typedef struct UserAcRecord UserAcRecord;

struct GroupIDRecord
	{
	 long GroupID;			// group ID
	 unsigned char Inited;
	 Point IconLoc;
	 Rect GroupWind;
	 short GroupView;
	 Point Scroll;
	 long Spare[2];			// extra space
	};
typedef struct GroupIDRecord GroupIDRecord;
	
struct UGNameRecord
	{
	 short UGFlag;
	 Str31 UGName;
	 long Spare[2];
	};
typedef struct UGNameRecord UGNameRecord;

struct GroupMemberRecord
	{
	 Boolean Inited;
	 Point IconLoc;
	};
typedef struct GroupMemberRecord GroupMemberRecord;

struct ULInfoRecord
	{
	 long UniqueID;			// UG file's unique ID
	 short Version;			// User List version
	 Str31 ServerName;		// the server name
	 char ServerFlags;		// Flags: Apple 2 mode, No Guest Users, inited
	 char AdPWLen;			// length of Admin password
	 char AdminPW[8];		// the Admin password
	 long MaxID;			// maximum ID used
	 Rect UGWind;
	 short View;
	 Point Scroll;
	 short Spare1;
	 long Spare2[13];			// extra space
	};
typedef struct ULInfoRecord ULInfoRecord;

struct FolderInfoRecord
	{
	char ShortName[13];		// short name
	int PDFT;				// ProDOS File Type
	int PDAT;				// ProDOS Aux Type
	int SubFolders;			// number of folders in this folder
	long CreatorID;			// creator ID
	long Access;			// access control
	long GroupID;			// group ID
	};
typedef struct FolderInfoRecord FolderInfoRecord;

struct PhoneRecord
	{
	 short PhoneFlags;		// 976 flags: Bit 0 login, Bit 1 call back
	 short RetryCount;
	 Str31 CallNum;			// 976 Callback number
	};
typedef struct PhoneRecord PhoneRecord;

union BTRecord
	{
	ULInfoRecord A;
	UGNameRecord N;
	GroupIDRecord G;
	UserAcRecord U;
	GroupMemberRecord M;
	FolderInfoRecord F;
	PhoneRecord T;
	char B[256];
	};
typedef union BTRecord BTRecord;
	
#endif
