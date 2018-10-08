/**
 *  LEHI QUINCHO MAMANI
 *  COMPUTACION GRAFICA
**/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

GLdouble mModel[16];
float rotaX=0.0;
float rotaY=0.0;
float rotaZ=0.0;

void putPixel(int x,int y,int z)
{	
	glPointSize(1);
    glBegin(GL_POINTS);
    	glVertex3i(x,y,z);
	glEnd();
}


int maximum(int x, int y, int z) {
	int max = x; 
	if (y > max) 
		max = y;
	if (z > max)
		max = z;
	return max; 
} 

void drawLine(GLint x1, GLint y1, GLint z1, GLint x2,GLint y2, GLint z2)
{
    int dx,dy ,dz, x,y,z;
    int err_1,err_2,err_3;
    int incX,incY,incZ;

	x=x1;
	y=y1;
	z=z1;

    dx=x2-x1;    
    dy=y2-y1;
    dz=z2-z1;
    
    incX = 1;    
    incY = 1;
    incZ = 1;
       
	if(maximum(dx,dy,dz)==dx) 
	{
		    err_1 = 2*dy - dx;
		    err_2 = 2*dz - dx;
		    for (int i = 0; i < dx; i++) {

		        if (err_1 > 0) {
		            y += incY;
		            err_1 -= 2*dx;
		        }
		        if (err_2 > 0) {
		            z += incZ;
		            err_2 -= 2*dx;
		        }
		        err_1 += 2*dy;
		        err_2 += 2*dz;
		        x+= incX;
		        		    putPixel(x,y,z);
		    }
	} 
	
	else if (maximum(dx,dy,dz)==dy) 
	{
		err_1 = 2*dx - dy;
		err_2 = 2*dz - dy;
		for (int i = 0; i < dy; i++) {

		    if (err_1 > 0) {
		        x += incX;
		        err_1 -= 2*dy;
		    }
		    if (err_2 > 0) {
		        z += incZ;
		        err_2 -= 2*dy;
		    }
		    err_1 += 2*dx;
		    err_2 += 2*dz;
		    y += incY;
		    		    putPixel(x,y,z);
		}
	} 
	else 
	{
		err_1 = 2*dy - dz;
		err_2 = 2*dx - dz;
		for (int i = 0; i < dz; i++) {

		    if (err_1 > 0) {
		        y += incY;
		        err_1 -= 2*dz;
		    }
		    if (err_2 > 0) {
		        x += incX;
		        err_2 -= 2*dz;
		    }
		    err_1 += 2*dy;
		    err_2 += 2*dx;
		    z += incZ;
		    		    putPixel(x,y,z);
		}
	}
		
    
	glBegin (GL_LINES);
		glVertex3f(0,0,z2);
		glVertex3f(x2,0,z2 ); 
	
		glVertex3f(x2,0,0);
		glVertex3f(x2,0,z2);
		
		glVertex3f(x2,0,z2);
		glVertex3f(x2,y2,z2);
	glEnd();
	glLineWidth(1);
}


void axis(void)
{
	glLineWidth(1);
	glBegin (GL_LINES);
		glColor3f (1,0,0); // X axis is red.
		glVertex3f(-300,0,0);
		glVertex3f(300,0,0 ); 
	
		glColor3f (0,1,0); // Y axis is green.
		glVertex3f(0,0,0);
		glVertex3f(0,300,0);
	
		glColor3f (0,0,1); // z axis is blue.
		glVertex3f(0,0,-300);
		glVertex3f(0,0,300 ); 
	glEnd();
	glColor3f (1,1,1); // X axis is red.
	glLineWidth(1);
}

void displayMe(void)
{
	glPushMatrix();
		glRotatef( rotaX, 1.0, 0.0, 0.0 );
		glRotatef( rotaY, 0.0, 1.0, 0.0 );
		glRotatef( rotaZ, 0.0, 0.0, 1.0 );

		glClear(GL_COLOR_BUFFER_BIT);
		drawLine(0,0,0,20,20,15); 
		axis();
    glPopMatrix();
    
    glFlush();
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


void reshape(int width, int height) 
{
    
	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
    glLoadIdentity();
    gluPerspective(20.0, (GLfloat)height / (GLfloat)width, 1.6, 128.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(25.0, 50.0, 100.0, 10, 10.0, 10.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(330,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Linea 3D");
	glMatrixMode(GL_PROJECTION);


    glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMe);
	glutReshapeFunc(reshape);
	glutMainLoop();

    return 0;
}

