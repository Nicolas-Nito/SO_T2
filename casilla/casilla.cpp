#include "casilla.hpp"

Casilla::Casilla(int _parametro, string _nombre){
    parametro = _parametro;
    nombre = _nombre;
};

int Casilla::action(Jugador *jugador){
    return -1;
}

int Casilla::getValue(){
    return this->parametro;
}

string Casilla::getName(){
    return this->nombre;
}