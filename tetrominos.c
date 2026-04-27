#include "tetrominos.h"
#include "colores.h"
#include <stdio.h>

static tTetrominoFondo tetrominos[3];

tForma formas[7] = {
    { {{0,0},{1,0},{2,0},{3,0}}, COL_CIAN}, // I (Línea)
    { {{0,0},{1,0},{0,1},{1,1}}, COL_AMARILLO}, // O (Cuadrado)
    { {{0,0},{1,0},{2,0},{1,1}}, COL_PURPURA}, // T (La T)
    { {{0,0},{1,0},{1,-1},{2,-1}}, COL_VERDE}, // S (Serpiente)
    { {{0,0},{1,0},{1,1},{2,1}}, COL_ROJO}, // Z (Serpiente inversa)
    { {{0,0},{1,0},{2,0},{0,1}}, COL_AZUL}, // J (Gancho)
    { {{0,0},{1,0},{2,0},{2,1}}, COL_NARANJA} // L(Gancho inverso)
};

void inicializar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int cantidad) {
    for(int i = 0; i < cantidad; i++) {
        tetrominos[i].activo = 0;
        tetrominos[i].x = 0;
        tetrominos[i].y = 0;
        tetrominos[i].tipo = 0;
    }
}

void actualizar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int cantidad, const int alto, const int ancho) {
    int i = 0;

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(0.05);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los tetrominos del fondo: %s\n", gbt_obtener_log());
        return -1;
    }

    tetrominos[i].x = rand() % ancho;

    while(i < cantidad && tetrominos[i].activo) {
        if (gbt_temporizador_consumir(temporizador)) {
            tetrominos[i].y += 2;
        }

        if(tetrominos[i].y > alto) {
            tetrominos[i].y = 0;
        }

        i++;
    }
}