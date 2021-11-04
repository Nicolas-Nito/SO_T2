#ifndef __ARRAY_H__
#define __ARRAY_H__

#define MAXSIZE 28

#include "../jugador/jugador.hpp"
#include "../casilla/casilla.hpp"
#include "../casilla/jailCasilla/jailCasilla.hpp"
#include "../casilla/moneyCasilla/moneyCasilla.hpp"
#include "../casilla/moveCasilla/moveCasilla.hpp"

/*La lista basada en array debe contar con : Tamaño maximo, tamaño actual, posicion curr, array lista.*/
typedef Casilla tElemLista;


class Tablero {
private:
    unsigned int maxsize;
    unsigned int listSize;
    unsigned int curr;
    tElemLista* listArray[MAXSIZE];
public:
    Tablero(); //constructor
    ~Tablero();
    int append(int type, int value, string nombre); // al final
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    void goForwardBy(int spaces);
    void goBackwardsBy(int spaces);
    int length();
    int currPos();
    void moveToPos(int pos);
    tElemLista* getValueFrom(int pos);
};

#endif

