#include "tablero.h"
#include <stdio.h>
int filas = 20;
int columnas = 10;

int** crear_tablero(int filas, int columnas, size_t tamElem) {
    int** tablero = (int**)malloc(filas * sizeof(int*));

    if(!tablero)
    {
        return NULL;
    }

    for (int i = 0; i < filas; i++) {
        tablero[i] = (int*)calloc(columnas, tamElem);

        if(!tablero[i]) {
            // Limpieza en caso de error
            for (int j = 0; j < i; j++) {
                free(tablero[j]);
            }
            free(tablero);
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

/*void destruir_tablero(int** tablero,int filas) {
    int** ult = tablero + filas;

    for (int** i = tablero; i < ult; i++) {
        free(*i);
    }
    free(tablero);
}
*/
void destruir_tablero(int** tablero, int filas) {
    for (int i = 0; i < filas; i++) {
        free(tablero[i]);
    }
    free(tablero);
}


int borrar_lineas(int** tablero, int filas, int columnas) {
    int fila = 0;
    int columna = 0;
    int llena = 0;
    int fil_eliminadas = 0;

    while(fila < filas) {
        while(columna < columnas && tablero[fila][columna]) {
            llena++;
            columna++;
        }
        if(llena == columnas) {
            // Fila completa encontrada
            // Guardar el puntero actual
            int* fila_reciclada = tablero[fila];
            // Correr los punteros (no los datos)
            for (int i = fila; i > 0; i--) {
                tablero[i] = tablero[i - 1];
            }
            // Poner la fila limpia al inicio
            tablero[0] = fila_reciclada;

            // Limpiar la fila
            for (int j = 0; j < columnas; j++) {
                tablero[0][j] = 0;
            }
            fil_eliminadas++;
        }
        columna = 0;
        fila++;
        llena = 0;
    }
    return fil_eliminadas;
}

void guardar_tablero(int** tablero, int filas, int columnas, const char* archivo) {
    FILE* f = fopen(archivo, "wb");
    if(!f) return;

    // Opcional: escribir las dimensiones para luego poder cargar el tablero correcto
    fwrite(&filas, sizeof(int), 1, f);
    fwrite(&columnas, sizeof(int), 1, f);

    // Escribir fila por fila
    for(int i = 0; i < filas; i++) {
        fwrite(tablero[i], sizeof(int), columnas, f);
    }

    fclose(f);
}

int cargar_tablero(int** tablero, int filas_esperadas, int columnas_esperadas, const char* archivo) {
    FILE* f = fopen(archivo, "rb");
    if(!f) return 0; // No existe o no se puede leer

    int f_leidas, c_leidas;
    if(fread(&f_leidas, sizeof(int), 1, f) != 1 || fread(&c_leidas, sizeof(int), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    if(f_leidas != filas_esperadas || c_leidas != columnas_esperadas) {
        // Dimensiones distintas, se ignora el archivo
        fclose(f);
        return 0;
    }

    for(int i = 0; i < filas_esperadas; i++) {
        if(fread(tablero[i], sizeof(int), columnas_esperadas, f) != (size_t)columnas_esperadas) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1; // Éxito
}
