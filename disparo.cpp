#include "disparo.h"
#include "constantes.h"
#include "jugador.h"
#include "spriteanimado.h"
#include <SDL.h>


Disparo::Disparo():SpriteAnimado(){
    estado=INACTIVO;
    danio=1;
    tipo=NORMAL;
    areasColision=new SDL_Rect[1];
    crearAreasColision();
}

void Disparo::crear(Jugador *player){
    estado=ACTIVO;
    setx(player->getx()+(WIDTH_PLAYER/2));
    sety(player->gety()+(HEIGHT_PLAYER/2));
    direccion=player->getDireccion();
}

void Disparo::crearAreasColision(){
    areasColision[0].x=1;
    areasColision[0].y=1;
    areasColision[0].w=3;
    areasColision[0].h=3;
}

void Disparo::mover(){
    if(getEstado()==ACTIVO){
        if(getx()>0 && getx()<WIDTH-5 && gety()>0 && gety()<HEIGHT-5){
            if(getDireccion()==UP){addy(-SPEED_DISPARO);}

            if(getDireccion()==DOWN){addy(SPEED_DISPARO);}

            if(getDireccion()==LEFT){addx(-SPEED_DISPARO);}

            if(getDireccion()==RIGHT){addx(SPEED_DISPARO);}

            if(getDireccion()==UP_LEFT){addy(-SPEED_DISPARO);
                                                    addx(-SPEED_DISPARO);}

            if(getDireccion()==UP_RIGHT){addy(-SPEED_DISPARO);
                                                    addx(SPEED_DISPARO);}

            if(getDireccion()==DOWN_LEFT){addy(SPEED_DISPARO);
                                                    addx(-SPEED_DISPARO);}

            if(getDireccion()==DOWN_RIGHT){addy(SPEED_DISPARO);
                                                    addx(SPEED_DISPARO);}
        }else{
            setEstado(INACTIVO);
        }
    }
}
