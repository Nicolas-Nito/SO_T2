#include "moneyCasilla.hpp"

int MoneyCasilla::action(Jugador *jugador){
    jugador->calculateMonedero(this->getValue());
    return MONEY;
}