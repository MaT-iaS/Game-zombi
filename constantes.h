#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/** TAMA�O DE PANTALLA **/
#define WIDTH 640
#define HEIGHT 480
#define FPS 26


/** JUGADOR **/
#define FRAMES_PLAYER1 3
#define WIDTH_PLAYER 18
#define HEIGHT_PLAYER 33
#define DELAY_ANIMACION_PLAYER1 300
#define SPEED_INICIAL_PLAYER 4

/** ENEMIGOS **/
#define WIDTH_ZOMBI  32
#define HEIGHT_ZOMBI 50
#define SPEED_INICIAL_ZOMBI 2
#define DELAY_ANIMACION_ZOMBI 300
#define DELAY_ANIMACION_SPAWNING_ZOMBI 650
#define DELAY_ANIMACION_DIEING_ZOMBI 500
#define DELAY_CREACION_ZOMBI 3000

/** DIRECCIONES **/
#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3
//diagonales
#define UP_RIGHT 3
#define DOWN_RIGHT 3
#define UP_LEFT 1
#define DOWN_LEFT 1

/** ESTADOS **/
#define STAND_STATE 0
#define WALKING_STATE 1
#define DIEING_STATE 2
#define SPAWNING_STATE 3
#define DEAD_STATE -1

/** DISPAROS **/
#define NORMAL 0
#define LASER 1
#define ACTIVO 1
#define INACTIVO 0
#define DELAY_CREACION_DISPARO 200
#define SPEED_DISPARO 4

/** TAMA�O DE ARRAYS **/
#define MAX_ZOMBIS 7
#define SIZE_RECT_COLISION_ZOMBI 3
#define MAX_DISPAROS 10
#define SIZE_RECT_COLISION_DISPARO 1
#define SIZE_RECT_COLISION_PLAYER 1







#endif // CONSTANTES_H_INCLUDED
