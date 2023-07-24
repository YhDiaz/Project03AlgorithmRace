# Carreras de algoritmos 

## Compilación del proyecto

El software debe ser compilado, de preferencia, en el IDE Dev-C++. En caso de algún problema con el compilador, intente realizar la siguiente operación:

-   Abrir el IDE Dev-C++
-   Seleccionar Tools/Herramientas en la barra superior
-   Seleccionar Compiler options.../Opciones de compilador...
-   Seleccionar la pestaña General
-   Marcar la casilla Add the following commands when calling the compiler/Agregue los siguientes comandos al llamar al compilador
-   En el cuadro de texto de la casilla escriba: -std=c++11
-   Seleccione OK e intente ejecutar nuevamente el programa

Dado que el programa fue desarrollado en un equipo con sistema operativo Windows, se recomienda compilarlo en un equipo con el mismo sistema operativo para evitar problemas.

Sobre el archivo de lectura:

* Debe estar en formato .txt
* Debe tener valores en el siguiente orden y formato: RangoMinimo,RangoMaximo
* Note que los datos están separados por una coma y sin espacios entre ellos. En caso de que exista un espacio, el programa podría no funcionar correctamente
* No se deben modificar los encabezados, ya que internamente se omite esa línea
* Las líneas debajo de los encabezados corresponden a las carreras, siendo la línea 1 (sin contar los encabezados) correspondiente a los rangos de la carrera 1, la línea 2 correspondiente a los rangos de la carrera 2 y de igual manera con la línea 3
* Los valores de los rangos deben ser ingresados coherentemente con lo que representa su orden, esto es, no ingresar un número mayor al del rango máximo como rango mínimo
* No se deben agregar más líneas, ya que el programa está diseñado para realizar 3 carreras
* Se pueden modificar los valores de los rangos siempre y cuando se tomen en consideración todas los puntos anteriores
