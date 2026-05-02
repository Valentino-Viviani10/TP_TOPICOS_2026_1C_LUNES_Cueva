#include "juego.h"
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
    // TODO: Recorrer la matriz 4x4 de la pieza actual.
    // Si hay un bloque (1), copiar el pieza->color en esa
    // coordenada (y, x) de int** tablero.




}
