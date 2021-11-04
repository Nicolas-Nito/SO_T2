#include "casilla.hpp"

Casilla::Casilla(int _parametro, string _nombre, int _type){
    parametro = _parametro;
    nombre = _nombre;
    type = _type;
};

int Casilla::action(Jugador *jugador){
    std::cout << "Jugador " <<jugador->getId() << " : " << this->getName();
    return NOTHING;
}

int Casilla::getValue(){
    return this->parametro;
}

string Casilla::getName(){
    return this->nombre;
}

int Casilla::getType(){
    return this->type;
}