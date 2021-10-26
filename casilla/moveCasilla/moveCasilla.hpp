#ifndef __H_MOVECASILLA__
#define __H_MOVECASILLA__

#include "../casilla.hpp"

class MoveCasilla :  public Casilla{
    public:
        MoveCasilla(int parametro, string nombre) : Casilla(parametro, nombre){};
        int action(Jugador *jugador);
};

#endif