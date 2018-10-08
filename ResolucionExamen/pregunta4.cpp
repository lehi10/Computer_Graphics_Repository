/**
 *  LEHI QUINCHO MAMANI
 *  COMPUTACION GRAFICA
**/

#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include <iostream>

using namespace std;

void putPixel(int x,int y)
{
    glBegin(GL_POINTS);            
        glVertex2d(x,y);
    glEnd();
}

void parabola(int xc, int yc, int p)
{
	int h=p/2;
	int x,y,d;
	int p2, p4;

	p2 = 2*p;
	p4 = 2*p2;
	x = 0;
	y = 0;
	d = 1 - p;

  	while(x < p && y<=h)
	{
		putPixel(xc+x,yc+y);
		putPixel(xc-x,yc+y);

		if(d >= 0)
		{
			y++;
			d = d - p2;
		}
		x++;
		d = d + 2*x +1;
	}


}




void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    parabola(0,0,200);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Algoritmo de la Parabola");
     gluOrtho2D(-200,200,-200,200);
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
