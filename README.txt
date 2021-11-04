# SO_T2
Pablo Contreras 201973572-1  P200
Nicolás Moraga 201973562-4   P201

Instrucciones de ejecución:
    Por medio de 'make' en la linea de comandos en el directorio raiz.
    Se pueden limpiar los archivos con 'make clean'.

El directorio "casilla" posee la super clase y sub clases de casilla, que se componen de:

    Casilla:
        - MoneyCasilla
        - JailCasilla
        - MoveCasilla

El directorio "jugador" contiene la clase Jugador, que representará a los distintos jugadores.

El directorio "tablero" contiene la clase Tablero, que corresponde al tablero de juego.

Cada directorio, excepto el main, está compuesto de un archivo hpp y uno cpp, con la estructura

    ${nombre_de_la_clase}.cpp
    ${nombre_de_la_clase}.hpp

El archivo 'main.cpp' ejecuta la mayoría del código. Aquí se incializa el tablero con sus distintos valores de casillas,
además de inicializarse los jugadores, los fork() de los subprocesos y se encarga de matar los hijos al finalizar la ejecuciónd e uno
de ellos y declarar un ganador.