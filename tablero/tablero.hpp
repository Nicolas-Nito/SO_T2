#ifndef __ARRAY_H__
#define __ARRAY_H__

#define MAXSIZE 28

#include "../jugador/jugador.hpp"
#include "../casilla/casilla.hpp"

/*La lista basada en array debe contar con : Tamaño maximo, tamaño actual, posicion curr, array lista.*/
typedef Casilla tElemLista;


class Tablero {
private:
    unsigned int maxsize;
    unsigned int listSize;
    unsigned int curr;
    tElemLista* listArray;
public:
    Tablero(); //constructor
    ~Tablero();
    void clear(); //reinicialización vacia
    int append(tElemLista item); // al final
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    void goForwardBy(int spaces);
    void goBackwardsBy(int spaces);
    int length();
    int currPos();
    void moveToPos(int pos);
    tElemLista getValue();
};

#endif

