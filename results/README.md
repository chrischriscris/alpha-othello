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

Para la versión simplificada de Othello, la representación usada consiste en dos mapa de bits guardados en enteros de 32 bits, en el que cada bit codifica una posición del tablero. Con ello se busca una mayor eficiencia en el uso de la memoria, ya que se utiliza un solo entero de 32 bits para representar el tablero de 36 piezas, aprovechando la forma del problema para guardar las 4 fichas fijas del centro en un entero de 8 bits y desperdiciar solo 4 bits, en lugar de tomar otras estructuras como un arreglo de 36 booleanos o un entero de 64 bits.

Más detalladamente, un estado consiste en 3 campos:

- Un entero de 32 bits, en el que el i-ésimo bit representa la posición i del tablero, exceptuando las 4 centrales, con 0 para las posiciones libres y 1 para las ocupadas.
- Un entero de 32 bits, en el que el i-ésimo bit representa la posición i del tablero, exceptuando las 4 centrales, con 0 para las posiciones ocupadas por las fichas blancas y 1 para las ocupadas por las fichas negras. En caso de que una posición esté libre, el bit correspondiente es 0 por defecto, por lo que se ha de consultar el primer entero para verificar si la posición está libre o no.
- Un entero de 8 bits en el que los 4 bits menos significativos representan las 4 posiciones centrales del tablero, siendo 0 para las posiciones ocupadas por las fichas blancas y 1 para las ocupadas por las fichas negras. Al nunca estar libres, no se necesita otro entero para representar si están ocupadas o no.

Así, se tienen distintos métodos para manipular un estado, en los cuales se emplean operaciones bit a bit para manipular los enteros que lo representan.Estos métodos incluyen:

- Hashing de un estado, para poder almacenar los estados visitados en una tabla de transposición.
- Verificaciones varias: si una posición está ocupada por determinado color, si está libre, si un jugador tiene movimientos válidos, si un estado es terminal, etcétera.
- Modificación del estado colocando una ficha en una posición y volteando consecuentemente las fichas del oponente que se encuentren entre dos fichas del jugador.
- Obtención de los movimientos válidos de un jugador
- Obtención un movimiento válido aleatorio.
- Impresión del estado, tanto en su representación en bits como de una forma legible.

Por ejemplo, para la función que verifica si una posición está ocupada dado un color, se realiza un enmascaramiento de la posición con el entero que representa las piezas ocupadas por el jugador, y se verifica si el resultado es distinto de 0.

Por otro lado, se completaron las verificaciones sobre las diagonales en las funciones `outflank` y `move` del archivo `othello_cut.hpp`. Dichas verificaciones buscan la posición en que se desea colocar la ficha, y verifican si hay fichas del oponente en las diagonales que se forman con las fichas del jugador en la misma fila y columna que la posición en cuestión. En caso de que este seguimiento de fichas del oponente termine en una ficha del jugador, se considera que hay fichas del oponente que se voltearán al colocar la ficha en la posición en cuestión.

Como detalle de implementación, se modificó la función `valid_moves` del archivo `othello_cut.hpp`, que originalmente retornaba un vector con las posiciones en las que el jugador puede colocar una ficha, estando este vacío si no habían movimientos válidos. La modificación consistió en retornar un vector con el elemento `36`, que representar el movimiento de ceder el turno.

### 2.2. Algoritmos de búsqueda

Se implementó los algoritmos de búsqueda Negamax, Negamax con poda alpha-beta, Scout y Negascout en el archivo `main.cpp`.

### 2.3. Evaluación de los algoritmos

## 3. Resultados experimentales

Para la ejecución de los algoritmos \<tal\>, se utilizaron computadores con las siguientes características:

|           Procesador           |   RAM   |           Sistema Operativo           |
| :----------------------------: | :-----: | :-----------------------------------: |
|  Intel i3-2120 (4) @ 3.300GHz  | 3797MiB | Debian GNU/Linux 11 (bullseye) x86_64 |
| Intel i5-1035G1 (8) @ 3.600GHz | 7689MiB |       Pop!_OS 22.04 LTS x86_64        |

Por otro lado, los algoritmos de búsqueda fueron implementados en C++, compilado con `g++ <version>` usando las flags `<flags>`.

## 4. Conclusiones
