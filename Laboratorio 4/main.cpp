#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "camera.h"
#include "vector_tools.h"
#include <stdio.h>

static camera *LOCAL_MyCamera;
static int old_x, old_y;

using namespace std;
float pi2 = 6.28318530718;


void Zoom(int x, int y){
  float zoom;
  zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
  old_y = y;
  switch(LOCAL_MyCamera->camMovimiento){
    case CAM_EXAMINAR:
      if (LOCAL_MyCamera->camAperture + zoom > (5 * DEGREE_TO_RAD) &&
      LOCAL_MyCamera->camAperture + zoom < 175 * DEGREE_TO_RAD)
      LOCAL_MyCamera->camAperture=LOCAL_MyCamera->camAperture + zoom;
      break;
  }
  glutPostRedisplay();
}

void Andar(int x, int y){
  float rotacion_x, avance_y;
  avance_y = (float)(y - old_y) / 10;
  rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
  YawCamera( LOCAL_MyCamera, rotacion_x );
  AvanceFreeCamera( LOCAL_MyCamera, avance_y);
  old_y = y;
  old_x = x;
  glutPostRedisplay();
}

void Examinar(int x, int y){
  float rot_x, rot_y;
  rot_y = (float)(old_y - y);
  rot_x = (float)(x - old_x);
  Rotar_Latitud( LOCAL_MyCamera, rot_y * DEGREE_TO_RAD );
  Rotar_Longitud( LOCAL_MyCamera, rot_x * DEGREE_TO_RAD );
  old_y = y;
  old_x = x;
  glutPostRedisplay();
}

void Tripode(int x, int y)
{
	float rotacion_x, rotacion_y;
	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	rotacion_y = (float)(old_y - y) * DEGREE_TO_RAD / 5;
	YawCamera( LOCAL_MyCamera, rotacion_x );
	PitchCamera( LOCAL_MyCamera, rotacion_y );
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}


void Pan(int x, int y)
{
	float avance_x, avance_y;
	avance_x = (float)(old_x - x) / 10;
	avance_y = (float)(y - old_y) / 10;
	PanCamera( LOCAL_MyCamera, avance_x, avance_y);
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
  old_x = x;
  old_y = y;
  switch(button){
    case GLUT_LEFT_BUTTON:
      switch(LOCAL_MyCamera->camMovimiento)	{
		case CAM_TRIPODE:
			if (state == GLUT_DOWN) glutMotionFunc(Tripode);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;
		case CAM_PAN:
			if (state == GLUT_DOWN) glutMotionFunc(Pan);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;

        case CAM_EXAMINAR:
          if (state == GLUT_DOWN) glutMotionFunc(Zoom);
          if (state == GLUT_UP){
            glutPassiveMotionFunc(Examinar);
            glutMotionFunc(NULL);
      }
        break;
    case CAM_PASEAR:
      if (state == GLUT_DOWN) glutMotionFunc(Andar);
      if (state == GLUT_UP) glutMotionFunc(NULL);
      break;
    }
    break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) ;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}



void MouseMotion(int x, int y){
  old_y = y;
  old_x = x;
}






static void SpecialKey ( int key, int x, int y ){
  switch(key) {
    case GLUT_KEY_F1:
      glutPassiveMotionFunc(MouseMotion);
      LOCAL_MyCamera->camMovimiento = CAM_STOP;
      break;
    case GLUT_KEY_F2:
      glutPassiveMotionFunc(Examinar);
      LOCAL_MyCamera->camMovimiento = CAM_EXAMINAR;
      break;
    case GLUT_KEY_F3:
      glutPassiveMotionFunc(MouseMotion);
      LOCAL_MyCamera->camMovimiento = CAM_PASEAR;
      LOCAL_MyCamera->camAtY = 0;
      LOCAL_MyCamera->camViewY = 0;
      SetDependentParametersCamera( LOCAL_MyCamera );
      break;

	case GLUT_KEY_F4:
		if(LOCAL_MyCamera->camProjection == CAM_CONIC){
		LOCAL_MyCamera->x1=-3;
		LOCAL_MyCamera->x2=3;
		LOCAL_MyCamera->y1=-3;
		LOCAL_MyCamera->y2=3;
		LOCAL_MyCamera->z1=-5;
		LOCAL_MyCamera->z2=5;
		LOCAL_MyCamera->camProjection = CAM_PARALLEL;
		cout<<"Proyección  Ortogonal"<<endl;
		} else 
		{
			cout<<"Proyección  Perspectiva"<<endl;	
			LOCAL_MyCamera->camProjection = CAM_CONIC;
		}
		break;  
	case GLUT_KEY_F5:
		LOCAL_MyCamera->camMovimiento = CAM_TRIPODE;
		break;
	case GLUT_KEY_F6:
		LOCAL_MyCamera->camMovimiento = CAM_PAN;
		break;
    case GLUT_KEY_F7: //Reset Camera
      LOCAL_MyCamera->camAtX =0;
      LOCAL_MyCamera->camAtY =0;
      LOCAL_MyCamera->camAtZ =0;
      LOCAL_MyCamera->camViewX = 0;
      LOCAL_MyCamera->camViewY = 1;
      LOCAL_MyCamera->camViewZ = -3;
      SetDependentParametersCamera( LOCAL_MyCamera );
      break;
    }
  glutPostRedisplay();
}








void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  SetGLAspectRatioCamera( LOCAL_MyCamera );
}


void displayMe(void)
{
    SetGLCamera( LOCAL_MyCamera );

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();


    int num_vertices = 100;
    float radio = 0.8;
    float d_teta;
    d_teta = (pi2) / num_vertices;
    float teta = 0;

    float x2, y2,x1, y1;

    glutWireTeapot(1);
	
      glFlush();

}

int main(int argc, char** argv)
{
    LOCAL_MyCamera = CreatePositionCamera(5.0f, 0.0f, -10.0f);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);


    glutCreateWindow("Hello world!");
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(displayMe);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKey);
    glutPassiveMotionFunc(MouseMotion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}