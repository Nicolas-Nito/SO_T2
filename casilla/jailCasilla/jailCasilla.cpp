#include "jailCasilla.hpp"

int JailCasilla::action(Jugador *jugador){
    jugador->setPreso(1);
    return JAIL;
}