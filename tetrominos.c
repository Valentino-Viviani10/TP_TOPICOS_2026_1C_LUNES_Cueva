#include "tetrominos.h"
#include "colores.h"
#include <stdio.h>

static const int cantidad = 4;

int elegirColor(int pieza);

int elegirColor(int pieza)
{
    int color;

    switch (pieza)
    {
    case 0:
        color = COL_CIAN;
        break;
    case 1:
        color = COL_AMARILLO;
        break;
    case 2:
        color = COL_PURPURA;
        break;
    case 3:
        color = COL_VERDE;
        break;
    case 4:
        color = COL_ROJO;
        break;
    case 5:
        color = COL_AZUL;
        break;
    case 6:
        color = COL_NARANJA;
        break;
    }

    return color;
}

int piezas[7][4][4][4] = {
    // I
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}
    },
    // O
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    // T
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // L
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // J
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
    },
    // S
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}
    },
    // Z
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}
    }
};

void inicializar_tetrominos_fondo(tTetrominoFondo tetrominos[]) {
    for(int i = 0; i < cantidad; i++) {
        tetrominos[i].activo = 0;
        tetrominos[i].x = 0;
        tetrominos[i].y = 0;
        tetrominos[i].tipo = 0;
        tetrominos[i].rot = 0;
    }
}

void actualizar_tetrominos_fondo(tTetrominoFondo tetrominos[], const int alto, const int ancho, const int limite_izquierdo, const int limite_derecho, tGBT_Temporizador *temp_hacer_caer, tGBT_Temporizador *temp_activar) {
    int ancho_tetromino = 4 * TETROMINO_ESCALA;
    int i;

    // Intentar activar un nuevo tetromino si hay espacio
    if(gbt_temporizador_consumir(temp_activar)) {
        for(i = 0; i < cantidad; i++) {
            if(!tetrominos[i].activo) {
                tetrominos[i].activo = 1;
                tetrominos[i].tipo = rand() % 7;
                tetrominos[i].rot = rand() % 4;
                tetrominos[i].color = elegirColor(tetrominos[i].tipo);
                tetrominos[i].y = -4 * TETROMINO_ESCALA;  // Entra desde arriba
                
                // Alternar entre lados: izquierda (0,1) y derecha (2,3)
                if(i < 2) {
                    int max_x = limite_izquierdo - ancho_tetromino;
                    if(max_x < 0) {
                        max_x = 0;
                    }
                    tetrominos[i].x = rand() % (max_x + 1);
                } else {
                    int min_x = limite_derecho;
                    int max_x = ancho - ancho_tetromino;

                    if(min_x > max_x) {
                        min_x = max_x;
                    }

                    tetrominos[i].x = min_x + (rand() % (max_x - min_x + 1));
                }
                break;  // Solo activar uno a la vez
            }
        }
    }

    // Hacer caer todos los tetrominos activos
    if(gbt_temporizador_consumir(temp_hacer_caer)) {
        for(i = 0; i < cantidad; i++) {
            if(tetrominos[i].activo) {
                tetrominos[i].y += 2;
                
                // Desactivar si sale de pantalla
                if(tetrominos[i].y > alto) {
                    tetrominos[i].activo = 0;
                }
            }
        }
    }
}