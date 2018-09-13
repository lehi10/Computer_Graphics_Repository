#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;


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

    glFlush();
}


void display(void) 
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    drawTurtle(0.0,0.0);
    
    glColor3f(0.0,0.0,1.0) ;
    
    glutSwapBuffers();
}

void reshape(int width, int height) 
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void keyboard(unsigned char key, int x, int y) 
{
    switch (key) {

    case 'e':
        glRotatef(1.0,1.,0.,0.);
        break;
    case 'q':
        glRotatef(1.0,0.,1.,0.);
        break;    
    case 'w':
        glTranslatef(0.0, .5, 0);
        break;
    case 's':
        glTranslatef(0.0, -.5, 0);
        break;
    case 'a':
        glTranslatef(-.5, 0.0, 0);
        break;
    case 'd':
        glTranslatef(.5, 0.0, 0);
        break;

    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Turtle");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}