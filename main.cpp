using namespace std;
#include <string>
#include <sstream>
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

int SLEEP_TIME = 5;    // Segundos de descanso entre turnos, +- sobre 5 funciona bien, muy poco y los turnos de un hijo pueden pasar al otro
int WIN_LIMIT = 500;   // Límite de victoria
int START_VALUE = 100; // Valor de la casilla de inicio

void drawBoard(int p1 = -1, int p2 = -1, int p3 = -1, Tablero *tablero = NULL){
    // Dibuja el tablero
    int board[8][8] =  {{7, 8, 9, 10 , 11 , 12, 13, 14},
                            {6 ,-1, -1, -1, -1, -1, -1, 15},
                            {5 ,-1, -1, -1, -1, -1, -1, 16},
                            {4 ,-1, -1, -1, -1, -1, -1, 17},
                            {3 ,-1, -1, -1, -1, -1, -1, 18},
                            {2 ,-1, -1, -1, -1, -1, -1, 19},
                            {1 ,-1, -1, -1, -1, -1, -1, 20},
                            {0 ,27, 26, 25, 24, 23, 22, 21}
                            }; 
    std::stringstream ss;
    string a = "";
    string printBoard[8][8] = {{a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            {a, a, a, a , a , a, a, a},
                            }; 
    for(int y = 0 ; y < 8 ; y++){
        for(int x = 0 ; x < 8 ; x++){
            //  x
            int pos = board[y][x];
            if(pos >-1){
                string isP1 = "";
                string isP2 = "";
                string isP3 = "";
                int value = tablero->getValueFrom(board[y][x])->getValue();
                if (p1 == pos) isP1 = "P1";
                if (p2 == pos) isP2 = "P2";
                if (p3 == pos) isP3 = "P3";
                if(value > 5){
                    std::stringstream ss;
                    
                    ss << "  "<<value<<"("<<isP1<<isP2<<isP3<<")"<<"  - ";
                    
                    
                    printBoard[y][x] += ss.str();
                }else if(value < -5){
                    std::stringstream ss;
                    ss << "  "<<value<<"("<<isP1<<isP2<<isP3<<")"<<"  -";
                    printBoard[y][x] += ss.str();                                          
                }else if(value == 0){//NOTHING
                    std::stringstream ss;
                    
                    ss << "   Free"<<"("<<isP1<<isP2<<isP3<<")"<<"  -";
                    
                    printBoard[y][x] += ss.str();

                }else if(value == -1){// JAIL
                    std::stringstream ss;
                    ss << "  Jail"<<"("<<isP1<<isP2<<isP3<<")"<<"  -";
                    
                    printBoard[y][x] += ss.str();
                }else if(value > 0 && value <= 5){ // MOVE
                    std::stringstream ss;
                    ss << "  Forward "<< value <<"("<<isP1<<isP2<<isP3<<")"<< "  -";
                    
                    printBoard[y][x] += ss.str();
                }else{
                    std::stringstream ss;
                    ss << "  Back "<< value <<"("<<isP1<<isP2<<isP3<<")"<<  "  -";
                    
                    printBoard[y][x] += ss.str();
                }
            }else{
                    std::stringstream ss;
                    ss << "           ";
                    printBoard[y][x] += ss.str();
                    
            }   
        }        
    }
    for(int y = 0 ; y < 8 ; y++){
        for(int x = 0 ; x < 8 ; x++){
            std::cout << printBoard[y][x];
            
        }
        std::cout << "\n";           
    }
}

void writeToPipe(int p[2], int pos){
    // Función para escribir a las pipes de hijos a padre
    close(p[0]);
    write(p[1], &pos, sizeof(&pos));
}

void throughStart(Jugador *player){
    // Se encarga de añadir los fondos de un jugador que pasa por salida
    player->calculateMonedero(START_VALUE);
    std::cout << "Jugador " << player->getId() << "pasó por salida, nuevo monedero : " << player->getMonedero() << "\n";
}

void generateBoard(Tablero *tablero){
    // Genera el tablero

    tablero->append(NOTHING, 0, "Diste una vuelta \n"); // Hacemos esta verificación aparte, así que no asignamos dinero como casilla
    tablero->append(MONEY, 50, "Ganas 50 pesos \n");
    tablero->append(MONEY, 50, "Ganas 50 pesos \n");
    tablero->append(MONEY, -25, "Pierdes 25 pesos \n");
    tablero->append(MOVE, -2, "Retrocedes 2 casillas \n");
    tablero->append(MONEY, 50, "Ganas 50 pesos \n");
    tablero->append(MONEY, -25, "Pierdes 25 pesos \n");
    tablero->append(JAIL, -1, "Caiste en cana\n");
    tablero->append(MONEY, 75, "Ganas 75 pesos \n");
    tablero->append(MONEY, -50, "Pierdes 50 pesos \n");
    tablero->append(MONEY, -50, "Pierdes 50 pesos \n");
    tablero->append(MONEY, 75, "Ganas 75 pesos \n");
    tablero->append(MONEY, 75, "Ganas 75 pesos \n");
    tablero->append(MOVE, -3, "Retrocedes 3 casillas \n");   
    tablero->append(NOTHING, 0, "Aqui no pasa naa, suerte no te asalto un flaite \n");   
    tablero->append(MOVE, 3, "Avanza 3 casillas \n");   
    tablero->append(MONEY, 50, "Ganas 50 pesos \n");   
    tablero->append(MOVE, -4, "Retrocedes 4 casillas \n");
    tablero->append(MONEY, 50, "Ganas 50 pesos \n");
    tablero->append(MONEY, -50, "Pierdes 50 pesos \n");
    tablero->append(MONEY, -25, "Pierdes 25 pesos \n");
    tablero->append(JAIL, -1, "Caiste en cana\n");
    tablero->append(MONEY, 75, "Ganas 75 pesos \n");
    tablero->append(MOVE, 5, "Avanza 5 casillas \n");  
    tablero->append(MONEY, 75, "Ganas 75 pesos \n");
    tablero->append(MOVE, -4, "Retrocedes 4 casillas \n");
    tablero->append(MONEY, -25, "Pierdes 25 pesos \n");
    tablero->append(MONEY, -75, "Pierdes 75 pesos \n");
}

void playAction(Jugador *player, Tablero *tablero){
    // Juega la acción de la casilla
    int playerPos = player->getPos();
    int type = tablero->getValueFrom(playerPos)->getType();
    int actionValue = tablero->getValueFrom(playerPos)->action(player);
    if(type == MOVE){
        if(actionValue) {
            throughStart(player);
        }
        playAction(player, tablero);
    }else if (type == MONEY){
        std::cout << "Nuevo monedero del jugador " << player->getId() << ": " << player->getMonedero() << "\n"; 
    }
    // JAIL y NOTHING no requieren ningún tipo de acción.
    return;
}

bool playTurn(Jugador *player, Tablero *tablero){
    if(player->getPreso() == JAILED){
        player->setPreso(NOT_JAILED);
        return false;
    } 
    bool vuelta = player->rollTheDiceAndMove();
    
    // Pasó por Salida
    if(vuelta) throughStart(player);
    
    // Win condition PRE-Acción
    if(player->getMonedero() >= WIN_LIMIT) return true;
    
    // Jugamos la acción
    playAction(player, tablero);
    
    // Win condition POST-Acción
    if(player->getMonedero() >= WIN_LIMIT) return true;
    return false;
}

int main(){
    pid_t child_pid[3] = {-1, -1, -1};
    Tablero tablero;
    bool win = false;
    generateBoard(&tablero);
    drawBoard(-1,-1,-1,&tablero);
    fflush(stdout);
    int p1[2];
    pipe(p1);
    child_pid[0] = fork();
    if(child_pid[0] == 0){
        srand(time(NULL) ^ getpid());
        // Player 1
        Jugador player1(1);
        while(!win){
            // Play
            std::cout << "Monedero player " << player1.getId() << ": "<< player1.getMonedero() << "\n";
            win = playTurn(&player1, &tablero);
            writeToPipe(p1, player1.getPos());
            sleep(SLEEP_TIME);
            if(win) exit(0);
        }
    }else{
        fflush(stdout);
        int p2[2];
        pipe(p2);
        child_pid[1] = fork();
        if(child_pid[1] == 0){
            // Player 2
            srand(time(NULL) ^ getpid());
            Jugador player2(2);
            while(!win){
                // Play
                std::cout << "Monedero player " << player2.getId() << ": "<< player2.getMonedero() << "\n";
                win = playTurn(&player2, &tablero);
                writeToPipe(p2, player2.getPos());
                sleep(SLEEP_TIME);
                if(win) exit(0); 
            }
        }else{
            fflush(stdout);
            int p3[2];
            pipe(p3);
            child_pid[2] = fork();
            if(child_pid[2] == 0){
                srand(time(NULL) ^ getpid());
                // Player 3
                Jugador player3(3);
                while(!win){
                    // Play
                    std::cout << "Monedero player " << player3.getId() << ": "<< player3.getMonedero() << "\n";
                    win = playTurn(&player3, &tablero);
                    writeToPipe(p3, player3.getPos());
                    sleep(SLEEP_TIME);
                    if(win) exit(0); 
                }
            }else{
                // Parent
                bool flag = true;
                while ( flag ) {
                    int pos1, pos2, pos3;
                    int status_p1, status_p2, status_p3;

                    read(p1[0], &pos1, sizeof(&pos1));
                    read(p2[0], &pos2, sizeof(&pos2));
                    read(p3[0], &pos3, sizeof(&pos3));
                    
                    drawBoard(pos1, pos2, pos3, &tablero);

                    int result_p1 = waitpid(child_pid[0], &status_p1, WNOHANG);
                    int result_p2 = waitpid(child_pid[1], &status_p2, WNOHANG);
                    int result_p3 = waitpid(child_pid[2], &status_p3, WNOHANG);
                    if (result_p1 == child_pid[0]){
                        std::cout << "Ganó el jugador 1\n";
                        flag = false;
                    }else if(result_p2 == child_pid[1]){
                        std::cout << "Ganó el jugador 2\n";
                        flag = false;
                    }else if(result_p3 == child_pid[2]){
                        std::cout << "Ganó el jugador 3\n";
                        flag = false;
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