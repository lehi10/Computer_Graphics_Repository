
# Ejercicios del Examen 

Lehi Quincho Mamani

Compilar con:
```
g++ -std=c++11 pregunta2.cpp -o main -lGL -lGLU -lglut
g++ -std=c++11 pregunta3.cpp -o main -lGL -lGLU -lglut
g++ -std=c++11 pregunta4.cpp -o main -lGL -lGLU -lglut

```
para las preguntas 2, 3 y 4 respectivamente.



# Usando las propiedades de Vectores ortogonales, transformar los siguientes puntos , C en el plano XY, y A en el eje X

Se hallan los vectores unitarios ortogonales para cada eje (X,Y y Z).
```
rx= (-2/3,	1/3,	2/3)
ry= (2/3,	2/3,	1/3)
rz= (-1/3,	2/3,	-2/3)
```
Estos vectores se obtuvijeron de:
### rx
El vector unitario de BC y representará nuestro eje X.

### rz
El vector unitario del producto cruz de los vectores unitarios de AB y CB
Este producto cruz nos da como resultado un vector ortogonal a AB y CB y representará nuestro eje Z. 

 
### ry
El vector unitario del producto de rx y rz.
Este vector es ortogonal a los anteriores y representará nuestro eje Y.


con los nuevos vectores unitarios rx, ry y rz, construirémos nuestra matriz de transformación.
```
[[-2/3	1/3		2/3		0],
[2/3	2/3		1/3		0],
[-1/3	2/3		-2/3	0],
[0		0		0		1]]
```
## Mover y transformar los puntos
Para tener nuestros puntos finales en los lugares deseados, primero necesitamos mover los puntos A, B y C al origen, y luego aplicar la matriz de transformación. Para esto se multiplica la matriz de traslación o desplazamiento con los valoes t1, t2 y t3 iguales a -1, esto debido a que el punto B tiene las coordenadas (1,1,1).
```
[[1,	0		0		-1],
[0		1		0		-1],
[0		0		1		-1],
[0		0		0		1]]
```
Luego de aplicar nuestra matriz de traslación por medio de una multiplicación de matrices a cada uno de nuestros puntos A, B y C, multiplicamos nuestros puntos resultantes por la matriz de transformación que hallamos a partir de los vectores ortogonales unitarios.

El resultado en OpenGL es el siguiente. 
En la imagen:
Los puntos unidos con los segmentos blancos son los puntos originales A, B y C.
Los puntos unidos con los segmentos rosados son los puntos transformados A', B' y C'.


![Transformación](https://github.com/lehi10/Computaci-n-Grafica/blob/master/ResolucionExamen/imgs/pregunta2.png)







