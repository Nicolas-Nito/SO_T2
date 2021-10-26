#include "moveCasilla.hpp"

int MoveCasilla::action(Jugador *jugador){
    int newPos = this->getValue() + jugador->getPos();
    jugador->setPos(newPos);
    return MOVE;
}