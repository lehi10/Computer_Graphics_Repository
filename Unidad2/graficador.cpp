#include <iostream>
#include<list>
#include<vector>
#include <string>
#include <stdlib.h>  
#include <GL/glut.h> 
#include <algorithm>
#include <map>
using namespace std;
using std::cerr;
using std::endl;

const int startwinsize = 400; 
int winw, winh;               
bool mouseleftdown = false;   
int mousex, mousey;
const int ESCKEY = 27;        
const double pointsize = 40;  
int numOfPoints=0;

int maxY=-100000;
int minY=1000000;

int maxX=-100000;
int minX=100000;

map<int,list<int>> edgeTable;


list<int *> figure;
bool NewFigureFLAG=false;



double **matRot=new double*[3];
double **matDesp=new double*[3];
int rotateFlag=false;
int centerPoint[2];


void putPixelColor(GLint x,GLint y,int color=2)
{	

	glColor3f (1,color,1); 
    glBegin(GL_POINTS);
    	glVertex2i(x,y);
	glEnd();
}



void putPixel(GLint x,GLint y)
{	

	glPointSize(3);
	glColor3f (1,1,1); 
    glBegin(GL_POINTS);
    	glVertex2i(x,y);
	glEnd();
}


void putPixel(GLint *array)
{	

	glPointSize(3);
	glColor3f (1,1,1); // X axis is red.
    glBegin(GL_POINTS);
    	glVertex2iv(array);
	glEnd();
}


void draw_Line(GLint *pointA,GLint *pointB)
{
	glLineWidth(1);
	glBegin (GL_LINES);
		glVertex2iv(pointA);
		glVertex2iv(pointB); 
	
	glEnd();
	glLineWidth(1);
}


void drawLine(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
	
		putPixel(x, y);
		
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			putPixel(x, y);

		}

	} else {
		putPixel(x, y);

		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			putPixel(x, y);
			
		}
	}
}


void addTableEdges(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
	
		edgeTable[y].push_back(x);
		//
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			edgeTable[y].push_back(x);
			//
		}

	} else {
		edgeTable[y].push_back(x);
		//
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) 
		{
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			edgeTable[y].push_back(x);
			//
		}
	}
}



int * mvmult(double **mat,int sizeMat ,int *&vec,int sizeVec)
{
	int *res=new int[sizeVec];
	for(int i=0;i<sizeVec;i++)
		res[i]=0;
	
	for(int i=0; i< sizeMat ;i++)
		for(int j=0;j< sizeMat ;j++)
		{

			res[i]+= mat[i][j]*vec[j];
		}					
	return res;
}


void drawAll()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	
	int *pointTemp=figure.back();
	for_each(figure.begin(),figure.end(),[&pointTemp](int *pointIt){
		draw_Line(pointTemp,pointIt);
		pointTemp=pointIt;

	});
	
	glFlush();
}


void rotate()
{
	
	matDesp[0][2]=(centerPoint[0]/numOfPoints)*-1;
	matDesp[1][2]=(centerPoint[1]/numOfPoints)*-1;


	
	for_each(figure.begin(),figure.end(),[](int *&pointIt){		
		int *temp =mvmult(matDesp,3,pointIt,3);
		pointIt[0]=temp[0];
		pointIt[1]=temp[1];

		
	});
	
	
	
	for_each(figure.begin(),figure.end(),[](int *&pointIt){		
		int *temp =mvmult(matRot,3,pointIt,3);
		pointIt[0]=temp[0];
		pointIt[1]=temp[1];

		
	});
	
	
	
	matDesp[0][2]=(centerPoint[0]/numOfPoints);
	matDesp[1][2]=(centerPoint[1]/numOfPoints);
	

	for_each(figure.begin(),figure.end(),[](int *&pointIt){		

		int *temp =mvmult(matDesp,3,pointIt,3);
		pointIt[0]=temp[0];
		pointIt[1]=temp[1];

		
	});
	
	drawAll();
		
}



void display()
{

	drawAll();	
   if (mouseleftdown)
   {
	int oglx = int(mousex)/winw;
	int ogly = winh-int(mousey)/winh;
	int *points=new int[3];
	points[0]=oglx;
	points[1]=ogly;
	points[2]=1;
	figure.push_back(points);
	
	
	
	maxY= ogly > maxY ? ogly : maxY;
	maxX= oglx > maxX ? oglx : maxX;
	
	minY= ogly < minY ? ogly : minY;
	minX= oglx < minX ? oglx : minX;
	
	
	centerPoint[0]+=points[0];
	centerPoint[1]+=points[1];
	numOfPoints++;	
	
	putPixel(points);
	glFlush();

   }

   glutSwapBuffers();
}


void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON)
   {
      mouseleftdown = (state == GLUT_DOWN);
      glutPostRedisplay(); 
   }
   mousex = x*400;
   mousey = y*400;
}


void LeftEdgeScan(int xmin, int ymin, int xmax,int ymax, int valor)
{

	int x=xmin;
	int y=ymin;

	int numerador=xmax-xmin; 
	int denominador=ymax-ymin;
	int incremento=denominador;

	for(y=ymin; y<=ymax; y++)
	{
		putPixelColor(x,y,valor);
		incremento+=numerador;
		
		if(incremento > denominador)
		{
			x++;
			incremento-=denominador;
		}
	}

}



void paint()
{

	int *pointTemp=figure.back();
	for_each(figure.begin(),figure.end(),[&pointTemp](int *pointIt){
		addTableEdges(pointTemp[0],pointTemp[1],pointIt[0],pointIt[1]);
		pointTemp=pointIt;
	});
	
	int pFlag=false;
	
	for(auto it=edgeTable.begin();it!=edgeTable.end();++it)
	{
		auto edge=it->second;

		int y=it->first;
		auto tempBegin=edge.begin();
		
		for(auto itEdge=edge.begin()++;itEdge!=edge.end();++itEdge)
		{
			for(int i=*tempBegin;i< *itEdge ; i++)
			{
				putPixel(i,y);
			}
			tempBegin=tempBegin++;;
		}
	}
	glFlush();
	
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case ESCKEY:  // ESC: Quit
      exit(0);
      break;
   case 'q':
   		break;
   case 'p':
		paint();
   		break;
   case 'd':
   		rotate();
   		break;
   case 'a':
   		break;
   }
}



void reshape(int w, int h)
{
   glViewport(0, 0, w, h);

   winw = w;
   winh = h;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
	gluOrtho2D(0,400,0,400);

   glMatrixMode(GL_MODELVIEW); 
}


void init()
{
   glClearColor(0.0, 0.0, .0, 0.0);
}


int main(int argc, char ** argv)
{
	for(int i=0;i<3;i++)
	{
		matRot[i] = new double[3];
		matDesp[i]= new double[3];
	}
	
	
	matRot[0][0]=0.5;		matRot[0][1]=-0.86;		matRot[0][2]=0;
	matRot[1][0]=0.86;		matRot[1][1]=0.5;	 	matRot[1][2]=0;
	matRot[2][0]=0;			matRot[2][1]=0;			matRot[2][2]=1;
	
	
	matDesp[0][0]=1.;	matDesp[0][1]=0.;	matDesp[0][2]=0.;	
	matDesp[1][0]=0.;	matDesp[1][1]=1.;	matDesp[1][2]=0.;	
	matDesp[2][0]=0.;	matDesp[2][1]=0.;	matDesp[2][2]=1.;	

	
	
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(330,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Hello World :D");
	glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,400,0,400);
    
   init();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);

   glutMainLoop();

   return 0;
}
