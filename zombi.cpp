#include "zombi.h"
#include <SDL.h>
#include "constantes.h"
#include "spriteanimado.h"
#include "jugador.h"


Zombi::Zombi():SpriteAnimado(){
    speed=1+rand()%SPEED_INICIAL_ZOMBI;
    estado=DEAD_STATE;
    HP=1;
    areasColision=new SDL_Rect[3];
    crearAreasColision();
}

void Zombi::animar(SDL_Surface *screen){
    SDL_Rect origen,destino;
    destino.x=getx();
    destino.y=gety();
    destino.w=WIDTH_ZOMBI;
    destino.h=HEIGHT_ZOMBI;

    origen.h=HEIGHT_ZOMBI;
    origen.w=WIDTH_ZOMBI;


    /** ANIMACION CUANDO CAMINA **/
    if(estado==WALKING_STATE){
        if(SDL_GetTicks()-getTimeAnimacion()>DELAY_ANIMACION_ZOMBI){
            setTimeAnimacion(SDL_GetTicks());
            if(getFrameActual()<getNFrames()){
                setFrameActual(getFrameActual()+1);
            }else{
                setFrameActual(0);
            }
        }
        origen.y=HEIGHT_ZOMBI*getDireccion();
        if(getFrameActual()<getNFrames()){
            origen.x=getFrameActual()*WIDTH_ZOMBI;
//            origen.y=HEIGHT_ZOMBI*getDireccion();
        }else{
            origen.x=0;
//            origen.y=HEIGHT_ZOMBI*getDireccion();
        }
    }

    /** ANIMACION CUANDO APARECE **/
    if(estado==SPAWNING_STATE){
        setNFrames(4);
        if(SDL_GetTicks()-getTimeAnimacion()>DELAY_ANIMACION_SPAWNING_ZOMBI){
            setTimeAnimacion(SDL_GetTicks());
            if(getFrameActual()<getNFrames()){
                setFrameActual(getFrameActual()+1);
            }else{
                setEstado(WALKING_STATE);
                setFrameActual(0);
            }
        }
        origen.x=getFrameActual()*WIDTH_ZOMBI;
        origen.y=HEIGHT_ZOMBI*5;
    }

    /** ANIMACION CUANDO MUERE **/
    if(estado==DIEING_STATE){
        setNFrames(10);
        if(SDL_GetTicks()-getTimeAnimacion()>DELAY_ANIMACION_DIEING_ZOMBI){
            setTimeAnimacion(SDL_GetTicks());
            if(getFrameActual()+1<getNFrames()){
                setFrameActual(getFrameActual()+1);
            }else{
                setEstado(DEAD_STATE);
            }
        }
        origen.x=getFrameActual()*WIDTH_ZOMBI;
        origen.y=HEIGHT_ZOMBI*4;
    }


    SDL_BlitSurface(spriteSheet,&origen,screen,&destino);
}

/**metodo mover teniendo en cuenta ancho y alto pj
void Zombi::mover(Jugador *player){
    int px=player->getx();
    int py=player->gety();
    int pw=WIDTH_PLAYER-5;
    int ph=HEIGHT_PLAYER-5;

    int zx=getx();
    int zy=gety();
    int zw=WIDTH_ZOMBI-5;
    int zh=HEIGHT_ZOMBI-5;

    if(getEstado()==WALKING_STATE){
        if(( (zx+zw>px) && (zx<px+pw) ) || ( (zy+zh>py) && (zy<py+ph) )){
            if(zx+zw>px && zx<px+pw){
                if(zy< py) {
                    setNFrames(6);
                    addy(getSpeed()+1); //SE MUEVE HACIA ABAJO
                    setDireccion(DOWN);

                }
                else {
                    setNFrames(3);
                    addy(-getSpeed()-1); // SE MUEVE HACIA ARRIBA
                    setDireccion(UP);
                    setNFrames(4);
                }

            }else{
                setNFrames(3);
                if(zx< px) {
                    addx(getSpeed()+1); //SE MUEVE A LA DERECHA
                    setDireccion(RIGHT);
                }
                else {
                    addx(-getSpeed()-1); // SE MUEVE A LA IZQ
                    setDireccion(LEFT);
                }
            }
        }else{
            setNFrames(3);
            if(zx<px){
                setDireccion(RIGHT);
                if(zy<py){
                    addx(getSpeed()); // SE MUEVE ABAJO A LA DERECHA
                    addy(getSpeed());
                }else{
                    addx(getSpeed()); //SE MUEVE ARRIBA A LA DERECHA
                    addy(-getSpeed());
                }
            }else{
                setDireccion(LEFT);
                if(zy<py){
                    addx(-getSpeed()); // SE MUEVE ABAJO A LA IZQ
                    addy(getSpeed());
                }else{
                    addx(-getSpeed()); //SE MUEVE ARRIBA A LA IZQ
                    addy(-getSpeed());
                }
           }
        }
    }
 }
//**/

/** mover teniendo en cuenta xy
void Zombi::mover(Jugador *player){
    int px=player->getx();
    int py=player->gety();
    int pw=WIDTH_PLAYER;
    int ph=HEIGHT_PLAYER;

    int zx=getx();
    int zy=gety();
    int zw=WIDTH_ZOMBI;
    int zh=HEIGHT_ZOMBI;

    if(getEstado()==WALKING_STATE){
        if(( px==zx || py==zy )){
            if(px=zx){
                if(zy< py) {
                    setNFrames(6);
                    addy(getSpeed()+1); //SE MUEVE HACIA ABAJO
                    setDireccion(DOWN);

                }
                else {
                    setNFrames(3);
                    addy(-getSpeed()-1); // SE MUEVE HACIA ARRIBA
                    setDireccion(UP);
                    setNFrames(4);
                }

            }else{
                setNFrames(3);
                if(zx< px) {
                    addx(getSpeed()+1); //SE MUEVE A LA DERECHA
                    setDireccion(RIGHT);
                }
                else {
                    addx(-getSpeed()-1); // SE MUEVE A LA IZQ
                    setDireccion(LEFT);
                }
            }
        }else{
            setNFrames(3);
            if(zx<px){
                setDireccion(RIGHT);
                if(zy<py){
                    addx(getSpeed()); // SE MUEVE ABAJO A LA DERECHA
                    addy(getSpeed());
                }else{
                    addx(getSpeed()); //SE MUEVE ARRIBA A LA DERECHA
                    addy(-getSpeed());
                }
            }else{
                setDireccion(LEFT);
                if(zy<py){
                    addx(-getSpeed()); // SE MUEVE ABAJO A LA IZQ
                    addy(getSpeed());
                }else{
                    addx(-getSpeed()); //SE MUEVE ARRIBA A LA IZQ
                    addy(-getSpeed());
                }
           }
        }
    }
 }
//**/

///**
int Zombi::mover(Jugador *player){
    int retorno=0;
    if(getEstado()==WALKING_STATE){
        int px=player->getx()+WIDTH_PLAYER/2;
        int py=player->gety()+HEIGHT_PLAYER/2;
        int pw=WIDTH_PLAYER/2;
        int ph=HEIGHT_PLAYER/2;

        int zx=getx()+WIDTH_ZOMBI/2;
        int zy=gety()+HEIGHT_ZOMBI/2;
        int zw=WIDTH_ZOMBI/2;
        int zh=HEIGHT_ZOMBI/2;

        if(( (zx+zw>px) && (zx<px+pw) ) || ( (zy+zh>py) && (zy<py+ph) )){
            if(zx+zw>px && zx<px+pw){
                if(zy< py) {
                    setNFrames(6);
                    addy(getSpeed()+1); //SE MUEVE HACIA ABAJO
                    setDireccion(DOWN);
                }
                else {
                    setNFrames(3);
                    addy(-getSpeed()-1); // SE MUEVE HACIA ARRIBA
                    setDireccion(UP);
                    setNFrames(4);
                }
            }else{
                setNFrames(3);
                if(zx< px) {
                    addx(getSpeed()+1); //SE MUEVE A LA DERECHA
                    setDireccion(RIGHT);
                }
                else {
                    addx(-getSpeed()-1); // SE MUEVE A LA IZQ
                    setDireccion(LEFT);
                }
            }
        }else{
            setNFrames(3);
            if(zx<px){
                setDireccion(RIGHT);
                if(zy<py){
                    addx(getSpeed()); // SE MUEVE ABAJO A LA DERECHA
                    addy(getSpeed());
                }else{
                    addx(getSpeed()); //SE MUEVE ARRIBA A LA DERECHA
                    addy(-getSpeed());
                }
            }else{
                setDireccion(LEFT);
                if(zy<py){
                    addx(-getSpeed()); // SE MUEVE ABAJO A LA IZQ
                    addy(getSpeed());
                }else{
                    addx(-getSpeed()); //SE MUEVE ARRIBA A LA IZQ
                    addy(-getSpeed());
                }
           }
        }
        if(colision(player,1,3)){
            retorno=1;
        }
    }
    return retorno;
 }


void Zombi::crear(){
    setEstado(SPAWNING_STATE);
    setx(rand()%WIDTH);
    sety(rand()%HEIGHT);
    setFrameActual(-1);
    setHP(1);

}

void Zombi::crearAreasColision(){

    areasColision[0].x=9;
    areasColision[0].y=3;
    areasColision[0].w=13;
    areasColision[0].h=46;

    areasColision[1].x=1;
    areasColision[1].y=16;
    areasColision[1].w=12;
    areasColision[1].h=10;

    areasColision[2].x=16;
    areasColision[2].y=14;
    areasColision[2].w=13;
    areasColision[2].h=14;
}
