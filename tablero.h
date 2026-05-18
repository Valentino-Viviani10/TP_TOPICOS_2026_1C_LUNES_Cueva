#ifndef TABLERO_H
#define TABLERO_H

#include <stdlib.h>

extern int filas;
extern int columnas;

int** crear_tablero(int filas, int columnas, size_t tamElem);

void destruir_tablero(int** tablero, int filas);

void eliminar_fila_y_bajar(int** tablero, int fila_a_borrar,int columnas);

int borrar_lineas(int** tablero, int filas, int columnas);

void guardar_tablero(int** tablero, int filas, int columnas, const char* archivo);

int cargar_tablero(int** tablero, int filas, int columnas, const char* archivo);

#endif

