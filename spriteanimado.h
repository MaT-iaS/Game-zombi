#ifndef SPRITEANIMADO_H
#define SPRITEANIMADO_H

#include <SDL.h>

class SpriteAnimado{
    public:
        SDL_Surface* spriteSheet;
        SDL_Rect *areasColision;
        SpriteAnimado();
        void animar(SDL_Surface *screen);
        void loadSpriteSheet(SDL_Surface *sheet,int r,int g,int b);
        void unloadSpriteSheet();
        int colision(SpriteAnimado *sprite,int size1,int size2);


        /** getters and setters **/
        int getTimeAnimacion(){return timeAnimacion;}
        void setTimeAnimacion(int t){timeAnimacion=t;}
        int getx() {return x;}
        int gety() {return y;}
        void setx(int posx) {x=posx;}
        void sety(int posy) {y=posy;}
        void addx(int c) {x+=c;}
        void addy(int c) {y+=c;}
        int getNFrames() {return nframes;}
        void setNFrames(int n){nframes=n-1;}
        int getFrameActual(){return frameActual;}
        void setFrameActual(int f){frameActual=f;}

    private:
        int x,y;
        int frameActual;
        int nframes;
        int timeAnimacion;
};

#endif // SPRITEANIMADO_H
