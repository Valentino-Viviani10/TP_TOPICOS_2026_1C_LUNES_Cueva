#include "tablero.h"
#include "juego.h"
#include <stdio.h>
#include <string.h>
int filas = 22;
int columnas = 10;

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

void eliminar_fila_y_bajar(int** tablero, int fila_a_borrar, int columnas) {
    int* fila_reciclada = tablero[fila_a_borrar];

    for (int i = fila_a_borrar; i > 0; i--) {
        tablero[i] = tablero[i - 1];
    }

    tablero[0] = fila_reciclada;

    for (int j = 0; j < columnas; j++) {
        tablero[0][j] = 0;
    }
}

void destruir_tablero(int** tablero, int filas) {
    int** ult = tablero + filas;

    for (int** i = tablero; i < ult; i++) {
        free(*i);
    }
    free(tablero);
}


int borrar_lineas(int** tablero, int filas, int columnas) {
    int fila = 0;
    int columna = 0;
    int llena = 0;
    int fil_eliminadas = 0;

    while (fila < filas) {
        while (columna < columnas && tablero[fila][columna]) {
            llena++;
            columna++;
        }
        if (llena == columnas) {
            eliminar_fila_y_bajar(tablero, fila, columnas);
            fil_eliminadas++;
        }
        columna = 0;
        fila++;
        llena = 0;
    }
    return fil_eliminadas;
}

void guardar_partida(int** tablero, int filas, int columnas, const tPartidaGuardada* datos, const char* archivo) {
    FILE* f = fopen(archivo, "wb");
    if(!f) return;

    fwrite(&filas, sizeof(int), 1, f);
    fwrite(&columnas, sizeof(int), 1, f);

    for(int i = 0; i < filas; i++) {
        fwrite(tablero[i], sizeof(int), columnas, f);
    }

    fwrite(datos, sizeof(tPartidaGuardada), 1, f);

    fclose(f);
}

int cargar_partida(int*** tablero_ptr, int* filas_leidas, int* columnas_leidas, tPartidaGuardada* datos, const char* archivo) {
    FILE* f = fopen(archivo, "rb");
    if(!f) return 0;

    int f_leidas, c_leidas;
    if(fread(&f_leidas, sizeof(int), 1, f) != 1 || fread(&c_leidas, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    int** nuevo_tablero = crear_tablero(f_leidas, c_leidas, sizeof(int));
    if (!nuevo_tablero) {
        fclose(f);
        return 0;
    }

    for(int i = 0; i < f_leidas; i++) {
        if(fread(nuevo_tablero[i], sizeof(int), c_leidas, f) != (size_t)c_leidas) {
            destruir_tablero(nuevo_tablero, f_leidas);
            fclose(f);
            return 0;
        }
    }

    if(fread(datos, sizeof(tPartidaGuardada), 1, f) != 1) {
        destruir_tablero(nuevo_tablero, f_leidas);
        fclose(f);
        return 0;
    }

    fclose(f);

    *tablero_ptr = nuevo_tablero;
    *filas_leidas = f_leidas;
    *columnas_leidas = c_leidas;

    return 1;
}
