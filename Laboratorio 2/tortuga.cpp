/**
 *  LEHI QUINCHO MAMANI
 *  COMPUTACION GRAFICA
*/
#include <GL/glut.h>
#include <math.h>
#include <cmath>

using namespace std;
double height= 480;
double width = 480;

double heightScreen= 480;
double widthScreen = 480;

void drawPoly(double c_x, double c_y,double radio,int numLados)
{

    double  temp_x=radio*cos(2*M_PI/numLados),
            temp_y=radio*sin(2*M_PI/numLados);

    for(int i =0; i <= numLados; i++)
    {
        double angulo = i*2*M_PI/numLados;

		widthScreen/2+radio*cos(angulo);
		heightScreen/2+radio*sin(angulo);
		
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

    drawPoly(x,y,50,lines);
    drawPoly(x,y,45,lines);
    drawPoly(x+50,y+40,20,lines);
    drawPoly(x-50,y+40,20,lines);
    drawPoly(x+40,y-50,20,lines);
    drawPoly(x-40,y-50,20,lines);
    drawPoly(x,y+60,20,lines);
    drawPoly(x-8,y+65,5,lines);
    drawPoly(x+8,y+65,5,lines);

    glFlush();
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawTurtle(300,300);
    glFlush();    
}

int myInit()    
{    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,widthScreen,0.0,heightScreen);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(widthScreen,heightScreen);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    glutDisplayFunc(displayMe);
    myInit();
    glutMainLoop();
    return 0;
}
