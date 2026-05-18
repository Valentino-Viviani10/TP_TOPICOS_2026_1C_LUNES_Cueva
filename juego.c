#include "juego.h"
#include <stdlib.h>

#define CANT_TETROMINOS 7

static int bolsa_tetrominos[CANT_TETROMINOS];
static int indice_bolsa = CANT_TETROMINOS;
extern int elegirColor(int pieza);


/* Inicializa la bolsa con los 7 tipos de tetrominos. Cada numero representa un tipo de pieza:
    0 = I // 1 = O // 2 = T // 3 = L // 4 = J // 5 = S // 6 = Z
    La idea es que en cada bolsa aparezca una vez cada pieza.
*/
static void cargar_bolsa_tetrominos(void){
    int i;
    for(i = 0; i < CANT_TETROMINOS; i++){
        bolsa_tetrominos[i] = i;
    }
}


/* Intercambia dos posiciones enteras. Se usa durante la mezcla de la bolsa. La funcion recibe punteros para modificar directamente los valores originales del arreglo.
*/
static void intercambiar_enteros(int *a, int *b){
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}


/* Mezcla la bolsa de tetrominos. Recorre la bolsa desde el final hacia el inicio. En cada vuelta elige una posicion aleatoria entre 0 e i, y cambia la pieza actual con esa posicion.
   Esto evita que las piezas salgan siempre en el mismo orden.
*/
static void mezclar_bolsa_tetrominos(void){
    int i;
    int j;

    for(i = CANT_TETROMINOS - 1; i > 0; i--){
        j = rand() % (i + 1);
        intercambiar_enteros(&bolsa_tetrominos[i], &bolsa_tetrominos[j]);
    }
}


/* Devuelve el proximo tipo de tetromino. Si la bolsa ya fue usada completa, se vuelve a cargar con los 7 tipos de piezas, se mezcla nuevamente y se empieza desde la primera posicion.
   Asi no puede haber una tendencia fuerte hacia un tipo de pieza, porque adentro de cada bolsa aparecen todos los tetrominos una sola vez.
*/
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
    pieza->tipo = obtener_tipo_tetromino(); //Antes usábamos rand() % 7, que daba igualdad de probabilidad en cada tirada, pero podía repetir muchas veces una misma pieza. Lamentablemente, con la bolsa estática, la estadística por tipo pierde valor porque tiende a quedar pareja por diseño.
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
    // TODO: Recorrer la matriz 4x4 de la pieza actual.
    // Si hay un bloque (1), copiar el pieza->color en esa
    // coordenada (y, x) de int** tablero.
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
