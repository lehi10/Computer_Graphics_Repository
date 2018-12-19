/**
 *  LEHI QUINCHO MAMANI
 *  COMPUTACION GRAFICA
**/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

void putPixel(int x,int y)
{	
    glBegin(GL_POINTS);
    	glVertex2i(x,y);
	glEnd();
}


void drawLine(GLint x1, GLint y1,GLint x2,GLint y2)
{
    double dx,dy , incE , incNE,d,x,y;
    dx=x2-x1;
    dy=y2-y1;

    d=2*dy-dx;
    incE=2*dy;
    incNE=2*(dy-dx);

    x=x1;
    y=y1;

    putPixel(x,y);

    while(x < x2)
    {
        if(d<=0)
        {
            d+=incE;
            x++;
        }
        else
        {
            d+=incNE;
            x++;
            y++;
        }
        putPixel(x,y);
    }
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(0,0,100,100); 
    glFlush();
}




int main(int argc, char** argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(330,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Hello World :D");
	glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200,200,-200,200);

	glutDisplayFunc(displayMe);
	glutMainLoop();

    return 0;
}
