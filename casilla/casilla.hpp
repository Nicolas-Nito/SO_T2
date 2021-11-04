#ifndef __H_CASILLA__
#define __H_CASILLA__

using namespace std;
#include <string>
#include "../jugador/jugador.hpp"
#include <iostream>
typedef enum tipoCasilla{
    MONEY = 2,
    MOVE = 3,
    JAIL = 4,
    NOTHING = 5
} tipoCasilla;

class Casilla{
    private:
        int parametro;
        string nombre;
        int type;
    public:
        Casilla(int _parametro, string _nombre, int _type);
        virtual ~Casilla(){};
        virtual int action(Jugador *jugador);
        int getValue();
        string getName();
        int getType();
};

#endif