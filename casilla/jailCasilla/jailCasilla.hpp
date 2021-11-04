#ifndef __H_JAILCASILLA__
#define __H_JAILCASILLA__

#include "../casilla.hpp"

class JailCasilla :  public Casilla{
    public:
        JailCasilla(int parametro, string nombre, int type) : Casilla(parametro, nombre, type){};
        ~JailCasilla(){};
        int action(Jugador *jugador) override;
};

#endif