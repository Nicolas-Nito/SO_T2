CC = g++
CFLAGS = -g -Wall

OBJS =casilla.o jailCasilla.o moneyCasilla.o moveCasilla.o jugador.o tablero.o main.o

all: main

main: $(OBJS)
	$(CC) $(OBJS) -o main 

main.o: casilla/casilla.hpp tablero/tablero.hpp jugador/jugador.hpp casilla/jailCasilla/jailCasilla.hpp casilla/moneyCasilla/moneyCasilla.hpp casilla/moveCasilla/moveCasilla.hpp main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

jugador.o: jugador/jugador.cpp
	$(CC) $(CFLAGS) -c jugador/jugador.cpp

tablero.o: jugador/jugador.hpp casilla/casilla.hpp tablero/tablero.cpp 
	$(CC) $(CFLAGS) -c tablero/tablero.cpp

casilla.o: jugador/jugador.hpp casilla/casilla.cpp
	$(CC) $(CFLAGS) -c casilla/casilla.cpp

jailCasilla.o: casilla/casilla.hpp casilla/jailCasilla/jailCasilla.cpp
	$(CC) $(CFLAGS) -c casilla/jailCasilla/jailCasilla.cpp

moneyCasilla.o: casilla/casilla.hpp casilla/moneyCasilla/moneyCasilla.cpp
	$(CC) $(CFLAGS) -c casilla/moneyCasilla/moneyCasilla.cpp

moveCasilla.o: casilla/casilla.hpp casilla/moveCasilla/moveCasilla.cpp
	$(CC) $(CFLAGS) -c casilla/moveCasilla/moveCasilla.cpp

clean:
	rm -f main $(OBJS) *.out
