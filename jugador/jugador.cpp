#include "jugador.hpp"
#include "stdlib.h"
#include "iostream"

Jugador::Jugador(int _id){
    pos = 0;
    monedero = 100;
    preso = NOT_JAILED;
    id = _id;
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
    return this->getId();
}

void Jugador::setPos(int pos){
    this->pos = pos;
}

void Jugador::setMonedero(int monedero){
    this->monedero = monedero;
}

void Jugador::setPreso(int preso){
    this->preso = preso;
}

bool Jugador::rollTheDiceAndMove(){
    if(this->getId() == 1) // Player 1
    {
        int a ;
        std::cout<<"*Lanzar el dado*";
        std::cin >> a;
        std::cout<<"\n"; 
    }
    int diceRoll = (rand()%6) + 1;
    std::cout << "Dado lanzado por el jugador " << this->getId() << ", resultado" << diceRoll << "\n";
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
    this->setMonedero(this->getMonedero() + value);
}