#include <windows.h>
#include <glut.h>
#include "Geometry3D.h"
#include "Scene3D.h"

extern void gfxInit();
extern void gfxClear();
extern void gfxFlush();


Geometry3D cubeCmpe("GeometryDef.txt","cube1");
Geometry3D cylinderCmpe("GeometryDef.txt","cylinder1");
Scene3D classroom;


Vector3D tableTopPosition(-3.0, 7.0, 0.0);
Vector3D tableTopSize(7.0, 1.0, 7.0);

Vector3D tableLegSize(0.2, 7.0, 0.2);

Vector3D tableLeg1Position(0,3,-3);
Vector3D tableLeg2Position(0,3,3);
Vector3D tableLeg3Position(-6,3,3);
Vector3D tableLeg4Position(-6,3,-3);

Vector3D floorSize(30.0,1.0,30.0);

Vector3D cylinderPosition(10.0, 4.0, 8.0);
Vector3D cylinderSize(0.2, 0.2, 0.2);


void drawScene()

{
	gfxClear();

		GfxObject3D& tableLeg1 = classroom += (cubeCmpe);
		(tableLeg1 *= tableLegSize ) += tableLeg1Position;

		
		GfxObject3D& tableLeg2 = classroom += (cubeCmpe);
		(tableLeg2 *= tableLegSize ) += tableLeg2Position;

		
		GfxObject3D& tableLeg3 = classroom += (cubeCmpe);
		(tableLeg3 *= tableLegSize ) += tableLeg3Position;

		
		GfxObject3D& tableLeg4 = classroom += (cubeCmpe);
		(tableLeg4 *= tableLegSize ) += tableLeg4Position;


		GfxObject3D& tableTop = classroom += (cubeCmpe);
		(tableTop *= tableTopSize) += tableTopPosition;

		GfxObject3D& floor = classroom += (cubeCmpe);
		floor *= floorSize;

		
		GfxObject3D& cylinder = classroom += (cylinderCmpe);
		(cylinder *= cylinderSize ) += cylinderPosition;


		//classroom -= tableLeg1;
		//classroom -= floor;
		classroom.draw();

	gfxFlush();
}



void main(int argc, char **argv)
{

	glutInit(&argc,argv);
    gfxInit();
	glutDisplayFunc(drawScene);    //drawScene is called for display events
    glutMainLoop();

}


