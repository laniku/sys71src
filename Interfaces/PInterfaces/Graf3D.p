
{
Created: Saturday, July 27, 1991 at 9:26 PM
 Graf3D.p
 Pascal Interface to the Macintosh Libraries

  Copyright Apple Computer, Inc. 1985-1991
  All rights reserved
    This file is used in these builds: Mac32 BigBang Sys606


	Change History (most recent first):

		 <3>	 7/30/91	JL		Updated Copyright.
		 <2>	 1/27/91	LN		Checked in Database generate file from DSG.

	To Do:
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
 UNIT Graf3D;
 INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingGraf3D}
{$SETC UsingGraf3D := 1}

{$I+}
{$SETC Graf3DIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := Graf3DIncludes}

CONST
radConst = 3754936;

TYPE
XfMatrix = ARRAY [0..3,0..3] OF Fixed;

Point3D = RECORD
 x: Fixed;
 y: Fixed;
 z: Fixed;
 END;

Point2D = RECORD
 x: Fixed;
 y: Fixed;
 END;

Port3DPtr = ^Port3D;
Port3DHandle = ^Port3DPtr;
Port3D = RECORD
 grPort: GrafPtr;
 viewRect: Rect;
 xLeft: Fixed;
 yTop: Fixed;
 xRight: Fixed;
 yBottom: Fixed;
 pen: Point3D;
 penPrime: Point3D;
 eye: Point3D;
 hSize: Fixed;
 vSize: Fixed;
 hCenter: Fixed;
 vCenter: Fixed;
 xCotan: Fixed;
 yCotan: Fixed;
 ident: BOOLEAN;
 xForm: XfMatrix;
 END;


PROCEDURE InitGrf3d(port: Port3DHandle);
PROCEDURE Open3DPort(port: Port3DPtr);
PROCEDURE SetPort3D(port: Port3DPtr);
PROCEDURE GetPort3D(VAR port: Port3DPtr);
PROCEDURE MoveTo2D(x: Fixed;y: Fixed);
PROCEDURE MoveTo3D(x: Fixed;y: Fixed;z: Fixed);
PROCEDURE LineTo2D(x: Fixed;y: Fixed);
PROCEDURE Move2D(dx: Fixed;dy: Fixed);
PROCEDURE Move3D(dx: Fixed;dy: Fixed;dz: Fixed);
PROCEDURE Line2D(dx: Fixed;dy: Fixed);
PROCEDURE Line3D(dx: Fixed;dy: Fixed;dz: Fixed);
PROCEDURE ViewPort(r: Rect);
PROCEDURE LookAt(left: Fixed;top: Fixed;right: Fixed;bottom: Fixed);
PROCEDURE ViewAngle(angle: Fixed);
PROCEDURE Identity;
PROCEDURE Scale(xFactor: Fixed;yFactor: Fixed;zFactor: Fixed);
PROCEDURE Translate(dx: Fixed;dy: Fixed;dz: Fixed);
PROCEDURE Pitch(xAngle: Fixed);
PROCEDURE Yaw(yAngle: Fixed);
PROCEDURE Roll(zAngle: Fixed);
PROCEDURE Skew(zAngle: Fixed);
PROCEDURE Transform(src: Point3D;VAR dst: Point3D);
FUNCTION Clip3D(src1: Point3D;src2: Point3D;VAR dst1: Point;VAR dst2: Point): INTEGER;
PROCEDURE SetPt3D(VAR pt3D: Point3D;x: Fixed;y: Fixed;z: Fixed);
PROCEDURE SetPt2D(VAR pt2D: Point2D;x: Fixed;y: Fixed);
PROCEDURE LineTo3D(x: Fixed;y: Fixed;z: Fixed);


{$ENDC} { UsingGraf3D }

{$IFC NOT UsingIncludes}
 END.
{$ENDC}

