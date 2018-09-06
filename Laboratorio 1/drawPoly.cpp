#include <GL/glut.h>
#include <math.h>
#include <cmath>

using namespace std;

void drawPoly(double radio,int numLados)
{

    double  temp_x=radio*cos(2*M_PI/numLados),
            temp_y=radio*sin(2*M_PI/numLados);

    for(int i =0; i <= numLados; i++)
    {
        double angulo = i*2*M_PI/numLados;
        double x = radio*cos(angulo);
        double y = radio*sin(angulo);

        glBegin(GL_LINES);            
            glVertex2d(x,y);
            glVertex2d(temp_x,temp_y);
        glEnd();
        temp_x=x;
        temp_y=y;
    }
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoly(0.5,100); // Esta función es la que se encarga de dibujar el poligono regular
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}