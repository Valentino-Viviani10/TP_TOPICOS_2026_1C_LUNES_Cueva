#include "tablero.h"

int** crear_tablero(int filas, int columnas, size_t tamElem) {
    int** tablero = (int**)malloc(filas * sizeof(int*));

    if(!tablero)
    {
        return NULL;
    }

    int** ult = tablero + filas;

    for (int** i = tablero; i < ult; i++) {
        *i = calloc(columnas, tamElem);

        if(!*i)
        {
            destruir_tablero(tablero, i - tablero);
            return NULL;
        }
    }
    return tablero;
}

void eliminar_fila_y_bajar(int** tablero, int fila_a_borrar,int columnas) {
    int* fila_reciclada = tablero[fila_a_borrar];

    for (int i = fila_a_borrar; i > 0; i--) {
        tablero[i] = tablero[i - 1];
    }

    tablero[0] = fila_reciclada;

    for (int j = 0; j < columnas; j++) {
        tablero[0][j] = 0;
    }
}

void destruir_tablero(int** tablero,int filas) {
    int** ult = tablero + filas;

    for (int** i = tablero; i < ult; i++) {
        free(*i);
    }
    free(tablero);
}
