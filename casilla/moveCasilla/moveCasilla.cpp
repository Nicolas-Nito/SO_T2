#include "moveCasilla.hpp"

int MoveCasilla::action(Jugador *jugador){
    Casilla::action(jugador);
    int newPos = this->getValue() + jugador->getPos();
    if(newPos > MAXSIZE-1){
        newPos -= MAXSIZE;
        jugador->setPos(newPos);
        return true;
    }else{
        jugador->setPos(newPos);
        return false;
    }
}