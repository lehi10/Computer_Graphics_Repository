# Laboratorio 4	

Lehi Quincho M.

Compilar con:
```
g++ main.cpp camera.cpp -o main vector_tools.cpp -lglut -lGL -lGLU

```

## Dotar al programa de una tecla que permita cambiar el modo de proyección entre ORTOGONAL y PERSPECTIVA.

```

```

![Image ortho view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/ortho1.png | width=70)

![Image ortho view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/ortho2.png)


![Image perspective view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/perspec1.png)

![Image perspective view](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/perspec2.png)

## Programar otros modos de movimiento de cámara como son el MODO PAN o el MODO TRÍPODE.

### MODO PAN

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


```
case CAM_PAN:
	if (state == GLUT_DOWN) glutMotionFunc(Pan);
	if (state == GLUT_UP) glutMotionFunc(NULL);
	break;
```

![Image pan mode](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/pan.png)


### MODO TRIPODE 

![Image tripode mode](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%204/img/tripode.png)

