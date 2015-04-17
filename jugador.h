#ifndef JUGADOR_H
#define JUGADOR_H

#include "spriteanimado.h"
#include "jugador.h"
#include "constantes.h"
#include <SDL.h>


class Jugador :public SpriteAnimado{
    private:
//        SDL_Surface *spriteSheet;
//        int posx,posy;
//        int frameActual;
//        int nframes;
        int vidas;
        int score;
        int speed;
        int estado;
        int direccion;
//        int timeAnimacion;


    public:
        Jugador();
        void animar(SDL_Surface *screen);

        //getters and setters
        int getVidas(){return vidas;}
        void setVidas(int lives){vidas=lives;}

        int getScore(){return score;}
        void setScore(int sc){score=sc;}

        int getSpeed() {return speed;}
        void setSpeed(int s) {speed=s;}

        int getEstado(){return estado;}
        void setEstado(int est){estado=est;}

        int getDireccion(){return direccion;}
        void setDireccion(int dir){direccion=dir;}

};

#endif // JUGADOR_H
