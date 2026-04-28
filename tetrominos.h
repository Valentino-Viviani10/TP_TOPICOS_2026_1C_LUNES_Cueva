#ifndef TETROMINOS_H_INCLUDED
#define TETROMINOS_H_INCLUDED

#include "GBT/gbt.h"

typedef struct {
    int x;
    int y;
    int tipo;
    int rot;
    int activo;
    int color;
} tTetrominoFondo;

typedef struct {
    int dx;
    int dy;
} tBloque;

#define TETROMINO_ESCALA 3

void inicializar_tetrominos_fondo(tTetrominoFondo tetrominos[]);

void actualizar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int alto, const int ancho, const int limite_izquierdo, const int limite_derecho, tGBT_Temporizador *temp_hacer_caer, tGBT_Temporizador *temp_activar);

extern int piezas[7][4][4][4];

#endif // TETROMINOS_H_INCLUDED
