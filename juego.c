#include "juego.h"
#include "puntuaciones.h"
#include <stdlib.h>

extern int elegirColor(int pieza);

void juego_inicializar_pieza(tPiezaActiva* pieza) {
    pieza->tipo = rand() % 7;
    pieza->rotacion = 0;
    pieza->color = elegirColor(pieza->tipo);

    pieza->x = COLUMNAS / 2 - 2;
    pieza->y = 0;
}

int posicion_valida(tPiezaActiva* pieza, int** tablero, int nueva_x, int nueva_y) {
    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            if (piezas[pieza->tipo][pieza->rotacion][fila][col]) {
                int pos_tablero_x = nueva_x + col;
                int pos_tablero_y = nueva_y + fila;

                if (pos_tablero_x < 0 || pos_tablero_x >= COLUMNAS) {
                    return 0;
                }
                if (pos_tablero_y >= FILAS) {
                    return 0;
                }
                if (pos_tablero_y >= 0 && tablero[pos_tablero_y][pos_tablero_x] != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void juego_mover_izquierda(tPiezaActiva* pieza, int** tablero) {
    if(posicion_valida(pieza, tablero, pieza->x - 1, pieza->y))
        pieza->x--;
}

void juego_mover_derecha(tPiezaActiva* pieza, int** tablero) {
    if(posicion_valida(pieza, tablero, pieza->x + 1, pieza->y))
        pieza->x++;
}

void juego_rotar(tPiezaActiva* pieza, int** tablero) {
    int rotacion_vieja = pieza->rotacion;

    pieza->rotacion = (pieza->rotacion + 1) % 4;

    if (posicion_valida(pieza, tablero, pieza->x, pieza->y)) {
        return;
    }
    if (posicion_valida(pieza, tablero, pieza->x - 1, pieza->y)) {
        pieza->x--;
        return;
    }
    if (posicion_valida(pieza, tablero, pieza->x + 1, pieza->y)) {
        pieza->x++;
        return;
    }
    if (posicion_valida(pieza, tablero, pieza->x - 2, pieza->y)) {
        pieza->x -= 2;
        return;
    }
    if (posicion_valida(pieza, tablero, pieza->x + 2, pieza->y)) {
        pieza->x += 2;
        return;
    }

    pieza->rotacion = rotacion_vieja;
}

int juego_caer(tPiezaActiva* pieza, int** tablero) {
    if (posicion_valida(pieza, tablero, pieza->x, pieza->y + 1)){
        pieza->y++;
        return 1;
    }
    return 0;
}

void juego_fijar_pieza(tPiezaActiva* pieza, int** tablero) {
    int fila;
    int col;

    for (fila = 0; fila < 4; fila++) {
        for (col = 0; col < 4; col++) {
            if (piezas[pieza->tipo][pieza->rotacion][fila][col]) {
                int pos_tablero_x = pieza->x + col;
                int pos_tablero_y = pieza->y + fila;

                if (pos_tablero_y >= 0 && pos_tablero_y < FILAS &&
                    pos_tablero_x >= 0 && pos_tablero_x < COLUMNAS) {
                    tablero[pos_tablero_y][pos_tablero_x] = pieza->color;
                }
            }
        }
    }
}

int juego_puede_iniciar_pieza(tPiezaActiva* pieza, int** tablero) {
    return posicion_valida(pieza, tablero, pieza->x, pieza->y);
}

void fijar_y_nueva_pieza(tPiezaActiva *pieza, int *puntaje, int **tablero, int *casillasManuales, int *juego_terminado, int *piezas_colocadas, int *nivel_velocidad, double *duracion_caida, tGBT_Temporizador **temp_juego_caida) {
    juego_fijar_pieza(pieza, tablero);

    int filasElim = borrar_lineas(tablero, FILAS, COLUMNAS);
    sumar_puntos(filasElim, *casillasManuales, puntaje, *nivel_velocidad);

    *casillasManuales = 0;
    (*piezas_colocadas)++;

    // Cada 10 piezas, acelerar un 3%
    if (*piezas_colocadas % 10 == 0) {
        (*nivel_velocidad)++;
        *duracion_caida *= 0.97;
        gbt_temporizador_destruir(*temp_juego_caida);
        *temp_juego_caida = gbt_temporizador_crear(*duracion_caida);
    }

    juego_inicializar_pieza(pieza);

    if(!juego_puede_iniciar_pieza(pieza, tablero)){
        *juego_terminado = 1;
    }
}