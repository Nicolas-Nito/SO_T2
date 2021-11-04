#include "moneyCasilla.hpp"

int MoneyCasilla::action (Jugador *jugador){
    Casilla::action(jugador);
    jugador->calculateMonedero(this->getValue());
    return MONEY;
}