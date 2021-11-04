#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablero.hpp"

Tablero::Tablero(){
    maxsize = MAXSIZE;
    listSize = 0;
    curr = 0;
    //listArray = (tElemLista *)malloc(maxsize * sizeof(tElemLista));
}

Tablero::~Tablero(){ 
    for(unsigned int i = 0 ; i < listSize ; i++){
        delete listArray[i];
    }
 }

int Tablero::append(int type, int value, string nombre){
    if (listSize >= maxsize){
        return 0; // lista llena, no inserta
    }
    if(type == JAIL){
        listArray[listSize++] = new JailCasilla(value, nombre, JAIL);
    }else if(type == MOVE){
        listArray[listSize++] = new MoveCasilla(value, nombre, MOVE);
    }else if(type == MONEY){
        listArray[listSize++] = new MoneyCasilla(value, nombre, MONEY);
    }else{
        listArray[listSize++] = new Casilla(value, nombre, NOTHING);
    }
    return 1; // insercion exitosa
}


void Tablero::moveToStart(){ curr = 0; }

void Tablero::moveToEnd(){ curr = listSize-1; }

void Tablero::prev(){ if (curr != 0) curr--; }

void Tablero::next(){ 
    if (this->curr < this->maxsize-1) this->curr++;
    else this->curr = 0;
}

void Tablero::goForwardBy(int spaces){
    for(int i = 0; i < spaces; i++){
        this->next();
    }
}

void Tablero::goBackwardsBy(int spaces){
    for(int i = 0; i < spaces; i++){
        this->prev();
    }
}

int Tablero::length(){
    return listSize;
}

int Tablero::currPos(){
    return curr;
}

void Tablero::moveToPos(int pos){
    curr = pos;
}

tElemLista* Tablero::getValueFrom(int pos){
    return this->listArray[pos];
}
