#include "jailCasilla.hpp"

int JailCasilla::action(Jugador *jugador){
    Casilla::action(jugador);
    jugador->setPreso(1);
    return JAIL;
}