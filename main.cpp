
#include <SDL.h>
#include <CSprite.h>
#include "constantes.h"
#include "jugador.h"
#include "zombi.h"
#include "disparo.h"



/**  DECLARACION DE VARIABLES  **/
//variables de SDL
SDL_Surface *screen=NULL;
SDL_Surface *spriteSheetZombi=NULL;
SDL_Surface *spriteSheetPlayer1=NULL;
SDL_Surface *spriteSheetDisparo=NULL;
SDL_Surface *suelo;
SDL_Rect rect;
SDL_Rect rectZombis[SIZE_RECT_COLISION_ZOMBI];
SDL_Rect rectPlayer[SIZE_RECT_COLISION_PLAYER];
SDL_Rect rectdisparo[SIZE_RECT_COLISION_DISPARO];
Uint8 *teclas;
SDL_Event event;

//Variables del Juego
int done=0;
int timeCreacionZombi;
int timeCreacionDisparo;
//char map[MAX_MAP+1]; //array para tiles del mapa
//FILE *f;

//Sptites
Jugador player;
Zombi zombis[MAX_ZOMBIS];
Disparo disparos[MAX_DISPAROS];

/**  PROTOTIPO DE FUNCIONES  **/
void initSDL();
void initVariables();
void loadSprites();
void initAreasColision();
void dibujarPantalla();
void dibujarMapa();
void dibujarEnemigos();
void drawDisparos();
void procesarEntrada();
void actualizarObjetos();
int moverEnemigos();
void moverDisparos();
void crearDisparo();
void crearEnemigo();
void matarZombis();

int main ( int argc, char** argv )
{

    initSDL();
    initVariables();
    loadSprites();

    while (!done){
        dibujarPantalla();
        procesarEntrada();
        actualizarObjetos();
    } // end main loop

    return 0;
}


void initSDL(){
       // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO |SDL_INIT_AUDIO) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    atexit(SDL_AudioQuit);

    // create a new window
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
    }

}

void initVariables(){
    timeCreacionZombi=SDL_GetTicks();
    timeCreacionDisparo=SDL_GetTicks();

    initAreasColision();
}

void initAreasColision(){

//    //jugador

//    //disparo
}
void loadSprites(){
    spriteSheetPlayer1=SDL_LoadBMP("sprites/sasuske.bmp");
    player.loadSpriteSheet(spriteSheetPlayer1,255,0,255);


    spriteSheetZombi=SDL_LoadBMP("sprites/zombi.bmp");
    for(int i=0;i<MAX_ZOMBIS;i++){
        zombis[i].loadSpriteSheet(spriteSheetZombi,255,0,255);
    }

    suelo=SDL_LoadBMP("sprites/suelo.bmp");
    suelo=SDL_DisplayFormat(suelo);


    spriteSheetDisparo=SDL_LoadBMP("sprites/bala.bmp");
    for(int i=0;i<MAX_DISPAROS;i++){
        disparos[i].loadSpriteSheet(spriteSheetDisparo,255,0,0);
    }

}

void dibujarPantalla(){
    SDL_Delay(1000/FPS);

    dibujarMapa();
    player.animar(screen);
    dibujarEnemigos();
    drawDisparos();
    SDL_Flip(screen);
}

void dibujarMapa(){
    rect.x=0;
    rect.w=WIDTH;
    rect.h=HEIGHT;
    SDL_BlitSurface(suelo,NULL,screen,&rect);
}

void drawDisparos(){
    for(int i=0; i<MAX_DISPAROS; i++){
        if(disparos[i].getEstado()==ACTIVO){
            disparos[i].animar(screen);
        }
    }
}

void dibujarEnemigos(){
    for(int i=0;i<MAX_ZOMBIS;i++){
        if(zombis[i].getEstado()!=DEAD_STATE){
            zombis[i].animar(screen);
        }
    }
}

void procesarEntrada(){


    teclas=SDL_GetKeyState(NULL);
    player.setEstado(STAND_STATE);

    if(teclas[SDLK_w]&&teclas[SDLK_d]){     //MUEVE ARRIBA A LA DERECHA
        player.setEstado(WALKING_STATE);
        player.setDireccion(UP_RIGHT);
        player.addy(-player.getSpeed());
        player.addx(player.getSpeed());
    }else{
        if(teclas[SDLK_w]&&teclas[SDLK_a]){     //MUEVE ARRIBA A LA IZQ
            player.setEstado(WALKING_STATE);
            player.setDireccion(UP_LEFT);
            player.addy(-player.getSpeed());
            player.addx(-player.getSpeed());
        }else{
            if(teclas[SDLK_s]&&teclas[SDLK_d]) {        //MUEVE ABAJO A LA DERECHA
                player.setEstado(WALKING_STATE);
                player.setDireccion(DOWN_RIGHT);
                player.addy(player.getSpeed());
                player.addx(player.getSpeed());
            }else{
                if(teclas[SDLK_s]&&teclas[SDLK_a]) {    //MUEVE  ABAJO A LA IZQ
                    player.setEstado(WALKING_STATE);
                    player.setDireccion(DOWN_LEFT);
                    player.addy(player.getSpeed());
                    player.addx(-player.getSpeed());
                }else{
                    if(teclas[SDLK_w]) {                    //MUEVE ARRIBA
                        player.setEstado(WALKING_STATE);
                        player.setDireccion(UP);
                        player.addy(-player.getSpeed());
                    }
                    if(teclas[SDLK_s]) {                    //MUEVE MUEVE ABAJO
                        player.setEstado(WALKING_STATE);
                        player.setDireccion(DOWN);
                        player.addy(player.getSpeed());
                    }
                    if(teclas[SDLK_a]) {                    //MUEVE A LA IZQ
                        player.setEstado(WALKING_STATE);
                        player.setDireccion(LEFT);
                        player.addx(-player.getSpeed());
                    }
                    if(teclas[SDLK_d]) {                    //MUEVE A LA DERECHA
                        player.setEstado(WALKING_STATE);
                        player.setDireccion(RIGHT);
                        player.addx(player.getSpeed());
                    }
                }
            }
        }
    }


    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            done=1;
        }
        if(event.type==SDL_KEYDOWN){
            if(event.key.keysym.sym==SDLK_SPACE){crearDisparo();}
            if(event.key.keysym.sym==SDLK_1) {matarZombis();}
            if(event.key.keysym.sym==SDLK_2) {player.setFrameActual(1);}
            if(event.key.keysym.sym==SDLK_3) {player.setFrameActual(2);}
        }
    }
}

void actualizarObjetos(){
    moverDisparos();
    crearEnemigo();
    moverEnemigos();
//    comprobarColisiones();
}

void moverDisparos(){
    for(int i=0; i<MAX_DISPAROS; i++){
        disparos[i].mover();
    }
}

int moverEnemigos(){
    for(int i=0;i<MAX_ZOMBIS;i++){
        if(zombis[i].mover(&player)){
            done=1;
            return 1;
        }
    }
    return 0;
}

void crearDisparo(){
    int creado=0;
    if(SDL_GetTicks()-timeCreacionDisparo>=DELAY_CREACION_DISPARO){
        for(int i=0;i<MAX_DISPAROS && !creado ;i++){
            if (disparos[i].getEstado()==INACTIVO){
                disparos[i].crear(&player);
                creado=1;
            }
        }
        timeCreacionDisparo=SDL_GetTicks();
    }
}

void crearEnemigo(){
    int creado=0;
    if(SDL_GetTicks()-timeCreacionZombi>DELAY_CREACION_ZOMBI){
        for(int i=0;i<MAX_ZOMBIS && !creado;i++){
            if(zombis[i].getEstado()==DEAD_STATE){
                zombis[i].crear();
                creado=1;
            }
        }
        timeCreacionZombi=SDL_GetTicks();
    }
}

void matarZombis(){
    for(int i=0;i<MAX_ZOMBIS;i++){
        if(zombis[i].getEstado()==WALKING_STATE){
            zombis[i].setEstado(DIEING_STATE);
            zombis[i].setFrameActual(0);
        }
    }

}
