
#include "spriteanimado.h"
#include "jugador.h"
#include "constantes.h"
#include <SDL.h>

Jugador::Jugador(){
    areasColision=new SDL_Rect[1];
    areasColision[0].x=4;
    areasColision[0].y=3;
    areasColision[0].w=10;
    areasColision[0].h=29;

    setTimeAnimacion(SDL_GetTicks());
    setx(WIDTH/2);
    sety(HEIGHT/2);
    speed=SPEED_INICIAL_PLAYER;
    estado=STAND_STATE;
    direccion=UP;
    vidas=3;
    score=0;
}

void Jugador::animar(SDL_Surface *screen){
    SDL_Rect origen,destino;
    destino.x=getx();
    destino.y=gety();
    destino.w=WIDTH_PLAYER;
    destino.h=HEIGHT_PLAYER;

    if(estado==WALKING_STATE){
        setNFrames(3);
        if(SDL_GetTicks()-getTimeAnimacion()>DELAY_ANIMACION_PLAYER1){
            setTimeAnimacion(SDL_GetTicks());
            if(getFrameActual()<getNFrames()){
                setFrameActual(getFrameActual()+1);
            }else{
                setFrameActual(1);
            }
        }
        origen.x=getFrameActual()*WIDTH_PLAYER;
        origen.y=HEIGHT_PLAYER*getDireccion();
        origen.h=HEIGHT_PLAYER;
        origen.w=WIDTH_PLAYER;

    }else{
        origen.x=0;
        origen.y=HEIGHT_PLAYER*getDireccion();
        origen.h=HEIGHT_PLAYER;
        origen.w=WIDTH_PLAYER;
    }
    SDL_BlitSurface(spriteSheet,&origen,screen,&destino);
}
