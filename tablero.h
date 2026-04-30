#ifndef TABLERO_H
#define TABLERO_H

#include <stdlib.h>

#define FILAS 20
#define COLUMNAS 10

int** crear_tablero(int filas, int columnas, size_t tamElem);

void destruir_tablero(int** tablero, int filas);

void eliminar_fila_y_bajar(int** tablero, int fila_a_borrar,int columnas);

#endif
