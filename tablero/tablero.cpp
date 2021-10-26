#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablero.hpp"

Tablero::Tablero(){
    maxsize = MAXSIZE;
    listSize = 0;
    curr = 0;
    listArray = (tElemLista *)malloc(maxsize * sizeof(tElemLista));
}

Tablero::~Tablero(){ free(listArray); }

void Tablero::clear(){
    free (listArray);
    curr = listSize = 0;
    listArray = (tElemLista *)malloc(maxsize * sizeof(tElemLista));
}


int Tablero::append(tElemLista item){
    if (listSize >= maxsize){
        return 0; // lista llena, no inserta
    }
    listArray[listSize++] = item;
    return 1; // insercion exitosa
}


void Tablero::moveToStart(){ curr = 0; }

void Tablero::moveToEnd(){ curr = listSize-1; }

void Tablero::prev(){ if (curr != 0) curr--; }

void Tablero::next(){ if (curr < listSize) curr++; }

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

tElemLista Tablero::getValue(){
    return listArray[curr];
}
