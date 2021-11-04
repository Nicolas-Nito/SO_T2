#ifndef __H_JUGADOR__
#define __H_JUGADOR__

#define NOT_JAILED 0
#define JAILED 1
#define MAXSIZE 28

using namespace std;

class Jugador{
    private:
        int id;
        int pos;
        int monedero;
        int preso;
    public:
        Jugador(int _id);
        int getPos();
        int getMonedero();
        int getPreso();
        int getId();
        void setPos(int _pos);
        void setMonedero(int _monedero);
        void setPreso(int _preso);
        void calculateMonedero(int value);
        bool rollTheDiceAndMove(); // Retorna un booleano para indicar si se dio una vuelta al tablero
};

#endif