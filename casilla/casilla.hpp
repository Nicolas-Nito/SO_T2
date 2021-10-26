#ifndef __H_CASILLA__
#define __H_CASILLA__

using namespace std;
#include <string>
#include "../jugador/jugador.hpp"

typedef enum tipoCasilla{
    MOVE,
    MONEY,
    JAIL
} tipoCasilla;

class Casilla{
    private:
        int parametro;
        string nombre;
    public:
        Casilla(int _parametro, string _nombre);
        int action(Jugador *jugador);
        int getValue();
        string getName();
};

#endif