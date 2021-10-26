using namespace std;
#include <string>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "casilla/casilla.hpp"
#include "tablero/tablero.hpp"
#include "jugador/jugador.hpp"
#include "casilla/moneyCasilla/moneyCasilla.hpp"
#include "casilla/moveCasilla/moveCasilla.hpp"
#include "casilla/jailCasilla/jailCasilla.hpp"

/*
    Llevar un registro de posición tanto en el tablero como en el jugador es un lío....
    pero se hizo así y no tengo ganas de refactorearlo la verdad.
*/

int WIN_LIMIT = 500;
int START_VALUE = 100;

pid_t child_pid[3] = {-1, -1, -1};

void generateBoard(Tablero *tablero){
    tablero->append(MoneyCasilla(200, "Diste una vuelta \n"));
    tablero->append(MoneyCasilla(50, "Ganas 50 pesos \n"));
    tablero->append(MoneyCasilla(50, "Ganas 50 pesos \n"));
    tablero->append(MoneyCasilla(-25, "Pierdes 25 pesos \n"));
    tablero->append(MoveCasilla(-2, "Retrocedes 2 casillas \n"));
    tablero->append(MoneyCasilla(50, "Ganas 50 pesos \n"));
    tablero->append(MoneyCasilla(-25, "Pierdes 25 pesos \n"));
    tablero->append(JailCasilla(0, "Caiste en cana\n"));
    tablero->append(MoneyCasilla(75, "Ganas 75 pesos \n"));
    tablero->append(MoneyCasilla(-50, "Pierdes 50 pesos \n"));
    tablero->append(MoneyCasilla(-50, "Pierdes 50 pesos \n"));
    tablero->append(MoneyCasilla(75, "Ganas 75 pesos \n"));
    tablero->append(MoneyCasilla(75, "Ganas 75 pesos \n"));
    tablero->append(MoveCasilla(-3, "Retrocedes 3 casillas \n"));   
    tablero->append(MoveCasilla(0, "Aqui no pasa naa, suerte no te asalto un flaite \n"));   
    tablero->append(MoveCasilla(3, "Avanza 3 casillas \n"));   
    tablero->append(MoneyCasilla(50, "Ganas 50 pesos \n"));   
    tablero->append(MoveCasilla(-4, "Retrocedes 4 casillas \n"));
    tablero->append(MoneyCasilla(50, "Ganas 50 pesos \n"));
    tablero->append(MoneyCasilla(-50, "Pierdes 50 pesos \n"));
    tablero->append(MoneyCasilla(-25, "Pierdes 25 pesos \n"));
    tablero->append(JailCasilla(0, "Caiste en cana\n"));
    tablero->append(MoneyCasilla(75, "Ganas 75 pesos \n"));
    tablero->append(MoveCasilla(5, "Avanza 5 casillas \n"));  
    tablero->append(MoneyCasilla(75, "Ganas 75 pesos \n"));
    tablero->append(MoveCasilla(-4, "Retrocedes 4 casillas \n"));
    tablero->append(MoneyCasilla(-25, "Pierdes 25 pesos \n"));
    tablero->append(MoneyCasilla(-75, "Pierdes 75 pesos \n"));
}

void playAction(Jugador *player, Tablero *tablero){
    int tipo = tablero->getValue().action(player); // Retorna el tipo de accion (JAIL, MOVE, MONEY)
    std::cout << tablero->getValue().getName();
    if(tipo == MOVE){
        int pos = tablero->getValue().getValue();
        if(pos > 0 ) tablero->goForwardBy(pos);
        else tablero->goBackwardsBy(pos);
        playAction(player, tablero);
    }
    // JAIL y MONEY no requieren ningún tipo de acción.
    return;
}

bool playTurn(Jugador *player, Tablero *tablero){
    if(player->getPreso() == JAILED){
        player->setPreso(NOT_JAILED);
        return false;
    } 
    bool vuelta = player->rollTheDiceAndMove();
    
    // Pasó por Salida
    if(vuelta) player->calculateMonedero(START_VALUE);
    
    // Win condition PRE-Acción
    if(player->getMonedero() >= WIN_LIMIT) return true;
    
    // Jugamos la acción
    tablero->moveToPos(player->getPos());
    playAction(player, tablero);
    
    // Win condition POST-Acción
    if(player->getMonedero() >= WIN_LIMIT) return true;
    return false;
}

int main(){
    Tablero tablero;
    bool win = false;
    generateBoard(&tablero);
    child_pid[0] = fork();
    if(child_pid[0] == 0){
        // Player 1
        Jugador player1(1);
        while(!win){
            // Play
            printf("Jugado player 1\n");
            win = playTurn(&player1, &tablero);
        }
    }else{
        child_pid[1] = fork();
        if(child_pid[1] == 0){
            // Player 2
            Jugador player2(2);
            while(!win){
                // Play
                printf("Jugado player 2\n");
                win = playTurn(&player2, &tablero); 
            }
        }else{
            if(child_pid[2] == 0){
                // Player 3
                Jugador player3(3);
                while(!win){
                    // Play
                    printf("Jugado player 3\n");
                    win = playTurn(&player3, &tablero); 
                }
            }else{
                // Parent
                int watchdog = 0;
                bool flag = true;
                while ( flag ) {
                    watchdog+=1;
                    int status_p1;
                    int status_p2;
                    int status_p3;

                    waitpid(child_pid[0], &status_p1, 0);
                    waitpid(child_pid[1], &status_p2, 0);
                    waitpid(child_pid[2], &status_p3, 0);
                    
                    if (WIFEXITED(status_p1)){
                        std::cout << "Ganó el jugador 1\n";
                        flag = false;
                    }else if(WIFEXITED(status_p2)){
                        std::cout << "Ganó el jugador 2\n";
                        flag = false;
                    }else if(WIFEXITED(status_p3)){
                        std::cout << "Ganó el jugador 3\n";
                        flag = false;
                    }
                    else{
                        printf("Esperando ganador\n");
                    }
                    if(!flag){
                        for(int i = 0 ; i < 3 ; i++){
                            kill(child_pid[i], SIGKILL);
                        }
                    }
                }
            }
        }
    }

    return 1;
}