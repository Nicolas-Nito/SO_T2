#ifndef __H_JAILCASILLA__
#define __H_JAILCASILLA__

#include "../casilla.hpp"

class JailCasilla :  public Casilla{
    public:
        JailCasilla(int parametro, string nombre) : Casilla(parametro, nombre){};
        int action(Jugador *jugador);
};

#endif