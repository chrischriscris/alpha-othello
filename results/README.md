#
### CI5437 - Inteligencia Artificial 1
##### Prof. Carlos Infante

# Proyecto 2

<div style='text-align: right;'>
Por <a href='https://www.github.com/chrischriscris'>Chus</a> | <a href='https://www.github.com/fungikami'>K</a>
</div>

## 1. Introducción

Una de las cuestiones fundacionales de la Inteligencia Artificial es la de construir agentes capaces de tomar decisiones razonables en un entorno, ya que es esta una de las características que comunmente se asocian a la inteligencia humana. En este sentido, los juegos de tablero (y en particular, los juegos de dos jugadores con información perfecta) son un entorno de interés para la Inteligencia Artificial, ya que son entornos discretos, determinísticos y de suma cero, lo que los hace ideales para el estudio de algoritmos de búsqueda y de estrategias de juego. Lo que se busca con esto es que el agente implementado pueda escoger la mejor jugada en cada turno, y que sea así capaz de ganar, o al menos empatar la partida, contra un oponente humano o contra otro agente.

Por otro lado, Othello se trata de un juego de mesa en el que dos jugadores se enfrentan en un tablero de 8x8. El juego comienza con cuatro fichas colocadas en el centro del tablero, dos de cada color, en una disposición alternada, y el objetivo es tener más fichas de tu color que el oponente al final de la partida. Para ello, los jugadores colocan fichas de su color en el tablero, de tal forma que las fichas del oponente que se encuentren entre dos fichas del jugador, en una misma fila, columna o diagonal, se voltean y pasan a ser del jugador. El juego termina cuando ninguno de los jugadores puede colocar una ficha en el tablero, y el ganador es el jugador con más fichas de su color en el tablero.

Así, el objetivo de este proyecto es el de implementar un agente para una versión simplificada de Othello (con un tablero de 6x6), utilizando los algoritmos de árboles de juego Negamax (con y sin poda alpha-beta), Scout y Negascout, y evaluar su desempeño en la variación principal del juego.

## 2. Detalles de implementación

### 2.1. Representación del juego

Para la versión simplificada de Othello, se representa el tablero con un número entero de 32 bits, en el que cada bit trata de una posición del tablero. Con ello se busca una mayor eficiencia en el uso de la memoria, ya que se utiliza un entero para representar el tablero de 36 piezas, en lugar de tomar un arreglo de 36 enteros o hasta un entero de 64 bits.

Para ello, se tiene un entero para representar las 4 piezas centrales del tablero y otro entero para indicar las piezas que han sido ocupadas por cada jugador, con 0 para las piezas blancas y 1 para las negras. Como también, se tiene en otro entero, la representación de las piezas que se encuentran libres, con 0 para las posiciones libres y 1 para las ocupadas. 

Así, se tienen distintas funciones para manipular el tablero, en la cual se emplean operaciones de bit a bit para manipular los enteros que representan el tablero. Estas funciones consisten en verificar si una posición está ocupada, colocar una ficha en una posición, voltear las fichas del oponente que se encuentren entre dos fichas del jugador, verificar si un jugador tiene movimientos válidos y obtener los movimientos válidos de un jugador, verificar si un estado es terminal e imprimir el tablero. Por ejemplo, para la función que verifica si una posición está ocupada dado un color, se realiza un enmascaramiento de la posición con el entero que representa las piezas ocupadas por el jugador, y se verifica si el resultado es distinto de 0. Para las funciones que verifican si han movimientos por 

Por otro lado, se completó las verificaciones sobre las diagonales en las funciones `outflank` y `move` del archivo `othello_cut.hpp`. Dichas verificaciones busca la posición en que se desea colocar la ficha, y verifica si hay fichas del oponente en las diagonales que se forman con las fichas del jugador en la misma fila y columna que la posición en cuestión. En caso de que esté seguimiento de fichas del oponente termine en una ficha del jugador, se considera que hay fichas del oponente que se voltearán al colocar la ficha en la posición en cuestión.

Se implementó la función `valid_moves` del archivo `othello_cut.hpp`, que devuelve un vector con las posiciones en las que el jugador puede colocar una ficha. En caso de que no haya movimientos válidos, se agrega el movimiento `36` al vector, que indica que el movimiento válido es pasar el turno. 

### 2.2. Algoritmos de búsqueda

Se implementó los algoritmos de búsqueda Negamax, Negamax con poda alpha-beta, Scout y Negascout en el archivo `main.cpp`. 

### 2.3. Evaluación de los algoritmos

## 3. Resultados experimentales

Para la ejecución de los algoritmos \<tal\>, se utilizaron computadores con las siguientes características:

| Procesador | RAM | Sistema Operativo |
|:----------:|:---:|:-----------------:|
| Intel i3-2120 (4) @ 3.300GHz | 3797MiB | Debian GNU/Linux 11 (bullseye) x86_64 |
| Intel i5-1035G1 (8) @ 3.600GHz | 7689MiB | Pop!_OS 22.04 LTS x86_64 |

Por otro lado, los algoritmos de búsqueda fueron implementados en C++, compilado con `g++ <version>` usando las flags `<flags>`.

## 4. Conclusiones
