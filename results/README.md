#
### CI5437 - Inteligencia Artificial 1
##### Prof. Carlos Infante

# Proyecto 2

<div style='text-align: right;'>
Por <a href='https://www.github.com/chrischriscris'>Chus</a> | <a href='https://www.github.com/fungikami'>K</a>
</div>

## 1. Introducción

Una de las cuestiones fundacionales de la Inteligencia Artificial es la de construir agentes ~~inteligentes~~ capaces de tomar decisiones razonables en un entorno, ya que es esta una de las características que comunmente se asocian a la inteligencia humana. En este sentido, los juegos de tablero (y en particular, los juegos de dos jugadores con información perfecta) son un entorno de interés para la Inteligencia Artificial, ya que son entornos discretos, determinísticos y de suma cero, lo que los hace ideales para el estudio de algoritmos de búsqueda y de estrategias de juego. Lo que se busca con esto es que el agente implementado pueda escoger la mejor jugada en cada turno, y que sea así capaz de ganar, o al menos empatar la partida, contra un oponente humano o contra otro agente.

Por otro lado, Othello se trata de un juego de mesa en el que dos jugadores se enfrentan en un tablero de 8x8. El juego comienza con cuatro fichas colocadas en el centro del tablero, dos de cada color, en una disposición alternada, y el objetivo es tener más fichas de tu color que el oponente al final de la partida. Para ello, los jugadores colocan fichas de su color en el tablero, de tal forma que las fichas del oponente que se encuentren entre dos fichas del jugador, en una misma fila, columna o diagonal, se voltean y pasan a ser del jugador. El juego termina cuando ninguno de los jugadores puede colocar una ficha en el tablero, y el ganador es el jugador con más fichas de su color en el tablero.

Así, el objetivo de este proyecto es el de implementar un agente para una versión simplificada de Othello (con un tablero de 6x6), utilizando los algoritmos de árboles de juego Negamax (con y sin poda alpha-beta), Scout y Negascout, y evaluar su desempeño en la variación principal del juego.

## 2. Detalles de implementación

### 2.1. Representación del juego

### 2.2. Algoritmos de búsqueda

### 2.3. Evaluación de los algoritmos

## 3. Resultados experimentales

Para la ejecución de los algoritmos \<tal\>, se utilizaron computadores con las siguientes características:

| Procesador | RAM | Sistema Operativo |
|:----------:|:---:|:-----------------:|
| Intel i3-2120 (4) @ 3.300GHz | 3797MiB | Debian GNU/Linux 11 (bullseye) x86_64 |
| Intel i5-1035G1 (8) @ 3.600GHz | 7689MiB | Pop!_OS 22.04 LTS x86_64 |

Por otro lado, los algoritmos de búsqueda fueron implementados en C++, compilado con `g++ <version>` usando las flags `<flags>`.

## 4. Conclusiones
