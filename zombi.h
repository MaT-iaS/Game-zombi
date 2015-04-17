#ifndef ZOMBI_H
#define ZOMBI_H

#include "spriteanimado.h"
#include "jugador.h"
#include <SDL.h>

class Zombi:public SpriteAnimado{
    private:
        int speed;
        int estado;
        int direccion;
        int HP;
//        SDL_Rect areasColision[3];
    public:
        Zombi();
        void animar(SDL_Surface *screen);
        int mover(Jugador *player);
        void crear();
        void crearAreasColision();

        //getters and setters
        int getHP(){return HP;}
        void setHP(int h){HP=h;}
        int getSpeed() {return speed;}
        void setSpeed(int s) {speed=s;}
        int getEstado(){return estado;}
        void setEstado(int est){estado=est;}
        int getDireccion(){return direccion;}
        void setDireccion(int dir){direccion=dir;}
};

#endif // ZOMBI_H
