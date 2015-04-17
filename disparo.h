#ifndef DISPARO_H
#define DISPARO_H

#include "constantes.h"
#include "spriteanimado.h"
#include "jugador.h"
#include <SDL.h>


class Disparo:public SpriteAnimado{
    public:
        Disparo();
        void crear(Jugador *player);
        int getEstado(){return estado;}
        void setEstado(int e){estado=e;}
        int getDireccion(){return direccion;}
        void setDireccion(int d){direccion=d;}
        void crearAreasColision();
        void mover();

    private:
        int tipo;
        int danio;
        int estado;
        int direccion;

};

#endif // DISPARO_H
