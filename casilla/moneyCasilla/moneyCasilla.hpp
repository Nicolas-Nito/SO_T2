#ifndef __H_MONEYCASILLA__
#define __H_MONEYCASILLA__

#include "../casilla.hpp"

class MoneyCasilla :  public Casilla{
    public:
        MoneyCasilla(int parametro, string nombre, int type) : Casilla(parametro, nombre, type){};
        ~MoneyCasilla(){};
        int action(Jugador *jugador) override;
};

#endif