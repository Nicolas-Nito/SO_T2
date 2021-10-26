#ifndef __H_MONEYCASILLA__
#define __H_MONEYCASILLA__

#include "../casilla.hpp"

class MoneyCasilla :  public Casilla{
    public:
        MoneyCasilla(int parametro, string nombre) : Casilla(parametro, nombre){};
        int action(Jugador *jugador);
};

#endif