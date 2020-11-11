#include <windows.h>
#include <glut.h>


GLfloat LightAmbient[]= { 0.3f, 0.3f, 0.3f, 1.0f }; 
GLfloat LightDiffuse[]= { 1.0f, 1.0f,1.0f, 1.0f };
GLfloat LightSpec[]= { 1.0f, 1.0f,1.0f, 1.0f };
GLfloat LightPosition[]= { 0, 5.0f, 0, 1.0f };	

GLfloat LightAmbient2[]= { 0.1f, 0.1f, 0.1f, 1.0f }; 
GLfloat LightDiffuse2[]= { 1.0f, 0,0, 1.0f };
GLfloat LightPosition2[]= { -5.0f, 0.0f, -1.0f, 1.0f };

GLsizei winWidth=600,winHeight=500;


void gfxInit()
{


	
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("Cmpe 160"); 

	glShadeModel(GL_FLAT);						// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			// Black Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);	
    	glLightfv(GL_LIGHT0, GL_SPECULAR,LightSpec);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient2);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse2);	
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition2);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);	
	glEnable(GL_LIGHT1);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(20.0,20.0,20.0,0.0,0,0.0,0.0,1.0,0.0); 
    glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, 1.5, 1.0, 100.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	
      
}

void gfxClear()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gfxFlush()
{
	 glFlush();
}