
/************************************************************

Created: Saturday, July 27, 1991 at 4:11 PM
 Graf3D.h
 C Interface to the Macintosh Libraries


  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <5>	 7/30/91	JL		Updated Copyright.
		 <4>	 1/27/91	LN		Checked in Database generate file from DSG.
		 <3>	 11/7/90	JL		Changed all #defines to anonymous enums.

	To Do:
************************************************************/


#ifndef __GRAF3D__
#define __GRAF3D__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif


enum {

 radConst = 3754936
};

typedef Fixed XfMatrix[4][4];

struct Point3D {
 Fixed x;
 Fixed y;
 Fixed z;
};

typedef struct Point3D Point3D;

struct Point2D {
 Fixed x;
 Fixed y;
};

typedef struct Point2D Point2D;

struct Port3D {
 GrafPtr grPort;
 Rect viewRect;
 Fixed xLeft;
 Fixed yTop;
 Fixed xRight;
 Fixed yBottom;
 Point3D pen;
 Point3D penPrime;
 Point3D eye;
 Fixed hSize;
 Fixed vSize;
 Fixed hCenter;
 Fixed vCenter;
 Fixed xCotan;
 Fixed yCotan;
 char filler;
 char ident;
 XfMatrix xForm;
};

typedef struct Port3D Port3D;
typedef Port3D *Port3DPtr, **Port3DHandle;


#ifdef __cplusplus
extern "C" {
#endif
pascal void InitGrf3d(Port3DHandle port); 
pascal void Open3DPort(Port3DPtr port); 
pascal void SetPort3D(Port3DPtr port); 
pascal void GetPort3D(Port3DPtr *port); 
pascal void MoveTo2D(Fixed x,Fixed y); 
pascal void MoveTo3D(Fixed x,Fixed y,Fixed z); 
pascal void LineTo2D(Fixed x,Fixed y); 
pascal void Move2D(Fixed dx,Fixed dy); 
pascal void Move3D(Fixed dx,Fixed dy,Fixed dz); 
pascal void Line2D(Fixed dx,Fixed dy); 
pascal void Line3D(Fixed dx,Fixed dy,Fixed dz); 
pascal void ViewPort(const Rect *r); 
pascal void LookAt(Fixed left,Fixed top,Fixed right,Fixed bottom); 
pascal void ViewAngle(Fixed angle); 
pascal void Identity(void); 
pascal void Scale(Fixed xFactor,Fixed yFactor,Fixed zFactor); 
pascal void Translate(Fixed dx,Fixed dy,Fixed dz); 
pascal void Pitch(Fixed xAngle); 
pascal void Yaw(Fixed yAngle); 
pascal void Roll(Fixed zAngle); 
pascal void Skew(Fixed zAngle); 
pascal void Transform(const Point3D *src,Point3D *dst); 
pascal short Clip3D(const Point3D *src1,const Point3D *src2,Point *dst1,
 Point *dst2); 
pascal void SetPt3D(Point3D *pt3D,Fixed x,Fixed y,Fixed z); 
pascal void SetPt2D(Point2D *pt2D,Fixed x,Fixed y); 
pascal void LineTo3D(Fixed x,Fixed y,Fixed z); 
#ifdef __cplusplus
}
#endif

#endif
