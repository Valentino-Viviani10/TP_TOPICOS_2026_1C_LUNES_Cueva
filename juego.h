#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "tablero.h"
#include "tetrominos.h"

/*<<<<<<< HEAD
=======
void juego_inicializar(int ancho, int alto);
>>>>>>> 8bb2de69627d242a00f91586679acdb38cfb856f*/

typedef struct {
    int x;          // Posicion X en el tablero 0 a 9
    int y;          // Posicion Y en el tablero 0 a 19
    int tipo;       // Que pieza es (0 a 6)
    int rotacion;   // Estado (0 a 3)
    int color;      // Color
} tPiezaActiva;

void juego_inicializar_pieza(tPiezaActiva* pieza);

//<<<<<<< HEAD
void juego_mover_izquierda(tPiezaActiva* pieza, int** tablero);

void juego_mover_derecha(tPiezaActiva* pieza, int** tablero);

void juego_rotar(tPiezaActiva* pieza, int** tablero);

int juego_caer(tPiezaActiva* pieza, int** tablero);

void juego_fijar_pieza(tPiezaActiva* pieza, int** tablero);
/*=======
int juego_obtener_marco_x();
int juego_obtener_marco_y();

>>>>>>> 8bb2de69627d242a00f91586679acdb38cfb856f*/

#endif // JUEGO_H_INCLUDED
