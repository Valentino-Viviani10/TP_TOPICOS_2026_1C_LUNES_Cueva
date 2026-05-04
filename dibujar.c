#include "dibujar.h"
#include "juego.h"
#include "colores.h"
#include <string.h>
#include <stdio.h>
#include "tablero.h"

int calcular_x_centrada(const char *palabra, const int ancho) {
    return (ancho - strlen(palabra) * 8) / 2;
}

void dibujar_linea_horizontal(const int x_ini, const int x_fin, const int y) {
    for(int x = x_ini; x <= x_fin; x++) {
        gbt_dibujar_pixel(x, y, COL_MAG_BRILL);
    }
}


void dibujar_texto_8x8(const char *texto, uint16_t x, uint16_t y, uint8_t color) {
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        for (int fila = 0; fila < 8; fila++) {
            for (int col = 0; col < 8; col++) {
                if (font8x8_basic[(int)c][fila] & (1 << col)) {
                    gbt_dibujar_pixel(x + i*8 + col, y + fila, color);
                }
            }
        }
    }
}

void dibujar_menu(const int opcionSeleccionada, const int ancho, const int alto, uint8_t colorSeleccionado) {
    int y;

    const char *opciones[2] = {"JUGAR", "INSTRUCCIONES"};

    const char titulo[] = "TETRIS";

    int xTitulo = calcular_x_centrada(titulo, ancho);
    int xJugar = calcular_x_centrada(opciones[0], ancho);
    int xInstrucciones = calcular_x_centrada(opciones[1], ancho);

    y = 20;

    dibujar_texto_8x8(titulo, xTitulo, y, COL_VERDE_BRILL);

    y = alto / 2;

    uint8_t colorJugar = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorInstrucciones = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_8x8(opciones[0], xJugar, y, colorJugar);
    dibujar_texto_8x8(opciones[1], xInstrucciones, y + 20, colorInstrucciones);

}

void dibujar_fondo(const int alto, const int ancho) {
    int x, y;

    for(y = 0; y < alto; y++) {
        for(x = 0; x < ancho; x++) {
            if((x + y) % 2 == 0) {
                gbt_dibujar_pixel(x, y, COL_NEGRO);
            } else {
                gbt_dibujar_pixel(x, y, COL_GRIS_OSC);
            }
        }
    }
}

void dibujar_borde(const int alto, const int ancho, const int iniX, const int iniY) {
    int x, y;

    for(int g = 0; g < GROSOR_BORDE; g++){
        for(x = iniX; x < ancho; x++){
            gbt_dibujar_pixel(x, iniY + g, COL_AZUL);          // superior
            gbt_dibujar_pixel(x, alto - 1 - g, COL_AZUL); // inferior
        }
        for(y = iniY; y < alto; y++){
            gbt_dibujar_pixel(iniX + g, y, COL_AZUL);          // izquierdo
            gbt_dibujar_pixel(ancho - 1 - g, y, COL_AZUL); // derecho
        }
    }
}

void dibujar_tetromino(tTetrominoFondo tetromino, const int pantalla, const int rot, const int alto, const int ancho)
{
    int pi, pj;
    int escala = TETROMINO_ESCALA;

    // Dibujar la pieza en su posición actual (escalada)
    for (pi = 0; pi < 4; pi++) {
        for (pj = 0; pj < 4; pj++) {
            if (piezas[tetromino.tipo][rot][pi][pj]) {
                int px = tetromino.x + pj * escala;
                int py = tetromino.y + pi * escala;

                // Dibujar bloque 3x3
                for (int dy = 0; dy < escala; dy++) {
                    for (int dx = 0; dx < escala; dx++) {
                        int final_x = px + dx;
                        int final_y = py + dy;

                        // Verificar que está dentro de pantalla
                        if (final_x >= 0 && final_x < ancho && final_y >= 0 && final_y < alto) {
                            gbt_dibujar_pixel(final_x, final_y, tetromino.color);
                        }
                    }
                }
            }
        }
    }
}

int calcular_lado_bloque_juego(int alto)
{
    int lado_bloque;

    lado_bloque = alto / 24;

    if(lado_bloque < 6){
        lado_bloque = 6;
    }

    if(lado_bloque > 20){
        lado_bloque = 20;
    }

    return lado_bloque;
}

void dibujar_bloque_tablero(int x, int y, int color, int lado_bloque)
{
    int dx;
    int dy;

    for(dy = 0; dy < lado_bloque - 1; dy++){
        for(dx = 0; dx < lado_bloque - 1; dx++){
            gbt_dibujar_pixel(x + dx, y + dy, color);
        }
    }
}

void dibujar_marco_tablero(int marco_x, int marco_y, int lado_bloque)
{
    int x;
    int y;
    int ancho_tablero;
    int alto_tablero;

    ancho_tablero = COLUMNAS * lado_bloque;
    alto_tablero = FILAS * lado_bloque;

    for(x = marco_x - 1; x <= marco_x + ancho_tablero; x++){
        gbt_dibujar_pixel(x, marco_y - 1, COL_MAG_BRILL);
        gbt_dibujar_pixel(x, marco_y + alto_tablero, COL_MAG_BRILL);
    }

    for(y = marco_y - 1; y <= marco_y + alto_tablero; y++){
        gbt_dibujar_pixel(marco_x - 1, y, COL_MAG_BRILL);
        gbt_dibujar_pixel(marco_x + ancho_tablero, y, COL_MAG_BRILL);
    }
}

void dibujar_tablero(int** tablero, int marco_x, int marco_y, int lado_bloque)
{
    int fila;
    int col;
    int color;

    for(fila = 0; fila < FILAS; fila++){
        for(col = 0; col < COLUMNAS; col++){
            color = tablero[fila][col];

            if(color == 0){
                color = COL_NEGRO;
            }

            dibujar_bloque_tablero(marco_x + col * lado_bloque,
                                   marco_y + fila * lado_bloque,
                                   color,
                                   lado_bloque);
        }
    }
}

void dibujar_pieza_activa(tPiezaActiva* pieza, int marco_x, int marco_y, int lado_bloque)
{
    int fila;
    int col;
    int grilla_x;
    int grilla_y;

    for(fila = 0; fila < 4; fila++){
        for(col = 0; col < 4; col++){
            if(piezas[pieza->tipo][pieza->rotacion][fila][col]){
                grilla_x = pieza->x + col;
                grilla_y = pieza->y + fila;

                if(grilla_x >= 0 && grilla_x < COLUMNAS && grilla_y >= 0 && grilla_y < FILAS){
                    dibujar_bloque_tablero(marco_x + grilla_x * lado_bloque,
                                           marco_y + grilla_y * lado_bloque,
                                           pieza->color,
                                           lado_bloque);
                }
            }
        }
    }
}

void dibujar_juego(int ancho, int alto, int** tablero, tPiezaActiva* pieza, int juego_terminado, int marco_x, int marco_y, int lado_bloque)
{
    dibujar_marco_tablero(marco_x, marco_y, lado_bloque);
    dibujar_tablero(tablero, marco_x, marco_y, lado_bloque);

    if(!juego_terminado){
        dibujar_pieza_activa(pieza, marco_x, marco_y, lado_bloque);
    }

    if(juego_terminado){
        dibujar_texto_8x8("JUEGO TERMINADO", calcular_x_centrada("JUEGO TERMINADO", ancho), alto / 2, COL_ROJO_BRILL);
        dibujar_texto_8x8("ESC PARA SALIR", calcular_x_centrada("ESC PARA SALIR", ancho), alto / 2 + 12, COL_GRIS_CLARO);
    }
}

void dibujar_puntuacion(int* puntaje, int altoPantalla, int altoJuego, int anchoPantalla, int anchoJuego) {
    int iniX = anchoJuego + 2;
    int finX = anchoPantalla - 10;
    int maxY = 60;
    int y = 7;
    int iniPal = iniX + 4;

    char buffer[20];
    sprintf(buffer, "%07d", *puntaje);

    dibujar_borde(maxY, finX, iniX, 4);

    dibujar_texto_8x8("SCORE", iniPal, y, COL_VERDE_BRILL);
    dibujar_texto_8x8(buffer, iniPal, y + ESPACIO_ENTRE_SCORES, COL_VERDE_BRILL);
}