#ifndef TETROMINOS_H_INCLUDED
#define TETROMINOS_H_INCLUDED

#include "GBT/gbt.h"

typedef struct {
    int x;
    int y;
    int tipo;
    int activo;
} tTetrominoFondo;

typedef struct {
    int dx;
    int dy;
} tBloque;

typedef struct {
    tBloque bloques[4];
    uint8_t color;
} tForma;

void inicializar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int cantidad);

void actualizar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int cantidad, const int alto, const int ancho);

#endif // TETROMINOS_H_INCLUDED
