#include "juego.h"
#include "puntuaciones.h"
#include <stdlib.h>

#define MAX_TETROMINOS 11

static int bolsa_tetrominos[MAX_TETROMINOS];
static int indice_bolsa = MAX_TETROMINOS;
extern int elegirColor(int pieza);

static int obtener_cant_tetrominos(void) {
    return modo_deluxe ? TOTAL_PIEZAS_DELUXE : TOTAL_PIEZAS_NORMAL;
}

static void cargar_bolsa_tetrominos(void){
    int i;
    int cant = obtener_cant_tetrominos();
    for(i = 0; i < cant; i++){
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
    int cant = obtener_cant_tetrominos();
    for(i = cant - 1; i > 0; i--){
        j = rand() % (i + 1);
        intercambiar_enteros(&bolsa_tetrominos[i], &bolsa_tetrominos[j]);
    }
}

static int obtener_tipo_tetromino(void){
    int tipo;
    int cant = obtener_cant_tetrominos();
    if(indice_bolsa >= cant){
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

                if (modo_deluxe) {
                    pos_tablero_x = ((pos_tablero_x % columnas) + columnas) % columnas;
                } else {
                    if (pos_tablero_x < 0 || pos_tablero_x >= columnas) {
                        return 0;
                    }
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

void juego_rotar_izquierda(tPiezaActiva* pieza, int** tablero) {
    int rotacion_vieja = pieza->rotacion;

    // Retrocede una rotacion. Si esta en 0, pasa a 3.
    pieza->rotacion = (pieza->rotacion + 3) % 4;

    // Si la pieza entra en la misma posicion, queda rotada.
    if (posicion_valida(pieza, tablero, pieza->x, pieza->y)) {
        return;
    }

    // Si no entra, se intenta correr un lugar hacia la izquierda.
    if (posicion_valida(pieza, tablero, pieza->x - 1, pieza->y)) {
        pieza->x--;
        return;
    }

    // Si no entra, se intenta correr un lugar hacia la derecha.
    if (posicion_valida(pieza, tablero, pieza->x + 1, pieza->y)) {
        pieza->x++;
        return;
    }

    // Segundo intento hacia la izquierda, igual que en la rotacion derecha.
    if (posicion_valida(pieza, tablero, pieza->x - 2, pieza->y)) {
        pieza->x -= 2;
        return;
    }

    // Segundo intento hacia la derecha, igual que en la rotacion derecha.
    if (posicion_valida(pieza, tablero, pieza->x + 2, pieza->y)) {
        pieza->x += 2;
        return;
    }

    // Si no se pudo rotar, se vuelve a la rotacion anterior.
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
                
                if (modo_deluxe) {
                    pos_tablero_x = ((pos_tablero_x % columnas) + columnas) % columnas;
                }

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

void juego_obtener_bolsa(int* bolsa_destino, int* indice_destino) {
    for(int i = 0; i < MAX_TETROMINOS; i++) {
        bolsa_destino[i] = bolsa_tetrominos[i];
    }
    *indice_destino = indice_bolsa;
}

void juego_cargar_bolsa(const int* bolsa_origen, int indice_origen) {
    for(int i = 0; i < MAX_TETROMINOS; i++) {
        bolsa_tetrominos[i] = bolsa_origen[i];
    }
    indice_bolsa = indice_origen;
}
