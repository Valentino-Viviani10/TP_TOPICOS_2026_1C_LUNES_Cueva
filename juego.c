#include "juego.h"
#include "puntuaciones.h"
#include <stdlib.h>

#define CANT_TETROMINOS 7

static int bolsa_tetrominos[CANT_TETROMINOS];
static int indice_bolsa = CANT_TETROMINOS;
extern int elegirColor(int pieza);

static void cargar_bolsa_tetrominos(void){
    int i;
    for(i = 0; i < CANT_TETROMINOS; i++){
        bolsa_tetrominos[i] = i;
    }
}

static void intercambiar_enteros(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

static void mezclar_bolsa_tetrominos(void){
    int i;
    int j;
    for(i = CANT_TETROMINOS - 1; i > 0; i--){
        j = rand() % (i + 1);
        intercambiar_enteros(&bolsa_tetrominos[i], &bolsa_tetrominos[j]);
    }
}

static int obtener_tipo_tetromino(void){
    int tipo;
    if(indice_bolsa >= CANT_TETROMINOS){
        cargar_bolsa_tetrominos();
        mezclar_bolsa_tetrominos();
        indice_bolsa = 0;
    }
    tipo = bolsa_tetrominos[indice_bolsa];
    indice_bolsa++;
    return tipo;
}

void juego_inicializar_pieza(tPiezaActiva* pieza) {
    pieza->tipo = obtener_tipo_tetromino();
    pieza->rotacion = 0;
    pieza->color = elegirColor(pieza->tipo);

    pieza->x = columnas / 2 - 2;
    pieza->y = 0;
}

int posicion_valida(tPiezaActiva* pieza, int** tablero, int nueva_x, int nueva_y) {
    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {
            if (piezas[pieza->tipo][pieza->rotacion][fila][col]) {
                int pos_tablero_x = nueva_x + col;
                int pos_tablero_y = nueva_y + fila;

                if (pos_tablero_x < 0 || pos_tablero_x >= columnas) {
                    return 0;
                }
                if (pos_tablero_y >= filas) {
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

                if (pos_tablero_y >= 0 && pos_tablero_y < filas &&
                    pos_tablero_x >= 0 && pos_tablero_x < columnas) {
                    tablero[pos_tablero_y][pos_tablero_x] = pieza->color;
                }
            }
        }
    }
}

int juego_puede_iniciar_pieza(tPiezaActiva* pieza, int** tablero) {
    return posicion_valida(pieza, tablero, pieza->x, pieza->y);
}

