#ifndef __H_MOVECASILLA__
#define __H_MOVECASILLA__

#include "../casilla.hpp"

class MoveCasilla :  public Casilla{
    public:
        MoveCasilla(int parametro, string nombre, int type) : Casilla(parametro, nombre, type){};
        ~MoveCasilla() {};
        int action(Jugador *jugador) override;
};

#endif