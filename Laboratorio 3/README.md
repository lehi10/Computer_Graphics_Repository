
# Laboratorio 3

Lehi Quincho M.

Compilar con:
```
g++ drawPathturtle.cpp -o main -lGL -lGLU -lglut

```

## Turtuga hecha con la función de poligonos regulares
Usando la función de poligonos regulares se dibujó la tortuga.

## Interaccion con la tortuga
A diferencia del ejercicio anterior, cada vez que realizamos algún movimiento con la tortuga, capturamos la matriz GL_MODELVIEW_MATRIX y obtenemos las coordenadas del objeto despues de hacer una accion que puede ser glTranslatef(...) o glRotatef(...). Usando 	glPushMatrix(), y glPopMatrix() las transformaciones realizadas entre la tortuga  no afectan al resto de la aplicación (el camino trazado). 


![Image of Turtle](https://github.com/lehi10/Computaci-n-Grafica/blob/master/Laboratorio%203/img/turtle.png)




