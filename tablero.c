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

int borrar_lineas(int** tablero, int filas, int columnas){
    int fila = 0;
    int columna = 0;
    int llena = 0;
    int fil_eliminadas = 0;

    while(fila < filas){
        while(columna < columnas && tablero[fila][columna]){
            llena++;
            columna++;
        }
        if(llena == columnas){
            eliminar_fila_y_bajar(tablero, fila, columnas);
            fil_eliminadas++;
        }
        columna = 0;
        fila++;
        llena = 0;
    }

    return fil_eliminadas;
}





