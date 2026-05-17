#include "dibujar.h"
#include "juego.h"
#include "colores.h"
#include <string.h>
#include <stdio.h>
#include "tablero.h"
#include "fuentes.h"


int calcular_x_centrada(const char *palabra, const int ancho) {
    return (ancho - calcular_ancho_texto_5x7(palabra)) / 2;
}

void dibujar_linea_horizontal(const int x_ini, const int x_fin, const int y) {
    for(int x = x_ini; x <= x_fin; x++) {
        gbt_dibujar_pixel(x, y, COL_MAG_BRILL);
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

    dibujar_texto_5x7(titulo, xTitulo, y, COL_VERDE_BRILL);

    y = alto / 2;

    uint8_t colorJugar = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorInstrucciones = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_5x7(opciones[0], xJugar, y, colorJugar);
    dibujar_texto_5x7(opciones[1], xInstrucciones, y + 20, colorInstrucciones);

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
    dibujar_texto_5x7("JUEGO TERMINADO", calcular_x_centrada("JUEGO TERMINADO", ancho), alto / 2, COL_ROJO_BRILL);
    dibujar_texto_5x7("ENTER REINICIA", calcular_x_centrada("ENTER REINICIA", ancho), alto / 2 + 12, COL_GRIS_CLARO);
    dibujar_texto_5x7("ESC PARA SALIR", calcular_x_centrada("ESC PARA SALIR", ancho), alto / 2 + 24, COL_GRIS_CLARO);
    }
}

void dibujar_puntuacion(int* puntaje, int lineas, int piezas_caidas, int velocidad_caida_ms, int altoPantalla, int altoJuego, int anchoPantalla, int anchoJuego){

    int iniX = anchoJuego + 2;
    int finX = anchoPantalla - 10;
    int maxY = 110;
    int y = 7;
    int iniPal = iniX + 4;

    char bufferPuntaje[20];
    char bufferLineas[20];
    char bufferCaida[20];
    char bufferPiezas[20];

    sprintf(bufferPuntaje, "%07d", *puntaje);
    sprintf(bufferLineas, "%03d", lineas);
    sprintf(bufferCaida, "%04dMS", velocidad_caida_ms);
    sprintf(bufferPiezas, "%03d", piezas_caidas);

    dibujar_borde(maxY, finX, iniX, 4);

    // PUNTAJE
    dibujar_texto_5x7("PUNTAJE", iniPal, y, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferPuntaje, iniPal, y + 10, COL_VERDE_BRILL);

    // LINEAS
    dibujar_texto_5x7("LINEAS", iniPal, y + 28, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferLineas, iniPal, y + 38, COL_VERDE_BRILL);

    // CAIDA
    dibujar_texto_5x7("VEL-CAIDA", iniPal, y + 50, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferCaida, iniPal, y + 60, COL_VERDE_BRILL);

    // PIEZAS CAIDAS
    dibujar_texto_5x7("TETROMINOS", iniPal, y + 75, COL_VERDE_BRILL);
    dibujar_texto_5x7("UTILIZADOS", iniPal, y + 85, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferPiezas, iniPal, y + 95, COL_VERDE_BRILL);
}
