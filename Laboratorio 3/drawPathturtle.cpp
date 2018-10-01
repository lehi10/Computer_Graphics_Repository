#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int np;
float px[10000];
float py[10000];
float pz[10000];

float trnsX=0.0;
float trnsY=0.0;
float trnsZ=0.0;

float rotaX=0.0;
float rotaY=0.0;
float rotaZ=0.0;



GLdouble mModel[16];

// Draw turtle --------------------------------------------------
void drawPoly(double c_x, double c_y,double radio,int numLados)
{

    double  temp_x=radio*cos(2*M_PI/numLados),
            temp_y=radio*sin(2*M_PI/numLados);

    for(int i =0; i <= numLados; i++)
    {
        double angulo = i*2*M_PI/numLados;

		
        double x = radio*cos(angulo);
        double y = radio*sin(angulo);

        glBegin(GL_LINES);            
            glVertex2d(x+c_x,y+c_y);
            glVertex2d(temp_x+c_x,temp_y+c_y);
        glEnd();
        temp_x=x;
        temp_y=y;
    }
}


void drawTurtle(int x,int y)
{
    glClear(GL_COLOR_BUFFER_BIT);

    int lines=10;

    drawPoly(x,y,.50,lines);
    drawPoly(x,y,.45,lines);
    drawPoly(x+.5,y+.40,.20,lines);
    drawPoly(x-.50,y+.40,.20,lines);
    drawPoly(x+.40,y-.50,.20,lines);
    drawPoly(x-.40,y-.50,.20,lines);
    drawPoly(x,y+.60,.20,lines);
    drawPoly(x-.08,y+.65,.05,lines);
    drawPoly(x+.08,y+.65,.05,lines);
  
  
    glLineWidth(5);
    glBegin (GL_LINES);
		glColor3f (1,0,0); // X axis is red.
		glVertex3f(0,0,0);
		glVertex3f(0.5,0,0 ); 
		
		glColor3f (0,1,0); // Y axis is green.
		glVertex3f(0,0,0);
		glVertex3f(0,0.5,0);
		
		glColor3f (0,0,1); // z axis is blue.
		glVertex3f(0,0,0);
		glVertex3f(0,0,0.5 ); 
	glEnd();
	glLineWidth(1);
  
    glFlush();
}



//Draw Trace------------------------------------

void displayTrace()
{
	int i;
	glColor3f(1.0,1.0,1.0) ;
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < np; i++) 
		glVertex3f(px[i],py[i],pz[i]);
	glEnd();
}


void addPointToTrace() {
	int i;
	GLdouble m[16];
	glGetDoublev (GL_MODELVIEW_MATRIX, m);

	if (np == 0) 
	{ 
		px [0] = 0.0;
		py [0] = 0.0;
		pz [0] = 0.0;
		np++;
	}
	
	px [np] = (m[0] * px [0] + m[4] * py [0] + m[8] * pz [0] + m[12])*0.5;
	py [np] = (m[1] * px [0] + m[5] * py [0] + m[9] * pz [0] + m[13])*0.5;
	pz [np] = (m[2] * px [0] + m[6] * py [0] + m[10] * pz [0] + m[14])*0.5;
	
	np++;
}



void display() 
{
    glClearColor(.0, .0, .0, 0.0);

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glRotatef( rotaX, 1.0, 0.0, 0.0 );
		glRotatef( rotaY, 0.0, 1.0, 0.0 );
		glRotatef( rotaZ, 0.0, 0.0, 1.0 );

		glTranslatef(trnsX, trnsY, trnsZ);		
		addPointToTrace();
		glMultMatrixd(mModel);
		glColor3f(1.0,0.0,0.0);
		drawTurtle(0.0,0.0);


	glPopMatrix();
	
	displayTrace(); 


    glutSwapBuffers();
}

void reshape(int width, int height) 
{

	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.6, 128.0);
    glMatrixMode(GL_MODELVIEW);

    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}


void keyboard(unsigned char key, int x, int y) 
{

    switch (key) {
    case 'q':
		rotaZ+=3;
    	break;
    case 'e':
	    rotaZ+=-3;
    	break;    
    case 'w':
		rotaX+=3;
        break;
    case 's':
    	rotaX+=-3;
        break;
    case 'a':
	    rotaY+=-3;
        break;
    case 'd':
	    rotaY+=3;
        break;
	case '-':
        glScalef(0.5,0.5,0.5);
        break;
    case '+':
	    glScalef(2,2,2);
	    break;


    case 27:
        exit(0);
        break;
    }
    
    glutPostRedisplay();
}


void catchKey(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)    
    {
		trnsX+= -.1;
    }
    
    else if(key == GLUT_KEY_RIGHT)
    {
		trnsX+= .1;
    }

    else if(key == GLUT_KEY_DOWN)
    {
		trnsY+= -.1;
	}
    else if(key == GLUT_KEY_UP)
    {
		trnsY+= .1;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB |  GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Turtle");
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(catchKey);
    glutDisplayFunc(display);
    
    glutReshapeFunc(reshape);


    glutMainLoop();
    return 0;
}
