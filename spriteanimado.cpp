#include "spriteanimado.h"
#include <SDL.h>

SpriteAnimado::SpriteAnimado(){
    setTimeAnimacion(SDL_GetTicks());
}

void SpriteAnimado::loadSpriteSheet(SDL_Surface *sheet,int r,int g,int b){
    spriteSheet=sheet;
    SDL_SetColorKey(spriteSheet,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(spriteSheet->format,r,g,b));
    spriteSheet=SDL_DisplayFormat(spriteSheet);
}

void SpriteAnimado::unloadSpriteSheet(){
    SDL_FreeSurface(spriteSheet);
}

void SpriteAnimado::animar(SDL_Surface *screen){
    SDL_Rect destino;
    destino.x=getx();
    destino.y=gety();
    destino.w=spriteSheet->w;
    destino.h=spriteSheet->h;

    SDL_BlitSurface(spriteSheet,NULL,screen,&destino);
}

int SpriteAnimado::colision(SpriteAnimado *sprite,int sizeArray1,int sizeArray2){ //size1=tamaño de array del objeto pasado como parametro
    int colision=0;                                                                //size2=tamaño de array del objeto q llama el metodo

//    int sizeArray1=sizeof(areasColision)/sizeof(SDL_Rect);
//    int sizeArray2=sizeof(sprite->areasColision)/sizeof(SDL_Rect);

    for(int i=0;i<sizeArray2 && !colision ;i++){
        for(int j=0; j<sizeArray1 && !colision ;j++){

            int x1=areasColision[i].x+getx();
            int y1=areasColision[i].y+gety();
            int w1=areasColision[i].w;
            int h1=areasColision[i].h;

            int x2=sprite->areasColision[j].x+sprite->getx();
            int y2=sprite->areasColision[j].y+sprite->gety();
            int w2=sprite->areasColision[j].w;
            int h2=sprite->areasColision[j].h;
            if(x1+w1>x2 && x1<x2+w2 && y1+h1>y2 && y1<y2+h2){
                colision=1;
            }
        }
    }
    return colision;
}


