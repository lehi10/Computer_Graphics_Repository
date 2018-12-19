/**
 *  LEHI QUINCHO MAMANI
 *  COMPUTACION GRAFICA
**/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <tuple>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

GLdouble mModel[16];
float rotaX=0.0;
float rotaY=0.0;
float rotaZ=0.0;

double *A=new double[4];
double *B=new double[4];
double *C=new double[4];

double **matTransf=new double*[4];
double **matDesp=new double*[4];



double * mvmult(double **mat,int sizeMat ,double *vec,int sizeVec)
{
	double *res=new double[sizeVec];
	
	for(int i=0; i< sizeMat ;i++)
		for(int j=0;j< sizeMat ;j++)
			res[i]+= mat[i][j]*vec[j];
			

			
	return res;
}


void putPixel(double *array)
{	

	glPointSize(3);
	glColor3f (1,1,1); // X axis is red.
    glBegin(GL_POINTS);
    	glVertex3dv(array);
	glEnd();
}


void axis(void)
{
	glLineWidth(1);
	glBegin (GL_LINES);
		glColor3f (1,0,0); // X axis is red.
		glVertex3f(-10,0,0);
		glVertex3f(10,0,0 ); 
	
		glColor3f (0,1,0); // Y axis is green.
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
	
		glColor3f (0,0,1); // z axis is blue.
		glVertex3f(0,0,-10);
		glVertex3f(0,0,10 ); 
	glEnd();
	glLineWidth(1);
}


void figure(double *_A,double *_B, double *_C,int color)
{
	glLineWidth(1);
	glColor3f (5,color,1); // X axis is red.
	glBegin (GL_LINES);
		glVertex3dv(_A);
		glVertex3dv(_B); 
	
		glVertex3dv(_B);
		glVertex3dv(_C);
	glEnd();
	
	putPixel(_A);
	putPixel(_B);
 	putPixel(_C);
}


void displayMe(void)
{
	glPushMatrix();
		glRotatef( rotaX, 1.0, 0.0, 0.0 );
		glRotatef( rotaY, 0.0, 1.0, 0.0 );
		glRotatef( rotaZ, 0.0, 0.0, 1.0 );


		glClear(GL_COLOR_BUFFER_BIT);
	 	axis();
	 	
	 	//Graficamos los puntos A,B y C originales
		figure(A,B,C,5);
	
		//Movemos los puntos al origen, para eso multiplicamos los puntos por la matriz de traslación
		double *despA = mvmult(matDesp,4,A,4);
		double *despB = mvmult(matDesp,4,B,4);
		double *despC = mvmult(matDesp,4,C,4);
	
		//Hacemos las rotaciones multiplicando a nuestros puntos con la mtriz obtenida a partir de los vectores unitarios
		double *tranA = mvmult(matTransf,4,despA,4);
		double *tranB = mvmult(matTransf,4,despB,4);
		double *tranC =	mvmult(matTransf,4,despC,4);
	
		//Graficamos los nuevos puntos A' B' C'
		figure( tranA,tranB,tranC,0);

    glPopMatrix();	
    glFlush();
    
}

void reshape(int width, int height) 
{
    
	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.6, 128.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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


int main(int argc, char** argv)
{
	// Puntos iniciales
	A[0]=-1.;	A[1]=2.;	A[2]=3.;	A[3]=1.;
	B[0]=1.;	B[1]=1.; 	B[2]=1.;	B[3]=1.;
	C[0]=3.;	C[1]=2.;	C[2]=1.;	C[3]=1.;
	
	for(int i=0;i<4;i++)
	{
		matTransf[i] = new double[4];
		matDesp[i] = new double[4];
	}
	
	//Matriz de transformación
	matTransf[0][0]=-2./3.;	matTransf[0][1]=1./3.;	matTransf[0][2]=2./3.;	matTransf[0][3]=0.;
	matTransf[1][0]=2./3.;	matTransf[1][1]=2./3.; 	matTransf[1][2]=1./3.;	matTransf[1][3]=0.;
	matTransf[2][0]=-1./3.;	matTransf[2][1]=2./3.;	matTransf[2][2]=-2./3.;	matTransf[2][3]=0.;
	matTransf[3][0]=0.;		matTransf[3][1]=0.;		matTransf[3][2]=0.;		matTransf[3][3]=1.;

	//Matriz de desplazamiento o traslación
	matDesp[0][0]=1.;	matDesp[0][1]=0.;	matDesp[0][2]=0.;	matDesp[0][3]=-1.;
	matDesp[1][0]=0.;	matDesp[1][1]=1.;	matDesp[1][2]=0.;	matDesp[1][3]=-1.;
	matDesp[2][0]=0.;	matDesp[2][1]=0.;	matDesp[2][2]=1.;	matDesp[2][3]=-1.;
	matDesp[3][0]=0.;	matDesp[3][1]=0.;	matDesp[3][2]=0.;	matDesp[3][3]=1.;


    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	
	
	glutInitWindowPosition(330,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Pregunta 2");
	glMatrixMode(GL_PROJECTION);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMe);
	glutReshapeFunc(reshape);
	glutMainLoop();

    return 0;
}
