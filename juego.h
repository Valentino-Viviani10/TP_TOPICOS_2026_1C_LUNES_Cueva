#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "tablero.h"
#include "tetrominos.h"


typedef struct {
    int x;          // Posicion X en el tablero 0 a 9
    int y;          // Posicion Y en el tablero 0 a 19
    int tipo;       // Que pieza es (0 a 6)
    int rotacion;   // Estado (0 a 3)
    int color;      // Color
} tPiezaActiva;

void juego_inicializar_pieza(tPiezaActiva* pieza);

void juego_mover_izquierda(tPiezaActiva* pieza, int** tablero);

void juego_mover_derecha(tPiezaActiva* pieza, int** tablero);

void juego_rotar(tPiezaActiva* pieza, int** tablero);

int juego_caer(tPiezaActiva* pieza, int** tablero);

void juego_fijar_pieza(tPiezaActiva* pieza, int** tablero);

#endif // JUEGO_H_INCLUDED
