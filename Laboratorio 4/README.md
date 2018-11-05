# Laboratorio 4	

Lehi Quincho M.

Compilar con:
```
g++ main.cpp camera.cpp -o main vector_tools.cpp -lglut -lGL -lGLU

```

## Dotar al programa de una tecla que permita cambiar el modo de proyección entre ORTOGONAL y PERSPECTIVA.

En la función special Keys para cambiar de ortogonal a Perspectiva:

```
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
```

![Image ortho view ](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/ortho1.png)

![Image ortho view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/ortho2.png)


![Image perspective view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/perspec1.png)

![Image perspective view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/perspec2.png)


## Programar otros modos de movimiento de cámara como son el MODO PAN o el MODO TRÍPODE.

### MODO PAN


Cambiará la posición de la camara llamando a PanCamera en camera.h
```
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
```

Se declara en camera.h e implementa en camera.cpp
Cambiará la posición de la camara
```
void PanCamera( camera *thisCamera, float stepX, float stepY )
{
    float vaX, vaY, vaZ;
    vaX= stepX * thisCamera->camIX + stepY * thisCamera->camJX;
    vaY= stepX * thisCamera->camIY + stepY * thisCamera->camJY;
    vaZ= stepX * thisCamera->camIZ + stepY * thisCamera->camJZ;
    // Set V & A
    thisCamera->camViewX = thisCamera->camViewX + vaX;
    thisCamera->camViewY = thisCamera->camViewY + vaY;
    thisCamera->camViewZ = thisCamera->camViewZ + vaZ;
    thisCamera->camAtX = thisCamera->camAtX + vaX;
    thisCamera->camAtY = thisCamera->camAtY + vaY;
    thisCamera->camAtZ = thisCamera->camAtZ + vaZ;
    SetDependentParametersCamera( thisCamera );
}
```

Se agrega al switch de la funcion mouse

```
case CAM_PAN:
	if (state == GLUT_DOWN) glutMotionFunc(Pan);
	if (state == GLUT_UP) glutMotionFunc(NULL);
	break;
```
Se le asigna una tecla para activar el modo PAN
```
	case GLUT_KEY_F6:
		LOCAL_MyCamera->camMovimiento = CAM_PAN;
		break;
```		
		
![Image pan mode](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/pan.png)


### MODO TRIPODE 

cambiará el angulo llamando a PitchCamera de camera.h
```		
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
```	
Se declara en camera.h e implementa en camera.cpp
Cambiará el angulo de la camara	
```		
void PitchCamera( camera *thisCamera, float angle )
{
    float vIn[3];
    vIn[0]= thisCamera->camAtX - thisCamera->camViewX;
    vIn[1]= thisCamera->camAtY - thisCamera->camViewY;
    vIn[2]= thisCamera->camAtZ - thisCamera->camViewZ;
    VectorRotXZ( vIn, angle, TRUE );
    thisCamera->camAtX = thisCamera->camViewX + vIn[0];
    thisCamera->camAtY = thisCamera->camViewY + vIn[1];
    thisCamera->camAtZ = thisCamera->camViewZ + vIn[2];
    SetDependentParametersCamera( thisCamera );
}
```		

```		
case GLUT_KEY_F5:
		LOCAL_MyCamera->camMovimiento = CAM_TRIPODE;
		break;
```		

![Image tripode mode](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/tripode.png)

