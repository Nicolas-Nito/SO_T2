#include <stdio.h>
#include <string.h>
#define LARGO_TABLERO 28

struct jugador {  //struct del jugador contiene monedero y poscicion en el juego
    int pos;
    int monedero;
    int preso;   //1 = si-> pierde el siguiente turno y cambia a 0
};

struct casilla {  //struct de las casillas del juego contiene una direccion para funciones para la implementacion de los efectos de las casillas
    void (*funcion)(const struct casilla**, struct jugador*, int );
    int parametro;
    char nombre[50];
};

void mover(const struct casilla** T, struct jugador* J, int casillas){                        // funcion que mueve a un jugador por el tablero y activa la sgt casilla
    //printf("pos inicial: %d\n",J->pos);
    if (J->pos+casillas/LARGO_TABLERO==1){ //se realisa una vuelta al tablero
        J->monedero=J->monedero+100;
    }
    J->pos = (J->pos+casillas)%LARGO_TABLERO;
    //printf("pos final: %d\n",J->pos);
    T[J->pos]->funcion(T,J,T[J->pos]->parametro);  
    /*probar al final, tener en cuanta que se hara un arreglo de struct tablero.*/}

void ajuste_monedero(const struct casilla** T, struct jugador* J,int dinero){
    J->monedero = J->monedero+dinero;

    /*if (J->monedero >= 500){
        funcion de fin del juego
    }*/}

void carcel(const struct casilla** T, struct jugador* J,int vacia){

    J->preso=1;}

void gratis(const struct casilla** T, struct jugador* J,int bool){
    printf("capo ¿que haces descansando? El mundo sigue girando");}
//struct tablero crear_tablero();
const struct casilla* crear_tablero(){
    struct casilla TABLERO[LARGO_TABLERO];
    
        TABLERO[0].funcion   = gratis;
        TABLERO[0].parametro = 1;
        strcpy(TABLERO[0].nombre, "Diste una vuelta \n");
        
        TABLERO[1].funcion   = ajuste_monedero;
        TABLERO[1].parametro = 50;
        strcpy(TABLERO[1].nombre, "Ganas 50 pesos \n");

        TABLERO[2].funcion   = ajuste_monedero;
        TABLERO[2].parametro = 50;
        strcpy(TABLERO[2].nombre, "Ganas 50 pesos \n");
        
        TABLERO[3].funcion   = ajuste_monedero;
        TABLERO[3].parametro = -25;
        strcpy(TABLERO[3].nombre, "Pierdes 25 pesos \n");
        
        TABLERO[4].funcion   = mover;
        TABLERO[4].parametro = -2;
        strcpy(TABLERO[4].nombre, "Retrocedes 2 casillas \n");
        
        TABLERO[5].funcion   = ajuste_monedero;
        TABLERO[5].parametro = 50;
        strcpy(TABLERO[5].nombre, "Ganas 50 pesos \n");
        
        TABLERO[6].funcion   = ajuste_monedero;
        TABLERO[6].parametro = -25;
        strcpy(TABLERO[6].nombre, "Pierdes 25 pesos \n");
        
        TABLERO[7].funcion   = carcel;
        TABLERO[7].parametro = 1;
        strcpy(TABLERO[7].nombre, "Caiste en cana");
        
        TABLERO[8].funcion   = ajuste_monedero;
        TABLERO[8].parametro = 75;
        strcpy(TABLERO[8].nombre, "Ganas 75 pesos \n");
        
        TABLERO[9].funcion   = ajuste_monedero;
        TABLERO[9].parametro = -50;
        strcpy(TABLERO[9].nombre, "Pierdes 50 pesos \n");
        
        TABLERO[10].funcion   = ajuste_monedero;
        TABLERO[10].parametro = -50;
        strcpy(TABLERO[10].nombre, "Pierdes 50 pesos \n");
        
        TABLERO[11].funcion   = ajuste_monedero;
        TABLERO[11].parametro = 75;
        strcpy(TABLERO[11].nombre, "Ganas 75 pesos \n");
         
        TABLERO[12].funcion   = ajuste_monedero;
        TABLERO[12].parametro = 75;
        strcpy(TABLERO[12].nombre, "Ganas 75 pesos \n");
         
        TABLERO[13].funcion   = mover;
        TABLERO[13].parametro = -3;
        strcpy(TABLERO[13].nombre, "Retrocedes 3 casillas \n");
         
        TABLERO[14].funcion   = gratis;
        TABLERO[14].parametro = 1;
        strcpy(TABLERO[14].nombre, "Aqui no pasa naa, suerte no te asalto un flaite \n");
         
        TABLERO[15].funcion   = mover;
        TABLERO[15].parametro = 3;
        strcpy(TABLERO[15].nombre, "Avanzas 3 casillas \n");
         
        TABLERO[16].funcion   = ajuste_monedero;
        TABLERO[16].parametro = 50;
        strcpy(TABLERO[16].nombre, "Ganas 50 pesos \n");
 
        TABLERO[17].funcion   = mover;
        TABLERO[17].parametro = -4;
        strcpy(TABLERO[17].nombre, "Retrocedes 4 casillas \n");
         
        TABLERO[18].funcion   = ajuste_monedero;
        TABLERO[18].parametro = 50;
        strcpy(TABLERO[18].nombre, "Ganas 50 pesos \n");
         
        TABLERO[19].funcion   = ajuste_monedero;
        TABLERO[19].parametro = -50;
        strcpy(TABLERO[19].nombre, "Pierdes 50 pesos \n");
         
        TABLERO[20].funcion   = ajuste_monedero;
        TABLERO[20].parametro = -25;
        strcpy(TABLERO[20].nombre, "Pierdes 25 pesos \n");
         
        TABLERO[21].funcion   = carcel;
        TABLERO[21].parametro = 1;
        strcpy(TABLERO[21].nombre, "Caiste en cana\n");
         
        TABLERO[22].funcion   = ajuste_monedero;
        TABLERO[22].parametro = 75;
        strcpy(TABLERO[22].nombre, "Ganas 75 pesos \n");
         
        TABLERO[23].funcion   = mover;
        TABLERO[23].parametro = 5;
        strcpy(TABLERO[23].nombre, "Avanzas 5 casillas \n");
         
        TABLERO[24].funcion   = ajuste_monedero;
        TABLERO[24].parametro = 75;
        strcpy(TABLERO[24].nombre, "Ganas 75 pesos \n");
         
        TABLERO[25].funcion   = mover;
        TABLERO[25].parametro = -4;
        strcpy(TABLERO[25].nombre, "Retrocedes 4 casillas \n");
         
        TABLERO[26].funcion   = ajuste_monedero;
        TABLERO[26].parametro = -25;
        strcpy(TABLERO[26].nombre, "Pierdes 25 pesos \n");
         
        TABLERO[27].funcion   = ajuste_monedero;
        TABLERO[27].parametro = -75;
        strcpy(TABLERO[27].nombre, "Pierdes 75 pesos \n");
        
    return TABLERO;
    }
int main(){
    struct jugador test_J = {0,100};
    const struct casilla* tablero = crear_tablero();

    mover(&tablero,&test_J,1);
    printf("dinero: %d\n",test_J.monedero);
    printf("pos: %d\n",test_J.pos);



    printf("valor almacenado: %d\n",test_J.pos);
    
}