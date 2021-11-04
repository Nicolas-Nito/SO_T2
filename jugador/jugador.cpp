#include "jugador.hpp"
#include "stdlib.h"
#include "iostream"

Jugador::Jugador(int _id){
    this->pos = 0;
    this->monedero = 100;
    this->preso = NOT_JAILED;
    this->id = _id;
}

int Jugador::getPos(){
    return this->pos;
}

int Jugador::getMonedero(){
    return this->monedero;
}

int Jugador::getPreso(){
    return this->preso;
}

int Jugador::getId(){
    return this->id;
}

void Jugador::setPos(int _pos){
    this->pos = _pos;
}

void Jugador::setMonedero(int _monedero){
    this->monedero = _monedero;
}

void Jugador::setPreso(int _preso){
    this->preso = _preso;
}

bool Jugador::rollTheDiceAndMove(){
    /* if(this->getId() == 1) // Player 1
    {
        std::cout<<"*Lanzar el dado*";
        std::cin.ignore();
    } */
    int diceRoll = (rand()%6) + 1;
    std::cout << "Dado lanzado por el jugador " << this->getId() << ", resultado " << diceRoll << "\n";
    int newPos = diceRoll + this->getPos();
    if(newPos > MAXSIZE-1){
        newPos -= MAXSIZE;
        this->setPos(newPos);
        return true;
    }else{
        this->setPos(newPos);
        return false;
    }
}

void Jugador::calculateMonedero(int value){
    int setValue = this->getMonedero() + value;
    if(setValue < 0) setValue = 0;
    this->setMonedero(setValue);
}