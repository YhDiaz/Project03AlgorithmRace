# Carreras de algoritmos 

## Descripción del proyecto

El presente proyecto corresponde al producto computacional de la unidad 3 del módulo Algoritmos y estructuras de datos. Como su nombre lo indica, el proyecto consiste en realizar una competencia de algoritmos de ordenamiento para medir el tiempo que tarda cada uno en ordenar un set de datos de ciertas características. Los algoritmos que se emplearon para realizar la carrera son:

* Selection sort 
* Bubble sort 
* Insertion sort 
* Shell sort (Utilizando la secuencia de Knuth) 
* Merge sort 
* Quick sort 
* Heap sort 

## Escenario general del proyecto 

En un contexto de desarrollo de videojuegos, se requiere el uso de algoritmos de ordenamiento en 3 áreas distintas:

* Tablero de puntaje de jugadores
* Determinación de la cantidad de caminos entre aldeas 
* Renderizado de objetos en un inventario 

Cada área representa una carrera en la que deberán competir los algoritmos. Cada carrera tiene un rango diferente correspondiente a la cantidad posible de datos que se requieren ordenar.

Adicionalmente, cada carrera tiene 4 modos de ordenamiento:

* Modo ordenado: El set de datos está ordenado de la forma requerida
* Modo inversamente ordenado: El set de datos está ordenado de forma inversa a la requerida 
* Modo aleatorio con valores únicos: El set de datos tiene datos distribuidos de manera aleatoria y ningún dato se repite 
* Modo aleatorio con valores duplicados: El set de datos tiene datos distribuidos de manera aleatoria y tiene datos repetidos 

Cada modo representa los 4 escenarios posibles de sets de datos que los algoritmos deben ordenar. En este punto cobra sentido la lógica que hay detrás de cada algoritmo, ya que el planteamiento de la condición en la que se comparan los elementos es un factor fundamental en el tiempo que tarda el algoritmo en ordenar un set de datos.

## Características implementadas

Dentro de las características implementadas en el programa se encuentran:

1. Elección, por parte del usuario, del modo en el que se ordenan los elementos de un set (ascendente o descendente).
2. Lectura del archivo que contiene los rangos de la cantidad de datos que habrá en cada carrera.
3. Selección aleatoria de un valor dentro de cada rango, el cual será utilizado para determinar la cantidad de elementos que tendrán los sets de una carrera.
4. Generación de los sets de datos para cada carrera: set de datos ordenado, set de datos inversamente ordenado, set de datos aleatorios con valores únicos y set de datos aleatorios con valores duplicados. Los sets de datos ordenado e inversamente ordenado dependerán de la elección inicial del usuario.
5. Desarrollo de los 7 algoritmos mencionados en la descripción del proyecto. Cada algoritmo puede ordenar los datos de forma ascendente o descendente según sea el caso.
6. Implementación de las 3 carreras y los 4 modos por carrera.
7. Cálculo del tiempo que tarda cada algoritmo en ordenar un set de datos.
8. Entrega de los resultados obtenidos por cada algoritmo (en el orden en que se ejecutaron) y obtención de el/los algoritmo/s ganador/es en cada modo de cada carrera.

Nota: Por motivos de mal funcionamiento, el algoritmo Quick sort tendrá un rango distinto al resto en las carreras 1 y 2, ya que ocurre un problema de desbordamiento al exceder un determinado límite de elementos en un set.
